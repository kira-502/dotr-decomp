#include "common.h"

/* shape c555:01E00080, 40 insns: colour three vertices of a packet from a (b, g, r, a) colour, q 1.0, alpha dimmed
   by 4/8, 7/8 and 8/8 of a eighth steps (a - (a >> 3) * 4, * 7, * 8); clear the three vertices' top xyz bytes */

typedef struct {
    u8 b, g, r, a;
} Col_c555_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c555_01E00080;

typedef struct {
    u8 head[0x10];
    Vtx_c555_01E00080 v[3];
} Pkt_c555_01E00080;

static void func_01E00080_c555(Pkt_c555_01E00080 *p, Col_c555_01E00080 *c) {
    s32 s;

    s = c->a >> 3;
    p->v[0].r = c->r;
    p->v[0].g = c->g;
    p->v[0].b = c->b;
    p->v[0].a = c->a - s * 4;
    p->v[0].q = 1.0f;
    p->v[1].r = c->r;
    p->v[1].g = c->g;
    p->v[1].b = c->b;
    p->v[1].a = c->a - s * 7;
    p->v[1].q = 1.0f;
    p->v[2].r = c->r;
    p->v[2].g = c->g;
    p->v[2].b = c->b;
    p->v[2].a = c->a - s * 8;
    p->v[2].q = 1.0f;
    p->v[0].f = 0;
    p->v[1].f = 0;
    p->v[2].f = 0;
}

/* shape c555:01E00120, 56 insns: colour four vertices of a packet from a (b, g, r, a) colour, q 1.0: the first two
   dimmed by k eighths of the alpha (0 when k is 0), the last two by k + 1 eighths */

typedef struct {
    u8 b, g, r, a;
} Col_c555_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 xyz;
} Vtx_c555_01E00120;

typedef struct {
    u8 head[0x10];
    Vtx_c555_01E00120 v[4];
} Pkt_c555_01E00120;

static void func_01E00120_c555(Pkt_c555_01E00120 *p, Col_c555_01E00120 *c, s32 k) {
    s32 s;
    u8 t;

    s = c->a >> 3;
    p->v[0].r = c->r;
    p->v[0].g = c->g;
    p->v[0].b = c->b;
    if (k == 0) {
        p->v[0].a = 0;
    } else {
        p->v[0].a = c->a - k * s;
    }
    p->v[0].q = 1.0f;
    p->v[1].r = c->r;
    p->v[1].g = c->g;
    p->v[1].b = c->b;
    if (k == 0) {
        p->v[1].a = 0;
    } else {
        p->v[1].a = c->a - k * s;
    }
    p->v[1].q = 1.0f;
    p->v[2].r = c->r;
    p->v[2].g = c->g;
    p->v[2].b = c->b;
    t = s + k * s;
    p->v[2].a = c->a - t;
    p->v[2].q = 1.0f;
    p->v[3].r = c->r;
    p->v[3].g = c->g;
    p->v[3].b = c->b;
    p->v[3].a = c->a - t;
    p->v[3].q = 1.0f;
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

static void func_01E00200_c555(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b000:01E00400, 87 insns, 46 copies: one flat-coloured full-screen quad (GS sprite packet, far z). The tag
   is written through a pointer that went through u32 (a plain &pk gets folded into $sp offsets). */

typedef struct Xyz_b000_01E00400 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b000_01E00400;

typedef struct Pk_b000_01E00400 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E00400 v[4];
} Pk_b000_01E00400;

typedef struct Src_b000_01E00400 {
    u8 b, g, r, a;
} Src_b000_01E00400;

static inline void b000_01E00400_tag(Pk_b000_01E00400 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E002A0_c555(s32 arg0, Src_b000_01E00400 *c) {
    Pk_b000_01E00400 pk;

    b000_01E00400_tag((Pk_b000_01E00400 *)(u32)&pk, 5, 4, 0x44441);
    func_002086D0((Pk_b000_01E00400 *)(u32)&pk, ((u64)0x80 << 32) | 0x48);
    pk.r = c->r;
    pk.g = c->g;
    pk.b = c->b;
    pk.a = c->a;
    pk.q = 1.0f;
    pk.v[0].x = 0x6000;
    pk.v[0].y = 0x7000;
    pk.v[0].z = 0xFFFFFF;
    pk.v[0].fog = 0;
    pk.v[1].x = 0xA000;
    pk.v[1].y = 0x7000;
    pk.v[1].z = 0xFFFFFF;
    pk.v[1].fog = 0;
    pk.v[2].x = 0x6000;
    pk.v[2].y = 0x9000;
    pk.v[2].z = 0xFFFFFF;
    pk.v[2].fog = 0;
    pk.v[3].x = 0xA000;
    pk.v[3].y = 0x9000;
    pk.v[3].z = 0xFFFFFF;
    pk.v[3].fog = 0;
    func_002075F0((s32)&pk, arg0, 0);
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

extern void c555_01E00200(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E00400_c555(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c555_01E00200(&pkt, &sp->color);
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

static s32 func_01E009E0_c555(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00200_c555) and needs that helper
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

static s32 func_01E00CA0_c555(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00200_c555(&pkt, &ring->color);
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

static s32 func_01E01190_c555(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00200_c555((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* shape c555:01E01D20 (LkSortFiretail4), 531 insns, 1 copy: a fire tail along the 8-point history
   (shifted in from pos): per segment two points at +-width * (8 - i) / 8 across the segment frame rolled by o->roll,
   segments 0..5 as quads (alpha dimmed by eighths), the last as a triangle to hist[7] */

typedef struct {
    f32 x, y, z, w;
} Vec_c555_01E01D20;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c555_01E01D20;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_c555_01E01D20 p;
} Vtx_c555_01E01D20;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c555_01E01D20 v[3];
    u64 tail;
} Tri_c555_01E01D20;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c555_01E01D20 v[4];
    u64 tail;
} Quad_c555_01E01D20;

typedef struct {
    Vec_c555_01E01D20 hist[8];
    s32 flags;
    f32 width;
    u8 b, g, r, a;
    s32 roll;
} Tail_c555_01E01D20;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c555_01E01D20;

static s32 func_01E01D20_c555(s32 ot __attribute__((aligned(8))), Tail_c555_01E01D20 *o, Cam_c555_01E01D20 *cam, Vec_c555_01E01D20 *pos) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020CBD0();
    f32 m[16];
    Vec_c555_01E01D20 u[1];
    Vec_c555_01E01D20 p[1];
    Vec_c555_01E01D20 v[1];
    s32 cr[4];
    s32 rot[4];
    f32 d[4];
    Quad_c555_01E01D20 quad __attribute__((aligned(8)));
    Tri_c555_01E01D20 tri __attribute__((aligned(8)));
    s32 i;

    for (i = 6; i > -1; i--) {
        o->hist[i + 1] = o->hist[i];
        if (i == 0) {
            o->hist[i].x = pos->x;
            o->hist[i].y = pos->y;
            o->hist[i].z = pos->z;
        }
    }
    ((Quad_c555_01E01D20 *)(s32)&quad)->count = 0x14;
    ((Quad_c555_01E01D20 *)(s32)&quad)->tag = 8;
    ((Quad_c555_01E01D20 *)(s32)&quad)->regs = 0x41414141;
    ((Quad_c555_01E01D20 *)(s32)&quad)->pad = 0;
    ((Tri_c555_01E01D20 *)(s32)&tri)->count = 0x13;
    ((Tri_c555_01E01D20 *)(s32)&tri)->tag = 6;
    ((Tri_c555_01E01D20 *)(s32)&tri)->regs = 0x414141;
    ((Tri_c555_01E01D20 *)(s32)&tri)->pad = 0;
    func_002086D0(&quad, ((u64)0x80 << 32) | 0x48);
    func_002086D0(&tri, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 6; i++) {
        func_01E00120_c555((Pkt_c555_01E00120 *)&quad, (Col_c555_01E00120 *)&o->b, i);

        v[0].x = o->hist[i + 1].x - o->hist[i].x;
        v[0].y = o->hist[i + 1].y - o->hist[i].y;
        v[0].z = o->hist[i + 1].z - o->hist[i].z;
        v[0].w = 0.0f;
        func_00103B50(&v[0].x, rot);
        func_001FAFB0(0, (s32)cr);
        cr[1] %= 0x10000;
        func_00103D00(rot[0], cr[0]);
        func_00103D00(rot[1], cr[1]);
        u[0].x = o->width / 8.0f * (8 - i);
        u[0].w = 0.0f;
        u[0].z = 0.0f;
        u[0].y = 0.0f;
        func_0020C630(m, rot);
        func_0020CDD0(&p[0], m, &u[0]);
        func_0020CBD0(m, &v[0], o->roll);
        func_0020CDD0(&u[0], m, &p[0]);
        p[0].x = u[0].x + o->hist[i].x;
        p[0].y = u[0].y + o->hist[i].y;
        p[0].z = u[0].z + o->hist[i].z;
        if (func_00205440(&p[0], cam->view, &quad.v[0].p, &d[0]) != 0) {
            o->flags |= 0x100000;
        }
        p[0].x = o->hist[i].x - u[0].x;
        p[0].y = o->hist[i].y - u[0].y;
        p[0].z = o->hist[i].z - u[0].z;
        if (func_00205440(&p[0], cam->view, &quad.v[1].p, &d[1]) != 0) {
            o->flags |= 0x200000;
        }

        v[0].x = o->hist[i + 2].x - o->hist[i + 1].x;
        v[0].y = o->hist[i + 2].y - o->hist[i + 1].y;
        v[0].z = o->hist[i + 2].z - o->hist[i + 1].z;
        v[0].w = 0.0f;
        func_00103B50(&v[0].x, rot);
        func_001FAFB0(0, (s32)cr);
        cr[1] %= 0x10000;
        func_00103D00(rot[0], cr[0]);
        func_00103D00(rot[1], cr[1]);
        u[0].x = o->width / 8.0f * (7 - i);
        u[0].w = 0.0f;
        u[0].z = 0.0f;
        u[0].y = 0.0f;
        func_0020C630(m, rot);
        func_0020CDD0(&p[0], m, &u[0]);
        func_0020CBD0(m, &v[0], o->roll);
        func_0020CDD0(&u[0], m, &p[0]);
        p[0].x = u[0].x + o->hist[i + 1].x;
        p[0].y = u[0].y + o->hist[i + 1].y;
        p[0].z = u[0].z + o->hist[i + 1].z;
        if (func_00205440(&p[0], cam->view, &quad.v[2].p, &d[2]) != 0) {
            o->flags |= 0x400000;
        }
        p[0].x = o->hist[i + 1].x - u[0].x;
        p[0].y = o->hist[i + 1].y - u[0].y;
        p[0].z = o->hist[i + 1].z - u[0].z;
        if (func_00205440(&p[0], cam->view, &quad.v[3].p, &d[3]) != 0) {
            o->flags |= 0x800000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
            func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
            func_002075F0(&quad, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
        }
        o->flags &= 0xFF0FFFFF;
    }

    func_01E00080_c555((Pkt_c555_01E00080 *)&tri, (Col_c555_01E00080 *)&o->b);
    v[0].x = o->hist[7].x - o->hist[6].x;
    v[0].y = o->hist[7].y - o->hist[6].y;
    v[0].z = o->hist[7].z - o->hist[6].z;
    v[0].w = 0.0f;
    func_00103B50(&v[0].x, rot);
    func_001FAFB0(0, (s32)cr);
    cr[1] %= 0x10000;
    func_00103D00(rot[0], cr[0]);
    func_00103D00(rot[1], cr[1]);
    u[0].x = o->width / 8.0f * 2.0f;
    u[0].w = 0.0f;
    u[0].z = 0.0f;
    u[0].y = 0.0f;
    func_0020C630(m, rot);
    func_0020CDD0(&p[0], m, &u[0]);
    func_0020CBD0(m, &v[0], o->roll);
    func_0020CDD0(&u[0], m, &p[0]);
    p[0].x = o->hist[6].x + u[0].x;
    p[0].y = o->hist[6].y + u[0].y;
    p[0].z = o->hist[6].z + u[0].z;
    if (func_00205440(&u[0], cam->view, &tri.v[0].p, &d[0]) != 0) {
        o->flags |= 0x100000;
    }
    p[0].x = o->hist[6].x - u[0].x;
    p[0].y = o->hist[6].y - u[0].y;
    p[0].z = o->hist[6].z - u[0].z;
    if (func_00205440(&u[0], cam->view, &tri.v[1].p, &d[1]) != 0) {
        o->flags |= 0x200000;
    }
    if (func_00205440(&o->hist[7], cam->view, &tri.v[2].p, &d[2]) != 0) {
        o->flags |= 0x400000;
    }
    if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
        func_00104520(o->flags, 0x16) != 0) {
        func_002075F0(&tri, ot, (u32)((d[2] + (d[0] + d[1])) / 3.0f));
    }
    o->flags &= 0xFF0FFFFF;
    return 0;
}

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c555:01E02570, 209 insns: b049:01E02690's flat quad for one object: dull red corners (alpha 0x20, the
   second 0x80), the object's 4 corner points turned by its z angle (0x8) and moved to its position (z only for
   the first), drawn into the given list when all 4 project */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 xyz;
} Vtx_c555_01E02570;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c555_01E02570 v[4];
    u8 tail[8];
} Pkt_c555_01E02570;

typedef struct {
    u8 pad0[4];
    s32 flags;
    s32 rz;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    Vec4f v[4];
} Obj_c555_01E02570;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c555_01E02570;

static s32 func_01E02570_c555(s32 ot, Obj_c555_01E02570 *o, Cam_c555_01E02570 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    f32 dep[4];
    f32 m[16];
    Vec4f p;
    s32 rot[4];
    Pkt_c555_01E02570 pkt __attribute__((aligned(8)));

    ((Pkt_c555_01E02570 *)(s32)&pkt)->count = 0x14;
    ((Pkt_c555_01E02570 *)(s32)&pkt)->tag = 8;
    ((Pkt_c555_01E02570 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_c555_01E02570 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    pkt.v[0].r = 0x80;
    pkt.v[0].g = 0x50;
    pkt.v[0].b = 0x50;
    pkt.v[0].a = 0x20;
    pkt.v[0].q = 1.0f;
    pkt.v[1].r = 0x80;
    pkt.v[1].g = 0x50;
    pkt.v[1].b = 0x50;
    pkt.v[1].a = 0x80;
    pkt.v[1].q = 1.0f;
    pkt.v[2].r = 0x80;
    pkt.v[2].g = 0x50;
    pkt.v[2].b = 0x50;
    pkt.v[2].a = 0x20;
    pkt.v[2].q = 1.0f;
    pkt.v[3].r = 0x80;
    pkt.v[3].g = 0x50;
    pkt.v[3].b = 0x50;
    pkt.v[3].a = 0x20;
    pkt.v[3].q = 1.0f;
    rot[0] = rot[1] = 0;
    rot[2] = o->rz;
    func_0020C630(m, rot);
    func_0020CDD0(&p, m, &o->v[0]);
    p.x += o->x;
    *(f32 *)(u32)&p.y += o->y;
    p.z += o->z;
    if (func_00205440(&p, cam->view, &pkt.v[0].xyz, &dep[0]) != 0) {
        o->flags |= 0x100000;
    }
    func_0020CDD0(&p, m, &o->v[1]);
    p.x += o->x;
    *(f32 *)(u32)&p.y += o->y;
    if (func_00205440(&p, cam->view, &pkt.v[1].xyz, &dep[1]) != 0) {
        o->flags |= 0x200000;
    }
    func_0020CDD0(&p, m, &o->v[2]);
    p.x += o->x;
    *(f32 *)(u32)&p.y += o->y;
    if (func_00205440(&p, cam->view, &pkt.v[2].xyz, &dep[2]) != 0) {
        o->flags |= 0x400000;
    }
    func_0020CDD0(&p, m, &o->v[3]);
    p.x += o->x;
    *(f32 *)(u32)&p.y += o->y;
    if (func_00205440(&p, cam->view, &pkt.v[3].xyz, &dep[3]) != 0) {
        o->flags |= 0x800000;
    }
    if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0 &&
        func_00104520(o->flags, 0x16) != 0 && func_00104520(o->flags, 0x17) != 0) {
        func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
    }
    o->flags &= 0xFF0FFFFF;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c555", func_01E028C0_c555);
