/**************************************************************************
 *									  *
 *		 Copyright (C) 1995, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/*---------------------------------------------------------------------*
        Copyright (C) 1998 Nintendo. (Originated by SGI)

        $RCSfile: os_internal.h,v $
        $Revision: 1.1.1.1 $
        $Date: 2002/05/02 03:28:24 $
 *---------------------------------------------------------------------*/

#pragma once

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/os.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

#include "os_internal_reg.h"
#include "os_internal_exception.h"
#include "os_internal_tlb.h"
#include "os_internal_si.h"
#include "os_internal_rsp.h"
#include "os_internal_error.h"
#include "os_internal_gio.h"
#include "os_internal_thread.h"
#include "os_internal_debug.h"
#include "os_internal_host.h"

#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif
