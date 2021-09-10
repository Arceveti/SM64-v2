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

/**************************************************************************
 *
 *  $Revision: 1.15 $
 *  $Date: 1998/03/31 07:58:57 $
 *  $Source: /exdisk2/cvs/N64OS/Master/cvsmdev2/PR/include/ucode.h,v $
 *
 **************************************************************************/

#ifndef _UCODE_H_
#define	_UCODE_H_

#ifdef _LANGUAGE_C_PLUS_PLUS
extern "C" {
#endif

#include <PR/ultratypes.h>

#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)

/**************************************************************************
 *
 * Macro definitions
 *
 */

/*
 * This is the recommended size of the SP DRAM stack area, used
 * by the graphics ucode. This stack is used primarily for the
 * matrix stack, so it needs to be AT LEAST (10 * 64bytes) in size.
 */
#define	SP_DRAM_STACK_SIZE8	(1024)
#define	SP_DRAM_STACK_SIZE64	(SP_DRAM_STACK_SIZE8 >> 3)

/*
 * This is the size of the IMEM, which is also the size of the
 * graphics microcode. (other ucode might be less)
 * This value is used in apps to tell the OS how much ucode to
 * load.
 */
#define SP_UCODE_SIZE           4096

/*
 * This is 1/2 the size of DMEM, which is the maximum amount of
 * initialized DMEM data any of the ucode tasks need to start up.
 * This value is dependent on all of the task ucodes, and is therefore
 * fixed per release.
 */
#define SP_UCODE_DATA_SIZE      2048


/**************************************************************************
 *
 * Extern variables
 *
 */

/*
 * Symbols generated by "rsp2elf", included by "makerom" that indicate
 * the location and size of the SP microcode objects. The ucode objects
 * are loaded as part of the codesegment (arbitrary, could do other
 * ways)
 *
 */

/* standard boot ucode: */
extern u64	rspbootTextStart[], rspbootTextEnd[];

/* standard 3D ucode: */
extern u64	gspFast3DTextStart[], gspFast3DTextEnd[];
extern u64	gspFast3DDataStart[], gspFast3DDataEnd[];

/* 3D ucode with output to DRAM: */
extern u64	gspFast3D_dramTextStart[], gspFast3D_dramTextEnd[];
extern u64	gspFast3D_dramDataStart[], gspFast3D_dramDataEnd[];

/* 3D ucode with output through DRAM FIFO to RDP: */
extern u64	gspFast3D_fifoTextStart[], gspFast3D_fifoTextEnd[];
extern u64	gspFast3D_fifoDataStart[], gspFast3D_fifoDataEnd[];

/* 3D ucode without nearclip: */
extern u64	gspF3DNoNTextStart[], gspF3DNoNTextEnd[];
extern u64	gspF3DNoNDataStart[], gspF3DNoNDataEnd[];

/* 3D ucode without nearclip with output to DRAM: */
extern u64	gspF3DNoN_dramTextStart[];
extern u64	gspF3DNoN_dramTextEnd[];
extern u64	gspF3DNoN_dramDataStart[];
extern u64	gspF3DNoN_dramDataEnd[];

/* 3D ucode without nearclip with output through DRAM FIFO to RDP: */
extern u64	gspF3DNoN_fifoTextStart[];
extern u64	gspF3DNoN_fifoTextEnd[];
extern u64	gspF3DNoN_fifoDataStart[];
extern u64	gspF3DNoN_fifoDataEnd[];

/* 3D line ucode: */
extern u64	gspLine3DTextStart[], gspLine3DTextEnd[];
extern u64	gspLine3DDataStart[], gspLine3DDataEnd[];

/* 3D line ucode with output to DRAM: */
extern u64	gspLine3D_dramTextStart[], gspLine3D_dramTextEnd[];
extern u64	gspLine3D_dramDataStart[], gspLine3D_dramDataEnd[];

/* 3D line ucode with output through DRAM FIFO to RDP: */
extern u64	gspLine3D_fifoTextStart[], gspLine3D_fifoTextEnd[];
extern u64	gspLine3D_fifoDataStart[], gspLine3D_fifoDataEnd[];

/* super 3D ucode: */
extern u64	gspSuper3DTextStart[], gspSuper3DTextEnd[];
extern u64	gspSuper3DDataStart[], gspSuper3DDataEnd[];

/* 3D ucode with output to DRAM: */
extern u64	gspSuper3D_dramTextStart[], gspSuper3D_dramTextEnd[];
extern u64	gspSuper3D_dramDataStart[], gspSuper3D_dramDataEnd[];

/* 3D ucode with output through DRAM FIFO to RDP: */
extern u64	gspSuper3D_fifoTextStart[], gspSuper3D_fifoTextEnd[];
extern u64	gspSuper3D_fifoDataStart[], gspSuper3D_fifoDataEnd[];


/* 2D sprite ucode: */
extern u64	gspSprite2DTextStart[], gspSprite2DTextEnd[];
extern u64	gspSprite2DDataStart[], gspSprite2DDataEnd[];

/* 2D sprite ucode with output to DRAM: */
extern u64	gspSprite2D_dramTextStart[], gspSprite2D_dramTextEnd[];
extern u64	gspSprite2D_dramDataStart[], gspSprite2D_dramDataEnd[];

/* 2D sprite ucode with output through DRAM FIFO to RDP: */
extern u64	gspSprite2D_fifoTextStart[], gspSprite2D_fifoTextEnd[];
extern u64	gspSprite2D_fifoDataStart[], gspSprite2D_fifoDataEnd[];

/* basic audio ucode: */
extern u64 	aspMainTextStart[], aspMainTextEnd[];
extern u64 	aspMainDataStart[], aspMainDataEnd[];

/*========== F3DEX/F3DLX/F3DLP/L3DEX ==========*/
/* FIFO version only */
extern u64  gspF3DEX_fifoTextStart[],     gspF3DEX_fifoTextEnd[];
extern u64  gspF3DEX_fifoDataStart[],     gspF3DEX_fifoDataEnd[];
extern u64  gspF3DEX_NoN_fifoTextStart[], gspF3DEX_NoN_fifoTextEnd[];
extern u64  gspF3DEX_NoN_fifoDataStart[], gspF3DEX_NoN_fifoDataEnd[];

extern u64  gspF3DLX_fifoTextStart[],     gspF3DLX_fifoTextEnd[];
extern u64  gspF3DLX_fifoDataStart[],     gspF3DLX_fifoDataEnd[];
extern u64  gspF3DLX_NoN_fifoTextStart[], gspF3DLX_NoN_fifoTextEnd[];
extern u64  gspF3DLX_NoN_fifoDataStart[], gspF3DLX_NoN_fifoDataEnd[];
extern u64  gspF3DLX_Rej_fifoTextStart[], gspF3DLX_Rej_fifoTextEnd[];
extern u64  gspF3DLX_Rej_fifoDataStart[], gspF3DLX_Rej_fifoDataEnd[];

extern u64  gspF3DLP_Rej_fifoTextStart[], gspF3DLP_Rej_fifoTextEnd[];
extern u64  gspF3DLP_Rej_fifoDataStart[], gspF3DLP_Rej_fifoDataEnd[];
extern u64  gspL3DEX_fifoTextStart[],     gspL3DEX_fifoTextEnd[];
extern u64  gspL3DEX_fifoDataStart[],     gspL3DEX_fifoDataEnd[];

/*========== F3DEX2/F3DLX2/F3DLP2/L3DEX2 ==========*/
/* FIFO version */
extern u64 gspF3DEX2_fifoTextStart[],    gspF3DEX2_fifoTextEnd[];
extern u64 gspF3DEX2_fifoDataStart[],    gspF3DEX2_fifoDataEnd[];
extern u64 gspF3DEX2_NoN_fifoTextStart[],gspF3DEX2_NoN_fifoTextEnd[];
extern u64 gspF3DEX2_NoN_fifoDataStart[],gspF3DEX2_NoN_fifoDataEnd[];
extern u64 gspF3DEX2_Rej_fifoTextStart[],gspF3DEX2_Rej_fifoTextEnd[];
extern u64 gspF3DEX2_Rej_fifoDataStart[],gspF3DEX2_Rej_fifoDataEnd[];
extern u64 gspF3DLX2_Rej_fifoTextStart[],gspF3DLX2_Rej_fifoTextEnd[];
extern u64 gspF3DLX2_Rej_fifoDataStart[],gspF3DLX2_Rej_fifoDataEnd[];
extern u64 gspL3DEX2_fifoTextStart[],    gspL3DEX2_fifoTextEnd[];
extern u64 gspL3DEX2_fifoDataStart[],    gspL3DEX2_fifoDataEnd[];

extern u64 gspF3DEX2_PosLight_fifoTextStart[],    gspF3DEX2_PosLight_fifoTextEnd[];
extern u64 gspF3DEX2_PosLight_fifoDataStart[],    gspF3DEX2_PosLight_fifoDataEnd[];

/* XBUS version */
extern u64 gspF3DEX2_xbusTextStart[],    gspF3DEX2_xbusTextEnd[];
extern u64 gspF3DEX2_xbusDataStart[],    gspF3DEX2_xbusDataEnd[];
extern u64 gspF3DEX2_NoN_xbusTextStart[],gspF3DEX2_NoN_xbusTextEnd[];
extern u64 gspF3DEX2_NoN_xbusDataStart[],gspF3DEX2_NoN_xbusDataEnd[];
extern u64 gspF3DEX2_Rej_xbusTextStart[],gspF3DEX2_Rej_xbusTextEnd[];
extern u64 gspF3DEX2_Rej_xbusDataStart[],gspF3DEX2_Rej_xbusDataEnd[];
extern u64 gspF3DLX2_Rej_xbusTextStart[],gspF3DLX2_Rej_xbusTextEnd[];
extern u64 gspF3DLX2_Rej_xbusDataStart[],gspF3DLX2_Rej_xbusDataEnd[];
extern u64 gspL3DEX2_xbusTextStart[],    gspL3DEX2_xbusTextEnd[];
extern u64 gspL3DEX2_xbusDataStart[],    gspL3DEX2_xbusDataEnd[];

/*========== F3DZEX2/L3DZEX2 ==========*/
/* FIFO version */
extern u64 gspF3DZEX2_fifoTextStart[],
                     gspF3DZEX2_fifoTextEnd[];
extern u64 gspF3DZEX2_fifoDataStart[],
                     gspF3DZEX2_fifoDataEnd[];
extern u64 gspF3DZEX2_NoN_fifoTextStart[],
                     gspF3DZEX2_NoN_fifoTextEnd[];
extern u64 gspF3DZEX2_NoN_fifoDataStart[],
                     gspF3DZEX2_NoN_fifoDataEnd[];
extern u64 gspL3DZEX2_fifoTextStart[],
                     gspL3DZEX2_fifoTextEnd[];
extern u64 gspL3DZEX2_fifoDataStart[],
                     gspL3DZEX2_fifoDataEnd[];
/* XBUS version */
extern u64 gspF3DZEX2_xbusTextStart[],
                     gspF3DZEX2_xbusTextEnd[];
extern u64 gspF3DZEX2_xbusDataStart[],
                     gspF3DZEX2_xbusDataEnd[];
extern u64 gspF3DZEX2_NoN_xbusTextStart[],
                     gspF3DZEX2_NoN_xbusTextEnd[];
extern u64 gspF3DZEX2_NoN_xbusDataStart[],
                     gspF3DZEX2_NoN_xbusDataEnd[];
extern u64 gspL3DZEX2_xbusTextStart[],
                     gspL3DZEX2_xbusTextEnd[];
extern u64 gspL3DZEX2_xbusDataStart[],
                     gspL3DZEX2_xbusDataEnd[];

/*========== F3DZEX2/L3DZEX2 ==========*/
extern u64 gspF3DZEX2_PosLight_fifoTextStart[],
           gspF3DZEX2_PosLight_fifoTextEnd[];
extern u64 gspF3DZEX2_PosLight_fifoDataStart[],
           gspF3DZEX2_PosLight_fifoDataEnd[];
extern u64 gspF3DZEX2_NoN_PosLight_fifoTextStart[],
           gspF3DZEX2_NoN_PosLight_fifoTextEnd[];
extern u64 gspF3DZEX2_NoN_PosLight_fifoDataStart[],
           gspF3DZEX2_NoN_PosLight_fifoDataEnd[];
extern u64 gspL3DZEX2_PosLight_fifoTextStart[],
           gspL3DZEX2_PosLight_fifoTextEnd[];
extern u64 gspL3DZEX2_PosLight_fifoDataStart[],
           gspL3DZEX2_PosLight_fifoDataEnd[];

/**************************************************************************
 *
 * decomp ucode names
 *
 */

// F3D ucode
extern u64 rspF3DStart[], rspF3DEnd[];

// F3D ucode data
extern u64 rspF3DDataStart[], rspF3DDataEnd[];


/**************************************************************************
 *
 * Function prototypes
 *
 */

#endif /* _LANGUAGE_C */

#ifdef _LANGUAGE_C_PLUS_PLUS
}
#endif

#endif /* !_UCODE_H */
