#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b709(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b709(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E005A0_b709(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b709((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00780_b709(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b709((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00B00_b709(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00150_b709((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00E30_b709(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

static Vec_b018_01E00EE0 func_01E010C0_b709(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b709", func_01E01500_b709);

/* shape b045:01E00E30, 224 insns: b018:01E005A0 with n taken as is, rot[1] = -(rot[1] / 180) instead of the
   object's rotation (no rotation for the world matrix), and func_00109100(m, rot, 0, self + 0xD8) per sprite; draws n textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E00E30;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E00E30 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E00E30;

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
} Obj_b045_01E00E30;

static void func_01E01970_b709(u8 *self, Obj_b045_01E00E30 *obj, Pk_b045_01E00E30 *pk, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E00E30 uv;
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
    n = *(s16 *)(self + 0xB8);
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
    func_01E00150_b709((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, 0, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
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

/* OVL_WARM */

/* shape b257:01E01270, 386 insns, 2 copies: a textured curved beam along the module's spline (shape b018:01E00EE0, here at
   b257:01E00E30) through the given points (b018:01E01320 family): 4 sub-steps per segment, each drawn as a
   4-quad cross (two tilted by half the width), gouraud between the two colours, alpha fading along the beam,
   depth far. The spline must be in the same file and static: the original keeps $a0/$a1 across each call. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b257_01E01270;

typedef struct {
    u8 r, g, b, a;
} Col_b257_01E01270;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b257_01E01270;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b257_01E01270 c;
        u64 st;
        Xyz_b257_01E01270 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b257_01E01270;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b257_01E01270;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b257_01E01270 col0;
    Col_b257_01E01270 col1;
    u8 pad30[8];
    s16 width;
} Beam_b257_01E01270;

static void func_01E01CF0_b709(Ctx_b257_01E01270 *c, Beam_b257_01E01270 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b257_01E01270 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00107790(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    s32 rot[4];
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b257_01E01270 pkt __attribute__((aligned(8)));
    Col_b257_01E01270 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b257_01E01270 *p;
    s32 target;
    f32 t;
    f32 w;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
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
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E010C0_b709(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E010C0_b709(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E010C0_b709(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E010C0_b709(ctrl, 0, t);
                ab[1] = r2;
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
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
                    q[1].y += w;
                    q[3].y += w;
                } else if (k == 1) {
                    q[1].y -= w;
                    q[3].y -= w;
                } else if (k == 2) {
                    q[1].x += w;
                    q[3].x += w;
                    q[1].z += w / 2.0f;
                    q[3].z += w / 2.0f;
                } else if (k == 3) {
                    q[1].x -= w;
                    q[3].x -= w;
                    q[1].z -= w / 2.0f;
                    q[3].z -= w / 2.0f;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                    func_002075F0(p, target, 0);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b709", func_01E02300_b709);

/* shape b709:01E02BF0, 134 insns: b019:01E01F60 with its sine table at ctx+0x36C4 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x36C4];
    u8 tab[1];
} Mgr_b709_01E02BF0;

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
} Fx_b709_01E02BF0;

static s32 func_01E02BF0_b709(Mgr_b709_01E02BF0 *m, Fx_b709_01E02BF0 *o) {
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

/* shape b709:01E02E10, 159 insns: an orange flare (size 15, 90 wide) tilted by the model's facing, growing 1..3 high per tick; widens 8 per tick (2 once scene count 171 or 161 is reached by side), and +12 more from count 188 or 179; alpha up by 64 to 0x80 for 4 ticks, then down by 13; turns 5 per tick */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x33BE];
    s16 count;
} Ctx_b709_01E02E10;

typedef struct {
    u8 pad0[6];
    s16 side;
    u8 pad8[6];
    s16 hE;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b709_01E02E10;

static s32 func_01E02E10_b709(Ctx_b709_01E02E10 *g, Fx_b709_01E02E10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 a[4];
    s16 n;

    n = 0;
    func_001076F0(o->col, 0x80, 0x50, 0xC8);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), a);
        if ((s32)(a[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = 0xFFFF4000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->f34 = 0;
        o->side = o->f30;
        o->f30 = 90;
        o->f38 = 15;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (o->side == 0 && g->count > 187) {
        o->f38 += 12;
    }
    if (o->side == 1 && g->count > 178) {
        o->f38 += 12;
    }
    if (o->side == 0) {
        if (g->count > 170) {
            n = 2;
        } else {
            n = 8;
        }
    }
    if (o->side == 1) {
        if (g->count > 160) {
            n = 2;
        } else {
            n = 8;
        }
    }
    o->tick++;
    o->hE += (s16)(func_0019A5C8() % 3 + 1);
    o->f30 += n;
    o->f3A += 5;
    if (o->f3A >= 360) {
        o->f3A %= 360;
    }
    return 0;
}

/* shape b709:01E03090, 113 insns: on start 0x38 = 6, variant 0..3, colour (0xA0, 0x60, 0), random 0x18 and 0x10, 0x3A
   keeps the old 0x30 (a game point index), 0x30 = 0, speed 7..23 (0xE), 0x8 0..9, hold 1..3 (0x6); alpha 0x80 during
   the hold, then fades by 10 and stops; its position is the game point 0x31B0 + 0x3A x 16; 0x30 grows by the speed */

typedef struct {
    u8 pad0[0x31B0];
    Vec4f pts[1];
} Game_b709_01E03090;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 pt;
} Fx_b709_01E03090;

static s32 func_01E03090_b709(Game_b709_01E03090 *g, Fx_b709_01E03090 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 6;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xA0, 0x60, 0);
        o->w18 = func_0019A5C8() % 0xFFFF;
        o->w10 = func_0019A5C8() % 0xFFFF;
        o->pt = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 17 + 7;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 2 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->x = func_001A22C0(g->pts[o->pt].x);
    o->y = func_001A22C0(g->pts[o->pt].y);
    o->z = func_001A22C0(g->pts[o->pt].z);
    o->f30 += o->speed;
    o->tick++;
    return 0;
}

/* shape b225:01E02120, 92 insns, 2 copies: a spinning violet ember: set up once (random frame, two turns, speed 7..23,
   size, life 2..3, keeps its old angle); full alpha for its life, then fades out; its angle advances by its speed (b003:01E01780 family) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    s32 rot2;
    u8 pad14[4];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 h3A;
} Ember_b225_01E02120;

static s32 func_01E03260_b709(void *arg0, Ember_b225_01E02120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 10;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x60, 8, 0xA0);
        o->rot = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
        o->h3A = o->ang;
        o->ang = 0;
        o->speed = func_0019A5C8() % 17 + 7;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 2 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->ang += o->speed;
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

static s32 func_01E033D0_b709(void *arg0, Obj_b018_01E02560 *o) {
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

/* shape b709:01E03480, 89 insns: on start 0x38 = 25, variant 0..7, colour (0x40, 8, 0x80), random 0x3A,
   speed 7..22 (0xE), 0x8 0..9, hold 3..9 (0x6); alpha grows by 0x38 (up to 0x70) during the hold,
   then fades by 10 and stops; 0x30 grows by the speed after the first tick */

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
} Fx_b709_01E03480;

static s32 func_01E03480_b709(s32 arg0, Fx_b709_01E03480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 25;
        o->f34 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x40, 8, 0x80);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 7;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x71) {
            o->col[3] += 0x38;
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

/* shape b709:01E035F0, 88 insns: an orange rising spark (b718:01E03620 family): frame 14, rise 6..23, height 0..9, full-alpha time 8..27; then fades
   by 10 until it ends; turns 5 a frame and rises every frame */

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
} Obj_b709_01E035F0;

static s32 func_01E035F0_b709(void *arg0, Obj_b709_01E035F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xE;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0);
        o->rot = func_0019A5C8() % 360;
        o->ang = o->y;
        o->y = 0;
        o->step = func_0019A5C8() % 18 + 6;
        o->h8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 20 + 8;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->rot += 5;
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b225:01E026A0, 90 insns, 2 copies: a spinning ember: set up once (random frame, turn, speed 5..20, size, life
   2..6); full alpha for its life, then fades out; its angle advances by its speed (b003:01E01780 family) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 h3A;
} Ember_b225_01E026A0;

static s32 func_01E03750_b709(void *arg0, Ember_b225_01E026A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x19;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0);
        o->rot = func_0019A5C8() % 65535;
        o->ang = 0;
        o->h3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 5;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 5 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->ang += o->speed;
    o->t++;
    return 0;
}

/* shape b709:01E038C0, 150 insns: b225:01E02810 with the scene count at ctx+0x33BE */

typedef struct {
    u8 pad0[0x33BE];
    s16 count;
} Ctx_b709_01E038C0;

typedef struct {
    s16 x, y, z;
    s16 life;
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
    s16 dir;
} Fx_b709_01E038C0;

static s32 func_01E038C0_b709(Ctx_b709_01E038C0 *g, Fx_b709_01E038C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 2;
        o->f34 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x40, 0x40, 0x80);
        o->rot = func_0019A5C8() % 360;
        o->dir = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 10 + 4;
        o->f8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 16 + 9;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->dir != 0) {
        o->rot += 5;
    } else {
        o->rot -= 5;
    }
    if (o->dir == 1) {
        if (g->count < 186) {
            o->f30 += o->speed;
        } else {
            func_001076F0(o->col, 0x20, 0x20, 0xC0);
            o->f30 += o->speed + 88;
        }
    }
    if (o->dir == 0) {
        if (g->count < 193) {
            o->f30 += o->speed;
        } else {
            func_001076F0(o->col, 0x20, 0x20, 0xC0);
            o->f30 += o->speed + 88;
        }
    }
    if (g->count >= 141) {
        o->f38 = 13;
    }
    o->tick++;
    return 0;
}

/* shape b709:01E03B20, 94 insns: b225:01E023F0 family: a grey spark (size 16, random frame 0..7, random roll and angle) spinning a random 10..27 a tick, size 0..9, held 3..9 ticks: in by 56 up to 0x70, then out by 10 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
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
} Glow_b709_01E03B20;

static s32 func_01E03B20_b709(s32 arg0, Glow_b709_01E03B20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 16;
        o->kind = func_0019A5C8() % 8;
        o->w18 = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0xA0, 0xA0, 0xA0);
        o->h30 = 0;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 18 + 10;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x70) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b709:01E03CA0, 96 insns: a grey/yellow two-colour glow (size 10, frame 1, 9 at +6): alpha 0xC0, dipping by 9 between ticks 40 and 140, then 0xC0 again until 175, then out by 9 and ends; rolls 6 a tick (wrapped at 360) */

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
} Glow_b709_01E03CA0;

static s32 func_01E03CA0_b709(s32 arg0, Glow_b709_01E03CA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    s16 r;

    if (o->mode == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0);
        o->h6 = 9;
        o->col[3] = 0x40;
        o->kind = 1;
        o->f38 = 10;
        o->mode = 2;
    }
    if (o->tick < 175) {
        if (o->tick < 40) {
            o->col[3] = 0xC0;
        } else if (o->tick < 140) {
            if (o->col[3] > 10) {
                o->col[3] -= 9;
            } else {
                o->col[3] = 0;
            }
        } else {
            o->col[3] = 0xC0;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    for (i = 0; i < 10; i++) {
    }
    r = o->w18 += 6;
    if (r >= 360) {
        r %= 360;
    }
    o->w18 = r;
    return 0;
}

/* shape b709:01E03E20, 90 insns, 1 copy: blink and fade, an empty delay loop (2.3.3 keeps it, 2.4 drops it),
   angle += 6 wrapped at 360 */

typedef struct Col_b709_01E03E20 {
    u8 r, g, b, a;
} Col_b709_01E03E20;

typedef struct Obj_b709_01E03E20 {
    u8 pad0[6];
    s16 f06;
    u8 pad8[0x10];
    s32 angle;
    u8 pad1C[0xC];
    Col_b709_01E03E20 c28;
    Col_b709_01E03E20 c2C;
    u8 pad30[2];
    s16 t;
    s16 f34;
    s16 state;
    s16 f38;
} Obj_b709_01E03E20;

static s32 func_01E03E20_b709(void *ctx, Obj_b709_01E03E20 *o) {
    extern void func_001076F0();
    s16 i;
    s16 a;

    if (o->state == 1) {
        func_001076F0(&o->c28, 0xC0, 0xC0, 0xC0);
        func_001076F0(&o->c2C, 0xC0, 0xC0, 0);
        o->f06 = 9;
        o->c28.a = 0x40;
        o->f34 = 1;
        o->f38 = 10;
        o->state = 2;
    }
    if (o->t < 0xAF) {
        if (o->t % 2 == 1) {
            o->c28.a = 0xC0;
        } else {
            o->c28.a = 0x80;
        }
    } else if (o->c28.a > 0xA) {
        o->c28.a -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    for (i = 0; i < 10; i++) {
    }
    a = o->angle += 6;
    if (a >= 360) {
        a = a % 360;
    }
    o->angle = a;
    return 0;
}

/* shape b500:01E02830, 108 insns: a spark at a random position: f38 16, variant 0..7, colour set twice (the
   grey one wins), angle 300..349, random direction, spin 10..27, f8 0..9, fC 10, life 2; alpha grows by 0x58 (below
   0xB1) during the life, then fades by 13 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    u8 padA[2];
    s16 fC;
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
} Spark_b500_01E02830;

static s32 func_01E03F90_b709(s32 arg0, Spark_b500_01E02830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 16;
        o->kind = func_0019A5C8() % 8;
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0xA0, 0xA0, 0x10);
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->angle = func_0019A5C8() % 50 + 300;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 18 + 10;
        o->f8 = func_0019A5C8() % 10;
        o->fC = 10;
        o->life = 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xB1) {
            o->col[3] += 0x58;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    o->tick++;
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

static s32 func_01E04140_b709(void *arg0, Obj_b018_01E02480 *o) {
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

/* shape b709:01E04220, 115 insns: on start 0x38 = 123, variant 0, colour 0x40 grey, random headings 0x30 and 0x3A; alpha 0x80
   for 10 ticks, then fades by 10 and stops; the variant counts up to 7 every third tick; it drifts (x by 14.0 x the
   cosine of 0x3A, y by 4.0 x the sine of 0x30, z by 14.0 x the sine of 0x3A, game table 0x36C4) */

typedef struct {
    u8 pad0[0x36C4];
    u8 trig[1];
} Game_b709_01E04220;

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
} Fx_b709_01E04220;

static s32 func_01E04220_b709(Game_b709_01E04220 *g, Fx_b709_01E04220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 123;
        o->f34 = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
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
    o->x = func_001A22C0(o->x + 14.0f * func_00108030(g->trig, o->f3A, 0));
    o->y = func_001A22C0(o->y + 4.0f * func_00108030(g->trig, o->f30, 1));
    o->z = func_001A22C0(o->z + 14.0f * func_00108030(g->trig, o->f3A, 1));
    return 0;
}

/* shape b709:01E043F0, 93 insns: a screen fog: on start sets the scene fog block (0x3180: 128, 4.0, 2.0, 0.0, position from
   the effect, colour (0, 120.0, 0)); its strength 0x31A8 rises by 0.2 to 1, then falls by 0.1 and ends; the block is
   passed to func_001F6C10 while alive (NULL once ended); it ends at scene counter 1 (0x3360) */

typedef struct {
    u8 pad0[0x3180];
    f32 f2A00;
    f32 f2A04;
    f32 f2A08;
    f32 f2A0C;
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f2A20;
    f32 f2A24;
    f32 strength;
    u8 pad31AC[0x3360 - 0x31AC];
    s32 count;
} Game_b709_01E043F0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[0x4];
    s16 mode;
} Fx_b709_01E043F0;

static s32 func_01E043F0_b709(Game_b709_01E043F0 *g, Fx_b709_01E043F0 *o) {
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

/* shape b709:01E04570, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3360 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3360];
    s32 state;
} Game_b709_01E04570;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b709_01E04570;

static s32 func_01E04570_b709(Game_b709_01E04570 *g, Fade_b709_01E04570 *o) {
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

static s32 func_01E04630_b709(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E06100_b709;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E06108_b709;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b709:01E04680, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-3 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x2FC0];
    s32 tex5[4];
} Scene_b709_01E04680;

static void func_01E04680_b709(s32 arg0, Scene_b709_01E04680 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 4; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b709", func_01E04730_b709);

/* shape b709:01E054A0, 72 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x33BA and the two arguments; returns 1 if a
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
} Slot_b709_01E054A0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b709_01E054A0 s[180];
    u8 pad3178[0x1EC];
    u8 r, g, b, a;
    u8 pad3368[0x52];
    s16 v;
} Pool_b709_01E054A0;

static s32 func_01E054A0_b709(Pool_b709_01E054A0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b709_01E054A0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 180; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 180;
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

/* shape b709:01E055C0 (B709PAINT_RAIN), 267 insns, 1 copy: b018:01E03760's cone of quads: mode 0 only sets up the
   packet (texture 0x97 at page 0x34, flat colour, texture corners by the module helper at 0x1E00150, shape
   b008:01E00080); otherwise it sits between the scene's point tables 0x31B0 and 0x320 (index 0x6, step 0xE fiftieths
   of the way), scaled by size / 250, and draws 12 quads 30 apart: heights 30 x sines of tilt and tilt+8, radii 90 x
   cosines of tilt (capped at 160) and tilt+14 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b709_01E055C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b709_01E055C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b709_01E055C0 c;
    struct {
        u64 tc;
        Xyz_b709_01E055C0 p;
    } v[4];
} Pkt_b709_01E055C0;

typedef struct {
    u8 pad0[0x320];
    Vec4f ta[5];
    u8 pad370[0xC];
    void *texture;
    u8 pad380[0x31B0 - 0x380];
    Vec4f tb[0x1B];
    u8 pad3360[0xC];
    s32 ot;
    u8 pad3370[0x24];
    f32 dep;
    u8 pad3398[0x36C4 - 0x3398];
    u8 trig[1];
} Ctx_b709_01E055C0;

typedef struct {
    u8 pad0[6];
    s16 idx;
    u8 pad8[6];
    s16 step;
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 tilt;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b709_01E055C0;

static void func_01E055C0_b709(Ctx_b709_01E055C0 *c, Fan_b709_01E055C0 *o, Pkt_b709_01E055C0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b709_01E055C0 func_00107740(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    f32 v[4];
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 j;
    s16 tl;
    s32 t2;
    s16 a;
    s16 t;
    f32 r0;
    f32 r1;
    f32 sn;
    f32 cs;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sc;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00150_b709((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
    } else {
        dx = (c->ta[o->idx].x - c->tb[o->idx].x) / 50.0f * o->step;
        dy = (c->ta[o->idx].y - c->tb[o->idx].y) / 50.0f * o->step;
        dz = (c->ta[o->idx].z - c->tb[o->idx].z) / 50.0f * o->step;
        v[0] = c->tb[o->idx].x;
        v[1] = c->tb[o->idx].y;
        v[2] = c->tb[o->idx].z;
        v[0] += dx;
        v[1] += dy;
        v[2] += dz;
        sc = o->size;
        sc /= 250.0f;
        func_00106DD0(&scale, sc, sc, sc);
        func_00108EF0(m, &scale, o->rot, v);
        for (j = 0; j < 1; j++) {
            tl = o->tilt;
            quad[0].y = 30.0f * func_00108030(c->trig, o->tilt, 0);
            quad[1].y = quad[0].y;
            quad[2].y = 30.0f * func_00108030(c->trig, o->tilt + 8, 0);
            quad[3].y = quad[2].y;
            if (tl > 0xA0) {
                tl = 0xA0;
            }
            r0 = 90.0f * func_00108030(c->trig, tl, 1);
            t2 = tl + 14;
            r1 = 90.0f * func_00108030(c->trig, t2, 1);
            a = 0;
            for (k = 0; k < 12; k++) {
                t = o->ang + a;
                sn = func_00108030(c->trig, t, 1);
                cs = func_00108030(c->trig, t, 0);
                quad[2].x = sn * r1;
                quad[2].z = cs * r1;
                quad[0].x = r0 * func_00108030(c->trig, t, 1);
                quad[0].z = r0 * func_00108030(c->trig, t, 0);
                t = o->ang + 30 + a;
                sn = func_00108030(c->trig, t, 1);
                cs = func_00108030(c->trig, t, 0);
                quad[3].x = sn * r1;
                quad[3].z = cs * r1;
                quad[1].x = sn * r0;
                quad[1].z = cs * r0;
                if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                    func_002075F0(p, c->ot, (u32)c->dep);
                }
                a += 30;
            }
        }
    }
}


/* shape b225:01E048B0, 206 insns, 2 copies: draws a row of thin bars into the caller's packet (b225:01E04BF0 family): each
   shaken by a per-entry table offset (/20) that grows along the row, its near edge pinned at x +-1 and its far
   edge pushed along the object's velocity; placed at the object's point, two colours by the gouraud helper */

typedef struct {
    u8 pad00[0x20];
    Vec4f vel[2];
    Vec4f pt[2];
    u8 pad60[0x20];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b225_01E048B0;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 padA[6];
    s32 rot[4];
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
    s16 idx;
} Spr_b225_01E048B0;

static void func_01E059F0_b709(Obj_b225_01E048B0 *o, Spr_b225_01E048B0 *s, void *p, s8 *tbl) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
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
    f32 vx;
    f32 vy;

    func_00207500();
    func_00109270(p, 0, 0);
    func_00107790(p, s->col1, 1);
    func_00107790(p, s->col0, 2);
    func_00108500(p, o->rect, 0);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] = s->rot[0];
    rot[1] = s->rot[1];
    rot[2] = s->rot[2];
    vx = 5.0f * o->vel[s->idx].x;
    vy = 5.0f * o->vel[s->idx].y;
    pos.x = o->pt[s->idx].x;
    pos.y = o->pt[s->idx].y;
    pos.z = o->pt[s->idx].z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, s->size, s->size);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 20.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 20.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        func_00109100(quad, s->rot, 2, o->xD8);
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[0].x = 1.0f;
        quad[1].x = -1.0f;
        quad[0].z = 0.0f;
        quad[1].z = 0.0f;
        quad[2].x += vx;
        quad[2].y += vy;
        quad[3].x += vx;
        quad[3].y += vy;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* shape b225:01E04BF0, 220 insns, 3 copies: draws a row of thin bars (count of them) at the sprite's position into the
   caller's packet: each shaken by a per-entry table offset that grows along the row, turned by the sprite's
   rotation, its far edge pinned at +-w; two colours top/bottom. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b225_01E04BF0;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b225_01E04BF0 c;
        u64 uv;
        u64 xyz;
    } v[4];
} Pkt_b225_01E04BF0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 xD8[1];
} Obj_b225_01E04BF0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[2];
    s16 w;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col0[4];
    u8 col1[4];
    s16 w30;
    u8 pad32[6];
    s16 size;
} Spr_b225_01E04BF0;

static void func_01E05D30_b709(Obj_b225_01E04BF0 *o, Spr_b225_01E04BF0 *s, Pkt_b225_01E04BF0 *p, s8 *tbl) {
    extern Rgbaq_b225_01E04BF0 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    s32 rot[4];
    f32 depth[4];
    s16 i;
    s32 h;
    s8 *j;
    f32 f;
    f32 w;
    f32 nw;

    func_00207500();
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(s->col1);
    p->v[1].c = func_00107740(s->col1);
    p->v[2].c = func_00107740(s->col0);
    p->v[3].c = func_00107740(s->col0);
    func_00108500(p, o->rect, 0);
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
    w = s->w;
    nw = -w;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, s->size, s->size);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 10.0f;
        func_00107070(quad, 0, f * (s->w30 + h));
        f = j[s->off + 100];
        f /= 10.0f;
        func_00107070(quad, 1, f * (s->w30 + h));
        f = j[s->off + 180];
        f /= 10.0f;
        func_00107070(quad, 2, f * (s->w30 + h));
        func_00109100(quad, s->rot, 2, o->xD8);
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        quad[2].x = w;
        quad[3].x = nw;
        quad[2].z = 0.0f;
        quad[3].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}
