#define Analyze_cxx


#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TString.h>

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;

Analyze::Analyze(TTree * /*tree*/ =0) { ;}
Analyze::~Analyze(){ }
Analyze::Analyze(){};

//******** Definition section *********

Int_t fNgraph = 8;
Int_t fNhist= 8;
TString gNamef = "gr";
TString gName;
TString cNamef = "c";
TString cName;
TString hName;
TString hNamef = "h";





Int_t Analyze::CreateGraphArrays()
{
  
   fGraph = new TGraph*[fNgraph];
   for (Int_t i=0; i < fNgraph; i++) 
   {  
      gName=gNamef+(i+1);
      fGraph[i] = new TGraph();
      fGraph[i]->SetMarkerSize(0.5);
      fGraph[i]->SetTitle(gName);
      fGraph[i]->SetName(gName);
      fGraph[i]->SetMarkerStyle(20);
      //fGraph[i]->ComputeRange(0,400,0,0.5);
   }

    
   // Done
   return 0;
}

Int_t Analyze::CreateHistArrays()
{
  

   fHist= new TH1F*[fNhist];
   for (Int_t i=0; i < fNhist; i++) 
   {  
      hName=hNamef+(i+1);
      fHist[i] = new TH1F();
      fHist[i]->SetTitle(hName);
      fHist[i]->SetName(hName);
      //fGraph[i]->ComputeRange(0,400,0,0.5);
   }

    
   // Done
   return 0;
}
void Analyze::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

   //******** Initialization section *********
   CreateGraphArrays();
   CreateHistArrays();
   x_values.resize(fNhist);
   dl_values.resize(fNhist);

   
}

void Analyze::SlaveBegin(TTree * /*tree*/){

   
}



Bool_t Analyze::Process(Long64_t entry)
{
    fReader.SetLocalEntry(entry);
    
    //******** Loop section *********
    GetEntry(entry);
    
    if      ((Float_t)*BarEdge > 1.09 && (Float_t)*BarEdge < 1.11) {
      fGraph[0]->SetPoint(fGraph[0]->GetN(),*x, *dl); 
      x_values[0].push_back(*x);
      dl_values[0].push_back(*dl);}
    else if ((Float_t)*BarEdge > 1.19 && (Float_t)*BarEdge < 1.21) {
      fGraph[1]->SetPoint(fGraph[1]->GetN(),*x, *dl);
      x_values[1].push_back(*x);
      dl_values[1].push_back(*dl);}
    else if ((Float_t)*BarEdge > 2.09 && (Float_t)*BarEdge < 2.11) {
      fGraph[2]->SetPoint(fGraph[2]->GetN(),*x, *dl);
      x_values[2].push_back(*x);
      dl_values[2].push_back(*dl); }
    else if ((Float_t)*BarEdge > 2.19 && (Float_t)*BarEdge < 2.21 /*&&(Float_t)*x!=80.75 && (Float_t)*x!=120.75 */) {
      fGraph[3]->SetPoint(fGraph[3]->GetN(),*x, *dl);
      x_values[3].push_back(*x);
      dl_values[3].push_back(*dl);}
    else if ((Float_t)*BarEdge > 3.09 && (Float_t)*BarEdge < 3.11) {
      fGraph[4]->SetPoint(fGraph[4]->GetN(),*x, *dl);
      x_values[4].push_back(*x);
      dl_values[4].push_back(*dl);}
    else if ((Float_t)*BarEdge > 3.19 && (Float_t)*BarEdge < 3.21) {
      fGraph[5]->SetPoint(fGraph[5]->GetN(),*x, *dl);
      x_values[5].push_back(*x);
      dl_values[5].push_back(*dl);}
    else if ((Float_t)*BarEdge > 4.09 && (Float_t)*BarEdge < 4.11) {
      fGraph[6]->SetPoint(fGraph[6]->GetN(),*x, *dl);
      x_values[6].push_back(*x);
      dl_values[6].push_back(*dl); }
    else if ((Float_t)*BarEdge > 4.19 && (Float_t)*BarEdge < 4.21) {
      fGraph[7]->SetPoint(fGraph[7]->GetN(),*x, *dl);
      x_values[7].push_back(*x);
      dl_values[7].push_back(*dl);
     }

  
    
  return kTRUE;
}

void Analyze::FillHistos(){
Int_t nbins;
  for (Int_t k=0; k<fNhist; k++){
      nbins=x_values[k].size();
      nbins-=1;
      fHist[k]->SetBins(nbins, x_values[k].data());//Define hist bins number and xbins array
       for (Int_t i=1, j=0; i<=nbins && j<nbins; i++, j++){ 
        fHist[k]->SetBinContent(i,dl_values[k].at(j)); //Setting bin content for each hist
        }
    }
}

void Analyze::SlaveTerminate(){

}


void Analyze::Terminate(TString outputrootfile, Int_t fNgraph)
{
   //******** Wrap-up section *********
   TString cNameg = "graph";
   TString cNameh = "hist";
   TString cName;
   TString  cNamepng;
 
   FillHistos();
  
   TFile* outrootf = new TFile(outputrootfile, "RECREATE");
   for (Int_t i=0,j=1; i < fNgraph; i++, j++) 
   {
           cName = cNameg +j;
           cNamepng = cName +".pdf";
           TCanvas *cName = new TCanvas(); 
         fGraph[i]->Draw("Ap");
          fGraph[i]->Write();
         cName->SaveAs(cNamepng);
   }
 //outrootf->Close();
  
  //TFile* outrootf = new TFile(outputrootfile, "RECREATE");
  for (Int_t k=0,j=1; k < fNhist; k++, j++) {
          cName = cNameh + j;
          cNamepng = cName +".pdf";
          TCanvas *cName = new TCanvas(); 
          fHist[k]->Draw();
          fHist[k]->Write();
          cName->SaveAs(cNamepng);
  }
 outrootf->Close();
   

  
   }

void Analyze::Init(TTree *tree)
{
   fChain = tree;
   fReader.SetTree(tree);
}

Bool_t Analyze::Notify()
{
   return kTRUE;
}


 Int_t   Analyze::GetEntry(Long64_t entry, Int_t getall ) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
 void    Analyze::SetOption(const char *option) { fOption = option; }
 void    Analyze::SetObject(TObject *obj) { fObject = obj; }
 void    Analyze::SetInputList(TList *input) { fInput = input; }
 TList   *Analyze::GetOutputList() const { return fOutput; }
 Int_t   Analyze::Version() const { return 2; }

