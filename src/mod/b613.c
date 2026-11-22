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

static void func_01E00080_b613(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b613(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b613((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E01A10_b613(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

/* shape b489:01E00240 (LkPrim_SortLineParticle), 853 insns, 55 copies: each live particle drawn as a camera-facing
   line quad from its position back along its direction (or straight down), texture-animated */

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b489_01E00240;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b489_01E00240;

typedef struct {
    UV_b489_01E00240 uv;
    Xyz_b489_01E00240 xyz;
} Vtx_b489_01E00240;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b489_01E00240 v[4];
    u8 tail[0x20];
} Pkt_b489_01E00240;

typedef struct {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 age;
} Part_b489_01E00240;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Part_b489_01E00240 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    u8 pad28[4];
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00240;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b489_01E00240;

#define UV_b489_01E00240(k) ((UV_b489_01E00240 *)(s32)&pkt.v[k].uv)

/* ot, cam aligned: their spill slot, needed for the match */
static s32 func_01E01BD0_b613(s32 ot __attribute__((aligned(8))), Emit_b489_01E00240 *e, Cam_b489_01E00240 *cam __attribute__((aligned(16)))) {
    extern s32 func_00104520(s32, s32);
    extern void func_002086D0(void *, u64);
    extern void func_0020D070(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001A6970(f32);
    extern f32 func_001A6C60(f32);
    extern void func_00208CB0(void *, u64);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec4f t;
    Xyz_b489_01E00240 q[2];
    Pkt_b489_01E00240 pkt __attribute__((aligned(8)));
    f32 dep[2];
    s32 i;
    f32 w;
    f32 dx;
    f32 dy;

    ((Pkt_b489_01E00240 *)(s32)&pkt)->count = 0x24;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->tag = 9;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
    ((Pkt_b489_01E00240 *)(s32)&pkt)->pad = 0;
    if (func_00104520(e->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(e->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(e->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    pkt.r = e->r;
    pkt.g = e->g;
    pkt.b = e->b;
    pkt.a = e->a;
    pkt.q = 1.0f;
    if (func_00104520(e->flags, 3) != 0) {
        ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
        UV_b489_01E00240(0)->u = e->u << 4;
        UV_b489_01E00240(0)->v = e->v << 4;
        UV_b489_01E00240(1)->u = e->u << 4;
        UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
        UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(2)->v = e->v << 4;
        UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
        UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
    }
    for (i = 0; i < e->count; i++) {
        if (e->parts[i].age >= 0) {
            if (e->parts[i].a < e->a) {
                pkt.a = e->parts[i].a;
            } else {
                pkt.a = e->a;
            }
            if (func_00104520(e->flags, 3) == 0) {
                if (func_00104520(e->flags, 1) != 0) {
                    e->u = e->u0 + e->w * (e->parts[i].frame % (e->tw / e->w));
                    e->v = e->v0 + e->h * (e->parts[i].frame / (e->tw / e->w));
                } else {
                    e->u = e->u0 + e->w * (e->parts[i].frame / (e->th / e->h));
                    e->v = e->v0 + e->h * (e->parts[i].frame % (e->th / e->h));
                }
                ((Pkt_b489_01E00240 *)(s32)&pkt)->count |= 0x800;
                UV_b489_01E00240(0)->u = e->u << 4;
                UV_b489_01E00240(0)->v = e->v << 4;
                UV_b489_01E00240(1)->u = e->u << 4;
                UV_b489_01E00240(1)->v = (e->v + e->h - 1) << 4;
                UV_b489_01E00240(2)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(2)->v = e->v << 4;
                UV_b489_01E00240(3)->u = (e->u + e->w - 1) << 4;
                UV_b489_01E00240(3)->v = (e->v + e->h - 1) << 4;
            }
            if (func_00104520(e->flags, 0x1E) != 0) {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y - e->len;
                t.z = e->parts[i].z;
            } else {
                t.x = e->parts[i].x;
                t.y = e->parts[i].y;
                t.z = e->parts[i].z;
                func_0020D070(&t);
                t.x *= -e->len;
                t.y *= -e->len;
                t.z *= -e->len;
                t.x += e->parts[i].x;
                t.y += e->parts[i].y;
                t.z += e->parts[i].z;
            }
            if (func_00205440(&e->parts[i], cam->view, &q[0], &dep[0]) != 0 && func_00101600(&q[0]) != 0) {
                e->flags |= 0x100000;
            }
            if (func_00205440(&t, cam->view, &q[1], &dep[1]) != 0 && func_00101600(&q[1]) != 0) {
                e->flags |= 0x200000;
            }
            if (func_00104520(e->flags, 0x14) != 0 && func_00104520(e->flags, 0x15) != 0) {
                dx = func_001A6970(q[0].x - q[1].x);
                dy = func_001A6970(q[0].y - q[1].y);
                w = func_001A6C60(dx * dx + dy * dy);
                w = w * e->width / e->len;
                if (dx > dy) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = q[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = q[1].x;
                    pkt.v[0].xyz.y = (u32)(q[0].y - w);
                    pkt.v[1].xyz.y = (u32)(q[1].y - w);
                    pkt.v[2].xyz.y = (u32)(q[0].y + w);
                    pkt.v[3].xyz.y = (u32)(q[1].y + w);
                } else {
                    pkt.v[0].xyz.x = (u32)(q[0].x - w);
                    pkt.v[1].xyz.x = (u32)(q[1].x - w);
                    pkt.v[2].xyz.x = (u32)(q[0].x + w);
                    pkt.v[3].xyz.x = (u32)(q[1].x + w);
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = q[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = q[1].y;
                }
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = q[0].z;
                if (func_00104520(e->flags, 0) != 0) {
                    func_00208CB0(&pkt, 0xA | ((s64)e->u << 4) | ((s64)(e->u + e->w - 1) << 14) |
                                            ((s64)e->v << 24) | ((s64)(e->v + e->h - 1) << 34));
                }
                func_00208700(&pkt, e->texture, 1);
                if (func_00104520(e->flags, 0x13) != 0) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else {
                    func_002075F0(&pkt, ot, (u32)((dep[0] + dep[1]) / 2.0f));
                }
            }
            e->flags &= 0xFFCFFFFF;
        }
        if (func_00104520(e->flags, 3) == 0) {
            e->parts[i].age++;
            if (e->parts[i].age % e->rate == 0) {
                e->parts[i].frame++;
                if (e->nframes == e->parts[i].frame) {
                    e->parts[i].frame = 0;
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

static s32 func_01E02930_b613(s32 obj __attribute__((aligned(8))), Obj_b055_01E02930 *o, Cam_b055_01E02930 *cam __attribute__((aligned(8))), Vec_b055_01E02930 *p0,
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

/* shape b055:01E02E50, 99 insns: set up a particle ring: nring points evenly spaced over half a turn at radius r,
   then npts particles at random positions (0..0xFFFF each axis), alpha from the emitter and a random negative
   start age (0..maxt-1) */

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} Pt_b055_01E02E50;

typedef struct {
    f32 x, y, z, w;
} Ring_b055_01E02E50;

typedef struct {
    u8 pad0[0xB];
    u8 a;
    f32 r;
    u8 pad10[0x10];
    Pt_b055_01E02E50 *pts;
    Ring_b055_01E02E50 *ring;
    s16 nring;
    s16 npts;
    u8 pad2C[4];
    s16 maxt;
} Em_b055_01E02E50;

static s32 func_01E02E50_b613(Em_b055_01E02E50 *o) {
    s32 i;
    s32 step;
    s32 a;

    step = 0x8000 / o->nring;
    for (i = 0, a = 0; i < o->nring; i++) {
        o->ring[i].y = o->r * func_0020B480(a);
        o->ring[i].x = o->r * func_0020B550(a);
        a += step;
    }
    for (i = 0; i < o->npts; i++) {
        o->pts[i].x = func_0019A5C8() % 0x10000;
        o->pts[i].y = func_0019A5C8() % 0x10000;
        o->pts[i].z = func_0019A5C8() % 0x10000;
        o->pts[i].age = -(func_0019A5C8() % o->maxt);
        o->pts[i].a = o->a;
    }
    return 0;
}

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b055_01E02FE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b055_01E02FE0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b055_01E02FE0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b055_01E02FE0 c;
    Xyz_b055_01E02FE0 v[2];
} Pkt_b055_01E02FE0;

typedef struct {
    s32 x, y, z;
    s16 pad;
    s16 t;
} Ent_b055_01E02FE0;

typedef struct {
    u8 pad00[4];
    s32 w4;
    u8 r, g, b, a;
    u8 pad0C[0x14];
    Ent_b055_01E02FE0 *list;
    Vec_b055_01E02FE0 *pts;
    s16 n;
    s16 count;
    u8 pad2C[6];
    s16 step;
} Obj_b055_01E02FE0;

static inline void tag_b055_01E02FE0(Pkt_b055_01E02FE0 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E02FE0_b613(s32 tgt __attribute__((aligned(8))), Obj_b055_01E02FE0 *o, u8 *cam __attribute__((aligned(8)))) {
    extern s32 func_00104520(s32, s32);
    extern void func_0020C630(void *, void *);
    extern void func_0020BCF0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    s32 mask;
    f32 m[16];
    s32 k;
    s32 v[4];
    s32 target;
    Xyz_b055_01E02FE0 xy[32];
    f32 dep[32];
    s32 i;
    f32 depth;
    Pkt_b055_01E02FE0 pkt;

    target = tgt;
    tag_b055_01E02FE0((Pkt_b055_01E02FE0 *)(u32)&pkt, 1, 3, 0x441);
    mask = 0;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    ((Pkt_b055_01E02FE0 *)(u32)&pkt)->count |= 0x400;
    pkt.c.r = o->b;
    pkt.c.g = o->g;
    pkt.c.b = o->r;
    pkt.c.a = o->a;
    pkt.c.q = 1.0f;
    for (k = 0; k < o->count; k++) {
        if (o->list[k].t < 0) {
            o->list[k].t++;
            continue;
        }
        v[0] = o->list[k].x;
        v[1] = o->list[k].y;
        v[2] = o->list[k].z;
        func_0020C630(m, v);
        func_0020BCF0(m, cam + 0x30);
        for (i = 0; i < o->n; i++) {
            if (func_00205440(&o->pts[i], m, &xy[i], &dep[i]) != 0) {
                mask |= 1 << i;
            }
        }
        for (i = 0; i < o->n - 1; i++) {
            if (func_00104520(o->w4, 0x1A) == 0 && i > o->list[k].t) {
                continue;
            }
            if (func_00104520(mask, i) != 0 && func_00104520(mask, i + 1) != 0) {
                pkt.v[0].x = xy[i].x;
                pkt.v[1].x = xy[i + 1].x;
                pkt.v[0].y = xy[i].y;
                pkt.v[1].y = xy[i + 1].y;
                pkt.v[0].z = xy[i].z;
                pkt.v[1].z = xy[i + 1].z;
                depth = (dep[i] + dep[i + 1]) / 2.0f;
                func_002075F0(&pkt, target, (u32)depth);
            }
        }
        o->list[k].t += o->step;
        mask = 0;
        if (o->list[k].t >= o->n) {
            if (func_00104520(o->w4, 0x1A) != 0) {
                o->list[k].t = o->n;
            } else {
                o->list[k].t = 0;
                o->list[k].x = func_0019A5C8() % 0x10000;
                o->list[k].y = func_0019A5C8() % 0x10000;
                o->list[k].z = func_0019A5C8() % 0x10000;
            }
        }
    }
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

static s32 func_01E03400_b613(Ring_b013_01E029E0 *o, Vec_b013_01E029E0 *center) {
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

static s32 func_01E03600_b613(s32 obj, Em_b013_01E02BE0 *o, Cam_b013_01E02BE0 *cam) {
    extern Quad_b013_01E02BE0 D_01E04F00_b613;
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

    in = D_01E04F00_b613;
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

/* shape b613:01E04010 (b613), 936 insns, 1 copy: b613 scene manager (LkEff_SetCocoon family): code >= 0 sets up an
   exhaust ring emitter, a 32-sprite burst, a 128-line spray, 8 yarn bolts and a 2048-point cocoon; then follows
   joints 0x47/0x26, adds exhaust rings at fixed ticks, draws the exhaust until 0xCA, the burst from 0xD2, yarn and
   spray in 0xCB..0x167, the cocoon from 0xF2; returns 2 / 1 / 6 at 0x18A / 0xC8 / 0xD2..0x189, 8 when the timer runs
   out */

typedef struct Rot_b613_01E04010 {
    s32 x, y, z, w;
} Rot_b613_01E04010;

typedef struct Crd_b613_01E04010 {
    Vec4f scale;
    Rot_b613_01E04010 rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b613_01E04010;

typedef struct Yarn_b613_01E04010 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    s32 f20;
    s32 f24;
    s16 max;
    s16 jitter;
    s16 progress;
    u8 pad2E[0x12];
} Yarn_b613_01E04010;

typedef struct Cocoon_b613_01E04010 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    f32 r0;
    s16 u, v, w, h;
    u8 pad18[8];
    void *pts;
    void *ring;
    s16 nring;
    s16 npts;
    s16 f2C;
    s16 f2E;
    s16 maxt;
    s16 step;
    u8 pad34[0xC];
} Cocoon_b613_01E04010;

typedef struct CPt_b613_01E04010 {
    s32 x, y, z;
    u8 a;
    u8 padD;
    s16 age;
} CPt_b613_01E04010;

typedef struct Pt_b613_01E04010 {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 t;
} Pt_b613_01E04010;

typedef struct Emit_b613_01E04010 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    f32 size;
    u8 pad10[0x10];
    Vec4f rot;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Pt_b613_01E04010 *pts;
    s32 rots;
    s32 f48;
    f32 radius;
    f32 grow;
    f32 amp;
    s16 freq;
    s16 count;
    s16 nframes;
    s16 rate;
} Emit_b613_01E04010;

typedef struct Line_b613_01E04010 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    Pt_b613_01E04010 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    f32 radius;
    s16 count;
    u8 nframes;
    u8 rate;
} Line_b613_01E04010;

typedef struct EPt_b613_01E04010 {
    f32 x, y, z;
    u8 c;
    u8 frame;
    s16 age;
} EPt_b613_01E04010;

typedef struct Exh_b613_01E04010 {
    s32 texture;
    u8 b, g, r, a;
    s32 flags;
    EPt_b613_01E04010 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    Vec4f rot;
    f32 size;
    f32 grow;
    f32 radius;
    u8 pad3C[6];
    s16 h42;
    s16 h44;
    s16 rings;
    s16 used;
    s16 count;
    s16 frames;
    s16 rate;
} Exh_b613_01E04010;

typedef struct Scene_b613_01E04010 {
    Crd_b613_01E04010 cam0;
    Yarn_b613_01E04010 yarn[8];
    Exh_b613_01E04010 exh;
    EPt_b613_01E04010 eparts[0x120];
    Crd_b613_01E04010 cam;
    Cocoon_b613_01E04010 cocoon;
    Vec4f ring[16];
    CPt_b613_01E04010 pts[0x800];
    Emit_b613_01E04010 emit;
    Pt_b613_01E04010 parts[32];
    Crd_b613_01E04010 crd;
    Line_b613_01E04010 line;
    Pt_b613_01E04010 lparts[128];
    s32 timer;
    s32 t;
    s32 code;
    s32 f2C;
    s32 jA;
    s32 jB;
    s32 jC;
    s32 jD;
    u8 fade;
    u8 pad[0xF];
} Scene_b613_01E04010;

static s32 func_01E04010_b613(s32 arg0, s32 code) {
    Scene_b613_01E04010 *g = (Scene_b613_01E04010 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103290(s32 *, s32);
    extern void func_00103260(s32 *, s32);
    extern void func_001F6D00(s32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_001043F0(void *, f32);
    extern void func_001F72C0(s32, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    s32 ot;
    Vec4f v;
    Vec4f p0;
    Vec4f w[3];
    s32 i;
    s32 j;
    s32 n;
    s32 a;
    f32 d;

    ot = func_00207500();
    if (code >= 0) {
        s32 tx[4];

        func_00195108(g, 0xA1A0);
        func_00103890(&g->cam0);
        func_00103890(&g->cam);
        func_00103890(&g->crd);
        g->jA = func_001F5560(func_001F53A0(), 0x47, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x26, 0);
        g->jC = func_001F5560(func_001F53A0(), 0x11, 0);
        g->jD = func_001F5560(func_001F53A0(), 0x20, 0);
        g->timer = 0x19A;
        g->t = 1;
        g->code = code;
        g->f2C = 0;
        g->fade = 0x80;
        func_00103260(tx, 0xF);
        g->exh.texture = tx[0];
        g->exh.r = 0x80;
        g->exh.g = 0x80;
        g->exh.b = 0x80;
        g->exh.a = 0x30;
        g->exh.flags = 0x19003;
        g->exh.parts = g->eparts;
        g->exh.u = 0x80;
        g->exh.v = 0xC0;
        g->exh.w = 0x20;
        g->exh.h = 0x20;
        g->exh.u0 = 0x80;
        g->exh.v0 = 0xC0;
        g->exh.tw = 0x80;
        g->exh.th = 0x100;
        g->exh.rot.x = 0.0f;
        g->exh.rot.y = 0.3f;
        g->exh.rot.z = 0.0f;
        g->exh.size = 3.0f;
        g->exh.grow = 0.2f;
        g->exh.radius = 3.3f;
        g->exh.h42 = 0;
        g->exh.h44 = 0x18;
        g->exh.rings = 0x24;
        g->exh.used = 0;
        g->exh.count = 8;
        g->exh.frames = 8;
        g->exh.rate = 0;
        func_00103290(tx, 0);
        g->emit.texture = tx[0];
        g->emit.flags = 0x48001003;
        g->emit.r = 0x80;
        g->emit.g = 0x80;
        g->emit.b = 0x80;
        g->emit.a = 0;
        g->emit.size = 20.0f;
        g->emit.rot.x = 0.0f;
        g->emit.rot.y = 0.0f;
        g->emit.rot.z = 0.0f;
        g->emit.u = 0;
        g->emit.v = 0;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.u0 = 0;
        g->emit.v0 = 0;
        g->emit.tw = 0x80;
        g->emit.th = 0x40;
        g->emit.pts = g->parts;
        g->emit.rots = 0;
        g->emit.f48 = 0;
        g->emit.radius = 15.0f;
        g->emit.grow = 10.0f;
        g->emit.count = 0x20;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&p0, 14.0f);
            g->parts[i].x = p0.x;
            g->parts[i].y = p0.y;
            g->parts[i].z = p0.z;
            g->parts[i].t = -(func_0019A5C8() % 12);
            g->parts[i].a = 0x80;
            g->parts[i].frame = func_0019A5C8() % 8;
        }
        g->line.texture = tx[0];
        g->line.flags = 0x20000003;
        g->line.r = 0x80;
        g->line.g = 0x80;
        g->line.b = 0x80;
        g->line.a = 0xFF;
        g->line.width = 0.5f;
        g->line.len = 5.0f;
        g->line.u = 0x20;
        g->line.v = 0x20;
        g->line.w = 0x20;
        g->line.h = 0x20;
        g->line.u0 = 0x20;
        g->line.v0 = 0x20;
        g->line.tw = 0x80;
        g->line.th = 0x40;
        g->line.parts = g->lparts;
        g->line.radius = 5.0f;
        g->line.count = 0x80;
        g->line.nframes = 1;
        g->line.rate = 0;
        func_01E01A10_b613((Obj_b015_01E01620 *)&g->line, 12, 4.0f);
        for (i = 0; i < 8; i++) {
            g->yarn[i].texture = tx[0];
            g->yarn[i].flags = 0;
            g->yarn[i].size = 5.0f;
            g->yarn[i].u = 0x5A;
            g->yarn[i].v = 0;
            g->yarn[i].w = 6;
            g->yarn[i].h = 0x20;
            g->yarn[i].r = 0x80;
            g->yarn[i].g = 0x80;
            g->yarn[i].b = 0x80;
            g->yarn[i].a = 0x80;
            g->yarn[i].max = 0x1C;
            g->yarn[i].progress = -i;
            g->yarn[i].jitter = 0x28;
            g->yarn[i].f20 = 0;
            g->yarn[i].f24 = 0;
        }
        g->cocoon.texture = tx[0];
        g->cocoon.flags = 0x4000000;
        g->cocoon.r = 0x80;
        g->cocoon.g = 0x80;
        g->cocoon.b = 0x80;
        g->cocoon.a = 0x10;
        g->cocoon.r0 = 18.0f;
        g->cocoon.u = 0x5A;
        g->cocoon.v = 0;
        g->cocoon.w = 6;
        g->cocoon.h = 0x20;
        g->cocoon.pts = g->pts;
        g->cocoon.ring = g->ring;
        g->cocoon.nring = 4;
        g->cocoon.npts = 0x800;
        g->cocoon.f2C = 0x28;
        g->cocoon.f2E = 0;
        g->cocoon.maxt = 0xA0;
        g->cocoon.step = 3;
        func_01E02E50_b613((Em_b055_01E02E50 *)&g->cocoon);
        g->cam.scale.y = 1.5f;
        return 0;
    }
    func_001F5620(func_001F53A0(), g->jA, &p0);
    func_001F5620(func_001F53A0(), g->jB, &w[0]);
    func_001F53C0(1, func_001F5380(), &w[2]);
    func_001F53C0(1, func_001F5380(), &g->cam.pos);
    func_00103DB0(&p0, &w[0], &g->crd.rot);
    g->crd.pos = p0;
    g->cam.rot.z = 0x1000;
    if (g->t == 0x49 || g->t == 0x5B || g->t == 0x73) {
        func_001F5620(func_001F53A0(), g->jD, &v);
        func_01E03400_b613((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&v);
    }
    if (g->t == 0x40 || g->t == 0x52 || g->t == 0x64 || g->t == 0x74) {
        func_001F5620(func_001F53A0(), g->jC, &v);
        func_01E03400_b613((Ring_b013_01E029E0 *)&g->exh, (Vec_b013_01E029E0 *)&v);
    }
    func_001038D0(&g->cam0);
    func_001038D0(&g->cam);
    func_001038D0(&g->crd);
    if (g->t <= 0x189) {
        func_00103470(&g->fade, 0x20, 4);
    } else {
        func_001032C0(&g->fade, 0x80, 4);
    }
    func_001F6D00(g->fade);
    if (g->t == 0x12C) {
        func_001F72C0(func_001F5380(), 1);
    }
    if (g->t == 0x189) {
        func_001F72C0(func_001F5380(), 0);
    }
    if (g->t <= 0xCA) {
        func_01E03600_b613(ot, (Em_b013_01E02BE0 *)&g->exh, (Cam_b013_01E02BE0 *)g);
        for (i = 0; i < g->exh.used; i++) {
            for (j = 0; j < g->exh.count; j++) {
                func_00103470(&g->eparts[j + i * g->exh.count].c, 0, 3);
            }
        }
    }
    if (g->t >= 0xD2) {
        func_01E00120_b613(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->cam);
        if (g->t >= 0x18A) {
            func_00103470(&g->emit.a, 0, 8);
        } else {
            func_001032C0(&g->emit.a, 0x80, 2);
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->parts[i].t >= 0) {
                g->parts[i].x *= 1.03f;
                g->parts[i].y *= 1.03f;
                g->parts[i].z *= 1.03f;
                func_00103470(&g->parts[i].a, 0, 8);
            }
            if (g->parts[i].t >= 0x10) {
                func_001043F0(&p0, 14.0f);
                g->parts[i].x = p0.x;
                g->parts[i].y = p0.y;
                g->parts[i].z = p0.z;
                g->parts[i].t = 0;
                g->parts[i].a = 0x80;
            }
        }
    }
    if (g->t >= 0xCB && g->t < 0x168) {
        for (i = 0; i < 8; i++) {
            w[1] = w[2];
            w[1].x += 20.0f * func_0020B480(i * 0x2000);
            w[1].y += 20.0f * func_0020B550(i * 0x2000);
            func_01E02930_b613(ot, (Obj_b055_01E02930 *)&g->yarn[i], (Cam_b055_01E02930 *)g, (Vec_b055_01E02930 *)&w[0],
                               (Vec_b055_01E02930 *)&w[1]);
        }
    }
    if (g->t >= 0xCB && g->t < 0x168) {
        func_01E01BD0_b613(ot, (Emit_b489_01E00240 *)&g->line, (Cam_b489_01E00240 *)&g->crd);
        for (i = 0; i < g->line.count; i++) {
            if (g->lparts[i].t >= 0) {
                g->lparts[i].x *= 1.3f;
                g->lparts[i].y *= 1.3f;
                g->lparts[i].z *= 1.3f;
                if (g->lparts[i].y > 50.0f) {
                    n = (s32)(10.0f * g->line.radius);
                    a = func_0019A5C8() % 0x10000;
                    d = 0.1f * (func_0019A5C8() % n);
                    g->lparts[i].y = 4.0f;
                    g->lparts[i].z = d * func_0020B480(a);
                    g->lparts[i].x = d * func_0020B550(a);
                    g->lparts[i].t = -(func_0019A5C8() % 12);
                }
            }
        }
    }
    if (g->t >= 0xF2) {
        func_01E02FE0_b613(ot, (Obj_b055_01E02FE0 *)&g->cocoon, (u8 *)&g->cam);
        if (g->t >= 0x17A) {
            func_00103470(&g->cocoon.a, 0, 1);
        }
    }
    g->t++;
    g->timer--;
    if (g->t == 0x18A) {
        return 2;
    }
    if (g->t == 0xC8) {
        return 1;
    }
    if (g->t >= 0xD2 && g->t < 0x18A) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
