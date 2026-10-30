#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b443(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00150_b443(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

/* shape b027:01E02300, 162 insns, 8 copies: a fan of 18 quads (centre at the origin, outer edge on a circle of
   radius data->radius, 20 angle units per step) sent through the caller's packet; same family as b016:01E01190 */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02300;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b027_01E02300;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 dx, dy, dz;
    u8 pad0E[0x1A];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 radius;
    s16 step;
} Data_b027_01E02300;

static void func_01E00590_b443(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b027_01E02300 quad[4];
    Vec_b027_01E02300 pos;
    Vec_b027_01E02300 scale;
    f32 matrix[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 j;
    s32 a;
    f32 fx;
    f32 fy;
    f32 fz;

    j = 0;
    func_00107990(pkt, data->mode0, 1);
    func_00107990(pkt, data->mode1, 2);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = data->dx;
    fy = data->dy;
    fz = data->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = data->x + fx;
    pos.y = data->y + fy;
    pos.z = data->z + fz;
    func_00108EF0(matrix, &scale, rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        a = data->step + j;
        quad[2].x = data->radius * func_00108030(obj->table, a, 1);
        quad[2].z = data->radius * func_00108030(obj->table, a, 0);
        a = j + (data->step + 20);
        quad[3].x = data->radius * func_00108030(obj->table, a, 1);
        quad[3].z = data->radius * func_00108030(obj->table, a, 0);
        if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
            func_00109380(pkt, 1);
            func_002075F0(pkt, obj->texture, 0);
        }
        j += 20;
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

static void func_01E00820_b443(Obj_b112_01E00B60 *o, Ring_b112_01E00B60 *s, s32 mode, Vec4f pos) {
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02590;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b027_01E02590;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b027_01E02590;

static void func_01E00CC0_b443(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b027_01E02590 quad[4];
    Vec_b027_01E02590 pos;
    Vec_b027_01E02590 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 0);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + 20) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + 20) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 2);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + 20) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + 20) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 40;
    }
}

/* OVL_WARM */

/* shape b064:01E00C10, 200 insns: variant of b027:01E02590 (ring of quads around a point): two colour sets,
   ring width from the anim (s16 at 6) instead of 20, 18 segments 20 apart */

typedef struct {
    f32 x, y, z, w;
} Vec_b064_01E00C10;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b064_01E00C10;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b064_01E00C10;

static void func_01E00FC0_b443(Obj_b064_01E00C10 *o, Anim_b064_01E00C10 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b064_01E00C10 quad[4];
    Vec_b064_01E00C10 pos;
    Vec_b064_01E00C10 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col + 4, 2);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 20);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 20;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b443", func_01E012E0_b443);

INCLUDE_ASM("asm/nonmatchings/mod/b443", func_01E01B00_b443);

INCLUDE_ASM("asm/nonmatchings/mod/b443", func_01E01EA0_b443);

/* shape b443:01E02330 (B443_W_S), 387 insns, 1 copy (-O3,p): advances the effect timer, places emitters on model
   joints, and spawns the ring and trail layers at their scene frames */

typedef struct Scene_b443_01E02330 {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x290 - 0x260];
    Vec4f a;
    Vec4f b;
    u8 pad2B0[0x28D0 - 0x2B0];
    Vec4f saved;
    u8 pad28E0[0x2DF4 - 0x28E0];
    u8 col[4];
    u8 pad2DF8[0x2E24 - 0x2DF8];
    s16 ja, jb, jc, jd;
    u8 pad2E2C[0x2E3E - 0x2E2C];
    s16 side;
    s16 unused;
    s16 t;
} Scene_b443_01E02330;

#pragma optimization_level 3

static void func_01E02330_b443(Scene_b443_01E02330 *g) {
    extern void b443_01E04CD0();
    extern void b443_01E037A0(), b443_01E040B0(), b443_01E03C80(), b443_01E02C40();
    extern void b443_01E03DA0(), b443_01E02EA0(), b443_01E030C0(), b443_01E033B0();
    extern void b443_01E04150();
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0x7E) {
        b443_01E04CD0(g, b443_01E037A0, 0);
    }
    if (g->t == 1) {
        b443_01E04CD0(g, b443_01E040B0, 0);
    }
    if (g->t == 0x4C) {
        i = 0;
        do {
            g->side = i;
            b443_01E04CD0(g, b443_01E03C80, 0);
            i += 1;
        } while (i < 6);
    }
    if ((g->t >= 0x4C) && (g->t < 0x50)) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        i = 0;
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        do {
            b443_01E04CD0(g, b443_01E02C40, 0);
            i += 1;
        } while (i < 0xC);
    }
    if (g->t == 0x89) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b443_01E04CD0(g, b443_01E03DA0, 0);
        i = 0;
        do {
            b443_01E04CD0(g, b443_01E02EA0, 0);
            i += 1;
        } while (i < 0xC);
        i = 0;
        do {
            b443_01E04CD0(g, b443_01E030C0, 0);
            i += 1;
        } while (i < 0xC);
        i = 0;
        do {
            b443_01E04CD0(g, b443_01E033B0, 0);
            i += 1;
        } while (i < 0xA);
    }
    if ((g->t > 93) && (g->t < 0x82)) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
    }
    if (g->t == 0x33) {
        func_001F5620(func_001F53A0(), g->jb, (&g->saved));
    }
    if ((g->t > 51) && (g->t < 0x41)) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        i = 0;
        do {
            i += 1;
            g->pos.x = g->saved.x;
            g->pos.y = g->saved.y;
            g->pos.z = g->saved.z;
        } while (i < 6);
    }
    if (g->t == 1) {
        func_001F5F90(func_001F53A0(), &g->a);
        func_001F5F90(func_001F53A0(), &g->b);
    }
    if ((g->t > 111) && (g->t < 0xC3)) {
        g->a.z = (g->a.z - 2.4f);
        g->pos.x = g->a.x;
        g->pos.y = (g->a.y - 10.0f);
        g->pos.z = (40.0f + g->a.z);
        g->side = 0;
    }
    if (g->t == 0x50) {
        func_001F5620(func_001F53A0(), g->jc, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
        func_001F5620(func_001F53A0(), g->jd, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
    }
    if ((g->t > 170) && (g->t < 0xE1)) {
        g->b.z = (g->b.z - 3.8f);
        g->pos.x = g->b.x;
        g->pos.y = (g->b.y - 10.0f);
        g->pos.z = (40.0f + g->b.z);
        g->side = 1;
    }
    if ((g->t >= 0x70) && (g->t < 0xBF)) {
        g->pos.x = g->a.x;
        g->pos.y = (g->a.y - 10.0f);
        g->pos.z = (40.0f + g->a.z);
        g->side = 0;
    }
    if ((g->t >= 0xA9) && (g->t < 0xDD)) {
        g->pos.x = g->b.x;
        g->pos.y = (g->b.y - 10.0f);
        g->pos.z = (40.0f + g->b.z);
        g->side = 1;
    }
    if (g->t == 1) {
        b443_01E04CD0(g, b443_01E04150, 0);
    }
    if ((g->t == 0x30) || (g->t == 0x31) || (g->t == 0x32) || (g->t == 0x33)) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
    }
    if ((g->t == 0x33) || (g->t == 0x34) || (g->t == 0x35) || (g->t == 0x36)) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 1;
    }
}

#pragma optimization_level reset

/* shape b443:01E02940, 134 insns: b019:01E01F60 with its sine table at ctx+0x2F44 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x2F44];
    u8 tab[1];
} Mgr_b443_01E02940;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b443_01E02940;

static s32 func_01E02940_b443(Mgr_b443_01E02940 *m, Fx_b443_01E02940 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E02B60_b443(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

/* shape b443:01E02C40, 149 insns: b207:01E029A0's falling spark, frame 0..3, fall 6..8, flickering blue, riding scene joint 0x2E24 */

typedef struct {
    u8 pad0000[0x2DF0];
    s32 w3B00;
    u8 pad2DF4[0x30];
    s16 joint;
} Mgr_b443_01E02C40;

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    s32 w10;
    s32 w14;
    u8 pad18[0x10];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b443_01E02C40;

static s32 func_01E02C40_b443(Mgr_b443_01E02C40 *m, Obj_b443_01E02C40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    s32 base;
    Vec4f v;

    if (o->h36 == 1) {
        o->h38 = 70;
        base = 0;
        o->w10 = func_0019A5C8() % 0x4000 + base;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = func_0019A5C8() % 4;
        o->h36 = 2;
        o->hE = func_0019A5C8() % 3 + 6;
        o->h6 = 1;
        if (o->h30 == 0) {
            func_001076F0(o->c28, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c28, 0, 0x80, 0x80);
        }
    }
    if (o->h32 < 2) {
        if (o->c28[3] < 0xA0) {
            o->c28[3] += 0x50;
        }
    } else {
        if (o->h38 < 12) {
            if (o->c28[3] > 20) {
                o->c28[3] -= 19;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h38 < -12) {
            o->h36 = 0;
        }
        if (m->w3B00 < 10) {
            if (o->c28[3] > 16) {
                o->c28[3] -= 15;
            } else {
                o->h36 = 0;
            }
        }
    }
    if (o->h32 % 2 == 1) {
        func_001076F0(o->c28, 0x40, 0x40, 0x80);
    } else {
        func_001076F0(o->c28, 0x80, 0x80, 0xB0);
    }
    func_001F5620(func_001F53A0(), m->joint, &v);
    o->x = func_001A22C0(v.x);
    o->y = func_001A22C0(v.y);
    o->z = func_001A22C0(v.z);
    o->h32++;
    o->h38 -= o->hE;
    return 0;
}

/* shape b443:01E02EA0, 133 insns: a blue spark that rises and falls: random tilt 0..0x3FFF and spin, frame 0..6, rise
   2..3, f6 1; alpha jumps by 0x50 (below 0xA0) for two ticks; after height 80 it fades by 0x13, below -12 it ends,
   and it fades by 15 once the scene timer drops below 10; colour stays blue */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 rise;
    s32 tilt;
    s32 spin;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 h;
} Fx_b443_01E02EA0;

typedef struct {
    u8 pad0[0x2DF0];
    s32 timer;
} Scene_b443_01E02EA0;

static s32 func_01E02EA0_b443(Scene_b443_01E02EA0 *g, Fx_b443_01E02EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->mode == 1) {
        o->h = 0;
        base = 0;
        o->tilt = func_0019A5C8() % 0x4000 + base;
        o->spin = func_0019A5C8() % 65535;
        o->frame = func_0019A5C8() % 7;
        o->mode = 2;
        o->rise = func_0019A5C8() % 2 + 2;
        o->h6 = 1;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        } else {
            func_001076F0(o->col, 0x20, 0x20, 0x80);
        }
    }
    if (o->t < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->h > 0x50) {
            if (o->col[3] > 0x14) {
                o->col[3] -= 0x13;
            } else {
                o->mode = 0;
            }
        }
        if (o->h < -0xC) {
            o->mode = 0;
        }
        if (g->timer < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x60);
    } else {
        func_001076F0(o->col, 0x20, 0x20, 0x60);
    }
    o->t++;
    o->h += o->rise;
    return 0;
}

/* shape b443:01E030C0, 134 insns: b443:01E02EA0 family rising spark (orange or cyan by kind, tilt 0x2000..0x5FFF, spin -0x2000..0x1FFF, frame 0..6, rising 2..3): alpha up by 32 to 0x40 for 2 ticks; past height 40 it fades by 19, and by 15 once the scene timer is under 10; colour flashes blue/grey every tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 rise;
    u8 padA[6];
    s32 tilt;
    s32 spin;
    u8 pad18[0x10];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 h;
} Fx_b443_01E030C0;

typedef struct {
    u8 pad0[0x2DF0];
    s32 timer;
} Scene_b443_01E030C0;

static s32 func_01E030C0_b443(Scene_b443_01E030C0 *g, Fx_b443_01E030C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h = 0;
        o->tilt = func_0019A5C8() % 0x4000 + 0x2000;
        o->spin = func_0019A5C8() % 0x4000 - 0x2000;
        o->frame = func_0019A5C8() % 7;
        o->mode = 2;
        o->rise = func_0019A5C8() % 2 + 2;
        o->h6 = 10;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->col, 0, 0x80, 0x80);
        }
        func_001076F0(o->col2, 8, 8, 0x80);
    }
    if (o->t < 2) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->h > 40) {
            if (o->col[3] > 0x14) {
                o->col[3] -= 0x13;
            } else {
                o->mode = 0;
            }
        }
        if (g->timer < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x60);
    }
    o->t++;
    o->h += o->rise;
    return 0;
}

typedef struct {
    u8 pad00[0x28];
    u8 col0[4];
    u8 col1[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b207_01E03000;

static s32 func_01E032E0_b443(s32 unused, Obj_b207_01E03000 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 60;
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0xC0, 0xC0, 0);
        o->h3A = o->h30;
        o->h36 = 2;
        o->col1[3] = 0;
    }
    if (o->h32 <= 0) {
        o->col0[3] += 0x50;
    } else {
        if (o->col0[3] > 10) {
            o->col0[3] -= 9;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    if (o->h38 < 0) {
        o->h38 -= 2;
    }
    return 0;
}

/* shape b443:01E033B0, 170 insns: b443:01E030C0 variant: three random turns, w1C -4, frame 2, rise 2..3, h6 4, a random
   angle; orange or grey colours and a red second colour; both alphas up by 32 to 0x40 for 2 ticks, both fade by 7 once
   above 30 (and the first by 15 near the scene's end); then it is painted blue (0x20/0x20/0x80) and turns by -8 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 rise;
    u8 padA[6];
    s32 tilt;
    s32 spin;
    s32 w18;
    s32 w1C;
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 h;
    s16 ang;
} Fx_b443_01E033B0;

typedef struct {
    u8 pad0[0x2DF0];
    s32 timer;
} Scene_b443_01E033B0;

static s32 func_01E033B0_b443(Scene_b443_01E033B0 *g, Fx_b443_01E033B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h = 0;
        o->tilt = func_0019A5C8() % 0x4000 + 0x2000;
        o->w18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->spin = func_0019A5C8() % 0x4000 - 0x2000;
        o->w1C = -4;
        o->frame = 2;
        o->mode = 2;
        o->rise = func_0019A5C8() % 2 + 2;
        o->h6 = 4;
        o->ang = func_0019A5C8() % 360;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->col, 0x80, 0x80, 8);
        }
        func_001076F0(o->col2, 0x80, 8, 8);
    }
    if (o->t < 2) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x20;
        }
        if (o->col2[3] < 0x40) {
            o->col2[3] += 0x20;
        }
    } else {
        if (o->h > 30) {
            if (o->col[3] > 8) {
                o->col[3] -= 7;
            } else {
                o->mode = 0;
            }
            if (o->col2[3] > 8) {
                o->col2[3] -= 7;
            }
        }
        if (g->timer < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x60);
    }
    func_001076F0(o->col, 0x20, 0x20, 0x80);
    func_001076F0(o->col2, 0x20, 0x20, 0x80);
    o->t++;
    o->h += o->rise;
    o->ang -= 8;
    return 0;
}

/* shape b443:01E03660, 77 insns: a dark arc (size 20) facing left or right of the scene camera (func_001F6160; sign of its angle / 180): in by 64 up to 0x80 for 2 ticks, then out by 5 and ends; sweeps 5 degrees a tick from 90 */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
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
} Glow_b443_01E03660;

static s32 func_01E03660_b443(s32 arg0, Glow_b443_01E03660 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_001A22C0(f32);
    struct {
        s32 x, y, z, w;
    } v;

    func_001076F0(o->col, 0x20, 0x20, 0x20);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), &v);
        if (func_001A22C0((f32)v.y / 180.0f) != 0) {
            o->w10 = -0x4000;
        } else {
            o->w10 = 0xFFFF4000;
        }
        o->w14 = 0;
        o->w18 = 0x3800;
        o->kind = 0;
        o->h30 = 90;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->f38 = 20;
    o->tick++;
    o->h30 += 5;
    return 0;
}

/* shape b443:01E037A0, 224 insns: eight curling blue tendrils of 10 points (ctx+0x28E0, 0xA0 apart): on start every
   point sits on scene joint 0x2E24, frame 9, size 5..12 x 44..60; alpha 0xC0 for 11 ticks, then down by 35; each tick
   the module's b443:01E00080 shifts each tendril from the joint, then every point curls by 3 x (sin a - cos b, cos a -
   sin b) with a = 8 k and b = 90 + 8 k, plus 2 x the tendril's own direction (40 j) */

typedef struct {
    Vec4f pt[10];
} Tendril_b443_01E037A0;

typedef struct {
    u8 pad0[0x28E0];
    Tendril_b443_01E037A0 tr[8];
    u8 pad2DE0[0x2E24 - 0x2DE0];
    s16 joint;
    u8 pad2E26[0x2F44 - 0x2E26];
    u8 trig[1];
} Ctx_b443_01E037A0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 h8;
    s16 hA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 h34;
    s16 mode;
    s16 h38;
    s16 ang;
} Fx_b443_01E037A0;

static s32 func_01E037A0_b443(Ctx_b443_01E037A0 *g, Fx_b443_01E037A0 *o) {
    extern void b443_01E00080(Vec4f *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f v;
    s32 n;
    s16 i;
    s16 k;
    s16 c;
    s32 a;
    Vec4f *p;
    f32 d;
    s32 b;

    c = 0;
    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0xF0);
        for (i = 0; i < 8; i++) {
            p = g->tr[i].pt;
            func_001F5620(func_001F53A0(), g->joint, &v);
            for (n = 0; n < 9; n++) {
                p->x = v.x;
                p->y = v.y;
                p->z = v.z;
                p++;
            }
        }
        o->frame = 9;
        o->col[3] = 0;
        o->hA = func_0019A5C8() % 17 + 44;
        o->h8 = func_0019A5C8() % 8 + 5;
        o->h34 = 0;
        o->ang = func_0019A5C8() % 360;
        o->h38 = 1;
        o->mode = 2;
    }
    if (o->tick < 11) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 36) {
        o->col[3] -= 35;
    } else {
        o->mode = 0;
    }
    for (i = 0; i < 8; i++) {
        b443_01E00080(&g->tr[i].pt[9], 10, g->joint);
    }
    for (k = 0; k < 8; k++) {
        b = 90;
        for (i = 0, a = 0; i < 10; i++) {
            d = 3.0f * func_00108030(g->trig, a, 0);
            d -= 3.0f * func_00108030(g->trig, b, 1);
            g->tr[k].pt[i].x += d;
            d = 3.0f * func_00108030(g->trig, a, 1);
            d -= 3.0f * func_00108030(g->trig, b, 0);
            g->tr[k].pt[i].y += d;
            g->tr[k].pt[i].x += 2.0f * func_00108030(g->trig, c, 1);
            g->tr[k].pt[i].y += 2.0f * func_00108030(g->trig, c, 0);
            a += 8;
            b += 8;
        }
        c += 40;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E03430, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x60, 0x60, 0x60) and fields;
   alpha 0x80 for the first 0x140 ticks, then fade out by 9 and stop */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b207_01E03430;

static s32 func_01E03B20_b443(s32 arg0, Glow_b207_01E03430 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E034E0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x20, 0x20, 0x20) and fields;
   alpha 0x80 for the first 0x140 ticks, then fade out by 9 and stop */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b207_01E034E0;

static s32 func_01E03BD0_b443(s32 arg0, Glow_b207_01E034E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b443:01E03C80, 69 insns: a grey-blue blinker: set up once (frame 60, x turn a quarter, angle from its h30); alpha
   rises by 4 for 18 frames, then blinks 0x40 / 0x50 by frame parity; ends after 0xD2 frames or when the game timer hits 0x8A */

typedef struct {
    u8 pad0[0x2E42];
    s16 timer;
} Game_b443_01E03C80;

typedef struct {
    u8 pad0[0x18];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 c1[4];
    s16 h30;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b443_01E03C80;

static s32 func_01E03C80_b443(Game_b443_01E03C80 *g, Obj_b443_01E03C80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x3C;
        func_001076F0(o->c0, 0x70, 0x70, 0x70);
        func_001076F0(o->c1, 0x10, 0x10, 0xC0);
        o->rot = 0x4000;
        o->ang = o->h30;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x12) {
        o->c0[3] = o->c0[3] + 4;
    } else if (o->t % 2 == 1) {
        o->c0[3] = 0x40;
    } else {
        o->c0[3] = 0x50;
    }
    o->t++;
    if (o->t > 0xD2) {
        o->state = 0;
    }
    if (g->timer == 0x8A) {
        o->state = 0;
    }
    return 0;
}

/* shape b443:01E03DA0, 55 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
   for the first 2 ticks, then fades out by 10 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b443_01E03DA0;

static s32 func_01E03DA0_b443(s32 arg0, Flash_b443_01E03DA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x12C;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0x30, 0x30, 0xF0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b443:01E03E80, 90 insns: a scene light pulse: sets the scene light (white, range 70, at the object's point), raises its
   strength by 0.2 to 1, then lowers it by 0.1 until it ends; applies the light while live (none once ended) and ends when the
   scene state is 1 */

typedef struct {
    u8 pad0[0x2890];
    s32 l0[4];
    f32 pos[3];
    u8 pad28AC[4];
    f32 f28B0;
    f32 range;
    f32 power;
    u8 pad28BC[0x534];
    s32 state;
} Scene_b443_01E03E80;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b443_01E03E80;

static s32 func_01E03E80_b443(Scene_b443_01E03E80 *g, Obj_b443_01E03E80 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 0;
        g->l0[1] = 0;
        g->l0[2] = 0;
        g->l0[3] = 0;
        g->f28B0 = 0.0f;
        g->range = 70.0f;
        g->power = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->live = 2;
        o->down = 0;
    }
    if (o->down == 0) {
        if (g->power < 1.0f) {
            g->power += 0.2f;
        } else {
            o->down = 1;
        }
    } else if (!(g->power <= 0.1f)) {
        g->power -= 0.1f;
    } else {
        o->live = 0;
    }
    if (o->live == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(g->l0);
    }
    if (g->state == 1) {
        o->live = 0;
    }
    return 0;
}

/* shape b443:01E03FF0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2DF0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2DF0];
    s32 state;
} Game_b443_01E03FF0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b443_01E03FF0;

static s32 func_01E03FF0_b443(Game_b443_01E03FF0 *g, Fade_b443_01E03FF0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b443:01E040B0, 38 insns: func_001F7170(3, 0, &a, &b, 0) with copies of the module's floats at 0x01E04E00 and
   0x01E04E08; mode 1 becomes 2; the effect stops once its tick (0x32) reaches 0x23; return 0 */

typedef struct {
    f32 v;
} F_b443_01E040B0;

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b443_01E040B0;

extern F_b443_01E040B0 D_01E04E00_b443;
extern F_b443_01E040B0 D_01E04E08_b443;

static s32 func_01E040B0_b443(s32 arg0, Fx_b443_01E040B0 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b443_01E040B0 a;
    F_b443_01E040B0 b;

    a = D_01E04E00_b443;
    b = D_01E04E08_b443;
    if (o->mode == 1) {
        o->mode = 2;
    }
    func_001F7170(3, 0, &a, &b, 0);
    if (o->tick >= 0x23) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E04150_b443(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b443", func_01E04160_b443);

/* shape b443:01E04CD0, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2E3E and the two arguments; returns 1 if a
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
    u8 pad38[0x8];
} Slot_b443_01E04CD0;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b443_01E04CD0 s[150];
    u8 pad2870[0x584];
    u8 r, g, b, a;
    u8 pad2DF8[0x46];
    s16 v;
} Pool_b443_01E04CD0;

static s32 func_01E04CD0_b443(Pool_b443_01E04CD0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b443_01E04CD0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
