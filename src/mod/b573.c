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

static void func_01E00080_b573(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b233:01E01BC0, 166 insns: b069:01E01A70 with the position passed by value: draws 4 copies of a gradient
   quad (colour A on three corners, B on the last), each turned by the effect's rotation; far z. The packet is
   passed in. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b233_01E01BC0;

typedef struct {
    Rgbaq_b233_01E01BC0 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b233_01E01BC0;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b233_01E01BC0 v[4];
    u8 tail[0x20];
} Pkt_b233_01E01BC0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b233_01E01BC0;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b233_01E01BC0;

static void func_01E00920_b573(Obj_b233_01E01BC0 *o, Fx_b233_01E01BC0 *fx, Pkt_b233_01E01BC0 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b233_01E01BC0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E00BC0_b573(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b573((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b112:01E00B60, 296 insns, 5 copies: draws a flat ring of 18 quads (inner and outer radius, 20 table steps
   apart) around a position, two colours; depth mode 0 (projected), 1 (far, after a packet tweak) or else front. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b112_01E00B60;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[0x20];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b112_01E00B60;

static void func_01E01120_b573(Obj_b112_01E00B60 *o, Ring_b112_01E00B60 *s, s32 mode, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    u8 pkt[0x90];
    s32 t;
    s32 k;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[0].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[2].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[2].z = s->inner * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[1].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[3].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[3].z = s->inner * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[1].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[3].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[3].z = s->inner * func_00108030(o->xD8, t, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
        a += 20;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b573", func_01E015C0_b573);

/* shape b573:01E02590, 82 insns: a blue spark that spins by a random 2..6 a tick (its old angle moved to +0xA), random size 0..34 and hold 2..4 ticks: in by 64 up to 0x80, then out by 7 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[8];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b573_01E02590;

static s32 func_01E02590_b573(s32 arg0, Glow_b573_01E02590 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 1;
        o->kind = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->hA = o->h30;
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->hC = 0;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->h30 += o->hE;
    o->tick++;
    return 0;
}

/* shape b573:01E026E0, 57 insns: a blue-white burst: frame 30 and a random angle once; fades in by 0x50 for 3 frames up
   to 0xA0, then out by 9 until it ends */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b573_01E026E0;

static s32 func_01E026E0_b573(void *arg0, Obj_b573_01E026E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    func_001076F0(o->c1, 0x1F, 0x1F, 0xFF);
    if (o->state == 1) {
        o->h38 = 0x1E;
        o->ang = func_0019A5C8() % 360;
        o->h34 = 0;
        o->state = 2;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b573:01E027D0, 99 insns: a grey flickering ring: frame 4 growing by 2 to 30 (by 9 more while fading), alpha up by 14 to
   0x90 until frame 70, then down by 13 until it ends; once the scene timer passes 280 it widens by 0x30 to 0x600 and grows to 90 */

typedef struct {
    u8 pad0[0x2BC0];
    s16 timer;
} Game_b573_01E027D0;

typedef struct {
    u8 pad0[0xE];
    s16 hE;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 size;
    s16 width;
} Obj_b573_01E027D0;

static s32 func_01E027D0_b573(Game_b573_01E027D0 *g, Obj_b573_01E027D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->sub = 0;
        o->hE = 1;
        o->state = 2;
    }
    if (o->t < 0x46) {
        if (o->c0[3] < 0x90) {
            o->c0[3] += 0xE;
        }
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        o->size += 9;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
    }
    if (o->size < 0x1E) {
        o->size += 2;
    }
    if (g->timer > 0x118) {
        if (o->width < 0x600) {
            o->width += 0x30;
        }
    }
    if (g->timer > 0x118) {
        if (o->size < 0x5A) {
            o->size += 1;
        }
    }
    o->t++;
    return 0;
}

/* shape b573:01E02960, 81 insns: a blue column (b267:01E00E50 shape): frame 46, size 3 by 8 growing by 8 in height, turning 10, direction from its angle; both alphas
   up by 0x40 for 2 frames, then down by 13 until the first runs out */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[2];
    s16 dir;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b573_01E02960;

static s32 func_01E02960_b573(void *arg0, Obj_b573_01E02960 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x2E;
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        func_001076F0(o->c1, 0x30, 0x30, 0x80);
        o->w = 3;
        o->h = 8;
        if (o->ang == 0) {
            o->dir = 0;
        } else {
            o->dir = 1;
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        o->c0[3] += 0x40;
        o->c1[3] += 0x40;
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xE) {
            o->c1[3] -= 0xD;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->dir == 0) {
        o->h += 8;
    } else {
        o->h += 8;
    }
    o->t++;
    o->ang += 0xA;
    return 0;
}

/* shape b573:01E02AB0, 83 insns: on start variant 0..6 (0x34), step 4..6 (0x8), 0x6 = 10, both colours
   (0x80, 0x80, 0x20); both alphas grow by 12 (below 0x80) for 20 ticks, then once the game step 0x2BC0 passes 0xDC
   fade by 9 (the first ends it) */

typedef struct {
    u8 pad0[0x2BC0];
    s16 step;
} Game_b573_01E02AB0;

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    u8 padA[0x1E];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b573_01E02AB0;

static s32 func_01E02AB0_b573(Game_b573_01E02AB0 *g, Fx_b573_01E02AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
        o->f6 = 10;
        func_001076F0(o->col, 0x80, 0x80, 0x20);
        func_001076F0(o->col2, 0x80, 0x80, 0x20);
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (g->step > 0xDC) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xA) {
            o->col2[3] -= 9;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b573:01E02C00, 152 insns: a rising spark sized by the scene frame (0x2BC0): before frame 195 small, yellow, slow
   (size 1, rise 1, held 1..3); after it blue (size 4, rise 5, held 4..6); after frame 220 big (size 18, rise 15,
   held 6..8); frame 0..3, keeps its old height in 0xA, turn 0..359, f8 0..34; alpha grows by 0x40 (to 0x80) while
   held, then fades by 9 (ends below 11) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 h0;
    s16 fC;
    s16 rise;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b573_01E02C00;

typedef struct {
    u8 pad0[0x2BC0];
    s16 frame;
} Scene_b573_01E02C00;

static s32 func_01E02C00_b573(Scene_b573_01E02C00 *g, Fx_b573_01E02C00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (g->frame < 0xC3) {
            o->size = 1;
        } else {
            o->size = 4;
        }
        if (g->frame > 0xDC) {
            o->size = 18;
        }
        o->frame = func_0019A5C8() % 4;
        if (g->frame < 0xC3) {
            func_001076F0(o->col, 0x80, 0x80, 0x20);
        } else {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        }
        o->h0 = o->h;
        o->h = 0;
        o->ang = func_0019A5C8() % 360;
        if (g->frame < 0xC3) {
            o->rise = 1;
        } else {
            o->rise = 5;
        }
        if (g->frame > 0xDC) {
            o->rise = 15;
        }
        o->f8 = func_0019A5C8() % 35;
        if (g->frame < 0xC3) {
            o->hold = func_0019A5C8() % 3 + 1;
        } else {
            o->hold = func_0019A5C8() % 3 + 4;
        }
        if (g->frame > 0xDC) {
            o->hold = func_0019A5C8() % 3 + 6;
        }
        o->fC = 0;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->h += o->rise;
    o->t++;
    return 0;
}

/* shape b573:01E02E60, 73 insns: a dark-teal puff: frame 23, random angle, its full-alpha time extended by 3..12; fades
   in by 0x40 to 0x80, then out by 14 while its frame grows by 6 */

typedef struct {
    u8 pad0[0xE];
    s16 hold;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b573_01E02E60;

static s32 func_01E02E60_b573(void *arg0, Obj_b573_01E02E60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x10, 0x10, 0x10);
    func_001076F0(o->c1, 0x1F, 0x80, 0x80);
    if (o->state == 1) {
        o->h38 = 0x17;
        o->ang = func_0019A5C8() % 360;
        o->h34 = 0;
        o->hold += (s16)(func_0019A5C8() % 10 + 3);
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        } else {
            o->state = 0;
        }
        o->h38 += 6;
    }
    o->t++;
    return 0;
}

/* shape b573:01E02F90, 59 insns: a grey puff: frame 6, random angle; fades in by 20 to 0xA0 for 8 frames, then once the
   game timer passes 0x96 out by 5 until it ends */

typedef struct {
    u8 pad0[0x2BC0];
    s16 timer;
} Game_b573_01E02F90;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b573_01E02F90;

static s32 func_01E02F90_b573(Game_b573_01E02F90 *g, Obj_b573_01E02F90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x4F, 0x4F, 0x4F);
    if (o->state == 1) {
        o->h38 = 6;
        o->ang = func_0019A5C8() % 360;
        o->h34 = 2;
        o->state = 2;
    }
    if (o->t < 8) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x14;
        }
    } else if (g->timer > 0x96) {
        if (o->c0[3] > 6) {
            o->c0[3] -= 5;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b573:01E03080, 55 insns: a yellow flash (b267:01E01740 twin): set up once (yellow, frame 10), fades in by 12 for 20 frames,
   then once the game timer passes 0xDC fades out by 9 until it ends */

typedef struct {
    u8 pad0[0x2BC0];
    s16 timer;
} Game_b573_01E03080;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 state;
} Obj_b573_01E03080;

static s32 func_01E03080_b573(Game_b573_01E03080 *g, Obj_b573_01E03080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 0x20);
        func_001076F0(o->c0, 0x80, 0x80, 0x20);
        o->h34 = 0xA;
        o->state = 2;
    }
    if (o->t < 0x14) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
    } else if (g->timer > 0xDC) {
        if (o->c0[3] > 0xA) {
            o->c0[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b573:01E03160, 131 insns: b573:01E03370 family flickering spark (size 10..29, frame cycling every third tick, fA = old f30, f30 30..59, fE 15, held 10..12 ticks: alpha up by 64, then down by 9); colour flips 0xC0/0x40 every third tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b573_01E03160;

static s32 func_01E03160_b573(s32 arg0, Fx_b573_01E03160 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 20 + 10;
        o->f34 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 30 + 30;
        o->f3A = func_0019A5C8() % 360;
        o->fE = 15;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 10;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        } else {
            o->f34 = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b573:01E03370, 126 insns: a flickering spark (size 40..69, frame cycling 0..7, fA = old f30, f30 80..179 growing 45 per tick, held 3..5 ticks: alpha up by 64, then down by 29); colour flips 0xC0/0x40 on every third tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b573_01E03370;

static s32 func_01E03370_b573(s32 arg0, Fx_b573_01E03370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 30 + 40;
        o->f34 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 100 + 80;
        o->f3A = func_0019A5C8() % 360;
        o->fE = 45;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->f34 < 7) {
        o->f34++;
    } else {
        o->f34 = 0;
    }
    o->f30 += o->fE;
    o->tick++;
    return 0;
}

/* shape b573:01E03570, 89 insns: a grey-yellow blinker: frame 500, random angle, full-alpha time 4; alpha up by 0x40 to 0x80,
   then blinks grey by the game timer's parity until 0x177, then fades by 14 until it ends */

typedef struct {
    u8 pad0[0x2BC0];
    s16 timer;
} Game_b573_01E03570;

typedef struct {
    u8 pad0[0xE];
    s16 hold;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b573_01E03570;

static s32 func_01E03570_b573(Game_b573_01E03570 *g, Obj_b573_01E03570 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x80, 0x80, 0x80);
    func_001076F0(o->c1, 0x80, 0x80, 0xF0);
    if (o->state == 1) {
        o->h38 = 0x1F4;
        o->ang = func_0019A5C8() % 360;
        o->h34 = 0;
        o->hold = 4;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (g->timer < 0x177) {
        if (g->timer % 2 == 1) {
            func_001076F0(o->c0, 0x80, 0x80, 0x80);
        } else {
            func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b573:01E036E0, 126 insns: b573:01E03370 with a blue start colour and f30 growing 125 per tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b573_01E036E0;

static s32 func_01E036E0_b573(s32 arg0, Fx_b573_01E036E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 30 + 40;
        o->f34 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 100 + 80;
        o->f3A = func_0019A5C8() % 360;
        o->fE = 125;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
    }
    if (o->f34 < 7) {
        o->f34++;
    } else {
        o->f34 = 0;
    }
    o->f30 += o->fE;
    o->tick++;
    return 0;
}

/* shape b573:01E038E0, 54 insns: volume fade: starts at 0x80; while the game counter at 0x2B20 is over 0x14 it drops by
   10 to 0x30, otherwise it rises by 10 (clamped) and stops at 0x80; func_001F6D00 gets it when the counter is 1,
   else the volume */

typedef struct {
    u8 pad0[0x2B20];
    s32 count;
} Game_b573_01E038E0;

typedef struct {
    u8 pad0[0x30];
    s16 v;
    u8 pad32[0x4];
    s16 mode;
} Fx_b573_01E038E0;

static s32 func_01E038E0_b573(Game_b573_01E038E0 *g, Fx_b573_01E038E0 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x14) {
        if (o->v > 0x30) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
            o->mode = 0;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    if (g->count == 1) {
        func_001F6D00(o->v);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

static s32 func_01E039C0_b573(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05480_b573;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05488_b573;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b573:01E03A10, 106 insns: b378:01E01B80 family: draws the grey bar sprite at its own alpha, which fades in by 11 up to 0x68 for 175 ticks, then out by 12 and ends; also ends at scene state 9 */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b573_01E03A10;

typedef struct {
    Hdr_b573_01E03A10 h;
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
} Pkt_b573_01E03A10;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b573_01E03A10;

typedef struct {
    u8 pad[0x2B20];
    s32 state;
} Game_b573_01E03A10;

static s32 func_01E03A10_b573(Game_b573_01E03A10 *g, Obj_b573_01E03A10 *o) {
    Pkt_b573_01E03A10 p __attribute__((aligned(8)));

    ((Hdr_b573_01E03A10 *)(s32)&p)->count = 0x26;
    ((Hdr_b573_01E03A10 *)(s32)&p)->tag = 5;
    ((Hdr_b573_01E03A10 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b573_01E03A10 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = o->col[3];
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
    if (o->tick < 175) {
        if (o->col[3] < 0x68) {
            o->col[3] += 11;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (g->state == 9) {
        o->mode = 0;
    }
    return 0;
}

/* shape b573:01E03BC0, 41 insns: look up the textures: group 4 cells 0-4, group 4 cells 14-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x270];
    s32 tex[16];
    u8 pad2B0[0x2850];
    s32 tex5[3];
} Scene_b573_01E03BC0;

static void func_01E03BC0_b573(s32 arg0, Scene_b573_01E03BC0 *o) {
    s32 i;

    for (i = 0; i < 5; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 14; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b573:01E03C70 (b573), 877 insns, 1 copy: b573 scene manager: setup (four joints, eight random camera joints,
   turn from the model angle, textures via b573:01E03BC0, two s8 jitter tables, thirty random 0..14), runs
   b573:01E015C0, steps the 140 slots as an else-if chain (01E039C0's fog call written out), draws thirteen slot
   kinds; returns 1 / 3 at frames 290 / 380, 6 in 301..374, 8 once the 400-frame countdown runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[4];
    s16 hA;
    u8 padC[0x18];
    void *fn;
    u8 c0[4];
    u8 c1[4];
    s16 h30;
    s16 t;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Slot_b573_01E03C70;

typedef struct {
    f32 a, b, c, d;
} Q_b573_01E03C70;

typedef union {
    Q_b573_01E03C70 q;
    s16 s[8];
} R_b573_01E03C70;

typedef struct {
    u8 pad0[0x20];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    R_b573_01E03C70 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 crdD8[0x198];
    s32 tex[16];
    Slot_b573_01E03C70 slot[140];
    u8 pad25B0[0x30];
    Vec4f pa[5];
    Vec4f pb[70];
    Vec4f pc[7];
    s32 tex5[3];
    u8 pad2B0C[0x14];
    s32 count2;
    u8 pad2B24[8];
    s32 ot;
    u8 pad2B30[0xC];
    f32 f2B3C;
    u8 pad2B40[0x14];
    s16 j[4];
    u8 pad2B5C[8];
    s16 js[8];
    s16 r[30];
    u8 pad2BB0[0xA];
    s16 turn;
    u8 pad2BBC[2];
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad2DC2[2];
    u8 crd[0x16C];
} Scene_b573_01E03C70;

static s32 func_01E03C70_b573(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b573_01E015C0();
    extern void b573_01E04B60();
    extern void b573_01E04EE0();
    extern void b573_01E05120();
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
    s32 ang[4];
    u8 buf[0x90] __attribute__((aligned(8)));
    f32 b;
    f32 a;
    s32 t;
    s32 i;
    Scene_b573_01E03C70 *g = (Scene_b573_01E03C70 *)arg0;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x2F30);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count2 = 0x190;
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->j[0] = func_001F5560(func_001F53A0(), 0x30, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x3F, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x50, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x39, 0);
        for (i = 0; i < 8; i++) {
            t = func_001F54E0(func_001F5380());
            t = func_0019A5C8() % t;
            if (t == 0) {
                t++;
            }
            if (!i) {
                g->js[i] = func_001F5560(func_001F5380(), t, 1);
            } else {
                g->js[i] = func_001F5560(func_001F5380(), t, 0);
            }
        }
        func_01E03BC0_b573(0, (Scene_b573_01E03BC0 *)g);
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 12 - 6;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 8 - 4;
        }
        for (i = 0; i < 30; i++) {
            g->r[i] = func_0019A5C8() % 15;
        }
        g->f2B3C = 3.0f;
        return 0;
    }
    b573_01E015C0(g, 0);
    for (i = 0; i < 140; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == (void *)func_01E02590_b573) {
                func_01E02590_b573((s32)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E026E0_b573) {
                func_01E026E0_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E027D0_b573) {
                func_01E027D0_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E02960_b573) {
                func_01E02960_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E02AB0_b573) {
                func_01E02AB0_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E02C00_b573) {
                func_01E02C00_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E02E60_b573) {
                func_01E02E60_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E02F90_b573) {
                func_01E02F90_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E03080_b573) {
                func_01E03080_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E03160_b573) {
                func_01E03160_b573((s32)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E03370_b573) {
                func_01E03370_b573((s32)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E03570_b573) {
                func_01E03570_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E036E0_b573) {
                func_01E036E0_b573((s32)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E038E0_b573) {
                func_01E038E0_b573((void *)g, (void *)&g->slot[i]);
            } else if (g->slot[i].fn == (void *)func_01E039C0_b573) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05480_b573;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05488_b573;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            } else if (g->slot[i].fn == (void *)func_01E03A10_b573) {
                func_01E03A10_b573((void *)g, (void *)&g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 140; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == (void *)func_01E02590_b573) {
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm;
                g->tex88 = g->tex[15];
                g->count = 0xF;
                g->mode = 0;
                g->px = g->pa[g->slot[i].hA].x;
                g->py = g->pa[g->slot[i].hA].y;
                g->pz = g->pa[g->slot[i].hA].z;
                func_01E00BC0_b573((void *)g, (void *)&g->slot[i], 0x20, g->jit);
                g->count = 0;
            }
            if (g->slot[i].fn == (void *)func_01E026E0_b573) {
                if (g->slot[i].h30 < 5) {
                    v.x = g->pa[g->slot[i].h30].x;
                    v.y = g->pa[g->slot[i].h30].y;
                    v.z = g->pa[g->slot[i].h30].z;
                    func_01E01120_b573((void *)g, (void *)&g->slot[i], 1, v);
                } else {
                    v.x = g->pc[g->slot[i].h30 - 5].x;
                    v.y = g->pc[g->slot[i].h30 - 5].y;
                    v.z = g->pc[g->slot[i].h30 - 5].z;
                    func_01E01120_b573((void *)g, (void *)&g->slot[i], 1, v);
                }
            }
            if (g->slot[i].fn == (void *)func_01E027D0_b573) {
                func_001F5F90(func_001F53A0(), &v);
                g->px = v.x;
                g->py = v.y + 2.5f;
                g->pz = v.z;
                b573_01E04B60(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == (void *)func_01E02960_b573) {
                g->tex88 = g->tex[15];
                func_00106080(rm2, 0x9A, 1, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm2;
                v.x = g->pa[g->slot[i].h30].x;
                v.y = g->pa[g->slot[i].h30].y;
                v.z = g->pa[g->slot[i].h30].z;
                g->mode = 0;
                func_01E00920_b573((void *)g, (void *)&g->slot[i], (void *)buf, v);
            }
            if (g->slot[i].fn == (void *)func_01E02AB0_b573) {
                g->tex88 = g->tex[3];
                func_00106080(rm3, 0x1E, g->slot[i].h34, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm3;
                g->count = 1;
                func_001F5F90(func_001F53A0(), &v);
                v.x = v.x;
                v.y = v.y + 2.5;
                v.z = v.z;
                g->mode = 0;
                b573_01E05120(g, &g->slot[i], 0, &v);
                g->count = 0;
            }
            if (g->slot[i].fn == (void *)func_01E02C00_b573) {
                func_00106080(rm4, 0x9B, g->slot[i].h34, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm4;
                g->tex88 = g->tex[15];
                if (g->frame < 0xDC) {
                    g->count = 0xF;
                } else {
                    g->count = 8;
                }
                g->mode = 0;
                g->px = g->pb[g->slot[i].hA].x;
                g->py = g->pb[g->slot[i].hA].y;
                g->pz = g->pb[g->slot[i].hA].z;
                func_01E00BC0_b573((void *)g, (void *)&g->slot[i], 0x20, g->jit);
                g->count = 0;
            }
            if (g->slot[i].fn == (void *)func_01E02E60_b573) {
                v.x = g->pb[g->slot[i].h30].x;
                v.y = g->pb[g->slot[i].h30].y;
                v.z = g->pb[g->slot[i].h30].z;
                func_01E01120_b573((void *)g, (void *)&g->slot[i], 1, v);
            }
            if (g->slot[i].fn == (void *)func_01E02F90_b573) {
                v.x = g->pa[g->slot[i].h30].x;
                v.y = g->pa[g->slot[i].h30].y;
                v.z = g->pa[g->slot[i].h30].z;
                b573_01E04EE0(g, &g->slot[i], buf, &v);
            }
            if (g->slot[i].fn == (void *)func_01E03160_b573) {
                func_00106080(rm5, 0x14, g->slot[i].h34, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm5;
                g->tex88 = g->tex5[2];
                g->count = 3;
                g->mode = func_0019A5C8() % 8;
                g->px = g->pb[g->slot[i].hA].x;
                g->py = g->pb[g->slot[i].hA].y;
                g->pz = g->pb[g->slot[i].hA].z;
                func_01E00BC0_b573((void *)g, (void *)&g->slot[i], 0x20, g->jit);
                g->count = 0;
            }
            if (g->slot[i].fn == (void *)func_01E03370_b573) {
                func_00106080(rm6, 0x14, g->slot[i].h34, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm6;
                g->tex88 = g->tex5[2];
                g->count = 3;
                g->mode = func_0019A5C8() % 8;
                func_001F5620(func_001F5380(), g->js[g->slot[i].hA], &v);
                g->px = g->slot[i].x;
                g->py = g->slot[i].y;
                g->pz = g->slot[i].z;
                func_01E00BC0_b573((void *)g, (void *)&g->slot[i], 0x20, g->jit);
                g->count = 0;
            }
            if (g->slot[i].fn == (void *)func_01E03570_b573) {
                v.x = g->pb[g->slot[i].h30].x;
                v.y = g->pb[g->slot[i].h30].y;
                v.z = g->pb[g->slot[i].h30].z;
                func_01E01120_b573((void *)g, (void *)&g->slot[i], 1, v);
            }
            if (g->slot[i].fn == (void *)func_01E036E0_b573) {
                func_00106080(rm7, 0x14, g->slot[i].h34, NULL);
                g->rect.q = *(Q_b573_01E03C70 *)rm7;
                g->tex88 = g->tex5[2];
                g->count = 0xA;
                g->mode = func_0019A5C8() % 8;
                g->px = g->pb[g->slot[i].hA].x;
                g->py = g->pb[g->slot[i].hA].y;
                g->pz = g->pb[g->slot[i].hA].z;
                func_01E00BC0_b573((void *)g, (void *)&g->slot[i], 0x20, g->jit);
                g->count = 0;
            }
        }
    }
    if (g->count2 != 0) {
        g->count2--;
    }
    if (g->frame == 0x122) {
        return 1;
    }
    if (g->frame == 0x17C) {
        return 3;
    }
    if (g->frame > 0x12C && g->frame < 0x177) {
        return 6;
    }
    if (g->count2 <= 0) {
        return 8;
    }
    return 0;
}

/* shape b573:01E04A30, 74 insns: twin of b046:01E03E20: take the first free slot of the 140-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x2BB8 and 0x2BB2 and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b573_01E04A30;

typedef struct {
    u8 pad[0x250];
    u8 m[0x60];
    Slot_b573_01E04A30 s[140];
    u8 pad25B0[0x574];
    u8 r, g, b, a;
    u8 pad2B28[0x8A];
    s16 w;
    u8 pad2BB4[0x4];
    s16 v;
} Pool_b573_01E04A30;

static s32 func_01E04A30_b573(Pool_b573_01E04A30 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b573_01E04A30 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 140; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 140;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b573:01E04B60, 222 insns: b069:01E01830's sprite quad drawn as two mirrored halves at the ctx point
   (ctx+0x20), scaled 0.1, size o->h38: texture rect (1, 1, 62, 127) through the module helper (shape b003:01E00080),
   texture ctx+0x2B04; each half far-z and sent twice to the ot at ctx+0x2B2C */

typedef struct {
    f32 u, v;
} Uv_b573_01E04B60;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b573_01E04B60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b573_01E04B60 uv;
    u64 pad18;
    Xyz_b573_01E04B60 v[4];
} Pk_b573_01E04B60;

typedef struct {
    u8 pad0[0x20];
    Vec4f pt;
    u8 pad30[0x2B04 - 0x30];
    s32 tex;
    u8 pad2B08[0x2B2C - 0x2B08];
    s32 ot;
} Ctx_b573_01E04B60;

typedef struct {
    u8 pad0[0x28];
    u8 col[8];
    u8 pad30[8];
    s16 size;
} Fx_b573_01E04B60;

static void func_01E04B60_b573(Ctx_b573_01E04B60 *g, Fx_b573_01E04B60 *o, Pk_b573_01E04B60 *p) {
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 depth[4];
    Rect_b003_01E00080 r __attribute__((aligned(16)));
    f32 m[16];
    s32 rot[4];
    Uv_b573_01E04B60 uv __attribute__((aligned(8)));

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    func_00107740(&uv, o->col);
    p->uv = uv;
    r.x = 1;
    r.y = 1;
    r.w = 62;
    r.h = 127;
    func_01E00080_b573((Pk_b003_01E00080 *)p, &r, 0);
    func_00208700(p, g->tex, 1);
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = g->pt.x;
    pos.y = g->pt.y;
    pos.z = g->pt.z;
    func_00108EF0(m, &sc, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    *(f32 *)(u32)&quad[1].x = 0.0f;
    *(f32 *)(u32)&quad[3].x = 0.0f;
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0(p, g->ot, 0);
        func_002075F0(p, g->ot, 0);
    }
    func_00108CE0(quad, o->size, o->size);
    *(f32 *)(u32)&quad[1].x = 0.0f;
    *(f32 *)(u32)&quad[3].x = 0.0f;
    quad[0].x *= -1.0f;
    quad[2].x *= -1.0f;
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0(p, g->ot, 0);
        func_002075F0(p, g->ot, 0);
    }
}

/* shape b573:01E04EE0, 141 insns: draw a 0.1-scaled sprite at the given position: the material is frame 0x9B (0x14 for
   objects run by b573:01E02F90) with the object's colour and the scene texture 0x2AC (0x2B00 for those objects); objects
   of b573:01E02F90 draw one quad (depth-tested), the others repeat func_00108F90 for their count */

typedef struct {
    u8 pad0[0x2AC];
    s32 tex0;
    u8 pad2B0[0x2850];
    s32 tex1;
} Game_b573_01E04EE0;

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 c28[4];
    u8 pad2C[4];
    s16 count;
    u8 pad32[2];
    s16 frame;
    u8 pad36[2];
    s16 size;
} Obj_b573_01E04EE0;

static void func_01E04EE0_b573(Game_b573_01E04EE0 *g, Obj_b573_01E04EE0 *o, void *p, Vec4f *in) {
    extern void b573_01E02F90();
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108F90(void *, void *, void *, s32);
    f32 pos[4];
    f32 q[16];
    Vec4f v;
    Vec4f sc;
    f32 rm[4];
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    s32 ctx;
    s16 i;

    *(Vec4f *)pos = *in;
    ctx = (s32)func_00207500();
    func_00106080(rm, 0x9B, o->frame, rm);
    if (o->fn == (void *)b573_01E02F90) {
        func_00106080(rm, 0x14, o->frame, rm);
    }
    func_00109270(p, 0, 0);
    func_00107790(p, o->c28, 0);
    func_00108500(p, rm, 0);
    if (o->fn == (void *)b573_01E02F90) {
        func_00208700(p, g->tex1, 1);
    } else {
        func_00208700(p, g->tex0, 1);
    }
    func_00205C40((s32)rot);
    v.x = pos[0];
    v.y = pos[1];
    v.z = pos[2];
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00108EF0(m, &sc, rot, &v);
    func_00108CE0(q, o->size, o->size);
    if (o->fn == (void *)b573_01E02F90) {
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            if (o->fn == (void *)b573_01E02F90) {
                func_00109380(p, 0);
            }
            func_002075F0(p, ctx, (u32)depth[0]);
        }
    } else {
        for (i = 0; i < o->count; i++) {
            func_00108F90(q, p, m, ctx);
        }
    }
}

/* shape b573:01E05120, 202 insns: b531:01E00DE0's ring with two colours, turned a quarter (rot[0] + 0x4000 on a random rotation): 18 quads 20 degrees wide between radius g+0x2B3C and that + 1, each with its frame from g+0x2B74 through func_00106080 into the rect, trig table g+0x2DC4, depth-tested into g+0x2B2C */

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b573_01E05120;

typedef struct {
    u8 pad00[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[0xA];
    s16 start;
} Anim_b573_01E05120;

typedef struct {
    u8 pad00[0x88];
    s32 texture;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 hBE;
    u8 padC0[0x2B2C - 0xC0];
    s32 target;
    u8 pad2B30[0xC];
    f32 rad;
    u8 pad2B40[0x34];
    s16 frames[18];
    u8 pad2B98[0x2DC4 - 0x2B98];
    u8 trig[1];
} Obj_b573_01E05120;

static void func_01E05120_b573(Obj_b573_01E05120 *o, Anim_b573_01E05120 *an, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 v[4];
    Vec_b573_01E05120 quad[4];
    Vec_b573_01E05120 pos;
    Vec_b573_01E05120 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 rot[4];
    f32 rm[4];
    s32 k;
    s32 a;
    s16 j;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    void *p = &buf;

    *(Vec4f *)v = *in;
    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col2, 2);
    func_00108500(p, &o->rect, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = v[0];
    pos.y = v[1];
    pos.z = v[2];
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    func_00108EF0(m, &scale, rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        func_00106080(rm, 0x1E, o->frames[k], 0);
        o->rect = *(Vec4f *)rm;
        func_00108500(p, &o->rect, o->hBE);
        a = an->start + j;
        quad[2].x = o->rad * func_00108030(o->trig, a, 1);
        quad[2].z = o->rad * func_00108030(o->trig, a, 0);
        quad[0].x = (1.0f + o->rad) * func_00108030(o->trig, a, 1);
        quad[0].z = (1.0f + o->rad) * func_00108030(o->trig, a, 0);
        a = j + (an->start + 20);
        quad[3].x = o->rad * func_00108030(o->trig, a, 1);
        quad[3].z = o->rad * func_00108030(o->trig, a, 0);
        quad[1].x = (1.0f + o->rad) * func_00108030(o->trig, a, 1);
        quad[1].z = (1.0f + o->rad) * func_00108030(o->trig, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            func_002075F0(p, o->target, (u32)depth);
        }
        j += 20;
    }
}
