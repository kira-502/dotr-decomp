#include "common.h"

/* shape c027:01E00080, 129 insns: scene step: red scene colour, 0x2366 20, 0x236E 130; on the first frame it sets the
   scene colours, eight 160.0 widths and four corner points (+-100) and spawns the node chain (c027:01E008B0 with
   handler 0x1E00290); every third frame, once 0x22D8 passes 16 and 0x2368 is set, six ribbon nodes at the origin
   with random turns (c027:01E00AA0, handler 0x1E003A0) */

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x2248];
    s32 w22D8;
    u8 col[4];
    u8 pad22E0[8];
    s32 head;
    u8 pad22EC[4];
    s32 w22F0;
    u8 pad22F4[0x1C];
    f32 width[8];
    u8 pad2330[0x1E];
    s16 h234E;
    u8 pad2350[6];
    s16 corner;
    u8 pad2358[4];
    s16 t;
    u8 pad235E[8];
    s16 h2366;
    s16 h2368;
    u8 pad236A[4];
    s16 h236E;
    u8 pad2370[2];
    u8 c2372[3];
    u8 pad2375;
    u8 c2376[3];
} Scene_c027_01E00080;

static void func_01E00080_c027(Scene_c027_01E00080 *g) {
    extern void c027_01E00290();
    extern void c027_01E003A0();
    extern void c027_01E008B0(Scene_c027_01E00080 *, void *);
    extern void c027_01E00AA0(Scene_c027_01E00080 *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->h2366 = 20;
    g->h236E = 0x82;
    g->t++;
    if (g->t == 1) {
        g->h2368 = 0;
        g->c2372[0] = 0x40;
        g->c2372[1] = 0x20;
        g->c2372[2] = 0x30;
        g->c2376[0] = 0xC0;
        g->c2376[1] = 0;
        g->c2376[2] = 0;
        g->col[0] = 0x30;
        g->col[1] = 0x30;
        g->col[2] = 0x30;
        g->col[0] = 0x80;
        g->col[1] = 0;
        g->col[2] = 0;
        g->col[3] = 0;
        for (i = 0; i < 8; i++) {
            g->width[i] = 160.0f;
        }
        g->corner = 0;
        func_00106DD0(&g->pos, -100.0f, 100.0f, 0.0f);
        g->corner = 1;
        func_00106DD0(&g->pos, 100.0f, 100.0f, 0.0f);
        g->corner = 2;
        func_00106DD0(&g->pos, -100.0f, -100.0f, 0.0f);
        g->corner = 3;
        func_00106DD0(&g->pos, 100.0f, -100.0f, 0.0f);
        c027_01E008B0(g, c027_01E00290);
    }
    if (g->t % 3 == 1 && g->w22D8 > 16 && g->h2368 != 0) {
        for (i = 0; i < 6; i++) {
            g->head = 0;
            g->w22F0 = 0;
            g->h234E = func_0019A5C8() % 360;
            func_00106DD0(&g->pos, 0.0f, 0.0f, 0.0f);
            c027_01E00AA0(g, c027_01E003A0);
        }
    }
}

/* shape c027:01E00290, 66 insns: 0x6A..0x6E = 360; while the game counter at 0x22D8 is below 6 both alphas fade by
   0x30 (the second ends it), otherwise both grow by 0x10 (below 0x80) and a full second alpha sets the game flag
   0x2368; after game step 0x235C passes 12 the game colour at 0x2372 dims by 10 (above 0x30), 0x2373 = 0 and 0x2374
   grows by 10 (below 0x50); the effect stops below counter 2 */

typedef struct {
    u8 pad0[0x22D8];
    s32 count;
    u8 pad22DC[0x80];
    s16 step;
    u8 pad235E[0xA];
    s16 flag;
    u8 pad236A[8];
    u8 c2372;
    u8 c2373;
    u8 c2374;
} Game_c027_01E00290;

typedef struct {
    u8 pad0[0x60];
    u8 col[4];
    u8 col2[4];
    s16 mode;
    s16 f6A;
    s16 f6C;
    s16 f6E;
} Fx_c027_01E00290;

static s32 func_01E00290_c027(Game_c027_01E00290 *g, Fx_c027_01E00290 *o) {
    o->f6A = 360;
    o->f6C = 360;
    o->f6E = 360;
    if (g->count < 6) {
        if (o->col[3] > 0x30) {
            o->col[3] -= 0x30;
        }
        if (o->col2[3] > 0x30) {
            o->col2[3] -= 0x30;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x10;
        }
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x10;
        }
        if (o->col2[3] >= 0x80) {
            g->flag = 1;
        }
    }
    if (g->step > 0xC) {
        if (g->c2372 > 0x30) {
            g->c2372 -= 10;
        }
        g->c2373 = 0;
        if (g->c2374 < 0x50) {
            g->c2374 += 10;
        }
    }
    if (g->count < 2) {
        o->mode = 0;
    }
    return 0;
}

/* shape c027:01E003A0, 176 insns: c027's ribbon node handler: while its delay (0x78) is 2+ it widens by 7 to 120 and
   counts down; at 1 it becomes the scene's head node and, below 120 wide, hands the scene its length, turn and corner
   and spawns the next node (c027:01E00AA0 with this handler); at 0 it fades by 32, passing its second colour to the
   node it points at once gone; every tick it wobbles, flickers between 0x30 and 0xB0 and fades by 16 while the scene
   count is under 10, else fades back in by 0x3A while still delayed */

typedef struct {
    u8 c[4];
} Rgba_c027_01E003A0;

typedef struct Node_c027_01E003A0 {
    u8 pad0[0xC];
    f32 fC;
    u8 pad10[4];
    f32 f14;
    u8 pad18[4];
    f32 f1C;
    u8 pad20[0x28];
    s16 h48;
    u8 pad4A[6];
    s32 w50;
    struct Node_c027_01E003A0 *next;
    u8 pad58[8];
    Rgba_c027_01E003A0 col;
    Rgba_c027_01E003A0 col2;
    s16 h68;
    u8 pad6A[8];
    s16 h72;
    u8 pad74[2];
    s16 h76;
    s16 h78;
    s16 h7A;
} Node_c027_01E003A0;

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x2248];
    s32 w22D8;
    u8 pad22DC[0xC];
    Node_c027_01E003A0 *head;
    u8 pad22EC[4];
    f32 len;
    u8 pad22F4[0x5A];
    s16 h234E;
    u8 pad2350[6];
    s16 corner;
} Scene_c027_01E003A0;

static s32 func_01E003A0_c027(Scene_c027_01E003A0 *g, Node_c027_01E003A0 *o) {
    extern void c027_01E00AA0(Scene_c027_01E003A0 *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_001076F0(void *, s32, s32, s32);
    Node_c027_01E003A0 *p;
    f32 x, y, w;

    if (o->h78 > 1) {
        if (o->f14 < 120.0f) {
            o->f14 += 7.0f;
        }
        o->h78--;
    } else if (o->h78 == 1) {
        if (o->f14 < 120.0f) {
            g->head = o;
            g->len = o->h72;
            g->h234E = o->h48;
            x = w = y = 0.0f;
            func_00106DD0(&g->pos, x, y, w);
            g->corner = o->h7A;
            c027_01E00AA0(g, func_01E003A0_c027);
        }
        o->h78 = 0;
    } else if (o->h78 == 0) {
        if (o->col.c[3] > 32) {
            o->col.c[3] -= 32;
        } else {
            p = o->next;
            if (p != 0) {
                p->col = o->col2;
                p->w50 = 0;
            }
            o->h68 = 0;
        }
        if (o->col2.c[3] > 32) {
            o->col2.c[3] -= 32;
        }
    }
    o->f1C = func_0019A5C8() % 40 - 20;
    o->fC = func_0019A5C8() % 20 - 10;
    if (o->h76 != 0) {
        func_001076F0(&o->col, 0x30, 0x30, 0);
        func_001076F0(&o->col2, 0x30, 0x30, 0);
        o->h76 = 0;
    } else {
        func_001076F0(&o->col, 0xB0, 0xB0, 0);
        func_001076F0(&o->col2, 0xB0, 0xB0, 0);
        o->h76 = 1;
    }
    if (g->w22D8 < 10) {
        if (o->col.c[3] > 16) {
            o->col.c[3] -= 16;
        }
        if (o->col2.c[3] > 16) {
            o->col2.c[3] -= 16;
        } else {
            o->h68 = 0;
        }
    } else if (o->h78 != 0) {
        if (o->col.c[3] < 0xB0) {
            o->col.c[3] += 0x3A;
        }
        if (o->col2.c[3] < 0xB0) {
            o->col2.c[3] += 0x3A;
        }
    }
    return 0;
}

/* shape c027:01E00660, 147 insns: c027's scene manager: with a scene id (>= 0) it clears the scene, builds the sine table
   for 0..90 degrees, keeps the id, sets the 44-frame countdown and loads texture 15; otherwise it runs the module's step,
   every live node's update callback, spins the shared rotation, and draws every live node twice with the camera point
   (func_001F9D30) and scale 0.5/0.2/0.5; it returns 8 once the countdown runs out */

typedef struct Node_c027_01E00660 {
    u8 pad0[0x58];
    void (*draw)(void *, struct Node_c027_01E00660 *, void *, s32);
    void (*update)(void *, struct Node_c027_01E00660 *);
    u8 pad60[8];
    s16 used;
    u8 pad6A[0x12];
} Node_c027_01E00660;

typedef struct {
    u8 m0[0x40];
    u8 m[0x40];
    u8 pad80[0x10];
    s32 tex[16];
    s32 rot[4];
    f32 sc[4];
    Node_c027_01E00660 node[70];
    s32 count;
    u8 pad22DC[8];
    s32 ot;
    u8 pad22E8[0x70];
    s16 id;
    u8 pad235A[0x4A];
    f32 sintab[91];
} Scene_c027_01E00660;

static s32 func_01E00660_c027(s32 arg0, s32 id) {
    Scene_c027_01E00660 *g = (Scene_c027_01E00660 *)arg0;
    extern void func_00195108(void *, s32);
    extern void c027_01E00080(Scene_c027_01E00660 *, s32);
    extern f32 func_001A6A88(f32);
    extern s32 func_00202BF0(s32, s32);
    extern f32 *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    s32 n;
    f32 v[4];
    u8 buf[0x90];
    void (*draw)(void *, Node_c027_01E00660 *, void *, s32);
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x2510);
        for (; n < 91; n++) {
            g->sintab[n] = func_001A6A88(3.1415927f * n / 180.0f);
        }
        g->id = id;
        g->count = 44;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        return 0;
    }
    c027_01E00080(g, 0);
    for (i = 0; i < 70; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].update != 0) {
                g->node[i].update(g, &g->node[i]);
            }
        }
    }
    v[0] = v[1] = v[2] = 0.0f;
    v[1] = 50.0f;
    *(Vec4f *)v = *(Vec4f *)func_001F9D30(0);
    func_00205C40((s32)g->rot);
    g->rot[0] += 0x4000;
    g->sc[1] = 0.2f;
    g->sc[0] = 0.5f;
    g->sc[2] = 0.5f;
    for (i = 0; i < 70; i++) {
        if (g->node[i].used != 0) {
            n++;
            func_0020EB40(g->m);
            func_0020C940(g, g->sc, g->rot, v);
            func_0020BC00(g->m, g);
            draw = g->node[i].draw;
            if (draw != 0) {
                draw(g, &g->node[i], buf, 0);
                draw(g, &g->node[i], buf, 1);
            }
        }
    }
    if (--g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape c027:01E008B0, 123 insns: take the first free node of 70 (0x7C bytes at ctx+0xF0), mark it with its index + 1,
   colour both from the scene colour at ctx+0x22DC, clear 0x72/0x74, random turns 0..179 and 0..359, three random
   +-30 speeds, handler shape c027:01E00C50 and the argument; the scene keeps it as its last node */

typedef struct {
    u8 pad0[0x30];
    f32 vx, vy, vz;
    u8 pad3C[0x1C];
    s32 fn;
    s32 arg;
    u8 col[4];
    u8 col2[4];
    s16 used;
    u8 pad6A[2];
    s16 h6C;
    s16 h6E;
    u8 pad70[2];
    s16 h72;
    s16 h74;
    u8 pad76[6];
} Node_c027_01E008B0;

typedef struct {
    u8 pad0[0xF0];
    Node_c027_01E008B0 node[70];
    u8 padEnd[0x22DC - 0xF0 - 70 * 0x7C];
    u8 col[4];
    u8 pad22E0[8];
    Node_c027_01E008B0 *head;
} Ctx_c027_01E008B0;

static void func_01E008B0_c027(Ctx_c027_01E008B0 *g, s32 arg) {
    extern void c027_01E00C50();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;
    Node_c027_01E008B0 *s;

    s = NULL;
    for (i = 0; i < 70; i++) {
        if (g->node[i].used == 0) {
            s = &g->node[i];
            func_00195108(s, 0x7C);
            g->node[i].used = i + 1;
            i = 70;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->col[0], g->col[1], g->col[2]);
        s->col[3] = g->col[3];
        func_001076F0(s->col2, g->col[0], g->col[1], g->col[2]);
        s->col2[3] = g->col[3];
        s->h72 = 0;
        s->h74 = 0;
        s->h6C = func_0019A5C8() % 180;
        s->h6E = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 == 0) {
            s->vx = 30.0f;
        } else {
            s->vx = -30.0f;
        }
        if (func_0019A5C8() % 2 == 0) {
            s->vy = 30.0f;
        } else {
            s->vy = -30.0f;
        }
        if (func_0019A5C8() % 2 == 0) {
            s->vz = 30.0f;
        } else {
            s->vz = -30.0f;
        }
        s->fn = (s32)c027_01E00C50;
        s->arg = arg;
        g->head = s;
    }
}

/* shape c027:01E00AA0, 105 insns: take the first free ribbon node of 70 (0x7C bytes at ctx+0xF0), mark it with its index + 1, colour it red (alpha 0), copy the scene point, link it after the scene's last node (starting from its position), give it the scene ids, three turns (fptosi of ctx+0x22F0..F8), handler shape c027:01E01930 and the argument */

typedef struct {
    f32 x, y, z, w;
} V4_c027_01E00AA0;

typedef struct Node_c027_01E00AA0 {
    f32 f0, f4, f8;
    u8 padC[4];
    f32 f10, f14, f18;
    u8 pad1C[4];
    V4_c027_01E00AA0 pos;
    u8 pad30[0x18];
    s32 w48;
    u8 pad4C[4];
    struct Node_c027_01E00AA0 *prev;
    struct Node_c027_01E00AA0 *next;
    s32 fn;
    s32 arg;
    u8 col[4];
    u8 col2[4];
    s16 used;
    u8 pad6A[6];
    s16 h70;
    s16 h72;
    s16 h74;
    s16 h76;
    s16 h78;
    s16 h7A;
} Node_c027_01E00AA0;

typedef struct {
    u8 pad0[0x80];
    V4_c027_01E00AA0 pos;
    u8 pad90[0x60];
    Node_c027_01E00AA0 node[70];
    u8 padEnd[0x22E8 - 0xF0 - 70 * 0x7C];
    Node_c027_01E00AA0 *head;
    u8 pad22EC[4];
    f32 rx, ry, rz;
    u8 pad22FC[0x52];
    s16 h234E;
    u8 pad2350[2];
    s16 h2352;
    u8 pad2354[2];
    s16 h2356;
} Ctx_c027_01E00AA0;

static void func_01E00AA0_c027(Ctx_c027_01E00AA0 *g, s32 arg) {
    extern void c027_01E01930();
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s16 func_001A22C0(f32);
    s16 i;
    Node_c027_01E00AA0 *s;
    Node_c027_01E00AA0 *q;

    s = NULL;
    for (i = 0; i < 70; i++) {
        if (g->node[i].used == 0) {
            s = &g->node[i];
            func_00195108(s, 0x7C);
            g->node[i].used = i + 1;
            i = 70;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, 0x80, 0, 0);
        s->col[3] = 0;
        func_001076F0(s->col2, 0x80, 0, 0);
        s->col2[3] = 0;
        s->pos = g->pos;
        s->prev = g->head;
        q = s->prev;
        if (q != NULL) {
            q->next = s;
            s->f0 = s->f10 = q->f10;
            s->f4 = s->f14 = q->f14;
            s->f8 = s->f18 = q->f18;
        }
        s->w48 = g->h234E;
        s->h72 = func_001A22C0(g->rx);
        s->h74 = func_001A22C0(g->ry);
        s->h70 = func_001A22C0(g->rz);
        s->h76 = g->h2352;
        s->h7A = g->h2356;
        s->prev = g->head;
        s->h78 = 4;
        s->fn = (s32)c027_01E01930;
        s->arg = arg;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c027", func_01E00C50_c027);

/* shape c027:01E01930 (C027PAINT_RAIN3), 314 insns, 1 copy: draw one link of c027's rain curtain: mode 0 builds the
   4-vertex packet (frame 0x96, near colours from the link, alpha 0 at a free end; far colours from the next link or
   the link's own at alpha 10); otherwise (an else, not an early return) the curtain hangs under the model's joint: a
   12-wide quad from the link to the next one (or its own base), 30 deep, turned by the link's rotation and lifted 30
   (the 30.0f through a block local), depth-tested */

typedef struct {
    u8 r, g, b, a;
} Col_c027_01E01930;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c027_01E01930;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad4;
    u64 regs;
    struct {
        Rgbaq_c027_01E01930 c;
        u64 uv;
        u64 xyz;
    } v[4];
} Pkt_c027_01E01930;

typedef struct Link_c027_01E01930 {
    f32 x0;
    f32 y4;
    u8 pad8[4];
    f32 xC;
    f32 x10;
    f32 y14;
    u8 pad18[4];
    f32 x1C;
    u8 pad20[0x20];
    s32 rot[4];
    struct Link_c027_01E01930 *next;
    s32 f54;
    u8 pad58[8];
    Col_c027_01E01930 c60;
    Col_c027_01E01930 c64;
} Link_c027_01E01930;

typedef struct {
    u8 pad0[0xCC];
    s32 tex;
    u8 padD0[0x2214];
    s32 ot;
    u8 pad22E8[0x48];
    f32 dep;
    u8 pad2334[0x70];
    u8 table[1];
} Scene_c027_01E01930;

static void func_01E01930_c027(Scene_c027_01E01930 *g, Link_c027_01E01930 *e, Pkt_c027_01E01930 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern Rgbaq_c027_01E01930 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern Vec4f *func_001F9D30(s32);
    extern void func_0020EB40(void *);
    extern s32 func_001F5380(void);
    extern void func_001F5BD0(s32, void *);
    extern void func_00205C40();
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Link_c027_01E01930 *q = e->next;
    Vec4f quad[4];
    f32 rm[4];
    f32 m[16];
    f32 m2[16];
    s32 rot[4];
    Vec4f cp;
    Vec4f t;
    Col_c027_01E01930 c;
    s32 i;
    s32 h;
    f32 w;

    if (mode == 0) {
        func_00106080(rm, 0x96, 0, rm);
        p->count = 0x34;
        p->tag = 0xC;
        p->regs = ((u64)0x4214 << 32) | 0x21421421;
        p->pad4 = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0xB0 << 32) | 0x48);
        if (e->f54 == 0) {
            c = e->c60;
            c.a = 0;
            p->v[0].c = func_00107740(&c);
            p->v[1].c = func_00107740(&c);
        } else {
            p->v[0].c = func_00107740(&e->c60);
            p->v[1].c = func_00107740(&e->c60);
        }
        if (q != 0) {
            p->v[2].c = func_00107740(&q->c64);
            p->v[3].c = func_00107740(&q->c64);
        } else {
            c = e->c60;
            c.a = 10;
            p->v[2].c = func_00107740(&c);
            p->v[3].c = func_00107740(&c);
        }
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        cp = *func_001F9D30(0);
        func_0020EB40(m);
        func_001F5BD0(func_001F5380(), &t);
        cp.x = t.x;
        cp.y = t.y;
        cp.z = t.z;
        func_00205C40(rot);
        func_0020C940(m2, 0, rot, &cp);
        func_0020BC00(m, m2);
        {
            f32 r = 30.0f;
            func_00106DD0(&cp, 0.0f, r, 0.0f);
        }
        w = 6.0f;
        for (i = 0; i < 1; i++) {
            quad[0].x = e->x1C + (e->x10 - w);
            quad[1].x = e->x1C + (e->x10 + w);
            if (q != 0) {
                quad[2].x = q->x1C + (q->x10 - w);
                quad[3].x = q->x1C + (q->x10 + w);
            } else {
                quad[2].x = e->xC + (e->x0 - w);
                quad[3].x = e->xC + (e->x0 + w);
            }
            quad[0].y = e->y14;
            quad[1].y = e->y14;
            if (q != 0) {
                h = q->y14;
            } else {
                h = e->y4;
            }
            quad[3].y = quad[2].y = (s16)h;
            quad[0].z = 30.0f;
            quad[2].z = 30.0f;
            quad[3].z = 30.0f;
            quad[1].z = 30.0f;
            func_00108950(&quad[0], e->rot, 2, g->table);
            func_00108950(&quad[1], e->rot, 2, g->table);
            func_00108950(&quad[2], e->rot, 2, g->table);
            func_00108950(&quad[3], e->rot, 2, g->table);
            quad[0].y += cp.y;
            quad[1].y += cp.y;
            quad[2].y += cp.y;
            quad[3].y += cp.y;
            if (func_00205630(quad, 0x70000000, m, p, &g->dep) != 0) {
                func_002075F0(p, g->ot, (u32)g->dep);
            }
        }
    }
}

