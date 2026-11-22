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

static void func_01E00080_b467(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b001:01E00900, 73 insns, 54 copies: one GS sprite (RGBAQ, ST, XYZ2, ST, XYZ2) sent with the current texture */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b001_01E00900;

typedef struct {
    Hdr_b001_01E00900 h;
    u8 r, g, b, a;
    f32 q;
    f32 s0, t0;
    u64 x0 : 16;
    u64 y0 : 16;
    u64 z0 : 24;
    u64 f0 : 8;
    f32 s1, t1;
    u64 x1 : 16;
    u64 y1 : 16;
    u64 z1 : 24;
    u64 f1 : 8;
    u8 tail[0x20];
} Pkt_b001_01E00900;

static s32 func_01E00120_b467(void) {
    Pkt_b001_01E00900 p __attribute__((aligned(8)));

    ((Hdr_b001_01E00900 *)(s32)&p)->count = 0x26;
    ((Hdr_b001_01E00900 *)(s32)&p)->tag = 5;
    ((Hdr_b001_01E00900 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b001_01E00900 *)(s32)&p)->pad = 0;
    p.r = 0x80;
    p.g = 0x80;
    p.b = 0x80;
    p.a = 0x60;
    p.q = 1.0f;
    p.x0 = 0x6BF8;
    p.y0 = 0x71F8;
    p.z0 = 0xFFFFFF;
    p.f0 = 0;
    p.x1 = 0x93F8;
    p.y1 = 0x8DF8;
    p.z1 = 0xFFFFFF;
    p.f1 = 0;
    p.s0 = 0.0f;
    p.t0 = 0.0f;
    p.s1 = 0.625f;
    p.t1 = 0.875f;
    func_002086D0(&p, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&p, 1);
    func_002075F0((s32)&p, (s32)func_00207500(), 0);
    return 0;
}

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E035A0;

typedef struct {
    s32 type;
    s32 id;
    u8 pad08[4];
    f32 height;
    u8 pad10[0x10];
    f32 inner;
    f32 a24;
    f32 a28;
    u8 pad2C[4];
    f32 outer;
    f32 b34;
    f32 b38;
    u8 pad3C[4];
    Vec_b001_01E035A0 in[30];
    Vec_b001_01E035A0 out[30];
} Ring_b001_01E035A0;

static s32 func_01E00250_b467(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
    extern s32 func_001A22C0(f32);
    Vec_b001_01E035A0 *in;
    s32 i;
    f32 span;
    f32 top;
    f32 span2;
    f32 top2;
    f32 angle;
    s32 r;

    o->type = type;
    o->height = height;
    o->inner = inner;
    o->outer = outer;
    if (func_00104520(o->id, 0x1D) != 0) {
        o->a24 = 0.0f;
        top = y + height;
        o->a28 = y;
        o->b34 = 0.0f;
        span = 2.0f * height;
        o->b38 = top;
        for (i = 0; i < 30; i++) {
            angle = 0.20943952f * (i + 1);
            o->in[i].x = inner * func_0020B620(angle);
            o->in[i].y = inner * func_0020B730(angle);
            o->in[i].z = y;
            o->out[i].x = outer * func_0020B620(angle);
            o->out[i].y = outer * func_0020B730(angle);
            if (func_00104520(o->id, 0xF) != 0) {
                r = func_0019A5C8();
                o->out[i].z = top + ((r % func_001A22C0(span) - func_001A22C0(height)) >> 1);
            } else {
                o->out[i].z = top;
            }
        }
    } else {
        top2 = y + height;
        o->a24 = y;
        o->a28 = 0.0f;
        o->b34 = top2;
        span2 = 2.0f * height;
        o->b38 = 0.0f;
        for (i = 0; i < 30; i++) {
            angle = 0.20943952f * (i + 1);
            o->in[i].x = inner * func_0020B620(angle);
            o->in[i].z = inner * func_0020B730(angle);
            o->in[i].y = y;
            o->out[i].x = outer * func_0020B620(angle);
            o->out[i].z = outer * func_0020B730(angle);
            if (func_00104520(o->id, 0xF) != 0) {
                r = func_0019A5C8();
                o->out[i].y = top2 + ((r % func_001A22C0(span2) - func_001A22C0(height)) >> 1);
            } else {
                o->out[i].y = top2;
            }
        }
    }
    return 0;
}

/* shape b001:01E03860, 316 insns, 72 copies: draws the 30-segment ring built by b001:01E035A0.
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_b467) and needs that helper
   defined EARLIER in the same file as a static function: MWCC keeps &pkt in a0 across the call only then.
   The static copy below is that helper (identical code to ovl-matched/b000_01E00100.c). */

typedef struct {
    u8 b, g, r, a;
} Src_b001_01E03860;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b001_01E03860;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b001_01E03860 v[4];
    u8 tail[0x20];
} Pkt_b001_01E03860;

typedef struct {
    f32 x, y, z, w;
} Vec_b001_01E03860;

typedef struct {
    void *texture;
    s32 flags;
    Src_b001_01E03860 color;
    u8 pad0C[4];
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    u8 pad18[8];
    Vec_b001_01E03860 p0;
    Vec_b001_01E03860 p1;
    Vec_b001_01E03860 in[30];
    Vec_b001_01E03860 out[30];
} Ring_b001_01E03860;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b001_01E03860;



static inline void init_b001_01E03860(Pkt_b001_01E03860 *p) {
    p->count = 0x34;
    p->tag = 0xC;
    p->regs = ((u64)0x4214 << 32) | 0x21421421;
    p->pad = 0;
}

static s32 func_01E00510_b467(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    f32 depth[4];
    Pkt_b001_01E03860 pkt;
    s32 i;
    Pkt_b001_01E03860 *hdr;

    ((Pkt_b001_01E03860 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b001_01E03860 *)(s32)&pkt)->pad = 0;
    if (func_00104520(ring->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(ring->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    for (i = 0; i < 30; i++) {
        func_01E00080_b467(&pkt, &ring->color);
        func_00104540(&pkt, &ring->u, 2);
        if (i == 0) {
            if (func_00205440(&ring->p0, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                ring->flags |= 0x100000;
            }
            if (func_00205440(&ring->p1, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                ring->flags |= 0x200000;
            }
        } else {
            if (func_00205440(&ring->in[i - 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                ring->flags |= 0x100000;
            }
            if (func_00205440(&ring->out[i - 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                ring->flags |= 0x200000;
            }
        }
        if (i != 29) {
            if (func_00205440(&ring->in[i], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                ring->flags |= 0x400000;
            }
            if (func_00205440(&ring->out[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                ring->flags |= 0x800000;
            }
        } else {
            if (func_00205440(&ring->p0, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                ring->flags |= 0x400000;
            }
            if (func_00205440(&ring->p1, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                ring->flags |= 0x800000;
            }
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)ring->u << 4) | ((u64)(ring->u + ring->w - 1) << 14) |
                                ((u64)ring->v << 24) | ((u64)(ring->v + ring->h - 1) << 34));
        func_00208700(&pkt, ring->texture, 1);
        if (func_00104520(ring->flags, 0x14) != 0 && func_00104520(ring->flags, 0x15) != 0 &&
            func_00104520(ring->flags, 0x16) != 0 && func_00104520(ring->flags, 0x17) != 0) {
            if (func_00104520(ring->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        ring->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape b025:01E007C0, 84 insns, 13 copies: pushes new head points into an object's two 8-entry trails (mode != 0), or
   keeps only the last two and lets func_001036E0 fill the middle point (mode 0) */

typedef struct {
    u8 pad0[0xE];
    s16 mode;
    Vec4f a[8];
    Vec4f b[8];
} Trail_b025_01E007C0;

static s32 func_01E00A00_b467(Trail_b025_01E007C0 *o, Vec4f *p1, Vec4f *p2) {
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

static s32 func_01E00B50_b467(Obj_b025_01E00910 *o, Cam_b025_01E00910 *cam) {
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
    func_01E00080_b467((Vtx_b000_01E00100 *)&pkt, &o->col);
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

/* shape b540:01E00250 (LkPrim_SortSpot), 341 insns, 66 copies: a flat disc drawn as count triangles from the centre
   (the colour and its alpha) to the rim (alpha 0); flags 0x100000..0x400000 record which vertices projected, flag
   bits 0x13/0x12 force the far or the near z */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b540_01E00250;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b540_01E00250 xyz;
} Vtx_b540_01E00250;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b540_01E00250 v[3];
    u8 tail[8];
} Pkt_b540_01E00250;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 radius;
    s16 count;
    s16 height;
} Disc_b540_01E00250;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b540_01E00250;

static s32 func_01E01350_b467(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f c[3];
    Pkt_b540_01E00250 pkt __attribute__((aligned(8)));
    f32 dep[3];
    f32 step;
    f32 a;
    s32 i;

    step = 6.2831855f / d->count;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->count = 0x13;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->tag = 6;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->regs = 0x414141;
    ((Pkt_b540_01E00250 *)(s32)&pkt)->pad = 0;
    if (func_00104520(d->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(d->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.v[0].r = d->r;
    pkt.v[0].g = d->g;
    pkt.v[0].b = d->b;
    pkt.v[0].a = d->a;
    pkt.v[0].q = 1.0f;
    pkt.v[1].r = d->r;
    pkt.v[1].g = d->g;
    pkt.v[1].b = d->b;
    pkt.v[1].a = 0;
    pkt.v[1].q = 1.0f;
    pkt.v[2].r = d->r;
    pkt.v[2].g = d->g;
    pkt.v[2].b = d->b;
    pkt.v[2].a = 0;
    pkt.v[2].q = 1.0f;
    c[0].y = 0.0f;
    c[0].x = 0.0f;
    c[0].z = c[1].z = c[2].z = 0.1f * d->height;
    for (i = 0; i < d->count; i++) {
        if (func_00205440(&c[0], cam->view, &pkt.v[0].xyz, &dep[0]) != 0) {
            d->flags |= 0x100000;
        }
        a = step * i;
        c[1].x = d->radius * func_0020B620(a);
        c[1].y = d->radius * func_0020B730(a);
        if (func_00205440(&c[1], cam->view, &pkt.v[1].xyz, &dep[1]) != 0) {
            d->flags |= 0x200000;
        }
        if (i == d->count - 1) {
            c[2].x = d->radius;
            c[2].y = 0.0f;
        } else {
            a = step * (i + 1);
            c[2].x = d->radius * func_0020B620(a);
            c[2].y = d->radius * func_0020B730(a);
        }
        if (func_00205440(&c[2], cam->view, &pkt.v[2].xyz, &dep[2]) != 0) {
            d->flags |= 0x400000;
        }
        if (func_00104520(d->flags, 0x14) != 0 && func_00104520(d->flags, 0x15) != 0 &&
            func_00104520(d->flags, 0x16) != 0) {
            if (func_00104520(d->flags, 0x13) != 0) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, 0);
                }
            } else if (func_00104520(d->flags, 0x12) != 0) {
                func_002075F0(&pkt, ot, 0xFFFFFF);
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, 0xFFFFFF);
                }
            } else {
                func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2]) / 3.0f));
                if (func_00104520(d->flags, 0x1C) != 0) {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2]) / 3.0f));
                }
            }
        }
        d->flags &= 0xFF8FFFFF;
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

static s32 func_01E018B0_b467(s32 obj, Wave_b025_01E016F0 *w, Cam_b025_01E016F0 *cam) {
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

static s32 func_01E020B0_b467(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E03E80_b467;
    Tbl_b000_01E032C0 tbl = D_01E03E80_b467;
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

static s32 func_01E02210_b467(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_b467((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

static s32 func_01E02820_b467(Ring_b013_01E029E0 *o, Vec_b013_01E029E0 *center) {
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

static s32 func_01E02A20_b467(s32 obj, Em_b013_01E02BE0 *o, Cam_b013_01E02BE0 *cam) {
    extern Quad_b013_01E02BE0 D_01E03EC0_b467;
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

    in = D_01E03EC0_b467;
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

/* shape b467:01E03430 (b467), 628 insns, 1 copy: b467 scene manager (b147:01E022B0 form): code >= 0 clears the scene
   (0x2A30), resets four coords, keeps eight joints, a 150-tick timer, a 256-entry random table, a spot disc, a ring
   (LkSetRing 0.1/12/14), a light (LkSetLight 2.0), the random-particle wave, two sword trails and the exhaust
   emitter; otherwise steps the trails before 106, aims the ring camera at joints 0/1, adds exhaust puffs at ticks
   55/66/77/79, from 106 draws wave, disc and light and grows their cameras, draws the trails from 25 (fading in, out
   from 106), the exhaust before 96 (then fades its parts), the ring 90..105; returns 2 at 130, 1 at 96, 6 in
   106..129, 8 when the timer ends */

typedef struct {
    Vec4f scale;
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b467_01E03430;

typedef struct {
    Obj_b025_01E00910 o;
    u8 pad[8];
} Sw_b467_01E03430;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 pad[3];
} Part_b467_01E03430;

typedef struct {
    void *texture;
    u8 b, g, r, a;
    s32 flags;
    Part_b467_01E03430 *parts;
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
    Part_b467_01E03430 pts[0x120];
} Exh_b467_01E03430;

typedef struct {
    s32 kind;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x448];
} Light_b467_01E03430;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_b467_01E03430;

typedef struct {
    Crd_b467_01E03430 cam0;
    Sw_b467_01E03430 sw[2];
    Exh_b467_01E03430 exh;
    Crd_b467_01E03430 cam1;
    Light_b467_01E03430 light;
    Disc_b540_01E00250 disc;
    Crd_b467_01E03430 cam2;
    Ring_b467_01E03430 ring;
    Crd_b467_01E03430 cam3;
    u8 pad1EE0[0x2F0];
    Wave_b025_01E016F0 wave;
    s32 timer;
    s32 t;
    s32 code;
    s32 j[8];
    Vec4f tr[4][28];
    s8 tab[256];
    u8 pad2A2C[4];
} Scene_b467_01E03430;

static s32 func_01E03430_b467(s32 arg0, s32 code) {
    Scene_b467_01E03430 *g = (Scene_b467_01E03430 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern s32 func_0019A5C8();
    s32 ot;
    Vec4f u[2];
    Vec4f v[2];
    Vec4f w[2];
    Vec4f p;
    s32 tx[4];
    s32 i;
    s32 k;
    s32 l;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2A30);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        g->j[0] = func_001F5560(func_001F53A0(), 0x14, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x1D, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x25, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x20, 0);
        g->j[6] = func_001F5560(func_001F53A0(), 0x39, 0);
        g->j[7] = func_001F5560(func_001F53A0(), 0x2D, 0);
        g->timer = 0x96;
        g->t = 1;
        g->code = code;
        for (i = 0; i < 256; i++) {
            g->tab[i] = func_0019A5C8() >> 4;
        }
        g->disc.flags = 0x80000;
        g->disc.r = 0xD0;
        g->disc.g = 0xA0;
        g->disc.b = 0x70;
        g->disc.a = 0x80;
        g->disc.radius = 30.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        func_00103260(tx, 0xF);
        g->ring.flags = 0;
        g->ring.u = 0x8E;
        g->ring.v = 0;
        g->ring.w = 0x20;
        g->ring.h = 0x40;
        g->ring.r = 0xD0;
        g->ring.g = 0xD0;
        g->ring.b = 0x70;
        g->ring.a = 0x20;
        func_01E00250_b467((Ring_b001_01E035A0 *)&g->ring, tx[0], 0.1f, 12.0f, 0.0f, 14.0f);
        g->light.flags = 0x80001;
        g->light.u = 0x8E;
        g->light.v = 0;
        g->light.w = 0x22;
        g->light.h = 0x40;
        g->light.r = 0xD0;
        g->light.g = 0xA0;
        g->light.b = 0x70;
        g->light.a = 0x20;
        func_01E020B0_b467((Obj_b000_01E032C0 *)&g->light, tx[0], 2.0f);
        g->wave.texture = (void *)tx[0];
        g->wave.tab = g->tab;
        g->wave.flags = 0x20000000;
        g->wave.u = 0xB0;
        g->wave.v = 0x40;
        g->wave.w = 0x20;
        g->wave.h = 0x20;
        g->wave.bA = 0x80;
        g->wave.b9 = 0x80;
        g->wave.b8 = 0x80;
        g->wave.bB = 0xFF;
        g->wave.size = 1.6f;
        g->wave.amp = 0.03f;
        g->wave.frame = 0;
        g->wave.count = 0x100;
        g->wave.phase = 7;
        g->sw[0].o.texture = (void *)tx[0];
        g->sw[0].o.flags = 1;
        g->sw[0].o.max = 8;
        g->sw[0].o.r.i.u = 0x8E;
        g->sw[0].o.r.i.v = 0x54;
        g->sw[0].o.r.i.w = 0x20;
        g->sw[0].o.r.i.h = 1;
        g->sw[0].o.col.r = 0xD0;
        g->sw[0].o.col.g = 0xD0;
        g->sw[0].o.col.b = 0x70;
        g->sw[0].o.col.a = 0;
        g->sw[0].o.p1 = g->tr[2];
        g->sw[0].o.p2 = g->tr[3];
        func_001F5620(func_001F53A0(), g->j[4], &v[0]);
        func_001F5620(func_001F53A0(), g->j[5], &v[1]);
        for (k = 0; k < 8; k++) {
            g->sw[0].o.a[k].x = v[0].x;
            g->sw[0].o.a[k].y = v[0].y;
            g->sw[0].o.a[k].z = v[0].z;
            g->sw[0].o.b[k].x = v[1].x;
            g->sw[0].o.b[k].y = v[1].y;
            g->sw[0].o.b[k].z = v[1].z;
        }
        g->sw[0].o.len = 0;
        g->sw[1].o.texture = (void *)tx[0];
        g->sw[1].o.flags = 1;
        g->sw[1].o.max = 8;
        g->sw[1].o.r.i.u = 0x8E;
        g->sw[1].o.r.i.v = 0x54;
        g->sw[1].o.r.i.w = 0x20;
        g->sw[1].o.r.i.h = 1;
        g->sw[1].o.col.r = 0xD0;
        g->sw[1].o.col.g = 0xD0;
        g->sw[1].o.col.b = 0x70;
        g->sw[1].o.col.a = 0;
        g->sw[1].o.p1 = g->tr[0];
        g->sw[1].o.p2 = g->tr[1];
        func_001F5620(func_001F53A0(), g->j[2], &w[0]);
        func_001F5620(func_001F53A0(), g->j[3], &w[1]);
        for (l = 0; l < 8; l++) {
            g->sw[1].o.a[l].x = w[0].x;
            g->sw[1].o.a[l].y = w[0].y;
            g->sw[1].o.a[l].z = w[0].z;
            g->sw[1].o.b[l].x = w[1].x;
            g->sw[1].o.b[l].y = w[1].y;
            g->sw[1].o.b[l].z = w[1].z;
        }
        g->sw[1].o.len = 0;
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
        g->cam2.scale.x = g->cam2.scale.y = g->cam2.scale.z = 0.0f;
        g->cam3.scale.x = g->cam3.scale.y = g->cam3.scale.z = 0.1f;
        return 0;
    }
    if (g->t < 0x6A) {
        g->sw[0].o.max = g->sw[1].o.max = 8;
        func_001F5620(func_001F53A0(), g->j[4], &v[0]);
        func_001F5620(func_001F53A0(), g->j[5], &v[1]);
        func_001F5620(func_001F53A0(), g->j[2], &w[0]);
        func_001F5620(func_001F53A0(), g->j[3], &w[1]);
        func_01E00A00_b467((Trail_b025_01E007C0 *)&g->sw[0], &v[0], &v[1]);
        func_01E00A00_b467((Trail_b025_01E007C0 *)&g->sw[1], &w[0], &w[1]);
    }
    func_001F5620(func_001F53A0(), g->j[0], &g->cam2.pos);
    func_001F5620(func_001F53A0(), g->j[0], &u[0]);
    func_001F5620(func_001F53A0(), g->j[1], &u[1]);
    func_00103DB0(&u[1], &u[0], &g->cam2.rot);
    if (g->t == 0x6A) {
        func_001F5F90(func_001F5380(), &g->cam1.pos);
        func_001F5F90(func_001F5380(), &g->cam3.pos);
    }
    if (g->t == 0x42 || g->t == 0x4F) {
        func_001F5620(func_001F53A0(), g->j[7], &p);
        func_01E02820_b467((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&p);
    }
    if (g->t == 0x37 || g->t == 0x4D) {
        func_001F5620(func_001F53A0(), g->j[6], &p);
        func_01E02820_b467((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&p);
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001038D0(&g->cam2);
    func_001039A0(&g->cam3);
    func_01E00120_b467();
    if (g->t >= 0x6A) {
        func_01E018B0_b467(ot, (Wave_b025_01E016F0 *)&g->wave, (Cam_b025_01E016F0 *)&g->cam3);
        func_00103470(&g->wave.bB, 0, 0x10);
        func_01E01350_b467(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->cam1);
        func_00103470(&g->disc.a, 0, 8);
        func_01E02210_b467(ot, (Spr_b000_01E03420 *)&g->light, (Cam_b000_01E03420 *)&g->cam1);
        func_00103470(&g->light.a, 0, 2);
        {
            f32 q = 0.2f;
            func_001033D0(&g->cam1, 3.0f, q);
        }
        {
            f32 q = 0.1f;
            f32 r = 0.3f;
            func_001033D0(&g->cam3, r, q);
        }
    }
    if (g->t >= 0x19) {
        func_01E00B50_b467(&g->sw[0].o, (Cam_b025_01E00910 *)&g->cam0);
        func_01E00B50_b467(&g->sw[1].o, (Cam_b025_01E00910 *)&g->cam0);
        if (g->t < 0x6A) {
            func_001032C0(&g->sw[0].o.col.a, 0xF0, 0x10);
            func_001032C0(&g->sw[1].o.col.a, 0xF0, 0x10);
        } else {
            func_00103470(&g->sw[0].o.col.a, 0, 0x10);
            func_00103470(&g->sw[1].o.col.a, 0, 0x10);
        }
    }
    if (g->t < 0x60) {
        func_01E02A20_b467(ot, (Em_b013_01E02BE0 *)&g->exh, (Cam_b013_01E02BE0 *)&g->cam0);
        for (k = 0; k < g->exh.n1; k++) {
            for (i = 0; i < g->exh.mult; i++) {
                func_00103470(&g->exh.pts[k * g->exh.mult + i].a, 0, 3);
            }
        }
    }
    if (g->t >= 0x5A && g->t < 0x6A) {
        func_01E00510_b467(ot, (Ring_b001_01E03860 *)&g->ring, (Cam_b001_01E03860 *)&g->cam2);
        func_001033D0(&g->cam2, 2.0f, 0.2f);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x82) {
        return 2;
    }
    if (g->t == 0x60) {
        return 1;
    }
    if (g->t >= 0x6A && g->t < 0x82) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
