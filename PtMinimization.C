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


//you first decalre all the varaibles you are goingt o pick from the tree and use in this code. Be careful that the type of the varaible (Int, Float etc) have to be the same that when it was filled in the tree maker


//my interesting variables 
double weight;
double charge[2], chi2[2], ndof[2], strip_hits[2], pixel_hits[2], pixel_layers[2], strip_layers[2], muon_hits[2];
double pt[2], qoverp[2], theta[2], eta[2], phi[2], dxy[2], dz[2];
double error_pt[2], error_qoverp[2], error_theta[2], error_phi[2], error_dxy[2], error_dz[2];

double ref_charge, ref_chi2[2],ref_ndof[2], ref_pixel_hits[2], ref_strip_hits[2], ref_pixel_layers[2], ref_strip_layers[2], ref_muon_hits[2];
double ref_pt,ref_theta[2], ref_phi[2], ref_dxy[2], ref_dz[2];
double ref_error_pt[2], ref_error_theta[2], ref_error_phi[2], ref_error_dxy[2], ref_error_dz[2];

double mc_charge, mc_pt, mc_inv_pt, mc_qpt, mc_qinv_pt, mc_theta, mc_phi, mc_dxy, mc_dz, mc_eta;


int tmr_choice[2], pmc_choice[2];



//Declaration of hitsogramm i plan to plot with this code

TH1F *hist =new TH1F("test","",50,0,2000);
TH1F *ref_hist =new TH1F("ref_test","",50,0,2000);


//Begining of teh function
void PtMinimization(){

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
	treedata->SetBranchAddress("chi2",chi2);
	treedata->SetBranchAddress("strip_hits",strip_hits);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("pixel_layers",pixel_layers);
	treedata->SetBranchAddress("strip_layers",strip_layers);
	treedata->SetBranchAddress("muon_hits",muon_hits);
	treedata->SetBranchAddress("pt",pt);
	treedata->SetBranchAddress("qoverp",qoverp);
	treedata->SetBranchAddress("theta",theta);
	treedata->SetBranchAddress("phi",phi);
	treedata->SetBranchAddress("dxy",dxy);
	treedata->SetBranchAddress("dz",dz);
	treedata->SetBranchAddress("error_pt",error_pt);
	treedata->SetBranchAddress("error_theta",error_theta);
	treedata->SetBranchAddress("error_phi",error_phi);
	treedata->SetBranchAddress("error_dxy",error_dxy);
	treedata->SetBranchAddress("error_dz",error_dz);

	treedata->SetBranchAddress("ref_charge",&ref_charge);
	treedata->SetBranchAddress("ref_chi2",&ref_chi2);
	treedata->SetBranchAddress("ref_strip_hits",&ref_strip_hits);
	treedata->SetBranchAddress("ref_pixel_layers",&ref_pixel_layers);
	treedata->SetBranchAddress("ref_strip_layers",&ref_strip_layers);
	treedata->SetBranchAddress("ref_muon_hits",&ref_muon_hits);
	treedata->SetBranchAddress("ref_pt",&ref_pt);
	treedata->SetBranchAddress("ref_theta",&ref_theta);
	treedata->SetBranchAddress("ref_phi",&ref_phi);
	treedata->SetBranchAddress("ref_dxy",&ref_dxy);
	treedata->SetBranchAddress("ref_dz",&ref_dz);
	treedata->SetBranchAddress("ref_error_pt",&ref_error_pt);
	treedata->SetBranchAddress("ref_error_theta",&ref_error_theta);
	treedata->SetBranchAddress("ref_error_phi",&ref_error_phi);
	treedata->SetBranchAddress("ref_error_dxy",&ref_error_dxy);
	treedata->SetBranchAddress("ref_error_dz",&ref_error_dz);

	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();


	//Decalaration of variable not in the tree that i use for the results

	Float_t sameCharge = 0.;
	Float_t goodMuon = 0.;
	Float_t highPtMuon = 0.;

	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting

		//if (pt[1]>53. && pt[0]>53. && strip_layers[0]>=5 && strip_layers[1]>=5 && pixel_hits[0]>=1 && pixel_hits[1]>=1  ){

			for (int k=0; k<2 ;k++) {

				goodMuon++;

				//if (pt[k]>400.){ // this corresponds to select high pT muon, in my case i have ony two muons per event

					highPtMuon++;



					//if (charge[0]==charge[1]) {

						//sameCharge ++;
						hist->Fill(pt[k]);
						//ref_hist->Fill(ref_pt);

					//}



				//	}//end of condition on muon pT muon
			} //end loop on individual muon k


		//}//end of condition on event selection


	}// end loop p


	//cout<<"Same charge muon = "<<sameCharge<<endl;
	cout << "entries = "<<nentries<<endl;
	cout<<"goodmuon = "<<goodMuon<<endl;
	cout<<"highPtmuon = "<<highPtMuon<<endl;


	TCanvas *dytMass = new TCanvas("pickypT","",600,600);
	hist->SetXTitle("pT GeV");
	hist->SetLineColor(2);
	hist->SetLineWidth(2);
	hist->Draw("");
	//ref_hist->SetLineColor(3);
	//ref_hist->SetLineWidth(2);
	//ref_hist->Draw("");

/*	TLegend * leg1 = new TLegend(0.6, 0.65, 0.98, 0.82);
	leg1->SetFillColor(10);
	//leg1->AddEntry(hist,"pT of same muon charge ","l");
	leg1->AddEntry(hist,"track","l");
	leg1->AddEntry(ref_hist,"ref track ","l");

	leg1 -> Draw();
	*/
		


	TFile *fout = new TFile("testPt.root ","RECREATE");

	hist->Write();
	//ref_hist->Write();

	fout->Close();

}// end of function 
