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

static void func_01E00080_b025(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b015:01E008F0 (LkPrim_ModelShot2), 422 insns, 7 copies (-O3,p): a 2x2 sprite light shot around the
   model's screen point, its texture window stretched over count steps by the point's offset over 640/448;
   q.y read through the u16 local py first (puts q.x/q.y in the original's temp registers) */

typedef struct {
    f32 x, y, z, w;
} Vec_b015_01E008F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b015_01E008F0;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b015_01E008F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_b015_01E008F0 st0;
    Xyz_b015_01E008F0 p0;
    Uv_b015_01E008F0 st1;
    Xyz_b015_01E008F0 p1;
    u8 pad50[8];
    u64 t58;
    u64 t60;
    u8 pad68[8];
} Pkt_b015_01E008F0;

typedef struct {
    u8 pad00[0x30];
    f32 m[16];
} Cam_b015_01E008F0;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 scale;
    s16 count;
    s16 model;
} Shot_b015_01E008F0;

#pragma optimization_level 3
static inline void b015_01E008F0_tag(Pkt_b015_01E008F0 *p, s32 tag, s32 count, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E00120_b025(Shot_b015_01E008F0 *o, Vec_b015_01E008F0 *pos) {
    extern s32 func_00207F60(void);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208460(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern f32 func_001F5860(s32);
    extern u64 func_00205D10(void *, f32);
    extern f32 func_00205DF0(void *, f32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    s32 h;
    s32 j;
    s32 i;
    u16 py;
    u16 y;
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    u16 x;
    s32 k;
    s16 x0;
    s16 y0;
    f32 ax;
    f32 bx;
    f32 ay;
    f32 by;
    Cam_b015_01E008F0 cam;
    Pkt_b015_01E008F0 pkt __attribute__((aligned(8)));
    Xyz_b015_01E008F0 q;
    f32 dep;

    h = func_00207F60();
    func_00103890(&cam);
    func_001038D0(&cam);
    if (func_00205440(pos, cam.m, &q, &dep) == 0) {
        return -1;
    }
    py = q.y;
    x0 = (q.x >> 4) - 0x6C0;
    y0 = (py >> 4) - 0x720;
    ax = x0 / 640.0f;
    bx = 1.0f - ax;
    ay = y0 / 448.0f;
    by = 1.0f - ay;
    ax *= o->scale;
    bx *= o->scale;
    ay *= 0.7f * o->scale;
    by *= 0.7f * o->scale;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = o->r;
    pkt.g = o->g;
    pkt.b = o->b;
    pkt.a = o->a;
    pkt.q = 1.0f;
    func_00208460();
    func_001F7060(o->model, 0, &pkt.t58, &pkt.t60);
    func_00208460();
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->count |= 0x800;
    for (i = 0; i < o->count; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                x = k * 640 + 0x6C0;
                y = j * 448 + 0x720;
                u0 = ((s32)ax * i) << 4;
                v0 = ((s32)ay * i) << 4;
                u1 = (640 - (s32)bx * i) << 4;
                v1 = (448 - (s32)by * i) << 4;
                py = (y << 4) - 8;
                pkt.p0.x = q.x;
                pkt.p0.y = q.y;
                pkt.p0.f = 0;
                pkt.p1.x = (x << 4) - 8;
                pkt.p1.y = py;
                pkt.p1.f = 0;
                ((Uv_b015_01E008F0 *)(s32)&pkt.st0)->s = x0 << 4;
                ((Uv_b015_01E008F0 *)(s32)&pkt.st0)->t = y0 << 4;
                if (j == 0) {
                    if (k == 0) {
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u0;
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v0;
                    } else {
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u1;
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v0;
                    }
                } else if (k == 0) {
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u0;
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v1;
                } else {
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u1;
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v1;
                }
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.p0.z = pkt.p1.z = 0xFFFFFF;
                    func_002075F0(&pkt, 0, 0);
                } else {
                    pkt.p0.z = pkt.p1.z = func_00205D10(pos, -func_001F5860(o->model));
                    func_002075F0(&pkt, 0, (u32)func_00205DF0(pos, -func_001F5860(o->model)));
                }
            }
        }
    }
    func_00207FD0(h, func_00207500(), 0);
    return 0;
}
#pragma optimization_level reset

/* shape b025:01E007C0, 84 insns, 13 copies: pushes new head points into an object's two 8-entry trails (mode != 0), or
   keeps only the last two and lets func_001036E0 fill the middle point (mode 0) */

typedef struct {
    u8 pad0[0xE];
    s16 mode;
    Vec4f a[8];
    Vec4f b[8];
} Trail_b025_01E007C0;

static s32 func_01E007C0_b025(Trail_b025_01E007C0 *o, Vec4f *p1, Vec4f *p2) {
    extern void func_001036E0(void *, void *, void *);
    s32 i;

    if (o->mode != 0) {
        for (i = 6; i > -1; i--) {
            o->a[i + 1] = o->a[i];
            o->b[i + 1] = o->b[i];
            if (i == 0) {
                o->a[i].x = p1->x;
                o->a[i].y = p1->y;
                o->a[i].z = p1->z;
                o->b[i].x = p2->x;
                o->b[i].y = p2->y;
                o->b[i].z = p2->z;
            }
        }
    } else {
        o->a[2].x = o->a[0].x;
        o->a[2].y = o->a[0].y;
        o->a[2].z = o->a[0].z;
        o->a[0].x = p1->x;
        o->a[0].y = p1->y;
        o->a[0].z = p1->z;
        func_001036E0(&o->a[0], &o->a[2], &o->a[1]);
        o->b[2].x = o->b[0].x;
        o->b[2].y = o->b[0].y;
        o->b[2].z = o->b[0].z;
        o->b[0].x = p2->x;
        o->b[0].y = p2->y;
        o->b[0].z = p2->z;
        func_001036E0(&o->b[0], &o->b[2], &o->b[1]);
    }
    return 0;
}

/* shape b025:01E00910 (LkPrim_SortSwordtail), 509 insns, 13 copies: splines the two 8-point trails (o->len + 3
   points) into (len + 2) * 4 points each, then per segment draws two quads, mid(p1,p2)[i] / [i+1] to p1 and to p2,
   alpha fading along the strip; grows len up to max */

typedef struct {
    u16 c : 14;
    u16 p : 2;
} Tc_b025_01E00910;

typedef struct {
    Tc_b025_01E00910 u;
    Tc_b025_01E00910 v;
    s32 pad;
} Uv_b025_01E00910;

typedef union {
    Uv_b025_01E00910 uv;
    struct {
        f32 s, t;
    } st;
} Tex_b025_01E00910;

typedef struct {
    u16 x, y;
    u32 z;
} Xyz_b025_01E00910;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Tex_b025_01E00910 tc;
    Xyz_b025_01E00910 xyz;
} Vtx_b025_01E00910;

typedef struct {
    u16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b025_01E00910 v[4];
    u8 tail[0x20];
} Pkt_b025_01E00910;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spl_b025_01E00910;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 col;
    s16 max;
    s16 len;
    Vec4f a[8];
    Vec4f b[8];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Vec4f *p1;
    Vec4f *p2;
} Obj_b025_01E00910;

typedef struct {
    u8 pad[0x30];
    f32 m[16];
} Cam_b025_01E00910;

#define UV(k) ((Uv_b025_01E00910 *)(s32)&pkt.v[k].tc)

static s32 func_01E00910_b025(Obj_b025_01E00910 *o, Cam_b025_01E00910 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001036E0(void *, void *, void *);
    Spl_b025_01E00910 spl;
    Vec4f t[2];
    f32 d[4];
    Pkt_b025_01E00910 pkt;
    s32 old;
    s32 n;
    s32 step;
    s32 i;

    old = func_00207F60();
    n = (o->len + 2) * 4;
    step = o->col.a / n;
    spl.n = o->len + 3;
    for (i = 0; i < o->len + 3; i++) {
        spl.x[i] = o->a[i].x;
        spl.y[i] = o->a[i].y;
        spl.z[i] = o->a[i].z;
    }
    func_00102550(&spl);
    for (i = 0; i < n; i++) {
        o->p1[i].x = spl.pts[i].x;
        o->p1[i].y = spl.pts[i].y;
        o->p1[i].z = spl.pts[i].z;
    }
    for (i = 0; i < o->len + 3; i++) {
        spl.x[i] = o->b[i].x;
        spl.y[i] = o->b[i].y;
        spl.z[i] = o->b[i].z;
    }
    func_00102550(&spl);
    for (i = 0; i < n; i++) {
        o->p2[i].x = spl.pts[i].x;
        o->p2[i].y = spl.pts[i].y;
        o->p2[i].z = spl.pts[i].z;
    }
    ((Pkt_b025_01E00910 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b025_01E00910 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b025_01E00910 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b025_01E00910 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_01E00080_b025((Vtx_b000_01E00100 *)&pkt, &o->col);
    if (func_00104520(o->flags, 0) != 0) {
        ((Pkt_b025_01E00910 *)(s32)&pkt)->count |= 0x800;
        UV(0)->u.c = o->r.i.u * 16;
        UV(0)->v.c = o->r.i.v * 16;
        UV(1)->u.c = o->r.i.u * 16;
        UV(1)->v.c = (o->r.i.v + o->r.i.h - 1) * 16;
        UV(2)->u.c = (o->r.i.u + o->r.i.w - 1) * 16;
        UV(2)->v.c = o->r.i.v * 16;
        UV(3)->u.c = (o->r.i.u + o->r.i.w - 1) * 16;
        UV(3)->v.c = (o->r.i.v + o->r.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = o->r.f.s;
        pkt.v[0].tc.st.t = o->r.f.t;
        pkt.v[1].tc.st.s = o->r.f.s;
        pkt.v[1].tc.st.t = o->r.f.t + o->r.f.h;
        pkt.v[2].tc.st.s = o->r.f.s + o->r.f.w;
        pkt.v[2].tc.st.t = o->r.f.t;
        pkt.v[3].tc.st.s = o->r.f.s + o->r.f.w;
        pkt.v[3].tc.st.t = o->r.f.t + o->r.f.h;
    }
    for (i = 0; i < n - 1; i++) {
        if (i == 0) {
            pkt.v[0].a = 0;
        } else {
            pkt.v[0].a = o->col.a - (u8)(i * step);
        }
        if (i == n - 2) {
            pkt.v[1].a = 0;
        } else {
            pkt.v[1].a = o->col.a - (step + (u8)(i * step));
        }
        pkt.v[2].a = pkt.v[3].a = 0;
        func_001036E0(&o->p1[i], &o->p2[i], &t[0]);
        func_001036E0(&o->p1[i + 1], &o->p2[i + 1], &t[1]);
        if (func_00205440(&t[0], cam->m, &pkt.v[0].xyz, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        if (func_00205440(&t[1], cam->m, &pkt.v[1].xyz, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00205440(&o->p1[i], cam->m, &pkt.v[2].xyz, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        if (func_00205440(&o->p1[i + 1], cam->m, &pkt.v[3].xyz, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_00208700(&pkt, o->texture, 0);
            func_002075F0(&pkt, 0, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
        if (func_00205440(&t[0], cam->m, &pkt.v[0].xyz, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        if (func_00205440(&t[1], cam->m, &pkt.v[1].xyz, &d[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00205440(&o->p2[i], cam->m, &pkt.v[2].xyz, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        if (func_00205440(&o->p2[i + 1], cam->m, &pkt.v[3].xyz, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_00208700(&pkt, o->texture, 0);
            func_002075F0(&pkt, 0, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
    }
    func_00207FD0(old, (s32)func_00207500(), 0);
    if (o->len + 3 < o->max) {
        o->len++;
    }
    return 0;
}

/* shape b013:01E010C0, 376 insns, 42 copies: 60-point spark sprite draw (sibling of b001:01E03860).
   Calls the module colour helper at 0x1E00100 (shape b000:01E00100) as a plain extern: nothing is kept
   in a scratch register across that call, so it need not be static in this file. */

typedef struct {
    u8 b, g, r, a;
} Src_b013_01E010C0;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
} Uv_b013_01E010C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        Uv_b013_01E010C0 i;
        f32 f[2];
    } st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b013_01E010C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b013_01E010C0 v[4];
    u8 tail[0x20];
} Pkt_b013_01E010C0;

typedef struct {
    f32 x, y, z, w;
} Vec_b013_01E010C0;

typedef struct {
    f32 x, y, z;
} Pt_b013_01E010C0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b013_01E010C0 color;
    f32 r;
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 u, v, w, h;
        } f;
    } uv;
    Pt_b013_01E010C0 pts[60];
} Spark_b013_01E010C0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b013_01E010C0;

extern void b025_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E01110_b025(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00103620(void *, s32);
    extern void func_001036A0(void *, s32);
    f32 depth[4];
    Vec_b013_01E010C0 v;
    Pkt_b013_01E010C0 pkt;
    s32 i;

    ((Pkt_b013_01E010C0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b013_01E010C0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b013_01E010C0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b013_01E010C0 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    b025_01E00080(&pkt, &sp->color);
    if (func_00104520(sp->flags, 0) != 0) {
        ((Pkt_b013_01E010C0 *)(s32)&pkt)->count |= 0x800;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[0].st)->s = sp->uv.i.u << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[0].st)->t = sp->uv.i.v << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[1].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[1].st)->t = sp->uv.i.v << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[2].st)->s = sp->uv.i.u << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[2].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[3].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b013_01E010C0 *)(s32)&pkt.v[3].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
    } else {
        pkt.v[0].st.f[0] = sp->uv.f.u;
        pkt.v[0].st.f[1] = sp->uv.f.v;
        pkt.v[1].st.f[0] = sp->uv.f.u + sp->uv.f.w;
        pkt.v[1].st.f[1] = sp->uv.f.v;
        pkt.v[2].st.f[0] = sp->uv.f.u;
        pkt.v[2].st.f[1] = sp->uv.f.v + sp->uv.f.h;
        pkt.v[3].st.f[0] = sp->uv.f.u + sp->uv.f.w;
        pkt.v[3].st.f[1] = sp->uv.f.v + sp->uv.f.h;
    }
    for (i = 0; i < 60; i++) {
        if (func_00104520(sp->flags, 0x1F) != 0) {
            func_00103620(&sp->pts[i], mode);
        } else {
            func_001036A0(&sp->pts[i], mode);
        }
        v.x = sp->pts[i].x - sp->r;
        v.y = sp->pts[i].y + sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            sp->flags |= 0x100000;
        }
        v.x = sp->pts[i].x + sp->r;
        v.y = sp->pts[i].y + sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            sp->flags |= 0x200000;
        }
        v.x = sp->pts[i].x - sp->r;
        v.y = sp->pts[i].y - sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            sp->flags |= 0x400000;
        }
        v.x = sp->pts[i].x + sp->r;
        v.y = sp->pts[i].y - sp->r;
        v.z = sp->pts[i].z;
        if (func_00205440(&v, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            sp->flags |= 0x800000;
        }
        func_00208700(&pkt, sp->texture, 0);
        if (func_00104520(sp->flags, 0x14) != 0 && func_00104520(sp->flags, 0x15) != 0 &&
            func_00104520(sp->flags, 0x16) != 0 && func_00104520(sp->flags, 0x17) != 0) {
            if (func_00104520(sp->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        sp->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b025:01E016F0, 509 insns, 17 copies: draws a cloud of sprite quads whose offsets follow a wave table: per point,
   amplitude from |tab[i]| / 10, x/y/z from tab[k], tab[k+1], tab[k+2] (or their absolute values, or 0, per
   flag bits), scaled by the frame count; depth-sorted unless flag 0x13 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b025_01E016F0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b025_01E016F0;

typedef struct {
    u64 uv;
    Xyz_b025_01E016F0 p;
} Vtx_b025_01E016F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b025_01E016F0 v[4];
    u8 tail[0x20];
} Pk_b025_01E016F0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b8, b9, bA, bB;
    s8 *tab;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 size;
    f32 amp;
    s16 count;
    s16 frame;
    u8 phase;
} Wave_b025_01E016F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b025_01E016F0;

static s32 func_01E016F0_b025(s32 obj, Wave_b025_01E016F0 *w, Cam_b025_01E016F0 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00195070(s32);
    Vec4f pos;
    f32 depth[4];
    Pk_b025_01E016F0 pk __attribute__((aligned(8)));
    s32 i;
    s32 k;
    f32 amp;
    f32 x;
    f32 y;
    f32 z;

    if (w->frame > 0) {
        ((Pk_b025_01E016F0 *)(s32)&pk)->flags = 0x24;
        ((Pk_b025_01E016F0 *)(s32)&pk)->size = 9;
        ((Pk_b025_01E016F0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b025_01E016F0 *)(s32)&pk)->pad4 = 0;
        if (func_00104520(w->flags, 0xC) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
        } else if (func_00104520(w->flags, 0xB) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
        } else if (func_00104520(w->flags, 0xA) != 0) {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
        } else {
            func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
        }
        pk.r = w->bA;
        pk.g = w->b9;
        pk.b = w->b8;
        pk.a = w->bB;
        pk.q = 1.0f;
        ((Pk_b025_01E016F0 *)(s32)&pk)->flags |= 0x800;
        ((UV_b025_01E016F0 *)(s32)&pk.v[0].uv)->u = w->u * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[0].uv)->v = w->v * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[1].uv)->u = w->u * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[1].uv)->v = (w->v + w->h - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[2].uv)->u = (w->u + w->w - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[2].uv)->v = w->v * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[3].uv)->u = (w->u + w->w - 1) * 16;
        ((UV_b025_01E016F0 *)(s32)&pk.v[3].uv)->v = (w->v + w->h - 1) * 16;
        for (i = 0; i < w->count; i++) {
            k = (u8)(w->phase + i);
            amp = w->amp * (0.1f * func_00195070(w->tab[i]));
            if (w->flags & 0x08000000) {
                x = 0.0f;
            } else if (w->flags & 0x01000000) {
                x = w->frame * (amp * func_00195070(w->tab[(u8)k]));
            } else {
                x = w->frame * (amp * w->tab[(u8)k]);
            }
            if (w->flags & 0x10000000) {
                y = 0.0f;
            } else if (w->flags & 0x02000000) {
                y = w->frame * (amp * func_00195070(w->tab[(u8)(k + 1)]));
            } else {
                y = w->frame * (amp * w->tab[(u8)(k + 1)]);
            }
            if (w->flags & 0x20000000) {
                z = 0.0f;
            } else if (w->flags & 0x04000000) {
                z = w->frame * (amp * func_00195070(w->tab[(u8)(k + 2)]));
            } else {
                z = w->frame * (amp * w->tab[(u8)(k + 2)]);
            }
            pos.x = x - w->size;
            pos.y = y + w->size;
            pos.z = z;
            if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
                w->flags |= 0x100000;
            }
            pos.x = x + w->size;
            pos.y = y + w->size;
            if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
                w->flags |= 0x200000;
            }
            pos.x = x - w->size;
            pos.y = y - w->size;
            if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
                w->flags |= 0x400000;
            }
            pos.x = x + w->size;
            pos.y = y - w->size;
            if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[3]) != 0) {
                w->flags |= 0x800000;
            }
            func_00208700(&pk, w->texture, 0);
            if (func_00104520(w->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else if (func_00104520(w->flags, 0x14) != 0 && func_00104520(w->flags, 0x15) != 0 &&
                       func_00104520(w->flags, 0x16) != 0 && func_00104520(w->flags, 0x17) != 0) {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
            w->flags &= 0xFF0FFFFF;
        }
    }
    w->frame++;
    return 0;
}

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b025_01E01EF0;

typedef struct {
    f32 x, y, z, w;
} Vec_b025_01E01EF0;

typedef struct {
    u8 pad00[7];
    u8 col;
    u8 pad08[0x2E];
    s16 life;
    s16 max;
    s16 used;
} Trail_b025_01E01EF0;

static s32 func_01E01EF0_b025(Trail_b025_01E01EF0 *o, Pt_b025_01E01EF0 *pts, Vec_b025_01E01EF0 *pos) {
    s32 k;

    if (o->used <= o->max - 1) {
        o->used++;
    }
    for (k = o->used; k > -1; k--) {
        if (pts[k].e > o->life) {
            o->used = k;
        }
    }
    for (k = o->used; k > 0; k--) {
        pts[k].x = pts[k - 1].x;
        pts[k].y = pts[k - 1].y;
        pts[k].z = pts[k - 1].z;
        pts[k].d = pts[k - 1].d;
        pts[k].e = pts[k - 1].e;
        pts[k].c = pts[k - 1].c;
    }
    pts[0].x = pos->x;
    pts[0].y = pos->y;
    pts[0].z = pos->z;
    pts[0].d = 0;
    pts[0].e = 0;
    pts[0].c = o->col;
    return 0;
}

/* shape b025:01E01FD0 (LkEFF_SortFieldThing), 616 insns, 9 copies: b013:01E02BE0's billboard particles with the points
   passed in (pts) and no count multiplier: per point the atlas cell of its frame (row- or column-major), frame advance
   every rate ticks, x jittered by rand() % 4 - 2 when the frame wraps, optional growth with age; depth-sorted unless
   flag 0x13. The fourth corner's depth goes to depth[1] (as in the original). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b025_01E01FD0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b025_01E01FD0;

typedef struct {
    Uv_b025_01E01FD0 uv;
    Xyz_b025_01E01FD0 p;
} Vtx_b025_01E01FD0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b025_01E01FD0 v[4];
    u8 tail[0x20];
} Pk_b025_01E01FD0;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} Part_b025_01E01FD0;

typedef struct {
    void *texture;
    u8 b4, b5, b6, b7;
    s32 flags;
    f32 size;
    u8 pad10[4];
    s16 cw;
    s16 ch;
    s16 u0;
    s16 v0;
    s16 aw;
    s16 ah;
    u8 f20[0x10];
    f32 grow;
    u8 pad34[4];
    s16 n0;
    s16 n1;
    s16 frames;
    s16 rate;
} Em_b025_01E01FD0;

typedef struct {
    Vec4f v[4];
} Quad_b025_01E01FD0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b025_01E01FD0;

static s32 func_01E01FD0_b025(s32 obj, Em_b025_01E01FD0 *o, Part_b025_01E01FD0 *pts, Cam_b025_01E01FD0 *cam) {
    extern Quad_b025_01E01FD0 D_01E05400_b025;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00205C90();
    extern void func_00103620();
    s32 n;
    f32 m[16];
    f32 depth[4];
    Quad_b025_01E01FD0 in;
    Vec4f out[4];
    Vec4f pos;
    Pk_b025_01E01FD0 pk __attribute__((aligned(8)));
    s32 i;
    s16 u;
    s16 v;
    f32 s;

    in = D_01E05400_b025;
    in.v[0].x = -o->size;
    in.v[0].y = o->size;
    in.v[1].x = o->size;
    in.v[1].y = o->size;
    in.v[2].x = -o->size;
    in.v[2].y = -o->size;
    in.v[3].x = o->size;
    in.v[3].y = -o->size;
    if (func_00104520(o->flags, 0x1F) != 0) {
        n = o->n0;
    } else {
        n = o->n1;
    }
    func_00205C90(m);
    for (i = 0; i < 4; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pk_b025_01E01FD0 *)(s32)&pk)->flags = 0x24;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->size = 9;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pk_b025_01E01FD0 *)(s32)&pk)->pad4 = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    pk.r = o->b6;
    pk.g = o->b5;
    pk.b = o->b4;
    pk.q = 1.0f;
    for (i = 0; i < n; i++) {
        if (func_00104520(o->flags, 1) != 0) {
            u = o->u0 + o->cw * (pts[i].frame % (o->aw / o->cw));
            v = o->v0 + o->ch * (pts[i].frame / (o->aw / o->cw));
        } else {
            u = o->u0 + o->cw * (pts[i].frame / (o->ah / o->ch));
            v = o->v0 + o->ch * (pts[i].frame % (o->ah / o->ch));
        }
        if (pts[i].age % o->rate == 0) {
            pts[i].frame++;
            if (pts[i].frame > o->frames - 1) {
                pts[i].frame = 0;
                pts[i].x += func_0019A5C8() % 4 - 2;
            }
        }
        ((Pk_b025_01E01FD0 *)(s32)&pk)->flags |= 0x800;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[0].uv)->u = u * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[0].uv)->v = v * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[1].uv)->u = (u + o->cw - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[1].uv)->v = v * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[2].uv)->u = u * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[2].uv)->v = (v + o->ch - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[3].uv)->u = (u + o->cw - 1) * 16;
        ((Uv_b025_01E01FD0 *)(s32)&pk.v[3].uv)->v = (v + o->ch - 1) * 16;
        pk.a = pts[i].c;
        if (func_00104520(o->flags, 0xF) != 0) {
            s = o->grow * pts[i].age;
        } else {
            s = 1.0f;
        }
        if (func_00104520(o->flags, 0x10) != 0) {
            func_00103620(&pts[i], o->f20);
        }
        pts[i].age++;
        pos.x = out[0].x * s + pts[i].x;
        pos.y = out[0].y * s + pts[i].y;
        pos.z = out[0].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        pos.x = out[1].x * s + pts[i].x;
        pos.y = out[1].y * s + pts[i].y;
        pos.z = out[1].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        pos.x = out[2].x * s + pts[i].x;
        pos.y = out[2].y * s + pts[i].y;
        pos.z = out[2].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
            o->flags |= 0x400000;
        }
        pos.x = out[3].x * s + pts[i].x;
        pos.y = out[3].y * s + pts[i].y;
        pos.z = out[3].z * s + pts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[1]) != 0) {
            o->flags |= 0x800000;
        }
        func_00208CB0(&pk, (u64)0xA | ((u64)u << 4) | ((u64)(u + o->cw - 1) << 14) | ((u64)v << 24) |
                               ((u64)(v + o->ch - 1) << 34));
        func_00208700(&pk, o->texture, 1);
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b013_01E029E0;

typedef struct {
    f32 x, y, z, w;
} Vec_b013_01E029E0;

typedef struct {
    u8 pad00[7];
    u8 col;
    u8 pad08[4];
    Pt_b013_01E029E0 *pts;
    u8 pad10[0x10];
    u8 rot[0x18];
    f32 radius;
    u8 pad3C[0xA];
    s16 rings;
    s16 used;
    s16 count;
} Ring_b013_01E029E0;

static s32 func_01E02970_b025(Ring_b013_01E029E0 *o, Vec_b013_01E029E0 *center) {
    extern void func_00103C40(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    f32 m[16];
    Vec_b013_01E029E0 t[2];
    s32 k;
    s32 j;
    s32 base;

    if (o->used <= o->rings - 1) {
        o->used++;
    }
    for (k = o->used; k > 0; k--) {
        base = k * o->count;
        for (j = 0; j < o->count; j++) {
            o->pts[base + j] = o->pts[j + (base - o->count)];
        }
    }
    func_00103C40(o->rot, m);
    for (j = 0; j < o->count; j++) {
        t[0].y = 0.0f;
        t[0].z = o->radius * func_0020B480(0x10000 / o->count * j);
        t[0].x = o->radius * func_0020B550(0x10000 / o->count * j);
        func_0020CDD0(&t[1], m, &t[0]);
        o->pts[j].x = center->x + t[1].x;
        o->pts[j].y = center->y + t[1].y;
        o->pts[j].z = center->z + t[1].z;
        o->pts[j].d = 0;
        o->pts[j].e = 0;
        o->pts[j].c = o->col;
    }
    return 0;
}

/* shape b013:01E02BE0, 642 insns, 11 copies: draws animated billboard particles: 4 corners (from a template,
   sized by the emitter) turned to the camera, per particle the atlas cell of its frame (row- or column-major),
   frame advance every `rate` ticks, optional growth with age; depth-sorted unless flag 0x13. The fourth corner's
   depth goes to depth[1] (as in the original), so the average reads an unset depth[3]. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b013_01E02BE0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b013_01E02BE0;

typedef struct {
    u64 uv;
    Xyz_b013_01E02BE0 p;
} Vtx_b013_01E02BE0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b013_01E02BE0 v[4];
    u8 tail[0x20];
} Pk_b013_01E02BE0;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} Part_b013_01E02BE0;

typedef struct {
    void *texture;
    u8 b4, b5, b6, b7;
    s32 flags;
    Part_b013_01E02BE0 *parts;
    u8 pad10[4];
    s16 cw;
    s16 ch;
    s16 u0;
    s16 v0;
    s16 aw;
    s16 ah;
    u8 f20[0x10];
    f32 size;
    f32 grow;
    u8 pad38[0xE];
    s16 n0;
    s16 n1;
    s16 mult;
    s16 frames;
    s16 rate;
} Em_b013_01E02BE0;

typedef struct {
    Vec4f v[4];
} Quad_b013_01E02BE0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b013_01E02BE0;

static s32 func_01E02B70_b025(s32 obj, Em_b013_01E02BE0 *o, Cam_b013_01E02BE0 *cam) {
    extern Quad_b013_01E02BE0 D_01E05440_b025;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00205C90();
    extern void func_00103620();
    s32 n;
    f32 m[16];
    f32 depth[4];
    Quad_b013_01E02BE0 in;
    Vec4f out[4];
    Vec4f pos;
    Pk_b013_01E02BE0 pk __attribute__((aligned(8)));
    s32 i;
    s16 u;
    s16 v;
    f32 s;

    in = D_01E05440_b025;
    in.v[0].x = -o->size;
    in.v[0].y = o->size;
    in.v[1].x = o->size;
    in.v[1].y = o->size;
    in.v[2].x = -o->size;
    in.v[2].y = -o->size;
    in.v[3].x = o->size;
    in.v[3].y = -o->size;
    if (func_00104520(o->flags, 0x1F) != 0) {
        n = o->n0 * o->mult;
    } else {
        n = o->n1 * o->mult;
    }
    func_00205C90(m);
    for (i = 0; i < 4; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pk_b013_01E02BE0 *)(s32)&pk)->flags = 0x24;
    ((Pk_b013_01E02BE0 *)(s32)&pk)->size = 9;
    ((Pk_b013_01E02BE0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pk_b013_01E02BE0 *)(s32)&pk)->pad4 = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    }
    pk.r = o->b6;
    pk.g = o->b5;
    pk.b = o->b4;
    pk.q = 1.0f;
    for (i = 0; i < n; i++) {
        if (func_00104520(o->flags, 1) != 0) {
            u = o->u0 + o->cw * (o->parts[i].frame % (o->aw / o->cw));
            v = o->v0 + o->ch * (o->parts[i].frame / (o->aw / o->cw));
        } else {
            u = o->u0 + o->cw * (o->parts[i].frame / (o->ah / o->ch));
            v = o->v0 + o->ch * (o->parts[i].frame % (o->ah / o->ch));
        }
        if (o->parts[i].age % o->rate == 0) {
            o->parts[i].frame++;
            if (o->parts[i].frame > o->frames - 1) {
                o->parts[i].frame = 0;
            }
        }
        ((Pk_b013_01E02BE0 *)(s32)&pk)->flags |= 0x800;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[0].uv)->u = u * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[0].uv)->v = v * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[1].uv)->u = (u + o->cw - 1) * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[1].uv)->v = v * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[2].uv)->u = u * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[2].uv)->v = (v + o->ch - 1) * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[3].uv)->u = (u + o->cw - 1) * 16;
        ((UV_b013_01E02BE0 *)(s32)&pk.v[3].uv)->v = (v + o->ch - 1) * 16;
        pk.a = o->parts[i].c;
        if (func_00104520(o->flags, 0xF) != 0) {
            s = o->grow * o->parts[i].age;
        } else {
            s = 1.0f;
        }
        if (func_00104520(o->flags, 0x10) != 0) {
            func_00103620(&o->parts[i], o->f20);
        }
        o->parts[i].age++;
        pos.x = out[0].x * s + o->parts[i].x;
        pos.y = out[0].y * s + o->parts[i].y;
        pos.z = out[0].z * s + o->parts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        pos.x = out[1].x * s + o->parts[i].x;
        pos.y = out[1].y * s + o->parts[i].y;
        pos.z = out[1].z * s + o->parts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        pos.x = out[2].x * s + o->parts[i].x;
        pos.y = out[2].y * s + o->parts[i].y;
        pos.z = out[2].z * s + o->parts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[2].p, &depth[2]) != 0) {
            o->flags |= 0x400000;
        }
        pos.x = out[3].x * s + o->parts[i].x;
        pos.y = out[3].y * s + o->parts[i].y;
        pos.z = out[3].z * s + o->parts[i].z;
        if (func_00205440(&pos, cam->view, &pk.v[3].p, &depth[1]) != 0) {
            o->flags |= 0x800000;
        }
        func_00208CB0(&pk, (u64)0xA | ((u64)u << 4) | ((u64)(u + o->cw - 1) << 14) | ((u64)v << 24) |
                               ((u64)(v + o->ch - 1) << 34));
        func_00208700(&pk, o->texture, 1);
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = pk.v[2].p.z = pk.v[3].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

typedef struct V4_b000_01E032C0 {
    f32 x, y, z, w;
} V4_b000_01E032C0;

typedef struct Rnd_b000_01E032C0 {
    s32 a, b, c, d;
} Rnd_b000_01E032C0;

typedef struct Obj_b000_01E032C0 {
    s32 kind;
    s32 model;
    s32 pad8;
    f32 scale;
    s32 pad10[4];
    V4_b000_01E032C0 v[4];
    Rnd_b000_01E032C0 r[64];
} Obj_b000_01E032C0;

typedef struct Tbl_b000_01E032C0 {
    V4_b000_01E032C0 v[4];
} Tbl_b000_01E032C0;

static s32 func_01E03580_b025(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E05480_b025;
    Tbl_b000_01E032C0 tbl = D_01E05480_b025;
    s32 flag;
    s32 n;
    s32 i;

    flag = func_00104520(obj->model, 0x1F);
    obj->scale = scale;
    obj->kind = kind;
    n = flag ? 0x10 : 0x40;
    for (i = 0; i < 4; i++) {
        obj->v[i].x = obj->scale * tbl.v[i].x;
        obj->v[i].y = obj->scale * tbl.v[i].y;
        obj->v[i].z = obj->scale * tbl.v[i].z;
    }
    for (i = 0; i < n; i++) {
        obj->r[i].a = func_0019A5C8() % 0x10000;
        obj->r[i].b = func_0019A5C8() % 0x10000;
        obj->r[i].c = func_0019A5C8() % 0x10000;
    }
    return 0;
}

/* shape b000:01E03420, 387 insns, 68 copies: draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E03420;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        struct {
            f32 s, t;
        } st;
        struct {
            u64 u : 14;
            u64 pad0 : 2;
            u64 v : 14;
            u64 pad1 : 34;
        } uv;
    } tc;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E03420;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E03420;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E03420 v[4];
    u8 tail[0x20];
} Pkt_b000_01E03420;

typedef struct {
    f32 x, y, z, w;
} Vec_b000_01E03420;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E03420 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    Vec_b000_01E03420 p[4];
    Vec_b000_01E03420 rot[1];
} Spr_b000_01E03420;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E03420;

static s32 func_01E036E0_b025(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b000_01E03420 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b000_01E03420 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E03420 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b025((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b000_01E03420 *)(s32)&pkt)->count |= 0x800;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b000_01E03420 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
    } else {
        pkt.v[0].tc.st.s = spr->rect.f.s;
        pkt.v[0].tc.st.t = spr->rect.f.t;
        pkt.v[1].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[1].tc.st.t = spr->rect.f.t;
        pkt.v[2].tc.st.s = spr->rect.f.s;
        pkt.v[2].tc.st.t = spr->rect.f.t + spr->rect.f.h;
        pkt.v[3].tc.st.s = spr->rect.f.s + spr->rect.f.w;
        pkt.v[3].tc.st.t = spr->rect.f.t + spr->rect.f.h;
    }
    for (i = 0; i < n[0]; i++) {
        func_0020C630(m, &spr->rot[i]);
        func_0020CDD0(&out, m, &spr->p[0]);
        if (func_00205440(&out, cam->view, &pkt.v[0].tc + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        func_0020CDD0(&out, m, &spr->p[1]);
        if (func_00205440(&out, cam->view, &pkt.v[1].tc + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        func_0020CDD0(&out, m, &spr->p[2]);
        if (func_00205440(&out, cam->view, &pkt.v[2].tc + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        func_0020CDD0(&out, m, &spr->p[3]);
        if (func_00205440(&out, cam->view, &pkt.v[3].tc + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208700(&pkt, spr->texture, 0);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else if (func_00104520(spr->flags, 0x12) != 0) {
                func_002075F0(&pkt, obj, 0xFFFFFF);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b025:01E03CF0, 103 insns, 9 copies: set up a particle object: 6 corner offsets from a local table sized
   by the object's width/height, then each particle gets a random start (-rand() % 0x2000, rand() % 0x10000) */

typedef struct V4_b025_01E03CF0 {
    f32 x, y, z, w;
} V4_b025_01E03CF0;

typedef struct Part_b025_01E03CF0 {
    s32 a;
    s32 b;
    s32 c;
    u8 col;
    u8 padD;
    s16 age;
} Part_b025_01E03CF0;

typedef struct Obj_b025_01E03CF0 {
    s32 kind;
    u8 pad4[7];
    u8 col;
    u8 padC[0x14];
    V4_b025_01E03CF0 v[6];
    Part_b025_01E03CF0 *parts;
    f32 h;
    f32 w;
    u8 pad8C[0xE];
    s16 count;
} Obj_b025_01E03CF0;

typedef struct W_tbl_func_01E03CF0_b025 {
    V4_b025_01E03CF0 v[6];
} W_tbl_func_01E03CF0_b025;

static s32 func_01E03CF0_b025(Obj_b025_01E03CF0 *o, s32 kind) {
    extern s32 func_0019A5C8();
    extern W_tbl_func_01E03CF0_b025 D_01E054C0_b025;
    W_tbl_func_01E03CF0_b025 tbl_w = D_01E054C0_b025;
    s32 i;

    tbl_w.v[0].x = -o->w / 2.0f;
    tbl_w.v[0].y = o->h;
    tbl_w.v[1].x = -o->w / 2.0f;
    tbl_w.v[2].y = o->h;
    tbl_w.v[4].x = o->w / 2.0f;
    tbl_w.v[4].y = o->h;
    tbl_w.v[5].x = o->w / 2.0f;
    o->kind = kind;
    for (i = 0; i < 6; i++) {
        o->v[i].x = tbl_w.v[i].x;
        o->v[i].y = tbl_w.v[i].y;
        o->v[i].z = tbl_w.v[i].z;
    }
    for (i = 0; i < o->count; i++) {
        o->parts[i].a = -func_0019A5C8() % 0x2000;
        o->parts[i].b = func_0019A5C8() % 0x10000;
        o->parts[i].c = 0;
        o->parts[i].age = 0;
        o->parts[i].col = o->col;
    }
    return 0;
}

/* shape b025:01E03E90 (LkSortShockWall), 450 insns, 9 copies: draws a textured shock wall: per segment a rotated,
   offset 6-point strip drawn as two quads, alpha fading out, the segment count growing each frame */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b025_01E03E90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b025_01E03E90 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b025_01E03E90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b025_01E03E90 v[4];
    u8 tail[0x20];
} Pkt_b025_01E03E90;

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 pad;
    s16 t;
} Seg_b025_01E03E90;

typedef struct {
    s32 x, y, z, w;
} Pos_b025_01E03E90;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 col;
    f32 r;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f q[6];
    Seg_b025_01E03E90 *seg;
    u8 pad84[8];
    f32 dy;
    f32 dx;
    s32 arc;
    s16 frame;
    s16 max;
    s16 n;
    s16 grow;
} Wall_b025_01E03E90;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b025_01E03E90;

/* n: a 4th parameter the caller never passes, reused as the segment count (its spill slot needs it) */

static s32 func_01E03E90_b025(s32 ot, Wall_b025_01E03E90 *o, Cam_b025_01E03E90 *cam __attribute__((aligned(16))),
                              s32 n) {
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f sc;
    Pos_b025_01E03E90 pos;
    f32 m[16];
    Vec4f pts[6];
    f32 d[4];
    Pkt_b025_01E03E90 pkt;
    s32 step;
    s32 start;
    s32 k;
    s32 i;
    s16 tu;

    n = o->n;
    if (o->max < n) {
        n = o->n = o->max;
    }
    step = -(o->arc / o->max);
    start = -(0x8000 - o->arc) >> 1;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->pad = 0;
    func_00208CB0(&pkt, ((u64)o->v << 24) | (((u64)(o->w - 1) << 4) | 0xB | ((u64)o->u << 14)) |
                            ((u64)(o->v + o->h - 1) << 34));
    func_00208700(&pkt, o->texture, 0);
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b025((Vtx_b000_01E00100 *)&pkt, &o->col);
    for (k = 0; k < n; k++) {
        sc.z = o->r * func_0020B550(start + step * k);
        sc.x = o->r * func_0020B480(start + step * k);
        sc.y = 0.0f;
        pos.x = o->seg[k].x;
        pos.y = o->seg[k].y;
        pos.z = o->seg[k].z;
        func_0020C940(m, 0, &pos, &sc);
        func_0020BCF0((s32)m, (s32)cam->view);
        for (i = 0; i < 6; i++) {
            pts[i] = o->q[i];
            if (i != 2 && i != 3) {
                pts[i].x = o->q[i].x + o->dx * o->seg[k].t;
            }
            if (i % 2 == 0) {
                pts[i].y = o->q[i].y + o->dy * o->seg[k].t;
            }
        }
        for (i = 0; i < 2; i++) {
            if (i != 0) {
                pkt.v[0].a = o->seg[k].a;
                pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = 0;
            } else {
                pkt.v[0].a = pkt.v[1].a = pkt.v[3].a = 0;
                pkt.v[2].a = o->seg[k].a;
            }
            tu = o->seg[k].t % o->w + (o->w >> 1) * i;
            ((Pkt_b025_01E03E90 *)(s32)&pkt)->count |= 0x800;
            pkt.v[0].st.s = tu * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[0].st)->t = o->v * 16;
            pkt.v[1].st.s = tu * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[1].st)->t = (o->v + o->h - 1) * 16;
            pkt.v[2].st.s = (tu + (o->w >> 1)) * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[2].st)->t = o->v * 16;
            pkt.v[3].st.s = (tu + (o->w >> 1)) * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[3].st)->t = (o->v + o->h - 1) * 16;
            if (func_00205630(&pts[i * 2], 0x70000000, m, &pkt, d) != 0) {
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else if (func_00104520(o->flags, 0x12) != 0) {
                    func_002075F0(&pkt, ot, 0xFFFFFF);
                } else {
                    func_002075F0(&pkt, ot, func_001A23B0(d[0]));
                }
            }
        }
        if (func_00104520(o->flags, 0x1E) == 0) {
            o->seg[k].t++;
        }
    }
    o->frame++;
    o->n += o->grow;
    return 0;
}

/* shape b025:01E045A0 (b025), 903 insns, 1 copy (-O2,p): b025 scene manager (b067:01E033B0's -O2 original): code >= 0
   sets up five coords, five joints, a 250-tick timer, a random table, the model shot, a shock wall, a sword trail, 60
   sparks, the wave, a puff trail, the exhaust emitter and a flash sprite; else steps the trail (resets at
   20/134/167), puffs at the joints, from 135 draws the wall, the sparks and wave until 168, the sprite from 168;
   returns 2 at 168, 1 at 126, 6 on 136..167, 8 when the timer ends */

typedef struct {
    Vec4f scale;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b025_01E045A0;

typedef struct {
    Obj_b025_01E00910 o;
    u8 pad[8];
} Sw_b025_01E045A0;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 pad[3];
} Part_b025_01E045A0;

typedef struct {
    void *texture;
    u8 b, g, r, a;
    s32 flags;
    f32 size;
    s16 h10, h12;
    s16 cw, ch;
    s16 u0, v0;
    s16 aw, ah;
    f32 f20, f24, f28;
    u8 pad2C[4];
    f32 grow;
    s16 h34;
    s16 h36;
    s16 n0;
    s16 n1;
    s16 frames;
    s16 rate;
    Part_b025_01E045A0 pts[36];
} Trl_b025_01E045A0;

typedef struct {
    void *texture;
    u8 b, g, r, a;
    s32 flags;
    Part_b025_01E045A0 *parts;
    s16 h10, h12;
    s16 cw, ch;
    s16 u0, v0;
    s16 aw, ah;
    f32 f20, f24, f28;
    u8 pad2C[4];
    f32 size;
    f32 grow;
    f32 f38;
    u8 pad3C[6];
    s16 h42;
    s16 h44;
    s16 n0;
    s16 n1;
    s16 mult;
    s16 frames;
    s16 rate;
    Part_b025_01E045A0 pts[0x120];
} Exh_b025_01E045A0;

typedef struct {
    f32 x, y, z;
} Pt_b025_01E045A0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_b025_01E045A0 pts[60];
} Spark_b025_01E045A0;

typedef struct {
    s32 kind;
    s32 flags;
    u8 b, g, r, a;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x448];
} Spr_b025_01E045A0;

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 pad;
    s16 t;
} Seg_b025_01E045A0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 r0;
    s16 u, v, w, h;
    u8 pad18[0x68];
    Seg_b025_01E045A0 *seg;
    f32 dy;
    f32 dx;
    f32 f8C;
    s32 f90;
    s32 arc;
    s16 frame;
    s16 count;
    s16 n;
    s16 grow;
} Wall_b025_01E045A0;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 scale;
    s16 count;
    s16 model;
} Shot_b025_01E045A0;

typedef struct {
    Crd_b025_01E045A0 cam0;
    Sw_b025_01E045A0 sw;
    Trl_b025_01E045A0 trl;
    Exh_b025_01E045A0 exh;
    Crd_b025_01E045A0 cam1;
    Spark_b025_01E045A0 spark;
    Wave_b025_01E016F0 wave;
    Crd_b025_01E045A0 cam2;
    Spr_b025_01E045A0 spr;
    Crd_b025_01E045A0 cam3;
    Wall_b025_01E045A0 wall;
    Seg_b025_01E045A0 seg[0x40];
    Crd_b025_01E045A0 cam4;
    Shot_b025_01E045A0 shot;
    s32 timer;
    s32 t;
    s32 code;
    s32 j[5];
    Vec4f tr[2][28];
    s8 tab[256];
} Scene_b025_01E045A0;

#pragma optimization_level 2

static s32 func_01E045A0_b025(s32 arg0, s32 code) {
    Scene_b025_01E045A0 *g = (Scene_b025_01E045A0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_0019A5C8();
    extern s32 b025_01E03E90();
    extern s32 b025_01E01110();
    extern s32 b025_01E016F0();
    extern s32 b025_01E02B70();
    extern s32 b025_01E01FD0();
    extern s32 b025_01E036E0();
    s32 ot;
    Vec4f v[2];
    Vec4f p;
    s32 tx[4];
    s32 i;
    s32 k;
    s32 j;
    s32 n;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2900);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        g->cam1.scale.x = g->cam1.scale.y = g->cam1.scale.z = 0.1f;
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        func_00103890(&g->cam4);
        g->j[0] = func_001F5560(func_001F53A0(), 0x3D, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x3C, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x3B, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x16, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0xC, 0);
        g->timer = 0xFA;
        g->t = 1;
        g->code = code;
        for (i = 0; i < 256; i++) {
            g->tab[i] = func_0019A5C8() >> 4;
        }
        g->shot.flags = 0;
        g->shot.r = 0x80;
        g->shot.g = 0x10;
        g->shot.b = 0x10;
        g->shot.a = 0;
        g->shot.scale = 20.0f;
        g->shot.count = 5;
        g->shot.model = func_001F53A0();
        func_00103290(tx, 0);
        g->wall.flags = 1;
        g->wall.u = 0;
        g->wall.v = 0;
        g->wall.w = 0x20;
        g->wall.h = 0x40;
        g->wall.r = 0x20;
        g->wall.g = 0x10;
        g->wall.b = 0x40;
        g->wall.a = 0x80;
        g->wall.seg = g->seg;
        g->wall.dy = 30.0f;
        g->wall.dx = 30.0f;
        g->wall.f8C = 2.0f;
        g->wall.f90 = 0;
        g->wall.arc = 0x6000;
        g->wall.r0 = 20.0f;
        g->wall.frame = 0;
        g->wall.count = 0x40;
        g->wall.n = 999;
        g->wall.grow = 3;
        func_01E03CF0_b025((Obj_b025_01E03CF0 *)&g->wall, tx[0]);
        func_00103260(tx, 0xF);
        g->sw.o.texture = (void *)tx[0];
        g->sw.o.flags = 1;
        g->sw.o.max = 8;
        g->sw.o.r.i.u = 0x8E;
        g->sw.o.r.i.v = 0x54;
        g->sw.o.r.i.w = 0x20;
        g->sw.o.r.i.h = 1;
        g->sw.o.col.r = 0x20;
        g->sw.o.col.g = 0x10;
        g->sw.o.col.b = 0x40;
        g->sw.o.col.a = 0xFF;
        g->sw.o.p1 = g->tr[0];
        g->sw.o.p2 = g->tr[1];
        func_001F5620(func_001F53A0(), g->j[1], &v[0]);
        func_001F5620(func_001F53A0(), g->j[2], &v[1]);
        for (j = 0; j < 8; j++) {
            g->sw.o.a[j].x = v[0].x;
            g->sw.o.a[j].y = v[0].y;
            g->sw.o.a[j].z = v[0].z;
            g->sw.o.b[j].x = v[1].x;
            g->sw.o.b[j].y = v[1].y;
            g->sw.o.b[j].z = v[1].z;
        }
        g->sw.o.len = 0;
        g->spark.texture = (void *)tx[0];
        g->spark.flags = 0x20080001;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.r = 0x80;
        g->spark.g = 0x80;
        g->spark.b = 0x80;
        g->spark.a = 0xFF;
        g->spark.size = 0.5f;
        for (n = 0; n < 60; n++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.pts[n].x = func_0019A5C8() % 100 - 50;
                g->spark.pts[n].z = func_0019A5C8() % 50;
                g->spark.pts[n].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.pts[n].x = func_0019A5C8() % 50 - 25;
                g->spark.pts[n].y = func_0019A5C8() % 25;
                g->spark.pts[n].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->wave.texture = (void *)tx[0];
        g->wave.tab = g->tab;
        g->wave.flags = 0x20000000;
        g->wave.u = 0xB0;
        g->wave.v = 0x40;
        g->wave.w = 0x20;
        g->wave.h = 0x20;
        g->wave.bA = 0x80;
        g->wave.b9 = 0x10;
        g->wave.b8 = 0x10;
        g->wave.bB = 0xFF;
        g->wave.size = 0.8f;
        g->wave.amp = 0.03f;
        g->wave.frame = 0;
        g->wave.count = 0x100;
        g->wave.phase = 7;
        g->trl.texture = (void *)tx[0];
        g->trl.r = 0x80;
        g->trl.g = 0x10;
        g->trl.b = 0x10;
        g->trl.a = 0x30;
        g->trl.flags = 0x9003;
        g->trl.size = 3.0f;
        g->trl.f20 = 0.0f;
        g->trl.f24 = 0.5f;
        g->trl.f28 = 0.0f;
        g->trl.h10 = 0x80;
        g->trl.h12 = 0xC0;
        g->trl.cw = 0x20;
        g->trl.ch = 0x20;
        g->trl.u0 = 0x80;
        g->trl.v0 = 0xC0;
        g->trl.aw = 0x80;
        g->trl.ah = 0x100;
        g->trl.grow = 0.3f;
        g->trl.h34 = 0;
        g->trl.h36 = 0x18;
        g->trl.n0 = 0x24;
        g->trl.n1 = 0;
        g->trl.frames = 8;
        g->exh.texture = (void *)tx[0];
        g->exh.r = 0x80;
        g->exh.g = 0x80;
        g->exh.b = 0x80;
        g->exh.a = 0x30;
        g->exh.flags = 0x19003;
        g->exh.parts = g->exh.pts;
        g->exh.h10 = 0x80;
        g->exh.h12 = 0xC0;
        g->exh.cw = 0x20;
        g->exh.ch = 0x20;
        g->exh.u0 = 0x80;
        g->exh.v0 = 0xC0;
        g->exh.aw = 0x80;
        g->exh.ah = 0x100;
        g->exh.f20 = 0.0f;
        g->exh.f24 = 0.3f;
        g->exh.f28 = 0.0f;
        g->exh.size = 3.0f;
        g->exh.grow = 0.2f;
        g->exh.f38 = 3.3f;
        g->exh.h42 = 0;
        g->exh.h44 = 0x18;
        g->exh.n0 = 0x24;
        g->exh.n1 = 0;
        g->exh.mult = 8;
        g->exh.frames = 8;
        g->exh.rate = 0;
        g->spr.flags = 0x80001;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.r = 0xD0;
        g->spr.g = 0xA0;
        g->spr.b = 0x70;
        g->spr.a = 0x20;
        { extern s32 b025_01E03580(void *, s32, f32); b025_01E03580(&g->spr, tx[0], 1.6f); }
        return 0;
    }
    func_001F53C0(1, func_001F53A0(), &g->cam4.pos);
    func_001F5F90(func_001F5380(), &g->cam1.pos);
    func_001F5F90(func_001F5380(), &g->cam2.pos);
    func_001F5620(func_001F53A0(), g->j[1], &v[0]);
    func_001F5620(func_001F53A0(), g->j[2], &v[1]);
    if (g->t == 0x14 || g->t == 0x86 || g->t == 0xA7) {
        for (j = 0; j < 8; j++) {
            g->sw.o.a[j].x = v[0].x;
            g->sw.o.a[j].y = v[0].y;
            g->sw.o.a[j].z = v[0].z;
            g->sw.o.b[j].x = v[1].x;
            g->sw.o.b[j].y = v[1].y;
            g->sw.o.b[j].z = v[1].z;
        }
        g->sw.o.len = 0;
    } else {
        func_01E007C0_b025((Trail_b025_01E007C0 *)&g->sw, &v[0], &v[1]);
    }
    if (g->t < 0xF) {
        func_01E01EF0_b025((Trail_b025_01E01EF0 *)&g->trl, (Pt_b025_01E01EF0 *)g->trl.pts, (Vec_b025_01E01EF0 *)&v[0]);
    }
    if (g->t == 0x4F || g->t == 0x63 || g->t == 0x86 || g->t == 0xBD) {
        func_001F5620(func_001F53A0(), g->j[4], &p);
        func_01E02970_b025((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&p);
    }
    if (g->t == 0x59 || g->t == 0x6D || g->t == 0x87 || g->t == 0xBE) {
        func_001F5620(func_001F53A0(), g->j[3], &p);
        func_01E02970_b025((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&p);
    }
    if (g->t == 0x87) {
        func_001F53C0(1, func_001F53A0(), &g->cam3.pos);
        g->cam3.pos.y = 20.0f;
        if (g->cam3.pos.z > 0.0f) {
            g->cam3.rot[1] = 0x8000;
        }
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001038D0(&g->cam2);
    func_001038D0(&g->cam3);
    func_001039A0(&g->cam4);
    if (g->t >= 0xC && g->t < 0xC0) {
        func_01E00120_b025((Shot_b015_01E008F0 *)&g->shot, (Vec_b015_01E008F0 *)&g->cam4.pos);
        if (g->t >= 0xA8) {
            func_00103470(&g->shot.a, 0, 4);
        } else {
            func_001032C0(&g->shot.a, 0x40, 2);
        }
    }
    if (g->t >= 0x87) {
        if (g->t == 0xA8) {
            g->wall.r0 = 20.0f;
            for (i = 0; i < g->wall.count; i++) {
                g->wall.seg[i].a = 0x80;
                g->wall.seg[i].t = 0x14;
            }
        }
        b025_01E03E90(ot, &g->wall, &g->cam3);
        { extern s32 func_00103390(f32 *p, f32 target, f32 step); func_00103390(&g->wall.r0, 50.0f, 2.0f); }
        for (i = 0; i < g->wall.count; i++) {
            if (g->wall.seg[i].t > 10) {
                func_00103470(&g->wall.seg[i].a, 0, 8);
            }
        }
    }
    if (g->t >= 0xA8) {
        b025_01E036E0(ot, &g->spr, &g->cam2);
        func_00103470(&g->spr.a, 0, 8);
    }
    if (g->t >= 0x87 && g->t < 0xA8) {
        p.x = p.y = p.z = 1.03f;
        b025_01E01110(ot, &g->spark, &g->cam1, &p);
        if (func_001033D0(&g->cam1.scale.x, 0.3f, 0.1f) == 0) {
            func_00103470(&g->spark.a, 0, 0x10);
        }
        b025_01E016F0(ot, &g->wave, &g->cam1);
        func_00103470(&g->wave.bB, 0, 0x10);
    }
    b025_01E02B70(ot, &g->exh, g);
    for (i = 0; i < g->exh.n1; i++) {
        for (k = 0; k < g->exh.mult; k++) {
            func_00103470(&g->exh.pts[i * g->exh.mult + k].a, 0, 3);
        }
    }
    b025_01E01FD0(ot, &g->trl, g->trl.pts, g);
    for (i = 0; i < g->trl.n1; i++) {
        func_00103470(&g->trl.pts[i].a, 0, 2);
    }
    if (g->t >= 0x8F) {
        func_00103470(&g->trl.a, 0, 8);
    }
    if ((g->t > 0x14 && g->t < 0x20) || (g->t > 0x86 && g->t < 0x8F) || (g->t > 0xA7 && g->t < 0xB6)) {
        func_01E00910_b025(&g->sw.o, (Cam_b025_01E00910 *)&g->cam0);
    }
    g->t++;
    g->timer--;
    if (g->t == 0xA8) {
        return 2;
    }
    if (g->t == 0x7E) {
        return 1;
    }
    if (g->t >= 0x88 && g->t < 0xA8) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

#pragma optimization_level reset
