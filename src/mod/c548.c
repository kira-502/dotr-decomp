#include "common.h"

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_c508_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c508_01E00080;

typedef struct {
    Col_c508_01E00080 c;
    Xyz_c508_01E00080 p;
} Vtx_c508_01E00080;

typedef struct {
    u8 hdr[0x10];
    Vtx_c508_01E00080 v[3];
} Pkt_c508_01E00080;

static void func_01E00080_c548(Pkt_c508_01E00080 *p, u8 *c) {
    p->v[0].c.r = c[2];
    p->v[0].c.g = c[1];
    p->v[0].c.b = c[0];
    p->v[0].c.a = 0;
    p->v[0].c.q = 1.0f;
    p->v[1].c.r = c[2];
    p->v[1].c.g = c[1];
    p->v[1].c.b = c[0];
    p->v[1].c.a = c[3];
    p->v[1].c.q = 1.0f;
    p->v[2].c.r = c[2];
    p->v[2].c.g = c[1];
    p->v[2].c.b = c[0];
    p->v[2].c.a = c[3];
    p->v[2].c.q = 1.0f;
    p->v[0].p.f = 0;
    p->v[1].p.f = 0;
    p->v[2].p.f = 0;
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

static void func_01E00100_c548(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E001A0_c548(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00100_c548((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_c508_01E010C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_c508_01E010C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c508_01E010C0;

typedef struct {
    Col_c508_01E010C0 c;
    Xyz_c508_01E010C0 p;
} Vtx_c508_01E010C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c508_01E010C0 v[3];
    u64 tail;
} Pkt_c508_01E010C0;

typedef struct {
    Vec_c508_01E010C0 pts[32];
    u8 pad200[4];
    u8 col[4];
} Ring_c508_01E010C0;


static inline void tag_c508_01E010C0(Pkt_c508_01E010C0 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E00D30_c548(s32 tgt, Ring_c508_01E010C0 *r) {
    extern void c548_01E00080(void *, u8 *);
    extern void func_002075F0(void *, s32, s32);
    Pkt_c508_01E010C0 pkt __attribute__((aligned(8)));
    s32 i;
    Vec_c508_01E010C0 *p;

    tag_c508_01E010C0((Pkt_c508_01E010C0 *)(u32)&pkt, 0x13, 6, 0x414141);
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    for (i = 0, p = r->pts; i < 30; i++, p++) {
        c548_01E00080(&pkt, r->col);
        pkt.v[0].p.x = ((s32)r->pts[0].x + 0x800) << 4;
        pkt.v[0].p.y = ((s32)r->pts[0].z + 0x800) << 4;
        pkt.v[0].p.z = 0xFFFFFF;
        pkt.v[0].p.f = 0;
        if (i == 0) {
            pkt.v[1].p.x = ((s32)r->pts[1].x + 0x800) << 4;
            pkt.v[1].p.y = ((s32)r->pts[1].z + 0x800) << 4;
            pkt.v[1].p.z = 0xFFFFFF;
            pkt.v[1].p.f = 0;
        } else {
            pkt.v[1].p.x = ((s32)p[1].x + 0x800) << 4;
            pkt.v[1].p.y = ((s32)p[1].z + 0x800) << 4;
            pkt.v[1].p.z = 0xFFFFFF;
            pkt.v[1].p.f = 0;
        }
        if (i != 29) {
            pkt.v[2].p.x = ((s32)p[2].x + 0x800) << 4;
            pkt.v[2].p.y = ((s32)p[2].z + 0x800) << 4;
            pkt.v[2].p.z = 0xFFFFFF;
            pkt.v[2].p.f = 0;
        } else {
            pkt.v[2].p.x = ((s32)r->pts[1].x + 0x800) << 4;
            pkt.v[2].p.y = ((s32)r->pts[1].z + 0x800) << 4;
            pkt.v[2].p.z = 0xFFFFFF;
            pkt.v[2].p.f = 0;
        }
        func_002075F0(&pkt, tgt, 0);
    }
    return 0;
}

typedef struct {
    u8 pad00[0xC];
    s16 x;
    s16 y;
    u8 pad10[6];
    s16 width;
    u8 pad18[2];
    s16 base;
    u8 pad1C[4];
    s16 digit[5];
    s16 pos[5];
    s16 h34;
    s16 h36;
    s32 w38;
} Num_c508_01E013C0;

static s32 func_01E01030_c548(Num_c508_01E013C0 *o, s16 x, s16 y, s32 n) {
    s32 k;

    o->x = x;
    o->y = y;
    o->h36 = 0;
    o->h34 = 0;
    o->w38 = 0;
    if (n >= 0) {
        o->digit[0] = 11;
    } else {
        o->digit[0] = 10;
        n = -n;
    }
    if (n > 999) {
        o->digit[1] = n / 1000;
        o->digit[2] = n % 1000 / 100;
        o->digit[3] = n % 100 / 10;
        o->digit[4] = n % 10;
    } else if (n > 99) {
        o->digit[1] = n / 100;
        o->digit[2] = n % 100 / 10;
        o->digit[3] = n % 10;
        o->digit[4] = -1;
    } else if (n > 9) {
        o->digit[1] = n / 10;
        o->digit[2] = n % 10;
        o->digit[3] = -1;
        o->digit[4] = -1;
    } else {
        o->digit[1] = n % 10;
        o->digit[2] = -1;
        o->digit[3] = -1;
        o->digit[4] = -1;
    }
    for (k = 0; k < 5; k++) {
        o->pos[k] = o->base + o->width * o->digit[k];
    }
    return 0;
}

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    s32 pad;
} Uv_c508_01E015C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c508_01E015C0;

typedef struct {
    Uv_c508_01E015C0 uv;
    Xyz_c508_01E015C0 p;
} Vtx_c508_01E015C0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_c508_01E015C0 v[4];
    u8 tail[0x20];
} Pkt_c508_01E015C0;

typedef struct {
    u8 b, g, r, a;
} Src_c508_01E015C0;

typedef struct {
    void *tex;
    s32 flags;
    Src_c508_01E015C0 c;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 du;
    s16 dv;
    s16 u0;
    s16 v0;
    u8 pad1C[4];
    s16 digit[5];
    s16 anim[5];
    s16 x;
    s16 h36;
    s32 frame;
} Num_c508_01E015C0;

typedef struct {
    s32 x;
    s32 y;
    s32 pad;
    s32 off;
} Pos_c508_01E015C0;

static s32 func_01E01230_c548(s32 obj __attribute__((aligned(8))), Num_c508_01E015C0 *o, Pos_c508_01E015C0 *pos) {
    extern s32 func_00104520(s32, s32);
    Pkt_c508_01E015C0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 x;
    s32 half;
    s32 n;
    s32 t;

    if (o->digit[2] < 0) {
        n = 2;
        x = o->x - o->w;
    } else if (o->digit[3] < 0) {
        n = 3;
        x = o->x - (o->w + (o->w >> 1));
    } else if (o->digit[4] < 0) {
        n = 4;
        x = o->x - o->w * 2;
    } else {
        n = 5;
        x = o->x - ((o->w >> 1) + o->w * 2);
    }
    half = o->h >> 1;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->count = 0x24;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->tag = 9;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_c508_01E015C0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0x12) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    }
    pkt.r = o->c.r;
    pkt.g = o->c.g;
    pkt.b = o->c.b;
    pkt.a = o->c.a;
    pkt.q = 1.0f;
    for (i = 0; i < n; i++) {
        o->u = o->u0;
        if (func_00104520(o->flags, 9) != 0 && func_00104520(o->flags, i + 10) == 0) {
            o->v = o->anim[i];
            if (o->v >= o->dv * 12) {
                o->anim[i] = 0;
                o->v = 0;
            }
            o->anim[i] += 8;
        } else {
            o->v = o->v0 + o->dv * o->digit[i];
        }
        ((Pkt_c508_01E015C0 *)(s32)&pkt)->count |= 0x800;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[0].uv)->u = o->u * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[0].uv)->v = o->v * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[1].uv)->u = (o->u + o->du) * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[1].uv)->v = o->v * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[2].uv)->u = o->u * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[2].uv)->v = (o->v + o->dv) * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[3].uv)->u = (o->u + o->du) * 16;
        ((Uv_c508_01E015C0 *)(s32)&pkt.v[3].uv)->v = (o->v + o->dv) * 16;
        if (func_00104520(o->flags, 0x1C) != 0) {
            if (n % 2 == 0) {
                if ((t = x + o->w * i) <= -o->w * 2) {
                    pos->off = -pos->y;
                } else if (t <= -o->w) {
                    pos->off = -pos->y >> 1;
                } else if (t >= o->w) {
                    pos->off = pos->y;
                } else if (t >= 0) {
                    pos->off = pos->y >> 1;
                } else {
                    pos->off = 0;
                }
            } else {
                s32 d;
                if (-(o->w + (o->w >> 1)) > (d = x + o->w * i)) {
                    pos->off = -pos->y;
                } else if (d < -o->w >> 1) {
                    pos->off = -pos->y >> 1;
                } else if (d >= o->w + (o->w >> 1)) {
                    pos->off = pos->y;
                } else if (d >= o->w >> 1) {
                    pos->off = pos->y >> 1;
                } else {
                    pos->off = 0;
                }
            }
        }
        pkt.v[0].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * i))) << 4;
        pkt.v[0].p.y = (pos->y + 0x800 - half) << 4;
        pkt.v[0].p.z = 0xFFFFFF;
        pkt.v[0].p.f = 0;
        pkt.v[1].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * (i + 1)))) << 4;
        pkt.v[1].p.y = (pos->y + 0x800 - half) << 4;
        pkt.v[1].p.z = 0xFFFFFF;
        pkt.v[1].p.f = 0;
        pkt.v[2].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * i))) << 4;
        pkt.v[2].p.y = (pos->y + 0x800 + half) << 4;
        pkt.v[2].p.z = 0xFFFFFF;
        pkt.v[2].p.f = 0;
        pkt.v[3].p.x = (pos->off + (pos->x + 0x800 + (x + o->w * (i + 1)))) << 4;
        pkt.v[3].p.y = (pos->y + 0x800 + half) << 4;
        pkt.v[3].p.z = 0xFFFFFF;
        pkt.v[3].p.f = 0;
        func_00208700(&pkt, o->tex, 0);
        func_002075F0((s32)&pkt, obj, 0);
    }
    o->frame++;
    if (func_00104520(o->flags, 0xF) == 0) {
        if (o->frame == 4) {
            o->flags |= 0x400;
        } else if (o->frame == 8) {
            o->flags |= 0x800;
        } else if (o->frame == 12) {
            o->flags |= 0x1000;
        } else if (o->frame == 16) {
            o->flags |= 0x2000;
        } else if (o->frame == 20) {
            o->flags |= 0x4000;
        }
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

extern void c548_01E00100(Pkt_b013_01E010C0 *p, Src_b013_01E010C0 *s);

static s32 func_01E019D0_c548(s32 obj, Spark_b013_01E010C0 *sp, Cam_b013_01E010C0 *cam, s32 mode) {
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
    c548_01E00100(&pkt, &sp->color);
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

static s32 func_01E01FB0_c548(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E03100_c548;
    Tbl_b000_01E032C0 tbl = D_01E03100_c548;
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

static s32 func_01E02110_c548(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00100_c548((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

INCLUDE_ASM("asm/nonmatchings/mod/c548", func_01E02720_c548);
