#include <PR/ultratypes.h>

#include "string_utils.h"

/* 23C468 -> 23C4AC; orig name: func_8018DC98 */
void gd_strcpy(char *dst, const char *src) {
    while ((*dst++ = *src++)) ;
}

/* 23C5A8 -> 23C5FC; orig name: func_8018DDD8 */
u32 gd_strlen(const char *str) {
    u32 len = 0;
    while (*str++) len++;
    return len;
}

/* 23C5FC -> 23C680; orig name: func_8018DE2C */
char *gd_strcat(char *dst, const char *src) {
    while (*dst++) ;
    if (*src) {
        dst--;
        gd_strcpy(dst, src);
    }
    return --dst;
}

/* 23C67C -> 23C728; orig name: func_8018DEB0 */
/* Returns a bool, not the position of the mismatch */
s32 gd_str_not_equal(const char *str1, const char *str2) {
    while (*str1 && *str2) if (*str1++ != *str2++) return TRUE;
    return *str1 != '\0' || *str2 != '\0';
}
