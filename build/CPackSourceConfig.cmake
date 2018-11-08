# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "")
set(CPACK_BINARY_NSIS "")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "")
set(CPACK_BINARY_ZIP "")
set(CPACK_BUILD_SOURCE_DIRS "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source;/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "Debug;Unspecified")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_GENERATOR "RPM")
set(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_INSTALLED_DIRECTORIES "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_COMMANDS "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/cpack_install.sh")
set(CPACK_INSTALL_PREFIX "usr/UserAnalysis/1.0.0/InstallArea/x86_64-slc6-gcc62-opt")
set(CPACK_INSTALL_SCRIPT "/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/cmake/modules/scripts/cpack_install.cmake")
set(CPACK_MODULE_PATH "/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/cmake/modules;/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBaseExternals/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/cmake/modules")
set(CPACK_NSIS_DISPLAY_NAME "UserAnalysis/1.0.0/InstallArea/x86_64-slc6-gcc62-opt")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "UserAnalysis/1.0.0/InstallArea/x86_64-slc6-gcc62-opt")
set(CPACK_OUTPUT_CONFIG_FILE "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "atlas-sw-core@cern.ch")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/usr")
set(CPACK_PACKAGE_DESCRIPTION "UserAnalysis - 1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/README.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "UserAnalysis - 1.0.0")
set(CPACK_PACKAGE_FILE_NAME "UserAnalysis-1.0.0-Source")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "UserAnalysis/1.0.0/InstallArea/x86_64-slc6-gcc62-opt")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "UserAnalysis/1.0.0/InstallArea/x86_64-slc6-gcc62-opt")
set(CPACK_PACKAGE_NAME "UserAnalysis")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "ATLAS Collaboration")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PROJECT_CONFIG_FILE "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/CPackOptions.cmake")
set(CPACK_RESOURCE_FILE_LICENSE "/cvmfs/atlas.cern.ch/repo/sw/software/21.2/AnalysisBase/21.2.48/InstallArea/x86_64-slc6-gcc62-opt/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/README.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/Cmake/3.11.0/Linux-x86_64/share/cmake-3.11/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_PACKAGE_ARCHITECTURE "noarch")
set(CPACK_RPM_PACKAGE_AUTOREQ " no")
set(CPACK_RPM_PACKAGE_AUTOREQPROV " no")
set(CPACK_RPM_PACKAGE_GROUP "ATLAS Software")
set(CPACK_RPM_PACKAGE_LICENSE "Simplified BSD")
set(CPACK_RPM_PACKAGE_NAME "UserAnalysis_1.0.0_x86_64-slc6-gcc62-opt")
set(CPACK_RPM_PACKAGE_PROVIDES "/bin/sh")
set(CPACK_RPM_PACKAGE_REQUIRES "AnalysisBase_21.2.48_x86_64-slc6-gcc62-opt")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_RPM_PACKAGE_VERSION "1.0.0")
set(CPACK_RPM_SPEC_MORE_DEFINE "%global __os_install_post %{nil}")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "RPM")
set(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/source;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "UserAnalysis-1.0.0-Source")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/afs/cern.ch/user/r/rslovak/analysis/MBTSCrossTalksAnalysis/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()