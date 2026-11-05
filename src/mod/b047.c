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

static void func_01E00080_b047(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b047(void) {
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

static s32 func_01E00250_b047(Obj_b015_01E01620 *obj, s32 life, f32 y) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b047", func_01E00410_b047);

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

static s32 func_01E01170_b047(Obj_b047_01E01170 *o, s32 owner) {
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

static s32 func_01E01270_b047(s32 ot __attribute__((aligned(8))), Beam_b047_01E01270 *o, Cam_b047_01E01270 *cam) {
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
    func_01E00080_b047((Vtx_b000_01E00100 *)&pkt, &o->col);
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

/* shape b047:01E01990 (b047), 429 insns, 1 copy: b047 scene manager: code >= 0 sets up three beams between joint
   pairs and a 256-particle emitter; else aims the beams, fades in, draws them (random blue from tick 58, faded past
   170) and the emitter (shown from 82, particles grown x1.3 and respawned), returns 2/1/6/8 by tick */

typedef struct {
    u8 pad0[0x10];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b047_01E01990;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 pad[4];
} Item_b047_01E01990;

typedef struct {
    s32 tex;
    u8 c[4];
    s32 flags;
    f32 scale;
    s16 uv[8];
    f32 pts[0x24][2];
    s16 n;
    s16 h142;
    f32 width;
    Item_b047_01E01990 *items;
    s16 count;
    s16 tick;
    f32 speed;
    u8 pad154[0xC];
} Beam_b047_01E01990;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b047_01E01990;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    Part_b047_01E01990 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 b2E;
    u8 b2F;
} Emit_b047_01E01990;

typedef struct {
    Crd_b047_01E01990 crd;
    Crd_b047_01E01990 m[3];
    Beam_b047_01E01990 beam[3];
    Item_b047_01E01990 items[3][64];
    Crd_b047_01E01990 cam;
    Emit_b047_01E01990 emit;
    Part_b047_01E01990 parts[256];
    s32 timer;
    s32 t;
    s32 code;
    s32 j[6];
    s32 fade;
    u8 pad22A8[8];
} Scene_b047_01E01990;

static s32 func_01E01990_b047(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_001043F0(void *, f32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_001F6D00(s32);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern s32 func_0019A5C8();
    extern void b047_01E00410();
    extern void b047_01E01270();
    Scene_b047_01E01990 *g = (Scene_b047_01E01990 *)arg0;
    s32 ot;
    Vec4f v[2];
    Vec4f p;
    s32 tex[2];
    u8 col[8];
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x22B0);
        func_00103890(&g->crd);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->m[i]);
        }
        func_00103890(&g->cam);
        g->j[0] = func_001F5560(func_001F53A0(), 8, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 9, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0xA, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 3, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 4, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 5, 0);
        g->timer = 0xBE;
        g->t = 1;
        g->code = code;
        g->fade = 0x80;
        func_00103290(tex, 0);
        g->beam[0].items = g->items[0];
        g->beam[1].items = g->items[1];
        g->beam[2].items = g->items[2];
        for (i = 0; i < 3; i++) {
            g->beam[i].tex = tex[0];
            g->beam[i].c[2] = 0x80;
            g->beam[i].c[1] = 0x80;
            g->beam[i].c[0] = 0x80;
            g->beam[i].c[3] = 0x80;
            g->beam[i].flags = 0x8000;
            g->beam[i].scale = 1.0f;
            g->beam[i].n = 0x20;
            g->beam[i].h142 = 0;
            g->beam[i].width = 5.0f;
            g->beam[i].uv[0] = 0;
            g->beam[i].uv[1] = 0;
            g->beam[i].uv[2] = 0x80;
            g->beam[i].uv[3] = 0x80;
            g->beam[i].uv[4] = 0;
            g->beam[i].uv[5] = 0;
            g->beam[i].uv[6] = 0x80;
            g->beam[i].uv[7] = 0x80;
            g->beam[i].count = 0x14;
            g->beam[i].tick = 0;
            g->beam[i].speed = 0.1f;
            func_01E01170_b047((Obj_b047_01E01170 *)&g->beam[i], tex[0]);
        }
        func_00103260(tex, 0xF);
        g->emit.tex = tex[0];
        g->emit.flags = 3;
        g->emit.c[2] = 0x80;
        g->emit.c[1] = 0x70;
        g->emit.c[0] = 0x40;
        g->emit.c[3] = 0;
        g->emit.f20 = 0.3f;
        g->emit.f24 = 11.0f;
        g->emit.uv[0] = 0xB0;
        g->emit.uv[1] = 0x60;
        g->emit.uv[2] = 0x20;
        g->emit.uv[3] = 0x20;
        g->emit.uv[4] = 0xB0;
        g->emit.uv[5] = 0x60;
        g->emit.uv[6] = 0x100;
        g->emit.uv[7] = 0x100;
        g->emit.parts = g->parts;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.b2E = 1;
        g->emit.b2F = 0;
        func_01E00250_b047((Obj_b015_01E01620 *)&g->emit, 0xC, 3.0f);
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001F5620(func_001F53A0(), g->j[i], &v[0]);
        func_001F5620(func_001F53A0(), g->j[i + 3], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->m[i].rot);
        func_001F5620(func_001F53A0(), g->j[i], &g->m[i].pos);
        if (g->t >= 100) {
            g->m[i].pos.z = 0.0f;
            g->m[i].pos.y -= 25.0f;
            g->beam[i].speed = 0.5f;
        }
    }
    func_001F53C0(1, func_001F5380(), &g->cam.pos);
    func_001038D0(&g->crd);
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->m[i]);
    }
    func_001038D0(&g->cam);
    if (g->t < 0xAA) {
        func_00103470((u8 *)&g->fade, 0x20, 4);
    } else {
        func_001032C0((u8 *)&g->fade, 0x80, 4);
    }
    func_001F6D00((u8)g->fade);
    if (g->t >= 0x3A) {
        func_01E00120_b047();
    }
    if (g->t < 100) {
        i = func_001F53A0();
        col[4] = 0x80;
        col[5] = 0x80;
        col[6] = 0x80;
        col[3] = 0x80;
        col[0] = 0x80;
        col[1] = 0x80;
        col[2] = 0x80;
        col[7] = 0;
        func_001F71A0(i, 3, 0, col, &col[4], 0);
    }
    if (g->t >= 0x3A) {
        for (i = 0; i < 3; i++) {
            g->beam[i].c[0] = func_0019A5C8() % 64 + 64;
            b047_01E01270(ot, &g->beam[i], &g->m[i]);
            if (g->t > 0xAA) {
                func_00103470(&g->beam[i].c[3], 0, 8);
            }
            g->beam[i].tick++;
        }
    }
    if (g->t == 0x52) {
        g->emit.c[3] = 0x80;
    }
    b047_01E00410(ot, &g->emit, &g->cam);
    if (g->t > 0xAA) {
        func_00103470(&g->emit.c[3], 0, 8);
    }
    for (i = 0; i < g->emit.count; i++) {
        if (g->parts[i].t >= 0) {
            g->parts[i].x *= 1.3f;
            g->parts[i].y *= 1.3f;
            g->parts[i].z *= 1.3f;
            if (g->parts[i].t > 0x10) {
                func_001043F0(&p, 1.0f);
                g->parts[i].y = p.y;
                g->parts[i].z = p.z;
                g->parts[i].x = p.x;
                g->parts[i].t = -(func_0019A5C8() % 12);
                if (g->t >= 0x52) {
                    g->parts[i].c = 0x80;
                } else {
                    g->parts[i].c = 0;
                }
            }
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0xAA) {
        return 2;
    }
    if (g->t == 0x48) {
        return 1;
    }
    if (g->t >= 0x52 && g->t < 0xAA) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
