import FWCore.ParameterSet.Config as cms

process = cms.Process("TestME0Segment")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.Geometry.GeometryExtended2023D4Reco_cff')
# process.load('Configuration.Geometry.GeometryExtended2023HGCalMuonReco_cff')
# process.load("Geometry.GEMGeometry.me0Geometry_cfi")
# process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # 'file:/afs/cern.ch/work/m/mmaggi/ME0/SEGMENTS/CMSSW_9_0_0_pre1/src/McProd/nick_me0segment.root'
        'file:/lustre/home/piet/CondorSubmissions/Jan2017_ME0Segment_OutFromIP_820p1_HighStat_D4/step3.root'
    )
)

process.me0s = cms.EDAnalyzer('TestME0SegmentAnalyzer',
                              # RootFileName = cms.untracked.string("TestME0NickSegmentHistogramsRU.root"),
                              RootFileName = cms.untracked.string("TestMESegmentHistogramsRUinChamber.root"),
                              # segmentToken = cms.InputTag("me0Segments","ME0RERECO"),
                              segmentToken = cms.InputTag("me0Segments","","RECO"),
)

process.p = cms.Path(process.me0s)
