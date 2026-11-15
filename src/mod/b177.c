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

static void func_01E00080_b177(Obj_b002_01E00080 *arg0) {
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

extern Tex_b011_01E04380 D_01E05A80_b177;

#pragma optimization_level 1

static s32 func_01E00440_b177(Ray_b011_01E04380 *obj, s32 target, s32 count) {
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
    tex0 = D_01E05A80_b177;
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

static s32 func_01E01170_b177(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E05AA0_b177;
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
    t = D_01E05AA0_b177;
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

/* shape b177:01E01E90 (ShFx_FreeLZ), 1099 insns, 2 copies (-O1,p): ShFx_FreeLZ at -O1 (b172:01E003A0's comet
   emitters): the head position pushed into a ring of pool entries, used as is or run through the spline; a head
   sprite at the first point, then a ribbon of quads between consecutive projected points; float locals declared hz,
   h, d, pw, step, al; the half-width difference a block local */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b177_01E01E90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b177_01E01E90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b177_01E01E90 p;
} Vtx_b177_01E01E90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b177_01E01E90 v[4];
    u8 tail[0x20];
} Pkt_b177_01E01E90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 tc;
        Xyz_b177_01E01E90 p;
    } v[4];
    u8 tail[0x20];
} Spr_b177_01E01E90;

typedef struct {
    u8 pad0[5];
    u8 page;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b177_01E01E90;

typedef struct {
    u8 life;
    u8 pad1[3];
    f32 x, y, z;
} Part_b177_01E01E90;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 mask;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b177_01E01E90 *parts;
    s16 slot[9];
    u8 count;
    u8 texid;
    u8 b20;
    u8 page;
    u8 frame;
    u8 frame2;
    u8 b24;
    u8 pad25[3];
    s32 type;
    f32 size;
    f32 width;
    u8 b, g, r, a;
    f32 pos[3];
} Comet_b177_01E01E90;

#pragma optimization_level 1

static s32 func_01E01E90_b177(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00101BA0(void *, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101B40(void *, u8, s32);
    extern s32 func_00102550(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern void func_00101EE0(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    f32 mat[16];
    Spline_b177_01E01E90 sp;
    Vec4f t;
    Xyz_b177_01E01E90 q[2];
    Tex_b177_01E01E90 td;
    Pkt_b177_01E01E90 pkt;
    Spr_b177_01E01E90 spr;
    f32 dz[2];
    Comet_b177_01E01E90 *e;
    Part_b177_01E01E90 *pool;
    s32 i;
    s32 k;
    s32 m;
    Part_b177_01E01E90 *p;
    void *tex;
    s32 ok;
    s32 pok;
    s32 fr;
    s32 idx;
    s32 dd;
    f32 hz;
    f32 h;
    f32 d;
    f32 pw;
    f32 step;
    f32 al;

    e = arg0;
    pool = e->parts;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Comet_b177_01E01E90 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        func_0020EB40(mat);
        if (e->follow != 0) {
            func_00101BA0(e, &t);
            e->pos[0] = t.x;
            e->pos[1] = t.y;
            e->pos[2] = t.z;
        }
        fr = e->mask & (e->max - e->life);
        if (e->life == 0) {
            for (k = 0; k < e->count; k++) {
                p = &pool[e->slot[k]];
                p->life = 0;
                e->slot[k] = -1;
            }
            continue;
        }
        for (k = e->count; k > 0; k--) {
            if (e->slot[k - 1] >= 0) {
                p = &pool[e->slot[k - 1]];
                p->life = e->life;
            }
            if (!(e->flags & 8)) {
                e->slot[k] = e->slot[k - 1];
            }
        }
        if (!(e->flags & 8)) {
            if (e->slot[e->count] >= 0) {
                p = &pool[e->slot[e->count]];
                p->life = 0;
                e->slot[e->count] = -1;
            }
            idx = func_00101C30(pool, 0x10, e->type);
            if (idx >= 0) {
                e->slot[0] = idx;
                p = &pool[e->slot[0]];
                func_00101B40(p, e->life, 0);
                p->x = e->pos[0];
                p->y = e->pos[1];
                p->z = e->pos[2];
            } else {
                e->slot[0] = -1;
            }
        }
        if (e->b24 & 4) {
            m = 0;
            for (k = 0; k < e->count; k++) {
                if (e->slot[k] >= 0) {
                    p = &pool[e->slot[k]];
                    sp.out[k].x = p->x;
                    sp.out[k].y = p->y;
                    sp.out[k].z = p->z;
                    m++;
                }
            }
        } else {
            sp.n = 0;
            for (k = 0; k < e->count; k++) {
                if (e->slot[k] >= 0) {
                    p = &pool[e->slot[k]];
                    sp.x[sp.n] = p->x;
                    sp.y[sp.n] = p->y;
                    sp.z[sp.n] = p->z;
                    sp.n++;
                }
            }
            if (func_00102550(&sp) == 0) {
                continue;
            }
            m = (sp.n - 1) * 4;
        }
        ok = func_00205440(&sp.out[0], mat, &q[1], &dz[1]);
        h = func_001018E0(e->size, dz[1]);
        if (ok != 0) {
            ok = func_00101600(&q[1]);
        }
        if (ok != 0 && !(e->flags & 1)) {
            ((Spr_b177_01E01E90 *)(s32)&spr)->count = 0x24;
            ((Spr_b177_01E01E90 *)(s32)&spr)->tag = 9;
            ((Spr_b177_01E01E90 *)(s32)&spr)->regs = ((u64)4 << 32) | 0x24242421;
            ((Spr_b177_01E01E90 *)(s32)&spr)->pad = 0;
            spr.r = e->r;
            spr.g = e->g;
            spr.b = e->b;
            spr.q = 1.0f;
            if (e->flags & 2) {
                dd = fr & 7;
                if (e->life < 7) {
                    dd = 7 - e->life;
                }
            } else {
                dd = e->frame;
            }
            td.page = e->page;
            func_001020B0(&td, dd, e->b20);
            func_00101D20(&spr, &td, tex);
            spr.a = e->a;
            if (!(e->flags & 0x40)) {
                if (e->life < 4) {
                    spr.a = (e->a >> 2) * e->life;
                }
            }
            if (e->flags & 0x80) {
                spr.v[0].p.z = spr.v[1].p.z = spr.v[2].p.z = spr.v[3].p.z = 0xFFFFFE;
                hz = 0.0f;
            } else {
                spr.v[0].p.z = spr.v[1].p.z = spr.v[2].p.z = spr.v[3].p.z = q[1].z;
                hz = dz[1];
            }
            spr.v[0].p.x = spr.v[2].p.x = q[1].x - h;
            spr.v[1].p.x = spr.v[3].p.x = q[1].x + h;
            spr.v[0].p.y = spr.v[1].p.y = q[1].y - h;
            spr.v[2].p.y = spr.v[3].p.y = q[1].y + h;
            func_002075F0(&spr, ot, (u32)hz);
        }
        ((Pkt_b177_01E01E90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b177_01E01E90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b177_01E01E90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b177_01E01E90 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        td.page = e->page;
        func_001020B0(&td, e->frame2, e->b20);
        if (e->flags & 4) {
            s32 w = td.w - td.u;
            td.u = td.u + (w >> 1) - 1;
            td.w = td.w - (w >> 1) + 1;
        }
        func_00101EE0(&pkt, &td, tex);
        h = func_001018E0(e->width, dz[1]);
        for (k = 1; k < m - 1; k++) {
            q[0] = q[1];
            dz[0] = dz[1];
            pw = h;
            pok = ok;
            ok = func_00205440(&sp.out[k], mat, &q[1], &dz[1]);
            if (ok != 0) {
                ok = func_00101600(&q[1]);
            }
            if (pok == 0 || ok == 0) {
                break;
            }
                h = func_001018E0(e->width, dz[1]);
                if (e->life < 4 && !(e->flags & 0x40)) {
                    al = (f32)e->life * e->a / 4.0f;
                } else {
                    al = e->a;
                }
                step = al / m;
                pkt.v[0].a = pkt.v[2].a = step * (m - k);
                pkt.v[1].a = pkt.v[3].a = step * (m - k - 1);
                if (k == 1 && (e->b24 & 2)) {
                    pkt.v[0].a = pkt.v[2].a = 0;
                }
                if (e->flags & 0x80) {
                    pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                    d = 0.0f;
                } else {
                    pkt.v[0].p.z = pkt.v[2].p.z = q[0].z;
                    pkt.v[1].p.z = pkt.v[3].p.z = q[1].z;
                    if (dz[0] < dz[1]) {
                        d = dz[0];
                    } else {
                        d = dz[1];
                    }
                }
                pkt.v[0].p.y = q[0].y - pw;
                pkt.v[1].p.y = q[1].y - h;
                pkt.v[2].p.y = q[0].y + pw;
                pkt.v[3].p.y = q[1].y + h;
                pkt.v[0].p.x = pkt.v[2].p.x = q[0].x;
                pkt.v[1].p.x = pkt.v[3].p.x = q[1].x;
                func_002075F0(&pkt, ot, (u32)d);
                pkt.v[0].p.x = q[0].x - pw;
                pkt.v[1].p.x = q[1].x - h;
                pkt.v[2].p.x = q[0].x + pw;
                pkt.v[3].p.x = q[1].x + h;
                pkt.v[0].p.y = pkt.v[2].p.y = q[0].y;
                pkt.v[1].p.y = pkt.v[3].p.y = q[1].y;
                func_002075F0(&pkt, ot, (u32)d);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b177:01E02FC0 (ShFx_Lfl2), 1163 insns, 1 copy (-O1,p): lens flare like ShFx_Lfl (b285:01E03B50), aimed from
   pos at tgt (0x58-byte emitters, func_00101940 gives the rotation) instead of spinning; elements spaced around -4 *
   base */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b177_01E02FC0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b177_01E02FC0 xyz;
} Vtx_b177_01E02FC0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b177_01E02FC0 v[3];
    u8 tail[8];
} Pkt3_b177_01E02FC0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b177_01E02FC0 v[4];
    u8 tail[8];
} Pkt4_b177_01E02FC0;

typedef struct {
    f32 x, y, z;
} V3_b177_01E02FC0;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    u8 kind[8];
    u8 cnt;
    u8 a1;
    u8 a2;
    u8 pad13;
    f32 size[8];
    f32 base;
    V3_b177_01E02FC0 pos;
    f32 pad44;
    V3_b177_01E02FC0 tgt;
    f32 pad54;
} Lfl_b177_01E02FC0;

#pragma optimization_level 1

static s32 func_01E02FC0_b177(Lfl_b177_01E02FC0 *arg0, s32 ot, s32 n) {
    extern Vec4f *func_001FAD10(s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern void func_00101940(void *, void *);
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern void func_0020D070(void *);
    extern f32 func_0020D1A0(void *, void *);
    extern void func_002086D0(void *, u64);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Lfl_b177_01E02FC0 *e;
    f32 mat2[16];
    f32 mat[16];
    f32 m[16];
    Vec4f d;
    Vec4f v;
    Vec4f dir;
    Vec4f cam;
    Vec4f rot;
    Xyz_b177_01E02FC0 xy;
    Pkt3_b177_01E02FC0 p3 __attribute__((aligned(8)));
    Pkt4_b177_01E02FC0 p4 __attribute__((aligned(8)));
    f32 depth;
    s32 i;
    s32 j;
    s32 seg;
    s32 k;
    s32 a1;
    s32 a2;
    s32 al;
    f32 r;
    f32 q;
    f32 z;
    f32 step;
    f32 x0, y0, x1, y1, x2, y2;
    f32 dot;
    f32 px0, px1, px2, py0, py1, py2;

    e = arg0;
    cam = *func_001FAD10(0);
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        if (func_00205440(&e->pos, mat, &xy, &depth) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        dir.x = e->tgt.x - e->pos.x;
        dir.y = e->tgt.y - e->pos.y;
        dir.z = e->tgt.z - e->pos.z;
        func_00101940(&dir, &rot);
        d.z = 0.0f;
        d.x = 0.0f;
        d.y = 1.0f;
        func_0020C630(m, &rot);
        func_0020CDD0(&v, m, &d);
        func_0020D070(&cam);
        dot = func_0020D1A0(&v, &cam);
        if (dot <= -0.7f) {
            seg = 9;
            step = 90.0f / seg;
            ((Pkt3_b177_01E02FC0 *)(s32)&p3)->count = 0x13;
            ((Pkt3_b177_01E02FC0 *)(s32)&p3)->tag = 6;
            ((Pkt3_b177_01E02FC0 *)(s32)&p3)->regs = 0x414141;
            ((Pkt3_b177_01E02FC0 *)(s32)&p3)->pad = 0;
            p3.v[0].r = p3.v[1].r = p3.v[2].r = p3.v[0].g = p3.v[1].g = p3.v[2].g = p3.v[0].b = p3.v[1].b =
                p3.v[2].b = 0x80;
            p3.v[0].q = p3.v[1].q = p3.v[2].q = 1.0f;
            func_002086D0(&p3, 0x48);
            ((Pkt4_b177_01E02FC0 *)(s32)&p4)->count = 0x14;
            ((Pkt4_b177_01E02FC0 *)(s32)&p4)->tag = 8;
            ((Pkt4_b177_01E02FC0 *)(s32)&p4)->regs = 0x41414141;
            ((Pkt4_b177_01E02FC0 *)(s32)&p4)->pad = 0;
            p4.v[0].r = p4.v[1].r = p4.v[2].r = p4.v[3].r = p4.v[0].g = p4.v[1].g = p4.v[2].g = p4.v[3].g =
                p4.v[0].b = p4.v[1].b = p4.v[2].b = p4.v[3].b = 0x80;
            p4.v[0].q = p4.v[1].q = p4.v[2].q = p4.v[3].q = 1.0f;
            func_002086D0(&p4, 0x48);
            func_0020EB40(mat);
            func_0020C940(mat2, NULL, &rot, &e->tgt);
            func_0020BC00(mat, mat2);
            if (e->life < 8) {
                a1 = (e->a1 >> 3) * e->life;
                a2 = (e->a2 >> 3) * e->life;
            } else {
                a1 = e->a1;
                a2 = e->a2;
            }
            for (k = 0; k < e->cnt; k++) {
                d.y = -(4.0f * e->base) + e->base * k;
                if (func_00205440(&d, mat, &xy, &depth) == 0) {
                    continue;
                }
                if (func_00101600(&xy) == 0) {
                    continue;
                }
                r = func_001018E0(e->size[k], depth);
                al = (s32)(a1 * (-dot - 0.7f) / 0.3f);
                switch (e->kind[k]) {
                case 0:
                    p3.v[0].a = p3.v[1].a = p3.v[2].a = al;
                    break;
                case 1:
                    p3.v[0].a = al;
                    p3.v[1].a = p3.v[2].a = al >> 2;
                    break;
                case 2:
                    p3.v[0].a = 0;
                    p3.v[1].a = p3.v[2].a = al;
                    break;
                case 3:
                case 5:
                    p4.v[0].a = p4.v[1].a = 0;
                    p4.v[2].a = p4.v[3].a = al;
                    break;
                case 4:
                    p4.v[0].a = p4.v[1].a = al;
                    p4.v[2].a = p4.v[3].a = 0;
                    break;
                }
                if (e->flags & 0x80) {
                    xy.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    z = depth;
                }
                p4.v[0].xyz.z = p4.v[1].xyz.z = p4.v[2].xyz.z = p4.v[3].xyz.z = p3.v[0].xyz.z = p3.v[1].xyz.z =
                    p3.v[2].xyz.z = xy.z;
                p4.v[0].xyz.f = p4.v[1].xyz.f = p4.v[2].xyz.f = p4.v[3].xyz.f = p3.v[0].xyz.f = p3.v[1].xyz.f =
                    p3.v[2].xyz.f = 1;
                x0 = r * func_001A6898(0.0f);
                y0 = r * func_001A6A88(0.0f);
                q = r / 4.0f;
                x1 = (r + q) * func_001A6898(0.0f);
                y1 = (r + q) * func_001A6A88(0.0f);
                x2 = (r - q) * func_001A6898(0.0f);
                y2 = (r - q) * func_001A6A88(0.0f);
                for (j = 1; j < seg * 4 + 1; j++) {
                    if (e->kind[k] >= 3) {
                        px0 = x0;
                        px1 = x1;
                        px2 = x2;
                        py0 = y0;
                        py1 = y1;
                        py2 = y2;
                        x0 = r * func_001A6898(3.1415927f * (step * j) / 180.0f);
                        y0 = r * func_001A6A88(3.1415927f * (step * j) / 180.0f);
                        x1 = (r + q) * func_001A6898(3.1415927f * (step * j) / 180.0f);
                        y1 = (r + q) * func_001A6A88(3.1415927f * (step * j) / 180.0f);
                        x2 = (r - q) * func_001A6898(3.1415927f * (step * j) / 180.0f);
                        y2 = (r - q) * func_001A6A88(3.1415927f * (step * j) / 180.0f);
                        p4.v[0].xyz.x = (u32)(xy.x + px1);
                        p4.v[0].xyz.y = (u32)(xy.y + py1);
                        p4.v[1].xyz.x = (u32)(xy.x + x1);
                        p4.v[1].xyz.y = (u32)(xy.y + y1);
                        p4.v[2].xyz.x = (u32)(xy.x + px0);
                        p4.v[2].xyz.y = (u32)(xy.y + py0);
                        p4.v[3].xyz.x = (u32)(xy.x + x0);
                        p4.v[3].xyz.y = (u32)(xy.y + y0);
                        func_002075F0(&p4, ot, (u32)z);
                        if (e->kind[k] == 5) {
                            p4.v[0].xyz.x = (u32)(xy.x + px2);
                            p4.v[0].xyz.y = (u32)(xy.y + py2);
                            p4.v[1].xyz.x = (u32)(xy.x + x2);
                            p4.v[1].xyz.y = (u32)(xy.y + y2);
                            func_002075F0(&p4, ot, (u32)z);
                        }
                    } else {
                        px0 = x0;
                        py0 = y0;
                        x0 = r * func_001A6898(3.1415927f * (step * j) / 180.0f);
                        y0 = r * func_001A6A88(3.1415927f * (step * j) / 180.0f);
                        p3.v[0].xyz.x = xy.x;
                        p3.v[0].xyz.y = xy.y;
                        p3.v[1].xyz.x = (u32)(xy.x + px0);
                        p3.v[1].xyz.y = (u32)(xy.y + py0);
                        p3.v[2].xyz.x = (u32)(xy.x + x0);
                        p3.v[2].xyz.y = (u32)(xy.y + y0);
                        func_002075F0(&p3, ot, (u32)z);
                    }
                }
            }
            p4.v[0].r = p4.v[1].r = p4.v[2].r = p4.v[3].r = p4.v[0].g = p4.v[1].g = p4.v[2].g = p4.v[3].g =
                p4.v[0].b = p4.v[1].b = p4.v[2].b = p4.v[3].b = 0xFF;
            p4.v[0].q = p4.v[1].q = p4.v[2].q = p4.v[3].q = 1.0f;
            p4.v[0].xyz.z = p4.v[1].xyz.z = p4.v[2].xyz.z = p4.v[3].xyz.z = 0xFFFFFF;
            p4.v[0].a = p4.v[1].a = p4.v[2].a = p4.v[3].a = (s32)(a2 * (-dot - 0.7f) / 0.3f);
            p4.v[0].xyz.x = p4.v[2].xyz.x = 0x6C00;
            p4.v[1].xyz.x = p4.v[3].xyz.x = 0x9400;
            p4.v[0].xyz.y = p4.v[1].xyz.y = 0x7200;
            p4.v[2].xyz.y = p4.v[3].xyz.y = 0x8E00;
            func_002075F0(&p4, ot, 0);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b059:01E00440, 626 insns, 8 copies: draws n ring/cone emitters (0x48 bytes each): a quarter ring of up to 9
   segments between an inner radius at height y+dy and an outer one at y, mirrored into four quadrants as quads;
   texture page from a 4-entry module table by e->type, STQ from the page rectangle (types 1-3) or func_00101EE0 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b059_01E00440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b059_01E00440 xyz;
} Vtx_b059_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b059_01E00440 v[4];
    u8 tail[0x20];
} Pkt_b059_01E00440;

typedef struct {
    s32 id;
    u8 sub;
    u8 pad5[3];
    s32 u, w, v, h;
} Tex_b059_01E00440;

typedef struct {
    Tex_b059_01E00440 e[4];
} Tab_b059_01E00440;

typedef struct {
    u8 b, g, r, a;
} Col_b059_01E00440;

typedef struct {
    u8 life;
    u8 pad1[6];
    u8 seg;
    u8 type;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 scale;
    f32 base;
    f32 dy;
    f32 y;
    f32 vy;
    Col_b059_01E00440 c0;
    Col_b059_01E00440 c1;
    Vec4f pos;
    Vec4f rot;
} Emit_b059_01E00440;

extern Tab_b059_01E00440 D_01E05AC0_b177;

#pragma optimization_level 1

static s32 func_01E041F0_b177(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f a[10];
    Vec4f b[10];
    Vec4f c[4];
    f32 depth[4];
    Tab_b059_01E00440 tab;
    Tex_b059_01E00440 td;
    Pkt_b059_01E00440 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b059_01E00440 *e;
    s32 i;
    s32 j;
    s32 k;
    s32 nseg;
    s32 tex;
    f32 sn;
    f32 step;
    f32 r1;
    f32 r2;
    f32 cs;

    e = arg0;
    tab = D_01E05AC0_b177;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(tab.e[e->type].id, tab.e[e->type].sub);
        e->y += e->vy;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        if (e->seg > 9) {
            nseg = 9;
        } else {
            nseg = e->seg;
        }
        step = 90.0f / nseg;
        r1 = e->scale * (e->y + e->dy) / e->base;
        r2 = e->scale * e->y / e->base;
        for (j = 0; j < nseg + 1; j++) {
            sn = func_001A6A88(3.1415927f * (step * j) / 180.0f);
            cs = func_001A6898(3.1415927f * (step * j) / 180.0f);
            a[j].x = r1 * cs;
            a[j].z = r1 * sn;
            a[j].y = e->y + e->dy;
            b[j].x = r2 * cs;
            b[j].z = r2 * sn;
            b[j].y = e->y;
        }
        ((Pkt_b059_01E00440 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b059_01E00440 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b059_01E00440 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b059_01E00440 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        c[0].y = c[1].y = a[0].y;
        c[2].y = c[3].y = b[0].y;
        for (j = 0; j < nseg; j++) {
            for (k = 0; k < 4; k++) {
                switch (k) {
                case 0:
                    c[0].x = a[j].x;
                    c[1].x = a[j + 1].x;
                    c[2].x = b[j].x;
                    c[3].x = b[j + 1].x;
                    c[0].z = a[j].z;
                    c[1].z = a[j + 1].z;
                    c[2].z = b[j].z;
                    c[3].z = b[j + 1].z;
                    break;
                case 1:
                    c[0].x = -a[j].x;
                    c[1].x = -a[j + 1].x;
                    c[2].x = -b[j].x;
                    c[3].x = -b[j + 1].x;
                    break;
                case 2:
                    c[0].z = -a[j].z;
                    c[1].z = -a[j + 1].z;
                    c[2].z = -b[j].z;
                    c[3].z = -b[j + 1].z;
                    break;
                case 3:
                    c[0].x = a[j].x;
                    c[1].x = a[j + 1].x;
                    c[2].x = b[j].x;
                    c[3].x = b[j + 1].x;
                    break;
                }
                if (func_00205440(&c[0], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                    func_00205440(&c[1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                    func_00205440(&c[2], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                    func_00205440(&c[3], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                    pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                    td = tab.e[e->type];
                    switch (e->type) {
                    case 1:
                    case 2:
                    case 3:
                        func_00208CB0(&pkt, 0xB | ((u64)e->b9 << 4) | ((u64)td.u << 14) | ((u64)td.v << 24) |
                                                ((u64)(td.h - 1) << 34));
                        td.u = 0;
                        td.w = e->bA;
                        pkt.v[0].q = 1.0f / depth[0];
                        pkt.v[1].q = 1.0f / depth[1];
                        pkt.v[2].q = 1.0f / depth[2];
                        pkt.v[3].q = 1.0f / depth[3];
                        pkt.v[0].s = td.u / 256.0f / depth[0];
                        pkt.v[0].t = td.v / 256.0f / depth[0];
                        pkt.v[1].s = td.w / 256.0f / depth[1];
                        pkt.v[1].t = td.v / 256.0f / depth[1];
                        pkt.v[2].s = td.u / 256.0f / depth[2];
                        pkt.v[2].t = td.h / 256.0f / depth[2];
                        pkt.v[3].s = td.w / 256.0f / depth[3];
                        pkt.v[3].t = td.h / 256.0f / depth[3];
                        func_00101C80(&td, bl);
                        func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                        func_00208700(&pkt, (void *)tex, 1);
                        break;
                    default:
                        func_00101EE0(&pkt, &td, (void *)tex);
                        break;
                    }
                    func_002075F0((s32)&pkt, ot, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b177:01E04BC0 (b177), 924 insns, 1 copy (-O1,p): b177 scene manager (-O1), b199:01E04E70's form: code >= 0
   clears the 0xBE0 scene, takes both units, the camera, joints 0x2A/0x17, the wave (2, 0x9E) and the table; else
   counts the frame: 61 the flare, the link and the emitter, 80 the lens flare aimed at joint 0x17, 99 six rays, the
   big flare and the ring; every 4th frame from 68 to 100 one more ray; steps every effect; 164 returns 8; 6 from 100
   to 128, 1 at 90, 2 at 129 */

typedef struct {
    s32 a;
    s32 dir;
    u8 pad8[0xC];
} Cam_b177_01E04BC0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7[0xD];
    f32 f14;
    f32 f18;
    f32 f1C;
    Vec4f pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    f32 f50;
    u8 pad54[0xC];
} Emit_b177_01E04BC0;

typedef struct {
    s16 a;
    s16 b;
} Wv_b177_01E04BC0;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    Vec4f pos;
    u8 pad2C[0x10];
    f32 ox, oy, oz, ow;
} Flear_b177_01E04BC0;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    u8 segments;
    u8 index;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 padD[3];
    s8 *table;
    f32 size;
    f32 radius;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec4f pos;
    Vec4f vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b177_01E04BC0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    s8 *buf;
    s16 pts[9];
    u8 cnt;
    u8 b1F;
    u8 pad20;
    u8 b21;
    u8 b22;
    u8 b23;
    u8 pad24[4];
    s32 w28;
    f32 f2C;
    f32 f30;
    u8 c[4];
    u8 pad38[0xC];
    u8 data[0x280];
} Lnk_b177_01E04BC0;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    u8 kind[8];
    u8 cnt;
    u8 a1;
    u8 a2;
    u8 pad13;
    f32 size[8];
    f32 base;
    Vec4f pos;
    f32 tx, ty, tz;
    f32 pad54;
} Lfl_b177_01E04BC0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 seg;
    u8 type;
    u8 pad9[3];
    f32 scale;
    f32 base;
    f32 dy;
    f32 y;
    f32 vy;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec4f pos;
    s32 rot[4];
} Ring_b177_01E04BC0;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    u8 pad14[0x18];
    Cam_b177_01E04BC0 cam;
    Emit_b177_01E04BC0 emit;
    Wv_b177_01E04BC0 wv;
    Flear_b177_01E04BC0 flear;
    Ray_b177_01E04BC0 ray[16];
    Lnk_b177_01E04BC0 lnk;
    Lfl_b177_01E04BC0 lfl;
    Ring_b177_01E04BC0 ring;
    s8 tbl[0x100];
    u8 padBD4[0xC];
} Scene_b177_01E04BC0;

#pragma optimization_level 1

static s32 func_01E04BC0_b177(Scene_b177_01E04BC0 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_01E01E90_b177();
    s32 ot = func_00207500();
    Vec4f v;
    s32 i;
    s32 j;
    s32 k;

    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0xBE0);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 1; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 0x2A, 1);
        g->m1 = func_001F5560(g->unitA, 0x17, 0);
        g->wv.a = 2;
        g->wv.b = 0x9E;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x3D:
        func_00101AD0(&g->flear, 0xC, 0, 0xFF);
        g->flear.b5 = 1;
        g->flear.b6 = g->m0;
        g->flear.flags = 0x80;
        g->flear.segs = 9;
        g->flear.r = 0x80;
        g->flear.g = 0x10;
        g->flear.b = 0x20;
        g->flear.ir = g->flear.ig = g->flear.ib = g->flear.alpha = 0xF0;
        g->flear.radius = 80.0f;
        g->flear.grow = 60.0f;
        g->flear.width = 8.0f;
        func_00101AD0(&g->lnk, 0x46, 0, 7);
        g->lnk.b5 = 1;
        g->lnk.b6 = g->m0;
        g->lnk.b4 = 0x86;
        g->lnk.buf = (s8 *)g->lnk.data;
        g->lnk.w28 = 0x28;
        g->lnk.cnt = 8;
        g->lnk.b1F = 0;
        g->lnk.b21 = 2;
        g->lnk.b22 = 3;
        g->lnk.b23 = 3;
        g->lnk.c[2] = g->lnk.c[1] = g->lnk.c[0] = 0x80;
        g->lnk.c[3] = 0xC0;
        g->lnk.f2C = 200.0f;
        g->lnk.f30 = 180.0f;
        for (j = 0; j < g->lnk.cnt + 1; j++) {
            g->lnk.pts[j] = -1;
        }
        func_00101AD0(&g->emit, 0x46, 0, 0xFF);
        g->emit.b5 = 1;
        g->emit.b6 = g->m0;
        g->emit.b4 = 4;
        g->emit.f14 = 2.0f;
        g->emit.f18 = 1.0f;
        g->emit.f1C = 1.2f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 80.0f;
        g->emit.f50 = 6.0f;
        break;
    case 0x50:
        func_00101AD0(&g->lfl, 0x12, 0, 0xFF);
        g->lfl.flags = 0x80;
        g->lfl.b5 = 1;
        g->lfl.b6 = g->m0;
        g->lfl.cnt = 8;
        g->lfl.a1 = 0x80;
        g->lfl.a2 = 0x60;
        g->lfl.base = 1.4f;
        func_001F5620(g->unitA, g->m1, &g->lfl.tx);
        if (g->cam.dir != 0x8000) {
            g->lfl.ty -= 0.6f;
        }
        if (g->cam.dir == 0x8000) {
            g->lfl.tx += 4.0f;
            g->lfl.tz += 5.0f;
        } else {
            g->lfl.tx -= 4.0f;
            g->lfl.tz -= 5.0f;
        }
        g->lfl.kind[0] = 0;
        g->lfl.size[0] = 30.0f;
        g->lfl.kind[1] = 4;
        g->lfl.size[1] = 40.0f;
        g->lfl.kind[2] = 2;
        g->lfl.size[2] = 10.0f;
        g->lfl.kind[3] = 2;
        g->lfl.size[3] = 30.0f;
        g->lfl.kind[4] = 4;
        g->lfl.size[4] = 60.0f;
        g->lfl.kind[5] = 0;
        g->lfl.size[5] = 20.0f;
        g->lfl.kind[6] = 5;
        g->lfl.size[6] = 80.0f;
        g->lfl.kind[7] = 2;
        g->lfl.size[7] = 20.0f;
        break;
    case 0x63:
        for (i = 0; i < 6; i++) {
            k = func_00101C30(g->ray, 0x68, 0x10);
            if (k >= 0) {
                g->ray[k].flags = 4;
                func_00101AD0(&g->ray[k], 0x14, (u8)(i * 3), 0xFF);
                g->ray[k].flags |= 2;
                g->ray[k].a1 = g->ray[k].a0 = 0x80;
                g->ray[k].b5 = 0;
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 3;
                g->ray[k].segments = 0x50;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
                g->ray[k].pos = v;
                g->ray[k].width = 20.0f * (f32)(i + 1);
                g->ray[k].size = 2.5f - 0.4f * (f32)i;
                g->ray[k].radius = 0.4f + 0.4f * (f32)i;
                if (g->cam.dir != 0x8000) {
                    g->ray[k].rot[0] = -0x4000;
                } else {
                    g->ray[k].rot[0] = 0x4000;
                }
            }
        }
        func_00101AD0(&g->flear, 0x20, 2, 0xFF);
        g->flear.b5 = 0;
        g->flear.flags = 0x81;
        g->flear.segs = 9;
        g->flear.radius = 800.0f;
        g->flear.grow = 0.0f;
        g->flear.ir = g->flear.ig = g->flear.ib = 0xC0;
        g->flear.r = 0x80;
        g->flear.g = 0x20;
        g->flear.b = 0xA0;
        g->flear.alpha = 0xD0;
        g->flear.ox = g->flear.oy = g->flear.oz = 0.0f;
        g->flear.pos = v;
        func_00101AD0(&g->ring, 0x18, 0, 0xFF);
        g->ring.b4 = 0;
        g->ring.b5 = 0;
        g->ring.seg = 9;
        g->ring.type = 0;
        g->ring.scale = 2.5f;
        g->ring.base = 0.1f;
        g->ring.dy = 0.4f;
        g->ring.y = 0.0f;
        g->ring.vy = 0.05f;
        g->ring.r0 = g->ring.g0 = g->ring.b0 = g->ring.a0 = 0x80;
        g->ring.r1 = 0x80;
        g->ring.g1 = 0;
        g->ring.b1 = 0x20;
        g->ring.a1 = 0;
        g->ring.pos = v;
        if (i) {
            g->ring.rot[0] = 0x4000;
        } else {
            g->ring.rot[0] = -0x4000;
        }
        break;
    case 0xA4:
        return 8;
    }
    if (g->t >= 0x44 && g->t < 0x67 && (g->t & 3) == 0) {
        k = func_00101C30(g->ray, 0x68, 0x10);
        if (k >= 0) {
            func_00101AD0(&g->ray[k], 0x10, 0, 0xFF);
            g->ray[k].flags = 5;
            g->ray[k].size = 3.5f;
            g->ray[k].width = 16.0f;
            g->ray[k].b5 = 1;
            g->ray[k].b6 = g->m0;
            g->ray[k].texkind = 0;
            g->ray[k].texpage = 2;
            g->ray[k].texmode = 6;
            g->ray[k].segments = 0x5A;
            g->ray[k].index = func_0019A5C8() >> 4;
            g->ray[k].table = g->tbl;
            g->ray[k].radius = 1.0f;
            g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
            g->ray[k].a0 = 0x10;
            g->ray[k].a1 = 0x80;
            g->ray[k].spin[0] = 0x40;
            g->ray[k].spin[1] = 0x80;
            g->ray[k].spin[2] = 0x100;
        }
    }
    func_01E00080_b177((void *)&g->emit);
    func_001031C0(&g->wv, g->t);
    func_01E01E90_b177(&g->lnk, ot, 1);
    func_01E00440_b177((void *)g->ray, ot, 0x10);
    func_01E01170_b177((void *)&g->flear, ot, 1);
    func_01E02FC0_b177((void *)&g->lfl, ot, 1);
    func_01E041F0_b177((void *)&g->ring, ot, 1);
    if (g->t >= 0x64 && g->t < 0x81) {
        return 6;
    }
    switch (g->t) {
    case 0x5A:
        return 1;
    case 0x81:
        return 2;
    }
    return 0;
}

#pragma optimization_level reset
