
/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo.

        $RCSfile: os_motor.h,v $
        $Revision: 1.1.1.1 $
        $Date: 2002/05/02 03:28:25 $
 *---------------------------------------------------------------------*/

#pragma once

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>
#include "os_message.h"
#include "os_pfs.h"


#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Type definitions
 *
 */


#endif /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

/**************************************************************************
 *
 * Global definitions
 *
 */


#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Macro definitions
 *
 */


/**************************************************************************
 *
 * Extern variables
 *
 */


/**************************************************************************
 *
 * Function prototypes
 *
 */

/* Rumble PAK interface */

extern s32 osMotorInit(OSMesgQueue *, OSPfs *, int);
#if	1
#define MOTOR_START		1
#define MOTOR_STOP		0
#define	osMotorStart(x)		__osMotorAccess((x), MOTOR_START)
#define	osMotorStop(x)		__osMotorAccess((x), MOTOR_STOP)
extern s32 __osMotorAccess(OSPfs *, s32);
#else
extern s32 osMotorStop(OSPfs *);
extern s32 osMotorStart(OSPfs *);
#endif


#endif  /* defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS) */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
