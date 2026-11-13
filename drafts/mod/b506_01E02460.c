#include "common.h"

/* shape b506:01E02460 (B506PAINT_RAIN), 536 insns, 1 copy: B506PAINT_RAIN: b521:01E02310's ring at -O4 with a turned
   matrix set (rot.x 0x4000/0xC000 by the scene flag, z +0x2000 per ring, scales 0.5..0.15 by 1.5), both passes per
   matrix with texture rect 0x97 then 0x96 and the packet flag j % 2 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b506_01E02460;

typedef struct {
    Rgbaq_b506_01E02460 c;
    f32 s, t;
    u64 xyz;
} Vtx_b506_01E02460;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b506_01E02460 v[4];
} Pkt_b506_01E02460;

typedef union {
    Vec4f v;
    struct {
        s16 x, y, w, h;
    } r;
} Rc_b506_01E02460;

typedef struct {
    f32 m[16];
} Mat_b506_01E02460;

typedef struct {
    s32 x, y, z, w;
} Rot_b506_01E02460;

typedef struct Ring_b506_01E02460 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 y2;
    u8 pad18[0x28];
    Vec4f pos;
    Vec4f rot;
    u8 pad60[0x10];
    struct Ring_b506_01E02460 *parent;
    u8 pad74[0xC];
    u8 col0[4];
    u8 col1[4];
    u8 pad88[2];
    s16 r0;
    s16 r1;
    u8 pad8E[4];
    s16 ang;
} Ring_b506_01E02460;

typedef struct {
    u8 pad0[0x2C8];
    void *texture;
    void *tex2CC;
    u8 pad2D0[0xAF10 - 0x2D0];
    Vec4f eye;
    u8 padAF20[0xBF80 - 0xAF20];
    void *glow;
    u8 padBF84[0xBFAC - 0xBF84];
    s32 ot;
    u8 padBFB0[0xBFE8 - 0xBFB0];
    f32 depth;
    u8 padBFEC[0xC02A - 0xBFEC];
    s16 flip;
    u8 padC02C[0xC130 - 0xC02C];
    u8 sin[4];
} Scene_b506_01E02460;

static void func_01E02460_b506(Scene_b506_01E02460 *g, Ring_b506_01E02460 *o, Pkt_b506_01E02460 *pk, s32 mode) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b506_01E02460 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern Mat_b506_01E02460 func_00108EF0(void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    Vec4f sc;
    Rc_b506_01E02460 c;
    Mat_b506_01E02460 m[5];
    Rot_b506_01E02460 r;
    s32 i;
    s32 j;
    Ring_b506_01E02460 *pa;
    s16 k;
    s16 a;

    pa = o->parent;
    a = 0;
    if (mode == 0) {
        func_00109270(pk, 0, 0);
        pk->v[0].c = func_00107740(o->col0);
        pk->v[1].c = func_00107740(o->col0);
        pk->v[2].c = func_00107740(o->col1);
        pk->v[3].c = func_00107740(o->col1);
        return;
    }
    if (g->flip != 0) {
        r.x = 0x4000;
    } else {
        r.x = 0xC000;
    }
    r.y = 0;
    r.z = 0;
    sc.x = 0.5f;
    sc.y = 1.5f;
    sc.z = 0.5f;
    func_00208700(pk, g->texture, 1);
    func_00106080(&c, 0x8C, 0, &c);
    func_00108500(pk, &c, 0);
    m[0] = func_00108EF0(&sc, &r, &g->eye);
    sc.x = 0.4f;
    sc.y = 1.5f;
    sc.z = 0.4f;
    r.z += 0x2000;
    m[1] = func_00108EF0(&sc, &r, &g->eye);
    sc.x = 0.3f;
    sc.y = 1.5f;
    sc.z = 0.3f;
    r.z += 0x2000;
    m[2] = func_00108EF0(&sc, &r, &g->eye);
    sc.x = 0.2f;
    sc.y = 1.5f;
    sc.z = 0.2f;
    r.z += 0x2000;
    m[3] = func_00108EF0(&sc, &r, &g->eye);
    sc.x = 0.15f;
    sc.y = 1.5f;
    sc.z = 0.15f;
    r.z += 0x2000;
    m[4] = func_00108EF0(&sc, &r, &g->eye);
    for (i = 0; i < 12; i++) {
        if (pa != NULL) {
            k = a + pa->ang;
            q[0].x = pa->r1 * func_00108030(g->sin, k, 1);
            q[0].z = pa->r1 * func_00108030(g->sin, k, 0);
            k = a + pa->ang - 30;
            q[1].x = pa->r1 * func_00108030(g->sin, k, 1);
            q[1].z = pa->r1 * func_00108030(g->sin, k, 0);
            o->y = pa->y2;
            if (pa != NULL) {
                func_00107DD0(q, &pa->pos, &o->pos, 0);
            }
        } else {
            q[0].x = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 1);
            q[0].z = o->r0 * func_00108030(g->sin, (s16)(a + o->ang), 0);
            q[1].x = o->r0 * func_00108030(g->sin, (s16)(a + o->ang - 30), 1);
            q[1].z = o->r0 * func_00108030(g->sin, (s16)(a + o->ang - 30), 0);
        }
        k = a + o->ang;
        q[2].x = o->r1 * func_00108030(g->sin, k, 1);
        q[2].z = o->r1 * func_00108030(g->sin, k, 0);
        k = a + o->ang - 30;
        q[3].x = o->r1 * func_00108030(g->sin, k, 1);
        q[3].z = o->r1 * func_00108030(g->sin, k, 0);
        q[0].y = o->y;
        q[1].y = o->y;
        q[2].y = o->y2;
        q[3].y = o->y2;
        for (j = 0; j < 4; j++) {
            if (q[j].y < 0.0f) {
                q[j].y = 0.0f;
            }
        }
        func_00106FA0(q, &o->pos, 0);
        func_00107DD0(&q[2], &o->pos, &o->rot, 0);
        for (j = 0; j < 4; j++) {
            func_00208700(pk, g->glow, 1);
            c.r.x = 0;
            c.r.y = 0;
            c.r.w = 0x1F;
            c.r.h = 0x7F;
            func_00208700(pk, g->tex2CC, 1);
            func_00106080(&c, 0x97, 0, &c);
            func_00108500(pk, &c, j % 2);
            if (func_00205630(q, 0x70000000, &m[j], pk, &g->depth) != 0) {
                func_002075F0(pk, g->ot, (u32)g->depth);
            }
            func_00208700(pk, g->tex2CC, 1);
            func_00106080(&c, 0x96, 0, &c);
            func_00108500(pk, &c, j % 2);
            if (func_00205630(q, 0x70000000, &m[j], pk, &g->depth) != 0) {
                func_002075F0(pk, g->ot, (u32)g->depth);
            }
        }
        a += 30;
    }
}
