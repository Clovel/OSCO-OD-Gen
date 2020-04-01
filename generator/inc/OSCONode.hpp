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

        /* Destructor */
        virtual ~OSCONode();

        /* Getters */
        uint8_t nodeID(void) const;

        /* Setters */
        bool setNodeID(const uint8_t &pNodeID);

    protected:
    private:
        uint8_t mNodeID;
};

#endif /* OSCONODE_HPP */