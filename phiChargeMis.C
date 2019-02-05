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

float phi[n_tracks][n_track_pos];
short charge[n_tracks][n_track_pos];

float unprop_phi[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];
float unprop_pt[n_tracks][n_track_pos];

ushort pixel_hits[n_tracks][n_track_pos];

ushort strip_layers[n_tracks][n_track_pos];


////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code

/*TH1F *phihistoGlbUP =new TH1F("phihistoGlb","",6,-3,0);
TH1F *phihistoGlbLOW =new TH1F("phihistoGlbLOW","",6,-3,0);

TH1F *phihistoTkonlyUP =new TH1F("phihistoTkonly","",6,-3,0);
TH1F *phihistoTkonlyLOW =new TH1F("phihistoTkonlyLOW","",6,-3,0);

TH1F *phihistoTpfmsUP =new TH1F("phihistoTpfms","",6,-3,0);
TH1F *phihistoTpfmsLOW =new TH1F("phihistoTpfmsLOW","",6,-3,0);

TH1F *phihistoPickyUP =new TH1F("phihistoPicky","",6,-3,0);
TH1F *phihistoPickyLOW =new TH1F("phihistoPickyLOW","",6,-3,0);

TH1F *phihistoDYTUP =new TH1F("phihistoDYT","",6,-3,0);
TH1F *phihistoDYTLOW =new TH1F("phihistoDYTLOW","",6,-3,0);

TH1F *phihistoTunePUP =new TH1F("phihistoTuneP","",6,-3,0);
TH1F *phihistoTunePLOW =new TH1F("phihistoTunePLOW","",6,-3,0);
*/TH1F *phihistoGlbUP =new TH1F("phihistoGlb","",1,-3,0);
  TH1F *phihistoGlbLOW =new TH1F("phihistoGlbLOW","",1,-3,0);

  TH1F *phihistoTkonlyUP =new TH1F("phihistoTkonly","",1,-3,0);
  TH1F *phihistoTkonlyLOW =new TH1F("phihistoTkonlyLOW","",1,-3,0);

  TH1F *phihistoTpfmsUP =new TH1F("phihistoTpfms","",1,-3,0);
  TH1F *phihistoTpfmsLOW =new TH1F("phihistoTpfmsLOW","",1,-3,0);

  TH1F *phihistoPickyUP =new TH1F("phihistoPicky","",1,-3,0);
  TH1F *phihistoPickyLOW =new TH1F("phihistoPickyLOW","",1,-3,0);

  TH1F *phihistoDYTUP =new TH1F("phihistoDYT","",1,-3,0);
  TH1F *phihistoDYTLOW =new TH1F("phihistoDYTLOW","",1,-3,0);

  TH1F *phihistoTunePUP =new TH1F("phihistoTuneP","",1,-3,0);
  TH1F *phihistoTunePLOW =new TH1F("phihistoTunePLOW","",1,-3,0);

//Begining of teh function
void phiChargeMis(){


	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	//treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_2016.root");
	treedata->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");
	//treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");


	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilephion mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	treedata->SetBranchAddress("phi",phi);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_phi",unprop_phi);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("strip_layers",strip_layers);


	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	//Decalaration of variable not in the tree that i use for the results

	Float_t sameCharge = 0.;
	Float_t goodMuon = 0.;

	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//
		//selection cuts

		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][1]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][1]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][1]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][1]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][1]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){


			//Algorithm choice

			//global
			phihistoGlbUP->Fill(unprop_phi[8][0]);
			if (charge[0][1]!=charge[8][0]){ 
				phihistoGlbLOW->Fill(unprop_phi[8][0]);
			}
			//Tkonly
			phihistoTkonlyUP->Fill(unprop_phi[8][0]);
			if (charge[2][1]!=charge[8][0]){ 
				phihistoTkonlyLOW->Fill(unprop_phi[8][0]);
			}
			//Tpfms
			phihistoTpfmsUP->Fill(unprop_phi[8][0]);
			if (charge[3][1]!=charge[8][0]){ 
				phihistoTpfmsLOW->Fill(unprop_phi[8][0]);
			}
			//Picky
			phihistoPickyUP->Fill(unprop_phi[8][0]);
			if (charge[4][1]!=charge[8][0]){ 
				phihistoPickyLOW->Fill(unprop_phi[8][0]);
			}
			//DYT
			phihistoDYTUP->Fill(unprop_phi[8][0]);
			if (charge[5][1]!=charge[8][0]){ 
				phihistoDYTLOW->Fill(unprop_phi[8][0]);
			}
			//TuneP
			phihistoTunePUP->Fill(unprop_phi[8][0]);
			if (charge[8][1]!=charge[8][0]){ 
				phihistoTunePLOW->Fill(unprop_phi[8][0]);
			}
		}
	}// end loop p


	// Define the Canvas
	TCanvas *c = new TCanvas("c", "canvas", 700,500);

	//c->SetLogy();


	// Define the ratio plot
	TH1F *h0 = (TH1F*)phihistoGlbUP->Clone("h0");
	h0->SetLineColor(kBlack);
	h0->Sumw2();
	h0->SetStats(1111);      // No statistics on lower plot
	h0->Divide(phihistoGlbLOW,phihistoGlbUP ,1,1,"B");
	h0->SetMarkerStyle(21);
	h0->SetMarkerColor(kBlack);
	h0->GetYaxis()->SetTitleSize(0.05);
	//h0->GetYaxis()->SetRangeUser(0,0.07);
	h0->Draw("E0");       // Draw the ratio plot
	// Y axis ratio plot settings
	h0->GetYaxis()->SetTitle("Prob. of misidentification");
	// X axis ratio plot settings
	h0->GetXaxis()->SetTitle("#phi-TuneP upper leg tag");
	h0->GetXaxis()->SetTitleSize(0.05);
	h0->GetXaxis()->SetTitleOffset(0.91);
	h0->GetYaxis()->SetRangeUser(0,0.004);
	h0->GetYaxis()->SetTitleOffset(1.1);
	float glbBin =  h0->GetBinContent(1);
	cout << "Charge rate - glb : " << glbBin << endl;

	TH1F *h1 = (TH1F*)phihistoTkonlyUP->Clone("h1");
	h1->SetLineColor(kRed);
	h1->Sumw2();
	h1->SetStats(0);      // No statistics on lower plot
	h1->Divide(phihistoTkonlyLOW,phihistoTkonlyUP ,1,1,"B");
	h1->SetMarkerStyle(22);
	h1->SetMarkerColor(kRed);
	float TkonlyBin =  h1->GetBinContent(1);
	cout << "Charge rate - Tkonly : " << TkonlyBin << endl;

	h1->Draw("E0 SAME");       // Draw the ratio plot

	TH1F *h2 = (TH1F*)phihistoTpfmsUP->Clone("h2");
	h2->SetLineColor(kOrange);
	h2->Sumw2();
	h2->SetStats(0);      // No statistics on lower plot
	h2->Divide(phihistoTpfmsLOW,phihistoTpfmsUP ,1,1,"B");
	h2->SetMarkerStyle(20);
	h2->SetMarkerColor(kOrange);
	float TpfmsBin =  h2->GetBinContent(1);
	cout << "Charge rate - TPFMS : " << TpfmsBin << endl;

	h2->Draw("E0 SAME");       // Draw the ratio plot



	TH1F *h3 = (TH1F*)phihistoPickyUP->Clone("h3");
	h3->SetLineColor(kMagenta);
	h3->Sumw2();
	h3->SetStats(0);      // No statistics on lower plot
	h3->Divide(phihistoPickyLOW,phihistoPickyUP ,1,1,"B");
	h3->SetMarkerStyle(23);
	h3->SetMarkerColor(kMagenta);
	float PickyBin =  h3->GetBinContent(1);
	cout << "Charge rate - Picky : " << PickyBin << endl;

	h3->Draw("E0 SAME");       // Draw the ratio plot


	// Define the ratio plot
	TH1F *h4 = (TH1F*)phihistoDYTUP->Clone("h4");
	h4->SetLineColor(kGreen);
	h4->Sumw2();
	h4->SetStats(0);      // No statistics on lower plot
	h4->Divide(phihistoDYTLOW,phihistoDYTUP ,1,1,"B");
	h4->SetMarkerStyle(24);
	h4->SetMarkerColor(kGreen);
	float DYTBin =  h4->GetBinContent(1);
	cout << "Charge rate - DYT : " << DYTBin << endl;

	h4->Draw("E0 SAME");       // Draw the ratio plot

	// Define the ratio plot
	TH1F *h5 = (TH1F*)phihistoTunePUP->Clone("h5");
	h5->SetLineColor(kBlue);
	h5->Sumw2();
	h5->SetMarkerColor(kBlue);

	h5->SetStats(1111);      // No statistics on lower plot
	h5->Divide(phihistoTunePLOW,phihistoTunePUP ,1,1,"B");
	h5->SetMarkerStyle(25);
	float TunePBin =  h5->GetBinContent(1);
	cout << "Charge rate - TuneP : " << TunePBin << endl;
	// Y axis ratio plot settings
	/*h5->GetYaxis()->SetTitle("Prob. of misidentification");
	// X axis ratio plot settings
	h5->GetXaxis()->SetTitle("#phi-TuneP lower leg tag");
	h5->GetXaxis()->SetTitleSize(0.05);
	h5->GetXaxis()->SetTitleOffset(0.91);
	//h0->GetYaxis()->SetRangeUser(0,0.005);
	h5->GetYaxis()->SetTitleOffset(1.1);
	h5->GetYaxis()->SetTitleSize(0.05);*/
	h5->Draw("E0 SAME");       // Draw the ratio plot
	// No statistics on lower plot


	TLegend * leg0 = new TLegend(0.75, 0.56,0.98, 0.76);
	leg0->SetHeader("2016+2017 data");
	//leg0->SetHeader("MC total");

	leg0->SetFillColor(10);
	leg0->AddEntry(h0,"Global ");
	leg0->AddEntry(h1,"Tkonly");
	leg0->AddEntry(h2,"TPFMS ");
	leg0->AddEntry(h3,"Picky");
	leg0->AddEntry(h4,"DYT ");
	leg0->AddEntry(h5,"TuneP");

	leg0 -> Draw();

	/*TLatex t(1,0.01,"2016 data");
	  t.DrawClone("Same");*/

	/*TFile *fout = new TFile("testphi.root ","RECREATE");

	  phihistoGlb->Write();
	  phihistoStalone->Write();

	  fout->Close();*/

}// end of function 
