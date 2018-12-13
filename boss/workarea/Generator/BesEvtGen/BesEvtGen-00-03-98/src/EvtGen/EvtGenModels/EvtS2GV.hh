//--------------------------------------------------------------------------
//
// Environment:
//      This software is part of models developed at BES collaboration
//      based on the EvtGen framework.  If you use all or part
//      of it, please give an appropriate acknowledgement.
//
// Copyright Information: See EvtGen/BesCopyright
//      Copyright (A) 2006      Ping Rong-Gang @IHEP
//
// Module:  EvtS2GV.cc
//
// Description: Routine to decay chi_c1-> gamma J/psi  using
//      helicity amplitude, assuming E1 dominance.  
// Modification history:
//
//    Ping R.-G.       December, 2006       Module created
//
//------------------------------------------------------------------------

#ifndef EVTS2GV_HH
#define EVTS2GV_HH

#include "EvtGenBase/EvtDecayAmp.hh"

class EvtParticle;

class EvtS2GV:public  EvtDecayAmp  {

public:

  EvtS2GV() {}
  virtual ~EvtS2GV();

  void getName(std::string& name);
  EvtDecayBase* clone();

  void decay(EvtParticle *p); 
  void init();
  void initProbMax();

};

#endif

