#include <AsgTools/MessageCheck.h>
#include <MyAnalysis/MyxAODAnalysis.h>
#include <xAODEventInfo/EventInfo.h>
#include <xAODJet/JetContainer.h>
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


}



StatusCode MyxAODAnalysis :: initialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  ANA_MSG_INFO ("in initialize");
  // GRL
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

  // print out run and event number from retrieved object
  //  ANA_MSG_INFO ("in execute, runNumber = " << eventInfo->runNumber() << ", eventNumber = " << eventInfo->eventNumber());

  // check if the event is data or MC
  // (many tools are applied either to data or MC)
  bool isMC = false;
  // check if the event is MC
  if (eventInfo->eventType (xAOD::EventInfo::IS_SIMULATION)) {
    isMC = true; // can do something with this later
  }

  // if data check if event passes GRL
  if (!isMC) { // it's data!
    if (!m_grl->passRunLB(*eventInfo)) {
      //      //  ANA_MSG_INFO ("drop event: GRL");
      //return StatusCode::SUCCESS; // go to next event
    }
  } // end if not MC

  //  ANA_MSG_INFO ("keep event: GRL");


  //trigger

  // examine the HLT_xe80* chains, see if they passed/failed and their total prescale
  auto chainGroup = m_trigDecisionTool->getChainGroup("HLT_j100_ion_L1J30");
  std::map<std::string,int> triggerCounts;
  for(auto &trig : chainGroup->getListOfTriggers()) {
    auto cg = m_trigDecisionTool->getChainGroup(trig);
    std::string thisTrig = trig;
    ANA_MSG_INFO ("execute(): " << thisTrig << ", chain passed(1)/failed(0) = " << cg->isPassed() << ", total chain prescale (L1*HLT) = " << cg->getPrescale());
  } 
  // end for loop (C++11 style) over chain group matching "HLT_xe80*" 


  // get jet container of interest
  const xAOD::JetContainer* jets = 0;
  ANA_CHECK(evtStore()->retrieve( jets, "AntiKt4HIJets" ));
  //ANA_MSG_INFO ("execute(): number of jets = " << jets->size());

  // loop over the jets in the container
  for (auto jet : *jets) {
    //ANA_MSG_INFO ("execute(): jet pt = " << (jet->pt() * 0.001) << " GeV"); // just to print out something
  } // end for loop over jets






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
