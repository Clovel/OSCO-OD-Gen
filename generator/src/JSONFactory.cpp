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

/* JSONFactory class implementation -------------------- */
std::string JSONFactory::OSCOODObjectToJSON(const OSCOODObject &pObj) {
    /* Create a RapidJSON Document */
    rapidjson::Document lDoc;
    lDoc.SetObject();

    /* Get the document's allocator */
    rapidjson::Document::AllocatorType &lAlloc = lDoc.GetAllocator();

    /* Get the object's contents */
    /* SubNumber */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.subNumber());
        lDoc.AddMember("SubNumber", lVal, lAlloc);
    }
    /* ParameterName */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.paramName().c_str(), pObj.paramName().size(), lAlloc);
        lDoc.AddMember("ParameterName", lVal, lAlloc);
    }
    /* ObjectType */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.objectType());
        lDoc.AddMember("ObjectType", lVal, lAlloc);
    }
    /* DataType */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.dataType());
        lDoc.AddMember("DataType", lVal, lAlloc);
    }
    /* AccessType */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.accessType().c_str(), pObj.accessType().size(), lAlloc);
        lDoc.AddMember("AccessType", lVal, lAlloc);
    }
    /* DefaultValue */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.defaultValue().c_str(), pObj.defaultValue().size(), lAlloc);
        lDoc.AddMember("DefaultValue", lVal, lAlloc);
    }
    /* LowLimit */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.lowLimit().c_str(), pObj.lowLimit().size(), lAlloc);
        lDoc.AddMember("LowLimit", lVal, lAlloc);
    }
    /* HighLimit */
    {
        rapidjson::Value lVal;
        lVal.SetString(pObj.highLimit().c_str(), pObj.highLimit().size(), lAlloc);
        lDoc.AddMember("HighLimit", lVal, lAlloc);
    }
    /* PDOMapping */
    {
        rapidjson::Value lVal;
        lVal.SetBool(pObj.pdoMapping());
        lDoc.AddMember("PDOMapping", lVal, lAlloc);
    }
    /* ObjFlags */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pObj.objFlags());
        lDoc.AddMember("ObjFlags", lVal, lAlloc);
    }
    /* CompactSubObj */
    {
        rapidjson::Value lVal;
        lVal.SetBool(pObj.compactSubObj());
        lDoc.AddMember("CompactSubObj", lVal, lAlloc);
    }

    /* Create a StringBuffer */
    rapidjson::StringBuffer lStrBuf;
    /* Create a Writer to convert the Document to a string */
    rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
    /* Set the writer as a handler for the Document */
    lDoc.Accept(lWriter);

    /* Create output string */
    std::string lOutput = std::string(lStrBuf.GetString()) + "\r\n";

    std::cout << "[DEBUG] <JSONFactory::OSCOODObjectToJSON> JSON : " << lOutput << std::endl;

    return lOutput;
}

std::string JSONFactory::OSCOODSubIndexToJSON(const OSCOODSubIndex &pSubIdx) {
    /* Create a RapidJSON Document */
    rapidjson::Document lDoc;
    lDoc.SetObject();

    /* Get the document's allocator */
    rapidjson::Document::AllocatorType &lAlloc = lDoc.GetAllocator();

    /* Get the Object's contents */
    std::string lObjJSON = OSCOODObjectToJSON((OSCOODObject)pSubIdx);

    /* Fill the document with the JSON string */
    lDoc.Parse(lObjJSON.c_str());

    if(!lDoc.IsObject()) {
        std::cerr << "[ERROR] <JSONFactory::OSCOODSubIndexToJSON> Got invalid JSON from OSCOODObjectToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }

    /* Get Index */
    {
        rapidjson::Value lVal;
        char lBuf[7U];
        std::memset(lBuf, 0, 7U);
        snprintf(lBuf, 7U, "0x%04X", pSubIdx.index());
        lVal.SetString(lBuf, 7U, lAlloc);
        lDoc.AddMember("Index", lVal, lAlloc);
    }
    /* Get SubIndex */
    {
        rapidjson::Value lVal;
        char lBuf[5U];
        std::memset(lBuf, 0, 5U);
        snprintf(lBuf, 5U, "0x%02X", (uint16_t)pSubIdx.subIndex());
        lVal.SetString(lBuf, 5U, lAlloc);
        lDoc.AddMember("SubIndex", lVal, lAlloc);
    }
    /* Add OSCO type */
    {
        rapidjson::Value lVal;
        lVal.SetString("OSCOODSubIndex", std::strlen("OSCOODSubIndex"), lAlloc);
        lDoc.AddMember("OSCO Type", lVal, lAlloc);
    }

    /* Create a StringBuffer */
    rapidjson::StringBuffer lStrBuf;
    /* Create a Writer to convert the Document to a string */
    rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
    /* Set the writer as a handler for the Document */
    lDoc.Accept(lWriter);

    /* Create output string */
    std::string lOutput = std::string(lStrBuf.GetString()) + "\r\n";

    std::cout << "[DEBUG] <JSONFactory::OSCOODSubIndexToJSON> JSON : " << lOutput << std::endl;

    return lOutput;
}

std::string JSONFactory::OSCOODIndexToJSON(const OSCOODIndex &pIdx) {
    /* Create a RapidJSON Document */
    rapidjson::Document lDoc;
    lDoc.SetObject();

    /* Get the document's allocator */
    rapidjson::Document::AllocatorType &lAlloc = lDoc.GetAllocator();

    /* Get the Object's contents */
    std::string lObjJSON = OSCOODObjectToJSON((OSCOODObject)pIdx);

    /* Fill the document with the JSON string */
    lDoc.Parse(lObjJSON.c_str());

    if(!lDoc.IsObject()) {
        std::cerr << "[ERROR] <JSONFactory::OSCOODIndexToJSON> Got invalid JSON from OSCOODObjectToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }

    /* Get Index */
    {
        rapidjson::Value lVal;
        char lBuf[7U];
        std::memset(lBuf, 0, 7U);
        snprintf(lBuf, 7U, "0x%04X", pIdx.index());
        lVal.SetString(lBuf, 7U, lAlloc);
        lDoc.AddMember("Index", lVal, lAlloc);
    }
    /* Get SubIdexes */
    {
        rapidjson::Value lVal(rapidjson::kArrayType);

        /* Go through every SubIndex */
        for(const auto &lElmt : pIdx.subIndexes()) {
            rapidjson::Document lSubDoc;
            std::string lSubIndexJSON = OSCOODSubIndexToJSON(*lElmt.second);

            /* Parse the subindex JSON */
            lSubDoc.Parse(lSubIndexJSON.c_str());
            if(!lDoc.IsObject()) {
                std::cerr << "[ERROR] <JSONFactory::OSCOODIndexToJSON> Got invalid sub JSON from OSCOODSubIndexToJSON" << std::endl;
                return "[ERROR OCCURED]";
            }

            /* Add the Document to the array */
            lVal.PushBack(lSubDoc, lAlloc);
        }

        /* Add the array of objects as a member of the main JSON doc */
        lDoc.AddMember("SubIndexes", lVal, lAlloc);
    }
    /* Add OSCO type */
    {
        rapidjson::Value lVal;
        lVal.SetString("OSCOODIndex", std::strlen("OSCOODIndex"), lAlloc);
        lDoc.AddMember("OSCO Type", lVal, lAlloc);
    }

    /* Create a StringBuffer */
    rapidjson::StringBuffer lStrBuf;
    /* Create a Writer to convert the Document to a string */
    rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
    /* Set the writer as a handler for the Document */
    lDoc.Accept(lWriter);

    /* Create output string */
    std::string lOutput = std::string(lStrBuf.GetString()) + "\r\n";

    std::cout << "[DEBUG] <JSONFactory::OSCOODIndexToJSON> JSON : " << lOutput << std::endl;

    return lOutput;
}

std::string JSONFactory::OSCOODToJSON(const OSCOOD &pOD) {
    /* Create a RapidJSON Document */
    rapidjson::Document lDoc;
    lDoc.SetObject();

    /* Get the document's allocator */
    rapidjson::Document::AllocatorType &lAlloc = lDoc.GetAllocator();

    /* Get OD name */
    {
        rapidjson::Value lVal;
        lVal.SetString(pOD.name().c_str(), pOD.name().size(), lAlloc);
        lDoc.AddMember("name", lVal, lAlloc);
    }
    /* Get FileInfo */
    {
        rapidjson::Value lFileInfoVal(rapidjson::kObjectType);
        /* Get file name */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.fileName().c_str(), pOD.fileName().size(), lAlloc);
            lFileInfoVal.AddMember("FileName", lVal, lAlloc);
        }
        /* Get file version */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.fileVersion());
            lFileInfoVal.AddMember("FileVersion", lVal, lAlloc);
        }
        /* Get file revision */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.fileRevision());
            lFileInfoVal.AddMember("FileRevision", lVal, lAlloc);
        }
        /* Get EDS Version */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.EDSVersion().c_str(), pOD.EDSVersion().size(), lAlloc);
            lFileInfoVal.AddMember("EDSVersion", lVal, lAlloc);
        }
        /* Get description */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.description().c_str(), pOD.description().size(), lAlloc);
            lFileInfoVal.AddMember("Description", lVal, lAlloc);
        }
        /* Get CreationDate */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.creationDate().c_str(), pOD.creationDate().size(), lAlloc);
            lFileInfoVal.AddMember("CreationDate", lVal, lAlloc);
        }
        /* Get CreationTime */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.creationTime().c_str(), pOD.creationTime().size(), lAlloc);
            lFileInfoVal.AddMember("CreationTime", lVal, lAlloc);
        }
        /* Get CreatedBy */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.createdBy().c_str(), pOD.createdBy().size(), lAlloc);
            lFileInfoVal.AddMember("CreatedBy", lVal, lAlloc);
        }
        /* Get ModificationDate */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.modificationDate().c_str(), pOD.modificationDate().size(), lAlloc);
            lFileInfoVal.AddMember("ModificationDate", lVal, lAlloc);
        }
        /* Get ModificationTime */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.modificationTime().c_str(), pOD.modificationTime().size(), lAlloc);
            lFileInfoVal.AddMember("ModificationTime", lVal, lAlloc);
        }
        /* Get ModifiedBy */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.modifiedBy().c_str(), pOD.modifiedBy().size(), lAlloc);
            lFileInfoVal.AddMember("ModifiedBy", lVal, lAlloc);
        }
        lDoc.AddMember("FileInfo", lFileInfoVal, lAlloc);
    }

    /* Get DeviceInfo */
    {
        rapidjson::Value lDeviceInfoVal(rapidjson::kObjectType);
        /* Get VendorName */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.vendorName().c_str(), pOD.vendorName().size(), lAlloc);
            lDeviceInfoVal.AddMember("VendorName", lVal, lAlloc);
        }
        /* Get VendorNumber */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.vendorNumber());
            lDeviceInfoVal.AddMember("VendorNumber", lVal, lAlloc);
        }
        /* Get ProductName */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.productName().c_str(), pOD.productName().size(), lAlloc);
            lDeviceInfoVal.AddMember("ProductName", lVal, lAlloc);
        }
        /* Get ProductNumber */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.productNumber());
            lDeviceInfoVal.AddMember("ProductNumber", lVal, lAlloc);
        }
        /* Get RevisionNumber */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.productNumber());
            lDeviceInfoVal.AddMember("ProductNumber", lVal, lAlloc);
        }
        /* Get OrderCode */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.orderCode().c_str(), pOD.orderCode().size(), lAlloc);
            lDeviceInfoVal.AddMember("OrderCode", lVal, lAlloc);
        }
        /* Get BaudRate_10 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate10Supported());
            lDeviceInfoVal.AddMember("BaudRate_10", lVal, lAlloc);
        }
        /* Get BaudRate_20 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate20Supported());
            lDeviceInfoVal.AddMember("BaudRate_20", lVal, lAlloc);
        }
        /* Get BaudRate_50 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate50Supported());
            lDeviceInfoVal.AddMember("BaudRate_50", lVal, lAlloc);
        }
        /* Get BaudRate_125 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate125Supported());
            lDeviceInfoVal.AddMember("BaudRate_125", lVal, lAlloc);
        }
        /* Get BaudRate_250 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate250Supported());
            lDeviceInfoVal.AddMember("BaudRate_250", lVal, lAlloc);
        }
        /* Get BaudRate_500 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate500Supported());
            lDeviceInfoVal.AddMember("BaudRate_500", lVal, lAlloc);
        }
        /* Get BaudRate_800 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate800Supported());
            lDeviceInfoVal.AddMember("BaudRate_800", lVal, lAlloc);
        }
        /* Get BaudRate_1000 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.baudrate1000Supported());
            lDeviceInfoVal.AddMember("BaudRate_1000", lVal, lAlloc);
        }
        /* Get SimpleBootUpMaster */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.simpleBootUpMaster());
            lDeviceInfoVal.AddMember("SimpleBootUpMaster", lVal, lAlloc);
        }
        /* Get SimpleBootUpSlave */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.simpleBootUpSlave());
            lDeviceInfoVal.AddMember("SimpleBootUpSlave", lVal, lAlloc);
        }
        /* Get Granularity */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.granularity());
            lDeviceInfoVal.AddMember("Granularity", lVal, lAlloc);
        }
        /* Get DynamicChannelsSupported */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.dynamicChannelsSupported());
            lDeviceInfoVal.AddMember("DynamicChannelsSupported", lVal, lAlloc);
        }
        /* Get GroupMessaging */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.groupMessaging());
            lDeviceInfoVal.AddMember("GroupMessaging", lVal, lAlloc);
        }
        /* Get NrOfRXPDO */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.nrOfRPDOs());
            lDeviceInfoVal.AddMember("NrOfRXPDO", lVal, lAlloc);
        }
        /* Get NrOfTXPDO */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.nrOfTPDOs());
            lDeviceInfoVal.AddMember("NrOfTXPDO", lVal, lAlloc);
        }
        /* Get LSS_Supported */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.LSSSupported());
            lDeviceInfoVal.AddMember("LSS_Supported", lVal, lAlloc);
        }
        lDoc.AddMember("DeviceInfo", lDeviceInfoVal, lAlloc);
    } 

    /* Get Comment section */
    {
        rapidjson::Value lCommentsVal(rapidjson::kObjectType);
        /* Get Comment line count */
        {
            rapidjson::Value lVal;
            lVal.SetInt(pOD.commentLineCount());
            lCommentsVal.AddMember("Lines", lVal, lAlloc);
        }
        /* Get comments */
        {
            rapidjson::Value lVal;
            lVal.SetString(pOD.comments().c_str(), pOD.comments().size(), lAlloc);
            lCommentsVal.AddMember("Comments", lVal, lAlloc);
        }
        lDoc.AddMember("Comments", lCommentsVal, lAlloc);
    }

    /* Get DummyUsage section */
    {
        rapidjson::Value lDummyUsageVal(rapidjson::kObjectType);
        /* Get Dummy0001 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0001Supported());
            lDummyUsageVal.AddMember("Dummy0001", lVal, lAlloc);
        }
        /* Get Dummy0002 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0002Supported());
            lDummyUsageVal.AddMember("Dummy0002", lVal, lAlloc);
        }
        /* Get Dummy0003 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0003Supported());
            lDummyUsageVal.AddMember("Dummy0003", lVal, lAlloc);
        }
        /* Get Dummy0004 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0004Supported());
            lDummyUsageVal.AddMember("Dummy0004", lVal, lAlloc);
        }
        /* Get Dummy0005 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0005Supported());
            lDummyUsageVal.AddMember("Dummy0005", lVal, lAlloc);
        }
        /* Get Dummy0006 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0006Supported());
            lDummyUsageVal.AddMember("Dummy0006", lVal, lAlloc);
        }
        /* Get Dummy0007 */
        {
            rapidjson::Value lVal;
            lVal.SetBool(pOD.dummy0007Supported());
            lDummyUsageVal.AddMember("Dummy0007", lVal, lAlloc);
        }
        lDoc.AddMember("DummyUsage", lDummyUsageVal, lAlloc);
    }
    /* Add OSCO type */
    {
        rapidjson::Value lVal;
        lVal.SetString("OSCOOD", std::strlen("OSCOOD"), lAlloc);
        lDoc.AddMember("OSCO Type", lVal, lAlloc);
    }

    /* Create a StringBuffer */
    rapidjson::StringBuffer lStrBuf;
    /* Create a Writer to convert the Document to a string */
    rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
    /* Set the writer as a handler for the Document */
    lDoc.Accept(lWriter);

    /* Create output string */
    std::string lOutput = std::string(lStrBuf.GetString()) + "\r\n";

    std::cout << "[DEBUG] <JSONFactory::OSCOODToJSON> JSON : " << lOutput << std::endl;

    return lOutput;
}

std::string JSONFactory::OSCONodeToJSON(const OSCONode &pNode) {
    /* Create a RapidJSON Document */
    rapidjson::Document lDoc;
    lDoc.SetObject();

    /* Get the document's allocator */
    rapidjson::Document::AllocatorType &lAlloc = lDoc.GetAllocator();

    /* Get the Object's contents */
    std::string lObjJSON = OSCOODToJSON((OSCOOD)pNode);

    /* Fill the document with the JSON string */
    lDoc.Parse(lObjJSON.c_str());

    if(!lDoc.IsObject()) {
        std::cerr << "[ERROR] <JSONFactory::OSCONodeToJSON> Got invalid JSON from OSCOODToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }

    /* Set OSCO type */
    rapidjson::Value::MemberIterator lIt = lDoc.FindMember("OSCO Type");
    if(lDoc.MemberEnd() != lIt) {
        lIt->value.SetString("OSCONode", std::strlen("OSCONode"), lAlloc);
    } else {
        std::cerr << "[ERROR] <JSONFactory::OSCONodeToJSON> Got partial JSON from OSCOODToJSON" << std::endl;
        return "[ERROR OCCURED]";
    }
    /* Get NodeID */
    {
        rapidjson::Value lVal;
        lVal.SetInt(pNode.nodeID());
        lDoc.AddMember("Node ID", lVal, lAlloc);
    }

    /* Create a StringBuffer */
    rapidjson::StringBuffer lStrBuf;
    /* Create a Writer to convert the Document to a string */
    rapidjson::Writer<rapidjson::StringBuffer> lWriter(lStrBuf);
    /* Set the writer as a handler for the Document */
    lDoc.Accept(lWriter);

    /* Create output string */
    std::string lOutput = std::string(lStrBuf.GetString()) + "\r\n";

    std::cout << "[DEBUG] <JSONFactory::OSCONodeToJSON> JSON : " << lOutput << std::endl;

    return lOutput;
}
