#include "TFile.h"
#include <iostream>
#include <vector>
#include "TChain.h"
#include "TTree.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include <math.h>
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

float theta[n_tracks][n_track_pos];
short charge[n_tracks][n_track_pos];

float unprop_theta[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];

float unprop_pt[n_tracks][n_track_pos];

ushort pixel_hits[n_tracks][n_track_pos];

ushort strip_layers[n_tracks][n_track_pos];

float eta[n_tracks][n_track_pos];
////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code

/*TH1F *etahistoGlbUP =new TH1F("etahistoGlb","",20,-3,3);
  TH1F *etahistoGlbLOW =new TH1F("etahistoGlbLOW","",20,-3,3);

  TH1F *etahistoTkonlyUP =new TH1F("etahistoTkonly","",20,-3,3);
  TH1F *etahistoTkonlyLOW =new TH1F("etahistoTkonlyLOW","",20,-3,3);

  TH1F *etahistoTpfmsUP =new TH1F("etahistoTpfms","",20,-3,3);
  TH1F *etahistoTpfmsLOW =new TH1F("etahistoTpfmsLOW","",20,-3,3);

  TH1F *etahistoPickyUP =new TH1F("etahistoPicky","",20,-3,3);
  TH1F *etahistoPickyLOW =new TH1F("etahistoPickyLOW","",20,-3,3);

  TH1F *etahistoDYTUP =new TH1F("etahistoDYT","",20,-3,3);
  TH1F *etahistoDYTLOW =new TH1F("etahistoDYTLOW","",20,-3,3);

  TH1F *etahistoTunePUP =new TH1F("etahistoTuneP","",20,-3,3);
  TH1F *etahistoTunePLOW =new TH1F("etahistoTunePLOW","",20,-3,3);*/

TH1F *etahistoGlbUP =new TH1F("etahistoGlb","",2,-0.9,0.9);
TH1F *etahistoGlbLOW =new TH1F("etahistoGlbLOW","",2,-0.9,0.9);

TH1F *etahistoTkonlyUP =new TH1F("etahistoTkonly","",2,-0.9,0.9);
TH1F *etahistoTkonlyLOW =new TH1F("etahistoTkonlyLOW","",2,-0.9,0.9);

TH1F *etahistoTpfmsUP =new TH1F("etahistoTpfms","",2,-0.9,0.9);
TH1F *etahistoTpfmsLOW =new TH1F("etahistoTpfmsLOW","",2,-0.9,0.9);

TH1F *etahistoPickyUP =new TH1F("etahistoPicky","",2,-0.9,0.9);
TH1F *etahistoPickyLOW =new TH1F("etahistoPickyLOW","",2,-0.9,0.9);

TH1F *etahistoDYTUP =new TH1F("etahistoDYT","",2,-0.9,0.9);
TH1F *etahistoDYTLOW =new TH1F("etahistoDYTLOW","",2,-0.9,0.9);

TH1F *etahistoTunePUP =new TH1F("etahistoTuneP","",2,-0.9,0.9);
TH1F *etahistoTunePLOW =new TH1F("etahistoTunePLOW","",2,-0.9,0.9);

/*
								       TH1F *etahistoGlbUP =new TH1F("etahistoGlb","",1,-0.9,0.9);
								       TH1F *etahistoGlbLOW =new TH1F("etahistoGlbLOW","",1,-0.9,0.9);

								       TH1F *etahistoTkonlyUP =new TH1F("etahistoTkonly","",1,-0.9,0.9);
								       TH1F *etahistoTkonlyLOW =new TH1F("etahistoTkonlyLOW","",1,-0.9,0.9);

								       TH1F *etahistoTpfmsUP =new TH1F("etahistoTpfms","",1,-0.9,0.9);
								       TH1F *etahistoTpfmsLOW =new TH1F("etahistoTpfmsLOW","",1,-0.9,0.9);

								       TH1F *etahistoPickyUP =new TH1F("etahistoPicky","",1,-0.9,0.9);
								       TH1F *etahistoPickyLOW =new TH1F("etahistoPickyLOW","",1,-0.9,0.9);

								       TH1F *etahistoDYTUP =new TH1F("etahistoDYT","",1,-0.9,0.9);
								       TH1F *etahistoDYTLOW =new TH1F("etahistoDYTLOW","",1,-0.9,0.9);

								       TH1F *etahistoTunePUP =new TH1F("etahistoTuneP","",1,-0.9,0.9);
								       TH1F *etahistoTunePLOW =new TH1F("etahistoTunePLOW","",1,-0.9,0.9);*/


//Begining of teh function
void etaChargeMis(){


	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");
	//treedata->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilethetaon mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	treedata->SetBranchAddress("theta",theta);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_theta",unprop_theta);
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
		//Algorithm choice
		for (int i=0;i<n_tracks;i++){
			for (int j=0;j<n_track_pos;j++){
				eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
			}
		}

		//selection cuts
		
		// UPPER LEG TAG
 
 
  		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][0]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][0]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][0]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][0]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][0]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][0]>30.){
 
			//global
			etahistoGlbUP->Fill(eta[8][0]);
			if (charge[0][1]!=charge[8][0]){ 
				etahistoGlbLOW->Fill(eta[8][0]);
			}
			//Tkonly
			etahistoTkonlyUP->Fill(eta[8][0]);
			if (charge[2][1]!=charge[8][0]){ 
				etahistoTkonlyLOW->Fill(eta[8][0]);
			}
			//Tpfms
			etahistoTpfmsUP->Fill(eta[8][0]);
			if (charge[3][1]!=charge[8][0]){ 
				etahistoTpfmsLOW->Fill(eta[8][0]);
			}
			//Picky
			etahistoPickyUP->Fill(eta[8][0]);
			if (charge[4][1]!=charge[8][0]){ 
				etahistoPickyLOW->Fill(eta[8][0]);
			}
			//DYT
			etahistoDYTUP->Fill(eta[8][0]);
			if (charge[5][1]!=charge[8][0]){ 
				etahistoDYTLOW->Fill(eta[8][0]);
			}
			//TuneP
			etahistoTunePUP->Fill(eta[8][0]);
			if (charge[8][1]!=charge[8][0]){ 
				etahistoTunePLOW->Fill(eta[8][0]);
			}

 
                //LOWER LEG TAG
/*		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][1]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][1]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][1]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][1]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][1]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			//global
			etahistoGlbUP->Fill(eta[8][1]);
			if (charge[0][0]!=charge[8][1]){ 
				etahistoGlbLOW->Fill(eta[8][1]);
			}
			//Tkonly
			etahistoTkonlyUP->Fill(eta[8][1]);
			if (charge[2][0]!=charge[8][1]){ 
				etahistoTkonlyLOW->Fill(eta[8][1]);
			}
			//Tpfms
			etahistoTpfmsUP->Fill(eta[8][1]);
			if (charge[3][0]!=charge[8][1]){ 
				etahistoTpfmsLOW->Fill(eta[8][1]);
			}
			//Picky
			etahistoPickyUP->Fill(eta[8][1]);
			if (charge[4][0]!=charge[8][1]){ 
				etahistoPickyLOW->Fill(eta[8][1]);
			}
			//DYT
			etahistoDYTUP->Fill(eta[8][1]);
			if (charge[5][0]!=charge[8][1]){ 
				etahistoDYTLOW->Fill(eta[8][1]);
			}
			//TuneP
			etahistoTunePUP->Fill(eta[8][1]);
			if (charge[8][0]!=charge[8][1]){ 
				etahistoTunePLOW->Fill(eta[8][1]);
			}*/



					}
	}// end loop p


	// Define the Canvas
	TCanvas *c = new TCanvas("c", "canvas", 700,500);	
	//c->SetLogy();

	// Define the ratio plot
	TH1F *h0 = (TH1F*)etahistoGlbUP->Clone("h0");
	h0->SetLineColor(kBlack);
	h0->Sumw2();
	h0->SetStats(1111);      // No statistics on lower plot
	h0->Divide(etahistoGlbLOW,etahistoGlbUP ,1,1,"B");
	h0->SetMarkerStyle(21);
	h0->SetMarkerColor(kBlack);
	h0->Draw("E0");       // Draw the ratio plot
	// Y axis ratio plot settings
	h0->GetYaxis()->SetTitle("Prob. of misidentification");
	// X axis ratio plot settings
	h0->GetXaxis()->SetTitle("#eta-TuneP upper leg tag");
	//h0->GetXaxis()->SetTitle("#eta-TuneP lower leg tag");
	h0->GetXaxis()->SetTitleSize(0.05);
	h0->GetYaxis()->SetTitleSize(0.049);
	h0->GetXaxis()->SetTitleOffset(0.91);
	h0->GetYaxis()->SetTitleOffset(1.1);
	h0->GetYaxis()->SetRangeUser(0,0.006);
	float glbBin =  h0->GetBinContent(1);
	cout << "Charge rate - glb : " << glbBin << endl;

	TH1F *h1 = (TH1F*)etahistoTkonlyUP->Clone("h1");
	h1->SetLineColor(kRed);
	h1->Sumw2();
	h1->SetStats(0);      // No statistics on lower plot
	h1->Divide(etahistoTkonlyLOW,etahistoTkonlyUP ,1,1,"B");
	h1->SetMarkerStyle(22);
	h1->SetMarkerColor(kRed);
	float TkonlyBin =  h1->GetBinContent(1);
	cout << "Charge rate - Tkonly : " << TkonlyBin << endl;

	h1->Draw("E0 SAME");       // Draw the ratio plot

	TH1F *h2 = (TH1F*)etahistoTpfmsUP->Clone("h2");
	h2->SetLineColor(kOrange);
	h2->Sumw2();
	h2->SetStats(0);      // No statistics on lower plot
	h2->Divide(etahistoTpfmsLOW,etahistoTpfmsUP ,1,1,"B");
	h2->SetMarkerStyle(20);
	h2->SetMarkerColor(kOrange);
	float TpfmsBin =  h2->GetBinContent(1);
	cout << "Charge rate - TPFMS : " << TpfmsBin << endl;

	h2->Draw("E0 SAME");       // Draw the ratio plot



	TH1F *h3 = (TH1F*)etahistoPickyUP->Clone("h3");
	h3->SetLineColor(kMagenta);
	h3->Sumw2();
	h3->SetStats(0);      // No statistics on lower plot
	h3->Divide(etahistoPickyLOW,etahistoPickyUP ,1,1,"B");
	h3->SetMarkerStyle(23);
	h3->SetMarkerColor(kMagenta);
	float PickyBin =  h3->GetBinContent(1);
	cout << "Charge rate - Picky : " << PickyBin << endl;

	h3->Draw("E0 SAME");       // Draw the ratio plot


	// Define the ratio plot
	TH1F *h4 = (TH1F*)etahistoDYTUP->Clone("h4");
	h4->SetLineColor(kGreen);
	h4->Sumw2();
	h4->SetStats(0);      // No statistics on lower plot
	h4->Divide(etahistoDYTLOW,etahistoDYTUP ,1,1,"B");
	h4->SetMarkerStyle(24);
	h4->SetMarkerColor(kGreen);
	float DYTBin =  h4->GetBinContent(1);
	cout << "Charge rate - DYT : " << DYTBin << endl;

	h4->Draw("E0 SAME");       // Draw the ratio plot

	// Define the ratio plot
	TH1F *h5 = (TH1F*)etahistoTunePUP->Clone("h5");
	h5->SetLineColor(kBlue);
	h5->Sumw2();
	h5->SetMarkerColor(kBlue);

	h5->SetStats(1111);      // No statistics on lower plot
	h5->Divide(etahistoTunePLOW,etahistoTunePUP ,1,1,"B");
	h5->SetMarkerStyle(25);
	// Y axis ratio plot settings
	/*h5->GetYaxis()->SetTitle("Prob. of misidentification");
	// X axis ratio plot settings
	h5->GetXaxis()->SetTitle("#eta-TuneP lower leg tag");
	h5->GetXaxis()->SetTitleSize(0.05);
	h5->GetYaxis()->SetTitleSize(0.049);
	h5->GetXaxis()->SetTitleOffset(0.91);
	h5->GetYaxis()->SetTitleOffset(1.1);*/

	h5->Draw("E0 SAME");       // Draw the ratio plot
	// No statistics on lower plot
	float TunePBin =  h5->GetBinContent(1);
	cout << "Charge rate - TuneP : " << TunePBin << endl;


	TLegend * leg0 = new TLegend(0.75, 0.56, 0.98, 0.76);
	//leg0->SetHeader("MC total");
	leg0->SetHeader("2016+2017 data");

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

	/*TFile *fout = new TFile("testtheta.root ","RECREATE");

	  thetahistoGlb->Write();
	  thetahistoStalone->Write();

	  fout->Close();*/

}// end of function 
