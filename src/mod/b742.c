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

static void func_01E00080_b742(Pk_b000_01E00080 *p, Src_b000_01E00080 *s, s32 mode) {
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

static void func_01E00100_b742(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E001A0_b742(void) {
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

static s32 func_01E002D0_b742(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00100_b742((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* shape b007:01E017F0, 355 insns, 16 copies: draws a sprite as two crossed quads: 8 corners (from a template, sized by
   two width/height pairs) rotated by the sprite's rotation, projected per quad, depth-sorted unless flag 0x13 */

typedef struct {
    u8 b, g, r, a;
} Src_b007_01E017F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b007_01E017F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b007_01E017F0 v[4];
    u8 tail[0x20];
} Pkt_b007_01E017F0;

typedef struct {
    f32 x, y, z, w;
} Vec_b007_01E017F0;

typedef struct {
    Vec_b007_01E017F0 v[8];
} Quad8_b007_01E017F0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b007_01E017F0 color;
    f32 w;
    f32 h;
    f32 w2;
    f32 h2;
    u8 pad1C[4];
    s16 u;
    s16 v;
    s16 tw;
    s16 th;
    u8 pad28[8];
    Vec_b007_01E017F0 rot;
} Spr_b007_01E017F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b007_01E017F0;

static s32 func_01E00E60_b742(s32 obj, Spr_b007_01E017F0 *spr, Cam_b007_01E017F0 *cam) {
    extern Quad8_b007_01E017F0 D_01E03500_b742;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad8_b007_01E017F0 in;
    Vec_b007_01E017F0 out[8];
    f32 m[16];
    f32 depth[4];
    Pkt_b007_01E017F0 pkt;
    s32 i;

    in = D_01E03500_b742;
    in.v[0].x = -spr->w;
    in.v[0].y = spr->h;
    in.v[1].x = spr->w;
    in.v[1].y = spr->h;
    in.v[2].x = -spr->w;
    in.v[2].y = -spr->h;
    in.v[3].x = spr->w;
    in.v[3].y = -spr->h;
    in.v[4].x = -spr->h2;
    in.v[4].y = spr->w2;
    in.v[5].x = spr->h2;
    in.v[5].y = spr->w2;
    in.v[6].x = -spr->h2;
    in.v[6].y = -spr->w2;
    in.v[7].x = spr->h2;
    in.v[7].y = -spr->w2;
    func_0020C630(m, &spr->rot);
    for (i = 0; i < 8; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00100_b742((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    func_00104540(&pkt, &spr->u, 0);
    for (i = 0; i < 2; i++) {
        if (func_00205440(&out[i * 4], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        if (func_00205440(&out[i * 4 + 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        if (func_00205440(&out[i * 4 + 2], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        if (func_00205440(&out[i * 4 + 3], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)spr->u << 4) | ((u64)(spr->u + spr->tw - 1) << 14) |
                                ((u64)spr->v << 24) | ((u64)(spr->v + spr->th - 1) << 34));
        func_00208700(&pkt, spr->texture, 1);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
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

static s32 func_01E013F0_b742(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

typedef struct W_tbl_func_01E01950_b742 {
    V4_b025_01E03CF0 v[6];
} W_tbl_func_01E01950_b742;

static s32 func_01E01950_b742(Obj_b025_01E03CF0 *o, s32 kind) {
    extern s32 func_0019A5C8();
    extern W_tbl_func_01E01950_b742 D_01E03580_b742;
    W_tbl_func_01E01950_b742 tbl_w = D_01E03580_b742;
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

static s32 func_01E01AF0_b742(s32 ot, Wall_b025_01E03E90 *o, Cam_b025_01E03E90 *cam __attribute__((aligned(16))),
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
    func_01E00100_b742((Vtx_b000_01E00100 *)&pkt, &o->col);
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

static s32 func_01E02200_b742(Obj_b000_01E04EC0 *o, s32 n, f32 v) {
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

static s32 func_01E02450_b742(s32 obj, Obj_b000_01E05110 *o, Cam_b000_01E05110 *cam, f32 v) {
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
            func_01E00080_b742((Pk_b000_01E00080 *)&pk, &o->color, 0);
        } else {
            func_01E00080_b742((Pk_b000_01E00080 *)&pk, &o->color, 1);
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

/* shape b742:01E029B0 (b742), 700 insns, 1 copy: b742 scene manager (b385:01E02AA0's form): code >= 0 sets up two
   shock walls, the 12-point spark emitter, the ring, the sprite and the disc; else follows joints, re-aims cameras at
   25/70/78/88, fades disc/sprite in by 20 and out to 125, walls from 70/78, ring fades 50..66 then out, sparks from
   25; 2 at tick 91, 1 at 60, 6 in 70..90, 8 when the timer ends */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Cam_b742_01E029B0;

typedef struct {
    f32 x;
    f32 y;
    u8 pad8[4];
    s16 frame;
    s16 ang;
} Pt_b742_01E029B0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    s32 rot[4];
    s16 uv[8];
    Pt_b742_01E029B0 pts[16];
    s16 h210;
    u8 pad212[4];
    s16 h216;
    s16 h218;
    s16 step;
    s16 h21C;
    s16 h21E;
    s16 h220;
    u8 pad222[0xE];
} Emit_b742_01E029B0;

typedef struct {
    s32 flags;
    u8 c[4];
    u8 pad8[0x408];
} Ring_b742_01E029B0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 w0, w1, h0, h1;
    u8 pad1C[4];
    s16 uv[4];
    u8 pad28[8];
    s32 rot[3];
    u8 pad3C[4];
} Spr_b742_01E029B0;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b742_01E029B0;

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 pad;
    s16 t;
} Seg_b742_01E029B0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 r;
    s16 uv[4];
    u8 pad18[8];
    Vec4f q[6];
    Seg_b742_01E029B0 *seg;
    f32 h;
    f32 w;
    f32 dy;
    f32 dx;
    s32 arc;
    s16 frame;
    s16 max;
    s16 n;
    s16 grow;
} Wall_b742_01E029B0;

typedef struct {
    Cam_b742_01E029B0 cam0;
    Cam_b742_01E029B0 cam1;
    Emit_b742_01E029B0 emit;
    Cam_b742_01E029B0 cam2;
    Ring_b742_01E029B0 ring;
    Cam_b742_01E029B0 cam3;
    Spr_b742_01E029B0 spr;
    Disc_b742_01E029B0 disc;
    Cam_b742_01E029B0 cam4;
    Wall_b742_01E029B0 wall;
    Seg_b742_01E029B0 segs[256];
    Cam_b742_01E029B0 cam5;
    Wall_b742_01E029B0 wall2;
    Seg_b742_01E029B0 segs2[256];
    s32 timer;
    s32 t;
    s32 code;
    s32 j[5];
} Scene_b742_01E029B0;

static s32 func_01E029B0_b742(s32 arg0, s32 code) {
    Scene_b742_01E029B0 *g = (Scene_b742_01E029B0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_00103390(void *, f32, f32);
    extern s32 func_0019A5C8();
    extern s32 b742_01E01AF0();
    Vec4f v[2];
    Vec4f vel;
    s32 tex[4];
    s32 ot;
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x29B0);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        func_00103890(&g->cam2);
        func_00103890(&g->cam4);
        func_00103890(&g->cam5);
        func_00103890(&g->cam3);
        g->j[0] = func_001F5560(func_001F53A0(), 0x18, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x23, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x14, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x1F, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0xE, 0);
        g->timer = 0x78;
        g->t = 1;
        g->code = code;
        func_00103290(tex, 0);
        g->wall.flags = 1;
        g->wall.uv[0] = 0;
        g->wall.uv[1] = 0;
        g->wall.uv[2] = 0x20;
        g->wall.uv[3] = 0x40;
        g->wall.c[2] = 0xB0;
        g->wall.c[1] = 0x70;
        g->wall.c[0] = 0x40;
        g->wall.c[3] = 0x80;
        g->wall.seg = g->segs;
        g->wall.h = 10.0f;
        g->wall.w = 15.0f;
        g->wall.dy = 12.0f;
        g->wall.dx = 0.0f;
        g->wall.arc = 0x10000;
        g->wall.r = 1.0f;
        g->wall.frame = 0;
        g->wall.max = 0x100;
        g->wall.n = 0x3E7;
        g->wall.grow = 3;
        func_01E01950_b742((Obj_b025_01E03CF0 *)&g->wall, tex[0]);
        g->wall2.flags = 1;
        g->wall2.uv[0] = 0;
        g->wall2.uv[1] = 0;
        g->wall2.uv[2] = 0x20;
        g->wall2.uv[3] = 0x40;
        g->wall2.c[2] = 0xB0;
        g->wall2.c[1] = 0x70;
        g->wall2.c[0] = 0x40;
        g->wall2.c[3] = 0x80;
        g->wall2.seg = g->segs2;
        g->wall2.h = 10.0f;
        g->wall2.w = 15.0f;
        g->wall2.dy = 12.0f;
        g->wall2.dx = 0.0f;
        g->wall2.arc = 0x10000;
        g->wall2.r = 1.0f;
        g->wall2.frame = 0;
        g->wall2.max = 0x100;
        g->wall2.n = 0x3E7;
        g->wall2.grow = 3;
        func_01E01950_b742((Obj_b025_01E03CF0 *)&g->wall2, tex[0]);
        func_00103260(tex, 0xF);
        g->emit.tex = tex[0];
        g->emit.flags = 0x80007;
        g->emit.rot[0] = 0;
        g->emit.rot[1] = 0;
        g->emit.rot[2] = 0;
        g->emit.uv[0] = 0x80;
        g->emit.uv[1] = 0xC0;
        g->emit.uv[2] = 0x20;
        g->emit.uv[3] = 0x20;
        g->emit.uv[4] = 0x80;
        g->emit.uv[5] = 0xC0;
        g->emit.uv[6] = 0x80;
        g->emit.uv[7] = 0x100;
        g->emit.size = 20.0f;
        g->emit.h210 = 0x10;
        g->emit.step = 1;
        g->emit.h21C = 1;
        g->emit.h220 = 8;
        g->emit.h216 = 0x1E;
        g->emit.h218 = -0x1E;
        g->emit.c[2] = 0xD0;
        g->emit.c[1] = 0x70;
        g->emit.c[0] = 0x30;
        g->emit.c[3] = 0x10;
        for (i = 0; i < 12; i++) {
            g->emit.pts[i].x = 0.1f * (f32)(func_0019A5C8() % 600 - 300);
            g->emit.pts[i].y = 0.1f * (f32)(func_0019A5C8() % 300);
            g->emit.pts[i].ang = -g->emit.step * i;
            g->emit.pts[i].frame = func_0019A5C8() % 8;
            g->emit.h21E = g->emit.h220 - 1;
        }
        g->ring.flags = 0x10080001;
        g->ring.c[2] = 0xD0;
        g->ring.c[1] = 0x70;
        g->ring.c[0] = 0x30;
        g->ring.c[3] = 0;
        {
            extern s32 b742_01E02200(void *, s32, f32);

            b742_01E02200(&g->ring, 0x40, 10.0f);
        }
        g->spr.tex = tex[0];
        g->spr.flags = 0x80000;
        g->spr.c[2] = 0x70;
        g->spr.c[1] = 0xD0;
        g->spr.c[0] = 0xA0;
        g->spr.c[3] = 0;
        g->spr.w0 = 0.5f;
        g->spr.w1 = 6.0f;
        g->spr.h0 = 0.5f;
        g->spr.h1 = 2.0f;
        g->spr.uv[0] = 0xB0;
        g->spr.uv[1] = 0x60;
        g->spr.uv[2] = 0x20;
        g->spr.uv[3] = 0x20;
        g->spr.rot[0] = 0;
        g->spr.rot[1] = 0;
        g->spr.rot[2] = 0;
        g->disc.flags = 0x80000;
        g->disc.c[2] = 0x70;
        g->disc.c[1] = 0xD0;
        g->disc.c[0] = 0xA0;
        g->disc.c[3] = 0;
        g->disc.radius = 4.0f;
        g->disc.count = 0x24;
        g->disc.height = 0;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->j[4], &g->cam3.pos);
    g->cam3.pos.y += 1.0f;
    func_001F5620(func_001F53A0(), g->j[0], &g->cam2.pos);
    switch (g->t) {
    case 0x19:
        func_001F5620(func_001F53A0(), g->j[0], &g->cam1.pos);
        g->emit.c[3] = 0x40;
        break;
    case 0x46:
        func_001F5620(func_001F53A0(), g->j[0], &g->cam1.pos);
        g->emit.c[3] = 0x80;
        g->emit.size = 15.0f;
        for (i = 0; i < 16; i++) {
            g->emit.pts[i].x = 0.1f * (f32)(func_0019A5C8() % 100 - 50);
            g->emit.pts[i].y = 0.1f * (f32)(func_0019A5C8() % 100 - 50);
            g->emit.pts[i].ang = -g->emit.step * i;
            g->emit.pts[i].frame = func_0019A5C8() % 8;
        }
        func_001F5620(func_001F53A0(), g->j[0], &g->cam4.pos);
        func_001F5620(func_001F53A0(), g->j[0], &v[0]);
        func_001F5620(func_001F53A0(), g->j[2], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->cam4.rot);
        break;
    case 0x4E:
        func_001F5620(func_001F53A0(), g->j[1], &g->cam5.pos);
        func_001F5620(func_001F53A0(), g->j[1], &v[0]);
        func_001F5620(func_001F53A0(), g->j[3], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->cam5.rot);
        break;
    case 0x58:
        func_001F5620(func_001F53A0(), g->j[0], &g->cam4.pos);
        func_001F5620(func_001F53A0(), g->j[0], &v[0]);
        func_001F5620(func_001F53A0(), g->j[2], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->cam4.rot);
        g->wall.r = 1.0f;
        for (i = 0; i < g->wall.max; i++) {
            g->wall.seg[i].a = 0x80;
            g->wall.seg[i].t = 0;
        }
        break;
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    func_001038D0(&g->cam2);
    func_001038D0(&g->cam4);
    func_001038D0(&g->cam5);
    func_001039A0(&g->cam3);
    func_01E001A0_b742();
    func_01E013F0_b742(ot, (Disc_b540_01E00250 *)&g->disc, (Cam_b540_01E00250 *)&g->cam3);
    func_01E00E60_b742(ot, (Spr_b007_01E017F0 *)&g->spr, (Cam_b007_01E017F0 *)&g->cam3);
    if (g->t < 0x14) {
        func_001032C0(&g->disc.c[3], 0x80, 8);
        func_001032C0(&g->spr.c[3], 0x80, 8);
    } else if (g->t >= 0x14 && g->t < 0x7D) {
        func_00103470(&g->disc.c[3], 0, 8);
        func_00103470(&g->spr.c[3], 0, 8);
    }
    if (g->t < 0x7D) {
        g->spr.rot[2] += 0x200;
    } else {
        g->spr.rot[2] = 0;
    }
    if (g->t >= 0x46) {
        b742_01E01AF0(ot, &g->wall, &g->cam4);
        {
            f32 r = 10.0f;

            func_00103390(&g->wall.r, r, 1.0f);
        }
        for (i = 0; i < g->wall.max; i++) {
            if (g->wall.seg[i].t > 4) {
                func_00103470(&g->wall.seg[i].a, 0, 0x10);
            }
        }
    }
    if (g->t >= 0x4E) {
        b742_01E01AF0(ot, &g->wall2, &g->cam5);
        {
            f32 r = 10.0f;

            func_00103390(&g->wall2.r, r, 1.0f);
        }
        for (i = 0; i < g->wall2.max; i++) {
            if (g->wall2.seg[i].t > 4) {
                func_00103470(&g->wall2.seg[i].a, 0, 0x10);
            }
        }
    }
    func_01E02450_b742(ot, (Obj_b000_01E05110 *)&g->ring, (Cam_b000_01E05110 *)&g->cam2, 1.5f);
    if (g->t >= 0x32 && g->t < 0x42) {
        func_001032C0(&g->ring.c[3], 0x80, 0x10);
    } else if (g->t >= 0x42) {
        func_00103470(&g->ring.c[3], 0, 0x20);
    }
    if (g->t >= 0x19 && g->t < 0x46) {
        vel.x = vel.y = vel.z = 0.0f;
        func_01E002D0_b742(ot, (Cam_b001_01E00A30 *)&g->cam1, (Emit_b001_01E00A30 *)&g->emit, (Vec_b001_01E00A30 *)&vel);
        func_00103470(&g->emit.c[3], 0, 4);
    } else if (g->t >= 0x46) {
        vel.x = vel.y = vel.z = 0.0f;
        func_01E002D0_b742(ot, (Cam_b001_01E00A30 *)&g->cam1, (Emit_b001_01E00A30 *)&g->emit, (Vec_b001_01E00A30 *)&vel);
        func_00103470(&g->emit.c[3], 0, 4);
    }
    g->t++;
    g->timer--;
    if (g->t == 0x5B) {
        return 2;
    }
    if (g->t == 0x3C) {
        return 1;
    }
    if (g->t >= 0x46 && g->t < 0x5B) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
