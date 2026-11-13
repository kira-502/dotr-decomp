#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b264(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b264(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b264(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E00D10_b264(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b264((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b264((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* shape b847:01E00E60 (IWMagicTThunder1), 723 insns, 14 copies: b081:01E05C10's beam along the module spline
   (inlined, b081:01E009A0 type 0 with its weights declared b3..b0), one sub-step per segment from the start index at
   0xE, each a 2-quad cross through the beam matrix (0x20) at the context position; float width (0x48) / 10 shrinking
   by width/(8n), alpha test from flags >> 4, alpha fades by col0.a/(3n); flags & 0xF picks the depth (0 real, 1 far)
   */

typedef struct {
    f32 x, y, z, w;
} Vec_b847_01E00E60;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b847_01E00E60;

typedef struct {
    u8 r, g, b, a;
} Col_b847_01E00E60;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b847_01E00E60;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b847_01E00E60 c;
        u64 st;
        Xyz_b847_01E00E60 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b847_01E00E60;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b847_01E00E60;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[6];
    s16 start;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 width;
    u8 pad4C[0x14];
    Col_b847_01E00E60 col0;
    Col_b847_01E00E60 col1;
} Beam_b847_01E00E60;

static inline Vec_b847_01E00E60 spline_b847_01E00E60(Vec_b847_01E00E60 *p, s32 type, f32 t) {
    Vec_b847_01E00E60 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

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

/* pts aligned: its spill slot, needed for the match */
static void func_01E012C0_b264(Ctx_b847_01E00E60 *c, Beam_b847_01E00E60 *an, Vec_b847_01E00E60 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_00109270(void *, s32, s32);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b847_01E00E60 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b847_01E00E60 ab[2];
    Vec_b847_01E00E60 ctrl[4];
    Vec_b847_01E00E60 prev;
    Vec_b847_01E00E60 q[4];
    Vec_b847_01E00E60 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b847_01E00E60 pkt __attribute__((aligned(8)));
    Col_b847_01E00E60 col;
    s32 x;
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    s16 sel;
    Pkt_b847_01E00E60 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    n = an->count;
    w /= 10.0f;
    w0 = w;
    func_00109270(p, 0, 0);
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_00108500(p, c->rect, c->mode);
    func_00208700(p, c->texture, 1);
    col = an->col0;
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    for (i = an->start; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 1; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 1.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                prev = ab[1];
            } else {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(ctrl, 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 1.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(ctrl, 0, t);
                prev = ab[1];
            }
            func_00107790(p, &col, 1);
            x = col.a - (s16)(an->col0.a / (n * 3));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107790(p, &col, 2);
            w1 = w;
            w -= w0 / (8.0f * n);
            for (k = 0; k < 2; k++) {
                func_00109A70(&q[0], &ab[0]);
                func_00109A70(&q[1], &ab[0]);
                func_00109A70(&q[2], &ab[1]);
                func_00109A70(&q[3], &ab[1]);
                if (k == 0) {
                    q[1].y += w1;
                    q[3].y += w;
                    q[0].y -= w1;
                    q[2].y -= w;
                } else if (k == 1) {
                    q[1].x += w1;
                    q[3].x += w;
                    q[1].z += w1 / 2.0f;
                    q[3].z += w / 2.0f;
                    q[0].x -= w1;
                    q[2].x -= w;
                    q[0].z -= w1 / 2.0f;
                    q[2].z -= w / 2.0f;
                }
                if ((flags & 0xF) == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, func_001A23B0(depth[0]));
                    }
                } else if ((flags & 0xF) == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                }
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b264 in the
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

static void func_01E01E10_b264(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b264((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E020D0_b264(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b264", func_01E024D0_b264);

/* shape b264:01E029E0, 74 insns: b232:01E00AC0 twin: a white/grey beam from 500 growing 10 a tick (tail 350 behind), turning 0x100: alpha 0x60 for 6 ticks, then out by 14 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    u8 pad28[0xC];
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
} Obj_b264_01E029E0;

static s32 func_01E029E0_b264(s32 arg0, Obj_b264_01E029E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 500.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
        o->h50 = 0;
        o->h5A = 15;
        o->h5C = 15;
        o->f34 = 100.0f;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
        o->w20 = 0x4000;
    }
    if (o->t < 6) {
        o->col[3] = 0x60;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 350.0f;
    o->w24 += 0x100;
    o->t++;
    return 0;
}

/* shape b264:01E02B10, 68 insns: on start f48 300, f4C 0, hold 0x6 = 10, colour white, second colour (0x80, 0x80,
   0xFF) with alpha 0, 0x5A/0x5C = 15; alpha grows by 0x30 (below 0xC0) during the hold, then fades by 15 (and stops)
   while f48 grows by 2; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
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
} Fx_b264_01E02B10;

static s32 func_01E02B10_b264(s32 arg0, Fx_b264_01E02B10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 300.0f;
        o->f4C = 0.0f;
        o->hold = 10;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        o->f5A = 15;
        o->f5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x30;
        }
    } else {
        if (o->col[3] > 0x10) {
            o->col[3] -= 15;
        } else {
            o->mode = 0;
        }
        o->f48 += 2.0f;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b264:01E02C20, 74 insns: a pink growing spark on a track point (b252:01E03410 family): size 50, f34 0.5; alpha up
   by 0x60 to 0xC0 for 50 frames, then down by 9 until it ends; sub-frame flips 3 / 5; random turn; placed at the game's
   track point h52 */

typedef struct {
    u8 pad0[0xD930];
    Vec4f pts[1];
} Game_b264_01E02C20;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1A];
    s16 idx;
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b264_01E02C20;

static s32 func_01E02C20_b264(Game_b264_01E02C20 *g, Obj_b264_01E02C20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x32;
        o->h = 0x32;
        o->sub = 3;
        o->f34 = 0.5f;
        func_001076F0(o->c0, 0xFF, 0xA0, 0x80);
        o->state = 2;
    }
    if (o->t < 0x32) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->sub == 3) {
        o->sub = 5;
    } else {
        o->sub = 3;
    }
    func_00205C40((s32)o->rot);
    o->pos = g->pts[o->idx];
    o->t++;
    return 0;
}

/* shape b264:01E02D50, 184 insns: a grey ring with a blue rim (rim blinking 0x8F/0x70 grey) riding the scene point
   numbered 0x52 (g+0xD930), turned a quarter past the camera yaw; size 80, alpha up by 0x30 for 50 ticks, then it
   fades by 15 and grows by 2; on tick 46 it drops the scene's burst at its place: 0x1E029E0, 0x1E02B10, three
   0x1E03030 and sixteen 0x1E035B0 numbered by a 0..79 ring */

typedef struct {
    f32 x, y, z, w;
} V4_b264_01E02D50;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    V4_b264_01E02D50 pos;
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 k;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Ring_b264_01E02D50;

typedef struct {
    u8 pad0[0x250];
    V4_b264_01E02D50 pos;
    u8 pad260[0xD6D0];
    V4_b264_01E02D50 pts[0x57];
    u8 padDEA0[0xE];
    s16 num;
    u8 padDEB0[8];
    s16 id;
} Scene_b264_01E02D50;

static s32 func_01E02D50_b264(Scene_b264_01E02D50 *g, Ring_b264_01E02D50 *o) {
    extern void b264_01E029E0(void);
    extern void b264_01E02B10(void);
    extern void b264_01E03030(void);
    extern void b264_01E035B0(void);
    extern s32 b264_01E04670(Scene_b264_01E02D50 *, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        o->f48 = 80.0f;
        o->f4C = 0.0f;
        o->hold = 50;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        o->h5A = 15;
        o->h5C = 15;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x30;
        }
    } else {
        if (o->col[3] > 16) {
            o->col[3] -= 15;
        } else {
            o->mode = 0;
        }
        o->f48 += 2.0f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col2, 0x8F, 0x8F, 0x8F);
    } else {
        func_001076F0(o->col2, 0x70, 0x70, 0x70);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->pos = g->pts[o->k];
    if (o->t == 46) {
        g->pos = o->pos;
        b264_01E04670(g, (s32)b264_01E029E0, 0);
        b264_01E04670(g, (s32)b264_01E02B10, 0);
        b264_01E04670(g, (s32)b264_01E03030, 0);
        b264_01E04670(g, (s32)b264_01E03030, 0);
        b264_01E04670(g, (s32)b264_01E03030, 0);
        for (i = 0; i < 16; i++) {
            g->id = g->num;
            b264_01E04670(g, (s32)b264_01E035B0, 0);
            g->num++;
            if (g->num >= 80) {
                g->num = 0;
            }
        }
    }
    o->t++;
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b264_01E03030;

typedef struct {
    u8 pad0000[0xD930];
    Vec_b264_01E03030 pts[1];
} Mgr_b264_01E03030;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    Vec_b264_01E03030 pos;
    u8 pad20[0x28];
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
} Obj_b264_01E03030;

static s32 func_01E03030_b264(Mgr_b264_01E03030 *m, Obj_b264_01E03030 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h58 == 1) {
        o->f48 = 10.0f;
        o->h56 = func_0019A5C8() % 7;
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 20;
        o->hE = func_0019A5C8() % 5 + 3;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->pos = m->pts[o->h52];
        o->h58 = 2;
    }
    if (o->h54 < o->h6) {
        o->c60[3] = 0xC0;
    } else if (o->c60[3] > 13) {
        o->c60[3] -= 12;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->h50 += o->hE;
    }
    o->h54++;
    return 0;
}

/* shape b264:01E03200, 145 insns: a yellow glow between two model joints: on start f48 0, grey 0x20 and yellow
   0x80/0x80/0x60, hold 140, height 25, size 20; alpha up by 24 to 0xC0 until the scene timer at g+0xDEC0 reaches 320,
   then down by 12; the colour blinks on the timer's parity; it sits on joint A (g+0xDE8C) moved a fifth of the way to joint
   B (g+0xDE8A) per step of h50; it spins by 0x4000 */

typedef struct {
    u8 pad0[0xDE8A];
    s16 jb;
    s16 ja;
    u8 padDE8E[0x32];
    s16 timer;
} Game_b264_01E03200;

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[4];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    f32 h;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 hh;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b264_01E03200;

static s32 func_01E03200_b264(Game_b264_01E03200 *g, Obj_b264_01E03200 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[2][4];
    f32 k;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        func_001076F0(o->c1, 0x80, 0x80, 0x60);
        o->hold = 140;
        o->h = 25.0f;
        o->w = 20;
        o->hh = 20;
        o->mode = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 320) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x18;
        }
    } else if (o->c1[3] > 13) {
        o->c1[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (g->timer % 2 == 1) {
        func_001076F0(o->c1, 0x80, 0x80, 0x20);
    } else {
        func_001076F0(o->c1, 0xA0, 0xA0, 0x30);
    }
    k = o->h50;
    func_001F5620(func_001F53A0(), g->ja, &o->x);
    func_001F5620(func_001F53A0(), g->jb, v[1]);
    func_001F5620(func_001F53A0(), g->ja, v[0]);
    o->x += k * ((v[1][0] - v[0][0]) / 5.0f);
    o->y += k * ((v[1][1] - v[0][1]) / 5.0f);
    o->z += k * ((v[1][2] - v[0][2]) / 5.0f);
    func_00205C40((s32)&o->rot);
    o->rot += 0x4000;
    o->t++;
    return 0;
}

/* shape b264:01E03450, 86 insns: a white spark: on start f48 5, variant 0..6, random 0x5A, 0xA 0..7, 0xC keeps the
   old 0x50, 0x50 10..29, speed 3..7 (0xE), 0x8 0..34, hold 1..2 (0x6); alpha 0xC0 during the hold, then it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x38];
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
} Fx_b264_01E03450;

static s32 func_01E03450_b264(s32 arg0, Fx_b264_01E03450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 5.0f;
        o->f56 = func_0019A5C8() % 7;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f5A = func_0019A5C8() % 360;
        o->fA = func_0019A5C8() % 8;
        o->fC = o->f50;
        o->f50 = func_0019A5C8() % 20 + 10;
        o->fE = func_0019A5C8() % 5 + 3;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 2 + 1;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        o->col[3] = 0xC0;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b264:01E035B0, 316 insns: B264_OBJ_MOVE_10_, a wandering spark per slot (index h50): on start it sits on start
   point idx % 6 with its 20-point trail filled there, speed (3..127)/10 at a random heading, 3..17 frames of full
   alpha; it grows for 7 frames then shrinks, blinks white/grey, jitters -40..39 and drifts by heading + jitter / 12,
   pushing its point into the trail for the first 7 frames */

typedef struct {
    u8 pad0[0x7030];
    Vec4f trail[77][20];
    u8 pad6FF0[0xD430 - 0x7030 - 77 * 0x140];
    Vec4f pos[(0xDCF0 - 0xD430) / 16];
    Vec4f start[6];
    u8 padDD50[0xE0C4 - 0xDD50];
    u8 ang[4];
} Game_b264_01E035B0;

typedef struct {
    u8 pad0[6];
    s16 size;
    s16 life;
    u8 padA[0x26];
    Vec4f jit;
    u8 pad40[8];
    f32 f48;
    f32 speed;
    s16 idx;
    s16 kind;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    u8 pad5C[4];
    u8 col[4];
} Obj_b264_01E035B0;

static s32 func_01E035B0_b264(Game_b264_01E035B0 *g, Obj_b264_01E035B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s32, s32);
    s16 i;
    Vec4f *p;
    Vec4f *q;

    if (o->state == 1) {
        o->size = 1;
        o->col[3] = 0;
        o->kind = o->idx % 6;
        g->pos[o->idx].x = 0.0f;
        g->pos[o->idx].y = 0.0f;
        g->pos[o->idx].z = 0.0f;
        o->jit.x = g->start[o->kind].x;
        o->jit.y = g->start[o->kind].y;
        o->jit.z = g->start[o->kind].z;
        q = &g->pos[o->idx];
        p = g->trail[o->idx];
        for (i = 0; i < 20; i++) {
            p->x = q->x;
            p->y = q->y;
            p->z = q->z;
            p++;
        }
        o->f48 = 200.0f;
        o->f48 /= 10.0f;
        o->speed = func_0019A5C8() % 125 + 3;
        o->speed /= 10.0f;
        o->head = (func_0019A5C8() >> 4) % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->size < 15) {
            o->size++;
        }
    } else if (o->size > 0) {
        o->size--;
    }
    if (o->t < o->life) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 30) {
        o->col[3] -= 29;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    o->jit.x = func_0019A5C8() % 80 - 40;
    o->jit.y = func_0019A5C8() % 80 - 40;
    o->jit.z = func_0019A5C8() % 80 - 40;
    if (o->t != 0) {
        g->pos[o->idx].x += o->speed * func_00108030(g->ang, o->head, 1);
        g->pos[o->idx].y += o->speed * func_00108030(g->ang, o->head, 0);
        g->pos[o->idx].x += o->jit.x / 12.0f;
        g->pos[o->idx].y += o->jit.y / 12.0f;
        g->pos[o->idx].z += o->jit.z / 12.0f;
    }
    if (o->t < 7) {
        func_01E00080_b264(&g->trail[o->idx][19], 20, 0, &g->pos[o->idx]);
    }
    o->t++;
    return 0;
}

/* shape b264:01E03AA0, 215 insns: b016:01E02B40's full-screen sprite through the scene's packet (ctx+0xDE68), in the
   object's colour (red 0xC0 at start, flickering 0xC0 / 0xB0 past scene time 78), its texture window inset by 0x8
   and 0xA tenths (the bottom by three times that), sent twice; fades in by 10 until scene time 350, then out by 13 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b264_01E03AA0;

typedef struct {
    f32 s, t;
    Xyz_b264_01E03AA0 p;
} Tv_b264_01E03AA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b264_01E03AA0 v[2];
} Tex_b264_01E03AA0;

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
} Fx_b264_01E03AA0;

typedef struct {
    u8 pad0[0xDE68];
    Tex_b264_01E03AA0 *pk;
    u8 padDE6C[0x54];
    s16 timer;
} Scn_b264_01E03AA0;

static s32 func_01E03AA0_b264(Scn_b264_01E03AA0 *g, Fx_b264_01E03AA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xC0, 0, 0);
        o->mode = 2;
    }
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
    func_002075F0((s32)g->pk, 0, 0);
    if (g->timer > 78) {
        if (g->timer % 2 == 1) {
            func_001076F0(o->col, 0xC0, 0, 0);
        } else {
            func_001076F0(o->col, 0xB0, 0, 0);
        }
    }
    if (g->timer < 350) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 14) {
        o->col[3] -= 13;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b264:01E03E00 (b264), 540 insns, 1 copy: b264 scene manager in b111:01E02F00 form: setup (camera and six
   joints, textures (4,14..15) and (5,0..4), a 256 s8 jitter with 100..179 set to rand % 4, a second 256 s8 jitter),
   step b264:01E024D0 and every slot (250 of 0x70) but b264:01E03AA0 (counted; any draws them through b264:01E04820),
   draw b264:01E029E0 bands, 01E02B10/02D50/03200 rings, 01E02C20 sprite, 01E03030/03450 jitter quads and 01E035B0
   trails; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0x8];
    s16 h50;
    u8 pad52[0x4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b264_01E03E00;

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
        s16 uv[8];
    } u94;
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
    Fx_b264_01E03E00 fx[250];
    u8 pad7000[0x30];
    Vec4f rib[88][20];
    s32 tex2[5];
    u8 padDE44[0xC];
    s32 count;
    u8 padDE54[8];
    s32 ot;
    u8 padDE60[0x28];
    s16 j[6];
    u8 padDE94[4];
    s16 cam;
    u8 padDE9A[0x22];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 padE0C2[2];
    u8 crd[0x16C];
} Scene_b264_01E03E00;

static s32 func_01E03E00_b264(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s16 func_001A22C0(f32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E024D0_b264();
    extern void func_01E012C0_b264();
    extern void b264_01E04820();
    extern void func_01E009B0_b264();
    Scene_b264_01E03E00 *g = (Scene_b264_01E03E00 *)arg0;
    s16 a;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 ang[4];
    s32 i;
    s16 k;

    a = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE230);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 410;
        g->j[0] = func_001F5560(func_001F53A0(), 0x35, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x36, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x38, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 5; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = func_001A22C0(ang[1] / 180.0f);
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
        return 0;
    }
    func_01E024D0_b264(g, 0);
    for (k = 0; k < 250; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E03AA0_b264) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    a++;
                }
            }
        }
    }
    for (k = 0; k < 250; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E029E0_b264) {
                func_00106080(rm, 0x8C, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->tex88 = g->tex[14];
                g->tex88 = g->tex2[4];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x1F;
                g->u94.uv[3] = 0x7F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0x18;
                g->hBE = 0;
                func_01E020D0_b264((void *)g, (void *)&g->fx[k], 0x20, g->fx[k].pos);
                func_01E020D0_b264((void *)g, (void *)&g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B10_b264) {
                g->hB8 = 0x18;
                func_01E009B0_b264(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02C20_b264) {
                g->tex88 = g->tex2[3];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01E10_b264((void *)g, (void *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02D50_b264) {
                g->hB8 = 0x18;
                func_01E009B0_b264(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03030_b264) {
                g->tex88 = g->tex2[0];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 0;
                func_01E00D10_b264((void *)g, (void *)&g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03200_b264) {
                g->hB8 = 0x12;
                func_01E009B0_b264(g, &g->fx[k], 0x21, &g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E03450_b264) {
                g->tex88 = g->tex2[0];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm4;
                g->hB8 = 3;
                g->hB0 = 0;
                func_01E00D10_b264((void *)g, (void *)&g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E035B0_b264) {
                g->tex88 = g->tex2[1];
                g->u94.uv[0] = 0;
                g->u94.uv[1] = 0;
                g->u94.uv[2] = 0x7F;
                g->u94.uv[3] = 0x3F;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hBE = 1;
                func_01E012C0_b264(g, &g->fx[k], g->rib[g->fx[k].h50], 0x21);
            }
        }
    }
    if (a) {
        b264_01E04820(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 264) {
        return 1;
    }
    if (g->frame == 405) {
        return 4;
    }
    if (g->frame == 396) {
        return 2;
    }
    if (g->frame > 274 && g->frame < 391) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b264:01E04670, 106 insns: takes the first free of 250 effect slots (0x70 bytes, b041:01E02C00 shape),
   clears and marks it, colours both from the scene, places it at the scene point, copies its settings and stores both
   arguments */

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
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b264_01E04670;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b264_01E04670 slot[250];
    u8 padEnd[0xDE54 - 0x2A0 - 250 * 0x70];
    u8 col[4];
    u8 padDE58[0x52];
    s16 hDEAA;
    u8 padDEAC[0xC];
    s16 hDEB8;
} Scene_b264_01E04670;

static s32 func_01E04670_b264(Scene_b264_01E04670 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b264_01E04670 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 250; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 250;
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
        sl->h50 = s->hDEB8;
        sl->h52 = s->hDEB8;
        sl->h5A = s->hDEAA;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}

/* shape b264:01E04820, 84 insns: b183:01E029E0 family draw pass: sprite packet on the stack, then every live slot (250 of 0x70 bytes) whose handler is shape b264:01E03AA0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b264_01E04820;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b264_01E04820 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b264_01E04820;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b264_01E04820;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b264_01E04820 slot[250];
    u8 padEnd[0xDE64 - 0x2A0 - 250 * 0x70];
    s32 ctx;
    Pkt_b264_01E04820 *pkt;
} Scene_b264_01E04820;

static void func_01E04820_b264(Scene_b264_01E04820 *s) {
    extern void b264_01E03AA0(Scene_b264_01E04820 *, Slot_b264_01E04820 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b264_01E04820 pkt __attribute__((aligned(8)));
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
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b264_01E03AA0) {
            b264_01E03AA0(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
