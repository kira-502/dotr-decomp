#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b721(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

/* shape b034:01E00110, 276 insns, 11 copies: texture coordinates of a sprite quad from a rectangle, 4 explicit
   modes (corner orders differ from b008:01E00080's). Module-internal: callers include it with OVL_LOCAL static. */

typedef struct Rect_b034_01E00110 {
    s16 x, y, w, h;
} Rect_b034_01E00110;

typedef struct Uv_b034_01E00110 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b034_01E00110;

typedef struct Pk_b034_01E00110 {
    u8 pad0[0x18];
    Uv_b034_01E00110 c[4];
} Pk_b034_01E00110;

static void func_01E00110_b721(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

static void func_01E00560_b721(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

static void func_01E00730_b721(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

static void func_01E00A90_b721(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b721((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b721((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

/* OVL_WARM */

/* shape b279:01E00920: quad ring sprite (b065/b193 family). The draw mode is written inline as (mode & 0xF) in each
   test: -O4 hoists it into a fresh register so the counter i can reuse mode's; a kind local coalesces with mode instead. */

typedef struct {
    f32 x, y, z, w;
} Vec_b279_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b279_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b279_01E00920;

typedef struct {
    u64 st;
    Xyz_b279_01E00920 p;
} Vtx_b279_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b279_01E00920 c;
    Vtx_b279_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b279_01E00920;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x28];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col[4];
} Anim_b279_01E00920;

typedef struct {
    u8 pad00[0x80];
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
} Obj_b279_01E00920;

extern void b721_01E00110(Pkt_b279_01E00920 *, void *, s32);

static void func_01E01040_b721(Obj_b279_01E00920 *o, Anim_b279_01E00920 *an, s32 mode, Vec_b279_01E00920 pos) {
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b279_01E00920 quad[4];
    Vec_b279_01E00920 at;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    struct {
        u64 pre;
        Pkt_b279_01E00920 pk;
    } buf;
    Col_b279_01E00920 col;
    s16 blend;
    f32 w0;
    s16 width;
    s16 i;
    s16 a;
    s16 j;
    Pkt_b279_01E00920 *p;
    f32 w1;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    j = 0;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, 0, an->rot, &at);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    width = an->width;
    b721_01E00110(p, o->b94, o->hC0);
    for (i = 0; i < o->count; j += an->step, i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + width);
        quad[1].x = w0 * func_00108030(o->bD8, a, 1);
        quad[1].z = w0 * func_00108030(o->bD8, a, 0);
        quad[3].x = w1 * func_00108030(o->bD8, a, 1);
        quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        if ((mode & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if ((mode & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if ((mode & 0xF) == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b721", func_01E01490_b721);

/* shape b721:01E01D90, 100 insns: on start f48 5..29, variant 0..7, colour white, 0x50 50..149, random 0x5A, speed
   16..35 (0xE), 0x8 0..34, hold 3..16 (0x6); alpha grows by 0x40 (below 0xC0) during the hold, then fades by 14 and
   stops */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b721_01E01D90;

static s32 func_01E01D90_b721(s32 arg0, Fx_b721_01E01D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 25 + 5;
        o->f56 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f50 = func_0019A5C8() % 100 + 50;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 20 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 14 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b721:01E01F20, 105 insns: a blue tumbling shard: size 10 growing by 10.5 for 4 frames and 10.8 after, random turn on all
   three axes, angle 45; alpha up by 0x40 for 8 frames, then down by 9 until it ends */

typedef struct {
    u8 pad0[0x20];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b721_01E01F20;

static s32 func_01E01F20_b721(void *arg0, Obj_b721_01E01F20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 10.0f;
        func_001076F0(o->c0, 0xCF, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 8, 8);
        func_001076F0(o->c0, 0x80, 0x40, 0xFF);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->ang = 0x2D;
        o->h5C = 3;
    }
    if (o->t < 8) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t < 4) {
        o->f48 += 10.5f;
    } else {
        o->f48 += 10.8f;
    }
    o->t++;
    return 0;
}

/* shape b721:01E020D0, 190 insns: a grey (0x50/0x60 flicker) glow pair by kind 0..2: size 14/20/26 with the inner part
   6 smaller, frame 0..6, h8 4..6, hold 55/45/35 ticks fading in by 12 to 0x8C, then out by 9 while growing by 1.5 a tick;
   for its first 10 ticks the angle word 0x24 is 0 or 0x8000 by the scene flag 0x9864, then it turns by 0x80 one way
   or the other by the kind's parity */

typedef struct {
    u8 pad0[0x9864];
    s16 flag;
} Game_b721_01E020D0;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[0x1A];
    s32 w24;
    u8 pad28[0x20];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    s16 frame;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b721_01E020D0;

static s32 func_01E020D0_b721(Game_b721_01E020D0 *g, Fx_b721_01E020D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f48 = 14.0f;
            o->f4C = o->f48 - 6.0f;
        } else if (o->kind == 1) {
            o->f48 = 20.0f;
            o->f4C = o->f48 - 6.0f;
        } else if (o->kind == 2) {
            o->f48 = 26.0f;
            o->f4C = o->f48 - 6.0f;
        }
        o->frame = func_0019A5C8() % 7;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        if (o->kind == 0) {
            o->hold = 55;
        }
        if (o->kind == 1) {
            o->hold = 45;
        }
        if (o->kind == 2) {
            o->hold = 35;
        }
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        }
        o->f48 += 1.5f;
        o->f4C = o->f48 - 6.0f;
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x50, 0x50, 0x50);
        func_001076F0(o->col2, 0x50, 0x50, 0x50);
    } else {
        func_001076F0(o->col, 0x60, 0x60, 0x60);
        func_001076F0(o->col2, 0x60, 0x60, 0x60);
    }
    if (o->tick < 10) {
        if (g->flag != 0) {
            o->w24 = 0;
        } else {
            o->w24 = 0x8000;
        }
    } else if (o->kind % 2 == 1) {
        o->w24 += 0x80;
    } else {
        o->w24 -= 0x80;
    }
    o->tick++;
    return 0;
}

/* shape b611:01E01BD0, 120 insns: a white spark: f48 70..99 (+6 per tick until tick 0x8C), variant 0..7, f50
   100..149, random f5A, spin 16..35, f8 0..34, life 3..16; alpha grows by 0x40 (below 0xC0) during the life,
   then fades by 14; f50 grows by the spin each tick from tick 1 to 0x59 */

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
} Fx_b611_01E01BD0;

static s32 func_01E023D0_b721(s32 arg0, Fx_b611_01E01BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 30 + 70;
        o->f56 = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f50 = func_0019A5C8() % 50 + 100;
        o->f5A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 20 + 16;
        o->f8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 14 + 3;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick < 0x5A) {
        if (o->tick != 0) {
            o->f50 += o->spin;
        }
    }
    if (o->tick < 0x8C) {
        o->f48 += 6.0f;
    }
    o->tick++;
    return 0;
}

/* shape b721:01E025B0, 90 insns: a purple tumbling glow at three random turns, sized by the scene (ctx+0x97D8): in by 0x80 for 8 ticks, then out by 9; its angle climbs a random 0..6 a tick from 90 and it ends at 270 */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
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
} Obj_b721_01E025B0;

typedef struct {
    u8 pad[0x97D8];
    f32 size;
} Game_b721_01E025B0;

static s32 func_01E025B0_b721(Game_b721_01E025B0 *g, Obj_b721_01E025B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->kind = 0;
        func_001076F0(o->col, 0x40, 0x20, 0x80);
        o->h50 = 90;
        o->mode = 2;
        o->col[3] = 0;
        o->f48 = g->size;
    }
    if (o->t < 8) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->t++;
    if (o->h50 < 270) {
        o->h50 += (s16)(func_0019A5C8() % 7);
    } else {
        o->mode = 0;
    }
    return 0;
}

/* shape b721:01E02720 (B721_OBJ_MOVE_10_), 386 insns, 1 copy (-O3,p): b363:01E04090 jittery spark trail with 20-point
   tracks: 80 tracks at 0x2E90, points at 0x9290, sine table at 0x9A6C */

typedef struct {
    Vec4f p[0x14];
} Track_b721_01E02720;

typedef struct {
    u8 pad0[0x2E90];
    Track_b721_01E02720 track[0x50];
    Vec4f pt[0x7D];
    u8 pad_9A60[0xC];
    u8 trig[1];
} World_b721_01E02720;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b721_01E02720;

#pragma optimization_level 3

static s32 func_01E02720_b721(World_b721_01E02720 *w, Spark_b721_01E02720 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 30 - 15;
        o->v.y = func_0019A5C8() % 30 - 15;
        o->v.z = func_0019A5C8() % 30 - 15;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 50 + 5;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 85 + 3;
        o->speed /= 10.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = func_0019A5C8() % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
    } else {
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
    }
    o->v.x = func_0019A5C8() % 40 - 20;
    o->v.y = func_0019A5C8() % 40 - 20;
    o->v.z = func_0019A5C8() % 40 - 20;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 1);
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
    }
    if (o->t < 7) {
        func_01E00080_b721(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    o->t++;
    return 0;
}

#pragma optimization_level reset

/* shape b721:01E02D30, 156 insns: c063:01E031E0 in blue/grey or cyan/black for kind 2, size 20, growing by the scene scale (ctx+0x97D8) / 20 per tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 hold;
    u8 padA[4];
    s16 fE;
    u8 pad10[0x10];
    s32 rot[3];
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b721_01E02D30;

typedef struct {
    u8 pad0[0x97D8];
    f32 scale;
} Ctx_b721_01E02D30;

static s32 func_01E02D30_b721(Ctx_b721_01E02D30 *g, Fx_b721_01E02D30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 0.0f;
        if (o->kind != 2) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        } else {
            func_001076F0(o->col, 0x10, 0x80, 0x80);
            func_001076F0(o->col2, 0x10, 0x10, 0x10);
        }
        o->fE = o->kind;
        if (o->kind == 0 || o->kind == 2) {
            o->rot[0] = func_0019A5C8() % 65535;
            o->rot[1] = func_0019A5C8() % 65535;
            o->rot[2] = func_0019A5C8() % 65535;
        } else {
            o->rot[0] = 0x4000;
            o->rot[1] = 0;
            o->rot[2] = 0;
        }
        o->w = 20;
        o->h = 20;
        o->mode = 2;
        o->col[3] = 0;
        o->h6 = 0;
        if (o->kind != 2) {
            o->hold = 18;
        } else {
            o->hold = 30;
        }
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 12;
        }
    } else if (o->kind != 2) {
        if (o->col2[3] > 10) {
            o->col2[3] -= 9;
        } else {
            o->mode = 0;
        }
    } else if (o->col2[3] > 8) {
        o->col2[3] -= 7;
    } else {
        o->mode = 0;
    }
    if (o->fE != 2) {
        o->f4C = o->f48 - 0.5f * o->f48;
    }
    if (o->h6 < 0) {
        o->f4C = 0.0f;
    }
    if (o->tick != 0) {
        o->f48 += g->scale / 20.0f;
    }
    o->tick++;
    return 0;
}

/* shape b721:01E02FA0, 179 insns: b247:01E01F70's kind of glow, blue (0x10/0x10/0x80) with a grey (kind 0) or white
   (kind 1) second colour, size 20; kind 0 flickers blue/violet and holds (alpha +0x10 to 0xC0) until the scene count
   0x9868 reaches 471, kind 1 flickers grey and holds (+0x18) for 30 ticks; then both fade by 9; the size follows the
   scene's 0x97D8 / 1.5 and the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x97D8];
    f32 size;
    u8 pad97DC[0x8C];
    s16 count;
} Game_b721_01E02FA0;

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
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
} Fx_b721_01E02FA0;

static s32 func_01E02FA0_b721(Game_b721_01E02FA0 *g, Fx_b721_01E02FA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        if (o->kind == 0) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
            func_001076F0(o->col2, 0x30, 0x30, 0x30);
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
            func_001076F0(o->col2, 0x80, 0x80, 0x80);
        }
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->kind == 0) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x10, 0x10, 0x80);
        } else {
            func_001076F0(o->col, 0x40, 0x10, 0x80);
        }
    } else if (o->kind == 1) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0x40, 0x40, 0x40);
        } else {
            func_001076F0(o->col, 0x60, 0x60, 0x60);
        }
    }
    if (o->kind == 0) {
        if (g->count < 471) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x10;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind == 0) {
        o->f48 = g->size / 1.5f;
    }
    if (o->kind == 1) {
        if (o->tick < 30) {
            if (o->col[3] < 0xC0) {
                o->col[3] += 0x18;
            }
        } else if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->kind == 1) {
        o->f48 = g->size / 1.5f;
    }
    func_00205C40(o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b721:01E03270, 97 insns: on start variant 0, colour (0x40, 0x20, 0x80), size 0x5A, alpha 0, f48 = 5 x the game
   float 0x97D8, 0x5A from 0x985A; alpha grows by 0x80 (below 0x80) for 11 ticks, then fades by 9 and stops; the
   rotation at 0x20 faces -0x4000 / 0x4000 by the game flag 0x9864; the size grows by 1..7 up to 0x10E; it ends at game
   step 0x9868 = 0x140 */

typedef struct {
    u8 pad0[0x97D8];
    f32 f97D8;
    u8 pad97DC[0x7E];
    s16 f985A;
    u8 pad985C[8];
    s16 flag;
    u8 pad9866[2];
    s16 step;
} Game_b721_01E03270;

typedef struct {
    u8 pad0[0x20];
    s32 rot;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 size;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
} Fx_b721_01E03270;

static s32 func_01E03270_b721(Game_b721_01E03270 *g, Fx_b721_01E03270 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f56 = 0;
        func_001076F0(o->col, 0x40, 0x20, 0x80);
        o->size = 0x5A;
        o->mode = 2;
        o->col[3] = 0;
        o->f48 = 5.0f * g->f97D8;
        o->f5A = g->f985A;
    }
    if (o->tick < 11) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x80;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->flag != 0) {
        o->rot = -0x4000;
    } else {
        o->rot = 0x4000;
    }
    o->tick++;
    if (o->size < 0x10E) {
        o->size += (s16)(func_0019A5C8() % 7 + 1);
    } else {
        o->size = 0x10E;
    }
    if (g->step == 0x140) {
        o->mode = 0;
    }
    return 0;
}

/* shape b721:01E03400, 98 insns: b283:01E036C0 family three-kind two-colour glow (grey, yellow, lilac; held 20): in by 18 up to 0x80, then out by 4 and ends */

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
} Obj_b721_01E03400;

static s32 func_01E03400_b721(s32 arg0, Obj_b721_01E03400 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->h6 = 20;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xD0, 0xD0, 0x80);
            func_001076F0(o->col2, 0xC0, 0xC0, 0x80);
            o->h6 = 20;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0xF0, 0xE0, 0xFF);
            func_001076F0(o->col2, 0xF0, 0xE0, 0xFF);
            o->h6 = 20;
        }
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x12;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x12;
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

/* shape b721:01E03590, 99 insns: a screen fog (fog block 0x2E60: 128, 2, 2, 400, colour (0, 123, 0)) following the
   game point 0x9790; its strength rises by 0.3 to 1 while the game counter 0x97C0 is over 0x1E, then falls by 0.3 and
   ends; the block is passed to func_001F6C10 while alive (NULL once ended); it ends at counter 1 */

typedef struct {
    u8 pad0[0x2E60];
    f32 f2E60;
    f32 f2E64;
    f32 f2E68;
    f32 f2E6C;
    f32 pos[3];
    u8 pad2E7C[4];
    f32 f2E80;
    f32 f2E84;
    f32 strength;
    u8 pad2E8C[0x9790 - 0x2E8C];
    f32 point[3];
    u8 pad979C[0x24];
    s32 count;
} Game_b721_01E03590;

typedef struct {
    u8 pad0[0x50];
    s16 phase;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
} Fx_b721_01E03590;

static s32 func_01E03590_b721(Game_b721_01E03590 *g, Fx_b721_01E03590 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->f2E60 = 128.0f;
        g->f2E64 = 2.0f;
        g->f2E68 = 2.0f;
        g->f2E6C = 400.0f;
        g->f2E80 = 0.0f;
        g->f2E84 = 123.0f;
        g->strength = 0.0f;
        o->mode = 2;
        o->phase = 0;
    }
    g->pos[0] = g->point[0];
    g->pos[1] = g->point[1];
    g->pos[2] = g->point[2];
    if (g->count > 0x1E) {
        if (g->strength < 1.0f) {
            g->strength += 0.3f;
        }
    } else if (!(g->strength <= 0.1f)) {
        g->strength -= 0.3f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->f2E60);
    }
    if (g->count == 1) {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b721:01E03720, 53 insns: volume fade by game state (b003:01E02330 family, layout at 0x50): state at 0x97C0
   limit 0x1E, floor 0x50, down 10, up 10, cap 0x80; state 3 sets the volume to 0x80 and ends the fade */

typedef struct {
    u8 pad[0x97C0];
    s32 state;
} Game_b721_01E03720;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b721_01E03720;

static s32 func_01E03720_b721(Game_b721_01E03720 *g, Fade_b721_01E03720 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x50) {
            o->vol -= 10;
        } else {
            o->vol = 0x50;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b721:01E03800, 127 insns: b016:01E02B40 with a grey full-screen tint (0x80), offsets written with a zero
   bias, blend 0x44, alpha up by 9 to 0x48 for 312 ticks, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b721_01E03800;

typedef struct {
    f32 s, t;
    Xyz_b721_01E03800 p;
} Tv_b721_01E03800;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b721_01E03800 v[2];
    u8 tail[0x20];
} Tex_b721_01E03800;

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
} Fx_b721_01E03800;

static s32 func_01E03800_b721(s32 arg0, Fx_b721_01E03800 *o) {
    extern void func_002087A0(void *, s32);
    Tex_b721_01E03800 pk __attribute__((aligned(8)));
    f32 z;

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    z = 0.0f;
    ((Tex_b721_01E03800 *)(s32)&pk)->flags = 0x26;
    ((Tex_b721_01E03800 *)(s32)&pk)->size = 5;
    ((Tex_b721_01E03800 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b721_01E03800 *)(s32)&pk)->pad4 = 0;
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
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
    pk.v[0].s = (o->f48 + z) / 1024.0f;
    pk.v[0].t = (o->f48 + z) / 512.0f;
    pk.v[1].s = (640.0f + o->f48 - z) / 1024.0f;
    pk.v[1].t = (448.0f + o->f48 - z) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (o->tick < 0x138) {
        if (o->col[3] < 0x48) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b721", func_01E03A00_b721);

/* shape b721:01E044D0, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x64 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b721_01E044D0 {
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
} Slot_b721_01E044D0;

typedef struct Obj_b721_01E044D0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b721_01E044D0 slots[0x64];
    u8 padB[0x97c4 - 0x2a0 - 0x64 * 0x70];
    u8 rgba[4];
    u8 padC[0x9860 - 0x97c4 - 4];
    s16 fB2B0;
} Obj_b721_01E044D0;

static s32 func_01E044D0_b721(Obj_b721_01E044D0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b721_01E044D0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x64; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x64;
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

INCLUDE_ASM("asm/nonmatchings/mod/b721", func_01E04660_b721);

/* shape b363:01E06930, 264 insns, 4 copies: draws a band of 12 quads (two rings, radius and height from the table at two
   angles 20 apart) around a position, scaled by size / 1500, turned by the object's rotation; blend from
   flags >> 4. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b363_01E06930;

typedef struct {
    u8 pad00[0x20];
    Vec4f rot;
    u8 pad30[0x18];
    f32 size;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[8];
    s16 start;
    u8 pad5C[4];
    u8 col[4];
} Band_b363_01E06930;

static void func_01E051B0_b721(Obj_b363_01E06930 *o, Band_b363_01E06930 *s, Vec4f pos, s32 flags) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    u8 pkt[0x90];
    f32 r0;
    s32 k;
    s16 b;
    s16 a;
    s16 t;
    u8 *p;
    f32 r1;
    f32 sc;

    p = pkt;
    func_00109270(p, 0, 0);
    func_00107790(p, s->col, 0);
    b = flags >> 4;
    if (b == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)b << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->mode);
    func_00208700(p, o->texture, 1);
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    sc = s->size;
    sc /= 1500.0f;
    func_00106DD0(&scale, sc, sc, sc);
    func_00108EF0(m, &scale, &s->rot, &p2);
    quad[0].y = 90.0f * func_00108030(o->xD8, s->h50, 0);
    quad[1].y = quad[0].y;
    quad[2].y = 90.0f * func_00108030(o->xD8, s->h50 + 20, 0);
    quad[3].y = quad[2].y;
    r0 = 90.0f * func_00108030(o->xD8, s->h50, 1);
    r1 = 90.0f * func_00108030(o->xD8, s->h50 + 20, 1);
    a = 0;
    for (k = 0; k < 12; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[2].x = r1 * func_00108030(o->xD8, t, 1);
            quad[2].z = r1 * func_00108030(o->xD8, t, 0);
            quad[0].x = r0 * func_00108030(o->xD8, t, 1);
            quad[0].z = r0 * func_00108030(o->xD8, t, 0);
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        } else {
            quad[2].x = quad[3].x;
            quad[2].z = quad[3].z;
            quad[0].x = quad[1].x;
            quad[0].z = quad[1].z;
            t = s->start + 30 + a;
            quad[3].x = r1 * func_00108030(o->xD8, t, 1);
            quad[3].z = r1 * func_00108030(o->xD8, t, 0);
            quad[1].x = r0 * func_00108030(o->xD8, t, 1);
            quad[1].z = r0 * func_00108030(o->xD8, t, 0);
        }
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, (u32)depth[0]);
        }
        a += 30;
    }
}

/* shape b721:01E055D0, 198 insns: c063:01E05840 cousin without the scale (scene tables past 0x9000); b756:01E061D0 family burst draw: two-colour packet, the scene rect and texture, blend by the mode's high nibble; placed at the point turned by the object; 18 quads 20 degrees wide at angles o->ang + 20 i - 200 between radii f4C and f48, each with its frame from the scene table through func_00106080 into the rect, depth-tested into the scene ot */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b721_01E055D0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x97CC - 0xC0];
    s32 ot;
    u8 pad97D0[0x9814 - 0x97D0];
    s16 frames[18];
    u8 pad9838[0x9A6C - 0x9838];
    u8 trig[1];
} Game_b721_01E055D0;

static void func_01E055D0_b721(Game_b721_01E055D0 *g, Obj_b721_01E055D0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];

    f32 m[16];
    f32 depth[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 a;
    void *p = &buf;
    s16 s;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;
    s32 t;

    *(Vec4f *)pos = *in;
    a = 0;
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
    for (i = 0; i < 18; i++) {
        func_00106080(rm, 0x14, g->frames[i], 0);
        g->rect = *(Vec4f *)rm;
        func_00108500(p, &g->rect, g->frame);
        s = o->ang + a - 200;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        t = o->ang + 20;
        s = a + t - 200;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        a += 20;
    }
}
