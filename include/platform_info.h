#pragma once

#ifdef TARGET_N64
#define IS_64_BIT     0x0
#define IS_BIG_ENDIAN 0x1
#else
#include <stdint.h>
#define IS_64_BIT (UINTPTR_MAX == 0xFFFFFFFFFFFFFFFFU)
#define IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#endif

#define DOUBLE_SIZE_ON_64_BIT(size) ((size) * (sizeof(void *) / 4))
