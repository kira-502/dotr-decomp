#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b411(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b411(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b411(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b411 in the
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

static void func_01E00D10_b411(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b411((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b411:01E00FD0 (B411_W_S), 378 insns, 1 copy: B411_W_S, the effect scene step: counts the frame (0x9D28);
   frame 1 spawns 0x1E02470, 59 three 0x1E02170 (sel 0..2); frames 108/130/140 take joint 0x9CB6/0x9CB8/0x9CB4 into
   pos and pts[sel], spawn 0x1E01D30, 0x1E022F0 and twenty 0x1E01960 on sides 0,18,..; frames
   108..198/130..220/140..230 copy pts[0/1/2] to pos and spawn 0x1E015C0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x9BF0 - 0x260];
    Vec4f pts[3];
    u8 pad9C20[0x9CB4 - 0x9C20];
    s16 joint2;
    s16 joint0;
    s16 joint1;
    u8 pad9CBA[0x9D12 - 0x9CBA];
    s16 side;
    u8 pad9D14[0x9D20 - 0x9D14];
    s16 sel;
    u8 pad9D22[0x9D28 - 0x9D22];
    s16 t;
} Scene_b411_01E00FD0;

static void func_01E00FD0_b411(Scene_b411_01E00FD0 *g) {
    extern void b411_01E015C0(void);
    extern void b411_01E01960(void);
    extern void b411_01E01D30(void);
    extern void b411_01E02170(void);
    extern void b411_01E022F0(void);
    extern void b411_01E02470(void);
    extern void b411_01E02F60(Scene_b411_01E00FD0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 j;

    g->t++;
    if (g->t == 1) {
        b411_01E02F60(g, b411_01E02470, 0);
    }
    if (g->t == 59) {
        g->sel = 0;
        b411_01E02F60(g, b411_01E02170, 0);
        g->sel = 1;
        b411_01E02F60(g, b411_01E02170, 0);
        g->sel = 2;
        b411_01E02F60(g, b411_01E02170, 0);
    }
    if (g->t == 108) {
        func_001F5620(func_001F53A0(), g->joint0, &g->pos);
        g->sel = 0;
        func_001F5620(func_001F53A0(), g->joint0, &g->pts[g->sel]);
        b411_01E02F60(g, b411_01E01D30, 0);
        b411_01E02F60(g, b411_01E022F0, 0);
        g->pos = g->pts[g->sel];
        for (i = 0, j = 0; i < 20; j += 18, i++) {
            g->side = j;
            b411_01E02F60(g, b411_01E01960, 0);
        }
    }
    if (g->t >= 108 && g->t < 199) {
        func_001F5620(func_001F53A0(), g->joint0, &g->pos);
        g->pos = g->pts[0];
        b411_01E02F60(g, b411_01E015C0, 0);
    }
    if (g->t == 130) {
        func_001F5620(func_001F53A0(), g->joint1, &g->pos);
        g->sel = 1;
        func_001F5620(func_001F53A0(), g->joint1, &g->pts[g->sel]);
        b411_01E02F60(g, b411_01E01D30, 0);
        b411_01E02F60(g, b411_01E022F0, 0);
        g->pos = g->pts[g->sel];
        for (j = 0, i = 0; j < 20; i += 18, j++) {
            g->side = i;
            b411_01E02F60(g, b411_01E01960, 0);
        }
    }
    if (g->t >= 130 && g->t < 221) {
        g->pos = g->pts[1];
        b411_01E02F60(g, b411_01E015C0, 0);
    }
    if (g->t == 140) {
        func_001F5620(func_001F53A0(), g->joint2, &g->pos);
        g->sel = 2;
        func_001F5620(func_001F53A0(), g->joint2, &g->pts[g->sel]);
        b411_01E02F60(g, b411_01E01D30, 0);
        b411_01E02F60(g, b411_01E022F0, 0);
        g->pos = g->pts[g->sel];
        for (j = 0, i = 0; j < 20; i += 18, j++) {
            g->side = i;
            b411_01E02F60(g, b411_01E01960, 0);
        }
    }
    if (g->t >= 140 && g->t < 231) {
        g->pos = g->pts[2];
        b411_01E02F60(g, b411_01E015C0, 0);
    }
}

/* shape b411:01E015C0, 114 insns: on start f48 30..36, variant 0..2, colour (0x20, 0x20, 0xFF), 0x50 5..14, random 0x5A, speed 2..6
   (0xE), 0x8 0..34, hold 2..16 (0x6); alpha grows by 0x40 (below 0xC0) during the hold, then fades by 19 and stops;
   after the first tick f48 grows by 1 and 0x50 by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
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
} Fx_b411_01E015C0;

static s32 func_01E015C0_b411(s32 arg0, Fx_b411_01E015C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 7 + 30;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0x20, 0x20, 0xFF);
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 5 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 8 + 9;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

/* shape b411:01E01790, 114 insns: on start f48 30..36, variant 0..2, colour (0xFF, 0xFF, 0xFF), 0x50 5..14, random 0x5A, speed 35..84
   (0xE), 0x8 0..34, hold 2..16 (0x6); alpha grows by 0x40 (below 0xC0) during the hold, then fades by 19 and stops;
   after the first tick f48 grows by 1 and 0x50 by the speed */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
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
} Fx_b411_01E01790;

static s32 func_01E01790_b411(s32 arg0, Fx_b411_01E01790 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 7 + 30;
        o->f56 = func_0019A5C8() % 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->f50 = func_0019A5C8() % 10 + 5;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 50 + 35;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 8 + 9;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f48 += 1.0f;
    }
    if (o->tick != 0) {
        o->f50 += o->speed;
    }
    o->tick++;
    return 0;
}

typedef struct {
    u8 pad0000[0x9F2C];
    u8 tab[1];
} Mgr_b411_01E01960;

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
    u8 pad30[0x22];
    s16 h52;
    s16 h54;
    s16 h56;
    s16 h58;
    s16 h5A;
    u8 pad5C[4];
    u8 c60[4];
} Obj_b411_01E01960;

static s32 func_01E01960_b411(Mgr_b411_01E01960 *m, Obj_b411_01E01960 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00205C40(void *);

    if (o->h58 == 1) {
        o->h8 = 40;
        o->hA = o->h8;
        o->h56 = (func_0019A5C8() >> 4) % 3 + 2;
        func_001076F0(o->c60, 0x20, 0x20, 0xFF);
        o->h58 = 2;
        o->f14 += 2.0f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 2.0f * func_00108030(m->tab, o->h5A, 1);
        o->h52 = (func_0019A5C8() >> 4) % 4;
    }
    if (o->h54 < 5) {
        if (o->c60[3] < 0xC0) {
            o->c60[3] += 0x60;
        }
    } else if (o->c60[3] > 20) {
        o->c60[3] -= 19;
    } else {
        o->h58 = 0;
    }
    if (o->h54 != 0) {
        o->f14 += 0.5f * func_00108030(m->tab, o->h5A, 0);
        o->f10 += 0.5f * func_00108030(m->tab, o->h5A, 1);
    }
    func_00205C40(o->rot);
    o->h54++;
    return 0;
}

/* shape b411:01E01B30, 128 insns: b432:01E022D0 with purple (0x40/0x20/0x80) and grey 0x80 colours for kind 1 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    u8 pad8[0x18];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
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
    u8 col[4];
    u8 col2[4];
} Fx_b411_01E01B30;

static s32 func_01E01B30_b411(s32 arg0, Fx_b411_01E01B30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            o->f4C = 220.0f;
            o->hold = 14;
            func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
            func_001076F0(o->col, 0xFF, 0x40, 0x40);
        }
        if (o->kind == 1) {
            o->hold = 8;
            func_001076F0(o->col2, 0x40, 0x20, 0x80);
            func_001076F0(o->col, 0x80, 0x80, 0x80);
            o->w20 = func_0019A5C8() % 65535;
            o->w24 = func_0019A5C8() % 65535;
            o->w28 = func_0019A5C8() % 65535;
        }
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < o->hold) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else {
        if (o->kind == 0) {
            if (o->col2[3] > 0xA) {
                o->col2[3] -= 9;
            } else {
                o->mode = 0;
            }
        }
        if (o->kind == 1) {
            if (o->col2[3] > 0x10) {
                o->col2[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->kind == 1) {
        o->f48 += 25.0f;
        o->f4C = 0.6f * o->f48;
    }
    o->tick++;
    return 0;
}

/* shape b411:01E01D30, 271 insns: a white trail head for scene point 0x50 (ctx+0x9BF0): on start fills its 70-point
   history (ctx+0x8610 + 0x460 per point) with the point; fades in by 0x2A for 90 ticks, then shrinks 0x48 by 1.5 and
   stops; shifts the history (the module's b411:01E00080) before tick 50 and after 80; flickers 0xFF / 0xC0 before 80;
   grows 0x6 to 50; for 50 ticks it slides the point 3.5 along z (sign by ctx+0x9D24) and lifts it 0.3, then hands
   it to the scene (ctx+0x250, flag 0x9D20) and starts b411:01E01B30 (even ticks), b411:01E01790 (odd) and
   b411:01E02580 (tick 50) through b411:01E02F60 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 idx;
    u8 pad52[2];
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
    u8 col2[4];
} Head_b411_01E01D30;

typedef struct {
    u8 pad0[0x250];
    Vec4f org;
    u8 pad260[0x8610 - 0x260];
    Vec4f trail[5][70];
    Vec4f pt[5];
    u8 pad9C40[0x9D20 - 0x9C40];
    s16 flag;
    u8 pad9D22[2];
    s16 side;
} Scn_b411_01E01D30;

static s32 func_01E01D30_b411(Scn_b411_01E01D30 *g, Head_b411_01E01D30 *o) {
    extern s32 b411_01E00080(Vec4f *dst, s32 n, s32 arg2, f32 *src);
    extern u8 b411_01E01790[];
    extern u8 b411_01E01B30[];
    extern u8 b411_01E02580[];
    extern void b411_01E02F60(Scn_b411_01E01D30 *g, void *data, s32 arg);
    extern void func_001076F0(void *, s32, s32, s32);
    f32 v[4];
    f32 *py;
    f32 *pz;
    s16 i;
    Vec4f *t;

    py = &v[1];
    pz = &v[2];
    v[0] = g->pt[o->idx].x;
    *py = g->pt[o->idx].y;
    *pz = g->pt[o->idx].z;
    if (o->mode == 1) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        t = g->trail[o->idx];
        for (i = 0; i < 70; i++) {
            t[i].x = v[0];
            t[i].y = *py;
            t[i].z = *pz;
        }
        o->h6 = 20;
        o->col[3] = 0;
        o->h8 = 0;
        o->kind = 4;
        o->f48 = 17.0f;
        o->mode = 2;
    }
    if (o->tick < 90) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x2A;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x2A;
        }
    } else if (o->f48 >= 0.0f) {
        o->f48 -= 1.5f;
    } else {
        o->mode = 0;
    }
    if (o->tick < 50 || o->tick > 80) {
        b411_01E00080(&g->trail[o->idx][69], 70, 0, v);
    }
    if (o->tick < 80) {
        if (o->tick % 2 == 1) {
            func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        } else {
            func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        }
    }
    if (o->tick != 0) {
        if (o->h6 < 50) {
            o->h6++;
        }
    }
    if (o->tick < 50) {
        if (g->side != 0) {
            g->pt[o->idx].z -= 3.5f;
        } else {
            g->pt[o->idx].z += 3.5f;
        }
        g->pt[o->idx].y -= 0.3f;
    } else {
        g->org = g->pt[o->idx];
        g->flag = 1;
        if (o->tick % 2 != 0) {
            b411_01E02F60(g, b411_01E01B30, 0);
        }
        if (o->tick % 2 == 1) {
            b411_01E02F60(g, b411_01E01790, 0);
        }
        if (o->tick == 50) {
            b411_01E02F60(g, b411_01E02580, 0);
        }
    }
    o->tick++;
    return 0;
}

/* shape b411:01E02170, 94 insns: on start f4C 40, second colour (0xCF, 0xCF, 0xFF) (alpha 0), colour (0x80, 0x80,
   0xFF), 0x52 = 0, 0x5A/0x5C = 10; the second alpha grows by 0x30 (below 0xC0) for 100 ticks, then fades by 15 and
   stops; follows model point 0x9CB4[0x50]; the second colour flickers; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x9CB4];
    s16 pts[1];
} Game_b411_01E02170;

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
} Fx_b411_01E02170;

static s32 func_01E02170_b411(Game_b411_01E02170 *g, Fx_b411_01E02170 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->f4C = 40.0f;
        func_001076F0(o->col2, 0xCF, 0xCF, 0xFF);
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->f52 = 0;
        o->f5A = 10;
        o->f5C = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 100) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x30;
        }
    } else if (o->col2[3] > 0x10) {
        o->col2[3] -= 15;
    } else {
        o->mode = 0;
    }
    func_001F5620(func_001F53A0(), g->pts[o->pt], o->pos);
    if (o->tick % 2 == 1) {
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->col2, 0xC0, 0xC0, 0xC0);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b411:01E022F0, 96 insns: a white-blue flicker glow on a scene point: size 40; second alpha up by 0x30 until frame 85,
   then down by 15 until it ends; takes the point each frame; flickers white/grey; spins a quarter turn */

typedef struct {
    u8 pad0[0x9BF0];
    Vec4f pts[1];
} Game_b411_01E022F0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x1C];
    f32 f4C;
    s16 pidx;
    s16 h52;
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b411_01E022F0;

static s32 func_01E022F0_b411(Game_b411_01E022F0 *g, Obj_b411_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f4C = 40.0f;
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c0, 0x80, 0x80, 0xFF);
        o->h52 = 0;
        o->h5A = 0xA;
        o->h5C = 0xA;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x55) {
        if (o->c1[3] < 0xC0) {
            o->c1[3] += 0x30;
        }
    } else if (o->c1[3] > 0x10) {
        o->c1[3] -= 0xF;
    } else {
        o->state = 0;
    }
    o->pos = g->pts[o->pidx];
    if (o->t % 2 == 1) {
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c1, 0xC0, 0xC0, 0xC0);
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->t++;
    return 0;
}

/* shape b411:01E02470, 66 insns: twin of b180:01E021D0 (volume fade), tick limit 0x97, floor 0x30, state at 0x9C80 below 0x1E */

typedef struct {
    u8 pad[0x9C80];
    s32 state;
} Game_b411_01E02470;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    s16 pad52;
    s16 tick;
    s16 pad56;
    s16 mode;
} Fade_b411_01E02470;

static s32 func_01E02470_b411(Game_b411_01E02470 *g, Fade_b411_01E02470 *o) {
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

/* shape b411:01E02580, 136 insns: b432:01E03460 in 0x80/0x80/0x90, alpha up by 12 to 0x30 until scene count 250 (s16 at ctx+0x9D28), then down by 4 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b411_01E02580;

typedef struct {
    f32 s, t;
    Xyz_b411_01E02580 p;
} Tv_b411_01E02580;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b411_01E02580 v[2];
    u8 tail[0x20];
} Tex_b411_01E02580;

typedef struct {
    u8 pad0[0x9D28];
    s16 count;
} Ctx_b411_01E02580;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b411_01E02580;

static s32 func_01E02580_b411(Ctx_b411_01E02580 *g, Fx_b411_01E02580 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b411_01E02580 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 2.5f;
        func_001076F0(o->col, 0x80, 0x80, 0x90);
        o->mode = 2;
    }
    ((Tex_b411_01E02580 *)(s32)&pk)->flags = 0x26;
    ((Tex_b411_01E02580 *)(s32)&pk)->size = 5;
    ((Tex_b411_01E02580 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b411_01E02580 *)(s32)&pk)->pad4 = 0;
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
    if (g->count < 250) {
        if (o->col[3] < 0x30) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 5) {
        o->col[3] -= 4;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E027A0_b411(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b411", func_01E027B0_b411);

/* shape b411:01E02F60, 106 insns: takes the first free of 300 effect slots (0x70 bytes, b041:01E02C00 shape),
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
} Slot_b411_01E02F60;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b411_01E02F60 slot[300];
    u8 padEnd[0x9C84 - 0x2A0 - 300 * 0x70];
    u8 col[4];
    u8 pad9C88[0x8A];
    s16 h9D12;
    u8 pad9D14[0xC];
    s16 h9D20;
} Scene_b411_01E02F60;

static s32 func_01E02F60_b411(Scene_b411_01E02F60 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b411_01E02F60 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 300; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 300;
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
        sl->h50 = s->h9D20;
        sl->h52 = s->h9D20;
        sl->h5A = s->h9D12;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
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

static void func_01E03110_b411(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b411((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b411((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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

INCLUDE_ASM("asm/nonmatchings/mod/b411", func_01E036C0_b411);
