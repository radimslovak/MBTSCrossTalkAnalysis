# Generated by lcg_generate_env...
if [ -z "${LCG_RELEASE_BASE}" ]; then
   export LCG_RELEASE_BASE=/cvmfs/atlas.cern.ch/repo/sw/software/21.2/sw/lcg/releases
fi
export ROOTSYS=/cvmfs/atlas-nightlies.cern.ch/repo/sw/21.2/2018-11-08T0411/AnalysisBaseExternals/21.2.52/InstallArea/x86_64-slc6-gcc62-opt
if [ -z "${PYTHONPATH}" ]; then
   export PYTHONPATH=${ROOTSYS}/lib:/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/python
else
   export PYTHONPATH=${ROOTSYS}/lib:/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/python:${PYTHONPATH}
fi
if [ -z "${PATH}" ]; then
   export PATH=${ROOTSYS}/bin:/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/bin
else
   export PATH=${ROOTSYS}/bin:/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/bin:${PATH}
fi
if [ -z "${LD_LIBRARY_PATH}" ]; then
   export LD_LIBRARY_PATH=${ROOTSYS}/lib:/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/lib
else
   export LD_LIBRARY_PATH=${ROOTSYS}/lib:/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/lib:${LD_LIBRARY_PATH}
fi
if [ -z "${ROOT_INCLUDE_PATH}" ]; then
   export ROOT_INCLUDE_PATH=${ROOTSYS}/include::/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/include
else
   export ROOT_INCLUDE_PATH=${ROOTSYS}/include::/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/include:${ROOT_INCLUDE_PATH}
fi
