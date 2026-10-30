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

static void func_01E00080_b135(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b135(u8 *c) {
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

static s32 func_01E00380_b135(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b135((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

static s32 func_01E01C70_b135(Obj_b039_01E036B0 *obj, Pt_b039_01E036B0 *pts, f32 *pos) {
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

extern void b135_01E00080(void *, void *);

#pragma optimization_level 3

static s32 func_01E01DE0_b135(s32 ot, Trail_b039_01E03820 *o, Pt_b039_01E03820 *pts, Cam_b039_01E03820 *cam __attribute__((aligned(16)))) {
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
    b135_01E00080(&pkt, o->color);
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

/* shape b135:01E027C0 (b135), 401 insns, 1 copy: b135 scene manager: setup (three joints, a 256-point belt, a
   32-point sparkle emitter), then the belt grown behind a joint from frame 12 and drawn in flickering colours, the
   negative-screen fade, and from frame 0x6F the sparkles drawn, grown and respawned */

typedef struct {
    void *tex;
    u8 b, g, r, a;
    s32 flags;
    f32 base;
    s16 rect[8];
    Vec4f vel;
    f32 sx;
    f32 grow;
    u8 padA8[2];
    s16 kind;
    s16 limit;
    s16 max;
    s16 n1;
    s16 n2;
    s16 hB4;
    u8 padB6[0xA];
} Belt_b135_01E027C0;

typedef struct {
    u8 crd[0x70];
    Belt_b135_01E027C0 belt;
    Pt_b039_01E036B0 bpts[0x100];
    Vec4f scale;
    u8 pad10D0[0x10];
    Vec4f pos;
    u8 pad10F0[0x40];
    Vec4f cam;
    u8 pad1140[0x10];
    Vec4f joint;
    u8 pad1160[0x40];
    Emit_b000_01E01140 emit;
    Pt_b000_01E01140 pts[32];
    u8 pad1400[0x10];
    s32 count;
    s32 frame;
    s32 id;
    s32 w141C;
    u8 neg[4];
    s32 jA;
    s32 jB;
    s32 jC;
} Scene_b135_01E027C0;

static s32 func_01E027C0_b135(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103290(void *, s32);
    extern void func_00103260(void *, s32);
    extern void func_00103660(void *, void *);
    extern s32 func_001043F0(void *, f32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_0019A5C8();
    Scene_b135_01E027C0 *g = (Scene_b135_01E027C0 *)arg0;
    s32 ot;
    Vec4f v;
    Vec4f t[2];
    s32 tex[4];
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1430);
        func_00103890(g);
        func_00103890(&g->scale);
        func_00103890(&g->cam);
        g->jA = func_001F5560(func_001F53A0(), 0x12, 1);
        g->jB = func_001F5560(func_001F53A0(), 1, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x42, 0);
        g->count = 0xE6;
        g->frame = 1;
        g->id = code;
        g->w141C = 0x10;
        g->neg[2] = 0x60;
        g->neg[1] = 0x10;
        g->neg[0] = 0x80;
        g->neg[3] = 0;
        func_00103290(tex, 2);
        g->belt.tex = (void *)tex[0];
        g->belt.flags = 0x8003;
        g->belt.r = 0x80;
        g->belt.g = 0x80;
        g->belt.b = 0x80;
        g->belt.a = 0;
        g->belt.rect[0] = 0;
        g->belt.rect[1] = 0;
        g->belt.rect[2] = 0x20;
        g->belt.rect[3] = 0x40;
        g->belt.rect[4] = 0;
        g->belt.rect[5] = 0;
        g->belt.rect[6] = 0x20;
        g->belt.rect[7] = 0x40;
        g->belt.base = 150.0f;
        g->belt.grow = 10.0f;
        g->belt.sx = 1.03f;
        g->belt.kind = 8;
        g->belt.limit = 0;
        g->belt.max = 0x40;
        g->belt.n1 = 0x100;
        g->belt.n2 = 0;
        g->belt.hB4 = 1;
        func_00103260(tex, 1);
        g->emit.texture = (void *)tex[0];
        g->emit.flags = 0x48000003;
        g->emit.color.r = 0x60;
        g->emit.color.g = 0x10;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x40;
        g->emit.size = 20.0f;
        g->emit.rot.x = 0.0f;
        g->emit.rot.y = 0.0f;
        g->emit.rot.z = 0.0f;
        g->emit.r.i.u = 0;
        g->emit.r.i.v = 0;
        g->emit.r.i.w = 0x18;
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
            func_001043F0(&v, 14.0f);
            g->pts[i].x = v.x;
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x40;
            g->pts[i].frame = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_001F53C0(1, func_001F53A0(), &t[0]);
    func_001F53C0(1, func_001F5380(), &t[1]);
    func_001F53C0(1, func_001F5380(), &g->joint);
    func_001F53C0(1, func_001F5380(), &g->belt.vel);
    func_00103660(&g->belt.vel, &t[0]);
    g->belt.vel.x /= 80.0f;
    g->belt.vel.y /= 80.0f;
    g->belt.vel.z /= 80.0f;
    if (g->frame >= 12) {
        func_001F5620(func_001F53A0(), g->jC, &g->pos);
        func_01E01C70_b135((void *)&g->belt, (void *)g->bpts, &g->pos.x);
    }
    func_001038D0(g);
    func_001039A0(&g->scale);
    func_001038D0(&g->cam);
    if (g->frame >= 0xBE) {
        func_00103470(&g->neg[3], 0, 8);
    } else {
        func_001032C0(&g->neg[3], 0x80, 8);
    }
    func_01E00120_b135(g->neg);
    if (g->frame > 12) {
        g->belt.r = func_0019A5C8() % 64 + 64;
        g->belt.g = func_0019A5C8() % 64 + 64;
        g->belt.b = func_0019A5C8() % 64 + 64;
        func_01E01DE0_b135(ot, (Trail_b039_01E03820 *)&g->belt, (Pt_b039_01E03820 *)g->bpts,
                           (Cam_b039_01E03820 *)g);
        if (g->frame >= 0xAF) {
            func_00103470(&g->belt.a, 0, 8);
        } else {
            func_001032C0(&g->belt.a, 0x80, 8);
        }
    }
    if (g->frame >= 0x6F) {
        func_01E00380_b135(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->cam);
        if (g->frame >= 0xBE) {
            func_00103470(&g->emit.color.a, 0, 2);
        } else {
            func_001032C0(&g->emit.color.a, 0x40, 1);
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts[i].t >= 0) {
                g->pts[i].x *= 1.03f;
                g->pts[i].y *= 1.03f;
                g->pts[i].z *= 1.03f;
                func_00103470(&g->pts[i].a, 0, 4);
            }
            if (g->pts[i].t >= 0x10) {
                func_001043F0(&v, 14.0f);
                g->pts[i].x = v.x;
                g->pts[i].y = v.y;
                g->pts[i].z = v.z;
                g->pts[i].t = 0;
                g->pts[i].a = 0x40;
            }
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 0xBE) {
        return 2;
    }
    if (g->frame == 0x65) {
        return 1;
    }
    if (g->frame >= 0x6F && g->frame <= 0xBD) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
