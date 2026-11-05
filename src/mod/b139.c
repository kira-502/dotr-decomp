#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b139(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;

typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;

typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00110_b139(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

/* shape b082:01E00920, 280 insns, 18 copies: draws a full ring of 36 segments (10 table steps each) between an
   inner and an outer radius around a position (passed by value); blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b082_01E00920;

typedef struct {
    u8 pad00[6];
    s16 outer;
    u8 pad08[0x18];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    u8 pad4C[0x0E];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b082_01E00920;

static void func_01E009B0_b139(Obj_b082_01E00920 *o, Data_b082_01E00920 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    i = 0;
    outer = data->outer;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b020_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b020_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E00920;

typedef struct {
    u64 st;
    Xyz_b020_01E00920 p;
} Vtx_b020_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b020_01E00920 c;
    Vtx_b020_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b020_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b020_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b020_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    u8 pad5C[4];
    u8 col[1];
} Anim_b020_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b020_01E00920;

extern void b139_01E00110(Pkt_b020_01E00920 *, void *, s32);

static void func_01E00E10_b139(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b020_01E00920 quad[4];
    Vec_b020_01E00920 d;
    Vec_b020_01E00920 pos;
    Vec_b020_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b020_01E00920 r;
    struct {
        u64 pre;
        Pkt_b020_01E00920 pk;
    } buf;
    Col_b020_01E00920 col;
    s16 i;
    Pkt_b020_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.v[2] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b139_01E00110(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 2, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b139:01E01360, 174 insns: the b139 module's event step: counts ticks; spawns b139:01E02070 at 97, 255 and 315 (slots 0, 1, 2); from 230 to 300 spawns b139:01E01780 at the camera-side point (ctx+0xC0FA); each tick marks the tracked point (ctx+0xC0EC) and reads the camera; from 97 to 300, every other tick, spawns 3 (5 from 200) pairs of b139:01E01910 / b139:01E01620 in the next of 120 slots */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0xBC70 - 0x25C];
    Vec4f mark;
    u8 padBC80[0xC0EC - 0xBC80];
    s16 id0;
    u8 padC0EE[0xC0FA - 0xC0EE];
    s16 id1;
    u8 padC0FC[0xC20A - 0xC0FC];
    s16 slot;
    s16 next;
    u8 padC20E[4];
    s16 timer;
} Ctx_b139_01E01360;

static void func_01E01360_b139(Ctx_b139_01E01360 *g) {
    extern s32 b139_01E01620(void);
    extern s32 b139_01E01780(void);
    extern s32 b139_01E01910(void);
    extern s32 b139_01E02070(void);
    extern void b139_01E02A60(Ctx_b139_01E01360 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[4];
    s16 i;
    s16 n;

    g->timer++;
    if (g->timer == 97) {
        g->slot = 0;
        b139_01E02A60(g, b139_01E02070, 0);
    }
    if (g->timer == 255) {
        g->slot = 1;
        b139_01E02A60(g, b139_01E02070, 0);
    }
    if (g->timer == 315) {
        g->slot = 2;
        b139_01E02A60(g, b139_01E02070, 0);
    }
    if (g->timer >= 230 && g->timer < 301) {
        g->slot = 0;
        func_001F5620(func_001F5380(), g->id1, v);
        g->pos[0] = v[0];
        g->pos[1] = v[1];
        g->pos[2] = v[2];
        b139_01E02A60(g, b139_01E01780, 0);
    }
    func_001F5620(func_001F53A0(), g->id0, &g->mark);
    func_001F5F90(func_001F53A0(), g->pos);
    if (g->timer >= 97 && g->timer < 301) {
        if (g->timer % 2 == 1) {
            n = g->timer < 200 ? 3 : 5;
            for (i = 0; i < n; i++) {
                g->slot = g->next;
                b139_01E02A60(g, b139_01E01910, 0);
                b139_01E02A60(g, b139_01E01620, 0);
                g->next++;
                if (g->next >= 120) {
                    g->next = 0;
                }
            }
        }
    }
}

/* shape b139:01E01620, 86 insns: a grey flickering spark (b215:01E01FF0 shape): size 10; both alphas up by 42 to 0x80 for 27
   frames, then the first down by 34 twice a frame until it ends; first colour flickers by frame parity; random turn */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b139_01E01620;

static s32 func_01E01620_b139(void *arg0, Obj_b139_01E01620 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0xA;
        o->h = 0xA;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x1B) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else {
        if (o->c0[3] > 0x23) {
            o->c0[3] -= 0x22;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 0x23) {
            o->c0[3] -= 0x22;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b139:01E01780, 98 insns: a dark spark: size 30 growing by 8 once started, random sub-frame 0..6, frame 0..7, start height
   100..199 (old one kept), rise 16..45, width 0..34, hold 3..7; full alpha until the hold, then down by 8 until it ends */

typedef struct {
    u8 pad0[2];
    s16 age;
    u8 pad4[2];
    s16 hold;
    s16 w;
    s16 frame;
    s16 y0;
    s16 step;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b139_01E01780;

static s32 func_01E01780_b139(void *arg0, Obj_b139_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 30.0f;
        o->sub = func_0019A5C8() % 7;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->frame = func_0019A5C8() % 8;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 100 + 0x64;
        o->step = func_0019A5C8() % 30 + 0x10;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->size += 8.0f;
    }
    o->age++;
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b139", func_01E01910_b139);

/* shape b139:01E02070, 176 insns: variant of b149:01E020F0 (game value at 0xC212): a glow whose kind (f50) picks its look: kinds 0/1 are grey with an orange second
   colour, flickering, brightening for 12 ticks; kind 1 also grows to 400 by 15; kind 2 starts at 840, white with a
   brown second colour, brightens by 0x20 for 13 ticks then fades by 9; kinds 0/1 fade by 15 once the game value
   at 0xC212 passes 0x140; the position's first word advances 0x4000 each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 kind;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b139_01E02070;

typedef struct {
    u8 pad[0xC212];
    s16 v;
} Game_b139_01E02070;

static s32 func_01E02070_b139(Game_b139_01E02070 *g, Fx_b139_01E02070 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        if (o->kind == 2) {
            o->f48 = 840.0f;
        }
        if (o->kind < 2) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            func_001076F0(o->col2, 0xF0, 0x80, 0x10);
        } else {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x40, 0x10);
        }
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->kind < 2) {
        if (o->tick < 12) {
            o->col[3] += 0x10;
        }
    }
    if (o->kind == 2) {
        if (o->tick < 13) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x20;
            }
        } else if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind < 2) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col2, 0xF0, 8, 0x80);
        } else {
            func_001076F0(o->col2, 0x80, 8, 0x40);
        }
    }
    if (o->kind == 1) {
        if (o->f48 < 400.0f) {
            o->f48 += 15.0f;
        }
        if (g->v > 0x140) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        if (g->v > 0x140) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_00205C40(o->pos);
    o->pos[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b139:01E02330 (b139), 458 insns, 1 copy: the scene manager: set up the scene, then step the 150 effect slots
   and draw four kinds (rain trail at a point, flame, rain at a point, magic circle at a camera position); returns cue
   codes by frame */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[4];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 sel;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b139_01E02330;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xE4];
} Pt_b139_01E02330;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s16 rm[8];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b139_01E02330 fx[150];
    u8 pad4440[0x30];
    Pt_b139_01E02330 pt[128];
    u8 padBC70[0x70];
    s32 tex2[1];
    u8 padBCE4[0x1C];
    s32 count;
    u8 padBD04[8];
    s32 ot;
    u8 padBD10[0x3DC];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padC0F2[8];
    s16 cam;
    u8 padC0FC[0x112];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x16C];
} Scene_b139_01E02330;

static s32 func_01E02330_b139(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01360_b139();
    extern void func_01E00E10_b139();
    extern void func_01E009B0_b139();
    extern s32 func_01E01910_b139();
    extern void b139_01E02BF0();
    extern void b139_01E03820();
    Scene_b139_01E02330 *g = (Scene_b139_01E02330 *)arg0;
    s32 k;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s16 i;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xC580);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 370;
        g->jA = func_001F5560(func_001F53A0(), 0x4E, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 10; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        g->tex[0] = func_00202BF0(4, 0);
        for (k = 0; k < 1; k++) {
            g->tex2[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = func_0019A5C8() % 4;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E01360_b139(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E01620_b139) {
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[0];
                g->hBE = 0;
                v.x = g->pt[g->fx[i].sel].x;
                v.y = g->pt[g->fx[i].sel].y;
                v.z = g->pt[g->fx[i].sel].z;
                b139_01E03820(g, &g->fx[i], 0x20, v);
            }
            if (g->fx[i].fn == func_01E01780_b139) {
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex[0];
                g->hB8 = 4;
                g->hC0 = g->fx[i].hA;
                g->px = g->fx[i].x;
                g->py = g->fx[i].y;
                g->pz = g->fx[i].z;
                func_01E00E10_b139(g, &g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01910_b139) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x97, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->rm[3] >>= 1;
                g->rm[1] += g->rm[3];
                func_001F5F90(func_001F53A0(), &v);
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                g->hBE = 1;
                b139_01E02BF0(g, &g->fx[i], &g->pt[g->fx[i].sel], 0);
            }
            if (g->fx[i].fn == func_01E02070_b139) {
                if (g->fx[i].sel == 0) {
                    func_001F5620(func_001F53A0(), g->jA, &v);
                }
                if (g->fx[i].sel == 1) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                if (g->fx[i].sel == 2) {
                    func_001F5620(func_001F5380(), g->cam, &v);
                }
                func_01E009B0_b139(g, &g->fx[i], 0x21, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 240) {
        return 1;
    }
    if (g->frame == 335) {
        return 3;
    }
    if (g->frame > 250 && g->frame < 330) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b139:01E02A60, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b139_01E02A60 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b139_01E02A60;

typedef struct Obj_b139_01E02A60 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b139_01E02A60 slots[0x96];
    u8 padB[0xbd04 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xc20a - 0xbd04 - 4];
    s16 fB2B0;
} Obj_b139_01E02A60;

static s32 func_01E02A60_b139(Obj_b139_01E02A60 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b139_01E02A60 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b139", func_01E02BF0_b139);

/* shape b139:01E03820: sibling of b016:01E00ED0 (one sprite quad, drawn twice). Needs func_01E00110_b139 in the
   same file and static (the original reuses $a0 across the call). */

typedef struct Cam_b139_01E03820 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b139_01E03820;

typedef struct Obj_b139_01E03820 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b139_01E03820;

typedef struct Xyz_b139_01E03820 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b139_01E03820;

typedef struct Uv_b139_01E03820 {
    f32 u, v;
} Uv_b139_01E03820;

typedef struct Pk_b139_01E03820 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b139_01E03820 uv;
    u64 pad18;
    Xyz_b139_01E03820 v[4];
    u64 pad60[6];
} Pk_b139_01E03820;

typedef struct Buf_b139_01E03820 {
    u64 tag;
    Pk_b139_01E03820 pk;
} Buf_b139_01E03820;

static void func_01E03820_b139(Obj_b139_01E03820 *obj, Cam_b139_01E03820 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b139_01E03820 buf;
    Uv_b139_01E03820 uv;
    s32 sel;
    s32 mode;
    Pk_b139_01E03820 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_b139((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        mode = flags & 0xF;
        if (mode == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}
