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

static void func_01E00080_b183(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

/* shape b111:01E00D70, 340 insns, 27 copies: draw a ring of sprite quads (GS packet of 9 qwords); each quad
   is pushed out along a rotated offset read from three s8 tables (/ 20) and scaled by the ring radius;
   mode (flags & 0xF) 0 = depth from the projection, 1 = far z, 2 = -1 */

typedef struct Data_b111_01E00D70 {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x3E];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 step;
    u8 pad5C[4];
    Vec4f f60;
} Data_b111_01E00D70;

typedef struct Obj_b111_01E00D70 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 table[1];
} Obj_b111_01E00D70;

typedef struct Xyz_b111_01E00D70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b111_01E00D70;

typedef struct Uv_b111_01E00D70 {
    f32 u, v;
} Uv_b111_01E00D70;

typedef struct Pk_b111_01E00D70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b111_01E00D70 uv;
    u64 pad18;
    Xyz_b111_01E00D70 v[4];
    u64 pad60[6];
} Pk_b111_01E00D70;

typedef struct Buf_b111_01E00D70 {
    u64 tag;
    Pk_b111_01E00D70 pk;
} Buf_b111_01E00D70;

static void func_01E00920_b183(Obj_b111_01E00D70 *obj, Data_b111_01E00D70 *data, s32 flags, s8 *tab) {
    f32 fq;
    extern void b183_01E00080();
    extern void func_00108950();
    extern void func_00108EF0();
    extern s32 func_00109100();
    Vec4f view[4];
    f32 t[4];
    Vec4f pos;
    Vec4f s;
    f32 depth[4];
    f32 m[4][4];
    s32 ang[4];
    s32 rot[4];
    Buf_b111_01E00D70 buf;
    Uv_b111_01E00D70 uv;
    s16 sel;
    s16 i;
    Pk_b111_01E00D70 *p;
    s32 mode;
    s32 half;
    s8 *row;

    func_00207500();
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
    func_00107740(&uv, &data->f60);
    p->uv = uv;
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] /= 180;
    ang[1] = -ang[1];
    ang[0] /= 180;
    ang[0] = -ang[0];
    rot[1] = data->step;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, 0, &pos);
    b183_01E00080(p, obj->f94, obj->fC0);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_00108CE0(view, data->f48, data->f48);
        func_00109100(view, ang, 1, obj->table);
        func_00109100(view, ang, 0, obj->table);
        row = tab + i;
        half = i >> 1;
        t[0] = (row[data->f8] / 20.0f) * (data->f50 + half);
        t[1] = (row[data->f8 + 100] / 20.0f) * (data->f50 + half);
        t[2] = 0.0f;
        func_00108950(t, rot, 0, obj->table);
        view[0].x += t[0];
        view[1].x += t[0];
        view[2].x += t[0];
        view[3].x += t[0];
        view[0].y += t[1];
        view[1].y += t[1];
        view[2].y += t[1];
        view[3].y += t[1];
        fq = row[data->f8 + 180];
        fq /= 20.0f;
        t[2] = fq * (data->f50 + half);
        view[0].z += t[2];
        view[1].z += t[2];
        view[2].z += t[2];
        view[3].z += t[2];
        if (mode == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(depth[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, depth) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b183:01E00E70, 182 insns: b016:01E00ED0 with fixed blends (sel 0 = 0x42, 1 = 0x44, else 0x48); draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b183 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b183_01E00E70 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b183_01E00E70;

typedef struct Obj_b183_01E00E70 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b183_01E00E70;

typedef struct Xyz_b183_01E00E70 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b183_01E00E70;

typedef struct Uv_b183_01E00E70 {
    f32 u, v;
} Uv_b183_01E00E70;

typedef struct Pk_b183_01E00E70 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b183_01E00E70 uv;
    u64 pad18;
    Xyz_b183_01E00E70 v[4];
    u64 pad60[6];
} Pk_b183_01E00E70;

typedef struct Buf_b183_01E00E70 {
    u64 tag;
    Pk_b183_01E00E70 pk;
} Buf_b183_01E00E70;

static void func_01E00E70_b183(Obj_b183_01E00E70 *obj, Cam_b183_01E00E70 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b183_01E00E70 buf;
    Uv_b183_01E00E70 uv;
    s32 sel;
    s32 mode;
    Pk_b183_01E00E70 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else if (sel == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b183((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b183:01E01150, 104 insns: the b183 scene's burst script: on ticks 10..20 it spawns two shape b183:01E012F0 sparks a tick at the scene joint lifted 0..6, and on tick 15 one each of b183:01E01480 and b183:01E01E50 lifted 5 and nudged 3 on z (back when flagged) */

typedef struct {
    u8 pad0[0x250];
    f32 x, y, z;
    u8 pad25C[0x44D4 - 0x25C];
    s16 joint;
    u8 pad44D6[0x30];
    s16 back;
    u8 pad4508[2];
    s16 tick;
} Ctx_b183_01E01150;

static void func_01E01150_b183(Ctx_b183_01E01150 *g) {
    extern void b183_01E012F0();
    extern void b183_01E01480();
    extern void b183_01E01E50();
    extern void b183_01E028A0(Ctx_b183_01E01150 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);

    g->tick++;
    if (g->tick >= 10 && g->tick < 21) {
        func_001F5620(func_001F53A0(), g->joint, &g->x);
        g->y += func_0019A5C8() % 7;
        b183_01E028A0(g, b183_01E012F0, 0);
        func_001F5620(func_001F53A0(), g->joint, &g->x);
        g->y += func_0019A5C8() % 7;
        b183_01E028A0(g, b183_01E012F0, 0);
    }
    if (g->tick == 15) {
        func_001F5620(func_001F53A0(), g->joint, &g->x);
        g->y += 5.0f;
        if (g->back != 0) {
            g->z -= 3.0f;
        } else {
            g->z += 3.0f;
        }
        b183_01E028A0(g, b183_01E01480, 0);
        b183_01E028A0(g, b183_01E01E50, 0);
    }
}

/* shape b183:01E012F0, 97 insns: a white ring: set up once (size 50, frame 3, start 10..59, growth 6..15, life 3..7); full alpha for its life, then fades by 8; grows after the first frame */

typedef struct {
    u8 pad00[6];
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
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b183_01E012F0;

static s32 func_01E012F0_b183(void *arg0, Obj_b183_01E012F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 50.0f;
        o->h56 = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->hE = func_0019A5C8() % 10 + 6;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b183:01E01480 (B183_OBJ_MOVE_3_), 324 insns, 1 copy: a glow that flies from the camera joint to the scene
   joint: size 20 growing to 50, fades in until 140 then out, blinks white/grey, moves a 75th of the gap a frame over
   61..139, bursts thirty 0x1E01990 at 140 and two 0x1E01B50 at 140..141, trails 0x1E01CE0, animates 8 frames */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[4];
    Vec4f pos;
    u8 rot[0x34];
    s16 t;
    s16 frame;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
    u8 c1[4];
} Glow_b183_01E01480;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
} Scene_b183_01E01480;

static s32 func_01E01480_b183(Scene_b183_01E01480 *g, Glow_b183_01E01480 *o) {
    extern void b183_01E01990(void);
    extern void b183_01E01B50(void);
    extern void b183_01E01CE0(void);
    extern void b183_01E028A0(Scene_b183_01E01480 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);
    f32 v[2][4];
    s16 i;

    func_001F5F90(func_001F5380(), v[0]);
    func_001F5F90(func_001F53A0(), v[1]);
    v[0][0] = (v[0][0] - v[1][0]) / 75.0f;
    v[0][1] = (v[0][1] - v[1][1]) / 75.0f;
    v[0][2] = (v[0][2] - v[1][2]) / 75.0f;
    if (o->state == 1) {
        o->w = 20;
        o->h = 20;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0x80, 0x80, 0x80);
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 140) {
        if (o->c0[3] < 128) {
            o->c0[3] += 42;
        }
        if (o->c1[3] < 128) {
            o->c1[3] += 42;
        }
    } else {
        if (o->c0[3] > 15) {
            o->c0[3] -= 14;
        } else {
            o->state = 0;
        }
        if (o->c0[3] > 15) {
            o->c0[3] -= 14;
        }
    }
    if (o->t != 0) {
        if (o->w < 50) {
            o->w += 2;
        }
        if (o->h < 50) {
            o->h += 2;
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
    } else {
        func_001076F0(o->c0, 0xC0, 0xC0, 0xC0);
    }
    if (o->t > 60 && o->t < 140) {
        o->pos.x += v[0][0];
        o->pos.y += v[0][1];
        o->pos.z += v[0][2];
    }
    if (o->t == 140) {
        for (i = 0; i < 30; i++) {
            g->pos = o->pos;
            g->pos.x += func_0019A5C8() % 10 - 5;
            g->pos.y += func_0019A5C8() % 10 - 5;
            g->pos.z += func_0019A5C8() % 10 - 5;
            b183_01E028A0(g, b183_01E01990, 0);
        }
    }
    if (o->t >= 140 && o->t < 142) {
        for (i = 0; i < 2; i++) {
            g->pos = o->pos;
            g->pos.x += func_0019A5C8() % 20 - 10;
            g->pos.y += func_0019A5C8() % 20 - 10;
            g->pos.z += func_0019A5C8() % 20 - 10;
            b183_01E028A0(g, b183_01E01B50, 0);
        }
    }
    if (o->t > 60 && o->t < 140) {
        g->pos = o->pos;
        b183_01E028A0(g, b183_01E01CE0, 0);
    }
    if (o->t > 60) {
        o->frame++;
        if (o->frame > 7) {
            o->frame = 0;
        }
    }
    func_00205C40(o->rot);
    o->t++;
    return 0;
}

/* shape b183:01E01990, 110 insns: b593:01E020C0 family: a grey spark (size 10, frame cycling 0..7 from random) spinning a random 26..35 a tick from 10..59 (old angle moved to +0xC), random 0..7 at +0xA, size 0..34, held 3..7 ticks at 0x80, then out by 8 and ends */

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
} Obj_b183_01E01990;

static s32 func_01E01990_b183(s32 arg0, Obj_b183_01E01990 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 10.0f;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->hE = func_0019A5C8() % 10 + 26;
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
    o->kind++;
    if (o->kind > 7) {
        o->kind = 0;
    }
    o->t++;
    return 0;
}

/* shape b183:01E01B50, 97 insns: b183:01E012F0 with size 100, start 20..99 and growth 14..23 */

typedef struct {
    u8 pad00[6];
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
    s16 h56;
    s16 state;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
} Obj_b183_01E01B50;

static s32 func_01E01B50_b183(void *arg0, Obj_b183_01E01B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 100.0f;
        o->h56 = 3;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 80 + 20;
        o->hE = func_0019A5C8() % 10 + 14;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->state = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->t++;
    return 0;
}

/* shape b183:01E01CE0, 90 insns: a grey spark: f48 5, sub-frame 3, random angle, frame 0..7, rise 6..15, height 0..34 and hold 1..5; its old h50 kept
   in hC and replaced by a random 4..53; full alpha until the hold, then down by 8 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 w;
    s16 h;
    s16 hC;
    s16 hE;
    u8 pad10[4];
    f32 y;
    u8 pad18[8];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    u8 pad52[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 ang;
    s16 h5C;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b183_01E01CE0;

static s32 func_01E01CE0_b183(void *arg0, Obj_b183_01E01CE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 5.0f;
        o->sub = 3;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        o->ang = func_0019A5C8() % 360;
        o->h = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 4;
        o->hE = func_0019A5C8() % 10 + 6;
        o->w = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 1;
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

/* shape b183:01E01E50, 54 insns: volume fade by game state (b058:01E017A0 shape, layout at 0x50): state at 0x44A0 limit
   0x14, down 10 to 0x30, up 10 to 0x80 where the fade ends; state 2 plays at 0x80 */

typedef struct {
    u8 pad[0x44A0];
    s32 state;
} Game_b183_01E01E50;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[6];
    s16 mode;
} Fade_b183_01E01E50;

static s32 func_01E01E50_b183(Game_b183_01E01E50 *g, Fade_b183_01E01E50 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x14) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
            o->mode = 0;
        }
        if (o->vol > 0x80) {
            o->vol = 0x80;
        }
    }
    if (g->state == 2) {
        func_001F6D00(0x80);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

/* shape b183:01E01F30, 174 insns: b491:01E03360 drawn once in grey 0xC0 at alpha 0x78, its offsets 0x8/0xA growing 100..129 a tick; after the first tick alpha falls by 49 and it ends at 40 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b183_01E01F30;

typedef struct {
    f32 s, t;
    Xyz_b183_01E01F30 p;
} Tv_b183_01E01F30;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b183_01E01F30 v[2];
} Tex_b183_01E01F30;

typedef struct {
    u8 pad[0x44B8];
    Tex_b183_01E01F30 *pk;
    u8 pad44BC[0x44D4 - 0x44BC];
    s16 id;
} Game_b183_01E01F30;

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
} Fx_b183_01E01F30;

static s32 func_01E01F30_b183(Game_b183_01E01F30 *g, Fx_b183_01E01F30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 fx;
    f32 fy;
    f32 v[4];

    fx = o->f8;
    fy = o->fA;
    fx /= 10.0f;
    fy /= 10.0f;
    if (o->mode == 1) {
        o->col[3] = 0x78;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->id, v);
    func_001F5F90(func_001F53A0(), v);
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
    o->f8 += (s16)(func_0019A5C8() % 30 + 100);
    o->fA += (s16)(func_0019A5C8() % 30 + 100);
    if (o->tick != 0) {
        if (o->col[3] > 40) {
            o->col[3] -= 49;
        } else {
            o->mode = 0;
        }
    }
    o->tick++;
    return 0;
}

/* shape b183:01E021F0 (b183), 428 insns, 1 copy: the module scene manager (b202:01E02860 form): with a scene id it
   clears the scene, sets the 195-frame countdown, reads four model ids, textures 4:15 and 5:0..3, the camera turn,
   scale 0.1 and the jitter tables; otherwise it runs the scene script b183:01E01150 and every handler but the anchor
   (counted), draws the five effect kinds, the anchor pass when counted, counts down and returns the next step by
   frame (145, 180, 155) or 8 */

typedef struct {
    u8 pad0[0xC];
    s16 hC;
    u8 padE[2];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b183_01E021F0;

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
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b183_01E021F0 fx[150];
    u8 pad4440[0x40];
    s32 tex2[4];
    u8 pad4490[0x10];
    s32 count;
    u8 pad44A4[8];
    s32 ot;
    u8 pad44B0[0x24];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 pad44DA[0xA];
    s16 cam;
    u8 pad44E6[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x174];
} Scene_b183_01E021F0;

static s32 func_01E021F0_b183(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E01150_b183();
    extern s32 func_01E01480_b183();
    extern void b183_01E029E0();
    Scene_b183_01E021F0 *g = (Scene_b183_01E021F0 *)arg0;
    s32 k;
    s32 c;
    s32 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 ang[4];
    s16 i;

    c = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4880);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 195;
        g->jA = func_001F5560(func_001F53A0(), 0xF, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 15; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        for (k = 0; k < 4; k++) {
            g->tex2[k] = func_00202BF0(5, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 20 - 10;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    func_01E01150_b183(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                if (g->fx[i].fn != func_01E01F30_b183) {
                    g->fx[i].fn(g, &g->fx[i]);
                } else {
                    c = (s16)(c + 1);
                }
            }
        }
    }
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E012F0_b183) {
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->tex88 = g->tex2[0];
                g->hB8 = 8;
                g->hC0 = 0;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b183((void *)g, (void *)&g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01480_b183) {
                func_00106080(rm2, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->tex88 = g->tex2[1];
                g->hBE = 0;
                v.x = g->fx[i].pos.x;
                v.y = g->fx[i].pos.y;
                v.z = g->fx[i].pos.z;
                func_01E00E70_b183((void *)g, (void *)&g->fx[i], 0x21, v);
            }
            if (g->fx[i].fn == func_01E01990_b183) {
                func_00106080(rm3, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                if (g->fx[i].hC == 0) {
                    g->tex88 = g->tex2[2];
                } else {
                    g->tex88 = g->tex2[3];
                }
                g->hB8 = 5;
                g->hC0 = 0;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b183((void *)g, (void *)&g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01B50_b183) {
                func_00106080(rm4, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->tex88 = g->tex2[0];
                g->hB8 = 8;
                g->hC0 = 0;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b183((void *)g, (void *)&g->fx[i], 0x20, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01CE0_b183) {
                func_00106080(rm5, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->tex88 = g->tex2[2];
                g->hB8 = 10;
                g->hC0 = 0;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                func_01E00920_b183((void *)g, (void *)&g->fx[i], 0x20, g->jit);
                g->hB8 = 0;
            }
        }
    }
    if (c != 0) {
        b183_01E029E0(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 145) {
        return 1;
    }
    if (g->frame == 180) {
        return 4;
    }
    if (g->frame == 155) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b111:01E03670, 80 insns, 3 copies: starts a particle: takes the first free one of 150 slots, clears it, gives it
   the emitter's colour (twice), position and timer and the two caller values; returns 0 when all are busy
   (150-slot variant of shape b539:01E03530). */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x24];
    s32 b;
    s32 a;
    u8 pad48[8];
    s16 t0;
    s16 t1;
    u8 pad54[4];
    s16 used;
    s16 t2;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b111_01E03670;

typedef struct {
    u8 pad0000[0x250];
    Vec4f pos;
    u8 pad0260[0x40];
    Slot_b111_01E03670 slots[150];
    u8 pad4440[0x64];
    u8 col[4];
    u8 pad44A8[0x5A];
    s16 t0;
} Emit_b111_01E03670;

static s32 func_01E028A0_b183(Emit_b111_01E03670 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b111_01E03670 *e;
    s16 i;

    e = NULL;
    for (i = 0; i < 150; i++) {
        if (o->slots[i].used == 0) {
            func_00195108(&o->slots[i], 0x70);
            o->slots[i].used = 1;
            e = &o->slots[i];
            i = 150;
        }
    }
    if (e != NULL) {
        func_001076F0(e->c0, o->col[0], o->col[1], o->col[2]);
        e->c0[3] = o->col[3];
        func_001076F0(e->c1, o->col[0], o->col[1], o->col[2]);
        e->c1[3] = o->col[3];
        func_00106AB0(e, &o->pos, 0);
        e->x = o->pos.x;
        e->y = o->pos.y;
        e->z = o->pos.z;
        e->t0 = o->t0;
        e->b = b;
        e->a = a;
        return 1;
    }
    return 0;
}

/* shape b183:01E029E0, 68 insns, 2 copies: the module's draw pass: opens a sprite packet on the stack (published through the
   scene), then runs every live slot (150 of 0x70 bytes) whose handler is shape b183:01E01F30 through it. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b183_01E029E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 st;
        Xyz_b183_01E029E0 p;
    } v[2];
    u8 pad38[8];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b183_01E029E0;

typedef struct {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Slot_b183_01E029E0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b183_01E029E0 slot[150];
    u8 padEnd[0x44B4 - 0x2A0 - 150 * 0x70];
    s32 ctx;
    Pkt_b183_01E029E0 *pkt;
} Scene_b183_01E029E0;

static void func_01E029E0_b183(Scene_b183_01E029E0 *s) {
    extern void b183_01E01F30(Scene_b183_01E029E0 *, Slot_b183_01E029E0 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b183_01E029E0 pkt __attribute__((aligned(8)));
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
    for (i = 0; i < 150; i++) {
        if (s->slot[i].active != 0 && s->slot[i].fn == (void *)b183_01E01F30) {
            b183_01E01F30(s, &s->slot[i]);
        }
    }
    func_00207FD0(s->ctx, func_00207500(), 0);
}
