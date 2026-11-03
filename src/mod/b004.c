#include "common.h"

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

/* shape b004:01E00080, 246 insns: the effect scene's step (frame test 79/80/81 kept as three compares: -O3,p): sets
   the scene colour to dark red, counts the frame (0x34AC), turns the camera heading (b004:01E00C10 / 180 - 180, kept
   at 0x349C) into a height offset 15 x -cos; frame 79 spawns 0x1E00460, 45 spawns 0x1E004E0; frame 77 copies the
   point (0x3300) to 0x3440; frame 78 spawns forty 0x1E006B0 with random turns (by the heading's side); frames 79..81
   spawn thirty 0x1E00560 around the point; frame 79 sixty 0x1E00790 at it; frames 46..83 spawn 0x1E009F0 there */

typedef struct {
    u8 pad0[0x80];
    f32 qx, qy, qz;
    s32 w8C;
    u8 pad90[0x10];
    s32 rA0;
    u8 padA4[4];
    s32 rA8;
    u8 padAC[0x3300 - 0xAC];
    f32 px, py, pz;
    u8 pad330C[0x3440 - 0x330C];
    f32 mx, my, mz;
    u8 pad344C[8];
    u8 col[4];
    u8 pad3458[0x349C - 0x3458];
    s16 head;
    u8 pad349E[2];
    s16 h34A0;
    u8 pad34A2[6];
    s16 h34A8;
    u8 pad34AA[2];
    s16 t;
    u8 pad34AE[0x34E0 - 0x34AE];
    u8 trig[1];
} Scene_b004_01E00080;


#pragma optimization_level 3

static void func_01E00080_b004(Scene_b004_01E00080 *g) {
    extern void b004_01E00460(void);
    extern void b004_01E004E0(void);
    extern void b004_01E00560(void);
    extern void b004_01E006B0(void);
    extern void b004_01E00790(void);
    extern void b004_01E009F0(void);
    extern f32 b004_01E00C10(s32);
    extern s32 b004_01E012B0(Scene_b004_01E00080 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern f32 func_00108030(void *, s16, s32);
    s32 i;
    s32 h;
    s32 z;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    g->head = (s16)(b004_01E00C10(func_001F53A0()) / 180.0f);
    g->head -= 180;
    h = (s32)(15.0f * -func_00108030(g->trig, g->head, 1));
    g->h34A8 = 0;
    g->w8C = 0;
    if (g->t == 79) {
        b004_01E012B0(g, (s32)b004_01E00460, 0);
    }
    if (g->t == 45) {
        b004_01E012B0(g, (s32)b004_01E004E0, 0);
    }
    g->col[3] = 0;
    if (g->t == 77) {
        g->mx = g->px;
        g->my = g->py;
        g->mz = g->pz;
    }
    if (g->t == 78) {
        for (i = 0; i < 40; i++) {
            if (-g->head < 90) {
                g->rA0 = func_0019A5C8() % 0x8000 - 0x8000;
            } else {
                z = 0;
                g->rA0 = func_0019A5C8() % 0x8000 + z;
            }
            g->rA8 = func_0019A5C8() % 0x8000 + 0x4000;
            g->qx = 0.0f;
            g->qy = 0.0f;
            g->qz = 0.0f;
            b004_01E012B0(g, (s32)b004_01E006B0, 0);
        }
    }
    if (g->t == 79 || g->t == 80 || g->t == 81) {
        for (i = 0; i < 30; i++) {
            g->qx = g->px + (f32)(func_0019A5C8() % 20) - 10.0f;
            g->qy = g->py + (f32)(func_0019A5C8() % 20) - 10.0f;
            g->qz = (f32)h + (g->pz + (f32)(func_0019A5C8() % 20) - 10.0f);
            g->h34A8 = func_0019A5C8() % 80;
            g->h34A0 = func_0019A5C8() % 360;
            b004_01E012B0(g, (s32)b004_01E00560, 0);
        }
    }
    if (g->t == 79) {
        for (i = 0; i < 60; i++) {
            g->qx = g->px;
            g->qy = g->py;
            g->qz = g->pz + h;
            b004_01E012B0(g, (s32)b004_01E00790, 0);
        }
    }
    if (g->t > 45 && g->t < 84) {
        g->qx = g->px;
        g->qy = g->py;
        g->qz = g->pz;
        g->h34A8 = 0;
        g->h34A0 = 0;
        b004_01E012B0(g, (s32)b004_01E009F0, 0);
    }
}
#pragma optimization_level reset

/* shape b004:01E00460, 32 insns, 5 copies: step of a flash: first rises to alpha 0xF0 (then marks itself done rising),
   afterwards fades by 14 until it ends; keeps its colour at 0x9F/0x5F/0x5F */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 up;
    u8 pad32[4];
    s16 state;
} Obj_b004_01E00460;

static s32 func_01E00460_b004(void *arg0, Obj_b004_01E00460 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->up == 0) {
        if (o->c0[3] < 0xF0) {
            o->c0[3] = 0xF0;
        } else {
            o->up = 1;
        }
    } else if (o->c0[3] > 15) {
        o->c0[3] -= 14;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x9F, 0x5F, 0x5F);
    return 0;
}

/* shape b004:01E004E0, 30 insns: colour from the module's table at 0x01E01F80; at game step 0x50 clear 0x36; below
   step 0x46 hold the countdown at 8, else count it down to 0 */

typedef struct {
    u8 r, g, b, a;
} Col_b004_01E004E0;

typedef struct {
    u8 pad0[0x34AC];
    s16 step;
} Game_b004_01E004E0;

typedef struct {
    u8 pad0[0x28];
    Col_b004_01E004E0 col;
    u8 pad2C[6];
    s16 count;
    u8 pad34[2];
    s16 f36;
} Fx_b004_01E004E0;

extern Col_b004_01E004E0 D_01E01F80_b004;

static s32 func_01E004E0_b004(Game_b004_01E004E0 *g, Fx_b004_01E004E0 *o) {
    o->col = D_01E01F80_b004;
    if (g->step == 0x50) {
        o->f36 = 0;
    }
    if (g->step < 0x46) {
        o->count = 8;
    } else if (o->count != 0) {
        o->count--;
    }
    return 0;
}

/* shape b004:01E00560, 83 insns: a purple mote (size 9) drifting 20 a tick along its two angles (sine table at ctx+0x34E0): in by 9 up to 0x60 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[2];
    s16 h2;
    s16 h4;
    u8 pad6[2];
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
} Glow_b004_01E00560;

typedef struct {
    u8 pad[0x34E0];
    u8 sin[1];
} Game_b004_01E00560;

static s32 func_01E00560_b004(Game_b004_01E00560 *g, Glow_b004_01E00560 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    o->f38 = 9;
    func_001076F0(o->col, 0x3F, 0, 0x6F);
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 20.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 20.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 20.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b004:01E006B0, 56 insns: a pink rising ring: grows by 4 up to 10, rises 2 a frame from 15 and ends past 180;
   fades both alphas by 32 from height 80 */

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[2];
    s16 size;
    u8 pad8[0x20];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[6];
    s16 state;
} Obj_b004_01E006B0;

static s32 func_01E006B0_b004(void *arg0, Obj_b004_01E006B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->size < 0xA) {
        o->size += 4;
    }
    o->y += 2;
    func_001076F0(o->c0, 0xFF, 0xF0, 0xFF);
    if (o->y > 0xB4) {
        o->state = 0;
    }
    if (o->state == 1) {
        o->y = 0xF;
        o->size = 0;
        o->c0[3] = 0xC0;
        o->state = 2;
    }
    if (o->y >= 0x50) {
        if (o->c0[3] > 0x20) {
            o->c0[3] -= 0x20;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x20) {
            o->c1[3] -= 0x20;
        }
    }
    return 0;
}

/* shape b004:01E00790, 150 insns: b019:01E01F60 family ember (yellow, red or orange; frame 0..3) swinging 20 on two sines (angle 90..269 offset by minus the scene value at ctx+0x349C, and 0..359), table at ctx+0x34E0; full alpha 10 ticks then down by 10 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x349C];
    s16 val;
    u8 pad349E[0x34E0 - 0x349E];
    u8 tab[1];
} Mgr_b004_01E00790;

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
} Fx_b004_01E00790;

static s32 func_01E00790_b004(Mgr_b004_01E00790 *m, Fx_b004_01E00790 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 a;
    s16 k;

    a = -m->val;
    if (o->mode == 1) {
        o->f38 = 1;
        o->f34 = func_0019A5C8() % 4;
        k = func_0019A5C8() % 3;
        if (k == 0) {
            func_001076F0(o->col, 0xFF, 0xF0, 0);
        } else if (k == 1) {
            func_001076F0(o->col, 0xFF, 0, 0);
        } else if (k == 2) {
            func_001076F0(o->col, 0xFF, 0x80, 0);
        }
        o->f3A = func_0019A5C8() % 180 + 90;
        o->f30 = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->x = o->x + 20.0f * func_00108030(m->tab, a + o->f3A, 0);
    o->y = o->y + 20.0f * func_00108030(m->tab, o->f30, 0);
    o->z = o->z + 20.0f * func_00108030(m->tab, a + o->f3A, 1);
    return 0;
}

/* shape b004:01E009F0, 84 insns: a purple pulse: set up once at alpha 0 with frame 22 (6 before game frame 0x4F); alpha up by
   0x50 for 2 frames, then down by 10 until it ends; sub-frame up to 7, frame down by one every third frame; at game frame
   0x53 the alpha drops to 0x20 and at 0x54 it ends */

typedef struct {
    u8 pad0[0x34AC];
    s16 frame;
} Game_b004_01E009F0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b004_01E009F0;

static s32 func_01E009F0_b004(Game_b004_01E009F0 *g, Obj_b004_01E009F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x9F, 0, 0x3F);
    if (o->state == 1) {
        o->c0[3] = 0;
        o->sub = 0;
        if (g->frame < 0x4F) {
            o->h38 = 6;
        } else {
            o->h38 = 0x16;
        }
        o->state = 2;
    }
    if (o->t < 2) {
        o->c0[3] += 0x50;
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->sub < 7) {
        o->sub++;
    }
    if (o->t % 3 == 1) {
        if (o->h38 != 0) {
            o->h38--;
        }
    }
    o->t++;
    if (g->frame == 0x53) {
        o->c0[3] = 0x20;
    }
    if (g->frame == 0x54) {
        o->state = 0;
    }
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00B40_b004(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

/* shape b004:01E00C10, 9 insns: asks func_001F6160 for a pair of ints and returns the second as a float */

static f32 func_01E00C10_b004(s32 arg0) {
    extern void func_001F6160(s32, s32 *);
    s32 v[4];

    func_001F6160(arg0, v);
    return v[1];
}

/* shape b004:01E00C40 (b004), 412 insns, 1 copy: b004 scene manager (b053:01E010F0 form): with a scene id (>= 0) it
   clears the scene, resets the sine table, keeps the id, sets the 130-frame countdown, takes four model handles and
   texture 15; otherwise it seeds both 10-point trails at frame 0 and steps them, runs the module step and every live
   node update (the b004:01E00460, b004:01E004E0 and b004:01E00560 steps written out in place), draws every live node
   (a flat flash, or once or twice by its drawer), counts down and returns 1 / 4 / 2 / 8 from the frame */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x16];
    s32 (*fn)();
    u8 col[4];
    u8 pad2C[4];
    s16 up;
    s16 count;
    u8 pad34[2];
    s16 used;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Fx_b004_01E00C40;

typedef struct {
    u8 pad0[0xFC];
    s32 tex;
    Fx_b004_01E00C40 fx[200];
    Vec_b004_01E00B40 pts[10];
    Vec_b004_01E00B40 pts2[10];
    u8 pad3440[0x10];
    s32 count;
    u8 pad3454[8];
    s32 ot;
    u8 pad3460[0x34];
    s16 model[4];
    u8 pad349C[0xE];
    s16 id;
    s16 t;
    u8 pad34AE[0x32];
    u8 trig[0x170];
} Scene_b004_01E00C40;

static s32 func_01E00C40_b004(s32 arg0, s32 id) {
    Scene_b004_01E00C40 *g = (Scene_b004_01E00C40 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_01E00080_b004();
    extern void b004_01E013F0();
    extern void b004_01E01860();
    extern void b004_01E01A00();
    extern void b004_01E01DA0();
    extern Col_b004_01E004E0 D_01E01F80_b004;
    s32 j;
    Vec4f p;
    Vec4f p2;
    u8 buf[0x90];
    s32 i;
    Vec_b004_01E00B40 *q;

    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3650);
        func_00107C10(g->trig);
        g->id = id;
        g->count = 130;
        g->model[0] = func_001F5560(func_001F53A0(), 0x26, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x25, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x45, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x4C, 0);
        g->tex = func_00202BF0(4, 15);
        return 0;
    }
    if (g->t == 0) {
        q = g->pts;
        func_001F5620(func_001F53A0(), g->model[0], &p);
        for (i = 0; i < 10; i++, q++) {
            q->x = p.x;
            q->y = p.y;
            q->z = p.z;
        }
    }
    if (g->t == 0) {
        q = g->pts2;
        func_001F5620(func_001F53A0(), g->model[1], &p2);
        for (i = 0; i < 10; i++, q++) {
            q->x = p2.x;
            q->y = p2.y;
            q->z = p2.z;
        }
    }
    func_01E00B40_b004(&g->pts[9], 10, g->model[0]);
    func_01E00B40_b004(&g->pts2[9], 10, g->model[1]);
    func_01E00080_b004(g, 0);
    for (j = 0; j < 200; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == (s32 (*)())func_01E00460_b004) {
                if (g->fx[j].up == 0) {
                    if (g->fx[j].col[3] < 0xF0) {
                        g->fx[j].col[3] = 0xF0;
                    } else {
                        g->fx[j].up = 1;
                    }
                } else if (g->fx[j].col[3] > 15) {
                    g->fx[j].col[3] -= 14;
                } else {
                    g->fx[j].used = 0;
                }
                func_001076F0(g->fx[j].col, 0x9F, 0x5F, 0x5F);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E004E0_b004) {
                *(Col_b004_01E004E0 *)g->fx[j].col = D_01E01F80_b004;
                if (g->t == 0x50) {
                    g->fx[j].used = 0;
                }
                if (g->t < 0x46) {
                    g->fx[j].count = 8;
                } else if (g->fx[j].count != 0) {
                    g->fx[j].count--;
                }
            }
            if (g->fx[j].fn == (s32 (*)())func_01E00560_b004) {
                g->fx[j].f38 = 9;
                func_001076F0(g->fx[j].col, 0x3F, 0, 0x6F);
                if (g->fx[j].count < 10) {
                    if (g->fx[j].col[3] < 0x60) {
                        g->fx[j].col[3] += 9;
                    }
                } else if (g->fx[j].col[3] > 0x10) {
                    g->fx[j].col[3] -= 10;
                } else {
                    g->fx[j].used = 0;
                }
                g->fx[j].count++;
                g->fx[j].h8 = func_001A22C0(g->fx[j].h8 + 20.0f * func_00108030(g->trig, g->fx[j].ang, 0));
                g->fx[j].hA = func_001A22C0(g->fx[j].hA + 20.0f * func_00108030(g->trig, g->fx[j].up, 1));
                g->fx[j].hC = func_001A22C0(g->fx[j].hC + 20.0f * func_00108030(g->trig, g->fx[j].ang, 1));
            }
            if (g->fx[j].fn == (s32 (*)())func_01E006B0_b004) {
                func_01E006B0_b004(g, (Obj_b004_01E006B0 *)&g->fx[j]);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E00790_b004) {
                func_01E00790_b004((Mgr_b004_01E00790 *)g, (Fx_b004_01E00790 *)&g->fx[j]);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E009F0_b004) {
                func_01E009F0_b004((Game_b004_01E009F0 *)g, (Obj_b004_01E009F0 *)&g->fx[j]);
            }
        }
    }
    for (j = 0; j < 200; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == (s32 (*)())func_01E00460_b004) {
                s32 ot = g->ot;
                func_00107990(buf, g->fx[j].col, 0);
                func_001092E0(buf, 0);
                func_001094F0(buf);
                func_002075F0(buf, ot, 0);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E004E0_b004) {
                b004_01E013F0(g, &g->fx[j], buf, 0);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E00560_b004) {
                b004_01E01860(g, &g->fx[j], buf, 0);
                b004_01E01860(g, &g->fx[j], buf, 1);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E006B0_b004) {
                b004_01E01A00(g, &g->fx[j], buf, 0);
                b004_01E01A00(g, &g->fx[j], buf, 1);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E00790_b004) {
                b004_01E01860(g, &g->fx[j], buf, 0);
                b004_01E01860(g, &g->fx[j], buf, 1);
            }
            if (g->fx[j].fn == (s32 (*)())func_01E009F0_b004) {
                b004_01E01DA0(g, &g->fx[j], buf, 0);
                b004_01E01DA0(g, &g->fx[j], buf, 1);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->t == 69) {
        return 1;
    }
    if (g->t == 89) {
        return 4;
    }
    if (g->t == 79) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b004:01E012B0, 80 insns: c035:01E01150 family: take the first free glow slot of 200 (0x40 bytes each, at ctx+0x100), clear it, give it the scene colour twice, position, turns, two angles and both arguments; returns 1 when it got one */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    u8 pad32[4];
    s16 used;
    u8 pad38[2];
    s16 ang;
    u8 pad3C[4];
} Glow_b004_01E012B0;

typedef struct {
    u8 pad0[0x80];
    u8 pos[0x20];
    s32 rot[3];
    u8 padAC[0x100 - 0xAC];
    Glow_b004_01E012B0 slot[200];
    u8 padEnd[0x3454 - 0x100 - 200 * 0x40];
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 pad3458[0x48];
    s16 ang;
    u8 pad34A2[6];
    s16 h30;
} Ctx_b004_01E012B0;

static s32 func_01E012B0_b004(Ctx_b004_01E012B0 *ctx, s32 arg1, s32 arg2) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Glow_b004_01E012B0 *s;

    s = NULL;
    for (i = 0; i < 200; i++) {
        if (ctx->slot[i].used == 0) {
            func_00195108(&ctx->slot[i], 0x40);
            ctx->slot[i].used = 1;
            s = &ctx->slot[i];
            i = 200;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, ctx->r, ctx->g, ctx->b);
        s->col[3] = ctx->a;
        func_001076F0(s->col2, ctx->r, ctx->g, ctx->b);
        s->col2[3] = ctx->a;
        func_00106AB0(s, ctx->pos, 0);
        s->w10 = ctx->rot[0];
        s->w14 = ctx->rot[1];
        s->w18 = ctx->rot[2];
        s->ang = ctx->ang;
        s->h30 = ctx->h30;
        s->w20 = arg2;
        s->w24 = arg1;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b004", func_01E013F0_b004);

/* shape b004:01E01860, 103 insns: c035:01E013A0 family sprite draw in two passes: with lit 0 it sets the material (texture id 0x9B at frame +0x34, colour, scene texture) and returns; otherwise it places a size x size quad at position + speed/10 with the object's turn */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b004_01E01860;

typedef struct {
    u8 pad0[0xfc];
    s32 tex;
} Scene_b004_01E01860;

static void func_01E01860_b004(Scene_b004_01E01860 *g, Fx_b004_01E01860 *o, void *p, s32 lit) {
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
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x9b, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    func_00108EF0(m, 0, rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    func_00108F90(quad, p, m, v);
}

/* shape b004:01E01A00, 229 insns: b414:01E04810's hanging quad in two passes (b004:01E01860 style): with lit 0 it sets
   up the packet (rect 0x9C at frame +0x34, colours 0x28 top and 0x2C bottom, scene texture 0xFC) and returns; otherwise
   it builds the scene matrix (0x40) from the scene point 0x3440 and the anim's rotation, and draws one quad 1 wide at
   the anim's s16 point hanging 0x6 down, heights kept within 0..200, depth in 0x3484, into 0x345C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b004_01E01A00;

typedef struct {
    Rgbaq_b004_01E01A00 c;
    u64 st;
    u64 xyz;
} Vtx_b004_01E01A00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b004_01E01A00 v[4];
} Pkt_b004_01E01A00;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 col2[4];
    u8 pad30[4];
    s16 h34;
} Anim_b004_01E01A00;

typedef struct {
    u8 pad00[0x40];
    u8 m[0x40];
    u8 pad80[0x7C];
    s32 tex;
    u8 pad100[0x3300 - 0x100];
    u8 cam[0x140];
    Vec4f point;
    u8 pad3450[0xC];
    s32 ot;
    u8 pad3460[0x24];
    f32 depth;
} Scene_b004_01E01A00;

static void func_01E01A00_b004(Scene_b004_01E01A00 *g, Anim_b004_01E01A00 *an, Pkt_b004_01E01A00 *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b004_01E01A00 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00107130(void *, void *, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 m[16];
    f32 v[4];
    f32 rm[4];

    if (lit == 0) {
        func_00106080(rm, 0x9C, an->h34, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_0020EB40(g->m);
    func_00107130(g->cam, v, 1);
    func_0020C940(m, 0, an->rot, &g->point);
    func_0020BC00(g->m, m);
    q[0].x = an->x;
    q[0].y = an->y;
    q[0].z = an->z;
    q[1] = q[0];
    q[1].x += 1.0f;
    q[2].x = an->x;
    q[2].y = an->y;
    q[2].z = an->z;
    q[2].y -= an->h6;
    q[3] = q[2];
    q[3].x += 1.0f;
    if (q[0].y > 200.0f) {
        q[0].y = 200.0f;
    }
    if (q[1].y > 200.0f) {
        q[1].y = 200.0f;
    }
    if (q[2].y > 200.0f) {
        q[2].y = 200.0f;
    }
    if (q[3].y > 200.0f) {
        q[3].y = 200.0f;
    }
    if (q[0].y < 0.0f) {
        q[0].y = 0.0f;
    }
    if (q[1].y < 0.0f) {
        q[1].y = 0.0f;
    }
    if (q[2].y < 0.0f) {
        q[2].y = 0.0f;
    }
    if (q[3].y < 0.0f) {
        q[3].y = 0.0f;
    }
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

/* shape b004:01E01DA0, 89 insns: draws a sprite: mode 0 builds the packet (texture page 0x99 frame from the object, its colour,
   the scene texture); other modes turn it at random, place it at the object's point, make a square of its size and queue it
   at its depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 pad2C[8];
    s16 sub;
    u8 pad36[2];
    s16 size;
} Obj_b004_01E01DA0;

typedef struct {
    u8 pad0[0xFC];
    void *tex;
    u8 pad100[0x345C - 0x100];
    s32 ot;
    u8 pad3460[0x24];
    f32 depth;
} Game_b004_01E01DA0;

static void func_01E01DA0_b004(Game_b004_01E01DA0 *g, Obj_b004_01E01DA0 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    s16 rect[8];
    f32 m[16];
    s32 rot[4];
    f32 s;

    func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0x99, o->sub, rect);
        func_00109270(p, 0, 0);
        func_00107790(p, o->c0, 0);
        func_00108500(p, rect, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_00205C40((s32)rot);
        pos.x = o->x;
        pos.y = o->y;
        pos.z = o->z;
        func_00108EF0(m, NULL, rot, &pos);
        s = o->size;
        func_00108CE0(quad, s, s);
        if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
            func_00109380(p, 0);
            func_002075F0(p, g->ot, (u32)g->depth);
        }
    }
}
