/**
 * @brief OSCO OD Generator class
 * 
 * @file OSCOODGenerator.hpp
 */

#ifndef OSCOODGENERATOR_HPP
#define OSCOODGENERATOR_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

/* C++ system */
#include <exception>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */
class OSCOOD;

/* OSCOODGenerator exception --------------------------- */
class OSCOODGeneratorException : public std::exception {
    virtual const char *what(void) const throw()
    {
        return "OSCOODGenerator exception occured !";
    }
};

/* OSCOODGenerator class ------------------------------- */
class API_EXPORT OSCOODGenerator {
    public:
        static int generate_OSCOGenOD_SourceFiles(const OSCOOD &pOD);
        static int generate_OSCOGenOD_h(const OSCOOD &pOD);
        static int generate_OSCOGenOD_c(const OSCOOD &pOD);
        static int generate_OSCOGenOD_DefaultValues_c(const OSCOOD &pOD);
        static int generate_OSCOGenOD_MaxValues_c(const OSCOOD &pOD);
        static int generate_OSCOGenOD_MinValues_c(const OSCOOD &pOD);
        static int generate_OSCOGenOD_Values_c(const OSCOOD &pOD);
    protected:
    private:
};

#endif /* OSCOODGENERATOR_HPP */
