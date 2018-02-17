#if !defined(__CINT__) || defined(__MAKECINT__)
// Auxiliary Headers
#include "../../Utilities/TreeReader/L1UpgradeTree.h"
#include "../../Utilities/TreeReader/Muon2RecoTree.h"
// ROOT headers
#include "TROOT.h"
#include "TSystem.h"
#include "TMath.h"
#include "TEfficiency.h"
#include "TLorentzVector.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TAxis.h"
// c++ headers
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <dirent.h>
#include <chrono>
// CMS headers
#include "../../Utilities/CMS/tdrstyle.C"
#include "../../Utilities/CMS/CMS_lumi.C"

#endif


// ------------------ FUNCTION -------------------------------
void setStyle();
void makeDir(const std::string& dir);
static inline void loadBar(const int iEvent, const int nEvents, const int r = 100, const int w = 100);

// ------------------ GLOBAL -------------------------------
const double MUON_MASS_ = 0.1056583745;
auto TIME_START_ = std::chrono::high_resolution_clock::now();
auto TIME_END_ = TIME_START_;
int  TIME_DIF_ = 0;


void getEfficiency()
{
  // Change the working directory
  const std::string CWD = getcwd(NULL, 0);
  const std::string mainDir = Form("%s/Output/", CWD.c_str());
  gSystem->mkdir(mainDir.c_str(), kTRUE);
  gSystem->ChangeDirectory(mainDir.c_str());
  //
  // Create list of samples
  const std::string filePath = "/home/llr/cms/stahl/L1NTuple/Data/L1Ntuple_XeXe_HiMinimumBias7.root";
  //
  // ------------------------------------------------------------------------------------------------------------------------
  //
  // Extract all the Trees
  // 
  // L1 Emulator Tree
  std::unique_ptr< L1UpgradeTree > L1EmuTree;
  L1EmuTree.reset(new L1UpgradeTree());
  if (!L1EmuTree->GetTree(filePath)) return;
  const Long64_t nentries = L1EmuTree->GetEntries();
  // Muon Reco Tree
  std::unique_ptr< Muon2RecoTree > MuonTree;
  MuonTree.reset(new Muon2RecoTree());
  if (!MuonTree->GetTree(filePath)) return;
  if (MuonTree->GetEntries()!=nentries) { std::cout << "[ERROR] Muon Reco Tree does not have the same number of entries as L1 Emu Tree" << std::endl; return; }
  //
  // ------------------------------------------------------------------------------------------------------------------------
  //
  // Initialize the TEfficiency containers
  //
  std::map< std::string , TEfficiency > effMap;
  const std::vector< std::string > varList = { "Eta" , "Phi" , "Pt" };
  const std::vector< double > binN = {   25 ,  36 ,   50 };
  const std::vector< double > minB = { -2.5 ,-3.6 ,  0.0 };
  const std::vector< double > maxB = {  2.5 , 3.6 , 50.0 };
  for (uint i = 0; i < varList.size(); i++) {
    const std::string var = varList[i];
    effMap[var] = TEfficiency("", "", binN[i], minB[i], maxB[i]);
    effMap.at(var).SetName(Form("Eff_%s", var.c_str())); effMap.at(var).SetStatisticOption(TEfficiency::kFCP); //Clopper-Pearson 
  }
  //
  // ------------------------------------------------------------------------------------------------------------------------
  //
  // Fill the TEfficiency containers
  //
  int treeIdx = -1;
  std::cout << "[INFO] Starting to process " << nentries << " nentries" << std::endl;
  //
  for (Long64_t jentry = 0; jentry < nentries; jentry++) { //
    //
    // Get the entry in the trees
    if (L1EmuTree->GetEntry(jentry)<0) { std::cout << "[ERROR] L1 Emu Tree invalid entry!"    << std::endl; return; }
    if ( MuonTree->GetEntry(jentry)<0) { std::cout << "[ERROR] Muon Reco Tree invalid entry!" << std::endl; return; }
    //
    if (L1EmuTree->Chain()->GetTreeNumber()!=treeIdx) {
      treeIdx = L1EmuTree->Chain()->GetTreeNumber();
      std::cout << "[INFO] Processing Root File: " << filePath << std::endl;
    }
    //
    loadBar(jentry, nentries);
    //
    // Compute the Efficiency
    //
    // Loop over the Reconstructed Muons
    for (uint iMu = 0; iMu < MuonTree->nMuons(); iMu++) {
      // Select good quality muons
      const bool isGoodMuon = ( MuonTree->isLooseMuon()[iMu] || MuonTree->isMediumMuon()[iMu] || MuonTree->isTightMuon()[iMu] );
      //
      if (isGoodMuon) {
        // Extract reco muon kinematic
        TLorentzVector muP4;
        double muEta = MuonTree->etaSt1()[iMu];
        double muPhi = MuonTree->phiSt1()[iMu];
        if (muEta<-10. && muPhi<-10.) {
          muEta = MuonTree->etaSt2()[iMu];
          muPhi = MuonTree->phiSt2()[iMu];
        }
        if (muEta<-10. && muPhi<-10.) {
          muEta = MuonTree->eta()[iMu];
          muPhi = MuonTree->phi()[iMu];
        }
        const double muPt  = MuonTree->pt()[iMu];
        muP4.SetPtEtaPhiM( muPt, muEta, muPhi, MUON_MASS_ );
        //
        // Make L1 - Reco matching
        int idxL1Mu = -1;
        double minDr = 1.0; // Maximum delta R
        for (uint iL1Mu = 0; iL1Mu < L1EmuTree->nMuons(); iL1Mu++) {
          // Extract L1 muon kinematic
          TLorentzVector muL1P4;
          const double muL1Eta = L1EmuTree->muonEta()[iL1Mu]; // L1EmuTree->muonEtaAtVtx()[iL1Mu];
          const double muL1Phi = L1EmuTree->muonPhi()[iL1Mu]; // L1EmuTree->muonPhiAtVtx()[iL1Mu];
          const double muL1Et  = L1EmuTree->muonEt()[iL1Mu];
          const double muL1Pt  = std::sqrt( std::pow(muL1Et, 2.0) - (std::pow(MUON_MASS_, 2.0)/(1.0 + std::pow(TMath::SinH(muL1Eta), 2.0))) );
          muL1P4.SetPtEtaPhiM( muL1Pt, muL1Eta, muL1Phi, MUON_MASS_ );
          // Compute deltaR
          const double dR = muP4.DeltaR( muL1P4 );
          // Find the closest L1 muon to reco muon
          if (dR < minDr) {
            minDr = dR;
            idxL1Mu = iL1Mu;
            break;
          }
        }
        const bool isL1Matched = (idxL1Mu >= 0);
        //
        // Fill the TEfficiency
        effMap.at("Eta").Fill(isL1Matched, muP4.Eta());
        effMap.at("Phi").Fill(isL1Matched, muP4.Phi());
        effMap.at("Pt" ).Fill(isL1Matched, muP4.Pt() );
      }
    }
  }
  //
  // ------------------------------------------------------------------------------------------------------------------------
  //
  // Draw the TEfficiency containers
  //
  // Set Style
  setStyle();
  //
  for (auto& v : effMap) {
    //
    std::string var = v.first;
    TEfficiency eff = v.second;
    // Create Canvas
    TCanvas c("c", "c", 1000, 1000); c.cd();
    //
    eff.Draw(); gPad->Update();
    auto graph = eff.GetPaintedGraph();
    //
    // Format the graph
    //
    // General
    graph->SetMarkerColor(kBlue);
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(1.0);
    graph->SetFillStyle(1001);
    // X-axis
    std::string xLabel = "Reco #mu";
    if (var=="Eta") { xLabel += " #eta"; }
    if (var=="Phi") { xLabel += " #phi"; }
    if (var=="Pt" ) { xLabel += " p_{T} (GeV/c)"; }
    graph->GetXaxis()->CenterTitle(kFALSE);
    graph->GetXaxis()->SetTitleOffset(0.9);
    graph->GetXaxis()->SetTitleSize(0.050);
    graph->GetXaxis()->SetLabelSize(0.035);
    double xMin, xMax, yDummy;
    graph->GetPoint(0, xMin, yDummy); xMin -= graph->GetErrorXlow(0);
    int n = (graph->GetN()-1);
    graph->GetPoint(n, xMax, yDummy); xMax += graph->GetErrorXhigh(n);
    xMin = (std::floor((xMin-0.1)*10.0)/10.0);
    xMax = (std::ceil((xMax+0.1)*10.0)/10.0);
    graph->GetXaxis()->SetLimits(xMin , xMax);
    // Y-axis
    std::string yLabel = "L1 Muon Efficiency";
    graph->GetYaxis()->CenterTitle(kFALSE);
    graph->GetYaxis()->SetTitleOffset(1.4);
    graph->GetYaxis()->SetTitleSize(0.04);
    graph->GetYaxis()->SetLabelSize(0.035);
    graph->GetYaxis()->SetRangeUser(0.00, 1.30);
    // Set Axis Titles
    graph->SetTitle(Form(";%s;%s", xLabel.c_str(), yLabel.c_str()));
    //
    // Draw Graph
    graph->Draw("ap");
    //
    // Draw line
    const double yLine = 1.0;
    TLine line( xMin , yLine ,  xMax , yLine ); line.SetLineStyle(2);
    line.Draw("same");
    // Update
    c.Modified(); c.Update();
    // set the CMS style
    int option = 119;
    CMS_lumi(&c, option, 33, "");
    c.Modified(); c.Update();
    // Create Output Directory
    const std::string plotDir = mainDir + "Plots/XeXe/";
    makeDir(plotDir + "/png/");
    makeDir(plotDir + "/pdf/");
    makeDir(plotDir + "/root/");
    // Save Canvas
    const std::string ename = "eff1D_" + var +"_XeXe";
    c.SaveAs(( plotDir + "/png/" + ename + ".png" ).c_str());
    c.SaveAs(( plotDir + "/pdf/" + ename + ".pdf" ).c_str());
    c.SaveAs(( plotDir + "/root/" + ename + ".root" ).c_str());
    // Clean up memory
    c.Clear(); c.Close();
  }
  //
};


void setStyle()
{
  // Set the CMS style
  setTDRStyle();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  //
};


bool existDir(const std::string& dir)
{
  bool exist = false;
  void * dirp = gSystem->OpenDirectory(dir.c_str());
  if (dirp) { gSystem->FreeDirectory(dirp); exist = true; }
  return exist;
};


void makeDir(const std::string& dir)
{
  if (existDir(dir.c_str())==false){
    std::cout << "[INFO] DataSet directory: " << dir << " doesn't exist, will create it!" << std::endl;  
    gSystem->mkdir(dir.c_str(), kTRUE);
  }
};


static inline void loadBar(const int iEvent, const int nEvents, const int r, const int w)
{
  // Only update r times.
  if ( iEvent == (nEvents-1) ) { std::cout << std::endl; }
  if ( (iEvent % ((nEvents/r) + 1)) != 0 ) return;
  // Calculuate the ratio of complete-to-incomplete.
  const float ratio = (iEvent / (float)nEvents);
  const int   c     = (ratio * w);
  // Get Time Difference
  TIME_END_   = std::chrono::high_resolution_clock::now();
  TIME_DIF_   = std::chrono::duration_cast<std::chrono::seconds>(TIME_END_ - TIME_START_).count();
  TIME_START_ = std::chrono::high_resolution_clock::now();
  // Show the percentage complete.
  const int sec  = int( double(TIME_DIF_) * (1.0-ratio) *100. );
  const int min  = (sec / 60);
  const int hour = (min / 60);
  printf("[INFO] %3d%% (%02d:%02d:%02d) [", (int)(ratio*100), hour, int(min%60), int(sec%60));
  // Show the load bar.
  for (int i = 0; i < c; i++) { std::cout << "="; }
  for (int i = c; i < w; i++) { std::cout << " "; }
  // ANSI Control codes to go back to the
  // previous line and clear it.
  std::cout << "]\r" << std::flush;
};
