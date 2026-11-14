#include "common.h"

/* shape b034:01E00080, 33 insns, 52 copies: shift a position history down by one, the newest from src */

static s32 func_01E00080_b073(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
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

static void func_01E00110_b073(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

static void func_01E009B0_b073(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
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
        func_01E00110_b073((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
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

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E00F10_b073(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
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
    f32 fx;
    f32 fy;
    f32 fz;

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
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
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
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

/* shape b073:01E011A0, 359 insns: the b073 scene's script (scene colour red): on ticks 111 and 151 a 025C0 at a random
   angle (numbered 0/1) and two 02A70 at 0 and 90 degrees; on tick 255 a 01B50; on tick 260 a 02090 at the joint's
   height under the model, two 02180, thirty-five 022E0 and ten 02450; on ticks 196/216/236/255 and 206/226/245/255
   two 01970 just under joints 5 and 6; on tick 1 the spawn point jitters (-3..2) around joints 1 and 3 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x3594 - 0x260];
    u8 col[4];
    u8 pad3598[0x20];
    s16 j[8];
    u8 pad35C8[2];
    s16 ang;
    u8 pad35CC[2];
    s16 ring;
    u8 pad35D0[4];
    s16 tick;
} Ctx_b073_01E011A0;

static void func_01E011A0_b073(Ctx_b073_01E011A0 *g) {
    extern s32 b073_01E01970();
    extern s32 b073_01E01B50();
    extern s32 b073_01E02090();
    extern s32 b073_01E02180();
    extern s32 b073_01E022E0();
    extern s32 b073_01E02450();
    extern s32 b073_01E025C0();
    extern s32 b073_01E02A70();
    extern void b073_01E03840(Ctx_b073_01E011A0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    Vec4f a;
    Vec4f b;
    s16 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    if (g->tick == 111) {
        func_001F5620(func_001F53A0(), g->j[0], &a);
        g->ang = func_0019A5C8() % 360;
        g->ring = 0;
        b073_01E03840(g, b073_01E025C0, 0);
        g->ang = 0;
        b073_01E03840(g, b073_01E02A70, 0);
        g->ang = 90;
        b073_01E03840(g, b073_01E02A70, 0);
    }
    if (g->tick == 151) {
        func_001F5620(func_001F53A0(), g->j[2], &a);
        g->ang = func_0019A5C8() % 360;
        g->ring = 1;
        b073_01E03840(g, b073_01E025C0, 0);
        g->ang = 0;
        b073_01E03840(g, b073_01E02A70, 0);
        g->ang = 90;
        b073_01E03840(g, b073_01E02A70, 0);
    }
    if (g->tick == 255) {
        b073_01E03840(g, b073_01E01B50, 0);
    }
    if (g->tick == 260) {
        func_001F5620(func_001F53A0(), g->j[2], &a);
        func_001F5F90(func_001F5380(), &b);
        g->pos.x = b.x;
        g->pos.y = a.y;
        g->pos.z = b.z;
        b073_01E03840(g, b073_01E02090, 0);
        g->ang = 0;
        b073_01E03840(g, b073_01E02180, 0);
        g->ang = 90;
        b073_01E03840(g, b073_01E02180, 0);
        for (i = 0; i < 35; i++) {
            b073_01E03840(g, b073_01E022E0, 0);
        }
        for (i = 0; i < 10; i++) {
            b073_01E03840(g, b073_01E02450, 0);
        }
    }
    if (g->tick == 196 || g->tick == 216 || g->tick == 236 || g->tick == 255) {
        func_001F5620(func_001F53A0(), g->j[5], &a);
        g->pos.x = a.x;
        g->pos.y = a.y - 2.0f;
        g->pos.z = a.z;
        for (i = 0; i < 2; i++) {
            b073_01E03840(g, b073_01E01970, 0);
        }
    }
    if (g->tick == 206 || g->tick == 226 || g->tick == 245 || g->tick == 255) {
        func_001F5620(func_001F53A0(), g->j[6], &a);
        g->pos.x = a.x;
        g->pos.y = a.y - 2.0f;
        g->pos.z = a.z;
        for (i = 0; i < 2; i++) {
            b073_01E03840(g, b073_01E01970, 0);
        }
    }
    if (g->tick == 1) {
        func_001F5620(func_001F53A0(), g->j[1], &a);
        g->pos.x = a.x + func_0019A5C8() % 6 - 3.0f;
        g->pos.y = a.y + func_0019A5C8() % 6 - 3.0f;
        g->pos.z = a.z + func_0019A5C8() % 6 - 3.0f;
        g->ring = 0;
        func_001F5620(func_001F53A0(), g->j[3], &a);
        g->pos.x = a.x + func_0019A5C8() % 6 - 3.0f;
        g->pos.y = a.y + func_0019A5C8() % 6 - 3.0f;
        g->pos.z = a.z + func_0019A5C8() % 6 - 3.0f;
        g->ring = 0;
    }
}

/* shape b073:01E01740, 137 insns: a grey flash (size 200, frame 1) whose speed is a fifth of the way between two tracked points (ids at ctx+0x35BA/0x35B8 for kind 0, 0x35BE/0x35BC for kind 1); full alpha for 7 ticks */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x35B8];
    s16 id[4];
} Ctx_b073_01E01740;

typedef struct {
    u8 pad0[8];
    s16 dx;
    s16 dy;
    s16 dz;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b073_01E01740;

static s32 func_01E01740_b073(Ctx_b073_01E01740 *g, Fx_b073_01E01740 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];
    f32 *q;

    if (o->mode == 1) {
        o->f38 = 200;
        o->f34 = 1;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        if (o->kind == 0) {
            func_001F5620(func_001F53A0(), g->id[1], v);
            func_001F5620(func_001F53A0(), g->id[0], q = (f32 *)(u32)&v[4]);
            v[0] = (q[0] - v[0]) / 5.0f;
            v[1] = (v[5] - v[1]) / 5.0f;
            v[2] = (v[6] - v[2]) / 5.0f;
            o->dx = v[0];
            o->dy = v[1];
            o->dz = v[2];
        }
        if (o->kind == 1) {
            func_001F5620(func_001F53A0(), g->id[3], v);
            func_001F5620(func_001F53A0(), g->id[2], q = (f32 *)(u32)&v[4]);
            v[0] = (q[0] - v[0]) / 5.0f;
            v[1] = (v[5] - v[1]) / 5.0f;
            v[2] = (v[6] - v[2]) / 5.0f;
            o->dx = v[0];
            o->dy = v[1];
            o->dz = v[2];
        }
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 7) {
        o->col[3] = 0x80;
    }
    o->tick++;
    return 0;
}

/* shape b073:01E01970, 117 insns: b573:01E02590 family: a white spark (size 80 growing 3 a tick, random frame 0..3 stepping every other tick to 6) spinning a random 13..25 a tick from 0..29, size 0..29, held 7..16 ticks: in by 64 up to 0x80, then out by 15 and ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b073_01E01970;

static s32 func_01E01970_b073(s32 arg0, Glow_b073_01E01970 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 80;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0xFF, 0xFF, 0xFF);
        o->h30 = func_0019A5C8() % 30;
        o->ang = func_0019A5C8() % 360;
        o->hE = func_0019A5C8() % 13 + 13;
        o->h8 = func_0019A5C8() % 30;
        o->h6 = func_0019A5C8() % 10 + 7;
        o->mode = 2;
    }
    if (o->tick < o->h6) {
        if (o->col[3] <= 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick % 2 == 1) {
        if (o->kind < 6) {
            o->kind++;
        }
    }
    if (o->tick != 0) {
        o->h30 += o->hE;
    }
    if (o->tick != 0) {
        o->f38 += 3;
    }
    o->tick++;
    return 0;
}

/* shape b073:01E01B50, 228 insns: b500:01E025C0's four-trail head in blue-grey (0x40, 0x40, 0x80): on start fills four
   9-point trails (ctx+0x28F0.. 0xA0 apart) with the four tracked points (ids at ctx+0x35B8..BE); alpha 0xC0 for 10
   ticks, then down by 15; on tick 8 it spawns b073:01E01EE0; h6 counts up to 6; every tick pushes each point into its
   trail (b073:01E00080, 10 steps) */

typedef struct {
    Vec4f pt[9];
    Vec4f head;
} Trail_b073_01E01B50;

typedef struct {
    u8 pad0[0x28F0];
    Trail_b073_01E01B50 tr[4];
    u8 pad2B70[0x35B8 - 0x2B70];
    s16 id[4];
} Ctx_b073_01E01B50;

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 f8;
    s16 fA;
    u8 padC[0x1C];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b073_01E01B50;

static s32 func_01E01B50_b073(Ctx_b073_01E01B50 *g, Fx_b073_01E01B50 *o) {
    extern void b073_01E00080(Vec4f *, s32, s32, f32 *);
    extern void b073_01E01EE0();
    extern void b073_01E03840(Ctx_b073_01E01B50 *, void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];
    Vec4f *p;
    s16 i;
    s16 j;
    s16 k;
    s16 m;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x40, 0x40, 0x80);
        func_001F5620(func_001F53A0(), g->id[0], v);
        p = g->tr[0].pt;
        for (i = 0; i < 9; i++) {
            p[i].x = v[0];
            p[i].y = v[1];
            p[i].z = v[2];
        }
        func_001F5620(func_001F53A0(), g->id[1], v);
        p = g->tr[1].pt;
        for (j = 0; j < 9; j++) {
            p[j].x = v[0];
            p[j].y = v[1];
            p[j].z = v[2];
        }
        func_001F5620(func_001F53A0(), g->id[2], v);
        p = g->tr[2].pt;
        for (k = 0; k < 9; k++) {
            p[k].x = v[0];
            p[k].y = v[1];
            p[k].z = v[2];
        }
        func_001F5620(func_001F53A0(), g->id[3], v);
        p = g->tr[3].pt;
        for (m = 0; m < 9; m++) {
            p[m].x = v[0];
            p[m].y = v[1];
            p[m].z = v[2];
        }
        o->hold = 0;
        o->col[3] = 0;
        o->fA = func_0019A5C8() % 17 + 44;
        o->f8 = func_0019A5C8() % 8 + 5;
        o->f34 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f38 = 30;
        o->mode = 2;
    }
    if (o->tick < 10) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 16) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    if (o->tick == 8) {
        b073_01E03840(g, b073_01E01EE0, 0);
    }
    if (o->tick != 0) {
        if (o->hold < 6) {
            o->hold++;
        }
    }
    func_001F5620(func_001F53A0(), g->id[0], v);
    b073_01E00080(&g->tr[0].head, 10, 0, v);
    func_001F5620(func_001F53A0(), g->id[1], v);
    b073_01E00080(&g->tr[1].head, 10, 0, v);
    func_001F5620(func_001F53A0(), g->id[2], v);
    b073_01E00080(&g->tr[2].head, 10, 0, v);
    func_001F5620(func_001F53A0(), g->id[3], v);
    b073_01E00080(&g->tr[3].head, 10, 0, v);
    o->tick++;
    return 0;
}

/* shape b073:01E01EE0, 108 insns: on its first tick copies the scene's 4 rows of 10 points (ctx+0x28F0) to the second set (ctx+0x2F30), then a grey glow (size 30, 6 at +6, random 44..60 and 5..12, random angle): in by 64 up to 0xC0 for 7 ticks, then out by 9 and ends */

typedef struct {
    f32 x, y, z, w;
} V4_b073_01E01EE0;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    u8 padC[0x1C];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b073_01E01EE0;

typedef struct {
    u8 pad[0x28F0];
    V4_b073_01E01EE0 src[4][10];
    u8 pad2B70[0x2F30 - 0x2B70];
    V4_b073_01E01EE0 dst[4][10];
} Game_b073_01E01EE0;

static s32 func_01E01EE0_b073(Game_b073_01E01EE0 *g, Glow_b073_01E01EE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 i;

    if (o->mode == 1) {
        func_001076F0(o->col, 0x40, 0x40, 0x40);
        for (i = 0; i < 10; i++) {
            g->dst[0][i].x = g->src[0][i].x;
            g->dst[0][i].y = g->src[0][i].y;
            g->dst[0][i].z = g->src[0][i].z;
            g->dst[1][i].x = g->src[1][i].x;
            g->dst[1][i].y = g->src[1][i].y;
            g->dst[1][i].z = g->src[1][i].z;
            g->dst[2][i].x = g->src[2][i].x;
            g->dst[2][i].y = g->src[2][i].y;
            g->dst[2][i].z = g->src[2][i].z;
            g->dst[3][i].x = g->src[3][i].x;
            g->dst[3][i].y = g->src[3][i].y;
            g->dst[3][i].z = g->src[3][i].z;
        }
        o->h6 = 6;
        o->col[3] = 0;
        o->hA = func_0019A5C8() % 17 + 44;
        o->h8 = func_0019A5C8() % 8 + 5;
        o->kind = 0;
        o->ang = func_0019A5C8() % 360;
        o->f38 = 30;
        o->mode = 2;
    }
    if (o->tick < 7) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b073:01E02090, 57 insns: on start 0x38 = 0x1AE, colour 0xC0 grey and second colour (0x80, 0x80, 0xFF) with
   alpha 0, random 0x3A; alpha grows by 0x50 (below 0xF0) for 5 ticks, then fades by 0x13 and stops */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b073_01E02090;

static s32 func_01E02090_b073(s32 arg0, Fx_b073_01E02090 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x1AE;
        func_001076F0(o->col, 0xC0, 0xC0, 0xC0);
        func_001076F0(o->col2, 0x80, 0x80, 0xFF);
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 5) {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x50;
        }
    } else if (o->col[3] > 0x14) {
        o->col[3] -= 0x13;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b073:01E02180, 87 insns: a blue beam (b073:01E02BD0 shape): size 40 by 500 growing by 70; alphas down by 19 */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[2];
    s16 dir;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b073_01E02180;

static s32 func_01E02180_b073(void *arg0, Obj_b073_01E02180 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x30, 0x30, 0xFF);
        func_001076F0(o->c1, 0x30, 0x30, 0xFF);
        o->w = 0x28;
        o->h = 0x1F4;
        if (o->ang == 0) {
            o->dir = 0;
        } else {
            o->dir = 1;
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0x14) {
            o->c0[3] -= 0x13;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0x14) {
            o->c1[3] -= 0x13;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->dir == 0) {
        o->h += 0x46;
    } else {
        o->h += 0x46;
    }
    o->t++;
    o->ang += 0xA;
    return 0;
}

/* shape b073:01E022E0, 92 insns: a blue rising spark (b531:01E04300 family): frame 5, start height 50..249 (old one kept), random angle, rise 5..12,
   width 0..34, hold 5..9; alpha up by 0x40 while at most 0x80, then down by 7 until it ends */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    s16 y0;
    u8 padC[2];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b073_01E022E0;

static s32 func_01E022E0_b073(void *arg0, Obj_b073_01E022E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 5;
        o->sub = 0;
        func_001076F0(o->c0, 0x40, 0x40, 0xFF);
        o->y0 = o->y;
        o->y = func_0019A5C8() % 200 + 0x32;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 8 + 5;
        o->h8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 5;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 8) {
        o->c0[3] -= 7;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b073:01E02450, 92 insns: a blue rising spark (b073:01E022E0 shape): frame 15, start height 10..59, rise 12..21 */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    s16 y0;
    u8 padC[2];
    s16 step;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 y;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b073_01E02450;

static s32 func_01E02450_b073(void *arg0, Obj_b073_01E02450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xF;
        o->sub = 0;
        func_001076F0(o->c0, 0x40, 0x40, 0xFF);
        o->y0 = o->y;
        o->y = func_0019A5C8() % 50 + 0xA;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 10 + 0xC;
        o->h8 = func_0019A5C8() % 35;
        o->hold = func_0019A5C8() % 5 + 5;
        o->state = 2;
    }
    if (o->t < o->hold) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 8) {
        o->c0[3] -= 7;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

/* shape b073:01E025C0, 165 insns: b073:01E02860 family: the kind's scene point (ctx+0x20) is set to the first tracked point (ctx+0x35B8 / 0x35BC by kind) and pushed toward the second (0x35BA / 0x35BE) by fE/20 of the gap, fE counting up; alpha up by 0x40 to 0x80 for 11 ticks, then down by 12 */

typedef struct {
    u8 pad0[0x20];
    Vec4f pt[2];
    u8 pad40[0x35B8 - 0x40];
    s16 id0;
    s16 id1;
    s16 id2;
    s16 id3;
} Ctx_b073_01E025C0;

typedef struct {
    u8 pad0[0xE];
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b073_01E025C0;

static s32 func_01E025C0_b073(Ctx_b073_01E025C0 *g, Fx_b073_01E025C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];

    if (o->mode == 1) {
        o->f38 = 60;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x10, 0x10, 8);
        o->fE = 0;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 11) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        func_001F5620(func_001F53A0(), g->id0, v);
        func_001F5620(func_001F53A0(), g->id1, &v[4]);
    } else {
        func_001F5620(func_001F53A0(), g->id2, v);
        func_001F5620(func_001F53A0(), g->id3, &v[4]);
    }
    g->pt[o->kind].x = v[0];
    g->pt[o->kind].y = v[1];
    g->pt[o->kind].z = v[2];
    v[0] = v[4] - v[0];
    v[1] = v[5] - v[1];
    v[2] = v[6] - v[2];
    v[0] /= 20.0f;
    v[1] /= 20.0f;
    v[2] /= 20.0f;
    g->pt[o->kind].x += v[0] * o->fE;
    g->pt[o->kind].y += v[1] * o->fE;
    g->pt[o->kind].z += v[2] * o->fE;
    o->fE++;
    o->tick++;
    return 0;
}

/* shape b073:01E02860, 132 insns: a marker that follows the tracked point (id at ctx+0x35C0) into scene point o->kind and nudges it 1.3 right (kind 0) or left; alpha up by 64 for 11 ticks, then down by 12 */

typedef struct {
    u8 pad0[0x20];
    Vec4f pt[1];
    u8 pad30[0x35C0 - 0x30];
    s16 id;
} Ctx_b073_01E02860;

typedef struct {
    u8 pad0[0xE];
    s16 fE;
    u8 pad10[0x18];
    u8 col[4];
    u8 col2[4];
    s16 kind;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b073_01E02860;

static s32 func_01E02860_b073(Ctx_b073_01E02860 *g, Fx_b073_01E02860 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[8];

    if (o->mode == 1) {
        o->f38 = 60;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        func_001076F0(o->col2, 0x10, 0x10, 8);
        o->fE = 0;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 11) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 12;
    } else {
        o->mode = 0;
    }
    if (o->kind == 0) {
        func_001F5620(func_001F53A0(), g->id, v);
    } else {
        func_001F5620(func_001F53A0(), g->id, v);
    }
    g->pt[o->kind].x = v[0];
    g->pt[o->kind].y = v[1];
    g->pt[o->kind].z = v[2];
    if (o->kind == 0) {
        v[0] = 1.3f;
        v[1] = 0.0f;
        v[2] = 0.0f;
    } else {
        v[0] = -1.3f;
        v[1] = 0.0f;
        v[2] = 0.0f;
    }
    g->pt[o->kind].x += v[0];
    g->pt[o->kind].y += v[1];
    g->pt[o->kind].z += v[2];
    o->fE++;
    o->tick++;
    return 0;
}

/* shape b073:01E02A70, 87 insns: a blue column (b073:01E02BD0 shape): size 7 by 25 growing by 20 (2 when turned), alphas up for 11 frames */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[2];
    s16 dir;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b073_01E02A70;

static s32 func_01E02A70_b073(void *arg0, Obj_b073_01E02A70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        func_001076F0(o->c1, 0x30, 0x30, 0x80);
        o->w = 7;
        o->h = 0x19;
        if (o->ang == 0) {
            o->dir = 0;
        } else {
            o->dir = 1;
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0xB) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xE) {
            o->c1[3] -= 0xD;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->dir == 0) {
        o->h += 0x14;
    } else {
        o->h += 2;
    }
    o->t++;
    o->ang += 0xA;
    return 0;
}

/* shape b073:01E02BD0, 86 insns: a blue column (b573:01E02960 shape): frame 6, size 7 growing by 3 in height, turning 10;
   both alphas up by 0x40 to 0x80 for 7 frames, then down by 13 until the first runs out */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[2];
    s16 dir;
    u8 pad10[0x18];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b073_01E02BD0;

static s32 func_01E02BD0_b073(void *arg0, Obj_b073_01E02BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x30, 0x30, 0x80);
        func_001076F0(o->c1, 0x30, 0x30, 0x80);
        o->w = 7;
        o->h = 7;
        if (o->ang == 0) {
            o->dir = 0;
        } else {
            o->dir = 1;
        }
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 7) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] += 0x40;
        }
    } else {
        if (o->c0[3] > 0xE) {
            o->c0[3] -= 0xD;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 0xE) {
            o->c1[3] -= 0xD;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->dir == 0) {
        o->h += 3;
    } else {
        o->h += 3;
    }
    o->t++;
    o->ang += 0xA;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b073", func_01E02D30_b073);

/* shape b073:01E03840, 74 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x35CE and 0x35CA and the two arguments; returns 1 if a
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
    u8 pad38[0x2];
    s16 w;
    u8 pad3C[0x4];
} Slot_b073_01E03840;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b073_01E03840 s[150];
    u8 pad2820[0xD74];
    u8 r, g, b, a;
    u8 pad3598[0x32];
    s16 w;
    u8 pad35CC[0x2];
    s16 v;
} Pool_b073_01E03840;

static s32 func_01E03840_b073(Pool_b073_01E03840 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b073_01E03840 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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
        s->w = o->w;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b073_01E03970;

typedef struct {
    u8 pad00[0x28];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    u8 pad32[6];
    s16 radius;
    s16 start;
} Anim_b073_01E03970;

typedef struct {
    u8 pad00[0x20];
    Vec_b073_01E03970 pts[6];
    s32 target;
    u8 pad84[0x54];
    u8 bD8[1];
} Obj_b073_01E03970;

static void func_01E03970_b073(Obj_b073_01E03970 *o, Anim_b073_01E03970 *an, void *p) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b073_01E03970 quad[4];
    Vec_b073_01E03970 at;
    Vec_b073_01E03970 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 rot[4];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    func_00107990(p, an->c28, 1);
    func_00107990(p, an->c2C, 2);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(rot);
    rot[0] += 0x4000;
    at.x = o->pts[an->h30].x;
    at.y = o->pts[an->h30].y;
    at.z = o->pts[an->h30].z;
    func_00108EF0(m, &scale, rot, &at);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 20);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            func_00109380(p, 1);
            func_002075F0(p, o->target, (u32)depth);
        }
        j += 20;
    }
}

/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E03BC0_b073(void) {
}

/* shape b069:01E01A70, 166 insns: draws 4 copies of a gradient quad (colour A on three corners, B on the last)
   at one of the object's points (fx->point), each turned by the effect's rotation; far z. The packet is passed
   in. Same family as b020:01E00E70. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b069_01E01A70;

typedef struct {
    Rgbaq_b069_01E01A70 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b069_01E01A70;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b069_01E01A70 v[4];
    u8 tail[0x20];
} Pkt_b069_01E01A70;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b069_01E01A70;

typedef struct {
    u8 pad00[8];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    s16 point;
    u8 pad32[8];
    s16 rz;
} Fx_b069_01E01A70;

static void func_01E03BD0_b073(Obj_b069_01E01A70 *o, Fx_b069_01E01A70 *fx, Pkt_b069_01E01A70 *p) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b069_01E01A70 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = o->pts[fx->point].x;
    t.y = o->pts[fx->point].y;
    t.z = o->pts[fx->point].z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
            func_002075F0(p, o->ot, 0);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b073", func_01E03E70_b073);

/* shape b073:01E04890 (B073PAINT_RAIN21), 640 insns, 1 copy (-O3,p): b092:01E04290's ribbon between two point trails
   with the spline inlined: 4 quads per segment, the near edge alpha 0, built at -O3 */

typedef struct {
    f32 x, y, z, w;
} Vec_b073_01E04890;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b073_01E04890;

typedef struct {
    Rgbaq_b073_01E04890 c;
    u64 xyz;
} Vtx_b073_01E04890;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b073_01E04890 v[4];
    u8 tail[0x40];
} Pkt_b073_01E04890;

typedef struct {
    u8 r, g, b, a;
} C4_b073_01E04890;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b073_01E04890 col;
} Rib_b073_01E04890;

static inline Vec_b073_01E04890 spline_b073_01E04890(Vec_b073_01E04890 *p, s32 type, f32 t) {
    Vec_b073_01E04890 r;
    f32 b3;
    f32 b2;
    f32 b1;
    f32 b0;

    if (type == 0) {
        b0 = -t * ((t - 1.0f) * (t - 2.0f)) / 6.0f;
        b1 = (t - 2.0f) * ((1.0f + t) * (t - 1.0f)) / 2.0f;
        b2 = -(1.0f + t) * (t * (t - 2.0f)) / 2.0f;
        b3 = (1.0f + t) * (t * (t - 1.0f)) / 6.0f;
    }
    r.x = p[0].x * b0 + p[1].x * b1 + p[2].x * b2 + p[3].x * b3;
    r.y = p[0].y * b0 + p[1].y * b1 + p[2].y * b2 + p[3].y * b3;
    r.z = p[0].z * b0 + p[1].z * b1 + p[2].z * b2 + p[3].z * b3;
    return r;
}

#pragma optimization_level 3

static void func_01E04890_b073(void *o, Rib_b073_01E04890 *s, Vec_b073_01E04890 *pa, Vec_b073_01E04890 *pb) {
    extern s32 func_00207500(void);
    extern Rgbaq_b073_01E04890 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b073_01E04890 quad[4];
    Vec_b073_01E04890 A[2];
    Vec_b073_01E04890 B[2];
    Vec_b073_01E04890 a4[4];
    Vec_b073_01E04890 b4[4];
    Pkt_b073_01E04890 pkt __attribute__((aligned(8)));
    C4_b073_01E04890 c;
    s32 k;
    s32 j;
    s16 n;
    s32 ot;
    Pkt_b073_01E04890 *p;
    f32 t;

    ot = func_00207500();
    n = s->n;
    p = &pkt;
    func_001092E0(p, 0);
    func_001094F0(p);
    c = s->col;
    a4[0] = pa[0];
    a4[1] = pa[0];
    a4[2] = pa[1];
    a4[3] = pa[2];
    b4[0] = pb[0];
    b4[1] = pb[0];
    b4[2] = pb[1];
    b4[3] = pb[2];
    p->v[2].c = func_00107740(&c);
    p->v[3].c = func_00107740(&c);
    c.a = 0;
    p->v[0].c = func_00107740(&c);
    p->v[1].c = func_00107740(&c);
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (k != 0) {
                A[0] = spline_b073_01E04890(&pa[k - 1], 0, t);
                B[0] = spline_b073_01E04890(&pb[k - 1], 0, t);
                t += 0.25f;
                A[1] = spline_b073_01E04890(&pa[k - 1], 0, t);
                B[1] = spline_b073_01E04890(&pb[k - 1], 0, t);
            } else {
                A[0] = spline_b073_01E04890(a4, 0, t);
                B[0] = spline_b073_01E04890(b4, 0, t);
                t += 0.25f;
                A[1] = spline_b073_01E04890(a4, 0, t);
                B[1] = spline_b073_01E04890(b4, 0, t);
            }
            func_00109A70(&quad[0], &A[0]);
            func_00109A70(&quad[1], &A[1]);
            func_00109A70(&quad[2], &B[0]);
            func_00109A70(&quad[3], &B[1]);
            if (func_00205630(quad, 0x70000000, NULL, p, depth) != 0) {
                func_002075F0(p, ot, 0);
            }
        }
    }
}
#pragma optimization_level reset

/* shape b073:01E05290, 126 insns: b069:01E01A70's four-quad sprite at the effect's own position (s16 x/y/z) at 1/20 scale,
   turned by its 0x3A; each quad that lands on screen is sent at its depth (fptoui) */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b073_01E05290;

typedef struct {
    Rgbaq_b073_01E05290 c;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b073_01E05290;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b073_01E05290 v[4];
    u8 tail[0x20];
} Pkt_b073_01E05290;

typedef struct {
    u8 pad00[0x20];
    Vec4f pts[6];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padC0[0x18];
    u8 xD8[1];
} Obj_b073_01E05290;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 u, v;
    u8 pad0C[0x1C];
    u8 colB[4];
    u8 colA[4];
    u8 pad30[0xA];
    s16 rz;
} Fx_b073_01E05290;

static void func_01E05290_b073(Obj_b073_01E05290 *o, Fx_b073_01E05290 *fx, Pkt_b073_01E05290 *p) {
    extern s32 func_00109270(void *, s32, s32);
    extern Rgbaq_b073_01E05290 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001A23B0(f32);
    extern s32 func_00109100(void *, void *, s32, void *);
    Vec4f quad[4];
    Vec4f t;
    Vec4f scale;
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;

    func_00109270(p, 0, 0);
    p->v[0].c = func_00107740(fx->colA);
    p->v[1].c = func_00107740(fx->colA);
    p->v[2].c = func_00107740(fx->colA);
    p->v[3].c = func_00107740(fx->colB);
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = fx->x;
    t.y = fx->y;
    t.z = fx->z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, o->ot, func_001A23B0(depth[0]));
        }
    }
}
