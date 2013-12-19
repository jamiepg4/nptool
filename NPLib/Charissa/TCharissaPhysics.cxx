/*****************************************************************************
 * Copyright (C) 2009-2013   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Adrien MATTA  contact address: matta@ipno.in2p3.fr       *
 *                                                                           *
 * Creation Date  : December 2013                                            *
 *																			 *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class hold Charissa treated data                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/
#include "TCharissaPhysics.h"
using namespace CHARISSA_LOCAL;

//   STL
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <limits>

//   NPL
#include "RootInput.h"
#include "RootOutput.h"
#include "TAsciiFile.h"
#include "NPOptionManager.h"

//   ROOT
#include "TChain.h"
///////////////////////////////////////////////////////////////////////////

ClassImp(TCharissaPhysics)
///////////////////////////////////////////////////////////////////////////
TCharissaPhysics::TCharissaPhysics(){
	EventMultiplicity   = 0 ;
	m_EventData         = new TCharissaData ;
	m_PreTreatedData    = new TCharissaData ;
	m_EventPhysics      = this ;
	m_Spectra           = NULL;
	m_NumberOfTelescope = 0 ;
	m_MaximumStripMultiplicityAllowed = 10;
	m_StripEnergyMatchingSigma = 0.020    ;
	m_StripEnergyMatchingNumberOfSigma = 3;
	// Raw Threshold
	m_Si_X_E_RAW_Threshold = 0 ;
	m_Si_Y_E_RAW_Threshold = 0 ;
	m_CsI_E_RAW_Threshold  = 0 ;
	// Calibrated Threshold
	m_Si_X_E_Threshold = 0 ;
	m_Si_Y_E_Threshold = 0 ;
	m_CsI_E_Threshold  = 0;
	m_NumberOfStrip = 16;

	m_Take_E_Y=false;
	m_Take_T_Y=true;
  
  }
  


///////////////////////////////////////////////////////////////////////////
TCharissaPhysics::~TCharissaPhysics(){

}
///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::BuildSimplePhysicalEvent(){
  BuildPhysicalEvent();
}

///////////////////////////////////////////////////////////////////////////

void TCharissaPhysics::BuildPhysicalEvent(){
  PreTreat();
  bool check_CSI  = false ;
  
	m_Layer1_StripXEMult = m_PreTreatedData->GetCharissaLayer1StripXEMult();
	m_Layer1_StripYEMult = m_PreTreatedData->GetCharissaLayer1StripYEMult();
	m_Layer1_StripXTMult = m_PreTreatedData->GetCharissaLayer1StripXTMult();
	m_Layer1_StripYTMult = m_PreTreatedData->GetCharissaLayer1StripYTMult();
	m_Layer2_StripXEMult = m_PreTreatedData->GetCharissaLayer2StripXEMult();
	m_Layer2_StripYEMult = m_PreTreatedData->GetCharissaLayer2StripYEMult();
	m_Layer2_StripXTMult = m_PreTreatedData->GetCharissaLayer2StripXTMult();
	m_Layer2_StripYTMult = m_PreTreatedData->GetCharissaLayer2StripYTMult();
	m_CsIEMult = m_PreTreatedData->GetCharissaCsIEMult();
	m_CsITMult = m_PreTreatedData->GetCharissaCsITMult();
 
	// Layer 1
  if( Layer1_CheckEvent() == 1 ){
	  vector< TVector2 > Layer1_couple = Layer1_Match_X_Y() ;
	  EventMultiplicity = Layer1_couple.size();
    
	  for(unsigned int i = 0 ; i < Layer1_couple.size() ; ++i){
		  check_CSI = false ;
      
		  int Layer1_N = m_PreTreatedData->GetCharissaLayer1StripXEDetectorNbr(Layer1_couple[i].X()) ;
      
		  int Layer1_X = m_PreTreatedData->GetCharissaLayer1StripXEStripNbr(Layer1_couple[i].X()) ;
		  int Layer1_Y = m_PreTreatedData->GetCharissaLayer1StripYEStripNbr(Layer1_couple[i].Y()) ;
      
		  double Layer1_Si_X_E = m_PreTreatedData->GetCharissaLayer1StripXEEnergy( Layer1_couple[i].X() ) ;
		  double Layer1_Si_Y_E = m_PreTreatedData->GetCharissaLayer1StripYEEnergy( Layer1_couple[i].Y() ) ;
      
		  //  Search for associate Time
		  double Layer1_Si_X_T = -1000 ;
      
		  for(unsigned int t = 0 ; t < m_Layer1_StripXTMult ; ++t )
          {
			  if(  m_PreTreatedData->GetCharissaLayer1StripXTStripNbr( Layer1_couple[i].X() ) == m_PreTreatedData->GetCharissaLayer1StripXTStripNbr(t)
				 ||m_PreTreatedData->GetCharissaLayer1StripXTDetectorNbr( Layer1_couple[i].X() ) == m_PreTreatedData->GetCharissaLayer1StripXTDetectorNbr(t))
				  Layer1_Si_X_T = m_PreTreatedData->GetCharissaLayer1StripXTTime(t);
          }
      
		  double Layer1_Si_Y_T = -1000 ;
      
		  for(unsigned int t = 0 ; t < m_Layer1_StripYTMult ; ++t )
          {
			  if(  m_PreTreatedData->GetCharissaLayer1StripYTStripNbr( Layer1_couple[i].Y() ) == m_PreTreatedData->GetCharissaLayer1StripYTStripNbr(t)
				 ||m_PreTreatedData->GetCharissaLayer1StripYTDetectorNbr( Layer1_couple[i].Y() ) == m_PreTreatedData->GetCharissaLayer1StripYTDetectorNbr(t))
				  Layer1_Si_Y_T = m_PreTreatedData->GetCharissaLayer1StripYTTime(t);
          }
      
		  Layer1_Si_X.push_back(Layer1_X) ; Layer1_Si_Y.push_back(Layer1_Y) ; Layer1_TelescopeNumber.push_back(Layer1_N) ;
      
		  if(m_Take_E_Y) Layer1_Si_E.push_back(Layer1_Si_Y_E);
		  else           Layer1_Si_E.push_back(Layer1_Si_X_E);
      
		  if(m_Take_T_Y) Layer1_Si_T.push_back(Layer1_Si_Y_T);
		  else           Layer1_Si_T.push_back(Layer1_Si_X_T);
      
		  // Store the other value for checking purpose
		  Layer1_Si_EX.push_back(Layer1_Si_X_E);            
		  Layer1_Si_TX.push_back(Layer1_Si_X_T);            
		  Layer1_Si_EY.push_back(Layer1_Si_Y_E);            
		  Layer1_Si_TY.push_back(Layer1_Si_Y_T);  
	  }
  }

		
	// Layer 2
	if( Layer2_CheckEvent() == 1 ){
		vector< TVector2 > Layer2_couple = Layer2_Match_X_Y() ;
		EventMultiplicity = Layer2_couple.size();
		
		for(unsigned int i = 0 ; i < Layer2_couple.size() ; ++i){
				
			check_CSI = false ;
				
			int Layer2_N = m_PreTreatedData->GetCharissaLayer2StripXEDetectorNbr(Layer2_couple[i].X()) ;
			int Layer2_X = m_PreTreatedData->GetCharissaLayer2StripXEStripNbr(Layer2_couple[i].X()) ;
			int Layer2_Y = m_PreTreatedData->GetCharissaLayer2StripYEStripNbr(Layer2_couple[i].Y()) ;
			
			double Layer2_Si_X_E = m_PreTreatedData->GetCharissaLayer1StripXEEnergy( Layer2_couple[i].X() ) ;
			double Layer2_Si_Y_E = m_PreTreatedData->GetCharissaLayer1StripYEEnergy( Layer2_couple[i].Y() ) ;
				
				//  Search for associate Time
			double Layer2_Si_X_T = -1000 ;
				
			for(unsigned int t = 0 ; t < m_Layer2_StripXTMult ; ++t )
			{
				if(  m_PreTreatedData->GetCharissaLayer2StripXTStripNbr( Layer2_couple[i].X() ) == m_PreTreatedData->GetCharissaLayer2StripXTStripNbr(t)
					||m_PreTreatedData->GetCharissaLayer2StripXTDetectorNbr( Layer2_couple[i].X() ) == m_PreTreatedData->GetCharissaLayer2StripXTDetectorNbr(t))
					Layer2_Si_X_T = m_PreTreatedData->GetCharissaLayer2StripXTTime(t);
			}
				
			double Layer2_Si_Y_T = -1000 ;
				
			for(unsigned int t = 0 ; t < m_Layer2_StripYTMult ; ++t )
			{
				if(  m_PreTreatedData->GetCharissaLayer2StripYTStripNbr( Layer2_couple[i].Y() ) == m_PreTreatedData->GetCharissaLayer2StripYTStripNbr(t)
					||m_PreTreatedData->GetCharissaLayer2StripYTDetectorNbr( Layer2_couple[i].Y() ) == m_PreTreatedData->GetCharissaLayer2StripYTDetectorNbr(t))
					Layer2_Si_Y_T = m_PreTreatedData->GetCharissaLayer2StripYTTime(t);
			}
				
			Layer2_Si_X.push_back(Layer2_X) ; Layer2_Si_Y.push_back(Layer2_Y) ; Layer2_TelescopeNumber.push_back(Layer2_N) ;
				
			if(m_Take_E_Y) Layer2_Si_E.push_back(Layer2_Si_Y_E);
			else           Layer2_Si_E.push_back(Layer2_Si_X_E);
				
			if(m_Take_T_Y) Layer2_Si_T.push_back(Layer2_Si_Y_T);
			else           Layer2_Si_T.push_back(Layer2_Si_X_T);
				
				// Store the other value for checking purpose
			Layer2_Si_EX.push_back(Layer2_Si_X_E);            
			Layer2_Si_TX.push_back(Layer2_Si_X_T);            
			Layer2_Si_EY.push_back(Layer2_Si_Y_E);            
			Layer2_Si_TY.push_back(Layer2_Si_Y_T); 
		
			for(unsigned int j = 0 ; j < m_CsIEMult ; ++j){
				if(m_PreTreatedData->GetCharissaCsIEDetectorNbr(j)==Layer2_N){
					if(Match_Si_CsI( Layer2_X, Layer2_Y , m_PreTreatedData->GetCharissaCsIECristalNbr(j) ) ){
						CsI_N.push_back( m_PreTreatedData->GetCharissaCsIECristalNbr(j) ) ;
						CsI_E.push_back( m_PreTreatedData->GetCharissaCsIEEnergy(j) ) ;
		
						//   Look for associate Time
						for(unsigned int k =0 ; k  < m_CsITMult ; ++k){
							// Same Cristal; Same Detector
							if(   m_PreTreatedData->GetCharissaCsIECristalNbr(j)==m_PreTreatedData->GetCharissaCsITCristalNbr(k)
							   && m_PreTreatedData->GetCharissaCsIEDetectorNbr(j)==m_PreTreatedData->GetCharissaCsITDetectorNbr(k) )
								CsI_T.push_back( m_PreTreatedData->GetCharissaCsITTime(j) ) ; break ;
						}
						check_CSI = true ;
					}
				}
			}
      
			if(!check_CSI){
				CsI_N.push_back(0)       ;
				CsI_E.push_back(-1000)   ;
				CsI_T.push_back(-1000)   ;
			}
		}
	}

	 


 
  return;
  
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::PreTreat(){
	
	ClearPreTreatedData();
	m_Layer1_StripXEMult = m_EventData->GetCharissaLayer1StripXEMult();
	m_Layer1_StripYEMult = m_EventData->GetCharissaLayer1StripYEMult();
	m_Layer1_StripXTMult = m_EventData->GetCharissaLayer1StripXTMult();
	m_Layer1_StripYTMult = m_EventData->GetCharissaLayer1StripYTMult();

	m_Layer2_StripXEMult = m_EventData->GetCharissaLayer2StripXEMult();
	m_Layer2_StripYEMult = m_EventData->GetCharissaLayer2StripYEMult();
	m_Layer2_StripXTMult = m_EventData->GetCharissaLayer2StripXTMult();
	m_Layer2_StripYTMult = m_EventData->GetCharissaLayer2StripYTMult();
	
	m_CsIEMult = m_EventData->GetCharissaCsIEMult();
	m_CsITMult = m_EventData->GetCharissaCsITMult();
  
  //   X Layer1
  //   E
  for(unsigned int i = 0 ; i < m_Layer1_StripXEMult ; ++i){
    if( m_EventData->GetCharissaLayer1StripXEEnergy(i)>m_Si_X_E_RAW_Threshold){
      double Layer1_EX = fDE_X_E(m_EventData , i);
      if( Layer1_EX > m_Si_X_E_Threshold ){
        m_PreTreatedData->SetCharissaLayer1StripXEDetectorNbr( m_EventData->GetCharissaLayer1StripXEDetectorNbr(i) );
        m_PreTreatedData->SetCharissaLayer1StripXEStripNbr( m_EventData->GetCharissaLayer1StripXEStripNbr(i) );
        m_PreTreatedData->SetCharissaLayer1StripXEEnergy( Layer1_EX );
      }
    }
  }
  
  //   T
  for(unsigned int i = 0 ; i < m_Layer1_StripXTMult ; ++i){
    if(IsValidChannel("X", m_EventData->GetCharissaLayer1StripXTDetectorNbr(i), m_EventData->GetCharissaLayer1StripXTStripNbr(i))){
      m_PreTreatedData->SetCharissaLayer1StripXTDetectorNbr( m_EventData->GetCharissaLayer1StripXTDetectorNbr(i) );
      m_PreTreatedData->SetCharissaLayer1StripXTStripNbr( m_EventData->GetCharissaLayer1StripXTStripNbr(i) );
      m_PreTreatedData->SetCharissaLayer1StripXTTime( fDE_X_T(m_EventData , i) );
    }
  }
  
  //   Y  Layer1
  //   E
  for(unsigned int i = 0 ; i < m_Layer1_StripYEMult ; ++i){
    if( m_EventData->GetCharissaLayer1StripYEEnergy(i)>m_Si_Y_E_RAW_Threshold){
      double Layer1_EY = fDE_Y_E(m_EventData , i);
      if( Layer1_EY >m_Si_Y_E_Threshold ){
        m_PreTreatedData->SetCharissaLayer1StripYEDetectorNbr( m_EventData->GetCharissaLayer1StripYEDetectorNbr(i) );
        m_PreTreatedData->SetCharissaLayer1StripYEStripNbr( m_EventData->GetCharissaLayer1StripYEStripNbr(i) );
        m_PreTreatedData->SetCharissaLayer1StripYEEnergy( Layer1_EY );
      }
    }
  }

	//   T
	for(unsigned int i = 0 ; i < m_Layer1_StripYTMult ; ++i){
		if(IsValidChannel("Y", m_EventData->GetCharissaLayer1StripYTDetectorNbr(i), m_EventData->GetCharissaLayer1StripYTStripNbr(i))){
			m_PreTreatedData->SetCharissaLayer1StripYTDetectorNbr( m_EventData->GetCharissaLayer1StripYTDetectorNbr(i) );
			m_PreTreatedData->SetCharissaLayer1StripYTStripNbr( m_EventData->GetCharissaLayer1StripYTStripNbr(i) );
			m_PreTreatedData->SetCharissaLayer1StripYTTime( fDE_Y_T(m_EventData , i) );
		}
	}
	

	//   X Layer2
	//   E
	for(unsigned int i = 0 ; i < m_Layer2_StripXEMult ; ++i){
    if( m_EventData->GetCharissaLayer2StripXEEnergy(i)>m_Si_X_E_RAW_Threshold){
			double Layer2_EX = fE_X_E(m_EventData , i);
      if( Layer2_EX > m_Si_X_E_Threshold ){
        
				m_PreTreatedData->SetCharissaLayer2StripXEDetectorNbr( m_EventData->GetCharissaLayer2StripXEDetectorNbr(i) );
				m_PreTreatedData->SetCharissaLayer2StripXEStripNbr( m_EventData->GetCharissaLayer2StripXEStripNbr(i) );
				m_PreTreatedData->SetCharissaLayer2StripXEEnergy( Layer2_EX );
			}
		}
	}
	

	//   T
	for(unsigned int i = 0 ; i < m_Layer2_StripXTMult ; ++i){
		if(IsValidChannel("X", m_EventData->GetCharissaLayer2StripXTDetectorNbr(i), m_EventData->GetCharissaLayer2StripXTStripNbr(i))){
			m_PreTreatedData->SetCharissaLayer2StripXTDetectorNbr( m_EventData->GetCharissaLayer2StripXTDetectorNbr(i) );
			m_PreTreatedData->SetCharissaLayer2StripXTStripNbr( m_EventData->GetCharissaLayer2StripXTStripNbr(i) );
			m_PreTreatedData->SetCharissaLayer2StripXTTime( fE_X_T(m_EventData , i) );
		}
	}
	
	//   Y  Layer2
	//   E
	for(unsigned int i = 0 ; i < m_Layer2_StripYEMult ; ++i){
		if( m_EventData->GetCharissaLayer2StripYEEnergy(i)>m_Si_Y_E_RAW_Threshold){
			double Layer2_EY = fE_Y_E(m_EventData , i);
			if( Layer2_EY >m_Si_Y_E_Threshold ){
				m_PreTreatedData->SetCharissaLayer2StripYEDetectorNbr( m_EventData->GetCharissaLayer2StripYEDetectorNbr(i) );
				m_PreTreatedData->SetCharissaLayer2StripYEStripNbr( m_EventData->GetCharissaLayer2StripYEStripNbr(i) );
				m_PreTreatedData->SetCharissaLayer2StripYEEnergy( Layer2_EY );
			}
		}
	}
	
  //   T
	for(unsigned int i = 0 ; i < m_Layer2_StripYTMult ; ++i){
		if( IsValidChannel("Y", m_EventData->GetCharissaLayer2StripYTDetectorNbr(i), m_EventData->GetCharissaLayer1StripYTStripNbr(i))){
				m_PreTreatedData->SetCharissaLayer2StripYTDetectorNbr( m_EventData->GetCharissaLayer2StripYTDetectorNbr(i) );
				m_PreTreatedData->SetCharissaLayer2StripYTStripNbr( m_EventData->GetCharissaLayer2StripYTStripNbr(i) );
				m_PreTreatedData->SetCharissaLayer2StripYTTime( fE_Y_T(m_EventData,i) );
		}
	}
	
  //   CsI
  //   E
  for(unsigned int i = 0 ; i < m_CsIEMult ; ++i){
    if( m_EventData->GetCharissaCsIEEnergy(i)>m_CsI_E_RAW_Threshold && IsValidChannel("CsI", m_EventData->GetCharissaCsIEDetectorNbr(i), m_EventData->GetCharissaCsIECristalNbr(i))){
      double ECsI = fCsI_E(m_EventData , i);
      if( ECsI > m_CsI_E_Threshold ){
        m_PreTreatedData->SetCharissaCsIEDetectorNbr( m_EventData->GetCharissaCsIEDetectorNbr(i) );
        m_PreTreatedData->SetCharissaCsIECristalNbr( m_EventData->GetCharissaCsIECristalNbr(i) );
        m_PreTreatedData->SetCharissaCsIEEnergy( ECsI );
      }
    }
  }
  
  //   T
  for(unsigned int i = 0 ; i < m_CsITMult ; ++i){
    if(IsValidChannel("CsI", m_EventData->GetCharissaCsITDetectorNbr(i), m_EventData->GetCharissaCsITCristalNbr(i))){
      m_PreTreatedData->SetCharissaCsITDetectorNbr( m_EventData->GetCharissaCsITDetectorNbr(i) );
      m_PreTreatedData->SetCharissaCsITCristalNbr( m_EventData->GetCharissaCsITCristalNbr(i) );
      m_PreTreatedData->SetCharissaCsITTime( fCsI_T(m_EventData , i) );
    }
  }
  
  return;
}


///////////////////////////////////////////////////////////////////////////
int TCharissaPhysics :: Layer1_CheckEvent(){
  // Check the size of the different elements
  if(         m_PreTreatedData->GetCharissaLayer1StripXEMult() == m_PreTreatedData->GetCharissaLayer1StripYEMult() /*&& m_PreTreatedData->GetCharissaLayer1StripYEMult() == m_PreTreatedData->GetCharissaLayer1StripXTMult() &&  m_PreTreatedData->GetCharissaLayer1StripXTMult() == m_PreTreatedData->GetCharissaLayer1StripYTMult()*/  )
    return 1 ; // Regular Event
  
  else if(         m_PreTreatedData->GetCharissaLayer1StripXEMult() == m_PreTreatedData->GetCharissaLayer1StripYEMult()+1 || m_PreTreatedData->GetCharissaLayer1StripXEMult() == m_PreTreatedData->GetCharissaLayer1StripYEMult()-1  )
    return 2 ; // Pseudo Event, potentially interstrip
  
  else
    return -1 ; // Rejected Event
  
}

///////////////////////////////////////////////////////////////////////////
int TCharissaPhysics :: Layer2_CheckEvent(){
	// Check the size of the different elements
	if(         m_PreTreatedData->GetCharissaLayer2StripXEMult() == m_PreTreatedData->GetCharissaLayer2StripYEMult() /*&& m_PreTreatedData->GetCharissaLayer1StripYEMult() == m_PreTreatedData->GetCharissaLayer1StripXTMult() &&  m_PreTreatedData->GetCharissaLayer1StripXTMult() == m_PreTreatedData->GetCharissaLayer1StripYTMult()*/  )
		return 1 ; // Regular Event
	
	else if(         m_PreTreatedData->GetCharissaLayer2StripXEMult() == m_PreTreatedData->GetCharissaLayer2StripYEMult()+1 || m_PreTreatedData->GetCharissaLayer2StripXEMult() == m_PreTreatedData->GetCharissaLayer2StripYEMult()-1  )
		return 2 ; // Pseudo Event, potentially interstrip
	
	else
		return -1 ; // Rejected Event
	
}

///////////////////////////////////////////////////////////////////////////
bool TCharissaPhysics :: ResolvePseudoEvent(){
  return false;
}

///////////////////////////////////////////////////////////////////////////
vector < TVector2 > TCharissaPhysics :: Layer1_Match_X_Y(){
  vector < TVector2 > ArrayOfGoodCouple ;
  m_Layer1_StripXEMult = m_PreTreatedData->GetCharissaLayer1StripXEMult();
  m_Layer1_StripYEMult = m_PreTreatedData->GetCharissaLayer1StripXEMult();
  
  // Prevent code from treating very high multiplicity Event
  // Those event are not physical anyway and that improve speed.
  if( m_Layer1_StripXEMult > m_MaximumStripMultiplicityAllowed || m_Layer1_StripYEMult > m_MaximumStripMultiplicityAllowed )
    return ArrayOfGoodCouple;
  
  for(unsigned int i = 0 ; i < m_Layer1_StripXEMult ; ++i){
    for(unsigned int j = 0 ; j < m_Layer1_StripYEMult ; j++){
      //   if same detector check energy
      if ( m_PreTreatedData->GetCharissaLayer1StripXEDetectorNbr(i) == m_PreTreatedData->GetCharissaLayer1StripYEDetectorNbr(j) ){
        //   Look if energy match
        if( abs( (m_PreTreatedData->GetCharissaLayer1StripXEEnergy(i)-m_PreTreatedData->GetCharissaLayer1StripYEEnergy(j))/2. ) < m_StripEnergyMatchingNumberOfSigma*m_StripEnergyMatchingSigma ){
          // Special Option, if the event is between two CsI cristal, it is rejected.
          if(m_Ignore_not_matching_CsI){
            bool check_validity=false;
            for (unsigned int hh = 0 ; hh<m_NumberOfStrip ; ++hh ){
              if( Match_Si_CsI(m_PreTreatedData->GetCharissaLayer1StripXEStripNbr(i), m_PreTreatedData->GetCharissaLayer1StripYEStripNbr(j) , hh+1) )
                check_validity=true;
              }
            
            if(check_validity)
              ArrayOfGoodCouple . push_back ( TVector2(i,j) ) ;
          }
          
          
          
          // Regular case, keep the event
          else ArrayOfGoodCouple . push_back ( TVector2(i,j) ) ;
        }
      }
    }
  }
  
  //   Prevent to treat event with ambiguous matchin beetween X and Y
  if( ArrayOfGoodCouple.size() > m_Layer1_StripXEMult ) ArrayOfGoodCouple.clear() ;
  
  return ArrayOfGoodCouple;
}

///////////////////////////////////////////////////////////////////////////
vector < TVector2 > TCharissaPhysics :: Layer2_Match_X_Y(){
	vector < TVector2 > ArrayOfGoodCouple ;
	m_Layer2_StripXEMult = m_PreTreatedData->GetCharissaLayer2StripXEMult();
	m_Layer2_StripYEMult = m_PreTreatedData->GetCharissaLayer2StripXEMult();
	
	// Prevent code from treating very high multiplicity Event
	// Those event are not physical anyway and that improve speed.
	if( m_Layer2_StripXEMult > m_MaximumStripMultiplicityAllowed || m_Layer2_StripYEMult > m_MaximumStripMultiplicityAllowed )
		return ArrayOfGoodCouple;
	
	for(unsigned int i = 0 ; i < m_Layer2_StripXEMult ; ++i){
		for(unsigned int j = 0 ; j < m_Layer2_StripYEMult ; j++){
			//   if same detector check energy
			if ( m_PreTreatedData->GetCharissaLayer2StripXEDetectorNbr(i) == m_PreTreatedData->GetCharissaLayer2StripYEDetectorNbr(j) ){
				//   Look if energy match
				if( abs( (m_PreTreatedData->GetCharissaLayer2StripXEEnergy(i)-m_PreTreatedData->GetCharissaLayer2StripYEEnergy(j))/2. ) < m_StripEnergyMatchingNumberOfSigma*m_StripEnergyMatchingSigma ){
					// Special Option, if the event is between two CsI cristal, it is rejected.
					if(m_Ignore_not_matching_CsI){
						bool check_validity=false;
						for (unsigned int hh = 0 ; hh<m_NumberOfStrip ; ++hh ){
							if( Match_Si_CsI(m_PreTreatedData->GetCharissaLayer2StripXEStripNbr(i), m_PreTreatedData->GetCharissaLayer2StripYEStripNbr(j) , hh+1) )
								check_validity=true;
						}
						
						if(check_validity)
							ArrayOfGoodCouple . push_back ( TVector2(i,j) ) ;
					}
					
					
					
					// Regular case, keep the event
					else ArrayOfGoodCouple . push_back ( TVector2(i,j) ) ;
				}
			}
		}
	}
	
	//   Prevent to treat event with ambiguous matchin beetween X and Y
	if( ArrayOfGoodCouple.size() > m_Layer2_StripXEMult ) ArrayOfGoodCouple.clear() ;
	
	return ArrayOfGoodCouple;
}





////////////////////////////////////////////////////////////////////////////
bool TCharissaPhysics :: IsValidChannel(const string DetectorType, const int telescope , const int channel){
 if(DetectorType == "CsI")
   return *(m_CsIChannelStatus[telescope-1].begin()+channel-1);
  
  else if(DetectorType == "X")
    return *(m_XChannelStatus[telescope-1].begin()+channel-1);
  
  else if(DetectorType == "Y")
    return *(m_YChannelStatus[telescope-1].begin()+channel-1);
  
  else return false;
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::ReadAnalysisConfig(){
  bool ReadingStatus = false;
  
  // path to file
  string FileName = "./configs/ConfigCharissa.dat";
  
  // open analysis config file
  ifstream AnalysisConfigFile;
  AnalysisConfigFile.open(FileName.c_str());
  
  if (!AnalysisConfigFile.is_open()) {
    cout << " No ConfigCharissa.dat found: Default parameters loaded for Analysis " << FileName << endl;
    return;
  }
  cout << " Loading user parameters for Analysis from ConfigCharissa.dat " << endl;
  
  // Save it in a TAsciiFile
  TAsciiFile* asciiConfig = RootOutput::getInstance()->GetAsciiFileAnalysisConfig();
  asciiConfig->AppendLine("%%% ConfigCharissaCHARISSA.dat %%%");
  asciiConfig->Append(FileName.c_str());
  asciiConfig->AppendLine("");
  // read analysis config file
  string LineBuffer,DataBuffer,whatToDo;
  while (!AnalysisConfigFile.eof()) {
    // Pick-up next line
    getline(AnalysisConfigFile, LineBuffer);
    
    // search for "header"
    if (LineBuffer.compare(0, 11, "ConfigCharissa") == 0) ReadingStatus = true;
    
    // loop on tokens and data
    while (ReadingStatus ) {
      
      whatToDo="";
      AnalysisConfigFile >> whatToDo;
      
      // Search for comment symbol (%)
      if (whatToDo.compare(0, 1, "%") == 0) {
        AnalysisConfigFile.ignore(numeric_limits<streamsize>::max(), '\n' );
      }
      
      else if (whatToDo=="MAX_STRIP_MULTIPLICITY") {
        AnalysisConfigFile >> DataBuffer;
        m_MaximumStripMultiplicityAllowed = atoi(DataBuffer.c_str() );
        cout << "MAXIMUN STRIP MULTIPLICITY " << m_MaximumStripMultiplicityAllowed << endl;
      }
      
      else if (whatToDo=="STRIP_ENERGY_MATCHING_SIGMA") {
        AnalysisConfigFile >> DataBuffer;
        m_StripEnergyMatchingSigma = atof(DataBuffer.c_str() );
        cout << "STRIP ENERGY MATCHING SIGMA " << m_StripEnergyMatchingSigma <<endl;
      }
      
      else if (whatToDo=="STRIP_ENERGY_MATCHING_NUMBER_OF_SIGMA") {
        AnalysisConfigFile >> DataBuffer;
        m_StripEnergyMatchingNumberOfSigma = atoi(DataBuffer.c_str() );
        cout << "STRIP ENERGY MATCHING NUMBER OF SIGMA " << m_StripEnergyMatchingNumberOfSigma << endl;
      }
      
      else if (whatToDo== "DISABLE_ALL") {
        AnalysisConfigFile >> DataBuffer;
        cout << whatToDo << "  " << DataBuffer << endl;
        int telescope = atoi(DataBuffer.substr(2,1).c_str());
        vector< bool > ChannelStatus;
        ChannelStatus.resize( m_NumberOfStrip,false);
        m_XChannelStatus[telescope-1] = ChannelStatus;
        m_YChannelStatus[telescope-1] = ChannelStatus;
        ChannelStatus.resize(m_NumberOfStrip,false);
        m_CsIChannelStatus[telescope-1]  = ChannelStatus;
      }
      
      else if (whatToDo == "DISABLE_CHANNEL") {
        AnalysisConfigFile >> DataBuffer;
        cout << whatToDo << "  " << DataBuffer << endl;
        int telescope = atoi(DataBuffer.substr(2,1).c_str());
        int channel = -1;
        if (DataBuffer.compare(3,4,"STRX") == 0) {
          channel = atoi(DataBuffer.substr(7).c_str());
          *(m_XChannelStatus[telescope-1].begin()+channel-1) = false;
        }
        
        else if (DataBuffer.compare(3,4,"STRY") == 0) {
          channel = atoi(DataBuffer.substr(7).c_str());
          *(m_YChannelStatus[telescope-1].begin()+channel-1) = false;
        }
        
        
        else if (DataBuffer.compare(3,3,"CSI") == 0) {
          channel = atoi(DataBuffer.substr(6).c_str());
          *(m_CsIChannelStatus[telescope-1].begin()+channel-1) = false;
        }
        
        else cout << "Warning: detector type for CharissaCHARISSA unknown!" << endl;
        
      }
      
      else if (whatToDo=="TAKE_E_Y") {
        m_Take_E_Y = true;
        cout << whatToDo << endl;
      }
      
      else if (whatToDo=="TAKE_T_Y") {
        m_Take_T_Y = true;
        cout << whatToDo << endl;
      }
      
      else if (whatToDo=="TAKE_E_X") {
        m_Take_E_Y = false;
        cout << whatToDo << endl;
      }
      
      else if (whatToDo=="TAKE_T_X") {
        m_Take_T_Y = false;
        cout << whatToDo << endl;
      }
      
      else if (whatToDo== "IGNORE_NOT_MATCHING_CSI") {
        m_Ignore_not_matching_CsI = true;
        cout << whatToDo << endl;
      }
      
      else if (whatToDo=="CSI_SIZE") {
        AnalysisConfigFile >> DataBuffer;
        m_CsI_Size = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_CsI_Size << endl;
      }
      
      
      else if (whatToDo=="SI_X_E_RAW_THRESHOLD") {
        AnalysisConfigFile >> DataBuffer;
        m_Si_X_E_RAW_Threshold = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_Si_X_E_RAW_Threshold << endl;
      }
      
      else if (whatToDo=="SI_Y_E_RAW_THRESHOLD") {
        AnalysisConfigFile >> DataBuffer;
        m_Si_Y_E_RAW_Threshold = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_Si_Y_E_RAW_Threshold << endl;
      }
      
		
      else if (whatToDo== "CSI_E_RAW_THRESHOLD") {
        AnalysisConfigFile >> DataBuffer;
        m_CsI_E_Threshold = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_CsI_E_Threshold << endl;
      }
      
      else if (whatToDo=="SI_X_E_THRESHOLD") {
        AnalysisConfigFile >> DataBuffer;
        m_Si_X_E_Threshold = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_Si_X_E_Threshold << endl;
      }
      
      else if (whatToDo== "SI_Y_E_THRESHOLD") {
        AnalysisConfigFile >> DataBuffer;
        m_Si_Y_E_Threshold = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_Si_Y_E_Threshold << endl;
      }
      
      
      else if (whatToDo=="CSI_E_THRESHOLD") {
        AnalysisConfigFile >> DataBuffer;
        m_CsI_E_Threshold = atoi(DataBuffer.c_str());
        cout << whatToDo << " " << m_CsI_E_Threshold << endl;
      }
      
      else {
        ReadingStatus = false;
      }
      
    }
  }
}




///////////////////////////////////////////////////////////////////////////
bool TCharissaPhysics :: Match_Si_CsI(int X, int Y , int CristalNbr){
  
  if( abs(m_CsI_MatchingX[CristalNbr-1] - X) < m_CsI_Size/2.&&
     abs(m_CsI_MatchingY[CristalNbr-1] - Y) < m_CsI_Size/2.)
    
    return true ;
  
  else return false;
  
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::Clear(){
	EventMultiplicity= 0 ;
  
	Layer1_TelescopeNumber.clear();
	EventType.clear();
	TotalEnergy.clear();
  
	// Si X
	Layer1_Si_E.clear();
	Layer1_Si_T.clear();
	Layer1_Si_X.clear();
	Layer1_Si_Y.clear();
	Layer2_Si_E.clear();
	Layer2_Si_T.clear();
	Layer2_Si_X.clear();
	Layer2_Si_Y.clear();
	
	
	// CsI
	CsI_E.clear();
	CsI_T.clear();
	CsI_N.clear();
  
	Layer1_Si_EX.clear();
	Layer1_Si_TX.clear();
	Layer1_Si_EY.clear();
	Layer1_Si_TY.clear();
	Layer1_TelescopeNumber_X.clear();
	Layer1_TelescopeNumber_Y.clear();
	Layer2_Si_EX.clear();
	Layer2_Si_TX.clear();
	Layer2_Si_EY.clear();
	Layer2_Si_TY.clear();
	Layer2_TelescopeNumber_X.clear();
	Layer2_TelescopeNumber_Y.clear();
}
///////////////////////////////////////////////////////////////////////////

void TCharissaPhysics::ReadCalibrationRun(){
  m_Layer1_StripXEMult = m_EventData->GetCharissaLayer1StripXEMult();
  m_Layer1_StripYEMult = m_EventData->GetCharissaLayer1StripYEMult();
  m_Layer1_StripXTMult = m_EventData->GetCharissaLayer1StripXTMult();
  m_Layer1_StripYTMult = m_EventData->GetCharissaLayer1StripYTMult();
	m_Layer2_StripXEMult = m_EventData->GetCharissaLayer2StripXEMult();
	m_Layer2_StripYEMult = m_EventData->GetCharissaLayer2StripYEMult();
	m_Layer2_StripXTMult = m_EventData->GetCharissaLayer2StripXTMult();
	m_Layer2_StripYTMult = m_EventData->GetCharissaLayer2StripYTMult();
  m_CsIEMult = m_EventData->GetCharissaCsIEMult();
  m_CsITMult = m_EventData->GetCharissaCsITMult();
  
  //   X Layer 1
  //   E
  for(unsigned int i = 0 ; i < m_Layer1_StripXEMult;++i){
    Layer1_TelescopeNumber_X.push_back(m_EventData->GetCharissaLayer1StripXEDetectorNbr(i));
    Layer1_Si_EX.push_back( fDE_X_E( m_EventData , i) );
    Layer1_Si_X.push_back(m_EventData->GetCharissaLayer1StripXEStripNbr(i));
  }
  //   T
  for(unsigned int i = 0 ; i < m_Layer1_StripXTMult;++i){
    Layer1_TelescopeNumber_X.push_back(m_EventData->GetCharissaLayer1StripXTDetectorNbr(i));
    Layer1_Si_TX.push_back( fDE_X_T( m_EventData , i) );
    Layer1_Si_X.push_back(m_EventData->GetCharissaLayer1StripXTStripNbr(i));
  }
  
  //   Y Layer 1
  //   E
  for(unsigned int i = 0 ; i < m_Layer1_StripYEMult;++i){
    Layer1_TelescopeNumber_Y.push_back(m_EventData->GetCharissaLayer1StripYEDetectorNbr(i));
    Layer1_Si_EY.push_back( fDE_Y_E( m_EventData , i) );
    Layer1_Si_Y.push_back(m_EventData->GetCharissaLayer1StripYEStripNbr(i));
  }
  
  //   T
  for(unsigned int i = 0 ; i < m_Layer1_StripYTMult;++i){
        Layer1_TelescopeNumber_Y.push_back(m_EventData->GetCharissaLayer1StripYTDetectorNbr(i));
        Layer1_Si_TY.push_back( fDE_Y_T( m_EventData , i) );
        Layer1_Si_Y.push_back(m_EventData->GetCharissaLayer1StripYTStripNbr(i));
  }
 
	
	//   X Layer 2
	//   E
	for(unsigned int i = 0 ; i < m_Layer2_StripXEMult;++i){
		Layer2_TelescopeNumber_X.push_back(m_EventData->GetCharissaLayer2StripXEDetectorNbr(i));
		Layer2_Si_EX.push_back( fE_X_E( m_EventData , i) );
		Layer2_Si_X.push_back(m_EventData->GetCharissaLayer2StripXEStripNbr(i));
	}
	//   T
	for(unsigned int i = 0 ; i < m_Layer2_StripXTMult;++i){
		Layer2_TelescopeNumber_X.push_back(m_EventData->GetCharissaLayer2StripXTDetectorNbr(i));
		Layer2_Si_TX.push_back( fE_X_T( m_EventData , i) );
		Layer2_Si_X.push_back(m_EventData->GetCharissaLayer2StripXTStripNbr(i));
	}
	
	//   Y Layer 2
	//   E
	for(unsigned int i = 0 ; i < m_Layer2_StripYEMult;++i){
		Layer2_TelescopeNumber_Y.push_back(m_EventData->GetCharissaLayer2StripYEDetectorNbr(i));
		Layer2_Si_EY.push_back( fE_Y_E( m_EventData , i) );
		Layer2_Si_Y.push_back(m_EventData->GetCharissaLayer2StripYEStripNbr(i));
	}
	
	//   T
	for(unsigned int i = 0 ; i < m_Layer2_StripYTMult;++i){
        Layer2_TelescopeNumber_Y.push_back(m_EventData->GetCharissaLayer2StripYTDetectorNbr(i));
        Layer2_Si_TY.push_back( fE_Y_T( m_EventData , i) );
        Layer2_Si_Y.push_back(m_EventData->GetCharissaLayer2StripYTStripNbr(i));
	}
	
	
  //CsI Energy
  for(unsigned int j = 0 ; j < m_CsIEMult ; ++j){
        CsI_N.push_back(m_EventData->GetCharissaCsIECristalNbr(j)) ;
        CsI_E.push_back(fCsI_E(m_EventData , j)) ;
  }
  
  //CsI Time
  for(unsigned int j = 0 ; j < m_CsITMult ; ++j){
        CsI_T.push_back(fCsI_T(m_EventData , j)) ;
  }
  
}

////   Innherited from VDetector Class   ////

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::ReadConfiguration(string Path){
  ifstream ConfigFile              ;
  ConfigFile.open(Path.c_str())    ;
  string LineBuffer                ;
  string DataBuffer                ;
  
  // A:X1_Y1     --> X:1    Y:1
  // B:X m_NumberOfStrip_Y1   --> X: m_NumberOfStrip  Y:1
  // C:X1_Y m_NumberOfStrip   --> X:1    Y: m_NumberOfStrip
  // D:X m_NumberOfStrip_Y m_NumberOfStrip --> X: m_NumberOfStrip  Y: m_NumberOfStrip
  
  double Ax , Bx , Cx , Dx , Ay , By , Cy , Dy , Az , Bz , Cz , Dz;
  TVector3 A , B , C , D;
  double Theta = 0 , Phi = 0 , R = 0 , beta_u = 0 , beta_v = 0 , beta_w = 0;
  
  bool check_A = false ;
  bool check_C = false ;
  bool check_B = false ;
  bool check_D = false ;
  
  bool check_Theta = false ;
  bool check_Phi   = false ;
  bool check_R     = false ;
  bool check_beta  = false ;
  
  bool ReadingStatus = false ;
  
  
  while (!ConfigFile.eof())
      {
    
    getline(ConfigFile, LineBuffer);
    
    //   If line is a Start Up CharissaCHARISSA bloc, Reading toggle to true
    if (LineBuffer.compare(0, 17, "CharissaTelescope")==0)
        {
      cout << "///" << endl                 ;
      cout << "Telescope found: " << endl   ;
      ReadingStatus = true                ;
      
        }
    
    //   Else don't toggle to Reading Block Status
    else ReadingStatus = false ;
    
    //   Reading Block
    while(ReadingStatus)
        {
      
      ConfigFile >> DataBuffer ;
      //   Comment Line
      if(DataBuffer.compare(0, 1, "%") == 0) {
        ConfigFile.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
        
      }
      
      //   Finding another telescope (safety), toggle out
      else if (DataBuffer=="CharissaTelescope") {
        cout << "WARNING: Another Telescope is find before standard sequence of Token, Error may occured in Telecope definition" << endl ;
        ReadingStatus = false ;
      }
      
      //   Position method
      
      else if (DataBuffer=="X1_Y1=") {
        check_A = true;
        ConfigFile >> DataBuffer ;
        Ax = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Ay = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Az = atof(DataBuffer.c_str()) ;
        
        A = TVector3(Ax, Ay, Az);
        cout << "X1 Y1 corner position : (" << A.X() << ";" << A.Y() << ";" << A.Z() << ")" << endl;
        
      }
      
      
      else if (DataBuffer=="X16_Y1=") {
        check_B = true;
        ConfigFile >> DataBuffer ;
        Bx = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        By = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Bz = atof(DataBuffer.c_str()) ;
        
        B = TVector3(Bx, By, Bz);
        cout << "X16 Y1 corner position : (" << B.X() << ";" << B.Y() << ";" << B.Z() << ")" << endl;
        
      }
      
      
      else if (DataBuffer=="X1_Y16=") {
        check_C = true;
        ConfigFile >> DataBuffer ;
        Cx = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Cy = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Cz = atof(DataBuffer.c_str()) ;
        
        C = TVector3(Cx, Cy, Cz);
        cout << "X1 Y16 corner position : (" << C.X() << ";" << C.Y() << ";" << C.Z() << ")" << endl;
        
      }
      
      else if (DataBuffer=="X16_Y16=") {
        check_D = true;
        ConfigFile >> DataBuffer ;
        Dx = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Dy = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        Dz = atof(DataBuffer.c_str()) ;
        
        D = TVector3(Dx, Dy, Dz);
        cout << "X16 Y16 corner position : (" << D.X() << ";" << D.Y() << ";" << D.Z() << ")" << endl;
        
      }
      
      //   End Position Method
      
      //   Angle method
      else if (DataBuffer=="THETA=") {
        check_Theta = true;
        ConfigFile >> DataBuffer ;
        Theta = atof(DataBuffer.c_str()) ;
        cout << "Theta:  " << Theta << endl;
        
      }
      
      //Angle method
      else if (DataBuffer=="PHI=") {
        check_Phi = true;
        ConfigFile >> DataBuffer ;
        Phi = atof(DataBuffer.c_str()) ;
        cout << "Phi:  " << Phi << endl;
        
      }
      
      //Angle method
      else if (DataBuffer=="R=") {
        check_R = true;
        ConfigFile >> DataBuffer ;
        R = atof(DataBuffer.c_str()) ;
        cout << "R:  " << R << endl;
        
      }
      
      //Angle method
      else if (DataBuffer=="BETA=") {
        check_beta = true;
        ConfigFile >> DataBuffer ;
        beta_u = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        beta_v = atof(DataBuffer.c_str()) ;
        ConfigFile >> DataBuffer ;
        beta_w = atof(DataBuffer.c_str()) ;
        cout << "Beta:  " << beta_u << " " << beta_v << " " << beta_w << endl  ;
        
      }
      
      /////////////////////////////////////////////////
      //   If All necessary information there, toggle out
      if ( (check_A && check_B && check_C && check_D) || (check_Theta && check_Phi && check_R && check_beta)  )
          {
            ReadingStatus = false;
        
            ///Add The previously define telescope
            //With position method
            if ( check_A && check_B && check_C && check_D )
                {
              AddTelescope(  A,
                           B,
                           C,
                           D) ;
                }
        
            //with angle method
            else if ( check_Theta && check_Phi && check_R && check_beta )
                {
              AddTelescope(  Theta,
                           Phi,
                           R,
                           beta_u,
                           beta_v,
                           beta_w);
                }
        
            check_A = false ;
            check_B = false ;
            check_C = false ;
            check_D = false ;
        
            check_Theta = false ;
            check_Phi  = false ;
            check_R    = false ;
            check_beta = false ;
          }
        }
      }
  
  InitializeStandardParameter();
  ReadAnalysisConfig();
  
  cout << endl << "/////////////////////////////" << endl << endl;
  
}
///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::InitSpectra(){  
   m_Spectra = new TCharissaSpectra(m_NumberOfTelescope);
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::FillSpectra(){  
	m_Spectra -> FillRawSpectra(m_EventData);
	m_Spectra -> FillPreTreatedSpectra(m_PreTreatedData);
}
///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::CheckSpectra(){  
  m_Spectra->CheckSpectra();  
}
///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::ClearSpectra(){  
  // To be done
}
///////////////////////////////////////////////////////////////////////////
map< vector<TString> , TH1*> TCharissaPhysics::GetSpectra() {
return m_Spectra->GetMapHisto();
} 
///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::AddParameterToCalibrationManager()
{
  CalibrationManager* Cal = CalibrationManager::getInstance();
  
  for(int i = 0 ; i < m_NumberOfTelescope ; ++i){
    
    for( int j = 0 ; j <  m_NumberOfStrip ; ++j){
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_DE_X"+itoa(j+1)+"_E","CHARISSA_T"+itoa(i+1)+"_DE_X"+itoa(j+1)+"_E")   ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_DE_Y"+itoa(j+1)+"_E","CHARISSA_T"+itoa(i+1)+"_DE_Y"+itoa(j+1)+"_E")   ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_DE_X"+itoa(j+1)+"_T","CHARISSA_T"+itoa(i+1)+"_DE_X"+itoa(j+1)+"_T")   ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_DE_Y"+itoa(j+1)+"_T","CHARISSA_T"+itoa(i+1)+"_DE_Y"+itoa(j+1)+"_T")   ;
      
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_E_X"+itoa(j+1)+"_E","CHARISSA_T"+itoa(i+1)+"_E_X"+itoa(j+1)+"_E")   ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_E_Y"+itoa(j+1)+"_E","CHARISSA_T"+itoa(i+1)+"_E_Y"+itoa(j+1)+"_E")   ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_E_X"+itoa(j+1)+"_T","CHARISSA_T"+itoa(i+1)+"_E_X"+itoa(j+1)+"_T")   ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_E_Y"+itoa(j+1)+"_T","CHARISSA_T"+itoa(i+1)+"_E_Y"+itoa(j+1)+"_T")   ;
     }
    
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_CsI_E","CHARISSA_T"+itoa(i+1)+"_CsI_E")      ;
      Cal->AddParameter("CHARISSA", "T"+itoa(i+1)+"_CsI_T","CHARISSA_T"+itoa(i+1)+"_CsI_T")      ;
    
  }
  
  return;
  
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::InitializeRootInputRaw()
{
  TChain* inputChain = RootInput::getInstance()->GetChain()   ;
  inputChain->SetBranchStatus( "Charissa" , true )               ;
  inputChain->SetBranchStatus( "fCharissa_*" , true )               ;
  inputChain->SetBranchAddress( "Charissa" , &m_EventData )      ;
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::InitializeRootInputPhysics()
{
	TChain* inputChain = RootInput::getInstance()->GetChain();
	inputChain->SetBranchStatus( "CHARISSA" , true );
	inputChain->SetBranchStatus( "EventMultiplicity" , true );
	inputChain->SetBranchStatus( "EventType" , true );
	inputChain->SetBranchStatus( "Layer1_TelescopeNumber" , true );
	inputChain->SetBranchStatus( "Layer1_Si_E" , true );
	inputChain->SetBranchStatus( "Layer1_Si_T" , true );
	inputChain->SetBranchStatus( "Layer1_Si_X" , true );
	inputChain->SetBranchStatus( "Layer1_Si_Y" , true );
	inputChain->SetBranchStatus( "Layer1_Si_EX" , true );
	inputChain->SetBranchStatus( "Layer1_Si_TX" , true );
	inputChain->SetBranchStatus( "Layer1_Si_EY" , true );
	inputChain->SetBranchStatus( "Layer1_Si_TY" , true );
	inputChain->SetBranchStatus( "Layer1_TelescopeNumber_X" , true );
	inputChain->SetBranchStatus( "Layer1_TelescopeNumber_Y" , true );
	inputChain->SetBranchStatus( "Layer2_TelescopeNumber" , true );
	inputChain->SetBranchStatus( "Layer2_Si_E" , true );
	inputChain->SetBranchStatus( "Layer2_Si_T" , true );
	inputChain->SetBranchStatus( "Layer2_Si_X" , true );
	inputChain->SetBranchStatus( "Layer2_Si_Y" , true );
	inputChain->SetBranchStatus( "Layer2_Si_EX" , true );
	inputChain->SetBranchStatus( "Layer2_Si_TX" , true );
	inputChain->SetBranchStatus( "Layer2_Si_EY" , true );
	inputChain->SetBranchStatus( "Layer2_Si_TY" , true );
	inputChain->SetBranchStatus( "Layer2_TelescopeNumber_X" , true );
	inputChain->SetBranchStatus( "Layer2_TelescopeNumber_Y" , true );	
	inputChain->SetBranchStatus( "CsI_E" , true );
	inputChain->SetBranchStatus( "CsI_T" , true );
	inputChain->SetBranchStatus( "CsI_N" , true );
	inputChain->SetBranchStatus( "TotalEnergy" , true );
	inputChain->SetBranchAddress( "CHARISSA" , &m_EventPhysics);
}

///////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::InitializeRootOutput()
{
  TTree* outputTree = RootOutput::getInstance()->GetTree();
  outputTree->Branch( "CHARISSA" , "TCharissaPhysics" , &m_EventPhysics );
}


/////   Specific to CHARISSAArray   ////
/////////////////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::AddTelescope(   TVector3 C_X1_Y1,
                                 TVector3 C_X16_Y1,
                                 TVector3 C_X1_Y16,
                                 TVector3 C_X16_Y16)
{
  // To avoid warning
  C_X16_Y16 *= 1;
  
  m_NumberOfTelescope++;
  
  //   Vector U on Telescope Face (paralelle to Y Strip) (NB: remember that Y strip are allong X axis)
  TVector3 U = C_X16_Y1 - C_X1_Y1 ;
  double Ushift = (U.Mag()-98)/2.;
  U = U.Unit();
  //   Vector V on Telescope Face (parallele to X Strip)
  TVector3 V = C_X1_Y16 - C_X1_Y1 ;
  double Vshift = (V.Mag() -98)/2. ;
  V = V.Unit() ;
  
  //   Position Vector of Strip Center
  TVector3 StripCenter = TVector3(0,0,0);
  //   Position Vector of X=1 Y=1 Strip
  TVector3 Strip_1_1;
  
  //   Geometry Parameter
  double Face = 98; //mm
  double NumberOfStrip =  m_NumberOfStrip;
  double StripPitch = Face/NumberOfStrip ; //mm
                                           //   Buffer object to fill Position Array
  vector<double> lineX ; vector<double> lineY ; vector<double> lineZ ;
  
  vector< vector< double > >   OneTelescopeStripPositionX   ;
  vector< vector< double > >   OneTelescopeStripPositionY   ;
  vector< vector< double > >   OneTelescopeStripPositionZ   ;
  
  //   Moving StripCenter to 1.1 corner:
  Strip_1_1 = C_X1_Y1 + (U+V) * (StripPitch/2.)    ;
  Strip_1_1+= U*Ushift+V*Vshift ;
  
  for( int i = 0 ; i <  m_NumberOfStrip ; ++i )
      {
    lineX.clear()   ;
    lineY.clear()   ;
    lineZ.clear()   ;
    
    for( int j = 0 ; j <  m_NumberOfStrip ; ++j )
        {
      StripCenter  = Strip_1_1 + StripPitch*( i*U + j*V  );
      lineX.push_back( StripCenter.X() );
      lineY.push_back( StripCenter.Y() );
      lineZ.push_back( StripCenter.Z() );
        }
    
    OneTelescopeStripPositionX.push_back(lineX);
    OneTelescopeStripPositionY.push_back(lineY);
    OneTelescopeStripPositionZ.push_back(lineZ);
    
      }
  m_StripPositionX.push_back( OneTelescopeStripPositionX ) ;
  m_StripPositionY.push_back( OneTelescopeStripPositionY ) ;
  m_StripPositionZ.push_back( OneTelescopeStripPositionZ ) ;
  
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::InitializeStandardParameter()
{
  //   Enable all channel
  vector< bool > ChannelStatus;
  m_XChannelStatus.clear()    ;
  m_YChannelStatus.clear()    ;
  m_CsIChannelStatus.clear()  ;
  
  ChannelStatus.resize(m_NumberOfStrip,true);
  for(int i = 0 ; i < m_NumberOfTelescope ; ++i)
      {
    m_XChannelStatus[i] = ChannelStatus;
    m_YChannelStatus[i] = ChannelStatus;
      }
  
  ChannelStatus.resize(m_NumberOfStrip,true);
  for(int i = 0 ; i < m_NumberOfTelescope ; ++i)
      {
    m_CsIChannelStatus[i]  = ChannelStatus;
      }
  
  
  m_MaximumStripMultiplicityAllowed = m_NumberOfTelescope   ;
  
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void TCharissaPhysics::AddTelescope(   double theta,
                                 double phi,
                                 double distance,
                                 double beta_u,
                                 double beta_v,
                                 double beta_w)
{
  

  m_NumberOfTelescope++;
  
  double Pi = 3.141592654 ;
  
  // convert from degree to radian:
  theta = theta * Pi/180. ;
  phi   = phi   * Pi/180. ;
  
  //Vector U on Telescope Face (paralelle to Y Strip) (NB: remember that Y strip are allong X axis)
  TVector3 U ;
  //Vector V on Telescope Face (parallele to X Strip)
  TVector3 V ;
  //Vector W normal to Telescope Face (pointing CsI)
  TVector3 W ;
  //Vector position of Telescope Face center
  TVector3 C ;
  
  C = TVector3 ( distance * sin(theta) * cos(phi) ,
                distance * sin(theta) * sin(phi) ,
                distance * cos(theta) );
  
  TVector3 P = TVector3( cos(theta ) * cos(phi) ,
                        cos(theta ) * sin(phi) ,
                        -sin(theta) );
  
  W = C.Unit() ;
  U = W .Cross ( P ) ;
  V = W .Cross ( U );
  
  U = U.Unit();
  V = V.Unit();
  
  U.Rotate( beta_u * Pi/180. , U ) ;
  V.Rotate( beta_u * Pi/180. , U ) ;
  
  U.Rotate( beta_v * Pi/180. , V ) ;
  V.Rotate( beta_v * Pi/180. , V ) ;
  
  U.Rotate( beta_w * Pi/180. , W ) ;
  V.Rotate( beta_w * Pi/180. , W ) ;
  
  double Face = 98                     ; //mm
  double NumberOfStrip =  m_NumberOfStrip             ;
  double StripPitch = Face/NumberOfStrip   ; //mm
  
  vector<double> lineX ; vector<double> lineY ; vector<double> lineZ ;
  
  vector< vector< double > >   OneTelescopeStripPositionX   ;
  vector< vector< double > >   OneTelescopeStripPositionY   ;
  vector< vector< double > >   OneTelescopeStripPositionZ   ;
  
  double X , Y , Z  ;
  
  //Moving C to the 1.1 corner:
  C.SetX( C.X() - ( Face/2 - StripPitch/2 ) * ( V.X() + U.X() ) )  ;
  C.SetY( C.Y() - ( Face/2 - StripPitch/2 ) * ( V.Y() + U.Y() ) )  ;
  C.SetZ( C.Z() - ( Face/2 - StripPitch/2 ) * ( V.Z() + U.Z() ) )  ;
  
  for( int i = 0 ; i <  m_NumberOfStrip ; ++i )
      {
    
    lineX.clear()   ;
    lineY.clear()   ;
    lineZ.clear()   ;
    
    for( int j = 0 ; j <  m_NumberOfStrip ; ++j )
        {
      X = C.X() + StripPitch * ( U.X()*i + V.X()*j )   ;
      Y = C.Y() + StripPitch * ( U.Y()*i + V.Y()*j )   ;
      Z = C.Z() + StripPitch * ( U.Z()*i + V.Z()*j )   ;
      
      lineX.push_back(X)   ;
      lineY.push_back(Y)   ;
      lineZ.push_back(Z)   ;
      
        }
    
    OneTelescopeStripPositionX.push_back(lineX)   ;
    OneTelescopeStripPositionY.push_back(lineY)   ;
    OneTelescopeStripPositionZ.push_back(lineZ)   ;
    
      }
  m_StripPositionX.push_back( OneTelescopeStripPositionX ) ;
  m_StripPositionY.push_back( OneTelescopeStripPositionY ) ;
  m_StripPositionZ.push_back( OneTelescopeStripPositionZ ) ;
}


//////////////////////////////////////////////////////////////////////////////////////////////
TVector3 TCharissaPhysics::GetPositionOfInteraction(const int i) const
{
  TVector3 Position = TVector3 (   GetStripPositionX( Layer1_TelescopeNumber[i] , Layer1_Si_X[i] , Layer1_Si_Y[i] )    ,
                                GetStripPositionY( Layer1_TelescopeNumber[i] , Layer1_Si_X[i] , Layer1_Si_Y[i] )      ,
                                GetStripPositionZ( Layer1_TelescopeNumber[i] , Layer1_Si_X[i] , Layer1_Si_Y[i] )      ) ;
  
  return(Position) ;
  
}

TVector3 TCharissaPhysics::GetTelescopeNormal( const int i) const
{
  TVector3 U =    TVector3 ( GetStripPositionX( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip , 1 ) ,
                            GetStripPositionY( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip , 1 ) ,
                            GetStripPositionZ( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip , 1 ) )
  
  -TVector3 ( GetStripPositionX( Layer1_TelescopeNumber[i] , 1 , 1 ) ,
             GetStripPositionY( Layer1_TelescopeNumber[i] , 1 , 1 ) ,
             GetStripPositionZ( Layer1_TelescopeNumber[i] , 1 , 1 ) );
  
  TVector3 V =    TVector3 ( GetStripPositionX( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip ,  m_NumberOfStrip ) ,
                            GetStripPositionY( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip ,  m_NumberOfStrip ) ,
                            GetStripPositionZ( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip ,  m_NumberOfStrip ) )
  
  -TVector3 ( GetStripPositionX( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip , 1 ) ,
             GetStripPositionY( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip , 1 ) ,
             GetStripPositionZ( Layer1_TelescopeNumber[i] ,  m_NumberOfStrip , 1 ) );
  
  TVector3 Normal = U.Cross(V);
  
  return(Normal.Unit()) ;
}

///////////////////////////////////////////////////////////////////////////
namespace CHARISSA_LOCAL
{
  //   tranform an integer to a string
  string itoa(int value)
  {
char buffer [33];
sprintf(buffer,"%d",value);
return buffer;
  }
  
  //   E
  //   X
  double fDE_X_E(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer1StripXEDetectorNbr(i) ) + "_DE_X" + itoa( m_EventData->GetCharissaLayer1StripXEStripNbr(i) ) + "_E",
                                                           m_EventData->GetCharissaLayer1StripXEEnergy(i) );
  }
  
  double fDE_X_T(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer1StripXTDetectorNbr(i) ) + "_DE_X" + itoa( m_EventData->GetCharissaLayer1StripXTStripNbr(i) ) +"_T",
                                                           m_EventData->GetCharissaLayer1StripXTTime(i) );
  }
  
  //   Y
  double fDE_Y_E(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer1StripYEDetectorNbr(i) ) + "_DE_Y" + itoa( m_EventData->GetCharissaLayer1StripYEStripNbr(i) ) +"_E",
                                                           m_EventData->GetCharissaLayer1StripYEEnergy(i) );
  }
  
  double fDE_Y_T(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer1StripYTDetectorNbr(i) ) + "_DE_Y" + itoa( m_EventData->GetCharissaLayer1StripYTStripNbr(i) ) +"_T",
                                                           m_EventData->GetCharissaLayer1StripYTTime(i) );
  }
  
  //   E
  //   X
  double fE_X_E(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer2StripXEDetectorNbr(i) ) + "_E_X" + itoa( m_EventData->GetCharissaLayer2StripXEStripNbr(i) ) + "_E",
                                                           m_EventData->GetCharissaLayer2StripXEEnergy(i) );
  }
  
  double fE_X_T(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer2StripXTDetectorNbr(i) ) + "_E_X" + itoa( m_EventData->GetCharissaLayer2StripXTStripNbr(i) ) +"_T",
                                                           m_EventData->GetCharissaLayer2StripXTTime(i) );
  }
  
  //   Y
  double fE_Y_E(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer2StripYEDetectorNbr(i) ) + "_E_Y" + itoa( m_EventData->GetCharissaLayer2StripYEStripNbr(i) ) +"_E",
                                                           m_EventData->GetCharissaLayer2StripYEEnergy(i) );
  }
  
  double fE_Y_T(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaLayer2StripYTDetectorNbr(i) ) + "_E_Y" + itoa( m_EventData->GetCharissaLayer2StripYTStripNbr(i) ) +"_T",
                                                           m_EventData->GetCharissaLayer2StripYTTime(i) );
  }
  

  //   CsI
  double fCsI_E(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaCsIEDetectorNbr(i) ) + "_CsI" + itoa( m_EventData->GetCharissaCsIECristalNbr(i) ) +"_E",
                                                           m_EventData->GetCharissaCsIEEnergy(i) );
  }
  
  double fCsI_T(const TCharissaData* m_EventData , const int i)
  {
return CalibrationManager::getInstance()->ApplyCalibration(   "CHARISSA/T" + itoa( m_EventData->GetCharissaCsITDetectorNbr(i) ) + "_CsI" + itoa( m_EventData->GetCharissaCsITCristalNbr(i) ) +"_T",
                                                           m_EventData->GetCharissaCsITTime(i) );
  }
  
}

	