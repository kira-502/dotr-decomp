#include "common.h"

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

static void func_01E00080_b384(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
} Obj_b108_01E009A0;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0x0A];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b108_01E009A0;

static void func_01E00920_b384(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E00D70_b384(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b384_01E00080();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b384_01E00080(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* OVL_WARM */

/* shape b279:01E00920: quad ring sprite (b065/b193 family). The draw mode is written inline as (mode & 0xF) in each
   test: -O4 hoists it into a fresh register so the counter i can reuse mode's; a kind local coalesces with mode instead. */

typedef struct {
    f32 x, y, z, w;
} Vec_b279_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b279_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b279_01E00920;

typedef struct {
    u64 st;
    Xyz_b279_01E00920 p;
} Vtx_b279_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b279_01E00920 c;
    Vtx_b279_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b279_01E00920;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x28];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col[4];
} Anim_b279_01E00920;

typedef struct {
    u8 pad00[0x80];
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
} Obj_b279_01E00920;

extern void b384_01E00080(Pkt_b279_01E00920 *, void *, s32);

static void func_01E012C0_b384(Obj_b279_01E00920 *o, Anim_b279_01E00920 *an, s32 mode, Vec_b279_01E00920 pos) {
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b279_01E00920 quad[4];
    Vec_b279_01E00920 at;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    struct {
        u64 pre;
        Pkt_b279_01E00920 pk;
    } buf;
    Col_b279_01E00920 col;
    s16 blend;
    f32 w0;
    s16 width;
    s16 i;
    s16 a;
    s16 j;
    Pkt_b279_01E00920 *p;
    f32 w1;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    j = 0;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, 0, an->rot, &at);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    width = an->width;
    b384_01E00080(p, o->b94, o->hC0);
    for (i = 0; i < o->count; j += an->step, i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + width);
        quad[1].x = w0 * func_00108030(o->bD8, a, 1);
        quad[1].z = w0 * func_00108030(o->bD8, a, 0);
        quad[3].x = w1 * func_00108030(o->bD8, a, 1);
        quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        if ((mode & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if ((mode & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if ((mode & 0xF) == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b384:01E01710, 274 insns: the scene script of b384: counts ctx+0x450E; up to tick 117 the mark (ctx+0x4470)
   takes x from joint 0x44DC and y, z from joint 0x44D8, moves along z by the step ctx+0x44C4 (side flag ctx+0x450A)
   and rises by 3 x the table sine of ctx+0x44FC (after tick 102 by 3); then until tick 160 it moves 4 along z and
   sinks 0.3, the burst point (ctx+0x250) follows the mark, and on tick 160 it spawns 0x1E02630, five 0x1E02130, six
   0x1E01F90 and two 0x1E02130; past tick 15 the step grows by 0.5 up to 10; from 65 to 160 a 0x1E023F0 a tick on
   joint 0x44D8; on tick 15 a 0x1E02800; 0x1E02A60 from 45 to 90 and 0x1E02D40 from 118 to 160 at the mark; past
   tick 15 ctx+0x44FC turns by 3 up to 90 */

typedef struct {
    u8 pad0[0xD8];
    u8 trig[1];
    u8 padD9[0x250 - 0xD9];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Vec4f m;
    u8 pad4480[0x44C4 - 0x4480];
    f32 step;
    u8 pad44C8[0x44D8 - 0x44C8];
    s16 id0;
    u8 pad44DA[2];
    s16 id1;
    u8 pad44DE[0x44FC - 0x44DE];
    s16 ang;
    u8 pad44FE[0x4506 - 0x44FE];
    s16 slot;
    u8 pad4508[2];
    s16 side;
    u8 pad450C[2];
    s16 t;
} Ctx_b384_01E01710;

static void func_01E01710_b384(Ctx_b384_01E01710 *g) {
    extern void b384_01E01F90();
    extern void b384_01E02130();
    extern void b384_01E023F0();
    extern void b384_01E02630();
    extern void b384_01E02800();
    extern void b384_01E02A60();
    extern void b384_01E02D40();
    extern void b384_01E03790(Ctx_b384_01E01710 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[2][4];

    g->t++;
    if (g->t < 118) {
        func_001F5620(func_001F53A0(), g->id0, v[0]);
        func_001F5620(func_001F53A0(), g->id1, v[1]);
        g->m.x = v[1][0];
        g->m.y = v[0][1];
        g->m.z = v[0][2];
        if (g->side != 0) {
            g->m.z -= g->step;
        } else {
            g->m.z += g->step;
        }
        if (g->t < 103) {
            g->m.y += 3.0f * func_00108030(g->trig, g->ang, 0);
        } else {
            g->m.y += 3.0f;
        }
    } else {
        if (g->t < 161) {
            if (g->side != 0) {
                g->m.z -= 4.0f;
            } else {
                g->m.z += 4.0f;
            }
            g->m.y -= 0.3f;
        }
        g->pos = g->m;
        if (g->t == 160) {
            g->slot = 0;
            b384_01E03790(g, b384_01E02630, 0);
            b384_01E03790(g, b384_01E02130, 0);
            b384_01E03790(g, b384_01E02130, 0);
            b384_01E03790(g, b384_01E02130, 0);
            b384_01E03790(g, b384_01E02130, 0);
            b384_01E03790(g, b384_01E02130, 0);
            b384_01E03790(g, b384_01E01F90, 0);
            b384_01E03790(g, b384_01E01F90, 0);
            b384_01E03790(g, b384_01E01F90, 0);
            b384_01E03790(g, b384_01E01F90, 0);
            b384_01E03790(g, b384_01E01F90, 0);
            b384_01E03790(g, b384_01E01F90, 0);
            g->slot = 0;
            b384_01E03790(g, b384_01E02130, 0);
            b384_01E03790(g, b384_01E02130, 0);
        }
    }
    if (g->t > 15) {
        if (g->step < 10.0f) {
            g->step += 0.5f;
        }
    }
    if (g->t >= 65 && g->t < 161) {
        func_001F5620(func_001F53A0(), g->id0, &g->pos);
        g->slot = 0;
        b384_01E03790(g, b384_01E023F0, 0);
    }
    if (g->t == 15) {
        b384_01E03790(g, b384_01E02800, 0);
    }
    if (g->t >= 45 && g->t < 91) {
        g->pos = g->m;
        b384_01E03790(g, b384_01E02A60, 0);
    }
    if (g->t >= 118 && g->t < 161) {
        g->pos = g->m;
        b384_01E03790(g, b384_01E02D40, 0);
    }
    if (g->t >= 15 && g->ang < 90) {
        g->ang += 3;
    }
}

/* shape b384:01E01B60, 268 insns: b111:01E01D30 with this module's table and side; b149:01E01770 cousin: size 10, grey 0x80, random frame 0..6, turn, spin and hA 0..7,
   height from 0 growing by 15 up to its limit 100..449 while it fades in by 0x20 for 147 ticks, then fades by 8 and
   ends; at tick 135 it hands its position to the scene and fires the module's b384:01E01F90 effect three times, then
   b384:01E023F0 six times in ten at a point jittered -15..14; its swing f34 is 3 x the table sine of h5C; from tick 96
   to 130 it is pushed 5 a tick in z by the scene side (0x450A) and sinks 1 while above the target's height - 10; from
   tick 141 it turns 5, rises by hE and 1 and grows 1; h5C turns by 6 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad260[0x450A - 0x260];
    s16 side;
    u8 pad450C[0x4710 - 0x450C];
    u8 table[1];
} Mgr_b384_01E01B60;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
} Obj_b384_01E01B60;

static s32 func_01E01B60_b384(Mgr_b384_01E01B60 *m, Obj_b384_01E01B60 *o) {
    extern void b384_01E01F90();
    extern void b384_01E023F0();
    extern void b384_01E03790(Mgr_b384_01E01B60 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    f32 v[4];

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 147) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
        if (o->h52 > o->h50) {
            o->h50 += 15;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 == 135) {
        m->pos = o->pos;
        b384_01E03790(m, b384_01E01F90, 0);
        b384_01E03790(m, b384_01E01F90, 0);
        b384_01E03790(m, b384_01E01F90, 0);
        m->pos.x += func_0019A5C8() % 30 - 15;
        m->pos.y += func_0019A5C8() % 30 - 15;
        m->pos.z += func_0019A5C8() % 30 - 15;
        if (func_0019A5C8() % 10 < 6) {
            b384_01E03790(m, b384_01E023F0, 0);
        }
    }
    func_001F5F90(func_001F5380(), v);
    o->f34 = 3.0f * func_00108030(m->table, o->h5C, 1);
    if (o->h54 > 95 && o->h54 < 131) {
        if (m->side != 0) {
            o->pos.z -= 5.0f;
        } else {
            o->pos.z += 5.0f;
        }
        if (v[1] - 10.0f < o->pos.y) {
            o->pos.y -= 1.0f;
        }
    }
    if (o->h54 > 140) {
        o->h5A += 5;
        o->h50 += o->hE;
        o->pos.y += 1.0f;
        o->f48 += 1.0f;
    }
    o->h5C += 6;
    o->h54++;
    return 0;
}

/* shape b384:01E01F90, 102 insns: on start f48 5, variant 0..3, colour 0x80 grey, random 0x5A, 0xA 0..7, 0xC keeps
   the old 0x50, 0x50 10..59, speed 6..15 (0xE), 0x8 0..34, hold 3..7 (0x6); alpha 0x80 during the hold, then fades by
   8 and stops; 0x50 grows by the speed after the first tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b384_01E01F90;

static s32 func_01E01F90_b384(s32 arg0, Fx_b384_01E01F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 50 + 10;
        o->speed = func_0019A5C8() % 10 + 6;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b384:01E02130, 174 insns: b384:01E023F0 with the five-way pick on the first colour, size from 10, f5A forced
   to 45, a random step 1..4 (0x5C); alpha up for 8 ticks; size grows 0.5 (then 0.8 from tick 4), f4C by 0.4 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b384_01E02130;

static s32 func_01E02130_b384(s32 arg0, Fx_b384_01E02130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        func_001076F0(o->col, 0xCF, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->f52 = func_0019A5C8() % 5;
        if (o->f52 == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
        } else if (o->f52 == 1) {
            func_001076F0(o->col, 0x80, 0xFF, 8);
        } else if (o->f52 == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
        } else if (o->f52 == 3) {
            func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        } else if (o->f52 == 4) {
            func_001076F0(o->col, 0x80, 0x40, 0xFF);
        }
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f5A = 45;
        o->h5C = func_0019A5C8() % 4 + 1;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick < 4) {
        o->f48 += 0.5f;
        o->f4C += 0.4f;
    } else {
        o->f48 += 0.8f;
        o->f4C += 0.4f;
    }
    o->tick++;
    return 0;
}

/* shape b384:01E023F0, 143 insns: b384:01E02630 variant: the second colour is picked once from five by a random 0..4,
   random spins; alpha up by 64 to 0xC0 for 13 ticks, then down by 9; size grows by 3 with f4C = size - 2 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b384_01E023F0;

static s32 func_01E023F0_b384(s32 arg0, Fx_b384_01E023F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->f52 = func_0019A5C8() % 5;
        if (o->f52 == 0) {
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        } else if (o->f52 == 1) {
            func_001076F0(o->col2, 0x80, 0xFF, 8);
        } else if (o->f52 == 2) {
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        } else if (o->f52 == 3) {
            func_001076F0(o->col2, 0xFF, 0xFF, 0x80);
        } else if (o->f52 == 4) {
            func_001076F0(o->col2, 0x80, 0x40, 0xFF);
        }
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < 13) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 3.0f;
    o->f4C = o->f48 - 2.0f;
    o->tick++;
    return 0;
}

/* shape b384:01E02630, 114 insns: on start f48 300, colour 0xCF grey, random 0x5A, second alpha 0; the second colour
   cycles red / green / blue / yellow / violet by 0x52 (0..4); alpha grows by 0x40 (below 0xC0) for 16 ticks, then fades
   by 9 and stops; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[6];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b384_01E02630;

static s32 func_01E02630_b384(s32 arg0, Fx_b384_01E02630 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 300.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->f52 == 0) {
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
    } else if (o->f52 == 1) {
        func_001076F0(o->col2, 0x80, 0xFF, 8);
    } else if (o->f52 == 2) {
        func_001076F0(o->col2, 0x80, 0x80, 0xFF);
    } else if (o->f52 == 3) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0x80);
    } else if (o->f52 == 4) {
        func_001076F0(o->col2, 0x80, 0x40, 0xFF);
    }
    o->f52++;
    if (o->f52 > 4) {
        o->f52 = 0;
    }
    if (o->tick < 16) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b384:01E02800, 149 insns: b384:01E02630's colour-cycling glow, size 5 with a red second colour, brightening by 0x18 for 135 ticks, growing 10 a tick on ticks 16..34 and 0.7 a tick below 30 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[6];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b384_01E02800;

static s32 func_01E02800_b384(s32 arg0, Fx_b384_01E02800 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 0x40, 0x40);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->f52 == 0) {
        func_001076F0(o->col2, 0xFF, 0x80, 0x80);
    } else if (o->f52 == 1) {
        func_001076F0(o->col2, 0x80, 0xFF, 8);
    } else if (o->f52 == 2) {
        func_001076F0(o->col2, 0x80, 0x80, 0xFF);
    } else if (o->f52 == 3) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0x80);
    } else if (o->f52 == 4) {
        func_001076F0(o->col2, 0x80, 0x40, 0xFF);
    }
    o->f52++;
    if (o->f52 > 4) {
        o->f52 = 0;
    }
    if (o->tick < 0x87) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x18;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick > 15 && o->tick < 35) {
        o->f48 += 10.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        if (o->f48 < 30.0f) {
            o->f48 += 0.7f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b384:01E02A60, 181 insns: b279:01E02690's five-colour ring with size 10..29 shrinking by 1 (f4C = size + 6),
   alpha up for 8 ticks */

typedef struct {
    u8 pad00[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b384_01E02A60;

static s32 func_01E02A60_b384(void *arg0, Obj_b384_01E02A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = func_0019A5C8() % 20 + 10;
        func_001076F0(o->col, 0xCF, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->h52 = func_0019A5C8() % 5;
        if (o->h52 == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        } else if (o->h52 == 1) {
            func_001076F0(o->col, 0x80, 0xFF, 8);
            func_001076F0(o->col2, 0x80, 0xFF, 8);
        } else if (o->h52 == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        } else if (o->h52 == 3) {
            func_001076F0(o->col, 0xFF, 0xFF, 0x80);
            func_001076F0(o->col2, 0xFF, 0xFF, 0x80);
        } else if (o->h52 == 4) {
            func_001076F0(o->col, 0x80, 0x40, 0xFF);
            func_001076F0(o->col2, 0x80, 0x40, 0xFF);
        }
        o->h5A = func_0019A5C8() % 360;
        o->state = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h5A = 45;
        o->h5C = 5;
    }
    if (o->t < 8) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f48 -= 1.0f;
    o->f4C = 6.0f + o->f48;
    o->t++;
    return 0;
}

/* shape b279:01E02690, 180 insns: b183:01E012F0 family: a two-tone flash in one of 5 colour pairs, growing 2 a frame; fades in to 0xC0 for 3 ticks, out by 9 */

typedef struct {
    u8 pad00[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b279_01E02690;

static s32 func_01E02D40_b384(void *arg0, Obj_b279_01E02690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = func_0019A5C8() % 10;
        func_001076F0(o->col, 0xCF, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->h52 = func_0019A5C8() % 5;
        if (o->h52 == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        } else if (o->h52 == 1) {
            func_001076F0(o->col, 0x80, 0xFF, 8);
            func_001076F0(o->col2, 0x80, 0xFF, 8);
        } else if (o->h52 == 2) {
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        } else if (o->h52 == 3) {
            func_001076F0(o->col, 0xFF, 0xFF, 0x80);
            func_001076F0(o->col2, 0xFF, 0xFF, 0x80);
        } else if (o->h52 == 4) {
            func_001076F0(o->col, 0x80, 0x40, 0xFF);
            func_001076F0(o->col2, 0x80, 0x40, 0xFF);
        }
        o->h5A = func_0019A5C8() % 360;
        o->state = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h5A = 45;
        o->h5C = 5;
    }
    if (o->t < 3) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f48 += 2.0f;
    o->f4C = o->f48 - 6.0f;
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03010_b384(void) {
    return 0;
}

/* shape b384:01E03020 (b384), 475 insns, 1 copy: b384 scene manager in b111:01E02F00 form: setup (camera and three
   joints, type-4 textures 10..15 and 0, one type-5, a 256 s8 jitter), step b384:01E01710 and every slot (150 of 0x70)
   but the empty b384:01E03010, draw the b384:01E01B60/01F90 flames, b384:01E02130/02A60/02D40 flames3 and
   b384:01E023F0/02630/02800 circles; scene code from the timer */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0xC];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b384_01E03020;

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
    union {
        s32 rm[4];
        s16 uv[8];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b384_01E03020 fx[150];
    u8 pad4440[0x30];
    Vec4f v4470;
    s32 tex2[1];
    u8 pad4484[0x1C];
    s32 count;
    u8 pad44A4[8];
    s32 ot;
    u8 pad44B0[0x28];
    s16 j[6];
    u8 pad44E4[4];
    s16 cam;
    u8 pad44EA[0x12];
    s16 h44FC;
    u8 pad44FE[0xC];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b384_01E03020;

static s32 func_01E03020_b384(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01710_b384();
    extern void func_01E00920_b384();
    extern void func_01E00D70_b384();
    extern void func_01E012C0_b384();
    Scene_b384_01E03020 *g = (Scene_b384_01E03020 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4880);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 210;
        g->j[0] = func_001F5560(func_001F53A0(), 0x33, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x3A, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 1, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[0] = func_00202BF0(4, 0);
        for (i = 0; i < 1; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        g->h44FC = -60;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E01710_b384(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E03010_b384) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01B60_b384) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[0];
                g->hB8 = 6;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y + g->fx[k].f34;
                g->pz = g->fx[k].pos.z;
                func_01E00D70_b384(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F90_b384) {
                func_00106080(rm2, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex[15];
                g->hB8 = 6;
                g->hC0 = g->fx[k].hA;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                func_01E00D70_b384(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02130_b384) {
                g->tex88 = g->tex[15];
                if (g->fx[k].h50 == 0) {
                    func_00106080(rm3, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                } else {
                    func_00106080(rm4, 0x97, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                }
                v = g->fx[k].pos;
                g->hB8 = 9;
                func_01E012C0_b384(g, &g->fx[k], 0x20, v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E023F0_b384) {
                v = g->v4470;
                func_01E00920_b384(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02630_b384) {
                v = g->fx[k].pos;
                func_01E00920_b384(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02800_b384) {
                v = g->v4470;
                func_01E00920_b384(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02A60_b384) {
                g->tex88 = g->tex[15];
                if (g->fx[k].h50 == 0) {
                    func_00106080(rm5, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                } else {
                    func_00106080(rm6, 0x9B, g->fx[k].h56, NULL);
                    *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                }
                v = g->v4470;
                g->hB8 = 9;
                func_01E012C0_b384(g, &g->fx[k], 0x20, v);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D40_b384) {
                g->tex88 = g->tex[15];
                func_00106080(rm7, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm7;
                v = g->fx[k].pos;
                g->hB8 = 9;
                func_01E012C0_b384(g, &g->fx[k], 0x20, v);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 150) {
        return 1;
    }
    if (g->frame == 170) {
        return 4;
    }
    if (g->frame == 160) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b279:01E03220, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b279_01E03220 {
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
} Slot_b279_01E03220;

typedef struct Obj_b279_01E03220 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b279_01E03220 slots[0x96];
    u8 padB[0x44a4 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0x4506 - 0x44a4 - 4];
    s16 fB2B0;
} Obj_b279_01E03220;

static s32 func_01E03790_b384(Obj_b279_01E03220 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b279_01E03220 *s = NULL;
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
