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

static void func_01E00080_b600(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b600(void) {
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E00250_b600(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

/* shape b489:01E00240 (LkPrim_SortLineParticle), 853 insns, 55 copies: each live particle drawn as a camera-facing
   line quad from its position back along its direction (or straight down), texture-animated */

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b489_01E00240;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b489_01E00240;

typedef struct {
    UV_b489_01E00240 uv;
    Xyz_b489_01E00240 xyz;
} Vtx_b489_01E00240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b489_01E00240 v[4];
    u8 tail[0x20];
} Pkt_b489_01E00240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 age;
} Part_b489_01E00240;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Part_b489_01E00240 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    u8 pad28[4];
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00240;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b489_01E00240;

#define UV_b489_01E00240(k) ((UV_b489_01E00240 *)(s32)&pkt.v[k].uv)

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E00410_b600(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_0020D070(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C60(f32);
    extern void func_00208CB0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f t;
    Xyz_b489_01E00240 q[2];
    Pkt_b489_01E00240 pkt __attribute__((aligned(8)));
    f32 dep[2];
    s32 i;
    f32 w;
    f32 dx;
    f32 dy;

    ((Pkt_b489_01E00240 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->tag = 9;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->r;
    pkt.g = e->g;
    pkt.b = e->b;
    pkt.a = e->a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
        UV_b489_01E00240(0)->u = e->u << 4;
        UV_b489_01E00240(0)->v = e->v << 4;
        UV_b489_01E00240(1)->u = e->u << 4;
        UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
        UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(2)->v = e->v << 4;
        UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
    }
    for (i = 0; i < e->count; i++) {
        if (e->parts[i].age >= 0) {
            if (e->parts[i].a < e->a) {
                pkt.a = e->parts[i].a;
            } else {
                pkt.a = e->a;
            }
            if (func_00104520(e->flags, 3) == 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->u = e->u0 + e->w * (e->parts[i].frame % (e->tw / e->w));
                    e->v = e->v0 + e->h * (e->parts[i].frame / (e->tw / e->w));
                } else {
                    e->u = e->u0 + e->w * (e->parts[i].frame / (e->th / e->h));
                    e->v = e->v0 + e->h * (e->parts[i].frame % (e->th / e->h));
                }
                ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
                UV_b489_01E00240(0)->u = e->u << 4;
                UV_b489_01E00240(0)->v = e->v << 4;
                UV_b489_01E00240(1)->u = e->u << 4;
                UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
                UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(2)->v = e->v << 4;
                UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
            }
            if (func_00104520(e->flags, 0x1E) != 0) {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y - e->len;
                t.z = e->parts[i].z;
            } else {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y;
                t.z = e->parts[i].z;
                func_0020D070(&t);
                t.x *= -e->len;
                t.y *= -e->len;
                t.z *= -e->len;
                t.x += e->parts[i].x;
                t.y += e->parts[i].y;
                t.z += e->parts[i].z;
            }
            if (func_00205440(&e->parts[i], cam->view, &q[0], &dep[0]) != 0 && func_00101600(&q[0]) != 0) {
                e->flags |= 0x100000;
            }
            if (func_00205440(&t, cam->view, &q[1], &dep[1]) != 0 && func_00101600(&q[1]) != 0) {
                e->flags |= 0x200000;
            }
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0) {
                dx = func_001A6970(q[0].x - q[1].x);
                dy = func_001A6970(q[0].y - q[1].y);
                w = func_001A6C60(dx * dx + dy * dy);
                w = w * e->width / e->len;
                if (dx > dy) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = q[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = q[1].x;
                    pkt.v[0].xyz.y = (u32)(q[0].y - w);
                    pkt.v[1].xyz.y = (u32)(q[1].y - w);
                    pkt.v[2].xyz.y = (u32)(q[0].y + w);
                    pkt.v[3].xyz.y = (u32)(q[1].y + w);
                } else {
                    pkt.v[0].xyz.x = (u32)(q[0].x - w);
                    pkt.v[1].xyz.x = (u32)(q[1].x - w);
                    pkt.v[2].xyz.x = (u32)(q[0].x + w);
                    pkt.v[3].xyz.x = (u32)(q[1].x + w);
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = q[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = q[1].y;
                }
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = q[0].z;
                if (func_00104520(e->flags, 0) != 0) {
                    func_00208CB0(&pkt, 0xA | ((s64)e->u << 4) | ((s64)(e->u + e->w - 1) << 14) |
                                            ((s64)e->v << 24) | ((s64)(e->v + e->h - 1) << 34));
                }
                func_00208700(&pkt, e->texture, 1);
                if (func_00104520(e->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1]) / 2.0f));
                }
            }
            e->flags &= 0xFFCFFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->parts[i].age++;
            if (e->parts[i].age % e->rate == 0) {
                e->parts[i].frame++;
                if (e->nframes == e->parts[i].frame) {
                    e->parts[i].frame = 0;
                }
            }
        }
    }
    return 0;
}

/* shape b047:01E01170, 61 insns, 6 copies: sets up a ring: n points (at most 0x24) on the unit circle, then gives
   every item the object's alpha. */

typedef struct {
    f32 x, y;
} Pt_b047_01E01170;

typedef struct {
    u8 pad0[0xC];
    u8 a;
    u8 padD[3];
} Item_b047_01E01170;

typedef struct {
    s32 owner;
    u8 pad4[3];
    u8 a;
    u8 pad8[0x18];
    Pt_b047_01E01170 pts[0x24];
    s16 n;
    u8 pad142[6];
    Item_b047_01E01170 *items;
    s16 count;
} Obj_b047_01E01170;

static s32 func_01E01170_b600(Obj_b047_01E01170 *o, s32 owner) {
    s32 i;
    s32 ang;
    s32 step;

    o->owner = owner;
    if (o->n > 0x24) {
        o->n = 0x24;
    }
    step = 0x10000 - 0x10000 / o->n;
    for (i = 0, ang = 0; i < o->n; i++) {
        o->pts[i].x = func_0020B480(ang);
        o->pts[i].y = func_0020B550(ang);
        ang += step;
    }
    for (i = 0; i < o->count; i++) {
        o->items[i].a = o->a;
    }
    return 0;
}

/* shape b047:01E01270 (LkEff_SortBeam), 454 insns, 6 copies: draws a scrolling textured beam: rows x n quads from the
   ring points of b047:01E01170, row widths growing by speed (flag 0xF), alpha from the items capped by the colour,
   ends faded; drawn when all four corners project */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b047_01E01270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b047_01E01270 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b047_01E01270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b047_01E01270 v[4];
    u8 tail[0x20];
} Pkt_b047_01E01270;

typedef struct {
    u8 pad0[0xC];
    u8 a;
    u8 padD[3];
} Item_b047_01E01270;

typedef struct {
    f32 x, y;
} Pt_b047_01E01270;

typedef struct {
    void *texture;
    Src_b000_01E00100 col;
    s32 flags;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_b047_01E01270 pts[0x24];
    s16 n;
    s16 phase;
    f32 width;
    Item_b047_01E01270 *items;
    s16 count;
    s16 rows;
    f32 speed;
} Beam_b047_01E01270;

typedef struct {
    u8 pad0[0x30];
    f32 m[16];
} Cam_b047_01E01270;

static s32 func_01E01270_b600(s32 ot __attribute__((aligned(8))), Beam_b047_01E01270 *o, Cam_b047_01E01270 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f p[4];
    f32 d[4];
    Pkt_b047_01E01270 pkt;
    s32 i;
    s32 j;
    s32 k;
    s32 base;
    s32 vs;
    s32 us;
    f32 r0;
    f32 r1;
    s32 t0;
    s32 t1;
    s32 u0;
    s32 u1;

    ((Pkt_b047_01E01270 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b047_01E01270 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b047_01E01270 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b047_01E01270 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b600((Vtx_b000_01E00100 *)&pkt, &o->col);
    ((Pkt_b047_01E01270 *)(s32)&pkt)->count |= 0x800;
    func_00208CB0(&pkt, ((u64)o->u << 4) | 0xE | ((u64)(o->u + o->w - 1) << 14) |
                            ((u64)(o->v + o->h - 1) << 24) | ((u64)o->v << 34));
    func_00208700(&pkt, o->texture, 1);
    if (o->rows > o->count - 1) {
        o->rows = o->count - 1;
    }
    for (i = 0; i < o->rows; i++) {
        base = o->h - o->phase % o->h;
        vs = o->h / o->count;
        t0 = (s16)(base + i * vs);
        t1 = (s16)(base + (i + 1) * vs);
        t0 *= 16;
        t1 *= 16;
        for (j = 0; j < o->n; j++) {
            us = o->w / o->n;
            u0 = (s16)(j * us);
            u1 = (s16)((j + 1) * us);
            u0 *= 16;
            pkt.v[0].st.s = u0;
            ((Uv_b047_01E01270 *)(s32)&pkt.v[0].st)->t = t0;
            pkt.v[1].st.s = u0;
            ((Uv_b047_01E01270 *)(s32)&pkt.v[1].st)->t = t1;
            u1 *= 16;
            pkt.v[2].st.s = u1;
            ((Uv_b047_01E01270 *)(s32)&pkt.v[2].st)->t = t0;
            pkt.v[3].st.s = u1;
            ((Uv_b047_01E01270 *)(s32)&pkt.v[3].st)->t = t1;
            if (o->items[i].a < o->col.a) {
                pkt.v[0].a = pkt.v[2].a = o->items[i].a;
            } else {
                pkt.v[0].a = pkt.v[2].a = o->col.a;
            }
            if (o->items[i + 1].a < o->col.a) {
                pkt.v[1].a = pkt.v[3].a = o->items[i + 1].a;
            } else {
                pkt.v[1].a = pkt.v[3].a = o->col.a;
            }
            if (i == 0) {
                pkt.v[0].a = pkt.v[2].a = 0;
            }
            if (i == o->rows - 1) {
                pkt.v[1].a = pkt.v[3].a = 0;
            }
            k = j + 1;
            if (k >= o->n) {
                k = 0;
            }
            if (func_00104520(o->flags, 0xF) != 0) {
                r0 = o->scale + o->speed * i;
                r1 = o->scale + o->speed * (i + 1);
            } else {
                r0 = r1 = o->scale;
            }
            p[0].z = o->pts[j].x * r0;
            p[0].x = o->pts[j].y * r0;
            p[0].y = o->width * i;
            if (func_00205440(&p[0], cam->m, &pkt.v[0].st + 1, &d[0]) != 0) {
                o->flags |= 0x100000;
            }
            p[1].z = o->pts[j].x * r1;
            p[1].x = o->pts[j].y * r1;
            p[1].y = o->width * (i + 1);
            if (func_00205440(&p[1], cam->m, &pkt.v[1].st + 1, &d[1]) != 0) {
                o->flags |= 0x200000;
            }
            p[2].z = o->pts[k].x * r0;
            p[2].x = o->pts[k].y * r0;
            p[2].y = o->width * i;
            if (func_00205440(&p[2], cam->m, &pkt.v[2].st + 1, &d[2]) != 0) {
                o->flags |= 0x400000;
            }
            p[3].z = o->pts[k].x * r1;
            p[3].x = o->pts[k].y * r1;
            p[3].y = o->width * (i + 1);
            if (func_00205440(&p[3], cam->m, &pkt.v[3].st + 1, &d[3]) != 0) {
                o->flags |= 0x800000;
            }
            if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
            o->flags &= 0xFF0FFFFF;
        }
    }
    o->phase++;
    return 0;
}

/* shape b600:01E01990 (b600), 343 insns, 1 copy: b600's scene manager: with a code it clears the scene and its two
   models, two joints, a 421-tick countdown, grey 0x80, a pink beam (texture from 0x103290, rect 0x80 x 0x80, 20
   segments) and a 256-point spark cloud (texture 15, rect 0x20 at (0xB0, 0x60)); otherwise it aims the second model
   between the camera and joint 1 until tick 390, fades the scene grey out until 400 then back, tints the screen until
   96, from 173 draws the flickering beam (fading after 400), from 197 lights the cloud, grows each live point by 1.3
   and re-rolls it past life 16; returns 2 at 400, 1 at 187, 6 from 197 to 399, 8 when the countdown runs out; the
   tint colours one u8 c[8] passed as c, &c[4], the screen handle fetched before them, tex aligned(8) */

typedef struct Pt_b600_01E01990 {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 life;
} Pt_b600_01E01990;

typedef struct Game_b600_01E01990 {
    u8 m0[0x70];
    s32 tex;
    u8 b, g, r, a;
    s32 w78;
    f32 f7C;
    s16 rect[8];
    u8 pad90[0x120];
    s16 h1B0;
    s16 h1B2;
    f32 f1B4;
    void *p1B8;
    s16 h1BC;
    s16 seg;
    f32 f1C0;
    u8 pad1C4[0x40C];
    u8 m5D0[0x10];
    Vec4f v5E0;
    Vec4f v5F0;
    u8 pad600[0x40];
    u8 m640[0x20];
    u8 m660[0x50];
    s32 tex2;
    s32 w6B4;
    u8 b2, g2, r2, a2;
    void *p6BC;
    s16 rect2[8];
    f32 f6D0;
    f32 f6D4;
    f32 f6D8;
    s16 count2;
    u8 b6DE;
    u8 b6DF;
    Pt_b600_01E01990 pts[256];
    s32 count;
    s32 clock;
    s32 code;
    s32 j0;
    s32 j1;
    s32 grey;
} Game_b600_01E01990;

static s32 func_01E01990_b600(s32 arg0, s32 code) {
    Game_b600_01E01990 *g = (Game_b600_01E01990 *)arg0;
    extern s32 func_001F53A0();
    extern s32 func_001F5380();
    extern void func_00103290();
    extern void func_00103260();
    extern void func_001F5F90();
    extern void func_001F5620();
    extern void func_00103DB0();
    extern s32 func_00103470();
    extern s32 func_001032C0();
    extern void func_001F6D00(u8);
    extern void func_001F71A0();
    extern void func_001043F0(void *, f32);
    extern void b600_01E00410();
    extern void b600_01E01270();
    s32 tex __attribute__((aligned(8)));
    u8 c[8];
    f32 m[4];
    f32 b[4];
    Vec4f v;
    f32 *pb;
    s32 ot;
    s32 i;

    ot = (s32)func_00207500();
    if (code >= 0) {
        func_00195108((s32)g, 0x1700);
        func_00103890(g);
        func_00103890(g->m5D0);
        func_00103890(g->m640);
        g->j0 = func_001F5560(func_001F53A0(), 3, 1);
        g->j1 = func_001F5560(func_001F53A0(), 1, 0);
        g->count = 421;
        g->clock = 1;
        g->code = code;
        g->grey = 0x80;
        func_00103290(&tex, 0);
        g->tex = tex;
        g->r = 0x80;
        g->g = 0x40;
        g->b = 0x60;
        g->a = 0x80;
        g->w78 = 0;
        g->f7C = 2.5f;
        g->h1B0 = 0x20;
        g->h1B2 = 0;
        g->f1B4 = 2.0f;
        g->rect[0] = 0;
        g->rect[1] = 0;
        g->rect[2] = 0x80;
        g->rect[3] = 0x80;
        g->rect[4] = 0;
        g->rect[5] = 0;
        g->rect[6] = 0x80;
        g->rect[7] = 0x80;
        g->p1B8 = g->pad1C4 + 0xC;
        g->h1BC = 20;
        g->seg = 0;
        g->f1C0 = 1.0f;
        func_01E01170_b600((void *)&g->tex, tex);
        func_00103260(&tex, 0xF);
        g->tex2 = tex;
        g->w6B4 = 3;
        g->r2 = 0x80;
        g->g2 = 0x40;
        g->b2 = 0x60;
        g->a2 = 0;
        g->f6D0 = 0.3f;
        g->f6D4 = 11.0f;
        g->rect2[0] = 0xB0;
        g->rect2[1] = 0x60;
        g->rect2[2] = 0x20;
        g->rect2[3] = 0x20;
        g->rect2[4] = 0xB0;
        g->rect2[5] = 0x60;
        g->rect2[6] = 0x100;
        g->rect2[7] = 0x100;
        g->p6BC = g->pts;
        g->f6D8 = 10.0f;
        g->count2 = 0x100;
        g->b6DE = 1;
        g->b6DF = 0;
        func_01E00250_b600((void *)&g->tex2, 12, 3.0f);
        return 0;
    }
    if (g->clock < 390) {
        func_001F5F90(func_001F5380(), m);
        func_001F5620(func_001F53A0(), g->j1, pb = (f32 *)(u32)b);
        func_00103DB0(m, pb, &g->v5E0);
        func_001F5620(func_001F53A0(), g->j0, &g->v5F0);
    }
    func_001F5F90(func_001F5380(), g->m660);
    func_001038D0(g);
    func_001038D0(g->m5D0);
    func_001038D0(g->m640);
    if (g->clock < 400) {
        func_00103470(&g->grey, 0x20, 4);
    } else {
        func_001032C0(&g->grey, 0x80, 4);
    }
    func_001F6D00(g->grey);
    if (g->clock >= 173) {
        func_01E00120_b600();
    }
    if (g->clock < 96) {
        s32 e = func_001F53A0();
        c[4] = 0x80;
        c[5] = 0x80;
        c[6] = 0x80;
        c[3] = 0x80;
        c[0] = 0x80;
        c[1] = 0x80;
        c[2] = 0x80;
        c[7] = 0;
        func_001F71A0(e, 3, 0, c, &c[4], 0);
    }
    if (g->clock >= 173) {
        g->b = func_0019A5C8() % 64 + 64;
        b600_01E01270(ot, &g->tex, g->m5D0);
        if (g->clock > 400) {
            func_00103470(&g->a, 0, 0x10);
        }
        g->seg++;
    }
    if (g->clock == 197) {
        g->a2 = 0x80;
    }
    b600_01E00410(ot, &g->tex2, g->m640);
    if (g->clock > 392) {
        func_00103470(&g->a2, 0, 8);
    }
    for (i = 0; i < g->count2; i++) {
        if (g->pts[i].life < 0) {
            continue;
        }
        g->pts[i].x *= 1.3f;
        g->pts[i].y *= 1.3f;
        g->pts[i].z *= 1.3f;
        if (g->pts[i].life > 16) {
            func_001043F0(&v, 1.0f);
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].x = v.x;
            g->pts[i].life = -(func_0019A5C8() % 12);
            if (g->clock >= 197) {
                g->pts[i].a = 0x80;
            } else {
                g->pts[i].a = 0;
            }
        }
    }
    g->clock++;
    g->count--;
    if (g->clock == 400) {
        return 2;
    }
    if (g->clock == 187) {
        return 1;
    }
    if (g->clock >= 197 && g->clock < 400) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
