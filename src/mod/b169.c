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

static void func_01E00080_b169(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

extern void b169_01E00080(Pkt_b015_01E00280 *, void *);

static s32 func_01E00120_b169(Wave_b015_01E00280 *o, Vec_b015_01E00280 *pos) {
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
    b169_01E00080(&pkt, o->b04);
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

static s32 func_01E00790_b169(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b169((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* shape b039:01E01B70, 1004 insns, 6 copies: draws an emitter's particles as camera-facing squares (one strip packet),
   sized by distance (and age with flag 0x1B), bobbing along z; UV or ST frames animate per particle; flag 0x1C
   first turns all points by the emitter's rotation. Same emitter layout as shape b000:01E01140. */

typedef struct {
    u8 b, g, r, a;
} Src_b039_01E01B70;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b039_01E01B70;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b039_01E01B70;

typedef union {
    UV_b039_01E01B70 uv;
    struct {
        f32 s, t;
    } st;
} Tc_b039_01E01B70;

typedef struct {
    Tc_b039_01E01B70 tc;
    Xyz_b039_01E01B70 xyz;
} Vtx_b039_01E01B70;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b039_01E01B70 v[4];
    u8 tail[0x20];
} Pkt_b039_01E01B70;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b039_01E01B70;

typedef struct {
    void *texture;
    s32 flags;
    Src_b039_01E01B70 color;
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
    Pt_b039_01E01B70 *pts;
    Vec4f *rots;
    u8 pad48[4];
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b039_01E01B70;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b039_01E01B70;

#define UV1(k) ((UV_b039_01E01B70 *)(s32)&pkt.v[k].tc)

static s32 func_01E02080_b169(s32 obj, Emit_b039_01E01B70 *e, Cam_b039_01E01B70 *cam __attribute__((aligned(16)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    f32 depth[4];
    f32 m[16];
    Vec4f off;
    Vec4f tmp;
    Pkt_b039_01E01B70 pkt __attribute__((aligned(8)));
    s32 i;
    f32 w;

    ((Pkt_b039_01E01B70 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b039_01E01B70 *)(s32)&pkt)->tag = 9;
    ((Pkt_b039_01E01B70 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b039_01E01B70 *)(s32)&pkt)->pad = 0;
    if (e->rate == 0) {
        e->rate = 1;
    }
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->color.r;
    pkt.g = e->color.g;
    pkt.b = e->color.b;
    *(u8 *)(s32)&pkt.a = e->color.a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        if (func_00104520(e->flags, 0) != 0) {
            ((Pkt_b039_01E01B70 *)(s32)&pkt)->count |= 0x800;
            UV1(0)->u = e->r.i.u * 16;
            UV1(0)->v = e->r.i.v * 16;
            UV1(1)->u = (e->r.i.u + e->r.i.w - 1) * 16;
            UV1(1)->v = e->r.i.v * 16;
            UV1(2)->u = e->r.i.u * 16;
            UV1(2)->v = (e->r.i.v + e->r.i.h - 1) * 16;
            UV1(3)->u = (e->r.i.u + e->r.i.w - 1) * 16;
            UV1(3)->v = (e->r.i.v + e->r.i.h - 1) * 16;
        } else {
            pkt.v[0].tc.st.s = e->r.f.s;
            pkt.v[0].tc.st.t = e->r.f.t;
            pkt.v[1].tc.st.s = e->r.f.s + e->r.f.w;
            pkt.v[1].tc.st.t = e->r.f.t;
            pkt.v[2].tc.st.s = e->r.f.s;
            pkt.v[2].tc.st.t = e->r.f.t + e->r.f.h;
            pkt.v[3].tc.st.s = e->r.f.s + e->r.f.w;
            pkt.v[3].tc.st.t = e->r.f.t + e->r.f.h;
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
    for (i = 0; i < e->count; i++) {
        if (e->pts[i].a < e->color.a) {
            *(u8 *)(s32)&pkt.a = e->pts[i].a;
        } else {
            *(u8 *)(s32)&pkt.a = e->color.a;
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
                ((Pkt_b039_01E01B70 *)(s32)&pkt)->count |= 0x800;
                UV1(0)->u = e->r.i.u * 16;
                UV1(0)->v = e->r.i.v * 16;
                UV1(1)->u = (e->r.i.u + e->r.i.w - 1) * 16;
                UV1(1)->v = e->r.i.v * 16;
                UV1(2)->u = e->r.i.u * 16;
                UV1(2)->v = (e->r.i.v + e->r.i.h - 1) * 16;
                UV1(3)->u = (e->r.i.u + e->r.i.w - 1) * 16;
                UV1(3)->v = (e->r.i.v + e->r.i.h - 1) * 16;
            } else {
                if (func_00104520(e->flags, 1) != 0) {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.w));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.w));
                } else {
                    e->r.f.s = e->r.f.w * (e->pts[i].frame / (s16)(s32)(1.0f / e->r.f.h));
                    e->r.f.t = e->r.f.h * (e->pts[i].frame % (s16)(s32)(1.0f / e->r.f.h));
                }
                pkt.v[0].tc.st.s = e->r.f.s;
                pkt.v[0].tc.st.t = e->r.f.t;
                pkt.v[1].tc.st.s = e->r.f.s + e->r.f.w;
                pkt.v[1].tc.st.t = e->r.f.t;
                pkt.v[2].tc.st.s = e->r.f.s;
                pkt.v[2].tc.st.t = e->r.f.t + e->r.f.h;
                pkt.v[3].tc.st.s = e->r.f.s + e->r.f.w;
                pkt.v[3].tc.st.t = e->r.f.t + e->r.f.h;
            }
        }
        off.x = e->pts[i].x;
        off.y = e->pts[i].y;
        off.z = e->pts[i].z - e->amp * func_0020B550(e->freq * e->pts[i].t);
        if (func_00205440(&off, cam->view, &pkt.v[0].xyz, &depth[0]) != 0 && func_00101600(&pkt.v[0].xyz) != 0) {
            e->flags |= 0xF00000;
        }
        depth[1] = depth[2] = depth[3] = depth[0];
        w = 20.0f * func_001018E0(e->size, depth[0]);
        if (func_00104520(e->flags, 0x1B) != 0) {
            w += e->grow * e->pts[i].t;
        }
        pkt.v[1].xyz.x = pkt.v[0].xyz.x + w;
        pkt.v[1].xyz.y = pkt.v[0].xyz.y - w;
        pkt.v[2].xyz.x = pkt.v[0].xyz.x - w;
        pkt.v[2].xyz.y = pkt.v[0].xyz.y + w;
        pkt.v[3].xyz.x = pkt.v[0].xyz.x + w;
        pkt.v[3].xyz.y = pkt.v[0].xyz.y + w;
        pkt.v[0].xyz.x = pkt.v[0].xyz.x - w;
        pkt.v[0].xyz.y = pkt.v[0].xyz.y - w;
        pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = pkt.v[0].xyz.z;
        if (func_00104520(e->flags, 0x18) != 0) {
            func_00208700(&pkt, e->texture, 0);
        } else {
            if (func_00104520(e->flags, 0) != 0) {
                func_00208CB0(&pkt, (u64)0xA | ((u64)e->r.i.u << 4) | ((u64)(e->r.i.u + e->r.i.w - 1) << 14) |
                                        ((u64)e->r.i.v << 24) | ((u64)(e->r.i.v + e->r.i.h - 1) << 34));
            }
            func_00208700(&pkt, e->texture, 1);
        }
        if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0 &&
            func_00104520(e->flags, 0x16) != 0 && func_00104520(e->flags, 0x17) != 0) {
            if (func_00104520(e->flags, 0x13) != 0) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                if (e->pts[i].t >= 0) {
                    func_002075F0(&pkt, obj, 0);
                }
            } else if (e->pts[i].t >= 0) {
                func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        e->flags &= 0xFF0FFFFF;
        if (func_00104520(e->flags, 3) == 0) {
            e->pts[i].t++;
            if (e->pts[i].t % e->rate == 0) {
                e->pts[i].frame++;
                if (e->nframes == e->pts[i].frame) {
                    e->pts[i].frame = 0;
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

static s32 func_01E03030_b169(s32 obj, Cam_b001_01E00A30 *cam, Emit_b001_01E00A30 *e, Vec_b001_01E00A30 *vel) {
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
    func_01E00080_b169((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&e->color);
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

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b039_01E036B0;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x18];
    f32 vx, vy, vz;
    u8 pad2C[4];
    f32 sx;
    u8 pad34[6];
    u8 kind;
    u8 pad3B[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b039_01E036B0;

static s32 func_01E03BC0_b169(Obj_b039_01E036B0 *obj, Pt_b039_01E036B0 *pts, f32 *pos) {
    s32 i;
    Pt_b039_01E036B0 *p;
    Pt_b039_01E036B0 *q;
    s32 j;

    i = obj->idx;
    if (i > -1) {
        p = &pts[i];
        do {
            if (p->e > obj->limit && func_00103470(&p->c, 0, obj->kind) == 0 && p[-1].c == 0) {
                obj->idx = i;
            }
            i--;
            p--;
        } while (i > -1);
    }
    if (obj->idx < obj->count - 1) {
        obj->idx++;
        j = obj->idx;
        if (j > 0) {
            q = &pts[j];
            do {
                j--;
                q->x = obj->vx + q[-1].x;
                q->x = q->x * obj->sx;
                q->y = obj->vy + q[-1].y;
                q->z = obj->vz + q[-1].z;
                q->d = q[-1].d;
                q->e = q[-1].e;
                q->c = q[-1].c;
                q--;
            } while (j > 0);
        }
        pts->x = pos[0];
        pts->y = pos[1];
        pts->z = pos[2];
        pts->d = 0;
        pts->e = 0;
        pts->c = obj->c;
    }
    return 0;
}

/* OVL_CFLAGS: -O3,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b039:01E03820, 630 insns: draws a ribbon trail through cnt points (0x10 bytes each): each piece between
   two projected points is one or two textured quads (flag 0x1E: below and above the line, else one quad
   across it) as wide as func_001018E0(base + grow * age, depth); alpha = min(object alpha, point alpha), first
   piece fades in from 0. Then every point ages by one. Colour from the module helper b039:01E00080.
   The point pointer is the compiler's induction variable (last spill slot), so the source indexes pts[i - 1] / pts[i];
   cam is aligned(16) to put its home at 0xF0. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b039_01E03820;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b039_01E03820;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b039_01E03820 uv;
    Xyz_b039_01E03820 xyz;
} Vtx_b039_01E03820;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b039_01E03820 v[4];
    u8 tail[0x20];
} Pkt_b039_01E03820;

typedef struct {
    s16 u, v, w, h;
} Rect_b039_01E03820;

typedef struct {
    void *texture;
    u8 color[3];
    u8 a;
    s32 flags;
    f32 base;
    Rect_b039_01E03820 rect;
    u8 pad18[0x1C];
    f32 grow;
    u8 pad38[4];
    s16 tick;
    u8 pad3E[2];
    s16 n1;
    s16 n2;
} Trail_b039_01E03820;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b039_01E03820;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b039_01E03820;


#pragma optimization_level 3

static s32 func_01E03D30_b169(s32 ot, Trail_b039_01E03820 *o, Pt_b039_01E03820 *pts, Cam_b039_01E03820 *cam __attribute__((aligned(16)))) {
    extern void b169_01E00080(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern f32 func_001018E0(f32, f32);
    Xyz_b039_01E03820 s[2];
    Vec4f w;
    Pkt_b039_01E03820 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    s32 j;
    s32 cnt;
    s32 nq;
    f32 w0;
    f32 w1;

    if (func_00104520(o->flags, 0x1F) != 0) {
        cnt = o->n1;
    } else {
        cnt = o->n2;
    }
    nq = func_00104520(o->flags, 0x1E) != 0 ? 2 : 1;
    ((Pkt_b039_01E03820 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b039_01E03820 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b039_01E03820 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b039_01E03820 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    b169_01E00080(&pkt, o->color);
    ((Pkt_b039_01E03820 *)(s32)&pkt)->count |= 0x800;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[0].uv)->u = o->rect.u << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[0].uv)->v = o->rect.v << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[1].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[1].uv)->v = o->rect.v << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[2].uv)->u = o->rect.u << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[2].uv)->v = (o->rect.v + o->rect.h) << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[3].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b039_01E03820 *)(s32)&pkt.v[3].uv)->v = (o->rect.v + o->rect.h) << 4;
    func_00208CB0(&pkt, (u64)0xA | ((u64)o->rect.u << 4) | ((u64)(o->rect.u + o->rect.w - 1) << 14) |
                            ((u64)o->rect.v << 24) | ((u64)(o->rect.v + o->rect.h - 1) << 34));
    func_00208700(&pkt, o->texture, 1);
    for (i = 1; i < cnt; i++) {
        w.x = pts[i - 1].x;
        w.y = pts[i - 1].y;
        w.z = pts[i - 1].z;
        if (func_00205440(&w, cam->view, &s[0], &depth[0]) != 0) {
            o->flags |= 0x100000;
        }
        w.x = pts[i].x;
        w.y = pts[i].y;
        w.z = pts[i].z;
        if (func_00205440(&w, cam->view, &s[1], &depth[1]) != 0) {
            o->flags |= 0x200000;
        }
        if (func_00104520(o->flags, 0x14) != 0 && func_00104520(o->flags, 0x15) != 0) {
            w0 = func_001018E0(o->base + o->grow * pts[i - 1].age, depth[0]);
            w1 = func_001018E0(o->base + o->grow * pts[i].age, depth[1]);
            if (o->a >= pts[i - 1].a) {
                pkt.v[0].a = pkt.v[2].a = pts[i - 1].a;
            } else {
                pkt.v[0].a = pkt.v[2].a = o->a;
            }
            if (o->a >= pts[i].a) {
                pkt.v[1].a = pkt.v[3].a = pts[i].a;
            } else {
                pkt.v[1].a = pkt.v[3].a = o->a;
            }
            if (i == 1) {
                pkt.v[0].a = pkt.v[2].a = 0;
            }
            for (j = 0; j < nq; j++) {
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                if (func_00104520(o->flags, 0x1E) != 0) {
                    if (j == 0) {
                        pkt.v[0].xyz.y = s[0].y - w0;
                        pkt.v[1].xyz.y = s[1].y - w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                    if (j == 1) {
                        pkt.v[0].xyz.y = s[0].y + w0;
                        pkt.v[1].xyz.y = s[1].y + w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                } else {
                    pkt.v[0].xyz.y = s[0].y - w0;
                    pkt.v[1].xyz.y = s[1].y - w1;
                    pkt.v[2].xyz.y = s[0].y + w0;
                    pkt.v[3].xyz.y = s[1].y + w1;
                }
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[0].z;
                    pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[1].z;
                    func_002075F0(&pkt, ot, (u32)((depth[0] + depth[1]) / 2.0f));
                }
            }
        }
        o->flags &= 0xFFCFFFFF;
    }
    for (i = 0; i < cnt + 1; i++) {
        pts->age++;
        pts++;
    }
    o->tick++;
    return 0;
}
#pragma optimization_level reset

/* shape b169:01E04710 (b169), 862 insns, 1 copy: b169 scene manager (b591:01E03B80's form): code >= 0 clears the
   scene (0x2E10), resets seven coords, joints 24/26/4, a 396-tick timer, a model-shot wave, a 16-point trail emitter,
   a 64-drop ring, 64 rising sparks and two 256-point ribbon trails; otherwise follows the joints, draws the trail
   emitter in 21..49, the ribbons from 52, runs b169_01E05490, the sparks, the wave from 127; returns 2 at 380, 1 at
   117, 6 in 127..379, 8 when the timer ends */

typedef struct {
    Vec4f scale;
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b169_01E04710;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} TPt_b169_01E04710;

typedef struct {
    void *tex;
    u8 b, g, r, a;
    s32 flags;
    f32 base;
    s16 u, v, w, h;
    s16 u1, v1, w1, h1;
    Vec4f pos;
    f32 sx;
    f32 grow;
    u8 pad38[2];
    s16 kind;
    s16 tick;
    s16 limit;
    s16 count;
    s16 idx;
    s16 h44;
    u8 pad46[0xA];
} Trail_b169_01E04710;

typedef struct {
    f32 x, y, z;
    s16 pad;
    s16 life;
} Pt1_b169_01E04710;

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    f32 x, y, z;
    s32 w1C;
    s16 h20, h22;
    s16 w, h;
    s16 tu, tv, tw, th;
    Pt1_b169_01E04710 pts[16];
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
} Em1_b169_01E04710;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt2_b169_01E04710;

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 u, v, w, h, u0, v0, tw, th;
    Pt2_b169_01E04710 *pts;
    void *rots;
    s32 w48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Em2_b169_01E04710;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    s16 h8;
    s16 model;
    s32 step;
    s32 phase;
    f32 amp;
} Wave_b169_01E04710;

typedef struct {
    Crd_b169_01E04710 crd0;
    Trail_b169_01E04710 ta;
    TPt_b169_01E04710 ptsA[0x100];
    Trail_b169_01E04710 tb;
    TPt_b169_01E04710 ptsB[0x100];
    Crd_b169_01E04710 crd1;
    Crd_b169_01E04710 crd2;
    Crd_b169_01E04710 crd3;
    Em2_b169_01E04710 em2;
    Pt2_b169_01E04710 pts2[0x40];
    Crd_b169_01E04710 crd4;
    Em2_b169_01E04710 em3;
    Pt2_b169_01E04710 pts3[0x40];
    Crd_b169_01E04710 crd5;
    Em1_b169_01E04710 em1;
    Crd_b169_01E04710 crd6;
    Wave_b169_01E04710 wave;
    u8 c[4];
    s32 count;
    s32 step;
    s32 id;
    s32 w64;
    s32 jA;
    s32 jB;
    s32 jC;
    s32 a74;
    s32 a78;
    f32 f7C;
    u8 fade;
    u8 pad2E05[0xB];
} Scene_b169_01E04710;

static s32 func_01E04710_b169(s32 arg0, s32 code) {
    Scene_b169_01E04710 *g = (Scene_b169_01E04710 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern f32 func_001F5850(void);
    extern void func_001F6580(s32, void *);
    extern void func_001F63E0(s32, void *);
    extern void func_001F6D00(s32);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_00103660(void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern void b169_01E05490();
    s32 ot;
    Vec4f t[2];
    Vec4f v;
    s32 tex[4];
    s32 i;
    s32 r;
    f32 f;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x2E10);
        func_00103890(&g->crd0);
        func_00103890(&g->crd1);
        func_00103890(&g->crd2);
        func_00103890(&g->crd3);
        func_00103890(&g->crd4);
        func_00103890(&g->crd5);
        func_00103890(&g->crd6);
        g->jA = func_001F5560(func_001F53A0(), 0x18, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x1A, 0);
        g->jC = func_001F5560(func_001F53A0(), 4, 0);
        g->count = 0x18C;
        g->step = 1;
        g->id = code;
        g->f7C = func_001F5850();
        g->fade = 0x80;
        g->w64 = 0;
        g->a74 = 0;
        g->a74 = 0x4000;
        g->wave.flags = 0x1000;
        g->wave.r = 0x80;
        g->wave.g = 0x80;
        g->wave.b = 0x40;
        g->wave.a = 0x80;
        g->wave.phase = 0;
        g->wave.step = 0x1000;
        g->wave.h8 = 0;
        g->wave.amp = 20.0f;
        g->wave.model = func_001F5380();
        g->c[2] = 0x80;
        g->c[1] = 0x80;
        g->c[0] = 0x80;
        g->c[3] = 0x80;
        func_00103260(tex, 0xF);
        g->em1.tex = (void *)tex[0];
        g->em1.flags = 0x80083;
        g->em1.x = 0.0f;
        g->em1.y = 0.0f;
        g->em1.z = 0.0f;
        g->em1.w1C = 0;
        g->em1.tu = 0x80;
        g->em1.tv = 0xC0;
        g->em1.w = 0x20;
        g->em1.h = 0x20;
        g->em1.tw = 0x80;
        g->em1.th = 0x40;
        g->em1.size = 5.0f;
        g->em1.count = 0x10;
        g->em1.step = 2;
        g->em1.h13C = 1;
        g->em1.h140 = 8;
        g->em1.h136 = 0;
        g->em1.h138 = 0;
        g->em1.r = 0x70;
        g->em1.g = 0xA0;
        g->em1.b = 0xA0;
        g->em1.a = 0x20;
        for (i = 0; i < 16; i++) {
            g->em1.pts[i].x = g->em1.x + (func_0019A5C8() % 6 - 3);
            g->em1.pts[i].y = g->em1.y + (func_0019A5C8() % 6 - 3);
            g->em1.pts[i].z = g->em1.z;
            g->em1.pts[i].life = -g->em1.step * i;
            g->em1.pts[i].pad = 0;
            g->em1.h13E = g->em1.h140 - 1;
        }
        func_00103290(tex, 0);
        g->em2.tex = (void *)tex[0];
        g->em2.flags = 0x58000003;
        g->em2.r = 0x80;
        g->em2.g = 0x80;
        g->em2.b = 0x80;
        g->em2.a = 0x80;
        g->em2.size = 1.5f;
        g->em2.rot[0] = 0;
        g->em2.rot[1] = 0;
        g->em2.rot[2] = 0;
        g->em2.u = 0;
        g->em2.v = 0x30;
        g->em2.w = 0x20;
        g->em2.h = 0x20;
        g->em2.u0 = 0;
        g->em2.v0 = 0x30;
        g->em2.tw = 0x100;
        g->em2.th = 0x80;
        g->em2.pts = g->pts2;
        g->em2.rots = 0;
        g->em2.w48 = 0;
        g->em2.radius = 2.0f;
        g->em2.grow = 5.0f;
        g->em2.amp = 50.0f;
        g->em2.freq = 0x400;
        g->em2.count = 0x40;
        g->em2.nframes = 0xE;
        g->em2.rate = 0x64;
        for (i = 0; i < g->em2.count; i++) {
            r = func_0019A5C8() % 0x10000;
            g->pts2[i].y = 0.0f;
            g->pts2[i].z = g->em2.radius * func_0020B480(r);
            g->pts2[i].x = g->em2.radius * func_0020B550(r);
            g->pts2[i].t = -i;
            g->pts2[i].a = 0;
            g->pts2[i].frame = func_0019A5C8() % 14;
        }
        g->em3.tex = (void *)tex[0];
        g->em3.flags = 0x70000003;
        g->em3.r = 0x80;
        g->em3.g = 0x80;
        g->em3.b = 0x80;
        g->em3.a = 0x80;
        g->em3.size = 2.0f;
        g->em3.rot[0] = 0;
        g->em3.rot[1] = 0x400;
        g->em3.rot[2] = 0;
        g->em3.u = 0;
        g->em3.v = 0x30;
        g->em3.w = 0x20;
        g->em3.h = 0x20;
        g->em3.u0 = 0;
        g->em3.v0 = 0x30;
        g->em3.tw = 0x100;
        g->em3.th = 0x80;
        g->em3.pts = g->pts3;
        g->em3.rots = 0;
        g->em3.w48 = 0;
        g->em3.radius = 2.0f;
        g->em3.count = 0x40;
        g->em3.nframes = 8;
        g->em3.rate = 0x64;
        for (i = 0; i < g->em3.count; i++) {
            g->pts3[i].t = 1;
            g->pts3[i].a = 0;
            g->pts3[i].frame = func_0019A5C8() % 8;
            r = func_0019A5C8() % 0x10000;
            f = 0.1f * (func_0019A5C8() % 60 - 30);
            g->pts3[i].z = f * func_0020B480(r);
            g->pts3[i].x = f * func_0020B550(r);
            g->pts3[i].y = 0.1f * (func_0019A5C8() % 200);
        }
        g->ta.tex = (void *)tex[0];
        g->ta.flags = 0x8003;
        g->ta.r = 0x80;
        g->ta.g = 0x80;
        g->ta.b = 0x80;
        g->ta.a = 0;
        g->ta.u = 0x10;
        g->ta.v = 0;
        g->ta.w = 0x20;
        g->ta.h = 0x30;
        g->ta.u1 = 0x10;
        g->ta.v1 = 0;
        g->ta.w1 = 0x20;
        g->ta.h1 = 0x30;
        g->ta.base = 150.0f;
        g->ta.grow = 10.0f;
        g->ta.sx = 1.03f;
        g->ta.kind = 8;
        g->ta.tick = 0;
        g->ta.limit = 0x40;
        g->ta.count = 0x100;
        g->ta.idx = 0;
        g->ta.h44 = 1;
        g->tb.tex = (void *)tex[0];
        g->tb.flags = 0x8003;
        g->tb.r = 0x80;
        g->tb.g = 0x80;
        g->tb.b = 0x80;
        g->tb.a = 0;
        g->tb.u = 0x10;
        g->tb.v = 0;
        g->tb.w = 0x20;
        g->tb.h = 0x30;
        g->tb.u1 = 0x10;
        g->tb.v1 = 0;
        g->tb.w1 = 0x20;
        g->tb.h1 = 0x30;
        g->tb.base = 150.0f;
        g->tb.grow = 10.0f;
        g->tb.sx = 1.03f;
        g->tb.kind = 8;
        g->tb.tick = 0;
        g->tb.limit = 0x40;
        g->tb.count = 0x100;
        g->tb.idx = 0;
        g->tb.h44 = 1;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->jA, &g->crd5.pos);
    func_001F5620(func_001F53A0(), g->jA, &g->crd3.pos);
    func_001F5F90(func_001F5380(), &t[0]);
    func_001F5620(func_001F53A0(), g->jA, &t[1]);
    func_00103DB0(&t[1], &t[0], &g->crd3.rot);
    func_001F5620(func_001F53A0(), g->jA, &g->crd4.pos);
    func_001F53C0(1, func_001F5380(), &g->ta.pos);
    g->ta.pos.y -= 20.0f;
    func_00103660(&g->ta.pos, &t[1]);
    g->ta.pos.x /= 80.0f;
    g->ta.pos.y /= 80.0f;
    g->ta.pos.z /= 80.0f;
    func_001F5620(func_001F53A0(), g->jC, &g->crd1.pos);
    g->crd1.pos.x = 3.0f * func_0020B550(g->a74);
    func_01E03BC0_b169((Obj_b039_01E036B0 *)&g->ta, (Pt_b039_01E036B0 *)g->ptsA, &g->crd1.pos.x);
    g->a74 += 0x800;
    func_001F53C0(1, func_001F5380(), &g->tb.pos);
    g->tb.pos.y += 20.0f;
    func_00103660(&g->tb.pos, &t[1]);
    g->tb.pos.x /= 80.0f;
    g->tb.pos.y /= 80.0f;
    g->tb.pos.z /= 80.0f;
    func_001F5620(func_001F53A0(), g->jC, &g->crd2.pos);
    g->crd2.pos.x = 3.0f * func_0020B550(g->a78);
    func_01E03BC0_b169((Obj_b039_01E036B0 *)&g->tb, (Pt_b039_01E036B0 *)g->ptsB, &g->crd2.pos.x);
    g->a78 += 0x800;
    func_001F53C0(1, func_001F5380(), &g->crd6.pos);
    func_001038D0(&g->crd0);
    func_001039A0(&g->crd1);
    func_001039A0(&g->crd2);
    func_001039A0(&g->crd5);
    func_001038D0(&g->crd3);
    func_001038D0(&g->crd4);
    func_001038D0(&g->crd6);
    if (g->step >= 0x17C) {
        func_001032C0(&g->fade, 0x80, 4);
    } else {
        func_00103470(&g->fade, 0x20, 4);
    }
    func_001F6D00(g->fade);
    g->ta.r = g->tb.r = g->em2.r = func_0019A5C8() % 0x80 + 0x7F;
    g->ta.g = g->tb.g = g->em2.g = func_0019A5C8() % 0x80 + 0x7F;
    g->ta.b = g->tb.b = g->em2.b = func_0019A5C8() % 0x80 + 0x7F;
    if (g->step >= 0x15 && g->step < 0x32) {
        v.x = v.y = v.z = 1.01f;
        func_01E03030_b169(ot, (Cam_b001_01E00A30 *)&g->crd5, (Emit_b001_01E00A30 *)&g->em1, (Vec_b001_01E00A30 *)&v);
        if (g->step >= 0x22) {
            func_00103470(&g->em1.a, 0, 2);
        }
    }
    if (g->step >= 0x34) {
        func_01E03D30_b169(ot, (Trail_b039_01E03820 *)&g->ta, (Pt_b039_01E03820 *)g->ptsA, (Cam_b039_01E03820 *)g);
        if (g->step >= 0x17C) {
            func_00103470(&g->ta.a, 0, 6);
        } else {
            func_001032C0(&g->ta.a, 0x60, 6);
        }
        func_01E03D30_b169(ot, (Trail_b039_01E03820 *)&g->tb, (Pt_b039_01E03820 *)g->ptsB, (Cam_b039_01E03820 *)g);
        if (g->step >= 0x17C) {
            func_00103470(&g->tb.a, 0, 6);
        } else {
            func_001032C0(&g->tb.a, 0x60, 6);
        }
    }
    b169_01E05490(g, ot);
    func_01E00790_b169(ot, (Emit_b000_01E01140 *)&g->em3, (Cam_b000_01E01140 *)&g->crd4);
    if (g->step >= 0x17C) {
        func_00103470(&g->em3.a, 0, 8);
    }
    for (i = 0; i < g->em3.count; i++) {
        if (g->pts3[i].t >= 0) {
            g->pts3[i].y += 1.0f;
            if (g->pts3[i].a != 0) {
                if (g->pts3[i].y > 10.0f) {
                    func_00103470(&g->pts3[i].a, 0, 8);
                } else {
                    func_001032C0(&g->pts3[i].a, 0x80, 8);
                }
            }
            if (g->pts3[i].y < 20.0f) {
                g->pts3[i].z *= 1.05f;
                g->pts3[i].x *= 1.05f;
            }
            if (g->pts3[i].y >= 20.0f) {
                r = func_0019A5C8() % 0x10000;
                f = 0.1f * (func_0019A5C8() % 60 - 30);
                g->pts3[i].z = f * func_0020B480(r);
                g->pts3[i].x = f * func_0020B550(r);
                g->pts3[i].y = 0.1f * (func_0019A5C8() % 60 - 30);
                g->pts3[i].a = 1;
                g->pts3[i].frame = func_0019A5C8() % 8;
            }
        }
    }
    if (g->step >= 0x7F) {
        g->c[3] = 0x80 - g->wave.a;
        func_01E00120_b169((Wave_b015_01E00280 *)&g->wave, (Vec_b015_01E00280 *)&g->crd6.pos);
        func_001F63E0(g->wave.model, g->c);
        if (g->step > 0x17C) {
            func_00103470(&g->wave.a, 0, 8);
        }
    }
    g->step++;
    g->count--;
    if (g->step == 0x17C) {
        func_001F6580(func_001F5380(), 0);
        return 2;
    }
    if (g->step == 0x75) {
        return 1;
    }
    if (g->step >= 0x7F && g->step <= 0x17B) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b169:01E05490, 137 insns: the scene's falling-ash ring: while flag 0x1F is set it moves the camera block at
   g+0x22B4 towards -30 (else +30), the scene's top flag bit follows whether it is done; the module's emitter runs on
   g+0x2260/0x21F0; each live particle falls by 3 and spreads (x0.8 above the ground, x1.05 below), and once below -200 it
   is reborn at a random angle on the scene radius (g+0x22AC), alpha 0x40 from scene step 43; past step 380 the scene's
   0x226B block is cleared */

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 a;
    u8 pad;
    s16 d;
} Part_b169_01E05490;

typedef struct {
    u8 pad0[0x21F0];
    u8 v21F0[0x70];
    u8 v2260[0xB];
    u8 b226B[0x41];
    f32 radius;
    u8 pad22B0[4];
    u8 cam[6];
    s16 n;
    u8 pad22BC[4];
    Part_b169_01E05490 part[137];
    u8 pad2B50[0x290];
    s32 step;
    u8 pad2DE4[4];
    u32 flags;
} Scene_b169_01E05490;

static void func_01E05490_b169(Scene_b169_01E05490 *g, s32 arg) {
    extern void b169_01E02080(s32, void *, void *);
    f32 s;
    extern s32 func_00104520(s32, s32);
    extern s32 func_00103540(void *, f32, f32);
    extern s32 func_00103390(void *, f32, f32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern void func_00103470(void *, s32, s32);
    s32 i;
    s32 r;

    if (func_00104520(g->flags, 0x1F)) {
        if (func_00103540(g->cam, -30.0f, s = 1.5f) == 0) {
            g->flags &= 0x7FFFFFFF;
        }
    } else if (func_00103390(g->cam, 30.0f, 1.5f) == 0) {
        g->flags |= 0x80000000;
    }
    b169_01E02080(arg, g->v2260, g->v21F0);
    for (i = 0; i < g->n; i++) {
        if (g->part[i].d < 0) {
            continue;
        }
        g->part[i].y -= 3.0f;
        if (g->part[i].y > 0.0f) {
            g->part[i].z *= 0.8f;
            g->part[i].x *= 0.8f;
        } else {
            g->part[i].z *= 1.05f;
            g->part[i].x *= 1.05f;
        }
        if (g->part[i].y < -200.0f) {
            r = func_0019A5C8() % 0x10000;
            g->part[i].d = -i;
            g->part[i].z = g->radius * func_0020B480(r);
            g->part[i].x = g->radius * func_0020B550(r);
            g->part[i].y = 0.0f;
            if (g->step >= 43) {
                g->part[i].a = 0x40;
            } else {
                g->part[i].a = 0;
            }
        }
    }
    if (g->step > 380) {
        func_00103470(g->b226B, 0, 0x10);
    }
}
