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

static void func_01E00080_b618(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

/* OVL_WARM */
/* z offset: in-place divide (fq = t; fq /= 20.0f;) puts the quotient in the dividend's register (chatA fix pass 16 Oct). */

typedef struct {
    f32 x, y, z, w;
} Vec_b038_01E00920;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b038_01E00920;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b038_01E00920;

typedef struct {
    u64 st;
    Xyz_b038_01E00920 p;
} Vtx_b038_01E00920;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b038_01E00920 c;
    Vtx_b038_01E00920 v[4];
    u8 tail[0x30];
} Pkt_b038_01E00920;

typedef struct {
    s32 rot[4];
    s32 v[4];
} Rot_b038_01E00920;

typedef struct {
    s8 x[100];
    s8 y[80];
    s8 z[1];
} Tbl_b038_01E00920;

typedef struct {
    u8 pad00[8];
    s16 base;
    u8 pad0A[0x3E];
    f32 size;
    u8 pad4C[4];
    s16 scale;
    u8 pad52[8];
    s16 spin;
    s16 tilt;
    u8 pad5E[2];
    u8 col[1];
} Anim_b038_01E00920;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[6];
    s16 hC0;
    u8 padC2[0x16];
    u8 bD8[1];
} Obj_b038_01E00920;

extern void b618_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00920_b618(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
    f32 fq;
    extern void func_00207500(void);
    extern void func_00107740(void *, void *);
    extern void func_00208700(void *, s32, s32);
    extern void func_00205C40(void *);
    extern void func_00108EF0(void *, void *, s32, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00109100(void *, void *, s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b038_01E00920 quad[4];
    Vec_b038_01E00920 d;
    Vec_b038_01E00920 pos;
    Vec_b038_01E00920 scale;
    f32 depth __attribute__((aligned(16)));
    f32 m[16];
    Rot_b038_01E00920 r;
    struct {
        u64 pre;
        Pkt_b038_01E00920 pk;
    } buf;
    Col_b038_01E00920 col;
    s16 i;
    Pkt_b038_01E00920 *p;
    s16 blend;
    s32 kind;
    s32 h;
    s8 *t;

    func_00207500();
    p = &buf.pk;
    p->count = 0x24;
    p->tag = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad = 0;
    p->count |= 0x800;
    blend = mode >> 4;
    if (blend == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((u64)blend << 2) | ((u64)0x80 << 32) | 0x40);
    }
    func_00107740(&col, an->col);
    p->c = col;
    func_00208700(p, o->texture, 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40(&r);
    r.rot[1] /= 180;
    r.rot[1] = -r.rot[1];
    r.rot[0] /= 180;
    r.rot[0] = -r.rot[0];
    r.rot[2] = an->tilt;
    r.v[1] = an->spin;
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    func_00108EF0(m, &scale, 0, &pos);
    b618_01E00080(p, o->b94, o->hC0);
    kind = mode & 0xF;
    for (i = 0; i < o->count; i++) {
        func_00108CE0(quad, an->size, an->size);
        func_00109100(quad, &r, 2, o->bD8);
        func_00109100(quad, &r, 1, o->bD8);
        func_00109100(quad, &r, 0, o->bD8);
        t = &tbl->x[i];
        h = i >> 1;
        d.x = t[an->base] / 20.0f * (an->scale + h);
        d.y = t[an->base + 100] / 20.0f * (an->scale + h);
        d.z = 0.0f;
        func_00108950(&d, r.v, 0, o->bD8);
        quad[0].x += d.x;
        quad[1].x += d.x;
        quad[2].x += d.x;
        quad[3].x += d.x;
        quad[0].y += d.y;
        quad[1].y += d.y;
        quad[2].y += d.y;
        quad[3].y += d.y;
        fq = t[an->base + 180];
        fq /= 20.0f;
        d.z = fq * (an->scale + h);
        quad[0].z += d.z;
        quad[1].z += d.z;
        quad[2].z += d.z;
        quad[3].z += d.z;
        if (kind == 0) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, (u32)depth);
            }
        } else if (kind == 1) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                p->v[0].p.z = p->v[1].p.z = p->v[2].p.z = p->v[3].p.z = 0xFFFFFF;
                func_002075F0(p, o->target, 0);
            }
        } else if (kind == 2) {
            if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
                func_002075F0(p, o->target, -1);
            }
        }
    }
}

/* shape b618:01E00E90, 223 insns: a pink (0xFF/0x80/0x80) spark, size 15 growing 1.5, frame (rand>>4)%8, random
   0x5A/0x5C, flip 0 or 2, old 0x50 kept in 0xC, 0x52 100..449, speed 10..29, 0x8 0..34, 0x6 3..7, drift -1/3..+1/3
   per axis from tick 11 to 69; z closes an 80th of the gap from the camera to the tracked joint (0xB228) each
   tick; alpha up to 0xC0 for 100 ticks, then down by 11; scene time past 420 jumps to the fade */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 pos[3];
    u8 pad1C[0x14];
    f32 vel[3];
    f32 dz;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 tick;
    s16 frame;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b618_01E00E90;

typedef struct {
    u8 pad0[0xB228];
    s16 joint;
    u8 padB22A[0x34];
    s16 timer;
} Scn_b618_01E00E90;

static s32 func_01E00E90_b618(Scn_b618_01E00E90 *g, Fx_b618_01E00E90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 v[12];

    if (o->mode == 1) {
        o->f48 = 15.0f;
        o->frame = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0x80, 0x80);
        o->f5A = func_0019A5C8() % 360;
        o->f5C = func_0019A5C8() % 360;
        if (func_0019A5C8() % 2 != 0) {
            o->hA = 2;
        } else {
            o->hA = 0;
        }
        o->hC = o->h50;
        o->h50 = 0;
        o->h52 = func_0019A5C8() % 350 + 100;
        o->hE = func_0019A5C8() % 20 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 5 + 3;
        o->vel[0] = func_0019A5C8() % 40 - 20;
        o->vel[1] = func_0019A5C8() % 40 - 20;
        o->vel[2] = func_0019A5C8() % 40 - 20;
        o->vel[0] /= 60.0f;
        o->vel[1] /= 60.0f;
        o->vel[2] /= 60.0f;
        func_001F5F90(func_001F5380(), v);
        func_001F5620(func_001F53A0(), g->joint, &v[4]);
        o->dz = (v[2] - v[6]) / 80.0f;
        o->mode = 2;
    }
    if (o->tick < 100) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 12) {
        o->col[3] -= 11;
    } else {
        o->mode = 0;
    }
    if (o->tick > 10 && o->tick < 70) {
        o->pos[0] += o->vel[0];
        o->pos[1] += o->vel[1];
        o->pos[2] += o->vel[2];
    }
    func_001F5F90(func_001F5380(), &v[8]);
    if (o->tick != 0) {
        o->pos[2] += o->dz;
        o->f48 += 1.5f;
    }
    if (g->timer > 420) {
        o->tick = 100;
    }
    o->tick++;
    return 0;
}

/* shape b618:01E01210 (b618), 370 insns, 1 copy: the module scene manager (b278:01E01230 form): with a scene id it
   clears the scene, keeps the two camera words, sets the 450-frame countdown, reads four model ids, textures 5:0..1,
   the camera turn, scale 0.1 and the jitter tables; otherwise it counts frames, from 170 to 352 spawns three
   b618:01E00E90 sparks at joint A a frame, runs every effect handler, draws the sparks, counts down and returns the
   next step by frame (230, 435, 241..424) or 8 when the countdown runs out */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b618_01E01210;

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
    s32 rm[4];
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 crdD8[0x178];
    Vec4f spawn;
    u8 pad260[0x40];
    Fx_b618_01E01210 fx[400];
    u8 padB1A0[0x30];
    s32 tex[2];
    u8 padB1D8[0x18];
    s32 count;
    u8 padB1F4[8];
    s32 ot;
    u8 padB200[4];
    s32 cam1;
    s32 cam2;
    u8 padB20C[0x1C];
    s16 jA;
    s16 jB;
    s16 jC;
    u8 padB22E[0xA];
    s16 cam;
    u8 padB23A[0x20];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x170];
} Scene_b618_01E01210;

static s32 func_01E01210_b618(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F9AD0(s32);
    extern s32 func_001F9D30(s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_01E00920_b618();
    extern s32 func_01E00E90_b618();
    extern s32 func_01E017E0_b618();
    Scene_b618_01E01210 *g = (Scene_b618_01E01210 *)arg0;
    s32 n;
    s32 rm[4];
    s32 ang[4];
    s16 i;
    s16 m;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    g->cam1 = func_001F9AD0(0);
    g->cam2 = func_001F9D30(0);
    if (id >= 0) {
        func_00195108(g, 0xB5D0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 450;
        g->jA = func_001F5560(func_001F53A0(), 6, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1C, 0);
        g->jC = func_001F5560(func_001F53A0(), 0xD, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (; n < 2; n++) {
            g->tex[n] = func_00202BF0(5, n);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->jit[i] = func_0019A5C8() % 4;
        }
        for (i = 180; i < 0x100; i++) {
            g->jit[i] = func_0019A5C8() % 16 - 8;
        }
        for (i = 0; i < 0x100; i++) {
            g->jit2[i] = func_0019A5C8() % 40 - 20;
        }
        return 0;
    }
    g->frame++;
    if (g->frame >= 170 && g->frame < 353) {
        if (g->frame < 100) {
            m = 3;
        } else {
            m = 3;
        }
        for (i = 0; i < m; i++) {
            func_001F5620(func_001F53A0(), g->jA, &g->spawn);
            func_01E017E0_b618(g, func_01E00E90_b618, 0);
        }
    }
    for (i = 0; i < 400; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn != NULL) {
                g->fx[i].fn(g, &g->fx[i]);
            }
        }
    }
    for (i = 0; i < 400; i++) {
        if (g->fx[i].used != 0) {
            n = (s16)(n + 1);
            if (g->fx[i].fn == func_01E00E90_b618) {
                func_00106080(rm, 0x14, g->fx[i].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hC0 = 5;
                g->tex88 = g->tex[0];
                g->hB8 = 1;
                g->px = g->fx[i].pos.x;
                g->py = g->fx[i].pos.y;
                g->pz = g->fx[i].pos.z;
                g->hBE = 0;
                func_01E00920_b618(g, &g->fx[i], 0x10, g->jit);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 230) {
        return 1;
    }
    if (g->frame == 435) {
        return 3;
    }
    if (g->frame > 240 && g->frame < 425) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b038:01E01E10, 98 insns, 8 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b038_01E01E10 {
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
} Slot_b038_01E01E10;

typedef struct Obj_b038_01E01E10 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b038_01E01E10 slots[0x190];
    u8 padB[0xb1f4 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb256 - 0xb1f4 - 4];
    s16 fB2B0;
} Obj_b038_01E01E10;

static s32 func_01E017E0_b618(Obj_b038_01E01E10 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b038_01E01E10 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
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
