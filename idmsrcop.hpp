#ifndef _IDMSRCOP_
#define _IDMSRCOP_
/*******************************************************************************
* FILE NAME: idmsrcop.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDMSourceOperation    - Direct manipulation "Source" operation class.    *
*     IDMSrcOperationHandle - "Handle" for the IDMSrcOperation object to       *
*                             maintain references to it.                       *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   S:/ibmclass/idrag/vcs/idmsrcop.hpv  $
//
//   Rev 1.1   30 Apr 1993 11:45:44   HAGGAR
//
//   Rev 1.0   22 Apr 1993 10:41:14   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IHANDLE_
  #include <ihandle.hpp>
#endif

#ifndef _IREFCNT_
  #include <irefcnt.hpp>
#endif

#ifndef _IWINDOW_
  #include <iwindow.hpp>
#endif

#ifndef _IDMOPER_
  #include <idmoper.hpp>
#endif

#ifndef _ISTRING_
  #include <istring.hpp>
#endif

struct _DRAGINFO;
class IDMSourceItem;
class IDMSrcItemHandle;
class IDMSourceBeginEvent;

class IDMSourceOperation : public IDMOperation {
typedef IDMOperation
  Inherited;
/*******************************************************************************
* This is the direct manipulation source drag operation class.  Objects of     *
* this class provide information about source direct manipulation operations.  *
*                                                                              *
* Access to this information is usually gained in one of the following ways:   *
*   o Via an associated IDMSourceItem object's dragOperation() function.       *
*   o Via an associated direct manipulation event's dragOperation() function.  *
*                                                                              *
* Objects of this class possess the following attributes:                      *
*   o Information about the source direct manipulation operation as a whole:   *
*       - number of associated drag items (ie. IDMSourceItems).                *
*       - pointer to the collection of IDMSourceItems.                         *
*   o A collection of IDMSourceItem objects, one for each item being "dragged" *
*     on this operation.                                                       *
*                                                                              *
* Instances of this class are not intended to be created by application        *
* programmers.  Generally, they are created only by the direct manipulation    *
* event classes requiring this information.  Typically, access is via an       *
* IDMSrcOperationHandle object (see below).                                    *
*******************************************************************************/
public:
typedef ISet<IDMSrcItemHandle> IDMSourceItemSet;

/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed one of two ways:                       |
|   o by providing the source of the direct manipulation operation and the     |
|     pointing device position.                                                |
|   o by providing a pointer to a _DRAGINFO structure.                         |
------------------------------------------------------------------------------*/
//  IDMSourceOperation ( IDMSourceBeginEvent::Source  source,
//                       const IPoint &position );
  IDMSourceOperation ( Source  source,
                       const IPoint &position );

  IDMSourceOperation ( _DRAGINFO *pDragInfo );

  ~IDMSourceOperation ( );

/*-------------------------------- Drag Items ----------------------------------
| The following functions provide means of accessing the IDMSourceItem objects |
| involved in the direct manipulation operation described by instances of      |
| this class:                                                                  |
|   numberOfItems - Returns the number of drag items.                          |
|   Item          - Returns the drag item with given index.                    |
|   replaceItem   - Replaces a given drag item with another.                   |
|   addItem       - Associates another drag item with this operation.          |
|   removeItem    - Removes a drag item from the operation.                    |
|   itemsSetCl    - Returns a pointer to the collection of IDMSourceItems.     |
|   begin         - Initiates the dragging of the object(s).                   |
------------------------------------------------------------------------------*/
unsigned
  numberOfItems ( );

IDMSrcItemHandle
  item ( unsigned index );

IDMSourceOperation
  &replaceItem ( unsigned        index,
                 IDMSrcItemHandle replacement ),

  &addItem     ( const IDMSrcItemHandle newItem ),

  &removeItem  ( unsigned index );

IDMSourceItemSet
  *itemsSetCl ( );

void
   begin ( );

protected:
/*------------------------------ Implementation --------------------------------
| These functions provide various utility services used to implement this      |
| class:                                                                       |
|   setItems    - Sets the pointer to the collection of IDMSourceItems.        |
------------------------------------------------------------------------------*/
IDMSourceOperation
  &setItems ( IDMSourceItemSet *pIDMSourceItemSet );


private: /*------------------------ PRIVATE ----------------------------------*/
IString
  stringFromHandle        (const IStringHandle& hstr);

IDMSourceItemSet
  *pDMSrcItemSetCl;
}; //class IDMSourceOperation

class IDMSrcOperationHandle : public IReference< IDMSourceOperation > {
/*******************************************************************************
* Objects of this class provide access to IDMSourceOperation objects           *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMSourceOperation object to ensure that it is not deleted *
* until the direct manipulation operation is completed.                        *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMSourceOperation object.                         *
*                                                                              *
* Example:                                                                     *
*   // Event providing access to the drag information...                       *
*   IBeginDragEvent                                                            *
*    &event;                                                                   *
*                                                                              *
*   // Get drag information handle from event...                               *
*   IDMSrcOperationHandle                                                      *
*     srcinfo = event.dragOperation();                                         *
*                                                                              *
*   // Process items (using info as a "pointer to IDMSoruceOperation")...      *
*   for( int i = 0; i < srcinfo->numberOfItems(); i++ )                        *
*     {                                                                        *
*     // Process drag items.                                                   *
*     }                                                                        *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMSourceOperation >.                                            *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o by providing a pointer to this handle class.                             |
------------------------------------------------------------------------------*/
  IDMSrcOperationHandle (IDMSourceOperation *pIDMSourceOp) :
    IReference <IDMSourceOperation> (pIDMSourceOp) { }

  ~IDMSrcOperationHandle ( ) { }

}; //IDMSrcOperationHandle

#endif //_IDMSRCOP_
