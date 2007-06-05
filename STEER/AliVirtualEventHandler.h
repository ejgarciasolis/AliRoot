#ifndef ALIVIRTUALEVENTHANDLER_H
#define ALIVIRTUALEVENTHANDLER_H
/* Copyright(c) 1998-2007, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */

//-------------------------------------------------------------------------
//     Event Handler base class
//     Author: Andreas Morsch, CERN
//-------------------------------------------------------------------------

#include <TNamed.h>


class AliVirtualEventHandler : public TNamed {

 public:
    AliVirtualEventHandler();
    AliVirtualEventHandler(const char* name, const char* title);
    virtual ~AliVirtualEventHandler();
    virtual Bool_t       InitIO()             = 0;
    virtual Bool_t       Fill()               = 0;
    virtual Bool_t       Terminate()          = 0;
    virtual Bool_t       TerminateIO()        = 0;
 private :
  ClassDef(AliVirtualEventHandler, 1);
};

#endif
