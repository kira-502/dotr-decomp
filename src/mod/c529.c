#include "common.h"

/* shape b000:01E00080, 31 insns, 12 copies: colour the two vertices of a line packet; mode 0 = colour on the
   first vertex (second black), else on the second (first black); alpha and q = 1.0 on both */

typedef struct Src_b000_01E00080 {
    u8 b, g, r, a;
} Src_b000_01E00080;

typedef struct Xyz_b000_01E00080 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E00080;

typedef struct Vtx_b000_01E00080 {
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00080 p;
} Vtx_b000_01E00080;

typedef struct Pk_b000_01E00080 {
    u8 head[0x10];
    Vtx_b000_01E00080 v[2];
} Pk_b000_01E00080;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00080_c529(Pk_b000_01E00080 *p, Src_b000_01E00080 *s, s32 mode) {
    if (mode == 0) {
        p->v[0].r = s->r;
        p->v[0].g = s->g;
        p->v[0].b = s->b;
        p->v[1].r = 0;
        p->v[1].g = 0;
        p->v[1].b = 0;
    } else {
        p->v[0].r = 0;
        p->v[0].g = 0;
        p->v[0].b = 0;
        p->v[1].r = s->r;
        p->v[1].g = s->g;
        p->v[1].b = s->b;
    }
    p->v[0].a = s->a;
    p->v[0].q = 1.0f;
    p->v[1].a = s->a;
    p->v[1].q = 1.0f;
    p->v[0].p.f = 0;
    p->v[1].p.f = 0;
}

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

static void func_01E00100_c529(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c505:01E003D0, 298 insns: draws the two quads of a 2-part strip (shape family of b001:01E03860): colour
   from the module's colour helper (shape b000:01E00100, static copy below), per-quad setup by func_00105830,
   corners p[1] or p[0], p[i + 2], p[i * 5], p[i + 3]; texture rect unless flag 0x18; far z under flag 0x13. */

typedef struct {
    u8 b, g, r, a;
} Src_c505_01E003D0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c505_01E003D0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c505_01E003D0 v[4];
    u8 tail[0x20];
} Pkt_c505_01E003D0;

typedef struct {
    s16 u, v, w, h;
    u8 pad8[0x2C];
    Src_c505_01E003D0 color;
    s32 flags;
} Def_c505_01E003D0;

typedef struct {
    void *texture;
    s32 flags;
    u8 pad8[0x18];
    Vec4f p[8];
} Obj_c505_01E003D0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c505_01E003D0;

static s32 func_01E001A0_c529(s32 ot, Def_c505_01E003D0 *d, Obj_c505_01E003D0 *o, Cam_c505_01E003D0 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00105830(void *, void *, s32);
    f32 depth[4];
    Pkt_c505_01E003D0 pkt;
    s32 i;

    ((Pkt_c505_01E003D0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c505_01E003D0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c505_01E003D0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c505_01E003D0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(d->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(d->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_c529(&pkt, &d->color);
    for (i = 0; i < 2; i++) {
        func_00105830(&pkt, d, i);
        if (i == 0) {
            if (func_00205440(&o->p[1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                o->flags |= 0x100000;
            }
        } else {
            if (func_00205440(&o->p[0], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                o->flags |= 0x100000;
            }
        }
        if (func_00205440(&o->p[i + 2], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00205440(&o->p[i * 5], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            o->flags |= 0x400000;
        }
        if (func_00205440(&o->p[i + 3], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(d->flags, 0x18) != 0) {
            func_00208700(&pkt, o->texture, 0);
        } else {
            if (func_00104520(d->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)d->u << 4) | ((u64)(d->u + d->w - 1) << 14) |
                                        ((u64)d->v << 24) | ((u64)(d->v + d->h - 1) << 34));
            }
            func_00208700(&pkt, o->texture, 1);
        }
        if (func_00104520(d->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, ot, 0);
        } else if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
                   func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_002075F0(&pkt, ot, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
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

extern void c529_01E00100(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E00650_c529(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c529_01E00100(&pkt, &sp->color);
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

static s32 func_01E00C30_c529(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00100_c529) and needs that helper
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

static s32 func_01E00EF0_c529(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00100_c529(&pkt, &ring->color);
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

/* shape b000:01E04EC0, 148 insns, 12 copies: seed n points with random positions: flag 0x1D set and v < 0:
   +-50 / +-50 / 0..50, flag set and v >= 0: +-240 / +-240 / 240..480, flag clear: tenths of +-240 / 0..240 */

typedef struct Pt_b000_01E04EC0 {
    f32 x, y, z, w;
} Pt_b000_01E04EC0;

typedef struct Obj_b000_01E04EC0 {
    s32 flags;
    u8 pad4[4];
    f32 f8;
    s32 count;
    Pt_b000_01E04EC0 pts[1];
} Obj_b000_01E04EC0;

static s32 func_01E013E0_c529(Obj_b000_01E04EC0 *o, s32 n, f32 v) {
    extern f32 func_001A6970(f32);
    extern s32 func_0019A5C8();
    s32 i;

    o->f8 = func_001A6970(v);
    o->count = n;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (v < 0.0f) {
                o->pts[i].x = func_0019A5C8() % 100 - 50;
                o->pts[i].y = func_0019A5C8() % 100 - 50;
                o->pts[i].z = func_0019A5C8() % 50;
            } else {
                o->pts[i].x = func_0019A5C8() % 480 - 240;
                o->pts[i].y = func_0019A5C8() % 480 - 240;
                o->pts[i].z = func_0019A5C8() % 240 + 240;
            }
        } else {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
    }
    return 0;
}

/* shape b000:01E05110, 344 insns, 12 copies: draws falling streaks (rain/snow): each point is drawn as a line
   from it along its normalised direction, then moved; points that fall past the floor are reseeded (the two
   ranges of b000:01E04EC0); drawn twice with flag 0x1C. Calls the module's line colour helper (b000:01E00080),
   included above as a static function. */

typedef struct Pt_b000_01E05110 {
    f32 x, y, z, w;
} Pt_b000_01E05110;

typedef struct Obj_b000_01E05110 {
    s32 flags;
    Src_b000_01E00080 color;
    f32 len;
    s32 count;
    Pt_b000_01E05110 pts[1];
} Obj_b000_01E05110;

typedef struct Cam_b000_01E05110 {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E05110;

typedef struct LPk_b000_01E05110 {
    s16 size;
    s16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b000_01E00080 v[2];
} LPk_b000_01E05110;

static s32 func_01E01630_c529(s32 obj, Obj_b000_01E05110 *o, Cam_b000_01E05110 *cam, f32 v) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020D070();
    extern s32 func_0019A5C8();
    Vec4f a;
    Vec4f b;
    LPk_b000_01E05110 pk;
    f32 depth[2];
    s32 i;

    ((LPk_b000_01E05110 *)(s32)&pk)->flags = 0x11;
    ((LPk_b000_01E05110 *)(s32)&pk)->size = 4;
    ((LPk_b000_01E05110 *)(s32)&pk)->regs = 0x4141;
    ((LPk_b000_01E05110 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < o->count; i++) {
        if (!(v < 0.0f)) {
            func_01E00080_c529((Pk_b000_01E00080 *)&pk, &o->color, 0);
        } else {
            func_01E00080_c529((Pk_b000_01E00080 *)&pk, &o->color, 1);
        }
        a.x = b.x = o->pts[i].x;
        a.y = b.y = o->pts[i].y;
        a.z = b.z = o->pts[i].z;
        if (func_00205440(&a, cam->view, &pk.v[0].p, &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        func_0020D070(&a);
        b.x += a.x * o->len;
        b.y += a.y * o->len;
        b.z += a.z * o->len;
        if (func_00205440(&b, cam->view, &pk.v[1].p, &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        o->pts[i].x -= a.x * v;
        o->pts[i].y -= a.y * v;
        o->pts[i].z -= a.z * v;
        if (func_00104520(o->flags, 0x1D) != 0) {
            if (!(o->pts[i].z < 300.0f)) {
                o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].y = 0.1f * (func_0019A5C8() % 480 - 240);
                o->pts[i].z = 0.1f * (func_0019A5C8() % 240);
            }
        } else if (o->pts[i].y <= 0.0f) {
            o->pts[i].x = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].z = 0.1f * (func_0019A5C8() % 480 - 240);
            o->pts[i].y = 0.1f * (func_0019A5C8() % 240);
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pk.v[0].p.z = pk.v[1].p.z = 0xFFFFFF;
                func_002075F0(&pk, obj, 0);
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, 0);
                }
            } else {
                func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                if (func_00104520(o->flags, 0x1C) != 0) {
                    func_002075F0(&pk, obj, func_001A23B0((depth[0] + depth[1]) / 2.0f));
                }
            }
        }
        o->flags &= 0xFF0FFFFF;
    }
    return 0;
}

/* shape c529:01E01B90 (c529), 478 insns, 1 copy: the c529 module main: on start clears the 0xDC0 scene (timer 30),
   four cameras, a 60-point spark (texture 15, size 1.5), a ring (0.1/30, y 2, height 6), 64 falling streaks (20), an
   outline source and an inlined 6-corner billboard (template * 15); each tick steps the cameras and draws the streaks
   (fading in to 0xA0 for 16 ticks, then out), the strip until tick 23 (camera to 1, blinking alpha), then from tick
   21 the ring and the sparks, growing by 0.2 up to 1 then 0.05; 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Col_c529_01E01B90;

typedef struct {
    f32 x, y, z;
    u8 padC[0x14];
    u8 pos[0x50];
} Cam_c529_01E01B90;

typedef struct {
    f32 x, y, z;
} Pt_c529_01E01B90;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c529_01E01B90 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_c529_01E01B90 pts[60];
} Spark_c529_01E01B90;

typedef struct {
    s32 flags;
    Col_c529_01E01B90 color;
    f32 len;
    s32 count;
    Vec4f pts[64];
} Rain_c529_01E01B90;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c529_01E01B90 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c529_01E01B90;

typedef struct {
    s32 id;
    u8 pad4[4];
    f32 scale;
    u8 padC[4];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[4];
    Vec4f v[6];
} Bb_c529_01E01B90;

typedef struct {
    Vec4f v[6];
} Six_c529_01E01B90;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c529_01E01B90 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c529_01E01B90;

typedef struct {
    Cam_c529_01E01B90 cam0;
    Cam_c529_01E01B90 cam1;
    Cam_c529_01E01B90 cam2;
    Cam_c529_01E01B90 cam3;
    Spark_c529_01E01B90 spark;
    Rain_c529_01E01B90 rain;
    Mdl_c529_01E01B90 mdl;
    Bb_c529_01E01B90 bb;
    Ring_c529_01E01B90 ring;
    f32 vel[3];
    u8 padDAC[4];
    s32 timer;
    s32 code;
    s32 t;
    u8 padDBC[4];
} Scene_c529_01E01B90;

static inline void bb_c529_01E01B90(Bb_c529_01E01B90 *out, s32 id, f32 size) {
    extern Six_c529_01E01B90 D_01E02380_c529;
    Six_c529_01E01B90 q;
    s32 i;

    q = D_01E02380_c529;
    out->f10 = out->f14 = out->f18 = 0;
    out->scale = size / 2.0f;
    out->id = id;
    for (i = 0; i < 6; i++) {
        out->v[i].x = out->scale * q.v[i].x;
        out->v[i].y = out->scale * q.v[i].y;
        out->v[i].z = out->scale * q.v[i].z;
    }
}

static s32 func_01E01B90_c529(s32 arg0, s32 code) {
    Scene_c529_01E01B90 *g = (Scene_c529_01E01B90 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_001039A0(void *);
    extern void func_001038D0(void *);
    extern void func_001F53B0(s32, void *);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xDC0);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        func_00103890(&g->cam3);
        g->timer = 30;
        g->code = code;
        g->t = 0;
        g->vel[0] = 1.05f;
        g->vel[1] = 1.05f;
        g->vel[2] = 1.05f;
        func_00103260(&tex, 0xF);
        g->spark.texture = tex;
        g->spark.size = 1.5f;
        for (i = 0; i < 60; i++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.pts[i].x = func_0019A5C8() % 100 - 50;
                g->spark.pts[i].z = func_0019A5C8() % 50;
                g->spark.pts[i].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.pts[i].x = func_0019A5C8() % 50 - 25;
                g->spark.pts[i].y = func_0019A5C8() % 25;
                g->spark.pts[i].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->spark.flags = 1;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0xA0;
        g->spark.color.b = 0xFF;
        g->spark.color.a = 0x80;
        g->ring.flags = 0x8000;
        g->ring.u = 0x8E;
        g->ring.v = 0;
        g->ring.w = 0x20;
        g->ring.h = 0x40;
        g->ring.color.r = 0x60;
        g->ring.color.g = 0x80;
        g->ring.color.b = 0xE0;
        g->ring.color.a = 0x80;
        { f32 h = 6.0f; func_01E00C30_c529((Ring_b001_01E035A0 *)&g->ring, tex, 0.1f, 30.0f, 2.0f, h); }
        g->rain.flags = 0x40000001;
        g->rain.color.r = 0x80;
        g->rain.color.g = 0xA0;
        g->rain.color.b = 0xFF;
        g->rain.color.a = 0;
        func_01E013E0_c529((Obj_b000_01E04EC0 *)&g->rain, 64, 20.0f);
        g->mdl.flags = 3;
        g->mdl.f30 = 1.0f;
        g->mdl.color.r = 0x60;
        g->mdl.color.g = 0x60;
        g->mdl.color.b = 0x80;
        g->mdl.color.a = 0;
        g->mdl.r[0] = 0xB2;
        g->mdl.r[1] = 0x60;
        g->mdl.r[2] = 0x20;
        g->mdl.r[3] = 0x20;
        g->mdl.r[4] = 0xB2;
        g->mdl.r[5] = 0x60;
        g->mdl.r[6] = 0x100;
        g->mdl.r[7] = 0x100;
        g->mdl.h48 = 0;
        g->mdl.h4A = 1;
        g->mdl.h4E = 2;
        g->mdl.h52 = 999;
        g->mdl.h50 = 0;
        g->mdl.h4C = g->mdl.h4E - 1U;
        bb_c529_01E01B90(&g->bb, tex, 30.0f);
        func_001F53B0(0, g->cam0.pos);
        func_001F53B0(0, g->cam1.pos);
        func_001F53B0(0, g->cam2.pos);
        func_001F53B0(0, g->cam3.pos);
        g->cam0.x = g->cam0.y = g->cam0.z = 0.1f;
        g->cam2.x = g->cam2.y = g->cam2.z = 0.1f;
        g->cam3.x = g->cam3.y = g->cam3.z = 0.1f;
        return 0;
    }
    func_001039A0(&g->cam0);
    func_001038D0(&g->cam1);
    func_001039A0(&g->cam2);
    func_001038D0(&g->cam3);
    func_01E01630_c529(ot, (Obj_b000_01E05110 *)&g->rain, (Cam_b000_01E05110 *)&g->cam1, 2.5f);
    if (g->t < 16) {
        if (g->rain.color.a < 0xA0) {
            g->rain.color.a += 0x20;
        } else {
            g->rain.color.a = 0xA0;
        }
    } else {
        if (g->rain.color.a > 0x20) {
            g->rain.color.a -= 0x20;
        } else {
            g->rain.color.a = 0;
        }
    }
    if (g->t < 23) {
        if (g->mdl.h52 == 0 || g->mdl.h52 == 999) {
            func_01E001A0_c529(ot, (Def_c505_01E003D0 *)&g->mdl, (Obj_c505_01E003D0 *)&g->bb,
                               (Cam_c505_01E003D0 *)&g->cam2);
        }
        if (g->cam2.x < 1.0f) {
            g->cam2.x += 0.05f;
            g->cam2.y += 0.05f;
            g->cam2.z += 0.05f;
            if (g->mdl.color.a < 0x80) {
                g->mdl.color.a += 4;
            } else {
                g->mdl.color.a = 0x80;
            }
        } else {
            g->cam2.x = 1.0f;
            g->cam2.y = 1.0f;
            g->cam2.z = 1.0f;
            if (g->t % 2 == 0) {
                g->mdl.color.a = 0x40;
            } else {
                g->mdl.color.a = 0x80;
            }
        }
    }
    if (g->t > 20) {
        func_01E00EF0_c529(ot, (Ring_b001_01E03860 *)&g->ring, (Cam_b001_01E03860 *)&g->cam3);
        if (g->ring.color.a > 16) {
            g->ring.color.a -= 16;
        } else {
            g->ring.color.a = 0;
        }
        if (g->cam3.x < 1.0f) {
            g->cam3.x += 0.2f;
            g->cam3.y += 0.2f;
            g->cam3.z += 0.2f;
        } else {
            g->cam3.x += 0.05f;
            g->cam3.y += 0.05f;
            g->cam3.z += 0.05f;
        }
        func_01E00650_c529(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)g, (s32)g->vel);
        if (g->spark.color.a > 16) {
            g->spark.color.a -= 16;
        } else {
            g->spark.color.a = 0;
        }
        if (g->cam0.x < 1.0f) {
            g->cam0.x += 0.2f;
            g->cam0.y += 0.2f;
            g->cam0.z += 0.2f;
        } else {
            g->cam0.x += 0.05f;
            g->cam0.y += 0.05f;
            g->cam0.z += 0.05f;
        }
    }
    g->t++;
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
