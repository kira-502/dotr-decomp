#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b393(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b393(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009F0_b393(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b393((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00D70_b393(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00150_b393((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E010A0_b393(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

static Vec_b018_01E00EE0 func_01E01330_b393(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b018:01E01320: curved beam along func_01E01330_b393 spline points. Needs func_01E01330_b393 in the same file and
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

static void func_01E01770_b393(s32 unused, Beam_b018_01E01320 *an, Vec_b018_01E00EE0 *pts) {
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
                ab[0] = func_01E01330_b393(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E01330_b393(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E01330_b393(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E01330_b393(ctrl, 0, t);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00150_b393 in the
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

static void func_01E01BB0_b393(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00150_b393((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b393:01E01DA0, 250 insns: the scene script of b393: colour 0x80/0/0/0, counts g+0x389E; at 51 reads joint
   0x388A into +0x36C0, which 52..64 is copied to the point (+0x2D0); before 137 two 0x1E023B0 a tick; 52..136 a
   0x1E02610 on each of joints 0x388C..0x3892; at 26 the point on joint 0x388C raised 1, flag set; at 136 on joint
   0x3888 eight 0x1E02C40, eight 0x1E02AB0, thirty 0x1E02900, a 0x1E02770 and a 0x1E02E60 */

typedef struct {
    f32 x, y, z, w;
} V4_b393_01E01DA0;

typedef struct {
    u8 pad0[0x2D0];
    V4_b393_01E01DA0 pos;
    u8 pad2E0[0x36C0 - 0x2E0];
    V4_b393_01E01DA0 pt;
    u8 pad36D0[0x174];
    u8 col[4];
    u8 pad3848[0x40];
    s16 j0;
    s16 j1;
    s16 j2;
    s16 j3;
    s16 j4;
    s16 j5;
    u8 pad3894[6];
    s16 flag;
    u8 pad389C[2];
    s16 tick;
} Ctx_b393_01E01DA0;

static void func_01E01DA0_b393(Ctx_b393_01E01DA0 *g) {
    extern void b393_01E023B0();
    extern void b393_01E02610();
    extern void b393_01E02770();
    extern void b393_01E02900();
    extern void b393_01E02AB0();
    extern void b393_01E02C40();
    extern void b393_01E02E60();
    extern void b393_01E03A40(Ctx_b393_01E01DA0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    f32 w[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick == 51) {
        func_001F5620(func_001F53A0(), g->j1, &g->pt);
    }
    if (g->tick > 51 && g->tick < 65) {
        func_001F5620(func_001F53A0(), g->j1, v);
        for (i = 0; i < 6; i++) {
            g->pos.x = g->pt.x;
            g->pos.y = g->pt.y;
            g->pos.z = g->pt.z;
        }
    }
    if (g->tick < 137) {
        b393_01E03A40(g, b393_01E023B0, 0);
        b393_01E03A40(g, b393_01E023B0, 0);
    }
    if (g->tick >= 52 && g->tick < 137) {
        func_001F5620(func_001F53A0(), g->j2, v);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        b393_01E03A40(g, b393_01E02610, 0);
        func_001F5620(func_001F53A0(), g->j3, v);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        b393_01E03A40(g, b393_01E02610, 0);
        func_001F5620(func_001F53A0(), g->j4, v);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        b393_01E03A40(g, b393_01E02610, 0);
        func_001F5620(func_001F53A0(), g->j5, v);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        b393_01E03A40(g, b393_01E02610, 0);
    }
    if (g->tick == 26) {
        func_001F5620(func_001F53A0(), g->j2, v);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        g->flag = 1;
        g->pos.y = 1.0f + v[1];
    }
    if (g->tick == 136) {
        func_001F5620(func_001F53A0(), g->j0, v);
        func_001F5F90(func_001F5380(), w);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b393_01E03A40(g, b393_01E02C40, 0);
        }
    }
    if (g->tick == 136) {
        func_001F5620(func_001F53A0(), g->j0, v);
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b393_01E03A40(g, b393_01E02AB0, 0);
        }
        for (i = 0; i < 30; i++) {
            b393_01E03A40(g, b393_01E02900, 0);
        }
        b393_01E03A40(g, b393_01E02770, 0);
        b393_01E03A40(g, b393_01E02E60, 0);
    }
}

/* shape b393:01E02190, 134 insns: b019:01E01F60 with its sine table at ctx+0x39A4 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x39A4];
    u8 tab[1];
} Mgr_b393_01E02190;

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
} Fx_b393_01E02190;

static s32 func_01E02190_b393(Mgr_b393_01E02190 *m, Fx_b393_01E02190 *o) {
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

/* shape b393:01E023B0, 150 insns: a red mote placed k tenths of the way from joint A to joint B (k 0..3): size 6,
   frame 2, a random spin word, height rising 7 - k/2 a tick, f8 0..9, held 1..3 at alpha 0x80, then fades by 10
   (ends below 0x11) */

typedef struct {
    s16 x, y, z;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 rise;
    u8 pad10[8];
    s32 spin;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 k;
} Fx_b393_01E023B0;

typedef struct {
    u8 pad0[0x3888];
    s16 ja;
    s16 jb;
} Scene_b393_01E023B0;

static s32 func_01E023B0_b393(Scene_b393_01E023B0 *g, Fx_b393_01E023B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    Vec4f v[2];
    f32 dx;
    f32 dy;
    f32 dz;

    if (o->mode == 1) {
        o->size = 6;
        o->k = func_0019A5C8() % 4;
        o->frame = 2;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
        o->spin = func_0019A5C8() % 65535;
        o->h = 0;
        o->rise = 7 - (o->k >> 1);
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->h += o->rise;
    o->t++;
    func_001F5620(func_001F53A0(), g->ja, &v[0]);
    func_001F5620(func_001F53A0(), g->jb, &v[1]);
    dx = v[1].x - v[0].x;
    dy = v[1].y - v[0].y;
    dz = v[1].z - v[0].z;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    o->x = func_001A22C0(v[0].x + dx * o->k);
    o->y = func_001A22C0(v[0].y + dy * o->k);
    o->z = func_001A22C0(v[0].z + dz * o->k);
    return 0;
}

/* shape b393:01E02610, 87 insns: a grey drifting puff: frame 60, sub-frame 5, random tilt and angle; full alpha for 7 frames,
   then down by 15 until it ends; drifts 16 along its angle (sin to x, cos to z) each frame */

typedef struct {
    u8 pad0[0x39A4];
    u8 trig[1];
} Game_b393_01E02610;

typedef struct {
    u8 pad0[8];
    s16 x;
    u8 padA[2];
    s16 z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 tilt;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b393_01E02610;

static s32 func_01E02610_b393(Game_b393_01E02610 *g, Obj_b393_01E02610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h38 = 0x3C;
        o->sub = 5;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->tilt = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 7) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->x = o->x + 16.0f * func_00108030(g->trig, o->ang, 0);
    o->z = o->z + 16.0f * func_00108030(g->trig, o->ang, 1);
    o->t++;
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

static s32 func_01E02770_b393(void *arg0, Obj_b018_01E02480 *o) {
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

/* shape b018:01E02560, 42 insns, 6 copies: an orange flash: colour, then fade after 75 frames (variant of b018:01E02480) */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x20];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b018_01E02560;

static s32 func_01E02850_b393(void *arg0, Obj_b018_01E02560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x80, 0x50, 0);
    if (o->state == 1) {
        o->h38 = 5;
        o->state = 2;
    }
    if (o->t < 0x4B) {
        o->c0[3] = 0x50;
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f6 = 10;
    o->t++;
    return 0;
}

/* shape b115:01E01BC0, 108 insns: variant of b018:01E02610 (col (128, 16, 16)): a twinkling sprite: on start pick a random variant, position, angle, spin speed,
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
} Spark_b115_01E01BC0;

static s32 func_01E02900_b393(s32 arg0, Spark_b115_01E01BC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xA;
        o->kind = func_0019A5C8() % 4;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0x80, 0x10, 0x10);
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

/* shape b115:01E01D70, 97 insns: a red spark: set up once (random frame, spin, speed 3..18, life 5..14); full alpha for its life, then fades by 15; turns by its speed */

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 h3A;
} Obj_b115_01E01D70;

static s32 func_01E02AB0_b393(void *arg0, Obj_b115_01E01D70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 2;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x20, 0x20);
        o->w18 = func_0019A5C8() % 65535;
        o->w10 = func_0019A5C8() % 65535;
        o->ang = 0;
        o->h3A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->state = 0;
    }
    o->ang += o->hE;
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[8];
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
} Spark_b018_01E02950;

static s32 func_01E02C40_b393(s32 unused, Spark_b018_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 3 + 1;
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

/* shape b018:01E02AC0, 43 insns: a glow: on start colour (0xA0,0x80,8), alpha 0x80, life 9, f38 8; alpha 0x60
   for the first 0x4B ticks, then fade out by 9 and stop */

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
} Glow_b018_01E02AC0;

static s32 func_01E02DB0_b393(s32 arg0, Glow_b018_01E02AC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xA0, 0x80, 8);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 8;
        o->mode = 2;
    }
    if (o->tick < 0x4B) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b393:01E02E60, 93 insns: a screen fog: on start sets the scene fog block (0x3680: 128, 4, 2, 0, position from
   the effect, colour (0, 120, 0)); its strength 0x36A8 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 */

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
    u8 pad36AC[0x3840 - 0x36AC];
    s32 count;
} Game_b393_01E02E60;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b393_01E02E60;

static s32 func_01E02E60_b393(Game_b393_01E02E60 *g, Fx_b393_01E02E60 *o) {
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

/* shape b393:01E02FE0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3840 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3840];
    s32 state;
} Game_b393_01E02FE0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b393_01E02FE0;

static s32 func_01E02FE0_b393(Game_b393_01E02FE0 *g, Fade_b393_01E02FE0 *o) {
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

static s32 func_01E030A0_b393(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03F80_b393;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03F88_b393;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b393:01E030F0, 40 insns: b734:01E03310 family: textures group 4 cells 0-2 and 13-15, group 5 cell 0 */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x34a0];
    s32 tex5[3];
} Scene_b393_01E030F0;

static void func_01E030F0_b393(s32 arg0, Scene_b393_01E030F0 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 1; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b393:01E03190 (b393), 554 insns, 1 copy: b393 scene manager (b052:01E02A00's form): with a scene id it clears
   the scene, takes six joints and the root joint, the textures (b393:01E030F0) and a 256-byte random table; otherwise
   it runs the script, fills both trails at frame 24, steps the 200 slots (0x1E02850 and 0x1E02DB0 written out), draws
   seven slot kinds and returns 1 / 4 / 2 at frames 126 / 146 / 136, 8 once the countdown runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 f6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[0x16];
    s32 (*fn)();
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 used;
    s16 h38;
    u8 pad3A[6];
} Slot_b393_01E03190;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x34];
    u8 crdD8[0x238];
    s32 z310[3];
    u8 pad31C[0x24];
    s32 tex[16];
    u8 pad380[0xF8];
    Slot_b393_01E03190 slot[200];
    u8 pad3678[0x58];
    Vec4f trB[10];
    Vec4f trA[10];
    u8 pad3810[0x10];
    s32 tex5[3];
    u8 pad382C[0x14];
    s32 count;
    u8 pad3844[8];
    s32 ot;
    u8 pad3850[0x38];
    s16 j[6];
    u8 pad3894[2];
    s16 jG;
    u8 pad3898[4];
    s16 id;
    s16 frame;
    u8 pad38A0[2];
    s8 jit[0x100];
    u8 pad39A2[2];
    u8 crd[0x16C];
} Scene_b393_01E03190;

static s32 func_01E03190_b393(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_01E01DA0_b393();
    extern void func_01E010A0_b393();
    extern void b393_01E03B60();
    Scene_b393_01E03190 *g = (Scene_b393_01E03190 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    Vec4f pa;
    Vec4f pb;
    u8 buf[0x90] __attribute__((aligned(8)));
    f32 b;
    f32 a;
    s32 i;

    m = 0;
    g->ot80 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3B10);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 200;
        g->z310[0] = 0;
        g->z310[1] = 0;
        g->z310[2] = 0;
        g->j[0] = func_001F5560(func_001F53A0(), 0x55, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x54, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x33, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x3F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x48, 0);
        g->jG = func_001F5560(func_001F5380(), 1, 1);
        func_01E030F0_b393(0, (Scene_b393_01E030F0 *)g);
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E01DA0_b393(g, 0);
    if (g->frame == 0x18) {
        Vec4f *p = g->trA;

        func_001F5620(func_001F53A0(), g->j[0], (s32)&pa);
        for (i = 0; i < 9; i++, p++) {
            p->x = pa.x;
            p->y = pa.y;
            p->z = pa.z;
        }
    }
    if (g->frame == 0x18) {
        Vec4f *p = g->trB;

        func_001F5620(func_001F53A0(), g->j[1], (s32)&pb);
        for (i = 0; i < 9; i++, p++) {
            p->x = pb.x;
            p->y = pb.y;
            p->z = pb.z;
        }
    }
    func_01E00080_b393((Vec_b004_01E00B40 *)&g->trA[9], 10, g->j[0]);
    func_01E00080_b393((Vec_b004_01E00B40 *)&g->trB[9], 10, g->j[1]);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E02190_b393) {
                func_01E02190_b393((Mgr_b393_01E02190 *)g, (Fx_b393_01E02190 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E023B0_b393) {
                func_01E023B0_b393((Scene_b393_01E023B0 *)g, (Fx_b393_01E023B0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02610_b393) {
                func_01E02610_b393((Game_b393_01E02610 *)g, (Obj_b393_01E02610 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02770_b393) {
                func_01E02770_b393(g, (Obj_b018_01E02480 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02850_b393) {
                func_001076F0(g->slot[i].c0, 0x80, 0x50, 0);
                if (g->slot[i].used == 1) {
                    g->slot[i].h38 = 5;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 0x4B) {
                    g->slot[i].c0[3] = 0x50;
                } else if (g->slot[i].c0[3] > 10) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].f6 = 10;
                g->slot[i].t++;
            }
            if (g->slot[i].fn == func_01E02900_b393) {
                func_01E02900_b393((s32)g, (Spark_b115_01E01BC0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02AB0_b393) {
                func_01E02AB0_b393(g, (Obj_b115_01E01D70 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02C40_b393) {
                func_01E02C40_b393((s32)g, (Spark_b018_01E02950 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02DB0_b393) {
                if (g->slot[i].used == 1) {
                    func_001076F0(g->slot[i].c0, 0xA0, 0x80, 8);
                    g->slot[i].f6 = 9;
                    g->slot[i].c0[3] = 0x80;
                    g->slot[i].h38 = 8;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 0x4B) {
                    g->slot[i].c0[3] = 0x60;
                } else if (g->slot[i].c0[3] > 10) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
            }
            if (g->slot[i].fn == func_01E02E60_b393) {
                func_01E02E60_b393((Game_b393_01E02E60 *)g, (Fx_b393_01E02E60 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02FE0_b393) {
                func_01E02FE0_b393((Game_b393_01E02FE0 *)g, (Fade_b393_01E02FE0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E030A0_b393) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03F80_b393;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03F88_b393;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E023B0_b393) {
                g->tex88 = g->tex[15];
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                b393_01E03B60(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02610_b393) {
                g->tex88 = g->tex5[0];
                func_00106080(rm2, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                c.x = g->slot[i].x;
                c.y = g->slot[i].y;
                c.z = g->slot[i].z;
                func_01E01BB0_b393((Obj_b046_01E00DD0 *)g, (Data_b046_01E00DD0 *)&g->slot[i], 0, c);
            }
            if (g->slot[i].fn == func_01E02770_b393) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                func_01E010A0_b393(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E02900_b393) {
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                func_01E009F0_b393((u8 *)g, (Obj_b018_01E005A0 *)&g->slot[i], (Pk_b018_01E005A0 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02AB0_b393) {
                g->tex88 = g->tex[1];
                func_00106080(rm5, 0xA, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                func_01E00D70_b393((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02C40_b393) {
                g->tex88 = g->tex[15];
                func_00106080(rm6, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                func_01E00D70_b393((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02DB0_b393) {
                func_01E01770_b393((s32)g, (Beam_b018_01E01320 *)&g->slot[i], (Vec_b018_01E00EE0 *)g->trB);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x7E) {
        return 1;
    }
    if (g->frame == 0x92) {
        return 4;
    }
    if (g->frame == 0x88) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b393:01E03A40, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x389A and the two arguments; returns 1 if a
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
} Slot_b393_01E03A40;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b393_01E03A40 s[200];
    u8 pad3678[0x1CC];
    u8 r, g, b, a;
    u8 pad3848[0x52];
    s16 v;
} Pool_b393_01E03A40;

static s32 func_01E03A40_b393(Pool_b393_01E03A40 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b393_01E03A40 *s = NULL;
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

/* OVL_WARM */

/* shape b052:01E03730, 245 insns, 3 copies: draws a row of 20 thin bars at the sprite's position into the caller's
   packet (b225:01E04BF0 family): each shaken by a per-entry table offset, far edge pinned at +-1, drawn far;
   texture corners by the module helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b052_01E03730;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b052_01E03730 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
} Pkt_b052_01E03730;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b008_01E00080 rect;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b052_01E03730;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[2];
    s16 w;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b052_01E03730;

static void func_01E03B60_b393(Obj_b052_01E03730 *o, Spr_b052_01E03730 *s, Pkt_b052_01E03730 *p, s8 *tbl) {
    extern Rgbaq_b052_01E03730 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;
    s32 h;
    s8 *j;
    f32 f;

    func_00207500();
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->c.q = 0;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
    p->v[3].f = 0;
    p->c = func_00107740(s->col);
    func_01E00150_b393((Pk_b008_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += s->rot[0];
    rot[1] += s->rot[1];
    rot[2] += s->rot[2];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        func_00108CE0(quad, s->size, s->size);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 50];
        f /= 20.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[0].x = 1.0f;
        quad[1].x = -1.0f;
        quad[0].z = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}
