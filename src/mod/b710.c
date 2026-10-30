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

static void func_01E00080_b710(Obj_b002_01E00080 *arg0) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b710", func_01E00440_b710);

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b380:01E01160, 637 insns, 3 copies: moves n arc emitters (0x5C bytes each: an angle window sweeping one way, a
   growing radius) and draws the arc as rings of gouraud quads from the centre outwards, colour fading from the
   inner to the outer colour per ring (or two-tone by flag 1), alpha fading at the end. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b380_01E01160;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b380_01E01160 xyz;
} Vtx_b380_01E01160;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b380_01E01160 v[4];
} Pkt_b380_01E01160;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    u8 n8;
    u8 grow_until;
    u8 rings;
    u8 padB;
    f32 a0;
    f32 a1;
    f32 step;
    f32 spin;
    f32 radius;
    f32 grow;
    u8 b0, g0, r0, al0;
    u8 b1, g1, r1, al1;
    f32 pos[3];
    u8 pad38[4];
    f32 vel[3];
    u8 pad48[4];
    s32 rot[4];
} Arc_b380_01E01160;

#pragma optimization_level 1

static s32 func_01E01160_b710(void *arg0, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat2[16];
    f32 mat[16];
    f32 d[4];
    Vec4f p;
    Pkt_b380_01E01160 pkt;
    Xyz_b380_01E01160 c;
    s32 al[2];
    f32 dc;
    Arc_b380_01E01160 *e;
    s32 i;
    s32 dir;
    s32 k;
    f32 a;
    f32 end;
    f32 astep;
    f32 ang;
    f32 rstep;
    f32 r;
    f32 dr;
    f32 dg;
    f32 db;
    f32 da;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Arc_b380_01E01160 *)((u8 *)e + 0x5C);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->a1 > e->a0) {
            dir = 0;
        } else {
            dir = 1;
        }
        if (dir) {
            e->a0 -= e->spin;
            e->a1 -= e->spin;
        } else {
            e->a0 += e->spin;
            e->a1 += e->spin;
        }
        e->pos[0] += e->vel[0];
        e->pos[1] += e->vel[1];
        e->pos[2] += e->vel[2];
        if (e->life > e->grow_until) {
            e->radius += e->grow;
        }
        func_00101BA0(e, e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b380_01E01160 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b380_01E01160 *)(s32)&pkt)->tag = 8;
        ((Pkt_b380_01E01160 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b380_01E01160 *)(s32)&pkt)->pad = 0;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_002086D0(&pkt, 0x48);
        if (dir) {
            a = e->a1;
            end = e->a0;
        } else {
            a = e->a0;
            end = e->a1;
        }
        astep = e->step * e->n8;
        rstep = e->radius / e->rings;
        dr = (e->r0 - e->r1) / (f32)e->rings;
        dg = (e->g0 - e->g1) / (f32)e->rings;
        db = (e->b0 - e->b1) / (f32)e->rings;
        da = (e->al0 - e->al1) / (f32)e->rings;
        p.x = p.y = p.z = 0.0f;
        if (func_00205440(&p, mat, &c, &dc) == 0) {
            continue;
        }
        for (; a < end; a += astep) {
            pkt.v[2].xyz = c;
            pkt.v[3].xyz = c;
            d[2] = d[3] = dc;
            for (k = 0; k < e->rings; k++) {
                pkt.v[0].xyz = pkt.v[2].xyz;
                d[0] = d[2];
                pkt.v[1].xyz = pkt.v[3].xyz;
                d[1] = d[3];
                if (dir) {
                    ang = a + e->step * k;
                } else {
                    ang = a - e->step * k;
                }
                r = (k + 1) * rstep;
                p.x = r * func_001A6898((3.1415927f * ang) / 180.0f);
                p.z = r * func_001A6A88((3.1415927f * ang) / 180.0f);
                if (func_00205440(&p, mat, &pkt.v[2].xyz, &d[2]) == 0) {
                    continue;
                }
                p.x = r * func_001A6898((3.1415927f * (ang + e->step)) / 180.0f);
                p.z = r * func_001A6A88((3.1415927f * (ang + e->step)) / 180.0f);
                if (func_00205440(&p, mat, &pkt.v[3].xyz, &d[3]) == 0) {
                    continue;
                }
                al[0] = e->al0 - (s32)(da * k);
                al[1] = e->al0 - (s32)(1.0f + da * k);
                if (e->life < 8) {
                    al[0] = e->life * (al[0] >> 3);
                    al[1] = e->life * (al[1] >> 3);
                }
                pkt.v[1].a = pkt.v[0].a = al[0];
                pkt.v[3].a = pkt.v[2].a = al[1];
                if (e->flags & 1) {
                    if (dir) {
                        pkt.v[1].a = pkt.v[3].a = al[0] >> 1;
                        pkt.v[1].r = pkt.v[3].r = e->r1;
                        pkt.v[1].g = pkt.v[3].g = e->g1;
                        pkt.v[1].b = pkt.v[3].b = e->b1;
                        pkt.v[0].r = pkt.v[2].r = e->r0;
                        pkt.v[0].g = pkt.v[2].g = e->g0;
                        pkt.v[0].b = pkt.v[2].b = e->b0;
                    } else {
                        pkt.v[0].a = pkt.v[2].a = al[0] >> 1;
                        pkt.v[1].r = pkt.v[3].r = e->r0;
                        pkt.v[1].g = pkt.v[3].g = e->g0;
                        pkt.v[1].b = pkt.v[3].b = e->b0;
                        pkt.v[0].r = pkt.v[2].r = e->r1;
                        pkt.v[0].g = pkt.v[2].g = e->g1;
                        pkt.v[0].b = pkt.v[2].b = e->b1;
                    }
                } else {
                    pkt.v[0].r = pkt.v[1].r = e->r0 - (s32)(dr * k);
                    pkt.v[2].r = pkt.v[3].r = e->r0 - (s32)(dr * (k + 1));
                    pkt.v[0].g = pkt.v[1].g = e->g0 - (s32)(dg * k);
                    pkt.v[2].g = pkt.v[3].g = e->g0 - (s32)(dg * (k + 1));
                    pkt.v[0].b = pkt.v[1].b = e->b0 - (s32)(db * k);
                    pkt.v[2].b = pkt.v[3].b = e->b0 - (s32)(db * (k + 1));
                }
                if (k == e->rings - 1) {
                    pkt.v[3].a = pkt.v[2].a = 0;
                }
                func_002075F0(&pkt, ot, (u32)((d[3] + (d[2] + (d[0] + d[1]))) / 4.0f));
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b710", func_01E01B60_b710);

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

extern Tex_b011_01E04380 D_01E078C0_b710;

#pragma optimization_level 1

static s32 func_01E02630_b710(Ray_b011_01E04380 *obj, s32 target, s32 count) {
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
    tex0 = D_01E078C0_b710;
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

static s32 func_01E03360_b710(void *arg0, s32 ot, s32 n) {
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

/* shape b710:01E03E40 (ShFx_Cfade), 336 insns, 1 copy (-O1,p): b532:01E025B0's colour fade quad at -O1, object
   pointer as a local copy of the first argument */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b710_01E03E40;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b710_01E03E40;

typedef struct {
    Hdr_b710_01E03E40 h;
    Vtx_b710_01E03E40 v[4];
    u8 tail[8];
} Pkt_b710_01E03E40;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 b, g, r;
} Obj_b710_01E03E40;

#pragma optimization_level 1

static s32 func_01E03E40_b710(s32 arg0, s32 tex) {
    Obj_b710_01E03E40 *o = (Obj_b710_01E03E40 *)arg0;
    Pkt_b710_01E03E40 p __attribute__((aligned(8)));
    u8 a;
    s32 d;
    f32 s;
    f32 c;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b710_01E03E40 *)(s32)&p)->count = 0x14;
    ((Hdr_b710_01E03E40 *)(s32)&p)->tag = 8;
    ((Hdr_b710_01E03E40 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b710_01E03E40 *)(s32)&p)->pad = 0;
    switch (o->flags & 7) {
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
    if (o->cur == 1 && (o->flags & 0x80)) {
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
    p.v[0].r = p.v[1].r = p.v[2].r = p.v[3].r = o->r;
    p.v[0].g = p.v[1].g = p.v[2].g = p.v[3].g = o->g;
    p.v[0].b = p.v[1].b = p.v[2].b = p.v[3].b = o->b;
    p.v[0].q = p.v[1].q = p.v[2].q = p.v[3].q = 1.0f;
    p.v[0].z = p.v[1].z = p.v[2].z = p.v[3].z = 0xFFFFFF;
    func_002086D0(&p, 0x48);
    if (o->flags & 0x10) {
        s = 7168.0f / (o->max >> 1);
        c = 32768.0f;
        d = o->max - o->cur;
        a = (0x80 / (o->max >> 1)) * (d >> 1);
        if ((o->max >> 1) < d) {
            p.v[0].a = p.v[1].a = a;
            d = o->max >> 1;
        } else {
            p.v[0].a = p.v[1].a = 0;
        }
        p.v[2].a = p.v[3].a = 0x80;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = func_001A23B0(c - s * d);
        p.v[2].y = p.v[3].y = func_001A23B0(c);
        func_002075F0((s32)&p, tex, 0);
        p.v[2].a = p.v[3].a = p.v[1].a;
        p.v[1].a = p.v[0].a = 0x80;
        p.v[0].y = p.v[1].y = func_001A23B0(c);
        p.v[2].y = p.v[3].y = func_001A23B0(c + s * d);
        func_002075F0((s32)&p, tex, 0);
    } else {
        p.v[0].a = p.v[1].a = p.v[2].a = p.v[3].a = a;
        p.v[0].x = p.v[2].x = 0x6C00;
        p.v[1].x = p.v[3].x = 0x9400;
        p.v[0].y = p.v[1].y = 0x7200;
        p.v[2].y = p.v[3].y = 0x8E00;
        func_002075F0((s32)&p, tex, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b710", func_01E04380_b710);

/* OVL_WARM */

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b059:01E00E10, 941 insns, 11 copies: b024:01E02120 at -O1 (angle inline, step = 17.0f local, ABS macro): update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b059_01E00E10 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b059_01E00E10;

typedef struct Rib_b059_01E00E10 {
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
} Rib_b059_01E00E10;

typedef struct Xyz_b059_01E00E10 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b059_01E00E10;

typedef struct Pk_b059_01E00E10 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b059_01E00E10 v[4];
    u64 pad60[3];
} Pk_b059_01E00E10;

static inline void b059_01E00E10_tag(Pk_b059_01E00E10 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 1
typedef struct W_tbl_func_01E04F80_b710 {
    Uvs_b059_01E00E10 v[4];
} W_tbl_func_01E04F80_b710;

static s32 func_01E04F80_b710(Rib_b059_01E00E10 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 step;
    f32 b;
    Rib_b059_01E00E10 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    s32 tex;
    u8 k;
    f32 w;
    f32 d;
    f32 a;
    f32 h0;
    s32 life;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E04F80_b710 D_01E07910_b710;
    W_tbl_func_01E04F80_b710 tbl_w = D_01E07910_b710;
    Uvs_b059_01E00E10 uvs;
    Pk_b059_01E00E10 pk;
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
        step = 17.0f;
        ang = 0.0f;
        life = p->life - p->age;
        b059_01E00E10_tag((Pk_b059_01E00E10 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
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
                ang += step;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                v.x = a * b * func_001A6898(3.1415927f * ang / 180.0f);
                v.z = a * b * func_001A6A88(3.1415927f * ang / 180.0f);
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
                dy = ABS(pk.v[2].y - pk.v[0].y);
                dx = ABS(pk.v[2].x - pk.v[0].x);
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b181:01E02D50, 346 insns (b198:01E05C30 at -O1): moves n trail emitters (0x7C bytes each) and drops trail particles into the
   emitter's pool: one at the head (flag 1) or four along a spline through the last three positions. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b181_01E02D50;

typedef struct {
    u8 r, g, b, a;
} C4_b181_01E02D50;

typedef struct {
    u8 pad00[4];
    u8 flags;
    u8 b5;
    u8 pad06[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 pad0E[2];
    s32 w10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    C4_b181_01E02D50 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 x48[0x10];
} Part_b181_01E02D50;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b181_01E02D50 *list;
    s32 w0C;
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 pad17;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    C4_b181_01E02D50 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
} Trail_b181_01E02D50;

#pragma optimization_level 1

static s32 func_01E05E40_b710(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    Spline_b181_01E02D50 sp;
    Vec4f tmp;
    Trail_b181_01E02D50 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Trail_b181_01E02D50 *)((u8 *)e + 0x7C);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->max - 1) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        func_00101BA0(e, &e->pos);
        if (e->follow != 0) {
            e->pos.x += e->off.x;
            e->pos.y += e->off.y;
            e->pos.z += e->off.z;
        }
        if (e->flags & 1) {
            sp.out[0] = e->pos;
            sp.out[1] = e->prev;
            cnt = 1;
        } else {
            sp.n = 3;
            sp.x[0] = e->pos.x;
            sp.y[0] = e->pos.y;
            sp.z[0] = e->pos.z;
            sp.x[1] = e->prev.x;
            sp.y[1] = e->prev.y;
            sp.z[1] = e->prev.z;
            sp.x[2] = e->prev2.x;
            sp.y[2] = e->prev2.y;
            sp.z[2] = e->prev2.z;
            func_00102550(&sp);
            cnt = 4;
        }
        for (k = 0; k < cnt; k++) {
            idx = func_00101C30(e->list, 0x58, e->b10);
            if (idx >= 0) {
                func_00101AD0(&e->list[idx], e->b11, 0, 0xFF);
                e->list[idx].f14 = e->f18;
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 5;
                if (e->flags & 2) {
                    e->list[idx].flags |= 8;
                }
                e->list[idx].bC = e->b16;
                e->list[idx].b5 = 0;
                e->list[idx].b8 = e->b12;
                e->list[idx].f1C = e->f20;
                e->list[idx].f20 = e->f24;
                e->list[idx].b9 = func_0019A5C8() >> 4;
                e->list[idx].bA = e->b13;
                e->list[idx].bB = e->b14;
                e->list[idx].bD = e->b15;
                e->list[idx].w10 = e->w0C;
                e->list[idx].col = e->col;
                e->list[idx].pos = sp.out[k];
                func_00101940(&tmp, e->list[idx].x48);
            }
        }
        e->prev2 = e->prev;
        e->prev = e->pos;
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b710:01E063B0 (b710_vmln), 232 insns (-O1,p): b380:01E04980's slot spawner with b8 = 1, colour 0xB0 (alpha
   0xB0) and second colour 0x60/0x10/0x80 alpha 0x40 */

typedef struct {
    f32 x, y, z, w;
} V4_b710_01E063B0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 a0;
    f32 a1;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 col[4];
    u8 col2[4];
    V4_b710_01E063B0 pos;
    u8 pad3C[0x20];
} Slot_b710_01E063B0;

typedef struct {
    u8 pad0[4];
    s32 skel;
    u8 pad8[8];
    s32 joint;
    u8 pad14[0xDC];
    Slot_b710_01E063B0 slot[100];
} Scene_b710_01E063B0;

#pragma optimization_level 1

static void func_01E063B0_b710(Scene_b710_01E063B0 *g) {
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    V4_b710_01E063B0 p;
    s32 k;

    func_001F5620(g->skel, g->joint, &p);
    k = func_00101C30(g->slot, 0x5C, 0x64);
    if (k >= 0) {
        func_00101AD0(&g->slot[k], 0x18, 0, 0xFF);
        g->slot[k].b4 = 0;
        g->slot[k].b5 = 0;
        g->slot[k].b8 = 1;
        g->slot[k].b9 = 0;
        g->slot[k].bA = 0x10;
        g->slot[k].f1C = 6.0f;
        g->slot[k].col2[2] = 0x80;
        g->slot[k].col2[1] = 0x10;
        g->slot[k].col2[0] = 0x60;
        g->slot[k].col2[3] = 0x40;
        g->slot[k].col[2] = g->slot[k].col[1] = g->slot[k].col[0] = g->slot[k].col[3] = 0xB0;
        g->slot[k].pos = p;
        g->slot[k].f18 = 15.0f;
        g->slot[k].f14 = 12.0f;
        g->slot[k].a0 = 360.0f + (f32)((func_0019A5C8() >> 4) % 360 * 200 - 36000) / 100.0f;
        g->slot[k].a1 = 60.0f + g->slot[k].a0;
        g->slot[k].f20 = 1.0f;
    }
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b710", func_01E06750_b710);
