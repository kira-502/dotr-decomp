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

static void func_01E00080_b003(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* shape b003:01E00920, 352 insns: b003:01E00EA0 placed at the def's s16 position instead of the object's; draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00920;

typedef struct {
    f32 u, v;
} Uv_b003_01E00920;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00920 uv;
    u64 pad18;
    Xyz_b003_01E00920 v[4];
    u64 pad60[6];
} Pk_b003_01E00920;

typedef struct {
    u64 tag;
    Pk_b003_01E00920 pk;
} Buf_b003_01E00920;

static void func_01E00920_b003(Obj_b003_01E00920 *obj, Def_b003_01E00920 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00920 buf;
    Uv_b003_01E00920 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00920 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = def->x;
    pos.y = def->y;
    pos.z = def->z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b003((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E00EA0_b003(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
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
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00080_b003((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* shape b003:01E01400 (B003_W_S), 222 insns: the scene script of b003: scene colour red 0x80, counts g+0x3310; on
   tick 175 and tick 1 it spawns one 0x1E02110 / 0x1E02440 effect; from tick 181 to 311 it puts the burst point on
   joint A (+-3 in z by the flag g+0x330E) and spawns a 0x1E01860 effect each tick (g+0x3304 cycles 0..169), twice on
   tick 311; from tick 191 to 319 it jitters the point around joint B and spawns 0x1E01C70 on odd ticks, 0x1E01EC0 on
   even ones */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x2B18];
    u8 col[4];
    u8 pad2D78[0x578];
    s16 ja;
    u8 pad32F2[2];
    s16 jb;
    u8 pad32F6[0xE];
    s16 n;
    u8 pad3306[4];
    s16 v;
    u8 pad330C[2];
    s16 flag;
    s16 tick;
} Ctx_b003_01E01400;

static void func_01E01400_b003(Ctx_b003_01E01400 *g) {
    extern void b003_01E01860();
    extern void b003_01E01C70();
    extern void b003_01E01EC0();
    extern void b003_01E02110();
    extern void b003_01E02440();
    extern void b003_01E02E90(Ctx_b003_01E01400 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    f32 v[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick == 175) {
        b003_01E02E90(g, b003_01E02110, 0);
    }
    if (g->tick == 1) {
        b003_01E02E90(g, b003_01E02440, 0);
    }
    if (g->tick > 180 && g->tick <= 311) {
        func_001F5620(func_001F53A0(), g->ja, v);
        g->x = v[0];
        g->y = v[1];
        if (g->flag != 0) {
            g->z = 3.0f + v[2];
        } else {
            g->z = v[2] - 3.0f;
        }
        g->v = g->n;
        for (i = 0; i < 1; i++) {
            b003_01E02E90(g, b003_01E01860, 0);
        }
        g->n++;
        if (g->n >= 170) {
            g->n = 0;
        }
    }
    if (g->tick == 311) {
        func_001F5620(func_001F53A0(), g->ja, v);
        for (i = 0; i < 2; i++) {
            g->x = v[0];
            g->y = v[1];
            if (g->flag != 0) {
                g->z = 3.0f + v[2];
            } else {
                g->z = v[2] - 3.0f;
            }
            g->v = g->n;
            b003_01E02E90(g, b003_01E01860, 0);
            g->n++;
            if (g->n >= 170) {
                g->n = 0;
            }
        }
    }
    if (g->tick > 190 && g->tick <= 319) {
        func_001F5620(func_001F5380(), g->jb, v);
        g->x = (v[0] + (f32)(func_0019A5C8() % 20)) - 10.0f;
        g->y = (v[1] + (f32)(func_0019A5C8() % 40)) - 20.0f;
        g->z = (v[2] + (f32)(func_0019A5C8() % 20)) - 10.0f;
        if (g->tick % 2 == 1) {
            for (i = 0; i < 1; i++) {
                b003_01E02E90(g, b003_01E01C70, 0);
            }
        }
        if (g->tick % 2 == 0) {
            b003_01E02E90(g, b003_01E01EC0, 0);
        }
    }
}

/* shape b003:01E01780, 56 insns, 6 copies: a rising, spinning glow: fades in over 2 frames, then out (variant of b018:01E02480) */

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x1C];
    u8 c0[4];
    u8 pad2C[6];
    s16 t;
    s16 f34;
    s16 state;
    s16 h38;
} Obj_b003_01E01780;

static s32 func_01E01780_b003(void *arg0, Obj_b003_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x50;
        o->f34 = func_0019A5C8() % 4;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 15;
    } else {
        o->state = 0;
    }
    func_001076F0(o->c0, 0x80, 0x40, 0);
    o->fA += 6;
    o->t++;
    o->h38 += 0x14;
    return 0;
}

/* shape b003:01E01860, 260 insns: b003:01E01400's burst puff (grey 0x40): takes the slot number into its spin field
   and keeps its height / depth in the scene tables (+0x2D94 / +0x303C, 170 each), the height sinking 0.7 then 0.8 a
   tick and the depth climbing a 95th of the camera-to-scene gap; size 12..23 growing 2 to 60 (+4 a tick after scene
   tick 341, +2 every other tick), kind up to 5 every other tick, three random angles a tick; brightens by 0x40 while
   held (37..61 ticks), then fades by 9; after scene tick 370 its age is pinned to 70 */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    s16 h8;
    s16 slot;
    s16 dist;
    s16 spin;
    s32 r10;
    s32 r14;
    s32 r18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 size;
    s16 f3A;
} Fx_b003_01E01860;

typedef struct {
    u8 pad0[0x2D94];
    f32 ys[170];
    f32 zs[170];
    u8 pad32E4[0xC];
    s16 ja;
    s16 jb;
    u8 pad32F4[0x1C];
    s16 tick;
} Game_b003_01E01860;

static s32 func_01E01860_b003(Game_b003_01E01860 *g, Fx_b003_01E01860 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, f32 *);
    extern s16 func_001A22C0(f32);
    f32 v[12];
    f32 *q;

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 12 + 12;
        o->kind = 0;
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        o->slot = o->f30;
        g->ys[o->slot] = o->y;
        g->zs[o->slot] = o->z;
        g->ys[o->slot] -= 0.7f;
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 5 + 5;
        o->h8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 25 + 37;
        func_001F5620(func_001F53A0(), g->ja, v);
        func_001F5620(func_001F53A0(), g->jb, q = (f32 *)(u32)&v[4]);
        o->dist = func_001A22C0(q[0] - v[0]);
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->tick > 341) {
        o->size += 4;
    }
    if (o->tick != 0) {
        if (o->size < 60) {
            o->size += 2;
        }
    }
    func_001F5F90(func_001F5380(), v);
    func_001F5F90(func_001F53A0(), &v[4]);
    if (o->tick != 0) {
        v[2] -= v[6];
        v[2] /= 95.0f;
        g->zs[o->slot] += v[2];
    }
    g->ys[o->slot] -= 0.8f;
    if (o->tick % 2 == 1) {
        if (o->kind < 5) {
            o->kind++;
        }
    }
    o->f30 += o->spin;
    if (o->tick % 2 == 1) {
        o->size += 2;
    }
    o->r10 = func_0019A5C8() % 360;
    o->r14 = func_0019A5C8() % 360;
    if (o->spin % 2 == 1) {
        o->f3A += 2;
    } else {
        o->f3A -= 2;
    }
    o->r18 = func_0019A5C8() % 360;
    o->tick++;
    if (g->tick > 370) {
        o->tick = 70;
    }
    return 0;
}

typedef struct {
    u8 pad00[2];
    s16 h2;
    u8 pad04[2];
    s16 h6;
    s16 h8;
    u8 pad0A[2];
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b003_01E01C70;

static s32 func_01E01C70_b003(s32 unused, Obj_b003_01E01C70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 45;
        o->h34 = 0;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->h30 = func_0019A5C8() % 300 + 130;
        o->h3A = func_0019A5C8() % 360;
        o->hE = 0;
        o->h8 = func_0019A5C8() % 35;
        o->hC = func_0019A5C8() % 3 + 2;
        o->h6 = func_0019A5C8() % 10 + 15;
        o->h36 = 2;
    }
    if (o->h32 < o->h6) {
        if (o->col[3] < 0x81) {
            o->col[3] += 0x12;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->h36 = 0;
    }
    if (o->h32 != 0) {
        if (o->h38 < 90) {
            o->h38 += 2;
        }
    }
    if (o->h32 % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->h32 != 0) {
        o->h30 += o->hE;
    }
    if (o->h32 != 0) {
        o->h38 += 2;
    }
    o->h2++;
    o->w10 = func_0019A5C8() % 360;
    o->w14 = func_0019A5C8() % 360;
    o->w18 = func_0019A5C8() % 360;
    o->h32++;
    return 0;
}

/* shape b003:01E01EC0, 146 insns, 4 copies: step of a rising puff: on state 1 sets a grey colour, random start, angle,
   size, layers and lifetime; fades in by 0x12, then out by 9 until it ends; grows, climbs and spins randomly. */

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[2];
    s16 layers;
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 pos;
    s16 t;
    s16 h34;
    s16 state;
    s16 size;
    s16 ang;
} Obj_b003_01E01EC0;

static s32 func_01E01EC0_b003(void *arg0, Obj_b003_01E01EC0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->size = 0x2D;
        o->h34 = 0;
        func_001076F0(o->c0, 0x20, 0x20, 0x20);
        o->pos = func_0019A5C8() % 300 + 130;
        o->ang = func_0019A5C8() % 360;
        o->speed = 0;
        o->h8 = func_0019A5C8() % 35;
        o->layers = func_0019A5C8() % 3 + 2;
        o->life = func_0019A5C8() % 10 + 15;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x12;
        }
    } else if (o->c0[3] > 10) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        if (o->size < 0x5A) {
            o->size += 2;
        }
    }
    if (o->t % 2 == 1) {
        if (o->h34 < 5) {
            o->h34++;
        }
    }
    if (o->t != 0) {
        o->pos += o->speed;
    }
    if (o->t != 0) {
        o->size += 2;
    }
    o->y++;
    o->rot[0] = func_0019A5C8() % 360;
    o->rot[1] = func_0019A5C8() % 360;
    o->rot[2] = func_0019A5C8() % 360;
    o->t++;
    return 0;
}

/* shape b003:01E02110, 41 insns: a glow: colour (0x60,8,8) on start; alpha grows by 8 (up to 0x88) for 0x96 ticks,
   then fades out by 9 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b003_01E02110;

static s32 func_01E02110_b003(s32 arg0, Glow_b003_01E02110 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        func_001076F0(o->col, 0x60, 8, 8);
        o->mode = 2;
    }
    if (o->tick < 0x96) {
        if (o->col[3] < 0x81) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b003:01E021C0, 92 insns, 2 copies: a scene light flash: sets the scene's light block once (colour 4,2,0, range 70,
   at the object's position), its strength rises by 0.2 to 1 then falls by 0.1; the light is switched off when
   the flash ends or the scene says so */

typedef struct {
    s32 w0;
    f32 r, g, b;
    f32 x, y, z;
    u8 pad1C[4];
    s32 w20;
    f32 range;
    f32 strength;
} Light_b003_01E021C0;

typedef struct {
    u8 pad0[0x2D40];
    Light_b003_01E021C0 light;
    u8 pad2D6C[4];
    s32 w2D70;
} World_b003_01E021C0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 falling;
    u8 pad32[4];
    s16 state;
} Flash_b003_01E021C0;

static s32 func_01E021C0_b003(World_b003_01E021C0 *w, Flash_b003_01E021C0 *o) {
    extern void func_001F6C10(void *);

    if (o->state == 1) {
        w->light.w0 = 0;
        w->light.r = 4.0f;
        w->light.g = 2.0f;
        w->light.b = 0;
        w->light.w20 = 0;
        w->light.range = 70.0f;
        w->light.strength = 0.0f;
        w->light.x = o->x;
        w->light.y = o->y;
        w->light.z = o->z;
        o->state = 2;
        o->falling = 0;
    }
    if (o->falling == 0) {
        if (w->light.strength < 1.0f) {
            w->light.strength += 0.2f;
        } else {
            o->falling = 1;
        }
    } else if (w->light.strength > 0.1f) {
        w->light.strength -= 0.1f;
    } else {
        o->state = 0;
    }
    if (o->state == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&w->light);
    }
    if (w->w2D70 == 1) {
        o->state = 0;
    }
    return 0;
}

/* shape b003:01E02330, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2D70 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2D70];
    s32 state;
} Game_b003_01E02330;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b003_01E02330;

static s32 func_01E02330_b003(Game_b003_01E02330 *g, Fade_b003_01E02330 *o) {
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

/* shape b003:01E023F0: b018:01E02DB0 with other constants (chatG) */

extern f32 D_01E03100_b003;
extern f32 D_01E03108_b003;

static s32 func_01E023F0_b003(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03100_b003;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03108_b003;
    func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
    return 0;
}

/* shape b003:01E02440, 132 insns: b555:01E02CB0 with the scene packet at ctx+0x32E8; while fading the zoom f8 grows 7 per tick */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b003_01E02440;

typedef struct {
    f32 s, t;
    Xyz_b003_01E02440 p;
} Tv_b003_01E02440;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b003_01E02440 v[2];
} Tex_b003_01E02440;

typedef struct {
    u8 pad[0x32E8];
    Tex_b003_01E02440 *pk;
} Game_b003_01E02440;

typedef struct {
    u8 pad0[8];
    s16 f8;
    u8 padA[0x1E];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b003_01E02440;

static s32 func_01E02440_b003(Game_b003_01E02440 *g, Fx_b003_01E02440 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    f32 f;

    f = o->f8;
    if (o->mode == 1) {
        o->col[3] = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->mode = 2;
    }
    g->pk->r = o->col[0];
    g->pk->g = o->col[1];
    g->pk->b = o->col[2];
    g->pk->a = o->col[3];
    g->pk->q = 1.0f;
    g->pk->v[0].p.x = 0x6BF8;
    g->pk->v[0].p.y = 0x71F8;
    g->pk->v[0].p.z = 0xFFFFFF;
    g->pk->v[0].p.f = 0;
    g->pk->v[1].p.x = 0x93F8;
    g->pk->v[1].p.y = 0x8DF8;
    g->pk->v[1].p.z = 0xFFFFFF;
    g->pk->v[1].p.f = 0;
    g->pk->v[0].s = f / 1024.0f;
    g->pk->v[0].t = f / 512.0f;
    g->pk->v[1].s = (640.0f - f) / 1024.0f;
    g->pk->v[1].t = (448.0f - f) / 512.0f;
    func_002075F0((s32)g->pk, 0, 0);
    if (o->tick < 29) {
        if (o->col[3] < 0x80) {
            o->col[3] += 10;
        }
    } else {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
        o->f8 += 7;
    }
    o->tick++;
    return 0;
}

/* shape b003:01E02650 (b003), 526 insns, 1 copy: b003 scene manager (b552:01E02630 form): setup (five models, type-4
   and four type-5 textures, an s8 jitter table, eight random 0..3 values), step B003_W_S and 170 slots of nine kinds
   (the 01E02110 and 01E023F0 handlers written out, 01E02440 slots counted to call 01E02FB0), draw four kinds; scene
   code from the timer */

typedef struct Fx_b003_01E02650 {
    s16 x;
    u8 pad2[8];
    s16 sel;
    s16 hC;
    u8 padE[0x16];
    void *fn;
    u8 col[4];
    u8 pad2C[6];
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Fx_b003_01E02650;

typedef struct Q_b003_01E02650 {
    f32 a, b, c, d;
} Q_b003_01E02650;

typedef union R_b003_01E02650 {
    Q_b003_01E02650 q;
    s16 s[8];
} R_b003_01E02650;

typedef struct Scene_b003_01E02650 {
    u8 pad0[0x20];
    f32 px, py, pz;
    u8 pad2C[0x80 - 0x2C];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    R_b003_01E02650 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    s16 hC0[8];
    u8 padD0[8];
    u8 camD8[0x260 - 0xD8];
    s32 tex[16];
    Fx_b003_01E02650 fx[170];
    s32 tex2[4];
    u8 pad2D30[0x2D70 - 0x2D30];
    s32 state;
    u8 pad2D74[8];
    s32 ot2;
    u8 pad2D80[0x2D94 - 0x2D80];
    f32 ta[170];
    f32 tb[170];
    u8 pad32E4[0x32F0 - 0x32E4];
    s16 model0;
    s16 model1;
    s16 model2;
    s16 model3;
    s16 model4;
    u8 pad32FA[0x330C - 0x32FA];
    s16 id;
    s16 flag;
    s16 timer;
    s8 rnd[256];
    u8 pad3412[2];
    u8 cam[0x3580 - 0x3414];
} Scene_b003_01E02650;

static s32 func_01E02650_b003(s32 arg0, s32 id) {
    Scene_b003_01E02650 *g = (Scene_b003_01E02650 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_002075F0(void *, s32, s32);
    extern f32 D_01E03100_b003;
    extern f32 D_01E03108_b003;
    extern void func_01E01400_b003();
    extern s32 func_01E01780_b003();
    extern s32 func_01E01860_b003();
    extern s32 func_01E01C70_b003();
    extern s32 func_01E01EC0_b003();
    extern s32 func_01E02110_b003();
    extern s32 func_01E021C0_b003();
    extern s32 func_01E02330_b003();
    extern s32 func_01E023F0_b003();
    extern s32 func_01E02440_b003();
    extern void func_01E00920_b003();
    extern void func_01E00EA0_b003();
    extern void b003_01E02FB0();
    s32 n;
    s16 cnt;
    Vec4f v;
    Q_b003_01E02650 r0;
    Q_b003_01E02650 r1;
    Q_b003_01E02650 r2;
    s32 info[4];
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;

    n = 0;
    cnt = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3580);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->state = 0x18B;
        g->model0 = func_001F5560(func_001F53A0(), 0x1F, 1);
        g->model1 = func_001F5560(func_001F53A0(), 0x20, 0);
        g->model2 = func_001F5560(func_001F5380(), 1, 1);
        g->model3 = func_001F5560(func_001F53A0(), 0x47, 0);
        g->model4 = func_001F5560(func_001F53A0(), 0x4E, 0);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        g->tex[0] = func_00202BF0(4, 0);
        for (i = 0; i < 4; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), info);
        g->flag = (s32)(info[1] / 180.0f);
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 16 - 8;
        }
        for (i = 0; i < 8; i++) {
            g->hC0[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    func_01E01400_b003(g, 0);
    for (i = 0; i < 170; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E01780_b003) {
                func_01E01780_b003(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01860_b003) {
                func_01E01860_b003(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01C70_b003) {
                func_01E01C70_b003(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01EC0_b003) {
                func_01E01EC0_b003(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02110_b003) {
                if (g->fx[i].used == 1) {
                    func_001076F0(g->fx[i].col, 0x60, 8, 8);
                    g->fx[i].used = 2;
                }
                if (g->fx[i].h32 < 0x96) {
                    if (g->fx[i].col[3] < 0x81) {
                        g->fx[i].col[3] += 8;
                    }
                } else if (g->fx[i].col[3] > 0xA) {
                    g->fx[i].col[3] -= 9;
                } else {
                    g->fx[i].used = 0;
                }
                g->fx[i].h32++;
            }
            if (g->fx[i].fn == func_01E021C0_b003) {
                func_01E021C0_b003(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02330_b003) {
                func_01E02330_b003(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E023F0_b003) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03100_b003;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03108_b003;
                func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
            }
            if (g->fx[i].fn == func_01E02440_b003) {
                cnt++;
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 170; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E01860_b003) {
                g->texture = g->tex2[2];
                func_00106080(&r0, 0x14, g->fx[i].h34, 0);
                g->rect.q = r0;
                g->rect.s[0] = 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x3F;
                g->rect.s[3] = 0x3F;
                g->count = g->fx[i].hC;
                g->mode = func_0019A5C8() % 4;
                g->px = g->fx[i].x;
                g->py = g->ta[g->fx[i].sel];
                g->pz = g->tb[g->fx[i].sel];
                g->count = 0;
                g->texture = g->tex[0];
                g->px = g->fx[i].x;
                g->py = g->ta[g->fx[i].sel];
                g->pz = g->tb[g->fx[i].sel];
                func_00106080(&r1, 0x14, g->fx[i].h34, 0);
                g->rect.q = r1;
                if (g->fx[i].h32 > 3) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    g->px = g->fx[i].x;
                    g->py = g->ta[g->fx[i].sel];
                    g->pz = g->tb[g->fx[i].sel];
                    func_01E00EA0_b003(g, &g->fx[i], 0x20, g->rnd);
                    g->count = 0;
                }
            }
            if (g->fx[i].fn == func_01E01C70_b003) {
                g->texture = g->tex2[3];
                func_00106080(&r2, 0x14, g->fx[i].h34, 0);
                g->rect.q = r2;
                g->count = g->fx[i].hC;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b003(g, &g->fx[i], 0x10, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E01EC0_b003) {
                g->texture = g->tex2[1];
                g->rect.s[0] = g->fx[i].h34 * 32 + 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x1F;
                g->rect.s[3] = 0x3D;
                g->count = g->fx[i].hC;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b003(g, &g->fx[i], 0x20, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E02110_b003) {
                s32 ot = g->ot2;
                func_00107990(buf, g->fx[i].col, 0);
                func_001092E0(buf, 0);
                func_001094F0(buf);
                func_002075F0(buf, ot, 0);
            }
        }
    }
    if (cnt) {
        b003_01E02FB0(g);
    }
    if (g->state != 0) {
        g->state--;
    }
    if (g->timer == 170) {
        return 1;
    }
    if (g->timer == 380) {
        return 4;
    }
    if (g->timer == 375) {
        return 2;
    }
    if (g->timer > 180 && g->timer < 370) {
        return 6;
    }
    if (g->state <= 0) {
        return 8;
    }
    return 0;
}

/* shape b003:01E02E90, 72 insns: twin of b046:01E03E20: take the first free slot of the 170-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x330A and the two arguments; returns 1 if a
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
} Slot_b003_01E02E90;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b003_01E02E90 s[170];
    u8 pad2D20[0x54];
    u8 r, g, b, a;
    u8 pad2D78[0x592];
    s16 v;
} Pool_b003_01E02E90;

static s32 func_01E02E90_b003(Pool_b003_01E02E90 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b003_01E02E90 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 170; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 170;
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

/* shape b003:01E02FB0, 79 insns: draw pass for the effect pool: open a sprite packet on the stack (kept at 0x32E8, ot at
   0x32E4), texture from func_001F53A0, then every used slot (0xAA of 0x40 bytes at 0x2A0) whose
   callback is b003:01E02440 is drawn by it; close the ot at depth - 2000 if any slot was used */

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 body[0x30];
    u64 t40;
    u64 t48;
    u8 pad50[8];
} Pkt_b003_01E02FB0;

typedef struct {
    u8 pad0[0x24];
    void (*cb)(void *, void *);
    u8 pad28[0xE];
    s16 used;
    u8 pad38[8];
} Slot_b003_01E02FB0;

typedef struct {
    u8 pad0[0x2A0];
    Slot_b003_01E02FB0 slots[0xAA];
    u8 pad2D20[0x5C4];
    s32 ot;
    Pkt_b003_01E02FB0 *pk;
    f32 depth;
} Scene_b003_01E02FB0;

static void func_01E02FB0_b003(Scene_b003_01E02FB0 *g) {
    extern void b003_01E02440(void *, void *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_001F53A0(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b003_01E02FB0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;

    n = 0;
    g->pk = &pkt;
    g->ot = func_00207F60();
    g->pk->count = 0x26;
    g->pk->tag = 5;
    g->pk->regs = 0x42421;
    g->pk->pad = 0;
    func_00208460();
    func_002086D0(g->pk, ((u64)0x80 << 32) | 0x48);
    func_001F7060(func_001F53A0(), 0, &pkt.t40, &pkt.t48);
    func_00208460();
    for (i = 0; i < 0xAA; i++) {
        if (g->slots[i].used != 0) {
            n++;
            if (g->slots[i].cb == b003_01E02440) {
                b003_01E02440(g, &g->slots[i]);
            }
        }
    }
    if (n != 0) {
        func_00207FD0(g->ot, func_00207500(), (u32)(g->depth - 2000.0f));
    }
}
