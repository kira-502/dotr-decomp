#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b052(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b052(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E005A0_b052(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00150_b052((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00920_b052(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00150_b052((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

static void func_01E00C50_b052(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

static Vec_b018_01E00EE0 func_01E00EE0_b052(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b018:01E01320: curved beam along func_01E00EE0_b052 spline points. Needs func_01E00EE0_b052 in the same file and
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

static void func_01E01320_b052(s32 unused, Beam_b018_01E01320 *an, Vec_b018_01E00EE0 *pts) {
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
                ab[0] = func_01E00EE0_b052(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E00EE0_b052(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E00EE0_b052(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E00EE0_b052(ctrl, 0, t);
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

/* shape b052:01E01760, 196 insns: the scene script of b052 (b115:01E01450's kind): scene colour red 0x80, counts
   g+0x387E; on tick 51 it stores joint A (g+0x386A) at g+0x36C0 and from 52 to 64 puts the burst point there; on
   tick 24 it spawns 0x1E02160 and 0x1E026C0; every tick two 0x1E01C90; on tick 26 sixteen 0x1E02550 on joint B
   (g+0x386C), then lifts the point by 1; on tick 76 it raises the scene flag g+0x387A on joint C (g+0x386E) and
   spawns 8 0x1E02550, 8 0x1E023C0, 30 0x1E02210, then 0x1E02080 and 0x1E02770 */

typedef struct {
    u8 pad0[0x2D0];
    f32 x;
    f32 y;
    f32 z;
    u8 pad2DC[0x36C0 - 0x2DC];
    f32 p[4];
    u8 pad36D0[0x3824 - 0x36D0];
    u8 col[4];
    u8 pad3828[0x386A - 0x3828];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 pad3870[0xA];
    s16 flag;
    u8 pad387C[2];
    s16 tick;
} Ctx_b052_01E01760;

static void func_01E01760_b052(Ctx_b052_01E01760 *g) {
    extern void b052_01E01C90();
    extern void b052_01E02080();
    extern void b052_01E02160();
    extern void b052_01E02210();
    extern void b052_01E023C0();
    extern void b052_01E02550();
    extern void b052_01E026C0();
    extern void b052_01E02770();
    extern void b052_01E03260(Ctx_b052_01E01760 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    f32 v[4];
    f32 cam[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick == 51) {
        func_001F5620(func_001F53A0(), g->ja, g->p);
    }
    if (g->tick > 51 && g->tick < 65) {
        func_001F5620(func_001F53A0(), g->ja, v);
        for (i = 0; i < 6; i++) {
            g->x = g->p[0];
            g->y = g->p[1];
            g->z = g->p[2];
        }
    }
    if (g->tick == 24) {
        b052_01E03260(g, b052_01E02160, 0);
    }
    if (g->tick == 24) {
        b052_01E03260(g, b052_01E026C0, 0);
    }
    b052_01E03260(g, b052_01E01C90, 0);
    b052_01E03260(g, b052_01E01C90, 0);
    if (g->tick == 26) {
        func_001F5620(func_001F53A0(), g->jb, v);
        g->x = v[0];
        g->y = *(f32 *)(u32)&v[1];
        g->z = v[2];
        g->flag = 1;
        for (i = 0; i < 16; i++) {
            b052_01E03260(g, b052_01E02550, 0);
        }
        g->y = 1.0f + v[1];
    }
    if (g->tick == 76) {
        func_001F5620(func_001F53A0(), g->jc, v);
        func_001F5F90(func_001F5380(), cam);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b052_01E03260(g, b052_01E02550, 0);
        }
    }
    if (g->tick == 76) {
        func_001F5620(func_001F53A0(), g->jc, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        g->flag = 1;
        for (i = 0; i < 8; i++) {
            b052_01E03260(g, b052_01E023C0, 0);
        }
        for (i = 0; i < 30; i++) {
            b052_01E03260(g, b052_01E02210, 0);
        }
        b052_01E03260(g, b052_01E02080, 0);
        b052_01E03260(g, b052_01E02770, 0);
    }
}

/* shape b018:01E01F60, 134 insns, 2 copies: a violet wisp: set up once (random heading, tilt -15..14); fades in to 0x60
   over 10 frames, then out; its size grows every other frame up to 18, its frame every third up to 7; x and z drift 10 along its heading, y 4 by
   its tilt, by a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0x3984];
    u8 trig[1];
} World_b018_01E01F60;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b018_01E01F60;

static s32 func_01E01A70_b052(World_b018_01E01F60 *w, Wisp_b018_01E01F60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->a3A = func_0019A5C8() % 360;
        o->frame = 0;
        o->a30 = func_0019A5C8() % 30 - 15;
        o->state = 2;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->h38 < 0x12) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* OVL_WARM */

/* shape b052:01E01C90, 148 insns: an orange spark on the line between two model joints (g+0x386C / 0x386E): on start
   size 6, a random step 0..11 along the line, a random spin, rise 7 - step / 2, frame 0..9, life 1..3; alpha 0x80 for its
   life, then down by 10 until it ends; it rises by its speed and sits step tenths of the way from joint 0 to joint 1 */

typedef struct {
    u8 pad0[0x386C];
    s16 j0;
    s16 j1;
} Game_b052_01E01C90;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 life;
    s16 frame;
    u8 padA[4];
    s16 rise;
    u8 pad10[8];
    s32 spin;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 f34;
    s16 mode;
    s16 size;
    s16 step;
} Obj_b052_01E01C90;

static s32 func_01E01C90_b052(Game_b052_01E01C90 *g, Obj_b052_01E01C90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[2][4];
    f32 dx;
    f32 dz;
    f32 dy;

    if (o->mode == 1) {
        o->size = 6;
        o->step = func_0019A5C8() % 12;
        o->f34 = 2;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->spin = func_0019A5C8() % 0xFFFF;
        o->h = 0;
        o->rise = 7 - (o->step >> 1);
        o->frame = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->t < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->h += o->rise;
    o->t++;
    func_001F5620(func_001F53A0(), g->j0, v[0]);
    func_001F5620(func_001F53A0(), g->j1, v[1]);
    dx = v[1][0] - v[0][0];
    dy = v[1][1] - v[0][1];
    dz = v[1][2] - v[0][2];
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    o->x = v[0][0] + dx * o->step;
    o->y = v[0][1] + dy * o->step;
    o->z = v[0][2] + dz * o->step;
    return 0;
}

/* shape b018:01E022E0, 101 insns, 2 copies: a dim arc flash facing away from the model: its turn set once from the model's
   heading (flipped past 180), its roll by side; fades in over 2 frames, then out; its sweep opens 8 a frame to
   160; fades out early when the scene's light is low */

typedef struct {
    u8 pad0[0x3820];
    s32 light;
} World_b018_01E022E0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 sweep;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Arc_b018_01E022E0;

static s32 func_01E01EE0_b052(World_b018_01E022E0 *w, Arc_b018_01E022E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    s32 r[4];

    func_001076F0(o->c0, 0x10, 0x10, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), r);
        if ((s32)(r[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = 0xFFFF4000;
        }
        o->rot[1] = 0;
        if (o->sweep == 0) {
            o->rot[2] = 0x2000;
        } else {
            o->rot[2] = -0x2000;
        }
        o->h34 = 0;
        o->sweep = 0x5A;
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
    if (o->sweep < 0xA0) {
        o->sweep += 8;
    }
    if (w->light < 0xF) {
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

static s32 func_01E02080_b052(void *arg0, Obj_b018_01E02480 *o) {
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

static s32 func_01E02160_b052(void *arg0, Obj_b018_01E02560 *o) {
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

static s32 func_01E02210_b052(s32 arg0, Spark_b018_01E02610 *o) {
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

/* shape b052:01E023C0, 97 insns, 3 copies: step of a drifting ember: on state 1 picks random seeds, angle, speed and
   lifetime and an orange colour; full alpha while young, then fades by 15 until it ends; drifts by its speed. */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    s32 w10;
    u8 pad14[4];
    s32 w18;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b052_01E023C0;

static s32 func_01E023C0_b052(void *arg0, Obj_b052_01E023C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 2;
        o->h34 = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0);
        o->w18 = func_0019A5C8() % 0xFFFF;
        o->w10 = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 10 + 5;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
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

static s32 func_01E02550_b052(s32 unused, Spark_b018_01E02950 *o) {
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

static s32 func_01E026C0_b052(s32 arg0, Glow_b018_01E02AC0 *o) {
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

/* shape b018:01E02B70, 93 insns, 2 copies: a scene light flash: sets the scene's light block once (level 128, colour 4,2,0, range 120,
   at the object's position), its strength rises by 0.2 to 1 then falls by 0.1; the light is switched off when
   the flash ends or the scene says so */

typedef struct {
    f32 level;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 range;
    f32 strength;
} Light_b018_01E02B70;

typedef struct {
    u8 pad0[0x3680];
    Light_b018_01E02B70 light;
    u8 pad36AC[0x174];
    s32 w3820;
} World_b018_01E02B70;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 falling;
    u8 pad32[4];
    s16 state;
} Flash_b018_01E02B70;

static s32 func_01E02770_b052(World_b018_01E02B70 *w, Flash_b018_01E02B70 *o) {
    extern void func_001F6C10(void *);

    if (o->state == 1) {
        w->light.level = 128.0f;
        w->light.r = 4.0f;
        w->light.g = 2.0f;
        w->light.b = 0;
        w->light.w20 = 0;
        w->light.range = 120.0f;
        w->light.strength = 0.0f;
        w->light.x = o->x;
        w->light.y = o->y;
        w->light.z = o->z;
        o->state = 2;
        o->falling = 0;
    }
    if (o->falling == 0) {
        if (w->light.strength < 1.0f) {
            w->light.strength += 0.2f;
        } else {
            o->falling = 1;
        }
    } else if (w->light.strength > 0.1f) {
        w->light.strength -= 0.1f;
    } else {
        o->state = 0;
    }
    if (o->state == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&w->light);
    }
    if (w->w3820 == 1) {
        o->state = 0;
    }
    return 0;
}

/* shape b018:01E02CF0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3820 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3820];
    s32 state;
} Game_b018_01E02CF0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b018_01E02CF0;

static s32 func_01E028F0_b052(Game_b018_01E02CF0 *g, Fade_b018_01E02CF0 *o) {
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

static s32 func_01E029B0_b052(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03B80_b052;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03B88_b052;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b052:01E02A00 (b052), 534 insns, 1 copy: b052 scene manager (b018:01E02E00's form): with a scene id (>= 0) it
   clears the scene, keeps the id, sets the 149-frame countdown, takes four joint handles and the root joint, looks up
   textures 0..2 and 13..15 and fills a 256-byte random table (-15..14); otherwise it runs the script, at frame 24
   fills both nine-point trails from joints 0 and 1, shifts the two trails, steps the 200 slots (0x1E02160 and
   0x1E026C0 written out in place), draws every live slot and returns 1 / 4 / 2 at frames 66 / 86 / 76, 8 once the
   countdown runs out */

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
} Slot_b052_01E02A00;

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
    Slot_b052_01E02A00 slot[200];
    u8 pad3678[0x58];
    Vec4f trB[10];
    Vec4f trA[10];
    u8 pad3810[0x10];
    s32 count;
    u8 pad3824[8];
    s32 ot;
    u8 pad3830[0x38];
    s16 j[4];
    u8 pad3870[6];
    s16 jG;
    u8 pad3878[4];
    s16 id;
    s16 frame;
    u8 pad3880[2];
    s8 jit[0x100];
    u8 pad3982[2];
    u8 crd[0x16C];
} Scene_b052_01E02A00;

static s32 func_01E02A00_b052(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_01E01760_b052();
    extern void func_01E00C50_b052();
    extern void b052_01E03380();
    extern void b052_01E03730();
    Scene_b052_01E02A00 *g = (Scene_b052_01E02A00 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    Vec4f pa;
    Vec4f pb;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;

    m = 0;
    g->ot80 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3AF0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x95;
        g->z310[0] = 0;
        g->z310[1] = 0;
        g->z310[2] = 0;
        g->j[0] = func_001F5560(func_001F53A0(), 0x19, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x4C, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0xE, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->jG = func_001F5560(func_001F5380(), 1, 1);
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 13; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E01760_b052(g, 0);
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
    func_01E00080_b052((Vec_b004_01E00B40 *)&g->trA[9], 10, g->j[0]);
    func_01E00080_b052((Vec_b004_01E00B40 *)&g->trB[9], 10, g->j[1]);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E01A70_b052) {
                func_01E01A70_b052((World_b018_01E01F60 *)g, (Wisp_b018_01E01F60 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01C90_b052) {
                func_01E01C90_b052((Game_b052_01E01C90 *)g, (Obj_b052_01E01C90 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01EE0_b052) {
                func_01E01EE0_b052((World_b018_01E022E0 *)g, (Arc_b018_01E022E0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02080_b052) {
                func_01E02080_b052(g, (Obj_b018_01E02480 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02160_b052) {
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
            if (g->slot[i].fn == func_01E02210_b052) {
                func_01E02210_b052((s32)g, (Spark_b018_01E02610 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E023C0_b052) {
                func_01E023C0_b052(g, (Obj_b052_01E023C0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02550_b052) {
                func_01E02550_b052((s32)g, (Spark_b018_01E02950 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E026C0_b052) {
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
            if (g->slot[i].fn == func_01E02770_b052) {
                func_01E02770_b052((World_b018_01E02B70 *)g, (Flash_b018_01E02B70 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E028F0_b052) {
                func_01E028F0_b052((Game_b018_01E02CF0 *)g, (Fade_b018_01E02CF0 *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E029B0_b052) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E03B80_b052;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E03B88_b052;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E01C90_b052) {
                g->tex88 = g->tex[15];
                func_00106080(rm, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                b052_01E03730(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E01EE0_b052) {
                b052_01E03380(g, &g->slot[i], buf, 0);
                b052_01E03380(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E02080_b052) {
                g->tex88 = g->tex[15];
                func_00106080(rm2, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                func_01E00C50_b052(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E02210_b052) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                func_01E005A0_b052((u8 *)g, (Obj_b018_01E005A0 *)&g->slot[i], (Pk_b018_01E005A0 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E023C0_b052) {
                g->tex88 = g->tex[1];
                func_00106080(rm4, 0xA, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                func_01E00920_b052((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E02550_b052) {
                g->tex88 = g->tex[15];
                func_00106080(rm5, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                func_01E00920_b052((u8 *)g, (Obj_b018_01E00920 *)&g->slot[i], (Pk_b018_01E00920 *)buf, g->jit);
            }
            if (g->slot[i].fn == func_01E026C0_b052) {
                func_01E01320_b052((s32)g, (Beam_b018_01E01320 *)&g->slot[i], (Vec_b018_01E00EE0 *)g->trB);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x42) {
        return 1;
    }
    if (g->frame == 0x56) {
        return 4;
    }
    if (g->frame == 0x4C) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b018:01E03640, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x387A and the two arguments; returns 1 if a
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
} Slot_b018_01E03640;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b018_01E03640 s[200];
    u8 pad3678[0x1AC];
    u8 r, g, b, a;
    u8 pad3828[0x52];
    s16 v;
} Pool_b018_01E03640;

static s32 func_01E03260_b052(Pool_b018_01E03640 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b018_01E03640 *s = NULL;
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

/* shape b018:01E03760, 233 insns, 2 copies: a cone of 9 quads (b112:01E03C50 family): latitudes from the object's tilt (capped
   at 160) and tilt+30, heights 45 x sines of tilt and tilt+35, inner and outer radius 3 and 20, each segment 40
   wide and 40 apart; mode 0 only sets up the packet (texture 0x97, flat colour). Texture corners by the module
   helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b018_01E03760;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b018_01E03760;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b018_01E03760 c;
    struct {
        u64 tc;
        Xyz_b018_01E03760 p;
    } v[4];
} Pkt_b018_01E03760;

typedef struct {
    u8 pad0[0x37C];
    void *texture;
    u8 pad380[0x34AC];
    s32 ot;
    u8 pad3830[0x24];
    f32 dep;
    u8 pad3858[0x12C];
    u8 trig[1];
} Ctx_b018_01E03760;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
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
} Fan_b018_01E03760;

static void func_01E03380_b052(Ctx_b018_01E03760 *c, Fan_b018_01E03760 *o, Pkt_b018_01E03760 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b018_01E03760 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
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
    f32 r2;
    f32 r3;
    f32 sn;
    f32 cs;

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
        func_01E00150_b052((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, NULL, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        if (o->tilt > 0xA0) {
            tl = 0xA0;
        }
        quad[0].y = 45.0f * func_00108030(c->trig, o->tilt, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 45.0f * func_00108030(c->trig, o->tilt + 0x23, 0);
        quad[3].y = quad[2].y;
        r0 = 20.0f * func_00108030(c->trig, tl, 1);
        t2 = tl + 0x1E;
        r1 = 20.0f * func_00108030(c->trig, t2, 1);
        r2 = 3.0f * func_00108030(c->trig, tl, 1);
        r3 = 3.0f * func_00108030(c->trig, t2, 1);
        a = 0;
        for (k = 0; k < 9; k++) {
            t = o->ang + a;
            sn = func_00108030(c->trig, t, 1);
            cs = func_00108030(c->trig, t, 0);
            quad[2].x = sn * r2;
            quad[2].z = cs * r1;
            quad[0].x = sn * r3;
            quad[0].z = cs * r0;
            t = o->ang + 0x28 + a;
            sn = func_00108030(c->trig, t, 1);
            cs = func_00108030(c->trig, t, 0);
            quad[3].x = sn * r2;
            quad[3].z = cs * r1;
            quad[1].x = sn * r3;
            quad[1].z = cs * r0;
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 0x28;
        }
    }
    }
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

static void func_01E03730_b052(Obj_b052_01E03730 *o, Spr_b052_01E03730 *s, Pkt_b052_01E03730 *p, s8 *tbl) {
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
    func_01E00150_b052((Pk_b008_01E00080 *)p, &o->rect, 0);
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
