#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b218(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00150_b218(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E001D0_b218(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00620_b218(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b218", func_01E00A60_b218);

/* shape b218:01E00ED0, 325 insns: b134:01E00820 family: a textured ribbon between two point trails, each segment 4
   spline quads (module curve function, shape b018:01E00EE0), the alpha fading along it; no matrix, far order 0;
   the first segment runs on local copies (each trail's first point doubled) */

typedef struct {
    f32 u, v;
} Uv_b218_01E00ED0;

typedef struct {
    Uv_b218_01E00ED0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b218_01E00ED0;

typedef struct {
    u8 hdr[0x10];
    Vtx_b218_01E00ED0 v[4];
    u8 tail[0x20];
} Pk_b218_01E00ED0;

typedef struct {
    u8 r, g, b, a;
} Col_b218_01E00ED0;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 mode;
} Obj_b218_01E00ED0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    u8 col[4];
} Rib_b218_01E00ED0;

static void func_01E00ED0_b218(Obj_b218_01E00ED0 *o, Rib_b218_01E00ED0 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
    extern s32 func_00109270();
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pk_b218_01E00ED0 pkt __attribute__((aligned(8)));
    Uv_b218_01E00ED0 uv0;
    Uv_b218_01E00ED0 uv1;
    Uv_b218_01E00ED0 uv2;
    Uv_b218_01E00ED0 uv3;
    Col_b218_01E00ED0 col;
    s32 k;
    s32 j;
    s16 n;
    Pk_b218_01E00ED0 *p;
    u8 *ot;
    Vec_b018_01E00EE0 *qa;
    Vec_b018_01E00EE0 *qb;
    f32 t;

    ot = func_00207500();
    n = s->n;
    p = (Pk_b218_01E00ED0 *)(s32)&pkt;
    func_00109270(p, 0, 0);
    func_00107740(&uv0, s->col);
    pkt.v[0].st = uv0;
    func_00107740(&uv1, s->col);
    pkt.v[1].st = uv1;
    func_00107740(&uv2, s->col);
    pkt.v[2].st = uv2;
    func_00107740(&uv3, s->col);
    pkt.v[3].st = uv3;
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    col = *(Col_b218_01E00ED0 *)s->col;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    for (k = 0; k < n - 1; k++) {
        func_00107790(p, &col.r, 1);
        col.a -= (u8)(s->col[3] / n);
        func_00107790(p, &col.r, 2);
        t = 0.0f;
        qa = pa + (k - 1);
        qb = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A[0] = func_01E00620_b218(qa, 0, t);
                B[0] = func_01E00620_b218(qb, 0, t);
                t += 0.25f;
                A[1] = func_01E00620_b218(qa, 0, t);
                B[1] = func_01E00620_b218(qb, 0, t);
            } else {
                A[0] = func_01E00620_b218(a4, 0, t);
                B[0] = func_01E00620_b218(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00620_b218(a4, 0, t);
                B[1] = func_01E00620_b218(b4, 0, t);
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
            if (func_00205630((s32)quad, 0x70000000, 0, (s32)p, depth) != 0) {
                func_002075F0((s32)p, (s32)ot, 0);
            }
        }
    }
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

static void func_01E013F0_b218(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
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
                A[0] = func_01E00620_b218(pa, 0, t);
                B[0] = func_01E00620_b218(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E00620_b218(pa, 0, t);
                B[1] = func_01E00620_b218(pq, 0, t);
            } else {
                A[0] = func_01E00620_b218(a4, 0, t);
                B[0] = func_01E00620_b218(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00620_b218(a4, 0, t);
                B[1] = func_01E00620_b218(b4, 0, t);
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

static void func_01E019B0_b218(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
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

static void func_01E01C40_b218(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
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

/* shape b046:01E00BB0, 133 insns, 4 copies: draws one camera-facing sprite at a position plus a tenth of an offset,
   blend by mode (0 normal, 1, other), texture corners by the module helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b046_01E00BB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b046_01E00BB0 c;
    struct {
        u64 tc;
        u64 xyz;
    } v[4];
    u8 tail[0x38];
} Pkt_b046_01E00BB0;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x22];
    s16 mode;
} Obj_b046_01E00BB0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
} Spr_b046_01E00BB0;

static void func_01E01F40_b218(Obj_b046_01E00BB0 *o, Spr_b046_01E00BB0 *s, s32 blend) {
    extern Rgbaq_b046_01E00BB0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    Pkt_b046_01E00BB0 pkt __attribute__((aligned(8)));
    Pkt_b046_01E00BB0 *p;
    f32 dx;
    f32 dy;
    f32 dz;

    p = (Pkt_b046_01E00BB0 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (blend == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    p->c = func_00107740(s->col);
    func_01E001D0_b218((Pk_b003_01E00080 *)p, &o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    dx = s->dx;
    dy = s->dy;
    dz = s->dz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x = s->x + dx;
    pos.y = s->y + dy;
    pos.z = s->z + dz;
    func_00108EF0(m, &scale, rot, &pos);
    func_00108CE0(quad, s->size, s->size);
    if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
        func_002075F0(p, o->ot, (u32)depth[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b218", func_01E02160_b218);

/* shape b218:01E027F0, 173 insns: a 10-point column effect: on start both colours 0x60/0x60/0xC0 (alpha 0x80 and
   0x40), both 10-point rows at g+0x2C90/0x2D30 copied from g+0x2A10 with the first one 10 lower, size 10; the first
   colour holds for 27 ticks, then both fade (by 15 and by 7); from the second tick each row point
   moves 8 down or up by the sign func_001A22C0 gives for the camera angle */

typedef struct {
    f32 x, y, z, w;
} Pt_b218_01E027F0;

typedef struct {
    u8 pad0[0x2A10];
    Pt_b218_01E027F0 src[10];
    u8 pad2AB0[0x1E0];
    Pt_b218_01E027F0 a[10];
    Pt_b218_01E027F0 b[10];
} Game_b218_01E027F0;

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 mode;
    s16 h38;
} Fx_b218_01E027F0;

static s32 func_01E027F0_b218(Game_b218_01E027F0 *g, Fx_b218_01E027F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 v[4];
    s16 i;
    s32 r;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0xC0);
        func_001076F0(o->col2, 0x60, 0x60, 0xC0);
        o->h6 = 8;
        o->col[3] = 0x80;
        o->col2[3] = 0x40;
        for (i = 0; i < 10; i++) {
            g->a[i] = g->src[i];
            g->b[i] = g->src[i];
        }
        for (i = 0; i < 10; i++) {
            g->a[i].z -= 10.0f;
        }
        o->h2 = 0;
        o->h0 = 0;
        o->h4 = 0;
        o->hA = 10;
        o->h8 = 10;
        o->hC = 10;
        for (i = 0; i < 10; i++) {
        }
        o->h38 = 6;
        o->mode = 2;
    }
    if (o->t < 27) {
        o->col[3] = 0x80;
    } else {
        if (o->col[3] > 16) {
            o->col[3] -= 15;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 8) {
            o->col2[3] -= 7;
        } else {
            o->col2[3] = 0;
        }
    }
    func_001F6160(func_001F53A0(), v);
    r = (s16)func_001A22C0((f32)v[1] / 180.0f);
    if (o->t != 0) {
        for (i = 0; i < 10; i++) {
            if (r != 0) {
                g->a[i].z -= 8.0f;
                g->b[i].z -= 8.0f;
            } else {
                g->a[i].z += 8.0f;
                g->b[i].z += 8.0f;
            }
        }
    }
    o->t++;
    return 0;
}

/* shape b218:01E02AB0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x10, 0x60, 0x10) and fields;
   alpha 0x60 for the first 0x78 ticks, then fade out by 9 and stop */

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
} Glow_b218_01E02AB0;

static s32 func_01E02AB0_b218(s32 arg0, Glow_b218_01E02AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x10, 0x60, 0x10);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x78) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b218:01E02B60, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x60, 0x60, 0x60) and fields;
   alpha 0x80 for the first 0x78 ticks, then fade out by 9 and stop */

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
} Glow_b218_01E02B60;

static s32 func_01E02B60_b218(s32 arg0, Glow_b218_01E02B60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x78) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b218:01E02C10, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x20, 0x20, 0x20) and fields;
   alpha 0x80 for the first 0x78 ticks, then fade out by 9 and stop */

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
} Glow_b218_01E02C10;

static s32 func_01E02C10_b218(s32 arg0, Glow_b218_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x78) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b218:01E02CC0, 50 insns: a two-colour glow: (0x60,0x60,0xC0) twice, alphas 0x80/0x40, life 8; alpha held
   at 0x80 for 0x78 ticks, then fades out by 9 and stops */

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
} Glow_b218_01E02CC0;

static s32 func_01E02CC0_b218(s32 arg0, Glow_b218_01E02CC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0xC0);
        func_001076F0(o->col2, 0x60, 0x60, 0xC0);
        o->life = 8;
        o->col[3] = 0x80;
        o->col2[3] = 0x40;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x78) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b218:01E02D90, 96 insns: a blue trail: both colours blue (alphas 0x80 and 0x40), sizes 10, copies the scene ten points
   into its trail row; full alpha on the first frame, then the first alpha down by 15 until it ends and the second down by 7 */

typedef struct {
    f32 x, y, z, w;
} V4_b218_01E02D90;

typedef struct {
    u8 pad0[0x2D30];
    V4_b218_01E02D90 src[10];
    u8 pad2DD0[0x2E70 - 0x2DD0];
    V4_b218_01E02D90 trail[1][10];
} Game_b218_01E02D90;

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 c1[4];
    s16 row;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b218_01E02D90;

static s32 func_01E02D90_b218(Game_b218_01E02D90 *g, Obj_b218_01E02D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->state == 1) {
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        func_001076F0(o->c1, 0x30, 0x30, 0x80);
        o->h6 = 8;
        o->c0[3] = 0x80;
        o->c1[3] = 0x40;
        o->h2 = 0;
        o->h0 = 0;
        o->h4 = 0;
        o->hA = 0xA;
        o->h8 = 0xA;
        o->hC = 0xA;
        for (i = 0; i < 10; i++) {
            g->trail[o->row][i] = g->src[i];
        }
        o->h38 = 6;
        o->state = 2;
    }
    if (o->t < 1) {
        o->c0[3] = 0x80;
    } else {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0xF;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 8) {
            o->c1[3] -= 7;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0x3B00];
    s32 w3B00;
} Mgr_b218_01E02F10;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[6];
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
} Obj_b218_01E02F10;

static s32 func_01E02F10_b218(Mgr_b218_01E02F10 *m, Obj_b218_01E02F10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 0;
        o->w10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = func_0019A5C8() % 7;
        o->h36 = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        o->h6 = 20;
        if (o->h30 == 0) {
            func_001076F0(o->c28, 0xC0, 0x80, 0);
        } else {
            func_001076F0(o->c28, 0, 0xA0, 0xA0);
        }
        func_001076F0(o->c2C, 0xA0, 8, 8);
    }
    if (o->h32 < 2) {
        if (o->c28[3] < 0x80) {
            o->c28[3] += 0x40;
        }
    } else {
        if (o->h38 > 40) {
            if (o->c28[3] > 20) {
                o->c28[3] -= 19;
            } else {
                o->h36 = 0;
            }
        }
        if (m->w3B00 < 10) {
            if (o->c28[3] > 16) {
                o->c28[3] -= 15;
            } else {
                o->h36 = 0;
            }
        }
    }
    if (o->h32 != 0) {
        o->h38 += o->h8;
    }
    o->h32++;
    return 0;
}

/* shape b218:01E030E0, 129 insns: blue trail head for trail f30 (of the scene's 0xA0-byte trails at ctx+0x2E70): on start fills all 10 points with the tracked point (ctx+0x2C90 for trail 15, else ctx+0x2D00); alpha up by 27 to 0xC0 for 28 ticks, then down by 9; each tick pushes the point into the trail (b218:01E00150, 10 steps) */

typedef struct {
    Vec4f pt[10];
} Trail_b218_01E030E0;

typedef struct {
    u8 pad0[0x2C90];
    Vec4f pa;
    u8 pad2CA0[0x60];
    Vec4f pb;
    u8 pad2D10[0x2E70 - 0x2D10];
    Trail_b218_01E030E0 tr[1];
} Ctx_b218_01E030E0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Fx_b218_01E030E0;

static s32 func_01E030E0_b218(Ctx_b218_01E030E0 *g, Fx_b218_01E030E0 *o) {
    extern void b218_01E00150(Vec4f *, s32, s32, Vec4f *);
    extern void func_001076F0(void *, s32, s32, s32);
    Vec4f v;
    s32 i;
    Vec4f *p;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x30, 0x30, 0x80);
        o->hold = 9;
        o->col[3] = 0;
        o->fA = func_0019A5C8() % 17 + 44;
        o->f8 = func_0019A5C8() % 8 + 5;
        if (o->kind == 15) {
            *(Vec4f *)(u32)&v = g->pa;
        } else {
            *(Vec4f *)(u32)&v = g->pb;
        }
        p = g->tr[o->kind].pt;
        for (i = 0; i < 10; i++) {
            p[i].x = v.x;
            p[i].y = v.y;
            p[i].z = v.z;
        }
        o->mode = o->f38 = 2;
    }
    if (o->tick < 28) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 27;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    *(Vec4f *)(u32)&v = *(o->kind == 15 ? &g->pa : &g->pb);
    b218_01E00150(&g->tr[o->kind].pt[9], 10, 0, &v);
    return 0;
}

/* shape b218:01E032F0, 64 insns: b383:01E034A0 twin: a white spark at a random frame and two random angles, growing 2 a tick up to 40: alpha 0x80 for 19 ticks, then out by 11 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b218_01E032F0;

static s32 func_01E032F0_b218(s32 arg0, Glow_b218_01E032F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 19) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->f38 < 40) {
        o->f38 += 2;
    }
    o->tick++;
    return 0;
}

/* shape b218:01E033F0, 90 insns: b115:01E01980 family: a grey/white spark (size 60, random frame 0..6) at two random angles drifting 24 a tick along its angle (sine table ctx+0x3C6C): alpha 0x80 for 7 ticks, then out by 0x14 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b218_01E033F0;

typedef struct {
    u8 pad[0x3c6c];
    u8 sin[1];
} Game_b218_01E033F0;

static s32 func_01E033F0_b218(Game_b218_01E033F0 *g, Glow_b218_01E033F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x15) {
        o->col[3] -= 0x14;
    } else {
        o->mode = 0;
    }
    o->h8 = func_001A22C0(o->h8 + 24.0f * func_00108030(g->sin, o->ang, 0));
    o->hC = func_001A22C0(o->hC + 24.0f * func_00108030(g->sin, o->ang, 1));
    o->tick++;
    return 0;
}

/* shape b218:01E03560, 104 insns: b266:01E01610 family: a white spark (size 60, random frame 0..6) at two random angles drifting 14 a tick on all three axes (sine table ctx+0x3C6C): alpha 0x80 for 12 ticks, then out by 20 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
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
} Glow_b218_01E03560;

typedef struct {
    u8 pad[0x3C6C];
    u8 sin[1];
} Game_b218_01E03560;

static s32 func_01E03560_b218(Game_b218_01E03560 *g, Glow_b218_01E03560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 60;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 12) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x15) {
        o->col[3] -= 0x14;
    } else {
        o->mode = 0;
    }
    o->h8 = func_001A22C0(o->h8 + 14.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 14.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 14.0f * func_00108030(g->sin, o->ang, 1));
    o->tick++;
    return 0;
}

/* shape b218:01E03700, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
   for the first 2 ticks, then fades out by 15 and stops */

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
} Flash_b218_01E03700;

static s32 func_01E03700_b218(s32 arg0, Flash_b218_01E03700 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x190;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0x10, 0x10, 0xF0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b218:01E037E0, 173 insns: a flash light at g+0x2920 (b490:01E00E90's kind): on start colour 0, height 0/70/0 and the
   effect's position; it brightens (strength +0.2 to 1, colour +42/+21/+10 up to 128/128/64), then once full fades
   (strength -0.1, colour -16/-16/-8) until it ends; func_001F6C10 gets the light (or 0 once ended); it also ends when
   the light's state word is 1 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x11B4];
    s32 state;
} Light_b218_01E037E0;

typedef struct {
    u8 pad0[0x2920];
    Light_b218_01E037E0 light;
} Game_b218_01E037E0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x2A];
    s16 f30;
    u8 pad32[4];
    s16 mode;
} Fx_b218_01E037E0;

static s32 func_01E037E0_b218(Game_b218_01E037E0 *g, Fx_b218_01E037E0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a[0] = 0.0f;
        g->light.a[1] = 0.0f;
        g->light.a[2] = 0.0f;
        g->light.a[3] = 0.0f;
        g->light.b[0] = 0.0f;
        g->light.b[1] = 70.0f;
        g->light.b[2] = 0.0f;
        g->light.pos[0] = o->x;
        g->light.pos[1] = o->y;
        g->light.pos[2] = o->z;
        o->mode = 2;
        o->f30 = 0;
    }
    if (o->f30 == 0) {
        if (g->light.b[2] < 1.0f) {
            g->light.b[2] += 0.2f;
        } else {
            o->f30 = 1;
        }
        if (g->light.a[0] < 128.0f) {
            g->light.a[0] += 42.0f;
        } else {
            g->light.a[0] = 128.0f;
        }
        if (g->light.a[1] < 64.0f) {
            g->light.a[1] += 21.0f;
        } else {
            g->light.a[1] = 128.0f;
        }
        if (g->light.a[2] < 32.0f) {
            g->light.a[2] += 10.0f;
        } else {
            g->light.a[2] = 64.0f;
        }
    } else {
        if (!(g->light.b[2] <= 0.1f)) {
            g->light.b[2] -= 0.1f;
        } else {
            o->mode = 0;
        }
        if (!(g->light.a[0] <= 16.0f)) {
            g->light.a[0] -= 16.0f;
        } else {
            g->light.a[0] = 0.0f;
        }
        if (!(g->light.a[1] <= 16.0f)) {
            g->light.a[1] -= 16.0f;
        } else {
            g->light.a[1] = 0.0f;
        }
        if (!(g->light.a[2] <= 8.0f)) {
            g->light.a[2] -= 8.0f;
        } else {
            g->light.a[2] = 0.0f;
        }
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->light.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b218:01E03AA0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3B00 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3B00];
    s32 state;
} Game_b218_01E03AA0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b218_01E03AA0;

static s32 func_01E03AA0_b218(Game_b218_01E03AA0 *g, Fade_b218_01E03AA0 *o) {
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

static s32 func_01E03B60_b218(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05C80_b218;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05C88_b218;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03BB0_b218(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b218", func_01E03BC0_b218);

/* shape b218:01E04890, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3B62 and the two arguments; returns 1 if a
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
} Slot_b218_01E04890;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0xB0];
    Slot_b218_01E04890 s[150];
    u8 pad2900[0x1204];
    u8 r, g, b, a;
    u8 pad3B08[0x5A];
    s16 v;
} Pool_b218_01E04890;

static s32 func_01E04890_b218(Pool_b218_01E04890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b218_01E04890 *s = NULL;
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

/* shape b218:01E049B0 (B218PAINT_RAIN10), 415 insns, 1 copy: the ribbon draw (b134:01E03880 form): four quads per
   segment, step 0.25 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b218_01E049B0;

typedef struct {
    Rgbaq_b218_01E049B0 c;
    u64 uv;
    u64 xyz;
} Vtx_b218_01E049B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b218_01E049B0 v[4];
    u8 tail[0x20];
} Pkt_b218_01E049B0;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b218_01E049B0;

typedef struct {
    u8 r, g, b, a;
} C4_b218_01E049B0;

typedef struct {
    s16 rx, ry, rz;
    s16 n;
    s16 sx, sy, sz;
    u8 pad0E[0x1A];
    C4_b218_01E049B0 col0;
    C4_b218_01E049B0 col1;
} Rib_b218_01E049B0;

static void func_01E049B0_b218(Obj_b218_01E049B0 *o, Rib_b218_01E049B0 *s, Vec_b018_01E00EE0 *pa,
                               Vec_b018_01E00EE0 *pb) {
    extern Rgbaq_b218_01E049B0 func_00107740(void *);
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
    Pkt_b218_01E049B0 pkt __attribute__((aligned(8)));
    C4_b218_01E049B0 c0;
    C4_b218_01E049B0 c1;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b218_01E049B0 *p;
    s32 ot;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b218_01E049B0 *)(s32)&pkt;
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
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A[0] = func_01E00620_b218(pa, 0, t);
                B[0] = func_01E00620_b218(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E00620_b218(pa, 0, t);
                B[1] = func_01E00620_b218(pq, 0, t);
            } else {
                A[0] = func_01E00620_b218(a4, 0, t);
                B[0] = func_01E00620_b218(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00620_b218(a4, 0, t);
                B[1] = func_01E00620_b218(b4, 0, t);
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

INCLUDE_ASM("asm/nonmatchings/mod/b218", func_01E05030_b218);

/* OVL_WARM */

/* shape b045:01E04270, 316 insns: b018:01E01320's curved beam, textured, drawn as 2 crossed quads per step. Needs func_01E00620_b218 in the same file and
   static: the original keeps $a0 (the returned Vec buffer) across each call. */

typedef struct {
    u8 r, g, b, a;
} Col_b045_01E04270;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x20];
    Col_b045_01E04270 col;
    u8 pad2C[0xC];
    s16 width;
} Beam_b045_01E04270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b045_01E04270;

typedef struct {
    Rgbaq_b045_01E04270 c;
    u64 uv;
    u64 xyz;
} Vtx_b045_01E04270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b045_01E04270 v[4];
    u8 tail[0x20];
} Pkt_b045_01E04270;

typedef struct {
    u8 pad00[0x88];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Obj_b045_01E04270;

static void func_01E05710_b218(Obj_b045_01E04270 *o, Beam_b045_01E04270 *an, Vec_b018_01E00EE0 *pts) {
    extern s32 func_00207500(void);
    extern void func_001094F0(void *);
    extern Rgbaq_b045_01E04270 func_00107740(void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00108500(void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b018_01E00EE0 ab[2];
    Vec_b018_01E00EE0 ctrl[4];
    Vec_b018_01E00EE0 q[4];
    f32 depth __attribute__((aligned(16)));
    Vec_b018_01E00EE0 r1;
    Vec_b018_01E00EE0 r2;
    Pkt_b045_01E04270 pkt __attribute__((aligned(8)));
    Col_b045_01E04270 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b045_01E04270 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 h;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    func_001094F0(p);
    func_00109270(p, 0, 0);
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    col = an->col;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                ab[0] = func_01E00620_b218(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E00620_b218(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E00620_b218(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E00620_b218(ctrl, 0, t);
                ab[1] = r2;
            }
            p->v[0].c = func_00107740(&col);
            p->v[1].c = func_00107740(&col);
            x = col.a - (s16)(an->col.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            p->v[2].c = func_00107740(&col);
            p->v[3].c = func_00107740(&col);
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
                    q[0].y += w;
                    q[2].y += w;
                    q[1].y -= w;
                    q[3].y -= w;
                } else if (k == 1) {
                    q[0].x += w;
                    q[2].x += w;
                    q[1].x -= w;
                    q[3].x -= w;
                    q[0].z += w / 2.0f;
                    q[2].z += w / 2.0f;
                    q[1].z -= w / 2.0f;
                    q[3].z -= w / 2.0f;
                }
                if (func_00205630(q, 0x70000000, 0, p, &depth) != 0) {
                    func_002075F0(p, target, (u32)depth);
                }
            }
        }
    }
}
