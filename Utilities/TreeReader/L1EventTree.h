#ifndef L1EventTree_h
#define L1EventTree_h

// Header file for ROOT classes
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for c++ classes
#include <iostream>
#include <string>
#include <memory>

// Header file for the classes stored in the Tree
#include "./DataFormats/L1TNtuples/L1AnalysisAllDataformats.h"


class L1EventTree {

 public :

  L1EventTree();
  virtual ~L1EventTree();
  virtual Bool_t       GetTree         (const std::vector< std::string >&, const std::string& treeName="l1EventTree");
  virtual Bool_t       GetTree         (const std::string&, const std::string& treeName="l1EventTree");
  virtual Int_t        GetEntry        (Long64_t);
  virtual void         SetEntry        (Long64_t entry) { entry_ = entry; }
  virtual Long64_t     GetEntries      (void) { return fChain_->GetEntries(); }
  virtual Long64_t     GetTreeEntries  (void) { return fChain_->GetTree()->GetEntriesFast(); }
  virtual TChain*      Chain           (void) { return fChain_.get(); }
  virtual void         Clear           (void);

  // GETTER

  // Declaration of leaf types
  UInt_t                run()       {  SetBranch({"Event" , "run"     });  return GET(Event_).run;      }
  ULong64_t             event()     {  SetBranch({"Event" , "event"   });  return GET(Event_).event;    }
  UInt_t                lumi()      {  SetBranch({"Event" , "lumi"    });  return GET(Event_).lumi;     }
  UInt_t                bx()        {  SetBranch({"Event" , "bx"      });  return GET(Event_).bx;       }
  ULong64_t             orbit()     {  SetBranch({"Event" , "orbit"   });  return GET(Event_).orbit;    }
  ULong64_t             time()      {  SetBranch({"Event" , "time"    });  return GET(Event_).time;     }
  Int_t                 nPV()       {  SetBranch({"Event" , "nPV"     });  return GET(Event_).nPV;      }
  Int_t                 nPV_True()  {  SetBranch({"Event" , "nPV_True"});  return GET(Event_).nPV_True; }
  std::vector<TString>  hlt()       {  SetBranch({"Event" , "hlt"     });  return GET(Event_).hlt;      }
  Double_t              puWeight()  {  SetBranch({"Event" , "puWeight"});  return GET(Event_).puWeight; }

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
  L1Analysis::L1AnalysisEventDataFormat *Event_;

  // BRANCHES
  TBranch        *b_Event;
};

L1EventTree::L1EventTree()
{
}

L1EventTree::~L1EventTree()
{
  if (fChain_ && fChain_->GetCurrentFile()) delete fChain_->GetCurrentFile();
}

Bool_t L1EventTree::GetTree(const std::string& fileName, const std::string& treeName)
{
  std::vector<std::string> fileNames = {fileName};
  return GetTree(fileNames, treeName);
}

Bool_t L1EventTree::GetTree(const std::vector< std::string >& inFileName, const std::string& treeName)
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
  if (dir->GetListOfKeys()->Contains("L1EventTree")  ) { fChain_.reset(new TChain((treeName+"/L1EventTree").c_str()  , "L1EventTree"));  }
  if (fChain_==NULL) { std::cout << "[ERROR] Tree L1EventTree was not found!" << std::endl; return false; }
  // Add the files in the TChain
  for (auto& f : fileName) { fChain_->Add(Form("%s/%s/L1EventTree", f.c_str(), treeName.c_str())); }; fChain_->GetEntries();
  if (!fChain_) { std::cout << "[ERROR] fChain L1EventTree was not created, some input files are missing" << std::endl; return false; }
  // Initialize the input TChains (set their branches)
  InitTree();
  // Set All Branches to Status 0
  fChain_->SetBranchStatus("*",0);
  //
  return true;
}

Int_t L1EventTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  entry_ = entry;
  if (LoadTree(entry_) < 0) return -1;
  Clear();
  return LoadEntry();
}

Long64_t L1EventTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain_) return -5;
  Long64_t centry = fChain_->LoadTree(entry);
  if (fChain_->GetTreeNumber() != fCurrent_) { fCurrent_ = fChain_->GetTreeNumber(); }
  return centry;
}

void L1EventTree::SetBranch(const std::vector<std::string>& nVec)
{
  for (const auto& n : nVec) {
    if ( fChain_->GetBranch(n.c_str()) && (fChain_->GetBranchStatus(n.c_str()) == 0) ) {
      fChain_->SetBranchStatus(Form("*%s*", n.c_str()), 1);
      LoadEntry();
    }
    if (fChain_->GetBranch(n.c_str())==NULL) { std::cout << "[ERROR] Branch " << n << " was not found!" << std::endl; }
  }
}

void L1EventTree::InitTree(void)
{
  // INITIALIZE POINTERS
  Event_ = NULL;

  if (fChain_==NULL) return;

  // SET BRANCHES
  if (fChain_->GetBranch("Event")) { fChain_->SetBranchAddress("Event", &Event_, &b_Event); }
}

void L1EventTree::Clear(void)
{
  if (fChain_==NULL) return;

  // CLEAR EVENT INFO
  if (Event_) { *Event_ = L1Analysis::L1AnalysisEventDataFormat(); }
}

#endif
