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

static void func_01E00080_b390(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b390(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

static void func_01E00D70_b390(Obj_b203_01E00D70 *obj, Cam_b203_01E00D70 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b390((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b390((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b390 in the
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

static void func_01E01320_b390(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b390((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E015E0_b390(Obj_b390_01E015E0 *o, Cam_b390_01E015E0 *cam, s32 flags, Vec4f c) {
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

/* shape b390:01E01AD0, 250 insns: the scene script of b390: counts g+0x8480; each new point (state 0) aims from its
   spot at the camera joint +0x83F4 jittered -10..9 on x and y (a 50th of the gap a tick; the x step is never set, z is
   written twice) and moves for 50 ticks; ticks 100..250, every 13 from +0x847A + 100, a new point on joint +0x83E4
   with 0x1E023E0, 0x1E01EC0 and eighteen 0x1E03270 (slot 0, 20, 40, ...) */

typedef struct {
    f32 x, y, z, w;
} V4_b390_01E01AD0;

typedef struct {
    u8 pad0[0x250];
    V4_b390_01E01AD0 pos;
    u8 pad260[0x7D50 - 0x260];
    V4_b390_01E01AD0 pts[50];
    V4_b390_01E01AD0 vel[50];
    u8 pad8390[0x54];
    s16 jb;
    u8 pad83E6[0xE];
    s16 ja;
    u8 pad83F6[0xE];
    s16 state[50];
    u8 pad8468[0xE];
    s16 cur;
    s16 n;
    s16 next;
    u8 pad847C[4];
    s16 tick;
} Ctx_b390_01E01AD0;

static void func_01E01AD0_b390(Ctx_b390_01E01AD0 *g) {
    extern void b390_01E01EC0();
    extern void b390_01E023E0();
    extern void b390_01E03270();
    extern void b390_01E04820(Ctx_b390_01E01AD0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[8];
    s16 i;
    s16 k;

    g->tick++;
    for (i = 0; i < g->n; i++) {
        if (g->state[i] == 0) {
            func_001F5620(func_001F5380(), g->ja, v);
            v[0] += func_0019A5C8() % 20 - 10;
            v[1] += func_0019A5C8() % 20 - 10;
            g->vel[i].z = (v[2] - g->pts[i].z) / 50.0f;
            g->vel[i].y = (v[1] - g->pts[i].y) / 50.0f;
            g->vel[i].z = (v[2] - g->pts[i].z) / 50.0f;
            g->state[i]++;
        }
    }
    for (i = 0; i < g->n; i++) {
        if (g->state[i] != 0) {
            if (g->state[i] < 51) {
                g->pts[i].z += g->vel[i].z;
                g->pts[i].y += g->vel[i].y;
                g->pts[i].x += g->vel[i].x;
                g->state[i]++;
            } else {
                g->state[i]++;
            }
        }
    }
    if (g->tick >= 100 && g->tick < 251 && g->tick == g->next + 100) {
        g->cur = g->n;
        func_001F5620(func_001F53A0(), g->jb, &g->pts[g->cur]);
        func_001F5620(func_001F53A0(), g->jb, &g->pos);
        b390_01E04820(g, b390_01E023E0, 0);
        b390_01E04820(g, b390_01E01EC0, 0);
        for (i = 0, k = 0; i < 18; i++) {
            g->cur = k;
            b390_01E04820(g, b390_01E03270, 0);
            k += 20;
        }
        g->next += 13;
        g->n++;
    }
}

/* shape b390:01E01EC0, 94 insns: on start 0x8/0xA = 25, random flip 0x56, both colours (0x20, 0x20, 0xFF) (second
   alpha 0); both alphas grow by 0x40 (below 0xC0) for 0x33 ticks, then the first fades by 14 twice a tick and ends
   it; 0x56 toggles; after the first tick 0x8/0xA grow by 10 below 0x4B; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 flip;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b390_01E01EC0;

static s32 func_01E01EC0_b390(s32 arg0, Fx_b390_01E01EC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 25;
        o->fA = 25;
        o->flip = func_0019A5C8() % 2;
        func_001076F0(o->col, 0x20, 0x20, 0xFF);
        func_001076F0(o->col2, 0x20, 0x20, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x33) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else {
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        } else {
            o->mode = 0;
        }
        if (o->col[3] > 0xF) {
            o->col[3] -= 14;
        }
    }
    if (o->flip != 0) {
        o->flip = 0;
    } else {
        o->flip = 1;
    }
    if (o->tick != 0) {
        if (o->f8 < 0x4B) {
            o->f8 += 10;
        }
        if (o->fA < 0x4B) {
            o->fA += 10;
        }
    }
    func_00205C40((s32)o->rot);
    o->tick++;
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

static s32 func_01E02040_b390(s32 arg0, Fx_b390_01E02040 *o) {
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

static s32 func_01E021E0_b390(s32 unused, Mote_b111_01E022F0 *o) {
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

/* shape b390:01E023E0, 207 insns: on start f48 100, colour white, second colour (0x80, 0x80, 8) with alpha 0, random
   0x5A, 0xE = 1..10; the second colour turns blue (8, 8, 0x80) on odd and even ticks alike; alpha grows by 0x40 (below
   0xC0) up to tick 50, then fades by 14 and stops; at tick 51 the game point moves to point[0x50] and spawns nine
   b390:01E02BE0, nine b390:01E02040, one b390:01E028D0 and five b390:01E02DE0; before it, every tick spawns
   b390:01E02F50 and b390:01E030F0 there; the rotation is re-read and turned a quarter each tick */

typedef struct {
    f32 x, y, z, w;
} V_b390_01E023E0;

typedef struct {
    u8 pad0[0x250];
    V_b390_01E023E0 pos;
    u8 pad260[0x7D50 - 0x260];
    V_b390_01E023E0 pts[1];
} Game_b390_01E023E0;

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
} Fx_b390_01E023E0;

static s32 func_01E023E0_b390(Game_b390_01E023E0 *g, Fx_b390_01E023E0 *o) {
    extern s32 b390_01E02040(void);
    extern s32 b390_01E028D0(void);
    extern s32 b390_01E02BE0(void);
    extern s32 b390_01E02DE0(void);
    extern s32 b390_01E02F50(void);
    extern s32 b390_01E030F0(void);
    extern s32 b390_01E04820(Game_b390_01E023E0 *, s32 (*)(void), s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->f48 = 100.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x80, 8);
        o->f5A = func_0019A5C8() % 360;
        o->fE = (func_0019A5C8() >> 4) % 10 + 1;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 8, 8, 0x80);
    } else {
        func_001076F0(o->col2, 8, 8, 0x80);
    }
    if (o->tick < 51) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick == 51) {
        g->pos = g->pts[o->pt];
        for (i = 0; i < 9; i++) {
            b390_01E04820(g, b390_01E02BE0, 0);
        }
        for (i = 0; i < 9; i++) {
            b390_01E04820(g, b390_01E02040, 0);
        }
        b390_01E04820(g, b390_01E028D0, 0);
    }
    if (o->tick == 51) {
        g->pos = g->pts[o->pt];
        for (i = 0; i < 5; i++) {
            b390_01E04820(g, b390_01E02DE0, 0);
        }
    }
    if (o->tick < 51) {
        g->pos = g->pts[o->pt];
        b390_01E04820(g, b390_01E02F50, 0);
        b390_01E04820(g, b390_01E030F0, 0);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b390:01E02720, 107 insns: on start f48 0, colour 0xCF grey, second colour (0x80, 8, 8) with alpha 0, random 0x5A
   and rotation; alpha grows by 0x40 (below 0xC0) for 10 ticks, then fades by 14 and stops; f48 grows by 8.5 while the
   game step 0x8480 is below 200, else by 4.5, with f4C 4 below it */

typedef struct {
    u8 pad0[0x8480];
    s16 step;
} Game_b390_01E02720;

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
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
} Fx_b390_01E02720;

static s32 func_01E02720_b390(Game_b390_01E02720 *g, Fx_b390_01E02720 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->col, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->col2, 0x80, 8, 8);
        o->f5A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (g->step < 200) {
        o->f48 += 8.5f;
        o->f4C = o->f48 - 4.0f;
    } else {
        o->f48 += 4.5f;
        o->f4C = o->f48 - 4.0f;
    }
    o->tick++;
    return 0;
}

/* shape b390:01E028D0, 80 insns: a pink glow of size 650 at a random angle, spun 0x4000 a tick, its second colour blinking blue: in by 64 up to 0xC0 for 4 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x24];
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
} Obj_b390_01E028D0;

static s32 func_01E028D0_b390(s32 arg0, Obj_b390_01E028D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 650.0f;
        func_001076F0(o->col, 0xFF, 0xCF, 0xCF);
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
        func_001076F0(o->col2, 8, 8, 0x80);
    } else {
        func_001076F0(o->col2, 8, 8, 0xC0);
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

static s32 func_01E02A10_b390(void *arg0, Obj_b111_01E02A10 *o) {
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

/* shape b390:01E02BE0, 127 insns: constant variant of b016:01E02940 (spark set-up) */

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
} Spark_b390_01E02BE0;

static s32 func_01E02BE0_b390(s32 arg0, Spark_b390_01E02BE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 10 + 10;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x50, 0x50, 0xC0);
        o->x = func_0019A5C8() % 0xFFFF;
        o->y = func_0019A5C8() % 0xFFFF;
        o->z = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 200 + 250;
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

/* shape b390:01E02DE0, 92 insns: a white-blue growing burst: f48 20 growing by 45 with f4C half of it, random angle and turn on
   all three axes; alpha up by 0x40 to 0xC0 for 5 frames, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b390_01E02DE0;

static s32 func_01E02DE0_b390(void *arg0, Obj_b390_01E02DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 20.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 8, 8, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = (func_0019A5C8() >> 4) % 65535;
        o->rot[1] = (func_0019A5C8() >> 4) % 65535;
        o->rot[2] = (func_0019A5C8() >> 4) % 65535;
    }
    if (o->t < 5) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f48 += 45.0f;
    o->f4C = 0.5f * o->f48;
    o->t++;
    return 0;
}

/* shape b390:01E02F50, 103 insns: a pale-blue shrinking ring (b270:01E03780 shape): size 150 shrinking by 15 to 20 once started,
   random sub-frame 0..7, angle and tilt -90..89; both alphas up by 0x40 for 3 frames, then down by 14 until it ends; turns */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    s32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    s16 tilt;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b390_01E02F50;

static s32 func_01E02F50_b390(void *arg0, Obj_b390_01E02F50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x96;
        o->h = 0x96;
        o->sub = func_0019A5C8() % 8;
        o->f34 = 0;
        func_001076F0(o->c0, 0x80, 0x80, 0xFF);
        func_001076F0(o->c1, 0x80, 0x80, 0xFF);
        o->state = 2;
        o->c1[3] = 0;
        o->ang = func_0019A5C8() % 360;
        o->tilt = func_0019A5C8() % 180 - 0x5A;
    }
    if (o->t < 3) {
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
    if (o->t != 0) {
        if (o->w > 0x14) {
            o->w -= 0xF;
        }
        if (o->h > 0x14) {
            o->h -= 0xF;
        }
    }
    func_00205C40((s32)o->rot);
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

static s32 func_01E030F0_b390(s32 arg0, Fx_b390_01E030F0 *o) {
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

/* shape b390:01E03270, 149 insns: b426:01E031D0's rising puff in blue (0x80, 0x80, 0xFF), sine table at +0x8784, up flag at +0x847C */

typedef struct {
    u8 pad0000[0x847C];
    s16 up;
    u8 pad847E[0x306];
    u8 tab[1];
} Mgr_b390_01E03270;

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
} Obj_b390_01E03270;

static s32 func_01E03270_b390(Mgr_b390_01E03270 *m, Obj_b390_01E03270 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 150;
        o->hA = 150;
        o->h56 = func_0019A5C8() % 8;
        o->f30 = 3.5f * func_00108030(m->tab, o->h50, 1);
        o->f34 = 3.5f * func_00108030(m->tab, o->h50, 0);
        func_001076F0(o->c60, 0x80, 0x80, 0xFF);
        func_001076F0(o->c64, 0x80, 0x80, 0xFF);
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

static s32 func_01E034D0_b390(s32 arg0, Fx_b390_01E034D0 *o) {
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
    u8 pad0000[0x83E4];
    s16 joint;
} Mgr_b390_01E035F0;

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
} Obj_b390_01E035F0;

static s32 func_01E035F0_b390(Mgr_b390_01E035F0 *m, Obj_b390_01E035F0 *o) {
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

static s32 func_01E037D0_b390(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b390", func_01E037E0_b390);

/* shape b390:01E04820, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x118 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b390_01E04820 {
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
} Slot_b390_01E04820;

typedef struct Obj_b390_01E04820 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b390_01E04820 slots[0x118];
    u8 padB[0x83b4 - 0x2a0 - 0x118 * 0x70];
    u8 rgba[4];
    u8 padC[0x8476 - 0x83b4 - 4];
    s16 fB2B0;
} Obj_b390_01E04820;

static s32 func_01E04820_b390(Obj_b390_01E04820 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b390_01E04820 *s = NULL;
    s16 i;

    for (i = 0; i < 0x118; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x118;
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
