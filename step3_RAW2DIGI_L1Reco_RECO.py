# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step3 --conditions auto:phase2_realistic -n -1 --era Phase2C1 --eventcontent FEVTDEBUGHLT --runUnscheduled -s RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-RECO --geometry Extended2023D6 --filein file:step2.root --fileout file:step3.root --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Phase2C1)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2023D6Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

## define new ME0 processes for the smeared digis
process.me0RecHitsPerfect = process.me0RecHits.clone(
    me0DigiLabel = cms.InputTag("simMuonME0Digis")
)
process.me0RecHitsSmeared = process.me0RecHits.clone(
    me0DigiLabel = cms.InputTag("simMuonME0ReDigis")
)

## define segments
process.me0SegmentsPerfect = process.me0Segments.clone(
    algo_type = 1,
    me0RecHitLabel = cms.InputTag("me0RecHitsPerfect")
)
process.me0SegmentsPerfectRU = process.me0Segments.clone(
    algo_type = 2,
    me0RecHitLabel = cms.InputTag("me0RecHitsPerfect")
)
process.me0SegmentsSmeared = process.me0Segments.clone(
    algo_type = 1,
    me0RecHitLabel = cms.InputTag("me0RecHitsSmeared")
)
process.me0SegmentsSmearedRU = process.me0Segments.clone(
    algo_type = 2,
    me0RecHitLabel = cms.InputTag("me0RecHitsSmeared")
)

## segment matching!
process.me0SegmentMatchingPerfect = process.me0SegmentMatching.clone(
    me0SegmentTag = cms.InputTag("me0SegmentsPerfect")
)
process.me0SegmentMatchingPerfectRU = process.me0SegmentMatching.clone(
    me0SegmentTag = cms.InputTag("me0SegmentsPerfectRU")
)
process.me0SegmentMatchingSmeared = process.me0SegmentMatching.clone(
    me0SegmentTag = cms.InputTag("me0SegmentsSmeared")
)
process.me0SegmentMatchingSmearedRU = process.me0SegmentMatching.clone(
    me0SegmentTag = cms.InputTag("me0SegmentsSmearedRU")
)

## muon converting!
process.me0MuonConvertingPerfect = process.me0MuonConverting.clone(
    me0SegmentTag = cms.InputTag("me0SegmentMatchingPerfect")
)
process.me0MuonConvertingPerfectRU = process.me0MuonConverting.clone(
    me0SegmentTag = cms.InputTag("me0SegmentMatchingPerfectRU")
)
process.me0MuonConvertingSmeared = process.me0MuonConverting.clone(
    me0SegmentTag = cms.InputTag("me0SegmentMatchingSmeared")
)
process.me0MuonConvertingSmearedRU = process.me0MuonConverting.clone(
    me0SegmentTag = cms.InputTag("me0SegmentMatchingSmearedRU")
)

## now propagate this all the way down...
process.me0MuonRecoPerfect = cms.Sequence(
    process.me0SegmentsPerfect *
    process.me0SegmentMatchingPerfect *
    process.me0MuonConvertingPerfect
)
process.me0MuonRecoPerfectRU = cms.Sequence(
    process.me0SegmentsPerfectRU *
    process.me0SegmentMatchingPerfectRU *
    process.me0MuonConvertingPerfectRU
)
process.me0MuonRecoSmeared = cms.Sequence(
    process.me0SegmentsSmeared *
    process.me0SegmentMatchingSmeared *
    process.me0MuonConvertingSmeared
)
process.me0MuonRecoSmearedRU = cms.Sequence(
    process.me0SegmentsSmearedRU *
    process.me0SegmentMatchingSmearedRU *
    process.me0MuonConvertingSmearedRU
)

process.me0LocalSequenceTDR = cms.Sequence(
    process.me0RecHitsPerfect *
    process.me0RecHitsSmeared *
    process.me0MuonRecoPerfect *
    process.me0MuonRecoPerfectRU *
    process.me0MuonRecoSmeared *
    process.me0MuonRecoSmearedRU
)

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing('analysis')
options.register ('nEvents',
                    -1,
                    VarParsing.multiplicity.singleton,
                    VarParsing.varType.int,
                    "Number of events")
options.parseArguments()
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.nEvents)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring("file:/eos/uscms/store/user/lpcgem/ME0TDRStudies/MuGun_0p5_30/90X_DIGI_PU200_WithNoise_BXFilter/job_0.root"),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:-1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(10485760),
    fileName = cms.untracked.string(options.outputFile),
    outputCommands = cms.untracked.vstring(
        'drop *_*_*_*',
        'keep *_g4SimHits_MuonME0*_*',
        'keep SimTracks_g4SimHits_*_*',
        'keep SimVertexs_g4SimHits_*_*',
        'keep *_me0*_*_*',
        'keep recoGenParticles_genParticles_*_*',
        'keep recoMuons_muons_*_*',
        'keep *_simMuonME0Digis_*_*',
        'keep *_simMuonME0ReDigis_*_*',
        'keep *_offlineBeamSpot_*_*',
        'keep *_primaryVertices_*_*',
        'keep recoVertexs_offlinePrimaryVertices__RECO',
        'keep recoTracks_generalTracks_*_RECO',
        'keep recoTrackExtras_generalTracks_*_RECO',
        'keep TrackingParticles_mix_MergedTrackTruth_HLT',
        'keep *_trackingParticleRecoTrackAsssociation_*_RECO',
        'drop TrackingVertexs_mix_MergedTrackTruth_HLT',
        'keep TrackingRecHitsOwned_generalTracks__RECO',
        'keep StripDigiSimLinkedmDetSetVector_simMuonCSCDigis_*_HLT',
        'keep DTLayerIdDTDigiSimLinkMuonDigiCollection_simMuonDTDigis_*_HLT',
        'keep RPCDigiSimLinkedmDetSetVector_simMuonRPCDigis_*_HLT',
        'keep GEMDigiSimLinkedmDetSetVector_simMuonGEMDigis_*_HLT',
        'keep StripDigiSimLinkedmDetSetVector_simMuonGEMDigis_*_HLT',
        'keep *_g4SimHits_Muon*_*',
        'keep PixelDigiSimLinkedmDetSetVector_simSiPixelDigis_*_HLT',
        'keep SiPixelClusteredmNewDetSetVector_siPixelClusters__RECO',
        'keep SiStripClusteredmNewDetSetVector_siStripClusters__RECO'
        ),
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase2_realistic', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)# * process.me0LocalSequenceTDR)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

#process.reconstruction_step.remove(process.me0RecHits)
#process.reconstruction_step.remove(process.me0Segments)
#process.reconstruction_step.remove(process.me0SegmentMatching)
#process.reconstruction_step.remove(process.me0MuonConverting)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)

#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)
from FWCore.ParameterSet.Utilities import cleanUnscheduled
process=cleanUnscheduled(process)


# Customisation from command line
