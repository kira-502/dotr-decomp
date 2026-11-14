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

static void func_01E00080_b490(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b490:01E00920, 177 insns: b361:01E00920's scene script for b490: red tint, counts g+0x8B56; from tick 35 to
   180 it spawns 0x1E01260 each tick; on tick 35 a 0x1E01D50, a 0x1E00D90 at the joint (g+0x8B38) and a 0x1E01080;
   from 35 to 220 6..14 sparks around the joint (x +-30, y -20..39, z +-15); it tracks the joint into g+0x8AD0 */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x8874];
    Vec4f v;
    u8 pad5F20[0x24];
    u8 col[4];
    u8 pad5F48[0x30];
    s16 joint;
    u8 pad5F7A[0x1C];
    s16 tick;
} Ctx_b490_01E00920;

static void func_01E00920_b490(Ctx_b490_01E00920 *g) {
    extern void b490_01E00BF0();
    extern void b490_01E00D90();
    extern void b490_01E01080();
    extern void b490_01E01260();
    extern void b490_01E01D50();
    extern void b490_01E02670(Ctx_b490_01E00920 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    f32 v[4];
    s32 i;
    s32 n;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick >= 35 && g->tick < 181) {
        b490_01E02670(g, b490_01E01260, 0);
    }
    if (g->tick == 35) {
        b490_01E02670(g, b490_01E01D50, 0);
    }
    if (g->tick == 35) {
        func_001F5620(func_001F53A0(), g->joint, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        b490_01E02670(g, b490_01E00D90, 0);
    }
    if (g->tick == 35) {
        b490_01E02670(g, b490_01E01080, 0);
    }
    if (g->tick >= 35 && g->tick < 221) {
        func_001F5620(func_001F53A0(), g->joint, v);
        n = func_0019A5C8() % 9 + 6;
        for (i = 0; i < n; i++) {
            g->x = v[0] + func_0019A5C8() % 60 - 30.0f;
            g->y = v[1] + func_0019A5C8() % 60 - 20.0f;
            g->z = v[2] + func_0019A5C8() % 30 - 15.0f;
            b490_01E02670(g, b490_01E00BF0, 0);
        }
    }
    func_001F5620(func_001F53A0(), g->joint, &g->v);
}

/* shape b490:01E00BF0, 102 insns: a blinking white streak (size 50, 50/8 turns, random tilt and angle, frame 2) sliding 10 a tick on z (direction from the scene flag): alpha 0x80 for 12 ticks, then out by 15 and ends */

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x1C];
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
} Obj_b490_01E00BF0;

typedef struct {
    u8 pad[0x8B52];
    s16 flip;
} Game_b490_01E00BF0;

static s32 func_01E00BF0_b490(Game_b490_01E00BF0 *g, Obj_b490_01E00BF0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 50.0f;
        o->w20 = 50;
        o->w24 = 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h50 = func_0019A5C8() % 180;
        o->h5A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->t < 12) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->kind = 2;
    if (g->flip != 0) {
        o->f18 -= 10.0f;
    } else {
        o->f18 += 10.0f;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    } else {
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
    }
    o->t++;
    return 0;
}

/* shape b490:01E00D90, 64 insns: an orange glow on the model joint: set up once (scale 630, size 10x10), fades in by
   0x40 to 0xC0 for 0xAA frames, then out by 10 until it ends; placed at the joint each frame */

typedef struct {
    u8 pad0[0x8B38];
    s16 joint;
} Game_b490_01E00D90;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x28];
    f32 scale;
    u8 pad4C[8];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b490_01E00D90;

static s32 func_01E00D90_b490(Game_b490_01E00D90 *g, Obj_b490_01E00D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->state == 1) {
        o->scale = 630.0f;
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x20, 0x10, 0);
        o->w = 0xA;
        o->h = 0xA;
        o->state = 2;
        o->c1[3] = 0x10;
    }
    if (o->t < 0xAA) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->t++;
    func_001F5620(func_001F53A0(), g->joint, &o->pos);
    return 0;
}

/* shape b490:01E00E90, 122 insns: a scene light at 0x8A80: on start colour/size 128/4/2/0, height 0/120/0 and the effect's
   position as floats; its strength 0x8AA8 rises by 0.2 up to 1 (then 0x50 = 1) and falls by 0.1 until it ends
   the effect; func_001F6C10 gets the light (or 0 once ended); it also ends when the light's 0x8B00 flag is 1 */

typedef struct {
    f32 a[4];
    f32 pos[3];
    u8 pad1C[4];
    f32 b[3];
    u8 pad2C[0x54];
    s32 done;
} Light_b490_01E00E90;

typedef struct {
    u8 pad0[0x8A80];
    Light_b490_01E00E90 light;
} Game_b490_01E00E90;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x4A];
    s16 f50;
    u8 pad52[6];
    s16 mode;
} Fx_b490_01E00E90;

static s32 func_01E00E90_b490(Game_b490_01E00E90 *g, Fx_b490_01E00E90 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a[0] = 128.0f;
        g->light.a[1] = 4.0f;
        g->light.a[2] = 2.0f;
        g->light.a[3] = 0.0f;
        g->light.b[0] = 0.0f;
        g->light.b[1] = 120.0f;
        g->light.b[2] = 0.0f;
        g->light.pos[0] = o->x;
        g->light.pos[1] = o->y;
        g->light.pos[2] = o->z;
        o->mode = 2;
        o->f50 = 0;
    }
    if (o->f50 == 0) {
        if (g->light.b[2] < 1.0f) {
            g->light.b[2] += 0.2f;
        } else {
            o->f50 = 1;
        }
    } else if (g->light.b[2] > 0.1f) {
        g->light.b[2] -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->light.done == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b490:01E01080, 55 insns: volume fade by game state (b124:01E01A30 layout at 0x50): state at 0x8B00 limit 0x14, down 10 to 0x30,
   up 10 to 0x80 where the fade ends; counts its frames */

typedef struct {
    u8 pad[0x8B00];
    s32 state;
} Game_b490_01E01080;

typedef struct {
    u8 pad[0x50];
    s16 vol;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fade_b490_01E01080;

static s32 func_01E01080_b490(Game_b490_01E01080 *g, Fade_b490_01E01080 *o) {
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
    }
    o->t++;
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

typedef struct {
    u8 r, g, b, a;
} Col_b361_01E01040;

typedef struct {
    u8 pad00[0x50];
    s16 h50;
    u8 pad52[6];
    s16 h58;
    u8 pad5A[9];
    u8 b63;
} Obj_b361_01E01040;

extern Col_b361_01E01040 D_01E02E00_b490;
extern Col_b361_01E01040 D_01E02E08_b490;

static s32 func_01E01160_b490(s32 unused, Obj_b361_01E01040 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    Col_b361_01E01040 c0;
    Col_b361_01E01040 c1;

    *(f32 *)(u32)&c0 = *(f32 *)(u32)&D_01E02E00_b490;
    *(f32 *)(u32)&c1 = *(f32 *)(u32)&D_01E02E08_b490;
    if (o->h58 == 1) {
        o->h50 = 0;
        o->b63 = 0;
    }
    if (o->h50 == 0) {
        if (o->b63 < 0xC0) {
            o->b63 += 0x1E;
        } else {
            o->h50 = 1;
        }
    } else {
        if (o->b63 > 0x40) {
            o->b63 -= 0x1E;
        } else {
            o->h50 = 0;
        }
    }
    c0.b = o->b63;
    c1.b = o->b63;
    c0.g = o->b63;
    c1.g = o->b63;
    c0.r = o->b63;
    c1.r = o->b63;
    func_001F7170(3, 1, &c0, &c1, 1);
    return 0;
}

/* shape b490:01E01260 (B490_OBJ_MOVE_202_), 697 insns, 1 copy: the b361:01E01140 overlay: a grey
   (0x38) scrolling full-screen overlay in the scene packet (0x8B14): four passes, each projects the scene point (z
   +-60 by side 0x8B52) onto one corner and places the other three from the scroll offsets (x + 0x940 / 0x6C0 - x, y +
   0x8E0 / 0x720 - y, *16 - 8), far z, texture coords from the screen position clamped to 640 x 480; offsets grow by
   20..34 a tick, alpha down by 19 once running, ends at scene frame 184. Built under opt_propagation off with the
   zero re-set per vertex block and the bottom corners on their own s/t pair */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b490_01E01260;

typedef struct {
    u64 x : 16, y : 16, z : 24, f : 8;
} Xyz_b490_01E01260;

typedef struct {
    Rgbaq_b490_01E01260 c;
    f32 s, t;
    Xyz_b490_01E01260 p;
} Vtx_b490_01E01260;

typedef struct {
    u8 hdr[0x10];
    Vtx_b490_01E01260 v[4];
} Pkt_b490_01E01260;

typedef struct {
    u8 pad0[0x8AD0];
    f32 pos[3];
    u8 pad8ADC[0x8B14 - 0x8ADC];
    Pkt_b490_01E01260 *pk;
    u8 pad8B18[4];
    s32 z;
    u8 pad8B20[0x8B3C - 0x8B20];
    s16 joint;
    u8 pad8B3E[0x8B52 - 0x8B3E];
    s16 flag;
    u8 pad8B54[2];
    s16 t;
} Scene_b490_01E01260;

typedef struct {
    u8 pad0[8];
    s16 x, y;
    u8 padC[0x54 - 0xC];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
} Obj_b490_01E01260;

#pragma opt_propagation off

static s32 func_01E01260_b490(Scene_b490_01E01260 *g, Obj_b490_01E01260 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern Rgbaq_b490_01E01260 func_00107740(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s32 func_00205440(void *, void *, void *, void *);
    extern void func_002075F0(s32, s32, s32);
    extern s32 func_0019A5C8(void);
    Vec4f d;
    Vec4f p[4];
    Vec4f j;
    s16 i;
    f32 z;
    f32 s;
    f32 t;
    f32 u;
    f32 v;

    if (o->state == 1) {
        func_001076F0(o->col, 0x38, 0x38, 0x38);
        o->col[3] = 0x80;
        o->x = 0;
        o->y = 0;
        o->state = 2;
    }
    g->pk->v[0].c = func_00107740(o->col);
    g->pk->v[1].c = func_00107740(o->col);
    g->pk->v[2].c = func_00107740(o->col);
    g->pk->v[3].c = func_00107740(o->col);
    p[0].x = g->pos[0];
    p[0].y = g->pos[1];
    p[0].z = g->pos[2];
    if (g->flag != 0) {
        p[0].z += 60.0f;
    } else {
        p[0].z -= 60.0f;
    }
    func_00205440(p, NULL, &g->pk->v[0].p, &g->z);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            func_001F5620(func_001F53A0(), g->joint, &j);
            p[0].x = g->pos[0];
            p[0].y = g->pos[1];
            p[0].z = g->pos[2];
            func_00205440(p, NULL, &g->pk->v[0].p, &d);
            g->pk->v[1].p.x = (o->x + 0x940) * 16 - 8;
            g->pk->v[1].p.y = g->pk->v[0].p.y;
            g->pk->v[2].p.x = g->pk->v[0].p.x;
            g->pk->v[2].p.y = (o->y + 0x8E0) * 16 - 8;
            g->pk->v[3].p.x = (o->x + 0x940) * 16 - 8;
            g->pk->v[3].p.y = (o->y + 0x8E0) * 16 - 8;
        }
        if (i == 1) {
            p[0].x = g->pos[0];
            p[0].y = g->pos[1];
            p[0].z = g->pos[2];
            func_00205440(p, NULL, &g->pk->v[1].p, &d);
            g->pk->v[0].p.x = (0x6C0 - o->x) * 16 - 8;
            g->pk->v[0].p.y = g->pk->v[1].p.y;
            g->pk->v[2].p.x = (0x6C0 - o->x) * 16 - 8;
            g->pk->v[2].p.y = (o->y + 0x8E0) * 16 - 8;
            g->pk->v[3].p.x = g->pk->v[1].p.x;
            g->pk->v[3].p.y = (o->y + 0x8E0) * 16 - 8;
        }
        if (i == 2) {
            p[0].x = g->pos[0];
            p[0].y = g->pos[1];
            p[0].z = g->pos[2];
            func_00205440(p, NULL, &g->pk->v[2].p, &d);
            g->pk->v[0].p.x = g->pk->v[2].p.x;
            g->pk->v[0].p.y = (0x720 - o->y) * 16 - 8;
            g->pk->v[1].p.x = (o->x + 0x940) * 16 - 8;
            g->pk->v[1].p.y = (0x720 - o->y) * 16 - 8;
            g->pk->v[3].p.x = (o->x + 0x940) * 16 - 8;
            g->pk->v[3].p.y = g->pk->v[2].p.y;
        }
        if (i == 3) {
            p[0].x = g->pos[0];
            p[0].y = g->pos[1];
            p[0].z = g->pos[2];
            func_00205440(p, NULL, &g->pk->v[3].p, &d);
            g->pk->v[0].p.x = (0x6C0 - o->x) * 16 - 8;
            g->pk->v[0].p.y = (0x720 - o->y) * 16 - 8;
            g->pk->v[1].p.x = g->pk->v[3].p.x;
            g->pk->v[1].p.y = (0x720 - o->y) * 16 - 8;
            g->pk->v[2].p.x = (0x6C0 - o->x) * 16 - 8;
            g->pk->v[2].p.y = g->pk->v[3].p.y;
        }
        g->pk->v[0].p.z = 0xFFFFFF;
        g->pk->v[0].p.f = 0;
        g->pk->v[1].p.z = 0xFFFFFF;
        g->pk->v[1].p.f = 0;
        g->pk->v[2].p.z = 0xFFFFFF;
        g->pk->v[2].p.f = 0;
        g->pk->v[3].p.z = 0xFFFFFF;
        g->pk->v[3].p.f = 0;
        z = 0.0f;
        s = 0x6BF8 - g->pk->v[0].p.x;
        t = 0x71F8 - g->pk->v[0].p.y;
        s /= -16.0f;
        t /= -16.0f;
        s -= z;
        t -= z;
        if (s < z) {
            s = z;
        }
        if (t < 0.0f) {
            t = 0.0f;
        }
        g->pk->v[0].s = s / 1024.0f;
        g->pk->v[0].t = t / 512.0f;
        z = 0.0f;
        s = 0x6BF8 - g->pk->v[1].p.x;
        t = 0x71F8 - g->pk->v[1].p.y;
        s /= -16.0f;
        t /= -16.0f;
        s -= z;
        t -= z;
        if (s > 640.0f) {
            s = 640.0f;
        }
        if (t < 0.0f) {
            t = 0.0f;
        }
        g->pk->v[1].s = s / 1024.0f;
        g->pk->v[1].t = t / 512.0f;
        z = 0.0f;
        u = 0x6BF8 - g->pk->v[2].p.x;
        v = 0x71F8 - g->pk->v[2].p.y;
        u /= -16.0f;
        v /= -16.0f;
        u -= z;
        v -= z;
        if (u < z) {
            u = z;
        }
        if (v > 480.0f) {
            v = 480.0f;
        }
        g->pk->v[2].s = u / 1024.0f;
        g->pk->v[2].t = v / 512.0f;
        z = 0.0f;
        u = 0x6BF8 - g->pk->v[3].p.x;
        v = 0x71F8 - g->pk->v[3].p.y;
        u /= -16.0f;
        v /= -16.0f;
        u -= z;
        v -= z;
        if (u > 640.0f) {
            u = 640.0f;
        }
        if (v > 480.0f) {
            v = 480.0f;
        }
        g->pk->v[3].s = u / 1024.0f;
        g->pk->v[3].t = v / 512.0f;
        func_002075F0((s32)g->pk, 0, 0);
    }
    o->x += (s16)((func_0019A5C8() >> 4) % 15 + 20);
    o->y += (s16)((func_0019A5C8() >> 4) % 15 + 20);
    if (o->t != 0) {
        if (o->col[3] > 20) {
            o->col[3] -= 19;
        } else {
            o->state = 0;
        }
    }
    if (g->t >= 184) {
        o->state = 0;
    }
    o->t++;
    return 0;
}
#pragma opt_propagation reset

/* shape b490:01E01D50, 230 insns: b361:01E01A00's white full-screen flash with the scene packet at ctx+0x8B14 (count
   at 0x8B56), ending once the count reaches 184 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b490_01E01D50;

typedef struct {
    Rgbaq_b490_01E01D50 c;
    f32 s, t;
    u64 x : 16, y : 16, z : 24, f : 8;
} Vtx_b490_01E01D50;

typedef struct {
    u8 hdr[0x10];
    Vtx_b490_01E01D50 v[4];
} Pkt_b490_01E01D50;

typedef struct {
    u8 pad0[0x8B14];
    Pkt_b490_01E01D50 *pk;
    u8 pad5F58[0x3E];
    s16 t;
} Scene_b490_01E01D50;

typedef struct {
    u8 pad0[0x54];
    s16 t;
    u8 pad56[2];
    s16 state;
    u8 pad5A[6];
    u8 col[4];
} Flash_b490_01E01D50;

static s32 func_01E01D50_b490(Scene_b490_01E01D50 *g, Flash_b490_01E01D50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern Rgbaq_b490_01E01D50 func_00107740(void *);

    if (o->state == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->state = 2;
    }
    g->pk->v[0].c = func_00107740(o->col);
    g->pk->v[1].c = func_00107740(o->col);
    g->pk->v[2].c = func_00107740(o->col);
    g->pk->v[3].c = func_00107740(o->col);
    g->pk->v[0].x = 0x6BF8;
    g->pk->v[0].y = 0x71F8;
    g->pk->v[0].z = 0xFFFFFF;
    g->pk->v[0].f = 0;
    g->pk->v[1].x = 0x93F8;
    g->pk->v[1].y = 0x71F8;
    g->pk->v[1].z = 0xFFFFFF;
    g->pk->v[1].f = 0;
    g->pk->v[2].x = 0x6BF8;
    g->pk->v[2].y = 0x8DF8;
    g->pk->v[2].z = 0xFFFFFF;
    g->pk->v[2].f = 0;
    g->pk->v[3].x = 0x93F8;
    g->pk->v[3].y = 0x8DF8;
    g->pk->v[3].z = 0xFFFFFF;
    g->pk->v[3].f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.0f;
    g->pk->v[2].s = 0.0f;
    g->pk->v[2].t = 0.875f;
    g->pk->v[3].s = 0.625f;
    g->pk->v[3].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    if (g->t < 200) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x10;
        }
    } else if (o->col[3] > 20) {
        o->col[3] -= 19;
    } else {
        o->state = 0;
    }
    if (g->t >= 184) {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b490:01E020F0, 349 insns: the module's main (b086:01E01290 family): on start clears the 0x8ED0 context, two
   cameras, 260 ticks, three joints, texture 5:0, the facing from the model's turn, a +-15 jitter table and a second
   table (0 for 100, 0..4 for 80, then 0..3 signed by the facing); each tick runs the 310 slots' five movers, counting
   the two kinds that need the module's extra pass, then draws the two drawn kinds; ends 1 at step 90, 4 at 245, 2 at
   230, 6 in 101..224, 8 when the timer runs out */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x28];
    void *fn;
    u8 pad48[0xE];
    s16 rot;
    s16 used;
    u8 pad5A[0x16];
} Slot_b490_01E020F0;

typedef struct {
    u8 pad0000[0x80];
    s32 ot2;
    u8 pad0084[4];
    s32 tex88;
    u8 pad008C[8];
    Vec4f m94;
    u8 pad00A4[0x14];
    s16 mode;
    u8 pad00BA[0x1E];
    u8 camD8[0x208];
    Slot_b490_01E020F0 slot[310];
    u8 pad8A80[0x60];
    s32 tex5[8];
    s32 timer;
    u8 pad8B04[8];
    s32 ot;
    u8 pad8B10[0x28];
    s16 joint[3];
    u8 pad8B3E[0x14];
    s16 face;
    s16 code;
    s16 step;
    s8 jit[256];
    s8 jit2[256];
    u8 pad8D58[1];
} Ctx_b490_01E020F0;

static s32 func_01E020F0_b490(s32 arg0, s32 code) {
    Ctx_b490_01E020F0 *g = (Ctx_b490_01E020F0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void b490_01E00920();
    extern s32 b490_01E00BF0();
    extern s32 b490_01E00D90();
    extern s32 b490_01E00E90();
    extern s32 b490_01E01080();
    extern s32 b490_01E01160();
    extern s32 b490_01E01260();
    extern s32 b490_01E01D50();
    extern void b490_01E02800();
    extern void b490_01E029F0();
    extern void b490_01E02BF0();
    f32 v[4];
    Vec4f m;
    s32 r1[4];
    s32 r2[4];
    u8 w[0x90];
    s32 n;
    s32 c;
    s32 i;
    s32 face;

    n = 0;
    c = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x8ED0);
        func_00107C10(g->pad8D58);
        func_00107C10(g->camD8);
        g->code = code;
        g->timer = 260;
        g->joint[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 1, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 1, 0);
        for (i = 0; i < 1; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), r1);
        g->face = r1[1] / 180.0f;
        for (i = 0; i < 256; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 100; i++) {
            g->jit2[i] = 0;
        }
        for (i = 100; i < 180; i++) {
            g->jit2[i] = func_0019A5C8() % 5;
        }
        func_001F6160(func_001F53A0(), r2);
        face = r2[1] / 180.0f;
        for (i = 180; i < 256; i++) {
            if (face != 0) {
                g->jit2[i] = func_0019A5C8() % 4;
            } else {
                g->jit2[i] = -(func_0019A5C8() % 4);
            }
        }
        return 0;
    }
    b490_01E00920(g, 0);
    for (i = 0; i < 310; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == b490_01E00BF0) {
                b490_01E00BF0(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b490_01E00D90) {
                b490_01E00D90(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b490_01E00E90) {
                b490_01E00E90(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b490_01E01080) {
                b490_01E01080(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b490_01E01160) {
                b490_01E01160(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b490_01E01260) {
                n = (s16)(n + 1);
            }
            if (g->slot[i].fn == b490_01E01D50) {
                n = (s16)(n + 1);
            }
        }
    }
    for (i = 0; i < 310; i++) {
        if (g->slot[i].used != 0) {
            c++;
            if (g->slot[i].fn == b490_01E00BF0) {
                g->tex88 = g->tex5[0];
                func_00106080(&m, 0x14, g->slot[i].rot, 0);
                g->m94 = m;
                v[0] = g->slot[i].x;
                v[1] = g->slot[i].y;
                v[2] = g->slot[i].z;
                b490_01E02800(g, &g->slot[i], 0, v);
            }
            if (g->slot[i].fn == b490_01E00D90) {
                b490_01E029F0(g, &g->slot[i], w, 0);
                g->mode = 0;
            }
        }
    }
    if (n != 0) {
        b490_01E02BF0(g);
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 90) {
        return 1;
    }
    if (g->step == 245) {
        return 4;
    }
    if (g->step == 230) {
        return 2;
    }
    if (g->step > 100 && g->step < 225) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b490:01E02670, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x136 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b490_01E02670 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b490_01E02670;

typedef struct Obj_b490_01E02670 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2e0 - 0x250 - 12];
    Slot_b490_01E02670 slots[0x136];
    u8 padB[0x8b04 - 0x2e0 - 0x136 * 0x70];
    u8 rgba[4];
    u8 padC[0x8b50 - 0x8b04 - 4];
    s16 fB2B0;
} Obj_b490_01E02670;

static s32 func_01E02670_b490(Obj_b490_01E02670 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b490_01E02670 *s = NULL;
    s16 i;

    for (i = 0; i < 0x136; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x136;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b490 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b361_01E022E0_unused {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b361_01E022E0_unused;

typedef struct Obj_b361_01E022E0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[1];
} Obj_b361_01E022E0;

typedef struct Xyz_b361_01E022E0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b361_01E022E0;

typedef struct Uv_b361_01E022E0 {
    f32 u, v;
} Uv_b361_01E022E0;

typedef struct Pk_b361_01E022E0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b361_01E022E0 uv;
    u64 pad18;
    Xyz_b361_01E022E0 v[4];
    u64 pad60[6];
} Pk_b361_01E022E0;

typedef struct Buf_b361_01E022E0 {
    u64 tag;
    Pk_b361_01E022E0 pk;
} Buf_b361_01E022E0;


typedef struct Data_b361_01E022E0 {
    u8 pad0[0x20];
    s32 wh[2];
    u8 padB[0x38];
    Vec4f uv;
} Data_b361_01E022E0;

static void func_01E02800_b490(Obj_b361_01E022E0 *obj, Data_b361_01E022E0 *data, s32 mode, Vec4f c) {
    extern void func_00108EF0();
    extern s32 func_00109100();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 ang[4];
    Buf_b361_01E022E0 buf;
    Uv_b361_01E022E0 uv;
    Pk_b361_01E022E0 *p = &buf.pk;

    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (mode == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    } else if (mode == 1) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x44);
    } else {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    }
    func_00107740(&uv, &data->uv);
    p->uv = uv;
    func_01E00080_b490((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
    func_00208700(p, (void *)obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)ang);
    ang[1] = 0x4000;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, ang, &a);
    func_00108CE0(view, data->wh[0], data->wh[1]);
    func_00109100(view, data->wh, 2, obj->table);
    if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out) != 0) {
        func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
    }
}

/* shape b361:01E024D0, 126 insns: b018:01E00C50 family: an 18-sector disc of float radius at the object's position */

typedef struct {
    u8 pad00[0x10];
    f32 x, y, z;
    u8 pad1C[0x2C];
    f32 radius;
    u8 pad4C[0xE];
    s16 angle;
    u8 pad5C[4];
    s32 tex0;
    s32 tex1;
} Obj_b361_01E024D0;

static void func_01E029F0_b490(u8 *self, Obj_b361_01E024D0 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    pos.x = obj->x;
    pos.y = obj->y;
    pos.z = obj->z;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

/* shape b490:01E02BF0, 117 insns: frame pass of a battle scene: open the scene's packet, then run the two kinds of
   active effect entries (310 slots) through their handlers and flush if any drew */

typedef struct Pk_b490_01E02BF0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 pad10[0x68];
    s32 f78[2];
    s32 f80[4];
} Pk_b490_01E02BF0;

typedef struct Ent_b490_01E02BF0 {
    u8 pad0[0x44];
    void *fn;
    u8 pad48[0x10];
    s16 active;
    u8 pad5A[0x16];
} Ent_b490_01E02BF0;

typedef struct Scn_b490_01E02BF0 {
    u8 pad0[0x2E0];
    Ent_b490_01E02BF0 ent[0x136];
    u8 pad8A80[0x94];
    Pk_b490_01E02BF0 *pk;
    u8 pad8B18[0x18];
    s32 ot;
    void *buf;
} Scn_b490_01E02BF0;

static void func_01E02BF0_b490(Scn_b490_01E02BF0 *w) {
    extern s32 func_001F53A0();
    extern void b490_01E01260(Scn_b490_01E02BF0 *w, Ent_b490_01E02BF0 *e);
    extern void b490_01E01D50(Scn_b490_01E02BF0 *w, Ent_b490_01E02BF0 *e);
    s32 i;
    s32 n;
    Pk_b490_01E02BF0 *p;
    u8 buf[0x58] __attribute__((aligned(8)));
    Pk_b490_01E02BF0 pk __attribute__((aligned(8)));

    w->buf = buf;
    w->pk = &pk;
    n = 0;
    w->ot = func_00207F60();
    w->pk->flags = 0x34;
    w->pk->size = 0xC;
    w->pk->regs = ((u64)0x4214 << 32) | 0x21421421;
    w->pk->pad4 = 0;
    func_00208460();
    func_002086D0(w->pk, ((u64)0x80 << 32) | 0x48);
    p = w->pk;
    func_001F7060(func_001F53A0(), 0, (s32)p->f78, (s32)p->f80);
    func_00208460();
    for (i = 0; i < 0x136; i++) {
        if (w->ent[i].active != 0 && w->ent[i].fn == b490_01E01260) {
            n++;
            b490_01E01260(w, &w->ent[i]);
        }
    }
    for (i = 0; i < 0x136; i++) {
        if (w->ent[i].active != 0 && w->ent[i].fn == b490_01E01D50) {
            n++;
            b490_01E01D50(w, &w->ent[i]);
        }
    }
    if (n != 0) {
        func_00207FD0(w->ot, (s32)func_00207500(), 0);
    }
}
