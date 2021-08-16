#define COURSE_ACTS(id, name, a,b,c,d,e,f) \
    static const uchar GLUE2(COURSE_TABLE, _ ## id)[] = { name };

#define SECRET_STAR(id, name) \
    static const uchar GLUE2(COURSE_TABLE, _ ## id)[] = { name };

#define CASTLE_SECRET_STARS(str) \
    static const uchar GLUE2(COURSE_TABLE, _castle_secret_stars)[] = { str };

#define EXTRA_TEXT(id, str)

#include "courses.h"

#undef COURSE_ACTS
#undef SECRET_STAR
#undef CASTLE_SECRET_STARS

#define COURSE_ACTS(id, name, a,b,c,d,e,f) GLUE2(COURSE_TABLE, _ ## id),
#define SECRET_STAR(id, name) GLUE2(COURSE_TABLE, _ ## id),
#define CASTLE_SECRET_STARS(str) GLUE2(COURSE_TABLE, _castle_secret_stars),

const uchar *const COURSE_TABLE[] = {
#include "courses.h"
    NULL
};

#undef COURSE_ACTS
#undef SECRET_STAR
#undef CASTLE_SECRET_STARS

