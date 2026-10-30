#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b161(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s16 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

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

static void func_01E00110_b161(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b161(Obj_b016_01E00920 *obj, Cam_b016_01E00920 *cam, s32 flags, s8 *table) {
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
    func_01E00110_b161((Pk_b003_01E00080 *)p, &obj->rect, 0);
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
            func_01E00110_b161((Pk_b003_01E00080 *)p, &obj->rect, obj->fC0[i]);
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
   position; mode (flags & 0xF) 0 = depth from the projection, 1 = far z, else -1. Needs func_01E00110_b161 in the
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

static void func_01E00F60_b161(Obj_b016_01E00ED0 *obj, Cam_b016_01E00ED0 *cam, s32 flags, Vec4f c) {
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
    func_01E00110_b161((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fBE);
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

INCLUDE_ASM("asm/nonmatchings/mod/b161", func_01E01220_b161);

/* shape b161:01E01970, 117 insns: b594:01E02790 family: a white tumbling spark (size 2, frame 4, three random turns, angle 3..12, spin 1..3, size 1..8) held 1..3 ticks: in by 64 up to 0xC0, then out by 19 and ends; also ends once the scene value reaches 121 */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[4];
    s16 hE;
    u8 pad10[0x10];
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
} Obj_b161_01E01970;

typedef struct {
    u8 pad[0xC3FC];
    s16 val;
} Game_b161_01E01970;

static s32 func_01E01970_b161(Game_b161_01E01970 *g, Obj_b161_01E01970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 2.0f;
        o->kind = 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->w20 = func_0019A5C8() % 65535;
        o->w24 = func_0019A5C8() % 65535;
        o->w28 = func_0019A5C8() % 65535;
        o->h50 = func_0019A5C8() % 10 + 3;
        o->h5A = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->h6 = func_0019A5C8() % 3 + 1;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    if (g->val >= 121) {
        o->mode = 0;
    }
    o->t++;
    return 0;
}

/* shape b161:01E01B50, 137 insns: blinking grey spark (size 10) that blinks on/off every other tick in two phases by h50; alpha up by 0x60 to 0xC0 for 15 ticks, then down by 9 once scene count 121 is passed; frame flips 0/1 each tick */

typedef struct {
    u8 pad0[0xC3C4];
    s16 ids[(0xC3FC - 0xC3C4) / 2];
    s16 count;
} Ctx_b161_01E01B50;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[4];
    f32 pos[4];
    s32 rot[4];
    u8 pad30[0x20];
    s16 h50;
    u8 pad52[2];
    s16 tick;
    s16 h56;
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b161_01E01B50;

static s32 func_01E01B50_b161(Ctx_b161_01E01B50 *g, Fx_b161_01E01B50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);

    if (o->mode == 1) {
        o->h8 = 10;
        o->hA = 10;
        o->h56 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    if (o->tick < 15) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (g->count > 121) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->h50 % 2 == 1) {
        if (o->tick % 4 == 1) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        } else if (o->tick % 4 == 3) {
            func_001076F0(o->col, 0, 0, 0);
        }
    } else {
        if (o->tick % 4 == 1) {
            func_001076F0(o->col, 0, 0, 0);
        } else if (o->tick % 4 == 3) {
            func_001076F0(o->col, 0x80, 0x80, 0x80);
        }
    }
    if (o->tick % 2 == 0) {
        o->h56 = 0;
    } else {
        o->h56 = 1;
    }
    func_00205C40(o->rot);
    o->tick++;
    func_001F5620(func_001F53A0(), g->ids[o->h50], o->pos);
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 limit;
    s16 h8;
    u8 pad0A[4];
    s16 speed;
    u8 pad10[0x10];
    s32 seed[3];
    u8 pad2C[0x1C];
    f32 size;
    u8 pad4C[4];
    s16 pos;
    s16 frame;
    s16 age;
    s16 kind;
    s16 state;
    s16 angle;
    u8 pad5C[4];
    u8 col[3];
    u8 alpha;
} Mote_b111_01E022F0;

static s32 func_01E01D80_b161(s32 unused, Mote_b111_01E022F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = func_0019A5C8() % 5 + 2;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x80, 0x30, 0x30);
        o->seed[0] = func_0019A5C8() % 0xFFFF;
        o->seed[1] = func_0019A5C8() % 0xFFFF;
        o->seed[2] = func_0019A5C8() % 0xFFFF;
        o->frame = 1;
        o->pos = func_0019A5C8() % 30 + 10;
        o->angle = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 3 + 1;
        o->h8 = func_0019A5C8() % 8 + 1;
        o->limit = func_0019A5C8() % 3 + 2;
        o->state = 2;
    }
    if (o->age < o->limit) {
        o->alpha = 0x60;
    } else if (o->alpha > 12) {
        o->alpha -= 11;
    } else {
        o->state = 0;
    }
    o->frame++;
    o->pos += o->speed;
    o->age++;
    return 0;
}

/* shape b161:01E01F80, 104 insns: b509:01E027C0 family: a grey beam falling from 900 by a random 25..59.9 a tick (tail 65 behind) at a random angle, spun 0x4000: alpha 0x80 for 2 ticks, out by 14 under 180, ends under 120 */

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
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
} Obj_b161_01E01F80;

static s32 func_01E01F80_b161(s32 arg0, Obj_b161_01E01F80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 900.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        o->h52 = func_0019A5C8() % 360;
        o->h5A = 5;
        o->h5C = 5;
        o->f34 = func_0019A5C8() % 350 + 250;
        o->f34 = o->f34 / 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->t < 2) {
        o->col[3] = 0x80;
    } else {
        if (o->f48 < 180.0f) {
            if (o->col[3] > 15) {
                o->col[3] -= 14;
            }
        }
        if (o->f48 < 120.0f) {
            o->mode = 0;
        }
    }
    o->f48 -= o->f34;
    o->f4C = o->f48 - 65.0f;
    func_00205C40((s32)&o->w20);
    o->w20 += 0x4000;
    o->t++;
    return 0;
}

/* shape b161:01E02120, 100 insns: on start f48 20, f4C 58 below it, both colours 0x40 grey (second alpha 0),
   random 0x52, 0x5A/0x5C = 5, rise speed 10..34.9 (f34); alpha 0x80 for 2 ticks, then fades by 14 and stops; f48 rises by the
   speed with f4C 30 below it; ends from game step 0xC3FC = 0x79; the rotation at 0x20 advances 0x4000 */

typedef struct {
    u8 pad0[0x20];
    s32 rot[4];
    u8 pad30[4];
    f32 speed;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    u8 pad50[2];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b161_01E02120;

typedef struct {
    u8 pad0[0xC3FC];
    s16 step;
} Game_b161_01E02120;

static s32 func_01E02120_b161(Game_b161_01E02120 *g, Fx_b161_01E02120 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 20.0f;
        o->f4C = o->f48 - 58.0f;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        func_001076F0(o->col2, 0x40, 0x40, 0x40);
        o->f52 = func_0019A5C8() % 360;
        o->f5A = 5;
        o->f5C = 5;
        o->speed = func_0019A5C8() % 250 + 100;
        o->speed /= 10.0f;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->f48 += o->speed;
    o->f4C = o->f48 - 30.0f;
    if (g->step >= 0x79) {
        o->mode = 0;
    }
    func_00205C40((s32)o->rot);
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b161:01E022B0 (B161_OBJ_MOVE_10_), 397 insns, 1 copy: b270:01E03900 jittery spark trail on a 20-point track:
   kick %20-10, size 1..3.9, speed (1..4)/20, 0x60/0x40 blink, drift by a twentieth of its kick; ends once the scene
   step reaches 121 */

typedef struct {
    Vec4f p[0x14];
} Track_b161_01E022B0;

typedef struct {
    u8 pad0[0x5A50];
    Track_b161_01E022B0 track[0x40];
    u8 pad[0xBE50 - 0x5A50 - 0x40 * 0x140];
    Vec4f pt[0x5A];
    u8 padC3F0[0xC];
    s16 step;
    u8 padC3FE[0xC600 - 0xC3FE];
    u8 trig[1];
} World_b161_01E022B0;

typedef struct {
    u8 pad0[6];
    s16 frame;
    s16 life;
    u8 padA[0x26];
    Vec4f v;
    u8 pad40[8];
    f32 size;
    f32 speed;
    s16 idx;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 state;
    s16 head;
    s16 pitch;
    u8 pad5E[2];
    u8 c0[4];
} Spark_b161_01E022B0;

static s32 func_01E022B0_b161(World_b161_01E022B0 *w, Spark_b161_01E022B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    s16 i;
    Vec4f *dst;
    Vec4f *src;

    if (o->state == 1) {
        o->frame = 1;
        o->c0[3] = 0;
        w->pt[o->idx].x = 0.0f;
        w->pt[o->idx].y = 0.0f;
        w->pt[o->idx].z = 0.0f;
        o->v.x = func_0019A5C8() % 20 - 10;
        o->v.y = func_0019A5C8() % 20 - 10;
        o->v.z = func_0019A5C8() % 20 - 10;
        w->pt[o->idx].x += o->v.x / 10.0f;
        w->pt[o->idx].y += o->v.y / 10.0f;
        w->pt[o->idx].z += o->v.z / 10.0f;
        src = &w->pt[o->idx];
        dst = w->track[o->idx].p;
        for (i = 0; i < 0x14; i++) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            dst++;
        }
        o->size = func_0019A5C8() % 30 + 10;
        o->size /= 10.0f;
        o->speed = func_0019A5C8() % 4 + 1;
        o->speed /= 20.0f;
        o->head = func_0019A5C8() % 360;
        o->pitch = (func_0019A5C8() >> 4) % 360;
        o->life = func_0019A5C8() % 15 + 3;
        o->state = 2;
    }
    if (o->t < 7) {
        if (o->frame < 0xF) {
            o->frame++;
        }
    } else if (o->frame > 0) {
        o->frame--;
    }
    if (o->t < o->life) {
        o->c0[3] = 0xC0;
    } else if (o->c0[3] > 0x1E) {
        o->c0[3] -= 0x1D;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 0) {
        func_001076F0(o->c0, 0x60, 0x60, 0x60);
    } else {
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
    }
    o->v.x = func_0019A5C8() % 20 - 10;
    o->v.y = func_0019A5C8() % 20 - 10;
    o->v.z = func_0019A5C8() % 20 - 10;
    if (o->t != 0) {
        w->pt[o->idx].z += o->speed * func_00108030(w->trig, o->head, 0);
        w->pt[o->idx].x += o->speed * func_00108030(w->trig, o->head, 1);
        w->pt[o->idx].y += o->speed * func_00108030(w->trig, o->pitch, 0);
        w->pt[o->idx].x += o->v.x / 20.0f;
        w->pt[o->idx].y += o->v.y / 20.0f;
        w->pt[o->idx].z += o->v.z / 20.0f;
    }
    if (o->t < 7) {
        func_01E00080_b161(&w->track[o->idx].p[0x13], 0x14, 0, &w->pt[o->idx]);
    }
    if (w->step >= 0x79) {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E028F0_b161(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b161", func_01E02900_b161);

/* shape b161:01E03370, 98 insns, 1 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0xc8 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b161_01E03370 {
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
} Slot_b161_01E03370;

typedef struct Obj_b161_01E03370 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b161_01E03370 slots[0xc8];
    u8 padB[0xc394 - 0x2a0 - 0xc8 * 0x70];
    u8 rgba[4];
    u8 padC[0xc3f4 - 0xc394 - 4];
    s16 fB2B0;
} Obj_b161_01E03370;

static s32 func_01E03370_b161(Obj_b161_01E03370 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b161_01E03370 *s = NULL;
    s16 i;

    for (i = 0; i < 0xc8; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0xc8;
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

/* shape b161:01E03500 (B161PAINT_RAIN20), 357 insns, 1 copy: b509:01E03790's wobbling band drawer with the wobble
   scaled by the inner width (w0 / 10 or w0 / 20), bands start at ang0 + cam+0x52, object fields moved up (wob at
   0xC3EC, table at 0xC600) */

typedef struct Cam_b161_01E03500 {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x18];
    f32 w0;
    f32 w1;
    s16 kind;
    s16 f52;
    u8 pad54[6];
    s16 step;
    s16 n;
    u8 pad5E[2];
    u8 uv0[4];
    u8 uv1[4];
} Cam_b161_01E03500;

typedef struct Obj_b161_01E03500 {
    u8 pad0[0x80];
    s32 f80;
    u8 pad84[4];
    s32 f88;
    u8 pad8C[8];
    u8 rect[0x24];
    s16 count;
    u8 padBA[4];
    s16 fBE;
    u8 padC0[0xC3EC - 0xC0];
    s16 wob;
    s16 ang0;
    u8 padC3F0[0xC600 - 0xC3F0];
    u8 table[0x10];
} Obj_b161_01E03500;

typedef struct Uv_b161_01E03500 {
    f32 u, v;
} Uv_b161_01E03500;

typedef struct Vtx_b161_01E03500 {
    Uv_b161_01E03500 st;
    u64 rgba;
    u64 xyz;
} Vtx_b161_01E03500;

typedef struct Pk_b161_01E03500 {
    u8 hdr[0x10];
    Vtx_b161_01E03500 v[4];
    u8 pad70[0x20];
} Pk_b161_01E03500;

static void func_01E03500_b161(Obj_b161_01E03500 *o, Cam_b161_01E03500 *cam, s32 flags, Vec4f c) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern void func_00108EF0();
    extern s32 func_00109270();
    f32 h;
    s32 i;
    s16 k;
    s32 n;
    s32 idx;
    s16 ang;
    f32 w0;
    Pk_b161_01E03500 *p;
    f32 w1;

    Vec4f pts[4];
    Vec4f a;
    Vec4f s;
    f32 m[4][4];
    f32 out[4];
    Pk_b161_01E03500 pk;
    Uv_b161_01E03500 uv0;
    Uv_b161_01E03500 uv1;
    Uv_b161_01E03500 uv2;
    Uv_b161_01E03500 uv3;

    p = &pk;
    n = cam->n;
    ang = 0;
    func_00107990(p, cam->uv0, 2);
    func_00107990(p, cam->uv1, 1);
    func_00109270(p, 0, 0);
    func_00107790(p, cam->uv0, 0);
    func_00108500(p, o->rect, 0);
    func_00208700(p, (void *)o->f88, 1);
    func_00107740(&uv0, cam->uv0);
    pk.v[0].st = uv0;
    func_00107740(&uv1, cam->uv1);
    pk.v[2].st = uv1;
    func_00107740(&uv2, cam->uv0);
    pk.v[1].st = uv2;
    func_00107740(&uv3, cam->uv1);
    pk.v[3].st = uv3;
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    a.x = c.x;
    a.y = c.y;
    a.z = c.z;
    func_00108EF0(m, &s, &cam->pos, &a);
    pts[0].y = 0.0f;
    pts[1].y = 0.0f;
    pts[2].y = 0.0f;
    pts[3].y = 0.0f;
    w0 = cam->w0;
    w1 = cam->w1;
    o->wob = 0;
    ang = o->ang0 + cam->f52;
    for (i = 0; i < o->count; i++) {
        k = ang;
        idx = cam->step + k;
        if (cam->kind == 0) {
            h = cam->w0 / 10.0f * func_00108030(o->table, o->wob, 0);
        } else if (cam->kind == 1) {
            h = cam->w0 / 20.0f * func_00108030(o->table, o->wob, 0);
        }
        if (cam->kind == 0) {
            o->wob += 20;
        } else if (cam->kind == 1) {
            o->wob += 40;
        }
        pts[0].x = h + w0 * func_00108030(o->table, idx, 1);
        pts[0].z = h + w0 * func_00108030(o->table, idx, 0);
        pts[2].x = h + w1 * func_00108030(o->table, idx, 1);
        pts[2].z = h + w1 * func_00108030(o->table, idx, 0);
        if (cam->kind == 0) {
            h = cam->w0 / 10.0f * func_00108030(o->table, o->wob, 0);
        } else if (cam->kind == 1) {
            h = cam->w0 / 20.0f * func_00108030(o->table, o->wob, 0);
        }
        idx = k + (cam->step + (s16)n);
        pts[1].x = h + w0 * func_00108030(o->table, idx, 1);
        pts[1].z = h + w0 * func_00108030(o->table, idx, 0);
        pts[3].x = h + w1 * func_00108030(o->table, idx, 1);
        pts[3].z = h + w1 * func_00108030(o->table, idx, 0);
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

INCLUDE_ASM("asm/nonmatchings/mod/b161", func_01E03AA0_b161);
