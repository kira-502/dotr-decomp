#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b005_01E00080;

typedef struct {
    u8 count;
    u8 pad01;
    u8 length;
    u8 mask;
    u8 mode;
    u8 pad05[0xB];
    u8 light[0x10];
    Vec_b005_01E00080 pos;
    u8 pad30[8];
    f32 value;
    u8 pad3C[4];
    Vec_b005_01E00080 vel;
    f32 base;
} Fx_b005_01E00080;

static void func_01E00080_b070(Fx_b005_01E00080 *o) {
    u8 phase;
    u8 mask;
    u8 rest;
    u8 count;
    f32 step;
    u8 length;
    s32 on;

    if (func_00101AF0(o) == 0) {
        return;
    }
    o->pos.x += o->vel.x;
    o->pos.y += o->vel.y;
    o->pos.z += o->vel.z;
    func_00101BA0(o, (s32)&o->pos);
    count = o->count;
    mask = o->mask;
    length = o->length;
    phase = count & mask;
    rest = length - count;
    if (mask == 0xFF) {
        step = o->base / length;
    } else {
        step = o->base / (mask + 1);
    }
    on = 1;
    switch (o->mode & 0xF) {
    case 1:
        o->value = step * phase;
        break;
    case 2:
        if (mask == 0xFF) {
            if (rest < length >> 1) {
                o->value = 2.0f * step * rest;
            } else {
                o->value = 2.0f * step * count;
            }
        } else {
            if (phase < mask >> 1) {
                o->value = 2.0f * step * (mask - phase);
            } else {
                o->value = 2.0f * step * phase;
            }
        }
        break;
    case 4:
        o->value = o->base;
        if (o->count & 1) {
            o->value *= 0.5f;
        }
        break;
    case 8:
        if (count & 1) {
            on = 0;
        }
    default:
        o->value = o->base;
        break;
    }
    if (on == 0 || o->count == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10((s32)o->light);
    }
}

/* OVL_WARM */

/* shape b029:01E02B80, 696 insns, 37 copies: update and draw ribbon emitters (0x68 bytes each, may turn toward a
   target object); each segment is projected and drawn as a quad from the emitter's origin, widened on screen */

typedef struct Uvs_b029_01E02B80 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b029_01E02B80;

typedef struct Rib_b029_01E02B80 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 b5c;
    u8 frame;
    u8 hold;
    u8 target;
    u8 padF;
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1c, g1, r1, a1;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    s32 rot[3];
    u8 pad54[4];
    s32 drot[3];
    u8 pad64[4];
} Rib_b029_01E02B80;

typedef struct Xyz_b029_01E02B80 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b029_01E02B80;

typedef struct Vtx_b029_01E02B80 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b029_01E02B80 xyz;
} Vtx_b029_01E02B80;

typedef struct Pk_b029_01E02B80 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b029_01E02B80 v[4];
    u8 pad70[0x20];
} Pk_b029_01E02B80;

static inline void b029_01E02B80_tag(Pk_b029_01E02B80 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

static s32 func_01E003A0_b070(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101EE0();
    extern void func_0020C940();
    extern void func_0020BC00();
    extern void func_00101940();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Rib_b029_01E02B80 *p = arg0;
    s32 i __attribute__((aligned(16)));
    s32 life __attribute__((aligned(16)));
    s32 j __attribute__((aligned(16)));
    s32 tex;
    u8 k;
    s32 dx;
    s32 dy;
    f32 h;
    f32 ang;
    f32 zf;
    f32 x;
    f32 lf;
    f32 half;
    f32 y;
    f32 z;
    f32 b;
    f32 rad;

    f32 m2[4][4];
    f32 m[4][4];
    Xyz_b029_01E02B80 s[2];
    f32 v[4];
    Vec4f d;
    Vec4f tgt;
    extern Uvs_b029_01E02B80 D_01E05580_b070;
    Uvs_b029_01E02B80 tbl = D_01E05580_b070;
    Uvs_b029_01E02B80 uvs;
    Pk_b029_01E02B80 pk __attribute__((aligned(8)));
    f32 depth[2];

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        if (p->flags & 4) {
            tex = func_00202BF0(5, p->idx);
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, p->frame, 0);
        } else {
            tex = func_00202BF0(tbl.kind, tbl.tex);
            uvs = tbl;
        }
        if (!(p->flags & 2)) {
            uvs.v0 -= 0x10;
            uvs.v1 -= 0x10;
        }
        ang = 0.0f;
        k = p->k;
        if (p->age < p->hold) {
            life = p->life - p->hold;
        } else {
            life = p->life - p->age;
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->rot[0] += p->drot[0];
        p->rot[1] += p->drot[1];
        p->rot[2] += p->drot[2];
        func_00101BA0(p, p->pos);
        if (p->flags & 8) {
            func_001F5620(func_001F53A0(), p->target, &tgt);
            d.x = tgt.x - p->pos[0];
            d.y = tgt.y - p->pos[1];
            d.z = tgt.z - p->pos[2];
            func_00101940(&d, p->rot);
        }
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        b029_01E02B80_tag((Pk_b029_01E02B80 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
        pk.v[0].r = pk.v[1].r = p->r0;
        pk.v[2].r = pk.v[3].r = p->r1;
        pk.v[0].g = pk.v[1].g = p->g0;
        pk.v[2].g = pk.v[3].g = p->g1;
        pk.v[0].b = pk.v[1].b = p->b0;
        pk.v[2].b = pk.v[3].b = p->b1c;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        if (p->age < 8 && !(p->flags & 0x40)) {
            pk.v[0].a = pk.v[1].a = pk.v[2].a = (p->a0 >> 3) * p->age;
            pk.v[3].a = (p->a1 >> 3) * p->age;
        } else {
            pk.v[0].a = pk.v[1].a = pk.v[2].a = p->a0;
            pk.v[3].a = p->a1;
        }
        func_00101EE0(&pk, &uvs, tex);
        v[0] = v[1] = v[2] = 0.0f;
        if (func_00205440(v, m, &s[1], &depth[1]) == 0) {
            continue;
        }
        if (func_00101600(&s[1]) == 0) {
            continue;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += 17.0f;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                b = p->f18 * (f32)(u32)p->pts[k++] / 255.0f;
                rad = 3.1415927f * ang / 180.0f;
                x = b * func_001A6898(rad);
                z = b * func_001A6A88(rad);
                half = p->scale / 2.0f;
                y = half + half * ((f32)(u32)p->pts[k++] / 255.0f);
            }
            lf = (f32)life;
            v[0] = x * lf;
            v[1] = y * lf;
            v[2] = z * lf;
            if (func_00205440(v, m, &s[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&s[0]) == 0) {
                continue;
            }
            h = func_001018E0(p->width, depth[0]);
            if (p->flags & 0x80) {
                zf = 0.0f;
                pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = pk.v[3].xyz.z = 0xFFFFFE;
            } else {
                if (depth[0] < depth[1]) {
                    zf = depth[0];
                } else {
                    zf = depth[1];
                }
                pk.v[0].xyz.z = pk.v[1].xyz.z = s[0].z;
                pk.v[2].xyz.z = pk.v[3].xyz.z = s[1].z;
            }
            pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
            dy = s[1].y - s[0].y;
            dy = dy >= 0 ? dy : -dy;
            dx = s[1].x - s[0].x;
            dx = dx >= 0 ? dx : -dx;
            if (dy < dx) {
                pk.v[0].xyz.y = s[0].y;
                pk.v[1].xyz.y = s[0].y - h;
                pk.v[2].xyz.y = s[0].y + h;
                pk.v[3].xyz.y = s[1].y;
                if ((s32)s[0].x < (s32)s[1].x) {
                    pk.v[0].xyz.x = s[0].x - h;
                } else {
                    pk.v[0].xyz.x = s[0].x + h;
                }
                pk.v[1].xyz.x = pk.v[2].xyz.x = s[0].x;
                pk.v[3].xyz.x = s[1].x;
            } else {
                pk.v[0].xyz.x = s[0].x;
                pk.v[1].xyz.x = s[0].x - h;
                pk.v[2].xyz.x = s[0].x + h;
                pk.v[3].xyz.x = s[1].x;
                if ((s32)s[0].y < (s32)s[1].y) {
                    pk.v[0].xyz.y = s[0].y - h;
                } else {
                    pk.v[0].xyz.y = s[0].y + h;
                }
                pk.v[1].xyz.y = pk.v[2].xyz.y = s[0].y;
                pk.v[3].xyz.y = s[1].y;
            }
            func_002075F0((s32)&pk, id, (u32)zf);
        }
    }
    return 1;
}

/* shape b051:01E003A0 (ShFx_Flear01), 660 insns, 39 copies (-O3,p): draws each emitter of a list as a glowing ring: a
   fan of segs*4 triangles from the centre colour out to the edge colour, and unless flag 1 a textured band along the
   edge (two quads per slice); the radius grows each frame; the source of shape b035:01E00410, built here at -O3 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b051_01E003A0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b051_01E003A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b051_01E003A0 xyz;
} Vtx1_b051_01E003A0;

typedef struct {
    Hdr_b051_01E003A0 h;
    Vtx1_b051_01E003A0 v[3];
    u8 tail[8];
} Pkt1_b051_01E003A0;

typedef struct {
    u64 st;
    Xyz_b051_01E003A0 xyz;
} Vtx2_b051_01E003A0;

typedef struct {
    Hdr_b051_01E003A0 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b051_01E003A0 v[4];
    u8 tail[0x20];
} Pkt2_b051_01E003A0;

typedef struct {
    f32 x, y, z, w;
} V4_b051_01E003A0;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b051_01E003A0;

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
    V4_b051_01E003A0 pos;
    V4_b051_01E003A0 vel;
    V4_b051_01E003A0 org;
} Obj_b051_01E003A0;

#pragma optimization_level 3

static s32 func_01E00E80_b070(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E055A0_b070;
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
    Obj_b051_01E003A0 *o; /* a copy of obj: needed for the match (register order) */
    s32 k;
    s32 h __attribute__((aligned(16))); /* aligned: its spill slot, needed for the match */
    f32 m0[16];
    f32 m1[16];
    V4_b051_01E003A0 org;
    Tex_b051_01E003A0 t;
    Xyz_b051_01E003A0 scr;
    Pkt1_b051_01E003A0 p1 __attribute__((aligned(8)));
    Pkt2_b051_01E003A0 p2 __attribute__((aligned(8)));
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
    t = D_01E055A0_b070;
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
        ((Hdr_b051_01E003A0 *)(s32)&p1)->count = 0x13;
        ((Hdr_b051_01E003A0 *)(s32)&p1)->tag = 6;
        ((Hdr_b051_01E003A0 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b051_01E003A0 *)(s32)&p1)->pad = 0;
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
        ((Hdr_b051_01E003A0 *)(s32)&p2)->count = 0x24;
        ((Hdr_b051_01E003A0 *)(s32)&p2)->tag = 9;
        ((Hdr_b051_01E003A0 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b051_01E003A0 *)(s32)&p2)->pad = 0;
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

/* shape b172:01E012E0 (ShFx_Afx04), 897 insns, 20 copies: draws n flare entities (0x38 bytes each): moves
   each by its velocity, projects a point 5 units above it (towards the camera, flipped by flags & 1) for the depth
   and the entity itself for the centre; one packet set up on the first live entity; then for cnt rings (scale grows
   with the ring) a fan of up to 8 triangles (flag bits of mask) from the screen centre to the corners and edge
   midpoints, like ShFx_Afx01 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b172_01E012E0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b172_01E012E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b172_01E012E0 uv;
    Xyz_b172_01E012E0 xyz;
} Vtx_b172_01E012E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b172_01E012E0 v[4];
    u8 tail[8];
} Pkt_b172_01E012E0;

typedef struct {
    f32 x, y, z;
} V3_b172_01E012E0;

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
    V3_b172_01E012E0 pos;
    f32 pad24;
    V3_b172_01E012E0 vel;
    f32 pad34;
} Afx_b172_01E012E0;

static s32 func_01E018D0_b070(Afx_b172_01E012E0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_00101BA0(void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Afx_b172_01E012E0 *e = arg0;
    f32 mat[16];
    u8 td[0x20];
    Vec4f cam;
    Vec4f d;
    Vec4f p;
    f32 m2[16];
    Xyz_b172_01E012E0 xy[2];
    struct {
        Pkt_b172_01E012E0 pk;
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
            ((Pkt_b172_01E012E0 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b172_01E012E0 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b172_01E012E0 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b172_01E012E0 *)(s32)&w.pk)->pad = 0;
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
        ((Pkt_b172_01E012E0 *)(s32)&w.pk)->count |= 0x800;
        ((Uv_b172_01E012E0 *)(s32)&w.pk.v[2].uv)->u = u;
        ((Uv_b172_01E012E0 *)(s32)&w.pk.v[2].uv)->v = v;
        ((Uv_b172_01E012E0 *)(s32)&w.pk.v[3].uv)->u = u;
        ((Uv_b172_01E012E0 *)(s32)&w.pk.v[3].uv)->v = v;
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
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = v;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = xy[1].y;
                    w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 1:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = u;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[1].xyz.x = xy[1].x;
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 2:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = u;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = xy[1].x;
                    w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 3:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = v;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = (u32)(29184.0f - fy);
                    w.pk.v[1].xyz.y = xy[1].y;
                    break;
                case 4:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = v;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = xy[1].y;
                    w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 5:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = u;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[1].xyz.x = xy[1].x;
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 6:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = u;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = xy[1].x;
                    w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 7:
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b172_01E012E0 *)(s32)&w.pk.v[1].uv)->v = v;
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

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b029:01E026A0, 310 insns, 35 copies: full-screen fade quad (4 vertices); its alpha follows the emitter's counter */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b029_01E026A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b029_01E026A0;

typedef struct {
    Hdr_b029_01E026A0 h;
    Vtx_b029_01E026A0 v[4];
    u8 tail[8];
} Pkt_b029_01E026A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b029_01E026A0;

static s32 func_01E026E0_b070(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
    Pkt_b029_01E026A0 p __attribute__((aligned(8)));
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 mid;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b029_01E026A0 *)(s32)&p)->count = 0x14;
    ((Hdr_b029_01E026A0 *)(s32)&p)->tag = 8;
    ((Hdr_b029_01E026A0 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b029_01E026A0 *)(s32)&p)->pad = 0;
    mode = o->flags;
    switch (mode & 7) {
    case 1:
        a = 128.0f / o->max * o->cur;
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
        mid = 32768.0f;
        p.v[0].y = p.v[1].y = mid - w;
        p.v[2].y = p.v[3].y = mid;
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = mid;
        p.v[2].y = p.v[3].y = mid + w;
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

INCLUDE_ASM("asm/nonmatchings/mod/b070", func_01E02BC0_b070);

/* shape b715:01E003A0 (ShFx_RingTX), 461 insns, 18 copies (-O3,p): n ring emitters (0x5C bytes each): an inner and an
   outer circle of up to 36 points (radii growing each frame) joined into textured quads; texture rect from
   func_001020B0, mode 1 = no clamp and s scaled by e->scale, mode 2 = a 1-texel column in the middle; far z with
   flags & 0x80; the source of shape b603:01E039B0, built here at -O3 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b715_01E003A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b715_01E003A0 xyz;
} Vtx_b715_01E003A0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b715_01E003A0 v[4];
    u8 tail[0x20];
} Pkt_b715_01E003A0;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b715_01E003A0;

typedef struct {
    u8 b, g, r, a;
} Col_b715_01E003A0;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 texid;
    u8 sub;
    u8 bA;
    u8 bB;
    u8 mode;
    u8 padD[3];
    f32 radius[2];
    f32 dradius[2];
    f32 scale;
    Col_b715_01E003A0 c0;
    Col_b715_01E003A0 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b715_01E003A0;

#pragma optimization_level 3

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E034D0_b070(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    f32 depth[4];
    Tex_b715_01E003A0 td;
    Pkt_b715_01E003A0 pkt;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b715_01E003A0 *e;
    s32 i;
    s32 tex;
    s32 nseg;
    s32 k;
    s32 r;
    f32 step;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texid);
        e->radius[0] += e->dradius[0];
        e->radius[1] += e->dradius[1];
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        if (e->seg > 36) {
            nseg = 36;
        } else {
            nseg = e->seg;
        }
        step = 360.0f / nseg;
        for (r = 0; r < 2; r++) {
            for (k = 0; k < nseg; k++) {
                ring[r][k].x = e->radius[r] * func_001A6898(3.1415927f * (step * k) / 180.0f);
                ring[r][k].z = e->radius[r] * func_001A6A88(3.1415927f * (step * k) / 180.0f);
                ring[r][k].y = 0.0f;
            }
        }
        ring[0][nseg] = ring[0][0];
        ring[1][nseg] = ring[1][0];
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        td.b5 = e->sub;
        func_001020B0(&td, e->bB, e->bA);
        func_00102210(e->bA, &sw, &sh);
        switch (e->mode & 3) {
        case 1:
            func_00208CB0(&pkt, 0);
            sw *= e->scale;
            break;
        case 2:
            td.u = td.u + ((td.w - td.u) >> 1);
            td.w = td.u + 1;
        default:
            func_00208CB0(&pkt, 0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            break;
        }
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        for (k = 0; k < nseg; k++) {
            if (func_00205440(&ring[0][k], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                func_00205440(&ring[0][k + 1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                func_00205440(&ring[1][k], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                func_00205440(&ring[1][k + 1], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                pkt.v[0].q = 1.0f / depth[0];
                pkt.v[1].q = 1.0f / depth[1];
                pkt.v[2].q = 1.0f / depth[2];
                pkt.v[3].q = 1.0f / depth[3];
                pkt.v[0].s = td.u / sw / depth[0];
                pkt.v[0].t = td.v / sh / depth[0];
                pkt.v[1].s = td.w / sw / depth[1];
                pkt.v[1].t = td.v / sh / depth[1];
                pkt.v[2].s = td.u / sw / depth[2];
                pkt.v[2].t = td.h / sh / depth[2];
                pkt.v[3].s = td.w / sw / depth[3];
                pkt.v[3].t = td.h / sh / depth[3];
                func_00101C80(&td, bl);
                func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                func_00208700(&pkt, (void *)tex, 1);
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_WARM */

/* shape b070:01E03C10, 676 insns, 13 copies: draws n lightning bolts (0x40-byte emitters): func_00102A50 builds the zigzag
   points between two ends (from func_00101BA0 or the emitter's moving ends); each projected segment becomes
   (life & 3) + 1 quads, widened across the shorter screen axis; the corner order rotates with age */

typedef struct {
    f32 x, y, z;
} Vec3_b070_01E03C10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b070_01E03C10;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b070_01E03C10 xyz;
} Vtx_b070_01E03C10;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b070_01E03C10 v[4];
    u8 tail[0x20];
} Pkt_b070_01E03C10;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b070_01E03C10;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b070_01E03C10 a;
    Vec3_b070_01E03C10 b;
    Vec3_b070_01E03C10 *pts;
} Bolt_b070_01E03C10;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 mode;
    u8 sel;
    u8 pad7;
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
    Vec3_b070_01E03C10 p0;
    Vec3_b070_01E03C10 p1;
    Vec3_b070_01E03C10 vel;
} Emit_b070_01E03C10;

typedef struct W_tmpl_func_01E03C10_b070 {
    Tex_b070_01E03C10 v[2];
} W_tmpl_func_01E03C10_b070;

static s32 func_01E03C10_b070(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00102A50(void *);
    extern void func_00101EE0(void *, void *, void *);
    Emit_b070_01E03C10 *e = arg0;
    f32 mat[16];
    Bolt_b070_01E03C10 bolt;
    Vec3_b070_01E03C10 pts[17];
    Xyz_b070_01E03C10 s[3];
    Vec4f v;
    Vec3_b070_01E03C10 ab[2];
    extern W_tmpl_func_01E03C10_b070 D_01E055C0_b070;
    W_tmpl_func_01E03C10_b070 tmpl_w = D_01E055C0_b070;
    Pkt_b070_01E03C10 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    void *tex;
    s32 j;
    s32 end;
    s32 k;
    s32 dx;
    s32 dy;
    f32 fdx;
    f32 fdy;
    f32 w;
    u32 c0;
    u32 c1;
    f32 z;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        if (e->mode != 0) {
            e->sel = e->sel0;
            func_00101BA0(e, &v);
            ab[0].x = v.x;
            ab[0].y = v.y;
            ab[0].z = v.z;
            if (e->flags & 2) {
                ab[1].x = ab[0].x + e->p0.x;
                ab[1].y = ab[0].y + e->p0.y;
                ab[1].z = ab[0].z + e->p0.z;
            } else {
                e->sel = e->sel1;
                func_00101BA0(e, &v);
                ab[1].x = v.x;
                ab[1].y = v.y;
                ab[1].z = v.z;
            }
        } else {
            e->p0.x += e->vel.x;
            e->p0.y += e->vel.y;
            e->p0.z += e->vel.z;
            e->p1.x += e->vel.x;
            e->p1.y += e->vel.y;
            e->p1.z += e->vel.z;
            ab[0] = e->p0;
            ab[1] = e->p1;
        }
        func_0020EB40(mat);
        bolt.n = e->nseg;
        bolt.jitter = e->jitter;
        bolt.pts = pts;
        bolt.a = ab[0];
        bolt.b = ab[1];
        func_00102A50(&bolt);
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        func_00101EE0(&pkt, &tmpl_w.v[e->texsel], tex);
        if (!(e->flags & 4) && e->life < bolt.n) {
            j = bolt.n - e->life;
        } else {
            j = 0;
        }
        if ((e->flags & 1) && e->max - e->life < bolt.n) {
            end = e->max - e->life;
        } else {
            end = bolt.n;
        }
        for (; j < end; j++) {
            if (func_00205440(&pts[j], mat, &s[0], &depth[0]) == 0 || func_00101600(&s[0]) == 0 ||
                func_00205440(&pts[j + 1], mat, &s[1], &depth[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            dx = s[0].x - s[1].x;
            fdx = (dx >= 0) ? dx : -dx;
            dy = s[0].y - s[1].y;
            fdy = (dy >= 0) ? dy : -dy;
            w = func_001A6C60(fdx * fdx + fdy * fdy) / e->wdiv;
            for (k = 0; k < (e->life & 3) + 1; k++) {
                w += k * (w * e->grow);
                if (fdx > fdy) {
                    c0 = s[0].y;
                    pkt.v[0].xyz.y = c0 - w;
                    c1 = s[1].y;
                    pkt.v[1].xyz.y = c1 - w;
                    pkt.v[2].xyz.y = c0 + w;
                    pkt.v[3].xyz.y = c1 + w;
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
                } else {
                    c0 = s[0].x;
                    pkt.v[0].xyz.x = c0 - w;
                    c1 = s[1].x;
                    pkt.v[1].xyz.x = c1 - w;
                    pkt.v[2].xyz.x = c0 + w;
                    pkt.v[3].xyz.x = c1 + w;
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[1].y;
                }
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = s[0].z;
                    pkt.v[2].xyz.z = pkt.v[3].xyz.z = s[1].z;
                    if (depth[0] < depth[1]) {
                        z = depth[0];
                    } else {
                        z = depth[1];
                    }
                }
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = 0;
                pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                switch ((e->life + j) & 3) {
                case 1:
                    s[2] = pkt.v[0].xyz;
                    pkt.v[0].xyz = pkt.v[3].xyz;
                    pkt.v[3].xyz = s[2];
                    s[2] = pkt.v[1].xyz;
                    pkt.v[1].xyz = pkt.v[2].xyz;
                    pkt.v[2].xyz = s[2];
                    break;
                case 2:
                    s[2] = pkt.v[0].xyz;
                    pkt.v[0].xyz = pkt.v[1].xyz;
                    pkt.v[1].xyz = s[2];
                    s[2] = pkt.v[2].xyz;
                    pkt.v[2].xyz = pkt.v[3].xyz;
                    pkt.v[3].xyz = s[2];
                    break;
                case 3:
                    s[2] = pkt.v[0].xyz;
                    pkt.v[0].xyz = pkt.v[2].xyz;
                    pkt.v[2].xyz = s[2];
                    s[2] = pkt.v[1].xyz;
                    pkt.v[1].xyz = pkt.v[3].xyz;
                    pkt.v[3].xyz = s[2];
                    break;
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}

/* shape b070:01E046A0 (b070), 927 insns, 1 copy: the b070 module main: code >= 0 clears the scene, takes both units
   and five joints; else counts the frame: 2 starts the glow, 170 the fade, ten bolt sets (three lines, four fixed
   arcs, three random arcs) and the light, 310 dims the glow, 440 ends; two sparks a frame at a joint, frames 170..321
   three bolts and a ring near the target; steps every effect; returns 6 on frames 170..330, 2/1 on frames 167/160 */

typedef struct {
    u8 count;
    u8 pad1;
    u8 len;
    u8 mask;
    u8 mode;
    u8 b5;
    u8 pad6[0xE];
    f32 sx, sy, sz;
    Vec4f pos;
    f32 f70;
    f32 f74;
    u8 pad78[0x18];
    f32 f90;
    u8 pad94[0xC];
} Fx_b070_01E046A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 b5;
    u8 pad6;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    Vec4f pos;
    u8 pad2C[0x20];
} Ring_b070_01E046A0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 on;
    u8 m;
    u8 hold;
    u8 scale;
    u8 blend;
    u8 mask;
    u8 len;
    s32 obj;
    u8 b2, g2, r2, a2;
    u8 b, g, r, a;
    u8 pad18[0x20];
} Afx_b070_01E046A0;

typedef struct {
    f32 x, y, z;
} Vec3_b070_01E046A0;

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
    Vec3_b070_01E046A0 p0;
    Vec3_b070_01E046A0 p1;
    Vec3_b070_01E046A0 vel;
} Bolt_b070_01E046A0;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 tex;
    u8 pad5[3];
    u8 kind;
    u8 frame;
    u8 b6;
    u8 b7;
    u8 c[4];
    f32 size;
    f32 scale;
    s32 w18;
    s32 w1C;
    f32 x, y, z;
    f32 f2C;
    f32 f30;
    u8 pad34[0x10];
} Spk_b070_01E046A0;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b070_01E046A0 a;
    Vec3_b070_01E046A0 b;
    Vec3_b070_01E046A0 *pts;
} Line_b070_01E046A0;

typedef struct {
    s32 n;
    f32 r;
    f32 ang;
    f32 fC;
    Vec3_b070_01E046A0 a;
    Vec3_b070_01E046A0 b;
    Vec3_b070_01E046A0 *pts;
} Arc_b070_01E046A0;

typedef struct {
    s32 v[17];
} Tbl_b070_01E046A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
} Ob_b070_01E046A0;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    s32 m2;
    s32 m3;
    s32 m4;
    u8 pad20[0xC];
    u8 cam[0x14];
    Fx_b070_01E046A0 fx;
    s16 wv[2];
    u8 rib[0x3C][0x68];
    Ring_b070_01E046A0 ring[0x18];
    Afx_b070_01E046A0 afx;
    u8 x205C[8][0x5C];
    Bolt_b070_01E046A0 bolt[0x96];
    Spk_b070_01E046A0 spk[0x12C];
    Ob_b070_01E046A0 ob;
    u8 tbl[0x100];
    u8 pad9974[0xC];
} Scene_b070_01E046A0;

static s32 func_01E046A0_b070(Scene_b070_01E046A0 *g, s32 code) {
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
    extern void func_001031C0(void *, s32);
    extern void func_00102A50(void *);
    extern void func_00102F20(void *);
    extern s32 func_01E00080_b070();
    extern s32 func_01E003A0_b070();
    extern s32 func_01E00E80_b070();
    extern s32 func_01E018D0_b070();
    extern s32 func_01E026E0_b070();
    extern s32 func_01E02BC0_b070();
    extern s32 func_01E034D0_b070();
    extern s32 func_01E03C10_b070();
    extern Tbl_b070_01E046A0 D_01E055F0_b070;
    s32 ot = func_00207500();
    Tbl_b070_01E046A0 tbl = D_01E055F0_b070;
    Vec4f v;
    Vec4f q[2];
    Line_b070_01E046A0 line;
    Arc_b070_01E046A0 arc;
    Vec3_b070_01E046A0 pts[17];
    s32 i;
    s32 j;
    s32 k;
    Vec3_b070_01E046A0 *p;

    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x9980);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 4; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 1, 1);
        g->m1 = func_001F5560(g->unitA, 0x12, 0);
        g->m2 = func_001F5560(g->unitA, 0x2B, 0);
        g->m3 = func_001F5560(g->unitA, 7, 0);
        g->m4 = func_001F5560(g->unitA, 8, 0);
        g->wv[0] = 2;
        g->wv[1] = 0x1B2;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 2:
        func_00101AD0(&g->afx, 0xFF, 0, 0xFF);
        g->afx.flags = 1;
        g->afx.blend = 2;
        g->afx.mask = 0xFF;
        g->afx.scale = 0xC;
        g->afx.len = 4;
        g->afx.obj = g->unitA;
        g->afx.r = 0x30;
        g->afx.g = 0x30;
        g->afx.b = 0x80;
        g->afx.a = 0;
        g->afx.r2 = 0x30;
        g->afx.g2 = 0x30;
        g->afx.b2 = 0x80;
        g->afx.a2 = 0;
        g->afx.on = 1;
        g->afx.m = g->m3;
        break;
    case 0xAA:
        func_00101AD0(&g->afx, 0xFF, 0, 0xFF);
        g->afx.r = 0x80;
        g->afx.g = 0x80;
        g->afx.b = 0xC0;
        g->afx.a = 0x20;
        g->afx.r2 = 0x80;
        g->afx.g2 = 0x80;
        g->afx.b2 = 0xC0;
        g->afx.a2 = 0xF0;
        func_00101AD0(&g->ob, 0x10, 0, 0xFF);
        g->ob.flags = 1;
        func_001F5620(g->unitA, g->m0, &q[0]);
        for (j = 0; j < 10; j++) {
            switch (j) {
            case 0:
            case 1:
            case 2:
                line.n = 5;
                line.jitter = 0.8f;
                line.pts = pts;
                line.a.x = q[0].x;
                line.a.y = q[0].y;
                line.a.z = q[0].z;
                line.b.x = v.x;
                line.b.y = v.y;
                line.b.z = v.z;
                func_00102A50(&line);
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                arc.n = 5;
                arc.r = 50.0f;
                switch (j) {
                case 3:
                    arc.ang = 40.0f;
                    break;
                case 4:
                    arc.ang = 320.0f;
                    break;
                case 5:
                    arc.ang = 140.0f;
                    break;
                case 6:
                    arc.ang = 220.0f;
                    break;
                }
                arc.pts = pts;
                arc.a.x = q[0].x;
                arc.a.y = q[0].y;
                arc.a.z = q[0].z;
                arc.b.x = v.x;
                arc.b.y = v.y;
                arc.b.z = v.z;
                func_00102F20(&arc);
                break;
            default:
                arc.n = 5;
                arc.r = 30.0f + (f32)((func_0019A5C8() >> 4) % 10 * 200 - 1000) / 100.0f;
                arc.ang = (f32)((func_0019A5C8() >> 4) % 360 * 200 - 36000) / 100.0f;
                arc.pts = pts;
                arc.a.x = q[0].x;
                arc.a.y = q[0].y;
                arc.a.z = q[0].z;
                arc.b.x = v.x;
                arc.b.y = v.y;
                arc.b.z = v.z;
                func_00102F20(&arc);
                break;
            }
            p = pts;
            for (i = 0; i < 5; i++) {
                k = func_00101C30(g->bolt, 0x40, 0x96);
                if (k < 0) {
                    break;
                }
                                func_00101AD0(&g->bolt[k], 0x8C, i & 1, 0xFF);
                g->bolt[k].mode = 0;
                g->bolt[k].flags = 1;
                g->bolt[k].p0 = p[0];
                g->bolt[k].p1 = p[1];
                g->bolt[k].nseg = 6;
                g->bolt[k].jitter = 0.7f;
                g->bolt[k].grow = 0.2f;
                g->bolt[k].texid = 3;
                g->bolt[k].wdiv = 3;
                g->bolt[k].texsel = 0;
                g->bolt[k].b = 0x80;
                g->bolt[k].g = 0x80;
                g->bolt[k].r = 0x80;
                g->bolt[k].a = 0x20;
                p++;
            }
        }
        func_00101AD0(&g->fx, (u8)(0x14E - g->t), 0, 0xFF);
        g->fx.b5 = 0;
        g->fx.mode = 8;
        g->fx.sx = 1.6f;
        g->fx.sy = 1.6f;
        g->fx.sz = 1.6f;
        g->fx.f70 = 0.0f;
        g->fx.f74 = 40.0f;
        g->fx.f90 = 6.0f;
        g->fx.pos = v;
        break;
    case 0x136:
        g->afx.hold = 0;
        g->afx.r = 0x30;
        g->afx.g = 0x30;
        g->afx.b = 0x80;
        g->afx.a = 0;
        g->afx.r2 = 0x30;
        g->afx.g2 = 0x30;
        g->afx.b2 = 0x80;
        g->afx.a2 = 0;
        break;
    case 0x1B8:
        return 8;
    }
    func_001F5620(g->unitA, g->m4, &q[0]);
    for (i = 0; i < 2; i++) {
        k = func_00101C30(g->spk, 0x44, 0x12C);
        if (k < 0) {
            continue;
        }
                func_00101AD0(&g->spk[k], 0x20, 0, 0xFF);
        g->spk[k].tex = ((func_0019A5C8() >> 4) & 3) * 16;
        if (i & 1) {
            g->spk[k].kind = 2;
            g->spk[k].c[3] = 0x80;
            g->spk[k].c[0] = 0x80;
            g->spk[k].c[1] = 0x80;
            g->spk[k].c[2] = 0x80;
            g->spk[k].size = 180.0f + (f32)((func_0019A5C8() >> 4) % 40 * 200 - 4000) / 100.0f;
            g->spk[k].scale = 1.0f;
        } else {
            g->spk[k].kind = 1;
            g->spk[k].c[2] = 0x80;
            g->spk[k].c[1] = 0xA0;
            g->spk[k].c[0] = 0xC0;
            g->spk[k].c[3] = 0x40;
            g->spk[k].size = 20.0f + (f32)((func_0019A5C8() >> 4) % 10 * 200 - 1000) / 100.0f;
            g->spk[k].scale = 1.0f + (f32)((func_0019A5C8() >> 4) % 150 - 75) / 100.0f;
        }
        g->spk[k].b7 = 2;
        g->spk[k].b6 = 0;
        g->spk[k].frame = (func_0019A5C8() >> 4) & 7;
        g->spk[k].w1C = 0;
        g->spk[k].w18 = 0;
        g->spk[k].x = q[0].x + (f32)((func_0019A5C8() >> 4) % 1000 - 500) / 100.0f;
        g->spk[k].y = q[0].y + (f32)((func_0019A5C8() >> 4) % 1000 - 500) / 100.0f;
        g->spk[k].z = q[0].z + (f32)((func_0019A5C8() >> 4) % 1000 - 500) / 100.0f;
        g->spk[k].f30 = 0.6f + (f32)((func_0019A5C8() >> 4) % 50 - 25) / 100.0f;
        g->spk[k].f2C = (f32)((func_0019A5C8() >> 4) % 20 - 10) / 100.0f;
    }
    if (g->t >= 0xAA && g->t < 0x142) {
        q[0] = v;
        q[1].x = q[0].x + (f32)((func_0019A5C8() >> 4) % 3200 - 1600) / 100.0f;
        q[1].y = q[0].y + (f32)((func_0019A5C8() >> 4) % 3200 - 1600) / 100.0f;
        q[1].z = q[0].z + (f32)((func_0019A5C8() >> 4) % 3200 - 1600) / 100.0f;
        for (j = 0; j < 3; j++) {
            k = func_00101C30(g->bolt, 0x40, 0x96);
            if (k < 0) {
                break;
            }
                        func_00101AD0(&g->bolt[k], 0xC, (u8)j, 0xFF);
            g->bolt[k].mode = 0;
            g->bolt[k].flags = 0;
            g->bolt[k].p0.x = g->bolt[k].p1.x = q[1].x;
            g->bolt[k].p0.y = g->bolt[k].p1.y = q[1].y;
            g->bolt[k].p0.z = g->bolt[k].p1.z = q[1].z;
            g->bolt[k].p1.x += (f32)((func_0019A5C8() >> 4) % 24 * 200 - 2400) / 100.0f;
            g->bolt[k].p1.y += (f32)((func_0019A5C8() >> 4) % 24 * 200 - 2400) / 100.0f;
            g->bolt[k].p1.z += (f32)((func_0019A5C8() >> 4) % 24 * 200 - 2400) / 100.0f;
            g->bolt[k].nseg = 8;
            g->bolt[k].jitter = 1.0f;
            g->bolt[k].grow = 0.3f;
            g->bolt[k].texid = 3;
            g->bolt[k].wdiv = 4;
            g->bolt[k].texsel = 0;
            g->bolt[k].b = 0x80;
            g->bolt[k].g = 0x80;
            g->bolt[k].r = 0x80;
            g->bolt[k].a = 0x20;
        }
        k = func_00101C30(g->ring, 0x4C, 0x18);
        if (k >= 0) {
            func_00101AD0(&g->ring[k], 0xC, 0, 0xFF);
            g->ring[k].b5 = 0;
            g->ring[k].flags = 4;
            g->ring[k].segs = 9;
            g->ring[k].alpha = 0xD0;
            g->ring[k].ib = 0xD0;
            g->ring[k].ig = 0xD0;
            g->ring[k].ir = 0xD0;
            g->ring[k].r = 0;
            g->ring[k].g = 0x60;
            g->ring[k].b = 0x80;
            g->ring[k].grow = 0.0f;
            g->ring[k].radius = 200.0f;
            g->ring[k].grow = 30.0f;
            g->ring[k].pos = q[1];
            g->ring[k].width = 20.0f;
        }
    }
    if (g->afx.life > 0) {
        if (g->afx.hold == 0) {
            g->afx.a2 = tbl.v[(g->t - 2) & 0xF] * 3;
        }
    }
    func_01E00080_b070(&g->fx);
    func_001031C0(g->wv, g->t);
    func_01E026E0_b070(&g->ob, ot);
    func_01E03C10_b070(g->bolt, ot, 0x96);
    func_01E003A0_b070(g->rib, ot, 0x3C);
    func_01E00E80_b070(g->ring, ot, 0x18);
    func_01E018D0_b070(&g->afx, ot, 1);
    func_01E034D0_b070(g->x205C, ot, 8);
    func_01E02BC0_b070(g->spk, ot, 0x12C);
    if (g->t >= 0xAA && g->t < 0x14B) {
        return 6;
    }
    switch (g->t) {
    case 0xA0:
        return 1;
    case 0xA7:
        return 2;
    }
    return 0;
}
