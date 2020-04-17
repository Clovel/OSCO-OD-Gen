/**
 * @brief OSCO OD Generator class implementation
 * 
 * @file OSCOODGenerator.cpp
 */

/* Includes -------------------------------------------- */
#include "OSCOODGenerator.hpp"
#include "OSCONode.hpp"
#include "OSCOOD.hpp"
#include "OSCOODIndex.hpp"
#include "OSCOODSubIndex.hpp"
#include "OSCOODObject.hpp"

/* EDSTools */
#include "EDSTools.hpp"

/* FileFiller */
#include "FileFiller.hpp"
#include "FileFillerTagFactory.hpp"

#include "Version.h"

/* C++ system */
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

/* Defines --------------------------------------------- */
/* Template file names */
#define OSCO_GEN_NODEID_H_TEMPLATE_NAME             "OSCOGenNodeID.in.h"
#define OSCO_GEN_OD_H_TEMPLATE_NAME                 "OSCOGenOD.in.h"
#define OSCO_GEN_OD_C_TEMPLATE_NAME                 "OSCOGenOD.in.c"
#define OSCO_GEN_OD_DEFAULTVALUES_C_TEMPLATE_NAME   "OSCOGenOD_DefaultValues.in.c"
#define OSCO_GEN_OD_MAXVALUES_C_TEMPLATE_NAME       "OSCOGenOD_MaxValues.in.c"
#define OSCO_GEN_OD_MINVALUES_C_TEMPLATE_NAME       "OSCOGenOD_MinValues.in.c"
#define OSCO_GEN_OD_VALUES_C_TEMPLATE_NAME          "OSCOGenOD_Values.in.c"

/* Output file names */
#define OSCO_GEN_NODEID_H_NAME              "OSCOGenNodeID.h"
#define OSCO_GEN_OD_H_NAME                  "OSCOGenOD.h"
#define OSCO_GEN_OD_C_NAME                  "OSCOGenOD.c"
#define OSCO_GEN_OD_DEFAULTVALUES_C_NAME    "OSCOGenOD_DefaultValues.c"
#define OSCO_GEN_OD_MAXVALUES_C_NAME        "OSCOGenOD_MaxValues.c"
#define OSCO_GEN_OD_MINVALUES_C_NAME        "OSCOGenOD_MinValues.c"
#define OSCO_GEN_OD_VALUES_C_NAME           "OSCOGenOD_Values.c"

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* Static variable declarations ------------------------ */
static std::string sOSCOODElementStructTemplate =
R"=====(/* @@OBJECT_NAME@@ */
{
    @@OBJECT_INDEX@@,
    @@OBJECT_SUBINDEX@@,
    @@OBJECT_TYPE@@,
    @@OBJECT_ACCESS_SETTINGS@@,
    @@OBJECT_VAL_PTR@@,
    @@OBJECT_DEFAULT_VAL_PTR@@,
    @@OBJECT_MAX_VAL_PTR@@,
    @@OBJECT_MIN_VAL_PTR@@,
}
")=====";

static size_t objValU8Counter  = 0U;
static size_t objValU16Counter = 0U;
static size_t objValU32Counter = 0U;
static size_t objValU64Counter = 0U;

static size_t maxValU8Counter  = 0U;
static size_t maxValU16Counter = 0U;
static size_t maxValU32Counter = 0U;
static size_t maxValU64Counter = 0U;

static size_t minValU8Counter  = 0U;
static size_t minValU16Counter = 0U;
static size_t minValU32Counter = 0U;
static size_t minValU64Counter = 0U;

static size_t defValU8Counter  = 0U;
static size_t defValU16Counter = 0U;
static size_t defValU32Counter = 0U;
static size_t defValU64Counter = 0U;

/* Helper functions ------------------------------------ */
static void initializeCounters(void) {
    objValU8Counter  = 0U;
    objValU16Counter = 0U;
    objValU32Counter = 0U;
    objValU64Counter = 0U;

    maxValU8Counter  = 0U;
    maxValU16Counter = 0U;
    maxValU32Counter = 0U;
    maxValU64Counter = 0U;

    minValU8Counter  = 0U;
    minValU16Counter = 0U;
    minValU32Counter = 0U;
    minValU64Counter = 0U;

    defValU8Counter  = 0U;
    defValU16Counter = 0U;
    defValU32Counter = 0U;
    defValU64Counter = 0U;
}

static int buildOSCOODElementStructString(OSCOODObject &pObj, size_t pObjCounter, std::string &pOut) {
    std::ostringstream lOSS(std::ostream::ate);

    enum {
        OBJECT = 0U,
        INDEX,
        SUB_INDEX
    } lObjClassType = OBJECT;

    /* Is the object an Index or a subIndex ? */
    OSCOODIndex    *lIndexObj    = nullptr;
    OSCOODSubIndex *lSubIndexObj = nullptr;
    if(nullptr != (lIndexObj = dynamic_cast<OSCOODIndex *>(&pObj))) {
        /* Is an OSCOODIndex */
        lObjClassType = INDEX;
        if(0 < lIndexObj->subIndexCount()) {
            std::cerr << "[ERROR] <buildOSCOODElementStructString> Object is an Index containing subindexes." << std::endl;
            return -1;
        }
    } else if (nullptr != (lSubIndexObj = dynamic_cast<OSCOODSubIndex *>(&pObj))) {
        /* Is an OSCOODSubIndex */
        lObjClassType = SUB_INDEX;
    } else {
        /* Is neither, this shouldn't be possible */
        std::cerr << "[ERROR] <buildOSCOODElementStructString> Invalid object class type." << std::endl;
        return -1;
    }

    uint16_t lIndexInt    = nullptr == lSubIndexObj ? lIndexObj->index() : lSubIndexObj->index();
    uint8_t  lSubIndexInt = nullptr == lSubIndexObj ? 0x00U              : lSubIndexObj->subIndex();

    ++pObjCounter;

    /* Description comment */
    lOSS << "OBJECT_NAME;" << pObj.paramName() << ";" << std::endl;
    lOSS << "OBJECT_INDEX;" << uint16ToHexStr(lIndexInt) << ";" << std::endl;
    lOSS << "OBJECT_SUBINDEX;" << uint8ToHexStr(lSubIndexInt) << ";" << std::endl;
    lOSS << "OBJECT_ACCESS_SETTINGS;" << pObj.accessType() << ";" << std::endl;
    lOSS << "OBJECT_TYPE;" << pObj.dataType() << ";" << std::endl;
    lOSS << "OBJECT_VAL_PTR;(void *)(objValU32 + " << ";" << std::endl;

}

/* OSCOODGenerator class implementation ---------------- */
int OSCOODGenerator::generate_OSCOGenOD_SourceFiles(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    /* Generate main generated OD header */
    if(0 > (lResult = generate_OSCOGenOD_h(pTemplateFilePath, pOutputPath, pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD source file */
    if(0 > (lResult = generate_OSCOGenOD_c(pTemplateFilePath, pOutputPath, pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD default values source file */
    if(0 > (lResult = generate_OSCOGenOD_DefaultValues_c(pTemplateFilePath, pOutputPath, pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD max values source file */
    if(0 > (lResult = generate_OSCOGenOD_MaxValues_c(pTemplateFilePath, pOutputPath, pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD min values source file */
    if(0 > (lResult = generate_OSCOGenOD_MinValues_c(pTemplateFilePath, pOutputPath, pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD value header */
    if(0 > (lResult = generate_OSCOGenOD_Values_c(pTemplateFilePath, pOutputPath, pOD))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_SourceFiles> generate_OSCOGenOD_h failed" << std::endl;
        return lResult;
    }

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenNode_SourceFiles(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCONode &pNode) {
    int lResult = 0;

    /* Generate main generated OD header */
    if(0 > (lResult = generate_OSCOGenOD_SourceFiles(pTemplateFilePath, pOutputPath, pNode))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenNode_SourceFiles> generate_OSCOGenOD_SourceFiles failed" << std::endl;
        return lResult;
    }

    /* Generate main generated OD value header */
    if(0 > (lResult = generate_OSCOGenNodeID_h(pTemplateFilePath, pOutputPath, pNode))) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenNode_SourceFiles> generate_OSCOGenNodeID_h failed" << std::endl;
        return lResult;
    }

    return 0; /* Or lResult ? */
}

int OSCOODGenerator::generate_OSCOGenOD_h(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    /* Build the mapping string using an output string stream */
    std::ostringstream lOSS(std::ios_base::ate);

    /* Custom include file */
    if(pOD.customHeader().empty()) {
        lOSS << "CUSTOM_OD_DEFINE_INCLUDE;" << LINE_REMOVAL_VAL <<";" << std::endl;
    } else {
        lOSS << "CUSTOM_OD_DEFINE_INCLUDE;" << "#include \"" << pOD.customHeader() << "\";" << std::endl;
    }

    /* OD description defines */
    if(pOD.name().empty()) {
        lOSS << "OD_NAME_DOXYGEN;" << "Untitled" << ";" << std::endl;
    } else {
        lOSS << "OD_NAME_DOXYGEN;" << pOD.name() << ";" << std::endl;
    }
    if(pOD.name().empty()) {
        lOSS << "OD_NAME;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "OD_NAME;\"" << pOD.name() << "\";" << std::endl;
    }
    if(pOD.name().empty()) {
        lOSS << "OD_SOURCE_FILE;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "OD_SOURCE_FILE;\"" << pOD.sourceFilePath() << "\";" << std::endl;
    }
    if(pOD.description().empty()) {
        lOSS << "OD_DESCRIPTION;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "OD_DESCRIPTION;\"" << pOD.description() << "\";" << std::endl;
    }

    /* OSCO OD Generator defines */
    lOSS << "OSCO_OD_GEN_VERSION_MAJOR;" << OSCO_OD_GEN_VERSION_MAJOR << ";" << std::endl;
    lOSS << "OSCO_OD_GEN_VERSION_MINOR;" << OSCO_OD_GEN_VERSION_MINOR << ";" << std::endl;
    lOSS << "OSCO_OD_GEN_VERSION_PATCH;" << OSCO_OD_GEN_VERSION_PATCH << ";" << std::endl;

    /* DeviceInfo defines */
    if(pOD.vendorName().empty()) {
        lOSS << "VENDOR_NAME;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "VENDOR_NAME;\"" << pOD.vendorName() << "\";" << std::endl;
    }
    lOSS << "VENDOR_NUMBER;0x" << std::hex << pOD.vendorNumber() << std::dec << ";" << std::endl;
    if(pOD.productName().empty()) {
        lOSS << "PRODUCT_NAME;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "PRODUCT_NAME;\"" << pOD.productName() << "\";" << std::endl;
    }
    lOSS << "PRODUCT_NUMBER;0x" << std::hex << pOD.productNumber() << std::dec << ";" << std::endl;
    lOSS << "REVISION_NUMBER;" << pOD.revisionNumber() << ";" << std::endl;
    if(pOD.orderCode().empty()) {
        lOSS << "ORDER_CODE;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "ORDER_CODE;\"" << pOD.orderCode() << "\";" << std::endl;
    }
    lOSS << "BAUDRATE_10;" << pOD.baudrate10Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_20;" << pOD.baudrate20Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_50;" << pOD.baudrate50Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_125;" << pOD.baudrate125Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_250;" << pOD.baudrate250Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_500;" << pOD.baudrate500Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_800;" << pOD.baudrate800Supported() << ";" << std::endl;
    lOSS << "BAUDRATE_1000;" << pOD.baudrate1000Supported() << ";" << std::endl;
    lOSS << "SIMPLE_BOOT_UP_MASTER;" << pOD.simpleBootUpMaster() << ";" << std::endl;
    lOSS << "SIMPLE_BOOT_UP_SLAVE;" << pOD.simpleBootUpSlave() << ";" << std::endl;
    lOSS << "GRANULARITY;" << (uint16_t)pOD.granularity() << ";" << std::endl;
    lOSS << "DYN_CHANNELS_SUPPORTED;" << (uint16_t)pOD.dynamicChannelsSupported() << ";" << std::endl;
    lOSS << "GROUP_MESSAGING;" << pOD.groupMessaging() << ";" << std::endl;
    lOSS << "LSS_SUPPORTED;" << pOD.LSSSupported() << ";" << std::endl;

    /* OD Comments defines */
    lOSS << "OD_COMMENTS_LINES;" << pOD.commentLineCount() << ";" << std::endl;
    if(pOD.comments().empty()) {
        lOSS << "OD_COMMENTS;" << LINE_REMOVAL_VAL << ";" << std::endl;
    } else {
        lOSS << "OD_COMMENTS;\"" << pOD.comments() << "\";" << std::endl;
    }

    /* DummyUsage defines */
    lOSS << "OD_DUMMY_0001_SUPPORTED;" << pOD.dummy0001Supported() << ";" << std::endl;
    lOSS << "OD_DUMMY_0002_SUPPORTED;" << pOD.dummy0002Supported() << ";" << std::endl;
    lOSS << "OD_DUMMY_0003_SUPPORTED;" << pOD.dummy0003Supported() << ";" << std::endl;
    lOSS << "OD_DUMMY_0004_SUPPORTED;" << pOD.dummy0004Supported() << ";" << std::endl;
    lOSS << "OD_DUMMY_0005_SUPPORTED;" << pOD.dummy0005Supported() << ";" << std::endl;
    lOSS << "OD_DUMMY_0006_SUPPORTED;" << pOD.dummy0006Supported() << ";" << std::endl;
    lOSS << "OD_DUMMY_0007_SUPPORTED;" << pOD.dummy0007Supported() << ";" << std::endl;

    /* OD Content defines */
    lOSS << "OD_OBJECT_COUNT;" << pOD.objectCount() << ";" << std::endl; /* TODO */
    lOSS << "OD_RPDO_COUNT;" << pOD.nrOfRPDOs() <<";" << std::endl;
    lOSS << "OD_TPDO_COUNT;" << pOD.nrOfTPDOs() <<";" << std::endl;
    lOSS << "OD_SDO_SERVER;" << LINE_REMOVAL_VAL << ";" << std::endl; /* TODO */
    lOSS << "OD_SDO_CLIENT;" << LINE_REMOVAL_VAL << ";" << std::endl; /* TODO */

    /* Get tag mapping string from the stringstream */
    const std::string lTagMappingStr = lOSS.str();

    std::cout << "[DEBUG] <OSCOODGenerator::generate_OSCOGenOD_h> Tag mapping string : " << std::endl << lTagMappingStr << std::endl;

    /* Generate the tag map */
    std::map<std::string, std::string> lTagMap;
    lResult = FileFillerTagFactory::buildTagMap(lTagMappingStr, lTagMap);
    if(0 > lResult) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_h> FileFillerTagFactory::buildTagMap failed" << std::endl;
        return lResult;
    }

    const std::string lTemplateFilePath = pTemplateFilePath + '/' + OSCO_GEN_OD_H_TEMPLATE_NAME;
    const std::string lOutputFilePath = pOutputPath + '/' + OSCO_GEN_OD_H_NAME;

    /* Parse the template and generate the code */
    std::string lTemp = ""; /* TODO Remove need for the output string in FileFiller */
    lResult = FileFiller::parseFile(lTagMap, lTemplateFilePath, lOutputFilePath, &lTemp);
    if(0 > lResult) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_h> FileFiller::parseFile failed" << std::endl;
        return lResult;
    }

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenODContents(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    (void)pTemplateFilePath;
    (void)pOutputPath;
    (void)pOD;

    /* Initialize counters */
    initializeCounters();

    /* Build the mapping string using an output string stream */
    std::ostringstream lOSS_Values(std::ios_base::ate);
    std::ostringstream lOSS_MaxValues(std::ios_base::ate);
    std::ostringstream lOSS_MinValues(std::ios_base::ate);
    std::ostringstream lOSS_DefaultValues(std::ios_base::ate);

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_c(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    (void)pTemplateFilePath;
    (void)pOutputPath;
    (void)pOD;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_DefaultValues_c(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    (void)pTemplateFilePath;
    (void)pOutputPath;
    (void)pOD;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_MaxValues_c(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    (void)pTemplateFilePath;
    (void)pOutputPath;
    (void)pOD;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_MinValues_c(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    (void)pTemplateFilePath;
    (void)pOutputPath;
    (void)pOD;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenOD_Values_c(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCOOD &pOD) {
    int lResult = 0;

    (void)pTemplateFilePath;
    (void)pOutputPath;
    (void)pOD;

    return lResult;
}

int OSCOODGenerator::generate_OSCOGenNodeID_h(const std::string &pTemplateFilePath, const std::string &pOutputPath, const OSCONode &pNode) {
    int lResult = 0;

    /* Build the mapping string using an output string stream */
    std::ostringstream lOSS(std::ios_base::ate);

    lOSS << "NODE_ID;" << (uint16_t)pNode.nodeID() << ";" << std::endl;

    /* Get tag mapping string from the stringstream */
    const std::string lTagMappingStr = lOSS.str();

    std::cout << "[DEBUG] <OSCOODGenerator::generate_OSCOGenOD_h> Tag mapping string : " << std::endl << lTagMappingStr << std::endl;

    /* Generate the tag map */
    std::map<std::string, std::string> lTagMap;
    lResult = FileFillerTagFactory::buildTagMap(lTagMappingStr, lTagMap);
    if(0 > lResult) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_h> FileFillerTagFactory::buildTagMap failed" << std::endl;
        return lResult;
    }

    const std::string lTemplateFilePath = pTemplateFilePath + '/' + OSCO_GEN_NODEID_H_TEMPLATE_NAME;
    const std::string lOutputFilePath = pOutputPath + '/' + OSCO_GEN_NODEID_H_NAME;

    /* Parse the template and generate the code */
    std::string lTemp = ""; /* TODO Remove need for the output string in FileFiller */
    lResult = FileFiller::parseFile(lTagMap, lTemplateFilePath, lOutputFilePath, &lTemp);
    if(0 > lResult) {
        std::cerr << "[ERROR] <OSCOODGenerator::generate_OSCOGenOD_h> FileFiller::parseFile failed" << std::endl;
        return lResult;
    }

    return lResult;
}
