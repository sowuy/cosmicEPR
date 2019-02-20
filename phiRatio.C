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

float unprop_phi[n_tracks][n_track_pos];
float unprop_pt[n_tracks][n_track_pos];
short unprop_charge[n_tracks][n_track_pos];
float unprop_theta[n_tracks][n_track_pos];
float eta[n_tracks][n_track_pos];
ushort pixel_hits[n_tracks][n_track_pos];
ushort strip_layers[n_tracks][n_track_pos];
////////////////////////////////////////////////////////////////////////////////





//Begining of teh function
void phiRatio(string var="", string tag=""){

	string titleX="";
	string titleLegend="";

	//phi5=

	/*float binMin =-3;
	float binMax =0;
	int binnum = 15;*/

	//eta 
	/*float binMin =-3;
	float binMax =3;
	int binnum = 20;*/

	//pt 

	float bins[]={10,100,200,300,400,500,700,2000};
	int binnum = 7;

	if (var == "pT"){
		titleX = string("p_{t} [GeV]-TuneP ") +tag+ string(" leg tag");

	}
	else if (var == "eta"){
		titleX = string("#eta-TuneP ")+tag+string(" leg tag") ;

	}
	else {
		titleX = string("#phi-TuneP ")+tag+string(" leg tag") ;

	}

	//Declaration of hitsogramm i plan to plot with this code
	//DATA TH1F
	TH1F *dataGlbmu_plus =new TH1F("dataGlb","",binnum,bins);
	TH1F *dataGlbmu_minus =new TH1F("dataGlbmu_minus","",binnum,bins);

	TH1F *dataTkonlymu_plus =new TH1F("dataTkonly","",binnum,bins);
	TH1F *dataTkonlymu_minus =new TH1F("dataTkonlymu_minus","",binnum,bins);

	TH1F *dataTpfmsmu_plus =new TH1F("dataTpfms","",binnum,bins);
	TH1F *dataTpfmsmu_minus =new TH1F("dataTpfmsmu_minus","",binnum,bins);

	TH1F *dataPickymu_plus =new TH1F("dataPicky","",binnum,bins);
	TH1F *dataPickymu_minus =new TH1F("dataPickymu_minus","",binnum,bins);

	TH1F *dataDYTmu_plus =new TH1F("dataDYT","",binnum,bins);
	TH1F *dataDYTmu_minus =new TH1F("dataDYTmu_minus","",binnum,bins);

	TH1F *dataTunePmu_plus =new TH1F("dataTuneP","",binnum,bins);
	TH1F *dataTunePmu_minus =new TH1F("dataTunePmu_minus","",binnum,bins);
	//MC10 TH1F
	TH1F *MCGlbmu_plus =new TH1F("MCGlb","",binnum,bins);
	TH1F *MCGlbmu_minus =new TH1F("MCGlbmu_minus","",binnum,bins);

	TH1F *MCTkonlymu_plus =new TH1F("MCTkonly","",binnum,bins);
	TH1F *MCTkonlymu_minus =new TH1F("MCTkonlymu_minus","",binnum,bins);

	TH1F *MCTpfmsmu_plus =new TH1F("MCTpfms","",binnum,bins);
	TH1F *MCTpfmsmu_minus =new TH1F("MCTpfmsmu_minus","",binnum,bins);

	TH1F *MCPickymu_plus =new TH1F("MCPicky","",binnum,bins);
	TH1F *MCPickymu_minus =new TH1F("MCPickymu_minus","",binnum,bins);

	TH1F *MCDYTmu_plus =new TH1F("MCDYT","",binnum,bins);
	TH1F *MCDYTmu_minus =new TH1F("MCDYTmu_minus","",binnum,bins);

	TH1F *MCTunePmu_plus =new TH1F("MCTuneP","",binnum,bins);
	TH1F *MCTunePmu_minus =new TH1F("MCTunePmu_minus","",binnum,bins);
	//MC100 TH1F
	TH1F *MC100Glbmu_plus =new TH1F("MC100Glb","",binnum,bins);
	TH1F *MC100Glbmu_minus =new TH1F("MC100Glbmu_minus","",binnum,bins);

	TH1F *MC100Tkonlymu_plus =new TH1F("MC100Tkonly","",binnum,bins);
	TH1F *MC100Tkonlymu_minus =new TH1F("MC100Tkonlymu_minus","",binnum,bins);

	TH1F *MC100Tpfmsmu_plus =new TH1F("MC100Tpfms","",binnum,bins);
	TH1F *MC100Tpfmsmu_minus =new TH1F("MC100Tpfmsmu_minus","",binnum,bins);

	TH1F *MC100Pickymu_plus =new TH1F("MC100Picky","",binnum,bins);
	TH1F *MC100Pickymu_minus =new TH1F("MC100Pickymu_minus","",binnum,bins);

	TH1F *MC100DYTmu_plus =new TH1F("MC100DYT","",binnum,bins);
	TH1F *MC100DYTmu_minus =new TH1F("MC100DYTmu_minus","",binnum,bins);

	TH1F *MC100TunePmu_plus =new TH1F("MC100TuneP","",binnum,bins);
	TH1F *MC100TunePmu_minus =new TH1F("MC100TunePmu_minus","",binnum,bins);
	//MC500 TH1F
	TH1F *MC500Glbmu_plus =new TH1F("MC500Glb","",binnum,bins);
	TH1F *MC500Glbmu_minus =new TH1F("MC500Glbmu_minus","",binnum,bins);

	TH1F *MC500Tkonlymu_plus =new TH1F("MC500Tkonly","",binnum,bins);
	TH1F *MC500Tkonlymu_minus =new TH1F("MC500Tkonlymu_minus","",binnum,bins);

	TH1F *MC500Tpfmsmu_plus =new TH1F("MC500Tpfms","",binnum,bins);
	TH1F *MC500Tpfmsmu_minus =new TH1F("MC500Tpfmsmu_minus","",binnum,bins);

	TH1F *MC500Pickymu_plus =new TH1F("MC500Picky","",binnum,bins);
	TH1F *MC500Pickymu_minus =new TH1F("MC500Pickymu_minus","",binnum,bins);

	TH1F *MC500DYTmu_plus =new TH1F("MC500DYT","",binnum,bins);
	TH1F *MC500DYTmu_minus =new TH1F("MC500DYTmu_minus","",binnum,bins);

	TH1F *MC500TunePmu_plus =new TH1F("MC500TuneP","",binnum,bins);
	TH1F *MC500TunePmu_minus =new TH1F("MC500TunePmu_minus","",binnum,bins);

	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");
	TChain *treeMC = new TChain("UTpickedTracks/t");
	TChain *treeMC100 = new TChain("UTpickedTracks/t");
	TChain *treeMC500 = new TChain("UTpickedTracks/t");

	// this is the root file you have input with your tree inside
	//treedata->Add("ROOT_Files/MC2016/MC_2016_P500.root");
	treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");
	treeMC->Add("ROOT_Files/MC2016/MC_P10.root");
	treeMC100->Add("ROOT_Files/MC2016/MC_2016_P100.root");
	treeMC500->Add("ROOT_Files/MC2016/MC_2016_P500.root");


	// the folmu_minusing lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilephion mass in my case for DY events.
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
	treeMC100->SetBranchAddress("unprop_charge",unprop_charge);
	treeMC100->SetBranchAddress("unprop_pt",unprop_pt);
	treeMC100->SetBranchAddress("pixel_hits",pixel_hits);
	treeMC100->SetBranchAddress("strip_layers",strip_layers);
	treeMC100->SetBranchAddress("unprop_theta",unprop_theta);
	treeMC100->SetBranchAddress("unprop_phi",unprop_phi);
	treeMC500->SetBranchAddress("unprop_charge",unprop_charge);
	treeMC500->SetBranchAddress("unprop_pt",unprop_pt);
	treeMC500->SetBranchAddress("pixel_hits",pixel_hits);
	treeMC500->SetBranchAddress("strip_layers",strip_layers);
	treeMC500->SetBranchAddress("unprop_theta",unprop_theta);
	treeMC500->SetBranchAddress("unprop_phi",unprop_phi);


	// This will get the numbers of entries of the tree.

	Long64_t nentries = treedata->GetEntries();
	Long64_t nentriesMC = treeMC->GetEntries();
	Long64_t nentriesMC100 = treeMC->GetEntries();
	Long64_t nentriesMC500 = treeMC->GetEntries();


	//Decalaration of variable not in the tree that i use for the results

	Float_t sameCharge = 0.;
	Float_t goodMuon = 0.;

	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5  && unprop_pt[8][1]>30.){

			if (var == "pT"){


				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					dataGlbmu_plus->Fill(unprop_pt[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					dataGlbmu_minus->Fill(unprop_pt[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					dataTkonlymu_plus->Fill(unprop_pt[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					dataTkonlymu_minus->Fill(unprop_pt[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					dataTpfmsmu_plus->Fill(unprop_pt[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					dataTpfmsmu_minus->Fill(unprop_pt[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					dataPickymu_plus->Fill(unprop_pt[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					dataPickymu_minus->Fill(unprop_pt[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					dataDYTmu_plus->Fill(unprop_pt[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					dataDYTmu_minus->Fill(unprop_pt[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					dataTunePmu_plus->Fill(unprop_pt[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					dataTunePmu_minus->Fill(unprop_pt[8][1]);
				}

			}

			/////////////ETA////////////////////


			else if (var == "eta"){

				for (int i=0;i<n_tracks;i++){
					for (int j=0;j<n_track_pos;j++){
						eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
					}
				}

				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					dataGlbmu_plus->Fill(eta[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					dataGlbmu_minus->Fill(eta[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					dataTkonlymu_plus->Fill(eta[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					dataTkonlymu_minus->Fill(eta[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					dataTpfmsmu_plus->Fill(eta[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					dataTpfmsmu_minus->Fill(eta[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					dataPickymu_plus->Fill(eta[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					dataPickymu_minus->Fill(eta[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					dataDYTmu_plus->Fill(eta[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					dataDYTmu_minus->Fill(eta[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					dataTunePmu_plus->Fill(eta[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					dataTunePmu_minus->Fill(eta[8][1]);
				}

			}

			/////////////PHI////////////////////


			else{
				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					dataGlbmu_plus->Fill(unprop_phi[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					dataGlbmu_minus->Fill(unprop_phi[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					dataTkonlymu_plus->Fill(unprop_phi[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					dataTkonlymu_minus->Fill(unprop_phi[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					dataTpfmsmu_plus->Fill(unprop_phi[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					dataTpfmsmu_minus->Fill(unprop_phi[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					dataPickymu_plus->Fill(unprop_phi[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					dataPickymu_minus->Fill(unprop_phi[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					dataDYTmu_plus->Fill(unprop_phi[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					dataDYTmu_minus->Fill(unprop_phi[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					dataTunePmu_plus->Fill(unprop_phi[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					dataTunePmu_minus->Fill(unprop_phi[8][1]);
				}

			}




		}// end loop p

	}

	//MC 10
	for ( int p=0; p<nentriesMC ;p++){
		// this loop over all the events in your tree

		treeMC->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5  && unprop_pt[8][1]>30.){

			if (var == "pT"){


				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MCGlbmu_plus->Fill(unprop_pt[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MCGlbmu_minus->Fill(unprop_pt[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MCTkonlymu_plus->Fill(unprop_pt[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MCTkonlymu_minus->Fill(unprop_pt[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MCTpfmsmu_plus->Fill(unprop_pt[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MCTpfmsmu_minus->Fill(unprop_pt[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MCPickymu_plus->Fill(unprop_pt[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MCPickymu_minus->Fill(unprop_pt[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MCDYTmu_plus->Fill(unprop_pt[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MCDYTmu_minus->Fill(unprop_pt[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MCTunePmu_plus->Fill(unprop_pt[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MCTunePmu_minus->Fill(unprop_pt[8][1]);
				}

			}

			/////////////ETA////////////////////


			else if (var == "eta"){

				for (int i=0;i<n_tracks;i++){
					for (int j=0;j<n_track_pos;j++){
						eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
					}
				}

				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MCGlbmu_plus->Fill(eta[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MCGlbmu_minus->Fill(eta[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MCTkonlymu_plus->Fill(eta[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MCTkonlymu_minus->Fill(eta[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MCTpfmsmu_plus->Fill(eta[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MCTpfmsmu_minus->Fill(eta[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MCPickymu_plus->Fill(eta[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MCPickymu_minus->Fill(eta[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MCDYTmu_plus->Fill(eta[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MCDYTmu_minus->Fill(eta[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MCTunePmu_plus->Fill(eta[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MCTunePmu_minus->Fill(eta[8][1]);
				}

			}

			/////////////PHI////////////////////


			else{
				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MCGlbmu_plus->Fill(unprop_phi[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MCGlbmu_minus->Fill(unprop_phi[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MCTkonlymu_plus->Fill(unprop_phi[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MCTkonlymu_minus->Fill(unprop_phi[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MCTpfmsmu_plus->Fill(unprop_phi[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MCTpfmsmu_minus->Fill(unprop_phi[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MCPickymu_plus->Fill(unprop_phi[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MCPickymu_minus->Fill(unprop_phi[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MCDYTmu_plus->Fill(unprop_phi[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MCDYTmu_minus->Fill(unprop_phi[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MCTunePmu_plus->Fill(unprop_phi[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MCTunePmu_minus->Fill(unprop_phi[8][1]);
				}
			}
		}// end loop p
	}



	//MC 100
	for ( int p=0; p<nentriesMC100 ;p++){
		// this loop over all the events in your tree

		treeMC100->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5  && unprop_pt[8][1]>30.){

			if (var == "pT"){


				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MC100Glbmu_plus->Fill(unprop_pt[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MC100Glbmu_minus->Fill(unprop_pt[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MC100Tkonlymu_plus->Fill(unprop_pt[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MC100Tkonlymu_minus->Fill(unprop_pt[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MC100Tpfmsmu_plus->Fill(unprop_pt[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MC100Tpfmsmu_minus->Fill(unprop_pt[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MC100Pickymu_plus->Fill(unprop_pt[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MC100Pickymu_minus->Fill(unprop_pt[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MC100DYTmu_plus->Fill(unprop_pt[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MC100DYTmu_minus->Fill(unprop_pt[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MC100TunePmu_plus->Fill(unprop_pt[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MC100TunePmu_minus->Fill(unprop_pt[8][1]);
				}
			}

			/////////////ETA////////////////////


			else if (var == "eta"){

				for (int i=0;i<n_tracks;i++){
					for (int j=0;j<n_track_pos;j++){
						eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
					}
				}

				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MC100Glbmu_plus->Fill(eta[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MC100Glbmu_minus->Fill(eta[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MC100Tkonlymu_plus->Fill(eta[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MC100Tkonlymu_minus->Fill(eta[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MC100Tpfmsmu_plus->Fill(eta[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MC100Tpfmsmu_minus->Fill(eta[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MC100Pickymu_plus->Fill(eta[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MC100Pickymu_minus->Fill(eta[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MC100DYTmu_plus->Fill(eta[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MC100DYTmu_minus->Fill(eta[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MC100TunePmu_plus->Fill(eta[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MC100TunePmu_minus->Fill(eta[8][1]);
				}
			}

			/////////////PHI////////////////////


			else{
				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MC100Glbmu_plus->Fill(unprop_phi[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MC100Glbmu_minus->Fill(unprop_phi[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MC100Tkonlymu_plus->Fill(unprop_phi[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MC100Tkonlymu_minus->Fill(unprop_phi[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MC100Tpfmsmu_plus->Fill(unprop_phi[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MC100Tpfmsmu_minus->Fill(unprop_phi[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MC100Pickymu_plus->Fill(unprop_phi[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MC100Pickymu_minus->Fill(unprop_phi[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MC100DYTmu_plus->Fill(unprop_phi[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MC100DYTmu_minus->Fill(unprop_phi[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MC100TunePmu_plus->Fill(unprop_phi[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MC100TunePmu_minus->Fill(unprop_phi[8][1]);
				}
			}
		}// end loop p
	}



	//MC 500
	for ( int p=0; p<nentriesMC500 ;p++){
		// this loop over all the events in your tree

		treeMC500->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5  && unprop_pt[8][1]>30.){

			if (var == "pT"){


				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MC500Glbmu_plus->Fill(unprop_pt[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MC500Glbmu_minus->Fill(unprop_pt[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MC500Tkonlymu_plus->Fill(unprop_pt[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MC500Tkonlymu_minus->Fill(unprop_pt[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MC500Tpfmsmu_plus->Fill(unprop_pt[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MC500Tpfmsmu_minus->Fill(unprop_pt[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MC500Pickymu_plus->Fill(unprop_pt[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MC500Pickymu_minus->Fill(unprop_pt[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MC500DYTmu_plus->Fill(unprop_pt[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MC500DYTmu_minus->Fill(unprop_pt[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MC500TunePmu_plus->Fill(unprop_pt[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MC500TunePmu_minus->Fill(unprop_pt[8][1]);
				}
			}

			/////////////ETA////////////////////


			else if (var == "eta"){

				for (int i=0;i<n_tracks;i++){
					for (int j=0;j<n_track_pos;j++){
						eta[i][j]=  - log(tan(unprop_theta[i][j]/2)); 
					}
				}

				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MC500Glbmu_plus->Fill(eta[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MC500Glbmu_minus->Fill(eta[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MC500Tkonlymu_plus->Fill(eta[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MC500Tkonlymu_minus->Fill(eta[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MC500Tpfmsmu_plus->Fill(eta[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MC500Tpfmsmu_minus->Fill(eta[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MC500Pickymu_plus->Fill(eta[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MC500Pickymu_minus->Fill(eta[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MC500DYTmu_plus->Fill(eta[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MC500DYTmu_minus->Fill(eta[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MC500TunePmu_plus->Fill(eta[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MC500TunePmu_minus->Fill(eta[8][1]);
				}
			}

			/////////////PHI////////////////////


			else{
				//Algorithm choice


				//global
				if (unprop_charge[0][1] > 0) {
					MC500Glbmu_plus->Fill(unprop_phi[0][1]);
				}
				if (unprop_charge[0][1] < 0) {
					MC500Glbmu_minus->Fill(unprop_phi[0][1]);
				}
				//Tkonly
				if (unprop_charge[2][1] > 0) {
					MC500Tkonlymu_plus->Fill(unprop_phi[2][0]);
				}
				if (unprop_charge[2][1] < 0) {
					MC500Tkonlymu_minus->Fill(unprop_phi[2][1]);
				}
				//Tpfms
				if (unprop_charge[3][1] > 0) {
					MC500Tpfmsmu_plus->Fill(unprop_phi[3][1]);
				}
				if (unprop_charge[3][1] < 0) {
					MC500Tpfmsmu_minus->Fill(unprop_phi[3][1]);
				}
				//Picky
				if (unprop_charge[4][1] > 0) {
					MC500Pickymu_plus->Fill(unprop_phi[4][1]);
				}
				if (unprop_charge[4][1] < 0) {
					MC500Pickymu_minus->Fill(unprop_phi[4][1]);
				}
				//DYT
				if (unprop_charge[5][1] > 0) {
					MC500DYTmu_plus->Fill(unprop_phi[5][1]);
				}
				if (unprop_charge[5][1] < 0) {
					MC500DYTmu_minus->Fill(unprop_phi[5][1]);
				}
				//TuneP
				if (unprop_charge[8][1] > 0) {
					MC500TunePmu_plus->Fill(unprop_phi[8][1]);
				}
				if (unprop_charge[8][1] < 0) {
					MC500TunePmu_minus->Fill(unprop_phi[8][1]);
				}
			}
		}// end loop p
	}

	TCanvas *c = new TCanvas("c", "canvas", 700, 600);
	Double_t norm = 1;


	// mu_plusper plot will be in pad5a
	TPad *pad5a = new TPad("pad3a", "pad3a", 0, 0.19, 1, 1.0);
	//pad5a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad5a->SetGridx();         // Vertical grid
	pad5a->Draw();             // Draw the mu_plusper pad: pad1
	pad5a->cd();               // pad1 becomes the current pad
	dataTunePmu_plus->SetStats(111);          // No statistics on mu_plusper plot
	

	//weighting of MC
	//mu_plus
	TAxis *axis =MCTunePmu_plus->GetXaxis();
  	int bmin1 = axis->FindBin(100); //in your case xmin=-1.5
  	int bmax1 = axis->FindBin(2000); //in your case xmax=0.8	

	double num100 = MCTunePmu_plus->Integral(bmin1,bmax1);
	double den100 = MC100TunePmu_plus->Integral();
	cout << "den=" << den100 << "   " << "num=" << num100 << endl;
	double scale100 = num100/den100;
	cout << "ratio=" << scale100 << endl;
	MC100TunePmu_plus->Scale(scale100);
	
  	int bmin2 = axis->FindBin(500); //in your case xmin=-1.5
  	int bmax2 = axis->FindBin(2000); //in your case xmax=0.8	
	double num500 = MCTunePmu_plus->Integral(bmin2,bmax2);
	double den500 = MC500TunePmu_plus->Integral();
	cout << "den2=" << den500 << "   " << "num2=" << num500 << endl;

	double scale500 = num500/den500;
	cout << "ratio2=" << scale500 << endl;

	MC500TunePmu_plus->Scale(scale500);
	


	//Set bin content of MC10, MC100 and MC500
	
	int n1 = 2;
	int n2 = 6;	
	TH1F *MCtotmu_plus = (TH1F*)MCTunePmu_plus->Clone();
	MCtotmu_plus->Reset("ICES,M");
	for (int i=1;i<n1;i++){
	MCtotmu_plus->SetBinContent(i,MCTunePmu_plus->GetBinContent(i));
		MCtotmu_plus->SetBinError(i,MCTunePmu_plus->GetBinError(i));
	}
	for (int i=n1;i<n2;i++){
		MCtotmu_plus->SetBinContent(i,MC100TunePmu_plus->GetBinContent(i));
		MCtotmu_plus->SetBinError(i,MC100TunePmu_plus->GetBinError(i));
	}
	for (int i=n2;i<8;i++){
		MCtotmu_plus->SetBinContent(i,MC100TunePmu_plus->GetBinContent(i));
		MCtotmu_plus->SetBinError(i,MC100TunePmu_plus->GetBinError(i));
	}

	//mu_minus
	TAxis *axismu_minus =MCTunePmu_minus->GetXaxis();
  	int bmin1mu_minus = axismu_minus->FindBin(100); //in your case xmin=-1.5
  	int bmax1mu_minus = axismu_minus->FindBin(2000); //in your case xmax=0.8	

	double num100mu_minus = MCTunePmu_minus->Integral(bmin1mu_minus,bmax1mu_minus);
	double den100mu_minus = MC100TunePmu_minus->Integral();
	double scale100mu_minus = num100mu_minus/den100mu_minus;
	MC100TunePmu_minus->Scale(scale100mu_minus);
	
  	int bmin2mu_minus = axismu_minus->FindBin(500); //in your case xmin=-1.5
  	int bmax2mu_minus = axismu_minus->FindBin(2000); //in your case xmax=0.8	
	double num500mu_minus = MCTunePmu_minus->Integral(bmin2mu_minus,bmax2mu_minus);
	double den500mu_minus = MC500TunePmu_minus->Integral();
	double scale500mu_minus = num500mu_minus/den500mu_minus;

	MC500TunePmu_minus->Scale(scale500mu_minus);
	


	//Set bin content of MC10, MC100 and MC500
	
	TH1F *MCtotmu_minus = (TH1F*)MCTunePmu_minus->Clone();
	MCtotmu_minus->Reset("ICES,M");
	for (int i=1;i<n1;i++){
	MCtotmu_minus->SetBinContent(i,MCTunePmu_minus->GetBinContent(i));
		MCtotmu_minus->SetBinError(i,MCTunePmu_minus->GetBinError(i));
	}
	for (int i=n1;i<n2;i++){
		MCtotmu_minus->SetBinContent(i,MC100TunePmu_minus->GetBinContent(i));
		MCtotmu_minus->SetBinError(i,MC100TunePmu_minus->GetBinError(i));
	}
	for (int i=n2;i<8;i++){
		MCtotmu_minus->SetBinContent(i,MC100TunePmu_minus->GetBinContent(i));
		MCtotmu_minus->SetBinError(i,MC100TunePmu_minus->GetBinError(i));
	}

	//renormalize histograms :
	dataTunePmu_plus->Sumw2();
	dataTunePmu_plus->Scale(norm/dataTunePmu_plus->Integral(), "width");
	dataTunePmu_minus->Sumw2();
	dataTunePmu_minus->Scale(norm/dataTunePmu_minus->Integral(), "width");
	MCtotmu_plus->Sumw2();
	MCtotmu_plus->Scale(norm/MCtotmu_plus->Integral(), "width");
	MCtotmu_minus->Sumw2();
	MCtotmu_minus->Scale(norm/MCtotmu_minus->Integral(), "width");

	// h1 settings
	dataTunePmu_plus->SetXTitle(titleX.c_str());
	dataTunePmu_plus->SetLineColor(kBlue);
	dataTunePmu_plus->SetLineWidth(2);
	dataTunePmu_plus->GetXaxis()->SetTitleSize(0.05);
	//dataTunePmu_plus->GetYaxis()->SetRangeUser(0,1.5);

	dataTunePmu_plus->SetMarkerColor(kBlue);
	dataTunePmu_plus->SetMarkerStyle(20);
	MCtotmu_plus->SetLineColor(kBlue-9);
	MCtotmu_plus->SetLineWidth(2);
	MCtotmu_plus->SetMarkerColor(kBlue-9);
	MCtotmu_plus->SetMarkerStyle(24);

	// Y axis h1 plot settings
	dataTunePmu_plus->GetYaxis()->SetTitleSize(20);
	dataTunePmu_plus->GetYaxis()->SetTitleFont(43);
	dataTunePmu_plus->GetYaxis()->SetTitleOffset(1.);
	// h5 settings
	dataTunePmu_minus->SetLineColor(kRed);
	dataTunePmu_minus->SetLineWidth(2);
	dataTunePmu_minus->SetMarkerColor(kRed);
	dataTunePmu_minus->SetMarkerStyle(20);
	MCtotmu_minus->SetLineColor(kRed-9);
	MCtotmu_minus->SetLineWidth(2);
	MCtotmu_minus->SetMarkerColor(kRed-9);
	MCtotmu_minus->SetMarkerStyle(24);

	//DRAW
	dataTunePmu_plus->Draw("E1");               
	dataTunePmu_minus->Draw("E1 same");        
	MCtotmu_plus->Draw("E1 same");      
	MCtotmu_minus->Draw("E1 same");
	//LEGEND
	TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg5->SetHeader("TuneP-2016+2017 data");
	leg5->SetFillColor(10);
	leg5->AddEntry(dataTunePmu_plus,"#mu^{+}");
	leg5->AddEntry(dataTunePmu_minus,"#mu^{-}");
	leg5 -> Draw();
	TLegend * legMC = new TLegend(0.6, 0.43, 0.98, 0.6);
	legMC->SetHeader("TuneP-MC 2016 combined");
	legMC->SetFillColor(10);
	legMC->AddEntry(MCtotmu_plus,"#mu^{+}");
	legMC->AddEntry(MCtotmu_minus,"#mu^{-}");
	legMC -> Draw();




	// mu_minuser plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad5b
	TPad *pad5b = new TPad("pad5b", "pad5b", 0, 0, 1, 0.16);
	pad5b->SetTopMargin(0);
	pad5b->SetBottomMargin(0.2);
	pad5b->SetGridx(); // vertical grid
	pad5b->Draw();
	pad5b->cd();       // pad2 becomes the current pad
	
	// Define the ratio plot
	TH1F *h5 = (TH1F*)dataTunePmu_plus->Clone("h5");
	h5->SetLineColor(kBlack);
	h5->Sumw2();
	h5->SetStats(0);      // No statistics on mu_minuser plot
	h5->Divide(dataTunePmu_plus,MCtotmu_minus ,1,1,"B");
	h5->SetMarkerStyle(21);
	h5->SetMarkerColor(kBlue);
	h5->SetLineColor(kBlue);

	h5->Draw("E1");       // Draw the ratio plot
	
	

	// Define the ratio plot - mu_minus
	TH1F *h5mu_minus = (TH1F*)dataTunePmu_minus->Clone("h5mu_minus");
	h5mu_minus->SetLineColor(kBlack);
	h5mu_minus->Sumw2();
	h5mu_minus->SetStats(0);      // No statistics on mu_minuser plot
	h5mu_minus->Divide(dataTunePmu_minus,MCtotmu_minus ,1,1,"B");
	h5mu_minus->SetMarkerStyle(21);
	h5mu_minus->SetMarkerColor(kRed);
	h5mu_minus->SetLineColor(kRed);


	h5mu_minus->Draw("E1 same");       // Draw the ratio plot

	// Ratio plot (h5) settings
	h5->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h5->GetYaxis()->SetTitle("data/MC");
	h5->GetYaxis()->SetNdivisions(505);
	h5->GetYaxis()->SetTitleSize(20);
	h5->GetYaxis()->SetTitleFont(43);
	h5->GetYaxis()->SetTitleOffset(1.);
	h5->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h5->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h5->GetXaxis()->SetLabelSize(15);
	h5->GetXaxis()->SetTitle("");

	h5->SetStats(0);      // No statistics on mu_minuser plot
	//h5->GetYaxis()->SetRangeUser(-2,2);


































	//h5->GetYaxis()->SetRangeUser(0.8,1.2);
	// Define the Canvas
	/*TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
	  c->Divide(3,2);
	  c->cd(1);
	// mu_plusper plot will be in pad0a
	TPad *pad0a = new TPad("pad0a", "pad0a", 0, 0.3, 1, 1.0);
	//pad0a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad0a->SetGridx();         // Vertical grid
	pad0a->Draw();             // Draw the mu_plusper pad: pad1
	pad0a->cd();               // pad1 becomes the current pad
	//dataGlbmu_plus->SetStats(0);          // No statistics on mu_plusper plot
	dataGlbmu_plus->Draw("E1");               // Draw h1
	dataGlbmu_minus->Draw("E1 same");         // Draw h2 on top of h1
	// Do not draw the Y axis label on the mu_plusper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg0 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg0->SetHeader("Global fit");
	leg0->SetFillColor(10);
	leg0->AddEntry(dataGlbmu_plus,"#mu^{+} ");
	leg0->AddEntry(dataGlbmu_minus,"#mu^{-}");
	leg0 -> Draw();


	// mu_minuser plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad0b
	TPad *pad0b = new TPad("pad0b", "pad0b", 0, 0.56, 0.33, 0.66);
	pad0b->SetTopMargin(0);
	pad0b->SetBottomMargin(0.2);
	pad0b->SetGridx(); // vertical grid
	pad0b->Draw();
	pad0b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h0 = (TH1F*)dataGlbmu_plus->Clone("h0");
	h0->SetLineColor(kBlack);
	h0->Sumw2();
	h0->SetStats(0);      // No statistics on mu_minuser plot
	h0->Divide(dataGlbmu_plus,dataGlbmu_minus ,1,1,"B");
	h0->SetMarkerStyle(21);
	h0->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataGlbmu_plus->SetXTitle("#phi ");
	dataGlbmu_plus->SetLineColor(kBlue+1);
	dataGlbmu_plus->SetLineWidth(2);
	// Y axis h1 plot settings
	dataGlbmu_plus->GetYaxis()->SetTitleSize(20);
	dataGlbmu_plus->GetYaxis()->SetTitleFont(43);
	dataGlbmu_plus->GetYaxis()->SetTitleOffset(1.55);
	// h2 settings
	dataGlbmu_minus->SetLineColor(kRed);
	dataGlbmu_minus->SetLineWidth(2);
	// Ratio plot (h0) settings
	h0->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h0->GetYaxis()->SetTitle("mu+/mu-");
	h0->GetYaxis()->SetNdivisions(505);
	h0->GetYaxis()->SetTitleSize(20);
	h0->GetYaxis()->SetTitleFont(43);
	h0->GetYaxis()->SetTitleOffset(1.55);
	h0->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h0->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h0->GetXaxis()->SetTitleSize(20);
	h0->GetXaxis()->SetTitleFont(43);
	h0->GetXaxis()->SetTitleOffset(4.);
	h0->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h0->GetXaxis()->SetLabelSize(15);
	h0->SetStats(0);      // No statistics on mu_minuser plot
	//h0->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(2);

	// mu_plusper plot will be in pad1a
	TPad *pad1a = new TPad("pad1a", "pad1a", 0, 0.3, 1, 1.0);
	//pad1a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad1a->SetGridx();         // Vertical grid
	pad1a->Draw();             // Draw the mu_plusper pad: pad1
	pad1a->cd();               // pad1 becomes the current pad
	//dataTkonlymu_plus->SetStats(0);          // No statistics on mu_plusper plot
	dataTkonlymu_plus->Draw("E1");               // Draw h1
	dataTkonlymu_minus->Draw("E1 same");         // Draw h2 on top of h1
	// Do not draw the Y axis label on the mu_plusper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg1 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg1->SetHeader("Tkonly");
	leg1->SetFillColor(10);
	leg1->AddEntry(dataTkonlymu_plus,"#mu^{+} ");
	leg1->AddEntry(dataTkonlymu_minus,"#mu^{-}");
	leg1 -> Draw();


	// mu_minuser plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad1b
	TPad *pad1b = new TPad("pad1b", "pad1b", 0.33, 0.56, 0.66,0.66);
	pad1b->SetTopMargin(0);
	pad1b->SetBottomMargin(0.2);
	pad1b->SetGridx(); // vertical grid
	pad1b->Draw();
	pad1b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h1 = (TH1F*)dataTkonlymu_plus->Clone("h1");
	h1->SetLineColor(kBlack);
	h1->Sumw2();
	h1->SetStats(0);      // No statistics on mu_minuser plot
	h1->Divide(dataTkonlymu_plus,dataTkonlymu_minus ,1,1,"B");
	h1->SetMarkerStyle(21);
	h1->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataTkonlymu_plus->SetXTitle("#phi ");
	dataTkonlymu_plus->SetLineColor(kBlue+1);
	dataTkonlymu_plus->SetLineWidth(2);
	// Y axis h1 plot settings
	dataTkonlymu_plus->GetYaxis()->SetTitleSize(20);
	dataTkonlymu_plus->GetYaxis()->SetTitleFont(43);
	dataTkonlymu_plus->GetYaxis()->SetTitleOffset(1.55);
	// h2 settings
	dataTkonlymu_minus->SetLineColor(kRed);
	dataTkonlymu_minus->SetLineWidth(2);
	// Ratio plot (h1) settings
	h1->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h1->GetYaxis()->SetTitle("mu+/mu-");
	h1->GetYaxis()->SetNdivisions(505);
	h1->GetYaxis()->SetTitleSize(20);
	h1->GetYaxis()->SetTitleFont(43);
	h1->GetYaxis()->SetTitleOffset(1.55);
	h1->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h1->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h1->GetXaxis()->SetTitleSize(20);
	h1->GetXaxis()->SetTitleFont(43);
	h1->GetXaxis()->SetTitleOffset(4.);
	h1->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h1->GetXaxis()->SetLabelSize(15);
	h1->SetStats(0);      // No statistics on mu_minuser plot
	//h1->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(3);
	// mu_plusper plot will be in pad2ba
	TPad *pad2a = new TPad("pad2a", "pad2a", 0, 0.3, 1, 1.0);
	//pad2a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad2a->SetGridx();         // Vertical grid
	pad2a->Draw();             // Draw the mu_plusper pad: pad1
	pad2a->cd();               // pad1 becomes the current pad
	//dataTpfmsmu_plus->SetStats(0);          // No statistics on mu_plusper plot
	dataTpfmsmu_plus->Draw("E1");               // Draw h1
	dataTpfmsmu_minus->Draw("E1 same");         // Draw h2 on top of h1
	// Do not draw the Y axis label on the mu_plusper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg2 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg2->SetHeader("TPFMS");
	leg2->SetFillColor(10);
	leg2->AddEntry(dataTpfmsmu_plus,"#mu^{+} ");
	leg2->AddEntry(dataTpfmsmu_minus,"#mu^{-}");
	leg2 -> Draw();


	// mu_minuser plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad2b
	TPad *pad2b = new TPad("pad2b", "pad2b", 0.66, 0.56, 1, 0.66);
	pad2b->SetTopMargin(0);
	pad2b->SetBottomMargin(0.2);
	pad2b->SetGridx(); // vertical grid
	pad2b->Draw();
	pad2b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h2 = (TH1F*)dataTpfmsmu_plus->Clone("h2");
	h2->SetLineColor(kBlack);
	h2->Sumw2();
	h2->SetStats(0);      // No statistics on mu_minuser plot
	h2->Divide(dataTpfmsmu_plus,dataTpfmsmu_minus ,1,1,"B");
	h2->SetMarkerStyle(21);
	h2->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataTpfmsmu_plus->SetXTitle("#phi ");
	dataTpfmsmu_plus->SetLineColor(kBlue+1);
	dataTpfmsmu_plus->SetLineWidth(2);
	// Y axis h1 plot settings
	dataTpfmsmu_plus->GetYaxis()->SetTitleSize(20);
	dataTpfmsmu_plus->GetYaxis()->SetTitleFont(43);
	dataTpfmsmu_plus->GetYaxis()->SetTitleOffset(1.55);
	// h2 settings
	dataTpfmsmu_minus->SetLineColor(kRed);
	dataTpfmsmu_minus->SetLineWidth(2);
	// Ratio plot (h2) settings
	h2->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h2->GetYaxis()->SetTitle("mu+/mu-");
	h2->GetYaxis()->SetNdivisions(505);
	h2->GetYaxis()->SetTitleSize(20);
	h2->GetYaxis()->SetTitleFont(43);
	h2->GetYaxis()->SetTitleOffset(1.55);
	h2->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h2->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h2->GetXaxis()->SetTitleSize(20);
	h2->GetXaxis()->SetTitleFont(43);
	h2->GetXaxis()->SetTitleOffset(4.);
	h2->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h2->GetXaxis()->SetLabelSize(15);
	h2->SetStats(0);      // No statistics on mu_minuser plot
	//h2->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(4);
	// mu_plusper plot will be in pad3a
	TPad *pad3a = new TPad("pad3a", "pad3a",0, 0.3, 1, 1.0);
	//pad3a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad3a->SetGridx();         // Vertical grid
	pad3a->Draw();             // Draw the mu_plusper pad: pad1
	pad3a->cd();               // pad1 becomes the current pad
	//dataPickymu_plus->SetStats(0);          // No statistics on mu_plusper plot
	dataPickymu_plus->Draw("E1");               // Draw h1
	dataPickymu_minus->Draw("E1 same");         // Draw h3 on top of h1
	// Do not draw the Y axis label on the mu_plusper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg3 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg3->SetHeader("Picky fit");
	leg3->SetFillColor(10);
	leg3->AddEntry(dataPickymu_plus,"#mu^{+} ");
	leg3->AddEntry(dataPickymu_minus,"#mu^{-}");
	leg3 -> Draw();


	// mu_minuser plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad3b
	TPad *pad3b = new TPad("pad3b", "pad3b", 0, 0.06, 0.33, 0.16);
	pad3b->SetTopMargin(0);
	pad3b->SetBottomMargin(0.2);
	pad3b->SetGridx(); // vertical grid
	pad3b->Draw();
	pad3b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h3 = (TH1F*)dataPickymu_plus->Clone("h3");
	h3->SetLineColor(kBlack);
	h3->Sumw2();
	h3->SetStats(0);      // No statistics on mu_minuser plot
	h3->Divide(dataPickymu_plus,dataPickymu_minus ,1,1,"B");
	h3->SetMarkerStyle(21);
	h3->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataPickymu_plus->SetXTitle("#phi ");
	dataPickymu_plus->SetLineColor(kBlue+1);
	dataPickymu_plus->SetLineWidth(2);
	// Y axis h1 plot settings
	dataPickymu_plus->GetYaxis()->SetTitleSize(20);
	dataPickymu_plus->GetYaxis()->SetTitleFont(43);
	dataPickymu_plus->GetYaxis()->SetTitleOffset(1.55);
	// h3 settings
	dataPickymu_minus->SetLineColor(kRed);
	dataPickymu_minus->SetLineWidth(2);
	// Ratio plot (h3) settings
	h3->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h3->GetYaxis()->SetTitle("mu+/mu-");
	h3->GetYaxis()->SetNdivisions(505);
	h3->GetYaxis()->SetTitleSize(20);
	h3->GetYaxis()->SetTitleFont(43);
	h3->GetYaxis()->SetTitleOffset(1.55);
	h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h3->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h3->GetXaxis()->SetTitleSize(20);
	h3->GetXaxis()->SetTitleFont(43);
	h3->GetXaxis()->SetTitleOffset(4.);
	h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h3->GetXaxis()->SetLabelSize(15);
	h3->SetStats(0);      // No statistics on mu_minuser plot
	//h3->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(5);
	// mu_plusper plot will be in pad4a
	TPad *pad4a = new TPad("pad4a", "pad4a", 0, 0.3, 1, 1.0);
	//pad4a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad4a->SetGridx();         // Vertical grid
	pad4a->Draw();             // Draw the mu_plusper pad: pad1
	pad4a->cd();               // pad1 becomes the current pad
	//dataDYTmu_plus->SetStats(0);          // No statistics on mu_plusper plot
	dataDYTmu_plus->Draw("E1");               // Draw h1
	dataDYTmu_minus->Draw("E1 same");         // Draw h4 on top of h1
	// Do not draw the Y axis label on the mu_plusper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg4 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg4->SetHeader("DYT");
	leg4->SetFillColor(10);
	leg4->AddEntry(dataDYTmu_plus,"#mu^{+} ");
	leg4->AddEntry(dataDYTmu_minus,"#mu^{-}");
	leg4 -> Draw();


	// mu_minuser plot will be in pad
	c->cd();          // Go ba to the main canvas before defining pad4b
	TPad *pad4b = new TPad("pad4b", "pad4b", 0.33, 0.06, 0.66,0.16);
	pad4b->SetTopMargin(0);
	pad4b->SetBottomMargin(0.2);
	pad4b->SetGridx(); // vertical grid
	pad4b->Draw();
	pad4b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h4 = (TH1F*)dataDYTmu_plus->Clone("h4");
	h4->SetLineColor(kBlack);
	h4->Sumw2();
	h4->SetStats(0);      // No statistics on mu_minuser plot
	h4->Divide(dataDYTmu_plus,dataDYTmu_minus ,1,1,"B");
	h4->SetMarkerStyle(21);
	h4->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataDYTmu_plus->SetXTitle("#phi ");
	dataDYTmu_plus->SetLineColor(kBlue+1);
	dataDYTmu_plus->SetLineWidth(2);
	// Y axis h1 plot settings
	dataDYTmu_plus->GetYaxis()->SetTitleSize(20);
	dataDYTmu_plus->GetYaxis()->SetTitleFont(43);
	dataDYTmu_plus->GetYaxis()->SetTitleOffset(1.55);
	// h4 settings
	dataDYTmu_minus->SetLineColor(kRed);
	dataDYTmu_minus->SetLineWidth(2);
	// Ratio plot (h4) settings
	h4->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h4->GetYaxis()->SetTitle("mu+/mu-");
	h4->GetYaxis()->SetNdivisions(505);
	h4->GetYaxis()->SetTitleSize(20);
	h4->GetYaxis()->SetTitleFont(43);
	h4->GetYaxis()->SetTitleOffset(1.55);
	h4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h4->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h4->GetXaxis()->SetTitleSize(20);
	h4->GetXaxis()->SetTitleFont(43);
	h4->GetXaxis()->SetTitleOffset(4.);
	h4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h4->GetXaxis()->SetLabelSize(15);
	h4->SetStats(0);      // No statistics on mu_minuser plot
	//h4->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(6);
	// mu_plusper plot will be in pad5a
	TPad *pad5a = new TPad("pad3a", "pad3a", 0, 0.3, 1, 1.0);
	//pad5a->SetBottomMargin(0); // mu_plusper and mu_minuser plot are joined
	pad5a->SetGridx();         // Vertical grid
	pad5a->Draw();             // Draw the mu_plusper pad: pad1
	pad5a->cd();               // pad1 becomes the current pad
	//dataTunePmu_plus->SetStats(0);          // No statistics on mu_plusper plot
	dataTunePmu_plus->Draw("E1");               // Draw h1
	dataTunePmu_minus->Draw("E1 same");         // Draw h5 on top of h1
	// Do not draw the Y axis label on the mu_plusper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg5->SetHeader("TuneP");
	leg5->SetFillColor(10);
	leg5->AddEntry(dataTunePmu_plus,"#mu^{+} ");
	leg5->AddEntry(dataTunePmu_minus,"#mu^{-}");
	leg5 -> Draw();


	// mu_minuser plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad5b
	TPad *pad5b = new TPad("pad5b", "pad5b", 0.66, 0.06, 1, 0.16);
	pad5b->SetTopMargin(0);
	pad5b->SetBottomMargin(0.2);
	pad5b->SetGridx(); // vertical grid
	pad5b->Draw();
	pad5b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h5 = (TH1F*)dataTunePmu_plus->Clone("h5");
	h5->SetLineColor(kBlack);
	h5->Sumw2();
	h5->SetStats(0);      // No statistics on mu_minuser plot
	h5->Divide(dataTunePmu_plus,dataTunePmu_minus ,1,1,"B");
	h5->SetMarkerStyle(21);
	h5->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataTunePmu_plus->SetXTitle("#phi ");
	dataTunePmu_plus->SetLineColor(kBlue+1);
	dataTunePmu_plus->SetLineWidth(2);
	// Y axis h1 plot settings
	dataTunePmu_plus->GetYaxis()->SetTitleSize(20);
	dataTunePmu_plus->GetYaxis()->SetTitleFont(43);
	dataTunePmu_plus->GetYaxis()->SetTitleOffset(1.55);
	// h5 settings
	dataTunePmu_minus->SetLineColor(kRed);
	dataTunePmu_minus->SetLineWidth(2);
	// Ratio plot (h5) settings
	h5->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h5->GetYaxis()->SetTitle("mu+/mu-");
	h5->GetYaxis()->SetNdivisions(505);
	h5->GetYaxis()->SetTitleSize(20);
	h5->GetYaxis()->SetTitleFont(43);
	h5->GetYaxis()->SetTitleOffset(1.55);
	h5->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h5->GetYaxis()->SetLabelSize(15);
	// X axis ratio plot settings
	h5->GetXaxis()->SetTitleSize(20);
	h5->GetXaxis()->SetTitleFont(43);
	h5->GetXaxis()->SetTitleOffset(4.);
	h5->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
	h5->GetXaxis()->SetLabelSize(15);
	h5->SetStats(0);      // No statistics on mu_minuser plot
	//h5->GetYaxis()->SetRangeUser(0.8,1.2);*/



	/*TFile *fout = new TFile("testphi.root ","RECREATE");

	  dataGlb->Write();
	  dataStalone->Write();

	  fout->Close();*/

}// end of function 
