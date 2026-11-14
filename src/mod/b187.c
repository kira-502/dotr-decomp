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

static void func_01E00080_b187(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b187(void) {
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
    f32 x, y, z, w;
} Vec_b001_01E01B20;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[4];
    f32 half;
    u8 pad10[0x30];
    Vec_b001_01E01B20 *pts;
    u8 pad44[8];
    f32 radius;
    u8 pad50[0xA];
    s16 count;
} Ring_b001_01E01B20;

static s32 func_01E00250_b187(Ring_b001_01E01B20 *o, f32 size) {
    s32 i;
    s32 ang;

    o->half = size / 2.0f;
    for (i = 0; i < o->count; i++) {
        if (func_00104520(o->flags, 0x1D) != 0) {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = o->radius * func_0020B550(ang);
            o->pts[i].z = func_0019A5C8() % 20;
            o->pts[i].x = o->radius * func_0020B480(ang);
        } else {
            ang = func_0019A5C8() % 0x10000;
            o->pts[i].y = func_0019A5C8() % 20;
            o->pts[i].z = o->radius * func_0020B480(ang);
            o->pts[i].x = o->radius * func_0020B550(ang);
        }
    }
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

static s32 func_01E003E0_b187(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b187((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

static s32 func_01E01CD0_b187(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

/* shape b015:01E008F0 (LkPrim_ModelShot2), 422 insns, 7 copies (-O3,p): a 2x2 sprite light shot around the
   model's screen point, its texture window stretched over count steps by the point's offset over 640/448;
   q.y read through the u16 local py first (puts q.x/q.y in the original's temp registers) */

typedef struct {
    f32 x, y, z, w;
} Vec_b015_01E008F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b015_01E008F0;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b015_01E008F0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Uv_b015_01E008F0 st0;
    Xyz_b015_01E008F0 p0;
    Uv_b015_01E008F0 st1;
    Xyz_b015_01E008F0 p1;
    u8 pad50[8];
    u64 t58;
    u64 t60;
    u8 pad68[8];
} Pkt_b015_01E008F0;

typedef struct {
    u8 pad00[0x30];
    f32 m[16];
} Cam_b015_01E008F0;

typedef struct {
    s32 flags;
    u8 b, g, r, a;
    f32 scale;
    s16 count;
    s16 model;
} Shot_b015_01E008F0;

#pragma optimization_level 3
static inline void b015_01E008F0_tag(Pkt_b015_01E008F0 *p, s32 tag, s32 count, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E02230_b187(Shot_b015_01E008F0 *o, Vec_b015_01E008F0 *pos) {
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
    s32 h;
    s32 j;
    s32 i;
    u16 py;
    u16 y;
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    u16 x;
    s32 k;
    s16 x0;
    s16 y0;
    f32 ax;
    f32 bx;
    f32 ay;
    f32 by;
    Cam_b015_01E008F0 cam;
    Pkt_b015_01E008F0 pkt __attribute__((aligned(8)));
    Xyz_b015_01E008F0 q;
    f32 dep;

    h = func_00207F60();
    func_00103890(&cam);
    func_001038D0(&cam);
    if (func_00205440(pos, cam.m, &q, &dep) == 0) {
        return -1;
    }
    py = q.y;
    x0 = (q.x >> 4) - 0x6C0;
    y0 = (py >> 4) - 0x720;
    ax = x0 / 640.0f;
    bx = 1.0f - ax;
    ay = y0 / 448.0f;
    by = 1.0f - ay;
    ax *= o->scale;
    bx *= o->scale;
    ay *= 0.7f * o->scale;
    by *= 0.7f * o->scale;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->count = 0x26;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->tag = 5;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->regs = 0x42421;
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = o->r;
    pkt.g = o->g;
    pkt.b = o->b;
    pkt.a = o->a;
    pkt.q = 1.0f;
    func_00208460();
    func_001F7060(o->model, 0, &pkt.t58, &pkt.t60);
    func_00208460();
    ((Pkt_b015_01E008F0 *)(s32)&pkt)->count |= 0x800;
    for (i = 0; i < o->count; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                x = k * 640 + 0x6C0;
                y = j * 448 + 0x720;
                u0 = ((s32)ax * i) << 4;
                v0 = ((s32)ay * i) << 4;
                u1 = (640 - (s32)bx * i) << 4;
                v1 = (448 - (s32)by * i) << 4;
                py = (y << 4) - 8;
                pkt.p0.x = q.x;
                pkt.p0.y = q.y;
                pkt.p0.f = 0;
                pkt.p1.x = (x << 4) - 8;
                pkt.p1.y = py;
                pkt.p1.f = 0;
                ((Uv_b015_01E008F0 *)(s32)&pkt.st0)->s = x0 << 4;
                ((Uv_b015_01E008F0 *)(s32)&pkt.st0)->t = y0 << 4;
                if (j == 0) {
                    if (k == 0) {
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u0;
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v0;
                    } else {
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u1;
                        ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v0;
                    }
                } else if (k == 0) {
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u0;
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v1;
                } else {
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->s = u1;
                    ((Uv_b015_01E008F0 *)(s32)&pkt.st1)->t = v1;
                }
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.p0.z = pkt.p1.z = 0xFFFFFF;
                    func_002075F0(&pkt, 0, 0);
                } else {
                    pkt.p0.z = pkt.p1.z = func_00205D10(pos, -func_001F5860(o->model));
                    func_002075F0(&pkt, 0, (u32)func_00205DF0(pos, -func_001F5860(o->model)));
                }
            }
        }
    }
    func_00207FD0(h, func_00207500(), 0);
    return 0;
}
#pragma optimization_level reset

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

static s32 func_01E028D0_b187(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E04D00_b187;
    Tbl_b000_01E032C0 tbl = D_01E04D00_b187;
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

static s32 func_01E02A30_b187(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_b187((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* shape b000:01E03A30, 81 insns, 30 copies: finds the last free slot of a point trail, then pushes a new
   point at the front (every older point moves one slot back). */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 e;
} Pt_b000_01E03A30;

typedef struct {
    u8 pad0[7];
    u8 c;
    u8 pad8[0x1A];
    u8 kind;
    u8 pad23[3];
    s16 limit;
    s16 count;
    s16 idx;
} Obj_b000_01E03A30;

static s32 func_01E03040_b187(Obj_b000_01E03A30 *obj, Pt_b000_01E03A30 *pts, f32 *pos) {
    s32 i;
    Pt_b000_01E03A30 *p;
    Pt_b000_01E03A30 *q;
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
                q->x = q[-1].x;
                q->y = q[-1].y;
                q->z = q[-1].z;
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

/* shape b117:01E00270, 624 insns, 28 copies (-O3,p): LkEFF_SortLaser: draws a laser trail through cnt points (0x10
   bytes each), every point aged first: each piece between two projected points is four textured quads (above, below,
   right, left of the line) as wide as func_001018E0(base, depth), skipped unless both corners are on screen; alpha =
   min(object alpha, point alpha), first piece fades in from 0. Colour from the module helper b117:01E00080. Both
   spilled parameters are aligned(8) to put their homes at 0xE8/0xE0. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b117_01E00270;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b117_01E00270;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b117_01E00270 uv;
    Xyz_b117_01E00270 xyz;
} Vtx_b117_01E00270;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b117_01E00270 v[4];
    u8 tail[0x20];
} Pkt_b117_01E00270;

typedef struct {
    s16 u, v, w, h;
} Rect_b117_01E00270;

typedef struct {
    void *texture;
    u8 color[3];
    u8 a;
    s32 flags;
    f32 base;
    Rect_b117_01E00270 rect;
    u8 pad18[0xC];
    s16 tick;
    u8 pad26[2];
    s16 n1;
    s16 n2;
} Laser_b117_01E00270;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b117_01E00270;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b117_01E00270;

#pragma optimization_level 3

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E03190_b187(s32 ot __attribute__((aligned(8))), Laser_b117_01E00270 *o, Pt_b117_01E00270 *pts, Cam_b117_01E00270 *cam __attribute__((aligned(8)))) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b117_01E00270 s[2];
    Vec4f w;
    Pkt_b117_01E00270 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    s32 j;
    s32 cnt;
    f32 w0;
    f32 w1;

    if (func_00104520(o->flags, 0x1F) != 0) {
        cnt = o->n1;
    } else {
        cnt = o->n2;
    }
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b117_01E00270 *)(s32)&pkt)->pad = 0;
    if (func_00104520(o->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b187((void *)&pkt, (void *)o->color);
    ((Pkt_b117_01E00270 *)(s32)&pkt)->count |= 0x800;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[0].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[1].uv)->v = o->rect.v << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->u = o->rect.u << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[2].uv)->v = (o->rect.v + o->rect.h) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->u = (o->rect.u + o->rect.w) << 4;
    ((Uv_b117_01E00270 *)(s32)&pkt.v[3].uv)->v = (o->rect.v + o->rect.h) << 4;
    for (i = 0; i < cnt + 1; i++) {
        pts[i].age++;
    }
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
            w0 = func_001018E0(o->base, depth[0]);
            w1 = func_001018E0(o->base, depth[1]);
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
            for (j = 0; j < 4; j++) {
                if (j < 2) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                    if (j == 0) {
                        pkt.v[0].xyz.y = s[0].y + w0;
                        pkt.v[1].xyz.y = s[1].y + w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                    if (j == 1) {
                        pkt.v[0].xyz.y = s[0].y - w0;
                        pkt.v[1].xyz.y = s[1].y - w1;
                        pkt.v[2].xyz.y = s[0].y;
                        pkt.v[3].xyz.y = s[1].y;
                    }
                } else {
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
                    if (j == 2) {
                        pkt.v[0].xyz.x = s[0].x + w0;
                        pkt.v[1].xyz.x = s[1].x + w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                    if (j == 3) {
                        pkt.v[0].xyz.x = s[0].x - w0;
                        pkt.v[1].xyz.x = s[1].x - w1;
                        pkt.v[2].xyz.x = s[0].x;
                        pkt.v[3].xyz.x = s[1].x;
                    }
                }
                func_00208CB0(&pkt, (u64)0xA | ((u64)o->rect.u << 4) | ((u64)(o->rect.u + o->rect.w - 1) << 14) |
                                        ((u64)o->rect.v << 24) | ((u64)(o->rect.v + o->rect.h - 1) << 34));
                func_00208700(&pkt, o->texture, 1);
                if (func_00101600(&pkt.v[0].xyz) != 0 && func_00101600(&pkt.v[1].xyz) != 0) {
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
        }
        o->flags &= 0xFFCFFFFF;
    }
    o->tick++;
    return 0;
}
#pragma optimization_level reset

/* shape b087:01E03B30, 87 insns, 9 copies: set up a ribbon sprite object (scale, 4 corner offsets from a local
   table sized by the object's widths/heights, 16 or 64 evenly spread angles) */

typedef struct V4_b087_01E03B30 {
    f32 x, y, z, w;
} V4_b087_01E03B30;

typedef struct Rnd_b087_01E03B30 {
    s32 a, b, c, d;
} Rnd_b087_01E03B30;

typedef struct Obj_b087_01E03B30 {
    s32 kind;
    s32 model;
    s32 pad8;
    f32 scale;
    s32 pad10[4];
    f32 w0;
    f32 w1;
    f32 h0;
    f32 h1;
    V4_b087_01E03B30 v[4];
    Rnd_b087_01E03B30 r[64];
} Obj_b087_01E03B30;

typedef struct W_tbl_func_01E03B50_b187 {
    V4_b087_01E03B30 v[4];
} W_tbl_func_01E03B50_b187;

static s32 func_01E03B50_b187(Obj_b087_01E03B30 *obj, s32 kind, f32 scale) {
    extern W_tbl_func_01E03B50_b187 D_01E04D40_b187;
    W_tbl_func_01E03B50_b187 tbl_w = D_01E04D40_b187;
    s32 flag;
    s32 n;
    s32 i;

    tbl_w.v[0].x = -obj->w0;
    tbl_w.v[0].y = obj->h0 + obj->h1;
    tbl_w.v[1].y = obj->h0 + obj->h1;
    tbl_w.v[2].x = -obj->w1;
    tbl_w.v[2].y = obj->h1;
    tbl_w.v[3].y = obj->h1;
    flag = func_00104520(obj->model, 0x1F);
    obj->scale = scale;
    obj->kind = kind;
    n = flag ? 0x10 : 0x40;
    for (i = 0; i < 4; i++) {
        obj->v[i].x = obj->scale * tbl_w.v[i].x;
        obj->v[i].y = obj->scale * tbl_w.v[i].y;
        obj->v[i].z = obj->scale * tbl_w.v[i].z;
    }
    for (i = 0; i < n; i++) {
        obj->r[i].b = 0x10000 / n * i;
    }
    return 0;
}

/* shape b087:01E03C90, 387 insns, 9 copies (b000:01E03420 with the corner list 16 bytes later): draws a textured sprite quad: n rotations of its 4 corner points,
   UV (texel) or ST coordinates from the sprite rect, depth-sorted unless flag 0x13/0x12.
   Calls the module's colour helper (shape b000:01E00100), included above as a static function. */

typedef struct {
    u8 b, g, r, a;
} Src_b087_01E03C90;

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
} Vtx_b087_01E03C90;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b087_01E03C90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b087_01E03C90 v[4];
    u8 tail[0x20];
} Pkt_b087_01E03C90;

typedef struct {
    f32 x, y, z, w;
} Vec_b087_01E03C90;

typedef struct {
    void *texture;
    s32 flags;
    Src_b087_01E03C90 color;
    u8 pad0C[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 s, t, w, h;
        } f;
    } rect;
    u8 pad20[0x10];
    Vec_b087_01E03C90 p[4];
    Vec_b087_01E03C90 rot[1];
} Spr_b087_01E03C90;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b087_01E03C90;

static s32 func_01E03CB0_b187(s32 obj, Spr_b087_01E03C90 *spr, Cam_b087_01E03C90 *cam) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 n[1];
    Vec_b087_01E03C90 out;
    f32 m[16];
    f32 depth[4];
    Pkt_b087_01E03C90 pkt;
    s32 i;
    s32 t;

    t = func_00104520(spr->flags, 0x1F);
    n[0] = 0x10;
    n[0] = t ? n[0] : 0x40;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b087_01E03C90 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b187((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    if (func_00104520(spr->flags, 0) != 0) {
        ((Pkt_b087_01E03C90 *)(s32)&pkt)->count |= 0x800;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[0].tc)->u = spr->rect.i.u * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[0].tc)->v = spr->rect.i.v * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[1].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[1].tc)->v = spr->rect.i.v * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[2].tc)->u = spr->rect.i.u * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[2].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[3].tc)->u = (spr->rect.i.u + spr->rect.i.w - 1) * 16;
        ((UV_b087_01E03C90 *)(s32)&pkt.v[3].tc)->v = (spr->rect.i.v + spr->rect.i.h - 1) * 16;
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

/* shape b187:01E042C0 (b187), 651 insns, 1 copy: b187 scene manager: code >= 0 sets up two discs, the model shot, the
   laser trail, a 256-point falling spray, a sprite and a ribbon sprite; else follows joints, draws the shot from 30
   to 104, the big disc/sprite from 123, the small disc and laser from 105, the spray before 105; returns 2/1/6/8 by
   tick */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Cam_b187_01E042C0;

typedef struct {
    s32 tex;
    u8 c[3];
    u8 a;
    s32 flags;
    f32 base;
    s16 uv[8];
    u8 pad20[2];
    s16 h22;
    s16 tick;
    s16 h26;
    s16 n1;
    s16 n2;
    s16 h2C;
    u8 pad2E[2];
} Laser_b187_01E042C0;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b187_01E042C0;

typedef struct {
    s32 flags;
    u8 c[4];
    f32 radius;
    s16 count;
    s16 height;
} Disc_b187_01E042C0;

typedef struct {
    s32 f0;
    u8 b, g, r, a;
    f32 size;
    s16 n;
    s16 id;
} Shot_b187_01E042C0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 scale;
    s16 uv[4];
    u8 pad18[8];
    Vec4f v[4];
    s32 r[64][4];
} Spr_b187_01E042C0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 scale;
    s16 uv[4];
    u8 pad18[8];
    f32 w0;
    f32 w1;
    f32 h0;
    f32 h1;
    Vec4f v[4];
    s32 r[64][4];
} Rib_b187_01E042C0;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    f32 size;
    u8 pad10[0x10];
    s32 rot[4];
    s16 uv[8];
    Pt_b187_01E042C0 *pts;
    s32 rots;
    s32 x48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b187_01E042C0;

typedef struct {
    Cam_b187_01E042C0 c0;
    Laser_b187_01E042C0 laser;
    Pt_b187_01E042C0 lpts[32];
    Cam_b187_01E042C0 c1;
    Cam_b187_01E042C0 c6;
    Shot_b187_01E042C0 shot;
    Cam_b187_01E042C0 c2;
    Disc_b187_01E042C0 disc1;
    Cam_b187_01E042C0 c3;
    Spr_b187_01E042C0 spr1;
    Disc_b187_01E042C0 disc2;
    Cam_b187_01E042C0 c4;
    Emit_b187_01E042C0 emit;
    Pt_b187_01E042C0 pts[0x100];
    Cam_b187_01E042C0 c5;
    Rib_b187_01E042C0 spr2;
    s32 timer;
    s32 t;
    s32 code;
    s32 fade;
    s32 cnt;
    u8 col[4];
    Vec4f tgt;
    s32 j[4];
    u8 pad1ED8[8];
} Scene_b187_01E042C0;

static s32 func_01E042C0_b187(s32 arg0, s32 code) {
    Scene_b187_01E042C0 *g = (Scene_b187_01E042C0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6D00(s32);
    extern void func_00103260(s32 *, s32);
    extern void func_00103290(s32 *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_00104490(void *, void *, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern s32 func_001033D0(void *, f32, f32);
    extern void func_00103540(void *, f32, f32);
    extern void func_00103390(void *, f32, f32);
    extern s32 func_0019A5C8();
    extern s32 b187_01E02230();
    Vec4f v[2];
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 a;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1EE0);
        func_00103890(&g->c0);
        func_00103890(&g->c1);
        func_00103890(&g->c4);
        func_00103890(&g->c2);
        func_00103890(&g->c3);
        func_00103890(&g->c5);
        func_00103890(&g->c6);
        g->j[0] = func_001F5560(func_001F53A0(), 0x1F, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 8, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x40, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x48, 0);
        g->timer = 0xE6;
        g->t = 1;
        g->code = code;
        g->cnt = 0x13;
        g->fade = 0x80;
        g->col[2] = 0xE0;
        g->col[1] = 0x70;
        g->col[0] = 0xA0;
        g->col[3] = 0;
        g->disc1.flags = 0x80000;
        g->disc1.c[2] = 0xE0;
        g->disc1.c[1] = 0x50;
        g->disc1.c[0] = 0x60;
        g->disc1.c[3] = 0;
        g->disc1.radius = 10.0f;
        g->disc1.count = 0x24;
        g->disc1.height = 0;
        g->disc2.flags = 0;
        g->disc2.c[2] = 0xE0;
        g->disc2.c[1] = 0x50;
        g->disc2.c[0] = 0x60;
        g->disc2.c[3] = 0;
        g->disc2.radius = 15.0f;
        g->disc2.count = 0x24;
        g->disc2.height = 0;
        g->shot.f0 = 0;
        g->shot.r = 0x80;
        g->shot.g = 0x80;
        g->shot.b = 0x80;
        g->shot.a = 0x30;
        g->shot.size = 0.0f;
        g->shot.n = 5;
        g->shot.id = func_001F53A0();
        func_00103290(tx, 0);
        g->laser.tex = tx[0];
        g->laser.flags = 0x8003;
        g->laser.c[2] = 0x80;
        g->laser.c[1] = 0x80;
        g->laser.c[0] = 0x80;
        g->laser.a = 0x80;
        g->laser.uv[0] = 0;
        g->laser.uv[1] = 0;
        g->laser.uv[2] = 0x10;
        g->laser.uv[3] = 0x20;
        g->laser.uv[4] = 0;
        g->laser.uv[5] = 0;
        g->laser.uv[6] = 0x80;
        g->laser.uv[7] = 0x40;
        g->laser.base = 150.0f;
        g->laser.h22 = 8;
        g->laser.tick = 0;
        g->laser.h26 = 0x30;
        g->laser.n1 = 0x20;
        g->laser.n2 = 0;
        g->laser.h2C = 1;
        g->spr2.flags = 1;
        g->spr2.uv[0] = 0x40;
        g->spr2.uv[1] = 0;
        g->spr2.uv[2] = 0x40;
        g->spr2.uv[3] = 0x40;
        g->spr2.c[2] = 0x80;
        g->spr2.c[1] = 0x80;
        g->spr2.c[0] = 0x80;
        g->spr2.c[3] = 0x40;
        g->spr2.w0 = 0.5f;
        g->spr2.w1 = 1.0f;
        g->spr2.h0 = 8.0f;
        g->spr2.h1 = 0.0f;
        func_01E03B50_b187((Obj_b087_01E03B30 *)&g->spr2, tx[0], 3.0f);
        g->emit.tex = tx[0];
        g->emit.flags = 0x70000003;
        g->emit.c[2] = 0x80;
        g->emit.c[1] = 0x80;
        g->emit.c[0] = 0x80;
        g->emit.c[3] = 0;
        g->emit.size = 0.5f;
        g->emit.rot[0] = 0;
        g->emit.rot[1] = 0;
        g->emit.rot[2] = 0;
        g->emit.uv[0] = 0;
        g->emit.uv[1] = 0x20;
        g->emit.uv[2] = 0x20;
        g->emit.uv[3] = 0x20;
        g->emit.uv[4] = 0;
        g->emit.uv[5] = 0x20;
        g->emit.uv[6] = 0x80;
        g->emit.uv[7] = 0x40;
        g->emit.pts = g->pts;
        g->emit.rots = 0;
        g->emit.x48 = 0;
        g->emit.radius = 15.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 1;
        g->emit.rate = 0;
        func_01E00250_b187((Ring_b001_01E01B20 *)&g->emit, 0.5f);
        for (i = 0; i < g->emit.count; i++) {
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x30;
            g->pts[i].frame = 0;
            g->pts[i].y += 10.0f;
        }
        func_00103260(tx, 0xF);
        g->spr1.flags = 1;
        g->spr1.uv[0] = 0x8E;
        g->spr1.uv[1] = 0;
        g->spr1.uv[2] = 0x22;
        g->spr1.uv[3] = 0x40;
        g->spr1.c[2] = 0xE0;
        g->spr1.c[1] = 0x50;
        g->spr1.c[0] = 0x60;
        g->spr1.c[3] = 0x20;
        func_01E028D0_b187((Obj_b000_01E032C0 *)&g->spr1, tx[0], 2.0f);
        g->c3.x = g->c3.y = g->c3.z = 0.1f;
        return 0;
    }
    func_001F53C0(1, func_001F53A0(), &g->c6.pos);
    if (g->t == 0x69) {
        func_001F5F90(func_001F5380(), &v[0]);
        func_001F5620(func_001F53A0(), g->j[0], &v[1]);
        func_00103DB0(&v[0], &v[1], &g->c5.rot);
        g->c5.pos = v[1];
    }
    func_001F5620(func_001F53A0(), g->j[0], &v[0]);
    func_001F5620(func_001F53A0(), g->j[1], &v[1]);
    func_00103DB0(&v[0], &v[1], &g->c4.rot);
    func_001F5F90(func_001F5380(), &g->tgt);
    func_001F5F90(func_001F5380(), &g->c3.pos);
    func_001F5620(func_001F53A0(), g->j[0], &g->c4.pos);
    func_001F5620(func_001F53A0(), g->j[0], &g->c2.pos);
    if (g->t <= 0x69) {
        func_001F5620(func_001F53A0(), g->j[0], &g->c1.pos);
    }
    if (g->t >= 0x69) {
        func_01E03040_b187((Obj_b000_01E03A30 *)&g->laser, (Pt_b000_01E03A30 *)g->lpts, (f32 *)&g->c1.pos);
        func_00104490(&g->c1.pos, &g->tgt, g->cnt);
        if (g->cnt != 0) {
            g->cnt--;
        }
    }
    func_001038D0(&g->c0);
    func_001039A0(&g->c1);
    func_001038D0(&g->c4);
    func_001039A0(&g->c2);
    func_001039A0(&g->c3);
    func_001038D0(&g->c5);
    if (g->t >= 0x69) {
        func_01E00120_b187();
    }
    if (g->t < 0xCC) {
        func_00103470((u8 *)&g->fade, 0x20, 4);
    } else {
        func_001032C0((u8 *)&g->fade, 0x80, 4);
    }
    func_001F6D00((u8)g->fade);
    if (g->t >= 0x1E && g->t < 0x69) {
        b187_01E02230(&g->shot, &g->c6.pos);
        if (g->t >= 0x3D) {
            func_00103540(&g->shot.size, 0.0f, 2.0f);
        } else {
            { f32 q = 2.0f; func_00103390(&g->shot.size, 40.0f, q); }
        }
    }
    if (g->t >= 0x7B) {
        if (g->t < 0xB2) {
            func_001033D0(&g->c3, 2.0f, 0.05f);
        } else {
            g->c3.x = g->c3.y = g->c3.z = 1.0f;
        }
        func_01E01CD0_b187(ot, (Disc_b540_01E00250 *)&g->disc2, (Cam_b540_01E00250 *)&g->c3);
        func_01E02A30_b187(ot, (Spr_b000_01E03420 *)&g->spr1, (Cam_b000_01E03420 *)&g->c3);
        if (g->t >= 0xBE) {
            func_00103470(&g->disc2.c[3], 0, 0x10);
            func_00103470(&g->spr1.c[3], 0, 2);
        } else {
            func_001032C0(&g->disc2.c[3], 0xFF, 8);
        }
        for (i = 0; i < 0x40; i++) {
            g->spr1.r[i][0] += 0x80;
            g->spr1.r[i][1] += 0x80;
            g->spr1.r[i][2] += 0x80;
        }
    }
    if (g->t >= 0x69) {
        if (g->t == 0x69) {
            g->disc1.c[3] = 0xFF;
        }
        func_01E01CD0_b187(ot, (Disc_b540_01E00250 *)&g->disc1, (Cam_b540_01E00250 *)&g->c2);
        func_00103470(&g->disc1.c[3], 0, 4);
    }
    if (g->t < 0x69) {
        func_01E003E0_b187(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->c4);
        if (g->t >= 0x51) {
            func_001032C0(&g->emit.c[3], 0x80, 8);
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts[i].t >= 0) {
                g->pts[i].y -= 1.0f;
                func_001032C0(&g->pts[i].a, 0x80, 8);
                if (g->pts[i].y > 0.0f) {
                    g->pts[i].z *= 0.8f;
                    g->pts[i].x *= 0.8f;
                }
                if (g->pts[i].y < 0.0f) {
                    a = func_0019A5C8() % 0x10000;
                    g->pts[i].z = g->emit.radius * func_0020B480(a);
                    g->pts[i].x = g->emit.radius * func_0020B550(a);
                    g->pts[i].y = 10.0f + (f32)(func_0019A5C8() % 10);
                    g->pts[i].a = 0;
                }
            }
        }
    }
    if (g->t > 0x69) {
        func_01E03CB0_b187(ot, (Spr_b087_01E03C90 *)&g->spr2, (Cam_b087_01E03C90 *)&g->c5);
        func_00103470(&g->spr2.c[3], 0, 1);
        func_001033D0(&g->c5, 3.0f, 0.4f);
        func_01E03190_b187(ot, (Laser_b117_01E00270 *)&g->laser, (Pt_b117_01E00270 *)g->lpts,
                           (Cam_b117_01E00270 *)&g->c0);
    }
    g->t++;
    g->timer--;
    if (g->t == 0xCC) {
        return 2;
    }
    if (g->t == 0x6F) {
        return 1;
    }
    if (g->t >= 0x7B && g->t < 0xCC) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
