#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b233(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b233(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static Vec_b018_01E00EE0 func_01E005A0_b233(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b233", func_01E009E0_b233);

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

static void func_01E00E50_b233(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
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

static void func_01E010E0_b233(Obj_b218_01E00ED0 *o, Rib_b218_01E00ED0 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
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
                A[0] = func_01E005A0_b233(qa, 0, t);
                B[0] = func_01E005A0_b233(qb, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(qa, 0, t);
                B[1] = func_01E005A0_b233(qb, 0, t);
            } else {
                A[0] = func_01E005A0_b233(a4, 0, t);
                B[0] = func_01E005A0_b233(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(a4, 0, t);
                B[1] = func_01E005A0_b233(b4, 0, t);
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

static void func_01E01600_b233(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
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
                A[0] = func_01E005A0_b233(pa, 0, t);
                B[0] = func_01E005A0_b233(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(pa, 0, t);
                B[1] = func_01E005A0_b233(pq, 0, t);
            } else {
                A[0] = func_01E005A0_b233(a4, 0, t);
                B[0] = func_01E005A0_b233(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b233(a4, 0, t);
                B[1] = func_01E005A0_b233(b4, 0, t);
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

/* shape b233:01E01BC0, 166 insns: b069:01E01A70 with the position passed by value: draws 4 copies of a gradient
   quad (colour A on three corners, B on the last), each turned by the effect's rotation; far z. The packet is
   passed in. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b233_01E01BC0;

typedef struct {
    Rgbaq_b233_01E01BC0 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b233_01E01BC0;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b233_01E01BC0 v[4];
    u8 tail[0x20];
} Pkt_b233_01E01BC0;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b233_01E01BC0;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b233_01E01BC0;

static void func_01E01BC0_b233(Obj_b233_01E01BC0 *o, Fx_b233_01E01BC0 *fx, Pkt_b233_01E01BC0 *p, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b233_01E01BC0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

/* shape b233:01E01E60 (B233_W_S), 503 insns, 1 copy (-O3,p): B233_W_S, the scene timer script: colour red, counts the
   frame (0x3972); at 163 four b233 glows, at 1 b233:01E03980/01E03900 and saves two points; at 89/111/170 and
   100/120/170 ten b233:01E03090 sparks at joints; at 167 the flash and three rings; 165..177 three steps of two
   trails between saved points; the point follows the saved points and joints by frame range */

typedef struct {
    Vec4f a;
    Vec4f b;
} Pair_b233_01E01E60;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x290 - 0x260];
    Vec4f a;
    Vec4f b;
    u8 pad2B0[0x28C0 - 0x2B0];
    Vec4f r0;
    Vec4f r1;
    u8 pad28E0[0x2960 - 0x28E0];
    Vec4f q0;
    Vec4f q1;
    u8 pad2980[0x31B0 - 0x2980];
    Pair_b233_01E01E60 arr[60];
    u8 pad[0x3934 - 0x31B0 - 60 * 32];
    u8 col[4];
    u8 pad3938[0x395C - 0x3938];
    s16 k;
    s16 j0;
    s16 j1;
    s16 j2;
    s16 j3;
    s16 pad3966;
    s16 h;
    s16 pad396A[2];
    s16 idx;
    s16 pad3970;
    s16 t;
} Ctx_b233_01E01E60;

#pragma optimization_level 3

static void func_01E01E60_b233(Ctx_b233_01E01E60 *g) {
    extern void b233_01E04760();
    extern void b233_01E02FE0(), b233_01E031F0(), b233_01E02F10(), b233_01E032D0();
    extern void b233_01E03980(), b233_01E03900(), b233_01E03090(), b233_01E03490();
    extern void b233_01E03570(), b233_01E036D0(), b233_01E02D60(), b233_01E033B0();
    extern void b233_01E03B90();
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    f32 d[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0xA3) {
        b233_01E04760(g, b233_01E02FE0, 0);
    }
    if (g->t == 0xA3) {
        b233_01E04760(g, b233_01E031F0, 0);
    }
    if (g->t == 0xA3) {
        b233_01E04760(g, b233_01E02F10, 0);
    }
    if (g->t == 0xA3) {
        b233_01E04760(g, b233_01E032D0, 0);
    }
    if (g->t == 1) {
        b233_01E04760(g, b233_01E03980, 0);
    }
    if (g->t == 1) {
        b233_01E04760(g, b233_01E03900, 0);
    }
    if (g->t == 0x59 || g->t == 0x6F || g->t == 0xAA) {
        func_001F5620(func_001F53A0(), g->j2, &v);
        for (i = 0; i < 10; i++) {
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b233_01E04760(g, b233_01E03090, 0);
        }
    }
    if (g->t == 0x64 || g->t == 0x78 || g->t == 0xAA) {
        func_001F5620(func_001F53A0(), g->j3, &v);
        for (i = 0; i < 10; i++) {
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            b233_01E04760(g, b233_01E03090, 0);
        }
    }
    if (g->t == 0xA7) {
        func_001F5620(func_001F53A0(), g->j0, &v);
        func_001F5F90(func_001F5380(), d);
        g->pos.x = d[0];
        g->pos.y = v.y;
        g->pos.z = d[2];
        b233_01E04760(g, b233_01E03490, 0);
        g->idx = 0;
        g->h = 0;
        b233_01E04760(g, b233_01E03570, 0);
        g->idx = 1;
        g->h = 45;
        b233_01E04760(g, b233_01E03570, 0);
        g->idx = 2;
        g->h = 90;
        b233_01E04760(g, b233_01E03570, 0);
        b233_01E04760(g, b233_01E036D0, 0);
    }
    if (g->t > 0xA4 && g->t < 0xB2) {
        func_001F5620(func_001F53A0(), g->j0, &v);
        for (i = 0; i < 3; i++) {
            g->idx = g->k;
            d[0] = (g->q1.x - g->q0.x) / 3.0f;
            d[1] = (g->q1.y - g->q0.y) / 3.0f;
            d[2] = (g->q1.z - g->q0.z) / 3.0f;
            g->pos.x = g->q0.x + d[0] * i;
            g->pos.y = g->q0.y + d[1] * i;
            g->pos.z = g->q0.z + d[2] * i;
            g->arr[g->idx].b.x = g->pos.x;
            g->arr[g->idx].b.y = g->pos.y;
            g->arr[g->idx].b.z = g->pos.z;
            b233_01E04760(g, b233_01E02D60, 0);
            d[0] = (g->r1.x - g->r0.x) / 3.0f;
            d[1] = (g->r1.y - g->r0.y) / 3.0f;
            d[2] = (g->r1.z - g->r0.z) / 3.0f;
            g->pos.x = g->r0.x + d[0] * i;
            g->pos.y = g->r0.y + d[1] * i;
            g->pos.z = g->r0.z + d[2] * i;
            g->arr[g->idx].a.x = g->pos.x;
            g->arr[g->idx].a.y = g->pos.y;
            g->arr[g->idx].a.z = g->pos.z;
            b233_01E04760(g, b233_01E033B0, 0);
            g->k++;
            if (g->k >= 60) {
                g->k = 0;
            }
        }
    }
    if (g->t == 0x42) {
        b233_01E04760(g, b233_01E03B90, 0);
    }
    if (g->t == 1) {
        func_001F5F90(func_001F53A0(), &g->a);
        func_001F5F90(func_001F53A0(), &g->b);
    }
    if (g->t > 0x6F && g->t < 0xC3) {
        g->a.z -= 2.4f;
        g->pos.x = g->a.x;
        g->pos.y = g->a.y - 10.0f;
        g->pos.z = 40.0f + g->a.z;
        g->idx = 0;
    }
    if (g->t > 0xAA && g->t < 0xE1) {
        g->b.z -= 3.8f;
        g->pos.x = g->b.x;
        g->pos.y = g->b.y - 10.0f;
        g->pos.z = 40.0f + g->b.z;
        g->idx = 1;
    }
    if (g->t >= 0x70 && g->t < 0xBF) {
        g->pos.x = g->a.x;
        g->pos.y = g->a.y - 10.0f;
        g->pos.z = 40.0f + g->a.z;
        g->idx = 0;
    }
    if (g->t >= 0xA9 && g->t < 0xDD) {
        g->pos.x = g->b.x;
        g->pos.y = g->b.y - 10.0f;
        g->pos.z = 40.0f + g->b.z;
        g->idx = 1;
    }
    if (g->t == 0x30 || g->t == 0x31 || g->t == 0x32 || g->t == 0x33) {
        func_001F5620(func_001F53A0(), g->j0, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->idx = 0;
    }
    if (g->t == 0x33 || g->t == 0x34 || g->t == 0x35 || g->t == 0x36) {
        func_001F5620(func_001F53A0(), g->j1, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->idx = 1;
    }
}

#pragma optimization_level reset

/* shape b233:01E02640, 134 insns: b117:01E01070's grey-purple drifting mote with a -15..14 tilt, drifting 10 sideways and 4 up */

typedef struct {
    u8 pad0[0x3A74];
    u8 sin[1];
} Game_b233_01E02640;

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
} Obj_b233_01E02640;

static s32 func_01E02640_b233(Game_b233_01E02640 *g, Obj_b233_01E02640 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->ang = func_0019A5C8() % 360;
        o->sub = 0;
        o->turn = func_0019A5C8() % 30 - 15;
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
        if (o->h38 < 18) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->h8 = func_001A22C0(o->h8 + 10.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 4.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 10.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b233:01E02860, 87 insns: an orange spark (size 8 growing 4 a tick, random frame 0..6) tipped by a random +-0x2000 and turned at random: in by 80 up to 0xA0 for 2 ticks; past size 20 out by 13, and out by 15 once the scene state is under 10; ends */

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
} Glow_b233_01E02860;

typedef struct {
    u8 pad[0x3930];
    s32 state;
} Game_b233_01E02860;

static s32 func_01E02860_b233(Game_b233_01E02860 *g, Glow_b233_01E02860 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->w18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w14 = func_0019A5C8() % 65535;
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 20) {
            if (o->col[3] > 14) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->state < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->tick++;
    o->f38 += 4;
    return 0;
}

/* shape b233:01E029C0, 101 insns: b443:01E03660 family: a dark yellow arc (size 50) facing left or right of the scene camera, tipped +-0x2000 by its kind, sweeping 8 a tick from 90 up to 160: in by 64 up to 0x80 for 2 ticks, then out by 9; out by 13 once the scene state is under 15; ends */

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
} Glow_b233_01E029C0;

typedef struct {
    u8 pad[0x3930];
    s32 state;
} Game_b233_01E029C0;

static s32 func_01E029C0_b233(Game_b233_01E029C0 *g, Glow_b233_01E029C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_001A22C0(f32);
    struct {
        s32 x, y, z, w;
    } v;

    func_001076F0(o->col, 0x10, 0x10, 0);
    if (o->mode == 1) {
        func_001F6160(func_001F53A0(), &v);
        if (func_001A22C0((f32)v.y / 180.0f) != 0) {
            o->w10 = -0x4000;
        } else {
            o->w10 = 0xFFFF4000;
        }
        o->w14 = 0;
        if (o->h30 == 0) {
            o->w18 = 0x2000;
        } else {
            o->w18 = -0x2000;
        }
        o->kind = 0;
        o->h30 = 90;
        o->mode = 2;
        o->col[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f38 = 50;
    o->tick++;
    if (o->h30 < 160) {
        o->h30 += 8;
    }
    if (g->state < 15) {
        if (o->col[3] > 14) {
            o->col[3] -= 13;
        } else {
            o->mode = 0;
        }
    }
    return 0;
}

/* shape b233:01E02B60, 59 insns: an orange column: set up once (its fall step from the model joint's height to its own
   y, frame 50), fades in by 0x19 for 5 frames; drops by the step each frame */

typedef struct {
    u8 pad0[0x3960];
    s16 joint;
} Game_b233_01E02B60;

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[6];
    s16 hA;
    u8 padC[2];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 h30;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Obj_b233_01E02B60;

static s32 func_01E02B60_b233(Game_b233_01E02B60 *g, Obj_b233_01E02B60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;

    if (o->state == 1) {
        func_001076F0(o->c0, 0x50, 0x20, 0);
        func_001F5620(func_001F53A0(), g->joint, &v);
        o->step = v.y - o->y;
        o->h38 = 0x32;
        o->h3A = 0;
        o->h34 = 2;
        o->h30 = 1;
        o->state = 2;
    }
    if (o->t < 5) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x19;
        }
    }
    o->t++;
    o->hA -= o->step;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b112_01E017B0;

static s32 func_01E02C50_b233(s32 unused, Obj_b112_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
    if (o->h36 == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (o->h30 == 0) {
            o->w18 = -0x2000;
        } else {
            o->w18 = 0x2000;
        }
        o->h6 = o->h30;
        o->h34 = func_0019A5C8() % 7;
    }
    if (o->h32 < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->col[3] > 20) {
            o->col[3] -= 0x13;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    return 0;
}

/* shape b233:01E02D60, 108 insns: a grey drifting mote: frame 20, sub-frame 5, random angle; sets its row velocity to half the
   gap between two scene values on each axis; full alpha for 4 frames, then down by 15 until it ends; moves by its velocity */

typedef struct {
    f32 x, y, z, w;
} V4_b233_01E02D60;

typedef struct {
    u8 pad0[0x28C0];
    f32 lo;
    u8 pad28C4[0x9C];
    f32 hi;
    u8 pad2964[0x48C];
    V4_b233_01E02D60 vel[1];
} Game_b233_01E02D60;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 row;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b233_01E02D60;

static s32 func_01E02D60_b233(Game_b233_01E02D60 *g, Obj_b233_01E02D60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0x14;
        o->sub = 5;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->ang = func_0019A5C8() % 360;
        g->vel[o->row].x = (g->hi - g->lo) / 2.0f;
        g->vel[o->row].y = (g->hi - g->lo) / 2.0f;
        g->vel[o->row].z = (g->hi - g->lo) / 2.0f;
        o->state = 2;
    }
    if (o->t < 4) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->h8 = func_001A22C0(o->h8 + g->vel[o->row].x);
    o->hA = func_001A22C0(o->hA + g->vel[o->row].y);
    o->hC = func_001A22C0(o->hC + g->vel[o->row].z);
    o->t++;
    return 0;
}

/* shape b233:01E02F10, 52 insns: a blue glow at a random angle: in by 0x1B up to 0xC0 for 10 ticks, then out by 11 and ends */

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
} Glow_b233_01E02F10;

static s32 func_01E02F10_b233(s32 arg0, Glow_b233_01E02F10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        o->h6 = 9;
        o->col[3] = 0;
        o->ang = func_0019A5C8() % 360;
        o->f38 = 2;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x1B;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b233:01E02FE0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x80, 0x10, 0xF0) and fields;
   alpha 0x60 for the first 0x7 ticks, then fade out by 9 and stop */

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
} Glow_b233_01E02FE0;

static s32 func_01E02FE0_b233(s32 arg0, Glow_b233_01E02FE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x10, 0xF0);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x7) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b233:01E03090, 87 insns: a white spark (size 60, frame 5) at two random angles drifting 16 a tick along its angle (sine table ctx+0x3A74): alpha 0x80 for 7 ticks, then out by 15 and ends */

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
} Glow_b233_01E03090;

typedef struct {
    u8 pad[0x3a74];
    u8 sin[1];
} Game_b233_01E03090;

static s32 func_01E03090_b233(Game_b233_01E03090 *g, Glow_b233_01E03090 *o) {
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

/* shape b233:01E031F0, 56 insns: a grey two-colour glow: both alphas held at 0x80 for 7 ticks, then both fade
   out by 11; stops when the first is gone */

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
} Glow_b233_01E031F0;

static s32 func_01E031F0_b233(s32 arg0, Glow_b233_01E031F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->life = 9;
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
    } else {
        if (o->col[3] > 0xC) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xC) {
            o->col2[3] -= 11;
        }
    }
    o->tick++;
    return 0;
}

/* shape b233:01E031F0, 56 insns: a grey two-colour glow: both alphas held at 0x80 for 7 ticks, then both fade
   out by 11; stops when the first is gone */

static s32 func_01E032D0_b233(s32 arg0, Glow_b233_01E031F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->life = 9;
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
        o->col2[3] = 0x80;
    } else {
        if (o->col[3] > 0xC) {
            o->col[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 0xC) {
            o->col2[3] -= 11;
        }
    }
    o->tick++;
    return 0;
}

/* shape b233:01E033B0, 56 insns: a purple glow that spins 1 a tick on all three axes and grows 2: in by 32 for 4 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[2];
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
} Glow_b233_01E033B0;

static s32 func_01E033B0_b233(s32 arg0, Glow_b233_01E033B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->kind = 2;
        o->h8 = 0;
        o->hA = 0;
        o->hC = 0;
        func_001076F0(o->col, 0x40, 0x10, 0x80);
        o->mode = 2;
    }
    if (o->tick < 4) {
        o->col[3] += 0x20;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->h8++;
    o->hA++;
    o->hC++;
    o->f38 += 2;
    o->tick++;
    return 0;
}

/* shape b233:01E03490, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
   for the first 2 ticks, then fades out by 6 and stops */

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
} Flash_b233_01E03490;

static s32 func_01E03490_b233(s32 arg0, Flash_b233_01E03490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xFA;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x80, 0x20, 0xF0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x7) {
        o->col[3] -= 6;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b233:01E03570, 88 insns: a blue/purple two-colour bolt (size 6, 20 wide, length 150 / 100 / 250 for angle 0 / 45 / 90) growing 40 and turning 10 a tick: in by 64 up to 0x80 for 2 ticks, then out by 5 and ends */

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
} Glow_b233_01E03570;

static s32 func_01E03570_b233(s32 arg0, Glow_b233_01E03570 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        func_001076F0(o->col, 0x20, 0x20, 0x80);
        func_001076F0(o->col2, 0x80, 0x20, 0x80);
        o->h8 = 20;
        if (o->ang == 0) {
            o->hA = 150;
        }
        if (o->ang == 45) {
            o->hA = 100;
        }
        if (o->ang == 90) {
            o->hA = 250;
        }
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 6) {
            o->col[3] -= 5;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 6) {
            o->col2[3] -= 5;
        } else {
            o->col2[3] = 0;
        }
    }
    o->hA += 40;
    o->tick++;
    o->ang += 10;
    return 0;
}

/* shape b233:01E036D0, 91 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 70, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x3930 is 1 */

typedef struct {
    u8 pad0[0x2870];
    f32 l0[4];
    f32 pos[3];
    u8 pad288C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad289C[0x1094];
    s32 state;
} Scene_b233_01E036D0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b233_01E036D0;

static s32 func_01E036D0_b233(Scene_b233_01E036D0 *g, Obj_b233_01E036D0 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 0.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 4.0f;
        g->l0[3] = 4.0f;
        g->f20 = 0.0f;
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

/* shape b233:01E03840, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3930 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3930];
    s32 state;
} Game_b233_01E03840;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b233_01E03840;

static s32 func_01E03840_b233(Game_b233_01E03840 *g, Fade_b233_01E03840 *o) {
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

/* shape b233:01E03900, 31 insns: b018:01E02DB0 family: func_001F7170(4, 0) with the module's two floats, then ends the object while its tick is under 65; counts the tick */

extern f32 D_01E04E00_b233;
extern f32 D_01E04E08_b233;

typedef struct {
    u8 pad0[0x10];
    s16 v;
} Ctx_b233_01E03900;

typedef struct {
    u8 pad0[0x32];
    s16 h32;
    u8 pad34[2];
    s16 h36;
    u8 pad38[0x1C];
    s16 h54;
    u8 pad56[2];
    s16 h58;
} Obj_b233_01E03900;

static s32 func_01E03900_b233(Ctx_b233_01E03900 *ctx, Obj_b233_01E03900 *o) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04E00_b233;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04E08_b233;
    func_001F7170(4, 0, (s32)&a, (s32)&b, 0);
    if (o->h32 < 65) {
        o->h36 = 0;
    }
    o->h32++;
    return 0;
}

/* shape b233:01E03980, 132 insns: b233:01E03B90's full-screen veil zooming in from its 0x30 counter (s = n / 1024,
   t = n / 512), alpha up by 12 (below 0x60) for 65 ticks, then fades by 12 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b233_01E03980;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b233_01E03980;

typedef struct {
    f32 s, t;
    Xyz_b233_01E03980 p;
} Vtx_b233_01E03980;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b233_01E03980 c;
    Vtx_b233_01E03980 v[2];
    u8 tail[0x20];
} Pkt_b233_01E03980;

typedef struct {
    u8 pad00[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
} Obj_b233_01E03980;

static inline void tag_b233_01E03980(Pkt_b233_01E03980 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E03980_b233(s32 unused, Obj_b233_01E03980 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b233_01E03980 pkt __attribute__((aligned(8)));
    f32 n;

    n = o->h30;
    tag_b233_01E03980((Pkt_b233_01E03980 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0x80;
    pkt.c.g = 0x80;
    pkt.c.b = 0x80;
    pkt.c.a = o->col[3];
    pkt.c.q = 1.0f;
    pkt.v[0].p.x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    if (o->h30 == 0) {
        pkt.v[0].s = n / 1024.0f;
        pkt.v[0].t = n / 512.0f;
        pkt.v[1].s = 0.625f;
        pkt.v[1].t = 0.875f;
    } else {
        pkt.v[0].s = n / 1024.0f;
        pkt.v[0].t = n / 512.0f;
        pkt.v[1].s = 0.625f;
        pkt.v[1].t = 0.875f;
    }
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0(&pkt, func_00207500(), 0);
    if (o->h32 < 0x41) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    if (o->h30 < 30) {
        o->h30++;
    }
    return 0;
}

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b233_01E03B90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b233_01E03B90;

typedef struct {
    f32 s, t;
    Xyz_b233_01E03B90 p;
} Vtx_b233_01E03B90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b233_01E03B90 c;
    Vtx_b233_01E03B90 v[2];
    u8 tail[0x20];
} Pkt_b233_01E03B90;

typedef struct {
    u8 pad00[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
} Obj_b233_01E03B90;

static inline void tag_b233_01E03B90(Pkt_b233_01E03B90 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E03B90_b233(s32 unused, Obj_b233_01E03B90 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b233_01E03B90 pkt __attribute__((aligned(8)));

    tag_b233_01E03B90((Pkt_b233_01E03B90 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0x80;
    pkt.c.g = 0x80;
    pkt.c.b = 0x80;
    pkt.c.a = o->col[3];
    pkt.c.q = 1.0f;
    pkt.v[0].p.x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    if (o->h30 == 0) {
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
    func_002075F0(&pkt, func_00207500(), 0);
    if (o->h32 < 55) {
        if (o->col[3] < 0x40) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    if (o->h30 < 30) {
        o->h30++;
    }
    return 0;
}

/* shape b233:01E03D60 (b233), 638 insns, 1 copy: b233 scene manager in b476:01E03810 form: setup (four joints,
   textures 4:10..15 and 4:2, two type-5 textures, s8 jitter table +-15), run the script, fill trails 0/1 from joints
   0/1 at frame 163, follow both, step the 150 slots (0x1E02FE0 and 0x1E03900 written out), draw eight slot kinds and
   return 1 / 4 / 2 / 6 at frames 160 / 210 / 1195 / 171..189, 8 once the countdown runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 f6;
    u8 pad8[0x1C];
    s32 (*fn)();
    u8 c0[4];
    u8 pad2C[4];
    s16 h30;
    s16 t;
    s16 h34;
    s16 used;
    s16 h38;
    s16 h3A;
    u8 pad3C[4];
} Slot_b233_01E03D60;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 uv[8];
    } u94;
    u8 padA4[0x1A];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x1D8];
    s32 tex[16];
    Slot_b233_01E03D60 slot[150];
    u8 pad2870[0x50];
    Vec4f tr[2][10];
    u8 pad2A00[0x3D0];
    s32 tex5[2];
    u8 pad2DD8[0xB58];
    s32 count;
    u8 pad3934[8];
    s32 ot;
    u8 pad3940[0x1E];
    s16 j[4];
    u8 pad3966[0xA];
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 crd[0x16C];
} Scene_b233_01E03D60;

static s32 func_01E03D60_b233(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void b233_01E01E60();
    extern void b233_01E009E0();
    extern void b233_01E04890();
    extern void b233_01E04A70();
    extern void b233_01E00E50();
    Scene_b233_01E03D60 *g = (Scene_b233_01E03D60 *)arg0;
    s32 m;
    Vec4f c;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
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
        func_00195108(g, 0x3BE0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 240;
        g->j[0] = func_001F5560(func_001F53A0(), 0x36, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x37, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0xC, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x14, 0);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    b233_01E01E60(g, 0);
    if (g->frame == 0xA3) {
        Vec4f *p = g->tr[0];

        func_001F5620(func_001F53A0(), g->j[0], (s32)&pa);
        for (i = 0; i < 9; i++, p++) {
            p->x = pa.x;
            p->y = pa.y;
            p->z = pa.z;
        }
    }
    if (g->frame == 0xA3) {
        Vec4f *p = g->tr[1];

        func_001F5620(func_001F53A0(), g->j[1], (s32)&pb);
        for (i = 0; i < 9; i++, p++) {
            p->x = pb.x;
            p->y = pb.y;
            p->z = pb.z;
        }
    }
    func_01E00080_b233((Vec_b004_01E00B40 *)&g->tr[0][9], 10, g->j[0]);
    func_01E00080_b233((Vec_b004_01E00B40 *)&g->tr[1][9], 10, g->j[1]);
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E02640_b233) {
                func_01E02640_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02860_b233) {
                func_01E02860_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E029C0_b233) {
                func_01E029C0_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02B60_b233) {
                func_01E02B60_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02C50_b233) {
                func_01E02C50_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02D60_b233) {
                func_01E02D60_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02F10_b233) {
                func_01E02F10_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02FE0_b233) {
                if (g->slot[i].used == 1) {
                    func_001076F0(g->slot[i].c0, 0x80, 0x10, 0xF0);
                    g->slot[i].f6 = 9;
                    g->slot[i].c0[3] = 0x80;
                    g->slot[i].h38 = 6;
                    g->slot[i].used = 2;
                }
                if (g->slot[i].t < 7) {
                    g->slot[i].c0[3] = 0x60;
                } else if (g->slot[i].c0[3] > 10) {
                    g->slot[i].c0[3] -= 9;
                } else {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
            }
            if (g->slot[i].fn == func_01E03090_b233) {
                func_01E03090_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E031F0_b233) {
                func_01E031F0_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E032D0_b233) {
                func_01E032D0_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E033B0_b233) {
                func_01E033B0_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03490_b233) {
                func_01E03490_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03570_b233) {
                func_01E03570_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E036D0_b233) {
                func_01E036D0_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03840_b233) {
                func_01E03840_b233(g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03900_b233) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04E00_b233;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04E08_b233;
                func_001F7170(4, 0, (s32)&a, (s32)&b, 0);
                if (g->slot[i].t < 65) {
                    g->slot[i].used = 0;
                }
                g->slot[i].t++;
            }
            if (g->slot[i].fn == func_01E03980_b233) {
                func_01E03980_b233((s32)g, &g->slot[i]);
            }
            if (g->slot[i].fn == func_01E03B90_b233) {
                func_01E03B90_b233((s32)g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == func_01E02D60_b233) {
                g->tex88 = g->tex5[1];
                func_00106080(rm, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                b233_01E04890(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E02FE0_b233) {
                b233_01E009E0(g, &g->slot[i], g->tr[0], g->tr[1]);
            }
            if (g->slot[i].fn == func_01E03090_b233) {
                g->tex88 = g->tex5[1];
                func_00106080(rm2, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                b233_01E04890(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E031F0_b233) {
                g->tex88 = g->tex[15];
                func_00106080(rm3, 0x97, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hBE = 0;
                g->tex88 = g->tex[15];
                func_00106080(rm4, 0x97, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->u94.uv[3] >>= 1;
                g->hBE = 0;
                func_01E01600_b233(g, &g->slot[i], g->tr[1], g->tr[0]);
                g->hBE = 0;
                func_01E01600_b233(g, &g->slot[i], g->tr[1], g->tr[0]);
                g->hBE = 0;
            }
            if (g->slot[i].fn == func_01E032D0_b233) {
                g->tex88 = g->tex[15];
                func_00106080(rm5, 0x97, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->hBE = 0;
                g->tex88 = g->tex[14];
                func_00106080(rm6, 0x8C, g->slot[i].h34, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1E;
                g->u94.uv[3] = 0x1E;
                g->hBE = 0;
                func_01E010E0_b233(g, &g->slot[i], g->tr[1], g->tr[0]);
                g->hBE = 0;
            }
            if (g->slot[i].fn == func_01E033B0_b233) {
                b233_01E04A70(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E03490_b233) {
                b233_01E00E50(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == func_01E03570_b233) {
                g->tex88 = g->tex[15];
                func_00106080(rm7, 0x9A, 1, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm7;
                c.x = g->slot[i].x;
                c.y = g->slot[i].y;
                c.z = g->slot[i].z;
                func_01E01BC0_b233(g, &g->slot[i], buf, c);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 160) {
        return 1;
    }
    if (g->frame == 210) {
        return 4;
    }
    if (g->frame == 1195) {
        return 2;
    }
    if (g->frame > 170 && g->frame < 190) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b233:01E04760, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x396E and 0x3968 and the two arguments; returns 1 if a
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
} Slot_b233_01E04760;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b233_01E04760 s[150];
    u8 pad2870[0x10C4];
    u8 r, g, b, a;
    u8 pad3938[0x30];
    s16 w;
    u8 pad396A[0x4];
    s16 v;
} Pool_b233_01E04760;

static s32 func_01E04760_b233(Pool_b233_01E04760 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b233_01E04760 *s = NULL;
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

/* shape b233:01E04890, 119 insns: b045:01E005A0's camera-facing sprite with a func_00207500 call first; calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function */

typedef struct {
    f32 s;
    f32 t;
} St_b233_01E04890;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b233_01E04890 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b233_01E04890;

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
} Obj_b233_01E04890;

static void func_01E04890_b233(u8 *self, Obj_b233_01E04890 *obj, Pk_b233_01E04890 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b233_01E04890 uv;
    f32 r;
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
    func_01E00150_b233((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

/* shape b233:01E04A70, 208 insns: a sprite sheet hung on scene segment h30 (ctx+0x31B0, 32 bytes: two points): the
   packet takes texture 0x9B at frame h34, the object's colour and the scene texture (UV through the module's
   b008:01E00080 helper); a quad of height h38 / 10 from the segment's first point to its second, the far edge pushed
   by h8/hA/hC thirds of the segment; depth-tested into ctx+0x393C and drawn twice */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b233_01E04A70;

typedef struct {
    f32 u, v;
} Uv_b233_01E04A70;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b233_01E04A70 uv;
    u64 pad18;
    Xyz_b233_01E04A70 v[4];
} Pk_b233_01E04A70;

typedef struct {
    Vec4f a;
    Vec4f b;
} Seg_b233_01E04A70;

typedef struct {
    u8 pad0[0x2EC];
    void *tex;
    u8 pad2F0[0x31B0 - 0x2F0];
    Seg_b233_01E04A70 seg[39];
    u8 pad3690[0x393C - 0x3690];
    s32 ot;
} Ctx_b233_01E04A70;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    u8 pad32[2];
    s16 h34;
    u8 pad36[2];
    s16 h38;
} Obj_b233_01E04A70;

static void func_01E04A70_b233(Ctx_b233_01E04A70 *g, Obj_b233_01E04A70 *o, Pk_b233_01E04A70 *p) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 depth[4];
    u8 td[0x10];
    Uv_b233_01E04A70 uv;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 h;

    func_00207500();
    func_00106080(td, 0x9B, o->h34, td);
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->uv.v = 0.0f;
    p->v[0].fog = 0;
    p->v[1].fog = 0;
    p->v[2].fog = 0;
    p->v[3].fog = 0;
    func_00107740(&uv, o->col);
    p->uv = uv;
    func_01E00150_b233((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
    func_00208700(p, g->tex, 1);
    h = o->h38;
    h /= 10.0f;
    func_00108CE0(q, 0.0f, h);
    dx = (g->seg[o->h30].b.x - g->seg[o->h30].a.x) / 3.0f;
    dy = (g->seg[o->h30].b.y - g->seg[o->h30].a.y) / 3.0f;
    dz = (g->seg[o->h30].b.z - g->seg[o->h30].a.z) / 3.0f;
    dx *= o->h8;
    dy *= o->hA;
    dz *= o->hC;
    q[0].x += g->seg[o->h30].a.x;
    q[0].y += g->seg[o->h30].a.y;
    q[0].z += g->seg[o->h30].a.z;
    q[2].x += g->seg[o->h30].a.x;
    q[2].y += g->seg[o->h30].a.y;
    q[2].z += g->seg[o->h30].a.z;
    q[1].x += g->seg[o->h30].b.x + dx;
    q[1].y += g->seg[o->h30].b.y + dy;
    q[1].z += g->seg[o->h30].b.z + dz;
    q[3].x += g->seg[o->h30].b.x + dx;
    q[3].y += g->seg[o->h30].b.y + dy;
    q[3].z += g->seg[o->h30].b.z + dz;
    if (func_00205630(q, 0x70000000, 0, p, depth) != 0) {
        func_002075F0(p, g->ot, func_001A23B0(depth[0]));
        func_002075F0(p, g->ot, func_001A23B0(depth[0]));
    }
}
