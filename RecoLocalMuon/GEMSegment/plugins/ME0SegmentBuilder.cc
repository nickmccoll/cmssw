#include "RecoLocalMuon/GEMSegment/plugins/ME0SegmentBuilder.h"
#include "DataFormats/MuonDetId/interface/ME0DetId.h"
#include "DataFormats/GEMRecHit/interface/ME0RecHit.h"
#include "Geometry/GEMGeometry/interface/ME0Geometry.h"
#include "Geometry/GEMGeometry/interface/ME0EtaPartition.h"
#include "Geometry/GEMGeometry/interface/ME0Chamber.h"
#include "RecoLocalMuon/GEMSegment/plugins/ME0SegmentAlgorithmBase.h"
#include "RecoLocalMuon/GEMSegment/plugins/ME0SegmentBuilderPluginFactory.h"

#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

ME0SegmentBuilder::ME0SegmentBuilder(const edm::ParameterSet& ps) : geom_(0) {

  // Algo type (indexed)
  int chosenAlgo = ps.getParameter<int>("algo_type") - 1;
  // Find appropriate ParameterSets for each algo type

  std::vector<edm::ParameterSet> algoPSets = ps.getParameter<std::vector<edm::ParameterSet> >("algo_psets");

  edm::ParameterSet segAlgoPSet = algoPSets[chosenAlgo].getParameter<edm::ParameterSet>("algo_pset");
  std::string algoName = algoPSets[chosenAlgo].getParameter<std::string>("algo_name");
  LogDebug("ME0SegmentBuilder")<< "ME0SegmentBuilder algorithm name: " << algoName;

  // Ask factory to build this algorithm, giving it appropriate ParameterSet
  algo = std::unique_ptr<ME0SegmentAlgorithmBase>(ME0SegmentBuilderPluginFactory::get()->create(algoName, segAlgoPSet));
}

ME0SegmentBuilder::~ME0SegmentBuilder() {}

void ME0SegmentBuilder::build(const ME0RecHitCollection* recHits, ME0SegmentCollection& oc) {

  LogDebug("ME0SegmentBuilder")<< "Total number of rechits in this event: " << recHits->size();


  std::map<ME0DetId, bool> foundChambers;
  for(ME0RecHitCollection::const_iterator it = recHits->begin(); it != recHits->end(); it++) {
	  const auto chId = it->me0Id().chamberId();
	  auto chIt = foundChambers.find(chId);
	  if(chIt !=  foundChambers.end()) continue;
	  foundChambers[chId] = true;
      ME0SegmentAlgorithmBase::HitAndPositionContainer hitAndPositions;
      const ME0Chamber* chamber = geom_->chamber(chId);
	  for(ME0RecHitCollection::const_iterator it2 = it; it2 != recHits->end(); it2++) {
		  if(it2->me0Id().chamberId() != chId) continue;

          const auto*  part = geom_->etaPartition(it2->me0Id());
          GlobalPoint glb = part->toGlobal(it2->localPosition());
          LocalPoint nLoc = chamber->toLocal(glb);
          hitAndPositions.emplace_back(&(*it2),nLoc,glb,hitAndPositions.size());
//          std::cout <<it2->me0Id()<< " ("<<it2->localPosition().x() <<" "<< it2->localPosition().y() <<" "<< it2->localPosition().z() <<") ("
//        		  << "("<<glb.x() <<" "<< glb.y() <<" "<<glb.z() <<" "<< glb.perp()<<") ("
//				  << "("<<nLoc.x() <<" "<< nLoc.y() <<" "<<nLoc.z() <<")"<<std::endl;
	  }

      LogDebug("ME0Segment|ME0") << "found " << hitAndPositions.size() << " rechits in chamber " << *chIt;
      //sort by layer
        auto getLayer =[&](int iL) ->const ME0Layer* { //function is broken in the geo currently
      	  for (auto layer : chamber->layers()){
      		  if (layer->id().layer()==iL)
      			  return layer;
      	  }
      	  return 0;
        };
        float z1 = getLayer(1)->position().z();
        float z6 = getLayer(6)->position().z();
        if(z1 < z6)
        	std::sort(hitAndPositions.begin(), hitAndPositions.end(), [](const ME0SegmentAlgorithmBase::HitAndPosition& h1,const ME0SegmentAlgorithmBase::HitAndPosition& h2 ) {return h1.layer < h2.layer;});
        else
        	std::sort(hitAndPositions.begin(), hitAndPositions.end(), [](const ME0SegmentAlgorithmBase::HitAndPosition& h1,const ME0SegmentAlgorithmBase::HitAndPosition& h2 ) {return h1.layer < h2.layer;} );



      //      std::sort(hitAndPositions.begin(), hitAndPositions.end(), [](const hitAndPosition& h1,const hitAndPosition& h2 ) )
      // given the chamber select the appropriate algo... and run it
      std::vector<ME0Segment> segv = algo->run(chamber, hitAndPositions);

      LogDebug("ME0Segment|ME0") << "found " << segv.size() << " segments in chamber " << *chIt;

      // Add the segments to master collection
      if(segv.size())
      oc.put(chId, segv.begin(), segv.end());

  }


//  for(ME0RecHitCollection::const_iterator it2 = recHits->begin(); it2 != recHits->end(); it2++) {
//	  std:: cout <<"!!"<< (*it2).me0Id() <<" "<< (*it2).me0Id().chamberId() <<" "<< (*it2).me0Id().chamberId().rawId() << std::endl;
//      bool insert = true;
//      for(chIt=chambers.begin(); chIt != chambers.end(); ++chIt)
//          if ((*it2).me0Id().chamberId() == (*chIt)) insert = false;
//      if (insert){
//          chambers.push_back((*it2).me0Id().chamberId());
//          std:: cout <<"YEP"<< std::endl;
//      }
//  }
//
//
//  for(chIt=chambers.begin(); chIt != chambers.end(); ++chIt) {
//      const ME0Chamber* chamber = geom_->chamber(*chIt);
//      ME0RecHitCollection::range range = recHits->get(std::make_pair(*chIt, ME0DetIdSameChamberComparator()));
//      std::vector<const ME0RecHit*> me0RecHits;
//      //Do coordinate transformations once, store global position and local position in
//      //chamber ref frame for each rechit
//      ME0SegmentAlgorithmBase::HitAndPositionContainer hitAndPositions;
//      hitAndPositions.reserve(range.second - range.first);
//      std::cout << "TRY "<<ME0DetId(*chIt)<<" "<<ME0DetId(*chIt).chamberId()<<std::endl;
//
//
//      for(ME0RecHitCollection::const_iterator rechit = range.first; rechit != range.second; rechit++) {
//          const auto*  part = geom_->etaPartition(rechit->me0Id());
//          GlobalPoint glb = part->toGlobal(rechit->localPosition());
//          LocalPoint nLoc = chamber->toLocal(glb);
//          hitAndPositions.emplace_back(&(*rechit),nLoc,glb,hitAndPositions.size());
//          std::cout <<rechit->me0Id()<< " ("<<rechit->localPosition().x() <<" "<< rechit->localPosition().y() <<" "<< rechit->localPosition().z() <<") ("
//        		  << "("<<glb.x() <<" "<< glb.y() <<" "<<glb.z() <<" "<< glb.perp()<<") ("
//				  << "("<<nLoc.x() <<" "<< nLoc.y() <<" "<<nLoc.z() <<")"<<std::endl;
//      }
//
//      LogDebug("ME0Segment|ME0") << "found " << me0RecHits.size() << " rechits in chamber " << *chIt;
//
//      // given the chamber select the appropriate algo... and run it
//      std::vector<ME0Segment> segv = algo->run(chamber, hitAndPositions);
//
//      LogDebug("ME0Segment|ME0") << "found " << segv.size() << " segments in chamber " << *chIt;
//
//      // Add the segments to master collection
//      oc.put((*chIt), segv.begin(), segv.end());
//  }
}

void ME0SegmentBuilder::setGeometry(const ME0Geometry* geom) {
  geom_ = geom;
}

