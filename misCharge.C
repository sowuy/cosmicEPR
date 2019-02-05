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
#include "../../plugins/CosmicSplittingResolutionNtuple.h"


//you first decalre all the varaibles you are goingt o pick from the tree and use in this code. Be careful that the type of the varaible (Int, Float etc) have to be the same that when it was filled in the tree maker


//my interesting variables 

float pt[n_tracks][n_track_pos];
short charge[n_tracks][n_track_pos];
float eta[n_tracks][n_track_pos];
float unprop_pt[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];
float unprop_eta[n_tracks][n_track_pos];

short ref_charge;
float ref_pt;
float ref_eta;


int track;      



////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code


TH1F *tag_charges_agree = new TH1F("tag_charges_agree","",20,0,800);
TH1F *tag_charges_agree_but_not_with_probe = new TH1F("tag_charges_agree_but_not_with_probe","",20,0,800);
TH1F *probe_charge_misid_prob = new TH1F("probe_charge_misid_prob","",20,0,800);

//m=binomial_divide(
//Begining of teh function
void misCharge(){

	gStyle->SetPadBorderMode(0);
	gStyle->SetCanvasColor(10);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasBorderSize(0);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetFrameLineColor(0);
	gStyle->SetFillColor(0);

	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	treedata->Add("resolution_cosmics_data.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilepton mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	treedata->SetBranchAddress("pt",pt);
	treedata->SetBranchAddress("eta",eta);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);
	treedata->SetBranchAddress("unprop_eta",eta);

	treedata->SetBranchAddress("ref_charge",&ref_charge);
	treedata->SetBranchAddress("ref_pt",&ref_pt);
	treedata->SetBranchAddress("ref_eta",&ref_eta);

	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	//Decalaration of variable not in the tree that i use for the results

	/*Je cr√e un histogramme qui montre le nombre d'√v√nmenents qui comportent une mauvaise identification de la charge par rapport a lower leg pour chaque algorithme de tuneP*/

	int numberOfGoodTag=0;
	int numberOfMisCharge=0;


	for ( int p=0; p<nentries ;p++){

		//ma condition de "goodtag" = tag events if tkonly, global and tpfms charges agree

		if (unprop_charge[2][1]==unprop_charge[0][1] && unprop_charge[2][1]==unprop_charge[3][1]){
			numberOfGoodTag++;

			tag_charges_agree->Fill(unprop_pt[2][1]);

			//Example with algorithme global
			if (unprop_charge[5][0] != unprop_charge[2][1]){
				numberOfMisCharge++;
				tag_charges_agree_but_not_with_probe->Fill(unprop_pt[2][1]);
			}


		}




	}// end loop p

	cout << "numberOfGoodTag = " << numberOfGoodTag <<endl;
	cout << "numberOfMischarge = " << numberOfMisCharge <<endl;


	TCanvas *c1 = new TCanvas("c1","",900,600);
	c1->Divide(2,1);
	c1->cd(1);
	tag_charges_agree->SetTitle("Tagged charges agree");
	tag_charges_agree->SetXTitle("tag tracker-only p_{T} (GeV)");
	tag_charges_agree->SetLineColor(2);
	tag_charges_agree->SetLineWidth(2);
	tag_charges_agree->Draw("E1");

	TLegend * leg1 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg1->SetFillColor(10);
	leg1->AddEntry(tag_charges_agree,"Tagged events ","l");

	leg1 -> Draw();

	c1->cd(2);
	tag_charges_agree_but_not_with_probe->SetTitle("Tagged events where probe disagrees");
	tag_charges_agree_but_not_with_probe->SetXTitle("tag tracker-only p_{T} (GeV)");
	tag_charges_agree_but_not_with_probe->SetLineColor(2);
	tag_charges_agree_but_not_with_probe->SetLineWidth(2);
	tag_charges_agree_but_not_with_probe->Draw("E1");


	TLegend * leg2 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg2->SetHeader("Algorithms");
	leg2->SetFillColor(10);
	leg2->AddEntry(tag_charges_agree_but_not_with_probe,"Global fit ","l");
	leg2 -> Draw();


	/*c1->cd(3);
	*/


	/*TFile *fout = new TFile("testPt.root ","RECREATE");

	  pThistoGlb->Write();
	  pThistoStalone->Write();

	  fout->Close();*/

}// end of function 
