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

  TH1F *ptDataDen =new TH1F("pthistoTkonly","",1,10,2000);
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
	treedata->Add("ROOT_Files/allVersions/cosmic_data_16_17.root");
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

	string titleX = string("p_{t} [GeV]-")+algo+ string(" lower leg tag");
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
			}
			*/
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
		//
		/////////////////DATA/////////////////
		TH1F *h5 = (TH1F*)ptDataDen->Clone("h5");
		h5->Sumw2();
		h5->SetStats(11111);      // No statistics on lower plot
		h5->Divide(ptDataTunePNum,ptDataDen ,1,1,"B");

		/////////////////////////////////////////
		//////////////////MC/////////////////////
		TH1F *h5MC = (TH1F*)ptMCDen->Clone("h5MC");
		h5MC->Sumw2();
		h5MC->Divide(ptMCTunePNum,ptMCDen ,1,1,"B");

		
		
		h5->SetMarkerColor(kBlue);
		h5->SetLineColor(kBlue);
		h5->SetMarkerStyle(20);
		h5->GetXaxis()->SetTitleSize(0.05);
		h5->GetXaxis()->SetTitle(titleX.c_str());
		h5->GetXaxis()->SetTitleOffset(0.91);
		// No statistics on lower plot
		h5->GetYaxis()->SetTitle("Prob. of misidentification");
		// X axis ratio plot settings
		h5->GetYaxis()->SetTitleSize(0.048);

		h5->GetYaxis()->SetTitleOffset(1.1);
		h5->GetYaxis()->SetRangeUser(0,0.006);

		h5->Draw("E0");       // Draw the ratio plot
		h5MC->SetMarkerColor(kBlue-9);
		h5MC->SetLineColor(kBlue-9);
		h5MC->SetMarkerStyle(24);
		h5MC->Draw("E0 SAME");       // Draw the ratio plot


		//////////////////////////////////////////////////////////
		/////////////LEGEND///////////////////////////////////////
		//////////////////////////////////////////////////////////
		TLegend * legData = new TLegend(0.75, 0.67, 0.98, 0.77);
		legData->SetHeader("Data 2016+2017");
		legData->SetFillColor(10);
		legData->AddEntry(h5,"TuneP");
		legData -> Draw();

		TLegend * legMC = new TLegend(0.75, 0.57, 0.98, 0.67);
		legMC->SetHeader("MC 2016");
		legMC->SetFillColor(10);
		legMC->AddEntry(h5MC,"TuneP");
		legMC -> Draw();

		/*

		///////////////////////////////////////////
		//            ALL ALGOS			 //
		///////////////////////////////////////////
		//
		//////////////////////////////////////////
		//GLOBAL
		//////////////////////////////////////////
		TH1F *h0 = (TH1F*)ptDataDen->Clone("h0");
		h0->SetLineColor(kBlack);
		h0->Sumw2();
		h0->SetStats(111111);      
		h0->Divide(ptDataGlbNum,ptDataDen ,1,1,"B");
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
		h0->GetYaxis()->SetRangeUser(0,0.05);
		//h0->GetXaxis()->SetTitle("Pt-TuneP lower leg tag");
		h0->GetXaxis()->SetTitle("Pt-TuneP upper leg tag");

		float glbBin =  h0->GetBinContent(1);
		//cout << "Charge rate - glb : " << glbBin << endl;

		/////////////////////////////////////////////////
		//Tkonly
		////////////////////////////////////////////////

		TH1F *h1 = (TH1F*)ptDataDen->Clone("h1");
		h1->SetLineColor(kRed);
		h1->Sumw2();
		h1->SetStats(0);      // No statistics on lower plot
		h1->Divide(ptDataTkonlyNum,ptDataDen ,1,1,"B");
		h1->SetMarkerStyle(22);
		h1->SetMarkerColor(kRed);
		float TkonlyBin =  h1->GetBinContent(1);
		//cout << "Charge rate - Tkonly : " << TkonlyBin << endl;

		h1->Draw("E0 SAME");      // Draw the ratio plot

		/////////////////////////////////////////////////
		//TPFMS
		/////////////////////////////////////////////////

		TH1F *h2 = (TH1F*)ptDataDen->Clone("h2");
		h2->SetLineColor(kOrange);
		h2->Sumw2();
		h2->SetStats(0);      // No statistics on lower plot
		h2->Divide(ptDataTpfmsNum,ptDataDen ,1,1,"B");
		h2->SetMarkerStyle(20);
		h2->SetMarkerColor(kOrange);
		float TpfmsBin =  h2->GetBinContent(1);
		//cout << "Charge rate - TPFMS : " << TpfmsBin << endl;

		h2->Draw("E0 SAME");       // Draw the ratio plot

		//////////////////////////////////////////////////
		//Picky
		//////////////////////////////////////////////////

		TH1F *h3 = (TH1F*)ptDataDen->Clone("h3");
		h3->SetLineColor(kMagenta);
		h3->Sumw2();
		h3->SetStats(0);      // No statistics on lower plot
		h3->Divide(ptDataPickyNum,ptDataDen ,1,1,"B");
		h3->SetMarkerStyle(23);
		h3->SetMarkerColor(kMagenta);
		float PickyBin =  h3->GetBinContent(1);
		//cout << "Charge rate - Picky : " << PickyBin << endl;

		h3->Draw("E0 SAME");       // Draw the ratio plot

		//////////////////////////////////////////////////
		//DYT
		//////////////////////////////////////////////////
		TH1F *h4 = (TH1F*)ptDataDen->Clone("h4");
		h4->SetLineColor(kGreen);
		h4->Sumw2();
		h4->SetStats(0);      // No statistics on lower plot
		h4->Divide(ptDataDYTNum,ptDataDen ,1,1,"B");
		h4->SetMarkerStyle(24);
		h4->SetMarkerColor(kGreen);
		float DYTBin =  h4->GetBinContent(1);
		//cout << "Charge rate - DYT : " << DYTBin << endl;

		h4->Draw("E0 SAME");       // Draw the ratio plot

		//////////////////////////////////////////////////
		//TuneP
		//////////////////////////////////////////////////

		TH1F *h5 = (TH1F*)ptDataDen->Clone("h5");
		h5->SetLineColor(kBlue);
		h5->Sumw2();
		h5->SetMarkerColor(kBlue);

		h5->SetStats(0);      // No statistics on lower plot
		h5->Divide(ptDataTunePNum,ptDataDen,1,1,"B");

		float TunePBin =  h5->GetBinContent(1);
		//cout << "Charge rate - TuneP : " << TunePBin << endl;

		h5->SetMarkerStyle(25);
		h5->Draw("E0 SAME");       // Draw the ratio plot

		///////////////////////////////////////////////////

		TLegend * leg0 = new TLegend(0.75, 0.56, 0.98, 0.76);
		leg0->SetHeader("2016+2017 data");
		//leg0->SetHeader("MC total");
		leg0->SetFillColor(10);
		leg0->AddEntry(h0,"Global ");
		//leg0->AddEntry(h1,"Tkonly");
		leg0->AddEntry(h2,"TPFMS ");
		//leg0->AddEntry(h3,"Picky");
		//leg0->AddEntry(h4,"DYT ");
		//leg0->AddEntry(h5,"TuneP");

		leg0 -> Draw();*/







			/*TLatex t(1,0.01,"2016 data");
			  t.DrawClone("Same");*/

			/*TFile *fout = new TFile("testpt.root ","RECREATE");

			  pthistoGlb->Write();
			  pthistoStalone->Write();

			  fout->Close();*/

	}// end of function 
