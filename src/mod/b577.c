#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b577(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b577(Obj_b016_01E014F0 *o, Cam_b016_01E014F0 *cam, s32 flags, Vec4f c) {
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

static void func_01E00510_b577(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

static void func_01E006E0_b577(Obj_b094_01E00920 *obj, Data_b094_01E00920 *data, s32 flags, Vec_b094_01E00920 *color) {
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

/* shape b577:01E00A40, 254 insns: the scene script of b577 (b232:01E00480's kind): counts ctx+0x4B06; each tick it
   puts the mark (ctx+0x4470) on joint 0x4A92, lifts it half way toward joint 0x4A94 and moves it 5 along z by the
   flag ctx+0x4B00; spawns on ticks 1, 45, 110 (ten, the first three into slots 0..2), 200 and 206; on odd ticks
   252..380 a 0x1E01250; from tick 202 to 380 it puts the burst point (ctx+0x250) on the camera at height 42, spawns a
   0x1E01360 on odd ticks and turns ctx+0x4AF6 by 3; from 226 to 300 it puts the point on joint 0x4A90 lifted by 10 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[4];
    u8 pad260[0x4470 - 0x260];
    f32 m[4];
    u8 pad4480[0x4A90 - 0x4480];
    s16 id2;
    s16 id0;
    s16 id1;
    u8 pad4A96[0x4AF6 - 0x4A96];
    s16 turn;
    u8 pad4AF8[4];
    s16 slot;
    u8 pad4AFE[2];
    s16 flag;
    u8 pad4B02[4];
    s16 t;
} Ctx_b577_01E00A40;

static void func_01E00A40_b577(Ctx_b577_01E00A40 *g) {
    extern void b577_01E00E40();
    extern void b577_01E01100();
    extern void b577_01E01250();
    extern void b577_01E01360();
    extern void b577_01E01490();
    extern void b577_01E01590();
    extern void b577_01E01680();
    extern void b577_01E018C0();
    extern void b577_01E01A00();
    extern void b577_01E01AE0();
    extern void b577_01E02690(Ctx_b577_01E00A40 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 a[4];
    f32 b[4];

    g->t++;
    func_001F5620(func_001F53A0(), g->id0, g->m);
    func_001F5620(func_001F53A0(), g->id0, a);
    func_001F5620(func_001F53A0(), g->id1, b);
    a[1] = (b[1] - a[1]) / 2.0f;
    g->m[1] += a[1];
    if (g->flag != 0) {
        g->m[2] -= 5.0f;
    } else {
        g->m[2] += 5.0f;
    }
    if (g->t == 1) {
        b577_01E02690(g, b577_01E01A00, 0);
    }
    if (g->t == 110) {
        g->slot = 0;
        b577_01E02690(g, b577_01E00E40, 0);
        g->slot = 1;
        b577_01E02690(g, b577_01E00E40, 0);
        g->slot = 2;
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
        b577_01E02690(g, b577_01E00E40, 0);
    }
    if (g->t == 45) {
        b577_01E02690(g, b577_01E01AE0, 0);
    }
    if (g->t == 200) {
        b577_01E02690(g, b577_01E01490, 0);
        b577_01E02690(g, b577_01E01590, 0);
        b577_01E02690(g, b577_01E01590, 0);
        b577_01E02690(g, b577_01E01100, 0);
        b577_01E02690(g, b577_01E01100, 0);
    }
    if (g->t == 206) {
        b577_01E02690(g, b577_01E01680, 0);
        b577_01E02690(g, b577_01E018C0, 0);
    }
    if (g->t >= 252 && g->t < 381) {
        if (g->t % 2 == 1) {
            b577_01E02690(g, b577_01E01250, 0);
        }
    }
    if (g->t >= 202 && g->t < 381) {
        func_001F5620(func_001F53A0(), g->id2, g->pos);
        func_001F5F90(func_001F53A0(), g->pos);
        g->pos[1] = 42.0f;
        if (g->t % 2 == 1) {
            b577_01E02690(g, b577_01E01360, 0);
        }
        g->turn += 3;
    }
    if (g->t >= 226 && g->t < 301) {
        func_001F5620(func_001F53A0(), g->id2, g->pos);
        g->pos[2] = 0.0f;
        g->pos[1] += 10.0f;
    }
}

/* shape b577:01E00E40, 176 insns: b232:01E00710's flickering pair (kinds 2+ also roll three 0..65534 words): variant 0..6, f8 4..6, sway angle 0..359; both
   alphas grow by 12 (below 0x80) until the scene count 0x4B06 reaches 335, then fade by 9 (the first ends it); while the scene count is
   set the size grows by 0.5 to 20 with f4C a fifth of it; it sways 20 x sin(0xE), turning 5 a tick, and 0x5A grows 10 */

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[4];
    s16 swing;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
    f32 f48;
    f32 f4C;
    s16 kind;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 h5A;
    s16 sway;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b577_01E00E40;

typedef struct {
    u8 pad0[0x4B06];
    s16 grow;
    u8 pad4B08[0x200];
    u8 sin[1];
} Ctx_b577_01E00E40;

static s32 func_01E00E40_b577(Ctx_b577_01E00E40 *g, Fx_b577_01E00E40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);
    f32 f;

    if (o->mode == 1) {
        o->f56 = func_0019A5C8() % 7;
        o->mode = 2;
        o->f8 = func_0019A5C8() % 3 + 4;
        o->swing = func_0019A5C8() % 360;
        if (o->kind >= 2) {
            o->w20 = func_0019A5C8() % 0xFFFF;
            o->w24 = func_0019A5C8() % 0xFFFF;
            o->w28 = func_0019A5C8() % 0xFFFF;
        }
        o->sway = 0;
        o->h5A = 0;
    }
    if (g->grow < 335) {
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
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    if (g->grow != 0) {
        if (o->f48 < 20.0f) {
            o->f48 += 0.5f;
        }
        f = o->f4C = 0.2f * o->f48;
        if (f < 0.0f) {
            o->f4C = 0.0f;
        }
    }
    o->sway = func_001A22C0(20.0f * func_00108030(g->sin, o->swing, 0));
    o->swing += 5;
    o->h5A += 10;
    o->tick++;
    return 0;
}

/* shape b577:01E01100, 84 insns: on start f48 120, f4C 0, colour white, second colour (0x80, 0x20, 0xFF) with alpha 0,
   random rotation, 0x5A = 20, 0x5C = 3; alpha grows by 0x40 (below 0xC0) for 0x16 ticks, then fades by 11 and stops;
   f48 grows by 3 after the first tick */

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
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b577_01E01100;

static s32 func_01E01100_b577(s32 arg0, Fx_b577_01E01100 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 120.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x20, 0xFF);
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f5A = 20;
        o->f5C = 3;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 0x16) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xC) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 3.0f;
    }
    o->tick++;
    return 0;
}

/* shape b577:01E01250, 65 insns: a white/purple beam growing 30 a tick from 40 (tail 40 behind) at turn 0x4000: alpha at least 0xC0 for 5 ticks, then out by 11 and ends */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b577_01E01250;

static s32 func_01E01250_b577(s32 arg0, Obj_b577_01E01250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        o->f4C = 0.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0x80, 0x20, 0xFF);
        o->h5A = 10;
        o->h5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 5) {
        if (o->col[3] < 0xC0) {
            o->col[3] = 0xC0;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    o->f48 += 30.0f;
    o->f4C = o->f48 - 40.0f;
    o->w20 = 0x4000;
    o->t++;
    return 0;
}

/* shape b577:01E01360, 75 insns: a white-grey rising flash (b749:01E028A0 shape, f4C floored at 0, no turn): f48 200 with f4C 58 below, rising by
   f34 = 950 / 10 a frame with f4C 400 below; full alpha for 13 frames, then down by 14 until it ends; y turns 0x100 */

typedef struct {
    u8 pad0[0x24];
    s32 rot1;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b577_01E01360;

static s32 func_01E01360_b577(void *arg0, Obj_b577_01E01360 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 200.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->h50 = 0;
        o->w = 0xF;
        o->h = 0xF;
        o->f34 = 950.0f;
        o->f34 /= 10.0f;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xD) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->f48 += o->f34;
    o->f4C = o->f48 - 400.0f;
    if (o->f4C < 0.0f) {
        o->f4C = 0.0f;
    }
    o->t++;
    return 0;
}

/* shape b577:01E01490, 63 insns: a white-violet glow (b529:01E02C10 shape): both alphas up by 25 to 0x80 for 22 frames, then down by 4; it ends
   when the first runs out */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x4C];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Obj_b577_01E01490;

static s32 func_01E01490_b577(void *arg0, Obj_b577_01E01490 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        func_001076F0(o->c0, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->c1, 0x80, 0x10, 0xFF);
        o->hold = 0x16;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x19;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x19;
        }
    } else {
        if (o->c0[3] > 5) {
            o->c0[3] -= 4;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 5) {
            o->c1[3] -= 4;
        } else {
            o->c1[3] = 0;
        }
    }
    o->t++;
    return 0;
}

/* shape b577:01E01590, 59 insns: a white-violet spinning flash (b236:01E01B70 family): scale 75, size 10x10; alpha up by 0x40 to 0xC0 for 22
   frames, then down by 11 until it ends; a random turn plus a quarter each frame */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    u8 pad50[4];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b577_01E01590;

static s32 func_01E01590_b577(void *arg0, Obj_b577_01E01590 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 75.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x80, 0x20, 0xFF);
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x16) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b577:01E01680, 143 insns: b084:01E02640 with the trail at m+0x4480 filled from the source point m+0x4470,
   which is also copied to the head point m+0x48E0; size 30; full alpha until the timer at m+0x4B06 reaches 385;
   white/grey blink; for ticks 1..33 the head point moves its depth by 5 (down when m+0x4B00 is set) */

typedef struct {
    f32 x, y, z, w;
} Vec_b577_01E01680;

typedef struct {
    u8 pad0000[0x4470];
    Vec_b577_01E01680 src;
    Vec_b577_01E01680 trail[69];
    u8 b1D00[0x10];
    Vec_b577_01E01680 pos;
    u8 pad48F0[0x210];
    s16 down;
    u8 pad4B02[4];
    s16 h768A;
} Mgr_b577_01E01680;

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x40];
    f32 f48;
    u8 pad4C[8];
    s16 h54;
    u8 pad56[2];
    s16 h58;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
} Obj_b577_01E01680;

static s32 func_01E01680_b577(Mgr_b577_01E01680 *m, Obj_b577_01E01680 *o) {
    extern void b577_01E00080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    s32 t;
    Vec_b577_01E01680 *p;

    if (o->h58 == 1) {
        o->h6 = 8;
        o->c60[3] = 0;
        for (i = 0, p = m->trail; i < 69; i++, p++) {
            p->x = m->src.x;
            p->y = m->src.y;
            p->z = m->src.z;
        }
        func_001076F0(o->c64, 0x40, 0x10, 0x80);
        m->pos = m->src;
        o->f48 = 30.0f;
        o->h58 = 2;
    }
    if (o->h6 < 68) {
        o->h6++;
    }
    if (m->h768A < 385) {
        o->c60[3] = 0xC0;
    } else {
        if (o->c60[3] > 10) {
            o->c60[3] -= 9;
        } else {
            o->h58 = 0;
        }
        if (o->f48 > 0.0f) {
            o->f48 -= 1.0f;
        }
    }
    if (o->h54 % 2 == 0) {
        func_001076F0(o->c60, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c60, 0xC0, 0xC0, 0xC0);
    }
    if (o->h54 < 50) {
        b577_01E00080(m->b1D00, 70, 0, &m->pos);
    }
    t = o->h54;
    if (t != 0 && (s16)t < 34) {
        if (m->down != 0) {
            m->pos.z -= 5.0f;
        } else {
            m->pos.z += 5.0f;
        }
    }
    o->h54++;
    return 0;
}

/* shape b577:01E018C0, 79 insns: a white-violet spinning flash: f48 250 (topped back up by 20 once the game timer passes 0x142),
   size 10x10; alpha up by 0x40 to 0xC0 until the timer reaches 0x188, then down by 11 until it ends */

typedef struct {
    u8 pad0[0x4B06];
    s16 timer;
} Game_b577_01E018C0;

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
} Obj_b577_01E018C0;

static s32 func_01E018C0_b577(Game_b577_01E018C0 *g, Obj_b577_01E018C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 250.0f;
        o->f4C = 0.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0x80, 0x20, 0xFF);
        o->w2 = 0xA;
        o->h2 = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (g->timer < 0x188) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (g->timer > 0x142) {
        if (o->f48 < 250.0f) {
            o->f48 += 20.0f;
        }
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b577:01E01A00, 56 insns: b718:01E03D10 family volume fader: down by 10 to 0x30 for its first 151 ticks, then up to 0x80 while the scene state is under 30; full volume and the end at state 3 */

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b577_01E01A00;

typedef struct {
    u8 pad[0x4A50];
    s32 state;
} Game_b577_01E01A00;

static s32 func_01E01A00_b577(Game_b577_01E01A00 *g, Fade_b577_01E01A00 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (o->t < 151) {
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

/* shape b577:01E01AE0, 109 insns: b550:01E03D30 family: draws the pale yellow bar sprite at its own alpha, fading in by 10 up to 0x50 while the scene state is 21 or more, otherwise out by 6 and ending */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b577_01E01AE0;

typedef struct {
    Hdr_b577_01E01AE0 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b577_01E01AE0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Obj_b577_01E01AE0;

typedef struct {
    u8 pad[0x4A50];
    s32 state;
} Game_b577_01E01AE0;

static s32 func_01E01AE0_b577(Game_b577_01E01AE0 *g, Obj_b577_01E01AE0 *o) {
    Pkt_b577_01E01AE0 p __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 0.0f;
        o->mode = 2;
    }
    ((Hdr_b577_01E01AE0 *)(s32)&p)->count = 0x26;
    ((Hdr_b577_01E01AE0 *)(s32)&p)->tag = 5;
    ((Hdr_b577_01E01AE0 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b577_01E01AE0 *)(s32)&p)->pad = 0;
    p.r = 0x90;
    p.g = 0x90;
    p.b = 0x78;
    p.a = o->col[3];
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    if (g->state > 20) {
        if (o->col[3] < 0x50) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 7) {
        o->col[3] -= 6;
    } else {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b577:01E01CA0, 144 insns: b232:01E01130 with the scene packet at ctx+0x4A68 and the sine table at ctx+0x4D08 */

/* OVL_WARM */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b577_01E01CA0;

typedef struct {
    f32 s, t;
    Xyz_b577_01E01CA0 p;
} Tv_b577_01E01CA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b577_01E01CA0 v[2];
} Tex_b577_01E01CA0;

typedef struct {
    u8 pad[0x4A68];
    Tex_b577_01E01CA0 *pk;
    u8 pad4A6C[0x4D08 - 0x4A6C];
    u8 tab[1];
} Game_b577_01E01CA0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x46];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b577_01E01CA0;

static s32 func_01E01CA0_b577(Game_b577_01E01CA0 *g, Fx_b577_01E01CA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s32 f;

    f = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x38, 0x38, 0x38);
        if (o->kind == 0) {
            o->ang = 0;
        }
        if (o->kind == 1) {
            o->ang = 180;
        }
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = (f + 0x6C0) * 16 - 8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = (f + 0x940) * 16 - 8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    func_002075F0((s32)g->pk, 0, 0);
    o->f8 = 10.0f * func_00108030(g->tab, o->ang, 1);
    o->ang += 25;
    if (o->tick < 80) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b577:01E01EE0 (b577), 489 insns, 1 copy: b577 scene manager in b232:01E01370 form: setup (six joints, two
   type-4 and three type-5 textures, 256 s8 and 30 s16 jitters), step b577:01E00A40 and every slot, counting the
   b577:01E01CA0 anchors, draw the eight effect kinds (b577:01E01490 at the camera lerp, projected into a stack
   packet); scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b577_01E01EE0;

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
        s16 h[8];
    } c;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b577_01E01EE0 fx[150];
    u8 pad4440[0x30];
    Vec4f p4470;
    Vec4f p4480;
    u8 pad4490[0x5A0];
    s32 tex[3];
    u8 pad4A3C[0x14];
    s32 count;
    u8 pad4A54[8];
    s32 ot;
    u8 pad4A60[0xC];
    Vec4f *cam1;
    Vec4f *cam2;
    u8 pad4A74[8];
    f32 depth;
    u8 pad4A80[0x10];
    s16 jA;
    s16 jB;
    s16 jC;
    s16 jD;
    s16 jE;
    s16 jF;
    u8 pad4A9C[4];
    s16 cam;
    u8 pad4AA2[0xE];
    s16 jit16[30];
    u8 pad4AEC[0x14];
    s16 turn;
    s16 id;
    s16 anchors;
    s16 frame;
    s8 jit[0x100];
    u8 pad4C08[0x100];
    u8 crd[0x178];
} Scene_b577_01E01EE0;

static s32 func_01E01EE0_b577(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern Vec4f *func_001F9AD0(s32);
    extern Vec4f *func_001F9D30(s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_01E00A40_b577();
    extern void func_01E006E0_b577();
    extern void func_01E00110_b577();
    extern void func_01E027D0_b577();
    extern void b577_01E02B40();
    Scene_b577_01E01EE0 *g = (Scene_b577_01E01EE0 *)arg0;
    s16 n;
    Vec4f a;
    Vec4f b[2];
    s32 rm[4];
    s32 ang[4];
    u8 pk[0x90];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    g->cam1 = func_001F9AD0(0);
    g->cam2 = func_001F9D30(0);
    if (id >= 0) {
        func_00195108(g, 0x4E80);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 420;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x1F, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 30; k++) {
            g->jit16[k] = func_0019A5C8() % 8;
        }
        return 0;
    }
    g->anchors = 0;
    func_01E00A40_b577(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E01CA0_b577) {
                    g->fx[k].fn(g, &g->fx[k]);
                } else {
                    g->anchors++;
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E00E40_b577) {
                func_001F5620(func_001F53A0(), g->jB, &a);
                func_001F5620(func_001F53A0(), g->jB, &b[0]);
                func_001F5620(func_001F53A0(), g->jC, &b[1]);
                b[0].y = (b[1].y - b[0].y) / 2.0f;
                a.y += b[0].y;
                if (g->turn) {
                    a.z -= 5.0f;
                } else {
                    a.z += 5.0f;
                }
                g->tex88 = g->tex[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->c.rm = *(Vec4f *)rm;
                g->hB8 = 1;
                g->hBE = 0;
                func_01E027D0_b577(g, &g->fx[k], 0x20, &a);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01250_b577) {
                g->hB8 = 0x24;
                a.x = g->p4480.x;
                a.y = g->p4480.y;
                a.z = g->p4480.z;
                func_01E006E0_b577(g, &g->fx[k], 0x21, &a);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01360_b577) {
                g->tex88 = g->tex[2];
                g->c.h[0] = 0;
                g->c.h[1] = 0;
                g->c.h[2] = 0x1F;
                g->c.h[3] = 0x3F;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 0x18;
                g->hBE = 0;
                func_01E00110_b577(g, &g->fx[k], 0x20, g->fx[k].pos);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01490_b577) {
                a.x = g->cam1->x + 5.0f * (g->cam2->x - g->cam1->x);
                a.y = g->cam1->y + 5.0f * (g->cam2->y - g->cam1->y);
                a.z = g->cam1->z + 5.0f * (g->cam2->z - g->cam1->z);
                func_00205440(&a, NULL, &pk[0x18], &g->depth);
                func_01E00510_b577((s32)g, (u8 *)&g->fx[k], 0x11, g->depth);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01590_b577) {
                g->hB8 = 0x24;
                func_01E006E0_b577(g, &g->fx[k], 0x21, &g->p4470);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01100_b577) {
                g->hB8 = 0x12;
                func_01E006E0_b577(g, &g->fx[k], 0x21, &g->p4470);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01680_b577) {
                g->hB8 = 0x12;
                g->px = 0.0f;
                g->py = 0.0f;
                g->pz = 0.0f;
                b577_01E02B40(g, &g->fx[k], &g->p4480, 0);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E018C0_b577) {
                g->hB8 = 0x24;
                a.x = g->p4480.x;
                a.y = g->p4480.y;
                a.z = g->p4480.z;
                func_01E006E0_b577(g, &g->fx[k], 0x21, &a);
                func_01E006E0_b577(g, &g->fx[k], 0x21, &g->p4470);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 226) {
        return 1;
    }
    if (g->frame == 405) {
        return 4;
    }
    if (g->frame == 395) {
        return 2;
    }
    if (g->frame > 236 && g->frame < 390) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}


/* shape b577:01E02690, 80 insns: twin of b034:01E05330: take a free effect slot (0x96 of 0x70 bytes), clear
   it, colour it from the scene colour, copy the scene position and value, store the two arguments; returns 1 if a
   slot was found */

typedef struct Slot_b577_01E02690 {
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
} Slot_b577_01E02690;

typedef struct Obj_b577_01E02690 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x44];
    Slot_b577_01E02690 slots[0x96];
    u8 padB[0x614];
    u8 rgba[4];
    u8 padC[0xA4];
    s16 fB2B0;
} Obj_b577_01E02690;

static s32 func_01E02690_b577(Obj_b577_01E02690 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b577_01E02690 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x96;
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

/* OVL_WARM */

/* shape b577:01E027D0, 220 insns: b232:01E01B90's twisted 18-quad burst at a third of the size (matrix scale 0.3)
   with b577's scene tables (ot 0x4A5C, frames 0x4AB0, trig 0x4D08) */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[0x18];
    f32 r1;
    f32 r0;
    u8 pad50[0xA];
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b577_01E027D0;

typedef struct {
    u8 pad0[0x88];
    s32 tex;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x1A];
    s16 frame;
    u8 padC0[0x4A5C - 0xC0];
    s32 ot;
    u8 pad4A60[0x4AB0 - 0x4A60];
    s16 frames[18];
    u8 pad4AD4[0x4D08 - 0x4AD4];
    u8 trig[1];
} Game_b577_01E027D0;

static void func_01E027D0_b577(Game_b577_01E027D0 *g, Obj_b577_01E027D0 *o, s32 mode, Vec4f *in) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109100(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 pos[4];
    Vec4f q[4];
    f32 v[4];
    f32 sc[4];
    f32 m[16];
    f32 depth[4];
    s32 tw[4];
    f32 rm[4];
    struct {
        u8 pk[0x70];
        u8 tail[0x20];
    } buf;
    s32 k;
    s16 i;
    s16 s;
    s16 a;
    void *p = &buf;
    f32 r1;
    f32 r0;
    f32 c;
    f32 sn;

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
    sc[0] = 0.3f;
    sc[1] = 0.3f;
    sc[2] = 0.3f;
    func_00108EF0(m, sc, o->rot, v);
    *(f32 *)(u32)&q[0].y = 0.0f;
    *(f32 *)(u32)&q[1].y = 0.0f;
    *(f32 *)(u32)&q[2].y = 0.0f;
    *(f32 *)(u32)&q[3].y = 0.0f;
    r1 = o->r1;
    r0 = o->r0;
    tw[1] = o->h5A;
    tw[2] = o->h5C;
    for (i = 0; i < 18; i++) {
        *(f32 *)(u32)&q[0].y = 0.0f;
        *(f32 *)(u32)&q[1].y = 0.0f;
        *(f32 *)(u32)&q[2].y = 0.0f;
        *(f32 *)(u32)&q[3].y = 0.0f;
        func_00106080(rm, 0x14, g->frames[i], 0);
        g->rect = *(Vec4f *)rm;
        func_00108500(p, &g->rect, g->frame);
        s = a - 200;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[2].x = c * r1;
        q[2].z = sn * r1;
        q[0].x = c * r0;
        q[0].z = sn * r0;
        s = a - 180;
        c = func_00108030(g->trig, s, 1);
        sn = func_00108030(g->trig, s, 0);
        q[3].x = c * r1;
        q[3].z = sn * r1;
        q[1].x = c * r0;
        q[1].z = sn * r0;
        func_00109100(q, tw, 2, g->trig);
        func_00109100(q, tw, 0, g->trig);
        if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, g->ot, (u32)depth[0]);
        }
        a += 20;
    }
}

/* shape b577:01E02B40 (B577PAINT_RAIN21), 637 insns, 1 copy (-O3,p): b084:01E03750's beam along the module spline
   (B577PAINT_RAIN21) */

typedef struct {
    f32 x, y, z, w;
} Vec_b577_01E02B40;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b577_01E02B40;

typedef struct {
    u8 r, g, b, a;
} Col_b577_01E02B40;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b577_01E02B40;

typedef struct {
    u8 hdr[0x10];
    struct {
        Rgbaq_b577_01E02B40 c;
        Xyz_b577_01E02B40 p;
    } v[4];
    u8 tail[0x40];
} Pkt_b577_01E02B40;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x5C];
    void *texture;
    u8 pad8C[8];
    s16 rect[4];
    u8 pad9C[0x22];
    s16 mode;
} Ctx_b577_01E02B40;

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
    Col_b577_01E02B40 col0;
    Col_b577_01E02B40 col1;
} Beam_b577_01E02B40;

static inline Vec_b577_01E02B40 spline_b847_01E00E60(Vec_b577_01E02B40 *p, s32 type, f32 t) {
    Vec_b577_01E02B40 r;
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

#pragma optimization_level 3

static void func_01E02B40_b577(Ctx_b577_01E02B40 *c, Beam_b577_01E02B40 *an, Vec_b577_01E02B40 *pts __attribute__((aligned(16))), s32 flags) {
    extern s32 func_00207500(void);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002086D0(void *, u64);
    extern Rgbaq_b577_01E02B40 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b577_01E02B40 ab[2];
    Vec_b577_01E02B40 ctrl[4];
    Vec_b577_01E02B40 prev;
    Vec_b577_01E02B40 q[4];
    Vec_b577_01E02B40 pos;
    f32 depth[4];
    f32 m[16];
    Pkt_b577_01E02B40 pkt __attribute__((aligned(8)));
    s32 i;
    s32 k;
    s32 j;
    s16 n;
    Pkt_b577_01E02B40 *p;
    s32 target;
    f32 t;
    f32 w;
    f32 w0;
    f32 w1;

    w = an->width;
    target = func_00207500();
    p = &pkt;
    w /= 10.0f;
    n = an->count;
    w0 = w;
    func_001092E0(p, 0);
    func_001094F0(p);
    p->v[0].c = func_00107740(&an->col0);
    p->v[1].c = func_00107740(&an->col1);
    p->v[2].c = func_00107740(&an->col0);
    p->v[3].c = func_00107740(&an->col1);
    func_002086D0(p, 0x48 | ((u64)0x80 << 32));
    ctrl[0] = pts[0];
    ctrl[1] = pts[0];
    ctrl[2] = pts[1];
    ctrl[3] = pts[2];
    pos.x = c->x;
    pos.y = c->y;
    pos.z = c->z;
    func_00108EF0(m, 0, an->rot, &pos);
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 2; j++) {
            if (i != 0) {
                if (i == 0 && j == 0) {
                    ab[0] = spline_b847_01E00E60(&pts[(s16)i - 1], 0, t);
                } else {
                    ab[0] = prev;
                }
                t += 0.5f;
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
                t += 0.5f;
                if (!(t < 0.9f)) {
                    t = 1.0f;
                }
                ab[1] = spline_b847_01E00E60(ctrl, 0, t);
                prev = ab[1];
            }
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
                } else if (k == 1) {
                    q[1].y -= w1;
                    q[3].y -= w;
                }
                if (flags == 0) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, (u32)depth[0]);
                    }
                } else if (flags == 1) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                        func_002075F0(p, target, 0);
                    }
                } else if (flags == 2) {
                    if (func_00205630(q, 0x70000000, m, p, depth) != 0) {
                        func_002075F0(p, target, -1);
                    }
                }
            }
        }
    }
}

#pragma optimization_level reset
