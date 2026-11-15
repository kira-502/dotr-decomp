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

static void func_01E00080_b112(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

static void func_01E004D0_b112(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00080_b112((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

/* OVL_WARM: compile warm */

/* shape b112:01E00850, 195 insns: b020:01E00E70 family: 4 rotated quads (func_00108D60 from fx->u/v, z rotation fx->rz) at pos, drawn by depth or at far z */

typedef struct {
    f32 u, v;
} Uv_b112_01E00850;

typedef struct {
    Uv_b112_01E00850 st;
    u64 rgba;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b112_01E00850;

typedef struct {
    s16 count;
    u16 flags;
    s32 pad;
    u64 regs;
    Vtx_b112_01E00850 v[4];
    u8 tail[0x20];
} Pkt_b112_01E00850;

typedef struct {
    u8 pad00[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    u8 tex[0x2A];
    s16 page;
    u8 padcol2[0x18];
    u8 xD8[1];
} Obj_b112_01E00850;

typedef struct {
    u8 pad00[8];
    s16 u;
    s16 v;
    u8 pad0C[0x1C];
    u8 col[4];
    u8 col2[4];
    u8 pad30[8];
    s16 size;
    s16 rz;
} Fx_b112_01E00850;

static void func_01E00850_b112(Obj_b112_01E00850 *o, Fx_b112_01E00850 *fx, s32 mode, Vec4f pos) {
    extern s32 func_00109270(void *, s32, s32);
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
    Pkt_b112_01E00850 pkt;
    Uv_b112_01E00850 uv0;
    Uv_b112_01E00850 uv1;
    Uv_b112_01E00850 uv2;
    Uv_b112_01E00850 uv3;
    s16 i;
    Pkt_b112_01E00850 *p;

    p = &pkt;
    func_00109270(p, 0, 0);
    func_00107740(&uv0, fx->col2);
    p->v[0].st = uv0;
    func_00107740(&uv1, fx->col2);
    p->v[1].st = uv1;
    func_00107740(&uv2, fx->col2);
    p->v[2].st = uv2;
    func_00107740(&uv3, fx->col);
    p->v[3].st = uv3;
    func_00108500(p, o->tex, o->page);
    func_00208700(p, o->texture, 1);
    scale.x = 0.05f;
    scale.y = 0.05f;
    scale.z = 0.05f;
    func_00205C40((s32)rot);
    t.x = pos.x;
    t.y = pos.y;
    t.z = pos.z;
    func_00108EF0(m, &scale, rot, &t);
    rot[2] = fx->rz;
    rot[1] = 0;
    rot[0] = 0;
    for (i = 0; i < 4; i++) {
        func_00108D60(quad, fx->u, fx->v, i);
        func_00109100(quad, rot, 2, o->xD8);
        if (mode == 0) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, o->ot, (u32)depth[0]);
            }
        } else if (mode == 1) {
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0(p, o->ot, 0);
            }
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

static void func_01E00B60_b112(Obj_b112_01E00B60 *o, Ring_b112_01E00B60 *s, s32 mode, Vec4f pos) {
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

/* OVL_WARM */

/* shape b112:01E01000, 233 insns: the b112 module's event step: red scene colour, counts ticks (0x31F6); at 92 saves
   joint 0x31D8 (0x3190) and spawns 50 b112:01E018C0 there; at 92/97/103/108 one b112:01E013B0 (slot 0) there; at 92
   also 50 b112:01E01D20, b112:01E01E90 and b112:01E02420; from 23 to 101 two b112:01E01F70 a tick at joint 0x31DA
   jittered, pushed along z by 2..11 x sin of the model's turn; from 2 to 101 one b112:01E021A0 at a random angle and
   one b112:01E022D0 at 90 (0x31EA) */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x3190 - 0x260];
    Vec4f save;
    u8 pad31A0[4];
    u8 col[4];
    u8 pad31A8[0x31D8 - 0x31A8];
    s16 j0;
    s16 j1;
    u8 pad31DC[0x31EA - 0x31DC];
    s16 ang;
    u8 pad31EC[6];
    s16 slot;
    u8 pad31F4[2];
    s16 count;
    u8 pad31F8[0x32F8 - 0x31F8];
    u8 trig[4];
} Ctx_b112_01E01000;

static void func_01E01000_b112(Ctx_b112_01E01000 *g) {
    extern s32 b112_01E013B0(void);
    extern s32 b112_01E018C0(void);
    extern s32 b112_01E01D20(void);
    extern s32 b112_01E01E90(void);
    extern s32 b112_01E01F70(void);
    extern s32 b112_01E021A0(void);
    extern s32 b112_01E022D0(void);
    extern s32 b112_01E02420(void);
    extern void b112_01E038C0(Ctx_b112_01E01000 *, s32 (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[4];
    s32 r[4];
    f32 s;
    s32 z;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count == 92) {
        func_001F5620(func_001F53A0(), g->j0, &g->save);
    }
    if (g->count == 92) {
        g->pos.x = g->save.x;
        g->pos.y = g->save.y;
        g->pos.z = g->save.z;
        for (i = 0; i < 50; i++) {
            b112_01E038C0(g, b112_01E018C0, 0);
        }
    }
    if (g->count == 92 || g->count == 97 || g->count == 103 || g->count == 108) {
        g->pos.x = g->save.x;
        g->pos.y = g->save.y;
        g->pos.z = g->save.z;
        g->slot = 0;
        for (i = 0; i < 1; i++) {
            b112_01E038C0(g, b112_01E013B0, 0);
        }
    }
    if (g->count == 92) {
        g->pos.x = g->save.x;
        g->pos.y = g->save.y;
        g->pos.z = g->save.z;
        for (i = 0; i < 50; i++) {
            b112_01E038C0(g, b112_01E01D20, 0);
        }
        b112_01E038C0(g, b112_01E01E90, 0);
        b112_01E038C0(g, b112_01E02420, 0);
    }
    if (g->count > 22 && g->count < 102) {
        for (i = 0; i < 2; i++) {
            func_001F6160(func_001F53A0(), r);
            s = func_00108030(g->trig, (s32)(r[1] / 180.0f) - 180, 1);
            z = s * (func_0019A5C8() % 10 + 2);
            func_001F5620(func_001F53A0(), g->j1, v);
            g->pos.x = v[0] + func_0019A5C8() % 20 - 10.0f;
            g->pos.y = v[1] + func_0019A5C8() % 12 - 3.0f;
            g->pos.z = v[2] + z;
            b112_01E038C0(g, b112_01E01F70, 0);
        }
    }
    if (g->count > 1 && g->count < 102) {
        for (i = 0; i < 1; i++) {
            g->ang = func_0019A5C8() % 360;
            b112_01E038C0(g, b112_01E021A0, 0);
            g->ang = 90;
            b112_01E038C0(g, b112_01E022D0, 0);
        }
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

static s32 func_01E013B0_b112(Game_b112_01E013B0 *g, Spark_b112_01E013B0 *o) {
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

/* OVL_WARM */

/* shape b112:01E01510, 166 insns: a dark red streak from joint B (g+0x31E2) towards joint A (g+0x31D8): on start no spin,
   hold 2 (4 from scene time 50), height 5..19; it sits on joint B, aims at A (pitch from the flat and full distances,
   func_001082B0), sets its swing to 50 x sin(pitch - 45) and its length to 5 x the depth gap; alpha up by 64 for 2
   ticks; its phase h3A runs 0..89 */

typedef struct {
    u8 pad0[0x31D8];
    s16 ja;
    u8 pad31DA[8];
    s16 jb;
    u8 pad31E4[0x12];
    s16 time;
    u8 pad31F8[0x100];
    u8 tab[1];
} Game_b112_01E01510;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    u8 pad8[2];
    s16 swing;
    s16 len;
    u8 padE[2];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 h34;
    s16 mode;
    s16 h38;
    s16 phase;
} Obj_b112_01E01510;

static s32 func_01E01510_b112(Game_b112_01E01510 *g, Obj_b112_01E01510 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_001A6C60(f32);
    extern s16 func_001082B0(s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    f32 v[2][4];
    f32 dy;
    f32 dz;
    f32 dx;
    s16 r;
    s16 l;

    func_001076F0(o->col, 0x30, 0x10, 0);
    if (o->mode == 1) {
        o->w10 = 0;
        o->w14 = 0;
        o->w18 = 0;
        o->h34 = 0;
        if (g->time < 50) {
            o->hold = 2;
        } else {
            o->hold = 4;
        }
        o->h = func_0019A5C8() % 15 + 5;
        o->mode = 2;
        o->col[3] = 0;
    }
    func_001F5620(func_001F53A0(), g->ja, v[0]);
    func_001F5620(func_001F53A0(), g->jb, v[1]);
    o->x = v[1][0];
    o->y = v[1][1];
    o->z = v[1][2];
    dx = v[0][0] - v[1][0];
    dy = v[0][1] - v[1][1];
    dz = v[0][2] - v[1][2];
    r = func_001A6C60(dx * dx + dz * dz);
    l = func_001A6C60(dx * dx + (dy * dy + dz * dz));
    o->swing = 50.0f * func_00108030(g->tab, func_001082B0(r, l) - 45, 1);
    o->len = 5.0f * dz;
    if (o->t < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    }
    func_00108030(g->tab, o->phase, 1);
    func_00108030(g->tab, o->phase, 0);
    o->h38 = 20;
    o->phase++;
    if (o->phase >= 90) {
        o->phase %= 90;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b112_01E017B0;

static s32 func_01E017B0_b112(s32 unused, Obj_b112_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
    if (o->h36 == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (o->h30 == 0) {
            o->w18 = -0x2000;
        } else {
            o->w18 = 0x2000;
        }
        o->h6 = o->h30;
        o->h34 = func_0019A5C8() % 7;
    }
    if (o->h32 < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->col[3] > 20) {
            o->col[3] -= 0x13;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
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

static s32 func_01E018C0_b112(World_b112_01E018C0 *w, Wisp_b112_01E018C0 *o) {
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

/* shape b112:01E01A60, 175 insns: b714:01E02E50 family puff (lilac 0x3F/0x30/0x3F for kinds 0-1, grey 0x10 else), size from 10 growing 5 to 40, frame up to 7 every other tick, angles 0..359 / 0..89; alpha up by 0x20 to 0x60 for 3 ticks, then down by 9; for its first 5 ticks sits on its tracked point (ctx+0x31D8 by kind; kinds 2+ only for 3); drifts 8 along the heading and 2 up */

typedef struct {
    u8 pad0[0x31D8];
    s16 ids[4];
    u8 pad31E0[0x32F8 - 0x31E0];
    u8 trig[1];
} Game_b112_01E01A60;

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 kind;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 heading;
} Fx_b112_01E01A60;

static s32 func_01E01A60_b112(Game_b112_01E01A60 *g, Fx_b112_01E01A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 v[4];

    if (o->mode == 1) {
        if (o->kind < 2) {
            func_001076F0(o->col, 0x3F, 0x30, 0x3F);
        } else {
            func_001076F0(o->col, 0x10, 0x10, 0x10);
        }
        o->f38 = 10;
        o->heading = func_0019A5C8() % 360;
        o->f34 = 0;
        o->h6 = func_0019A5C8() % 90;
        o->mode = 2;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x20;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick < 6) {
        func_001F5620(func_001F53A0(), g->ids[o->kind], v);
        if (o->kind < 2) {
            o->x = v[0];
            o->y = v[1];
            o->z = v[2];
        } else if (o->tick < 4) {
            o->x = v[0];
            o->y = v[1];
            o->z = v[2];
        }
    }
    if (o->f38 < 40) {
        o->f38 += 5;
    }
    if (o->tick % 2 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->h8 = o->h8 + 8.0f * func_00108030(g->trig, o->heading, 0);
    o->hA = o->hA + 2.0f * func_00108030(g->trig, o->h6, 1);
    o->hC = o->hC + 8.0f * func_00108030(g->trig, o->heading, 1);
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

static s32 func_01E01D20_b112(s32 arg0, Spark_b112_01E01D20 *o) {
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

static s32 func_01E01E90_b112(s32 arg0, Flash_b112_01E01E90 *o) {
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

/* shape b112:01E01F70, 139 insns: a rising ember in a random warm colour (yellow, orange or brown): size 3..11, frame
   0..3, rise 3..10, f8 0..9, fA 2..6, fC 2..16, f6 5..11; alpha grows by 0x30 (to 0x60) for 3 ticks, then fades by 10
   (ends below 0x11); rises every tick */

typedef struct {
    u8 pad0[6];
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 rise;
    u8 pad10[0x18];
    u8 col[4];
    u8 pad2C[4];
    s16 h;
    s16 t;
    s16 frame;
    s16 mode;
    s16 size;
    s16 ang;
} Fx_b112_01E01F70;

static s32 func_01E01F70_b112(s32 arg0, Fx_b112_01E01F70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s16 c;

    if (o->mode == 1) {
        o->size = func_0019A5C8() % 9 + 3;
        o->frame = func_0019A5C8() % 4;
        c = func_0019A5C8() % 3;
        if (c == 0) {
            func_001076F0(o->col, 0x80, 0x80, 8);
        } else if (c == 1) {
            func_001076F0(o->col, 0x80, 0x40, 8);
        } else if (c == 2) {
            func_001076F0(o->col, 0x60, 0x40, 0x20);
        }
        o->h = 0;
        o->ang = func_0019A5C8() % 360;
        o->rise = func_0019A5C8() % 8 + 3;
        o->f8 = func_0019A5C8() % 10;
        o->fA = func_0019A5C8() % 5 + 2;
        o->fC = func_0019A5C8() % 15 + 2;
        o->f6 = func_0019A5C8() % 7 + 5;
        o->mode = 2;
    }
    if (o->t < 3) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->h += o->rise;
    o->t++;
    return 0;
}

/* shape b112:01E021A0, 76 insns: a grey-yellow flash: frame 6, size 6 by 100, random kind 0..4; both alphas up by 0x40 to 0x40 on
   the first frame, then down by 13; ends when the first runs out; turns 4 a frame */

typedef struct {
    u8 pad0[8];
    s16 w;
    s16 h;
    u8 padC[0x1C];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b112_01E021A0;

static s32 func_01E021A0_b112(void *arg0, Obj_b112_01E021A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 6;
        func_001076F0(o->c0, 0x30, 0x30, 0x30);
        func_001076F0(o->c1, 0x50, 0x50, 0);
        o->w = 6;
        o->h = 0x64;
        o->kind = func_0019A5C8() % 5;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 1) {
        if (o->c0[3] < 0x40) {
            o->c0[3] += 0x40;
        }
        if (o->c1[3] < 0x40) {
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
    o->t++;
    o->ang += 4;
    return 0;
}

/* shape b112:01E022D0, 81 insns: a grey-yellow blinking flash: frame 30, random kind 0..4 and angle; alpha up by 0x40 on the
   first frame, then down by 19 until it ends; first colour blinks grey by frame parity */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    s16 kind;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b112_01E022D0;

static s32 func_01E022D0_b112(void *arg0, Obj_b112_01E022D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x1E;
        func_001076F0(o->c0, 8, 8, 8);
        func_001076F0(o->c1, 0x50, 0x50, 0);
        o->kind = func_0019A5C8() % 5;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 1) {
        o->c0[3] += 0x40;
    } else if (o->c0[3] > 0x14) {
        o->c0[3] -= 0x13;
    } else {
        o->state = 0;
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x30, 0x30, 0x30);
    } else {
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
    }
    o->t++;
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

static s32 func_01E02420_b112(Game_b112_01E02420 *g, Fx_b112_01E02420 *o) {
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

/* shape b112:01E025B0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x31A0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x31A0];
    s32 state;
} Game_b112_01E025B0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b112_01E025B0;

static s32 func_01E025B0_b112(Game_b112_01E025B0 *g, Fade_b112_01E025B0 *o) {
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

/* shape b112:01E02670, 20 insns: func_001F7170(2, 2, &a, &b, 1) with copies of the module's two floats at
   0x01E04880 and 0x01E04888, return 0 */

typedef struct {
    f32 v;
} F_b112_01E02670;

extern F_b112_01E02670 D_01E04880_b112;
extern F_b112_01E02670 D_01E04888_b112;

static s32 func_01E02670_b112(void) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b112_01E02670 a;
    F_b112_01E02670 b;

    a = D_01E04880_b112;
    b = D_01E04888_b112;
    func_001F7170(2, 2, &a, &b, 1);
    return 0;
}

/* shape b112:01E026C0 (b112), 1151 insns, 1 copy: the b112 scene manager in b774:01E02610's form (b194 family),
   written from the asm: with a scene id (>= 0) it clears the scene, resets both cameras, keeps the id, sets the
   145-frame countdown, takes eight joints, loads textures 7..15 and fills the 256-byte jitter table; otherwise it
   runs the module step and every live node update (func_01E02670 written out), draws every live node (twice by its
   drawer; the flash ring at the node, the ember sprites, and two blinking kinds drawn on four joint segments a fifth
   of the way along per node step, held while the scene count is in 51..77 / 24..30), grows the scale by 0.01 up to
   0.5 after frame 20, counts down and returns 1 / 4 / 2 at frames 82 / 140 / 125, 6 in 93..119, 8 once the countdown
   runs out */

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x1E];
    void *fn;
    u8 pad28[8];
    s16 k;
    s16 h32;
    s16 h34;
    s16 used;
    u8 pad38[8];
} Slot_b112_01E026C0;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rm;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1A];
    void *pD4;
    u8 crdD8[0x1B8];
    f32 sx, sy, sz;
    u8 pad29C[0x24];
    s32 tex[16];
    Slot_b112_01E026C0 slot[180];
    u8 pad3000[0xF0];
    u8 x30F0[0xB0];
    s32 count;
    u8 pad31A4[8];
    s32 ot;
    u8 pad31B0[0x28];
    s16 j[8];
    u8 pad31E8[0xC];
    s16 id;
    s16 state;
    s8 jit[0x100];
    u8 crd[0x178];
} Scene_b112_01E026C0;

static s32 func_01E026C0_b112(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001F7170(s32, s32, void *, void *, s32);
    extern void b112_01E01000();
    extern void b112_01E039F0();
    extern void b112_01E03C50();
    extern void b112_01E03F90();
    extern void b112_01E04260();
    extern void b112_01E04480();
    Scene_b112_01E026C0 *g = (Scene_b112_01E026C0 *)arg0;
    s32 n;
    Vec4f w[2];
    Vec4f v[2];
    Vec4f rm;
    Vec4f rm2;
    Vec4f rm3;
    Vec4f rm4;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 m;
    s32 j;
    s32 i;

    n = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x3470);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x91;
        g->j[0] = func_001F5560(func_001F53A0(), 0x15, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x4D, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x16, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x18, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x1B, 0);
        g->j[6] = func_001F5560(func_001F53A0(), 0x1A, 0);
        g->j[7] = func_001F5560(func_001F53A0(), 0x19, 0);
        for (i = 7; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 100 - 50;
        }
        return 0;
    }
    b112_01E01000(g, 0);
    for (i = 0; i < 180; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == func_01E013B0_b112) {
                func_01E013B0_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01510_b112) {
                func_01E01510_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E017B0_b112) {
                func_01E017B0_b112((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E018C0_b112) {
                func_01E018C0_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01A60_b112) {
                func_01E01A60_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01D20_b112) {
                func_01E01D20_b112((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01E90_b112) {
                func_01E01E90_b112((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E01F70_b112) {
                func_01E01F70_b112((s32)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E021A0_b112) {
                func_01E021A0_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E022D0_b112) {
                func_01E022D0_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02420_b112) {
                func_01E02420_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E025B0_b112) {
                func_01E025B0_b112((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == func_01E02670_b112) {
                F_b112_01E02670 fb;
                F_b112_01E02670 fa;

                fa = D_01E04880_b112;
                fb = D_01E04888_b112;
                func_001F7170(2, 2, &fa, &fb, 1);
            }
        }
    }
    for (i = 0; i < 180; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == func_01E013B0_b112) {
                b112_01E039F0(g, &g->slot[i], buf, 0);
                b112_01E039F0(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E01510_b112) {
                b112_01E03C50(g, &g->slot[i], buf, 0);
                b112_01E03C50(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E017B0_b112) {
                b112_01E03F90(g, &g->slot[i], buf, 0);
                b112_01E03F90(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E018C0_b112) {
                b112_01E04260(g, &g->slot[i], buf, 0);
                b112_01E04260(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E01A60_b112) {
                b112_01E04260(g, &g->slot[i], buf, 0);
                b112_01E04260(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == func_01E01D20_b112) {
                g->tex88 = g->tex[15];
                func_00106080(&rm, 0x9B, g->slot[i].h34, NULL);
                g->rm = rm;
                g->hB8 = 0xE;
                func_01E004D0_b112((void *)g, (void *)&g->slot[i], buf, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == func_01E01E90_b112) {
                g->tex88 = g->tex[15];
                func_00106080(&rm2, 0x9B, g->slot[i].h34, NULL);
                g->rm = rm2;
                w[1].x = g->slot[i].x;
                w[1].y = g->slot[i].y;
                w[1].z = g->slot[i].z;
                func_01E00B60_b112((void *)g, (void *)&g->slot[i], 1, w[1]);
            }
            if (g->slot[i].fn == func_01E01F70_b112) {
                g->tex88 = g->tex[15];
                func_00106080(&rm3, 0x9E, g->slot[i].h34, NULL);
                g->rm = rm3;
                g->pD4 = g->x30F0;
                b112_01E04480(g, &g->slot[i], buf, g->jit);
            }
            if (g->slot[i].fn == func_01E021A0_b112) {
                g->tex88 = g->tex[15];
                func_00106080(&rm4, 0x9A, 1, NULL);
                g->rm = rm4;
                m = 1;
                if (g->state > 0x32 && g->state < 0x4E) {
                    m = 0;
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[2], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[3], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00850_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[3], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[4], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00850_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
                m = 1;
                if (g->state >= 0x18 && g->state < 0x1F) {
                    m = 0;
                }
                if (g->state > 0x32 && g->state < 0x4E) {
                    m = 0;
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[5], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[6], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00850_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[6], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[7], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00850_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
            }
            if (g->slot[i].fn == func_01E022D0_b112) {
                m = 1;
                if (g->state > 0x32 && g->state < 0x4E) {
                    m = 0;
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[2], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[3], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00B60_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[3], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[4], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00B60_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
                m = 1;
                if (g->state >= 0x18 && g->state < 0x1F) {
                    m = 0;
                }
                if (g->state > 0x32 && g->state < 0x4E) {
                    m = 0;
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[5], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[6], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00B60_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
                for (j = 0; j < 1; j++) {
                    func_001F5620(func_001F53A0(), g->j[6], &v[0]);
                    func_001F5620(func_001F53A0(), g->j[7], &v[1]);
                    w[0].x = (v[1].x - v[0].x) / 5.0f;
                    w[0].y = (v[1].y - v[0].y) / 5.0f;
                    w[0].z = (v[1].z - v[0].z) / 5.0f;
                    w[1].x = v[0].x + w[0].x * g->slot[i].k;
                    w[1].y = v[0].y + w[0].y * g->slot[i].k;
                    w[1].z = v[0].z + w[0].z * g->slot[i].k;
                    func_01E00B60_b112((void *)g, (void *)&g->slot[i], m, w[1]);
                }
            }
        }
    }
    if (g->state > 20) {
        if (g->sx < 0.5) {
            g->sx += 0.01f;
        }
        g->sy = 0.1f;
        if (g->sz < 0.5) {
            g->sz += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->state == 0x52) {
        return 1;
    }
    if (g->state == 0x8C) {
        return 4;
    }
    if (g->state == 0x7D) {
        return 2;
    }
    if (g->state > 0x5C && g->state < 0x78) {
        return 6;
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

static s32 func_01E038C0_b112(Pool_b112_01E038C0 *o, s32 a, s32 b) {
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

static void func_01E039F0_b112(Game_b112_01E039F0 *g, Anim_b112_01E039F0 *an, void *p, s32 mode) {
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

static void func_01E03C50_b112(Ctx_b112_01E03C50 *c, Fan_b112_01E03C50 *o, Pkt_b112_01E03C50 *p, s32 mode) {
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
        func_01E00080_b112((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
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

/* shape b112:01E03F90, 179 insns: b112:01E03C50's fan of 9 thin triangles scaled 1 x 1.5 x 1 at the object's
   position (no drift); mode 0 sets up the packet with texture 0x97. Texture corners by the module helper (shape
   b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b112_01E03F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b112_01E03F90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b112_01E03F90 c;
    struct {
        u64 tc;
        Xyz_b112_01E03F90 p;
    } v[4];
} Pkt_b112_01E03F90;

typedef struct {
    u8 pad0[0x2FC];
    void *texture;
    u8 pad300[0x2EAC];
    s32 ot;
    u8 pad31B0[0x18];
    f32 dep;
    u8 pad31CC[0x12C];
    u8 trig[1];
} Ctx_b112_01E03F90;

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
} Fan_b112_01E03F90;

static void func_01E03F90_b112(Ctx_b112_01E03F90 *c, Fan_b112_01E03F90 *o, Pkt_b112_01E03F90 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b112_01E03F90 func_00107740(void *);
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
    s32 k;
    s32 t;
    s16 a;

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
        func_01E00080_b112((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
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

static void func_01E04260_b112(u8 *ctx, Obj_b112_01E04260 *o, void *pkt, s32 mode) {
    extern s32 b112_01E01A60();
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
        if (o->fn == (void *)b112_01E01A60) {
            func_00106080(td, 0x14, o->page, td);
        } else {
            func_00106080(td, 0x9B, o->page, td);
        }
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        if (o->fn == (void *)b112_01E01A60) {
            func_00208700(pkt, *(void **)(ctx + 0x2C8), 1);
            return;
        }
        func_00208700(pkt, *(void **)(ctx + 0x2FC), 1);
        return;
    }
    if (o->fn == (void *)b112_01E01A60) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b112", func_01E04480_b112);
