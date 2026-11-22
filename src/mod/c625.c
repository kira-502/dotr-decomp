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

static void func_01E00080_c625(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_c625(u8 *c) {
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

static s32 func_01E00260_c625(s32 arg0, Src_b000_01E00400 *c) {
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

static s32 func_01E003C0_c625(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_c625((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

static s32 func_01E01CB0_c625(Obj_b000_01E032C0 *obj, s32 kind, f32 scale) {
    extern Tbl_b000_01E032C0 D_01E03980_c625;
    Tbl_b000_01E032C0 tbl = D_01E03980_c625;
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

static s32 func_01E01E10_c625(s32 obj, Spr_b000_01E03420 *spr, Cam_b000_01E03420 *cam) {
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
    func_01E00080_c625((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
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

/* OVL_WARM */

/* shape b021:01E03460, 608 insns, 12 copies: draws a lightning bolt between two points: the line is cut into n pieces
   (at most 16), each inner point shaken by a random jitter, all projected; then each piece is one textured
   quad (random texture corner) as wide as its screen length / 3 (or a fixed width), drawn only when both ends
   are visible and the piece is not past the moving head. Calls the module's colour helper (shape b000:01E00100).
   The spilled ot parameter is aligned(8): that puts its home at 0xB8 like the original (plain s32 gives 0xBC). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b021_01E03460;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b021_01E03460 xyz;
} Vtx_b021_01E03460;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b021_01E03460 v[4];
    u8 tail[0x20];
} Pkt_b021_01E03460;

typedef struct {
    s16 u, v, w, h;
} Rect_b021_01E03460;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 color;
    s16 n;
    s16 jitter;
    Rect_b021_01E03460 rect;
    u8 pad18[0x10];
    s16 head;
    u8 pad2A[2];
    f32 width;
} Bolt_b021_01E03460;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b021_01E03460;

static s32 func_01E02420_c625(s32 ot __attribute__((aligned(8))), Bolt_b021_01E03460 *b, Cam_b021_01E03460 *cam, Vec4f *p1, Vec4f *p2) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    Xyz_b021_01E03460 s[17];
    Vec4f mid;
    f32 depth[17];
    Pkt_b021_01E03460 pkt;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 w;
    f32 len;
    s32 vis;
    s32 k;
    s32 r;

    vis = 0;
    if (b->n > 16) {
        b->n = 16;
    }
    ((Pkt_b021_01E03460 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b021_01E03460 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b021_01E03460 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b021_01E03460 *)(s32)&pkt)->pad = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    func_01E00080_c625((Vtx_b000_01E00100 *)&pkt, &b->color);
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    dz = p2->z - p1->z;
    if (func_00205440(p1, cam->view, &s[0], &depth[0]) != 0) {
        if (func_00101600(&s[0]) != 0) {
            vis |= 1;
        }
    }
    for (k = 1; k < b->n; k++) {
        t = (f32)k / b->n;
        if (b->jitter != 0) {
            mid.x = p1->x + dx * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
            mid.y = p1->y + dy * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
            mid.z = p1->z + dz * t + 0.1f * (func_0019A5C8() % (b->jitter * 2) - b->jitter);
        } else {
            mid.x = p1->x + dx * t;
            mid.y = p1->y + dy * t;
            mid.z = p1->z + dz * t;
        }
        if (func_00205440(&mid, cam->view, &s[k], &depth[k]) != 0) {
            if (func_00101600(&s[k]) != 0) {
                vis |= 1 << k;
            }
        }
    }
    if (func_00205440(p2, cam->view, &s[b->n], &depth[b->n]) != 0) {
        if (func_00101600(&s[b->n]) != 0) {
            vis |= 1 << b->n;
        }
    }
    for (k = 0; k < b->n; k++) {
        if (func_00104520(b->flags, 0x1A) != 0 || k <= b->head) {
            r = func_0019A5C8() % 4;
            if (r == 0) {
                func_00104540(&pkt, &b->rect, 1);
            } else if (r == 1) {
                func_00104540(&pkt, &b->rect, 2);
            } else if (r == 2) {
                func_00104540(&pkt, &b->rect, 5);
            } else {
                func_00104540(&pkt, &b->rect, 7);
            }
            dx = func_001A6970((s32)(s[k].x - s[k + 1].x));
            dy = func_001A6970((s32)(s[k].y - s[k + 1].y));
            len = func_001A6C60(dx * dx + dy * dy);
            if (func_00104520(b->flags, 0x1B) != 0) {
                w = b->width;
            } else {
                w = len / 3.0f;
            }
            if (dx > dy) {
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[k].x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[k + 1].x;
                pkt.v[0].xyz.y = s[k].y - w;
                pkt.v[1].xyz.y = s[k + 1].y - w;
                pkt.v[2].xyz.y = w + s[k].y;
                pkt.v[3].xyz.y = w + s[k + 1].y;
            } else {
                pkt.v[0].xyz.x = s[k].x - w;
                pkt.v[1].xyz.x = s[k + 1].x - w;
                pkt.v[2].xyz.x = w + s[k].x;
                pkt.v[3].xyz.x = w + s[k + 1].x;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[k].y;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[k + 1].y;
            }
            func_00208CB0(&pkt, 2 | (2 << 2) | ((u64)b->rect.u << 4) | ((u64)(b->rect.u + b->rect.w - 1) << 14) |
                                    ((u64)b->rect.v << 24) | ((u64)(b->rect.v + b->rect.h - 1) << 34));
            func_00208700(&pkt, b->texture, 1);
            if (func_00104520(vis, k) != 0 && func_00104520(vis, k + 1) != 0) {
                if (func_00104520(b->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[k].z;
                    pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[k + 1].z;
                    func_002075F0(&pkt, ot, (u32)((depth[k] + depth[k + 1]) / 2.0f));
                }
            }
        }
    }
    b->head++;
    if (b->head > b->n) {
        b->head = 0;
    }
    return 0;
}

/* shape c625:01E02DA0 (c625), 728 insns, 1 copy: c625 scene manager: code >= 0 sets up 87 lightning bolts (a 60-bolt
   ring of random points, 21 to a spot on the field, 6 from a point above), a spark emitter of 32 particles and a
   sprite with 64 random rotations; then draws the flash and fade, the three bolt groups by tick (fading after ticks
   7/30/22), the growing sprite and the sparks; returns 2 at tick 48, 8 when the timer runs out */

typedef struct Crd_c625_01E02DA0 {
    Vec4f scale;
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c625_01E02DA0;

typedef struct Rot_c625_01E02DA0 {
    s32 x, y, z, w;
} Rot_c625_01E02DA0;

typedef struct Spr_c625_01E02DA0 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rot_c625_01E02DA0 rot[64];
} Spr_c625_01E02DA0;

typedef struct Scene_c625_01E02DA0 {
    Crd_c625_01E02DA0 cam0;
    Bolt_b021_01E03460 bolt[60];
    Bolt_b021_01E03460 boltB[21];
    Bolt_b021_01E03460 boltC[6];
    Crd_c625_01E02DA0 crd[60];
    Crd_c625_01E02DA0 crdB[21];
    Crd_c625_01E02DA0 crdC[6];
    Crd_c625_01E02DA0 cam1;
    Emit_b000_01E01140 emit;
    Pt_b000_01E01140 pts[32];
    Crd_c625_01E02DA0 cam2;
    Spr_c625_01E02DA0 spr;
    s32 flags;
    s32 timer;
    s32 t;
    s32 code;
    s32 x;
    s32 z;
    Src_b000_01E00400 flash;
    Src_b000_01E00400 fade;
} Scene_c625_01E02DA0;

static s32 func_01E02DA0_c625(s32 arg0, s32 code) {
    Scene_c625_01E02DA0 *g = (Scene_c625_01E02DA0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F5380(void);
    extern void func_001E10F0(s32, s32, s32, void *);
    extern void func_00103260(s32 *, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001043F0(void *, f32);
    extern s32 func_001033D0(f32 *, f32, f32);
    extern s32 func_0019A5C8();
    s32 ot;
    Vec4f v;
    s32 tx[4];
    s32 i;
    s32 base;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3E90);
        func_00103890(&g->cam0);
        func_00103890(&g->cam2);
        for (i = 0; i < 3; i++) {
            func_00103890(&g->crd[i]);
        }
        func_00103890(&g->cam1);
        g->flags = 0;
        g->timer = 0x31;
        g->t = 0;
        g->code = code;
        g->flash.r = 0x80;
        g->flash.g = 0x50;
        g->flash.b = 0xE0;
        g->flash.a = 0xFF;
        g->fade.r = 0x80;
        g->fade.g = 0x80;
        g->fade.b = 0x80;
        g->fade.a = 0x20;
        g->x = func_001F5380() & 0xFF;
        g->z = func_001F5380() >> 8;
        func_001E10F0(g->x, g->z, 0, &g->cam2.pos);
        func_00103260(tx, 2);
        g->emit.texture = (void *)tx[0];
        g->emit.flags = 0x48000403;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x40;
        g->emit.size = 10.0f;
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
        g->emit.rots = 0;
        *(s32 *)g->emit.pad48 = 0;
        g->emit.radius = 15.0f;
        g->emit.grow = 10.0f;
        g->emit.count = 0x20;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&v, 10.0f);
            g->pts[i].x = v.x;
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x80;
            g->pts[i].frame = func_0019A5C8() % 8;
        }
        g->cam1.pos.x = 0.0f;
        g->cam1.pos.z = 0.0f;
        g->cam1.pos.y = 175.0f;
        func_00103260(tx, 0xF);
        for (i = 0; i < 60; i++) {
            g->bolt[i].texture = (void *)tx[0];
            g->bolt[i].flags = 0;
            g->bolt[i].rect.u = i % 3 * 44 + 10;
            g->bolt[i].rect.v = 0;
            g->bolt[i].rect.w = 0x2C;
            g->bolt[i].rect.h = 0x80;
            g->bolt[i].color.r = 0x80;
            g->bolt[i].color.g = 0x50;
            g->bolt[i].color.b = 0xE0;
            g->bolt[i].color.a = 0x80;
            g->bolt[i].n = 8;
            g->bolt[i].head = -(i % 3 * 4);
            g->bolt[i].jitter = 100;
            *(s32 *)&g->bolt[i].pad18[8] = 0;
            *(s32 *)&g->bolt[i].pad18[12] = 0;
            g->crd[i].pos.x = 0.1f * (func_0019A5C8() % 3000 - 1500);
            g->crd[i].pos.y = 0.1f * (func_0019A5C8() % 1500 + 1000);
            g->crd[i].pos.z = 0.1f * (func_0019A5C8() % 3000 - 1500);
        }
        for (i = 0; i < 21; i++) {
            g->boltB[i].texture = (void *)tx[0];
            g->boltB[i].flags = 0;
            g->boltB[i].rect.u = i % 3 * 44 + 10;
            g->boltB[i].rect.v = 0;
            g->boltB[i].rect.w = 0x2C;
            g->boltB[i].rect.h = 0x80;
            g->boltB[i].color.r = 0x80;
            g->boltB[i].color.g = 0x50;
            g->boltB[i].color.b = 0xE0;
            g->boltB[i].color.a = 0xA0;
            g->boltB[i].n = 8;
            g->boltB[i].head = -(i % 3 * 4);
            g->boltB[i].jitter = 100;
            *(s32 *)&g->boltB[i].pad18[8] = 0;
            *(s32 *)&g->boltB[i].pad18[12] = 0;
            g->crdB[i].pos.x = g->cam2.pos.x + 0.1f * (func_0019A5C8() % 2000 - 1000);
            g->crdB[i].pos.y = g->cam2.pos.y + 0.1f * (func_0019A5C8() % 500);
            g->crdB[i].pos.z = g->cam2.pos.z + 0.1f * (func_0019A5C8() % 2000 - 1000);
        }
        for (i = 0; i < 6; i++) {
            g->boltC[i].texture = (void *)tx[0];
            g->boltC[i].flags = 0;
            g->boltC[i].rect.u = i % 3 * 44 + 10;
            g->boltC[i].rect.v = 0;
            g->boltC[i].rect.w = 0x2C;
            g->boltC[i].rect.h = 0x80;
            g->boltC[i].color.r = 0x80;
            g->boltC[i].color.g = 0x50;
            g->boltC[i].color.b = 0xE0;
            g->boltC[i].color.a = 0xFF;
            g->boltC[i].n = 8;
            g->boltC[i].head = -(i % 3 * 4);
            g->boltC[i].jitter = 200;
            *(s32 *)&g->boltC[i].pad18[8] = 0;
            *(s32 *)&g->boltC[i].pad18[12] = 0;
            g->crdC[i].pos.x = g->cam1.pos.x + 0.1f * (func_0019A5C8() % 400 - 200);
            g->crdC[i].pos.y = g->cam1.pos.y + 0.1f * (func_0019A5C8() % 50);
            g->crdC[i].pos.z = g->cam1.pos.z + 0.1f * (func_0019A5C8() % 400 - 200);
        }
        g->spr.flags = 1;
        g->spr.u = 0x8E;
        g->spr.v = 0;
        g->spr.w = 0x22;
        g->spr.h = 0x40;
        g->spr.r = 0x80;
        g->spr.g = 0x50;
        g->spr.b = 0xE0;
        g->spr.a = 0x20;
        func_01E01CB0_c625((Obj_b000_01E032C0 *)&g->spr, tx[0], 4.0f);
        base = 0;
        for (i = 0; i < 64; i++) {
            g->spr.rot[i].x = func_0019A5C8() % 0x4000 + base;
            g->spr.rot[i].y = func_0019A5C8() % 0x10000;
            g->spr.rot[i].z = func_0019A5C8() % 0x6000 - 0x3000;
        }
        g->cam2.scale.x = g->cam2.scale.y = g->cam2.scale.z = 0.1f;
        return 0;
    }
    func_001038D0(&g->cam0);
    func_001038D0(&g->cam2);
    func_001038D0(&g->cam1);
    if (g->t >= 20 && g->t < 32) {
        g->fade.a = 0x60;
    } else if (g->t >= 32) {
        func_00103470(&g->fade.a, 0, 6);
    }
    func_01E00120_c625((u8 *)&g->fade);
    func_01E00260_c625(ot, &g->flash);
    if (g->t > 32) {
        func_00103470(&g->flash.a, 0, 8);
    } else if (g->t % 2 == 0) {
        g->flash.a = 0x80;
    } else {
        g->flash.a = 0x40;
    }
    if (g->t < 0xD3) {
        for (i = 0; i < 59; i++) {
            func_01E02420_c625(ot, &g->bolt[i], (Cam_b021_01E03460 *)&g->cam0, &g->crd[i].pos, &g->crd[i + 1].pos);
        }
        func_01E02420_c625(ot, &g->bolt[59], (Cam_b021_01E03460 *)&g->cam0, &g->crd[59].pos, &g->crd[0].pos);
        if (g->t >= 7) {
            for (i = 0; i < 60; i++) {
                g->bolt[i].flags |= 0x4000000;
                func_00103470(&g->bolt[i].color.a, 0, 8);
            }
        }
    }
    if (g->t > 16) {
        for (i = 0; i < 21; i++) {
            func_01E02420_c625(ot, &g->boltB[i], (Cam_b021_01E03460 *)&g->cam0, &g->cam2.pos, &g->crdB[i].pos);
        }
        if (g->t >= 30) {
            for (i = 0; i < 21; i++) {
                g->boltB[i].flags |= 0x4000000;
                func_00103470(&g->boltB[i].color.a, 0, 10);
            }
        }
        func_01E01E10_c625(ot, (Spr_b000_01E03420 *)&g->spr, (Cam_b000_01E03420 *)&g->cam2);
        if (!(g->cam2.scale.x < 1.0f)) {
            func_001033D0((f32 *)&g->cam2, 5.0f, 0.05f);
            func_00103470(&g->spr.a, 0, 1);
        } else {
            func_001033D0((f32 *)&g->cam2, 1.0f, 0.3f);
        }
    }
    if (g->t > 8) {
        for (i = 0; i < 6; i++) {
            func_01E02420_c625(ot, &g->boltC[i], (Cam_b021_01E03460 *)&g->cam0, &g->crdC[i].pos, &g->cam2.pos);
        }
        if (g->t >= 22) {
            for (i = 0; i < 6; i++) {
                g->boltC[i].flags |= 0x4000000;
                func_00103470(&g->boltC[i].color.a, 0, 16);
            }
        }
    }
    func_01E003C0_c625(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->cam1);
    for (i = 0; i < g->emit.count; i++) {
        if (g->pts[i].t >= 0) {
            g->pts[i].x *= 1.1f;
            g->pts[i].y *= 1.02f;
            g->pts[i].z *= 1.1f;
            func_00103470(&g->pts[i].a, 0, 8);
        }
        if (g->pts[i].t >= 32) {
            func_001043F0(&v, 10.0f);
            g->pts[i].x = v.x;
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].t = 0;
            g->pts[i].a = 0x80;
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 48) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
