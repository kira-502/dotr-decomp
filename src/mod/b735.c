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

static void func_01E00080_b735(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b735(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b735((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b735((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b735 in the
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

static void func_01E00ED0_b735(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b735((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E01190_b735(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b034:01E00E60, 115 insns, 33 copies: builds a 4-vertex sprite packet from the object's two
   texture refs, sets the blend mode from arg2 >> 4 and, when arg2 & 0xF is 0, puts every vertex at the
   far depth; then sends it with the given (or no) level. */

typedef struct {
    u64 rgbaq;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b034_01E00E60;

typedef struct {
    u64 tag[2];
    Vtx_b034_01E00E60 v[4];
    u8 rest[0x40];
} Pk_b034_01E00E60;

static void func_01E01590_b735(s32 arg0, u8 *obj, s32 mode, f32 level) {
    Pk_b034_01E00E60 pk;
    u8 *dst;
    Pk_b034_01E00E60 *p;
    s16 blend;

    dst = func_00207500();
    p = (Pk_b034_01E00E60 *)(u32)&pk;
    func_00107990(p, obj + 0x60, 1);
    func_00107990(p, obj + 0x64, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, 0x42 | ((s64)0x80 << 32));
    } else {
        func_002086D0(p, ((s64)blend << 2) | (0x40 | ((s64)0x80 << 32)));
    }
    if ((mode & 0xF) == 0) {
        p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
        func_002075F0((s32)p, (s32)dst, 0);
    } else {
        func_002075F0((s32)p, (s32)dst, func_001A23B0(level));
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

static void func_01E01760_b735(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b735:01E01AD0, 194 insns: the effect scene's step: counts the frame (0xB2BE); frames 42..254 spawn 0x1E021B0 at
   joint 0xB248, from frame 44 the 0xB2B8 counter climbs to 50, frames 82..259 spawn nine 0x1E02500 at joint 0xB248
   (0xB2B4 = 18, 24, .. 66); at frame 256 it spawns fourteen 0x1E02850 at joint 0xB24A, then 0x1E02C60 and four
   0x1E02A50 (0xB2A6 = 0, 90, 45, 135; 0xB2B4 = 0, 0, 1, 1) */

typedef struct {
    u8 pad0[0x250];
    f32 pos[4];
    u8 pad260[0xB248 - 0x260];
    s16 jA;
    s16 jB;
    u8 padB24C[0x5A];
    s16 ang;
    u8 padB2A8[0xC];
    s16 kind;
    u8 padB2B6[2];
    s16 grow;
    u8 padB2BA[4];
    s16 t;
} Scene_b735_01E01AD0;

static void func_01E01AD0_b735(Scene_b735_01E01AD0 *g) {
    extern void b735_01E021B0(void);
    extern void b735_01E02500(void);
    extern void b735_01E02850(void);
    extern void b735_01E02A50(void);
    extern void b735_01E02C60(void);
    extern s32 b735_01E036A0(Scene_b735_01E01AD0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;
    s16 a;

    g->t++;
    if (g->t > 41 && g->t < 255) {
        func_001F5620(func_001F53A0(), g->jA, g->pos);
        b735_01E036A0(g, (s32)b735_01E021B0, 0);
    }
    if (g->t > 43) {
        if (g->grow < 50) {
            g->grow++;
        }
    }
    if (g->t > 81 && g->t < 260) {
        func_001F5620(func_001F53A0(), g->jA, g->pos);
        for (i = 1, a = 18; i < 10; i++) {
            g->kind = a;
            b735_01E036A0(g, (s32)b735_01E02500, 0);
            a += 6;
        }
    }
    if (g->t == 256) {
        func_001F5620(func_001F53A0(), g->jB, g->pos);
        func_001F5F90(func_001F5380(), g->pos);
        for (i = 1; i < 15; i++) {
            b735_01E036A0(g, (s32)b735_01E02850, 0);
        }
        g->kind = 0;
        b735_01E036A0(g, (s32)b735_01E02C60, 0);
        g->ang = 0;
        g->kind = 0;
        b735_01E036A0(g, (s32)b735_01E02A50, 0);
        g->ang = 90;
        g->kind = 0;
        b735_01E036A0(g, (s32)b735_01E02A50, 0);
        g->ang = 45;
        g->kind = 1;
        b735_01E036A0(g, (s32)b735_01E02A50, 0);
        g->ang = 135;
        g->kind = 1;
        b735_01E036A0(g, (s32)b735_01E02A50, 0);
    }
}

/* shape b735:01E01DE0, 241 insns: b256:01E02A40's spark in pink (0xFF, 0x80, 0x80) with random drift and spin,
   fading in to 0x80 for 32 ticks; it starts on joint 0xB248 and, for a random 30..49 ticks, moves toward joint
   0xB24A by a 50th of the gap times a growing step (from 10); frame 0..3 cycles, size grows to 60 */

typedef struct {
    u8 pad0[0xB248];
    s16 ja;
    s16 jb;
} Ctx_b735_01E01DE0;

typedef struct {
    s16 h0, h2, h4, h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    Vec4f pos;
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
} Obj_b735_01E01DE0;

static s32 func_01E01DE0_b735(Ctx_b735_01E01DE0 *ctx, Obj_b735_01E01DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[4];
    f32 k;

    if (o->state == 1) {
        o->h8 = 10;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
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
        o->h6 = func_0019A5C8() % 8;
        o->hE = func_0019A5C8() % 20 + 30;
        o->h52 = 10;
    }
    if (o->t < 32) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h56++;
    if (o->h56 > 3) {
        o->h56 = 0;
    }
    if (o->h8 < 60) {
        o->h8++;
    }
    o->hA = o->h8;
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    if (o->t < o->hE) {
        func_001F5620(func_001F53A0(), ctx->ja, &o->pos);
        func_001F5620(func_001F53A0(), ctx->jb, v);
        v[0] = (v[0] - o->pos.x) / 50.0f;
        v[1] = (v[1] - o->pos.y) / 50.0f;
        v[2] = (v[2] - o->pos.z) / 50.0f;
        k = o->h52;
        o->pos.x += v[0] * k;
        o->pos.y += v[1] * k;
        o->pos.z += v[2] * k;
        o->h52++;
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b735:01E021B0, 211 insns: b377:01E01CA0 cousin, a red (0x80/0x30/0x30) spark between scene joints 0xB248 and
   0xB24A: size 5..14, frame 0..2 cycling to 7, speed 16..35, hold 25..27; alpha up by 0x40 to 0x100, then down by 14;
   it sits k (0x52, from 10) fiftieths of the way from the first joint to the second, k climbing to the scene's 0xB2B8
   while the size grows by 0.2..0.9 a tick; ends once the scene frame (0xB2BE) reaches 260 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    f32 pos[3];
    u8 pad1C[0x2C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 k;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b735_01E021B0;

typedef struct {
    u8 pad0[0xB248];
    s16 ja;
    s16 jb;
    u8 padB24C[0x6C];
    s16 kmax;
    u8 padB2BA[4];
    s16 t;
} Scene_b735_01E021B0;

static s32 func_01E021B0_b735(Scene_b735_01E021B0 *g, Fx_b735_01E021B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    f32 k;
    f32 d;

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 10 + 5;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x30, 0x30);
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 25;
        o->k = 10;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f56++;
    if (o->f56 > 7) {
        o->f56 = 0;
    }
    func_001F5620(func_001F53A0(), g->ja, o->pos);
    func_001F5620(func_001F53A0(), g->jb, &v);
    v.x = (v.x - o->pos[0]) / 50.0f;
    *(f32 *)(u32)&v.y = (*(f32 *)(u32)&v.y - o->pos[1]) / 50.0f;
    *(f32 *)(u32)&v.z = (*(f32 *)(u32)&v.z - o->pos[2]) / 50.0f;
    o->pos[0] += v.x * (k = o->k);
    o->pos[1] += *(f32 *)(u32)&v.y * k;
    o->pos[2] += *(f32 *)(u32)&v.z * k;
    if (g->kmax > o->k) {
        o->k++;
    }
    d = func_0019A5C8() % 8 + 2;
    d /= 10.0f;
    if (o->tick != 0) {
        if (g->kmax > o->k) {
            o->f48 += d;
        }
    }
    if (g->t >= 260) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b735:01E02500, 211 insns: b735:01E021B0's red spark placed once (tick 0) k fiftieths of the way from joint
   0xB248 to 0xB24A; size 8..27 growing by (2 + rand % (k / 3)) / 40, hold 2..4, f50 5..14 growing by 2..4 on odd ticks */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    f32 pos[3];
    u8 pad1C[0x2C];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 k;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b735_01E02500;

typedef struct {
    u8 pad0[0xB248];
    s16 ja;
    s16 jb;
    u8 padB24C[0x6C];
    s16 kmax;
    u8 padB2BA[4];
    s16 t;
} Scene_b735_01E02500;

static s32 func_01E02500_b735(Scene_b735_01E02500 *g, Fx_b735_01E02500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    f32 k;
    f32 d;

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 8;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x30, 0x30);
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f56++;
    if (o->f56 > 7) {
        o->f56 = 0;
    }
    if (o->tick == 0) {
        func_001F5620(func_001F53A0(), g->ja, o->pos);
        func_001F5620(func_001F53A0(), g->jb, &v);
        v.x = (v.x - o->pos[0]) / 50.0f;
        *(f32 *)(u32)&v.y = (*(f32 *)(u32)&v.y - o->pos[1]) / 50.0f;
        *(f32 *)(u32)&v.z = (*(f32 *)(u32)&v.z - o->pos[2]) / 50.0f;
        o->pos[0] += v.x * (k = o->k);
        o->pos[1] += *(f32 *)(u32)&v.y * k;
        o->pos[2] += *(f32 *)(u32)&v.z * k;
    }
    d = func_0019A5C8() % (o->k / 3) + 2;
    d /= 40.0f;
    if (o->tick != 0) {
        o->f48 += d;
    }
    if (o->tick) {
        if (o->tick % 2) {
            o->f50 += o->speed;
        }
    }
    o->tick++;
    return 0;
}

/* shape b735:01E02850, 125 insns: b203:01E03140 family rising flash, one of two looks (red on black or light red on grey 0x30), size 60, from 200 rising (150..229)/10 per tick, f4C = 0.1 of it, full alpha 8 ticks then down by 5 */

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
} Obj_b735_01E02850;

static s32 func_01E02850_b735(void *arg0, Obj_b735_01E02850 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->c0, 0xC0, 0x20, 0x20);
            func_001076F0(o->c1, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->c0, 0xFF, 0xA0, 0xA0);
            func_001076F0(o->c1, 0x30, 0x30, 0x30);
        }
        o->w = 60;
        o->h = 60;
        o->f34 = func_0019A5C8() % 80 + 150;
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
    o->f4C = 0.1f * o->f48;
    o->t++;
    return 0;
}

/* shape b735:01E02A50, 129 insns: constant variant of b247:01E02320 (first 6->4, 0xA->0xE, 9->13, 28.0f->18.0f, 1600.0f->1000.0f, colour (255, 96, 96), colour (255, 64, 64), colour (255, 64, 64)) */

typedef struct {
    u8 pad0[0x30];
    f32 thick;
    f32 radius;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Ring_b735_01E02A50;

static s32 func_01E02A50_b735(void *arg0, Ring_b735_01E02A50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 6.0f;
        func_001076F0(o->c0, 0xFF, 0x60, 0x60);
        func_001076F0(o->c1, 0xFF, 0x40, 0x40);
        if (o->kind == 0) {
            o->thick = 18.0f;
            o->radius = 1000.0f;
        }
        if (o->kind == 1) {
            o->thick = 18.0f;
            o->radius = 500.0f;
        }
        if (o->kind == 2) {
            o->thick = 6.0f;
            o->radius = 100.0f;
            func_001076F0(o->c0, 0x80, 0x80, 0xC0);
            func_001076F0(o->c1, 0xFF, 0x40, 0x40);
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xE) {
        o->c0[3] -= 13;
    } else {
        o->state = 0;
    }
    if (o->kind == 0) {
        if (o->t != 0) {
            o->radius += 60.0f;
        }
        o->ang += 6;
    }
    if (o->kind == 1) {
        if (o->t != 0) {
            o->radius += 20.0f;
        }
        o->ang += 6;
    }
    if (o->kind == 2) {
        if (o->t != 0) {
            o->radius += 5.0f;
        }
        o->ang += 6;
    }
    o->t++;
    return 0;
}

/* shape b735:01E02C60, 98 insns: a two-colour fade by kind (b180:01E02040 shape: 0 pink both, 1 blue/purple, 2 pale blue both;
   hold 8, 8 or 22): both alphas up by 0x40 until the hold, then down by 4, the first ending it and the second stopping at 0 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b735_01E02C60;

static s32 func_01E02C60_b735(void *arg0, Obj_b735_01E02C60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            func_001076F0(o->c0, 0x9F, 0x5F, 0x5F);
            func_001076F0(o->c1, 0x9F, 0x5F, 0x5F);
            o->hold = 8;
        }
        if (o->kind == 1) {
            func_001076F0(o->c0, 0, 0x30, 0xF0);
            func_001076F0(o->c1, 0x30, 0, 0xF0);
            o->hold = 8;
        }
        if (o->kind == 2) {
            func_001076F0(o->c0, 0x58, 0x58, 0x78);
            func_001076F0(o->c1, 0x58, 0x58, 0x78);
            o->hold = 0x16;
        }
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 5) {
            o->c0[3] -= 4;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 5) {
            o->c1[3] -= 4;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E02DF0_b735(void) {
    return 0;
}

/* shape b735:01E02E00 (b735), 550 insns, 1 copy: scene manager in b590:01E02680's form: setup (six func_001F5560 ids,
   two type-4 and three type-5 textures, 256 s8 and 30 s16 jitters), else run the 400 slot handlers and draw six slot
   kinds; returns by scene frame */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b735_01E02E00;

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
    Fx_b735_01E02E00 fx[400];
    u8 padB1A0[0x50];
    s32 tex[4];
    u8 padB200[0x10];
    s32 count;
    u8 padB214[8];
    s32 ot;
    u8 padB220[0x14];
    f32 depth;
    u8 padB238[0x10];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 padB254[4];
    s16 cam;
    u8 padB25A[0xE];
    s16 jit16[30];
    u8 padB2A4[0x16];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 padB3C0[0x100];
    u8 crd[0x170];
} Scene_b735_01E02E00;

static s32 func_01E02E00_b735(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void b735_01E01AD0();
    Scene_b735_01E02E00 *g = (Scene_b735_01E02E00 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 ang[4];
    u8 pk[0x90];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 300;
        g->jA = func_001F5560(func_001F53A0(), 0x31, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x32, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
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
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    b735_01E01AD0(g, 0);
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E02DF0_b735) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 400; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01DE0_b735) {
                g->tex88 = g->tex[2];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                if (g->fx[k].h56 < 2) {
                    g->c.h[0] = g->fx[k].h56 << 6;
                    g->c.h[1] = 0;
                } else {
                    g->c.h[0] = (g->fx[k].h56 - 2) << 6;
                    g->c.h[1] = 0x40;
                }
                g->c.h[2] = 0x40;
                g->c.h[3] = 0x40;
                g->hBE = g->fx[k].h6;
                func_01E00ED0_b735((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x21, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E021B0_b735) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm2;
                g->c.h[0] = g->fx[k].h56 << 5;
                g->c.h[1] = 0;
                g->c.h[2] = 0x20;
                g->c.h[3] = 0x40;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b735((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02500_b735) {
                g->tex88 = g->tex[1];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm3;
                g->c.h[0] = g->fx[k].h56 << 5;
                g->c.h[1] = 0;
                g->c.h[2] = 0x20;
                g->c.h[3] = 0x40;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b735((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02850_b735) {
                func_00106080(rm4, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm4;
                g->tex88 = g->tex260[15];
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0xC;
                g->hBE = 0;
                func_01E01190_b735((Obj_b016_01E014F0 *)g, (Cam_b016_01E014F0 *)&g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02A50_b735) {
                g->tex88 = g->tex260[15];
                func_00106080(rm5, 0x9A, 0, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm5;
                g->hBE = 0;
                func_01E01760_b735((Obj_b020_01E00E70 *)g, (Fx_b020_01E00E70 *)&g->fx[k], 0, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02C60_b735) {
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 50.0f;
                } else {
                    v.z += 50.0f;
                }
                func_00205440(&v, NULL, &pk[0x18], &g->depth);
                if (g->fx[k].h50 == 0) {
                    func_01E01590_b735((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
                if (g->fx[k].h50 == 1) {
                    func_01E01590_b735((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
                if (g->fx[k].h50 == 2) {
                    func_01E01590_b735((s32)g, (u8 *)&g->fx[k], 0x21, g->depth);
                }
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0xF6) {
        return 1;
    }
    if (g->frame == 0x127) {
        return 4;
    }
    if (g->frame == 0x118) {
        return 2;
    }
    if (g->frame > 0x100 && g->frame < 0x113) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b539:01E03530, 106 insns, 4 copies: starts a particle: takes the first free one of 400 slots, clears it, gives
   it the emitter's two colours, position and timers and the two caller values; returns 0 when all are busy. */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 t0;
    s16 t1;
    u8 pad54[4];
    s16 used;
    s16 t2;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b539_01E03530;

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad0260[0x40];
    Slot_b539_01E03530 slots[400];
    u8 padB1A0[0x74];
    u8 col[4];
    u8 padB218[0x8E];
    s16 t2;
    u8 padB2A8[0xC];
    s16 t0;
} Emit_b539_01E03530;

static s32 func_01E036A0_b735(Emit_b539_01E03530 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b539_01E03530 *e;
    s16 i;

    e = NULL;
    for (i = 0; i < 400; i++) {
        if (o->slots[i].used == 0) {
            func_00195108(&o->slots[i], 0x70);
            o->slots[i].used = 1;
            e = &o->slots[i];
            i = 400;
        }
    }
    if (e != NULL) {
        func_001076F0(e->c0, o->col[0], o->col[1], o->col[2]);
        e->c0[3] = o->col[3];
        func_001076F0(e->c1, o->col[0], o->col[1], o->col[2]);
        e->c1[3] = o->col[3];
        func_00106AB0(e, &o->pos, 0);
        e->x = o->pos.x;
        e->y = o->pos.y;
        e->z = o->pos.z;
        e->t0 = o->t0;
        e->t1 = o->t0;
        e->t2 = o->t2;
        e->b = b;
        e->a = a;
        return 1;
    }
    return 0;
}
