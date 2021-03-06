#pragma once

#include <PR/ultratypes.h>

#define BHV_PROC_CONTINUE 0x0
#define BHV_PROC_BREAK    0x1

#define cur_obj_get_int(  offset) o->OBJECT_FIELD_S32(offset)
#define cur_obj_get_float(offset) o->OBJECT_FIELD_F32(offset)

#define cur_obj_add_float(offset, value) o->OBJECT_FIELD_F32(offset) +=    (f32)(value)
#define cur_obj_set_float(offset, value) o->OBJECT_FIELD_F32(offset)  =    (f32)(value)
#define cur_obj_add_int(  offset, value) o->OBJECT_FIELD_S32(offset) +=    (s32)(value)
#define cur_obj_set_int(  offset, value) o->OBJECT_FIELD_S32(offset)  =    (s32)(value)
#define cur_obj_or_int(   offset, value) o->OBJECT_FIELD_S32(offset) |=    (s32)(value)
#define cur_obj_and_int(  offset, value) o->OBJECT_FIELD_S32(offset) &=    (s32)(value)
#define cur_obj_set_vptr( offset, value) o->OBJECT_FIELD_VPTR(offset) = (void *)(value)

#define obj_and_int(object, offset, value) object->OBJECT_FIELD_S32(offset) &= (s32)(value)

void cur_obj_update(void);
