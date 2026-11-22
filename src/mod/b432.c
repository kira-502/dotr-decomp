#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b432(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b432(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E009B0_b432(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b432_01E00110();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b432_01E00110(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
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

static void func_01E00F00_b432(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b432 in the
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

static void func_01E01260_b432(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b432((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01520_b432(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b432:01E01920, 164 insns: b763:01E01920 family event step: counts ticks; from 96 to 154 spawns two b432:01E01BB0 and a b432:01E02FA0 at the first tracked point, then moves to the second (slot 4); from 130 to 230 spawns b432:01E020D0 and b432:01E022D0 (slot 1); at tick 1 reads the camera and spawns b432:01E03360, 01E03460 and 01E03680; at 100 spawns b432:01E02DE0 and b432:01E031D0; from 148, every fourth tick, places up to 30 points (ctx+0x7CB0) and spawns b432:01E02800 and b432:01E01D80 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x7CB0 - 0x25C];
    Vec4f pts[30];
    f32 cam[4];
    u8 pad7EA0[0x7EF4 - 0x7EA0];
    s16 id1;
    u8 pad7EF6[2];
    s16 id0;
    u8 pad7EFA[0x7F22 - 0x7EFA];
    s16 slot;
    s16 n;
    u8 pad7F26[4];
    s16 timer;
} Ctx_b432_01E01920;

static void func_01E01920_b432(Ctx_b432_01E01920 *g) {
    extern s32 b432_01E01BB0(void);
    extern s32 b432_01E01D80(void);
    extern s32 b432_01E020D0(void);
    extern s32 b432_01E022D0(void);
    extern s32 b432_01E02800(void);
    extern s32 b432_01E02DE0(void);
    extern s32 b432_01E02FA0(void);
    extern s32 b432_01E031D0(void);
    extern s32 b432_01E03360(void);
    extern s32 b432_01E03460(void);
    extern s32 b432_01E03680(void);
    extern void b432_01E04130(Ctx_b432_01E01920 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, f32 *);

    g->timer++;
    if (g->timer >= 96 && g->timer < 155) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        g->slot = 0;
        b432_01E04130(g, b432_01E01BB0, 0);
        b432_01E04130(g, b432_01E01BB0, 0);
        b432_01E04130(g, b432_01E02FA0, 0);
        func_001F5620(func_001F53A0(), g->id1, g->pos);
        g->slot = 4;
    }
    if (g->timer >= 130 && g->timer < 231) {
        g->slot = 1;
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        b432_01E04130(g, b432_01E020D0, 0);
        b432_01E04130(g, b432_01E022D0, 0);
    }
    if (g->timer == 1) {
        func_001F5F90(func_001F5380(), g->cam);
    }
    if (g->timer == 1) {
        b432_01E04130(g, b432_01E03360, 0);
    }
    if (g->timer == 1) {
        b432_01E04130(g, b432_01E03460, 0);
    }
    if (g->timer == 1) {
        b432_01E04130(g, b432_01E03680, 0);
    }
    if (g->timer == 100) {
        b432_01E04130(g, b432_01E02DE0, 0);
    }
    if (g->timer == 100) {
        b432_01E04130(g, b432_01E031D0, 0);
    }
    if (g->timer >= 148) {
        if (g->timer % 4 == 1) {
            if (g->n < 30) {
                g->slot = g->n;
                func_001F5620(func_001F53A0(), g->id0, &g->pts[g->slot]);
                b432_01E04130(g, b432_01E02800, 0);
                b432_01E04130(g, b432_01E01D80, 0);
                g->n++;
            }
        }
    }
}

/* shape b432:01E01BB0, 115 insns: b038:01E01090's smoke puff, short form: on start size 4.0, random frame/headings/
   timings, grey colour; alpha +0x20 (below 0x80) for h6 ticks then -8; heading 0x5C turns 2 per tick. */

typedef struct {
    u8 pad0[0x7EF8];
    s16 v;
} Ctx_b432_01E01BB0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 x, y, z;
    u8 pad1C[0x14];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    u8 pad40[8];
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
} Obj_b432_01E01BB0;

static s32 func_01E01BB0_b432(Ctx_b432_01E01BB0 *ctx, Obj_b432_01E01BB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 b[4];

    if (o->state == 1) {
        o->f48 = 4.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 20 + 10;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        func_001F5620(func_001F53A0(), ctx->v, b);
        o->state = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->state = 0;
    }
    o->h5C += 2;
    o->t++;
    return 0;
}

/* shape b432:01E01D80, 102 insns, 2 copies: a white blinker pinned to a model joint: set up once (size 30, frame 4, random
   angle); fades in over 50 frames, then out; blinks white/grey each frame and follows the joint's position */

typedef struct {
    f32 x, y, z;
    u8 padC[0x1D4];
} Joint_b432_01E01D80;

typedef struct {
    u8 pad0[0x4470];
    Joint_b432_01E01D80 j[1];
} World_b432_01E01D80;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    u8 x20[0x30];
    s16 joint;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 c0[4];
} Blink_b432_01E01D80;

static s32 func_01E01D80_b432(World_b432_01E01D80 *w, Blink_b432_01E01D80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = 0x1E;
        o->hA = o->h8;
        o->frame = 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->state = 2;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->x20);
    }
    if (o->t < 0x32) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    o->x = w->j[o->joint].x;
    o->y = w->j[o->joint].y;
    o->z = w->j[o->joint].z;
    func_00205C40((s32)o->x20);
    o->t++;
    return 0;
}

/* shape b432:01E01F20, 108 insns: a white spark: f48 10, f56 5, random f5A/f5C, fA -7..7, fC = the old f50, f50
   10..19, spin 10..29, f8 0..34, life 3..7; alpha grows by 0x20 (below 0x80) during the life, then fades by 8;
   f50 grows by the spin each tick after the first */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x38];
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
} Fx_b432_01E01F20;

static s32 func_01E01F20_b432(s32 arg0, Fx_b432_01E01F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = 5;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 10 + 10;
        o->spin = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b432:01E020D0, 125 insns: b203:01E03140 family rising flash, one of two looks (pink on black or light red on grey 0x50), from 80 rising (200..249)/10 per tick, f4C = 0.2 of it, full alpha 8 ticks then down by 5 */

typedef struct {
    u8 pad0[0x20];
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b432_01E020D0;

static s32 func_01E020D0_b432(void *arg0, Obj_b432_01E020D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 80.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->c0, 0xC0, 0x80, 0x80);
            func_001076F0(o->c1, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->c0, 0xFF, 0xA0, 0xA0);
            func_001076F0(o->c1, 0x50, 0x50, 0x50);
        }
        o->w = 30;
        o->h = 30;
        o->f34 = func_0019A5C8() % 50 + 200;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot0 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = 0.2f * o->f48;
    o->t++;
    return 0;
}

/* shape b432:01E022D0, 127 insns: two-kind glow (b247:01E01F70 family): kind 0 white over red, size 220, held 14; kind 1
   dark (0x18, 8, 8) over dark grey, held 8, three random words; second alpha grows by 0x60 (below 0xC0) while held,
   then fades by 9 (kind 0) or 15 (kind 1); kind 1 grows f48 by 25 and keeps f4C at 0.6 of it */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b432_01E022D0;

static s32 func_01E022D0_b432(s32 arg0, Fx_b432_01E022D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f4C = 220.0f;
            o->hold = 14;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x40, 0x40);
        }
        if (o->kind == 1) {
            o->hold = 8;
            func_001076F0(o->col2, 0x18, 8, 8);
            func_001076F0(o->col, 0x18, 0x18, 0x18);
            o->w20 = func_0019A5C8() % 65535;
            o->w24 = func_0019A5C8() % 65535;
            o->w28 = func_0019A5C8() % 65535;
        }
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->kind == 0) {
            if (o->col2[3] > 0xA) {
                o->col2[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 0x10) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 1) {
        o->f48 += 25.0f;
        o->f4C = 0.6f * o->f48;
    }
    o->tick++;
    return 0;
}

/* shape b432:01E024D0, 128 insns: b432:01E022D0 with red (0x80/0x20/0x20) and grey 0x80 colours for kind 1 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b432_01E024D0;

static s32 func_01E024D0_b432(s32 arg0, Fx_b432_01E024D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f4C = 220.0f;
            o->hold = 14;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x40, 0x40);
        }
        if (o->kind == 1) {
            o->hold = 8;
            func_001076F0(o->col2, 0x80, 0x20, 0x20);
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            o->w20 = func_0019A5C8() % 65535;
            o->w24 = func_0019A5C8() % 65535;
            o->w28 = func_0019A5C8() % 65535;
        }
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->kind == 0) {
            if (o->col2[3] > 0xA) {
                o->col2[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 0x10) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 1) {
        o->f48 += 25.0f;
        o->f4C = 0.6f * o->f48;
    }
    o->tick++;
    return 0;
}

/* shape b432:01E026D0, 75 insns: a pink-grey spinning flash (b236:01E01B70 family): f4C 70 growing by 1 up to 150; second alpha up by 0x40 to
   0xC0 for 7 frames, then down by 15 until it ends */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b432_01E026D0;

static s32 func_01E026D0_b432(void *arg0, Obj_b432_01E026D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = 70.0f;
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 7) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x40;
        }
    } else if (o->c1[3] > 0x10) {
        o->c1[3] -= 0xF;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->t != 0) {
        if (o->f4C < 150.0f) {
            o->f4C += 1.0f;
        }
    }
    o->t++;
    return 0;
}

/* shape b432:01E02800, 374 insns: a homing streak (B432_OBJ_MOVE_10_): set up once with white second colour, its
   30-point trail (ctx+0x4470, slot 0x50) on its point (ctx+0x7CB0), a 48-tick step toward the scene target
   (ctx+0x7E90) jittered by -10..9 on each axis, random turn rate (-10..9), wobble 0..29, turn 0..359; fades in by
   42 before tick 55, then shrinks 0x48 by 1.5 and ends below 0; for 48 ticks it wobbles around its point (sine table
   ctx+0x812C) into the trail; flashes 0xFF / 0xC0 until 80; moves until 45, then marks 0x7F22 and bursts
   b432:01E024D0 + b432:01E01F20 at the trail head until 50, b432:01E026D0 at 48 */

typedef struct {
    Vec4f v[30];
} Trail_b432_01E02800;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Trail_b432_01E02800 trail[16];
    u8 pad6270[0x7CB0 - 0x6270];
    Vec4f pts[16];
    u8 pad7DB0[0x7E90 - 0x7DB0];
    f32 tx, ty, tz;
    u8 pad7E9C[0x7F22 - 0x7E9C];
    s16 flag;
    u8 pad7F24[0x812C - 0x7F24];
    u8 sin[4];
} Ctx_b432_01E02800;

typedef struct {
    s16 turn;
    u8 pad2[4];
    s16 len;
    s16 w;
    s16 wob;
    u8 padC[0x24];
    f32 dx, dy, dz;
    u8 pad3C[0xC];
    f32 f48;
    f32 r;
    s16 idx;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Streak_b432_01E02800;

static s32 func_01E02800_b432(Ctx_b432_01E02800 *g, Streak_b432_01E02800 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(s32, s32, s32);
    extern void func_01E00080_b432();
    extern void b432_01E04130();
    extern s32 func_01E01F20_b432();
    extern s32 func_01E024D0_b432();
    extern s32 func_01E026D0_b432();
    Vec4f v;
    Vec4f *p;
    f32 tx;
    f32 ty;
    f32 tz;
    s16 i;

    v.x = g->pts[o->idx].x;
    v.y = g->pts[o->idx].y;
    v.z = g->pts[o->idx].z;
    if (o->state == 1) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        p = g->trail[o->idx].v;
        for (i = 0; i < 30; i++) {
            p[i].x = v.x;
            p[i].y = v.y;
            p[i].z = v.z;
        }
        tx = g->tx;
        ty = g->ty;
        tz = g->tz;
        ty += func_0019A5C8() % 20 - 10;
        tx += func_0019A5C8() % 20 - 10;
        tz += func_0019A5C8() % 20 - 10;
        o->dx = (tx - g->pts[o->idx].x) / 48.0f;
        o->dy = (ty - g->pts[o->idx].y) / 48.0f;
        o->dz = (tz - g->pts[o->idx].z) / 48.0f;
        o->len = 20;
        o->turn = (func_0019A5C8() >> 4) % 20 - 10;
        o->col[3] = 0;
        o->w = 0;
        o->wob = func_0019A5C8() % 30;
        o->h56 = 4;
        o->ang = func_0019A5C8() % 360;
        o->f48 = 10.0f;
        o->state = 2;
    }
    if (o->t < 55) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    } else {
        if (o->f48 >= 0.0f) {
            o->f48 -= 1.5f;
        } else {
            o->state = 0;
        }
    }
    if (o->t < 48) {
        v.y += o->r * func_00108030((s32)g->sin, o->ang, 0);
        v.x += o->r * func_00108030((s32)g->sin, o->ang, 1);
        o->r = o->wob * func_00108030((s32)g->sin, o->h5C, 0);
        func_01E00080_b432(&g->trail[o->idx].v[29], 30, 0, &v);
        if (o->h5C < 180) {
            o->h5C += 4;
        }
        o->ang += o->turn;
    }
    if (o->t < 80) {
        if (o->t % 2 == 1) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        } else {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        }
    }
    if (o->t != 0 && o->len < 22) {
        o->len++;
    }
    if (o->t < 46) {
        g->pts[o->idx].x += o->dx;
        g->pts[o->idx].y += o->dy;
        g->pts[o->idx].z += o->dz;
    } else {
        if (o->t < 51) {
            g->flag = 1;
            g->pos.x = g->trail[o->idx].v[0].x;
            g->pos.y = g->trail[o->idx].v[0].y;
            g->pos.z = g->trail[o->idx].v[0].z;
            b432_01E04130(g, func_01E024D0_b432, 0);
            b432_01E04130(g, func_01E01F20_b432, 0);
        }
        if (o->t == 48) {
            g->pos.x = g->trail[o->idx].v[0].x;
            g->pos.y = g->trail[o->idx].v[0].y;
            g->pos.z = g->trail[o->idx].v[0].z;
            b432_01E04130(g, func_01E026D0_b432, 0);
        }
    }
    o->t++;
    return 0;
}

/* shape b432:01E02DE0, 111 insns: a red-white glow pushed past a joint: size 50 growing by 3 to 100 after frame 30; second alpha
   up by 19 to 0xC0 until frame 200, then down by 15 until it ends; spins; sits on one joint, pushed a fifth away from another */

typedef struct {
    u8 pad0[0x7EF6];
    s16 joint1;
    s16 joint0;
} Game_b432_01E02DE0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x1C];
    f32 f4C;
    u8 pad50[2];
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b432_01E02DE0;

static s32 func_01E02DE0_b432(Game_b432_01E02DE0 *g, Obj_b432_01E02DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    struct {
        f32 x, y, z, w;
    } v;

    if (o->state == 1) {
        o->f4C = 50.0f;
        func_001076F0(o->c1, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->h52 = 0;
        o->h5A = 0xA;
        o->h5C = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xC8) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x13;
        }
    } else if (o->c1[3] > 0x10) {
        o->c1[3] -= 0xF;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->t >= 0x1E) {
        if (o->f4C < 100.0f) {
            o->f4C += 3.0f;
        }
    }
    o->t++;
    func_001F5620(func_001F53A0(), g->joint0, &o->pos);
    func_001F5620(func_001F53A0(), g->joint1, &v);
    o->pos.x += 0.2f * (o->pos.x - v.x);
    o->pos.y += 0.2f * (o->pos.y - v.y);
    o->pos.z += 0.2f * (o->pos.z - v.z);
    return 0;
}

/* shape b432:01E02FA0, 140 insns: a pink tumbling chip: size 30 (kept in 0xA), frame 2..4, drift -50..49 / 60 on all
   three axes, turn 0..359, an initial spin, a random -0x400..0x3FF tilt per axis, f52 0..3; alpha grows by 0x40
   (below 0x80) for 4 ticks, then fades by 4 (ends below 6); spins every tick */

typedef struct {
    s16 tx, ty, tz;
    u8 pad6[2];
    s16 size;
    s16 size0;
    u8 padC[0x14];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0x16];
    s16 h52;
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b432_01E02FA0;

static s32 func_01E02FA0_b432(s32 arg0, Fx_b432_01E02FA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 30;
        o->size0 = o->size;
        o->frame = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        o->mode = 2;
        o->vy = func_0019A5C8() % 100 - 50;
        o->vx = func_0019A5C8() % 100 - 50;
        o->vz = func_0019A5C8() % 100 - 50;
        o->vy /= 60.0f;
        o->vx /= 60.0f;
        o->vz /= 60.0f;
        o->ang = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->tz = func_0019A5C8() % 0x800 - 0x400;
        o->ty = func_0019A5C8() % 0x800 - 0x400;
        o->tx = func_0019A5C8() % 0x800 - 0x400;
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b432:01E031D0, 100 insns: a white light on a model joint: colour 128/4/4/4, range 123; power up by 0.1 to 1 until frame
   210, then down by 0.3 until it ends; the light follows the joint each frame; ends when the scene state is 1 */

typedef struct {
    u8 pad0[0x4440];
    f32 l0[4];
    f32 pos[3];
    u8 pad445C[4];
    f32 f20;
    f32 range;
    f32 power;
    u8 pad446C[0x7EC0 - 0x446C];
    s32 state;
    u8 pad7EC4[0x34];
    s16 joint;
} Scene_b432_01E031D0;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x34];
    s16 down;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 live;
} Obj_b432_01E031D0;

static s32 func_01E031D0_b432(Scene_b432_01E031D0 *g, Obj_b432_01E031D0 *o) {
    extern void func_001F6C10(void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    struct {
        f32 x, y, z, w;
        f32 pad[4];
    } v;

    if (o->live == 1) {
        g->l0[0] = 128.0f;
        g->l0[1] = 4.0f;
        g->l0[2] = 4.0f;
        g->l0[3] = 4.0f;
        g->f20 = 0.0f;
        g->range = 123.0f;
        g->power = 0.0f;
        g->pos[0] = o->x;
        g->pos[1] = o->y;
        g->pos[2] = o->z;
        o->live = 2;
        o->down = 0;
    }
    func_001F5620(func_001F53A0(), g->joint, &v);
    g->pos[0] = v.x;
    g->pos[1] = v.y;
    g->pos[2] = v.z;
    if (o->t < 0xD2) {
        if (g->power < 1.0f) {
            g->power += 0.1f;
        }
    } else if (!(g->power <= 0.1f)) {
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
    o->t++;
    return 0;
}

/* shape b432:01E03360, 62 insns: volume fade: starts at 0x80, fades down by 10 (floor 0x60) for the first 0x33
   ticks, then back up by 10 (cap 0x80) while the game state is below 0x1E; state 3 forces full volume */

typedef struct {
    u8 pad[0x7EC0];
    s32 state;
} Game_b432_01E03360;

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 size;
    s16 vol;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b432_01E03360;

static s32 func_01E03360_b432(Game_b432_01E03360 *g, Fx_b432_01E03360 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x33) {
        if (o->vol > 0x60) {
            o->vol -= 10;
        } else {
            o->vol = 0x60;
        }
    } else if (g->state < 0x1E) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->tick++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b432:01E03460, 134 insns: b594:01E02CB0 with the sprite in its own colour (0x90, 0x80, 0x80 set on start) at 2.5; alpha up by 22 to 0x58 while the scene timer (s32 at ctx+0x7EC0) is past 45, then down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b432_01E03460;

typedef struct {
    f32 s, t;
    Xyz_b432_01E03460 p;
} Tv_b432_01E03460;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b432_01E03460 v[2];
    u8 tail[0x20];
} Tex_b432_01E03460;

typedef struct {
    u8 pad0[0x7EC0];
    s32 timer;
} Ctx_b432_01E03460;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b432_01E03460;

static s32 func_01E03460_b432(Ctx_b432_01E03460 *g, Fx_b432_01E03460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b432_01E03460 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x90, 0x80, 0x80);
        o->mode = 2;
    }
    ((Tex_b432_01E03460 *)(s32)&pk)->flags = 0x26;
    ((Tex_b432_01E03460 *)(s32)&pk)->size = 5;
    ((Tex_b432_01E03460 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b432_01E03460 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
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
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->timer > 45) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b432:01E03680, 145 insns: b555:01E02CB0 with a pink (0xFF, 0x30, 0x80) sprite in the scene packet at ctx+0x7ED8, zoomed by f8/10 and fA/10; alpha up by 9 to 0x80 for 140 ticks, then down by 7 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b432_01E03680;

typedef struct {
    f32 s, t;
    Xyz_b432_01E03680 p;
} Tv_b432_01E03680;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b432_01E03680 v[2];
} Tex_b432_01E03680;

typedef struct {
    u8 pad[0x7ED8];
    Tex_b432_01E03680 *pk;
} Game_b432_01E03680;

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
} Fx_b432_01E03680;

static s32 func_01E03680_b432(Game_b432_01E03680 *g, Fx_b432_01E03680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0x30, 0x80);
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
    if (o->tick < 140) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->tick > 40) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b432:01E038D0 (b432), 534 insns, 1 copy: b432 scene manager in b763:01E03510 form: setup (six joints,
   type-4/5 textures, two jitter tables), step b432:01E01920 and every slot except b432:01E03680 (counted; the pool
   draw b432:01E04C70 runs if any), draw the ten effect kinds; scene code from the timer */

typedef struct {
    u8 pad0[0xA];
    s16 h0A;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0xC];
    s32 (*fn)();
    u8 pad48[0x8];
    s16 h50;
    s16 h52;
    u8 pad54[0x2];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b432_01E038D0;

typedef struct {
    Vec4f p[30];
} Row_b432_01E038D0;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        s16 h[8];
    } c;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b432_01E038D0 fx[150];
    u8 pad4440[0x30];
    Row_b432_01E038D0 row[31];
    u8 pad7E90[0x10];
    s32 tex[2];
    u8 pad7EA8[0x18];
    s32 count;
    u8 pad7EC4[0x8];
    s32 ot;
    u8 pad7ED0[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad7F00[4];
    s16 cam;
    u8 pad7F06[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b432_01E038D0;

static s32 func_01E038D0_b432(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b432_01E04280();
    extern void b432_01E04C70();
    extern void func_01E01920_b432();
    extern void func_01E009B0_b432();
    extern void func_01E00F00_b432();
    Scene_b432_01E038D0 *g = (Scene_b432_01E038D0 *)arg0;
    s16 m;
    s16 n;
    Vec4f buf;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    s32 i;
    s16 k;

    m = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x82A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 379;
        g->jA = func_001F5560(func_001F53A0(), 0x3B, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x20, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x27, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x26, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x3F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x40, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        g->tex260[0] = func_00202BF0(4, 0);
        for (i = 0; i < 2; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E01920_b432(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E03680_b432) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    m++;
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01BB0_b432) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                g->tex88 = g->tex[0];
                g->hB8 = 3;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y + g->fx[k].f34;
                g->pz = g->fx[k].pos.z;
                func_01E009B0_b432(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D80_b432) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                g->hBE = 0;
                func_01E01260_b432((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos);
                func_01E01260_b432((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01F20_b432) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->tex88 = g->tex[0];
                g->hB8 = 6;
                g->hC0 = g->fx[k].h0A;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y + g->fx[k].f34;
                g->pz = g->fx[k].pos.z;
                func_01E009B0_b432(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E020D0_b432) {
                func_00106080(rm4, 0x96, 2, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm4;
                g->tex88 = g->tex260[15];
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 12;
                g->hBE = 0;
                func_01E01520_b432((Obj_b016_01E014F0 *)g, (Cam_b016_01E014F0 *)&g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E022D0_b432) {
                g->hB8 = 36;
                func_01E00F00_b432(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E024D0_b432) {
                g->hB8 = 36;
                func_01E00F00_b432(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E026D0_b432) {
                g->hB8 = 36;
                func_01E00F00_b432(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02800_b432) {
                g->tex88 = g->tex[0];
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm5;
                g->c.h[1] += 15;
                g->c.h[2] = 0x1F;
                g->c.h[3] = 1;
                func_001F5F90(func_001F53A0(), &buf);
                g->px = 0.0f;
                g->py = 0.0f;
                g->pz = 0.0f;
                g->hBE = 2;
                b432_01E04280(g, &g->fx[k], &g->row[g->fx[k].h50], 0);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02DE0_b432) {
                g->hB8 = 36;
                func_01E00F00_b432(g, &g->fx[k], 0x20, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02FA0_b432) {
                g->tex88 = g->tex[1];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm6;
                g->hBE = g->fx[k].h52;
                func_01E01260_b432((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos);
            }
        }
    }
    if (m) {
        b432_01E04C70(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 190) {
        return 1;
    }
    if (g->frame == 355) {
        return 4;
    }
    if (g->frame == 335) {
        return 2;
    }
    if (g->frame > 200 && g->frame < 330) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b432:01E04130, 82 insns: take a free effect slot (0x96 of 0x70 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0x7EC4, attach it to the scene position (0x250) and copy it, 0x50 and 0x52 from 0x7F22, store the two
   arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b432_01E04130;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b432_01E04130 slots[0x96];
    u8 pad4440[0x7EC4 - 0x4440];
    u8 rgba[4];
    u8 pad7EC8[0x5A];
    s16 f7F22;
} Scene_b432_01E04130;

static s32 func_01E04130_b432(Scene_b432_01E04130 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b432_01E04130 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->pos[0] = g->pos[0];
        s->pos[1] = g->pos[1];
        s->pos[2] = g->pos[2];
        s->f50 = g->f7F22;
        s->f52 = g->f7F22;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b432:01E04280 (B432PAINT_RAIN30), 633 insns, 2 copies: b411:01E036C0's beam along the module spline from
   point 0 without the flags: one step of 1.5 (clamped to 1) per segment, alpha down by col0.a/n, width down by
   w0/(2n), one quad offset in +y/-y (the k == 1 arm of the one-pass loop is dead) */

typedef struct {
    f32 x, y, z, w;
} Vec_b432_01E04280;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b432_01E04280;

typedef struct {
    u8 r, g, b, a;
} Col_b432_01E04280;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b432_01E04280;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b432_01E04280 c;
        u64 st;
        Xyz_b432_01E04280 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b432_01E04280;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b432_01E04280;

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
    Col_b432_01E04280 col0;
    Col_b432_01E04280 col1;
} Beam_b432_01E04280;

static inline Vec_b432_01E04280 spline_b847_01E00E60(Vec_b432_01E04280 *p, s32 type, f32 t) {
    Vec_b432_01E04280 r;
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

static void func_01E04280_b432(Ctx_b432_01E04280 *c, Beam_b432_01E04280 *an, Vec_b432_01E04280 *pts __attribute__((aligned(16)))) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b432_01E04280 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b432_01E04280 ab[2];
    Vec_b432_01E04280 ctrl[4];
    Vec_b432_01E04280 prev;
    Vec_b432_01E04280 q[4];
    Vec_b432_01E04280 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b432_01E04280 pkt __attribute__((aligned(8)));
    Col_b432_01E04280 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b432_01E04280 *p;
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
    for (i = 0; i < n - 1; i++) {
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
            x = col.a - (s16)(an->col0.a / n);
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (2.0f * n);
            for (k = 0; k < 1; k++) {
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
                if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                    func_002075F0(p, target, (u32)depth[0]);
                }
            }
        }
    }
}

/* shape b432:01E04C70, 73 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x7ED8, ot at
   0x7ED4), texture from func_001F53A0, then every used slot (0x96 of 0x70 bytes at 0x2A0) whose
   callback is b432:01E03680 is drawn by it; close the ot if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b432_01E04C70;

typedef struct {
    u8 pad0[0x44];
    void (*cb)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b432_01E04C70;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b432_01E04C70 slots[0x96];
    u8 pad4440[0x3A94];
    s32 ot;
    Pkt_b432_01E04C70 *pk;
} Scene_b432_01E04C70;

static void func_01E04C70_b432(Scene_b432_01E04C70 *g) {
    extern void b432_01E03680(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b432_01E04C70 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b432_01E03680) {
                b432_01E03680(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), 0);
    }
}
