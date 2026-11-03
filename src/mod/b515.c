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

static void func_01E00080_b515(Pk_b003_01E00080 *p, Rect_b003_01E00080 *r, s32 mode) {
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

extern void b515_01E00080(Pkt_b038_01E00920 *, void *, s32);

static void func_01E00920_b515(Obj_b038_01E00920 *o, Anim_b038_01E00920 *an, s32 mode, Tbl_b038_01E00920 *tbl) {
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
    b515_01E00080(p, o->b94, o->hC0);
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

/* shape b515:01E00E90, 165 insns: the module's spawn step: ticks the timer (0xDE1E); from frame 120 to 380 it spawns
   0x1E01130 at three (odd frames) or four joints, the first list on odd frames and the second on even ones; from
   frame 28 to 340 the same with 0x1E013C0 */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0xDDE8 - 0x260];
    s16 ja[3];
    s16 jb[4];
    u8 padDDF6[0x28];
    s16 t;
} Scene_b515_01E00E90;

static void func_01E00E90_b515(Scene_b515_01E00E90 *s) {
    extern void b515_01E01130(void);
    extern void b515_01E013C0(void);
    extern s32 b515_01E01BD0(Scene_b515_01E00E90 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    s16 i;
    s16 n;

    s->t++;
    if (s->t >= 120 && s->t < 381) {
        if (s->t % 2 == 1) {
            n = 3;
        } else {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            if (s->t % 2 == 1) {
                func_001F5620(func_001F53A0(), s->ja[i], &s->pos);
            } else {
                func_001F5620(func_001F53A0(), s->jb[i], &s->pos);
            }
            b515_01E01BD0(s, b515_01E01130, 0);
        }
    }
    if (s->t >= 28 && s->t < 341) {
        if (s->t % 2 == 1) {
            n = 3;
        } else {
            n = 4;
        }
        for (i = 0; i < n; i++) {
            if (s->t % 2 == 1) {
                func_001F5620(func_001F53A0(), s->ja[i], &s->pos);
            } else {
                func_001F5620(func_001F53A0(), s->jb[i], &s->pos);
            }
            b515_01E01BD0(s, b515_01E013C0, 0);
        }
    }
}

/* shape b515:01E01130, 164 insns: yellow (0xFF, 0xFF, 0x80) ember (size 35 growing 4.3, frame 0..7, angle 0..359) drifting (-20..19)/50 x and /60 y/z, sinking 0.2, and closing a fortieth of the camera-to-point z gap each tick; alpha up by 0xC0 for 47 ticks, then down by 14 */

typedef struct {
    u8 pad0[0xDDE8];
    s16 id;
} Ctx_b515_01E01130;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x14];
    f32 vx, vy, vz;
    f32 dz;
    u8 pad40[8];
    f32 f48;
    u8 pad4C[4];
    s16 f50;
    s16 f52;
    s16 tick;
    s16 f56;
    s16 mode;
    s16 f5A;
    s16 f5C;
    u8 pad5E[2];
    u8 col[4];
} Fx_b515_01E01130;

static s32 func_01E01130_b515(Ctx_b515_01E01130 *g, Fx_b515_01E01130 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F5F90(s32, f32 *);
    f32 c[4];
    f32 t[4];

    if (o->mode == 1) {
        o->f48 = 35.0f;
        o->f56 = (func_0019A5C8() >> 4) % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->f5A = 0;
        o->f5C = func_0019A5C8() % 360;
        o->f50 = 0;
        o->f52 = 0;
        o->vx = func_0019A5C8() % 40 - 20;
        o->vy = func_0019A5C8() % 40 - 20;
        o->vz = func_0019A5C8() % 40 - 20;
        o->vx /= 50.0f;
        o->vy /= 60.0f;
        o->vz /= 60.0f;
        func_001F5F90(func_001F5380(), c);
        func_001F5620(func_001F53A0(), g->id, t);
        o->dz = (c[2] - t[2]) / 40.0f;
        o->mode = 2;
    }
    if (o->tick < 47) {
        if (o->col[3] < 0xC0) {
            o->col[3] += 0xC0;
        }
    } else if (o->col[3] > 15) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->x += o->vx;
        o->y += o->vy;
        o->y -= 0.2f;
        o->z += o->vz;
    }
    if (o->tick != 0) {
        o->z += o->dz;
        o->f48 += 4.3f;
    }
    o->tick++;
    return 0;
}

/* shape b515:01E013C0, 107 insns: b593:01E020C0 family: a yellow spark (size 40 growing 3, random frame 0..7) spinning a random 2..9 a tick from 10..59 (old angle moved to +0xC), random 0..7 at +0xA, size 0..34, held 2..5 ticks at 0x80, then out by 8 and ends */

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    u8 pad24[0xC];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    u8 pad4C[4];
    s16 h50;
    s16 h52;
    s16 t;
    s16 kind;
    s16 mode;
    s16 h5A;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Obj_b515_01E013C0;

static s32 func_01E013C0_b515(s32 arg0, Obj_b515_01E013C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f48 = 40.0f;
        o->kind = func_0019A5C8() % 8;
        func_001076F0(o->col, 0xFF, 0xFF, 0x80);
        o->h5A = func_0019A5C8() % 360;
        o->hA = func_0019A5C8() % 8;
        o->hC = o->h50;
        o->h50 = func_0019A5C8() % 50 + 10;
        o->hE = func_0019A5C8() % 8 + 2;
        o->h8 = func_0019A5C8() % 35;
        o->h6 = func_0019A5C8() % 4 + 2;
        o->mode = 2;
    }
    if (o->t < o->h6) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 9) {
        o->col[3] -= 8;
    } else {
        o->mode = 0;
    }
    if (o->t != 0) {
        o->h50 += o->hE;
    }
    o->f48 += 3.0f;
    o->t++;
    return 0;
}

/* shape b515:01E01570 (b515), 407 insns, 1 copy: b515 scene manager, the code of b595:01E017E0 (b069:01E01210 family)
   with seven page models, a 449-frame countdown, a zeroed 100..179 band in the second jitter table, the second sprite
   kind drawn in mode 6 with that table, and returns 1 / 4 / 3 / 6 at frames 190 / 445 / 440 / 201..429, 8 once the
   countdown runs out */

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[0x28];
    void (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Node_b515_01E01570;

typedef struct {
    u8 pad0[0x10];
    f32 sc[3];
    u8 pad1C[4];
    f32 px, py, pz;
    u8 pad2C[0x54];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    s16 hC0;
    u8 padC2[0x16];
    u8 camD8[0x1C8];
    Node_b515_01E01570 node[500];
    u8 padDD60[0xDD90 - 0xDD60];
    s32 tex5[2];
    u8 padDD98[0x18];
    s32 count;
    u8 padDDB4[8];
    s32 ot;
    u8 padDDC0[0x28];
    s16 model[7];
    u8 padDDF6[2];
    s16 model2;
    u8 padDDFA[0x20];
    s16 ang;
    s16 id;
    s16 timer;
    s8 rnd[256];
    s8 rnd2[256];
} Scene_b515_01E01570;

static s32 func_01E01570_b515(s32 arg0, s32 id) {
    Scene_b515_01E01570 *g = (Scene_b515_01E01570 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00920_b515();
    extern void func_01E00E90_b515();
    extern void func_01E01130_b515();
    extern void func_01E013C0_b515();
    s16 n;
    Vec4f r1;
    Vec4f r2;
    s32 iv[4];
    s32 i;
    s16 k;

    n = 0;
    g->ot = (s32)func_00207500();
    g->ot2 = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE190);
        func_00107C10((u8 *)g + 0xE020);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 449;
        g->model[0] = func_001F5560(func_001F53A0(), 0x32, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x35, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x38, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x41, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x4A, 0);
        g->model[5] = func_001F5560(func_001F53A0(), 0x50, 0);
        g->model[6] = func_001F5560(func_001F53A0(), 0x5C, 0);
        g->model2 = func_001F5560(func_001F5380(), 1, 1);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), iv);
        g->ang = iv[1] / 180.0f;
        g->sc[0] = 0.1f;
        g->sc[1] = 0.1f;
        g->sc[2] = 0.1f;
        for (k = 0; k < 256; k++) {
            g->rnd[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->rnd[k] = func_0019A5C8() % 4;
        }
        for (k = 180; k < 256; k++) {
            g->rnd[k] = func_0019A5C8() % 16 - 8;
        }
        for (k = 0; k < 256; k++) {
            g->rnd2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 100; k < 180; k++) {
            g->rnd2[k] = 0;
        }
        return 0;
    }
    func_01E00E90_b515(g, 0);
    for (k = 0; k < 500; k++) {
        if (g->node[k].used != 0) {
            if (g->node[k].fn != 0) {
                g->node[k].fn(g, &g->node[k]);
            }
        }
    }
    for (k = 0; k < 500; k++) {
        if (g->node[k].used != 0) {
            n++;
            if (g->node[k].fn == func_01E01130_b515) {
                func_00106080(&r1, 0x14, g->node[k].h56, 0);
                g->rect = r1;
                g->hC0 = 5;
                g->tex88 = g->tex5[0];
                g->hB8 = 1;
                g->px = g->node[k].x;
                g->py = g->node[k].y;
                g->pz = g->node[k].z;
                g->hBE = 0;
                func_01E00920_b515(g, &g->node[k], 16, g->rnd);
                g->hB8 = 0;
            }
            if (g->node[k].fn == func_01E013C0_b515) {
                func_00106080(&r2, 0x14, g->node[k].h56, 0);
                g->rect = r2;
                g->tex88 = g->tex5[0];
                g->hB8 = 6;
                g->hC0 = 0;
                g->px = g->node[k].x;
                g->py = g->node[k].y;
                g->pz = g->node[k].z;
                func_01E00920_b515(g, &g->node[k], 16, g->rnd2);
                g->hB8 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 190) {
        return 1;
    }
    if (g->timer == 445) {
        return 4;
    }
    if (g->timer == 440) {
        return 3;
    }
    if (g->timer > 200 && g->timer < 430) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b515:01E01BD0, 98 insns, 2 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x1f4 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b515_01E01BD0 {
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
} Slot_b515_01E01BD0;

typedef struct Obj_b515_01E01BD0 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b515_01E01BD0 slots[0x1f4];
    u8 padB[0xddb4 - 0x2a0 - 0x1f4 * 0x70];
    u8 rgba[4];
    u8 padC[0xde16 - 0xddb4 - 4];
    s16 fB2B0;
} Obj_b515_01E01BD0;

static s32 func_01E01BD0_b515(Obj_b515_01E01BD0 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b515_01E01BD0 *s = NULL;
    s16 i;

    for (i = 0; i < 0x1f4; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x1f4;
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
