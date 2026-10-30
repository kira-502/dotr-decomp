#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b256(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
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

/* shape b003:01E00080, 552 insns, 183 copies: the module's first function. Texture coordinates of a
   sprite quad from a rectangle, in one of 8 corner orders (flips and quarter turns). Callers in the same
   file rely on it leaving $a0 alone, so it must stay in their file. */

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


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00110_b256(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 2) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 3) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 4) {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    } else if (mode == 5) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else if (mode == 6) {
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y + r->h) << 4;
    } else if (mode == 7) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b016_01E01190;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b016_01E01190;

typedef struct {
    u8 pad00[0x20];
    Vec_b016_01E01190 rotation;
    u8 pad30[4];
    f32 height;
    u8 pad38[0x10];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b016_01E01190;

static void func_01E009B0_b256(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b016_01E01190 c;
    Vec_b016_01E01190 quad[4];
    Vec_b016_01E01190 pos;
    Vec_b016_01E01190 scale;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s32 i;
    s16 width;
    s32 a;
    s16 j;
    f32 inner;
    u8 *pkt;
    s32 mode;
    f32 outer;

    pkt = packet;
    c = *color;
    width = data->width;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    pos.x = c.x;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = data->height;
    quad[3].y = data->height;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = data->step + j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = j + (data->step + width);
        quad[1].x = inner * func_00108030(obj->table, a, 1);
        quad[1].z = inner * func_00108030(obj->table, a, 0);
        quad[3].x = outer * func_00108030(obj->table, a, 1);
        quad[3].z = outer * func_00108030(obj->table, a, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_002075F0(pkt, obj->texture, func_001A23B0(depth[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, obj->texture, 0);
            }
        }
        j += data->step;
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b256 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E00D10_b256(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_b256((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    func_00108CE0(view, cam->w, cam->h);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        mode = flags & 0xF;
        if (mode == 0) {
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b038_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b038_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b038_01E00920;

typedef struct {
    u64 st;
    Xyz_b038_01E00920 p;
} Vtx_b038_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b038_01E00920 c;
    Vtx_b038_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b038_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b038_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b038_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    s16 tilt;
    u8 pad5E[2];
    u8 col[1];
} Anim_b038_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b038_01E00920;

extern void b256_01E00110(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00FD0_b256(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b038_01E00920 quad[4];
    Vec_b038_01E00920 d;
    Vec_b038_01E00920 pos;
    Vec_b038_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b038_01E00920 r;
    struct {
        u64 pre;
        Pkt_b038_01E00920 pk;
    } buf;
    Col_b038_01E00920 col;
    s16 i;
    Pkt_b038_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.rot[2] = an->tilt;
    r.v[1] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b256_01E00110(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 2, o->bD8);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 0, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E01540_b256(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b020:01E00E70, 218 insns, 35 copies: draws 4 copies of a gradient quad (colour A/B per corner, by mode = flags >> 4)
   around a position, each turned by the effect's rotation; far z. The position is passed by value. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b020_01E00E70;

typedef struct {
    Rgbaq_b020_01E00E70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b020_01E00E70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b020_01E00E70 v[4];
    u8 tail[0x20];
} Pkt_b020_01E00E70;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b020_01E00E70;

typedef struct {
    u8 pad00[0x30];
    f32 u, v;
    u8 pad38[0x22];
    s16 rz;
    u8 pad5C[4];
    u8 colB[4];
    u8 colA[4];
} Fx_b020_01E00E70;

static void func_01E01980_b256(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b020_01E00E70 func_00107740(void *);
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
    Pkt_b020_01E00E70 pkt;
    s32 mode;
    s32 a;
    s16 i;
    Pkt_b020_01E00E70 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    mode = flags >> 4;
    if (mode == 0) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colA);
        p->v[3].c = func_00107740(fx->colB);
    } else if (mode == 1) {
        p->v[0].c = func_00107740(fx->colA);
        p->v[1].c = func_00107740(fx->colA);
        p->v[2].c = func_00107740(fx->colB);
        p->v[3].c = func_00107740(fx->colB);
    }
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
        a = (s32)fx->u;
        func_00108D60(quad, a, (s32)fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, (u32)pos.w);
        }
    }
}

/* shape b256:01E01CF0 (B256_W_S), 379 insns, 1 copy: B256_W_S, the effect scene step: counts the frame (0xCBB8);
   frames 151..351 take joint 0 into base, raise it 3.3 and copy it to pos; 123..134 / 145..155 spawn 0x1E022E0 and
   four 0x1E02A40 at joints 3 / 5; frames 123/143 spawn 0x1E02FC0 on side 0/1, 124/146 0x1E03B50; 128/149 0x1E02D00
   and two 0x1E028B0 (angles 45/135); 97/118/128 and 107/129 put pos 1.5 under joint 0 / 1 and spawn thirteen
   0x1E02DF0; frame 23 spawns 0x1E03A60 and 0x1E03DC0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCAD0 - 0x260];
    Vec4f base;
    u8 padCAE0[0xCB44 - 0xCAE0];
    s16 joint[6];
    u8 padCB50[0xCBA2 - 0xCB50];
    s16 ang;
    u8 padCBA4[0xCBB0 - 0xCBA4];
    s16 flag;
    u8 padCBB2[0xCBB8 - 0xCBB2];
    s16 t;
} Scene_b256_01E01CF0;

static void func_01E01CF0_b256(Scene_b256_01E01CF0 *g) {
    extern void b256_01E022E0(void);
    extern void b256_01E028B0(void);
    extern void b256_01E02A40(void);
    extern void b256_01E02D00(void);
    extern void b256_01E02DF0(void);
    extern void b256_01E02FC0(void);
    extern void b256_01E03A60(void);
    extern void b256_01E03B50(void);
    extern void b256_01E03DC0(void);
    extern void b256_01E04900(Scene_b256_01E01CF0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    if (g->t > 150 && g->t < 352) {
        func_001F5620(func_001F53A0(), g->joint[0], &g->base);
        g->base.y += 3.3f;
        g->pos = g->base;
    }
    if (g->t >= 123 && g->t < 135) {
        func_001F5620(func_001F53A0(), g->joint[3], &g->pos);
        b256_01E04900(g, b256_01E022E0, 0);
        b256_01E04900(g, b256_01E02A40, 0);
        b256_01E04900(g, b256_01E02A40, 0);
        b256_01E04900(g, b256_01E02A40, 0);
        b256_01E04900(g, b256_01E02A40, 0);
    }
    if (g->t >= 145 && g->t < 156) {
        func_001F5620(func_001F53A0(), g->joint[5], &g->pos);
        b256_01E04900(g, b256_01E022E0, 0);
        b256_01E04900(g, b256_01E02A40, 0);
        b256_01E04900(g, b256_01E02A40, 0);
        b256_01E04900(g, b256_01E02A40, 0);
        b256_01E04900(g, b256_01E02A40, 0);
    }
    if (g->t == 123) {
        g->flag = 0;
        b256_01E04900(g, b256_01E02FC0, 0);
    }
    if (g->t == 143) {
        g->flag = 1;
        b256_01E04900(g, b256_01E02FC0, 0);
    }
    if (g->t == 124) {
        b256_01E04900(g, b256_01E03B50, 0);
    }
    if (g->t == 146) {
        b256_01E04900(g, b256_01E03B50, 0);
    }
    if (g->t == 128) {
        func_001F5620(func_001F53A0(), g->joint[3], &g->pos);
        b256_01E04900(g, b256_01E02D00, 0);
        g->ang = 45;
        g->flag = 0;
        b256_01E04900(g, b256_01E028B0, 0);
        g->ang = 135;
        g->flag = 1;
        b256_01E04900(g, b256_01E028B0, 0);
    }
    if (g->t == 149) {
        func_001F5620(func_001F53A0(), g->joint[5], &g->pos);
        b256_01E04900(g, b256_01E02D00, 0);
        g->ang = 135;
        g->flag = 0;
        b256_01E04900(g, b256_01E028B0, 0);
        g->ang = 45;
        g->flag = 1;
        b256_01E04900(g, b256_01E028B0, 0);
    }
    if (g->t == 97 || g->t == 118 || g->t == 128) {
        func_001F5620(func_001F53A0(), g->joint[0], &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b256_01E04900(g, b256_01E02DF0, 0);
        }
    }
    if (g->t == 107 || g->t == 129) {
        func_001F5620(func_001F53A0(), g->joint[1], &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b256_01E04900(g, b256_01E02DF0, 0);
        }
    }
    if (g->t == 23) {
        b256_01E04900(g, b256_01E03A60, 0);
    }
    if (g->t == 23) {
        b256_01E04900(g, b256_01E03DC0, 0);
    }
}

/* shape b256:01E022E0, 149 insns: constant variant of b418:01E020E0 (40->10, 70->10, 45->5) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
    s32 pos[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b256_01E022E0;

static s32 func_01E022E0_b256(s32 arg0, Fx_b256_01E022E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 30.0f;
        o->f56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->fA = 2;
        } else {
            o->fA = 0;
        }
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f52 = func_0019A5C8() % 350 + 100;
        o->spin = (func_0019A5C8() >> 4) % 10 + 5;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    o->tick++;
    return 0;
}

/* shape b256:01E02540, 218 insns: b256:01E02A40 family: a drifting spark (drift /100, random spin and spin speed), fades in for 6 ticks, out by 11; grows every third tick; the scene counter past 445 ends it */

typedef struct {
    u8 pad0[0xCBB4];
    s16 flag;
    u8 padCBB6[2];
    s16 count;
} Ctx_b256_01E02540;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b256_01E02540;

static s32 func_01E02540_b256(Ctx_b256_01E02540 *ctx, Obj_b256_01E02540 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = func_0019A5C8() % 3 + 3;
        o->hA = o->h8 + 4;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f38 = func_0019A5C8() % 100 - 50;
        o->f34 /= 100.0f;
        o->f30 /= 100.0f;
        o->f38 /= 100.0f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->h8 < 11) {
            o->h8++;
        }
        if (o->hA < o->h8 + 4) {
            o->hA++;
        }
    }
    if (o->t != 0) {
        o->x += o->f30;
        o->y += o->f34;
        o->z += o->f38;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    if (ctx->count > 445) {
        o->t = 90;
    }
    return 0;
}

/* shape b256:01E028B0, 97 insns: on start f48 6, colours 0xF0, 0xE0, 0xFF / 0xF0, 0xE0, 0xFF (second alpha 0), f30 18 and length f34 by kind
   (0x50: 1000.0 / 250.0 / 400.0); alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and stops; after the
   first tick kinds 0/1 grow by 40.0 / 20.0 */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 len;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b256_01E028B0;

static s32 func_01E028B0_b256(s32 arg0, Fx_b256_01E028B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xF0, 0xE0, 0xFF);
        func_001076F0(o->col2, 0xF0, 0xE0, 0xFF);
        if (o->kind == 0) {
            o->f30 = 18.0f;
            o->len = 1000.0f;
        }
        if (o->kind == 1) {
            o->f30 = 18.0f;
            o->len = 250.0f;
        }
        if (o->kind == 2) {
            o->f30 = 18.0f;
            o->len = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (o->tick != 0) {
            o->len += 40.0f;
        }
    }
    if (o->kind == 1) {
        if (o->tick != 0) {
            o->len += 20.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b256:01E02A40, 176 insns: a purple spark with a random drift (-50..49)/60, random spin and spin speed (-1024..1023 per axis), fades in to 0x80 for 10 ticks, out by 9; z spin eased 1.5 by the scene flag */

typedef struct {
    u8 pad0[0xCBB4];
    s16 flag;
} Ctx_b256_01E02A40;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b256_01E02A40;

static s32 func_01E02A40_b256(Ctx_b256_01E02A40 *ctx, Obj_b256_01E02A40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = 150;
        o->hA = o->h8 >> 1;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f38 = func_0019A5C8() % 100 - 50;
        o->f34 /= 60.0f;
        o->f30 /= 60.0f;
        o->f38 /= 60.0f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    if (ctx->flag != 0) {
        o->rot[2] -= 1.5f;
    } else {
        o->rot[2] += 1.5f;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b256:01E02D00, 59 insns: a spinning flash: set up once (scale 140.0, both colours 0xF0, 0xE0, 0xFF, size 10x10),
   fades in by 0x60 up to 0xC0 for 10 frames, then out by 9 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x1C];
    f32 scale;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b256_01E02D00;

static s32 func_01E02D00_b256(void *arg0, Obj_b256_01E02D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->scale = 140.0f;
        func_001076F0(o->c1, 0xF0, 0xE0, 0xFF);
        func_001076F0(o->c0, 0xF0, 0xE0, 0xFF);
        o->h52 = 0;
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xA) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x60;
        }
    } else if (o->c1[3] > 0xA) {
        o->c1[3] -= 9;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0xCDBC];
    u8 tab[1];
} Mgr_b256_01E02DF0;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    u8 pad14[4];
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b256_01E02DF0;

static s32 func_01E02DF0_b256(Mgr_b256_01E02DF0 *m, Obj_b256_01E02DF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 130;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h58 = 2;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->f18 += 8.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 8.6f * func_00108030(m->tab, o->h5A, 1);
    }
    if (o->h54 < 10) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x40;
        }
    } else if (o->c60[3] > 10) {
        o->c60[3] -= 9;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f18 += 0.8f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 0.8f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b256", func_01E02FC0_b256);

/* shape b256:01E03A60, 60 insns: volume fade (layout at 0x50): for 0x1E frames down 10 to 0x30, then while the game
   state at 0xCB10 is below 0x14 up 10 to 0x80; state 3 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0xCB10];
    s32 state;
} Game_b256_01E03A60;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b256_01E03A60;

static s32 func_01E03A60_b256(Game_b256_01E03A60 *g, Fade_b256_01E03A60 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x14) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b256:01E03B50, 154 insns: b144:01E034D0 with a lilac tint (0x80/0x70/0x90) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b256_01E03B50;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b256_01E03B50 p;
    } v[2];
    u8 tail[0x20];
} Pkt_b256_01E03B50;

typedef struct {
    u8 pad0[0x48];
    f32 zoom;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Flash_b256_01E03B50;

static s32 func_01E03B50_b256(void *arg0, Flash_b256_01E03B50 *o) {
    extern void func_002087A0(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b256_01E03B50 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->zoom = 1.0f;
        o->state = 2;
    }
    ((Pkt_b256_01E03B50 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b256_01E03B50 *)(s32)&pkt)->tag = 5;
    ((Pkt_b256_01E03B50 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b256_01E03B50 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x70;
    pkt.b = 0x90;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    pkt.v[0].p.x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = o->zoom / 1024.0f;
    pkt.v[0].t = o->zoom / 512.0f;
    pkt.v[1].s = (640.0f - o->zoom) / 1024.0f;
    pkt.v[1].t = (448.0f - o->zoom) / 512.0f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0(&pkt, (s32)func_00207500(), 0);
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 0x13;
        }
        if (o->zoom < 100.0f) {
            o->zoom += 0.3f;
        }
    } else {
        if (o->c0[3] > 7) {
            o->c0[3] -= 6;
        } else {
            o->state = 0;
        }
        if (o->zoom > 0.0f) {
            o->zoom -= 0.3f;
        } else {
            o->zoom = 0.0f;
        }
    }
    o->t++;
    return 0;
}

/* shape b256:01E03DC0, 180 insns: b491:01E03360 family full-screen tint in pale violet (0xF0, 0xE0, 0xFF) from alpha 0 through the scene packet (ctx+0xCB28), uv shrunk by a tenth of 0x8/0xA on each side, drawn once; alpha up by 9 to 0x80 before scene count 183 (ctx+0xCBB8), then down by 7 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b256_01E03DC0;

typedef struct {
    f32 s, t;
    Xyz_b256_01E03DC0 p;
} Tv_b256_01E03DC0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b256_01E03DC0 v[2];
} Tex_b256_01E03DC0;

typedef struct {
    u8 pad[0xCB28];
    Tex_b256_01E03DC0 *pk;
    u8 padCB2C[0xCBB8 - 0xCB2C];
    s16 count;
} Game_b256_01E03DC0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x48];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b256_01E03DC0;

static s32 func_01E03DC0_b256(Game_b256_01E03DC0 *g, Fx_b256_01E03DC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xF0, 0xE0, 0xFF);
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
    if (g->count < 183) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b256", func_01E04090_b256);

/* shape b256:01E04900, 106 insns, 7 copies: b759:01E03880 with 400 slots and two more fields copied (f52 = owner fCBB0, f5A = owner fCBA2): take a free effect slot, clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b256_01E04900 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b256_01E04900;

typedef struct Obj_b256_01E04900 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b256_01E04900 slots[400];
    u8 padB[0xCB14 - 0x2a0 - 400 * 0x70];
    u8 rgba[4];
    u8 padC[0xCBA2 - 0xCB14 - 4];
    s16 fB;
    u8 padD[0xCBB0 - 0xCBA2 - 2];
    s16 fA;
} Obj_b256_01E04900;

static s32 func_01E04900_b256(Obj_b256_01E04900 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b256_01E04900 *s = NULL;
    s16 i;

    for (i = 0; i < 400; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 400;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fA;
        s->f52 = obj->fA;
        s->f5A = obj->fB;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b256:01E04AB0, 335 insns, 3 copies: draws a ribbon between two point trails like b134:01E00820: each segment is 4
   spline quads (module curve function, shape b018:01E00EE0) from the first trail to the second; the near edge
   is transparent, the far edge fades by 3 per quad; the first segment runs on local copies (each trail's first
   point doubled). */

typedef struct Rgbaq_b256_01E04AB0 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b256_01E04AB0;

typedef struct {
    Rgbaq_b256_01E04AB0 c;
    u64 xyz;
} Vtx_b256_01E04AB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b256_01E04AB0 v[4];
    u8 tail[0x40];
} Pkt_b256_01E04AB0;

typedef struct {
    u8 r, g, b, a;
} C4_b256_01E04AB0;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b256_01E04AB0 col;
} Rib_b256_01E04AB0;

static inline u8 b256_01E04AB0_fade(s32 x) {
    s16 r = x;

    r -= 3;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E04AB0_b256(void *o, Rib_b256_01E04AB0 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b256_01E04AB0 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b256_01E04AB0 pkt __attribute__((aligned(8)));
    C4_b256_01E04AB0 c0;
    C4_b256_01E04AB0 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s32 ot;
    Pkt_b256_01E04AB0 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b256_01E04AB0 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = s->col;
    c1 = s->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    pkt.v[0].c = func_00107740(&c0);
    pkt.v[1].c = func_00107740(&c0);
    pkt.v[2].c = func_00107740(&c1);
    pkt.v[3].c = func_00107740(&c1);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c1);
            al = c1.a;
            if (al - 4 > 0) {
                c1.a = b256_01E04AB0_fade(al);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E01540_b256(pp, 0, t);
                B[0] = func_01E01540_b256(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E01540_b256(pp, 0, t);
                B[1] = func_01E01540_b256(pq, 0, t);
            } else {
                A[0] = func_01E01540_b256(a4, 0, t);
                B[0] = func_01E01540_b256(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E01540_b256(a4, 0, t);
                B[1] = func_01E01540_b256(b4, 0, t);
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}

/* shape b256:01E04FF0, 89 insns, 3 copies: draws all live particles of the module's pool whose callback is the module's
   particle drawer (b256:01E03DC0) into one packet, inside a draw context opened only when one was drawn. */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
} Pkt_b256_01E04FF0;

typedef struct {
    u8 pad00[0x44];
    void *cb;
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b256_01E04FF0;

typedef struct {
    u8 pad0000[0x2A0];
    Slot_b256_01E04FF0 slots[400];
    u8 padB1A0[0x1984];
    s32 ctx;
    Pkt_b256_01E04FF0 *pkt;
} Pool_b256_01E04FF0;

static void func_01E04FF0_b256(Pool_b256_01E04FF0 *o) {
    extern s32 func_00207F60(void);
    extern s32 func_00208460();
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_00207FD0(s32, void *, s32);
    extern void b256_01E03DC0(void *, void *);
    Pkt_b256_01E04FF0 pkt __attribute__((aligned(8)));
    s32 a[2];
    s32 b[4] __attribute__((aligned(8)));
    s32 i;
    s32 n;

    o->pkt = &pkt;
    n = 0;
    o->ctx = func_00207F60();
    o->pkt->count = 0x26;
    o->pkt->tag = 5;
    o->pkt->regs = 0x42421;
    o->pkt->pad = 0;
    func_00208460();
    func_002086D0(o->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, a, b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (o->slots[i].used != 0) {
            n++;
            if (o->slots[i].cb == b256_01E03DC0) {
                b256_01E03DC0(o, &o->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(o->ctx, func_00207500(), 0);
    }
}
