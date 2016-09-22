#include <L1Trigger/CSCTriggerPrimitives/src/CSCGEMMotherboard.h>

CSCGEMMotherboard::CSCGEMMotherboard(unsigned endcap, unsigned station,
             unsigned sector, unsigned subsector,
             unsigned chamber,
             const edm::ParameterSet& conf) :
    CSCMotherboard(endcap, station, sector, subsector, chamber, conf)
{

}

CSCGEMMotherboard::CSCGEMMotherboard() : CSCMotherboard()
{

}

CSCGEMMotherboard::~CSCGEMMotherboard()
{
}


std::vector<GEMCoPadDigi> CSCGEMMotherboard::readoutCoPads()
{
  return gemCoPadV;
}


