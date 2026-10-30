#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b130(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

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

static void func_01E00150_b130(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b130:01E005A0, 186 insns: the b130 module's event step: red scene colour, counts ticks; tracks two points; at 106 spawns 40 pairs of b130:01E00AB0 / b130:01E00E30 at the camera-side point with random turns and 10 b130:01E012D0 (kind 3); at tick 1 spawns b130:01E00FF0 at the first point; before 106 spawns two b130:01E010B0 a tick there (kind 0, 1 from 99) */

typedef struct {
    u8 pad0[0x80];
    f32 pos[3];
    u8 pad8C[0x3B04 - 0x8C];
    u8 col[4];
    u8 pad3B08[0x3B48 - 0x3B08];
    s16 id0;
    s16 id1;
    u8 pad3B4C[0x3B52 - 0x3B4C];
    s16 turn;
    u8 pad3B54[0x3B58 - 0x3B54];
    s16 kind;
    u8 pad3B5A[2];
    s16 timer;
} Ctx_b130_01E005A0;

static void func_01E005A0_b130(Ctx_b130_01E005A0 *g) {
    extern s32 b130_01E00AB0(void);
    extern s32 b130_01E00E30(void);
    extern s32 b130_01E00FF0(void);
    extern s32 b130_01E010B0(void);
    extern s32 b130_01E012D0(void);
    extern void b130_01E01A00(Ctx_b130_01E005A0 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[4];
    s32 i;
    s32 n;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->timer++;
    func_001F5620(func_001F53A0(), g->id0, v);
    func_001F5620(func_001F5380(), g->id1, v);
    func_001F5F90(func_001F5380(), v);
    if (g->timer == 106) {
        for (i = 0; i < 40; i++) {
            g->turn = func_0019A5C8() % 360;
            g->pos[0] = v[0];
            g->pos[1] = v[1];
            g->pos[2] = v[2];
            b130_01E01A00(g, b130_01E00AB0, 0);
            b130_01E01A00(g, b130_01E00E30, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->id0, v);
    if (g->timer == 1) {
        for (i = 0; i < 1; i++) {
            g->turn = func_0019A5C8() % 360;
            g->pos[0] = v[0];
            g->pos[1] = v[1];
            g->pos[2] = v[2];
            b130_01E01A00(g, b130_01E00FF0, 0);
        }
    }
    if (g->timer < 106) {
        if (g->timer < 99) {
            n = 2;
        } else {
            n = 2;
        }
        for (i = 0; i < n; i++) {
            g->turn = func_0019A5C8() % 360;
            g->pos[0] = v[0];
            g->pos[1] = v[1];
            g->pos[2] = v[2];
            if (g->timer < 99) {
                g->kind = 0;
            } else {
                g->kind = 1;
            }
            b130_01E01A00(g, b130_01E010B0, 0);
        }
    }
    func_001F5620(func_001F5380(), g->id1, v);
    func_001F5F90(func_001F5380(), v);
    if (g->timer == 106) {
        for (i = 0; i < 10; i++) {
            g->turn = func_0019A5C8() % 360;
            g->pos[0] = v[0];
            g->pos[1] = v[1];
            g->pos[2] = v[2];
            g->kind = 3;
            b130_01E01A00(g, b130_01E012D0, 0);
        }
    }
}

/* shape b130:01E00890, 134 insns: b019:01E01F60 with its sine table at ctx+0x3B60 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3B60];
    u8 tab[1];
} Mgr_b130_01E00890;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b130_01E00890;

static s32 func_01E00890_b130(Mgr_b130_01E00890 *m, Fx_b130_01E00890 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* shape b130:01E00AB0, 124 insns: b064:01E01A00 with a tilt of 0..359 and the sine table at g+0x3B60: a grey puff drifting 13 a
   frame; fades in by 8 to 0xA0 for 8 ticks, out by 5; f38 grows to 13, kind steps every 5 ticks to 7 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b130_01E00AB0;

static s32 func_01E00AB0_b130(u8 * g, Spark_b130_01E00AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x3F, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->dir = func_0019A5C8() % 360;
        o->kind = 0;
        o->angle = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 13) {
        o->f38++;
    }
    if (o->tick % 5 == 1) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f8 = o->f8 + 13.0f * func_00108030(g + 0x3B60, o->dir, 0);
    o->fA = o->fA + 13.0f * func_00108030(g + 0x3B60, o->angle, 1);
    o->fC = o->fC + 13.0f * func_00108030(g + 0x3B60, o->dir, 1);
    return 0;
}

/* shape b130:01E00CA0, 97 insns: a faint grey puff: frame 10, angle any way until scene frame 130, then a 120-degree cone facing
   away from the camera side; alpha up by 6 to 0x30 for 8 frames, then down by 7 until it ends */

typedef struct {
    u8 pad0[0x3B5C];
    s16 timer;
} Scene_b130_01E00CA0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b130_01E00CA0;

static s32 func_01E00CA0_b130(Scene_b130_01E00CA0 *g, Obj_b130_01E00CA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->c0, 0x3F, 0x3F, 0x3F);
    if (o->state == 1) {
        o->h38 = 0xA;
        if (func_001F53A0() < 0xA) {
            if (g->timer < 0x82) {
                o->ang = func_0019A5C8() % 360;
            } else {
                o->ang = func_0019A5C8() % 120 - 0x3C;
            }
        } else if (g->timer < 0x82) {
            o->ang = func_0019A5C8() % 360;
        } else {
            o->ang = func_0019A5C8() % 120 + 0x78;
        }
        o->sub = 0;
        o->state = 2;
    }
    if (o->t < 8) {
        if (o->c0[3] < 0x30) {
            o->c0[3] += 6;
        }
    } else if (o->c0[3] > 8) {
        o->c0[3] -= 7;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0x3B60];
    u8 tab[1];
} Mgr_b130_01E00E30;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b130_01E00E30;

static s32 func_01E00E30_b130(Mgr_b130_01E00E30 *m, Obj_b130_01E00E30 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        o->h38 = 5;
        o->h34 = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
        o->h30 = 0;
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    o->h30 += (s16)(func_0019A5C8() % 14 + 1);
    o->x = o->x + 16.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 16.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 16.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b130:01E00FF0, 46 insns: b120:01E01890 family: a purple glow held at alpha 0x80, fading by 15 once the scene value passes 106; ends at scene state 50 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b130_01E00FF0;

typedef struct {
    u8 pad[0x3B00];
    s32 state;
    u8 pad3B04[0x58];
    s16 val;
} Game_b130_01E00FF0;

static s32 func_01E00FF0_b130(Game_b130_01E00FF0 *g, Glow_b130_01E00FF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x1F, 0x10, 0x8F);
    if (o->mode == 1) {
        o->f38 = 5;
        o->col[3] = 0x80;
        o->mode = 2;
    }
    if (g->val > 106) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 15;
        } else {
            o->mode = 0;
        }
    }
    o->tick = 7;
    if (g->state == 0x32) {
        o->mode = 0;
    }
    return 0;
}

/* shape b130:01E010B0, 133 insns: b117:01E01820 with a dark blue colour for kinds 0-1 (0x10/0x10/0x40) or purple
   (0x80/0x40/0x80), start alpha 0x70 / 0xB0 / 0x70 by kind, and kind 1 fading past 40 while growing by 6 */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 kind;
    u8 pad32[2];
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Swell_b130_01E010B0;

static s32 func_01E010B0_b130(void *arg0, Swell_b130_01E010B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->kind < 2) {
        func_001076F0(o->c0, 0x10, 0x10, 0x40);
    } else {
        func_001076F0(o->c0, 0x80, 0x40, 0x80);
    }
    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h34 = 0;
        o->size = 0;
        o->state = 2;
        if (o->kind == 0) {
            o->c0[3] = 0x70;
        }
        if (o->kind == 1) {
            o->c0[3] = 0xB0;
        }
        if (o->kind == 2) {
            o->c0[3] = 0x70;
        }
    }
    if (o->kind == 0) {
        if (o->size > 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        o->size += 1;
    } else if (o->kind == 1) {
        if (o->size > 0x28) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        if (o->size < 0x32) {
            o->size += 6;
        }
    } else {
        if (o->size > 0x14) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0x10;
            } else {
                o->state = 0;
            }
        }
        if (o->size < 0x1E) {
            o->size += 2;
        }
    }
    o->ang += 12;
    return 0;
}

/* shape b130:01E012D0, 67 insns: a blue ring (b056:01E01AF0 shape): set up once at full alpha with a random turn on all
   three axes; grows by 6 up to 50, counts frames, fades by 16 after 40 */

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[8];
    s16 h34;
    s16 state;
    s16 size;
    s16 t;
} Obj_b130_01E012D0;

static s32 func_01E012D0_b130(void *arg0, Obj_b130_01E012D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x20, 0x20, 0x40);
    if (o->state == 1) {
        o->rot[0] = func_0019A5C8() % 65535;
        o->rot[1] = func_0019A5C8() % 65535;
        o->rot[2] = func_0019A5C8() % 65535;
        o->h34 = 0;
        o->size = 0;
        o->state = 2;
        o->c0[3] = 0x80;
    }
    if (o->size > 0x28) {
        if (o->c0[3] > 0x10) {
            o->c0[3] -= 0x10;
        } else {
            o->state = 0;
        }
    }
    if (o->size < 0x32) {
        o->size += 6;
    }
    o->t++;
    return 0;
}

/* shape b130:01E013E0 (b130), 389 insns, 1 copy: b130 scene manager (b058:01E01880 form): with a scene id (>= 0) it
   clears the scene, resets the camera, keeps the id, sets the 170-frame countdown, takes three model handles and
   loads textures 2 and 15; otherwise it seeds the 10-point trail at frame 0 and steps it, runs the module step and
   every live node update (the glow update written out), draws every live node twice by its callback, grows the scene
   scale by 0.01 up to 0.5 after frame 20, counts down and returns 1 / 4 / 2 at frames 96 / 165 / 106, 8 once the
   countdown runs out */

typedef struct Fx_b130_01E013E0 {
    u8 pad0[0x24];
    void *fn;
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 used;
    s16 f38;
    u8 pad3A[6];
} Fx_b130_01E013E0;

typedef struct Scene_b130_01E013E0 {
    u8 pad0[0xC0];
    f32 sx, sy, sz;
    u8 padCC[4];
    s32 tex[16];
    u8 pad110[0x284 - 0x110];
    Fx_b130_01E013E0 fx[220];
    u8 pad3984[0x3A60 - 0x3984];
    Vec_b004_01E00B40 pts[10];
    s32 count;
    u8 pad3B04[8];
    s32 ot;
    u8 pad3B10[0x38];
    s16 model[4];
    u8 pad3B50[0xA];
    s16 id;
    s16 timer;
    u8 pad3B5E[2];
    u8 cam[0x170];
} Scene_b130_01E013E0;

static s32 func_01E013E0_b130(s32 arg0, s32 id) {
    Scene_b130_01E013E0 *g = (Scene_b130_01E013E0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_01E005A0_b130();
    extern s32 func_01E00890_b130();
    extern s32 func_01E00AB0_b130();
    extern s32 func_01E00CA0_b130();
    extern s32 func_01E00E30_b130();
    extern s32 func_01E00FF0_b130();
    extern s32 func_01E010B0_b130();
    extern s32 func_01E012D0_b130();
    extern void b130_01E01B20();
    extern void b130_01E01CC0();
    extern void b130_01E01E60();
    extern void b130_01E022D0();
    extern void b130_01E02730();
    extern void b130_01E028E0();
    s32 j;
    s32 n;
    Vec4f v;
    Vec4f p;
    u8 buf[0x90];
    s32 i;
    Vec_b004_01E00B40 *q;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3CD0);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 170;
        g->sx = 0.0f;
        g->sy = 0.0f;
        g->sz = 0.0f;
        g->model[0] = func_001F5560(func_001F53A0(), 0x6D, 1);
        g->model[1] = func_001F5560(func_001F5380(), 1, 1);
        g->model[2] = func_001F5560(func_001F53A0(), 0x6C, 0);
        for (i = 2; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    if (g->timer == 0) {
        q = g->pts;
        func_001F5620(func_001F53A0(), g->model[0], &p);
        for (i = 0; i < 9; i++, q++) {
            q->x = p.x;
            q->y = p.y;
            q->z = p.z;
        }
    }
    func_01E00080_b130(&g->pts[9], 10, g->model[0]);
    func_01E005A0_b130(g, 0);
    for (j = 0; j < 220; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == func_01E00890_b130) {
                func_01E00890_b130(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00AB0_b130) {
                func_01E00AB0_b130(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00CA0_b130) {
                func_01E00CA0_b130(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00E30_b130) {
                func_01E00E30_b130(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00FF0_b130) {
                func_001076F0(g->fx[j].col, 0x1F, 0x10, 0x8F);
                if (g->fx[j].used == 1) {
                    g->fx[j].f38 = 5;
                    g->fx[j].col[3] = 0x80;
                    g->fx[j].used = 2;
                }
                if (g->timer > 106) {
                    if (g->fx[j].col[3] > 0x10) {
                        g->fx[j].col[3] -= 15;
                    } else {
                        g->fx[j].used = 0;
                    }
                }
                g->fx[j].tick = 7;
                if (g->count == 0x32) {
                    g->fx[j].used = 0;
                }
            }
            if (g->fx[j].fn == func_01E010B0_b130) {
                func_01E010B0_b130(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E012D0_b130) {
                func_01E012D0_b130(g, &g->fx[j]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E00890_b130) {
                b130_01E01CC0(g, &g->fx[i], buf, 0);
                b130_01E01CC0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00AB0_b130) {
                b130_01E01B20(g, &g->fx[i], buf, 0);
                b130_01E01B20(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00CA0_b130) {
                b130_01E01B20(g, &g->fx[i], buf, 0);
                b130_01E01B20(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00E30_b130) {
                b130_01E02730(g, &g->fx[i], buf, 0);
                b130_01E02730(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00FF0_b130) {
                b130_01E01E60(g, &g->fx[i], buf, 0);
                b130_01E01E60(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E010B0_b130) {
                b130_01E022D0(g, &g->fx[i], buf, 0);
                b130_01E022D0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E012D0_b130) {
                b130_01E028E0(g, &g->fx[i], buf, 0);
                b130_01E028E0(g, &g->fx[i], buf, 1);
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
    if (g->timer == 96) {
        return 1;
    }
    if (g->timer == 165) {
        return 4;
    }
    if (g->timer == 106) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b060:01E01890, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3B58 and the two arguments; returns 1 if a
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
} Slot_b060_01E01890;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b060_01E01890 s[220];
    u8 pad3984[0x180];
    u8 r, g, b, a;
    u8 pad3B08[0x50];
    s16 v;
} Pool_b060_01E01890;

static s32 func_01E01A00_b130(Pool_b060_01E01890 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b060_01E01890 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 220; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 220;
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

typedef struct {
    f32 x, y, z, w;
} Vec_b058_01E01F00;

typedef struct {
    u8 pad000[0x10C];
    s32 texture;
} Mgr_b058_01E01F00;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 dx, dy, dz;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[8];
    s16 h34;
    u8 pad36[2];
    s16 scale;
} Obj_b058_01E01F00;

static void func_01E01B20_b130(Mgr_b058_01E01F00 *m, Obj_b058_01E01F00 *o, void *p, s32 flag) {
    extern s32 func_00207500(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    f32 m3[16];
    Vec_b058_01E01F00 pos;
    Vec_b058_01E01F00 buf;
    f32 m2[16];
    Vec_b058_01E01F00 v;
    s32 t;
    f32 s;

    t = func_00207500();
    if (flag == 0) {
        func_00106080(&buf, 0x99, o->h34, &buf);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, &buf, 0);
        func_00208700(p, m->texture, 1);
        return;
    }
    func_00205C40(&v);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m2, 0, &v, &pos);
    s = o->scale;
    func_00108CE0(m3, s, s);
    func_00108F90(m3, p, m2, t);
}

/* shape b053:01E022F0, 103 insns: one textured square of an object (like b058:01E00080); mode 0 only sets up the
   packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn via
   func_00108F90. */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b053_01E022F0;

static void func_01E01CC0_b130(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0xD8), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

INCLUDE_ASM("asm/nonmatchings/mod/b130", func_01E01E60_b130);

/* shape b130:01E022D0, 278 insns, 1 copy: B130PAINT_RAIN5: mode 0 sets the drawing state (a 0x96 matrix from angle 0x34,
   colour, texture 0x10C, vertex alphas 0); otherwise draws two rings of 18 quads (inner radius size-10, outer size,
   20 apart, a random start angle) stepping back along the line between the scene's two joint points (from the
   object once the scene clock passes 40) */

typedef struct Uv_b130_01E022D0 {
    f32 u, v;
} Uv_b130_01E022D0;

typedef struct Pkt_b130_01E022D0 {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Uv_b130_01E022D0 uv;
    struct {
        u8 pad0[0xF];
        u8 a;
    } v[4];
} Pkt_b130_01E022D0;

typedef struct Fx_b130_01E022D0 {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fx_b130_01E022D0;

typedef struct Game_b130_01E022D0 {
    u8 pad0[0x10C];
    s32 tex;
    u8 pad110[0x3B0C - 0x110];
    s32 ot;
    u8 pad3B10[0x3B34 - 0x3B10];
    f32 depth;
    u8 pad3B38[0x3B48 - 0x3B38];
    s16 j0;
    u8 pad3B4A[2];
    s16 j1;
    u8 pad3B4E[0x3B5C - 0x3B4E];
    s16 clock;
    u8 pad3B5E[2];
    u8 trig[1];
} Game_b130_01E022D0;

static void func_01E022D0_b130(Game_b130_01E022D0 *g, Fx_b130_01E022D0 *o, Pkt_b130_01E022D0 *p, s32 mode) {
    extern void func_00106080();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    extern void func_00108EF0();
    extern f32 func_00108030();
    extern s32 func_0019A5C8();
    extern s32 func_00205630();
    extern void func_002075F0();
    extern void func_00208700();
    extern void func_00107740();
    Vec4f quad[4];
    f32 pos[4];
    f32 m[16];
    f32 rm[4];
    f32 a[4];
    f32 b[4];
    Uv_b130_01E022D0 uv;
    s32 k;
    s32 j;
    s16 i;
    s16 r;
    s16 t;
    f32 c;
    f32 s;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 *pb;

    if (mode == 0) {
        func_00106080(rm, 0x96, o->h34, rm);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->uv.v = 0;
        p->v[0].a = 0;
        p->v[1].a = 0;
        p->v[2].a = 0;
        p->v[3].a = 0;
        func_00107740(&uv, o->col);
        p->uv = uv;
        func_01E00150_b130((void *)p, (void *)rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_001F5620(func_001F53A0(), g->j0, a);
    func_001F5620(func_001F53A0(), g->j1, pb = (f32 *)(u32)b);
    dx = a[0] - pb[0];
    dy = a[1] - b[1];
    dz = a[2] - b[2];
    quad[0].y = 0;
    quad[1].y = 0;
    quad[2].y = 0;
    quad[3].y = 0;
    dx /= 14.0f;
    dy /= 14.0f;
    dz /= 14.0f;
    for (k = 1; k < 3; k++) {
        if (g->clock > 40) {
            pos[0] = o->x - dx * k;
            pos[1] = o->y - dy * k;
            pos[2] = o->z - dz * k;
        } else {
            pos[0] = a[0] - dx * k;
            pos[1] = a[1] - dy * k;
            pos[2] = a[2] - dz * k;
        }
        func_00108EF0(m, NULL, o->rot, pos);
        i = 0;
        r = func_0019A5C8() % 360;
        for (j = 0; j < 18; j++) {
            t = r + (o->ang + i);
            c = func_00108030(g->trig, t, 1);
            s = func_00108030(g->trig, t, 0);
            quad[2].x = c * o->size;
            quad[2].z = s * o->size;
            quad[0].x = c * (o->size - 10);
            quad[0].z = s * (o->size - 10);
            t = r + (o->ang + 20 + i);
            c = func_00108030(g->trig, t, 1);
            s = func_00108030(g->trig, t, 0);
            quad[3].x = c * o->size;
            quad[3].z = s * o->size;
            quad[1].x = c * (o->size - 10);
            quad[1].z = s * (o->size - 10);
            if (func_00205630(quad, 0x70000000, m, p, &g->depth)) {
                func_002075F0(p, g->ot, func_001A23B0(g->depth));
            }
            i += 20;
        }
    }
}

/* shape b130:01E02730, 106 insns: mode 0 sets the drawing state (a 0x99 matrix from its angle 0x34, colour, the scene
   texture 0x10C); otherwise draws the effect as a camera-facing square of its size 0x38: camera rotation, world matrix (scale 0.1) at its position offset by
   a tenth of 0x8..0xC, then func_00108F90 */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b130_01E02730;

typedef struct {
    u8 pad0[0x10C];
    s32 tex;
} Scene_b130_01E02730;

static void func_01E02730_b130(Scene_b130_01E02730 *g, Fx_b130_01E02730 *o, void *p, s32 mode) {
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

    v = (s32)func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x99, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        func_00205C40((s32)rot);
        pos.x = o->x + o->dx / 10;
        pos.y = o->y + o->dy / 10;
        pos.z = o->z + o->dz / 10;
        func_00108EF0(m, &scale, rot, &pos);
        func_00108CE0(quad, o->size, o->size);
        func_00108F90(quad, p, m, v);
    }
}

/* shape b130:01E028E0, 187 insns: b159:01E01B30 family ring of 6 segments (35 degrees each, 60 apart from 0x3A) at radius 0x38 from the centre, drawn twice per segment: texture 0x97 in the object's colour, then 0x96 in dark blue (0x20, 0x20, 0x40) at the object's alpha; mode 0 sets texture 0x9C and the scene texture (ctx+0x10C) */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b130_01E028E0;

typedef struct W_c2_func_01E028E0_b130 {
    u8 v[4];
} W_c2_func_01E028E0_b130;

static void func_01E028E0_b130(u8 *ctx, Obj_b130_01E028E0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001A23B0(f32);
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    u8 td[0x10];
    extern W_c2_func_01E028E0_b130 D_01E02C00_b130;
    W_c2_func_01E028E0_b130 c2_w = D_01E02C00_b130;
    s32 i;
    s16 a;
    s16 k;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x9C, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, NULL, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 6; i++) {
        k = o->ang + a;
        q[2].x = o->size * func_00108030(ctx + 0x3B60, k, 1);
        q[2].z = o->size * func_00108030(ctx + 0x3B60, k, 0);
        q[0].x = 0.0f;
        q[0].z = 0.0f;
        k = o->ang + 35 + a;
        q[3].x = o->size * func_00108030(ctx + 0x3B60, k, 1);
        q[3].z = o->size * func_00108030(ctx + 0x3B60, k, 0);
        q[1].x = 0.0f;
        q[1].z = 0.0f;
        func_00107790(pkt, o->col, 0);
        func_00106080(td, 0x97, o->page, td);
        func_00108500(pkt, td, 1);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3B34)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x3B0C), func_001A23B0(*(f32 *)(ctx + 0x3B34)));
        }
        c2_w.v[3] = o->col[3];
        func_00107790(pkt, c2_w.v, 0);
        func_00106080(td, 0x96, o->page, td);
        func_00108500(pkt, td, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3B34)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x3B0C), func_001A23B0(*(f32 *)(ctx + 0x3B34)));
        }
        a += 60;
    }
}
