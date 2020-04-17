/**
 * @brief OSCONode class implementation
 * 
 * @file OSCONode.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCONode.hpp"
#include "OSCOOD.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* OSCONode class implementation ----------------------- */
/* Constructors */
OSCONode::OSCONode() : OSCOOD(), mNodeID(0U)
{
    /* Empty */
}

OSCONode::OSCONode(const uint8_t &pNodeID) :
    OSCOOD()
{
    (void)setNodeID(pNodeID);
}

OSCONode::OSCONode(const uint8_t &pNodeID, const std::map<uint16_t, OSCOODIndex *> &pObjects) :
    OSCOOD(pObjects)
{
    (void)setNodeID(pNodeID);
}

OSCONode::OSCONode(const uint8_t &pNodeID, const std::vector<OSCOODIndex *> &pObjects) :
    OSCOOD(pObjects)
{
    (void)setNodeID(pNodeID);
}

OSCONode::OSCONode(OSCOOD &pOD, const uint8_t &pNodeID, const bool &pTakeOwnership) :
    OSCOOD(pOD, pTakeOwnership)
{
    (void)setNodeID(pNodeID);
}

OSCONode::OSCONode(OSCONode &pNode, const bool &pTakeOwnership) :
    OSCONode(pNode, pNode.nodeID(), pTakeOwnership)
{
    /* Empty */
}

/* Destructor */
OSCONode::~OSCONode() {
    /* Empty */
}

/* Getters */
uint8_t OSCONode::nodeID(void) const {
    return mNodeID;
}

bool OSCONode::nodeIDValidity(void) const {
    return mNodeIDValid;
}

/* Setters */
bool OSCONode::setNodeID(const uint8_t &pNodeID) {
    mNodeID = pNodeID;
    if(CANOPEN_NODE_ID_MIN <= pNodeID && CANOPEN_NODE_ID_MAX >= pNodeID)
        mNodeIDValid = true;
    else
        mNodeIDValid = false;
    
    return mNodeIDValid;
}
