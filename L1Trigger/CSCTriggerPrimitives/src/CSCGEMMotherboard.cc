#include <L1Trigger/CSCTriggerPrimitives/src/CSCGEMMotherboard.h>

std::vector<CSCCorrelatedLCTDigi> CSCGEMMotherboard::LCTContainer::getTimeMatched(const int bx) const {
  std::vector<CSCCorrelatedLCTDigi> lcts;
  for (unsigned int mbx = 0; mbx < match_trig_window_size; mbx++)
    for (int i=0;i<2;i++)
      if (data[bx][mbx][i].isValid())
        lcts.push_back(data[bx][mbx][i]);
  return lcts;
}

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

void CSCGEMMotherboardFunctions::sortLCTs(std::vector<CSCCorrelatedLCTDigi>& lcts, const unsigned int maxNumLCTS, bool (*sorter)(const CSCCorrelatedLCTDigi&,const CSCCorrelatedLCTDigi&)  ){
  std::sort(lcts.begin(), lcts.end(), *sorter);
  if (lcts.size() > maxNumLCTS) lcts.erase(lcts.begin()+maxNumLCTS, lcts.end());
}

