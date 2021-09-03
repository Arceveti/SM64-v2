#ifndef RENDERING_GRAPH_NODE_H
#define RENDERING_GRAPH_NODE_H

#include <PR/ultratypes.h>

#include "engine/graph_node.h"

extern struct GraphNodeRoot        *gCurGraphNodeRoot;
extern struct GraphNodeMasterList  *gCurGraphNodeMasterList;
extern struct GraphNodePerspective *gCurGraphNodeCamFrustum;
extern struct GraphNodeCamera      *gCurGraphNodeCamera;
extern struct GraphNodeObject      *gCurGraphNodeObject;
extern struct GraphNodeHeldObject  *gCurGraphNodeHeldObject;
extern u16 gAreaUpdateCounter;
#ifdef METAL_CAP_REFLECTION_LAKITU
extern ScreenPos gMarioScreenX, gMarioScreenY;
#endif
extern f32 gWorldScale;

// after processing an object, the type is reset to this
#define ANIM_TYPE_NONE                  0x0

// Not all parts have full animation: to save space, some animations only
// have xz, y, or no translation at all. All animations have rotations though
#define ANIM_TYPE_TRANSLATION           0x1
#define ANIM_TYPE_VERTICAL_TRANSLATION  0x2
#define ANIM_TYPE_LATERAL_TRANSLATION   0x3
#define ANIM_TYPE_NO_TRANSLATION        0x4

// Every animation includes rotation, after processing any of the above
// translation types the type is set to this
#define ANIM_TYPE_ROTATION              0x5

void geo_process_node_and_siblings(struct GraphNode *firstNode);
void geo_process_root(struct GraphNodeRoot *node, Vp *b, Vp *c, s32 clearColor);

#endif // RENDERING_GRAPH_NODE_H
