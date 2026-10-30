#include "common.h"

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

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
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E00080_b058(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E00260_b058);

/* shape b058:01E00B40, 134 insns: b194:01E00C60 with colour 0x2F/0x20/0x2F and the sine table at g+0x3560 */

typedef struct {
    u8 pad0[0x3560];
    u8 trig[1];
} World_b058_01E00B40;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b058_01E00B40;

static s32 func_01E00B40_b058(World_b058_01E00B40 *w, Wisp_b058_01E00B40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x2F, 0x20, 0x2F);
    if (o->state == 1) {
        o->h38 = 0;
        o->a3A = func_0019A5C8() % 360;
        o->frame = 0;
        o->a30 = func_0019A5C8() % 30 - 15;
        o->state = 2;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->h38 < 0x12) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b058:01E00D60, 117 insns: a dark smoke puff (size 2 growing to 25, random frame 0..6, random heading, tilt -30..29) swept 50 a tick along its heading and 4 up/down by the tilt (sine table ctx+0x3560): in by 5 up to 0x60 for 20 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
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
} Glow_b058_01E00D60;

typedef struct {
    u8 pad[0x3560];
    u8 sin[1];
} Game_b058_01E00D60;

static s32 func_01E00D60_b058(Game_b058_01E00D60 *g, Glow_b058_01E00D60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->col, 0x28, 0x28, 0x28);
    if (o->mode == 1) {
        o->f38 = 2;
        o->ang = func_0019A5C8() % 360;
        o->kind = func_0019A5C8() % 7;
        o->h30 = func_0019A5C8() % 60 - 30;
        o->mode = 2;
    }
    if (o->tick < 20) {
        if (o->col[3] < 0x60) {
            o->col[3] += 5;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 25) {
        o->f38++;
    }
    o->h8 = func_001A22C0(o->h8 + 50.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 4.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 50.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

typedef struct {
    u8 pad0000[0x3560];
    u8 tab[1];
} Mgr_b058_01E00F40;

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
} Obj_b058_01E00F40;

static s32 func_01E00F40_b058(Mgr_b058_01E00F40 *m, Obj_b058_01E00F40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x60, 0x30, 0);
    if (o->h36 == 1) {
        o->h38 = 2;
        o->h3A = func_0019A5C8() % 360;
        o->h34 = 0;
        o->h30 = func_0019A5C8() % 30 - 15;
        o->h36 = 2;
    }
    if (o->h32 < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    if (o->h32 % 3 == 1) {
        if (o->h34 < 7) {
            o->h34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y - 10.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b058:01E01120, 97 insns: an orange spark (size 1, random frame 0..3) at a random angle drifting 16 a tick along it and bobbing 20 x sine of a phase that turns 6 a tick (sine table ctx+0x3560): alpha 0x80 for 10 ticks, then out by 10 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[8];
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
} Glow_b058_01E01120;

typedef struct {
    u8 pad[0x3560];
    u8 sin[1];
} Game_b058_01E01120;

static s32 func_01E01120_b058(Game_b058_01E01120 *g, Glow_b058_01E01120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->mode == 1) {
        o->f38 = 1;
        o->kind = func_0019A5C8() % 4;
        func_0019A5C8();
        func_001076F0(o->col, 0x80, 0x40, 0);
        o->h30 = 0;
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
    o->h30 += 6;
    o->h8 = func_001A22C0(o->h8 + 16.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(20.0f * func_00108030(g->sin, o->h30, 0));
    o->hC = func_001A22C0(o->hC + 16.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b058:01E012B0, 210 insns: an orange (0x60, 0x30, 0) trail seed: on start it turns rot[1] to the model angle read
   through func_001F6160 less 0x4000 plus a random -0x6000..0x5FFF, then lays trail h30 (ctx+0x3100 + 0x80 h30, 8
   points) out 20 apart in x with z wandering by -30..29 from the previous point; alpha up by 30 to 0xF0 for 28 ticks,
   then down by 3 */

typedef struct {
    u8 pad0[0x3100];
    Vec4f tr[7][8];
} Ctx_b058_01E012B0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
} Obj_b058_01E012B0;

static s32 func_01E012B0_b058(Ctx_b058_01E012B0 *g, Obj_b058_01E012B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 v[4];
    Vec4f *p;
    Vec4f *q;
    s16 i;
    s32 a;

    func_001076F0(o->col, 0x60, 0x30, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), v);
        o->rot[1] = func_001A22C0((f32)v[1]);
        o->rot[1] -= 0x4000;
        if (o->h30 == 0) {
            o->rot[1] += 0;
        } else if (o->h30 == 0) {
            o->rot[1] += 0x1000;
        } else if (o->h30 == 0) {
            o->rot[1] -= 0x1000;
        } else {
            o->rot[1] += func_0019A5C8() % 0xC000 - 0x6000;
        }
        o->h34 = 0;
        o->h38 = 60;
        if (o->h30 == 0) {
            p = g->tr[0];
        }
        if (o->h30 == 1) {
            p = g->tr[1];
        }
        if (o->h30 == 2) {
            p = g->tr[2];
        }
        if (o->h30 == 3) {
            p = g->tr[3];
        }
        if (o->h30 == 4) {
            p = g->tr[4];
        }
        if (o->h30 == 5) {
            p = g->tr[5];
        }
        if (o->h30 == 6) {
            p = g->tr[6];
        }
        for (i = 0, a = 0; i < 8; i++) {
            p->x = a;
            a += 20;
            p++;
        }
        if (o->h30 == 0) {
            q = p = g->tr[0];
        }
        if (o->h30 == 1) {
            q = p = g->tr[1];
        }
        if (o->h30 == 2) {
            q = p = g->tr[2];
        }
        if (o->h30 == 3) {
            q = p = g->tr[3];
        }
        if (o->h30 == 4) {
            q = p = g->tr[4];
        }
        if (o->h30 == 5) {
            q = p = g->tr[5];
        }
        if (o->h30 == 6) {
            q = p = g->tr[6];
        }
        for (i = 0; i < 8; i++) {
            if (i == 0) {
                p->z = 0.0f;
            } else {
                p->z = q->z + func_0019A5C8() % 60 - 30.0f;
            }
            if (i == 0) {
                p++;
            } else {
                p++;
                q++;
            }
        }
        o->state = 2;
    }
    if (o->t < 28) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 30;
        }
    } else if (o->col[3] > 4) {
        o->col[3] -= 3;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b058:01E01600, 103 insns: b027:01E00F90 family: an olive flame (size 15 shrinking to 0) at a random angle, or (scene value 130 on) within 60 degrees of 0 or of 180 depending on the scene handle being under 10: in by 15 up to 0x60 for 8 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b058_01E01600;

typedef struct {
    u8 pad[0x355C];
    s16 val;
} Game_b058_01E01600;

static s32 func_01E01600_b058(Game_b058_01E01600 *g, Glow_b058_01E01600 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);

    func_001076F0(o->col, 0x40, 0x40, 0x1F);
    if (o->mode == 1) {
        o->f38 = 15;
        if (func_001F53A0() < 10) {
            if (g->val < 130) {
                o->ang = func_0019A5C8() % 360;
            } else {
                o->ang = func_0019A5C8() % 120 - 60;
            }
        } else if (g->val < 130) {
            o->ang = func_0019A5C8() % 360;
        } else {
            o->ang = func_0019A5C8() % 120 + 120;
        }
        o->kind = 0;
        o->col[3] = 0;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 15;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 != 0) {
        o->f38--;
    }
    return 0;
}

/* shape b058:01E017A0, 53 insns: volume fade by game state (b003:01E02330 family): state at 0x3500 limit 0x19,
   down 10 to 0x30, up 7 capped at 0x80 */

typedef struct {
    u8 pad[0x3500];
    s32 state;
} Game_b058_01E017A0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b058_01E017A0;

static s32 func_01E017A0_b058(Game_b058_01E017A0 *g, Fade_b058_01E017A0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x19) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 7;
        } else {
            o->vol = 0x80;
        }
        if (o->vol > 0x80) {
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

/* shape b058:01E01880 (b058), 341 insns, 1 copy: b058 scene manager (b286:01E01520 form): with a scene id (>= 0) it
   clears the scene, resets the camera, keeps the id, sets the 450-frame countdown, takes a model handle and loads
   textures 2, 14 and 15; otherwise it takes four more model handles at frame 145, runs the module step and every live
   node update, draws every live node (twice by its callback, or one KEMU_PAINT_1 square), grows the scene scale by
   0.01 up to 0.5 after frame 20, counts down and returns 1 / 4 / 2 at frames 351 / 420 / 391, 6 from 362 to 385, 8
   once the countdown runs out */

typedef struct Fx_b058_01E01880 {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 used;
    u8 pad38[0x8];
} Fx_b058_01E01880;

typedef struct Spr_b058_01E01880 {
    s32 texture;
    s32 tex;
    s32 c;
    s32 mode;
} Spr_b058_01E01880;

typedef struct Scene_b058_01E01880 {
    u8 pad0[0xC0];
    f32 sx, sy, sz;
    u8 padCC[4];
    s32 tex[16];
    u8 pad110[0x284 - 0x110];
    Fx_b058_01E01880 fx[180];
    u8 pad2F84[0x3500 - 0x2F84];
    s32 count;
    u8 pad3504[8];
    s32 ot;
    u8 pad3510[0x38];
    s16 model[4];
    u8 pad3550[0xA];
    s16 id;
    s16 timer;
    u8 pad355E[2];
    u8 cam[0x170];
} Scene_b058_01E01880;

static s32 func_01E01880_b058(s32 arg0, s32 id) {
    Scene_b058_01E01880 *g = (Scene_b058_01E01880 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_01E00260_b058();
    extern s32 func_01E00B40_b058();
    extern s32 func_01E00D60_b058();
    extern s32 func_01E00F40_b058();
    extern s32 func_01E01120_b058();
    extern s32 func_01E012B0_b058();
    extern s32 func_01E01600_b058();
    extern s32 func_01E017A0_b058();
    extern void b058_01E01F00();
    extern void b058_01E020A0();
    extern void b058_01E02240();
    extern void b058_01E023F0();
    s32 j;
    s32 n;
    Vec4f v;
    Spr_b058_01E01880 s;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x36D0);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 450;
        g->sx = 0.0f;
        g->sy = 0.0f;
        g->sz = 0.0f;
        g->model[0] = func_001F5560(func_001F53A0(), 0x11, 1);
        for (i = 2; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    if (g->timer == 145) {
        g->model[0] = func_001F5560(func_001F53A0(), 0x1C, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x2E, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x36, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0xC, 0);
    }
    func_01E00260_b058(g, 0);
    for (j = 0; j < 180; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == func_01E00B40_b058) {
                func_01E00B40_b058(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00D60_b058) {
                func_01E00D60_b058(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00F40_b058) {
                func_01E00F40_b058(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01120_b058) {
                func_01E01120_b058(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E012B0_b058) {
                func_01E012B0_b058(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01600_b058) {
                func_01E01600_b058(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E017A0_b058) {
                func_01E017A0_b058(g, &g->fx[j]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 180; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E00B40_b058) {
                b058_01E01F00(g, &g->fx[i], buf, 0);
                b058_01E01F00(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00D60_b058) {
                b058_01E020A0(g, &g->fx[i], buf, 0);
                b058_01E020A0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00F40_b058) {
                b058_01E02240(g, &g->fx[i], buf, 0);
                b058_01E02240(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01120_b058) {
                s.texture = g->tex[15];
                s.c = 0;
                s.tex = 0x9B;
                s.mode = 0;
                func_01E00080_b058(g->ot, (Obj_b058_01E00080 *)&g->fx[i], (Spr_b058_01E00080 *)&s);
            }
            if (g->fx[i].fn == func_01E012B0_b058) {
                b058_01E023F0(g, &g->fx[i], buf, 0);
                b058_01E023F0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01600_b058) {
                b058_01E01F00(g, &g->fx[i], buf, 0);
                b058_01E01F00(g, &g->fx[i], buf, 1);
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
    if (g->timer == 351) {
        return 1;
    }
    if (g->timer == 420) {
        return 4;
    }
    if (g->timer == 391) {
        return 2;
    }
    if (g->timer > 361 && g->timer < 386) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b058:01E01DE0, 72 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3558 and the two arguments; returns 1 if a
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
} Slot_b058_01E01DE0;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b058_01E01DE0 s[180];
    u8 pad2F84[0x580];
    u8 r, g, b, a;
    u8 pad3508[0x50];
    s16 v;
} Pool_b058_01E01DE0;

static s32 func_01E01DE0_b058(Pool_b058_01E01DE0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b058_01E01DE0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 180; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 180;
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

static void func_01E01F00_b058(Mgr_b058_01E01F00 *m, Obj_b058_01E01F00 *o, void *p, s32 flag) {
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

static void func_01E020A0_b058(u8 *ctx, Obj_b053_01E022F0 *o, void *pkt, s32 mode) {
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

/* shape b058:01E02240, 107 insns, 2 copies: one textured square of an object (b053:01E022F0 with a 0.1 scale); mode 0 only
   sets up the packet's texture, otherwise position = pos + vel / 10, camera-facing, size from the object, drawn
   via func_00108F90. */

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
} Obj_b058_01E02240;

static void func_01E02240_b058(u8 *ctx, Obj_b058_01E02240 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
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
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00108EF0(m, &scale, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

INCLUDE_ASM("asm/nonmatchings/mod/b058", func_01E023F0_b058);
