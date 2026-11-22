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

static void func_01E00080_c509(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b000:01E02A30, 546 insns, 18 copies: draws one particle as a textured quad of the sprite's size, aspect-scaled,
   rotated by the sprite angle (flag 0x1F) or axis-aligned; depth-sorted unless flag 0x13.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E02A30;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b000_01E02A30;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b000_01E02A30 v[4];
    u8 tail[0x20];
} Pkt_b000_01E02A30;

typedef struct {
    s16 u, v, w, h;
    f32 fw, fh;
    u8 pad10[0x20];
    f32 size;
    Src_b000_01E02A30 color;
    s32 flags;
    u8 pad3C[8];
    s32 angle;
} Spr_b000_01E02A30;

typedef struct {
    void *texture;
    s32 flags;
    f32 scale;
    u8 padC[4];
    f32 x, y, z;
} Part_b000_01E02A30;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E02A30;

static s32 func_01E00120_c509(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00104DC0(void *, void *);
    f32 depth[4];
    Vec4f c;
    Pkt_b000_01E02A30 pkt;
    f32 kx;
    f32 ky;
    f32 r;
    f32 cs;
    f32 sn;
    f32 sz;
    f32 hx;
    f32 hy;

    ((Pkt_b000_01E02A30 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b000_01E02A30 *)(s32)&pkt)->pad = 0;
    if (func_00104520(s->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(s->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(s->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_c509((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
    func_00104DC0(&pkt, s);
    if (func_00104520(s->flags, 5) == 0) {
        if (func_00104520(s->flags, 0) != 0) {
            if (s->w > s->h) {
                kx = 1.0f;
                ky = (f32)s->h / (f32)s->w;
            } else if (s->w < s->h) {
                kx = (f32)s->w / (f32)s->h;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        } else {
            if (s->fw > s->fh) {
                ky = s->fh / s->fw;
                kx = 1.0f;
            } else if (s->fw < s->fh) {
                kx = s->fw / s->fh;
                ky = 1.0f;
            } else {
                ky = 1.0f;
                kx = 1.0f;
            }
        }
    } else {
        kx = 1.0f;
        ky = (f32)s->h / (f32)s->w;
    }
    if (func_00104520(s->flags, 0x1F) != 0) {
        r = 0.017453292f * (s->angle % 360);
        cs = func_0020B620(r);
        sn = func_0020B730(r);
        sz = p->scale * s->size;
        hy = ky * sz;
        hx = kx * sz;
        c.x = p->x + (cs * -hx - sn * hy);
        c.y = p->y + (sn * -hx + cs * hy);
        c.z = p->z;
        if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            p->flags |= 0x100000;
        }
        c.x = p->x + (cs * hx - sn * hy);
        c.y = p->y + (sn * hx + cs * hy);
        if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            p->flags |= 0x200000;
        }
        c.x = p->x + (cs * -hx - sn * -hy);
        c.y = p->y + (sn * -hx + cs * -hy);
        if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            p->flags |= 0x400000;
        }
        c.x = p->x + (cs * hx - sn * -hy);
        c.y = p->y + (sn * hx + cs * -hy);
        if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            p->flags |= 0x800000;
        }
    } else {
        c.x = p->x - kx * (p->scale * s->size);
        c.y = p->y + ky * (p->scale * s->size);
        c.z = p->z;
        if (func_00205440(&c, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            p->flags |= 0x100000;
        }
        c.x = p->x + kx * (p->scale * s->size);
        c.y = p->y + ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            p->flags |= 0x200000;
        }
        c.x = p->x - kx * (p->scale * s->size);
        c.y = p->y - ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            p->flags |= 0x400000;
        }
        c.x = p->x + kx * (p->scale * s->size);
        c.y = p->y - ky * (p->scale * s->size);
        if (func_00205440(&c, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            p->flags |= 0x800000;
        }
    }
    if (func_00104520(s->flags, 0x18) != 0) {
        func_00208700(&pkt, p->texture, 0);
    } else {
        if (func_00104520(s->flags, 0) != 0) {
            func_00208CB0(&pkt, (u64)0xA | ((u64)s->u << 4) | ((u64)(s->u + s->w - 1) << 14) |
                                    ((u64)s->v << 24) | ((u64)(s->v + s->h - 1) << 34));
        }
        func_00208700(&pkt, p->texture, 1);
    }
    if (func_00104520(p->flags, 0x14) != 0 && func_00104520(p->flags, 0x15) != 0 &&
        func_00104520(p->flags, 0x16) != 0 && func_00104520(p->flags, 0x17) != 0) {
        if (func_00104520(s->flags, 0x13) != 0) {
            pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
            func_002075F0(&pkt, obj, 0);
        } else {
            func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
        }
    }
    p->flags &= 0xFF0FFFFF;
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

static s32 func_01E009B0_c509(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_c509((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

static s32 func_01E01540_c509(Num_c508_01E013C0 *o, s16 x, s16 y, s32 n) {
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

static s32 func_01E01740_c509(s32 obj __attribute__((aligned(8))), Num_c508_01E015C0 *o, Pos_c508_01E015C0 *pos) {
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

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_c509_01E01EE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_c509_01E01EE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_c509_01E01EE0 p;
} Vtx_c509_01E01EE0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c509_01E01EE0 v[4];
    u64 tail;
} Pkt_c509_01E01EE0;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec_c509_01E01EE0 pts[28];
} Curve_c509_01E01EE0;

typedef struct {
    Vec_c509_01E01EE0 hist[8];
    u8 pad80[4];
    f32 width;
    u8 b, g, r, a;
    s32 n;
} Trail_c509_01E01EE0;

static s32 func_01E01EE0_c509(Trail_c509_01E01EE0 *t __attribute__((aligned(16))), u8 *cam, Vec_c509_01E01EE0 *pos, Vec_c509_01E01EE0 *out) {
    extern s32 func_00207F60(void);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_001018E0(f32, f32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00101600(void *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    s32 n4 __attribute__((aligned(16)));
    s32 mask __attribute__((aligned(16)));
    u8 fade __attribute__((aligned(16)));
    s32 s;
    Xyz_c509_01E01EE0 *nxt;
    Vec_c509_01E01EE0 *h;
    Curve_c509_01E01EE0 c;
    Xyz_c509_01E01EE0 xy[28];
    f32 dep[28];
    f32 w[28];
    Pkt_c509_01E01EE0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 j;
    s32 k;

    mask = 0;
    s = func_00207F60();
    n4 = (t->n + 2) * 4;
    fade = t->a / 28;
    if (t->n != 0) {
        for (i = 6, h = &t->hist[6]; i > -1; i--, h--) {
            h[1] = h[0];
            if (i == 0) {
                h->x = pos->x;
                h->y = pos->y;
                h->z = pos->z;
            }
        }
    } else {
        t->hist[2].x = t->hist[0].x;
        t->hist[2].y = t->hist[0].y;
        t->hist[2].z = t->hist[0].z;
        t->hist[0].x = pos->x;
        t->hist[0].y = pos->y;
        t->hist[0].z = pos->z;
        func_001036E0(t, &t->hist[2], &t->hist[1]);
    }
    c.n = t->n + 3;
    for (i = 0; i < t->n + 3; i++) {
        c.x[i] = t->hist[i].x;
        c.y[i] = t->hist[i].y;
        c.z[i] = t->hist[i].z;
    }
    func_00102550(&c);
    for (i = 0; i < n4; i++) {
        out[i].x = c.pts[i].x;
        out[i].y = c.pts[i].y;
        out[i].z = c.pts[i].z;
        if (func_00205440(&out[i], cam + 0x30, &xy[i], &dep[i]) != 0) {
            mask |= 1 << i;
        }
        w[i] = (28 - i) * (0.0357f * func_001018E0(t->width, dep[i]));
    }
    ((Pkt_c509_01E01EE0 *)(s32)&pkt)->count = 0x14;
    ((Pkt_c509_01E01EE0 *)(s32)&pkt)->tag = 8;
    ((Pkt_c509_01E01EE0 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_c509_01E01EE0 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = t->r;
    pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = t->g;
    pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = t->b;
    pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
    for (j = 0; j < n4 - 1; j++) {
        if (func_00104520(mask, j) == 0) {
            continue;
        }
        if (func_00104520(mask, j + 1) == 0) {
            continue;
        }
        pkt.v[0].a = 0;
        pkt.v[1].a = 0;
        pkt.v[2].a = fade * (28 - j);
        pkt.v[3].a = fade * (28 - (j + 1));
        if (j == 0) {
            pkt.v[3].a = 0;
            pkt.v[2].a = 0;
        }
        for (k = 0, nxt = &xy[j + 1]; k < 4; k++) {
            if (k < 2) {
                pkt.v[0].p.x = pkt.v[2].p.x = xy[j].x;
                pkt.v[1].p.x = pkt.v[3].p.x = xy[j + 1].x;
                if (k == 0) {
                    pkt.v[0].p.y = (u32)((f32)(u32)xy[j].y + w[j]);
                    pkt.v[1].p.y = (u32)((f32)(u32)xy[j + 1].y + w[j + 1]);
                    pkt.v[2].p.y = xy[j].y;
                    pkt.v[3].p.y = xy[j + 1].y;
                }
                if (k == 1) {
                    pkt.v[0].p.y = (u32)((f32)(u32)xy[j].y - w[j]);
                    pkt.v[1].p.y = (u32)((f32)(u32)xy[j + 1].y - w[j + 1]);
                    pkt.v[2].p.y = xy[j].y;
                    pkt.v[3].p.y = xy[j + 1].y;
                }
            } else {
                pkt.v[0].p.y = pkt.v[2].p.y = xy[j].y;
                pkt.v[1].p.y = pkt.v[3].p.y = xy[j + 1].y;
                if (k == 2) {
                    pkt.v[0].p.x = (u32)((f32)(u32)xy[j].x + w[j]);
                    pkt.v[1].p.x = (u32)((f32)(u32)xy[j + 1].x + w[j + 1]);
                    pkt.v[2].p.x = xy[j].x;
                    pkt.v[3].p.x = xy[j + 1].x;
                }
                if (k == 3) {
                    pkt.v[0].p.x = (u32)((f32)(u32)xy[j].x - w[j]);
                    pkt.v[1].p.x = (u32)((f32)(u32)xy[j + 1].x - w[j + 1]);
                    pkt.v[2].p.x = xy[j].x;
                    pkt.v[3].p.x = xy[j + 1].x;
                }
            }
            if (func_00101600(&pkt.v[0].p) == 0) {
                continue;
            }
            if (func_00101600(&pkt.v[1].p) == 0) {
                continue;
            }
            pkt.v[0].p.z = pkt.v[2].p.z = xy[j].z;
            pkt.v[1].p.z = pkt.v[3].p.z = nxt->z;
            func_002075F0(&pkt, 0, (u32)((dep[j] + dep[j + 1]) / 2.0f));
        }
    }
    func_00207FD0(s, func_00207500(), 0);
    if (t->n + 3 < 8) {
        t->n++;
    }
    return 0;
}

/* shape c509:01E02700 (c509), 794 insns, 1 copy: c509 scene manager: code >= 0 sets up three homing shots (camera at
   the func_001F53A0 grid cell, trail, three 3-emitter sets), the number (-(code & 0xFFFF), green or red), the hit
   sprite and the start speeds turned toward the target; else steers each shot to its target (straight for 5 ticks),
   draws its trail, bursts on arrival (8 when code >> 16), the counter while flag 0 runs, 2 once all three land; 8
   when done */

typedef struct {
    f32 x, y, z;
    u8 padC[0x14];
    Vec4f pos;
    u8 pad30[0x40];
} Cam_c509_01E02700;

typedef struct {
    Vec4f hist[8];
    s32 f80;
    f32 width;
    u8 c[4];
    s32 n;
    Vec4f pos;
} Trail_c509_01E02700;

typedef struct {
    s16 uv[8];
    u8 pad10[0x20];
    f32 size;
    u8 c[4];
    s32 flags;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Spr_c509_01E02700;

typedef struct {
    s32 tex;
    s32 flags;
    f32 scale;
    u8 c[4];
    f32 x, y, z;
    u8 pad1C[4];
} Part_c509_01E02700;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt_c509_01E02700;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    f32 cx, cy, cz;
    s32 w1C;
    s16 uv[8];
    Pt_c509_01E02700 pts[16];
    s16 count;
    s16 h132;
    s16 h134;
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Emit_c509_01E02700;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    s16 x, y;
    s16 uv[8];
    u8 pad20[0x20];
} Num_c509_01E02700;

typedef struct {
    s32 x, y, z, w;
} Pos_c509_01E02700;

typedef struct {
    Cam_c509_01E02700 c0;
    Trail_c509_01E02700 trail[3];
    Cam_c509_01E02700 cam[3];
    Spr_c509_01E02700 spr;
    Part_c509_01E02700 part;
    Emit_c509_01E02700 emA[3];
    Emit_c509_01E02700 emB[3];
    Emit_c509_01E02700 emC[3];
    Num_c509_01E02700 num;
    Pos_c509_01E02700 pos;
    Vec4f tp[3];
    Vec4f vel[3];
    f32 radius;
    s32 timer;
    s32 mode;
    s32 t;
    s32 flags;
    s32 cnt;
    s32 cx;
    s32 cz;
    Vec4f buf[3][28];
    Vec4f *ptrs[3];
    u8 pad160C[4];
} Scene_c509_01E02700;

static s32 func_01E02700_c509(s32 arg0, s32 code) {
    Scene_c509_01E02700 *g = (Scene_c509_01E02700 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern void func_00103260(s32 *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F53B0(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_00104520(s32, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_0019A5C8();
    Vec4f v;
    s32 tx[4];
    f32 m[16];
    Vec4f d;
    s32 ang[4];
    u8 r;
    u8 gr;
    s32 n;
    u8 b;
    s32 i;
    s32 j;
    s32 k;
    s32 ot;
    s32 t;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1610);
        func_00103890(&g->cam[0]);
        func_00103890(&g->cam[1]);
        func_00103890(&g->cam[2]);
        func_00103890(&g->c0);
        g->t = 0;
        g->timer = 0xB4;
        g->flags = 0;
        g->cnt = 4;
        n = -(code & 0xFFFF);
        if (code >> 16) {
            g->mode = 1;
        } else {
            g->mode = 0;
        }
        g->cx = func_001F53A0() & 0xFF;
        g->cz = func_001F53A0() >> 8;
        if (n >= 0) {
            r = 0x60;
            gr = 0xB0;
            b = 0x70;
        } else {
            r = 0xB0;
            gr = 0x50;
            b = 0x60;
        }
        g->pos.x = g->pos.y = g->pos.z = g->pos.w = 0;
        func_00103260(tx, 0);
        for (i = 0; i < 3; i++) {
            g->emA[i].tex = tx[0];
            g->emA[i].flags = 7;
            g->emA[i].cx = 0.0f;
            g->emA[i].cy = 15.0f;
            g->emA[i].cz = 0.0f;
            g->emA[i].w1C = 0;
            g->emA[i].uv[0] = 0;
            g->emA[i].uv[1] = 0;
            g->emA[i].uv[4] = 0;
            g->emA[i].uv[5] = 0;
            g->emA[i].uv[2] = 0x20;
            g->emA[i].uv[3] = 0x20;
            g->emA[i].uv[6] = 0x80;
            g->emA[i].uv[7] = 0x40;
            g->emA[i].size = 20.0f;
            g->emA[i].count = 8;
            g->emA[i].step = 3;
            g->emA[i].h13C = 1;
            g->emA[i].h140 = 8;
            g->emA[i].h136 = 10;
            g->emA[i].h138 = 10;
            g->emA[i].c[2] = 0x80;
            g->emA[i].c[1] = 0x80;
            g->emA[i].c[0] = 0x80;
            g->emA[i].c[3] = 0x60;
            for (j = 0; j < g->emA[i].count; j++) {
                g->emA[i].pts[j].x = g->emA[i].cx + (f32)(func_0019A5C8() % 20 - 10);
                g->emA[i].pts[j].y = g->emA[i].cy + (f32)(func_0019A5C8() % 16 - 4);
                g->emA[i].pts[j].z = g->emA[i].cz;
                g->emA[i].pts[j].life = -g->emA[i].step * j;
                g->emA[i].pts[j].pad = 0;
                g->emA[i].h13E = g->emA[i].h140 - 1;
            }
        }
        func_00103260(tx, 0xF);
        for (i = 0; i < 3; i++) {
            g->emB[i].tex = tx[0];
            g->emB[i].flags = 0x485;
            g->emB[i].cx = 0.0f;
            g->emB[i].cy = 20.0f;
            g->emB[i].cz = 0.0f;
            g->emB[i].w1C = 0;
            g->emB[i].uv[0] = 0xF0;
            g->emB[i].uv[1] = 0;
            g->emB[i].uv[4] = 0xF0;
            g->emB[i].uv[5] = 0;
            g->emB[i].uv[2] = 0x10;
            g->emB[i].uv[3] = 0x10;
            g->emB[i].uv[6] = 0x100;
            g->emB[i].uv[7] = 0x100;
            g->emB[i].size = 10.0f;
            g->emB[i].count = 8;
            g->emB[i].step = 3;
            g->emB[i].h13C = 1;
            g->emB[i].h140 = 8;
            g->emB[i].h136 = 0x1E;
            g->emB[i].h138 = 0x1E;
            g->emB[i].c[2] = 0x80;
            g->emB[i].c[1] = 0x80;
            g->emB[i].c[0] = 0x80;
            g->emB[i].c[3] = 0x60;
            for (j = 0; j < g->emB[i].count; j++) {
                g->emB[i].pts[j].x = g->emB[i].cx + (f32)(func_0019A5C8() % 20 - 10);
                g->emB[i].pts[j].y = g->emB[i].cy + (f32)(func_0019A5C8() % 16 - 4);
                g->emB[i].pts[j].z = g->emB[i].cz;
                g->emB[i].pts[j].life = -g->emB[i].step * j;
                g->emB[i].pts[j].pad = 0;
                g->emB[i].h13E = g->emB[i].h140 - 1;
            }
        }
        g->num.flags = 0x40200;
        g->num.tex = tx[0];
        g->num.uv[0] = 0;
        g->num.uv[1] = 0;
        g->num.uv[2] = 0xA;
        g->num.uv[3] = 0x10;
        g->num.uv[4] = 0;
        g->num.uv[5] = 8;
        g->num.uv[6] = 0x100;
        g->num.uv[7] = 0x100;
        g->num.c[2] = r;
        g->num.c[1] = gr;
        g->num.c[0] = b;
        g->num.c[3] = 0x80;
        func_01E01540_c509((Num_c508_01E013C0 *)&g->num, 0x1E, 0x30, n);
        func_00103260(tx, 7);
        g->spr.flags = 0x801;
        g->spr.uv[0] = 0;
        g->spr.uv[1] = 0;
        g->spr.uv[2] = 0x40;
        g->spr.uv[3] = 0x40;
        g->spr.uv[4] = 0;
        g->spr.uv[5] = 0;
        g->spr.uv[6] = 0x80;
        g->spr.uv[7] = 0x40;
        g->spr.size = 1.0f;
        g->spr.c[2] = 0x80;
        g->spr.c[1] = 0x80;
        g->spr.c[0] = 0x80;
        g->spr.c[3] = 0x80;
        g->spr.h48 = 0;
        g->spr.h4A = 0;
        g->spr.h4C = 0;
        g->spr.h4E = 1;
        g->spr.h50 = 0;
        g->spr.h52 = 0x3E7;
        t = tx[0];
        g->part.x = g->part.y = g->part.z = 0.0f;
        g->part.scale = 5.0f;
        g->part.tex = t;
        g->part.c[2] = 0x80;
        g->part.c[1] = 0x80;
        g->part.c[0] = 0x80;
        g->part.c[3] = 0x80;
        func_00103260(tx, 1);
        for (i = 0; i < 3; i++) {
            g->emC[i].flags = 0x40000001;
            g->emC[i].tex = tx[0];
            g->emC[i].cx = 0.0f;
            g->emC[i].cy = 0.0f;
            g->emC[i].cz = 0.0f;
            g->emC[i].w1C = 0;
            g->emC[i].uv[0] = 0;
            g->emC[i].uv[1] = 0;
            g->emC[i].uv[2] = 0x18;
            g->emC[i].uv[3] = 0x20;
            g->emC[i].uv[4] = 0;
            g->emC[i].uv[5] = 0;
            g->emC[i].uv[6] = 0x80;
            g->emC[i].uv[7] = 0x40;
            g->emC[i].size = 20.0f;
            g->emC[i].count = 8;
            g->emC[i].step = 1;
            g->emC[i].h13C = 1;
            g->emC[i].h140 = 10;
            g->emC[i].c[2] = 0x80;
            g->emC[i].c[1] = 0x80;
            g->emC[i].c[0] = 0x80;
            g->emC[i].c[3] = 0x20;
            g->emC[i].h132 = 0;
            for (j = 0; j < g->emC[i].count; j++) {
                g->emC[i].pts[j].x = g->emC[i].cx + (f32)(func_0019A5C8() % 20 - 10);
                g->emC[i].pts[j].y = g->emC[i].cy + (f32)(func_0019A5C8() % 16 - 4);
                g->emC[i].pts[j].z = g->emC[i].cz;
                g->emC[i].pts[j].life = -g->emC[i].step * j;
                g->emC[i].pts[j].pad = 0;
                g->emC[i].h13E = g->emC[i].h140 - 1;
            }
        }
        func_001F53B0(2, &g->c0.pos);
        g->ptrs[0] = g->buf[0];
        g->ptrs[1] = g->buf[1];
        g->ptrs[2] = g->buf[2];
        func_001E10F0(g->cx, g->cz, 0, &g->cam[0].pos);
        func_001E10F0(g->cx, g->cz, 0, &g->cam[1].pos);
        func_001E10F0(g->cx, g->cz, 0, &g->cam[2].pos);
        func_001F53C0(1, func_001F5380(), &g->tp[0]);
        func_001F53C0(1, func_001F5380(), &g->tp[1]);
        func_001F53C0(1, func_001F5380(), &g->tp[2]);
        g->radius = 30.0f;
        d.x = g->tp[0].x - g->cam[0].pos.x;
        d.z = g->tp[0].z - g->cam[0].pos.z;
        d.y = d.w = 0.0f;
        func_00103A30((f32 *)&d, ang);
        g->vel[0].x = 0.0f;
        g->vel[0].y = 12.0f;
        g->vel[0].z = 0.0f;
        g->vel[1].x = 8.4853f;
        g->vel[1].y = 8.4853f;
        g->vel[1].z = 0.0f;
        g->vel[2].x = -8.4853f;
        g->vel[2].y = 8.4853f;
        g->vel[2].z = 0.0f;
        func_0020C750(m, &g->vel[0], ang[1]);
        func_0020CDD0(&d, m, &g->vel[1]);
        g->vel[1].x = d.x;
        g->vel[1].y = d.y;
        g->vel[1].z = d.z;
        func_0020CDD0(&d, m, &g->vel[2]);
        g->vel[2].x = d.x;
        g->vel[2].y = d.y;
        g->vel[2].z = d.z;
        for (i = 0; i < 3; i++) {
            g->trail[i].f80 = 0;
            g->trail[i].c[2] = 0x80;
            g->trail[i].c[1] = 0x70;
            g->trail[i].c[0] = 0x50;
            g->trail[i].c[3] = 0x40;
            for (k = 0; k < 8; k++) {
                g->trail[i].hist[k].x = g->cam[i].pos.x;
                g->trail[i].hist[k].y = g->cam[i].pos.y;
                g->trail[i].hist[k].z = g->cam[i].pos.z;
            }
            g->trail[i].n = 0;
            g->trail[i].width = 500.0f;
        }
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001F53C0(1, func_001F5380(), &g->tp[i]);
        if (!func_00104520(g->flags, i + 10)) {
            if (g->t < 5) {
                g->cam[i].pos.x += g->vel[i].x;
                g->cam[i].pos.y += g->vel[i].y;
                g->cam[i].pos.z += g->vel[i].z;
            } else {
                func_00103EC0((f32 *)&g->cam[i].pos, (f32 *)&g->tp[i], (f32 *)&g->vel[i], 0xA00);
            }
            g->trail[i].pos.x = g->tp[i].x + g->cam[i].pos.x;
            g->trail[i].pos.y = g->tp[i].y + g->cam[i].pos.y;
            g->trail[i].pos.z = g->tp[i].z + g->cam[i].pos.z;
            g->trail[i].pos.w = 0.0f;
        }
        func_001039A0(&g->cam[i]);
        g->emC[i].h132 = (func_001037C0((u8 *)g, (s32)&g->trail[i], (s32)&g->trail[i].hist[1]) * 360) >> 16;
    }
    func_001038D0(g);
    if (func_00104520(g->flags, 0x1F)) {
        return 8;
    }
    if (func_00104520(g->flags, 0)) {
        if (g->cnt != 0) {
            g->cnt--;
        } else {
            g->flags |= 0x1C00;
        }
    }
    if (g->mode == 0) {
        if (func_00104520(g->flags, 0)) {
            func_01E01740_c509(ot, (Num_c508_01E015C0 *)&g->num, (Pos_c508_01E015C0 *)&g->pos);
        }
    }
    for (i = 0; i < 3; i++) {
        if (func_0020D100((f32 *)&g->trail[i].pos, (f32 *)&g->cam[i].pos) < g->radius) {
            g->flags |= 1 << (i + 10);
            if (g->mode == 1 && !func_00104520(g->flags, 0x1F)) {
                g->flags |= 0x80000000;
                return 8;
            }
        }
        if (!func_00104520(g->flags, 0x1F)) {
            if (func_00104520(g->flags, i + 10)) {
                v.x = v.y = v.z = 0.0f;
                func_01E009B0_c509(ot, (Cam_b001_01E00A30 *)&g->cam[i], (Emit_b001_01E00A30 *)&g->emA[i],
                                   (Vec_b001_01E00A30 *)&v);
                func_00103470(&g->emA[i].c[3], 0, 8);
                v.x = v.y = v.z = 1.01f;
                func_01E009B0_c509(ot, (Cam_b001_01E00A30 *)&g->cam[i], (Emit_b001_01E00A30 *)&g->emB[i],
                                   (Vec_b001_01E00A30 *)&v);
                if (!func_00103470(&g->emB[i].c[3], 0, 2)) {
                    return 8;
                }
            } else {
                v.x = v.y = v.z = 0.0f;
                func_01E009B0_c509(ot, (Cam_b001_01E00A30 *)&g->cam[i], (Emit_b001_01E00A30 *)&g->emC[0],
                                   (Vec_b001_01E00A30 *)&v);
                func_01E00120_c509(ot, (Spr_b000_01E02A30 *)&g->spr, (Part_b000_01E02A30 *)&g->part,
                                   (Cam_b000_01E02A30 *)&g->cam[i]);
            }
        }
        func_01E01EE0_c509((Trail_c509_01E01EE0 *)&g->trail[i], (u8 *)g, (Vec_c509_01E01EE0 *)&g->cam[i].pos,
                           (Vec_c509_01E01EE0 *)g->ptrs[i]);
    }
    if (g->mode == 0 && !func_00104520(g->flags, 0)) {
        if (func_00104520(g->flags, 10) || func_00104520(g->flags, 11) || func_00104520(g->flags, 12)) {
            g->flags |= 1;
            return 2;
        }
    }
    g->t++;
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c509", func_01E03380_c509);
