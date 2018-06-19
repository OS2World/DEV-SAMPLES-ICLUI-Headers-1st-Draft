#ifndef _IDMITEM_
#define _IDMITEM_
/*******************************************************************************
  FILE NAME: idrgitem.hpp

  DESCRIPTION:
    This file contains the declaration(s) of the class(es):
      IDMItem                   - Base direct manipulation "item" class.
      IDMSourceItem             - Source direct manipulation "item" class.
      IDMSrcItemHandle          - Handle to manage references to IDMSourceItem
                                  objects.
      IDMTargetItem             - Target direct manipulation "item" class.
      IDMTgtItemHandle          - Handle to manage references to IDMTargetItem
                                  objects.
      IDMRendererAssociate      - Base direct manipulation renderer association
                                  class.
      IDMSrcRendererAssoc       - Source direct manipulation renderer
                                  association class.
      IDMSrcRendererAssocHandle - Handle to manage references to
                                  IDMSrcRendererAssoc objects.
      IDMTgtRendererAssoc       - Target direct manipulation renderer
                                  association class.
      IDMTgtRendererAssocHandle - Handle to manage references to
                                  IDMTgtRendererAssoc objects.
      IDMSrcRendererAssocSeq    - Sequence of IDMSrcRendererAssoc objects.
      IDMTgtRendererAssocSeq    - Sequence of IDMTgtRendererAssoc objects.

  COPYRIGHT:
    Licensed Materials - Property of IBM
    (C) Copyright IBM Corporation 1992, 1993
    All Rights Reserved
    US Government Users Restricted Rights - Use, duplication, or
    disclosure
    restricted by GSA ADP Schedule Contract with IBM Corp.

* $Log:   S:/ibmclass/idrag/vcs/idmitem.hpv  $
//
//   Rev 1.1   30 Apr 1993 11:45:28   HAGGAR
//
//   Rev 1.0   22 Apr 1993 10:41:06   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IREFCNT_
  #include <irefcnt.hpp>
#endif

#ifndef _ISEQ_H
  #include <iseq.h>
#endif

#ifndef _IDMSRCOP_
  #include <idmsrcop.hpp>
#endif

#ifndef _IDMTGTOP_
  #include <idmtgtop.hpp>
#endif

#ifndef _IDMRENDR_
  #include <idmrendr.hpp>
#endif

#ifndef _ISTRING_
  #include <istring.hpp>
#endif

/* Forward Declarations */
struct _DRAGITEM;
class IDMSrcRendererAssoc;
class IDMTgtRendererAssoc;
class IDMSourceRenderEvent;
class IDMSourcePrepareEvent;
class IDMTargetRenderEvent;
class IDMSrcRndrAssocHandle;
class IDMTgtRndrAssocHandle;

class IDMSrcRendererAssocSeq : public ISequence< IDMSrcRendererAssoc* > {
/*******************************************************************************
  This class is just a wrapper for a sequence of IDMSrcRendererAssoc's.  It
  is used to add a level of indirection in the IDMSourceItem interface.
*******************************************************************************/
}; // class IDMSrcRendererAssocSeq

class IDMTgtRendererAssocSeq : public ISequence< IDMTgtRendererAssoc* > {
/*******************************************************************************
  This class is just a wrapper for a sequence of IDMTgtRendererAssoc's.  It
  is used to add a level of indirection in the IDMTargetItem interface.
*******************************************************************************/
}; // class IDMTgtRendererAssocSeq

class IDMItem : public IRefCounted {
typedef IRefCounted
  Inherited;
/*******************************************************************************
* This is the common base class for the direct manipulation source and target  *
* drag item classes.                                                           *
*                                                                              *
* This base class provides the common support required to represent objects    *
* that are dragged/dropped during a direct manipulation operation.  The        *
* derived classes, IDMSourceDragItem and IDMTargetDragItem, are declared       *
* below.                                                                       *
*                                                                              *
* Objects of this class possess the following attributes (in addition to       *
* those inherited from its base class):                                        *
*   o source window handle                                                     *
*   o types ("true" and additional) of the dragged object                      *
*   o container name (at the source)                                           *
*   o source name                                                              *
*   o suggested target name                                                    *
*   o relative position of the corresponding object image in the drag pointer  *
*   o source flags providing instructions as to how the object is to be        *
*     rendered, etc.                                                           *
*******************************************************************************/
public:

/*----------------------  Supported Operations Flags  --------------------------
  The following static members define a drag object's supported
  operations flags:

  The valid supported operations are:
    unknown   - No supported drag operations are available.
    copyable  - The source object that is being dragged can be copied to
                the specified drop location.
    moveable  - The source object that is being dragged can be moved to
                the specified drop location.
    linkable  - The source object that is being dragged can be linked to
                the specified object.

  Note:  These static members represent bit masks.  User defined values
         must be greater than linkable.
------------------------------------------------------------------------------*/
static const unsigned short
  unknown,
  copyable,
  moveable,
  linkable;

/*----------------------------  Attributes Flags  ------------------------------
  The following static members define the drag object's attribute flags:

  The valid attributes of dragged objects are:
    none             - No attributes are defined.
    open             - Source object is open
    reference        - Source object is a reference to another object
    group            - Source object is a group of objects
    container        - Source object is a container of other objects
    prepare          - Source object requires preparation before it
                         establishes a data transfer conversation
    removableMedia   - Source object is on removable media, or source object
                         cannot be recovered after a move operation

  Note:  These static members represent bit masks.  User defined values
         must be greater than removableMedia.
----------------------------------------------------------------------------*/
static const unsigned short
  none,
  open,
  reference,
  group,
  container,
  prepare,
  removableMedia;

/*-------------------------------- Accessors -----------------------------------
| These functions provide access to attributes of instances of this class:     |
|   sourceWindow         - Returns handle of the source window for this item.  |
|   containerName        - Returns the source container name.                  |
|   sourceName           - Returns the source object "name."                   |
|   targetName           - Returns the suggested target object "name."         |
|   attributes           - Returns the control attributes for this item.       |
|   supportedOperations  - Returns the operations supported by this item       |
|   origin               - Returns the item's origin offset from pointer       |
|                           hotspot.                                           |
|   dragImage            - Returns the drag image for this item, or 0 if none. |
------------------------------------------------------------------------------*/
IWindowHandle
  sourceWindow           ( ) const;

IString
  containerName          ( ) const,
  sourceName             ( ) const,
  targetName             ( ) const;

unsigned short
  attributes             ( ) const;

unsigned short
  supportedOperations    ( ) const;

ISize
  origin                 ( ) const;

//pfh virtual IDMImageHandle
//pfh   dragImage              ( ) const;

/*-------------------------------- Attributes ----------------------------------
| These functions permit the testing of a variety of drag item "attribute"     |
| flags:                                                                       |
|   isOpen                 - Indicates whether the dragged object is "open."   |
|   isReference            - Indicates whether the dragged object is a         |
|                            "reference" to another object.                    |
|   isGroup                - Indicates whether the item is a group of objecgs. |
|   isContainer            - Indicates whether the item is a container of other|
|                            objects.                                          |
|   isOnRemovableMedia     - Indicates whether the item is on removable media  |
|                            or cannot be recovered after a move operation.    |
|   requiresPreparation    - Indicates whether the source requires preparation |
|                            prior to rendering.                               |
------------------------------------------------------------------------------*/
virtual Boolean
  isOpen                    ( ) const,
  isReference               ( ) const,
  isGroup                   ( ) const,
  isContainer               ( ) const,
  isOnRemovableMedia        ( ) const,
  requiresPreparation       ( ) const;

/*-------------------------------- Operations ----------------------------------
| These functions permit the querying of the supported direct manipulation     |
| operations for the drag item:                                                |
|   canBeCopied  - Indicates whether a copy operation is supported.            |
|   canBeLinked  - Indicates whether a link operation is supported.            |
|   canBeMoved   - Indicates whether a move operation is supported.            |
------------------------------------------------------------------------------*/
virtual Boolean
  canBeCopied    ( ) const,
  canBeLinked    ( ) const,
  canBeMoved     ( ) const;

/*------------------------------- Object Type ----------------------------------
| These functions provide means for querying the "type" of the item:           |
|   trueType  - Returns the "true type" of the item.                           |
|   types     - Returns all types for the item.                                |
|   hasType   - Indicates whether the item supports an argument type.          |
------------------------------------------------------------------------------*/
virtual IString
  trueType          ( ) const,
  types             ( ) const;

virtual Boolean
  hasType           ( const IString &aType ) const;

/*-----------------------  Rendering Mechanisms/Formats  -----------------------
| These functions provide means for querying the rendering mechanism and/or    |
| format of the item:                                                          |
|   nativeSourceRMF - Returns the "native" rendering mechanism and format of   |
|                      the item.                                               |
|   nativeSourceRM  - Returns the "native" rendering mechanism of the item.    |
|   nativeSourceRF  - Returns the "native" rendering format of the item.       |
|   sourceRMFs      - Returns all rendering mechanisms and formats of the item.|
|   hasRMF          - Indicates whether the item supports a specific rendering |
|                      mechanism and format.                                   |
------------------------------------------------------------------------------*/
virtual IString
  nativeSourceRMF    ( ) const,
  nativeSourceRM     ( ) const,
  nativeSourceRF     ( ) const,
  sourceRMFs         ( ) const;

virtual Boolean
  hasRMF       ( const IString &aType );

//pfh moved from protected to public since I need them in IDMSourceOperation.
/*--------------------------- Source Accessors ---------------------------------
| These functions allow the setting of attributes for instances of the source  |
| drag item class, IDMSourceItem, which is derived from this class:            |
|   setSourceWindow      - Sets the source window for this item.               |
|   setContainerName     - Sets the source container name.                     |
|   setTargetName        - Sets the suggested target object "name."            |
|   setSourceName        - Sets the source object "name."                      |
|   setOrigin            - Sets this item's origin offset from the pointer     |
|                           hotspot.                                           |
------------------------------------------------------------------------------*/
IDMItem
 &setSourceWindow        ( IWindowHandle window ),
 &setContainerName       ( const char* containerName ),
 &setTargetName          ( const char* targetName ),
 &setSourceName          ( const char* sourceName ),
 &setOrigin              ( const ISize& origin );

//pfh moved from protected to public since I need them in IDMSourceOperation.
/*-----------------------  Rendering Mechanisms/Formats  -----------------------
| These functions provide means for setting the "RMF" of the source drag       |
| item:                                                                        |
|   addRMF - Adds an additional RMF (or RMFs).                                 |
------------------------------------------------------------------------------*/
virtual IDMItem
 &addRMF            ( const IString &aRMF );

protected:
/*----------------------------- Constructor ------------------------------------
| Generic objects of this class are constructed in the following manner:       |
|   o By providing the types, supported operations and attributes.             |
------------------------------------------------------------------------------*/
  IDMItem     ( const IString &types,
                const unsigned short supportedOperations = unknown,
                const unsigned short attributes = none);

/*--------------------------- Source Accessors ---------------------------------
| These functions allow the setting of attributes for instances of the source  |
| drag item class, IDMSourceItem, which is derived from this class:            |
|   setDragImage         - Sets or removes this item's drag image              |
------------------------------------------------------------------------------*/
//pfh IDMItem
//pfh &setDragImage           ( IDMImageHandle image,
//pfh                           Boolean        autoDelete = true);

/*--------------------------- Source Attributes --------------------------------
| These functions permit the setting of a variety of source drag item          |
| "attribute" flags:                                                           |
|   setOpen                - Set/reset the "isOpen" flag.                      |
|   setReference           - Set/reset the "isReference" flag.                 |
|   setGroup               - Set/reset the "isGroup" flag.                     |
|   setContainer           - Set/reset the "isContainer" flag.                 |
|   setOnRemovableMedia    - Set/reset the "isOnRemovableMedia" flag.          |
|   setRequiresPreparation - Set/reset the "requiresPreparation" flag.         |
------------------------------------------------------------------------------*/
virtual IDMItem
 &setOpen                   ( Boolean open             = true ),
 &setReference              ( Boolean reference        = true ),
 &setGroup                  ( Boolean group            = true ),
 &setContainer              ( Boolean container        = true ),
 &setOnRemovableMedia       ( Boolean onRemovableMedia = true ),
 &setRequiresPreparation    ( Boolean requiresPrep     = true );

/*--------------------------- Source Operations --------------------------------
| These functions permit the setting of the supported direct manipulation      |
| operations for the source drag item:                                         |
|   enableCopy    - Enables or disables copy operation for the item.           |
|   enableLink    - Enables or disables link operation for the item.           |
|   enableMove    - Enables or disables move operation for the item.           |
------------------------------------------------------------------------------*/
virtual IDMItem
 &enableCopy       ( Boolean copyable = true ),
 &enableLink       ( Boolean linkable = true ),
 &enableMove       ( Boolean moveable = true );

/*-------------------------- Source Object Type --------------------------------
| These functions provide means for setting the "type" of the source drag      |
| item:                                                                        |
|   setTrueType     - Sets the "true type" to the argument type.               |
|   addType         - Adds an additional type (or types).                      |
|   removeType      - Removes a type from this item.                           |
|   replaceType     - Replaces a type for this item.                           |
------------------------------------------------------------------------------*/
virtual IDMItem
 &setTrueType       ( const IString &aType ),
 &addType           ( const IString &aType ),
 &removeType        ( const IString &aType ),
 &replaceType       ( const IString &oldType, const IString &newType );

/*-----------------------  Rendering Mechanisms/Formats  -----------------------
| These functions provide means for setting the "RMF" of the source drag       |
| item:                                                                        |
|   setNativeRMF    - Sets the "native RMF to the argument type.               |
|   removeRMF       - Removes a RMF from this item.                            |
|   replaceRMF      - Replaces a RMF for this item.                            |
------------------------------------------------------------------------------*/
virtual IDMItem
 &setNativeRMF      ( const IString &aRMF ),
 &removeRMF         ( const IString &aRMF ),
 &replaceRMF        ( const IString &oldRMF, const IString &newRMF );


private: /*------------------------ PRIVATE ----------------------------------*/

unsigned short
  dragSupOps,
  dragAttrs;

IWindowHandle
  sourceWndh;

//pfhIDMImageHandle
//pfh  pDragImage;

Boolean
  bAutoDelImage;

ISize
  sizeOrigin;

IString
  strContainerName,
  strSourceName,
  strTargetName,
  strTypes,
  strRMFs;

}; // IDMItem


//class IDMItemHandle : public IReference< IDMItem > {
/*******************************************************************************
* Objects of this common base class provide access to generic IDMItem objects. *
* This "handle" class manages references to the IDMItem object to ensure that  *
* it is not deleted until the drag operation is completed.                     *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMItem object.                                    *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMItem >.                                                       *
*******************************************************************************/
//public:
//  IDMItemHandle (IDMItem *pIDMItem);
//  ~IDMItemHandle ( );

/*--------------------------------- Operators ---------------------------------+
| Operators defined for IDMItemHandle:                                         |
|   == - Overload definition to handle comparisons of base drag item handles.  |
|   <  - Overload definition to handle comparisons of base drag item handles.  |
+-----------------------------------------------------------------------------*/
//Boolean
//  operator ==    ( const IDMItemHandle &item ) const,
//  operator <     ( const IDMItemHandle &item ) const;

//}; // IDMItemHandle


class IDMSourceItem : public IDMItem {
typedef IDMItem
  Inherited;
/*******************************************************************************
* Objects of this class are created by windows when a direct manipulation      *
* operation commences on the source side.                                      *
*                                                                              *
* Objects of this class possess the following attributes (in addition to       *
* those inherited from its base class):                                        *
*   o association with a source drag operation object (see                     *
*     IDMSourceOperation)                                                      *
*   o association(s) with source drag renderer object(s) (see                  *
*     IDMSourceRenderer) which are created by the source handler (see          *
*     IDMSourceHandler)                                                        *
*                                                                              *
* This class provides virtual functions that implement the source rendering    *
* of the dragged/dropped objects.  Derived classes are created to support      *
* additional rendering mechanisms and/or formats.  The IDMSourceItem           *
* class supports, in conjunction with the standard library IWindow subclasses, *
* rendering with all the standard system rendering mechanisms whenever such    *
* rendering makes sense.                                                       *
*******************************************************************************/
friend class IDMSourceOperation;

public:
/*-------------------------------- Rendering -----------------------------------
| These functions are called during the course of "rendering" the drag item:   |
|   render                 - Transfer the item from source to target.          |
|   prepareToRender        - Notify source that rendering will commence.       |
|   notifyRenderCompletion - Notify source/target that rendering is complete.  |
|                                                                              |
|   Bill - move to source renderer ...                                         |
------------------------------------------------------------------------------*/
virtual IDMSourceItem
 &render                    ( const IDMSourceRenderEvent &renderEvent ),
 &prepareToRender           ( const IDMSourcePrepareEvent &prepareEvent ),
 &notifyRenderCompletion    ( const IDMSourceRenderEvent &renderEvent);

/*-------------------------------- Accessors -----------------------------------
| These functions provide access to attributes of instances of this class:     |
|   dragOperation        - Returns a handle to the "owning" IDMSourceOperation |
|                           object.                                            |
|   rendererAssociations - Used to access the rendering mechanism and format,  |
|                           and type associations for this item.               |
------------------------------------------------------------------------------*/
IDMSrcOperationHandle
  dragOperation           ( ) const;

IDMSrcRendererAssocSeq
  &rendererAssociations    ( );

/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o By providing the drag source operation handle, types, supported          |
|     operations and attributes.                                               |
------------------------------------------------------------------------------*/
  IDMSourceItem     ( const IDMSrcOperationHandle sourceOperation,
                      const IString &types,
                      const unsigned short supportedOperations = unknown,
                      const unsigned short attributes = none);

virtual
  ~IDMSourceItem    ( );

protected:
/*------------------------------ Implementation --------------------------------

------------------------------------------------------------------------------*/

private: /*------------------------ PRIVATE ----------------------------------*/

//IString
//  stringFromHandle        (const IStringHandle& hstr);

void
  asPMDragItem  ( _DRAGITEM *pDragItem );

IDMSrcOperationHandle
  pDMSrcOperation;

IDMSrcRendererAssocSeq
  pSrcRendAssocSeqCl;

}; // IDMSourceItem


class IDMSrcItemHandle : public IReference< IDMSourceItem > {
/*******************************************************************************
* Objects of this class provide access to IDMSourceItem objects                *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMSourceItem object to ensure that it is not              *
* deleted until the drag operation is completed.                               *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMSourceItem object.                              *
*                                                                              *
* Example:                                                                     *
*   // IDMSrcOperationHandle providing access to the source drag operation...  *
*   IDMSrcOperationHandle                                                      *
*     srcOperation;                                                            *
*                                                                              *
*   // Process items...                                                        *
*   for( int i = 0; i < srcOperation->numberOfItems(); i++ )                   *
*     {                                                                        *
*     IDMSrcItemHandle                                                         *
*       item = srcOperation->item( i );                                        *
*     // If item is C code, then this handler can accept it...                 *
*     if ( item->trueType() == IDragItem::cCode )                              *
*       // Note: The following line is tentative and should be amended         *
*       //       per the actual drag item protocol when it is completed.       *
*       item -> enableDrop();                                                  *
*     }                                                                        *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMSourceItem >.                                                 *
*******************************************************************************/
public:
  IDMSrcItemHandle (IDMSourceItem *pIDMSrcItem);
  ~IDMSrcItemHandle ( );

/*--------------------------------- Operators ---------------------------------+
| Operators defined for IDMSrcItemHandle:                                      |
|   == - Overload definition to handle comparisons of source drag item handles.|
|   <  - Overload definition to handle comparisons of source drag item handles.|
+-----------------------------------------------------------------------------*/
Boolean
  operator ==    ( const IDMSrcItemHandle &sourceItem ) const,
  operator <     ( const IDMSrcItemHandle &sourceItem ) const;

}; // IDMSrcItemHandle


class IDMTargetItem : private IDMItem {
typedef IDMItem
  Inherited;
/*******************************************************************************
* Objects of this class are created by windows during a direct manipulation    *
* operation when the objects are dragged over or dropped on a target window.   *
*                                                                              *
* Objects of this class possess the following attributes (in addition to       *
* those inherited from its base class):                                        *
*   o association with a target drag operation object (see                     *
*     IDMTargetOperation)                                                      *
*   o association(s) with target drag renderer object(s) (see                  *
*     IDMTargetRenderer) which are created by the target handler (see          *
*     IDMTargetHandler)                                                        *
*                                                                              *
* This class provides virtual functions that implement the target rendering    *
* of the dragged/dropped objects.  Derived classes are created to support      *
* additional rendering mechanisms and/or formats.  The IDMTargetItem           *
* class supports, in conjunction with the standard library IWindow subclasses, *
* rendering with all the standard system rendering mechanisms whenever such    *
* rendering makes sense.                                                       *
*******************************************************************************/
public:
friend class IDMTgtOperationHandle;
friend class IDMTargetRenderer;

/*-------------------------------- Promotions ----------------------------------
| The following functions are inherited as private functions from IDMItem.     |
| They are promoted to make them publicly accessible.                          |
|   sourceWindow         - Returns handle of the source window for this item.  |
|   containerName        - Returns the source container name.                  |
|   sourceName           - Returns the source object "name."                   |
|   targetName           - Returns the suggested target object "name."         |
|   attributes           - Returns the control attributes for this item.       |
|   supportedOperations  - Returns the operations supported by this item       |
|   origin               - Returns the item's origin offset from pointer       |
|                           hotspot.                                           |
|   dragImage            - Returns the drag image for this item, or 0 if none. |
|   isOpen               - Indicates whether the dragged object is "open."     |
|   isReference          - Indicates whether the dragged object is a           |
|                          "reference" to another object.                      |
|   isGroup              - Indicates whether the item is a group of objecgs.   |
|   isContainer          - Indicates whether the item is a container of other  |
|                          objects.                                            |
|   isOnRemovableMedia   - Indicates whether the item is on removable media    |
|                          or cannot be recovered after a move operation.      |
|   requiresPreparation  - Indicates whether the soure requires preparation    |
|                          prior to rendering.                                 |
|   canBeCopied          - Indicates whether a copy operation is supported.    |
|   canBeLinked          - Indicates whether a link operation is supported.    |
|   canBeMoved           - Indicates whether a move operation is supported.    |
|   trueType             - Returns the "true type" of the item.                |
|   types                - Returns all types for the item.                     |
|   hasType              - Indicates whether the item supports an argument     |
|                          type.                                               |
|   nativeRMF            - Returns the "native" rendering mechanism and format |
|                          of the item.                                        |
|   nativeRM             - Returns the "native" rendering mechanism of the     |
|                          item.                                               |
|   nativeRF             - Returns the "native" rendering format of the item.  |
|   RMFs                 - Returns all rendering mechanisms and formats of     |
|                          the item.                                           |
|   hasRMF               - Indicates whether the item supports a specific      |
|                          rendering mechanism and format.                     |
|   addRef               - used by the template class.                         |
|   removeRef            - used by the template class.                         |
------------------------------------------------------------------------------*/
  IDMItem::sourceWindow;
  IDMItem::containerName;
  IDMItem::sourceName;
  IDMItem::targetName;
  IDMItem::attributes;
  IDMItem::supportedOperations;
  IDMItem::origin;
  IDMItem::isOpen;
  IDMItem::isReference;
  IDMItem::isGroup;
  IDMItem::isContainer;
  IDMItem::isOnRemovableMedia;
  IDMItem::requiresPreparation;
  IDMItem::canBeCopied;
  IDMItem::canBeLinked;
  IDMItem::canBeMoved;
  IDMItem::trueType;
  IDMItem::types;
  IDMItem::hasType;
  IDMItem::hasRMF;
  IDMItem::addRef;
  IDMItem::removeRef;
  IDMItem::sourceRMFs;

/*--------------------------  Target Rendering  --------------------------------
| These functions are called during the course of "rendering" the drag item:   |
|   render                 - Allow target to render the item.                  |
|   notifyRenderCompletion - Notify target that rendering is complete. (???)   |
------------------------------------------------------------------------------*/
virtual IDMTargetItem
 &render                    ( const IDMTargetRenderEvent &renderEvent ),
 &notifyRenderCompletion    ( );

/*-------------------------------- Accessors -----------------------------------
| These functions provide access to attributes of instances of this class:     |
|   dragOperation        - Returns a handle to the "owning" IDMTargetOperation |
|                           object.                                            |
|   rendererAssociations - Used to access the rendering mechanism and format,  |
|                           and type associations for this item.               |
------------------------------------------------------------------------------*/
IDMTgtOperationHandle
  dragOperation           ( ) const;

virtual IDMTgtRendererAssocSeq
 &rendererAssociations    ( );

//pfh moved to make public
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o By providing a pointer to a DRAGITEM structure                           |
------------------------------------------------------------------------------*/
  IDMTargetItem     ( _DRAGITEM *pDragItem );

virtual
  ~IDMTargetItem    ( );

protected:
private: /*------------------------ PRIVATE ----------------------------------*/

void
  asPMDragItem  ( _DRAGITEM *pDragItem );

//IString
//  stringFromHandle  (const IStringHandle& hstr);

_DRAGITEM
 *PMDragItem  ( );

_DRAGITEM
 *pPMDragItem;

IDMTgtOperationHandle
  pDMTgtOperation;

IDMTgtRendererAssocSeq
  pTgtRendAssocSeqCl;

}; // IDMTargetItem


class IDMTgtItemHandle : public IReference< IDMTargetItem > {
/*******************************************************************************
* Objects of this class provide access to IDMTargetItem objects                *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMTargetItem object to ensure that it is not              *
* deleted until the drag operation is completed.                               *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMTargetItem object.                              *
*                                                                              *
* Example:                                                                     *
*   // IDMTgtOperationHandle providing access to the drag information...       *
*   IDMTgtOperationHandle                                                      *
*     tgtOperation;                                                            *
*                                                                              *
*   // Process items...                                                        *
*   for( int i = 0; i < tgtOperation->numberOfItems(); i++ )                   *
*     {                                                                        *
*     IDMTgtItemHandle                                                         *
*       item = tgtOperation->item( i );                                        *
*     // If item is C code, then this handler can accept it...                 *
*     if ( item->trueType() == IDragItem::cCode )                              *
*       // Note: The following line is tentative and should be amended         *
*       //       per the actual drag item protocol when it is completed.       *
*       item -> enableDrop();                                                  *
*     }                                                                        *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMTargetItem >.                                                 *
*******************************************************************************/
public:
  IDMTgtItemHandle (IDMTargetItem *pIDMTgtItem);
  ~IDMTgtItemHandle ( );

/*--------------------------------- Operators ---------------------------------+
| Operators defined for IDMTgtItemHandle:                                      |
|   == - Overload definition to handle comparisons of target drag item handles.|
|   <  - Overload definition to handle comparisons of target drag item handles.|
+-----------------------------------------------------------------------------*/
Boolean
  operator ==    ( const IDMTgtItemHandle &targetItem ) const,
  operator <     ( const IDMTgtItemHandle &targetItem ) const;

}; // IDMTgtItemHandle

class IDMSrcRendererAssoc : public IRefCounted {
typedef IBase
  Inherited;
/*******************************************************************************
* Objects of this class are created by windows when a direct manipulation      *
* operation commences on the source side.                                      *
*                                                                              *
* This class provides the support required to link source renderers with       *
* with drag items based upon the drag item type(s).                            *
*******************************************************************************/
public:

/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o By providing type and identifying the source renderer.                   |
------------------------------------------------------------------------------*/
  IDMSrcRendererAssoc     (IString type,
                           IDMSrcRendererHandle renderer);

virtual
  ~IDMSrcRendererAssoc    ( );

/*-------------------------------- Accessors -----------------------------------
| This function provides access to attributes of instances of this class:      |
|   sourceRenderer  - Returns a handle to the source renderer.                 |
------------------------------------------------------------------------------*/
virtual IDMSrcRendererHandle
  sourceRenderer    ( ) const;

protected:
private: /*------------------------ PRIVATE ----------------------------------*/

IString
  strTypes;

IDMSrcRendererHandle
  pSrcRenderer;

}; // class IDMSrcRendererAssoc

class IDMSrcRndrAssocHandle : public IReference< IDMSrcRendererAssoc > {
/*******************************************************************************
* Objects of this class provide access to IDMSrcRendererAssoc objects          *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMSrcRendererAssoc object to ensure that it is not        *
* deleted until the drag operation is completed.                               *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMSrcRendererAssoc object.                        *
*                                                                              *
* Example:                                                                     *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMSrcRendererAssoc >.                                           *
*******************************************************************************/
public:
  IDMSrcRndrAssocHandle (IDMSrcRendererAssoc *pIDMSrcRendAssoc) :
    IReference <IDMSrcRendererAssoc> (pIDMSrcRendAssoc) { };
  ~IDMSrcRndrAssocHandle ( );
}; // IDMSrcRndrAssocHandle


class IDMTgtRendererAssoc : public IRefCounted {
typedef IBase
  Inherited;
/*******************************************************************************
* Objects of this class are created by windows during a direct manipulation    *
* operation when the objects are dragged over or dropped on a target window.   *
*                                                                              *
* This class provides the support required to link target renderers with       *
* with drag items based upon the drag item type(s).                            *
*******************************************************************************/
public:

/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed in the following manner:               |
|   o By providing type and identifying the target renderer.                   |
------------------------------------------------------------------------------*/
  IDMTgtRendererAssoc     (IString type,
                           IDMTgtRendererHandle renderer);

virtual
  ~IDMTgtRendererAssoc    ( );

/*-------------------------------- Accessors -----------------------------------
| This function provides access to attributes of instances of this class:      |
|   targetRenderer  - Returns a handle to the target renderer.                 |
------------------------------------------------------------------------------*/
virtual IDMTgtRendererHandle
  targetRenderer    ( ) const;

protected:
private: /*------------------------ PRIVATE ----------------------------------*/

IString
  strTypes;

IDMTgtRendererHandle
  pTgtRenderer;

}; // class IDMTgtRendererAssoc


class IDMTgtRndrAssocHandle : public IReference< IDMTgtRendererAssoc > {
/*******************************************************************************
* Objects of this class provide access to IDMTgtRendererAssoc objects          *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMTgtRendererAssoc object to ensure that it is not        *
* deleted until the drag operation is completed.                               *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMTgtRendererAssoc object.                        *
*                                                                              *
* Example:                                                                     *
*                                                                              *
* This class has no members.  It is essentially a synonym for the type         *
* IReference< IDMTgtRendererAssoc >.                                           *
*******************************************************************************/
public:
  IDMTgtRndrAssocHandle (IDMTgtRendererAssoc *pIDMTgtRendAssoc) :
    IReference <IDMTgtRendererAssoc> (pIDMTgtRendAssoc) { };
  ~IDMTgtRndrAssocHandle ( );
}; // IDMTgtRndrAssocHandle

#ifndef I_NO_INLINES
  #include <idmitem.inl>
#endif

#endif // _IDMITEM_
