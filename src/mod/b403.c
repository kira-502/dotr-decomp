#include "common.h"

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00080_b403(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b018:01E00920: draws 20 textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b018_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b018_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b018_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b018_01E005A0;

static void func_01E004D0_b403(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b018_01E005A0 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    pk->nreg = 0x24;
    pk->n = 9;
    pk->regs = 0x24242421 | ((s64)4 << 32);
    pk->pad4 = 0;
    pk->nreg |= 0x800;
    func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
    *(s32 *)&pk->st.t = 0;
    pk->q0 = 0;
    pk->q1 = 0;
    pk->q2 = 0;
    pk->q3 = 0;
    func_00107740(&uv, obj->tex);
    pk->st = uv;
    func_01E00080_b403((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    n = (*(s16 *)(self + 0xB8) != 0) ? *(s16 *)(self + 0xB8) : (s16)20;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += obj->rx;
    rot[1] += obj->ry;
    rot[2] += obj->rz;
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b112:01E00B60, 296 insns, 5 copies: draws a flat ring of 18 quads (inner and outer radius, 20 table steps
   apart) around a position, two colours; depth mode 0 (projected), 1 (far, after a packet tweak) or else front. */

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 xD8[1];
} Obj_b112_01E00B60;

typedef struct {
    u8 pad00[6];
    s16 inner;
    u8 pad08[0x20];
    u8 col0[4];
    u8 col1[4];
    u8 pad30[8];
    s16 outer;
    s16 start;
} Ring_b112_01E00B60;

static void func_01E00850_b403(Obj_b112_01E00B60 *o, Ring_b112_01E00B60 *s, s32 mode, Vec4f pos) {
    extern void func_00107990(void *, void *, s32);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f p2;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    u8 pkt[0x90];
    s32 t;
    s32 k;
    s16 a;
    u8 *p;

    p = pkt;
    a = 0;
    func_00107990(p, s->col0, 2);
    func_00107990(p, s->col1, 1);
    func_001092E0(p, 0);
    func_001094F0(p);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    p2.x = pos.x;
    p2.y = pos.y;
    p2.z = pos.z;
    func_00108EF0(m, &scale, rot, &p2);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 18; k++) {
        if (k == 0) {
            t = s->start + a;
            quad[0].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[0].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[2].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[2].z = s->inner * func_00108030(o->xD8, t, 0);
            t = a + (s->start + 20);
            quad[1].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[1].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[3].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[3].z = s->inner * func_00108030(o->xD8, t, 0);
        } else {
            quad[0] = quad[1];
            quad[2] = quad[3];
            t = a + (s->start + 20);
            quad[1].x = s->outer * func_00108030(o->xD8, t, 1);
            quad[1].z = s->outer * func_00108030(o->xD8, t, 0);
            quad[3].x = s->inner * func_00108030(o->xD8, t, 1);
            quad[3].z = s->inner * func_00108030(o->xD8, t, 0);
        }
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, o->ot, 0);
            }
        } else {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, -1);
            }
        }
        a += 20;
    }
}

/* shape b403:01E00CF0, 127 insns: scene spawn step: red scene colour; t++; frame 1 starts handlers 0x1E015F0 and
   0x1E016D0; on frame 87 it reads the joint point and fires 50 of 0x1E01060, 50 of 0x1E01210, then 0x1E01380 and
   0x1E01460 from it; frames 87/92/98/103 fire one 0x1E00EF0 there */

typedef struct {
    f32 x, y, z, w;
} V4_b403_01E00CF0;

typedef struct {
    u8 pad0[0x250];
    V4_b403_01E00CF0 pos;
    u8 pad260[0x2F30];
    V4_b403_01E00CF0 pt;
    u8 pad31A0[4];
    u8 col[4];
    u8 pad31A8[0x30];
    s16 joint;
    u8 pad31DA[0x18];
    s16 h31F2;
    u8 pad31F4[2];
    s16 t;
} Scene_b403_01E00CF0;

static void func_01E00CF0_b403(Scene_b403_01E00CF0 *g) {
    extern void b403_01E00EF0(void);
    extern void b403_01E01060(void);
    extern void b403_01E01210(void);
    extern void b403_01E01380(void);
    extern void b403_01E01460(void);
    extern void b403_01E015F0(void);
    extern void b403_01E016D0(void);
    extern void b403_01E01D90(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0x57) {
        func_001F5620(func_001F53A0(), g->joint, &g->pt);
    }
    if (g->t == 1) {
        b403_01E01D90(g, b403_01E015F0, 0);
    }
    if (g->t == 1) {
        b403_01E01D90(g, b403_01E016D0, 0);
    }
    if (g->t == 0x57) {
        g->pos.x = g->pt.x;
        g->pos.y = g->pt.y;
        g->pos.z = g->pt.z;
        for (i = 0; i < 50; i++) {
            b403_01E01D90(g, b403_01E01060, 0);
        }
    }
    if (g->t == 0x57 || g->t == 0x5C || g->t == 0x62 || g->t == 0x67) {
        g->pos.x = g->pt.x;
        g->pos.y = g->pt.y;
        g->pos.z = g->pt.z;
        g->h31F2 = 0;
        for (i = 0; i < 1; i++) {
            b403_01E01D90(g, b403_01E00EF0, 0);
        }
    }
    if (g->t == 0x57) {
        g->pos.x = g->pt.x;
        g->pos.y = g->pt.y;
        g->pos.z = g->pt.z;
        for (i = 0; i < 50; i++) {
            b403_01E01D90(g, b403_01E01210, 0);
        }
        b403_01E01D90(g, b403_01E01380, 0);
        b403_01E01D90(g, b403_01E01460, 0);
    }
}

/* shape b112:01E013B0, 87 insns: a blob: on start f38 8, x 0x4000, y 0, a random variant, life 1; colour
   (0x40,0x20,0) or (0,0x80,0x80) when f30 is set; alpha grows by 0x50 (below 0xA0) for 2 ticks; later fades by 8
   once f38 reaches 0x24, and by 15 while the game value 0x31A0 is below 10; f38 grows by 2 per tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b112_01E013B0;

typedef struct {
    u8 pad[0x31A0];
    s32 v;
} Game_b112_01E013B0;

static s32 func_01E00EF0_b403(Game_b112_01E013B0 *g, Spark_b112_01E013B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->x = 0x4000;
        o->y = 0;
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
        o->life = 1;
        if (o->angle == 0) {
            func_001076F0(o->col, 0x40, 0x20, 0);
        } else {
            func_001076F0(o->col, 0, 0x80, 0x80);
        }
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0x23) {
            if (o->col[3] > 9) {
                o->col[3] -= 8;
            } else {
                o->mode = 0;
            }
        }
        if (g->v < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    o->tick++;
    o->f38 += 2;
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01050_b403(void) {
    return 0;
}

/* shape b112:01E018C0, 101 insns, 2 copies: an amber wisp: set up once with two random angles; full for 10 frames, then
   fades out; each frame its x, y and z drift by 9 times a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0x32F8];
    u8 trig[1];
} World_b112_01E018C0;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b112_01E018C0;

static s32 func_01E01060_b403(World_b112_01E018C0 *w, Wisp_b112_01E018C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h38 = 0xD;
        o->frame = 2;
        func_001076F0(o->c0, 0x60, 0x40, 0);
        o->a30 = func_0019A5C8() % 360;
        o->a3A = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 10) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    o->x += 9.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 9.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 9.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b027:01E00DA0, 2 insns, 89 copies: an empty handler that returns 0 */

static s32 func_01E01200_b403(void) {
    return 0;
}

/* shape b112:01E01D20, 89 insns: a spark: on start f38 25, random variant, colour (0x20,0x10,8), random
   direction, spin 3..18, f8 0..9, life 5..11; alpha grows by 0x38 (below 0x71) during the life, then fades out by
   10 and stops; turns by the spin every tick after the first */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b112_01E01D20;

static s32 func_01E01210_b403(s32 arg0, Spark_b112_01E01D20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 25;
        o->kind = func_0019A5C8() % 4;
        func_001076F0(o->col, 0x20, 0x10, 8);
        o->angle = 0;
        o->dir = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 16 + 3;
        o->f8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 5;
        o->mode = 2;
    }
    if (o->tick < o->life) {
        if (o->col[3] < 0x71) {
            o->col[3] += 0x38;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->angle += o->spin;
    }
    o->tick++;
    return 0;
}

/* shape b112:01E01E90, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha held at 0xC0
   for the first 5 ticks, then fades out by 15 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b112_01E01E90;

static s32 func_01E01380_b403(s32 arg0, Flash_b112_01E01E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x14A;
        func_001076F0(o->col, 0xC0, 0x70, 0);
        func_001076F0(o->col2, 0x20, 0x10, 0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0x10;
    }
    if (o->tick < 5) {
        o->col[3] = 0xC0;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b112:01E02420, 97 insns: a point light for the scene: on start sets the light (colour 128/6/3, range
   153) at the effect's position; its strength rises by 0.2 up to 1, then falls by 0.08 and the effect ends; the
   light is switched off (func_001F6C10(0)) once ended, and the effect ends when the game value 0x31A0 is 1 */

typedef struct {
    f32 a, b, c, d;
    f32 x, y, z;
    u8 pad1C[4];
    f32 e, f, g;
} Light_b112_01E02420;

typedef struct {
    u8 pad[0x3000];
    Light_b112_01E02420 light;
    u8 pad302C[0x174];
    s32 v;
} Game_b112_01E02420;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b112_01E02420;

static s32 func_01E01460_b403(Game_b112_01E02420 *g, Fx_b112_01E02420 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a = 128.0f;
        g->light.b = 6.0f;
        g->light.c = 3.0f;
        g->light.d = 0.0f;
        g->light.e = 0.0f;
        g->light.f = 153.0f;
        g->light.g = 0.0f;
        g->light.x = o->x;
        g->light.y = o->y;
        g->light.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->light.g < 1.0f) {
            g->light.g += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (g->light.g > 0.1f) {
        g->light.g -= 0.08f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->v == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b403:01E015F0, 54 insns: volume fade: starts at 0x80; while the game counter at 0x31A0 is over 0x14 it drops by
   10 to 0x30, otherwise it rises by 10 (clamped) and stops at 0x80; func_001F6D00 gets it when the counter is 1,
   else the volume */

typedef struct {
    u8 pad0[0x31A0];
    s32 count;
} Game_b403_01E015F0;

typedef struct {
    u8 pad0[0x30];
    s16 v;
    u8 pad32[0x4];
    s16 mode;
} Fx_b403_01E015F0;

static s32 func_01E015F0_b403(Game_b403_01E015F0 *g, Fx_b403_01E015F0 *o) {
    extern void func_001F6D00(u8);

    if (o->mode == 1) {
        o->v = 0x80;
        o->mode = 2;
    }
    if (g->count > 0x14) {
        if (o->v > 0x30) {
            o->v -= 10;
        } else {
            o->v = 0x30;
        }
    } else {
        if (o->v < 0x80) {
            o->v += 10;
        } else {
            o->v = 0x80;
            o->mode = 0;
        }
        if (o->v > 0x80) {
            o->v = 0x80;
        }
    }
    if (g->count == 1) {
        func_001F6D00(o->v);
    } else {
        func_001F6D00(o->v);
    }
    return 0;
}

/* shape b403:01E016D0, 31 insns: b018:01E02DB0 family: func_001F7170(3, 0) with the module's two floats, then ends the object when the scene value is 10 */

extern f32 D_01E02680_b403;
extern f32 D_01E02688_b403;

typedef struct {
    u8 pad0[0x31A0];
    s32 v;
} Ctx_b403_01E016D0;

typedef struct {
    u8 pad0[0x32];
    s16 h32;
    u8 pad34[2];
    s16 h36;
    u8 pad38[0x1C];
    s16 h54;
    u8 pad56[2];
    s16 h58;
} Obj_b403_01E016D0;

static s32 func_01E016D0_b403(Ctx_b403_01E016D0 *ctx, Obj_b403_01E016D0 *o) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02680_b403;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02688_b403;
    func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
    if (ctx->v == 10) {
        o->h36 = 0;
    }
    return 0;
}

/* shape b403:01E01750 (b403), 398 insns, 1 copy: scene manager: code >= 0 clears the scene, two cameras, 150-frame
   countdown, eight model handles, textures 7..15 and 256 random bytes in -50..49; else runs the spawn step and every
   live node update (B403_OBJ_MOVE_201_ written out in place), draws each live node by kind, grows the scene scale
   after frame 20, counts down and returns 1 / 4 / 2 at frames 77 / 130 / 87, 8 once the countdown runs out */

typedef struct Fx_b403_01E01750 {
    s16 x, y, z;
    u8 pad6[0x24 - 6];
    void *fn;
    u8 pad28[0xC];
    s16 h34;
    s16 used;
    u8 pad38[0x8];
} Fx_b403_01E01750;

typedef struct Scene_b403_01E01750 {
    u8 pad0[0x80];
    s32 ot0;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 cam[0x290 - 0xD8];
    f32 sx, sy, sz;
    u8 pad29C[0x2C0 - 0x29C];
    s32 tex[16];
    Fx_b403_01E01750 fx[180];
    u8 pad3000[0x1A0];
    s32 count;
    u8 pad31A4[8];
    s32 ot;
    u8 pad31B0[0x28];
    s16 model[8];
    u8 pad31E8[0xC];
    s16 id;
    s16 timer;
    s8 rnd[256];
    u8 cam2[0x170];
} Scene_b403_01E01750;

static s32 func_01E01750_b403(s32 arg0, s32 id) {
    Scene_b403_01E01750 *g = (Scene_b403_01E01750 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00CF0_b403();
    extern s32 func_01E00EF0_b403();
    extern s32 func_01E01050_b403();
    extern s32 func_01E01060_b403();
    extern s32 func_01E01200_b403();
    extern s32 func_01E01210_b403();
    extern s32 func_01E01380_b403();
    extern s32 func_01E01460_b403();
    extern s32 func_01E015F0_b403();
    extern s32 func_01E016D0_b403();
    extern void func_01E004D0_b403();
    extern void b403_01E01EC0();
    extern void b403_01E02120();
    extern void b403_01E02460();
    s32 n;
    Vec4f t[2];
    Vec4f r1;
    Vec4f r2;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;

    n = 0;
    g->ot0 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3470);
        func_00107C10(g->cam2);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 150;
        g->model[0] = func_001F5560(func_001F53A0(), 0x31, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x4D, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x16, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x18, 0);
        g->model[5] = func_001F5560(func_001F53A0(), 0x1B, 0);
        g->model[6] = func_001F5560(func_001F53A0(), 0x1A, 0);
        g->model[7] = func_001F5560(func_001F53A0(), 0x19, 0);
        for (i = 7; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 100 - 50;
        }
        return 0;
    }
    func_01E00CF0_b403(g, 0);
    for (i = 0; i < 180; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E00EF0_b403) {
                func_01E00EF0_b403(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01060_b403) {
                func_01E01060_b403(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01210_b403) {
                func_01E01210_b403(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01380_b403) {
                func_01E01380_b403(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01460_b403) {
                func_01E01460_b403(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E015F0_b403) {
                func_01E015F0_b403(g, &g->fx[i]);
            }
            if (g->fx[i].fn == func_01E016D0_b403) {
                f32 b;
                f32 a;

                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02680_b403;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02688_b403;
                func_001F7170(3, 0, (s32)&a, (s32)&b, 0);
                if (g->count == 10) {
                    g->fx[i].used = 0;
                }
            }
        }
    }
    for (i = 0; i < 180; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E00EF0_b403) {
                b403_01E01EC0(g, &g->fx[i], buf, 0);
                b403_01E01EC0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01050_b403) {
                b403_01E02120(g, &g->fx[i], buf, 0);
                b403_01E02120(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01060_b403) {
                b403_01E02460(g, &g->fx[i], buf, 0);
                b403_01E02460(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01200_b403) {
                b403_01E02460(g, &g->fx[i], buf, 0);
                b403_01E02460(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01210_b403) {
                g->tex88 = g->tex[15];
                func_00106080(&r1, 0x9B, g->fx[i].h34, 0);
                g->rect = r1;
                g->hB8 = 14;
                func_01E004D0_b403(g, &g->fx[i], buf, g->rnd);
                g->hB8 = 0;
            }
            if (g->fx[i].fn == func_01E01380_b403) {
                g->tex88 = g->tex[15];
                func_00106080(&r2, 0x9B, g->fx[i].h34, 0);
                g->rect = r2;
                t[1].x = g->fx[i].x;
                t[1].y = g->fx[i].y;
                t[1].z = g->fx[i].z;
                func_01E00850_b403((Obj_b112_01E00B60 *)g, (Ring_b112_01E00B60 *)&g->fx[i], 1, t[1]);
            }
        }
    }
    if (g->timer > 20) {
        if (g->sx < 0.5f) {
            g->sx += 0.01f;
        }
        g->sy = 0.1f;
        if (g->sz < 0.5f) {
            g->sz += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 77) {
        return 1;
    }
    if (g->timer == 130) {
        return 4;
    }
    if (g->timer == 87) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b112:01E038C0, 74 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's value 0x31F2 and 0x31EA and the two arguments; returns 1 if a
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
} Slot_b112_01E038C0;

typedef struct {
    u8 pad[0x250];
    u8 m[0xB0];
    Slot_b112_01E038C0 s[180];
    u8 pad3000[0x1A4];
    u8 r, g, b, a;
    u8 pad31A8[0x42];
    s16 w;
    u8 pad31EC[0x6];
    s16 v;
} Pool_b112_01E038C0;

static s32 func_01E01D90_b403(Pool_b112_01E038C0 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b112_01E038C0 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 180; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 180;
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

/* shape b112:01E039F0, 150 insns: mode 0 sets up the drawing state (a 0x97 matrix from the anim's angle at 0x34,
   colour, the game's texture at 0x2FC); otherwise draws a flat ring of 9 quads 40 apart around the anim's point
   (inner edge at the centre, outer at its radius), scaled (1, 1.5, 1), into the game's target with its depth */

typedef struct {
    f32 x, y, z, w;
} Vec_b112_01E039F0;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b112_01E039F0;

typedef struct {
    u8 pad00[0x2FC];
    s32 texture;
    u8 pad300[0x31AC - 0x300];
    s32 target;
    u8 pad31B0[0x31C8 - 0x31B0];
    f32 depth;
    u8 pad31CC[0x32F8 - 0x31CC];
    u8 trig[1];
} Game_b112_01E039F0;

static void func_01E01EC0_b403(Game_b112_01E039F0 *g, Anim_b112_01E039F0 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b112_01E039F0 quad[4];
    Vec_b112_01E039F0 pos;
    Vec_b112_01E039F0 scale;
    f32 m[16];
    f32 rm[4];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    if (mode == 0) {
        func_00106080(rm, 0x97, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        pos.x = an->x;
        pos.y = an->y;
        pos.z = an->z;
        scale.x = 1.0f;
        scale.y = 1.5f;
        scale.z = 1.0f;
        func_00108EF0(m, &scale, an->rot, &pos);
        quad[0].y = 0.0f;
        quad[1].y = 0.0f;
        quad[2].y = 0.0f;
        quad[3].y = 0.0f;
        for (k = 0; k < 9; k++) {
            a = an->start + j;
            quad[2].x = an->radius * func_00108030(g->trig, a, 1);
            quad[2].z = an->radius * func_00108030(g->trig, a, 0);
            quad[0].x = 0.0f;
            quad[0].z = 0.0f;
            a = j + (an->start + 40);
            quad[3].x = an->radius * func_00108030(g->trig, a, 1);
            quad[3].z = an->radius * func_00108030(g->trig, a, 0);
            quad[1].x = 0.0f;
            quad[1].z = 0.0f;
            if (func_00205630(quad, 0x70000000, m, p, &g->depth) != 0) {
                func_002075F0(p, g->target, (u32)g->depth);
            }
            j += 40;
        }
    }
}

/* shape b112:01E03C50, 205 insns, 2 copies: a fan of 9 thin triangles around the object (each 40 apart, spanning the object's
   span, length from its size), position = pos + vel / 10; mode 0 only sets up the packet (texture 0x97, flat
   colour). Texture corners by the module helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b112_01E03C50;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b112_01E03C50;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b112_01E03C50 c;
    struct {
        u64 tc;
        Xyz_b112_01E03C50 p;
    } v[4];
} Pkt_b112_01E03C50;

typedef struct {
    u8 pad0[0x2FC];
    void *texture;
    u8 pad300[0x2EAC];
    s32 ot;
    u8 pad31B0[0x18];
    f32 dep;
    u8 pad31CC[0x12C];
    u8 trig[1];
} Ctx_b112_01E03C50;

typedef struct {
    s16 x, y, z;
    s16 span;
    s16 vx, vy, vz;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b112_01E03C50;

static void func_01E02120_b403(Ctx_b112_01E03C50 *c, Fan_b112_01E03C50 *o, Pkt_b112_01E03C50 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b112_01E03C50 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s16 span;
    f32 dx;
    s32 k;
    s32 t;
    f32 dy;
    s16 a;
    f32 dz;

    span = o->span;
    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00080_b403((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    dx = o->vx;
    dy = o->vy;
    dz = o->vz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x += dx;
    pos.y += dy;
    pos.z += dz;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, o->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        quad[0].x = 0.0f;
        quad[0].z = 0.0f;
        t = a + (o->ang + span);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        quad[1].x = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
            func_002075F0(p, c->ot, (u32)c->dep);
        }
        a += 0x28;
    }
}

/* shape b112:01E04260, 134 insns, 2 copies: one textured square of an object (b053:01E022F0 family): texture and page pick
   by its handler (shape b112:01E01A60 or not); mode 0 only sets up the packet's texture, otherwise additive for that
   handler, position = pos + vel / 10, scaled 0.1, size from the object, drawn via func_00108F90. */


typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x16];
    void *fn;
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b112_01E04260;

static void func_01E02460_b403(u8 *ctx, Obj_b112_01E04260 *o, void *pkt, s32 mode) {
    extern s32 b403_01E01200();
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        if (o->fn == (void *)b403_01E01200) {
            func_00106080(td, 0x14, o->page, td);
        } else {
            func_00106080(td, 0x9B, o->page, td);
        }
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        if (o->fn == (void *)b403_01E01200) {
            func_00208700(pkt, *(void **)(ctx + 0x2C8), 1);
            return;
        }
        func_00208700(pkt, *(void **)(ctx + 0x2FC), 1);
        return;
    }
    if (o->fn == (void *)b403_01E01200) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    }
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)&rot);
    dx = o->vx;
    dy = o->vy;
    dz = o->vz;
    dx /= 10.0f;
    dy /= 10.0f;
    dz /= 10.0f;
    pos.x = o->x + dx;
    pos.y = o->y + dy;
    pos.z = o->z + dz;
    func_00108EF0(m, &scale, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}
