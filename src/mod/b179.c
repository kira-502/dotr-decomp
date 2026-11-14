#include "common.h"

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E00080, 237 insns, 27 copies: b010:01E00080 (move an emitter, set its level from the blend mode) built at -O1,p: every field read again, nothing CSEd */

typedef struct Obj_b002_01E00080 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 pad5[0xB];
    u8 f10[0x10];
    Vec4f pos;
    u8 pad30[8];
    f32 level;
    u8 pad3C[4];
    Vec4f vel;
    f32 base;
} Obj_b002_01E00080;

#pragma optimization_level 1

static void func_01E00080_b179(Obj_b002_01E00080 *arg0) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    Obj_b002_01E00080 *o;
    u8 d;
    u8 e;
    s32 on;
    f32 k;

    o = arg0;
    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    d = o->b0 & o->b3;
    e = o->b2 - o->b0;
    if (o->b3 == 0xFF) {
        k = o->base / o->b2;
    } else {
        k = o->base / (o->b3 + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (o->b3 == 0xFF) {
            if (e < o->b2 >> 1) {
                o->level = 2.0f * k * e;
            } else {
                o->level = 2.0f * k * o->b0;
            }
        } else {
            if (d < o->b3 >> 1) {
                o->level = 2.0f * k * (o->b3 - d);
            } else {
                o->level = 2.0f * k * d;
            }
        }
        break;
    case 4:
        o->level = o->base;
        if (o->b0 & 1) {
            o->level *= 0.5f;
        }
        break;
    case 8:
        if (o->b0 & 1) {
            on = 0;
        }
    default:
        o->level = o->base;
        break;
    }
    if (on == 0 || o->b0 == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(o->f10);
    }
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

/* shape b061:01E01170, 696 insns, 12 copies: moves and draws n spark emitters (0x44 bytes each): velocity, gravity, floor
   bounce, size growth, optional follow; each live one is one camera-facing square of its size around its
   projected point, with one of four texture corner orders picked by flags & 0x30. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b061_01E01170;

typedef struct {
    u64 uv;
    Xyz_b061_01E01170 xyz;
} Vtx_b061_01E01170;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b061_01E01170 v[4];
    u8 tail[0x20];
} Pkt_b061_01E01170;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b061_01E01170;

typedef struct {
    u8 life;
    u8 pad01;
    u8 max;
    u8 pad03;
    u8 flags;
    u8 follow;
    u8 pad06[2];
    u8 texkind;
    u8 mode;
    u8 texmode;
    u8 page;
    u8 b, g, r, a;
    f32 size;
    f32 grow;
    f32 gravity;
    f32 floor;
    f32 px, py, pz;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Spark_b061_01E01170;

#pragma optimization_level 1

static s32 func_01E00440_b179(void *arg0, s32 ot, s32 n) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern s32 func_001022D0(s32, s32);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat[16];
    Vec4f pt;
    Vec4f tmp;
    Tex_b061_01E01170 td;
    Pkt_b061_01E01170 pkt __attribute__((aligned(8)));
    Xyz_b061_01E01170 scr;
    f32 depth;
    Spark_b061_01E01170 *e;
    s32 i;
    s32 tex;
    s32 mode;
    s32 d;
    f32 s;
    f32 zf;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Spark_b061_01E01170 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texkind);
        e->vx += e->ax;
        e->vy += e->ay + e->gravity;
        e->vz += e->az;
        e->px += e->vx;
        e->py += e->vy;
        e->pz += e->vz;
        e->size += e->grow;
        if (e->py < e->floor) {
            e->py = e->floor;
            if (e->flags & 2) {
                e->vy = -(0.7f * e->vy);
            }
        }
        if (e->follow != 0) {
            func_00101BA0(e, &tmp);
            e->px = tmp.x;
            e->py = tmp.y;
            e->pz = tmp.z;
        }
        pt.x = e->px;
        pt.y = e->py;
        pt.z = e->pz;
        func_0020EB40(mat);
        ((Pkt_b061_01E01170 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b061_01E01170 *)(s32)&pkt)->tag = 9;
        ((Pkt_b061_01E01170 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b061_01E01170 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        d = e->max - e->life;
        mode = e->mode;
        if (e->flags & 1) {
            mode = (u8)func_001022D0(e->texmode, d);
            if (e->flags & 4) {
                e->flags &= 0xCF;
                e->flags |= ((func_0019A5C8() >> 4) & 3) << 4;
            }
        }
        td.page = e->page;
        func_001020B0(&td, mode, e->texmode);
        func_00101D20(&pkt, &td, tex);
        pkt.a = e->a;
        if (!(e->flags & 0x40) && e->life < 16) {
            pkt.a = (e->a >> 4) * e->life;
        }
        if (func_00205440(&pt, mat, &scr, &depth) != 0 && func_00101600(&scr) != 0) {
            s = func_001018E0(e->size, depth);
            if (e->flags & 0x80) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                zf = 0.0f;
            } else {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = scr.z;
                zf = depth;
            }
            switch (e->flags & 0x30) {
            case 0x10:
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = scr.x - s;
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = scr.x + s;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = scr.y - s;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = scr.y + s;
                break;
            case 0x20:
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = scr.x - s;
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = scr.x + s;
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = scr.y - s;
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = scr.y + s;
                break;
            case 0x30:
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = scr.x - s;
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = scr.x + s;
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = scr.y - s;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = scr.y + s;
                break;
            default:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = scr.x - s;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = scr.x + s;
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = scr.y - s;
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = scr.y + s;
                break;
            }
            func_002075F0(&pkt, ot, (u32)zf);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b241:01E00440 (ShFx_Flear01), 839 insns, 26 copies (-O1,p): draws each emitter of a list as a glowing ring: a
   fan of triangles and a quad pair per segment */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b241_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b241_01E00440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b241_01E00440 xyz;
} Vtx1_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    Vtx1_b241_01E00440 v[3];
    u8 tail[8];
} Pkt1_b241_01E00440;

typedef struct {
    u64 st;
    Xyz_b241_01E00440 xyz;
} Vtx2_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b241_01E00440 v[4];
    u8 tail[0x20];
} Pkt2_b241_01E00440;

typedef struct {
    f32 x, y, z, w;
} V4_b241_01E00440;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b241_01E00440;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    V4_b241_01E00440 pos;
    V4_b241_01E00440 vel;
    V4_b241_01E00440 org;
} Obj_b241_01E00440;

#pragma optimization_level 1

static s32 func_01E00F20_b179(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E05180_b179;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002086D0(void *, u64);
    extern void func_00101D20(void *, void *, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b241_01E00440 *o;
    s32 k;
    s32 i;
    s32 segs;
    s32 h;
    f32 m0[16];
    f32 m1[16];
    V4_b241_01E00440 org;
    Tex_b241_01E00440 t;
    Xyz_b241_01E00440 scr;
    Pkt1_b241_01E00440 p1 __attribute__((aligned(8)));
    Pkt2_b241_01E00440 p2 __attribute__((aligned(8)));
    f32 depth;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    u8 d;

    o = obj;
    t = D_01E05180_b179;
    h = func_00202BF0(t.id, t.kind);
    for (k = 0; k < n; k++) {
        if (k != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->radius += o->grow;
        org = o->org;
        segs = o->segs > 9 ? 9 : o->segs;
        step = 90.0f / segs;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m0, NULL, NULL, &o->pos);
        func_0020BC00(m1, m0);
        if (func_00205440(&org, m1, &scr, &depth) == 0 || func_00101600(&scr) == 0) {
            continue;
        }
        r = func_001018E0(o->radius, depth);
        w = func_001018E0(o->width, depth);
        if (o->flags & 0x80) {
            scr.z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            zf = depth;
        }
        ((Hdr_b241_01E00440 *)(s32)&p1)->count = 0x13;
        ((Hdr_b241_01E00440 *)(s32)&p1)->tag = 6;
        ((Hdr_b241_01E00440 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b241_01E00440 *)(s32)&p1)->pad = 0;
        p1.v[0].r = o->ir;
        p1.v[1].r = p1.v[2].r = o->r;
        p1.v[0].g = o->ig;
        p1.v[1].g = p1.v[2].g = o->g;
        p1.v[0].b = o->ib;
        p1.v[1].b = p1.v[2].b = o->b;
        p1.v[0].q = p1.v[1].q = p1.v[2].q = 1.0f;
        if (o->flags & 8) {
            func_002086D0(&p1, 0x42);
        } else {
            func_002086D0(&p1, 0x48);
        }
        ((Hdr_b241_01E00440 *)(s32)&p2)->count = 0x24;
        ((Hdr_b241_01E00440 *)(s32)&p2)->tag = 9;
        ((Hdr_b241_01E00440 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b241_01E00440 *)(s32)&p2)->pad = 0;
        p2.r = o->r;
        p2.g = o->g;
        p2.b = o->b;
        p2.q = 1.0f;
        func_00101D20(&p2, &t, h);
        p1.v[0].a = o->alpha;
        p2.a = o->alpha >> 1;
        p1.v[1].a = p1.v[2].a = 0;
        if (!(o->flags & 0x40)) {
            if (o->cur < 8) {
                p1.v[0].a = (o->alpha >> 3) * o->cur;
                p2.a = (o->alpha >> 4) * o->cur;
            } else {
                d = o->max - o->cur;
                if (d < 8) {
                    p1.v[0].a = (o->alpha >> 3) * d;
                    p2.a = (o->alpha >> 4) * d;
                }
            }
        }
        if (o->cur & 1) {
            if (o->flags & 2) {
                if (p1.v[0].a > 0x10) {
                    p1.v[0].a -= 0x10;
                }
            }
            if (o->flags & 4) {
                if (p1.v[0].a > 0) {
                    p1.v[0].a >>= 1;
                }
            }
        }
        x = r * func_001A6898(0.0f);
        y = r * func_001A6A88(0.0f);
        p2.v[0].xyz.z = p2.v[1].xyz.z = p2.v[2].xyz.z = p2.v[3].xyz.z = p1.v[0].xyz.z = p1.v[1].xyz.z =
            p1.v[2].xyz.z = scr.z;
        p2.v[0].xyz.f = p2.v[1].xyz.f = p2.v[2].xyz.f = p2.v[3].xyz.f = p1.v[0].xyz.f = p1.v[1].xyz.f =
            p1.v[2].xyz.f = 1;
        for (i = 1; i < segs * 4 + 1; i++) {
            px = x;
            py = y;
            x = r * func_001A6898(3.1415927f * (step * i) / 180.0f);
            y = r * func_001A6A88(3.1415927f * (step * i) / 180.0f);
            p1.v[0].xyz.x = scr.x;
            p1.v[0].xyz.y = scr.y;
            p1.v[1].xyz.x = scr.x + px;
            p1.v[1].xyz.y = scr.y + py;
            p1.v[2].xyz.x = scr.x + x;
            p1.v[2].xyz.y = scr.y + y;
            func_002075F0(&p1, tex, (u32)zf);
            if (o->flags & 1) {
                continue;
            }
            p2.v[0].xyz.x = p2.v[2].xyz.x = scr.x + px;
            p2.v[1].xyz.x = p2.v[3].xyz.x = scr.x + x;
            p2.v[0].xyz.y = scr.y + py - w;
            p2.v[2].xyz.y = w + (scr.y + py);
            p2.v[1].xyz.y = scr.y + y - w;
            p2.v[3].xyz.y = w + (scr.y + y);
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            p2.v[0].xyz.x = w + (scr.x + px);
            p2.v[2].xyz.x = scr.x + px - w;
            p2.v[1].xyz.x = w + (scr.x + x);
            p2.v[3].xyz.x = scr.x + x - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

#define ABS_b011_01E04380(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b011_01E04380;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b011_01E04380;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b011_01E04380 p;
} Vtx_b011_01E04380;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b011_01E04380 v[4];
    u8 tail[0x20];
} Pkt_b011_01E04380;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b011_01E04380;

typedef struct {
    u8 step;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 segments;
    u8 index;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 delay;
    u8 target;
    u8 pad0F;
    u8 *table;
    f32 size;
    f32 radius;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec_b011_01E04380 pos;
    Vec_b011_01E04380 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b011_01E04380;

extern Tex_b011_01E04380 D_01E051A0_b179;

#pragma optimization_level 1

static s32 func_01E01C40_b179(Ray_b011_01E04380 *obj, s32 target, s32 count) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101940(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Ray_b011_01E04380 *o;
    s32 i;
    s32 j;
    u8 idx;
    s32 span;
    s32 texture;
    f32 w;
    f32 zd;
    f32 y;
    f32 angle;
    f32 x;
    f32 r;
    f32 z;
    f32 step;
    f32 m2[16];
    f32 m1[16];
    Xyz_b011_01E04380 xy[2];
    Vec_b011_01E04380 pt;
    Vec_b011_01E04380 d;
    Vec_b011_01E04380 tmp;
    Tex_b011_01E04380 tex0;
    Tex_b011_01E04380 tex;
    Pkt_b011_01E04380 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E051A0_b179;
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        if (o->flags & 4) {
            texture = func_00202BF0(5, o->texkind);
            tex.page = o->texpage;
            func_001020B0(&tex, o->texmode, 0);
        } else {
            texture = func_00202BF0(tex0.id, tex0.kind);
            tex = tex0;
        }
        if (!(o->flags & 2)) {
            tex.u -= 0x10;
            tex.v -= 0x10;
        }
        idx = o->index;
        step = 17.0f;
        angle = 0.0f;
        if (o->step < o->delay) {
            span = o->total - o->delay;
        } else {
            span = o->total - o->step;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->rot[0] += o->spin[0];
        o->rot[1] += o->spin[1];
        o->rot[2] += o->spin[2];
        func_00101BA0(o, &o->pos);
        if (o->flags & 8) {
            func_001F5620(func_001F53A0(), o->target, &tmp);
            d.x = tmp.x - o->pos.x;
            d.y = tmp.y - o->pos.y;
            d.z = tmp.z - o->pos.z;
            func_00101940(&d, o->rot);
        }
        func_0020EB40(m1);
        func_0020C940(m2, 0, o->rot, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b011_01E04380 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b011_01E04380 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = o->r0;
        pkt.v[2].r = pkt.v[3].r = o->r1;
        pkt.v[0].g = pkt.v[1].g = o->g0;
        pkt.v[2].g = pkt.v[3].g = o->g1;
        pkt.v[0].b = pkt.v[1].b = o->b0;
        pkt.v[2].b = pkt.v[3].b = o->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (o->step <= 7 && !(o->flags & 0x40)) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = (o->a0 >> 3) * o->step;
            pkt.v[3].a = (o->a1 >> 3) * o->step;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = o->a0;
            pkt.v[3].a = o->a1;
        }
        func_00101EE0(&pkt, &tex, texture);
        pt.x = pt.y = pt.z = 0.0f;
        if (func_00205440(&pt, m1, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
            continue;
        }
        for (j = 0; j < o->segments; j++) {
            if (o->flags & 1) {
                x = o->size * (o->table[idx] - o->table[idx + 1]) / 255.0f;
                y = o->size * (o->table[idx + 2] - o->table[idx + 3]) / 255.0f;
                z = o->size * (o->table[idx + 4] - o->table[idx + 5]) / 255.0f;
                idx += 6;
            } else {
                angle += step;
                if (!(angle <= 360.0f)) {
                    angle -= 360.0f;
                }
                r = o->radius * o->table[idx] / 255.0f;
                idx++;
                x = r * func_001A6898(3.1415927f * angle / 180.0f);
                z = r * func_001A6A88(3.1415927f * angle / 180.0f);
                y = o->size / 2.0f;
                y += y * (o->table[idx] / 255.0f);
                idx++;
            }
            pt.x = x * span;
            pt.y = y * span;
            pt.z = z * span;
            if (func_00205440(&pt, m1, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0) {
                continue;
            }
            w = func_001018E0(o->width, dep[0]);
            if (o->flags & 0x80) {
                pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                zd = 0.0f;
            } else {
                if (dep[0] < dep[1]) {
                    zd = dep[0];
                } else {
                    zd = dep[1];
                }
                pkt.v[0].p.z = pkt.v[1].p.z = xy[0].z;
                pkt.v[2].p.z = pkt.v[3].p.z = xy[1].z;
            }
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 0;
            if (ABS_b011_01E04380(xy[1].x - xy[0].x) > ABS_b011_01E04380(xy[1].y - xy[0].y)) {
                pkt.v[0].p.y = xy[0].y;
                pkt.v[1].p.y = (u32)(xy[0].y - w);
                pkt.v[2].p.y = (u32)(xy[0].y + w);
                pkt.v[3].p.y = xy[1].y;
                if (xy[0].x < xy[1].x) {
                    pkt.v[0].p.x = (u32)(xy[0].x - w);
                } else {
                    pkt.v[0].p.x = (u32)(xy[0].x + w);
                }
                pkt.v[1].p.x = pkt.v[2].p.x = xy[0].x;
                pkt.v[3].p.x = xy[1].x;
            } else {
                pkt.v[0].p.x = xy[0].x;
                pkt.v[1].p.x = (u32)(xy[0].x - w);
                pkt.v[2].p.x = (u32)(xy[0].x + w);
                pkt.v[3].p.x = xy[1].x;
                if (xy[0].y < xy[1].y) {
                    pkt.v[0].p.y = (u32)(xy[0].y - w);
                } else {
                    pkt.v[0].p.y = (u32)(xy[0].y + w);
                }
                pkt.v[1].p.y = pkt.v[2].p.y = xy[0].y;
                pkt.v[3].p.y = xy[1].y;
            }
            func_002075F0(&pkt, target, (u32)zd);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b059:01E03720 (ShFx_Afx04), 1011 insns, 4 copies (-O1,p): the -O1 build of b172:01E012E0 (ShFx_Afx04): draws
   n flare entities with a fan of up to 8 triangles per ring */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b059_01E03720;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b059_01E03720;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b059_01E03720 uv;
    Xyz_b059_01E03720 xyz;
} Vtx_b059_01E03720;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b059_01E03720 v[4];
    u8 tail[8];
} Pkt_b059_01E03720;

typedef struct {
    f32 x, y, z;
} V3_b059_01E03720;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 scale;
    u8 blend;
    u8 mask;
    u8 len;
    s32 obj;
    u8 b2, g2, r2, a2;
    u8 b, g, r, a;
    V3_b059_01E03720 pos;
    f32 pad24;
    V3_b059_01E03720 vel;
    f32 pad34;
} Afx_b059_01E03720;

#pragma optimization_level 1

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E02970_b179(Afx_b059_01E03720 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_00101BA0(void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Afx_b059_01E03720 *e = arg0;
    f32 mat[16];
    u8 td[0x20];
    Vec4f cam;
    Vec4f d;
    Vec4f p;
    f32 m2[16];
    Xyz_b059_01E03720 xy[2];
    struct {
        Pkt_b059_01E03720 pk;
        s32 a[2];
        s32 b[2];
    } w;
    f32 depth[2];
    u8 bl[4];
    s32 i;
    s32 list;
    s32 u;
    s32 v;
    s32 j;
    s32 k;
    s32 cnt;
    s32 any;
    f32 fy;
    f32 fx;
    f32 h;
    f32 z;
    f32 t;
    s32 left;

    list = func_00207F60();
    any = 0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        cam = *func_001F9AD0(0);
        d.x = cam.x - e->pos.x;
        d.y = cam.y - e->pos.y;
        d.z = cam.z - e->pos.z;
        func_00101A00(&d, m2);
        d.x = d.z = 0.0f;
        d.y = 5.0f;
        if (e->flags & 1) {
            d.y *= -1.0f;
        }
        func_0020CDD0(&p, m2, &d);
        p.x += e->pos.x;
        p.y += e->pos.y;
        p.z += e->pos.z;
        if (func_00205440(&p, mat, &xy[0], &depth[0]) == 0) {
            continue;
        }
        if (func_00205440(&e->pos, mat, &xy[1], &depth[1]) == 0) {
            continue;
        }
        if (func_00101770(&xy[1]) == 0) {
            continue;
        }
        u = (s32)(xy[1].x - 27648.0f);
        v = (s32)(xy[1].y - 29184.0f);
        if (any == 0) {
            ((Pkt_b059_01E03720 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b059_01E03720 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b059_01E03720 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b059_01E03720 *)(s32)&w.pk)->pad = 0;
            w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g =
                w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = 0;
            w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = 0x80;
            w.pk.v[0].q = w.pk.v[1].q = w.pk.v[2].q = w.pk.v[3].q = 1.0f;
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = 0xFFFFFF;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            func_00208460();
            func_001F7060(e->obj, 0, w.a, w.b);
            func_00208460();
            any = 1;
        }
        w.pk.v[0].r = w.pk.v[1].r = e->r;
        w.pk.v[2].r = w.pk.v[3].r = e->r2;
        w.pk.v[0].g = w.pk.v[1].g = e->g;
        w.pk.v[2].g = w.pk.v[3].g = e->g2;
        w.pk.v[0].b = w.pk.v[1].b = e->b;
        w.pk.v[2].b = w.pk.v[3].b = e->b2;
        if (e->flags & 0x80) {
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = 0xFFFFFF;
            z = 0.0f;
        } else {
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = xy[0].z;
            z = depth[0];
        }
        td[5] = e->blend;
        func_00101C80(td, bl);
        func_002086D0(&w.pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        ((Pkt_b059_01E03720 *)(s32)&w.pk)->count |= 0x800;
        ((Uv_b059_01E03720 *)(s32)&w.pk.v[2].uv)->u = u;
        ((Uv_b059_01E03720 *)(s32)&w.pk.v[2].uv)->v = v;
        ((Uv_b059_01E03720 *)(s32)&w.pk.v[3].uv)->u = u;
        ((Uv_b059_01E03720 *)(s32)&w.pk.v[3].uv)->v = v;
        w.pk.v[2].xyz.x = w.pk.v[3].xyz.x = xy[1].x;
        w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = xy[1].y;
        if (e->life < 8) {
            w.pk.v[0].a = w.pk.v[1].a = (e->a >> 3) * e->life;
            w.pk.v[2].a = w.pk.v[3].a = (e->a2 >> 3) * e->life;
        } else {
            w.pk.v[0].a = w.pk.v[1].a = e->a;
            w.pk.v[2].a = w.pk.v[3].a = e->a2;
        }
        cnt = e->len;
        left = e->span - e->life + 1;
        if (left < cnt) {
            cnt = left;
        }
        if (e->life < cnt) {
            cnt = e->life;
        }
        for (k = 0; k < cnt; k++) {
            t = 0.5f * k;
            h = t * (u32)e->scale;
            for (j = 0; j < 8; j++) {
                if (!(e->mask & (1 << j))) {
                    continue;
                }
                fx = 16.0f * h;
                fy = 11.2f * h;
                switch (j) {
                case 0:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = v;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = xy[1].y;
                    w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 1:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = u;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[1].xyz.x = xy[1].x;
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 2:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = u;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = xy[1].x;
                    w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 3:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = v;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = (u32)(29184.0f - fy);
                    w.pk.v[1].xyz.y = xy[1].y;
                    break;
                case 4:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = v;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = xy[1].y;
                    w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 5:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = u;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[1].xyz.x = xy[1].x;
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 6:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = u;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = xy[1].x;
                    w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 7:
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b059_01E03720 *)(s32)&w.pk.v[1].uv)->v = v;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = (u32)(36352.0f + fy);
                    w.pk.v[1].xyz.y = xy[1].y;
                    break;
                }
                func_002075F0(&w.pk, 0, (u32)z);
            }
        }
    }
    if (any) {
        func_00207FD0(list, ot, 0);
    }
    return 1;
}
#pragma optimization_level reset

/* shape b179:01E03940 (ShFx_ReqBlur), 340 insns, 1 copy (-O1,p): ShFx_ReqBlur, -O1 build of b029:01E05AA0 (obj
   parameter copied under opt_propagation off): a flat textured screen quad between frames start..end with an alpha
   fade */

typedef struct {
    u16 start;
    u16 end;
    u8 pad4;
    u8 fade;
    u8 tex;
    u8 pad7;
    f32 level;
    s32 x[4];
    s32 y[4];
    u8 b, g, r;
} Obj_b179_01E03940;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
} Hdr_b179_01E03940;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
} Uv_b179_01E03940;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b179_01E03940;

typedef struct {
    Hdr_b179_01E03940 h;
    struct {
        u8 r, g, b, a;
        f32 q;
        Uv_b179_01E03940 uv;
        Xyz_b179_01E03940 xyz;
    } v[4];
    u8 tail[0x20];
} Pk_b179_01E03940;

typedef struct {
    u8 pad0[5];
    u8 tex;
    u8 pad6[0x12];
} Tex_b179_01E03940;

#pragma optimization_level 1
#pragma opt_propagation off

static s32 func_01E03940_b179(Obj_b179_01E03940 *arg0, s32 dst, u16 frame) {
    Obj_b179_01E03940 *obj = arg0;
    Tex_b179_01E03940 tex;
    Pk_b179_01E03940 pk __attribute__((aligned(8)));
    u8 o[4];
    u8 a;
    s32 d;

    if (frame >= obj->start && frame <= obj->end) {
        ((Hdr_b179_01E03940 *)(s32)&pk)->nreg = 0x34;
        ((Hdr_b179_01E03940 *)(s32)&pk)->n = 0xC;
        ((Hdr_b179_01E03940 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Hdr_b179_01E03940 *)(s32)&pk)->pad4 = 0;
        func_002087A0(&pk, 1);
        pk.v[0].r = pk.v[1].r = pk.v[2].r = pk.v[3].r = obj->r;
        pk.v[0].g = pk.v[1].g = pk.v[2].g = pk.v[3].g = obj->g;
        pk.v[0].b = pk.v[1].b = pk.v[2].b = pk.v[3].b = obj->b;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[1].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
        pk.v[0].xyz.f = pk.v[1].xyz.f = pk.v[2].xyz.f = pk.v[3].xyz.f = 0;
        d = frame - obj->start;
        a = obj->fade * 16;
        if (d < obj->fade) {
            a = d * 16;
        }
        if (obj->end - frame < obj->fade * 2) {
            a = (obj->end - frame) * 8;
        }
        pk.v[0].a = pk.v[1].a = pk.v[2].a = pk.v[3].a = a;
        tex.tex = obj->tex;
        func_00101C80(&tex, o);
        func_002086D0(&pk, (s64)o[0] | ((s64)o[1] << 2) | ((s64)o[2] << 4) | ((s64)o[3] << 6));
        ((Hdr_b179_01E03940 *)(s32)&pk)->nreg |= 0x800;
        ((Uv_b179_01E03940 *)(s32)&pk.v[0].uv)->u = 0;
        ((Uv_b179_01E03940 *)(s32)&pk.v[0].uv)->v = 0;
        ((Uv_b179_01E03940 *)(s32)&pk.v[1].uv)->u = 0x2800;
        ((Uv_b179_01E03940 *)(s32)&pk.v[1].uv)->v = 0;
        ((Uv_b179_01E03940 *)(s32)&pk.v[2].uv)->u = 0;
        ((Uv_b179_01E03940 *)(s32)&pk.v[2].uv)->v = 0x1C00;
        ((Uv_b179_01E03940 *)(s32)&pk.v[3].uv)->u = 0x2800;
        ((Uv_b179_01E03940 *)(s32)&pk.v[3].uv)->v = 0x1C00;
        pk.v[0].xyz.x = (u32)(27648.0f + (f32)(obj->x[0] * 16));
        pk.v[1].xyz.x = (u32)(37888.0f + (f32)(obj->x[1] * 16));
        pk.v[2].xyz.x = (u32)(27648.0f + (f32)(obj->x[2] * 16));
        pk.v[3].xyz.x = (u32)(37888.0f + (f32)(obj->x[3] * 16));
        pk.v[0].xyz.y = (u32)(29184.0f + (f32)(obj->y[0] * 16));
        pk.v[1].xyz.y = (u32)(29184.0f + (f32)(obj->y[1] * 16));
        pk.v[2].xyz.y = (u32)(36352.0f + (f32)(obj->y[2] * 16));
        pk.v[3].xyz.y = (u32)(36352.0f + (f32)(obj->y[3] * 16));
        func_002075F0((s32)&pk, dst, (u32)(obj->level));
    }
    return 1;
}

#pragma opt_propagation reset
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b179", func_01E03E90_b179);
