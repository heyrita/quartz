#include <TSelector.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TChain.h>
#include <Analyze.h>
#include <TCanvas.h>
#include <TStyle.h>

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

void analyzer (TString inrootfilelist, TString outrootfile);
void areaPlot (TString inrootfilelist, TString outHist);


int main(int argc, char *argv[])
{
  TString inrootfilelist;
  TString outrootfile;
  TString outHist;
  if(argc==3) {
    inrootfilelist = argv[1];
    outrootfile = argv[2];

    analyzer(inrootfilelist, outrootfile);
  }
  else if (argc==4 && atoi(argv[1])==1)
  {inrootfilelist = argv[2];
    outHist = argv[3];
     areaPlot(inrootfilelist,outHist);}
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] - in root files list"<<endl
        <<"        [2] - out root file"<<endl;
  }

  return 0;
}

void analyzer (TString inrootfilelist, TString outrootfile){

  cout<<" ---> Analysis of "<<inrootfilelist<<endl;

  TString rootFileName;
  ifstream indata;
  Int_t fNgraph=0;
  cout << "Creating the chain" << endl;

  TChain *chain = new TChain("T");
  indata.open(inrootfilelist.Data()); 
  assert(indata.is_open());  
  while (indata  >> rootFileName){
    ++fNgraph;
    cout<<"        adding "<<rootFileName<<endl;
    chain->Add(rootFileName.Data(),-1);
  }

  indata.close();

  Analyze *Selector = new Analyze();
  chain->Process(Selector);
  Selector->Terminate(outrootfile, fNgraph);

}

void areaPlot (TString inrootfilelist, TString outHist){


  cout<<" ---> Analysis of "<<inrootfilelist<<endl;

  TString rootFileName;
  ifstream indata;
  Int_t fNgraph=0;
  cout << "Creating the chain" << endl;

  TChain *chain = new TChain("T");
  indata.open(inrootfilelist.Data()); 
  assert(indata.is_open());  
  while (indata  >> rootFileName){
    ++fNgraph;
    cout<<"        adding "<<rootFileName<<endl;
    chain->Add(rootFileName.Data(),-1);
  }
  TCanvas *c1 = new TCanvas();

  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.09);
  
gStyle->SetOptStat("rie");
 chain->Draw("dl*x");

 c1->SaveAs(outHist);

  indata.close();
}