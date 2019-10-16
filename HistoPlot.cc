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
#include <TH1.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TCollection.h>
#include <TKey.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <numeric>

using namespace std;

void DrawAllGraph(TString inputRootFile, TString outfilename); // First arg = 0
void Draw2Graph(TString inputRootFile, TString outfilename); // First arg = 1
void DrawAreaHist(TString inputRootFile);

int main(int argc, char *argv[]){
  TString inputRootFile;
  TString outfilename;
  if(argc == 4 && atoi(argv[1])==0){
    inputRootFile = argv[2];
    outfilename = argv[3];
    cout<<"inputRootFile  : "<<inputRootFile<<endl
	<<"Drawing all graphs"<<endl;
    DrawAllGraph(inputRootFile, outfilename);
  }
  else if(argc==4 && atoi(argv[1])==1){
    inputRootFile = argv[2];
    outfilename = argv[3];
    cout<<"inputRootFile  : "<<inputRootFile<<endl
	<<"Drawing 2 graphs"<<endl;
    Draw2Graph(inputRootFile, outfilename);
  }
else if(argc==3 && atoi(argv[1])==2){
   inputRootFile = argv[2];
    cout<<"inputRootFile  : "<<inputRootFile<<endl;
  DrawAreaHist(inputRootFile);
  }	
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0 if all graphs  "<<endl
        <<"              1 if by two graphs"<<endl
        <<"              2 if histos"<<endl
        <<"        [2] - in root file"<<endl
         <<"        [3] - outfile.png "<<endl;
  }

  return 0;
}


Double_t GetMeanMg(TMultiGraph *mg){
	vector<Double_t> gMean;
	TGraph *g;
	Double_t sum_of_elems;
    TIter   next(mg->GetListOfGraphs());
    while ((g = (TGraph*) next())) {
       gMean.push_back(g->GetMean(2));
	}
	for (auto& n : gMean)
    sum_of_elems += n;

	Double_t mgMean = sum_of_elems/(mg->GetListOfGraphs()->GetEntries());
	return mgMean;
}

void DrawAllGraph(TString inputRootFile, TString outfilename){

	TFile *f = new TFile(inputRootFile);
	TIter keyList(f->GetListOfKeys());
	TMultiGraph *All_brinks = new TMultiGraph ("All edges of goodbar","All edges of goodbar");
	TKey *key = 0;
	TAxis *xAxis=0;
	TAxis *yAxis=0;
	
	while ( (key=(TKey*)keyList()) )
	{
		TGraph* gr = (TGraph*)key->ReadObj();
		//Chek if this is a graph
		TClass *cl = gROOT->GetClass(key->GetClassName());
        if (!cl->InheritsFrom("TGraph")) continue;
		
			TString name = gr->GetName();
			if (name == "gr1" || name == "gr3") {
				gr->SetMarkerColor(46);gr->SetLineColor(46);
				if (name == "gr1") gr->SetMarkerStyle(8);
			    if (name == "gr3") gr->SetMarkerStyle(22); }
			if (name == "gr4" || name == "gr6") {
				gr->SetMarkerColor(38);gr->SetLineColor(38);
				if (name == "gr4") gr->SetMarkerStyle(8);
				if (name == "gr6") gr->SetMarkerStyle(22);}
			if (name == "gr5" || name == "gr7") {
				gr->SetMarkerColor(30);gr->SetLineColor(30);
				if (name == "gr5") gr->SetMarkerStyle(8);
				if (name == "gr7") gr->SetMarkerStyle(22);}
			if (name == "gr8" || name == "gr2") {
				gr->SetMarkerColor(1);gr->SetLineColor(1);
				if (name == "gr8") gr->SetMarkerStyle(8);
				if (name == "gr2") gr->SetMarkerStyle(22);}
			gr->SetLineWidth(3);
			gr->SetMarkerSize(1);
			All_brinks->Add(gr);


	}
	
	xAxis = All_brinks->GetXaxis();
    xAxis->SetTitle("x, mm");
    yAxis = All_brinks->GetYaxis();
  	yAxis->SetTitle("Edge size, mm");
  	//yAxis->SetRange(0,0.6);
  	TCanvas *c1 = new TCanvas();
  	c1->Clear();
  	c1->SetFillColor(kWhite);
  	c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.08);
  c1->SetBottomMargin(0.09);
   gStyle->SetOptStat("n");
  	All_brinks->Draw("AP");
  	yAxis->SetRange(0,1);
  	gPad->Modified();
  	All_brinks->SetMaximum(0.6);
  	c1->SaveAs("graphs_b.pdf");
  	Double_t meanMg = GetMeanMg(All_brinks);
  	cout << "Mean value of size" << meanMg << endl;

	f->Close();
}


void Draw2Graph(TString inputRootFile, TString outfilename) {

	TFile *f = new TFile(inputRootFile);
	TIter keyList(f->GetListOfKeys());
	vector <TMultiGraph *> mGraphs;
	TMultiGraph *Two_ribs1 = new TMultiGraph ("Two edges 1", "Two edges 1");
	mGraphs.push_back(Two_ribs1);
	TMultiGraph *Two_ribs2 = new TMultiGraph ("Two edges 2", "Two edges 2");
	mGraphs.push_back(Two_ribs2);
	TMultiGraph *Two_ribs3 = new TMultiGraph ("Two edges 3", "Two edges 3");
	mGraphs.push_back(Two_ribs3);
	TMultiGraph *Two_ribs4 = new TMultiGraph ("Two edges 4", "Two edges 4");
	mGraphs.push_back(Two_ribs4);
	TKey *key = 0;
	TAxis *xAxis=0;
	TAxis *yAxis=0;
	TString cName = "c";
	TString cNamepng;
	
	while ( (key=(TKey*)keyList()) )
	{
		TGraph* gr = (TGraph*)key->ReadObj();
		//Chek if this is a graph
		if(gr != 0)
		{
			TString name = gr->GetName();
			if (name == "gr1" || name == "gr3") {gr->SetMarkerColor(46);gr->SetLineColor(46); 
				if (name == "gr1") gr->SetMarkerStyle(8);
			    if (name == "gr3") gr->SetMarkerStyle(22);
				mGraphs[0]->Add(gr);}
			if (name == "gr4" || name == "gr6") {gr->SetMarkerColor(38);gr->SetLineColor(38); 
				if (name == "gr4") gr->SetMarkerStyle(8);
				if (name == "gr6") gr->SetMarkerStyle(22);
				mGraphs[1]->Add(gr);}
			if (name == "gr5" || name == "gr7") {gr->SetMarkerColor(30);gr->SetLineColor(30); 
				if (name == "gr5") gr->SetMarkerStyle(8);
				if (name == "gr7") gr->SetMarkerStyle(22);
				mGraphs[2]->Add(gr);}
			if (name == "gr8" || name == "gr2") {gr->SetMarkerColor(1);gr->SetLineColor(1);
				if (name == "gr8") gr->SetMarkerStyle(8);
				if (name == "gr2") gr->SetMarkerStyle(22);
			 mGraphs[3]->Add(gr);}
			gr->SetMarkerSize(1);

		}

	}

	for(Int_t i =0; i<4; i++){
	xAxis = mGraphs[i]->GetXaxis();
    xAxis->SetTitle("Position[mm]");
    yAxis = mGraphs[i]->GetYaxis();
  	yAxis->SetTitle("Size of in. area[micro m]");
  	cName+=i;
  	cNamepng=cName+".pdf";
  	TCanvas *cName = new TCanvas();
  	cName->BuildLegend();
  	cName->SetFillColor(kWhite);
  	//mGraphs[i]->SetLineWidth(3);
  	mGraphs[i]->Draw("AP");

  	cName->SaveAs(cNamepng);
    }
	f->Close();
}

void DrawAreaHist(TString inputRootFile) {

	TFile *f = new TFile(inputRootFile);
	
	TIter keyList(f->GetListOfKeys());
	TKey *key = 0;
	Int_t i;
	long unsigned int k=0,j=0;
	vector <Double_t> bin_w;
	vector <Double_t> content;

	vector <Double_t> area;
	vector <Double_t> width;
	while ((key=(TKey*)keyList() ) )
	{
		TH1F* h = (TH1F*)key->ReadObj();
		for (i=1; i < (h->GetNbinsX()); i++){
			bin_w.push_back(h->GetBinWidth(i)) ;
			content.push_back(h->GetBinContent(i));
			}
			
	}
    f->Close();
    while (k<bin_w.size())
    {
    area.push_back(bin_w.at(k)*content.at(k));
    k++;
   }
 
    Int_t sizeV=area.size();
    width.resize(sizeV);
    cout << area.size();
  	TH1F * h1 = new TH1F("h", "Area", sizeV, 0, 10);
			cout << "Histogram is defined" << endl;
	for (Int_t m =0; m<sizeV; m++)
		h1->Fill(area.at(m));

 	TCanvas *c1 = new TCanvas();

	gStyle->SetOptStat("iou");
	
	TFile* areaf= new TFile("areaf_good.root", "RECREATE");
 	h1->Draw();
 	h1->Write();
 	c1->SaveAs("area_good.pdf");
	areaf->Close();

}