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

static void func_01E00080_b556(Vtx_b000_01E00100 *v, Src_b000_01E00100 *s) {
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

static s32 func_01E00120_b556(void) {
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

static s32 func_01E00250_b556(Obj_b015_01E01620 *obj, s32 life, f32 y) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b556", func_01E00410_b556);

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

static s32 func_01E01170_b556(Ring_b001_01E01B20 *o, f32 size) {
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

static s32 func_01E01300_b556(s32 obj, Emit_b000_01E01140 *e, Cam_b000_01E01140 *cam) {
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
    func_01E00080_b556((Vtx_b000_01E00100 *)&p2, (Src_b000_01E00100 *)&e->color);
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

/* shape b007:01E017F0, 355 insns, 16 copies: draws a sprite as two crossed quads: 8 corners (from a template, sized by
   two width/height pairs) rotated by the sprite's rotation, projected per quad, depth-sorted unless flag 0x13 */

typedef struct {
    u8 b, g, r, a;
} Src_b007_01E017F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b007_01E017F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b007_01E017F0 v[4];
    u8 tail[0x20];
} Pkt_b007_01E017F0;

typedef struct {
    f32 x, y, z, w;
} Vec_b007_01E017F0;

typedef struct {
    Vec_b007_01E017F0 v[8];
} Quad8_b007_01E017F0;

typedef struct {
    void *texture;
    s32 flags;
    Src_b007_01E017F0 color;
    f32 w;
    f32 h;
    f32 w2;
    f32 h2;
    u8 pad1C[4];
    s16 u;
    s16 v;
    s16 tw;
    s16 th;
    u8 pad28[8];
    Vec_b007_01E017F0 rot;
} Spr_b007_01E017F0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b007_01E017F0;

static s32 func_01E02BF0_b556(s32 obj, Spr_b007_01E017F0 *spr, Cam_b007_01E017F0 *cam) {
    extern Quad8_b007_01E017F0 D_01E05500_b556;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00104540(void *, void *, s32);
    Quad8_b007_01E017F0 in;
    Vec_b007_01E017F0 out[8];
    f32 m[16];
    f32 depth[4];
    Pkt_b007_01E017F0 pkt;
    s32 i;

    in = D_01E05500_b556;
    in.v[0].x = -spr->w;
    in.v[0].y = spr->h;
    in.v[1].x = spr->w;
    in.v[1].y = spr->h;
    in.v[2].x = -spr->w;
    in.v[2].y = -spr->h;
    in.v[3].x = spr->w;
    in.v[3].y = -spr->h;
    in.v[4].x = -spr->h2;
    in.v[4].y = spr->w2;
    in.v[5].x = spr->h2;
    in.v[5].y = spr->w2;
    in.v[6].x = -spr->h2;
    in.v[6].y = -spr->w2;
    in.v[7].x = spr->h2;
    in.v[7].y = -spr->w2;
    func_0020C630(m, &spr->rot);
    for (i = 0; i < 8; i++) {
        func_0020CDD0(&out[i], m, &in.v[i]);
    }
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b007_01E017F0 *)(s32)&pkt)->pad = 0;
    if (func_00104520(spr->flags, 0xC) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    } else if (func_00104520(spr->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(spr->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b556((Vtx_b000_01E00100 *)&pkt, (Src_b000_01E00100 *)&spr->color);
    func_00104540(&pkt, &spr->u, 0);
    for (i = 0; i < 2; i++) {
        if (func_00205440(&out[i * 4], cam->view, &pkt.v[0].st + 1, &depth[0]) != 0) {
            spr->flags |= 0x100000;
        }
        if (func_00205440(&out[i * 4 + 1], cam->view, &pkt.v[1].st + 1, &depth[1]) != 0) {
            spr->flags |= 0x200000;
        }
        if (func_00205440(&out[i * 4 + 2], cam->view, &pkt.v[2].st + 1, &depth[2]) != 0) {
            spr->flags |= 0x400000;
        }
        if (func_00205440(&out[i * 4 + 3], cam->view, &pkt.v[3].st + 1, &depth[3]) != 0) {
            spr->flags |= 0x800000;
        }
        func_00208CB0(&pkt, (u64)0xA | ((u64)spr->u << 4) | ((u64)(spr->u + spr->tw - 1) << 14) |
                                ((u64)spr->v << 24) | ((u64)(spr->v + spr->th - 1) << 34));
        func_00208700(&pkt, spr->texture, 1);
        if (func_00104520(spr->flags, 0x14) != 0 && func_00104520(spr->flags, 0x15) != 0 &&
            func_00104520(spr->flags, 0x16) != 0 && func_00104520(spr->flags, 0x17) != 0) {
            if (func_00104520(spr->flags, 0x13) != 0) {
                pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                func_002075F0(&pkt, obj, 0);
            } else {
                func_002075F0(&pkt, obj, func_001A23B0((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        spr->flags &= 0xFF0FFFFF;
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

static s32 func_01E03180_b556(s32 ot, Disc_b540_01E00250 *d, Cam_b540_01E00250 *cam) {
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

/* OVL_WARM */

/* shape b101:01E021A0, 492 insns: draws a beam between two points: the line is cut into n pieces (at most 32),
   all points projected; each visible piece up to the moving head is drawn as four quads (above, below, right,
   left of the line) as wide as func_001018E0(width, depth). Colour from the module helper b101:01E00080.
   Both spilled params are aligned(8): that puts their homes at 0xD8/0xD0 like the original. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b101_01E021A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b101_01E021A0 xyz;
} Vtx_b101_01E021A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b101_01E021A0 v[4];
    u8 tail[0x20];
} Pkt_b101_01E021A0;

typedef struct {
    s16 u, v, w, h;
} Rect_b101_01E021A0;

typedef struct {
    void *texture;
    s32 flags;
    u8 color[4];
    f32 width;
    Rect_b101_01E021A0 rect;
    u8 pad18[0x10];
    s16 n;
    u8 pad2A[2];
    s16 head;
} Beam_b101_01E021A0;

typedef struct {
    u8 pad[0x30];
    f32 view[1];
} Cam_b101_01E021A0;

extern void b556_01E00080(void *, void *);

static s32 func_01E036E0_b556(s32 ot __attribute__((aligned(8))), Beam_b101_01E021A0 *b, Cam_b101_01E021A0 *cam __attribute__((aligned(8))), Vec4f *p1, Vec4f *p2) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern s32 func_00104540(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00208CB0(void *, u64);
    extern f32 func_001018E0(f32, f32);
    Vec4f pts[33];
    Xyz_b101_01E021A0 s[33];
    f32 depth[33];
    Pkt_b101_01E021A0 pkt;
    f32 t;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 w0;
    f32 w1;
    s32 vis;
    s32 i;
    s32 j;

    vis = 0;
    if (b->n > 32) {
        b->n = 32;
    }
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b101_01E021A0 *)(s32)&pkt)->pad = 0;
    func_00208CB0(&pkt, (u64)0xA | ((u64)b->rect.u << 4) | ((u64)(b->rect.u + b->rect.w - 1) << 14) |
                            ((u64)b->rect.v << 24) | ((u64)(b->rect.v + b->rect.h - 1) << 34));
    func_00208700(&pkt, b->texture, 1);
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    b556_01E00080(&pkt, b->color);
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    dz = p2->z - p1->z;
    for (i = 0; i < b->n + 1; i++) {
        if (i == b->n) {
            pts[b->n] = *p2;
        } else {
            t = (f32)i / b->n;
            pts[i].x = p1->x + dx * t;
            pts[i].y = p1->y + dy * t;
            pts[i].z = p1->z + dz * t;
        }
        if (func_00205440(&pts[i], cam->view, &s[i], &depth[i]) != 0) {
            vis |= 1 << i;
        }
    }
    for (i = 0; i < b->n; i++) {
        if (i <= b->head) {
            func_00104540(&pkt, &b->rect, 0);
            if (func_00104520(vis, i) != 0 && func_00104520(vis, i + 1) != 0) {
                w0 = func_001018E0(b->width, depth[i]);
                w1 = func_001018E0(b->width, depth[i + 1]);
                for (j = 0; j < 4; j++) {
                    if (j < 2) {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[i].x;
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[i + 1].x;
                        if (j == 0) {
                            pkt.v[0].xyz.y = w0 + s[i].y;
                            pkt.v[1].xyz.y = w1 + s[i + 1].y;
                            pkt.v[2].xyz.y = s[i].y;
                            pkt.v[3].xyz.y = s[i + 1].y;
                        }
                        if (j == 1) {
                            pkt.v[0].xyz.y = s[i].y - w0;
                            pkt.v[1].xyz.y = s[i + 1].y - w1;
                            pkt.v[2].xyz.y = s[i].y;
                            pkt.v[3].xyz.y = s[i + 1].y;
                        }
                    } else {
                        pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[i].y;
                        pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[i + 1].y;
                        if (j == 2) {
                            pkt.v[0].xyz.x = w0 + s[i].x;
                            pkt.v[1].xyz.x = w1 + s[i + 1].x;
                            pkt.v[2].xyz.x = s[i].x;
                            pkt.v[3].xyz.x = s[i + 1].x;
                        }
                        if (j == 3) {
                            pkt.v[0].xyz.x = s[i].x - w0;
                            pkt.v[1].xyz.x = s[i + 1].x - w1;
                            pkt.v[2].xyz.x = s[i].x;
                            pkt.v[3].xyz.x = s[i + 1].x;
                        }
                    }
                    if (func_00101600(&pkt.v[0].xyz) != 0) {
                        b->flags |= 0x100000;
                    }
                    if (func_00101600(&pkt.v[1].xyz) != 0) {
                        b->flags |= 0x200000;
                    }
                    if (func_00104520(b->flags, 0x14) != 0 && func_00104520(b->flags, 0x15) != 0) {
                        pkt.v[0].xyz.z = pkt.v[2].xyz.z = s[i].z;
                        pkt.v[1].xyz.z = pkt.v[3].xyz.z = s[i + 1].z;
                        func_002075F0(&pkt, ot, (u32)((depth[i] + depth[i + 1]) / 2.0f));
                    }
                    b->flags &= 0xFFCFFFFF;
                }
            }
        }
    }
    b->head++;
    if (b->head >= b->n) {
        if (func_00104520(b->flags, 0x1A) != 0) {
            b->head = b->n;
        } else {
            b->head = 0;
        }
    }
    return 0;
}

/* shape b025:01E03CF0, 103 insns, 9 copies: set up a particle object: 6 corner offsets from a local table sized
   by the object's width/height, then each particle gets a random start (-rand() % 0x2000, rand() % 0x10000) */

typedef struct V4_b025_01E03CF0 {
    f32 x, y, z, w;
} V4_b025_01E03CF0;

typedef struct Part_b025_01E03CF0 {
    s32 a;
    s32 b;
    s32 c;
    u8 col;
    u8 padD;
    s16 age;
} Part_b025_01E03CF0;

typedef struct Obj_b025_01E03CF0 {
    s32 kind;
    u8 pad4[7];
    u8 col;
    u8 padC[0x14];
    V4_b025_01E03CF0 v[6];
    Part_b025_01E03CF0 *parts;
    f32 h;
    f32 w;
    u8 pad8C[0xE];
    s16 count;
} Obj_b025_01E03CF0;

typedef struct W_tbl_func_01E03E90_b556 {
    V4_b025_01E03CF0 v[6];
} W_tbl_func_01E03E90_b556;

static s32 func_01E03E90_b556(Obj_b025_01E03CF0 *o, s32 kind) {
    extern s32 func_0019A5C8();
    extern W_tbl_func_01E03E90_b556 D_01E05580_b556;
    W_tbl_func_01E03E90_b556 tbl_w = D_01E05580_b556;
    s32 i;

    tbl_w.v[0].x = -o->w / 2.0f;
    tbl_w.v[0].y = o->h;
    tbl_w.v[1].x = -o->w / 2.0f;
    tbl_w.v[2].y = o->h;
    tbl_w.v[4].x = o->w / 2.0f;
    tbl_w.v[4].y = o->h;
    tbl_w.v[5].x = o->w / 2.0f;
    o->kind = kind;
    for (i = 0; i < 6; i++) {
        o->v[i].x = tbl_w.v[i].x;
        o->v[i].y = tbl_w.v[i].y;
        o->v[i].z = tbl_w.v[i].z;
    }
    for (i = 0; i < o->count; i++) {
        o->parts[i].a = -func_0019A5C8() % 0x2000;
        o->parts[i].b = func_0019A5C8() % 0x10000;
        o->parts[i].c = 0;
        o->parts[i].age = 0;
        o->parts[i].col = o->col;
    }
    return 0;
}

/* shape b025:01E03E90 (LkSortShockWall), 450 insns, 9 copies: draws a textured shock wall: per segment a rotated,
   offset 6-point strip drawn as two quads, alpha fading out, the segment count growing each frame */

typedef struct {
    u16 s : 14;
    u16 s_pad : 2;
    u16 t : 14;
    u16 t_pad : 2;
    u32 pad;
} Uv_b025_01E03E90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b025_01E03E90 st;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b025_01E03E90;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b025_01E03E90 v[4];
    u8 tail[0x20];
} Pkt_b025_01E03E90;

typedef struct {
    s32 x, y, z;
    u8 a;
    u8 pad;
    s16 t;
} Seg_b025_01E03E90;

typedef struct {
    s32 x, y, z, w;
} Pos_b025_01E03E90;

typedef struct {
    void *texture;
    s32 flags;
    Src_b000_01E00100 col;
    f32 r;
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f q[6];
    Seg_b025_01E03E90 *seg;
    u8 pad84[8];
    f32 dy;
    f32 dx;
    s32 arc;
    s16 frame;
    s16 max;
    s16 n;
    s16 grow;
} Wall_b025_01E03E90;

typedef struct {
    u8 pad[0x30];
    f32 view[16];
} Cam_b025_01E03E90;

/* n: a 4th parameter the caller never passes, reused as the segment count (its spill slot needs it) */

static s32 func_01E04030_b556(s32 ot, Wall_b025_01E03E90 *o, Cam_b025_01E03E90 *cam __attribute__((aligned(16))),
                              s32 n) {
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f sc;
    Pos_b025_01E03E90 pos;
    f32 m[16];
    Vec4f pts[6];
    f32 d[4];
    Pkt_b025_01E03E90 pkt;
    s32 step;
    s32 start;
    s32 k;
    s32 i;
    s16 tu;

    n = o->n;
    if (o->max < n) {
        n = o->n = o->max;
    }
    step = -(o->arc / o->max);
    start = -(0x8000 - o->arc) >> 1;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->count = 0x34;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->tag = 0xC;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
    ((Pkt_b025_01E03E90 *)(s32)&pkt)->pad = 0;
    func_00208CB0(&pkt, ((u64)o->v << 24) | (((u64)(o->w - 1) << 4) | 0xB | ((u64)o->u << 14)) |
                            ((u64)(o->v + o->h - 1) << 34));
    func_00208700(&pkt, o->texture, 0);
    if (func_00104520(o->flags, 0xB) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x88);
    } else if (func_00104520(o->flags, 0xA) != 0) {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(&pkt, ((u64)0x80 << 32) | 0x48);
    }
    func_01E00080_b556((Vtx_b000_01E00100 *)&pkt, &o->col);
    for (k = 0; k < n; k++) {
        sc.z = o->r * func_0020B550(start + step * k);
        sc.x = o->r * func_0020B480(start + step * k);
        sc.y = 0.0f;
        pos.x = o->seg[k].x;
        pos.y = o->seg[k].y;
        pos.z = o->seg[k].z;
        func_0020C940(m, 0, &pos, &sc);
        func_0020BCF0((s32)m, (s32)cam->view);
        for (i = 0; i < 6; i++) {
            pts[i] = o->q[i];
            if (i != 2 && i != 3) {
                pts[i].x = o->q[i].x + o->dx * o->seg[k].t;
            }
            if (i % 2 == 0) {
                pts[i].y = o->q[i].y + o->dy * o->seg[k].t;
            }
        }
        for (i = 0; i < 2; i++) {
            if (i != 0) {
                pkt.v[0].a = o->seg[k].a;
                pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = 0;
            } else {
                pkt.v[0].a = pkt.v[1].a = pkt.v[3].a = 0;
                pkt.v[2].a = o->seg[k].a;
            }
            tu = o->seg[k].t % o->w + (o->w >> 1) * i;
            ((Pkt_b025_01E03E90 *)(s32)&pkt)->count |= 0x800;
            pkt.v[0].st.s = tu * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[0].st)->t = o->v * 16;
            pkt.v[1].st.s = tu * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[1].st)->t = (o->v + o->h - 1) * 16;
            pkt.v[2].st.s = (tu + (o->w >> 1)) * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[2].st)->t = o->v * 16;
            pkt.v[3].st.s = (tu + (o->w >> 1)) * 16;
            ((Uv_b025_01E03E90 *)(s32)&pkt.v[3].st)->t = (o->v + o->h - 1) * 16;
            if (func_00205630(&pts[i * 2], 0x70000000, m, &pkt, d) != 0) {
                if (func_00104520(o->flags, 0x13) != 0) {
                    pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
                    func_002075F0(&pkt, ot, 0);
                } else if (func_00104520(o->flags, 0x12) != 0) {
                    func_002075F0(&pkt, ot, 0xFFFFFF);
                } else {
                    func_002075F0(&pkt, ot, func_001A23B0(d[0]));
                }
            }
        }
        if (func_00104520(o->flags, 0x1E) == 0) {
            o->seg[k].t++;
        }
    }
    o->frame++;
    o->n += o->grow;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b556", func_01E04740_b556);
