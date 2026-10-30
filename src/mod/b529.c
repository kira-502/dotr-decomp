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

static void func_01E00080_b529(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b529(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b529((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b529((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00ED0_b529(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E01230_b529(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

static void func_01E01630_b529(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

typedef struct {
    s16 x, y, w, h;
    s32 pad[2];
} Rect_b152_01E014F0;

/* takes the third argument its callers pass (a3 = 0, unused) */
static Rect_b152_01E014F0 func_01E01800_b529(s32 unused, s16 n, s32 unused2) {
    Rect_b152_01E014F0 r;

    if (n < 2) {
        r.x = n * 32 + 1;
        r.y = 1;
        r.w = 30;
        r.h = 126;
    } else if (n < 4) {
        r.x = n % 2 * 32 + 1;
        r.y = 33;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 65;
        r.w = 30;
        r.h = 126;
    } else if (n < 8) {
        r.x = n % 2 * 32 + 1;
        r.y = 97;
        r.w = 30;
        r.h = 126;
    }
    r.w = 31;
    r.h = 31;
    return r;
}

/* shape b529:01E01950, 333 insns: the b529 scene's script: the anchor point follows joint 0x72E8 until tick 190, then
   glides to joint 0x72F8 over 50 ticks (until tick 238); on tick 1 it spawns 03090, 03170 and a ring 0 (023B0); from
   tick 73 one 01E90 a tick (72 of them, angle 10 x index); on tick 146 a 02650; on tick 164 rings 1 and 2, twenty
   027F0 and eleven 02D10; on ticks 250..280 a 02AB0 every other tick (numbered) and a 027F0 + 02D10 each tick; on tick
   288 rings 1 and 2 and a 02C10; a 02EF0 every tick until 300; every third tick the spawn point takes the anchor */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x7270 - 0x260];
    Vec4f p;
    Vec4f vel;
    u8 pad7290[0x58];
    s16 jointA;
    u8 pad72EA[0xE];
    s16 jointB;
    u8 pad72FA[0x9E];
    s16 k;
    s16 n;
    s16 ang;
    u8 pad739E[0xA];
    s16 ring;
    u8 pad73AA[6];
    s16 tick;
} Ctx_b529_01E01950;

static void func_01E01950_b529(Ctx_b529_01E01950 *g) {
    extern s32 b529_01E01E90();
    extern s32 b529_01E023B0();
    extern s32 b529_01E02650();
    extern s32 b529_01E027F0();
    extern s32 b529_01E02AB0();
    extern s32 b529_01E02C10();
    extern s32 b529_01E02D10();
    extern s32 b529_01E02EF0();
    extern s32 b529_01E03090();
    extern s32 b529_01E03170();
    extern void b529_01E03DF0(Ctx_b529_01E01950 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f t[2];
    s16 i;

    g->tick++;
    if (g->tick == 1) {
        b529_01E03DF0(g, b529_01E03090, 0);
        b529_01E03DF0(g, b529_01E03170, 0);
    }
    if (g->tick >= 73 && g->k < 72) {
        g->ang = g->k * 10;
        g->ring = g->k;
        b529_01E03DF0(g, b529_01E01E90, 0);
        g->k++;
    }
    if (g->tick < 190) {
        func_001F5620(func_001F53A0(), g->jointA, &g->p);
    } else {
        if (g->tick == 190) {
            func_001F5620(func_001F5380(), g->jointB, t);
            g->vel.z = (t[0].z - g->p.z) / 50.0f;
            g->vel.y = (t[0].y - g->p.y) / 50.0f;
            g->vel.x = (t[0].x - g->p.x) / 50.0f;
        }
        if (g->tick < 239) {
            g->p.z += g->vel.z;
            g->p.y += g->vel.y;
            g->p.x += g->vel.x;
        }
    }
    if (g->tick % 3 == 1) {
        g->pos = g->p;
    }
    if (g->tick == 1) {
        g->pos = g->p;
        g->ring = 0;
        b529_01E03DF0(g, b529_01E023B0, 0);
    }
    if (g->tick == 0xA4) {
        g->pos = g->p;
        g->ring = 1;
        b529_01E03DF0(g, b529_01E023B0, 0);
        g->ring = 2;
        b529_01E03DF0(g, b529_01E023B0, 0);
        g->pos = g->p;
        g->ring = 0;
        for (i = 0; i < 20; i++) {
            b529_01E03DF0(g, b529_01E027F0, 0);
        }
        for (i = 0; i < 10; i++) {
            b529_01E03DF0(g, b529_01E02D10, 0);
        }
        b529_01E03DF0(g, b529_01E02D10, 0);
    }
    if (g->tick == 0x92) {
        g->pos = g->p;
        g->ring = 0;
        b529_01E03DF0(g, b529_01E02650, 0);
    }
    if (g->tick >= 250 && g->tick < 281) {
        g->pos = g->p;
        g->ring = g->n;
        if (g->tick % 2 == 0) {
            b529_01E03DF0(g, b529_01E02AB0, 0);
        }
        g->n++;
    }
    if (g->tick >= 250 && g->tick < 281) {
        g->pos = g->p;
        g->ring = 1;
        b529_01E03DF0(g, b529_01E027F0, 0);
        b529_01E03DF0(g, b529_01E02D10, 0);
    }
    if (g->tick == 0x120) {
        g->pos = g->p;
        g->ring = 1;
        b529_01E03DF0(g, b529_01E023B0, 0);
        g->ring = 2;
        b529_01E03DF0(g, b529_01E023B0, 0);
        b529_01E03DF0(g, b529_01E02C10, 0);
    }
    if (g->tick < 301) {
        g->pos = g->p;
        b529_01E03DF0(g, b529_01E02EF0, 0);
    }
}

/* OVL_WARM */

/* shape b529:01E01E90, 236 insns: a two-colour grey glow (0x80 / 0x70 flicker) whose stage (0x52: from 0x50, 0 below
   36, 2 below 72) grows 0x48 by 0.5 to 10 (stage 0) or 6 (stage 2), then 0x4C to 7 / 4; fades in by 8 for 30 ticks,
   out by 11 past scene time 300; before scene time 176 it spins randomly with x locked at 0x4000, after that its
   z angle turns by 256 + 0x30 (sign by 0x50), and 0x30 grows by 32 to 512 from scene time 241 */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x16];
    s32 rot[3];
    u8 pad2C[4];
    f32 f30;
    u8 pad34[0x14];
    f32 f48;
    f32 f4C;
    s16 f50;
    s16 stage;
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col0[4];
    u8 col1[4];
} Fx_b529_01E01E90;

typedef struct {
    u8 pad0[0x73B0];
    s16 timer;
} Scn_b529_01E01E90;

static s32 func_01E01E90_b529(Scn_b529_01E01E90 *g, Fx_b529_01E01E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->f4C = 0.0f;
        o->f56 = 0;
        o->mode = 2;
        if (o->f50 < 36) {
            o->stage = 0;
        } else if (o->f50 < 72) {
            o->stage = 2;
        }
        o->h8 = func_0019A5C8() % 3 + 4;
    }
    if (o->tick < 30) {
        if (o->col0[3] < 0x80) {
            o->col0[3] += 8;
        }
        if (o->col1[3] < 0x80) {
            o->col1[3] += 8;
        }
    } else if (g->timer > 300) {
        if (o->col0[3] > 12) {
            o->col0[3] -= 11;
        } else {
            o->mode = 0;
        }
        if (o->col1[3] > 12) {
            o->col1[3] -= 11;
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col0, 0x70, 0x70, 0x70);
        func_001076F0(o->col1, 0x70, 0x70, 0x70);
    }
    if (g->timer != 0) {
        k = o->stage;
        if (k == 0) {
            if (o->f48 < 10.0f) {
                o->f48 += 0.5f;
            } else {
                o->stage = k + 1;
            }
        } else if (k == 1) {
            if (o->f4C < 7.0f) {
                o->f4C += 0.5f;
            }
        } else if (k == 2) {
            if (o->f48 < 6.0f) {
                o->f48 += 0.5f;
            } else {
                o->stage = k + 1;
            }
        } else if (k == 3) {
            if (o->f4C < 4.0f) {
                o->f4C += 0.5f;
            }
        }
    }
    if (g->timer > 175) {
        if (o->f50 < 36) {
            o->rot[2] += 256.0f + o->f30;
        } else {
            o->rot[2] -= 256.0f + o->f30;
        }
    } else {
        func_00205C40((s32)o->rot);
        o->rot[0] = 0x4000;
    }
    if (g->timer > 240) {
        if (o->f30 < 512.0f) {
            o->f30 += 32.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b529:01E02240, 89 insns: a blinking white/blue glow (random size 5..24 unless set, spun 0x4000 a tick): alpha 0xC0 for 3 ticks, then out by 11 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    u8 pad24[4];
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
} Obj_b529_01E02240;

static s32 func_01E02240_b529(s32 arg0, Obj_b529_01E02240 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->h50 == 0) {
            o->f48 = 5.0f + func_0019A5C8() % 20;
            o->f4C = 0.0f;
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        }
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 3) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b529:01E023B0, 167 insns: b771:01E022D0 family glow in three kinds: 0 is 30 wide, white over blue, held 300 ticks fading in by 14 and flickering grey; 1 is 300 wide, white over pale blue, held 12; 2 is 110 wide, white glow over blue, held 12 on the second colour; fades by 11 (kind 2: 15); turns 0x4000 a tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b529_01E023B0;

static s32 func_01E023B0_b529(s32 arg0, Fx_b529_01E023B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 30.0f;
            o->f4C = 0.0f;
            o->hold = 300;
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        }
        if (o->kind == 1) {
            o->f48 = 300.0f;
            o->f4C = 0.0f;
            o->hold = 12;
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col2, 0xC0, 0xC0, 0xFF);
        }
        if (o->kind == 2) {
            o->f48 = 110.0f;
            o->f4C = 0.0f;
            o->hold = 12;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0x80, 0x80, 0xFF);
        }
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->kind == 0) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 14;
            }
        }
        if (o->kind == 1) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x40;
            }
        }
        if (o->kind == 2) {
            if (o->col2[3] < 0xC0) {
                o->col2[3] += 0x40;
            }
        }
    } else {
        if (o->kind == 0 || o->kind == 1) {
            if (o->col[3] > 12) {
                o->col[3] -= 11;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 2) {
            if (o->col2[3] > 16) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
        } else {
            func_001076F0(o->col, 0x70, 0x70, 0x70);
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] = 0x4000;
    o->tick++;
    return 0;
}

/* shape b529:01E02650, 102 insns: a white rising ring by kind (0: size 110, 1: size 80, inner 5 less): rise 950 / 10, sub-frame
   4; both alphas up by 14 to 0xC0 until frame 103, then down by 14, either ending it; held at a quarter turn */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[4];
    f32 rise;
    u8 pad38[0x10];
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
} Obj_b529_01E02650;

static s32 func_01E02650_b529(void *arg0, Obj_b529_01E02650 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            o->f48 = 110.0f;
            o->f4C = o->f48 - 5.0f;
        } else if (o->kind == 1) {
            o->f48 = 80.0f;
            o->f4C = o->f48 - 5.0f;
        }
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->kind = 0;
        o->h5A = 0xA;
        o->h5C = 0xA;
        o->rise = 950.0f;
        o->rise /= 10.0f;
        o->state = 2;
        o->sub = 4;
        o->c1[3] = 0;
    }
    if (o->t < 0x67) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0xE;
        }
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0xE;
        }
    } else {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xF) {
            o->c1[3] -= 0xE;
        } else {
            o->state = 0;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] = 0x4000;
    o->t++;
    return 0;
}

/* shape b529:01E027F0, 176 insns: a grey glow with a blue rim: kind 0 size 5..104, life 8..25, grows 10..29 a tick;
   kind 1 size 100..199, life 3..10, grows 5..14; three random angle words after func_00205C40 resets them; alpha up by
   42 to 0x80 for its life, then down by 15 until it ends; the rim's blue flips 0x60/0x50 every tick */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[6];
    s16 grow;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b529_01E027F0;

static s32 func_01E027F0_b529(s32 arg0, Fx_b529_01E027F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 5.0f + func_0019A5C8() % 100;
            o->f4C = 1.0f;
            o->hold = func_0019A5C8() % 18 + 8;
            o->f5C = 2;
            o->grow = func_0019A5C8() % 20 + 10;
        }
        if (o->kind == 1) {
            o->f48 = 100.0f + func_0019A5C8() % 100;
            o->f4C = 1.0f;
            o->hold = func_0019A5C8() % 8 + 3;
            o->f5C = 5;
            o->grow = func_0019A5C8() % 10 + 5;
        }
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x10, 0x10, 0x30);
        o->f5A = 15;
        func_00205C40(&o->w20);
        o->w20 = 0x4000;
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0x30, 0x30, 0x60);
    } else {
        func_001076F0(o->col2, 0x30, 0x30, 0x50);
    }
    o->f48 += o->grow;
    o->tick++;
    return 0;
}

/* shape b529:01E02AB0, 87 insns: a white/yellow tumbling glow of size 600 x 1 at three random turns (spin 10..29): in by 64 up to 0xC0 while the scene value is under 300, then out by 15 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b529_01E02AB0;

typedef struct {
    u8 pad[0x73B0];
    s16 val;
} Game_b529_01E02AB0;

static s32 func_01E02AB0_b529(Game_b529_01E02AB0 *g, Obj_b529_01E02AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 600.0f;
        o->f4C = 1.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x40, 0x40, 0xF0);
        o->h5A = 30;
        o->h5C = 10;
        o->hE = func_0019A5C8() % 20 + 10;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->val < 300) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b529:01E02C10, 63 insns: a white glow: both alphas up by 18 to 0x80 for 16 frames, then down by 4; it ends when the first runs out */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x4C];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b529_01E02C10;

static s32 func_01E02C10_b529(void *arg0, Obj_b529_01E02C10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0xF0, 0xF0, 0xF0);
        o->hold = 0x10;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x12;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x12;
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

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b529_01E02D10;

static s32 func_01E02D10_b529(s32 unused, Obj_b529_01E02D10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 10 + 5;
        o->h56 = 4;
        func_001076F0(o->c60, 0xC0, 0x50, 0x50);
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
        o->h52 = 1;
        o->h50 = func_0019A5C8() % 30 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 10 + 5;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        o->c60[3] = 0x80;
    } else if (o->c60[3] > 12) {
        o->c60[3] -= 11;
    } else {
        o->h58 = 0;
    }
    o->h52++;
    o->h50 += o->hE;
    o->h54++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[0x16];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b152_01E02680;

static s32 func_01E02EF0_b529(s32 unused, Obj_b152_01E02680 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 2 + 1;
        o->h56 = 4;
        func_001076F0(o->c60, 0xC0, 0xC0, 0xC0);
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
        o->h50 = func_0019A5C8() % 80 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 4 + 3;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        o->c60[3] = 0x80;
    } else if (o->c60[3] > 12) {
        o->c60[3] -= 11;
    } else {
        o->h58 = 0;
    }
    o->h54++;
    return 0;
}

/* shape b529:01E03090, 55 insns: volume fade by game state (b058:01E017A0 shape, layout at 0x50): state at 0x72B0
   limit 0x14, down 10 to 0x40, up 10 capped at 0x80; state 2 ends the fade */

typedef struct {
    u8 pad[0x72B0];
    s32 state;
} Game_b529_01E03090;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b529_01E03090;

static s32 func_01E03090_b529(Game_b529_01E03090 *g, Fade_b529_01E03090 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
        if (o->vol > 0x40) {
            o->vol -= 10;
        } else {
            o->vol = 0x40;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    func_001F6D00((u8)o->vol);
    if (g->state == 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape b529:01E03170, 128 insns: b747:01E02B40 with a blue-grey tint (0x78/0x78/0x90), start offset 1.5, and the
   fade-out once the game counter at g+0x73B0 reaches 300 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b529_01E03170;

typedef struct {
    f32 s, t;
    Xyz_b529_01E03170 p;
} Tv_b529_01E03170;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b529_01E03170 v[2];
    u8 tail[0x20];
} Tex_b529_01E03170;

typedef struct {
    u8 pad0[0x73B0];
    s16 count;
} Ctx_b529_01E03170;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b529_01E03170;

static s32 func_01E03170_b529(Ctx_b529_01E03170 *g, Fx_b529_01E03170 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b529_01E03170 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 1.5f;
        o->mode = 2;
    }
    ((Tex_b529_01E03170 *)(s32)&pk)->flags = 0x26;
    ((Tex_b529_01E03170 *)(s32)&pk)->size = 5;
    ((Tex_b529_01E03170 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b529_01E03170 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x78;
    pk.g = 0x78;
    pk.b = 0x90;
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
    if (g->count < 300) {
        if (o->col[3] < 0x50) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 8) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b529:01E03370, 174 insns: b491:01E03360's grey window (packet at ctx+0x72C8, point 0x72E8) drawn once, starting
   at alpha 0x78; the zoom grows by 100..129 a tick each way, and after the first tick it fades by 49 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b529_01E03370;

typedef struct {
    f32 s, t;
    Xyz_b529_01E03370 p;
} Tv_b529_01E03370;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b529_01E03370 v[2];
} Tex_b529_01E03370;

typedef struct {
    u8 pad[0x72C8];
    Tex_b529_01E03370 *pk;
    u8 pad72CC[0x72E8 - 0x72CC];
    s16 id;
} Game_b529_01E03370;

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
} Fx_b529_01E03370;

static s32 func_01E03370_b529(Game_b529_01E03370 *g, Fx_b529_01E03370 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b529", func_01E03630_b529);

/* shape b529:01E03DF0, 82 insns: c035:01E01150 family: take the first free effect slot of 250 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

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
} Obj_b529_01E03DF0;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b529_01E03DF0 slot[250];
    u8 padEnd[0x72b4 - 0x2a0 - 250 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad72B8[0xE4];
    s16 ang;
    u8 pad739E[0xA];
    s16 h30;
} Ctx_b529_01E03DF0;

static s32 func_01E03DF0_b529(Ctx_b529_01E03DF0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b529_01E03DF0 *s;

    s = NULL;
    for (i = 0; i < 250; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 250;
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

/* shape b529:01E03F40 (B529PAINT_RAIN20), 192 insns, 1 copy: b232:01E01B90's ring draw with one segment: two-colour
   packet, the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; the
   frame rect for the scene table entry (g+0x7308, 36 of them) picked by the object's 0x50; one quad from angle
   0x5A - 200 to 10 degrees on, between radii 0x4C and 0x48 (trig g+0x75B4), depth-tested into g+0x72BC */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    s16 h50;
    u8 pad52[8];
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b529_01E03F40;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Rect_b152_01E014F0 rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x72BC - 0xC0];
    s32 ot;
    u8 pad72C0[0x7308 - 0x72C0];
    s16 tbl[36];
    u8 pad7350[0x75B4 - 0x7350];
    u8 trig[1];
} Game_b529_01E03F40;

static void func_01E03F40_b529(Game_b529_01E03F40 *g, Obj_b529_01E03F40 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 m[16];
    f32 depth[4];
    Rect_b152_01E014F0 rc;
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;

    *(Vec4f *)pos = *in;
    s = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, o->col, 1);
    func_00107790(p, o->col2, 2);
    func_00108500(p, &g->rect, g->frame);
    func_00208700(p, g->tex, 1);
    k = mode >> 4;
    if (k == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)k << 2) | (((u64)0x80 << 32) | 0x40));
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    func_00108EF0(m, 0, o->rot, v);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    rc = func_01E01800_b529(0x14, g->tbl[o->h50 % 36], 0);
    g->rect = rc;
    func_00108500(p, &g->rect, g->frame);
    for (i = 0; i < 1; i++) {
        a = o->h5A + s - 200;
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        a = s + (s16)(o->h5A + 10) - 200; /* the (s16) keeps the +10 apart: needed for the match */
        c = func_00108030(g->trig, a, 1);
        sn = func_00108030(g->trig, a, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        s += 10;
    }
}

/* shape b529:01E04240, 68 insns: b183:01E029E0 family draw pass: sprite packet on the stack, then every live slot (250 of 0x70 bytes) whose handler is shape b529:01E03370 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b529_01E04240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b529_01E04240 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b529_01E04240;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b529_01E04240;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b529_01E04240 slot[250];
    u8 padEnd[0x72c4 - 0x2A0 - 250 * 0x70];
    s32 ctx;
    Pkt_b529_01E04240 *pkt;
} Scene_b529_01E04240;

static void func_01E04240_b529(Scene_b529_01E04240 *s) {
    extern void b529_01E03370(Scene_b529_01E04240 *, Slot_b529_01E04240 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b529_01E04240 pkt __attribute__((aligned(8)));
    s32 i;

    s->pkt = &pkt;
    s->ctx = func_00207F60();
    s->pkt->count = 0x26;
    s->pkt->tag = 5;
    s->pkt->regs = 0x42421;
    s->pkt->pad = 0;
    func_00208460();
    func_002086D0(s->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 250; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b529_01E03370) {
            b529_01E03370(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
