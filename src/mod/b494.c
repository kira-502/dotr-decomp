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

static void func_01E00080_b494(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b494 in the
   same file and static (the original reuses $a0 across the call). The colour is passed by value. */

typedef struct Cam_b016_01E00ED0 {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x30];
    Vec4f at;
} Cam_b016_01E00ED0;

typedef struct Obj_b016_01E00ED0 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 f94[0x2A];
    s16 fBE;
} Obj_b016_01E00ED0;

typedef struct Xyz_b016_01E00ED0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00ED0;

typedef struct Uv_b016_01E00ED0 {
    f32 u, v;
} Uv_b016_01E00ED0;

typedef struct Pk_b016_01E00ED0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00ED0 uv;
    u64 pad18;
    Xyz_b016_01E00ED0 v[4];
    u64 pad60[6];
} Pk_b016_01E00ED0;

typedef struct Buf_b016_01E00ED0 {
    u64 tag;
    Pk_b016_01E00ED0 pk;
} Buf_b016_01E00ED0;

static void func_01E00920_b494(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
    extern void func_00108EF0();
    f32 view[4][4];
    Vec4f a;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    Buf_b016_01E00ED0 buf;
    Uv_b016_01E00ED0 uv;
    s32 sel;
    s32 mode;
    Pk_b016_01E00ED0 *p = &buf.pk;

    sel = (flags >> 4) & 0xF;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b494((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b494:01E00BE0, 190 insns: the effect scene's step: counts the frame (0x4528); from frame 25 to 234, every 30th
   frame it picks eight random model joints (the first through the alternate lookup), on every 4th frame it spawns a
   0x1E00EE0 at each of them (numbered by side); the eight angles turn by 10 (wrapped at 360); in that range it also
   spawns 0x1E010D0 and 0x1E01230 at the camera point raised to 31 on even frames */

typedef struct {
    f32 x, y, z, w;
} V4_b494_01E00BE0;

typedef struct {
    u8 pad0[0x250];
    V4_b494_01E00BE0 pos;
    u8 pad260[0x4284];
    s16 joint[8];
    u8 pad44F4[0x18];
    s16 ang[8];
    u8 pad451C[4];
    s16 side;
    u8 pad4522[6];
    s16 t;
} Scene_b494_01E00BE0;

static void func_01E00BE0_b494(Scene_b494_01E00BE0 *g) {
    extern void b494_01E00EE0(void);
    extern void b494_01E010D0(void);
    extern void b494_01E01230(void);
    extern s32 b494_01E01940(Scene_b494_01E00BE0 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    V4_b494_01E00BE0 v[2];
    s16 r;
    s16 i;
    s32 n;

    g->t++;
    if (g->t >= 25 && g->t < 235) {
        if (g->t % 30 == 1) {
            for (i = 0; i < 8; i++) {
                n = func_001F54E0(func_001F53A0());
                r = func_0019A5C8() % n;
                if (r == 0) {
                    r++;
                }
                if (!i) {
                    g->joint[i] = func_001F5560(func_001F53A0(), r, 1);
                } else {
                    g->joint[i] = func_001F5560(func_001F53A0(), r, 0);
                }
            }
        } else if (g->t % 4 == 0) {
            for (i = 0; i < 8; i++) {
                func_001F5620(func_001F53A0(), g->joint[i], &v[0]);
                g->pos = v[0];
                g->side = i;
                b494_01E01940(g, (s32)b494_01E00EE0, 0);
            }
        }
    }
    for (i = 0; i < 8; i++) {
        g->ang[i] += 10;
        if (g->ang[i] >= 360) {
            g->ang[i] %= 360;
        }
    }
    if (g->t >= 25 && g->t < 235) {
        func_001F5F90(func_001F53A0(), &g->pos);
        g->pos.y = 31.0f;
        if (g->t % 2 == 0) {
            b494_01E01940(g, (s32)b494_01E010D0, 0);
        }
        if (g->t % 2 == 0) {
            b494_01E01940(g, (s32)b494_01E01230, 0);
        }
    }
}

/* shape b494:01E00EE0, 124 insns: a blue flickering flame: on start size 12, target size 12..41, a random frame and a
   tilt from the game's per-kind table at g+0x450C; alpha up by 64 to 0x80 for 5 ticks, then down by 9 until it ends; colour
   blinks 0x80/0x80/0xFF and 0x70/0x70/0xC0; frame wraps at 8; after the first tick it rises 0.6 a tick and grows f48 by 0.1 to 0.8 */

typedef struct {
    u8 pad0[0x450C];
    s16 tilt[1];
} Game_b494_01E00EE0;

typedef struct {
    u8 pad0[8];
    s16 size;
    s16 size0;
    u8 padC[8];
    f32 y;
    u8 pad18[8];
    s32 w20;
    u8 pad24[0x24];
    f32 f48;
    u8 pad4C[4];
    s16 kind;
    u8 pad52[2];
    s16 t;
    s16 frame;
    s16 mode;
    u8 pad5A[2];
    s16 ang;
    u8 pad5E[2];
    u8 col[4];
} Fx_b494_01E00EE0;

static s32 func_01E00EE0_b494(Game_b494_01E00EE0 *g, Fx_b494_01E00EE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->size = 12;
        o->size0 = func_0019A5C8() % 30 + 12;
        o->f48 = 0.0f;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
        o->ang = g->tilt[o->kind];
    }
    if (o->t < 5) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->col, 0x80, 0x80, 0xFF);
    } else {
        func_001076F0(o->col, 0x70, 0x70, 0xC0);
    }
    o->frame++;
    if (o->frame > 7) {
        o->frame = 0;
    }
    if (o->t != 0) {
        o->y += 0.6f;
        if (o->f48 < 0.8f) {
            o->f48 += 0.1f;
        }
    }
    func_00205C40((s32)&o->w20);
    o->t++;
    return 0;
}

/* shape b494:01E010D0, 87 insns: a white rising flash (b749:01E028A0 family): f48 20 with f4C 58 below, rising by 950 / 11 a
   frame with f4C 60 below; y turn a half when the game's side is set; alpha 0xC0 for 15 frames, then down by 14 until it ends;
   skips to frame 15 once the game timer reaches 0xE7 */

typedef struct {
    u8 pad0[0x4524];
    s16 side;
    u8 pad4526[2];
    s16 timer;
} Game_b494_01E010D0;

typedef struct {
    u8 pad0[0x24];
    s32 rot1;
    u8 pad28[0x14];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b494_01E010D0;

static s32 func_01E010D0_b494(Game_b494_01E010D0 *g, Obj_b494_01E010D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->c0, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->c1, 0xFF, 0xFF, 0xFF);
        o->h50 = 0;
        o->w = 0xA;
        o->h = 0xA;
        o->f3C = 950.0f;
        o->f3C /= 11.0f;
        o->state = 2;
        o->c1[3] = 0;
        if (g->side != 0) {
            o->rot1 = 0x8000;
        } else {
            o->rot1 = 0;
        }
    }
    if (o->t < 0xF) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0xF) {
        o->c0[3] -= 0xE;
    } else {
        o->state = 0;
    }
    o->f48 += o->f3C;
    o->f4C = o->f48 - 60.0f;
    o->t++;
    if (g->timer > 0xE6) {
        o->t = 0xF;
    }
    return 0;
}

/* shape b494:01E01230, 93 insns: a white beam from 20 growing 950/11 a tick (both ends), tipped 0x8000 when the scene flag is set: alpha 0xC0 for 15 ticks, then out by 14 and ends; from scene value 221 its width grows 40 a tick, from 231 its clock holds at 15 */

typedef struct {
    u8 pad0[0x24];
    s32 w24;
    u8 pad28[0xC];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b494_01E01230;

typedef struct {
    u8 pad[0x4524];
    s16 flag;
    u8 pad4526[2];
    s16 val;
} Game_b494_01E01230;

static s32 func_01E01230_b494(Game_b494_01E01230 *g, Obj_b494_01E01230 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        o->h50 = 0;
        o->h5A = 10;
        o->h5C = 10;
        o->f3C = 950.0f;
        o->f3C = o->f3C / 11.0f;
        o->mode = 2;
        o->col2[3] = 0;
        if (g->flag != 0) {
            o->w24 = 0x8000;
        } else {
            o->w24 = 0;
        }
    }
    if (o->t < 15) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->f3C;
    o->f4C = o->f48;
    if (g->val > 220) {
        o->f34 += 40.0f;
    }
    o->t++;
    if (g->val > 230) {
        o->t = 15;
    }
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E013B0_b494(void) {
    return 0;
}

/* shape b494:01E013C0 (b494), 350 insns, 1 copy: the b494 scene manager (one s16 counter k for the setup, step and
   draw loops, set to 0 with the count): code >= 0 sets up (textures, scale 0.1, two jitter tables, eight random model
   joints, eight random angles), else runs B494_W_S, steps the 150 effect slots and draws the 01E00EE0 flames,
   01E010D0 and 01E01230 beams; scene code from the frame */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0xA];
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b494_01E013C0;

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
    s16 h94;
    s16 h96;
    s16 h98;
    s16 h9A;
    u8 pad9C[0x1C];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b494_01E013C0 fx[150];
    u8 pad4440[0x50];
    s32 tex2[2];
    u8 pad4498[0x18];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 joint[8];
    u8 pad44F4[0x18];
    s16 ang[8];
    u8 pad451C[8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad472A[2];
    u8 crd[0x174];
} Scene_b494_01E013C0;

static s32 func_01E013C0_b494(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void b494_01E01A90();
    extern void b494_01E02400();
    extern void func_01E00BE0_b494();
    Scene_b494_01E013C0 *g = (Scene_b494_01E013C0 *)arg0;
    Vec4f v;
    s32 rm[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s16 n;
    s32 m;

    k = 0;
    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x48A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 250;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 0; k < 8; k++) {
            m = func_001F54E0(func_001F53A0());
            n = func_0019A5C8() % m;
            if (n == 0) {
                n++;
            }
            if (!k) {
                g->joint[k] = func_001F5560(func_001F53A0(), n, 1);
            } else {
                g->joint[k] = func_001F5560(func_001F53A0(), n, 0);
            }
        }
        for (k = 0; k < 8; k++) {
            g->ang[k] = (func_0019A5C8() >> 4) % 360;
        }
        return 0;
    }
    func_01E00BE0_b494(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL) {
                if (g->fx[k].fn != (s32 (*)())func_01E013B0_b494) {
                    g->fx[k].fn(g, &g->fx[k]);
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E00EE0_b494) {
                g->tex88 = g->tex2[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)&g->h94 = *(Vec4f *)rm;
                g->hBE = 0;
                v.x = g->fx[k].pos.x + g->fx[k].f48 * func_00108030(g->crdD8, g->fx[k].h5C, 0);
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b494((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E010D0_b494) {
                g->tex88 = g->tex2[0];
                g->h94 = 0;
                g->h96 = 0;
                g->h98 = 31;
                g->h9A = 63;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 18;
                g->hBE = 0;
                b494_01E01A90(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01230_b494) {
                g->tex88 = g->tex2[0];
                g->h94 = 0;
                g->h96 = 0;
                g->h98 = 31;
                g->h9A = 31;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 18;
                g->hBE = 0;
                b494_01E02400(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 40) {
        return 1;
    }
    if (g->frame == 240) {
        return 3;
    }
    if (g->frame > 50 && g->frame < 235) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b494:01E01940, 82 insns: take a free effect slot (0x96 of 0x70 bytes at 0x2A0), clear it, colour both colours from
   the scene colour 0x44B4, attach it to the scene position (0x250) and copy it, 0x5A and 0x50 from 0x4506 / 0x4520, store the two
   arguments; returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 a2;
    s32 a1;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    s16 f5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
    u8 pad68[8];
} Slot_b494_01E01940;

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x44];
    Slot_b494_01E01940 slots[0x96];
    u8 pad4440[0x44B4 - 0x4440];
    u8 rgba[4];
    u8 pad44B8[0x4E];
    s16 f4506;
    u8 pad4508[0x18];
    s16 f4520;
} Scene_b494_01E01940;

static s32 func_01E01940_b494(Scene_b494_01E01940 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b494_01E01940 *s = NULL;
    s16 i;

    for (i = 0; i < 0x96; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x70);
            g->slots[i].used = 1;
            s = &g->slots[i];
            i = 0x96;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g->pos, 0);
        s->pos[0] = g->pos[0];
        s->pos[1] = g->pos[1];
        s->pos[2] = g->pos[2];
        s->f5A = g->f4506;
        s->f50 = g->f4520;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b494:01E01A90 (IW494MagicCircleGT4_1), 603 insns, 1 copy: b065:01E012B0's camera-facing ring with the alpha
   ramped over the first and last six segments, parameters copied to locals with opt_propagation off */

typedef struct {
    f32 x, y, z, w;
} Vec_b494_01E01A90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b494_01E01A90;

typedef struct {
    u8 r, g, b, a;
} Rgba_b494_01E01A90;

typedef struct {
    Col_b494_01E01A90 c;
    u64 st;
    u64 xyz;
} Vtx_b494_01E01A90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b494_01E01A90 v[4];
    u8 tail[0x20];
} Pkt_b494_01E01A90;

typedef struct {
    u64 dma;
    Pkt_b494_01E01A90 gif;
} Buf_b494_01E01A90;

typedef struct {
    u8 pad00[0x20];
    u8 rot[0x14];
    f32 y;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    Rgba_b494_01E01A90 col0;
    Rgba_b494_01E01A90 col1;
} Anim_b494_01E01A90;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b494_01E01A90;

#pragma opt_propagation off

static void func_01E01A90_b494(Obj_b494_01E01A90 *arg0, Anim_b494_01E01A90 *arg1, s32 arg2, Vec_b494_01E01A90 pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107740(void *, void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Anim_b494_01E01A90 *an = arg1;
    Obj_b494_01E01A90 *o = arg0;
    Vec_b494_01E01A90 quad[4];
    Vec_b494_01E01A90 at;
    Vec_b494_01E01A90 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    Buf_b494_01E01A90 pkt;
    Col_b494_01E01A90 c0;
    Col_b494_01E01A90 c1;
    Col_b494_01E01A90 c2;
    Col_b494_01E01A90 c3;
    Col_b494_01E01A90 c4;
    Col_b494_01E01A90 c5;
    Col_b494_01E01A90 c6;
    Col_b494_01E01A90 c7;
    Col_b494_01E01A90 c8;
    Col_b494_01E01A90 c9;
    Col_b494_01E01A90 c10;
    Col_b494_01E01A90 c11;
    Col_b494_01E01A90 c12;
    Col_b494_01E01A90 c13;
    Col_b494_01E01A90 c14;
    Col_b494_01E01A90 c15;
    Rgba_b494_01E01A90 c;
    s32 i;
    s16 blend;
    s16 j;
    s16 wd;
    Pkt_b494_01E01A90 *p;
    s32 mode = arg2;
    s32 a;
    s32 width;
    f32 w0;
    f32 w1;

    p = &pkt.gif;
    width = an->width;
    j = 0;
    func_00107990(p, &an->col0, 2);
    func_00107990(p, &an->col1, 1);
    blend = mode >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, &an->col0, 0);
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    func_00107740(&c0, &an->col0);
    p->v[0].c = c0;
    func_00107740(&c1, &an->col1);
    p->v[2].c = c1;
    func_00107740(&c2, &an->col0);
    p->v[1].c = c2;
    func_00107740(&c3, &an->col1);
    p->v[3].c = c3;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    at.x = pos.x;
    at.y = pos.y;
    at.z = pos.z;
    func_00108EF0(m, &scale, an->rot, &at);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    w0 = an->w0;
    w1 = an->w1;
    wd = width;
    mode &= 0xF;
    for (i = 0; i < o->count; i++) {
        if (i < 6) {
            c = an->col0;
            if (i == 0) {
                c.a = 0;
            }
            if (i > 0) {
                c.a = an->col0.a / 6 * i;
            }
            func_00107740(&c4, &c);
            p->v[0].c = c4;
            func_00107740(&c5, &c);
            p->v[2].c = c5;
            c = an->col0;
            if (i >= 0) {
                c.a = an->col0.a / 6 * (i + 1);
            }
            func_00107740(&c6, &c);
            p->v[1].c = c6;
            func_00107740(&c7, &c);
            p->v[3].c = c7;
        } else if (i >= o->count - 6) {
            c = an->col0;
            if (i == o->count - 6) {
                c.a = an->col0.a / 6 * 6;
            }
            if (i == o->count - 5) {
                c.a = an->col0.a / 6 * 5;
            }
            if (i == o->count - 4) {
                c.a = an->col0.a / 6 * 4;
            }
            if (i == o->count - 3) {
                c.a = an->col0.a / 6 * 3;
            }
            if (i == o->count - 2) {
                c.a = an->col0.a / 6 * 2;
            }
            if (i == o->count - 1) {
                c.a = an->col0.a / 6;
            }
            func_00107740(&c8, &c);
            p->v[0].c = c8;
            func_00107740(&c9, &c);
            p->v[2].c = c9;
            c = an->col0;
            if (i == o->count - 6) {
                c.a = an->col0.a / 6 * 5;
            }
            if (i == o->count - 5) {
                c.a = an->col0.a / 6 * 4;
            }
            if (i == o->count - 4) {
                c.a = an->col0.a / 6 * 3;
            }
            if (i == o->count - 3) {
                c.a = an->col0.a / 6 * 2;
            }
            if (i == o->count - 2) {
                c.a = an->col0.a / 6;
            }
            if (i == o->count - 1) {
                c.a = 0;
            }
            func_00107740(&c10, &c);
            p->v[1].c = c10;
            func_00107740(&c11, &c);
            p->v[3].c = c11;
        } else {
            func_00107740(&c12, &an->col0);
            p->v[0].c = c12;
            func_00107740(&c13, &an->col0);
            p->v[1].c = c13;
            func_00107740(&c14, &an->col1);
            p->v[2].c = c14;
            func_00107740(&c15, &an->col1);
            p->v[3].c = c15;
        }
        a = j;
        quad[0].x = w0 * func_00108030(o->bD8, a, 1);
        quad[0].z = w0 * func_00108030(o->bD8, a, 0);
        quad[2].x = w1 * func_00108030(o->bD8, a, 1);
        quad[2].z = w1 * func_00108030(o->bD8, a, 0);
        a = wd + j;
        quad[1].x = w0 * func_00108030(o->bD8, a, 1);
        quad[1].z = w0 * func_00108030(o->bD8, a, 0);
        quad[3].x = w1 * func_00108030(o->bD8, a, 1);
        quad[3].z = w1 * func_00108030(o->bD8, a, 0);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->target, 0);
            }
        }
        j += an->step;
    }
}
#pragma opt_propagation reset

/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b494:01E02400, 260 insns: b016:01E014F0's camera-facing bands with the inner edge at height cam->f34 and the
   outer edge at cam->f30 (instead of 0) */

typedef struct Cam_b494_01E02400 {
    u8 pad0[0x20];
    Vec4f pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 w0;
    f32 w1;
    u8 pad50[0xA];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b494_01E02400;

typedef struct Obj_b494_01E02400 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0x18];
    u8 table[0x10];
} Obj_b494_01E02400;

typedef struct Uv_b494_01E02400 {
    f32 u, v;
} Uv_b494_01E02400;

typedef struct Vtx_b494_01E02400 {
    Uv_b494_01E02400 st;
    u64 rgba;
    u64 xyz;
} Vtx_b494_01E02400;

typedef struct Pk_b494_01E02400 {
    u8 hdr[0x10];
    Vtx_b494_01E02400 v[4];
    u8 pad70[0x20];
} Pk_b494_01E02400;

static void func_01E02400_b494(Obj_b494_01E02400 *o, Cam_b494_01E02400 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    s16 sel;
    Pk_b494_01E02400 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b494_01E02400 pk;
    Uv_b494_01E02400 uv0;
    Uv_b494_01E02400 uv1;
    Uv_b494_01E02400 uv2;
    Uv_b494_01E02400 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    sel = flags >> 4;
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00108500(p, o->rect, o->fBE);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    p->v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    p->v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    p->v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    p->v[3].st = uv3;
    s.x = 0.1f;
    a.x = c.x;
    s.y = 0.1f;
    a.y = c.y;
    s.z = 0.1f;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = cam->f34;
    pts[1].y = cam->f34;
    pts[2].y = cam->f30;
    pts[3].y = cam->f30;
    w0 = cam->w0;
    w1 = cam->w1;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        pts[0].x = w0 * func_00108030(o->table, idx, 1);
        pts[0].z = w0 * func_00108030(o->table, idx, 0);
        pts[2].x = w1 * func_00108030(o->table, idx, 1);
        pts[2].z = w1 * func_00108030(o->table, idx, 0);
        idx = k + (cam->step + (s16)n);
        pts[1].x = w0 * func_00108030(o->table, idx, 1);
        pts[1].z = w0 * func_00108030(o->table, idx, 0);
        pts[3].x = w1 * func_00108030(o->table, idx, 1);
        pts[3].z = w1 * func_00108030(o->table, idx, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, o->f80, func_001A23B0(out[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)pts, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_00109380(p, 1);
                func_002075F0((s32)p, o->f80, 0);
            }
        }
        ang += cam->step;
    }
}
