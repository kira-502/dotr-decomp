#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b703(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b703(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b703(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b703((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b703((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

static void func_01E00F60_b703(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b703 in the
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

static void func_01E012C0_b703(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b703((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static Vec_b018_01E00EE0 func_01E01580_b703(Vec_b018_01E00EE0 *p, s32 type, f32 t) {
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

static void func_01E019C0_b703(Obj_b020_01E00E70 *o, Fx_b020_01E00E70 *fx, s32 flags, Vec4f pos) {
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

static void func_01E01D30_b703(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b703:01E01F00, 283 insns: B703_W_S, the effect scene's step (b522:01E01D30 form): counts the frame (0xCBBC);
   frame 1 spawns 0x1E03320 and four 0x1E02BD0 at angles 0/90 (side 0) and 45/135 (side 1); frame 10 spawns
   0x1E02E70; frame 123 puts the scene point on the camera, 5 down, spawns 0x1E03200, four 0x1E02840 (same angles),
   twenty 0x1E02370 and 0x1E026B0; frames 118..150 spawn 0x1E02520 at joint 0xCB4A; frames 91/119 and 102/119
   spawn thirteen 0x1E02A00 1.5 below joint 0xCB4C */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xCB4A - 0x260];
    s16 jc;
    s16 jd;
    u8 padCB4E[0xCBA6 - 0xCB4E];
    s16 ang;
    u8 padCBA8[0xCBB4 - 0xCBA8];
    s16 side;
    u8 padCBB6[6];
    s16 t;
} Scene_b703_01E01F00;

static void func_01E01F00_b703(Scene_b703_01E01F00 *g) {
    extern void b703_01E02370(void);
    extern void b703_01E02520(void);
    extern void b703_01E026B0(void);
    extern void b703_01E02840(void);
    extern void b703_01E02A00(void);
    extern void b703_01E02BD0(void);
    extern void b703_01E02E70(void);
    extern void b703_01E03200(void);
    extern void b703_01E03320(void);
    extern void b703_01E03C70(Scene_b703_01E01F00 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    s16 i;

    g->t++;
    if (g->t == 1) {
        b703_01E03C70(g, b703_01E03320, 0);
    }
    if (g->t == 10) {
        b703_01E03C70(g, b703_01E02E70, 0);
    }
    if (g->t == 123) {
        func_001F5F90(func_001F5380(), &g->pos);
        g->pos.y -= 5.0f;
        b703_01E03C70(g, b703_01E03200, 0);
        g->ang = 0;
        g->side = 0;
        b703_01E03C70(g, b703_01E02840, 0);
        g->ang = 90;
        g->side = 0;
        b703_01E03C70(g, b703_01E02840, 0);
        g->ang = 45;
        g->side = 1;
        b703_01E03C70(g, b703_01E02840, 0);
        g->ang = 135;
        g->side = 1;
        b703_01E03C70(g, b703_01E02840, 0);
        for (i = 0; i < 20; i++) {
            b703_01E03C70(g, b703_01E02370, 0);
        }
        g->side = 0;
        b703_01E03C70(g, b703_01E026B0, 0);
    }
    if (g->t == 1) {
        g->ang = 0;
        g->side = 0;
        b703_01E03C70(g, b703_01E02BD0, 0);
        g->ang = 90;
        g->side = 0;
        b703_01E03C70(g, b703_01E02BD0, 0);
        g->ang = 45;
        g->side = 1;
        b703_01E03C70(g, b703_01E02BD0, 0);
        g->ang = 135;
        g->side = 1;
        b703_01E03C70(g, b703_01E02BD0, 0);
    }
    if (g->t >= 118 && g->t <= 150) {
        func_001F5620(func_001F53A0(), g->jc, &g->pos);
        b703_01E03C70(g, b703_01E02520, 0);
    }
    if (g->t == 91 || g->t == 119) {
        func_001F5620(func_001F53A0(), g->jd, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b703_01E03C70(g, b703_01E02A00, 0);
        }
    }
    if (g->t == 102 || g->t == 119) {
        func_001F5620(func_001F53A0(), g->jd, &g->pos);
        g->pos.y -= 1.5f;
        for (i = 0; i < 13; i++) {
            b703_01E03C70(g, b703_01E02A00, 0);
        }
    }
}

/* shape b703:01E02370, 105 insns: a grey spark: size 4..6, random sub-frame 0..2, height 10..49, angle, rise 16..35, width 0..34,
   hold 8..14, rising once started; alpha up by 0x40 to 0xC0 until the hold, then down by 14 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    u8 padA[4];
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
} Obj_b703_01E02370;

static s32 func_01E02370_b703(void *arg0, Obj_b703_01E02370 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 3 + 4;
        o->sub = func_0019A5C8() % 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->y = func_0019A5C8() % 40 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 20 + 0x10;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 7 + 8;
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

/* shape b703:01E02520, 98 insns: b282:01E01C20 family white spark (random size 10..12) held 3..5 ticks: in by 64 up to 0xC0, then out by 14 and ends */

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
} Obj_b703_01E02520;

static s32 func_01E02520_b703(s32 arg0, Obj_b703_01E02520 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 3 + 10;
        o->kind = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 40 + 10;
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
    o->t++;
    return 0;
}

/* shape b703:01E026B0, 98 insns: b283:01E036C0 family three-kind two-colour glow (blue, green/purple, lavender; held 8/8/22): in by 38 up to 0xC0, then out by 9 and ends */

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
} Obj_b703_01E026B0;

static s32 func_01E026B0_b703(s32 arg0, Obj_b703_01E026B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0x60, 0x60, 0xFF);
            func_001076F0(o->col2, 0x60, 0x60, 0xFF);
            o->h6 = 8;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0, 0x30, 0xF0);
            func_001076F0(o->col2, 0x30, 0, 0xF0);
            o->h6 = 8;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0x58, 0x58, 0x78);
            func_001076F0(o->col2, 0x58, 0x58, 0x78);
            o->h6 = 22;
        }
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xc0) {
            o->col[3] += 0x26;
        }
        if (o->col2[3] < 0xc0) {
            o->col2[3] += 0x26;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->col2[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b703:01E02840, 112 insns: b413:01E023D0 twin shock wave (white/blue, scale 6): kind 0 from 670 growing 30 (width 5.5), kind 1 from 630 growing 10, kind 2 400 x 8 fixed; in by 64 up to 0x80 for 4 ticks, then out by 9 and ends; +0x52 counts to 25; spins 6 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
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
} Obj_b703_01E02840;

static s32 func_01E02840_b703(s32 arg0, Obj_b703_01E02840 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 6.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x40, 0x40, 0xFF);
        if (o->h50 == 0) {
            o->f30 = 5.5f;
            o->f34 = 670.0f;
        }
        if (o->h50 == 1) {
            o->f30 = 5.5f;
            o->f34 = 630.0f;
        }
        if (o->h50 == 2) {
            o->f30 = 8.0f;
            o->f34 = 400.0f;
        }
        o->mode = 2;
        o->col2[3] = 0;
        o->h52 = 0;
    }
    if (o->t < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->h50 == 0 && o->t != 0) {
        o->f34 += 30.0f;
    }
    if (o->h50 == 1 && o->t != 0) {
        o->f34 += 10.0f;
    }
    if (o->t != 0) {
        if (o->h52 < 25) {
            o->h52++;
        }
    }
    o->t++;
    o->h5A += 6;
    return 0;
}

/* shape b703:01E02A00, 113 insns: on start 0x8/0xA = 100, variant 2..4, colour white, random heading 0x5A and a jump of
   6.6 along it (z by the cosine, x by the sine of the game table 0xCDC0); alpha grows by 0x40 (below 0x80) for 10
   ticks, then fades by 9 and stops; after the first tick it moves 0.5 along the heading; func_00205C40 on the
   rotation */

typedef struct {
    u8 pad0[0xCDC0];
    u8 trig[1];
} Game_b703_01E02A00;

typedef struct {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x24];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 heading;
    u8 pad5C[4];
    u8 col[4];
} Fx_b703_01E02A00;

static s32 func_01E02A00_b703(Game_b703_01E02A00 *g, Fx_b703_01E02A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->mode == 1) {
        o->f8 = 100;
        o->fA = o->f8;
        o->f56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
        o->heading = (func_0019A5C8() >> 4) % 360;
        o->z += 6.6f * func_00108030(g->trig, o->heading, 0);
        o->x += 6.6f * func_00108030(g->trig, o->heading, 1);
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->z += 0.5f * func_00108030(g->trig, o->heading, 0);
        o->x += 0.5f * func_00108030(g->trig, o->heading, 1);
    }
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b292:01E01C90, 165 insns, 2 copies: a blue ring travelling between two model joints by kind (radius grows 30/10/0 a
   frame); fades in over 4 frames, then out; each frame it is placed on the first joint and slides toward the
   second by up to 25/25 of the way */

typedef struct {
    u8 pad0[0xCB48];
    s16 j0;
    s16 j1;
} World_b292_01E01C90;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x10];
    f32 thick;
    f32 radius;
    u8 pad38[0x10];
    f32 size;
    u8 pad4C[4];
    s16 kind;
    s16 step;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
} Ring_b292_01E01C90;

static s32 func_01E02BD0_b703(World_b292_01E01C90 *w, Ring_b292_01E01C90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    Vec4f v[2];
    f32 k;

    if (o->state == 1) {
        o->size = 6.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x40, 0x40, 0xFF);
        if (o->kind == 0) {
            o->thick = 3.0f;
            o->radius = 70.0f;
        }
        if (o->kind == 1) {
            o->thick = 3.0f;
            o->radius = 30.0f;
        }
        if (o->kind == 2) {
            o->thick = 8.0f;
            o->radius = 400.0f;
        }
        o->state = 2;
        o->c1[3] = 0;
        o->step = 0;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->kind == 0 && o->t != 0) {
        o->radius += 30.0f;
    }
    if (o->kind == 1 && o->t != 0) {
        o->radius += 10.0f;
    }
    if (o->t != 0) {
        if (o->step < 0x19) {
            o->step++;
        }
    }
    o->t++;
    o->ang += 6;
    func_001F5620(func_001F53A0(), w->j0, &o->pos);
    func_001F5620(func_001F53A0(), w->j1, v);
    k = o->step;
    v[0].x = (v[0].x - o->pos.x) / 25.0f;
    v[0].y = (v[0].y - o->pos.y) / 25.0f;
    v[0].z = (v[0].z - o->pos.z) / 25.0f;
    o->pos.x += v[0].x * k;
    o->pos.y += v[0].y * k;
    o->pos.z += v[0].z * k;
    return 0;
}

/* shape b703:01E02E70 (B703_OBJ_MOVE_10_), 225 insns: b746:01E03990's trail light in blue-violet (0x60/0x60/0xC0)
   feeding four 20-point trails from joints 0xCB48, 0xCB4A, 0xCB4C and 0xCB4E until scene frame 131; alpha up until
   frame 130 */

typedef struct {
    f32 x, y, z, w;
} Pt_b703_01E02E70;

typedef struct {
    u8 pad0[0xB1D0];
    Pt_b703_01E02E70 a[20];
    Pt_b703_01E02E70 b[20];
    Pt_b703_01E02E70 c[20];
    Pt_b703_01E02E70 d[20];
    u8 padB6D0[0x1478];
    s16 ja;
    s16 jb;
    s16 jc;
    s16 jd;
    u8 padCB50[0x6C];
    s16 frame;
} Scene_b703_01E02E70;

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
} Fx_b703_01E02E70;

static s32 func_01E02E70_b703(Scene_b703_01E02E70 *g, Fx_b703_01E02E70 *o) {
    extern void b703_01E00080(Pt_b703_01E02E70 *, s32, s32, f32 *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 p[4];
    s16 i;
    s16 j;
    s16 k;
    s16 m;
    Pt_b703_01E02E70 *q;

    func_001076F0(o->col, 0x60, 0x60, 0xC0);
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
    if (g->frame < 131) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->mode = 0;
    }
    if (g->frame < 132) {
        func_001F5620(func_001F53A0(), g->ja, p);
        b703_01E00080(&g->a[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jb, p);
        b703_01E00080(&g->b[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jc, p);
        b703_01E00080(&g->c[19], 20, 0, p);
        func_001F5620(func_001F53A0(), g->jd, p);
        b703_01E00080(&g->d[19], 20, 0, p);
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

static s32 func_01E03200_b703(s32 arg0, Fx_b287_01E02C80 *o) {
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

static s32 func_01E03320_b703(Game_b287_01E02DA0 *g, Fade_b287_01E02DA0 *o) {
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

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E03430_b703(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b703", func_01E03440_b703);

/* shape b703:01E03C70, 82 insns: c035:01E01150 family: take the first free effect slot of 400 (0x70 bytes each, at ctx+0x2A0), clear it, give it the scene colour twice, the scene position, the scene value twice, its angle and both arguments; returns 1 when it got one */

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
} Obj_b703_01E03C70;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x2a0 - 0x25C];
    Obj_b703_01E03C70 slot[400];
    u8 padEnd[0xcb14 - 0x2a0 - 400 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padCB18[0x8E];
    s16 ang;
    u8 padCBA8[0xC];
    s16 val;
} Ctx_b703_01E03C70;

static s32 func_01E03C70_b703(Ctx_b703_01E03C70 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b703_01E03C70 *s;

    s = NULL;
    for (i = 0; i < 400; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 400;
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
        s->h50 = ctx->val;
        s->h52 = ctx->val;
        s->h5A = ctx->ang;
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b703:01E03E20 (B703KPOINT_RAIN_3), 347 insns, 9 copies: the B092KPOINT_RAIN_3 ribbon (b092:01E04290): two
   point trails drawn as 4 spline quads per segment, the far edge fading by alpha / (3n) */

typedef struct Rgbaq_b703_01E03E20 {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b703_01E03E20;

typedef struct {
    Rgbaq_b703_01E03E20 c;
    u64 xyz;
} Vtx_b703_01E03E20;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b703_01E03E20 v[4];
    u8 tail[0x40];
} Pkt_b703_01E03E20;

typedef struct {
    u8 r, g, b, a;
} C4_b703_01E03E20;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x58];
    C4_b703_01E03E20 col;
} Rib_b703_01E03E20;

static inline u8 b703_01E03E20_fade(s32 x, s16 step) {
    s16 r = x;

    r -= step;
    if (r < 0) {
        r = 0;
    }
    return r;
}

static void func_01E03E20_b703(void *o, Rib_b703_01E03E20 *s, Vec_b018_01E00EE0 *pa __attribute__((aligned(16))), Vec_b018_01E00EE0 *pb __attribute__((aligned(16)))) {
    extern Rgbaq_b703_01E03E20 func_00107740(void *);
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
    Pkt_b703_01E03E20 pkt __attribute__((aligned(8)));
    C4_b703_01E03E20 c0;
    C4_b703_01E03E20 c1;
    s32 k;
    s32 j;
    s16 n;
    s16 al;
    s16 step;
    s32 ot;
    Pkt_b703_01E03E20 *p;
    Vec_b018_01E00EE0 *pp;
    Vec_b018_01E00EE0 *pq;
    f32 t;

    ot = (s32)func_00207500();
    n = s->n;
    p = (Pkt_b703_01E03E20 *)(s32)&pkt;
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
                c1.a = b703_01E03E20_fade(al, step);
            } else {
                c1.a = 0;
            }
            p->v[3].c = func_00107740(&c1);
            if (k != 0) {
                A[0] = func_01E01580_b703(pp, 0, t);
                B[0] = func_01E01580_b703(pq, 0, t);
                t += 0.25f;
                A[1] = func_01E01580_b703(pp, 0, t);
                B[1] = func_01E01580_b703(pq, 0, t);
            } else {
                A[0] = func_01E01580_b703(a4, 0, t);
                B[0] = func_01E01580_b703(b4, 0, t);
                t += 0.25f;
                A[1] = func_01E01580_b703(a4, 0, t);
                B[1] = func_01E01580_b703(b4, 0, t);
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
