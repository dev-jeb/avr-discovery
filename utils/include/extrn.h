#ifndef EXTRN_H
#define EXTRN_H

/**
 * @contact_info:
 *   Author: dev_jeb
 *   Email: developer_jeb@outlook.com
 *   Date: 05-01-2024
 *
 * @purpose:
 *  This module will provide a way to define symbols expected to be defined in
 * the runtime environment.
 */

#include "types.h"

/**
 * @brief System clock frequency.
 *
 * @details
 *   This symbol should be defined by the runtime environment.
 */
extern uint32_t __F_CPU;

#endif // EXTRN_H
