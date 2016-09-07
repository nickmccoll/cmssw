#ifndef L1Trigger_CSCTriggerPrimitives_GEMCoPadProcessor_h
#define L1Trigger_CSCTriggerPrimitives_GEMCoPadProcessor_h

/** \class GEMCoPadProcessor
 *
 * \author Sven Dildick (TAMU)
 *
 */

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/GEMDigi/interface/GEMPadDigiCollection.h"
#include "DataFormats/GEMDigi/interface/GEMPadDigiClusterCollection.h"
#include "DataFormats/GEMDigi/interface/GEMCoPadDigi.h"

#include <vector>

class GEMCoPadProcessor
{
 public:
  /** Normal constructor. */
  GEMCoPadProcessor(unsigned endcap, unsigned station, unsigned ring,
		    unsigned chamber,
		    const edm::ParameterSet& conf,
		    const edm::ParameterSet& comm,
		    const edm::ParameterSet& copad);
  
  /** Default constructor. Used for testing. */
  GEMCoPadProcessor();

  /** Runs the CoPad processor code. Called in normal running -- gets info from
      a collection of pad digis. */
  std::vector<GEMCoPadDigi> run(const GEMPadDigiCollection*);

  /** Runs the CoPad processor code. Called in normal running -- gets info from
      a collection of pad digi clusters. */
  std::vector<GEMCoPadDigi> run(const GEMPadDigiClusterCollection*);

  /** Maximum number of time bins. */
  enum {MAX_CoPad_BINS = 3};

  /** Returns vector of CoPads in the read-out time window, if any. */
  std::vector<GEMCoPadDigi> readoutCoPads();

  /** Returns vector of all found CoPads, if any. */
  std::vector<GEMCoPadDigi> getCoPads();

 private:
  /** Verbosity level: 0: no print (default).
   *                   1: print only CoPads found.
   *                   2: info at every step of the algorithm.
   *                   3: add special-purpose prints. */
  int infoV;

  /** Chamber id (trigger-type labels). */
  const unsigned theEndcap;
  const unsigned theStation;
  const unsigned theRing;
  const unsigned theChamber;

  std::vector<GEMPadDigi> digiV[2];

  // functions to add later
  /*
   * 1. method that declusterizes the clusters (for realistic emulation)
   */
};

#endif
