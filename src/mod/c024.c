#include "common.h"

/* shape c024:01E00080, 223 insns: the c024 module's scene step: full alpha, 0x3B78 = 20, counts ticks (0x3B6E); at 1
   white and the grid built (c024:01E01CD0); for the first 32 ticks, while the rise 0x3B7A is under 230, four grey
   c024:01E00400 sparks a tick at height 0x3B62 + 4 (size 10..18, random angle, scale 1.5); 0x3B62 climbs 4 a tick;
   the rise climbs 8 to 230 (copied to 0x3B7C once past it), then 0x3B7C drops 3 every other tick; a 180-step delay
   loop; at 34 and 37 bursts of 30 c024:01E004F0 at the origin in the saved colour (0x3B58) when 0x3B20 is over 17 */

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x124 - 0xCC];
    f32 scale;
    u8 pad128[0x3B20 - 0x128];
    s32 level;
    u8 col[4];
    u8 pad3B28[8];
    s32 w3B30;
    u8 pad3B34[4];
    f32 size;
    u8 pad3B3C[0x3B58 - 0x3B3C];
    u8 save[3];
    u8 pad3B5B[3];
    s16 ang;
    u8 pad3B60[2];
    s16 height;
    u8 pad3B64[0x3B6E - 0x3B64];
    s16 count;
    u8 pad3B70[8];
    s16 h3B78;
    s16 rise;
    s16 top;
    s16 wait;
} Ctx_c024_01E00080;

static void func_01E00080_c024(Ctx_c024_01E00080 *g) {
    extern s32 c024_01E00400(void);
    extern s32 c024_01E004F0(void);
    extern void c024_01E009B0(Ctx_c024_01E00080 *, s32 (*)(void));
    extern void c024_01E00AE0(Ctx_c024_01E00080 *, s32 (*)(void));
    extern void c024_01E01CD0(Ctx_c024_01E00080 *, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 i;
    s32 k;

    g->col[3] = 0x80;
    g->h3B78 = 20;
    g->count++;
    if (g->count == 1) {
        g->col[0] = 0xFF;
        g->col[1] = 0xFF;
        g->col[2] = 0xFF;
    }
    if (g->count == 1) {
        c024_01E01CD0(g, 0);
    }
    if (g->count < 33 && g->rise < 230) {
        for (i = 0; i < 4; i++) {
            g->pos[0] = 0.0f;
            g->pos[1] = g->height + 4;
            g->pos[2] = 0.0f;
            g->col[0] = 0x80;
            g->col[1] = 0x80;
            g->col[2] = 0x80;
            g->size = func_0019A5C8() % 9 + 10;
            g->col[3] = 10;
            g->ang = func_0019A5C8() % 360;
            g->scale = 1.5f;
            c024_01E009B0(g, c024_01E00400);
        }
    }
    g->height += 4;
    if (g->rise < 230) {
        g->rise += 8;
        if (g->rise > 230) {
            g->top = g->rise;
        }
    } else if (g->wait == 0) {
        g->top -= 3;
        g->wait = 1;
    } else {
        g->wait--;
    }
    for (k = 0; k < 180; k++) {
    }
    if (g->count == 34) {
        g->col[3] = 0;
        g->col[0] = g->save[0];
        g->col[1] = g->save[1];
        g->col[2] = g->save[2];
        func_00106DD0(g->pos, 0.0f, 0.0f, 0.0f);
        for (i = 0; i < 30; i++) {
            g->scale = func_0019A5C8() % 10 + 8;
            g->size = func_0019A5C8() % 140 + 5;
            g->w3B30 = 0;
            if (g->level > 17) {
                c024_01E00AE0(g, c024_01E004F0);
            }
        }
    }
    if (g->count == 37) {
        g->col[3] = 0;
        g->col[0] = g->save[0];
        g->col[1] = g->save[1];
        g->col[2] = g->save[2];
        for (i = 0; i < 30; i++) {
            func_00106DD0(g->pos, 0.0f, 0.0f, 0.0f);
            g->size = func_0019A5C8() % 140 + 5;
            g->scale = func_0019A5C8() % 10 + 8;
            g->w3B30 = 0;
            if (g->level > 17) {
                c024_01E00AE0(g, c024_01E004F0);
            }
        }
    }
}

/* shape c024:01E00400, 59 insns: an animated sprite: frame steps every 3 ticks up to 7 (then dies), slides by its speed; in by 15 for frames 0-2, then out by 12 and dies */

typedef struct {
    u8 pad0[0x16];
    s16 h16;
    u8 pad18[4];
    s16 h1C;
    u8 pad1E[4];
    s16 h22;
    s8 frame;
    s8 alive;
    s16 h26;
    u8 pad28[5];
    u8 alpha;
    u8 pad2E[3];
    u8 alpha2;
} Spr_c024_01E00400;

static s32 func_01E00400_c024(s32 arg0, Spr_c024_01E00400 *o) {
    if (o->h22 == 0) {
        if (o->frame < 7) {
            o->frame++;
        } else {
            o->alive = 0;
        }
        o->h22 = 2;
    } else {
        o->h22--;
    }
    o->h16 -= o->h1C;
    o->h26++;
    if (o->frame < 3) {
        if (o->alpha < 0x80) {
            o->alpha += 15;
        }
        if (o->alpha < 0x80) {
            o->alpha2 += 15;
        }
    } else {
        if (o->alpha > 0x10) {
            o->alpha -= 12;
        }
        if (o->alpha > 0x10) {
            o->alpha2 -= 12;
        } else {
            o->alive = 0;
        }
    }
    return 0;
}

/* shape c024:01E004F0, 59 insns: a rising sprite: frame 0 climbs by its speed (dies past 260), others by 8 (die past 180); in by 27 up to 0xC0, past 130 out by 32 and dies */

typedef struct {
    u8 pad0[0x16];
    s16 h16;
    u8 pad18[4];
    s16 h1C;
    u8 pad1E[4];
    s16 h22;
    s8 frame;
    s8 alive;
    s16 h26;
    u8 pad28[5];
    u8 alpha;
    u8 pad2E[3];
    u8 alpha2;
} Spr_c024_01E004F0;

static s32 func_01E004F0_c024(s32 arg0, Spr_c024_01E004F0 *o) {
    if (o->frame == 0) {
        o->h16 += o->h1C;
        if (o->h16 > 0x104) {
            o->alive = 0;
        }
    } else {
        o->h16 += 8;
        if (o->h16 > 180) {
            o->alive = 0;
        }
    }
    if (o->frame == 0) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x1B;
        }
    } else if (o->h16 < 0x82) {
        if (o->alpha < 0xC0) {
            o->alpha += 0x1B;
        }
    } else {
        if (o->alpha > 0x20) {
            o->alpha -= 0x20;
        } else {
            o->alive = 0;
        }
        if (o->alpha2 > 0x20) {
            o->alpha2 -= 0x20;
        }
    }
    return 0;
}

/* shape c024:01E005E0 (c024), 243 insns, 1 copy: c024's scene manager: with a scene id (>= 0) it clears the scene, sets
   the scene colour and the module step, builds the sine table for 0..90 degrees, keeps the id, sets the 71-frame
   countdown and loads texture 15; otherwise it runs the step, every live node's update (c024:01E00400 or
   c024:01E004F0 by its handler), and draws every live node twice with the camera point (func_001F5BD0) by its handler
   and flag; it grows the shared scale to 1, draws the scene layer while the countdown is above 3, and returns 2 once
   the scene state reaches 38, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    void *fn;
    u8 pad14[0x10];
    s8 flag;
    s8 used;
    u8 pad26[0xE];
} Node_c024_01E005E0;

typedef struct {
    u8 m0[0x80];
    u8 m[0x50];
    s32 tex[16];
    s32 rot[4];
    u8 pad120[0x20];
    f32 sc[4];
    u8 pad150[0x2A90 - 0x150];
    Node_c024_01E005E0 node[80];
    u8 pad3AD0[0x50];
    s32 count;
    u8 pad3B24[8];
    s32 ot;
    u8 pad3B30[4];
    void *step;
    u8 pad3B38[0x20];
    u8 col[4];
    u8 pad3B5C[0xE];
    s16 id;
    u8 pad3B6C[2];
    s16 state;
    u8 pad3B70[0x10];
    f32 sintab[91];
} Scene_c024_01E005E0;

static void func_01E01220_c024();
static void func_01E02020_c024();

static s32 func_01E005E0_c024(s32 arg0, s32 id) {
    Scene_c024_01E005E0 *g = (Scene_c024_01E005E0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void c024_01E00080();
    extern void c024_01E00400();
    extern void c024_01E004F0();
    extern void c024_01E00CD0();
    extern void c024_01E015D0();
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 n;
    f32 v[4];
    Vec4f t;
    u8 buf[0x90];
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        v[0] = v[1] = v[2] = 0.0f;
        func_00195108(g, 0x3CF0);
        g->col[0] = 0x50;
        g->col[1] = 0x50;
        g->col[2] = 0xFF;
        g->col[3] = 0xFF;
        g->step = func_01E00080_c024;
        for (; n < 91; n++) {
            g->sintab[n] = func_001A6A88(3.1415927f * n / 180.0f);
        }
        g->id = id;
        g->count = 71;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    c024_01E00080(g, 0);
    func_001F5BD0(func_001F5380(), &t);
    v[0] = t.x;
    v[1] = t.y;
    v[2] = t.z;
    func_0020EB40(g->m);
    func_00205C40((s32)g->rot);
    g->rot[0] = 0;
    func_0020C940(g, NULL, g->rot, v);
    func_0020BC00(g->m, g);
    for (i = 0; i < 80; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E00400_c024) {
                c024_01E00400(g, &g->node[i]);
            } else if (g->node[i].fn == func_01E004F0_c024) {
                c024_01E004F0(g, &g->node[i]);
            }
        }
    }
    v[2] = 0.0f;
    v[0] = 0.0f;
    v[1] = 50.0f;
    func_00205C40((s32)g->rot);
    for (i = 0; i < 80; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E00400_c024) {
                func_01E02020_c024(g, &g->node[i], buf, 0);
                func_01E02020_c024(g, &g->node[i], buf, 1);
            } else if (g->node[i].fn == func_01E004F0_c024) {
                if (g->node[i].flag == 0) {
                    func_01E01220_c024(g, &g->node[i], buf, 0);
                    func_01E01220_c024(g, &g->node[i], buf, 1);
                } else {
                    c024_01E00CD0(g, &g->node[i], buf, 0);
                    c024_01E00CD0(g, &g->node[i], buf, 1);
                }
            }
        }
    }
    v[2] = 0.0f;
    v[1] = 0.0f;
    v[0] = 0.0f;
    v[1] = 50.0f;
    if (g->sc[1] < 1.0f) {
        func_00106DD0(g->sc, 0.24f, 0.5f, 0.24f);
    }
    if (g->count > 3) {
        c024_01E015D0(g, 0, buf, 0);
        c024_01E015D0(g, 0, buf, 1);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->state == 38) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape c024:01E009B0, 74 insns: take a free slot (0x50 of 0x34 bytes at 0x2A90, byte flag at 0x25 = index + 1),
   clear it, colour both colours from the scene colour 0x3B24, position (0xC0..0xC8), 0x26/0x1C from the scene floats
   0x3B38/0x124, 0x28 from 0x3B5E, store arg */

typedef struct {
    u8 pad0[0x10];
    s32 arg;
    s16 x, y, z;
    u8 pad1A[2];
    s16 f1C;
    u8 pad1E[7];
    s8 used;
    s16 f26;
    s16 f28;
    u8 c2A[4];
    u8 c2E[4];
    u8 pad32[2];
} Slot_c024_01E009B0;

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x58];
    f32 f124;
    u8 pad128[0x2A90 - 0x128];
    Slot_c024_01E009B0 slots[0x50];
    u8 pad3AD0[0x54];
    u8 rgba[4];
    u8 pad3B28[0x10];
    f32 f3B38;
    u8 pad3B3C[0x22];
    s16 f3B5E;
} Scene_c024_01E009B0;

static void func_01E009B0_c024(Scene_c024_01E009B0 *g, s32 arg) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    Slot_c024_01E009B0 *s = NULL;
    s32 i;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x34);
            g->slots[i].used = i + 1;
            s = &g->slots[i];
            i = 0x50;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2A, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2A[3] = g->rgba[3];
        func_001076F0(s->c2E, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2E[3] = g->rgba[3];
        s->x = g->pos[0];
        s->y = g->pos[1];
        s->z = g->pos[2];
        s->f26 = g->f3B38;
        s->f28 = g->f3B5E;
        s->f1C = g->f124;
        s->arg = arg;
    }
}

/* shape c024:01E00AE0, 123 insns: take a free slot (0x50 of 0x34 bytes at 0x2A90, byte flag at 0x25 = index + 1),
   clear it, colour both colours from the scene colour 0x3B24, position (0xC0..0xC8), two random words 0x0/0x8
   (-0x4000..0x3FF0), 0x26/0x28 from the scene 0x3B38/0x3B5E, a random half-size flag 0x24 (0x1C = scene 0x124,
   halved when set), 0x20 random 0..19, store arg */

typedef struct {
    s32 w0;
    u8 pad4[4];
    s32 w8;
    u8 padC[4];
    s32 arg;
    s16 x, y, z;
    u8 pad1A[2];
    s16 f1C;
    u8 pad1E[2];
    s16 f20;
    u8 pad22[2];
    s8 half;
    s8 used;
    s16 f26;
    s16 f28;
    u8 c2A[4];
    u8 c2E[4];
    u8 pad32[2];
} Slot_c024_01E00AE0;

typedef struct {
    u8 pad0[0xC0];
    f32 pos[3];
    u8 padCC[0x58];
    f32 f124;
    u8 pad128[0x2A90 - 0x128];
    Slot_c024_01E00AE0 slots[0x50];
    u8 pad3AD0[0x54];
    u8 rgba[4];
    u8 pad3B28[0x10];
    f32 f3B38;
    u8 pad3B3C[0x22];
    s16 f3B5E;
} Scene_c024_01E00AE0;

static void func_01E00AE0_c024(Scene_c024_01E00AE0 *g, s32 arg) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;
    Slot_c024_01E00AE0 *s = NULL;

    for (i = 0; i < 0x50; i++) {
        if (g->slots[i].used == 0) {
            s = &g->slots[i];
            func_00195108(s, 0x34);
            g->slots[i].used = i + 1;
            i = 0x50;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c2A, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2A[3] = g->rgba[3];
        func_001076F0(s->c2E, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->c2E[3] = g->rgba[3];
        s->x = g->pos[0];
        s->y = g->pos[1];
        s->z = g->pos[2];
        func_0019A5C8();
        s->w8 = func_0019A5C8() % 0x800 * 16 - 0x4000;
        s->w0 = func_0019A5C8() % 0x800 * 16 - 0x4000;
        s->f26 = g->f3B38;
        s->f28 = g->f3B5E;
        s->half = func_0019A5C8() % 2;
        if (s->half == 0) {
            s->f1C = g->f124;
        } else {
            s->f1C = g->f124 / 2.0f;
        }
        s->f20 = func_0019A5C8() % 20;
        s->arg = arg;
    }
}

/* shape c024:01E00CD0 (C024PAINT_RAIN2), 340 insns, 1 copy: mode 0 sets the drawing state (a 0x9C
   matrix, packet header, top colours 0x2A, bottom 0x2E, texture 15); otherwise a quad cut from the scene grid (point
   j, j+1, j+24, j+25 less point j), scaled by 0.15, drawn at three points 120 degrees apart around (0x14, 0x18) at
   radius 0x16, height 0x26 x sin(0x16) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c024_01E00CD0;

typedef struct {
    Rgbaq_c024_01E00CD0 c;
    u64 st;
    u64 xyz;
} Vtx_c024_01E00CD0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c024_01E00CD0 v[4];
} Pkt_c024_01E00CD0;

typedef struct {
    s32 rx;
    s32 pad4;
    s32 rz;
    u8 padC[8];
    s16 x;
    s16 r;
    s16 z;
    u8 pad1A[6];
    s16 j;
    u8 pad22[4];
    s16 h;
    u8 pad28[2];
    u8 col0[4];
    u8 col1[4];
} Obj_c024_01E00CD0;

typedef struct {
    u8 pad0[0x80];
    u8 m[0x50];
    u8 padD0[0x3C];
    s32 tex;
    u8 pad110[0x30];
    f32 sc[4];
    Vec4f pt[1];
    u8 pad160[0x3AE0 - 0x160];
    Vec4f quad[4];
    u8 pad3B20[0xC];
    s32 ot;
    u8 pad3B30[0x18];
    f32 depth;
    u8 pad3B4C[0x34];
    f32 sintab[91];
} Scene_c024_01E00CD0;

static void func_01E00CD0_c024(Scene_c024_01E00CD0 *g, Obj_c024_01E00CD0 *o, Pkt_c024_01E00CD0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c024_01E00CD0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00106B50(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f v[4];
    f32 pos[4];
    f32 rm[4];
    s16 a;
    s16 b;
    s16 i;
    f32 s;

    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->v[0].c = func_00107740(o->col0);
        p->v[1].c = func_00107740(o->col0);
        p->v[2].c = func_00107740(o->col1);
        p->v[3].c = func_00107740(o->col1);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        v[0].x = g->pt[o->j].x - g->pt[o->j].x;
        v[0].y = g->pt[o->j].y - g->pt[o->j].y;
        v[0].z = g->pt[o->j].z - g->pt[o->j].z;
        v[1].x = g->pt[o->j + 1].x - g->pt[o->j].x;
        v[1].y = g->pt[o->j + 1].y - g->pt[o->j].y;
        v[1].z = g->pt[o->j + 1].z - g->pt[o->j].z;
        v[2].x = g->pt[o->j + 24].x - g->pt[o->j].x;
        v[2].y = g->pt[o->j + 24].y - g->pt[o->j].y;
        v[2].z = g->pt[o->j + 24].z - g->pt[o->j].z;
        v[3].x = g->pt[o->j + 25].x - g->pt[o->j].x;
        v[3].y = g->pt[o->j + 25].y - g->pt[o->j].y;
        v[3].z = g->pt[o->j + 25].z - g->pt[o->j].z;
        s = 0.15f;
        func_00106DD0(g->sc, s, s, s);
        func_00106E90(&v[0], g->sc);
        func_00106E90(&v[1], g->sc);
        func_00106E90(&v[2], g->sc);
        func_00106E90(&v[3], g->sc);
        a = o->rx / 182;
        b = o->rz / 182;
        for (i = 0; i < 3; i++) {
            pos[0] = o->x;
            pos[2] = o->z;
            pos[0] += o->r * func_00108030(g->sintab, a + i * 120, 0);
            pos[2] += o->r * func_00108030(g->sintab, b + i * 120, 0);
            a = o->r;
            pos[1] = o->h * func_00108030(g->sintab, a, 0);
            g->quad[0] = v[0];
            g->quad[1] = v[1];
            g->quad[2] = v[2];
            g->quad[3] = v[3];
            func_00106B50(&g->quad[0], pos);
            func_00106B50(&g->quad[1], pos);
            func_00106B50(&g->quad[2], pos);
            func_00106B50(&g->quad[3], pos);
            if (func_00205630(g->quad, 0x70000000, g->m, p, &g->depth) != 0) {
                func_002075F0(p, g->ot, func_001A23B0(g->depth));
            }
        }
    }
}

/* shape c024:01E01220, 233 insns: b004:01E01A00's hanging quad in two passes: with lit 0 it sets up the packet (rect
   0x8C,0,4,0x7F, colours 0x2A top and 0x2E bottom, scene texture 0x10C) and returns; otherwise it builds the scene
   matrix (0x40) from the point func_001F53B0 gives and the anim's rotation, and draws one quad 3 wide at the anim's
   s16 point hanging 60 down, heights kept within 12..200, depth in 0x3B48, into 0x3B2C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c024_01E01220;

typedef struct {
    Rgbaq_c024_01E01220 c;
    u64 st;
    u64 xyz;
} Vtx_c024_01E01220;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c024_01E01220 v[4];
} Pkt_c024_01E01220;

typedef struct {
    s16 x, y, w, h;
} Rect_c024_01E01220;

typedef struct {
    s32 rot[4];
    u8 pad10[4];
    s16 x, y, z;
    u8 pad1A[0x10];
    u8 col[4];
    u8 col2[4];
} Anim_c024_01E01220;

typedef struct {
    u8 pad00[0x40];
    u8 m[0x40];
    u8 pad80[0x8C];
    s32 tex;
    u8 pad110[0x3B2C - 0x110];
    s32 ot;
    u8 pad3B30[0x18];
    f32 depth;
} Scene_c024_01E01220;

static void func_01E01220_c024(Scene_c024_01E01220 *g, Anim_c024_01E01220 *an, Pkt_c024_01E01220 *p, s32 lit) {
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c024_01E01220 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_001F53B0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    f32 m[16];
    f32 v[4];
    Rect_c024_01E01220 r __attribute__((aligned(16)));

    if (lit == 0) {
        r.x = 0x8C;
        r.y = 0;
        r.w = 4;
        r.h = 0x7F;
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, &r, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_001F53B0(0, v);
    func_0020EB40(g->m);
    func_0020C940(m, 0, an->rot, v);
    func_0020BC00(g->m, m);
    q[0].x = an->x;
    q[0].y = an->y;
    q[0].z = an->z;
    q[1] = q[0];
    q[1].x += 3.0f;
    q[2].x = an->x;
    q[2].y = an->y;
    q[2].z = an->z;
    q[2].y -= 60.0f;
    q[3] = q[2];
    q[3].x += 3.0f;
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
    if (q[0].y < 12.0f) {
        q[0].y = 12.0f;
    }
    if (q[1].y < 12.0f) {
        q[1].y = 12.0f;
    }
    if (q[2].y < 12.0f) {
        q[2].y = 12.0f;
    }
    if (q[3].y < 12.0f) {
        q[3].y = 12.0f;
    }
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}

/* shape c024:01E015D0 (C024PAINT_RAIN4), 445 insns, 1 copy: mode 0 sets the drawing state (a 0x9C
   matrix, packet via func_00109270, all four colours from the scene colour 0x3B58, texture 0x10C); otherwise, from
   scene state 3, draws the 10x24 grid at ctx+0x150 as quads (point j, j+1 wrapping at 23, and the next ring), each
   moved by its own piece (0x1C bytes at ctx+0x1050, the first ctx+0x3B7A drawn), scaled by ctx+0x140 and offset by
   the unit position; at tick 34 each piece takes its point / 15 as speed, from tick 36 (state 5+) pieces fly and turn
   by 12 and the alpha fades by 13 down to 16 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c024_01E015D0;

typedef struct {
    Rgbaq_c024_01E015D0 c;
    u64 st;
    u64 xyz;
} Vtx_c024_01E015D0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c024_01E015D0 v[4];
} Pkt_c024_01E015D0;

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    s16 rx;
    s16 ry;
    u8 pad14[2];
    s16 vx;
    s16 vy;
    s16 vz;
} Obj_c024_01E015D0;

typedef struct {
    u8 pad0[0x10C];
    s32 tex;
    u8 pad110[0x30];
    f32 sc[4];
    Vec4f pt[10][24];
    Obj_c024_01E015D0 obj[240];
    u8 pad2A90[0x3B20 - 0x2A90];
    s32 state;
    u8 pad3B24[8];
    s32 ot;
    u8 pad3B30[0x18];
    f32 depth;
    u8 pad3B4C[0xC];
    u8 col[4];
    u8 pad3B5C[0x12];
    s16 t;
    u8 pad3B70[0xA];
    s16 cnt;
    u8 pad3B7C[4];
    f32 sintab[91];
} Scene_c024_01E015D0;

static void func_01E015D0_c024(Scene_c024_01E015D0 *g, s32 unused, Pkt_c024_01E015D0 *p __attribute__((aligned(8))), s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c024_01E015D0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern Vec4f *func_001F9D30(s32);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_001E11B0(s32, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_00106B50(void *, void *);
    extern void func_00106E90(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, void *);
    extern s32 func_001A23B0(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f v[4];
    f32 rm[4];
    s32 a[4];
    f32 m[16];
    f32 off[4];
    f32 rot[4];
    Vec4f pos;
    Vec4f *c;
    Obj_c024_01E015D0 *o;
    s32 i;
    s32 j;
    s16 n;
    f32 ox;
    f32 oy;
    f32 oz;

    n = 0;
    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(g->col);
        p->v[1].c = func_00107740(g->col);
        p->v[2].c = func_00107740(g->col);
        p->v[3].c = func_00107740(g->col);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        func_0020EB40(m);
        c = func_001F9D30(0);
        func_00205C40((s32)rot);
        pos = *c;
        func_001F5BD0(func_001F5380(), off);
        func_001E11B0(func_001F5380() >> 8, func_001F5380() & 0xF, off);
        ox = off[0];
        oy = off[1];
        oz = off[2];
        if (g->state > 2) {
            for (i = 0; i < 10; i++) {
                for (j = 0; j < 24; j++) {
                    o = &g->obj[n];
                    pos = g->pt[i][j];
                    if (g->cnt > n) {
                        v[0].x = g->pt[i][j].x - pos.x;
                        v[0].z = g->pt[i][j].z - pos.z;
                        if (j != 23) {
                            v[1].x = g->pt[i][j + 1].x - pos.x;
                            v[1].z = g->pt[i][j + 1].z - pos.z;
                        } else {
                            v[1].x = g->pt[i][0].x - pos.x;
                            v[1].z = g->pt[i][0].z - pos.z;
                        }
                        v[2].x = g->pt[i + 1][j].x - pos.x;
                        v[2].z = g->pt[i + 1][j].z - pos.z;
                        if (j != 23) {
                            v[3].x = g->pt[i + 1][j + 1].x - pos.x;
                            v[3].z = g->pt[i + 1][j + 1].z - pos.z;
                        } else {
                            v[3].x = g->pt[i + 1][0].x - pos.x;
                            v[3].z = g->pt[i + 1][0].z - pos.z;
                        }
                        v[0].y = g->pt[i][j].y - pos.y;
                        if (j != 23) {
                            v[1].y = g->pt[i][j + 1].y - pos.y;
                        } else {
                            v[1].y = g->pt[i][0].y - pos.y;
                        }
                        v[2].y = g->pt[i + 1][j].y - pos.y;
                        if (j != 23) {
                            v[3].y = g->pt[i + 1][j + 1].y - pos.y;
                        } else {
                            v[3].y = g->pt[i + 1][0].y - pos.y;
                        }
                        pos.x *= g->sc[0];
                        pos.y *= g->sc[1];
                        pos.z *= g->sc[2];
                        pos.x += o->x;
                        pos.y += o->y;
                        pos.z += o->z;
                        pos.x += ox;
                        pos.y += oy;
                        pos.z += oz;
                        if (g->t > 35 && g->state > 4) {
                            a[1] = o->ry;
                            func_00108950(&v[0], a, 0, g->sintab);
                            func_00108950(&v[1], a, 0, g->sintab);
                            func_00108950(&v[2], a, 0, g->sintab);
                            func_00108950(&v[3], a, 0, g->sintab);
                            a[0] = o->rx;
                            func_00108950(&v[0], a, 1, g->sintab);
                            func_00108950(&v[1], a, 1, g->sintab);
                            func_00108950(&v[2], a, 1, g->sintab);
                            func_00108950(&v[3], a, 1, g->sintab);
                        }
                        func_00106E90(&v[0], g->sc);
                        func_00106E90(&v[1], g->sc);
                        func_00106E90(&v[2], g->sc);
                        func_00106E90(&v[3], g->sc);
                        func_00106B50(&v[0], &pos);
                        func_00106B50(&v[1], &pos);
                        func_00106B50(&v[2], &pos);
                        func_00106B50(&v[3], &pos);
                        if (func_00205630(v, 0x70000000, 0, p, &g->depth) != 0) {
                            func_002075F0(p, g->ot, func_001A23B0(g->depth));
                        }
                    }
                    if (g->t == 34) {
                        o->vx = g->pt[i][j].x / 15.0f;
                        o->vy = g->pt[i][j].y / 15.0f;
                        o->vz = g->pt[i][j].z / 15.0f;
                    } else if (g->t > 35 && g->state > 4) {
                        o->x += o->vx;
                        o->y += o->vy;
                        o->z += o->vz;
                        o->rx += 12;
                        o->ry += 12;
                    }
                    n++;
                }
            }
        }
        if (g->t > 35 && g->state > 4 && g->col[3] > 16) {
            g->col[3] -= 13;
        }
    }
}

/* shape c024:01E01CD0, 210 insns (C024_MAP_ATTACK_1): builds a 10x24 point bowl at ctx+0x150: rings of radius 100
   shrinking by 10 (at least 1), 15 degrees between points; each ring is shifted by a random walk (-5..4 a ring on x and
   z) and each point jittered by up to the ring's spread (70, -7 a ring, 1 from the ninth ring), centred; heights rise
   by 20 a ring for the first eight rings, then by 3 */

typedef struct {
    f32 x, y, z, w;
} V_c024_01E01CD0;

typedef struct {
    u8 pad0[0x150];
    V_c024_01E01CD0 p[10][24];
} Ctx_c024_01E01CD0;

static void func_01E01CD0_c024(Ctx_c024_01E01CD0 *g) {
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    s32 i;
    s32 j;
    s16 a;
    s16 z;
    s16 r;
    s16 x;
    s16 w;
    s16 dx;
    s16 dz;
    s16 y;
    f32 t;

    a = 0;
    z = 0;
    r = 100;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 24; j++) {
            t = 3.1415927f * a / 180.0f;
            g->p[i][j].x = r * func_001A6898(t);
            g->p[i][j].z = r * func_001A6A88(t);
            a += 15;
        }
        r -= 10;
        a = 0;
        if (r <= 0) {
            r = 1;
        }
    }
    w = 70;
    x = 0;
    for (i = 0; i < 10; i++) {
        x += (s16)(func_0019A5C8() % 10 - 5);
        z += (s16)(func_0019A5C8() % 10 - 5);
        for (j = 0; j < 24; j++) {
            dx = func_0019A5C8() % w;
            dz = func_0019A5C8() % w;
            g->p[i][j].x += x + (dx - (w >> 1));
            g->p[i][j].z += z + (dz - (w >> 1));
        }
        if (i < 8) {
            w -= 7;
        }
        if (i == 8) {
            w = 1;
        }
        if (w <= 0) {
            w = 1;
        }
    }
    y = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 24; j++) {
            g->p[i][j].y = y;
        }
        if (i < 8) {
            y += 20;
        } else {
            y += 3;
        }
    }
}

/* shape c024:01E02020, 319 insns: C024PAINT_RAIN5, a flat diamond on the ground: mode 0 builds the packet (texture
   page 0x99 frame b24, the effect's colour in all four corners); other modes stand on the model's root (y + h16),
   take corners at angles 135/45/225/315 of radius r + 5 and push them all r out along the heading ang + 15, then draw
   at the context depth */

typedef struct {
    u8 c[4];
    f32 q;
    u64 uv;
    u64 xyz;
} Vtx_c024_01E02020;

typedef struct {
    u8 pad0[0x10];
    Vtx_c024_01E02020 v[4];
} Pkt_c024_01E02020;

typedef struct {
    u8 pad0[4];
    s32 ry;
    u8 pad8[0xE];
    s16 dy;
    u8 pad18[0xC];
    s8 frame;
    u8 pad25;
    s16 r;
    s16 ang;
    u8 col[4];
} Fx_c024_01E02020;

typedef struct {
    u8 pad0[0x40];
    f32 m[16];
    u8 pad80[0x10C - 0x80];
    void *tex;
    u8 scale[0x3B2C - 0x110];
    s32 ot;
    u8 pad3B30[0x3B48 - 0x3B30];
    f32 depth;
    u8 pad3B4C[0x3B80 - 0x3B4C];
    u8 sin[4];
} Ctx_c024_01E02020;

static void func_01E02020_c024(Ctx_c024_01E02020 *g, Fx_c024_01E02020 *o, Pkt_c024_01E02020 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107710(void *, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_001F53B0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_00205C40(void *);
    extern void func_0020C940(void *, s32, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f q[4];
    s16 rect[8];
    f32 m1[16];
    Vec4f pos;
    s32 rot[4];

    if (mode == 0) {
        func_00106080(rect, 0x99, o->frame, 0);
        func_00109270(p, 0, 0);
        func_00107710(p->v[0].c, o->col);
        p->v[0].q = 1.0f;
        func_00107710(p->v[1].c, o->col);
        p->v[1].q = 1.0f;
        func_00107710(p->v[2].c, o->col);
        p->v[2].q = 1.0f;
        func_00107710(p->v[3].c, o->col);
        p->v[3].q = 1.0f;
        func_00108500(p, rect, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_001F53B0(0, &pos);
    func_0020EB40(g->m);
    func_00205C40(rot);
    rot[0] = 0;
    rot[1] = o->ry;
    rot[2] = 0;
    pos.y += o->dy;
    func_0020C940(m1, 0, g->scale, &pos);
    func_0020BC00(g->m, m1);
    q[0].x = (o->r + 5) * func_00108030(g->sin, 0x87, 1);
    q[0].y = (o->r + 5) * func_00108030(g->sin, 0x87, 0);
    q[0].z = 0.0f;
    q[1].x = (o->r + 5) * func_00108030(g->sin, 0x2D, 1);
    q[1].y = (o->r + 5) * func_00108030(g->sin, 0x2D, 0);
    q[1].z = 0.0f;
    q[2].x = (o->r + 5) * func_00108030(g->sin, 0xE1, 1);
    q[2].y = (o->r + 5) * func_00108030(g->sin, 0xE1, 0);
    q[2].z = 0.0f;
    q[3].x = (o->r + 5) * func_00108030(g->sin, 0x13B, 1);
    q[3].y = (o->r + 5) * func_00108030(g->sin, 0x13B, 0);
    q[3].z = 0.0f;
    q[0].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[0].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    q[1].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[1].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    q[2].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[2].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    q[3].x += o->r * func_00108030(g->sin, o->ang + 15, 1);
    q[3].z += o->r * func_00108030(g->sin, o->ang + 15, 0);
    if (func_00205630(q, 0x70000000, g->m, p, &g->depth) != 0) {
        func_002075F0(p, g->ot, (u32)g->depth);
    }
}
