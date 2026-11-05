#include "common.h"
#include "mod/c560.c"

/* shape c560:01E01E40 (C030PAINT_R), 440 insns, 1 copy: C030PAINT_R ring: a textured 10-segment band 36 degrees apart
   (c030:01E02170 form, 50 wide) drawn from a local packet with the object colour and the scene rect as uv; the outer
   edge follows the parent link (radius 0x4C) or its own radius 0x4A, heights bob 30 + 30 cos(z - 180), on-screen
   quads sent at the far plane */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c560_01E01E40;


typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c560_01E01E40;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c560_01E01E40;

typedef struct {
    union {
        u32 w;
        struct {
            u8 r, g, b, a;
        } c;
    } u;
    f32 q;
} Col8_c560_01E01E40;

typedef struct {
    Col8_c560_01E01E40 c;
    u64 uv;
    Xyz_c560_01E01E40 p;
} Vtx_c560_01E01E40;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c560_01E01E40 v[4];
    u8 tail[0x20];
} Pkt_c560_01E01E40;

typedef struct {
    u8 r, g, b, a;
} Col_c560_01E01E40;

typedef struct Ent_c560_01E01E40 {
    Vec4f q[2];
    u8 pad20[0x10];
    Col_c560_01E01E40 col0;
    Col_c560_01E01E40 col1;
    struct Ent_c560_01E01E40 *prev;
    struct Ent_c560_01E01E40 *next;
    u8 pad40[8];
    s16 f48;
    s16 hA;
    s16 hC;
    s16 f4E;
    s16 f50;
    s16 ang;
} Ent_c560_01E01E40;

typedef struct {
    s32 tex;
    s32 u, v, w, h;
    u8 pad14[0x50];
    f32 tab[91];
} Ctx_c560_01E01E40;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_c560_01E01E40;

typedef struct {
    u64 d;
} Raw_c560_01E01E40;

static inline void col_c560_01E01E40(Pkt_c560_01E01E40 *p, Raw_c560_01E01E40 c) {
    p->v[0].c = *(Col8_c560_01E01E40 *)&c;
    p->v[1].c = *(Col8_c560_01E01E40 *)&c;
    p->v[2].c = *(Col8_c560_01E01E40 *)&c;
    p->v[3].c = *(Col8_c560_01E01E40 *)&c;
}

static inline void uv_c560_01E01E40(Pkt_c560_01E01E40 *p, Ctx_c560_01E01E40 *g) {
    ((Uv_c560_01E01E40 *)&p->v[0].uv)->u = g->u << 4;
    ((Uv_c560_01E01E40 *)&p->v[0].uv)->v = g->v << 4;
    ((Uv_c560_01E01E40 *)&p->v[1].uv)->u = (g->u + g->w) << 4;
    ((Uv_c560_01E01E40 *)&p->v[1].uv)->v = g->v << 4;
    ((Uv_c560_01E01E40 *)&p->v[2].uv)->u = g->u << 4;
    ((Uv_c560_01E01E40 *)&p->v[2].uv)->v = (g->v + g->h) << 4;
    ((Uv_c560_01E01E40 *)&p->v[3].uv)->u = (g->u + g->w) << 4;
    ((Uv_c560_01E01E40 *)&p->v[3].uv)->v = (g->v + g->h) << 4;
}

static void func_01E01E40_c560(Ctx_c560_01E01E40 *g, Ent_c560_01E01E40 *o, Cam_c560_01E01E40 *cam) {
    extern Col8_c560_01E01E40 D_01E02F80_c560;
    extern s32 func_00208700(void *, s32, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 depth[4];
    Col8_c560_01E01E40 c;
    Pkt_c560_01E01E40 pk __attribute__((aligned(8)));
    s32 i;
    Ent_c560_01E01E40 *p;
    s16 a;
    Pkt_c560_01E01E40 *pp;
    s16 ang;

    p = o->prev;
    c = D_01E02F80_c560;
    c.u.w = (c.u.w & ~0xFF) | o->col0.b;
    c.u.w = (c.u.w & 0xFFFF00FF) | (o->col0.g << 8);
    a = 0;
    pp = (Pkt_c560_01E01E40 *)(s32)&pk;
    c.u.w = (c.u.w & 0xFF00FFFF) | (o->col0.r << 16);
    pp->count = 0x34;
    pp->tag = 0xC;
    pp->regs = ((u64)0x4214 << 32) | 0x21421421;
    pp->pad = 0;
    pp->count |= 0x800;
    func_002086D0(pp, ((u64)0x80 << 32) | 0x48);
    col_c560_01E01E40(&pk, *(Raw_c560_01E01E40 *)&c);
    uv_c560_01E01E40(&pk, g);
    func_00208700(pp, g->tex, 1);
    for (i = 0; i < 10; i++) {
        if (p != NULL) {
            ang = a + p->ang;
            q[0].y = p->hC * func_01E019D0_c560(g->tab, ang, 1);
            q[0].x = p->hC * func_01E019D0_c560(g->tab, ang, 0);
            ang = a + p->ang + 50;
            q[1].y = p->hC * func_01E019D0_c560(g->tab, ang, 1);
            q[1].x = p->hC * func_01E019D0_c560(g->tab, ang, 0);
            o->q[0].y = p->q[1].y;
        } else {
            ang = a;
            q[0].y = o->hA * func_01E019D0_c560(g->tab, ang + o->ang, 1);
            q[0].x = o->hA * func_01E019D0_c560(g->tab, ang + o->ang, 0);
            q[1].y = o->hA * func_01E019D0_c560(g->tab, ang + o->ang, 1);
            q[1].x = o->hA * func_01E019D0_c560(g->tab, ang + o->ang, 0);
        }
        ang = a + o->ang;
        q[2].y = o->hC * func_01E019D0_c560(g->tab, ang, 1);
        q[2].x = o->hC * func_01E019D0_c560(g->tab, ang, 0);
        ang = a + o->ang + 50;
        q[3].y = o->hC * func_01E019D0_c560(g->tab, ang, 1);
        q[3].x = o->hC * func_01E019D0_c560(g->tab, ang, 0);
        if (p == NULL) {
            c.u.c.a = o->col1.a;
        } else {
            c.u.c.a = p->col0.a;
        }
        pp->v[0].c.u.c.a = c.u.c.a;
        pp->v[1].c.u.c.a = c.u.c.a;
        c.u.c.a = o->col0.a;
        pp->v[2].c.u.c.a = c.u.c.a;
        pp->v[3].c.u.c.a = c.u.c.a;
        q[0].z = 30.0f + 30.0f * func_01E019D0_c560(g->tab, (s32)(o->q[0].z - 180.0f), 1);
        q[1].z = q[0].z;
        q[2].z = 30.0f + 30.0f * func_01E019D0_c560(g->tab, (s16)(o->q[1].z - 180.0f), 1);
        q[3].z = q[2].z;
        if (func_00205630(q, 0x70000000, cam->m, pp, depth) != 0) {
            pp->v[0].p.z = pp->v[1].p.z = pp->v[2].p.z = pp->v[3].p.z = 0xFFFFFF;
            func_002075F0(pp, (s32)func_00207500(), 0);
        }
        a += 36;
    }
}
