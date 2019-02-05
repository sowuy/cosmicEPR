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
#include "TText.h"
#include "TAttText.h"
#include "TLatex.h"
#include <cstring>
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

////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code
//Bin declaration for MC
float MCbins[]={50,100,200,300,400,600,1000,2000};

int MCbinnum = 7;
//Bin declaration for MC
float bins[]={50,100,200,400,1000,2000};

int binnum = 5;

//(pT_up-pT_low) for events with wrong charge

TH1F *hdiffPt_Glb =new TH1F("hdiffPt_Glb","",binnum,bins);
TH1F *hdiffPt_Tkonly =new TH1F("hdiffPt_Tkonly","",binnum,bins);
TH1F *hdiffPt_Tpfms =new TH1F("hdiffPt_Tpfms","",binnum,bins);
TH1F *hdiffPt_Picky =new TH1F("hdiffPt_Picky","",binnum,bins);
TH1F *hdiffPt_DYT =new TH1F("hdiffPt_DYT","",binnum,bins);
TH1F *hdiffPt_TuneP =new TH1F("hdiffPt_TuneP","",binnum,bins);


//Charge confusion rate - data
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
//Charge confusion rate - MC 
/*TH1F *pthistoGlbUP =new TH1F("pthistoGlb","",MCbinnum,MCbins);
TH1F *pthistoGlbLOW =new TH1F("pthistoGlbLOW","",MCbinnum,MCbins);

TH1F *pthistoTkonlyUP =new TH1F("pthistoTkonly","",MCbinnum,MCbins);
TH1F *pthistoTkonlyLOW =new TH1F("pthistoTkonlyLOW","",MCbinnum,MCbins);

TH1F *pthistoTpfmsUP =new TH1F("pthistoTpfms","",MCbinnum,MCbins);
TH1F *pthistoTpfmsLOW =new TH1F("pthistoTpfmsLOW","",MCbinnum,MCbins);

TH1F *pthistoPickyUP =new TH1F("pthistoPicky","",MCbinnum,MCbins);
TH1F *pthistoPickyLOW =new TH1F("pthistoPickyLOW","",MCbinnum,MCbins);

TH1F *pthistoDYTUP =new TH1F("pthistoDYT","",MCbinnum,MCbins);
TH1F *pthistoDYTLOW =new TH1F("pthistoDYTLOW","",MCbinnum,MCbins);

TH1F *pthistoTunePUP =new TH1F("pthistoTuneP","",MCbinnum,MCbins);
TH1F *pthistoTunePLOW =new TH1F("pthistoTunePLOW","",MCbinnum,MCbins);*/

//Charge confusion rate
/*TH1F *pthistoGlbUP =new TH1F("pthistoGlb","",1,10,2000);
TH1F *pthistoGlbLOW =new TH1F("pthistoGlbLOW","",1,10,2000);

TH1F *pthistoTkonlyUP =new TH1F("pthistoTkonly","",1,10,2000);
TH1F *pthistoTkonlyLOW =new TH1F("pthistoTkonlyLOW","",1,10,2000);

TH1F *pthistoTpfmsUP =new TH1F("pthistoTpfms","",1,10,2000);
TH1F *pthistoTpfmsLOW =new TH1F("pthistoTpfmsLOW","",1,10,2000);

TH1F *pthistoPickyUP =new TH1F("pthistoPicky","",1,10,2000);
TH1F *pthistoPickyLOW =new TH1F("pthistoPickyLOW","",1,10,2000);

TH1F *pthistoDYTUP =new TH1F("pthistoDYT","",1,10,2000);
TH1F *pthistoDYTLOW =new TH1F("pthistoDYTLOW","",1,10,2000);

TH1F *pthistoTunePUP =new TH1F("pthistoTuneP","",1,10,2000);
TH1F *pthistoTunePLOW =new TH1F("pthistoTunePLOW","",1,10,2000);*/

//Begining of teh function
void pTChargeMis(string algo=""){


	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	//treedata->Add("ROOT_Files/MC2016/MC_P10.root");
	//treedata->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");
	treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");


	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilepton mass in my case for DY events.
	treedata->SetBranchAddress("charge",charge);
	treedata->SetBranchAddress("pt",pt);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("strip_layers",strip_layers);

	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();

	//Decalaration of variable not in the tree that i use for the results

	Float_t wrongCharge_Glb = 0.;
	Float_t wrongCharge_Tkonly = 0.;
	Float_t wrongCharge_TPFMS = 0.;
	Float_t wrongCharge_Picky = 0.;
	Float_t wrongCharge_DYT = 0.;
	Float_t wrongCharge_TuneP = 0.;

	int algoNum=0;
	string titleX = string("p_{t} [GeV]-")+algo+ string(" lower leg tag");
	string titleDiff = string("(Pt_{up}-Pt_{low}) [GeV]-"+algo+ " tag");
	string title = algo+ string(" lower leg tag");

	string a= "coucou";
	if (algo == "Glb") algoNum=0;
	if (algo == "Tkonly") algoNum=2;
	if (algo == "TPFMS") algoNum=3;
	if (algo == "Picky") algoNum=4;
	if (algo == "DYT") algoNum=5;
	if (algo == "TuneP")  algoNum=8;


	Float_t diffPt_Glb = 0.;
	Float_t diffPt_Tkonly = 0.;
	Float_t diffPt_TPFMS = 0.;
	Float_t diffPt_Picky = 0.;
	Float_t diffPt_DYT = 0.;
	Float_t diffPt_TuneP = 0.;






	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//
		//
		//selection cuts - LOWER LEG TAG
/*if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][1]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][1]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][1]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][1]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][1]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

		
			//Algorithm choice

			//global
			pthistoGlbUP->Fill(unprop_pt[algoNum][1]);
			if (charge[0][0]!=charge[algoNum][1]){ 
				diffPt_Glb=(unprop_pt[0][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Glb->Fill(diffPt_Glb);
				pthistoGlbLOW->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Glb++;
			}
			//Tkonly
			pthistoTkonlyUP->Fill(unprop_pt[algoNum][1]);
			if (charge[2][0]!=charge[algoNum][1]){ 
				diffPt_Tkonly=(unprop_pt[2][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Tkonly->Fill(diffPt_Tkonly);
				pthistoTkonlyLOW->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Tkonly++;

			}
			//Tpfms
			pthistoTpfmsUP->Fill(unprop_pt[algoNum][1]);
			if (charge[3][0]!=charge[algoNum][1]){ 
				diffPt_Tpfms=(unprop_pt[3][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Tpfms->Fill(diffPt_TPFMS);
				pthistoTpfmsLOW->Fill(unprop_pt[algoNum][1]);
				wrongCharge_TPFMS++;

			}
			//Picky
			pthistoPickyUP->Fill(unprop_pt[algoNum][1]);
			if (charge[4][0]!=charge[algoNum][1]){ 
				diffPt_Picky=(unprop_pt[4][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Picky->Fill(diffPt_Picky);
				pthistoPickyLOW->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Picky++;

			}
			//DYT
			pthistoDYTUP->Fill(unprop_pt[algoNum][1]);
			if (charge[5][0]!=charge[algoNum][1]){ 
				diffPt_DYT=(unprop_pt[5][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_DYT->Fill(diffPt_DYT);
				pthistoDYTLOW->Fill(unprop_pt[algoNum][1]);
				wrongCharge_DYT++;

			}
			//TuneP
			pthistoTunePUP->Fill(unprop_pt[algoNum][1]);
			if (charge[8][0]!=charge[algoNum][1]){ 
				diffPt_TuneP=(unprop_pt[8][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_TuneP->Fill(diffPt_TuneP);
				pthistoTunePLOW->Fill(unprop_pt[algoNum][1]);
				wrongCharge_TuneP++;
			}*/


			//selection cuts - UPPER LEG TAG
			if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][0]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][0]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][0]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][0]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][0]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][0]>30.){

		
			//Algorithm choice

			//global
			pthistoGlbUP->Fill(unprop_pt[algoNum][0]);
			if (charge[0][1]!=charge[algoNum][0]){ 
				diffPt_Glb=(unprop_pt[0][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Glb->Fill(diffPt_Glb);
				pthistoGlbLOW->Fill(unprop_pt[algoNum][0]);
				wrongCharge_Glb++;
			}
			//Tkonly
			pthistoTkonlyUP->Fill(unprop_pt[algoNum][0]);
			if (charge[2][1]!=charge[algoNum][0]){ 
				diffPt_Tkonly=(unprop_pt[2][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Tkonly->Fill(diffPt_Tkonly);
				pthistoTkonlyLOW->Fill(unprop_pt[algoNum][0]);
				wrongCharge_Tkonly++;

			}
			//Tpfms
			pthistoTpfmsUP->Fill(unprop_pt[algoNum][0]);
			if (charge[3][1]!=charge[algoNum][0]){ 
				diffPt_Tpfms=(unprop_pt[3][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Tpfms->Fill(diffPt_TPFMS);
				pthistoTpfmsLOW->Fill(unprop_pt[algoNum][0]);
				wrongCharge_TPFMS++;

			}
			//Picky
			pthistoPickyUP->Fill(unprop_pt[algoNum][0]);
			if (charge[4][1]!=charge[algoNum][0]){ 
				diffPt_Picky=(unprop_pt[4][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_Picky->Fill(diffPt_Picky);
				pthistoPickyLOW->Fill(unprop_pt[algoNum][0]);
				wrongCharge_Picky++;

			}
			//DYT
			pthistoDYTUP->Fill(unprop_pt[algoNum][0]);
			if (charge[5][1]!=charge[algoNum][0]){ 
				diffPt_DYT=(unprop_pt[5][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_DYT->Fill(diffPt_DYT);
				pthistoDYTLOW->Fill(unprop_pt[algoNum][0]);
				wrongCharge_DYT++;

			}
			//TuneP
			pthistoTunePUP->Fill(unprop_pt[algoNum][0]);
			if (charge[8][1]!=charge[algoNum][0]){ 
				diffPt_TuneP=(unprop_pt[8][0]-unprop_pt[algoNum][1])/unprop_pt[algoNum][1];
				hdiffPt_TuneP->Fill(diffPt_TuneP);
				pthistoTunePLOW->Fill(unprop_pt[algoNum][0]);
				wrongCharge_TuneP++;
			}

		}
	}// end loop p
	/*cout << "Tag given by " << algo << "lower leg" << endl;
	  cout << "Events with wrong charge for the 6 algorithms :" << endl;
	  cout << "Global wrong charge = " << wrongCharge_Glb << endl;
	  cout << "Tkonly wrong charge = " << wrongCharge_Tkonly << endl;
	  cout << "TPFMS wrong charge = " << wrongCharge_TPFMS << endl;
	  cout << "Picky wrong charge = " << wrongCharge_Picky << endl;
	  cout << "DYT wrong charge = " << wrongCharge_DYT << endl;
	  cout << "TuneP wrong charge = " << wrongCharge_TuneP << endl;*/

	Float_t wrongCharge[6] = {wrongCharge_Glb,wrongCharge_Tkonly,wrongCharge_TPFMS,wrongCharge_Picky,wrongCharge_DYT,wrongCharge_TuneP};
	// Define the Canvas
	TCanvas *c = new TCanvas("c", "canvas", 700,550);
 //c->SetLogy();

	//Define the difference plot (pT_up-pT_low) for events with wrong charge reconstructed


	  /*hdiffPt_Glb->Draw("E0");
	  hdiffPt_Glb->SetMarkerStyle(21);
	  hdiffPt_Glb->SetMarkerColor(kBlack);
	  hdiffPt_Glb->SetLineColor(kBlack);
	  hdiffPt_Glb->GetYaxis()->SetTitleOffset(1.2);
	  hdiffPt_Glb->Draw("E0");       // Draw the ratio plot
	  hdiffPt_Glb->SetStats(0);
	// Y axis ratio plot settings
	hdiffPt_Glb->GetYaxis()->SetTitle("");
	// X axis ratio plot settings
	hdiffPt_Glb->GetXaxis()->SetTitleSize(0.05);
	hdiffPt_Glb->GetXaxis()->SetTitle(titleDiff.c_str());
	hdiffPt_Glb->GetXaxis()->SetTitleOffset(0.91);
	hdiffPt_Glb->GetYaxis()->SetTitleSize(0.05);
	hdiffPt_Glb->GetYaxis()->SetTitleOffset(0.95);
	//hdiffPt_Glb->GetYaxis()->SetRangeUser(0,8);

	hdiffPt_Tkonly->Draw("E0 SAME");
	hdiffPt_Tkonly->SetMarkerStyle(22);
	hdiffPt_Tkonly->SetLineColor(kRed);
	hdiffPt_Tkonly->SetStats(0);      // No statistics on lower plot
	hdiffPt_Tkonly->SetMarkerColor(kRed);

	hdiffPt_Tpfms->Draw("E0 SAME");
	hdiffPt_Tpfms->SetMarkerStyle(20);
	hdiffPt_Tpfms->SetLineColor(kOrange);
	hdiffPt_Tpfms->SetStats(0);      // No statistics on lower plot
	hdiffPt_Tpfms->SetMarkerColor(kOrange);

	hdiffPt_Picky->Draw("E0 SAME");
	hdiffPt_Picky->SetMarkerStyle(23);
	hdiffPt_Picky->SetLineColor(kMagenta);
	hdiffPt_Picky->SetStats(0);      // No statistics on lower plot
	hdiffPt_Picky->SetMarkerColor(kMagenta);


	hdiffPt_DYT->Draw("E0 SAME");
	hdiffPt_DYT->SetMarkerStyle(24);
	hdiffPt_DYT->SetLineColor(kGreen);
	hdiffPt_DYT->SetStats(0);      // No statistics on lower plot
	hdiffPt_DYT->SetMarkerColor(kGreen);


	hdiffPt_TuneP->Draw("E0 SAME");
	hdiffPt_TuneP->SetMarkerStyle(25);
	hdiffPt_TuneP->SetLineColor(kBlue);
	hdiffPt_TuneP->SetMarkerColor(kBlue);
	hdiffPt_TuneP->SetStats(0);      // No statistics on lower plot

	TLegend * leg0 = new TLegend(0.6, 0.70, 0.95, 0.95);
	leg0->SetHeader("MCP100");
	leg0->SetFillColor(10);
	leg0->AddEntry(hdiffPt_Glb,"Global ");
	leg0->AddEntry(hdiffPt_Tkonly,"Tkonly");
	leg0->AddEntry(hdiffPt_Tpfms,"TPFMS ");
	leg0->AddEntry(hdiffPt_Picky,"Picky");
	leg0->AddEntry(hdiffPt_DYT,"DYT ");
	leg0->AddEntry(hdiffPt_TuneP,"TuneP");

	leg0 -> Draw();*/

	// Define the ratio plot
	//
	//
	//TuneP
	//
	// Define the ratio plot
	TH1F *h5 = (TH1F*)pthistoTunePUP->Clone("h5");
	h5->SetLineColor(kBlue);
	h5->Sumw2();
	h5->SetMarkerColor(kBlue);
	
	h5->SetStats(11111);      // No statistics on lower plot
	h5->Divide(pthistoTunePLOW,pthistoTunePUP ,1,1,"B");


	h5->SetMarkerStyle(25);
	h5->Draw("E0 SAME");       // Draw the ratio plot
	// No statistics on lower plot
	h5->GetYaxis()->SetTitle("Prob. of misidentification");
	// X axis ratio plot settings
	h5->GetXaxis()->SetTitleSize(0.05);
	h5->GetXaxis()->SetTitle(titleX.c_str());
	h5->GetXaxis()->SetTitleOffset(0.91);
	h5->GetYaxis()->SetTitleSize(0.05);
	h5->GetYaxis()->SetTitleOffset(1.1);
	//h5->GetYaxis()->SetRangeUser(0,0.018);
	h5->GetXaxis()->SetTitle("Pt-TuneP upper leg tag");
	//h5->GetXaxis()->SetTitle("Pt-TuneP lower leg tag");

	float TunePBin =  h5->GetBinContent(1);
	cout << "Charge rate - TuneP : " << TunePBin << endl;


	TLegend * leg0 = new TLegend(0.75, 0.56, 0.98, 0.76);
	//leg0->SetHeader("MC total");
	leg0->SetHeader("2016+2017 data");
	leg0->SetFillColor(10);
	leg0->AddEntry(h5,"TuneP");

	leg0 -> Draw();
	/*TH1F *h0 = (TH1F*)pthistoGlbUP->Clone("h0");
	h0->SetLineColor(kBlack);
	h0->Sumw2();
	h0->SetStats(111111);      // No statistics on lower plot
	h0->Divide(pthistoGlbLOW,pthistoGlbUP ,1,1,"B");
	h0->SetMarkerStyle(21);
	h0->SetMarkerColor(kBlack);
	//h0->GetYaxis()->SetTitleOffset(1.2);
	h0->Draw("E0");       // Draw the ratio plot
	// Y axis ratio plot settings
	h0->GetYaxis()->SetTitle("Prob. of misidentification");
	// X axis ratio plot settings
	h0->GetXaxis()->SetTitleSize(0.05);
	h0->GetXaxis()->SetTitle(titleX.c_str());
	h0->GetXaxis()->SetTitleOffset(0.91);
	h0->GetYaxis()->SetTitleSize(0.05);
	h0->GetYaxis()->SetTitleOffset(1.1);
	h0->GetYaxis()->SetRangeUser(0,0.02);
	h0->GetXaxis()->SetTitle("Pt-TuneP lower leg tag");
	//h0->GetXaxis()->SetTitle("Pt-TuneP upper leg tag");

float glbBin =  h0->GetBinContent(1);
	cout << "Charge rate - glb : " << glbBin << endl;


	TH1F *h1 = (TH1F*)pthistoTkonlyUP->Clone("h1");
	h1->SetLineColor(kRed);
	h1->Sumw2();
	h1->SetStats(0);      // No statistics on lower plot
	h1->Divide(pthistoTkonlyLOW,pthistoTkonlyUP ,1,1,"B");
	h1->SetMarkerStyle(22);
	h1->SetMarkerColor(kRed);
	float TkonlyBin =  h1->GetBinContent(1);
	cout << "Charge rate - Tkonly : " << TkonlyBin << endl;

	//h1->Draw("E0 SAME");       // Draw the ratio plot

	TH1F *h2 = (TH1F*)pthistoTpfmsUP->Clone("h2");
	h2->SetLineColor(kOrange);
	h2->Sumw2();
	h2->SetStats(0);      // No statistics on lower plot
	h2->Divide(pthistoTpfmsLOW,pthistoTpfmsUP ,1,1,"B");
	h2->SetMarkerStyle(20);
	h2->SetMarkerColor(kOrange);
	float TpfmsBin =  h2->GetBinContent(1);
	cout << "Charge rate - TPFMS : " << TpfmsBin << endl;

	h2->Draw("E0 SAME");       // Draw the ratio plot



	TH1F *h3 = (TH1F*)pthistoPickyUP->Clone("h3");
	h3->SetLineColor(kMagenta);
	h3->Sumw2();
	h3->SetStats(0);      // No statistics on lower plot
	h3->Divide(pthistoPickyLOW,pthistoPickyUP ,1,1,"B");
	h3->SetMarkerStyle(23);
	h3->SetMarkerColor(kMagenta);
	float PickyBin =  h3->GetBinContent(1);
	cout << "Charge rate - Picky : " << PickyBin << endl;

	//h3->Draw("E0 SAME");       // Draw the ratio plot


	// Define the ratio plot
	TH1F *h4 = (TH1F*)pthistoDYTUP->Clone("h4");
	h4->SetLineColor(kGreen);
	h4->Sumw2();
	h4->SetStats(0);      // No statistics on lower plot
	h4->Divide(pthistoDYTLOW,pthistoDYTUP ,1,1,"B");
	h4->SetMarkerStyle(24);
	h4->SetMarkerColor(kGreen);
	float DYTBin =  h4->GetBinContent(1);
	cout << "Charge rate - DYT : " << DYTBin << endl;

	//h4->Draw("E0 SAME");       // Draw the ratio plot

	// Define the ratio plot
	TH1F *h5 = (TH1F*)pthistoTunePUP->Clone("h5");
	h5->SetLineColor(kBlue);
	h5->Sumw2();
	h5->SetMarkerColor(kBlue);
	
	h5->SetStats(0);      // No statistics on lower plot
	h5->Divide(pthistoTunePLOW,pthistoTunePUP ,1,1,"B");

	float TunePBin =  h5->GetBinContent(1);
	cout << "Charge rate - TuneP : " << TunePBin << endl;

	h5->SetMarkerStyle(25);
	//h5->Draw("E0 SAME");       // Draw the ratio plot
	// No statistics on lower plot


	TLegend * leg0 = new TLegend(0.75, 0.56, 0.98, 0.76);
	//leg0->SetHeader("2016+2017 data");
	leg0->SetHeader("MC total");
	leg0->SetFillColor(10);
	leg0->AddEntry(h0,"Global ");
	//leg0->AddEntry(h1,"Tkonly");
	leg0->AddEntry(h2,"TPFMS ");
	//leg0->AddEntry(h3,"Picky");
	//leg0->AddEntry(h4,"DYT ");
	//leg0->AddEntry(h5,"TuneP");

	leg0 -> Draw();*/

	//TGraph

	/*	Double_t x[6], y[6];
		Int_t n = 6;
		for (Int_t i=0;i<n;i++) {
		x[i] = i+1;
		y[i] = 	wrongCharge[i];
		}



		TGraph *gr = new TGraph(n,x,y);
		gr->Draw("AB1");
		gr->GetYaxis()->SetTitle("#events w/ wrong charge");
		//gr->GetYaxis()->SetRangeUser(0,35);
		gr->SetTitle("");

		TLatex t(3.7,12,title.c_str());
		t.DrawClone("Same");
		TLatex t1(1,3,"Global");
		t1.SetTextAngle(90);
		t1.DrawClone("Same");	
		TLatex t2(2,3,"Tkonly");
		t2.SetTextAngle(90);
		t2.DrawClone("Same");	
		TLatex t3(3,3,"TPFMS");
		t3.SetTextAngle(90);
		t3.DrawClone("Same");	
		TLatex t4(4,3,"Picky");
		t4.SetTextAngle(90);
		t4.DrawClone("Same");	
		TLatex t5(5,3,"DYT");
		t5.SetTextAngle(90);
		t5.DrawClone("Same");	
		TLatex t6(6,3,"TuneP");
		t6.SetTextAngle(90);
		t6.DrawClone("Same");	


		Int_t ci;      // for color index setting
		TColor *color; // for color definition with alpha
		ci = TColor::GetColor("#333399");
		gr->SetFillColor(ci);
		gr->SetFillStyle(3001);
		gr->SetMarkerStyle(3);

		char const *algor[6]={"Glb","Tkonly","TPFMS","Picky","DYT","TuneP"};*/






	/*TLatex t(1,0.01,"2016 data");
	  t.DrawClone("Same");*/

	/*TFile *fout = new TFile("testpt.root ","RECREATE");

	  pthistoGlb->Write();
	  pthistoStalone->Write();

	  fout->Close();*/

}// end of function 
