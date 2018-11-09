#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoopAlgs/AlgSelect.h>

void ATestRun (const std::string& submitDir)
{
  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;

//  const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/ttbar_signal/group.phys-hi.mc16_valid.410503.PowhegPythia8EvtGen_A14_ttbar_hdamp258p75_dil_r20180318T2154_HI_mc15c_02_EXT1/");
 const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/MuonJet/run/data/");
 //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/pp_5TeV_2017/data17_5TeV.00340718.physics_Main.merge.AOD.f911_m1917/");
 //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/Zx_signal/mc16_5TeV.420012.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ2R04.merge.AOD.e6608_s3238_r10313_r10210/");
// const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/rel21_repro/user.stapiaar.repro.R10trigg-try1_EXT0/");
 //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/rel21_repro/data15_hi.00287843.physics_EnhancedBias.merge.AOD.r10840_r10835_p3516_tid15419358_00/");
//  const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/gammaJet/mc15_5TeV.423103.Pythia8EvtGen_A14NNPDF23LO_gammajet_DP70_140.merge.AOD.e5094_s2860_r7792_r7676");
 //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/rel21_repro/user.stapiaar.repro.ptseed25notracktry1_EXT0");
  SH::ScanDir().filePattern("AOD.TNW*").scan(sh,inputFilePath);

  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  sh.setMetaString ("nc_tree", "CollectionTree");

// further sample handler configuration may go here

// print out the samples we found
   sh.print ();

  // this is the basic description of our job
  EL::Job job;
  job.sampleHandler (sh); // use SampleHandler in this job
  //job.options()->setDouble (EL::Job::optMaxEvents, 500); // for testing purposes, limit to run over the first 500 events only!

    // define an output and an ntuple associated to that output  
  EL::OutputStream output  ("myOutput");
  job.outputAdd (output);
  //EL::NTupleSvc *ntuple = new EL::NTupleSvc ("myOutput");
  //job.algsAdd (ntuple);

  // add our algorithm to the job
  //job.useXAOD ();  

  EL::AnaAlgorithmConfig config;
  //config.setType ("MyxAODAnalysis");
  config.setType ("TrigxAODAnalysis");

  // set the name of the algorithm (this is the name use with
  // messages)
  config.setName ("AnalysisAlg");

  // later on we'll add some configuration options for our algorithm that go here
  
  job.algsAdd (config);

  //config.m_outputName = "myOutput"; // give the name of the output to our algorithm

// make the driver we want to use:
// this one works by running the algorithm directly:
EL::DirectDriver driver;
  // we can use other drivers to run things on the Grid, with PROOF, etc.
    // process the job using the driver
 driver.submit (job, submitDir);

}



