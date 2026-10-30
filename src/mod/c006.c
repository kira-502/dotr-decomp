#include "common.h"

/* shape c006:01E00080, 269 insns: the c006 scene's step: colour 0x80/0/0/0, 0x2970 = 20, counts the tick (0x296E);
   tick 1 sets the scene bytes and the four corner points (0x296A = 0..3 through func_00106DD0) and adds a 0x1E004C0
   slot; every odd tick four slots at a random point (0x1E005F0 through 0x1E01020, then 0x1E004C0 left or right by
   0x296C) while over 18 are in use (0x2910); tick 10 sets one white point (chatA, 16 Oct) */

typedef struct {
    f32 x, y, z, w;
} V4_c006_01E00080;

typedef struct {
    u8 pad0[0x80];
    V4_c006_01E00080 pos;
    u8 pad90[0x2910 - 0x90];
    s32 n;
    u8 col[4];
    u8 pad2918[0x296A - 0x2918];
    s16 corner;
    s16 side;
    s16 tick;
    s16 f2970;
    u8 b2972;
    u8 b2973;
    u8 b2974;
    u8 pad2975;
    u8 b2976;
    u8 b2977;
    u8 b2978;
} Scene_c006_01E00080;

static void func_01E00080_c006(Scene_c006_01E00080 *g) {
    extern void c006_01E004C0(void);
    extern void c006_01E005F0(void);
    extern void c006_01E00F00(Scene_c006_01E00080 *, s32);
    extern void c006_01E01020(Scene_c006_01E00080 *, s32);
    extern void func_00106DD0(V4_c006_01E00080 *, f32, f32, f32);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->f2970 = 20;
    g->tick++;
    if (g->tick == 1) {
        g->b2972 = 0x40;
        g->b2973 = 0x20;
        g->b2974 = 0x30;
        g->b2976 = 0xC0;
        g->b2977 = 0;
        g->b2978 = 0;
        g->col[0] = 0x30;
        g->col[1] = 0x30;
        g->col[2] = 0x30;
        g->col[0] = 0x80;
        g->col[1] = 0x80;
        g->col[2] = 0x80;
        g->col[3] = 0;
        g->corner = 0;
        func_00106DD0(&g->pos, -100.0f, 100.0f, 0.0f);
        g->corner = 1;
        func_00106DD0(&g->pos, 100.0f, 100.0f, 0.0f);
        g->corner = 2;
        func_00106DD0(&g->pos, -100.0f, -100.0f, 0.0f);
        g->corner = 3;
        func_00106DD0(&g->pos, 0.0f, 0.0f, 0.0f);
        c006_01E00F00(g, (s32)c006_01E004C0);
    }
    if (g->tick % 2 == 1) {
        for (i = 0; i < 4; i++) {
            g->col[0] = 0x20;
            g->col[1] = 0x20;
            g->col[2] = 0x20;
            g->pos.x = -(func_0019A5C8() % 150 + 100);
            g->pos.z = func_0019A5C8() % 400 - 200;
            g->pos.y = func_0019A5C8() % 40 + 20;
            if (g->n > 18) {
                c006_01E01020(g, (s32)c006_01E005F0);
            }
        }
        if (g->side == 0) {
            for (i = 0; i < 4; i++) {
                g->col[0] = 0x40;
                g->col[1] = 0x40;
                g->col[2] = 0x40;
                g->pos.x = func_0019A5C8() % 150 + 300;
                g->pos.z = 0.0f;
                g->pos.y = func_0019A5C8() % 40 + 60;
                if (g->n > 18) {
                    c006_01E00F00(g, (s32)c006_01E004C0);
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                g->col[0] = 0x40;
                g->col[1] = 0x40;
                g->col[2] = 0x40;
                g->pos.x = -(func_0019A5C8() % 150 + 300);
                g->pos.z = 0.0f;
                g->pos.y = func_0019A5C8() % 40 + 60;
                if (g->n > 18) {
                    c006_01E00F00(g, (s32)c006_01E004C0);
                }
            }
        }
    }
    if (g->tick == 10) {
        for (i = 0; i < 1; i++) {
            g->col[0] = 0xFF;
            g->col[1] = 0xFF;
            g->col[2] = 0xFF;
            g->pos.x = -(func_0019A5C8() % 150 + 100);
            g->pos.z = func_0019A5C8() % 400 - 200;
            g->pos.y = func_0019A5C8() % 40 + 20;
        }
    }
}

/* shape c006:01E004C0, 74 insns: moves by 80 a tick, down to -400 (game flag 0x296C clear) or up to 400 (set), then
   ends; 0x56 wraps at 64; while the game counter at 0x2910 is below 14 both alphas fade by 8 (the second ends it),
   otherwise both are 0x1A; the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x2910];
    s32 count;
    u8 pad2914[0x58];
    s16 dir;
} Game_c006_01E004C0;

typedef struct {
    f32 y;
    u8 pad4[0x34];
    u8 col[4];
    u8 pad3C[4];
    u8 col2[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[0xC];
    s16 f56;
} Fx_c006_01E004C0;

static s32 func_01E004C0_c006(Game_c006_01E004C0 *g, Fx_c006_01E004C0 *o) {
    if (g->dir == 0) {
        if (!(o->y <= -400.0f)) {
            o->y -= 80.0f;
        } else {
            o->mode = 0;
        }
    } else if (o->y < 400.0f) {
        o->y += 80.0f;
    } else {
        o->mode = 0;
    }
    if (o->f56 >= 0x40) {
        o->f56 %= 0x40;
    }
    if (g->count < 14) {
        if (o->col[3] > 0xA) {
            o->col[3] -= 8;
        }
        if (o->col2[3] > 0xA) {
            o->col2[3] -= 8;
        } else {
            o->mode = 0;
        }
    } else {
        o->col[3] = 0x1A;
        o->col2[3] = 0x1A;
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c006:01E005F0, 70 insns: an 8-tick counter (0x52); rises by its speed (0x20) up to 150, then ends; 0x56 wraps
   at 64; while the game counter at 0x2910 is below 14 both alphas fade by 7 (the second ends it), otherwise both
   grow by 0x10 (below 0x50); the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x2910];
    s32 count;
} Game_c006_01E005F0;

typedef struct {
    f32 y;
    u8 pad4[0x1C];
    f32 speed;
    u8 pad24[0x14];
    u8 col[4];
    u8 pad3C[4];
    u8 col2[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[8];
    s16 f52;
    u8 pad54[2];
    s16 f56;
} Fx_c006_01E005F0;

static s32 func_01E005F0_c006(Game_c006_01E005F0 *g, Fx_c006_01E005F0 *o) {
    o->f52++;
    if (o->f52 >= 8) {
        o->f52 = 0;
    }
    if (o->y < 150.0f) {
        o->y += o->speed;
    } else {
        o->mode = 0;
    }
    if (o->f56 >= 0x40) {
        o->f56 %= 0x40;
    }
    if (g->count < 14) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        }
        if (o->col2[3] > 8) {
            o->col2[3] -= 7;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x10;
        }
        if (o->col2[3] < 0x50) {
            o->col2[3] += 0x10;
        }
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c006:01E00710, 118 insns: sets up the scene's 22 models (ids 0..10 and 256..266): object 0x1C90 + i x 0x70 gets
   a random size 1..5 (0x54), 0x28 -2..12, 0x34 0x100..0x18FF, 0x38 -0x3FF..0x3FF; all but models 0 and 11 are
   switched, it is registered (0x4 cleared, func_001F5B70 for flagged models), tagged from 0x2780 + i x 0x10 and
   coloured; flagged models get alpha 0x80 */

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x1C];
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    s32 w34;
    s32 w38;
    u8 pad3C[4];
    f32 scale[3];
    u8 pad4C[8];
    f32 f54;
    u8 pad58[8];
    u8 col[4];
    u8 pad64[0xC];
} Obj_c006_01E00710;

typedef struct {
    u8 tag[0x10];
} Tag_c006_01E00710;

typedef struct {
    u8 pad0[0x1C90];
    Obj_c006_01E00710 obj[22];
    u8 pad2630[0x2780 - 0x2630];
    Tag_c006_01E00710 tags[22];
} Scene_c006_01E00710;

static void func_01E00710_c006(Scene_c006_01E00710 *g) {
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    s16 i;
    s32 id;

    for (i = 0; i < 22; i++) {
        id = i;
        if (i > 10) {
            id = i + 0xF5;
        }
        {
        Obj_c006_01E00710 *p = &g->obj[i];
        p->f54 = (func_0019A5C8() % 26 + 9) / 6;
        p->w28 = func_0019A5C8() % 8 + 5;
        p->w34 = func_0019A5C8() % 0x1800 + 0x100;
        p->w38 = func_0019A5C8() % 0x800 - 0x400;
        if (i != 0 && i != 11) {
            func_001F5970(id, 1);
        }
        func_001F5BD0(id, p);
        p->w4 = 0;
        if (func_001F5AF0(id) != 0) {
            func_001F5B70(id, p);
        }
        func_001F5CA0(id, &g->tags[i]);
        func_001F5E40(id, p->col);
        if (func_001F5AF0(id) != 0) {
            func_001F5E40(id, p->col);
            p->col[3] = 0x80;
            func_001F5DE0(id, p->col);
        }
        }
    }
}

/* shape c006:01E008F0, 162 insns: c006's camera follower for one view (id, or id + 245 past 10): it refreshes the view's
   lens when live; when the view's bit (21 - id) is set in the scene mask and the view is live, it moves the view's eye
   behind the object (rising by half its speed from scene time 28, sliding by 1 or 2.5), wobbles or spins its turn (by
   +-0x800 before time 27, by the object's spin or three times it after), and fades the view out past height 75 and before
   scene step 25 */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 padC[4];
    f32 dx;
    u8 pad14[4];
    f32 dz;
    u8 pad1C[0x1C];
    s32 spin;
    u8 pad3C[0x18];
    f32 speed;
    u8 pad58[8];
    u8 col[4];
    s32 flip;
} Obj_c006_01E008F0;

typedef struct {
    u8 pad0[0x2910];
    s32 step;
    u8 pad2914[0x48];
    u32 mask;
    u8 pad2960[0xE];
    s16 time;
} Ctx_c006_01E008F0;

static s32 func_01E008F0_c006(Ctx_c006_01E008F0 *g, Obj_c006_01E008F0 *o, s32 id) {
    extern s32 func_001F5EC0(s32);
    extern void func_00107180(s32, s32, s32, s32);
    extern s32 func_001F5AF0(s32);
    extern void func_00107130(void *, void *, s32);
    extern f32 func_001A6C60(f32);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5C40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    s32 r[4];
    f32 w[4];
    f32 v[4];
    s32 k;

    k = id;
    if (id > 10) {
        k = id + 245;
    }
    if (func_001F5EC0(k)) {
        func_00107180(k, 0, g->step, 1);
    }
    if ((g->mask >> (21 - id)) & 1) {
        if (func_001F5AF0(k)) {
            func_00107130(o, v, 1);
            func_001A6C60((o->x + o->dx) * (o->x + o->dx) + (o->z + o->dz) * (o->z + o->dz));
            if (g->time > 27) {
                o->y += o->speed / 2.0f;
            }
            if (g->time < 55) {
                o->dx += 1.0f;
            } else {
                o->dx += 2.5f;
            }
            v[0] += o->dx;
            v[2] += o->dz;
            func_00107130(w, v, 0);
            func_001F5B70(k, w);
            func_001F5CA0(k, r);
            if (g->time < 27) {
                if (o->flip == 0) {
                    r[2] -= 0x800;
                    o->flip = 1;
                } else {
                    r[2] += 0x800;
                    o->flip = 0;
                }
            } else if (g->time < 55) {
                r[2] += o->spin;
            } else {
                r[2] += o->spin * 3;
            }
            func_001F5C40(k, r);
            if (!(o->y <= 75.0f)) {
                if (o->col[3] > 5) {
                    o->col[3] -= 4;
                }
            }
            if (g->step < 25) {
                if (o->col[3] > 8) {
                    o->col[3] -= 7;
                }
            }
            func_001F5DE0(k, o->col);
        }
    }
    return 0;
}

/* shape c006:01E00B80 (c006), 223 insns, 1 copy: the c006 module's main step: with a code it clears the scene, fills
   the cosine table (0..90 degrees at ctx+0x29A4), keeps the code and a 162-tick timer, textures (4,2) and (4,15),
   sets up the cards (c006:01E00710) and keeps the target's view mask; otherwise it runs the scene step
   (c006:01E00080) and every live slot's handler (80 of 0x58 bytes), draws the slots at the camera point
   (func_001F9D30) turned a quarter, scale (0.5, 0.2, 0.5), two passes each; above tick 10 it runs the 22 card
   followers (c006:01E008F0), below it hands each live, unmasked card (id, or id + 245 past 10) back to the model:
   scale 0.15, not busy, its position and turn, card on 0x18; counts down and returns 8 when the timer ends */

typedef struct {
    f32 x, y, z, w;
} V4_c006_01E00B80;

typedef struct Slot_c006_01E00B80 {
    u8 pad0[0x30];
    s32 (*draw)(void *, struct Slot_c006_01E00B80 *, void *, s32);
    s32 (*fn)(void *, struct Slot_c006_01E00B80 *);
    u8 pad38[0x10];
    s16 used;
    u8 pad4A[0xE];
} Slot_c006_01E00B80;

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x68];
} Card_c006_01E00B80;

typedef struct {
    u8 pad0[0x40];
    u8 cam[0x68];
    s32 texA8;
    u8 padAC[0x30];
    s32 texDC;
    s32 rot[4];
    u8 padF0[0x10];
    V4_c006_01E00B80 sc;
    Slot_c006_01E00B80 slot[80];
    Card_c006_01E00B80 card[22];
    u8 pad2630[0x2780 - 0x2630];
    s32 crot[22][4];
    u8 pad28E0[0x2910 - 0x28E0];
    s32 timer;
    u8 pad2914[8];
    s32 ot;
    u8 pad2920[0x295C - 0x2920];
    u32 mask;
    u8 pad2960[0x296C - 0x2960];
    s16 code;
    u8 pad296E[0x29A4 - 0x296E];
    f32 cos[91];
} Ctx_c006_01E00B80;

extern void c006_01E00080(Ctx_c006_01E00B80 *, s32);
extern void c006_01E00710(Ctx_c006_01E00B80 *);
extern s32 c006_01E008F0(Ctx_c006_01E00B80 *, Card_c006_01E00B80 *, s32);

static s32 func_01E00B80_c006(s32 arg0, s32 code) {
    Ctx_c006_01E00B80 *g = (Ctx_c006_01E00B80 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern s32 func_00202BF0(s32, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_001F5380(void);
    extern V4_c006_01E00B80 *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_001F5EC0(s32);
    extern void func_00107370(s32, s32, f32);
    extern s32 func_001F5AF0(s32);
    extern void func_001F5970(s32, s32);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5C40(s32, void *);
    extern void func_00107650(s32, s32);
    s32 n;
    V4_c006_01E00B80 pos;
    u8 pkt[0x90];
    s32 (*draw)();
    s32 (*fn)();
    s32 i;
    s32 id;

    n = 0;
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2B10);
        for (i = 0; i < 91; i++) {
            g->cos[i] = func_001A6A88(3.1415927f * i / 180.0f);
        }
        g->code = code;
        g->timer = 162;
        g->texA8 = func_00202BF0(4, 2);
        g->texDC = func_00202BF0(4, 15);
        c006_01E00710(g);
        g->mask = func_001F5380();
        return 0;
    }
    c006_01E00080(g, 0);
    for (i = 0; i < 80; i++) {
        if (g->slot[i].used != 0) {
            fn = g->slot[i].fn;
            if (fn != NULL) {
                fn(g, &g->slot[i]);
            }
        }
    }
    pos.x = pos.y = pos.z = 0.0f;
    pos.y = 50.0f;
    pos = *func_001F9D30(0);
    func_00205C40((s32)g->rot);
    g->rot[0] += 0x4000;
    g->sc.y = 0.2f;
    g->sc.x = 0.5f;
    g->sc.z = 0.5f;
    func_00205C40((s32)g->rot);
    for (i = 0; i < 80; i++) {
        if (g->slot[i].used != 0) {
            n++;
            func_0020EB40(g->cam);
            func_0020C940(g, &g->sc, g->rot, &pos);
            func_0020BC00(g->cam, g);
            draw = g->slot[i].draw;
            if (g->slot[i].draw != NULL) {
                draw(g, &g->slot[i], pkt, 0);
                draw(g, &g->slot[i], pkt, 1);
            }
        }
    }
    if (g->timer > 10) {
        for (i = 0; i < 22; i++) {
            c006_01E008F0(g, &g->card[i], i);
        }
    } else {
        for (i = 0; i < 22; i++) {
            id = i;
            if (i > 10) {
                id = i + 245;
            }
            if (!((g->mask >> (21 - i)) & 1)) {
                if (g->timer < 10) {
                    if (func_001F5EC0(id) != 0) {
                        func_00107370(id, 0, 0.15f);
                    }
                    if (func_001F5AF0(id) != 0) {
                        func_001F5970(id, 0);
                        g->card[i].w4 = 0;
                        func_001F5B70(id, &g->card[i]);
                        func_001F5C40(id, g->crot[i]);
                        func_00107650(id, 0x18);
                    }
                }
            }
        }
    }
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}


/* shape c006:01E00F00, 70 insns: take a free slot (0x50 of 0x58 bytes at 0x110), clear it, copy the scene's pair at
   0x2914 twice, its vector at 0x80 and 0x296A; callback c006:01E01180 and arg */

typedef struct {
    f32 x, y, z, w;
} V4_c006_01E00F00;

typedef struct {
    f32 a, b;
} P2_c006_01E00F00;

typedef struct {
    V4_c006_01E00F00 pos;
    u8 pad10[0x20];
    void (*cb)(void);
    s32 arg;
    P2_c006_01E00F00 p38;
    P2_c006_01E00F00 p40;
    s16 used;
    u8 pad4A[0xC];
    s16 f56;
} Slot_c006_01E00F00;

typedef struct {
    u8 pad0[0x80];
    V4_c006_01E00F00 pos;
    u8 pad90[0x80];
    Slot_c006_01E00F00 slots[0x50];
    u8 pad1C90[0x2914 - 0x1C90];
    P2_c006_01E00F00 pair;
    u8 pad291C[0x4E];
    s16 f296A;
} Scene_c006_01E00F00;

static void func_01E00F00_c006(Scene_c006_01E00F00 *g, s32 arg) {
    extern void c006_01E01180(void);
    extern void func_00195108();
    Slot_c006_01E00F00 *s = NULL;
    s16 i;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x58);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        s->p38 = g->pair;
        s->p40 = g->pair;
        s->pos = g->pos;
        s->f56 = g->f296A;
        s->cb = c006_01E01180;
        s->arg = arg;
    }
}

/* shape c006:01E01020, 88 insns: takes the first free of 80 effect slots (0x58 bytes, b108:01E02FF0 family), gives it the
   context's UV pair twice and point, a random size 10..19 and side 0..1, the context's frame, and hooks c006:01E012D0 */

typedef struct {
    f32 s, t;
} St_c006_01E01020;

typedef struct {
    Vec4f pos;
    u8 pad10[0x10];
    f32 size;
    u8 pad24[0xC];
    void (*cb)(void);
    s32 arg;
    St_c006_01E01020 st0;
    St_c006_01E01020 st1;
    s16 used;
    u8 pad4A[0xA];
    s16 side;
    s16 f56;
} Slot_c006_01E01020;

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x80];
    Slot_c006_01E01020 slots[0x50];
    u8 pad[0x2914 - 0x110 - 0x50 * 0x58];
    St_c006_01E01020 st;
    u8 pad291C[0x4E];
    s16 f296A;
} Ctx_c006_01E01020;

static void func_01E01020_c006(Ctx_c006_01E01020 *ctx, s32 arg) {
    extern void c006_01E012D0(void);
    extern void func_00195108();
    Slot_c006_01E01020 *s = NULL;
    s16 i;

    for (i = 0; i < 0x50; i++) {
        if (ctx->slots[i].used == 0) {
            func_00195108(&ctx->slots[i], 0x58);
            ctx->slots[i].used = 1;
            s = &ctx->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        s->st0 = ctx->st;
        s->st1 = ctx->st;
        s->pos = ctx->pos;
        s->size = func_0019A5C8() % 10 + 0xA;
        s->side = func_0019A5C8() % 2;
        s->f56 = ctx->f296A;
        s->cb = c006_01E012D0;
        s->arg = arg;
    }
}

/* shape c006:01E01180, 83 insns: draws a textured quad effect: mode 0 builds the packet (texture page 0x99 rectangle, UVs from
   the effect's two corners, the context's texture); other modes place it at 600 x 720 and queue it at the context depth */

typedef struct {
    f32 s, t;
} St_c006_01E01180;

typedef struct {
    St_c006_01E01180 st;
    u8 c[8];
    u64 xyz;
} Vtx_c006_01E01180;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c006_01E01180 v[4];
} Pkt_c006_01E01180;

typedef struct {
    u8 pad0[0x38];
    St_c006_01E01180 st0;
    St_c006_01E01180 st1;
} Fx_c006_01E01180;

typedef struct {
    u8 pad0[0xDC];
    void *tex;
    u8 padE0[0x291C - 0xE0];
    s32 ot;
    u8 pad2920[0x28];
    f32 depth;
} Ctx_c006_01E01180;

static void func_01E01180_c006(Ctx_c006_01E01180 *g, Fx_c006_01E01180 *o, Pkt_c006_01E01180 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_001095D0(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    s16 rect[8];
    Vec4f v;

    if (mode == 0) {
        func_00106080(rect, 0x99, 2, rect);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].st = o->st0;
        p->v[1].st = o->st0;
        p->v[2].st = o->st1;
        p->v[3].st = o->st1;
        func_00108500(p, rect, 1);
        func_00208700(p, g->tex, 1);
    } else {
        func_00106DD0(&v, 600.0f, 720.0f, 0.0f);
        func_001095D0(p, &v, o);
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

/* shape c006:01E012D0, 176 insns: c006:01E01180's textured quad as a billboard: mode 0 builds the packet (texture page
   0x99 or 0x14 rectangle by the h54 flag, UVs from the effect's two corners, the context's texture or the other one);
   other modes turn the effect 300 x the angle table's first entry up from 100 above it and draw an 80-wide square there
   at the context depth */

typedef struct {
    f32 s, t;
} St_c006_01E012D0;

typedef struct {
    St_c006_01E012D0 st;
    u8 c[8];
    u64 xyz;
} Vtx_c006_01E012D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c006_01E012D0 v[4];
} Pkt_c006_01E012D0;

typedef struct {
    u8 pad0[0x38];
    St_c006_01E012D0 st0;
    St_c006_01E012D0 st1;
    u8 pad48[0xA];
    s16 h52;
    s16 h54;
} Fx_c006_01E012D0;

typedef struct {
    u8 pad0[0xA8];
    void *tex2;
    u8 padAC[0x30];
    void *tex;
    u8 padE0[0x291C - 0xE0];
    s32 ot;
    u8 pad2920[0x28];
    f32 depth;
    u8 pad294C[0x58];
    u8 sin[1];
} Ctx_c006_01E012D0;

static void func_01E012D0_c006(Ctx_c006_01E012D0 *g, Fx_c006_01E012D0 *o, Pkt_c006_01E012D0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00109830(void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    extern void func_0020EB40(void *);
    extern void func_00205C40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    Vec4f q[4];
    s16 rect[8];
    f32 m[16];
    f32 m1[16];
    f32 m2[16];
    Vec4f rot;
    Vec4f up;
    Vec4f at;
    s32 i;
    f32 x, y, z;

    if (mode == 0) {
        if (o->h54 != 0) {
            func_00106080(rect, 0x99, o->h52, rect);
        } else {
            func_00106080(rect, 0x14, o->h52, rect);
        }
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0xB0 << 32) | 0x48);
        p->v[0].st = o->st0;
        p->v[1].st = o->st0;
        p->v[2].st = o->st1;
        p->v[3].st = o->st1;
        func_00108500(p, rect, 0);
        if (o->h54 != 0) {
            func_00208700(p, g->tex, 1);
        } else {
            func_00208700(p, g->tex2, 1);
        }
    } else {
        func_0020EB40(m);
        func_00205C40(&rot);
        func_0020C940(m1, 0, &rot, o);
        func_0020BC00(m, m1);
        z = y = x = 0.0f;
        func_00106DD0(&at, x, y, z);
        at.z = 300.0f * func_00108030(g->sin, 0, 1);
        at.y = 300.0f * func_00108030(g->sin, 0, 1);
        z = x = 0.0f;
        func_00106DD0(&up, x, 100.0f, z);
        func_00109830(&up, o, &at);
        func_0020EB40(m1);
        func_00205C40(&rot);
        func_0020C940(m2, 0, 0, &at);
        func_0020BC00(m1, m2);
        for (i = 0; i < 1; i++) {
            if (i == 0) {
                q[0].x = -40.0f;
                q[0].y = 40.0f;
                q[1].x = 40.0f;
                q[1].y = 40.0f;
                q[2].x = -40.0f;
                q[2].y = -40.0f;
                q[3].x = 40.0f;
                q[3].y = -40.0f;
                q[0].z = 0.0f;
                q[2].z = 0.0f;
                q[3].z = 0.0f;
                q[1].z = 0.0f;
            }
            if (func_00205630(q, 0x70000000, m, p, &g->depth) != 0) {
                func_002075F0(p, g->ot, func_001A23B0(g->depth));
            }
        }
    }
}
