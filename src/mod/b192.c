#include "common.h"

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E00080_b192(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00260_b192(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

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

static void func_01E00330_b192(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b045:01E005A0, 118 insns, 7 copies: one camera-facing sprite at the object position plus offset / 10,
   scaled by obj->size: the single-sprite member of the b018:01E00920 family. Calls the module's
   sprite-UV helper (shape b008:01E00080) as a static function. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E005A0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E005A0 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E005A0;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E005A0;

static void func_01E00780_b192(u8 *self, Obj_b045_01E005A0 *obj, Pk_b045_01E005A0 *pk, s8 *base) {
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E005A0 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

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
    func_01E00330_b192((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, rot, &pos);
    r = obj->size;
    func_00108CE0(m, r, r);
    if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
        func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
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

static void func_01E00960_b192(u8 *self, Obj_b018_01E005A0 *obj, Pk_b018_01E005A0 *pk, s8 *base) {
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
    func_01E00330_b192((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
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

/* shape b192:01E00CE0, 178 insns: b112:01E03C50 family fan of 18 thin triangles 20 apart (size 0x38) at the object,
   scaled 0.1 and turned by the camera plus the object's turn (a quarter more on x); the two inner corners take the
   first colour and the two outer the second */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b192_01E00CE0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    struct {
        Rgbaq_b192_01E00CE0 c;
        u64 p;
    } v[4];
} Pkt_b192_01E00CE0;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[0x54];
    u8 trig[1];
} Ctx_b192_01E00CE0;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    u8 pad30[8];
    s16 size;
    s16 ang;
} Fan_b192_01E00CE0;

static void func_01E00CE0_b192(Ctx_b192_01E00CE0 *c, Fan_b192_01E00CE0 *o, Pkt_b192_01E00CE0 *p) {
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern Rgbaq_b192_01E00CE0 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    s32 rot[4];
    s32 k;
    s32 t;
    s16 a;

    a = 0;
    func_001092E0(p, 0);
    func_001094F0(p);
    p->v[0].c = func_00107740(o->col);
    p->v[1].c = func_00107740(o->col);
    p->v[2].c = func_00107740(o->col2);
    p->v[3].c = func_00107740(o->col2);
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += o->rot[0] + 0x4000;
    rot[1] += o->rot[1];
    rot[2] += o->rot[2];
    func_00108EF0(m, &scale, rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 18; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        t = a + (o->ang + 20);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0(p, c->ot, (u32)depth[0]);
        }
        a += 20;
    }
}

/* OVL_WARM */
/* func_00108030 really takes an s16 angle (functions.h says s32): hide that prototype */

/* shape b192:01E00FB0, 253 insns: scene step of a joint-anchored burst: the scene colour turns red-black, the tick
   0x365A counts; the scene point follows joint 0x3648; from tick 32 / 36 it spawns three effects each tick there;
   at tick 85, at joint 0x364C, it spawns 0x1E015D0, fifteen 0x1E01DA0 scattered +-10 around it, 0x1E019C0 and
   thirteen pairs of 0x1E01A60 stepping along the joint's heading; the angle 0x3650 turns 2 a tick */

typedef struct {
    f32 x, y, z;
    u8 padC[0xB2 - 0xC];
    s16 hB2;
    u8 padB4[0x764 - 0xB4];
    u8 x764[0x3614 - 0x764];
    u8 col[4];
    u8 pad3618[0x3648 - 0x3618];
    s16 j0;
    u8 pad364A[2];
    s16 j1;
    u8 pad364E[2];
    s16 ang;
    u8 pad3652[8];
    s16 tick;
    u8 pad365C[0x375C - 0x365C];
    u8 trig[1];
} G_b192_01E00FB0;

static void func_01E00FB0_b192(G_b192_01E00FB0 *g) {
    extern f32 func_00108030(void *table, s16 angle, s32 axis);
    extern s32 b192_01E015D0(void);
    extern s32 b192_01E019C0(void);
    extern s32 b192_01E01A60(void);
    extern s32 b192_01E01DA0(void);
    extern s32 b192_01E01F00(void);
    extern s32 b192_01E020D0(void);
    extern s32 b192_01E02250(void);
    extern s32 b192_01E02F00(G_b192_01E00FB0 *, s32 (*)(void), s32, void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, s32 *);
    s32 i;
    s32 a;
    f32 s;
    Vec4f p;
    s32 r[4];
    s32 r2[4];

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->tick++;
    func_001F5620(func_001F53A0(), g->j0, &p);
    g->x = p.x;
    g->y = *(f32 *)(u32)&p.y;
    g->z = *(f32 *)(u32)&p.z;
    if (g->tick > 31) {
        b192_01E02F00(g, b192_01E01F00, 0, g->x764);
    }
    if (g->tick > 31) {
        b192_01E02F00(g, b192_01E020D0, 0, g->x764);
    }
    if (g->tick > 35) {
        b192_01E02F00(g, b192_01E02250, 0, g->x764);
    }
    if (g->tick == 85) {
        b192_01E02F00(g, b192_01E015D0, 0, g->x764);
    }
    func_001F5620(func_001F53A0(), g->j1, &p);
    if (g->tick == 85) {
        func_001F6160(func_001F53A0(), r);
        a = (s32)((f32)r[1] / 180.0f);
        for (i = 0; i < 15; i++) {
            func_0019A5C8();
            func_00108030(g->trig, a - 180, 1);
            g->x = p.x + (f32)(func_0019A5C8() % 20) - 10.0f;
            g->y = *(f32 *)(u32)&p.y + (f32)(func_0019A5C8() % 20) - 10.0f;
            g->z = *(f32 *)(u32)&p.z + (f32)(func_0019A5C8() % 20) - 10.0f;
            b192_01E02F00(g, b192_01E01DA0, 0, g->x764);
        }
    }
    if (g->tick == 85) {
        b192_01E02F00(g, b192_01E019C0, 0, g->x764);
    }
    if (g->tick == 85) {
        func_001F6160(func_001F53A0(), r2);
        s = -func_00108030(g->trig, (s32)((f32)r2[1] / 180.0f) - 180, 1);
        for (i = 0; i < 13; i++) {
            g->x = p.x;
            g->y = *(f32 *)(u32)&p.y;
            g->z = *(f32 *)(u32)&p.z + s * i;
            g->hB2 = 0;
            b192_01E02F00(g, b192_01E01A60, 0, g->x764);
            g->x = p.x;
            g->y = *(f32 *)(u32)&p.y;
            g->z = *(f32 *)(u32)&p.z + s * i;
            g->hB2 = 1;
            b192_01E02F00(g, b192_01E01A60, 0, g->x764);
        }
    }
    g->ang += 2;
    if (g->ang >= 360) {
        g->ang %= 360;
    }
}

/* shape b192:01E013B0, 134 insns: b019:01E01F60 with its sine table at ctx+0x375C */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x375C];
    u8 tab[1];
} Mgr_b192_01E013B0;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b192_01E013B0;

static s32 func_01E013B0_b192(Mgr_b192_01E013B0 *m, Fx_b192_01E013B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

/* shape b192:01E015D0, 79 insns: a green-purple rising glow: frame 650 rising by 4, random sub-frame 0..6; alpha up by 0x50 to
   0xA0 for 2 frames, then down by 13 past frame 20, and also by 15 while the game state is below 10 */

typedef struct {
    u8 pad0[0x3610];
    s32 state;
} Game_b192_01E015D0;

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b192_01E015D0;

static s32 func_01E015D0_b192(Game_b192_01E015D0 *g, Obj_b192_01E015D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x28A;
        o->sub = func_0019A5C8() % 7;
        o->c1[3] = 0x10;
        o->state = 2;
    }
    if (o->t < 2) {
        if (o->c0[3] < 0xA0) {
            o->c0[3] += 0x50;
        }
    } else {
        if (o->h38 > 0x14) {
            if (o->c0[3] > 0xE) {
                o->c0[3] -= 0xD;
            } else {
                o->state = 0;
            }
        }
        if (g->state < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    func_001076F0(o->c0, 0x40, 0xF0, 0x40);
    func_001076F0(o->c1, 0x10, 0x80, 0x10);
    o->t++;
    o->h38 += 4;
    return 0;
}

/* OVL_WARM */

/* shape b192:01E01710, 170 insns: a yellow spark on the line between two joints (0x364C/0x364E): on start it gets turn
   0x4000 plus a random spin, a step 0..27 along the line, and a size 2 (4 from scene frame 50); for its first 20 ticks
   it sits at the second joint moved step/20 of the way to the first; alpha grows by 21 to 0x80 for 6 ticks, then
   fades by 5; a random flicker 3..14 every tick */

typedef struct {
    s16 x, y, z;
    s16 size;
    u8 pad8[8];
    s32 rot[2];
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 k;
    s16 t;
    s16 h34;
    s16 state;
    s16 flick;
} Spark_b192_01E01710;

typedef struct {
    u8 pad0[0x364C];
    s16 j0;
    s16 j1;
    u8 pad3650[0xA];
    s16 frame;
} Scene_b192_01E01710;

static s32 func_01E01710_b192(Scene_b192_01E01710 *g, Spark_b192_01E01710 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[2];
    f32 dx;
    f32 dy;
    f32 dz;

    func_001076F0(o->col, 0x50, 0x50, 0);
    if (o->state == 1) {
        o->rot[0] = 0x4000;
        o->rot[1] = func_0019A5C8() % 65535;
        o->h34 = 0;
        if (g->frame < 50) {
            o->size = 2;
        } else {
            o->size = 4;
        }
        o->k = func_0019A5C8() % 28;
        o->state = 2;
        o->col[3] = 0;
    }
    func_001F5620(func_001F53A0(), g->j0, &v[0]);
    func_001F5620(func_001F53A0(), g->j1, &v[1]);
    if (o->t < 21) {
        o->x = v[1].x;
        o->y = v[1].y;
        o->z = v[1].z;
        dx = v[0].x - v[1].x;
        dy = v[0].y - v[1].y;
        dz = v[0].z - v[1].z;
        dx /= 20.0f;
        dy /= 20.0f;
        dz /= 20.0f;
        o->x += dx * o->k;
        o->y += dy * o->k;
        o->z += dz * o->k;
    }
    if (o->t < 6) {
        if (o->col[3] < 0x80) {
            o->col[3] += 21;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->state = 0;
    }
    o->flick = func_0019A5C8() % 12 + 3;
    o->t++;
    return 0;
}

/* shape b192:01E019C0, 40 insns: b120:01E01890 family: a yellow glow held at the model point, alpha 0x50 */

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b192_01E019C0;

typedef struct {
    u8 pad[0x3610];
    s32 state;
    u8 padS[0x34];
    s16 val;
} Game_b192_01E019C0;

static s32 func_01E019C0_b192(Game_b192_01E019C0 *g, Glow_b192_01E019C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s32 buf[4];

    func_001076F0(o->col, 0x50, 0x50, 0);
    if (o->mode == 1) {
        o->f38 = 5;
        o->mode = 2;
    }
    func_001F5620(func_001F53A0(), g->val, buf);
    o->col[3] = 0x50;
    o->tick = 10;
    if (g->state == 0x32) {
        o->mode = 0;
    }
    return 0;
}

/* shape b192:01E01A60, 90 insns: a green drifting spark: frame 4 growing by 10..24, random turns, drift 15 by its side; alpha
   up by 42 to 0x80 for 3 frames, then down by 10 until it ends */

typedef struct {
    u8 pad0[6];
    s16 x;
    s16 dx;
    s16 grow;
    u8 padC[8];
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 side;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
} Obj_b192_01E01A60;

static s32 func_01E01A60_b192(void *arg0, Obj_b192_01E01A60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->c0, 0x10, 0x40, 0x10);
    if (o->state == 1) {
        o->h38 = 4;
        o->rot2 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
        if (o->side == 0) {
            o->dx = 0xF;
        } else {
            o->dx = -0xF;
        }
        o->grow = func_0019A5C8() % 15 + 0xA;
        o->state = 2;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x80) {
            o->c0[3] += 0x2A;
        }
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    o->x += o->dx;
    o->h38 += o->grow;
    o->t++;
    return 0;
}

/* shape b192:01E01BD0, 116 insns: a green drifting mote (b080:01E023D0 shape): frame 123, random turn and angle; alpha up by 32
   for 6 frames, then down by 10; sub-frame steps up to 7 every third frame; drifts 14 along its angle and bobs 4 by its turn */

typedef struct {
    u8 pad0[0x375C];
    u8 sin[1];
} Game_b192_01E01BD0;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 turn;
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b192_01E01BD0;

static s32 func_01E01BD0_b192(Game_b192_01E01BD0 *g, Obj_b192_01E01BD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    if (o->state == 1) {
        o->h38 = 0x7B;
        o->sub = 0;
        func_001076F0(o->c0, 0x20, 0x40, 0x20);
        o->turn = func_0019A5C8() % 360;
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
    }
    if (o->t < 6) {
        o->c0[3] += 0x20;
    } else if (o->c0[3] > 0xB) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t % 3 == 1) {
        if (o->sub < 7) {
            o->sub++;
        }
    }
    o->t++;
    o->h8 = func_001A22C0(o->h8 + 14.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 4.0f * func_00108030(g->sin, o->turn, 1));
    o->hC = func_001A22C0(o->hC + 14.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b192:01E01DA0, 85 insns: a green rising spark: frame 35, random sub-frame 0..3, angle, rise step 3..18, start height
   0..9 and full-alpha time 5..11; then fades by 10 until it ends; rises by its step each frame */

typedef struct {
    u8 pad0[6];
    s16 hold;
    s16 h8;
    u8 padA[4];
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
} Obj_b192_01E01DA0;

static s32 func_01E01DA0_b192(void *arg0, Obj_b192_01E01DA0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x23;
        o->sub = func_0019A5C8() % 4;
        func_001076F0(o->c0, 0x20, 0x80, 0x20);
        o->y = 0;
        o->ang = func_0019A5C8() % 360;
        o->step = func_0019A5C8() % 16 + 3;
        o->h8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 7 + 5;
        o->state = 2;
    }
    if (o->t < o->hold) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->t != 0) {
        o->y += o->step;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad0000[0x375C];
    u8 tab[1];
} Mgr_b192_01E01F00;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b192_01E01F00;

static s32 func_01E01F00_b192(Mgr_b192_01E01F00 *m, Obj_b192_01E01F00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->h36 == 1) {
        o->h38 = 130;
        o->h34 = 0;
        func_001076F0(o->col, 0x20, 0x40, 0x20);
        o->h30 = func_0019A5C8() % 360;
        o->h3A = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 10) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->h36 = 0;
    }
    if (o->h32 % 3 == 1) {
        if (o->h34 < 7) {
            o->h34++;
        }
    }
    o->h32++;
    o->x = o->x + 14.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 6.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 14.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

/* shape b192:01E020D0, 95 insns: on start 0x38 = 260, variant 0..6, second alpha 8, green colours (darker before game
   step 0x365A reaches 0x4A); alpha grows by 0x10 (below 0x20) for 2 ticks, then fades by 12 once 0x38 passes 0x14 and
   by 15 while the game counter 0x3610 is below 10; 0x38 grows by 4 */

typedef struct {
    u8 pad0[0x3610];
    s32 count;
    u8 pad3614[0x46];
    s16 step;
} Game_b192_01E020D0;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b192_01E020D0;

static s32 func_01E020D0_b192(Game_b192_01E020D0 *g, Fx_b192_01E020D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 260;
        o->f34 = func_0019A5C8() % 7;
        o->col2[3] = 8;
        if (g->step < 0x4A) {
            func_001076F0(o->col, 0x10, 0x60, 0x10);
            func_001076F0(o->col2, 8, 0x20, 8);
        } else {
            func_001076F0(o->col, 0x10, 0x80, 0x10);
            func_001076F0(o->col2, 8, 0x40, 8);
        }
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x20) {
            o->col[3] += 0x10;
        }
    } else {
        if (o->f38 > 0x14) {
            if (o->col[3] > 0xD) {
                o->col[3] -= 12;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    o->tick++;
    o->f38 += 4;
    return 0;
}

/* shape b192:01E02250, 74 insns: a dark spark (size 60, or 110 once the scene value reaches 74) at the scene angle and a random frame, growing 2 and turning 15 a tick: in by 64 up to 0x80 for 2 ticks, then out by 12 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 hE;
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[8];
    s32 w24;
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 used;
    s16 f38;
    s16 ang;
    u8 pad3C[4];
} Glow_b192_01E02250;

typedef struct {
    u8 pad[0x3650];
    s16 ang;
    u8 pad3652[8];
    s16 val;
} Game_b192_01E02250;

static s32 func_01E02250_b192(Game_b192_01E02250 *g, Glow_b192_01E02250 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->used == 1) {
        o->f38 = 60;
        if (g->val > 73) {
            o->f38 = 110;
        }
        o->ang = g->ang;
        o->kind = func_0019A5C8() % 7;
        o->col2[3] = 8;
        func_001076F0(o->col, 0x18, 0x18, 0x18);
        o->used = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 13) {
        o->col[3] -= 12;
    } else {
        o->used = 0;
    }
    o->tick++;
    o->f38 += 2;
    o->ang += 15;
    if (o->ang >= 360) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b270:01E04340, 47 insns, 1 copy: fade a level toward 0x40 or 0x80 by the scene timer */

typedef struct Ctx_b046_01E030F0 {
    u8 pad[0x3610];
    s32 timer;
} Ctx_b046_01E030F0;

typedef struct Obj_b046_01E030F0 {
    u8 pad0[0x30];
    s16 level;
    u8 pad32[4];
    s16 state;
} Obj_b046_01E030F0;

static s32 func_01E02380_b192(Ctx_b046_01E030F0 *ctx, Obj_b046_01E030F0 *o) {
    if (o->state == 1) {
        o->level = 0x80;
        o->state = 2;
    }
    if (ctx->timer > 0x1E) {
        if (o->level > 0x30) {
            o->level -= 10;
        } else {
            o->level = 0x30;
        }
    } else {
        if (o->level < 0x80) {
            o->level += 10;
        } else {
            o->level = 0x80;
        }
    }
    if (ctx->timer == 1) {
        func_001F6D00((u8)o->level);
    } else {
        func_001F6D00((u8)o->level);
    }
    return 0;
}

static s32 func_01E02440_b192(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03C00_b192;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03C08_b192;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b192:01E02490 (b192), 667 insns, 1 copy: b192 scene manager (b052:01E02A00's form): with a scene id (>= 0) it
   clears the scene, keeps the id, sets the 152-frame countdown, takes four joint handles, loads textures 0..2 and
   14..15, builds ten quads and bends nine of them on a sine, fills a 256-byte random table (-100..99); otherwise it
   runs the script, at frame 90 fills both nine-point trails from joints 2 and 3, shifts the trails, steps the 180
   slots (0x1E019C0 written out in place), draws every live slot, grows the scene scale after frame 20 and returns 1 /
   4 / 2 at frames 75 / 95 / 85, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 c0[4];
    u8 pad2C[6];
    s16 f32_;
    s16 h34;
    s16 used;
    s16 h38;
    u8 pad3A[6];
} Slot_b192_01E02490;

typedef struct {
    s32 texture;
    s32 tex;
    s32 c;
    s32 mode;
} Spr_b192_01E02490;

typedef struct {
    u8 pad0[0x80];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 crdD8[0x228];
    f32 f300;
    f32 f304;
    f32 f308;
    u8 pad30C[0x24];
    s32 tex[16];
    Vec4f q[10][4];
    u8 pad5F0[0x174];
    Slot_b192_01E02490 slot[180];
    u8 pad3464[0x5C];
    Vec4f trB[10];
    Vec4f trA[10];
    u8 pad3600[0x10];
    s32 count;
    u8 pad3614[8];
    s32 ot;
    u8 pad3620[0x28];
    s16 j[4];
    u8 pad3650[8];
    s16 id;
    s16 frame;
    s8 jit[0x100];
    u8 crd[0x174];
} Scene_b192_01E02490;

static s32 func_01E02490_b192(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00108CE0(void *, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001F7170(s32, s32, s32, s32, s32);
    extern void b192_01E00FB0();
    extern void b192_01E00CE0();
    extern void b192_01E03030();
    extern void b192_01E03310();
    extern void b192_01E03600();
    extern void b192_01E03920();
    extern void b192_01E00960();
    Scene_b192_01E02490 *g = (Scene_b192_01E02490 *)arg0;
    s32 m;
    Vec4f c;
    Spr_b192_01E02490 s;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    Vec4f pa;
    Vec4f pb;
    Vec4f pc;
    u8 buf[0x90] __attribute__((aligned(8)));
    s32 i;
    s32 j;

    m = 0;
    g->ot80 = func_00207500();
    g->ot = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x38D0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 0x98;
        g->f300 = 0.0f;
        g->f304 = 0.0f;
        g->f308 = 0.0f;
        g->j[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x44, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0xE, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->hB8 = 0xB4;
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (j = 0; j < 10; j++) {
            func_00108CE0(g->q[j], 5.0f, 50.0f);
        }
        for (i = 0; i < 9; i++) {
            f32 t;

            g->q[i][0].y = 15.0f * func_00108030(g->crd, i * 20, 0);
            g->q[i][1].y = 15.0f * func_00108030(g->crd, i * 20 + 20, 0);
            g->q[i][2].y = 35.0f * func_00108030(g->crd, i * 20, 0);
            g->q[i][3].y = 35.0f * func_00108030(g->crd, i * 20 + 20, 0);
            t = i * 10 - 45;
            g->q[i][0].x += t;
            g->q[i][1].x += t;
            g->q[i][2].x += t;
            g->q[i][3].x += t;
            g->q[i][0].y -= 10.0f;
            g->q[i][1].y -= 10.0f;
            g->q[i][2].y += 15.0f;
            g->q[i][3].y += 15.0f;
            g->q[i][0].z = 0.0f;
            g->q[i][1].z = 0.0f;
            g->q[i][2].z = 0.0f;
            g->q[i][3].z = 0.0f;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 200 - 100;
        }
        return 0;
    }
    b192_01E00FB0(g, 0);
    if (g->frame == 0x5A) {
        Vec4f *p = g->trA;

        func_001F5620(func_001F53A0(), g->j[2], &pa);
        for (i = 0; i < 9; i++, p++) {
            p->x = pa.x;
            p->y = pa.y;
            p->z = pa.z;
        }
    }
    if (g->frame == 0x5A) {
        Vec4f *p = g->trB;

        func_001F5620(func_001F53A0(), g->j[3], &pb);
        for (i = 0; i < 9; i++, p++) {
            p->x = pb.x;
            p->y = pb.y;
            p->z = pb.z;
        }
    }
    func_01E00260_b192((Vec_b004_01E00B40 *)&g->trA[9], 10, g->j[2]);
    func_01E00260_b192((Vec_b004_01E00B40 *)&g->trB[9], 10, g->j[3]);
    for (i = 0; i < 180; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == (void *)func_01E013B0_b192) {
                func_01E013B0_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E015D0_b192) {
                func_01E015D0_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E01710_b192) {
                func_01E01710_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E019C0_b192) {
                func_001076F0(g->slot[i].c0, 0x50, 0x50, 0);
                if (g->slot[i].used == 1) {
                    g->slot[i].h38 = 5;
                    g->slot[i].used = 2;
                }
                func_001F5620(func_001F53A0(), g->j[0], &pc);
                g->slot[i].c0[3] = 0x50;
                g->slot[i].f32_ = 10;
                if (g->count == 50) {
                    g->slot[i].used = 0;
                }
            }
            if (g->slot[i].fn == (void *)func_01E01A60_b192) {
                func_01E01A60_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E01BD0_b192) {
                func_01E01BD0_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E01DA0_b192) {
                func_01E01DA0_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E01F00_b192) {
                func_01E01F00_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E020D0_b192) {
                func_01E020D0_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E02250_b192) {
                func_01E02250_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E02380_b192) {
                func_01E02380_b192((void *)g, (void *)&g->slot[i]);
            }
            if (g->slot[i].fn == (void *)func_01E02440_b192) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E03C00_b192;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E03C08_b192;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &c);
    for (i = 0; i < 180; i++) {
        if (g->slot[i].used != 0) {
            m++;
            if (g->slot[i].fn == (void *)func_01E013B0_b192) {
                s.texture = g->tex[2];
                s.c = 0;
                s.tex = 0x14;
                s.mode = 0;
                func_01E00080_b192(g->ot, (Obj_b058_01E00080 *)&g->slot[i], (Spr_b058_01E00080 *)&s);
            }
            if (g->slot[i].fn == (void *)func_01E015D0_b192) {
                b192_01E00CE0(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == (void *)func_01E01710_b192) {
                g->tex88 = g->tex[15];
                b192_01E03030(g, &g->slot[i], buf, 0);
                b192_01E03030(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == (void *)func_01E019C0_b192) {
                b192_01E03310(g, &g->slot[i], buf, 0);
                b192_01E03310(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == (void *)func_01E01A60_b192) {
                b192_01E03600(g, &g->slot[i], buf, 0);
                b192_01E03600(g, &g->slot[i], buf, 1);
            }
            if (g->slot[i].fn == (void *)func_01E01BD0_b192) {
                g->tex88 = g->tex[2];
                func_00106080(rm, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                func_01E00780_b192((u8 *)g, (Obj_b045_01E005A0 *)&g->slot[i], (Pk_b045_01E005A0 *)buf, 0);
                func_01E00780_b192((u8 *)g, (Obj_b045_01E005A0 *)&g->slot[i], (Pk_b045_01E005A0 *)buf, (s8 *)1);
            }
            if (g->slot[i].fn == (void *)func_01E01DA0_b192) {
                g->tex88 = g->tex[15];
                func_00106080(rm2, 0x9B, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hB8 = 0xE;
                b192_01E00960(g, &g->slot[i], buf, g->jit);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == (void *)func_01E01F00_b192) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->slot[i].h34, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                func_01E00780_b192((u8 *)g, (Obj_b045_01E005A0 *)&g->slot[i], (Pk_b045_01E005A0 *)buf, 0);
                func_01E00780_b192((u8 *)g, (Obj_b045_01E005A0 *)&g->slot[i], (Pk_b045_01E005A0 *)buf, (s8 *)1);
            }
            if (g->slot[i].fn == (void *)func_01E020D0_b192) {
                b192_01E00CE0(g, &g->slot[i], buf, 0);
            }
            if (g->slot[i].fn == (void *)func_01E02250_b192) {
                b192_01E03920(g, &g->slot[i], buf, 0);
                b192_01E03920(g, &g->slot[i], buf, 1);
            }
        }
    }
    if (g->frame > 20) {
        if (g->f300 < 0.5) {
            g->f300 += 0.01f;
        }
        g->f304 = 0.1f;
        if (g->f308 < 0.5) {
            g->f308 += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x4B) {
        return 1;
    }
    if (g->frame == 0x5F) {
        return 4;
    }
    if (g->frame == 0x55) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b192:01E02F00, 75 insns: take a free slot from the given pool (g->0xB8 slots of 0x40 bytes), clear it, colour
   both colours from the object colour 0x8C, attach it to the object, 0x30 from 0xB2, store the two arguments;
   returns 1 if a slot was found */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    u8 col[4];
    u8 col2[4];
    s16 f30;
    u8 pad32[4];
    s16 used;
    u8 pad38[8];
} Slot_b192_01E02F00;

typedef struct {
    u8 pad0[0x8C];
    u8 rgba[4];
    u8 pad90[0x22];
    s16 fB2;
    u8 padB4[4];
    s16 count;
} Obj_b192_01E02F00;

static s32 func_01E02F00_b192(Obj_b192_01E02F00 *g, s32 a1, s32 a2, Slot_b192_01E02F00 *pool) {
    extern void func_00195108();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b192_01E02F00 *s = NULL;
    s16 i;

    for (i = 0; i < g->count; i++) {
        if (pool[i].used == 0) {
            func_00195108(&pool[i], 0x40);
            pool[i].used = 1;
            s = &pool[i];
            i = g->count;
        }
    }
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_001076F0(s->col2, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col2[3] = g->rgba[3];
        func_00106AB0(s, g, 0);
        s->f30 = g->fB2;
        s->a2 = a2;
        s->a1 = a1;
        return 1;
    }
    return 0;
}

/* shape b192:01E03030, 182 insns: b195:01E02A40's fan of 9 thin triangles (span 18) with the rim raised to the object's
   h6, scaled 1 x 1.5 x 1 at the object's position; mode 0 sets up the packet with texture 0x97. Texture corners by the module
   helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b192_01E03030;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b192_01E03030;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b192_01E03030 c;
    struct {
        u64 tc;
        Xyz_b192_01E03030 p;
    } v[4];
} Pkt_b192_01E03030;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[0x4C];
    u8 trig[1];
} Ctx_b192_01E03030;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b192_01E03030;

static void func_01E03030_b192(Ctx_b192_01E03030 *c, Fan_b192_01E03030 *o, Pkt_b192_01E03030 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b192_01E03030 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x10];
    f32 dep[6];
    s32 k;
    s32 t;
    s16 a;

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
        func_01E00330_b192((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
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
    quad[2].y = o->h6;
    quad[3].y = o->h6;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        t = a + (o->ang + 18);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        if (func_00205630(quad, 0x70000000, m, p, dep) != 0) {
            func_002075F0(p, c->ot, (u32)dep[0]);
        }
        a += 0x28;
    }
}

/* shape b192:01E03310, 188 insns: draws a ribbon between two 10-point trails (g+0x34C0 and g+0x3560) for the effect's
   first h32 points: one quad per segment, the second row pulled in by half the first segment's height and depth
   (each widened by a fiftieth / twentieth), its colour fading by alpha / h32 along the ribbon; packets go far after a
   packet tweak into the current order table */

typedef struct {
    u8 pad0[0x34C0];
    Vec4f a[10];
    Vec4f b[10];
} Game_b192_01E03310;

typedef struct {
    u8 c[4];
} Rgba_b192_01E03310;

typedef struct {
    u64 tag;
    u8 pk[0x90];
} Buf_b192_01E03310;

typedef struct {
    u8 pad0[0x28];
    Rgba_b192_01E03310 col;
    u8 pad2C[6];
    s16 n;
} Fx_b192_01E03310;

static void func_01E03310_b192(Game_b192_01E03310 *g, Fx_b192_01E03310 *o) {
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_00109380(void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec4f q[4];
    Vec4f d;
    Vec4f e;
    Buf_b192_01E03310 buf;
    Rgba_b192_01E03310 col;
    s32 i;
    s32 k;
    u8 *p;
    s32 ot;
    s16 j;
    s16 n;
    f32 fk;
    f32 wy;
    f32 wz;

    ot = (s32)func_00207500();
    p = buf.pk;
    n = o->n;
    fk = 0.0f;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = o->col;
    d = g->a[0];
    e = g->b[0];
    d.y -= e.y;
    d.z -= e.z;
    d.y += d.y / 50.0f;
    d.z += d.z / 20.0f;
    wy = d.y;
    wz = d.z;
    for (i = 0; i < n - 1; i++) {
        j = 0;
        func_00107990(p, &col, 1);
        col.c[3] -= o->col.c[3] / n;
        func_00107990(p, &col, 2);
        for (k = 0; k < 1; k++) {
            q[0].x = g->a[i].x;
            q[0].y = g->a[i].y;
            q[0].z = g->a[i].z;
            q[1].x = g->b[i].x;
            q[1].y = g->b[i].y;
            q[1].z = g->b[i].z;
            q[2].x = g->a[i + 1].x;
            q[2].y = g->a[i + 1].y;
            q[2].z = g->a[i + 1].z;
            q[3].x = g->b[i + 1].x;
            q[3].y = g->b[i + 1].y;
            q[3].z = g->b[i + 1].z;
            q[1].y -= wy / 2.0f;
            q[3].y -= wy / 2.0f;
            q[1].z -= wz / 2.0f;
            q[3].z -= wz / 2.0f;
            if (func_00205630(q, 0x70000000, 0, p, depth) != 0) {
                func_00109380(p, 1);
                func_002075F0(p, ot, 0);
            }
            j += 30;
        }
        fk += 1.0f;
    }
}

/* OVL_WARM */

/* shape b192:01E03600, 200 insns (B192PAINT_RAIN5): two-pass quad pair: the setup pass sets the material (frame 0x97
   with its height halved, one colour, scene texture 0x36C); the draw pass places it at position + speed/10 turned by
   the effect's rotation, scale (0.2, 0.8, 1), and draws two 3-wide quads of the effect's length, flat in y, shifted
   +-h6 along x, into the scene order table 0x361C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b192_01E03600;

typedef struct {
    Rgbaq_b192_01E03600 c;
    u64 st;
    u64 xyz;
} Vtx_b192_01E03600;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b192_01E03600 v[4];
} Pkt_b192_01E03600;

typedef struct {
    u8 pad0[0x36C];
    s32 tex;
    u8 pad370[0x361C - 0x370];
    s32 ot;
} Game_b192_01E03600;

typedef struct {
    s16 x, y, z;
    s16 h6;
    s16 dx, dy, dz;
    u8 padE[2];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[0xC];
    s16 len;
} Fx_b192_01E03600;

static void func_01E03600_b192(Game_b192_01E03600 *g, Fx_b192_01E03600 *o, Pkt_b192_01E03600 *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b192_01E03600 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    s16 rm[8];
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    s16 i;
    f32 ax, ay, az;

    func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x97, 0, rm);
        rm[3] >>= 1;
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col);
        p->v[3].c = func_00107740(o->col);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        sc.x = 0.2f;
        sc.y = 0.8f;
        sc.z = 1.0f;
        func_00205C40((s32)rot);
        rot[0] += o->rot[0];
        rot[1] += o->rot[1];
        rot[2] += o->rot[2];
        ax = o->dx;
        ay = o->dy;
        az = o->dz;
        ax /= 10.0f;
        ay /= 10.0f;
        az /= 10.0f;
        pos.x = o->x + ax;
        pos.y = o->y + ay;
        pos.z = o->z + az;
        func_00108EF0(m, &sc, rot, &pos);
        for (i = 0; i < 2; i++) {
            func_00108CE0(quad, 3.0f, o->len);
            quad[2].y = 0.0f;
            quad[3].y = 0.0f;
            if (i == 0) {
                quad[0].x += o->h6;
                quad[1].x += o->h6;
            } else {
                quad[0].x -= o->h6;
                quad[1].x -= o->h6;
            }
            if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
                func_002075F0(p, g->ot, (u32)depth[0]);
            }
        }
    }
}

/* shape b192:01E03920 (B192PAINT_RAIN7), 177 insns, 1 copy: b361:01E022E0 family sprite draw: blended (0x48) 9-qword packet with the object colour, alphas cleared, rect via b192:01E00330 from texture 0x14 at its angle 0x34 and the scene texture (g+0x330); scale 0.1 at its position plus a tenth of 0x8..0xC; four quads of size x size pushed 120 out at angles 0x3A + 0/90/180/270 (g+0x375C), depth-tested into g+0x361C */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b192_01E03920;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Rgbaq_b192_01E03920 c;
    u8 pad18[0xF];
    u8 a27;
    u8 pad28[0xF];
    u8 a37;
    u8 pad38[0xF];
    u8 a47;
    u8 pad48[0xF];
    u8 a57;
} Pk_b192_01E03920;

typedef struct {
    u8 pad0[0x330];
    s32 tex;
    u8 pad334[0x361C - 0x334];
    s32 ot;
    u8 pad3620[0x375C - 0x3620];
    u8 trig[1];
} Game_b192_01E03920;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[0x1A];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
    s16 h3A;
} Fx_b192_01E03920;

static void func_01E03920_b192(Game_b192_01E03920 *g, Fx_b192_01E03920 *o, Pk_b192_01E03920 *p) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00107070(void *, s32, f32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f sc;
    f32 rm[4];
    f32 depth[4];
    f32 m[16];
    s32 rot[4];
    f32 x;
    f32 y;
    f32 ax, ay, az;
    s16 i;
    s16 ang = 0;
    Rgbaq_b192_01E03920 uv __attribute__((aligned(8)));

    func_00106080(rm, 0x14, o->h34, rm);
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    *(s32 *)&p->c.q = 0;
    p->a27 = 0;
    p->a37 = 0;
    p->a47 = 0;
    p->a57 = 0;
    func_00107740(&uv, o->col);
    p->c = uv;
    func_01E00330_b192((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)rm, 0);
    func_00208700(p, g->tex, 1);
    sc.x = 0.1f;
    sc.y = 0.1f;
    sc.z = 0.1f;
    func_00205C40((s32)rot);
    ax = o->dx;
    ay = o->dy;
    az = o->dz;
    ax /= 10.0f;
    ay /= 10.0f;
    az /= 10.0f;
    pos.x = o->x + ax;
    pos.y = o->y + ay;
    pos.z = o->z + az;
    func_00108EF0(m, &sc, rot, &pos);
    for (i = 0; i < 4; i++) {
        func_00108CE0(quad, o->size, o->size);
        x = 120.0f * func_00108030(g->trig, (s16)(ang + o->h3A), 0);
        y = 120.0f * func_00108030(g->trig, (s16)(ang + o->h3A), 1);
        func_00107070(quad, 0, x);
        func_00107070(quad, 1, y);
        ang += 90;
        if (func_00205630(quad, 0x70000000, m, p, depth) != 0) {
            func_002075F0((s32)p, g->ot, (u32)depth[0]);
        }
    }
}

