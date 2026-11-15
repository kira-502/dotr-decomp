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

static void func_01E00080_b530(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* amp product in its own variable (u = v * amp) puts it in the amp conversion's register; plus the in-place divide (chatA 16 Oct). */

/* shape b016:01E00920, 362 insns, 90 copies: draw an object's parts as sprite quads, each part shaken on three
   axes from a signed byte table (scaled by cam->f50 + part / 2); same packet and depth modes as b016:01E00ED0 */

typedef struct Cam_b016_01E00920 {
    u8 pad0[8];
    s16 h8;
    u8 padA[6];
    f32 f10, f14, f18;
    u8 pad1C[4];
    Vec4f pos;
    u8 pad30[0x18];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    u8 pad52[8];
    s16 f5A;
    u8 pad5C[4];
    Vec4f at;
} Cam_b016_01E00920;

typedef struct Obj_b016_01E00920 {
    u8 pad0[0x10];
    Vec4f f10;
    u8 pad20[0x60];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    Rect_b003_01E00080 rect;
    u8 pad9C[0x14];
    s16 fB0;
    u8 padB2[6];
    s16 fB8;
    u8 padBA[6];
    s16 fC0[12];
    u8 fD8[0x10];
} Obj_b016_01E00920;

typedef struct Uv_b016_01E00920 {
    f32 u, v;
} Uv_b016_01E00920;

typedef struct Xyz_b016_01E00920 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b016_01E00920;

typedef struct Pk_b016_01E00920 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b016_01E00920 uv;
    u64 pad18;
    Xyz_b016_01E00920 v[4];
    u64 pad60[6];
} Pk_b016_01E00920;

typedef struct Buf_b016_01E00920 {
    u64 tag;
    Pk_b016_01E00920 pk;
} Buf_b016_01E00920;

static void func_01E00920_b530(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
    f32 u;
    extern void func_00108EF0();
    extern void func_00205C40();
    extern void func_00108950();
    extern void func_00109100();
    s16 off;
    f32 v;
    Pk_b016_01E00920 *p;
    s16 j;
    s16 i;
    s32 sel;

    f32 view[4][4];
    Vec4f pos;
    f32 out[4];
    f32 out2[4];
    f32 m[4][4];
    s32 rot[4];
    s32 x[4];
    Buf_b016_01E00920 buf;
    Uv_b016_01E00920 uv;

    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, &cam->at);
    p->uv = uv;
    func_01E00080_b530((Pk_b003_01E00080 *)p, &obj->rect, 0);
    func_00208700(p, (void *)obj->f88, 1);
    func_00205C40(rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    pos.x = cam->f10;
    pos.y = cam->f14;
    pos.z = cam->f18;
    if (obj->fB0 == 0) {
        func_00108EF0(m, &obj->f10, NULL, &pos);
    } else if (obj->fB0 == 1) {
        func_00108EF0(m, &obj->f10, &cam->pos, &pos);
    }
    x[1] = cam->f5A;
    for (i = 0; i < obj->fB8; i++) {
        if (obj->fB0 == 0) {
            func_01E00080_b530((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
            func_00108CE0(view, cam->f48, cam->f48);
            func_00109100(view, rot, 1, obj->fD8);
            func_00109100(view, rot, 0, obj->fD8);
        } else if (obj->fB0 == 1) {
            func_00108CE0(view, cam->f48, cam->f48);
        }
        for (j = 0; j < 3; j++) {
            if (j == 0) {
                off = 0;
            }
            if (j == 1) {
                off = 100;
            }
            if (j == 2) {
                off = 180;
            }
            v = (table + i)[cam->h8 + off];
            v /= 20.0f;
            u = v * (f32)(cam->f50 + (i >> 1));
            if (j == 0) {
                out[0] = u;
            }
            if (j == 1) {
                out[1] = u;
            }
            if (j == 2) {
                out[2] = u;
            }
        }
        if (obj->fB0 == 0) {
            func_00108950(out, x, 0, obj->fD8);
        }
        func_00107070(view, 0, out[0]);
        func_00107070(view, 1, out[1]);
        func_00107070(view, 2, out[2]);
        if (obj->fB0 == 1) {
            view[0][1] = 0.0f;
            view[1][1] = 0.0f;
            view[0][0] = cam->f48;
            view[1][0] = -cam->f48;
            view[0][2] = 0.0f;
            view[1][2] = 0.0f;
        }
        if ((flags & 0xF) == 0) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out2[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if ((flags & 0xF) == 2) {
            if (func_00205630((s32)view, 0x70000000, (s32)m, (s32)p, out2) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b016:01E00ED0, 175 insns, 99 copies: draw one sprite quad (GS packet of 9 qwords) at an object's
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00080_b530 in the
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

static void func_01E00ED0_b530(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00080_b530((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

/* shape b530:01E01190, 221 insns: the effect scene's step: counts the frame (0xE068) and keeps the scene point on joint
   0xDFA4; frames 20..170 spawn 0x1E01BA0 + 0x1E01D40 (before 106) or 0x1E01510 + 0x1E019A0; from frame 170 to 295,
   every tenth frame opens the next of 20 rings (0xE058, wrapping) with size 40 and height 20; each open ring hands its
   index, size, turn and height to the scene, spawns 0x1E01720 and 0x1E01870, shrinks 1 (closing below 0), sinks 1.2
   and turns 10 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xDD94 - 0x260];
    Vec4f b[20];
    u8 padDED4[0xDEF4 - 0xDED4];
    f32 fDEF4;
    u8 padDEF8[0xDF3C - 0xDEF8];
    f32 fDF3C;
    u8 padDF40[4];
    f32 a[20];
    u8 padDF94[0xDFA4 - 0xDF94];
    s16 joint;
    u8 padDFA6[0xE002 - 0xDFA6];
    s16 hE002;
    u8 padE004[4];
    s16 h[20];
    s16 act[20];
    s16 n;
    u8 padE05A[6];
    s16 cur;
    u8 padE062[6];
    s16 t;
} Scene_b530_01E01190;

static void func_01E01190_b530(Scene_b530_01E01190 *g) {
    extern void b530_01E01510(void);
    extern void b530_01E01720(void);
    extern void b530_01E01870(void);
    extern void b530_01E019A0(void);
    extern void b530_01E01BA0(void);
    extern void b530_01E01D40(void);
    extern s32 b530_01E031A0(Scene_b530_01E01190 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;

    g->t++;
    func_001F5620(func_001F53A0(), g->joint, &g->pos);
    if (g->t >= 20 && g->t < 171) {
        if (g->t < 106) {
            b530_01E031A0(g, (s32)b530_01E01BA0, 0);
            b530_01E031A0(g, (s32)b530_01E01D40, 0);
        } else {
            b530_01E031A0(g, (s32)b530_01E01510, 0);
            b530_01E031A0(g, (s32)b530_01E019A0, 0);
        }
    }
    if (g->t >= 170 && g->t < 296 && g->t % 10 == 1) {
        if (g->n < 20) {
            g->act[g->n]++;
            g->a[g->n] = 40.0f;
            g->b[g->n].x = 20.0f;
            g->n++;
            if (g->n >= 20) {
                g->n = 0;
            }
        }
    }
    for (i = 0; i < 20; i++) {
        if (g->act[i] != 0) {
            g->cur = i;
            g->fDF3C = g->a[i];
            g->hE002 = g->h[i];
            g->fDEF4 = g->b[i].x;
            b530_01E031A0(g, (s32)b530_01E01720, 0);
            b530_01E031A0(g, (s32)b530_01E01870, 0);
            g->a[i] -= 1.0f;
            g->b[i].x -= 1.2f;
            if (g->a[i] < 0.0f) {
                g->act[i] = 0;
            }
            g->h[i] += 10;
        }
    }
}

/* shape b530:01E01510, 130 insns: b530:01E01D40 family grey spark (f48 1..4, frame cycling 0..7, f50 from 0 growing 2..5 per tick for 90 ticks, angle 0..359, f8 0..34): alpha up by 64 to 0xC0 for 3..5 ticks, then down by 14; from scene count 108 its z drifts -1 or +1 by the scene flag */

typedef struct {
    u8 pad0[0xE064];
    s16 flag;
    u8 padE066[2];
    s16 count;
} Ctx_b530_01E01510;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[8];
    f32 z;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b530_01E01510;

static s32 func_01E01510_b530(Ctx_b530_01E01510 *g, Fx_b530_01E01510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 4 + 1;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = 0;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 4 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f56++;
    if (o->f56 > 7) {
        o->f56 = 0;
    }
    if (o->tick < 90) {
        if (o->tick != 0) {
            o->f50 += o->speed;
        }
    }
    if (g->count >= 108) {
        if (g->flag != 0) {
            o->z -= 1.0f;
        } else {
            o->z += 1.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b530:01E01720, 81 insns: a violet growing spark (b252:01E03410 shape): size 70 growing to 90, random sub-frame 0..3; alpha up
   by 0x60 to 0xC0 for 13 frames, then down by 9; skips to frame 20 once the game timer passes 0x127 */

typedef struct {
    u8 pad0[0xE068];
    s16 timer;
} Game_b530_01E01720;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x1C];
    s16 t;
    s16 sub;
    s16 state;
    u8 pad5A[6];
    u8 c0[4];
} Obj_b530_01E01720;

static s32 func_01E01720_b530(Game_b530_01E01720 *g, Obj_b530_01E01720 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x46;
        o->h = 0x46;
        o->sub = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->c0, 0xA0, 0xA0, 0xFF);
        o->state = 2;
    }
    if (o->t < 0xD) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->w < 0x5A) {
            o->w++;
        }
        if (o->h < 0x5A) {
            o->h++;
        }
    }
    func_00205C40((s32)o->rot);
    if (g->timer > 0x127) {
        o->t = 0x14;
    }
    o->t++;
    return 0;
}

/* shape b530:01E01870, 75 insns: a pink growing spark (b252:01E03410 family): size 85 growing by 1, random sub-frame 0..3; alpha up by
   0x60 to 0xC0 for 9 frames, then down by 9 until it ends; random turn; skips to frame 20 once the game timer passes 0x127 */

typedef struct {
    u8 pad0[0xE068];
    s16 timer;
} Game_b530_01E01870;

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x14];
    s32 rot[4];
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    s16 h52;
    s16 t;
    s16 sub;
    s16 state;
    s16 w2;
    s16 h2;
    u8 pad5E[2];
    u8 c0[4];
    u8 c1[4];
} Obj_b530_01E01870;

static s32 func_01E01870_b530(Game_b530_01E01870 *g, Obj_b530_01E01870 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->w = 0x55;
        o->h = 0x55;
        o->sub = (func_0019A5C8() >> 4) % 4;
        func_001076F0(o->c0, 0xFF, 0x80, 0x80);
        o->state = 2;
    }
    if (o->t < 9) {
        if (o->c0[3] < 0xC0) {
            o->c0[3] += 0x60;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->w++;
        o->h++;
    }
    func_00205C40((s32)o->rot);
    if (g->timer > 0x127) {
        o->t = 0x14;
    }
    o->t++;
    return 0;
}

/* shape b530:01E019A0, 127 insns: b530:01E01D40's grey puff that also slides 1 a tick on y (0x18) from scene frame 108,
   down or up by the scene side flag */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[8];
    f32 y;
    u8 pad1C[4];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b530_01E019A0;

typedef struct {
    u8 pad0[0xE064];
    s16 side;
    u8 padE066[2];
    s16 frame;
} Scene_b530_01E019A0;

static s32 func_01E019A0_b530(Scene_b530_01E019A0 *g, Fx_b530_01E019A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 3 + 1;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = func_0019A5C8() % 30 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 4 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f56++;
    if (o->f56 > 7) {
        o->f56 = 0;
    }
    if (g->frame >= 0x6C) {
        if (g->side != 0) {
            o->y -= 1.0f;
        } else {
            o->y += 1.0f;
        }
    }
    o->tick++;
    return 0;
}

/* shape b530:01E01BA0, 103 insns: on start f48 1..4, colour 0x80 grey, 0x50 0, random 0x5A, speed 2..5 (0xE),
   0x8 0..34, hold 3..5 (0x6); alpha grows by 0x40 (below 0xC0) during the hold, then fades by 14 and stops; the
   variant 0x56 cycles 0..7; 0x50 grows by the speed on ticks 1..0x59 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b530_01E01BA0;

static s32 func_01E01BA0_b530(s32 arg0, Fx_b530_01E01BA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 4 + 1;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = 0;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 4 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f56++;
    if (o->f56 > 7) {
        o->f56 = 0;
    }
    if (o->tick < 0x5A) {
        if (o->tick != 0) {
            o->f50 += o->speed;
        }
    }
    o->tick++;
    return 0;
}

/* shape b530:01E01D40, 100 insns: on start f48 1..3, colour 0x80 grey, 0x50 10..39, random 0x5A, speed 2..5 (0xE),
   0x8 0..34, hold 3..5 (0x6); alpha grows by 0x40 (below 0xC0) during the hold, then fades by 14 and stops; the
   variant 0x56 cycles 0..7 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x10];
    s32 rot[4];
    u8 pad30[0x18];
    f32 f48;
    f32 f4C;
    s16 f50;
    u8 pad52[2];
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b530_01E01D40;

static s32 func_01E01D40_b530(s32 arg0, Fx_b530_01E01D40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = func_0019A5C8() % 3 + 1;
        o->f56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->f50 = func_0019A5C8() % 30 + 10;
        o->f5A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 4 + 2;
        o->f8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 3 + 3;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f56++;
    if (o->f56 > 7) {
        o->f56 = 0;
    }
    o->tick++;
    return 0;
}

/* shape b530:01E01ED0, 183 insns: b491:01E03360 family dark grey (0x38) screen band through the scene packet (ctx+0xDF38) from alpha 0, its left and right edges shifted by 0x8 (texels 0..0.625 x 0..0.875), drawn twice; 0x8 swings 10 along the angle 0x5A (0 or 180 by kind, +25 a tick, ctx+0xE26C); alpha up by 10 to 0x80 for 80 ticks, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b530_01E01ED0;

typedef struct {
    f32 s, t;
    Xyz_b530_01E01ED0 p;
} Tv_b530_01E01ED0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b530_01E01ED0 v[2];
} Tex_b530_01E01ED0;

typedef struct {
    u8 pad[0xDF38];
    Tex_b530_01E01ED0 *pk;
    u8 padDF3C[0xE26C - 0xDF3C];
    u8 trig[1];
} Game_b530_01E01ED0;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x46];
    s16 kind;
    u8 pad52[2];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
} Fx_b530_01E01ED0;

static s32 func_01E01ED0_b530(Game_b530_01E01ED0 *g, Fx_b530_01E01ED0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 d;

    d = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0x38, 0x38, 0x38);
        if (o->kind == 0) {
            o->ang = 0;
        }
        if (o->kind == 1) {
            o->ang = 180;
        }
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = (d + 0x6C0) * 16 - 8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = (d + 0x940) * 16 - 8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = 0.0f;
    g->pk->v[0].t = 0.0f;
    g->pk->v[1].s = 0.625f;
    g->pk->v[1].t = 0.875f;
    func_002075F0((s32)g->pk, 0, 0);
    func_002075F0((s32)g->pk, 0, 0);
    o->f8 = 10.0f * func_00108030(g->trig, o->ang, 1);
    o->ang += 25;
    if (o->tick < 80) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b530:01E021B0 (b530), 1017 insns, 1 copy: b530 scene manager in b764:01E03EC0's form: six joints and the root
   joint, textures 4:14..15 and 5:0..3, the unit's facing, two jitter tables, 30 random frames, 30 ring sizes of 40
   (the 20-entry table runs on over the joints) and 20 random angles; otherwise runs B530_W_S, steps the 500 slots
   through their handlers (not 0x1E01ED0), draws six kinds (two as four sprites a quarter turn apart round the slot)
   and returns 1/4/2 at frames 174/325/315, 6 on 185..309, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x14];
    f32 f34;
    u8 pad38[0xC];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0xA];
    s16 h56;
    s16 used;
    s16 h5A;
    u8 pad5C[0x14];
} Fx_b530_01E021B0;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        Vec4f m;
        s16 uv[4];
    } u94;
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b530_01E021B0 fx[500];
    u8 padDD60[0x1A0];
    s32 tex[4];
    u8 padDF10[0x10];
    s32 count;
    u8 padDF24[8];
    s32 ot;
    u8 padDF30[0x14];
    union {
        f32 size[30];
        struct {
            u8 pad0[0x60];
            s16 jA;
            s16 jB;
            s16 jC;
            s16 jD;
            s16 jE;
            s16 jF;
            u8 pad6C[4];
            s16 cam;
        } j;
    } u;
    u8 padDFBC[8];
    s16 rnd[30];
    u8 padE000[8];
    s16 ang[20];
    u8 padE030[0x34];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 padE26A[2];
    u8 crd[0x174];
} Scene_b530_01E021B0;

static s32 func_01E021B0_b530(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8(void);
    extern void b530_01E01190();
    Scene_b530_01E021B0 *g = (Scene_b530_01E021B0 *)arg0;
    s16 n;
    Vec4f v;
    Vec4f rm;
    Vec4f rm2;
    Vec4f rm3;
    Vec4f rm4;
    Vec4f rm5;
    s32 ang[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE3E0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x154;
        g->u.j.jA = func_001F5560(func_001F53A0(), 0x6A, 1);
        g->u.j.jB = func_001F5560(func_001F53A0(), 0x34, 0);
        g->u.j.jC = func_001F5560(func_001F53A0(), 0x35, 0);
        g->u.j.jD = func_001F5560(func_001F53A0(), 0x30, 0);
        g->u.j.jE = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->u.j.jF = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->u.j.cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 14; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 4; i++) {
            g->tex[i] = func_00202BF0(5, i);
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
            g->jit2[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 30; k++) {
            g->rnd[k] = func_0019A5C8() % 8;
        }
        /* 30 sizes: the table shares its last ten slots with the joints, which this overwrites */
        for (k = 0; k < 30; k++) {
            g->u.size[k] = 40.0f;
        }
        for (k = 0; k < 20; k++) {
            g->ang[k] = (func_0019A5C8() >> 4) % 360;
        }
        return 0;
    }
    b530_01E01190(g, 0);
    for (k = 0; k < 500; k++) {
        if (g->fx[k].used != 0) {
            if (g->fx[k].fn != NULL && g->fx[k].fn != (s32 (*)())func_01E01ED0_b530) {
                g->fx[k].fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 500; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E01510_b530) {
                g->tex88 = g->tex[0];
                func_00106080(&rm, 0x14, g->fx[k].h56, NULL);
                g->u94.m = rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b530((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01720_b530) {
                g->tex88 = g->tex[1];
                if (g->fx[k].h56 <= 1) {
                    g->u94.uv[0] = g->fx[k].h56 << 6;
                    g->u94.uv[1] = 0;
                } else {
                    g->u94.uv[0] = (g->fx[k].h56 - 2) << 6;
                    g->u94.uv[1] = 0;
                }
                g->u94.uv[2] = 0x3F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 90, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 90, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 180, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 180, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 270, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 270, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01870_b530) {
                g->tex88 = g->tex[2];
                func_00106080(&rm2, 0x14, g->fx[k].h56, NULL);
                g->u94.m = rm2;
                g->u94.uv[2] = 0x3F;
                g->u94.uv[3] = 0x3F;
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 90, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 90, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 180, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 180, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
                func_001F5F90(func_001F5380(), &v);
                if (g->turn) {
                    v.z -= 10.0f;
                } else {
                    v.z += 10.0f;
                }
                v.z += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 270, 1);
                v.x += g->fx[k].f48 * func_00108030(g->crd, g->fx[k].h5A + 270, 0);
                v.y += g->fx[k].f34;
                func_01E00ED0_b530((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x10, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E019A0_b530) {
                g->tex88 = g->tex[3];
                func_00106080(&rm3, 0x14, g->fx[k].h56, NULL);
                g->u94.m = rm3;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b530((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01BA0_b530) {
                g->tex88 = g->tex[0];
                func_00106080(&rm4, 0x14, g->fx[k].h56, NULL);
                g->u94.m = rm4;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b530((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01D40_b530) {
                g->tex88 = g->tex[3];
                func_00106080(&rm5, 0x14, g->fx[k].h56, NULL);
                g->u94.m = rm5;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b530((Obj_b016_01E00920 *)g, (Cam_b016_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0xAE) {
        return 1;
    }
    if (g->frame == 0x145) {
        return 4;
    }
    if (g->frame == 0x13B) {
        return 2;
    }
    if (g->frame > 0xB8 && g->frame < 0x136) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b425:01E02B60, 114 insns, 2 copies: spawns an effect into the first free slot (500 of 0x70 bytes): clears it, marks it
   live, both colours from the scene, placed at the scene position, with the caller's handler and argument */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x18];
    f32 f34;
    u8 pad38[8];
    s32 w40;
    s32 w44;
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    u8 pad54[4];
    s16 active;
    s16 h5A;
    u8 pad5C[4];
    u8 c0[4];
    u8 c1[4];
    u8 pad68[8];
} Slot_b425_01E02B60;

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x40];
    Slot_b425_01E02B60 slot[500];
    u8 padDD60[0xDEF4 - 0x2A0 - 500 * 0x70];
    f32 fDEF4;
    u8 padDEF8[0x2C];
    u8 col[4];
    u8 padDF28[0x14];
    f32 fDF3C;
    u8 padDF40[0xC2];
    s16 hE002;
    u8 padE004[0x5C];
    s16 hE060;
} Scene_b425_01E02B60;

static s32 func_01E031A0_b530(Scene_b425_01E02B60 *s, s32 fn, s32 arg) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b425_01E02B60 *sl;
    s16 i;

    sl = NULL;
    for (i = 0; i < 500; i++) {
        if (s->slot[i].active == 0) {
            func_00195108(&s->slot[i], 0x70);
            s->slot[i].active = 1;
            sl = &s->slot[i];
            i = 500;
        }
    }
    if (sl != NULL) {
        func_001076F0(sl->c0, s->col[0], s->col[1], s->col[2]);
        sl->c0[3] = s->col[3];
        func_001076F0(sl->c1, s->col[0], s->col[1], s->col[2]);
        sl->c1[3] = s->col[3];
        func_00106AB0(sl, &s->pos, 0);
        sl->x = s->pos.x;
        sl->y = s->pos.y;
        sl->z = s->pos.z;
        sl->h50 = s->hE060;
        sl->h52 = s->hE060;
        sl->h5A = s->hE002;
        sl->f34 = s->fDEF4;
        sl->f48 = s->fDF3C;
        sl->w40 = arg;
        sl->w44 = fn;
        return 1;
    }
    return 0;
}
