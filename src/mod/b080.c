#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b080(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b080(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E005A0_b080(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b080((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00780_b080(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b080((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00B00_b080(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00150_b080((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00E30_b080(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

/* shape b080:01E010C0 (KPOINT_RAIN_2), 278 insns, 1 copy: rain streaks: per segment, a ring of 7 angles (30 apart) x
   4 offset quads drawn between consecutive points, lifted along y by the first point's height */

typedef struct {
    u8 r, g, b, a;
} Col_b080_01E010C0;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[0xCC];
    u8 trig[4];
} Own_b080_01E010C0;

typedef struct {
    u8 pad0[6];
    s16 n;
    u8 pad8[0x20];
    Col_b080_01E010C0 col;
} Fx_b080_01E010C0;

typedef struct {
    u32 tag[2];
    u8 pk[0x94];
} Buf_b080_01E010C0;

static void func_01E010C0_b080(Own_b080_01E010C0 *g, Fx_b080_01E010C0 *o, Vec4f *pts, Vec4f *base) {
    extern void func_001092E0();
    extern void func_001094F0();
    extern void func_00107990();
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630();
    extern void func_002075F0();
    extern s32 func_00207500(void);
    f32 depth[4];
    Vec4f q[4];
    Vec4f v[2];
    Buf_b080_01E010C0 buf;
    Col_b080_01E010C0 col;
    s16 n;
    s32 j;
    u8 *p;
    s32 ot;
    s32 i;
    s32 k;
    s32 last;
    s32 cnt;
    s16 a;
    s32 ang;
    f32 t;
    f32 r;
    f32 z;
    f32 h;
    f32 y;

    ot = func_00207500();
    n = o->n;
    t = 0.0f;
    p = buf.pk;
    func_001092E0(p, 0);
    func_001094F0(p);
    cnt = n;
    col = o->col;
    v[0] = *pts;
    v[1] = *base;
    v[0].x -= v[1].x;
    v[0].y -= v[1].y;
    v[0].z -= v[1].z;
    v[0].x = g->x;
    v[0].y = -v[0].y;
    v[0].z = g->z;
    i = 0;
    last = cnt - 1;
    h = v[0].z;
    y = v[0].y;
    goto test;
loop:
    {
        a = 0;
        func_00107990(p, &col, 1);
        col.a -= o->col.a / cnt;
        func_00107990(p, &col, 2);
        for (k = 0, ang = -90; k < 7; k++, ang += 30) {
            r = v[0].x * func_00108030(g->trig, ang, 0);
            z = h * func_00108030(g->trig, ang, 1);
            for (j = 0; j < 4; j++) {
                q[0].x = pts->x;
                q[0].y = pts->y;
                q[0].z = pts->z;
                q[1].x = pts->x;
                q[1].y = pts->y;
                q[1].z = pts->z;
                q[2].x = pts[1].x;
                q[2].y = pts[1].y;
                q[2].z = pts[1].z;
                q[3].x = pts[1].x;
                q[3].y = pts[1].y;
                q[3].z = pts[1].z;
                func_00107070(q, 0, r);
                func_00107070(q, 2, z);
                func_00107070(q, 1, y);
                if (j == 0) {
                    q[0].z += 0.2f;
                    q[2].z += 0.2f;
                } else if (j == 1) {
                    q[0].z -= 0.2f;
                    q[2].z -= 0.2f;
                } else if (j == 2) {
                    q[0].x += 0.2f;
                    q[2].x += 0.2f;
                } else if (j == 3) {
                    q[0].x -= 0.2f;
                    q[2].x -= 0.2f;
                }
                if (func_00205630(q, 0x70000000, 0, p, depth)) {
                    func_002075F0(p, ot, 0);
                }
                a += 30;
            }
        }
        pts++;
        t += 1.0f;
        i++;
    }
test:
    if (i < last) goto loop;
}


typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E01520_b080(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* several callees are called with other argument lists than functions.h gives: hide those prototypes */

/* shape b080:01E01960 (SPR_Paint_1), 226 insns: draw a flat sprite 150 units in front of the camera, turned to face
   it: the b205:01E01F90 packet (texture 0.625 x 0.875, colour 0x80) at the camera position pushed out along the
   camera's heading, a quad of half-size o->size, z forced to 0xFFFFFF */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b080_01E01960;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b080_01E01960;

typedef struct {
    f32 s, t;
    Xyz_b080_01E01960 p;
} Vtx_b080_01E01960;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b080_01E01960 c;
    Vtx_b080_01E01960 v[2];
    u64 tail;
} Pkt_b080_01E01960;

typedef struct {
    u8 pad0[0x38];
    s16 size;
} Obj_b080_01E01960;

typedef struct {
    u8 pad0[0xD8];
    u8 table[0x10];
} Scn_b080_01E01960;

static inline void tag_b080_01E01960(Pkt_b080_01E01960 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static void func_01E01960_b080(Scn_b080_01E01960 *w, Obj_b080_01E01960 *o) {
    extern void func_00108EF0();
    extern void func_001FAFB0();
    extern void func_00205C40();
    extern void func_001F9D30();
    extern f32 *func_001F9AD0();
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108950();
    extern s32 func_00205630();
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    extern void func_001FAF60(s32);
    f32 quad[4][4];
    f32 pos[4];
    f32 dir[4];
    f32 m[4][4];
    s32 rot[4];
    s32 ang2[4];
    f32 z[4];
    Pkt_b080_01E01960 pkt __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    s64 h;
    f32 *cam;
    s32 s;

    func_00207500();
    s = func_00207F60();
    tag_b080_01E01960((Pkt_b080_01E01960 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0x80;
    pkt.c.g = 0x80;
    pkt.c.b = 0x80;
    pkt.c.a = 0x80;
    pkt.c.q = 1.0f;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_00208460();
    func_00208800(func_00209E50(), 0, &a, b);
    func_00208460();
    func_001F9D30(0);
    cam = func_001F9AD0(0);
    func_001FAF60(0);
    pos[0] = cam[0];
    pos[1] = cam[1];
    pos[2] = cam[2];
    func_001FAFB0(0, rot);
    h = rot[1] / 180;
    h -= 180;
    dir[0] = 50.0f * func_00108030(w->table, h, 0);
    dir[2] = 50.0f * func_00108030(w->table, h, 1);
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = 150.0f;
    ang2[1] = h;
    func_00108950(dir, ang2, 0, w->table);
    dir[0] *= -1.0f;
    h = rot[0] / 180;
    ang2[0] = h;
    func_00108950(dir, ang2, 1, w->table);
    pos[1] += dir[1];
    pos[2] += dir[2];
    pos[0] += dir[0];
    func_00205C40(rot);
    func_00108EF0(m, 0, rot, pos);
    quad[0][0] = -o->size;
    quad[0][1] = o->size;
    quad[0][2] = 0.0f;
    quad[1][0] = o->size;
    quad[1][1] = -o->size;
    quad[1][2] = 0.0f;
    if (func_00205630(quad, 0x70000000, m, &pkt, z) != 0) {
        pkt.v[0].p.z = 0xFFFFFF;
        pkt.v[1].p.z = 0xFFFFFF;
        func_002075F0(&pkt, 0, 0);
        func_00207FD0(s, func_00207500(), 0);
    }
}

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b080:01E01CF0, 276 insns: b019:01E01BD0's scene step for module b080 (tick g+0x2D46, scene colour turned
   red-black): marks joint 0x2D2A at tick 51 and holds the point there until 64; flag 0x2D42 off with 0x1E02680 at 178,
   back on at 192; eight 0x1E023D0 at joint 0x2D2E on ticks 27/66/97/130/185/270 and at joint 0x2D30 on ticks
   46/80/114/157/185/270; eight 0x1E02AA0 at the joint over the model on ticks 186/187, and on 186 eight 0x1E02910,
   twenty 0x1E02760, twenty 0x1E02220, 0x1E025A0 and 0x1E02C70; a 100 x sine sway turning 5 a tick */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x2A40 - 0x2E0];
    Vec4f mark;
    u8 pad2A50[0x2CD0 - 0x2A50];
    f32 sway;
    u8 pad2CD4[0x10];
    u8 col[4];
    u8 pad2CE8[0x2D2A - 0x2CE8];
    s16 ja;
    u8 pad2D2C[2];
    s16 jb;
    s16 jc;
    u8 pad2D32[0xC];
    s16 ang;
    u8 pad2D40[2];
    s16 flag;
    u8 pad2D44[2];
    s16 t;
    u8 pad2D48[0x2E4C - 0x2D48];
    u8 trig[1];
} Scene_b080_01E01CF0;

static void func_01E01CF0_b080(Scene_b080_01E01CF0 *g) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void b080_01E02220(void);
    extern void b080_01E023D0(void);
    extern void b080_01E025A0(void);
    extern void b080_01E02680(void);
    extern void b080_01E02760(void);
    extern void b080_01E02910(void);
    extern void b080_01E02AA0(void);
    extern void b080_01E02C70(void);
    extern s32 b080_01E03AA0(Scene_b080_01E01CF0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v[2];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 51) {
        func_001F5620(func_001F53A0(), g->ja, &g->mark);
    }
    if (g->t > 51 && g->t < 65) {
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        for (i = 0; i < 6; i++) {
            g->pos.x = g->mark.x;
            g->pos.y = g->mark.y;
            g->pos.z = g->mark.z;
        }
    }
    if (g->t == 178) {
        g->flag = 0;
        b080_01E03AA0(g, (s32)b080_01E02680, 0);
    }
    if (g->t == 192) {
        g->flag = 1;
    }
    if (g->t == 27 || g->t == 66 || g->t == 97 || g->t == 130 || g->t == 185 || g->t == 270) {
        func_001F5620(func_001F53A0(), g->jb, &v[0]);
        g->pos.x = v[0].x;
        g->pos.y = v[0].y;
        g->pos.z = v[0].z;
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b080_01E03AA0(g, (s32)b080_01E023D0, 0);
        }
    }
    if (g->t == 46 || g->t == 80 || g->t == 114 || g->t == 157 || g->t == 185 || g->t == 270) {
        func_001F5620(func_001F53A0(), g->jc, &v[0]);
        g->pos.x = v[0].x;
        g->pos.y = v[0].y;
        g->pos.z = v[0].z;
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b080_01E03AA0(g, (s32)b080_01E023D0, 0);
        }
    }
    if (g->t == 186 || g->t == 187) {
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5F90(func_001F5380(), &v[1]);
        g->pos.x = v[0].x;
        g->pos.y = v[0].y;
        g->pos.z = v[1].z;
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b080_01E03AA0(g, (s32)b080_01E02AA0, 0);
        }
    }
    if (g->t == 186) {
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5F90(func_001F5380(), &v[1]);
        g->pos.x = v[0].x;
        g->pos.y = v[0].y;
        g->pos.z = v[1].z;
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b080_01E03AA0(g, (s32)b080_01E02910, 0);
        }
        for (i = 0; i < 20; i++) {
            b080_01E03AA0(g, (s32)b080_01E02760, 0);
        }
        for (i = 0; i < 20; i++) {
            b080_01E03AA0(g, (s32)b080_01E02220, 0);
        }
        b080_01E03AA0(g, (s32)b080_01E025A0, 0);
        b080_01E03AA0(g, (s32)b080_01E02C70, 0);
    }
    g->sway = 100.0f * func_00108030(g->trig, g->ang, 0);
    g->ang += 5;
    if (g->ang >= 360) {
        g->ang %= 360;
    }
}

/* shape b080:01E02140, 55 insns: colour (0xFF,0xF0,0xFF); on start f38 50, random direction, f34 0, f30 random
   -15..14; alpha grows by 0x26 (below 0xC0) for 5 ticks; resets f0/f2/f4 to (0, 20, 0) every tick */

typedef struct {
    s16 f0, f2, f4;
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 dir;
} Glow_b080_01E02140;

static s32 func_01E02140_b080(s32 arg0, Glow_b080_01E02140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0xFF, 0xF0, 0xFF);
    if (o->mode == 1) {
        o->f38 = 50;
        o->dir = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x26;
        }
    }
    o->tick++;
    o->f0 = 0;
    o->f2 = 20;
    o->f4 = 0;
    return 0;
}

/* shape b080:01E02220, 106 insns: on start 0x38 = 10, variant 0, colour 0x30 grey, random headings 0x30 and 0x3A, speed
   3..17 (0xE); alpha 0x70 for 10 ticks, then fades by 10 and stops; it drifts by its speed a tick (x by the cosine of 0x3A, y by the
   sine of 0x30, z by the sine of 0x3A, game table 0x2E4C) */

typedef struct {
    u8 pad0[0x2E4C];
    u8 trig[1];
} Game_b080_01E02220;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b080_01E02220;

static s32 func_01E02220_b080(Game_b080_01E02220 *g, Fx_b080_01E02220 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 10;
        o->f34 = 0;
        func_001076F0(o->col, 0x30, 0x30, 0x30);
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 15 + 3;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x70;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->x = func_001A22C0(o->x + o->speed * func_00108030(g->trig, o->f3A, 0));
    o->y = func_001A22C0(o->y + o->speed * func_00108030(g->trig, o->f30, 1));
    o->z = func_001A22C0(o->z + o->speed * func_00108030(g->trig, o->f3A, 1));
    return 0;
}

/* shape b080:01E023D0, 115 insns: a dark drifting mote (b045:01E03130 shape): frame 65, random turn and angle; alpha 0x70 for 10
   frames, then down by 10; sub-frame steps up to 7 every third frame; drifts 10 along its angle and bobs 4 by its turn */

typedef struct {
    u8 pad0[0x2E4C];
    u8 sin[1];
} Game_b080_01E023D0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b080_01E023D0;

static s32 func_01E023D0_b080(Game_b080_01E023D0 *g, Obj_b080_01E023D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0x41;
        o->sub = 0;
        func_001076F0(o->c0, 0x10, 0x10, 0x10);
        o->turn = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 0xA) {
        o->c0[3] = 0x70;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 10.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 4.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 10.0f * func_00108030(g->sin, o->ang, 1));
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

static s32 func_01E025A0_b080(void *arg0, Obj_b018_01E02480 *o) {
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

/* shape b080:01E02680, 54 insns: an orange flash: colour 0x80/0x40/8; set up once (frame 5, full-alpha time 10 for
   kind 0, 7 for kind 1), full alpha until then, then fades out by 0x1D */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hold;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b080_01E02680;

static s32 func_01E02680_b080(void *arg0, Obj_b080_01E02680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x80, 0x40, 8);
    if (o->state == 1) {
        o->h38 = 5;
        if (o->kind == 0) {
            o->hold = 0xA;
        }
        if (o->kind == 1) {
            o->hold = 7;
        }
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    o->h6 = 0xA;
    o->t++;
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

static s32 func_01E02760_b080(s32 arg0, Spark_b018_01E02610 *o) {
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

static s32 func_01E02910_b080(s32 unused, Spark_b018_01E027C0 *o) {
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

static s32 func_01E02AA0_b080(s32 unused, Spark_b018_01E02950 *o) {
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

/* shape b080:01E02C10, 23 insns: a glow start: on mode 1 set f38 = 0x14, colour (0x10,0x10,0x10), alpha 0x20, mode 2 */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[0xA];
    s16 mode;
    s16 f38;
} Glow_b080_01E02C10;

static s32 func_01E02C10_b080(s32 arg0, Glow_b080_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        o->col[3] = 0x20;
        o->mode = 2;
    }
    return 0;
}

/* shape b080:01E02C70, 93 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 120, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x2CE0 is 1 */

typedef struct {
    u8 pad0[0x2A00];
    f32 l0[4];
    f32 pos[3];
    u8 pad2A1C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad2A2C[0x2B4];
    s32 state;
} Scene_b080_01E02C70;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b080_01E02C70;

static s32 func_01E02C70_b080(Scene_b080_01E02C70 *g, Obj_b080_01E02C70 *o) {
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

/* shape b080:01E02DF0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2CE0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2CE0];
    s32 state;
} Game_b080_01E02DF0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b080_01E02DF0;

static s32 func_01E02DF0_b080(Game_b080_01E02DF0 *g, Fade_b080_01E02DF0 *o) {
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

static s32 func_01E02EB0_b080(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04000_b080;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04008_b080;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b080:01E02F00, 97 insns: a scrolling full-screen sprite: one grey sprite across the screen, shifted sideways
   by the scene scroll (0x2CD0), its texture window 0..0.625 x 0..0.875; drawn in its own draw context */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b080_01E02F00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b080_01E02F00;

typedef struct {
    f32 s, t;
    Xyz_b080_01E02F00 p;
} Vtx_b080_01E02F00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b080_01E02F00 c;
    Vtx_b080_01E02F00 v[2];
    u64 tail;
} Pkt_b080_01E02F00;

typedef struct {
    u8 pad0000[0x2CD0];
    f32 scroll;
} Scene_b080_01E02F00;

static inline void tag_b080_01E02F00(Pkt_b080_01E02F00 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E02F00_b080(Scene_b080_01E02F00 *g) {
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b080_01E02F00 pkt __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    s32 s;
    s16 h;

    s = func_00207F60();
    h = g->scroll;
    tag_b080_01E02F00((Pkt_b080_01E02F00 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0x80;
    pkt.c.g = 0x80;
    pkt.c.b = 0x80;
    pkt.c.a = 0x80;
    pkt.c.q = 1.0f;
    pkt.v[0].p.x = (h + 0x6C0) * 16 - 8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = (h + 0x940) * 16 - 8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_00208460();
    func_00208800(func_00209E50(), 0, &a, b);
    func_00208460();
    func_002075F0(&pkt, 0, 0);
    func_00207FD0(s, func_00207500(), 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b080", func_01E03090_b080);

/* shape b080:01E03AA0, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2D42 and the two arguments; returns 1 if a
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
} Slot_b080_01E03AA0;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b080_01E03AA0 s[150];
    u8 pad29F8[0x2EC];
    u8 r, g, b, a;
    u8 pad2CE8[0x5A];
    s16 v;
} Pool_b080_01E03AA0;

static s32 func_01E03AA0_b080(Pool_b080_01E03AA0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b080_01E03AA0 *s = NULL;
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

/* several callees are called with other argument lists than functions.h gives: hide those prototypes */

/* shape b080:01E03BC0, 113 insns: set up the draw matrix of a flat sprite: screen-space (mode 0) or billboarded
   30 units in front of the camera, scaled by o->size */

typedef struct Obj_b080_01E03BC0 {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[8];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Obj_b080_01E03BC0;

typedef struct Scn_b080_01E03BC0 {
    u8 pad0[0x37C];
    void *tex;
    u8 pad380[0x2ACC];
    u8 table[0x10];
} Scn_b080_01E03BC0;

static void func_01E03BC0_b080(Scn_b080_01E03BC0 *w, Obj_b080_01E03BC0 *o, void *pk, s32 mode) {
    extern void func_00106080();
    extern void func_00109270();
    extern void func_00108EF0();
    extern void func_00108F90();
    extern void func_001FAFB0();
    extern void func_00205C40();
    extern f32 *func_001F9D30();
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    u8 *ot;
    f32 *cam;
    s16 ang;
    f32 m3[4][4];
    Vec4f pos;
    f32 m[4];
    f32 m2[4][4];
    s32 rot[4];

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(m, 0x9B, o->h34, m);
        func_00109270(pk, 0, 0);
        func_00107790(pk, o->col, 0);
        func_00108500(pk, m, 0);
        func_00208700(pk, w->tex, 1);
        return;
    }
    cam = func_001F9D30(0);
    func_001FAF60(0);
    pos.x = cam[0];
    pos.y = cam[1];
    pos.z = cam[2];
    func_001FAFB0(0, rot);
    ang = rot[1] / 180;
    pos.x += 30.0f * func_00108030(w->table, ang, 0);
    pos.z += 30.0f * func_00108030(w->table, ang, 1);
    func_00205C40(rot);
    func_00108EF0(m2, 0, rot, &pos);
    func_00108CE0(m3, (f32)o->size, (f32)o->size);
    func_00108F90(m3, pk, m2, ot);
}

/* shape b080:01E03D90, 128 insns: b117:01E02C00-family sprite draw in two passes: with mode 0 it sets the material
   (texture frame 0x83 at +0x34, colour, scene texture at 0x374); otherwise a tenth-scale matrix at position + drift / 10
   (the z offset reuses the y drift, divided twice, as in the original) and four size x size quads, each sent at its
   depth when it lands on screen */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b080_01E03D90;

typedef struct {
    u8 pad0[0x374];
    s32 tex;
} Scene_b080_01E03D90;

static void func_01E03D90_b080(Scene_b080_01E03D90 *g, Fx_b080_01E03D90 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    Vec4f quad[4];
    Vec4f scale;
    f32 pos[4];
    f32 rm[4];
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    s32 v;
    s16 i;
    f32 t;

    v = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x83, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        func_00205C40((s32)rot);
        t = o->dx;
        t /= 10.0f;
        pos[0] = o->x;
        pos[0] += t;
        t = o->dy;
        t /= 10.0f;
        pos[1] = o->y;
        pos[1] += t;
        pos[2] = o->dz;
        t /= 10.0f;
        pos[2] = o->z;
        pos[2] += t;
        func_00108EF0(m, &scale, rot, pos);
        for (i = 0; i < 4; i++) {
            func_00108D60(quad, o->size, o->size, i);
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, v, func_001A23B0(depth[0]));
            }
        }
    }
}
