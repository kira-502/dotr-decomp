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

static void func_01E00080_b351(Fx_b005_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b351", func_01E003A0_b351);

INCLUDE_ASM("asm/nonmatchings/mod/b351", func_01E014C0_b351);

/* shape b285:01E014C0 (ShFx_Mptc), 791 insns, 12 copies (-O3,p): update and draw ribbon emitters (0x58 bytes each);
   every segment is projected straight into the packet's vertex slots and widened on screen; the source of shape
   b024:01E02120, built here at -O3 */

typedef struct Uvs_b285_01E014C0 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b285_01E014C0;

typedef struct Rib_b285_01E014C0 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 frame;
    u8 b5c;
    u8 div;
    u8 padE[2];
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    f32 rot[4];
} Rib_b285_01E014C0;

typedef struct Xyz_b285_01E014C0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b285_01E014C0;

typedef struct Pk_b285_01E014C0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b285_01E014C0 v[4];
    u64 pad60[3];
} Pk_b285_01E014C0;

static inline void b285_01E014C0_tag(Pk_b285_01E014C0 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 3
typedef struct W_tbl_func_01E02BC0_b536 {
    Uvs_b285_01E014C0 v[4];
} W_tbl_func_01E02BC0_b536;

/* id aligned: its spill slot, needed for the match */
static s32 func_01E01D20_b351(Rib_b285_01E014C0 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 w;
    f32 b;
    Rib_b285_01E014C0 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    u8 k;
    s32 tex;
    s32 life;
    f32 rad;
    f32 d;
    f32 a;
    f32 h0;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E02BC0_b536 D_01E07A10_b351;
    W_tbl_func_01E02BC0_b536 tbl_w = D_01E07A10_b351;
    Uvs_b285_01E014C0 uvs;
    Pk_b285_01E014C0 pk;
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
        } else {
            tex = func_00202BF0(tbl_w.v[p->idx].kind, tbl_w.v[p->idx].tex);
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        func_00101BA0(p, p->pos);
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        k = p->k;
        ang = 0.0f;
        life = p->life - p->age;
        b285_01E014C0_tag((Pk_b285_01E014C0 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        if (p->flags & 4) {
            sel = p->frame;
            if (p->flags & 8) {
                sel = life & 7;
                if (life < 3) {
                    sel = life;
                }
                if (p->age < 4) {
                    sel = 7 - p->age;
                }
            }
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, sel, 0);
            func_00101D20(&pk, &uvs, tex);
        } else {
            func_00101D20(&pk, &tbl_w.v[p->idx], tex);
        }
        if (p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
        } else {
            pk.a = p->a;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                v.x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                v.y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                v.z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += 17.0f;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                rad = 3.1415927f * ang / 180.0f;
                v.x = a * b * func_001A6898(rad);
                v.z = a * b * func_001A6A88(rad);
                v.y = a * p->scale;
            }
            w = p->width + p->grow * (f32)life;
            if (p->div > 1) {
                d = p->scale / (f32)p->div;
                w = w / (1.0f + func_0020D0E0(&v.x) / d);
            }
            t[0].x = v.x * (f32)life;
            t[0].y = v.y * (f32)life;
            t[0].z = v.z * (f32)life;
            if (func_00205440(&t[0], m, &pk.v[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&pk.v[0]) == 0) {
                continue;
            }
            h0 = func_001018E0(w, depth[0]);
            if (p->flags & 2) {
                t[1].x = t[0].x + 4.0f * v.x;
                t[1].y = t[0].y + 4.0f * v.y;
                t[1].z = t[0].z + 4.0f * v.z;
                if (func_00205440(&t[1], m, &pk.v[2], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&pk.v[2]) == 0) {
                    continue;
                }
                h1 = func_001018E0(w, depth[1]);
                dy = pk.v[2].y - pk.v[0].y;
                dy = dy >= 0 ? dy : -dy;
                dx = pk.v[2].x - pk.v[0].x;
                dx = dx >= 0 ? dx : -dx;
                if (dy < dx) {
                    pk.v[1].x = pk.v[0].x;
                    pk.v[3].x = pk.v[2].x;
                    pk.v[1].y = (u32)(pk.v[0].y + h0);
                    pk.v[0].y = (u32)(pk.v[0].y - h0);
                    pk.v[3].y = (u32)(pk.v[2].y + h1);
                    pk.v[2].y = (u32)(pk.v[2].y - h1);
                } else {
                    pk.v[1].y = pk.v[0].y;
                    pk.v[3].y = pk.v[2].y;
                    pk.v[1].x = (u32)(pk.v[0].x + h0);
                    pk.v[0].x = (u32)(pk.v[0].x - h0);
                    pk.v[3].x = (u32)(pk.v[2].x + h1);
                    pk.v[2].x = (u32)(pk.v[2].x - h1);
                }
                pk.v[1].z = pk.v[0].z;
                pk.v[3].z = pk.v[2].z;
            } else {
                pk.v[1].x = (u32)(pk.v[0].x + h0);
                pk.v[1].y = (u32)(pk.v[0].y - h0);
                pk.v[2].x = (u32)(pk.v[0].x - h0);
                pk.v[2].y = (u32)(pk.v[0].y + h0);
                pk.v[3].x = (u32)(pk.v[0].x + h0);
                pk.v[3].y = (u32)(pk.v[0].y + h0);
                pk.v[0].x = (u32)(pk.v[0].x - h0);
                pk.v[0].y = (u32)(pk.v[0].y - h0);
                pk.v[1].z = pk.v[2].z = pk.v[3].z = pk.v[0].z;
            }
            pk.v[0].fog = pk.v[1].fog = pk.v[2].fog = pk.v[3].fog = 1;
            func_002075F0((s32)&pk, id, (u32)(depth[0]));
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b351:01E02980, 287 insns (ShFx_Flear03): steps and draws n flare arcs (0x5C bytes each): the arc's start
   and end angles slide by 0x18 toward each other's side, the centre moves by its speed, the radius grows by 0x20 while
   the life is above 0x09; each arc is drawn as a fan of triangles from the centre (colour 0x24, fading in over its
   first 8 life steps) to the rim (colour 0x28), one per (0x14 x 0x08) degrees */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 xyz;
} Vtx_b351_01E02980;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b351_01E02980 v[3];
    u64 tail;
} Pkt_b351_01E02980;

typedef struct {
    f32 x, y, z;
} V3_b351_01E02980;

typedef struct {
    u8 life;
    u8 pad1[7];
    u8 steps;
    u8 b9;
    u8 padA[2];
    f32 a0;
    f32 a1;
    f32 step;
    f32 da;
    f32 r;
    f32 dr;
    u8 c0[4];
    u8 c1[4];
    V3_b351_01E02980 pos;
    u8 pad38[4];
    V3_b351_01E02980 vel;
    u8 pad48[4];
    s32 rot[4];
} Flare_b351_01E02980;

static s32 func_01E02980_b351(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101BA0(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    f32 m2[16];
    f32 m1[16];
    Vec4f v;
    Pkt_b351_01E02980 pk __attribute__((aligned(8)));
    f32 dep[3];
    Flare_b351_01E02980 *e;
    s32 i;
    s32 down;
    f32 lo;
    f32 hi;
    f32 st;
    f32 ang;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) != 0) {
            if (e->a1 > e->a0) {
                down = 0;
            } else {
                down = 1;
            }
            if (down) {
                e->a0 -= e->da;
                e->a1 -= e->da;
            } else {
                e->a0 += e->da;
                e->a1 += e->da;
            }
            e->pos.x += e->vel.x;
            e->pos.y += e->vel.y;
            e->pos.z += e->vel.z;
            if (e->life > e->b9) {
                e->r += e->dr;
            }
            func_00101BA0(e, &e->pos);
            func_0020EB40(m1);
            func_0020C940(m2, 0, e->rot, &e->pos);
            func_0020BC00((s32)m1, m2);
            ((Pkt_b351_01E02980 *)(s32)&pk)->count = 0x13;
            ((Pkt_b351_01E02980 *)(s32)&pk)->tag = 6;
            ((Pkt_b351_01E02980 *)(s32)&pk)->regs = 0x414141;
            ((Pkt_b351_01E02980 *)(s32)&pk)->pad = 0;
            pk.v[0].r = e->c0[2];
            pk.v[1].r = pk.v[2].r = e->c1[2];
            pk.v[0].g = e->c0[1];
            pk.v[1].g = pk.v[2].g = e->c1[1];
            pk.v[0].b = e->c0[0];
            pk.v[1].b = pk.v[2].b = e->c1[0];
            pk.v[0].q = pk.v[1].q = pk.v[2].q = 1.0f;
            pk.v[1].a = pk.v[2].a = e->c1[3];
            if (e->life < 8) {
                pk.v[0].a = e->life * (e->c0[3] >> 3);
            } else {
                pk.v[0].a = e->c0[3];
            }
            func_002086D0(&pk, 0x48);
            v.z = 0.0f;
            v.y = 0.0f;
            v.x = 0.0f;
            if (func_00205440(&v, m1, &pk.v[0].xyz, &dep[0]) != 0) {
                if (down) {
                    lo = e->a1;
                    hi = e->a0;
                } else {
                    lo = e->a0;
                    hi = e->a1;
                }
                st = e->step * e->steps;
                for (; lo < hi; lo += st) {
                    ang = 3.1415927f * lo / 180.0f;
                    v.x = e->r * func_001A6898(ang);
                    v.z = e->r * func_001A6A88(ang);
                    if (func_00205440(&v, m1, &pk.v[1].xyz, &dep[1]) != 0) {
                        v.x = e->r * func_001A6898(3.1415927f * (lo + e->step) / 180.0f);
                        v.z = e->r * func_001A6A88(3.1415927f * (lo + e->step) / 180.0f);
                        if (func_00205440(&v, m1, &pk.v[2].xyz, &dep[2]) != 0) {
                            func_002075F0((s32)&pk, ot, (u32)dep[2]);
                        }
                    }
                }
            }
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

static s32 func_01E02E00_b351(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E07A70_b351;
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
    t = D_01E07A70_b351;
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

/* OVL_WARM */

#define ABS_b040_01E03E90(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b040_01E03E90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b040_01E03E90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b040_01E03E90 p;
} Vtx_b040_01E03E90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b040_01E03E90 v[4];
    u8 tail[0x20];
} Pkt_b040_01E03E90;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b040_01E03E90;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 b, g, r;
    u8 pad0B;
    u8 b2, g2, r2, a;
    f32 len;
    f32 width;
    f32 angle;
    f32 spin;
    Vec_b040_01E03E90 pos;
    Vec_b040_01E03E90 vel;
    Vec_b040_01E03E90 point;
} Beam_b040_01E03E90;

extern Tex_b040_01E03E90 D_01E07A90_b351;

static s32 func_01E03850_b351(Beam_b040_01E03E90 *o, s32 target, s32 count) {
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    s32 i;
    s32 h __attribute__((aligned(16)));
    s32 j;
    u8 k;
    f32 zd;
    f32 dy;
    f32 dx;
    f32 len;
    f32 r1;
    f32 w;
    f32 t;
    f32 m2[16];
    f32 m1[16];
    Vec_b040_01E03E90 pt;
    Tex_b040_01E03E90 tex;
    Xyz_b040_01E03E90 q;
    Pkt_b040_01E03E90 pkt __attribute__((aligned(8)));
    f32 dep;

    tex = D_01E07A90_b351;
    h = func_00202BF0(tex.id, tex.kind);
    for (i = 0; i < count; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        o->pos.x += o->vel.x;
        o->pos.y += o->vel.y;
        o->pos.z += o->vel.z;
        o->angle += o->spin;
        pt = o->point;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m2, 0, 0, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b040_01E03E90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b040_01E03E90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b040_01E03E90 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b040_01E03E90 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = 0;
        pkt.v[1].r = pkt.v[2].r = o->r;
        pkt.v[0].g = 0;
        pkt.v[1].g = pkt.v[2].g = o->g;
        pkt.v[0].b = 0;
        pkt.v[1].b = pkt.v[2].b = o->b;
        pkt.v[3].r = o->r2;
        pkt.v[3].g = o->g2;
        pkt.v[3].b = o->b2;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_00101EE0(&pkt, &tex, h);
        if (o->life >= 8 || (o->flags & 0x40)) {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->a;
        } else {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (o->a >> 3) * o->life;
        }
        pkt.v[0].a = 0;
        if (func_00205440(&pt, m1, &q, &dep) == 0 || func_00101600(&q) == 0) {
            continue;
        }
        r1 = func_001018E0(o->len, dep);
        w = func_001018E0(o->width, dep);
        if (o->flags & 0x80) {
            q.z = 0xFFFFFE;
            zd = 0.0f;
        } else {
            zd = dep;
        }
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
        pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
        len = r1;
        if (!(o->flags & 0x40)) {
            if (!(o->flags & 1)) {
                k = o->total - o->life;
                if (k < 8) {
                    len = r1 * (0.125f * k);
                }
            }
            if (o->life < 8) {
                len = r1 * (0.125f * o->life);
            }
        }
        for (j = 0; j < 2; j++) {
            t = 180.0f * j;
            dx = len * func_001A6898(3.1415927f * (o->angle + t) / 180.0f);
            dy = len * func_001A6A88(3.1415927f * (o->angle + t) / 180.0f);
            if (!(ABS_b040_01E03E90(dx) <= ABS_b040_01E03E90(dy))) {
                pkt.v[0].p.x = pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[1].p.x = pkt.v[3].p.x = q.x;
                pkt.v[0].p.y = (u32)(q.y + dy - w);
                pkt.v[1].p.y = (u32)(q.y - w);
                pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[3].p.y = q.y;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.y = (u32)(w + (q.y + dy));
                pkt.v[1].p.y = (u32)(q.y + w);
                func_002075F0(&pkt, target, (u32)zd);
            } else {
                pkt.v[0].p.y = pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[1].p.y = pkt.v[3].p.y = q.y;
                pkt.v[0].p.x = (u32)(q.x + dx - w);
                pkt.v[1].p.x = (u32)(q.x - w);
                pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[3].p.x = q.x;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.x = (u32)(w + (q.x + dx));
                pkt.v[1].p.x = (u32)(q.x + w);
                func_002075F0(&pkt, target, (u32)zd);
            }
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b351", func_01E04150_b351);

/* OVL_WARM: compile warm (its (u32) casts are jal fptoui, func_001A23B0) */

/* shape b040:01E01340, 1016 insns: n beam emitters (0x38 bytes each): on first use the two ends come from
   func_00101BA0 (sel = i0, then i1); the beam a-b is drawn as 4 offset lines of half-width func_001018E0(size,
   depth) at each end, plus the extensions past a (ext0) and past b (ext1), far z with flags & 0x80; the
   extensions use a width the original never sets (r2) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b040_01E01340;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b040_01E01340 xyz;
} Vtx_b040_01E01340;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b040_01E01340 v[4];
    u8 tail[8];
} Pkt_b040_01E01340;

typedef struct {
    u8 b, g, r, a;
} Col_b040_01E01340;

typedef struct {
    f32 x, y, z;
} V3_b040_01E01340;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 inited;
    u8 sel;
    u8 pad7;
    u8 i0;
    u8 i1;
    u8 padA[2];
    f32 size;
    f32 ext0;
    f32 ext1;
    Col_b040_01E01340 c1;
    Col_b040_01E01340 c0;
    V3_b040_01E01340 a;
    V3_b040_01E01340 b;
} Emit_b040_01E01340;

static s32 func_01E04AA0_b351(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101BA0(void *, void *);
    extern f32 func_001018E0(f32, f32);
    s32 i;
    f32 mat[16];
    Vec4f pt[4];
    Vec4f tmp;
    Xyz_b040_01E01340 xy[4];
    f32 dep[4];
    Pkt_b040_01E01340 pkt __attribute__((aligned(8)));
    Emit_b040_01E01340 *e;
    f32 r0;
    f32 r1;
    f32 r2;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (!(e->flags & 1)) {
            e->inited = 1;
            e->sel = e->i0;
            func_00101BA0(e, &tmp);
            e->a.x = tmp.x;
            e->a.y = tmp.y;
            e->a.z = tmp.z;
            e->sel = e->i1;
            func_00101BA0(e, &tmp);
            e->b.x = tmp.x;
            e->b.y = tmp.y;
            e->b.z = tmp.z;
        }
        pt[0].x = e->a.x;
        pt[0].y = e->a.y;
        pt[0].z = e->a.z;
        pt[1].x = e->b.x;
        pt[1].y = e->b.y;
        pt[1].z = e->b.z;
        pt[2].x = e->a.x + e->ext0 * (e->a.x - e->b.x);
        pt[2].y = e->a.y + e->ext0 * (e->a.y - e->b.y);
        pt[2].z = e->a.z + e->ext0 * (e->a.z - e->b.z);
        pt[3].x = e->b.x - e->ext1 * (e->a.x - e->b.x);
        pt[3].y = e->b.y - e->ext1 * (e->a.y - e->b.y);
        pt[3].z = e->b.z - e->ext1 * (e->a.z - e->b.z);
        func_0020EB40(mat);
        ((Pkt_b040_01E01340 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->tag = 8;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b040_01E01340 *)(s32)&pkt)->pad = 0;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_002086D0(&pkt, 0x48);
        if ((e->flags & 2) && (e->life & 1)) {
            pkt.v[0].a = pkt.v[1].a = e->c0.a >> 1;
            pkt.v[2].a = pkt.v[3].a = e->c1.a >> 1;
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        if (func_00205440(&pt[0], mat, &xy[0], &dep[0]) == 0 || func_00205440(&pt[1], mat, &xy[1], &dep[1]) == 0 ||
            (!(e->ext0 <= 0.0f) && func_00205440(&pt[2], mat, &xy[2], &dep[2]) == 0) ||
            (!(e->ext1 <= 0.0f) &&
             (func_00205440(&pt[3], mat, &xy[3], &dep[3]) == 0 || func_00101600(&xy[3]) == 0))) {
            continue;
        }
        r0 = func_001018E0(e->size, dep[0]);
        r1 = func_001018E0(e->size, dep[1]);
        if (e->flags & 0x80) {
            xy[0].z = xy[1].z = xy[2].z = 0xFFFFFE;
            dep[0] = dep[1] = dep[2] = 0.0f;
        }
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
        pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[1].z;
        pkt.v[0].xyz.f = pkt.v[2].xyz.f = pkt.v[1].xyz.f = pkt.v[3].xyz.f = 1;
        pkt.v[2].xyz.y = xy[0].y;
        pkt.v[3].xyz.y = xy[1].y;
        pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
        pkt.v[1].xyz.y = (u32)(xy[1].y - r1);
        pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
        pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[1].x;
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.y = (u32)(xy[0].y + r0);
        pkt.v[1].xyz.y = (u32)(xy[1].y + r1);
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
        pkt.v[1].xyz.x = (u32)(xy[1].x - r1);
        pkt.v[2].xyz.x = xy[0].x;
        pkt.v[3].xyz.x = xy[1].x;
        pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
        pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[1].y;
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[0].xyz.x = (u32)(xy[0].x + r0);
        pkt.v[1].xyz.x = (u32)(xy[1].x + r1);
        func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        pkt.v[3].a = 0;
        if (!(e->ext0 <= 0.0f)) {
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[2].z;
            pkt.v[2].xyz.y = xy[0].y;
            pkt.v[3].xyz.y = xy[2].y;
            pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
            pkt.v[1].xyz.y = (u32)(xy[2].y - r2);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[2].x;
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.y = (u32)(xy[0].y + r0);
            pkt.v[1].xyz.y = (u32)(xy[2].y + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
            pkt.v[1].xyz.x = (u32)(xy[2].x - r2);
            pkt.v[2].xyz.x = xy[0].x;
            pkt.v[3].xyz.x = xy[2].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[2].y;
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
            pkt.v[0].xyz.x = (u32)(xy[0].x + r0);
            pkt.v[1].xyz.x = (u32)(xy[2].x + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[0]);
        }
        if (!(e->ext1 <= 0.0f)) {
            pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[1].z;
            pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[3].z;
            pkt.v[2].xyz.y = xy[1].y;
            pkt.v[3].xyz.y = xy[3].y;
            pkt.v[0].xyz.y = (u32)(xy[1].y - r1);
            pkt.v[1].xyz.y = (u32)(xy[3].y - r2);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[1].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[3].x;
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.y = (u32)(xy[1].y + r1);
            pkt.v[1].xyz.y = (u32)(xy[3].y + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.x = (u32)(xy[1].x - r1);
            pkt.v[1].xyz.x = (u32)(xy[3].x - r2);
            pkt.v[2].xyz.x = xy[1].x;
            pkt.v[3].xyz.x = xy[3].x;
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[1].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[3].y;
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
            pkt.v[0].xyz.x = (u32)(xy[1].x + r1);
            pkt.v[1].xyz.x = (u32)(xy[3].x + r2);
            func_002075F0((s32)&pkt, ot, (u32)dep[1]);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b351", func_01E05A80_b351);

INCLUDE_ASM("asm/nonmatchings/mod/b351", func_01E068F0_b351);

INCLUDE_ASM("asm/nonmatchings/mod/b351", func_01E06BE0_b351);
