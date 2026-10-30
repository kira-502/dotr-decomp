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

static void func_01E00080_b438(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b037:01E00F70, 77 insns, 10 copies: b001:01E00900 with the colour from the caller (b, g, r, a bytes): one GS sprite (RGBAQ, ST, XYZ2, ST, XYZ2) sent with the current texture */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b037_01E00F70;

typedef struct {
    Hdr_b037_01E00F70 h;
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
} Pkt_b037_01E00F70;

static s32 func_01E00120_b438(u8 *c) {
    Pkt_b037_01E00F70 p __attribute__((aligned(8)));

    ((Hdr_b037_01E00F70 *)(s32)&p)->count = 0x26;
    ((Hdr_b037_01E00F70 *)(s32)&p)->tag = 5;
    ((Hdr_b037_01E00F70 *)(s32)&p)->regs = 0x42421;
    ((Hdr_b037_01E00F70 *)(s32)&p)->pad = 0;
    p.r = c[2];
    p.g = c[1];
    p.b = c[0];
    p.a = c[3];
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

static s32 func_01E00260_b438(s32 arg0, Src_b000_01E00400 *c) {
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

static s32 func_01E003C0_b438(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

static s32 func_01E00920_b438(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E01B80_b438;
    Tbl_b000_01E032C0 tbl = D_01E01B80_b438;
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

static s32 func_01E00A80_b438(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_b438((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

INCLUDE_ASM("asm/nonmatchings/mod/b438", func_01E01090_b438);

/* shape b438:01E01530 (b438), 399 insns, 1 copy: b438 scene manager: code >= 0 sets up the glow sprite, disc, 8
   lightning glows/discs and the bolt; else steps them (fade, blur after tick 135, random flash colour from 70, bolt
   from 196) and returns 2/1/6/8 by tick */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x40];
} Mat_b438_01E01530;

typedef struct {
    s32 x, y, z, w;
} Rnd_b438_01E01530;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 padC[4];
    s16 uv[4];
    u8 pad18[8];
    Vec4f p[4];
    Rnd_b438_01E01530 r[64];
} Spr_b438_01E01530;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 radius;
    s16 count;
    s16 height;
} Disc_b438_01E01530;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    s16 count;
    s16 jitter;
    s16 uv[4];
    u8 pad88[8];
    Mat_b438_01E01530 *nodes;
    Spr_b438_01E01530 *glow;
    Disc_b438_01E01530 *sa;
    Disc_b438_01E01530 *sb;
    s16 tick;
    s16 step;
    s16 fade;
    u8 ac;
    u8 aa;
    u8 ab;
    u8 padA9[7];
} Bolt_b438_01E01530;

typedef struct {
    Mat_b438_01E01530 m0;
    Bolt_b438_01E01530 bolt;
    Mat_b438_01E01530 ma;
    Mat_b438_01E01530 cam;
    Spr_b438_01E01530 spr;
    Disc_b438_01E01530 disc;
    Mat_b438_01E01530 mb[8];
    Spr_b438_01E01530 glow[8];
    Disc_b438_01E01530 sa[8];
    Disc_b438_01E01530 sb[8];
    u8 c[4];
    u8 c2[4];
    s32 timer;
    s32 t;
    s32 code;
    s32 fade;
    s32 ja;
    s32 jb;
} Scene_b438_01E01530;

static s32 func_01E01530_b438(s32 arg0, s32 code) {
    Scene_b438_01E01530 *g = (Scene_b438_01E01530 *)arg0;
    extern void b438_01E01090();
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00103260(s32 *, s32);
    extern void func_00103470(u8 *, s32, s32);
    extern void func_001032C0(u8 *, s32, s32);
    extern void func_001F6D00(s32);
    Vec4f v[3];
    s32 tx[4];
    s32 ot;
    Vec4f *p;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2DA0);
        func_00103890(&g->m0);
        func_00103890(&g->ma);
        func_00103890(&g->cam);
        for (i = 0; i < 8; i++) {
            func_00103890(&g->mb[i]);
        }
        g->ja = func_001F5560(func_001F53A0(), 0x4E, 1);
        g->jb = func_001F5560(func_001F53A0(), 0x28, 0);
        g->timer = 340;
        g->t = 1;
        g->code = code;
        g->fade = 0x80;
        g->c[2] = 0x80;
        g->c[1] = 0x80;
        g->c[0] = 0x80;
        g->c[3] = 0x40;
        g->c2[2] = 0x80;
        g->c2[1] = 0x80;
        g->c2[0] = 0x80;
        g->c2[3] = 0x60;
        g->disc.flags = 0x80000;
        g->disc.r = 0xD0;
        g->disc.g = 0xA0;
        g->disc.b = 0x70;
        g->disc.a = 0;
        g->disc.radius = 8.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        for (i = 0; i < 8; i++) {
            g->sa[i].flags = 0x80000;
            g->sa[i].r = 0xD0;
            g->sa[i].g = 0xA0;
            g->sa[i].b = 0x70;
            g->sa[i].a = 0xFF;
            g->sa[i].radius = 16.0f;
            g->sa[i].count = 0x24;
            g->sa[i].height = 0;
            g->sb[i].flags = 0x10080000;
            g->sb[i].r = 0xD0;
            g->sb[i].g = 0xA0;
            g->sb[i].b = 0x70;
            g->sb[i].a = 0xFF;
            g->sb[i].radius = 3.0f;
            g->sb[i].count = 0x24;
            g->sb[i].height = 0;
        }
        func_00103260(tx, 0xF);
        g->spr.flags = 1;
        g->spr.uv[0] = 0x8E;
        g->spr.uv[1] = 0;
        g->spr.uv[2] = 0x22;
        g->spr.uv[3] = 0x40;
        g->spr.c[2] = 0xD0;
        g->spr.c[1] = 0xA0;
        g->spr.c[0] = 0x70;
        g->spr.c[3] = 0;
        func_01E00920_b438((Obj_b000_01E032C0 *)&g->spr, tx[0], 0.7f);
        for (i = 0; i < 8; i++) {
            g->glow[i].flags = 0x80001;
            g->glow[i].uv[0] = 0x8E;
            g->glow[i].uv[1] = 0;
            g->glow[i].uv[2] = 0x22;
            g->glow[i].uv[3] = 0x40;
            g->glow[i].c[2] = 0x80;
            g->glow[i].c[1] = 0x80;
            g->glow[i].c[0] = 0x80;
            g->glow[i].c[3] = 0x30;
            func_01E00920_b438((Obj_b000_01E032C0 *)&g->glow[i], tx[0], 0.8f);
        }
        g->bolt.tex = tx[0];
        g->bolt.flags = 0;
        g->bolt.uv[0] = 10;
        g->bolt.uv[1] = 0;
        g->bolt.uv[2] = 0x2A;
        g->bolt.uv[3] = 0x80;
        g->bolt.c[2] = 0x80;
        g->bolt.c[1] = 0x80;
        g->bolt.c[0] = 0x80;
        g->bolt.c[3] = 0x20;
        g->bolt.count = 8;
        g->bolt.tick = 0;
        g->bolt.step = 1;
        g->bolt.fade = 0;
        g->bolt.jitter = 0x50;
        g->bolt.nodes = g->mb;
        g->bolt.glow = g->glow;
        g->bolt.sa = g->sa;
        g->bolt.sb = g->sb;
        g->bolt.ac = g->glow[0].c[3];
        g->bolt.aa = g->sa[0].a;
        g->bolt.ab = g->sb[0].a;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->ja, &v[0]);
    func_001F5620(func_001F53A0(), g->jb, &v[1]);
    func_001036E0(&v[0], &v[1], &g->cam.pos);
    func_001F5F90(func_001F5380(), p = &v[2]);
    func_001038D0(&g->m0);
    func_001039A0(&g->ma);
    func_001039A0(&g->cam);
    for (i = 0; i < 8; i++) {
        func_001039A0(&g->mb[i]);
    }
    if (g->t < 0x140) {
        func_00103470((u8 *)&g->fade, 0x20, 4);
    } else {
        func_001032C0((u8 *)&g->fade, 0x80, 4);
    }
    func_001F6D00((u8)g->fade);
    if (g->t >= 0x87 && g->t < 0x113) {
        func_01E00120_b438(g->c2);
        if (g->t >= 0x10E) {
            func_00103470(&g->c2[3], 0, 6);
        }
    }
    if (g->t >= 0x46) {
        g->c[2] = g->disc.r = g->spr.c[2] = func_0019A5C8() % 128;
        g->c[1] = g->disc.g = g->spr.c[1] = func_0019A5C8() % 128;
        g->c[0] = g->disc.b = g->spr.c[0] = func_0019A5C8() % 128;
        func_01E00260_b438(ot, (Src_b000_01E00400 *)g->c);
        func_01E003C0_b438(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->cam);
        func_001032C0(&g->disc.a, 0xFF, 0x10);
        func_01E00A80_b438(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->cam);
        func_001032C0(&g->spr.c[3], 0x20, 2);
        for (i = 0; i < 64; i++) {
            g->spr.r[i].x += 0x80;
            g->spr.r[i].y += 0x80;
            g->spr.r[i].z += 0x80;
        }
    }
    if (g->t >= 0xC4) {
        for (i = 0; i < 8; i++) {
            g->glow[i].c[2] = g->sa[i].r = g->sb[i].r = g->spr.c[2];
            g->glow[i].c[1] = g->sa[i].g = g->sb[i].g = g->spr.c[1];
            g->glow[i].c[0] = g->sa[i].b = g->sb[i].b = g->spr.c[0];
        }
        b438_01E01090(ot, &g->bolt, g, &g->cam.pos, p);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x140) {
        return 2;
    }
    if (g->t == 0xDC) {
        return 1;
    }
    if (g->t >= 0xE6 && g->t < 0x140) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
