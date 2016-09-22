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


  CSCGEMMotherboard(unsigned endcap, unsigned station, unsigned sector,
       unsigned subsector, unsigned chamber,
       const edm::ParameterSet& conf);
  
  //Default constructor for testing
  CSCGEMMotherboard();

  virtual ~CSCGEMMotherboard();

};

#endif
