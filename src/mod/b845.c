#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b845(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b845(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b845(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b445:01E00D10, 372 insns, 5 copies: draws a row of small sprites (one per entry) at a position: kind 0 camera-facing
   quads turned by the emitter rotation, kind 1 flat bars; each shaken by a per-entry table offset that grows along
   the row; blend from flags >> 4, depth mode flags & 0xF (projected, far, front). Texture corners by the module
   helper (shape b003:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b445_01E00D10;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b445_01E00D10 c;
    struct {
        u64 tc;
        u64 x : 16, y : 16, z : 24, f : 8;
    } v[4];
    u8 tail[0x38];
} Pkt_b445_01E00D10;

typedef struct {
    u8 pad00[0x10];
    Vec4f scale;
    u8 pad20[0x60];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 kind;
    u8 padB2[6];
    s16 count;
    u8 padBA[6];
    s16 ids[12];
    u8 xD8[1];
} Obj_b445_01E00D10;

typedef struct {
    u8 pad00[8];
    s16 off;
    u8 pad0A[6];
    Vec4f pos;
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 w50;
    u8 pad52[8];
    s16 axis;
    u8 pad5C[4];
    u8 col[4];
} Spr_b445_01E00D10;

static void func_01E00D10_b845(Obj_b445_01E00D10 *o, Spr_b445_01E00D10 *s, s32 flags, s8 *tbl) {
    extern Rgbaq_b445_01E00D10 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00107070(void *, s32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f e;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s32 ax[4];
    Pkt_b445_01E00D10 pkt __attribute__((aligned(8)));
    f32 f;
    f32 u;
    s16 off;
    s16 c;
    s16 i;
    Pkt_b445_01E00D10 *p;
    u8 mode;

    p = (Pkt_b445_01E00D10 *)(s32)&pkt;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    if ((flags >> 4) == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)(flags >> 4) << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->c = func_00107740(s->col);
    func_01E00110_b845((Pk_b003_01E00080 *)p, &o->rect, 0);
    func_00208700(p, o->texture, 1);
    func_00205C40((s32)rot);
    rot[1] = rot[1] / 180;
    rot[1] = -rot[1];
    rot[0] = rot[0] / 180;
    rot[0] = -rot[0];
    p2.x = s->pos.x;
    p2.y = s->pos.y;
    p2.z = s->pos.z;
    if (o->kind == 0) {
        func_00108EF0(m, &o->scale, NULL, &p2);
    } else if (o->kind == 1) {
        func_00108EF0(m, &o->scale, &s->rot, &p2);
    }
    ax[1] = s->axis;
    mode = flags & 0xF;
    for (i = 0; i < o->count; i++) {
        if (o->kind == 0) {
            func_01E00110_b845((Pk_b003_01E00080 *)p, &o->rect, o->ids[i]);
            func_00108CE0(quad, s->size, s->size);
            func_00109100(quad, rot, 1, o->xD8);
            func_00109100(quad, rot, 0, o->xD8);
        } else if (o->kind == 1) {
            func_00108CE0(quad, s->size, s->size);
        }
        for (c = 0; c < 3; c++) {
            if (c == 0) {
                off = 0;
            }
            if (c == 1) {
                off = 100;
            }
            if (c == 2) {
                off = 180;
            }
            f = (tbl + i)[s->off + off];
            f /= 20.0f;
            u = f * (f32)(s->w50 + (i >> 1));
            if (c == 0) {
                e.x = u;
            }
            if (c == 1) {
                e.y = u;
            }
            if (c == 2) {
                e.z = u;
            }
        }
        if (o->kind == 0) {
            func_00108950(&e, ax, 0, o->xD8);
        }
        if (o->kind == 1) {
            func_00108950(&e, ax, 0, o->xD8);
        }
        func_00107070(quad, 0, e.x);
        func_00107070(quad, 1, e.y);
        func_00107070(quad, 2, e.z);
        if (o->kind == 1) {
            quad[0].y = 0.0f;
            quad[1].y = 0.0f;
            quad[0].x = s->size;
            quad[1].x = -s->size;
            quad[0].z = 0.0f;
            quad[1].z = 0.0f;
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
        } else if (mode == 2) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b845 in the
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

static void func_01E012E0_b845(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b845((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b016:01E014F0, 256 insns, 37 copies: draw an object's parts as camera-facing bands (two edge widths,
   angles stepped by cam->f5A through a sine table); colour passed by value */

typedef struct Cam_b016_01E014F0 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b016_01E014F0;

typedef struct Obj_b016_01E014F0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b016_01E014F0;

typedef struct Uv_b016_01E014F0 {
    f32 u, v;
} Uv_b016_01E014F0;

typedef struct Vtx_b016_01E014F0 {
    Uv_b016_01E014F0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b016_01E014F0;

typedef struct Pk_b016_01E014F0 {
    u8 hdr[0x10];
    Vtx_b016_01E014F0 v[4];
    u8 pad70[0x20];
} Pk_b016_01E014F0;

static void func_01E015A0_b845(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b016_01E014F0 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b016_01E014F0 pk;
    Uv_b016_01E014F0 uv0;
    Uv_b016_01E014F0 uv1;
    Uv_b016_01E014F0 uv2;
    Uv_b016_01E014F0 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}

/* shape b845:01E019A0 (B845_W_S), 269 insns: b445:01E019A0 with every TENTH tick (not 13th) from 140 to 320 for the
   point spawns, and this module's own callbacks (0x1E01DE0, 0x1E03C50, 0x1E03D10, 0x1E026F0, 0x1E02AF0, 0x1E03640,
   0x1E02E40; spawn helper 0x1E04BC0) (chatA, 16 Oct) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xD930 - 0x260];
    Vec4f pts[10];
    u8 padD9D0[0xDA70 - 0xD9D0];
    Vec4f pt0;
    Vec4f pt1;
    u8 padDA90[0xDB68 - 0xDA90];
    s16 id;
    u8 padDB6A[0xDC1A - 0xDB6A];
    s16 cnt;
    u8 padDC1C[6];
    s16 next;
    u8 padDC24[0x20];
    s16 slot;
    u8 padDC46[6];
    s16 timer;
} Ctx_b845_01E019A0;

static void func_01E019A0_b845(Ctx_b845_01E019A0 *g) {
    extern s32 b845_01E01DE0(void);
    extern s32 b845_01E026F0(void);
    extern s32 b845_01E02AF0(void);
    extern s32 b845_01E02E40(void);
    extern s32 b845_01E03640(void);
    extern s32 b845_01E03C50(void);
    extern s32 b845_01E03D10(void);
    extern void b845_01E04BC0(Ctx_b845_01E019A0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->timer++;
    func_001F5620(func_001F53A0(), g->id, &g->pt0);
    func_001F5620(func_001F53A0(), g->id, &g->pt1);
    if (g->timer == 45) {
        g->slot = 0;
        b845_01E04BC0(g, b845_01E01DE0, 0);
    }
    if (g->timer >= 55 && g->timer % 3 == 1 && g->timer < 286) {
        g->slot = 1;
        b845_01E04BC0(g, b845_01E01DE0, 0);
    }
    if (g->timer == 1) {
        b845_01E04BC0(g, b845_01E03C50, 0);
    }
    if (g->timer == 173) {
        g->slot = 0;
        b845_01E04BC0(g, b845_01E03D10, 0);
    }
    if (g->timer >= 140 && g->timer % 10 == 1 && g->timer < 321) {
        if (g->cnt < 10) {
            g->slot = g->cnt;
            func_001F5620(func_001F53A0(), g->id, &g->pts[g->cnt]);
            b845_01E04BC0(g, b845_01E026F0, 0);
            b845_01E04BC0(g, b845_01E02AF0, 0);
            g->cnt++;
        }
    }
    if (g->timer > 45 && g->timer < 286) {
        for (i = 0; i < 1; i++) {
            if (g->timer % 2 == 1) {
                g->slot = g->next;
                b845_01E04BC0(g, b845_01E03640, 0);
                g->next++;
                if (g->next >= 80) {
                    g->next = 0;
                }
            } else {
                g->slot = g->next;
                g->next++;
                if (g->next >= 80) {
                    g->next = 0;
                }
            }
        }
    }
    if (g->timer > 45 && g->timer < 316) {
        for (i = 0; i < 1; i++) {
            g->pos = g->pt1;
            b845_01E04BC0(g, b845_01E02E40, 0);
        }
    }
}

/* shape b845:01E01DE0, 253 insns: b845:01E02570's beam set up by kind (0x50): kind 0 is 100 long, white and yellow, in
   over 20 ticks by 10 and out by 11 after scene clock 280; kind 1 is 10..59 long, grey (dimmer from clock 200), in
   over 4 ticks by 0x40 and out by 11 at once; both blink by tick parity in their own colours and turn 0x4000 a tick */

typedef struct {
    u8 pad0[0xDC4C];
    s16 clock;
} Scene_b845_01E01DE0;

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x20];
    f32 f4C;
    s16 kind;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b845_01E01DE0;

static s32 func_01E01DE0_b845(Scene_b845_01E01DE0 *g, Obj_b845_01E01DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f4C = 100.0f;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0xFF, 0x80);
            o->h52 = 20;
        }
        if (o->kind == 1) {
            o->f4C = 10.0f + func_0019A5C8() % 50;
            if (g->clock < 200) {
                func_001076F0(o->col2, 0x40, 0x40, 0x40);
                func_001076F0(o->col, 0x80, 0x80, 0x40);
            } else {
                func_001076F0(o->col2, 0x20, 0x20, 0x20);
                func_001076F0(o->col, 0x40, 0x40, 0x20);
            }
            o->h52 = 4;
        }
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->h52) {
        if (o->kind == 0) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 10;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 0x40;
            }
        }
    } else {
        if (o->kind == 0) {
            if (g->clock > 280) {
                if (o->col2[3] > 12) {
                    o->col2[3] -= 11;
                } else {
                    o->mode = 0;
                }
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 12) {
                o->col2[3] -= 11;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        if (g->clock < 200) {
            if (o->t % 2 == 1) {
                func_001076F0(o->col, 0xFF, 0xFF, 0x80);
            } else {
                func_001076F0(o->col, 0xC0, 0xC0, 0x80);
            }
        } else if (o->t % 2 == 1) {
            func_001076F0(o->col, 0xC0, 0xC0, 0x60);
        } else {
            func_001076F0(o->col, 0x80, 0x80, 0x40);
        }
    }
    if (o->kind == 1) {
        if (g->clock < 200) {
            if (o->t % 2 == 1) {
                func_001076F0(o->col, 0x80, 0x80, 0xFF);
            } else {
                func_001076F0(o->col, 0x80, 0x80, 0xC0);
            }
        } else if (o->t % 2 == 1) {
            func_001076F0(o->col, 0x40, 0x40, 0x80);
        } else {
            func_001076F0(o->col, 0x40, 0x40, 0x60);
        }
    }
    o->t++;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    return 0;
}

/* shape b445:01E021E0, 81 insns: a flickering spinning flash: on start size 280, colours white and
   (0xFF,0xFF,0x80), f52 6; the second alpha grows by 0x60 (below 0xC0) for f52 ticks, then fades out by 19 and
   stops; the first colour flickers between (0xFF,0xFF,0x80) and (0xC0,0xC0,0x80); turns by 0x4000 each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
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
} Fx_b445_01E021E0;

static s32 func_01E021E0_b845(s32 arg0, Fx_b445_01E021E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 280.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->f52 = 6;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->f52) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 0x14) {
        o->col2[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0x80);
    }
    o->tick++;
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    return 0;
}

/* shape b445:01E02330, 144 insns: b183:01E012F0 family: a spark cycling yellow/red/blue every tick */

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b445_01E02330;

static s32 func_01E02330_b845(void *arg0, Obj_b445_01E02330 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = func_0019A5C8() % 10 + 10;
        o->h56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 20 + 10;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->h5C = (func_0019A5C8() >> 4) % 360;
        o->hE = func_0019A5C8() % 15 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 10 + 13;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0x40);
    } else if (o->t % 3 == 2) {
        func_001076F0(o->col, 0xC0, 0x40, 0x40);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0xC0);
    }
    o->h52++;
    o->h50 += o->hE;
    o->t++;
    return 0;
}

/* shape b845:01E02570, 94 insns: b264:01E029E0 family: a white/grey beam from 200 growing 75 a tick (tail 400 behind) at three random turns, turning 0x100: alpha 0x60 for 6 ticks, then out by 14 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b845_01E02570;

static s32 func_01E02570_b845(s32 arg0, Obj_b845_01E02570 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        o->h50 = 0;
        o->h5A = 15;
        o->h5C = 15;
        o->f34 = 750.0f;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 6) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 400.0f;
    o->w24 += 0x100;
    o->t++;
    return 0;
}

/* shape b845:01E026F0, 253 insns: a pale blue flash (size 70) that fades in by 0x60 for 20 ticks, blinks white/grey,
   cycles 8 frames and turns; until tick 32 it moves its point (the scene's points at 0xD930, picked by 0x50) 5 in
   depth, against the scene flag (0xDC48); at tick 32 it puts the scene point there and spawns 0x1E021E0, five
   0x1E02330, seven 0x1E02570, ten 0x1E02C60, seven 0x1E03040 (numbered by the scene's 0..79 counter 0xDC22, passed
   in 0xDC44) and 0x1E03D10 (0xDC44 = 1) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xD930 - 0x260];
    Vec4f pts[0x2F];
    u8 padDC20[2];
    s16 count;
    u8 padDC24[0x20];
    s16 arg;
    u8 padDC46[2];
    s16 flag;
} Scene_b845_01E026F0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x18];
    s16 idx;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Obj_b845_01E026F0;

static s32 func_01E026F0_b845(Scene_b845_01E026F0 *g, Obj_b845_01E026F0 *o) {
    extern void b845_01E021E0(void);
    extern void b845_01E02330(void);
    extern void b845_01E02570(void);
    extern void b845_01E02C60(void);
    extern void b845_01E03040(void);
    extern void b845_01E03D10(void);
    extern void b845_01E04BC0(Scene_b845_01E026F0 *, void (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->hA = o->h8 = 70;
        o->h56 = func_0019A5C8() % 8;
        o->f34 = 0.5f;
        func_001076F0(o->col, 0xA0, 0xA0, 0xFF);
        o->mode = 2;
    }
    if (o->t < 20) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    o->h56++;
    if (o->h56 > 7) {
        o->h56 = 0;
    }
    if (o->t != 0) {
        if (g->flag != 0) {
            if ((s16)o->t < 33) {
                g->pts[o->idx].z -= 5.0f;
            }
        } else if ((s16)o->t < 33) {
            g->pts[o->idx].z += 5.0f;
        }
    }
    if (o->t == 32) {
        g->pos = g->pts[o->idx];
        b845_01E04BC0(g, b845_01E021E0, 0);
        for (i = 0; i < 5; i++) {
            b845_01E04BC0(g, b845_01E02330, 0);
        }
        for (i = 0; i < 7; i++) {
            b845_01E04BC0(g, b845_01E02570, 0);
        }
        for (i = 0; i < 10; i++) {
            b845_01E04BC0(g, b845_01E02C60, 0);
        }
        for (i = 0; i < 7; i++) {
            g->arg = g->count;
            b845_01E04BC0(g, b845_01E03040, 0);
            g->count++;
            if (g->count >= 80) {
                g->count = 0;
            }
        }
        g->arg = 1;
        b845_01E04BC0(g, b845_01E03D10, 0);
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b445:01E02B30, 89 insns: a flickering ring: on start f48 80, f8/fA 70, f56 random 0..7, grey colour,
   life 5; alpha 0x80 until tick 0x22, then stops; colour flickers between (0xC0,0xC0,0) and (0x40,0x40,0xC0);
   f56 cycles 0..7; turns each tick and f5A steps by 10 (mod 360) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
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
} Fx_b445_01E02B30;

static s32 func_01E02AF0_b845(s32 arg0, Fx_b445_01E02B30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 80.0f;
        o->f8 = 70;
        o->fA = 70;
        o->f56 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->life = 5;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x22) {
        o->col[3] = 0x80;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0xC0, 0xC0, 0);
    } else {
        func_001076F0(o->col, 0x40, 0x40, 0xC0);
    }
    if (o->f56 < 7) {
        o->f56++;
    } else {
        o->f56 = 0;
    }
    o->tick++;
    func_00205C40((s32)o->rot);
    o->f5A += 10;
    if (o->f5A >= 360) {
        o->f5A %= 360;
    }
    return 0;
}

/* shape b445:01E02CA0, 119 insns, 2 copies: a dark smoke puff: set up once (random size 50..89, frame 0..4, angle, two turns,
   speed, life 13..22); full for its life, then fades out; its frame climbs each frame and it ends at 8 (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    s16 h52;
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b445_01E02CA0;

static s32 func_01E02C60_b845(void *arg0, Spark_b445_01E02CA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 40 + 50;
        o->frame = (func_0019A5C8() >> 4) % 5;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->ang = func_0019A5C8() % 250 + 100;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->h5C = (func_0019A5C8() >> 4) % 360;
        o->speed = func_0019A5C8() % 15 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 10 + 13;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->frame++;
        if (o->frame > 7) {
            o->state = 0;
        }
    }
    o->h52++;
    o->t++;
    return 0;
}

/* shape b445:01E02E80, 126 insns: b183:01E012F0 family: a flickering spark (alternates 0x80/0x60 grey every frame), frames 2..7 then dies */

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b445_01E02E80;

static s32 func_01E02E40_b845(void *arg0, Obj_b445_01E02E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 2.0f;
        o->h56 = 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 80 + 20;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->h5C = (func_0019A5C8() >> 4) % 360;
        o->hE = func_0019A5C8() % 15 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 10 + 13;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->h56++;
        if (o->h56 > 7) {
            o->state = 0;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
    }
    o->h52++;
    o->t++;
    return 0;
}

/* shape b445:01E03080, 381 insns, 2 copies: a jittery white spark trail on a world track (b149:01E01ED0 family): set up once
   (point reset and nudged by a random kick, the track's 20 points filled with it, random size, speed, heading,
   life); its frame grows for 7 frames then shrinks, full for its life then fades out, blinks; each frame the
   point drifts along its heading and jitters, while the module's shape b445:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b445_01E03080;

typedef struct {
    u8 pad0[0x7030];
    Track_b445_01E03080 track[0x40];
    u8 pad[0xD430 - 0x7030 - 0x40 * 0x140];
    Vec4f pt[0xB2];
    u8 trig[1];
} World_b445_01E03080;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b445_01E03080;

static s32 func_01E03040_b845(World_b445_01E03080 *w, Spark_b445_01E03080 *o) {
    extern void b845_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 2.0f;
        w->pt[o->idx].y += o->v.y / 2.0f;
        w->pt[o->idx].z += o->v.z / 2.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 150 + 50;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 125 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = 0x5A;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        b845_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b445:01E03680, 387 insns, 2 copies: a jittery spark trail (b445:01E03080 twin: smaller, random pitch, grey blink) on a world track (b149:01E01ED0 family): set up once
   (point reset and nudged by a random kick, the track's 20 points filled with it, random size, speed, heading,
   life); its frame grows for 7 frames then shrinks, full for its life then fades out, blinks; each frame the
   point drifts along its heading and jitters, while the module's shape b445:01E00080 shifts the track */

typedef struct {
    Vec4f p[0x14];
} Track_b445_01E03680;

typedef struct {
    u8 pad0[0x7030];
    Track_b445_01E03680 track[0x40];
    u8 pad[0xD430 - 0x7030 - 0x40 * 0x140];
    Vec4f pt[0xB2];
    u8 trig[1];
} World_b445_01E03680;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b445_01E03680;

static s32 func_01E03640_b845(World_b445_01E03680 *w, Spark_b445_01E03680 *o) {
    extern void b845_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 60 - 30;
        o->v.y = func_0019A5C8() % 60 - 30;
        o->v.z = func_0019A5C8() % 60 - 30;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 50 + 20;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 25 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = (func_0019A5C8() >> 4) % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
    }
    o->v.x = func_0019A5C8() % 80 - 40;
    o->v.y = func_0019A5C8() % 80 - 40;
    o->v.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 15.0f;
        w->pt[o->idx].y += o->v.y / 15.0f;
        w->pt[o->idx].z += o->v.z / 15.0f;
    }
    if (o->t < 7) {
        b845_01E00080(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b445:01E03C90, 48 insns: volume fade: starts at 0x80; while the game state 0xDB30 is above 0x14 fade down
   by 10 (floor 0x30), else back up by 10, ending the effect once at the cap 0x80 */

typedef struct {
    u8 pad[0xDB30];
    s32 state;
} Game_b445_01E03C90;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b445_01E03C90;

static s32 func_01E03C50_b845(Game_b445_01E03C90 *g, Fade_b445_01E03C90 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
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
            o->mode = 0;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    func_001F6D00((u8)o->vol);
    return 0;
}

/* shape b845:01E03D10, 166 insns: b445:01E03D50's two-kind veil in warm grey (0x80/0x80/0x68); kind 0 rises while the
   scene timer at 0xDB30 is above 20 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b845_01E03D10;

typedef struct {
    f32 s, t;
    Xyz_b845_01E03D10 p;
} Tv_b845_01E03D10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b845_01E03D10 v[2];
    u8 tail[0x20];
} Tex_b845_01E03D10;

typedef struct {
    u8 pad0[0xDB30];
    s32 timer;
} Ctx_b845_01E03D10;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b845_01E03D10;

static s32 func_01E03D10_b845(Ctx_b845_01E03D10 *g, Fx_b845_01E03D10 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b845_01E03D10 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    ((Tex_b845_01E03D10 *)(s32)&pk)->flags = 0x26;
    ((Tex_b845_01E03D10 *)(s32)&pk)->size = 5;
    ((Tex_b845_01E03D10 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b845_01E03D10 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x68;
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    if (o->kind == 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    }
    if (o->kind == 1) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (o->kind == 0) {
        if (g->timer > 20) {
            if (o->col[3] < 0x50) {
                o->col[3] += 8;
            }
        } else if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind == 1) {
        if (o->tick < 5) {
            if (o->col[3] < 0x50) {
                o->col[3] += 0x28;
            }
        } else if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03FB0_b845(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b845", func_01E03FC0_b845);

/* shape b445:01E04BF0, 106 insns: b003:01E02E90 family (like b544:01E031D0): take the first free slot of the 250-slot pool,
   clear it, give it the scene's colour twice, the scene matrix and position, scene values and the two arguments;
   returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 v50;
    s16 v52;
    u8 pad54[4];
    s16 used;
    s16 v5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b445_01E04BF0;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x44];
    Slot_b445_01E04BF0 s[250];
    u8 padEND[0x6b34];
    u8 r, g, b, a;
    u8 padC4[0xe6];
    s16 vA;
    u8 padA2[0x24];
    s16 vB;
} Pool_b445_01E04BF0;

static s32 func_01E04BC0_b845(Pool_b445_01E04BF0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b445_01E04BF0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 250; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x70);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 250;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, &o->x, 0);
        ret = 1;
        s->x = o->x;
        s->y = o->y;
        s->z = o->z;
        s->v5A = o->vA;
        s->v50 = o->vB;
        s->v52 = o->vB;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b847:01E00E60 (IWMagicTThunder1), 723 insns, 14 copies: b081:01E05C10's beam along the module spline
   (inlined, b081:01E009A0 type 0 with its weights declared b3..b0), one sub-step per segment from the start index at
   0xE, each a 2-quad cross through the beam matrix (0x20) at the context position; float width (0x48) / 10 shrinking
   by width/(8n), alpha test from flags >> 4, alpha fades by col0.a/(3n); flags & 0xF picks the depth (0 real, 1 far)
   */

typedef struct {
    f32 x, y, z, w;
} Vec_b847_01E00E60;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b847_01E00E60;

typedef struct {
    u8 r, g, b, a;
} Col_b847_01E00E60;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b847_01E00E60;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b847_01E00E60 c;
        u64 st;
        Xyz_b847_01E00E60 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b847_01E00E60;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b847_01E00E60;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[6];
    s16 start;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 width;
    u8 pad4C[0x14];
    Col_b847_01E00E60 col0;
    Col_b847_01E00E60 col1;
} Beam_b847_01E00E60;

static inline Vec_b847_01E00E60 spline_b847_01E00E60(Vec_b847_01E00E60 *p, s32 type, f32 t) {
    Vec_b847_01E00E60 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

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

/* pts aligned: its spill slot, needed for the match */
static void func_01E04D70_b845(Ctx_b847_01E00E60 *c, Beam_b847_01E00E60 *an, Vec_b847_01E00E60 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b847_01E00E60 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b847_01E00E60 ab[2];
    Vec_b847_01E00E60 ctrl[4];
    Vec_b847_01E00E60 prev;
    Vec_b847_01E00E60 q[4];
    Vec_b847_01E00E60 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b847_01E00E60 pkt __attribute__((aligned(8)));
    Col_b847_01E00E60 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    s16 sel;
    Pkt_b847_01E00E60 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    n = an->count;
    w /= 10.0f;
    w0 = w;
    func_00109270(p, 0, 0);
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    for (i = an->start; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 1; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 1.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 1.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(ctrl, 0, t);
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (8.0f * n);
            for (k = 0; k < 2; k++) {
                func_00109A70(&q[0], &ab[0]);
                func_00109A70(&q[1], &ab[0]);
                func_00109A70(&q[2], &ab[1]);
                func_00109A70(&q[3], &ab[1]);
                if (k == 0) {
                    q[1].y += w1;
                    q[3].y += w;
                    q[0].y -= w1;
                    q[2].y -= w;
                } else if (k == 1) {
                    q[1].x += w1;
                    q[3].x += w;
                    q[1].z += w1 / 2.0f;
                    q[3].z += w / 2.0f;
                    q[0].x -= w1;
                    q[2].x -= w;
                    q[0].z -= w1 / 2.0f;
                    q[2].z -= w / 2.0f;
                }
                if ((flags & 0xF) == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, func_001A23B0(depth[0]));
                    }
                } else if ((flags & 0xF) == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                }
            }
        }
    }
}
