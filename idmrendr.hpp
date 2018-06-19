#ifndef _IDMRENDR_
#define _IDMRENDR_
/*******************************************************************************
* FILE NAME: idmrendr.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDMRenderer          - Direct manipulation renderer common base class.   *
*     IDMSourceRenderer    - Source renderer.                                  *
*     IDMSrcRendererHandle - Source renderer handle.                           *
*     IDMTargetRenderer    - Target renderer.                                  *
*     IDMTgtRendererHandle - Target renderer handle.                           *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   M:/ibmclass/idrag/vcs/idmrendr.hpv  $
//
//   Rev 1.2   05 May 1993 16:36:00   unknown
//Source Render Prepare changes
//
//   Rev 1.1   30 Apr 1993 11:45:40   HAGGAR
//No change.
//
//   Rev 1.0   22 Apr 1993 10:44:08   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IREFCNT_
  #include <irefcnt.hpp>
#endif

#ifndef _IDMEVENT_
  #include <idmevent.hpp>
#endif

#ifndef _ISTRING_
  #include <istring.hpp>
#endif

/* Forward Declarations */
struct _DRAGTRANSFER;
class IDMTgtItemHandle;
class IDMItem;
class IDMSourceItem;
class IDMTargetItem;


class IDMRenderer : public IRefCounted {
typedef IRefCounted
  Inherited;
/*******************************************************************************
* This is the common base class for the source and target direct               *
* manipulation renderer classes.                                               *
*                                                                              *
* Objects of this class perform the "rendering" of items during direct         *
* manipulation.  Such "rendering" is essentially the transfer of the dragged   *
* object from the source to the target window.                                 *
*                                                                              *
* This class is an abstract base class that defines the common protocol of     *
* source and target renderers.  The derived classes IDMSourceRenderer and      *
* IDMTargetRenderer, declared below, define the specific protocol for source   *
* and target renderers.                                                        *
*                                                                              *
* A generic renderer possesses the following attributes:                       *
*   o A set of supported types.  These are the types of dragged items that     *
*     this renderer can work with.                                             *
*   o A set of supported rendering mechanisms and rendering formats (RMFs).    *
*     These describe the various means by which this renderer can transfer     *
*     the dragged object.                                                      *
*                                                                              *
* The operations that can be performed on objects of this class fall into      *
* two basic categories:                                                        *
*   o Queries as to whether the renderer can render a given item.              *
*   o Requests to perform one of the basic rendering processes.                *
*******************************************************************************/
public:

/*------------------------ Constructor/Destructor ------------------------------
| Generic objects of this class are constructed without formal parameters.     |
------------------------------------------------------------------------------*/
  IDMRenderer             ( );
  virtual ~IDMRenderer    ( );

/*------------------------- Supported Types and RMFs ---------------------------
  These functions return the types and renderering mechanisms/formats
  supported by an IDMRenderer object:
    supportedTypes - Returns the types of items supported by the renderer.
    supportedRMFs  - Returns the rendering mechanisms and formsts supported
                     by this renderer.
------------------------------------------------------------------------------*/
virtual IString
  supportedTypes    ( ) const,
  supportedRMFs     ( ) const;

/*--------------------------------- Testing ------------------------------------
  These function permit querying of the renderer's capability to render a
  given item:
    canSourceRender - Returns true if the source renderer can render an
                      object with a given type (or set of possible types).
    canSourceRender - Returns true if the source renderer can render an
                      object with a given selecte type + selected RMF +
                      selected operation.
    canTargetRender - Returns true if the target renderer can render an
                      object with a given type + set of possible source RMFs +
                      default operation.
------------------------------------------------------------------------------*/
virtual Boolean
  canSourceRender    ( const IString  &types ),
  canSourceRender    ( const IString  &selectedType,
                       const IString  &selectedRMF,
                       unsigned short selectedOp ),
  canTargetRender    ( const IString  &types,
                       const IString  &sourceRMFs,
                       unsigned short defaultOp );

/*-------------------------------- Rendering -----------------------------------
  These functions are called to actually perform the rendering:
    sourceRender - Called when the target renderer requests that a source
                   renderer render an item.
    targetRender - Called when a dragged operation is dropped on a target.
    sourceRenderComplete - Called (on the target renderer) when the source
                   renderer indicates it has completed a sourceRender.
    renderComplete - Invoked against the target renderer when it has
                   completed rendering (generates DM_ENDCONVERSATIION),
                   called against the source handler when the
                   DM_ENDCONVERSATION event occurs.
------------------------------------------------------------------------------*/
virtual IDMRenderer
 &sourceRender            ( const IDMSrcItemHandle &dragItem ),
 &targetRender            ( const IDMTgtItemHandle &dragItem ),

 &sourceRenderComplete    ( const IDMSrcItemHandle &dragItem ),

 &renderComplete          ( const IDMItem &dragItem );

protected:
/*------------------------- Supported Types and RMFs ---------------------------
  These functions set the types and renderering mechanisms/formats
  supported by an IDMRenderer object:
    setSupportedTypes - Sets the types of items supported by the renderer.
    setSupportedRMFs  - Sets the rendering mechanisms and formsts supported
                        by this renderer.
------------------------------------------------------------------------------*/
virtual IDMRenderer
 &setSupportedTypes    ( const IString &aType ),
 &setSupportedRMFs     ( const IString &aRMF );

private: /*------------------------ PRIVATE ----------------------------------*/

IString
  strTypes,
  strRMFs;

}; // class IDMRenderer


class IDMSourceRenderer : public IDMRenderer {
/*******************************************************************************
* Objects of this class provide source rendering when a direct manipulation    *
* operation is performed.  Instances of this class are "registered" with the   *
* source handler.  The handler selects a renderer for a given drag item and    *
* invokes rendering functions of the renderer when source rendering events     *
* occur.                                                                       *
*******************************************************************************/
public:
/*--------------------------------- Testing ------------------------------------
| These functions are used to test whether a given item can be rendered:       |
|   canRender - Returns true if the renderer can render items with the         |
|               argument attribute(s).                                         |
------------------------------------------------------------------------------*/
virtual Boolean
  canRender    ( const IString  &types ),
  canRender    ( const IString  &selectedType,
                 const IString  &selectedRMF,
                 unsigned short selectedOp );

/*-------------------------------- Rendering -----------------------------------
| These functions are called to perform rendering operations:                  |
|   renderPrepare  - Called when a "render prepare" event occurs for a drag    |
|                    item to be rendered by this renderer.                     |
|   render         - Called when a "render" event occurs for a drag item to    |
|                    be rendered by this renderer.                             |
|   renderComplete - Called when a "completion" event occurs for a drag item   |
|                    to be rendered by this renderer.                          |
------------------------------------------------------------------------------*/
virtual IDMSourceRenderer
 &renderPrepare     ( IDMSourcePrepareEvent &event ),
 &render            ( IDMSourceRenderEvent  &event ),
 &renderComplete    ( const IDMSourceItem   &sourceItem,
                      IDMSourceEndEvent     &event );

}; // class IDMSourceRenderer


class IDMSrcRendererHandle : public IReference< IDMSourceRenderer > {
/*******************************************************************************
* Objects of this class provide access to IDMSourceRenderer objects            *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMSourceRenderer object to ensure that it is not          *
* deleted until the drag operation is completed.                               *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMSourceRenderer object.                          *
*                                                                              *
* Example:                                                                     *
*   // BUGBUG - Provide example                                                *
*                                                                              *
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
* IReference< IDMSourceRenderer >.                                             *
*******************************************************************************/
public:
  IDMSrcRendererHandle (IDMSourceRenderer *pIDMSrcRenderer);
  ~IDMSrcRendererHandle ( );

/*--------------------------------- Operators ---------------------------------+
| Operators defined for IDMSrcRendererHandle:                                  |
|   == - Overload definition to handle comparisons of source drag item handles.|
|   <  - Overload definition to handle comparisons of source drag item handles.|
+-----------------------------------------------------------------------------*/
Boolean
  operator ==    ( const IDMSrcRendererHandle &sourceRenderer ) const,
  operator <     ( const IDMSrcRendererHandle &sourceRenderer ) const;

}; // IDMSrcRendererHandle


class IDMTargetRenderer : public IDMRenderer {
/*******************************************************************************
  Objects of this class provide target rendering when a direct manipulation
  operation is performed.  Instances of this class are "registered" with the
  target handler.  The handler selects a renderer for a given drag item and
  invokes rendering functions of the renderer when target rendering events
  occur.
*******************************************************************************/
public:

/*------------------------ Constructor/Destructor ------------------------------
| Generic objects of this class are constructed without formal parameters.     |
------------------------------------------------------------------------------*/
  IDMTargetRenderer     ( );
  ~IDMTargetRenderer    ( );

/*--------------------------------- Testing ------------------------------------
| These functions are used to test whether a given item can be rendered:       |
|   canRender - Returns drop indicator per the renderers ability to render     |
|               the item with the argument attributes.                         |
------------------------------------------------------------------------------*/
virtual IDMSourceNotifyEvent::DropIndicator
  canRender         ( const IString &aType,
                      const IString &sourceRMFs,
                      unsigned short defaultOp,
                      const IDMTgtItemHandle dragItem );

virtual Boolean
  checkOperation    ( const IDMTgtItemHandle dragItem,
                      unsigned short defaultOp );

/*-------------------------------- Rendering -----------------------------------
| These functions are called to perform rendering operations:                  |
|   render         - Called when a "drop" event occurs for a drag item to      |
|                    be rendered by this renderer.                             |
|   renderComplete - Called when a "completion" event occurs for a drag item   |
|                    to be rendered by this renderer.                          |
------------------------------------------------------------------------------*/
virtual IDMTargetRenderer
 &render            ( const IDMTgtItemHandle &dragItem,
                      IDMTargetDropEvent     &dropEvent ),
 &renderComplete    ( const IDMTargetItem    &targetItem,
                      IDMTargetEndEvent      &event );

protected:
/*------------------------------ Implementation --------------------------------
| These functions provide utilities used to implement this class:              |
|   sourceRender             - Send "render" event to source window to request |
|                              source rendering for the argument item.         |
|   sourceRenderPrepare      - Send "prepare" event to source window to request|
|                              source preparation for the argument item.       |
|   informSourceOfCompletion - Send "end" event to source to inform it that    |
|                              rendering is completed for the argument item.   |
------------------------------------------------------------------------------*/
virtual IDMTargetRenderer
 &sourceRender                ( const IDMTgtItemHandle &dragItem,
                                IDMTargetDropEvent     &dropEvent ),
 &sourceRenderPrepare         ( const IDMTgtItemHandle &dragItem,
                                IDMTargetDropEvent     &dropEvent ),
 &informSourceOfCompletion    ( const IDMTgtItemHandle &dragItem );

private: /*------------------------ PRIVATE ----------------------------------*/

_DRAGTRANSFER *dragTransfer (const IDMTgtItemHandle &dragItem,
                             IDMTargetDropEvent     &dropEvent);
_DRAGTRANSFER
 *pPMDragTransfer;

}; // class IDMTargetRenderer


class IDMTgtRendererHandle : public IReference< IDMTargetRenderer > {
/*******************************************************************************
* Objects of this class provide access to IDMTargetRenderer objects            *
* associated with a direct manipulation event.  This "handle" class manages    *
* references to the IDMTargetRenderer object to ensure that it is not          *
* deleted until the drag operation is completed.                               *
*                                                                              *
* This class provides a "->" operator that enables instances to be treated     *
* just like a pointer to an IDMTargetRenderer object.                          *
*                                                                              *
* Example:                                                                     *
*   // BUGBUG - Provide example                                                *
*                                                                              *
*   // IDMTgtOperationHandle providing access to the source drag operation...  *
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
* IReference< IDMTargetRenderer >.                                             *
*******************************************************************************/
public:
  IDMTgtRendererHandle (IDMTargetRenderer *pIDMTgtRenderer);
  ~IDMTgtRendererHandle ( );

/*--------------------------------- Operators ---------------------------------+
| Operators defined for IDMTgtRendererHandle:                                  |
|   == - Overload definition to handle comparisons of target drag item handles.|
|   <  - Overload definition to handle comparisons of target drag item handles.|
+-----------------------------------------------------------------------------*/
Boolean
  operator ==    ( const IDMTgtRendererHandle &targetRenderer ) const,
  operator <     ( const IDMTgtRendererHandle &targetRenderer ) const;

}; // IDMTgtRendererHandle


#ifndef I_NO_INLINES
  #include <idmrendr.inl>
#endif

#endif // _IDMRENDR_
