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

static void func_01E00080_b079(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b079(s32 obj, Spr_b000_01E02A30 *s, Part_b000_01E02A30 *p, Cam_b000_01E02A30 *cam) {
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
    func_01E00080_b079((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&s->color);
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

/* shape b000:01E01140, 1595 insns, 70 copies: draws an emitter's particles. Each particle is either a camera-facing
   sprite (strip packet, 9 regs) sized by distance, or with flag 0x1F a quad (12 regs) turned by its own rotation;
   UV or ST frames animate per particle; flag 2 respawns a particle on a circle when its animation wraps.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b000_01E01140;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b000_01E01140;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E01140;

typedef union {
    UV_b000_01E01140 uv;
    struct {
        f32 s, t;
    } st;
} Tc_b000_01E01140;

typedef struct {
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx1_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx1_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt1_b000_01E01140;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Tc_b000_01E01140 tc;
    Xyz_b000_01E01140 xyz;
} Vtx2_b000_01E01140;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx2_b000_01E01140 v[4];
    u8 tail[0x20];
} Pkt2_b000_01E01140;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b000_01E01140;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E01140 color;
    f32 size;
    u8 pad10[0x10];
    Vec4f rot;
    union {
        struct {
            s16 u, v, w, h;
            s16 u0, v0, tw, th;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } r;
    Pt_b000_01E01140 *pts;
    Vec4f *rots;
    u8 pad48[4];
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b000_01E01140;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b000_01E01140;

#define UV1(k) ((UV_b000_01E01140 *)(s32)&p1.v[k].tc)
#define UV2(k) ((UV_b000_01E01140 *)(s32)&p2.v[k].tc)

static s32 func_01E009B0_b079(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
    extern s32 func_002058D0(void *, s32, void *, void *, f32 *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    f32 m[16];
    Vec4f c[4];
    Vec4f off;
    Vec4f tmp;
    Vec4f pos;
    Pkt1_b000_01E01140 p1 __attribute__((aligned(8)));
    Pkt2_b000_01E01140 p2 __attribute__((aligned(8)));
    f32 nx;
    f32 ny;
    f32 sx;
    f32 sy;
    s32 i;
    f32 hx;
    f32 hy;
    f32 dz;
    s32 a;

    ((Pkt1_b000_01E01140 *)(s32)&p1)->count = 0x24;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->tag = 9;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt1_b000_01E01140 *)(s32)&p1)->pad = 0;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->count = 0x34;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->tag = 0xC;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt2_b000_01E01140 *)(s32)&p2)->pad = 0;
    if (e->rate == 0) {
        e->rate = 1;
    }
    if (e->r.i.w == e->r.i.h) {
        sy = e->size;
        sx = sy;
    } else if (e->r.i.h < e->r.i.w) {
        sx = e->size;
        sy = sx * ((f32)e->r.i.h / (f32)e->r.i.w);
    } else {
        sy = e->size;
        sx = sy * ((f32)e->r.i.w / (f32)e->r.i.h);
    }
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x44);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x88);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x42);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&p1, ((u64)0x80 << 32) | 0x48);
        func_002086D0(&p2, ((u64)0x80 << 32) | 0x48);
    }
    p1.r = e->color.r;
    p1.g = e->color.g;
    p1.b = e->color.b;
    *(u8 *)(s32)&p1.a = e->color.a;
    p1.q = 1.0f;
    func_01E00080_b079((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
    if (func_00104520(e->flags, 3) != 0) {
        if (func_00104520(e->flags, 0) != 0) {
            ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
            UV1(0)->u = e->r.i.u * 16;
            UV1(0)->v = e->r.i.v * 16;
            UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(1)->v = e->r.i.v * 16;
            UV1(2)->u = e->r.i.u * 16;
            UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
            ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
            UV2(0)->u = e->r.i.u * 16;
            UV2(0)->v = e->r.i.v * 16;
            UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(1)->v = e->r.i.v * 16;
            UV2(2)->u = e->r.i.u * 16;
            UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
            UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
            UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
        } else {
            p1.v[0].tc.st.s = e->r.f.s;
            p1.v[0].tc.st.t = e->r.f.t;
            p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[1].tc.st.t = e->r.f.t;
            p1.v[2].tc.st.s = e->r.f.s;
            p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[0].tc.st.s = e->r.f.s;
            p2.v[0].tc.st.t = e->r.f.t;
            p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[1].tc.st.t = e->r.f.t;
            p2.v[2].tc.st.s = e->r.f.s;
            p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
        }
    }
    if (func_00104520(e->flags, 0x1C) != 0) {
        func_0020C630(m, &e->rot);
        for (i = 0; i < e->count; i++) {
            tmp.x = e->pts[i].x;
            tmp.y = e->pts[i].y;
            tmp.z = e->pts[i].z;
            func_0020CDD0(&off, m, &tmp);
            e->pts[i].x = off.x;
            e->pts[i].y = off.y;
            e->pts[i].z = off.z;
        }
    }
    nx = -sx;
    ny = -sy;
    for (i = 0; i < e->count; i++) {
        if (e->pts[i].a < e->color.a) {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->pts[i].a;
        } else {
            *(u8 *)(s32)&p1.a = p2.v[0].a = p2.v[1].a = p2.v[2].a = p2.v[3].a = e->color.a;
        }
        if (func_00104520(e->flags, 3) == 0) {
            if (func_00104520(e->flags, 0) != 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame % (e->r.i.tw / e->r.i.w));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame / (e->r.i.tw / e->r.i.w));
                } else {
                    e->r.i.u = e->r.i.u0 + e->r.i.w * (e->pts[i].frame / (e->r.i.th / e->r.i.h));
                    e->r.i.v = e->r.i.v0 + e->r.i.h * (e->pts[i].frame % (e->r.i.th / e->r.i.h));
                }
                ((Pkt1_b000_01E01140 *)(s32)&p1)->count |= 0x800;
                UV1(0)->u = e->r.i.u * 16;
                UV1(0)->v = e->r.i.v * 16;
                UV1(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(1)->v = e->r.i.v * 16;
                UV1(2)->u = e->r.i.u * 16;
                UV1(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV1(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV1(3)->v = (e->r.i.v + e->r.i.h) * 16;
                ((Pkt2_b000_01E01140 *)(s32)&p2)->count |= 0x800;
                UV2(0)->u = e->r.i.u * 16;
                UV2(0)->v = e->r.i.v * 16;
                UV2(1)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(1)->v = e->r.i.v * 16;
                UV2(2)->u = e->r.i.u * 16;
                UV2(2)->v = (e->r.i.v + e->r.i.h) * 16;
                UV2(3)->u = (e->r.i.u + e->r.i.w) * 16;
                UV2(3)->v = (e->r.i.v + e->r.i.h) * 16;
            } else {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.w));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.w));
                } else {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.h));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.h));
                }
                p1.v[0].tc.st.s = e->r.f.s;
                p1.v[0].tc.st.t = e->r.f.t;
                p1.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[1].tc.st.t = e->r.f.t;
                p1.v[2].tc.st.s = e->r.f.s;
                p1.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p1.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p1.v[3].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[0].tc.st.s = e->r.f.s;
                p2.v[0].tc.st.t = e->r.f.t;
                p2.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[1].tc.st.t = e->r.f.t;
                p2.v[2].tc.st.s = e->r.f.s;
                p2.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                p2.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                p2.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            }
        }
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&p1, e->texture, 0);
            func_00208700(&p2, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&p1, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
                func_00208CB0(&p2, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                       ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
            }
            func_00208700(&p1, e->texture, 1);
            func_00208700(&p2, e->texture, 1);
        }
        pos.x = e->pts[i].x;
        pos.y = e->pts[i].y;
        pos.z = e->pts[i].z;
        if (func_00104520(e->flags, 0x1A) != 0) {
            dz = -(e->amp * func_0020B550(e->freq * e->pts[i].t));
            pos.z += dz;
        }
        if (func_00104520(e->flags, 0x1F) != 0) {
            func_0020C630(m, &e->rots[i]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx = sx + sx * e->grow * e->pts[i].t;
                hy = sy + sy * e->grow * e->pts[i].t;
                off.x = -hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = -hy;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = -hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = hx;
                off.y = 0.0f;
                off.z = hy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            } else {
                off.x = nx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[0], m, &off);
                func_00103620(&c[0], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = ny;
                func_0020CDD0(&c[1], m, &off);
                func_00103620(&c[1], &pos);
                off.x = nx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[2], m, &off);
                func_00103620(&c[2], &pos);
                off.x = sx;
                off.y = 0.0f;
                off.z = sy;
                func_0020CDD0(&c[3], m, &off);
                func_00103620(&c[3], &pos);
                if (func_002058D0(c, 0x70000000, cam->view, &p2, depth) != 0 && e->pts[i].t >= 0) {
                    func_002075F0(&p2, obj, (u32)depth[0]);
                }
            }
        } else {
            if (func_00205440(&pos, cam->view, &p1.v[0].xyz, depth) != 0 && func_00101600(&p1.v[0].xyz) != 0) {
                e->flags |= 0xF00000;
            }
            depth[1] = depth[2] = depth[3] = depth[0];
            hx = 20.0f * func_001018E0(sx, depth[0]);
            hy = 20.0f * func_001018E0(sy, depth[0]);
            if (func_00104520(e->flags, 0x1B) != 0) {
                hx += sx * e->grow * e->pts[i].t;
                hy += sy * e->grow * e->pts[i].t;
            }
            p1.v[1].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[1].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[2].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[2].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[3].xyz.x = p1.v[0].xyz.x + hx;
            p1.v[3].xyz.y = p1.v[0].xyz.y + hy;
            p1.v[0].xyz.x = p1.v[0].xyz.x - hx;
            p1.v[0].xyz.y = p1.v[0].xyz.y - hy;
            p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = p1.v[0].xyz.z;
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
                func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
                if (func_00104520(e->flags, 0x13) != 0) {
                    p1.v[0].xyz.z = p1.v[1].xyz.z = p1.v[2].xyz.z = p1.v[3].xyz.z = 0xFFFFFF;
                    if (e->pts[i].t >= 0) {
                        func_002075F0(&p1, obj, 0);
                    }
                } else if (e->pts[i].t >= 0) {
                    func_002075F0(&p1, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
            e->flags &= 0xFF0FFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->pts[i].t++;
            if (e->pts[i].t % e->rate == 0) {
                e->pts[i].frame++;
                if (e->nframes == e->pts[i].frame) {
                    e->pts[i].frame = 0;
                    if (func_00104520(e->flags, 2) != 0) {
                        if (func_00104520(e->flags, 0x1D) != 0) {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = e->radius * func_0020B550(a);
                            e->pts[i].z = func_0019A5C8() % 20;
                            e->pts[i].x = e->radius * func_0020B480(a);
                        } else {
                            a = func_0019A5C8() % 0x10000;
                            e->pts[i].y = func_0019A5C8() % 20;
                            e->pts[i].z = e->radius * func_0020B480(a);
                            e->pts[i].x = e->radius * func_0020B550(a);
                        }
                    }
                }
            }
        }
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

static s32 func_01E022A0_b079(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_b079((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

static s32 func_01E02E30_b079(s32 obj, Wave_b025_01E016F0 *w, Cam_b025_01E016F0 *cam) {
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

static s32 func_01E03630_b079(Ring_b013_01E029E0 *o, Vec_b013_01E029E0 *center) {
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

static s32 func_01E03830_b079(s32 obj, Em_b013_01E02BE0 *o, Cam_b013_01E02BE0 *cam) {
    extern Quad_b013_01E02BE0 D_01E04F80_b079;
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

    in = D_01E04F80_b079;
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

/* shape b079:01E04240 (b079), 817 insns, 1 copy: b079 scene manager: code >= 0 clears the scene (0x1920), five
   coords, joints 0x18/0x17/0x14, a 250-tick timer, a 256-byte random wave table, a sprite with its part, the wave,
   three 16-point emitters, a 32-point burst emitter and the exhaust emitter; otherwise follows joint 2 with up to
   three coords from 115, puffs exhaust at every third tick of three windows, gathers the coords on the target then on
   coord 1, draws exhaust before 160, emitters and sprites from 177, wave and burst from 176; returns 2 at 222, 1 at
   166, 6 from 176, 8 when the timer ends */

typedef struct {
    u8 b, g, r, a;
} Col_b079_01E04240;

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    f32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Cam_b079_01E04240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 pad[3];
} Part_b079_01E04240;

typedef struct {
    void *texture;
    Col_b079_01E04240 color;
    s32 flags;
    Part_b079_01E04240 *parts;
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
    Part_b079_01E04240 pts[0x90];
} Exh_b079_01E04240;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_b079_01E04240 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_b079_01E04240;

typedef struct {
    s32 texture;
    s32 flags;
    f32 scale;
    Col_b079_01E04240 color;
    f32 x, y, z;
    u8 pad1C[4];
} Fx_b079_01E04240;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt1_b079_01E04240;

typedef struct {
    s32 tex;
    s32 flags;
    Col_b079_01E04240 color;
    f32 size;
    f32 x, y, z;
    s32 w1C;
    s16 h20, h22;
    s16 w, h;
    s16 tu, tv, tw, th;
    Pt1_b079_01E04240 pts[16];
    s16 count;
    s16 angle;
    s16 cur;
    s16 h136;
    s16 h138;
    s16 step;
    s16 h13C;
    s16 h13E;
    s16 h140;
    u8 pad142[0xE];
} Em1_b079_01E04240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt2_b079_01E04240;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b079_01E04240 color;
    f32 size;
    u8 pad10[0x10];
    f32 rx, ry, rz;
    u8 pad2C[4];
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Pt2_b079_01E04240 *pts;
    Vec4f *rots;
    s32 w48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b079_01E04240;

typedef struct {
    s32 texture;
    s32 flags;
    Col_b079_01E04240 color;
    u8 *tab;
    s16 u, v, w, h;
    u8 pad18[8];
    f32 size;
    f32 amp;
    s16 count;
    s16 frame;
    u8 phase;
    u8 pad2D[3];
} Wave_b079_01E04240;

typedef struct {
    Cam_b079_01E04240 cam0;
    Exh_b079_01E04240 exh;
    Cam_b079_01E04240 cams[3];
    Mdl_b079_01E04240 mdl;
    Fx_b079_01E04240 fx;
    Em1_b079_01E04240 em[3];
    Cam_b079_01E04240 cam1;
    Emit_b079_01E04240 emit;
    Pt2_b079_01E04240 pts[32];
    Vec4f rots[32];
    Cam_b079_01E04240 cam2;
    u8 pad14C0[0x2F0];
    Wave_b079_01E04240 wave;
    Vec4f target;
    s32 timer;
    s32 t;
    s32 code;
    s32 j[3];
    s32 n[3];
    u8 tab[256];
    u8 pad1914[0xC];
} Scene_b079_01E04240;

static s32 func_01E04240_b079(s32 arg0, s32 code) {
    Scene_b079_01E04240 *g = (Scene_b079_01E04240 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(void *, s32);
    extern void func_001039A0(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F53C0(s32, s32, void *);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00103470(void *, s32, s32);
    extern void func_001032C0(void *, s32, s32);
    extern void func_001033D0(void *, f32, f32);
    extern void func_001043F0(void *, f32);
    extern void func_00104490(void *, void *, s32);
    extern void func_001036E0(void *, void *, void *);
    extern void func_00103660(void *, void *);
    Vec4f v[3];
    Vec4f d;
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 k;
    s32 n;
    s32 m;
    s32 r;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1920);
        func_00103890(&g->cam0);
        func_00103890(&g->cam1);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->cams[i]);
        }
        func_00103890(&g->cam2);
        g->j[0] = func_001F5560(func_001F53A0(), 0x18, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x14, 0);
        g->timer = 250;
        g->t = 1;
        g->code = code;
        for (i = 0; i < 3; i++) {
            g->n[i] = 0x10;
        }
        for (i = 0; i < 256; i++) {
            g->tab[i] = func_0019A5C8() >> 4;
        }
        g->target.x = g->target.z = 0.0f;
        g->target.y = 50.0f;
        func_00103260(&tex, 7);
        g->mdl.flags = 0x801;
        g->mdl.r[0] = 0;
        g->mdl.r[1] = 0;
        g->mdl.r[2] = 0x40;
        g->mdl.r[3] = 0x40;
        g->mdl.r[4] = 0;
        g->mdl.r[5] = 0;
        g->mdl.r[6] = 0x80;
        g->mdl.r[7] = 0x40;
        g->mdl.f30 = 1.0f;
        g->mdl.color.r = 0x80;
        g->mdl.color.g = 0x80;
        g->mdl.color.b = 0x80;
        g->mdl.color.a = 0x80;
        g->mdl.h48 = 0;
        g->mdl.h4A = 0;
        g->mdl.h4C = 0;
        g->mdl.h4E = 1;
        g->mdl.h50 = 0;
        g->mdl.h52 = 999;
        r = tex;
        g->fx.z = 0.0f;
        g->fx.y = 0.0f;
        g->fx.x = 0.0f;
        g->fx.scale = 2.5f;
        g->fx.texture = r;
        g->fx.color.r = 0x80;
        g->fx.color.g = 0x80;
        g->fx.color.b = 0x80;
        g->fx.color.a = 0x80;
        g->wave.texture = tex;
        g->wave.tab = g->tab;
        g->wave.flags = 0x1000;
        g->wave.u = 0x40;
        g->wave.v = 0x40;
        g->wave.w = 0x20;
        g->wave.h = 0x20;
        g->wave.color.r = 0x80;
        g->wave.color.g = 0x80;
        g->wave.color.b = 0x80;
        g->wave.color.a = 0x80;
        g->wave.size = 1.5f;
        g->wave.amp = 0.05f;
        g->wave.frame = 0;
        g->wave.count = 0x100;
        g->wave.phase = 7;
        func_00103260(&tex, 1);
        for (i = 0; i < 3; i++) {
            g->em[i].flags = 0xC0000001;
            g->em[i].tex = tex;
            g->em[i].x = 0.0f;
            g->em[i].y = 0.0f;
            g->em[i].z = 0.0f;
            g->em[i].w1C = 0;
            g->em[i].h20 = 0;
            g->em[i].h22 = 0;
            g->em[i].w = 0x18;
            g->em[i].h = 0x20;
            g->em[i].tu = 0;
            g->em[i].tv = 0;
            g->em[i].tw = 0x80;
            g->em[i].th = 0x40;
            g->em[i].size = 5.0f;
            g->em[i].count = 0x10;
            g->em[i].step = 1;
            g->em[i].h13C = 1;
            g->em[i].h140 = 10;
            g->em[i].h136 = 3;
            g->em[i].h138 = 3;
            g->em[i].color.r = 0x80;
            g->em[i].color.g = 0x80;
            g->em[i].color.b = 0x80;
            g->em[i].color.a = 0x60;
            g->em[i].angle = -0x6000;
            for (k = 0; k < g->em[i].count; k++) {
                g->em[i].pts[k].x = g->em[i].x + 0.1f * (func_0019A5C8() % 60 - 30);
                g->em[i].pts[k].y = g->em[i].y + 0.1f * (func_0019A5C8() % 60 - 30);
                g->em[i].pts[k].z = g->em[i].z;
                g->em[i].pts[k].life = 0;
                g->em[i].pts[k].pad = func_0019A5C8() % 10;
                g->em[i].h13E = g->em[i].h140 - 1;
            }
        }
        g->emit.texture = tex;
        g->emit.flags = 0x48000003;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x40;
        g->emit.size = 20.0f;
        g->emit.rx = 0.0f;
        g->emit.ry = 0.0f;
        g->emit.rz = 0.0f;
        g->emit.u = 0;
        g->emit.v = 0;
        g->emit.w = 0x18;
        g->emit.h = 0x20;
        g->emit.u0 = 0;
        g->emit.v0 = 0;
        g->emit.tw = 0x80;
        g->emit.th = 0x40;
        g->emit.pts = g->pts;
        g->emit.rots = g->rots;
        g->emit.w48 = 0;
        g->emit.radius = 15.0f;
        g->emit.grow = 10.0f;
        g->emit.count = 0x20;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (k = 0; k < g->emit.count; k++) {
            func_001043F0(&d, 14.0f);
            g->pts[k].x = d.x;
            g->pts[k].y = d.y;
            g->pts[k].z = d.z;
            g->pts[k].t = -(func_0019A5C8() % 12);
            g->pts[k].a = 0x40;
            g->pts[k].frame = func_0019A5C8() % 8;
        }
        func_00103260(&tex, 0xF);
        g->exh.texture = (void *)tex;
        g->exh.color.r = 0xB0;
        g->exh.color.g = 0x70;
        g->exh.color.b = 0x40;
        g->exh.color.a = 0x30;
        g->exh.flags = 0x18003;
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
        g->exh.grow = 0.5f;
        g->exh.f38 = 2.3f;
        g->exh.h42 = 0;
        g->exh.h44 = 0x10;
        g->exh.n0 = 0x24;
        g->exh.n1 = 0;
        g->exh.mult = 4;
        g->exh.frames = 8;
        g->exh.rate = 0;
        for (i = 0; i < 3; i++) {
            g->cams[i].x = g->cams[i].y = g->cams[i].z = 0.1f;
        }
        g->cam2.x = g->cam2.y = g->cam2.z = 0.1f;
        return 0;
    }
    func_001F53C0(1, func_001F5380(), &g->cam1.pos);
    func_001F53C0(1, func_001F5380(), &g->cam2.pos);
    if (g->t < 0x73) {
        n = -1;
    } else if (g->t < 0x87) {
        n = 0;
    } else if (g->t < 0x9B) {
        n = 1;
    } else {
        n = 2;
    }
    for (i = 2; i > n; i--) {
        func_001F5620(func_001F53A0(), g->j[2], &g->cams[i].pos);
    }
    if (((g->t >= 0x6D && g->t < 0x76) || (g->t >= 0x81 && g->t < 0x8A) || (g->t >= 0x95 && g->t < 0x9E)) &&
        g->t % 3 == 0) {
        func_001F5620(func_001F53A0(), g->j[0], &v[0]);
        func_001F5620(func_001F53A0(), g->j[1], &v[1]);
        func_001F5620(func_001F53A0(), g->j[2], &v[2]);
        func_001036E0(&v[0], &v[1], &d);
        func_00103660(&d, &v[2]);
        g->exh.f20 = 0.2f * d.x;
        g->exh.f24 = 0.2f * d.y;
        g->exh.f28 = 0.2f * d.z;
        func_01E03630_b079((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&v[2]);
    }
    d.x = d.y = d.z = 0.0f;
    if (g->t == 0xA0) {
        for (i = 0; i < 3; i++) {
            g->cams[i].pos = g->target;
            g->n[i] = 0x10;
        }
    }
    if (g->t < 0xA0) {
        if (g->t >= 0x9A) {
            m = 3;
        } else if (g->t >= 0x86) {
            m = 2;
        } else {
            if (g->t >= 0x72) {
                m = 1;
            } else {
                m = 0;
            }
        }
        for (n = 0; n < m; n++) {
            func_001033D0(&g->cams[n], 1.0f, 0.1f);
            func_00104490(&g->cams[n].pos, &g->target, g->n[n]);
            g->n[n]--;
        }
    } else {
        if (g->t >= 0xC8) {
            n = 3;
        } else if (g->t >= 0xB4) {
            n = 2;
        } else {
            if (g->t >= 0xA0) {
                n = 1;
            } else {
                n = 0;
            }
        }
        for (k = 0; k < n; k++) {
            func_00104490(&g->cams[k].pos, &g->cam1.pos, g->n[k]);
            g->n[k]--;
        }
    }
    func_001038D0(&g->cam0);
    func_001039A0(&g->cam1);
    for (i = 0; i < 3; i++) {
        func_001039A0(&g->cams[i]);
    }
    func_001039A0(&g->cam2);
    if (g->t < 0xA0) {
        func_01E03830_b079(ot, (Em_b013_01E02BE0 *)&g->exh, (Cam_b013_01E02BE0 *)&g->cam0);
        for (i = 0; i < g->exh.n1; i++) {
            for (k = 0; k < g->exh.mult; k++) {
                g->exh.pts[k + i * g->exh.mult].y += 0.1f * k;
                func_00103470(&g->exh.pts[k + i * g->exh.mult].a, 0, 3);
            }
        }
    }
    if (g->t < 0xB1) {
        n = -1;
    } else if (g->t < 0xC5) {
        n = 0;
    } else if (g->t < 0xD9) {
        n = 1;
    } else {
        n = 2;
    }
    for (i = 2; i > n; i--) {
        d.x = d.y = d.z = 0.0f;
        func_01E022A0_b079(ot, (Cam_b001_01E00A30 *)&g->cams[i], (Emit_b001_01E00A30 *)&g->em[i],
                           (Vec_b001_01E00A30 *)&d);
        func_01E00120_b079(ot, (Spr_b000_01E02A30 *)&g->mdl, (Part_b000_01E02A30 *)&g->fx,
                           (Cam_b000_01E02A30 *)&g->cams[i]);
    }
    if (g->t >= 0xB0) {
        if (g->wave.frame > 0x14) {
            g->wave.frame = 0;
            g->wave.color.a = 0x80;
        }
        func_01E02E30_b079(ot, (Wave_b025_01E016F0 *)&g->wave, (Cam_b025_01E016F0 *)&g->cam2);
        func_00103470(&g->wave.color.a, 0, 8);
        func_001033D0(&g->cam2, 0.3f, 0.1f);
    }
    if (g->t >= 0xB0) {
        func_01E009B0_b079(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->cam1);
        if (g->t >= 0xDE) {
            func_00103470(&g->emit.color.a, 0, 2);
        } else {
            func_001032C0(&g->emit.color.a, 0x40, 1);
        }
        for (k = 0; k < g->emit.count; k++) {
            if (g->pts[k].t >= 0) {
                g->pts[k].x *= 1.03f;
                g->pts[k].y *= 1.03f;
                g->pts[k].z *= 1.03f;
                func_00103470(&g->pts[k].a, 0, 4);
            }
            if (g->pts[k].t >= 0x10) {
                func_001043F0(&d, 14.0f);
                g->pts[k].x = d.x;
                g->pts[k].y = d.y;
                g->pts[k].z = d.z;
                g->pts[k].t = 0;
                g->pts[k].a = 0x40;
            }
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0xDE) {
        return 2;
    }
    if (g->t == 0xA6) {
        return 1;
    }
    if (g->t >= 0xB0 && g->t < 0xDE) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
