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

static void func_01E00080_b378(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */

/* shape b378:01E00260, 222 insns: the b378 module's event step: red scene colour, counts ticks (0x3BFE); saves joint
   0x3BE8 at 150 and joints 0x3BEC/0x3BEE at 160 (0x3B50.. points); spawns b378:01E01B80 at 152; at 60 spawns
   b378:01E00970 at both hand joints (0x3BE8/0x3BEA, slot 0/1); from 60 to 68 spawns 4 b378:01E01530 at each hand; at
   280 spawns 30 b378:01E01910 at each of the two points 0xD0/0xE0; the scale (0x110..) starts at 0.03 at 60 and grows
   by 0.01 up to 0.2 (middle 0.05); the scene angle 0x3BF6 turns by -8 */

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0xD0 - 0x90];
    Vec4f pt[2];
    u8 padF0[0x20];
    f32 sx, sy, sz;
    u8 pad11C[0x3B50 - 0x11C];
    Vec4f save[3];
    u8 pad3B80[0x3BA4 - 0x3B80];
    u8 col[4];
    u8 pad3BA8[0x3BE8 - 0x3BA8];
    s16 id[4];
    u8 pad3BF0[0x3BF6 - 0x3BF0];
    s16 ang;
    u8 pad3BF8[2];
    s16 slot;
    u8 pad3BFC[2];
    s16 count;
} Ctx_b378_01E00260;


#pragma optimization_level 3

static void func_01E00260_b378(Ctx_b378_01E00260 *g) {
    extern s32 b378_01E00970(void);
    extern s32 b378_01E01530(void);
    extern s32 b378_01E01910(void);
    extern s32 b378_01E01B80(void);
    extern void b378_01E02320(Ctx_b378_01E00260 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 v[4];
    s32 i;
    s32 k;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count == 150) {
        func_001F5620(func_001F53A0(), g->id[0], &g->save[0]);
    }
    if (g->count == 160) {
        func_001F5620(func_001F53A0(), g->id[2], &g->save[1]);
    }
    if (g->count == 160) {
        func_001F5620(func_001F53A0(), g->id[3], &g->save[2]);
    }
    if (g->count == 152) {
        b378_01E02320(g, b378_01E01B80, 0);
    }
    if (g->count == 60) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->id[i], v);
            g->pos.x = v[0];
            g->pos.y = v[1];
            g->pos.z = v[2];
            g->slot = i;
            b378_01E02320(g, b378_01E00970, 0);
        }
    }
    if (g->count == 60 || g->count == 61 || g->count == 62 || g->count == 63 || g->count == 64 ||
        g->count == 65 || g->count == 66 || g->count == 67 || g->count == 68) {
        for (i = 0; i < 2; i++) {
            func_001F5620(func_001F53A0(), g->id[i], v);
            g->pos.x = v[0];
            g->pos.y = v[1];
            g->pos.z = v[2];
            for (k = 0; k < 4; k++) {
                b378_01E02320(g, b378_01E01530, 0);
            }
        }
    }
    if (g->count == 280) {
        for (i = 0; i < 2; i++) {
            g->pos.x = g->pt[i].x;
            g->pos.y = g->pt[i].y;
            g->pos.z = g->pt[i].z;
            for (k = 0; k < 30; k++) {
                b378_01E02320(g, b378_01E01910, 0);
            }
        }
    }
    if (g->count == 60) {
        g->sx = 0.03f;
        g->sy = 0.03f;
        g->sz = 0.03f;
    }
    if (g->count > 60) {
        if (g->sx < 0.2f) {
            g->sx += 0.01f;
            g->sy = 0.05f;
            g->sz += 0.01f;
        }
    }
    g->ang -= 8;
    if (g->ang < -359) {
        g->ang %= 360;
    }
}
#pragma optimization_level reset

/* shape b378:01E005E0, 134 insns: b019:01E01F60 with its sine table at ctx+0x3C04 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3C04];
    u8 tab[1];
} Mgr_b378_01E005E0;

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
} Fx_b378_01E005E0;

static s32 func_01E005E0_b378(Mgr_b378_01E005E0 *m, Fx_b378_01E005E0 *o) {
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

/* shape b378:01E00800, 92 insns: a dark swirl: frame 90, random angle, sinking to -30 by 4; alpha up by 8 to 0xA0 for 20 frames,
   then while the game state is below 20 down by 13 until it ends; past game frame 0x118 it spins up by 0x30 a frame (to 0x600)
   and regrows its frame to 90 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 state;
    u8 pad3BA4[0x5A];
    s16 frame;
} Game_b378_01E00800;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b378_01E00800;

static s32 func_01E00800_b378(Game_b378_01E00800 *g, Obj_b378_01E00800 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x1F, 0x1F, 0x1F);
    if (o->state == 1) {
        o->h38 = 0x5A;
        o->ang = func_0019A5C8() % 360;
        o->h34 = 0;
        o->y = 0;
        o->state = 2;
    }
    if (o->t < 0x14) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 8;
        }
    } else if (g->state < 0x14) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    if (g->frame > 0x118) {
        if (o->ang < 0x600) {
            o->ang += 0x30;
        }
    }
    if (g->frame > 0x118) {
        if (o->h38 < 0x5A) {
            o->h38 += 4;
        } else {
            o->h38 = 0x5A;
        }
    }
    if (o->y > -0x1E) {
        o->y -= 4;
    }
    o->t++;
    o->ang++;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E00970_b378);

/* shape b378:01E01230, 95 insns: a yellow camera-facing glow: turned by the camera's side, size 90 growing by 8 up to 160;
   alpha up by 0x40 for 2 frames, then down by 5 until it ends; fades faster (by 13) once the scene timer drops under 15 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 timer;
} Scene_b378_01E01230;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 size;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b378_01E01230;

static s32 func_01E01230_b378(Scene_b378_01E01230 *g, Obj_b378_01E01230 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 ang[4];

    func_001076F0(o->c0, 0x20, 0x20, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), ang);
        if (func_001A22C0(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->sub = 0;
        o->size = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    if (g->timer < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b378:01E013B0, 95 insns: a red camera-facing glow (b378:01E01230 shape): turned by the camera's side, size 90 growing by 8 up to 160;
   alpha up by 0x40 for 2 frames, then down by 5 until it ends; fades faster (by 13) once the scene timer drops under 15 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 timer;
} Scene_b378_01E013B0;

typedef struct {
    u8 pad0[0x10];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 size;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b378_01E013B0;

static s32 func_01E013B0_b378(Scene_b378_01E013B0 *g, Obj_b378_01E013B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern s32 func_001A22C0(f32);
    s32 ang[4];

    func_001076F0(o->c0, 0x40, 0, 0);
    if (o->state == 1) {
        func_001F6160(func_001F53A0(), ang);
        if (func_001A22C0(ang[1] / 180.0f) != 0) {
            o->rot[0] = -0x4000;
        } else {
            o->rot[0] = -0xC000;
        }
        o->rot[1] = 0;
        o->rot[2] = 0x3800;
        o->sub = 0;
        o->size = 0x5A;
        o->state = 2;
        o->c0[3] = 0;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 6) {
        o->c0[3] -= 5;
    } else {
        o->state = 0;
    }
    o->h38 = 0x32;
    o->t++;
    if (o->size < 0xA0) {
        o->size += 8;
    }
    if (g->timer < 0xF) {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
    }
    return 0;
}

/* shape b378:01E01530, 87 insns: an orange rising spark (b192:01E015D0 family): frame 4 rising by 2, random tilt -0x7000..-0x1001,
   y turn and sub-frame 0..6; alpha up by 0x50 to 0xA0 for 2 frames, then down by 13 past frame 8, and also by 15 while the
   game state is below 10 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 state;
} Game_b378_01E01530;

typedef struct {
    u8 pad0[0x14];
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b378_01E01530;

static s32 func_01E01530_b378(Game_b378_01E01530 *g, Obj_b378_01E01530 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 4;
        o->rot2 = func_0019A5C8() % 24576 - 0x7000;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 7;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else {
        if (o->h38 > 8) {
            if (o->c0[3] > 0xE) {
                o->c0[3] -= 0xD;
            } else {
                o->state = 0;
            }
        }
        if (g->state < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    func_001076F0(o->c0, 0xFF, 0x80, 0);
    o->t++;
    o->h38 += 2;
    return 0;
}

/* shape b378:01E01690, 158 insns: an amber rider on scene point o->kind: copies that point's turn (ctx+0xB0, spinning 0x400) and, before scene count 100 (and for 4 ticks after 256), its position (ctx+0xD0) as shorts; between 100 and 255 reads the tracked points (ctx+0x3BEC/E); alpha up by 80 to 0xA0 for 2 ticks, then down by 13 once grown past 8 and by 15 once the scene timer is under 10; grows to 20 */

/* OVL_WARM */

typedef struct {
    s32 v[4];
} V4i_b378_01E01690;

typedef struct {
    u8 pad0[0xB0];
    V4i_b378_01E01690 rot[2];
    Vec4f pos[2];
    u8 padF0[0x3BA0 - 0xF0];
    s32 timer;
    u8 pad3BA4[0x3BEC - 0x3BA4];
    s16 id0;
    s16 id1;
    u8 pad3BF0[0x3BFE - 0x3BF0];
    s16 count;
} Ctx_b378_01E01690;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    V4i_b378_01E01690 rot;
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 size;
} Fx_b378_01E01690;

static s32 func_01E01690_b378(Ctx_b378_01E01690 *g, Fx_b378_01E01690 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];

    if (o->mode == 1) {
        o->size = 4;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->size > 8) {
            if (o->col[3] > 14) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->timer < 10) {
            if (o->col[3] > 16) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (g->count < 100) {
        o->x = g->pos[o->kind].x;
        o->y = g->pos[o->kind].y;
        o->z = g->pos[o->kind].z;
    } else if (g->count < 256) {
        if (o->kind == 0) {
            func_001F5620(func_001F53A0(), g->id0, &v[4]);
        }
        if (o->kind == 1) {
            func_001F5620(func_001F53A0(), g->id1, &v[4]);
        }
    } else if (o->tick < 4) {
        o->x = g->pos[o->kind].x;
        o->y = g->pos[o->kind].y;
        o->z = g->pos[o->kind].z;
    }
    o->rot = g->rot[o->kind];
    o->rot.v[1] += 0x400;
    func_001076F0(o->col, 0x80, 0x40, 0);
    o->tick++;
    if (o->size < 20) {
        o->size++;
    }
    return 0;
}

/* shape b378:01E01910, 87 insns: on start 0x38 = 4, random rotation (0x18 -0x2000..0x1FFF, 0x14), variant 0..6; alpha grows
   by 0x50 (below 0xA0) for 2 ticks, then fades by 13 once 0x38 passes 0x14 and by 15 while the game counter at
   0x3BA0 is below 10; colour (0x80, 0x40, 0); 0x38 grows by 2 */

typedef struct {
    u8 pad0[0x3BA0];
    s32 count;
} Game_b378_01E01910;

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
} Fx_b378_01E01910;

static s32 func_01E01910_b378(Game_b378_01E01910 *g, Fx_b378_01E01910 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 4;
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
    o->f38 += 2;
    return 0;
}

/* shape b378:01E01A70, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x3BA0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x3BA0];
    s32 state;
} Game_b378_01E01A70;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b378_01E01A70;

static s32 func_01E01A70_b378(Game_b378_01E01A70 *g, Fade_b378_01E01A70 *o) {
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

static s32 func_01E01B30_b378(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03C00_b378;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03C08_b378;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b378:01E01B80, 98 insns: b001:01E00900 family: draws the grey bar sprite at its own alpha, which fades in by 12 up to 0x60 for 90 ticks, then out by 12 and ends */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b378_01E01B80;

typedef struct {
    Hdr_b378_01E01B80 h;
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
} Pkt_b378_01E01B80;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Obj_b378_01E01B80;

static s32 func_01E01B80_b378(s32 arg0, Obj_b378_01E01B80 *o) {
    Pkt_b378_01E01B80 p __attribute__((aligned(8)));

    ((Hdr_b378_01E01B80 *)(s32)&p)->count = 0x26;
    ((Hdr_b378_01E01B80 *)(s32)&p)->tag = 5;
    ((Hdr_b378_01E01B80 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b378_01E01B80 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
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
    if (o->tick < 90) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b378:01E01D10 (b378), 385 insns, 1 copy: b378 scene manager (b058:01E01880 form): with a scene id (>= 0) it
   clears the scene, resets the camera, keeps the id, sets the 300-frame countdown, takes four model handles and loads
   textures 10..15; otherwise it runs the module step and every live node update (B378_OBJ_MOVE_201_ is written
   out in place), draws every live node (twice by its drawer, or one KEMU_PAINT_1 square), grows the scene scale by
   0.01 up to 0.5 after frame 20, counts down and returns 1 / 4 / 2 at frames 270 / 290 / 280, 8 once the countdown
   runs out */

typedef struct Fx_b378_01E01D10 {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xE];
    s16 used;
    u8 pad38[0x8];
} Fx_b378_01E01D10;

typedef struct Spr_b378_01E01D10 {
    s32 texture;
    s32 tex;
    s32 c;
    s32 mode;
} Spr_b378_01E01D10;

typedef struct Scene_b378_01E01D10 {
    u8 pad0[0x100];
    f32 sx, sy, sz;
    u8 pad10C[0x14];
    s32 tex[16];
    u8 pad160[0x2D4 - 0x160];
    Fx_b378_01E01D10 fx[220];
    u8 pad39D4[0x3BA0 - 0x39D4];
    s32 count;
    u8 pad3BA4[8];
    s32 ot;
    u8 pad3BB0[0x3BE8 - 0x3BB0];
    s16 model[4];
    u8 pad3BF0[0xC];
    s16 id;
    s16 timer;
    u8 pad3C00[4];
    u8 cam[0x170];
} Scene_b378_01E01D10;

static s32 func_01E01D10_b378(s32 arg0, s32 id) {
    Scene_b378_01E01D10 *g = (Scene_b378_01E01D10 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_01E00260_b378();
    extern s32 func_01E005E0_b378();
    extern s32 func_01E00800_b378();
    extern s32 func_01E00970_b378();
    extern s32 func_01E01230_b378();
    extern s32 func_01E013B0_b378();
    extern s32 func_01E01530_b378();
    extern s32 func_01E01690_b378();
    extern s32 func_01E01910_b378();
    extern s32 func_01E01A70_b378();
    extern s32 func_01E01B30_b378();
    extern s32 func_01E01B80_b378();
    extern void b378_01E02440();
    extern void b378_01E02950();
    extern void b378_01E02D00();
    extern void b378_01E03080();
    extern void b378_01E03450();
    extern void b378_01E03790();
    s32 j;
    s32 n;
    Vec4f v;
    Spr_b378_01E01D10 s;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3D70);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 300;
        g->model[0] = func_001F5560(func_001F53A0(), 0x24, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x2B, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x22, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x2E, 0);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    func_01E00260_b378(g, 0);
    for (j = 0; j < 220; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn == func_01E005E0_b378) {
                func_01E005E0_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00800_b378) {
                func_01E00800_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E00970_b378) {
                func_01E00970_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01230_b378) {
                func_01E01230_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E013B0_b378) {
                func_01E013B0_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01530_b378) {
                func_01E01530_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01690_b378) {
                func_01E01690_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01910_b378) {
                func_01E01910_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01A70_b378) {
                func_01E01A70_b378(g, &g->fx[j]);
            }
            if (g->fx[j].fn == func_01E01B30_b378) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03C00_b378;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03C08_b378;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
            if (g->fx[j].fn == func_01E01B80_b378) {
                func_01E01B80_b378(g, &g->fx[j]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    v.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E005E0_b378) {
                s.texture = g->tex[2];
                s.c = 0;
                s.tex = 0x14;
                s.mode = 0;
                func_01E00080_b378(g->ot, (Obj_b058_01E00080 *)&g->fx[i], (Spr_b058_01E00080 *)&s);
            }
            if (g->fx[i].fn == func_01E00800_b378) {
                b378_01E02950(g, &g->fx[i], buf, 0);
                b378_01E02950(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00970_b378) {
                b378_01E02440(g, &g->fx[i], buf, 0);
                b378_01E02440(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01230_b378) {
                b378_01E02D00(g, &g->fx[i], buf, 0);
                b378_01E02D00(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E013B0_b378) {
                b378_01E03080(g, &g->fx[i], buf, 0);
                b378_01E03080(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01530_b378) {
                b378_01E03450(g, &g->fx[i], buf, 0);
                b378_01E03450(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01690_b378) {
                b378_01E03790(g, &g->fx[i], buf, 0);
                b378_01E03790(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01910_b378) {
                b378_01E03450(g, &g->fx[i], buf, 0);
                b378_01E03450(g, &g->fx[i], buf, 1);
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
    if (g->timer == 270) {
        return 1;
    }
    if (g->timer == 290) {
        return 4;
    }
    if (g->timer == 280) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b378:01E02320, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3BFA and the two arguments; returns 1 if a
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
} Slot_b378_01E02320;

typedef struct {
    u8 pad[0x80];
    u8 m[0x254];
    Slot_b378_01E02320 s[220];
    u8 pad39D4[0x1D0];
    u8 r, g, b, a;
    u8 pad3BA8[0x52];
    s16 v;
} Pool_b378_01E02320;

static s32 func_01E02320_b378(Pool_b378_01E02320 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b378_01E02320 *s = NULL;
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

INCLUDE_ASM("asm/nonmatchings/mod/b378", func_01E02440_b378);

/* shape b378:01E02950, 236 insns: b193:01E009B0 family upright ring: mode 0 sets up the packet (two colours, blend
   0x42); otherwise 36 quads 10 degrees apart between radius 0x38 and 0x38 + 20 (the outer edge pushed out 0x30
   along z), scale 0.1, at the object's position plus a tenth of its 0x8/0xA/0xC offset, turned by a random angle
   with x and y cleared and z plus 0x18; flat-shaded into the frame's list */

typedef struct {
    f32 x, y, z, w;
} Vec_b378_01E02950;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0xA];
    s32 spin;
    u8 pad1C[0xC];
    u8 col0[4];
    u8 col1[4];
    s16 depth;
    u8 pad32[6];
    s16 size;
} Fx_b378_01E02950;

static void func_01E02950_b378(u8 *ctx, Fx_b378_01E02950 *o, void *p, s32 mode) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b378_01E02950 quad[4];
    Vec_b378_01E02950 pos;
    Vec_b378_01E02950 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    s32 rot[4];
    s32 ot;
    s16 i;
    s16 a;

    ot = (s32)func_00207500();
    a = 0;
    if (mode == 0) {
        func_001092E0(p, 0);
        func_001094F0(p);
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
        func_00107990(p, o->col0, 1);
        func_00107990(p, o->col1, 2);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        pos.x = o->x + o->dx / 10;
        pos.y = o->y + o->dy / 10;
        pos.z = o->z + o->dz / 10;
        func_00205C40((s32)rot);
        rot[0] = 0;
        rot[1] = 0;
        rot[2] += o->spin;
        func_00108EF0(m, &scale, rot, &pos);
        for (i = 0; i < 36; i++) {
            quad[0].z = 0;
            quad[0].x = o->size * func_00108030(ctx + 0x3C04, a, 0);
            quad[0].y = o->size * func_00108030(ctx + 0x3C04, a, 1);
            quad[1].z = 0;
            quad[1].x = o->size * func_00108030(ctx + 0x3C04, a + 10, 0);
            quad[1].y = o->size * func_00108030(ctx + 0x3C04, a + 10, 1);
            quad[2].z = o->depth;
            quad[2].x = (o->size + 20) * func_00108030(ctx + 0x3C04, a, 0);
            quad[2].y = (o->size + 20) * func_00108030(ctx + 0x3C04, a, 1);
            quad[3].z = o->depth;
            quad[3].x = (o->size + 20) * func_00108030(ctx + 0x3C04, a + 10, 0);
            quad[3].y = (o->size + 20) * func_00108030(ctx + 0x3C04, a + 10, 1);
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, ot, 0);
            }
            a += 10;
        }
    }
}

/* OVL_WARM */

/* shape b378:01E02D00, 221 insns: b148:01E05240 cousin: the band scaled (size/750, 1.2 x size/250, size/250), its
   lower edge at the band's tilt (the radii clamped at tilt 160), 9 sectors 40 apart; b046:01E03F40 family dome band */

typedef struct {
    u8 pad0[0x15C];
    void *texture;
    u8 pad160[0x3BAC - 0x160];
    s32 ot;
    u8 pad3BB0[0x3BD4 - 0x3BB0];
    f32 dep;
    u8 pad3BD8[0x3C04 - 0x3BD8];
    u8 trig[1];
} Ctx_b378_01E02D00;

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
} Band_b378_01E02D00;

static void func_01E02D00_b378(Ctx_b378_01E02D00 *c, Band_b378_01E02D00 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x10];
    s32 k;
    s32 j;
    s16 a;
    s16 t;
    s16 tl;
    f32 sx;
    f32 sc;
    f32 r0;
    f32 r1;
    f32 y;
    f32 cs;
    f32 sn;

    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    sc = o->size;
    sc /= 250.0f;
    sx = sc / 3.0f;
    func_00106DD0(&scale, sx, 1.2 * sc, sc);
    func_00108EF0(m, &scale, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        if (o->tilt > 160) {
            tl = 160;
        }
        quad[0].y = 90.0f * func_00108030(c->trig, o->tilt, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 90.0f * func_00108030(c->trig, o->tilt + 40, 0);
        quad[3].y = quad[2].y;
        r0 = 90.0f * func_00108030(c->trig, tl, 1);
        r1 = 90.0f * func_00108030(c->trig, tl + 30, 1);
        a = 0;
        for (k = 0; k < 9; k++) {
            t = o->ang + a;
            cs = func_00108030(c->trig, t, 1);
            sn = func_00108030(c->trig, t, 0);
            quad[2].x = cs * r1;
            quad[2].z = sn * r1;
            quad[0].x = cs * r0;
            quad[0].z = sn * r0;
            t = o->ang + 40 + a;
            cs = func_00108030(c->trig, t, 1);
            sn = func_00108030(c->trig, t, 0);
            quad[3].x = cs * r1;
            quad[3].z = sn * r1;
            quad[1].x = cs * r0;
            quad[1].z = sn * r0;
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 40;
        }
    }
    }
}

/* OVL_WARM */

/* shape b378:01E03080, 241 insns: b378:01E02D00 with texture 0x9B, the band scaled (1.3 x size/750, 2 x size/250,
   1.3 x size/250) and each of the 9 sectors (40 apart) 20 wide */

typedef struct {
    u8 pad0[0x15C];
    void *texture;
    u8 pad160[0x3BAC - 0x160];
    s32 ot;
    u8 pad3BB0[0x3BD4 - 0x3BB0];
    f32 dep;
    u8 pad3BD8[0x3C04 - 0x3BD8];
    u8 trig[1];
} Ctx_b378_01E03080;

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
} Band_b378_01E03080;

static void func_01E03080_b378(Ctx_b378_01E03080 *c, Band_b378_01E03080 *o, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x10];
    s32 k;
    s32 j;
    s16 a;
    s16 t;
    s16 tl;
    f32 sx;
    f32 sy;

    f32 sc;
    f32 r0;
    f32 r1;
    f32 y;
    f32 cs;
    f32 sn;

    if (mode == 0) {
        func_00106080(td, 0x9B, o->page, td);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, td, 0);
        func_00208700(p, c->texture, 1);
    } else {
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    sc = o->size;
    sc /= 250.0f;
    sy = 2.0f * sc;
    func_00106DD0(&scale, 1.3 * (sc / 3.0f), sy, 1.3 * sc);
    func_00108EF0(m, &scale, o->rot, &pos);
    for (j = 0; j < 1; j++) {
        tl = o->tilt;
        if (o->tilt > 160) {
            tl = 160;
        }
        quad[0].y = 90.0f * func_00108030(c->trig, o->tilt, 0);
        quad[1].y = quad[0].y;
        quad[2].y = 90.0f * func_00108030(c->trig, o->tilt + 40, 0);
        quad[3].y = quad[2].y;
        r0 = 90.0f * func_00108030(c->trig, tl, 1);
        r1 = 90.0f * func_00108030(c->trig, tl + 30, 1);
        a = 0;
        for (k = 0; k < 9; k++) {
            t = o->ang + a;
            cs = func_00108030(c->trig, t, 1);
            sn = func_00108030(c->trig, t, 0);
            quad[2].x = cs * r1;
            quad[2].z = sn * r1;
            quad[0].x = cs * r0;
            quad[0].z = sn * r0;
            t = o->ang + 20 + a;
            cs = func_00108030(c->trig, t, 1);
            sn = func_00108030(c->trig, t, 0);
            quad[3].x = cs * r1;
            quad[3].z = sn * r1;
            quad[1].x = cs * r0;
            quad[1].z = sn * r0;
            if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
                func_002075F0(p, c->ot, (u32)c->dep);
            }
            a += 40;
        }
    }
    }
}

/* OVL_WARM */

/* shape b378:01E03450, 207 insns: b027:01E02590's ring draw for module b378: with no fourth argument it only sets up
   the draw (rect 0x9B from page 0x34, colour, texture ctx+0x15C) and returns; otherwise it builds the matrix (scale
   1/1.5/1) and draws 9 ring quads, radius 0x38 and 7 less, each spanning 1 degree step (4 for b378:01E01910 rings),
   40 apart from angle 0x3A, with the depth kept in ctx+0x3BD4 and the target ctx+0x3BAC */

typedef struct {
    f32 x, y, z, w;
} Vec_b378_01E03450;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x14];
    s32 fn;
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b378_01E03450;

typedef struct {
    u8 pad00[0x15C];
    s32 texture;
    u8 pad160[0x3BAC - 0x160];
    s32 target;
    u8 pad3BB0[0x3BD4 - 0x3BB0];
    f32 depth;
    u8 pad3BD8[0x3C04 - 0x3BD8];
    u8 trig[1];
} Obj_b378_01E03450;

static void func_01E03450_b378(Obj_b378_01E03450 *o, Anim_b378_01E03450 *an, void *p, s32 draw) {
    extern s32 b378_01E01910(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b378_01E03450 quad[4];
    Vec_b378_01E03450 pos;
    Vec_b378_01E03450 scale;
    f32 m[16];
    f32 rm[4];
    s32 k;
    s32 a;
    s16 j;
    s16 d;

    j = 0;
    d = 1;
    if (draw == 0) {
        func_00106080(rm, 0x9B, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 0);
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
    if (an->fn == (s32)b378_01E01910) {
        d = 4;
    }
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->trig, a, 1);
        quad[2].z = an->radius * func_00108030(o->trig, a, 0);
        quad[0].x = (an->radius - 7) * func_00108030(o->trig, a, 1);
        quad[0].z = (an->radius - 7) * func_00108030(o->trig, a, 0);
        a = j + (an->start + d);
        quad[3].x = an->radius * func_00108030(o->trig, a, 1);
        quad[3].z = an->radius * func_00108030(o->trig, a, 0);
        quad[1].x = (an->radius - 7) * func_00108030(o->trig, a, 1);
        quad[1].z = (an->radius - 7) * func_00108030(o->trig, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &o->depth) != 0) {
            func_002075F0(p, o->target, (u32)o->depth);
        }
        j += 40;
    }
}

/* OVL_WARM */

/* shape b378:01E03790, 256 insns: b378:01E03450's ring of 18 quads 20 degrees wide (radius 0x38, inner 0x6), turned by the anim's rotation plus a quarter on z, at the anim, or at scene times 101..255 at the joint 0x3BEC / 0x3BEE (by kind 0x30) plus a tenth of the scene offset; setup pass page 0x97 */

typedef struct {
    f32 x, y, z, w;
} Vec_b378_01E03790;

typedef struct {
    s16 x, y, z;
    s16 inner;
    u8 pad08[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    s16 kind;
    u8 pad32[2];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b378_01E03790;

typedef struct {
    u8 pad00[0x15C];
    s32 texture;
    u8 pad160[0x3B80 - 0x160];
    Vec_b378_01E03790 off[2];
    u8 pad3BA0[0xC];
    s32 target;
    u8 pad3BB0[0x3BD4 - 0x3BB0];
    f32 depth;
    u8 pad3BD8[0x3BEC - 0x3BD8];
    s16 joint[2];
    u8 pad3BF0[0xE];
    s16 timer;
    u8 pad3C00[4];
    u8 trig[1];
} Obj_b378_01E03790;

static void func_01E03790_b378(Obj_b378_01E03790 *o, Anim_b378_01E03790 *an, void *p, s32 draw) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    Vec_b378_01E03790 quad[4];
    Vec_b378_01E03790 pos;
    f32 m[16];
    f32 rm[8];
    f32 v[4];
    s32 r[4];
    f32 *py;
    s16 j;
    f32 *pz;
    f32 *q;
    s32 k;
    s16 a;

    j = 0;
    if (draw == 0) {
        func_00106080(rm, 0x97, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, o->texture, 1);
        return;
    }
    py = &pos.y;
    pz = &pos.z;
    pos.x = an->x;
    *py = an->y;
    *pz = an->z;
    if (o->timer > 100 && o->timer < 256) {
        if (an->kind == 0) {
            func_001F5620(func_001F53A0(), o->joint[0], q = (f32 *)(u32)v);
            pos.x = q[0] + o->off[0].x / 10.0f;
            *py = v[1] + o->off[0].y / 10.0f;
            *pz = v[2] + o->off[0].z / 10.0f;
        }
        if (an->kind == 1) {
            func_001F5620(func_001F53A0(), o->joint[1], q = (f32 *)(u32)v);
            pos.x = q[0] + o->off[1].x / 10.0f;
            *py = v[1] + o->off[1].y / 10.0f;
            *pz = v[2] + o->off[1].z / 10.0f;
        }
    }
    *(Vec_b378_01E03790 *)r = *(Vec_b378_01E03790 *)an->rot;
    r[2] += 0x4000;
    func_00108EF0(m, NULL, r, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->trig, a, 1);
        quad[2].z = an->radius * func_00108030(o->trig, a, 0);
        quad[0].x = an->inner * func_00108030(o->trig, a, 1);
        quad[0].z = an->inner * func_00108030(o->trig, a, 0);
        a = an->start + 20 + j;
        quad[3].x = an->radius * func_00108030(o->trig, a, 1);
        quad[3].z = an->radius * func_00108030(o->trig, a, 0);
        quad[1].x = an->inner * func_00108030(o->trig, a, 1);
        quad[1].z = an->inner * func_00108030(o->trig, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &o->depth) != 0) {
            func_002075F0(p, o->target, (u32)o->depth);
        }
        j += 20;
    }
}
