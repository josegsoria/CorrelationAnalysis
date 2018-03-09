#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include <TROOT.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH2D.h>
#include <THStack.h>
#include <TProfile.h>
#include <iostream>
#include <fstream>

//int main(int argc, char *argv[])
int main()
{
//    if (argc < 3){
//     std::cout<<"Syntax is [Command] [Same_Event_root_file] [Mixed_Event_root_file]"<<std::endl;
//     exit(EXIT_FAILURE);
//   }

  //TFile *corr = TFile::Open((TString)argv[1]);
  TFile *corr = TFile::Open("fout_frixione.root");
  if (corr == NULL) {
    std::cout << "file 1 fail" << std::endl;
    exit(EXIT_FAILURE);
    }

  TFile *mix = TFile::Open("fout_mixed_frixione.root");  
  if (mix == NULL) {
    std::cout << " file 2 fail" << std::endl;
    exit(EXIT_FAILURE);
  }

  int nztbins = 7;
  float* ztbins;
  ztbins = new float[nztbins+1];
  ztbins[0] = 0.0; ztbins[1] = 0.1; ztbins[2] = 0.2; ztbins[3] = 0.4; ztbins[4] = 0.6; ztbins[5] = 0.8; ztbins[6] = 1.0; ztbins[7] = 1.2;

  TH2F* Corr_Iso_same[nztbins]; 
  TH2F* Corr_Iso_mix[nztbins];

  TH2F* Corr_AntiIso_same[nztbins];
  TH2F* Corr_AntiIso_mix[nztbins];

  TH1D* IsoPhiProj[nztbins];
  TH1D* AntiIsoPhiProj[nztbins];
  for (int izt = 0; izt<nztbins; izt++){
    Corr_Iso_same[izt] = (TH2F*)corr->Get(Form("IsoCorrelation_ztmin%1.0f_ztmax%1.0f",10*ztbins[izt],10*ztbins[izt+1]));
   if (Corr_Iso_same[izt] == NULL) {
      std::cout << "tree 1 fail" << std::endl;
      exit(EXIT_FAILURE);}

    Corr_Iso_mix[izt] = (TH2F*)mix->Get(Form("IsoCorrelation_ztmin%1.0f_ztmax%1.0f",10*ztbins[izt],10*ztbins[izt+1]));
    if (Corr_Iso_mix[izt] == NULL) {
      std::cout << "tree 2 fail" << std::endl;
      exit(EXIT_FAILURE);
    }

    Corr_AntiIso_same[izt] = (TH2F*)corr->Get(Form("AntiIsoCorrelation_ztmin%1.0f_ztmax%1.0f",10*ztbins[izt],10*ztbins[izt+1]));
    if (Corr_AntiIso_same[izt] == NULL) {
      std::cout << "tree 1 fail" << std::endl;
      exit(EXIT_FAILURE);}

    Corr_AntiIso_mix[izt] = (TH2F*)mix->Get(Form("AntiIsoCorrelation_ztmin%1.0f_ztmax%1.0f",10*ztbins[izt],10*ztbins[izt+1]));
    if (Corr_Iso_mix[izt] == NULL) {
      std::cout << "tree 2 fail" << std::endl;
      exit(EXIT_FAILURE);
    }

    //Normalize Mixing to 1 at ∆eta∆phi = 0,0
    TAxis *mix_Iso_xaxis = Corr_Iso_mix[izt]->GetXaxis();
    Int_t mix_Iso_bin_phi = mix_Iso_xaxis->FindBin(0.0);
    TAxis *mix_Iso_yaxis = Corr_Iso_mix[izt]->GetYaxis();
    Int_t mix_Iso_bin_eta = mix_Iso_yaxis->FindBin(0.0);
    Double_t mix_Iso_integ = Corr_Iso_mix[izt]->Integral(mix_Iso_bin_phi,mix_Iso_bin_phi,mix_Iso_bin_eta,mix_Iso_bin_eta);
    std::cout<<"Iso Mix Integ: "<<mix_Iso_integ<<std::endl;
    Double_t Iso_norm = 1/mix_Iso_integ;
    Corr_Iso_mix[izt]->Scale(Iso_norm);

    TAxis *mix_AntiIso_xaxis = Corr_AntiIso_mix[izt]->GetXaxis();
    Int_t mix_AntiIso_bin_phi = mix_AntiIso_xaxis->FindBin(0.0);
    TAxis *mix_AntiIso_yaxis = Corr_AntiIso_mix[izt]->GetYaxis();
    Int_t mix_AntiIso_bin_eta = mix_AntiIso_yaxis->FindBin(0.0);
    Double_t mix_AntiIso_integ = Corr_AntiIso_mix[izt]->Integral(mix_AntiIso_bin_phi,mix_AntiIso_bin_phi,mix_AntiIso_bin_eta,mix_AntiIso_bin_eta);
    std::cout<<"Anti Iso Mix Integral: "<<mix_AntiIso_integ<<std::endl;
    Double_t AntiIso_norm = 1/mix_AntiIso_integ;
    Corr_AntiIso_mix[izt]->Scale(AntiIso_norm);

    //Divide
    Corr_Iso_same[izt]->Divide(Corr_Iso_mix[izt]);
    Corr_AntiIso_same[izt]->Divide(Corr_Iso_mix[izt]);

    //Phi Projection
    TAxis *same_Iso_yaxis = Corr_Iso_same[izt]->GetYaxis();
    Int_t bin_Iso_eta_neg = same_Iso_yaxis->FindBin(-0.6);
    Int_t bin_Iso_eta_pos = same_Iso_yaxis->FindBin(0.6);
    IsoPhiProj[izt] =Corr_Iso_same[izt]->ProjectionX(Form("Iso_Phi_Projection_ztmin%1.0f_ztmax%1.0f",10*ztbins[izt],10*ztbins[izt+1]),bin_Iso_eta_neg,bin_Iso_eta_pos);
    IsoPhiProj[izt]->SetTitle(Form("Isolated #Delta#phi Projection  %1.0f < z_{T} < %1.0f",10*ztbins[izt],10*ztbins[izt+1]));

    TAxis *same_AntiIso_yaxis = Corr_AntiIso_same[izt]->GetYaxis();
    Int_t bin_AntiIso_eta_neg = same_AntiIso_yaxis->FindBin(-0.6);
    Int_t bin_AntiIso_eta_pos = same_AntiIso_yaxis->FindBin(0.6);
    std::cout<<"Entries: "<<Corr_AntiIso_same[izt]->GetEntries()<<std::endl;
    AntiIsoPhiProj[izt] =Corr_AntiIso_same[izt]->ProjectionX(Form("Anti_Phi_Projection_ztmin%1.0f_ztmax%1.0f",10*ztbins[izt],10*ztbins[izt+1]),bin_AntiIso_eta_neg,bin_AntiIso_eta_pos);
    AntiIsoPhiProj[izt]->SetTitle(Form("Anti Isolated #Delta#phi Projection  %1.0f < z_{T} < %1.0f",10*ztbins[izt],10*ztbins[izt+1]));
  }
  
  TFile *MyFile = new TFile("Ratio_Correlation.root","RECREATE");

  for (int izt = 0; izt<nztbins; izt++){
    Corr_Iso_same[izt]->GetXaxis()->SetTitle("#Delta #phi");
    Corr_Iso_same[izt]->GetYaxis()->SetTitle("#Delta #eta");
    Corr_Iso_same[izt]->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^2N}{d#Delta #phi d#Delta #eta}");
    Corr_Iso_mix[izt]->GetZaxis()->SetTitleOffset(1.6);
    Corr_Iso_same[izt]->SetTitle(Form("Isolated #gamma-H  %1.0f < z_{T} < %1.0f",10*ztbins[izt],10*ztbins[izt+1]));
    Corr_Iso_same[izt]->Write();
  }

  for (int izt = 0; izt<nztbins; izt++){
    Corr_AntiIso_same[izt]->GetXaxis()->SetTitle("#Delta #phi");
    Corr_AntiIso_same[izt]->GetYaxis()->SetTitle("#Delta #eta");
    Corr_AntiIso_same[izt]->GetZaxis()->SetTitle("#frac{1}{N_{trig}}#frac{d^2N}{d#Delta #phi d#Delta #eta}");
    Corr_AntiIso_mix[izt]->GetZaxis()->SetTitleOffset(1.6);
    Corr_AntiIso_same[izt]->SetTitle(Form("AntiIsolated #gamma-H  %1.0f < z_{T} < %1.0f",10*ztbins[izt],10*ztbins[izt+1]));
    Corr_AntiIso_same[izt]->Write();
  }

  for (int izt = 0; izt<nztbins; izt++){
    IsoPhiProj[izt]->Write();
  }

  for (int izt = 0; izt<nztbins; izt++){
    AntiIsoPhiProj[izt]->Write();
  }

  MyFile->Close();
}
