#ifndef _IDIPROV_
#define _IDIPROV_
/*******************************************************************************
* FILE NAME: idiprov.hpp                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDragItemProvider - Class used to provide drag items to a source handler *
*                         at commencement of a direct manipulation operation.  *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   S:/ibmclass/idrag/vcs/idiprov.hpv  $
//
//   Rev 1.1   30 Apr 1993 11:45:14   HAGGAR
//No change.
//
//   Rev 1.0   22 Apr 1993 10:40:58   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IVBASE_
  #include <ivbase.hpp>
#endif

/* Forward declarations */
class IDMSrcOperationHandle;

class IDragItemProvider : public IVBase {
typedef IVBase
  Inherited;
/*******************************************************************************
  Objects of this class have one purpose: they provide an IDMSourceHandler
  object with the items to be dragged when a direct manipulation operation
  begins.  A pointer to an object of this class must be provided when an
  IDMSourceHandler is constructed.

  When the source handler detects that a direct manipulation operation is
  being initiated from one of its windows, it will call the provideDragItems
  function of this class, passing the IDMSourceOperation object (via a handle
  to it).  The IDragItemProvider simply creates IDMSourceItem objects to
  represent the items to be dragged from the source window and adds these to
  the IDMSourceOperation object.

  This class is an abstract base class.  Derived classes must implement the
  provideDragItems function in an application (or control) specific manner.
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
------------------------------------------------------------------------------*/
  IDragItemProvider ( );

virtual
  ~IDragItemProvider ( );

/*--------------------------- Drag Item Provision ------------------------------
  provideDragItems - Called to give provider opportunity to attach new
                     IDMSourceItems to the argument IDMSourceOperation object.
                     Returns true if items were provided, false otherwise.
------------------------------------------------------------------------------*/
virtual Boolean
  provideDragItems ( const IDMSrcOperationHandle &dragOpHandle ) = 0;

protected:

private: /*------------------------ PRIVATE ----------------------------------*/
}; // class IDragItemProvider

#endif //_IDIPROV_
