#ifndef TrigAnalysis_TrigxAODAnalysis_H
#define TrigAnalysis_TrigxAODAnalysis_H

#include <AnaAlgorithm/AnaAlgorithm.h>
// GRL
#include <AsgAnalysisInterfaces/IGoodRunsListSelectionTool.h>
#include <AsgTools/AnaToolHandle.h>
#include <TrigConfInterfaces/ITrigConfigTool.h>
#include <TrigDecisionTool/TrigDecisionTool.h>
#include <MuonAnalysisInterfaces/IMuonSelectionTool.h>
#include <MuonAnalysisInterfaces/IMuonCalibrationAndSmearingTool.h>
#include "InDetTrackSelectionTool/InDetTrackSelectionTool.h"
#include <xAODJet/JetContainer.h>
// Others
#include <TTree.h>

class TrigxAODAnalysis : public EL::AnaAlgorithm
{
public:
  // this is a standard algorithm constructor
  TrigxAODAnalysis (const std::string& name, ISvcLocator* pSvcLocator);
  
  // these are the functions inherited from Algorithm
  virtual StatusCode initialize () override;
  virtual StatusCode execute () override;
  virtual StatusCode finalize () override;

  void  clearVector();
  double dR(const double eta1,
            const double phi1,
            const double eta2,
            const double phi2);
  double dRmin_jet_muon(double eta, double phi);
  double Trig_mindEta_ion(double eta);
  double Trig_mindPhi_ion(double phi);
  double dRmin_muon_jet(double eta, double phi);
  double Trig_mindEta_tc(double eta);
  double Trig_mindPhi_tc(double phi);
  double dRmin_jet_trig(double eta, double phi);
  double dpt_jet_trig(double eta, double phi, double pt);
  double dpt_jet_trignorm(double eta, double phi, double pt);
  double dRmin_jet_df_trig(double eta, double phi);
  double dpt_jet_df_trignorm(double eta, double phi, double pt);
  //bool GetFJR(xAOD::Jet* jet, InDet::InDetTrackSelectionTool *m_track_selection_tool);
  
private:
 
 
  asg::AnaToolHandle<IGoodRunsListSelectionTool> m_grl; //!
  asg::AnaToolHandle<Trig::TrigDecisionTool> m_trigDecisionTool; //!
  asg::AnaToolHandle<TrigConf::ITrigConfigTool> m_trigConfigTool; //!
  // MuonSelectionTool
  asg::AnaToolHandle<CP::IMuonSelectionTool> m_muonSelection; //!
  // MuonCalibrationAndSmearing
  asg::AnaToolHandle<CP::IMuonCalibrationAndSmearingTool> m_muonCalibrationAndSmearingTool; //!
  asg::AnaToolHandle<InDet::InDetTrackSelectionTool> *m_trkSelection; //!


  std::string m_outputName;
  TTree *m_tree; //!
  int m_EventNumber; //!
  int m_RunNumber; //!
  int m_LumiBlock; //!
  double m_FCal_Et; //!

  std::vector<std::string> m_TriggerObject_Chain; //!
  std::vector<float>   m_TriggerObject_Ps; //!
  bool m_HLT_noalg_eb_L1TE50; //!
  bool m_HLT_noalg_eb_L1ZDC_A_C_VTE50; //!
  bool m_HLT_noalg_eb_L1MBTS_1_1; //!
  bool m_HLT_noalg_mb_L1TE5; //!
  bool m_HLT_noalg_mb_L1TE20; //!
  bool m_HLT_noalg_mb_L1TE50; //!
  bool m_L1_TE4; //!
  bool m_L1_TE5; //!
  bool m_L1_TE20; //!
  bool m_L1_TE50; //!
  bool HLT_noalg_L1J15; //!
  bool HLT_noalg_L1J20; //!
  bool HLT_noalg_L1J30; //!
  bool HLT_noalg_L1J50; //!
  bool m_L1_J15; //!
  bool m_L1_J20; //!
  bool m_L1_J30; //!
  bool m_L1_J50; //!
  bool m_L1_J75; //!
  bool m_HLT_mu4_j40; //!
  bool m_HLT_mu4_j50; //!
  bool m_HLT_mu4_j60; //!
  bool m_HLT_j40_ion_L1TE20; //!
  bool m_HLT_j50_ion_L1TE20; //!
  bool m_HLT_j40_ion_L1TE50; //!
  bool m_HLT_j50_ion_L1TE50; //!
  bool m_HLT_j60_ion_L1TE50; //!
  bool m_HLT_j75_ion_L1TE50; //!
  bool m_HLT_j100_ion_L1TE50; //!
  bool m_HLT_j150_ion_L1TE50; //!
  bool m_HLT_j75_ion_L1J20; //!
  bool m_HLT_j100_ion_L1J20; //!
  bool m_HLT_j150_ion_L1J20; //!
  
  std::vector<double> m_Jet_roi_pt; //!
  std::vector<double> m_Jet_roi_eta; //!
  std::vector<double> m_Jet_roi_phi; //!
  std::vector<std::vector<float>> m_Jet_roi_thr; //!
  std::vector<double> m_Jet_roi_minthr; //!
  std::vector<double> m_Jet_02_pt; //!
  std::vector<double> m_Jet_02_eta; //!
  std::vector<double> m_Jet_02_phi; //!
  std::vector<double> m_Jet_02_e; //!
  std::vector<double> m_Jet_03_pt; //!
  std::vector<double> m_Jet_03_eta; //!
  std::vector<double> m_Jet_03_phi; //!
  std::vector<double> m_Jet_03_e; //!
  std::vector<double> m_Jet_pt; //!
  std::vector<double> m_Jet_eta; //!
  std::vector<double> m_Jet_phi; //!
  std::vector<double> m_Jet_e; //!
  std::vector<double> m_Jet_em_pt; //!
  std::vector<double> m_Jet_em_eta; //!
  std::vector<double> m_Jet_em_phi; //!
  std::vector<double> m_Jet_em_e; //!
  std::vector<double> m_Jet_trig_pt; //!
  std::vector<double> m_Jet_trig_eta; //!
  std::vector<double> m_Jet_trig_phi; //!
  std::vector<double> m_Jet_trig_e; //!
  std::vector<double> m_Jet_df_trig_pt; //!
  std::vector<double> m_Jet_df_trig_eta; //!
  std::vector<double> m_Jet_df_trig_phi; //!
  std::vector<double> m_Jet_df_trig_e; //!
  std::vector<double> m_Jet_us_pt; //!
  std::vector<double> m_Jet_us_eta; //!
  std::vector<double> m_Jet_us_phi; //!
  std::vector<double> m_Jet_us_e; //!
  std::vector<double> m_Jet_sNoiter_pt; //!
  std::vector<double> m_Jet_sNoiter_eta; //!
  std::vector<double> m_Jet_sNoiter_phi; //!
  std::vector<double> m_Jet_sNoiter_e; //!
  std::vector<double> m_Jet_s_pt; //!
  std::vector<double> m_Jet_s_eta; //!
  std::vector<double> m_Jet_s_phi; //!
  std::vector<double> m_Jet_s_e; //!
  std::vector<double> m_Jet_trig_us_pt; //!
  std::vector<double> m_Jet_trig_us_eta; //!
  std::vector<double> m_Jet_trig_us_phi; //!
  std::vector<double> m_Jet_trig_us_e; //!
  std::vector<double> m_Jet_trig_sNoiter_pt; //!
  std::vector<double> m_Jet_trig_sNoiter_eta; //!
  std::vector<double> m_Jet_trig_sNoiter_phi; //!
  std::vector<double> m_Jet_trig_sNoiter_e; //!
  std::vector<double> m_Jet_trig_s_pt; //!
  std::vector<double> m_Jet_trig_s_eta; //!
  std::vector<double> m_Jet_trig_s_phi; //!
  std::vector<double> m_Jet_trig_s_e; //!
  std::vector<double> m_Jet_trig_em_pt; //!
  std::vector<double> m_Jet_trig_em_eta; //!
  std::vector<double> m_Jet_trig_em_phi; //!
  std::vector<double> m_Jet_trig_em_e; //!
  std::vector<double> m_Jet_dRmu; //!
  std::vector<double> m_Jet_dRTrig; //!
  std::vector<double> m_Jet_dptTrig; //!
  std::vector<double> m_Jet_dptTrigNorm; //!
  std::vector<double> m_Jet_df_dRmu; //!
  std::vector<double> m_Jet_df_dRTrig; //!
  std::vector<double> m_Jet_df_dptTrigNorm; //!
  std::vector<double> m_Jet_df_pt; //!
  std::vector<double> m_Jet_df_eta; //!
  std::vector<double> m_Jet_df_phi; //!
  std::vector<double> m_Jet_df_e; //!
  std::vector<double> m_Jet_df02_pt; //!
  std::vector<double> m_Jet_df02_eta; //!
  std::vector<double> m_Jet_df02_phi; //!
  std::vector<double> m_Jet_df02_e; //!
  std::vector<double> m_Jet_df03_pt; //!
  std::vector<double> m_Jet_df03_eta; //!
  std::vector<double> m_Jet_df03_phi; //!
  std::vector<double> m_Jet_df03_e; //!
  std::vector<double> m_Jet_df10_pt; //!
  std::vector<double> m_Jet_df10_eta; //!
  std::vector<double> m_Jet_df10_phi; //!
  std::vector<double> m_Jet_df10_e; //!
  std::vector<double> m_Jet_df_em_pt; //!
  std::vector<double> m_Jet_df_em_eta; //!
  std::vector<double> m_Jet_df_em_phi; //!
  std::vector<double> m_Jet_df_em_e; //!
  std::vector<double> m_Muon_pt; //!
  std::vector<double> m_Muon_eta; //!
  std::vector<double> m_Muon_phi; //!
  std::vector<int>    m_Muon_charge; //!
  std::vector<double> m_Muon_eloss; //!
  std::vector<double> m_Muon_e; //!
  std::vector<double> m_Muon_quality; //!
  std::vector<double> m_Muon_dRj; //!
  std::vector<double> m_Muon_id_pt; //!
  std::vector<double> m_Muon_id_eta; //!
  std::vector<double> m_Muon_id_phi; //!
  std::vector<double> m_Muon_id_theta; //!
  std::vector<double> m_Muon_id_d0; //!
  std::vector<double> m_Muon_id_z0; //!

  // Configuration, and any other types of variables go here.
  //float m_cutValue;
  //TTree *m_myTree;
  //TH1 *m_myHist;
  };
  
 #endif
