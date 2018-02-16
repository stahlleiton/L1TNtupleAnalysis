#ifndef L1UpgradeTfMuonTree_h
#define L1UpgradeTfMuonTree_h

// Header file for ROOT classes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for c++ classes
#include <iostream>
#include <string>
#include <memory>

// Header file for the classes stored in the Tree
#include "../DataFormats/L1TNtuples/L1AnalysisAllDataformats.h"


class L1UpgradeTfMuonTree {

 public :
  
  L1UpgradeTfMuonTree();
  virtual ~L1UpgradeTfMuonTree();
  virtual Bool_t       GetTree         (const std::vector< std::string >&, const std::string& treeName="l1UpgradeTfMuonEmuTree");
  virtual Bool_t       GetTree         (const std::string&, const std::string& treeName="l1UpgradeTfMuonEmuTree");
  virtual Int_t        GetEntry        (Long64_t);
  virtual void         SetEntry        (Long64_t entry) { entry_ = entry; }
  virtual Long64_t     GetEntries      (void) { return fChain_->GetEntries(); }
  virtual Long64_t     GetTreeEntries  (void) { return fChain_->GetTree()->GetEntriesFast(); }
  virtual TChain*      Chain           (void) { return fChain_.get(); }
  virtual void         Clear           (void);

  // GETTER
  unsigned short int      BMTF_nTfMuons()              {  SetBranch({"L1UpgradeBmtfMuon" , "nTfMuons"             });  return GET(L1UpgradeBmtfMuon_).nTfMuons;              }
  std::vector<short int>  BMTF_tfMuonHwPt()            {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwPt"           });  return GET(L1UpgradeBmtfMuon_).tfMuonHwPt;            }
  std::vector<short int>  BMTF_tfMuonHwEta()           {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwEta"          });  return GET(L1UpgradeBmtfMuon_).tfMuonHwEta;           }
  std::vector<short int>  BMTF_tfMuonHwPhi()           {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwPhi"          });  return GET(L1UpgradeBmtfMuon_).tfMuonHwPhi;           }
  std::vector<short int>  BMTF_tfMuonGlobalPhi()       {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonGlobalPhi"      });  return GET(L1UpgradeBmtfMuon_).tfMuonGlobalPhi;       }
  std::vector<short int>  BMTF_tfMuonHwSign()          {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwSign"         });  return GET(L1UpgradeBmtfMuon_).tfMuonHwSign;          }
  std::vector<short int>  BMTF_tfMuonHwSignValid()     {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwSignValid"    });  return GET(L1UpgradeBmtfMuon_).tfMuonHwSignValid;     }
  std::vector<short int>  BMTF_tfMuonHwQual()          {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwQual"         });  return GET(L1UpgradeBmtfMuon_).tfMuonHwQual;          }
  std::vector<short int>  BMTF_tfMuonLink()            {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonLink"           });  return GET(L1UpgradeBmtfMuon_).tfMuonLink;            }
  std::vector<short int>  BMTF_tfMuonProcessor()       {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonProcessor"      });  return GET(L1UpgradeBmtfMuon_).tfMuonProcessor;       }
  std::vector<short int>  BMTF_tfMuonTrackFinderType() {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonTrackFinderType"});  return GET(L1UpgradeBmtfMuon_).tfMuonTrackFinderType; }
  std::vector<short int>  BMTF_tfMuonHwHF()            {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonHwHF"           });  return GET(L1UpgradeBmtfMuon_).tfMuonHwHF;            }
  std::vector<short int>  BMTF_tfMuonBx()              {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonBx"             });  return GET(L1UpgradeBmtfMuon_).tfMuonBx;              }
  std::vector<short int>  BMTF_tfMuonWh()              {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonWh"             });  return GET(L1UpgradeBmtfMuon_).tfMuonWh;              }
  std::vector<short int>  BMTF_tfMuonTrAdd()           {  SetBranch({"L1UpgradeBmtfMuon" , "tfMuonTrAdd"          });  return GET(L1UpgradeBmtfMuon_).tfMuonTrAdd;           }
  //
  int                     BMTF_phSize()                {  SetBranch({"L1UpgradeBmtfInputs" , "phSize"             });  return GET(L1UpgradeBmtfInputs_).phSize;              }
  std::vector<int>        BMTF_phBx()                  {  SetBranch({"L1UpgradeBmtfInputs" , "phBx"               });  return GET(L1UpgradeBmtfInputs_).phBx;                }
  std::vector<int>        BMTF_phWh()                  {  SetBranch({"L1UpgradeBmtfInputs" , "phWh"               });  return GET(L1UpgradeBmtfInputs_).phWh;                }
  std::vector<int>        BMTF_phSe()                  {  SetBranch({"L1UpgradeBmtfInputs" , "phSe"               });  return GET(L1UpgradeBmtfInputs_).phSe;                }
  std::vector<int>        BMTF_phSt()                  {  SetBranch({"L1UpgradeBmtfInputs" , "phSt"               });  return GET(L1UpgradeBmtfInputs_).phSt;                }
  std::vector<float>      BMTF_phAng()                 {  SetBranch({"L1UpgradeBmtfInputs" , "phAng"              });  return GET(L1UpgradeBmtfInputs_).phAng;               }
  std::vector<float>      BMTF_phBandAng()             {  SetBranch({"L1UpgradeBmtfInputs" , "phBandAng"          });  return GET(L1UpgradeBmtfInputs_).phBandAng;           }
  std::vector<int>        BMTF_phCode()                {  SetBranch({"L1UpgradeBmtfInputs" , "phCode"             });  return GET(L1UpgradeBmtfInputs_).phCode;              }
  std::vector<int>        BMTF_phTs2Tag()              {  SetBranch({"L1UpgradeBmtfInputs" , "phTs2Tag"           });  return GET(L1UpgradeBmtfInputs_).phTs2Tag;            }
  int                     BMTF_thSize()                {  SetBranch({"L1UpgradeBmtfInputs" , "thSize"             });  return GET(L1UpgradeBmtfInputs_).thSize;              }
  std::vector<int>        BMTF_thBx()                  {  SetBranch({"L1UpgradeBmtfInputs" , "thBx"               });  return GET(L1UpgradeBmtfInputs_).thBx;                }
  std::vector<int>        BMTF_thWh()                  {  SetBranch({"L1UpgradeBmtfInputs" , "thWh"               });  return GET(L1UpgradeBmtfInputs_).thWh;                }
  std::vector<int>        BMTF_thSe()                  {  SetBranch({"L1UpgradeBmtfInputs" , "thSe"               });  return GET(L1UpgradeBmtfInputs_).thSe;                }
  std::vector<int>        BMTF_thSt()                  {  SetBranch({"L1UpgradeBmtfInputs" , "thSt"               });  return GET(L1UpgradeBmtfInputs_).thSt;                }
  std::vector<int>        BMTF_thTheta()               {  SetBranch({"L1UpgradeBmtfInputs" , "thTheta"            });  return GET(L1UpgradeBmtfInputs_).thTheta;             }
  std::vector<int>        BMTF_thCode()                {  SetBranch({"L1UpgradeBmtfInputs" , "thCode"             });  return GET(L1UpgradeBmtfInputs_).thCode;              }
  //
  unsigned short int      OMTF_nTfMuons()              {  SetBranch({"L1UpgradeOmtfMuon" , "nTfMuons"             });  return GET(L1UpgradeOmtfMuon_).nTfMuons;              }
  std::vector<short int>  OMTF_tfMuonHwPt()            {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwPt"           });  return GET(L1UpgradeOmtfMuon_).tfMuonHwPt;            }
  std::vector<short int>  OMTF_tfMuonHwEta()           {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwEta"          });  return GET(L1UpgradeOmtfMuon_).tfMuonHwEta;           }
  std::vector<short int>  OMTF_tfMuonHwPhi()           {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwPhi"          });  return GET(L1UpgradeOmtfMuon_).tfMuonHwPhi;           }
  std::vector<short int>  OMTF_tfMuonGlobalPhi()       {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonGlobalPhi"      });  return GET(L1UpgradeOmtfMuon_).tfMuonGlobalPhi;       }
  std::vector<short int>  OMTF_tfMuonHwSign()          {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwSign"         });  return GET(L1UpgradeOmtfMuon_).tfMuonHwSign;          }
  std::vector<short int>  OMTF_tfMuonHwSignValid()     {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwSignValid"    });  return GET(L1UpgradeOmtfMuon_).tfMuonHwSignValid;     }
  std::vector<short int>  OMTF_tfMuonHwQual()          {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwQual"         });  return GET(L1UpgradeOmtfMuon_).tfMuonHwQual;          }
  std::vector<short int>  OMTF_tfMuonLink()            {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonLink"           });  return GET(L1UpgradeOmtfMuon_).tfMuonLink;            }
  std::vector<short int>  OMTF_tfMuonProcessor()       {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonProcessor"      });  return GET(L1UpgradeOmtfMuon_).tfMuonProcessor;       }
  std::vector<short int>  OMTF_tfMuonTrackFinderType() {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonTrackFinderType"});  return GET(L1UpgradeOmtfMuon_).tfMuonTrackFinderType; }
  std::vector<short int>  OMTF_tfMuonHwHF()            {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonHwHF"           });  return GET(L1UpgradeOmtfMuon_).tfMuonHwHF;            }
  std::vector<short int>  OMTF_tfMuonBx()              {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonBx"             });  return GET(L1UpgradeOmtfMuon_).tfMuonBx;              }
  std::vector<short int>  OMTF_tfMuonWh()              {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonWh"             });  return GET(L1UpgradeOmtfMuon_).tfMuonWh;              }
  std::vector<short int>  OMTF_tfMuonTrAdd()           {  SetBranch({"L1UpgradeOmtfMuon" , "tfMuonTrAdd"          });  return GET(L1UpgradeOmtfMuon_).tfMuonTrAdd;           }
  //
  unsigned short int      EMTF_nTfMuons()              {  SetBranch({"L1UpgradeEmtfMuon" , "nTfMuons"             });  return GET(L1UpgradeEmtfMuon_).nTfMuons;              }
  std::vector<short int>  EMTF_tfMuonHwPt()            {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwPt"           });  return GET(L1UpgradeEmtfMuon_).tfMuonHwPt;            }
  std::vector<short int>  EMTF_tfMuonHwEta()           {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwEta"          });  return GET(L1UpgradeEmtfMuon_).tfMuonHwEta;           }
  std::vector<short int>  EMTF_tfMuonHwPhi()           {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwPhi"          });  return GET(L1UpgradeEmtfMuon_).tfMuonHwPhi;           }
  std::vector<short int>  EMTF_tfMuonGlobalPhi()       {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonGlobalPhi"      });  return GET(L1UpgradeEmtfMuon_).tfMuonGlobalPhi;       }
  std::vector<short int>  EMTF_tfMuonHwSign()          {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwSign"         });  return GET(L1UpgradeEmtfMuon_).tfMuonHwSign;          }
  std::vector<short int>  EMTF_tfMuonHwSignValid()     {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwSignValid"    });  return GET(L1UpgradeEmtfMuon_).tfMuonHwSignValid;     }
  std::vector<short int>  EMTF_tfMuonHwQual()          {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwQual"         });  return GET(L1UpgradeEmtfMuon_).tfMuonHwQual;          }
  std::vector<short int>  EMTF_tfMuonLink()            {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonLink"           });  return GET(L1UpgradeEmtfMuon_).tfMuonLink;            }
  std::vector<short int>  EMTF_tfMuonProcessor()       {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonProcessor"      });  return GET(L1UpgradeEmtfMuon_).tfMuonProcessor;       }
  std::vector<short int>  EMTF_tfMuonTrackFinderType() {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonTrackFinderType"});  return GET(L1UpgradeEmtfMuon_).tfMuonTrackFinderType; }
  std::vector<short int>  EMTF_tfMuonHwHF()            {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonHwHF"           });  return GET(L1UpgradeEmtfMuon_).tfMuonHwHF;            }
  std::vector<short int>  EMTF_tfMuonBx()              {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonBx"             });  return GET(L1UpgradeEmtfMuon_).tfMuonBx;              }
  std::vector<short int>  EMTF_tfMuonWh()              {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonWh"             });  return GET(L1UpgradeEmtfMuon_).tfMuonWh;              }
  std::vector<short int>  EMTF_tfMuonTrAdd()           {  SetBranch({"L1UpgradeEmtfMuon" , "tfMuonTrAdd"          });  return GET(L1UpgradeEmtfMuon_).tfMuonTrAdd;           }

 private:

  virtual Long64_t  LoadTree   (Long64_t);
  virtual void      SetBranch  (const std::vector<std::string>&);
  virtual void      InitTree   (void);
  virtual Int_t     LoadEntry  (void) { return fChain_->GetEntry(entry_); }

  template <typename T>
    T GET(T* x) { if (x==NULL) { std::cout << "WTF" << std::endl; }; return ( (x) ? *x : T() ); }

  std::unique_ptr<TChain>    fChain_;
  Int_t                      fCurrent_ = -1;
  Long64_t                   entry_;

  // POINTERS
  L1Analysis::L1AnalysisL1UpgradeTfMuonDataFormat   *L1UpgradeBmtfMuon_;
  L1Analysis::L1AnalysisL1UpgradeTfMuonDataFormat   *L1UpgradeOmtfMuon_;
  L1Analysis::L1AnalysisL1UpgradeTfMuonDataFormat   *L1UpgradeEmtfMuon_;
  L1Analysis::L1AnalysisBMTFInputsDataFormat        *L1UpgradeBmtfInputs_;

  // BRANCHES
  TBranch        *b_L1UpgradeBmtfMuon;
  TBranch        *b_L1UpgradeOmtfMuon;
  TBranch        *b_L1UpgradeEmtfMuon;
  TBranch        *b_L1UpgradeBmtfInputs;
};

L1UpgradeTfMuonTree::L1UpgradeTfMuonTree()
{
}

L1UpgradeTfMuonTree::~L1UpgradeTfMuonTree()
{
  if (fChain_ && fChain_->GetCurrentFile()) delete fChain_->GetCurrentFile();
}

Bool_t L1UpgradeTfMuonTree::GetTree(const std::string& fileName, const std::string& treeName)
{
  std::vector<std::string> fileNames = {fileName};
  return GetTree(fileNames, treeName);
}

Bool_t L1UpgradeTfMuonTree::GetTree(const std::vector< std::string >& inFileName, const std::string& treeName)
{
  // Check the File Names
  std::vector< std::string > fileName = inFileName;
  for (auto& f : fileName) { if (f.find("/store/")!=std::string::npos && f.find("root://")==std::string::npos) { f = "root://cms-xrd-global.cern.ch/" + f.substr(f.find("/store/")); } }
  // Open the input files
  TFile *f = TFile::Open(fileName[0].c_str());
  if (!f || !f->IsOpen()) { std::cout << "[ERROR] The file was not found or is corrupted!" << std::endl; return false; }
  // Extract the input TChains
  TDirectory * dir;
  if (fileName[0].find("root://")!=std::string::npos) { dir = (TDirectory*)f->Get(treeName.c_str()); }
  else { dir = (TDirectory*)f->Get((fileName[0]+":/"+treeName).c_str()); }
  if (!dir) { std::cout << "[ERROR] Directory " << treeName << " was not found!" << std::endl; return false; }
  if (dir->GetListOfKeys()->Contains("L1UpgradeTfMuonTree")  ) { fChain_.reset(new TChain((treeName+"/L1UpgradeTfMuonTree").c_str()  , "L1UpgradeTfMuonTree"));  }
  if (fChain_==NULL) { std::cout << "[ERROR] Tree L1UpgradeTfMuonTree was not found!" << std::endl; return false; }
  // Add the files in the TChain
  for (auto& f : fileName) { fChain_->Add(Form("%s/%s/L1UpgradeTfMuonTree", f.c_str(), treeName.c_str())); }; fChain_->GetEntries();
  if (!fChain_) { std::cout << "[ERROR] fChain L1UpgradeTfMuonTree was not created, some input files are missing" << std::endl; return false; }
  // Initialize the input TChains (set their branches)
  InitTree();
  // Set All Branches to Status 0
  fChain_->SetBranchStatus("*",0);
  //
  return true;
}

Int_t L1UpgradeTfMuonTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  entry_ = entry;
  if (LoadTree(entry_) < 0) return -1;
  Clear();
  return LoadEntry();
}

Long64_t L1UpgradeTfMuonTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain_) return -5;
  Long64_t centry = fChain_->LoadTree(entry);
  if (fChain_->GetTreeNumber() != fCurrent_) { fCurrent_ = fChain_->GetTreeNumber(); }
  return centry;
}

void L1UpgradeTfMuonTree::SetBranch(const std::vector<std::string>& nVec)
{
  for (const auto& n : nVec) {
    if ( fChain_->GetBranch(n.c_str()) && (fChain_->GetBranchStatus(n.c_str()) == 0) ) {
      fChain_->SetBranchStatus(Form("*%s*", n.c_str()), 1);
      LoadEntry();
    }
    if (fChain_->GetBranch(n.c_str())==NULL) { std::cout << "[ERROR] Branch " << n << " was not found!" << std::endl; }
  }
}


void L1UpgradeTfMuonTree::InitTree(void)
{
  // INITIALIZE POINTERS
  L1UpgradeBmtfMuon_   = NULL;
  L1UpgradeOmtfMuon_   = NULL;
  L1UpgradeEmtfMuon_   = NULL;
  L1UpgradeBmtfInputs_ = NULL;

  if (fChain_==NULL) return;

  // SET BRANCHES
  if (fChain_->GetBranch("L1UpgradeBmtfMuon"  )) fChain_->SetBranchAddress("L1UpgradeBmtfMuon",   &L1UpgradeBmtfMuon_,   &b_L1UpgradeBmtfMuon  );
  if (fChain_->GetBranch("L1UpgradeOmtfMuon"  )) fChain_->SetBranchAddress("L1UpgradeOmtfMuon",   &L1UpgradeOmtfMuon_,   &b_L1UpgradeOmtfMuon  );
  if (fChain_->GetBranch("L1UpgradeEmtfMuon"  )) fChain_->SetBranchAddress("L1UpgradeEmtfMuon",   &L1UpgradeEmtfMuon_,   &b_L1UpgradeEmtfMuon  );
  if (fChain_->GetBranch("L1UpgradeBmtfInputs")) fChain_->SetBranchAddress("L1UpgradeBmtfInputs", &L1UpgradeBmtfInputs_, &b_L1UpgradeBmtfInputs);
}

void L1UpgradeTfMuonTree::Clear(void)
{
  if (fChain_==NULL) return;

  // CLEAR EVENT INFO
  if (L1UpgradeBmtfMuon_  ) { *L1UpgradeBmtfMuon_   = L1Analysis::L1AnalysisL1UpgradeTfMuonDataFormat(); }
  if (L1UpgradeOmtfMuon_  ) { *L1UpgradeOmtfMuon_   = L1Analysis::L1AnalysisL1UpgradeTfMuonDataFormat(); }
  if (L1UpgradeEmtfMuon_  ) { *L1UpgradeEmtfMuon_   = L1Analysis::L1AnalysisL1UpgradeTfMuonDataFormat(); }
  if (L1UpgradeBmtfInputs_) { *L1UpgradeBmtfInputs_ = L1Analysis::L1AnalysisBMTFInputsDataFormat();      }
}

#endif
