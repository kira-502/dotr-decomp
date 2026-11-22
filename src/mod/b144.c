#include "common.h"

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

static void func_01E00080_b144(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E00920_b144(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

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
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b144((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00080_b144((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
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

static void func_01E00ED0_b144(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E01230_b144(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b144 in the
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

static void func_01E01630_b144(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b144((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E018F0_b144(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b144:01E01C60, 244 insns (B144_W_S): the b144 module's event step: counts ticks; below 91 spawns
   b144:01E02C40 and b144:01E02F30, puts the point on the tracked joint (ctx+0x5A9E) and spawns b144:01E03040; at 19
   two b144:01E02E30 (turns 0 and 90); the point goes to the camera at height 33; every other tick from 110 to 133
   b144:01E02030 and b144:01E022A0; from 118 to 143 every third tick (and at 118) b144:01E02630, and at 118 eight
   b144:01E02430 and a ring of 20 b144:01E02750/b144:01E02930 pairs 18 degrees apart; from 118 on one b144:01E02430 and
   a pair at a random angle each tick; at 43 the point goes back to the joint for b144:01E03210 and six b144:01E03300;
   at 118 b144:01E02B50 and b144:01E034D0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x5A9E - 0x260];
    s16 id;
    u8 pad5AA0[0x5ABE - 0x5AA0];
    s16 turn;
    u8 pad5AC0[0x5ACA - 0x5AC0];
    s16 ang;
    u8 pad5ACC[0x5AD2 - 0x5ACC];
    s16 timer;
} Ctx_b144_01E01C60;

static void func_01E01C60_b144(Ctx_b144_01E01C60 *g) {
    extern s32 b144_01E02030(void);
    extern s32 b144_01E022A0(void);
    extern s32 b144_01E02430(void);
    extern s32 b144_01E02630(void);
    extern s32 b144_01E02750(void);
    extern s32 b144_01E02930(void);
    extern s32 b144_01E02B50(void);
    extern s32 b144_01E02C40(void);
    extern s32 b144_01E02E30(void);
    extern s32 b144_01E02F30(void);
    extern s32 b144_01E03040(void);
    extern s32 b144_01E03210(void);
    extern s32 b144_01E03300(void);
    extern s32 b144_01E034D0(void);
    extern void b144_01E04140(Ctx_b144_01E01C60 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;
    s16 a;

    g->timer++;
    if (g->timer < 91) {
        b144_01E04140(g, b144_01E02C40, 0);
        b144_01E04140(g, b144_01E02F30, 0);
        func_001F5620(func_001F53A0(), g->id, &g->pos);
        b144_01E04140(g, b144_01E03040, 0);
    }
    if (g->timer == 19) {
        g->turn = 0;
        b144_01E04140(g, b144_01E02E30, 0);
        g->turn = 90;
        b144_01E04140(g, b144_01E02E30, 0);
    }
    func_001F5F90(func_001F5380(), &g->pos);
    g->pos.y = 33.0f;
    if (g->timer >= 110 && g->timer < 134) {
        if (g->timer % 2 == 1) {
            b144_01E04140(g, b144_01E02030, 0);
            b144_01E04140(g, b144_01E022A0, 0);
        }
    }
    if (g->timer >= 118 && g->timer < 144) {
        if (g->timer % 3 == 1 || g->timer == 118) {
            b144_01E04140(g, b144_01E02630, 0);
        }
        if (g->timer == 118) {
            for (i = 0; i < 8; i++) {
                b144_01E04140(g, b144_01E02430, 0);
            }
            for (i = 0, a = 0; i < 20; i++) {
                g->ang = a;
                b144_01E04140(g, b144_01E02750, 0);
                b144_01E04140(g, b144_01E02930, 0);
                a += 18;
            }
        }
        if (g->timer >= 118) {
            b144_01E04140(g, b144_01E02430, 0);
            g->ang = func_0019A5C8() % 360;
            b144_01E04140(g, b144_01E02750, 0);
            b144_01E04140(g, b144_01E02930, 0);
        }
    }
    if (g->timer == 43) {
        func_001F5620(func_001F53A0(), g->id, &g->pos);
        b144_01E04140(g, b144_01E03210, 0);
        b144_01E04140(g, b144_01E03300, 0);
        b144_01E04140(g, b144_01E03300, 0);
        b144_01E04140(g, b144_01E03300, 0);
        b144_01E04140(g, b144_01E03300, 0);
        b144_01E04140(g, b144_01E03300, 0);
        b144_01E04140(g, b144_01E03300, 0);
    }
    if (g->timer == 118) {
        b144_01E04140(g, b144_01E02B50, 0);
    }
    if (g->timer == 118) {
        b144_01E04140(g, b144_01E034D0, 0);
    }
}

/* shape b144:01E02030, 154 insns: a red ember of two kinds: kind 0 size 2..6, height 50..149 rising 5..24; kind 1 size
   6..10, height 10..39 rising 10..12; frame 0..3, colour 0xC0/0x70/0x70, a random spin and angle, frame 1..8, life 2..4;
   alpha 0x60 for its life, then down by 11 until it ends; it rises by its speed */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 rise;
    u8 pad10[0x14];
    s32 spin;
    u8 pad28[0x20];
    f32 size;
    u8 pad4C[4];
    s16 h;
    s16 kind;
    s16 t;
    s16 frame;
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Obj_b144_01E02030;

static s32 func_01E02030_b144(void *g, Obj_b144_01E02030 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->size = func_0019A5C8() % 5 + 2;
        }
        if (o->kind == 1) {
            o->size = func_0019A5C8() % 5 + 6;
        }
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0x70, 0x70);
        o->spin = func_0019A5C8() % 0xFFFF;
        if (o->kind == 0) {
            o->h = func_0019A5C8() % 100 + 50;
            o->rise = func_0019A5C8() % 20 + 5;
        }
        if (o->kind == 1) {
            o->h = func_0019A5C8() % 30 + 10;
            o->rise = func_0019A5C8() % 3 + 10;
        }
        o->ang = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->t < o->life) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->h += o->rise;
    o->t++;
    return 0;
}

/* shape b144:01E022A0, 97 insns: a red-white swirling column: width 10 growing by 6 to 150, height 60 growing by 40, rise 2 growing
   by a random 5..39, random y turn going 0x200 a frame; second alpha up by 42 for 7 frames, then down by 11 until it ends */

typedef struct {
    u8 pad0[0xA];
    s16 speed;
    u8 padC[0x18];
    s32 rot1;
    u8 pad28[0xC];
    f32 rise;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b144_01E022A0;

static s32 func_01E022A0_b144(void *arg0, Obj_b144_01E022A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 10.0f;
        o->f4C = 60.0f;
        o->rise = 2.0f;
        o->speed = func_0019A5C8() % 35 + 5;
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->h5A = 0xF;
        o->h5C = 2;
        o->rot1 = func_0019A5C8() % 65535;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 7) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else if (o->c1[3] > 0xC) {
        o->c1[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->rot1 += 0x200;
    if (o->f48 < 150.0f) {
        o->f48 += 6.0f;
    }
    o->f4C += 40.0f;
    o->rise += o->speed;
    o->t++;
    return 0;
}

/* shape b144:01E02430, 127 insns: b747:01E02500 family white spark (f48 25..44 growing 1, frame 0..3, random turn, f50 10..29 growing 60..109 per tick, angle 0..359, f8 1..8): alpha 0x60 for 4..8 ticks, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b144_01E02430;

static s32 func_01E02430_b144(s32 arg0, Fx_b144_01E02430 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 25;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 20 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 50 + 60;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 5 + 4;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f50 += o->speed;
    o->f48 += 1.0f;
    o->tick++;
    return 0;
}

/* shape b144:01E02630, 72 insns: a white-grey rising flash (b363:01E02940 family): f48 200 with f4C 58 below, rising by
   f34 = 600 / 10 a frame with f4C 250 below; full alpha for 8 frames, then down by 14 until it ends; y turns 0x100 */

typedef struct {
    u8 pad0[0x24];
    s32 rot1;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b144_01E02630;

static s32 func_01E02630_b144(void *arg0, Obj_b144_01E02630 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x30, 0x30, 0x30);
        o->h50 = 0;
        o->w = 0xF;
        o->h = 0xF;
        o->f34 = 600.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 8) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 250.0f;
    o->rot1 += 0x100;
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0x5DD4];
    u8 tab[1];
} Mgr_b144_01E02750;

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
    f32 f30;
    u8 pad34[4];
    f32 f38;
    u8 pad3C[0x14];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
    u8 c64[4];
} Obj_b144_01E02750;

static s32 func_01E02750_b144(Mgr_b144_01E02750 *m, Obj_b144_01E02750 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 150;
        o->hA = 150;
        o->h56 = func_0019A5C8() % 8;
        o->f30 = 3.5f * func_00108030(m->tab, o->h50, 1);
        o->f38 = 3.5f * func_00108030(m->tab, o->h50, 0);
        func_001076F0(o->c60, 0xFF, 0x80, 0x80);
        func_001076F0(o->c64, 0xFF, 0x80, 0x80);
        o->h58 = 2;
        o->c64[3] = 0;
        o->h5C = 0;
    }
    if (o->h54 < 10) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x40;
        }
        if (o->c64[3] < 0xC0) {
            o->c64[3] += 0x40;
        }
    } else {
        if (o->c60[3] > 15) {
            o->c60[3] -= 14;
        } else {
            o->h58 = 0;
        }
        if (o->c60[3] > 15) {
            o->c60[3] -= 14;
        }
    }
    if (o->h54 != 0) {
        o->h8 += 15;
        o->hA += 15;
    }
    if (o->h54 != 0) {
        o->f10 += o->f30;
        o->f18 += o->f38;
        if (o->h5A < 90) {
            o->h5A += 5;
        }
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b144:01E02930, 135 insns: b749:01E029D0 family pink puff (size 100 growing 15 on both axes) that waits 6 ticks rising 4, then drifts 3.5 along h50 rising 1.5 and turning to 90; alphas up by 64 to 0xC0 for 12 ticks, then the inner one falls by 14 (twice) */

typedef struct {
    u8 pad0[0x5DD4];
    u8 tab[1];
} Mgr_b144_01E02930;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    u8 pad34[4];
    f32 f38;
    u8 pad3C[0x14];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
    u8 c64[4];
} Obj_b144_01E02930;

static s32 func_01E02930_b144(Mgr_b144_01E02930 *m, Obj_b144_01E02930 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 100;
        o->hA = 100;
        o->h56 = func_0019A5C8() % 8;
        o->f30 = 3.5f * func_00108030(m->tab, o->h50, 1);
        o->f38 = 3.5f * func_00108030(m->tab, o->h50, 0);
        func_001076F0(o->c60, 0xFF, 0x80, 0x80);
        func_001076F0(o->c64, 0xFF, 0x80, 0x80);
        o->h58 = 2;
        o->c64[3] = 0;
        o->h5C = 0;
    }
    if (o->h54 < 12) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x40;
        }
        if (o->c64[3] < 0xC0) {
            o->c64[3] += 0x40;
        }
    } else {
        if (o->c60[3] > 15) {
            o->c60[3] -= 14;
        } else {
            o->h58 = 0;
        }
        if (o->c60[3] > 15) {
            o->c60[3] -= 14;
        }
    }
    if (o->h54 != 0) {
        o->h8 += 15;
        o->hA += 15;
    }
    if (o->h54 > 5) {
        o->f10 += o->f30;
        o->f18 += o->f38;
        o->f14 += 1.5f;
        if (o->h5A < 90) {
            o->h5A += 5;
        }
    }
    if (o->h54 < 6) {
        o->f14 += 4.0f;
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b144:01E02B50, 60 insns: b764:01E02A60 family ring (white/pink, height 500, scale 2) held at turn 0x4000: in by 42 up to 0x80 for 17 ticks, then out by 7 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b144_01E02B50;

static s32 func_01E02B50_b144(s32 arg0, Obj_b144_01E02B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 500.0f;
        o->f34 = 2.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0xA0, 0xA0);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 17) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else if (o->col2[3] > 8) {
        o->col2[3] -= 7;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 = 0x4000;
    o->t++;
    return 0;
}

/* shape b144:01E02C40, 122 insns: on start a random size 1..4, frame 0..3, colour C0/70/70, random spin, speed 2..21
   with an extra 2..9, heading, h8 1..8 and life 2..4; full alpha while young, then fades by 11 and stops;
   the speed grows by its extra and the tick climbs */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 accel;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 speed;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b144_01E02C40;

static s32 func_01E02C40_b144(void *w, Obj_b144_01E02C40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 4 + 1;
        o->frame = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0xC0, 0x70, 0x70);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->speed = func_0019A5C8() % 20 + 2;
        o->accel = func_0019A5C8() % 8 + 2;
        o->ang = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->speed += o->accel;
    o->t++;
    return 0;
}

/* shape b144:01E02E30, 62 insns: a blue-white growing flash: set up once (f48 6, f30 1.5, size 5 growing by 4 a frame),
   fades in by 0x40 to 0x80 for 4 frames, then out by 9 until it ends */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 size;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b144_01E02E30;

static s32 func_01E02E30_b144(void *arg0, Obj_b144_01E02E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->c1, 0x40, 0x40, 0xC0);
        o->f30 = 1.5f;
        o->size = 5.0f;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->size += 4.0f;
    }
    o->t++;
    return 0;
}

/* shape b144:01E02F30, 67 insns: b144:01E02B50 twin: a grey/red ring of random height 10..59 (scale 2) held at turn 0x4000: in by 64 up to 0x80 for 2 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b144_01E02F30;

static s32 func_01E02F30_b144(s32 arg0, Obj_b144_01E02F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = func_0019A5C8() % 50 + 10;
        o->f34 = 2.0f;
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        func_001076F0(o->col, 0x40, 0x20, 0x20);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 2) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 = 0x4000;
    o->t++;
    return 0;
}

/* shape b144:01E03040, 116 insns: a white tumbling spark (b034:01E027A0 shape): size 8 + 4, sub-frame 4, random turn on all three
   axes, rising, angle, width 1..8, hold 4..8; alpha 0x60 until the hold, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b144_01E03040;

static s32 func_01E03040_b144(void *arg0, Obj_b144_01E03040 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 8 + 4;
        o->sub = 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->y = func_0019A5C8() % 100 + 0x32;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 10 + 5;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 5 + 4;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x60;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b144:01E03210, 60 insns: a pink-white spinning flash (b236:01E01B70 family): f4C 80, f34 2, size 15x15;
   second alpha up by 42 to 0x80 for 10 frames, then down by 7 until it ends; a random turn, then the x turn reset to a
   quarter */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b144_01E03210;

static s32 func_01E03210_b144(void *arg0, Obj_b144_01E03210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 0.0f;
        o->f4C = 80.0f;
        o->f34 = 2.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0xFF, 0xA0, 0xA0);
        o->w = 0xF;
        o->h = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xA) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x2A;
        }
    } else if (o->c1[3] > 8) {
        o->c1[3] -= 7;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] = 0x4000;
    o->t++;
    return 0;
}

/* shape b144:01E03300, 116 insns: a white tumbling spark (b034:01E027A0 shape): size 4 + 2, sub-frame 4, random turn on all three
   axes, rising, angle, width 1..8, hold 4..8; alpha 0x60 until the hold, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 y;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b144_01E03300;

static s32 func_01E03300_b144(void *arg0, Obj_b144_01E03300 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 4 + 2;
        o->sub = 4;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->y = func_0019A5C8() % 30 + 5;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 15 + 0xA;
        o->w = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 5 + 4;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x60;
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->y += o->step;
    o->t++;
    return 0;
}

/* shape b144:01E034D0, 153 insns, 2 copies: a full-screen zoom flash: draws one textured sprite over the whole screen, its
   texture window shrinking in by the zoom value; fades in over 10 frames while the zoom grows by 0.3 (to 100),
   then fades out while it shrinks back to 0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b144_01E034D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b144_01E034D0 p;
    } v[2];
    u8 tail[0x20];
} Pkt_b144_01E034D0;

typedef struct {
    u8 pad0[0x48];
    f32 zoom;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Flash_b144_01E034D0;

static s32 func_01E034D0_b144(void *arg0, Flash_b144_01E034D0 *o) {
    extern void func_002087A0(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b144_01E034D0 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->zoom = 1.0f;
        o->state = 2;
    }
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b144_01E034D0 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x7F;
    pkt.b = 0x7F;
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

/* shape b144:01E03740 (b144), 637 insns, 1 copy: b144 scene manager in b632:01E03BC0 form: setup (camera and three
   joints, textures (4,10..15), (4,0) and (5,0..2), turn from the camera angle, scale 0.1, s8 jitter tables: +-15 with
   100..179 rand%4, +-20 with 100..179 rand%40, then the second refilled +-15), step b144:01E01C60 and every slot (200
   of 0x70), draw the slots by handler (00920 jitter strips, 00ED0 glows, 01230/01630/018F0); scene code 1/4/2/6/8
   from the frame and timer; 00ED0 and 00920 called through no-prototype aliases */

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0x8];
    s16 h50;
    u8 pad52[0x4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b144_01E03740;

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
        s16 uv[8];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b144_01E03740 fx[200];
    u8 pad5A20[0x30];
    s32 tex2[3];
    u8 pad5A5C[0x14];
    s32 count;
    u8 pad5A74[8];
    s32 ot;
    u8 pad5A80[0x1C];
    s16 j[3];
    u8 pad5AA2[8];
    s16 cam;
    u8 pad5AAC[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    s8 jit3[0x100];
    u8 crd[0x16C];
} Scene_b144_01E03740;

static s32 func_01E03740_b144(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern void b144_01E01C60();
    extern void b144_01E00920();
    extern void b144_01E00ED0();
    Scene_b144_01E03740 *g = (Scene_b144_01E03740 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 rm7[4];
    s32 rm8[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x5F40);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0xBE;
        g->j[0] = func_001F5560(func_001F53A0(), 0xB, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x14, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[0] = func_00202BF0(4, 0);
        for (i = 0; i < 3; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s32)(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 100; k < 180; k++) {
            g->jit2[k] = func_0019A5C8() % 40;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    b144_01E01C60(g, 0);
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E02030_b144) {
                g->tex88 = g->tex[15];
                func_00106080(rm, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hB8 = 7;
                g->hB0 = 1;
                b144_01E00920(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E022A0_b144) {
                g->hB8 = 0x18;
                func_001F5620(func_001F53A0(), g->j[0], &v);
                b144_01E00ED0(g, &g->fx[k], 0x20, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02430_b144) {
                g->tex88 = g->tex2[0];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 7;
                g->hB0 = 0;
                b144_01E00920(g, &g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02630_b144) {
                g->tex88 = g->tex2[1];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x7F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0x18;
                g->hBE = 0;
                func_01E01230_b144((Obj_b016_01E014F0 *)g, (Cam_b016_01E014F0 *)&g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02750_b144) {
                g->tex88 = g->tex2[2];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01630_b144((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02930_b144) {
                g->tex88 = g->tex2[2];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01630_b144((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B50_b144) {
                g->hB8 = 0x18;
                b144_01E00ED0(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02C40_b144) {
                g->tex88 = g->tex[15];
                func_00106080(rm5, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->hB8 = 7;
                g->hB0 = 1;
                func_001F5620(func_001F53A0(), g->j[1], &g->fx[k].pos);
                b144_01E00920(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02E30_b144) {
                func_001F5620(func_001F53A0(), g->j[0], &v);
                g->tex88 = g->tex[15];
                func_00106080(rm6, 0x9A, 0, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                g->hBE = 0;
                v.w = 0.0f;
                func_01E018F0_b144((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02F30_b144) {
                g->hB8 = 0x18;
                func_001F5620(func_001F53A0(), g->j[1], &g->fx[k].pos);
                b144_01E00ED0(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03040_b144) {
                g->tex88 = g->tex2[0];
                func_00106080(rm7, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm7;
                g->hB8 = 4;
                g->hB0 = 0;
                b144_01E00920(g, &g->fx[k], 0x20, g->jit3);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03210_b144) {
                g->hB8 = 0x18;
                b144_01E00ED0(g, &g->fx[k], 0x20, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03300_b144) {
                g->tex88 = g->tex2[0];
                func_00106080(rm8, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm8;
                g->hB8 = 8;
                g->hB0 = 0;
                b144_01E00920(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x6E) {
        return 1;
    }
    if (g->frame == 0xAF) {
        return 4;
    }
    if (g->frame == 0x9B) {
        return 2;
    }
    if (g->frame > 0x78 && g->frame < 0x96) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b144:01E04140, 82 insns: c035:01E01150 family: take the first free effect slot of 200 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    u8 pad52[6];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b144_01E04140;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2A0 - 0x25C];
    Obj_b144_01E04140 slot[200];
    u8 padEnd[0x5a74 - 0x2A0 - 200 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padA[0x5abe - 0x5a74 - 4];
    s16 ang;
    u8 padB[0x5aca - 0x5abe - 2];
    s16 h30;
} Ctx_b144_01E04140;

static s32 func_01E04140_b144(Ctx_b144_01E04140 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b144_01E04140 *s;

    s = NULL;
    for (i = 0; i < 200; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 200;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, &ctx->x, 0);
        s->x = ctx->x;
        s->y = ctx->y;
        s->z = ctx->z;
        s->h5A = ctx->ang;
        s->h50 = ctx->h30;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}
