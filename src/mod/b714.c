#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b714(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00150_b714(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b045:01E005A0, 118 insns, 7 copies: one camera-facing sprite at the object position plus offset / 10,
   scaled by obj->size: the single-sprite member of the b018:01E00920 family. Calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E005A0;

static void func_01E005A0_b714(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E005A0 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00150_b714((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    r = obj->size;
    func_00108CE0(m, r, r);
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
        func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E005A0;

static void func_01E00780_b714(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E005A0 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00150_b714((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = (*(s16 *)(self + 0xB8) != 0) ? *(s16 *)(self + 0xB8) : (s16)20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E00920;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E00920 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E00920;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    u8 padA[6];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E00920;

static void func_01E00B00_b714(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E00920 uv;
    s16 i;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00150_b714((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        m[1] = 0.0f;
        m[5] = 0.0f;
        m[0] = 1.0f;
        m[4] = -1.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E00E30_b714(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;
    f32 fx;
    f32 fy;
    f32 fz;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E010C0_b714(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* OVL_WARM */

/* shape b018:01E01320: curved beam along func_01E010C0_b714 spline points. Needs func_01E010C0_b714 in the same file and
   static: the original keeps $a0 (the returned Vec buffer) across each call. */

typedef struct {
    u8 r, g, b, a;
} Col_b018_01E01320;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b018_01E01320 col;
    u8 pad2C[0xC];
    s16 width;
} Beam_b018_01E01320;

typedef struct {
    u8 b[0x90];
} Pkt_b018_01E01320;

static void func_01E01500_b714(s32 unused, Beam_b018_01E01320 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b018_01E01320 pkt __attribute__((aligned(8)));
    Col_b018_01E01320 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b018_01E01320 *p;
    s32 target;
    f32 t;
    f32 w;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    func_001094F0(p);
    func_00107990(p, &an->col, 0);
    func_001092E0(p, 0);
    func_001094F0(p);
    col = an->col;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E010C0_b714(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E010C0_b714(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E010C0_b714(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E010C0_b714(ctrl, 0, t);
                ab[1] = r2;
            }
            func_00107990(p, &col, 1);
            x = col.a - (s16)(an->col.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107990(p, &col, 2);
            for (k = 0; k < 4; k++) {
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
                    q[0].z += w;
                    q[2].z += w;
                } else if (k == 1) {
                    q[0].z -= w;
                    q[2].z -= w;
                } else if (k == 2) {
                    q[0].x += w;
                    q[2].x += w;
                } else if (k == 3) {
                    q[0].x -= w;
                    q[2].x -= w;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    func_002075F0(p, target, (u32)depth);
                }
            }
        }
    }
}

/* shape b018:01E01760 (KPOINT_RAIN_1_1), 281 insns, 7 copies: KPOINT_RAIN_1_1: draws a ribbon between two point
   trails (n points each) as 4 quads per segment along the module's spline b018:01E00EE0, alpha fading along the
   ribbon */

typedef struct Col_b018_01E01760 {
    u8 r, g, b, a;
} Col_b018_01E01760;

typedef struct Obj_b018_01E01760 {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b018_01E01760 col;
} Obj_b018_01E01760;

static void func_01E01940_b714(s32 arg0, Obj_b018_01E01760 *obj, Vec_b018_01E00EE0 *pa0, Vec_b018_01E00EE0 *pb0) {
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 qa[2];
    Vec_b018_01E00EE0 qb[2];
    Vec_b018_01E00EE0 a[4];
    Vec_b018_01E00EE0 b[4];
    Vec_b018_01E00EE0 t0;
    Vec_b018_01E00EE0 t1;
    Vec_b018_01E00EE0 t2;
    Vec_b018_01E00EE0 t3;
    u8 pk[0x90] __attribute__((aligned(8)));
    Col_b018_01E01760 col;
    s16 n;
    f32 t;
    s32 i;
    s32 j;
    u8 *p;
    s32 dst;
    Vec_b018_01E00EE0 *pa;
    Vec_b018_01E00EE0 *pb;

    dst = (s32)func_00207500();
    p = pk;
    n = obj->n;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = obj->col;
    a[0] = pa0[0];
    a[1] = pa0[0];
    a[2] = pa0[1];
    a[3] = pa0[2];
    b[0] = pb0[0];
    b[1] = pb0[0];
    b[2] = pb0[1];
    b[3] = pb0[2];
    for (i = 0; i < n - 1; i++) {
        func_00107990(p, &col, 1);
        col.a -= obj->col.a / n;
        func_00107990(p, &col, 2);
        t = 0.0f;
        pa = pa0 + (i - 1);
        pb = pb0 + (i - 1);
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                qa[0] = func_01E010C0_b714(pa, 0, t);
                qb[0] = func_01E010C0_b714(pb, 0, t);
                t += 0.25f;
                t0 = func_01E010C0_b714(pa, 0, t);
                qa[1] = t0;
                t1 = func_01E010C0_b714(pb, 0, t);
                qb[1] = t1;
            } else {
                qa[0] = func_01E010C0_b714(a, 0, t);
                qb[0] = func_01E010C0_b714(b, 0, t);
                t += 0.25f;
                t2 = func_01E010C0_b714(a, 0, t);
                qa[1] = t2;
                t3 = func_01E010C0_b714(b, 0, t);
                qb[1] = t3;
            }
            quad[0].x = qa[0].x;
            quad[0].y = qa[0].y;
            quad[0].z = qa[0].z;
            quad[1].x = qa[1].x;
            quad[1].y = qa[1].y;
            quad[1].z = qa[1].z;
            quad[2].x = qb[0].x;
            quad[2].y = qb[0].y;
            quad[2].z = qb[0].z;
            quad[3].x = qb[1].x;
            quad[3].y = qb[1].y;
            quad[3].z = qb[1].z;
            if (func_00205630((s32)quad, 0x70000000, 0, (s32)p, depth) != 0) {
                func_002075F0((s32)p, dst, 0);
            }
        }
    }
}

/* shape b714:01E01DB0, 339 insns: the module's spawn step: scene colour red, ticks the timer; tick 51 keeps joint
   0x3B8A's position, ticks 52..64 copy it to the spawn point (six times over); ticks 1 and 117 six b714:01E02300 by
   index; every third tick before 106 a b714:01E02450 at one of six random joints; ticks 44/98 and 19/71 six
   b714:01E02E50 2 below joint 0x3B94; tick 1 b714:01E03230; tick 106 three b714:01E02DA0 and three b714:01E02840;
   tick 111 at joint 0x3B88 eight b714:01E02C30, eight b714:01E02AA0, thirty b714:01E028F0, a b714:01E02760 and a
   b714:01E02FF0 */

typedef struct {
    u8 pad0[0x2D0];
    f32 px, py, pz;
    u8 pad2DC[0x36C0 - 0x2DC];
    f32 kx, ky, kz;
    u8 pad36CC[0x3B44 - 0x36CC];
    u8 rgba[4];
    u8 pad3B48[0x3B88 - 0x3B48];
    s16 joints[6];
    s16 j94;
    u8 pad3B96[0x3B9A - 0x3B96];
    s16 idx;
    u8 pad3B9C[2];
    s16 t;
} Scene_b714_01E01DB0;

static s32 func_01E02300_b714();
static s32 func_01E02450_b714();
static s32 func_01E02760_b714();
static s32 func_01E02840_b714();
static s32 func_01E028F0_b714();
static s32 func_01E02AA0_b714();
static s32 func_01E02C30_b714();
static s32 func_01E02DA0_b714();
static s32 func_01E02E50_b714();
static s32 func_01E02FF0_b714();
static s32 func_01E03230_b714();
static s32 func_01E040B0_b714();

static void func_01E01DB0_b714(Scene_b714_01E01DB0 *s) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 p[4];
    f32 cam[4];
    s32 i;
    s16 k;

    s->rgba[0] = 0x80;
    s->rgba[1] = 0;
    s->rgba[2] = 0;
    s->rgba[3] = 0;
    s->t++;
    if (s->t == 0x33) {
        func_001F5620(func_001F53A0(), s->joints[1], &s->kx);
    }
    if (s->t > 0x33 && s->t <= 0x40) {
        func_001F5620(func_001F53A0(), s->joints[1], p);
        for (i = 0; i < 6; i++) {
            s->px = s->kx;
            s->py = s->ky;
            s->pz = s->kz;
        }
    }
    if (s->t == 1 || s->t == 0x75) {
        s->idx = 0;
        func_01E040B0_b714(s, func_01E02300_b714, 0);
        s->idx = 1;
        func_01E040B0_b714(s, func_01E02300_b714, 0);
        s->idx = 2;
        func_01E040B0_b714(s, func_01E02300_b714, 0);
        s->idx = 3;
        func_01E040B0_b714(s, func_01E02300_b714, 0);
        s->idx = 4;
        func_01E040B0_b714(s, func_01E02300_b714, 0);
        s->idx = 5;
        func_01E040B0_b714(s, func_01E02300_b714, 0);
    }
    if (s->t % 3 == 1 && s->t < 0x6A) {
        k = func_0019A5C8() % 6;
        func_001F5620(func_001F53A0(), s->joints[k], p);
        s->px = p[0];
        s->py = p[1];
        s->pz = p[2];
        func_01E040B0_b714(s, func_01E02450_b714, 0);
    }
    if (s->t == 0x2C || s->t == 0x62) {
        func_001F5620(func_001F53A0(), s->j94, p);
        for (i = 0; i < 6; i++) {
            s->px = p[0];
            s->py = p[1] - 2.0f;
            s->pz = p[2];
            func_01E040B0_b714(s, func_01E02E50_b714, 0);
        }
    }
    if (s->t == 0x13 || s->t == 0x47) {
        func_001F5620(func_001F53A0(), s->j94, p);
        for (i = 0; i < 6; i++) {
            s->px = p[0];
            s->py = p[1] - 2.0f;
            s->pz = p[2];
            func_01E040B0_b714(s, func_01E02E50_b714, 0);
        }
    }
    if (s->t == 1) {
        func_01E040B0_b714(s, func_01E03230_b714, 0);
    }
    if (s->t == 0x6A) {
        s->idx = 0;
        func_01E040B0_b714(s, func_01E02DA0_b714, 0);
        s->idx = 1;
        func_01E040B0_b714(s, func_01E02DA0_b714, 0);
        s->idx = 2;
        func_01E040B0_b714(s, func_01E02DA0_b714, 0);
        s->idx = 0;
        func_01E040B0_b714(s, func_01E02840_b714, 0);
        s->idx = 1;
        func_01E040B0_b714(s, func_01E02840_b714, 0);
        s->idx = 2;
        func_01E040B0_b714(s, func_01E02840_b714, 0);
    }
    if (s->t == 0x6F) {
        func_001F5620(func_001F53A0(), s->joints[0], p);
        func_001F5F90(func_001F5380(), cam);
        s->px = p[0];
        s->py = p[1];
        s->pz = p[2];
        s->idx = 1;
        for (i = 0; i < 8; i++) {
            func_01E040B0_b714(s, func_01E02C30_b714, 0);
        }
    }
    if (s->t == 0x6F) {
        func_001F5620(func_001F53A0(), s->joints[0], p);
        s->px = p[0];
        s->py = p[1];
        s->pz = p[2];
        s->idx = 1;
        for (i = 0; i < 8; i++) {
            func_01E040B0_b714(s, func_01E02AA0_b714, 0);
        }
        for (i = 0; i < 30; i++) {
            func_01E040B0_b714(s, func_01E028F0_b714, 0);
        }
        func_01E040B0_b714(s, func_01E02760_b714, 0);
        func_01E040B0_b714(s, func_01E02FF0_b714, 0);
    }
}

/* shape b714:01E02300, 84 insns: follows model point 0x3B88[0x30] (for 0x65 ticks); colour (0xA0, 0x80, 8); alpha
   grows by 12 (below 0x80) for 0x66 ticks once the game counter 0x3B40 reaches 0x10, then fades by 10; also fades
   while the counter is below 15; 0x6 = 50 while following */

typedef struct {
    u8 pad0[0x3B40];
    s32 count;
    u8 pad3B44[0x44];
    s16 pts[1];
} Game_b714_01E02300;

typedef struct {
    s16 x, y, z;
    s16 f6;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[4];
    s16 pt;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b714_01E02300;

static s32 func_01E02300_b714(Game_b714_01E02300 *g, Fx_b714_01E02300 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];

    func_001F5620(func_001F53A0(), g->pts[o->pt], p);
    func_001076F0(o->col, 0xA0, 0x80, 8);
    if (o->mode == 1) {
        o->mode = 2;
    }
    if (o->tick < 0x66) {
        if (g->count > 0xF) {
            if (o->col[3] < 0x80) {
                o->col[3] += 12;
            }
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (g->count < 15) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 10;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    if (o->tick < 0x65) {
        o->x = p[0];
        o->y = p[1];
        o->z = p[2];
        o->f6 = 50;
    }
    return 0;
}

/* shape b714:01E02450, 95 insns: constant variant of b045:01E021B0 (70->10, 20->9, 8->3, 3->5) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    s32 rot;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b714_01E02450;

static s32 func_01E02450_b714(s32 arg0, Fx_b714_01E02450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 10;
        o->f34 = func_0019A5C8() % 2 + 2;
        o->rot = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x30, 0x28, 8);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 9 + 3;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 5;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x61) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b714:01E025D0, 99 insns: a dim yellow camera-facing glow (b378:01E01230 shape): turned by the camera side, size 90
   growing by 8 up to 160; alpha up by 0x40 for 2 frames, then down by 9; fades faster (by 13) once the scene timer drops under 15 */

typedef struct {
    u8 pad0[0x3B40];
    s32 timer;
} Scene_b714_01E025D0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 size;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b714_01E025D0;

static s32 func_01E025D0_b714(Scene_b714_01E025D0 *g, Obj_b714_01E025D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 ang[4];

    func_001076F0(o->c0, 0x10, 0x10, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), ang);
        if (func_001A22C0(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        if (o->size == 0) {
            o->rot[2] = 0;
        } else {
            o->rot[2] = 0;
        }
        o->sub = 0;
        o->size = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    if (g->timer < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b018:01E02480, 54 insns, 11 copies: step of a fading effect: on state 1 sets its two colours, a random angle and
   state 2; full alpha for the first 5 ticks, then fades by 10 until state 0 */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b018_01E02480;

static s32 func_01E02760_b714(void *arg0, Obj_b018_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x14A;
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x20, 0x10, 0);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0x10;
    }
    if (o->t < 5) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b714:01E02840, 42 insns: colour (0x40, 0x30, 0); on start 0x38 = 5; alpha 0x60 for 0xC ticks, then fades by 9
   and stops; 0x6 = 10 each tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x20];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b714_01E02840;

static s32 func_01E02840_b714(s32 arg0, Fx_b714_01E02840 *o) {
    func_001076F0(o->col, 0x40, 0x30, 0);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    if (o->tick < 0xC) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f6 = 10;
    o->tick++;
    return 0;
}

/* shape b018:01E02610, 108 insns: a twinkling sprite: on start pick a random variant, position, angle, spin speed,
   delay and lifetime and colour (0x20,0x10,8); fade in by 0x38 while younger than its lifetime, then fade out by
   10 and stop; spin while running */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b018_01E02610;

static s32 func_01E028F0_b714(s32 arg0, Spark_b018_01E02610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xA;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x20, 0x10, 8);
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->delay = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 5;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x71) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->angle += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b018:01E027C0, 97 insns: b018:01E02950 with a second seed and a longer fade start. */

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    s32 seed2;
    u8 pad14[4];
    s32 seed;
    u8 pad1C[0xC];
    u8 col[3];
    u8 alpha;
    u8 pad2C[4];
    s16 pos;
    s16 age;
    s16 kind;
    s16 state;
    s16 mode;
    s16 angle;
} Spark_b018_01E027C0;

static s32 func_01E02AA0_b714(s32 unused, Spark_b018_01E027C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->seed2 = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 20 + 10;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 16) {
        o->alpha -= 10;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b045:01E02B90, 90 insns: a spark: on start f38 5, random variant, colour (0x80,0x40,0), random depth,
   direction, spin 3..18, f8 0..9, life 1..3; alpha 0x80 during the life, then fades out by 10 and stops; turns
   by the spin every tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b045_01E02B90;

static s32 func_01E02C30_b714(s32 arg0, Spark_b045_01E02B90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 5;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->z = func_0019A5C8() % 0xFFFF;
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->f8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->angle += o->spin;
    o->tick++;
    return 0;
}

/* shape b714:01E02DA0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0xA0, 0x80, 8) and fields;
   alpha 0x60 for the first 0xC ticks, then fade out by 9 and stop */

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
} Glow_b714_01E02DA0;

static s32 func_01E02DA0_b714(s32 arg0, Glow_b714_01E02DA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xA0, 0x80, 8);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0xC) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b714:01E02E50, 101 insns: on start 0x38 = 50, colour 0x20 grey, random 0x30 and heading 0x3A; alpha 0x80 for
   10 ticks, then fades by 10 and stops; 0x34 counts up to 7 every third tick; it drifts 4 along the heading (0x8 by
   the sine, 0xC by the cosine of the game table 0x3CA4) */

typedef struct {
    u8 pad0[0x3CA4];
    u8 trig[1];
} Game_b714_01E02E50;

typedef struct {
    u8 pad0[8];
    s16 x;
    u8 padA[2];
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b714_01E02E50;

static s32 func_01E02E50_b714(Game_b714_01E02E50 *g, Fx_b714_01E02E50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f38 = 50;
        o->f34 = 0;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->f30 = func_0019A5C8() % 360;
        o->heading = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->tick++;
    o->x = o->x + 4.0f * func_00108030(g->trig, o->heading, 0);
    o->z = o->z + 4.0f * func_00108030(g->trig, o->heading, 1);
    return 0;
}

/* shape b714:01E02FF0, 93 insns: a screen fog: on start sets the scene fog block (0x3680: 128, 4.0, 2.0, 0.0, position from
   the effect, colour (0, 120.0, 0)); its strength 0x36A8 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 (0x3B40) */

typedef struct {
    u8 pad0[0x3680];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad36AC[0x3B40 - 0x36AC];
    s32 count;
} Game_b714_01E02FF0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[0x4];
    s16 mode;
} Fx_b714_01E02FF0;

static s32 func_01E02FF0_b714(Game_b714_01E02FF0 *g, Fx_b714_01E02FF0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2A00 = 128.0f;
        g->f2A04 = 4.0f;
        g->f2A08 = 2.0f;
        g->f2A0C = 0.0f;
        g->f2A20 = 0.0f;
        g->f2A24 = 120.0f;
        g->strength = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->strength < 1.0f) {
            g->strength += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (!(g->strength <= 0.1f)) {
        g->strength -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->f2A00);
    }
    if (g->count == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b714:01E03170, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3B40 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3B40];
    s32 state;
} Game_b714_01E03170;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b714_01E03170;

static s32 func_01E03170_b714(Game_b714_01E03170 *g, Fade_b714_01E03170 *o) {
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

/* shape b714:01E03230, 31 insns: func_001F7170(2, 0, &a, &b, 0) with copies of the module's floats at 0x01E04300 and
   0x01E04308; when the game value at 0x3B40 is 0xA the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b714_01E03230;

typedef struct {
    u8 pad0[0x3B40];
    s32 v;
} Game_b714_01E03230;

typedef struct {
    u8 pad0[0x36];
    s16 f;
} Fx_b714_01E03230;

extern F_b714_01E03230 D_01E04300_b714;
extern F_b714_01E03230 D_01E04308_b714;

static s32 func_01E03230_b714(Game_b714_01E03230 *g, Fx_b714_01E03230 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b714_01E03230 a;
    F_b714_01E03230 b;

    a = D_01E04300_b714;
    b = D_01E04308_b714;
    func_001F7170(2, 0, &a, &b, 0);
    if (g->v == 0xA) {
        o->f = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b714", func_01E032B0_b714);

/* shape b714:01E040B0, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3B9A and the two arguments; returns 1 if a
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
} Slot_b714_01E040B0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b714_01E040B0 s[200];
    u8 pad3678[0x4CC];
    u8 r, g, b, a;
    u8 pad3B48[0x52];
    s16 v;
} Pool_b714_01E040B0;

static s32 func_01E040B0_b714(Pool_b714_01E040B0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b714_01E040B0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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

/* shape b714:01E041D0, 67 insns: draws a vertical bar sprite (b045:01E04160 twin): colour from the object, a two-point column from (x, y, z)
   up by h, projected into the given packet and queued at its depth */

typedef struct {
    s16 x, y, z, h;
    u8 pad8[0x20];
    u8 c0[4];
} Bar_b714_01E041D0;

typedef struct {
    u8 pad0[0x18];
    u16 h18;
    u8 pad1A[0xE];
    u16 h28;
} Pkt_b714_01E041D0;

typedef struct {
    u8 pad0[0x3B4C];
    s32 ot;
} Game_b714_01E041D0;

static void func_01E041D0_b714(Game_b714_01E041D0 *g, Bar_b714_01E041D0 *b, Pkt_b714_01E041D0 *p) {
    extern void func_001091B0(void *, void *, void *);
    extern void func_00195108();
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[2];
    f32 depth __attribute__((aligned(16)));

    func_001091B0(p, b->c0, b->c0);
    func_00195108(q, 0x20);
    q[0].y = b->y;
    q[1].y = q[0].y + b->h;
    q[0].x = b->x;
    q[0].z = b->z;
    q[1].x = b->x;
    q[1].z = b->z;
    func_00205630(q, 0x70000000, NULL, p, &depth);
    p->h28 = p->h18;
    func_002075F0(p, g->ot, (u32)depth);
}
