// /afs/cern.ch/work/s/stapiaar/public/TrigAnalysis/


#include <AsgTools/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
#include <xAODHIEvent/HIEventShapeContainer.h>
#include <xAODForward/MBTSModuleContainer.h>

#include <TSystem.h>


MyxAODAnalysis :: MyxAODAnalysis (const std::string& name,
                                  ISvcLocator *pSvcLocator)
  : EL::AnaAlgorithm (name, pSvcLocator),
    m_grl ("GoodRunsListSelectionTool/grl", this),
    m_trigDecisionTool ("Trig::TrigDecisionTool/TrigDecisionTool"),
    m_trigConfigTool("TrigConf::xAODConfigTool/xAODConfigTool")




{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  This is also where you
  // declare all properties for your algorithm.  Note that things like
  // resetting statistics variables or booking histograms should
  // rather go into the initialize() function.

  
  
  // declare the tool handle as a property on the algorithm
  m_grl.declarePropertyFor (this, "grlTool");

  m_centralityScheme = 31;   
}



StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  ANA_MSG_INFO ("in initialize");

  m_eventCounter = 0;

  // GRL
  //TODO this GRL is old and it is not used
  const char* GRLFilePath = "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis/data/GRL_PbPb_5p02TeV_2015.xml";
  const char* fullGRLFilePath = gSystem->ExpandPathName (GRLFilePath);
  std::vector<std::string> vecStringGRL;
  vecStringGRL.push_back(fullGRLFilePath);
  ANA_CHECK(m_grl.setProperty( "GoodRunsListVec", vecStringGRL));
  ANA_CHECK(m_grl.setProperty("PassThrough", false)); // if true (default) will ignore result of GRL and will just pass all events
  ANA_CHECK(m_grl.initialize());


  // Initialize and configure trigger tools
  ANA_CHECK (m_trigConfigTool.initialize());
  ANA_CHECK (m_trigDecisionTool.setProperty ("ConfigTool", m_trigConfigTool.getHandle())); // connect the TrigDecisionTool to the ConfigTool
  ANA_CHECK (m_trigDecisionTool.setProperty ("TrigDecisionKey", "xTrigDecision"));
  ANA_CHECK (m_trigDecisionTool.initialize());

  // histo FCal Et
  ANA_CHECK (book (TH1F ("h_FCal", "h_FCal", 100, 0, 5))); // jet pt [GeV]   
 
  //histograms jets
  ANA_CHECK (book (TH1F ("h_jet_Pt", "h_jet_Pt", 100, 0, 500))); // jet pt [GeV]
  ANA_CHECK (book (TH2F ("h2_jet_EtaPhi", "h2_jet_EtaPhi", 100, -5, 5, 64, -TMath::Pi(), TMath::Pi() )));

  for (int cent = 0; cent < getCentralityNBins(m_centralityScheme); ++cent)  {
    ANA_CHECK (book (TH1F (Form("h_jet_Pt_c%i",cent), ";p_{T,jet} [GeV];N", 100, 0, 500))); 


  }
  // mbts histo

  ANA_CHECK (book (TH1F ("h_mbts_energy", "h_mbts_energy", 1000, -500, 500))); 
  ANA_CHECK (book (TH2F ("h2_mbts_EtaPhi", "h2_mbts_EtaPhi", 100, -5, 5, 64, -TMath::Pi(), TMath::Pi() )));
  ANA_CHECK (book (TH1F ("h_mbts_time", "h_mbts_time", 1000, -500, 500)));  

  return StatusCode::SUCCESS;
}



StatusCode MyxAODAnalysis :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.


  // retrieve the eventInfo object from the event store
  const xAOD::EventInfo *eventInfo = nullptr;
  ANA_CHECK (evtStore()->retrieve (eventInfo, "EventInfo"));

  m_eventCounter++;


  // print out run and event number from retrieved object
  //  ANA_MSG_INFO ("in execute, runNumber = " << eventInfo->runNumber() << ", eventNumber = " << eventInfo->eventNumber());

  // check if the event is data or MC
  // (many tools are applied either to data or MC)
  bool isMC = false;
  // check if the event is MC
  if (eventInfo->eventType (xAOD::EventInfo::IS_SIMULATION)) {
    isMC = true; // can do something with this later
  }

  /*
  // if data check if event passes GRL
  if (!isMC) { // it's data!
    if (!m_grl->passRunLB(*eventInfo)) {
      //      //  ANA_MSG_INFO ("drop event: GRL");
      return StatusCode::SUCCESS; // go to next event
    }
  } // end if not MC
  */


  // centrality

  // only to be used for PbPb data                                                                                                                                            
  const xAOD::HIEventShapeContainer *hiue(0);
  ANA_CHECK( evtStore()->retrieve(hiue, "CaloSums"));
  double FCal_Et = hiue->at(5)->et()*1e-6;
  int cent_bin = getCentralityBin(3, FCal_Et); 


  //  ANA_MSG_INFO ("execute(): cent = " <<cent_bin<< "\t FCal = "<<FCal_Et); 

  hist("h_FCal")->Fill(FCal_Et);



  //trigger

  std::vector<std::string> trig_pattern;
  trig_pattern.push_back("HLT_noalg_eb_L1TE50");
  trig_pattern.push_back("HLT_j75_ion_L1TE50");
  trig_pattern.push_back("HLT_j100_ion_L1TE50");

  std::vector<bool> trig_decision;
  std::vector<float> trig_prescales;


  // examine the HLT_xe80* chains, see if they passed/failed and their total prescale
  auto chainGroup = m_trigDecisionTool->getChainGroup( trig_pattern );
  std::map<std::string,int> triggerCounts;
  for(auto &trig : chainGroup->getListOfTriggers()) {
    auto cg = m_trigDecisionTool->getChainGroup(trig);
    std::string thisTrig = trig;
    //    ANA_MSG_INFO ("execute(): " << thisTrig << ", chain passed(1)/failed(0) = " << cg->isPassed() << ", total chain prescale (L1*HLT) = " << cg->getPrescale());

    trig_decision.push_back(cg->isPassed());
    trig_prescales.push_back(cg->getPrescale());


  } 
  // end for loop (C++11 style) over chain group matching "HLT_xe80*" 








  //-----------------------------------------------------------
  // The code to extract information on individual MBTS module
  //-----------------------------------------------------------

  const xAOD::MBTSModuleContainer* mbts = 0;
  ANA_CHECK(evtStore()->retrieve( mbts, "MBTSModules" ));

  int nmbts = 0;
 

  for (auto i_mbts : *mbts) {
    nmbts++;
    int mbts_num =  mod_num( i_mbts->eta(), i_mbts->phi() );
    //    if( i_mbts->type() > 0.0 )
    //Info("info:", "MBTSA%d", mbts_num);
    //else
    //Info("info:", "MBTSC%d", mbts_num);



    hist ( "h_mbts_energy")->Fill(i_mbts->e() );
    hist ( "h_mbts_time")->Fill(i_mbts->time() );
    hist ( "h2_mbts_EtaPhi")->Fill(i_mbts->eta(), i_mbts->phi() );


  }


  /*
  xAOD::MBTSModuleContainer::const_iterator mbts_itr = mbts->begin();
  xAOD::MBTSModuleContainer::const_iterator mbts_end = mbts->end();

  for (; mbts_itr != mbts_end; ++mbts_itr) {
    nmbts++;

    int mbts_num =  mod_num( (*mbts_itr)->eta(), (*mbts_itr)->phi() );

    if( (*mbts_itr)->type() > 0.0 )
      Info("info:", "MBTSA%d", mbts_num);
    else
      Info("info:", "MBTSC%d", mbts_num);

    Info("info:", "mbts eta, phi, energy & time: %f  %f   %f  %f", (*mbts_itr)->eta(), (*mbts_itr)->phi(), (*mbts_itr)->e(), (*mbts_itr)->time() );
  }
  */

  /*
  
  if( ! evtStore()->retrieve( mbts, "MBTSModules" )){
    if( m_eventCounter < 10 )  {
      Error("execute()", "Failed to retrieve MBTSModule container. " );
    }
  } else  {
    if( m_eventCounter < 10 )  {
      Info("execute()", "Retrieved MBTSModules container" );
    }
    int nmbts = 0;
    xAOD::MBTSModuleContainer::const_iterator mbts_itr = mbts->begin();
    xAOD::MBTSModuleContainer::const_iterator mbts_end = mbts->end();
    for (; mbts_itr != mbts_end; ++mbts_itr) {
      nmbts++;

      int mbts_num =  mod_num( (*mbts_itr)->eta(), (*mbts_itr)->phi() );
      if( (*mbts_itr)->type() > 0.0 )
	Info("info:", "MBTSA%d", mbts_num);
      else
	Info("info:", "MBTSC%d", mbts_num);

      Info("info:", "mbts eta, phi, energy & time: %f  %f   %f  %f", (*mbts_itr)->eta(), (*mbts_itr)->phi(), (*mbts_itr)->e(), (*mbts_itr)->time() );

    }
  } 
  */










  // get jet container of interest
  const xAOD::JetContainer* DFjets = 0;
  ANA_CHECK(evtStore()->retrieve( DFjets, "AntiKt4HIJets" ));
  //ANA_MSG_INFO ("execute(): number of jets = " << jets->size());

  // loop over the jets in the container
  for (auto jet : *DFjets) {
    
    hist ("h_jet_Pt")->Fill (jet->pt() * 0.001); // GeV
    hist("h_jet_Pt_c"+std::to_string(cent_bin))->Fill(jet->pt() * 0.001);
        
    if (jet->pt() *0.001 > 30) 
      hist ("h2_jet_EtaPhi")->Fill( jet->eta(), jet->phi());


    const xAOD::JetFourMom_t jet_us_4mom = jet->jetP4("JetUnsubtractedScaleMomentum");
    //  m_Jet_us_pt    .push_back( jet_us_4mom.pt()*1e-3);
    // m_Jet_us_eta   .push_back( jet_us_4mom.eta() );
    //m_Jet_us_phi   .push_back( jet_us_4mom.phi() );
    //m_Jet_us_e     .push_back( jet_us_4mom.e()*1e-3);
    
    const xAOD::JetFourMom_t jet_s_4mom = jet->jetP4("JetSubtractedScaleMomentum");
    //m_Jet_s_pt    .push_back( jet_s_4mom.pt()*1e-3);
    //m_Jet_s_eta   .push_back( jet_s_4mom.eta() );
    //m_Jet_s_phi   .push_back( jet_s_4mom.phi() );
    //m_Jet_s_e     .push_back( jet_s_4mom.e()*1e-3);
    const xAOD::JetFourMom_t jet_em_4mom = jet->jetP4("JetEMScaleMomentum");
    //m_Jet_em_pt    .push_back( jet_em_4mom.pt()*1e-3);
    //m_Jet_em_eta   .push_back( jet_em_4mom.eta() );
    //m_Jet_em_phi   .push_back( jet_em_4mom.phi() );
    //m_Jet_em_e     .push_back( jet_em_4mom.e()*1e-3);
    
  } // end for loop over DF jets    





  // get jet container of interest                                                                                                                                              
  const xAOD::JetContainer* jets = 0;
  ANA_CHECK(evtStore()->retrieve( jets, "AntiKt4HIJets" ));
  //ANA_MSG_INFO ("execute(): number of jets = " << jets->size());                                                                                                              

  // loop over the jets in the container                                                                                                                                        
  for (auto jet : *jets) {

    hist ("h_jet_Pt")->Fill (jet->pt() * 0.001); // GeV                                                                                                                        
    hist("h_jet_Pt_c"+std::to_string(cent_bin))->Fill(jet->pt() * 0.001);



    if (jet->pt() *0.001 > 30)
      hist ("h2_jet_EtaPhi")->Fill( jet->eta(), jet->phi());



    const xAOD::JetFourMom_t jet_us_4mom = jet->jetP4("JetUnsubtractedScaleMomentum");
    //  m_Jet_us_pt    .push_back( jet_us_4mom.pt()*1e-3);                                                                                                                         // m_Jet_us_eta   .push_back( jet_us_4mom.eta() );                                                                                                                             //m_Jet_us_phi   .push_back( jet_us_4mom.phi() );                                                                                                                              //m_Jet_us_e     .push_back( jet_us_4mom.e()*1e-3);                                                                                                                         
    const xAOD::JetFourMom_t jet_s_4mom = jet->jetP4("JetSubtractedScaleMomentum");
    //m_Jet_s_pt    .push_back( jet_s_4mom.pt()*1e-3);                                                                                                                             //m_Jet_s_eta   .push_back( jet_s_4mom.eta() );                                                                                                                                //m_Jet_s_phi   .push_back( jet_s_4mom.phi() );                                                                                                                                //m_Jet_s_e     .push_back( jet_s_4mom.e()*1e-3);                                                                                                                           
    const xAOD::JetFourMom_t jet_em_4mom = jet->jetP4("JetEMScaleMomentum");
    //m_Jet_em_pt    .push_back( jet_em_4mom.pt()*1e-3);                                                                                                                           //m_Jet_em_eta   .push_back( jet_em_4mom.eta() );                                                                                                                              //m_Jet_em_phi   .push_back( jet_em_4mom.phi() );                                                                                                                              //m_Jet_em_e     .push_back( jet_em_4mom.e()*1e-3); 



  }














  const xAOD::JetContainer* trig_jets = 0;
  //ANA_CHECK(evtStore()->retrieve( trig_jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfFS" ));
  ANA_CHECK(evtStore()->retrieve( trig_jets, "HLT_xAOD__JetContainer_a4ionemsubjesFS" ));
  

  for (auto trig_jet : *trig_jets) {

    //m_Jet_trig_pt       .push_back( trig_jet->pt()*1e-3);
    //m_Jet_trig_eta      .push_back( trig_jet->eta() );
    //m_Jet_trig_phi      .push_back( trig_jet->phi() );
    //m_Jet_trig_e        .push_back( trig_jet->e()*1e-3 );

    const xAOD::JetFourMom_t jet_trig_us_4mom = trig_jet->jetP4("JetUnsubtractedScaleMomentum");
    //m_Jet_trig_us_pt    .push_back( jet_trig_us_4mom.pt()*1e-3);
    //m_Jet_trig_us_eta   .push_back( jet_trig_us_4mom.eta() );
    //m_Jet_trig_us_phi   .push_back( jet_trig_us_4mom.phi() );
    //m_Jet_trig_us_e     .push_back( jet_trig_us_4mom.e()*1e-3);
    
    const xAOD::JetFourMom_t jet_trig_s_4mom = trig_jet->jetP4("JetSubtractedScaleMomentum");
    //m_Jet_trig_s_pt    .push_back( jet_trig_s_4mom.pt()*1e-3);
    //m_Jet_trig_s_eta   .push_back( jet_trig_s_4mom.eta() );
    //m_Jet_trig_s_phi   .push_back( jet_trig_s_4mom.phi() );
    //m_Jet_trig_s_e     .push_back( jet_trig_s_4mom.e()*1e-3);
    const xAOD::JetFourMom_t trig_jet_em_4mom = trig_jet->jetP4("JetEMScaleMomentum");
    //m_Jet_trig_em_pt    .push_back( trig_jet_em_4mom.pt()*1e-3);
    //m_Jet_trig_em_eta   .push_back( trig_jet_em_4mom.eta() );
    //m_Jet_trig_em_phi   .push_back( trig_jet_em_4mom.phi() );
    //m_Jet_trig_em_e     .push_back( trig_jet_em_4mom.e()*1e-3);
  }// end jet loop                                     


  const xAOD::JetContainer* trig_df_jets = 0;
  //  ANA_CHECK(evtStore()->retrieve( trig_df_jets, "HLT_xAOD__JetContainer_a4ionemsubjesISdfvnFS" ));
  ANA_CHECK(evtStore()->retrieve( trig_df_jets, "HLT_xAOD__JetContainer_a4ionemsubjesISFS" ));

  for (auto trig_df_jet : *trig_df_jets) {
 
    //m_Jet_df_trig_pt       .push_back( trig_df_jet->pt()*1e-3);
    //m_Jet_df_trig_eta      .push_back( trig_df_jet->eta() );
    //m_Jet_df_trig_phi      .push_back( trig_df_jet->phi() );
    //m_Jet_df_trig_e        .push_back( trig_df_jet->e()*1e-3 );
  }
 









  return StatusCode::SUCCESS;
}



StatusCode MyxAODAnalysis :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.
  return StatusCode::SUCCESS;
}


int MyxAODAnalysis ::mod_num(float eta, float phi) {
  // calculate MBTS number 

  int iphi=0;

  if(phi > 3.14/4.0)  iphi=1;
  if(phi > 2*3.14/4.0)  iphi=2;
  if(phi > 3*3.14/4.0)  iphi=3;
  if(phi > 4*3.14/4.0)  iphi=4;
  if(phi > 5*3.14/4.0)  iphi=5;
  if(phi > 6*3.14/4.0)  iphi=6;
  if(phi > 7*3.14/4.0)  iphi=7;

  if(eta < 3.0)  iphi+=8;

  return iphi; 


}


double MyxAODAnalysis::dR(double eta1, double phi1, double eta2, double phi2) {
  double smaller = std::min(phi1,phi2);
  double bigger  = std::max(phi1,phi2);
  double diff = bigger - smaller;

  if ( diff < TMath::Pi()) return diff;
  diff = TMath::TwoPi() - diff;
  return TMath::Hypot( eta2 - eta1, diff);
}


int MyxAODAnalysis::getCentralityBin(Int_t centralityScheme, float FCal_Et)
// @brief: returns a global bin [0-9] based on centralityScheme, MTGlobalEvent, and MTEvent (e.g. position of leading jet wrt RP)                                             
{
  Float_t centrality = FCal_Et;
  if (centralityScheme==1)
    return 0;

  else if(centralityScheme == 2)  {

    // 2011, 98%, for fragmentation functions analysis                                                                                                                        
    if ((centrality >= 0.6624) && (centrality <= 10.0000) ) return 0; //0-40%                                                                                                 
    if ((centrality >= 0.0146) && (centrality < 0.6624)) return 1;  //40-90%  zatim pro nova data                                                                             
    return -1;
  }
  else if (centralityScheme == 3)  {


    //TODO fix cent labels in comments                                                                                                                                        
    if  (2.38 <= centrality) return 0; //0-10%                                                                                                                                
    if ( 1.22 <= centrality) return 1; //10-20%                                                                                                                               
    if ( 0.56 <= centrality) return 2; //20-30                                                                                                                                
    if ( 0.22 <= centrality) return 3; //30-40%                                                                                                                               
    if ( 0.02 <= centrality) return 4; //40-60%                                                                                                                               
    if (0.02 > centrality)   return 5; //60-80%                                                                                                                               

    return -1;

  }
  else if (centralityScheme == 31) {
  
    if ( 2.98931 <=centrality && centrality< 4.9  ) return 0;           // 0-10%
    if ( 2.04651 <=centrality && centrality< 2.98931  ) return 1;        // 10-20%
    if ( 1.36875 <=centrality && centrality< 2.04651  ) return 2;        // 20-30%
    if ( 0.87541 <=centrality && centrality< 1.36875  ) return 3;        // 30-40%
    if ( 0.525092 <=centrality && centrality< 0.87541  ) return 4;  // 40-50%
    if ( 0.289595 <=centrality && centrality< 0.525092  ) return 5;  // 50-60%
    if ( 0.14414  <=centrality && centrality< 0.289595 ) return 6;                // 60-70%
    if ( 0.063719 <=centrality && centrality< 0.14414 ) return 7;                // 70-80%

    return -1;

  }
  

  else {
    centrality = 0;
    return -1;
  }
}

int MyxAODAnalysis::getCentralityNBins(Int_t centralityScheme)  {

  if (centralityScheme==1) return 1;
  if (centralityScheme==2) return 2;
  if (centralityScheme==3) return 6;
  if (centralityScheme==7) return 7;
  if (centralityScheme==31) return 8;
  
  else return 1;
}

int MyxAODAnalysis::  setCentralityScheme(int centalityScheme) {


  m_centralityScheme = centalityScheme;
  return 0;


  }
