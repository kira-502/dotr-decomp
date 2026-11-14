#include "common.h"

/* shape b073:01E03E70 (B073PAINT_RAIN20), 646 insns, 1 copy (-O3,p): B073PAINT_RAIN21's ribbon (b073:01E04890) with
   the alpha stepping down per quad as in b756:01E05530, 4 quads per segment, built at -O3. HARD: code identical
   except the frame: the original has four unused spill slots (0xD0..0xD8 below the hoisted spline weights, 0x10C
   between ot and n - 1), so every stack offset is 0x10 off (514/646) */

typedef struct {
    f32 x, y, z, w;
} Vec_b073_01E03E70;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b073_01E03E70;

typedef struct {
    Rgbaq_b073_01E03E70 c;
    u64 xyz;
} Vtx_b073_01E03E70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b073_01E03E70 v[4];
    u8 tail[0x40];
} Pkt_b073_01E03E70;

typedef struct {
    u8 r, g, b, a;
} C4_b073_01E03E70;

typedef struct {
    u8 pad00[6];
    s16 n;
    u8 pad08[0x20];
    C4_b073_01E03E70 col;
} Rib_b073_01E03E70;

static inline Vec_b073_01E03E70 spline_b073_01E03E70(Vec_b073_01E03E70 *p, s32 type, f32 t) {
    Vec_b073_01E03E70 r;
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
static void func_01E03E70_b073(void *o, Rib_b073_01E03E70 *s, Vec_b073_01E03E70 *pa, Vec_b073_01E03E70 *pb) {
    extern s32 func_00207500(void);
    extern Rgbaq_b073_01E03E70 func_00107740(void *);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    Vec_b073_01E03E70 quad[4];
    Vec_b073_01E03E70 A[2];
    Vec_b073_01E03E70 B[2];
    Vec_b073_01E03E70 a4[4];
    Vec_b073_01E03E70 b4[4];
    Pkt_b073_01E03E70 pkt __attribute__((aligned(8)));
    C4_b073_01E03E70 c;
    s32 k;
    s32 j;
    s16 n;
    s32 x;
    s32 ot;
    Pkt_b073_01E03E70 *p;
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
    for (k = 0; k < n - 1; k++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            p->v[0].c = func_00107740(&c);
            p->v[2].c = func_00107740(&c);
            x = c.a - (s16)(s->col.a / (n * 2));
            if (x > 0) {
                c.a = x;
            } else {
                c.a = 0;
            }
            p->v[1].c = func_00107740(&c);
            p->v[3].c = func_00107740(&c);
            if (k != 0) {
                A[0] = spline_b073_01E03E70(&pa[k - 1], 0, t);
                B[0] = spline_b073_01E03E70(&pb[k - 1], 0, t);
                t += 0.25f;
                A[1] = spline_b073_01E03E70(&pa[k - 1], 0, t);
                B[1] = spline_b073_01E03E70(&pb[k - 1], 0, t);
            } else {
                A[0] = spline_b073_01E03E70(a4, 0, t);
                B[0] = spline_b073_01E03E70(b4, 0, t);
                t += 0.25f;
                A[1] = spline_b073_01E03E70(a4, 0, t);
                B[1] = spline_b073_01E03E70(b4, 0, t);
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
