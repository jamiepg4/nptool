add_library(NPSScorers SHARED NPSHitsMap.hh CalorimeterScorers.cc  SiliconScorers.cc PhotoDiodeScorers.cc ObsoleteGeneralScorers.cc DriftElectronScorers.cc )
target_link_libraries(NPSScorers ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} ${NPLib_LIBRARIES} -lNPInitialConditions -lNPInteractionCoordinates)
