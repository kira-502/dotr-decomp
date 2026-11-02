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

static void func_01E00080_c500(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b021:01E00120, 81 insns, 7 copies: the four corner colours of a sprite packet from one colour, alpha
   faded by level (corners 0/2 by (5 - level) * 16, corners 1/3 by (4 - level) * 16, never below 0),
   q = 1.0f, fog bytes cleared. A variant of b000:01E00100. */

typedef struct {
    u8 b, g, r, a;
} Src_b021_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    u8 xyz[7];
    u8 fog;
} Vtx_b021_01E00120;

typedef struct {
    u8 tag[0x10];
    Vtx_b021_01E00120 v[4];
} Pk_b021_01E00120;


/* static in its module (callers that include this file #define OVL_LOCAL static first) */

static void func_01E00120_c500(Pk_b021_01E00120 *p, Src_b021_01E00120 *s, s32 lvl) {
    p->v[0].r = s->r;
    p->v[0].g = s->g;
    p->v[0].b = s->b;
    if (s->a >= (5 - lvl) * 16) {
        p->v[0].a = s->a - (5 - lvl) * 16;
    } else {
        p->v[0].a = 0;
    }
    p->v[0].q = 1.0f;
    p->v[1].r = s->r;
    p->v[1].g = s->g;
    p->v[1].b = s->b;
    if (s->a >= (4 - lvl) * 16) {
        p->v[1].a = s->a - (4 - lvl) * 16;
    } else {
        p->v[1].a = 0;
    }
    p->v[1].q = 1.0f;
    p->v[2].r = s->r;
    p->v[2].g = s->g;
    p->v[2].b = s->b;
    if (s->a >= (5 - lvl) * 16) {
        p->v[2].a = s->a - (5 - lvl) * 16;
    } else {
        p->v[2].a = 0;
    }
    p->v[2].q = 1.0f;
    p->v[3].r = s->r;
    p->v[3].g = s->g;
    p->v[3].b = s->b;
    if (s->a >= (4 - lvl) * 16) {
        p->v[3].a = s->a - (4 - lvl) * 16;
    } else {
        p->v[3].a = 0;
    }
    p->v[3].q = 1.0f;
    p->v[0].fog = 0;
    p->v[1].fog = 0;
    p->v[2].fog = 0;
    p->v[3].fog = 0;
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

static s32 func_01E00270_c500(s32 arg0, Src_b000_01E00400 *c) {
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

/* shape c500:01E003D0, 149 insns: set up a 6-corner billboard: copy the module's corner template, store the id and
   half the size, then stretch x or y so the shape keeps the source's aspect (s16 w/h when flag 0 is set and flag
   0x1F is not, f32 w/h otherwise), and write corner = template * size/2 * stretch */

typedef struct {
    Vec4f v[6];
} Six_c500_01E003D0;

typedef struct {
    u8 pad0[4];
    s16 w;
    s16 h;
    f32 fw;
    f32 fh;
    u8 pad10[0x28];
    s32 flags;
} Src_c500_01E003D0;

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
} Bb_c500_01E003D0;

extern Six_c500_01E003D0 D_01E03200_c500;

static s32 func_01E003D0_c500(Src_c500_01E003D0 *o, Bb_c500_01E003D0 *out, s32 id, f32 size) {
    Six_c500_01E003D0 q;
    f32 sx;
    f32 sy;
    f32 half;
    s32 i;

    q = D_01E03200_c500;
    out->f10 = out->f14 = out->f18 = 0;
    out->scale = size / 2.0f;
    out->id = id;
    if (func_00104520(o->flags, 0) != 0 && func_00104520(o->flags, 0x1F) == 0) {
        if (o->w > o->h >> 1) {
            sx = 1.0f;
            sy = o->w / (o->h / 2.0f);
        } else if (o->w < o->h >> 1) {
            sx = o->w / (o->h / 2.0f);
            sy = 1.0f;
        } else {
            sy = 1.0f;
            sx = sy;
        }
    } else {
        half = o->fh / 2.0f;
        if (o->fw > half) {
            sy = o->fw / half;
            sx = 1.0f;
        } else if (o->fw < half) {
            sx = o->fw / half;
            sy = 1.0f;
        } else {
            sy = 1.0f;
            sx = sy;
        }
    }
    for (i = 0; i < 6; i++) {
        out->v[i].x = sx * (out->scale * q.v[i].x);
        out->v[i].y = sy * (out->scale * q.v[i].y);
        out->v[i].z = out->scale * q.v[i].z;
    }
    return 0;
}

/* shape c500:01E00630, 465 insns: draws two textured quads of a 6-point strip (like b001:01E03860's ring):
   quad i uses points 2i, 4, 2i+1, 5 offset by the strip position, rotated by the object's angle when flag 0x1E
   is set; colour from the module helper c500:01E00080. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c500_01E00630;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c500_01E00630 v[4];
    u8 tail[0x20];
} Pkt_c500_01E00630;

typedef struct {
    s16 u, v, w, h;
    u8 pad8[0x2C];
    u8 color[4];
    s32 flags;
    u8 pad3C[4];
    s32 angle;
} Obj_c500_01E00630;

typedef struct {
    void *texture;
    s32 flags;
    u8 pad8[8];
    Vec4f pos;
    Vec4f pts[6];
} Strip_c500_01E00630;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c500_01E00630;

extern void c500_01E00080(void *, void *);

static s32 func_01E00630_c500(s32 ot, Obj_c500_01E00630 *o, Strip_c500_01E00630 *s, Cam_c500_01E00630 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_00104DC0(void *, void *);
    extern void func_0020C750(void *, void *, s32);
    extern void func_0020CDD0(void *, void *, void *);
    f32 depth[4];
    Vec4f p;
    Vec4f rv;
    f32 m[16];
    Pkt_c500_01E00630 pkt;
    s32 i;

    ((Pkt_c500_01E00630 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c500_01E00630 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    c500_01E00080(&pkt, o->color);
    for (i = 0; i < 2; i++) {
        if (func_00104520(o->flags, 0x1F) != 0) {
            func_00104540(&pkt, o, 5);
        } else {
            func_00104DC0(&pkt, o);
        }
        if (func_00104520(o->flags, 0x1E) != 0) {
            rv.x = rv.z = rv.w = 0.0f;
            rv.y = 1.0f;
            func_0020C750(m, &rv, o->angle % 0x10000);
            func_0020CDD0(&p, m, &s->pts[i * 2]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                s->flags |= 0x100000;
            }
            func_0020CDD0(&p, m, &s->pts[4]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                s->flags |= 0x200000;
            }
            func_0020CDD0(&p, m, &s->pts[i * 2 + 1]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                s->flags |= 0x400000;
            }
            func_0020CDD0(&p, m, &s->pts[5]);
            p.x += s->pos.x;
            p.y += s->pos.y;
            p.z += s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                s->flags |= 0x800000;
            }
        } else {
            p.x = s->pos.x + s->pts[i * 2].x;
            p.y = s->pos.y + s->pts[i * 2].y;
            p.z = s->pos.z;
            if (func_00205440(&p, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                s->flags |= 0x100000;
            }
            p.x = s->pos.x + s->pts[4].x;
            p.y = s->pos.y + s->pts[4].y;
            if (func_00205440(&p, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                s->flags |= 0x200000;
            }
            p.x = s->pos.x + s->pts[i * 2 + 1].x;
            p.y = s->pos.y + s->pts[i * 2 + 1].y;
            if (func_00205440(&p, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                s->flags |= 0x400000;
            }
            p.x = s->pos.x + s->pts[5].x;
            p.y = s->pos.y + s->pts[5].y;
            if (func_00205440(&p, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                s->flags |= 0x800000;
            }
        }
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00208700(&pkt, s->texture, 0);
        } else {
            if (func_00104520(o->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->u << 4) | ((u64)(o->u + o->w - 1) << 14) |
                                        ((u64)o->v << 24) | ((u64)(o->v + o->h - 1) << 34));
            }
            func_00208700(&pkt, s->texture, 1);
        }
        if (func_00104520(s->flags, 0x14) != 0 && func_00104520(s->flags, 0x15) != 0 &&
            func_00104520(s->flags, 0x16) != 0 && func_00104520(s->flags, 0x17) != 0) {
            if (func_00104520(o->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, ot, 0);
            } else {
                func_002075F0(&pkt, ot, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        s->flags &= 0xFF0FFFFF;
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

static s32 func_01E00D80_c500(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
    extern void c500_01E00080(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);
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
    c500_01E00080(&pkt, &sp->color);
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

static s32 func_01E01360_c500(Ring_b001_01E035A0 *o, s32 type, f32 inner, f32 outer, f32 y, f32 height) {
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
   It calls the module's colour helper (shape b000:01E00100, here func_01E00080_c500) and needs that helper
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

static s32 func_01E01620_c500(s32 obj, Ring_b001_01E03860 *ring, Cam_b001_01E03860 *cam) {
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
        func_01E00080_c500(&pkt, &ring->color);
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

INCLUDE_ASM("asm/nonmatchings/mod/c500", func_01E01B10_c500);

/* shape c500:01E02310 (LkSortElec), 307 insns, 1 copy: a lightning bolt: jitter its five points (x -5..4, y 0..19,
   the last y -5..4), then draw 5 - n segments as textured quads of width ctx+0x2C from the start (or the previous
   point) to each point, depth-sorted when all four corners are in view */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_c500_01E02310;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c500_01E02310 v[4];
    u8 tail[0x20];
} Pkt_c500_01E02310;

typedef struct {
    void *texture;
    u8 x4[8];
    s16 n;
    u8 padE[2];
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p0;
    Vec4f pts[5];
} Elec_c500_01E02310;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_c500_01E02310;

static s32 func_01E02310_c500(s32 ot __attribute__((aligned(8))), Elec_c500_01E02310 *s, Cam_c500_01E02310 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    f32 depth[4];
    Pkt_c500_01E02310 pkt;
    s32 flags;
    s32 i;

    ((Pkt_c500_01E02310 *)(s32)&pkt)->count = 0x34;
    ((Pkt_c500_01E02310 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_c500_01E02310 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_c500_01E02310 *)(s32)&pkt)->pad = 0;
    flags = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0; i < 5; i++) {
        if (i == 4) {
            s->pts[i].x = func_0019A5C8() % 10 - 5;
            s->pts[i].y = func_0019A5C8() % 10 - 5;
        } else {
            s->pts[i].x = func_0019A5C8() % 10 - 5;
            s->pts[i].y = func_0019A5C8() % 20;
        }
    }
    for (i = 0; i < 5 - s->n; i++) {
        func_01E00120_c500((Pk_b021_01E00120 *)&pkt, (Src_b021_01E00120 *)s->x4, i);
        func_00104540(&pkt, &s->u, 1);
        if (i == 0) {
            if (func_00205440(&s->p0, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                flags |= 0x100000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                flags |= 0x200000;
            }
            s->p0.x += s->p0.w;
            s->pts[i].x += s->p0.w;
            if (func_00205440(&s->p0, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                flags |= 0x400000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                flags |= 0x800000;
            }
            s->p0.x -= s->p0.w;
            s->pts[i].x -= s->p0.w;
        } else {
            if (func_00205440(&s->pts[i - 1], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
                flags |= 0x100000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
                flags |= 0x200000;
            }
            s->pts[i - 1].x += s->p0.w;
            s->pts[i].x += s->p0.w;
            if (func_00205440(&s->pts[i - 1], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
                flags |= 0x400000;
            }
            if (func_00205440(&s->pts[i], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
                flags |= 0x800000;
            }
            s->pts[i - 1].x -= s->p0.w;
            s->pts[i].x -= s->p0.w;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)s->u << 4) | ((u64)(s->u + s->w - 1) << 14) |
                                ((u64)s->v << 24) | ((u64)(s->v + s->h - 1) << 34));
        func_00208700(&pkt, s->texture, 1);
        if (func_00104520(flags, 0x14) != 0 && func_00104520(flags, 0x15) != 0 &&
            func_00104520(flags, 0x16) != 0 && func_00104520(flags, 0x17) != 0) {
            func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
        flags &= 0xFF0FFFFF;
    }
    return 0;
}


INCLUDE_ASM("asm/nonmatchings/mod/c500", func_01E027E0_c500);
