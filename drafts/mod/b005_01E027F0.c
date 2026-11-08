#include "common.h"

/* shape b005:01E027F0 (ShFx_RingTX), 461 insns, 1 copy (-O3,p): b715:01E003A0 (ShFx_RingTX) at -O3; 445/461: the
   0xFFFFFE z-chain temps land in a2/a3 where the original has a1/a2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b005_01E027F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b005_01E027F0 xyz;
} Vtx_b005_01E027F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b005_01E027F0 v[4];
    u8 tail[0x20];
} Pkt_b005_01E027F0;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b005_01E027F0;

typedef struct {
    u8 b, g, r, a;
} Col_b005_01E027F0;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 texid;
    u8 sub;
    u8 bA;
    u8 bB;
    u8 mode;
    u8 padD[3];
    f32 radius[2];
    f32 dradius[2];
    f32 scale;
    Col_b005_01E027F0 c0;
    Col_b005_01E027F0 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b005_01E027F0;

#pragma optimization_level 3

static s32 func_01E027F0_b005(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    f32 depth[4];
    Tex_b005_01E027F0 td;
    Pkt_b005_01E027F0 pkt;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b005_01E027F0 *e;
    s32 i;
    s32 tex;
    s32 nseg;
    s32 k;
    s32 r;
    f32 step;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texid);
        e->radius[0] += e->dradius[0];
        e->radius[1] += e->dradius[1];
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        if (e->seg > 36) {
            nseg = 36;
        } else {
            nseg = e->seg;
        }
        step = 360.0f / nseg;
        for (r = 0; r < 2; r++) {
            for (k = 0; k < nseg; k++) {
                ring[r][k].x = e->radius[r] * func_001A6898(3.1415927f * (step * k) / 180.0f);
                ring[r][k].z = e->radius[r] * func_001A6A88(3.1415927f * (step * k) / 180.0f);
                ring[r][k].y = 0.0f;
            }
        }
        ring[0][nseg] = ring[0][0];
        ring[1][nseg] = ring[1][0];
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->pad = 0;
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
            td.u = td.u + ((td.w - td.u) >> 1);
            td.w = td.u + 1;
        default:
            func_00208CB0(&pkt, 0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            break;
        }
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
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
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}
#pragma optimization_level reset
