/**
 * @brief OSCONode class implementation
 * 
 * @file OSCONode.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCONode.hpp"

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
    if(!setNodeID(pNodeID)) {
        throw OSCONodeException();
    }
}

OSCONode::OSCONode(const uint8_t &pNodeID, const std::map<uint16_t, OSCOODIndex *> &pObjects) :
    OSCOOD(pObjects)
{
    if(!setNodeID(pNodeID)) {
        throw OSCONodeException();
    }
}

OSCONode::OSCONode(const uint8_t &pNodeID, const std::vector<OSCOODIndex *> &pObjects) :
    OSCOOD(pObjects)
{
    if(!setNodeID(pNodeID)) {
        throw OSCONodeException();
    }
}


/* Destructor */
OSCONode::~OSCONode() {
    /* Empty */
}

/* Getters */
uint8_t OSCONode::nodeID(void) const {
    return mNodeID;
}

/* Setters */
bool OSCONode::setNodeID(const uint8_t &pNodeID) {
    if(0U < pNodeID && 128U > pNodeID) {
        mNodeID = pNodeID;
        return true;
    } else return false;
}
