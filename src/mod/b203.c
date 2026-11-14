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

static void func_01E00080_b203(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b203(Obj_b108_01E009A0 *o, Data_b108_01E009A0 *data, s32 flags, Vec4f pos) {
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

static void func_01E00D70_b203(Obj_b203_01E00D70 *obj, Cam_b203_01E00D70 *cam, s32 flags, s8 *table) {
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
    func_01E00080_b203((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00080_b203((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b203 in the
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

static void func_01E01320_b203(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b203((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E015E0_b203(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E01940_b203(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b203:01E01D40 (B203_W_S), 408 insns, 1 copy: B203_W_S, the scene script: counts the frame (0x452A); on
   211/235 catches the carried points A/B on joint A, on 211 aims the climb (z/y over 14); A rises on 212..224, B on
   236..247 with trails; motes on joints B/C until 134/94, sparks on joint A (10 to the side) on 78..133; on 211/235 a
   ring of 10 (kind 0/1) and a flash, on 224/247 a ring of 10 and 5+5+4 bursts and a closer */

typedef struct {
    u8 pad0000[0x250];
    Vec4f p;
    u8 pad0260[0x4470 - 0x260];
    Vec4f posA;
    Vec4f posB;
    Vec4f step;
    u8 pad44A0[0x44F4 - 0x44A0];
    s16 jB;
    s16 jC;
    s16 jA;
    u8 pad44FA[0x4504 - 0x44FA];
    s16 jT;
    u8 pad4506[0x4522 - 0x4506];
    s16 kind;
    u8 pad4524[2];
    s16 side;
    u8 pad4528[2];
    s16 frame;
} Ctx_b203_01E01D40;

static void func_01E01D40_b203(Ctx_b203_01E01D40 *g) {
    extern s32 func_001F5380(void);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void b203_01E03FB0();
    extern s32 b203_01E027D0();
    extern s32 b203_01E02950();
    extern s32 b203_01E02B50();
    extern s32 b203_01E02D10();
    extern s32 b203_01E02E90();
    extern s32 b203_01E03030();
    extern s32 b203_01E03140();
    extern s32 b203_01E032D0();
    Vec4f v;
    Vec4f w;
    s16 i;
    s16 j;

    g->frame++;
    if (g->frame == 0xD3) {
        func_001F5620(func_001F53A0(), g->jA, &g->posA);
    }
    if (g->frame == 0xEB) {
        func_001F5620(func_001F53A0(), g->jA, &g->posB);
    }
    if (g->frame == 0xD3) {
        func_001F5620(func_001F5380(), g->jT, &v);
        func_001F5620(func_001F53A0(), g->jB, &w);
        g->step.z = (v.z - w.z) / 14.0f;
        g->step.y = (v.y - w.y) / 14.0f;
    }
    if (g->frame > 0xD3 && g->frame < 0xE1) {
        g->posA.z += g->step.z;
        g->p = g->posA;
        b203_01E03FB0(g, b203_01E027D0, 0);
    }
    if (g->frame > 0xEB && g->frame < 0xF8) {
        g->posB.z += g->step.z;
        g->p = g->posB;
        b203_01E03FB0(g, b203_01E027D0, 0);
    }
    if (g->frame == 0xBA) {
        g->p = g->posA;
        g->kind = 0;
    }
    if (g->frame < 0x86) {
        func_001F5620(func_001F53A0(), g->jB, &g->p);
        b203_01E03FB0(g, b203_01E027D0, 0);
    }
    if (g->frame < 0x5E) {
        func_001F5620(func_001F53A0(), g->jC, &g->p);
        b203_01E03FB0(g, b203_01E027D0, 0);
    }
    if (g->frame > 0x4D && g->frame < 0x86) {
        func_001F5620(func_001F53A0(), g->jA, &g->p);
        if (g->side != 0) {
            g->p.z -= 10.0f;
        } else {
            g->p.z += 10.0f;
        }
        b203_01E03FB0(g, b203_01E02950, 0);
    }
    if (g->frame == 0xD3 || g->frame == 0xEB) {
        func_001F5620(func_001F53A0(), g->jA, &g->p);
        for (i = 0, j = 0; i < 10; i++) {
            g->kind = j;
            b203_01E03FB0(g, b203_01E02B50, 0);
            j += 0x24;
        }
        if (g->frame == 0xD3) {
            g->kind = 0;
        }
        if (g->frame == 0xEB) {
            g->kind = 1;
        }
        b203_01E03FB0(g, b203_01E02D10, 0);
    }
    if (g->frame == 0xE0) {
        g->p = g->posA;
        for (j = 0, i = 0; j < 10; j++) {
            g->kind = i;
            b203_01E03FB0(g, b203_01E02B50, 0);
            i += 0x24;
        }
        for (i = 0; i < 5; i++) {
            b203_01E03FB0(g, b203_01E02E90, 0);
        }
        for (i = 0; i < 5; i++) {
            b203_01E03FB0(g, b203_01E03140, 0);
        }
        for (i = 0; i < 4; i++) {
            b203_01E03FB0(g, b203_01E032D0, 0);
        }
        b203_01E03FB0(g, b203_01E03030, 0);
    }
    if (g->frame == 0xF7) {
        g->p = g->posB;
        for (j = 0, i = 0; j < 10; j++) {
            g->kind = i;
            b203_01E03FB0(g, b203_01E02B50, 0);
            i += 0x24;
        }
        for (i = 0; i < 5; i++) {
            b203_01E03FB0(g, b203_01E02E90, 0);
        }
        for (i = 0; i < 5; i++) {
            b203_01E03FB0(g, b203_01E03140, 0);
        }
        for (i = 0; i < 4; i++) {
            b203_01E03FB0(g, b203_01E032D0, 0);
        }
        b203_01E03FB0(g, b203_01E03030, 0);
    }
}

/* shape b203:01E023A0, 268 insns: b111:01E01D30 with this module's table and side; b149:01E01770 cousin: size 10, grey 0x80, random frame 0..6, turn, spin and hA 0..7,
   height from 0 growing by 15 up to its limit 100..449 while it fades in by 0x20 for 147 ticks, then fades by 8 and
   ends; at tick 135 it hands its position to the scene and fires the module's b203:01E027D0 effect three times, then
   b203:01E02B50 six times in ten at a point jittered -15..14; its swing f34 is 3 x the table sine of h5C; from tick 96
   to 130 it is pushed 5 a tick in z by the scene side (0x4526) and sinks 1 while above the target's height - 10; from
   tick 141 it turns 5, rises by hE and 1 and grows 1; h5C turns by 6 */

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad260[0x4526 - 0x260];
    s16 side;
    u8 pad4528[0x482C - 0x4528];
    u8 table[1];
} Mgr_b203_01E023A0;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
} Obj_b203_01E023A0;

static s32 func_01E023A0_b203(Mgr_b203_01E023A0 *m, Obj_b203_01E023A0 *o) {
    extern void b203_01E027D0();
    extern void b203_01E02B50();
    extern void b203_01E03FB0(Mgr_b203_01E023A0 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    f32 v[4];

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->h5C = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->h58 = 2;
    }
    if (o->h54 < 147) {
        if (o->c60[3] < 0x80) {
            o->c60[3] += 0x20;
        }
        if (o->h52 > o->h50) {
            o->h50 += 15;
        }
    } else if (o->c60[3] > 9) {
        o->c60[3] -= 8;
    } else {
        o->h58 = 0;
    }
    if (o->h54 == 135) {
        m->pos = o->pos;
        b203_01E03FB0(m, b203_01E027D0, 0);
        b203_01E03FB0(m, b203_01E027D0, 0);
        b203_01E03FB0(m, b203_01E027D0, 0);
        m->pos.x += func_0019A5C8() % 30 - 15;
        m->pos.y += func_0019A5C8() % 30 - 15;
        m->pos.z += func_0019A5C8() % 30 - 15;
        if (func_0019A5C8() % 10 < 6) {
            b203_01E03FB0(m, b203_01E02B50, 0);
        }
    }
    func_001F5F90(func_001F5380(), v);
    o->f34 = 3.0f * func_00108030(m->table, o->h5C, 1);
    if (o->h54 > 95 && o->h54 < 131) {
        if (m->side != 0) {
            o->pos.z -= 5.0f;
        } else {
            o->pos.z += 5.0f;
        }
        if (v[1] - 10.0f < o->pos.y) {
            o->pos.y -= 1.0f;
        }
    }
    if (o->h54 > 140) {
        o->h5A += 5;
        o->h50 += o->hE;
        o->pos.y += 1.0f;
        o->f48 += 1.0f;
    }
    o->h5C += 6;
    o->h54++;
    return 0;
}

/* shape b203:01E027D0, 95 insns: an orange spark: size 10, random sub-frame 0..3, angle, frame 0..7, start height 5..44 (old one
   kept), rise 6..15, width 0..34, hold 3..7; full alpha until the hold, then down by 8 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 frame;
    s16 y0;
    s16 step;
    u8 pad10[0x38];
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
} Obj_b203_01E027D0;

static s32 func_01E027D0_b203(void *arg0, Obj_b203_01E027D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 10.0f;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x80, 0x40, 0x20);
        o->ang = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 8;
        o->y0 = o->y;
        o->y = func_0019A5C8() % 40 + 5;
        o->step = func_0019A5C8() % 10 + 6;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 9) {
        o->c0[3] -= 8;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b203:01E02950, 128 insns: b394:01E01AA0 family orange spark (size 10, frame 0..3, angle 0..359 turning 5, fC = old f50, f50 50..149 shrinking 6..15 per tick, f8 0..34, life 3..7): z drifts +1.5 while the scene flag is set, else -1.2 */

typedef struct {
    u8 pad0[0x4526];
    s16 flag;
} Ctx_b203_01E02950;

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 spin;
    u8 pad10[8];
    f32 z;
    u8 pad1C[0x2C];
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
} Fx_b203_01E02950;

static s32 func_01E02950_b203(Ctx_b203_01E02950 *g, Fx_b203_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0x20);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 100 + 50;
        o->spin = func_0019A5C8() % 10 + 6;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (g->flag != 0) {
            o->z += 1.5f;
        } else {
            o->z -= 1.2f;
        }
    }
    if (o->tick != 0) {
        o->f50 -= o->spin;
    }
    o->tick++;
    o->f5A += 5;
    return 0;
}

typedef struct {
    u8 pad0000[0x482C];
    u8 tab[1];
} Mgr_b203_01E02B50;

typedef struct {
    u8 pad00[8];
    s16 h8;
    s16 hA;
    u8 pad0C[4];
    f32 f10;
    f32 f14;
    u8 pad18[8];
    s32 rot[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    s16 h50;
    u8 pad52[2];
    s16 h54;
    s16 h56;
    s16 h58;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
} Obj_b203_01E02B50;

static s32 func_01E02B50_b203(Mgr_b203_01E02B50 *m, Obj_b203_01E02B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 80;
        o->hA = 80;
        o->h56 = func_0019A5C8() % 8;
        o->f30 = 1.5f * func_00108030(m->tab, o->h50, 1);
        o->f34 = 1.5f * func_00108030(m->tab, o->h50, 0);
        func_001076F0(o->c60, 0xFF, 0x80, 0x80);
        func_001076F0(o->c64, 0xFF, 0x80, 0x80);
        o->h58 = 2;
        o->c64[3] = 0;
    }
    if (o->h54 < 4) {
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
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b203:01E02D10, 96 insns: on start 0x8/0xA = 40, variant 3, both colours white (second alpha 0); both alphas
   grow by 0x40 (below 0xC0) for 14 ticks, then the first fades by 14 twice a tick and ends it; the variant swaps 3/5;
   the colour flickers grey; func_00205C40 on the rotation */

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 f56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b203_01E02D10;

static s32 func_01E02D10_b203(s32 arg0, Fx_b203_01E02D10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f8 = 40;
        o->fA = 40;
        o->f56 = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 14) {
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
    if (o->f56 == 3) {
        o->f56 = 5;
    } else {
        o->f56 = 3;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0x70);
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b203:01E02E90, 102 insns: b593:01E020C0 twin: a white spark (size 35, random frame 0..3) spinning 12..31 a tick from 5..44 */

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
} Obj_b203_01E02E90;

static s32 func_01E02E90_b203(s32 arg0, Obj_b203_01E02E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 35.0f;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 40 + 5;
        o->hE = func_0019A5C8() % 20 + 12;
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

/* shape b203:01E03030, 68 insns: on start f48 220, f4C 0, colour white, second colour (0xFF, 0x40, 0x40) with alpha 0,
   0x5A/0x5C = 15; alpha grows by 0x60 (below 0xC0) for 7 ticks, then fades by 11 and stops; f48 grows by 1 after the
   first tick; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b203_01E03030;

static s32 func_01E03030_b203(s32 arg0, Fx_b203_01E03030 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 220.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0x40, 0x40);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 7) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b203:01E03140, 98 insns: a grey rising flash (b445:01E02570 shape): rising by 350 / 10 from 100 with f4C 570 below,
   random sub-frame 0..7 and turn on all three axes; full alpha for 6 frames, then down by 9 until it ends */

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
} Obj_b203_01E03140;

static s32 func_01E03140_b203(void *arg0, Obj_b203_01E03140 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 100.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->h50 = 0;
        o->sub = func_0019A5C8() % 8;
        o->w = 0xF;
        o->h = 0xF;
        o->f34 = 350.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
        o->rot0 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
    }
    if (o->t < 6) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 570.0f;
    o->t++;
    return 0;
}

/* shape b203:01E032D0, 130 insns: b193:01E02910 family pink (0xCF, 0x80, 0x80) spark (f48 10..29, f50 500..899 growing 1..3), alpha 0x70 for 2..4 ticks then down by 9, angle turning 2 per tick */

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
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b203_01E032D0;

static s32 func_01E032D0_b203(s32 arg0, Fx_b203_01E032D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 20 + 10;
        o->f56 = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xCF, 0x80, 0x80);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f52 = 1;
        o->f50 = func_0019A5C8() % 400 + 500;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->f8 = func_0019A5C8() % 8 + 1;
        o->hold = func_0019A5C8() % 3 + 2;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0x70;
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f5A += 2;
    o->f52++;
    o->f50 += o->speed;
    o->tick++;
    return 0;
}

/* shape b111:01E02DE0, 68 insns, 2 copies: a rising flash: set up once with a random angle and two colours, fades in over 13
   frames, then out; rises 3 a frame, its second height 5 above (b016:01E01FF0 family) */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0x24];
    f32 y;
    f32 y2;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Obj_b111_01E02DE0;

static s32 func_01E034E0_b203(void *arg0, Obj_b111_01E02DE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->y = 0.0f;
        func_001076F0(o->c0, 0xCF, 0xCF, 0xCF);
        func_001076F0(o->c1, 0x80, 8, 8);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
        o->w20 = 0x4000;
    }
    if (o->t < 0xD) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->y += 3.0f;
    o->y2 = 5.0f + o->y;
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E035F0_b203(void) {
    return 0;
}

/* shape b203:01E03600 (b203), 620 insns, 1 copy: b203 scene manager in b189:01E03230 form: setup (six joints and
   camera, texture (4,15), three type-5 textures, turn from the camera angle, scale 0.1, three s8 jitter tables: +-15
   with 100..179 rand%4, +-20 with 180..255 +-10, +-20 with 180..255 +-5), step b203:01E01D40 and every slot (150 of
   0x70) but the empty b203:01E035F0, draw the slots by handler (023A0 sets the light, 027D0/02E90/032D0 and 02950
   (pinned to joint 2) as D70 strips, 02B50/02D10 as 01320 glows, 03030, 03140, 034E0); scene code 1/3/6/8 from the
   frame and timer */

typedef struct {
    u8 pad0[0xA];
    s16 h0A;
    u8 padC[4];
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0xC];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b203_01E03600;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 x20;
    f32 y24;
    f32 z28;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
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
    Fx_b203_01E03600 fx[150];
    u8 pad4440[0x30];
    Vec4f v4470[3];
    s32 tex2[3];
    u8 pad44AC[0x14];
    s32 count;
    u8 pad44C4[8];
    s32 ot;
    u8 pad44D0[0x24];
    s16 j[6];
    u8 pad4500[4];
    s16 cam;
    u8 pad4506[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    s8 jit3[0x100];
    u8 crd[0x16C];
} Scene_b203_01E03600;

static s32 func_01E03600_b203(s32 arg0, s32 id) {
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
    extern void b203_01E01D40();
    Scene_b203_01E03600 *g = (Scene_b203_01E03600 *)arg0;
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
        func_00195108(g, 0x49A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x10D;
        g->j[0] = func_001F5560(func_001F53A0(), 0x40, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x4C, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x14, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
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
        for (k = 180; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit3[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 180; k < 0x100; k++) {
            g->jit3[k] = func_0019A5C8() % 10 - 5;
        }
        return 0;
    }
    b203_01E01D40(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E035F0_b203) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E023A0_b203) {
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[0];
                g->hB8 = 6;
                g->hC0 = g->fx[k].h0A;
                g->x20 = g->fx[k].pos.x;
                g->y24 = g->fx[k].pos.y + g->fx[k].f34;
                g->z28 = g->fx[k].pos.z;
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E027D0_b203) {
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[0];
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00D70_b203(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02950_b203) {
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->tex88 = g->tex2[0];
                g->hB8 = 4;
                g->hB0 = 0;
                func_001F5620(func_001F53A0(), g->j[2], &v);
                g->fx[k].pos.x = v.x;
                g->fx[k].pos.y = v.y;
                func_01E00D70_b203(g, &g->fx[k], 0x20, g->jit3);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B50_b203) {
                g->tex88 = g->tex2[1];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01320_b203(g, &g->fx[k], 0x11, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D10_b203) {
                g->tex88 = g->tex2[2];
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->hBE = func_0019A5C8() % 6;
                v.x = g->v4470[g->fx[k].h50].x;
                v.y = g->v4470[g->fx[k].h50].y;
                v.z = g->v4470[g->fx[k].h50].z;
                func_01E01320_b203(g, &g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02E90_b203) {
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                g->tex88 = g->tex2[0];
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00D70_b203(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03030_b203) {
                g->hB8 = 0x18;
                func_01E015E0_b203(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03140_b203) {
                func_00106080(rm7, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm7;
                g->tex88 = g->tex2[0];
                g->hB8 = 0x18;
                func_01E01940_b203(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E032D0_b203) {
                func_00106080(rm8, 0x9B, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm8;
                g->tex88 = g->tex[15];
                g->hB8 = 9;
                g->hB0 = 1;
                func_01E00D70_b203(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E034E0_b203) {
                v = g->fx[k].pos;
                func_01E00920_b203(g, &g->fx[k], 0x20, v);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0xD6) {
        return 1;
    }
    if (g->frame == 0x109) {
        return 3;
    }
    if (g->frame > 0xE0 && g->frame < 0x104) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b203:01E03FB0, 82 insns: c035:01E01150 family: take the first free effect slot of 150 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, two angles and both arguments; returns 1 when it got one */

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
} Obj_b203_01E03FB0;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2A0 - 0x25C];
    Obj_b203_01E03FB0 slot[150];
    u8 padEnd[0x44c4 - 0x2A0 - 150 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padA[0x4516 - 0x44c4 - 4];
    s16 ang;
    u8 padB[0x4522 - 0x4516 - 2];
    s16 h30;
} Ctx_b203_01E03FB0;

static s32 func_01E03FB0_b203(Ctx_b203_01E03FB0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b203_01E03FB0 *s;

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
        s->h50 = ctx->h30;
        s->h5A = ctx->ang;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}
