#include "common.h"

/* shape b000:01E00080, 31 insns, 12 copies: colour the two vertices of a line packet; mode 0 = colour on the
   first vertex (second black), else on the second (first black); alpha and q = 1.0 on both */

typedef struct Src_b000_01E00080 {
    u8 b, g, r, a;
} Src_b000_01E00080;

typedef struct Xyz_b000_01E00080 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E00080;

typedef struct Vtx_b000_01E00080 {
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00080 p;
} Vtx_b000_01E00080;

typedef struct Pk_b000_01E00080 {
    u8 head[0x10];
    Vtx_b000_01E00080 v[2];
} Pk_b000_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b000(Pk_b000_01E00080 *p, Src_b000_01E00080 *s, s32 mode) {
    if (mode == 0) {
        p->v[0].r = s->r;
        p->v[0].g = s->g;
        p->v[0].b = s->b;
        p->v[1].r = 0;
        p->v[1].g = 0;
        p->v[1].b = 0;
    } else {
        p->v[0].r = 0;
        p->v[0].g = 0;
        p->v[0].b = 0;
        p->v[1].r = s->r;
        p->v[1].g = s->g;
        p->v[1].b = s->b;
    }
    p->v[0].a = s->a;
    p->v[0].q = 1.0f;
    p->v[1].a = s->a;
    p->v[1].q = 1.0f;
    p->v[0].p.f = 0;
    p->v[1].p.f = 0;
}

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00100_b000(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

/* shape b000:01E001A0, 151 insns: fade the screen rect 0x6BF8,0x71F8 - 0x93F8,0x8DF8: a flat quad in the given
   colour, then the frame texture (s 0..0.625, t 0..0.875) at alpha 0x80 - colour alpha, both at far z, into a
   fresh draw buffer */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E001A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E001A0 v[2];
    u64 tail;
} Flat_b000_01E001A0;

typedef struct {
    f32 s, t;
    Xyz_b000_01E001A0 p;
} Tv_b000_01E001A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b000_01E001A0 v[2];
    u64 tail;
} Tex_b000_01E001A0;

static s32 func_01E001A0_b000(u8 *c) {
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u64 func_00208D00(s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Flat_b000_01E001A0 flat __attribute__((aligned(8)));
    Tex_b000_01E001A0 pk __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    s32 buf;

    buf = func_00207F60();
    ((Tex_b000_01E001A0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b000_01E001A0 *)(s32)&pk)->size = 5;
    ((Tex_b000_01E001A0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b000_01E001A0 *)(s32)&pk)->pad4 = 0;
    func_00208460();
    func_00208800(func_00209E50(), 0, &a, b);
    func_00208460();
    ((Flat_b000_01E001A0 *)(s32)&flat)->flags = 6;
    ((Flat_b000_01E001A0 *)(s32)&flat)->size = 3;
    ((Flat_b000_01E001A0 *)(s32)&flat)->regs = 0x441;
    ((Flat_b000_01E001A0 *)(s32)&flat)->pad4 = 0;
    flat.r = c[2];
    flat.g = c[1];
    flat.b = c[0];
    flat.a = c[3];
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFFF;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFFF;
    flat.v[1].f = 0;
    func_002086D0(&flat, func_00208D00(3));
    func_002075F0((s32)&flat, 0, 0);
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
    pk.a = 0x80 - c[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = 0.0f;
    pk.v[0].t = 0.0f;
    pk.v[1].s = 0.625f;
    pk.v[1].t = 0.875f;
    func_002086D0(&pk, func_00208D00(0));
    func_002075F0((s32)&pk, 0, 0);
    func_00207FD0(buf, func_00207500(), 0xFFFFFF);
    return 0;
}

/* shape b000:01E00400, 87 insns, 46 copies: one flat-coloured full-screen quad (GS sprite packet, far z). The tag
   is written through a pointer that went through u32 (a plain &pk gets folded into $sp offsets). */

typedef struct Xyz_b000_01E00400 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b000_01E00400;

typedef struct Pk_b000_01E00400 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00400 v[4];
} Pk_b000_01E00400;

typedef struct Src_b000_01E00400 {
    u8 b, g, r, a;
} Src_b000_01E00400;

static inline void b000_01E00400_tag(Pk_b000_01E00400 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E00400_b000(s32 arg0, Src_b000_01E00400 *c) {
    Pk_b000_01E00400 pk;

    b000_01E00400_tag((Pk_b000_01E00400 *)(u32)&pk, 5, 4, 0x44441);
    func_002086D0((Pk_b000_01E00400 *)(u32)&pk, ((u64)0x80 << 32) | 0x48);
    pk.r = c->r;
    pk.g = c->g;
    pk.b = c->b;
    pk.a = c->a;
    pk.q = 1.0f;
    pk.v[0].x = 0x6000;
    pk.v[0].y = 0x7000;
    pk.v[0].z = 0xFFFFFF;
    pk.v[0].fog = 0;
    pk.v[1].x = 0xA000;
    pk.v[1].y = 0x7000;
    pk.v[1].z = 0xFFFFFF;
    pk.v[1].fog = 0;
    pk.v[2].x = 0x6000;
    pk.v[2].y = 0x9000;
    pk.v[2].z = 0xFFFFFF;
    pk.v[2].fog = 0;
    pk.v[3].x = 0xA000;
    pk.v[3].y = 0x9000;
    pk.v[3].z = 0xFFFFFF;
    pk.v[3].fog = 0;
    func_002075F0((s32)&pk, arg0, 0);
    return 0;
}

/* shape b000:01E00560, 416 insns, 3 copies: screen-split sprite: projects the position, then for count rows draws the four
   quadrants around the projected point as 2-vertex sprites, UVs from per-row offsets (u += 10, v += 7) and the
   point itself; blend from flags 0xC/0xB/0xA, depth far (flag 0x13) or from the position. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E00560;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b000_01E00560;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        Uv_b000_01E00560 st;
        Xyz_b000_01E00560 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b000_01E00560;

typedef struct {
    u8 pad00[0x30];
    f32 m[16];
} Cam_b000_01E00560;

typedef struct {
    s32 flags;
    u8 b4, b5, b6, b7;
    u8 pad8[4];
    s16 count;
    s16 model;
} Obj_b000_01E00560;

static s32 func_01E00560_b000(Obj_b000_01E00560 *o, Vec4f *pos) {
    extern s32 func_00207F60(void);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208460(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern f32 func_001F5860(s32);
    extern u64 func_00205D10(void *, f32);
    extern f32 func_00205DF0(void *, f32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    s32 h;
    s32 k;
    s32 i;
    s32 j;
    Cam_b000_01E00560 cam;
    Pkt_b000_01E00560 pkt __attribute__((aligned(8)));
    Xyz_b000_01E00560 q;
    f32 dep;

    h = func_00207F60();
    func_00103890(&cam);
    func_001038D0(&cam);
    if (func_00205440(pos, cam.m, &q, &dep) == 0) {
        return -1;
    }
    ((Pkt_b000_01E00560 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b000_01E00560 *)(s32)&pkt)->tag = 5;
    ((Pkt_b000_01E00560 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b000_01E00560 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = o->b6;
    pkt.g = o->b5;
    pkt.b = o->b4;
    pkt.a = o->b7;
    pkt.q = 1.0f;
    func_00208460();
    func_001F7060(o->model, 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (k = 0; k < o->count; k++) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                pkt.v[0].p.x = ((((q.x >> 4) - 0x6C0) * j + 0x6C0) << 4) - 8;
                pkt.v[0].p.y = ((((q.y >> 4) - 0x720) * i + 0x720) << 4) - 8;
                pkt.v[0].p.f = 0;
                pkt.v[1].p.x = ((((q.x >> 4) - 0x6C0) * (j + 1) + 0x6C0) << 4) - 8;
                pkt.v[1].p.y = ((((q.y >> 4) - 0x720) * (i + 1) + 0x720) << 4) - 8;
                pkt.v[1].p.f = 0;
                ((Pkt_b000_01E00560 *)(s32)&pkt)->count |= 0x800;
                if (i == 0) {
                    if (j == 0) {
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->s = (k * 10) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->t = (k * 7) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->s = ((q.x >> 4) - 0x6C0) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->t = ((q.y >> 4) - 0x720) << 4;
                    } else {
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->s = ((q.x >> 4) - 0x6C0) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->t = (k * 7) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->s = (0x280 - k * 10) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->t = ((q.y >> 4) - 0x720) << 4;
                    }
                } else {
                    if (j == 0) {
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->s = (k * 10) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->t = ((q.y >> 4) - 0x720) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->s = ((q.x >> 4) - 0x6C0) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->t = (0x1C0 - k * 7) << 4;
                    } else {
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->s = ((q.x >> 4) - 0x6C0) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[0].st)->t = ((q.y >> 4) - 0x720) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->s = (0x280 - k * 10) << 4;
                        ((Uv_b000_01E00560 *)(s32)&pkt.v[1].st)->t = (0x1C0 - k * 7) << 4;
                    }
                }
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.v[0].p.z = pkt.v[1].p.z = 0xFFFFFF;
                    func_002075F0(&pkt, 0, 0);
                } else {
                    pkt.v[0].p.z = pkt.v[1].p.z = func_00205D10(pos, -func_001F5860(o->model));
                    func_002075F0(&pkt, 0, (u32)func_00205DF0(pos, -func_001F5860(o->model)));
                }
            }
        }
    }
    func_00207FD0(h, func_00207500(), 0);
    return 0;
}

/* shape b540:01E00250 (LkPrim_SortSpot), 341 insns, 66 copies: a flat disc drawn as count triangles from the centre
   (the colour and its alpha) to the rim (alpha 0); flags 0x100000..0x400000 record which vertices projected, flag
   bits 0x13/0x12 force the far or the near z */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b540_01E00250;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b540_01E00250 xyz;
} Vtx_b540_01E00250;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b540_01E00250 v[3];
    u8 tail[8];
} Pkt_b540_01E00250;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 radius;
    s16 count;
    s16 height;
} Disc_b540_01E00250;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b540_01E00250;

static s32 func_01E00BE0_b000(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f c[3];
    Pkt_b540_01E00250 pkt __attribute__((aligned(8)));
    f32 dep[3];
    f32 step;
    f32 a;
    s32 i;

    step = 6.2831855f / d->count;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->count = 0x13;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->tag = 6;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->regs = 0x414141;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->pad = 0;
    if (func_00104520(d->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(d->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.v[0].r = d->r;
    pkt.v[0].g = d->g;
    pkt.v[0].b = d->b;
    pkt.v[0].a = d->a;
    pkt.v[0].q = 1.0f;
    pkt.v[1].r = d->r;
    pkt.v[1].g = d->g;
    pkt.v[1].b = d->b;
    pkt.v[1].a = 0;
    pkt.v[1].q = 1.0f;
    pkt.v[2].r = d->r;
    pkt.v[2].g = d->g;
    pkt.v[2].b = d->b;
    pkt.v[2].a = 0;
    pkt.v[2].q = 1.0f;
    c[0].y = 0.0f;
    c[0].x = 0.0f;
    c[0].z = c[1].z = c[2].z = 0.1f * d->height;
    for (i = 0; i < d->count; i++) {
        if (func_00205440(&c[0], cam->view, &pkt.v[0].xyz, &dep[0]) != 0) {
            d->flags |= 0x100000;
        }
        a = step * i;
        c[1].x = d->radius * func_0020B620(a);
        c[1].y = d->radius * func_0020B730(a);
        if (func_00205440(&c[1], cam->view, &pkt.v[1].xyz, &dep[1]) != 0) {
            d->flags |= 0x200000;
        }
        if (i == d->count - 1) {
            c[2].x = d->radius;
            c[2].y = 0.0f;
        } else {
            a = step * (i + 1);
            c[2].x = d->radius * func_0020B620(a);
            c[2].y = d->radius * func_0020B730(a);
        }
        if (func_00205440(&c[2], cam->view, &pkt.v[2].xyz, &dep[2]) != 0) {
            d->flags |= 0x400000;
        }
        if (func_00104520(d->flags, 0x14) != 0 && func_00104520(d->flags, 0x15) != 0 &&
            func_00104520(d->flags, 0x16) != 0) {
            if (func_00104520(d->flags, 0x13) != 0) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, 0);
                }
            } else if (func_00104520(d->flags, 0x12) != 0) {
                func_002075F0(&pkt, ot, 0xFFFFFF);
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, 0xFFFFFF);
                }
            } else {
                func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2]) / 3.0f));
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2]) / 3.0f));
                }
            }
        }
        d->flags &= 0xFF8FFFFF;
    }
    return 0;
}

/* shape b000:01E01140, 1595 insns, 70 copies: draws an emitter's particles. Each particle is either a camera-facing
   sprite (strip packet, 9 regs) sized by distance, or with flag 0x1F a quad (12 regs) turned by its own rotation;
   UV or ST frames animate per particle; flag 2 respawns a particle on a circle when its animation wraps.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E01140;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E01140;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E01140;

typedef union {
    UV_b000_01E01140 uv;
    struct {
        f32 s, t;
    } st;
} Tc_b000_01E01140;

typedef struct {
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx1_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx1_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt1_b000_01E01140;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx2_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx2_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt2_b000_01E01140;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b000_01E01140;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E01140 color;
    f32 size;
    u8 pad10[0x10];
    Vec4f rot;
    union {
        struct {
            s16 u, v, w, h;
            s16 u0, v0, tw, th;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Pt_b000_01E01140 *pts;
    Vec4f *rots;
    u8 pad48[4];
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b000_01E01140;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E01140;

#define UV1(k) ((UV_b000_01E01140 *)(s32)&p1.v[k].tc)
#define UV2(k) ((UV_b000_01E01140 *)(s32)&p2.v[k].tc)

static s32 func_01E01140_b000(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
    extern s32 func_002058D0(void *, s32, void *, void *, f32 *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    f32 m[16];
    Vec4f c[4];
    Vec4f off;
    Vec4f tmp;
    Vec4f pos;
    Pkt1_b000_01E01140 p1 __attribute__((aligned(8)));
    Pkt2_b000_01E01140 p2 __attribute__((aligned(8)));
    f32 nx;
    f32 ny;
    f32 sx;
    f32 sy;
    s32 i;
    f32 hx;
    f32 hy;
    f32 dz;
    s32 a;

    ((Pkt1_b000_01E01140 *)(s32)&p1)->count = 0x24;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->tag = 9;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->pad = 0;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->count = 0x34;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->tag = 0xC;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->pad = 0;
    if (e->rate == 0) {
        e->rate = 1;
    }
    if (e->r.i.w == e->r.i.h) {
        sy = e->size;
        sx = sy;
    } else if (e->r.i.h < e->r.i.w) {
        sx = e->size;
        sy = sx * ((f32)e->r.i.h / (f32)e->r.i.w);
    } else {
        sy = e->size;
        sx = sy * ((f32)e->r.i.w / (f32)e->r.i.h);
    }
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x44);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x88);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x42);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x48);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x48);
    }
    p1.r = e->color.r;
    p1.g = e->color.g;
    p1.b = e->color.b;
    *(u8 *)(s32)&p1.a = e->color.a;
    p1.q = 1.0f;
    func_01E00100_b000((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
    if (func_00104520(e->flags, 3) != 0) {
        if (func_00104520(e->flags, 0) != 0) {
            ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
            UV1(0)->u = e->r.i.u * 16;
            UV1(0)->v = e->r.i.v * 16;
            UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(1)->v = e->r.i.v * 16;
            UV1(2)->u = e->r.i.u * 16;
            UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
            ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
            UV2(0)->u = e->r.i.u * 16;
            UV2(0)->v = e->r.i.v * 16;
            UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(1)->v = e->r.i.v * 16;
            UV2(2)->u = e->r.i.u * 16;
            UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
        } else {
            p1.v[0].tc.st.s = e->r.f.s;
            p1.v[0].tc.st.t = e->r.f.t;
            p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[1].tc.st.t = e->r.f.t;
            p1.v[2].tc.st.s = e->r.f.s;
            p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[0].tc.st.s = e->r.f.s;
            p2.v[0].tc.st.t = e->r.f.t;
            p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[1].tc.st.t = e->r.f.t;
            p2.v[2].tc.st.s = e->r.f.s;
            p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
        }
    }
    if (func_00104520(e->flags, 0x1C) != 0) {
        func_0020C630(m, &e->rot);
        for (i = 0; i < e->count; i++) {
            tmp.x = e->pts[i].x;
            tmp.y = e->pts[i].y;
            tmp.z = e->pts[i].z;
            func_0020CDD0(&off, m, &tmp);
            e->pts[i].x = off.x;
            e->pts[i].y = off.y;
            e->pts[i].z = off.z;
        }
    }
    nx = -sx;
    ny = -sy;
    for (i = 0; i < e->count; i++) {
        if (e->pts[i].a < e->color.a) {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->pts[i].a;
        } else {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->color.a;
        }
        if (func_00104520(e->flags, 3) == 0) {
            if (func_00104520(e->flags, 0) != 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame % (e->r.i.tw / e->r.i.w));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame / (e->r.i.tw / e->r.i.w));
                } else {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame / (e->r.i.th / e->r.i.h));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame % (e->r.i.th / e->r.i.h));
                }
                ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
                UV1(0)->u = e->r.i.u * 16;
                UV1(0)->v = e->r.i.v * 16;
                UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(1)->v = e->r.i.v * 16;
                UV1(2)->u = e->r.i.u * 16;
                UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
                ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
                UV2(0)->u = e->r.i.u * 16;
                UV2(0)->v = e->r.i.v * 16;
                UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(1)->v = e->r.i.v * 16;
                UV2(2)->u = e->r.i.u * 16;
                UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
            } else {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.w));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.w));
                } else {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.h));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.h));
                }
                p1.v[0].tc.st.s = e->r.f.s;
                p1.v[0].tc.st.t = e->r.f.t;
                p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[1].tc.st.t = e->r.f.t;
                p1.v[2].tc.st.s = e->r.f.s;
                p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[0].tc.st.s = e->r.f.s;
                p2.v[0].tc.st.t = e->r.f.t;
                p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[1].tc.st.t = e->r.f.t;
                p2.v[2].tc.st.s = e->r.f.s;
                p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&p1, e->texture, 0);
            func_00208700(&p2, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&p1, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
                func_00208CB0(&p2, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
            }
            func_00208700(&p1, e->texture, 1);
            func_00208700(&p2, e->texture, 1);
        }
        pos.x = e->pts[i].x;
        pos.y = e->pts[i].y;
        pos.z = e->pts[i].z;
        if (func_00104520(e->flags, 0x1A) != 0) {
            dz = -(e->amp * func_0020B550(e->freq * e->pts[i].t));
            pos.z += dz;
        }
        if (func_00104520(e->flags, 0x1F) != 0) {
            func_0020C630(m, &e->rots[i]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx = sx + sx * e->grow * e->pts[i].t;
                hy = sy + sy * e->grow * e->pts[i].t;
                off.x = -hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = -hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            } else {
                off.x = nx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = nx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            }
        } else {
            if (func_00205440(&pos, cam->view, &p1.v[0].xyz, depth) != 0 && func_00101600(&p1.v[0].xyz) != 0) {
                e->flags |= 0xF00000;
            }
            depth[1] = depth[2] = depth[3] = depth[0];
            hx = 20.0f * func_001018E0(sx, depth[0]);
            hy = 20.0f * func_001018E0(sy, depth[0]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx += sx * e->grow * e->pts[i].t;
                hy += sy * e->grow * e->pts[i].t;
            }
            p1.v[1].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[1].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[2].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[2].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[3].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[3].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[0].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[0].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = p1.v[0].xyz.z;
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
                func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
                if (func_00104520(e->flags, 0x13) != 0) {
                    p1.v[0].xyz.z = p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = 0xFFFFFF;
                    if (e->pts[i].t >= 0) {
                        func_002075F0(&p1, obj, 0);
                    }
                } else if (e->pts[i].t >= 0) {
                    func_002075F0(&p1, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
            e->flags &= 0xFF0FFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->pts[i].t++;
            if (e->pts[i].t % e->rate == 0) {
                e->pts[i].frame++;
                if (e->nframes == e->pts[i].frame) {
                    e->pts[i].frame = 0;
                    if (func_00104520(e->flags, 2) != 0) {
                        if (func_00104520(e->flags, 0x1D) != 0) {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = e->radius * func_0020B550(a);
                            e->pts[i].z = func_0019A5C8() % 20;
                            e->pts[i].x = e->radius * func_0020B480(a);
                        } else {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = func_0019A5C8() % 20;
                            e->pts[i].z = e->radius * func_0020B480(a);
                            e->pts[i].x = e->radius * func_0020B550(a);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/* shape b000:01E02A30, 546 insns, 18 copies: draws one particle as a textured quad of the sprite's size, aspect-scaled,
   rotated by the sprite angle (flag 0x1F) or axis-aligned; depth-sorted unless flag 0x13.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E02A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E02A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E02A30 v[4];
    u8 tail[0x20];
} Pkt_b000_01E02A30;

typedef struct {
    s16 u, v, w, h;
    f32 fw, fh;
    u8 pad10[0x20];
    f32 size;
    Src_b000_01E02A30 color;
    s32 flags;
    u8 pad3C[8];
    s32 angle;
} Spr_b000_01E02A30;

typedef struct {
    void *texture;
    s32 flags;
    f32 scale;
    u8 padC[4];
    f32 x, y, z;
} Part_b000_01E02A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E02A30;

static s32 func_01E02A30_b000(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00104DC0(void *, void *);
    f32 depth[4];
    Vec4f c;
    Pkt_b000_01E02A30 pkt;
    f32 kx;
    f32 ky;
    f32 r;
    f32 cs;
    f32 sn;
    f32 sz;
    f32 hx;
    f32 hy;

    ((Pkt_b000_01E02A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(s->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(s->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(s->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_b000((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
    func_00104DC0(&pkt, s);
    if (func_00104520(s->flags, 5) == 0) {
        if (func_00104520(s->flags, 0) != 0) {
            if (s->w > s->h) {
                kx = 1.0f;
                ky = (f32)s->h / (f32)s->w;
            } else if (s->w < s->h) {
                kx = (f32)s->w / (f32)s->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (s->fw > s->fh) {
                ky = s->fh / s->fw;
                kx = 1.0f;
            } else if (s->fw < s->fh) {
                kx = s->fw / s->fh;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
    } else {
        kx = 1.0f;
        ky = (f32)s->h / (f32)s->w;
    }
    if (func_00104520(s->flags, 0x1F) != 0) {
        r = 0.017453292f * (s->angle % 360);
        cs = func_0020B620(r);
        sn = func_0020B730(r);
        sz = p->scale * s->size;
        hy = ky * sz;
        hx = kx * sz;
        c.x = p->x + (cs * -hx - sn * hy);
        c.y = p->y + (sn * -hx + cs * hy);
        c.z = p->z;
        if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            p->flags |= 0x100000;
        }
        c.x = p->x + (cs * hx - sn * hy);
        c.y = p->y + (sn * hx + cs * hy);
        if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            p->flags |= 0x200000;
        }
        c.x = p->x + (cs * -hx - sn * -hy);
        c.y = p->y + (sn * -hx + cs * -hy);
        if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            p->flags |= 0x400000;
        }
        c.x = p->x + (cs * hx - sn * -hy);
        c.y = p->y + (sn * hx + cs * -hy);
        if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            p->flags |= 0x800000;
        }
    } else {
        c.x = p->x - kx * (p->scale * s->size);
        c.y = p->y + ky * (p->scale * s->size);
        c.z = p->z;
        if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            p->flags |= 0x100000;
        }
        c.x = p->x + kx * (p->scale * s->size);
        c.y = p->y + ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            p->flags |= 0x200000;
        }
        c.x = p->x - kx * (p->scale * s->size);
        c.y = p->y - ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            p->flags |= 0x400000;
        }
        c.x = p->x + kx * (p->scale * s->size);
        c.y = p->y - ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            p->flags |= 0x800000;
        }
    }
    if (func_00104520(s->flags, 0x18) != 0) {
        func_00208700(&pkt, p->texture, 0);
    } else {
        if (func_00104520(s->flags, 0) != 0) {
            func_00208CB0(&pkt, (u64)0xA | ((u64)s->u << 4) | ((u64)(s->u + s->w - 1) << 14) |
                                    ((u64)s->v << 24) | ((u64)(s->v + s->h - 1) << 34));
        }
        func_00208700(&pkt, p->texture, 1);
    }
    if (func_00104520(p->flags, 0x14) != 0 && func_00104520(p->flags, 0x15) != 0 &&
        func_00104520(p->flags, 0x16) != 0 && func_00104520(p->flags, 0x17) != 0) {
        if (func_00104520(s->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, obj, 0);
        } else {
            func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
    }
    p->flags &= 0xFF0FFFFF;
    return 0;
}

/* shape b000:01E032C0, 86 insns, 68 copies: set up an effect object (scale, 4 corner offsets from a local
   table, 16 or 64 random triples) */

typedef struct V4_b000_01E032C0 {
    f32 x, y, z, w;
} V4_b000_01E032C0;

typedef struct Rnd_b000_01E032C0 {
    s32 a, b, c, d;
} Rnd_b000_01E032C0;

typedef struct Obj_b000_01E032C0 {
    s32 kind;
    s32 model;
    s32 pad8;
    f32 scale;
    s32 pad10[4];
    V4_b000_01E032C0 v[4];
    Rnd_b000_01E032C0 r[64];
} Obj_b000_01E032C0;

typedef struct Tbl_b000_01E032C0 {
    V4_b000_01E032C0 v[4];
} Tbl_b000_01E032C0;

static s32 func_01E032C0_b000(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E06480_b000;
    Tbl_b000_01E032C0 tbl = D_01E06480_b000;
    s32 flag;
    s32 n;
    s32 i;

    flag = func_00104520(obj->model, 0x1F);
    obj->scale = scale;
    obj->kind = kind;
    n = flag ? 0x10 : 0x40;
    for (i = 0; i < 4; i++) {
        obj->v[i].x = obj->scale * tbl.v[i].x;
        obj->v[i].y = obj->scale * tbl.v[i].y;
        obj->v[i].z = obj->scale * tbl.v[i].z;
    }
    for (i = 0; i < n; i++) {
        obj->r[i].a = func_0019A5C8() % 0x10000;
        obj->r[i].b = func_0019A5C8() % 0x10000;
        obj->r[i].c = func_0019A5C8() % 0x10000;
    }
    return 0;
}

/* shape b000:01E03420, 387 insns, 68 copies: draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E03420;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        struct {
            f32 s, t;
        } st;
        struct {
            u64 u : 14;
            u64 pad0 : 2;
            u64 v : 14;
            u64 pad1 : 34;
        } uv;
    } tc;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E03420;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E03420;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E03420 v[4];
    u8 tail[0x20];
} Pkt_b000_01E03420;

typedef struct {
    f32 x, y, z, w;
} Vec_b000_01E03420;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E03420 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    Vec_b000_01E03420 p[4];
    Vec_b000_01E03420 rot[1];
} Spr_b000_01E03420;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E03420;

static s32 func_01E03420_b000(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b000_01E03420 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b000_01E03420 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_b000((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b000_01E03420 *)(s32)&pkt)->count |= 0x800;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = spr->rect.f.s;
        pkt.v[0].tc.st.t = spr->rect.f.t;
        pkt.v[1].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[1].tc.st.t = spr->rect.f.t;
        pkt.v[2].tc.st.s = spr->rect.f.s;
        pkt.v[2].tc.st.t = spr->rect.f.t + spr->rect.f.h;
        pkt.v[3].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[3].tc.st.t = spr->rect.f.t + spr->rect.f.h;
    }
    for (i = 0; i < n[0]; i++) {
        func_0020C630(m, &spr->rot[i]);
        func_0020CDD0(&out, m, &spr->p[0]);
        if (func_00205440(&out, cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        func_0020CDD0(&out, m, &spr->p[1]);
        if (func_00205440(&out, cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        func_0020CDD0(&out, m, &spr->p[2]);
        if (func_00205440(&out, cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        func_0020CDD0(&out, m, &spr->p[3]);
        if (func_00205440(&out, cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208700(&pkt, spr->texture, 0);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else if (func_00104520(spr->flags, 0x12) != 0) {
                func_002075F0(&pkt, obj, 0xFFFFFF);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b000_01E03A30;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x1A];
    u8 kind;
    u8 pad23[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b000_01E03A30;

static s32 func_01E03A30_b000(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
    s32 i;
    Pt_b000_01E03A30 *p;
    Pt_b000_01E03A30 *q;
    s32 j;

    i = obj->idx;
    if (i > -1) {
        p = &pts[i];
        do {
            if (p->e > obj->limit && func_00103470(&p->c, 0, obj->kind) == 0 && p[-1].c == 0) {
                obj->idx = i;
            }
            i--;
            p--;
        } while (i > -1);
    }
    if (obj->idx < obj->count - 1) {
        obj->idx++;
        j = obj->idx;
        if (j > 0) {
            q = &pts[j];
            do {
                j--;
                q->x = q[-1].x;
                q->y = q[-1].y;
                q->z = q[-1].z;
                q->d = q[-1].d;
                q->e = q[-1].e;
                q->c = q[-1].c;
                q--;
            } while (j > 0);
        }
        pts->x = pos[0];
        pts->y = pos[1];
        pts->z = pos[2];
        pts->d = 0;
        pts->e = 0;
        pts->c = obj->c;
    }
    return 0;
}

/* shape b000:01E03B80 (LkEFF_SortLaser), 624 insns, 1 copy (-O3,p): b117:01E00270's LkEFF_SortLaser, compiled cold
   (config/mod_warm.txt: b000 0) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E03B80;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b000_01E03B80;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b000_01E03B80 uv;
    Xyz_b000_01E03B80 xyz;
} Vtx_b000_01E03B80;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E03B80 v[4];
    u8 tail[0x20];
} Pkt_b000_01E03B80;

typedef struct {
    s16 u, v, w, h;
} Rect_b000_01E03B80;

typedef struct {
    void *texture;
    u8 color[3];
    u8 a;
    s32 flags;
    f32 base;
    Rect_b000_01E03B80 rect;
    u8 pad18[0xC];
    s16 tick;
    u8 pad26[2];
    s16 n1;
    s16 n2;
} Laser_b000_01E03B80;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b000_01E03B80;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E03B80;

#pragma optimization_level 3

static s32 func_01E03B80_b000(s32 ot __attribute__((aligned(8))), Laser_b000_01E03B80 *o, Pt_b000_01E03B80 *pts, Cam_b000_01E03B80 *cam __attribute__((aligned(8)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b000_01E03B80 s[2];
    Vec4f w;
    Pkt_b000_01E03B80 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    s32 j;
    s32 cnt;
    f32 w0;
    f32 w1;

    if (func_00104520(o->flags, 0x1F) != 0) {
        cnt = o->n1;
    } else {
        cnt = o->n2;
    }
    ((Pkt_b000_01E03B80 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E03B80 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E03B80 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E03B80 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_b000((void *)&pkt, (void *)o->color);
    ((Pkt_b000_01E03B80 *)(s32)&pkt)->count |= 0x800;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[0].uv)->u = o->rect.u << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[0].uv)->v = o->rect.v << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[1].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[1].uv)->v = o->rect.v << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[2].uv)->u = o->rect.u << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[2].uv)->v = (o->rect.v + o->rect.h) << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[3].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b000_01E03B80 *)(s32)&pkt.v[3].uv)->v = (o->rect.v + o->rect.h) << 4;
    for (i = 0; i < cnt + 1; i++) {
        pts[i].age++;
    }
    for (i = 1; i < cnt; i++) {
        w.x = pts[i - 1].x;
        w.y = pts[i - 1].y;
        w.z = pts[i - 1].z;
        if (func_00205440(&w, cam->view, &s[0], &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        w.x = pts[i].x;
        w.y = pts[i].y;
        w.z = pts[i].z;
        if (func_00205440(&w, cam->view, &s[1], &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            w0 = func_001018E0(o->base, depth[0]);
            w1 = func_001018E0(o->base, depth[1]);
            if (o->a >= pts[i - 1].a) {
                pkt.v[0].a = pkt.v[2].a = pts[i - 1].a;
            } else {
                pkt.v[0].a = pkt.v[2].a = o->a;
            }
            if (o->a >= pts[i].a) {
                pkt.v[1].a = pkt.v[3].a = pts[i].a;
            } else {
                pkt.v[1].a = pkt.v[3].a = o->a;
            }
            if (i == 1) {
                pkt.v[0].a = pkt.v[2].a = 0;
            }
            for (j = 0; j < 4; j++) {
                if (j < 2) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                    if (j == 0) {
                        pkt.v[0].xyz.y = s[0].y + w0;
                        pkt.v[1].xyz.y = s[1].y + w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                    if (j == 1) {
                        pkt.v[0].xyz.y = s[0].y - w0;
                        pkt.v[1].xyz.y = s[1].y - w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                } else {
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
                    if (j == 2) {
                        pkt.v[0].xyz.x = s[0].x + w0;
                        pkt.v[1].xyz.x = s[1].x + w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                    if (j == 3) {
                        pkt.v[0].xyz.x = s[0].x - w0;
                        pkt.v[1].xyz.x = s[1].x - w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                }
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->rect.u << 4) | ((u64)(o->rect.u + o->rect.w - 1) << 14) |
                                        ((u64)o->rect.v << 24) | ((u64)(o->rect.v + o->rect.h - 1) << 34));
                func_00208700(&pkt, o->texture, 1);
                if (func_00101600(&pkt.v[0].xyz) != 0 && func_00101600(&pkt.v[1].xyz) != 0) {
                    if (func_00104520(o->flags, 0x13) != 0) {
                        pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                        func_002075F0(&pkt, ot, 0);
                    } else {
                        pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[0].z;
                        pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[1].z;
                        func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1]) / 2.0f));
                    }
                }
            }
        }
        o->flags &= 0xFFCFFFFF;
    }
    o->tick++;
    return 0;
}
#pragma optimization_level reset

/* shape b000:01E04540 (LkEff_SortElectr), 608 insns, 1 copy (-O3,p): draws a lightning bolt between two points: the
   line is cut into n pieces (at most 16), each inner point shaken by a random jitter, all projected; then each piece
   is one textured quad (random texture corner) as wide as its screen length / 3 (or a fixed width), drawn only when
   both ends are visible and the piece is not past the moving head. Calls the module's colour helper (shape
   b000:01E00100). The spilled ot parameter is aligned(8): that puts its home at 0xB8 like the original (plain s32
   gives 0xBC). The depth goes through an explicit func_001A23B0 call, not a (u32) cast: b021's twins' cast lets
   the compiler keep &pkt / ot in $a0 / $a1 across the helper, which pushes the z stores' temps to $a2 / $a3. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E04540;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b000_01E04540 xyz;
} Vtx_b000_01E04540;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E04540 v[4];
    u8 tail[0x20];
} Pkt_b000_01E04540;

typedef struct {
    s16 u, v, w, h;
} Rect_b000_01E04540;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    s16 n;
    s16 jitter;
    Rect_b000_01E04540 rect;
    u8 pad18[0x10];
    s16 head;
    u8 pad2A[2];
    f32 width;
} Bolt_b000_01E04540;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E04540;

#pragma optimization_level 3

static s32 func_01E04540_b000(s32 ot __attribute__((aligned(8))), Bolt_b000_01E04540 *b, Cam_b000_01E04540 *cam, Vec4f *p1, Vec4f *p2) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b000_01E04540 s[17];
    Vec4f mid;
    f32 depth[17];
    Pkt_b000_01E04540 pkt;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 w;
    f32 len;
    s32 vis;
    s32 k;
    s32 r;

    vis = 0;
    if (b->n > 16) {
        b->n = 16;
    }
    ((Pkt_b000_01E04540 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E04540 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E04540 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E04540 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_01E00100_b000((Vtx_b000_01E00100 *)&pkt, &b->color);
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    dz = p2->z - p1->z;
    if (func_00205440(p1, cam->view, &s[0], &depth[0]) != 0) {
        if (func_00101600(&s[0]) != 0) {
            vis |= 1;
        }
    }
    for (k = 1; k < b->n; k++) {
        t = (f32)k / b->n;
        if (b->jitter != 0) {
            mid.x = p1->x + dx * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
            mid.y = p1->y + dy * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
            mid.z = p1->z + dz * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
        } else {
            mid.x = p1->x + dx * t;
            mid.y = p1->y + dy * t;
            mid.z = p1->z + dz * t;
        }
        if (func_00205440(&mid, cam->view, &s[k], &depth[k]) != 0) {
            if (func_00101600(&s[k]) != 0) {
                vis |= 1 << k;
            }
        }
    }
    if (func_00205440(p2, cam->view, &s[b->n], &depth[b->n]) != 0) {
        if (func_00101600(&s[b->n]) != 0) {
            vis |= 1 << b->n;
        }
    }
    for (k = 0; k < b->n; k++) {
        if (func_00104520(b->flags, 0x1A) != 0 || k <= b->head) {
            r = func_0019A5C8() % 4;
            if (r == 0) {
                func_00104540(&pkt, &b->rect, 1);
            } else if (r == 1) {
                func_00104540(&pkt, &b->rect, 2);
            } else if (r == 2) {
                func_00104540(&pkt, &b->rect, 5);
            } else {
                func_00104540(&pkt, &b->rect, 7);
            }
            dx = func_001A6970((s32)(s[k].x - s[k + 1].x));
            dy = func_001A6970((s32)(s[k].y - s[k + 1].y));
            len = func_001A6C60(dx * dx + dy * dy);
            if (func_00104520(b->flags, 0x1B) != 0) {
                w = b->width;
            } else {
                w = len / 3.0f;
            }
            if (dx > dy) {
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[k].x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[k + 1].x;
                pkt.v[0].xyz.y = s[k].y - w;
                pkt.v[1].xyz.y = s[k + 1].y - w;
                pkt.v[2].xyz.y = w + s[k].y;
                pkt.v[3].xyz.y = w + s[k + 1].y;
            } else {
                pkt.v[0].xyz.x = s[k].x - w;
                pkt.v[1].xyz.x = s[k + 1].x - w;
                pkt.v[2].xyz.x = w + s[k].x;
                pkt.v[3].xyz.x = w + s[k + 1].x;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[k].y;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[k + 1].y;
            }
            func_00208CB0(&pkt, 2 | (2 << 2) | ((u64)b->rect.u << 4) | ((u64)(b->rect.u + b->rect.w - 1) << 14) |
                                    ((u64)b->rect.v << 24) | ((u64)(b->rect.v + b->rect.h - 1) << 34));
            func_00208700(&pkt, b->texture, 1);
            if (func_00104520(vis, k) != 0 && func_00104520(vis, k + 1) != 0) {
                if (func_00104520(b->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[k].z;
                    pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[k + 1].z;
                    func_002075F0(&pkt, ot, func_001A23B0((depth[k] + depth[k + 1]) / 2.0f));
                }
            }
        }
    }
    b->head++;
    if (b->head > b->n) {
        b->head = 0;
    }
    return 0;
}

#pragma optimization_level reset

/* shape b000:01E04EC0, 148 insns, 12 copies: seed n points with random positions: flag 0x1D set and v < 0:
   +-50 / +-50 / 0..50, flag set and v >= 0: +-240 / +-240 / 240..480, flag clear: tenths of +-240 / 0..240 */

typedef struct Pt_b000_01E04EC0 {
    f32 x, y, z, w;
} Pt_b000_01E04EC0;

typedef struct Obj_b000_01E04EC0 {
    s32 flags;
    u8 pad4[4];
    f32 f8;
    s32 count;
    Pt_b000_01E04EC0 pts[1];
} Obj_b000_01E04EC0;

static s32 func_01E04EC0_b000(Obj_b000_01E04EC0 *o, s32 n, f32 v) {
    extern f32 func_001A6970(f32);
    extern s32 func_0019A5C8();
    s32 i;

    o->f8 = func_001A6970(v);
    o->count = n;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (v < 0.0f) {
                o->pts[i].x = func_0019A5C8() % 100 - 50;
                o->pts[i].y = func_0019A5C8() % 100 - 50;
                o->pts[i].z = func_0019A5C8() % 50;
            } else {
                o->pts[i].x = func_0019A5C8() % 480 - 240;
                o->pts[i].y = func_0019A5C8() % 480 - 240;
                o->pts[i].z = func_0019A5C8() % 240 + 240;
            }
        } else {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
    }
    return 0;
}

/* shape b000:01E05110, 344 insns, 12 copies: draws falling streaks (rain/snow): each point is drawn as a line
   from it along its normalised direction, then moved; points that fall past the floor are reseeded (the two
   ranges of b000:01E04EC0); drawn twice with flag 0x1C. Calls the module's line colour helper (b000:01E00080),
   included above as a static function. */

typedef struct Pt_b000_01E05110 {
    f32 x, y, z, w;
} Pt_b000_01E05110;

typedef struct Obj_b000_01E05110 {
    s32 flags;
    Src_b000_01E00080 color;
    f32 len;
    s32 count;
    Pt_b000_01E05110 pts[1];
} Obj_b000_01E05110;

typedef struct Cam_b000_01E05110 {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E05110;

typedef struct LPk_b000_01E05110 {
    s16 size;
    s16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b000_01E00080 v[2];
} LPk_b000_01E05110;

static s32 func_01E05110_b000(s32 obj, Obj_b000_01E05110 *o, Cam_b000_01E05110 *cam, f32 v) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020D070();
    extern s32 func_0019A5C8();
    Vec4f a;
    Vec4f b;
    LPk_b000_01E05110 pk;
    f32 depth[2];
    s32 i;

    ((LPk_b000_01E05110 *)(s32)&pk)->flags = 0x11;
    ((LPk_b000_01E05110 *)(s32)&pk)->size = 4;
    ((LPk_b000_01E05110 *)(s32)&pk)->regs = 0x4141;
    ((LPk_b000_01E05110 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < o->count; i++) {
        if (!(v < 0.0f)) {
            func_01E00080_b000((Pk_b000_01E00080 *)&pk, &o->color, 0);
        } else {
            func_01E00080_b000((Pk_b000_01E00080 *)&pk, &o->color, 1);
        }
        a.x = b.x = o->pts[i].x;
        a.y = b.y = o->pts[i].y;
        a.z = b.z = o->pts[i].z;
        if (func_00205440(&a, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        func_0020D070(&a);
        b.x += a.x * o->len;
        b.y += a.y * o->len;
        b.z += a.z * o->len;
        if (func_00205440(&b, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        o->pts[i].x -= a.x * v;
        o->pts[i].y -= a.y * v;
        o->pts[i].z -= a.z * v;
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (!(o->pts[i].z < 300.0f)) {
                o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].y = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].z = 0.1f * (func_0019A5C8() % 240);
            }
        } else if (o->pts[i].y <= 0.0f) {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, 0);
                }
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                }
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b000:01E05670 (b000), 875 insns, 1 copy: b000 scene manager in b185:01E03A90's family (b628:01E046A0's form):
   seven cameras, eight bolts, a laser, a particle emitter, discs, a line and a rotating sprite set; joints
   0x79/0x7D/0x81/0x78/0x7A; returns 2/1 at 0x11E/0xAC, 6 on 0xB6..0x11D, 8 when the timer ends */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Cam_b000_01E05670;

typedef struct {
    s32 tex;
    u8 c[3];
    u8 a;
    s32 flags;
    f32 base;
    s16 uv[8];
    u8 pad20[2];
    s16 h22;
    s16 tick;
    s16 h26;
    s16 n1;
    s16 n2;
    s16 h2C;
    u8 pad2E[2];
} Laser_b000_01E05670;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b000_01E05670;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    s16 n;
    s16 jitter;
    s16 uv[4];
    u8 pad18[8];
    f32 f20;
    f32 f24;
    s16 head;
    u8 pad2A[6];
} Bolt_b000_01E05670;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 size;
    u8 c[4];
    s32 flags;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Spr_b000_01E05670;

typedef struct {
    s32 tex;
    u8 pad4[4];
    f32 scale;
    u8 c[4];
    f32 x, y, z;
    u8 pad1C[4];
} Part_b000_01E05670;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 uv[8];
    Pt_b000_01E05670 *pts;
    s32 rots;
    s32 x48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b000_01E05670;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b000_01E05670;

typedef struct {
    s32 kind;
    s32 flags;
    u8 c[4];
    f32 scale;
    s16 uv[4];
    u8 pad18[8];
    Vec4f v[4];
    s32 r[64][4];
} Rs_b000_01E05670;

typedef struct {
    s32 flags;
    u8 c[4];
    u8 pad8[0x408];
} Line_b000_01E05670;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 f8;
    s16 count;
    s16 model;
} Shot_b000_01E05670;

typedef struct {
    Cam_b000_01E05670 c0;
    Laser_b000_01E05670 laser;
    Pt_b000_01E05670 lpts[32];
    Bolt_b000_01E05670 bolt[8];
    Cam_b000_01E05670 c1;
    Spr_b000_01E05670 spr;
    Part_b000_01E05670 part;
    Emit_b000_01E05670 emit;
    Pt_b000_01E05670 pts[0x80];
    Cam_b000_01E05670 c2;
    Disc_b000_01E05670 disc;
    Cam_b000_01E05670 c3;
    Rs_b000_01E05670 rs;
    Line_b000_01E05670 line;
    Cam_b000_01E05670 c4;
    Disc_b000_01E05670 disc2;
    Cam_b000_01E05670 c5;
    Disc_b000_01E05670 disc3;
    Cam_b000_01E05670 c6;
    Shot_b000_01E05670 shot;
    Vec4f vec[8];
    Vec4f tgt;
    u8 src1[4];
    u8 src2[4];
    s32 cnt;
    s32 timer;
    s32 t;
    s32 code;
    s32 ang;
    s32 j[5];
} Scene_b000_01E05670;

static s32 func_01E05670_b000(s32 arg0, s32 code) {
    Scene_b000_01E05670 *g = (Scene_b000_01E05670 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern void func_001043F0(void *, f32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern s32 func_00103580(void *, f32, f32);
    extern void func_00103540(f32 *, f32, f32);
    extern s32 func_0019A5C8();
    Vec4f w;
    Vec4f a;
    Vec4f b;
    s32 tx[4];
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1910);
        func_00103890(&g->c0);
        func_00103890(&g->c1);
        func_00103890(&g->c3);
        func_00103890(&g->c2);
        func_00103890(&g->c6);
        func_00103890(&g->c4);
        func_00103890(&g->c5);
        g->j[0] = func_001F5560(func_001F53A0(), 0x79, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x7D, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x81, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x78, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x7A, 0);
        g->timer = 0x12E;
        g->t = 1;
        g->code = code;
        g->cnt = 0x18;
        g->src1[2] = 0x10;
        g->src1[1] = 0x60;
        g->src1[0] = 0x80;
        g->src1[3] = 0;
        g->ang = 0xC000;
        g->src2[2] = 0x80;
        g->src2[1] = 0x80;
        g->src2[0] = 0x80;
        g->src2[3] = 0;
        g->shot.flags = 0x80400;
        g->shot.c[2] = 0x80;
        g->shot.c[1] = 0x80;
        g->shot.c[0] = 0x80;
        g->shot.c[3] = 0;
        g->shot.f8 = 0.3f;
        g->shot.count = 0xA;
        g->shot.model = func_001F5380();
        g->disc2.flags = 0x80000;
        g->disc2.c[2] = 0x60;
        g->disc2.c[1] = 0x60;
        g->disc2.c[0] = 0xA0;
        g->disc2.c[3] = 0xFF;
        g->disc2.radius = 1.0f;
        g->disc2.count = 0x24;
        g->disc2.height = 0;
        g->disc3.flags = 0x80000;
        g->disc3.c[2] = 0x70;
        g->disc3.c[1] = 0xA0;
        g->disc3.c[0] = 0xD0;
        g->disc3.c[3] = 0x80;
        g->disc3.radius = 1.0f;
        g->disc3.count = 0x24;
        g->disc3.height = 0;
        g->disc.flags = 0x80000;
        g->disc.c[2] = 0x70;
        g->disc.c[1] = 0xA0;
        g->disc.c[0] = 0xD0;
        g->disc.c[3] = 0;
        g->disc.radius = 5.0f;
        g->disc.count = 0x20;
        g->disc.height = 0;
        g->line.flags = 0x30080001;
        g->line.c[2] = 0x80;
        g->line.c[1] = 0x80;
        g->line.c[0] = 0xE0;
        g->line.c[3] = 0x80;
        { f32 fs2 = 10.0f; func_01E04EC0_b000((Obj_b000_01E04EC0 *)&g->line, 0x40, fs2); }
        func_00103290(tx, 0);
        for (i = 0; i < 8; i++) {
            g->bolt[i].tex = tx[0];
            g->bolt[i].flags = 0;
            g->bolt[i].uv[0] = 0x80;
            g->bolt[i].uv[1] = 0x40;
            g->bolt[i].uv[2] = 0x20;
            g->bolt[i].uv[3] = 0x40;
            g->bolt[i].c[2] = 0x80;
            g->bolt[i].c[1] = 0x80;
            g->bolt[i].c[0] = 0x80;
            g->bolt[i].c[3] = 0x40;
            g->bolt[i].n = 0x10;
            g->bolt[i].head = -(i + 1);
            g->bolt[i].jitter = 0xA;
            g->bolt[i].f20 = 0.0f;
            g->bolt[i].f24 = 0.0f;
            { f32 fs1 = 8.0f; func_001043F0(&g->vec[i], fs1); }
        }
        func_00103290(tx, 1);
        g->emit.tex = tx[0];
        g->emit.flags = 0x70000003;
        g->emit.c[2] = 0x80;
        g->emit.c[1] = 0x80;
        g->emit.c[0] = 0x80;
        g->emit.c[3] = 0;
        g->emit.size = 0.5f;
        g->emit.rot[0] = 0;
        g->emit.rot[1] = 0;
        g->emit.rot[2] = 0;
        g->emit.uv[0] = 0;
        g->emit.uv[1] = 0;
        g->emit.uv[2] = 0x20;
        g->emit.uv[3] = 0x20;
        g->emit.uv[4] = 0;
        g->emit.uv[5] = 0;
        g->emit.uv[6] = 0x80;
        g->emit.uv[7] = 0x40;
        g->emit.pts = g->pts;
        g->emit.rots = 0;
        g->emit.x48 = 0;
        g->emit.radius = 15.0f;
        g->emit.count = 0x80;
        g->emit.nframes = 8;
        g->emit.rate = 0;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&w, 8.0f);
            g->pts[i].x = w.x;
            g->pts[i].y = w.y;
            g->pts[i].z = w.z;
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x30;
            g->pts[i].frame = 0;
        }
        func_00103260(tx, 0xF);
        g->rs.flags = 1;
        g->rs.uv[0] = 0x8E;
        g->rs.uv[1] = 0;
        g->rs.uv[2] = 0x22;
        g->rs.uv[3] = 0x40;
        g->rs.c[2] = 0x70;
        g->rs.c[1] = 0xA0;
        g->rs.c[0] = 0xD0;
        g->rs.c[3] = 0x20;
        { f32 fs2 = 0.5f; func_01E032C0_b000((Obj_b000_01E032C0 *)&g->rs, tx[0], fs2); }
        for (i = 0; i < 0x40; i++) {
            g->rs.r[i][0] = func_0019A5C8() % 0x2000 - 0x1000;
            g->rs.r[i][1] = func_0019A5C8() % 0x10000;
            g->rs.r[i][2] = func_0019A5C8() % 0x6000 - 0x3000;
        }
        func_00103290(tx, 2);
        g->laser.tex = tx[0];
        g->laser.flags = 0x8003;
        g->laser.c[2] = 0x80;
        g->laser.c[1] = 0x80;
        g->laser.c[0] = 0x80;
        g->laser.a = 0x80;
        g->laser.uv[0] = 0x10;
        g->laser.uv[1] = 0;
        g->laser.uv[2] = 0x10;
        g->laser.uv[3] = 0x20;
        g->laser.uv[4] = 0x10;
        g->laser.uv[5] = 0;
        g->laser.uv[6] = 0x80;
        g->laser.uv[7] = 0x40;
        g->laser.base = 80.0f;
        g->laser.h22 = 0x10;
        g->laser.tick = 0;
        g->laser.h26 = 0x32;
        g->laser.n1 = 0x20;
        g->laser.n2 = 0;
        g->laser.h2C = 1;
        g->spr.flags = 0x80001;
        g->spr.uv[0] = 0x20;
        g->spr.uv[1] = 0x20;
        g->spr.uv[2] = 0x20;
        g->spr.uv[3] = 0x20;
        g->spr.uv[4] = 0x20;
        g->spr.uv[5] = 0x20;
        g->spr.uv[6] = 0x80;
        g->spr.uv[7] = 0x40;
        g->spr.size = 1.0f;
        g->spr.c[2] = 0x80;
        g->spr.c[1] = 0x80;
        g->spr.c[0] = 0x80;
        g->spr.c[3] = 0;
        g->spr.h48 = 0;
        g->spr.h4A = 0;
        g->spr.h4C = 0;
        g->spr.h4E = 1;
        g->spr.h50 = 0;
        g->spr.h52 = 0x3E7;
        {
            s32 tex = tx[0];

            g->part.z = 0.0f;
            g->part.y = 0.0f;
            g->part.x = 0.0f;
            g->part.scale = 5.0f;
            g->part.tex = tex;
        }
        g->part.c[2] = 0x80;
        g->part.c[1] = 0x80;
        g->part.c[0] = 0x80;
        g->part.c[3] = 0x80;
        g->c3.x = g->c3.y = g->c3.z = 0.1f;
        return 0;
    }
    func_001F53C0(1, func_001F5380(), &g->c6.pos);
    func_001F5620(func_001F53A0(), g->j[1], &g->c2.pos);
    func_001F5620(func_001F53A0(), g->j[3], &g->c4.pos);
    func_001F5620(func_001F53A0(), g->j[4], &g->c5.pos);
    if (g->t < 0xA0) {
        func_001F5620(func_001F53A0(), g->j[1], &g->c1.pos);
        func_001F5620(func_001F53A0(), g->j[1], &a);
        func_001F5620(func_001F53A0(), g->j[2], &b);
        func_00103DB0(&a, &b, &g->c3.rot);
        func_001036E0(&a, &b, &g->c3.pos);
        if (g->t >= 0x64) {
            if (g->t % 2 == 0) {
                g->c1.x = g->c1.y = g->c1.z = 0.8f;
            } else {
                g->c1.x = g->c1.y = g->c1.z = 1.0f;
            }
        }
    } else {
        if (g->t == 0xA0) {
            func_001F5620(func_001F53A0(), g->j[2], &a);
            a.y += 1.0f;
            g->c1.pos.y += 1.0f;
            func_01E03A30_b000((Obj_b000_01E03A30 *)&g->laser, (Pt_b000_01E03A30 *)g->lpts, (f32 *)&a);
            g->c1.x = g->c1.y = g->c1.z = 1.0f;
        } else {
            func_001F5F90(func_001F5380(), &g->tgt);
        }
        func_00104490(&g->c1.pos, &g->tgt, g->cnt);
        if (g->cnt != 0) {
            { f32 fs2 = 0.2f; func_001033D0(&g->c1, 5.0f, fs2); }
            g->cnt--;
            func_01E03A30_b000((Obj_b000_01E03A30 *)&g->laser, (Pt_b000_01E03A30 *)g->lpts, (f32 *)&g->c1.pos);
        } else {
            { extern s32 func_001033D0(void *, f32, f32); func_001033D0(&g->c1, 20.0f, 0.5f); }
            func_001F5F90(func_001F5380(), &g->c1.pos);
            { f32 fs1 = 0.0f; func_00103540(&g->laser.base, fs1, 8.0f); }
        }
    }
    if (g->t == 0x29) {
        g->c2.x = g->c2.y = g->c2.z = 1.5f;
    }
    if (g->t == 0x49) {
        g->c2.x = g->c2.y = g->c2.z = 0.7f;
    }
    func_001038D0(&g->c0);
    func_001039A0(&g->c1);
    func_001039A0(&g->c2);
    func_001038D0(&g->c3);
    func_001039A0(&g->c6);
    func_001039A0(&g->c4);
    func_001039A0(&g->c5);
    if (g->t >= 0xB6) {
        func_01E00400_b000(ot, (Src_b000_01E00400 *)g->src2);
        if (g->t < 0xD5) {
            func_001032C0(&g->src2[3], 0xFF, 8);
        } else {
            func_00103470(&g->src2[3], 0, 8);
        }
    }
    if (g->t >= 0xD5) {
        func_01E00560_b000((Obj_b000_01E00560 *)&g->shot, &g->c1.pos);
        func_001032C0(&g->shot.c[3], 0x40, 4);
    }
    if (g->t < 0x90) {
        g->ang += 0x800;
        g->src1[3] = (u8)(s32)(64.0f * func_0020B550(g->ang % 0x10000)) + 0x40;
    } else if (g->t > 0x87 && g->t <= 0x11D) {
        func_001032C0(&g->src1[3], 0x80, 4);
    } else if (g->t >= 0x11E) {
        func_00103470(&g->src1[3], 0, 4);
    }
    func_01E001A0_b000(g->src1);
    if (g->t < 0x29) {
        { extern s32 func_001033D0(void *, f32, f32); f32 fs1 = 1.0f; f32 fs2 = 0.05f; func_001033D0(&g->c3, fs1, fs2); }
        func_001032C0(&g->disc.c[3], 0xFF, 8);
    } else if (g->t > 0x29 && g->t <= 0x48) {
        { extern s32 func_00103580(void *, f32, f32); f32 fs1; f32 fs2; fs2 = 0.02f; fs1 = 0.7f; func_00103580(&g->c2, fs1, fs2); }
        if (g->t % 2 == 0) {
            g->disc.c[3] = 0xFF;
        } else {
            g->disc.c[3] = 0x80;
        }
    } else if (g->t >= 0x49) {
        func_00103470(&g->rs.c[3], 0, 2);
    }
    if (g->t > 0xA0) {
        g->disc.c[3] = 0x80;
        { f32 fs1 = 2.0f; f32 fs2 = 0.1f; func_001033D0(&g->c2, fs1, fs2); }
        if (g->t >= 0xB0) {
            func_00103470(&g->disc.c[3], 0, 4);
        }
    }
    func_01E00BE0_b000(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->c2);
    func_01E03420_b000(ot, (Spr_b000_01E03420 *)&g->rs, (Cam_b000_01E03420 *)&g->c3);
    if (g->t >= 0x43) {
        func_01E02A30_b000(ot, (Spr_b000_01E02A30 *)&g->spr, (Part_b000_01E02A30 *)&g->part, (Cam_b000_01E02A30 *)&g->c1);
        func_001032C0(&g->spr.c[3], 0x80, 8);
        {
            f32 fs1 = 1.5f;

            func_01E05110_b000(ot, (Obj_b000_01E05110 *)&g->line, (Cam_b000_01E05110 *)&g->c1, fs1);
        }
        func_01E01140_b000(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->c1);
        func_001032C0(&g->emit.c[3], 0x80, 3);
        if (g->t >= 0xB6) {
            g->emit.size = 10.0f;
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts[i].t >= 0) {
                g->pts[i].x *= 0.9f;
                g->pts[i].y *= 0.9f;
                g->pts[i].z *= 0.9f;
            }
            if (g->pts[i].t >= 8) {
                { f32 fs1 = 8.0f; func_001043F0(&w, fs1); }
                g->pts[i].x = w.x;
                g->pts[i].y = w.y;
                g->pts[i].z = w.z;
                g->pts[i].t = 0;
            }
        }
        a.x = a.y = a.z = 0.0f;
        for (i = 0; i < 8; i++) {
            func_01E04540_b000(ot, (Bolt_b000_01E04540 *)&g->bolt[i], (Cam_b000_01E04540 *)&g->c1, &a, &g->vec[i]);
            if (g->bolt[i].head == 0) {
                { extern void func_001043F0(void *, f32); f32 fs1 = 8.0f; func_001043F0(&g->vec[i], fs1); }
            }
        }
    }
    if (g->t >= 0xA0) {
        func_01E03B80_b000(ot, (Laser_b000_01E03B80 *)&g->laser, (Pt_b000_01E03B80 *)g->lpts, (Cam_b000_01E03B80 *)&g->c0);
        for (i = 0; i < g->laser.n2; i++) {
            func_00103470(&g->lpts[i].a, 0, 5);
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x11E) {
        return 2;
    }
    if (g->t == 0xAC) {
        return 1;
    }
    if (g->t >= 0xB6 && g->t < 0x11E) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
