#include <TMath.h>
#include "MyAnalysis/Utils.h"


namespace Utils {

  double dR(double eta1, double phi1, double eta2, double phi2) {
    double smaller = std::min(phi1,phi2);
    double bigger  = std::max(phi1,phi2);
    double diff = bigger - smaller;
    
    if ( diff < TMath::Pi()) return diff;
    diff = TMath::TwoPi() - diff;
    return TMath::Hypot( eta2 - eta1, diff);
  }




  int GetCentralitylBin(Int_t centralityScheme, float FCal_Et)
  // @brief: returns a global bin [0-9] based on centralityScheme, MTGlobalEvent, and MTEvent (e.g. position of leading jet wrt RP)
  {
    Float_t centrality;
    if (centralityScheme==1)
      return 0;
    
    else if(centralityScheme == 2)  {
      centrality = FCal_Et;
      // 2011, 98%, for fragmentation functions analysis  
      if ((centrality >= 0.6624) && (centrality <= 10.0000) ) return 0; //0-40%
      if ((centrality >= 0.0146) && (centrality < 0.6624)) return 1;  //40-90%  zatim pro nova data   
      return -1;
    }   
         
    else if (centralityScheme == 3)  {
        
      centrality = FCal_Et;
      //TODO fix cent labels in comments
      if  (2.38 <= centrality) return 0; //0-10%
      if ( 1.22 <= centrality) return 1; //10-20%
      if ( 0.56 <= centrality) return 2; //20-30
      if ( 0.22 <= centrality) return 3; //30-40%
      if ( 0.02 <= centrality) return 4; //40-50%
      if (0.02 > centrality)   return 5; //60-80%
        
      return -1;
              
    }
    else { 
      centrality = 0; 
      return -1;
    }
  }
  
  int GetCentralityNBins(Int_t centralityScheme)  {
    
    if (centralityScheme==1) return 1;
    if (centralityScheme==2) return 2;
    if (centralityScheme==3) return 6;
    if (centralityScheme==7) return 7;
    
    else return 1;
  }

}
