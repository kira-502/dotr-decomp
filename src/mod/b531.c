#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b531(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
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

static void func_01E00100_b531(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E009A0_b531(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b531:01E00DE0, 194 insns: b027:01E02590's ring of 9 quads (radius 0x38 to +20, 2 degrees each, 40 apart from 0x3A) drawn into a local packet at the point passed in */

/* OVL_WARM */
typedef struct {
    f32 x, y, z, w;
} Vec_b531_01E00DE0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b531_01E00DE0;

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
} Obj_b531_01E00DE0;

static void func_01E00DE0_b531(Obj_b531_01E00DE0 *o, Anim_b531_01E00DE0 *an, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 v[4];
    Vec_b531_01E00DE0 quad[4];
    Vec_b531_01E00DE0 pos;
    Vec_b531_01E00DE0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
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
    func_00107790(p, an->col, 0);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = v[0];
    pos.y = v[1];
    pos.z = v[2];
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

/* shape b119:01E00920, 258 insns, 4 copies: draws a flat ring of 18 quads like shape b112:01E00B60, turned by the ring's own
   rotation instead of the camera's; radii converted once. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b119_01E00920;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[8];
    Vec4f rot;
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b119_01E00920;

static void func_01E010F0_b531(Obj_b119_01E00920 *o, Ring_b119_01E00920 *s, s32 mode, Vec4f pos) {
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
    u8 pkt[0x90];
    s32 t;
    f32 ro;
    f32 ri;
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
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    ro = s->outer;
    ri = s->inner;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = ro * func_00108030(o->xD8, t, 1);
            quad[0].z = ro * func_00108030(o->xD8, t, 0);
            quad[2].x = ri * func_00108030(o->xD8, t, 1);
            quad[2].z = ri * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = ro * func_00108030(o->xD8, t, 1);
            quad[1].z = ro * func_00108030(o->xD8, t, 0);
            quad[3].x = ri * func_00108030(o->xD8, t, 1);
            quad[3].z = ri * func_00108030(o->xD8, t, 0);
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

/* shape b046:01E01A60, 283 insns, 10 copies: draws obj->count (0 = 20) sprites along a curve read from three s8
   tables (0x64 apart), each turned on three axes by the definition's angles; mode 0 = depth from the
   projection, 1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static
   function. Sibling of b003:01E00EA0 and b018:01E005A0. */

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
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 fD8[4];
} Obj_b046_01E01A60;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Def_b046_01E01A60;

typedef struct {
    union {
        struct {
            u64 x : 16;
            u64 y : 16;
            u64 z : 24;
            u64 fog : 8;
        } b;
        struct {
            u8 pad[7];
            u8 fog;
        } h;
    } xyz;
    u64 reg;
} Xyz_b046_01E01A60;

typedef struct {
    f32 u, v;
} Uv_b046_01E01A60;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b046_01E01A60 uv;
    u64 pad18;
    Xyz_b046_01E01A60 v[4];
    u64 pad60[6];
} Pk_b046_01E01A60;

typedef struct {
    u64 tag;
    Pk_b046_01E01A60 pk;
} Buf_b046_01E01A60;

static void func_01E01500_b531(Obj_b046_01E01A60 *obj, Def_b046_01E01A60 *def, s32 mode, s8 *base) {
    f32 m2[4][4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    Buf_b046_01E01A60 buf;
    Uv_b046_01E01A60 uv;
    s16 i;
    Pk_b046_01E01A60 *p;
    s16 n;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    buf.pk.uv.v = 0.0f;
    buf.pk.v[0].xyz.h.fog = 0;
    buf.pk.v[1].xyz.h.fog = 0;
    buf.pk.v[2].xyz.h.fog = 0;
    buf.pk.v[3].xyz.h.fog = 0;
    func_00107740(&uv, def->tex);
    buf.pk.uv = uv;
    func_01E00100_b531((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, obj->f88, 1);
    n = (obj->count != 0) ? obj->count : (s16)20;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, rot, &pos);
    for (i = 0; i < n; i++) {
        r = def->size;
        func_00108CE0(m2, r, r);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        func_00107070(m2, 0, f * (def->scale + h));
        f = t[def->tab + 100];
        f /= 20.0f;
        func_00107070(m2, 1, f * (def->scale + h));
        f = t[def->tab + 180];
        f /= 20.0f;
        func_00107070(m2, 2, f * (def->scale + h));
        func_00109100(m2, def->rot, 0, obj->fD8);
        func_00109100(m2, def->rot, 1, obj->fD8);
        func_00109100(m2, def->rot, 2, obj->fD8);
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].xyz.b.z = p->v[1].xyz.b.z = p->v[2].xyz.b.z = p->v[3].xyz.b.z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b531", func_01E01970_b531);

/* shape b081:01E05C10 (B081PAINT_RAIN10), 517 insns, 4 copies: b121:01E033A0 beam form with a world matrix: the
   textured beam along the module spline (b081:01E009A0), 3 sub-steps per segment, each a 2-quad cross drawn through a
   matrix from the beam rotation (0x10) at the context position; width shrinks by width/(4n) per step, alpha fades by
   col0.a/(3n); also reads the camera angle (unused); flags picks the depth (0 real, 1 far, 2 -1) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b081_01E05C10;

typedef struct {
    u8 r, g, b, a;
} Col_b081_01E05C10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b081_01E05C10;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b081_01E05C10 c;
        u64 st;
        Xyz_b081_01E05C10 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b081_01E05C10;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b081_01E05C10;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[8];
    s32 rot[4];
    u8 pad20[8];
    Col_b081_01E05C10 col0;
    Col_b081_01E05C10 col1;
    u8 pad30[8];
    s16 width;
} Beam_b081_01E05C10;

/* pts aligned: its spill slot, needed for the match */
static void func_01E01E20_b531(Ctx_b081_01E05C10 *c, Beam_b081_01E05C10 *an, Vec_b018_01E00EE0 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b081_01E05C10 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00205C40(s32 *);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 prev;
    Vec_b018_01E00EE0 q[4];
    Vec_b018_01E00EE0 pos;
    f32 depth[4];
    s32 rot[4];
    f32 m[16];
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b081_01E05C10 pkt __attribute__((aligned(8)));
    Col_b081_01E05C10 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b081_01E05C10 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    w0 = w;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 3; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = func_01E009A0_b531(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.33f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                r1 = func_01E009A0_b531(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = func_01E009A0_b531(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.33f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                r2 = func_01E009A0_b531(ctrl, 0, t);
                ab[1] = r2;
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (4.0f * n);
            for (k = 0; k < 2; k++) {
                q[0].x = ab[0].x;
                q[0].y = ab[0].y;
                q[0].z = ab[0].z;
                q[1].x = ab[0].x;
                q[1].y = ab[0].y;
                q[1].z = ab[0].z;
                q[2].x = ab[1].x;
                q[2].y = ab[1].y;
                q[2].z = ab[1].z;
                q[3].x = ab[1].x;
                q[3].y = ab[1].y;
                q[3].z = ab[1].z;
                if (k == 0) {
                    q[1].y += w1;
                    q[3].y += w;
                    q[0].y -= w1;
                    q[2].y -= w;
                } else if (k == 1) {
                    q[1].x += w1;
                    q[3].x += w;
                    q[1].z += w1 / 2.0f;
                    q[3].z += w / 2.0f;
                    q[0].x -= w1;
                    q[2].x -= w;
                    q[0].z -= w1 / 2.0f;
                    q[2].z -= w / 2.0f;
                }
                if (flags == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, func_001A23B0(depth[0]));
                    }
                } else if (flags == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                } else if (flags == 2) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, -1);
                    }
                }
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00100_b531 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b046_01E00DD0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b046_01E00DD0_unused;

typedef struct Obj_b046_01E00DD0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b046_01E00DD0;

typedef struct Xyz_b046_01E00DD0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b046_01E00DD0;

typedef struct Uv_b046_01E00DD0 {
    f32 u, v;
} Uv_b046_01E00DD0;

typedef struct Pk_b046_01E00DD0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b046_01E00DD0 uv;
    u64 pad18;
    Xyz_b046_01E00DD0 v[4];
    u64 pad60[6];
} Pk_b046_01E00DD0;

typedef struct Buf_b046_01E00DD0 {
    u64 tag;
    Pk_b046_01E00DD0 pk;
} Buf_b046_01E00DD0;


typedef struct Data_b046_01E00DD0 {
    u8 pad0[0x10];
    s32 ang[4];
    u8 pad20[8];
    Vec4f f28;
    s16 f38;
} Data_b046_01E00DD0;

static void func_01E02640_b531(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b046_01E00DD0 buf;
    Uv_b046_01E00DD0 uv;
    Pk_b046_01E00DD0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (mode == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (mode == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->f28);
    p->uv = uv;
    func_01E00100_b531((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->f38, data->f38);
    func_00109100(view, data->ang, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b531", func_01E02830_b531);

/* shape b531:01E03A30, 113 insns: a blue or purple (by kind) falling streak: frame 50 falling by 4..6, random tilt 0..0x3FFF,
   turn and sub-frame 0..3; alpha up by 10 to 0x80 for 12 frames, then down by 19 under 12, gone under -12, and down by 15 when
   the scene timer drops under 10 */

typedef struct {
    u8 pad0[0x3150];
    s32 timer;
} Scene_b531_01E03A30;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 fall;
    s32 rot0;
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b531_01E03A30;

static s32 func_01E03A30_b531(Scene_b531_01E03A30 *g, Obj_b531_01E03A30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->state == 1) {
        o->h38 = 0x32;
        base = 0;
        o->rot0 = func_0019A5C8() % 0x4000 + base;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 4;
        o->state = 2;
        o->fall = func_0019A5C8() % 3 + 4;
        o->h6 = 1;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x20, 0x20, 0x80);
        } else {
            func_001076F0(o->c0, 0x40, 0x20, 0x80);
        }
    }
    if (o->t < 0xC) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xA;
        }
    } else {
        if (o->h38 < 0xC) {
            if (o->c0[3] > 0x14) {
                o->c0[3] -= 0x13;
            } else {
                o->state = 0;
            }
        }
        if (o->h38 < -0xC) {
            o->state = 0;
        }
        if (g->timer < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    o->t++;
    o->h38 -= o->fall;
    return 0;
}

/* shape b531:01E03C00, 57 insns: on start 0x38 from the game (0x3198), colour 0x80 grey and second colour
   (0x20, 0x20, 0x80) with alpha 0, random 0x3A; alpha 0xA0 on the first tick, then fades by 0x3A and stops; the
   rotation at 0x10 advances 0x4000 each tick */

typedef struct {
    u8 pad0[0x3198];
    s16 v;
} Game_b531_01E03C00;

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b531_01E03C00;

static s32 func_01E03C00_b531(Game_b531_01E03C00 *g, Fx_b531_01E03C00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = g->v;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x20, 0x20, 0x80);
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick <= 0) {
        o->col[3] = 0xA0;
    } else if (o->col[3] > 0x3C) {
        o->col[3] -= 0x3A;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b531:01E03CF0, 124 insns: a red-white marker that waits for the camera: on start colours 0xC0 grey and 0xF0/0x20/0x20,
   a random angle; alpha 0xA0 on the first tick, then blinking 0xA0/0x80; f38 grows by 2 to 40; once the camera's depth is
   within 5 of the target point (g+0x2870 + 16*point) it copies the point to g+0x250, sets g+0x3194, fires the module's
   three effects and ends; it spins by 0x4000 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Pt_b531_01E03CF0;

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x2614];
    Pt_b531_01E03CF0 pt[1];
    u8 pad2880[0x914];
    s16 f3194;
} Game_b531_01E03CF0;

typedef struct {
    u8 pad0[0x10];
    s32 rot;
    u8 pad14[0x14];
    u8 c0[4];
    u8 c1[4];
    s16 point;
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Obj_b531_01E03CF0;

static s32 func_01E03CF0_b531(Game_b531_01E03CF0 *g, Obj_b531_01E03CF0 *o) {
    extern void b531_01E04300(void);
    extern void b531_01E05630(void);
    extern void b531_01E06890(Game_b531_01E03CF0 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001A6C60(f32);
    f32 cam[8];
    f32 d;

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0xF0, 0x20, 0x20);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->c1[3] = 0;
    }
    if (o->t <= 0) {
        o->c0[3] = 0xA0;
    } else if (o->t % 2 == 1) {
        o->c0[3] = 0xA0;
    } else {
        o->c0[3] = 0x80;
    }
    if (o->f38 < 0x28) {
        o->f38 += 2;
    }
    o->t++;
    func_001F5F90(func_001F5380(), cam);
    d = cam[2] - g->pt[o->point].z;
    if (func_001A6C60(d * d) < 5.0f) {
        g->x = g->pt[o->point].x;
        g->y = g->pt[o->point].y;
        g->z = g->pt[o->point].z;
        g->f3194 = 1;
        b531_01E06890(g, b531_01E05630, 0);
        b531_01E06890(g, b531_01E04300, 0);
        b531_01E06890(g, b531_01E04300, 0);
        o->mode = 0;
    }
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    return 0;
}

/* shape b531:01E03EE0, 262 insns: a purple (0x80/0x10/0x80) glow on scene point o->f30 (+0x2870, 16 bytes each):
   on start hA 44..60, h8 5..12, random angle; once the scene count (+0x31AC) passes 188/193/198/205/210/215 for
   points 0..5, h6 counts up to 8 and the size by 4 up to 40; ends (mode 3) when the camera's z is within 5 of the
   point's; alpha up by 0x12 below 0x80 for 12 ticks, then down by 0x3F once ending */

typedef struct {
    f32 x, y, z, w;
} V4_b531_01E03EE0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[4];
    s16 pt;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 size;
    s16 f3A;
} Fx_b531_01E03EE0;

typedef struct {
    u8 pad0[0x2870];
    V4_b531_01E03EE0 pts[1];
    u8 pad2880[0x92C];
    s16 count;
} Game_b531_01E03EE0;

static s32 func_01E03EE0_b531(Game_b531_01E03EE0 *g, Fx_b531_01E03EE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    extern f32 func_001A6C60(f32);
    f32 v[8];
    f32 d;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0x80);
        o->h6 = 0;
        o->col[3] = 0;
        o->hA = func_0019A5C8() % 17 + 44;
        o->h8 = func_0019A5C8() % 8 + 5;
        o->f3A = func_0019A5C8() % 360;
        o->size = 0;
        o->mode = 2;
    }
    if (g->count > 188 && o->pt == 0) {
        if (o->h6 < 8) {
            o->h6++;
        }
    }
    if (g->count > 193 && o->pt == 1) {
        if (o->h6 < 8) {
            o->h6++;
        }
    }
    if (g->count > 198 && o->pt == 2) {
        if (o->h6 < 8) {
            o->h6++;
        }
    }
    if (g->count > 205 && o->pt == 3) {
        if (o->h6 < 8) {
            o->h6++;
        }
    }
    if (g->count > 210 && o->pt == 4) {
        if (o->h6 < 8) {
            o->h6++;
        }
    }
    if (g->count > 215 && o->pt == 5) {
        if (o->h6 < 8) {
            o->h6++;
        }
    }
    if (g->count > 188 && o->pt == 0) {
        if (o->size < 40) {
            o->size += 4;
        }
    }
    if (g->count > 193 && o->pt == 1) {
        if (o->size < 40) {
            o->size += 4;
        }
    }
    if (g->count > 198 && o->pt == 2) {
        if (o->size < 40) {
            o->size += 4;
        }
    }
    if (g->count > 205 && o->pt == 3) {
        if (o->size < 40) {
            o->size += 4;
        }
    }
    if (g->count > 210 && o->pt == 4) {
        if (o->size < 40) {
            o->size += 4;
        }
    }
    if (g->count > 215 && o->pt == 5) {
        if (o->size < 40) {
            o->size += 4;
        }
    }
    func_001F5F90(func_001F5380(), v);
    d = v[2] - g->pts[o->pt].z;
    if (func_001A6C60(d * d) < 5.0f) {
        o->mode = 3;
    }
    if (o->tick < 12) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x12;
        }
    } else if (o->mode == 3) {
        if (o->col[3] > 0x40) {
            o->col[3] -= 0x3F;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b531:01E04300, 88 insns: a grey rising spark (b192:01E01DA0 family): frame 80, sub-frame 1, random turn and angle, rise 80..97, height 0..19,
   hold 3..9; alpha up by 0x40 while at most 0x80, then down by 10 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
    s16 step;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b531_01E04300;

static s32 func_01E04300_b531(void *arg0, Obj_b531_01E04300 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->sub = 1;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = 0;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 18 + 0x50;
        o->h8 = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 7 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b531:01E04460, 206 insns: a purple (0x40, 0x10, 0x80) ring: on start size 9, random spins, alpha 0, 0xA 44..60,
   frame 5..12, random turn and angle; alpha up by 0x1B (below 0xC0) for 12 ticks, then, once the camera is within 3
   of ctx+0x2868 in z, down by 29 until it ends; each tick writes 10 points (20 * sin/cos of angle - 10 * i) into
   ring 0x30 of the ctx (ctx+0x2D60), angle +18 */

typedef struct {
    Vec4f v[10];
} Ring_b531_01E04460;

typedef struct {
    u8 pad0[0x2868];
    f32 z;
    u8 pad286C[0x2D60 - 0x286C];
    Ring_b531_01E04460 ring[8];
    u8 pad3260[0x32B0 - 0x3260];
    u8 trig[4];
} Ctx_b531_01E04460;

typedef struct {
    u8 pad0[6];
    s16 size;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 ring;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b531_01E04460;

static s32 func_01E04460_b531(Ctx_b531_01E04460 *g, Obj_b531_01E04460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, f32 *);
    extern f32 func_001A6C60(f32);
    extern f32 func_00108030(void *, s16, s32);
    f32 c[4];
    f32 d;
    s16 i;
    s16 a = 0;

    if (o->state == 1) {
        func_001076F0(o->col, 0x40, 0x10, 0x80);
        o->size = 9;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->col[3] = 0;
        o->hA = func_0019A5C8() % 17 + 44;
        o->h8 = func_0019A5C8() % 8 + 5;
        o->hE = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->h38 = 2;
        o->state = 2;
    }
    if (o->t < 12) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x1B;
        }
    } else {
        func_001F5F90(func_001F5380(), c);
        d = c[2] - g->z;
        if (func_001A6C60(d * d) < 3.0f) {
            if (o->col[3] > 30) {
                o->col[3] -= 29;
            } else {
                o->state = 0;
            }
        }
    }
    o->t++;
    for (i = 0; i < 10; i++) {
        g->ring[o->ring].v[i].x = 20.0f * func_00108030(g->trig, o->ang + a, 0);
        g->ring[o->ring].v[i].y = 20.0f * func_00108030(g->trig, o->ang + a, 1);
        g->ring[o->ring].v[i].z = 20.0f * func_00108030(g->trig, o->ang + a, 1);
        a -= 10;
    }
    o->ang += 18;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b531:01E047A0, 136 insns: a blue ring marker (size 7 x 25) whose size follows the scene's value/3 and that turns 4 per tick: both alphas up by 48 to 0x60 for 11 ticks; random frame each tick (1 once the scene flag is set); flickers grey 0x48/0x50 while the flag is clear, 0x40 after; once the flag passes 8 alpha falls by 9 */

typedef struct {
    u8 pad0[0x3198];
    s16 val;
    u8 pad319A[0x31AA - 0x319A];
    s16 flag;
} Ctx_b531_01E047A0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0xC];
    s32 rot;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b531_01E047A0;

static s32 func_01E047A0_b531(Ctx_b531_01E047A0 *g, Fx_b531_01E047A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x30, 0x30, 0x80);
        func_001076F0(o->col2, 0x30, 0x30, 0x80);
        o->f8 = 7;
        o->fA = 25;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 11) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
        if (o->col2[3] < 0x60) {
            o->col2[3] += 0x30;
        }
    }
    o->f34 = func_0019A5C8() % 8;
    if (g->flag == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x48, 0x48, 0x48);
            func_001076F0(o->col2, 0x48, 0x48, 0x48);
        } else {
            func_001076F0(o->col, 0x50, 0x50, 0x50);
            func_001076F0(o->col2, 0x50, 0x50, 0x50);
        }
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
    }
    o->tick++;
    o->f38 = g->val / 3;
    o->rot += 4;
    if (g->flag != 0) {
        o->f34 = 1;
    }
    if (g->flag > 8) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape b531:01E049C0, 167 insns: a blue (0x30, 0x30, 0x80) pair-coloured flicker (grey 0x60 / 0xA0 every other tick), frame 0..7, both alphas up by 0x40 to 0x80 for 11 ticks, then by 0x30 to 0xF0 while the scene stage (ctx+0x31AA) runs; f38 is a third of ctx+0x3198, h18 grows 4; at stage 1 spawns four b531:01E04DB0 5 above the scene point (ctx+0x2860) and ends; from stage 11 fades by 9 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x2860 - 0x25C];
    f32 at[3];
    u8 pad286C[0x3194 - 0x286C];
    s16 slot;
    u8 pad3196[2];
    s16 h3198;
    u8 pad319A[0x31AA - 0x319A];
    s16 stage;
} Ctx_b531_01E049C0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0xC];
    s32 h18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b531_01E049C0;

static s32 func_01E049C0_b531(Ctx_b531_01E049C0 *g, Fx_b531_01E049C0 *o) {
    extern s32 b531_01E04DB0(void);
    extern void b531_01E06890(Ctx_b531_01E049C0 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x30, 0x30, 0x80);
        func_001076F0(o->col2, 0x30, 0x30, 0x80);
        o->h8 = 7;
        o->hA = 25;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 11) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (g->stage != 0) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x30;
        }
        if (o->col2[3] < 0xF0) {
            o->col2[3] += 0x30;
        }
    }
    o->f34 = func_0019A5C8() % 8;
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        func_001076F0(o->col2, 0x60, 0x60, 0x60);
    } else {
        func_001076F0(o->col, 0xA0, 0xA0, 0xA0);
        func_001076F0(o->col2, 0xA0, 0xA0, 0xA0);
    }
    o->tick++;
    o->f38 = g->h3198 / 3;
    o->h18 += 4;
    if (g->stage == 1) {
        g->pos[0] = g->at[0];
        g->pos[1] = 5.0f + g->at[1];
        g->pos[2] = g->at[2];
        g->slot = 0;
        b531_01E06890(g, b531_01E04DB0, 0);
        b531_01E06890(g, b531_01E04DB0, 0);
        b531_01E06890(g, b531_01E04DB0, 0);
        b531_01E06890(g, b531_01E04DB0, 0);
        o->mode = 0;
    }
    if (g->stage > 10) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape b531:01E04C60, 82 insns: a white flicker (alpha 0x90 / 0x80 on odd / even ticks) at a random angle, growing to 20 and rising 4 a tick; ends when it is within 3 of its target's height (the scene camera pair, func_001F5F90, vs target table ctx+0x2870) */

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
} Glow_b531_01E04C60;

typedef struct {
    f32 x, y, z, w;
} V4_b531_01E04C60;

typedef struct {
    u8 pad[0x2870];
    V4_b531_01E04C60 tgt[1];
} Game_b531_01E04C60;

static s32 func_01E04C60_b531(Game_b531_01E04C60 *g, Glow_b531_01E04C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001A6C60(f32);
    V4_b531_01E04C60 v[2];
    f32 d;

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->kind = 0;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 1) {
        o->col[3] = 0x90;
    } else if (o->tick % 2 == 1) {
        o->col[3] = 0x90;
    } else {
        o->col[3] = 0x80;
    }
    if (o->f38 < 20) {
        o->f38++;
    }
    o->tick++;
    func_001F5F90(func_001F5380(), &v);
    d = v[0].z - g->tgt[o->h30].z;
    d = func_001A6C60(d * d);
    o->w18 += 4;
    if (d < 3.0f) {
        o->mode = 0;
    }
    return 0;
}

/* shape b531:01E04DB0, 102 insns: a dark-blue rising streak: frame 80, sub-frame 1, random turn on all three axes and angle, rise
   120..199 once started from 0, width 0..19, hold 23..29; alpha up by 0x40 until the hold, then down by 10 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b531_01E04DB0;

static s32 func_01E04DB0_b531(void *arg0, Obj_b531_01E04DB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->sub = 1;
        o->rot0 = func_0019A5C8() % 360;
        o->rot1 = func_0019A5C8() % 360;
        o->rot2 = func_0019A5C8() % 360;
        func_001076F0(o->c0, 0x20, 0x20, 0x40);
        o->y = 0;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 80 + 0x78;
        o->w = func_0019A5C8() % 20;
        o->hold = func_0019A5C8() % 7 + 0x17;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b531:01E04F50, 64 insns: a dark burst: set up once (frame 90 then counting up, x turn a quarter, random angle),
   alpha up by 0xA0 for 7 frames, then down by 8 until it ends */

typedef struct {
    u8 pad0[0x18];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b531_01E04F50;

static s32 func_01E04F50_b531(void *arg0, Obj_b531_01E04F50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x5A;
        func_001076F0(o->c0, 0x10, 0x10, 0x10);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->rot = 0x4000;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0xA0;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->h38++;
    }
    o->t++;
    return 0;
}

/* shape b531:01E05050, 115 insns: two-colour glow: on start the kind (h30) is latched into h3A; kind 0 fades both
   colours' alpha in by 0x10 to 0xA0 for 15 ticks then out by 9 (blue-white 0xF0,0xF0,0x80), kind 1 by 0xD to 0xD0
   then out by 6 (white 0xFF,0xFF,0xC0); h30 = 1 once the first alpha is full; ends when the first alpha runs out. */

typedef struct {
    u8 pad00[0x28];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 t;
    u8 pad34[2];
    s16 state;
    u8 pad38[2];
    s16 kind;
} Glow_b531_01E05050;

static s32 func_01E05050_b531(s32 ctx, Glow_b531_01E05050 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->kind = o->h30;
        o->h30 = 0;
        o->state = 2;
    }
    if (o->kind == 0) {
        if (o->t < 15) {
            if (o->col[3] < 0xA0) {
                o->col[3] += 0x10;
            } else {
                o->h30 = 1;
            }
            if (o->col2[3] < 0xA0) {
                o->col2[3] += 0x10;
            }
        } else {
            if (o->col[3] > 0xA) {
                o->col[3] -= 9;
            } else {
                o->state = 0;
            }
            if (o->col2[3] > 0xA) {
                o->col2[3] -= 9;
            }
        }
        func_001076F0(o->col, 0xF0, 0xF0, 0x80);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x80);
    } else if (o->kind == 1) {
        if (o->t < 15) {
            if (o->col[3] < 0xD0) {
                o->col[3] += 0xD;
            } else {
                o->h30 = 1;
            }
            if (o->col2[3] < 0xD0) {
                o->col2[3] += 0xD;
            }
        } else {
            if (o->col[3] > 7) {
                o->col[3] -= 6;
            } else {
                o->state = 0;
            }
            if (o->col2[3] > 7) {
                o->col2[3] -= 6;
            }
        }
        func_001076F0(o->col, 0xFF, 0xFF, 0xC0);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xC0);
    }
    o->t++;
    return 0;
}

/* shape b531:01E05220, 86 insns: on start 0x38 = 100, colour 0x10 grey (alpha 0x10), second colour (0x2F, 0x2F,
   0xFF) with alpha 0, random rotation and 0x3A; the second alpha grows by 0xC0 (below 0xC0) for 20 ticks, then fades
   by 8 and stops; 0x38 grows by 15 after the first tick */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b531_01E05220;

static s32 func_01E05220_b531(s32 arg0, Fx_b531_01E05220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 100;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        func_001076F0(o->col2, 0x2F, 0x2F, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0x10;
        o->col2[3] = 0;
    }
    if (o->tick < 20) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0xC0;
        }
    } else if (o->col2[3] > 0xA) {
        o->col2[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38 += 15;
    }
    o->tick++;
    return 0;
}

/* shape b531:01E05380, 84 insns: on start 0x38 = 10, 0x34 keeps the old 0x30, random rotation 0x18, colour 0x80 grey,
   0x30 20..119, random 0x3A, speed 80..97 (0xE), 0x8 0..19, hold 1; alpha grows by 0x40 (up to 0x80) during the
   hold, then fades by 15 and stops */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b531_01E05380;

static s32 func_01E05380_b531(s32 arg0, Fx_b531_01E05380 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 10;
        o->f34 = o->f30;
        o->rot = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f30 = func_0019A5C8() % 100 + 20;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 18 + 80;
        o->f8 = func_0019A5C8() % 20;
        o->hold = 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b531:01E054D0, 86 insns: on start 0x38 = 0, colours 0x10 / 0x20 grey (alphas 0), rotation (0x4000, 0, 0),
   random 0x3A; the second alpha grows by 0xC0 (below 0xC0) for 2 ticks, then fades by 14 and stops; after the first
   tick 0x38 grows by 1/2/3 for kind 0/1/2 (0x30); 0x6 = 0x38 - 2 */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[8];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b531_01E054D0;

static s32 func_01E054D0_b531(s32 arg0, Fx_b531_01E054D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        func_001076F0(o->col2, 0x20, 0x20, 0x20);
        o->rot[0] = 0x4000;
        o->rot[1] = 0;
        o->rot[2] = 0;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col[3] = 0;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0xC0;
        }
    } else if (o->col2[3] > 0xF) {
        o->col2[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->kind == 0) {
            o->f38 += 1;
        }
        if (o->kind == 1) {
            o->f38 += 2;
        }
        if (o->kind == 2) {
            o->f38 += 3;
        }
    }
    o->f6 = o->f38 - 2;
    o->tick++;
    return 0;
}

/* shape b531:01E05630, 74 insns: a white-yellow / white-red spinning flash by kind: frame 720, random angle; full alpha
   0xA0 on the first frame, then down by 48 until it ends; random turn plus a quarter */

typedef struct {
    u8 pad0[0x10];
    s32 rot[4];
    u8 pad20[8];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b531_01E05630;

static s32 func_01E05630_b531(void *arg0, Obj_b531_01E05630 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x2D0;
        if (o->kind == 0) {
            func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c1, 0x80, 0x80, 0x20);
        } else if (o->kind == 1) {
            func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->c1, 0x80, 0x20, 0x20);
        }
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->t < 1) {
        o->c0[3] = 0xA0;
    } else if (o->c0[3] > 0x32) {
        o->c0[3] -= 0x30;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b531:01E05760, 49 insns: b718:01E03D10 family volume fader (to 0x30 after scene state 30), full volume and the end at state 2 */

typedef struct {
    u8 pad[0x3150];
    s32 state;
} Game_b531_01E05760;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 padV[0x4];
    s16 mode;
} Fade_b531_01E05760;

static s32 func_01E05760_b531(Game_b531_01E05760 *g, Fade_b531_01E05760 *o) {
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
    if (g->state == 2) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b531:01E05830, 115 insns: a grey full-screen veil (b064:01E02F10 shape): one sprite over the whole screen at the object
   alpha, sent at once; alpha up by 10 to 0x50 until frame 85, then down by 9 until it ends; a counter runs up to 30 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b531_01E05830;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b531_01E05830 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b531_01E05830;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 state;
} Obj_b531_01E05830;

static s32 func_01E05830_b531(void *arg0, Obj_b531_01E05830 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b531_01E05830 pkt __attribute__((aligned(8)));

    ((Pkt_b531_01E05830 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b531_01E05830 *)(s32)&pkt)->tag = 5;
    ((Pkt_b531_01E05830 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b531_01E05830 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x80;
    pkt.b = 0x80;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b531_01E05830 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    if (o->kind == 0) {
        pkt.v[0].s = 0.0f;
        pkt.v[0].t = 0.0f;
        pkt.v[1].s = 0.625f;
        pkt.v[1].t = 0.875f;
    } else {
        pkt.v[0].s = 0.0f;
        pkt.v[0].t = 0.0f;
        pkt.v[1].s = 0.625f;
        pkt.v[1].t = 0.875f;
    }
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (o->t < 0x55) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0xA;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->kind < 0x1E) {
        o->kind++;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b531", func_01E05A00_b531);

/* shape b531:01E06890, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x3194 and 0x318E and the two arguments; returns 1 if a
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
} Slot_b531_01E06890;

typedef struct {
    u8 pad[0x250];
    u8 m[0x60];
    Slot_b531_01E06890 s[150];
    u8 pad2830[0x924];
    u8 r, g, b, a;
    u8 pad3158[0x36];
    s16 w;
    u8 pad3190[0x4];
    s16 v;
} Pool_b531_01E06890;

static s32 func_01E06890_b531(Pool_b531_01E06890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b531_01E06890 *s = NULL;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}
