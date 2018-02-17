#ifndef Muon2RecoTree_h
#define Muon2RecoTree_h

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


class Muon2RecoTree {

 public :

  Muon2RecoTree();
  virtual ~Muon2RecoTree();
  virtual Bool_t       GetTree         (const std::vector< std::string >&, const std::string& treeName="l1MuonRecoTree");
  virtual Bool_t       GetTree         (const std::string&, const std::string& treeName="l1MuonRecoTree");
  virtual Int_t        GetEntry        (Long64_t);
  virtual void         SetEntry        (Long64_t entry) { entry_ = entry; }
  virtual Long64_t     GetEntries      (void) { return fChain_->GetEntries(); }
  virtual Long64_t     GetTreeEntries  (void) { return fChain_->GetTree()->GetEntriesFast(); }
  virtual TChain*      Chain           (void) { return fChain_.get(); }
  virtual void         Clear           (void);

  // GETTER

  // Declaration of leaf types
  UShort_t        nMuons()           {  SetBranch({"Muon" , "nMuons"          });  return GET(Muon_).nMuons;           }
  vector<float>   e()                {  SetBranch({"Muon" , "e"               });  return GET(Muon_).e;                }
  vector<float>   et()               {  SetBranch({"Muon" , "et"              });  return GET(Muon_).et;               }
  vector<float>   pt()               {  SetBranch({"Muon" , "pt"              });  return GET(Muon_).pt;               }
  vector<float>   eta()              {  SetBranch({"Muon" , "eta"             });  return GET(Muon_).eta;              }
  vector<float>   phi()              {  SetBranch({"Muon" , "phi"             });  return GET(Muon_).phi;              }
  vector<bool>    isLooseMuon()      {  SetBranch({"Muon" , "isLooseMuon"     });  return GET(Muon_).isLooseMuon;      }
  vector<bool>    isMediumMuon()     {  SetBranch({"Muon" , "isMediumMuon"    });  return GET(Muon_).isMediumMuon;     }
  vector<bool>    isTightMuon()      {  SetBranch({"Muon" , "isTightMuon"     });  return GET(Muon_).isTightMuon;      }
  vector<float>   iso()              {  SetBranch({"Muon" , "iso"             });  return GET(Muon_).iso;              }
  vector<short>   hlt_isomu()        {  SetBranch({"Muon" , "hlt_isomu"       });  return GET(Muon_).hlt_isomu;        }
  vector<short>   hlt_mu()           {  SetBranch({"Muon" , "hlt_mu"          });  return GET(Muon_).hlt_mu;           }
  vector<float>   hlt_isoDeltaR()    {  SetBranch({"Muon" , "hlt_isoDeltaR"   });  return GET(Muon_).hlt_isoDeltaR;    }
  vector<float>   hlt_deltaR()       {  SetBranch({"Muon" , "hlt_deltaR"      });  return GET(Muon_).hlt_deltaR;       }
  vector<int>     passesSingleMuon() {  SetBranch({"Muon" , "passesSingleMuon"});  return GET(Muon_).passesSingleMuon; }
  vector<int>     charge()           {  SetBranch({"Muon" , "charge"          });  return GET(Muon_).charge;           }
  vector<double>  met()              {  SetBranch({"Muon" , "met"             });  return GET(Muon_).met;              }
  vector<double>  mt()               {  SetBranch({"Muon" , "mt"              });  return GET(Muon_).mt;               }
  vector<float>   etaSt1()           {  SetBranch({"Muon" , "etaSt1"          });  return GET(Muon_).etaSt1;           }
  vector<float>   phiSt1()           {  SetBranch({"Muon" , "phiSt1"          });  return GET(Muon_).phiSt1;           }
  vector<float>   etaSt2()           {  SetBranch({"Muon" , "etaSt2"          });  return GET(Muon_).etaSt2;           }
  vector<float>   phiSt2()           {  SetBranch({"Muon" , "phiSt2"          });  return GET(Muon_).phiSt2;           }

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
  L1Analysis::L1AnalysisRecoMuon2DataFormat *Muon_;

  // BRANCHES
  TBranch        *b_Muon;
};

Muon2RecoTree::Muon2RecoTree()
{
}

Muon2RecoTree::~Muon2RecoTree()
{
  if (fChain_ && fChain_->GetCurrentFile()) delete fChain_->GetCurrentFile();
}

Bool_t Muon2RecoTree::GetTree(const std::string& fileName, const std::string& treeName)
{
  std::vector<std::string> fileNames = {fileName};
  return GetTree(fileNames, treeName);
}

Bool_t Muon2RecoTree::GetTree(const std::vector< std::string >& inFileName, const std::string& treeName)
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
  if (dir->GetListOfKeys()->Contains("Muon2RecoTree")  ) { fChain_.reset(new TChain((treeName+"/Muon2RecoTree").c_str()  , "Muon2RecoTree"));  }
  if (fChain_==NULL) { std::cout << "[ERROR] Tree Muon2RecoTree was not found!" << std::endl; return false; }
  // Add the files in the TChain
  for (auto& f : fileName) { fChain_->Add(Form("%s/%s/Muon2RecoTree", f.c_str(), treeName.c_str())); }; fChain_->GetEntries();
  if (!fChain_) { std::cout << "[ERROR] fChain Muon2RecoTree was not created, some input files are missing" << std::endl; return false; }
  // Initialize the input TChains (set their branches)
  InitTree();
  // Set All Branches to Status 0
  fChain_->SetBranchStatus("*",0);
  //
  return true;
}

Int_t Muon2RecoTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  entry_ = entry;
  if (LoadTree(entry_) < 0) return -1;
  Clear();
  return LoadEntry();
}

Long64_t Muon2RecoTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain_) return -5;
  Long64_t centry = fChain_->LoadTree(entry);
  if (fChain_->GetTreeNumber() != fCurrent_) { fCurrent_ = fChain_->GetTreeNumber(); }
  return centry;
}

void Muon2RecoTree::SetBranch(const std::vector<std::string>& nVec)
{
  for (const auto& n : nVec) {
    if ( fChain_->GetBranch(n.c_str()) && (fChain_->GetBranchStatus(n.c_str()) == 0) ) {
      fChain_->SetBranchStatus(Form("*%s*", n.c_str()), 1);
      LoadEntry();
    }
    if (fChain_->GetBranch(n.c_str())==NULL) { std::cout << "[ERROR] Branch " << n << " was not found!" << std::endl; }
  }
}

void Muon2RecoTree::InitTree(void)
{
  // INITIALIZE POINTERS
  Muon_ = NULL;

  if (fChain_==NULL) return;

  // SET BRANCHES
  if (fChain_->GetBranch("Muon")) { fChain_->SetBranchAddress("Muon", &Muon_, &b_Muon); }
}

void Muon2RecoTree::Clear(void)
{
  if (fChain_==NULL) return;

  // CLEAR EVENT INFO
  if (Muon_) { *Muon_ = L1Analysis::L1AnalysisRecoMuon2DataFormat(); }
}

#endif
