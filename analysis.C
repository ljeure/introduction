#define analysis_cxx
#include "analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <map>

void analysis::Loop(double track_cut, double momentum_cut)
{
//   In a ROOT session, you can do:
//      root> .L analysis.C
//      root> analysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile * outputfile = new TFile("outfilename.root", "recreate");
   TH1D * htrkPt = new TH1D("htrkPt", 
       "average track momentum;number of collisions;average track momentum",
       100,0.2,100);
   TH1D * htrkPt2 = new TH1D("htrkPt2", 
       "track momentum v. number of tracks;number of tracks in event; mean track momentum *10",
       100,0.2,10.8);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   // for avg track momentum v # tracks in event
   std::map <int, double> sum_avg_momentum;
   std::map <int, int> entries_avg_momentum;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (nTrk < track_cut+1) continue;

      Long64_t total_track_Pt = 0;
      for (int itrk = 0 ; itrk< nTrk ; itrk++) {
        if(trkPt[itrk]>momentum_cut) continue;
        total_track_Pt += trkPt[itrk];
      }
      Long64_t avg_track_Pt = total_track_Pt / nTrk;

      htrkPt->Fill(avg_track_Pt);

      // track mometum changing as function of number of tracks
      Long64_t total_track_Pt2 = 0;
      for (int itrk = 0 ; itrk< nTrk ; itrk++) {
        total_track_Pt2 += trkPt[itrk];
      }
      Long64_t avg_track_Pt2 = total_track_Pt2 / nTrk;

      // if map entry doesn't exist for this number of tracks, create it
      if ( sum_avg_momentum.find(nTrk) == sum_avg_momentum.end() ) {
        sum_avg_momentum[nTrk] = avg_track_Pt2;
        entries_avg_momentum[nTrk] = 1;
      }
      else {
        sum_avg_momentum[nTrk] += avg_track_Pt2;
        entries_avg_momentum[nTrk] += 1;
      }
   }

   for(std::map<int,double>::iterator iter = sum_avg_momentum.begin(); iter != sum_avg_momentum.end(); ++iter)
   {
     int k =  iter->first;
     if (k==3) continue;
     int avg_times_10 = (int) (sum_avg_momentum[k] / entries_avg_momentum[k] * 10);
     for (int i = 0; i < avg_times_10; i++) {
       htrkPt2->Fill(k);
     }
   }

   outputfile->Write();
   outputfile->Close();
}

int main(int argc, char *argv[])
{
  analysis * ana = new analysis();

  double track_cut = atof (argv[1]);
  double momentum_cut = atof (argv[2]);
  std::cout << "cut track at " << track_cut << std::endl;
  std::cout << "cut p at " << momentum_cut << std::endl;


  ana->Loop(track_cut, momentum_cut);
  return 0;
}
