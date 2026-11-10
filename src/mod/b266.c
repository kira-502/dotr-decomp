#include "common.h"

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00080_b266(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E00920;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E00920 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E00920;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    u8 padA[6];
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E00920;

static void func_01E004D0_b266(u8 *self, Obj_b018_01E00920 *obj, Pk_b018_01E00920 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E00920 uv;
    s16 i;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00080_b266((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < 20; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        m[1] = 0.0f;
        m[5] = 0.0f;
        m[0] = 1.0f;
        m[4] = -1.0f;
        m[2] = 0.0f;
        m[6] = 0.0f;
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b266", func_01E00800_b266);

/* shape b266:01E01060, 87 insns: on start 0x38 = 8, random rotation (0x18 -0x2000..0x1FFF, 0x14), variant 0..6; alpha grows
   by 0x50 (below 0xA0) for 2 ticks, then fades by 13 once 0x38 passes 0x14 and by 15 while the game counter at
   0x2EA0 is below 10; colour (0x80, 0x40, 0); 0x38 grows by 4 */

typedef struct {
    u8 pad0[0x2EA0];
    s32 count;
} Game_b266_01E01060;

typedef struct {
    u8 pad0[0x14];
    s32 rot14;
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b266_01E01060;

static s32 func_01E01060_b266(Game_b266_01E01060 *g, Fx_b266_01E01060 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->rot18 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot14 = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0x14) {
            if (o->col[3] > 0xE) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->tick++;
    o->f38 += 4;
    return 0;
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b266:01E011C0, 113 insns: swipe that turns to face the camera side, fades in, widens and fades out */

typedef struct Sw_b266_01E011C0 {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[0xC];
    u8 c28[4];
    u8 c2C[4];
    s16 w;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
} Sw_b266_01E011C0;

typedef struct Scn_b266_01E011C0 {
    u8 pad0[0x2EA0];
    s32 count;
} Scn_b266_01E011C0;

static s32 func_01E011C0_b266(Scn_b266_01E011C0 *sc, Sw_b266_01E011C0 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F6160();
    s32 v[4];
    s16 side;

    func_001076F0(o->c28, 0x18, 0x18, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), v);
        side = (s32)((f32)v[1] / 180.0f);
        if (side != 0) {
            o->f10 = -0x4000;
        } else {
            o->f10 = -0xC000;
        }
        o->f14 = 0;
        if (side != 0) {
            if (o->w == 0) {
                o->f18 = 0x1800;
            } else {
                o->f18 = -0x1800;
            }
        } else if (o->w == 0) {
            o->f18 = -0x1800;
        } else {
            o->f18 = 0x1800;
        }
        o->h34 = 0;
        o->w = 0x5A;
        o->state = 2;
        o->c28[3] = 0;
    }
    if (o->age < 2) {
        if (o->c28[3] < 0x80) {
            o->c28[3] += 0x40;
        }
    } else if (o->c28[3] > 10) {
        o->c28[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 = 50;
    o->age++;
    if (o->w < 0xA0) {
        o->w += 8;
    }
    if (sc->count < 15) {
        if (o->c28[3] > 14) {
            o->c28[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b266:01E01390, 59 insns: an orange glow that drops toward the scene joint's height (step = func_001A22C0 of the gap): in by 25 up to 0x80 for 5 ticks */

typedef struct {
    s16 h0;
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b266_01E01390;

typedef struct {
    u8 pad[0x2EEA];
    s16 joint;
} Game_b266_01E01390;

static s32 func_01E01390_b266(Game_b266_01E01390 *g, Glow_b266_01E01390 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    Vec4f pos;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x50, 0x20, 0);
        func_001F5620(func_001F53A0(), g->joint, &pos);
        o->hE = func_001A22C0(pos.y - o->h2);
        o->f38 = 50;
        o->ang = 0;
        o->kind = 2;
        o->h30 = 1;
        o->mode = 2;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x19;
        }
    }
    o->tick++;
    o->hA -= o->hE;
    return 0;
}

/* shape b266:01E01480, 100 insns: a grey camera-facing slash: frame 3..10, turned by the camera side and by its side flag
   (+-0x2800 tilt), random sub-frame 0..6; alpha up by 20 to 0x50 for 4 frames, then down by 13 until it ends */

typedef struct {
    u8 pad0[6];
    s16 side0;
    u8 pad8[8];
    s32 rot0;
    u8 pad14[4];
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 side;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b266_01E01480;

static s32 func_01E01480_b266(void *arg0, Obj_b266_01E01480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s16 func_001A22C0(f32);
    s32 ang[4];
    s32 flip;

    func_001F6160(func_001F53A0(), ang);
    flip = func_001A22C0(ang[1] / 180.0f);
    func_001076F0(o->c0, 0xA0, 0xA0, 0xA0);
    if (o->state == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (flip != 0) {
            o->rot0 = 0;
        } else {
            o->rot0 = 0x8000;
        }
        if (flip != 0) {
            if (o->side == 0) {
                o->rot2 = -0x2800;
            } else {
                o->rot2 = 0x2800;
            }
        } else if (o->side == 0) {
            o->rot2 = 0x2800;
        } else {
            o->rot2 = -0x2800;
        }
        o->side0 = o->side;
        o->sub = func_0019A5C8() % 7;
    }
    if (o->t < 4) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x14;
        }
    } else if (o->c0[3] > 0xE) {
        o->c0[3] -= 0xD;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b266:01E01610, 101 insns: an orange ember (size 13, frame 2) at two random angles drifting 9 a tick on all three axes (sine table ctx+0x3004): alpha 0x80 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[2];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b266_01E01610;

typedef struct {
    u8 pad[0x3004];
    u8 sin[1];
} Game_b266_01E01610;

static s32 func_01E01610_b266(Game_b266_01E01610 *g, Glow_b266_01E01610 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 13;
        o->kind = 2;
        func_001076F0(o->col, 0x60, 0x40, 8);
        o->h30 = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 9.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 9.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 9.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b207:01E030D0, 79 insns, 2 copies: a streak flash: size and turn by kind (0..3) once, two colours; full alpha for 5
   frames, then fades out (b003:01E01780 family) */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Obj_b207_01E030D0;

static s32 func_01E017B0_b266(void *arg0, Obj_b207_01E030D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 k;

    if (o->state == 1) {
        if ((k = o->kind) == 0) {
            o->h38 = 0x19;
            o->h34 = 6;
        } else if (k == 1) {
            o->h38 = 6;
            o->h34 = 0x19;
        } else if (k == 2) {
            o->h38 = 0x15;
            o->h34 = 6;
            o->h3A = 0x2D;
        } else if (k == 3) {
            o->h38 = 0x15;
            o->h34 = 6;
            o->h3A = -0x2D;
        }
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x80, 0x40, 0);
        o->state = 2;
    }
    if (o->t < 5) {
        o->c0[3] = 0x40;
        o->c1[3] = 0;
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 7;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[8];
    s32 seed;
    u8 pad1C[0xC];
    u8 col[3];
    u8 alpha;
    u8 pad2C[4];
    s16 pos;
    s16 age;
    s16 kind;
    s16 state;
    s16 mode;
    s16 angle;
} Spark_b018_01E02950;

static s32 func_01E018F0_b266(s32 unused, Spark_b018_01E02950 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->mode = 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->seed = func_0019A5C8() % 0xFFFF;
        o->pos = 0;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->limit = func_0019A5C8() % 3 + 1;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x80;
    } else if (o->alpha > 16) {
        o->alpha -= 10;
    } else {
        o->state = 0;
    }
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b266:01E01A60, 119 insns: b582:01E03470 family scene light at ctx+0x2D00 (orange 4/2/0, height 70) whose range swells by 42 to 128 while it rises and shrinks by 16 to 0 while it falls; applied while alive; ends at scene state 1 */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Obj_b266_01E01A60;

typedef struct {
    f32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 h;
    f32 level;
    u8 pad2C[0x174];
    s32 state;
} Light_b266_01E01A60;

typedef struct {
    u8 pad[0x2D00];
    Light_b266_01E01A60 l;
} Game_b266_01E01A60;

static s32 func_01E01A60_b266(Game_b266_01E01A60 *g, Obj_b266_01E01A60 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->l.w0 = 0.0f;
        g->l.r = 4.0f;
        g->l.g = 2.0f;
        g->l.b = 0.0f;
        g->l.w20 = 0;
        g->l.h = 70.0f;
        g->l.level = 0.0f;
        g->l.x = o->x;
        g->l.y = o->y;
        g->l.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->l.level < 1.0f) {
            g->l.level += 0.2f;
        } else {
            o->phase = 1;
        }
        if (g->l.w0 < 128.0f) {
            g->l.w0 += 42.0f;
        } else {
            g->l.w0 = 128.0f;
        }
    } else {
        if (g->l.level > 0.1f) {
            g->l.level -= 0.1f;
        } else {
            o->mode = 0;
        }
        if (g->l.w0 > 16.0f) {
            g->l.w0 -= 16.0f;
        } else {
            g->l.w0 = 0.0f;
        }
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->l);
    }
    if (g->l.state == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b266:01E01C40, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2EA0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2EA0];
    s32 state;
} Game_b266_01E01C40;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b266_01E01C40;

static s32 func_01E01C40_b266(Game_b266_01E01C40 *g, Fade_b266_01E01C40 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
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
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

static s32 func_01E01D00_b266(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03580_b266;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03588_b266;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b266:01E01D50 (b266), 499 insns, 1 copy: b266 scene manager (b194:01E01B30 form): with a scene id (>= 0) it
   clears the scene, resets the camera, keeps the id, sets the 190-frame countdown, takes four model handles, loads
   textures 10..15 and 2, lays out nine 5x50 quads along a sine arc and fills a 256-byte random table (-15..14);
   otherwise it runs the module step and every live node update (B266_OBJ_MOVE_201_ written out in place), draws every
   live node (twice by its drawer, or the PAINT_Fragment_3 burst with frame 0x9B), grows the scene scale by 0.01 up to
   0.5 after frame 20, counts down and returns 1 / 4 / 2 at frames 124 / 180 / 165, 6 in 135..159, 8 once the
   countdown runs out */

typedef struct Fx_b266_01E01D50 {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 idx;
    s16 used;
    u8 pad38[0x8];
} Fx_b266_01E01D50;

typedef struct Uv_b266_01E01D50 {
    f32 a, b, c, d;
} Uv_b266_01E01D50;

typedef struct Scene_b266_01E01D50 {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Uv_b266_01E01D50 uv;
    u8 padA4[0x310 - 0xA4];
    f32 sx, sy, sz;
    u8 pad31C[0x340 - 0x31C];
    s32 tex[16];
    f32 m[10][16];
    u8 pad600[0x774 - 0x600];
    Fx_b266_01E01D50 fx[150];
    u8 pad2CF4[0x2EA0 - 0x2CF4];
    s32 count;
    u8 pad2EA4[8];
    s32 ot2;
    u8 pad2EB0[0x2EE8 - 0x2EB0];
    s16 model[4];
    u8 pad2EF0[0xC];
    s16 id;
    s16 timer;
    u8 pad2F00[2];
    s8 rnd[256];
    u8 pad3002[2];
    u8 sin[0x3170 - 0x3004];
} Scene_b266_01E01D50;

static s32 func_01E01D50_b266(s32 arg0, s32 id) {
    Scene_b266_01E01D50 *g = (Scene_b266_01E01D50 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_01E00800_b266();
    extern void b266_01E02640();
    extern void b266_01E029F0();
    extern void b266_01E02D50();
    extern void b266_01E02F10();
    extern void b266_01E03130();
    extern void b266_01E03340();
    s32 a;
    Vec4f v;
    Uv_b266_01E01D50 uv;
    u8 buf[0x90] __attribute__((aligned(8)));
    f32 fc;
    s32 i;
    s32 n;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3170);
        func_00107C10(g->sin);
        g->id = id;
        g->count = 190;
        g->sx = 0.0f;
        g->sy = 0.0f;
        g->sz = 0.0f;
        g->model[0] = func_001F5560(func_001F53A0(), 0x18, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x29, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x1D, 0);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (a = 0; a < 10; a++) {
            func_00108CE0(g->m[a], 5.0f, 50.0f);
        }
        for (i = 0; i < 9; i++) {
            g->m[i][1] = 15.0f * func_00108030(g->sin, i * 20, 0);
            g->m[i][5] = 15.0f * func_00108030(g->sin, i * 20 + 20, 0);
            g->m[i][9] = 35.0f * func_00108030(g->sin, i * 20, 0);
            g->m[i][13] = 35.0f * func_00108030(g->sin, i * 20 + 20, 0);
            fc = i * 10 - 45;
            g->m[i][0] += fc;
            g->m[i][4] += fc;
            g->m[i][8] += fc;
            g->m[i][12] += fc;
            g->m[i][1] -= 10.0f;
            g->m[i][5] -= 10.0f;
            g->m[i][9] += 15.0f;
            g->m[i][13] += 15.0f;
            g->m[i][2] = 0.0f;
            g->m[i][6] = 0.0f;
            g->m[i][10] = 0.0f;
            g->m[i][14] = 0.0f;
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E00800_b266(g, 0);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E01060_b266) {
                func_01E01060_b266((Game_b266_01E01060 *)g, (Fx_b266_01E01060 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E011C0_b266) {
                func_01E011C0_b266((Scn_b266_01E011C0 *)g, (Sw_b266_01E011C0 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01390_b266) {
                func_01E01390_b266((Game_b266_01E01390 *)g, (Glow_b266_01E01390 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01480_b266) {
                func_01E01480_b266(g, (Obj_b266_01E01480 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01610_b266) {
                func_01E01610_b266((Game_b266_01E01610 *)g, (Glow_b266_01E01610 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E017B0_b266) {
                func_01E017B0_b266(g, (Obj_b207_01E030D0 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E018F0_b266) {
                func_01E018F0_b266((s32)g, (Spark_b018_01E02950 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01A60_b266) {
                func_01E01A60_b266((Game_b266_01E01A60 *)g, (Obj_b266_01E01A60 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01C40_b266) {
                func_01E01C40_b266((Game_b266_01E01C40 *)g, (Fade_b266_01E01C40 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01D00_b266) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E03580_b266;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E03588_b266;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 150; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E01060_b266) {
                b266_01E029F0(g, &g->fx[i], buf, 0);
                b266_01E029F0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E011C0_b266) {
                b266_01E02640(g, &g->fx[i], buf, 0);
                b266_01E02640(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01390_b266) {
                b266_01E02D50(g, &g->fx[i], buf, 0);
                b266_01E02D50(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01480_b266) {
                b266_01E02F10(g, &g->fx[i], buf, 0);
                b266_01E02F10(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01610_b266) {
                b266_01E03130(g, &g->fx[i], buf, 0);
                b266_01E03130(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E017B0_b266) {
                b266_01E03340(g, &g->fx[i], buf, 0);
                b266_01E03340(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E018F0_b266) {
                g->tex88 = g->tex[15];
                func_00106080(&uv, 0x9B, g->fx[i].idx, 0);
                g->uv = uv;
                func_01E004D0_b266((u8 *)g, (Obj_b018_01E00920 *)&g->fx[i], (Pk_b018_01E00920 *)buf, g->rnd);
            }
        }
    }
    if (g->timer > 20) {
        if (g->sx < 0.5) {
            g->sx += 0.01f;
        }
        g->sy = 0.1f;
        if (g->sz < 0.5) {
            g->sz += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 124) {
        return 1;
    }
    if (g->timer == 180) {
        return 4;
    }
    if (g->timer == 165) {
        return 2;
    }
    if (g->timer > 134 && g->timer < 160) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}


/* shape b266:01E02520, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2EFA and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b266_01E02520;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x4A4];
    Slot_b266_01E02520 s[150];
    u8 pad2CF4[0x1B0];
    u8 r, g, b, a;
    u8 pad2EA8[0x52];
    s16 v;
} Pool_b266_01E02520;

static s32 func_01E02520_b266(Pool_b266_01E02520 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b266_01E02520 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b266:01E02640, 233 insns: b018:01E03760's cone of 9 quads with the tilt capped at 135, outer radii 40 and 30,
   the trig table at ctx+0x3004, depth ctx+0x2ED4 and ot ctx+0x2EAC */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b266_01E02640;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b266_01E02640;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b266_01E02640 c;
    struct {
        u64 tc;
        Xyz_b266_01E02640 p;
    } v[4];
} Pkt_b266_01E02640;

typedef struct {
    u8 pad0[0x37C];
    void *texture;
    u8 pad380[0x2EAC - 0x380];
    s32 ot;
    u8 pad2EB0[0x2ED4 - 0x2EB0];
    f32 dep;
    u8 pad2ED8[0x3004 - 0x2ED8];
    u8 trig[1];
} Ctx_b266_01E02640;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 tilt;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b266_01E02640;

static void func_01E02640_b266(Ctx_b266_01E02640 *c, Fan_b266_01E02640 *o, Pkt_b266_01E02640 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b266_01E02640 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 j;
    s16 tl;
    s32 t2;
    s16 a;
    s16 t;
    f32 r0;
    f32 r1;
    f32 r2;
    f32 r3;
    f32 sn;
    f32 cs;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00080_b266((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, NULL, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        if (o->tilt > 0x87) {
            tl = 0x87;
        }
        quad[0].y = 45.0f * func_00108030(c->trig, o->tilt, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 45.0f * func_00108030(c->trig, o->tilt + 0x23, 0);
        quad[3].y = quad[2].y;
        r0 = 40.0f * func_00108030(c->trig, tl, 1);
        t2 = tl + 0x1E;
        r1 = 30.0f * func_00108030(c->trig, t2, 1);
        r2 = 3.0f * func_00108030(c->trig, tl, 1);
        r3 = 3.0f * func_00108030(c->trig, t2, 1);
        a = 0;
        for (k = 0; k < 9; k++) {
            t = o->ang + a;
            sn = func_00108030(c->trig, t, 1);
            cs = func_00108030(c->trig, t, 0);
            quad[2].x = sn * r2;
            quad[2].z = cs * r1;
            quad[0].x = sn * r3;
            quad[0].z = cs * r0;
            t = o->ang + 0x28 + a;
            sn = func_00108030(c->trig, t, 1);
            cs = func_00108030(c->trig, t, 0);
            quad[3].x = sn * r2;
            quad[3].z = cs * r1;
            quad[1].x = sn * r3;
            quad[1].z = cs * r0;
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 0x28;
        }
    }
    }
}

/* OVL_WARM */

/* shape b266:01E029F0, 216 insns: b018:01E03B10's ring draw with b266's ctx (target 0x2EAC, depth 0x2ED4, trig
   0x3004); the corner helper (shape b008:01E00080) is the module's 0x1E00080 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b266_01E029F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b266_01E029F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b266_01E029F0 c;
    struct {
        u64 tc;
        Xyz_b266_01E029F0 p;
    } v[4];
} Pkt_b266_01E029F0;

typedef struct {
    f32 x, y, z, w;
} Vec_b266_01E029F0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b266_01E029F0;

typedef struct {
    u8 pad00[0x37C];
    void *texture;
    u8 pad380[0x2EAC - 0x380];
    s32 target;
    u8 pad2EB0[0x2ED4 - 0x2EB0];
    f32 depth;
    u8 pad2ED8[0x3004 - 0x2ED8];
    u8 trig[1];
} Obj_b266_01E029F0;

static void func_01E029F0_b266(Obj_b266_01E029F0 *o, Anim_b266_01E029F0 *an, Pkt_b266_01E029F0 *p, s32 draw) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b266_01E029F0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b266_01E029F0 quad[4];
    Vec_b266_01E029F0 pos;
    Vec_b266_01E029F0 scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    if (draw == 0) {
        func_00106080(td, 0x9B, an->h34, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(an->col);
        func_01E00080_b266((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, o->texture, 1);
        return;
    }
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->trig, a, 1);
        quad[2].z = an->radius * func_00108030(o->trig, a, 0);
        quad[0].x = (an->radius - 17) * func_00108030(o->trig, a, 1);
        quad[0].z = (an->radius - 17) * func_00108030(o->trig, a, 0);
        a = j + (an->start + 40);
        quad[3].x = an->radius * func_00108030(o->trig, a, 1);
        quad[3].z = an->radius * func_00108030(o->trig, a, 0);
        quad[1].x = (an->radius - 17) * func_00108030(o->trig, a, 1);
        quad[1].z = (an->radius - 17) * func_00108030(o->trig, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &o->depth) != 0) {
            func_002075F0(p, o->target, (u32)o->depth);
        }
        j += 40;
    }
}

/* shape b266:01E02D50, 111 insns: draws a small sprite (b089:01E03780 shape): unlit, it sets up the colour and texture page; lit,
   it builds a matrix at a tenth scale from its turn, at its position plus a tenth of its drift, and draws a square of its size
   with the lower texture corners at u 0.5 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b266_01E02D50;

typedef struct {
    u8 pad0[0x37C];
    s32 tex;
} Scene_b266_01E02D50;

static void func_01E02D50_b266(Scene_b266_01E02D50 *g, Fx_b266_01E02D50 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;
    f32 f;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9b, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    scale.z = 0.1f;
    scale.y = 0.1f;
    scale.x = 0.1f;
    func_00205C40((s32)rot);
    f = o->dx;
    f /= 10.0f;
    pos.x = o->x;
    pos.x += f;
    f = o->dy;
    f /= 10.0f;
    pos.y = o->y;
    pos.y += f;
    f = o->dz;
    f /= 10.0f;
    pos.z = o->z;
    pos.z += f;
    func_00108EF0(m, &scale, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[2].x = 0.5f;
    quad[3].x = 0.5f;
    func_00108F90(quad, p, m, v);
}

/* shape b266:01E02F10, 133 insns: b120:01E03DF0-family nine-quad draw: mode 0 sets the material (frame 0x97, two corners each colour), else one matrix (scale 0.55, turn 0x10 - 0x4000 and 0x18) at the effect position and nine quads sent at the scene depth */

typedef struct {
    f32 x, y, z, w;
} Vec_b266_01E02F10;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b266_01E02F10;

typedef struct {
    Rgbaq_b266_01E02F10 c;
    u64 st;
    u64 xyz;
} Vtx_b266_01E02F10;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b266_01E02F10 v[4];
} Pkt_b266_01E02F10;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 x2, y2, z2;
    u8 pad0E[2];
    s32 r0;
    s32 r1;
    s32 r2;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
} Anim_b266_01E02F10;

typedef struct {
    u8 pad00[0x290];
    u8 m[0x40];
    u8 pad2D0[0xAC];
    s32 texture;
    Vec_b266_01E02F10 quad[9][4];
    u8 pad5C0[0x2EAC - 0x5C0];
    s32 target;
    u8 pad2EB0[0x24];
    f32 depth;
} Game_b266_01E02F10;

static void func_01E02F10_b266(Game_b266_01E02F10 *g, Anim_b266_01E02F10 *an, Pkt_b266_01E02F10 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b266_01E02F10 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b266_01E02F10 pos;
    f32 rm[4];
    s32 rot[4];
    Vec_b266_01E02F10 sc;
    f32 t;
    f32 m[16];
    s16 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        func_0020EB40(g->m);
        func_00106DD0(&pos, an->x, an->y, an->z);
        sc.x = 0.55f;
        sc.y = 1.0f;
        sc.z = 1.0f;
        rot[0] = an->r0 - 0x4000;
        rot[1] = 0;
        rot[2] = an->r2;
        func_0020C940(m, &sc, rot, &pos);
        func_0020BC00(g->m, m);
        for (i = 0; i < 9; i++) {
            if (func_00205630(g->quad[i], 0x70000000, g->m, p, &g->depth) != 0) {
                func_00109380(p, 0);
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

/* shape b266:01E03130, 131 insns: b195:01E03200 with frame 0x9B, scene texture 0x37C, packet list 0x2EAC and depth 0x2ED4 */

typedef struct {
    f32 s;
    f32 t;
} St_b266_01E03130;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b266_01E03130 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b266_01E03130;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    u8 padE[0x1A];
    u8 tex[8];
    u8 pad30[4];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Obj_b266_01E03130;

typedef struct {
    u8 pad0[0x37C];
    void *tex;
    u8 pad380[0x2B2C];
    s32 ctx;
    u8 pad4030[0x24];
    f32 depth[1];
} Scene_b266_01E03130;

static void func_01E03130_b266(Scene_b266_01E03130 *g, Obj_b266_01E03130 *obj, Pk_b266_01E03130 *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    Rect_b008_01E00080 rect[2];
    Vec4f world[4];
    s32 rot[4];
    St_b266_01E03130 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0x9B, obj->h34, rect);
        pk->nreg = 0x24;
        pk->n = 9;
        pk->regs = 0x24242421 | ((s64)4 << 32);
        pk->pad4 = 0;
        pk->nreg |= 0x800;
        func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
        *(s32 *)&pk->st.t = 0;
        pk->q0 = 0;
        pk->q1 = 0;
        pk->q2 = 0;
        pk->q3 = 0;
        func_00107740(&uv, obj->tex);
        pk->st = uv;
        func_01E00080_b266((Pk_b008_01E00080 *)pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        func_00205C40((s32)rot);
        fx = obj->dx;
        fy = obj->dy;
        fz = obj->dz;
        fx /= 10.0f;
        fy /= 10.0f;
        fz /= 10.0f;
        pos.x = obj->x + fx;
        pos.y = obj->y + fy;
        pos.z = obj->z + fz;
        func_00108EF0(world, &scale, rot, &pos);
        r = obj->size;
        func_00108CE0(m, r, r);
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, g->depth) != 0) {
            func_002075F0((s32)pk, g->ctx, func_001A23B0(g->depth[0]));
        }
    }
}

/* shape b266:01E03340, 142 insns: b207:01E04850 with the scene table at ctx+0x3004 */

/* OVL_WARM */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b266_01E03340;

typedef struct {
    Rgbaq_b266_01E03340 c;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b266_01E03340;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b266_01E03340 v[4];
} Pkt_b266_01E03340;

typedef struct {
    u8 pad0[0x3004];
    u8 tab[1];
} Ctx_b266_01E03340;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 colB[4];
    u8 colA[4];
    u8 pad30[4];
    s16 u;
    u8 pad36[2];
    s16 v;
    s16 rz;
} Fx_b266_01E03340;

static void func_01E03340_b266(Ctx_b266_01E03340 *g, Fx_b266_01E03340 *o, Pkt_b266_01E03340 *p, s32 lit) {
    extern Rgbaq_b266_01E03340 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    s32 rot[4];
    s32 r[4];
    f32 depth[4];
    s32 ot;
    s16 i;
    f32 ax, ay, az;

    ot = (s32)func_00207500();
    if (lit == 0) {
        func_001092E0(p, 0);
        func_001094F0(p);
        p->v[0].c = func_00107740(o->colA);
        p->v[1].c = func_00107740(o->colA);
        p->v[2].c = func_00107740(o->colA);
        p->v[3].c = func_00107740(o->colB);
    } else {
    sc.x = 1.0f;
    sc.y = 1.0f;
    sc.z = 1.0f;
    func_00205C40((s32)rot);
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    func_00108EF0(m, &sc, rot, &pos);
    r[2] = o->rz;
    r[1] = 0;
    r[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, o->u, o->v, i);
        func_00109100(quad, r, 2, g->tab);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, ot, (u32)depth[0]);
        }
    }
    }
}
