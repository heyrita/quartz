////////////////////////////////////////////////////////////////////
//                Date: Tue Oct 8 21:40:34 CEST 2019              //
//               Autor: Rita Kvitochka                            //
// Program description: Reading a tree with data and making       //
//                      a histogram with output file given        //
//                      format.                         		  //
////////////////////////////////////////////////////////////////////
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2.h>


//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void HistoPlot(TString inputRootFile, TString outputHisto);


int main(int argc, char *argv[]){
  TString inputRootFile;
  TString outputHisto;
  if(argc == 4 && atoi(argv[1])==0){
    inputRootFile = argv[2];
    outputHisto = argv[3];
    cout<<"inputRootFile  : "<<inputRootFile<<endl
	<<"outputHisto : "<<outputHisto<<endl;
    HistoPlot(inputRootFile, outputHisto);
  }
  else if(argc>1 && atoi(argv[1])==9){
    for(Int_t i = 0; i < argc;i++)
      cout<<argv[i]<<endl;
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0  "<<endl
        <<"        [2] - in root file"<<endl
        <<"        [3] - out png file"<<endl;
  }

  return 0;
}



void HistoPlot(TString inputRootFile, TString outputHisto) {

	TFile *f = new TFile(inputRootFile);
	TTree *t1 = (TTree*)f->Get("T");

	Double_t x, dl;

	t1->SetBranchAddress("x", &x);
	t1->SetBranchAddress("dl", &dl);

	TH2F *h_xdl = new TH2F("h_xdl", "x Vs dl", 400, 0, 400, 20, 0, 0.5);

	Int_t nEntries = (Int_t)t1->GetEntries();
	
	for (Int_t i=0; i<nEntries; i++)
	{ 
		t1->GetEntry(i);
	    h_xdl->Fill(x, dl);
	}

	TCanvas *c1= new TCanvas();
	h_xdl->GetXaxis()->SetTitle("Position");
	h_xdl->GetYaxis()->SetTitle("Size");
	h_xdl->SetMarkerSize(20);
	h_xdl->Draw();

	c1->SaveAs(outputHisto);

	f->Close();
}