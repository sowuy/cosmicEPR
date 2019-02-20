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
void phiDistri(string var=""){

	string titleX="";
	string titleLegend="";
	//phi
	/*float binMin =-3;
	float binMax =0;
	int binnum = 15;

	//eta 
	float binMin =-3;
	float binMax =3;
	int binnum = 20;*/
	
	//pt 

	float bins[]={10,100,200,300,400,500,700,2000};
	int binnum = 7;
	//Declaration of histogramm i plan to plot with this code	
	if (var == "pT"){
		titleX = string("p_{t} [GeV]-TuneP") ;

	}
	else if (var == "eta"){
		titleX = string("#eta-TuneP") ;

	}
	else {
		titleX = string("#phi-TuneP") ;

	}


	//Declaration of hitsogramm i plan to plot with this code
	//DATA TH1F
	TH1F *dataGlbUP =new TH1F("dataGlb","",binnum,bins);
	TH1F *dataGlbLOW =new TH1F("dataGlbLOW","",binnum,bins);

	TH1F *dataTkonlyUP =new TH1F("dataTkonly","",binnum,bins);
	TH1F *dataTkonlyLOW =new TH1F("dataTkonlyLOW","",binnum,bins);

	TH1F *dataTpfmsUP =new TH1F("dataTpfms","",binnum,bins);
	TH1F *dataTpfmsLOW =new TH1F("dataTpfmsLOW","",binnum,bins);

	TH1F *dataPickyUP =new TH1F("dataPicky","",binnum,bins);
	TH1F *dataPickyLOW =new TH1F("dataPickyLOW","",binnum,bins);

	TH1F *dataDYTUP =new TH1F("dataDYT","",binnum,bins);
	TH1F *dataDYTLOW =new TH1F("dataDYTLOW","",binnum,bins);

	TH1F *dataTunePUP =new TH1F("dataTuneP","",binnum,bins);
	TH1F *dataTunePLOW =new TH1F("dataTunePLOW","",binnum,bins);

	//MC10 TH1F
	TH1F *MCGlbUP =new TH1F("MCGlb","",binnum,bins);
	TH1F *MCGlbLOW =new TH1F("MCGlbLOW","",binnum,bins);

	TH1F *MCTkonlyUP =new TH1F("MCTkonly","",binnum,bins);
	TH1F *MCTkonlyLOW =new TH1F("MCTkonlyLOW","",binnum,bins);

	TH1F *MCTpfmsUP =new TH1F("MCTpfms","",binnum,bins);
	TH1F *MCTpfmsLOW =new TH1F("MCTpfmsLOW","",binnum,bins);

	TH1F *MCPickyUP =new TH1F("MCPicky","",binnum,bins);
	TH1F *MCPickyLOW =new TH1F("MCPickyLOW","",binnum,bins);

	TH1F *MCDYTUP =new TH1F("MCDYT","",binnum,bins);
	TH1F *MCDYTLOW =new TH1F("MCDYTLOW","",binnum,bins);

	TH1F *MCTunePUP =new TH1F("MCTuneP","",binnum,bins);
	TH1F *MCTunePLOW =new TH1F("MCTunePLOW","",binnum,bins);

	//MC100 TH1F
	TH1F *MC100GlbUP =new TH1F("MC100Glb","",binnum,bins);
	TH1F *MC100GlbLOW =new TH1F("MC100GlbLOW","",binnum,bins);

	TH1F *MC100TkonlyUP =new TH1F("MC100Tkonly","",binnum,bins);
	TH1F *MC100TkonlyLOW =new TH1F("MC100TkonlyLOW","",binnum,bins);

	TH1F *MC100TpfmsUP =new TH1F("MC100Tpfms","",binnum,bins);
	TH1F *MC100TpfmsLOW =new TH1F("MC100TpfmsLOW","",binnum,bins);

	TH1F *MC100PickyUP =new TH1F("MC100Picky","",binnum,bins);
	TH1F *MC100PickyLOW =new TH1F("MC100PickyLOW","",binnum,bins);

	TH1F *MC100DYTUP =new TH1F("MC100DYT","",binnum,bins);
	TH1F *MC100DYTLOW =new TH1F("MC100DYTLOW","",binnum,bins);

	TH1F *MC100TunePUP =new TH1F("MC100TuneP","",binnum,bins);
	TH1F *MC100TunePLOW =new TH1F("MC100TunePLOW","",binnum,bins);


	//MC00 TH1F
	TH1F *MC500GlbUP =new TH1F("MC500Glb","",binnum,bins);
	TH1F *MC500GlbLOW =new TH1F("MC500GlbLOW","",binnum,bins);

	TH1F *MC500TkonlyUP =new TH1F("MC500Tkonly","",binnum,bins);
	TH1F *MC500TkonlyLOW =new TH1F("MC500TkonlyLOW","",binnum,bins);

	TH1F *MC500TpfmsUP =new TH1F("MC500Tpfms","",binnum,bins);
	TH1F *MC500TpfmsLOW =new TH1F("MC500TpfmsLOW","",binnum,bins);

	TH1F *MC500PickyUP =new TH1F("MC500Picky","",binnum,bins);
	TH1F *MC500PickyLOW =new TH1F("MC500PickyLOW","",binnum,bins);

	TH1F *MC500DYTUP =new TH1F("MC500DYT","",binnum,bins);
	TH1F *MC500DYTLOW =new TH1F("MC500DYTLOW","",binnum,bins);

	TH1F *MC500TunePUP =new TH1F("MC500TuneP","",binnum,bins);
	TH1F *MC500TunePLOW =new TH1F("MC500TunePLOW","",binnum,bins);


	// the next line is to link the tree you have

	TChain *treedata = new TChain("UTpickedTracks/t");
	TChain *treeMC = new TChain("UTpickedTracks/t");
	TChain *treeMC100 = new TChain("UTpickedTracks/t");
	TChain *treeMC500 = new TChain("UTpickedTracks/t");


	// this is the root file you have input with your tree inside
	//treedata->Add("ROOT_Files/allVersions/cosmic_data_16_17_18.root");
	treedata->Add("ROOT_Files/cosmic_data_2016_2017/cosmic_data_16_17.root");
	//treedata->Add ("ROOT_Files/resolution_cosmics.root");
	//treeMC->Add ("ROOT_Files/resolution_cosmics.root");
	//treeMC->Add("ROOT_Files/MC2016/cosmic_MC_2016.root");
	treeMC->Add("ROOT_Files/MC2016/MC_P10.root");
	treeMC100->Add("ROOT_Files/MC2016/MC_2016_P100.root");
	treeMC500->Add("ROOT_Files/MC2016/MC_2016_P500.root");

	// the following lines are to extract the branch of the trees, when there is a & it means that there is only one entry per event, like for run, lumi, event, dilephion mass in my case for DY events.
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


	//DATA
	for ( int p=0; p<nentries ;p++){
		// this loop over all the events in your tree

		treedata->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			//Pt Bin
			/*if (unprop_pt[8][1]>500 && unprop_pt[8][1]<500){*/
				
				/////////////Pt////////////////////


				if (var == "pT"){


					//Algorithm choice


					//global
					dataGlbUP->Fill(unprop_pt[0][0]);
					dataGlbLOW->Fill(unprop_pt[0][1]);
					//Tkonly
					dataTkonlyUP->Fill(unprop_pt[2][0]);
					dataTkonlyLOW->Fill(unprop_pt[2][1]);
					//Tpfms
					dataTpfmsUP->Fill(unprop_pt[3][0]);
					dataTpfmsLOW->Fill(unprop_pt[3][1]);
					//Picky
					dataPickyUP->Fill(unprop_pt[4][0]);
					dataPickyLOW->Fill(unprop_pt[4][1]);
					//DYT
					dataDYTUP->Fill(unprop_pt[5][0]);
					dataDYTLOW->Fill(unprop_pt[5][1]);
					//TuneP
					dataTunePUP->Fill(unprop_pt[8][0]);
					dataTunePLOW->Fill(unprop_pt[8][1]);
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
					dataGlbUP->Fill(eta[0][0]);
					dataGlbLOW->Fill(eta[0][1]);
					//Tkonly
					dataTkonlyUP->Fill(eta[2][0]);
					dataTkonlyLOW->Fill(eta[2][1]);
					//Tpfms
					dataTpfmsUP->Fill(eta[3][0]);
					dataTpfmsLOW->Fill(eta[3][1]);
					//Picky
					dataPickyUP->Fill(eta[4][0]);
					dataPickyLOW->Fill(eta[4][1]);
					//DYT
					dataDYTUP->Fill(eta[5][0]);
					dataDYTLOW->Fill(eta[5][1]);
					//TuneP
					dataTunePUP->Fill(eta[8][0]);
					dataTunePLOW->Fill(eta[8][1]);
				}

				/////////////PHI////////////////////


				else{


					//Algorithm choice


					//global
					dataGlbUP->Fill(unprop_phi[0][0]);
					dataGlbLOW->Fill(unprop_phi[0][1]);
					//Tkonly
					dataTkonlyUP->Fill(unprop_phi[2][0]);
					dataTkonlyLOW->Fill(unprop_phi[2][1]);
					//Tpfms
					dataTpfmsUP->Fill(unprop_phi[3][0]);
					dataTpfmsLOW->Fill(unprop_phi[3][1]);
					//Picky
					dataPickyUP->Fill(unprop_phi[4][0]);
					dataPickyLOW->Fill(unprop_phi[4][1]);
					//DYT
					dataDYTUP->Fill(unprop_phi[5][0]);
					dataDYTLOW->Fill(unprop_phi[5][1]);
					//TuneP
					dataTunePUP->Fill(unprop_phi[8][0]);
					dataTunePLOW->Fill(unprop_phi[8][1]);
				}


			}// end loop p

	//	}	
	}
	//MC 10
	for ( int p=0; p<nentriesMC ;p++){
		// this loop over all the events in your tree

		treeMC->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			/////////////Pt////////////////////

			if (var == "pT"){

				//Algorithm choice


				//global
				MCGlbUP->Fill(unprop_pt[0][0]);
				MCGlbLOW->Fill(unprop_pt[0][1]);
				//Tkonly
				MCTkonlyUP->Fill(unprop_pt[2][0]);
				MCTkonlyLOW->Fill(unprop_pt[2][1]);
				//Tpfms
				MCTpfmsUP->Fill(unprop_pt[3][0]);
				MCTpfmsLOW->Fill(unprop_pt[3][1]);
				//Picky
				MCPickyUP->Fill(unprop_pt[4][0]);
				MCPickyLOW->Fill(unprop_pt[4][1]);
				//DYT
				MCDYTUP->Fill(unprop_pt[5][0]);
				MCDYTLOW->Fill(unprop_pt[5][1]);
				//TuneP
				MCTunePUP->Fill(unprop_pt[8][0]);
				MCTunePLOW->Fill(unprop_pt[8][1]);
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
				MCGlbUP->Fill(eta[0][0]);
				MCGlbLOW->Fill(eta[0][1]);
				//Tkonly
				MCTkonlyUP->Fill(eta[2][0]);
				MCTkonlyLOW->Fill(eta[2][1]);
				//Tpfms
				MCTpfmsUP->Fill(eta[3][0]);
				MCTpfmsLOW->Fill(eta[3][1]);
				//Picky
				MCPickyUP->Fill(eta[4][0]);
				MCPickyLOW->Fill(eta[4][1]);
				//DYT
				MCDYTUP->Fill(eta[5][0]);
				MCDYTLOW->Fill(eta[5][1]);
				//TuneP
				MCTunePUP->Fill(eta[8][0]);
				MCTunePLOW->Fill(eta[8][1]);
			}

			/////////////PHI////////////////////

			else {

				//Algorithm choice


				//global
				MCGlbUP->Fill(unprop_phi[0][0]);
				MCGlbLOW->Fill(unprop_phi[0][1]);
				//Tkonly
				MCTkonlyUP->Fill(unprop_phi[2][0]);
				MCTkonlyLOW->Fill(unprop_phi[2][1]);
				//Tpfms
				MCTpfmsUP->Fill(unprop_phi[3][0]);
				MCTpfmsLOW->Fill(unprop_phi[3][1]);
				//Picky
				MCPickyUP->Fill(unprop_phi[4][0]);
				MCPickyLOW->Fill(unprop_phi[4][1]);
				//DYT
				MCDYTUP->Fill(unprop_phi[5][0]);
				MCDYTLOW->Fill(unprop_phi[5][1]);
				//TuneP
				MCTunePUP->Fill(unprop_phi[8][0]);
				MCTunePLOW->Fill(unprop_phi[8][1]);
			}

		}// end loop p

	}
//MC 100
	for ( int p=0; p<nentriesMC100 ;p++){
		// this loop over all the events in your tree

		treeMC100->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			/////////////Pt////////////////////

			if (var == "pT"){

				//Algorithm choice


				//global
				MC100GlbUP->Fill(unprop_pt[0][0]);
				MC100GlbLOW->Fill(unprop_pt[0][1]);
				//Tkonly
				MC100TkonlyUP->Fill(unprop_pt[2][0]);
				MC100TkonlyLOW->Fill(unprop_pt[2][1]);
				//Tpfms
				MC100TpfmsUP->Fill(unprop_pt[3][0]);
				MC100TpfmsLOW->Fill(unprop_pt[3][1]);
				//Picky
				MC100PickyUP->Fill(unprop_pt[4][0]);
				MC100PickyLOW->Fill(unprop_pt[4][1]);
				//DYT
				MC100DYTUP->Fill(unprop_pt[5][0]);
				MC100DYTLOW->Fill(unprop_pt[5][1]);
				//TuneP
				MC100TunePUP->Fill(unprop_pt[8][0]);
				MC100TunePLOW->Fill(unprop_pt[8][1]);
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
				MC100GlbUP->Fill(eta[0][0]);
				MC100GlbLOW->Fill(eta[0][1]);
				//Tkonly
				MC100TkonlyUP->Fill(eta[2][0]);
				MC100TkonlyLOW->Fill(eta[2][1]);
				//Tpfms
				MC100TpfmsUP->Fill(eta[3][0]);
				MC100TpfmsLOW->Fill(eta[3][1]);
				//Picky
				MC100PickyUP->Fill(eta[4][0]);
				MC100PickyLOW->Fill(eta[4][1]);
				//DYT
				MC100DYTUP->Fill(eta[5][0]);
				MC100DYTLOW->Fill(eta[5][1]);
				//TuneP
				MC100TunePUP->Fill(eta[8][0]);
				MC100TunePLOW->Fill(eta[8][1]);
			}

			/////////////PHI////////////////////

			else {

				//Algorithm choice


				//global
				MC100GlbUP->Fill(unprop_phi[0][0]);
				MC100GlbLOW->Fill(unprop_phi[0][1]);
				//Tkonly
				MC100TkonlyUP->Fill(unprop_phi[2][0]);
				MC100TkonlyLOW->Fill(unprop_phi[2][1]);
				//Tpfms
				MC100TpfmsUP->Fill(unprop_phi[3][0]);
				MC100TpfmsLOW->Fill(unprop_phi[3][1]);
				//Picky
				MC100PickyUP->Fill(unprop_phi[4][0]);
				MC100PickyLOW->Fill(unprop_phi[4][1]);
				//DYT
				MC100DYTUP->Fill(unprop_phi[5][0]);
				MC100DYTLOW->Fill(unprop_phi[5][1]);
				//TuneP
				MC100TunePUP->Fill(unprop_phi[8][0]);
				MC100TunePLOW->Fill(unprop_phi[8][1]);
			}

		}// end loop p

	}

//MC 500
	for ( int p=0; p<nentriesMC500 ;p++){
		// this loop over all the events in your tree

		treeMC500->GetEntry(p);
		//apply some quality cuts to select the entries that we think are interesting
		//selection cuts

		if (pixel_hits[8][0]>=1 && strip_layers[8][0]>=5 && pixel_hits[8][1]>=1 && strip_layers[8][1]>=5 && unprop_pt[8][1]>30.){

			/////////////Pt////////////////////

			if (var == "pT"){

				//Algorithm choice


				//global
				MC500GlbUP->Fill(unprop_pt[0][0]);
				MC500GlbLOW->Fill(unprop_pt[0][1]);
				//Tkonly
				MC500TkonlyUP->Fill(unprop_pt[2][0]);
				MC500TkonlyLOW->Fill(unprop_pt[2][1]);
				//Tpfms
				MC500TpfmsUP->Fill(unprop_pt[3][0]);
				MC500TpfmsLOW->Fill(unprop_pt[3][1]);
				//Picky
				MC500PickyUP->Fill(unprop_pt[4][0]);
				MC500PickyLOW->Fill(unprop_pt[4][1]);
				//DYT
				MC500DYTUP->Fill(unprop_pt[5][0]);
				MC500DYTLOW->Fill(unprop_pt[5][1]);
				//TuneP
				MC500TunePUP->Fill(unprop_pt[8][0]);
				MC500TunePLOW->Fill(unprop_pt[8][1]);
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
				MC500GlbUP->Fill(eta[0][0]);
				MC500GlbLOW->Fill(eta[0][1]);
				//Tkonly
				MC500TkonlyUP->Fill(eta[2][0]);
				MC500TkonlyLOW->Fill(eta[2][1]);
				//Tpfms
				MC500TpfmsUP->Fill(eta[3][0]);
				MC500TpfmsLOW->Fill(eta[3][1]);
				//Picky
				MC500PickyUP->Fill(eta[4][0]);
				MC500PickyLOW->Fill(eta[4][1]);
				//DYT
				MC500DYTUP->Fill(eta[5][0]);
				MC500DYTLOW->Fill(eta[5][1]);
				//TuneP
				MC500TunePUP->Fill(eta[8][0]);
				MC500TunePLOW->Fill(eta[8][1]);
			}

			/////////////PHI////////////////////

			else {

				//Algorithm choice


				//global
				MC500GlbUP->Fill(unprop_phi[0][0]);
				MC500GlbLOW->Fill(unprop_phi[0][1]);
				//Tkonly
				MC500TkonlyUP->Fill(unprop_phi[2][0]);
				MC500TkonlyLOW->Fill(unprop_phi[2][1]);
				//Tpfms
				MC500TpfmsUP->Fill(unprop_phi[3][0]);
				MC500TpfmsLOW->Fill(unprop_phi[3][1]);
				//Picky
				MC500PickyUP->Fill(unprop_phi[4][0]);
				MC500PickyLOW->Fill(unprop_phi[4][1]);
				//DYT
				MC500DYTUP->Fill(unprop_phi[5][0]);
				MC500DYTLOW->Fill(unprop_phi[5][1]);
				//TuneP
				MC500TunePUP->Fill(unprop_phi[8][0]);
				MC500TunePLOW->Fill(unprop_phi[8][1]);
			}

		}// end loop p

	}

	Double_t norm = 1;
	//Define the Canvas
	TCanvas *c = new TCanvas("c", "canvas", 700, 600);

	// Upper plot will be in pad5a
	TPad *pad5a = new TPad("pad5a", "pad5a", 0, 0.18, 1, 1.0);
	//pad5a->SetBottomMargin(0); // Upper and lower plot are joined
	pad5a->SetGridx();         // Vertical grid
	pad5a->Draw();             // Draw the upper pad: pad1
	pad5a->cd();               // pad1 becomes the current pad
	dataTunePUP->SetStats(111);          // No statistics on upper plot

	


	//weighting of MC
	//UP
	TAxis *axis =MCTunePUP->GetXaxis();
  	int bmin1 = axis->FindBin(100); //in your case xmin=-1.5
  	int bmax1 = axis->FindBin(2000); //in your case xmax=0.8	

	double num100 = MCTunePUP->Integral(bmin1,bmax1);
	double den100 = MC100TunePUP->Integral();
	cout << "den=" << den100 << "   " << "num=" << num100 << endl;
	double scale100 = num100/den100;
	cout << "ratio=" << scale100 << endl;
	MC100TunePUP->Scale(scale100);
	
  	int bmin2 = axis->FindBin(500); //in your case xmin=-1.5
  	int bmax2 = axis->FindBin(2000); //in your case xmax=0.8	
	double num500 = MCTunePUP->Integral(bmin2,bmax2);
	double den500 = MC500TunePUP->Integral();
	cout << "den2=" << den500 << "   " << "num2=" << num500 << endl;

	double scale500 = num500/den500;
	cout << "ratio2=" << scale500 << endl;

	MC500TunePUP->Scale(scale500);
	


	//Set bin content of MC10, MC100 and MC500
	
	int n1 = 2;
	int n2 = 6;	
	TH1F *MCtotUP = (TH1F*)MCTunePUP->Clone();
	MCtotUP->Reset("ICES,M");
	for (int i=1;i<n1;i++){
	MCtotUP->SetBinContent(i,MCTunePUP->GetBinContent(i));
		MCtotUP->SetBinError(i,MCTunePUP->GetBinError(i));
	}
	for (int i=n1;i<n2;i++){
		MCtotUP->SetBinContent(i,MC100TunePUP->GetBinContent(i));
		MCtotUP->SetBinError(i,MC100TunePUP->GetBinError(i));
	}
	for (int i=n2;i<8;i++){
		MCtotUP->SetBinContent(i,MC100TunePUP->GetBinContent(i));
		MCtotUP->SetBinError(i,MC100TunePUP->GetBinError(i));
	}

	//LOW
	TAxis *axisLOW =MCTunePLOW->GetXaxis();
  	int bmin1LOW = axisLOW->FindBin(100); //in your case xmin=-1.5
  	int bmax1LOW = axisLOW->FindBin(2000); //in your case xmax=0.8	

	double num100LOW = MCTunePLOW->Integral(bmin1LOW,bmax1LOW);
	double den100LOW = MC100TunePLOW->Integral();
	double scale100LOW = num100LOW/den100LOW;
	MC100TunePLOW->Scale(scale100LOW);
	
  	int bmin2LOW = axisLOW->FindBin(500); //in your case xmin=-1.5
  	int bmax2LOW = axisLOW->FindBin(2000); //in your case xmax=0.8	
	double num500LOW = MCTunePLOW->Integral(bmin2LOW,bmax2LOW);
	double den500LOW = MC500TunePLOW->Integral();
	double scale500LOW = num500LOW/den500LOW;

	MC500TunePLOW->Scale(scale500LOW);
	


	//Set bin content of MC10, MC100 and MC500
	
	TH1F *MCtotLOW = (TH1F*)MCTunePLOW->Clone();
	MCtotLOW->Reset("ICES,M");
	for (int i=1;i<n1;i++){
	MCtotLOW->SetBinContent(i,MCTunePLOW->GetBinContent(i));
		MCtotLOW->SetBinError(i,MCTunePLOW->GetBinError(i));
	}
	for (int i=n1;i<n2;i++){
		MCtotLOW->SetBinContent(i,MC100TunePLOW->GetBinContent(i));
		MCtotLOW->SetBinError(i,MC100TunePLOW->GetBinError(i));
	}
	for (int i=n2;i<8;i++){
		MCtotLOW->SetBinContent(i,MC100TunePLOW->GetBinContent(i));
		MCtotLOW->SetBinError(i,MC100TunePLOW->GetBinError(i));
	}


	//renormalize histograms 
	//DATA :
	dataTunePUP->Sumw2();
	dataTunePUP->Scale(norm/dataTunePUP->Integral(), "width");
	dataTunePLOW->Sumw2();
	dataTunePLOW->Scale(norm/dataTunePLOW->Integral(), "width");

	//MC
	MCtotUP->Sumw2();
	MCtotUP->Scale(norm/MCtotUP->Integral(), "width");
	MCtotLOW->Sumw2();
	MCtotLOW->Scale(norm/MCtotLOW->Integral(), "width");

	dataTunePUP->SetXTitle(titleX.c_str());
	dataTunePUP->SetLineColor(kBlue);
	dataTunePUP->SetLineWidth(2);
	dataTunePUP->GetXaxis()->SetTitleSize(0.05);
	//dataTunePUP->GetYaxis()->SetRangeUser(0,1.5);
	dataTunePUP->SetMarkerColor(kBlue);
	dataTunePUP->SetMarkerStyle(20);
	MCtotUP->SetLineColor(kBlue-9);
	MCtotUP->SetLineWidth(2);
	MCtotUP->SetMarkerColor(kBlue-9);
	MCtotUP->SetMarkerStyle(24);

	// Y axis h1 plot settings
	dataTunePUP->GetYaxis()->SetTitleSize(20);
	dataTunePUP->GetYaxis()->SetTitleFont(43);
	dataTunePUP->GetYaxis()->SetTitleOffset(1.);
	// h5 settings
	dataTunePLOW->SetLineColor(kRed);
	dataTunePLOW->SetLineWidth(2);
	dataTunePLOW->SetMarkerColor(kRed);
	dataTunePLOW->SetMarkerStyle(20);
	MCtotLOW->SetLineColor(kRed-9);
	MCtotLOW->SetLineWidth(2);
	MCtotLOW->SetMarkerColor(kRed-9);
	MCtotLOW->SetMarkerStyle(24);

	//DRAW
	dataTunePUP->Draw("E1");               
	dataTunePLOW->Draw("E1 same");        
	MCtotUP->Draw("E1 same");      
	MCtotLOW->Draw("E1 same");
	


	//LEGEND
	TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg5->SetHeader("TuneP-2016+2017 data");
	leg5->SetFillColor(10);
	leg5->AddEntry(dataTunePUP,"Upper leg ");
	leg5->AddEntry(dataTunePLOW,"Lower leg");
	leg5 -> Draw();
	TLegend * legMC = new TLegend(0.6, 0.43, 0.98, 0.6);
	legMC->SetHeader("TuneP-MC 2016 combined");
	legMC->SetFillColor(10);
	legMC->AddEntry(MCtotUP,"Upper leg ");
	legMC->AddEntry(MCtotLOW,"Lower leg");
	legMC -> Draw();


	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad5b
	TPad *pad5b = new TPad("pad5b", "pad5b", 0, 0., 1, 0.17);
	pad5b->SetTopMargin(0);
	pad5b->SetBottomMargin(0.2);
	pad5b->SetGridx(); // vertical grid
	pad5b->Draw();
	pad5b->cd();       // pad2 becomes the current pad

	// Define the ratio plot - UP
	TH1F *h5 = (TH1F*)dataTunePUP->Clone("h5");
	h5->SetLineColor(kBlack);
	h5->Sumw2();
	h5->SetStats(0);      // No statistics on lower plot
	h5->Divide(dataTunePUP,MCtotUP ,1,1,"B");
	h5->SetMarkerStyle(21);
	h5->SetMarkerColor(kBlue);
	h5->SetLineColor(kBlue);

	h5->Draw("E1");       // Draw the ratio plot
	// Define the ratio plot - LOW
	TH1F *h5LOW = (TH1F*)dataTunePLOW->Clone("h5LOW");
	h5LOW->SetLineColor(kBlack);
	h5LOW->Sumw2();
	h5LOW->SetStats(0);      // No statistics on lower plot
	h5LOW->Divide(dataTunePLOW,MCtotLOW ,1,1,"B");
	h5LOW->SetMarkerStyle(21);
	h5LOW->SetMarkerColor(kRed);
	h5LOW->SetLineColor(kRed);


	h5LOW->Draw("E1 same");       // Draw the ratio plot

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

	h5->SetStats(0);      // No statistics on lower plot
	//h5->GetYaxis()->SetRangeUser(-2,2);








	// Define the Canvas
	/*TCanvas *c = new TCanvas("c", "canvas", 1200, 800);
	  c->Divide(3,2);
	  c->cd(1);
	// Upper plot will be in pad0a
	TPad *pad0a = new TPad("pad0a", "pad0a", 0, 0.3, 1, 1.0);
	//pad0a->SetBottomMargin(0); // Upper and lower plot are joined
	pad0a->SetGridx();         // Vertical grid
	pad0a->Draw();             // Draw the upper pad: pad1
	pad0a->cd();               // pad1 becomes the current pad
	//dataGlbUP->SetStats(0);          // No statistics on upper plot
	dataGlbUP->Draw("E1");               // Draw h1
	dataGlbLOW->Draw("E1 same");         // Draw h2 on top of h1
	// Do not draw the Y axis label on the upper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg0 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg0->SetHeader("Global fit");
	leg0->SetFillColor(10);
	leg0->AddEntry(dataGlbUP,"Upper leg ");
	leg0->AddEntry(dataGlbLOW,"Lower leg");
	leg0 -> Draw();


	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad0b
	TPad *pad0b = new TPad("pad0b", "pad0b", 0, 0.56, 0.33, 0.66);
	pad0b->SetTopMargin(0);
	pad0b->SetBottomMargin(0.2);
	pad0b->SetGridx(); // vertical grid
	pad0b->Draw();
	pad0b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h0 = (TH1F*)dataGlbUP->Clone("h0");
	h0->SetLineColor(kBlack);
	h0->Sumw2();
	h0->SetStats(0);      // No statistics on lower plot
	h0->Divide(dataGlbUP,dataGlbLOW ,1,1,"B");
	h0->SetMarkerStyle(21);
	h0->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataGlbUP->SetXTitle("#phi ");
	dataGlbUP->SetLineColor(kBlue+1);
	dataGlbUP->SetLineWidth(2);
	// Y axis h1 plot settings
	dataGlbUP->GetYaxis()->SetTitleSize(20);
	dataGlbUP->GetYaxis()->SetTitleFont(43);
	dataGlbUP->GetYaxis()->SetTitleOffset(1.55);
	// h2 settings
	dataGlbLOW->SetLineColor(kRed);
	dataGlbLOW->SetLineWidth(2);
	// Ratio plot (h0) settings
	h0->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h0->GetYaxis()->SetTitle("up/low");
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
	h0->SetStats(0);      // No statistics on lower plot
	h0->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(2);

	// Upper plot will be in pad1a
	TPad *pad1a = new TPad("pad1a", "pad1a", 0, 0.3, 1, 1.0);
	//pad1a->SetBottomMargin(0); // Upper and lower plot are joined
	pad1a->SetGridx();         // Vertical grid
	pad1a->Draw();             // Draw the upper pad: pad1
	pad1a->cd();               // pad1 becomes the current pad
	//dataTkonlyUP->SetStats(0);          // No statistics on upper plot
	dataTkonlyUP->Draw("E1");               // Draw h1
	dataTkonlyLOW->Draw("E1 same");         // Draw h2 on top of h1
	// Do not draw the Y axis label on the upper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg1 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg1->SetHeader("Tkonly");
	leg1->SetFillColor(10);
	leg1->AddEntry(dataTkonlyUP,"Upper leg ");
	leg1->AddEntry(dataTkonlyLOW,"Lower leg");
	leg1 -> Draw();


	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad1b
	TPad *pad1b = new TPad("pad1b", "pad1b", 0.33, 0.56, 0.66,0.66);
	pad1b->SetTopMargin(0);
	pad1b->SetBottomMargin(0.2);
	pad1b->SetGridx(); // vertical grid
	pad1b->Draw();
	pad1b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h1 = (TH1F*)dataTkonlyUP->Clone("h1");
	h1->SetLineColor(kBlack);
	h1->Sumw2();
	h1->SetStats(0);      // No statistics on lower plot
	h1->Divide(dataTkonlyUP,dataTkonlyLOW ,1,1,"B");
	h1->SetMarkerStyle(21);
	h1->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataTkonlyUP->SetXTitle("#phi ");
	dataTkonlyUP->SetLineColor(kBlue+1);
	dataTkonlyUP->SetLineWidth(2);
	// Y axis h1 plot settings
	dataTkonlyUP->GetYaxis()->SetTitleSize(20);
	dataTkonlyUP->GetYaxis()->SetTitleFont(43);
	dataTkonlyUP->GetYaxis()->SetTitleOffset(1.55);
	// h2 settings
	dataTkonlyLOW->SetLineColor(kRed);
	dataTkonlyLOW->SetLineWidth(2);
	// Ratio plot (h1) settings
	h1->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h1->GetYaxis()->SetTitle("up/low");
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
	h1->SetStats(0);      // No statistics on lower plot
	h1->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(3);
	// Upper plot will be in pad2ba
	TPad *pad2a = new TPad("pad2a", "pad2a", 0, 0.3, 1, 1.0);
	//pad2a->SetBottomMargin(0); // Upper and lower plot are joined
	pad2a->SetGridx();         // Vertical grid
	pad2a->Draw();             // Draw the upper pad: pad1
	pad2a->cd();               // pad1 becomes the current pad
	//dataTpfmsUP->SetStats(0);          // No statistics on upper plot
	dataTpfmsUP->Draw("E1");               // Draw h1
	dataTpfmsLOW->Draw("E1 same");         // Draw h2 on top of h1
	// Do not draw the Y axis label on the upper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg2 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg2->SetHeader("TPFMS");
	leg2->SetFillColor(10);
	leg2->AddEntry(dataTpfmsUP,"Upper leg ");
	leg2->AddEntry(dataTpfmsLOW,"Lower leg");
	leg2 -> Draw();


	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad2b
	TPad *pad2b = new TPad("pad2b", "pad2b", 0.66, 0.56, 1, 0.66);
	pad2b->SetTopMargin(0);
	pad2b->SetBottomMargin(0.2);
	pad2b->SetGridx(); // vertical grid
	pad2b->Draw();
	pad2b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h2 = (TH1F*)dataTpfmsUP->Clone("h2");
	h2->SetLineColor(kBlack);
	h2->Sumw2();
	h2->SetStats(0);      // No statistics on lower plot
	h2->Divide(dataTpfmsUP,dataTpfmsLOW ,1,1,"B");
	h2->SetMarkerStyle(21);
	h2->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataTpfmsUP->SetXTitle("#phi ");
	dataTpfmsUP->SetLineColor(kBlue+1);
	dataTpfmsUP->SetLineWidth(2);
	// Y axis h1 plot settings
	dataTpfmsUP->GetYaxis()->SetTitleSize(20);
	dataTpfmsUP->GetYaxis()->SetTitleFont(43);
	dataTpfmsUP->GetYaxis()->SetTitleOffset(1.55);
	// h2 settings
	dataTpfmsLOW->SetLineColor(kRed);
	dataTpfmsLOW->SetLineWidth(2);
	// Ratio plot (h2) settings
	h2->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h2->GetYaxis()->SetTitle("up/low");
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
	h2->SetStats(0);      // No statistics on lower plot
	h2->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(4);
	// Upper plot will be in pad3a
	TPad *pad3a = new TPad("pad3a", "pad3a",0, 0.3, 1, 1.0);
	//pad3a->SetBottomMargin(0); // Upper and lower plot are joined
	pad3a->SetGridx();         // Vertical grid
	pad3a->Draw();             // Draw the upper pad: pad1
	pad3a->cd();               // pad1 becomes the current pad
	//dataPickyUP->SetStats(0);          // No statistics on upper plot
	dataPickyUP->Draw("E1");               // Draw h1
	dataPickyLOW->Draw("E1 same");         // Draw h3 on top of h1
	// Do not draw the Y axis label on the upper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg3 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg3->SetHeader("Picky fit");
	leg3->SetFillColor(10);
	leg3->AddEntry(dataPickyUP,"Upper leg ");
	leg3->AddEntry(dataPickyLOW,"Lower leg");
	leg3 -> Draw();


	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad3b
	TPad *pad3b = new TPad("pad3b", "pad3b", 0, 0.06, 0.33, 0.16);
	pad3b->SetTopMargin(0);
	pad3b->SetBottomMargin(0.2);
	pad3b->SetGridx(); // vertical grid
	pad3b->Draw();
	pad3b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h3 = (TH1F*)dataPickyUP->Clone("h3");
	h3->SetLineColor(kBlack);
	h3->Sumw2();
	h3->SetStats(0);      // No statistics on lower plot
	h3->Divide(dataPickyUP,dataPickyLOW ,1,1,"B");
	h3->SetMarkerStyle(21);
	h3->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataPickyUP->SetXTitle("#phi ");
	dataPickyUP->SetLineColor(kBlue+1);
	dataPickyUP->SetLineWidth(2);
	// Y axis h1 plot settings
	dataPickyUP->GetYaxis()->SetTitleSize(20);
	dataPickyUP->GetYaxis()->SetTitleFont(43);
	dataPickyUP->GetYaxis()->SetTitleOffset(1.55);
	// h3 settings
	dataPickyLOW->SetLineColor(kRed);
	dataPickyLOW->SetLineWidth(2);
	// Ratio plot (h3) settings
	h3->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h3->GetYaxis()->SetTitle("up/low");
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
	h3->SetStats(0);      // No statistics on lower plot
	h3->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(5);
	// Upper plot will be in pad4a
	TPad *pad4a = new TPad("pad4a", "pad4a", 0, 0.3, 1, 1.0);
	//pad4a->SetBottomMargin(0); // Upper and lower plot are joined
	pad4a->SetGridx();         // Vertical grid
	pad4a->Draw();             // Draw the upper pad: pad1
	pad4a->cd();               // pad1 becomes the current pad
	//dataDYTUP->SetStats(0);          // No statistics on upper plot
	dataDYTUP->Draw("E1");               // Draw h1
	dataDYTLOW->Draw("E1 same");         // Draw h4 on top of h1
	// Do not draw the Y axis label on the upper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg4 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg4->SetHeader("DYT");
	leg4->SetFillColor(10);
	leg4->AddEntry(dataDYTUP,"Upper leg ");
	leg4->AddEntry(dataDYTLOW,"Lower leg");
	leg4 -> Draw();


	// lower plot will be in pad
	c->cd();          // Go ba to the main canvas before defining pad4b
	TPad *pad4b = new TPad("pad4b", "pad4b", 0.33, 0.06, 0.66,0.16);
	pad4b->SetTopMargin(0);
	pad4b->SetBottomMargin(0.2);
	pad4b->SetGridx(); // vertical grid
	pad4b->Draw();
	pad4b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h4 = (TH1F*)dataDYTUP->Clone("h4");
	h4->SetLineColor(kBlack);
	h4->Sumw2();
	h4->SetStats(0);      // No statistics on lower plot
	h4->Divide(dataDYTUP,dataDYTLOW ,1,1,"B");
	h4->SetMarkerStyle(21);
	h4->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataDYTUP->SetXTitle("#phi ");
	dataDYTUP->SetLineColor(kBlue+1);
	dataDYTUP->SetLineWidth(2);
	// Y axis h1 plot settings
	dataDYTUP->GetYaxis()->SetTitleSize(20);
	dataDYTUP->GetYaxis()->SetTitleFont(43);
	dataDYTUP->GetYaxis()->SetTitleOffset(1.55);
	// h4 settings
	dataDYTLOW->SetLineColor(kRed);
	dataDYTLOW->SetLineWidth(2);
	// Ratio plot (h4) settings
	h4->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h4->GetYaxis()->SetTitle("up/low");
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
	h4->SetStats(0);      // No statistics on lower plot
	h4->GetYaxis()->SetRangeUser(0.8,1.2);

	c->cd(6);
	// Upper plot will be in pad5a
	TPad *pad5a = new TPad("pad3a", "pad3a", 0, 0.3, 1, 1.0);
	//pad5a->SetBottomMargin(0); // Upper and lower plot are joined
	pad5a->SetGridx();         // Vertical grid
	pad5a->Draw();             // Draw the upper pad: pad1
	pad5a->cd();               // pad1 becomes the current pad
	//dataTunePUP->SetStats(0);          // No statistics on upper plot
	dataTunePUP->Draw("E1");               // Draw h1
	dataTunePLOW->Draw("E1 same");         // Draw h5 on top of h1
	// Do not draw the Y axis label on the upper plot and redraw a small
	// axis instead, in order to avoid the first label (0) to be clipped.

	TLegend * leg5 = new TLegend(0.6, 0.60, 0.98, 0.77);
	leg5->SetHeader("TuneP");
	leg5->SetFillColor(10);
	leg5->AddEntry(dataTunePUP,"Upper leg ");
	leg5->AddEntry(dataTunePLOW,"Lower leg");
	leg5 -> Draw();


	// lower plot will be in pad
	c->cd();          // Go back to the main canvas before defining pad5b
	TPad *pad5b = new TPad("pad5b", "pad5b", 0.66, 0.06, 1, 0.16);
	pad5b->SetTopMargin(0);
	pad5b->SetBottomMargin(0.2);
	pad5b->SetGridx(); // vertical grid
	pad5b->Draw();
	pad5b->cd();       // pad2 becomes the current pad
	// Define the ratio plot
	TH1F *h5 = (TH1F*)dataTunePUP->Clone("h5");
	h5->SetLineColor(kBlack);
	h5->Sumw2();
	h5->SetStats(0);      // No statistics on lower plot
	h5->Divide(dataTunePUP,dataTunePLOW ,1,1,"B");
	h5->SetMarkerStyle(21);
	h5->Draw("E1");       // Draw the ratio plot
	// h1 settings
	dataTunePUP->SetXTitle("#phi ");
	dataTunePUP->SetLineColor(kBlue+1);
	dataTunePUP->SetLineWidth(2);
	// Y axis h1 plot settings
	dataTunePUP->GetYaxis()->SetTitleSize(20);
	dataTunePUP->GetYaxis()->SetTitleFont(43);
	dataTunePUP->GetYaxis()->SetTitleOffset(1.55);
	// h5 settings
	dataTunePLOW->SetLineColor(kRed);
	dataTunePLOW->SetLineWidth(2);
	// Ratio plot (h5) settings
	h5->SetTitle(""); // Remove the ratio title
	// Y axis ratio plot settings
	h5->GetYaxis()->SetTitle("up/low");
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
	h5->SetStats(0);      // No statistics on lower plot
	h5->GetYaxis()->SetRangeUser(0.8,1.2);*/



		/*TFile *fout = new TFile("testphi.root ","RECREATE");

		  dataGlb->Write();
		  dataStalone->Write();

		  fout->Close();*/

}// end of function 
