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

static void func_01E00080_b740(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b740(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b740((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* shape b055:01E02930, 325 insns, 8 copies: a lightning bolt from p0 to p1: 6 jittered points between the ends,
   a spline through the 8 (func_00102550) gives 28 points, projected and drawn as up to 27 coloured lines (all of
   them with flag 0x1A, else only the first o->progress); far z with flag 0x13; progress wraps at o->max */

typedef struct {
    f32 x, y, z, w;
} Vec_b055_01E02930;

typedef struct {
    u8 b, g, r, a;
} Src_b055_01E02930;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b055_01E02930;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b055_01E02930 p;
} Vtx_b055_01E02930;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b055_01E02930 v[2];
    u8 tail[8];
} Pk_b055_01E02930;

typedef struct {
    u64 tag;
    Pk_b055_01E02930 pk;
} Buf_b055_01E02930;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec_b055_01E02930 out[28];
} Spl_b055_01E02930;

typedef struct {
    u8 pad0[4];
    s32 flags;
    Src_b055_01E02930 col;
    u8 padC[0x1C];
    s16 max;
    s16 jitter;
    s16 progress;
} Obj_b055_01E02930;

typedef struct {
    u8 pad0[0x30];
    f32 view[1];
} Cam_b055_01E02930;

static s32 func_01E01A10_b740(s32 obj __attribute__((aligned(8))), Obj_b055_01E02930 *o, Cam_b055_01E02930 *cam __attribute__((aligned(8))), Vec_b055_01E02930 *p0,
                  Vec_b055_01E02930 *p1) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_0019A5C8();
    Spl_b055_01E02930 s;
    Vec_b055_01E02930 a[28];
    Xyz_b055_01E02930 xyz[28];
    f32 depth[29];
    Pk_b055_01E02930 pk __attribute__((aligned(8)));
    u32 mask;
    s32 i;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;

    mask = 0;
    if (o->max > 28) {
        o->max = 28;
    }
    ((Pk_b055_01E02930 *)(s32)&pk)->flags = 0x11;
    ((Pk_b055_01E02930 *)(s32)&pk)->size = 4;
    ((Pk_b055_01E02930 *)(s32)&pk)->regs = 0x4141;
    ((Pk_b055_01E02930 *)(s32)&pk)->pad4 = 0;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x48);
    ((Pk_b055_01E02930 *)(s32)&pk)->flags |= 0x400;
    pk.v[0].r = pk.v[1].r = o->col.r;
    pk.v[0].g = pk.v[1].g = o->col.g;
    pk.v[0].b = pk.v[1].b = o->col.b;
    pk.v[0].a = pk.v[1].a = o->col.a;
    pk.v[0].q = pk.v[1].q = 1.0f;
    dx = p1->x - p0->x;
    dy = p1->y - p0->y;
    dz = p1->z - p0->z;
    s.x[0] = p0->x;
    s.y[0] = p0->y;
    s.z[0] = p0->z;
    for (i = 1; i < 7; i++) {
        t = (f32)i / 7.0f;
        s.x[i] = p0->x + dx * t + 0.1f * (func_0019A5C8() % (o->jitter * 2) - o->jitter);
        s.y[i] = p0->y + dy * t + 0.1f * (func_0019A5C8() % (o->jitter * 2) - o->jitter);
        s.z[i] = p0->z + dz * t + 0.1f * (func_0019A5C8() % (o->jitter * 2) - o->jitter);
    }
    s.x[7] = p1->x;
    s.y[7] = p1->y;
    s.z[7] = p1->z;
    s.n = 8;
    func_00102550(&s);
    for (i = 0; i < 28; i++) {
        a[i].x = s.out[i].x;
        a[i].y = s.out[i].y;
        a[i].z = s.out[i].z;
        if (func_00205440(&a[i], cam->view, &xyz[i], &depth[i]) != 0 && func_00101600(&xyz[i]) != 0) {
            mask |= 1 << i;
        }
    }
    for (i = 0; i < 27; i++) {
        if (func_00104520(o->flags, 0x1A) != 0 || i <= o->progress) {
            pk.v[0].p.x = xyz[i].x;
            pk.v[1].p.x = xyz[i + 1].x;
            pk.v[0].p.y = xyz[i].y;
            pk.v[1].p.y = xyz[i + 1].y;
            if (func_00104520(mask, i) != 0 && func_00104520(mask, i + 1) != 0) {
                if (func_00104520(o->flags, 0x13) != 0) {
                    pk.v[0].p.z = pk.v[1].p.z = 0xFFFFFF;
                    func_002075F0(&pk, obj, 0);
                } else {
                    pk.v[0].p.z = xyz[i].z;
                    pk.v[1].p.z = xyz[i + 1].z;
                    func_002075F0(&pk, obj, (s32)(u32)((depth[i] + depth[i + 1]) / 2.0f));
                }
            }
        }
    }
    o->progress++;
    if (o->progress > o->max) {
        o->progress = 0;
    }
    return 0;
}

/* shape b740:01E01F30 (b740), 366 insns, 1 copy: b740 scene manager: setup (two joints, a 64-point sparkle emitter,
   eight yarn strands), then the strands drawn around the falling centre point between frames 0x2C and 0xA7 and the
   sparkles grown and respawned */

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    f32 width;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    u8 pad18[8];
    s32 w20;
    s32 w24;
    s16 max;
    s16 jitter;
    s16 progress;
    u8 pad2E[0x12];
} Yarn_b740_01E01F30;

typedef struct {
    u8 crd[0x70];
    Yarn_b740_01E01F30 yarn[8];
    Vec4f scale;
    u8 pad280[0x10];
    Vec4f joint;
    u8 pad2A0[0x40];
    Emit_b000_01E01140 emit;
    Pt_b000_01E01140 pts[64];
    Vec4f pos;
    s32 count;
    s32 frame;
    s32 id;
    s32 w75C;
    s32 w760;
    s32 jA;
    s32 jB;
    u8 pad76C[4];
} Scene_b740_01E01F30;

static s32 func_01E01F30_b740(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103290(void *, s32);
    extern s32 func_001043F0(void *, f32);
    extern void func_00104490(void *, void *, s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    Scene_b740_01E01F30 *g = (Scene_b740_01E01F30 *)arg0;
    s32 ot;
    Vec4f v;
    Vec4f t[2];
    s32 tex[4];
    s32 i;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x770);
        func_00103890(g);
        func_00103890(&g->scale);
        g->jA = func_001F5560(func_001F53A0(), 0x13, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x14, 0);
        g->count = 0x114;
        g->frame = 1;
        g->id = code;
        g->w75C = 0;
        g->w760 = 30;
        func_00103290(tex, 0);
        g->emit.texture = (void *)tex[0];
        g->emit.flags = 0x48080003;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0x40;
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
        g->emit.count = 0x40;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&v, 14.0f);
            g->pts[i].x = v.x;
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x80;
            g->pts[i].frame = func_0019A5C8() % 8;
        }
        for (i = 0; i < 8; i++) {
            g->yarn[i].tex = (void *)tex[0];
            g->yarn[i].flags = 0;
            g->yarn[i].width = 5.0f;
            g->yarn[i].h10 = 0x5A;
            g->yarn[i].h12 = 0;
            g->yarn[i].h14 = 6;
            g->yarn[i].h16 = 0x20;
            g->yarn[i].r = 0x80;
            g->yarn[i].g = 0x80;
            g->yarn[i].b = 0x80;
            g->yarn[i].a = 0x80;
            g->yarn[i].max = 0x1C;
            g->yarn[i].progress = -i;
            g->yarn[i].jitter = 0x28;
            g->yarn[i].w20 = 0;
            g->yarn[i].w24 = 0;
        }
        g->scale.x = g->scale.z = g->scale.y = 0.5f;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->jA, &v);
    func_001F5F90(func_001F5380(), &t[0]);
    func_001F53C0(1, func_001F5380(), tex);
    if (g->frame <= 0x56) {
        func_001F5620(func_001F53A0(), g->jA, &g->joint);
    } else {
        g->scale.x = g->scale.z = 1.0f;
        g->scale.y = 1.5f;
        g->emit.color.a = 0x80;
        func_001F53C0(1, func_001F5380(), &g->joint);
    }
    if (g->frame <= 0x66) {
        g->pos.x = 0.0f;
        g->pos.z = 0.0f;
        g->pos.y = 100.0f;
    }
    if (g->frame >= 0x66) {
        func_00104490(&g->pos, &t[0], g->w760);
        if (g->w760 != 0) {
            g->w760--;
        }
    }
    func_001038D0(g);
    func_001038D0(&g->scale);
    if (g->frame >= 0x2C && g->frame <= 0xA7) {
        for (i = 0; i < 8; i++) {
            t[1] = g->pos;
            t[1].x += 20.0f * func_0020B480(i * 0x2000);
            t[1].y += 20.0f * func_0020B550(i * 0x2000);
            func_01E01A10_b740(ot, (Obj_b055_01E02930 *)&g->yarn[i], (Cam_b055_01E02930 *)g, (Vec_b055_01E02930 *)&v, (Vec_b055_01E02930 *)&t[1]);
        }
    }
    func_01E00120_b740(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->scale);
    if (g->frame >= 0x104) {
        func_00103470(&g->emit.color.a, 0, 8);
    }
    for (i = 0; i < g->emit.count; i++) {
        if (g->pts[i].t >= 0) {
            g->pts[i].x *= 1.03f;
            g->pts[i].y *= 1.03f;
            g->pts[i].z *= 1.03f;
            func_00103470(&g->pts[i].a, 0, 8);
        }
        if (g->pts[i].t >= 0x10) {
            func_001043F0(&v, 14.0f);
            g->pts[i].x = v.x;
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].t = 0;
            g->pts[i].a = 0x80;
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 0x104) {
        return 2;
    }
    if (g->frame == 0x4E) {
        return 1;
    }
    if (g->frame >= 0x58 && g->frame <= 0x103) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
