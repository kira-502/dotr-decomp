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

static void func_01E00080_b593(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b593(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b593((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b593((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
} Vec_b094_01E00920;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b094_01E00920;

typedef struct {
    u8 pad00[0x20];
    Vec_b094_01E00920 rotation;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b094_01E00920;

static void func_01E00ED0_b593(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b094_01E00920 c;
    Vec_b094_01E00920 quad[4];
    Vec_b094_01E00920 pos;
    Vec_b094_01E00920 scale;
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
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
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

static void func_01E01230_b593(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b593 in the
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

static void func_01E01630_b593(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b593((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b593:01E018F0, 353 insns: the module's spawn step for two points: B follows joint 0x4618 (camera 2) from tick
   81 to 119 while the scene tint's alpha drops 6 a tick (91..109, cleared at 111); from 120 B glides over 20 ticks
   (z to 0 in 30 steps, y toward 50 in 20); A follows joint 0x4608 2 higher from 190 to 254, then glides (z over 20,
   y away from 50 over 50 steps) until 281; both points spawn b593:01E01E80 + b593:01E02250 (with b593:01E025B0 on
   their first tick), B three b593:01E02BD0 on 81..99; A ends with b593:01E02480/b593:01E020C0 (281..295),
   b593:01E028B0 (281), the tint back at 289 and five b593:01E029F0 at 291 */

typedef struct {
    f32 x, y, z, w;
} V4_b593_01E018F0;

typedef struct {
    u8 pad0[0x250];
    V4_b593_01E018F0 p;
    u8 pad260[0x4470 - 0x260];
    V4_b593_01E018F0 a;
    V4_b593_01E018F0 b;
    u8 pad4490[0x4510 - 0x4490];
    V4_b593_01E018F0 va;
    V4_b593_01E018F0 vb;
    u8 pad4530[0x45DC - 0x4530];
    u8 tint[4];
    u8 pad45E0[0x4608 - 0x45E0];
    s16 ja;
    u8 pad460A[0x4618 - 0x460A];
    s16 jb;
    u8 pad461A[0x4636 - 0x461A];
    s16 kind;
    u8 pad4638[6];
    s16 t;
} Scene_b593_01E018F0;

static s32 func_01E01E80_b593();
static s32 func_01E020C0_b593();
static s32 func_01E02250_b593();
static s32 func_01E02480_b593();
static s32 func_01E025B0_b593();
static s32 func_01E028B0_b593();
static s32 func_01E029F0_b593();
static s32 func_01E02BD0_b593();
static s32 func_01E03870_b593();

static void func_01E018F0_b593(Scene_b593_01E018F0 *s) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    s16 i;

    s->t++;
    if (s->t > 0x50 && s->t <= 0x77) {
        func_001F5620(func_001F5380(), s->jb, &s->b);
        func_001F6490(func_001F5380(), s->tint);
        if (s->t > 0x5A && s->t <= 0x6D) {
            s->tint[3] -= 6;
        }
        if (s->t == 0x6F) {
            s->tint[3] = 0;
        }
        func_001F63E0(func_001F5380(), s->tint);
    }
    if (s->t >= 0x78) {
        if (s->t == 0x78) {
            s->vb.z = -s->b.z / 30.0f;
        }
        if (s->t == 0x78) {
            s->vb.y = (50.0f - s->b.y) / 20.0f;
        }
        if (s->t < 0x8D) {
            s->b.z += s->vb.z;
        }
        if (s->t < 0x8D) {
            s->b.y += s->vb.y;
        }
    }
    if (s->t > 0xBD && s->t <= 0xFE) {
        func_001F5620(func_001F53A0(), s->ja, &s->a);
        s->a.y += 2.0f;
    }
    if (s->t >= 0xFF) {
        if (s->t == 0xFF) {
            s->va.z = -s->a.z / 20.0f;
        }
        if (s->t == 0xFF) {
            s->va.y = -(50.0f - s->a.y) / 50.0f;
        }
        if (s->t < 0x11A) {
            s->a.z += s->va.z;
        }
        if (s->t < 0x11A) {
            s->a.y -= s->va.y;
        }
    }
    if (s->t > 0xBD && s->t <= 0x11E) {
        s->kind = 0;
        if (s->t == 0xBE) {
            func_01E03870_b593(s, func_01E025B0_b593, 0);
        }
        func_01E03870_b593(s, func_01E01E80_b593, 0);
        s->p = s->a;
        func_01E03870_b593(s, func_01E02250_b593, 0);
    }
    if (s->t > 0x50 && s->t <= 0x11E) {
        s->kind = 1;
        if (s->t == 0x6F) {
            func_01E03870_b593(s, func_01E025B0_b593, 0);
        }
        func_01E03870_b593(s, func_01E01E80_b593, 0);
        s->p = s->b;
        func_01E03870_b593(s, func_01E02250_b593, 0);
    }
    if (s->t > 0x50 && s->t <= 0x63) {
        s->kind = 1;
        s->p = s->b;
        for (i = 0; i < 3; i++) {
            func_01E03870_b593(s, func_01E02BD0_b593, 0);
        }
    }
    if (s->t >= 0x119 && s->t < 0x128) {
        s->p = s->a;
        if (s->t % 2 == 0) {
            func_01E03870_b593(s, func_01E02480_b593, 0);
        }
        func_01E03870_b593(s, func_01E020C0_b593, 0);
    }
    if (s->t == 0x119) {
        s->p = s->a;
        func_01E03870_b593(s, func_01E028B0_b593, 0);
    }
    if (s->t == 0x121) {
        func_001F6490(func_001F5380(), s->tint);
        s->tint[3] = 0x80;
        func_001F63E0(func_001F5380(), s->tint);
    }
    if (s->t == 0x123) {
        s->p = s->a;
        for (i = 0; i < 5; i++) {
            func_01E03870_b593(s, func_01E029F0_b593, 0);
        }
    }
}

/* shape b593:01E01E80, 144 insns: spinning glow (size 20..99 growing 1, grey over a green or blue that flashes every tick): alpha up by 48 to 0x60 for 2 ticks, then down by 11; spins 0x4000 per tick */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b593_01E01E80;

static s32 func_01E01E80_b593(s32 arg0, Fx_b593_01E01E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 20.0f + func_0019A5C8() % 80;
        o->f4C = 0.0f;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x48, 0x48, 0x48);
            func_001076F0(o->col2, 0x40, 0x80, 0x40);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0x48, 0x48, 0x48);
            func_001076F0(o->col2, 0x40, 0x40, 0x80);
        }
        o->w = 15;
        o->h = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col2, 0x20, 0x80, 0x20);
        } else {
            func_001076F0(o->col2, 0x20, 0x40, 0x20);
        }
    }
    if (o->kind == 1) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col2, 0x20, 0x20, 0x80);
        } else {
            func_001076F0(o->col2, 0x20, 0x20, 0x40);
        }
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b593:01E020C0, 97 insns: a white spark (size 20, frame 5, random heading) spinning a random 16..45 a tick from 10..59 (old angle moved to +0xC), random 0..7 at +0xA, size 0..34, held 3..7 ticks at 0x80, then out by 8 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b593_01E020C0;

static s32 func_01E020C0_b593(s32 arg0, Obj_b593_01E020C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->kind = 5;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->hE = func_0019A5C8() % 30 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b593:01E02250, 139 insns: b279:01E02310 variant: size 5..12 growing by 1, red or blue by f52, start 10..39,
   alpha 0x80 during the fade-in, then down by 11 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 x;
    s32 y;
    s32 z;
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 dir;
    u8 pad5C[4];
    u8 col[4];
} Spark_b593_01E02250;

static s32 func_01E02250_b593(s32 arg0, Spark_b593_01E02250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 8 + 5;
        o->kind = func_0019A5C8() % 4;
        if (o->f52 == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
        }
        if (o->f52 == 1) {
            func_001076F0(o->col, 0x10, 0x10, 0xFF);
        }
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 30 + 10;
        o->dir = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->size += 1.0f;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b593:01E02480, 75 insns: b232:01E00AC0 family: a grey beam from 200 growing 20 a tick (tail flat), turning 0x100: alpha 0x80 for 8 ticks, then out by 14 and ends */

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
} Obj_b593_01E02480;

static s32 func_01E02480_b593(s32 arg0, Obj_b593_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        o->h50 = 0;
        o->h5A = 15;
        o->h5C = 15;
        o->f34 = 200.0f;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->w20 = 0x4000;
    }
    if (o->t < 8) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f34;
    o->f4C = 100.0f + o->f48;
    o->f4C = 0.0f;
    o->w24 += 0x100;
    o->t++;
    return 0;
}

/* shape b593:01E025B0, 191 insns: a pink (kind 0) or blue (kind 1) ring pair 45 x 45 sitting on its kind's scene point (ctx+0x4470), flickering green/dark green (kind 0) or blue/dark green (kind 1) every other tick with frame 1/0, random turn; both alphas up by 9 to 0xC0 before scene count 280 (ctx+0x463E), then down by 14 */

typedef struct {
    u8 pad0[0x4470];
    Vec4f pts[2];
    u8 pad4490[0x463E - 0x4490];
    s16 count;
} Ctx_b593_01E025B0;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x20];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    s16 frame;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b593_01E025B0;

static s32 func_01E025B0_b593(Ctx_b593_01E025B0 *g, Fx_b593_01E025B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 45;
        o->h = 45;
        o->frame = func_0019A5C8() % 8;
        if (o->kind == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
            func_001076F0(o->col2, 0xFF, 0x80, 0x80);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->f5C = 0;
    }
    if (g->count < 280) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 9;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 9;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        }
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x20, 0xFF, 0x20);
            func_001076F0(o->col2, 0x20, 0xFF, 0x20);
        } else {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
            func_001076F0(o->col2, 0x10, 0x80, 0x10);
        }
    }
    if (o->kind == 1) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x20, 0x20, 0xFF);
            func_001076F0(o->col2, 0x20, 0x20, 0xFF);
        } else {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
            func_001076F0(o->col2, 0x10, 0x80, 0x10);
        }
    }
    if (o->tick % 2 == 1) {
        o->frame = 1;
    } else {
        o->frame = 0;
    }
    o->f5A = func_0019A5C8() % 360;
    o->pos = g->pts[o->kind];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b593:01E028B0, 80 insns: a white flickering spinning flash (b550:01E02F50 shape): alpha up by 0x60 to 0xC0 for 14 frames; teal flicker */

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
} Obj_b593_01E028B0;

static s32 func_01E028B0_b593(void *arg0, Obj_b593_01E028B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 300.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x40, 0x80, 0x80);
        o->w2 = 0xF;
        o->h2 = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xE) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x20, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0x20, 0x40, 0x40);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b593:01E029F0, 120 insns, 1 copy (B593_OBJ_MOVE_9_): a grey puff, size 15..24 growing 1 a tick, random spot and turn, rising 5..14 a tick; fades by 11 after 10..17 frames */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 x;
    s32 y;
    s32 z;
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 tick;
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b593_01E029F0;

static s32 func_01E029F0_b593(s32 arg0, Obj_b593_01E029F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 10 + 15;
        o->h56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->h50 = func_0019A5C8() % 30 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 10 + 5;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 8 + 10;
        o->state = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 0xB;
    } else {
        o->state = 0;
    }
    o->size += 1.0f;
    o->h50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b593:01E02BD0, 142 insns: b593:01E02250's spark, size 15..34, red or blue-white, height 50..249 falling 15..34 a tick while above 0 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 delay;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 x;
    s32 y;
    s32 z;
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 dir;
    u8 pad5C[4];
    u8 col[4];
} Spark_b593_01E02BD0;

static s32 func_01E02BD0_b593(s32 arg0, Spark_b593_01E02BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 20 + 15;
        o->kind = func_0019A5C8() % 4;
        if (o->f52 == 0) {
            func_001076F0(o->col, 0xFF, 0x80, 0x80);
        }
        if (o->f52 == 1) {
            func_001076F0(o->col, 0x40, 0x40, 0xFF);
        }
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f50 = func_0019A5C8() % 200 + 50;
        o->dir = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 15;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->size += 1.0f;
    if (o->f50 > 0) {
        o->f50 -= o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b593:01E02E10, 174 insns: b183:01E01F30 with the packet at ctx+0x45EC and the tracked point at ctx+0x4608 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b593_01E02E10;

typedef struct {
    f32 s, t;
    Xyz_b593_01E02E10 p;
} Tv_b593_01E02E10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b593_01E02E10 v[2];
} Tex_b593_01E02E10;

typedef struct {
    u8 pad[0x45EC];
    Tex_b593_01E02E10 *pk;
    u8 pad45F0[0x4608 - 0x45F0];
    s16 id;
} Game_b593_01E02E10;

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
} Fx_b593_01E02E10;

static s32 func_01E02E10_b593(Game_b593_01E02E10 *g, Fx_b593_01E02E10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;
    f32 v[4];

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0x78;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->id, v);
    func_001F5F90(func_001F53A0(), v);
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
    g->pk->v[1].t = (448.0f - 3.0f * fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    o->f8 += (s16)(func_0019A5C8() % 30 + 100);
    o->fA += (s16)(func_0019A5C8() % 30 + 100);
    if (o->tick != 0) {
        if (o->col[3] > 40) {
            o->col[3] -= 49;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b593:01E030D0 (b593), 486 insns, 1 copy: b593 scene manager in b611:01E024B0 form: setup (seven joints, one
   type-4 and three type-5 textures, jitter tables with 100..179 set to 0..3), step b593:01E018F0 and every slot
   except b593:01E02E10 (counting those), draw the eight effect kinds, call b593:01E039C0 if any were counted; scene
   code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0x8];
    s16 h50;
    u8 pad52[0x4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b593_01E030D0;

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
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b593_01E030D0 fx[150];
    u8 pad4440[0x30];
    Vec4f pt[20];
    s32 tex[3];
    u8 pad45BC[0x14];
    s32 count;
    u8 pad45D4[0xC];
    s32 ot;
    u8 pad45E4[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad4614[4];
    s16 cam;
    u8 pad461A[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b593_01E030D0;

static s32 func_01E030D0_b593(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b593_01E039C0();
    extern void func_01E018F0_b593();
    extern void func_01E00ED0_b593();
    extern void func_01E00920_b593();
    Scene_b593_01E030D0 *g = (Scene_b593_01E030D0 *)arg0;
    s16 m;
    s16 n;
    Vec4f p;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s32 i;
    s16 k;

    m = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x49B0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 350;
        g->jA = func_001F5560(func_001F53A0(), 0x6D, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
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
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    func_01E018F0_b593(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02E10_b593) {
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
            if (g->fx[k].fn == (s32 (*)())func_01E01E80_b593) {
                g->hB8 = 24;
                func_01E00ED0_b593(g, &g->fx[k], 0x21, &g->pt[g->fx[k].h50]);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E020C0_b593) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hB0 = 1;
                func_01E00920_b593(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02250_b593) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b593(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02480_b593) {
                g->tex88 = g->tex[1];
                g->c.h[0] = 0;
                g->c.h[1] = 0;
                g->c.h[2] = 0x1F;
                g->c.h[3] = 0x7F;
                g->hBE = 0;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 24;
                func_01E01230_b593((Obj_b016_01E014F0 *)g, (Cam_b016_01E014F0 *)&g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E025B0_b593) {
                g->tex88 = g->tex[2];
                g->c.h[0] = g->fx[k].h56 << 6;
                g->c.h[1] = 0;
                g->c.h[2] = 0x3F;
                g->c.h[3] = 0x3F;
                g->hBE = func_0019A5C8() % 5;
                p.x = g->fx[k].pos.x;
                p.y = g->fx[k].pos.y;
                p.z = g->fx[k].pos.z;
                func_01E01630_b593((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E028B0_b593) {
                g->hB8 = 24;
                func_01E00ED0_b593(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E029F0_b593) {
                g->tex88 = g->tex[0];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->hB8 = 7;
                g->hB0 = 0;
                func_01E00920_b593(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02BD0_b593) {
                g->tex88 = g->tex[0];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm4;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b593(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (m) {
        b593_01E039C0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 75) {
        return 1;
    }
    if (g->frame == 335) {
        return 4;
    }
    if (g->frame == 325) {
        return 2;
    }
    if (g->frame > 85 && g->frame < 320) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b593:01E03870, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, the scene value twice and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 used;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Obj_b593_01E03870;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b593_01E03870 slot[150];
    u8 padEnd[0x45d4 - 0x2a0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad45D8[0x5E];
    s16 val;
} Ctx_b593_01E03870;

static s32 func_01E03870_b593(Ctx_b593_01E03870 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b593_01E03870 *s;

    s = NULL;
    for (i = 0; i < 150; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 150;
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
        s->h50 = ctx->val;
        s->h52 = ctx->val;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b593:01E039C0, 73 insns: the module's draw pass (b016:01E03880 shape): opens a sprite packet on the stack, then
   runs every live slot (150 of 0x70 bytes) whose handler is shape b593:01E02E10 through it; queues the batch only if any
   slot was live. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b593_01E039C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b593_01E039C0 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b593_01E039C0;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b593_01E039C0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b593_01E039C0 slot[150];
    u8 padEnd[0x45E8 - 0x2A0 - 150 * 0x70];
    s32 ctx;
    Pkt_b593_01E039C0 *pkt;
} Scene_b593_01E039C0;

static void func_01E039C0_b593(Scene_b593_01E039C0 *s) {
    extern void b593_01E02E10(Scene_b593_01E039C0 *, Slot_b593_01E039C0 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b593_01E039C0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    s->pkt = &pkt;
    n = 0;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active != 0) {
            n++;
            if (s->slot[i].fn == (void *)b593_01E02E10) {
                b593_01E02E10(s, &s->slot[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(s->ctx, func_00207500(), 0);
    }
}
