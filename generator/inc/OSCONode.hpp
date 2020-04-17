/**
 * @brief OSCONode class
 * 
 * @file OSCONode.hpp
 */

#ifndef OSCONODE_HPP
#define OSCONODE_HPP

/* Includes -------------------------------------------- */
#include "OSCOOD.hpp"

/* Library/API export defines */
#include "APIExports.h"

/* C System */
#include <cstdint>

/* Defines --------------------------------------------- */
#define CANOPEN_NODE_ID_MIN 1U
#define CANOPEN_NODE_ID_MAX 127U

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* OSCOOD exception ------------------------------------ */
class OSCONodeException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "OSCONode exception occured !";
    }
};

/* OSCONode class -------------------------------------- */
class API_EXPORT OSCONode : public OSCOOD {
    public:
        /* Constructors */
        OSCONode();
        OSCONode(const uint8_t &pNodeID);
        OSCONode(const uint8_t &pNodeID, const std::map<uint16_t, OSCOODIndex *> &pObjects);
        OSCONode(const uint8_t &pNodeID, const std::vector<OSCOODIndex *> &pObjects);

        /**
         * @brief This copy constructor can take the ownership of the
         * OSCOODIndex opbjects contained within the source OSCOOD instance.
         * 
         * @details Using the pTakeOwnership parameter, you can take
         * or not the ownership of the OSCOODIndex contained in the source
         * OSCOOD instance.
         * 
         * @param[in]   pOD             Source OSCOOD instance to copy.
         * @param[in]   pNodeID         Node ID
         * @param[in]   pTakeOwnership  Weither to take ownership or not.
         *  `true` by default
         */
        OSCONode(OSCOOD &pOD, const uint8_t &pNodeID = 0U, const bool &pTakeOwnership = true);

        /**
         * @brief This copy constructor can take the ownership of the
         * OSCOODIndex opbjects contained within the source OSCONode instance.
         * 
         * @details Using the pTakeOwnership parameter, you can take
         * or not the ownership of the OSCOODIndex contained in the source
         * OSCONode instance.
         * 
         * @param[in]   pNode           Source OSCONode instance to copy.
         * @param[in]   pTakeOwnership  Weither to take ownership or not.
         *  `true` by default
         */
        OSCONode(OSCONode &pNode, const bool &pTakeOwnership = true);

        /* Destructor */
        virtual ~OSCONode();

        /* Getters */
        uint8_t nodeID(void) const;
        bool nodeIDValidity(void) const;

        /* Setters */
        bool setNodeID(const uint8_t &pNodeID);

    protected:
    private:
        uint8_t mNodeID;
        bool    mNodeIDValid;
};

#endif /* OSCONODE_HPP */
