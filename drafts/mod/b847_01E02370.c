#include "common.h"

/* shape b847:01E02370 (IWMagicKPoint1), 624 insns, 1 copy (-O3,p): a two-edge ribbon between the position histories a
   and b along the module spline (b847:01E00E60's inline, type 0), four sub-steps per segment, the first segment from
   control points {p0, p0, p1, p2}; alpha falling by col.a/(2n) per quad, no depth sort. HARD at -O3:
   code matches, but the original's spill area is 0x10 bigger (floats at 0xDC.., target 0x108, n-1 0x110, locals from
   0x120) */

typedef struct {
    f32 x, y, z, w;
} Vec_b847_01E02370;

typedef struct {
    u8 r, g, b, a;
} Col_b847_01E02370;

typedef struct {
    u8 hdr[0x10];
    u64 v[12];
    u8 tail[0x20];
} Pkt_b847_01E02370;

typedef struct {
    u8 pad00[6];
    s16 count;
    u8 pad08[0x58];
    Col_b847_01E02370 col;
} Obj_b847_01E02370;

static inline Vec_b847_01E02370 spline_b847_01E02370(Vec_b847_01E02370 *p, s32 type, f32 t) {
    Vec_b847_01E02370 r;
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
static void func_01E02370_b847(s32 unused, Obj_b847_01E02370 *o, Vec_b847_01E02370 *a, Vec_b847_01E02370 *b) {
    extern s32 func_00207500(void);
    extern void func_001092E0(void *, s32);
    extern void func_001094F0(void *);
    extern void func_00107990(void *, void *, s32);
    extern void func_00109A70(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 i;
    s32 j;
    Pkt_b847_01E02370 *p;
    f32 depth[4];
    Vec_b847_01E02370 q[4];
    Vec_b847_01E02370 va[2];
    Vec_b847_01E02370 vb[2];
    Vec_b847_01E02370 ca[4];
    Vec_b847_01E02370 cb[4];
    Col_b847_01E02370 col;
    Pkt_b847_01E02370 pkt __attribute__((aligned(8)));
    s32 target;
    s16 n;
    s32 x;
    f32 t;

    target = func_00207500();
    p = &pkt;
    n = o->count;
    func_001092E0(p, 0);
    func_001094F0(p);
    col = o->col;
    ca[0] = a[0];
    ca[1] = a[0];
    ca[2] = a[1];
    ca[3] = a[2];
    cb[0] = b[0];
    cb[1] = b[0];
    cb[2] = b[1];
    cb[3] = b[2];
    for (i = 0; i < n - 1; i++) {
        t = 0.0f;
        for (j = 0; j < 4; j++) {
            if (i != 0) {
                va[0] = spline_b847_01E02370(&a[i - 1], 0, t);
                vb[0] = spline_b847_01E02370(&b[i - 1], 0, t);
                t += 0.25f;
                va[1] = spline_b847_01E02370(&a[i - 1], 0, t);
                vb[1] = spline_b847_01E02370(&b[i - 1], 0, t);
            } else {
                va[0] = spline_b847_01E02370(ca, 0, t);
                vb[0] = spline_b847_01E02370(cb, 0, t);
                t += 0.25f;
                va[1] = spline_b847_01E02370(ca, 0, t);
                vb[1] = spline_b847_01E02370(cb, 0, t);
            }
            func_00107990(p, &col, 1);
            x = col.a - (s16)(o->col.a / (n * 2));
            if (x <= 0) {
                col.a = 0;
            } else {
                col.a = x;
            }
            func_00107990(p, &col, 2);
            func_00109A70(&q[0], &va[0]);
            func_00109A70(&q[1], &va[1]);
            func_00109A70(&q[2], &vb[0]);
            func_00109A70(&q[3], &vb[1]);
            if (func_00205630(q, 0x70000000, 0, p, depth) != 0) {
                func_002075F0(p, target, 0);
            }
        }
    }
}
#pragma optimization_level reset
