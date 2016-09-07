#include "L1Trigger/CSCTriggerPrimitives/src/GEMCoPadProcessor.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>

//----------------
// Constructors --
//----------------

GEMCoPadProcessor::GEMCoPadProcessor(unsigned endcap,
				     unsigned station,
				     unsigned ring,
				     unsigned chamber,
				     const edm::ParameterSet& conf,
				     const edm::ParameterSet& copad) :
  theEndcap(endcap), theStation(station), theRing(ring),
  theChamber(chamber) {
  
  // if (isSLHC && !smartME1aME1b) edm::LogError("GEMCoPadProcessorConfigError")
  //   << "+++ SLHC upgrade configuration is used (isSLHC=True) but smartME1aME1b=False!\n"
  //   << "Only smartME1aME1b algorithm is so far supported for upgrade! +++\n";

  // Verbosity level, set to 0 (no print) by default.
  infoV        = conf.getParameter<int>("verbosity");

  maxDeltaRoll_ = copad.getParameter<int>("maxDeltaRoll");
  maxDeltaPadGE11_ = copad.getParameter<int>("maxDeltaPadGE11");
  maxDeltaPadGE21_ = copad.getParameter<int>("maxDeltaPadGE21");
  maxDeltaBX_ = copad.getParameter<int>("maxDeltaBX");
}

GEMCoPadProcessor::GEMCoPadProcessor() :
  		     theEndcap(1), theStation(1), theRing(1),
                     theChamber(1) 
{
}

void
GEMCoPadProcessor::clear()
{
  gemCoPadV.clear();
}

std::vector<GEMCoPadDigi>
GEMCoPadProcessor::run(const GEMPadDigiCollection* in_pads) 
{
  const int region((theEndcap == 1) ? 1: -1);
  
  // Build coincidences
  for (auto det_range = in_pads->begin(); det_range != in_pads->end(); ++det_range) {
    const GEMDetId& id = (*det_range).first;
    
    // same chamber (no restriction on the roll number)
    if (id.region() != region or id.station() != theStation or 
	id.ring() != theRing or id.chamber() != theChamber) continue;
    
    // all coincidences detIDs will have layer=1
    if (id.layer() != 1) continue;
    
    // find the corresponding id with layer=2 and same roll number
    GEMDetId co_id(id.region(), id.ring(), id.station(), 2, id.chamber(), id.roll());
    
    auto co_pads_range = in_pads->get(co_id);
    // empty range = no possible coincidence pads
    if (co_pads_range.first == co_pads_range.second) continue;
    
    // now let's correlate the pads in two layers of this partition
    const auto& pads_range = (*det_range).second;
    for (auto p = pads_range.first; p != pads_range.second; ++p) {
      for (auto co_p = co_pads_range.first; co_p != co_pads_range.second; ++co_p) {
	
	const int deltaPad(std::abs(p->pad() - co_p->pad()));
        // check the match in pad
        if ((theStation==1 and deltaPad > maxDeltaPadGE11_) or
	    (theStation==2 and deltaPad > maxDeltaPadGE21_)) continue;

        // check the match in BX
        if (std::abs(p->bx() - co_p->bx()) > maxDeltaBX_) continue;
	
        // make a new coincidence pad digi
        gemCoPadV.push_back(GEMCoPadDigi(id.roll(),*p,*co_p));
      }
    }
  }
  return gemCoPadV;
}

std::vector<GEMCoPadDigi> 
GEMCoPadProcessor::run(const GEMPadDigiClusterCollection* in_clusters)
{
  std::unique_ptr<GEMPadDigiCollection> out_pads(new GEMPadDigiCollection());
  declusterize(in_clusters, *out_pads);
  return run(out_pads.get());
}


std::vector<GEMCoPadDigi>
GEMCoPadProcessor::readoutCoPads()
{
  return gemCoPadV;
}

void
GEMCoPadProcessor::declusterize(const GEMPadDigiClusterCollection* in_clusters,
				GEMPadDigiCollection& out_pads)
{
  GEMPadDigiClusterCollection::DigiRangeIterator detUnitIt;
  for (detUnitIt = in_clusters->begin();detUnitIt != in_clusters->end(); ++detUnitIt) {
    const GEMDetId& id = (*detUnitIt).first;
    const GEMPadDigiClusterCollection::Range& range = (*detUnitIt).second;
    for (GEMPadDigiClusterCollection::const_iterator digiIt = range.first; digiIt!=range.second; ++digiIt) {
      for (auto p: digiIt->pads()){
	out_pads.insertDigi(id, GEMPadDigi(p, digiIt->bx()));
      }
    }
  }
}
