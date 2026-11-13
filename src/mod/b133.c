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

static void func_01E00080_b133(Obj_b010_01E00080 *o) {
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

/* shape b133:01E00410 (ShFx_Qprim01), 484 insns, 1 copy (-O2,p): n quad sprites (0x40-byte emitters): each moves by
   its velocity and grows, is projected through a translation matrix, coloured with a separate fourth-corner colour,
   faded in over its first 8 frames, and drawn as four corner quads around its screen point (twice with flag 2) */

typedef struct {
    f32 x, y, z, w;
} Vec_b133_01E00410;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b133_01E00410;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b133_01E00410 xyz;
} Vtx_b133_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b133_01E00410 v[4];
    u8 tail[0x20];
} Pkt_b133_01E00410;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b133_01E00410;

typedef struct {
    u8 life;
    u8 pad01[3];
    u8 flags;
    u8 pad05[3];
    s32 tex;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    f32 size;
    f32 grow;
    f32 scale;
    Vec_b133_01E00410 pos;
    Vec_b133_01E00410 vel;
} Obj_b133_01E00410;

#pragma optimization_level 2

static s32 func_01E00410_b133(Obj_b133_01E00410 *obj, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern void func_002075F0(void *, s32, s32);
    extern Tex_b133_01E00410 D_01E05380_b133[];
    s32 i;
    Obj_b133_01E00410 *e;
    s32 k;
    f32 rm[16];
    f32 m[16];
    Vec_b133_01E00410 a;
    Xyz_b133_01E00410 xy;
    Pkt_b133_01E00410 pkt __attribute__((aligned(8)));
    f32 d;
    s32 texture __attribute__((aligned(16)));
    f32 w;
    f32 z;

    e = obj;
    texture = func_00202BF0(D_01E05380_b133[e->tex].id, D_01E05380_b133[e->tex].kind);
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->tex > 1) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        e->size += e->grow;
        func_00101BA0(e, &e->pos);
        func_0020EB40(m);
        func_0020C940(rm, 0, 0, &e->pos);
        func_0020BC00(m, rm);
        a.x = a.y = a.z = 0.0f;
        ((Pkt_b133_01E00410 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b133_01E00410 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b133_01E00410 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b133_01E00410 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = e->r0;
        pkt.v[3].r = e->r1;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = e->g0;
        pkt.v[3].g = e->g1;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = e->b0;
        pkt.v[3].b = e->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        func_00101EE0(&pkt, &D_01E05380_b133[e->tex], (void *)texture);
        if (e->life > 7 || (e->flags & 0x40)) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = 0x80;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->life << 4;
        }
        if (func_00205440(&a, m, &xy, &d) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        w = e->size / (d / 256.0f);
        if (e->flags & 0x80) {
            xy.z = 0xFFFFFE;
            z = 0.0f;
        } else {
            z = d;
        }
        if ((e->flags & 1) && (e->life & 1)) {
            w *= e->scale;
        }
        pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xy.z;
        for (k = 0; k < 4; k++) {
            switch (k) {
            case 0:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x - w);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy.x;
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y - w);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = xy.y;
                break;
            case 1:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x + w);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y - w);
                break;
            case 2:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x - w);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y + w);
                break;
            case 3:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x + w);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y + w);
                break;
            }
            func_002075F0(&pkt, ot, (u32)z);
            if (e->flags & 2) {
                func_002075F0(&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}

#pragma optimization_level reset


/* shape b133:01E00BA0 (ShFx_Qprim02), 549 insns, 1 copy (-O2,p): n quad-sprite trails (0x50-byte emitters,
   b133:01E00410 form): each moves by its velocity, then walks its count trail points (16-byte pool records named by
   index bytes): the first point's life/max go to the emitter, the rest copy it; the head point takes the emitter
   position; size grows with the point's age, alpha fades in over 8 frames, each drawn as four corner quads around its
   screen point (twice with flag 4); the head steps back */

typedef struct {
    f32 x, y, z, w;
} Vec_b133_01E00BA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b133_01E00BA0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b133_01E00BA0 xyz;
} Vtx_b133_01E00BA0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b133_01E00BA0 v[4];
    u8 tail[0x20];
} Pkt_b133_01E00BA0;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b133_01E00BA0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    f32 x, y, z;
} Pt_b133_01E00BA0;

typedef struct {
    u8 life;
    u8 pad01;
    u8 max;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    Pt_b133_01E00BA0 *pool;
    u8 idx[8];
    u8 count;
    u8 head;
    u8 pad16[2];
    s32 tex;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    f32 size;
    f32 grow;
    f32 scale;
    Vec_b133_01E00BA0 pos;
    Vec_b133_01E00BA0 vel;
} Obj_b133_01E00BA0;

#pragma optimization_level 2

static s32 func_01E00BA0_b133(Obj_b133_01E00BA0 *obj, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern s32 func_00101B50(void *);
    extern void func_00101EE0(void *, void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern void func_002075F0(void *, s32, s32);
    extern Tex_b133_01E00BA0 D_01E053B0_b133[];
    s32 i;
    Obj_b133_01E00BA0 *e;
    s32 j;
    s32 k;
    Pt_b133_01E00BA0 *c;
    Pt_b133_01E00BA0 *pool;
    f32 m[16];
    Vec_b133_01E00BA0 a;
    Xyz_b133_01E00BA0 xy;
    Pkt_b133_01E00BA0 pkt __attribute__((aligned(8)));
    f32 d;
    s32 texture __attribute__((aligned(16)));
    f32 w;
    f32 z;

    e = obj;
    pool = e->pool;
    texture = func_00202BF0(D_01E053B0_b133[e->tex].id, D_01E053B0_b133[e->tex].kind);
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->tex > 1) {
            continue;
        }
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;
        e->pos.z += e->vel.z;
        func_00101BA0(e, &e->pos);
        func_0020EB40(m);
        e->life = 0;
        for (j = 0; j < e->count; j++) {
            c = &pool[e->idx[j]];
            if (j == 0) {
                e->life = c->life;
                e->max = c->max;
            } else {
                c->life = e->life;
                c->max = e->max;
            }
            if (func_00101B50(c) == 0) {
                continue;
            }
            w = e->size + e->grow * (f32)(c->max - c->life);
            if (j == e->head) {
                c->x = e->pos.x;
                c->y = e->pos.y;
                c->z = e->pos.z;
            }
            a.x = c->x;
            a.y = c->y;
            a.z = c->z;
            ((Pkt_b133_01E00BA0 *)(s32)&pkt)->count = 0x34;
            ((Pkt_b133_01E00BA0 *)(s32)&pkt)->tag = 0xC;
            ((Pkt_b133_01E00BA0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b133_01E00BA0 *)(s32)&pkt)->pad = 0;
            pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = e->r0;
            pkt.v[3].r = e->r1;
            pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = e->g0;
            pkt.v[3].g = e->g1;
            pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = e->b0;
            pkt.v[3].b = e->b1;
            pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
            func_00101EE0(&pkt, &D_01E053B0_b133[e->tex], (void *)texture);
            if ((e->life & 1) && (e->flags & 2)) {
                continue;
            }
            if (c->life > 7 || (e->flags & 0x40)) {
                pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a1;
            } else {
                pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (e->a1 >> 3) * c->life;
            }
            if (func_00205440(&a, m, &xy, &d) == 0) {
                continue;
            }
            if (func_00101600(&xy) == 0) {
                continue;
            }
            w = w / (d / 256.0f);
            if (e->flags & 0x80) {
                xy.z = 0xFFFFFE;
                z = 0.0f;
            } else {
                z = d;
            }
            if ((e->flags & 1) && (c->life & 1)) {
                w *= e->scale;
            }
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xy.z;
            for (k = 0; k < 4; k++) {
                switch (k) {
                case 0:
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x - w);
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy.x;
                    pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y - w);
                    pkt.v[2].xyz.y = pkt.v[3].xyz.y = xy.y;
                    break;
                case 1:
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x + w);
                    pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y - w);
                    break;
                case 2:
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x - w);
                    pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y + w);
                    break;
                case 3:
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)((f32)(u32)xy.x + w);
                    pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)((f32)(u32)xy.y + w);
                    break;
                }
                func_002075F0(&pkt, ot, (u32)z);
                if (e->flags & 4) {
                    func_002075F0(&pkt, ot, (u32)z);
                }
            }
        }
        if (e->head == 0) {
            e->head = e->count - 1;
        } else {
            e->head--;
        }
    }
    return 1;
}

#pragma optimization_level reset

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM: compile warm (its (u32) casts are jal fptoui, func_001A23B0) */

/* shape b133:01E01440, 325 insns: n burst emitters (0x60 bytes each): move and spin, then draw count radial lines
   from a random byte table: angle steps by 20 + table[idx], radius and height from the next two table bytes,
   length 1 + (mask & table), pushed out by the emitter's age; each line drawn twice */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b133_01E01440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b133_01E01440 xyz;
} Vtx_b133_01E01440;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b133_01E01440 v[2];
    u8 tail[8];
} Pk_b133_01E01440;

typedef struct {
    u8 b, g, r, a;
} Col_b133_01E01440;

typedef struct {
    f32 x, y, z;
    u8 padC[4];
} V3_b133_01E01440;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3[5];
    u8 count;
    u8 idx;
    u8 mask;
    u8 padB;
    u8 *tab;
    f32 hscale;
    f32 rscale;
    Col_b133_01E01440 c1;
    Col_b133_01E01440 c0;
    V3_b133_01E01440 pos;
    V3_b133_01E01440 vel;
    s32 rot[4];
    s32 drot[4];
} Emit_b133_01E01440;

#pragma optimization_level 2

static s32 func_01E01440_b133(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020BC00(void *, void *);
    f32 m2[16];
    f32 m[16];
    f32 p[8];
    Pk_b133_01E01440 pk __attribute__((aligned(8)));
    f32 dep;
    Emit_b133_01E01440 *e;
    s32 i;
    s32 j;
    s32 len;
    s32 k;
    f32 ang;
    f32 step;
    f32 c;
    f32 r;
    f32 a;
    f32 h;
    f32 s;
    f32 fl;
    f32 w;

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
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        func_00101BA0(e, &e->pos);
        func_0020EB40(m);
        func_0020C940(m2, NULL, e->rot, &e->pos);
        func_0020BC00(m, m2);
        j = e->idx;
        step = 20.0f + e->tab[j];
        j = (u8)(j + 1);
        ang = 0.0f;
        len = e->max - e->life;
        ((Pk_b133_01E01440 *)(s32)&pk)->flags = 0x11;
        ((Pk_b133_01E01440 *)(s32)&pk)->size = 4;
        ((Pk_b133_01E01440 *)(s32)&pk)->regs = 0x4141;
        ((Pk_b133_01E01440 *)(s32)&pk)->pad4 = 0;
        pk.v[0].r = e->c0.r;
        pk.v[0].g = e->c0.g;
        pk.v[0].b = e->c0.b;
        pk.v[1].r = e->c1.r;
        pk.v[1].g = e->c1.g;
        pk.v[1].b = e->c1.b;
        pk.v[0].q = pk.v[1].q = 1.0f;
        if (e->life < 8) {
            pk.v[0].a = pk.v[1].a = (e->c1.a >> 3) * e->life;
        } else {
            pk.v[0].a = pk.v[1].a = e->c1.a;
        }
        func_002086D0(&pk, 0x48);
        ((Pk_b133_01E01440 *)(s32)&pk)->flags |= 0x400;
        for (k = 0; k < e->count; k++) {
            ang += step;
            if (!(ang <= 360.0f)) {
                ang -= 360.0f;
            }
            r = e->rscale * e->tab[(u8)j] / 255.0f;
            a = 3.1415927f * ang / 180.0f;
            c = r * func_001A6898(a);
            s = r * func_001A6A88(a);
            h = e->hscale * e->tab[(u8)(j + 1)] / 255.0f;
            fl = len;
            p[0] = c * fl;
            p[1] = h * fl;
            p[2] = s * fl;
            w = 1.0f + (e->mask & e->tab[(u8)(j + 2)]);
            j = (u8)(j + 3);
            p[4] = p[0] + c * w;
            p[5] = p[1] + h * w;
            p[6] = p[2] + s * w;
            if (func_00205440(p, m, &pk.v[0].xyz, &dep) != 0 && func_00205440(&p[4], m, &pk.v[1].xyz, &dep) != 0) {
                func_002075F0((s32)&pk, ot, (u32)dep);
                func_002075F0((s32)&pk, ot, (u32)dep);
            }
        }
    }
    return 1;
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
typedef struct W_tbl_func_01E01960_b133 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E01960_b133;

static s32 func_01E01960_b133(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E01960_b133 D_01E053E0_b133;
    W_tbl_func_01E01960_b133 tbl_w = D_01E053E0_b133;
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b042:01E038E0, 339 insns: trail emitters (0x8C bytes each): move, follow a bone, then spawn
   particles (0x58 bytes) along the path from the last three positions (a spline of 4 points, or just the
   last segment when flags & 1). */

typedef struct {
    u8 r, g, b, a;
} Col_b042_01E038E0;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 f5;
    u8 pad6[2];
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
    u8 fC;
    u8 fD;
    u8 padE[2];
    s32 f10;
    f32 len;
    f32 f18;
    f32 f1C;
    f32 f20;
    Col_b042_01E038E0 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 f48[0x10];
} Part_b042_01E038E0;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 attached;
    u8 pad6[2];
    Part_b042_01E038E0 *pool;
    s32 fC;
    u8 kind;
    u8 sub;
    u8 f12;
    u8 f13;
    u8 f14;
    u8 f15;
    u8 f16;
    u8 pad17;
    f32 scale;
    f32 f1C;
    f32 f20;
    f32 f24;
    Col_b042_01E038E0 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
    f32 drift[3];
    u8 pad88[4];
} Emit_b042_01E038E0;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spline_b042_01E038E0;

#pragma optimization_level 2

static s32 func_01E02710_b133(Emit_b042_01E038E0 *arg0, s32 arg1, s32 n) {
    extern void func_00101BA0();
    extern s32 func_00101C30();
    extern void func_00101AD0();
    extern void func_00101940();
    Emit_b042_01E038E0 *e = arg0;
    Spline_b042_01E038E0 spl;
    f32 dir[4];
    s32 i;
    s32 j;
    s32 k;
    s32 idx;
    s32 off;
    f32 len;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) != 0 && e->age != e->life - 1) {
            e->pos.x += e->vel.x;
            e->pos.y += e->vel.y;
            e->pos.z += e->vel.z;
            func_00101BA0(e, &e->pos);
            if (e->attached != 0) {
                e->pos.x += e->off.x;
                e->pos.y += e->off.y;
                e->pos.z += e->off.z;
            }
            if (e->flags & 1) {
                spl.pts[0] = e->pos;
                spl.pts[1] = e->prev;
                k = 1;
            } else {
                spl.n = 3;
                spl.x[0] = e->pos.x;
                spl.y[0] = e->pos.y;
                spl.z[0] = e->pos.z;
                spl.x[1] = e->prev.x;
                spl.y[1] = e->prev.y;
                spl.z[1] = e->prev.z;
                spl.x[2] = e->prev2.x;
                spl.y[2] = e->prev2.y;
                spl.z[2] = e->prev2.z;
                func_00102550(&spl);
                k = 4;
            }
            for (j = 0; j < k; j++) {
                idx = func_00101C30(e->pool, 0x58, e->kind);
                if (idx >= 0) {
                    func_00101AD0(&e->pool[idx], e->sub, 0, 0xFF);
                    dir[0] = spl.pts[j + 1].x - spl.pts[j].x;
                    dir[1] = spl.pts[j + 1].y - spl.pts[j].y;
                    dir[2] = spl.pts[j + 1].z - spl.pts[j].z;
                    len = func_0020D0E0(dir);
                    if (len < 0.3f) {
                        dir[0] += e->drift[0];
                        dir[1] += e->drift[1];
                        dir[2] += e->drift[2];
                    } else if (!(len <= 1.0f)) {
                        func_0020D070(dir);
                    }
                    e->pool[idx].len = func_0020D0E0(dir);
                    if (e->scale) {
                        e->pool[idx].len *= e->scale;
                    }
                    e->pool[idx].f18 = e->f1C;
                    e->pool[idx].flags = 0;
                    if (e->flags & 2) {
                        e->pool[idx].flags |= 4;
                        e->pool[idx].fC = e->f16;
                    }
                    if (e->flags & 4) {
                        e->pool[idx].flags |= 8;
                    }
                    e->pool[idx].f5 = 0;
                    e->pool[idx].f8 = e->f12;
                    e->pool[idx].f1C = e->f20;
                    e->pool[idx].f20 = e->f24;
                    e->pool[idx].f9 = func_0019A5C8() >> 4;
                    e->pool[idx].fA = e->f13;
                    e->pool[idx].fB = e->f14;
                    e->pool[idx].fD = e->f15;
                    e->pool[idx].f10 = e->fC;
                    e->pool[idx].col = e->col;
                    e->pool[idx].pos = spl.pts[j];
                    func_00101940(dir, (u8 *)e->pool + idx * 0x58 + 0x48);
                }
            }
            e->prev2 = e->prev;
            e->prev = e->pos;
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

static s32 func_01E02C60_b133(void *p, s32 target, s32 count) {
    extern Tex_b213_01E00F90 D_01E05440_b133;
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

    tex = D_01E05440_b133;
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

static s32 func_01E03670_b133(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E05460_b133;
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
    t = D_01E05460_b133;
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

INCLUDE_ASM("asm/nonmatchings/mod/b133", func_01E041F0_b133);
