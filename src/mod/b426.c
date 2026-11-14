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

static void func_01E00080_b426(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b426(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

/* shape b203:01E00D70, 362 insns, 6 copies: twin of b016:01E00920 (x[2] = cam->f5A, func_00108950 mode 2). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b203_01E00D70 {
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
} Cam_b203_01E00D70;

typedef struct Obj_b203_01E00D70 {
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
} Obj_b203_01E00D70;

typedef struct Uv_b203_01E00D70 {
    f32 u, v;
} Uv_b203_01E00D70;

typedef struct Xyz_b203_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b203_01E00D70;

typedef struct Pk_b203_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b203_01E00D70 uv;
    u64 pad18;
    Xyz_b203_01E00D70 v[4];
    u64 pad60[6];
} Pk_b203_01E00D70;

typedef struct Buf_b203_01E00D70 {
    u64 tag;
    Pk_b203_01E00D70 pk;
} Buf_b203_01E00D70;

static void func_01E00D70_b426(Obj_b203_01E00D70 *obj, Cam_b203_01E00D70 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b203_01E00D70 *p;
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
    Buf_b203_01E00D70 buf;
    Uv_b203_01E00D70 uv;

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
    func_01E00080_b426((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
    x[2] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00080_b426((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
            func_00108950(out, x, 2, obj->fD8);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b426 in the
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

static void func_01E01320_b426(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b426((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b390:01E015E0 (IWMagicCircleGT4_2), 316 insns, 2 copies: b016:01E014F0's ring of bands, flat (y 0), each
   corner turned by the object's two angles (func_00108BE0); start angle 180 unless o->fB0 (c061:01E01100's form) */

typedef struct Cam_b390_01E015E0 {
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
} Cam_b390_01E015E0;

typedef struct Obj_b390_01E015E0 {
    u8 pad0[0x20];
    f32 f20;
    f32 f24;
    u8 pad28[0x58];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x1C];
    s16 fB0;
    u8 padB2[6];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b390_01E015E0;

typedef struct Uv_b390_01E015E0 {
    f32 u, v;
} Uv_b390_01E015E0;

typedef struct Vtx_b390_01E015E0 {
    Uv_b390_01E015E0 st;
    u64 rgba;
    u64 xyz;
} Vtx_b390_01E015E0;

typedef struct Pk_b390_01E015E0 {
    u8 hdr[0x10];
    Vtx_b390_01E015E0 v[4];
    u8 pad70[0x20];
} Pk_b390_01E015E0;

static void func_01E015E0_b426(Obj_b390_01E015E0 *o, Cam_b390_01E015E0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109270();
    extern Vec4f func_00108BE0(Vec4f *, s32, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    s32 k;
    s16 b;
    s16 span;
    s16 a;
    Pk_b390_01E015E0 *p;
    s32 t;
    f32 w0;
    f32 w1;

    Vec4f pts[4];
    Vec4f p2;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    Pk_b390_01E015E0 pk;
    Uv_b390_01E015E0 uv0;
    Uv_b390_01E015E0 uv1;
    Uv_b390_01E015E0 uv2;
    Uv_b390_01E015E0 uv3;

    p = &pk;
    span = cam->n;
    a = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    b = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)b << 2) | (((u64)0x80 << 32) | 0x40));
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
    s.y = 0.1f;
    s.z = 0.1f;
    p2.x = c.x;
    p2.y = c.y;
    p2.z = c.z;
    func_00108EF0(m, &s, NULL, &p2);
    w0 = cam->w0;
    w1 = cam->w1;
    if (o->fB0 == 0) {
        a = 180;
    } else {
        a = 0;
    }
    for (k = 0; k < o->count; k++) {
        pts[0].y = 0.0f;
        pts[1].y = 0.0f;
        pts[2].y = 0.0f;
        pts[3].y = 0.0f;
        t = a;
        pts[0].x = w0 * func_00108030(o->table, t, 1);
        pts[0].z = w0 * func_00108030(o->table, t, 0);
        pts[2].x = w1 * func_00108030(o->table, t, 1);
        pts[2].z = w1 * func_00108030(o->table, t, 0);
        t = span + a;
        pts[1].x = w0 * func_00108030(o->table, t, 1);
        pts[1].z = w0 * func_00108030(o->table, t, 0);
        pts[3].x = w1 * func_00108030(o->table, t, 1);
        pts[3].z = w1 * func_00108030(o->table, t, 0);
        pts[0] = func_00108BE0(&pts[0], 1, o->f24, o->f20);
        r1 = func_00108BE0(&pts[1], 1, o->f24, o->f20);
        pts[1] = r1;
        r2 = func_00108BE0(&pts[2], 1, o->f24, o->f20);
        pts[2] = r2;
        r3 = func_00108BE0(&pts[3], 1, o->f24, o->f20);
        pts[3] = r3;
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
        a += cam->step;
    }
}

/* shape b426:01E01AD0, 223 insns: b731:01E01C10 family scene step with homing points: each new point (age 0) aims at
   the camera point jittered by +-10 and sets its step to a 50th of the gap (the y and twice the z; x is never set);
   live points move by their step while young (age < 25) or aged 126..148; at scene times 83, 120, 154, 183, 216
   and 246 a new point starts at the tracked joint (0x5324) with two bursts and a ring of 18 (angles 0, 20, ..),
   and from 60 to 80 one more effect each frame */

typedef struct Scn_b426_01E01AD0 {
    u8 pad0[0x250];
    Vec4f org;
    u8 pad260[0x5190 - 0x260];
    Vec4f pos[10];
    Vec4f vel[10];
    u8 pad52D0[0x5324 - 0x52D0];
    s16 joint;
    u8 pad5326[0xE];
    s16 cam;
    u8 pad5336[0xE];
    s16 age[17];
    s16 cur;
    s16 count;
    u8 pad536A[4];
    s16 timer;
} Scn_b426_01E01AD0;

static void func_01E01AD0_b426(Scn_b426_01E01AD0 *g) {
    extern s32 func_001F53A0();
    extern s32 func_001F5380();
    extern void func_001F5620();
    extern u8 b426_01E01E50[];
    extern u8 b426_01E02370[];
    extern u8 b426_01E031D0[];
    extern u8 b426_01E03530[];
    extern void b426_01E04630(Scn_b426_01E01AD0 *w, void *data, s32 arg);
    f32 p[8];
    s16 i;
    s16 a;
    s16 k;

    g->timer++;
    for (i = 0; i < g->count; i++) {
        if (g->age[i] == 0) {
            func_001F5620(func_001F5380(), g->cam, p);
            p[0] += func_0019A5C8() % 20 - 10;
            p[1] += func_0019A5C8() % 20 - 10;
            g->vel[i].z = (p[2] - g->pos[i].z) / 50.0f;
            g->vel[i].y = (p[1] - g->pos[i].y) / 50.0f;
            g->vel[i].z = (p[2] - g->pos[i].z) / 50.0f;
            g->age[i]++;
        }
    }
    for (i = 0; i < g->count; i++) {
        if (g->age[i] != 0) {
            if (g->age[i] < 25 || (g->age[i] > 125 && g->age[i] < 149)) {
                g->pos[i].z += g->vel[i].z;
                g->pos[i].y += g->vel[i].y;
                g->pos[i].x += g->vel[i].x;
                g->age[i]++;
            } else {
                g->age[i]++;
            }
        }
    }
    if (g->timer == 0x53 || g->timer == 0x78 || g->timer == 0x9A || g->timer == 0xB7 || g->timer == 0xD8 ||
        g->timer == 0xF6) {
        g->cur = g->count;
        func_001F5620(func_001F53A0(), g->joint, &g->pos[g->cur]);
        func_001F5620(func_001F53A0(), g->joint, &g->org);
        b426_01E04630(g, b426_01E02370, 0);
        b426_01E04630(g, b426_01E01E50, 0);
        for (k = 0, a = 0; k < 18; k++) {
            g->cur = a;
            b426_01E04630(g, b426_01E031D0, 0);
            a += 20;
        }
        g->count++;
    }
    if (g->timer >= 60 && g->timer < 81) {
        func_001F5620(func_001F53A0(), g->joint, &g->org);
        b426_01E04630(g, b426_01E03530, 0);
    }
}

/* shape b426:01E01E50, 94 insns: a grey flickering spark (frame toggles 0/1) growing 10 a tick from 25 up to 75: both alphas in by 64 up to 0xC0 for 149 ticks, then out by 14 (twice on the first colour) and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
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
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b426_01E01E50;

static s32 func_01E01E50_b426(s32 arg0, Obj_b426_01E01E50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h8 = 25;
        o->hA = 25;
        o->kind = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 149) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
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
    if (o->kind != 0) {
        o->kind = 0;
    } else {
        o->kind = 1;
    }
    if (o->t != 0) {
        if (o->h8 < 75) {
            o->h8 += 10;
        }
        if (o->hA < 75) {
            o->hA += 10;
        }
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b390:01E02040, 103 insns: a white spark (like b390:01E030F0): f48 30, f50 10..29, spin 16..45; alpha 0x80 during
   the life, then fades by 8; f5A steps by 1 and f50 grows by the spin each tick after the first */

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
} Fx_b390_01E02040;

static s32 func_01E01FD0_b426(s32 arg0, Fx_b390_01E02040 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 30.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 20 + 10;
        o->spin = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    o->f5A++;
    if (o->tick != 0) {
        o->f50 += o->spin;
    }
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[0x10];
    s32 seed[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 pos;
    s16 frame;
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Mote_b111_01E022F0;

static s32 func_01E02170_b426(s32 unused, Mote_b111_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 5 + 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x30, 0x30);
        o->seed[0] = func_0019A5C8() % 0xFFFF;
        o->seed[1] = func_0019A5C8() % 0xFFFF;
        o->seed[2] = func_0019A5C8() % 0xFFFF;
        o->frame = 1;
        o->pos = func_0019A5C8() % 30 + 10;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->limit = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x60;
    } else if (o->alpha > 12) {
        o->alpha -= 11;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b426:01E02370, 216 insns: b390:01E023E0 cousin: grey with a yellow second colour flickering to dull on even
   ticks, 0xE = 1..10, alpha up for 149 ticks; at tick 149 it spawns ten 0x1E02BA0, ten 0x1E01FD0 and 0x1E02880 at its
   point (ctx+0x5190 table); from tick 7 to 12 (outside 25..125) every 0xE-th tick 0x1E02DA0; before tick 149, outside
   ticks 25..125, 0x1E02EB0 and 0x1E03050 there each tick */

typedef struct {
    f32 x, y, z, w;
} V_b426_01E02370;

typedef struct {
    u8 pad0[0x250];
    V_b426_01E02370 pos;
    u8 pad260[0x5190 - 0x260];
    V_b426_01E02370 pts[1];
} Game_b426_01E02370;

typedef struct {
    u8 pad0[0xE];
    s16 fE;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 pt;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b426_01E02370;

static s32 func_01E02370_b426(Game_b426_01E02370 *g, Fx_b426_01E02370 *o) {
    extern s32 b426_01E01FD0(void);
    extern s32 b426_01E02880(void);
    extern s32 b426_01E02BA0(void);
    extern s32 b426_01E02DA0(void);
    extern s32 b426_01E02EB0(void);
    extern s32 b426_01E03050(void);
    extern s32 b426_01E04630(Game_b426_01E02370 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->f48 = 100.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 8);
        o->f5A = func_0019A5C8() % 360;
        o->fE = func_0019A5C8() % 10 + 1;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x80, 8);
    } else {
        func_001076F0(o->col2, 0x60, 0x60, 8);
    }
    if (o->tick < 149) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick == 149) {
        g->pos = g->pts[o->pt];
        for (i = 0; i < 10; i++) {
            b426_01E04630(g, b426_01E02BA0, 0);
        }
        for (i = 0; i < 10; i++) {
            b426_01E04630(g, b426_01E01FD0, 0);
        }
        b426_01E04630(g, b426_01E02880, 0);
    }
    if (o->tick > 6 && o->tick < 13 && (o->tick < 25 || o->tick > 125) && o->tick % o->fE == 1) {
        g->pos = g->pts[o->pt];
        b426_01E04630(g, b426_01E02DA0, 0);
    }
    if (o->tick < 149) {
        if (o->tick < 25 || o->tick > 125) {
            g->pos = g->pts[o->pt];
            b426_01E04630(g, b426_01E02EB0, 0);
            b426_01E04630(g, b426_01E03050, 0);
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b426:01E026D0, 105 insns: a grey/red tumbling column (three random turns, random angle) growing 8.5 a tick (4.5 once the scene value reaches 200), its tail 4 behind: in by 64 up to 0xC0 for 10 ticks, then out by 14 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b426_01E026D0;

typedef struct {
    u8 pad[0x536E];
    s16 val;
} Game_b426_01E026D0;

static s32 func_01E026D0_b426(Game_b426_01E026D0 *g, Obj_b426_01E026D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 10) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (g->val < 200) {
        o->f48 += 8.5f;
        o->f4C = o->f48 - 4.0f;
    } else {
        o->f48 += 4.5f;
        o->f4C = o->f48 - 4.0f;
    }
    o->t++;
    return 0;
}

/* shape b426:01E02880, 84 insns: b390:01E028D0 family: a pink glow of size 500, its second colour blinking yellow, at a random angle, spun 0x4000 a tick: in by 64 up to 0xC0 for 4 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b426_01E02880;

static s32 func_01E02880_b426(s32 arg0, Obj_b426_01E02880 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 500.0f;
        func_001076F0(o->col, 0xFF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x80, 0x80, 8);
    } else {
        func_001076F0(o->col2, 0xC0, 0xC0, 8);
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b111:01E02A10, 113 insns, 3 copies: step of a blinking flash (b547:01E02400 family): size 100; the second
   colour blinks red (mode 0) or blue (mode 1) every other tick; fades in by 0x40 for 4 ticks, then out by 9;
   spins a quarter turn. */

typedef struct {
    u8 pad00[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 mode;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b111_01E02A10;

static s32 func_01E029D0_b426(void *arg0, Obj_b111_01E02A10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 100.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->mode == 0) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 0x80, 8, 8);
        } else {
            func_001076F0(o->c1, 0xC0, 8, 8);
        }
    } else if (o->mode == 1) {
        if (o->t % 2 == 1) {
            func_001076F0(o->c1, 8, 8, 0x80);
        } else {
            func_001076F0(o->c1, 8, 8, 0xC0);
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b426:01E02BA0, 127 insns: constant variant of b016:01E02940 (spark set-up) */

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
} Spark_b426_01E02BA0;

static s32 func_01E02BA0_b426(s32 arg0, Spark_b426_01E02BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 10 + 10;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xC0, 0xC0, 0x50);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 200 + 200;
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

/* shape b426:01E02DA0, 66 insns: on start f48 20, colour 0xCF grey, second colour (0x80, 0x80, 8) with alpha 0,
   random 0x5A, rotation 0x4000; alpha grows by 0x40 (below 0xC0) for 13 ticks, then fades by 9 and stops; f48 grows
   by 20 each tick and f4C = 20 + f48 */

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b426_01E02DA0;

static s32 func_01E02DA0_b426(s32 arg0, Fx_b426_01E02DA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 0x80, 8);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot = 0x4000;
    }
    if (o->tick < 0xD) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f48 += 20.0f;
    o->f4C = 20.0f + o->f48;
    o->tick++;
    return 0;
}

/* shape b426:01E02EB0, 103 insns: a yellow spark (150 x 150 shrinking 15 a tick to 20, random frame 0..7, random angle and tilt -90..89): both alphas in by 64 up to 0xC0 for 3 ticks, then out by 14 (twice on the first) and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[0x14];
    s32 w20;
    u8 pad24[0x10];
    s32 w34;
    u8 pad38[0x1C];
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b426_01E02EB0;

static s32 func_01E02EB0_b426(s32 arg0, Obj_b426_01E02EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->h8 = 150;
        o->hA = 150;
        o->kind = func_0019A5C8() % 8;
        o->w34 = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        func_001076F0(o->col2, 0xFF, 0xFF, 0x80);
        o->mode = 2;
        o->col2[3] = 0;
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 180 - 90;
    }
    if (o->t < 3) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
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
    if (o->t != 0) {
        if (o->h8 > 20) {
            o->h8 -= 15;
        }
        if (o->hA > 20) {
            o->hA -= 15;
        }
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b390:01E030F0, 96 insns: a grey spark: on start f48 10, random variant 0..6, random f5A, fA -7..7,
   fC = the old f50, f50 10..89, spin 16..45, f8 0..34, life 2..4; alpha 0x80 during the life, then fades out by 8
   and stops; f5A steps by 1 each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[0x10];
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
} Fx_b390_01E030F0;

static s32 func_01E03050_b426(s32 arg0, Fx_b390_01E030F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 80 + 10;
        o->spin = func_0019A5C8() % 30 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    o->f5A++;
    o->tick++;
    return 0;
}

/* shape b426:01E031D0, 143 insns: b144:01E02750 with the sine table at m+0x5670, yellow colours, drift in x/y and a
   height swing of 2 x sin(h5A) up or down by the manager flag at m+0x536A */

typedef struct {
    u8 pad0000[0x536A];
    s16 up;
    u8 pad536C[0x304];
    u8 tab[1];
} Mgr_b426_01E031D0;

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
    f32 f34;
    u8 pad38[0x18];
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
} Obj_b426_01E031D0;

static s32 func_01E031D0_b426(Mgr_b426_01E031D0 *m, Obj_b426_01E031D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 150;
        o->hA = 150;
        o->h56 = func_0019A5C8() % 8;
        o->f30 = 3.5f * func_00108030(m->tab, o->h50, 1);
        o->f34 = 3.5f * func_00108030(m->tab, o->h50, 0);
        func_001076F0(o->c60, 0xFF, 0xFF, 0x80);
        func_001076F0(o->c64, 0xFF, 0xFF, 0x80);
        o->h58 = 2;
        o->c64[3] = 0;
        o->h5A = 0;
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
        o->f14 += o->f34;
        if (m->up != 0) {
            o->f18 += 2.0f * func_00108030(m->tab, o->h5A, 0);
        } else {
            o->f18 -= 2.0f * func_00108030(m->tab, o->h5A, 0);
        }
        if (o->h5A < 90) {
            o->h5A += 5;
        }
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b390:01E034D0, 69 insns: a rising dark flash: starts at height 100 (f4C = f48 - 500), speed 600/10,
   colours (0x20,0x20,0x20) twice, f5A/f5C 15; alpha 0x80 for 3 ticks, then fades out by 14 and stops; climbs by
   the speed every tick */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
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
} Fx_b390_01E034D0;

static s32 func_01E03410_b426(s32 arg0, Fx_b390_01E034D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 100.0f;
        o->size = o->f48 - 500.0f;
        func_001076F0(o->col, 0x20, 0x20, 0x20);
        func_001076F0(o->col2, 0x20, 0x20, 0x20);
        o->f50 = 0;
        o->f5A = 15;
        o->f5C = 15;
        o->f3C = 600.0f;
        o->f3C /= 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 3) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f3C;
    o->size = o->f48 - 500.0f;
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad0000[0x5324];
    s16 joint;
} Mgr_b426_01E03530;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pos[0x38];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    u8 pad5A[6];
    u8 c60[4];
} Obj_b426_01E03530;

static s32 func_01E03530_b426(Mgr_b426_01E03530 *m, Obj_b426_01E03530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 8 + 4;
        o->h56 = func_0019A5C8() % 4;
        func_001076F0(o->c60, 0xC0, 0xC0, 0x50);
        o->h52 = 1;
        o->h50 = func_0019A5C8() % 200 + 200;
        o->hE = func_0019A5C8() % 30 + 10;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 4;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        if (o->c60[3] < 0x60) {
            o->c60[3] += 0x18;
        }
    } else if (o->c60[3] > 12) {
        o->c60[3] -= 11;
    } else {
        o->h58 = 0;
    }
    o->h52++;
    if (o->h50 > 30) {
        o->h50 -= o->hE;
    } else {
        o->h50 = 30;
    }
    o->h54++;
    func_001F5620(func_001F53A0(), m->joint, o->pos);
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03700_b426(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b426", func_01E03710_b426);

/* shape b426:01E04630, 80 insns: twin of b034:01E05330: take a free effect slot (0xB4 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b426_01E04630 {
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
} Slot_b426_01E04630;

typedef struct Obj_b426_01E04630 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b426_01E04630 slots[0xB4];
    u8 padB[0x194];
    u8 rgba[4];
    u8 padC[0x6E];
    s16 fB2B0;
} Obj_b426_01E04630;

static s32 func_01E04630_b426(Obj_b426_01E04630 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b426_01E04630 *s = NULL;
    s16 i;

    for (i = 0; i < 0xB4; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xB4;
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
