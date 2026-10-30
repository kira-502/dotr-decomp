#include "common.h"

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

static void func_01E00080_b585(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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

static void func_01E003E0_b585(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b065_01E012B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b065_01E012B0;

typedef struct {
    Col_b065_01E012B0 c;
    u64 st;
    u64 xyz;
} Vtx_b065_01E012B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b065_01E012B0 v[4];
    u8 tail[0x20];
} Pkt_b065_01E012B0;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Anim_b065_01E012B0;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b065_01E012B0;

static void func_01E005B0_b585(Obj_b065_01E012B0 *o, Anim_b065_01E012B0 *an, s32 mode, Vec_b065_01E012B0 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107740(void *, void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b065_01E012B0 quad[4];
    Vec_b065_01E012B0 at;
    Vec_b065_01E012B0 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Pkt_b065_01E012B0 pkt;
    Col_b065_01E012B0 c0;
    Col_b065_01E012B0 c1;
    Col_b065_01E012B0 c2;
    Col_b065_01E012B0 c3;
    s16 blend;
    s32 i;
    s32 a;
    s16 j;
    s16 wd;
    Pkt_b065_01E012B0 *p;
    s32 width;
    f32 w0;
    f32 w1;

    p = &pkt;
    width = an->width;
    j = 0;
    func_00107990(p, an->col0, 2);
    func_00107990(p, an->col1, 1);
    blend = mode >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col0, 0);
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    func_00107740(&c0, an->col0);
    p->v[0].c = c0;
    func_00107740(&c1, an->col1);
    p->v[2].c = c1;
    func_00107740(&c2, an->col0);
    p->v[1].c = c2;
    func_00107740(&c3, an->col1);
    p->v[3].c = c3;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    quad[0].y = an->y;
    quad[1].y = an->y;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    wd = width;
    for (i = 0; i < o->count; i++) {
        a = an->step + j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = j + (an->step + wd);
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
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        }
        j += an->step;
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

static void func_01E009C0_b585(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

/* shape b585:01E00DC0, 200 insns: the b585 module's event step (b293:01E01B10 family): counts ticks; spawns
   b585:01E01C20 at 1, b585:01E01920 at 173 and 245, b585:01E01F30 in slot 0 for the first 6 ticks, b585:01E01AB0
   (slot 0) and b585:01E01D10 at 205; from 245 to 280 follows joint 0xB248 and, before 275, spawns b585:01E01210 every
   tick in slot 2 plus on even ticks, and in slot 1 on odd ticks; b585:01E010E0 at 245; from 205 to 280 follows the
   joint and spawns b585:01E01720 in slot 2 on odd ticks */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xB248 - 0x260];
    s16 joint;
    u8 padB24A[0xB2B4 - 0xB24A];
    s16 slot;
    u8 padB2B6[0xB2BC - 0xB2B6];
    s16 timer;
} Ctx_b585_01E00DC0;

static void func_01E00DC0_b585(Ctx_b585_01E00DC0 *g) {
    extern s32 b585_01E010E0(void);
    extern s32 b585_01E01210(void);
    extern s32 b585_01E01720(void);
    extern s32 b585_01E01920(void);
    extern s32 b585_01E01AB0(void);
    extern s32 b585_01E01C20(void);
    extern s32 b585_01E01D10(void);
    extern s32 b585_01E01F30(void);
    extern void b585_01E02A30(Ctx_b585_01E00DC0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    g->timer++;
    if (g->timer == 1) {
        b585_01E02A30(g, b585_01E01C20, 0);
    }
    if (g->timer == 173) {
        b585_01E02A30(g, b585_01E01920, 0);
    }
    if (g->timer < 7) {
        g->slot = 0;
        b585_01E02A30(g, b585_01E01F30, 0);
    }
    if (g->timer == 205) {
        g->slot = 0;
        b585_01E02A30(g, b585_01E01AB0, 0);
        b585_01E02A30(g, b585_01E01D10, 0);
    }
    if (g->timer >= 245 && g->timer < 281) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        g->slot = 2;
        if (g->timer < 275) {
            b585_01E02A30(g, b585_01E01210, 0);
        }
        if (g->timer < 275 && g->timer % 2 == 0) {
            b585_01E02A30(g, b585_01E01210, 0);
        }
        g->slot = 1;
        if (g->timer < 275 && g->timer % 2 == 1) {
            b585_01E02A30(g, b585_01E01210, 0);
        }
        if (g->timer == 245) {
            b585_01E02A30(g, b585_01E010E0, 0);
        }
        if (g->timer == 245) {
            b585_01E02A30(g, b585_01E01920, 0);
        }
    }
    if (g->timer >= 205 && g->timer < 281) {
        func_001F5620(func_001F53A0(), g->joint, &g->pos);
        g->slot = 2;
        if (g->timer % 2 == 1) {
            b585_01E02A30(g, b585_01E01720, 0);
        }
    }
}

/* shape b585:01E010E0, 75 insns: b764:01E02A60 family ring (white/blue, height 260; grows 2.5 a tick while under 220): in by 64 up to 0xC0 for 14 ticks, then out by 15 and ends */

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
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b585_01E010E0;

static s32 func_01E010E0_b585(s32 arg0, Obj_b585_01E010E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f4C = 260.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->h52 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 14) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x40;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    if (o->t != 0) {
        if (o->f4C < 220.0f) {
            o->f4C += 2.5f;
        }
    }
    o->t++;
    return 0;
}

/* shape b585:01E01210 (B585_OBJ_MOVE_6_), 323 insns, 1 copy: sets up a rising puff of one of three kinds, then
   grows and fades it */

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[0x18];
    s32 f20;
    s32 f24;
    s32 f28;
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    f32 f38;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    s16 kind;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Fx_b585_01E01210;

typedef struct {
    u8 pad0[0xB2B8];
    s16 flip;
    u8 padB2BA[2];
    s16 side;
} Game_b585_01E01210;

static s32 func_01E01210_b585(Game_b585_01E01210 *g, Fx_b585_01E01210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        if (o->kind == 0) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x80, 0xC0, 0x80);
                func_001076F0(o->col0, 8, 8, 8);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x80, 0xFF, 0x80);
                func_001076F0(o->col0, 0x38, 0x38, 0x38);
            }
            o->f6 = 8;
        }
        if (o->kind == 1) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x60, 0x80, 0x60);
                func_001076F0(o->col0, 8, 8, 8);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x40, 0xFF, 0x40);
                func_001076F0(o->col0, 0x38, 0x38, 0x38);
            }
            o->f34 = 10.0f;
            o->f6 = 10;
        }
        if (o->kind == 2) {
            if (g->side % 2 == 0) {
                func_001076F0(o->col1, 0x50, 0x50, 0x50);
                func_001076F0(o->col0, 0x28, 0x28, 0x28);
            }
            if (g->side % 2 == 1) {
                func_001076F0(o->col1, 0x60, 0x60, 0x60);
                func_001076F0(o->col0, 0x30, 0x30, 0x30);
            }
            o->f34 = 70.0f;
            o->f6 = 10;
        }
        if (o->kind == 0) {
            o->f5A = 15;
            o->f5C = 15;
            o->f52 = (func_0019A5C8() >> 4) % 2;
        }
        if (o->kind == 1) {
            o->f5A = 10;
            o->f5C = 3;
        }
        if (o->kind == 2) {
            o->f5A = 60;
            o->f5C = 60;
        }
        o->f38 = func_0019A5C8() % 100 + 350;
        o->f38 = o->f38 / 10.0f;
        o->f30 = 350.0f;
        o->f30 = o->f30 / 10.0f;
        o->mode = 2;
        o->col1[3] = 0;
        if (g->flip != 0) {
            o->f20 = -0x4000;
        } else {
            o->f20 = 0x4000;
        }
        o->f28 = func_0019A5C8() % 0xFFFF;
    }
    if (o->tick < o->f6) {
        o->col1[3] = 0x80;
    } else if (o->col1[3] > 12) {
        o->col1[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        o->f48 += o->f38;
        o->f4C = 0.2f * o->f48;
        if (o->f52 == 0) {
            o->f24 += 0x80;
        } else {
            o->f24 -= 0x80;
        }
    }
    if (o->kind == 1) {
        o->f48 += o->f38 / 4.0f;
        o->f4C = 0.7f * o->f48;
        o->f34 += o->f38;
    }
    if (o->kind == 2) {
        o->f48 += o->f38 / 4.0f;
        o->f4C = 0.3f * o->f48;
        o->f34 += o->f38;
    }
    o->tick++;
    return 0;
}

/* shape b354:01E020F0, 125 insns: b183:01E012F0 family: a swelling blue/white glow (one of two colour pairs), random spin, speed 10..14.9 added to its size each frame; full alpha for 8 frames, then out by 5 */

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
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b354_01E020F0;

static s32 func_01E01720_b585(void *arg0, Obj_b354_01E020F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 80.0f;
        o->f4C = o->f48 - 58.0f;
        o->h50 = (func_0019A5C8() >> 4) % 2;
        if (o->h50 == 0) {
            func_001076F0(o->col, 0x80, 0x80, 0xC0);
            func_001076F0(o->col2, 0, 0, 0);
        }
        if (o->h50 == 1) {
            func_001076F0(o->col, 0xA0, 0xA0, 0xFF);
            func_001076F0(o->col2, 0x50, 0x50, 0x50);
        }
        o->h5A = 30;
        o->h5C = 30;
        o->f34 = func_0019A5C8() % 50 + 100;
        o->f34 /= 10.0f;
        o->state = 2;
        o->col2[3] = 0;
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
    }
    if (o->t < 8) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = 0.2f * o->f48;
    o->t++;
    return 0;
}

/* shape b585:01E01920, 98 insns: on start colours and hold by kind (0x50); both alphas grow by 0x19 (below 0x80) during the
   hold, then fade by 4 (the first ends the effect) */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x48];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Fx_b585_01E01920;

static s32 func_01E01920_b585(s32 arg0, Fx_b585_01E01920 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
            func_001076F0(o->col2, 0xF0, 0xF0, 0xF0);
            o->hold = 0xF;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xE0, 0xB0, 0xF0);
            func_001076F0(o->col2, 0xD0, 0xA0, 0xF0);
            o->hold = 0xF;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0x58, 0x58, 0x78);
            func_001076F0(o->col2, 0x58, 0x58, 0x78);
            o->hold = 0x16;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x19;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x19;
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
    o->tick++;
    return 0;
}

/* shape b585:01E01AB0, 90 insns: on start f4C 60, second colour 0xC0 grey (alpha 0), colour (0x80, 0xFF, 0x80),
   0x52 = 0, 0x5A/0x5C = 10; the second alpha grows by 12 (below 0xC0) while the game step 0xB2BC is below 0x118,
   then fades by 15 and stops; the rotation at 0x20 advances 0x4000; f4C grows by 2.5 up to 220 after the first tick;
   follows the model point 0xB248[0x50] */

typedef struct {
    u8 pad0[0xB248];
    s16 pts[0x3A];
    s16 step;
} Game_b585_01E01AB0;

typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    s32 rot[4];
    u8 pad30[0x1C];
    f32 f4C;
    s16 pt;
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b585_01E01AB0;

static s32 func_01E01AB0_b585(Game_b585_01E01AB0 *g, Fx_b585_01E01AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->f4C = 60.0f;
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col, 0x80, 0xFF, 0x80);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->step < 0x118) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 12;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    if (o->tick != 0) {
        if (o->f4C < 220.0f) {
            o->f4C += 2.5f;
        }
    }
    o->tick++;
    func_001F5620(func_001F53A0(), g->pts[o->pt], o->pos);
    return 0;
}

/* shape b585:01E01C20, 60 insns: volume fade (layout at 0x50): for 0x97 frames down 10 to 0x30, then while the game
   state at 0xB210 is below 0x1E up 10 to 0x80; state 3 plays at 0x80 and ends the fade */

typedef struct {
    u8 pad[0xB210];
    s32 state;
} Game_b585_01E01C20;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b585_01E01C20;

static s32 func_01E01C20_b585(Game_b585_01E01C20 *g, Fade_b585_01E01C20 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 0x97) {
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
    }
    o->t++;
    if (g->state == 3) {
        func_001F6D00(0x80);
        o->mode = 0;
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b585:01E01D10, 136 insns: b432:01E03460 in 0x80/0x80/0x90, alpha up by 22 to 0x58 until scene count 280 (s16 at ctx+0xB2BC), then down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b585_01E01D10;

typedef struct {
    f32 s, t;
    Xyz_b585_01E01D10 p;
} Tv_b585_01E01D10;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b585_01E01D10 v[2];
    u8 tail[0x20];
} Tex_b585_01E01D10;

typedef struct {
    u8 pad0[0xB2BC];
    s16 count;
} Ctx_b585_01E01D10;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b585_01E01D10;

static s32 func_01E01D10_b585(Ctx_b585_01E01D10 *g, Fx_b585_01E01D10 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b585_01E01D10 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x90);
        o->mode = 2;
    }
    ((Tex_b585_01E01D10 *)(s32)&pk)->flags = 0x26;
    ((Tex_b585_01E01D10 *)(s32)&pk)->size = 5;
    ((Tex_b585_01E01D10 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b585_01E01D10 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
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
    if (g->count < 280) {
        if (o->col[3] < 0x58) {
            o->col[3] += 0x16;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b585:01E01F30, 191 insns: b362:01E028A0's window in grey 0x30 at ctx+0xB228 that zooms out by 30 each way
   after tick 156; alpha up by 9 for 156 ticks, then down by 7 after tick 40 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b585_01E01F30;

typedef struct {
    f32 s, t;
    Xyz_b585_01E01F30 p;
} Tv_b585_01E01F30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b585_01E01F30 v[2];
} Tex_b585_01E01F30;

typedef struct {
    u8 pad[0xB228];
    Tex_b585_01E01F30 *pk;
} Game_b585_01E01F30;

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
} Fx_b585_01E01F30;

static s32 func_01E01F30_b585(Game_b585_01E01F30 *g, Fx_b585_01E01F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x30, 0x30, 0x30);
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
    g->pk->v[1].t = (448.0f - fy) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick > 156) {
        o->f8 += 30;
        o->fA += 30;
    }
    if (o->tick < 156) {
        if (o->col[3] < 0x80) {
            o->col[3] += 9;
        }
    } else if (o->tick > 40) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b585", func_01E02230_b585);

/* shape b388:01E01B60, 98 insns, 3 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b388_01E01B60 {
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
} Slot_b388_01E01B60;

typedef struct Obj_b388_01E01B60 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b388_01E01B60 slots[0x190];
    u8 padB[0xb214 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb2b4 - 0xb214 - 4];
    s16 fB2B0;
} Obj_b388_01E01B60;

static s32 func_01E02A30_b585(Obj_b388_01E01B60 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b388_01E01B60 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
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

/* shape b098:01E02650, 89 insns, 7 copies: draws the module's live objects: sets up a sprite packet on the stack,
   then for each of the 400 objects (0x70 bytes) that is active and uses the module's draw routine
   (b098:01E01C50), calls it; sends the list if any object was active. */

typedef struct {
    s16 n;
    s16 nreg;
    s32 pad4;
    u64 regs;
    u8 rest[0x30];
} Pk_b098_01E02650;

typedef struct Obj_b098_01E02650 {
    u8 pad0[0x44];
    void *draw;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Obj_b098_01E02650;

typedef struct {
    u8 pad0[0x2A0];
    Obj_b098_01E02650 objs[400];
    u8 padB1A0[0x84];
    s32 list;
    Pk_b098_01E02650 *pk;
} Ctx_b098_01E02650;

typedef struct {
    u64 tag;
    Pk_b098_01E02650 pk;
    s32 a[2];
    s32 b[2];
} Buf_b098_01E02650;

extern void b585_01E01F30(Ctx_b098_01E02650 *ctx, Obj_b098_01E02650 *o);

static void func_01E02BC0_b585(Ctx_b098_01E02650 *ctx) {
    extern s32 func_001F53A0();
    Buf_b098_01E02650 buf;
    s32 i;
    s32 n;

    ctx->pk = &buf.pk;
    n = 0;
    ctx->list = func_00207F60();
    ctx->pk->nreg = 0x26;
    ctx->pk->n = 5;
    ctx->pk->regs = 0x42421;
    ctx->pk->pad4 = 0;
    func_00208460();
    func_002086D0(ctx->pk, 0x48 | ((s64)0x80 << 32));
    func_001F7060(func_001F53A0(), 0, (s32)buf.a, (s32)buf.b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (ctx->objs[i].active != 0) {
            n++;
            if (ctx->objs[i].draw == b585_01E01F30) {
                b585_01E01F30(ctx, &ctx->objs[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(ctx->list, (s32)func_00207500(), 0);
    }
}
