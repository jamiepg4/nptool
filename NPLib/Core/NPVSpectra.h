#ifndef VSPECTRA_H
#define VSPECTRA_H
/*****************************************************************************
 * Copyright (C) 2009-2016    this file is part of the NPTool Project        *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: A. Matta       contact address: matta@lpccaen.in2p3.fr   *
 *                                                                           *
 * Creation Date  : may 2014                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  Virtual class for the TDetectorSpectra classes                           *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/

// ROOT headers
#include "TObject.h"
#include "TH1.h"
#include "TCanvas.h"
// C++ STL headers
#include <map>
#include <vector>
#include <string>
using namespace std;

class VSpectra {
  public:
    // constructor and destructor
    VSpectra();
    virtual ~VSpectra(){};

  public:
    // Instantiate and register histo to maps
    TH1* AddHisto1D(string name, string title, Int_t nbinsx, Double_t xlow, Double_t xup, string family);
    TH1* AddHisto2D(string name, string title, Int_t nbinsx, Double_t xlow, Double_t xup, 
        Int_t nbinsy, Double_t ylow, Double_t yup, string family);

  public:
    // Initialization methods
    virtual void InitRawSpectra()        {};
    virtual void InitPreTreatedSpectra() {};
    virtual void InitPhysicsSpectra()    {};

  public:
    // Filling methods
    virtual void FillRawSpectra(void*) {};
    virtual void FillPreTreatedSpectra(void*) {};
    virtual void FillPhysicsSpectra(void*) {}; 
    virtual void CheckSpectra(){};

  public:
    // get map histo which will be used for GSpectra in GUser
    map< string, TH1* > GetMapHisto() const {return fMapHisto;}
    TH1* GetSpectra(const string& family, const string& name);    
    TH1* GetSpectra(const string& FamilyAndName);    
    // TEMP FIX
//    TH1* GetHisto(const string& family, const string& name){return GetSpectra(family,name);};    
//    TH1* GetHisto(const string& FamilyAndName){return GetSpectra(FamilyAndName);};    

    void FillSpectra(const string& family, const string& name, double val);
    void FillSpectra(const string& family, const string& name, double x, double y);
    void FillSpectra(const string& familyAndname, double val);
    void FillSpectra(const string& familyAndname, double x, double y);


    void WriteSpectra(string filename = "VOID");      
     
  protected:
    // map holding histo pointers and their family names
    map< string, TH1* > fMapHisto;
    
  private: // Name of the Detector
   string m_name;

  public:
   inline void SetName(string name) {m_name=name;}
   inline string GetName() {return m_name;}
};

#endif
