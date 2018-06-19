#ifndef _IDMTGTOP_
#define _IDMTGTOP_
/*******************************************************************************
* FILE NAME: idmtgtop.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDMTargetOperation    - Direct manipulation "Target" operation class.    *
*     IDMTgtOperationHandle - "Handle" for IDMTgtOperation object to maintain  *
*                             references to it.                                *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   M:/ibmclass/idrag/vcs/idmtgtop.hpv  $
//
//   Rev 1.3   03 May 1993 16:14:02   unknown
//Remove dead function
//
//   Rev 1.2   03 May 1993 16:06:08   unknown
//Latest changes per IC_UM_DRAGOVER
//
//   Rev 1.1   30 Apr 1993 11:45:48   HAGGAR
//
//   Rev 1.0   22 Apr 1993 10:41:18   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IHANDLE_
  #include <ihandle.hpp>
#endif

#ifndef _IREFCNT_
  #include <irefcnt.hpp>
#endif

/* Forward Declarations */
class _DRAGINFO;
class IDMTgtItemHandle;
class IDMTargetItem;
class IDMTgtOperationHandle;

class IDMTargetOperation : public IDMOperation {
typedef IDMOperation
  Inherited;
/*******************************************************************************
* This is the direct manipulation target drag operation class.  Objects of     *
* this class provide information about target direct manipulation operations.  *
*                                                                              *
* Access to this information is usually gained in one of the following ways:   *
*   o Via an associated IDMTargetItem object's dragOperation() function.       *
*   o Via an associated direct manipulation event's dragOperation() function.  *
*                                                                              *
* Objects of this class possess the following attributes:                      *
*   o Information about the target direct manipulation operation as a whole:   *
*       - number of associated drag items (ie. IDMTargetItems).                *
*       - pointer to the collection of IDMTargetItems.                         *
*   o A collection of IDMTargetItem objects, one for each item being "dragged" *
*     on this operation.                                                       *
*                                                                              *
* Instances of this class are not intended to be created by application        *
* programmers.  Generally, they are created only by the direct manipulation    *
* event classes requiring this information.  Typically, access is via an       *
* IDMTgtOperationHandle object (see below).                                    *
*******************************************************************************/
public:
typedef ISet<IDMTgtItemHandle> IDMTargetItemSet;

/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o by providing a pointer to a _DRAGINFO structure.                         |
------------------------------------------------------------------------------*/
  IDMTargetOperation ( _DRAGINFO *pDragInfo );

  ~IDMTargetOperation ( );

/*-------------------------------- Drag Items ----------------------------------
| The following functions provide means of accessing the IDMTargetItem objects |
| involved in the direct manipulation operation described by instances of      |
| this class:                                                                  |
|   numberOfItems - Returns the number of target drag items.                   |
|   item          - Returns the drag item with given index.                    |
|   addItem       - Associates another drag item with this operation.          |
------------------------------------------------------------------------------*/
unsigned
  numberOfItems ( );

IDMTgtItemHandle
  item ( unsigned index );

IDMTargetOperation
  &addItem     ( const IDMTgtItemHandle newItem );

/*------------------------------ Implementation --------------------------------
| These functions provide various utility services used to implement this      |
| class:                                                                       |
|   instanceFor         - Returns IDMTargetOperation object for a given        |
|                         _DRAGINFO structure.                                 |
|   targetOperation     - Returns IDMTargetOperation object handle that was    |
|                         created during the target enter event.               |
|   setTargetOperation  - Set IDMTargetOperation object handle during the      |
|                         target enter event.                                  |
------------------------------------------------------------------------------*/
static IDMTgtOperationHandle
  instanceFor           ( _DRAGINFO *pDragInfo );

static IDMTgtOperationHandle
  targetOperation       ( );

static void //IDMTargetOperation
 setTargetOperation    ( IDMTgtOperationHandle targetOp );

/*------------------------------ Implementation --------------------------------
| These functions provide various utility services used to implement this      |
| class:                                                                       |
|   itemsSetCl    - Returns a pointer to the collection of IDMTargetItems.     |
|   setItems      - Sets the pointer to the collection of IDMTargetItems.      |
|   itemsRC       - Returns a pointer to the items return code (RC) array.     |
|   setItemsRC    - Sets the pointer to the items return code (RC) array.      |
|                                                                              |
|   MAB - temporarily move to public                                           |
------------------------------------------------------------------------------*/
IDMTargetItemSet
 *itemsSetCl    ( );

IDMTargetOperation
 &setItems      ( IDMTargetItemSet *pIDMTargetItemSet );

unsigned int
 *itemsRC       ( ) const;

IDMTargetOperation
 &setItemsRC    ( unsigned int *returnCodes );

protected:
private: /*------------------------ PRIVATE ----------------------------------*/

IDMTargetItemSet
  *pDMTgtItemSetCl;

static IDMTgtOperationHandle
  pDMTgtOpHandle;

}; //class IDMTargetOperation

class IDMTgtOperationHandle : public IReference< IDMTargetOperation > {
/*******************************************************************************
* Objects of this class provide access to IDMTargetOperation objects           *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMTargetOperation object to ensure that it is not deleted *
* until the drag operation is completed.                                       *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMTargetOperation object.                         *
*                                                                              *
* Example:                                                                     *
*   // Event providing access to the drag information...                       *
*   IBeginDragEvent                                                            *
*    &event;                                                                   *
*                                                                              *
*   // Get drag information handle from event...                               *
*   IDMTgtOperationHandle                                                      *
*     tgtinfo = event.dragOperation();                                         *
*                                                                              *
*   // Process items (using info as a "pointer to IDMTargetOperation")...      *
*   for( int i = 0; i < tgtinfo->numberOfItems(); i++ )                        *
*     {                                                                        *
*     // Process drag items.                                                   *
*     }                                                                        *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMTargetOperation >.                                            *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o by providing a pointer to this handle class.                             |
------------------------------------------------------------------------------*/
  IDMTgtOperationHandle (IDMTargetOperation *pIDMTargetOp) :
    IReference< IDMTargetOperation > (pIDMTargetOp) { }

  ~IDMTgtOperationHandle ( ) { }

}; //IDMTgtOperationHandle

#endif //_IDMTGTOP_
