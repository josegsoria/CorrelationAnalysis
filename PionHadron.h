#ifndef PIONHADRON_H
#define PIONHADRON_H

// $Id$
#include "AliAnalysisTaskEmcal.h"
#include "AliEventPoolManager.h"
#include <THn.h>
#include "AliStaObjects.h"
#include "AliEventCuts.h"

class TH1;
class TH2;
class TH3;
class THnSparse;
class THnSparse;
class AliVVZERO;
class AliEvtPoolManager;

using std::vector;

class PionHadron : public AliAnalysisTaskEmcal {
 public:
	PionHadron();
	PionHadron(Bool_t InputSameEventAnalysis);
virtual ~PionHadron();

  void SetEffHistGamma(THnF *h)                              { fHistEffGamma    = h      ; }
  void SetEffHistHadron(THnF *h)                             { fHistEffHadron   = h      ; }
  void SetSavePool(Bool_t input)                             { fSavePool        = input  ; }
  void SetEvtTriggerType(UInt_t input)                       { fTriggerType     = input  ; }
  void SetEvtMixType(UInt_t input)                           { fMixingEventType = input  ; }
  void SetUseManualEvtCuts(Bool_t input)                     { fUseManualEventCuts = input;}

  //Functions for mixed event purposes
  void SetExternalEventPoolManager(AliEventPoolManager* mgr) {fPoolMgr = mgr;}
  AliEventPoolManager*        GetEventPoolManager()                                 {return fPoolMgr;}
  // Set which pools will be saved
  void AddEventPoolsToOutput(Double_t minCent, Double_t maxCent,  Double_t minZvtx, Double_t maxZvtx, Double_t minPt, Double_t maxPt);
  
  private:
  AliEventCuts fEventCuts;                   ///< event selection utility
  
  void                        InitArrays()                                                 ;
  // overwritten EMCal framework functions
  Bool_t                      Run()                             	                          ;
  void                        ExecOnce()         									      ;
  Bool_t                      IsEventSelected()											  ;
  void                        UserCreateOutputObjects()        		                      ;
  
  //Functions for mixed event purposes
  void                        InitEventMixer()											  ;
  TObjArray*                  CloneToCreateTObjArray(AliParticleContainer* tracks)          ;

  Bool_t                      FillHistograms()                                              ;
  
  void                        FillClusterHisto(AliVCluster* cluster, THnSparse* histo);
  void                        FillPionHisto(AliVCluster* cluster1, AliVCluster* cluster2, THnSparse* histo);
  void                        FillCorrelation(AliVCluster* cluster1, AliVCluster* cluster2, AliVParticle* track, THnSparse* histo, double weight);
  Int_t                       CorrelateClusterAndTrack(AliParticleContainer* tracks,TObjArray* bgTracks,Bool_t SameMix, Double_t Weight);
  Bool_t                      PassedCuts(AliVCluster* caloCluster);
  double                      GetIsolation_Track(AliVCluster* cluster);
  
   //<<<<<><<<<<<<<<><<<<<<<<<<><<<<<<<<<<<<><<<<<<<<<<<<<<><<<<<<<<<<<<<<<<<<<<<>
  TObjArray*                  CloneClustersTObjArray(AliClusterContainer* clusters)          ;
  Double_t                    GetEff(AliTLorentzVector ParticleVec)                         ;

  Bool_t                      fSavePool;                 ///< Defines whether to save output pools in a root file
  Bool_t                      fUseManualEventCuts;       ///< Use manual cuts if automatic setup is not available for the period
  
  //..Input histograms
  THnF                       *fHistEffGamma;             ///< ??input efficiency for trigger particles
  THnF                       *fHistEffHadron;            ///< ??input efficiency for associate particles

  //..Constant
  static const Int_t          kNvertBins=20;             ///< vertex bins in which the ME are mixed
  static const Int_t          kNcentBins=8;              ///< centrality bins in which the ME are mixed
  Double_t                    fArrayNVertBins[21];       ///< 21=kNvertBins+1

  //..Event pool variables
  TAxis                      *fMixBCent;                 ///< Number of centrality bins for the mixed event
  TAxis                      *fMixBZvtx;                 ///< Number of vertex bins for the mixed event
  AliEventPoolManager        *fPoolMgr;                  ///< event pool manager
  Int_t                       fTrackDepth;               ///<  #tracks to fill pool
  Int_t                       fPoolSize;                 ///<  Maximum number of events
  vector<vector<Double_t> >   fEventPoolOutputList;      //!<! ???vector representing a list of pools (given by value range) that will be saved
  //..Event selection types
  UInt_t                      fTriggerType;              ///<  Event types that are used for the trigger (gamma or pi0)
  UInt_t                      fMixingEventType;          ///<  Event types that are used for the tracks in the mixed event
  UInt_t                      fCurrentEventTrigger;      //!<! Trigger of the current event

   // THnSparse
  //THnSparse                 *h_Track;                   //!<!
  THnSparse                 *h_Cluster;                 //!<!
  THnSparse                 *h_Pi0;                 //!<!
  THnSparse                 *h_Pi0Track;                 //!<! THnSparse with info on pi0 and track.
  THnSparse                 *h_Pi0Track_Mixed;                 //!<!
  // Other stuff
  TList                      *fEventCutList;           //!<! Output list for event cut histograms
 // TList                      *OutputList;            //!<! Output list
  
  const static int nEvt      =   10;//30; // mixing "depth"

  private:
  PionHadron(const PionHadron&);            // not implemented
  PionHadron &operator=(const PionHadron&); // not implemented
  ClassDef(PionHadron, 10) // Class to analyse gamma hadron correlations
};
#endif



