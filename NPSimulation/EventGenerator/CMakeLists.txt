add_library(NPSEventGenerator OBJECT EventGeneratorParticleDecay.cc EventGeneratorBeam.cc EventGeneratorTwoBodyReaction.cc EventGeneratorMultipleParticle.cc EventGeneratorGammaDecay.cc EventGeneratorIsotropic.cc VEventGenerator.cc) 
#target_link_libraries(NPSEventGenerator ${ROOT_LIBRARIES} ${Geant4_LIBRARIES} ${NPLib_LIBRARIES} -lNPInitialConditions -lNPInteractionCoordinates )
