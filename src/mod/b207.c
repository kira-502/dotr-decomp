#include "common.h"

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E00080_b207(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00260_b207(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

static void func_01E00330_b207(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E00780_b207(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
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
    func_01E00330_b207((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E00AB0_b207(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b207:01E00EF0, 220 insns: variant of b064:01E00C10 (ring of quads around a point): the four corner colours
   from the anim's two colours (0x28 inner, 0x2C outer), scale 0.1, inner edge at radius/2 and outer at radius,
   outer corners raised to the anim's h0A, 18 segments 40 apart (step 20), drawn once */

typedef struct {
    f32 x, y, z, w;
} Vec_b207_01E00EF0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b207_01E00EF0;

typedef struct {
    Rgbaq_b207_01E00EF0 c;
    u64 st;
    u64 xyz;
} Vtx_b207_01E00EF0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b207_01E00EF0 v[4];
} Pkt_b207_01E00EF0;

typedef struct {
    s16 x, y, z;
    u8 pad06[4];
    s16 h0A;
    u8 pad0C[4];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b207_01E00EF0;

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
} Obj_b207_01E00EF0;

static void func_01E00EF0_b207(Obj_b207_01E00EF0 *o, Anim_b207_01E00EF0 *an, Pkt_b207_01E00EF0 *p) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b207_01E00EF0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b207_01E00EF0 quad[4];
    Vec_b207_01E00EF0 pos;
    Vec_b207_01E00EF0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(an->col);
    p->v[1].c = func_00107740(an->col);
    p->v[2].c = func_00107740(an->col + 4);
    p->v[3].c = func_00107740(an->col + 4);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = an->h0A;
    quad[3].y = an->h0A;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius >> 1) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius >> 1) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 40);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius >> 1) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius >> 1) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            func_002075F0(p, o->target, (u32)depth);
        }
        j += 20;
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

static void func_01E01260_b207(Obj_b134_01E00820 *o, Rib_b134_01E00820 *s, Vec_b018_01E00EE0 *pa, Vec_b018_01E00EE0 *pb) {
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
                A[0] = func_01E00AB0_b207(pa, 0, t);
                B[0] = func_01E00AB0_b207(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E00AB0_b207(pa, 0, t);
                B[1] = func_01E00AB0_b207(pq, 0, t);
            } else {
                A[0] = func_01E00AB0_b207(a4, 0, t);
                B[0] = func_01E00AB0_b207(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E00AB0_b207(a4, 0, t);
                B[1] = func_01E00AB0_b207(b4, 0, t);
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

static void func_01E01820_b207(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
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

static void func_01E01AB0_b207(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
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

/* shape b064:01E00C10, 200 insns: variant of b027:01E02590 (ring of quads around a point): two colour sets,
   ring width from the anim (s16 at 6) instead of 20, 18 segments 20 apart */

typedef struct {
    f32 x, y, z, w;
} Vec_b064_01E00C10;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b064_01E00C10;

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
} Obj_b064_01E00C10;

static void func_01E01DB0_b207(Obj_b064_01E00C10 *o, Anim_b064_01E00C10 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b064_01E00C10 quad[4];
    Vec_b064_01E00C10 pos;
    Vec_b064_01E00C10 scale;
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
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 20);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 20;
    }
}

/* shape b207:01E020D0 (B207_W_S), 369 insns: advances the effect timer, places emitters on model joints, and spawns the ring and trail layers at their scene frames. */
typedef struct Scene_b207_01E020D0 {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x320 - 0x2E0];
    Vec4f a;
    Vec4f b;
    u8 pad340[0x2AE0 - 0x340];
    Vec4f saved;
    u8 pad2AF0[0x3004 - 0x2AF0];
    u8 col[4];
    u8 pad3008[0x3048 - 0x3008];
    s16 ja, jb, jc, jd;
    u8 pad3050[0x3062 - 0x3050];
    s16 side;
    s16 unused;
    s16 t;
} Scene_b207_01E020D0;

#pragma optimization_level 3

static void func_01E020D0_b207(Scene_b207_01E020D0 *g) {
    extern void b207_01E04730();
    extern void b207_01E029A0(), b207_01E02BC0(), b207_01E02DE0(), b207_01E03000();
    extern void b207_01E03590(), b207_01E03780(), b207_01E03C30();
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f v;
    s32 i;
    s16 angle;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0xA) {
        i = 0;
        angle = (s16)(i * 30);
        do {
            g->side = (s16) angle;
            b207_01E04730(g, b207_01E03590, 0);
            i += 1;
            angle = (s16)(angle + 30);
        } while (i < 0xC);
    }
    if (g->t < 4) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        i = 0;
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        do {
            b207_01E04730(g, b207_01E029A0, 0);
            i += 1;
        } while (i < 0xC);
    }
    if (g->t == 0x82) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b207_01E04730(g, b207_01E03780, 0);
        i = 0;
        do {
            b207_01E04730(g, b207_01E02BC0, 0);
            i += 1;
        } while (i < 0xC);
        i = 0;
        do {
            b207_01E04730(g, b207_01E02DE0, 0);
            i += 1;
        } while (i < 0xC);
    }
    if ((g->t > 93) && (g->t < 0x82)) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        b207_01E04730(g, b207_01E03000, 0);
    }
    if (g->t == 0x33) {
        func_001F5620(func_001F53A0(), g->jb, (&g->saved));
    }
    if ((g->t > 51) && (g->t < 0x41)) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        i = 0;
        do {
            i += 1;
            g->pos.x = g->saved.x;
            g->pos.y = g->saved.y;
            g->pos.z = g->saved.z;
        } while (i < 6);
    }
    if (g->t == 1) {
        func_001F5F90(func_001F53A0(), &g->a);
        func_001F5F90(func_001F53A0(), &g->b);
    }
    if ((g->t > 111) && (g->t < 0xC3)) {
        g->a.z = (g->a.z - 2.4f);
        g->pos.x = g->a.x;
        g->pos.y = (g->a.y - 10.0f);
        g->pos.z = (40.0f + g->a.z);
        g->side = 0;
    }
    if (g->t == 0x50) {
        func_001F5620(func_001F53A0(), g->jc, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
        func_001F5620(func_001F53A0(), g->jd, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
    }
    if ((g->t > 170) && (g->t < 0xE1)) {
        g->b.z = (g->b.z - 3.8f);
        g->pos.x = g->b.x;
        g->pos.y = (g->b.y - 10.0f);
        g->pos.z = (40.0f + g->b.z);
        g->side = 1;
    }
    if ((g->t >= 0x70) && (g->t < 0xBF)) {
        g->pos.x = g->a.x;
        g->pos.y = (g->a.y - 10.0f);
        g->pos.z = (40.0f + g->a.z);
        g->side = 0;
    }
    if ((g->t >= 0xA9) && (g->t < 0xDD)) {
        g->pos.x = g->b.x;
        g->pos.y = (g->b.y - 10.0f);
        g->pos.z = (40.0f + g->b.z);
        g->side = 1;
    }
    if (g->t == 1) {
        b207_01E04730(g, b207_01E03C30, 0);
    }
    if ((g->t == 0x30) || (g->t == 0x31) || (g->t == 0x32) || (g->t == 0x33)) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 0;
    }
    if ((g->t == 0x33) || (g->t == 0x34) || (g->t == 0x35) || (g->t == 0x36)) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->side = 1;
    }
}

#pragma optimization_level reset

/* shape b207:01E026A0, 134 insns: b194:01E00C60 with the sine table at g+0x316C */

typedef struct {
    u8 pad0[0x316C];
    u8 trig[1];
} World_b207_01E026A0;

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
} Wisp_b207_01E026A0;

static s32 func_01E026A0_b207(World_b207_01E026A0 *w, Wisp_b207_01E026A0 *o) {
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

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E028C0_b207(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

/* shape b207:01E029A0, 134 insns: b207:01E02BC0 falling from 70: it fades out once below 12 */

typedef struct {
    u8 pad0000[0x3000];
    s32 w3B00;
} Mgr_b207_01E029A0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
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
} Obj_b207_01E029A0;

static s32 func_01E029A0_b207(Mgr_b207_01E029A0 *m, Obj_b207_01E029A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->h36 == 1) {
        o->h38 = 70;
        base = 0;
        o->w10 = func_0019A5C8() % 0x4000 + base;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = func_0019A5C8() % 7;
        o->h36 = 2;
        o->hE = func_0019A5C8() % 3 + 4;
        o->h6 = 1;
        if (o->h30 == 0) {
            func_001076F0(o->c28, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c28, 0, 0x80, 0x80);
        }
    }
    if (o->h32 < 2) {
        if (o->c28[3] < 0xA0) {
            o->c28[3] += 0x50;
        }
    } else {
        if (o->h38 < 12) {
            if (o->c28[3] > 20) {
                o->c28[3] -= 19;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h38 < -12) {
            o->h36 = 0;
        }
        if (m->w3B00 < 10) {
            if (o->c28[3] > 16) {
                o->c28[3] -= 15;
            } else {
                o->h36 = 0;
            }
        }
    }
    if (o->h32 % 2 == 1) {
        func_001076F0(o->c28, 0x80, 0x40, 0);
    } else {
        func_001076F0(o->c28, 0xB0, 0x80, 0);
    }
    o->h32++;
    o->h38 -= o->hE;
    return 0;
}

/* shape b207:01E02BC0, 133 insns: b207:01E02DE0 variant: spin start 0..0x3FFF, fall speed in hE, h6 1, one colour,
   a fade-in by 80 to 0xA0, the fade-out past 80 and an end below -12, and a gold blink */

typedef struct {
    u8 pad0000[0x3000];
    s32 w3B00;
} Mgr_b207_01E02BC0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
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
} Obj_b207_01E02BC0;

static s32 func_01E02BC0_b207(Mgr_b207_01E02BC0 *m, Obj_b207_01E02BC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->h36 == 1) {
        o->h38 = 0;
        base = 0;
        o->w10 = func_0019A5C8() % 0x4000 + base;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = func_0019A5C8() % 7;
        o->h36 = 2;
        o->hE = func_0019A5C8() % 3 + 4;
        o->h6 = 1;
        if (o->h30 == 0) {
            func_001076F0(o->c28, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c28, 0, 0x80, 0x80);
        }
    }
    if (o->h32 < 2) {
        if (o->c28[3] < 0xA0) {
            o->c28[3] += 0x50;
        }
    } else {
        if (o->h38 > 80) {
            if (o->c28[3] > 20) {
                o->c28[3] -= 19;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h38 < -12) {
            o->h36 = 0;
        }
        if (m->w3B00 < 10) {
            if (o->c28[3] > 16) {
                o->c28[3] -= 15;
            } else {
                o->h36 = 0;
            }
        }
    }
    if (o->h32 % 2 == 1) {
        func_001076F0(o->c28, 0x80, 0x40, 0);
    } else {
        func_001076F0(o->c28, 0xB0, 0x80, 0);
    }
    o->h32++;
    o->h38 += o->hE;
    return 0;
}

/* shape b207:01E02DE0, 133 insns: b218:01E02F10 with orange (0x80/0x40/0) or teal (0/0x80/0x80) and red 0x80/8/8
   colours, h6 10, a fade-in by 32 to 0x40, the manager count at 0x3000, a brown blink on odd/even ticks, and the
   growth applied every tick after the count */

typedef struct {
    u8 pad0000[0x3000];
    s32 w3B00;
} Mgr_b207_01E02DE0;

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
} Obj_b207_01E02DE0;

static s32 func_01E02DE0_b207(Mgr_b207_01E02DE0 *m, Obj_b207_01E02DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 0;
        o->w10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = func_0019A5C8() % 7;
        o->h36 = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        o->h6 = 10;
        if (o->h30 == 0) {
            func_001076F0(o->c28, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c28, 0, 0x80, 0x80);
        }
        func_001076F0(o->c2C, 0x80, 8, 8);
    }
    if (o->h32 < 2) {
        if (o->c28[3] < 0x40) {
            o->c28[3] += 0x20;
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
    if (o->h32 % 2 == 1) {
        func_001076F0(o->c28, 0x30, 0x20, 0);
    } else {
        func_001076F0(o->c28, 0x50, 0x40, 0);
    }
    o->h32++;
    o->h38 += o->h8;
    return 0;
}

typedef struct {
    u8 pad00[0x28];
    u8 col0[4];
    u8 col1[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b207_01E03000;

static s32 func_01E03000_b207(s32 unused, Obj_b207_01E03000 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 60;
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0xC0, 0xC0, 0);
        o->h3A = o->h30;
        o->h36 = 2;
        o->col1[3] = 0;
    }
    if (o->h32 <= 0) {
        o->col0[3] += 0x50;
    } else {
        if (o->col0[3] > 10) {
            o->col0[3] -= 9;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    if (o->h38 < 0) {
        o->h38 -= 2;
    }
    return 0;
}

/* shape b207:01E030D0, 79 insns, 2 copies: a streak flash: size and turn by kind (0..3) once, two colours; full alpha for 5
   frames, then fades out (b003:01E01780 family) */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Obj_b207_01E030D0;

static s32 func_01E030D0_b207(void *arg0, Obj_b207_01E030D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->state == 1) {
        if ((k = o->kind) == 0) {
            o->h38 = 0x19;
            o->h34 = 6;
        } else if (k == 1) {
            o->h38 = 6;
            o->h34 = 0x19;
        } else if (k == 2) {
            o->h38 = 0x15;
            o->h34 = 6;
            o->h3A = 0x2D;
        } else if (k == 3) {
            o->h38 = 0x15;
            o->h34 = 6;
            o->h3A = -0x2D;
        }
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x80, 0x40, 0);
        o->state = 2;
    }
    if (o->t < 5) {
        o->c0[3] = 0x40;
        o->c1[3] = 0;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 7;
    } else {
        o->state = 0;
    }
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

static s32 func_01E03210_b207(s32 unused, Spark_b018_01E02950 *o) {
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

/* shape b207:01E03380, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x10, 0x60, 0x10) and fields;
   alpha 0x60 for the first 0x140 ticks, then fade out by 9 and stop */

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
} Glow_b207_01E03380;

static s32 func_01E03380_b207(s32 arg0, Glow_b207_01E03380 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x10, 0x60, 0x10);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E03430, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x60, 0x60, 0x60) and fields;
   alpha 0x80 for the first 0x140 ticks, then fade out by 9 and stop */

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
} Glow_b207_01E03430;

static s32 func_01E03430_b207(s32 arg0, Glow_b207_01E03430 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E034E0, 43 insns: constant variant of b018:01E02AC0 (glow): on start colour (0x20, 0x20, 0x20) and fields;
   alpha 0x80 for the first 0x140 ticks, then fade out by 9 and stop */

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
} Glow_b207_01E034E0;

static s32 func_01E034E0_b207(s32 arg0, Glow_b207_01E034E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->life = 9;
        o->col[3] = 0x80;
        o->f38 = 6;
        o->mode = 2;
    }
    if (o->tick < 0x140) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E03590, 123 insns: a yellow-white circling glow on a model joint: frame 40, angle from its start value; alpha up by 4 for
   18 frames, then flickering 0x40/0x50; sits on the joint, circling 3 around it as the angle turns 10 a frame; ends at frame 211 */

typedef struct {
    u8 pad0[0x3048];
    s16 joint;
    u8 pad304A[0x122];
    u8 sin[1];
} Game_b207_01E03590;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 c1[4];
    s16 ang0;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b207_01E03590;

static s32 func_01E03590_b207(Game_b207_01E03590 *g, Obj_b207_01E03590 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    struct {
        f32 x, y, z, w;
        f32 pad[4];
    } v;

    func_00108030(g->sin, o->ang, 0);
    if (o->state == 1) {
        o->h38 = 0x28;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0xC0, 0xC0, 0);
        o->ang = o->ang0;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x12) {
        o->c0[3] += 4;
    } else if (o->t % 2 == 1) {
        o->c0[3] = 0x40;
    } else {
        o->c0[3] = 0x50;
    }
    func_001F5620(func_001F53A0(), g->joint, &v);
    o->x = func_001A22C0(v.x);
    o->y = func_001A22C0(v.y);
    o->z = func_001A22C0(v.z);
    o->x = func_001A22C0(o->x + 3.0f * func_00108030(g->sin, o->ang, 0));
    o->z = func_001A22C0(o->z + 3.0f * func_00108030(g->sin, o->ang, 1));
    o->t++;
    if (o->t > 0xD2) {
        o->state = 0;
    }
    o->ang += 0xA;
    if (o->ang >= 0x168) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b207:01E03780, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
   for the first 2 ticks, then fades out by 10 and stops */

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
} Flash_b207_01E03780;

static s32 func_01E03780_b207(s32 arg0, Flash_b207_01E03780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x12C;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0xF0, 0xF0, 0x10);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b207:01E03860, 173 insns: a flash light at g+0x2AA0 (b490:01E00E90's kind): on start colour 0, height 0/70/0 and the
   effect's position; it brightens (strength +0.2 to 1, colour +42/+21/+10 up to 128/128/64), then once full fades
   (strength -0.1, colour -16/-16/-8) until it ends; func_001F6C10 gets the light (or 0 once ended); it also ends when
   the light's state word is 1 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x534];
    s32 state;
} Light_b207_01E03860;

typedef struct {
    u8 pad0[0x2AA0];
    Light_b207_01E03860 light;
} Game_b207_01E03860;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x2A];
    s16 f30;
    u8 pad32[4];
    s16 mode;
} Fx_b207_01E03860;

static s32 func_01E03860_b207(Game_b207_01E03860 *g, Fx_b207_01E03860 *o) {
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

static s32 func_01E03B20_b207(Game_b207_01E03B20 *g, Fade_b207_01E03B20 *o) {
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

static s32 func_01E03BE0_b207(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E04B00_b207;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E04B08_b207;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03C30_b207(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b207", func_01E03C40_b207);

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

static s32 func_01E04730_b207(Pool_b207_01E04730 *o, s32 a, s32 b) {
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

/* shape b207:01E04850, 142 insns: b069:01E01A70 family four-part quad (func_00108D60 parts, twisted by the scene table at ctx+0x316C) at position + speed/10, scale 1; the setup pass colours it (three colA corners, one colB) */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b207_01E04850;

typedef struct {
    Rgbaq_b207_01E04850 c;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b207_01E04850;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b207_01E04850 v[4];
} Pkt_b207_01E04850;

typedef struct {
    u8 pad0[0x316C];
    u8 tab[1];
} Ctx_b207_01E04850;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 colB[4];
    u8 colA[4];
    u8 pad30[4];
    s16 u;
    u8 pad36[2];
    s16 v;
    s16 rz;
} Fx_b207_01E04850;

static void func_01E04850_b207(Ctx_b207_01E04850 *g, Fx_b207_01E04850 *o, Pkt_b207_01E04850 *p, s32 lit) {
    extern Rgbaq_b207_01E04850 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    s32 rot[4];
    s32 r[4];
    f32 depth[4];
    s32 ot;
    s16 i;
    f32 ax, ay, az;

    ot = (s32)func_00207500();
    if (lit == 0) {
        func_001092E0(p, 0);
        func_001094F0(p);
        p->v[0].c = func_00107740(o->colA);
        p->v[1].c = func_00107740(o->colA);
        p->v[2].c = func_00107740(o->colA);
        p->v[3].c = func_00107740(o->colB);
    } else {
    sc.x = 1.0f;
    sc.y = 1.0f;
    sc.z = 1.0f;
    func_00205C40((s32)rot);
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    func_00108EF0(m, &sc, rot, &pos);
    r[2] = o->rz;
    r[1] = 0;
    r[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, o->u, o->v, i);
        func_00109100(quad, r, 2, g->tab);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, ot, (u32)depth[0]);
        }
    }
    }
}
