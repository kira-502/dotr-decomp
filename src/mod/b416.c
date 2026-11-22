#include "common.h"

/* shape b000:01E00100, 38 insns, 169 copies: one colour into the four vertices of a quad (q = 1.0) */

typedef struct Src_b000_01E00100 {
    u8 b, g, r, a;
} Src_b000_01E00100;

typedef struct Col_b000_01E00100 {
    u8 r, g, b, a;
    f32 q;
} Col_b000_01E00100;

typedef struct Vtx_b000_01E00100 {
    u8 pad[0x10];
    Col_b000_01E00100 c;
} Vtx_b000_01E00100;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_b416(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
    v[0].c.r = s->r;
    v[0].c.g = s->g;
    v[0].c.b = s->b;
    v[0].c.a = s->a;
    v[0].c.q = 1.0f;
    v[1].c.r = s->r;
    v[1].c.g = s->g;
    v[1].c.b = s->b;
    v[1].c.a = s->a;
    v[1].c.q = 1.0f;
    v[2].c.r = s->r;
    v[2].c.g = s->g;
    v[2].c.b = s->b;
    v[2].c.a = s->a;
    v[2].c.q = 1.0f;
    v[3].c.r = s->r;
    v[3].c.g = s->g;
    v[3].c.b = s->b;
    v[3].c.a = s->a;
    v[3].c.q = 1.0f;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E01B20;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[4];
    f32 half;
    u8 pad10[0x30];
    Vec_b001_01E01B20 *pts;
    u8 pad44[8];
    f32 radius;
    u8 pad50[0xA];
    s16 count;
} Ring_b001_01E01B20;

static s32 func_01E00120_b416(Ring_b001_01E01B20 *o, f32 size) {
    s32 i;
    s32 ang;

    o->half = size / 2.0f;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = o->radius * func_0020B550(ang);
            o->pts[i].z = func_0019A5C8() % 20;
            o->pts[i].x = o->radius * func_0020B480(ang);
        } else {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = func_0019A5C8() % 20;
            o->pts[i].z = o->radius * func_0020B480(ang);
            o->pts[i].x = o->radius * func_0020B550(ang);
        }
    }
    return 0;
}

/* shape b001:01E00A30, 740 insns, 55 copies: draws an emitter's particles as textured quads. Each point moves
   with the velocity (or func_001036A0), turns around the emitter centre while the angle catches up, and gets a
   square of the emitter size, aspect-scaled, either rotated (flag 0x1E) or axis-aligned.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E00A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E00A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E00A30 v[4];
    u8 tail[0x20];
} Pkt_b001_01E00A30;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E00A30;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt_b001_01E00A30;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E00A30 color;
    f32 size;
    f32 cx, cy;
    u8 pad18[8];
    s16 u, v, w, h;
    f32 fw, fh;
    Pt_b001_01E00A30 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
} Emit_b001_01E00A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E00A30;

static s32 func_01E002B0_b416(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b001_01E00A30 p;
    Pkt_b001_01E00A30 pkt;
    s32 i;
    f32 dx;
    f32 dy;
    f32 da;
    f32 r;
    f32 kx;
    f32 ky;

    ((Pkt_b001_01E00A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E00A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b416((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
    for (i = 0; i < e->count; i++) {
        if (e->cur != e->angle) {
            if (func_00104520(e->flags, 0x1F) != 0) {
                da = e->angle - e->cur;
                dx = e->pts[i].x - e->cx;
                dy = e->pts[i].y - e->cy;
                if (func_00104520(e->flags, 7) != 0) {
                    func_001036A0(&e->pts[i].x, vel);
                    r = 0.017453292f * da;
                    e->pts[i].x = e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r));
                    e->pts[i].y = e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r));
                } else {
                    r = 0.017453292f * da;
                    e->pts[i].x = vel->x + (e->cx + (dx * func_0020B620(r) - dy * func_0020B730(r)));
                    e->pts[i].y = vel->y + (e->cy + (dx * func_0020B730(r) + dy * func_0020B620(r)));
                }
            } else if (func_00104520(e->flags, 7) != 0) {
                func_001036A0(&e->pts[i].x, vel);
            } else {
                e->pts[i].x += vel->x;
                e->pts[i].y += vel->y;
            }
            if (i == e->count - 1) {
                e->cur = e->angle;
            }
        } else if (func_00104520(e->flags, 7) != 0) {
            func_001036A0(&e->pts[i].x, vel);
        } else {
            e->pts[i].x += vel->x;
            e->pts[i].y += vel->y;
        }
        func_00105260(&pkt, e, i);
        if (func_00104520(e->flags, 0) != 0) {
            if (e->w > e->h) {
                kx = 1.0f;
                ky = (f32)e->h / (f32)e->w;
            } else if (e->w < e->h) {
                kx = (f32)e->w / (f32)e->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (e->fw > e->fh) {
                ky = e->fh / e->fw;
                kx = 1.0f;
            } else if (e->fw < e->fh) {
                kx = e->fh / e->fw;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
        if (func_00104520(e->flags, 0x1E) != 0) {
            r = 0.017453292f * ((e->angle + 135) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            r = 0.017453292f * ((e->angle + 45) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            r = 0.017453292f * ((e->angle + 225) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            r = 0.017453292f * ((e->angle + 315) % 360);
            p.x = e->pts[i].x + kx * (e->size * func_0020B620(r));
            p.y = e->pts[i].y + ky * (e->size * func_0020B730(r));
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        } else {
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            p.z = e->pts[i].z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                e->flags |= 0x100000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y + e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                e->flags |= 0x200000;
            }
            p.x = e->pts[i].x - e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                e->flags |= 0x400000;
            }
            p.x = e->pts[i].x + e->size * kx;
            p.y = e->pts[i].y - e->size * ky;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                e->flags |= 0x800000;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&pkt, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)e->u << 4) | ((u64)(e->u + e->w - 1) << 14) |
                                        ((u64)e->v << 24) | ((u64)(e->v + e->h - 1) << 34));
            }
            func_00208700(&pkt, e->texture, 1);
        }
        if (e->pts[i].life >= 0 && func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
            func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
            if (func_00104520(e->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        e->flags &= 0xFF0FFFFF;
    }
    if (func_00104520(e->flags, 7) == 0) {
        e->cx += vel->x;
        e->cy += vel->y;
    }
    return 0;
}

/* shape b416:01E00E40, 658 insns, 1 copy: b416 scene manager (b157:01E02540 form): code >= 0 clears the scene
   (0x2560), resets two coords, three joint coords, two trail coords (scale 0.1) and a ring coord, six joints, a
   170-tick timer, a disc, two 16-point trail emitters, two 60-point sparks and three 128-point ring sprays (LkSetRing
   2.0); otherwise follows the joint pairs until ticks 122/115/56, copies two joint coords, draws the trails from 116
   and 123; returns 2 at 130, 1 at 105, 6 in 115..129, 8 when the timer ends */

typedef struct {
    Vec4f scale;
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b416_01E00E40;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt1_b416_01E00E40;

typedef struct {
    s32 tex __attribute__((aligned(16)));
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 x, y, z;
    s32 w1C;
    s16 h20, h22;
    s16 w, h;
    s16 tu, tv, tw, th;
    Pt1_b416_01E00E40 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Em1_b416_01E00E40;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt2_b416_01E00E40;

typedef struct {
    s32 tex __attribute__((aligned(16)));
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 u, v, w, h, u0, v0, tw, th;
    Pt2_b416_01E00E40 *pts;
    void *rots;
    s32 w48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Em2_b416_01E00E40;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    s16 h0C;
    s16 h0E;
} Disc_b416_01E00E40;

typedef struct {
    f32 x, y, z;
} Xyz_b416_01E00E40;

typedef struct {
    s32 tex __attribute__((aligned(16)));
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Xyz_b416_01E00E40 pts[60];
} Spark_b416_01E00E40;

typedef struct {
    Crd_b416_01E00E40 crd0;
    Crd_b416_01E00E40 crd1;
    Em1_b416_01E00E40 em1;
    Em1_b416_01E00E40 em2;
    Crd_b416_01E00E40 crd2;
    Disc_b416_01E00E40 disc;
    Crd_b416_01E00E40 crdA[3];
    Em2_b416_01E00E40 ring[3];
    Pt2_b416_01E00E40 pts[3][0x80];
    Crd_b416_01E00E40 crdB[2];
    Spark_b416_01E00E40 spark[2];
    s32 timer;
    s32 step;
    s32 id;
    s32 j[6];
    u8 pad2554[0xC];
} Scene_b416_01E00E40;

static s32 func_01E00E40_b416(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_0019A5C8();
    Scene_b416_01E00E40 *g = (Scene_b416_01E00E40 *)arg0;
    s32 ot;
    Vec4f c[2];
    Vec4f a[2];
    Vec4f b[2];
    Vec4f sc;
    s32 tex __attribute__((aligned(16)));
    s32 i;
    s32 k;
    s32 j;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2560);
        func_00103890(&g->crd0);
        func_00103890(&g->crd1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->crdA[i]);
        }
        for (i = 0; i < 2; i++) {
            func_00103890(&g->crdB[i]);
            g->crdB[i].scale.x = g->crdB[i].scale.y = g->crdB[i].scale.z = 0.1f;
        }
        func_00103890(&g->crd2);
        g->j[0] = func_001F5560(func_001F53A0(), 0x13, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x12, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x2E, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2D, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->timer = 0xAA;
        g->step = 1;
        g->id = code;
        g->disc.flags = 0;
        g->disc.r = 0x80;
        g->disc.g = 0x80;
        g->disc.b = 0x40;
        g->disc.a = 0xFF;
        g->disc.size = 2.0f;
        g->disc.h0C = 0x24;
        g->disc.h0E = 0;
        func_00103260(&tex, 2);
        g->em1.tex = tex;
        g->em1.flags = 0x80007;
        g->em1.x = 0.0f;
        g->em1.y = 0.0f;
        g->em1.z = 0.0f;
        g->em1.w1C = 0;
        g->em1.tu = 0;
        g->em1.tv = 0;
        g->em1.w = 0x20;
        g->em1.h = 0x20;
        g->em1.tw = 0x80;
        g->em1.th = 0x40;
        g->em1.size = 10.0f;
        g->em1.count = 0x10;
        g->em1.step = 1;
        g->em1.h13C = 0;
        g->em1.h140 = 8;
        g->em1.h136 = 5;
        g->em1.h138 = 0xA;
        g->em1.r = 0x40;
        g->em1.g = 0x80;
        g->em1.b = 0x20;
        g->em1.a = 0x80;
        for (i = 0; i < g->em1.count; i++) {
            g->em1.pts[i].x = g->em1.x + (func_0019A5C8() % 20 - 10);
            g->em1.pts[i].y = g->em1.y + (func_0019A5C8() % 20 - 10);
            g->em1.pts[i].z = g->em1.z;
            g->em1.pts[i].life = -g->em1.step * i;
            g->em1.pts[i].pad = 0;
            g->em1.h13E = g->em1.h140 - 1;
        }
        func_00103290(&tex, 1);
        g->em2.tex = tex;
        g->em2.flags = 0x485;
        g->em2.x = 0.0f;
        g->em2.y = 0.0f;
        g->em2.z = 0.0f;
        g->em2.w1C = 0;
        g->em2.tu = 0;
        g->em2.tv = 0;
        g->em2.w = 0x20;
        g->em2.h = 0x20;
        g->em2.tw = 0x80;
        g->em2.th = 0x40;
        g->em2.size = 20.0f;
        g->em2.count = 0x10;
        g->em2.step = 1;
        g->em2.h13C = 1;
        g->em2.h140 = 8;
        g->em2.h136 = 0xA;
        g->em2.h138 = 0xA;
        g->em2.r = 0x80;
        g->em2.g = 0x80;
        g->em2.b = 0x80;
        g->em2.a = 0x80;
        for (i = 0; i < g->em2.count; i++) {
            g->em2.pts[i].x = g->em2.x + (func_0019A5C8() % 20 - 10);
            g->em2.pts[i].y = g->em2.y + (func_0019A5C8() % 20 - 10);
            g->em2.pts[i].z = g->em2.z;
            g->em2.pts[i].life = -g->em2.step * i;
            g->em2.pts[i].pad = func_0019A5C8() % 8;
            g->em2.h13E = g->em2.h140 - 1;
        }
        func_00103260(&tex, 0xF);
        for (i = 0; i < 2; i++) {
            g->spark[i].tex = tex;
            g->spark[i].flags = 1;
            g->spark[i].u = 0xB0;
            g->spark[i].v = 0x40;
            g->spark[i].w = 0x20;
            g->spark[i].h = 0x20;
            g->spark[i].size = 0.5f;
            for (k = 0; k < 60; k++) {
                if (func_00104520(g->spark[i].flags, 0x1D)) {
                    g->spark[i].pts[k].x = func_0019A5C8() % 100 - 50;
                    g->spark[i].pts[k].z = func_0019A5C8() % 50;
                    g->spark[i].pts[k].y = func_0019A5C8() % 100 - 50;
                } else {
                    g->spark[i].pts[k].x = func_0019A5C8() % 50 - 25;
                    g->spark[i].pts[k].y = func_0019A5C8() % 25;
                    g->spark[i].pts[k].z = func_0019A5C8() % 50 - 25;
                }
            }
            g->spark[i].r = 0x80;
            g->spark[i].g = 0x20;
            g->spark[i].b = 0x20;
            g->spark[i].a = 0x80;
        }
        func_00103290(&tex, 0);
        for (k = 0; k < 3; k++) {
            g->ring[k].tex = tex;
            g->ring[k].flags = 0x50000003;
            g->ring[k].r = 0x80;
            g->ring[k].g = 0x80;
            g->ring[k].b = 0x80;
            g->ring[k].a = 0x80;
            g->ring[k].size = 2.0f;
            g->ring[k].rot[0] = 0;
            g->ring[k].rot[1] = 0;
            g->ring[k].rot[2] = 0;
            g->ring[k].u = 0;
            g->ring[k].v = 0;
            g->ring[k].w = 0x20;
            g->ring[k].h = 0x20;
            g->ring[k].u0 = 0;
            g->ring[k].v0 = 0;
            g->ring[k].tw = 0x80;
            g->ring[k].th = 0x40;
            g->ring[k].pts = g->pts[k];
            g->ring[k].rots = 0;
            g->ring[k].w48 = 0;
            g->ring[k].radius = 3.0f;
            g->ring[k].count = 0x80;
            g->ring[k].nframes = 8;
            g->ring[k].rate = 0;
            func_01E00120_b416((Ring_b001_01E01B20 *)&g->ring[k], 2.0f);
            for (j = 0; j < g->ring[k].count; j++) {
                g->pts[k][j].t = -(func_0019A5C8() % 12);
                g->pts[k][j].a = 0;
                g->pts[k][j].frame = 0;
                g->pts[k][j].y -= 10.0f;
            }
        }
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->crd1.pos);
    if (g->step < 0x7A) {
        func_001F5620(func_001F53A0(), g->j[2], &g->crdA[0].pos);
        func_001F5620(func_001F53A0(), g->j[2], &a[0]);
        func_001F5620(func_001F53A0(), g->j[3], &a[1]);
        func_00103DB0(&a[0], &a[1], &g->crdA[0].rot);
    }
    if (g->step < 0x73) {
        func_001F5620(func_001F53A0(), g->j[4], &g->crdA[1].pos);
        func_001F5620(func_001F53A0(), g->j[4], &b[0]);
        func_001F5620(func_001F53A0(), g->j[5], &b[1]);
        func_00103DB0(&b[0], &b[1], &g->crdA[1].rot);
    }
    if (g->step < 0x38) {
        func_001F5620(func_001F53A0(), g->j[0], &g->crdA[2].pos);
        func_001F5620(func_001F53A0(), g->j[0], &c[0]);
        func_001F5620(func_001F53A0(), g->j[1], &c[1]);
        func_00103DB0(&c[0], &c[1], &g->crdA[2].rot);
    }
    func_001F5620(func_001F53A0(), g->j[0], &g->crd2.pos);
    for (i = 0; i < 2; i++) {
        g->crdB[i].pos = g->crdA[i].pos;
    }
    func_001038D0(&g->crd0);
    func_001039A0(&g->crd1);
    for (i = 0; i < 2; i++) {
        func_001039A0(&g->crdB[i]);
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->crdA[i]);
    }
    func_001039A0(&g->crd2);
    if (g->step > 0x73) {
        sc.x = sc.y = sc.z = 0.0f;
        func_01E002B0_b416(ot, (Cam_b001_01E00A30 *)&g->crd1, (Emit_b001_01E00A30 *)&g->em1,
                           (Vec_b001_01E00A30 *)&sc);
        func_00103470(&g->em1.a, 0, 8);
    }
    if (g->step == 0x7A) {
        g->em1.a = 0x80;
    }
    if (g->step > 0x7A) {
        sc.x = sc.y = sc.z = 1.01f;
        func_01E002B0_b416(ot, (Cam_b001_01E00A30 *)&g->crd1, (Emit_b001_01E00A30 *)&g->em2,
                           (Vec_b001_01E00A30 *)&sc);
        func_00103470(&g->em2.a, 0, 4);
    }
    g->step++;
    g->timer--;
    if (g->step == 0x82) {
        return 2;
    }
    if (g->step == 0x69) {
        return 1;
    }
    if (g->step >= 0x73 && g->step < 0x82) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
