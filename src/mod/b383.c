#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b383(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00150_b383(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static Vec_b018_01E00EE0 func_01E005A0_b383(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b383", func_01E009E0_b383);

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

static void func_01E00E50_b383(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
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
                A[0] = func_01E005A0_b383(pa, 0, t);
                B[0] = func_01E005A0_b383(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b383(pa, 0, t);
                B[1] = func_01E005A0_b383(pq, 0, t);
            } else {
                A[0] = func_01E005A0_b383(a4, 0, t);
                B[0] = func_01E005A0_b383(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E005A0_b383(a4, 0, t);
                B[1] = func_01E005A0_b383(b4, 0, t);
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

static void func_01E01410_b383(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
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

static void func_01E016A0_b383(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
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

/* OVL_WARM */

/* shape b383:01E019A0, 197 insns: b383:01E01CC0's ring with each outer point jittered by -15..14 (rand() % 30 - 15) */

typedef struct {
    f32 x, y, z, w;
} Vec_b383_01E019A0;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b383_01E019A0;

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
} Obj_b383_01E019A0;

static void func_01E019A0_b383(Obj_b383_01E019A0 *o, Anim_b383_01E019A0 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b383_01E019A0 quad[4];
    Vec_b383_01E019A0 pos;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col + 4, 2);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    func_00108EF0(m, 0, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1) + func_0019A5C8() % 30 - 15.0f;
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0) + func_0019A5C8() % 30 - 15.0f;
        a = j + (an->start + 60);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1) + func_0019A5C8() % 30 - 15.0f;
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0) + func_0019A5C8() % 30 - 15.0f;
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 20;
    }
}

/* OVL_WARM */

/* shape b383:01E01CC0, 150 insns: constant variant of b148:01E02530 (20->60, 40->20, 9->18) */

typedef struct {
    f32 x, y, z, w;
} Vec_b383_01E01CC0;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b383_01E01CC0;

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
} Obj_b383_01E01CC0;

static void func_01E01CC0_b383(Obj_b383_01E01CC0 *o, Anim_b383_01E01CC0 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b383_01E01CC0 quad[4];
    Vec_b383_01E01CC0 pos;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col + 4, 2);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    func_00108EF0(m, 0, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 60);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 20;
    }
}

/* shape b383:01E01F20 (IWTThunder3), 260 insns, 2 copies: variant of b045:01E011B0 (sprite row into the given
   packet): per-sprite texture corner from the object ids (0x1E00150), square sprites of the sprite h38, camera
   rotation only, every corner shaken by the full table offset / 20; the same source as b357:01E02180 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b383_01E01F20;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b383_01E01F20 c;
    struct {
        u64 tc;
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } v[4];
} Pkt_b383_01E01F20;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b383_01E01F20;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 off;
    u8 padA[6];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 w30;
    u8 pad32[6];
    s16 h38;
} Spr_b383_01E01F20;
static void func_01E00150_b383();

static void func_01E01F20_b383(Obj_b383_01E01F20 *o, Spr_b383_01E01F20 *s, Pkt_b383_01E01F20 *p, s8 *tbl) {
    f32 w;
    extern Rgbaq_b383_01E01F20 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;
    f32 d;
    s32 h;
    f32 f;
    s8 *j;

    func_00207500();
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    p->c.q = 0.0f;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
    p->v[3].f = 0;
    p->c = func_00107740(s->col);
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    pos.x = s->x;
    pos.y = s->y;
    pos.z = s->z;
    func_00108EF0(m, &scale, NULL, &pos);
    for (i = 0; i < o->count; i++) {
        j = (s8 *)&o->ids[i];
        func_01E00150_b383(p, &o->rect, *(s16 *)j);
        w = s->h38;
        func_00108CE0(quad, w, w);
        func_00109100(quad, rot, 0, o->xD8);
        j = tbl + i;
        h = i >> 1;
        f = j[s->off];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].x += d;
        quad[1].x += d;
        quad[2].x += f * (s->w30 + h);
        quad[3].x += f * (s->w30 + h);
        f = j[s->off + 100];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].y += d;
        quad[1].y += d;
        quad[2].y += f * (s->w30 + h);
        quad[3].y += f * (s->w30 + h);
        f = j[s->off + 180];
        f /= 20.0f;
        d = f * (s->w30 + h);
        quad[0].z += d;
        quad[1].z += d;
        quad[2].z += f * (s->w30 + h);
        quad[3].z += f * (s->w30 + h);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
    }
}

/* shape b383:01E02330 (B383_W_S), 417 insns, 1 copy: the module spawn step: scene colour red, ticks the timer; tick
   125 a b383:01E03590 glow; ticks 80..111 step the 0x3064 frame (0..13, last in 0x3062); tick 155 the burst at joint
   0x3048 (03DF0, 029C0, seven 03B60, three 02AE0, five 02CC0, three 02F00, 03ED0); tick 159 nine 03130 there; ticks
   58 and 102 twenty 03330 at each of joints 0x304C/0x304E (2 lower); ticks 27..58 and 73..100 one 034A0 at each;
   ticks 125..152 one 03640 at joint 0x3048 */

typedef struct {
    u8 pad0[0x2D0];
    f32 px, py, pz;
    u8 pad2DC[0x3004 - 0x2DC];
    u8 rgba[4];
    u8 pad3008[0x3048 - 0x3008];
    s16 joint0;
    u8 pad304A[2];
    s16 joint1;
    s16 joint2;
    u8 pad3050[0x3062 - 0x3050];
    s16 h3062;
    s16 h3064;
    u8 pad3066[2];
    s16 t;
} Scene_b383_01E02330;

static s32 func_01E029C0_b383();
static s32 func_01E02AE0_b383();
static s32 func_01E02CC0_b383();
static s32 func_01E02F00_b383();
static s32 func_01E03130_b383();
static s32 func_01E03330_b383();
static s32 func_01E034A0_b383();
static s32 func_01E03590_b383();
static s32 func_01E03640_b383();
static s32 func_01E03B60_b383();
static s32 func_01E03DF0_b383();
static s32 func_01E03ED0_b383();
static s32 func_01E04F70_b383();

static void func_01E02330_b383(Scene_b383_01E02330 *s) {
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    s->rgba[0] = 0x80;
    s->rgba[1] = 0;
    s->rgba[2] = 0;
    s->rgba[3] = 0;
    s->t++;
    if (s->t == 125) {
        func_01E04F70_b383(s, func_01E03590_b383, 0);
    }
    if (s->t >= 80 && s->t < 112) {
        s->h3062 = s->h3064;
        s->h3064++;
        if (s->h3064 >= 14) {
            s->h3064 = 0;
        }
    }
    if (s->t == 155) {
        func_001F5620(func_001F53A0(), s->joint0, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        func_01E04F70_b383(s, func_01E03DF0_b383, 0);
        func_01E04F70_b383(s, func_01E029C0_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E03B60_b383, 0);
        func_01E04F70_b383(s, func_01E02AE0_b383, 0);
        func_01E04F70_b383(s, func_01E02AE0_b383, 0);
        func_01E04F70_b383(s, func_01E02AE0_b383, 0);
        s->h3062 = 0;
        func_01E04F70_b383(s, func_01E02CC0_b383, 0);
        func_01E04F70_b383(s, func_01E02CC0_b383, 0);
        func_01E04F70_b383(s, func_01E02CC0_b383, 0);
        func_01E04F70_b383(s, func_01E02CC0_b383, 0);
        func_01E04F70_b383(s, func_01E02CC0_b383, 0);
        s->h3062 = 0;
        func_01E04F70_b383(s, func_01E02F00_b383, 0);
        func_01E04F70_b383(s, func_01E02F00_b383, 0);
        func_01E04F70_b383(s, func_01E02F00_b383, 0);
        func_01E04F70_b383(s, func_01E03ED0_b383, 0);
    }
    if (s->t == 159) {
        func_001F5620(func_001F53A0(), s->joint0, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
        func_01E04F70_b383(s, func_01E03130_b383, 0);
    }
    if (s->t == 58 || s->t == 102) {
        func_001F5620(func_001F53A0(), s->joint1, &v);
        s->px = v.x;
        s->py = v.y - 2.0f;
        s->pz = v.z;
        for (i = 0; i < 20; i++) {
            func_01E04F70_b383(s, func_01E03330_b383, 0);
        }
        func_001F5620(func_001F53A0(), s->joint2, &v);
        s->px = v.x;
        s->py = v.y - 2.0f;
        s->pz = v.z;
        for (i = 0; i < 20; i++) {
            func_01E04F70_b383(s, func_01E03330_b383, 0);
        }
    }
    if (s->t >= 27 && s->t < 59) {
        func_001F5620(func_001F53A0(), s->joint1, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        for (i = 0; i < 1; i++) {
            func_01E04F70_b383(s, func_01E034A0_b383, 0);
        }
        func_001F5620(func_001F53A0(), s->joint2, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        for (i = 0; i < 1; i++) {
            func_01E04F70_b383(s, func_01E034A0_b383, 0);
        }
    }
    if (s->t >= 73 && s->t < 101) {
        func_001F5620(func_001F53A0(), s->joint1, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        for (i = 0; i < 1; i++) {
            func_01E04F70_b383(s, func_01E034A0_b383, 0);
        }
        func_001F5620(func_001F53A0(), s->joint2, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        for (i = 0; i < 1; i++) {
            func_01E04F70_b383(s, func_01E034A0_b383, 0);
        }
    }
    if (s->t >= 125 && s->t < 153) {
        func_001F5620(func_001F53A0(), s->joint0, &v);
        s->px = v.x;
        s->py = v.y;
        s->pz = v.z;
        func_01E04F70_b383(s, func_01E03640_b383, 0);
    }
}

/* shape b383:01E029C0, 72 insns: a grey ring at the model point: set up once (frame 5, random angle, size 3, height 0);
   full alpha on the first frame, then down by 18 until it ends; sub-frame grows to 7; rises by its size each frame */

typedef struct {
    u8 pad0[6];
    s16 y;
    s16 dy;
    u8 padA[0x1E];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b383_01E029C0;

static s32 func_01E029C0_b383(void *arg0, Obj_b383_01E029C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    Vec4f v;

    func_001F6160(func_001F53A0(), &v);
    if (o->state == 1) {
        o->h38 = 5;
        o->sub = 0;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->dy = 3;
        o->y = 0;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    if (o->t < 1) {
        if (o->c0[3] < 0x80) {
            o->c0[3] = 0x80;
        }
    } else if (o->c0[3] > 0x13) {
        o->c0[3] -= 0x12;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    if (o->t != 0) {
        o->y += o->dy;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[0xE];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b383_01E02AE0;

static s32 func_01E02AE0_b383(s32 unused, Obj_b383_01E02AE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 10;
        o->w10 = func_0019A5C8() % 0x4000 + 0x2000;
        o->w14 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->h34 = func_0019A5C8() % 7;
        o->h36 = 2;
        o->hE = func_0019A5C8() % 2 + 2;
        if (o->h30 == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->col, 0, 0x80, 0x80);
        }
    }
    if (o->h32 < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    if (o->h32 % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x40, 0);
    } else {
        func_001076F0(o->col, 0xB0, 0x80, 0);
    }
    if (o->h32 != 0) {
        o->h38 += o->hE;
    }
    o->h32++;
    return 0;
}

/* shape b383:01E02CC0, 144 insns: b383:01E02F00 with three random turns, rising 1..2, alpha down by 9 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 rise;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 h;
} Fx_b383_01E02CC0;

static s32 func_01E02CC0_b383(s32 arg0, Fx_b383_01E02CC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->frame = func_0019A5C8() % 7;
        o->mode = 2;
        if (o->kind == 0) {
            o->rise = func_0019A5C8() % 2 + 1;
            o->h6 = 1;
        } else {
            o->rise = func_0019A5C8() % 2 + 1;
            o->h6 = 4;
        }
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->col, 0, 0x80, 0x80);
        }
    }
    if (o->t < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x40, 0);
    } else {
        func_001076F0(o->col, 0xB0, 0x80, 0);
    }
    if (o->t != 0) {
        o->h += o->rise;
    }
    if (o->kind == 1 && o->t != 0) {
        o->h6 += 3;
    }
    o->t++;
    return 0;
}

/* shape b383:01E02F00, 138 insns: b443:01E030C0 family rising spark (tilt 0..0x3FFF, random spin, frame 0..6; kind 0 orange with life 1, kind 1 cyan with life 4 growing 3 per tick; rising 4..6): alpha up by 64 to 0x80 for 2 ticks, then down by 13; colour flashes orange/gold every tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 rise;
    s32 tilt;
    s32 spin;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 h;
} Fx_b383_01E02F00;

static s32 func_01E02F00_b383(s32 arg0, Fx_b383_01E02F00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->mode == 1) {
        o->h = 0;
        base = 0;
        o->tilt = func_0019A5C8() % 0x4000 + base;
        o->spin = func_0019A5C8() % 65535;
        o->frame = func_0019A5C8() % 7;
        o->mode = 2;
        if (o->kind == 0) {
            o->rise = func_0019A5C8() % 3 + 4;
            o->h6 = 1;
        } else {
            o->rise = func_0019A5C8() % 3 + 4;
            o->h6 = 4;
        }
        if (o->kind == 0) {
            func_001076F0(o->col, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->col, 0, 0x80, 0x80);
        }
    }
    if (o->t < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x40, 0);
    } else {
        func_001076F0(o->col, 0xB0, 0x80, 0);
    }
    if (o->t != 0) {
        o->h += o->rise;
    }
    if (o->kind == 1 && o->t != 0) {
        o->h6 += 3;
    }
    o->t++;
    return 0;
}

/* shape b383:01E03130, 126 insns: b383:01E03640 with a random size 30..109, start height 100..349 and rise 5..9 */

typedef struct {
    u8 pad0[6];
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
} Glow_b383_01E03130;

static s32 func_01E03130_b383(s32 arg0, Glow_b383_01E03130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 80 + 30;
        o->kind = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->h30 = func_0019A5C8() % 250 + 100;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 8 + 3;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 6) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->tick++;
    return 0;
}

/* shape b383:01E03330, 90 insns: b115:01E01980 family: a grey/white spark (size 60, random frame 0..6) at two random angles drifting 11 a tick along its angle (sine table ctx+0x316C): alpha 0xF0 for 7 ticks, then out by 0x14 and ends */

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
} Glow_b383_01E03330;

typedef struct {
    u8 pad[0x316c];
    u8 sin[1];
} Game_b383_01E03330;

static s32 func_01E03330_b383(Game_b383_01E03330 *g, Glow_b383_01E03330 *o) {
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
        o->col[3] = 0xF0;
    } else if (o->col[3] > 0x15) {
        o->col[3] -= 0x14;
    } else {
        o->mode = 0;
    }
    o->h8 = func_001A22C0(o->h8 + 11.0f * func_00108030(g->sin, o->ang, 0));
    o->hC = func_001A22C0(o->hC + 11.0f * func_00108030(g->sin, o->ang, 1));
    o->tick++;
    return 0;
}

/* shape b383:01E034A0, 59 insns: a white spark of size 40 at a random frame 0..6 and two random angles: alpha 0xF0 for 2 ticks, then out by 20 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b383_01E034A0;

static s32 func_01E034A0_b383(s32 arg0, Glow_b383_01E034A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 40;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] = 0xF0;
    } else if (o->col[3] > 0x15) {
        o->col[3] -= 20;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b383:01E03590, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0xF0, 0x10, 0x10) and fields;
   alpha 0x60 for the first 0x19 ticks, then fade out by 9 and stop */

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
} Glow_b383_01E03590;

static s32 func_01E03590_b383(s32 arg0, Glow_b383_01E03590 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0xF0, 0x10, 0x10);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x19) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b383:01E03640, 119 insns: a grey spark (size 10, frame 0 stepping every other tick to 6, angle 10..109, spin 4..8, size 0..9) held 3..10 ticks: in by 64 up to 0xC0, then ends; three random turns 0..359 every tick */

typedef struct {
    u8 pad0[6];
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
} Glow_b383_01E03640;

static s32 func_01E03640_b383(s32 arg0, Glow_b383_01E03640 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 10;
        o->kind = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->h30 = func_0019A5C8() % 100 + 10;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 4;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 8 + 3;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 6) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
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

static s32 func_01E03830_b383(s32 arg0, Glow_b218_01E02B60 *o) {
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

static s32 func_01E038E0_b383(s32 arg0, Glow_b218_01E02C10 *o) {
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

static s32 func_01E03990_b383(s32 arg0, Glow_b218_01E02CC0 *o) {
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

/* shape b383:01E03A60, 64 insns: a blue two-colour flash (size 6, scale 10): full alpha on its first tick, then out by 15 (second colour by 7) and ends */

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
} Glow_b383_01E03A60;

static s32 func_01E03A60_b383(s32 arg0, Glow_b383_01E03A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x30, 0x30, 0x80);
        func_001076F0(o->col2, 0x30, 0x30, 0x80);
        o->h6 = 8;
        o->col[3] = 0x80;
        o->col2[3] = 0x40;
        o->h2 = 0;
        o->h0 = 0;
        o->h4 = 0;
        o->hA = 10;
        o->h8 = 10;
        o->hC = 10;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 1) {
        o->col[3] = 0x80;
    } else {
        if (o->col[3] > 0x10) {
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
    o->tick++;
    return 0;
}

/* shape b383:01E03B60, 97 insns: on start 0x38 = 0, rotation (-0x2000..0x1FFF, random), variant 0..6, step 2..4,
   0x6 = 20, 0x30 = 0 (then picks the orange colour), second colour (0xA0, 8, 8); alpha 0x80 for 3 ticks, then fades
   by 14 and stops; 0x38 grows by the step after the first tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 step;
    u8 padA[6];
    s32 rot[2];
    u8 pad18[0x10];
    u8 col[4];
    u8 col2[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b383_01E03B60;

static s32 func_01E03B60_b383(s32 arg0, Fx_b383_01E03B60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->rot[0] = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->step = func_0019A5C8() % 3 + 2;
        o->f6 = 20;
        o->f30 = 0;
        if (o->f30 == 0) {
            func_001076F0(o->col, 0xC0, 0x80, 0);
        } else {
            func_001076F0(o->col, 0, 0xA0, 0xA0);
        }
        func_001076F0(o->col2, 0xA0, 8, 8);
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f38 += o->step;
    }
    o->tick++;
    return 0;
}

/* shape b383:01E03CF0, 61 insns: a blue spark: set up once (blue, frame 9, random size 5..12 and height 44..60),
   fades in by 27 to 0xC0 for 28 frames, then out by 9 until it ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 w;
    s16 h;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b383_01E03CF0;

static s32 func_01E03CF0_b383(void *arg0, Obj_b383_01E03CF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        o->h6 = 9;
        o->c0[3] = 0;
        o->h = func_0019A5C8() % 17 + 0x2C;
        o->w = func_0019A5C8() % 8 + 5;
        o->h38 = 2;
        o->state = 2;
    }
    if (o->t < 0x1C) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x1B;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b383:01E03DF0, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
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
} Flash_b383_01E03DF0;

static s32 func_01E03DF0_b383(s32 arg0, Flash_b383_01E03DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0xC8;
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

/* shape b383:01E03ED0, 92 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 140, at the object's point),
   raises its strength by 0.2f to 1, then lowers it by 0.1f until it ends; applies the light while live and ends when the
   scene state at 0x3000 is 1 */

typedef struct {
    u8 pad0[0x2AA0];
    f32 l0[4];
    f32 pos[3];
    u8 pad2ABC[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad2ACC[0x534];
    s32 state;
} Scene_b383_01E03ED0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b383_01E03ED0;

static s32 func_01E03ED0_b383(Scene_b383_01E03ED0 *g, Obj_b383_01E03ED0 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 5.0f;
        g->l0[2] = 0.0f;
        g->l0[3] = 0.0f;
        g->f20 = 0.0f;
        g->range = 140.0f;
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

/* shape b207:01E03B20, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3000 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3000];
    s32 state;
} Game_b207_01E03B20;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b207_01E03B20;

static s32 func_01E04040_b383(Game_b207_01E03B20 *g, Fade_b207_01E03B20 *o) {
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

static s32 func_01E04100_b383(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E05600_b383;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E05608_b383;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b383", func_01E04150_b383);

/* shape b207:01E04730, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3062 and the two arguments; returns 1 if a
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
} Slot_b207_01E04730;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x224];
    Slot_b207_01E04730 s[150];
    u8 pad2A74[0x590];
    u8 r, g, b, a;
    u8 pad3008[0x5A];
    s16 v;
} Pool_b207_01E04730;

static s32 func_01E04F70_b383(Pool_b207_01E04730 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b207_01E04730 *s = NULL;
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

/* shape b383:01E05090, 131 insns: b195:01E03200 with frame 0x14, scene texture 0x2A78, packet list 0x300C and depth 0x3034 */

typedef struct {
    f32 s;
    f32 t;
} St_b383_01E05090;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b383_01E05090 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b383_01E05090;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    u8 padE[0x1A];
    u8 tex[8];
    u8 pad30[4];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Obj_b383_01E05090;

typedef struct {
    u8 pad0[0x2A78];
    void *tex;
    u8 pad2A7C[0x590];
    s32 ctx;
    u8 pad4030[0x24];
    f32 depth[1];
} Scene_b383_01E05090;

static void func_01E05090_b383(Scene_b383_01E05090 *g, Obj_b383_01E05090 *obj, Pk_b383_01E05090 *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    Rect_b008_01E00080 rect[2];
    Vec4f world[4];
    s32 rot[4];
    St_b383_01E05090 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0x14, obj->h34, rect);
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
        func_01E00150_b383((Pk_b008_01E00080 *)pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
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
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, g->depth) != 0) {
            func_002075F0((s32)pk, g->ctx, func_001A23B0(g->depth[0]));
        }
    }
}

/* shape b383:01E052A0, 185 insns: b357:01E02770's ring as six camera-facing sprites in an upright circle (y/z,
   radius 0x06, 60 apart from the start angle 0x3A) around the object, each sized obj->size and turned to face the camera's yaw, sent count+1 times (self+0xB8).
   Calls the module's sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b383_01E052A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b383_01E052A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b383_01E052A0;

typedef struct {
    s16 x, y, z;
    s16 rad;
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
    s16 ang;
} Obj_b383_01E052A0;

static void func_01E052A0_b383(u8 *self, Obj_b383_01E052A0 *obj, Pk_b383_01E052A0 *pk) {
    extern void func_00108EF0();
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    f32 m[16];
    Vec4f pos;
    f32 world[16];
    f32 depth[4];
    s32 rot[4];
    St_b383_01E052A0 uv;
    f32 r;
    s32 k;
    s32 t;
    s32 j;
    s16 a;

    a = 0;
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
    func_01E00150_b383((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    func_00108EF0(world, 0, &obj->rx, &pos);
    pos.x = 0.0f;
    for (k = 0; k < 6; k++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        t = obj->ang + a;
        pos.z = obj->rad * func_00108030(self + 0xD8, t, 1);
        pos.y = obj->rad * func_00108030(self + 0xD8, t, 0);
        func_00107070(m, 0, pos.x);
        func_00107070(m, 1, pos.y);
        func_00107070(m, 2, pos.z);
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            for (j = 0; j < *(s16 *)(self + 0xB8) + 1; j++) {
                func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
            }
        }
        a += 60;
    }
}
