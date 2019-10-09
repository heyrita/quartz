#define Analyze_cxx


#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>

//******** Definition section *********
TGraph* g_xdl = NULL;
Int_t             nEntries;
//vector<Double_t>  x_values;
//vector<Double_t>  dl_values;

void Analyze::Begin(TTree * /*tree*/)
{
   TString option = GetOption();

   //******** Initialization section *********
   g_xdl = new TGraph();
   g_xdl->SetMarkerSize(0.5); g_xdl->SetMarkerStyle(20);
   
}

void Analyze::SlaveBegin(TTree * /*tree*/){
   
}

Bool_t Analyze::Process(Long64_t entry)
{
    fReader.SetEntry(entry);

    //******** Loop section *********
    GetEntry(entry);
    ++nEntries;
    //x_values.push_back(x);
    //dl_values.push_back(dl);
    g_xdl->SetPoint(nEntries,*x, *dl);
   return kTRUE;
}

void Analyze::SlaveTerminate(){}

void Analyze::Terminate()
{
   //******** Wrap-up section *********
   TCanvas *c1= new TCanvas();
   g_xdl->Draw("ap");
   c1->SaveAs(outputGraph.png);
}