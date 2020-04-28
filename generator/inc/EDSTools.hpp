/**
 * @brief EDS tools
 * 
 * @file EDSTools.hpp
 */

#ifndef EDSTOOLS_HPP
#define EDSTOOLS_HPP

/* Includes -------------------------------------------- */
/* Library/API export defines */
#include "APIExports.h"

/* C++ system */
#include <string>

/* C system */
#include <cstdint>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Forward declarations -------------------------------- */

/* EDS tool functions ---------------------------------- */
/**
 * @brief Checks if the section given is an Index section.
 * 
 * @param[in]   pSection    Section name
 * @param[out]  pIdx        Extracted index value
 * 
 * @return true if this section is a sub-index section, false elsewise.
 */
bool isIndexSection(const std::string &pSection, uint16_t * const pIdx = nullptr);

/**
 * @brief Checks if the section given is a Sub-index section.
 * 
 * @param[in]   pSection    Section name
 * @param[out]  pIdx        Extracted index value
 * @param[out]  pSubIdx     Extracted sub-index value
 * 
 * @return true if this section is a sub-index section, false elsewise.
 */
bool isSubIdxSection(const std::string &pSection, uint16_t * const pIdx = nullptr, uint8_t * const pSubIdx = nullptr);

/**
 * @brief Removes the "0x" prefix from a hex string
 * if there is one.
 * 
 * @param[in, out]  pHexStr     Hex string to change
 * 
 * @return Bool :
 * - true : the Hex string was changed
 * - false : the hex string did not change
 */
bool remove0xPrefix(std::string &pHexStr);

/**
 * @brief Adds the "0x" prefix from a hex string
 * if there isn't one.
 * 
 * @param[in, out]  pHexStr     Hex string to change
 * 
 * @return Bool :
 * - true : the Hex string was changed
 * - false : the hex string did not change
 */
bool add0xPrefix(std::string &pHexStr);

/**
 * @brief Converts a uint8_t value to a hexadecimal string.
 * The hexadecimal is filled with zeros to fit the type size.
 * 
 * @param[in]   pInt    Integer to convert
 * @param[in]   pZeroX  Weither we add the "0x" prefix or not
 * 
 * @return The resulting hexadecimal string
 */
std::string uint8ToHexStr(const uint8_t &pInt, const bool &pZeroX = true);

/**
 * @brief Converts a uint16_t value to a hexadecimal string.
 * The hexadecimal is filled with zeros to fit the type size.
 * 
 * @param[in]   pInt    Integer to convert
 * @param[in]   pZeroX  Weither we add the "0x" prefix or not
 * 
 * @return The resulting hexadecimal string
 */
std::string uint16ToHexStr(const uint16_t &pInt, const bool &pZeroX = true);

/**
 * @brief Converts a uint32_t value to a hexadecimal string.
 * The hexadecimal is filled with zeros to fit the type size.
 * 
 * @param[in]   pInt    Integer to convert
 * @param[in]   pZeroX  Weither we add the "0x" prefix or not
 * 
 * @return The resulting hexadecimal string
 */
std::string uint32ToHexStr(const uint32_t &pInt, const bool &pZeroX = true);

/**
 * @brief Converts a uint64_t value to a hexadecimal string.
 * The hexadecimal is filled with zeros to fit the type size.
 * 
 * @param[in]   pInt    Integer to convert
 * @param[in]   pZeroX  Weither we add the "0x" prefix or not
 * 
 * @return The resulting hexadecimal string
 */
std::string uint64ToHexStr(const uint64_t &pInt, const bool &pZeroX = true);

bool hexStrToUInt8(const std::string &pStr, uint8_t &pInt);
bool hexStrToUInt16(const std::string &pStr, uint16_t &pInt);

#endif /* EDSTOOLS_HPP */