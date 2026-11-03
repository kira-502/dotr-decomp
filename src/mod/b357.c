#include "common.h"

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00080_b357(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00100_b357(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E00550_b357(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00100_b357((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E008D0_b357(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* shape b045:01E04270, 316 insns: b018:01E01320's curved beam, textured, drawn as 2 crossed quads per step. Needs func_01E008D0_b357 in the same file and
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

static void func_01E00D10_b357(Obj_b045_01E04270 *o, Beam_b045_01E04270 *an, Vec_b018_01E00EE0 *pts) {
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
                ab[0] = func_01E008D0_b357(&pts[(s16)i - 1], 0, t);
                t += 0.25f;
                r1 = func_01E008D0_b357(&pts[(s16)i - 1], 0, t);
                ab[1] = r1;
            } else {
                ab[0] = func_01E008D0_b357(ctrl, 0, t);
                t += 0.25f;
                r2 = func_01E008D0_b357(ctrl, 0, t);
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

static void func_01E01200_b357(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
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

static void func_01E01490_b357(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b357", func_01E01790_b357);

/* shape b357:01E01CD0 (IWTThunder2), 299 insns, 1 copy: lightning ribbon through the object's points: per segment a
   quad from point i to i+1 widened by the object's 0x38 across the camera, the far edge with both alphas lowered by
   alpha / (n - 1); world matrix at the object's position, scale its 0x8/0xA/0xC tenths */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b357_01E01CD0;

typedef struct {
    Rgbaq_b357_01E01CD0 c;
    f32 s, t;
    u64 xyz;
} Vtx_b357_01E01CD0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b357_01E01CD0 v[4];
    u8 tail[0x20];
} Pkt_b357_01E01CD0;

typedef struct {
    u8 r, g, b, a;
} Col_b357_01E01CD0;

typedef struct {
    u8 pad0[0x88];
    void *texture;
    u8 pad8C[8];
    u8 rect[0x2A];
    s16 mode;
    u8 padC0[0x18];
    u8 fD8[4];
} Self_b357_01E01CD0;

typedef struct {
    s16 x, y, z;
    s16 n;
    s16 sx, sy, sz;
    u8 padE[0x1A];
    Col_b357_01E01CD0 c0;
    Col_b357_01E01CD0 c1;
    u8 pad30[8];
    s16 w;
} Obj_b357_01E01CD0;

static void func_01E01CD0_b357(Self_b357_01E01CD0 *self, Obj_b357_01E01CD0 *obj, Vec4f *pt) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b357_01E01CD0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00106B50(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s16 n;
    s32 j;
    f32 d[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    s32 rot[4];
    Vec4f p[4];
    Vec4f q[4];
    Pkt_b357_01E01CD0 pk __attribute__((aligned(8)));
    Col_b357_01E01CD0 c0;
    Col_b357_01E01CD0 c1;
    Pkt_b357_01E01CD0 *pp;
    s32 ot;
    s32 i;
    s32 last;

    ot = (s32)func_00207500();
    n = obj->n;
    pp = &pk;
    func_00109270(pp, 0, 0);
    pp->v[0].c = func_00107740(&obj->c0);
    pp->v[1].c = func_00107740(&obj->c1);
    pp->v[2].c = func_00107740(&obj->c0);
    pp->v[3].c = func_00107740(&obj->c1);
    func_00108500(pp, self->rect, self->mode);
    func_00208700(pp, self->texture, 1);
    c0 = obj->c0;
    c1 = obj->c1;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    sc.x = obj->sx;
    sc.y = obj->sy;
    sc.z = obj->sz;
    sc.x /= 10.0f;
    sc.y /= 10.0f;
    sc.z /= 10.0f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    func_00108EF0(m, &sc, 0, &pos);
    i = 0;
    last = n - 1;
    goto test;
loop:
    {
        pp->v[0].c = func_00107740(&c0);
        pp->v[1].c = func_00107740(&c1);
        c0.a -= obj->c0.a / last;
        c1.a -= obj->c1.a / last;
        pp->v[2].c = func_00107740(&c0);
        pp->v[3].c = func_00107740(&c1);
        for (j = 0; j < 1; j++) {
            func_00108CE0(q, obj->w, 0);
            func_00109100(q, rot, 0, self->fD8);
            p[0].x = pt[0].x;
            p[0].y = pt[0].y;
            p[0].z = pt[0].z;
            p[1].x = pt[0].x;
            p[1].y = pt[0].y;
            p[1].z = pt[0].z;
            p[2].x = pt[1].x;
            p[2].y = pt[1].y;
            p[2].z = pt[1].z;
            p[3].x = pt[1].x;
            p[3].y = pt[1].y;
            p[3].z = pt[1].z;
            func_00106B50(&p[0], &q[0]);
            func_00106B50(&p[1], &q[1]);
            func_00106B50(&p[2], &q[2]);
            func_00106B50(&p[3], &q[3]);
            if (func_00205630(p, 0x70000000, m, pp, d) != 0) {
                func_002075F0(pp, ot, (u32)d[0]);
            }
        }
        pt++;
        i++;
    }
test:
    if (i < last) goto loop;
}


INCLUDE_ASM("asm/nonmatchings/mod/b357", func_01E02180_b357);

/* shape b357:01E02590, 118 insns, 7 copies: one camera-facing sprite at the object position plus offset / 10,
   scaled by obj->size: the single-sprite member of the b018:01E00920 family. Calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b357_01E02590;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b357_01E02590 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b357_01E02590;

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
} Obj_b357_01E02590;

static void func_01E02590_b357(u8 *self, Obj_b357_01E02590 *obj, Pk_b357_01E02590 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b357_01E02590 uv;
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
    func_01E00100_b357((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), *(s16 *)(self + 0xBE));
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

/* shape b357:01E02770, 176 insns: twelve camera-facing sprites in a circle (radius 0x06, 30 apart from the start angle
   0x3A) around the object, each sized obj->size and turned to face the camera's yaw, sent count+1 times (self+0xB8).
   Calls the module's sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b357_01E02770;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b357_01E02770 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b357_01E02770;

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
} Obj_b357_01E02770;

static void func_01E02770_b357(u8 *self, Obj_b357_01E02770 *obj, Pk_b357_01E02770 *pk) {
    extern void func_00108EF0();
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    f32 m[16];
    Vec4f pos;
    f32 world[16];
    f32 depth[4];
    s32 rot[4];
    St_b357_01E02770 uv;
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
    func_01E00100_b357((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    func_00108EF0(world, 0, &obj->rx, &pos);
    for (k = 0; k < 12; k++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        t = obj->ang + a;
        pos.x = obj->rad * func_00108030(self + 0xD8, t, 1);
        pos.y = obj->rad * func_00108030(self + 0xD8, t, 0);
        func_00107070(m, 0, pos.x);
        func_00107070(m, 1, pos.y);
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            for (j = 0; j < *(s16 *)(self + 0xB8) + 1; j++) {
                func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
            }
        }
        a += 30;
    }
}

/* shape b357:01E02A30, 287 insns (B357_W_S): the module's spawn step: scene colour red, ticks the timer; tick 1
   spawns b357:01E05230; on six ticks (68..122) it stores joint 0x38AC as a new point (0x1EC0 + 16 x n) and spawns
   b357:01E04240/046D0/04910, 03F50, 032B0, three 03D30 and 04B50 there; from tick 11 every point more than 7 off the
   camera depth slides 5 toward it (by the camera's turn); before tick 180, while 0x3880 > 20, two b357:01E03420 on
   the next of ten slots; from tick 68 every point that far off becomes the spawn point, 2.5 deeper */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x1EC0 - 0x25C];
    Vec4f pt[1];
    u8 pad1ED0[0x3880 - 0x1ED0];
    s32 n3880;
    u8 rgba[4];
    u8 pad3888[0x38AC - 0x3888];
    s16 joint;
    u8 pad38AE[0x38BC - 0x38AE];
    s16 n;
    s16 ang;
    u8 pad38C0[6];
    s16 cur;
    s16 k;
    u8 pad38CA[4];
    s16 t;
} Scene_b357_01E02A30;

static s32 func_01E032B0_b357();
static s32 func_01E03420_b357();
static s32 func_01E03D30_b357();
static s32 func_01E03F50_b357();
static s32 func_01E04240_b357();
static s32 func_01E046D0_b357();
static s32 func_01E04910_b357();
static s32 func_01E04B50_b357();
static s32 func_01E05230_b357();
static s32 func_01E06200_b357();

static void func_01E02A30_b357(Scene_b357_01E02A30 *s) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern f32 func_001A6C60(f32);
    Vec4f v;
    s32 r[4];
    f32 d;
    s32 side;
    s32 i;

    s->rgba[0] = 0x80;
    s->rgba[1] = 0;
    s->rgba[2] = 0;
    s->rgba[3] = 0;
    s->t++;
    if (s->t == 1) {
        func_01E06200_b357(s, func_01E05230_b357, 0);
    }
    if (s->t == 68 || s->t == 77 || s->t == 87 || s->t == 99 || s->t == 111 || s->t == 122) {
        func_001F5620(func_001F53A0(), s->joint, &v);
        s->cur = s->n;
        s->n++;
        s->pt[s->cur] = v;
        for (i = 0; i < 1; i++) {
            s->ang = i * 30;
            func_01E06200_b357(s, func_01E04240_b357, 0);
            func_01E06200_b357(s, func_01E046D0_b357, 0);
            func_01E06200_b357(s, func_01E04910_b357, 0);
        }
        func_01E06200_b357(s, func_01E03F50_b357, 0);
        s->px = s->pt[s->cur].x;
        s->py = s->pt[s->cur].y;
        s->pz = s->pt[s->cur].z;
        func_01E06200_b357(s, func_01E032B0_b357, 0);
        func_01E06200_b357(s, func_01E03D30_b357, 0);
        func_01E06200_b357(s, func_01E03D30_b357, 0);
        func_01E06200_b357(s, func_01E03D30_b357, 0);
        for (i = 0; i < 1; i++) {
            func_01E06200_b357(s, func_01E04B50_b357, 0);
        }
    }
    func_001F6160(func_001F53A0(), r);
    side = r[1] / 180.0f;
    if (s->t >= 11) {
        func_001F5F90(func_001F5380(), &v);
        for (i = 0; i < s->n; i++) {
            d = v.z - s->pt[i].z;
            if (func_001A6C60(d * d) > 7.0f) {
                if (side != 0) {
                    s->pt[i].z -= 5.0f;
                } else {
                    s->pt[i].z += 5.0f;
                }
            }
        }
    }
    if (s->t < 180) {
        if (s->n3880 > 20) {
            for (i = 0; i < 2; i++) {
                s->cur = s->k;
                func_01E06200_b357(s, func_01E03420_b357, 0);
                s->k++;
                if (s->k >= 10) {
                    s->k = 0;
                }
            }
        }
    }
    for (i = 0; i < s->n; i++) {
        s->cur = i;
    }
    if (s->t >= 68) {
        func_001F5F90(func_001F5380(), &v);
        for (i = 0; i < s->n; i++) {
            d = v.z - s->pt[i].z;
            if (func_001A6C60(d * d) > 7.0f) {
                s->px = s->pt[i].x;
                s->py = s->pt[i].y;
                s->pz = s->pt[i].z;
                s->pz += 2.5f;
            }
        }
    }
}

/* shape b357:01E02EB0, 127 insns: b501:01E02FE0 family grey spark (size 30..79, frame 0 stepping every other tick to 6, random turn rerolled 0..359 each tick, angle 0..359, f30 growing 1..3, f8 0..9): alpha up by 64 for 1..2 ticks, then down by 15 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
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
} Fx_b357_01E02EB0;

static s32 func_01E02EB0_b357(s32 arg0, Fx_b357_01E02EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 50 + 30;
        o->f34 = 0;
        func_00205C40(o->rot);
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 6) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    return 0;
}

/* shape b357:01E030B0, 126 insns: b383:01E03130 with a fade-in of 4..13 ticks */

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
} Glow_b357_01E030B0;

static s32 func_01E030B0_b357(s32 arg0, Glow_b357_01E030B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 80 + 30;
        o->kind = 0;
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        o->h30 = func_0019A5C8() % 250 + 100;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 10;
        o->h6 = func_0019A5C8() % 10 + 4;
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

/* shape b357:01E032B0, 89 insns: a dark green blinking flash (frame 1, turn 0x4000, size growing a random 4..6 a tick): in by 0x80 on its first tick; past size 20 out by 19, and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[6];
    s32 w10;
    u8 pad14[0x14];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b357_01E032B0;

static s32 func_01E032B0_b357(s32 arg0, Glow_b357_01E032B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->w10 = 0x4000;
        o->kind = 1;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        o->h6 = 8;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0x10, 0x10, 0xF0);
    }
    if (o->tick < 1) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->f38 > 20) {
        if (o->col[3] > 0x14) {
            o->col[3] -= 0x13;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x10, 0xF0, 0x10);
    } else {
        func_001076F0(o->col, 8, 0xF0, 8);
    }
    if (o->tick != 0) {
        o->f38 += o->h8;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b357", func_01E03420_b357);

/* shape b357:01E03850, 175 insns: a flickering (grey 0x40 / 0xC0 every other tick) column: frame 0..2, random turn, size 1, hold 1..6, h6 6, f38 10..29; on start lays its kind's 8 trail points (ctx+0x30E0 + kind*0x80) as a stack, each 15..39 above the one before; alpha up by 0x60 to 0xC0 for the hold, then down by 39 */

typedef struct {
    u8 pad0[0x30E0];
    Vec4f pts[1][8];
} Ctx_b357_01E03850;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hold;
    u8 pad10[8];
    s32 rot;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b357_01E03850;

static s32 func_01E03850_b357(Ctx_b357_01E03850 *g, Fx_b357_01E03850 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->f34 = func_0019A5C8() % 3;
        o->mode = 2;
        o->rot = func_0019A5C8() % 65535;
        o->h8 = 1;
        o->hA = 1;
        o->hC = 1;
        o->hold = func_0019A5C8() % 6 + 1;
        o->h6 = 6;
        o->f38 = func_0019A5C8() % 20 + 10;
        func_0019A5C8();
        func_0019A5C8();
        for (i = 0; i < 8; i++) {
            if (i) {
                g->pts[o->kind][i].y = 15.0f + (g->pts[o->kind][i - 1].y + func_0019A5C8() % 25);
                g->pts[o->kind][i].z = 0.0f;
                g->pts[o->kind][i].x = 0.0f;
            } else {
                g->pts[o->kind][i].y = 0.0f;
                g->pts[o->kind][i].z = 0.0f;
                g->pts[o->kind][i].x = 0.0f;
            }
        }
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 40) {
        o->col[3] -= 39;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    o->tick++;
    return 0;
}

/* shape b357:01E03B10, 134 insns: a rising spark flickering yellow / red / blue: size 10..17, random spin, height
   50..199, turn 0..359, rise 20..29, f8 0..9, held 3..9; alpha grows by 0x30 (to 0x60) while held, then fades by 10
   (ends below 0x11); rises after the first tick */

typedef struct {
    u8 pad0[6];
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
    s16 f34;
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b357_01E03B10;

static s32 func_01E03B10_b357(s32 arg0, Fx_b357_01E03B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 k;

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 8 + 10;
        o->f34 = 0;
        o->spin = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->h = func_0019A5C8() % 150 + 50;
        o->ang = func_0019A5C8() % 360;
        o->rise = func_0019A5C8() % 10 + 20;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 3;
        o->mode = 2;
    }
    if (o->t < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    k = o->t % 3;
    if (k == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0x40);
    } else if (k == 2) {
        func_001076F0(o->col, 0xC0, 0x40, 0x40);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0xC0);
    }
    if (o->t != 0) {
        o->h += o->rise;
    }
    o->t++;
    return 0;
}

/* shape b357:01E03D30, 134 insns: b207:01E02BC0's rising spark, tilt 0x3000..0x4FFF, frame 1, held 2..11, fades above height 22, ends above 42, flickers blue */

typedef struct {
    u8 pad0000[0x3880];
    s32 w3B00;
} Mgr_b357_01E03D30;

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
} Obj_b357_01E03D30;

static s32 func_01E03D30_b357(Mgr_b357_01E03D30 *m, Obj_b357_01E03D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 0;
        o->w10 = func_0019A5C8() % 0x2000 + 0x3000;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = 1;
        o->h36 = 2;
        o->hE = func_0019A5C8() % 3 + 4;
        o->h6 = func_0019A5C8() % 10 + 2;
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
        if (o->h38 > 22) {
            if (o->c28[3] > 20) {
                o->c28[3] -= 19;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h38 > 42) {
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
        func_001076F0(o->c28, 0x10, 0x10, 0x80);
    } else {
        func_001076F0(o->c28, 0x40, 0x40, 0x80);
    }
    o->h32++;
    o->h38 += o->hE;
    return 0;
}

/* shape b357:01E03F50, 99 insns: a yellow trail: frame 30, width 6; fills its trail row with its point, then holds alpha 0x30
   until frame 40 and fades by 9 until it ends; rebuilds the trail tail from the point each frame; flickers yellow/orange */

typedef struct {
    f32 x, y, z, w;
} V4_b357_01E03F50;

typedef struct {
    u8 pad0[0x1EC0];
    V4_b357_01E03F50 pts[10];
    V4_b357_01E03F50 trail[1][10];
} Game_b357_01E03F50;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x20];
    u8 c0[4];
    u8 pad2C[4];
    s16 row;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b357_01E03F50;

static s32 func_01E03F50_b357(Game_b357_01E03F50 *g, Obj_b357_01E03F50 *o) {
    extern void b357_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    V4_b357_01E03F50 *p;
    V4_b357_01E03F50 *q;

    if (o->state == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 8);
        o->h6 = 6;
        o->c0[3] = 0x80;
        o->h38 = 0x1E;
        o->state = 2;
        p = &g->pts[o->row];
        q = g->trail[o->row];
        for (i = 0; i < 10; i++) {
            q->x = p->x;
            q->y = p->y;
            q->z = p->z;
            q++;
        }
    }
    if (o->t < 0x28) {
        o->c0[3] = 0x30;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    b357_01E00080(&g->trail[o->row][9], 0xA, 0, &g->pts[o->row]);
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x80, 0x80, 8);
    } else {
        func_001076F0(o->c0, 0xC0, 0x80, 8);
    }
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

static s32 func_01E040E0_b357(s32 arg0, Glow_b207_01E03430 *o) {
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

static s32 func_01E04190_b357(s32 arg0, Glow_b207_01E034E0 *o) {
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

/* shape b357:01E04240, 292 insns (B357_OBJ_MOVE_13_): sits on its point (0x1EC0 + 16 x 0x30) at full alpha; once the
   camera is within 7 in depth of it, it ends and bursts there: b357:01E04FE0, six jittered (-15..14) b357:01E030B0,
   five 01E03B10, six 01E04D20, one 01E04E80, twelve 01E03850 on the next of fifteen slots, and 01E050C0; it counts
   a frame 0..7, ends after 211 ticks and turns 10 a tick */

typedef struct {
    u8 pad0[0x250];
    f32 px, py, pz;
    u8 pad25C[0x1EC0 - 0x25C];
    Vec4f pt[1];
    u8 pad1ED0[0x38C6 - 0x1ED0];
    s16 cur;
    u8 pad38C8[2];
    s16 k;
} Scene_b357_01E04240;

typedef struct {
    s16 x, y, z;
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 idx;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Obj_b357_01E04240;

static s32 func_01E030B0_b357();
static s32 func_01E03850_b357();
static s32 func_01E03B10_b357();
static s32 func_01E04D20_b357();
static s32 func_01E04E80_b357();
static s32 func_01E04FE0_b357();
static s32 func_01E050C0_b357();
static s32 func_01E06200_b357();

static s32 func_01E04240_b357(Scene_b357_01E04240 *s, Obj_b357_01E04240 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001A6C60(f32);
    Vec4f v;
    f32 d;
    s16 i;

    if (o->mode == 1) {
        o->size = 80;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->life = 5;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t <= 0) {
        o->col[3] = 0x80;
    } else if (o->t % 2 == 1) {
        o->col[3] = 0x80;
    } else {
        o->col[3] = 0x80;
    }
    o->x = s->pt[o->idx].x;
    o->y = s->pt[o->idx].y;
    o->z = s->pt[o->idx].z;
    func_001F5F90(func_001F5380(), &v);
    d = v.z - s->pt[o->idx].z;
    if (func_001A6C60(d * d) < 7.0f) {
        o->mode = 0;
        s->px = s->pt[o->idx].x;
        s->py = s->pt[o->idx].y;
        s->pz = s->pt[o->idx].z;
        func_01E06200_b357(s, func_01E04FE0_b357, 0);
        for (i = 0; i < 6; i++) {
            s->px = s->pt[0].x + (func_0019A5C8() % 30 - 15);
            s->py = s->pt[0].y + (func_0019A5C8() % 30 - 15);
            s->pz = s->pt[0].z + (func_0019A5C8() % 30 - 15);
            func_01E06200_b357(s, func_01E030B0_b357, 0);
        }
        for (i = 0; i < 5; i++) {
            s->px = s->pt[0].x;
            s->py = s->pt[0].y;
            s->pz = s->pt[0].z;
            func_01E06200_b357(s, func_01E03B10_b357, 0);
        }
        for (i = 0; i < 6; i++) {
            s->px = s->pt[0].x;
            s->py = s->pt[0].y;
            s->pz = s->pt[0].z;
            func_01E06200_b357(s, func_01E04D20_b357, 0);
        }
        for (i = 0; i < 1; i++) {
            s->px = s->pt[0].x;
            s->py = s->pt[0].y;
            s->pz = s->pt[0].z;
            func_01E06200_b357(s, func_01E04E80_b357, 0);
        }
        for (i = 0; i < 12; i++) {
            s->cur = s->k;
            s->px = s->pt[0].x;
            s->py = s->pt[0].y;
            s->pz = s->pt[0].z;
            func_01E06200_b357(s, func_01E03850_b357, 0);
            s->k++;
            if (s->k >= 15) {
                s->k = 0;
            }
        }
        func_01E06200_b357(s, func_01E050C0_b357, 0);
    }
    if (o->frame < 7) {
        o->frame++;
    } else {
        o->frame = 0;
    }
    o->t++;
    if (o->t > 210) {
        o->mode = 0;
    }
    o->ang += 10;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b357:01E046D0, 143 insns: a marker on a scene point (16-byte points at +0x1EC0): size 80, frame 0..7 cycling,
   alpha 0x80, flickering yellow / blue; it ends once the camera is within 7 of it in depth or after 211 ticks;
   its turn goes 10 a tick */

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 k;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b357_01E046D0;

typedef struct {
    u8 pad0[0x1EC0];
    Vec4f pt[1];
} Scene_b357_01E046D0;

static s32 func_01E046D0_b357(Scene_b357_01E046D0 *g, Fx_b357_01E046D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001A6C60(f32);
    Vec4f cam;
    f32 d;

    if (o->mode == 1) {
        o->size = 80;
        o->frame = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h6 = 5;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 1) {
        o->col[3] = 0x80;
    } else if (o->t % 2 == 1) {
        o->col[3] = 0x80;
    } else {
        o->col[3] = 0x80;
    }
    o->x = func_001A22C0(g->pt[o->k].x);
    o->y = func_001A22C0(g->pt[o->k].y);
    o->z = func_001A22C0(g->pt[o->k].z);
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0xC0);
    }
    func_001F5F90(func_001F5380(), &cam);
    d = cam.z - g->pt[o->k].z;
    if (func_001A6C60(d * d) < 7.0f) {
        o->mode = 0;
    }
    if (o->frame < 7) {
        o->frame++;
    } else {
        o->frame = 0;
    }
    o->t++;
    if (o->t > 0xD2) {
        o->mode = 0;
    }
    o->ang += 10;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b357:01E04910, 143 insns: b357:01E046D0's scene-point marker, size 120, alpha 0x20 flickering with 0x10 */

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    s16 k;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b357_01E04910;

typedef struct {
    u8 pad0[0x1EC0];
    Vec4f pt[1];
} Scene_b357_01E04910;

static s32 func_01E04910_b357(Scene_b357_01E04910 *g, Fx_b357_01E04910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_001A6C60(f32);
    Vec4f cam;
    f32 d;

    if (o->mode == 1) {
        o->size = 120;
        o->frame = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h6 = 5;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 1) {
        o->col[3] = 0x20;
    } else if (o->t % 2 == 1) {
        o->col[3] = 0x20;
    } else {
        o->col[3] = 0x10;
    }
    o->x = func_001A22C0(g->pt[o->k].x);
    o->y = func_001A22C0(g->pt[o->k].y);
    o->z = func_001A22C0(g->pt[o->k].z);
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0xC0);
    }
    func_001F5F90(func_001F5380(), &cam);
    d = cam.z - g->pt[o->k].z;
    if (func_001A6C60(d * d) < 7.0f) {
        o->mode = 0;
    }
    if (o->frame < 7) {
        o->frame++;
    } else {
        o->frame = 0;
    }
    o->t++;
    if (o->t > 0xD2) {
        o->mode = 0;
    }
    o->ang += 10;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b357:01E04B50, 114 insns: reads the camera (func_001F6160) and keeps whether its turn / 180 is non-zero; on
   start 0x38 = 5, variant 0, random 0x3A, 0x8 = 2, 0x6 = 0, colour (8, 8, 0x40); alpha 0x80 on the first tick, then
   fades by 18 and stops; the variant cycles 0..7; colour green on tick 1, blue on tick 2; after the first tick 0x6
   grows by 0x8 and 0x4 moves 2 (up when the camera has turned, else down) */

typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    s16 f8;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b357_01E04B50;

static s32 func_01E04B50_b357(s32 arg0, Fx_b357_01E04B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_001A22C0(f32);
    s32 cam[4];
    s32 turn;

    func_001F6160(func_001F53A0(), cam);
    turn = (s16)func_001A22C0(cam[1] / 180.0f);
    if (o->mode == 1) {
        o->f38 = 5;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->f8 = 2;
        o->f6 = 0;
        func_001076F0(o->col, 8, 8, 0x40);
    }
    if (o->tick <= 0) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 0x13) {
        o->col[3] -= 18;
    } else {
        o->mode = 0;
    }
    if (o->f34 < 7) {
        o->f34++;
    } else {
        o->f34 = 0;
    }
    if (o->tick == 1) {
        func_001076F0(o->col, 0x10, 0x50, 0x10);
    } else if (o->tick == 2) {
        func_001076F0(o->col, 0x18, 0x38, 0x80);
    }
    if (o->tick != 0) {
        o->f6 += o->f8;
    }
    if (o->tick != 0) {
        if (turn != 0) {
            o->f4 += 2;
        } else {
            o->f4 -= 2;
        }
    }
    o->tick++;
    return 0;
}

/* shape b357:01E04D20, 88 insns: a light grey tumbling flash (size 6 growing a random 3..4 a tick) at three random turns: alpha at least 0x80 on its first tick, then out by 15 and ends */

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
} Glow_b357_01E04D20;

static s32 func_01E04D20_b357(s32 arg0, Glow_b357_01E04D20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 6;
        o->w10 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->kind = 0;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 2 + 3;
        o->h6 = 50;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    }
    if (o->tick < 1) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001076F0(o->col, 0xB0, 0xB0, 0xB0);
    o->tick++;
    o->f38 += o->h8;
    return 0;
}

/* shape b357:01E04E80, 86 insns: on start 0x38 = 15, random 0x3A, step 3, colour (0xF0, 0xF0, 0x10); alpha 0x80 for
   4 ticks, then fades by 0x11 and stops; 0x34 cycles 0..7; tick 1 turns it (0x50, 0x50, 0x10), tick 2 (0x38, 0x38,
   0x80); 0x6 grows by the step after the first tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 step;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b357_01E04E80;

static s32 func_01E04E80_b357(s32 arg0, Fx_b357_01E04E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 15;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->step = 3;
        o->f6 = 0;
        func_001076F0(o->col, 0xF0, 0xF0, 0x10);
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] = 0x80;
        }
    } else if (o->col[3] > 0x12) {
        o->col[3] -= 0x11;
    } else {
        o->mode = 0;
    }
    if (o->f34 < 7) {
        o->f34++;
    } else {
        o->f34 = 0;
    }
    if (o->tick == 1) {
        func_001076F0(o->col, 0x50, 0x50, 0x10);
    } else if (o->tick == 2) {
        func_001076F0(o->col, 0x38, 0x38, 0x80);
    }
    if (o->tick != 0) {
        o->f6 += o->step;
    }
    o->tick++;
    return 0;
}

/* shape b357:01E04FE0, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0xC0
   for the first 10 ticks, then fades out by 15 and stops */

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
} Flash_b357_01E04FE0;

static s32 func_01E04FE0_b357(s32 arg0, Flash_b357_01E04FE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x2BC;
        func_001076F0(o->col, 0x10, 0x10, 0x80);
        func_001076F0(o->col2, 0, 0, 0xF0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xA) {
        o->col[3] += 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b357:01E050C0, 91 insns: a scene light pulse (b443:01E03E80 shape): sets the scene light (range 140, at the object's point),
   raises its strength by 0.5f to 1, then lowers it by 0.3f until it ends; applies the light while live and ends when the
   scene state at 0x3880 is 1 */

typedef struct {
    u8 pad0[0x1E90];
    f32 l0[4];
    f32 pos[3];
    u8 pad1EAC[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad1EBC[0x19C4];
    s32 state;
} Scene_b357_01E050C0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 down;
    u8 pad32[4];
    s16 live;
} Obj_b357_01E050C0;

static s32 func_01E050C0_b357(Scene_b357_01E050C0 *g, Obj_b357_01E050C0 *o) {
    extern void func_001F6C10(void *);

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 3.0f;
        g->l0[2] = 3.0f;
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
            g->power += 0.5f;
        } else {
            o->down = 1;
        }
    } else if (!(g->power <= 0.3f)) {
        g->power -= 0.3f;
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

/* shape b357:01E05230, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3880 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3880];
    s32 state;
} Game_b357_01E05230;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b357_01E05230;

static s32 func_01E05230_b357(Game_b357_01E05230 *g, Fade_b357_01E05230 *o) {
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

static s32 func_01E052F0_b357(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E06A00_b357;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E06A08_b357;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b357", func_01E05340_b357);

/* shape b357:01E06200, 74 insns: twin of b046:01E03E20: take the first free slot of the 110-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x38C6 and 0x38BE and the two arguments; returns 1 if a
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
} Slot_b357_01E06200;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b357_01E06200 s[110];
    u8 pad1E70[0x1A14];
    u8 r, g, b, a;
    u8 pad3888[0x36];
    s16 w;
    u8 pad38C0[0x6];
    s16 v;
} Pool_b357_01E06200;

static s32 func_01E06200_b357(Pool_b357_01E06200 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b357_01E06200 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 110; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 110;
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

INCLUDE_ASM("asm/nonmatchings/mod/b357", func_01E06330_b357);
