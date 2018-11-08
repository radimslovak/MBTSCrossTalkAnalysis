set -e
tmpdir=`mktemp -d makeMyAnalysisDictReflexDict.XXXXXX`
cd ${tmpdir}
/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/bin/genreflex /afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis/MyAnalysis/MyAnalysisDict.h -o MyAnalysisDictReflexDict.cxx --noIncludePaths --rootmap=MyAnalysisDict.dsomap --rootmap-lib=libMyAnalysisDict.so --library=libMyAnalysisDict.so --select="/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis/MyAnalysis/selection.xml" -I"/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include" -I"/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis/MyAnalysis" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/RootCore/include" -I"/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis" -I"/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source/MyAnalysis" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/AnaAlgorithm" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthToolSupport/AsgTools" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/xAODRootAccessInterfaces" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/xAODRootAccess" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthContainers" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthContainersInterfaces" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/AthLinksSA" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Control/CxxUtils" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODCore" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODEventFormat" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/RootCoreUtils" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODEventInfo" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODJet" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODBase" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODBTagging" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODTracking" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/DetectorDescription/GeoPrimitives" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/EventPrimitives" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODMuon" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODCaloEvent" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include/eigen3" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Calorimeter/CaloGeoHelpers" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODPrimitives" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/MuonSpectrometer/MuonIdHelpers" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODPFlow" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Event/xAOD/xAODTrigger" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/Interfaces/AsgAnalysisInterfaces" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/AnalysisCommon/PATInterfaces" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigAnalysis/TrigDecisionTool" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigConfiguration/TrigConfInterfaces" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigEvent/TrigDecisionInterface" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigConfiguration/TrigConfHLTData" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigConfiguration/TrigConfL1Data" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigEvent/TrigNavStructure" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigEvent/TrigRoiConversion" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/Trigger/TrigEvent/TrigSteeringEvent" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/DetectorDescription/RoiDescriptor" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/DetectorDescription/IRegionSelector" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/EventLoopGrid" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/EventLoop" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -I"/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/src/PhysicsAnalysis/D3PDTools/SampleHandler" -I"/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBase/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/../../../../AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt/include" -DHAVE_PRETTY_FUNCTION -DHAVE_64_BITS -D__IDENTIFIER_64BIT__ -DATLAS -DROOTCORE -DXAOD_STANDALONE -DXAOD_ANALYSIS -DROOTCORE_RELEASE_SERIES=25 -DPACKAGE_VERSION=\"MyAnalysis-00-00-00\" -DPACKAGE_VERSION_UQ=MyAnalysis-00-00-00 -DEIGEN_DONT_VECTORIZE -DUSE_CMAKE -DUSE_CMAKE
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake -E copy MyAnalysisDictReflexDict.cxx "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/MyAnalysis/CMakeFiles/MyAnalysisDictReflexDict.cxx"
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake -E copy MyAnalysisDict.dsomap "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/MyAnalysis/CMakeFiles/MyAnalysisDict.dsomap"
/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/bin/cmake -E copy libMyAnalysisDict_rdict.pcm "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/x86_64-slc6-gcc62-opt/lib/libMyAnalysisDict_rdict.pcm"