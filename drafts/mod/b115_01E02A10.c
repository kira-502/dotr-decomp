/* OVL_WARM */
#include "common.h"

/* shape b115:01E02A10, 267 insns: b052:01E03730 cousin with its own packet: draws a row of 13 thin bars at the given
   point (third argument) shaken by the per-entry table offsets, the far edge pinned at +-2.5 (+-5.5 once the scene
   clock 0x3730 reaches 107); before clock 47 they are drawn far, then at their depth; texture corners by the module
   helper (shape b003:01E00080) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b115_01E02A10;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b115_01E02A10 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x30];
} Pkt_b115_01E02A10;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    u8 rect[0x10];
    u8 padA4[0x36FC - 0xA4];
    s32 ot;
    u8 pad3700[0x3730 - 0x3700];
    s16 clock;
} Obj_b115_01E02A10;

typedef struct {
    u8 pad0[8];
    s16 off;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b115_01E02A10;
static void func_01E00080_b115();


static void func_01E02A10_b115(Obj_b115_01E02A10 *o, Spr_b115_01E02A10 *s, Vec4f *at, s8 *tbl) {
    extern Rgbaq_b115_01E02A10 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f c;
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    struct {
        u64 tag;
        Pkt_b115_01E02A10 pk;
    } buf;
    s16 i;
    Pkt_b115_01E02A10 *p;
    s32 h;
    s8 *j;
    f32 f;
    f32 w;

    c = *at;
    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.c.q = 0;
    buf.pk.v[0].f = 0;
    buf.pk.v[1].f = 0;
    buf.pk.v[2].f = 0;
    buf.pk.v[3].f = 0;
    buf.pk.c = func_00107740(s->col);
    func_01E00080_b115(p, o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    pos.x = c.x;
    pos.y = c.y;
    pos.z = c.z;
    func_00108EF0(m, &scale, rot, &pos);
    for (i = 0; i < 13; i++) {
        func_00108CE0(quad, s->size, s->size);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 50];
        f /= 20.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        if (o->clock < 107) {
            w = 2.5f;
        } else {
            w = 5.5f;
        }
        quad[0].y = 0.0f;
        quad[1].y = quad[0].y;
        quad[0].x = w;
        quad[1].x = -w;
        quad[0].z = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            if (o->clock < 47) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            } else {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
    }
}
