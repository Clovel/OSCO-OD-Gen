/**
 * @brief JSONFactory class implementation
 * 
 * @file JSONFactory.hpp
 */

/* Includes -------------------------------------------- */
#include "JSONFactory.hpp"

#include "OSCONode.hpp"
#include "OSCOOD.hpp"
#include "OSCOODIndex.hpp"
#include "OSCOODSubIndex.hpp"
#include "OSCOODObject.hpp"

/* RapidJSON */
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

/* C++ system */
#include <string>
#include <iostream>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Static functions ------------------------------------ */
/**
 * @brief Static common allocator for the whole factory.
 * This avoids segmentation faults.
 */
static rapidjson::MemoryPoolAllocator<> sJsonAlloc;

/* JSONFactory class implementation -------------------- */
std::string JSONFactory::OSCOODObjectToJSON(const OSCOODObject &pObj, rapidjson::Document * const pDoc) {
    rapidjson::Document *lDoc = nullptr;
    if(nullptr == pDoc) {
        /* Create a RapidJSON Document */
        lDoc = new rapidjson::Document(rapidjson::kObjectType);
    } else {
        lDoc = pDoc;
    }

    /* Get the object's contents */
    /* SubNumber */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.subNumber());
        lDoc->AddMember("SubNumber", lVal, sJsonAlloc);
    }
    /* ParameterName */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.paramName().c_str(), pObj.paramName().size(), sJsonAlloc);
        lDoc->AddMember("ParameterName", lVal, sJsonAlloc);
    }
    /* ObjectType */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.objectType());
        lDoc->AddMember("ObjectType", lVal, sJsonAlloc);
    }
    /* DataType */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.dataType());
        lDoc->AddMember("DataType", lVal, sJsonAlloc);
    }
    /* AccessType */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.accessType().c_str(), pObj.accessType().size(), sJsonAlloc);
        lDoc->AddMember("AccessType", lVal, sJsonAlloc);
    }
    /* DefaultValue */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.defaultValue().c_str(), pObj.defaultValue().size(), sJsonAlloc);
        lDoc->AddMember("DefaultValue", lVal, sJsonAlloc);
    }
    /* LowLimit */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.lowLimit().c_str(), pObj.lowLimit().size(), sJsonAlloc);
        lDoc->AddMember("LowLimit", lVal, sJsonAlloc);
    }
    /* HighLimit */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.highLimit().c_str(), pObj.highLimit().size(), sJsonAlloc);
        lDoc->AddMember("HighLimit", lVal, sJsonAlloc);
    }
    /* PDOMapping */
    {
        rapidjson::Value lVal;
        lVal.SetBool(pObj.pdoMapping());
        lDoc->AddMember("PDOMapping", lVal, sJsonAlloc);
    }
    /* ObjFlags */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.objFlags());
        lDoc->AddMember("ObjFlags", lVal, sJsonAlloc);
    }
    /* CompactSubObj */
    {
        rapidjson::Value lVal;
        lVal.SetBool(pObj.compactSubObj());
        lDoc->AddMember("CompactSubObj", lVal, sJsonAlloc);
    }

    std::string lOutput = "";
    if(nullptr == pDoc) {
        /* Create a StringBuffer */
        rapidjson::StringBuffer lStrBuf;
        /* Create a Writer to convert the Document to a string */
        rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
        /* Set the writer as a handler for the Document */
        lDoc->Accept(lWriter);

        /* Create output string */
        lOutput = std::string(lStrBuf.GetString()) + "\r\n";

        //std::cout << "[DEBUG] <JSONFactory::OSCOODObjectToJSON> JSON : " << lOutput << std::endl;

        delete lDoc;
    }

    return lOutput;
}

std::string JSONFactory::OSCOODSubIndexToJSON(const OSCOODSubIndex &pSubIdx, rapidjson::Document * const pDoc) {
    rapidjson::Document *lDoc = nullptr;
    if(nullptr == pDoc) {
        /* Create a RapidJSON Document */
        lDoc = new rapidjson::Document(rapidjson::kObjectType);
    } else {
        lDoc = pDoc;
    }

    /* Get the Object's contents */
    (void)OSCOODObjectToJSON((OSCOODObject)pSubIdx, lDoc);

    if(!lDoc->IsObject()) {
        std::cerr << "[ERROR] <JSONFactory::OSCOODSubIndexToJSON> Got invalid JSON from OSCOODObjectToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }

    /* Get Index */
    {
        rapidjson::Value lVal;
        char lBuf[7U];
        std::memset(lBuf, 0, 7U);
        snprintf(lBuf, 7U, "0x%04X", pSubIdx.index());
        lVal.SetString(lBuf, 6U, sJsonAlloc);
        lDoc->AddMember("Index", lVal, sJsonAlloc);
    }
    /* Get SubIndex */
    {
        rapidjson::Value lVal;
        char lBuf[5U];
        std::memset(lBuf, 0, 5U);
        snprintf(lBuf, 5U, "0x%02X", (uint16_t)pSubIdx.subIndex());
        lVal.SetString(lBuf, 4U, sJsonAlloc);
        lDoc->AddMember("SubIndex", lVal, sJsonAlloc);
    }
    /* Add OSCO type */
    {
        rapidjson::Value lVal;
        lVal.SetString("OSCOODSubIndex", std::strlen("OSCOODSubIndex"), sJsonAlloc);
        lDoc->AddMember("OSCO Type", lVal, sJsonAlloc);
    }

    std::string lOutput = "";
    if(nullptr == pDoc) {
        /* Create a StringBuffer */
        rapidjson::StringBuffer lStrBuf;
        /* Create a Writer to convert the Document to a string */
        rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
        /* Set the writer as a handler for the Document */
        lDoc->Accept(lWriter);

        /* Create output string */
        lOutput = std::string(lStrBuf.GetString()) + "\r\n";

        //std::cout << "[DEBUG] <JSONFactory::OSCOODSubIndexToJSON> JSON : " << lOutput << std::endl;

        delete lDoc;
    }

    return lOutput;
}

std::string JSONFactory::OSCOODIndexToJSON(const OSCOODIndex &pIdx, rapidjson::Document * const pDoc) {
    rapidjson::Document *lDoc = nullptr;
    if(nullptr == pDoc) {
        /* Create a RapidJSON Document */
        lDoc = new rapidjson::Document(rapidjson::kObjectType);
    } else {
        lDoc = pDoc;
    }

    /* Get the Object's contents */
    (void)OSCOODObjectToJSON((OSCOODObject)pIdx, lDoc);

    if(!lDoc->IsObject()) {
        std::cerr << "[ERROR] <JSONFactory::OSCOODIndexToJSON> Got invalid JSON from OSCOODObjectToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }

    /* Get Index */
    {
        rapidjson::Value lVal;
        char lBuf[7U];
        std::memset(lBuf, 0, 7U);
        snprintf(lBuf, 7U, "0x%04X", pIdx.index());
        lVal.SetString(lBuf, 6U, sJsonAlloc);
        lDoc->AddMember("Index", lVal, sJsonAlloc);
    }
    /* Get SubIdexes */
    {
        rapidjson::Value lVal(rapidjson::kArrayType);

        /* Go through every SubIndex */
        for(const auto &lElmt : pIdx.subIndexes()) {
            rapidjson::Document lSubDoc(rapidjson::kObjectType);
            (void)OSCOODSubIndexToJSON(*lElmt.second, &lSubDoc);

            if(!lSubDoc.IsObject()) {
                std::cerr << "[ERROR] <JSONFactory::OSCOODIndexToJSON> Got invalid sub JSON from OSCOODSubIndexToJSON" << std::endl;
                return "[ERROR OCCURED]";
            }

            /* Add the Document to the array */
            lVal.PushBack(lSubDoc, sJsonAlloc);
        }

        /* Add the array of objects as a member of the main JSON doc */
        lDoc->AddMember("SubIndexes", lVal, sJsonAlloc);
    }
    /* Add OSCO type */
    {
        rapidjson::Value lVal;
        lVal.SetString("OSCOODIndex", std::strlen("OSCOODIndex"), sJsonAlloc);
        lDoc->AddMember("OSCO Type", lVal, sJsonAlloc);
    }

    std::string lOutput = "";
    if(nullptr == pDoc) {
        /* Create a StringBuffer */
        rapidjson::StringBuffer lStrBuf;
        /* Create a Writer to convert the Document to a string */
        rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
        /* Set the writer as a handler for the Document */
        lDoc->Accept(lWriter);

        /* Create output string */
        lOutput = std::string(lStrBuf.GetString()) + "\r\n";

        //std::cout << "[DEBUG] <JSONFactory::OSCOODIndexToJSON> JSON : " << lOutput << std::endl;

        delete lDoc;
    }

    return lOutput;
}

std::string JSONFactory::OSCOODToJSON(const OSCOOD &pOD, rapidjson::Document * const pDoc) {
    rapidjson::Document *lDoc = nullptr;
    if(nullptr == pDoc) {
        /* Create a RapidJSON Document */
        lDoc = new rapidjson::Document(rapidjson::kObjectType);
    } else {
        lDoc = pDoc;
    }

    /* Get OD name */
    {
        rapidjson::Value lVal;
        lVal.SetString(pOD.name().c_str(), pOD.name().size(), sJsonAlloc);
        lDoc->AddMember("name", lVal, sJsonAlloc);
    }
    /* Get FileInfo */
    {
        rapidjson::Value lFileInfoVal(rapidjson::kObjectType);
        /* Get file name */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.fileName().c_str(), pOD.fileName().size(), sJsonAlloc);
            lFileInfoVal.AddMember("FileName", lVal, sJsonAlloc);
        }
        /* Get file version */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.fileVersion());
            lFileInfoVal.AddMember("FileVersion", lVal, sJsonAlloc);
        }
        /* Get file revision */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.fileRevision());
            lFileInfoVal.AddMember("FileRevision", lVal, sJsonAlloc);
        }
        /* Get EDS Version */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.EDSVersion().c_str(), pOD.EDSVersion().size(), sJsonAlloc);
            lFileInfoVal.AddMember("EDSVersion", lVal, sJsonAlloc);
        }
        /* Get description */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.description().c_str(), pOD.description().size(), sJsonAlloc);
            lFileInfoVal.AddMember("Description", lVal, sJsonAlloc);
        }
        /* Get CreationDate */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.creationDate().c_str(), pOD.creationDate().size(), sJsonAlloc);
            lFileInfoVal.AddMember("CreationDate", lVal, sJsonAlloc);
        }
        /* Get CreationTime */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.creationTime().c_str(), pOD.creationTime().size(), sJsonAlloc);
            lFileInfoVal.AddMember("CreationTime", lVal, sJsonAlloc);
        }
        /* Get CreatedBy */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.createdBy().c_str(), pOD.createdBy().size(), sJsonAlloc);
            lFileInfoVal.AddMember("CreatedBy", lVal, sJsonAlloc);
        }
        /* Get ModificationDate */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.modificationDate().c_str(), pOD.modificationDate().size(), sJsonAlloc);
            lFileInfoVal.AddMember("ModificationDate", lVal, sJsonAlloc);
        }
        /* Get ModificationTime */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.modificationTime().c_str(), pOD.modificationTime().size(), sJsonAlloc);
            lFileInfoVal.AddMember("ModificationTime", lVal, sJsonAlloc);
        }
        /* Get ModifiedBy */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.modifiedBy().c_str(), pOD.modifiedBy().size(), sJsonAlloc);
            lFileInfoVal.AddMember("ModifiedBy", lVal, sJsonAlloc);
        }
        lDoc->AddMember("FileInfo", lFileInfoVal, sJsonAlloc);
    }

    /* Get DeviceInfo */
    {
        rapidjson::Value lDeviceInfoVal(rapidjson::kObjectType);
        /* Get VendorName */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.vendorName().c_str(), pOD.vendorName().size(), sJsonAlloc);
            lDeviceInfoVal.AddMember("VendorName", lVal, sJsonAlloc);
        }
        /* Get VendorNumber */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.vendorNumber());
            lDeviceInfoVal.AddMember("VendorNumber", lVal, sJsonAlloc);
        }
        /* Get ProductName */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.productName().c_str(), pOD.productName().size(), sJsonAlloc);
            lDeviceInfoVal.AddMember("ProductName", lVal, sJsonAlloc);
        }
        /* Get ProductNumber */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.productNumber());
            lDeviceInfoVal.AddMember("ProductNumber", lVal, sJsonAlloc);
        }
        /* Get RevisionNumber */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.productNumber());
            lDeviceInfoVal.AddMember("RevisionNumber", lVal, sJsonAlloc);
        }
        /* Get OrderCode */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.orderCode().c_str(), pOD.orderCode().size(), sJsonAlloc);
            lDeviceInfoVal.AddMember("OrderCode", lVal, sJsonAlloc);
        }
        /* Get BaudRate_10 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate10Supported());
            lDeviceInfoVal.AddMember("BaudRate_10", lVal, sJsonAlloc);
        }
        /* Get BaudRate_20 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate20Supported());
            lDeviceInfoVal.AddMember("BaudRate_20", lVal, sJsonAlloc);
        }
        /* Get BaudRate_50 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate50Supported());
            lDeviceInfoVal.AddMember("BaudRate_50", lVal, sJsonAlloc);
        }
        /* Get BaudRate_125 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate125Supported());
            lDeviceInfoVal.AddMember("BaudRate_125", lVal, sJsonAlloc);
        }
        /* Get BaudRate_250 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate250Supported());
            lDeviceInfoVal.AddMember("BaudRate_250", lVal, sJsonAlloc);
        }
        /* Get BaudRate_500 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate500Supported());
            lDeviceInfoVal.AddMember("BaudRate_500", lVal, sJsonAlloc);
        }
        /* Get BaudRate_800 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate800Supported());
            lDeviceInfoVal.AddMember("BaudRate_800", lVal, sJsonAlloc);
        }
        /* Get BaudRate_1000 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate1000Supported());
            lDeviceInfoVal.AddMember("BaudRate_1000", lVal, sJsonAlloc);
        }
        /* Get SimpleBootUpMaster */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.simpleBootUpMaster());
            lDeviceInfoVal.AddMember("SimpleBootUpMaster", lVal, sJsonAlloc);
        }
        /* Get SimpleBootUpSlave */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.simpleBootUpSlave());
            lDeviceInfoVal.AddMember("SimpleBootUpSlave", lVal, sJsonAlloc);
        }
        /* Get Granularity */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.granularity());
            lDeviceInfoVal.AddMember("Granularity", lVal, sJsonAlloc);
        }
        /* Get DynamicChannelsSupported */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.dynamicChannelsSupported());
            lDeviceInfoVal.AddMember("DynamicChannelsSupported", lVal, sJsonAlloc);
        }
        /* Get GroupMessaging */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.groupMessaging());
            lDeviceInfoVal.AddMember("GroupMessaging", lVal, sJsonAlloc);
        }
        /* Get NrOfRXPDO */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.nrOfRPDOs());
            lDeviceInfoVal.AddMember("NrOfRXPDO", lVal, sJsonAlloc);
        }
        /* Get NrOfTXPDO */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.nrOfTPDOs());
            lDeviceInfoVal.AddMember("NrOfTXPDO", lVal, sJsonAlloc);
        }
        /* Get LSS_Supported */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.LSSSupported());
            lDeviceInfoVal.AddMember("LSS_Supported", lVal, sJsonAlloc);
        }
        lDoc->AddMember("DeviceInfo", lDeviceInfoVal, sJsonAlloc);
    } 

    /* Get Comment section */
    {
        rapidjson::Value lCommentsVal(rapidjson::kObjectType);
        /* Get Comment line count */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.commentLineCount());
            lCommentsVal.AddMember("Lines", lVal, sJsonAlloc);
        }
        /* Get comments */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.comments().c_str(), pOD.comments().size(), sJsonAlloc);
            lCommentsVal.AddMember("Comments", lVal, sJsonAlloc);
        }
        lDoc->AddMember("Comments", lCommentsVal, sJsonAlloc);
    }

    /* Get DummyUsage section */
    {
        rapidjson::Value lDummyUsageVal(rapidjson::kObjectType);
        /* Get Dummy0001 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0001Supported());
            lDummyUsageVal.AddMember("Dummy0001", lVal, sJsonAlloc);
        }
        /* Get Dummy0002 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0002Supported());
            lDummyUsageVal.AddMember("Dummy0002", lVal, sJsonAlloc);
        }
        /* Get Dummy0003 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0003Supported());
            lDummyUsageVal.AddMember("Dummy0003", lVal, sJsonAlloc);
        }
        /* Get Dummy0004 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0004Supported());
            lDummyUsageVal.AddMember("Dummy0004", lVal, sJsonAlloc);
        }
        /* Get Dummy0005 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0005Supported());
            lDummyUsageVal.AddMember("Dummy0005", lVal, sJsonAlloc);
        }
        /* Get Dummy0006 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0006Supported());
            lDummyUsageVal.AddMember("Dummy0006", lVal, sJsonAlloc);
        }
        /* Get Dummy0007 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0007Supported());
            lDummyUsageVal.AddMember("Dummy0007", lVal, sJsonAlloc);
        }
        lDoc->AddMember("DummyUsage", lDummyUsageVal, sJsonAlloc);
    }
    
    /* Get Indexes */
    {
        rapidjson::Value lVal(rapidjson::kArrayType);

        /* Go through every SubIndex */
        for(const auto &lElmt : pOD.indexes()) {
            rapidjson::Document lSubDoc(rapidjson::kObjectType);
            (void)OSCOODIndexToJSON(*lElmt.second, &lSubDoc);

            if(!lDoc->IsObject()) {
                std::cerr << "[ERROR] <JSONFactory::OSCOODToJSON> Got invalid sub JSON from OSCOODIndexToJSON" << std::endl;
                return "[ERROR OCCURED]";
            }

            /* Add the Document to the array */
            lVal.PushBack(lSubDoc, sJsonAlloc);
        }

        /* Add the array of objects as a member of the main JSON doc */
        lDoc->AddMember("Indexes", lVal, sJsonAlloc);
    }

    /* Add OSCO type */
    {
        rapidjson::Value lVal;
        lVal.SetString("OSCOOD", std::strlen("OSCOOD"), sJsonAlloc);
        lDoc->AddMember("OSCO Type", lVal, sJsonAlloc);
    }

    std::string lOutput = "";
    if(nullptr == pDoc) {
        /* Create a StringBuffer */
        rapidjson::StringBuffer lStrBuf;
        /* Create a Writer to convert the Document to a string */
        rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
        /* Set the writer as a handler for the Document */
        lDoc->Accept(lWriter);

        /* Create output string */
        lOutput = std::string(lStrBuf.GetString()) + "\r\n";

        //std::cout << "[DEBUG] <JSONFactory::OSCOODToJSON> JSON : " << lOutput << std::endl;

        delete lDoc;
    }

    return lOutput;
}

std::string JSONFactory::OSCONodeToJSON(const OSCONode &pNode, rapidjson::Document * const pDoc) {
    rapidjson::Document *lDoc = nullptr;
    if(nullptr == pDoc) {
        /* Create a RapidJSON Document */
        lDoc = new rapidjson::Document(rapidjson::kObjectType);
    } else {
        lDoc = pDoc;
    }

    /* Get the Object's contents */
    (void)OSCOODToJSON((OSCOOD)pNode, lDoc);

    if(!lDoc->IsObject()) {
        std::cerr << "[ERROR] <JSONFactory::OSCONodeToJSON> Got invalid JSON from OSCOODToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }

    /* Set OSCO type */
    rapidjson::Value::MemberIterator lIt = lDoc->FindMember("OSCO Type");
    if(lDoc->MemberEnd() != lIt) {
        lIt->value.SetString("OSCONode", std::strlen("OSCONode"), sJsonAlloc);
    } else {
        std::cerr << "[ERROR] <JSONFactory::OSCONodeToJSON> Got partial JSON from OSCOODToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }
    /* Get NodeID */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pNode.nodeID());
        lDoc->AddMember("Node ID", lVal, sJsonAlloc);
    }

    std::string lOutput = "";
    if(nullptr == pDoc) {
        /* Create a StringBuffer */
        rapidjson::StringBuffer lStrBuf;
        /* Create a Writer to convert the Document to a string */
        rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
        /* Set the writer as a handler for the Document */
        lDoc->Accept(lWriter);

        /* Create output string */
        lOutput = std::string(lStrBuf.GetString()) + "\r\n";

        //std::cout << "[DEBUG] <JSONFactory::OSCONodeToJSON> JSON : " << lOutput << std::endl;

        delete lDoc;
    }

    return lOutput;
}
