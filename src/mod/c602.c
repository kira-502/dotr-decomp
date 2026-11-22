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

static void func_01E00080_c602(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

extern void c602_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E00120_c602(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c602_01E00080(&pkt, &sp->color);
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

static s32 func_01E00700_c602(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c602) and needs that helper
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

static s32 func_01E009C0_c602(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c602(&pkt, &ring->color);
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

/* shape b087:01E03B30, 87 insns, 9 copies: set up a ribbon sprite object (scale, 4 corner offsets from a local
   table sized by the object's widths/heights, 16 or 64 evenly spread angles) */

typedef struct V4_b087_01E03B30 {
    f32 x, y, z, w;
} V4_b087_01E03B30;

typedef struct Rnd_b087_01E03B30 {
    s32 a, b, c, d;
} Rnd_b087_01E03B30;

typedef struct Obj_b087_01E03B30 {
    s32 kind;
    s32 model;
    s32 pad8;
    f32 scale;
    s32 pad10[4];
    f32 w0;
    f32 w1;
    f32 h0;
    f32 h1;
    V4_b087_01E03B30 v[4];
    Rnd_b087_01E03B30 r[64];
} Obj_b087_01E03B30;

typedef struct W_tbl_func_01E00EB0_c602 {
    V4_b087_01E03B30 v[4];
} W_tbl_func_01E00EB0_c602;

static s32 func_01E00EB0_c602(Obj_b087_01E03B30 *obj, s32 kind, f32 scale) {
    extern W_tbl_func_01E00EB0_c602 D_01E02A00_c602;
    W_tbl_func_01E00EB0_c602 tbl_w = D_01E02A00_c602;
    s32 flag;
    s32 n;
    s32 i;

    tbl_w.v[0].x = -obj->w0;
    tbl_w.v[0].y = obj->h0 + obj->h1;
    tbl_w.v[1].y = obj->h0 + obj->h1;
    tbl_w.v[2].x = -obj->w1;
    tbl_w.v[2].y = obj->h1;
    tbl_w.v[3].y = obj->h1;
    flag = func_00104520(obj->model, 0x1F);
    obj->scale = scale;
    obj->kind = kind;
    n = flag ? 0x10 : 0x40;
    for (i = 0; i < 4; i++) {
        obj->v[i].x = obj->scale * tbl_w.v[i].x;
        obj->v[i].y = obj->scale * tbl_w.v[i].y;
        obj->v[i].z = obj->scale * tbl_w.v[i].z;
    }
    for (i = 0; i < n; i++) {
        obj->r[i].b = 0x10000 / n * i;
    }
    return 0;
}

/* shape b087:01E03C90, 387 insns, 9 copies (b000:01E03420 with the corner list 16 bytes later): draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b087_01E03C90;

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
} Vtx_b087_01E03C90;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b087_01E03C90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b087_01E03C90 v[4];
    u8 tail[0x20];
} Pkt_b087_01E03C90;

typedef struct {
    f32 x, y, z, w;
} Vec_b087_01E03C90;

typedef struct {
    void *texture;
    s32 flags;
    Src_b087_01E03C90 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    u8 pad20[0x10];
    Vec_b087_01E03C90 p[4];
    Vec_b087_01E03C90 rot[1];
} Spr_b087_01E03C90;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b087_01E03C90;

static s32 func_01E01010_c602(s32 obj, Spr_b087_01E03C90 *spr, Cam_b087_01E03C90 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b087_01E03C90 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b087_01E03C90 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c602((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b087_01E03C90 *)(s32)&pkt)->count |= 0x800;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
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

/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape c602:01E01620, 510 insns: draws a 23 x 16 grid of textured tiles: each tile's alpha from a per-tile table,
   its texture cell (tw / 16 by th / 23) from (u0, v0), a square of half-size half around its point (z only under
   flag 0x1E, else additive blend when z > 0); the first tile also binds the object's texture (func_001DA7A0). */

typedef struct {
    u8 b, g, r, a;
} Src_c602_01E01620;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_c602_01E01620;

typedef struct {
    u64 v;
} Q_c602_01E01620;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_c602_01E01620 uv;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c602_01E01620;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c602_01E01620 v[4];
    u8 pad70[8];
    Q_c602_01E01620 t0, t1, t2;
} Pkt_c602_01E01620;

typedef struct {
    f32 x, y, z;
} Pt_c602_01E01620;

typedef struct {
    u8 pad0[4];
    s32 flags;
    f32 half;
    Src_c602_01E01620 col;
    s16 u, v;
    s16 tw, th;
    s16 u0, v0;
    u8 pad1C[4];
    Pt_c602_01E01620 pos[23][16];
    u8 pad1160[0x6C0];
    u8 alpha[23][16];
} Grid_c602_01E01620;

typedef struct {
    u8 pad0[0x60];
    Q_c602_01E01620 t0, t1, t2;
    u8 pad78[0x18];
    s32 f90;
} Obj_c602_01E01620;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c602_01E01620;

static s32 func_01E01620_c602(Obj_c602_01E01620 *o, Cam_c602_01E01620 *cam, Grid_c602_01E01620 *g) {
    extern void c602_01E00080(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_001D9F00(void *, s32);
    extern void func_001DA7A0(s32, void *);
    s32 r;
    s32 fl;
    s32 du;
    s32 c;
    s32 dv;
    f32 dep[4];
    Vec4f p[3];
    Pkt_c602_01E01620 pkt;

    fl = func_001D9F00(o, 1);
    ((Pkt_c602_01E01620 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c602_01E01620 *)(s32)&pkt)->pad = 0;
    if (func_00104520(g->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(g->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    du = g->tw >> 4;
    dv = g->th / 23;
    for (r = 0; r < 23; r++) {
        for (c = 0; c < 16; c++) {
            g->col.a = g->alpha[r][c];
            c602_01E00080(&pkt, &g->col);
            g->u = g->u0 + (s16)(c * du);
            g->v = g->v0 + (s16)(r * dv);
            ((Pkt_c602_01E01620 *)(s32)&pkt)->count |= 0x800;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[0].uv)->u = g->u << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[0].uv)->v = g->v << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[1].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[1].uv)->v = g->v << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[2].uv)->u = g->u << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[2].uv)->v = (g->v + dv - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[3].uv)->u = (g->u + du - 1) << 4;
            ((Uv_c602_01E01620 *)(s32)&pkt.v[3].uv)->v = (g->v + dv - 1) << 4;
            if (func_00104520(g->flags, 0x1E) == 0 && !(g->pos[r][c].z <= 0.0f)) {
                func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
            }
            p[0].x = g->pos[r][c].x - g->half;
            p[0].y = g->pos[r][c].y + g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[0].z = g->pos[r][c].z;
            } else {
                p[0].z = 0.0f;
            }
            if (func_00205440(&p[0], cam->view, &pkt.v[0].uv + 1, &dep[0]) != 0) {
                g->flags |= 0x100000;
            }
            p[0].x = g->pos[r][c].x + g->half;
            p[0].y = g->pos[r][c].y + g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[0].z = g->pos[r][c].z;
            } else {
                p[0].z = 0.0f;
            }
            if (func_00205440(&p[0], cam->view, &pkt.v[1].uv + 1, &dep[1]) != 0) {
                g->flags |= 0x200000;
            }
            p[1].x = g->pos[r][c].x - g->half;
            p[1].y = g->pos[r][c].y - g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[1].z = g->pos[r][c].z;
            } else {
                p[1].z = 0.0f;
            }
            if (func_00205440(&p[1], cam->view, &pkt.v[2].uv + 1, &dep[2]) != 0) {
                g->flags |= 0x400000;
            }
            p[2].x = g->pos[r][c].x + g->half;
            p[2].y = g->pos[r][c].y - g->half;
            if (func_00104520(g->flags, 0x1E) != 0) {
                p[2].z = g->pos[r][c].z;
            } else {
                p[2].z = 0.0f;
            }
            if (func_00205440(&p[2], cam->view, &pkt.v[3].uv + 1, &dep[3]) != 0) {
                g->flags |= 0x800000;
            }
            pkt.t0 = o->t0;
            pkt.t1 = o->t1;
            pkt.t2 = o->t2;
            if (r == 0 && c == 0) {
                if (fl != 0) {
                    func_001DA7A0(o->f90, o);
                } else {
                    func_001DA7A0(0, o);
                }
            }
            if (func_00104520(g->flags, 0x14) != 0) {
                if (func_00104520(g->flags, 0x15) != 0 && func_00104520(g->flags, 0x16) != 0 &&
                    func_00104520(g->flags, 0x17) != 0) {
                    if (func_00104520(g->flags, 0x13) != 0) {
                        pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                        func_002075F0(&pkt, 0, 0);
                    } else {
                        func_002075F0(&pkt, 0, func_001A23B0((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f));
                    }
                }
            }
            g->flags &= 0xFF0FFFFF;
        }
    }
    return 0;
}

/* shape c602:01E01E20 (c602), 743 insns, 1 copy: the c602 module main: on start copies the unit's object, sets up a
   23 x 16 tile grid (texture 3/2), a sprite, four rings and a 60-point spark cloud, timer 30; each tick draws and
   grows the effects, fades them after tick 7; code 1 fades the unit colour, code 2 draws the grid and jitters and
   fades each tile; 8 when the last tile fades or the timer ends */

typedef struct {
    f32 sx, sy, sz;
    u8 pad0C[4];
    s32 rx, ry, rz;
    u8 pad1C[4];
    f32 px, py, pz;
    u8 pad2C[4];
    f32 view[16];
} Crd_c602_01E01E20;

typedef struct {
    f32 x __attribute__((aligned(16)));
    f32 y, z;
    u8 pad0C[0x75];
    s8 b0 : 5;
    s8 f5 : 1;
    s8 f6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} Obj_c602_01E01E20;

typedef struct {
    u8 b, g, r, a;
} Col_c602_01E01E20;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c602_01E01E20 color;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c602_01E01E20;

typedef struct {
    f32 x, y, z;
} Pt_c602_01E01E20;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c602_01E01E20 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    Pt_c602_01E01E20 pts[60];
} Spark_c602_01E01E20;

typedef struct {
    s32 kind;
    s32 flags;
    Col_c602_01E01E20 color;
    f32 scale;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 w0, w1, h0, h1;
    u8 pad30[0x440];
} Spr_c602_01E01E20;

typedef struct {
    Crd_c602_01E01E20 cam;
    Grid_c602_01E01620 grid;
    u8 pad1A00[0x90];
    Obj_c602_01E01E20 obj;
    Crd_c602_01E01E20 c3;
    Spr_c602_01E01E20 spr;
    Crd_c602_01E01E20 c1;
    Crd_c602_01E01E20 c2;
    Crd_c602_01E01E20 c4;
    Spark_c602_01E01E20 spark;
    Ring_c602_01E01E20 ring0;
    Ring_c602_01E01E20 ring1;
    Ring_c602_01E01E20 ring2;
    Ring_c602_01E01E20 ring3;
    f32 sc[3];
    u8 pad345C[4];
    u8 col[4];
    s32 ch;
    s32 timer;
    s32 t;
    s32 code;
    s32 w3474;
    u8 pad3478[8];
} Scene_c602_01E01E20;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
    s32 f14;
    s32 f18;
    u8 pad1C[0x27];
    s8 b43;
} Ent_c602_01E01E20;

static s32 func_01E01E20_c602(s32 arg0, s32 code) {
    Scene_c602_01E01E20 *g = (Scene_c602_01E01E20 *)arg0;
    extern s32 func_001F5380(void);
    extern Ent_c602_01E01E20 *func_001F5B30(s32);
    extern void func_00103260(void *, s32);
    extern void func_00195108(void *, s32);
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 ch;
    Ent_c602_01E01E20 *e;
    s32 i;
    s32 j;
    s32 fp;
    s32 k;

    ot = (s32)func_00207500();
    ch = func_001F5380();
    e = func_001F5B30(ch);
    if (e == 0) {
        return 8;
    }
    if (code >= 0) {
        func_00195108(g, 0x3480);
        func_00103890(g);
        func_00103890(&g->c1);
        func_00103890(&g->c2);
        func_00103890(&g->c4);
        func_00103890(&g->c3);
        g->obj = *(Obj_c602_01E01E20 *)e;
        func_001F59D0(ch, 1);
        g->obj.f6 = 1;
        g->obj.f5 = 1;
        g->t = 1;
        g->w3474 = 0;
        g->timer = 30;
        g->code = code;
        g->sc[0] = 1.04f;
        g->sc[1] = 1.04f;
        g->sc[2] = 1.04f;
        g->ch = ch;
        if (g->code == 2) {
            e->b43 = 0;
        }
        g->obj.x = g->obj.y = g->obj.z = 0;
        tex = func_00202BF0(3, 2);
        *(s32 *)g->grid.pad0 = tex;
        g->grid.flags = 0x40000801;
        g->grid.half = 0.8f;
        g->grid.u = 0;
        g->grid.v = 0;
        g->grid.u0 = 0;
        g->grid.v0 = 0;
        g->grid.tw = 0x100;
        g->grid.th = 0x170;
        g->grid.col.b = g->grid.col.g = g->grid.col.r = 0x80;
        for (i = 0; i < 23; i++) {
            for (j = 0; j < 16; j++) {
                g->grid.pos[i][j].x = -12.0f + 2.0f * g->grid.half * j;
                g->grid.pos[i][j].z = 0.0f;
                g->grid.pos[i][j].y = 17.6f + -2.0f * g->grid.half * i;
                g->grid.alpha[i][j] = 0x80;
            }
        }
        func_001F53B0(0, (s32)&g->cam.px);
        g->cam.rx = e->f10;
        g->cam.ry = e->f14;
        g->cam.rz = e->f18;
        func_00103260(&tex, 0xF);
        g->spr.flags = 1;
        g->spr.u = 0xD0;
        g->spr.v = 0x20;
        g->spr.w = 0x20;
        g->spr.h = 0x20;
        g->spr.color.r = 0xB0;
        g->spr.color.g = 0xB0;
        g->spr.color.b = 0x60;
        g->spr.color.a = 0x20;
        g->spr.w0 = 0.5f;
        g->spr.w1 = 2.0f;
        g->spr.h0 = 25.0f;
        g->spr.h1 = 0.0f;
        func_01E00EB0_c602((Obj_b087_01E03B30 *)&g->spr, tex, 3.0f);
        g->ring1.flags = 0x8000;
        g->ring1.u = 0x8E;
        g->ring1.v = 0;
        g->ring1.w = 0x20;
        g->ring1.h = 0x40;
        g->ring1.color.r = 0xB0;
        g->ring1.color.g = 0xB0;
        g->ring1.color.b = 0x60;
        g->ring1.color.a = 0x60;
        {
            f32 h = 28.0f;
            func_01E00700_c602((Ring_b001_01E035A0 *)&g->ring1, tex, 0.1f, 34.0f, 0.0f, h);
        }
        g->ring2.flags = 0x8000;
        g->ring2.u = 0x8E;
        g->ring2.v = 0;
        g->ring2.w = 0x20;
        g->ring2.h = 0x40;
        g->ring2.color.r = 0xB0;
        g->ring2.color.g = 0xB0;
        g->ring2.color.b = 0x60;
        g->ring2.color.a = 0x60;
        func_01E00700_c602((Ring_b001_01E035A0 *)&g->ring2, tex, 0.1f, 37.0f, 0.0f, 21.0f);
        g->ring3.flags = 0x8000;
        g->ring3.u = 0x8E;
        g->ring3.v = 0;
        g->ring3.w = 0x20;
        g->ring3.h = 0x40;
        g->ring3.color.r = 0xB0;
        g->ring3.color.g = 0xB0;
        g->ring3.color.b = 0x60;
        g->ring3.color.a = 0x60;
        func_01E00700_c602((Ring_b001_01E035A0 *)&g->ring3, tex, 0.1f, 40.0f, 0.0f, 14.0f);
        g->ring0.flags = 0x8000;
        g->ring0.u = 0x8E;
        g->ring0.v = 0;
        g->ring0.w = 0x20;
        g->ring0.h = 0x40;
        g->ring0.color.r = 0x80;
        g->ring0.color.g = 0x80;
        g->ring0.color.b = 0x80;
        g->ring0.color.a = 0xFF;
        func_01E00700_c602((Ring_b001_01E035A0 *)&g->ring0, tex, 4.0f, 0.3f, 0.0f, 60.0f);
        func_00103260(&tex, 8);
        g->spark.texture = tex;
        g->spark.size = 2.0f;
        for (k = 0; k < 60; k++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.pts[k].x = func_0019A5C8() % 100 - 50;
                g->spark.pts[k].z = func_0019A5C8() % 50;
                g->spark.pts[k].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.pts[k].x = func_0019A5C8() % 50 - 25;
                g->spark.pts[k].y = func_0019A5C8() % 25;
                g->spark.pts[k].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->spark.flags = 1;
        g->spark.u = 0;
        g->spark.v = 0x5A;
        g->spark.w = 0xA;
        g->spark.h = 0xA;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x80;
        g->spark.color.b = 0x80;
        g->spark.color.a = 0x80;
        g->c1.sy = 0.1f;
        g->c2.sx = g->c2.sy = g->c2.sz = 0.1f;
        g->c4.sx = g->c4.sy = g->c4.sz = 0.1f;
        g->c3.sx = g->c3.sy = g->c3.sz = 0.1f;
        func_001F53B0(0, (s32)&g->c1.px);
        func_001F53B0(0, (s32)&g->c2.px);
        func_001F53B0(0, (s32)&g->c4.px);
        func_001F53B0(0, (s32)&g->c3.px);
        return 0;
    }
    func_001038D0(g);
    func_001038D0(&g->c1);
    g->c2.py = 3.0f;
    func_001039A0(&g->c2);
    func_001038D0(&g->c4);
    g->c1.ry += 0x400;
    func_001038D0(&g->c3);
    func_01E01010_c602(ot, (Spr_b087_01E03C90 *)&g->spr, (Cam_b087_01E03C90 *)&g->c3);
    if (g->c2.sx < 1.0f) {
        g->c2.sx = g->c2.sy = g->c2.sz += 0.3f;
    }
    func_01E00120_c602(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)&g->c2, (s32)g->sc);
    func_00103470(&g->ring0.color.a, 0, 18);
    func_01E009C0_c602(ot, (Ring_b001_01E03860 *)&g->ring1, (Cam_b001_01E03860 *)&g->c4);
    func_01E009C0_c602(ot, (Ring_b001_01E03860 *)&g->ring2, (Cam_b001_01E03860 *)&g->c4);
    func_01E009C0_c602(ot, (Ring_b001_01E03860 *)&g->ring3, (Cam_b001_01E03860 *)&g->c4);
    if (g->t >= 7) {
        func_00103470(&g->spark.color.a, 0, 10);
        func_00103470(&g->spr.color.a, 0, 2);
        func_00103470(&g->ring1.color.a, 0, 6);
        func_00103470(&g->ring2.color.a, 0, 6);
        func_00103470(&g->ring3.color.a, 0, 6);
    }
    if (g->c4.sx < 1.0f) {
        g->c4.sx = g->c4.sy = g->c4.sz += 0.3f;
    } else {
        g->c4.sx = g->c4.sy = g->c4.sz += 0.05f;
    }
    if (g->c1.sy < 1.0f) {
        g->c1.sy += 0.3f;
    } else {
        g->c1.sy += 0.05f;
    }
    if (g->c3.sy < 1.0f) {
        g->c3.sx += 0.3f;
        g->c3.sy += 0.3f;
        g->c3.sz += 0.3f;
    } else {
        g->c3.sx += 0.05f;
        g->c3.sy += 0.05f;
        g->c3.sz += 0.05f;
    }
    if (g->code == 1) {
        if (func_001F5AF0(g->ch) != 0) {
            func_001F5E40(g->ch, g->col);
            func_00103470(&g->col[3], 0, 4);
            func_001F5DE0(g->ch, (s32)g->col);
        }
    } else if (g->code == 2) {
        fp = func_00207F60();
        func_001D99F0();
        func_00208490(1);
        func_01E01620_c602((Obj_c602_01E01620 *)&g->obj, (Cam_c602_01E01620 *)g, &g->grid);
        for (i = 0; i < 23; i++) {
            for (j = 0; j < 16; j++) {
                g->grid.pos[i][j].z += 0.2f * (func_0019A5C8() % (g->t * 2) - g->t);
                g->grid.pos[i][j].x += 0.2f * (func_0019A5C8() % (g->t * 2) - g->t);
                g->grid.pos[i][j].y += 0.2f * (func_0019A5C8() % (g->t * 2) - g->t);
                if (i == 0 && j == 0) {
                    g->cam.ry += g->t << 9;
                }
                if (func_00103470(&g->grid.alpha[i][j], 0, 4) == 0 && i == 22 && j == 15) {
                    return 8;
                }
                if (g->grid.alpha[22][15] <= 0x60) {
                    g->grid.flags = 0x40000001;
                }
            }
        }
        func_00208490(0);
        func_001D9DD0();
        func_00207FD0(fp, (s32)func_00207500(), 0xFFFFFF);
    }
    g->t++;
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
