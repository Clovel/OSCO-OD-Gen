/**
 * @brief EDS file class implementation
 * 
 * @file EDS.cpp
 */

/* Includes -------------------------------------------- */
#include "EDS.hpp"
#include "INI.hpp"

#include <string>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Variable declaration -------------------------------- */

/* EDS class implementation ---------------------------- */
EDS::EDS(const std::string &pFile) : INI(pFile) {
    /* Empty */
}

EDS::~EDS() {
    /* Empty */
}

int EDS::reorderEDSSections(void) {
    /* Empty for now */
}

int EDS::checkIfSection(const std::string &pSection) const {
    //
}

int EDS::check(void) const {
    /* Empty for now */

    /* Check for mandatory sections : 
     * - FileInfo
     * - Comments
     * - DeviceInfo
     * - DummyUsage
     * - ManufacturerObjects
     * - OptionalObjects
     * - 1000 (Device Type)
     * - 1001 (Error Register)
     * - 1018 (Identity Object)
     * 
     * Madantory if HB :
     * - 1017 (Producer HB time)
     * else :
     * - 100C (Guard Time)
     * - 100D (Life Time Factor)
     */
    
    if(sectionExists("FileInfo")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("Comments")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("DeviceInfo")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("DummyUsage")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("ManufacturerObjects")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("OptionalObjects")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("1000")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("1001")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("1018")) {
        /* Check for mandatory keys */
    } else {
        return -1;
    }
    
    if(sectionExists("1017")) {
        /* Check for mandatory keys */
    } else {
        /* Producer hartbeat is absent, 
         * check for Node Guarding entries */
        if(sectionExists("100C")
            && sectionExists("100D")) {
            /* Check for mandatory keys */
        } else {
            return -1;
        }
    }
}
