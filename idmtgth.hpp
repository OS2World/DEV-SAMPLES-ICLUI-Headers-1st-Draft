#ifndef _IDMTGTH_
#define _IDMTGTH_
/*******************************************************************************
* FILE NAME: idmtgth.hpp                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Declaration of the class(es):                                              *
*     IDMTargetHandler - Drag/Drop target window handler.                      *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or disclosure    *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   M:/ibmclass/idrag/vcs/idmtgth.hpv  $
//
//   Rev 1.3   05 May 1993 16:37:44   unknown
//DM_DROP changes
//
//   Rev 1.2   03 May 1993 16:06:06   unknown
//Latest changes per IC_UM_DRAGOVER
//
//   Rev 1.1   30 Apr 1993 11:45:46   HAGGAR
//
//   Rev 1.0   22 Apr 1993 10:41:16   HAGGAR
//Initial revision.
*******************************************************************************/
#ifndef _IDMHNDLR_
  #include <idmhndlr.hpp>
#endif

#ifndef _IDMEVENT_
  #include <idmevent.hpp>
#endif

#ifndef _IDMRENDR_
  #include <idmrendr.hpp>
#endif

#ifndef _ISET_H
  #include <iset.h>
#endif

/* Forward Declarations */
class IEvent;
class IDMTargetEnterEvent;
class IDMSourceNotifyEvent;
class IDMTargetDropEvent;
class IDMTargetEndEvent;
class IDMTargetRenderer;

#define IC_UM_DRAGOVER  WM_USER + 2

class IDMTargetHandler : public IDMHandler {
typedef IDMHandler
  Inherited;
/*******************************************************************************
* Objects of this class handle events occurring at target windows in direct    *
* manipulation operations.  An instance of this class (or a derived class)     *
* must be added to any window that will support direct manipulation to that    *
* window.                                                                      *
*                                                                              *
* Example:                                                                     *
*                                                                              *
* // Define target handler and add to an entry field...                        *
* IDragTargetHandler                                                           *
*   target;                                                                    *
*                                                                              *
* IEntryField                                                                  *
*  *pEntryField;                                                               *
*                                                                              *
* target.startHandlingEventsFor( pEntryField );                                *
*******************************************************************************/
public:
typedef ISequence<IDMTgtRendererHandle> IDMTgtRendererSeq;

/*------------------------ Constructor/Destructor ------------------------------
| Generic objects of this class are constructed without formal parameters.     |
------------------------------------------------------------------------------*/
  IDMTargetHandler     ( );
  ~IDMTargetHandler    ( );

protected:

/*------------------------------ Event Handling --------------------------------
| These functions are dispatched in response to specific direct manipulation   |
| target events:                                                               |
|   dragOver       - Called when dragged objects are moved over the target     |
|                    window.                                                   |
|   dragLeave      - Called when the dragged objects are moved off the target  |
|                    window.                                                   |
|   drop           - Called when the dragged objects are dropped on the        |
|                    target window.                                            |
|   renderComplete - Called when the source has completed rendering of a       |
|                    particular dragged object.                                |
|   dropHelp       - Called when the user has requested help while dragging    |
|                    over the target window.                                   |
------------------------------------------------------------------------------*/
virtual Boolean
  dragOver          ( IDMTargetEnterEvent  &event ),

  dragLeave         ( IDMSourceNotifyEvent &event ),
  drop              ( IDMTargetDropEvent   &event ),
  dropHelp          ( IDMSourceNotifyEvent &event ),

  renderComplete    ( IDMTargetEndEvent    &event );

/*-------------------------------- Rendering -----------------------------------
  These functions permit specificiation of "renderer" objects that will be
  used to handle rendering of dropped objects of compatible types:
    addRenderer    - Adds an IDMTargetRenderer object to the set of such
                     objects maintained for this target handler.
    removeRenderer - Removes an IDMTargetRenderer object from the set.
    findRenderers  - Identifies renderers for a given set of dragged objects,
    renderers      - Returns pointer to collection of IDMTargetRenderer objects.
    setRenderers   - Sets pointer to collection of IDMTargetRenderer objects.
------------------------------------------------------------------------------*/
//pfh - not implemented virtual IDMTargetHandler
// &addRenderer       ( IDMTargetRenderer &aRenderer ),
// &removeRenderer    ( IDMTargetRenderer &aRenderer ),
// &setRenderers      ( IDMTgtRendererSeq *renderers );

IDMTgtRendererSeq
 *renderers ( );

/*------------------------------ Implementation --------------------------------
| The following utility functions are used to implement the behavior of        |
| this class:                                                                  |
------------------------------------------------------------------------------*/

/*-------------------------------- Overrides -----------------------------------
| This class overrides the following inherited functions:                      |
|   dispatchHandlerEvent - Dispatching function; handles drag target events.   |
------------------------------------------------------------------------------*/
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );

private: /*------------------------ PRIVATE ----------------------------------*/

Boolean
  assocItmsToRndrs(IDMUMTgtEnterEvent& tgtEnterEvt);

IDMTgtRendererSeq
 *pTgtRenderersCl;

}; // IDMTargetHandler

#ifndef I_NO_INLINES
  #include <idmtgth.inl>
#endif

#endif // _IDMTGTH_
