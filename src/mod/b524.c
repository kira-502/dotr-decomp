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

static void func_01E00080_b524(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b524(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b524((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b524((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b524 in the
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

static void func_01E00ED0_b524(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b524((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01190_b524(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

static void func_01E01590_b524(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b524:01E018F0, 142 insns: scene spawn step: t++; on odd frames 100..124 a numbered pair of handlers 0x1E01B30
   and 0x1E025A0 at the first joint, jittered -8..7; on odd frames 60..150 one 0x1E02170 at joint A at height 40;
   on frames 59..120 three 0x1E02710 a tick at joint B */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x5B90];
    s16 ja;
    s16 jb;
    u8 pad5DF4[0xC];
    s16 j0;
    u8 pad5E02[0xE4];
    s16 num;
    s16 ring;
    u8 pad5EEA[4];
    s16 t;
} Scene_b524_01E018F0;

static void func_01E018F0_b524(Scene_b524_01E018F0 *g) {
    extern void b524_01E01B30(void);
    extern void b524_01E02170(void);
    extern void b524_01E025A0(void);
    extern void b524_01E02710(void);
    extern void b524_01E034A0(void *, void *, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    g->t++;
    if (g->t >= 0x64 && g->t < 0x7D) {
        if (g->t % 2 == 1) {
            func_001F5620(func_001F5380(), g->j0, &g->pos);
            g->pos.x += func_0019A5C8() % 16 - 8;
            g->pos.y += func_0019A5C8() % 16 - 8;
            g->pos.z += func_0019A5C8() % 16 - 8;
            g->num = g->ring;
            b524_01E034A0(g, b524_01E01B30, 0);
            b524_01E034A0(g, b524_01E025A0, 0);
            g->ring++;
        }
    }
    if (g->t >= 0x3C) {
        if (g->t % 2 == 1 && g->t < 0x97) {
            func_001F5620(func_001F53A0(), g->ja, &g->pos);
            g->pos.y = 40.0f;
            g->num = 0;
            b524_01E034A0(g, b524_01E02170, 0);
        }
    }
    if (g->t >= 0x3B && g->t < 0x79) {
        func_001F5620(func_001F53A0(), g->jb, &g->pos);
        b524_01E034A0(g, b524_01E02710, 0);
        b524_01E034A0(g, b524_01E02710, 0);
        b524_01E034A0(g, b524_01E02710, 0);
    }
}

/* shape b524:01E01B30, 297 insns: a flying shard (B524_OBJ_MOVE_2_): set up once at size 20, a random frame 2..7,
   grey 0x80, a random direction (ctx+0x5A50 slot, x/z -50..49, y 0..39, all /15), speed 50, random turn and side;
   fades in by 10 before tick 80 then out by 9; frame cycles 0..2; grows to 30 every third tick; flies at its speed
   from its point, sparking b524:01E01FE0 on odd ticks; slows to 20, then after tick 60 to 0 and bursts
   (b524:01E023F0 + b524:01E02910) once it runs out; speed kept in ctx+0x5E10/0x5E74 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x5A50 - 0x260];
    Vec4f dir[0x3C];
    s16 spd[0x32];
    s16 spd2[0x32];
} Ctx_b524_01E01B30;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    s16 side;
    u8 padE[2];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 idx;
    s16 speed;
    s16 t;
    s16 frame;
    s16 state;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Shard_b524_01E01B30;

static s32 func_01E01B30_b524(Ctx_b524_01E01B30 *g, Shard_b524_01E01B30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_01E034A0_b524();
    extern s32 func_01E01FE0_b524();
    extern s32 func_01E023F0_b524();
    extern s32 func_01E02910_b524();
    f32 sp;

    if (o->state == 1) {
        o->w = 20;
        o->h = 20;
        o->f48 = 5.0f;
        o->frame = func_0019A5C8() % 6 + 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        g->dir[o->idx].x = func_0019A5C8() % 100 - 50;
        g->dir[o->idx].y = func_0019A5C8() % 40;
        g->dir[o->idx].z = func_0019A5C8() % 100 - 50;
        g->dir[o->idx].x /= 15.0f;
        g->dir[o->idx].y /= 15.0f;
        g->dir[o->idx].z /= 15.0f;
        o->state = 2;
        o->speed = 50;
        o->ang = func_0019A5C8() % 360;
        o->side = (func_0019A5C8() >> 4) % 2;
        if (o->side == 0) {
            o->side = 0;
        } else {
            o->side = 2;
        }
    }
    if (o->t < 80) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->state = 0;
        }
    }
    o->frame++;
    if (o->frame >= 3) {
        o->frame = 0;
    }
    if (o->t % 3 == 1) {
        if (o->w < 30) {
            o->w++;
        }
        if (o->h < 30) {
            o->h++;
        }
    }
    if (o->t != 0) {
        g->pos = o->pos;
        sp = o->speed;
        g->pos.x += g->dir[o->idx].x * sp;
        g->pos.y += g->dir[o->idx].y * sp;
        g->pos.z += g->dir[o->idx].z * sp;
        if (o->t % 2 == 1) {
            func_01E034A0_b524(g, func_01E01FE0_b524, 0);
        }
        if (o->speed > 20) {
            o->speed--;
        } else if (o->t > 60) {
            if (o->speed != 0) {
                o->speed--;
            } else {
                o->speed--;
                g->pos = o->pos;
                sp = o->speed;
                g->pos.x += g->dir[o->idx].x * sp;
                g->pos.y += g->dir[o->idx].y * sp;
                g->pos.z += g->dir[o->idx].z * sp;
                func_01E034A0_b524(g, func_01E023F0_b524, 0);
                func_01E034A0_b524(g, func_01E02910_b524, 0);
            }
        }
    }
    g->spd[o->idx] = o->speed;
    func_00205C40((s32)o->rot);
    o->t++;
    o->ang += 5;
    g->spd2[o->idx] = o->speed;
    return 0;
}

/* shape b428:01E018E0, 98 insns, 2 copies: a grey ember: set up once (random size 2..4, frame, angle, speed 16..35, life
   3..5); fades in for its life, then out (b225:01E026A0 family, 0x58-state layout) */

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
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b428_01E018E0;

static s32 func_01E01FE0_b524(void *arg0, Spark_b428_01E018E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 3 + 2;
        o->frame = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b524:01E02170, 76 insns: a grey rising flash (b144:01E02630 shape): f48 100 rising by 350 / 10 with f4C 58 below; both
   alphas full for 5 frames, then down by 14 until the first runs out */

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
} Obj_b524_01E02170;

static s32 func_01E02170_b524(void *arg0, Obj_b524_01E02170 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 100.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->h50 = 0;
        o->w = 0xA;
        o->h = 0xA;
        o->f34 = 350.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 5) {
        o->c0[3] = 0x80;
        o->c1[3] = 0x80;
    } else {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xF) {
            o->c1[3] -= 0xE;
        }
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 58.0f;
    o->t++;
    return 0;
}

/* shape b524:01E022A0, 81 insns: a yellow flickering spinning flash (b400:01E01E30 shape): f4C 100; second alpha up by 0x40 to 0x80 for 4
   frames */

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
} Obj_b524_01E022A0;

static s32 func_01E022A0_b524(void *arg0, Obj_b524_01E022A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = 100.0f;
        o->f4C = 100.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0xFF, 0xFF, 0x80);
        o->h52 = 0;
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else if (o->c1[3] > 0xC) {
        o->c1[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0x80);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b524:01E023F0, 105 insns: b282:01E01C20 family spinning white spark (random size 8..21, frame 0..2, angle 3..7, spin 16..35, held 3..5 ticks): in by 64 up to 0xC0, then out by 14 and ends */

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
} Obj_b524_01E023F0;

static s32 func_01E023F0_b524(s32 arg0, Obj_b524_01E023F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 14 + 8;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 5 + 3;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b524:01E025A0, 91 insns: a white/yellow ring (height 60), its first colour blinking: in by 10 up to 0x80 for 70 ticks while its slot value (ctx+0x5E10 table) is under 21, then out by 11 and ends; spun 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 f10;
    u8 pad14[4];
    f32 f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b524_01E025A0;

typedef struct {
    u8 pad[0x5E10];
    s16 val[1];
} Game_b524_01E025A0;

static s32 func_01E025A0_b524(Game_b524_01E025A0 *g, Obj_b524_01E025A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f4C = 60.0f;
        o->f4C = 60.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 70) {
        if (g->val[o->h50] < 21) {
            if (o->col2[3] < 0x80) {
                o->col2[3] += 10;
            }
        }
    } else if (o->col2[3] > 12) {
        o->col2[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0x80);
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b524:01E02710, 127 insns: a grey mote thrown from joint A toward joint B: size 12, f48 5, frame 2..7; its speed is
   a tenth of the gap (a quarter on z) with a random 0..14 - 4 lift; alpha grows by 0x40 (below 0x80) for 15 ticks,
   then fades by 9 (ends below 11); frame cycles 0..3; moves from the second tick; turns 0x20 */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b524_01E02710;

typedef struct {
    u8 pad0[0x5DF0];
    s16 ja;
    s16 jb;
} Scene_b524_01E02710;

static s32 func_01E02710_b524(Scene_b524_01E02710 *g, Fx_b524_01E02710 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[2];

    if (o->mode == 1) {
        func_001F5620(func_001F53A0(), g->ja, &v[0]);
        func_001F5620(func_001F53A0(), g->jb, &v[1]);
        o->w = 12;
        o->h = 12;
        o->f48 = 5.0f;
        o->frame = func_0019A5C8() % 6 + 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->vx = v[1].x - v[0].x;
        o->vy = v[1].y - v[0].y + func_0019A5C8() % 15 - 4.0f;
        o->vz = v[1].z - v[0].z;
        o->vx /= 10.0f;
        o->vy /= 10.0f;
        o->vz /= 4.0f;
        o->mode = 2;
    }
    if (o->t < 15) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->frame++;
    if (o->frame >= 4) {
        o->frame = 0;
    }
    if (o->t != 0) {
        o->x += o->vx;
        o->y += o->vy;
        o->z += o->vz;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b493:01E03310, 80 insns: a growing grey glow: on start f8/fA 80, f48 5, f56 0; alpha grows by 0x60 (below
   0xC0) for 5 ticks, then fades out by 9 and stops; from tick 2 f56 steps up every other tick (max 5); f8/fA grow
   by 1 every tick after the first */

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
} Fx_b493_01E03310;

static s32 func_01E02910_b524(s32 arg0, Fx_b493_01E03310 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 80;
        o->fA = 80;
        o->f48 = 5.0f;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick > 1 && o->tick % 2 == 1) {
        o->f56++;
    }
    if (o->f56 > 5) {
        o->f56 = 5;
    }
    if (o->tick != 0) {
        o->f8++;
        o->fA++;
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02A50_b524(void) {
    return 0;
}

/* shape b524:01E02A60 (b524), 656 insns, 1 copy: b524 scene manager in b593:01E030D0 form: setup (six joints, one
   type-4 and four type-5 textures, jitter tables with 100..179 set to 0..3), step b524:01E018F0 and every slot except
   the empty handler, draw the eight effect kinds (the b524:01E01B30 shard flips its side against the camera z +-30 on
   its first tick); scene code from the frame */

typedef struct {
    u8 pad0[0xC];
    s16 hC;
    u8 padE[2];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0x4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b524_01E02A60;

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
    Fx_b524_01E02A60 fx[200];
    u8 pad5A20[0x30];
    Vec4f pt[52];
    s32 tex[4];
    u8 pad5DA0[0x10];
    s32 count;
    u8 pad5DB4[0x8];
    s32 ot;
    u8 pad5DC0[0xC];
    Vec4f *pa;
    Vec4f *pb;
    u8 pad5DD4[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad5DFC[4];
    s16 cam;
    u8 pad5E02[0xE];
    s16 mul[50];
    s16 idx[59];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b524_01E02A60;

static s32 func_01E02A60_b524(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern Vec4f *func_001F9D30(s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void b524_01E018F0();
    extern void b524_01E01590();
    Scene_b524_01E02A60 *g = (Scene_b524_01E02A60 *)arg0;
    Vec4f p;
    Vec4f q;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s16 n;
    f32 t;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x6260);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 240;
        g->jA = func_001F5560(func_001F53A0(), 0x1B, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 4; i++) {
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
    b524_01E018F0(g, 0);
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02A50_b524) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 200; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01B30_b524) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                g->c.h[0] = g->fx[k].h56 << 6;
                g->c.h[1] = 0;
                g->c.h[2] = 0x40;
                g->c.h[3] = 0x40;
                p.x = g->fx[k].pos.x + g->fx[k].f48 * func_00108030(g->crd, g->idx[g->fx[k].h50], 0);
                p.y = g->fx[k].pos.y;
                p.z = g->fx[k].pos.z;
                t = g->fx[k].h52;
                p.x += g->pt[g->fx[k].h50].x * t;
                p.y += g->pt[g->fx[k].h50].y * t;
                p.z += g->pt[g->fx[k].h50].z * t;
                if (g->fx[k].h54 == 1) {
                    func_001F5F90(func_001F5380(), &q);
                    g->pa = func_001F9AD0(0);
                    g->pb = func_001F9D30(0);
                    if (g->turn != 0) {
                        q.z -= 30.0f;
                        if (g->pa->x < 0.0f) {
                            if (!(q.z <= p.z)) {
                                g->fx[k].hC = 0;
                            } else {
                                g->fx[k].hC = 2;
                            }
                        } else {
                            if (!(q.z <= p.z)) {
                                g->fx[k].hC = 2;
                            } else {
                                g->fx[k].hC = 0;
                            }
                        }
                    } else {
                        q.z += 30.0f;
                        if (!(g->pa->x <= 0.0f)) {
                            if (!(q.z <= p.z)) {
                                g->fx[k].hC = 2;
                            } else {
                                g->fx[k].hC = 0;
                            }
                        } else {
                            if (!(q.z <= p.z)) {
                                g->fx[k].hC = 0;
                            } else {
                                g->fx[k].hC = 2;
                            }
                        }
                    }
                }
                g->hBE = g->fx[k].hC;
                func_01E00ED0_b524((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01FE0_b524) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b524((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02170_b524) {
                g->tex88 = g->tex[2];
                g->c.h[0] = 0;
                g->c.h[1] = 0;
                g->c.h[2] = 0x1F;
                g->c.h[3] = 0x3F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 36;
                g->hBE = 0;
                func_01E01190_b524((Obj_b016_01E014F0 *)g, (Cam_b016_01E014F0 *)&g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E022A0_b524) {
                g->hB8 = 36;
                b524_01E01590(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E023F0_b524) {
                g->tex88 = g->tex[1];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->hB8 = 12;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b524((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E025A0_b524) {
                g->hB8 = 36;
                p.x = g->fx[k].pos.x + 5.0f * func_00108030(g->crd, g->idx[g->fx[k].h50], 0);
                p.y = g->fx[k].pos.y;
                p.z = g->fx[k].pos.z;
                t = g->mul[g->fx[k].h50];
                p.x += g->pt[g->fx[k].h50].x * t;
                p.y += g->pt[g->fx[k].h50].y * t;
                p.z += g->pt[g->fx[k].h50].z * t;
                b524_01E01590(g, &g->fx[k], 0x21, &p);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02710_b524) {
                g->tex88 = g->tex[1];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm4;
                g->hBE = 0;
                func_01E00ED0_b524((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02910_b524) {
                g->tex88 = g->tex[3];
                g->c.h[0] = g->fx[k].h56 << 6;
                g->c.h[1] = 0;
                g->c.h[2] = 0x3F;
                g->c.h[3] = 0x3F;
                g->hBE = 0;
                func_01E00ED0_b524((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x21, g->fx[k].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 170) {
        return 1;
    }
    if (g->frame == 225) {
        return 4;
    }
    if (g->frame == 215) {
        return 2;
    }
    if (g->frame > 180 && g->frame < 210) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b524:01E034A0, 80 insns: twin of b034:01E05330: take a free effect slot (0xC8 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b524_01E034A0 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b524_01E034A0;

typedef struct Obj_b524_01E034A0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b524_01E034A0 slots[0xC8];
    u8 padB[0x394];
    u8 rgba[4];
    u8 padC[0x12E];
    s16 fB2B0;
} Obj_b524_01E034A0;

static s32 func_01E034A0_b524(Obj_b524_01E034A0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b524_01E034A0 *s = NULL;
    s16 i;

    for (i = 0; i < 0xC8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xC8;
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
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}
