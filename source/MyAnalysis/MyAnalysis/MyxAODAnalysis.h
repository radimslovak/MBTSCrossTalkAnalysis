#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>

//grl
#include <AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h>
#include <AsgTools/AnaToolHandle.h>

//trigger
#include <TrigConfInterfaces/ITrigConfigTool.h>
#include <TrigDecisionTool/TrigDecisionTool.h>


class MyxAODAnalysis : public EL::AnaAlgorithm
{
 public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

 private:
  //grl
  asg::AnaToolHandle<IGoodRunsListSelectionTool> m_grl;
 
  //trigger
  asg::AnaToolHandle<Trig::TrigDecisionTool> m_trigDecisionTool;
  asg::AnaToolHandle<TrigConf::ITrigConfigTool> m_trigConfigTool;


 
  // Configuration, and any other types of variables go here.
  //float m_cutValue;
  //TTree *m_myTree;
  //TH1 *m_myHist;
};

#endif
