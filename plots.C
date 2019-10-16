//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

Int_t plots(){

  TString fileN;
  fileN = "./badbar.root";

  TFile *f1 = new TFile(fileN.Data());

  TH1D *h1_1 = (TH1D*)f1->Get("h8");

  //h1_1->Rebin(4);

  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,600);

  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.09);
  

  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
   gStyle->SetOptStat("rie");
  //gStyle->SetOptStat(kFALSE);
  h1_1->SetTitle("Edge 8");
  h1_1->SetLineColor(kBlack);
  h1_1->GetXaxis()->SetTitle("x, mm");
  h1_1->GetYaxis()->SetTitle("Edge size, mm");
  

  h1_1->SetLineWidth(3.0);
 
 

  h1_1->Draw();
  c1->SaveAs("h8_b.png");

  
  


  //h1_1->GetXaxis()->SetTitle("Amplitude, V");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);
  //h1_1->GetXaxis()->CenterTitle();
  //h1_1->GetXaxis()->SetTitleSize(0.05);
  //h1_1->GetXaxis()->SetTitleOffset(0.75);


  /*
  h1_1->Fit("gaus");
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_1, "Without corrections","l");
  leg->AddEntry(h1_2, "With corrections","l");
  leg->Draw();
  */

  return 0;
}
