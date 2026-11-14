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

static void func_01E00080_b033(Obj_b010_01E00080 *o) {
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

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b024:01E02120, 875 insns, 51 copies: update and draw ribbon emitters (0x58 bytes each); every segment
   is projected straight into the packet's vertex slots and widened on screen */

typedef struct Uvs_b024_01E02120 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b024_01E02120;

typedef struct Rib_b024_01E02120 {
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
} Rib_b024_01E02120;

typedef struct Xyz_b024_01E02120 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b024_01E02120;

typedef struct Pk_b024_01E02120 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b024_01E02120 v[4];
    u64 pad60[3];
} Pk_b024_01E02120;

static inline void b024_01E02120_tag(Pk_b024_01E02120 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2
typedef struct W_tbl_func_01E00410_b033 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E00410_b033;

static s32 func_01E00410_b033(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    Rib_b024_01E02120 *p = arg0;
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
    extern W_tbl_func_01E00410_b033 D_01E06600_b033;
    W_tbl_func_01E00410_b033 tbl_w = D_01E06600_b033;
    Uvs_b024_01E02120 uvs;
    Pk_b024_01E02120 pk;
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
        b024_01E02120_tag((Pk_b024_01E02120 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
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

/* shape b033:01E011C0 (ShFx_Vlt01), 706 insns, 1 copy (-O2,p): ShFx_Vlt02 without the width-growth loop: draws n
   lightning bolts (0x3C-byte emitters), the quad width tripled on odd lives */

typedef struct {
    f32 x, y, z;
} Vec3_b033_01E011C0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b033_01E011C0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b033_01E011C0 xyz;
} Vtx_b033_01E011C0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b033_01E011C0 v[4];
    u8 tail[0x20];
} Pkt_b033_01E011C0;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b033_01E011C0;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b033_01E011C0 a;
    Vec3_b033_01E011C0 b;
    Vec3_b033_01E011C0 *pts;
} Bolt_b033_01E011C0;

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
    u8 b, g, r, a;
    Vec3_b033_01E011C0 p0;
    Vec3_b033_01E011C0 p1;
    Vec3_b033_01E011C0 vel;
} Emit_b033_01E011C0;

typedef struct Wtmpl_b033_01E011C0 {
    Tex_b033_01E011C0 v[2];
} Wtmpl_b033_01E011C0;

#pragma optimization_level 2
#pragma opt_propagation off

static s32 func_01E011C0_b033(void *arg0, s32 ot, s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00102A50(void *);
    extern void func_00101EE0(void *, void *, void *);
    Emit_b033_01E011C0 *e = arg0;
    f32 mat[16];
    Bolt_b033_01E011C0 bolt;
    Vec3_b033_01E011C0 pts[17];
    Xyz_b033_01E011C0 s[3];
    Vec4f v;
    Vec3_b033_01E011C0 ab[2];
    extern Wtmpl_b033_01E011C0 D_01E06660_b033;
    Wtmpl_b033_01E011C0 tmpl_w = D_01E06660_b033;
    Pkt_b033_01E011C0 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    void *tex;
    s32 j;
    s32 st;
    s32 end;
    s32 dx;
    s32 dy;
    f32 fdx;
    f32 fdy;
    f32 w;
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
        ((Pkt_b033_01E011C0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b033_01E011C0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b033_01E011C0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b033_01E011C0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        func_00101EE0(&pkt, &tmpl_w.v[e->texsel], tex);
        if (e->life < bolt.n) {
            st = bolt.n - e->life;
        } else {
            st = 0;
        }
        if ((e->flags & 1) && e->max - e->life < bolt.n) {
            end = e->max - e->life;
        } else {
            end = bolt.n;
        }
        for (j = st; j < end; j++) {
            if (func_00205440(&pts[j], mat, &s[0], &depth[0]) == 0 || func_00101600(&s[0]) == 0 ||
                func_00205440(&pts[j + 1], mat, &s[1], &depth[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            dx = s[0].x - s[1].x;
            fdx = (dx >= 0) ? dx : -dx;
            dy = s[0].y - s[1].y;
            fdy = (dy >= 0) ? dy : -dy;
            w = func_001A6C60(fdx * fdx + fdy * fdy) / e->wdiv;
            if (e->life & 1) {
                w *= 3.0f;
            }
            if (fdx > fdy) {
                pkt.v[0].xyz.y = s[0].y - w;
                pkt.v[1].xyz.y = s[1].y - w;
                pkt.v[2].xyz.y = s[0].y + w;
                pkt.v[3].xyz.y = s[1].y + w;
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[1].x;
            } else {
                pkt.v[0].xyz.x = s[0].x - w;
                pkt.v[1].xyz.x = s[1].x - w;
                pkt.v[2].xyz.x = s[0].x + w;
                pkt.v[3].xyz.x = s[1].x + w;
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
    return 1;
}

#pragma opt_propagation reset
#pragma optimization_level reset

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b033:01E01CD0, 203 insns (-O2,p): steps n emitters (0x38 bytes each): a live one moves by its velocity
   and, unless flags 0 & 3 say it is paused, takes a free particle (0x3C bytes) from its pool, copies its settings,
   colour and velocity into it, snaps to its anchor when 0x5 is set, and places it at a random spread (+-0x14/2
   hundredths) around itself (flag 2: the spread alone) */

typedef struct {
    f32 x, y, z;
} V3_b033_01E01CD0;

typedef struct {
    u8 r, g, b, a;
} Col_b033_01E01CD0;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 padA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 padE[2];
    f32 f10;
    Col_b033_01E01CD0 col;
    f32 a[3];
    f32 b[3];
    V3_b033_01E01CD0 vel;
} Part_b033_01E01CD0;

typedef struct {
    u8 b0;
    u8 pad1[2];
    u8 b3;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    Part_b033_01E01CD0 *pool;
    u8 kind;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 b10;
    u8 b11;
    u8 pad12[2];
    s32 spread;
    f32 f18;
    Col_b033_01E01CD0 col;
    V3_b033_01E01CD0 pos;
    V3_b033_01E01CD0 vel;
} Emit_b033_01E01CD0;

#pragma optimization_level 2

static s32 func_01E01CD0_b033(Emit_b033_01E01CD0 *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, u8, s32, s32);
    extern void func_00101BA0(void *, f32 *);
    f32 v[4];
    Emit_b033_01E01CD0 *e = arg0;
    Part_b033_01E01CD0 *pt;
    s32 i;
    s32 k;
    f32 dx;
    f32 dy;
    f32 dz;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) != 0) {
            e->pos.x += e->vel.x;
            e->pos.y += e->vel.y;
            e->pos.z += e->vel.z;
            if (!(e->b0 & e->b3)) {
                k = func_00101C30(e->pool, 0x3C, e->kind);
                if (k >= 0) {
                    pt = &e->pool[k];
                    func_00101AD0(pt, e->b11, 0, 0xFF);
                    pt->b5 = e->b5;
                    pt->b4 = e->b4;
                    pt->b9 = e->b6;
                    pt->b8 = e->bD;
                    pt->bB = e->bE;
                    pt->bC = e->bF;
                    pt->bD = e->b10;
                    pt->f10 = e->f18;
                    pt->col = e->col;
                    pt->vel = e->vel;
                    if (e->b5 != 0) {
                        func_00101BA0(e, v);
                        e->pos.x = v[0];
                        e->pos.y = v[1];
                        e->pos.z = v[2];
                    }
                    dx = (f32)((func_0019A5C8() >> 4) % e->spread - (e->spread >> 1)) / 100.0f;
                    dy = (f32)((func_0019A5C8() >> 4) % e->spread - (e->spread >> 1)) / 100.0f;
                    dz = (f32)((func_0019A5C8() >> 4) % e->spread - (e->spread >> 1)) / 100.0f;
                    if (e->b4 & 2) {
                        pt->a[0] = dx;
                        pt->a[1] = dy;
                        pt->a[2] = dz;
                    } else {
                        pt->a[0] = e->pos.x + dx;
                        pt->a[1] = e->pos.y + dy;
                        pt->a[2] = e->pos.z + dz;
                        pt->b[0] = e->pos.x - dx;
                        pt->b[1] = e->pos.y - dy;
                        pt->b[2] = e->pos.z - dz;
                    }
                }
            }
        }
    }
    return 1;
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

static s32 func_01E02000_b033(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E06690_b033;
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
    t = D_01E06690_b033;
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

/* shape b213:01E00F90 (ShFx_Core01), 644 insns, 28 copies (-O2,p): update and draw spinning 2-D beams (0x50 bytes
   each): move, project, and draw each as two quads per half-turn, alpha and length fading in and out */

#define ABS_b213_01E00F90(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b213_01E00F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b213_01E00F90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b213_01E00F90 p;
} Vtx_b213_01E00F90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b213_01E00F90 v[4];
    u8 tail[0x20];
} Pkt_b213_01E00F90;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b213_01E00F90;

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
    Vec_b213_01E00F90 pos;
    Vec_b213_01E00F90 vel;
    Vec_b213_01E00F90 point;
} Beam_b213_01E00F90;

#pragma optimization_level 2

static s32 func_01E02B80_b033(void *p, s32 target, s32 count) {
    extern Tex_b213_01E00F90 D_01E066B0_b033;
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
    Beam_b213_01E00F90 *o = p;
    s32 i;
    s32 h __attribute__((aligned(16)));
    s32 j;
    u8 k;
    u8 a;
    s32 s;
    f32 zd;
    f32 dx;
    f32 ady;
    f32 dy;
    f32 len;
    f32 r1;
    f32 w;
    f32 t;
    f32 m2[16];
    f32 m1[16];
    Vec_b213_01E00F90 pt;
    Tex_b213_01E00F90 tex;
    Xyz_b213_01E00F90 q;
    Pkt_b213_01E00F90 pkt __attribute__((aligned(8)));
    f32 dep;

    tex = D_01E066B0_b033;
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
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->pad = 0;
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
        a = o->a;
        s = a >> 3;
        if (o->life >= 8 || (o->flags & 0x40)) {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = a;
        } else {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = s * o->life;
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
            ady = ABS_b213_01E00F90(dy);
            if (!(ABS_b213_01E00F90(dx) <= ady)) {
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

#pragma optimization_level reset

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b033:01E03590, 674 insns: update and draw a pool of jittering particles (0x3C bytes each): move, every
   (mask+1) ticks re-follow the owner and pick a new random offset, frame from the tick (fade-in frames while
   young), project, then one textured sprite whose corners (rounded) follow the flip bits */

typedef struct Part_b033_01E03590 {
    u8 age;
    u8 b1;
    u8 life;
    u8 mask;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    s32 range;
    f32 pos[3];
    f32 vel[3];
    f32 off[3];
} Part_b033_01E03590;

typedef struct Xyz_b033_01E03590 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b033_01E03590;

typedef struct Pk_b033_01E03590 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b033_01E03590 v[4];
    u64 pad60[3];
} Pk_b033_01E03590;

typedef struct Buf_b033_01E03590 {
    u64 tag;
    Pk_b033_01E03590 pk;
} Buf_b033_01E03590;

typedef struct Uvs_b033_01E03590 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b033_01E03590;

typedef struct Scr_b033_01E03590 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b033_01E03590;

static inline void b033_01E03590_tag(Pk_b033_01E03590 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E03590_b033(Part_b033_01E03590 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b033_01E03590 *p = arg0;
    s32 i;
    s32 tex;
    s32 tick;
    s32 frame;
    s32 r;
    f32 half;
    u32 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b033_01E03590 uvs;
    Pk_b033_01E03590 pk __attribute__((aligned(8)));
    Scr_b033_01E03590 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        tick = p->mask & (p->life - p->age);
        if (tick == 0 || p->life - 1 == p->age) {
            if (p->follow != 0) {
                func_00101BA0(p, &tmp);
                p->pos[0] = tmp.x;
                p->pos[1] = tmp.y;
                p->pos[2] = tmp.z;
            }
            r = p->range;
            p->off[0] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
            r = p->range;
            p->off[1] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
            r = p->range;
            p->off[2] = ((func_0019A5C8() >> 4) % r - (r >> 1)) / 100.0f;
        }
        pos.x = p->pos[0] + p->off[0];
        pos.y = p->pos[1] + p->off[1];
        pos.z = p->pos[2] + p->off[2];
        func_0020EB40(m);
        ((Pk_b033_01E03590 *)(u32)&pk)->flags = 0x24;
        ((Pk_b033_01E03590 *)(u32)&pk)->size = 9;
        ((Pk_b033_01E03590 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b033_01E03590 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        frame = tick & 7;
        if (p->age < 4) {
            frame = 7 - p->age;
        }
        if ((p->flags & 1) && frame == 0) {
            p->flags = (p->flags & 0xC7) | (((func_0019A5C8() >> 4) & 3) << 4);
        }
        uvs.b5 = p->bA;
        func_001020B0(&uvs, frame, 0);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
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
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
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
        func_002075F0((s32)&pk, id, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E04020_b033);

/* shape b033:01E04F60 (b033_setVolt), 323 insns, 1 copy (-O2,p): with a flag set, four bolts are taken from the
   emitter pool (stopping when it runs out), each between two of the unit's five joints: bolt 0 from joint 0 to 1, bolt
   1 from joint 1 towards it with a random spread scaled by how far the gap is from the range, bolts 2 and 3 from joint
   2 to joints 3 and 4; then the five joints are picked again (joint 1 fixed, the rest random within the model) */

typedef struct {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 b6[2];
    u8 kind;
    u8 b9[2];
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE[2];
    f32 size;
    u8 col[4];
    f32 pos[3];
    f32 tgt[3];
    f32 off[3];
} Emit_b033_01E04F60;

typedef struct {
    u8 pad0[8];
    s32 unit;
    s32 joint[5];
    u8 pad20[0x180];
    Emit_b033_01E04F60 pool[100];
    u8 pad[0x1C88 - 0x1A0 - 100 * 0x3C];
    f32 range;
} Volt_b033_01E04F60;

#pragma optimization_level 2

static void func_01E04F60_b033(Volt_b033_01E04F60 *g, s32 on) {
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern f32 func_0020D0E0(void *);
    extern s32 func_001F54E0(s32);
    extern s32 func_001F5560(s32, s32, s32);
    Vec4f p[5];
    Vec4f d;
    f32 f;
    s32 i;
    s32 k;
    s32 j;

    while (on != 0) {
        for (i = 0; i < 4; i++) {
            k = func_00101C30(g->pool, 0x3C, 40);
            if (k < 0) {
                break;
            }
            for (j = 0; j < 5; j++) {
                func_001F5620(g->unit, g->joint[j], &p[j]);
            }
            func_00101AD0(&g->pool[k], 12, 0, 0xFF);
            g->pool[k].b5 = 0;
            g->pool[k].b4 = 0;
            g->pool[k].bB = 0;
            g->pool[k].bC = 0;
            g->pool[k].col[0] = 0x80;
            g->pool[k].col[1] = 0x80;
            g->pool[k].col[2] = 0x80;
            g->pool[k].col[3] = 0x80;
            g->pool[k].off[2] = 0.0f;
            g->pool[k].off[1] = 0.0f;
            g->pool[k].off[0] = 0.0f;
            switch (i) {
            case 0:
                g->pool[k].kind = 8;
                g->pool[k].size = 0.8f;
                g->pool[k].bD = 3;
                g->pool[k].pos[0] = p[0].x;
                g->pool[k].pos[1] = p[0].y;
                g->pool[k].pos[2] = p[0].z;
                g->pool[k].tgt[0] = p[1].x;
                g->pool[k].tgt[1] = p[1].y;
                g->pool[k].tgt[2] = p[1].z;
                break;
            case 1:
                g->pool[k].kind = 6;
                g->pool[k].size = 1.2f;
                g->pool[k].bD = 4;
                g->pool[k].pos[0] = p[1].x;
                g->pool[k].pos[1] = p[1].y;
                g->pool[k].pos[2] = p[1].z;
                d.x = p[1].x - p[0].x;
                d.y = p[1].y - p[0].y;
                d.z = p[1].z - p[0].z;
                f = 200.0f * (g->range - func_0020D0E0(&d) >= 0.0f ? g->range - func_0020D0E0(&d)
                                                                    : -(g->range - func_0020D0E0(&d)));
                g->pool[k].tgt[0] = p[1].x + ((func_0019A5C8() >> 4) % (s32)f - ((s32)f >> 1)) / 100.0f;
                g->pool[k].tgt[1] = p[1].y + ((func_0019A5C8() >> 4) % (s32)f - ((s32)f >> 1)) / 100.0f;
                g->pool[k].tgt[2] = p[1].z + ((func_0019A5C8() >> 4) % (s32)f - ((s32)f >> 1)) / 100.0f;
                break;
            case 2:
            case 3:
                g->pool[k].kind = 8;
                g->pool[k].size = 0.8f;
                g->pool[k].bD = 3;
                g->pool[k].pos[0] = p[2].x;
                g->pool[k].pos[1] = p[2].y;
                g->pool[k].pos[2] = p[2].z;
                g->pool[k].tgt[0] = p[i + 1].x;
                g->pool[k].tgt[1] = p[i + 1].y;
                g->pool[k].tgt[2] = p[i + 1].z;
                break;
            }
        }
        break;
    }
    k = func_001F54E0(g->unit);
    g->joint[0] = func_001F5560(g->unit, 1, 1);
    i = (func_0019A5C8() >> 4) % (k - 3) + 3;
    g->joint[1] = func_001F5560(g->unit, i, 0);
    i = (func_0019A5C8() >> 4) % (k - 5) + 3;
    g->joint[2] = func_001F5560(g->unit, i, 0);
    g->joint[3] = func_001F5560(g->unit, i - 2, 0);
    g->joint[4] = func_001F5560(g->unit, i + 2, 0);
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b033", func_01E05470_b033);
