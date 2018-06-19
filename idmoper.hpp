#ifndef _IDMOPER_
#define _IDMOPER_
/*******************************************************************************
* FILE NAME: idmoper.hpp                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDMOperation          - General purpose "direct manipulation operation"  *
*                             class.                                           *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   S:/ibmclass/idrag/vcs/idmoper.hpv  $
//
//   Rev 1.1   30 Apr 1993 11:45:36   HAGGAR
//
//   Rev 1.0   22 Apr 1993 10:41:10   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IREFCNT_
  #include <irefcnt.hpp>
#endif

#ifndef _IPOINT_
  #include <ipoint.hpp>
#endif

#ifndef _IHANDLE_
  #include <ihandle.hpp>
#endif

#ifndef _ISET_H
  #include <iset.h>
#endif

#ifndef _IDMCOMM_
  #include <idmcomm.hpp>
#endif

struct _DRAGINFO;

class IDMOperation : public IRefCounted {
typedef IRefCounted
  Inherited;
/*******************************************************************************
* This is the common base class for the direct manipulation source and target  *
* drag operation classes.  Objects of this class provide general-purpose       *
* information about direct manipulation operations.                            *
*                                                                              *
* Access to this information is gained via its derived classes.                *
*                                                                              *
* Objects of this class possess the following attributes:                      *
*   o Information about the direct manipulation operation as a whole:          *
*       - operation "type" (i.e., copy, move, or link),                        *
*       - position (i.e., of the pointing device) within the source or         *
*         target window,                                                       *
*       - source of the operation (pointing device versus keyboard),           *
*       - pointer to the PM DRAGINFO structure.                                *
*                                                                              *
* Instances of this class are not intended to be created by application        *
* programmers.  Generally, they are created only by their subclasses           *
* requiring this information.                                                  *
*******************************************************************************/
public:
//pfh typedef ISet<IDMDragImageHandle> IDMDragImageSet;

/*-------------------------------- Accessors -----------------------------------
| These functions provide access to attributes of instances of this class:     |
|   position     - Returns the drag or drop position within the source/target  |
|                  window.                                                     |
|   source       - Returns the source of the direct manipulation operation     |
|                  (always "unknown" on the target side).                      |
|   sourceWindow - Returns the handle of the source window for the direct      |
|                  manipulation operation.                                     |
------------------------------------------------------------------------------*/
//enum Source
//{
//  pointingDevice,
//  keyboard
//};

IPoint
  position ( ) const;

//IDMSourceBeginEvent::Source
Source
  source ( ) const;

IWindowHandle
  sourceWindow ( ) const;

/*-------------------------------- Operations ----------------------------------
| These functions deal with the "default operation" attribute of instances     |
| of this class:                                                               |
|   operation - Returns the default operation.                                 |
|                                                                              |
| These static members provide the set of pre-defined operation codes:         |
|   drag    - Default drag (no augmentation keys are pressed).                 |
|   copy    - Copy (the copy augmentation key is pressed).                     |
|   link    - Link (the link augmentation key(s) is(are) pressed).             |
|   move    - Move (the move augmentation key is pressed).                     |
|   unknown - Unknown (application-defined operation codes should              |
|             be assigned values greater than this).                           |
------------------------------------------------------------------------------*/
unsigned short
  operation ( ) const;

static const unsigned short
  drag,
  copy,
  link,
  move,
  unknown;

protected:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
------------------------------------------------------------------------------*/
//  IDMOperation (IDMSourceBeginEvent::Source source, const IPoint &position );
  IDMOperation (Source source, const IPoint &position );

 virtual
  ~IDMOperation ( );

/*-------------------------------- Drag Items ----------------------------------
| The following functions provide means of accessing the IDMDragImage objects  |
| involved in the direct manipulation operation.                               |
|   numberOfImages - Returns the number of drag images.                        |
|   image          - Returns the drag image with given index.                  |
|   replaceImage   - Replaces a given drag image with another.                 |
|   addImage       - Associates another drag image with this operation.        |
|   removeImage    - Removes a drag image from the operation.                  |
------------------------------------------------------------------------------*/
unsigned
  numberOfImages ( );

//pfh IDMDragImageHandle
//pfh   image ( unsigned index );

  IDMOperation
//pfh  &replaceImage ( unsigned        index,
//pfh                  IDMDragImageHandle replacement ),

//pfh  &addImage    ( IDMDragImageHandle newImage ),

  &removeImage ( unsigned index );

/*------------------------------ Implementation --------------------------------
| These functions provide various utility services used to implement this      |
| class:                                                                       |
|   setOperation  - Set the operation of the DM operation.                     |
|   setSrcWindow  - Set the source window of the DM operation.                 |
|   setSrc        - Set the source of the DM operation.                        |
|   setPosition   - Set the pointing device position for the DM operation.     |
|   setPMDragInfo - Set the pointer to the PM DRAGINFO structure.              |
|   PMDragInfo    - Returns the pointer to the PM DRAGINFO structure.          |
|   imageSetCl    - Returns a pointer to the collection of IDMDragImages.      |
|   setImages     - Sets the pointer to the collection of IDMDragImages.       |
------------------------------------------------------------------------------*/
IDMOperation
  &setOperation (unsigned short Operation),
  &setSrcWindow (IWindowHandle sourceWindow),
//pfh  &setSrc (IBeginDragEvent::Source source),
  &setSrc (Source source),
  &setPosition (IPoint position),
  &setPMDragInfo (_DRAGINFO *pDragInfo);

_DRAGINFO
   *PMDragInfo ();

//pfh IDMDragImageSet
//pfh  *imageSetCl ( ) const;

//pfh IDMOperation
//pfh   &setImages ( IDMDragImageSet *pIDMDragImageSet );

private: /*------------------------ PRIVATE ----------------------------------*/
unsigned short
  op;
IWindowHandle
  srcWindow;
//IDMSourceBeginEvent::Source
Source
  src;
IPoint
  pos;
_DRAGINFO
 *pPMDragInfo;
//pfh IDMDragImageSet
//pfh   *pDMDragImageSetCl;
}; // class IDMOperation

#ifndef I_NO_INLINES
  #include <idmoper.inl>
#endif

#endif //_IDMOPER_
