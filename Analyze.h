//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct  9 14:47:47 2019 by ROOT version 6.16/00
// from TTree T/Quartz measurments R0OOT Data tree
// found on file: output1.root
//////////////////////////////////////////////////////////

#ifndef Analyze_h
#define Analyze_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraph.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include "TEntryList.h"
#include <vector>
#include <TH1.h>
#include <TH1D.h>

// Headers needed by this particular selector


class Analyze : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   TGraph        **fGraph;//fNgraph
   TH1F          **fHist;
   std::vector <std::vector <Double_t> > x_values;
   std::vector <std::vector <Double_t> > dl_values;
 
   

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> x = {fReader, "x"};
   TTreeReaderValue<Double_t> dl = {fReader, "dl"};
   //TTreeReaderValue<Double_t> id = {fReader, "id"};
   TTreeReaderArray<Char_t>  BarName = {fReader, "BarName"};
   TTreeReaderValue<Float_t> BarEdge = {fReader, "BarEdge"};


   Analyze(TTree * /*tree*/); //{ }
   Analyze();
   virtual ~Analyze(); //{ }
   virtual Int_t   Version() const; //{ return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0); //{ return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option); //{ fOption = option; }
   virtual void    SetObject(TObject *obj); //{ fObject = obj; }
   virtual void    SetInputList(TList *input); //{ fInput = input; }
   virtual TList  *GetOutputList() const; //{ return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate(TString outputrootfile, Int_t fNgraph);
   Int_t   CreateGraphArrays();
   Int_t   CreateHistArrays();
   void    FillHistos();

  //ClassDef(Analyze,0);

};

#endif

//#ifdef Analyze_cxx


//endif // #ifdef Analyze_cxx
