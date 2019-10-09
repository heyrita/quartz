#define Analyze_cxx
// The class definition in Analyze.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("Analyze.C")
// root> T->Process("Analyze.C","some options")
// root> T->Process("Analyze.C+")
//


#include "Analyze.h"
#include <TH2.h>
#include <TStyle.h>

void Analyze::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   //******** Initialization section *********
}

void Analyze::SlaveBegin(TTree * /*tree*/){}

Bool_t Analyze::Process(Long64_t entry)
{
   
   fReader.SetEntry(entry);
    //******** Loop section *********
    // GetEntry(entry) here.

   return kTRUE;
}

void Analyze::SlaveTerminate(){}

void Analyze::Terminate()
{
   //******** Wrap-up section *********
}