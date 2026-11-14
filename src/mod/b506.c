#include "common.h"

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

static void func_01E00080_b506(Pk_b034_01E00110 *p, Rect_b034_01E00110 *r, s32 mode) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b506 in the
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

static void func_01E004D0_b506(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b506((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

static void func_01E00790_b506(s32 arg0, u8 *obj, s32 mode, f32 level) {
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

/* shape b506:01E00960 (B506_W_S), 322 insns, 1 copy: the b506 module's event step: scene colour red 0x80; counts
   ticks; at 70 b506:01E019C0, ten ring points stacked from -30 by 17 (radius 0 then 3, random angles), colour 0x20 and
   the point (0, 30, 0), then one b506:01E00E70; at 87 b506:01E01540; every tick the ring points turn by 4; until 87
   the eye point follows joint 0xC00C (copied to 0xAF10); from 70 to 115 the point follows that joint and five (from
   87 twelve) b506:01E016D0 are spawned */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xAE20 - 0x260];
    Vec4f eye;
    u8 padAE30[0x40];
    Vec4f pts[10];
    Vec4f eye2;
    u8 padAF20[0xBFA4 - 0xAF20];
    u8 col[4];
    u8 padBFA8[0xC];
    f32 rad[10];
    u8 padBFDC[4];
    s32 wBFE0;
    u8 padBFE4[0x14];
    s16 ang[10];
    s16 jB;
    s16 jA;
    u8 padC010[0x10];
    s16 hC020;
    s16 hC022;
    u8 padC024[2];
    s16 fA;
    u8 padC028[4];
    s16 timer;
    u8 padC02E[0x102];
    u8 sin[1];
} Ctx_b506_01E00960;

static void func_01E00960_b506(Ctx_b506_01E00960 *g) {
    extern s32 b506_01E00E70(void);
    extern s32 b506_01E01540(void);
    extern s32 b506_01E016D0(void);
    extern s32 b506_01E019C0(void);
    extern void b506_01E02120(Ctx_b506_01E00960 *, s32 (*)(void), s32);
    extern void b506_01E022C0(Ctx_b506_01E00960 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f v;
    s32 i;
    s32 k;
    s32 n;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    if (g->timer == 70) {
        b506_01E022C0(g, b506_01E019C0, 0);
    }
    if (g->timer == 87) {
        g->fA = 0;
        b506_01E022C0(g, b506_01E01540, 0);
    }
    if (g->timer == 70) {
        for (i = 0, k = -30; i < 10; i++, k += 17) {
            g->pts[i].y = k;
        }
        g->rad[0] = 0.0f;
        for (i = 1; i < 10; i++) {
            g->rad[i] = 3.0f;
        }
        for (i = 0; i < 10; i++) {
            g->ang[i] = func_0019A5C8() % 360;
        }
        g->col[0] = 0x20;
        g->col[1] = 0x20;
        g->col[2] = 0x20;
        g->pos.x = 0.0f;
        g->pos.y = 30.0f;
        g->pos.z = 0.0f;
        for (i = 0; i < 1; i++) {
            g->hC022 = 1;
            g->wBFE0 = 0;
            g->fA = 1;
            g->hC020 = 0;
            b506_01E02120(g, b506_01E00E70, 0);
        }
    }
    func_001F5620(func_001F5380(), g->jA, &v);
    for (i = 0; i < 10; i++) {
        if (i != 0) {
            g->pts[i].x = g->rad[i] * func_00108030(g->sin, g->ang[i], 1);
            g->pts[i].z = g->rad[i] * func_00108030(g->sin, g->ang[i], 0);
        } else {
            g->pts[i].x = g->rad[i] * func_00108030(g->sin, g->ang[i], 1);
            g->pts[i].z = g->rad[i] * func_00108030(g->sin, g->ang[i], 0);
        }
        g->ang[i] += 4;
        if (g->ang[i] >= 360) {
            g->ang[i] %= 360;
        }
    }
    if (g->timer < 88) {
        func_001F5620(func_001F53A0(), g->jB, &g->eye);
        g->eye2 = g->eye;
    }
    if (g->timer < 116) {
        if (g->timer >= 70) {
            func_001F5620(func_001F53A0(), g->jB, &g->pos);
        }
    }
    if (g->timer >= 70 && g->timer < 116) {
        func_001F5620(func_001F53A0(), g->jB, &g->pos);
        if (g->timer < 87) {
            n = 5;
        } else {
            n = 12;
        }
        for (i = 0; i < n; i++) {
            b506_01E022C0(g, b506_01E016D0, 0);
        }
    }
}

/* shape b506:01E00E70, 243 insns: c061:01E01BA0's rising column for module b506: colours (0x38, 0x38, 0x48), spine
   at g+0xAE70, side widths up to 10 / 9 per point, publish block at g+0xBFB0..0xC026, run while the scene count
   (0xC02C) is under 115 through b506:01E02120 */

typedef struct {
    u8 pad0[0x70];
    s32 w70;
} Link_b506_01E00E70;

typedef struct {
    u8 pad0[4];
    f32 top;
    u8 pad8[0xC];
    f32 base;
    u8 pad18[0x18];
    s32 w30;
    s32 w34;
    s32 w38;
    u8 pad3C[4];
    Vec4f a;
    Vec4f b;
    u8 pad60[0x14];
    Link_b506_01E00E70 *link;
    u8 pad78[8];
    u8 c80[4];
    u8 c84[4];
    s16 state;
    s16 h8A;
    s16 h8C;
    u8 pad8E[4];
    s16 ang;
} Obj_b506_01E00E70;

typedef struct {
    u8 pad0[0xAE70];
    Vec4f pts[8];
    u8 padAEF0[0xBFB0 - 0xAEF0];
    Obj_b506_01E00E70 *obj;
    u8 padBFB4[0x28];
    f32 size;
    f32 base;
    u8 padBFE4[0x3C];
    s16 ang;
    s16 h68BE;
    u8 padC024[2];
    s16 h68C2;
    u8 padC028[4];
    s16 step;
} Scene_b506_01E00E70;

static s32 func_01E00E70_b506(Scene_b506_01E00E70 *g, Obj_b506_01E00E70 *o) {
    extern s32 b506_01E02120(Scene_b506_01E00E70 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern Vec4f func_001098E0(void *, void *, void *, void *);
    f32 v[4];
    s16 i;

    v[1] = 0.0f;
    func_001076F0(o->c80, 0x38, 0x38, 0x48);
    func_001076F0(o->c84, 0x38, 0x38, 0x48);
    o->w30 = 0;
    o->w34 = 0;
    o->w38 = 0;
    if (o->top < 100.0f) {
        if (o->c80[3] < 0x50) {
            o->c80[3] += 10;
        }
        if (o->c84[3] < 0x50) {
            o->c84[3] += 10;
        }
    } else {
        if (o->c80[3] > 16) {
            o->c80[3] -= 14;
        }
        if (o->c84[3] > 16) {
            o->c84[3] -= 14;
        }
    }
    for (i = 1; i < 8; i++) {
        if (!(g->pts[i].y <= o->top)) {
            v[0] = g->pts[0].x;
            v[2] = g->pts[0].z;
            o->a = func_001098E0(v, o, &g->pts[i - 1], &g->pts[i]);
            o->b = func_001098E0(v, o, &g->pts[i - 1], &g->pts[i]);
            if (o->h8A <= i * 10) {
                o->h8A += 7;
            }
            if (o->h8C <= i * 9) {
                o->h8C += 6;
            }
            i = 8;
        }
    }
    if (o->top <= 80.0f) {
        o->top += 4.0f;
        if (!(o->top - o->base <= 18.0f)) {
            o->base += 4.0f;
        }
    } else {
        o->base += 4.0f;
        if (!(o->base <= o->top)) {
            if (o->link != 0) {
                o->link->w70 = 0;
            }
            o->state = 0;
        }
    }
    if (o->state == 1) {
        if (!(o->base <= 0.0f)) {
            g->size = 14.0f;
            g->obj = o;
            g->h68BE = 1;
            g->base = o->base;
            g->h68C2 = 1;
            g->ang = o->ang - 15;
            if (g->step < 115) {
                if (b506_01E02120(g, func_01E00E70_b506, 0)) {
                    o->state = 2;
                }
            }
        }
    }
    return 0;
}

/* shape b506:01E01240, 189 insns: c063:01E04250 family blue-grey (0x60, 0x60, 0x80) flake 20 square growing 10 to 200, frame 0..2, held 20 ticks, drifting 2 a tick in z by the scene side flag (ctx+0xC02A), tumbling on all axes */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b506_01E01240;

typedef struct {
    u8 pad0[0xC02A];
    s16 side;
} Ctx_b506_01E01240;

static s32 func_01E01240_b506(Ctx_b506_01E01240 *g, Fx_b506_01E01240 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 20;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x60, 0x60, 0x80);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 60.0f;
        o->vel[0] /= 60.0f;
        o->vel[2] /= 60.0f;
        o->f5C = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        if (o->w < 200) {
            o->w += 10;
        }
        o->h = o->w;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
        if (g->side != 0) {
            o->pos[2] += 2.0f;
        } else {
            o->pos[2] -= 2.0f;
        }
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b506:01E01540, 98 insns: on start colours and hold by kind (0x50); both alphas grow by 0x40 (below 0x80) during the
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
} Fx_b506_01E01540;

static s32 func_01E01540_b506(s32 arg0, Fx_b506_01E01540 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        if (o->kind == 0) {
            func_001076F0(o->col, 0x90, 0x90, 0xA0);
            func_001076F0(o->col2, 0x90, 0x90, 0xA0);
            o->hold = 0x20;
        }
        if (o->kind == 1) {
            func_001076F0(o->col, 0xD0, 0xD0, 0x80);
            func_001076F0(o->col2, 0xC0, 0xC0, 0x80);
            o->hold = 0x14;
        }
        if (o->kind == 2) {
            func_001076F0(o->col, 0xF0, 0xE0, 0xFF);
            func_001076F0(o->col2, 0xF0, 0xE0, 0xFF);
            o->hold = 0x14;
        }
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x40;
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

/* shape b506:01E016D0, 187 insns: b631:01E01690's tumbling spark at size 20, faster drift (/15), hold 5..14, blinking
   grey 0x80/0xC0, refreshing its turn after spinning */

typedef struct {
    s16 spin[3];
    s16 hold;
    s16 w;
    s16 h;
    u8 padC[4];
    f32 pos[3];
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[4];
    f32 vel[3];
    u8 pad3C[0x16];
    s16 f52;
    s16 tick;
    s16 kind;
    s16 mode;
    u8 pad5A[2];
    s16 dir;
    u8 pad5E[2];
    u8 col[4];
} Spark_b506_01E016D0;

static s32 func_01E016D0_b506(s32 arg0, Spark_b506_01E016D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->w = 20;
        o->h = o->w;
        o->kind = (func_0019A5C8() >> 4) % 3;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->vel[1] = func_0019A5C8() % 100 - 50;
        o->vel[0] = func_0019A5C8() % 100 - 50;
        o->vel[2] = func_0019A5C8() % 100 - 50;
        o->vel[1] /= 15.0f;
        o->vel[0] /= 15.0f;
        o->vel[2] /= 15.0f;
        o->dir = func_0019A5C8() % 360;
        func_00205C40((s32)o->rot);
        o->spin[2] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[1] = func_0019A5C8() % 0x800 - 0x400;
        o->spin[0] = func_0019A5C8() % 0x800 - 0x400;
        o->hold = func_0019A5C8() % 10 + 5;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    o->rot[2] += o->spin[2];
    o->rot[1] += o->spin[1];
    o->rot[0] += o->spin[0];
    func_00205C40((s32)o->rot);
    o->tick++;
    return 0;
}

/* shape b506:01E019C0, 117 insns: a blue-grey full-screen veil in its own colour (b215:01E02390 shape): one sprite over the whole
   screen; alpha up by 20 to 0x50 while the scene timer is over 20, then down by 9 until it ends */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b506_01E019C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        f32 s, t;
        Xyz_b506_01E019C0 p;
    } v[2];
    u8 pad38[0x20];
} Pkt_b506_01E019C0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b506_01E019C0;

typedef struct {
    u8 pad0[0xBFA0];
    s32 timer;
} Scene_b506_01E019C0;

static s32 func_01E019C0_b506(Scene_b506_01E019C0 *g, Obj_b506_01E019C0 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    extern void func_001076F0(void *, s32, s32, s32);
    Pkt_b506_01E019C0 pkt __attribute__((aligned(8)));

    if (o->state == 1) {
        o->f48 = 0.0f;
        func_001076F0(o->c0, 0x70, 0x70, 0x80);
        o->state = 2;
    }
    ((Pkt_b506_01E019C0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b506_01E019C0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b506_01E019C0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b506_01E019C0 *)(s32)&pkt)->pad = 0;
    pkt.r = o->c0[0];
    pkt.g = o->c0[1];
    pkt.b = o->c0[2];
    pkt.a = o->c0[3];
    pkt.q = 1.0f;
    ((Xyz_b506_01E019C0 *)(s32)&pkt.v[0].p)->x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.0f;
    pkt.v[0].t = 0.0f;
    pkt.v[1].s = 0.625f;
    pkt.v[1].t = 0.875f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0((s32)&pkt, func_00207500(), 0);
    if (g->timer > 0x14) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x14;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b506:01E01BA0 (b506), 351 insns, 1 copy: the module's main: with arg >= 0 it clears the scene, builds both
   trig tables, loads textures 14-15 and 5:0, picks seven of the unit's joints, notes the camera's side, the mode, a
   170-tick life and 256 random offsets (-15..14); otherwise it runs the event step, updates and draws the 30 objects
   into one work packet, updates the 350 effects and draws the three kinds with their textures (the 01E01540 ones as
   screen glows 30 to the camera's side, projected into the packet's xyz part), and returns the phase codes 1/4/2/6 at
   the script's beats or 8 when the life ends */

typedef struct {
    u8 pad0[0x88];
    s16 live;
    u8 pad8A[0xE];
} Obj_b506_01E01BA0;

typedef struct {
    u8 pad0[0x10];
    Vec4f v10;
    u8 pad20[0x24];
    s32 (*fn)(void *, void *);
    u8 pad48[0xE];
    s16 frame;
    s16 live;
    u8 pad5A[0x16];
} Fx_b506_01E01BA0;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex;
    u8 pad8C[8];
    f32 rect[4];
    u8 padA4[0x34];
    u8 trigD8[0x1B8];
    s32 texs[16];
    Obj_b506_01E01BA0 obj[30];
    Fx_b506_01E01BA0 fx[350];
    u8 padB0C0[0xBF80 - 0x14A0 - 350 * 0x70];
    s32 tex2[1];
    u8 padBF84[0x1C];
    s32 life;
    u8 padBFA4[8];
    s32 ot2;
    u8 padBFB0[0x34];
    f32 level;
    u8 padBFE8[0x24];
    s16 joint[7];
    u8 padC01A[0xE];
    s16 mode;
    s16 side;
    s16 timer;
    s8 rnd[256];
    u8 padC12E[2];
    u8 trig[1];
} Scene_b506_01E01BA0;

typedef struct {
    u8 hdr[0x18];
    u8 xyz[0x78];
} Pkt_b506_01E01BA0;

static s32 func_01E01BA0_b506(s32 arg0, s32 arg) {
    Scene_b506_01E01BA0 *g = (Scene_b506_01E01BA0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_00205440(void *, s32, void *, void *);
    extern void b506_01E00960();
    extern s32 b506_01E00E70(void *, void *);
    extern void b506_01E02460(void *, void *, void *, s32);
    extern s32 b506_01E01240(void *, void *);
    extern s32 b506_01E01540(void *, void *);
    extern s32 b506_01E016D0(void *, void *);
    extern void b506_01E004D0(void *, void *, s32, void *);
    extern void b506_01E00790(void *, void *, s32, f32);
    s32 n;
    s32 i;
    s32 k;
    Vec4f v;
    f32 r[4];
    f32 r2[4];
    s32 cam[4];
    Pkt_b506_01E01BA0 pk;

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (arg >= 0) {
        func_00195108(g, 0xC2A0);
        func_00107C10(g->trig);
        func_00107C10(g->trigD8);
        for (i = 14; i < 16; i++) {
            g->texs[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 1; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        g->joint[0] = func_001F5560(func_001F53A0(), 19, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x81, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x24, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x50, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 14, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 15, 0);
        g->joint[6] = func_001F5560(func_001F53A0(), 0x23, 0);
        func_001F6160(func_001F53A0(), cam);
        g->side = cam[1] / 180.0f;
        g->mode = arg;
        g->life = 170;
        for (k = 0; k < 256; k++) {
            g->rnd[k] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    b506_01E00960(g, 0);
    for (i = 0; i < 30; i++) {
        if (g->obj[i].live != 0) {
            b506_01E00E70(g, &g->obj[i]);
        }
    }
    for (i = 0; i < 30; i++) {
        if (g->obj[i].live != 0) {
            n++;
            b506_01E02460(g, &g->obj[i], &pk, 0);
            b506_01E02460(g, &g->obj[i], &pk, 1);
        }
    }
    for (i = 0; i < 350; i++) {
        if (g->fx[i].live != 0 && g->fx[i].fn != NULL) {
            g->fx[i].fn(g, &g->fx[i]);
        }
    }
    for (k = 0; k < 350; k++) {
        if (g->fx[k].live != 0) {
            n++;
            if (g->fx[k].fn == b506_01E01240) {
                g->tex = g->texs[15];
                func_00106080(r, 0x9B, g->fx[k].frame, 0);
                *(Vec4f *)g->rect = *(Vec4f *)r;
                b506_01E004D0(g, &g->fx[k], 0x20, &g->fx[k].v10);
            }
            if (g->fx[k].fn == b506_01E01540) {
                func_001F5F90(func_001F5380(), &v);
                if (g->side != 0) {
                    v.z -= 30.0f;
                } else {
                    v.z += 30.0f;
                }
                func_00205440(&v, 0, pk.xyz, &g->level);
                b506_01E00790(g, &g->fx[k], 0x20, g->level);
            }
            if (g->fx[k].fn == b506_01E016D0) {
                g->tex = g->tex2[0];
                func_00106080(r2, 0x14, g->fx[k].frame, 0);
                *(Vec4f *)g->rect = *(Vec4f *)r2;
                b506_01E004D0(g, &g->fx[k], 0x20, &g->fx[k].v10);
            }
        }
    }
    if (g->life != 0) {
        g->life--;
    }
    if (g->timer == 77) {
        return 1;
    }
    if (g->timer == 135) {
        return 4;
    }
    if (g->timer == 100) {
        return 2;
    }
    if (g->timer > 87 && g->timer < 97) {
        return 6;
    }
    if (g->life <= 0) {
        return 8;
    }
    return 0;
}

/* shape b506:01E02120, 103 insns: b056:01E038A0 family: take the first free trail node of 30 (0x98 bytes), copy the scene position, ids and height (minus 18 below), link it after the current head and make it the head */

typedef struct {
    f32 x, y, z, w;
} V4_b506_01E02120;

typedef struct Node_b506_01E02120 {
    u8 pad0[4];
    f32 y;
    u8 pad8[0xC];
    f32 f14;
    u8 pad18[0x18];
    V4_b506_01E02120 pos;
    u8 pad40[0x30];
    struct Node_b506_01E02120 *prev;
    struct Node_b506_01E02120 *next;
    u8 pad78[0x10];
    s16 used;
    u8 pad8A[4];
    s16 f8E;
    u8 pad90[2];
    s16 f92;
    s16 f94;
    s16 f96;
} Node_b506_01E02120;

typedef struct {
    u8 pad0[0x250];
    V4_b506_01E02120 pos;
    u8 pad260[0x70];
    Node_b506_01E02120 nodes[0x1E];
    u8 pad14A0[0xBFB0 - 0x14A0];
    Node_b506_01E02120 *head;
    u8 pad3924[0x2C];
    f32 y;
    u8 pad3954[0x3C];
    s16 f398C;
    u8 pad398E[4];
    s16 f3992;
} Scene_b506_01E02120;

static s32 func_01E02120_b506(Scene_b506_01E02120 *g) {
    extern void func_00195108();
    Node_b506_01E02120 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1E; i++) {
        if (g->nodes[i].used == 0) {
            func_00195108(&g->nodes[i], 0x98);
            g->nodes[i].used = 1;
            s = &g->nodes[i];
            i = 0x1E;
        }
    }
    if (s != NULL) {
        s->pos = g->pos;
        s->f92 = g->f398C;
        s->prev = g->head;
        s->f8E = g->f3992;
        if (s->prev == NULL) {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        } else {
            s->y = g->y;
            s->f14 = s->y - 18.0f;
        }
        s->prev = g->head;
        if (s->prev != NULL) {
            s->prev->next = s;
        }
        s->f94 = 1;
        s->f96 = 1;
        g->head = s;
        return 1;
    }
    return 0;
}

/* shape b506:01E022C0, 82 insns: c035:01E01150 family: take the first free effect slot of 350 (0x70 bytes each, at ctx+0x14A0), clear it, give it the scene colour twice, the scene position, the scene value twice and both arguments; returns 1 when it got one */

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
} Obj_b506_01E022C0;

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x14a0 - 0x25C];
    Obj_b506_01E022C0 slot[350];
    u8 padEnd[0xbfa4 - 0x14a0 - 350 * 0x70];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 padBFA8[0x7E];
    s16 val;
} Ctx_b506_01E022C0;

static s32 func_01E022C0_b506(Ctx_b506_01E022C0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Obj_b506_01E022C0 *s;

    s = NULL;
    for (i = 0; i < 350; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x70);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 350;
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
        s->w40 = arg2;
        s->w44 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b506", func_01E02460_b506);
