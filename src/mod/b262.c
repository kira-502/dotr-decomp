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

static void func_01E00080_b262(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b262(s32 arg0, Src_b000_01E00400 *c) {
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

static s32 func_01E00280_b262(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

static s32 func_01E007E0_b262(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E01A00_b262;
    Tbl_b000_01E032C0 tbl = D_01E01A00_b262;
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

static s32 func_01E00940_b262(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_b262((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* shape b262:01E00F50 (LkEff_SortFlash), 294 insns, 3 copies: lightning bolt update: on tick 0 lays count (<= 16)
   nodes from p0 to p1 jittered by rand and resets the three strand alphas; grows one node per step ticks, builds and
   fades the strands (fade steps u8, passed to a (u8 *, u8, u8) fader), nudges each glow point, restarts after fade +
   step * count ticks */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x40];
} Node_b262_01E00F50;

typedef struct {
    u8 pad0[7];
    u8 a;
    u8 pad8[8];
} Strand_b262_01E00F50;

typedef struct {
    s32 x, y, z, w;
} Pt_b262_01E00F50;

typedef struct {
    u8 pad0[0xB];
    u8 a;
    u8 padC[0x54];
    Pt_b262_01E00F50 v[64];
} Glow_b262_01E00F50;

typedef struct {
    u8 pad0[4];
    s32 flags;
    u8 pad8[4];
    s16 count;
    s16 jitter;
    u8 pad10[0x10];
    Node_b262_01E00F50 *nodes;
    Glow_b262_01E00F50 *glow;
    Strand_b262_01E00F50 *sa;
    Strand_b262_01E00F50 *sb;
    s16 tick;
    s16 step;
    s16 fade;
    u8 ac;
    u8 aa;
    u8 ab;
} Bolt_b262_01E00F50;

static s32 func_01E00F50_b262(s32 ot, Bolt_b262_01E00F50 *o, s32 unused, Vec4f *p0, Vec4f *p1) {
    extern void b262_01E00280(s32, void *, void *);
    extern void b262_01E00940(s32, void *, void *);
    extern s32 func_0019A5C8(void);
    extern void func_001039A0(void *);
    extern void func_00103470(u8 *, u8, u8);
    u8 fa;
    u8 fb;
    u8 fc;
    s32 i;
    s32 k;
    s32 n;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;

    fa = o->aa / o->fade;
    fb = o->ab / o->fade;
    fc = o->ac / o->fade;
    if (o->count > 16) {
        o->count = 16;
    }
    if (o->tick == 0) {
        dx = p1->x - p0->x;
        dy = p1->y - p0->y;
        dz = p1->z - p0->z;
        for (i = 0; i < o->count; i++) {
            t = (f32)(i + 1) / (f32)o->count;
            if (o->jitter != 0) {
                o->nodes[i].pos.x = p0->x + dx * t + 0.1f * (f32)(func_0019A5C8() % (o->jitter * 2) - o->jitter);
                o->nodes[i].pos.y = p0->y + dy * t + 0.1f * (f32)(func_0019A5C8() % (o->jitter * 2) - o->jitter);
                o->nodes[i].pos.z = p0->z + dz * t + 0.1f * (f32)(func_0019A5C8() % (o->jitter * 2) - o->jitter);
            } else {
                o->nodes[i].pos.x = p0->x + dx * t;
                o->nodes[i].pos.y = p0->y + dy * t;
                o->nodes[i].pos.z = p0->z + dz * t;
            }
            if (i == 0) {
                func_001039A0(o->nodes);
            }
            if (func_00104520(o->flags, 0x18) != 0) {
                o->sa[i].a = o->aa;
                o->sb[i].a = o->ab;
                o->glow[i].a = o->ac;
            }
        }
    }
    n = o->tick / o->step + 1;
    if (o->count < n) {
        n = o->count;
    }
    for (i = 0; i < n; i++) {
        b262_01E00280(ot, &o->sa[i], &o->nodes[i]);
        b262_01E00280(ot, &o->sb[i], &o->nodes[i]);
        b262_01E00940(ot, &o->glow[i], &o->nodes[i]);
        if (func_00104520(o->flags, 0x18) != 0) {
            func_00103470(&o->sa[i].a, 0, fa);
            func_00103470(&o->sb[i].a, 0, fb);
            func_00103470(&o->glow[i].a, 0, fc);
        }
        for (k = 0; k < 64; k++) {
            o->glow[i].v[k].x += 0x80;
            o->glow[i].v[k].y += 0x80;
            o->glow[i].v[k].z += 0x80;
        }
    }
    o->tick++;
    if (o->tick > o->fade + o->step * o->count) {
        o->tick = 0;
    }
    return 0;
}

/* shape b262:01E013F0 (b262), 358 insns, 1 copy: b438:01E01530's scene manager with 16 bolt nodes: code >= 0 sets up
   the glow sprite, disc, 16 glows/discs and the bolt; else follows joint 0x26 with the camera, fades, and from tick
   25 to 199 flashes one random grey into sprite, disc and glows, draws them and the bolt; returns 5/1/6/8 by tick */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x40];
} Mat_b262_01E013F0;

typedef struct {
    s32 x, y, z, w;
} Rnd_b262_01E013F0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    u8 padC[4];
    s16 uv[4];
    u8 pad18[8];
    Vec4f p[4];
    Rnd_b262_01E013F0 r[64];
} Spr_b262_01E013F0;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 radius;
    s16 count;
    s16 height;
} Disc_b262_01E013F0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    s16 count;
    s16 jitter;
    s16 uv[4];
    u8 pad88[8];
    Mat_b262_01E013F0 *nodes;
    Spr_b262_01E013F0 *glow;
    Disc_b262_01E013F0 *sa;
    Disc_b262_01E013F0 *sb;
    s16 tick;
    s16 step;
    s16 fade;
    u8 ac;
    u8 aa;
    u8 ab;
    u8 padA9[7];
} Bolt_b262_01E013F0;

typedef struct {
    Mat_b262_01E013F0 m0;
    Bolt_b262_01E013F0 bolt;
    Mat_b262_01E013F0 ma;
    Mat_b262_01E013F0 cam;
    Spr_b262_01E013F0 spr;
    Disc_b262_01E013F0 disc;
    Mat_b262_01E013F0 mb[16];
    Spr_b262_01E013F0 glow[16];
    Disc_b262_01E013F0 sa[16];
    Disc_b262_01E013F0 sb[16];
    u8 c[4];
    u8 c2[4];
    s32 timer;
    s32 t;
    s32 code;
    s32 fade;
    s32 ja;
    s32 jb;
} Scene_b262_01E013F0;

static s32 func_01E013F0_b262(s32 arg0, s32 code) {
    Scene_b262_01E013F0 *g = (Scene_b262_01E013F0 *)arg0;
    extern void b262_01E00F50();
    extern void b262_01E00120();
    extern void b262_01E00280();
    extern void b262_01E00940();
    extern s32 b262_01E007E0(void *, s32, f32);
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
        func_00195108(g, 0x5520);
        func_00103890(&g->m0);
        func_00103890(&g->ma);
        func_00103890(&g->cam);
        for (i = 0; i < 16; i++) {
            func_00103890(&g->mb[i]);
        }
        g->ja = func_001F5560(func_001F53A0(), 0x26, 1);
        g->jb = func_001F5560(func_001F53A0(), 0x21, 0);
        g->timer = 220;
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
        g->disc.flags = 0;
        g->disc.r = 0xD0;
        g->disc.g = 0xA0;
        g->disc.b = 0x70;
        g->disc.a = 0;
        g->disc.radius = 3.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        for (i = 0; i < 16; i++) {
            g->sa[i].flags = 0;
            g->sa[i].r = 0xD0;
            g->sa[i].g = 0xA0;
            g->sa[i].b = 0x70;
            g->sa[i].a = 0xFF;
            g->sa[i].radius = 16.0f;
            g->sa[i].count = 0x24;
            g->sa[i].height = 0;
            g->sb[i].flags = 0x10000000;
            g->sb[i].r = 0xD0;
            g->sb[i].g = 0xA0;
            g->sb[i].b = 0x70;
            g->sb[i].a = 0xFF;
            g->sb[i].radius = 5.0f;
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
        b262_01E007E0(&g->spr, tx[0], 0.3f);
        for (i = 0; i < 16; i++) {
            g->glow[i].flags = 1;
            g->glow[i].uv[0] = 0x8E;
            g->glow[i].uv[1] = 0;
            g->glow[i].uv[2] = 0x22;
            g->glow[i].uv[3] = 0x40;
            g->glow[i].c[2] = 0x80;
            g->glow[i].c[1] = 0x80;
            g->glow[i].c[0] = 0x80;
            g->glow[i].c[3] = 0x30;
            b262_01E007E0(&g->glow[i], tx[0], 0.8f);
        }
        g->bolt.tex = tx[0];
        g->bolt.flags = 0x1000000;
        g->bolt.uv[0] = 10;
        g->bolt.uv[1] = 0;
        g->bolt.uv[2] = 0x2A;
        g->bolt.uv[3] = 0x80;
        g->bolt.c[2] = 0x80;
        g->bolt.c[1] = 0x80;
        g->bolt.c[0] = 0x80;
        g->bolt.c[3] = 0x20;
        g->bolt.count = 14;
        g->bolt.tick = 0;
        g->bolt.step = 1;
        g->bolt.fade = 14;
        g->bolt.jitter = 100;
        g->bolt.nodes = g->mb;
        g->bolt.glow = g->glow;
        g->bolt.sa = g->sa;
        g->bolt.sb = g->sb;
        g->bolt.ac = g->glow[0].c[3];
        g->bolt.aa = g->sa[0].a;
        g->bolt.ab = g->sb[0].a;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->ja, &g->cam.pos);
    func_001F5F90(func_001F5380(), p = &v[2]);
    func_001038D0(&g->m0);
    func_001039A0(&g->ma);
    func_001039A0(&g->cam);
    for (i = 0; i < 16; i++) {
        func_001039A0(&g->mb[i]);
    }
    if (g->t < 200) {
        func_00103470((u8 *)&g->fade, 0x20, 4);
    } else {
        func_001032C0((u8 *)&g->fade, 0x80, 4);
    }
    func_001F6D00((u8)g->fade);
    if (g->t >= 25 && g->t < 200) {
        g->c[2] = g->disc.r = g->spr.c[2] = g->c[1] = g->disc.g = g->spr.c[1] = g->c[0] = g->disc.b = g->spr.c[0] =
            func_0019A5C8() % 64 + 64;
        b262_01E00120(ot, g->c);
        b262_01E00280(ot, &g->disc, &g->cam);
        func_001032C0(&g->disc.a, 0xFF, 0x10);
        b262_01E00940(ot, &g->spr, &g->cam);
        func_001032C0(&g->spr.c[3], 0x20, 2);
        for (i = 0; i < 64; i++) {
            g->spr.r[i].x += 0x80;
            g->spr.r[i].y += 0x80;
            g->spr.r[i].z += 0x80;
        }
        for (i = 0; i < 16; i++) {
            g->glow[i].c[2] = g->sa[i].r = g->sb[i].r = g->spr.c[2];
            g->glow[i].c[1] = g->sa[i].g = g->sb[i].g = g->spr.c[1];
            g->glow[i].c[0] = g->sa[i].b = g->sb[i].b = g->spr.c[0];
        }
        b262_01E00F50(ot, &g->bolt, g, &g->cam.pos, p);
    }
    g->t++;
    g->timer--;
    if (g->t == 200) {
        return 5;
    }
    if (g->t == 26) {
        return 1;
    }
    if (g->t >= 36 && g->t < 200) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
