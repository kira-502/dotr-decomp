#include "common.h"

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E00080, 237 insns, 27 copies: b010:01E00080 (move an emitter, set its level from the blend mode) built at -O1,p: every field read again, nothing CSEd */

typedef struct Obj_b002_01E00080 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 pad5[0xB];
    u8 f10[0x10];
    Vec4f pos;
    u8 pad30[8];
    f32 level;
    u8 pad3C[4];
    Vec4f vel;
    f32 base;
} Obj_b002_01E00080;

#pragma optimization_level 1

static void func_01E00080_b710(Obj_b002_01E00080 *arg0) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    Obj_b002_01E00080 *o;
    u8 d;
    u8 e;
    s32 on;
    f32 k;

    o = arg0;
    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    d = o->b0 & o->b3;
    e = o->b2 - o->b0;
    if (o->b3 == 0xFF) {
        k = o->base / o->b2;
    } else {
        k = o->base / (o->b3 + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (o->b3 == 0xFF) {
            if (e < o->b2 >> 1) {
                o->level = 2.0f * k * e;
            } else {
                o->level = 2.0f * k * o->b0;
            }
        } else {
            if (d < o->b3 >> 1) {
                o->level = 2.0f * k * (o->b3 - d);
            } else {
                o->level = 2.0f * k * d;
            }
        }
        break;
    case 4:
        o->level = o->base;
        if (o->b0 & 1) {
            o->level *= 0.5f;
        }
        break;
    case 8:
        if (o->b0 & 1) {
            on = 0;
        }
    default:
        o->level = o->base;
        break;
    }
    if (on == 0 || o->b0 == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(o->f10);
    }
}
#pragma optimization_level reset

/* shape b241:01E00440 (ShFx_Flear01), 839 insns, 26 copies (-O1,p): draws each emitter of a list as a glowing ring: a
   fan of triangles and a quad pair per segment */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b241_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b241_01E00440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b241_01E00440 xyz;
} Vtx1_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    Vtx1_b241_01E00440 v[3];
    u8 tail[8];
} Pkt1_b241_01E00440;

typedef struct {
    u64 st;
    Xyz_b241_01E00440 xyz;
} Vtx2_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b241_01E00440 v[4];
    u8 tail[0x20];
} Pkt2_b241_01E00440;

typedef struct {
    f32 x, y, z, w;
} V4_b241_01E00440;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b241_01E00440;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    V4_b241_01E00440 pos;
    V4_b241_01E00440 vel;
    V4_b241_01E00440 org;
} Obj_b241_01E00440;

#pragma optimization_level 1

static s32 func_01E00440_b710(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E07880_b710;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002086D0(void *, u64);
    extern void func_00101D20(void *, void *, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b241_01E00440 *o;
    s32 k;
    s32 i;
    s32 segs;
    s32 h;
    f32 m0[16];
    f32 m1[16];
    V4_b241_01E00440 org;
    Tex_b241_01E00440 t;
    Xyz_b241_01E00440 scr;
    Pkt1_b241_01E00440 p1 __attribute__((aligned(8)));
    Pkt2_b241_01E00440 p2 __attribute__((aligned(8)));
    f32 depth;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    u8 d;

    o = obj;
    t = D_01E07880_b710;
    h = func_00202BF0(t.id, t.kind);
    for (k = 0; k < n; k++) {
        if (k != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->radius += o->grow;
        org = o->org;
        segs = o->segs > 9 ? 9 : o->segs;
        step = 90.0f / segs;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m0, NULL, NULL, &o->pos);
        func_0020BC00(m1, m0);
        if (func_00205440(&org, m1, &scr, &depth) == 0 || func_00101600(&scr) == 0) {
            continue;
        }
        r = func_001018E0(o->radius, depth);
        w = func_001018E0(o->width, depth);
        if (o->flags & 0x80) {
            scr.z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            zf = depth;
        }
        ((Hdr_b241_01E00440 *)(s32)&p1)->count = 0x13;
        ((Hdr_b241_01E00440 *)(s32)&p1)->tag = 6;
        ((Hdr_b241_01E00440 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b241_01E00440 *)(s32)&p1)->pad = 0;
        p1.v[0].r = o->ir;
        p1.v[1].r = p1.v[2].r = o->r;
        p1.v[0].g = o->ig;
        p1.v[1].g = p1.v[2].g = o->g;
        p1.v[0].b = o->ib;
        p1.v[1].b = p1.v[2].b = o->b;
        p1.v[0].q = p1.v[1].q = p1.v[2].q = 1.0f;
        if (o->flags & 8) {
            func_002086D0(&p1, 0x42);
        } else {
            func_002086D0(&p1, 0x48);
        }
        ((Hdr_b241_01E00440 *)(s32)&p2)->count = 0x24;
        ((Hdr_b241_01E00440 *)(s32)&p2)->tag = 9;
        ((Hdr_b241_01E00440 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b241_01E00440 *)(s32)&p2)->pad = 0;
        p2.r = o->r;
        p2.g = o->g;
        p2.b = o->b;
        p2.q = 1.0f;
        func_00101D20(&p2, &t, h);
        p1.v[0].a = o->alpha;
        p2.a = o->alpha >> 1;
        p1.v[1].a = p1.v[2].a = 0;
        if (!(o->flags & 0x40)) {
            if (o->cur < 8) {
                p1.v[0].a = (o->alpha >> 3) * o->cur;
                p2.a = (o->alpha >> 4) * o->cur;
            } else {
                d = o->max - o->cur;
                if (d < 8) {
                    p1.v[0].a = (o->alpha >> 3) * d;
                    p2.a = (o->alpha >> 4) * d;
                }
            }
        }
        if (o->cur & 1) {
            if (o->flags & 2) {
                if (p1.v[0].a > 0x10) {
                    p1.v[0].a -= 0x10;
                }
            }
            if (o->flags & 4) {
                if (p1.v[0].a > 0) {
                    p1.v[0].a >>= 1;
                }
            }
        }
        x = r * func_001A6898(0.0f);
        y = r * func_001A6A88(0.0f);
        p2.v[0].xyz.z = p2.v[1].xyz.z = p2.v[2].xyz.z = p2.v[3].xyz.z = p1.v[0].xyz.z = p1.v[1].xyz.z =
            p1.v[2].xyz.z = scr.z;
        p2.v[0].xyz.f = p2.v[1].xyz.f = p2.v[2].xyz.f = p2.v[3].xyz.f = p1.v[0].xyz.f = p1.v[1].xyz.f =
            p1.v[2].xyz.f = 1;
        for (i = 1; i < segs * 4 + 1; i++) {
            px = x;
            py = y;
            x = r * func_001A6898(3.1415927f * (step * i) / 180.0f);
            y = r * func_001A6A88(3.1415927f * (step * i) / 180.0f);
            p1.v[0].xyz.x = scr.x;
            p1.v[0].xyz.y = scr.y;
            p1.v[1].xyz.x = scr.x + px;
            p1.v[1].xyz.y = scr.y + py;
            p1.v[2].xyz.x = scr.x + x;
            p1.v[2].xyz.y = scr.y + y;
            func_002075F0(&p1, tex, (u32)zf);
            if (o->flags & 1) {
                continue;
            }
            p2.v[0].xyz.x = p2.v[2].xyz.x = scr.x + px;
            p2.v[1].xyz.x = p2.v[3].xyz.x = scr.x + x;
            p2.v[0].xyz.y = scr.y + py - w;
            p2.v[2].xyz.y = w + (scr.y + py);
            p2.v[1].xyz.y = scr.y + y - w;
            p2.v[3].xyz.y = w + (scr.y + y);
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            p2.v[0].xyz.x = w + (scr.x + px);
            p2.v[2].xyz.x = scr.x + px - w;
            p2.v[1].xyz.x = w + (scr.x + x);
            p2.v[3].xyz.x = scr.x + x - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b380:01E01160, 637 insns, 3 copies: moves n arc emitters (0x5C bytes each: an angle window sweeping one way, a
   growing radius) and draws the arc as rings of gouraud quads from the centre outwards, colour fading from the
   inner to the outer colour per ring (or two-tone by flag 1), alpha fading at the end. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b380_01E01160;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b380_01E01160 xyz;
} Vtx_b380_01E01160;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b380_01E01160 v[4];
} Pkt_b380_01E01160;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    u8 n8;
    u8 grow_until;
    u8 rings;
    u8 padB;
    f32 a0;
    f32 a1;
    f32 step;
    f32 spin;
    f32 radius;
    f32 grow;
    u8 b0, g0, r0, al0;
    u8 b1, g1, r1, al1;
    f32 pos[3];
    u8 pad38[4];
    f32 vel[3];
    u8 pad48[4];
    s32 rot[4];
} Arc_b380_01E01160;

#pragma optimization_level 1

static s32 func_01E01160_b710(void *arg0, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat2[16];
    f32 mat[16];
    f32 d[4];
    Vec4f p;
    Pkt_b380_01E01160 pkt;
    Xyz_b380_01E01160 c;
    s32 al[2];
    f32 dc;
    Arc_b380_01E01160 *e;
    s32 i;
    s32 dir;
    s32 k;
    f32 a;
    f32 end;
    f32 astep;
    f32 ang;
    f32 rstep;
    f32 r;
    f32 dr;
    f32 dg;
    f32 db;
    f32 da;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Arc_b380_01E01160 *)((u8 *)e + 0x5C);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->a1 > e->a0) {
            dir = 0;
        } else {
            dir = 1;
        }
        if (dir) {
            e->a0 -= e->spin;
            e->a1 -= e->spin;
        } else {
            e->a0 += e->spin;
            e->a1 += e->spin;
        }
        e->pos[0] += e->vel[0];
        e->pos[1] += e->vel[1];
        e->pos[2] += e->vel[2];
        if (e->life > e->grow_until) {
            e->radius += e->grow;
        }
        func_00101BA0(e, e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b380_01E01160 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b380_01E01160 *)(s32)&pkt)->tag = 8;
        ((Pkt_b380_01E01160 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b380_01E01160 *)(s32)&pkt)->pad = 0;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_002086D0(&pkt, 0x48);
        if (dir) {
            a = e->a1;
            end = e->a0;
        } else {
            a = e->a0;
            end = e->a1;
        }
        astep = e->step * e->n8;
        rstep = e->radius / e->rings;
        dr = (e->r0 - e->r1) / (f32)e->rings;
        dg = (e->g0 - e->g1) / (f32)e->rings;
        db = (e->b0 - e->b1) / (f32)e->rings;
        da = (e->al0 - e->al1) / (f32)e->rings;
        p.x = p.y = p.z = 0.0f;
        if (func_00205440(&p, mat, &c, &dc) == 0) {
            continue;
        }
        for (; a < end; a += astep) {
            pkt.v[2].xyz = c;
            pkt.v[3].xyz = c;
            d[2] = d[3] = dc;
            for (k = 0; k < e->rings; k++) {
                pkt.v[0].xyz = pkt.v[2].xyz;
                d[0] = d[2];
                pkt.v[1].xyz = pkt.v[3].xyz;
                d[1] = d[3];
                if (dir) {
                    ang = a + e->step * k;
                } else {
                    ang = a - e->step * k;
                }
                r = (k + 1) * rstep;
                p.x = r * func_001A6898((3.1415927f * ang) / 180.0f);
                p.z = r * func_001A6A88((3.1415927f * ang) / 180.0f);
                if (func_00205440(&p, mat, &pkt.v[2].xyz, &d[2]) == 0) {
                    continue;
                }
                p.x = r * func_001A6898((3.1415927f * (ang + e->step)) / 180.0f);
                p.z = r * func_001A6A88((3.1415927f * (ang + e->step)) / 180.0f);
                if (func_00205440(&p, mat, &pkt.v[3].xyz, &d[3]) == 0) {
                    continue;
                }
                al[0] = e->al0 - (s32)(da * k);
                al[1] = e->al0 - (s32)(1.0f + da * k);
                if (e->life < 8) {
                    al[0] = e->life * (al[0] >> 3);
                    al[1] = e->life * (al[1] >> 3);
                }
                pkt.v[1].a = pkt.v[0].a = al[0];
                pkt.v[3].a = pkt.v[2].a = al[1];
                if (e->flags & 1) {
                    if (dir) {
                        pkt.v[1].a = pkt.v[3].a = al[0] >> 1;
                        pkt.v[1].r = pkt.v[3].r = e->r1;
                        pkt.v[1].g = pkt.v[3].g = e->g1;
                        pkt.v[1].b = pkt.v[3].b = e->b1;
                        pkt.v[0].r = pkt.v[2].r = e->r0;
                        pkt.v[0].g = pkt.v[2].g = e->g0;
                        pkt.v[0].b = pkt.v[2].b = e->b0;
                    } else {
                        pkt.v[0].a = pkt.v[2].a = al[0] >> 1;
                        pkt.v[1].r = pkt.v[3].r = e->r0;
                        pkt.v[1].g = pkt.v[3].g = e->g0;
                        pkt.v[1].b = pkt.v[3].b = e->b0;
                        pkt.v[0].r = pkt.v[2].r = e->r1;
                        pkt.v[0].g = pkt.v[2].g = e->g1;
                        pkt.v[0].b = pkt.v[2].b = e->b1;
                    }
                } else {
                    pkt.v[0].r = pkt.v[1].r = e->r0 - (s32)(dr * k);
                    pkt.v[2].r = pkt.v[3].r = e->r0 - (s32)(dr * (k + 1));
                    pkt.v[0].g = pkt.v[1].g = e->g0 - (s32)(dg * k);
                    pkt.v[2].g = pkt.v[3].g = e->g0 - (s32)(dg * (k + 1));
                    pkt.v[0].b = pkt.v[1].b = e->b0 - (s32)(db * k);
                    pkt.v[2].b = pkt.v[3].b = e->b0 - (s32)(db * (k + 1));
                }
                if (k == e->rings - 1) {
                    pkt.v[3].a = pkt.v[2].a = 0;
                }
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b603:01E01160 (ShFx_Core01), 691 insns, 9 copies (-O1,p): update and draw spinning 2-D beams (0x50 bytes
   each): move, project, and draw each as two quads per half-turn, alpha and length fading in and out; the source of
   shape b213:01E00F90, built here at -O1 */

#define ABS_b603_01E01160(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b603_01E01160;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b603_01E01160;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b603_01E01160 p;
} Vtx_b603_01E01160;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b603_01E01160 v[4];
    u8 tail[0x20];
} Pkt_b603_01E01160;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b603_01E01160;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 b, g, r;
    u8 pad0B;
    u8 b2, g2, r2, a;
    f32 len;
    f32 width;
    f32 angle;
    f32 spin;
    Vec_b603_01E01160 pos;
    Vec_b603_01E01160 vel;
    Vec_b603_01E01160 point;
} Beam_b603_01E01160;

#pragma optimization_level 1

static s32 func_01E01B60_b710(void *p, s32 target, s32 count) {
    extern Tex_b603_01E01160 D_01E078A0_b710;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Beam_b603_01E01160 *o = p;
    s32 i;
    s32 j;
    s32 h __attribute__((aligned(16)));
    u8 k;
    f32 zd;
    f32 dx;
    f32 ady;
    f32 dy;
    f32 len;
    f32 r1;
    f32 w;
    f32 t;
    f32 m2[16];
    f32 m1[16];
    Vec_b603_01E01160 pt;
    Tex_b603_01E01160 tex;
    Xyz_b603_01E01160 q;
    Pkt_b603_01E01160 pkt __attribute__((aligned(8)));
    f32 dep;

    tex = D_01E078A0_b710;
    h = func_00202BF0(tex.id, tex.kind);
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->angle += o->spin;
        pt = o->point;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m2, 0, 0, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b603_01E01160 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b603_01E01160 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b603_01E01160 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b603_01E01160 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = 0;
        pkt.v[1].r = pkt.v[2].r = o->r;
        pkt.v[0].g = 0;
        pkt.v[1].g = pkt.v[2].g = o->g;
        pkt.v[0].b = 0;
        pkt.v[1].b = pkt.v[2].b = o->b;
        pkt.v[3].r = o->r2;
        pkt.v[3].g = o->g2;
        pkt.v[3].b = o->b2;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_00101EE0(&pkt, &tex, h);
        if (o->life >= 8 || (o->flags & 0x40)) {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->a;
        } else {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (o->a >> 3) * o->life;
        }
        pkt.v[0].a = 0;
        if (func_00205440(&pt, m1, &q, &dep) == 0 || func_00101600(&q) == 0) {
            continue;
        }
        r1 = func_001018E0(o->len, dep);
        w = func_001018E0(o->width, dep);
        if (o->flags & 0x80) {
            q.z = 0xFFFFFE;
            zd = 0.0f;
        } else {
            zd = dep;
        }
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
        pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
        len = r1;
        if (!(o->flags & 0x40)) {
            if (!(o->flags & 1)) {
                k = o->total - o->life;
                if (k < 8) {
                    len = r1 * (0.125f * k);
                }
            }
            if (o->life < 8) {
                len = r1 * (0.125f * o->life);
            }
        }
        for (j = 0; j < 2; j++) {
            t = 180.0f * j;
            dx = len * func_001A6898(3.1415927f * (o->angle + t) / 180.0f);
            dy = len * func_001A6A88(3.1415927f * (o->angle + t) / 180.0f);
            ady = ABS_b603_01E01160(dy);
            if (!(ABS_b603_01E01160(dx) <= ady)) {
                pkt.v[0].p.x = pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[1].p.x = pkt.v[3].p.x = q.x;
                pkt.v[0].p.y = (u32)(q.y + dy - w);
                pkt.v[1].p.y = (u32)(q.y - w);
                pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[3].p.y = q.y;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.y = (u32)(w + (q.y + dy));
                pkt.v[1].p.y = (u32)(q.y + w);
                func_002075F0(&pkt, target, (u32)zd);
            } else {
                pkt.v[0].p.y = pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[1].p.y = pkt.v[3].p.y = q.y;
                pkt.v[0].p.x = (u32)(q.x + dx - w);
                pkt.v[1].p.x = (u32)(q.x - w);
                pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[3].p.x = q.x;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.x = (u32)(w + (q.x + dx));
                pkt.v[1].p.x = (u32)(q.x + w);
                func_002075F0(&pkt, target, (u32)zd);
            }
        }
    }
    return 1;
}

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

#define ABS_b011_01E04380(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b011_01E04380;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b011_01E04380;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b011_01E04380 p;
} Vtx_b011_01E04380;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b011_01E04380 v[4];
    u8 tail[0x20];
} Pkt_b011_01E04380;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b011_01E04380;

typedef struct {
    u8 step;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 segments;
    u8 index;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 delay;
    u8 target;
    u8 pad0F;
    u8 *table;
    f32 size;
    f32 radius;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec_b011_01E04380 pos;
    Vec_b011_01E04380 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b011_01E04380;

extern Tex_b011_01E04380 D_01E078C0_b710;

#pragma optimization_level 1

static s32 func_01E02630_b710(Ray_b011_01E04380 *obj, s32 target, s32 count) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101940(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Ray_b011_01E04380 *o;
    s32 i;
    s32 j;
    u8 idx;
    s32 span;
    s32 texture;
    f32 w;
    f32 zd;
    f32 y;
    f32 angle;
    f32 x;
    f32 r;
    f32 z;
    f32 step;
    f32 m2[16];
    f32 m1[16];
    Xyz_b011_01E04380 xy[2];
    Vec_b011_01E04380 pt;
    Vec_b011_01E04380 d;
    Vec_b011_01E04380 tmp;
    Tex_b011_01E04380 tex0;
    Tex_b011_01E04380 tex;
    Pkt_b011_01E04380 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E078C0_b710;
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        if (o->flags & 4) {
            texture = func_00202BF0(5, o->texkind);
            tex.page = o->texpage;
            func_001020B0(&tex, o->texmode, 0);
        } else {
            texture = func_00202BF0(tex0.id, tex0.kind);
            tex = tex0;
        }
        if (!(o->flags & 2)) {
            tex.u -= 0x10;
            tex.v -= 0x10;
        }
        idx = o->index;
        step = 17.0f;
        angle = 0.0f;
        if (o->step < o->delay) {
            span = o->total - o->delay;
        } else {
            span = o->total - o->step;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->rot[0] += o->spin[0];
        o->rot[1] += o->spin[1];
        o->rot[2] += o->spin[2];
        func_00101BA0(o, &o->pos);
        if (o->flags & 8) {
            func_001F5620(func_001F53A0(), o->target, &tmp);
            d.x = tmp.x - o->pos.x;
            d.y = tmp.y - o->pos.y;
            d.z = tmp.z - o->pos.z;
            func_00101940(&d, o->rot);
        }
        func_0020EB40(m1);
        func_0020C940(m2, 0, o->rot, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b011_01E04380 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = o->r0;
        pkt.v[2].r = pkt.v[3].r = o->r1;
        pkt.v[0].g = pkt.v[1].g = o->g0;
        pkt.v[2].g = pkt.v[3].g = o->g1;
        pkt.v[0].b = pkt.v[1].b = o->b0;
        pkt.v[2].b = pkt.v[3].b = o->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (o->step <= 7 && !(o->flags & 0x40)) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = (o->a0 >> 3) * o->step;
            pkt.v[3].a = (o->a1 >> 3) * o->step;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = o->a0;
            pkt.v[3].a = o->a1;
        }
        func_00101EE0(&pkt, &tex, texture);
        pt.x = pt.y = pt.z = 0.0f;
        if (func_00205440(&pt, m1, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
            continue;
        }
        for (j = 0; j < o->segments; j++) {
            if (o->flags & 1) {
                x = o->size * (o->table[idx] - o->table[idx + 1]) / 255.0f;
                y = o->size * (o->table[idx + 2] - o->table[idx + 3]) / 255.0f;
                z = o->size * (o->table[idx + 4] - o->table[idx + 5]) / 255.0f;
                idx += 6;
            } else {
                angle += step;
                if (!(angle <= 360.0f)) {
                    angle -= 360.0f;
                }
                r = o->radius * o->table[idx] / 255.0f;
                idx++;
                x = r * func_001A6898(3.1415927f * angle / 180.0f);
                z = r * func_001A6A88(3.1415927f * angle / 180.0f);
                y = o->size / 2.0f;
                y += y * (o->table[idx] / 255.0f);
                idx++;
            }
            pt.x = x * span;
            pt.y = y * span;
            pt.z = z * span;
            if (func_00205440(&pt, m1, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0) {
                continue;
            }
            w = func_001018E0(o->width, dep[0]);
            if (o->flags & 0x80) {
                pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                zd = 0.0f;
            } else {
                if (dep[0] < dep[1]) {
                    zd = dep[0];
                } else {
                    zd = dep[1];
                }
                pkt.v[0].p.z = pkt.v[1].p.z = xy[0].z;
                pkt.v[2].p.z = pkt.v[3].p.z = xy[1].z;
            }
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 0;
            if (ABS_b011_01E04380(xy[1].x - xy[0].x) > ABS_b011_01E04380(xy[1].y - xy[0].y)) {
                pkt.v[0].p.y = xy[0].y;
                pkt.v[1].p.y = (u32)(xy[0].y - w);
                pkt.v[2].p.y = (u32)(xy[0].y + w);
                pkt.v[3].p.y = xy[1].y;
                if (xy[0].x < xy[1].x) {
                    pkt.v[0].p.x = (u32)(xy[0].x - w);
                } else {
                    pkt.v[0].p.x = (u32)(xy[0].x + w);
                }
                pkt.v[1].p.x = pkt.v[2].p.x = xy[0].x;
                pkt.v[3].p.x = xy[1].x;
            } else {
                pkt.v[0].p.x = xy[0].x;
                pkt.v[1].p.x = (u32)(xy[0].x - w);
                pkt.v[2].p.x = (u32)(xy[0].x + w);
                pkt.v[3].p.x = xy[1].x;
                if (xy[0].y < xy[1].y) {
                    pkt.v[0].p.y = (u32)(xy[0].y - w);
                } else {
                    pkt.v[0].p.y = (u32)(xy[0].y + w);
                }
                pkt.v[1].p.y = pkt.v[2].p.y = xy[0].y;
                pkt.v[3].p.y = xy[1].y;
            }
            func_002075F0(&pkt, target, (u32)zd);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

/* shape b061:01E01170, 696 insns, 12 copies: moves and draws n spark emitters (0x44 bytes each): velocity, gravity, floor
   bounce, size growth, optional follow; each live one is one camera-facing square of its size around its
   projected point, with one of four texture corner orders picked by flags & 0x30. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b061_01E01170;

typedef struct {
    u64 uv;
    Xyz_b061_01E01170 xyz;
} Vtx_b061_01E01170;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b061_01E01170 v[4];
    u8 tail[0x20];
} Pkt_b061_01E01170;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b061_01E01170;

typedef struct {
    u8 life;
    u8 pad01;
    u8 max;
    u8 pad03;
    u8 flags;
    u8 follow;
    u8 pad06[2];
    u8 texkind;
    u8 mode;
    u8 texmode;
    u8 page;
    u8 b, g, r, a;
    f32 size;
    f32 grow;
    f32 gravity;
    f32 floor;
    f32 px, py, pz;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Spark_b061_01E01170;

#pragma optimization_level 1

static s32 func_01E03360_b710(void *arg0, s32 ot, s32 n) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern s32 func_001022D0(s32, s32);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat[16];
    Vec4f pt;
    Vec4f tmp;
    Tex_b061_01E01170 td;
    Pkt_b061_01E01170 pkt __attribute__((aligned(8)));
    Xyz_b061_01E01170 scr;
    f32 depth;
    Spark_b061_01E01170 *e;
    s32 i;
    s32 tex;
    s32 mode;
    s32 d;
    f32 s;
    f32 zf;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Spark_b061_01E01170 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texkind);
        e->vx += e->ax;
        e->vy += e->ay + e->gravity;
        e->vz += e->az;
        e->px += e->vx;
        e->py += e->vy;
        e->pz += e->vz;
        e->size += e->grow;
        if (e->py < e->floor) {
            e->py = e->floor;
            if (e->flags & 2) {
                e->vy = -(0.7f * e->vy);
            }
        }
        if (e->follow != 0) {
            func_00101BA0(e, &tmp);
            e->px = tmp.x;
            e->py = tmp.y;
            e->pz = tmp.z;
        }
        pt.x = e->px;
        pt.y = e->py;
        pt.z = e->pz;
        func_0020EB40(mat);
        ((Pkt_b061_01E01170 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b061_01E01170 *)(s32)&pkt)->tag = 9;
        ((Pkt_b061_01E01170 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b061_01E01170 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        d = e->max - e->life;
        mode = e->mode;
        if (e->flags & 1) {
            mode = (u8)func_001022D0(e->texmode, d);
            if (e->flags & 4) {
                e->flags &= 0xCF;
                e->flags |= ((func_0019A5C8() >> 4) & 3) << 4;
            }
        }
        td.page = e->page;
        func_001020B0(&td, mode, e->texmode);
        func_00101D20(&pkt, &td, tex);
        pkt.a = e->a;
        if (!(e->flags & 0x40) && e->life < 16) {
            pkt.a = (e->a >> 4) * e->life;
        }
        if (func_00205440(&pt, mat, &scr, &depth) != 0 && func_00101600(&scr) != 0) {
            s = func_001018E0(e->size, depth);
            if (e->flags & 0x80) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                zf = 0.0f;
            } else {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = scr.z;
                zf = depth;
            }
            switch (e->flags & 0x30) {
            case 0x10:
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = scr.x - s;
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = scr.x + s;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = scr.y - s;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = scr.y + s;
                break;
            case 0x20:
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = scr.x - s;
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = scr.x + s;
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = scr.y - s;
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = scr.y + s;
                break;
            case 0x30:
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = scr.x - s;
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = scr.x + s;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = scr.y - s;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = scr.y + s;
                break;
            default:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = scr.x - s;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = scr.x + s;
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = scr.y - s;
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = scr.y + s;
                break;
            }
            func_002075F0(&pkt, ot, (u32)zf);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b710:01E03E40 (ShFx_Cfade), 336 insns, 1 copy (-O1,p): b532:01E025B0's colour fade quad at -O1, object
   pointer as a local copy of the first argument */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b710_01E03E40;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b710_01E03E40;

typedef struct {
    Hdr_b710_01E03E40 h;
    Vtx_b710_01E03E40 v[4];
    u8 tail[8];
} Pkt_b710_01E03E40;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 b, g, r;
} Obj_b710_01E03E40;

#pragma optimization_level 1

static s32 func_01E03E40_b710(s32 arg0, s32 tex) {
    Obj_b710_01E03E40 *o = (Obj_b710_01E03E40 *)arg0;
    Pkt_b710_01E03E40 p __attribute__((aligned(8)));
    u8 a;
    s32 d;
    f32 s;
    f32 c;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b710_01E03E40 *)(s32)&p)->count = 0x14;
    ((Hdr_b710_01E03E40 *)(s32)&p)->tag = 8;
    ((Hdr_b710_01E03E40 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b710_01E03E40 *)(s32)&p)->pad = 0;
    switch (o->flags & 7) {
    case 1:
        a = func_001A23B0(128.0f / o->max * o->cur);
        break;
    case 2:
        a = ((o->max - o->cur) << 7) / o->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (o->cur == 1 && (o->flags & 0x80)) {
        o->cur = o->max;
        if (o->flags & 1) {
            o->flags = 2;
        } else {
            o->flags = 1;
        }
    }
    if (o->flags & 8) {
        a >>= 1;
    }
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = o->r;
    p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g = o->g;
    p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = o->b;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        s = 7168.0f / (o->max >> 1);
        c = 32768.0f;
        d = o->max - o->cur;
        a = (0x80 / (o->max >> 1)) * (d >> 1);
        if ((o->max >> 1) < d) {
            p.v[0].a = p.v[1].a = a;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = func_001A23B0(c - s * d);
        p.v[2].y = p.v[3].y = func_001A23B0(c);
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = func_001A23B0(c);
        p.v[2].y = p.v[3].y = func_001A23B0(c + s * d);
        func_002075F0((s32)&p, tex, 0);
    } else {
        p.v[0].a = p.v[1].a = p.v[2].a = p.v[3].a = a;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = 0x7200;
        p.v[2].y = p.v[3].y = 0x8E00;
        func_002075F0((s32)&p, tex, 0);
    }
    return 1;
}
#pragma optimization_level reset

/* shape b200:01E05B40 (ShFx_Redeye), 766 insns, 3 copies (-O1,p): b099:01E02A90's red-eye streak at -O1: locals
   declared i, pool, ..., idx, r, tex, k, m; both alpha factors unsigned */

typedef struct {
    f32 x, y, z;
} Vec3_b200_01E05B40;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b200_01E05B40;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b200_01E05B40 xyz;
} Vtx_b200_01E05B40;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b200_01E05B40 v[4];
    u8 tail[0x20];
} Pkt_b200_01E05B40;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b200_01E05B40;

typedef struct {
    Tex_b200_01E05B40 v[2];
} Tmpl_b200_01E05B40;

typedef struct {
    u8 life;
    u8 pad1[3];
    f32 x;
    f32 y;
    f32 z;
} Rec_b200_01E05B40;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spl_b200_01E05B40;

typedef struct {
    u8 life;
    u8 pad1[4];
    u8 on;
    u8 sel;
    u8 pad7;
    Rec_b200_01E05B40 *pool;
    s16 ids[9];
    u8 kind;
    u8 n;
    u8 texid;
    u8 sel0;
    u8 sel1;
    u8 maxseg;
    u8 pad24[4];
    f32 th;
    f32 width;
    f32 depth;
    u8 b, g, r, a;
    Vec3_b200_01E05B40 off;
    u8 pad44[4];
} Emit_b200_01E05B40;

#pragma optimization_level 1

static s32 func_01E04380_b710(void *arg0, s32 ot, s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101EE0(void *, void *, void *);
    Emit_b200_01E05B40 *e = arg0;
    s32 i;
    Rec_b200_01E05B40 *pool = e->pool;
    f32 mat[16];
    Spl_b200_01E05B40 spl;
    Vec4f pos;
    extern Tmpl_b200_01E05B40 D_01E078E0_b710;
    Tmpl_b200_01E05B40 tmpl = D_01E078E0_b710;
    Vec4f pos2;
    Vec4f dir;
    Vec4f cam;
    Xyz_b200_01E05B40 scr;
    Pkt_b200_01E05B40 pkt __attribute__((aligned(8)));
    f32 depth;
    s32 idx;
    Rec_b200_01E05B40 *r;
    void *tex;
    s32 k;
    s32 m;
    f32 a;
    f32 hw;
    f32 as;
    f32 dx;
    f32 dy;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->on = 1;
        e->sel = e->sel0;
        func_00101BA0(e, &pos);
        pos.x += e->off.x;
        pos.y += e->off.y;
        pos.z += e->off.z;
        cam = *(Vec4f *)func_001FAD10(0);
        e->sel = e->sel1;
        func_00101BA0(e, &pos2);
        dir.x = pos.x - pos2.x;
        dir.y = pos.y - pos2.y;
        dir.z = pos.z - pos2.z;
        func_0020D070(&dir.x);
        func_0020D070(&cam.x);
        if (func_0020D1A0(&dir.x, &cam.x) > e->th) {
            for (k = 0; k < e->n; k++) {
                if (e->ids[k] >= 0) {
                    (r = &pool[e->ids[k]])->life = 0;
                    e->ids[k] = -1;
                }
            }
            continue;
        }
        func_0020EB40(mat);
        for (k = e->n; k > 0; k--) {
            if (e->ids[k - 1] >= 0) {
                r = &pool[e->ids[k - 1]];
                r->life = e->life;
            }
            e->ids[k] = e->ids[k - 1];
        }
        if (e->ids[e->n] >= 0) {
            (r = &pool[e->ids[e->n]])->life = 0;
            e->ids[e->n] = -1;
        }
        if (e->life == 0) {
            continue;
        }
        idx = func_00101C30(pool, 0x10, e->kind);
        if (idx >= 0) {
            e->ids[0] = idx;
            r = &pool[e->ids[0]];
            if (func_00205440(&pos, mat, &scr, &depth)) {
                func_00101B40(r, e->life, 0);
                r->x = scr.x;
                r->y = scr.y;
                r->z = func_0017B340(scr.z);
                e->depth = depth;
            } else {
                e->ids[0] = -1;
            }
        } else {
            e->ids[0] = -1;
        }
        spl.n = 0;
        for (k = 0; k < e->n; k++) {
            if (e->ids[k] >= 0) {
                r = &pool[e->ids[k]];
                spl.x[spl.n] = r->x;
                spl.y[spl.n] = r->y;
                spl.z[spl.n] = 0.0f;
                if (spl.n != 0) {
                    dx = spl.x[spl.n - 1] - r->x;
                    dy = spl.y[spl.n - 1] - r->y;
                    if (func_001A6C60(dx * dx + dy * dy) > 32.0f) {
                        spl.n++;
                    }
                } else {
                    spl.n++;
                }
            }
        }
        if (spl.n < 3) {
            spl.pts[0].x = spl.x[0];
            spl.pts[0].y = spl.y[0];
            spl.pts[0].z = spl.z[0];
            m = 2;
        } else {
            func_00102550(&spl);
            m = (spl.n - 1) * 4;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->life < 8) {
            a = (f32)(u32)e->life * (f32)(u32)e->a / 8.0f;
        } else {
            a = (u32)e->a;
        }
        as = a / m;
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = pkt.v[1].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
        hw = e->width / (e->depth / 256.0f);
        for (k = 0; k < m - 1; k++) {
            if (k == 0) {
                func_00101EE0(&pkt, &tmpl.v[0], tex);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(spl.pts[k].x - hw);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(spl.pts[k].x + hw);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(spl.pts[k].y - hw);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(spl.pts[k].y + hw);
                pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (u32)(as * (f32)(m - k));
                func_002075F0((s32)&pkt, ot, 0);
            } else {
                func_00101EE0(&pkt, &tmpl.v[1], tex);
                pkt.v[0].a = pkt.v[2].a = (u32)(as * (f32)(m - k));
                pkt.v[1].a = pkt.v[3].a = (u32)(as * (f32)(m - k - 1));
                pkt.v[0].xyz.y = (u32)(scr.y - hw);
                pkt.v[2].xyz.y = (u32)(scr.y + hw);
                pkt.v[1].xyz.y = (u32)(spl.pts[k].y - hw);
                pkt.v[3].xyz.y = (u32)(spl.pts[k].y + hw);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = scr.x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)spl.pts[k].x;
                func_002075F0((s32)&pkt, ot, 0);
                pkt.v[0].xyz.x = (u32)(scr.x - hw);
                pkt.v[2].xyz.x = (u32)(scr.x + hw);
                pkt.v[1].xyz.x = (u32)(spl.pts[k].x - hw);
                pkt.v[3].xyz.x = (u32)(spl.pts[k].x + hw);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = scr.y;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)spl.pts[k].y;
                func_002075F0((s32)&pkt, ot, 0);
            }
            scr.x = (u32)spl.pts[k].x;
            scr.y = (u32)spl.pts[k].y;
        }
    }
    return 1;
}

#pragma optimization_level reset

/* OVL_WARM */

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b059:01E00E10, 941 insns, 11 copies: b024:01E02120 at -O1 (angle inline, step = 17.0f local, ABS macro): update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b059_01E00E10 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b059_01E00E10;

typedef struct Rib_b059_01E00E10 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 frame;
    u8 b5c;
    u8 div;
    u8 padE[2];
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    f32 rot[4];
} Rib_b059_01E00E10;

typedef struct Xyz_b059_01E00E10 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b059_01E00E10;

typedef struct Pk_b059_01E00E10 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b059_01E00E10 v[4];
    u64 pad60[3];
} Pk_b059_01E00E10;

static inline void b059_01E00E10_tag(Pk_b059_01E00E10 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 1
typedef struct W_tbl_func_01E04F80_b710 {
    Uvs_b059_01E00E10 v[4];
} W_tbl_func_01E04F80_b710;

static s32 func_01E04F80_b710(Rib_b059_01E00E10 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 step;
    f32 b;
    Rib_b059_01E00E10 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    s32 tex;
    u8 k;
    f32 w;
    f32 d;
    f32 a;
    f32 h0;
    s32 life;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E04F80_b710 D_01E07910_b710;
    W_tbl_func_01E04F80_b710 tbl_w = D_01E07910_b710;
    Uvs_b059_01E00E10 uvs;
    Pk_b059_01E00E10 pk;
    f32 depth[2];

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        if (p->flags & 4) {
            tex = func_00202BF0(5, p->idx);
        } else {
            tex = func_00202BF0(tbl_w.v[p->idx].kind, tbl_w.v[p->idx].tex);
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        func_00101BA0(p, p->pos);
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        k = p->k;
        step = 17.0f;
        ang = 0.0f;
        life = p->life - p->age;
        b059_01E00E10_tag((Pk_b059_01E00E10 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        if (p->flags & 4) {
            sel = p->frame;
            if (p->flags & 8) {
                sel = life & 7;
                if (life < 3) {
                    sel = life;
                }
                if (p->age < 4) {
                    sel = 7 - p->age;
                }
            }
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, sel, 0);
            func_00101D20(&pk, &uvs, tex);
        } else {
            func_00101D20(&pk, &tbl_w.v[p->idx], tex);
        }
        if (p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
        } else {
            pk.a = p->a;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                v.x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                v.y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                v.z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += step;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                v.x = a * b * func_001A6898(3.1415927f * ang / 180.0f);
                v.z = a * b * func_001A6A88(3.1415927f * ang / 180.0f);
                v.y = a * p->scale;
            }
            w = p->width + p->grow * (f32)life;
            if (p->div > 1) {
                d = p->scale / (f32)p->div;
                w = w / (1.0f + func_0020D0E0(&v.x) / d);
            }
            t[0].x = v.x * (f32)life;
            t[0].y = v.y * (f32)life;
            t[0].z = v.z * (f32)life;
            if (func_00205440(&t[0], m, &pk.v[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&pk.v[0]) == 0) {
                continue;
            }
            h0 = func_001018E0(w, depth[0]);
            if (p->flags & 2) {
                t[1].x = t[0].x + 4.0f * v.x;
                t[1].y = t[0].y + 4.0f * v.y;
                t[1].z = t[0].z + 4.0f * v.z;
                if (func_00205440(&t[1], m, &pk.v[2], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&pk.v[2]) == 0) {
                    continue;
                }
                h1 = func_001018E0(w, depth[1]);
                dy = ABS(pk.v[2].y - pk.v[0].y);
                dx = ABS(pk.v[2].x - pk.v[0].x);
                if (dy < dx) {
                    pk.v[1].x = pk.v[0].x;
                    pk.v[3].x = pk.v[2].x;
                    pk.v[1].y = (u32)(pk.v[0].y + h0);
                    pk.v[0].y = (u32)(pk.v[0].y - h0);
                    pk.v[3].y = (u32)(pk.v[2].y + h1);
                    pk.v[2].y = (u32)(pk.v[2].y - h1);
                } else {
                    pk.v[1].y = pk.v[0].y;
                    pk.v[3].y = pk.v[2].y;
                    pk.v[1].x = (u32)(pk.v[0].x + h0);
                    pk.v[0].x = (u32)(pk.v[0].x - h0);
                    pk.v[3].x = (u32)(pk.v[2].x + h1);
                    pk.v[2].x = (u32)(pk.v[2].x - h1);
                }
                pk.v[1].z = pk.v[0].z;
                pk.v[3].z = pk.v[2].z;
            } else {
                pk.v[1].x = (u32)(pk.v[0].x + h0);
                pk.v[1].y = (u32)(pk.v[0].y - h0);
                pk.v[2].x = (u32)(pk.v[0].x - h0);
                pk.v[2].y = (u32)(pk.v[0].y + h0);
                pk.v[3].x = (u32)(pk.v[0].x + h0);
                pk.v[3].y = (u32)(pk.v[0].y + h0);
                pk.v[0].x = (u32)(pk.v[0].x - h0);
                pk.v[0].y = (u32)(pk.v[0].y - h0);
                pk.v[1].z = pk.v[2].z = pk.v[3].z = pk.v[0].z;
            }
            pk.v[0].fog = pk.v[1].fog = pk.v[2].fog = pk.v[3].fog = 1;
            func_002075F0((s32)&pk, id, (u32)(depth[0]));
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b181:01E02D50, 346 insns (b198:01E05C30 at -O1): moves n trail emitters (0x7C bytes each) and drops trail particles into the
   emitter's pool: one at the head (flag 1) or four along a spline through the last three positions. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b181_01E02D50;

typedef struct {
    u8 r, g, b, a;
} C4_b181_01E02D50;

typedef struct {
    u8 pad00[4];
    u8 flags;
    u8 b5;
    u8 pad06[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 pad0E[2];
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    C4_b181_01E02D50 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 x48[0x10];
} Part_b181_01E02D50;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b181_01E02D50 *list;
    s32 w0C;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 pad17;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    C4_b181_01E02D50 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
} Trail_b181_01E02D50;

#pragma optimization_level 1

static s32 func_01E05E40_b710(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    Spline_b181_01E02D50 sp;
    Vec4f tmp;
    Trail_b181_01E02D50 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Trail_b181_01E02D50 *)((u8 *)e + 0x7C);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->max - 1) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        func_00101BA0(e, &e->pos);
        if (e->follow != 0) {
            e->pos.x += e->off.x;
            e->pos.y += e->off.y;
            e->pos.z += e->off.z;
        }
        if (e->flags & 1) {
            sp.out[0] = e->pos;
            sp.out[1] = e->prev;
            cnt = 1;
        } else {
            sp.n = 3;
            sp.x[0] = e->pos.x;
            sp.y[0] = e->pos.y;
            sp.z[0] = e->pos.z;
            sp.x[1] = e->prev.x;
            sp.y[1] = e->prev.y;
            sp.z[1] = e->prev.z;
            sp.x[2] = e->prev2.x;
            sp.y[2] = e->prev2.y;
            sp.z[2] = e->prev2.z;
            func_00102550(&sp);
            cnt = 4;
        }
        for (k = 0; k < cnt; k++) {
            idx = func_00101C30(e->list, 0x58, e->b10);
            if (idx >= 0) {
                func_00101AD0(&e->list[idx], e->b11, 0, 0xFF);
                e->list[idx].f14 = e->f18;
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 5;
                if (e->flags & 2) {
                    e->list[idx].flags |= 8;
                }
                e->list[idx].bC = e->b16;
                e->list[idx].b5 = 0;
                e->list[idx].b8 = e->b12;
                e->list[idx].f1C = e->f20;
                e->list[idx].f20 = e->f24;
                e->list[idx].b9 = func_0019A5C8() >> 4;
                e->list[idx].bA = e->b13;
                e->list[idx].bB = e->b14;
                e->list[idx].bD = e->b15;
                e->list[idx].w10 = e->w0C;
                e->list[idx].col = e->col;
                e->list[idx].pos = sp.out[k];
                func_00101940(&tmp, e->list[idx].x48);
            }
        }
        e->prev2 = e->prev;
        e->prev = e->pos;
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b710:01E063B0 (b710_vmln), 232 insns (-O1,p): b380:01E04980's slot spawner with b8 = 1, colour 0xB0 (alpha
   0xB0) and second colour 0x60/0x10/0x80 alpha 0x40 */

typedef struct {
    f32 x, y, z, w;
} V4_b710_01E063B0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 a0;
    f32 a1;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 col[4];
    u8 col2[4];
    V4_b710_01E063B0 pos;
    u8 pad3C[0x20];
} Slot_b710_01E063B0;

typedef struct {
    u8 pad0[4];
    s32 skel;
    u8 pad8[8];
    s32 joint;
    u8 pad14[0xDC];
    Slot_b710_01E063B0 slot[100];
} Scene_b710_01E063B0;

#pragma optimization_level 1

static void func_01E063B0_b710(Scene_b710_01E063B0 *g) {
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    V4_b710_01E063B0 p;
    s32 k;

    func_001F5620(g->skel, g->joint, &p);
    k = func_00101C30(g->slot, 0x5C, 0x64);
    if (k >= 0) {
        func_00101AD0(&g->slot[k], 0x18, 0, 0xFF);
        g->slot[k].b4 = 0;
        g->slot[k].b5 = 0;
        g->slot[k].b8 = 1;
        g->slot[k].b9 = 0;
        g->slot[k].bA = 0x10;
        g->slot[k].f1C = 6.0f;
        g->slot[k].col2[2] = 0x80;
        g->slot[k].col2[1] = 0x10;
        g->slot[k].col2[0] = 0x60;
        g->slot[k].col2[3] = 0x40;
        g->slot[k].col[2] = g->slot[k].col[1] = g->slot[k].col[0] = g->slot[k].col[3] = 0xB0;
        g->slot[k].pos = p;
        g->slot[k].f18 = 15.0f;
        g->slot[k].f14 = 12.0f;
        g->slot[k].a0 = 360.0f + (f32)((func_0019A5C8() >> 4) % 360 * 200 - 36000) / 100.0f;
        g->slot[k].a1 = 60.0f + g->slot[k].a0;
        g->slot[k].f20 = 1.0f;
    }
}
#pragma optimization_level reset

/* shape b710:01E06750 (b710), 1070 insns, 1 copy (-O1,p): b710 scene manager (-O1), b380:01E04D20's form: code -3/-2
   returns 8; code >= 0 clears the 0x8130 scene, takes both units, the camera, six joints, the wave (2, 0xC2) and the
   table; else counts the frame: 2 two red-eye streaks and the emitter, 82 the white fade and the trail, 110 the red
   fade, the core, the flare, the needle and the emitter, 200 ends; 65-81 vmln each frame, 20-55 a spark at joint 4,
   82-126 six gusts; frames 2-32 drive func_001F6D00/6CE0, else the wave; steps every effect; returns 6 from 82 to
   138, 1 at 72, 2 at 139 */

typedef struct {
    s32 a;
    s32 dir;
    u8 pad8[0xC];
} Cam_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 b5;
    u8 b6;
    u8 pad7[0xD];
    f32 f14;
    f32 f18;
    f32 f1C;
    Vec4f pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    f32 f50;
    u8 pad54[0xC];
} Emit_b710_01E06750;

typedef struct {
    s16 a;
    s16 b;
} Wv_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    Vec4f pos;
    u8 pad2C[0x10];
    f32 ox, oy, oz;
    u8 pad48[4];
} Flear_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 b, g, r;
    u8 padB;
    u8 b2, g2, r2, a;
    f32 len;
    f32 width;
    f32 angle;
    f32 spin;
    Vec4f pos;
    u8 pad30[0x20];
} Core_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    void *tbl;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c[4];
    u8 d[4];
    Vec4f pos;
    u8 pad38[0x20];
    s32 w58;
    s32 w5C;
    s32 w60;
    u8 pad64[4];
} Ndl_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[3];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 c[4];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 x;
    f32 y;
    f32 z;
    f32 f2C;
    f32 f30;
    f32 f34;
    u8 pad38[0xC];
} Gus_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 pad5[3];
    u8 c[3];
    u8 padB;
} Fade_b710_01E06750;

typedef struct {
    u8 life;
    u8 pad1[4];
    u8 on;
    u8 sel;
    u8 pad7;
    void *pool;
    s16 ids[9];
    u8 kind;
    u8 n;
    u8 texid;
    u8 sel0;
    u8 sel1;
    u8 maxseg;
    u8 pad24[4];
    f32 th;
    f32 width;
    f32 depth;
    u8 b, g, r, a;
    u8 pad38[0x10];
} Red_b710_01E06750;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    void *rib;
    s8 *table;
    u8 b10, b11, b12, b13;
    u8 b14;
    u8 pad15;
    u8 b16;
    u8 pad17;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    u8 c[4];
    u8 pad2C[0x10];
    Vec4f pos;
    Vec4f org;
    u8 pad5C[0x20];
} Trail_b710_01E06750;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[6];
    u8 pad24[8];
    Cam_b710_01E06750 cam;
    Emit_b710_01E06750 emit;
    Wv_b710_01E06750 wv;
    Flear_b710_01E06750 flear;
    u8 slot[100][0x5C];
    Core_b710_01E06750 core;
    Ndl_b710_01E06750 ndl;
    Gus_b710_01E06750 gus[200];
    Fade_b710_01E06750 fade;
    Red_b710_01E06750 red[2];
    u8 pool[0x200];
    Trail_b710_01E06750 trail;
    u8 rib[100][0x58];
    s8 tbl[0x100];
} Scene_b710_01E06750;

#pragma optimization_level 1

static s32 func_01E06750_b710(Scene_b710_01E06750 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6D00(u8);
    extern void func_001F6CE0(u8);
    s32 ot = func_00207500();
    Vec4f v;
    Vec4f w[3];
    s32 i;
    s32 k;

    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x8130);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 3; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 1, 1);
        g->m[1] = func_001F5560(g->unitA, 0x10, 0);
        g->m[2] = func_001F5560(g->unitA, 0x1B, 0);
        g->m[3] = func_001F5560(g->unitA, 0x1C, 0);
        g->m[4] = func_001F5560(g->unitA, 0x36, 0);
        g->m[5] = func_001F5560(g->unitA, 0x1A, 0);
        g->wv.a = 2;
        g->wv.b = 0xC2;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 2:
        for (k = 0; k < 2; k++) {
            func_00101AD0(&g->red[k], 0x70, 0, 0xFF);
            g->red[k].on = 1;
            if (k == 0) {
                g->red[k].sel0 = g->m[2];
                g->red[k].sel1 = g->m[3];
            } else {
                g->red[k].sel0 = g->m[3];
                g->red[k].sel1 = g->m[2];
            }
            g->red[k].pool = g->pool;
            g->red[k].kind = 0x20;
            g->red[k].n = 8;
            g->red[k].texid = 0;
            g->red[k].width = 40.0f;
            g->red[k].th = 0.5f;
            g->red[k].r = g->red[k].g = g->red[k].b = 0x80;
            g->red[k].a = 0x60;
            for (i = 0; i < g->red[k].n + 1; i++) {
                g->red[k].ids[i] = -1;
            }
            g->red[k].depth = -1.0f;
        }
        func_00101AD0(&g->emit, 0x70, 0, 0xFF);
        g->emit.b5 = 1;
        g->emit.b6 = g->m[5];
        g->emit.on = 1;
        g->emit.f14 = 1.9f;
        g->emit.f18 = 1.0f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 10.0f;
        g->emit.f50 = 2.0f;
        func_001F5F90(g->unitB, &g->emit.pos);
        break;
    case 0x52:
        func_00101AD0(&g->fade, 0x10, 0, 0xFF);
        g->fade.c[2] = g->fade.c[1] = g->fade.c[0] = 0xFF;
        g->fade.flags = 1;
        func_00101AD0(&g->trail, 0x20, 0, 0xFF);
        g->trail.b4 = 0;
        g->trail.b5 = 1;
        g->trail.b6 = g->m[1];
        g->trail.rib = g->rib;
        g->trail.b10 = 0x64;
        g->trail.b12 = 8;
        g->trail.b11 = 0x12;
        g->trail.b13 = 0;
        g->trail.b16 = 2;
        g->trail.b14 = 4;
        g->trail.f18 = 0.5f;
        g->trail.f1C = 0.5f;
        g->trail.f20 = 45.0f;
        g->trail.f24 = 0.5f;
        g->trail.table = g->tbl;
        g->trail.c[2] = g->trail.c[1] = g->trail.c[0] = g->trail.c[3] = 0x80;
        func_001F5620(g->unitA, g->m[0], &g->trail.pos);
        g->trail.org = g->trail.pos;
        break;
    case 0x6E:
        func_00101AD0(&g->fade, 0x10, 0, 0xFF);
        g->fade.c[2] = 0xFF;
        g->fade.c[1] = 0x20;
        g->fade.c[0] = 0;
        g->fade.flags = 0x82;
        g->core.b5 = 0;
        g->core.pos = v;
        func_00101AD0(&g->core, 0x20, 1, 0xFF);
        g->core.flags = 0x81;
        g->core.len = 3000.0f;
        g->core.width = 100.0f;
        g->core.r2 = g->core.g2 = g->core.b2 = 0x80;
        g->core.g = 0;
        g->core.r = 0;
        g->core.b = 0x40;
        g->core.a = 0xC0;
        g->core.spin = 0.0f;
        g->core.angle = 0.0f;
        func_00101AD0(&g->flear, 0x20, 0, 0xFF);
        g->flear.b5 = 0;
        g->flear.flags = 0x81;
        g->flear.segs = 9;
        g->flear.radius = 200.0f;
        g->flear.grow = 0.0f;
        g->flear.ir = g->flear.ig = g->flear.ib = g->flear.alpha = 0xD0;
        g->flear.r = 0x40;
        g->flear.g = 0x10;
        g->flear.b = 0x80;
        g->flear.ox = g->flear.oy = g->flear.oz = 0.0f;
        g->flear.pos = v;
        func_00101AD0(&g->ndl, 0x1E, 0, 0xFF);
        g->ndl.b4 = 5;
        g->ndl.f14 = 2.0f;
        g->ndl.f1C = 40.0f;
        g->ndl.b5 = 0;
        g->ndl.bA = 0;
        g->ndl.bB = 2;
        g->ndl.bC = 3;
        g->ndl.b8 = 0xA0;
        g->ndl.b9 = func_0019A5C8() >> 4;
        g->ndl.tbl = g->tbl;
        g->ndl.f18 = 1.0f;
        g->ndl.c[2] = g->ndl.c[1] = g->ndl.c[0] = g->ndl.d[2] = g->ndl.d[1] = g->ndl.d[0] = 0x80;
        g->ndl.c[3] = 0x20;
        g->ndl.d[3] = 0x80;
        g->ndl.pos = v;
        g->ndl.w58 = 0x40;
        g->ndl.w5C = 0x80;
        g->ndl.w60 = 0x100;
        func_00101AD0(&g->emit, 0x20, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.8f;
        g->emit.f18 = 1.8f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 4.0f;
        func_001F5F90(g->unitB, &g->emit.pos);
        break;
    case 0xC8:
        return 8;
    }
    if (g->t >= 0x41 && g->t < 0x52) {
        func_01E063B0_b710((Scene_b710_01E063B0 *)g);
    }
    if (g->t >= 0x14 && g->t < 0x38) {
        for (i = 0; i < 1; i++) {
            k = func_00101C30(g->gus, 0x44, 0xC8);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x1C, 0, 0xFF);
                g->gus[k].b4 = (func_0019A5C8() >> 4 & 3) << 4;
                g->gus[k].b8 = 1;
                g->gus[k].bA = 5;
                g->gus[k].bB = 1;
                g->gus[k].b9 = func_0019A5C8() >> 4 & 3;
                g->gus[k].c[2] = g->gus[k].c[1] = g->gus[k].c[0] = 0x80;
                g->gus[k].c[3] = (func_0019A5C8() >> 4 & 0x1F) + 0x60;
                g->gus[k].f10 = 50.0f;
                g->gus[k].f14 = 8.0f;
                g->gus[k].f1C = 0.0f;
                g->gus[k].f18 = 0.0f;
                func_001F5620(g->unitA, g->m[4], w);
                g->gus[k].x = w[0].x;
                g->gus[k].y = w[0].y;
                g->gus[k].z = w[0].z;
                g->gus[k].f2C = (f32)((func_0019A5C8() >> 4) % 30 - 15) / 100.0f;
                g->gus[k].f30 = (f32)((func_0019A5C8() >> 4) % 30 - 15) / 100.0f;
                g->gus[k].f34 = (f32)((func_0019A5C8() >> 4) % 30 - 15) / 100.0f;
            }
        }
    }
    if (g->t >= 0x52 && g->t < 0x7F) {
        for (i = 0; i < 6; i++) {
            k = func_00101C30(g->gus, 0x44, 0xC8);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x20, func_0019A5C8() >> 4 & 0xF, 0xFF);
                g->gus[k].b4 = 0;
                g->gus[k].b8 = 0;
                g->gus[k].bB = 2;
                g->gus[k].bA = 0;
                g->gus[k].b9 = 3;
                g->gus[k].c[2] = g->gus[k].c[1] = g->gus[k].c[0] = 0x80;
                g->gus[k].c[3] = 0x60;
                g->gus[k].f10 = 100.0f + (f32)((func_0019A5C8() >> 4) % 20 * 200 - 2000) / 100.0f;
                g->gus[k].f14 = 0.8f;
                g->gus[k].f18 = -0.06f;
                g->gus[k].f1C = 0.0f;
                g->gus[k].x = v.x;
                g->gus[k].y = v.y;
                g->gus[k].z = v.z;
                g->gus[k].f2C = (f32)((func_0019A5C8() >> 4) % 180 - 90) / 100.0f;
                g->gus[k].f30 = 0.4f + (f32)((func_0019A5C8() >> 4) % 180 - 90) / 100.0f;
                g->gus[k].f34 = (f32)((func_0019A5C8() >> 4) % 180 - 90) / 100.0f;
            }
        }
    }
    if (g->t >= 2 && g->t < 0x21) {
        func_001F6D00((g->t - 2) * 2);
        func_001F6CE0((g->t - 2) * 4);
    } else {
        func_001031C0(&g->wv, g->t);
    }
    func_01E00080_b710((Obj_b002_01E00080 *)&g->emit);
    func_01E00440_b710((Obj_b241_01E00440 *)&g->flear, ot, 1);
    func_01E01160_b710(g->slot, ot, 100);
    func_01E01B60_b710(&g->core, ot, 1);
    func_01E02630_b710((Ray_b011_01E04380 *)&g->ndl, ot, 1);
    func_01E03360_b710(g->gus, ot, 0xC8);
    func_01E03E40_b710((s32)&g->fade, ot);
    func_01E04380_b710(g->red, ot, 2);
    func_01E05E40_b710(&g->trail, ot, 1);
    func_01E04F80_b710((Rib_b059_01E00E10 *)g->rib, ot, 100);
    if (g->t >= 0x52 && g->t < 0x8B) {
        return 6;
    }
    switch (g->t) {
    case 0x48:
        return 1;
    case 0x8B:
        return 2;
    }
    return 0;
}

#pragma optimization_level reset
