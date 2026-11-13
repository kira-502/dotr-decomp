#include "common.h"

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

static void func_01E00080_b385(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b001:01E00900, 73 insns, 54 copies: one GS sprite (RGBAQ, ST, XYZ2, ST, XYZ2) sent with the current texture */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b001_01E00900;

typedef struct {
    Hdr_b001_01E00900 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b001_01E00900;

static s32 func_01E00120_b385(void) {
    Pkt_b001_01E00900 p __attribute__((aligned(8)));

    ((Hdr_b001_01E00900 *)(s32)&p)->count = 0x26;
    ((Hdr_b001_01E00900 *)(s32)&p)->tag = 5;
    ((Hdr_b001_01E00900 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b001_01E00900 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0x60;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    return 0;
}

typedef struct {
    f32 x, y, z;
} P3_b364_01E02A90;

typedef struct {
    s32 id;
    u8 pad4[8];
    f32 r;
    u8 pad10[0x10];
    P3_b364_01E02A90 p[16][32];
} Dome_b364_01E02A90;

static s32 func_01E00250_b385(Dome_b364_01E02A90 *o, s32 id, f32 r) {
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    s32 i;
    s32 j;
    f32 a;
    f32 b;

    o->id = id;
    o->r = r;
    for (i = 0; i < 16; i++) {
        a = r * func_0020B480(0x4000 - i * 0x888);
        b = r * func_0020B550(0x4000 - i * 0x888);
        for (j = 0; j < 32; j++) {
            o->p[i][j].z = a * func_0020B480(j * 0x800);
            o->p[i][j].x = a * func_0020B550(j * 0x800);
            o->p[i][j].y = b;
        }
    }
    return 0;
}

/* shape b364:01E02B80, 434 insns, 2 copies: draws a textured cylinder-like grid of 15 x 32 quads from a 16 x 32 point mesh
   (each column wrapping to the last one), texture spread over the grid; corners' visibility flagged on the object
   (bits 20..23), drawn when all four project, far by flag 0x13; blend by flags 0xC/0xB/0xA. Colour by the module
   helper (shape b000:01E00100). */

typedef struct {
    f32 x, y, z;
} V3_b364_01E02B80;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b364_01E02B80;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b364_01E02B80 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b364_01E02B80;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b364_01E02B80 v[4];
    u8 tail[0x20];
} Pkt_b364_01E02B80;

typedef struct {
    void *texture;
    s32 flags;
    u8 col[8];
    s16 u, v, w, h;
    u8 pad18[8];
    V3_b364_01E02B80 p[16][32];
} Grid_b364_01E02B80;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_b364_01E02B80;

static s32 func_01E00340_b385(s32 ot, Grid_b364_01E02B80 *o, Cam_b364_01E02B80 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 d[4];
    Pkt_b364_01E02B80 pkt;
    s32 r;
    s32 c;
    s16 us;
    s16 vs;

    ((Pkt_b364_01E02B80 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b364_01E02B80 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b364_01E02B80 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b364_01E02B80 *)(s32)&pkt)->pad = 0;
    ((Pkt_b364_01E02B80 *)(s32)&pkt)->count |= 0x800;
    func_00208CB0(&pkt, ((u64)o->v << 24) | (((u64)(o->w - 1) << 4) | 0xB | ((u64)o->u << 14)) |
                            ((u64)(o->v + o->h - 1) << 34));
    func_00208700(&pkt, o->texture, 1);
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b385((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)o->col);
    us = o->w >> 5;
    vs = o->h >> 4;
    for (r = 1; r < 16; r++) {
        for (c = 0; c < 32; c++) {
            if (c == 0) {
                if (func_00205440(&o->p[r - 1][31], cam->m, &pkt.v[0].st + 1, &d[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (func_00205440(&o->p[r][31], cam->m, &pkt.v[1].st + 1, &d[1]) != 0) {
                    o->flags |= 0x200000;
                }
            } else {
                if (func_00205440(&o->p[r - 1][c - 1], cam->m, &pkt.v[0].st + 1, &d[0]) != 0) {
                    o->flags |= 0x100000;
                }
                if (func_00205440(&o->p[r][c - 1], cam->m, &pkt.v[1].st + 1, &d[1]) != 0) {
                    o->flags |= 0x200000;
                }
            }
            if (func_00205440(&o->p[r - 1][c], cam->m, &pkt.v[2].st + 1, &d[2]) != 0) {
                o->flags |= 0x400000;
            }
            if (func_00205440(&o->p[r][c], cam->m, &pkt.v[3].st + 1, &d[3]) != 0) {
                o->flags |= 0x800000;
            }
            pkt.v[0].st.s = (c * us) * 16;
            ((Uv_b364_01E02B80 *)(s32)&pkt.v[0].st)->t = (vs * (r - 1)) * 16;
            pkt.v[1].st.s = (c * us) * 16;
            ((Uv_b364_01E02B80 *)(s32)&pkt.v[1].st)->t = (r * vs) * 16;
            pkt.v[2].st.s = (us * (c + 1)) * 16;
            ((Uv_b364_01E02B80 *)(s32)&pkt.v[2].st)->t = (vs * (r - 1)) * 16;
            pkt.v[3].st.s = (us * (c + 1)) * 16;
            ((Uv_b364_01E02B80 *)(s32)&pkt.v[3].st)->t = (r * vs) * 16;
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                       func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
            o->flags &= 0xFF0FFFFF;
        }
    }
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

static s32 func_01E00A10_b385(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

static s32 func_01E00F70_b385(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
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

/* shape b117:01E00270, 624 insns, 28 copies (-O3,p): LkEFF_SortLaser: draws a laser trail through cnt points (0x10
   bytes each), every point aged first: each piece between two projected points is four textured quads (above, below,
   right, left of the line) as wide as func_001018E0(base, depth), skipped unless both corners are on screen; alpha =
   min(object alpha, point alpha), first piece fades in from 0. Colour from the module helper b117:01E00080. Both
   spilled parameters are aligned(8) to put their homes at 0xE8/0xE0. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b117_01E00270;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b117_01E00270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b117_01E00270 uv;
    Xyz_b117_01E00270 xyz;
} Vtx_b117_01E00270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b117_01E00270 v[4];
    u8 tail[0x20];
} Pkt_b117_01E00270;

typedef struct {
    s16 u, v, w, h;
} Rect_b117_01E00270;

typedef struct {
    void *texture;
    u8 color[3];
    u8 a;
    s32 flags;
    f32 base;
    Rect_b117_01E00270 rect;
    u8 pad18[0xC];
    s16 tick;
    u8 pad26[2];
    s16 n1;
    s16 n2;
} Laser_b117_01E00270;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b117_01E00270;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b117_01E00270;

#pragma optimization_level 3

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E010C0_b385(s32 ot __attribute__((aligned(8))), Laser_b117_01E00270 *o, Pt_b117_01E00270 *pts, Cam_b117_01E00270 *cam __attribute__((aligned(8)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b117_01E00270 s[2];
    Vec4f w;
    Pkt_b117_01E00270 pkt __attribute__((aligned(8)));
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
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b385((void *)&pkt, (void *)o->color);
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count |= 0x800;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->v = (o->rect.v + o->rect.h) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->v = (o->rect.v + o->rect.h) << 4;
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

/* shape b087:01E03B30, 87 insns, 9 copies: set up a ribbon sprite object (scale, 4 corner offsets from a local
   table sized by the object's widths/heights, 16 or 64 evenly spread angles) */

typedef struct V4_b087_01E03B30 {
    f32 x, y, z, w;
} V4_b087_01E03B30;

typedef struct Rnd_b087_01E03B30 {
    s32 a, b, c, d;
} Rnd_b087_01E03B30;

typedef struct Obj_b087_01E03B30 {
    s32 kind;
    s32 model;
    s32 pad8;
    f32 scale;
    s32 pad10[4];
    f32 w0;
    f32 w1;
    f32 h0;
    f32 h1;
    V4_b087_01E03B30 v[4];
    Rnd_b087_01E03B30 r[64];
} Obj_b087_01E03B30;

typedef struct W_tbl_func_01E01A80_b385 {
    V4_b087_01E03B30 v[4];
} W_tbl_func_01E01A80_b385;

static s32 func_01E01A80_b385(Obj_b087_01E03B30 *obj, s32 kind, f32 scale) {
    extern W_tbl_func_01E01A80_b385 D_01E03400_b385;
    W_tbl_func_01E01A80_b385 tbl_w = D_01E03400_b385;
    s32 flag;
    s32 n;
    s32 i;

    tbl_w.v[0].x = -obj->w0;
    tbl_w.v[0].y = obj->h0 + obj->h1;
    tbl_w.v[1].y = obj->h0 + obj->h1;
    tbl_w.v[2].x = -obj->w1;
    tbl_w.v[2].y = obj->h1;
    tbl_w.v[3].y = obj->h1;
    flag = func_00104520(obj->model, 0x1F);
    obj->scale = scale;
    obj->kind = kind;
    n = flag ? 0x10 : 0x40;
    for (i = 0; i < 4; i++) {
        obj->v[i].x = obj->scale * tbl_w.v[i].x;
        obj->v[i].y = obj->scale * tbl_w.v[i].y;
        obj->v[i].z = obj->scale * tbl_w.v[i].z;
    }
    for (i = 0; i < n; i++) {
        obj->r[i].b = 0x10000 / n * i;
    }
    return 0;
}

/* shape b087:01E03C90, 387 insns, 9 copies (b000:01E03420 with the corner list 16 bytes later): draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b087_01E03C90;

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
} Vtx_b087_01E03C90;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b087_01E03C90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b087_01E03C90 v[4];
    u8 tail[0x20];
} Pkt_b087_01E03C90;

typedef struct {
    f32 x, y, z, w;
} Vec_b087_01E03C90;

typedef struct {
    void *texture;
    s32 flags;
    Src_b087_01E03C90 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    u8 pad20[0x10];
    Vec_b087_01E03C90 p[4];
    Vec_b087_01E03C90 rot[1];
} Spr_b087_01E03C90;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b087_01E03C90;

static s32 func_01E01BE0_b385(s32 obj, Spr_b087_01E03C90 *spr, Cam_b087_01E03C90 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b087_01E03C90 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b087_01E03C90 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b385((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b087_01E03C90 *)(s32)&pkt)->count |= 0x800;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
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

/* shape b025:01E03CF0, 103 insns, 9 copies: set up a particle object: 6 corner offsets from a local table sized
   by the object's width/height, then each particle gets a random start (-rand() % 0x2000, rand() % 0x10000) */

typedef struct V4_b025_01E03CF0 {
    f32 x, y, z, w;
} V4_b025_01E03CF0;

typedef struct Part_b025_01E03CF0 {
    s32 a;
    s32 b;
    s32 c;
    u8 col;
    u8 padD;
    s16 age;
} Part_b025_01E03CF0;

typedef struct Obj_b025_01E03CF0 {
    s32 kind;
    u8 pad4[7];
    u8 col;
    u8 padC[0x14];
    V4_b025_01E03CF0 v[6];
    Part_b025_01E03CF0 *parts;
    f32 h;
    f32 w;
    u8 pad8C[0xE];
    s16 count;
} Obj_b025_01E03CF0;

typedef struct W_tbl_func_01E021F0_b385 {
    V4_b025_01E03CF0 v[6];
} W_tbl_func_01E021F0_b385;

static s32 func_01E021F0_b385(Obj_b025_01E03CF0 *o, s32 kind) {
    extern s32 func_0019A5C8();
    extern W_tbl_func_01E021F0_b385 D_01E03440_b385;
    W_tbl_func_01E021F0_b385 tbl_w = D_01E03440_b385;
    s32 i;

    tbl_w.v[0].x = -o->w / 2.0f;
    tbl_w.v[0].y = o->h;
    tbl_w.v[1].x = -o->w / 2.0f;
    tbl_w.v[2].y = o->h;
    tbl_w.v[4].x = o->w / 2.0f;
    tbl_w.v[4].y = o->h;
    tbl_w.v[5].x = o->w / 2.0f;
    o->kind = kind;
    for (i = 0; i < 6; i++) {
        o->v[i].x = tbl_w.v[i].x;
        o->v[i].y = tbl_w.v[i].y;
        o->v[i].z = tbl_w.v[i].z;
    }
    for (i = 0; i < o->count; i++) {
        o->parts[i].a = -func_0019A5C8() % 0x2000;
        o->parts[i].b = func_0019A5C8() % 0x10000;
        o->parts[i].c = 0;
        o->parts[i].age = 0;
        o->parts[i].col = o->col;
    }
    return 0;
}

/* shape b025:01E03E90 (LkSortShockWall), 450 insns, 9 copies: draws a textured shock wall: per segment a rotated,
   offset 6-point strip drawn as two quads, alpha fading out, the segment count growing each frame */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b025_01E03E90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b025_01E03E90 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b025_01E03E90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b025_01E03E90 v[4];
    u8 tail[0x20];
} Pkt_b025_01E03E90;

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 pad;
    s16 t;
} Seg_b025_01E03E90;

typedef struct {
    s32 x, y, z, w;
} Pos_b025_01E03E90;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 col;
    f32 r;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f q[6];
    Seg_b025_01E03E90 *seg;
    u8 pad84[8];
    f32 dy;
    f32 dx;
    s32 arc;
    s16 frame;
    s16 max;
    s16 n;
    s16 grow;
} Wall_b025_01E03E90;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b025_01E03E90;

/* n: a 4th parameter the caller never passes, reused as the segment count (its spill slot needs it) */

static s32 func_01E02390_b385(s32 ot, Wall_b025_01E03E90 *o, Cam_b025_01E03E90 *cam __attribute__((aligned(16))),
                              s32 n) {
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f sc;
    Pos_b025_01E03E90 pos;
    f32 m[16];
    Vec4f pts[6];
    f32 d[4];
    Pkt_b025_01E03E90 pkt;
    s32 step;
    s32 start;
    s32 k;
    s32 i;
    s16 tu;

    n = o->n;
    if (o->max < n) {
        n = o->n = o->max;
    }
    step = -(o->arc / o->max);
    start = -(0x8000 - o->arc) >> 1;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->pad = 0;
    func_00208CB0(&pkt, ((u64)o->v << 24) | (((u64)(o->w - 1) << 4) | 0xB | ((u64)o->u << 14)) |
                            ((u64)(o->v + o->h - 1) << 34));
    func_00208700(&pkt, o->texture, 0);
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b385((Vtx_b000_01E00100 *)&pkt, &o->col);
    for (k = 0; k < n; k++) {
        sc.z = o->r * func_0020B550(start + step * k);
        sc.x = o->r * func_0020B480(start + step * k);
        sc.y = 0.0f;
        pos.x = o->seg[k].x;
        pos.y = o->seg[k].y;
        pos.z = o->seg[k].z;
        func_0020C940(m, 0, &pos, &sc);
        func_0020BCF0((s32)m, (s32)cam->view);
        for (i = 0; i < 6; i++) {
            pts[i] = o->q[i];
            if (i != 2 && i != 3) {
                pts[i].x = o->q[i].x + o->dx * o->seg[k].t;
            }
            if (i % 2 == 0) {
                pts[i].y = o->q[i].y + o->dy * o->seg[k].t;
            }
        }
        for (i = 0; i < 2; i++) {
            if (i != 0) {
                pkt.v[0].a = o->seg[k].a;
                pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = 0;
            } else {
                pkt.v[0].a = pkt.v[1].a = pkt.v[3].a = 0;
                pkt.v[2].a = o->seg[k].a;
            }
            tu = o->seg[k].t % o->w + (o->w >> 1) * i;
            ((Pkt_b025_01E03E90 *)(s32)&pkt)->count |= 0x800;
            pkt.v[0].st.s = tu * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[0].st)->t = o->v * 16;
            pkt.v[1].st.s = tu * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[1].st)->t = (o->v + o->h - 1) * 16;
            pkt.v[2].st.s = (tu + (o->w >> 1)) * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[2].st)->t = o->v * 16;
            pkt.v[3].st.s = (tu + (o->w >> 1)) * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[3].st)->t = (o->v + o->h - 1) * 16;
            if (func_00205630(&pts[i * 2], 0x70000000, m, &pkt, d) != 0) {
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else if (func_00104520(o->flags, 0x12) != 0) {
                    func_002075F0(&pkt, ot, 0xFFFFFF);
                } else {
                    func_002075F0(&pkt, ot, func_001A23B0(d[0]));
                }
            }
        }
        if (func_00104520(o->flags, 0x1E) == 0) {
            o->seg[k].t++;
        }
    }
    o->frame++;
    o->n += o->grow;
    return 0;
}

/* shape b385:01E02AA0 (b385), 581 insns, 1 copy: b385 module main: code >= 0 sets up the laser trail, the shock wall,
   the dome grid, the ribbon sprite and the disc; else follows joints, draws the disc from 70, sprite in 70..117,
   laser from 101, wall/grid from 127 (fading from 220); 2 at tick 240, 1 at 117, 6 in 127..239, 8 when the timer ends
   */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Cam_b385_01E02AA0;

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b385_01E02AA0;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 t;
} Pt_b385_01E02AA0;

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
} Laser_b385_01E02AA0;

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 pad;
    s16 t;
} Seg_b385_01E02AA0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 r;
    s16 uv[4];
    u8 pad18[8];
    Vec4f q[6];
    Seg_b385_01E02AA0 *seg;
    f32 h;
    f32 w;
    f32 dy;
    f32 dx;
    s32 arc;
    s16 frame;
    s16 max;
    s16 n;
    s16 grow;
} Wall_b385_01E02AA0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 padC[4];
    s16 uv[4];
    u8 pad18[8];
    f32 p[16][32][3];
} Grid_b385_01E02AA0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 scale;
    s16 uv[4];
    u8 pad18[8];
    f32 w0, w1, h0, h1;
    Vec4f v[4];
    s32 r[64][4];
} Spr_b385_01E02AA0;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b385_01E02AA0;

typedef struct {
    Cam_b385_01E02AA0 cam0;
    Laser_b385_01E02AA0 laser;
    Pt_b385_01E02AA0 pts[32];
    Cam_b385_01E02AA0 cam1;
    Cam_b385_01E02AA0 cam2;
    Wall_b385_01E02AA0 wall;
    Seg_b385_01E02AA0 segs[256];
    Crd_b385_01E02AA0 cam3;
    Grid_b385_01E02AA0 grid;
    Cam_b385_01E02AA0 cam4;
    Spr_b385_01E02AA0 spr;
    Cam_b385_01E02AA0 cam5;
    Disc_b385_01E02AA0 disc;
    Vec4f mid;
    Vec4f tgt;
    u8 pad3230[0x10];
    s32 cnt;
    s32 ang;
    s32 timer;
    s32 t;
    s32 code;
    s32 j[4];
    u8 pad3264[0xC];
} Scene_b385_01E02AA0;

static s32 func_01E02AA0_b385(s32 arg0, s32 code) {
    Scene_b385_01E02AA0 *g = (Scene_b385_01E02AA0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103290(void *, s32);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_001033D0(void *, f32, f32);
    extern void func_00103390(void *, f32, f32);
    extern s32 func_0019A5C8();
    extern s32 func_01E02390_b385();
    Vec4f a;
    Vec4f v[2];
    s32 tex[4];
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3270);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam4);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        func_00103890(&g->cam5);
        g->j[0] = func_001F5560(func_001F53A0(), 0x4E, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x51, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x4D, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x53, 0);
        g->timer = 0x104;
        g->t = 1;
        g->code = code;
        g->cnt = 0x1A;
        g->ang = 0x8000;
        g->disc.flags = 0x10080000;
        g->disc.c[2] = 0xB0;
        g->disc.c[1] = 0x70;
        g->disc.c[0] = 0x40;
        g->disc.c[3] = 0;
        g->disc.radius = 5.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        func_00103290(tex, 0);
        g->laser.tex = tex[0];
        g->laser.flags = 0x8003;
        g->laser.c[2] = 0x80;
        g->laser.c[1] = 0x80;
        g->laser.c[0] = 0x80;
        g->laser.a = 0;
        g->laser.uv[0] = 0;
        g->laser.uv[1] = 0;
        g->laser.uv[2] = 0x10;
        g->laser.uv[3] = 0x20;
        g->laser.uv[4] = 0;
        g->laser.uv[5] = 0;
        g->laser.uv[6] = 0x80;
        g->laser.uv[7] = 0x40;
        g->laser.base = 100.0f;
        g->laser.h22 = 10;
        g->laser.tick = 0;
        g->laser.h26 = 0x24;
        g->laser.n1 = 0x20;
        g->laser.n2 = 0;
        g->laser.h2C = 1;
        g->spr.flags = 1;
        g->spr.uv[0] = 0x40;
        g->spr.uv[1] = 0;
        g->spr.uv[2] = 0x40;
        g->spr.uv[3] = 0x40;
        g->spr.c[2] = 0x80;
        g->spr.c[1] = 0x80;
        g->spr.c[0] = 0x80;
        g->spr.c[3] = 0x80;
        g->spr.w0 = 0.5f;
        g->spr.w1 = 1.0f;
        g->spr.h0 = 5.0f;
        g->spr.h1 = 0.0f;
        func_01E01A80_b385((Obj_b087_01E03B30 *)&g->spr, tex[0], 3.0f);
        func_00103290(tex, 1);
        g->wall.flags = 1;
        g->wall.uv[0] = 0;
        g->wall.uv[1] = 0;
        g->wall.uv[2] = 0x20;
        g->wall.uv[3] = 0x40;
        g->wall.c[2] = 0xB0;
        g->wall.c[1] = 0x70;
        g->wall.c[0] = 0x40;
        g->wall.c[3] = 0x80;
        g->wall.seg = g->segs;
        g->wall.h = 5.0f;
        g->wall.w = 30.0f;
        g->wall.dy = 0.8f;
        g->wall.dx = 0.0f;
        g->wall.arc = 0x10000;
        g->wall.r = 0.0f;
        g->wall.frame = 0;
        g->wall.max = 0x100;
        g->wall.n = 0x3E7;
        g->wall.grow = 3;
        func_01E021F0_b385((Obj_b025_01E03CF0 *)&g->wall, tex[0]);
        func_00103290(tex, 2);
        g->grid.flags = 3;
        g->grid.uv[0] = 0;
        g->grid.uv[1] = 0;
        g->grid.uv[2] = 0x80;
        g->grid.uv[3] = 0x80;
        g->grid.c[2] = 0xB0;
        g->grid.c[1] = 0x70;
        g->grid.c[0] = 0x40;
        g->grid.c[3] = 0x80;
        func_01E00250_b385((Dome_b364_01E02A90 *)&g->grid, tex[0], 30.0f);
        g->cam3.x = g->cam3.y = g->cam3.z = 0.0f;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->j[2], &v[0]);
    func_001F5620(func_001F53A0(), g->j[3], &v[1]);
    func_001036E0(&v[0], &v[1], &g->mid);
    if (g->t < 0x77) {
        v[0] = g->mid;
        func_001F5620(func_001F53A0(), g->j[1], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->cam4.rot);
        func_001F5620(func_001F53A0(), g->j[1], &g->cam4.pos);
    }
    func_001F5620(func_001F53A0(), g->j[1], &g->cam5.pos);
    if (g->t == 100) {
        func_001F53C0(1, func_001F5380(), &g->tgt);
        g->tgt.y = 15.0f;
    }
    if (g->t < 0x65) {
        func_001F5620(func_001F53A0(), g->j[1], &g->cam1.pos);
    }
    if (g->t >= 100) {
        a = g->cam1.pos;
        a.y += 20.0f * func_0020B550(g->ang);
        func_01E00F70_b385((Obj_b000_01E03A30 *)&g->laser, (Pt_b000_01E03A30 *)g->pts, (f32 *)&a);
        func_00104490(&g->cam1.pos, &g->tgt, g->cnt);
        if (g->cnt != 0) {
            g->cnt--;
            g->ang += 0x4EC;
        }
    }
    if (g->t == 0x7F) {
        func_001F53C0(1, func_001F5380(), &g->cam2.pos);
        g->cam2.pos.y = 10.0f;
        g->cam3.pos = g->cam2.pos;
        g->cam3.pos.y = 10.0f;
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001038D0(&g->cam4);
    func_001038D0(&g->cam2);
    func_001038D0(&g->cam3);
    func_001039A0(&g->cam5);
    if (g->t >= 0x46) {
        func_01E00120_b385();
    }
    if (g->t >= 0x7F) {
        if (g->t == 0xB7) {
            g->wall.flags |= 0x40000000;
        }
        func_01E02390_b385(ot, &g->wall, &g->cam2);
        { f32 r = 35.0f; func_00103390(&g->wall.r, r, 1.0f); }
        if (g->t >= 0xDC) {
            if (g->t == 0xDC) {
                g->wall.flags &= 0xBFFFFFFF;
                g->wall.dy = 6.0f;
                for (i = 0; i < g->wall.max; i++) {
                    g->segs[i].t = 7;
                }
            }
            for (i = 0; i < g->wall.max; i++) {
                if (g->wall.seg[i].t > 10) {
                    func_00103470(&g->wall.seg[i].a, 0, 8);
                }
            }
            func_00103470(&g->grid.c[3], 0, 8);
        }
        func_01E00340_b385(ot, (Grid_b364_01E02B80 *)&g->grid, (Cam_b364_01E02B80 *)&g->cam3);
        func_001033D0(&g->cam3, 1.6f, 0.03f);
        { f32 r = 40.0f; func_00103390(&g->cam3.pos.y, r, 1.0f); }
        g->cam3.rot[0] += 0x100;
        g->cam3.rot[1] += 0x100;
        g->cam3.rot[2] += 0x100;
    }
    g->disc.c[2] = func_0019A5C8() % 64 + 0x70;
    g->disc.c[1] = func_0019A5C8() % 64 + 0x30;
    g->disc.c[0] = func_0019A5C8() % 64;
    if (g->t >= 0x46) {
        func_01E00A10_b385(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->cam5);
        if (g->t >= 0x76) {
            g->disc.flags &= 0xEFFFFFFF;
            g->disc.radius = 15.0f;
            func_00103470(&g->disc.c[3], 0, 8);
        } else {
            func_001032C0(&g->disc.c[3], 0xFF, 0x10);
        }
    }
    if (g->t >= 0x46 && g->t < 0x76) {
        g->spr.c[3] = func_0019A5C8() % 8 + 8;
        func_01E01BE0_b385(ot, (Spr_b087_01E03C90 *)&g->spr, (Cam_b087_01E03C90 *)&g->cam4);
    }
    if (g->t > 100) {
        if (g->t == 0x76) {
            g->laser.a = 0x80;
            for (i = 0; i < g->laser.n2; i++) {
                g->pts[i].a = 0x80;
            }
        }
        func_01E010C0_b385(ot, (Laser_b117_01E00270 *)&g->laser, (Pt_b117_01E00270 *)g->pts,
                           (Cam_b117_01E00270 *)&g->cam0);
    }
    g->t++;
    g->timer--;
    if (g->t == 0xF0) {
        return 2;
    }
    if (g->t == 0x75) {
        return 1;
    }
    if (g->t >= 0x7F && g->t < 0xF0) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
