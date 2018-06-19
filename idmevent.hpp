#ifndef _IDMEVENT_
#define _IDMEVENT_
/*******************************************************************************
* FILE NAME: idmevent.hpp                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*   This file contains the declaration(s) of the class(es):                    *
*     IDMEvent                                                                 *
*                                                                              *
*     IDMSourceBeginEvent                                                      *
*     IDMSourceRenderEvent                                                     *
*     IDMSourcePrepareEvent                                                    *
*     IDMSourceEndEvent                                                        *
*     IDMSourceNotifyEvent                                                     *
*                                                                              *
*     IDMTargetEnterEvent                                                      *
*     IDMTargetDropEvent                                                       *
*     IDMTargetEndEvent                                                        *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or               *
*   disclosure                                                                 *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   M:/ibmclass/idrag/vcs/idmevent.hpv  $
//
//   Rev 1.2   03 May 1993 16:05:46   unknown
//Latest changes per IC_UM_DRAGOVER
//
//   Rev 1.1   30 Apr 1993 11:45:18   HAGGAR
//
//   Rev 1.0   22 Apr 1993 10:41:02   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IEVENT_
  #include <ievent.hpp>
#endif

#ifndef _IDMSRCOP_
  #include <idmsrcop.hpp>
#endif

#ifndef _IDMTGTOP_
  #include <idmtgtop.hpp>
#endif

class IDMSrcItemHandle;
class IPoint;
class IWindowHandle;
class IString;

class IDMEvent : public IEvent {
/*******************************************************************************
* This is the common base class for all direct manipulation event classes.     *
*******************************************************************************/
public:
protected:
/*----------------------- Constructor/Destructor ------------------------------|
| Instances of this class are constructed from a generic IEvent and an         |
| IDragInformation handle.                                                     |
|                                                                              |
| The constructor is protected so that this class is effectively an abstract   |
| base class.                                                                  |
------------------------------------------------------------------------------*/
  IDMEvent ( IEvent &event );
  ~IDMEvent ( );

private: /*------------------------ PRIVATE ----------------------------------*/
};

class IDMSourceBeginEvent : public IDMEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
* Objects of this class represent the event that occurs upon initiation        *
* of a direct manipulation event at the source window.  Instances are          *
* passed as argument to the IDMSourceHandler functions setup() and             *
* begin() functions.                                                           *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMSourceBeginEvent ( IEvent &event );
  ~IDMSourceBeginEvent ( );

/*--------------------------------- Accessors ----------------------------------
| These functions provide means of getting and setting the accessible          |
| attributes of instances of this class:                                       |
|   Source        - Enumeration of the possible drag start sources:            |
|                     pointingDevice - Drag initiated via mouse.               |
|                     keyboard       - Drag initiated via keyboard.            |
|   source        - Returns the source of the drag operation.                  |
|   position      - Returns the pointing device position (only if source is    |
|                   pointingDevice).                                           |
|   dragOperation - Returns the source drag operation handle for this event.   |
------------------------------------------------------------------------------*/

//virtual IDMOperation::Source
//  source ( ) const;

virtual IPoint
  position ( ) const;

IDMSrcOperationHandle
  dragOperation () const;

protected:
private: /*------------------------ PRIVATE ----------------------------------*/
IDMSrcOperationHandle
  pDMSrcOpHandle;
IPoint
  pos;
}; // IDMSourceBeginEvent


class IDMSourceRenderEvent : public IDMEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
* Objects of this class represent direct manipulation "rendering" events.      *
* Such events are created and dispatched to source handlers when a direct      *
* manipulation target handler requests source rendering.                       *
*                                                                              *
* In addition to the standard IEvent attributes (event and window              *
* identifiers), such objects also possess:                                     *
*   o an associated IDragItem                                                  *
*   o a target window handle                                                   *
*   o a rendering mechanism/format selected by the target                      *
*   o a target name                                                            *
*   o an arbitrary target "information" (an unsigned long)                     *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMSourceRenderEvent ( IEvent &event );
  ~IDMSourceRenderEvent ( );

/*-------------------------------- Accessors -----------------------------------
| The following functions provide access to the accessible attributes of       |
| instances of this class:                                                     |
|   dragItem          - Returns handle to the IDragItem corresponding to       |
|                       the item being rendered.                               |
|   alternateWindow   - Returns the handle of the alternate source window.     |
|   selectedMechanism - Returns the selected rendering mechanism.              |
|   selectedFormat    - Returns the selected rendering format.                 |
|   targetName        - Returns the target "render to" name.                   |
|   targetInfo        - Returns the target-defined "information."              |
|   dragOperation     - Returns the source drag operation handle for this      |
|                       event.                                                 |
------------------------------------------------------------------------------*/
IDMSrcItemHandle
  dragItem ( ) const;

IWindowHandle
  alternateWindow ( ) const;

IString
  selectedMechanism ( ) const,
  selectedFormat    ( ) const,
  targetName        ( ) const;

unsigned long
  targetInfo ( ) const;

IDMSrcOperationHandle
  dragOperation ();

protected:
private: /*------------------------ PRIVATE ----------------------------------*/
IDMSrcOperationHandle
  pDMSrcOpHandle;
}; // IDMSourceRenderEvent

class IDMSourcePrepareEvent : public IDMSourceRenderEvent {
typedef IDMSourceRenderEvent
  Inherited;
/*******************************************************************************
* These events are sent to the source window when the source renderer for a    *
* given object has indicated such notification is necessary prior to starting  *
* the source rendering of a drag item.                                         *
*                                                                              *
* Objects of this class provide all the "query" functions inherited from       *
* IDMSourceRenderEvent.  In addition, functions are provided to provide        *
* return information to the target:                                            *
*   o an alternate source window that the target should communicate with       *
*     during rendering                                                         *
*   o two result flags indicating whether rendering should be done by the      *
*     target and/or whether the target should retry with a different           *
*     rendering mechanism and format.                                          *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMSourcePrepareEvent ( IEvent &event );
  ~IDMSourcePrepareEvent ( );

/*---------------------------------- Result ------------------------------------
| These functions provide means of specifying render preparation results to    |
| be passed back to the target:                                                |
|   setAlternateWindow   - Sets alternate source window handle.                |
|   targetCanRetry       - Returns current setting of the "retry" flag.        |
|   setTargetCanRetry    - Sets "retry" flag.                                  |
|   noSourceRendering    - Returns current "no source rendering" flag.         |
|   setNoSourceRendering - Sets "no source rendering" flag.                    |
------------------------------------------------------------------------------*/
virtual Boolean
  targetCanRetry    ( ) const,
  noSourceRendering ( ) const;

virtual IDMSourcePrepareEvent
 &setAlternateWindow   ( const IWindowHandle &window ),
 &setTargetCanRetry    ( Boolean              flag ),
 &setNoSourceRendering ( Boolean            flag );

}; // IDMSourcePrepareEvent

class IDMSourceEndEvent : public IDMEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
* These events are sent to the direct manipulation source window when a        *
* target renderer has completed the rendering of a drag item.  One such        *
* event is expected for each of the drag items involved in the direct          *
* manipulation operation.                                                      *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMSourceEndEvent ( IEvent &event );
  ~IDMSourceEndEvent ( );

/*-------------------------------- Accessors -----------------------------------
| These functions provide access to attributes of instances of this class:     |
|   dragItem            - Returns handle of drag item the target has           |
|                         completed rendering of.                              |
|   wasTargetSuccessful - Returns whether target successfully completed its    |
|                         rendering.                                           |
|   dragOperation       - Returns the source drag operation handle for this   |
|                         event.                                              |
------------------------------------------------------------------------------*/
IDMSrcItemHandle
  dragItem ( ) const;

virtual Boolean
  wasTargetSuccessful ( ) const;

IDMSrcOperationHandle
  dragOperation ();

protected:
private: /*------------------------ PRIVATE ----------------------------------*/
IDMSrcOperationHandle
  pDMSrcOpHandle;
}; // IDMSourceEndEvent

class IDMSourceNotifyEvent : public IDMEvent {
/*******************************************************************************
* Events of this class are sent to the source window when the dragged objects  *
* pass over a new potential target window.  The event essentially passes to    *
* the source the result information returned by IDMTargetHandler::enter().     *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMSourceNotifyEvent ( IEvent &event );
  ~IDMSourceNotifyEvent ( );

/*-------------------------------- Accessors -----------------------------------
| These functions provide access to attributes of instances of this class:     |
|   DropIndicator    - Enumeration of possible drop indicator values:          |
|                        ok             - Drop permitted.                      |
|                        notOk          - Not permitted at this location.      |
|                        operationNotOk - Operation(s) not permitted.          |
|                        neverOk        - Not permitted on this window.        |
|   dropIndicator    - Returns target indicator of whether drop is permitted.  |
|   defaultOperation - Returns default operation to be used by target.         |
|   dragOperation    - Returns the source drag operation handle for this event.|
------------------------------------------------------------------------------*/
enum DropIndicator
  {
  ok,
  notOk,
  operationNotOk,
  neverOk
  };

virtual DropIndicator
  dropIndicator ( ) const;

virtual unsigned short
  defaultOperation ( ) const;

IDMSrcOperationHandle
  dragOperation ();

protected:
private: /*------------------------ PRIVATE ----------------------------------*/
IDMSrcOperationHandle
  pDMSrcOpHandle;
DropIndicator
  dropInd;
unsigned short
  op;
}; // IDMSourceNotifyEvent


class IDMTargetEnterEvent : public IDMEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
* Instances of this class encapsulate direct manipulation events that          *
* occur at the target handler when a drag operation enters a potential         *
* target window.  Target handlers access information about the dragged         *
* items from the associated IDMTargetOperation object                          *
*                                                                              *
* The event result field is of particular importance for these event objects.  *
* The result will indicate whether the dragged object(s) can be dropped on     *
* this target, and if so, what the default operation would be.  This class     *
* provides specialized functions to set the components of the event result.    *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMTargetEnterEvent     ( IEvent &event );

  ~IDMTargetEnterEvent    ( );

/*--------------------------------- Accessors ----------------------------------
| These functions provide means of getting and setting the accessible          |
| attributes of instances of this class:                                       |
|   position      - Returns the pointing device position.                      |
|   dragOperation - Returns handle of the target operation object for the      |
|                   target enter event.                                        |
------------------------------------------------------------------------------*/
virtual IPoint
  position         ( ) const;

IDMTgtOperationHandle
  dragOperation    ( ) const;

/*---------------------------------- Result ------------------------------------
| These functions provide means of querying and setting the components of      |
| the event result:                                                            |
|   dropIndicator       - Returns indicator of whether drop is allowed.        |
|   setDropIndicator    - Sets indicator of whether drop is allowed.           |
|   defaultOperation    - Returns the default operation for this target.       |
|   setDefaultOperation - Sets the default operation for this target.          |
------------------------------------------------------------------------------*/
virtual IDMSourceNotifyEvent::DropIndicator
  dropIndicator ( ) const;

virtual unsigned short
  defaultOperation ( ) const;

IDMTargetEnterEvent
 &setDropIndicator    ( IDMSourceNotifyEvent::DropIndicator indicator ),
 &setDefaultOperation ( unsigned short operation );


private: /*------------------------ PRIVATE ----------------------------------*/
IDMTgtOperationHandle
  pDMTgtOpHandle;

IPoint
  pos;

IDMSourceNotifyEvent::DropIndicator
  dropInd;

unsigned short
  op;

}; // IDMTargetEnterEvent

class IDMUMTgtEnterEvent : public IDMEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
* Instances of this class encapsulate direct manipulation events that          *
* occur at the target handler when a drag operation enters a potential         *
* target window.  Target handlers access information about the dragged         *
* items from the associated IDMTargetOperation object                          *
*                                                                              *
* The event result field is of particular importance for these event objects.  *
* The result will indicate whether the dragged object(s) can be dropped on     *
* this target, and if so, what the default operation would be.  This class     *
* provides specialized functions to set the components of the event result.    *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects or         |
| from an IDMTargetEnterEvent object.                                          |
------------------------------------------------------------------------------*/
  IDMUMTgtEnterEvent     ( IEvent &event );

  ~IDMUMTgtEnterEvent    ( );

/*--------------------------------- Accessors ----------------------------------
| These functions provide means of getting and setting the accessible          |
| attributes of instances of this class:                                       |
|   position      - Returns the pointing device position.                      |
|   dragOperation - Returns handle of the target operation object for the      |
|                   target enter event.                                        |
------------------------------------------------------------------------------*/
virtual IPoint
  position         ( ) const;

IDMTgtOperationHandle
  dragOperation    ( ) const;

private: /*------------------------ PRIVATE ----------------------------------*/
IDMTgtOperationHandle
  pDMTgtOpHandle;

IPoint
  pos;

}; // IDMUMTgtEnterEvent

class IDMTargetDropEvent : public IDMEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
* Instances of this class encapsulate direct manipulation events that          *
* occur at the target handler when a drop occurs on a target window.           *
* Target handlers access information about the dragged items from the          *
* stored IDMTargetOperation object that was created as part of the             *
* IDMTargetEnterEvent processing.                                              *
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMTargetDropEvent     ( IEvent &event );

  ~IDMTargetDropEvent    ( );

/*--------------------------------- Accessors ----------------------------------
| This function provides means of getting and setting the accessible           |
| attributes of instances of this class:                                       |
|   dragOperation - Returns handle of the target operation object for the      |
|                   target drop event.                                         |
------------------------------------------------------------------------------*/
IDMTgtOperationHandle
  dragOperation    ( ) const;

private: /*------------------------ PRIVATE ----------------------------------*/
IDMTgtOperationHandle
  pDMTgtOpHandle;

}; // IDMTargetDropEvent


class IDMTargetEndEvent : public IDMSourceRenderEvent {
typedef IDMEvent
  Inherited;
/*******************************************************************************
  These events occur when the source window has completed rendering of a
  given drag item.  The event provides information about the item rendered
  (as per the IDMSourceRenderEvent processed by the source), plus, provides
  result information provided by the source window.
*******************************************************************************/
public:
/*------------------------- Constructors/Destructor ----------------------------
| Objects of this class are constructed from generic IEvent objects.           |
------------------------------------------------------------------------------*/
  IDMTargetEndEvent ( IEvent &event );
  ~IDMTargetEndEvent ( );

/*---------------------------------- Result ------------------------------------
  These functions provide access to rendering result information returned
  by the source window:
    renderingFailed -
    targetCanRetry  -
------------------------------------------------------------------------------*/
virtual Boolean
  renderingFailed ( ) const,
  targetCanRetry  ( ) const;

}; // IDMTargetEndEvent

#ifndef I_NO_INLINES
  #include <idmevent.inl>
#endif

#endif //_IDMEVENT_
