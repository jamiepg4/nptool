/*****************************************************************************
 * Copyright (C) 2009-2016   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Adrien MATTA  contact address: matta@lpccaen.in2p3.fr    *
 *                                                                           *
 * Creation Date  : May 2012                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This event Generator is used to simulated the particle decay of nuclei   *
 * generated by previous event generator. Multiple cases are supported:      *
 *  - Only one particle is emmited, in this case a Cross section can be given*
 *  - If Multiple particle are emitted, a Phase Space generator is used      *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/

#include "EventGeneratorParticleDecay.hh"

// NPS
#include "Particle.hh"

// G4
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"

// G4 headers including CLHEP headers
// for generating random numbers
#include "Randomize.hh"

// NPL
#include "NPNucleus.h"
#include "NPOptionManager.h"
using namespace NPL;

// ROOT
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TF1.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventGeneratorParticleDecay::EventGeneratorParticleDecay(){
    m_ParticleStack = ParticleStack::getInstance();
}

EventGeneratorParticleDecay::~EventGeneratorParticleDecay(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorParticleDecay::ReadConfiguration(NPL::InputParser parser){

  vector<NPL::InputBlock*> blocks = parser.GetAllBlocksWithToken("ParticleDecay");
  
  m_MotherNucleiName = blocks[0]->GetMainValue();
  if(NPOptionManager::getInstance()->GetVerboseLevel())
    cout << endl << "\033[1;35m//// Particle decay found for" << m_MotherNucleiName << endl; 

  vector<string> token = {"Daughter","shoot"};
  vector<string> DaughterName;
  vector<int>   shoot;
  vector<double> ExcitationEnergy;
  string CSPath = "TGenPhaseSpace";
  string CSName = "";
  for(unsigned int i = 0 ; i < blocks.size() ; i++){
    if(blocks[i]->HasTokenList(token)){
      DaughterName = blocks[i]->GetVectorString("Daughter");
      shoot        = blocks[i]->GetVectorInt("shoot");
      
      if(blocks[i]->HasToken("ExcitationEnergy"))
        ExcitationEnergy =  blocks[i]->GetVectorDouble("ExcitationEnergy","MeV"); 
      
      if(blocks[i]->HasToken("DifferentialCrossSection")){
          vector<string> cs = blocks[i]->GetVectorString("DifferentialCrossSection");
          CSPath = cs[0]; CSName=cs[1];
      }

    }
    else{
      cout << "ERROR: check your input file formatting \033[0m" << endl; 
      exit(1);
    }
  }
  
  if(ExcitationEnergy.size()==0)
    ExcitationEnergy.resize(DaughterName.size(),0);

  SetDecay(DaughterName,shoot,ExcitationEnergy,CSPath,CSName);
  cout << "\033[0m" ;

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorParticleDecay::GenerateEvent(G4Event*){
    // Look for the decaying nucleus
    Particle decayingParticle = m_ParticleStack->SearchAndRemoveParticle(m_MotherNucleiName);
    if(decayingParticle.GetParticleDefinition()==NULL){
        G4cout << "Particle Decay Warning: The decaying particle " << m_MotherNucleiName
        << " was not found in the particle stack " << G4endl;
        return ;
    }
    
    G4ParticleDefinition* decayingParticleDefinition = decayingParticle.GetParticleDefinition();
    // Build the decaying particle four momenta vector:
    
    double NucleiEnergy= decayingParticle.GetParticleKineticEnergy()+decayingParticleDefinition->GetPDGMass();
    
    double NucleiMomentum=sqrt(NucleiEnergy*NucleiEnergy -
                               decayingParticleDefinition->GetPDGMass()*decayingParticleDefinition->GetPDGMass());
    
    G4ThreeVector Momentum = decayingParticle.GetParticleMomentumDirection().unit();
    
    // Case of one particle decaying with a user given cross section
    if(m_DifferentialCrossSection!="TGenPhaseSpace"){
        TLorentzVector NucleiLV( NucleiMomentum*Momentum.x(),
                                NucleiMomentum*Momentum.y(),
                                NucleiMomentum*Momentum.z(),
                                NucleiEnergy);
        // Shoot the angle in Center of Mass (CM) frame
        G4double ThetaCM = m_CrossSectionHist->GetRandom()* deg;
        G4double phi     = RandFlat::shoot()*2.*pi;
        
        // Build daughter particule CM LV
        // Pre compute variable for the decay
        double M  = decayingParticleDefinition->GetPDGMass();
        double m1 = m_DaughterNuclei[0]->GetPDGMass();
        double m2 = m_DaughterNuclei[1]->GetPDGMass();
        
        if(M<(m1+m2))
            G4cout << "Warning: Particle Decay forbiden by kinematic, no particle emitted "<<endl;
        
        else {
            double Energy = ( 1./(2.*M) )*( M*M + m1*m1 - m2*m2);
            double Momentum1 = sqrt(Energy*Energy - m1*m1);
            
            TVector3 FirstDaughterMomentum = Momentum1 * TVector3( sin(ThetaCM) * cos(phi),
                                                                  sin(ThetaCM) * sin(phi),
                                                                  cos(ThetaCM));
            
            TLorentzVector FirstDaughterLV(FirstDaughterMomentum,Energy);
            
            FirstDaughterLV.Boost( NucleiLV.BoostVector() );
            TLorentzVector SecondDaughterLV = NucleiLV - FirstDaughterLV;
            
            G4ThreeVector DaughterDirection = G4ThreeVector( FirstDaughterLV.X()   ,
                                                            FirstDaughterLV.Y()   ,
                                                            FirstDaughterLV.Z()   );
            
            Particle FirstDaughterParticle( m_DaughterNuclei[0],
                                           ThetaCM,
                                           FirstDaughterLV.E()-m_DaughterNuclei[0]->GetPDGMass(),
                                           DaughterDirection.unit(),
                                           decayingParticle.GetParticlePosition(),
                                           m_shoot[0]);
            
            DaughterDirection = G4ThreeVector( SecondDaughterLV.X()   ,
                                              SecondDaughterLV.Y()   ,
                                              SecondDaughterLV.Z()   );
            
            Particle SecondDaughterParticle( m_DaughterNuclei[1],
                                            ThetaCM+M_PI,
                                            SecondDaughterLV.E()-m_DaughterNuclei[1]->GetPDGMass(),
                                            DaughterDirection.unit(),
                                            decayingParticle.GetParticlePosition(),
                                            m_shoot[1]);
            
            m_ParticleStack->AddParticleToStack(FirstDaughterParticle);
            m_ParticleStack->AddParticleToStack(SecondDaughterParticle);
        }
        
    }
    
    // Case of a TGenPhaseSpace
    else{
        TLorentzVector NucleiLV( NucleiMomentum*Momentum.x()/GeV,
                                NucleiMomentum*Momentum.y()/GeV,
                                NucleiMomentum*Momentum.z()/GeV,
                                NucleiEnergy/GeV);
        
        if( !m_TPhaseSpace.SetDecay(NucleiLV, m_DaughterNuclei.size(), m_Masses) )
            G4cout << "Warning: Phase Space Decay forbiden by kinematic, or more than 18 particles, no particle emitted "<<endl;
        
        else{
            m_TPhaseSpace.Generate();
            
            TLorentzVector* daughterLV ;
            double KineticEnergy;
            
            for (unsigned int i = 0 ;  i < m_DaughterNuclei.size(); i++) {
                
                daughterLV = m_TPhaseSpace.GetDecay(i);
                G4ThreeVector daughterDirection = G4ThreeVector( daughterLV->X()   ,
                                                                daughterLV->Y()   ,
                                                                daughterLV->Z()   );
                
                KineticEnergy   = daughterLV->E()-m_Masses[i] ;
                
                Particle daughterParticle( m_DaughterNuclei[i],
                                          -1,
                                          KineticEnergy*GeV,
                                          daughterDirection.unit(),
                                          decayingParticle.GetParticlePosition(),
                                          m_shoot[i]);
                m_ParticleStack->AddParticleToStack(daughterParticle);
            }
        }
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorParticleDecay::SetTarget(Target* Target){
    m_Target = Target;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorParticleDecay::SetDecay(vector<string> DaughterName, vector<int> shoot, vector<double> ExcitationEnergy, string CSPath, string CSName){
    m_CrossSectionPath=CSPath;
    m_CrossSectionName=CSName;
    
    // Check the validity of the given data:
    if (DaughterName.size() != shoot.size() || (DaughterName.size() != ExcitationEnergy.size() && ExcitationEnergy.size()!=0) ) {
        cout << "ERROR : Missmatching information: Getting out " << endl ;
        exit(1);
    }
    
    if ( DaughterName.size() != 2 && CSPath!="TGenPhaseSpace" ) {
        cout << "ERROR : Missmatching information (User CS allowed only for two body decay): Getting out " << endl ;
        exit(1);
    }
    
    m_shoot = shoot ;
    m_ExcitationEnergy= ExcitationEnergy ;
    
    // If the Excitation Energy Token was omitted, then it is set to zero
    if(m_ExcitationEnergy.size()==0)
        for (unsigned int i = 0 ; i < DaughterName.size(); i++) {
            m_ExcitationEnergy.push_back(0);
        }
    
    // used check for mass and charge conservation
    Nucleus*  myNucleus = new Nucleus(m_MotherNucleiName);
    int InitialCharge = myNucleus->GetZ() ; int FinalCharge = 0 ;
    int InitialMass   = myNucleus->GetA() ; int FinalMass   = 0 ;
    delete myNucleus;
    for (unsigned int i = 0 ; i< DaughterName.size(); i++) {
        if(DaughterName[i] == "p" || DaughterName[i] == "proton" || DaughterName[i] == "1H"){
            m_DaughterNuclei.push_back(G4ParticleTable::GetParticleTable()->FindParticle("proton"));
            FinalMass++;FinalCharge++;
        }
        
        else if (DaughterName[i] == "n" || DaughterName[i] == "neutron"){
            m_DaughterNuclei.push_back(G4ParticleTable::GetParticleTable()->FindParticle("neutron"));
            FinalMass++;
        }
        
        else{
            Nucleus*  myNucleus1 = new Nucleus(DaughterName[i]);
            m_DaughterNuclei.push_back(G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(myNucleus1->GetZ(),
                                                                                                  myNucleus1->GetA(),
                                                                                                  m_ExcitationEnergy[i]*MeV));
            FinalMass+=myNucleus1->GetA();
            FinalCharge+=myNucleus1->GetZ();
            delete myNucleus1;
        }
    }
    
    // Check mass and charge conservation
    if (InitialMass!=FinalMass || InitialCharge!=FinalCharge) {
        G4cout << "ERROR: Mass and charge are not conserved." << G4endl;
        exit(1);
    }
    
    m_DaughterName = DaughterName;
    
    m_DifferentialCrossSection = CSPath;
    if(CSPath!="TGenPhaseSpace") {
        if(m_CrossSectionPath!="_void_"){
            m_CrossSectionHist = Read1DProfile(m_CrossSectionPath,m_CrossSectionName);
            TF1* sinus = new TF1("sinus","1/sin(x*3.141592653589793/180.)",0,180);
            m_CrossSectionHist->Divide(sinus,1);
            delete sinus;
        }
        else{
            int offset = 0;
            while(gDirectory->FindObjectAny(Form("_particlevoid_%i",offset))!=0)
                ++offset;
            
            m_CrossSectionHist = new TH1F(Form("_particlevoid_%i",offset),Form("_particlevoid_%i",offset),180,0,180);
            for(unsigned int i = 0 ; i < 180 ; i++)
                m_CrossSectionHist->Fill(i);
            
            TF1* sinus = new TF1("sinus","1/sin(x*3.141592653589793/180.)",0,180);
            m_CrossSectionHist->Divide(sinus,1);
            delete sinus;
        }
        
    }
    
    
    else{
        // Set up the array of masses
        m_Masses = new double[m_DaughterNuclei.size()];
        
        // Mass of the daugther nuclei are set once
        for (unsigned int i = 0 ; i < m_DaughterNuclei.size(); i++) {
            m_Masses[i] = m_DaughterNuclei[i]->GetPDGMass()/GeV;
        }
        
    }
    
    // Change the name of the decaying nucleus to G4 standard
    m_MotherNucleiName = m_ParticleStack->ChangeNameToG4Standard(m_MotherNucleiName);
}
