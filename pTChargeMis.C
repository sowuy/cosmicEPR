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

float unprop_pt[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];

ushort pixel_hits[n_tracks][n_track_pos];

ushort strip_layers[n_tracks][n_track_pos];

////////////////////////////////////////////////////////////////////////////////


//Declaration of hitsogramm i plan to plot with this code
float bins[]={50,100,200,400,1000,2000};


int binnum = 5;



//Charge confusion rate - data
//
//Denominateur
//
TH1F *ptDataDen =new TH1F("ptDataDen","",binnum,bins);

//Numerateur
TH1F *ptDataGlbNum =new TH1F("ptDataGlbNum","",binnum,bins);

TH1F *ptDataTkonlyNum =new TH1F("ptDataTkonlyNum","",binnum,bins);

TH1F *ptDataTpfmsNum =new TH1F("ptDataTpfmsNum","",binnum,bins);

TH1F *ptDataPickyNum =new TH1F("ptDataPickyNum","",binnum,bins);

TH1F *ptDataDYTNum =new TH1F("ptDataDYTNum","",binnum,bins);

TH1F *ptDataTunePNum =new TH1F("ptDataTunePNum","",binnum,bins);

//Charge confusion rate - MC
//
//Denominateur
//
TH1F *ptMCDen =new TH1F("ptMCDen","",binnum,bins);

//Numerateur
TH1F *ptMCGlbNum =new TH1F("ptMCGlbNum","",binnum,bins);

TH1F *ptMCTkonlyNum =new TH1F("ptMCTkonlyNum","",binnum,bins);

TH1F *ptMCTpfmsNum =new TH1F("ptMCTpfmsNum","",binnum,bins);

TH1F *ptMCPickyNum =new TH1F("ptMCPickyNum","",binnum,bins);

TH1F *ptMCDYTNum =new TH1F("ptMCDYTNum","",binnum,bins);

TH1F *ptMCTunePNum =new TH1F("ptMCTunePNum","",binnum,bins);

//
//Charge confusion rate - 1bin
/*TH1F *ptDataDen =new TH1F("pthistoGlb","",1,10,2000);
  TH1F *ptDataGlbNum =new TH1F("ptDataGlbNum","",1,10,2000);

  TH1F *ptDataDen =new TH1F("pthistoH1","",1,10,2000);
  TH1F *ptDataTkonlyNum =new TH1F("ptDataTkonlyNum","",1,10,2000);

  TH1F *pthistoTpfmsUP =new TH1F("pthistoTpfms","",1,10,2000);
  TH1F *ptDataTpfmsNum =new TH1F("ptDataTpfmsNum","",1,10,2000);

  TH1F *pthistoPickyUP =new TH1F("pthistoPicky","",1,10,2000);
  TH1F *ptDataPickyNum =new TH1F("ptDataPickyNum","",1,10,2000);

  TH1F *pthistoDYTUP =new TH1F("pthistoDYT","",1,10,2000);
  TH1F *ptDataDYTNum =new TH1F("ptDataDYTNum","",1,10,2000);

  TH1F *pthistoTunePUP =new TH1F("pthistoTuneP","",1,10,2000);
  TH1F *ptDataTunePNum =new TH1F("ptDataTunePNum","",1,10,2000);*/

//Begining of the function
//
//
void pTChargeMis(string algo=""){


	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");
	TChain *treeMC = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	treedata->Add("ROOT_Files/allVersions/cosmic_data_16_17_18.root");
	//treedata->Add ("ROOT_Files/resolution_cosmics.root");
	//treeMC->Add ("ROOT_Files/resolution_cosmics.root");

	treeMC->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilepton mass in my case for DY events.
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("strip_layers",strip_layers);
	treeMC->SetBranchAddress("unprop_charge",unprop_charge);
	treeMC->SetBranchAddress("unprop_pt",unprop_pt);
	treeMC->SetBranchAddress("pixel_hits",pixel_hits);
	treeMC->SetBranchAddress("strip_layers",strip_layers);

	// This will get the numbers of entries of the tree.

	int nentries = treedata->GetEntries();
	int nentriesMC = treeMC->GetEntries();


	int selectedEvents = 0;
	cout << "nEntries = " << nentries << endl;

	//Decalaration of variable not in the tree that i use for the results

	Float_t wrongCharge_Glb = 0.;
	Float_t wrongCharge_Tkonly = 0.;
	Float_t wrongCharge_TPFMS = 0.;
	Float_t wrongCharge_Picky = 0.;
	Float_t wrongCharge_DYT = 0.;
	Float_t wrongCharge_TuneP = 0.;

	int algoNum=0;

	string titleX = string("p_{T} [GeV]-")+algo+ string(" lower leg tag");
	string title = algo + string(" lower leg tag");

	if (algo == "Glb") algoNum=0;
	if (algo == "Tkonly") algoNum=2;
	if (algo == "TPFMS") algoNum=3;
	if (algo == "Picky") algoNum=4;
	if (algo == "DYT") algoNum=5;
	if (algo == "TuneP")  algoNum=8;



	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);


		//******************************//	
		//selection cuts - LOWER LEG TAG//
		//******************************//

		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][1]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][1]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][1]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][1]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][1]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			selectedEvents+=1;

			//Fill Denominateur with events who passed the selection	
			ptDataDen->Fill(unprop_pt[algoNum][1]);



			//global
			if (unprop_charge[0][0]!=unprop_charge[algoNum][1]){ 
				//Fill Numerateur with events with misidentified charge
				ptDataGlbNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Glb++;
			}
			//Tkonly
			if (unprop_charge[2][0]!=unprop_charge[algoNum][1]){ 
				ptDataTkonlyNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Tkonly++;

			}
			//Tpfms
			if (unprop_charge[3][0]!=unprop_charge[algoNum][1]){ 
				ptDataTpfmsNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_TPFMS++;

			}
			//Picky
			if (unprop_charge[4][0]!=unprop_charge[algoNum][1]){ 
				ptDataPickyNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Picky++;

			}
			//DYT
			if (unprop_charge[5][0]!=unprop_charge[algoNum][1]){ 
				ptDataDYTNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_DYT++;

			}
			//TuneP
			if (unprop_charge[8][0]!=unprop_charge[algoNum][1]){ 
				ptDataTunePNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_TuneP++;
			}





			//******************************//	
			//selection cuts - UPPER LEG TAG//
			//******************************//

			/*if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][0]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][0]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][0]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][0]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][0]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][0]>30.){


			//Fill Denominateur with events who passed the selection	
			ptDataDen->Fill(unprop_pt[algoNum][0]);

			////////////////////
			//Algorithm choice//
			////////////////////

			//global
			if (unprop_charge[0][1]!=unprop_charge[algoNum][0]){ 
			ptDataGlbNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_Glb++;
			}
			//Tkonly
			if (unprop_charge[2][1]!=unprop_charge[algoNum][0]){ 
			ptDataTkonlyNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_Tkonly++;

			}
			//Tpfms
			if (unprop_charge[3][1]!=unprop_charge[algoNum][0]){ 
			ptDataTpfmsNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_TPFMS++;

			}
			//Picky
			if (unprop_charge[4][1]!=unprop_charge[algoNum][0]){ 
			ptDataPickyNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_Picky++;

			}
			//DYT
			if (unprop_charge[5][1]!=unprop_charge[algoNum][0]){ 
			ptDataDYTNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_DYT++;

			}
			//TuneP
			if (unprop_charge[8][1]!=unprop_charge[algoNum][0]){ 
			ptDataTunePNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_TuneP++;
			}*/
			
		}
		}// end loop p

		/************************************************************/
		/*                    MC                                    */
		/************************************************************/

		for ( int p=0; p<nentriesMC ;p++){
		// this loop over all the events in your tree

		treeMC->GetEntry(p);


		//******************************//	
		//selection cuts - LOWER LEG TAG//
		//******************************//

		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][1]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][1]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][1]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][1]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][1]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			//Fill Denominateur with events who passed the selection	
			ptMCDen->Fill(unprop_pt[algoNum][1]);



			//global
			if (unprop_charge[0][0]!=unprop_charge[algoNum][1]){ 
				//Fill Numerateur with events with misidentified charge
				ptMCGlbNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Glb++;
			}
			//Tkonly
			if (unprop_charge[2][0]!=unprop_charge[algoNum][1]){ 
				ptMCTkonlyNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Tkonly++;

			}
			//Tpfms
			if (unprop_charge[3][0]!=unprop_charge[algoNum][1]){ 
				ptMCTpfmsNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_TPFMS++;

			}
			//Picky
			if (unprop_charge[4][0]!=unprop_charge[algoNum][1]){ 
				ptMCPickyNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_Picky++;

			}
			//DYT
			if (unprop_charge[5][0]!=unprop_charge[algoNum][1]){ 
				ptMCDYTNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_DYT++;

			}
			//TuneP
			if (unprop_charge[8][0]!=unprop_charge[algoNum][1]){ 
				ptMCTunePNum->Fill(unprop_pt[algoNum][1]);
				wrongCharge_TuneP++;
			}

		}

			//******************************//	
			//selection cuts - UPPER LEG TAG//
			//******************************//

		/*	if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][0]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][0]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][0]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][0]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][0]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][0]>30.){


			//Fill Denominateur with events who passed the selection	
			ptMCDen->Fill(unprop_pt[algoNum][0]);

			////////////////////
			//Algorithm choice//
			////////////////////

			//global
			if (unprop_charge[0][1]!=unprop_charge[algoNum][0]){ 
			ptMCGlbNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_Glb++;
			}
			//Tkonly
			if (unprop_charge[2][1]!=unprop_charge[algoNum][0]){ 
			ptMCTkonlyNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_Tkonly++;

			}
			//Tpfms
			if (unprop_charge[3][1]!=unprop_charge[algoNum][0]){ 
			ptMCTpfmsNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_TPFMS++;

			}
			//Picky
			if (unprop_charge[4][1]!=unprop_charge[algoNum][0]){ 
			ptMCPickyNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_Picky++;

			}
			//DYT
			if (unprop_charge[5][1]!=unprop_charge[algoNum][0]){ 
			ptMCDYTNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_DYT++;

			}
			//TuneP
			if (unprop_charge[8][1]!=unprop_charge[algoNum][0]){ 
			ptMCTunePNum->Fill(unprop_pt[algoNum][0]);
			wrongCharge_TuneP++;
			}
			
		}*/


}




		/*cout << "Tag given by " << algo << "lower leg" << endl;
		  cout << "Events with wrong charge for the 6 algorithms :" << endl;
		  cout << "Global wrong charge = " << wrongCharge_Glb << endl;
		  cout << "Tkonly wrong charge = " << wrongCharge_Tkonly << endl;
		  cout << "TPFMS wrong charge = " << wrongCharge_TPFMS << endl;
		  cout << "Picky wrong charge = " << wrongCharge_Picky << endl;
		  cout << "DYT wrong charge = " << wrongCharge_DYT << endl;
		  cout << "TuneP wrong charge = " << wrongCharge_TuneP << endl;*/


		cout << "Selected events = " << selectedEvents << endl;
		Float_t wrongCharge[6] = {wrongCharge_Glb,wrongCharge_Tkonly,wrongCharge_TPFMS,wrongCharge_Picky,wrongCharge_DYT,wrongCharge_TuneP};



		// Define the Canvas
		TCanvas *c1 = new TCanvas("c", "canvas", 700,550);

		//c->SetLogy();



		//////////////////////////////////////
		//            TuneP  only           //
		//////////////////////////////////////
		
		/////////////////DATA/////////////////
		/*TH1F*TuneP = (TH1F*)ptDataDen->Clone("TuneP");
		TuneP->Sumw2();
		TuneP->SetStats(11111);      
		TuneP->Divide(ptDataTunePNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////
		TH1F *TunePMC = (TH1F*)ptMCDen->Clone("TunePMC");
		TunePMC->Sumw2();
		TunePMC->Divide(ptMCTunePNum,ptMCDen ,1,1,"B");
		
		// PLOT SETTINGS
		TuneP->SetMarkerColor(kBlue+2);
		TuneP->SetLineColor(kBlue+2);
		TuneP->SetMarkerStyle(20);
		TuneP->GetXaxis()->SetTitleSize(0.045);
		TuneP->GetXaxis()->SetLabelSize(0.04);
		TuneP->GetXaxis()->SetTitle(titleX.c_str());
		TuneP->GetXaxis()->SetTitleOffset(0.95);
		TuneP->GetYaxis()->SetTitle("Prob. of misidentification");
		TuneP->GetYaxis()->SetTitleSize(0.048);
		TuneP->GetYaxis()->SetTitleOffset(1.1);
		TuneP->GetYaxis()->SetRangeUser(0,0.006);
		TuneP->Draw("E0");      
		
		TunePMC->SetMarkerColor(kBlue-9);
		TunePMC->SetLineColor(kBlue-9);
		TunePMC->SetMarkerStyle(24);
		TunePMC->Draw("E0 SAME");       

		//////////////////////////////////////////////////////////
		/////////////LEGEND///////////////////////////////////////
		//////////////////////////////////////////////////////////
		TLegend * legData = new TLegend(0.75, 0.67, 0.98, 0.77);
		legData->SetHeader("Data 16-17-18");
		legData->SetFillColor(10);
		legData->AddEntry(TuneP,"TuneP");
		legData -> Draw();

		TLegend * legMC = new TLegend(0.75, 0.57, 0.98, 0.67);
		legMC->SetHeader("MC 2016");
		legMC->SetFillColor(10);
		legMC->AddEntry(TunePMC,"TuneP");
		legMC -> Draw();*/

		

		///////////////////////////////////////////
		//            ALL ALGOS			 //
		///////////////////////////////////////////
		
		//////////////////////////////////////////
		//GLOBAL
		//////////////////////////////////////////
		
		
		/////////////////DATA/////////////////

		TH1 *Glb = (TH1F*)ptDataDen->Clone("Glb");
		Glb->Sumw2();
		Glb->SetStats(111111);      
		Glb->Divide(ptDataGlbNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *GlbMC = (TH1F*)ptMCDen->Clone("GlbMC");
		GlbMC->Sumw2();
		GlbMC->Divide(ptMCGlbNum,ptMCDen ,1,1,"B");

		// PLOT SETTINGS

		Glb->SetMarkerColor(kBlack);
		Glb->SetLineColor(kBlack);
		Glb->SetMarkerStyle(20);
		Glb->GetXaxis()->SetTitleSize(0.045);
		Glb->GetXaxis()->SetLabelSize(0.04);
		Glb->GetXaxis()->SetTitle(titleX.c_str());
		Glb->GetXaxis()->SetTitleOffset(0.95);
		Glb->GetYaxis()->SetTitle("Prob. of misidentification");
		Glb->GetYaxis()->SetTitleSize(0.048);
		Glb->GetYaxis()->SetTitleOffset(1.1);
		Glb->GetYaxis()->SetRangeUser(0,0.05);
		Glb->Draw("E0");      
		
		GlbMC->SetMarkerColor(kGray);
		GlbMC->SetLineColor(kGray);
		GlbMC->SetMarkerStyle(24);
		GlbMC->Draw("E0 SAME");  
		float glbBin =  Glb->GetBinContent(1);
		//cout << "Charge rate - glb : " << glbBin << endl;

		/////////////////////////////////////////////////
		//TKONLY
		////////////////////////////////////////////////

		/////////////////DATA/////////////////

		/*TH1F *Tkonly = (TH1F*)ptDataDen->Clone("Tkonly");
		Tkonly->Sumw2();
		Tkonly->SetStats(0);      
		Tkonly->Divide(ptDataTkonlyNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *TkonlyMC = (TH1F*)ptDataDen->Clone("TkonlyMC");
		TkonlyMC->Sumw2();
		TkonlyMC->SetStats(0);      
		TkonlyMC->Divide(ptDataTkonlyMCNum,ptDataDen ,1,1,"B");

		// PLOT SETTINGS

		Tkonly->SetLineColor(kRed+2);
		Tkonly->SetMarkerStyle(20);
		Tkonly->SetMarkerColor(kRed+2);
		TkonlyMC->SetLineColor(kRed-9);
		TkonlyMC->SetMarkerStyle(24);
		TkonlyMC->SetMarkerColor(kRed-9);

		float TkonlyBin =  Tkonly->GetBinContent(1);
		//cout << "Charge rate - Tkonly : " << TkonlyBin << endl;

		Tkonly->Draw("E0 SAME"); 
		TkonlyMC->Draw("E0 SAME");*/
		/////////////////////////////////////////////////
		//TPFMS
		/////////////////////////////////////////////////
		
		/////////////////DATA/////////////////

		TH1F *Tpfms = (TH1F*)ptDataDen->Clone("Tpfms");
		Tpfms->Sumw2();
		Tpfms->SetStats(0);      
		Tpfms->Divide(ptDataTpfmsNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *TpfmsMC = (TH1F*)ptMCDen->Clone("TpfmsMC");
		TpfmsMC->Sumw2();
		TpfmsMC->SetStats(0);      
		TpfmsMC->Divide(ptMCTpfmsNum,ptMCDen ,1,1,"B");

		// PLOT SETTINGS

		Tpfms->SetLineColor(kOrange+2);
		Tpfms->SetMarkerStyle(20);
		Tpfms->SetMarkerColor(kOrange+2);
		TpfmsMC->SetLineColor(kOrange-9);
		TpfmsMC->SetMarkerStyle(24);
		TpfmsMC->SetMarkerColor(kOrange-9);

		float TpfmsBin =  Tpfms->GetBinContent(1);
		//cout << "Charge rate - TPFMS : " << TpfmsBin << endl;

		Tpfms->Draw("E0 SAME"); 
		TpfmsMC->Draw("E0 SAME");

	
		//////////////////////////////////////////////////
		//Picky
		//////////////////////////////////////////////////
		
		/////////////////DATA/////////////////

		/*TH1F *Picky = (TH1F*)ptDataDen->Clone("Picky");
		Picky->Sumw2();
		Picky->SetStats(0);      
		Picky->Divide(ptDataPickyNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *PickyMC = (TH1F*)ptDataDen->Clone("PickyMC");
		PickyMC->Sumw2();
		PickyMC->SetStats(0);      
		PickyMC->Divide(ptDataPickyMCNum,ptDataDen ,1,1,"B");

		// PLOT SETTINGS

		Picky->SetLineColor(kMagenta+2);
		Picky->SetMarkerStyle(20);
		Picky->SetMarkerColor(kMagenta+2);
		PickyMC->SetLineColor(kMagenta-9);
		PickyMC->SetMarkerStyle(24);
		PickyMC->SetMarkerColor(kMagenta-9);

		float PickyBin =  Picky->GetBinContent(1);
		//cout << "Charge rate - Picky : " << PickyBin << endl;

		Picky->Draw("E0 SAME"); 
		PickyMC->Draw("E0 SAME");

		//////////////////////////////////////////////////
		//DYT
		//////////////////////////////////////////////////
		
		/////////////////DATA/////////////////

		TH1F *DYT = (TH1F*)ptDataDen->Clone("DYT");
		DYT->Sumw2();
		DYT->SetStats(0);      
		DYT->Divide(ptDataDYTNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *DYTMC = (TH1F*)ptDataDen->Clone("DYTMC");
		DYTMC->Sumw2();
		DYTMC->SetStats(0);      
		DYTMC->Divide(ptDataDYTMCNum,ptDataDen ,1,1,"B");

		// PLOT SETTINGS

		DYT->SetLineColor(kGreen+2);
		DYT->SetMarkerStyle(20);
		DYT->SetMarkerColor(kGreen+2);
		DYTMC->SetLineColor(kGreen-9);
		DYTMC->SetMarkerStyle(24);
		DYTMC->SetMarkerColor(kGreen-9);

		float DYTBin =  DYT->GetBinContent(1);
		//cout << "Charge rate - DYT : " << DYTBin << endl;

		DYT->Draw("E0 SAME"); 
		DYTMC->Draw("E0 SAME");

		//////////////////////////////////////////////////
		//TuneP
		//////////////////////////////////////////////////

		/////////////////DATA/////////////////

		TH1F *TuneP = (TH1F*)ptDataDen->Clone("TuneP");
		TuneP->Sumw2();
		TuneP->SetStats(0);      
		TuneP->Divide(ptDataTunePNum,ptDataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *TunePMC = (TH1F*)ptDataDen->Clone("TunePMC");
		TunePMC->Sumw2();
		TunePMC->SetStats(0);      
		TunePMC->Divide(ptDataTunePMCNum,ptDataDen ,1,1,"B");

		// PLOT SETTINGS

		TuneP->SetLineColor(kBlue+2);
		TuneP->SetMarkerStyle(20);
		TuneP->SetMarkerColor(kBlue+2);
		TunePMC->SetLineColor(kBlue-9);
		TunePMC->SetMarkerStyle(24);
		TunePMC->SetMarkerColor(kBlue-9);

		float TunePBin =  TuneP->GetBinContent(1);
		//cout << "Charge rate - TuneP : " << TunePBin << endl;

		TuneP->Draw("E0 SAME"); 
		TunePMC->Draw("E0 SAME");*/

		///////////////////////////////////////////////////

		TLegend * legData = new TLegend(0.75, 0.63, 0.98, 0.77);
		legData->SetHeader("Data 16-17-18");
		legData->SetFillColor(10);
		legData->AddEntry(Glb,"Global");
		//legData->AddEntry(Tkonly,"Tkonly");
		legData->AddEntry(Tpfms,"TPFMS ");
		//legData->AddEntry(Picky,"Picky");
		//legData->AddEntry(DYT,"DYT ");
		//legData->AddEntry(TuneP,"TuneP");
		legData -> Draw();
	
		TLegend * legMC = new TLegend(0.75, 0.49, 0.98, 0.63);
		legMC->SetHeader("MC 2016");
		legMC->SetFillColor(10);
		legMC->AddEntry(GlbMC,"Global");
		//legMC->AddEntry(TkonlyMC,"Tkonly");
		legMC->AddEntry(TpfmsMC,"TPFMS ");
		//legMC->AddEntry(PickyMC,"Picky");
		//legMC->AddEntry(DYTMC,"DYT ");
		//legMC->AddEntry(TunePMC,"TuneP");
		legMC -> Draw();

		





			/*TLatex t(1,0.01,"2016 data");
			  t.DrawClone("Same");*/

			/*TFile *fout = new TFile("testpt.root ","RECREATE");

			  pthistoGlb->Write();
			  pthistoStalone->Write();

			  fout->Close();*/

	}// end of function 
