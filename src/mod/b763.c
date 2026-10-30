#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b763(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b763(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b763(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b763_01E00110();
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
    b763_01E00110(p, obj->f94, obj->fC0);
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

static void func_01E00F00_b763(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b763 in the
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

static void func_01E01260_b763(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b763((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01520_b763(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b763:01E01920, 161 insns: the b763 module's event step: counts ticks; from 96 to 154 spawns two b763:01E01BB0 (slots 0 and 4) at the first tracked point; from 180 to 230 alternates b763:01E02200 / b763:01E02400 at the second; at tick 1 reads the camera and spawns b763:01E031F0 and b763:01E032F0; at 153 spawns b763:01E02F10 and b763:01E03060; from 178, every fourth tick, places up to 30 points (ctx+0x7CB0) and spawns b763:01E02930 and b763:01E01EB0 there */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x7CB0 - 0x25C];
    Vec4f pts[30];
    f32 cam[4];
    u8 pad7EA0[0x7EEC - 0x7EA0];
    s16 id0;
    u8 pad7EEE[2];
    s16 id1;
    u8 pad7EF2[0x7F1A - 0x7EF2];
    s16 slot;
    s16 n;
    u8 pad7F1E[4];
    s16 timer;
} Ctx_b763_01E01920;

static void func_01E01920_b763(Ctx_b763_01E01920 *g) {
    extern s32 b763_01E01BB0(void);
    extern s32 b763_01E01EB0(void);
    extern s32 b763_01E02200(void);
    extern s32 b763_01E02400(void);
    extern s32 b763_01E02930(void);
    extern s32 b763_01E02F10(void);
    extern s32 b763_01E03060(void);
    extern s32 b763_01E031F0(void);
    extern s32 b763_01E032F0(void);
    extern void b763_01E03CB0(Ctx_b763_01E01920 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, f32 *);

    g->timer++;
    if (g->timer >= 96 && g->timer < 155) {
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        g->slot = 0;
        b763_01E03CB0(g, b763_01E01BB0, 0);
        func_001F5620(func_001F53A0(), g->id0, g->pos);
        g->slot = 4;
        b763_01E03CB0(g, b763_01E01BB0, 0);
    }
    if (g->timer >= 180 && g->timer < 231) {
        g->slot = 1;
        func_001F5620(func_001F53A0(), g->id1, g->pos);
        if (g->timer % 2 == 1) {
            b763_01E03CB0(g, b763_01E02200, 0);
        } else {
            b763_01E03CB0(g, b763_01E02400, 0);
        }
    }
    if (g->timer == 1) {
        func_001F5F90(func_001F5380(), g->cam);
    }
    if (g->timer == 1) {
        b763_01E03CB0(g, b763_01E031F0, 0);
    }
    if (g->timer == 1) {
        b763_01E03CB0(g, b763_01E032F0, 0);
    }
    if (g->timer == 153) {
        b763_01E03CB0(g, b763_01E02F10, 0);
    }
    if (g->timer == 153) {
        b763_01E03CB0(g, b763_01E03060, 0);
    }
    if (g->timer >= 178) {
        if (g->timer % 4 == 1) {
            if (g->n < 30) {
                g->slot = g->n;
                func_001F5620(func_001F53A0(), g->id1, &g->pts[g->slot]);
                b763_01E03CB0(g, b763_01E02930, 0);
                b763_01E03CB0(g, b763_01E01EB0, 0);
                g->n++;
            }
        }
    }
}

/* shape b763:01E01BB0, 191 insns: a grey (0x80) mote, size 4, frame 0..6, angles 0..359, side 0..7, keeps the old 0x50 in 0xC, life 50..149, speed 10..29, 0x8 0..34, hold 3..7; flies to its slot's tracked point (ctx+0x7EEE) over 40 ticks from a spot -10..9 off; alpha up by 0x20 to 0x80 during the hold, then down by 8; turns 2 a tick */

typedef struct {
    u8 pad0[0x7EEE];
    s16 ids[1];
} Ctx_b763_01E01BB0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 side;
    s16 fC;
    s16 speed;
    f32 pos[3];
    u8 pad1C[0x14];
    f32 vel[3];
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 slot;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b763_01E01BB0;

static s32 func_01E01BB0_b763(Ctx_b763_01E01BB0 *g, Fx_b763_01E01BB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];

    if (o->mode == 1) {
        o->f48 = 4.0f;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        o->side = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 100 + 50;
        o->speed = func_0019A5C8() % 20 + 10;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        func_001F5620(func_001F53A0(), g->ids[o->slot], v);
        o->vel[0] = (v[0] - o->pos[0]) / 40.0f;
        o->vel[1] = (v[1] - o->pos[1]) / 40.0f;
        o->vel[2] = (v[2] - o->pos[2]) / 40.0f;
        o->pos[0] += func_0019A5C8() % 20 - 10;
        o->pos[1] += func_0019A5C8() % 20 - 10;
        o->pos[2] += func_0019A5C8() % 20 - 10;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    o->f5C += 2;
    o->tick++;
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

static s32 func_01E01EB0_b763(World_b432_01E01D80 *w, Blink_b432_01E01D80 *o) {
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

static s32 func_01E02050_b763(s32 arg0, Fx_b432_01E01F20 *o) {
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

/* shape b763:01E02200, 125 insns: b354:01E020F0's growing puff, kind 0 reddish (0xC0, 0x80, 0x80), growth 20..24.9 a tick */

typedef struct {
    u8 pad00[0x20];
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
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b763_01E02200;

static s32 func_01E02200_b763(void *arg0, Obj_b763_01E02200 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 80.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->col, 0xC0, 0x80, 0x80);
            func_001076F0(o->col2, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->col, 0xA0, 0xA0, 0xFF);
            func_001076F0(o->col2, 0x50, 0x50, 0x50);
        }
        o->h5A = 30;
        o->h5C = 30;
        o->f34 = func_0019A5C8() % 50 + 200;
        o->f34 /= 10.0f;
        o->state = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = 0.2f * o->f48;
    o->t++;
    return 0;
}

/* shape b763:01E02400, 127 insns: b432:01E022D0 with a dark blue second colour (8/8/0x18) for kind 1 */

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
} Fx_b763_01E02400;

static s32 func_01E02400_b763(s32 arg0, Fx_b763_01E02400 *o) {
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
            func_001076F0(o->col2, 8, 8, 0x18);
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

/* shape b763:01E02600, 128 insns: a glow in two kinds: kind 0 red/white, size 220, 14 ticks then down by 9; kind 1 blue/grey with a random turn, 8 ticks then down by 15, growing 25 per tick with f4C = 0.6 of it; outer alpha up by 0x60 to 0xC0 while alive */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b763_01E02600;

static s32 func_01E02600_b763(s32 arg0, Fx_b763_01E02600 *o) {
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
            func_001076F0(o->col2, 0x20, 0x20, 0x80);
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
        }
        o->f52 = 0;
        o->w = 10;
        o->h = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->kind == 0) {
            if (o->col2[3] > 10) {
                o->col2[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 16) {
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

/* shape b763:01E02800, 75 insns: b764:01E02A60 family ring (white/blue, height 70 growing 1 a tick up to 150): in by 64 up to 0xC0 for 7 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b763_01E02800;

static s32 func_01E02800_b763(s32 arg0, Obj_b763_01E02800 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f4C = 70.0f;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 7) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    if (o->t != 0) {
        if (o->f4C < 150.0f) {
            o->f4C += 1.0f;
        }
    }
    o->t++;
    return 0;
}

/* shape b763:01E02930 (B763_OBJ_MOVE_10_), 374 insns, 1 copy: b432:01E02800 homing streak:
   30-point trail at ctx+0x4470 on its point ctx+0x7CB0, 48-tick jittered step toward ctx+0x7E90, wobble on the sine
   table ctx+0x8124; marks 0x7F1A and bursts b763:01E02600 + b763:01E02050 at the trail head until 50, b763:01E02800
   at 48 */

typedef struct {
    Vec4f v[30];
} Trail_b763_01E02930;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4470 - 0x260];
    Trail_b763_01E02930 trail[16];
    u8 pad6270[0x7CB0 - 0x6270];
    Vec4f pts[16];
    u8 pad7DB0[0x7E90 - 0x7DB0];
    f32 tx, ty, tz;
    u8 pad7E9C[0x7F1A - 0x7E9C];
    s16 flag;
    u8 pad7F1C[0x8124 - 0x7F1C];
    u8 sin[4];
} Ctx_b763_01E02930;

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
} Streak_b763_01E02930;

static s32 func_01E02930_b763(Ctx_b763_01E02930 *g, Streak_b763_01E02930 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(s32, s32, s32);
    extern void func_01E00080_b763();
    extern void b763_01E03CB0();
    extern s32 func_01E02050_b763();
    extern s32 func_01E02600_b763();
    extern s32 func_01E02800_b763();
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
        func_01E00080_b763(&g->trail[o->idx].v[29], 30, 0, &v);
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
            b763_01E03CB0(g, func_01E02600_b763, 0);
            b763_01E03CB0(g, func_01E02050_b763, 0);
        }
        if (o->t == 48) {
            g->pos.x = g->trail[o->idx].v[0].x;
            g->pos.y = g->trail[o->idx].v[0].y;
            g->pos.z = g->trail[o->idx].v[0].z;
            b763_01E03CB0(g, func_01E02800_b763, 0);
        }
    }
    o->t++;
    return 0;
}

/* shape b763:01E02F10, 83 insns: a blue-grey spinning flash on the model joint (b432:01E026D0 shape): f4C 50 growing by 1 up
   to 150; second alpha up by 19 to 0xC0 for 200 frames, then down by 15 until it ends */

typedef struct {
    u8 pad0[0x7EF0];
    s16 joint;
} Game_b763_01E02F10;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
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
} Obj_b763_01E02F10;

static s32 func_01E02F10_b763(Game_b763_01E02F10 *g, Obj_b763_01E02F10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f4C = 50.0f;
        func_001076F0(o->c1, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c0, 0x80, 0x80, 0xFF);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
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
    if (o->t != 0) {
        if (o->f4C < 150.0f) {
            o->f4C += 1.0f;
        }
    }
    o->t++;
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    return 0;
}

/* shape b763:01E03060, 100 insns: a white light on a model joint (b432:01E031D0 shape, joint at 0x7EF0): colour 128/4/4/4,
   range 123; power up by 0.1 to 1 until frame 210, then down by 0.3 until it ends; ends when the scene state is 1 */

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
    u8 pad7EC4[0x2C];
    s16 joint;
} Scene_b763_01E03060;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x34];
    s16 down;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 live;
} Obj_b763_01E03060;

static s32 func_01E03060_b763(Scene_b763_01E03060 *g, Obj_b763_01E03060 *o) {
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

static s32 func_01E031F0_b763(Game_b432_01E03360 *g, Fx_b432_01E03360 *o) {
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

/* shape b763:01E032F0, 134 insns: b432:01E03460 in 0x80/0x80/0x90, fading in while the scene timer is past 30 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b763_01E032F0;

typedef struct {
    f32 s, t;
    Xyz_b763_01E032F0 p;
} Tv_b763_01E032F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b763_01E032F0 v[2];
    u8 tail[0x20];
} Tex_b763_01E032F0;

typedef struct {
    u8 pad0[0x7EC0];
    s32 timer;
} Ctx_b763_01E032F0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b763_01E032F0;

static s32 func_01E032F0_b763(Ctx_b763_01E032F0 *g, Fx_b763_01E032F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b763_01E032F0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x90);
        o->mode = 2;
    }
    ((Tex_b763_01E032F0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b763_01E032F0 *)(s32)&pk)->size = 5;
    ((Tex_b763_01E032F0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b763_01E032F0 *)(s32)&pk)->pad4 = 0;
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
    if (g->timer > 30) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b763", func_01E03510_b763);

/* shape b763:01E03CB0, 82 insns (b020:01E02D90 shape): takes the first free of 150 effect slots (0x70 bytes, b089:01E030B0 shape), colours it from
   the context, places it at the context's position (copying it in), stores two frames and both arguments */

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
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b763_01E03CB0;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b763_01E03CB0 slots[0x96];
    u8 pad[0x7EC4 - 0x2A0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 pad7EC8[0x52];
    s16 f7F1A;
} Ctx_b763_01E03CB0;

static s32 func_01E03CB0_b763(Ctx_b763_01E03CB0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b763_01E03CB0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x70);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c60[3] = ctx->rgba[3];
        func_001076F0(s->c64, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c64[3] = ctx->rgba[3];
        func_00106AB0(s, ctx->pos, 0);
        s->pos[0] = ctx->pos[0];
        s->pos[1] = ctx->pos[1];
        s->pos[2] = ctx->pos[2];
        s->f50 = ctx->f7F1A;
        s->f52 = ctx->f7F1A;
        s->a2 = arg2;
        s->a1 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b763", func_01E03E00_b763);
