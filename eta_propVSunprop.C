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

float eta[n_tracks][n_track_pos];
short charge[n_tracks][n_track_pos];

float unprop_eta[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];



////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code

TH1F *etahistoGlbUP =new TH1F("etahistoGlbProp","",30,-3,3);
TH1F *etahistoGlbLOW =new TH1F("etahistoGlbUnprop","",30,-3,3);

//TH1F *etahistoStalone =new TH1F("etahistoStalone","",10,30,800);
TH1F *etahistoTkonlyUP =new TH1F("etahistoTkonlyProp","",30,-3,3);
TH1F *etahistoTkonlyLOW =new TH1F("etahistoTkonlyLOW","",30,-3,3);

TH1F *etahistoTpfmsUP =new TH1F("etahistoTpfmsProp","",30,-3,3);
TH1F *etahistoTpfmsLOW =new TH1F("etahistoTpfmsLOW","",30,-3,3);

TH1F *etahistoPickyUP =new TH1F("etahistoPickyProp","",30,-3,3);
TH1F *etahistoPickyLOW =new TH1F("etahistoPickyLOW","",30,-3,3);

TH1F *etahistoDYTUP =new TH1F("etahistoDYTProp","",30,-3,3);
TH1F *etahistoDYTLOW =new TH1F("etahistoDYTLOW","",30,-3,3);

//TH1F *etaRef=new TH1F("etaRef","",100,0,640);
//TH1F *etaTuneP = new TH1F("etaTuneP","",100,0,640);

//Begining of teh function
void eta_propVSunprop(){

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

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dileetaon mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	treedata->SetBranchAddress("eta",eta);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_eta",unprop_eta);

	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	//Decalaration of variable not in the tree that i use for the results

	Float_t sameCharge = 0.;
	Float_t goodMuon = 0.;
	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting

		etahistoGlbUP->Fill(eta[0][1]);
		etahistoGlbLOW->Fill(unprop_eta[0][1]);
		etahistoTkonlyUP->Fill(eta[2][1]);
		etahistoTkonlyLOW->Fill(unprop_eta[2][1]);
		etahistoTpfmsUP->Fill(eta[3][1]);
		etahistoTpfmsLOW->Fill(unprop_eta[3][1]);
		etahistoPickyUP->Fill(eta[4][1]);
		etahistoPickyLOW->Fill(unprop_eta[4][1]);
		etahistoDYTUP->Fill(eta[5][1]);
		etahistoDYTLOW->Fill(unprop_eta[5][1]);


	}// end loop p


	
	TCanvas *c1 = new TCanvas("c1","",1400,900);
	c1->Divide(3,2);
	c1->cd(1);

	etahistoGlbUP->SetXTitle("#eta");
	etahistoGlbLOW->SetLineColor(8);
	etahistoGlbLOW->SetLineWidth(2);
	etahistoGlbLOW->Draw("E1");
	etahistoGlbUP->SetLineColor(2);
	etahistoGlbUP->SetLineWidth(2);
	etahistoGlbUP->Draw("E1 SAME");
	
	TLegend * leg1 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg1->SetHeader("Global fit - lower leg");
	leg1->SetFillColor(10);
	leg1->AddEntry(etahistoGlbUP,"Propagated ","l");
	leg1->AddEntry(etahistoGlbLOW,"Unpropagated","l");
	leg1 -> Draw();
	//TLatex t(0.2,270,"Unpropagated values");
	//t.DrawClone("Same");

	c1->cd(2);
	etahistoTkonlyUP->SetXTitle("#eta");
	etahistoTkonlyUP->SetLineColor(2);
	etahistoTkonlyUP->SetLineWidth(2);
	etahistoTkonlyUP->Draw("E1");
	etahistoTkonlyLOW->SetLineColor(8);
	etahistoTkonlyLOW->SetLineWidth(2);
	etahistoTkonlyLOW->Draw("E1 SAME");

	TLegend * leg2 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg2->SetHeader("Tracker only - lower leg");
	leg2->SetFillColor(10);
	leg2->AddEntry(etahistoTkonlyUP,"Propagated ","l");
	leg2->AddEntry(etahistoTkonlyLOW,"Unpropagated","l");
	leg2 -> Draw();
	//TLatex t2(0.2,270,"Unpropagated values");
	//t2.DrawClone("Same");

	c1->cd(3);
	etahistoTpfmsUP->SetXTitle("#eta");
	etahistoTpfmsUP->SetLineColor(2);
	etahistoTpfmsUP->SetLineWidth(2);
	etahistoTpfmsUP->Draw("E1");
	etahistoTpfmsLOW->SetLineColor(8);
	etahistoTpfmsLOW->SetLineWidth(2);
	etahistoTpfmsLOW->Draw("E1 SAME");

	TLegend * leg3 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg3->SetHeader("TPFMS - lower leg");
	leg3->SetFillColor(10);
	leg3->AddEntry(etahistoTpfmsUP,"Propagated","l");
	leg3->AddEntry(etahistoTpfmsLOW,"Unpropagated","l");
	leg3 -> Draw();
	//TLatex t3(0.2,270,"Unpropagated values");
	//t3.DrawClone("Same");

	c1->cd(4);
	etahistoPickyUP->SetXTitle("#eta");
	etahistoPickyUP->SetLineColor(2);
	etahistoPickyUP->SetLineWidth(2);
	etahistoPickyUP->Draw("E1");
	etahistoPickyLOW->SetLineColor(8);
	etahistoPickyLOW->SetLineWidth(2);
	etahistoPickyLOW->Draw("E1 SAME");

	TLegend * leg4 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg4->SetHeader("Picky - lower leg");
	leg4->SetFillColor(10);
	leg4->AddEntry(etahistoPickyUP,"Propagated ","l");
	leg4->AddEntry(etahistoPickyLOW,"Unpropagated","l");
	leg4-> Draw();
	//TLatex t4(0.2,270,"Unpropagated values");
	//t4.DrawClone("Same");

	c1->cd(5);
	etahistoDYTUP->SetXTitle("#eta");
	etahistoDYTUP->SetLineColor(2);
	etahistoDYTUP->SetLineWidth(2);
	etahistoDYTUP->Draw("E1");
	etahistoDYTLOW->SetLineColor(8);
	etahistoDYTLOW->SetLineWidth(2);
	etahistoDYTLOW->Draw("E1 SAME");


	TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg5->SetHeader("DYT - lower leg");
	leg5->SetFillColor(10);
	leg5->AddEntry(etahistoDYTUP,"Propagated ","l");
	leg5->AddEntry(etahistoDYTLOW,"Unpropagated","l");
	leg5 -> Draw();
	//TLatex t5(0.2,270,"Unpropagated values");
	//t5.DrawClone("Same");



	/*TFile *fout = new TFile("testeta.root ","RECREATE");

	etahistoGlb->Write();
	etahistoStalone->Write();

	fout->Close();*/

}// end of function 
