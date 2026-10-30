#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b287(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b287(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b287(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b287((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b287((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00F60_b287(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b287 in the
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

static void func_01E012C0_b287(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b287((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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
} Vec_b018_01E00EE0;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static Vec_b018_01E00EE0 func_01E01580_b287(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
    Vec_b018_01E00EE0 r;
    f32 b0;
    f32 b1;
    f32 b2;
    f32 b3;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    } else if (type == 1) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t)) / 6.0f;
        b1 = 2.0f / 3.0f + ((t * (t * t)) / 2.0f - (t * t));
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(t * (t * t)) / 2.0f + (t * t) / 2.0f));
        b3 = (t * (t * t)) / 6.0f;
    } else if (type == 2) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 1.75f * (t * (t * t)) - 4.5f * (t * t) + 3.0f * t;
        b2 = -(11.0f / 12.0f * (t * (t * t))) + 1.5f * (t * t);
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 3) {
        b0 = 0.25f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 7.0f / 12.0f + (7.0f / 12.0f * (t * (t * t)) - 1.25f * (t * t) + 0.25f * t);
        b2 = 1.0f / 6.0f + (t / 2.0f + (-(0.5f * (t * (t * t))) + 0.5f * (t * t)));
        b3 = 1.0f / 6.0f * (t * (t * t));
    } else if (type == 4) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = 1.0f / 6.0f + (-0.5f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 0.5f * ((1.0f - t) * (1.0f - t)) + 0.5f * (1.0f - t));
        b2 = 7.0f / 12.0f + (7.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 1.25f * ((1.0f - t) * (1.0f - t)) + 0.25f * (1.0f - t));
        b3 = 0.25f * (t * (t * t));
    } else if (type == 5) {
        b0 = 1.0f / 6.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t)));
        b1 = -11.0f / 12.0f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) + 1.5f * ((1.0f - t) * (1.0f - t));
        b2 = 1.75f * ((1.0f - t) * ((1.0f - t) * (1.0f - t))) - 4.5f * ((1.0f - t) * (1.0f - t)) + 3.0f * (1.0f - t);
        b3 = (t * (t * t));
    } else if (type == 6) {
        b0 = (1.0f - t) * ((1.0f - t) * (1.0f - t));
        b1 = 3.0f * t * ((1.0f - t) * (1.0f - t));
        b2 = (1.0f - t) * (3.0f * (t * t));
        b3 = t * (t * t);
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
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

static void func_01E019C0_b287(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

/* shape b287:01E01D30, 173 insns: b422:01E014F0 family event step: spawns b287:01E02DA0 and b287:01E02EB0 at tick 1; at 130 marks the tracked point (ctx+0xCB46) and there spawns b287:01E02C80, 20 b287:01E02510 and four b287:01E02760 (turns 0/90/45/135, slots 0/1/2/2); from 130 to 140 spawns 10 b287:01E01FF0 a tick at the mark */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCAD0 - 0x260];
    Vec4f mark;
    u8 padCAE0[0xCB46 - 0xCAE0];
    s16 id;
    u8 padCB48[0xCBA2 - 0xCB48];
    s16 turn;
    u8 padCBA4[0xCBB0 - 0xCBA4];
    s16 slot;
    u8 padCBB2[0xCBB8 - 0xCBB2];
    s16 timer;
} Ctx_b287_01E01D30;

static void func_01E01D30_b287(Ctx_b287_01E01D30 *g) {
    extern s32 b287_01E01FF0(void);
    extern s32 b287_01E02510(void);
    extern s32 b287_01E02760(void);
    extern s32 b287_01E02C80(void);
    extern s32 b287_01E02DA0(void);
    extern s32 b287_01E02EB0(void);
    extern void b287_01E03890(Ctx_b287_01E01D30 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->timer++;
    if (g->timer == 1) {
        b287_01E03890(g, b287_01E02DA0, 0);
    }
    if (g->timer == 1) {
        b287_01E03890(g, b287_01E02EB0, 0);
    }
    if (g->timer == 130) {
        func_001F5620(func_001F53A0(), g->id, &g->mark);
    }
    if (g->timer == 130) {
        g->pos = g->mark;
        b287_01E03890(g, b287_01E02C80, 0);
        for (i = 0; i < 20; i++) {
            b287_01E03890(g, b287_01E02510, 0);
        }
        g->turn = 0;
        g->slot = 0;
        b287_01E03890(g, b287_01E02760, 0);
        g->turn = 90;
        g->slot = 1;
        b287_01E03890(g, b287_01E02760, 0);
        g->turn = 45;
        g->slot = 2;
        b287_01E03890(g, b287_01E02760, 0);
        g->turn = 135;
        g->slot = 2;
        b287_01E03890(g, b287_01E02760, 0);
    }
    if (g->timer >= 130 && g->timer < 141) {
        g->pos = g->mark;
        for (i = 0; i < 10; i++) {
            b287_01E03890(g, b287_01E01FF0, 0);
        }
    }
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    u8 pad10[0x38];
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
} Obj_b287_01E01FF0;

static s32 func_01E01FF0_b287(s32 unused, Obj_b287_01E01FF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = func_0019A5C8() % 15 + 6;
        o->h56 = func_0019A5C8() % 3;
        func_001076F0(o->c60, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 20 + 16;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 7;
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x40;
        }
    } else if (o->c60[3] > 15) {
        o->c60[3] -= 14;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->h50 += o->hE;
    }
    o->h54++;
    return 0;
}

/* shape b256:01E02540, 218 insns: b256:01E02A40 family: a drifting spark (drift /100, random spin and spin speed), fades in for 6 ticks, out by 11; grows every third tick; the scene counter past 445 ends it */

typedef struct {
    u8 pad0[0xCBB4];
    s16 flag;
    u8 padCBB6[2];
    s16 count;
} Ctx_b256_01E02540;

typedef struct {
    s16 h0, h2, h4;
    u8 pad6[2];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    u8 pad4C[6];
    s16 h52;
    s16 t;
    s16 h56;
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
} Obj_b256_01E02540;

static s32 func_01E021A0_b287(Ctx_b256_01E02540 *ctx, Obj_b256_01E02540 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h8 = func_0019A5C8() % 3 + 3;
        o->hA = o->h8 + 4;
        o->h56 = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->state = 2;
        o->f34 = func_0019A5C8() % 100 - 50;
        o->f30 = func_0019A5C8() % 100 - 50;
        o->f38 = func_0019A5C8() % 100 - 50;
        o->f34 /= 100.0f;
        o->f30 /= 100.0f;
        o->f38 /= 100.0f;
        o->h5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->h4 = func_0019A5C8() % 0x800 - 0x400;
        o->h2 = func_0019A5C8() % 0x800 - 0x400;
        o->h0 = func_0019A5C8() % 0x800 - 0x400;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
    }
    if (o->t < 6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->h8 < 11) {
            o->h8++;
        }
        if (o->hA < o->h8 + 4) {
            o->hA++;
        }
    }
    if (o->t != 0) {
        o->x += o->f30;
        o->y += o->f34;
        o->z += o->f38;
    }
    o->rot[2] += o->h4;
    o->rot[1] += o->h2;
    o->rot[0] += o->h0;
    o->t++;
    if (ctx->count > 445) {
        o->t = 90;
    }
    return 0;
}

/* shape b287:01E02510, 147 insns: b256:01E02DF0 family white spark (size 150) kicked 8.6 and drifting 0.6 along two random angles in 3D (table at ctx+0xCDBC); alpha up by 0x60 to 0xC0 for 26 ticks, then down by 19 */

typedef struct {
    u8 pad0000[0xCDBC];
    u8 tab[1];
} Mgr_b287_01E02510;

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
    u8 pad30[0x24];
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c60[4];
} Obj_b287_01E02510;

static s32 func_01E02510_b287(Mgr_b287_01E02510 *m, Obj_b287_01E02510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 150;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h58 = 2;
        o->h5A = (func_0019A5C8() >> 4) % 360;
        o->h5C = (func_0019A5C8() >> 4) % 360;
        o->f14 += 8.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 8.6f * func_00108030(m->tab, o->h5A, 1);
        o->f18 += 8.6f * func_00108030(m->tab, o->h5C, 1);
    }
    if (o->h54 < 26) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 0x13;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f14 += 0.6f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 0.6f * func_00108030(m->tab, o->h5A, 1);
        o->f18 += 0.6f * func_00108030(m->tab, o->h5C, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b287:01E02760, 97 insns: on start f48 6, colours 0xFF, 0xFF, 0xFF / 0x10, 0x10, 0x80 (second alpha 0), f30 18 and length f34 by kind
   (0x50: 800.0 / 500.0 / 400.0); alpha grows by 0x40 (below 0x80) for 4 ticks, then fades by 9 and stops; after the
   first tick kinds 0/1 grow by 80.0 / 60.0 */

typedef struct {
    u8 pad0[0x30];
    f32 f30;
    f32 len;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b287_01E02760;

static s32 func_01E02760_b287(s32 arg0, Fx_b287_01E02760 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x10, 0x10, 0x80);
        if (o->kind == 0) {
            o->f30 = 18.0f;
            o->len = 800.0f;
        }
        if (o->kind == 1) {
            o->f30 = 18.0f;
            o->len = 500.0f;
        }
        if (o->kind == 2) {
            o->f30 = 18.0f;
            o->len = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        if (o->tick != 0) {
            o->len += 80.0f;
        }
    }
    if (o->kind == 1) {
        if (o->tick != 0) {
            o->len += 60.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b287:01E028F0, 225 insns: b746:01E03990's trail light in pale blue (0xC0/0xC0/0xFF) feeding four 20-point
   trails from joints 0xCB44, 0xCB46, 0xCB48 and 0xCB4A until scene frame 141; alpha up until frame 140 */

typedef struct {
    f32 x, y, z, w;
} Pt_b287_01E028F0;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b287_01E028F0 a[20];
    Pt_b287_01E028F0 b[20];
    Pt_b287_01E028F0 c[20];
    Pt_b287_01E028F0 d[20];
    u8 padB6D0[0xCB44 - 0xB6D0];
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 padCB4C[0xCBB8 - 0xCB4C];
    s16 frame;
} Scene_b287_01E028F0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[6];
    s16 hE;
    u8 pad10[0x38];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b287_01E028F0;

static s32 func_01E028F0_b287(Scene_b287_01E028F0 *g, Fx_b287_01E028F0 *o) {
    extern void b287_01E00080(Pt_b287_01E028F0 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    s16 k;
    s16 m;
    Pt_b287_01E028F0 *q;

    func_001076F0(o->col, 0xC0, 0xC0, 0xFF);
    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->hE = 30;
        func_001F5620(func_001F53A0(), g->ja, p);
        q = g->a;
        for (i = 0; i < 19; i++) {
            q[i].x = p[0];
            q[i].y = p[1];
            q[i].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jb, p);
        q = g->b;
        for (j = 0; j < 19; j++) {
            q[j].x = p[0];
            q[j].y = p[1];
            q[j].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jc, p);
        q = g->c;
        for (k = 0; k < 19; k++) {
            q[k].x = p[0];
            q[k].y = p[1];
            q[k].z = p[2];
        }
        func_001F5620(func_001F53A0(), g->jd, p);
        q = g->d;
        for (m = 0; m < 19; m++) {
            q[m].x = p[0];
            q[m].y = p[1];
            q[m].z = p[2];
        }
        o->mode = 2;
    }
    if (g->frame < 140) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (g->frame < 141) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b287_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b287_01E00080(&g->b[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jc, p);
        b287_01E00080(&g->c[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jd, p);
        b287_01E00080(&g->d[19], 20, 0, p);
    }
    o->h6 = 10;
    o->t++;
    return 0;
}

/* shape b287:01E02C80, 69 insns: a spinning, growing flash: on start size 150, colours (0xC0,0xC0,0xC0) and
   (0x80,0x80,0xFF), f5A/f5C 10; the second alpha grows by 0x30 (below 0xC0) for 14 ticks, then fades out by 15
   and stops; turns by 0x4000 and grows by 0.4 every tick after the first */

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
} Fx_b287_01E02C80;

static s32 func_01E02C80_b287(s32 arg0, Fx_b287_01E02C80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 150.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0xE) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        o->size += 0.4f;
    }
    o->tick++;
    return 0;
}

/* shape b287:01E02DA0, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x97, floor 0x30, state at 0xCB10 below 0x1E */

typedef struct {
    u8 pad[0xCB10];
    s32 state;
} Game_b287_01E02DA0;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b287_01E02DA0;

static s32 func_01E02DA0_b287(Game_b287_01E02DA0 *g, Fade_b287_01E02DA0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->tick < 0x97) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else if (g->state < 0x1E) {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    o->tick++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b287:01E02EB0, 181 insns: b152:01E03400's full-screen overlay (colour 0xC0/0xFF/0xC0) with a fixed inset: one sprite over the
   whole screen, its texture window inset by the slot's width and height; alpha up by 9 to 0x80 for 140 ticks, then
   down by 7 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b287_01E02EB0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b287_01E02EB0 p;
    } v[2];
} Pkt_b287_01E02EB0;

typedef struct {
    u8 pad0[8];
    s16 w, h;
    u8 padC[0x48];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Slot_b287_01E02EB0;

typedef struct {
    u8 pad0[0xCB28];
    Pkt_b287_01E02EB0 *pkt;
} Scene_b287_01E02EB0;

static s32 func_01E02EB0_b287(Scene_b287_01E02EB0 *s, Slot_b287_01E02EB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 w;
    f32 h;

    w = o->w;
    h = o->h;
    w /= 10.0f;
    h /= 10.0f;
    if (o->state == 1) {
        o->c0[3] = 0;
        func_001076F0(o->c0, 0xC0, 0xFF, 0xC0);
        o->state = 2;
    }
    s->pkt->r = o->c0[0];
    s->pkt->g = o->c0[1];
    s->pkt->b = o->c0[2];
    s->pkt->a = o->c0[3];
    s->pkt->q = 1.0f;
    s->pkt->v[0].p.x = 0x6BF8;
    s->pkt->v[0].p.y = 0x71F8;
    s->pkt->v[0].p.z = 0xFFFFFF;
    s->pkt->v[0].p.f = 0;
    s->pkt->v[1].p.x = 0x93F8;
    s->pkt->v[1].p.y = 0x8DF8;
    s->pkt->v[1].p.z = 0xFFFFFF;
    s->pkt->v[1].p.f = 0;
    s->pkt->v[0].s = w / 1024.0f;
    s->pkt->v[0].t = h / 512.0f;
    s->pkt->v[1].s = (640.0f - w) / 1024.0f;
    s->pkt->v[1].t = (448.0f - h) / 512.0f;
    func_002075F0(s->pkt, 0, 0);
    if (o->t < 140) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 9;
        }
    } else if (o->t > 40) {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b287", func_01E03190_b287);

/* shape b256:01E04900, 106 insns, 7 copies: b759:01E03880 with 400 slots and two more fields copied (f52 = owner fCBB0, f5A = owner fCBA2): take a free effect slot, clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b256_01E04900 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    s16 f52;
    u8 pad54[4];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b256_01E04900;

typedef struct Obj_b256_01E04900 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b256_01E04900 slots[400];
    u8 padB[0xCB14 - 0x2a0 - 400 * 0x70];
    u8 rgba[4];
    u8 padC[0xCBA2 - 0xCB14 - 4];
    s16 fB;
    u8 padD[0xCBB0 - 0xCBA2 - 2];
    s16 fA;
} Obj_b256_01E04900;

static s32 func_01E03890_b287(Obj_b256_01E04900 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b256_01E04900 *s = NULL;
    s16 i;

    for (i = 0; i < 400; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 400;
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
        s->f50 = obj->fA;
        s->f52 = obj->fA;
        s->f5A = obj->fB;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b287:01E03A40 (B287KPOINT_RAIN_3), 347 insns, 9 copies: the B092KPOINT_RAIN_3 ribbon (b092:01E04290): two
   point trails drawn as 4 spline quads per segment, the far edge fading by alpha / (3n) */

typedef struct Rgbaq_b287_01E03A40 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b287_01E03A40;

typedef struct {
    Rgbaq_b287_01E03A40 c;
    u64 xyz;
} Vtx_b287_01E03A40;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b287_01E03A40 v[4];
    u8 tail[0x40];
} Pkt_b287_01E03A40;

typedef struct {
    u8 r, g, b, a;
} C4_b287_01E03A40;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b287_01E03A40 col;
} Rib_b287_01E03A40;

static inline u8 b287_01E03A40_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E03A40_b287(void *o, Rib_b287_01E03A40 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b287_01E03A40 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b018_01E00EE0 quad[4];
    Vec_b018_01E00EE0 A[2];
    Vec_b018_01E00EE0 B[2];
    Vec_b018_01E00EE0 a4[4];
    Vec_b018_01E00EE0 b4[4];
    Pkt_b287_01E03A40 pkt __attribute__((aligned(8)));
    C4_b287_01E03A40 c0;
    C4_b287_01E03A40 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b287_01E03A40 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b287_01E03A40 *)(s32)&pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c0 = s->col;
    c1 = s->col;
    c0.a = 0;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    pkt.v[0].c = func_00107740(&c0);
    pkt.v[1].c = func_00107740(&c0);
    pkt.v[2].c = func_00107740(&c1);
    pkt.v[3].c = func_00107740(&c1);
    step = s->col.a;
    step /= (s16)(n * 3);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        pp = pa + (k - 1);
        pq = pb + (k - 1);
        for (j = 0; j < 4; j++) {
            p->v[2].c = func_00107740(&c1);
            al = c1.a;
            if (al - step > 0) {
                c1.a = b287_01E03A40_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E01580_b287(pp, 0, t);
                B[0] = func_01E01580_b287(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E01580_b287(pp, 0, t);
                B[1] = func_01E01580_b287(pq, 0, t);
            } else {
                A[0] = func_01E01580_b287(a4, 0, t);
                B[0] = func_01E01580_b287(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E01580_b287(a4, 0, t);
                B[1] = func_01E01580_b287(b4, 0, t);
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}

/* shape b256:01E04FF0, 89 insns, 3 copies: draws all live particles of the module's pool whose callback is the module's
   particle drawer (b256:01E03DC0) into one packet, inside a draw context opened only when one was drawn. */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
} Pkt_b256_01E04FF0;

typedef struct {
    u8 pad00[0x44];
    void *cb;
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b256_01E04FF0;

typedef struct {
    u8 pad0000[0x2A0];
    Slot_b256_01E04FF0 slots[400];
    u8 padB1A0[0x1984];
    s32 ctx;
    Pkt_b256_01E04FF0 *pkt;
} Pool_b256_01E04FF0;

static void func_01E03FB0_b287(Pool_b256_01E04FF0 *o) {
    extern s32 func_00207F60(void);
    extern s32 func_00208460();
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern void func_00207FD0(s32, void *, s32);
    extern void b287_01E02EB0(void *, void *);
    Pkt_b256_01E04FF0 pkt __attribute__((aligned(8)));
    s32 a[2];
    s32 b[4] __attribute__((aligned(8)));
    s32 i;
    s32 n;

    o->pkt = &pkt;
    n = 0;
    o->ctx = func_00207F60();
    o->pkt->count = 0x26;
    o->pkt->tag = 5;
    o->pkt->regs = 0x42421;
    o->pkt->pad = 0;
    func_00208460();
    func_002086D0(o->pkt, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, a, b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (o->slots[i].used != 0) {
            n++;
            if (o->slots[i].cb == b287_01E02EB0) {
                b287_01E02EB0(o, &o->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(o->ctx, func_00207500(), 0);
    }
}
