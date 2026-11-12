#include "common.h"

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E00080, 226 insns, 89 copies: move an emitter (pos += vel) and set its level from the blend mode */

typedef struct Obj_b010_01E00080 {
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
} Obj_b010_01E00080;

#pragma optimization_level 2

static void func_01E00080_b461(Obj_b010_01E00080 *o) {
    extern s32 func_00101AF0();
    extern void func_00101BA0();
    extern void func_001F6C10();
    u8 d;
    u8 e;
    u8 a;
    s32 on;
    u8 n;
    f32 k;
    u8 m;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, &o->pos);
    a = o->b0;
    m = o->b3;
    d = a & m;
    n = o->b2;
    e = n - a;
    if (m == 0xFF) {
        k = o->base / n;
    } else {
        k = o->base / (m + 1);
    }
    on = 1;
    switch (o->b4 & 0xF) {
    case 1:
        o->level = k * d;
        break;
    case 2:
        if (m == 0xFF) {
            if (e < n >> 1) {
                k = 2.0f * k;
                o->level = k * e;
            } else {
                k = 2.0f * k;
                o->level = k * a;
            }
        } else {
            if (d < m >> 1) {
                k = 2.0f * k;
                o->level = k * (m - d);
            } else {
                k = 2.0f * k;
                o->level = k * d;
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
        if (a & 1) {
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

/* shape b035:01E00410 (ShFx_Flear01), 736 insns, 89 copies (-O2,p): draws each emitter of a list as a glowing ring: a
   fan of segs*4 triangles from the centre colour out to the edge colour, and unless flag 1 a textured band along the
   edge (two quads per slice); the radius grows each frame */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b035_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b035_01E00410;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b035_01E00410 xyz;
} Vtx1_b035_01E00410;

typedef struct {
    Hdr_b035_01E00410 h;
    Vtx1_b035_01E00410 v[3];
    u8 tail[8];
} Pkt1_b035_01E00410;

typedef struct {
    u64 st;
    Xyz_b035_01E00410 xyz;
} Vtx2_b035_01E00410;

typedef struct {
    Hdr_b035_01E00410 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b035_01E00410 v[4];
    u8 tail[0x20];
} Pkt2_b035_01E00410;

typedef struct {
    f32 x, y, z, w;
} V4_b035_01E00410;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b035_01E00410;

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
    V4_b035_01E00410 pos;
    V4_b035_01E00410 vel;
    V4_b035_01E00410 org;
} Obj_b035_01E00410;

#pragma optimization_level 2

static s32 func_01E00410_b461(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E04A80_b461;
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
    Obj_b035_01E00410 *o; /* a copy of obj: needed for the match (register order) */
    s32 k;
    s32 h __attribute__((aligned(16))); /* aligned: its spill slot, needed for the match */
    f32 m0[16];
    f32 m1[16];
    V4_b035_01E00410 org;
    Tex_b035_01E00410 t;
    Xyz_b035_01E00410 scr;
    Pkt1_b035_01E00410 p1 __attribute__((aligned(8)));
    Pkt2_b035_01E00410 p2 __attribute__((aligned(8)));
    f32 depth;
    s32 i;
    s32 segs;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    f32 v;
    f32 a;
    u8 d;

    o = obj;
    t = D_01E04A80_b461;
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
        segs = o->segs;
        segs = segs > 9 ? 9 : segs; /* this form for the match */
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
        ((Hdr_b035_01E00410 *)(s32)&p1)->count = 0x13;
        ((Hdr_b035_01E00410 *)(s32)&p1)->tag = 6;
        ((Hdr_b035_01E00410 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b035_01E00410 *)(s32)&p1)->pad = 0;
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
        ((Hdr_b035_01E00410 *)(s32)&p2)->count = 0x24;
        ((Hdr_b035_01E00410 *)(s32)&p2)->tag = 9;
        ((Hdr_b035_01E00410 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b035_01E00410 *)(s32)&p2)->pad = 0;
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
            a = 3.1415927f * (step * i) / 180.0f;
            x = r * func_001A6898(a);
            y = r * func_001A6A88(a);
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
            v = scr.y + py;
            p2.v[0].xyz.y = v - w;
            p2.v[2].xyz.y = w + v;
            v = scr.y + y;
            p2.v[1].xyz.y = v - w;
            p2.v[3].xyz.y = w + v;
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            px = scr.x + px; /* px reused as the temporary: needed for the match */
            p2.v[0].xyz.x = w + px;
            p2.v[2].xyz.x = px - w;
            px = scr.x + x;
            p2.v[1].xyz.x = w + px;
            p2.v[3].xyz.x = px - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* shape b532:01E00080 (ShFx_Ndl), 737 insns, 73 copies (-O2,p): a needle beam: per emitter a strip of quads from a
   point out along a table-driven path (or a circle of growing radius), each quad turned to face its direction; the
   source of shape b011:01E04380, built here at -O2 */

#define ABS_b532_01E00080(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b532_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b532_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b532_01E00080 p;
} Vtx_b532_01E00080;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b532_01E00080 v[4];
    u8 tail[0x20];
} Pkt_b532_01E00080;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b532_01E00080;

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
    Vec_b532_01E00080 pos;
    Vec_b532_01E00080 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b532_01E00080;

extern Tex_b532_01E00080 D_01E04AA0_b461;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E00F90_b461(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    Ray_b532_01E00080 *o;
    s32 i;
    u8 idx;
    s32 j;
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
    Xyz_b532_01E00080 xy[2];
    Vec_b532_01E00080 pt;
    Vec_b532_01E00080 d;
    Vec_b532_01E00080 tmp;
    Tex_b532_01E00080 tex0;
    Tex_b532_01E00080 tex;
    Pkt_b532_01E00080 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E04AA0_b461;
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
        ((Pkt_b532_01E00080 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b532_01E00080 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b532_01E00080 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b532_01E00080 *)(s32)&pkt)->pad = 0;
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
            if (ABS_b532_01E00080(xy[1].x - xy[0].x) > ABS_b532_01E00080(xy[1].y - xy[0].y)) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b461", func_01E01B20_b461);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E05740, 337 insns, 56 copies: full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b010_01E05740;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b010_01E05740;

typedef struct {
    Hdr_b010_01E05740 h;
    Vtx_b010_01E05740 v[4];
    u8 tail[8];
} Pkt_b010_01E05740;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b010_01E05740;

#pragma optimization_level 2

static s32 func_01E02670_b461(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
    Pkt_b010_01E05740 p __attribute__((aligned(8)));
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b010_01E05740 *)(s32)&p)->count = 0x14;
    ((Hdr_b010_01E05740 *)(s32)&p)->tag = 8;
    ((Hdr_b010_01E05740 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b010_01E05740 *)(s32)&p)->pad = 0;
    mode = o->flags;
    switch (mode & 7) {
    case 1:
        a = func_001A23B0(128.0f / o->max * o->cur);
        break;
    case 2:
        a = ((o->max - o->cur) << 7) / o->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (o->cur == 1 && (mode & 0x80)) {
        o->cur = o->max;
        if (o->flags & 1) {
            o->flags = 2;
        } else {
            o->flags = 1;
        }
    }
    if (o->flags & 8) {
        a >>= 1;
    }
    p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = 0xFF;
    p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g = 0xFF;
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = 0xFF;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        h = o->max >> 1;
        s = h;
        s = 7168.0f / s;
        d = o->max - o->cur;
        k = (0x80 / h) * (d >> 1);
        if (h < d) {
            p.v[0].a = p.v[1].a = k;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        w = s * d;
        p.v[0].y = p.v[1].y = func_001A23B0(32768.0f - w);
        p.v[2].y = p.v[3].y = func_001A23B0(32768.0f);
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = func_001A23B0(32768.0f);
        p.v[2].y = p.v[3].y = func_001A23B0(32768.0f + w);
        func_002075F0((s32)&p, tex, 0);
    } else {
        p.v[0].a = p.v[1].a = p.v[2].a = p.v[3].a = a;
        if (o->flags & 0x20) {
            p.v[2].a = p.v[3].a = 0;
        }
        if (o->flags & 0x40) {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = 0x7200;
        p.v[2].y = p.v[3].y = 0x8E00;
        func_002075F0((s32)&p, tex, 0);
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_WARM */
/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b063:01E03F30, 560 insns, 6 copies: b062:01E05220 at -O2 (seed steps before the speed store): moves n spark emitters (0x60 bytes each: position, velocity, turning angles,
   growing size and speed) and draws count square sprites per emitter, each pushed out from the emitter
   along a direction from its random table, scaled by the speed (optionally jittered); frame from age or
   fixed, alpha fading at the end. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b063_01E03F30;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 tc;
        Xyz_b063_01E03F30 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b063_01E03F30;

typedef struct {
    u8 pad0[5];
    u8 page;
    u8 pad6[2];
    s32 u, w, v, h;
    u8 pad18[8];
} Tex_b063_01E03F30;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 count;
    u8 seed;
    u8 texid;
    u8 frame;
    u8 bC;
    u8 bD;
    u8 padE[2];
    u8 *tbl;
    f32 speed;
    f32 dspeed;
    f32 rise;
    f32 size;
    f32 dsize;
    u8 b, g, r, a;
    s32 rot[4];
    f32 pos[3];
    f32 vel[3];
    f32 rv[3];
} Spark_b063_01E03F30;

#pragma optimization_level 2

static s32 func_01E02BC0_b461(void *arg0, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat2[16];
    f32 mat[16];
    f32 rm[16];
    Vec4f out;
    Vec4f p;
    Vec4f d;
    Tex_b063_01E03F30 td;
    Pkt_b063_01E03F30 pkt __attribute__((aligned(8)));
    f32 dep;
    Spark_b063_01E03F30 *e;
    s32 i;
    void *tex;
    u8 seed;
    s32 fr;
    s32 j;
    f32 sp;
    f32 h;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Spark_b063_01E03F30 *)((u8 *)e + 0x60);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        e->pos[0] += e->vel[0];
        e->pos[1] += e->vel[1];
        e->pos[2] += e->vel[2];
        e->rot[0] += e->rv[0];
        e->rot[1] += e->rv[1];
        e->rot[2] += e->rv[2];
        e->size += e->dsize;
        e->speed += e->dspeed;
        p.x = e->pos[0];
        p.y = e->pos[1];
        p.z = e->pos[2];
        func_00101BA0(e, &p);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &p);
        func_0020BC00(mat, mat2);
        seed = e->seed;
        fr = e->max - e->life;
        ((Pkt_b063_01E03F30 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b063_01E03F30 *)(s32)&pkt)->tag = 9;
        ((Pkt_b063_01E03F30 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b063_01E03F30 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        fr = (e->flags & 1) ? fr & 7 : e->frame;
        td.page = e->bD;
        func_001020B0(&td, fr, e->bC);
        func_00101D20(&pkt, &td, tex);
        pkt.a = e->a;
        if (!(e->flags & 0x40) && e->life < 8) {
            pkt.a = (e->a >> 3) * e->life;
        }
        p.x = p.y = p.z = 0.0f;
        for (j = 0; j < e->count; j++) {
            if (e->flags & 8) {
                sp = e->speed;
            } else {
                sp = e->speed * (e->tbl[seed++] / 255.0f);
                if (e->flags & 4) {
                    sp = 0.5f * (sp + e->speed);
                }
            }
            if (e->flags & 2) {
                d.x = e->tbl[seed] - e->tbl[seed + 1];
                d.z = e->tbl[seed + 2] - e->tbl[seed + 3];
                d.y = 0.0f;
                seed += 4;
                p.x = sp;
            } else {
                d.x = e->tbl[seed] - e->tbl[seed + 1];
                d.z = e->tbl[seed + 2] - e->tbl[seed + 3];
                d.y = e->tbl[seed + 4] - e->tbl[seed + 5];
                seed += 6;
                p.y = sp;
            }
            func_00101A00(&d, rm);
            func_0020CDD0(&out, rm, &p);
            if (e->flags & 2) {
                out.y += (e->rise * e->tbl[seed++]) / 255.0f;
            }
            if (func_00205440(&out, mat, &pkt.v[0].p, &dep) == 0) {
                continue;
            }
            if (func_00101600(&pkt.v[0].p) == 0) {
                continue;
            }
            h = func_001018E0(e->size, dep);
            pkt.v[1].p.x = pkt.v[0].p.x + h;
            pkt.v[1].p.y = pkt.v[0].p.y - h;
            pkt.v[2].p.x = pkt.v[0].p.x - h;
            pkt.v[2].p.y = pkt.v[0].p.y + h;
            pkt.v[3].p.x = pkt.v[0].p.x + h;
            pkt.v[3].p.y = pkt.v[0].p.y + h;
            pkt.v[0].p.x = pkt.v[0].p.x - h;
            pkt.v[0].p.y = pkt.v[0].p.y - h;
            pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = pkt.v[0].p.z;
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
            func_002075F0(&pkt, ot, (u32)dep);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b461:01E03480 (b461), 1377 insns, 1 copy (-O2,p): the b461 module main: code >= 0 clears the scene, takes
   both units and two joints; else counts the frame: 2 the light, 50 six bolt lines from the joint, 170 a big flare,
   190 the fade, the glow and six bolt lines through the target, 350 ends; frames 2..139 bolts and a flare at the
   joint, 2..49 sparks, rays every other frame 170..327, frames 190..326 flares and rays near the target; steps every
   effect; returns 6 on frames 190..326, 1/2 on frames 180/327 */

typedef struct {
    u8 count;
    u8 pad1;
    u8 len;
    u8 mask;
    u8 mode;
    u8 b5;
    u8 b6;
    u8 pad7[0xD];
    f32 sx, sy, sz;
    Vec4f pos;
    f32 f70;
    f32 f74;
    u8 pad78[0x18];
    f32 f90;
    u8 pad94[0xC];
} Fx_b461_01E03480;

typedef struct {
    f32 x, y, z;
} Vec3_b461_01E03480;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 mode;
    u8 pad6[2];
    u8 nseg;
    u8 sel0;
    u8 sel1;
    u8 texid;
    u8 texsel;
    u8 wdiv;
    u8 padE[2];
    f32 jitter;
    f32 grow;
    u8 b, g, r, a;
    Vec3_b461_01E03480 p0;
    Vec3_b461_01E03480 p1;
    Vec3_b461_01E03480 vel;
} Bolt_b461_01E03480;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b461_01E03480 a;
    Vec3_b461_01E03480 b;
    Vec3_b461_01E03480 *pts;
} Line_b461_01E03480;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    u8 pad14[0x18];
    u8 cam[0x14];
    Fx_b461_01E03480 fx;
    s16 wv[2];
    Ray_b532_01E00080 ray[0x3C];
    Obj_b035_01E00410 flear[0x18];
    Bolt_b461_01E03480 bolt[0x64];
    Spark_b063_01E03F30 spark[0x50];
    Obj_b010_01E05740 fade;
    u8 pad5729[3];
    u8 tbl[0x100];
    u8 pad582C[4];
} Scene_b461_01E03480;

#pragma optimization_level 2

static s32 func_01E03480_b461(Scene_b461_01E03480 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_00102A50(void *);
    extern s32 func_01E02670_b461();
    extern s32 func_01E01B20_b461();
    s32 ot;
    Vec4f v;
    Vec4f p;
    Vec4f q[2];
    Line_b461_01E03480 line;
    Vec3_b461_01E03480 pts[17];
    s32 i;
    s32 k;
    s32 j;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x5830);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 1, 1);
        g->m1 = func_001F5560(g->unitA, 0x2A, 0);
        g->wv[0] = 2;
        g->wv[1] = 0x158;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 2:
        func_00101AD0(&g->fx, 0xFA, 0, 0xFF);
        g->fx.b5 = 1;
        g->fx.b6 = g->m1;
        g->fx.mode = 8;
        g->fx.sx = 1.0f;
        g->fx.sy = 1.8f;
        g->fx.sz = 1.8f;
        g->fx.f70 = 0.0f;
        g->fx.f74 = 40.0f;
        g->fx.f90 = 4.0f;
        break;
    case 0x32:
        for (j = 0; j < 6; j++) {
            func_001F5620(g->unitA, g->m0, &q[0]);
            q[1] = q[0];
            q[0].y += 80.0f;
            q[1].y -= 15.0f;
            switch (j) {
            case 0:
                q[0].x -= 8.0f;
                q[1].x -= 8.0f;
                break;
            case 1:
                q[0].x += 8.0f;
                q[1].x += 8.0f;
                break;
            case 2:
                q[0].z -= 8.0f;
                q[1].z -= 8.0f;
                break;
            case 3:
                q[0].z += 8.0f;
                q[1].z += 8.0f;
                break;
            case 4:
                q[0].x += 6.0f;
                q[1].x += 6.0f;
                q[0].z += 6.0f;
                q[1].z += 6.0f;
                break;
            case 5:
                q[0].x -= 6.0f;
                q[1].x -= 6.0f;
                q[0].z -= 6.0f;
                q[1].z -= 6.0f;
                break;
            }
            line.n = 5;
            line.jitter = 0.4f;
            line.pts = pts;
            line.a.x = q[0].x;
            line.a.y = q[0].y;
            line.a.z = q[0].z;
            line.b.x = q[1].x;
            line.b.y = q[1].y;
            line.b.z = q[1].z;
            func_00102A50(&line);
            for (i = 0; i < 5; i++) {
                k = func_00101C30(g->bolt, 0x40, 0x64);
                if (k < 0) {
                    break;
                }
                func_00101AD0(&g->bolt[k], 0x8C, j & 1, 0xFF);
                g->bolt[k].mode = 0;
                g->bolt[k].flags = 0;
                g->bolt[k].p0 = pts[i];
                g->bolt[k].p1 = pts[i + 1];
                g->bolt[k].nseg = 6;
                g->bolt[k].jitter = 1.0f;
                g->bolt[k].grow = 0.3f;
                g->bolt[k].texid = 1;
                g->bolt[k].wdiv = 4;
                g->bolt[k].texsel = 0;
                g->bolt[k].b = 0x80;
                g->bolt[k].g = 0x80;
                g->bolt[k].r = 0x80;
                g->bolt[k].a = 0x30;
            }
        }
        break;
    case 0xAA:
        k = func_00101C30(g->flear, 0x4C, 0x18);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x20, 0, 0xFF);
            g->flear[k].pad5[0] = 0;
            g->flear[k].flags = 3;
            g->flear[k].segs = 9;
            g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xD0;
            g->flear[k].r = 0;
            g->flear[k].g = 0x40;
            g->flear[k].b = 0x80;
            g->flear[k].grow = 0.0f;
            g->flear[k].radius = 500.0f;
            g->flear[k].grow = 180.0f;
            g->flear[k].pos = *(V4_b035_01E00410 *)&v;
            g->flear[k].pos.y += 80.0f;
        }
        break;
    case 0xBE:
        func_00101AD0(&g->fade, 0x18, 0, 0xFF);
        g->fade.flags = 1;
        func_00101AD0(&g->fx, 0x8C, 0, 0xFF);
        g->fx.b5 = 0;
        g->fx.mode = 8;
        g->fx.sx = 1.0f;
        g->fx.sy = 1.8f;
        g->fx.sz = 1.8f;
        g->fx.f70 = 0.0f;
        g->fx.f74 = 160.0f;
        g->fx.pos = v;
        g->fx.f90 = 8.0f;
        g->fx.pos.z = 0.0f;
        for (j = 0; j < 6; j++) {
            q[1] = v;
            q[0] = q[1];
            q[0].y += 80.0f;
            q[1].y -= 60.0f;
            switch (j) {
            case 0:
                q[0].x -= 18.0f;
                q[1].x -= 18.0f;
                break;
            case 1:
                q[0].x += 18.0f;
                q[1].x += 18.0f;
                break;
            case 2:
                q[0].z -= 18.0f;
                q[1].z -= 18.0f;
                break;
            case 3:
                q[0].z += 18.0f;
                q[1].z += 18.0f;
                break;
            case 4:
                q[0].x += 10.0f;
                q[1].x += 10.0f;
                q[0].z += 10.0f;
                q[1].z += 10.0f;
                break;
            case 5:
                q[0].x -= 10.0f;
                q[1].x -= 10.0f;
                q[0].z -= 10.0f;
                q[1].z -= 10.0f;
                break;
            }
            line.n = 5;
            line.jitter = 0.4f;
            line.pts = pts;
            line.a.x = q[0].x;
            line.a.y = q[0].y;
            line.a.z = q[0].z;
            line.b.x = q[1].x;
            line.b.y = q[1].y;
            line.b.z = q[1].z;
            func_00102A50(&line);
            for (i = 0; i < 5; i++) {
                k = func_00101C30(g->bolt, 0x40, 0x64);
                if (k < 0) {
                    break;
                }
                func_00101AD0(&g->bolt[k], 0x8C, j & 1, 0xFF);
                g->bolt[k].mode = 0;
                g->bolt[k].flags = 0;
                g->bolt[k].p0 = pts[i];
                g->bolt[k].p1 = pts[i + 1];
                g->bolt[k].nseg = 6;
                g->bolt[k].jitter = 1.0f;
                g->bolt[k].grow = 0.3f;
                g->bolt[k].texid = 1;
                g->bolt[k].wdiv = 4;
                g->bolt[k].texsel = 0;
                g->bolt[k].b = 0x80;
                g->bolt[k].g = 0x80;
                g->bolt[k].r = 0x80;
                g->bolt[k].a = 0x30;
            }
        }
        break;
    case 0x15E:
        return 8;
    }
    if (g->t >= 2 && g->t < 0x8C) {
        func_001F5620(g->unitA, g->m0, &q[0]);
        q[1].x = q[0].x + (f32)((func_0019A5C8() >> 4) % 1600 - 800) / 100.0f;
        q[1].y = q[0].y + (f32)((func_0019A5C8() >> 4) % 1600 - 800) / 100.0f;
        q[1].z = q[0].z + (f32)((func_0019A5C8() >> 4) % 1600 - 800) / 100.0f;
        for (i = 0; i < 2; i++) {
            k = func_00101C30(g->bolt, 0x40, 0x64);
            if (k < 0) {
                break;
            }
            func_00101AD0(&g->bolt[k], 0xE, (u8)i, 0xFF);
            g->bolt[k].mode = 0;
            g->bolt[k].flags = 0;
            g->bolt[k].p0.x = g->bolt[k].p1.x = q[1].x;
            g->bolt[k].p0.y = g->bolt[k].p1.y = q[1].y;
            g->bolt[k].p0.z = g->bolt[k].p1.z = q[1].z;
            g->bolt[k].p1.x += (f32)((func_0019A5C8() >> 4) % 6 * 200 - 600) / 100.0f;
            g->bolt[k].p1.y += (f32)((func_0019A5C8() >> 4) % 6 * 200 - 600) / 100.0f;
            g->bolt[k].p1.z += (f32)((func_0019A5C8() >> 4) % 6 * 200 - 600) / 100.0f;
            g->bolt[k].nseg = 5;
            g->bolt[k].jitter = 1.0f;
            g->bolt[k].grow = 0.4f;
            g->bolt[k].texid = 1;
            g->bolt[k].wdiv = 4;
            g->bolt[k].texsel = 0;
            g->bolt[k].b = 0x80;
            g->bolt[k].g = 0x80;
            g->bolt[k].r = 0x80;
            g->bolt[k].a = 0x30;
        }
        k = func_00101C30(g->flear, 0x4C, 0x18);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0xC, 0, 0xFF);
            g->flear[k].pad5[0] = 0;
            g->flear[k].flags = 5;
            g->flear[k].segs = 9;
            g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xD0;
            g->flear[k].r = 0;
            g->flear[k].g = 0;
            g->flear[k].b = 0x80;
            g->flear[k].grow = 0.0f;
            g->flear[k].radius = 200.0f;
            g->flear[k].grow = 0.0f;
            g->flear[k].pos = *(V4_b035_01E00410 *)&q[1];
        }
    }
    if (g->t >= 2 && g->t < 0x32) {
        func_001F5620(g->unitA, g->m0, &q[0]);
        k = func_00101C30(g->spark, 0x60, 0x50);
        if (k >= 0) {
            func_00101AD0(&g->spark[k], 0x20, 0, 0xFF);
            g->spark[k].pad5[0] = 0;
            g->spark[k].flags = 2;
            g->spark[k].seed = func_0019A5C8() >> 4;
            g->spark[k].texid = 0;
            g->spark[k].frame = func_0019A5C8() >> 4 & 7;
            g->spark[k].bC = 0;
            g->spark[k].bD = 2;
            g->spark[k].tbl = g->tbl;
            g->spark[k].dsize = 0.0f;
            g->spark[k].b = 0x80;
            g->spark[k].g = 0x80;
            g->spark[k].r = 0x80;
            g->spark[k].a = 0x60;
            g->spark[k].pos[0] = q[0].x;
            g->spark[k].pos[1] = q[0].y - 15.0f;
            g->spark[k].pos[2] = q[0].z;
            g->spark[k].count = 6;
            g->spark[k].rise = 20.0f;
            g->spark[k].speed = 10.0f + (f32)((func_0019A5C8() >> 4) % 2 * 200 - 200) / 100.0f;
            g->spark[k].size = 25.0f;
            g->spark[k].vel[1] = 0.5f + (f32)((func_0019A5C8() >> 4) % 80 - 40) / 100.0f;
        }
    }
    if (g->t >= 0xAA && g->t < 0x148 && !(g->t & 1)) {
        for (j = 0; j < 2; j++) {
            k = func_00101C30(g->ray, 0x68, 0x3C);
            if (k < 0) {
                continue;
            }
            func_00101AD0(&g->ray[k], 0x10, 0, 0xFF);
            g->ray[k].flags = 5;
            g->ray[k].size = 15.0f;
            g->ray[k].width = 100.0f;
            g->ray[k].segments = 0x18;
            g->ray[k].pad05[0] = 0;
            g->ray[k].texkind = 0;
            g->ray[k].texpage = 2;
            g->ray[k].texmode = 3;
            g->ray[k].index = func_0019A5C8() >> 4;
            g->ray[k].table = g->tbl;
            g->ray[k].radius = 1.0f;
            g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
            g->ray[k].a0 = 0x10;
            g->ray[k].a1 = 0x40;
            g->ray[k].spin[0] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].spin[1] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].spin[2] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].pos = *(Vec_b532_01E00080 *)&v;
            g->ray[k].pos.y += 80.0f;
        }
    }
    if (g->t >= 0xBE && g->t < 0x147) {
        for (i = 0; i < 4; i++) {
            p.x = v.x + (f32)((func_0019A5C8() >> 4) % 2800 - 1400) / 100.0f;
            p.y = v.y + (f32)((func_0019A5C8() >> 4) % 2800 - 1400) / 100.0f;
            p.z = v.z + (f32)((func_0019A5C8() >> 4) % 2800 - 1400) / 100.0f;
            k = func_00101C30(g->flear, 0x4C, 0x18);
            if (k >= 0) {
                func_00101AD0(&g->flear[k], 0xC, 0, 0xFF);
                g->flear[k].pad5[0] = 0;
                g->flear[k].flags = 1;
                g->flear[k].segs = 9;
                g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xD0;
                g->flear[k].r = 0;
                g->flear[k].g = 0;
                g->flear[k].b = 0x80;
                g->flear[k].grow = 0.0f;
                g->flear[k].radius = 300.0f;
                g->flear[k].grow = 0.0f;
                g->flear[k].pos = *(V4_b035_01E00410 *)&p;
            }
            k = func_00101C30(g->ray, 0x68, 0x3C);
            if (k >= 0) {
                g->ray[k].flags = 5;
                func_00101AD0(&g->ray[k], 8, 0, 0xFF);
                g->ray[k].size = 5.0f;
                g->ray[k].width = 40.0f;
                g->ray[k].a1 = 0x80;
                g->ray[k].a0 = 0;
                g->ray[k].pad05[0] = 0;
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 3;
                g->ray[k].segments = 0x28;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 1.0f;
                g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
                g->ray[k].pos = *(Vec_b532_01E00080 *)&p;
            }
        }
    }
    func_01E00080_b461((Obj_b010_01E00080 *)&g->fx);
    func_001031C0(g->wv, g->t);
    func_01E02670_b461(&g->fade, ot);
    func_01E00410_b461(g->flear, ot, 0x18);
    func_01E00F90_b461(g->ray, ot, 0x3C);
    func_01E01B20_b461(g->bolt, ot, 0x64);
    func_01E02BC0_b461(g->spark, ot, 0x50);
    if (g->t >= 0xBE && g->t < 0x147) {
        return 6;
    }
    switch (g->t) {
    case 0xB4:
        return 1;
    case 0x147:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
