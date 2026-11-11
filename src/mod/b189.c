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

static void func_01E00080_b189(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b082:01E00920, 280 insns, 18 copies: draws a full ring of 36 segments (10 table steps each) between an
   inner and an outer radius around a position (passed by value); blend from flags >> 4, depth mode flags & 0xF */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b108_01E009A0;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 inner;
    f32 outer;
    u8 pad50[0x0A];
    s16 step;
    u8 pad5C[4];
    u8 mode0[4];
    u8 mode1[4];
} Data_b108_01E009A0;

static void func_01E00920_b189(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 packet[0x90];
    s32 i;
    f32 inner;
    s16 j;
    s16 alpha;
    f32 outer;
    u8 *pkt;
    s32 a;
    s32 mode;

    pkt = packet;
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
    t.x = pos.x;
    scale.y = 0.1f;
    t.y = pos.y;
    scale.z = 0.1f;
    t.z = pos.z;
    func_00108EF0(m, &scale, &data->rot, &t);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    mode = flags & 0xF;
    inner = data->inner;
    i = 0;
    outer = data->outer;
    do {
        if (i == 0) {
            a = data->step + j;
            quad[0].x = inner * func_00108030(o->table, a, 1);
            quad[0].z = inner * func_00108030(o->table, a, 0);
            quad[2].x = outer * func_00108030(o->table, a, 1);
            quad[2].z = outer * func_00108030(o->table, a, 0);
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            a = j + (data->step + 10);
            quad[1].x = inner * func_00108030(o->table, a, 1);
            quad[1].z = inner * func_00108030(o->table, a, 0);
            quad[3].x = outer * func_00108030(o->table, a, 1);
            quad[3].z = outer * func_00108030(o->table, a, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_002075F0(pkt, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, o->ot, 0);
            }
        } else if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
            func_002075F0(pkt, o->ot, -1);
        }
        j += 10;
        i++;
    } while (i < 36);
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

static void func_01E00D70_b189(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b189((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b189((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E01320_b189(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

static void func_01E01720_b189(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b189 in the
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

static void func_01E01A80_b189(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b189((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b189:01E01D40, 339 insns: B189_W_S, the scene script: counts the scene frame (0x4530); before frame 120 the
   carried point (0x4470) rides 5 above the first joint, from frame 105 it is thrown back along its line to the
   second joint (falling 0.1 * t sideways by the side flag); on 120 it aims at the target joint, flies there on frames
   126..141, bursts on 142 and 164; sparks at the second joint on odd frames 125..135, trails behind it on 51..162 /
   65..162, the extra one on 55, and the spin (0x4518) +7 a frame on 61..74 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f p;
    u8 pad0260[0x4470 - 0x260];
    Vec4f pos;
    Vec4f step;
    Vec4f back;
    u8 pad44A0[0x44E4 - 0x44A0];
    f32 t;
    u8 pad44E8[0x10];
    s16 j0;
    u8 pad44FA[2];
    s16 j1;
    u8 pad44FE[0xA];
    s16 j2;
    u8 pad450A[0xE];
    s16 spin;
    u8 pad451A[0xE];
    s16 kind;
    u8 pad452A[2];
    s16 side;
    u8 pad452E[2];
    s16 frame;
} Ctx_b189_01E01D40;

static void func_01E01D40_b189(Ctx_b189_01E01D40 *g) {
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void b189_01E03A40();
    extern s32 b189_01E02290();
    extern s32 b189_01E023E0();
    extern s32 b189_01E02560();
    extern s32 b189_01E02850();
    extern s32 b189_01E02990();
    extern s32 b189_01E02B00();
    extern s32 b189_01E02D00();
    extern s32 b189_01E02EA0();
    f32 v[8];
    s16 i;

    g->frame++;
    if (g->frame < 120) {
        func_001F5620(func_001F53A0(), g->j0, &g->pos);
        g->pos.y += 5.0f;
        if (g->frame == 105) {
            func_001F5620(func_001F53A0(), g->j1, v);
            g->back.y = (g->pos.y - v[1]) / 15.0f;
            g->back.x = (g->pos.x - v[0]) / 15.0f;
        }
        if (g->frame >= 105) {
            g->pos.x -= g->back.x * g->t;
            g->pos.y -= g->back.y * g->t;
            if (g->side != 0) {
                g->pos.z -= (f32)(0.1 * g->t);
            } else {
                g->pos.z += (f32)(0.1 * g->t);
            }
            g->t += 1.0f;
        }
    } else {
        if (g->frame == 120) {
            func_001F5620(func_001F5380(), g->j2, v);
            g->step.z = (v[2] - g->pos.z) / 16.0f;
            g->step.y = (v[1] - g->pos.y) / 16.0f;
            g->step.x = (v[0] - g->pos.x) / 16.0f;
        }
        if (g->frame > 125 && g->frame < 142) {
            g->pos.z += g->step.z;
            g->pos.y += g->step.y;
            g->pos.x += g->step.x;
        }
    }
    if (g->frame == 142) {
        g->p = g->pos;
        g->kind = 0;
        for (i = 0; i < 10; i++) {
            b189_01E03A40(g, b189_01E02B00, 0);
        }
        b189_01E03A40(g, b189_01E02850, 0);
    }
    if (g->frame == 164) {
        g->p = g->pos;
        g->kind = 1;
        for (i = 0; i < 10; i++) {
            b189_01E03A40(g, b189_01E02EA0, 0);
        }
        for (i = 0; i < 10; i++) {
            b189_01E03A40(g, b189_01E02D00, 0);
        }
        b189_01E03A40(g, b189_01E02850, 0);
    }
    if (g->frame >= 125 && g->frame < 136) {
        func_001F5620(func_001F53A0(), g->j1, &g->p);
        if (g->side != 0) {
            g->p.z -= 5.0f;
        } else {
            g->p.z += 5.0f;
        }
        if (g->frame % 2 == 1) {
            b189_01E03A40(g, b189_01E02290, 0);
        }
    }
    if (g->frame >= 65 && g->frame < 163) {
        g->p = g->pos;
        b189_01E03A40(g, b189_01E023E0, 0);
    }
    if (g->frame > 50 && g->frame < 163) {
        g->p = g->pos;
        b189_01E03A40(g, b189_01E02560, 0);
        if (g->frame == 55) {
            b189_01E03A40(g, b189_01E02990, 0);
        }
    }
    if (g->frame > 60 && g->frame < 75) {
        g->spin += 7;
    }
}

/* shape b163:01E02130, 82 insns, 2 copies: a rising red column: set up once (size 50, climb 400/10 a frame, random turn);
   full for 8 frames, then fades out; its top follows 50 below the climb (b016:01E026B0 family) */

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
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b163_01E02130;

static s32 func_01E02290_b189(void *arg0, Obj_b163_01E02130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->y = 50.0f;
        o->y2 = o->y - 50.0f;
        func_001076F0(o->c0, 0xFF, 0xC0, 0xC0);
        func_001076F0(o->c1, 0xFF, 0xC0, 0xC0);
        o->h50 = 0;
        o->h5C = o->h5A = 0xF;
        o->h56 = 4;
        o->climb = 400.0f;
        o->climb /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = 0x4000;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->climb;
        o->y2 = o->y - 50.0f;
    }
    o->t++;
    return 0;
}

/* shape b163:01E02280, 95 insns, 3 copies: step of a small purple spark: on state 1 sets size 10, its colour, random
   angle, phase, height, speed and lifetime; full alpha while young, then fades by 8 until it ends. */

typedef struct {
    u8 pad00[6];
    s16 life;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 speed;
    u8 pad10[0x38];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 h56;
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
} Obj_b163_01E02280;

static s32 func_01E023E0_b189(void *arg0, Obj_b163_01E02280 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f;
        o->h56 = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x40, 0x20, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->speed = func_0019A5C8() % 10 + 6;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b189:01E02560, 103 insns: a grey-red flicker flash (b406:01E027F0 shape): size 10 plus 0..the scene range, growing by 1
   once started; alpha up by 0x30 to 0x60 for 2 frames, then down by 11 until it ends; second colour flickers red; spins */

typedef struct {
    u8 pad0[0x4518];
    s16 range;
} Game_b189_01E02560;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
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
} Obj_b189_01E02560;

static s32 func_01E02560_b189(Game_b189_01E02560 *g, Obj_b189_01E02560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f + (f32)(func_0019A5C8() % g->range);
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0x68, 0x68, 0x68);
        func_001076F0(o->c1, 0x80, 0x40, 0x40);
        o->h5A = 0xF;
        o->h5C = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 0x30;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0x80, 0x20, 0x20);
    } else {
        func_001076F0(o->c1, 0x40, 0x20, 0x20);
    }
    if (o->t != 0) {
        o->size += 1.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b189:01E02700, 84 insns, 3 copies: step of a blinking flash (variant of shape b547:01E02400): size 100, second
   colour blinks red every other tick; fades in by 0x40 until tick 186, then out by 14; spins a quarter turn. */

typedef struct {
    u8 pad00[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b189_01E02700;

static s32 func_01E02700_b189(void *arg0, Obj_b189_01E02700 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 100.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 8, 8);
    } else {
        func_001076F0(o->c1, 0xC0, 8, 8);
    }
    if (o->t < 186) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b189:01E02850, 77 insns: a white-red growing spinning flash (b163:01E026F0 shape) */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b189_01E02850;

static s32 func_01E02850_b189(void *arg0, Obj_b189_01E02850 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        if (o->kind == 0) {
            o->f48 = 250.0f;
        }
        if (o->kind == 1) {
            o->f48 = 300.0f;
        }
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0x40, 0x40);
        o->w = 0xF;
        o->h = 0xF;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xC) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->f48 += 1.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b189:01E02990, 90 insns: a grey growing spark (b163:01E02830 shape): alphas up for 130 frames */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    s16 hE;
    u8 pad10[4];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b189_01E02990;

static s32 func_01E02990_b189(void *arg0, Obj_b189_01E02990 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 5;
        o->h = 5;
        o->sub = 3;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        func_001076F0(o->c1, 0x40, 0x40, 0x40);
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x82) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 0xF) {
            o->c0[3] -= 0xE;
        }
    }
    if (o->sub == 3) {
        o->sub = 5;
    } else {
        o->sub = 3;
    }
    if (o->t != 0) {
        if (o->w < 0x1E) {
            o->w++;
        }
        if (o->h < 0x1E) {
            o->h++;
        }
    }
    func_00205C40((s32)o->rot);
    o->t++;
    return 0;
}

/* shape b189:01E02B00, 127 insns: b203:01E03140 family dark grey flash swinging on a sine: f48 = 600 sin(h50) (f4C 400 below), h50 stepping 8 up to 90 then 6; full alpha 20 ticks, ends when f48 drops under 80; past 90 alpha falls by 7 */

typedef struct {
    u8 pad0[0x4734];
    u8 tab[1];
} Ctx_b189_01E02B00;

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
} Obj_b189_01E02B00;

static s32 func_01E02B00_b189(Ctx_b189_01E02B00 *g, Obj_b189_01E02B00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->f48 = 100.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        func_001076F0(o->c1, 0x20, 0x20, 0x20);
        o->h50 = 0;
        o->sub = func_0019A5C8() % 8;
        o->w = 0xF;
        o->h = 0xA;
        o->f34 = 250.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot0 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 20) {
        o->c0[3] = 0x80;
    } else if (o->f48 < 80.0f) {
        o->state = 0;
    }
    o->f48 = 600.0f * func_00108030(g->tab, o->h50, 0);
    o->f4C = o->f48 - 400.0f;
    if (o->h50 > 90) {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        }
    }
    if (o->h50 < 90) {
        o->h50 += 8;
    } else {
        o->h50 += 6;
    }
    o->t++;
    return 0;
}

/* shape b189:01E02D00, 102 insns: b593:01E020C0 twin: a red spark (size 20, random frame 0..3) */

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
} Obj_b189_01E02D00;

static s32 func_01E02D00_b189(s32 arg0, Obj_b189_01E02D00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0x40, 0x40);
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

/* shape b189:01E02EA0, 127 insns: constant variant of b016:01E02940 (spark set-up) */

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
} Spark_b189_01E02EA0;

static s32 func_01E02EA0_b189(s32 arg0, Spark_b189_01E02EA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 20 + 10;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xCF, 0x50, 0x80);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 400 + 500;
        o->dir = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->delay = func_0019A5C8() % 8 + 1;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x70;
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b163:01E02280, 95 insns, 3 copies: step of a small purple spark: on state 1 sets size 10, its colour, random
   angle, phase, height, speed and lifetime; full alpha while young, then fades by 8 until it ends. */

static s32 func_01E030A0_b189(void *arg0, Obj_b163_01E02280 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f;
        o->h56 = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x40, 0x20, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->speed = func_0019A5C8() % 10 + 6;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->life) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03220_b189(void) {
    return 0;
}

/* shape b189:01E03230 (b189), 515 insns, 1 copy: b189 scene manager in b402:01E02CE0 form: setup (camera and six
   joints, textures (4,14..15), three type-5 textures, s8 jitter tables: first 256 at +-15 then 100..179 rand%4,
   second 256 at +-20), step b189:01E01D40 and every slot (150 of 0x70) but the empty b189:01E03220, draw the
   02290/02B00 bands, 023E0/02D00/02EA0 sprites, 02560/02850 and 02990 flashes, 02700/030A0 rings; scene code from the
   timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b189_01E03230;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
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
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b189_01E03230 fx[150];
    u8 pad4440[0x30];
    Vec4f v4470;
    u8 pad4480[0x20];
    s32 tex2[3];
    u8 pad44AC[0x14];
    s32 count;
    u8 pad44C4[8];
    s32 ot;
    u8 pad44D0[0x28];
    s16 j[6];
    u8 pad4504[4];
    s16 cam;
    u8 pad450A[0xE];
    s16 h4518;
    u8 pad451A[0x12];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad4732[2];
    u8 crd[0x16C];
} Scene_b189_01E03230;

static s32 func_01E03230_b189(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern void func_01E01D40_b189();
    Scene_b189_01E03230 *g = (Scene_b189_01E03230 *)arg0;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x48A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 220;
        g->j[0] = func_001F5560(func_001F53A0(), 0x36, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x34, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x43, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex2[i] = func_00202BF0(5, i);
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
        g->h4518 = 1;
        return 0;
    }
    func_01E01D40_b189(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E03220_b189) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E02290_b189) {
                func_00106080(rm, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex[15];
                g->u94.uv[3] >>= 1;
                g->hB8 = 0x18;
                func_01E01320_b189(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E023E0_b189) {
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[1];
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00D70_b189(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02560_b189) {
                g->hB8 = 0x18;
                func_01E01720_b189(g, &g->fx[k], 0x21, &g->v4470);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02700_b189) {
                v = g->v4470;
                func_01E00920_b189(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02850_b189) {
                g->hB8 = 0x18;
                func_01E01720_b189(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02990_b189) {
                g->tex88 = g->tex2[2];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hBE = 5;
                v = g->v4470;
                func_01E01A80_b189(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B00_b189) {
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->tex88 = g->tex2[0];
                g->hB8 = 0x18;
                func_01E01320_b189(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D00_b189) {
                g->tex88 = g->tex[15];
                func_00106080(rm5, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm5;
                g->hB8 = 5;
                g->hB0 = 0;
                func_01E00D70_b189(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02EA0_b189) {
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm6;
                g->tex88 = g->tex2[0];
                g->hB8 = 10;
                g->hB0 = 1;
                func_01E00D70_b189(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E030A0_b189) {
                v = g->fx[k].pos;
                func_01E00920_b189(g, &g->fx[k], 0x20, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 132) {
        return 1;
    }
    if (g->frame == 205) {
        return 4;
    }
    if (g->frame == 185) {
        return 2;
    }
    if (g->frame > 142 && g->frame < 180) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}


/* shape b163:01E03CD0, 80 insns, 2 copies: spawns an effect into the first free slot (150 of 0x70 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 w40;
    s32 w44;
    u8 pad48[8];
    s16 h50;
    u8 pad52[6];
    s16 active;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b163_01E03CD0;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b163_01E03CD0 slot[150];
    u8 pad4500[0x44C4 - 0x2A0 - 150 * 0x70];
    u8 col[4];
    u8 pad44C8[0x60];
    s16 h4528;
} Scene_b163_01E03CD0;

static s32 func_01E03A40_b189(Scene_b163_01E03CD0 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b163_01E03CD0 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 150;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->h4528;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}
