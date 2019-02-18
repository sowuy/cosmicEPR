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

float unprop_phi[n_tracks][n_track_pos];
float unprop_pt[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];
float unprop_theta[n_tracks][n_track_pos];
float eta[n_tracks][n_track_pos];
ushort pixel_hits[n_tracks][n_track_pos];
ushort strip_layers[n_tracks][n_track_pos];

////////////////////////////////////////////////////////////////////////////////



//
//Charge confusion rate - 1bin
/*TH1F *DataDen =new TH1F("pthistoGlb","",1,10,2000);
  TH1F *DataGlbNum =new TH1F("DataGlbNum","",1,10,2000);

  TH1F *DataDen =new TH1F("pthistoH1","",1,10,2000);
  TH1F *DataTkonlyNum =new TH1F("DataTkonlyNum","",1,10,2000);

  TH1F *pthistoTpfmsUP =new TH1F("pthistoTpfms","",1,10,2000);
  TH1F *DataTpfmsNum =new TH1F("DataTpfmsNum","",1,10,2000);

  TH1F *pthistoPickyUP =new TH1F("pthistoPicky","",1,10,2000);
  TH1F *DataPickyNum =new TH1F("DataPickyNum","",1,10,2000);

  TH1F *pthistoDYTUP =new TH1F("pthistoDYT","",1,10,2000);
  TH1F *DataDYTNum =new TH1F("DataDYTNum","",1,10,2000);

  TH1F *pthistoTunePUP =new TH1F("pthistoTuneP","",1,10,2000);
  TH1F *DataTunePNum =new TH1F("DataTunePNum","",1,10,2000);*/

//Begining of the function
//
//
void pTChargeMis(string var="",string algo="", string tag="", bool TunePOnly = false){

	string titleX="";
	//int binnum=0;
	//float bins[]={};
	//float bins[]={-0.9,0,0.9};
	//int binnum = 2;
	float bins[]={50,100,200,400,1000,2000};
	int binnum = 5;

	cout << "print var : " << var <<endl;	

	//Declaration of histogramm i plan to plot with this code	
	if (var == "pT"){
		//bins[]={50,100,200,400,1000,2000};
		//binnum = 5;
		titleX = string("p_{t} [GeV]-") +algo+ " " + tag + string(" leg tag");

	}
	else if (var == "eta"){
		//bins[]={-0.9,0,0.9};
		//binnum = 2;
		titleX = string("#eta-") +algo+ " " + tag + string(" leg tag");

	}
	else {
		//bins[]={-3,-2.5,-2,-1.5,-1,-0.5,0};
		//binnum = 6;
		titleX = string("#phi-") +algo+ " " + tag + string(" leg tag");

	}


	//Charge confusion rate - data
	//
	//Denominateur
	//
	TH1F *DataDen =new TH1F("DataDen","",binnum,bins);

	//Numerateur
	TH1F *DataGlbNum =new TH1F("DataGlbNum","",binnum,bins);
	TH1F *DataTkonlyNum =new TH1F("DataTkonlyNum","",binnum,bins);
	TH1F *DataTpfmsNum =new TH1F("DataTpfmsNum","",binnum,bins);
	TH1F *DataPickyNum =new TH1F("DataPickyNum","",binnum,bins);
	TH1F *DataDYTNum =new TH1F("DataDYTNum","",binnum,bins);
	TH1F *DataTunePNum =new TH1F("DataTunePNum","",binnum,bins);
	///////////////////////////////////////////////////////////////

	//Charge confusion rate - MC

	//Denominateur
	//
	TH1F *MCDen =new TH1F("MCDen","",binnum,bins);

	//Numerateur
	TH1F *MCGlbNum =new TH1F("MCGlbNum","",binnum,bins);
	TH1F *MCTkonlyNum =new TH1F("MCTkonlyNum","",binnum,bins);
	TH1F *MCTpfmsNum =new TH1F("MCTpfmsNum","",binnum,bins);
	TH1F *MCPickyNum =new TH1F("MCPickyNum","",binnum,bins);
	TH1F *MCDYTNum =new TH1F("MCDYTNum","",binnum,bins);
	TH1F *MCTunePNum =new TH1F("MCTunePNum","",binnum,bins);

	///////////////////////////////////////////////////////////////
	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");
	TChain *treeMC = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");
	//treedata->Add ("ROOT_Files/resolution_cosmics.root");
	//treeMC->Add ("ROOT_Files/resolution_cosmics.root");
	treeMC->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilepton mass in my case for DY events.

	treedata->SetBranchAddress("unprop_phi",unprop_phi);
	treedata->SetBranchAddress("unprop_charge",unprop_charge);
	treedata->SetBranchAddress("unprop_pt",unprop_pt);
	treedata->SetBranchAddress("unprop_theta",unprop_theta);
	treedata->SetBranchAddress("pixel_hits",pixel_hits);
	treedata->SetBranchAddress("strip_layers",strip_layers);
	treeMC->SetBranchAddress("unprop_charge",unprop_charge);
	treeMC->SetBranchAddress("unprop_pt",unprop_pt);
	treeMC->SetBranchAddress("pixel_hits",pixel_hits);
	treeMC->SetBranchAddress("strip_layers",strip_layers);
	treeMC->SetBranchAddress("unprop_theta",unprop_theta);
	treeMC->SetBranchAddress("unprop_phi",unprop_phi);


	// This will get the numbers of entries of the tree.

	int nentries = treedata->GetEntries();
	int nentriesMC = treeMC->GetEntries();


	int algoNum=0;

	//string titleX = var + string(" - ")+algo+ " " + tag + string(" leg tag");
	string title = algo + string(" lower leg tag");

	if (algo == "Glb") algoNum=0;
	if (algo == "Tkonly") algoNum=2;
	if (algo == "TPFMS") algoNum=3;
	if (algo == "Picky") algoNum=4;
	if (algo == "DYT") algoNum=5;
	if (algo == "TuneP")  algoNum=8;

	int leg, antileg;

	if (tag =="lower"){
		leg = 1;
		antileg = 0;
	}
	else {
		leg = 0;
		antileg=1;
	}

	/************************************************************/
	/*                    Data                                  */
	/************************************************************/

	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);


		//***************//	
		//selection cuts //
		//***************//

		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][1]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][leg]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][leg]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][leg]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][leg]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][leg]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][leg]>30.){


			/////////////Pt////////////////////

			if (var == "pT"){

				//Fill Denominateur with events who passed the selection	
				DataDen->Fill(unprop_pt[algoNum][leg]);

				//global
				if (unprop_charge[0][antileg]!=unprop_charge[algoNum][leg]){ 
					//Fill Numerateur with events with misidentified charge
					DataGlbNum->Fill(unprop_pt[algoNum][leg]);
				}
				//Tkonly
				if (unprop_charge[2][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTkonlyNum->Fill(unprop_pt[algoNum][leg]);

				}
				//Tpfms
				if (unprop_charge[3][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTpfmsNum->Fill(unprop_pt[algoNum][leg]);

				}
				//Picky
				if (unprop_charge[4][antileg]!=unprop_charge[algoNum][leg]){ 
					DataPickyNum->Fill(unprop_pt[algoNum][leg]);

				}
				//DYT
				if (unprop_charge[5][antileg]!=unprop_charge[algoNum][leg]){ 
					DataDYTNum->Fill(unprop_pt[algoNum][leg]);

				}
				//TuneP
				if (unprop_charge[8][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTunePNum->Fill(unprop_pt[algoNum][leg]);
				}
			}

			/////////////ETA////////////////////

			else if (var=="eta"){

				for (int i=0;i<n_tracks;i++){
					for (int j=0;j<n_track_pos;j++){
						eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
					}
				}


				//Fill Denominateur with events who passed the selection	
				DataDen->Fill(eta[algoNum][leg]);

				//global
				if (unprop_charge[0][antileg]!=unprop_charge[algoNum][leg]){ 
					//Fill Numerateur with events with misidentified charge
					DataGlbNum->Fill(eta[algoNum][leg]);
				}
				//Tkonly
				if (unprop_charge[2][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTkonlyNum->Fill(eta[algoNum][leg]);

				}
				//Tpfms
				if (unprop_charge[3][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTpfmsNum->Fill(eta[algoNum][leg]);

				}
				//Picky
				if (unprop_charge[4][antileg]!=unprop_charge[algoNum][leg]){ 
					DataPickyNum->Fill(eta[algoNum][leg]);

				}
				//DYT
				if (unprop_charge[5][antileg]!=unprop_charge[algoNum][leg]){ 
					DataDYTNum->Fill(eta[algoNum][leg]);

				}
				//TuneP
				if (unprop_charge[8][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTunePNum->Fill(eta[algoNum][leg]);
				}
			}

			/////////////PHI////////////////////
			else {
				//Fill Denominateur with events who passed the selection	
				DataDen->Fill(unprop_phi[algoNum][leg]);

				//global
				if (unprop_charge[0][antileg]!=unprop_charge[algoNum][leg]){ 
					//Fill Numerateur with events with misidentified charge
					DataGlbNum->Fill(unprop_phi[algoNum][leg]);
				}
				//Tkonly
				if (unprop_charge[2][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTkonlyNum->Fill(unprop_phi[algoNum][leg]);

				}
				//Tpfms
				if (unprop_charge[3][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTpfmsNum->Fill(unprop_phi[algoNum][leg]);

				}
				//Picky
				if (unprop_charge[4][antileg]!=unprop_charge[algoNum][leg]){ 
					DataPickyNum->Fill(unprop_phi[algoNum][leg]);

				}
				//DYT
				if (unprop_charge[5][antileg]!=unprop_charge[algoNum][leg]){ 
					DataDYTNum->Fill(unprop_phi[algoNum][leg]);

				}
				//TuneP
				if (unprop_charge[8][antileg]!=unprop_charge[algoNum][leg]){ 
					DataTunePNum->Fill(unprop_phi[algoNum][leg]);
				}
			}

		} //end selection cut
	}// end loop p

	/************************************************************/
	/*                    MC                                    */
	/************************************************************/

	for ( int p=0; p<nentriesMC ;p++){
		// this loop over all the events in your tree

		treeMC->GetEntry(p);


		//**************//	
		//selection cuts//
		//**************//

		if (pixel_hits[0][0]>=1 && strip_layers[0][0]>=5 && pixel_hits[0][leg]>=1 && strip_layers[0][1]>=5 && unprop_pt[0][leg]>30. && pixel_hits[2][0]>=1 && strip_layers[2][0]>=5 && pixel_hits[2][1]>=1 && strip_layers[2][1]>=5 && unprop_pt[2][leg]>30. && pixel_hits[3][0]>=1 && strip_layers[3][0]>=5 && pixel_hits[3][1]>=1 && strip_layers[3][1]>=5 && unprop_pt[3][leg]>30. && pixel_hits[4][0]>=1 && strip_layers[4][0]>=5 && pixel_hits[4][1]>=1 && strip_layers[4][1]>=5 && unprop_pt[4][leg]>30. && pixel_hits[5][0]>=1 && strip_layers[5][0]>=5 && pixel_hits[5][1]>=1 && strip_layers[5][1]>=5 && unprop_pt[5][leg]>30. && pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][leg]>30.){

			/////////////Pt////////////////////

			if (var == "pT"){


				//Fill Denominateur with events who passed the selection	
				MCDen->Fill(unprop_pt[algoNum][leg]);

				//global
				if (unprop_charge[0][antileg]!=unprop_charge[algoNum][leg]){ 
					//Fill Numerateur with events with misidentified charge
					MCGlbNum->Fill(unprop_pt[algoNum][leg]);
				}
				//Tkonly
				if (unprop_charge[2][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTkonlyNum->Fill(unprop_pt[algoNum][leg]);

				}
				//Tpfms
				if (unprop_charge[3][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTpfmsNum->Fill(unprop_pt[algoNum][leg]);

				}
				//Picky
				if (unprop_charge[4][antileg]!=unprop_charge[algoNum][leg]){ 
					MCPickyNum->Fill(unprop_pt[algoNum][leg]);

				}
				//DYT
				if (unprop_charge[5][antileg]!=unprop_charge[algoNum][leg]){ 
					MCDYTNum->Fill(unprop_pt[algoNum][leg]);

				}
				//TuneP
				if (unprop_charge[8][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTunePNum->Fill(unprop_pt[algoNum][leg]);
				}
			}
			/////////////ETA////////////////////

			else if (var=="eta"){

				for (int i=0;i<n_tracks;i++){
					for (int j=0;j<n_track_pos;j++){
						eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
					}
				}

				//Fill Denominateur with events who passed the selection	
				MCDen->Fill(eta[algoNum][leg]);

				//global
				if (unprop_charge[0][antileg]!=unprop_charge[algoNum][leg]){ 
					//Fill Numerateur with events with misidentified charge
					MCGlbNum->Fill(eta[algoNum][leg]);
				}
				//Tkonly
				if (unprop_charge[2][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTkonlyNum->Fill(eta[algoNum][leg]);

				}
				//Tpfms
				if (unprop_charge[3][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTpfmsNum->Fill(eta[algoNum][leg]);

				}
				//Picky
				if (unprop_charge[4][antileg]!=unprop_charge[algoNum][leg]){ 
					MCPickyNum->Fill(eta[algoNum][leg]);

				}
				//DYT
				if (unprop_charge[5][antileg]!=unprop_charge[algoNum][leg]){ 
					MCDYTNum->Fill(eta[algoNum][leg]);

				}
				//TuneP
				if (unprop_charge[8][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTunePNum->Fill(eta[algoNum][leg]);
				}
			}

			/////////////PHI////////////////////
			else {
				//Fill Denominateur with events who passed the selection	
				MCDen->Fill(unprop_phi[algoNum][leg]);

				//global
				if (unprop_charge[0][antileg]!=unprop_charge[algoNum][leg]){ 
					//Fill Numerateur with events with misidentified charge
					MCGlbNum->Fill(unprop_phi[algoNum][leg]);
				}
				//Tkonly
				if (unprop_charge[2][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTkonlyNum->Fill(unprop_phi[algoNum][leg]);

				}
				//Tpfms
				if (unprop_charge[3][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTpfmsNum->Fill(unprop_phi[algoNum][leg]);

				}
				//Picky
				if (unprop_charge[4][antileg]!=unprop_charge[algoNum][leg]){ 
					MCPickyNum->Fill(unprop_phi[algoNum][leg]);

				}
				//DYT
				if (unprop_charge[5][antileg]!=unprop_charge[algoNum][leg]){ 
					MCDYTNum->Fill(unprop_phi[algoNum][leg]);

				}
				//TuneP
				if (unprop_charge[8][antileg]!=unprop_charge[algoNum][leg]){ 
					MCTunePNum->Fill(unprop_phi[algoNum][leg]);
				}
			}

		} //end selection cuts


	} //end p loop



	// Define the Canvas
	TCanvas *c1 = new TCanvas("c", "canvas", 700,550);

	//c->SetLogy();


	if (TunePOnly) {
		//////////////////////////////////////
		//            TuneP  only           //
		//////////////////////////////////////

		/////////////////DATA/////////////////
		TH1F*TuneP = (TH1F*)DataDen->Clone("TuneP");
		TuneP->Sumw2();
		TuneP->SetStats(11111);      
		TuneP->Divide(DataTunePNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////
		TH1F *TunePMC = (TH1F*)MCDen->Clone("TunePMC");
		TunePMC->Sumw2();
		TunePMC->Divide(MCTunePNum,MCDen ,1,1,"B");

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
		//TuneP->GetYaxis()->SetRangeUser(0,0.02);
		TuneP->Draw("E0");      

		TunePMC->SetMarkerColor(kBlue-9);
		TunePMC->SetLineColor(kBlue-9);
		TunePMC->SetMarkerStyle(24);
		TunePMC->Draw("E0 SAME");       

		//////////////////////////////////////////////////////////
		/////////////LEGEND///////////////////////////////////////
		//////////////////////////////////////////////////////////
		TLegend * legData = new TLegend(0.75, 0.67, 0.98, 0.77);
		legData->SetHeader("Data 16-17");
		legData->SetFillColor(10);
		legData->AddEntry(TuneP,"TuneP");
		legData -> Draw();

		TLegend * legMC = new TLegend(0.75, 0.57, 0.98, 0.67);
		legMC->SetHeader("MC 2016");
		legMC->SetFillColor(10);
		legMC->AddEntry(TunePMC,"TuneP");
		legMC -> Draw();
	}

	else{
		///////////////////////////////////////////
		//            ALL ALGOS			 //
		///////////////////////////////////////////

		//////////////////////////////////////////
		//GLOBAL
		//////////////////////////////////////////


		/////////////////DATA/////////////////

		TH1 *Glb = (TH1F*)DataDen->Clone("Glb");
		Glb->Sumw2();
		Glb->SetStats(111111);      
		Glb->Divide(DataGlbNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *GlbMC = (TH1F*)MCDen->Clone("GlbMC");
		GlbMC->Sumw2();
		GlbMC->Divide(MCGlbNum,MCDen ,1,1,"B");

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
		Glb->GetYaxis()->SetRangeUser(0,0.02);
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

		/*TH1F *Tkonly = (TH1F*)DataDen->Clone("Tkonly");
		  Tkonly->Sumw2();
		  Tkonly->SetStats(0);      
		  Tkonly->Divide(DataTkonlyNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *TkonlyMC = (TH1F*)MCDen->Clone("TkonlyMC");
		TkonlyMC->Sumw2();
		TkonlyMC->SetStats(0);      
		TkonlyMC->Divide(MCTkonlyNum,MCDen ,1,1,"B");

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

		TH1F *Tpfms = (TH1F*)DataDen->Clone("Tpfms");
		Tpfms->Sumw2();
		Tpfms->SetStats(0);      
		Tpfms->Divide(DataTpfmsNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *TpfmsMC = (TH1F*)MCDen->Clone("TpfmsMC");
		TpfmsMC->Sumw2();
		TpfmsMC->SetStats(0);      
		TpfmsMC->Divide(MCTpfmsNum,MCDen ,1,1,"B");

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

		/*TH1F *Picky = (TH1F*)DataDen->Clone("Picky");
		  Picky->Sumw2();
		  Picky->SetStats(0);      
		  Picky->Divide(DataPickyNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *PickyMC = (TH1F*)MCDen->Clone("PickyMC");
		PickyMC->Sumw2();
		PickyMC->SetStats(0);      
		PickyMC->Divide(MCPickyNum,MCDen ,1,1,"B");

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

		TH1F *DYT = (TH1F*)DataDen->Clone("DYT");
		DYT->Sumw2();
		DYT->SetStats(0);      
		DYT->Divide(DataDYTNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *DYTMC = (TH1F*)MCDen->Clone("DYTMC");
		DYTMC->Sumw2();
		DYTMC->SetStats(0);      
		DYTMC->Divide(MCDYTNum,MCDen ,1,1,"B");

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

		TH1F *TuneP = (TH1F*)DataDen->Clone("TuneP");
		TuneP->Sumw2();
		TuneP->SetStats(0);      
		TuneP->Divide(DataTunePNum,DataDen ,1,1,"B");

		//////////////////MC/////////////////////

		TH1F *TunePMC = (TH1F*)MCDen->Clone("TunePMC");
		TunePMC->Sumw2();
		TunePMC->SetStats(0);      
		TunePMC->Divide(MCTunePNum,MCDen ,1,1,"B");

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

			//TLegend * legData = new TLegend(0.75, 0.63, 0.98, 0.77);
			//all algos
			TLegend * legData = new TLegend(0.75, 0.6, 0.98, 0.77);

		legData->SetHeader("Data 16-17");
		legData->SetFillColor(10);
		legData->AddEntry(Glb,"Global");
		//legData->AddEntry(Tkonly,"Tkonly");
		legData->AddEntry(Tpfms,"TPFMS ");
		//legData->AddEntry(Picky,"Picky");
		//legData->AddEntry(DYT,"DYT ");
		//legData->AddEntry(TuneP,"TuneP");
		legData -> Draw();

		//TLegend * legMC = new TLegend(0.75, 0.49, 0.98, 0.63);
		//all algos
		TLegend * legMC = new TLegend(0.75, 0.43, 0.98, 0.6);

		legMC->SetHeader("MC 2016");
		legMC->SetFillColor(10);
		legMC->AddEntry(GlbMC,"Global");
		//legMC->AddEntry(TkonlyMC,"Tkonly");
		legMC->AddEntry(TpfmsMC,"TPFMS ");
		//legMC->AddEntry(PickyMC,"Picky");
		//legMC->AddEntry(DYTMC,"DYT ");
		//legMC->AddEntry(TunePMC,"TuneP");
		legMC -> Draw();

	}





	/*TLatex t(1,0.01,"2016 data");
	  t.DrawClone("Same");*/

	/*TFile *fout = new TFile("testpt.root ","RECREATE");

	  pthistoGlb->Write();
	  pthistoStalone->Write();

	  fout->Close();*/

}// end of function 
