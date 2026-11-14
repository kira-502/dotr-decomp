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

static void func_01E00080_b105(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

/* shape b105:01E00120, 479 insns, 10 copies. Calls the module colour helper at 0x1E00080 (shape b000:01E00100)
   as a plain extern: nothing is kept in a scratch register across that call. */


typedef struct {
    u8 b, g, r, a;
} Src_b105_01E00120;

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
} Uv_b105_01E00120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    union {
        Uv_b105_01E00120 i;
        f32 f[2];
    } st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b105_01E00120;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b105_01E00120 v[4];
    u8 tail[0x20];
} Pkt_b105_01E00120;

typedef struct {
    f32 x, y, z, w;
} Vec_b105_01E00120;

typedef struct {
    f32 x, y, z;
} Pt_b105_01E00120;

typedef struct {
    void *texture;
    s32 flags;
    Src_b105_01E00120 color;
    f32 r;
    f32 spin[4];
    union {
        struct {
            s16 u, v, w, h;
        } i;
        struct {
            f32 u, v, w, h;
        } f;
    } uv;
    Vec_b105_01E00120 rots[60];
    Pt_b105_01E00120 pts[60];
} Spark_b105_01E00120;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b105_01E00120;

extern void b105_01E00080(Pkt_b105_01E00120 *p, Src_b105_01E00120 *s);

static s32 func_01E00120_b105(s32 obj, Spark_b105_01E00120 *sp, Cam_b105_01E00120 *cam, s32 mode) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00103620(void *, void *);
    extern void func_001036A0(void *, s32);
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    f32 depth[4];
    f32 m[16];
    Vec_b105_01E00120 a;
    Vec_b105_01E00120 b;
    Pkt_b105_01E00120 pkt;
    s32 i;
    f32 rx;
    f32 ry;

    ((Pkt_b105_01E00120 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b105_01E00120 *)(s32)&pkt)->pad = 0;
    if (func_00104520(sp->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(sp->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(sp->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    b105_01E00080(&pkt, &sp->color);
    if (func_00104520(sp->flags, 0) != 0) {
        ((Pkt_b105_01E00120 *)(s32)&pkt)->count |= 0x800;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[0].st)->s = sp->uv.i.u << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[0].st)->t = sp->uv.i.v << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[1].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[1].st)->t = sp->uv.i.v << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[2].st)->s = sp->uv.i.u << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[2].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[3].st)->s = (sp->uv.i.u + sp->uv.i.w - 1) << 4;
        ((Uv_b105_01E00120 *)(s32)&pkt.v[3].st)->t = (sp->uv.i.v + sp->uv.i.h - 1) << 4;
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
    if (func_00104520(sp->flags, 0x1E) != 0) {
        func_0020C630(m, sp->spin);
        for (i = 0; i < 60; i++) {
            b.x = sp->pts[i].x;
            b.y = sp->pts[i].y;
            b.z = sp->pts[i].z;
            func_0020CDD0(&a, m, &b);
            sp->pts[i].x = a.x;
            sp->pts[i].y = a.y;
            sp->pts[i].z = a.z;
        }
    }
    if (sp->uv.i.w == sp->uv.i.h) {
        rx = ry = sp->r;
    } else if (sp->uv.i.h < sp->uv.i.w) {
        rx = sp->r;
        ry = rx * ((f32)sp->uv.i.h / sp->uv.i.w);
    } else {
        ry = sp->r;
        rx = ry * ((f32)sp->uv.i.w / sp->uv.i.h);
    }
    for (i = 0; i < 60; i++) {
        func_001036A0(&sp->pts[i], mode);
        func_0020C630(m, &sp->rots[i]);
        a.x = -rx;
        a.y = ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            sp->flags |= 0x100000;
        }
        a.x = rx;
        a.y = ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            sp->flags |= 0x200000;
        }
        a.x = -rx;
        a.y = -ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            sp->flags |= 0x400000;
        }
        a.x = rx;
        a.y = -ry;
        a.z = 0.0f;
        func_0020CDD0(&b, m, &a);
        func_00103620(&b, &sp->pts[i]);
        if (func_00205440(&b, cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            sp->flags |= 0x800000;
        }
        func_00208700(&pkt, sp->texture, 0);
        if (func_00104520(sp->flags, 0x14) != 0 && func_00104520(sp->flags, 0x15) != 0 &&
            func_00104520(sp->flags, 0x16) != 0 && func_00104520(sp->flags, 0x17) != 0) {
            if (func_00104520(sp->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        sp->flags &= 0xFF0FFFFF;
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

static s32 func_01E008A0_b105(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b105((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* shape b105:01E02190 (LkEFF_SortBlowing), 469 insns, 7 copies (-O3,p): draws n rotating textured sprites as 3 quads
   each: per item a frame cell of a sheet (flag 1 picks row/col order), the cell stepped every rate ticks, scale
   shrinking (flag 0xF), 4 transformed points split in 3 strips, alpha capped by the colour */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b105_01E02190;

typedef struct {
    Uv_b105_01E02190 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b105_01E02190;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b105_01E02190 v[4];
    u8 tail[0x20];
} Pkt_b105_01E02190;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 cell;
    s16 t;
    f32 scale;
    s32 ang;
    u8 pad18[8];
} Item_b105_01E02190;

typedef struct {
    void *texture;
    u8 b, g, r, a;
    s32 flags;
    u8 padC[8];
    s16 w, h, u, v, tw, th;
    Vec4f q[4];
    f32 dy;
    f32 shrink;
    u8 pad68[0xE];
    s16 n1;
    s16 n2;
    u8 pad7A[2];
    s16 cells;
    s16 rate;
} Obj_b105_01E02190;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b105_01E02190;

typedef struct {
    Vec4f v;
} Axis_b105_01E02190;

#pragma optimization_level 3

static s32 func_01E02190_b105(s32 ot __attribute__((aligned(8))), Obj_b105_01E02190 *o, Item_b105_01E02190 *it, Cam_b105_01E02190 *cam __attribute__((aligned(16)))) {
    extern Axis_b105_01E02190 D_01E03700_b105;
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_0020CF00(void *, void *, void *, s32);
    f32 m[16];
    f32 d[4];
    Axis_b105_01E02190 axis;
    Vec4f p[4];
    Vec4f out[4];
    Pkt_b105_01E02190 pkt __attribute__((aligned(8)));
    s32 i;
    s32 n;
    s32 j;
    s16 cols;
    s16 rows;
    s16 w3;
    Vec4f *q;
    s16 b;
    s16 a;

    axis = D_01E03700_b105;
    if (func_00104520(o->flags, 0x1F) != 0) {
        n = o->n1;
    } else {
        n = o->n2;
    }
    ((Pkt_b105_01E02190 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b105_01E02190 *)(s32)&pkt)->tag = 9;
    ((Pkt_b105_01E02190 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b105_01E02190 *)(s32)&pkt)->pad = 0;
    ((Pkt_b105_01E02190 *)(s32)&pkt)->count |= 0x800;
    func_00208700(&pkt, o->texture, 1);
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
    pkt.q = 1.0f;
    cols = o->tw / o->w;
    rows = o->th / o->h;
    w3 = o->w / 3;
    for (i = 0; i < n; i++, it++) {
        if (it->t < 0) {
            it->t++;
            continue;
        }
        if (func_00104520(o->flags, 1) != 0) {
            b = o->u + o->w * (it->cell % cols);
            a = o->v + o->h * (it->cell / cols);
        } else {
            b = o->u + o->w * (it->cell / rows);
            a = o->v + o->h * (it->cell % rows);
        }
        if (it->t % o->rate == 0) {
            it->cell++;
            if (it->cell > o->cells - 1) {
                it->cell = 0;
            }
        }
        if (func_00104520(o->flags, 0xF) != 0) {
            it->scale *= o->shrink;
        }
        it->t++;
        func_0020C750(m, &axis, it->ang);
        func_0020CF00(out, m, o->q, 4);
        it->ang += 0x400;
        if (it->a < o->a) {
            pkt.a = it->a;
        } else {
            pkt.a = o->a;
        }
        for (j = 0, q = out; j < 3; j++, q++) {
            p[0].x = it->x + q[0].x * it->scale;
            p[0].y = o->dy + (it->y + q[0].y * it->scale);
            p[0].z = it->z + q[0].z * it->scale;
            p[1].x = it->x + q[1].x * it->scale;
            p[1].y = o->dy + (it->y + q[1].y * it->scale);
            p[1].z = it->z + q[1].z * it->scale;
            p[2].x = it->x + q[0].x * it->scale;
            p[2].y = it->y + q[0].y * it->scale;
            p[2].z = it->z + q[0].z * it->scale;
            p[3].x = it->x + q[1].x * it->scale;
            p[3].y = it->y + q[1].y * it->scale;
            p[3].z = it->z + q[1].z * it->scale;
            if (func_00205630(p, 0x70000000, cam->view, &pkt, d) != 0) {
                pkt.v[0].st.s = (b + w3 * j) * 16;
                ((Uv_b105_01E02190 *)(s32)&pkt.v[0].st)->t = a * 16;
                pkt.v[1].st.s = (b + w3 * (j + 1)) * 16;
                ((Uv_b105_01E02190 *)(s32)&pkt.v[1].st)->t = a * 16;
                pkt.v[2].st.s = (b + w3 * j) * 16;
                ((Uv_b105_01E02190 *)(s32)&pkt.v[2].st)->t = (a + o->h) * 16;
                pkt.v[3].st.s = (b + w3 * (j + 1)) * 16;
                ((Uv_b105_01E02190 *)(s32)&pkt.v[3].st)->t = (a + o->h) * 16;
                func_00208CB0(&pkt, ((u64)a << 24) |
                                        (((u64)(b + w3 * j) << 4) | 0xA | ((u64)(b + w3 * (j + 1) - 1) << 14)) |
                                        ((u64)(a + o->h - 1) << 34));
                func_002075F0(&pkt, ot, func_001A23B0(d[0]));
            }
        }
    }
    return 0;
}
#pragma optimization_level reset

/* shape b105:01E028F0 (b105), 872 insns, 1 copy: b105 scene manager (b273:01E02BB0's family): sparks, a 512-item
   rising column on a joint-to-joint frame and a 128-item column over the player, a 32-particle burst; returns 2/1/6/8
   by tick */

typedef struct Crd_b105_01E028F0 {
    Vec4f scale;
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b105_01E028F0;

typedef struct Item_b105_01E028F0 {
    f32 x, y, z;
    u8 a;
    u8 cell;
    s16 t;
    f32 scale;
    s32 ang;
    u8 pad18[8];
} Item_b105_01E028F0;

typedef struct Obj_b105_01E028F0 {
    s32 tex;
    u8 b, g, r, a;
    s32 flags;
    Item_b105_01E028F0 *items;
    s16 w, h, u, v, tw, th, f1C, f1E;
    Vec4f q[4];
    f32 dy;
    f32 shrink;
    u8 pad68[0xA];
    s16 f72;
    s16 f74;
    s16 n1;
    s16 n2;
    u8 pad7A[2];
    s16 cells;
    s16 rate;
} Obj_b105_01E028F0;

typedef struct Pt_b105_01E028F0 {
    f32 x, y, z;
} Pt_b105_01E028F0;

typedef struct Rot_b105_01E028F0 {
    s32 x, y, z, w;
} Rot_b105_01E028F0;

typedef struct Spark_b105_01E028F0 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 r0;
    s32 spin[4];
    s16 u, v, w, h;
    u8 pad28[8];
    Rot_b105_01E028F0 rots[60];
    Pt_b105_01E028F0 pts[60];
} Spark_b105_01E028F0;

typedef struct Part_b105_01E028F0 {
    f32 x, y, z;
    u8 a;
    u8 cell;
    s16 t;
} Part_b105_01E028F0;

typedef struct Emit_b105_01E028F0 {
    s32 tex;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    s32 f20, f24, f28;
    u8 pad2C[4];
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Part_b105_01E028F0 *parts;
    s32 f44;
    s32 f48;
    f32 radius;
    f32 f50;
    u8 pad54[6];
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b105_01E028F0;

typedef struct Scene_b105_01E028F0 {
    Crd_b105_01E028F0 c0;
    Crd_b105_01E028F0 c1;
    Obj_b105_01E028F0 obj1;
    Item_b105_01E028F0 items1[0x200];
    Obj_b105_01E028F0 obj2;
    Item_b105_01E028F0 items2[0x80];
    Crd_b105_01E028F0 c2;
    Spark_b105_01E028F0 spark;
    Crd_b105_01E028F0 c3;
    Emit_b105_01E028F0 emit;
    Part_b105_01E028F0 parts[0x20];
    Vec4f vec;
    s32 timer;
    s32 t;
    s32 code;
    s32 j0;
    s32 j1;
    u8 pad5C04[0xC];
} Scene_b105_01E028F0;

static s32 func_01E028F0_b105(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001039A0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103DB0(void *, void *, void *);
    extern void func_001043F0(void *, f32);
    extern void func_00103260(void *, s32);
    extern void func_00103290(void *, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern f32 func_0020B620(f32);
    extern f32 func_0020B730(f32);
    extern s32 func_0019A5C8();
    Scene_b105_01E028F0 *g = (Scene_b105_01E028F0 *)arg0;
    s32 ot;
    f32 sc[4];
    Vec4f pa;
    Vec4f pb;
    s32 tex[4];
    s32 i;
    s32 a;
    s32 k;
    s32 ang;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x5C10);
        func_00103890(&g->c0);
        func_00103890(&g->c1);
        func_00103890(&g->c2);
        func_00103890(&g->c3);
        g->j0 = func_001F5560(func_001F53A0(), 0x2D, 1);
        g->j1 = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->timer = 0x17B;
        g->t = 1;
        g->code = code;
        func_00103290(tex, 0);
        g->spark.tex = tex[0];
        g->spark.flags = 0x40001001;
        g->spark.r0 = 1.0f;
        g->spark.u = 0;
        g->spark.v = 0;
        g->spark.w = 0x40;
        g->spark.h = 0x80;
        g->spark.r = 0x80;
        g->spark.g = 0x80;
        g->spark.b = 0x80;
        g->spark.a = 0x80;
        g->spark.spin[0] = 0;
        g->spark.spin[1] = 0x400;
        g->spark.spin[2] = 0;
        for (i = 0; i < 60; i++) {
            a = func_0019A5C8() % 0x10000;
            g->spark.pts[i].y = 0.1f * (func_0019A5C8() % 1800);
            g->spark.pts[i].z = 2.0f * func_0020B480(a);
            g->spark.pts[i].x = 2.0f * func_0020B550(a);
            g->spark.rots[i].x = func_0019A5C8() % 0x10000;
            g->spark.rots[i].y = func_0019A5C8() % 0x10000;
            g->spark.rots[i].z = func_0019A5C8() % 0x10000;
        }
        func_00103260(tex, 0xF);
        g->obj1.tex = tex[0];
        g->obj1.r = 0x70;
        g->obj1.g = 0xA0;
        g->obj1.b = 0xD0;
        g->obj1.a = 0;
        g->obj1.flags = 0x9003;
        g->obj1.items = g->items1;
        g->obj1.dy = 10.0f;
        g->obj1.w = 0x80;
        g->obj1.h = 0xC0;
        g->obj1.u = 0x20;
        g->obj1.v = 0x20;
        g->obj1.tw = 0x80;
        g->obj1.th = 0xC0;
        g->obj1.f1C = 0x80;
        g->obj1.f1E = 0x100;
        g->obj1.shrink = 1.1f;
        g->obj1.f72 = 0;
        g->obj1.f74 = 0x18;
        g->obj1.n1 = 0x200;
        g->obj1.n2 = 0x200;
        g->obj1.cells = 8;
        g->obj1.rate = 1;
        for (k = 0, ang = 0; k < 4; k++) {
            g->obj1.q[k].z = func_0020B620(ang);
            g->obj1.q[k].x = func_0020B730(ang);
            g->obj1.q[k].y = 0.0f;
            ang += 0x1000;
        }
        for (i = 0; i < g->obj1.n1; i++) {
            g->items1[i].t = 0;
            g->items1[i].a = 0;
            g->items1[i].cell = func_0019A5C8() % 8;
            g->items1[i].y = 0.1f * (func_0019A5C8() % 1800);
            g->items1[i].ang = func_0019A5C8() % 0x10000;
            g->items1[i].scale = 0.1f * (func_0019A5C8() % 60);
        }
        g->obj2.tex = tex[0];
        g->obj2.r = 0x70;
        g->obj2.g = 0xA0;
        g->obj2.b = 0xD0;
        g->obj2.a = 0;
        g->obj2.flags = 0x8003;
        g->obj2.items = g->items2;
        g->obj2.dy = 4.0f;
        g->obj2.w = 0x80;
        g->obj2.h = 0xC0;
        g->obj2.u = 0x20;
        g->obj2.v = 0x20;
        g->obj2.tw = 0x80;
        g->obj2.th = 0xC0;
        g->obj2.f1C = 0x80;
        g->obj2.f1E = 0x100;
        g->obj2.shrink = 1.08f;
        g->obj2.f72 = 0;
        g->obj2.f74 = 0x18;
        g->obj2.n1 = 0x80;
        g->obj2.n2 = 0x80;
        g->obj2.cells = 8;
        g->obj2.rate = 1;
        {
            s32 n, ang2;

            for (n = 0, ang2 = 0; n < 4; n++) {
                g->obj2.q[n].z = func_0020B620(ang2);
                g->obj2.q[n].x = func_0020B730(ang2);
                g->obj2.q[n].y = 0.0f;
                ang2 += 0x1000;
            }
        }
        for (i = 0; i < g->obj2.n1; i++) {
            g->items2[i].t = 0;
            g->items2[i].a = 0x10;
            g->items2[i].cell = func_0019A5C8() % 8;
            g->items2[i].y = 0.1f * (func_0019A5C8() % 500);
            g->items2[i].ang = func_0019A5C8() % 0x10000;
            g->items2[i].scale = 0.1f * (func_0019A5C8() % 60);
        }
        g->emit.tex = tex[0];
        g->emit.flags = 0x48000003;
        g->emit.r = 0x70;
        g->emit.g = 0xA0;
        g->emit.b = 0xD0;
        g->emit.a = 0x40;
        g->emit.size = 10.0f;
        g->emit.f20 = 0;
        g->emit.f24 = 0;
        g->emit.f28 = 0;
        g->emit.u = 0x80;
        g->emit.v = 0xC0;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.u0 = 0x80;
        g->emit.v0 = 0xC0;
        g->emit.tw = 0x80;
        g->emit.th = 0x40;
        g->emit.parts = g->parts;
        g->emit.f44 = 0;
        g->emit.f48 = 0;
        g->emit.radius = 15.0f;
        g->emit.f50 = 10.0f;
        g->emit.count = 0x20;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(sc, 14.0f);
            if (!(sc[1] <= 0.0f)) {
                sc[1] *= -1.0f;
            }
            g->parts[i].x = sc[0];
            g->parts[i].y = sc[1];
            g->parts[i].z = sc[2];
            g->parts[i].t = -(func_0019A5C8() % 12);
            g->parts[i].a = 0x40;
            g->parts[i].cell = func_0019A5C8() % 8;
        }
        return 0;
    }
    func_001F53C0(1, func_001F5380(), &g->vec);
    func_001F5620(func_001F53A0(), g->j0, &pa);
    func_001F5620(func_001F53A0(), g->j1, &pb);
    g->c2.pos = pa;
    func_00103DB0(&g->vec, &pa, &g->c2.rot);
    func_001F53C0(1, func_001F53A0(), &g->c3.pos);
    g->c3.pos.y = 30.0f;
    func_001038D0(&g->c0);
    func_001039A0(&g->c1);
    func_001038D0(&g->c2);
    func_001038D0(&g->c3);
    func_01E02190_b105(ot, (Obj_b105_01E02190 *)&g->obj1, (Item_b105_01E02190 *)g->items1, (Cam_b105_01E02190 *)&g->c2);
    if (g->t == 0x4E) {
        g->obj1.a = 0x10;
    }
    if (g->t > 0x15E) {
        func_00103470(&g->obj1.a, 0, 1);
    }
    for (i = 0; i < g->obj1.n1; i++) {
        if (i % 2 == 0) {
            g->items1[i].y += 4.0f;
        } else {
            g->items1[i].y += 6.0f;
        }
        if (!(g->items1[i].y < 180.0f)) {
            g->items1[i].t = 0;
            g->items1[i].y = 0.1f * (func_0019A5C8() % 30);
            g->items1[i].scale = 0.1f * (func_0019A5C8() % 15);
        }
        if (g->t >= 0x4E) {
            if (g->items1[i].t == 0) {
                g->items1[i].a = g->obj1.a;
            }
        }
    }
    func_01E02190_b105(ot, (Obj_b105_01E02190 *)&g->obj2, (Item_b105_01E02190 *)g->items2, (Cam_b105_01E02190 *)&g->c3);
    if (g->t < 0x4E) {
        func_001032C0(&g->obj2.a, 0x10, 1);
    } else {
        func_00103470(&g->obj2.a, 0, 1);
    }
    for (i = 0; i < g->obj2.n1; i++) {
        if (i % 2 == 0) {
            g->items2[i].y += 2.0f;
        } else {
            g->items2[i].y += 3.0f;
        }
        if (!(g->items2[i].y < 50.0f)) {
            g->items2[i].t = 0;
            g->items2[i].y = 0.1f * (func_0019A5C8() % 30);
            g->items2[i].scale = 0.1f * (func_0019A5C8() % 30);
        }
        if (g->t >= 0x50) {
            if (g->items2[i].t == 0) {
                g->items2[i].a = g->obj2.a;
            }
        }
    }
    sc[1] = 1.0f;
    sc[0] = sc[2] = 1.1f;
    func_01E00120_b105(ot, (Spark_b105_01E00120 *)&g->spark, (Cam_b105_01E00120 *)&g->c2, (s32)sc);
    if (g->t >= 0x15E) {
        func_00103470(&g->spark.a, 0, 8);
    }
    for (i = 0; i < 60; i++) {
        if (i % 2 == 0) {
            g->spark.pts[i].y += 4.0f;
        } else {
            g->spark.pts[i].y += 6.0f;
        }
        if (!(g->spark.pts[i].y < 180.0f)) {
            a = func_0019A5C8() % 0x10000;
            g->spark.pts[i].y = 0.0f;
            g->spark.pts[i].z = 4.0f * func_0020B480(a);
            g->spark.pts[i].x = 4.0f * func_0020B550(a);
        }
        g->spark.rots[i].x += 0x1000;
        g->spark.rots[i].y += 0x1000;
        g->spark.rots[i].z += 0x1000;
    }
    func_01E008A0_b105(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->c3);
    if (g->t >= 0x6E) {
        func_00103470(&g->emit.a, 0x10, 1);
    }
    for (i = 0; i < g->emit.count; i++) {
        if (g->parts[i].t >= 0) {
            g->parts[i].x *= 1.05f;
            g->parts[i].y *= 1.07f;
            g->parts[i].z *= 1.05f;
            func_00103470(&g->parts[i].a, 0, 4);
        }
        if (g->parts[i].t >= 0x10) {
            func_001043F0(sc, 14.0f);
            if (!(sc[1] <= 0.0f)) {
                sc[1] *= -1.0f;
            }
            g->parts[i].x = sc[0];
            g->parts[i].y = sc[1];
            g->parts[i].z = sc[2];
            g->parts[i].t = 0;
            g->parts[i].a = 0x40;
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x15E) {
        return 2;
    }
    if (g->t == 0x6E) {
        return 1;
    }
    if (g->t >= 0x78 && g->t < 0x15E) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
