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

static void func_01E00080_b398(Obj_b010_01E00080 *o) {
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b173:01E02070, 569 insns, 7 copies: the -O2 twin of b051:01E00DF0 (squares inline, not hoisted): draws n shell emitters (0x54 bytes each, family of b059:01E00440 / b032:01E02820):
   a half circle of up to 2*9 segments of radius b, and two arched rows above it (heights sqrt(a^2 (1 - x^2/b^2)) and
   the same for the radius 80% of the way from b to a), optionally spun by e->ang; each segment is two untextured
   gouraud quads (outer arch to inner arch, then the base circle to the inner arch's lower edge). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b173_01E02070;

typedef struct {
    u8 r, g, b, a;
    s32 pad4;
    Xyz_b173_01E02070 xyz;
} Vtx_b173_01E02070;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b173_01E02070 v[4];
    u8 tail[8];
} Pkt_b173_01E02070;

typedef struct {
    u8 b, g, r, a;
} Col_b173_01E02070;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 seg;
    Col_b173_01E02070 c0;
    Col_b173_01E02070 c1;
    f32 r;
    f32 k;
    f32 dr;
    s32 ang;
    s32 dang;
    Vec4f pos;
    Vec4f vel;
    Vec4f rot;
} Emit_b173_01E02070;

#pragma optimization_level 2

static s32 func_01E00410_b398(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    f32 mat2[16];
    f32 mat[16];
    f32 rmat[16];
    Vec4f pts[3][19];
    Vec4f tmp;
    s32 rv[4];
    f32 depth[4];
    Emit_b173_01E02070 *e;
    s32 i;
    s32 j;
    s32 nseg;
    f32 step;
    f32 sn;
    f32 cs;
    f32 x;
    f32 rm;
    f32 ra;
    f32 dep;
    f32 ang;
    f32 rb;
    Pkt_b173_01E02070 pkt __attribute__((aligned(8)));

    e = arg0;
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
        e->r += e->dr;
        e->ang += e->dang;
        if (e->seg > 9) {
            nseg = 9;
        } else {
            nseg = e->seg;
        }
        step = 90.0f / nseg;
        if (e->k < 1.0f) {
            ra = e->r;
            rb = ra * e->k;
        } else {
            rb = e->r;
            ra = rb * e->k;
        }
        rm = rb + 0.8f * (ra - rb);
        if (e->ang != 0) {
            rv[0] = rv[2] = 0;
            rv[1] = e->ang;
            func_0020C940(rmat, NULL, rv, NULL);
        }
        for (j = 0; j < nseg * 2 + 1; j++) {
            ang = 3.1415927f * (step * j) / 180.0f;
            sn = func_001A6A88(ang);
            cs = func_001A6898(ang);
            x = rb * cs;
            pts[0][j].x = x;
            pts[0][j].y = rb * sn;
            pts[0][j].z = 0.0f;
            pts[1][j].x = x;
            pts[1][j].y = func_001A6C60(ra * ra * (1.0f - x * x / (rb * rb)));
            pts[1][j].z = 0.0f;
            pts[2][j].x = x;
            pts[2][j].y = func_001A6C60(rm * rm * (1.0f - x * x / (rb * rb)));
            pts[2][j].z = 0.0f;
            if (e->ang != 0) {
                func_0020CDD0(&tmp, rmat, &pts[0][j]);
                pts[0][j] = tmp;
                func_0020CDD0(&tmp, rmat, &pts[1][j]);
                pts[1][j] = tmp;
                func_0020CDD0(&tmp, rmat, &pts[2][j]);
                pts[2][j] = tmp;
            }
        }
        ((Pkt_b173_01E02070 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b173_01E02070 *)(s32)&pkt)->tag = 8;
        ((Pkt_b173_01E02070 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b173_01E02070 *)(s32)&pkt)->pad = 0;
        func_002086D0(&pkt, 0x48);
        pkt.v[2].a = pkt.v[3].a = e->c1.a;
        pkt.v[0].a = pkt.v[1].a = e->c0.a;
        if (!(e->flags & 0x40) && e->life < 8) {
            pkt.v[2].a = pkt.v[3].a = (e->c1.a >> 3) * e->life;
            pkt.v[0].a = pkt.v[1].a = (e->c0.a >> 3) * e->life;
        }
        if ((e->flags & 1) && e->span - e->life < 8) {
            pkt.v[2].a = pkt.v[3].a = (e->c1.a >> 3) * (e->span - e->life + 1);
            pkt.v[0].a = pkt.v[1].a = (e->c0.a >> 3) * (e->span - e->life + 1);
        }
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        for (j = 0; j < nseg * 2; j++) {
            if (func_00205440(&pts[1][j], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                func_00205440(&pts[1][j + 1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                func_00205440(&pts[2][j], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                func_00205440(&pts[2][j + 1], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    dep = 0.0f;
                } else {
                    dep = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
                }
                func_002075F0((s32)&pkt, ot, (u32)dep);
                if (func_00205440(&pts[0][j], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                    func_00205440(&pts[0][j + 1], mat, &pkt.v[1].xyz, &depth[1]) != 0) {
                    pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                    if (e->flags & 0x80) {
                        pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                        dep = 0.0f;
                    } else {
                        dep = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
                    }
                    func_002075F0((s32)&pkt, ot, (u32)dep);
                }
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

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

static s32 func_01E00D00_b398(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
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

extern Tex_b532_01E00080 D_01E06E80_b398;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E01250_b398(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    tex0 = D_01E06E80_b398;
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

INCLUDE_ASM("asm/nonmatchings/mod/b398", func_01E01DE0_b398);

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

static s32 func_01E027F0_b398(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E06EC0_b398;
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
    t = D_01E06EC0_b398;
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b095:01E02120, 345 insns, 17 copies: draws n billboards (0x3C-byte emitters): a quad that shrinks with age
   and grows along y, turned by the emitter's rotation at its position, perspective STQ, texture frame from
   func_001020B0, blend from func_00101C80 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b095_01E02120;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b095_01E02120 xyz;
} Vtx_b095_01E02120;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b095_01E02120 v[4];
    u8 tail[0x20];
} Pkt_b095_01E02120;

typedef struct {
    u8 pad0[5];
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b095_01E02120;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 texid;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 b, g, r, a;
    f32 r0;
    f32 w0;
    f32 dw;
    Vec4f rot;
    Vec4f pos;
} Emit_b095_01E02120;

#pragma optimization_level 2

static s32 func_01E03370_b398(void *arg0, s32 ot, s32 n) {
    extern void func_001020B0();
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat[16];
    f32 mat2[16];
    Vec4f c[4];
    f32 depth[4];
    Tex_b095_01E02120 td;
    Pkt_b095_01E02120 pkt __attribute__((aligned(8)));
    u8 bl[4];
    Emit_b095_01E02120 *e;
    s32 i;
    void *tex;
    s32 d;
    f32 r0;
    f32 h;
    f32 w;
    s32 life;
    f32 q1;
    f32 q2;
    f32 q3;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        d = e->max - e->life;
        r0 = e->r0;
        h = r0 - d * (r0 / e->max);
        w = e->w0 + e->dw * d;
        c[0].z = c[1].z = c[2].z = c[3].z = 0.0f;
        c[0].x = c[2].x = -h;
        c[1].x = c[3].x = h;
        c[0].y = c[1].y = -w;
        c[2].y = c[3].y = w;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, &e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b095_01E02120 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b095_01E02120 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b095_01E02120 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b095_01E02120 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        life = e->life;
        if (!(e->flags & 0x40) && life < 8) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (e->a >> 3) * life;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        }
        if (func_00205440(&c[0], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
            func_00205440(&c[1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
            func_00205440(&c[2], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
            func_00205440(&c[3], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
            td.b5 = e->bB;
            func_001020B0(&td, e->bA, e->b9);
            pkt.v[0].q = 1.0f / depth[0];
            q1 = 1.0f / depth[1];
            pkt.v[1].q = q1;
            q2 = 1.0f / depth[2];
            pkt.v[2].q = q2;
            q3 = 1.0f / depth[3];
            pkt.v[3].q = q3;
            pkt.v[0].s = 0.0f;
            pkt.v[0].t = 0.0f;
            pkt.v[1].s = q1;
            pkt.v[1].t = 0.0f;
            pkt.v[2].s = 0.0f;
            pkt.v[2].t = q2;
            pkt.v[3].s = q3;
            pkt.v[3].t = q3;
            func_00208CB0(&pkt, (u64)0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            func_00101C80(&td, bl);
            func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
            func_00208700(&pkt, tex, 1);
            if (e->flags & 0x80) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                z = 0.0f;
            } else {
                z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
            }
            func_002075F0((s32)&pkt, ot, (u32)z);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E04D20, 646 insns, 49 copies: update and draw a pool of particles (0x44 bytes each): move,
   floor bounce, colour and frame, project, then one textured sprite whose corners follow the flip bits */

typedef struct Part_b010_01E04D20 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 frame;
    u8 anim;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    f32 grow;
    f32 grav;
    f32 floor;
    f32 pos[3];
    f32 vel[3];
    f32 acc[3];
} Part_b010_01E04D20;

typedef struct Xyz_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b010_01E04D20;

typedef struct Pk_b010_01E04D20 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b010_01E04D20 v[4];
    u64 pad60[3];
} Pk_b010_01E04D20;

typedef struct Buf_b010_01E04D20 {
    u64 tag;
    Pk_b010_01E04D20 pk;
} Buf_b010_01E04D20;

typedef struct Uvs_b010_01E04D20 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b010_01E04D20;

typedef struct Scr_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b010_01E04D20;

static inline void b010_01E04D20_tag(Pk_b010_01E04D20 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E038E0_b398(Part_b010_01E04D20 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b010_01E04D20 *p = arg0;
    s32 i;
    s32 tex;
    s32 life;
    s32 frame;
    f32 half;
    f32 zf;
    u16 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b010_01E04D20 uvs;
    Pk_b010_01E04D20 pk __attribute__((aligned(8)));
    Scr_b010_01E04D20 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->vel[0] += p->acc[0];
        p->vel[1] += p->acc[1] + p->grav;
        p->vel[2] += p->acc[2];
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->size += p->grow;
        if (p->pos[1] < p->floor) {
            p->pos[1] = p->floor;
            if (p->flags & 2) {
                p->vel[1] = -(0.7f * p->vel[1]);
            }
        }
        if (p->follow != 0) {
            func_00101BA0(p, &tmp);
            p->pos[0] = tmp.x;
            p->pos[1] = tmp.y;
            p->pos[2] = tmp.z;
        }
        pos.x = p->pos[0];
        pos.y = p->pos[1];
        pos.z = p->pos[2];
        func_0020EB40(m);
        ((Pk_b010_01E04D20 *)(u32)&pk)->flags = 0x24;
        ((Pk_b010_01E04D20 *)(u32)&pk)->size = 9;
        ((Pk_b010_01E04D20 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b010_01E04D20 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        life = p->life - p->age;
        frame = p->frame;
        if (p->flags & 1) {
            frame = (u8)func_001022D0(p->anim, life);
            if (p->flags & 4) {
                p->flags &= 0xCF;
                p->flags |= (u8)(((func_0019A5C8() >> 4) & 3) << 4);
            }
        }
        uvs.b5 = p->bB;
        func_001020B0(&uvs, frame, p->anim);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 0x10) {
            pk.a = (p->a >> 4) * p->age;
        }
        if (func_00205440(&pos, m, &scr, &depth) == 0) {
            continue;
        }
        if (func_00101600(&scr) == 0) {
            continue;
        }
        half = func_001018E0(p->size, depth);
        if (p->flags & 0x80) {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
            zf = depth;
        }
        switch (p->flags & 0x30) {
        case 0x10:
            c = scr.x;
            pk.v[0].x = pk.v[1].x = (u32)(c - half);
            pk.v[2].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[1].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[2].y = (u32)(c + half);
            break;
        case 0x20:
            c = scr.x;
            pk.v[1].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[2].x = (u32)(c + half);
            c = scr.y;
            pk.v[2].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[1].y = (u32)(c + half);
            break;
        case 0x30:
            c = scr.x;
            pk.v[2].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[1].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[2].y = (u32)(c - half);
            pk.v[1].y = pk.v[3].y = (u32)(c + half);
            break;
        default:
            c = scr.x;
            pk.v[0].x = pk.v[2].x = (u32)(c - half);
            pk.v[1].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[1].y = (u32)(c - half);
            pk.v[2].y = pk.v[3].y = (u32)(c + half);
            break;
        }
        func_002075F0((s32)&pk, id, (u32)(zf));
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b398", func_01E04300_b398);

INCLUDE_ASM("asm/nonmatchings/mod/b398", func_01E05120_b398);

/* shape b398:01E05600 (ShFx_ReqBlur2), 427 insns, 1 copy (-O2,p): screen blur quads: two textured full-width bands
   (rows 0..h and h..448) at x offsets x0 and x1, alpha fading in over fade frames from start and out over 2*fade
   before end */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b398_01E05600;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b398_01E05600;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b398_01E05600 uv;
    Xyz_b398_01E05600 xyz;
} Vtx_b398_01E05600;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b398_01E05600 v[4];
    u8 tail[0x20];
} Pkt_b398_01E05600;

typedef struct {
    s32 id;
    u8 sub;
    u8 blend;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b398_01E05600;

typedef struct {
    u16 start;
    u16 end;
    u8 pad4;
    u8 fade;
    u8 blend;
    u8 pad7;
    s32 h;
    s32 x0;
    s32 x1;
    f32 depth;
    u8 b, g, r;
} Blur_b398_01E05600;

#pragma optimization_level 2

static s32 func_01E05600_b398(Blur_b398_01E05600 *o, s32 ot, u16 t) {
    extern void func_002075F0(void *, s32, s32);
    extern void func_00101C80(void *, u8 *);
    Tex_b398_01E05600 td;
    Pkt_b398_01E05600 pk __attribute__((aligned(8)));
    u8 bl[4];
    u8 a;
    s32 d;

    if (t >= o->start && t <= o->end) {
        ((Pkt_b398_01E05600 *)(s32)&pk)->count = 0x34;
        ((Pkt_b398_01E05600 *)(s32)&pk)->tag = 0xC;
        ((Pkt_b398_01E05600 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b398_01E05600 *)(s32)&pk)->pad = 0;
        func_002087A0(&pk, 1);
        pk.v[0].r = pk.v[1].r = pk.v[2].r = pk.v[3].r = o->r;
        pk.v[0].g = pk.v[1].g = pk.v[2].g = pk.v[3].g = o->g;
        pk.v[0].b = pk.v[1].b = pk.v[2].b = pk.v[3].b = o->b;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[1].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
        pk.v[0].xyz.f = pk.v[1].xyz.f = pk.v[2].xyz.f = pk.v[3].xyz.f = 0;
        d = t - o->start;
        a = o->fade << 4;
        if (d < o->fade) {
            a = d << 4;
        }
        if (o->end - t < o->fade * 2) {
            a = (o->end - t) << 3;
        }
        pk.v[0].a = pk.v[1].a = pk.v[2].a = pk.v[3].a = a;
        td.blend = o->blend;
        func_00101C80(&td, bl);
        func_002086D0(&pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        ((Pkt_b398_01E05600 *)(s32)&pk)->count |= 0x800;
        ((Uv_b398_01E05600 *)(s32)&pk.v[0].uv)->u = 0;
        ((Uv_b398_01E05600 *)(s32)&pk.v[0].uv)->v = 0;
        ((Uv_b398_01E05600 *)(s32)&pk.v[1].uv)->u = 0x2800;
        ((Uv_b398_01E05600 *)(s32)&pk.v[1].uv)->v = 0;
        ((Uv_b398_01E05600 *)(s32)&pk.v[2].uv)->u = 0;
        ((Uv_b398_01E05600 *)(s32)&pk.v[2].uv)->v = o->h << 4;
        ((Uv_b398_01E05600 *)(s32)&pk.v[3].uv)->u = 0x2800;
        ((Uv_b398_01E05600 *)(s32)&pk.v[3].uv)->v = o->h << 4;
        pk.v[0].xyz.x = (u32)(27648.0f + (o->x0 << 4));
        pk.v[1].xyz.x = (u32)(37888.0f + (o->x0 << 4));
        pk.v[2].xyz.x = (u32)(27648.0f + (o->x0 << 4));
        pk.v[3].xyz.x = (u32)(37888.0f + (o->x0 << 4));
        pk.v[0].xyz.y = pk.v[1].xyz.y = 0x7200;
        pk.v[2].xyz.y = pk.v[3].xyz.y = (u32)(29184.0f + (o->h << 4));
        func_002075F0(&pk, ot, (u32)o->depth);
        ((Uv_b398_01E05600 *)(s32)&pk.v[0].uv)->u = 0;
        ((Uv_b398_01E05600 *)(s32)&pk.v[0].uv)->v = o->h << 4;
        ((Uv_b398_01E05600 *)(s32)&pk.v[1].uv)->u = 0x2800;
        ((Uv_b398_01E05600 *)(s32)&pk.v[1].uv)->v = o->h << 4;
        ((Uv_b398_01E05600 *)(s32)&pk.v[2].uv)->u = 0;
        ((Uv_b398_01E05600 *)(s32)&pk.v[2].uv)->v = 0x1C00;
        ((Uv_b398_01E05600 *)(s32)&pk.v[3].uv)->u = 0x2800;
        ((Uv_b398_01E05600 *)(s32)&pk.v[3].uv)->v = 0x1C00;
        pk.v[0].xyz.x = (u32)(27648.0f + (o->x1 << 4));
        pk.v[1].xyz.x = (u32)(37888.0f + (o->x1 << 4));
        pk.v[2].xyz.x = (u32)(27648.0f + (o->x1 << 4));
        pk.v[3].xyz.x = (u32)(37888.0f + (o->x1 << 4));
        pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f + (o->h << 4));
        pk.v[2].xyz.y = pk.v[3].xyz.y = 0x8E00;
        func_002075F0(&pk, ot, (u32)o->depth);
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b268:01E03E40, 102 insns, 2 copies: a full-screen tint: between its start and end frame draws one flat sprite over
   the whole screen in its colour, depth from its own value */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b268_01E03E40;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b268_01E03E40 p0;
    Xyz_b268_01E03E40 p1;
} Pkt_b268_01E03E40;

typedef struct {
    u16 start;
    u16 end;
    u8 pad4[4];
    f32 depth;
    u8 b, g, r, a;
} Tint_b268_01E03E40;

#pragma optimization_level 2

static s32 func_01E05CB0_b398(Tint_b268_01E03E40 *o, s32 ctx2, u16 t) {
    extern s32 func_00207F60(void);
    extern u64 func_00208D00(s32);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00207FD0(s32, s32, s32);
    Pkt_b268_01E03E40 pkt;
    s32 ctx;

    ctx = func_00207F60();
    if (t >= o->start && t <= o->end) {
        ((Pkt_b268_01E03E40 *)(s32)&pkt)->count = 6;
        ((Pkt_b268_01E03E40 *)(s32)&pkt)->tag = 3;
        ((Pkt_b268_01E03E40 *)(s32)&pkt)->regs = 0x441;
        ((Pkt_b268_01E03E40 *)(s32)&pkt)->pad = 0;
        pkt.r = o->r;
        pkt.g = o->g;
        pkt.b = o->b;
        pkt.a = o->a;
        pkt.q = 1.0f;
        pkt.p0.x = 0x6BF8;
        pkt.p0.y = 0x71F8;
        pkt.p0.z = 0xFFFFFF;
        pkt.p0.f = 0;
        pkt.p1.x = 0x93F8;
        pkt.p1.y = 0x8DF8;
        pkt.p1.z = 0xFFFFFE;
        pkt.p1.f = 0;
        func_002086D0(&pkt, func_00208D00(3));
        func_002075F0(&pkt, 0, (u32)o->depth);
        func_00207FD0(ctx, ctx2, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b398", func_01E05E50_b398);
