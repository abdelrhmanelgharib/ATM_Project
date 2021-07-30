/**
 * @file DataTypes.h
 * @author Elgharib
 * @brief 
 * @version 0.1
 * @date 2021-07-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DATATYPES_H_ // if not define
#define _DATATYPES_H_


typedef unsigned char           uint8_t;
typedef signed char             sint8_t;
typedef unsigned short int      u16;
typedef signed short int        sint16_t;
typedef unsigned long int       uint32_t;
typedef signed long int         sint32_t;
typedef unsigned long long int  uint64_t;
typedef signed long long int    sint64_t;

#define NULLPTR (void*)0

typedef enum
{
    E_ERROR,
    E_OK
}EN_ERRORSTATE_t;

#endif
