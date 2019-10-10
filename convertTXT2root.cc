////////////////////////////////////////////////////////////////////
//                Date: Thu Oct  3 21:02:34 CEST 2019             //
//               Autor: Rita Kvitochka                            //
// Program description: Convertion of the txt data                //
//                      with measurements into the root           //
//                      format. The txt data file contains        //
//                      information with position and size of the //
//                      chip edges. The measurements done with    //
//                      USB-microscope                            //
////////////////////////////////////////////////////////////////////

//root
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void convertTXT2root(TString inputDataFile, TString outputrootFile);

int main(int argc, char *argv[]){
  
  TString inputDataFile;
  TString outputrootFile;
  if(argc == 4 && atoi(argv[1])==0){
    inputDataFile = argv[2];
    outputrootFile = argv[3];
    cout<<"inputDataFile  : "<<inputDataFile<<endl
	<<"outputrootFile : "<<outputrootFile<<endl;
    convertTXT2root(inputDataFile, outputrootFile);
  }
  else if(argc>1 && atoi(argv[1])==9){
    for(Int_t i = 0; i < argc;i++)
      cout<<argv[i]<<endl;
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0  "<<endl
        <<"        [2] - in data file"<<endl
        <<"        [3] - out root file"<<endl;
  }

  return 0;
}

void convertTXT2root(TString inputDataFile, TString outputrootFile) {
  cout<<" ---> Conversion of "<<inputDataFile<<endl;
  ////////////////
	
	Char_t         BarName[4];
	Float_t        BarEdge;
  Double_t 		   x, dl, id;
  string         mot;
 // Int_t          k = 0;
  
  ifstream indata;
  indata.open(inputDataFile.Data()); 
  if (indata.is_open())
  {
    cout<< "File successfully open\n";
  }
  else
  {
    cout << "Error opening file";
  }
  
  ////////////////

  TFile *hfile = new TFile( outputrootFile, "RECREATE", "Ineffective area", 1);
  if (hfile->IsZombie()) {
    cout << "PROBLEM with the initialization of the output ROOT ntuple " 
	 << outputrootFile << ": check that the path is correct!!!"
	 << endl;
    exit(-1);
  }
  TTree *tree = new TTree("T", "Quartz measurments R0OOT Data tree");
  tree->SetMaxTreeSize(10000000000000);
  hfile->SetCompressionLevel(2);
  tree->SetAutoSave(1000000);
  // Create new event
  TTree::SetBranchStyle(0);
  //Event 
  tree->Branch("x", &x,"x/D");
  tree->Branch("dl", &dl,"dl/D");
  tree->Branch("id", &id,"id/D");
  tree->Branch("BarName", &BarName,"BarName/C");
  tree->Branch("BarEdge", &BarEdge,"BarEdge/F");
  ////////////////

	while (indata  >> mot )
  {
    //k++;
    //cout<<mot<<endl;
    //if(k == 3) assert(0);
    if(mot == "BARNAME:")
    {
      indata >> BarName;
	    cout << BarName << endl;
      indata >> mot; 
  	  if(mot == "BAREDGE:")
      {
        cout << "1" << endl;
        indata >> BarEdge;
        indata >> mot >> mot >> mot >> mot;
        cout<<mot<<endl;
   		}
	  }
    std::istringstream(mot) >> x;
    indata>>dl>>id;
    tree->Fill();
  }
	////////////////////// or ////////////////
/*while (indata  >> mot ){
    k++;
    if(k == 3) assert(0);
      if(mot == "BARNAME:"){
  indata >> BarName;
  indata >> mot;
  if(mot != "BAREDGE:") assert(0);
  indata >> mot;
  indata >> BarEdge;
  indata>>x>>dl>>id;
  tree->Fill();
    }
} */

  indata.close();
  
  hfile = tree->GetCurrentFile();
  hfile->Write();
  hfile->Close();


}
