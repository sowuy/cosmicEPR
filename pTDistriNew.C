#include "TFile.h"
#include <iostream>
#include <vector>
#include "TChain.h"
#include "TTree.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TROOT.h"
#include "TMath.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TPad.h"
#include "TLine.h"
#include "TH1F.h"
//#include "TRatioPlot.h"
#include "../../plugins/CosmicSplittingResolutionNtuple.h"

//you first decalre all the varaibles you are goingt o pick from the tree and use in this code. Be careful that the type of the varaible (Int, Float etc) have to be the same that when it was filled in the tree maker


//my interesting variables 

float pt[n_tracks][n_track_pos];
short charge[n_tracks][n_track_pos];

float unprop_pt[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];

ushort pixel_hits[n_tracks][n_track_pos];

ushort strip_layers[n_tracks][n_track_pos];

ushort muon_hits[n_tracks][n_track_pos];



////////////////////////////////////////////////////////////////////////////////

float bins[]={50,100,200,300,400,600,2000};
int binnum = 6;
//Declaration of hitsogramm i plan to plot with this code

TH1F *pthistoGlbUP =new TH1F("pthistoGlb","",binnum,bins);
TH1F *pthistoGlbLOW =new TH1F("pthistoGlbLOW","",binnum,bins);

TH1F *pthistoTkonlyUP =new TH1F("pthistoTkonly","",binnum,bins);
TH1F *pthistoTkonlyLOW =new TH1F("pthistoTkonlyLOW","",binnum,bins);

TH1F *pthistoTpfmsUP =new TH1F("pthistoTpfms","",binnum,bins);
TH1F *pthistoTpfmsLOW =new TH1F("pthistoTpfmsLOW","",binnum,bins);

TH1F *pthistoPickyUP =new TH1F("pthistoPicky","",binnum,bins);
TH1F *pthistoPickyLOW =new TH1F("pthistoPickyLOW","",binnum,bins);

TH1F *pthistoDYTUP =new TH1F("pthistoDYT","",binnum,bins);
TH1F *pthistoDYTLOW =new TH1F("pthistoDYTLOW","",binnum,bins);

TH1F *pthistoTunePUP =new TH1F("pthistoTuneP","",binnum,bins);
TH1F *pthistoTunePLOW =new TH1F("pthistoTunePLOW","",binnum,bins);


//Begining of teh function
void pTDistri(){

	//MC 
	// the next line is to link the tree you have - MC

	TChain *MCtreedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	MCtreedata->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilepton mass in my case for DY events.
	MCtreedata->SetBranchAddress("charge",charge);
	MCtreedata->SetBranchAddress("pt",pt);
	MCtreedata->SetBranchAddress("unprop_charge",unprop_charge);
	MCtreedata->SetBranchAddress("unprop_pt",unprop_pt);
	MCtreedata->SetBranchAddress("pixel_hits",pixel_hits);
	MCtreedata->SetBranchAddress("strip_layers",strip_layers);
	MCtreedata->SetBranchAddress("muon_hits",muon_hits);



	// This will get the numbers of entries of the tree.

	Long64_t nentries = MCtreedata->GetEntries();

	//DATA
	//
	//
	//
	// the next line is to link the tree you have - DATA 

	TChain *treedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilepton mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	treedata->SetBranchAddress("pt",pt);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("strip_layers",strip_layers);
	treedata->SetBranchAddress("muon_hits",muon_hits);



	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	//Decalaration of variable not in the tree that i use for the results

	Float_t sameCharge = 0.;
	Float_t goodMuon = 0.;

	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5  && unprop_pt[8][1]>30.){

			//
			//Algorithm choice
			//


			//global
			pthistoGlbUP->Fill(unprop_pt[0][0]);
			pthistoGlbLOW->Fill(unprop_pt[0][1]);
			//Tkonly
			pthistoTkonlyUP->Fill(unprop_pt[2][0]);
			pthistoTkonlyLOW->Fill(unprop_pt[2][1]);
			//Tpfms
			pthistoTpfmsUP->Fill(unprop_pt[3][0]);
			pthistoTpfmsLOW->Fill(unprop_pt[3][1]);
			//Picky
			pthistoPickyUP->Fill(unprop_pt[4][0]);
			pthistoPickyLOW->Fill(unprop_pt[4][1]);
			//DYT
			pthistoDYTUP->Fill(unprop_pt[5][0]);
			pthistoDYTLOW->Fill(unprop_pt[5][1]);
			//TuneP
			pthistoTunePUP->Fill(unprop_pt[8][0]);
			pthistoTunePLOW->Fill(unprop_pt[8][1]);

		}

		//	}
}// end loop p


TCanvas *c = new TCanvas("c", "canvas", 700, 600);


// Upper plot will be in pad5a
TPad *pad5a = new TPad("pad3a", "pad3a", 0, 0.19, 1, 1.0);
//pad5a->SetBottomMargin(0); // Upper and lower plot are joined
pad5a->SetGridx();         // Vertical grid
pad5a->Draw();             // Draw the upper pad: pad1
pad5a->cd();               // pad1 becomes the current pad
pthistoTunePUP->SetStats(111);          // No statistics on upper plot
pthistoTunePUP->Draw("E1");               // Draw h1
pthistoTunePLOW->Draw("E1 same");         // Draw h5 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg5->SetHeader("TuneP-MCP500");
leg5->SetFillColor(10);
leg5->AddEntry(pthistoTunePUP,"Upper leg ","l");
leg5->AddEntry(pthistoTunePLOW,"Lower leg","l");
leg5 -> Draw();


// lower plot will be in pad
c->cd();          // Go back to the main canvas before defining pad5b
TPad *pad5b = new TPad("pad5b", "pad5b", 0, 0, 1, 0.16);
pad5b->SetTopMargin(0);
pad5b->SetBottomMargin(0.2);
pad5b->SetGridx(); // vertical grid
pad5b->Draw();
pad5b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h5 = (TH1F*)pthistoTunePUP->Clone("h5");
h5->SetLineColor(kBlack);
h5->Sumw2();
h5->SetStats(0);      // No statistics on lower plot
h5->Divide(pthistoTunePUP,pthistoTunePLOW ,1,1,"B");
h5->SetMarkerStyle(21);
h5->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoTunePUP->SetXTitle("p_{t} [GeV]-TuneP");
pthistoTunePUP->SetLineColor(kBlue+1);
pthistoTunePUP->SetLineWidth(2);
pthistoTunePUP->GetXaxis()->SetTitleSize(0.05);


// Y axis h1 plot settings
pthistoTunePUP->GetYaxis()->SetTitleSize(20);
pthistoTunePUP->GetYaxis()->SetTitleFont(43);
pthistoTunePUP->GetYaxis()->SetTitleOffset(1.);
// h5 settings
pthistoTunePLOW->SetLineColor(kRed);
pthistoTunePLOW->SetLineWidth(2);
// Ratio plot (h5) settings
h5->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h5->GetYaxis()->SetTitle("up/low");
h5->GetYaxis()->SetNdivisions(505);
h5->GetYaxis()->SetTitleSize(20);
h5->GetYaxis()->SetTitleFont(43);
h5->GetYaxis()->SetTitleOffset(1.);
h5->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h5->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h5->GetXaxis()->SetTitleSize(20);
h5->GetXaxis()->SetTitleFont(43);
h5->GetXaxis()->SetTitleOffset(4.);
h5->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h5->GetXaxis()->SetLabelSize(15);
h5->SetStats(0);      // No statistics on lower plot
//h5->GetYaxis()->SetRangeUser(-2,6);







// Define the Canvas
/*TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
  c->Divide(3,2);
  c->cd(1);
// Upper plot will be in pad0a
TPad *pad0a = new TPad("pad0a", "pad0a", 0, 0.3, 1, 1.0);
//pad0a->SetBottomMargin(0); // Upper and lower plot are joined
pad0a->SetGridx();         // Vertical grid
pad0a->Draw();             // Draw the upper pad: pad1
pad0a->cd();               // pad1 becomes the current pad
//pthistoGlbUP->SetStats(0);          // No statistics on upper plot
pthistoGlbUP->Draw("E1");               // Draw h1
pthistoGlbLOW->Draw("E1 same");         // Draw h2 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg0 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg0->SetHeader("Global fit");
leg0->SetFillColor(10);
leg0->AddEntry(pthistoGlbUP,"Upper leg ","l");
leg0->AddEntry(pthistoGlbLOW,"Lower leg","l");
leg0 -> Draw();


// lower plot will be in pad
c->cd();          // Go back to the main canvas before defining pad0b
TPad *pad0b = new TPad("pad0b", "pad0b", 0, 0.56, 0.33, 0.66);
pad0b->SetTopMargin(0);
pad0b->SetBottomMargin(0.2);
pad0b->SetGridx(); // vertical grid
pad0b->Draw();
pad0b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h0 = (TH1F*)pthistoGlbUP->Clone("h0");
h0->SetLineColor(kBlack);
h0->Sumw2();
h0->SetStats(0);      // No statistics on lower plot
h0->Divide(pthistoGlbUP,pthistoGlbLOW ,1,1,"B");
h0->SetMarkerStyle(21);
h0->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoGlbUP->SetXTitle("p_t [GeV]");
pthistoGlbUP->SetLineColor(kBlue+1);
pthistoGlbUP->SetLineWidth(2);
// Y axis h1 plot settings
pthistoGlbUP->GetYaxis()->SetTitleSize(20);
pthistoGlbUP->GetYaxis()->SetTitleFont(43);
pthistoGlbUP->GetYaxis()->SetTitleOffset(1.55);
// h2 settings
pthistoGlbLOW->SetLineColor(kRed);
pthistoGlbLOW->SetLineWidth(2);
// Ratio plot (h0) settings
h0->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h0->GetYaxis()->SetTitle("up/low");
h0->GetYaxis()->SetNdivisions(505);
h0->GetYaxis()->SetTitleSize(20);
h0->GetYaxis()->SetTitleFont(43);
h0->GetYaxis()->SetTitleOffset(1.55);
h0->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h0->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h0->GetXaxis()->SetTitleSize(20);
h0->GetXaxis()->SetTitleFont(43);
h0->GetXaxis()->SetTitleOffset(4.);
h0->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h0->GetXaxis()->SetLabelSize(15);
h0->SetStats(0);      // No statistics on lower plot
h0->GetYaxis()->SetRangeUser(-2,6);

c->cd(2);

// Upper plot will be in pad1a
TPad *pad1a = new TPad("pad1a", "pad1a", 0, 0.3, 1, 1.0);
//pad1a->SetBottomMargin(0); // Upper and lower plot are joined
pad1a->SetGridx();         // Vertical grid
pad1a->Draw();             // Draw the upper pad: pad1
pad1a->cd();               // pad1 becomes the current pad
//pthistoTkonlyUP->SetStats(0);          // No statistics on upper plot
pthistoTkonlyUP->Draw("E1");               // Draw h1
pthistoTkonlyLOW->Draw("E1 same");         // Draw h2 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg1 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg1->SetHeader("Tkonly");
leg1->SetFillColor(10);
leg1->AddEntry(pthistoTkonlyUP,"Upper leg ","l");
leg1->AddEntry(pthistoTkonlyLOW,"Lower leg","l");
leg1 -> Draw();


// lower plot will be in pad
c->cd();          // Go back to the main canvas before defining pad1b
TPad *pad1b = new TPad("pad1b", "pad1b", 0.33, 0.56, 0.66,0.66);
pad1b->SetTopMargin(0);
pad1b->SetBottomMargin(0.2);
pad1b->SetGridx(); // vertical grid
pad1b->Draw();
pad1b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h1 = (TH1F*)pthistoTkonlyUP->Clone("h1");
h1->SetLineColor(kBlack);
h1->Sumw2();
h1->SetStats(0);      // No statistics on lower plot
h1->Divide(pthistoTkonlyUP,pthistoTkonlyLOW ,1,1,"B");
h1->SetMarkerStyle(21);
h1->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoTkonlyUP->SetXTitle("p_t [GeV]");
pthistoTkonlyUP->SetLineColor(kBlue+1);
pthistoTkonlyUP->SetLineWidth(2);
// Y axis h1 plot settings
pthistoTkonlyUP->GetYaxis()->SetTitleSize(20);
pthistoTkonlyUP->GetYaxis()->SetTitleFont(43);
pthistoTkonlyUP->GetYaxis()->SetTitleOffset(1.55);
// h2 settings
pthistoTkonlyLOW->SetLineColor(kRed);
pthistoTkonlyLOW->SetLineWidth(2);
// Ratio plot (h1) settings
h1->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h1->GetYaxis()->SetTitle("up/low");
h1->GetYaxis()->SetNdivisions(505);
h1->GetYaxis()->SetTitleSize(20);
h1->GetYaxis()->SetTitleFont(43);
h1->GetYaxis()->SetTitleOffset(1.55);
h1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h1->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h1->GetXaxis()->SetTitleSize(20);
h1->GetXaxis()->SetTitleFont(43);
h1->GetXaxis()->SetTitleOffset(4.);
h1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h1->GetXaxis()->SetLabelSize(15);
h1->SetStats(0);      // No statistics on lower plot
h1->GetYaxis()->SetRangeUser(-2,6);

c->cd(3);
// Upper plot will be in pad2ba
TPad *pad2a = new TPad("pad2a", "pad2a", 0, 0.3, 1, 1.0);
//pad2a->SetBottomMargin(0); // Upper and lower plot are joined
pad2a->SetGridx();         // Vertical grid
pad2a->Draw();             // Draw the upper pad: pad1
pad2a->cd();               // pad1 becomes the current pad
//pthistoTpfmsUP->SetStats(0);          // No statistics on upper plot
pthistoTpfmsUP->Draw("E1");               // Draw h1
pthistoTpfmsLOW->Draw("E1 same");         // Draw h2 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg2 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg2->SetHeader("TPFMS");
leg2->SetFillColor(10);
leg2->AddEntry(pthistoTpfmsUP,"Upper leg ","l");
leg2->AddEntry(pthistoTpfmsLOW,"Lower leg","l");
leg2 -> Draw();


// lower plot will be in pad
c->cd();          // Go back to the main canvas before defining pad2b
TPad *pad2b = new TPad("pad2b", "pad2b", 0.66, 0.56, 1, 0.66);
pad2b->SetTopMargin(0);
pad2b->SetBottomMargin(0.2);
pad2b->SetGridx(); // vertical grid
pad2b->Draw();
pad2b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h2 = (TH1F*)pthistoTpfmsUP->Clone("h2");
h2->SetLineColor(kBlack);
h2->Sumw2();
h2->SetStats(0);      // No statistics on lower plot
h2->Divide(pthistoTpfmsUP,pthistoTpfmsLOW ,1,1,"B");
h2->SetMarkerStyle(21);
h2->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoTpfmsUP->SetXTitle("p_t [GeV]");
pthistoTpfmsUP->SetLineColor(kBlue+1);
pthistoTpfmsUP->SetLineWidth(2);
// Y axis h1 plot settings
pthistoTpfmsUP->GetYaxis()->SetTitleSize(20);
pthistoTpfmsUP->GetYaxis()->SetTitleFont(43);
pthistoTpfmsUP->GetYaxis()->SetTitleOffset(1.55);
// h2 settings
pthistoTpfmsLOW->SetLineColor(kRed);
pthistoTpfmsLOW->SetLineWidth(2);
// Ratio plot (h2) settings
h2->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h2->GetYaxis()->SetTitle("up/low");
h2->GetYaxis()->SetNdivisions(505);
h2->GetYaxis()->SetTitleSize(20);
h2->GetYaxis()->SetTitleFont(43);
h2->GetYaxis()->SetTitleOffset(1.55);
h2->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h2->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h2->GetXaxis()->SetTitleSize(20);
h2->GetXaxis()->SetTitleFont(43);
h2->GetXaxis()->SetTitleOffset(4.);
h2->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h2->GetXaxis()->SetLabelSize(15);
h2->SetStats(0);      // No statistics on lower plot
h2->GetYaxis()->SetRangeUser(-2,6);

c->cd(4);
// Upper plot will be in pad3a
TPad *pad3a = new TPad("pad3a", "pad3a",0, 0.3, 1, 1.0);
//pad3a->SetBottomMargin(0); // Upper and lower plot are joined
pad3a->SetGridx();         // Vertical grid
pad3a->Draw();             // Draw the upper pad: pad1
pad3a->cd();               // pad1 becomes the current pad
//pthistoPickyUP->SetStats(0);          // No statistics on upper plot
pthistoPickyUP->Draw("E1");               // Draw h1
pthistoPickyLOW->Draw("E1 same");         // Draw h3 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg3 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg3->SetHeader("Picky fit");
leg3->SetFillColor(10);
leg3->AddEntry(pthistoPickyUP,"Upper leg ","l");
leg3->AddEntry(pthistoPickyLOW,"Lower leg","l");
leg3 -> Draw();


// lower plot will be in pad
c->cd();          // Go back to the main canvas before defining pad3b
TPad *pad3b = new TPad("pad3b", "pad3b", 0, 0.06, 0.33, 0.16);
pad3b->SetTopMargin(0);
pad3b->SetBottomMargin(0.2);
pad3b->SetGridx(); // vertical grid
pad3b->Draw();
pad3b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h3 = (TH1F*)pthistoPickyUP->Clone("h3");
h3->SetLineColor(kBlack);
h3->Sumw2();
h3->SetStats(0);      // No statistics on lower plot
h3->Divide(pthistoPickyUP,pthistoPickyLOW ,1,1,"B");
h3->SetMarkerStyle(21);
h3->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoPickyUP->SetXTitle("p_t [GeV]");
pthistoPickyUP->SetLineColor(kBlue+1);
pthistoPickyUP->SetLineWidth(2);
// Y axis h1 plot settings
pthistoPickyUP->GetYaxis()->SetTitleSize(20);
pthistoPickyUP->GetYaxis()->SetTitleFont(43);
pthistoPickyUP->GetYaxis()->SetTitleOffset(1.55);
// h3 settings
pthistoPickyLOW->SetLineColor(kRed);
pthistoPickyLOW->SetLineWidth(2);
// Ratio plot (h3) settings
h3->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h3->GetYaxis()->SetTitle("up/low");
h3->GetYaxis()->SetNdivisions(505);
h3->GetYaxis()->SetTitleSize(20);
h3->GetYaxis()->SetTitleFont(43);
h3->GetYaxis()->SetTitleOffset(1.55);
h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h3->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h3->GetXaxis()->SetTitleSize(20);
h3->GetXaxis()->SetTitleFont(43);
h3->GetXaxis()->SetTitleOffset(4.);
h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h3->GetXaxis()->SetLabelSize(15);
h3->SetStats(0);      // No statistics on lower plot
h3->GetYaxis()->SetRangeUser(-2,6);

c->cd(5);
// Upper plot will be in pad4a
TPad *pad4a = new TPad("pad4a", "pad4a", 0, 0.3, 1, 1.0);
//pad4a->SetBottomMargin(0); // Upper and lower plot are joined
pad4a->SetGridx();         // Vertical grid
pad4a->Draw();             // Draw the upper pad: pad1
pad4a->cd();               // pad1 becomes the current pad
//pthistoDYTUP->SetStats(0);          // No statistics on upper plot
pthistoDYTUP->Draw("E1");               // Draw h1
pthistoDYTLOW->Draw("E1 same");         // Draw h4 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg4 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg4->SetHeader("DYT");
leg4->SetFillColor(10);
leg4->AddEntry(pthistoDYTUP,"Upper leg ","l");
leg4->AddEntry(pthistoDYTLOW,"Lower leg","l");
leg4 -> Draw();


// lower plot will be in pad
c->cd();          // Go ba to the main canvas before defining pad4b
TPad *pad4b = new TPad("pad4b", "pad4b", 0.33, 0.06, 0.66,0.16);
pad4b->SetTopMargin(0);
pad4b->SetBottomMargin(0.2);
pad4b->SetGridx(); // vertical grid
pad4b->Draw();
pad4b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h4 = (TH1F*)pthistoDYTUP->Clone("h4");
h4->SetLineColor(kBlack);
h4->Sumw2();
h4->SetStats(0);      // No statistics on lower plot
h4->Divide(pthistoDYTUP,pthistoDYTLOW ,1,1,"B");
h4->SetMarkerStyle(21);
h4->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoDYTUP->SetXTitle("p_t [GeV]");
pthistoDYTUP->SetLineColor(kBlue+1);
pthistoDYTUP->SetLineWidth(2);
// Y axis h1 plot settings
pthistoDYTUP->GetYaxis()->SetTitleSize(20);
pthistoDYTUP->GetYaxis()->SetTitleFont(43);
pthistoDYTUP->GetYaxis()->SetTitleOffset(1.55);
// h4 settings
pthistoDYTLOW->SetLineColor(kRed);
pthistoDYTLOW->SetLineWidth(2);
// Ratio plot (h4) settings
h4->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h4->GetYaxis()->SetTitle("up/low");
h4->GetYaxis()->SetNdivisions(505);
h4->GetYaxis()->SetTitleSize(20);
h4->GetYaxis()->SetTitleFont(43);
h4->GetYaxis()->SetTitleOffset(1.55);
h4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h4->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h4->GetXaxis()->SetTitleSize(20);
h4->GetXaxis()->SetTitleFont(43);
h4->GetXaxis()->SetTitleOffset(4.);
h4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h4->GetXaxis()->SetLabelSize(15);
h4->SetStats(0);      // No statistics on lower plot
h4->GetYaxis()->SetRangeUser(-2,6);

c->cd(6);
// Upper plot will be in pad5a
TPad *pad5a = new TPad("pad3a", "pad3a", 0, 0.3, 1, 1.0);
//pad5a->SetBottomMargin(0); // Upper and lower plot are joined
pad5a->SetGridx();         // Vertical grid
pad5a->Draw();             // Draw the upper pad: pad1
pad5a->cd();               // pad1 becomes the current pad
//pthistoTunePUP->SetStats(0);          // No statistics on upper plot
pthistoTunePUP->Draw("E1");               // Draw h1
pthistoTunePLOW->Draw("E1 same");         // Draw h5 on top of h1
// Do not draw the Y axis label on the upper plot and redraw a small
// axis instead, in order to avoid the first label (0) to be clipped.

TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
leg5->SetHeader("TuneP");
leg5->SetFillColor(10);
leg5->AddEntry(pthistoTunePUP,"Upper leg ","l");
leg5->AddEntry(pthistoTunePLOW,"Lower leg","l");
leg5 -> Draw();


// lower plot will be in pad
c->cd();          // Go back to the main canvas before defining pad5b
TPad *pad5b = new TPad("pad5b", "pad5b", 0.66, 0.06, 1, 0.16);
pad5b->SetTopMargin(0);
pad5b->SetBottomMargin(0.2);
pad5b->SetGridx(); // vertical grid
pad5b->Draw();
pad5b->cd();       // pad2 becomes the current pad
// Define the ratio plot
TH1F *h5 = (TH1F*)pthistoTunePUP->Clone("h5");
h5->SetLineColor(kBlack);
h5->Sumw2();
h5->SetStats(0);      // No statistics on lower plot
h5->Divide(pthistoTunePUP,pthistoTunePLOW ,1,1,"B");
h5->SetMarkerStyle(21);
h5->Draw("E1");       // Draw the ratio plot
// h1 settings
pthistoTunePUP->SetXTitle("p_t [GeV]");
pthistoTunePUP->SetLineColor(kBlue+1);
pthistoTunePUP->SetLineWidth(2);
// Y axis h1 plot settings
pthistoTunePUP->GetYaxis()->SetTitleSize(20);
pthistoTunePUP->GetYaxis()->SetTitleFont(43);
pthistoTunePUP->GetYaxis()->SetTitleOffset(1.55);
// h5 settings
pthistoTunePLOW->SetLineColor(kRed);
pthistoTunePLOW->SetLineWidth(2);
// Ratio plot (h5) settings
h5->SetTitle(""); // Remove the ratio title
// Y axis ratio plot settings
h5->GetYaxis()->SetTitle("up/low");
h5->GetYaxis()->SetNdivisions(505);
h5->GetYaxis()->SetTitleSize(20);
h5->GetYaxis()->SetTitleFont(43);
h5->GetYaxis()->SetTitleOffset(1.55);
h5->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h5->GetYaxis()->SetLabelSize(15);
// X axis ratio plot settings
h5->GetXaxis()->SetTitleSize(20);
h5->GetXaxis()->SetTitleFont(43);
h5->GetXaxis()->SetTitleOffset(4.);
h5->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
h5->GetXaxis()->SetLabelSize(15);
h5->SetStats(0);      // No statistics on lower plot
h5->GetYaxis()->SetRangeUser(-2,6);*/



/*TFile *fout = new TFile("testpt.root ","RECREATE");

  pthistoGlb->Write();
  pthistoStalone->Write();

  fout->Close();*/

}// end of function 
