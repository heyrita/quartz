#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

Int_t areas(){

  TString fileN;
  fileN = "./hists_b.root";

  TFile *f = new TFile(fileN.Data());

  TH1D *h = (TH1D*)f->Get("h8");
  
  Int_t i;
  long unsigned int k=0,j=0;
  vector <Double_t> bin_w;
  vector <Double_t> content;
  vector <Double_t> area;
  vector <Double_t> width;
  TFile* areaf= new TFile("h8_b_area.root", "RECREATE");
    TTree * T = new TTree ("T", "Information about area"); 
    for (i=1; i < (h->GetNbinsX()); i++){
      bin_w.push_back(h->GetBinWidth(i)) ;
      content.push_back(h->GetBinContent(i));
      }
      
  
    f->Close();
    while (k<bin_w.size())
    {
    area.push_back(bin_w.at(k)*content.at(k));
    k++;
     }
    Int_t sizeV=area.size();
    T->Branch("width", &bin_w);
    T->Branch("content", &content);
    T->Branch("area", &area);
    
    for (Int_t m=0; m<sizeV; m++)T->Fill();
    
    
  T->Write();
 
  return 0;
}
