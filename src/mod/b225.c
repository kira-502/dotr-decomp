#include "common.h"

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

static void func_01E00080_b225(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E004D0_b225(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
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
    func_01E00080_b225((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E006B0_b225(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00080_b225((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00A30_b225(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00080_b225((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00D60_b225(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

static void func_01E00FF0_b225(u8 *self, Obj_b045_01E00E30 *obj, Pk_b045_01E00E30 *pk, s8 *base) {
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
    func_01E00080_b225((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b225 in the
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

static void func_01E01370_b225(Obj_b046_01E00DD0 *obj, Data_b046_01E00DD0 *data, s32 mode, Vec4f c) {
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
    func_01E00080_b225((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b225:01E01560 (B225_W_S), 591 insns, 1 copy (-O3,p): b709:01E02300's two-joint scene step with other times:
   tracks joints A/B and C/D before 220, pushes point A in z by 5 (side by flag), kicks A at 196 and C at 187..190 by
   the camera turn; at 211 / 193 bursts on C / A; trails, sparks and the 01E01EA0 swirl from 185..217; at 130/150 and
   121/140/160 ten embers on joints E / F */

typedef struct {
    u8 pad0[0x20];
    Vec4f d0;
    Vec4f d1;
    Vec4f c0;
    Vec4f c1;
    u8 pad60[0x2D0 - 0x60];
    Vec4f pos;
    u8 pad2E0[0x320 - 0x2E0];
    Vec4f q0;
    Vec4f q1;
    u8 pad340[0x31B0 - 0x340];
    Vec4f p0;
    Vec4f p1;
    u8 pad31D0[0x31F0 - 0x31D0];
    Vec4f r0;
    Vec4f r1;
    u8 pad3210[0x3384 - 0x3210];
    u8 col[4];
    u8 pad3388[0x33D0 - 0x3388];
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 pad33D8[2];
    s16 je;
    s16 jf;
    u8 pad33DE[4];
    s16 side;
    s16 flip;
    u8 pad33E6[2];
    s16 t;
    u8 pad33EA[0x36EC - 0x33EA];
    u8 trig[1];
} Scene_b225_01E01560;

#pragma optimization_level 3

static void func_01E01560_b225(Scene_b225_01E01560 *g) {
    extern s32 b225_01E01EA0(void);
    extern s32 b225_01E02120(void);
    extern s32 b225_01E02290(void);
    extern s32 b225_01E023F0(void);
    extern s32 b225_01E02540(void);
    extern s32 b225_01E02810(void);
    extern s32 b225_01E02A70(void);
    extern s32 b225_01E02BF0(void);
    extern s32 b225_01E02CD0(void);
    extern s32 b225_01E02E70(void);
    extern s32 b225_01E03120(void);
    extern s32 b225_01E033B0(void);
    extern void b225_01E04360(Scene_b225_01E01560 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f v;
    s32 a[4];
    s32 b[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t < 220) {
        func_001F5620(func_001F53A0(), g->ja, &g->p0);
    }
    if (g->t < 220) {
        func_001F5620(func_001F53A0(), g->jb, &g->q0);
    }
    if (g->t < 220) {
        g->d0.x = g->q0.x - g->p0.x;
        g->d0.y = g->q0.y - g->p0.y;
        g->d0.z = g->q0.z - g->p0.z;
    }
    if (g->t < 220) {
        func_001F5620(func_001F53A0(), g->jc, &g->p1);
    }
    if (g->t < 220) {
        func_001F5620(func_001F53A0(), g->jd, &g->q1);
    }
    if (g->t < 220) {
        g->d1.x = g->q1.x - g->p1.x;
        g->d1.y = g->q1.y - g->p1.y;
        g->d1.z = g->q1.z - g->p1.z;
    }
    if (g->flip) {
        g->p0.z -= 5.0f;
    } else {
        g->p0.z += 5.0f;
    }
    if (g->t < 194) {
        g->c0 = g->p0;
    }
    if (g->t < 212) {
        g->c1 = g->p1;
    }
    if (g->t >= 196 && g->t < 197) {
        func_001F6160(func_001F53A0(), a);
        g->p0.z += 3.0f * -func_00108030(g->trig, (s32)(a[1] / 180.0f) - 180, 1);
    }
    if (g->t >= 187 && g->t < 191) {
        func_001F6160(func_001F53A0(), b);
        g->p1.z += 3.0f * -func_00108030(g->trig, (s32)(b[1] / 180.0f) - 180, 1);
    }
    if (g->t < 8) {
        g->side = 0;
        b225_01E04360(g, b225_01E033B0, 0);
    }
    if (g->t == 1) {
        g->side = 1;
        b225_01E04360(g, b225_01E033B0, 0);
    }
    if (g->t == 211) {
        g->pos.x = g->p1.x;
        g->pos.y = g->p1.y;
        g->pos.z = g->p1.z;
        b225_01E04360(g, b225_01E02E70, 0);
        for (i = 0; i < 3; i++) {
            b225_01E04360(g, b225_01E02A70, 0);
        }
        for (i = 0; i < 10; i++) {
            b225_01E04360(g, b225_01E02CD0, 0);
        }
        g->side = 0;
        for (i = 0; i < 4; i++) {
            b225_01E04360(g, b225_01E02810, 0);
        }
        b225_01E04360(g, b225_01E02BF0, 0);
    }
    if (g->t == 193) {
        g->pos.x = g->p0.x;
        g->pos.y = g->p0.y;
        g->pos.z = g->p0.z;
        b225_01E04360(g, b225_01E02E70, 0);
        for (i = 0; i < 3; i++) {
            b225_01E04360(g, b225_01E02A70, 0);
        }
        for (i = 0; i < 10; i++) {
            b225_01E04360(g, b225_01E02CD0, 0);
        }
        g->side = 1;
        for (i = 0; i < 4; i++) {
            b225_01E04360(g, b225_01E02810, 0);
        }
        b225_01E04360(g, b225_01E02BF0, 0);
    }
    if (g->t >= 185 && g->t < 201) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
        b225_01E04360(g, b225_01E02120, 0);
    }
    if (g->t >= 200 && g->t < 218) {
        func_001F5620(func_001F53A0(), g->jd, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 1;
        b225_01E04360(g, b225_01E02120, 0);
    }
    if (g->t < 201 && g->t >= 192) {
        if (g->t == 192) {
            func_001F5620(func_001F53A0(), g->jb, &g->r0);
        }
        if (g->t % 2 == 0) {
            func_001F5620(func_001F53A0(), g->jb, &v);
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            g->side = 0;
            for (i = 0; i < 1; i++) {
                b225_01E04360(g, b225_01E023F0, 0);
            }
            g->pos.x = g->r0.x;
            g->pos.y = g->r0.y;
            g->pos.z = g->r0.z;
            for (i = 0; i < 1; i++) {
                b225_01E04360(g, b225_01E02540, 0);
            }
        }
        g->side = 0;
        b225_01E04360(g, b225_01E01EA0, 0);
        if (g->t == 192) {
            b225_01E04360(g, b225_01E03120, 0);
        }
    }
    if (g->t < 218 && g->t >= 210) {
        if (g->t == 210) {
            func_001F5620(func_001F53A0(), g->jd, &g->r1);
        }
        if (g->t % 2 == 1) {
            func_001F5620(func_001F53A0(), g->jd, &v);
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            g->side = 1;
            for (i = 0; i < 1; i++) {
                b225_01E04360(g, b225_01E023F0, 0);
            }
            g->pos.x = g->r1.x;
            g->pos.y = g->r1.y;
            g->pos.z = g->r1.z;
            for (i = 0; i < 1; i++) {
                b225_01E04360(g, b225_01E02540, 0);
            }
        }
        g->side = 1;
        b225_01E04360(g, b225_01E01EA0, 0);
        if (g->t == 210) {
            b225_01E04360(g, b225_01E03120, 0);
        }
    }
    if (g->t == 130 || g->t == 150) {
        func_001F5620(func_001F53A0(), g->je, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        for (i = 0; i < 10; i++) {
            b225_01E04360(g, b225_01E02290, 0);
        }
    }
    if (g->t == 121 || g->t == 140 || g->t == 160) {
        func_001F5620(func_001F53A0(), g->jf, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        for (i = 0; i < 10; i++) {
            b225_01E04360(g, b225_01E02290, 0);
        }
    }
}

#pragma optimization_level reset

/* OVL_WARM */

/* shape b225:01E01EA0, 159 insns: a purple swirl on the camera: colour 0x80/0x50/0xC8; on start it faces left or right by
   the camera's turn (func_001F6160), side = its old height, height 90, size 15; alpha up by 64 for 4 ticks, then down by 13
   until it ends; after scene time 187 (side 0) or 178 (side 1) it grows by 12; it rises by 2 (4 before time 171 / 161),
   drifts by 1..3 and turns by 5 */

typedef struct {
    u8 pad0[0x33E8];
    s16 time;
} Game_b225_01E01EA0;

typedef struct {
    u8 pad0[6];
    s16 side;
    u8 pad8[6];
    s16 drift;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 h34;
    s16 mode;
    s16 size;
    s16 ang;
} Obj_b225_01E01EA0;

static s32 func_01E01EA0_b225(Game_b225_01E01EA0 *g, Obj_b225_01E01EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 r[4];
    s16 d;

    d = 0;
    func_001076F0(o->col, 0x80, 0x50, 0xC8);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), r);
        if ((s32)(r[1] / 180.0f)) {
            o->w10 = -0x4000;
        } else {
            o->w10 = -0xC000;
        }
        o->w14 = 0;
        o->w18 = 0x3800;
        o->h34 = 0;
        o->side = o->h;
        o->h = 90;
        o->size = 15;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (o->side == 0) {
        if (g->time > 187) {
            o->size += 12;
        }
    }
    if (o->side == 1) {
        if (g->time > 178) {
            o->size += 12;
        }
    }
    if (o->side == 0) {
        if (g->time > 170) {
            d = 2;
        } else {
            d = 4;
        }
    }
    if (o->side == 1) {
        if (g->time > 160) {
            d = 2;
        } else {
            d = 4;
        }
    }
    o->t++;
    o->drift += (s16)(func_0019A5C8() % 3 + 1);
    o->h += d;
    o->ang += 5;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
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

static s32 func_01E02120_b225(void *arg0, Ember_b225_01E02120 *o) {
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

/* shape b225:01E02290, 87 insns: a white spark (size 60, frame 5) at two random angles drifting 16 a tick along its angle (sine table ctx+0x36EC): alpha 0x80 for 7 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[2];
    s16 hC;
    u8 padE[2];
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
} Glow_b225_01E02290;

typedef struct {
    u8 pad[0x36ec];
    u8 sin[1];
} Game_b225_01E02290;

static s32 func_01E02290_b225(Game_b225_01E02290 *g, Glow_b225_01E02290 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = 5;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->h8 = func_001A22C0(o->h8 + 16.0f * func_00108030(g->sin, o->ang, 0));
    o->hC = func_001A22C0(o->hC + 16.0f * func_00108030(g->sin, o->ang, 1));
    o->tick++;
    return 0;
}

/* shape b225:01E023F0, 84 insns: b573:01E02590 family: a purple spark at a random frame 0..7 that spins by a random 27..42 a tick (its old angle moved to the angle slot), size 0..9, hold 3..9 ticks: in by 56 up to 0x70, then out by 15 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
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
} Glow_b225_01E023F0;

static s32 func_01E023F0_b225(s32 arg0, Glow_b225_01E023F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 25;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x40, 8, 0x80);
        o->ang = o->h30;
        o->h30 = 0;
        o->hE = func_0019A5C8() % 16 + 27;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x70) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->tick++;
    return 0;
}

/* shape b225:01E02540, 88 insns: b225:01E023F0 family: an orange spark (size 14, random frame 0..3, random roll) spinning a random 20..37 a tick, rolling 5, size 0..9, held 8..27 ticks at 0x80, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
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
} Glow_b225_01E02540;

static s32 func_01E02540_b225(s32 arg0, Glow_b225_01E02540 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 14;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->w18 = func_0019A5C8() % 360;
        o->ang = o->h30;
        o->h30 = 0;
        o->hE = func_0019A5C8() % 18 + 20;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 20 + 8;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->w18 += 5;
    o->h30 += o->hE;
    o->tick++;
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

static s32 func_01E026A0_b225(void *arg0, Ember_b225_01E026A0 *o) {
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

/* shape b225:01E02810, 150 insns: b718:01E02F40 family blue flame (size 2, 13 from scene count 141; frame 0..3, turning 5 one way or the other by the old f30, f30 from 0 growing 4..13, +88 and deep blue after scene count 186 or 193 by direction; f8 0..9, life 9..24): full alpha then down by 10 */

typedef struct {
    u8 pad0[0x33E8];
    s16 count;
} Ctx_b225_01E02810;

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
} Fx_b225_01E02810;

static s32 func_01E02810_b225(Ctx_b225_01E02810 *g, Fx_b225_01E02810 *o) {
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

/* shape b225:01E02A70, 94 insns: on start 0x38 = 26, variant 0..7, random rotation 0x18, colour 0xA0 grey, random
   0x3A, speed 20..37 (0xE), 0x8 0..9, hold 3..9 (0x6); alpha grows by 0x38 (up to 0x70) during the hold,
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
} Fx_b225_01E02A70;

static s32 func_01E02A70_b225(s32 arg0, Fx_b225_01E02A70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 26;
        o->f34 = func_0019A5C8() % 8;
        o->rot = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->col, 0xA0, 0xA0, 0xA0);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 18 + 20;
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

/* shape b225:01E02BF0, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0xC0
   for the first 5 ticks, then fades out by 10 and stops */

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
} Flash_b225_01E02BF0;

static s32 func_01E02BF0_b225(s32 arg0, Flash_b225_01E02BF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xE6;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x20, 0x10, 0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 5) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b225:01E02CD0, 104 insns: a white spark (size 16, random frame 0..7, two random turns, angle 350..499, spin 10..27, size 0..9, 15 at +0xC), held 2 ticks: in by 88 up to 0xB0, then out by 13 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    u8 pad18[0x10];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b225_01E02CD0;

static s32 func_01E02CD0_b225(s32 arg0, Glow_b225_01E02CD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 16;
        o->kind = func_0019A5C8() % 8;
        o->w10 = (func_0019A5C8() >> 4) % 65535;
        o->w14 = (func_0019A5C8() >> 4) % 65535;
        func_001076F0(o->col, 0xA0, 0xA0, 0x10);
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 150 + 350;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 18 + 10;
        o->h8 = func_0019A5C8() % 10;
        o->hC = 15;
        o->h6 = 2;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0xB0) {
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

static s32 func_01E02E70_b225(void *arg0, Obj_b018_01E02480 *o) {
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

typedef struct {
    u8 pad0000[0x36EC];
    u8 tab[1];
} Mgr_b225_01E02F50;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b225_01E02F50;

static s32 func_01E02F50_b225(Mgr_b225_01E02F50 *m, Obj_b225_01E02F50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        o->h38 = 123;
        o->h34 = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->h30 = func_0019A5C8() % 360;
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    if (o->h32 % 3 == 1) {
        if (o->h34 < 7) {
            o->h34++;
        }
    }
    o->h32++;
    o->x = o->x + 14.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 14.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b225:01E03120, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x3380 is 1 */

typedef struct {
    u8 pad0[0x3180];
    f32 l0[4];
    f32 pos[3];
    u8 pad319C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad31AC[0x1D4];
    s32 state;
} Scene_b225_01E03120;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b225_01E03120;

static s32 func_01E03120_b225(Scene_b225_01E03120 *g, Obj_b225_01E03120 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 2.0f;
        g->l0[3] = 0.0f;
        g->f20 = 0.0f;
        g->range = 120.0f;
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

/* shape b225:01E032A0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3380 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3380];
    s32 state;
} Game_b225_01E032A0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b225_01E032A0;

static s32 func_01E032A0_b225(Game_b225_01E032A0 *g, Fade_b225_01E032A0 *o) {
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

static s32 func_01E03360_b225(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05100_b225;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05108_b225;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b225:01E033B0, 197 insns: b432:01E03680's screen sprite in the scene packet at ctx+0x3398, kind h30: kind 0 grey
   0x30, growing by 30 after tick 35, alpha up by 9 to 0x80 for 14 ticks, then down by 7 after tick 40; kind 1 pink
   (0xC0, 0x80, 0x80), alpha up by 13 to 0xC0 while the scene count ctx+0x33E8 is under 220, then down by 7 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b225_01E033B0;

typedef struct {
    f32 s, t;
    Xyz_b225_01E033B0 p;
} Tv_b225_01E033B0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b225_01E033B0 v[2];
} Tex_b225_01E033B0;

typedef struct {
    u8 pad[0x3398];
    Tex_b225_01E033B0 *pk;
    u8 pad339C[0x4C];
    s16 h33E8;
} Game_b225_01E033B0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b225_01E033B0;

static s32 func_01E033B0_b225(Game_b225_01E033B0 *g, Fx_b225_01E033B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        if (o->h30 == 0) {
            func_001076F0(o->col, 0x30, 0x30, 0x30);
        }
        if (o->h30 == 1) {
            func_001076F0(o->col, 0xC0, 0x80, 0x80);
        }
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = 0x93F8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = fx / 1024.0f;
    g->pk->v[0].t = fy / 512.0f;
    g->pk->v[1].s = (640.0f - fx) / 1024.0f;
    g->pk->v[1].t = (448.0f - fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->h30 == 0) {
        if (o->tick > 35) {
            o->f8 += 30;
            o->fA += 30;
        }
        if (o->tick < 14) {
            if (o->col[3] < 0x80) {
                o->col[3] += 9;
            }
        } else if (o->tick > 40) {
            if (o->col[3] > 8) {
                o->col[3] -= 7;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->h30 == 1) {
        if (g->h33E8 < 220) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 13;
            }
        } else if (o->tick > 40) {
            if (o->col[3] > 8) {
                o->col[3] -= 7;
            } else {
                o->mode = 0;
            }
        }
    }
    o->tick++;
    return 0;
}

/* shape b225:01E036D0, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-4 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x2FE0];
    s32 tex5[5];
} Scene_b225_01E036D0;

static void func_01E036D0_b225(s32 arg0, Scene_b225_01E036D0 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 5; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b225", func_01E03780_b225);

/* shape b225:01E04360, 72 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x33E2 and the two arguments; returns 1 if a
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
} Slot_b225_01E04360;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b225_01E04360 s[180];
    u8 pad3178[0x20C];
    u8 r, g, b, a;
    u8 pad3388[0x5A];
    s16 v;
} Pool_b225_01E04360;

static s32 func_01E04360_b225(Pool_b225_01E04360 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b225_01E04360 *s = NULL;
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

/* shape b225:01E04480 (B225PAINT_RAIN), 267 insns, 1 copy: b018:01E03760's cone, here of 12 quads 30 apart, hung on
   a point moved from joint B towards joint A (ctx+0x31B0 / ctx+0x320, joint o->h6) by o->hE fiftieths and scaled by
   size/250: latitudes from the tilt + 8 and the tilt, heights 30 x their sines, radius 90 at the tilt (capped at 160)
   and tilt+14; trig table ctx+0x36EC, depth ctx+0x33BC, ot ctx+0x338C; mode 0 only sets up the packet (texture
   0x97). The step folded into each delta (b709), the cap an if on (s16)tl, the sibling called by its real name */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b225_01E04480;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b225_01E04480;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b225_01E04480 c;
    struct {
        u64 tc;
        Xyz_b225_01E04480 p;
    } v[4];
} Pkt_b225_01E04480;

typedef struct {
    u8 pad0[0x320];
    Vec4f a[5];
    u8 pad370[0xC];
    void *texture;
    u8 pad380[0x31B0 - 0x380];
    Vec4f b[29];
    u8 pad3380[0xC];
    s32 ot;
    u8 pad3390[0x33BC - 0x3390];
    f32 dep;
    u8 pad33C0[0x36EC - 0x33C0];
    u8 trig[1];
} Ctx_b225_01E04480;

typedef struct {
    u8 pad0[6];
    s16 joint;
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
} Fan_b225_01E04480;

static void func_01E04480_b225(Ctx_b225_01E04480 *c, Fan_b225_01E04480 *o, Pkt_b225_01E04480 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b225_01E04480 func_00107740(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 j;
    s16 tl;
    s16 a;
    s16 t;
    f32 r0;
    f32 r1;
    f32 sn;
    f32 cs;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 s;

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
        func_01E00080_b225((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    dx = (c->a[o->joint].x - c->b[o->joint].x) / 50.0f * o->step;
    dy = (c->a[o->joint].y - c->b[o->joint].y) / 50.0f * o->step;
    dz = (c->a[o->joint].z - c->b[o->joint].z) / 50.0f * o->step;
    pos.x = c->b[o->joint].x;
    pos.y = c->b[o->joint].y;
    pos.z = c->b[o->joint].z;
    pos.x += dx;
    pos.y += dy;
    pos.z += dz;
    s = o->size;
    s /= 250.0f;
    func_00106DD0(&sc, s, s, s);
    func_00108EF0(m, &sc, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        quad[0].y = 30.0f * func_00108030(c->trig, tl + 8, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 30.0f * func_00108030(c->trig, o->tilt, 0);
        quad[3].y = quad[2].y;
        if ((s16)tl > 0xA0) {
            tl = 0xA0;
        }
        r0 = 90.0f * func_00108030(c->trig, tl, 1);
        r1 = 90.0f * func_00108030(c->trig, tl + 14, 1);
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

static void func_01E048B0_b225(Obj_b225_01E048B0 *o, Spr_b225_01E048B0 *s, void *p, s8 *tbl) {
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

static void func_01E04BF0_b225(Obj_b225_01E04BF0 *o, Spr_b225_01E04BF0 *s, Pkt_b225_01E04BF0 *p, s8 *tbl) {
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

/* shape b225:01E04F60, 73 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x3398, ot at
   0x3394), texture from func_001F53A0, then every used slot (0xB4 of 0x40 bytes at 0x478) whose
   callback is b225:01E033B0 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b225_01E04F60;

typedef struct {
    u8 pad0[0x24];
    void (*cb)(void *, void *);
    u8 pad28[0xE];
    s16 used;
    u8 pad38[0x8];
} Slot_b225_01E04F60;

typedef struct {
    u8 pad0[0x478];
    Slot_b225_01E04F60 slots[0xB4];
    u8 pad3178[0x21C];
    s32 ot;
    Pkt_b225_01E04F60 *pk;
} Scene_b225_01E04F60;

static void func_01E04F60_b225(Scene_b225_01E04F60 *g) {
    extern void b225_01E033B0(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b225_01E04F60 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0xB4; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b225_01E033B0) {
                b225_01E033B0(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}
