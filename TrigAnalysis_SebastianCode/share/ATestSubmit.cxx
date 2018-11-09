#include <EventLoopAlgs/NTupleSvc.h>
#include <EventLoopAlgs/AlgSelect.h>

void ATestSubmit (const std::string& submitDir)
{
  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;

//  const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/ttbar_signal/group.phys-hi.mc16_valid.410503.PowhegPythia8EvtGen_A14_ttbar_hdamp258p75_dil_r20180318T2154_HI_mc15c_02_EXT1/");
 //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/JetB_tag/run/data/");
  //const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/s/stapiaar/Jetdata/Hion2015/data15_hi.00287931.physics_HardProbes.merge.AOD.r7874_p2580");
  //SH::ScanDir().filePattern("*AOD*").scan(sh,inputFilePath);
  //SH::scanRucio (sh, "data15_hi.00287931.physics_HardProbes.merge.AOD.r7874_p2580");
  //SH::scanRucio (sh, "data15_hi.00287843.physics_EnhancedBias.merge.AOD.r10747_r10754_p3516_tid14861777_00");
  //SH::scanRucio (sh, "data15_hi.00287843.physics_EnhancedBias.merge.AOD.r10840_r10835_p3516_tid15419358_00");
  SH::scanRucio (sh, "data15_hi.00287866.physics_HardProbes.merge.AOD.r10968_p3666_tid15763798_00");
  SH::scanRucio (sh, "data15_hi.00287843.physics_EnhancedBias.merge.AOD.r10971_r10972_p3516_tid15769220_00");

  //SH::scanRucio (sh, "group.phys-hi.mc15_5TeV.420024.PowhegPythia8EvtGen_A14_NNPDF23LO_CT10ME_jetjet_JZ4R04_20180318T2154_01_EXT2/");
  //SH::scanRucio (sh, "group.phys-hi.mc15_5TeV.420023.PowhegPythia8EvtGen_A14_NNPDF23LO_CT10ME_jetjet_JZ3R04_20180318T2154_01_EXT2/");
  //SH::scanRucio (sh, "group.phys-hi.mc15_5TeV.420025.PowhegPythia8EvtGen_A14_NNPDF23LO_CT10ME_jetjet_JZ5R04_20180318T2154_01_EXT2/");
  //SH::scanRucio (sh, "group.phys-hi.mc15_5TeV.420021.PowhegPythia8EvtGen_A14_NNPDF23LO_CT10ME_jetjet_JZ1R04_20180318T2154_01_EXT2/");
  //SH::scanRucio (sh, "group.phys-hi.mc15_5TeV.420022.PowhegPythia8EvtGen_A14_NNPDF23LO_CT10ME_jetjet_JZ2R04_20180318T2154_01_EXT2/");

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
  //EL::DirectDriver driver;
  EL::PrunDriver driver;
  //driver.options()->setString("nc_outputSampleName", "user.stapiaar.mujet_MC_dijet.%in:name[4]%");
 driver.options()->setString("nc_outputSampleName", "user.stapiaar.repro7_try1.%in:name[2]%.%in:name[3]%.%in:name[6]%");
  // we can use other drivers to run things on the Grid, with PROOF, etc.
    // process the job using the driver
 //driver.submit (job, submitDir);
 driver.submitOnly (job, submitDir);

}



