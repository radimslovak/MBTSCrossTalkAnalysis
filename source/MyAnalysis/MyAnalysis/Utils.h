#ifndef Utils_h
#define Utils_h

#include <iostream>

namespace Utils {

  double dR(double eta1, double phi1, double eta2, double phi2);

  int GetCentralityBin(Int_t centralityScheme, float FCal_Et);
  int GetCentralityNBins(Int_t centralityScheme);


}

#endif
