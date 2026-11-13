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

static void func_01E00080_b736(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b736(void) {
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

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b000_01E001A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b000_01E001A0 v[2];
    u64 tail;
} Flat_b000_01E001A0;

typedef struct {
    f32 s, t;
    Xyz_b000_01E001A0 p;
} Tv_b000_01E001A0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b000_01E001A0 v[2];
    u64 tail;
} Tex_b000_01E001A0;

static s32 func_01E00250_b736(u8 *c) {
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern u64 func_00208D00(s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    Flat_b000_01E001A0 flat __attribute__((aligned(8)));
    Tex_b000_01E001A0 pk __attribute__((aligned(8)));
    u64 a;
    s32 b[3];
    s32 buf;

    buf = func_00207F60();
    ((Tex_b000_01E001A0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b000_01E001A0 *)(s32)&pk)->size = 5;
    ((Tex_b000_01E001A0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b000_01E001A0 *)(s32)&pk)->pad4 = 0;
    func_00208460();
    func_00208800(func_00209E50(), 0, &a, b);
    func_00208460();
    ((Flat_b000_01E001A0 *)(s32)&flat)->flags = 6;
    ((Flat_b000_01E001A0 *)(s32)&flat)->size = 3;
    ((Flat_b000_01E001A0 *)(s32)&flat)->regs = 0x441;
    ((Flat_b000_01E001A0 *)(s32)&flat)->pad4 = 0;
    flat.r = c[2];
    flat.g = c[1];
    flat.b = c[0];
    flat.a = c[3];
    flat.q = 1.0f;
    flat.v[0].x = 0x6BF8;
    flat.v[0].y = 0x71F8;
    flat.v[0].z = 0xFFFFFF;
    flat.v[0].f = 0;
    flat.v[1].x = 0x93F8;
    flat.v[1].y = 0x8DF8;
    flat.v[1].z = 0xFFFFFF;
    flat.v[1].f = 0;
    func_002086D0(&flat, func_00208D00(3));
    func_002075F0((s32)&flat, 0, 0);
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
    pk.a = 0x80 - c[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = 0.0f;
    pk.v[0].t = 0.0f;
    pk.v[1].s = 0.625f;
    pk.v[1].t = 0.875f;
    func_002086D0(&pk, func_00208D00(0));
    func_002075F0((s32)&pk, 0, 0);
    func_00207FD0(buf, func_00207500(), 0xFFFFFF);
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

static s32 func_01E004B0_b736(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b736((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* OVL_WARM */

/* shape b015:01E00280, 412 insns, 10 copies: 64-strip wave/water sprite.
   func_00205D10 is declared here returning u64 (functions.h says s32): the 24-bit z store takes its result
   with no sign extension, which only a 64-bit return type gives (an SCE-style u_long). */

typedef struct {
    f32 x, y, z, w;
} Vec_b015_01E00280;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b015_01E00280;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b015_01E00280;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b015_01E00280 st;
    Xyz_b015_01E00280 p;
} Vtx_b015_01E00280;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b015_01E00280 v[4];
    u8 pad70[8];
    u64 t78;
    u64 t80;
    u8 pad88[8];
} Pkt_b015_01E00280;

typedef struct {
    u8 pad00[0x30];
    f32 m[16];
} Cam_b015_01E00280;

typedef struct {
    s32 flags;
    u8 b04[6];
    s16 model;
    s32 step;
    s32 phase;
    f32 amp;
} Wave_b015_01E00280;

extern void b736_01E00080(Pkt_b015_01E00280 *, void *);

static s32 func_01E01DA0_b736(Wave_b015_01E00280 *o, Vec_b015_01E00280 *pos) {
    extern s32 func_00207F60(void);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208460(void);
    extern void func_001F7060(s32, s32, void *, void *);
    extern f32 func_001F5860(s32);
    extern u64 func_00205D10(void *, f32);
    extern f32 func_00205DF0(void *, f32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    u16 y;
    s32 x1;
    s32 x0;
    s32 d;
    s32 i;
    s32 h;
    Cam_b015_01E00280 cam;
    Pkt_b015_01E00280 pkt;
    Xyz_b015_01E00280 q;
    f32 dep;

    h = func_00207F60();
    func_00103890(&cam);
    func_001038D0(&cam);
    if (func_00205440(pos, cam.m, &q, &dep) == 0) {
        return -1;
    }
    ((Pkt_b015_01E00280 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b015_01E00280 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b015_01E00280 *)(s32)&pkt)->regs = 0x421421421421LL;
    ((Pkt_b015_01E00280 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    b736_01E00080(&pkt, o->b04);
    func_00208460();
    func_001F7060(o->model, 1, &pkt.t78, &pkt.t80);
    func_00208460();
    ((Pkt_b015_01E00280 *)(s32)&pkt)->count |= 0x800;
    for (i = 0; i < 64; i++) {
        y = i * 7 + 0x720;
        x0 = (s32)(o->amp * func_0020B550(o->phase + o->step * i));
        x1 = (s32)(o->amp * func_0020B550(o->phase + o->step * (i + 1)));
        pkt.v[0].p.x = ((x0 + 0x6C0) << 4) - 8;
        pkt.v[0].p.y = (y << 4) - 8;
        pkt.v[0].p.f = 0;
        pkt.v[1].p.x = ((x0 + 0x940) << 4) - 8;
        pkt.v[1].p.y = (y << 4) - 8;
        pkt.v[1].p.f = 0;
        pkt.v[2].p.x = ((x1 + 0x6C0) << 4) - 8;
        pkt.v[2].p.y = (((i + 1) * 7 + 0x720) << 4) - 8;
        pkt.v[2].p.f = 0;
        pkt.v[3].p.x = ((x1 + 0x940) << 4) - 8;
        pkt.v[3].p.y = (((i + 1) * 7 + 0x720) << 4) - 8;
        pkt.v[3].p.f = 0;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[0].st)->s = 0;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[0].st)->t = (i * 7) << 4;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[1].st)->s = 0x2800;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[1].st)->t = (i * 7) << 4;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[2].st)->s = 0;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[2].st)->t = ((i + 1) * 7) << 4;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[3].st)->s = 0x2800;
        ((Uv_b015_01E00280 *)(s32)&pkt.v[3].st)->t = ((i + 1) * 7) << 4;
        if (func_00104520(o->flags, 0x13) != 0) {
            pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFF;
            d = 0;
        } else if (func_00104520(o->flags, 0x12) != 0) {
            pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
            d = 0xFFFFFF;
        } else {
            pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = func_00205D10(pos, -func_001F5860(o->model));
            d = (u32)func_00205DF0(pos, -func_001F5860(o->model));
        }
        func_002075F0(&pkt, 0, d);
    }
    o->phase += o->step;
    func_00207FD0(h, func_00207500(), d);
    return 0;
}

/* shape b736:01E02410 (b736), 574 insns, 1 copy: b736 scene manager in b514:01E01A10 form: setup (three joints, a
   32-sparkle emitter, a 128-point rising ring, a b015 wave sprite and a glow colour), the flash over frames
   0x1C-0x3C, the wave from 0x3D on with its tint, then the sparkles and ring as in b514 with other timings and
   colours */

typedef struct {
    u8 pad[0x10];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b736_01E02410;

typedef struct {
    s32 flags;
    u8 col[4];
    s16 h8;
    s16 model;
    s32 step;
    s32 phase;
    f32 amp;
} Wave_b736_01E02410;

typedef struct {
    u8 crd[0x70];
    Crd_b736_01E02410 m;
    Emit_b000_01E01140 ring;
    Pt_b000_01E01140 rpts[0x80];
    Vec4f rrots[0x80];
    Crd_b736_01E02410 cam;
    Emit_b000_01E01140 emit;
    Pt_b000_01E01140 pts[32];
    u8 pad1410[0x20];
    Vec4f wpos;
    u8 pad1440[0x40];
    Wave_b736_01E02410 wave;
    u8 col[4];
    u8 glow[4];
    s32 timer;
    s32 t;
    s32 code;
    s32 j[3];
    u8 pad14B8[8];
} Scene_b736_01E02410;

static s32 func_01E02410_b736(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F63E0(s32, void *);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_001043F0(void *, f32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    Scene_b736_01E02410 *g = (Scene_b736_01E02410 *)arg0;
    s32 ot;
    Vec4f p;
    Vec4f v[2];
    s32 tex[4];
    s32 i;
    s32 a;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x14C0);
        func_00103890(g);
        func_00103890(&g->m);
        func_00103890(&g->cam);
        g->j[0] = func_001F5560(func_001F53A0(), 0x49, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x25, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 3, 0);
        g->timer = 0xDC;
        g->t = 1;
        g->code = code;
        g->glow[2] = 0x80;
        g->glow[1] = 0x30;
        g->glow[0] = 0x30;
        g->glow[3] = 0;
        g->wave.flags = 0x41000;
        g->wave.col[2] = 0x80;
        g->wave.col[1] = 0x80;
        g->wave.col[0] = 0x80;
        g->wave.col[3] = 0x80;
        g->wave.phase = 0;
        g->wave.step = 0x4000;
        g->wave.h8 = 0;
        g->wave.amp = 3.0f;
        g->wave.model = func_001F53A0();
        g->col[2] = 0x80;
        g->col[1] = 0x80;
        g->col[0] = 0x80;
        g->col[3] = 0x80;
        func_00103290(tex, 0);
        g->emit.texture = (void *)tex[0];
        g->emit.flags = 0x48080003;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x80;
        g->emit.size = 20.0f;
        g->emit.rot.x = 0.0f;
        g->emit.rot.y = 0.0f;
        g->emit.rot.z = 0.0f;
        g->emit.r.i.u = 0;
        g->emit.r.i.v = 0;
        g->emit.r.i.w = 0x20;
        g->emit.r.i.h = 0x20;
        g->emit.r.i.u0 = 0;
        g->emit.r.i.v0 = 0;
        g->emit.r.i.tw = 0x80;
        g->emit.r.i.th = 0x40;
        g->emit.pts = g->pts;
        g->emit.rots = NULL;
        *(s32 *)g->emit.pad48 = 0;
        g->emit.radius = 15.0f;
        g->emit.grow = 10.0f;
        g->emit.count = 0x20;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&p, 10.0f);
            g->pts[i].x = p.x;
            g->pts[i].y = p.y;
            g->pts[i].z = p.z;
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x80;
            g->pts[i].frame = func_0019A5C8() % 8;
        }
        func_00103290(tex, 1);
        g->ring.texture = (void *)tex[0];
        g->ring.flags = 0xF8000003;
        g->ring.color.r = 0x80;
        g->ring.color.g = 0x30;
        g->ring.color.b = 0x30;
        g->ring.color.a = 0;
        g->ring.size = 5.0f;
        g->ring.rot.x = 0.0f;
        g->ring.rot.y = 0.0f;
        g->ring.rot.z = 0.0f;
        g->ring.r.i.u = 0;
        g->ring.r.i.v = 0;
        g->ring.r.i.w = 0x40;
        g->ring.r.i.h = 0x40;
        g->ring.r.i.u0 = 0;
        g->ring.r.i.v0 = 0;
        g->ring.r.i.tw = 0x100;
        g->ring.r.i.th = 0x40;
        g->ring.pts = g->rpts;
        g->ring.rots = g->rrots;
        *(s32 *)g->ring.pad48 = 0;
        g->ring.radius = 3.0f;
        g->ring.grow = 0.5f;
        g->ring.count = 0x80;
        g->ring.nframes = 4;
        g->ring.rate = 0;
        for (i = 0; i < g->ring.count; i++) {
            a = func_0019A5C8() % 0x10000;
            g->rpts[i].y = func_0019A5C8() % 20;
            g->rpts[i].z = g->ring.radius * func_0020B480(a);
            g->rpts[i].x = g->ring.radius * func_0020B550(a);
            g->rpts[i].t = -(func_0019A5C8() % 20);
            g->rpts[i].a = 0;
            g->rpts[i].frame = 0;
        }
        return 0;
    }
    func_001F5F90(func_001F5380(), &v[0]);
    func_001F5620(func_001F53A0(), g->j[1], &v[1]);
    func_001F5620(func_001F53A0(), g->j[1], &g->m.pos);
    func_00103DB0(&v[0], &v[1], &g->m.rot);
    func_001F53C0(1, func_001F5380(), &g->cam.pos);
    func_001F53C0(1, func_001F53A0(), &g->wpos);
    func_001038D0(g);
    func_001038D0(&g->m);
    func_001038D0(&g->cam);
    if (g->t >= 0x1C && g->t < 0x3D) {
        func_01E00120_b736();
    }
    if (g->t >= 0x3D) {
        g->col[3] = 0x80 - g->wave.col[3];
        func_01E01DA0_b736((Wave_b015_01E00280 *)&g->wave, (Vec_b015_01E00280 *)&g->wpos);
        func_001F63E0(g->wave.model, g->col);
        if (g->t > 0xC8) {
            func_00103470(&g->wave.col[3], 0, 8);
        }
    }
    if (g->t >= 0xC8) {
        func_00103470(&g->glow[3], 0, 8);
    } else {
        func_001032C0(&g->glow[3], 0x80, 8);
    }
    func_01E00250_b736(g->glow);
    func_01E004B0_b736(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->cam);
    if (g->t >= 0x35 && g->t < 0x3D) {
        func_00103470(&g->emit.color.a, 0, 4);
    } else if (g->t > 0xC8) {
        func_00103470(&g->emit.color.a, 0, 8);
    } else {
        func_001032C0(&g->emit.color.a, 0x80, 4);
    }
    for (i = 0; i < g->emit.count; i++) {
        if (g->pts[i].t >= 0) {
            g->pts[i].x *= 1.03f;
            g->pts[i].y *= 1.03f;
            g->pts[i].z *= 1.03f;
            func_00103470(&g->pts[i].a, 0, 8);
        }
        if (g->pts[i].t >= 0x10) {
            func_001043F0(&p, 10.0f);
            g->pts[i].x = p.x;
            g->pts[i].y = p.y;
            g->pts[i].z = p.z;
            g->pts[i].t = 0;
            g->pts[i].a = 0x80;
        }
    }
    func_01E004B0_b736(ot, (Emit_b000_01E01140 *)&g->ring, (Cam_b000_01E01140 *)&g->m);
    if (g->t >= 0xC8) {
        func_00103470(&g->ring.color.a, 0, 8);
    } else {
        func_001032C0(&g->ring.color.a, 0x80, 8);
    }
    for (i = 0; i < g->ring.count; i++) {
        if (g->rpts[i].t >= 0) {
            if (g->rpts[i].y < 180.0f) {
                g->rpts[i].t = 0;
                if (i % 3 == 0) {
                    g->rpts[i].y += 8.0f;
                } else if (i % 3 == 1) {
                    g->rpts[i].y += 9.0f;
                } else {
                    g->rpts[i].y += 10.0f;
                }
                g->rpts[i].z *= 1.12f;
                g->rpts[i].x *= 1.12f;
            }
            if (g->t >= 0x35) {
                func_001032C0(&g->rpts[i].a, 0x80, 0x20);
            }
            if (g->rpts[i].y >= 180.0f && g->rpts[i].t > 4) {
                a = func_0019A5C8() % 0x10000;
                g->rpts[i].t = -(func_0019A5C8() % 20);
                g->rpts[i].z = g->ring.radius * func_0020B480(a);
                g->rpts[i].x = g->ring.radius * func_0020B550(a);
                g->rpts[i].y = func_0019A5C8() % 20;
                g->rpts[i].a = 0;
            }
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0xC8) {
        return 2;
    }
    if (g->t == 0x36) {
        return 1;
    }
    if (g->t >= 0x40 && g->t < 0xC8) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
