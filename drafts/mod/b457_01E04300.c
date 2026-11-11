#include "common.h"

/* shape b457:01E04300 (ShFx_DomeRing), 514 insns, 3 copies (-O3,p): n dome-ring emitters (0x5C bytes each): an inner
   and an outer circle of up to 36 points, offset by a tilt (radius - / + tilt*sin(ang), heights +/- tilt*cos(ang)),
   joined into textured quads; alpha fades by age (flags 8/0x10); z from a tracked object plus a per-emitter step */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b457_01E04300;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b457_01E04300 xyz;
} Vtx_b457_01E04300;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b457_01E04300 v[4];
    u8 tail[0x20];
} Pkt_b457_01E04300;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b457_01E04300;

typedef struct {
    u8 b, g, r, a;
} Col_b457_01E04300;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 texid;
    u8 sub;
    u8 bA;
    u8 bB;
    u8 mode;
    u8 obj;
    u8 zstep;
    u8 padF;
    f32 radius;
    f32 dradius;
    f32 tilt;
    f32 ang;
    f32 scale;
    Col_b457_01E04300 c0;
    Col_b457_01E04300 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b457_01E04300;

static inline f32 rad_b457_01E04300(f32 d) { return 3.1415927f * d / 180.0f; }
#pragma optimization_level 3

static s32 func_01E04300_b457(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    extern void func_001F53C0(s32, s32, void *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    Vec4f pos;
    f32 depth[4];
    Tex_b457_01E04300 td;
    Pkt_b457_01E04300 pkt __attribute__((aligned(8)));
    Xyz_b457_01E04300 xy;
    f32 z;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b457_01E04300 *e;
    s32 i;
    s32 tex;
    s32 k;
    s32 r;
    s32 nseg;
    s32 d;
    s32 h;
    f32 step;
    f32 hx;
    f32 hy;

    e = arg0;
    func_0020EB40(mat);
    if (e->mode & 0x20) {
        z = 4294967040.0f;
    } else {
        func_001F53C0(1, e->obj, &pos);
        if (func_00205440(&pos, mat, &xy, &z) == 0) {
            z = 0.0f;
        }
    }
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texid);
        e->radius += e->dradius;
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        if (e->seg > 36) {
            nseg = 36;
        } else {
            nseg = e->seg;
        }
        step = 360.0f / nseg;
        hx = e->tilt * func_001A6898(rad_b457_01E04300(e->ang)); hy = e->tilt * func_001A6A88(rad_b457_01E04300(e->ang));
        for (r = 0; r < 2; r++) {
            for (k = 0; k < nseg; k++) {
                if (r == 0) {
                    ring[r][k].x = (e->radius - hx) * func_001A6898(rad_b457_01E04300(step * k));
                    ring[r][k].z = (e->radius - hx) * func_001A6A88(rad_b457_01E04300(step * k));
                    ring[r][k].y = hy;
                } else {
                    ring[r][k].x = (e->radius + hx) * func_001A6898(rad_b457_01E04300(step * k));
                    ring[r][k].z = (e->radius + hx) * func_001A6A88(rad_b457_01E04300(step * k));
                    ring[r][k].y = -hy;
                }
            }
        }
        ring[0][nseg] = ring[0][0];
        ring[1][nseg] = ring[1][0];
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b457_01E04300 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b457_01E04300 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b457_01E04300 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b457_01E04300 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        td.b5 = e->sub;
        func_001020B0(&td, e->bB, e->bA);
        func_00102210(e->bA, &sw, &sh);
        switch (e->mode & 3) {
        case 1:
            func_00208CB0(&pkt, 0);
            sw *= e->scale;
            break;
        case 2:
            {
                s32 u;
                s32 hh = (td.w - (u = td.u)) >> 1;
                td.u = u + hh - 1;
                td.w = td.w - hh + 1;
            }
        default:
            func_00208CB0(&pkt, 0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            break;
        }
        pkt.v[0].a = pkt.v[1].a = e->c0.a;
        pkt.v[2].a = pkt.v[3].a = e->c1.a;
        d = e->max - e->life;
        if ((e->mode & 8) && d < 31) {
            pkt.v[0].a = pkt.v[1].a = d * (e->c0.a >> 5);
            pkt.v[2].a = pkt.v[3].a = d * (e->c1.a >> 5);
        }
        if ((e->mode & 0x10) && e->life < 31) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 5);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 5);
        }
        for (k = 0; k < nseg; k++) {
            if (func_00205440(&ring[0][k], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                func_00205440(&ring[0][k + 1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                func_00205440(&ring[1][k], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                func_00205440(&ring[1][k + 1], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                pkt.v[0].q = 1.0f / depth[0];
                pkt.v[1].q = 1.0f / depth[1];
                pkt.v[2].q = 1.0f / depth[2];
                pkt.v[3].q = 1.0f / depth[3];
                pkt.v[0].s = td.u / sw / depth[0];
                pkt.v[0].t = td.v / sh / depth[0];
                pkt.v[1].s = td.w / sw / depth[1];
                pkt.v[1].t = td.v / sh / depth[1];
                pkt.v[2].s = td.u / sw / depth[2];
                pkt.v[2].t = td.h / sh / depth[2];
                pkt.v[3].s = td.w / sw / depth[3];
                pkt.v[3].t = td.h / sh / depth[3];
                func_00101C80(&td, bl);
                func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                func_00208700(&pkt, (void *)tex, 1);
                func_002075F0((s32)&pkt, ot, (u32)(z + (i + 1) * e->zstep));
            }
        }
    }
    return 1;
}
#pragma optimization_level reset
