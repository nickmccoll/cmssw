#ifndef GEMRecHit_ME0SegmentAlgorithmBase_h
#define GEMRecHit_ME0SegmentAlgorithmBase_h

/** \class ME0SegmentAlgo derived from CSC
 * An abstract base class for algorithmic classes used to
 * build segments in one ensemble of ME0 detector
 *
 * Implementation notes: <BR>
 * For example, ME0SegmAlgoMM inherits from this class,
 *
 * \author Marcello Maggi
 *
 */

#include "DataFormats/GEMRecHit/interface/ME0RecHitCollection.h"
#include "DataFormats/GEMRecHit/interface/ME0Segment.h"
#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "Geometry/GEMGeometry/interface/ME0Chamber.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include <map>
#include <vector>

class ME0SegmentAlgorithmBase {
public:

  /// Typedefs
  typedef std::vector<const ME0RecHit*> EnsembleHitContainer;
  typedef std::vector<EnsembleHitContainer> ProtoSegments;
  typedef std::pair<const ME0Chamber*, std::map<uint32_t, const ME0EtaPartition*> >ME0Ensemble;

    /// Constructor
    explicit ME0SegmentAlgorithmBase(const edm::ParameterSet&) {};
    /// Destructor
    virtual ~ME0SegmentAlgorithmBase() {};

    /** Run the algorithm = build the segments in this chamber
    */
    virtual std::vector<ME0Segment> run(const ME0Ensemble& ensemble, const EnsembleHitContainer& rechits) = 0;

    private:
};
#endif
