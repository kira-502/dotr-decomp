#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b283(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b283(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b283(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

static void func_01E00B80_b283(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b283((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b283((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E01130_b283(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E01490_b283(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b283:01E01890 (B283_W_S), 386 insns, 1 copy: B283_W_S, the effect scene step: counts the frame (0xA2CA);
   before frame 199 takes joint 0xA298 into a local and joints 0xA294/0xA296 into the four points, frames 199..239
   move each point z by 0.08 (down when flag 0xA2C6 is set); frame 34 spawns 0x1E03120 on sides 0/1; frame 250 spawns
   seven 0x1E03260, 0x1E036C0 on sides 0/1 and 0x1E03400; frames 251..300 spawn 0x1E03500; frame 199 spawns 0x1E029A0
   and 0x1E024B0 on sides 0..3; frame 196 spawns 0x1E026F0 on sides 0/1; frame 210 clears the side */

typedef struct {
    u8 pad0[0xA060];
    Vec4f pt[4];
    u8 padA0A0[0xA294 - 0xA0A0];
    s16 joint0;
    s16 joint1;
    s16 joint2;
    u8 padA29A[0xA2C2 - 0xA29A];
    s16 side;
    u8 padA2C4[2];
    s16 flag;
    u8 padA2C8[2];
    s16 t;
} Scene_b283_01E01890;

static void func_01E01890_b283(Scene_b283_01E01890 *g) {
    extern void b283_01E024B0(void);
    extern void b283_01E026F0(void);
    extern void b283_01E029A0(void);
    extern void b283_01E03120(void);
    extern void b283_01E03260(void);
    extern void b283_01E03400(void);
    extern void b283_01E03500(void);
    extern void b283_01E036C0(void);
    extern void b283_01E04320(Scene_b283_01E01890 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[3];

    g->t++;
    if (g->t < 199) {
        func_001F5620(func_001F53A0(), g->joint2, v);
        func_001F5620(func_001F53A0(), g->joint0, &g->pt[0]);
        func_001F5620(func_001F53A0(), g->joint1, &g->pt[1]);
        func_001F5620(func_001F53A0(), g->joint0, &g->pt[2]);
        func_001F5620(func_001F53A0(), g->joint1, &g->pt[3]);
    } else if (g->t < 240) {
        if (g->flag) {
            g->pt[0].z -= 0.08f;
        } else {
            g->pt[0].z += 0.08f;
        }
        if (g->flag) {
            g->pt[1].z -= 0.08f;
        } else {
            g->pt[1].z += 0.08f;
        }
        if (g->flag) {
            g->pt[2].z -= 0.08f;
        } else {
            g->pt[2].z += 0.08f;
        }
        if (g->flag) {
            g->pt[3].z -= 0.08f;
        } else {
            g->pt[3].z += 0.08f;
        }
    }
    if (g->t == 34) {
        g->side = 0;
        b283_01E04320(g, b283_01E03120, 0);
        g->side = 1;
        b283_01E04320(g, b283_01E03120, 0);
    }
    if (g->t == 250) {
        b283_01E04320(g, b283_01E03260, 0);
        b283_01E04320(g, b283_01E03260, 0);
        b283_01E04320(g, b283_01E03260, 0);
        b283_01E04320(g, b283_01E03260, 0);
        b283_01E04320(g, b283_01E03260, 0);
        b283_01E04320(g, b283_01E03260, 0);
        b283_01E04320(g, b283_01E03260, 0);
        g->side = 0;
        b283_01E04320(g, b283_01E036C0, 0);
        g->side = 1;
        b283_01E04320(g, b283_01E036C0, 0);
        b283_01E04320(g, b283_01E03400, 0);
    }
    if (g->t >= 251 && g->t <= 300) {
        b283_01E04320(g, b283_01E03500, 0);
    }
    if (g->t == 199) {
        g->side = 0;
        b283_01E04320(g, b283_01E029A0, 0);
        b283_01E04320(g, b283_01E024B0, 0);
        g->side = 1;
        b283_01E04320(g, b283_01E029A0, 0);
        b283_01E04320(g, b283_01E024B0, 0);
        g->side = 2;
        b283_01E04320(g, b283_01E029A0, 0);
        b283_01E04320(g, b283_01E024B0, 0);
        g->side = 3;
        b283_01E04320(g, b283_01E029A0, 0);
        b283_01E04320(g, b283_01E024B0, 0);
    }
    if (g->t == 196) {
        g->side = 0;
        b283_01E04320(g, b283_01E026F0, 0);
        g->side = 1;
        b283_01E04320(g, b283_01E026F0, 0);
        g->side = 3;
        g->side = 4;
        g->side = 5;
    }
    if (g->t == 210) {
        g->side = 0;
    }
}

/* shape b283:01E01EA0, 134 insns: b703:01E02370's grey rising mote placed on start at the scene part picked by its 0x50 (0x460-byte parts at +0x48D0) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    f32 x, y0, z;
    u8 pad1C[0x2C];
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
} Obj_b283_01E01EA0;

typedef struct {
    f32 x, y, z;
    u8 padC[0x454];
} Part_b283_01E01EA0;

typedef struct {
    u8 pad0[0x48D0];
    Part_b283_01E01EA0 part[1];
} Scene_b283_01E01EA0;

static s32 func_01E01EA0_b283(Scene_b283_01E01EA0 *g, Obj_b283_01E01EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 10 + 10;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->x = g->part[o->y].x;
        o->y0 = g->part[o->y].y;
        o->z = g->part[o->y].z;
        o->y = func_0019A5C8() % 60 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 10 + 6;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b283:01E020C0, 122 insns: base = the game value 0xA280 / 1.4; on start f48 20, variant 4, colour 0x80 grey,
   random rotation, 0x50 base..base+99, random 0x5A, speed 1..3 (0xE), 0x8 -6..8, hold 1..3 (0x6); alpha grows by 0x40
   (below 0xC0) during the hold, then fades by 19 and stops */

typedef struct {
    u8 pad0[0xA280];
    f32 fA280;
} Game_b283_01E020C0;

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
} Fx_b283_01E020C0;

static s32 func_01E020C0_b283(Game_b283_01E020C0 *g, Fx_b283_01E020C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001A22C0(f32);
    s16 base;

    base = func_001A22C0(g->fA280 / 1.4f);
    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = base + func_0019A5C8() % 100;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b283:01E022B0, 126 insns: b084:01E01DB0 with the game value at 0xA280: a dark spark at a random position */

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
} Fx_b283_01E022B0;

typedef struct {
    u8 pad[0xA280];
    f32 v;
} Game_b283_01E022B0;

static s32 func_01E022B0_b283(Game_b283_01E022B0 *g, Fx_b283_01E022B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 base;

    base = g->v / 1.4f;
    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f56 = 4;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        o->pos[0] = func_0019A5C8() % 0xFFFF;
        o->pos[1] = func_0019A5C8() % 0xFFFF;
        o->pos[2] = func_0019A5C8() % 0xFFFF;
        o->f50 = base + func_0019A5C8() % 100;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 30 + 20;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 80;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    o->f50 += o->spin;
    o->tick++;
    return 0;
}

/* shape b283:01E024B0, 79 insns: a white-green flickering spinning flash: f48 100, size 10x10; alpha up by 38 to 0xC0 until the game timer reaches
   0x122, then down by 8 until it ends; second colour flickers by frame parity */

typedef struct {
    u8 pad0[0xA2CA];
    s16 timer;
} Game_b283_01E024B0;

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
} Obj_b283_01E024B0;

static s32 func_01E024B0_b283(Game_b283_01E024B0 *g, Obj_b283_01E024B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 100.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0x122) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x26;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x10, 0x80, 0x10);
    } else {
        func_001076F0(o->c1, 0x10, 0xF0, 0x10);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b283:01E025F0, 63 insns: on start f48 300.0f, colour 0xFF grey, second colour (0x10, 0xFF, 0x10) with alpha 0,
   0x5A/0x5C = 10; alpha grows by 0xE (below 0xC0) while the game step at 0xA2CA is below 0x12C, then fades by
   8 and stops; the rotation at 0x20 advances 0x4000 each tick */

typedef struct {
    u8 pad0[0xA2CA];
    s16 step;
} Game_b283_01E025F0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b283_01E025F0;

static s32 func_01E025F0_b283(Game_b283_01E025F0 *g, Fx_b283_01E025F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 300.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x10, 0xFF, 0x10);
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->step < 0x12C) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xE;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b283:01E026F0, 63 insns: on start f48 150.0f, colour 0x80 grey, second colour (0x10, 0xFF, 0x10) with alpha 0,
   0x5A/0x5C = 10; alpha grows by 0x40 (below 0x80) while the game step at 0xA2CA is below 0x12C, then fades by
   8 and stops; the rotation at 0x20 advances 0x4000 each tick */

typedef struct {
    u8 pad0[0xA2CA];
    s16 step;
} Game_b283_01E026F0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b283_01E026F0;

static s32 func_01E026F0_b283(Game_b283_01E026F0 *g, Fx_b283_01E026F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 150.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x10, 0xFF, 0x10);
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->step < 0x12C) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b283:01E027F0, 105 insns: b282:01E01C20 family spinning spark (random size 20..39, frame 0..2, angle 10..69, spin 16..35, held 3..5 ticks): in by 64 up to 0xC0, then out by 14 and ends */

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
} Obj_b283_01E027F0;

static s32 func_01E027F0_b283(s32 arg0, Obj_b283_01E027F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 20;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 60 + 10;
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

/* shape b283:01E029A0, 357 insns: one of four green orbiters of the b283 scene (idx 0..3 start a quarter turn apart):
   on start it fills its 69-point trail with its centre, copies the centre, colours its tail red and aims a climb
   over 50 ticks from the model's height to the joint's; full alpha until scene step 290, then fades and shrinks;
   flashes green every other tick; it climbs (until step 249) and circles its centre at a radius that grows to 10
   for 25 ticks then eases to 8; for 50 ticks its trail follows (b283:01E00080), for 45 a spark rides the trail head */

typedef struct {
    Vec4f p[70];
} Trail_b283_01E029A0;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x48D0 - 0x260];
    Trail_b283_01E029A0 tr[4];
    u8 pad5A50[0xA060 - 0x5A50];
    Vec4f a[10];
    Vec4f b[4];
    u8 padA140[0xA298 - 0xA140];
    s16 joint;
    u8 padA29A[0x28];
    s16 ring;
    u8 padA2C4[6];
    s16 step;
    u8 padA2CC[0x200];
    u8 table[1];
} Ctx_b283_01E029A0;

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x28];
    f32 rad;
    u8 pad34[4];
    f32 vy;
    u8 pad3C[0xC];
    f32 size;
    u8 pad4C[4];
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Orb_b283_01E029A0;

static s32 func_01E029A0_b283(Ctx_b283_01E029A0 *g, Orb_b283_01E029A0 *o) {
    extern void b283_01E00080(Vec4f *, s32, s32, Vec4f *);
    extern s32 b283_01E01EA0();
    extern void b283_01E04320(Ctx_b283_01E029A0 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f q;
    Vec4f p[2];
    s16 i;
    Vec4f *s;
    Vec4f *d;

    if (o->state == 1) {
        o->life = 8;
        o->c0[3] = 0;
        s = &g->a[o->idx];
        d = g->tr[o->idx].p;
        for (i = 0; i < 69; i++) {
            d->x = s->x;
            d->y = s->y;
            d->z = s->z;
            d++;
        }
        g->b[o->idx].x = g->a[o->idx].x;
        g->b[o->idx].y = g->a[o->idx].y;
        g->b[o->idx].z = g->a[o->idx].z;
        func_001076F0(o->c1, 0x80, 0x10, 0x10);
        if (o->idx == 0) {
            o->ang = 0;
        }
        if (o->idx == 1) {
            o->ang = 180;
        }
        if (o->idx == 2) {
            o->ang = 90;
        }
        if (o->idx == 3) {
            o->ang = 270;
        }
        func_001F5F90(func_001F5380(), p);
        func_001F5620(func_001F53A0(), g->joint, &q);
        o->vy = (p[0].z - q.z) / 50.0f;
        o->size = 20.0f;
        o->state = 2;
    }
    if (o->life < 52) {
        o->life++;
    }
    if (g->step < 290) {
        o->c0[3] = 0xC0;
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->size > 0.0f) {
            o->size -= 1.0f;
        }
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0x10, 0xFF, 0x10);
    } else {
        func_001076F0(o->c0, 0x10, 0x80, 0x10);
    }
    if (o->t != 0) {
        if (g->step < 249) {
            g->b[o->idx].z += o->vy;
        }
        g->b[o->idx].x = g->a[o->idx].x + o->rad * func_00108030(g->table, o->ang, 1);
        g->b[o->idx].y = g->a[o->idx].y + o->rad * func_00108030(g->table, o->ang, 0);
        if (o->idx == 0) {
            o->ang += 8;
        }
        if (o->idx == 1) {
            o->ang += 8;
        }
        if (o->idx == 2) {
            o->ang += 8;
        }
        if (o->idx == 3) {
            o->ang += 8;
        }
        if (o->t < 25) {
            if (o->rad < 10.0f) {
                o->rad += 1.5f;
            }
        } else if (o->rad > 8.0f) {
            o->rad -= 0.5f;
        }
    }
    if (o->t < 50) {
        b283_01E00080(&g->tr[o->idx].p[69], 70, 0, &g->b[o->idx]);
    }
    if (o->t < 45) {
        g->pos.x = g->tr[o->idx].p[0].x;
        g->pos.y = g->tr[o->idx].p[0].y;
        g->pos.z = g->tr[o->idx].p[0].z;
        g->ring = o->idx;
        b283_01E04320(g, b283_01E01EA0, 0);
    }
    o->t++;
    return 0;
}

/* shape b283:01E02F40, 119 insns: a white tumbling ring (size 1000, spin 20/4, random turns re-rolled in 0..32767), its second colour blinking green: in by 64 up to 0xC0 while the scene value is under 300, then out by 8 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
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
} Obj_b283_01E02F40;

typedef struct {
    u8 pad[0xA2CA];
    s16 val;
} Game_b283_01E02F40;

static s32 func_01E02F40_b283(Game_b283_01E02F40 *g, Obj_b283_01E02F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 1000.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h5A = 20;
        o->h5C = 4;
        o->w20 = (func_0019A5C8() >> 4) % 65535;
        o->w24 = (func_0019A5C8() >> 4) % 65535;
        o->w28 = (func_0019A5C8() >> 4) % 65535;
        o->w20 = func_0019A5C8() % 32768;
        o->w24 = func_0019A5C8() % 32768;
        o->w28 = func_0019A5C8() % 32768;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->val < 300) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x10, 0x80, 0x10);
    } else {
        func_001076F0(o->col2, 0x20, 0xF0, 0x20);
    }
    o->t++;
    return 0;
}

/* shape b283:01E03120, 79 insns: a white-green flickering spinning flash: f48 40 (b283:01E024B0 shape), size 10x10; alpha up by 14 to 0xC0 until the game timer
   reaches 300, then down by 8 until it ends; second colour flickers by frame parity */

typedef struct {
    u8 pad0[0xA2CA];
    s16 timer;
} Game_b283_01E03120;

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
} Obj_b283_01E03120;

static s32 func_01E03120_b283(Game_b283_01E03120 *g, Obj_b283_01E03120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 40.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0x12C) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0xE;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x10, 0x80, 0x10);
    } else {
        func_001076F0(o->c1, 0x20, 0xF0, 0x20);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b283:01E03260, 103 insns: a grey-green flicker veil: size 1000, random turn on all three axes, sub-frame 4; alpha up by
   0x40 to 0xC0 while the scene timer is under 300, then down by 8 until it ends; second colour flickers green */

typedef struct {
    u8 pad0[0xA2CA];
    s16 timer;
} Game_b283_01E03260;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b283_01E03260;

static s32 func_01E03260_b283(Game_b283_01E03260 *g, Obj_b283_01E03260 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 1000.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x10, 0x10, 0x10);
        o->kind = 0;
        o->h5A = 0x14;
        o->h5C = 2;
        o->sub = 4;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (g->timer < 0x12C) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x10, 0x80, 0x10);
    } else {
        func_001076F0(o->c1, 0x20, 0xF0, 0x20);
    }
    o->t++;
    return 0;
}

/* shape b283:01E03400, 63 insns: on start f48 320.0f, colour 0xFF grey, second colour (0x40, 0xFF, 0x40) with alpha 0,
   0x5A/0x5C = 10; alpha grows by 0x60 (below 0xC0) while the game step at 0xA2CA is below 0x12C, then fades by
   8 and stops; the rotation at 0x20 advances 0x4000 each tick */

typedef struct {
    u8 pad0[0xA2CA];
    s16 step;
} Game_b283_01E03400;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b283_01E03400;

static s32 func_01E03400_b283(Game_b283_01E03400 *g, Fx_b283_01E03400 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 320.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0xFF, 0x40);
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->step < 0x12C) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b283:01E03500, 111 insns: a grey rising spark on the current model (b631:01E01D30 shape): placed at the model, 50 up;
   size 30..59, sub-frame 0..2, height 10..69, angle, rise 26..55 once started, width 0..34, hold 3..5; alpha up, then down by 14 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
    s16 step;
    Vec4f pos;
    u8 pad20[0x28];
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
} Obj_b283_01E03500;

static s32 func_01E03500_b283(void *arg0, Obj_b283_01E03500 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 30 + 0x1E;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 60 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 30 + 0x1A;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        func_001F5F90(func_001F5380(), &o->pos);
        o->pos.y = 50.0f;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b283:01E036C0, 82 insns: a two-colour glow (white, or blue/green for kind 1): in by 42 up to 0x80 for 16 ticks, then out by 4 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b283_01E036C0;

static s32 func_01E036C0_b283(s32 arg0, Obj_b283_01E036C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->h6 = 16;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xD0, 0xD0, 0x80);
            func_001076F0(o->col2, 0x80, 0xC0, 0x80);
            o->h6 = 16;
        }
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else {
        if (o->col[3] > 5) {
            o->col[3] -= 4;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 5) {
            o->col2[3] -= 4;
        } else {
            o->col2[3] = 0;
        }
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b283", func_01E03810_b283);

/* shape b283:01E04320, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x96 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b283_01E04320 {
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
} Slot_b283_01E04320;

typedef struct Obj_b283_01E04320 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b283_01E04320 slots[0x96];
    u8 padB[0xa264 - 0x2a0 - 0x96 * 0x70];
    u8 rgba[4];
    u8 padC[0xa2c2 - 0xa264 - 4];
    s16 fB2B0;
} Obj_b283_01E04320;

static s32 func_01E04320_b283(Obj_b283_01E04320 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b283_01E04320 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
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

INCLUDE_ASM("asm/nonmatchings/mod/b283", func_01E044B0_b283);
