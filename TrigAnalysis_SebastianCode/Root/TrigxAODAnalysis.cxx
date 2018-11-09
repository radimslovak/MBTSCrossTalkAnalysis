#include <AsgTools/MessageCheck.h>
//#include <EventLoop/Job.h>
//#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>
#include <TrigAnalysis/TrigxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>
#include <TSystem.h>
#include <xAODJet/JetContainer.h>
#include "xAODHIEvent/HIEventShapeContainer.h"
#include <xAODMuon/MuonContainer.h>
#include "xAODTrigger/JetRoIContainer.h"
#include "xAODTrigger/JetRoIAuxContainer.h"
#include <TFile.h>
#include <PATInterfaces/CorrectionCode.h> // to check the return correction code status of tools
#include <xAODCore/ShallowAuxContainer.h>
#include <xAODCore/ShallowCopy.h>



TrigxAODAnalysis :: TrigxAODAnalysis (const std::string& name,
                                  ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm (name, pSvcLocator),
      m_grl ("GoodRunsListSelectionTool/grl", this),
      m_trigDecisionTool ("Trig::TrigDecisionTool/TrigDecisionTool"),	
      m_trigConfigTool("TrigConf::xAODConfigTool/xAODConfigTool"),
      m_muonSelection ("CP::MuonSelectionTool", this),
      m_muonCalibrationAndSmearingTool ("CP::MuonCalibrationAndSmearingTool/MuonCorrectionTool",this)
      //m_trkSelection ("InDet::InDetTrackSelectionTool",this)
{
 
}


StatusCode TrigxAODAnalysis :: initialize ()
{
  ANA_MSG_INFO ("in initialize");

  TFile *outputFile = wk()->getOutputFile ("myOutput");
  m_tree = new TTree ("tree", "tree");
  m_tree->SetDirectory (outputFile);
  m_tree->Branch ("EventNumber", &m_EventNumber);
  m_tree->Branch ("RunNumber", &m_RunNumber);
  m_tree->Branch ("LumiBlock", &m_LumiBlock);
  m_tree->Branch ("Fcal", &m_FCal_Et);
  m_tree->Branch ("TriggerObject_Chain", &m_TriggerObject_Chain);
  m_tree->Branch ("TriggerObject_Ps", &m_TriggerObject_Ps);
  //MinBias
  m_tree->Branch ("HLT_noalg_eb_L1TE50",  &m_HLT_noalg_eb_L1TE50);
  m_tree->Branch ("HLT_noalg_eb_L1ZDC_A_C_VTE50",  &m_HLT_noalg_eb_L1ZDC_A_C_VTE50);
  m_tree->Branch ("HLT_noalg_eb_L1MBTS_1_1",  &m_HLT_noalg_eb_L1MBTS_1_1);
 // ROI Jet (L1) 
  m_tree->Branch ("Jet_roi_pt",  &m_Jet_roi_pt);
  m_tree->Branch ("Jet_roi_eta", &m_Jet_roi_eta);
  m_tree->Branch ("Jet_roi_phi", &m_Jet_roi_phi);
  m_tree->Branch ("Jet_roi_thrs", &m_Jet_roi_thr);
  m_tree->Branch ("Jet_roi_minthrs", &m_Jet_roi_minthr);
// Antikt4
  m_tree->Branch ("Jet_pt",   &m_Jet_pt);
  m_tree->Branch ("Jet_eta",  &m_Jet_eta);
  m_tree->Branch ("Jet_phi",  &m_Jet_phi);
  m_tree->Branch ("Jet_e",    &m_Jet_e);
// Antikt4 -- Unsubtracted
  m_tree->Branch ("Jet_us_pt",	&m_Jet_us_pt);
  m_tree->Branch ("Jet_us_eta",	&m_Jet_us_eta);
  m_tree->Branch ("Jet_us_phi",	&m_Jet_us_phi);
  m_tree->Branch ("Jet_us_e",	    &m_Jet_us_e);
// Antikt4 -- Subtracted no iteration
  m_tree->Branch ("Jet_sNoiter_pt",	&m_Jet_sNoiter_pt);
  m_tree->Branch ("Jet_sNoiter_eta",	&m_Jet_sNoiter_eta);
  m_tree->Branch ("Jet_sNoiter_phi",	&m_Jet_sNoiter_phi);
  m_tree->Branch ("Jet_sNoiter_e",	&m_Jet_sNoiter_e);
// Antikt4 -- Subtracted
  m_tree->Branch ("Jet_s_pt",	    &m_Jet_s_pt);
  m_tree->Branch ("Jet_s_eta",	    &m_Jet_s_eta);
  m_tree->Branch ("Jet_s_phi",	    &m_Jet_s_phi);
  m_tree->Branch ("Jet_s_e",	    &m_Jet_s_e);
// Antikt4 -- EMScale
  m_tree->Branch ("Jet_em_pt",   &m_Jet_em_pt);
  m_tree->Branch ("Jet_em_eta",  &m_Jet_em_eta);
  m_tree->Branch ("Jet_em_phi",  &m_Jet_em_phi);
  m_tree->Branch ("Jet_em_e",    &m_Jet_em_e);
// Antikt4 -- trigger
  m_tree->Branch ("Jet_trig_pt",      &m_Jet_trig_pt);
  m_tree->Branch ("Jet_trig_eta",     &m_Jet_trig_eta);
  m_tree->Branch ("Jet_trig_phi",     &m_Jet_trig_phi);
  m_tree->Branch ("Jet_trig_e",       &m_Jet_trig_e);
// Antikt4 -- trigger Unsubtracted
  m_tree->Branch ("Jet_trig_us_pt", &m_Jet_trig_us_pt);
  m_tree->Branch ("Jet_trig_us_eta", &m_Jet_trig_us_eta);
  m_tree->Branch ("Jet_trig_us_phi", &m_Jet_trig_us_phi);
  m_tree->Branch ("Jet_trig_us_e", &m_Jet_trig_us_e);
// Antikt4 -- trigger Subtracted no iteration
  m_tree->Branch ("Jet_trig_sNoiter_pt", &m_Jet_trig_sNoiter_pt);
  m_tree->Branch ("Jet_trig_sNoiter_eta", &m_Jet_trig_sNoiter_eta);
  m_tree->Branch ("Jet_trig_sNoiter_phi", &m_Jet_trig_sNoiter_phi);
  m_tree->Branch ("Jet_trig_sNoiter_e", &m_Jet_trig_sNoiter_e);
// Antikt4 -- trigger Subtracted
  m_tree->Branch ("Jet_trig_s_pt", &m_Jet_trig_s_pt);
  m_tree->Branch ("Jet_trig_s_eta", &m_Jet_trig_s_eta);
  m_tree->Branch ("Jet_trig_s_phi", &m_Jet_trig_s_phi);
  m_tree->Branch ("Jet_trig_s_e", &m_Jet_trig_s_e);
// Antikt4 -- trigger EMScale
  m_tree->Branch ("Jet_trig_em_pt",   &m_Jet_trig_em_pt);
  m_tree->Branch ("Jet_trig_em_eta",  &m_Jet_trig_em_eta);
  m_tree->Branch ("Jet_trig_em_phi",  &m_Jet_trig_em_phi);
  m_tree->Branch ("Jet_trig_em_e",    &m_Jet_trig_em_e);
// Antikt4 -- Others
  m_tree->Branch ("Jet_dRmu", &m_Jet_dRmu);
  m_tree->Branch ("Jet_dRTrig", &m_Jet_dRTrig);
  m_tree->Branch ("Jet_dptTrig", &m_Jet_dptTrig);
  m_tree->Branch ("Jet_dptTrigNorm", &m_Jet_dptTrigNorm);
 
 
  m_tree->Branch ("Jet_df_pt",   &m_Jet_df_pt);
  m_tree->Branch ("Jet_df_eta",  &m_Jet_df_eta);
  m_tree->Branch ("Jet_df_phi",  &m_Jet_df_phi);
  m_tree->Branch ("Jet_df_e",    &m_Jet_df_e);
  m_tree->Branch ("Jet_df_em_pt",   &m_Jet_df_em_pt);
  m_tree->Branch ("Jet_df_em_eta",  &m_Jet_df_em_eta);
  m_tree->Branch ("Jet_df_em_phi",  &m_Jet_df_em_phi);
  m_tree->Branch ("Jet_df_em_e",    &m_Jet_df_em_e);
  m_tree->Branch ("Jet_df_dRmu", &m_Jet_df_dRmu);
  m_tree->Branch ("Jet_df_dRTrig", &m_Jet_df_dRTrig);
  m_tree->Branch ("Jet_df_dptTrigNorm", &m_Jet_df_dptTrigNorm);

// DFAntikt4 -- trigger
  m_tree->Branch ("Jet_df_trig_pt",      &m_Jet_df_trig_pt);
  m_tree->Branch ("Jet_df_trig_eta",     &m_Jet_df_trig_eta);
  m_tree->Branch ("Jet_df_trig_phi",     &m_Jet_df_trig_phi);
  m_tree->Branch ("Jet_df_trig_e",       &m_Jet_df_trig_e);

  // DF R=xx
  m_tree->Branch ("Jet_df02_pt",  &m_Jet_df02_pt);
  m_tree->Branch ("Jet_df02_eta", &m_Jet_df02_eta);
  m_tree->Branch ("Jet_df02_phi", &m_Jet_df02_phi);
  m_tree->Branch ("Jet_df02_e",   &m_Jet_df02_e);
  m_tree->Branch ("Jet_df03_pt",  &m_Jet_df03_pt);
  m_tree->Branch ("Jet_df03_eta", &m_Jet_df03_eta);
  m_tree->Branch ("Jet_df03_phi", &m_Jet_df03_phi);
  m_tree->Branch ("Jet_df03_e",   &m_Jet_df03_e);
  m_tree->Branch ("Jet_df10_pt",  &m_Jet_df10_pt);
  m_tree->Branch ("Jet_df10_eta", &m_Jet_df10_eta);
  m_tree->Branch ("Jet_df10_phi", &m_Jet_df10_phi);
  m_tree->Branch ("Jet_df10_e",   &m_Jet_df10_e);

  // R=xx
  m_tree->Branch ("Jet_02_pt",  &m_Jet_02_pt);
  m_tree->Branch ("Jet_02_eta", &m_Jet_02_eta);
  m_tree->Branch ("Jet_02_phi", &m_Jet_02_phi);
  m_tree->Branch ("Jet_02_e",   &m_Jet_02_e);
  m_tree->Branch ("Jet_03_pt",  &m_Jet_03_pt);
  m_tree->Branch ("Jet_03_eta", &m_Jet_03_eta);
  m_tree->Branch ("Jet_03_phi", &m_Jet_03_phi);
  m_tree->Branch ("Jet_03_e",   &m_Jet_03_e);

  m_tree->Branch ("Muon_pt",  &m_Muon_pt);
  m_tree->Branch ("Muon_eta", &m_Muon_eta);
  m_tree->Branch ("Muon_phi", &m_Muon_phi);
  m_tree->Branch ("Muon_charge", &m_Muon_charge);
  m_tree->Branch ("Muon_eloss",  &m_Muon_eloss);
  m_tree->Branch ("Muon_e", &m_Muon_e);
  m_tree->Branch ("Muon_quality", &m_Muon_quality);
  m_tree->Branch ("Muon_dRj",    &m_Muon_dRj);
  m_tree->Branch ("Muon_id_pt",  &m_Muon_id_pt);
  m_tree->Branch ("Muon_id_eta", &m_Muon_id_eta);
  m_tree->Branch ("Muon_id_phi", &m_Muon_id_phi);
  m_tree->Branch ("Muon_id_theta", &m_Muon_id_theta);
  m_tree->Branch ("Muon_id_d0", &m_Muon_id_d0);
  m_tree->Branch ("Muon_id_z0", &m_Muon_id_z0);

 
/* const char* GRLFilePath = "$ALRB_TutorialData/data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml";
  const char* fullGRLFilePath = gSystem->ExpandPathName (GRLFilePath);
  std::vector<std::string> vecStringGRL;
  vecStringGRL.push_back(fullGRLFilePath);
  ANA_CHECK(m_grl.setProperty( "GoodRunsListVec", vecStringGRL));
  ANA_CHECK(m_grl.setProperty("PassThrough", false)); // if true (default) will ignore result of GRL and will just pass all events
  ANA_CHECK(m_grl.initialize());*/

  ANA_CHECK (m_trigConfigTool.initialize());
  ANA_CHECK (m_trigDecisionTool.setProperty ("ConfigTool", m_trigConfigTool.getHandle()));
  ANA_CHECK (m_trigDecisionTool.setProperty ("TrigDecisionKey", "xTrigDecision"));
  ANA_CHECK (m_trigDecisionTool.initialize());

  //ANA_CHECK (m_muonSelection.msg().setLevel( MSG::INFO ));
  ANA_CHECK (m_muonSelection.setProperty("TrtCutOff",true));
  ANA_CHECK (m_muonSelection.setProperty("MaxEta", 2.5)); 
  ANA_CHECK (m_muonSelection.setProperty("MuQuality", 1));
  ANA_CHECK (m_muonSelection.initialize());
 
  ANA_CHECK (m_muonCalibrationAndSmearingTool.initialize());

  //ANA_CHECK (m_trkSelection->initialize());

  return StatusCode::SUCCESS;
}

StatusCode TrigxAODAnalysis :: execute ()
{
  // retrieve the eventInfo object from the event store
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK (evtStore()->retrieve (eventInfo, "EventInfo"));
   m_EventNumber = eventInfo->eventNumber(); 
   m_RunNumber   = eventInfo->runNumber();
   m_LumiBlock   = eventInfo->lumiBlock();
   m_FCal_Et = -99; 
 
   bool isMC = false;
   // check if the event is MC
   if (eventInfo->eventType (xAOD::EventInfo::IS_SIMULATION)) {
      isMC = true; // can do something with this later
   }

// if data check if event passes GRL
/*if (!isMC) { // it's data!
    if (!m_grl->passRunLB(*eventInfo)) {
      //ANA_MSG_INFO ("drop event: GRL");
      return EL::StatusCode::SUCCESS; // go to next event
    }
  } // end if not MC
*/


    // only to be used for PbPb data
    const xAOD::HIEventShapeContainer *hiue(0);
    ANA_CHECK( evtStore()->retrieve(hiue, "CaloSums"));
    double m_fcalEt = hiue->at(5)->et();
    m_FCal_Et = m_fcalEt*1e-6;

    bool HLT_eb_L1TE50          = false;
    bool HLT_eb_L1ZDC_A_C_VTE50 = false;
    bool HLT_eb_L1MBTS_1_1      = false;
    auto chainGroup = m_trigDecisionTool->getChainGroup(".*");
    for (auto &trig : chainGroup->getListOfTriggers()) {
    auto cg = m_trigDecisionTool->getChainGroup(trig);
    if(cg->isPassed()) {
      std::string thisTrig = trig;
      m_TriggerObject_Chain.push_back(thisTrig);
      m_TriggerObject_Ps.push_back(cg->getPrescale());
      if(trig=="HLT_noalg_eb_L1TE50") HLT_eb_L1TE50 = true;
      if(trig=="HLT_noalg_eb_L1ZDC_A_C_VTE50") HLT_eb_L1ZDC_A_C_VTE50 = true;
      if(trig=="HLT_noalg_eb_L1MBTS_1_1") HLT_eb_L1MBTS_1_1 = true;
	}
    }
    m_HLT_noalg_eb_L1TE50 = HLT_eb_L1TE50;
    m_HLT_noalg_eb_L1ZDC_A_C_VTE50 = HLT_eb_L1ZDC_A_C_VTE50;
    m_HLT_noalg_eb_L1MBTS_1_1 = HLT_eb_L1MBTS_1_1;

  //if( !(HLT_eb_L1TE50 || HLT_eb_L1ZDC_A_C_VTE50 || HLT_eb_L1MBTS_1_1) ) return StatusCode::SUCCESS;
 // get jet container of interest
 
 const xAOD::JetContainer* jets = 0;
 ANA_CHECK(evtStore()->retrieve( jets, "DFAntiKt4HIJets" ));

 for (auto jet : *jets) {
  //if(jet->pt()<10000) continue;
  m_Jet_pt       .push_back( jet->pt()*1e-3);
  m_Jet_eta      .push_back( jet->eta() );
  m_Jet_phi      .push_back( jet->phi() );
  m_Jet_e        .push_back( jet->e()*1e-3 );
  m_Jet_dRmu     .push_back( dRmin_jet_muon( jet->eta(), jet->phi()) );
  m_Jet_dRTrig   .push_back( dRmin_jet_trig( jet->eta(), jet->phi()) );
  m_Jet_dptTrig  .push_back( dpt_jet_trig( jet->eta(), jet->phi(), jet->pt()) );
  m_Jet_dptTrigNorm  .push_back( dpt_jet_trignorm( jet->eta(), jet->phi(), jet->pt()) ); 
 
  const xAOD::JetFourMom_t jet_us_4mom = jet->jetP4("JetUnsubtractedScaleMomentum");
  m_Jet_us_pt    .push_back( jet_us_4mom.pt()*1e-3);
  m_Jet_us_eta   .push_back( jet_us_4mom.eta() ); 
  m_Jet_us_phi   .push_back( jet_us_4mom.phi() );
  m_Jet_us_e     .push_back( jet_us_4mom.e()*1e-3);
  //const xAOD::JetFourMom_t jet_sNoiter_4mom = jet->jetP4("JetSubtractedScaleV2OnlyMomentum");
  //m_Jet_sNoiter_pt    .push_back( jet_sNoiter_4mom.pt()*1e-3);
  //m_Jet_sNoiter_eta   .push_back( jet_sNoiter_4mom.eta() );   
  //m_Jet_sNoiter_phi   .push_back( jet_sNoiter_4mom.phi() );
  //m_Jet_sNoiter_e     .push_back( jet_sNoiter_4mom.e()*1e-3); 
  const xAOD::JetFourMom_t jet_s_4mom = jet->jetP4("JetSubtractedScaleMomentum");
  m_Jet_s_pt    .push_back( jet_s_4mom.pt()*1e-3);
  m_Jet_s_eta   .push_back( jet_s_4mom.eta() );
  m_Jet_s_phi   .push_back( jet_s_4mom.phi() );
  m_Jet_s_e     .push_back( jet_s_4mom.e()*1e-3); 
  const xAOD::JetFourMom_t jet_em_4mom = jet->jetP4("JetEMScaleMomentum");
  m_Jet_em_pt    .push_back( jet_em_4mom.pt()*1e-3);
  m_Jet_em_eta   .push_back( jet_em_4mom.eta() );
  m_Jet_em_phi   .push_back( jet_em_4mom.phi() );
  m_Jet_em_e     .push_back( jet_em_4mom.e()*1e-3);
  }// end jet loop

 const xAOD::JetContainer* trig_jets = 0;
 ANA_CHECK(evtStore()->retrieve( trig_jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfFS" ));

 for (auto trig_jet : *trig_jets) {
  if(trig_jet->pt()<10000) continue;
  m_Jet_trig_pt       .push_back( trig_jet->pt()*1e-3);
  m_Jet_trig_eta      .push_back( trig_jet->eta() );
  m_Jet_trig_phi      .push_back( trig_jet->phi() );
  m_Jet_trig_e        .push_back( trig_jet->e()*1e-3 );

  const xAOD::JetFourMom_t jet_trig_us_4mom = trig_jet->jetP4("JetUnsubtractedScaleMomentum");
  m_Jet_trig_us_pt    .push_back( jet_trig_us_4mom.pt()*1e-3);
  m_Jet_trig_us_eta   .push_back( jet_trig_us_4mom.eta() );
  m_Jet_trig_us_phi   .push_back( jet_trig_us_4mom.phi() );
  m_Jet_trig_us_e     .push_back( jet_trig_us_4mom.e()*1e-3);
  //const xAOD::JetFourMom_t jet_trig_sNoiter_4mom = trig_jet->jetP4("JetSubtractedScaleV2OnlyMomentum");
  //m_Jet_trig_sNoiter_pt    .push_back( jet_trig_sNoiter_4mom.pt()*1e-3);
  //m_Jet_trig_sNoiter_eta   .push_back( jet_trig_sNoiter_4mom.eta() );
  //m_Jet_trig_sNoiter_phi   .push_back( jet_trig_sNoiter_4mom.phi() );
  //m_Jet_trig_sNoiter_e     .push_back( jet_trig_sNoiter_4mom.e()*1e-3);
  const xAOD::JetFourMom_t jet_trig_s_4mom = trig_jet->jetP4("JetSubtractedScaleMomentum");
  m_Jet_trig_s_pt    .push_back( jet_trig_s_4mom.pt()*1e-3);
  m_Jet_trig_s_eta   .push_back( jet_trig_s_4mom.eta() );
  m_Jet_trig_s_phi   .push_back( jet_trig_s_4mom.phi() );
  m_Jet_trig_s_e     .push_back( jet_trig_s_4mom.e()*1e-3); 
  const xAOD::JetFourMom_t trig_jet_em_4mom = trig_jet->jetP4("JetEMScaleMomentum");
  m_Jet_trig_em_pt    .push_back( trig_jet_em_4mom.pt()*1e-3);
  m_Jet_trig_em_eta   .push_back( trig_jet_em_4mom.eta() );
  m_Jet_trig_em_phi   .push_back( trig_jet_em_4mom.phi() );
  m_Jet_trig_em_e     .push_back( trig_jet_em_4mom.e()*1e-3);
  }// end jet loop

 const xAOD::JetContainer* dfjets = 0;
 ANA_CHECK(evtStore()->retrieve( dfjets, "DFAntiKt4HIJets" ));//AntiKt4EMTopoJets
 
  for (auto dfjet : *dfjets) {
   //if(jet->pt()<50000) continue;
   m_Jet_df_pt       .push_back( dfjet->pt()*1e-3);
   m_Jet_df_eta      .push_back( dfjet->eta() );
   m_Jet_df_phi      .push_back( dfjet->phi() );
   m_Jet_df_e        .push_back( dfjet->e()*1e-3 );
   m_Jet_df_dRmu     .push_back( dRmin_jet_muon( dfjet->eta(), dfjet->phi()) );
   m_Jet_df_dRTrig   .push_back( dRmin_jet_df_trig( dfjet->eta(), dfjet->phi()) );
   m_Jet_df_dptTrigNorm  .push_back( dpt_jet_df_trignorm( dfjet->eta(), dfjet->phi(), dfjet->pt()) );
   const xAOD::JetFourMom_t dfjet_em_4mom = dfjet->jetP4("JetEMScaleMomentum");
   m_Jet_df_em_pt    .push_back( dfjet_em_4mom.pt()*1e-3);
   m_Jet_df_em_eta   .push_back( dfjet_em_4mom.eta() );
   m_Jet_df_em_phi   .push_back( dfjet_em_4mom.phi() );
   m_Jet_df_em_e     .push_back( dfjet_em_4mom.e()*1e-3 );
   
   }// end jet loop

 const xAOD::JetContainer* dfjets02 = 0;
 ANA_CHECK(evtStore()->retrieve( dfjets02, "DFAntiKt2HIJets" ));
  for (auto dfjet02 : *dfjets02) {
    //if(jet->pt()<50000) continue;
    m_Jet_df02_pt       .push_back( dfjet02->pt()*1e-3);
    m_Jet_df02_eta      .push_back( dfjet02->eta() );
    m_Jet_df02_phi      .push_back( dfjet02->phi() );
    m_Jet_df02_e        .push_back( dfjet02->e()*1e-3 );
  }

  const xAOD::JetContainer* dfjets03 = 0;
  ANA_CHECK(evtStore()->retrieve( dfjets03, "DFAntiKt3HIJets" ));
   for (auto dfjet03 : *dfjets03) {
     m_Jet_df03_pt       .push_back( dfjet03->pt()*1e-3);
     m_Jet_df03_eta      .push_back( dfjet03->eta() );
     m_Jet_df03_phi      .push_back( dfjet03->phi() );
     m_Jet_df03_e        .push_back( dfjet03->e()*1e-3 );
   }

  const xAOD::JetContainer* dfjets10 = 0;
  ANA_CHECK(evtStore()->retrieve( dfjets10, "DFAntiKt10HIJets" ));
   for (auto dfjet10 : *dfjets10) {
     m_Jet_df10_pt       .push_back( dfjet10->pt()*1e-3);
     m_Jet_df10_eta      .push_back( dfjet10->eta() );
     m_Jet_df10_phi      .push_back( dfjet10->phi() );
     m_Jet_df10_e        .push_back( dfjet10->e()*1e-3 );
   }

    const xAOD::JetContainer* jets02 = 0;
  ANA_CHECK(evtStore()->retrieve( jets02, "AntiKt2HIJets" ));
   for (auto jet02 : *jets02) {
     m_Jet_02_pt       .push_back( jet02->pt()*1e-3);
     m_Jet_02_eta      .push_back( jet02->eta() );
     m_Jet_02_phi      .push_back( jet02->phi() );
     m_Jet_02_e        .push_back( jet02->e()*1e-3 );
   }

  const xAOD::JetContainer* jets03 = 0;
  ANA_CHECK(evtStore()->retrieve( jets03, "AntiKt3HIJets" ));
   for (auto jet03 : *jets03) {
     m_Jet_03_pt       .push_back( jet03->pt()*1e-3);
     m_Jet_03_eta      .push_back( jet03->eta() );
     m_Jet_03_phi      .push_back( jet03->phi() );
     m_Jet_03_e        .push_back( jet03->e()*1e-3 );
   }

  const xAOD::JetContainer* trig_df_jets = 0;
  ANA_CHECK(evtStore()->retrieve( trig_df_jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfvnFS" ));

  for (auto trig_df_jet : *trig_df_jets) {
   if(trig_df_jet->pt()<10000) continue;
   m_Jet_df_trig_pt       .push_back( trig_df_jet->pt()*1e-3);
   m_Jet_df_trig_eta      .push_back( trig_df_jet->eta() );
   m_Jet_df_trig_phi      .push_back( trig_df_jet->phi() );
   m_Jet_df_trig_e        .push_back( trig_df_jet->e()*1e-3 );
   }

 const xAOD::JetRoIContainer * l1_jet = 0;
 ANA_CHECK(evtStore()->retrieve( l1_jet, "LVL1JetRoIs" ));
 
 xAOD::JetRoIContainer::const_iterator L1jet_itr = l1_jet->begin();
 xAOD::JetRoIContainer::const_iterator L1jet_end = l1_jet->end();

 for (; L1jet_itr != L1jet_end; ++L1jet_itr) {
  m_Jet_roi_pt       .push_back( (*L1jet_itr)->et4x4());
  m_Jet_roi_eta      .push_back( (*L1jet_itr)->eta() );
  m_Jet_roi_phi      .push_back( (*L1jet_itr)->phi() );
  m_Jet_roi_thr      .push_back( (*L1jet_itr)->thrValues() );
  if ( (*L1jet_itr)->thrValues().size()!=0 ){
    m_Jet_roi_minthr .push_back( (*L1jet_itr)->thrValues().at(0) );
     }
   }// end RoI jet loop

 const xAOD::MuonContainer* muons = 0;
 ANA_CHECK(evtStore()->retrieve( muons, "Muons" ));
 
 auto muons_shallowCopy = xAOD::shallowCopyContainer( *muons );
 std::unique_ptr<xAOD::MuonContainer> muonsSC (muons_shallowCopy.first);
 std::unique_ptr<xAOD::ShallowAuxContainer> muonsAuxSC (muons_shallowCopy.second);

 for (auto muonSC : *muonsSC) {
  if(m_muonCalibrationAndSmearingTool->applyCorrection(*muonSC)!= CP::CorrectionCode::Ok){
       ANA_MSG_INFO ("execute(): Problem with Muon Calibration And Smearing Tool (Error or OutOfValidityRange) ");
  }
  if ( !m_muonSelection->accept(*muonSC) ) continue;
  //if (muonSC->pt()<4000) continue;
  m_Muon_pt       .push_back( muonSC->pt()*1e-3);
  m_Muon_eta      .push_back( muonSC->eta() );
  m_Muon_phi      .push_back( muonSC->phi() );
  m_Muon_charge   .push_back( muonSC->charge() );
  m_Muon_e   .push_back( muonSC->e()*1e-3 );
  m_Muon_eloss    .push_back( muonSC->floatParameter(xAOD::Muon::EnergyLoss)*1e-3 );
  m_Muon_quality  .push_back( m_muonSelection->getQuality(*muonSC) );
  m_Muon_dRj      .push_back( dRmin_muon_jet( muonSC->eta(), muonSC->phi()) );
  // Muon ID parameters
  const xAOD::TrackParticle* IDtrack = muonSC->trackParticle( xAOD::Muon::InnerDetectorTrackParticle );
  if(IDtrack){
        m_Muon_id_pt  .push_back(IDtrack->pt()*1e-3);
        m_Muon_id_eta .push_back(IDtrack->eta());
        m_Muon_id_phi .push_back(IDtrack->phi());
        m_Muon_id_theta .push_back(IDtrack->theta());
        m_Muon_id_d0  .push_back(IDtrack->d0());
        m_Muon_id_z0  .push_back(IDtrack->z0());
   } 
  else {
       ANA_MSG_INFO ("Warning: Muon without ID link");
       m_Muon_id_pt  .push_back(-99);
       m_Muon_id_eta .push_back(-99);
       m_Muon_id_phi .push_back(-99);
       m_Muon_id_theta .push_back(-99);
       m_Muon_id_d0  .push_back(-99);
       m_Muon_id_z0  .push_back(-99);  
  } 
} // end for loop over shallow copied muons
  
 
  if(!m_Jet_pt.empty()) m_tree->Fill();  
  clearVector(); 

  return StatusCode::SUCCESS;
}

void TrigxAODAnalysis :: clearVector () {
  m_Jet_roi_pt.clear();
  m_Jet_roi_eta.clear();
  m_Jet_roi_phi.clear();
  m_Jet_roi_thr.clear();
  m_Jet_roi_minthr.clear();
  m_Jet_pt.clear();
  m_Jet_eta.clear();
  m_Jet_phi.clear();
  m_Jet_e.clear();
  m_Jet_us_pt.clear();
  m_Jet_us_eta.clear();
  m_Jet_us_phi.clear();
  m_Jet_us_e.clear();
  m_Jet_sNoiter_pt.clear();
  m_Jet_sNoiter_eta.clear();
  m_Jet_sNoiter_phi.clear();
  m_Jet_sNoiter_e.clear();
  m_Jet_s_pt.clear();
  m_Jet_s_eta.clear();
  m_Jet_s_phi.clear();
  m_Jet_s_e.clear();
  m_Jet_em_pt.clear();
  m_Jet_em_eta.clear();
  m_Jet_em_phi.clear();
  m_Jet_em_e.clear();
  m_Jet_trig_pt.clear();
  m_Jet_trig_eta.clear();
  m_Jet_trig_phi.clear();
  m_Jet_trig_e.clear();
  m_Jet_trig_us_pt.clear();
  m_Jet_trig_us_eta.clear();
  m_Jet_trig_us_phi.clear();
  m_Jet_trig_us_e.clear();
  m_Jet_trig_sNoiter_pt.clear();
  m_Jet_trig_sNoiter_eta.clear();
  m_Jet_trig_sNoiter_phi.clear();
  m_Jet_trig_sNoiter_e.clear();
  m_Jet_trig_s_pt.clear();
  m_Jet_trig_s_eta.clear();
  m_Jet_trig_s_phi.clear();
  m_Jet_trig_s_e.clear();
  m_Jet_trig_em_pt.clear();
  m_Jet_trig_em_eta.clear();
  m_Jet_trig_em_phi.clear();
  m_Jet_trig_em_e.clear();
  m_Jet_dRmu.clear();
  m_Jet_dRTrig.clear();
  m_Jet_dptTrig.clear();
  m_Jet_dptTrigNorm.clear();
  m_Jet_df_pt.clear();
  m_Jet_df_eta.clear();
  m_Jet_df_phi.clear();
  m_Jet_df_e.clear();
  m_Jet_df_dRTrig.clear();
  m_Jet_df_dptTrigNorm.clear();
  m_Jet_df_em_pt.clear();
  m_Jet_df_em_eta.clear();
  m_Jet_df_em_phi.clear();
  m_Jet_df_em_e.clear();
  m_Jet_df_dRmu.clear();
  m_Jet_df_trig_pt.clear();
  m_Jet_df_trig_eta.clear();
  m_Jet_df_trig_phi.clear();
  m_Jet_df_trig_e.clear();
  m_Jet_df02_pt.clear();
  m_Jet_df02_eta.clear();
  m_Jet_df02_phi.clear();
  m_Jet_df02_e.clear();
  m_Jet_df03_pt.clear();
  m_Jet_df03_eta.clear();
  m_Jet_df03_phi.clear();
  m_Jet_df03_e.clear();
  m_Jet_df10_pt.clear();
  m_Jet_df10_eta.clear();
  m_Jet_df10_phi.clear();
  m_Jet_df10_e.clear();
  m_Jet_02_pt.clear();
  m_Jet_02_eta.clear();
  m_Jet_02_phi.clear();
  m_Jet_02_e.clear();
  m_Jet_03_pt.clear();
  m_Jet_03_eta.clear();
  m_Jet_03_phi.clear();
  m_Jet_03_e.clear();
  m_Muon_pt.clear();
  m_Muon_eta.clear();
  m_Muon_phi.clear();
  m_Muon_charge.clear();
  m_Muon_eloss.clear();
  m_Muon_quality.clear();
  m_Muon_e.clear();
  m_Muon_dRj.clear();
  m_Muon_id_pt.clear();
  m_Muon_id_eta.clear();
  m_Muon_id_phi.clear();
  m_Muon_id_theta.clear();
  m_Muon_id_d0.clear();
  m_Muon_id_z0.clear();  
  m_TriggerObject_Chain.clear();
  m_TriggerObject_Ps.clear();
}


double TrigxAODAnalysis::dR(const double eta1,
                          const double phi1,
                          const double eta2,
                          const double phi2)
   {
     double deta = fabs(eta1 - eta2);
     double dphi = fabs(phi1 - phi2) < TMath::Pi() ? fabs(phi1 - phi2) : 2*TMath::Pi() - fabs(phi1 - phi2);
     return sqrt(deta*deta + dphi*dphi);
   }

double TrigxAODAnalysis::dRmin_jet_muon(double eta, double phi){

 double dr_min = 99;
 const xAOD::MuonContainer* muons = 0;
 ANA_CHECK(evtStore()->retrieve( muons, "Muons" ));
 for (auto mu : *muons) {
 double dr = dR(eta, phi, mu->eta(), mu->phi());
  if(dr<dr_min) dr_min = dr;
 }
return dr_min;
}

double TrigxAODAnalysis::dRmin_muon_jet(double eta, double phi){
 
  double dr_min = 99;
  const xAOD::JetContainer* jets = 0;
  ANA_CHECK(evtStore()->retrieve( jets, "AntiKt4HIJets" ));
  for (auto jet : *jets) {
  double dr = dR(eta, phi, jet->eta(), jet->phi());
   if(dr<dr_min) dr_min = dr;
  }
 return dr_min;
 }

double TrigxAODAnalysis::dRmin_jet_trig(double eta, double phi){
 
  double dr_min = 99;
  const xAOD::JetContainer* jets = 0;
  ANA_CHECK(evtStore()->retrieve( jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfFS" ));
  for (auto jet : *jets) {
  double dr = dR(eta, phi, jet->eta(), jet->phi());
   if(dr<dr_min) dr_min = dr;
  }
 return dr_min;
 }

double TrigxAODAnalysis::dpt_jet_trig(double eta, double phi, double pt){

  double dr_min = 99;
  double dpt_min = 99;
  const xAOD::JetContainer* jets = 0;
  ANA_CHECK(evtStore()->retrieve( jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfFS" ));
  for (auto jet : *jets) {
  double dr = dR(eta, phi, jet->eta(), jet->phi());
   if(dr<dr_min){
    dr_min = dr;
    dpt_min = pt*1e-3 - jet->pt()*1e-3;
    }
  }
 return dpt_min;
 }

double TrigxAODAnalysis::dpt_jet_trignorm(double eta, double phi, double pt){

  double dr_min = 99;
  double dpt_min = 99;
  const xAOD::JetContainer* jets = 0;
  ANA_CHECK(evtStore()->retrieve( jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfFS" ));
  for (auto jet : *jets) {
  double dr = dR(eta, phi, jet->eta(), jet->phi());
   if(dr<dr_min){
    dr_min = dr;
    dpt_min = (pt - jet->pt())/pt;
    }
  }
 return dpt_min;
 }

double TrigxAODAnalysis::dRmin_jet_df_trig(double eta, double phi){
 
   double dr_min = 99;
   const xAOD::JetContainer* jets = 0;
   ANA_CHECK(evtStore()->retrieve( jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfvnFS" ));
   for (auto jet : *jets) {
   double dr = dR(eta, phi, jet->eta(), jet->phi());
    if(dr<dr_min) dr_min = dr;
   }
  return dr_min;
  }

 double TrigxAODAnalysis::dpt_jet_df_trignorm(double eta, double phi, double pt){
 
   double dr_min = 99;
   double dpt_min = 99;
   const xAOD::JetContainer* jets = 0;
   ANA_CHECK(evtStore()->retrieve( jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfvnFS" ));
   for (auto jet : *jets) {
   double dr = dR(eta, phi, jet->eta(), jet->phi());
    if(dr<dr_min){
     dr_min = dr;
     dpt_min = (pt - jet->pt())/pt;
     }
   }
  return dpt_min;
  }

/*
bool TrigxAODAnalysis::GetFJR(xAOD::Jet* jet, InDet::InDetTrackSelectionTool *m_track_selection_tool){

    const xAOD::JetFourMom_t jet_4mom = jet->jetP4();
    float jetEta  = jet_4mom.eta();

    const xAOD::Vertex* jetorigin=nullptr;
    bool hasVertex=jet->getAssociatedObject<xAOD::Vertex>("OriginVertex", jetorigin);

    std::vector<const xAOD::TrackParticle*> tracks;
    bool havetracks = jet->getAssociatedObjects("GhostTrack", tracks);
    if ( ! havetracks ) std::cerr << "no tracks found for given jet" << std::endl;
    float sumpt = 0.; //this is the sum pT track variable to cut on for the FJR

    bool isFake = true;
    //Jet is outside the tracker -> no FJR
     if (fabs(jetEta) > 2.5  ) {
        return false;
    }
    for(unsigned int itrack = 0; itrack < tracks.size(); itrack++){
        if (!tracks[itrack]) continue;
        const xAOD::TrackParticle* t = tracks[itrack];
        bool removetrk = false;
        if(hasVertex) {
           if(!m_track_selection_tool->accept(*t,jetorigin)) removetrk = true;
         }
        else {
           if(!m_track_selection_tool->accept(*t)) removetrk = true;
         }
        TLorentzVector p_trk;
        if (t->pt()*1e-3 < 4.) continue; //require the tracks to be greater than 4 GeV
        if (removetrk == true) continue; //only use jets that pass the track selector
        p_trk.SetPtEtaPhiM(t->pt()*1e-3, t->eta(), t->phi(), 0.14); //mass pion in GeV
        sumpt+=(t->pt()*1e-3);
    }
    if (sumpt > 8.) isFake = false;
    return isFake;
}*/

StatusCode TrigxAODAnalysis :: finalize ()
{
  ANA_MSG_INFO ("in finalize");
  return StatusCode::SUCCESS;
}
