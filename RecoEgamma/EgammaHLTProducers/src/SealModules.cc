#include "PluginManager/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTEcalIsolationProducers.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTHcalIsolationProducers.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTPhotonTrackIsolationProducers.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTElectronTrackIsolationProducers.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTRecoEcalCandidateProducers.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTPixelMatchElectronProducers.h"
#include "RecoEgamma/EgammaHLTProducers/interface/EgammaHLTRegionalPixelSeedGeneratorProducers.h"

DEFINE_SEAL_MODULE();
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTEcalIsolationProducers);
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTHcalIsolationProducers);
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTPhotonTrackIsolationProducers);
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTElectronTrackIsolationProducers);
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTRecoEcalCandidateProducers);
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTPixelMatchElectronProducers);
DEFINE_ANOTHER_FWK_MODULE(EgammaHLTRegionalPixelSeedGeneratorProducers);
