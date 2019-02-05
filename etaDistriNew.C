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

float eta[n_tracks][n_track_pos];
short charge[n_tracks][n_track_pos];

float unprop_theta[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];


ushort pixel_hits[n_tracks][n_track_pos];

ushort strip_layers[n_tracks][n_track_pos];

float unprop_pt[n_tracks][n_track_pos];

////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code



TH1F *eta_DATA_P10 =new TH1F("eta_DATA_P10","",20,-3,3);
TH1F *eta_MC_P10 =new TH1F("eta_MC_P10","",20,-3,3);

TH1F *eta_DATA_P100 =new TH1F("eta_DATA_P100","",20,-3,3);
TH1F *eta_MC_P100 =new TH1F("eta_MC_P100","",20,-3,3);

TH1F *eta_DATA_P500 =new TH1F("eta_DATA_P500","",20,-3,3);
TH1F *eta_MC_P500 =new TH1F("eta_MC_P500","",20,-3,3);


//Begining of teh function
void etaDistriNew(){

	

	//DATA
	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	treedata->Add("ROOT_Files/MC2016/MC_2016_P500.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dileetaon mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	//treedata->SetBranchAddress("theta",theta);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_theta",unprop_theta);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("strip_layers",strip_layers);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);


	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	
	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree
		
		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//
		//
		//Algorithm choice
		//
		

		for (int i=0;i<n_tracks;i++){


			for (int j=0;j<n_track_pos;j++){

				eta[i][j]=-log(tan(unprop_theta[i][j]/2));
			}
		}
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){




				//TuneP
					eta_DATA_P10->Fill(eta[8][0]);
					eta_MC_P10->Fill(eta[8][1]);
	}
	}// end loop p


			TCanvas *c = new TCanvas("c", "canvas", 700, 600);


			// Upper plot will be in pad5a
			TPad *pad5a = new TPad("pad3a", "pad3a", 0, 0.18, 1, 1.0);
			//pad5a->SetBottomMargin(0); // Upper and lower plot are joined
			pad5a->SetGridx();         // Vertical grid
			pad5a->Draw();             // Draw the upper pad: pad1
			pad5a->cd();               // pad1 becomes the current pad
			eta_DATA_P10->SetStats(111);          // No statistics on upper plot
			eta_DATA_P10->Draw("E1");               // Draw h1
			eta_MC_P10->Draw("E1 same");         // Draw h5 on top of h1
			// Do not draw the Y axis label on the upper plot and redraw a small
			// axis instead, in order to avoid the first label (0) to be clipped.

			TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
			leg5->SetHeader("TuneP-MCP500");
			leg5->SetFillColor(10);
			leg5->AddEntry(eta_DATA_P10,"Upper leg ","l");
			leg5->AddEntry(eta_MC_P10,"Lower leg","l");
			leg5 -> Draw();


			// lower plot will be in pad
			c->cd();          // Go back to the main canvas before defining pad5b
			TPad *pad5b = new TPad("pad5b", "pad5b", 0, 0, 1, 0.17);
			pad5b->SetTopMargin(0);
			pad5b->SetBottomMargin(0.2);
			pad5b->SetGridx(); // vertical grid
			pad5b->Draw();
			pad5b->cd();       // pad2 becomes the current pad
			// Define the ratio plot
			TH1F *h5 = (TH1F*)eta_DATA_P10->Clone("h5");
			h5->SetLineColor(kBlack);
			h5->Sumw2();
			h5->SetStats(0);      // No statistics on lower plot
			h5->Divide(eta_DATA_P10,eta_MC_P10 ,1,1,"B");
			h5->SetMarkerStyle(21);
			h5->Draw("E1");       // Draw the ratio plot
			// h1 settings
			eta_DATA_P10->SetXTitle("#eta-TuneP ");
			eta_DATA_P10->SetLineColor(kBlue+1);
			eta_DATA_P10->SetLineWidth(2);
			eta_DATA_P10->GetXaxis()->SetTitleSize(0.05);


			// Y axis h1 plot settings
			eta_DATA_P10->GetYaxis()->SetTitleSize(20);
			eta_DATA_P10->GetYaxis()->SetTitleFont(43);
			eta_DATA_P10->GetYaxis()->SetTitleOffset(1.);
			// h5 settings
			eta_MC_P10->SetLineColor(kRed);
			eta_MC_P10->SetLineWidth(2);
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
			h5->GetYaxis()->SetRangeUser(0.8,1.2);






	
}// end of function 
