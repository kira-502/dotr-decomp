#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b731(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b731(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b020_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b020_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b020_01E00920;

typedef struct {
    u64 st;
    Xyz_b020_01E00920 p;
} Vtx_b020_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b020_01E00920 c;
    Vtx_b020_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b020_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b020_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b020_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    u8 pad5C[4];
    u8 col[1];
} Anim_b020_01E00920;

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
} Obj_b020_01E00920;

extern void b731_01E00110(Pkt_b020_01E00920 *, void *, s32);

static void func_01E009B0_b731(Obj_b020_01E00920 *o, Anim_b020_01E00920 *an, s32 mode, Tbl_b020_01E00920 *tbl) {
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
    Vec_b020_01E00920 quad[4];
    Vec_b020_01E00920 d;
    Vec_b020_01E00920 pos;
    Vec_b020_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b020_01E00920 r;
    struct {
        u64 pre;
        Pkt_b020_01E00920 pk;
    } buf;
    Col_b020_01E00920 col;
    s16 i;
    Pkt_b020_01E00920 *p;
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
    r.v[2] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b731_01E00110(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 2, o->bD8);
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

static void func_01E00F00_b731(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b731((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b731((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E014B0_b731(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E01810_b731(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b731:01E01C10, 202 insns: b082:01E01880 family scene timer step: at 165 five double bursts at the tracked
   point (slots 0..119), at 198 seven of one effect, at 88 two of another (cur 1 and 2), from 95 to 180 three more
   every frame, and two starters on frame 1 */

typedef struct Scn_b731_01E01C10 {
    u8 pad0[0x250];
    Vec4f org;
    u8 pad260[0xBB7C - 0x260];
    s16 id;
    u8 padBB7E[0xBC9A - 0xBB7E];
    s16 cur;
    s16 next;
    u8 padBC9E[4];
    s16 timer;
} Scn_b731_01E01C10;

static void func_01E01C10_b731(Scn_b731_01E01C10 *w) {
    extern s32 func_001F53A0();
    extern void func_001F5620();
    extern u8 b731_01E01F40[];
    extern u8 b731_01E02A00[];
    extern u8 b731_01E02EA0[];
    extern u8 b731_01E031E0[];
    extern u8 b731_01E033A0[];
    extern u8 b731_01E03520[];
    extern u8 b731_01E03840[];
    extern u8 b731_01E03A10[];
    extern u8 b731_01E03B00[];
    extern void b731_01E04780(Scn_b731_01E01C10 *w, void *data, s32 arg);
    s16 i;

    w->timer++;
    if (w->timer == 0xA5) {
        for (i = 0; i < 5; i++) {
            func_001F5620(func_001F53A0(), w->id, &w->org);
            w->cur = w->next;
            b731_01E04780(w, b731_01E01F40, 0);
            b731_01E04780(w, b731_01E02EA0, 0);
            w->next++;
            if (w->next >= 0x78) {
                w->next = 0;
            }
        }
    }
    if (w->timer == 0xC6) {
        func_001F5620(func_001F53A0(), w->id, &w->org);
        b731_01E04780(w, b731_01E03840, 0);
        b731_01E04780(w, b731_01E03840, 0);
        b731_01E04780(w, b731_01E03840, 0);
        b731_01E04780(w, b731_01E03840, 0);
        b731_01E04780(w, b731_01E03840, 0);
        b731_01E04780(w, b731_01E03840, 0);
        b731_01E04780(w, b731_01E03840, 0);
    }
    if (w->timer == 0x58) {
        w->cur = 1;
        b731_01E04780(w, b731_01E033A0, 0);
        w->cur = 2;
        b731_01E04780(w, b731_01E033A0, 0);
    }
    if (w->timer >= 0x5F && w->timer <= 0xB4) {
        func_001F5620(func_001F53A0(), w->id, &w->org);
        b731_01E04780(w, b731_01E02A00, 0);
        b731_01E04780(w, b731_01E031E0, 0);
        b731_01E04780(w, b731_01E03520, 0);
    }
    if (w->timer == 1) {
        b731_01E04780(w, b731_01E03A10, 0);
    }
    if (w->timer == 1) {
        b731_01E04780(w, b731_01E03B00, 0);
    }
}

/* shape b731:01E01F40 (B731_OBJ_MOVE_2_), 458 insns, 1 copy: b743:01E020C0 form: on start sets scene slot k to its
   position with angle (k-1)*72 + 0..143, radius 0, size 20..69; fades both alphas in by 42 for 60 ticks, then out by
   14; blinks; on tick 53 moves the scene point onto its circle and spawns ten effects; ticks 34..52 grow, turn the
   radius, slide the slot 8.5 along z and up 0.65, spawning b731:01E03840 until 51 */

typedef struct Game_b731_01E01F40 {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB1D0 - 0x260];
    Vec4f pts[(0xB98C - 0xB1D0) / 16];
    u8 padB98C[0xB98C - 0xB1D0 - 16 * ((0xB98C - 0xB1D0) / 16)];
    f32 rad[(0xBB9C - 0xB98C) / 4];
    s16 ang[(0xBC9E - 0xBB9C) / 2];
    s16 flag;
    u8 padBCA0[0xBEA4 - 0xBCA0];
    u8 trig[1];
} Game_b731_01E01F40;

typedef struct Obj_b731_01E01F40 {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 size;
    u8 pad38[0x18];
    s16 k;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b731_01E01F40;

static s32 func_01E02670_b731();
static s32 func_01E02800_b731();
static s32 func_01E02BB0_b731();
static s32 func_01E02D60_b731();
static s32 func_01E036C0_b731();
static s32 func_01E03840_b731();
static s32 func_01E04780_b731();

static s32 func_01E01F40_b731(Game_b731_01E01F40 *g, Obj_b731_01E01F40 *o) {
    extern void func_001076F0();
    extern s32 func_0019A5C8();
    extern void func_00205C40();
    extern f32 func_00108030();
    s16 k;
    s32 base = 0;

    if (o->mode == 1) {
        o->h8 = 10;
        o->hA = 10;
        o->size = func_0019A5C8() % 50 + 20;
        o->h56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        g->pts[o->k].x = o->pos.x;
        g->pts[o->k].y = o->pos.y;
        g->pts[o->k].z = o->pos.z;
        o->mode = 2;
        o->col2[3] = 0;
        if (o->k == 0) {
            g->ang[o->k] = func_0019A5C8() % 144 - 72;
        }
        if (o->k == 1) {
            g->ang[o->k] = func_0019A5C8() % 144 + base;
        }
        if (o->k == 2) {
            g->ang[o->k] = func_0019A5C8() % 144 + 72;
        }
        if (o->k == 3) {
            g->ang[o->k] = func_0019A5C8() % 144 + 144;
        }
        if (o->k == 4) {
            g->ang[o->k] = func_0019A5C8() % 144 + 216;
        }
        g->rad[o->k] = 0.0f;
    }
    if (o->t < 60) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    } else {
        if (o->col[3] > 15) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 15) {
            o->col2[3] -= 14;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    func_00205C40(o->rot);
    if (o->t == 53) {
        k = o->k;
        g->pos.x = g->pts[k].x + g->rad[k] * func_00108030(g->trig, g->ang[k], 1);
        k = o->k;
        g->pos.y = g->pts[k].y + g->rad[k] * func_00108030(g->trig, g->ang[k], 0);
        g->pos.z = g->pts[o->k].z;
        func_01E04780_b731(g, func_01E02670_b731, 0);
        func_01E04780_b731(g, func_01E02670_b731, 0);
        func_01E04780_b731(g, func_01E02670_b731, 0);
        func_01E04780_b731(g, func_01E02800_b731, 0);
        func_01E04780_b731(g, func_01E02800_b731, 0);
        func_01E04780_b731(g, func_01E02D60_b731, 0);
        func_01E04780_b731(g, func_01E02BB0_b731, 0);
        func_01E04780_b731(g, func_01E02BB0_b731, 0);
        func_01E04780_b731(g, func_01E02BB0_b731, 0);
        func_01E04780_b731(g, func_01E036C0_b731, 0);
    }
    o->t++;
    if (o->t > 33 && o->t < 53) {
        if (o->h8 < 50) {
            o->h8 += 5;
        }
        if (o->hA < 50) {
            o->hA += 5;
        }
        if (o->h5A < 180) {
            o->h5A += 10;
        }
        if (g->flag) {
            g->pts[o->k].z -= 8.5f;
        } else {
            g->pts[o->k].z += 8.5f;
        }
        g->pts[o->k].y -= 0.65f;
        k = o->k;
        g->pos.x = g->pts[k].x + g->rad[k] * func_00108030(g->trig, g->ang[k], 1);
        k = o->k;
        g->pos.y = g->pts[k].y + g->rad[k] * func_00108030(g->trig, g->ang[k], 0);
        g->pos.z = g->pts[o->k].z;
        if (o->t < 51) {
            func_01E04780_b731(g, func_01E03840_b731, 0);
        }
    }
    g->rad[o->k] = o->size * func_00108030(g->trig, o->h5A, 0);
    return 0;
}

/* shape b111:01E02160, 100 insns: spark update, a variant of b018:01E02950 (on spawn: random kind, white
   colour, angle, spin, height, speed, size and lifetime; then fade out after the lifetime, move while
   alive). b193:01E02780 is the same code with 40.0f for the first field. */

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 pos;
    u8 pad52[2];
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Spark_b193_01E02780;

static s32 func_01E02670_b731(s32 unused, Spark_b193_01E02780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 40.0f;
        o->kind = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->angle = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->pos;
        o->pos = func_0019A5C8() % 50 + 10;
        o->speed = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->limit = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 9) {
        o->alpha -= 8;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->pos += o->speed;
    }
    o->age++;
    return 0;
}

/* shape b731:01E02800, 127 insns: constant variant of b016:01E02940 (spark set-up) */

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
} Spark_b731_01E02800;

static s32 func_01E02800_b731(s32 arg0, Spark_b731_01E02800 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 30 + 25;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 350 + 300;
        o->dir = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b550:01E02BF0, 106 insns: b183:01E012F0 family: a ring that closes in (size 10, start 200..299, step 36..65 toward 0) */

typedef struct {
    u8 pad00[6];
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
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b550_01E02BF0;

static s32 func_01E02A00_b731(void *arg0, Obj_b550_01E02BF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 100 + 200;
        o->hE = func_0019A5C8() % 30 + 36;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->h50 > 0) {
            o->h50 -= o->hE;
        } else {
            o->h50 += o->hE;
        }
    }
    o->t++;
    return 0;
}

/* shape b550:01E02DA0, 105 insns: a white spark: f48 40 (+11 per tick), f50 10..59, spin 12..31, life 4..7; alpha 0xC0
   during the life, then fades by 11; f50 grows by the spin each tick after the first */

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
} Fx_b550_01E02DA0;

static s32 func_01E02BB0_b731(s32 arg0, Fx_b550_01E02DA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 50 + 10;
        o->spin = func_0019A5C8() % 20 + 12;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 4 + 4;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    o->f48 += 11.0f;
    o->tick++;
    return 0;
}

/* shape b731:01E02D60, 80 insns: a white flickering spinning flash (b550:01E02F50 shape): red flicker */

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
} Obj_b731_01E02D60;

static s32 func_01E02D60_b731(void *arg0, Obj_b731_01E02D60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 300.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0x80, 0x80);
        o->w2 = 0xF;
        o->h2 = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0xCF, 0x70, 0x70);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b731:01E02EA0, 205 insns: b550:01E03090's 70-point trail spark with b731's tables (radius 0xB98C, angle
   0xBB9C, trig 0xBEA4); alphas rise for 60 ticks, frames up to 50 */

typedef struct {
    u8 pad0[0x5A50];
    Vec4f tr[1][70];
    u8 pad5EB0[0xB1D0 - 0x5EB0];
    Vec4f pt[1];
    u8 padB1E0[0xB98C - 0xB1E0];
    f32 rad[1];
    u8 padB990[0xBB9C - 0xB990];
    s16 ang[1];
    u8 padBB9E[0xBEA4 - 0xBB9E];
    u8 trig[1];
} Ctx_b731_01E02EA0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 h8;
    u8 padA[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 k;
    u8 pad52[2];
    s16 tick;
    s16 h56;
    s16 mode;
    s16 turn;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b731_01E02EA0;

static s32 func_01E02EA0_b731(Ctx_b731_01E02EA0 *g, Fx_b731_01E02EA0 *o) {
    extern void b731_01E00080(Vec4f *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[4];
    s16 k;
    s16 i;
    Vec4f *p;

    k = o->k;
    v[0] = g->pt[k].x + g->rad[k] * func_00108030(g->trig, g->ang[k], 1);
    k = o->k;
    v[1] = g->pt[k].y + g->rad[k] * func_00108030(g->trig, g->ang[k], 0);
    v[2] = g->pt[o->k].z;
    if (o->mode == 1) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        p = g->tr[o->k];
        for (i = 0; i < 70; i++) {
            p[i].x = v[0];
            p[i].y = v[1];
            p[i].z = v[2];
        }
        o->frame = 20;
        o->col[3] = 0;
        o->h8 = 0;
        o->h56 = 4;
        o->size = 20.0f;
        o->mode = 2;
    }
    if (o->tick < 60) {
        if (o->col[3] < 0x80) {
            o->col[3] += 42;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 42;
        }
    } else if (o->size >= 0.0f) {
        o->size -= 1.5f;
    } else {
        o->mode = 0;
    }
    if (o->tick < 83) {
        o->turn += 5;
    }
    if (o->tick < 117) {
        b731_01E00080(&g->tr[o->k][69], 70, 0, v);
    }
    if (o->tick < 80) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        } else {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        }
    }
    if (o->tick != 0) {
        if (o->frame < 50) {
            o->frame++;
        }
    }
    o->tick++;
    return 0;
}

/* shape b550:01E033D0, 112 insns: b183:01E012F0 family: a slow spinning flake (random 3-axis spin, start 300..649, growth 1..3, frame 1..8, life 2..4) */


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
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b550_01E033D0;

static s32 func_01E031E0_b731(void *arg0, Obj_b550_01E033D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 1.0f;
        o->h56 = 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h52 = 1;
        o->h50 = func_0019A5C8() % 350 + 300;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    o->h52++;
    o->h50 += o->hE;
    o->t++;
    return 0;
}

/* shape b731:01E033A0, 95 insns: a red flicker glow on a model joint (b743:01E033E0 shape): size 70; alpha up by 12 until the
   scene timer reaches 215, then down by 11 until it ends; second colour flickers by frame parity; spins and follows the joint */

typedef struct {
    u8 pad0[0xBB7C];
    s16 joint[0x93];
    s16 timer;
} Game_b731_01E033A0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 jidx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b731_01E033A0;

static s32 func_01E033A0_b731(Game_b731_01E033A0 *g, Obj_b731_01E033A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->f48 = 70.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xDF, 0xDF, 0xDF);
        func_001076F0(o->c1, 0xFF, 0x80, 0x80);
        o->h5A = 0xF;
        o->h5C = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0xD7) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0xC;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0x80, 0x80);
    } else {
        func_001076F0(o->c1, 0xCF, 0x70, 0x70);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    func_001F5620(func_001F53A0(), g->joint[o->jidx], &o->pos);
    o->t++;
    return 0;
}

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
    s16 h54;
    u8 pad56[2];
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
    u8 c64[4];
} Obj_b279_01E01E80;

static s32 func_01E03520_b731(s32 unused, Obj_b279_01E01E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = 1300.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c60, 0x20, 0x20, 0x20);
        func_001076F0(o->c64, 0x20, 0x20, 0x20);
        o->h50 = 0;
        o->h5A = 15;
        o->h5C = 15;
        o->f34 = 600.0f;
        o->f34 /= 10.0f;
        o->h58 = 2;
        o->c64[3] = 0;
        o->w20 = func_0019A5C8() % 0xFFFF;
        o->w24 = func_0019A5C8() % 0xFFFF;
        o->w28 = func_0019A5C8() % 0xFFFF;
    }
    if (o->h54 < 18) {
        o->c60[3] = 0x80;
    } else if (o->c60[3] > 15) {
        o->c60[3] -= 14;
    } else {
        o->h58 = 0;
    }
    if (o->f48 > 40.0f) {
        o->f48 -= o->f34;
    }
    o->f4C = o->f48 - 300.0f;
    o->w24 += 0x100;
    o->h54++;
    return 0;
}

/* shape b550:01E03910, 93 insns, 2 copies: a fast grey column: set up once (size 20, climb 600/2 a frame, random turn on all
   axes); full for 10 frames, then fades out; its top 300 below the climb, spinning (b163:01E02130 family) */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[8];
    f32 climb;
    u8 pad38[0x10];
    f32 y;
    f32 y2;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b550_01E03910;

static s32 func_01E036C0_b731(void *arg0, Obj_b550_01E03910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->y = 20.0f;
        o->y2 = o->y - 58.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->h50 = 0;
        o->h5C = o->h5A = 0xF;
        o->climb = 600.0f;
        o->climb /= 2.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 10) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->y += o->climb;
    o->y2 = o->y - 300.0f;
    o->rot[1] += 0x100;
    o->t++;
    return 0;
}

/* shape b550:01E03A90, 116 insns, 2 copies: a growing grey glint: set up once (size 10, frame 4, random turn on all axes,
   angle 0..99, speed 10..29, life 2..4); full for its life, then fades out; turns by its speed, grows 2 a
   frame (b225:01E026A0 family, 0x58-state layout) */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 speed;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 ang;
    s16 h52;
    s16 t;
    s16 frame;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
} Spark_b550_01E03A90;

static s32 func_01E03840_b731(void *arg0, Spark_b550_01E03A90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f;
        o->frame = 4;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h52 = 1;
        o->ang = func_0019A5C8() % 100;
        o->h5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 10;
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
    o->h52++;
    o->ang += o->speed;
    o->size += 2.0f;
    o->t++;
    return 0;
}

/* shape b731:01E03A10, 60 insns: volume fade (func_001F6D00 family): starts at 0x80; drops by 10 to 0x40 for 0xD2
   ticks, then rises by 10 to 0x80 (clamped); when the game value at 0xB970 is 1 the effect stops after the call */

typedef struct {
    u8 pad0[0xB970];
    s32 v;
} Game_b731_01E03A10;

typedef struct {
    u8 pad0[0x50];
    s16 v;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
} Fx_b731_01E03A10;

static s32 func_01E03A10_b731(Game_b731_01E03A10 *g, Fx_b731_01E03A10 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0xD2) {
        if (o->v > 0x40) {
            o->v -= 10;
        } else {
            o->v = 0x40;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    o->tick++;
    if (g->v == 1) {
        func_001F6D00(o->v);
        o->mode = 0;
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b731:01E03B00, 106 insns: a pink-grey full-screen veil (b215:01E02390 shape): one sprite over the whole screen at the
   object alpha, sent at once; alpha up by 10 to 0x50 until frame 244, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b731_01E03B00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b731_01E03B00 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b731_01E03B00;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b731_01E03B00;

static s32 func_01E03B00_b731(void *arg0, Obj_b731_01E03B00 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    Pkt_b731_01E03B00 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->f48 = 0.0f;
        o->state = 2;
    }
    ((Pkt_b731_01E03B00 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b731_01E03B00 *)(s32)&pkt)->tag = 5;
    ((Pkt_b731_01E03B00 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b731_01E03B00 *)(s32)&pkt)->pad = 0;
    pkt.r = 0x80;
    pkt.g = 0x60;
    pkt.b = 0x70;
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b731_01E03B00 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (o->t < 0xF4) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0xA;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b731", func_01E03CB0_b731);

/* shape b731:01E04780, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0xc8 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b731_01E04780 {
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
} Slot_b731_01E04780;

typedef struct Obj_b731_01E04780 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b731_01E04780 slots[0xc8];
    u8 padB[0xb974 - 0x2a0 - 0xc8 * 0x70];
    u8 rgba[4];
    u8 padC[0xbc9a - 0xb974 - 4];
    s16 fB2B0;
} Obj_b731_01E04780;

static s32 func_01E04780_b731(Obj_b731_01E04780 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b731_01E04780 *s = NULL;
    s16 i;

    for (i = 0; i < 0xc8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xc8;
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

INCLUDE_ASM("asm/nonmatchings/mod/b731", func_01E04910_b731);

/* shape b139:01E03820: sibling of b016:01E00ED0 (one sprite quad, drawn twice). Needs func_01E00110_b731 in the
   same file and static (the original reuses $a0 across the call). */

typedef struct Cam_b139_01E03820 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b139_01E03820;

typedef struct Obj_b139_01E03820 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b139_01E03820;

typedef struct Xyz_b139_01E03820 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b139_01E03820;

typedef struct Uv_b139_01E03820 {
    f32 u, v;
} Uv_b139_01E03820;

typedef struct Pk_b139_01E03820 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b139_01E03820 uv;
    u64 pad18;
    Xyz_b139_01E03820 v[4];
    u64 pad60[6];
} Pk_b139_01E03820;

typedef struct Buf_b139_01E03820 {
    u64 tag;
    Pk_b139_01E03820 pk;
} Buf_b139_01E03820;

static void func_01E05450_b731(Obj_b139_01E03820 *obj, Cam_b139_01E03820 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b139_01E03820 buf;
    Uv_b139_01E03820 uv;
    s32 sel;
    s32 mode;
    Pk_b139_01E03820 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00110_b731((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
            func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
        } else if (mode == 1) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0((s32)p, obj->f80, 0);
            func_002075F0((s32)p, obj->f80, 0);
        } else {
            func_002075F0((s32)p, obj->f80, -1);
            func_002075F0((s32)p, obj->f80, -1);
        }
    }
}
