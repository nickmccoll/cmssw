#ifndef SimMuon_GEMDigitizer_ME0NewGeoDigiProducer_h
#define SimMuon_GEMDigitizer_ME0NewGeoDigiProducer_h

/*
 * This module smears and discretizes the timing and position of the
 * ME0 pseudo digis.
 */

#include "FWCore/Framework/interface/stream/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "DataFormats/GEMDigi/interface/ME0DigiPreRecoCollection.h"
#include "DataFormats/GEMDigi/interface/ME0DigiMap.h"

#include <string>

class ME0Geometry;
class ME0EtaPartition;
class TrapezoidalStripTopology;

namespace CLHEP {
  class HepRandomEngine;
}

class ME0NewGeoDigiProducer : public edm::stream::EDProducer<>
{
private:
	//assume that all ME0 chambers have the same dimension
	//and for the same layer have the same radial and Z position
	//Good for now, can build in support for more varied geos later
	//if necessary
	class TemporaryGeometry {
	public:
		TemporaryGeometry(const ME0Geometry* geometry, const unsigned int numberOfStrips, const unsigned int numberOfPartitions);
		~TemporaryGeometry();
		unsigned int findEtaPartition(float locY) const;
		const TrapezoidalStripTopology * getTopo(const unsigned int partIdx) const {return stripTopos[partIdx];}
		float getPartCenter(const unsigned int partIdx) const; //position of part. in chamber
		float getCentralTOF(const ME0DetId& me0Id, unsigned int partIdx) const {return tofs[me0Id.layer() -1 ][partIdx];} //in detId layer numbers stat at 1
	private:
		TrapezoidalStripTopology * buildTopo(const std::vector<float>& _p) const;
	private:
		float middleDistanceFromBeam;                        // radiusOfMainPartitionInCenter;
		std::vector<TrapezoidalStripTopology * > stripTopos; // vector of Topos, one for each part
		std::vector<std::vector<double> > tofs ;             //TOF to center of the partition:  [layer][part]
		std::vector<float> partionTops;                      //Top of each position in the chamber's local coords

	};
public:

  explicit ME0NewGeoDigiProducer(const edm::ParameterSet& ps);

  virtual ~ME0NewGeoDigiProducer();

  virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;

  virtual void produce(edm::Event&, const edm::EventSetup&) override;


  void buildDigis(const ME0DigiPreRecoCollection &,
                  ME0DigiPreRecoCollection &,
				  ME0DigiPreRecoMap &,
                  CLHEP::HepRandomEngine* engine);

private:
  //paramters
  unsigned int numberOfSrips     ; // number of strips per partition
  unsigned int numberOfPartitions; // number of partitions per chamber
  double       neutronAcceptance ; // fraction of neutron events to keep in event (>= 1 means no filtering)
  double       timeResolution    ; // smear time by gaussian with this sigma (in ns)....negative for no smearing
  int          minBXReadout      ; // Minimum BX to readout
  int          maxBXReadout      ; // Maximum BX to readout
  bool         mergeDigis        ; // Keep only one digi at the same chamber, strip, partition, and BX

  edm::EDGetTokenT<ME0DigiPreRecoCollection> token;
  const ME0Geometry* geometry;
  TemporaryGeometry* tempGeo;
};

#endif

