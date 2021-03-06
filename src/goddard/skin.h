#pragma once

#include <PR/ultratypes.h>

// bss
extern struct ObjNet* gGdSkinNet;   // @ 801BAAF0

// functions
void reset_net(         struct ObjNet   *net  );
struct ObjNet *make_net(struct ObjGroup *group);
void convert_net_verts( struct ObjNet   *net  );
void move_nets(         struct ObjGroup *group);
void func_80193848(     struct ObjGroup *group);
void reset_net_count(void);
