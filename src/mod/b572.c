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

static void func_01E00080_b572(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E00920_b572(Obj_b003_01E00920 *obj, Def_b003_01E00920 *def, s32 flags, s8 *base) {
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
        func_01E00080_b572((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
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

static void func_01E00EA0_b572(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
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
        func_01E00080_b572((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
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

/* shape b572:01E01400, 266 insns: the scene script of b572 (b003:01E01400 family): scene colour red 0x80, counts
   g+0x3310; ticks 137..311 put the burst point on joint 0x32F0 (1.6 up, +-0.6 in z by the flag g+0x330E) and spawn
   0x1E019E0 numbered by a 170-count (g+0x3304); odd ticks 69..309 put it halfway between joints 0x32F2 and 0x32F4
   and spawn 0x1E01830 (kind 1 when the tick is 1 mod 5, else 2); ticks 291..364 jitter it around joint 0x32FE and
   spawn 0x1E01E90; ticks 13 and 43 spawn 0x1E020A0 on joint 0x32F8, tick 30 on joint 0x32FA */

typedef struct {
    u8 pad0[0x250];
    f32 x;
    f32 y;
    f32 z;
    u8 pad25C[0x2B18];
    u8 col[4];
    u8 pad2D78[0x578];
    s16 ja;
    s16 jb;
    s16 jc;
    u8 pad32F6[2];
    s16 jd;
    s16 je;
    u8 pad32FC[2];
    s16 jf;
    u8 pad3300[4];
    s16 n;
    u8 pad3306[4];
    s16 v;
    u8 pad330C[2];
    s16 flag;
    s16 tick;
} Ctx_b572_01E01400;

extern void b572_01E02C90(Ctx_b572_01E01400 *, void *, s32);
extern void b572_01E019E0();
extern void b572_01E01830();
extern void b572_01E01E90();
extern void b572_01E020A0();

static void func_01E01400_b572(Ctx_b572_01E01400 *g) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern s32 func_0019A5C8(void);
    f32 v[4];
    f32 w[4];
    f32 *pw;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick > 136 && g->tick <= 311) {
        func_001F5620(func_001F53A0(), g->ja, v);
        g->x = v[0];
        g->y = 1.6f + v[1];
        if (g->flag != 0) {
            g->z = 0.6f + v[2];
        } else {
            g->z = v[2] - 0.6f;
        }
        g->v = g->n;
        for (i = 0; i < 1; i++) {
            b572_01E02C90(g, b572_01E019E0, 0);
        }
        g->n++;
        if (g->n >= 170) {
            g->n = 0;
        }
    }
    if (g->tick > 68 && g->tick <= 309) {
        if (g->tick % 2 == 1) {
            func_001F5620(func_001F53A0(), g->jb, v);
            func_001F5620(func_001F53A0(), g->jc, pw = w);
            pw[0] = (pw[0] - v[0]) / 2.0f;
            w[1] = (w[1] - v[1]) / 2.0f;
            w[2] = (w[2] - v[2]) / 2.0f;
            g->x = v[0] + pw[0];
            g->y = v[1] + w[1];
            g->z = v[2] + w[2];
            if (g->tick % 5 == 1) {
                g->v = 1;
            } else {
                g->v = 2;
            }
            for (i = 0; i < 1; i++) {
                b572_01E02C90(g, b572_01E01830, 0);
            }
        }
    }
    if (g->tick > 290 && g->tick <= 364) {
        func_001F5F90(func_001F5380(), v);
        func_001F5620(func_001F5380(), g->jf, v);
        g->x = (v[0] + (f32)(func_0019A5C8() % 40)) - 20.0f;
        g->y = v[1] - (f32)(func_0019A5C8() % 10);
        g->z = (v[2] + (f32)(func_0019A5C8() % 40)) - 20.0f;
        b572_01E02C90(g, b572_01E01E90, 0);
    }
    if (g->tick == 13 || g->tick == 43) {
        func_001F5620(func_001F53A0(), g->jd, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        b572_01E02C90(g, b572_01E020A0, 0);
    }
    if (g->tick == 30) {
        func_001F5620(func_001F53A0(), g->je, v);
        g->x = v[0];
        g->y = v[1];
        g->z = v[2];
        b572_01E02C90(g, b572_01E020A0, 0);
    }
}

/* shape b572:01E01830, 107 insns: on start 0x38 = 20, variant 0, colour 0xFF grey, 0xA keeps the old 0x30, 0x30 = 0, speed
   5..9 (0xE), 0x8 0..24, hold 4..13 (0x6), random 0x3A, 0xC = 0; alpha grows by 0x60 (below 0xC0) during the
   hold, then fades by 19 and stops; the variant counts up to 5 every other tick; after the first tick 0x30 grows by
   the speed and 0x38 by 1 */

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b572_01E01830;

static s32 func_01E01830_b572(s32 arg0, Fx_b572_01E01830 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 20;
        o->f34 = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->fA = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 5 + 5;
        o->f8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 4;
        o->f3A = func_0019A5C8() % 360;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38++;
    }
    o->tick++;
    return 0;
}

/* shape b572:01E019E0 (B572_OBJ_MOVE_4_), 300 insns, 1 copy: a dark (0x10) wisp that claims a slot in the scene's
   height/depth tables: it starts at its point (0.7 lower), turns by the spread between two joints, brightens by 0x40
   while young and fades by 7 (9 after tick 314 of the scene); its slot's depth follows the camera gap (/83, /70
   later), its height sinks by 1.8 down to 35, it grows by 2..5 every other tick up to 60 and spins one way */

typedef struct {
    s16 x, y, z;
    s16 f6;
    s16 f8;
    s16 slot;
    s16 fC;
    s16 fE;
    s32 f10;
    u8 pad14[0x14];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b572_01E019E0;

typedef struct {
    u8 pad0[0x2D94];
    f32 ya[170];
    f32 za[170];
    u8 pad32E4[0xC];
    s16 j0;
    s16 j1;
    u8 pad32F4[0x1C];
    s16 timer;
} Game_b572_01E019E0;

static s32 func_01E019E0_b572(Game_b572_01E019E0 *g, Fx_b572_01E019E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f a;
    Vec4f b[2];
    Vec4f *pb;

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 6 + 10;
        o->f34 = (func_0019A5C8() >> 4) % 2;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        o->slot = o->f30;
        g->ya[o->slot] = o->y;
        g->za[o->slot] = o->z;
        g->ya[o->slot] -= 0.7f;
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->fE = func_0019A5C8() % 5 + 5;
        o->f8 = func_0019A5C8() % 35;
        o->f6 = func_0019A5C8() % 25 + 37;
        func_001F5620(func_001F53A0(), g->j0, &a);
        func_001F5620(func_001F53A0(), g->j1, pb = b);
        o->fC = pb->x - a.x;
        o->f10 = (func_0019A5C8() >> 4) % 4;
        o->mode = 2;
    }
    if (o->tick < o->f6) {
        if (o->tick < 314) {
            if (o->col[3] <= 0x80) {
                o->col[3] += 0x40;
            }
        }
    } else if (g->timer < 314) {
        if (o->col[3] > 8) {
            o->col[3] -= 7;
        } else {
            o->mode = 0;
        }
    }
    if (g->timer > 314) {
        if (o->col[3] > 10) {
            o->col[3] -= 9;
        } else {
            o->mode = 0;
        }
    }
    if (o->tick != 0) {
        if (o->f38 < 60) {
            o->f38 += 2;
        }
    }
    func_001F5F90(func_001F5380(), &a);
    func_001F5F90(func_001F53A0(), b);
    if (o->tick != 0) {
        a.z -= b[0].z;
        if (g->timer < 300) {
            a.z /= 83.0f;
        } else {
            a.z /= 70.0f;
        }
        g->za[o->slot] += a.z;
    }
    if (g->ya[o->slot] > 35.0f) {
        g->ya[o->slot] -= 1.8f;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 6) {
            o->f34++;
        }
    }
    if (g->timer >= 297) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
    }
    o->f30 += o->fE;
    if (o->tick % 2 == 1) {
        o->f38 += (s16)(func_0019A5C8() % 4 + 2);
    }
    if (o->fE % 2 == 1) {
        o->f3A++;
    } else {
        o->f3A--;
    }
    o->tick++;
    return 0;
}

/* shape b572:01E01E90, 129 insns: b572:01E020A0 variant: dark (0x10) ember starting 20..169 high, speed 5..9, fade-in
   4..10 ticks up by 64 to 0x80, then down by 9; once the game counter at g+0x3310 passes 296 it turns 0x20 grey; it
   grows by 1 a tick and counts f2 */

typedef struct {
    u8 pad0[0x3310];
    s16 count;
} Game_b572_01E01E90;

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b572_01E01E90;

static s32 func_01E01E90_b572(Game_b572_01E01E90 *g, Fx_b572_01E01E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 70;
        o->f34 = 0;
        func_001076F0(o->col, 0x10, 0x10, 0x10);
        o->fA = o->f30;
        o->f30 = func_0019A5C8() % 150 + 20;
        o->speed = func_0019A5C8() % 5 + 5;
        o->f8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 7 + 4;
        o->f3A = func_0019A5C8() % 360;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->count >= 0x129) {
        func_001076F0(o->col, 0x20, 0x20, 0x20);
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38 += 1;
    }
    o->f2++;
    o->tick++;
    return 0;
}

/* shape b572:01E020A0, 107 insns: on start 0x38 = 30, variant 0, colour 0xFF grey, 0xA keeps the old 0x30, 0x30 = 0, speed
   8..12 (0xE), 0x8 0..24, hold 4..13 (0x6), random 0x3A, 0xC = 0; alpha grows by 0x60 (below 0xC0) during the
   hold, then fades by 19 and stops; the variant counts up to 5 every other tick; after the first tick 0x30 grows by
   the speed and 0x38 by 2 */

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 hold;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 speed;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b572_01E020A0;

static s32 func_01E020A0_b572(s32 arg0, Fx_b572_01E020A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 30;
        o->f34 = 0;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->fA = o->f30;
        o->f30 = 0;
        o->speed = func_0019A5C8() % 5 + 8;
        o->f8 = func_0019A5C8() % 25;
        o->hold = func_0019A5C8() % 10 + 4;
        o->f3A = func_0019A5C8() % 360;
        o->fC = 0;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x60;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 19;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 5) {
            o->f34++;
        }
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    if (o->tick != 0) {
        o->f38 += 2;
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

static s32 func_01E02250_b572(World_b003_01E021C0 *w, Flash_b003_01E021C0 *o) {
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

static s32 func_01E023C0_b572(Game_b003_01E02330 *g, Fade_b003_01E02330 *o) {
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

extern f32 D_01E02E00_b572;
extern f32 D_01E02E08_b572;

static s32 func_01E02480_b572(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02E00_b572;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02E08_b572;
    func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
    return 0;
}

/* shape b572:01E024D0 (b572), 494 insns, 1 copy: b572 scene manager (b552:01E02630 form): setup (six models, type-4
   and three type-5 textures, two s8 jitter tables with the second cleared from 180, eight random 0..3 values), step
   B572_W_S and 170 slots of seven kinds (the 201 handler written out), draw four kinds; scene code from the timer */

typedef struct Fx_b572_01E024D0 {
    s16 x;
    u8 pad2[8];
    s16 sel;
    u8 padC[0x18];
    void *fn;
    u8 pad28[0xA];
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Fx_b572_01E024D0;

typedef struct Q_b572_01E024D0 {
    f32 a, b, c, d;
} Q_b572_01E024D0;

typedef union R_b572_01E024D0 {
    Q_b572_01E024D0 q;
    s16 s[8];
} R_b572_01E024D0;

typedef struct Scene_b572_01E024D0 {
    u8 pad0[0x20];
    f32 px, py, pz;
    u8 pad2C[0x80 - 0x2C];
    s32 ot;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    R_b572_01E024D0 rect;
    u8 padA4[0x14];
    s16 count;
    u8 padBA[4];
    s16 mode;
    s16 hC0[8];
    u8 padD0[8];
    u8 camD8[0x260 - 0xD8];
    s32 tex[16];
    Fx_b572_01E024D0 fx[170];
    s32 tex2[3];
    u8 pad2D2C[0x2D70 - 0x2D2C];
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
    u8 pad32F6[2];
    s16 model3;
    s16 model4;
    u8 pad32FC[2];
    s16 model5;
    u8 pad3300[0x330C - 0x3300];
    s16 id;
    s16 flag;
    s16 timer;
    s8 rnd[256];
    s8 rnd2[256];
    u8 pad3512[2];
    u8 cam[0x3680 - 0x3514];
} Scene_b572_01E024D0;

static s32 func_01E024D0_b572(s32 arg0, s32 id) {
    Scene_b572_01E024D0 *g = (Scene_b572_01E024D0 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, s32);
    extern f32 D_01E02E00_b572;
    extern f32 D_01E02E08_b572;
    extern void func_01E01400_b572();
    extern s32 func_01E01830_b572();
    extern s32 func_01E019E0_b572();
    extern s32 func_01E01E90_b572();
    extern s32 func_01E020A0_b572();
    extern s32 func_01E02250_b572();
    extern s32 func_01E023C0_b572();
    extern s32 func_01E02480_b572();
    extern void func_01E00920_b572();
    extern void func_01E00EA0_b572();
    s32 n;
    Vec4f v;
    Q_b572_01E024D0 r0;
    Q_b572_01E024D0 r1;
    Q_b572_01E024D0 r2;
    Q_b572_01E024D0 r3;
    s32 info[4];
    s32 i;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3680);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->state = 0x18B;
        g->model0 = func_001F5560(func_001F53A0(), 0x23, 1);
        g->model1 = func_001F5560(func_001F53A0(), 0x22, 0);
        g->model2 = func_001F5560(func_001F53A0(), 0x25, 0);
        g->model3 = func_001F5560(func_001F53A0(), 0xC, 0);
        g->model4 = func_001F5560(func_001F53A0(), 0x37, 0);
        g->model5 = func_001F5560(func_001F5380(), 1, 1);
        for (i = 10; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        g->tex[0] = func_00202BF0(4, 0);
        for (i = 0; i < 3; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), info);
        g->flag = (s32)(info[1] / 180.0f);
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 16 - 8;
        }
        for (i = 0; i < 256; i++) {
            g->rnd2[i] = func_0019A5C8() % 16 - 8;
        }
        for (i = 180; i < 256; i++) {
            g->rnd2[i] = 0;
        }
        for (i = 0; i < 8; i++) {
            g->hC0[i] = func_0019A5C8() % 4;
        }
        return 0;
    }
    func_01E01400_b572(g, 0);
    for (i = 0; i < 170; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E01830_b572) {
                func_01E01830_b572(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E019E0_b572) {
                func_01E019E0_b572(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01E90_b572) {
                func_01E01E90_b572(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E020A0_b572) {
                func_01E020A0_b572(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02250_b572) {
                func_01E02250_b572(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E023C0_b572) {
                func_01E023C0_b572(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E02480_b572) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02E00_b572;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02E08_b572;
                func_001F7170(1, 0, (s32)&a, (s32)&b, 1);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 170; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E01830_b572) {
                g->texture = g->tex2[1];
                func_00106080(&r0, 0x14, g->fx[i].h34, 0);
                g->rect.q = r0;
                g->count = 3;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b572(g, &g->fx[i], 0x10, g->rnd2);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E019E0_b572) {
                g->texture = g->tex[0];
                func_00106080(&r1, 0x14, g->fx[i].h34, 0);
                g->rect.q = r1;
                g->texture = g->tex2[2];
                g->rect.s[0] = g->fx[i].h34 * 32 + 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x1F;
                g->rect.s[3] = 0x3F;
                if (g->fx[i].h32 > 1) {
                    g->count = 3;
                    g->mode = func_0019A5C8() % 4;
                    g->px = g->fx[i].x;
                    g->py = g->ta[g->fx[i].sel];
                    g->pz = g->tb[g->fx[i].sel];
                    if (g->timer < 0xAA) {
                        func_01E00EA0_b572(g, &g->fx[i], 0x21, g->rnd);
                    } else {
                        func_01E00EA0_b572(g, &g->fx[i], 0x20, g->rnd);
                    }
                    g->count = 0;
                }
            }
            if (g->fx[i].fn == func_01E01E90_b572) {
                g->texture = g->tex[0];
                func_00106080(&r2, 0x14, g->fx[i].h34, 0);
                g->rect.q = r2;
                g->texture = g->tex2[2];
                g->rect.s[0] = g->fx[i].h34 * 32 + 1;
                g->rect.s[1] = 1;
                g->rect.s[2] = 0x1F;
                g->rect.s[3] = 0x3F;
                g->count = 3;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b572(g, &g->fx[i], 0x20, g->rnd);
                g->count = 0;
            }
            if (g->fx[i].fn == func_01E020A0_b572) {
                g->texture = g->tex2[1];
                func_00106080(&r3, 0x14, g->fx[i].h34, 0);
                g->rect.q = r3;
                g->count = 8;
                g->mode = func_0019A5C8() % 4;
                func_01E00920_b572(g, &g->fx[i], 0x20, g->rnd2);
                g->count = 0;
            }
        }
    }
    if (g->state != 0) {
        g->state--;
    }
    if (g->timer == 180) {
        return 1;
    }
    if (g->timer == 375) {
        return 4;
    }
    if (g->timer == 355) {
        return 2;
    }
    if (g->timer > 190 && g->timer < 345) {
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

static s32 func_01E02C90_b572(Pool_b003_01E02E90 *o, s32 a, s32 b) {
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
