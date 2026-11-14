#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b134(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b134(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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

static Vec_b018_01E00EE0 func_01E003E0_b134(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b134:01E00820, 365 insns, 5 copies: draws a ribbon between two point trails: each segment is 4 spline quads
   (module curve function, shape b018:01E00EE0) from the first trail to the second, colours from two
   colours whose alpha fades along the ribbon; the first segment runs on local copies (second trail's
   first point doubled). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b134_01E00820;

typedef struct {
    Rgbaq_b134_01E00820 c;
    u64 uv;
    u64 xyz;
} Vtx_b134_01E00820;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b134_01E00820 v[4];
    u8 tail[0x20];
} Pkt_b134_01E00820;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b134_01E00820;

typedef struct {
    u8 r, g, b, a;
} C4_b134_01E00820;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b134_01E00820 col0;
    C4_b134_01E00820 col1;
} Rib_b134_01E00820;

static void func_01E00820_b134(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
    extern Rgbaq_b134_01E00820 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[4];
    Vec_b018_01E00EE0 B[4];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b134_01E00820 pkt __attribute__((aligned(8)));
    C4_b134_01E00820 c0;
    C4_b134_01E00820 c1;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b134_01E00820 *p;
    s32 ot;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b134_01E00820 *)(s32)&pkt;
    func_00109270(p, 0, 0);
    pkt.v[0].c = func_00107740(&s->col0);
    pkt.v[1].c = func_00107740(&s->col1);
    pkt.v[2].c = func_00107740(&s->col0);
    pkt.v[3].c = func_00107740(&s->col1);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    c0 = s->col0;
    c1 = s->col1;
    a4[0] = pa[0];
    a4[1] = pa[1];
    a4[2] = pa[2];
    a4[3] = pa[3];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 2; k++) {
        p->v[0].c = func_00107740(&c0);
        p->v[1].c = func_00107740(&c1);
        c0.a -= (u8)(s->col0.a / (n - 1));
        c1.a -= (u8)(s->col1.a / (n - 1));
        p->v[2].c = func_00107740(&c0);
        p->v[3].c = func_00107740(&c1);
        t = 0.0f;
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A[0] = func_01E003E0_b134(pa, 0, t);
                B[0] = func_01E003E0_b134(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E003E0_b134(pa, 0, t);
                B[1] = func_01E003E0_b134(pq, 0, t);
            } else {
                A[0] = func_01E003E0_b134(a4, 0, t);
                B[0] = func_01E003E0_b134(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E003E0_b134(a4, 0, t);
                B[1] = func_01E003E0_b134(b4, 0, t);
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
        pa++;
    }
}

/* shape b134:01E00DE0, 254 insns: b476:01E017C0's ring of 9 textured quads, side 0 drawing only the quads behind
   (z < 0), side 1 only those in front */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[4];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b134_01E00DE0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
    s16 ang;
} Ring_b134_01E00DE0;

static void func_01E00DE0_b134(Obj_b134_01E00DE0 *o, Ring_b134_01E00DE0 *s, s32 side) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    s32 n;
    s32 k;
    s32 t;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col, 0);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, NULL, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        t = s->ang + a;
        quad[2].x = s->size * func_00108030(o->xD8, t, 1);
        quad[2].z = s->size * func_00108030(o->xD8, t, 0);
        quad[0].x = (s->size + 20) * func_00108030(o->xD8, t, 1);
        quad[0].z = (s->size + 20) * func_00108030(o->xD8, t, 0);
        t = a + (s->ang + 2);
        quad[3].x = s->size * func_00108030(o->xD8, t, 1);
        quad[3].z = s->size * func_00108030(o->xD8, t, 0);
        quad[1].x = (s->size + 20) * func_00108030(o->xD8, t, 1);
        quad[1].z = (s->size + 20) * func_00108030(o->xD8, t, 0);
        func_00109100(quad, s->rot, 0, o->xD8);
        func_00109100(quad, s->rot, 1, o->xD8);
        func_00109100(quad, s->rot, 2, o->xD8);
        if (side == 0) {
            if (quad[0].z < 0.0f) {
                if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                    for (n = 0; n < o->count + 1; n++) {
                        func_002075F0(p, o->ot, (u32)depth[0]);
                    }
                }
            }
        } else if (quad[0].z > 0.0f && func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        }
        a += 0x28;
    }
}

/* shape b134:01E011E0 (IWTusk1), 315 insns, 1 copy: a tusk along one point trail: each segment is 4 spline
   steps (module curve, shape b018:01E00EE0), each drawn as two crossed quads of width h38 / 10 (one widened in z, one
   in x), scaled, the colour's alpha falling by a / (3 n) per step; the first segment runs on local copies (first
   point doubled); b018:01E01760's form (ab[0] direct, ab[1] through named temps), n - 1 and n * 3 written inline, pts
   aligned(16) */

typedef struct {
    u8 r, g, b, a;
} C4_b134_01E011E0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b134_01E011E0 col;
    u8 pad2C[0xC];
    s16 width;
} Tusk_b134_01E011E0;

static void func_01E011E0_b134(void *o, Tusk_b134_01E011E0 *s, Vec_b018_01E00EE0 *pts __attribute__((aligned(16))), Vec_b018_01E00EE0 *scale) {
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 sc;
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth[4];
    Vec_b018_01E00EE0 t0;
    Vec_b018_01E00EE0 t1;
    u8 pkt[0x94] __attribute__((aligned(8)));
    C4_b134_01E011E0 c;
    s32 k;
    s32 j;
    Vec_b018_01E00EE0 *pq;
    s32 m;
    u8 *p;
    s16 n;
    s32 ot;
    f32 t;
    f32 w;
    s32 a;

    sc = *scale;
    w = s->width;
    ot = (s32)func_00207500();
    n = s->n;
    w /= 10.0f;
    p = pkt;
    func_001094F0(p);
    func_00107990(p, &s->col, 0);
    func_001092E0(p, 0);
    func_001094F0(p);
    c = s->col;
    a4[0] = pts[0];
    a4[1] = pts[0];
    a4[2] = pts[1];
    a4[3] = pts[2];
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pq = pts + ((s16)k - 1);
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                ab[0] = func_01E003E0_b134(pq, 0, t);
                t += 0.25f;
                t0 = func_01E003E0_b134(pq, 0, t);
                ab[1] = t0;
            } else {
                ab[0] = func_01E003E0_b134(a4, 0, t);
                t += 0.25f;
                t1 = func_01E003E0_b134(a4, 0, t);
                ab[1] = t1;
            }
            func_00107990(p, &c, 1);
            a = c.a - (s16)(s->col.a / (n * 3));
            if (a <= 0) {
                c.a = 0;
            } else {
                c.a = a;
            }
            func_00107990(p, &c, 2);
            for (m = 0; m < 2; m++) {
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
                func_00107070(q, 0, sc.x);
                func_00107070(q, 1, sc.y);
                func_00107070(q, 2, sc.z);
                if (m == 0) {
                    q[0].z += w;
                    q[2].z += w;
                    q[1].z += w;
                    q[3].z += w;
                } else if (m == 1) {
                    q[0].x += w;
                    q[2].x += w;
                    q[1].x -= w;
                    q[3].x -= w;
                }
                if (func_00205630(q, 0x70000000, NULL, p, depth) != 0) {
                    func_002075F0(p, ot, func_001A23B0(depth[0]));
                }
            }
        }
    }
}

/* shape b134:01E016D0, 304 insns: the scene script by frame (ctx+0x3026): 155 one 0x1E02750, 180 one 0x1E024D0,
   179/201, 185/205 and 191 a 0x1E02080 of kind 0/1/2, 186-187 a point at joint 0x300A (y from the model) as kind 1;
   then frames 179-184/201-205, 185-189/205-209 and 191-199 put the point on joint 0x300A / 0x300E / 0x3012, kind by
   the model's facing (turn / 180 != 0 -> 0), and spawn three 0x1E01E20 and one 0x1E01FB0 */

typedef struct {
    u8 pad0[0x2D0];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2DC[0x2FC4 - 0x2DC];
    u8 col[4];
    u8 pad2FC8[0x300A - 0x2FC8];
    s16 j0;
    u8 pad300C[2];
    s16 j1;
    u8 pad3010[2];
    s16 j2;
    u8 pad3014[0x3022 - 0x3014];
    s16 kind;
    u8 pad3024[2];
    s16 t;
} Scene_b134_01E016D0;

static s32 func_01E01E20_b134();
static s32 func_01E01FB0_b134();
static s32 func_01E02080_b134();
static s32 func_01E024D0_b134();
static s32 func_01E02750_b134();
static s32 func_01E03760_b134();

#pragma optimization_level 3

static void func_01E016D0_b134(Scene_b134_01E016D0 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    f32 a[4];
    f32 b[4];
    s32 r[4];
    s32 flip;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 155) {
        func_01E03760_b134(g, (s32)func_01E02750_b134, 0);
    }
    if (g->t == 180) {
        func_01E03760_b134(g, (s32)func_01E024D0_b134, 0);
    }
    if (g->t == 179 || g->t == 201) {
        g->kind = 0;
        func_01E03760_b134(g, (s32)func_01E02080_b134, 0);
    }
    if (g->t == 185 || g->t == 205) {
        g->kind = 1;
        func_01E03760_b134(g, (s32)func_01E02080_b134, 0);
    }
    if (g->t == 191) {
        g->kind = 2;
        func_01E03760_b134(g, (s32)func_01E02080_b134, 0);
    }
    if (g->t == 186 || g->t == 187) {
        func_001F5620(func_001F53A0(), g->j0, a);
        func_001F5F90(func_001F5380(), b);
        g->px = a[0];
        g->py = a[1];
        g->pz = b[2];
        g->kind = 1;
    }
    func_001F6160(func_001F53A0(), r);
    flip = (s32)(r[1] / 180.0f);
    if (g->t == 179 || g->t == 180 || g->t == 181 || g->t == 182 || g->t == 183 || g->t == 184 ||
        g->t == 201 || g->t == 202 || g->t == 203 || g->t == 204 || g->t == 205) {
        func_001F5620(func_001F53A0(), g->j0, a);
        g->px = a[0];
        g->py = a[1];
        g->pz = a[2];
        if (flip != 0) {
            g->kind = 0;
        } else {
            g->kind = 1;
        }
        for (i = 0; i < 3; i++) {
            func_01E03760_b134(g, (s32)func_01E01E20_b134, 0);
        }
        func_01E03760_b134(g, (s32)func_01E01FB0_b134, 0);
    }
    if (g->t == 185 || g->t == 186 || g->t == 187 || g->t == 188 || g->t == 189 ||
        g->t == 205 || g->t == 206 || g->t == 207 || g->t == 208 || g->t == 209) {
        func_001F5620(func_001F53A0(), g->j1, a);
        g->px = a[0];
        g->py = a[1];
        g->pz = a[2];
        if (flip != 0) {
            g->kind = 0;
        } else {
            g->kind = 1;
        }
        for (i = 0; i < 3; i++) {
            func_01E03760_b134(g, (s32)func_01E01E20_b134, 0);
        }
        func_01E03760_b134(g, (s32)func_01E01FB0_b134, 0);
    }
    if (g->t == 191 || g->t == 192 || g->t == 193 || g->t == 194 || g->t == 195 || g->t == 196 ||
        g->t == 197 || g->t == 198 || g->t == 199) {
        func_001F5620(func_001F53A0(), g->j2, a);
        g->px = a[0];
        g->py = a[1];
        g->pz = a[2];
        if (flip != 0) {
            g->kind = 0;
        } else {
            g->kind = 1;
        }
        for (i = 0; i < 3; i++) {
            func_01E03760_b134(g, (s32)func_01E01E20_b134, 0);
        }
        func_01E03760_b134(g, (s32)func_01E01FB0_b134, 0);
    }
}
#pragma optimization_level reset

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

static s32 func_01E01B90_b134(s32 arg0, Glow_b080_01E02140 *o) {
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

/* shape b134:01E01C70, 108 insns: a dark drifting mote (b194:01E015C0 shape): frame 10, random angles and speed 3..17; alpha 0x70
   for 10 frames, then down by 10 until it ends; drifts its speed along its angle and bobs it by its second angle */

typedef struct {
    u8 pad0[0x312C];
    u8 sin[1];
} Game_b134_01E01C70;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    s16 speed;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 bob;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b134_01E01C70;

static s32 func_01E01C70_b134(Game_b134_01E01C70 *g, Obj_b134_01E01C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0xA;
        o->sub = 0;
        func_001076F0(o->c0, 0x30, 0x30, 0x30);
        o->bob = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 0xA) {
        o->c0[3] = 0x70;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + o->speed * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + o->speed * func_00108030(g->sin, o->bob, 1));
    o->hC = func_001A22C0(o->hC + o->speed * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b134:01E01E20, 100 insns: on start 0x38 = -10, rotation (90, random, random), variant 0, step 4..6, 0x6 = 20,
   colour 0x80 grey; alpha grows by 0x40 (below 0x80) for 2 ticks, then fades by 0x13 once 0x38 passes 10; the colour
   flickers grey; 0x38 grows by the step after the first tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 step;
    u8 padA[6];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b134_01E01E20;

static s32 func_01E01E20_b134(s32 arg0, Fx_b134_01E01E20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = -10;
        o->rot[0] = 90;
        o->rot[1] = func_0019A5C8() % 360;
        o->rot[2] = func_0019A5C8() % 360;
        o->f34 = 0;
        o->mode = 2;
        o->step = func_0019A5C8() % 3 + 4;
        o->f6 = 20;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->f38 > 0xA) {
        if (o->col[3] > 0x14) {
            o->col[3] -= 0x13;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    if (o->tick != 0) {
        o->f38 += o->step;
    }
    o->tick++;
    return 0;
}

/* shape b134:01E01FB0, 52 insns: a white/red two-colour glow of size 130 at a random angle: alpha 0x80 on its first tick, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b134_01E01FB0;

static s32 func_01E01FB0_b134(s32 arg0, Glow_b134_01E01FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x82;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x10, 0x10);
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 1) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b134:01E02080, 45 insns: red flash (0x80, 0x20, 0x20): on start 0x38 = 13 and a hold of 8 ticks (0xE);
   alpha 0x80 during the hold, then fades by 0x1D and stops; 0x6 = 9 each tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[6];
    s16 hold;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b134_01E02080;

static s32 func_01E02080_b134(s32 arg0, Fx_b134_01E02080 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x80, 0x20, 0x20);
    if (o->mode == 1) {
        o->f38 = 13;
        o->hold = 8;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 0x1D;
    } else {
        o->mode = 0;
    }
    o->f6 = 9;
    o->tick++;
    return 0;
}

/* shape b134:01E02140, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x60, 0x60, 0x60) and fields;
   alpha 0x80 for the first 0xD ticks, then fade out by 29 and stop */

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
} Glow_b134_01E02140;

static s32 func_01E02140_b134(s32 arg0, Glow_b134_01E02140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->life = 7;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0xD) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x1E) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b134:01E021F0, 65 insns: on start both colours (0x60, 0x60, 0xC0), alphas 0x80 / 0x40, 0x6 = 8, position
   zeroed, 0x8..0xC = 10, 0x38 = 6; alpha 0x80 for 8 ticks, then the first fades by 0x1D (ends the effect) and the
   second by 15 */

typedef struct {
    s16 x, y, z;
    s16 f6;
    s16 f8, fA, fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b134_01E021F0;

static s32 func_01E021F0_b134(s32 arg0, Fx_b134_01E021F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0xC0);
        func_001076F0(o->col2, 0x60, 0x60, 0xC0);
        o->f6 = 8;
        o->col[3] = 0x80;
        o->col2[3] = 0x40;
        o->y = 0;
        o->x = 0;
        o->z = 0;
        o->fA = 10;
        o->f8 = 10;
        o->fC = 10;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 8) {
        o->col[3] = 0x80;
    } else {
        if (o->col[3] > 0x1E) {
            o->col[3] -= 0x1D;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0x10) {
            o->col2[3] -= 15;
        } else {
            o->col2[3] = 0;
        }
    }
    o->tick++;
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

static s32 func_01E02300_b134(s32 unused, Spark_b018_01E02950 *o) {
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

static s32 func_01E02470_b134(s32 arg0, Glow_b080_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        o->col[3] = 0x20;
        o->mode = 2;
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b134_01E024D0;

typedef struct {
    f32 f0, f4, f8, fC;
    Vec_b134_01E024D0 pos;
    f32 f20, f24, f28;
} Cam_b134_01E024D0;

typedef struct {
    u8 pad0000[0x2900];
    Cam_b134_01E024D0 cam;
    u8 pad351C[0x2FC0 - 0x292C];
    s32 w3610;
} Mgr_b134_01E024D0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0x2A];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
} Obj_b134_01E024D0;

static s32 func_01E024D0_b134(Mgr_b134_01E024D0 *m, Obj_b134_01E024D0 *o) {
    extern void func_001F6C10(void *);

    if (o->h36 == 1) {
        m->cam.f0 = 128.0f;
        m->cam.f4 = 6.0f;
        m->cam.f8 = 0.0f;
        m->cam.fC = 0.0f;
        m->cam.f20 = 0.0f;
        m->cam.f24 = 150.0f;
        m->cam.f28 = 0.0f;
        m->cam.pos.x = o->x;
        m->cam.pos.y = o->y;
        m->cam.pos.z = o->z;
        o->h36 = 2;
        o->h30 = 0;
    }
    if (o->h32 < 30) {
        if (m->cam.f28 < 1.0f) {
            m->cam.f28 += 0.2f;
        }
    } else {
        if (m->cam.f28 > 0.1f) {
            m->cam.f28 -= 0.1f;
        } else {
            o->h36 = 0;
        }
    }
    if (o->h32 % 2 == 1) {
        m->cam.f4 = 6.0f;
        m->cam.f8 = 0.0f;
    } else {
        m->cam.f4 = 6.0f;
        m->cam.f8 = 3.0f;
    }
    if (o->h36 == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&m->cam);
    }
    if (m->w3610 == 1) {
        o->h36 = 0;
    }
    o->h32++;
    return 0;
}

/* shape b134:01E02690, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2FC0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2FC0];
    s32 state;
} Game_b134_01E02690;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b134_01E02690;

static s32 func_01E02690_b134(Game_b134_01E02690 *g, Fade_b134_01E02690 *o) {
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

/* shape b134:01E02750, 38 insns: func_001F7170(10, 0, &a, &b, 0) with copies of the module's floats at 0x01E03F80 and
   0x01E03F88; mode 1 becomes 2; the effect stops once its tick (0x32) reaches 0x50; return 0 */

typedef struct {
    f32 v;
} F_b134_01E02750;

typedef struct {
    u8 pad0[0x32];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b134_01E02750;

extern F_b134_01E02750 D_01E03F80_b134;
extern F_b134_01E02750 D_01E03F88_b134;

static s32 func_01E02750_b134(s32 arg0, Fx_b134_01E02750 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b134_01E02750 a;
    F_b134_01E02750 b;

    a = D_01E03F80_b134;
    b = D_01E03F88_b134;
    if (o->mode == 1) {
        o->mode = 2;
    }
    func_001F7170(10, 0, &a, &b, 0);
    if (o->tick >= 0x50) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b134:01E027F0, 91 insns: a full-screen grey sprite overlay with the object's alpha (far depth, UV 0..0.625/0.875), queued
   every frame; its alpha rises by 0x50 to 0x50, and it ends after 35 frames */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b134_01E027F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    Xyz_b134_01E027F0 p0;
    f32 s1, t1;
    Xyz_b134_01E027F0 p1;
    u8 tail[0x20];
} Pkt_b134_01E027F0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
} Obj_b134_01E027F0;

static s32 func_01E027F0_b134(void *arg0, Obj_b134_01E027F0 *o) {
    extern void func_002087A0(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b134_01E027F0 pkt __attribute__((aligned(8)));

    ((Pkt_b134_01E027F0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b134_01E027F0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b134_01E027F0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b134_01E027F0 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x80;
    pkt.b = 0x80;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    pkt.p0.x = 0x6BF8;
    pkt.p0.y = 0x71F8;
    pkt.p0.z = 0xFFFFFF;
    pkt.p0.f = 0;
    pkt.p1.x = 0x93F8;
    pkt.p1.y = 0x8DF8;
    pkt.p1.z = 0xFFFFFF;
    pkt.p1.f = 0;
    pkt.s0 = 0.0f;
    pkt.t0 = 0.0f;
    pkt.s1 = 0.625f;
    pkt.t1 = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_002087A0(&pkt, 1);
    func_002075F0(&pkt, (s32)func_00207500(), 0);
    if (o->t < 0x23) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x50;
        }
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b134:01E02960, 40 insns: b734:01E03310 family: textures group 4 cells 0-2 and 11-15, group 5 cell 0 */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x2c20];
    s32 tex5[3];
} Scene_b134_01E02960;

static void func_01E02960_b134(s32 arg0, Scene_b134_01E02960 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 11; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 1; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b134", func_01E02A00_b134);

/* shape b134:01E03760, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3022 and the two arguments; returns 1 if a
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
} Slot_b134_01E03760;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0xB0];
    Slot_b134_01E03760 s[150];
    u8 pad2900[0x6C4];
    u8 r, g, b, a;
    u8 pad2FC8[0x5A];
    s16 v;
} Pool_b134_01E03760;

static s32 func_01E03760_b134(Pool_b134_01E03760 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b134_01E03760 *s = NULL;
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

/* shape b134:01E03880 (B134PAINT_RAIN9), 415 insns, 1 copy: b134:01E00820's ribbon between two point trails, drawn
   through a matrix from the ribbon's own rotation and scale (tenths): each segment is 2 spline quads, the first
   segment on local copies */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b134_01E03880;

typedef struct {
    Rgbaq_b134_01E03880 c;
    u64 uv;
    u64 xyz;
} Vtx_b134_01E03880;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b134_01E03880 v[4];
    u8 tail[0x20];
} Pkt_b134_01E03880;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b134_01E03880;

typedef struct {
    u8 r, g, b, a;
} C4_b134_01E03880;

typedef struct {
    s16 rx, ry, rz;
    s16 n;
    s16 sx, sy, sz;
    u8 pad0E[0x1A];
    C4_b134_01E03880 col0;
    C4_b134_01E03880 col1;
} Rib_b134_01E03880;

static void func_01E03880_b134(Obj_b134_01E03880 *o, Rib_b134_01E03880 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
    extern Rgbaq_b134_01E03880 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 rot;
    Vec_b018_01E00EE0 scale;
    f32 mat[4][4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[4];
    Vec_b018_01E00EE0 B[4];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b134_01E03880 pkt __attribute__((aligned(8)));
    C4_b134_01E03880 c0;
    C4_b134_01E03880 c1;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b134_01E03880 *p;
    s32 ot;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b134_01E03880 *)(s32)&pkt;
    func_00109270(p, 0, 0);
    pkt.v[0].c = func_00107740(&s->col0);
    pkt.v[1].c = func_00107740(&s->col1);
    pkt.v[2].c = func_00107740(&s->col0);
    pkt.v[3].c = func_00107740(&s->col1);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    c0 = s->col0;
    c1 = s->col1;
    a4[0] = pa[0];
    a4[1] = pa[1];
    a4[2] = pa[2];
    a4[3] = pa[3];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    rot.x = s->rx;
    rot.y = s->ry;
    rot.z = s->rz;
    scale.x = s->sx;
    scale.y = s->sy;
    scale.z = s->sz;
    scale.x /= 10.0f;
    scale.y /= 10.0f;
    scale.z /= 10.0f;
    func_00108EF0(mat, &scale, NULL, &rot);
    for (k = 0; k < n - 2; k++) {
        p->v[0].c = func_00107740(&c0);
        p->v[1].c = func_00107740(&c1);
        c0.a -= (u8)(s->col0.a / (n - 1));
        c1.a -= (u8)(s->col1.a / (n - 1));
        p->v[2].c = func_00107740(&c0);
        p->v[3].c = func_00107740(&c1);
        t = 0.0f;
        pq = pb + (k - 1);
        for (j = 0; j < 2; j++) {
            if (k != 0) {
                A[0] = func_01E003E0_b134(pa, 0, t);
                B[0] = func_01E003E0_b134(pq, 0, t);
                t += 0.5f;
                A[1] = func_01E003E0_b134(pa, 0, t);
                B[1] = func_01E003E0_b134(pq, 0, t);
            } else {
                A[0] = func_01E003E0_b134(a4, 0, t);
                B[0] = func_01E003E0_b134(b4, 0, t);
                t += 0.5f;
                A[1] = func_01E003E0_b134(a4, 0, t);
                B[1] = func_01E003E0_b134(b4, 0, t);
            }
            quad[0].x = A[0].x;
            quad[0].y = A[0].y;
            quad[0].z = A[0].z;
            quad[1].x = A[1].x;
            quad[1].y = A[1].y;
            quad[1].z = A[1].z;
            quad[2].x = B[0].x;
            quad[2].y = B[0].y;
            quad[2].z = B[0].z;
            quad[3].x = B[1].x;
            quad[3].y = B[1].y;
            quad[3].z = B[1].z;
            if (func_00205630(quad, 0x70000000, mat, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
        pa++;
    }
}
