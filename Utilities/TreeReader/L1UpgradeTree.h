#ifndef L1UpgradeTree_h
#define L1UpgradeTree_h

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


class L1UpgradeTree {

 public :
  
  L1UpgradeTree();
  virtual ~L1UpgradeTree();
  virtual Bool_t       GetTree         (const std::vector< std::string >&, const std::string& treeName="l1UpgradeEmuTree");
  virtual Bool_t       GetTree         (const std::string&, const std::string& treeName="l1UpgradeEmuTree");
  virtual Int_t        GetEntry        (Long64_t);
  virtual void         SetEntry        (Long64_t entry) { entry_ = entry; }
  virtual Long64_t     GetEntries      (void) { return fChain_->GetEntries(); }
  virtual Long64_t     GetTreeEntries  (void) { return fChain_->GetTree()->GetEntriesFast(); }
  virtual TChain*      Chain           (void) { return fChain_.get(); }
  virtual void         Clear           (void);

  // GETTER

  // Declaration of leaf types
  UShort_t                     nEGs()          {  SetBranch({"L1Upgrade" , "nEGs"         });  return GET(L1Upgrade_).nEGs;          }
  std::vector<float>           egEt()          {  SetBranch({"L1Upgrade" , "egEt"         });  return GET(L1Upgrade_).egEt;          }
  std::vector<float>           egEta()         {  SetBranch({"L1Upgrade" , "egEta"        });  return GET(L1Upgrade_).egEta;         }
  std::vector<float>           egPhi()         {  SetBranch({"L1Upgrade" , "egPhi"        });  return GET(L1Upgrade_).egPhi;         }
  std::vector<short>           egIEt()         {  SetBranch({"L1Upgrade" , "egIEt"        });  return GET(L1Upgrade_).egIEt;         }
  std::vector<short>           egIEta()        {  SetBranch({"L1Upgrade" , "egIEta"       });  return GET(L1Upgrade_).egIEta;        }
  std::vector<short>           egIPhi()        {  SetBranch({"L1Upgrade" , "egIPhi"       });  return GET(L1Upgrade_).egIPhi;        }
  std::vector<short>           egIso()         {  SetBranch({"L1Upgrade" , "egIso"        });  return GET(L1Upgrade_).egIso;         }
  std::vector<short>           egBx()          {  SetBranch({"L1Upgrade" , "egBx"         });  return GET(L1Upgrade_).egBx;          }
  std::vector<short>           egTowerIPhi()   {  SetBranch({"L1Upgrade" , "egTowerIPhi"  });  return GET(L1Upgrade_).egTowerIPhi;   }
  std::vector<short>           egTowerIEta()   {  SetBranch({"L1Upgrade" , "egTowerIEta"  });  return GET(L1Upgrade_).egTowerIEta;   }
  std::vector<short>           egRawEt()       {  SetBranch({"L1Upgrade" , "egRawEt"      });  return GET(L1Upgrade_).egRawEt;       }
  std::vector<short>           egIsoEt()       {  SetBranch({"L1Upgrade" , "egIsoEt"      });  return GET(L1Upgrade_).egIsoEt;       }
  std::vector<short>           egFootprintEt() {  SetBranch({"L1Upgrade" , "egFootprintEt"});  return GET(L1Upgrade_).egFootprintEt; }
  std::vector<short>           egNTT()         {  SetBranch({"L1Upgrade" , "egNTT"        });  return GET(L1Upgrade_).egNTT;         }
  std::vector<short>           egShape()       {  SetBranch({"L1Upgrade" , "egShape"      });  return GET(L1Upgrade_).egShape;       }
  std::vector<short>           egTowerHoE()    {  SetBranch({"L1Upgrade" , "egTowerHoE"   });  return GET(L1Upgrade_).egTowerHoE;    }
  UShort_t                     nTaus()         {  SetBranch({"L1Upgrade" , "nTaus"        });  return GET(L1Upgrade_).nTaus;         }
  std::vector<float>           tauEt()         {  SetBranch({"L1Upgrade" , "tauEt"        });  return GET(L1Upgrade_).tauEt;         }
  std::vector<float>           tauEta()        {  SetBranch({"L1Upgrade" , "tauEta"       });  return GET(L1Upgrade_).tauEta;        }
  std::vector<float>           tauPhi()        {  SetBranch({"L1Upgrade" , "tauPhi"       });  return GET(L1Upgrade_).tauPhi;        }
  std::vector<short>           tauIEt()        {  SetBranch({"L1Upgrade" , "tauIEt"       });  return GET(L1Upgrade_).tauIEt;        }
  std::vector<short>           tauIEta()       {  SetBranch({"L1Upgrade" , "tauIEta"      });  return GET(L1Upgrade_).tauIEta;       }
  std::vector<short>           tauIPhi()       {  SetBranch({"L1Upgrade" , "tauIPhi"      });  return GET(L1Upgrade_).tauIPhi;       }
  std::vector<short>           tauIso()        {  SetBranch({"L1Upgrade" , "tauIso"       });  return GET(L1Upgrade_).tauIso;        }
  std::vector<short>           tauBx()         {  SetBranch({"L1Upgrade" , "tauBx"        });  return GET(L1Upgrade_).tauBx;         }
  std::vector<short>           tauTowerIPhi()  {  SetBranch({"L1Upgrade" , "tauTowerIPhi" });  return GET(L1Upgrade_).tauTowerIPhi;  }
  std::vector<short>           tauTowerIEta()  {  SetBranch({"L1Upgrade" , "tauTowerIEta" });  return GET(L1Upgrade_).tauTowerIEta;  }
  std::vector<short>           tauRawEt()      {  SetBranch({"L1Upgrade" , "tauRawEt"     });  return GET(L1Upgrade_).tauRawEt;      }
  std::vector<short>           tauIsoEt()      {  SetBranch({"L1Upgrade" , "tauIsoEt"     });  return GET(L1Upgrade_).tauIsoEt;      }
  std::vector<short>           tauNTT()        {  SetBranch({"L1Upgrade" , "tauNTT"       });  return GET(L1Upgrade_).tauNTT;        }
  std::vector<short>           tauHasEM()      {  SetBranch({"L1Upgrade" , "tauHasEM"     });  return GET(L1Upgrade_).tauHasEM;      }
  std::vector<short>           tauIsMerged()   {  SetBranch({"L1Upgrade" , "tauIsMerged"  });  return GET(L1Upgrade_).tauIsMerged;   }
  std::vector<short>           tauHwQual()     {  SetBranch({"L1Upgrade" , "tauHwQual"    });  return GET(L1Upgrade_).tauHwQual;     }
  UShort_t                     nJets()         {  SetBranch({"L1Upgrade" , "nJets"        });  return GET(L1Upgrade_).nJets;         }
  std::vector<float>           jetEt()         {  SetBranch({"L1Upgrade" , "jetEt"        });  return GET(L1Upgrade_).jetEt;         }
  std::vector<float>           jetEta()        {  SetBranch({"L1Upgrade" , "jetEta"       });  return GET(L1Upgrade_).jetEta;        }
  std::vector<float>           jetPhi()        {  SetBranch({"L1Upgrade" , "jetPhi"       });  return GET(L1Upgrade_).jetPhi;        }
  std::vector<short>           jetIEt()        {  SetBranch({"L1Upgrade" , "jetIEt"       });  return GET(L1Upgrade_).jetIEt;        }
  std::vector<short>           jetIEta()       {  SetBranch({"L1Upgrade" , "jetIEta"      });  return GET(L1Upgrade_).jetIEta;       }
  std::vector<short>           jetIPhi()       {  SetBranch({"L1Upgrade" , "jetIPhi"      });  return GET(L1Upgrade_).jetIPhi;       }
  std::vector<short>           jetBx()         {  SetBranch({"L1Upgrade" , "jetBx"        });  return GET(L1Upgrade_).jetBx;         }
  std::vector<short>           jetTowerIPhi()  {  SetBranch({"L1Upgrade" , "jetTowerIPhi" });  return GET(L1Upgrade_).jetTowerIPhi;  }
  std::vector<short>           jetTowerIEta()  {  SetBranch({"L1Upgrade" , "jetTowerIEta" });  return GET(L1Upgrade_).jetTowerIEta;  }
  std::vector<short>           jetRawEt()      {  SetBranch({"L1Upgrade" , "jetRawEt"     });  return GET(L1Upgrade_).jetRawEt;      }
  std::vector<short>           jetSeedEt()     {  SetBranch({"L1Upgrade" , "jetSeedEt"    });  return GET(L1Upgrade_).jetSeedEt;     }
  std::vector<short>           jetPUEt()       {  SetBranch({"L1Upgrade" , "jetPUEt"      });  return GET(L1Upgrade_).jetPUEt;       }
  std::vector<short>           jetPUDonutEt0() {  SetBranch({"L1Upgrade" , "jetPUDonutEt0"});  return GET(L1Upgrade_).jetPUDonutEt0; }
  std::vector<short>           jetPUDonutEt1() {  SetBranch({"L1Upgrade" , "jetPUDonutEt1"});  return GET(L1Upgrade_).jetPUDonutEt1; }
  std::vector<short>           jetPUDonutEt2() {  SetBranch({"L1Upgrade" , "jetPUDonutEt2"});  return GET(L1Upgrade_).jetPUDonutEt2; }
  std::vector<short>           jetPUDonutEt3() {  SetBranch({"L1Upgrade" , "jetPUDonutEt3"});  return GET(L1Upgrade_).jetPUDonutEt3; }
  UShort_t                     nMuons()        {  SetBranch({"L1Upgrade" , "nMuons"       });  return GET(L1Upgrade_).nMuons;        }
  std::vector<float>           muonEt()        {  SetBranch({"L1Upgrade" , "muonEt"       });  return GET(L1Upgrade_).muonEt;        }
  std::vector<float>           muonEta()       {  SetBranch({"L1Upgrade" , "muonEta"      });  return GET(L1Upgrade_).muonEta;       }
  std::vector<float>           muonPhi()       {  SetBranch({"L1Upgrade" , "muonPhi"      });  return GET(L1Upgrade_).muonPhi;       }
  std::vector<float>           muonEtaAtVtx()  {  SetBranch({"L1Upgrade" , "muonEtaAtVtx" });  return GET(L1Upgrade_).muonEtaAtVtx;  }
  std::vector<float>           muonPhiAtVtx()  {  SetBranch({"L1Upgrade" , "muonPhiAtVtx" });  return GET(L1Upgrade_).muonPhiAtVtx;  }
  std::vector<short>           muonIEt()       {  SetBranch({"L1Upgrade" , "muonIEt"      });  return GET(L1Upgrade_).muonIEt;       }
  std::vector<short>           muonIEta()      {  SetBranch({"L1Upgrade" , "muonIEta"     });  return GET(L1Upgrade_).muonIEta;      }
  std::vector<short>           muonIPhi()      {  SetBranch({"L1Upgrade" , "muonIPhi"     });  return GET(L1Upgrade_).muonIPhi;      }
  std::vector<short>           muonIEtaAtVtx() {  SetBranch({"L1Upgrade" , "muonIEtaAtVtx"});  return GET(L1Upgrade_).muonIEtaAtVtx; }
  std::vector<short>           muonIPhiAtVtx() {  SetBranch({"L1Upgrade" , "muonIPhiAtVtx"});  return GET(L1Upgrade_).muonIPhiAtVtx; }
  std::vector<short>           muonIDEta()     {  SetBranch({"L1Upgrade" , "muonIDEta"    });  return GET(L1Upgrade_).muonIDEta;     }
  std::vector<short>           muonIDPhi()     {  SetBranch({"L1Upgrade" , "muonIDPhi"    });  return GET(L1Upgrade_).muonIDPhi;     }
  std::vector<short>           muonChg()       {  SetBranch({"L1Upgrade" , "muonChg"      });  return GET(L1Upgrade_).muonChg;       }
  std::vector<unsigned short>  muonIso()       {  SetBranch({"L1Upgrade" , "muonIso"      });  return GET(L1Upgrade_).muonIso;       }
  std::vector<unsigned short>  muonQual()      {  SetBranch({"L1Upgrade" , "muonQual"     });  return GET(L1Upgrade_).muonQual;      }
  std::vector<unsigned short>  muonTfMuonIdx() {  SetBranch({"L1Upgrade" , "muonTfMuonIdx"});  return GET(L1Upgrade_).muonTfMuonIdx; }
  std::vector<short>           muonBx()        {  SetBranch({"L1Upgrade" , "muonBx"       });  return GET(L1Upgrade_).muonBx;        }
  UShort_t                     nSums()         {  SetBranch({"L1Upgrade" , "nSums"        });  return GET(L1Upgrade_).nSums;         }
  std::vector<short>           sumType()       {  SetBranch({"L1Upgrade" , "sumType"      });  return GET(L1Upgrade_).sumType;       }
  std::vector<float>           sumEt()         {  SetBranch({"L1Upgrade" , "sumEt"        });  return GET(L1Upgrade_).sumEt;         }
  std::vector<float>           sumPhi()        {  SetBranch({"L1Upgrade" , "sumPhi"       });  return GET(L1Upgrade_).sumPhi;        }
  std::vector<short>           sumIEt()        {  SetBranch({"L1Upgrade" , "sumIEt"       });  return GET(L1Upgrade_).sumIEt;        }
  std::vector<short>           sumIPhi()       {  SetBranch({"L1Upgrade" , "sumIPhi"      });  return GET(L1Upgrade_).sumIPhi;       }
  std::vector<float>           sumBx()         {  SetBranch({"L1Upgrade" , "sumBx"        });  return GET(L1Upgrade_).sumBx;         }

 private:

  virtual Long64_t  LoadTree   (Long64_t);
  virtual void      SetBranch  (const std::vector<std::string>&);
  virtual void      InitTree   (void);
  virtual Int_t     LoadEntry  (void) { return fChain_->GetEntry(entry_); }

  template <typename T>
    T GET(T* x) { return ( (x) ? *x : T() ); }

  std::unique_ptr<TChain>    fChain_;
  Int_t                      fCurrent_ = -1;
  Long64_t                   entry_;

  // POINTERS
  L1Analysis::L1AnalysisL1UpgradeDataFormat *L1Upgrade_;

  // BRANCHES
  TBranch        *b_L1Upgrade;
};

L1UpgradeTree::L1UpgradeTree()
{
}

L1UpgradeTree::~L1UpgradeTree()
{
  if (fChain_ && fChain_->GetCurrentFile()) delete fChain_->GetCurrentFile();
}

Bool_t L1UpgradeTree::GetTree(const std::string& fileName, const std::string& treeName)
{
  std::vector<std::string> fileNames = {fileName};
  return GetTree(fileNames, treeName);
}

Bool_t L1UpgradeTree::GetTree(const std::vector< std::string >& inFileName, const std::string& treeName)
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
  if (dir->GetListOfKeys()->Contains("L1UpgradeTree")  ) { fChain_.reset(new TChain((treeName+"/L1UpgradeTree").c_str()  , "L1UpgradeTree"));  }
  if (fChain_==NULL) { std::cout << "[ERROR] Tree L1UpgradeTree was not found!" << std::endl; return false; }
  // Add the files in the TChain
  for (auto& f : fileName) { fChain_->Add(Form("%s/%s/L1UpgradeTree", f.c_str(), treeName.c_str())); }; fChain_->GetEntries();
  if (!fChain_) { std::cout << "[ERROR] fChain L1UpgradeTree was not created, some input files are missing" << std::endl; return false; }
  // Initialize the input TChains (set their branches)
  InitTree();
  // Set All Branches to Status 0
  fChain_->SetBranchStatus("*",0);
  //
  return true;
}

Int_t L1UpgradeTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  entry_ = entry;
  if (LoadTree(entry_) < 0) return -1;
  Clear();
  return LoadEntry();
}

Long64_t L1UpgradeTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain_) return -5;
  Long64_t centry = fChain_->LoadTree(entry);
  if (fChain_->GetTreeNumber() != fCurrent_) { fCurrent_ = fChain_->GetTreeNumber(); }
  return centry;
}

void L1UpgradeTree::SetBranch(const std::vector<std::string>& nVec)
{
  for (const auto& n : nVec) {
    if ( fChain_->GetBranch(n.c_str()) && (fChain_->GetBranchStatus(n.c_str()) == 0) ) {
      fChain_->SetBranchStatus(Form("*%s*", n.c_str()), 1);
      LoadEntry();
    }
    if (fChain_->GetBranch(n.c_str())==NULL) { std::cout << "[ERROR] Branch " << n << " was not found!" << std::endl; }
  }
}

void L1UpgradeTree::InitTree(void)
{
  // INITIALIZE POINTERS
  L1Upgrade_ = NULL;

  if (fChain_==NULL) return;

  // SET BRANCHES
  if (fChain_->GetBranch("L1Upgrade")) { fChain_->SetBranchAddress("L1Upgrade", &L1Upgrade_, &b_L1Upgrade); }
}

void L1UpgradeTree::Clear(void)
{
  if (fChain_==NULL) return;

  // CLEAR EVENT INFO
  if (L1Upgrade_) { *L1Upgrade_ = L1Analysis::L1AnalysisL1UpgradeDataFormat(); }
}

#endif
