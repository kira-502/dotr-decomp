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

static void func_01E00080_b208(Obj_b010_01E00080 *o) {
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

/* shape b091:01E00410 (ShFx_Blade), 1182 insns, 43 copies (-O2,p): draws n blade ribbons (0x60 bytes each): shifts
   the two trail-point lists, spawns this frame's points, splines both edges and draws each segment as a quad lerped
   between them, plus up to three flat side quads offset by (dx, dy) */

typedef struct Pool_b091_01E00410 {
    u8 kind;
    u8 pad1[3];
    f32 x, y, z;
} Pool_b091_01E00410;

typedef struct Spl_b091_01E00410 {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spl_b091_01E00410;

typedef struct Rib_b091_01E00410 {
    u8 kind;
    u8 pad1[3];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    Pool_b091_01E00410 *pool;
    s16 idx[2][9];
    u8 slot;
    u8 count;
    u8 selA;
    u8 selB;
    u8 type;
    u8 pad35;
    s16 vset;
    f32 t1;
    f32 t2;
    f32 width;
    u8 b1, g1, r1, a1;
    u8 b2, g2, r2, a2;
    u8 b3, g3, r3, a3;
    f32 dx;
    f32 dy;
    u8 pad58[8];
} Rib_b091_01E00410;

typedef struct Uvs_b091_01E00410 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b091_01E00410;

typedef struct Tbl_b091_01E00410 {
    Uvs_b091_01E00410 v[3];
} Tbl_b091_01E00410;

typedef struct Xyz_b091_01E00410 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b091_01E00410;

typedef struct Vtx_b091_01E00410 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b091_01E00410 xyz;
} Vtx_b091_01E00410;

typedef struct Pk_b091_01E00410 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b091_01E00410 v[4];
    u64 pad70[3];
    u64 b0 : 2;
    u64 abe : 2;
    u64 b4 : 20;
    u64 fix : 10;
    u64 ref : 10;
    u64 b44 : 20;
} Pk_b091_01E00410;

#pragma optimization_level 2

static s32 func_01E00410_b208(Rib_b091_01E00410 *arg0, s32 id, s32 n) {
    extern s32 func_00101AF0();
    extern void func_0020EB40();
    extern void func_00101BA0();
    extern s32 func_00101C30();
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00102550();
    extern s32 func_00202BF0();
    extern s32 func_00205440();
    extern s32 func_00101600();
    extern void func_00101EE0();
    extern void func_002075F0();
    Rib_b091_01E00410 *rib = arg0;
    Pool_b091_01E00410 *pool = arg0->pool;
    Pool_b091_01E00410 *pt;
    s32 i __attribute__((aligned(16)));
    s32 j;
    s32 k;
    s32 idx;
    s32 segs;
    s32 tex0 __attribute__((aligned(16)));
    s32 tex1 __attribute__((aligned(16)));
    s32 tex2 __attribute__((aligned(16)));
    s32 cnt __attribute__((aligned(16)));
    f32 a;
    f32 h0;
    f32 h1;
    f32 m[4][4];
    Spl_b091_01E00410 spl[2];
    Vec4f pos[2];
    Vec4f v[5];
    Vec4f q[2];
    Xyz_b091_01E00410 s[2];
    f32 depth[4];
    extern Tbl_b091_01E00410 D_01E04F00_b208;
    Tbl_b091_01E00410 tbl = D_01E04F00_b208;
    extern Uvs_b091_01E00410 D_01E04F50_b208;
    Uvs_b091_01E00410 tbl1 = D_01E04F50_b208;
    extern Uvs_b091_01E00410 D_01E04F70_b208;
    Uvs_b091_01E00410 tbl2 = D_01E04F70_b208;
    Uvs_b091_01E00410 uvs;
    Pk_b091_01E00410 pk;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            rib++;
        }
        if (func_00101AF0(rib) == 0) {
            continue;
        }
        func_0020EB40(m);
        rib->b5 = 1;
        rib->b6 = rib->selA;
        func_00101BA0(rib, &pos[0]);
        rib->b6 = rib->selB;
        func_00101BA0(rib, &pos[1]);
        for (j = 0; j < 2; j++) {
            for (k = rib->count; k > 0; k--) {
                if (rib->idx[j][k - 1] >= 0) {
                    pt = &pool[rib->idx[j][k - 1]];
                    pt->kind = rib->kind;
                }
                rib->idx[j][k] = rib->idx[j][k - 1];
            }
            if (rib->idx[j][rib->count] >= 0) {
                pt = &pool[rib->idx[j][rib->count]];
                pt->kind = 0;
                rib->idx[j][rib->count] = -1;
            }
        }
        if (rib->kind == 0) {
            continue;
        }
        idx = func_00101C30(pool, 0x10, rib->slot);
        if (idx >= 0) {
            rib->idx[0][0] = idx;
            pt = &pool[rib->idx[0][0]];
            func_00101B40(pt, rib->kind, 0);
            pt->x = pos[0].x;
            pt->y = pos[0].y;
            pt->z = pos[0].z;
        } else {
            rib->idx[0][0] = -1;
        }
        idx = func_00101C30(pool, 0x10, rib->slot);
        if (idx >= 0) {
            rib->idx[1][0] = idx;
            pt = &pool[rib->idx[1][0]];
            func_00101B40(pt, rib->kind, 0);
            pt->x = pos[1].x;
            pt->y = pos[1].y;
            pt->z = pos[1].z;
        } else {
            rib->idx[1][0] = -1;
        }
        for (j = 0; j < 2; j++) {
            spl[j].n = 0;
            for (k = 0; k < rib->count; k++) {
                if (rib->idx[j][k] >= 0) {
                    pt = &pool[rib->idx[j][k]];
                    spl[j].x[spl[j].n] = pt->x;
                    spl[j].y[spl[j].n] = pt->y;
                    spl[j].z[spl[j].n] = pt->z;
                    spl[j].n++;
                }
            }
        }
        if (spl[0].n != spl[1].n || func_00102550(&spl[0]) == 0 || func_00102550(&spl[1]) == 0) {
            continue;
        }
        segs = (spl[0].n - 1) * 4;
        tex0 = func_00202BF0(tbl.v[rib->type].kind, tbl.v[rib->type].tex);
        tex1 = func_00202BF0(tbl1.kind, tbl1.tex);
        tex2 = func_00202BF0(tbl2.kind, tbl2.tex);
        ((Pk_b091_01E00410 *)(u32)&pk)->flags = 0x34;
        ((Pk_b091_01E00410 *)(u32)&pk)->size = 0xC;
        ((Pk_b091_01E00410 *)(u32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pk_b091_01E00410 *)(u32)&pk)->pad4 = 0;
        for (k = 0; k < segs - 1; k++) {
            v[0].x = spl[1].out[k].x + rib->t1 * (spl[0].out[k].x - spl[1].out[k].x);
            v[0].y = spl[1].out[k].y + rib->t1 * (spl[0].out[k].y - spl[1].out[k].y);
            v[0].z = spl[1].out[k].z + rib->t1 * (spl[0].out[k].z - spl[1].out[k].z);
            v[1].x = spl[1].out[k + 1].x + rib->t1 * (spl[0].out[k + 1].x - spl[1].out[k + 1].x);
            v[1].y = spl[1].out[k + 1].y + rib->t1 * (spl[0].out[k + 1].y - spl[1].out[k + 1].y);
            v[1].z = spl[1].out[k + 1].z + rib->t1 * (spl[0].out[k + 1].z - spl[1].out[k + 1].z);
            v[2] = spl[1].out[k];
            v[3] = spl[1].out[k + 1];
            v[4].x = v[0].x + rib->t2 * (v[1].x - v[0].x);
            v[4].y = v[0].y + rib->t2 * (v[1].y - v[0].y);
            v[4].z = v[0].z + rib->t2 * (v[1].z - v[0].z);
            while (rib->flags & 1) {
                if (func_00205440(&v[0], m, &pk.v[0].xyz, &depth[0]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[0].xyz) == 0) {
                    break;
                }
                if (func_00205440(&v[1], m, &pk.v[1].xyz, &depth[1]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[1].xyz) == 0) {
                    break;
                }
                if (func_00205440(&v[2], m, &pk.v[2].xyz, &depth[2]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[2].xyz) == 0) {
                    break;
                }
                if (func_00205440(&v[3], m, &pk.v[3].xyz, &depth[3]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[3].xyz) == 0) {
                    break;
                }
                pk.v[0].r = pk.v[1].r = rib->r1;
                pk.v[2].r = pk.v[3].r = rib->r2;
                pk.v[0].g = pk.v[1].g = rib->g1;
                pk.v[2].g = pk.v[3].g = rib->g2;
                pk.v[0].b = pk.v[1].b = rib->b1;
                pk.v[2].b = pk.v[3].b = rib->b2;
                pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
                pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
                uvs = tbl.v[rib->type];
                if (rib->type != 0 && rib->vset != 0) {
                    uvs.v1 = rib->vset;
                }
                func_00101EE0(&pk, &uvs, tex0);
                switch (rib->type) {
                case 1:
                    pk.abe = 3;
                    pk.fix = 7;
                    pk.ref = 0x80;
                    break;
                case 2:
                    pk.abe = 3;
                    pk.fix = 3;
                    pk.ref = 0x84;
                    break;
                }
                a = (rib->kind < 8 ? (f32)rib->kind * (f32)(u32)rib->a1 / 8.0f : (f32)(u32)rib->a1) / (f32)segs;
                pk.v[2].a = pk.v[3].a = 0;
                pk.v[0].a = (u32)(a * (f32)(segs - k));
                pk.v[1].a = (u32)(a * (f32)(segs - k - 1));
                func_002075F0((s32)&pk, id, 0);
                break;
            }
            cnt = 0;
            if (rib->flags & 2) {
                cnt = 1;
            }
            if (rib->flags & 4) {
                cnt = 3;
            }
            for (j = 0; j < cnt; j++) {
                q[0] = v[0];
                if (rib->flags & 8) {
                    q[1] = v[4];
                } else {
                    q[1] = v[1];
                }
                switch (j) {
                case 1:
                    q[0].x += rib->dx;
                    q[0].y += rib->dy;
                    q[1].x += rib->dx;
                    q[1].y += rib->dy;
                    break;
                case 2:
                    q[0].x -= rib->dx;
                    q[0].y -= rib->dy;
                    q[1].x -= rib->dx;
                    q[1].y -= rib->dy;
                    break;
                }
                if (func_00205440(&q[0], m, &s[0], &depth[0]) == 0) {
                    continue;
                }
                if (func_00101600(&s[0]) == 0) {
                    continue;
                }
                if (func_00205440(&q[1], m, &s[1], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&s[1]) == 0) {
                    continue;
                }
                h0 = h1 = rib->width / (depth[0] / 256.0f);
                if (rib->flags & 8) {
                    h1 = 0.0f;
                    func_00101EE0(&pk, &tbl2, tex2);
                } else {
                    func_00101EE0(&pk, &tbl1, tex1);
                }
                pk.v[0].r = pk.v[2].r = pk.v[1].r = pk.v[3].r = rib->r3;
                pk.v[0].g = pk.v[2].g = pk.v[1].g = pk.v[3].g = rib->g3;
                pk.v[0].b = pk.v[2].b = pk.v[1].b = pk.v[3].b = rib->b3;
                pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
                pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
                a = (rib->kind < 8 ? (f32)rib->kind * (f32)(u32)rib->a3 / 8.0f : (f32)(u32)rib->a3) / (f32)segs;
                pk.v[0].a = pk.v[1].a = (u32)(a * (f32)(segs - k));
                pk.v[2].a = pk.v[3].a = (u32)(a * (f32)(segs - k - 1));
                if (k == 0) {
                    pk.v[0].a = pk.v[1].a = 0;
                }
                pk.v[0].xyz.z = pk.v[1].xyz.z = s[0].z;
                pk.v[2].xyz.z = pk.v[3].xyz.z = s[1].z;
                pk.v[0].xyz.y = (u32)(s[0].y + h0);
                pk.v[1].xyz.y = (u32)(s[0].y - h0);
                pk.v[2].xyz.y = (u32)(s[1].y + h1);
                pk.v[3].xyz.y = (u32)(s[1].y - h1);
                pk.v[0].xyz.x = pk.v[1].xyz.x = s[0].x;
                pk.v[2].xyz.x = pk.v[3].xyz.x = s[1].x;
                func_002075F0((s32)&pk, id, 0);
                pk.v[0].xyz.x = (u32)(s[0].x - h0);
                pk.v[1].xyz.x = (u32)(s[0].x + h0);
                pk.v[2].xyz.x = (u32)(s[1].x - h1);
                pk.v[3].xyz.x = (u32)(s[1].x + h1);
                pk.v[0].xyz.y = pk.v[1].xyz.y = s[0].y;
                pk.v[2].xyz.y = pk.v[3].xyz.y = s[1].y;
                func_002075F0((s32)&pk, id, 0);
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

static s32 func_01E01690_b208(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E04F90_b208;
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
    t = D_01E04F90_b208;
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

extern Tex_b532_01E00080 D_01E04FB0_b208;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E02210_b208(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    tex0 = D_01E04FB0_b208;
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

static s32 func_01E02DA0_b208(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
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
typedef struct W_tbl_func_01E032F0_b208 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E032F0_b208;

static s32 func_01E032F0_b208(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E032F0_b208 D_01E04FD0_b208;
    W_tbl_func_01E032F0_b208 tbl_w = D_01E04FD0_b208;
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

static s32 func_01E040A0_b208(Emit_b042_01E038E0 *arg0, s32 arg1, s32 n) {
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

/* shape b208:01E045F0 (b208), 562 insns, 1 copy (-O2,p): b208, the effect scene manager: code >= 0 clears the scene,
   takes both units, the camera and five joints and sets the frame window 2..154; else counts the frame: 8 starts four
   flares and the light, 40 the blade, 65 the trail emitter, 67 the fade, flare, needle ray and light, 160 ends;
   spreads the four flares between two joints; steps every effect; returns 6 on frames 67..95, else 1/2 on frames
   57/64 */

typedef struct {
    u8 pad0[4];
    u8 on;
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
} Emit_b208_01E045F0;

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
    Emit_b208_01E045F0 emit;
    u16 frames[2];
    Rib_b024_01E02120 rib[0x28];
    Emit_b042_01E038E0 act;
    Rib_b091_01E00410 blade;
    u8 pool[0x140];
    Ray_b532_01E00080 ray;
    Obj_b010_01E05740 fade;
    u8 pad10FD[3];
    Obj_b035_01E00410 flear;
    Obj_b035_01E00410 flears[4];
    s8 tbl[0x100];
    u8 pad137C[4];
} Scene_b208_01E045F0;

#pragma optimization_level 2

static s32 func_01E045F0_b208(Scene_b208_01E045F0 *g, s32 code) {
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
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_01E00410_b208();
    extern s32 func_01E02DA0_b208();
    s32 ot;
    Vec4f v;
    Vec4f a;
    Vec4f b;
    Vec4f *pb;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;
    s32 j;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x1380);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 3; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 1, 1);
        g->m1 = func_001F5560(g->unitA, 0x3E, 0);
        g->m2 = func_001F5560(g->unitA, 0x45, 0);
        g->m3 = func_001F5560(g->unitA, 0xE, 0);
        g->m4 = func_001F5560(g->unitA, 0xC, 0);
        g->frames[0] = 2;
        g->frames[1] = 0x9A;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 8:
        for (i = 0; i < 4; i++) {
            func_00101AD0(&g->flears[i], 0x80, 0, 0xFF);
            g->flears[i].pad5[0] = 0;
            g->flears[i].flags = 0x85;
            g->flears[i].segs = 9;
            g->flears[i].radius = 100.0f + 50.0f * i;
            g->flears[i].grow = 0.0f;
            g->flears[i].ir = g->flears[i].ig = g->flears[i].ib = 0x80;
            g->flears[i].alpha = 0xC0;
            g->flears[i].r = 0x80;
            g->flears[i].g = 0x20;
            g->flears[i].b = 0x60;
        }
        func_00101AD0(&g->emit, 0x80, 0, 0xFF);
        g->emit.b5 = 1;
        g->emit.b6 = g->m3;
        g->emit.on = 4;
        g->emit.f14 = 1.6f;
        g->emit.f18 = 1.6f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 6.0f;
        break;
    case 0x28:
        func_00101AD0(&g->blade, 0xFF, 0, 0xFF);
        g->blade.flags = 1;
        g->blade.pool = (Pool_b091_01E00410 *)g->pool;
        g->blade.slot = 0x14;
        g->blade.count = 8;
        g->blade.selA = g->m3;
        g->blade.selB = g->m4;
        g->blade.t1 = 1.0f;
        g->blade.type = 0;
        g->blade.vset = 0;
        g->blade.width = 10.0f;
        g->blade.b1 = 0x80;
        g->blade.g1 = 0x80;
        g->blade.r1 = 0x80;
        g->blade.a1 = 0xC0;
        g->blade.r2 = 0xC0;
        g->blade.g2 = 0x10;
        g->blade.b2 = 0x80;
        for (j = 0; j < g->blade.count + 1; j++) {
            g->blade.idx[0][j] = g->blade.idx[1][j] = -1;
        }
        break;
    case 0x41:
        func_00101AD0(&g->act, 9, 0, 0xFF);
        g->act.flags = 2;
        g->act.attached = 1;
        g->act.pad6[0] = g->m3;
        g->act.pool = (Part_b042_01E038E0 *)g->rib;
        g->act.kind = 0x28;
        g->act.f12 = 0xC;
        g->act.sub = 0x20;
        g->act.f13 = 2;
        g->act.f16 = 2;
        g->act.f14 = 4;
        g->act.scale = 2.0f;
        g->act.f1C = 0.5f;
        g->act.f20 = 70.0f;
        g->act.fC = (s32)g->tbl;
        g->act.col.b = g->act.col.g = g->act.col.r = g->act.col.a = 0x80;
        func_001F5620(g->unitA, g->m3, &g->act.prev);
        g->act.prev2 = g->act.prev;
        break;
    case 0x43:
        func_00101AD0(&g->fade, 8, 0, 0xFF);
        g->fade.flags = 1;
        func_00101AD0(&g->flear, 0x20, 0, 0xFF);
        g->flear.pad5[0] = 0;
        g->flear.flags = 0x81;
        g->flear.segs = 9;
        g->flear.radius = 600.0f;
        g->flear.grow = 0.0f;
        g->flear.ir = g->flear.ig = g->flear.ib = 0xC0;
        g->flear.r = 0x20;
        g->flear.g = 0x20;
        g->flear.b = 0x80;
        g->flear.alpha = 0xD0;
        g->flear.org.x = g->flear.org.y = g->flear.org.z = 0;
        g->flear.pos = *(V4_b035_01E00410 *)&v;
        func_00101AD0(&g->ray, 0x1C, 0, 0xFF);
        g->ray.flags = 4;
        g->ray.flags |= 1;
        g->ray.texkind = 0;
        g->ray.texmode = 4;
        g->ray.size = 1.5f;
        g->ray.width = 30.0f;
        g->ray.a0 = 0;
        g->ray.a1 = 0x60;
        g->ray.segments = 0xA0;
        g->ray.spin[0] = 0x40;
        g->ray.spin[1] = 0x80;
        g->ray.spin[2] = 0x100;
        g->ray.pad05[0] = 0;
        g->ray.texpage = 2;
        g->ray.index = func_0019A5C8() >> 4;
        g->ray.table = (u8 *)g->tbl;
        g->ray.r0 = g->ray.g0 = g->ray.b0 = g->ray.r1 = g->ray.g1 = g->ray.b1 = 0x80;
        g->ray.pos = *(Vec_b532_01E00080 *)&v;
        func_00101AD0(&g->emit, 0x20, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.6f;
        g->emit.f18 = 1.6f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 80.0f;
        g->emit.f50 = 6.0f;
        g->emit.pos = v;
        break;
    case 0xA0:
        return 8;
    }
    if (g->flears[0].cur) {
        func_001F5620(g->unitA, g->m3, &a);
        func_001F5620(g->unitA, g->m4, pb = &b);
        dx = (a.x - pb->x) / 4.0f;
        dy = (a.y - b.y) / 4.0f;
        dz = (a.z - b.z) / 4.0f;
        for (j = 0; j < 4; j++) {
            g->flears[j].pos.x = pb->x + dx * j;
            g->flears[j].pos.y = b.y + dy * j;
            g->flears[j].pos.z = b.z + dz * j;
        }
    }
    func_01E00080_b208((Obj_b010_01E00080 *)&g->emit);
    func_001031C0(g->frames, g->t);
    func_01E02DA0_b208(&g->fade, ot);
    func_01E00410_b208(&g->blade, ot, 1);
    func_01E02210_b208(&g->ray, ot, 1);
    func_01E01690_b208(&g->flear, ot, 1);
    func_01E01690_b208(g->flears, ot, 4);
    func_01E040A0_b208(&g->act, ot, 1);
    func_01E032F0_b208(g->rib, ot, 0x28);
    if (g->t >= 0x43 && g->t < 0x60) {
        return 6;
    }
    switch (g->t) {
    case 0x39:
        return 1;
    case 0x40:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
