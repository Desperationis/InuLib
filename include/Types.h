/** @file Types.h
 * @brief Define commonly used types.
 */

#ifndef TYPES_H
#define TYPES_H

/**
 * Represents the port of a motor; You should never go over 10, as there are
 * only 10 motor ports on the cortex.
*/
typedef unsigned char tMotor;

/**
 * [-128, 127]
*/
typedef char byte;

/**
 * [0, 255]
*/
typedef unsigned char ubyte;

#endif
