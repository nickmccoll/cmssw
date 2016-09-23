#ifndef L1Trigger_CSCTriggerPrimitives_CSCGEMMotherboard_h
#define L1Trigger_CSCTriggerPrimitives_CSCGEMMotherboard_h


#include "L1Trigger/CSCTriggerPrimitives/src/CSCMotherboard.h"
#include "L1Trigger/CSCTriggerPrimitives/src/GEMCoPadProcessor.h"
#include "DataFormats/GEMDigi/interface/GEMPadDigiCollection.h"
#include "DataFormats/GEMDigi/interface/GEMCoPadDigiCollection.h"

class CSCGeometry;
class CSCChamber;
class GEMGeometry;
class GEMSuperChamber;

class CSCGEMMotherboard : public CSCMotherboard
{
public:
  typedef std::pair<unsigned int, const GEMPadDigi> GEMPadBX;
  typedef std::vector<GEMPadBX> GEMPadsBX;
  typedef std::map<int, GEMPadsBX> GEMPads;

  typedef std::pair<unsigned int, const GEMCoPadDigi> GEMCoPadBX;
  typedef std::vector<GEMCoPadBX> GEMCoPadsBX;
  typedef std::map<int, GEMCoPadsBX> GEMCoPads;

  /** for the case when more than 2 LCTs/BX are allowed;
      maximum match window = 15 */

  class LCTContainer {
  public:
    LCTContainer (unsigned int match_trig_window_size ) : match_trig_window_size(match_trig_window_size){}
    CSCCorrelatedLCTDigi& operator()(int bx, int match_bx, int lct) { return data[bx][match_bx][lct]; }
    std::vector<CSCCorrelatedLCTDigi> getTimeMatched(const int bx) const;
    CSCCorrelatedLCTDigi data[CSCMotherboard::MAX_LCT_BINS][15][2];
    const unsigned int match_trig_window_size;
  };

  CSCGEMMotherboard(unsigned endcap, unsigned station, unsigned sector,
       unsigned subsector, unsigned chamber,
       const edm::ParameterSet& conf);
  
  //Default constructor for testing
  CSCGEMMotherboard();

  virtual ~CSCGEMMotherboard();


  virtual std::vector<GEMCoPadDigi> readoutCoPads();


protected:

  std::vector<GEMCoPadDigi> gemCoPadV;

  // map< bx , vector<gemid, pad> >
  GEMPads pads_;
  GEMPads coPads_;

};


namespace CSCGEMMotherboardFunctions {

/** Methods to sort the LCTs */
void sortLCTs(std::vector<CSCCorrelatedLCTDigi>& lcts, const unsigned int maxNumLCTS, bool (*sorter)(const CSCCorrelatedLCTDigi&,const CSCCorrelatedLCTDigi&)  );
}

#endif
