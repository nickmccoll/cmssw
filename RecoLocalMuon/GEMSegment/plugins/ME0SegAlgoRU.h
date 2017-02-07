#ifndef ME0Segment_ME0SegAlgoRU_h
#define ME0Segment_ME0SegAlgoRU_h

/**
 * \class ME0SegAlgoRU
 * adapted from CSC to ME0 bt Marcello Maggi
 *
 * This is the original algorithm for building endcap muon track segments
 * out of the rechit's in a ME0Chamber
 * 'RU' = 'RUssia' = Road Usage
 *
 * A ME0Segment is a RecSegment4D, and is built from
 * ME0RecHit2D objects, each of which is a RecHit2DLocalPos. <BR>
 *
 * This class is used by the ME0SegmentAlgorithm. <BR>
 * Alternative algorithms can be used for the segment building
 * by writing classes like this, and then selecting which one is actually
 * used via the ME0SegmentBuilder. <BR>
 *
 * developed and implemented by Vladimir Palichik <Vladimir.Paltchik@cern.ch>
 *                          and Nikolay Voytishin <nikolay.voytishin@cern.ch>
 */

#include <RecoLocalMuon/GEMSegment/plugins/ME0SegmentAlgorithmBase.h>
#include <DataFormats/GEMRecHit/interface/ME0RecHit.h>
#include "MuonSegFit.h"


#include <vector>

class MuonSegFit;



class ME0SegAlgoRU : public ME0SegmentAlgorithmBase {

public:
	struct SegmentParameters {
		float maxETASeeds       ;
		float maxPhiSeeds       ;
		float maxPhiAdditional  ;
		float maxChi2Additional ;
		float maxChi2Prune      ;
		float maxChi2GoodSeg    ;
		float maxTOFDiff        ;
		unsigned int minNumberOfHits;
		bool  requireBeamConstr  ;

	};

    // We need to be able to flag a hit as 'used' and so need a container of bool's. 
    typedef std::vector<bool> BoolContainer;
	typedef std::vector<std::pair<float,HitAndPositionPtrContainer> > SegmentByMetricContainer;
    
    /// Constructor
    explicit ME0SegAlgoRU(const edm::ParameterSet& ps);
    /// Destructor
    virtual ~ME0SegAlgoRU() {};

    /**
     * Here we must implement the algorithm
     */
    std::vector<ME0Segment> run(const ME0Chamber * chamber, const HitAndPositionContainer& rechits);

private:

    //Look for segments that have at least "n_seg_min" consituents and following the associated paramters
    void lookForSegments(const SegmentParameters& params, const unsigned int n_seg_min, const HitAndPositionContainer& rechits, const std::vector<unsigned int>& recHits_per_layer, BoolContainer& used, std::vector<ME0Segment>& segments) const;
    //Look for any hits between the two seed hits consistent with a segment
    void tryAddingHitsToSegment( const float maxTOF,const float maxETA,  const float maxPhi, const float maxChi2, std::unique_ptr<MuonSegFit>& current_fit, HitAndPositionPtrContainer& proto_segment,
    					  const BoolContainer& used, HitAndPositionContainer::const_iterator i1, HitAndPositionContainer::const_iterator i2) const;
    //Remove extra hits until the segment passes "maxChi2"
    void pruneBadHits(const float maxChi2, HitAndPositionPtrContainer& proto_segment,  std::unique_ptr<MuonSegFit>& fit, const unsigned int n_seg_min) const;
    //Remove any overlapping segments by which has the lowset chi2
    void addUniqueSegments(SegmentByMetricContainer& proto_segments, std::vector<ME0Segment>& segments, BoolContainer& used) const;

    //Are the two seed hits consistent spatially?
    bool areHitsCloseInEta(const float maxETA, const bool beamConst,  const GlobalPoint& h1, const GlobalPoint& h2) const;
    bool areHitsCloseInGlobalPhi(const float maxPHI, const unsigned int nLayDisp, const GlobalPoint& h1, const GlobalPoint& h2) const;

    //Add a hit to a segment
    std::unique_ptr<MuonSegFit> addHit(HitAndPositionPtrContainer& proto_segment, const HitAndPosition& aHit) const;
    //Does the segment have any hits on this layer?
    bool hasHitOnLayer(const HitAndPositionPtrContainer& proto_segment, const unsigned int layer) const;
    //Remove any hits on the segment in this hits layer and add that one to the proto segment
    std::unique_ptr<MuonSegFit>  replaceHit(HitAndPositionPtrContainer& proto_segment, const HitAndPosition& aHit) const;
    //Produce a new fit
    std::unique_ptr<MuonSegFit> makeFit(const HitAndPositionPtrContainer& proto_segment) const;

    //Is this hit consistent in time with the other hits?
    bool areHitsConsistentInTime(const float maxTOF, const HitAndPositionPtrContainer& proto_segment, const HitAndPosition& h)  const;
    //Is this new hit btw the seeds near the segment fit?
    bool isHitNearSegment(const float maxETA, const float maxPHI, const std::unique_ptr<MuonSegFit>& fit, const HitAndPositionPtrContainer& proto_segment, const HitAndPosition& h)  const;
    //Return a chi2 for a hit and a predicted segment extrapolation
    float getHitSegChi2(const std::unique_ptr<MuonSegFit>& fit, const ME0RecHit& hit) const;
    //Global point of a segment extrapolated to a Z value
    GlobalPoint globalAtZ(const std::unique_ptr<MuonSegFit>& fit, float z) const;

    //Try adding a hit instead of another and return new or old, depending on which has the smallest chi2
    void compareProtoSegment(std::unique_ptr<MuonSegFit>& current_fit, HitAndPositionPtrContainer& current_proto_segment, const HitAndPosition& new_hit) const;
    //Try adding this hit to the segment, dont if the new chi2 is too big
    void increaseProtoSegment(const float maxChi2,  std::unique_ptr<MuonSegFit>& current_fit, HitAndPositionPtrContainer& current_proto_segment, const HitAndPosition& new_hit) const;


    const std::string myName;
	bool doCollisions;
    bool allowWideSegments;

    SegmentParameters stdParameters;
    SegmentParameters displacedParameters;
    SegmentParameters wideParameters;

    //Objects used to produce the segments
    const ME0Chamber *theChamber;




//    std::vector<ME0Segment> buildSegments();

    // Could be static at the moment, but in principle one
    // might like ME0Segmentizer-specific behaviour?
//    bool areHitsCloseInEta(const ME0RecHit* h1, const ME0RecHit* h2) const;
//    bool areHitsCloseInGlobalPhi(const ME0RecHit* h1, const ME0RecHit* h2) const;
//    bool isHitNearSegment(const ME0RecHit* h) const;

    /**
     * Try adding non-used hits to segment
     */
//    void tryAddingHitsToSegment(const EnsembleHitContainer& rechitsInChamber,
//	const BoolContainer& used, const LayerIndex& layerIndex,
//        const EnsembleHitContainerCIt i1, const EnsembleHitContainerCIt i2);
//


    /**
     * Return true if segment is 'good'.
     * In this algorithm, 'good' means has sufficient hits
     */
//    bool isSegmentGood(const EnsembleHitContainer& rechitsInChamber) const;

    /**
     * Flag hits on segment as used
     */
//    void flagHitsAsUsed(const EnsembleHitContainer& rechitsInChamber, BoolContainer& used) const;
	
    /// Utility functions 	
//    bool addHit(const ME0RecHit* hit, int layer);
//    void updateParameters(void);
//    float fit_r_phi(SVector6 points, int layer) const;
//    float fitX(SVector6 points, SVector6 errors, int ir, int ir2, float &chi2_str) const;
//    void baseline(int n_seg_min);//function for arasing bad hits in case of bad chi2/NDOF
   /**
     * Always enforce direction of segment to point from IP outwards
     * (Incorrect for particles not coming from IP, of course.)
     */
//    float phiAtZ(float z) const;
//    bool hasHitOnLayer(int layer) const;
//    bool replaceHit(const ME0RecHit* h, int layer);
//    void compareProtoSegment(const ME0RecHit* h, int layer);
//    void increaseProtoSegment(const ME0RecHit* h, int layer, int chi2_factor);









//    float windowScale;
//    bool doCollisions;
//    float dRMax ;
//    float dPhiMax;
//    float dRIntMax;
//    float dPhiIntMax;
//    float chi2Max;
//    float chi2_str_;
//    float chi2Norm_2D_;
//    float wideSeg;
};

// functor to sort rechits in the segment
//struct  sortByLayer{
//  sortByLayer(){}
//  bool operator()(const ME0RecHit* a, const ME0RecHit* b) const{
//    int layer1 = a->me0Id().layer();
//    int layer2 = b->me0Id().layer();
//    return  layer1 < layer2;
//  }
//};
#endif
