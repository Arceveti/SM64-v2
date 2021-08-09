#ifndef GD_STRING_UTILS_H
#define GD_STRING_UTILS_H

#include <PR/ultratypes.h>

// functions
extern void  gd_strcpy(             char *, const char *);
extern u32   gd_strlen(                     const char *);
extern char *gd_strcat(             char *, const char *);
extern s32   gd_str_not_equal(const char *, const char *);

#endif // GD_STRING_UTILS_H
