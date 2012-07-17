//
// File generated by rootcint at Tue Jul 17 16:41:36 2012

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME TVamosPlasticDataDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "TVamosPlasticDataDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void TVamosPlasticData_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_TVamosPlasticData(void *p = 0);
   static void *newArray_TVamosPlasticData(Long_t size, void *p);
   static void delete_TVamosPlasticData(void *p);
   static void deleteArray_TVamosPlasticData(void *p);
   static void destruct_TVamosPlasticData(void *p);
   static void streamer_TVamosPlasticData(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TVamosPlasticData*)
   {
      ::TVamosPlasticData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TVamosPlasticData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TVamosPlasticData", ::TVamosPlasticData::Class_Version(), "./TVamosPlasticData.h", 31,
                  typeid(::TVamosPlasticData), DefineBehavior(ptr, ptr),
                  &::TVamosPlasticData::Dictionary, isa_proxy, 0,
                  sizeof(::TVamosPlasticData) );
      instance.SetNew(&new_TVamosPlasticData);
      instance.SetNewArray(&newArray_TVamosPlasticData);
      instance.SetDelete(&delete_TVamosPlasticData);
      instance.SetDeleteArray(&deleteArray_TVamosPlasticData);
      instance.SetDestructor(&destruct_TVamosPlasticData);
      instance.SetStreamerFunc(&streamer_TVamosPlasticData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TVamosPlasticData*)
   {
      return GenerateInitInstanceLocal((::TVamosPlasticData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TVamosPlasticData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *TVamosPlasticData::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *TVamosPlasticData::Class_Name()
{
   return "TVamosPlasticData";
}

//______________________________________________________________________________
const char *TVamosPlasticData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TVamosPlasticData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TVamosPlasticData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TVamosPlasticData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void TVamosPlasticData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TVamosPlasticData*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *TVamosPlasticData::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TVamosPlasticData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void TVamosPlasticData::Streamer(TBuffer &R__b)
{
   // Stream an object of class TVamosPlasticData.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fVamos_Plastic_Energy_Left;
      R__b >> fVamos_Plastic_Energy_Right;
      R__b >> fVamos_Plastic_Time_LeftRight;
      R__b.CheckByteCount(R__s, R__c, TVamosPlasticData::IsA());
   } else {
      R__c = R__b.WriteVersion(TVamosPlasticData::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fVamos_Plastic_Energy_Left;
      R__b << fVamos_Plastic_Energy_Right;
      R__b << fVamos_Plastic_Time_LeftRight;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

//______________________________________________________________________________
void TVamosPlasticData::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class TVamosPlasticData.
      TClass *R__cl = ::TVamosPlasticData::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fVamos_Plastic_Energy_Left", &fVamos_Plastic_Energy_Left);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fVamos_Plastic_Energy_Right", &fVamos_Plastic_Energy_Right);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "fVamos_Plastic_Time_LeftRight", &fVamos_Plastic_Time_LeftRight);
      TObject::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TVamosPlasticData(void *p) {
      return  p ? new(p) ::TVamosPlasticData : new ::TVamosPlasticData;
   }
   static void *newArray_TVamosPlasticData(Long_t nElements, void *p) {
      return p ? new(p) ::TVamosPlasticData[nElements] : new ::TVamosPlasticData[nElements];
   }
   // Wrapper around operator delete
   static void delete_TVamosPlasticData(void *p) {
      delete ((::TVamosPlasticData*)p);
   }
   static void deleteArray_TVamosPlasticData(void *p) {
      delete [] ((::TVamosPlasticData*)p);
   }
   static void destruct_TVamosPlasticData(void *p) {
      typedef ::TVamosPlasticData current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TVamosPlasticData(TBuffer &buf, void *obj) {
      ((::TVamosPlasticData*)obj)->::TVamosPlasticData::Streamer(buf);
   }
} // end of namespace ROOT for class ::TVamosPlasticData

/********************************************************
* TVamosPlasticDataDict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableTVamosPlasticDataDict();

extern "C" void G__set_cpp_environmentTVamosPlasticDataDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("TVamosPlasticData.h");
  G__cpp_reset_tagtableTVamosPlasticDataDict();
}
#include <new>
extern "C" int G__cpp_dllrevTVamosPlasticDataDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* TVamosPlasticData */
static int G__TVamosPlasticDataDict_162_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TVamosPlasticData* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TVamosPlasticData[n];
     } else {
       p = new((void*) gvp) TVamosPlasticData[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TVamosPlasticData;
     } else {
       p = new((void*) gvp) TVamosPlasticData;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TVamosPlasticData*) G__getstructoffset())->Clear();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 114, (long) ((TVamosPlasticData*) G__getstructoffset())->GetEnergyLeft());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 114, (long) ((TVamosPlasticData*) G__getstructoffset())->GetEnergyRight());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 114, (long) ((TVamosPlasticData*) G__getstructoffset())->GetTimeLeftRight());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TVamosPlasticData*) G__getstructoffset())->SetEnergyLeft((UShort_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TVamosPlasticData*) G__getstructoffset())->SetEnergyRight((UShort_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TVamosPlasticData*) G__getstructoffset())->SetTimeLeftRight((UShort_t) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) TVamosPlasticData::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TVamosPlasticData::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) TVamosPlasticData::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      TVamosPlasticData::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TVamosPlasticData*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TVamosPlasticData::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TVamosPlasticData::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TVamosPlasticData::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TVamosPlasticDataDict_162_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TVamosPlasticData::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__TVamosPlasticDataDict_162_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   TVamosPlasticData* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new TVamosPlasticData(*(TVamosPlasticData*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef TVamosPlasticData G__TTVamosPlasticData;
static int G__TVamosPlasticDataDict_162_0_24(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 1
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (TVamosPlasticData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((TVamosPlasticData*) (soff+(sizeof(TVamosPlasticData)*i)))->~G__TTVamosPlasticData();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (TVamosPlasticData*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((TVamosPlasticData*) (soff))->~G__TTVamosPlasticData();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__TVamosPlasticDataDict_162_0_25(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TVamosPlasticData* dest = (TVamosPlasticData*) G__getstructoffset();
   *dest = *(TVamosPlasticData*) libp->para[0].ref;
   const TVamosPlasticData& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* TVamosPlasticData */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncTVamosPlasticDataDict {
 public:
  G__Sizep2memfuncTVamosPlasticDataDict(): p(&G__Sizep2memfuncTVamosPlasticDataDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncTVamosPlasticDataDict::*p)();
};

size_t G__get_sizep2memfuncTVamosPlasticDataDict()
{
  G__Sizep2memfuncTVamosPlasticDataDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceTVamosPlasticDataDict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData))) {
     TVamosPlasticData *G__Lderived;
     G__Lderived=(TVamosPlasticData*)0x1000;
     {
       TObject *G__Lpbase=(TObject*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData),G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TObject),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableTVamosPlasticDataDict() {

   /* Setting up typedef entry */
   G__search_typename2("UShort_t",114,-1,0,-1);
   G__setnewtype(-1,"Unsigned Short integer 2 bytes (unsigned short)",0);
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* TVamosPlasticData */
static void G__setup_memvarTVamosPlasticData(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData));
   { TVamosPlasticData *p; p=(TVamosPlasticData*)0x1000; if (p) { }
   G__memvar_setup((void*)0,114,0,0,-1,G__defined_typename("UShort_t"),-1,4,"fVamos_Plastic_Energy_Left=",0,(char*)NULL);
   G__memvar_setup((void*)0,114,0,0,-1,G__defined_typename("UShort_t"),-1,4,"fVamos_Plastic_Energy_Right=",0,(char*)NULL);
   G__memvar_setup((void*)0,114,0,0,-1,G__defined_typename("UShort_t"),-1,4,"fVamos_Plastic_Time_LeftRight=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarTVamosPlasticDataDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncTVamosPlasticData(void) {
   /* TVamosPlasticData */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData));
   G__memfunc_setup("TVamosPlasticData",1700,G__TVamosPlasticDataDict_162_0_1, 105, G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,G__TVamosPlasticDataDict_162_0_2, 121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Clear",487,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "C - 'Option_t' 10 - -", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Dump",406,(G__InterfaceMethod) NULL,121, -1, -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("GetEnergyLeft",1301,G__TVamosPlasticDataDict_162_0_5, 114, -1, G__defined_typename("UShort_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetEnergyRight",1416,G__TVamosPlasticDataDict_162_0_6, 114, -1, G__defined_typename("UShort_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTimeLeftRight",1592,G__TVamosPlasticDataDict_162_0_7, 114, -1, G__defined_typename("UShort_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetEnergyLeft",1313,G__TVamosPlasticDataDict_162_0_8, 121, -1, -1, 0, 1, 1, 1, 0, "r - 'UShort_t' 0 - E", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetEnergyRight",1428,G__TVamosPlasticDataDict_162_0_9, 121, -1, -1, 0, 1, 1, 1, 0, "r - 'UShort_t' 0 - E", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetTimeLeftRight",1604,G__TVamosPlasticDataDict_162_0_10, 121, -1, -1, 0, 1, 1, 1, 0, "r - 'UShort_t' 0 - E", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Class",502,G__TVamosPlasticDataDict_162_0_11, 85, G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&TVamosPlasticData::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__TVamosPlasticDataDict_162_0_12, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TVamosPlasticData::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__TVamosPlasticDataDict_162_0_13, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&TVamosPlasticData::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__TVamosPlasticDataDict_162_0_14, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&TVamosPlasticData::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - insp", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__TVamosPlasticDataDict_162_0_18, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__TVamosPlasticDataDict_162_0_19, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TVamosPlasticData::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__TVamosPlasticDataDict_162_0_20, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TVamosPlasticData::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__TVamosPlasticDataDict_162_0_21, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TVamosPlasticData::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__TVamosPlasticDataDict_162_0_22, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TVamosPlasticData::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("TVamosPlasticData", 1700, G__TVamosPlasticDataDict_162_0_23, (int) ('i'), G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData), -1, 0, 1, 1, 1, 0, "u 'TVamosPlasticData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~TVamosPlasticData", 1826, G__TVamosPlasticDataDict_162_0_24, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__TVamosPlasticDataDict_162_0_25, (int) ('u'), G__get_linked_tagnum(&G__TVamosPlasticDataDictLN_TVamosPlasticData), -1, 1, 1, 1, 1, 0, "u 'TVamosPlasticData' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncTVamosPlasticDataDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalTVamosPlasticDataDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcTVamosPlasticDataDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__TVamosPlasticDataDictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_TObject = { "TObject" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TVamosPlasticDataDictLN_TVamosPlasticData = { "TVamosPlasticData" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableTVamosPlasticDataDict() {
  G__TVamosPlasticDataDictLN_TClass.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_TBuffer.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_TMemberInspector.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_TObject.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TVamosPlasticDataDictLN_TVamosPlasticData.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableTVamosPlasticDataDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_TClass);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_TObject);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__TVamosPlasticDataDictLN_TVamosPlasticData),sizeof(TVamosPlasticData),-1,29952,"VamosPlasticData structure",G__setup_memvarTVamosPlasticData,G__setup_memfuncTVamosPlasticData);
}
extern "C" void G__cpp_setupTVamosPlasticDataDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupTVamosPlasticDataDict()");
  G__set_cpp_environmentTVamosPlasticDataDict();
  G__cpp_setup_tagtableTVamosPlasticDataDict();

  G__cpp_setup_inheritanceTVamosPlasticDataDict();

  G__cpp_setup_typetableTVamosPlasticDataDict();

  G__cpp_setup_memvarTVamosPlasticDataDict();

  G__cpp_setup_memfuncTVamosPlasticDataDict();
  G__cpp_setup_globalTVamosPlasticDataDict();
  G__cpp_setup_funcTVamosPlasticDataDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncTVamosPlasticDataDict();
  return;
}
class G__cpp_setup_initTVamosPlasticDataDict {
  public:
    G__cpp_setup_initTVamosPlasticDataDict() { G__add_setup_func("TVamosPlasticDataDict",(G__incsetup)(&G__cpp_setupTVamosPlasticDataDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initTVamosPlasticDataDict() { G__remove_setup_func("TVamosPlasticDataDict"); }
};
G__cpp_setup_initTVamosPlasticDataDict G__cpp_setup_initializerTVamosPlasticDataDict;

