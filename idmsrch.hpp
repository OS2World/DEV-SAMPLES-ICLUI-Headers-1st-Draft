#ifndef _IDMSRCH_
#define _IDMSRCH_
/*******************************************************************************
* FILE NAME: idmsrch.hpp                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*   Declaration of the class(es):                                              *
*     IDMSourceHandler - Direct manipulation source window handler.            *
*                                                                              *
* COPYRIGHT:                                                                   *
*   Licensed Materials - Property of IBM                                       *
*   (C) Copyright IBM Corporation 1992, 1993                                   *
*   All Rights Reserved                                                        *
*   US Government Users Restricted Rights - Use, duplication, or disclosure    *
*   restricted by GSA ADP Schedule Contract with IBM Corp.                     *
*                                                                              *
* $Log:   S:/ibmclass/idrag/vcs/idmsrch.hpv  $
//
//   Rev 1.1   30 Apr 1993 11:45:42   HAGGAR
//No change.
//
//   Rev 1.0   22 Apr 1993 10:41:12   HAGGAR
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

class IDMSourceHandler : public IDMHandler {
typedef IDMHandler
  Inherited;
/*******************************************************************************
* Objects of this class handle events occuring at source windows in direct     *
* manipulation operations.  An instance of this class (or a derived class)     *
* must be added to any window that will support direct manipulation from       *
* that window.                                                                 *
*                                                                              *
* Example:                                                                     *
* // Create IDragItemProvider object specific to my entry field...             *
* MyDragItemProvider                                                           *
*   provider;                                                                  *
*                                                                              *
* // Define source handler and add to an entry field...                        *
* IDMSourceHandler                                                             *
*   source( provider );                                                        *
*                                                                              *
* IEntryField                                                                  *
*  *pEntryField;                                                               *
*                                                                              *
* source.startHandlingEventsFor( pEntryField );                                *
*******************************************************************************/
public:
typedef ISet<IDMSrcRendererHandle> IDMSourceRendererSet;

/*----------------------- Constructor/Destructor -------------------------------
| Objects of this class are constructed as follows:                            |
------------------------------------------------------------------------------*/
  IDMSourceHandler ( );

  ~IDMSourceHandler ( );

protected:
/*------------------------------ Event Handling --------------------------------
| These functions are dispatched in response to specific direct manipulation   |
| source events:                                                               |
|   setup            - Called to process the initiation of a drag operation    |
|                      and subsequently commence a drag operation.  This is    |
|                      called in response to WM_BEGINDRAG.  The initial        |
|                      processing of this function is to invoke the            |
|                      createIDMSrcOper() function.  Then the                  |
|                      provideDragItems() function of the IDragItemProvider    |
|                      class is envoked to retrieve the items that are to be   |
|                      dragged.  Then the IC_UM_BEGINDRAG message is sent to   |
|                      all source handlers.  If there are items to be dragged, |
|                      the function begin() is called to commence the drag via |
|                      DrgDrag().                                              |
|   assocItmsToRndrs - Called to associate each IDMSourceItem object with an   |
|                      IDMSourceRenderer object that supports the specified    |
|                      Type and RMF.  This is called in response to the        |
|                      IC_UM_BEGINDRAG message.                                |
|   prepareToRender  - Called to indicate to the source that rendering is      |
|                      about to commence.  The default implementation in       |
|                      this class dispatches the prepareToRender() function    |
|                      on the corresponding IDMSourceItem created during       |
|                      setup().                                                |
|   render           - Called to indicate to the source handler to render      |
|                      a given drag item.  The default implementation in       |
|                      this class is to dispatch the render() function on      |
|                      the IDMSourceItem object created during setup().        |
|   endConversation  - Called to indicate that a given item has been processed |
|                      by the target.  The default implementation in this      |
|                      class dispatches the endConversation() function on the  |
|                      corresponding IDMSourceItem object created during       |
|                      setup().  When all the endConversation events have been |
|                      received, then the IDMSourceOperaton object created at  |
|                      setup() will be deleted.                                |
|   dragOverNotify   - Called to indicate that a target window has processed   |
|                      a "target enter" event.  The default implementation in  |
|                      this class takes no action.  Derived classes can use    |
|                      the information received from the target to draw        |
|                      different source emphasis, etc.                         |
------------------------------------------------------------------------------*/
virtual Boolean
  setup            ( IDMSourceBeginEvent   &event ),
  assocItmsToRndrs ( IDMSourceBeginEvent   &event ),
  prepareToRender  ( IDMSourcePrepareEvent &event ),
  render           ( IDMSourceRenderEvent  &event ),
  endConversation  ( IDMSourceEndEvent     &event ),
  dragOverNotify   ( IDMSourceNotifyEvent  &event ),
  begin            ( IDMSourceBeginEvent   &event );

/*------------------------------ Implementation --------------------------------
| The following utility functions are used to implement the behavior of        |
| this class:                                                                  |
|   allocIDMSrcOper     - Creates an instance of the IDMSourceOperation class  |
|                         and returns a pointer to it.                         |
------------------------------------------------------------------------------*/
virtual IDMSrcOperationHandle
  allocIDMSrcOper ( IDMSourceBeginEvent& event ) const;

/*------------------------------ Renderers -------------------------------------
| The following functions provide means of accessing the IDMSourceRenderer     |
| objects involved in the direct manipulation operation.                       |
|   numberOfRenderers - Returns the number of renderers.                       |
|   renderer          - Returns the renderer with given index.                 |
|   replaceRenderer   - Replaces a given renderer with another.                |
|   addRenderer       - Associates another renderer with this operation.       |
|   removeRenderer    - Removes a renderer from the operation.                 |
------------------------------------------------------------------------------*/
unsigned
  numberOfRenderers ( );

IDMSrcRendererHandle
  renderer ( unsigned index );

IDMSourceHandler
 &replaceRenderer ( unsigned             index,
                    IDMSrcRendererHandle replacement ),

 &addRenderer ( IDMSrcRendererHandle newItem ),

 &removeRenderer  ( unsigned   index );

/*------------------------------ Implementation --------------------------------
| The following utility functions are used to implement the behavior of        |
| this class:                                                                  |
|   sendBeginEvent      - Sends IC_UM_BEGINDRAG to the associated window.      |
|   setRenderers        - Sets the pointer to the collection of                |
|                         IDMSourceRenderers.                                  |
|   rendererSetCl       - Returns a pointer to the collection of               |
|                         IDMSourceRenderers.                                  |
------------------------------------------------------------------------------*/
virtual void
  sendBeginEvent ( IDMSourceBeginEvent &beginEvent );
IDMSourceHandler
  &setRenderers ( IDMSourceRendererSet *pIDMSrcRendererSet );
IDMSourceRendererSet
  *rendererSetCl ();

/*-------------------------------- Overrides -----------------------------------
| This class overrides the following inherited functions:                      |
|   dispatchHandlerEvent - Dispatching function; handles drag source events.   |
------------------------------------------------------------------------------*/
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );

private: /*------------------------ PRIVATE ----------------------------------*/
IDMSourceRendererSet
  *pIRendererSetCl;
}; //IDMSourceHandler

#ifndef I_NO_INLINES
  #include <idmsrch.inl>
#endif

#endif //_IDMSRCH_
