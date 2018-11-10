#ifndef MyAnalysis_MyxAODAnalysis_H
#define MyAnalysis_MyxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>

//grl
#include <AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h>
#include <AsgTools/AnaToolHandle.h>

//trigger
#include <TrigConfInterfaces/ITrigConfigTool.h>
#include <TrigDecisionTool/TrigDecisionTool.h>


//#include "MyAnalysis/Utils.h"

#include "TH1.h"
#include "TH2.h"



class MyxAODAnalysis : public EL::AnaAlgorithm
{
 public:
  // this is a standard algorithm constructor
  MyxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);

  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

  // calculate MBTS number 
  int mod_num(float eta, float phi);

  double dR(double eta1, double phi1, double eta2, double phi2);

  int getCentralityBin(Int_t centralityScheme, float FCal_Et);
  int getCentralityNBins(Int_t centralityScheme);
  int setCentralityScheme(int centalityScheme);


 private:

  int m_eventCounter;
  int m_centralityScheme;

  std::map<std::string, std::pair<int, float>> m_trigInfo;

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
