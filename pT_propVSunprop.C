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

float unprop_pt[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];



////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code

TH1F *pthistoGlbUP =new TH1F("pthistoGlbProp","",20,0,800);
TH1F *pthistoGlbLOW =new TH1F("pthistoGlbUnprop","",20,0,800);

//TH1F *pthistoStalone =new TH1F("pthistoStalone","",10,30,800);
TH1F *pthistoTkonlyUP =new TH1F("pthistoTkonlyProp","",20,0,800);
TH1F *pthistoTkonlyLOW =new TH1F("pthistoTkonlyLOW","",20,0,800);

TH1F *pthistoTpfmsUP =new TH1F("pthistoTpfmsProp","",20,0,800);
TH1F *pthistoTpfmsLOW =new TH1F("pthistoTpfmsLOW","",20,0,800);

TH1F *pthistoPickyUP =new TH1F("pthistoPickyProp","",20,0,800);
TH1F *pthistoPickyLOW =new TH1F("pthistoPickyLOW","",20,0,800);

TH1F *pthistoDYTUP =new TH1F("pthistoDYTProp","",20,0,800);
TH1F *pthistoDYTLOW =new TH1F("pthistoDYTLOW","",20,0,800);

//TH1F *ptRef=new TH1F("ptRef","",100,0,640);
//TH1F *ptTuneP = new TH1F("ptTuneP","",100,0,640);

//Begining of teh function
void pT_propVSunprop(){

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
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);

	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	//Decalaration of variable not in the tree that i use for the results

	Float_t sameCharge = 0.;
	Float_t goodMuon = 0.;
	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting

		pthistoGlbUP->Fill(pt[0][1]);
		pthistoGlbLOW->Fill(unprop_pt[0][1]);
		pthistoTkonlyUP->Fill(pt[2][1]);
		pthistoTkonlyLOW->Fill(unprop_pt[2][1]);
		pthistoTpfmsUP->Fill(pt[3][1]);
		pthistoTpfmsLOW->Fill(unprop_pt[3][1]);
		pthistoPickyUP->Fill(pt[4][1]);
		pthistoPickyLOW->Fill(unprop_pt[4][1]);
		pthistoDYTUP->Fill(pt[5][1]);
		pthistoDYTLOW->Fill(unprop_pt[5][1]);


	}// end loop p


	
	TCanvas *c1 = new TCanvas("c1","",1400,900);
	c1->Divide(3,2);
	c1->cd(1);

	pthistoGlbUP->SetXTitle("#p_{t} (GeV)");
	pthistoGlbLOW->SetLineColor(8);
	pthistoGlbLOW->SetLineWidth(2);
	pthistoGlbLOW->Draw("E1");
	pthistoGlbUP->SetLineColor(2);
	pthistoGlbUP->SetLineWidth(2);
	pthistoGlbUP->Draw("E1 SAME");
	
	TLegend * leg1 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg1->SetHeader("Global fit - lower leg");
	leg1->SetFillColor(10);
	leg1->AddEntry(pthistoGlbUP,"Propagated ","l");
	leg1->AddEntry(pthistoGlbLOW,"Unpropagated","l");
	leg1 -> Draw();
	//TLatex t(0.2,270,"Unpropagated values");
	//t.DrawClone("Same");

	c1->cd(2);
	pthistoTkonlyUP->SetXTitle("#pt");
	pthistoTkonlyUP->SetLineColor(2);
	pthistoTkonlyUP->SetLineWidth(2);
	pthistoTkonlyUP->Draw("E1");
	pthistoTkonlyLOW->SetLineColor(8);
	pthistoTkonlyLOW->SetLineWidth(2);
	pthistoTkonlyLOW->Draw("E1 SAME");

	TLegend * leg2 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg2->SetHeader("Tracker only - lower leg");
	leg2->SetFillColor(10);
	leg2->AddEntry(pthistoTkonlyUP,"Propagated ","l");
	leg2->AddEntry(pthistoTkonlyLOW,"Unpropagated","l");
	leg2 -> Draw();
	//TLatex t2(0.2,270,"Unpropagated values");
	//t2.DrawClone("Same");

	c1->cd(3);
	pthistoTpfmsUP->SetXTitle("#pt");
	pthistoTpfmsUP->SetLineColor(2);
	pthistoTpfmsUP->SetLineWidth(2);
	pthistoTpfmsUP->Draw("E1");
	pthistoTpfmsLOW->SetLineColor(8);
	pthistoTpfmsLOW->SetLineWidth(2);
	pthistoTpfmsLOW->Draw("E1 SAME");

	TLegend * leg3 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg3->SetHeader("TPFMS - lower leg");
	leg3->SetFillColor(10);
	leg3->AddEntry(pthistoTpfmsUP,"Propagated","l");
	leg3->AddEntry(pthistoTpfmsLOW,"Unpropagated","l");
	leg3 -> Draw();
	//TLatex t3(0.2,270,"Unpropagated values");
	//t3.DrawClone("Same");

	c1->cd(4);
	pthistoPickyUP->SetXTitle("#pt");
	pthistoPickyUP->SetLineColor(2);
	pthistoPickyUP->SetLineWidth(2);
	pthistoPickyUP->Draw("E1");
	pthistoPickyLOW->SetLineColor(8);
	pthistoPickyLOW->SetLineWidth(2);
	pthistoPickyLOW->Draw("E1 SAME");

	TLegend * leg4 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg4->SetHeader("Picky - lower leg");
	leg4->SetFillColor(10);
	leg4->AddEntry(pthistoPickyUP,"Propagated ","l");
	leg4->AddEntry(pthistoPickyLOW,"Unpropagated","l");
	leg4-> Draw();
	//TLatex t4(0.2,270,"Unpropagated values");
	//t4.DrawClone("Same");

	c1->cd(5);
	pthistoDYTUP->SetXTitle("#pt");
	pthistoDYTUP->SetLineColor(2);
	pthistoDYTUP->SetLineWidth(2);
	pthistoDYTUP->Draw("E1");
	pthistoDYTLOW->SetLineColor(8);
	pthistoDYTLOW->SetLineWidth(2);
	pthistoDYTLOW->Draw("E1 SAME");


	TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg5->SetHeader("DYT - lower leg");
	leg5->SetFillColor(10);
	leg5->AddEntry(pthistoDYTUP,"Propagated ","l");
	leg5->AddEntry(pthistoDYTLOW,"Unpropagated","l");
	leg5 -> Draw();
	//TLatex t5(0.2,270,"Unpropagated values");
	//t5.DrawClone("Same");



	/*TFile *fout = new TFile("testpt.root ","RECREATE");

	pthistoGlb->Write();
	pthistoStalone->Write();

	fout->Close();*/

}// end of function 
