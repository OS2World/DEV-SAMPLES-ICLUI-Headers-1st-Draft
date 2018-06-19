#ifndef _IDMHNDLR_
#define _IDMHNDLR_
/*******************************************************************************
* FILE NAME: idmhndlr.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDMHandler - Base direct manipulation handler class.                     *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   S:/ibmclass/idrag/vcs/idmhndlr.hpv  $
//
//   Rev 1.1   30 Apr 1993 11:45:26   HAGGAR
//No change.
//
//   Rev 1.0   22 Apr 1993 10:41:04   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IHANDLER_
  #include <ihandler.hpp>
#endif

template < class T > class ISequence;
class IRenderer;

class IDMHandler : public IHandler {
typedef IHandler
  Inherited;
/*******************************************************************************
  This class is the common base for the direct manipulation source and
  target window handler classes IDMSourceHandler and IDMTargetHandler.
*******************************************************************************/
protected:
private: /*------------------------ PRIVATE ----------------------------------*/
}; // class IDMHandler

#ifndef I_NO_INLINES
//#include <idmhndlr.inl>
#endif

#endif // _IDMHNDLR_
