//#include <boost/shared_ptr.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>



void ATestRun_eljob (const std::string& submitDir)
{


  
  /*
  std::string input_file;
  std::string output_file;
  std::string input_directory;
  std::string submitDir;
  std::string reco_jet_collection;
  std::string trigger_jet_collection;
  


  //Boost configuration                                                                                                                                                        
  //1) command line only: options can only be given on command line, not in config file                                                                                         
  boost::program_options::options_description cmd_only_options("command line only options");
  std::string config_file_name;

  cmd_only_options.add_options() //note unusual syntax when adding options!                                                                                                     
    ("help,h","produce help message")
    ("config,c",boost::program_options::value<std::string>(&config_file_name),"name of configuration file");

  //2) main options: most likely to be set by user, can be specified both via command line or config                                                                            
  //explaination is included in help message                                                                                                                                    
  boost::program_options::options_description main_options("main options");

  main_options.add_options()
    ("input_file",boost::program_options::value<std::string>(&input_file)->default_value(""),"name of input file for testing")
    ("input_directory",boost::program_options::value<std::string>(&input_directory)->default_value("/afs/cern.ch/work/m/mrybar/xAOD/"),"name of input directory containing all\
 files")
    ("submit_directory",boost::program_options::value<std::string>(&submitDir)->default_value("submitDir"),"name of output directory")
    ("output_file",boost::program_options::value<std::string>(&output_file)->default_value("out.root"),"name of output root file")
    ("reco_jet_collection",boost::program_options::value<std::string>(&reco_jet_collection)->default_value("antikt4HIItrEM"),"Reco jet collection")
    ("trigger_jet_collection",boost::program_options::value<std::string>(&trigger_jet_collection)->default_value("a4ionemsubjesFS"),"Trigger jet collection")
    


    //combine options types for parsing                                                                                                                                           
    //all options may be specified on command line                                                                                                                                
    boost::program_options::options_description cmdline_options;
  cmdline_options.add(cmd_only_options).add(main_options);

  //all options except command line only may be specified in config file                                                                                                        
  boost::program_options::options_description config_options;
  config_options.add(main_options);

  boost::program_options::variables_map vm;
  //first parse command line                                                                                                                                                    
  try
    {
      boost::program_options::store(boost::program_options::parse_command_line(argc, argv, cmdline_options), vm);
      boost::program_options::notify(vm);
    }
  catch(std::exception& e)
    {
      std::cerr << "Bad command line argument" << std::endl;
      std::cerr << e.what() << std::endl;
      return 1;
    }

  //if config was specified, also parse config file                                                                                                                             
  if(vm.count("config"))
    {
      ifstream config_stream(config_file_name.c_str());
    try
      {
	boost::program_options::store(boost::program_options::parse_config_file(config_stream,cmdline_options), vm);
	boost::program_options::notify(vm);
      }
    catch(std::exception& e)
      {
	std::cerr << "Bad config file argument" << std::endl;
	std::cerr << e.what() << std::endl;
	return 1;
      }
    }
  

  cout << "Input file:  " << input_file << endl;
  cout << "Input directory:  " << input_directory << endl;
  cout << "Output file:  " << output_file << endl;
  cout << "Output directory:  " << submitDir << endl;
  cout << "Reco jet collection:  " << reco_jet_collection << endl;
  cout << "Trigger jet collection:  " << trigger_jet_collection << endl;
  */










  // Set up the job for xAOD access:
  xAOD::Init().ignore();

  // create a new sample handler to describe the data files we use
  SH::SampleHandler sh;

  // scan for datasets in the given directory
  // this works if you are on lxplus, otherwise you'd want to copy over files
  // to your local machine and use a local path.  if you do so, make sure
  // that you copy all subdirectories and point this to the directory
  // containing all the files, not the subdirectories.

  // use SampleHandler to scan all of the subdirectories of a directory for particular MC single file:
  //  const char* inputFilePath = gSystem->ExpandPathName ("$ALRB_TutorialData/r9315/");
  //SH::ScanDir().filePattern("AOD.11182705._000001.pool.root.1").scan(sh,inputFilePath);


  const char* inputFilePath = gSystem->ExpandPathName ("/afs/cern.ch/work/r/rslovak/RunTaking2018/eos/express_00365318/");
  SH::ScanDir().filePattern("data18_hi.00365318.express_express.recon.AOD.x580._lb0063._SFO-ALL._0003.1").scan(sh,inputFilePath);



  // set the name of the tree in our files
  // in the xAOD the TTree containing the EDM containers is "CollectionTree"
  sh.setMetaString ("nc_tree", "CollectionTree");

  // further sample handler configuration may go here

  // print out the samples we found
  sh.print ();

  // this is the basic description of our job
  EL::Job job;
  job.sampleHandler (sh); // use SampleHandler in this job
  job.options()->setDouble (EL::Job::optMaxEvents, 500); // for testing purposes, limit to run over the first 500 events only!

  // add our algorithm to the job
  EL::AnaAlgorithmConfig alg;
  alg.setType ("MyxAODAnalysis");

  // set the name of the algorithm (this is the name use with
  // messages)
  alg.setName ("AnalysisAlg");

  // later on we'll add some configuration options for our algorithm that go here

  job.algsAdd (alg);

  // make the driver we want to use:
  // this one works by running the algorithm directly:
  EL::DirectDriver driver;
  // we can use other drivers to run things on the Grid, with PROOF, etc.

  // process the job using the driver
  driver.submit (job, submitDir);
}
