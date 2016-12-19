import FWCore.ParameterSet.Config as cms

# Module to create simulated ME0 Pre Reco digis.
simMuonME0NewGeoDigis = cms.EDProducer("ME0NewGeoDigiProducer",
    inputCollection    =cms.string('simMuonME0Digis'),
    numberOfSrips      =cms.uint32(768), # number of strips per partition                                             
    numberOfPartitions =cms.uint32(8),   # number of partitions per chamber                                           
    neutronAcceptance  =cms.double(2.0),   # fraction of neutron events to keep in event (>= 1 means no filtering)      
    timeResolution     =cms.double(5),   # smear time by gaussian with this sigma (in ns)....negative for no smearing 
    minBXReadout       =cms.int32(-1),  # Minimum BX to readout                                                      
    maxBXReadout       =cms.int32(1), # Maximum BX to readout                                                      
    mergeDigis         =cms.bool(True),   # Keep only one digi at the same chamber, strip, partition, and BX           
)
