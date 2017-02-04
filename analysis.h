//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 24 14:08:23 2017 by ROOT version 6.08/02
// from TTree ztree/Jet track tree
// found on file: g.pp-photonHLTFilter-v0-HiForest-tutorial.root
//////////////////////////////////////////////////////////

#ifndef analysis_h
#define analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class analysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           isPP;
   UInt_t          run;
   ULong64_t       evt;
   UInt_t          lumi;
   Float_t         vz;
   Int_t           njet;
   Float_t         jetpt[5];   //[njet]
   Float_t         jetptCorr[5];   //[njet]
   Float_t         jeteta[5];   //[njet]
   Float_t         jetphi[5];   //[njet]
   Int_t           nTrk;
   Float_t         trkPt[95];   //[nTrk]
   Float_t         trkEta[95];   //[nTrk]
   Float_t         trkPhi[95];   //[nTrk]
   Int_t           trkCharge[95];   //[nTrk]
   Bool_t          highPurity[95];   //[nTrk]
   Float_t         trkWeight[95];   //[nTrk]
   Int_t           nPho;
   Float_t         phoE[1];   //[nPho]
   Float_t         phoEt[1];   //[nPho]
   Float_t         phoEtCorrected[1];   //[nPho]
   Float_t         phoEta[1];   //[nPho]
   Float_t         phoPhi[1];   //[nPho]

   // List of branches
   TBranch        *b_isPP;   //!
   TBranch        *b_run;   //!
   TBranch        *b_evt;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_njet;   //!
   TBranch        *b_jetpt;   //!
   TBranch        *b_jetptCorr;   //!
   TBranch        *b_jeteta;   //!
   TBranch        *b_jetphi;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
   TBranch        *b_trkCharge;   //!
   TBranch        *b_highPurity;   //!
   TBranch        *b_trkWeight;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEtCorrected;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!

   analysis(TTree *tree=0);
   virtual ~analysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(double track_cut, double momentum_cut);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analysis_cxx
analysis::analysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("g.pp-photonHLTFilter-v0-HiForest-tutorial.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("g.pp-photonHLTFilter-v0-HiForest-tutorial.root");
      }
      f->GetObject("ztree",tree);

   }
   Init(tree);
}

analysis::~analysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("isPP", &isPP, &b_isPP);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("njet", &njet, &b_njet);
   fChain->SetBranchAddress("jetpt", jetpt, &b_jetpt);
   fChain->SetBranchAddress("jetptCorr", jetptCorr, &b_jetptCorr);
   fChain->SetBranchAddress("jeteta", jeteta, &b_jeteta);
   fChain->SetBranchAddress("jetphi", jetphi, &b_jetphi);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("trkPt", trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkEta", trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", trkPhi, &b_trkPhi);
   fChain->SetBranchAddress("trkCharge", trkCharge, &b_trkCharge);
   fChain->SetBranchAddress("highPurity", highPurity, &b_highPurity);
   fChain->SetBranchAddress("trkWeight", trkWeight, &b_trkWeight);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoE", phoE, &b_phoE);
   fChain->SetBranchAddress("phoEt", phoEt, &b_phoEt);
   fChain->SetBranchAddress("phoEtCorrected", phoEtCorrected, &b_phoEtCorrected);
   fChain->SetBranchAddress("phoEta", phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", phoPhi, &b_phoPhi);
   Notify();
}

Bool_t analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analysis_cxx
