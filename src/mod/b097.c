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

static void func_01E00080_b097(Obj_b002_01E00080 *arg0) {
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

/* shape b097:01E00440 (ShFx_Blade), 1294 insns, 7 copies (-O1,p): ShFx_Blade variant, -O1 build of b091:01E00410's
   source */

typedef struct Pool_b097_01E00440 {
    u8 kind;
    u8 pad1[3];
    f32 x, y, z;
} Pool_b097_01E00440;

typedef struct Spl_b097_01E00440 {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spl_b097_01E00440;

typedef struct Rib_b097_01E00440 {
    u8 kind;
    u8 pad1[3];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    Pool_b097_01E00440 *pool;
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
} Rib_b097_01E00440;

typedef struct Uvs_b097_01E00440 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b097_01E00440;

typedef struct Tbl_b097_01E00440 {
    Uvs_b097_01E00440 v[3];
} Tbl_b097_01E00440;

typedef struct Xyz_b097_01E00440 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b097_01E00440;

typedef struct Vtx_b097_01E00440 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b097_01E00440 xyz;
} Vtx_b097_01E00440;

typedef struct Pk_b097_01E00440 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b097_01E00440 v[4];
    u64 pad70[3];
    u64 b0 : 2;
    u64 abe : 2;
    u64 b4 : 20;
    u64 fix : 10;
    u64 ref : 10;
    u64 b44 : 20;
} Pk_b097_01E00440;

#pragma optimization_level 1

static s32 func_01E00440_b097(Rib_b097_01E00440 *arg0, s32 id, s32 n) {
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
    Rib_b097_01E00440 *rib = arg0;
    Pool_b097_01E00440 *pool = arg0->pool;
    Pool_b097_01E00440 *pt;
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
    Spl_b097_01E00440 spl[2];
    Vec4f pos[2];
    Vec4f v[5];
    Vec4f q[2];
    Xyz_b097_01E00440 s[2];
    f32 depth[4];
    extern Tbl_b097_01E00440 D_01E07100_b097;
    Tbl_b097_01E00440 tbl = D_01E07100_b097;
    extern Uvs_b097_01E00440 D_01E07150_b097;
    Uvs_b097_01E00440 tbl1 = D_01E07150_b097;
    extern Uvs_b097_01E00440 D_01E07170_b097;
    Uvs_b097_01E00440 tbl2 = D_01E07170_b097;
    Uvs_b097_01E00440 uvs;
    Pk_b097_01E00440 pk;

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
        ((Pk_b097_01E00440 *)(u32)&pk)->flags = 0x34;
        ((Pk_b097_01E00440 *)(u32)&pk)->size = 0xC;
        ((Pk_b097_01E00440 *)(u32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pk_b097_01E00440 *)(u32)&pk)->pad4 = 0;
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
                a = (rib->kind < 8 ? (f32)(u32)rib->kind * (f32)(u32)rib->a1 / 8.0f : (f32)(u32)rib->a1) / (f32)segs;
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
                h0 = rib->width / (depth[0] / 256.0f);
                if (rib->flags & 8) {
                    h1 = 0.0f;
                    func_00101EE0(&pk, &tbl2, tex2);
                } else {
                    h1 = rib->width / (depth[0] / 256.0f);
                    func_00101EE0(&pk, &tbl1, tex1);
                }
                pk.v[0].r = pk.v[2].r = pk.v[1].r = pk.v[3].r = rib->r3;
                pk.v[0].g = pk.v[2].g = pk.v[1].g = pk.v[3].g = rib->g3;
                pk.v[0].b = pk.v[2].b = pk.v[1].b = pk.v[3].b = rib->b3;
                pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
                pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
                a = (rib->kind < 8 ? (f32)(u32)rib->kind * (f32)(u32)rib->a3 / 8.0f : (f32)(u32)rib->a3) / (f32)segs;
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

static s32 func_01E01880_b097(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E07190_b097;
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
    t = D_01E07190_b097;
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
/* OVL_WARM: compile warm (its (u32) cast is jal fptoui, func_001A23B0) */

/* shape b097:01E025A0, 813 insns: ribbon emitters (0x74 bytes each, family of b029:01E02B80): either moving ones
   (pos += vel, rot += drot) or ones aimed at a target point (flags & 2); each draws count streaks from its origin to
   points read from a byte table (raw offsets with flags & 1, else a spiral of radius/height bytes), widened on
   screen; alpha fades in over the first 16 ticks on the far edge. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b097_01E025A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b097_01E025A0 xyz;
} Vtx_b097_01E025A0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b097_01E025A0 v[4];
    u8 tail[0x20];
} Pkt_b097_01E025A0;

typedef struct {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b097_01E025A0;

typedef struct {
    u8 age;
    u8 pad1;
    u8 life;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 count;
    u8 k;
    u8 padA[2];
    u8 *pts;
    f32 scale;
    f32 rad;
    f32 width;
    u8 b0, g0, r0, a0;
    u8 b1, g1, r1, a1;
    Vec4f pos;
    Vec4f tgt;
    Vec4f vel;
    s32 rot[4];
    s32 drot[4];
} Rib_b097_01E025A0;

#pragma optimization_level 1
typedef struct W_tbl_func_01E025A0_b097 {
    Uvs_b097_01E025A0 v[2];
} W_tbl_func_01E025A0_b097;

static s32 func_01E025A0_b097(Rib_b097_01E025A0 *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    Rib_b097_01E025A0 *e = arg0;
    s32 i;
    u8 k;
    s32 life;
    s32 j;
    s32 texA;
    s32 texB;
    f32 b;
    f32 zf;
    f32 ang;
    f32 half;
    f32 z;
    f32 x;
    f32 step;
    f32 y;
    f32 w2;
    f32 w;
    f32 m2[16];
    f32 m[16];
    f32 dep[4];
    Xyz_b097_01E025A0 s[4];
    Vec4f v[3];
    extern W_tbl_func_01E025A0_b097 D_01E071B0_b097;
    W_tbl_func_01E025A0_b097 tbl_w = D_01E071B0_b097;
    Pkt_b097_01E025A0 pkt;

    texA = func_00202BF0(tbl_w.v[0].kind, tbl_w.v[0].tex);
    texB = func_00202BF0(tbl_w.v[1].kind, tbl_w.v[1].tex);
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        k = e->k;
        step = 20.0f + (f32)(u32)e->pts[k];
        k++;
        ang = 0.0f;
        life = e->life - e->age;
        ((Pkt_b097_01E025A0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b097_01E025A0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b097_01E025A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b097_01E025A0 *)(s32)&pkt)->pad = 0;
        func_0020EB40(m);
        if (e->flags & 2) {
            if (func_00205440(&e->tgt, m, &s[3], &dep[3]) == 0 || func_00101600(&s[3]) == 0) {
                continue;
            }
            func_0020C940(m2, NULL, e->rot, &e->tgt);
            pkt.v[0].r = pkt.v[1].r = e->r0;
            pkt.v[0].g = pkt.v[1].g = e->g0;
            pkt.v[0].b = pkt.v[1].b = e->b0;
            pkt.v[2].r = pkt.v[3].r = e->r1;
            pkt.v[2].g = pkt.v[3].g = e->g1;
            pkt.v[2].b = pkt.v[3].b = e->b1;
            if (e->age < 16) {
                pkt.v[2].a = pkt.v[3].a = (e->a1 >> 4) * e->age;
            } else {
                pkt.v[2].a = pkt.v[3].a = e->a1;
            }
            pkt.v[0].a = pkt.v[1].a = 0;
            func_00101EE0(&pkt, &tbl_w.v[1], texB);
        } else {
            e->pos.x += e->vel.x;
            e->pos.y += e->vel.y;
            e->pos.z += e->vel.z;
            e->rot[0] += e->drot[0];
            e->rot[1] += e->drot[1];
            e->rot[2] += e->drot[2];
            func_00101BA0(e, &e->pos);
            func_0020C940(m2, NULL, e->rot, &e->pos);
            pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = e->r0;
            pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = e->g0;
            pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = e->b0;
            pkt.v[3].r = e->r1;
            pkt.v[3].g = e->g1;
            pkt.v[3].b = e->b1;
            if (e->age < 16) {
                pkt.v[3].a = (e->a1 >> 4) * e->age;
            } else {
                pkt.v[3].a = e->a1;
            }
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = 0;
            func_00101EE0(&pkt, &tbl_w.v[0], texA);
        }
        if (func_00205440(&e->pos, m, &s[2], &dep[2]) == 0 || func_00101600(&s[2]) == 0) {
            continue;
        }
        func_0020BC00(m, m2);
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        for (j = 0; j < e->count; j++) {
            if (e->flags & 1) {
                x = e->scale * (f32)(e->pts[k] - e->pts[k + 1]) / 255.0f;
                y = e->scale * (f32)(e->pts[k + 2] - e->pts[k + 3]) / 255.0f;
                z = e->scale * (f32)(e->pts[k + 4] - e->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += step;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                b = e->rad * (f32)(u32)e->pts[k++] / 255.0f;
                x = b * func_001A6898(3.1415927f * ang / 180.0f);
                z = b * func_001A6A88(3.1415927f * ang / 180.0f);
                half = e->scale / 2.0f;
                y = half + half * (f32)(u32)e->pts[k++] / 255.0f;
            }
            v[0].x = x * life;
            v[0].y = y * life;
            v[0].z = z * life;
            if (func_00205440(&v[0], m, &s[0], &dep[0]) == 0 || func_00101600(&s[0]) == 0) {
                continue;
            }
            w = e->width / (dep[0] / 256.0f);
            if (dep[0] < dep[2]) {
                zf = dep[0];
            } else {
                zf = dep[2];
            }
            if (e->flags & 2) {
                pkt.v[1].xyz.z = s[0].z;
                if (((s[2].x - s[0].x) >= 0 ? s[2].x - s[0].x : -(s[2].x - s[0].x)) >
                    ((s[2].y - s[0].y) >= 0 ? s[2].y - s[0].y : -(s[2].y - s[0].y))) {
                    pkt.v[1].xyz.y = (u32)((f32)(u32)s[0].y + w);
                    pkt.v[1].xyz.x = s[0].x;
                } else {
                    pkt.v[1].xyz.x = (u32)((f32)(u32)s[0].x + w);
                    pkt.v[1].xyz.y = s[0].y;
                }
                pkt.v[0].xyz = s[0];
                pkt.v[2].xyz = s[2];
                pkt.v[3].xyz = s[3];
            } else {
                w2 = e->width / (dep[2] / 256.0f);
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = s[0].z;
                pkt.v[2].xyz.z = pkt.v[3].xyz.z = s[2].z;
                if (((s[2].x - s[0].x) >= 0 ? s[2].x - s[0].x : -(s[2].x - s[0].x)) >
                    ((s[2].y - s[0].y) >= 0 ? s[2].y - s[0].y : -(s[2].y - s[0].y))) {
                    pkt.v[0].xyz.y = (u32)((f32)(u32)s[0].y - w);
                    pkt.v[1].xyz.y = (u32)((f32)(u32)s[2].y - w2);
                    pkt.v[2].xyz.y = s[0].y;
                    pkt.v[3].xyz.y = s[2].y;
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = s[0].x;
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = s[2].x;
                } else {
                    pkt.v[0].xyz.x = (u32)((f32)(u32)s[0].x - w);
                    pkt.v[1].xyz.x = (u32)((f32)(u32)s[2].x - w2);
                    pkt.v[2].xyz.x = s[0].x;
                    pkt.v[3].xyz.x = s[2].x;
                    pkt.v[0].xyz.y = pkt.v[2].xyz.y = s[0].y;
                    pkt.v[1].xyz.y = pkt.v[3].xyz.y = s[2].y;
                }
            }
            pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
            func_002075F0(&pkt, ot, (u32)zf);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b097:01E03260, 504 insns: spawners (0x2C bytes) riding a ribbon emitter (the b029:01E03660 / b011:01E01690
   kind): splines the ribbon's two pool trails, then for each of count segments spawns a 0x74-byte particle between
   the lerped points (direction along the band, or from the outer trail with flags & 2; sub-type stepping down per
   segment with flags & 1). */

typedef struct {
    u8 kind;
    u8 pad1[3];
    f32 x, y, z;
} Pool_b097_01E03260;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spl_b097_01E03260;

typedef struct {
    u8 kind;
    u8 pad1[3];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    Pool_b097_01E03260 *pool;
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
} Rib_b097_01E03260;

typedef struct {
    u8 r, g, b, a;
} Col_b097_01E03260;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 padA[2];
    s32 wC;
    f32 len;
    f32 f14;
    f32 f18;
    Col_b097_01E03260 c0;
    Col_b097_01E03260 c1;
    Vec4f a;
    Vec4f b;
    u8 pad44[0x10];
    u8 x54[0x20];
} Part_b097_01E03260;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 pad5[3];
    Rib_b097_01E03260 *rib;
    Part_b097_01E03260 *pool;
    s32 w10;
    u8 slot;
    u8 sub;
    u8 b16;
    u8 count;
    f32 scale;
    f32 f1C;
    f32 f20;
    Col_b097_01E03260 c0;
    Col_b097_01E03260 c1;
} Spawn_b097_01E03260;

#pragma optimization_level 1

static s32 func_01E03260_b097(Spawn_b097_01E03260 *arg0, s32 unused, s32 n) {
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern s32 func_00102550(void *);
    extern f32 func_0020D0E0(void *);
    extern void func_0020D070(void *);
    extern void func_00101940(void *, void *);
    extern s32 func_0019A5C8(void);
    Spawn_b097_01E03260 *e = arg0;
    s32 i;
    Rib_b097_01E03260 *rib;
    s32 k;
    s32 idx;
    Pool_b097_01E03260 *pool;
    Pool_b097_01E03260 *pt;
    s32 j;
    Spl_b097_01E03260 spl[2];
    Vec4f d;
    Vec4f p0;
    Vec4f p1;
    Vec4f q;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0 || e->rib == NULL) {
            continue;
        }
        rib = e->rib;
        pool = rib->pool;
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
        for (k = 0; k < e->count; k++) {
            p0.x = spl[1].out[k].x + rib->t1 * (spl[0].out[k].x - spl[1].out[k].x);
            p0.y = spl[1].out[k].y + rib->t1 * (spl[0].out[k].y - spl[1].out[k].y);
            p0.z = spl[1].out[k].z + rib->t1 * (spl[0].out[k].z - spl[1].out[k].z);
            p1.x = spl[1].out[k + 1].x + rib->t1 * (spl[0].out[k + 1].x - spl[1].out[k + 1].x);
            p1.y = spl[1].out[k + 1].y + rib->t1 * (spl[0].out[k + 1].y - spl[1].out[k + 1].y);
            p1.z = spl[1].out[k + 1].z + rib->t1 * (spl[0].out[k + 1].z - spl[1].out[k + 1].z);
            q = spl[1].out[k];
            idx = func_00101C30(e->pool, 0x74, e->slot);
            if (idx < 0) {
                continue;
            }
            func_00101AD0(&e->pool[idx], (u8)(e->sub - ((e->flags & 1) ? k : 0)), 0, 0xFF);
            if (e->flags & 2) {
                d.x = p1.x - p0.x;
                d.y = p1.y - p0.y;
                d.z = p1.z - p0.z;
            } else {
                d.x = p0.x - q.x;
                d.y = p0.y - q.y;
                d.z = p0.z - q.z;
            }
            if (!(func_0020D0E0(&d) <= 1.0f)) {
                func_0020D070(&d);
            }
            e->pool[idx].len = func_0020D0E0(&d);
            if (e->scale) {
                e->pool[idx].len *= e->scale;
            }
            e->pool[idx].f14 = e->f1C;
            e->pool[idx].flags = 2;
            e->pool[idx].b5 = 0;
            e->pool[idx].b8 = e->b16;
            e->pool[idx].f18 = e->f20;
            e->pool[idx].b9 = func_0019A5C8() >> 4;
            e->pool[idx].wC = e->w10;
            e->pool[idx].c0 = e->c0;
            e->pool[idx].c1 = e->c1;
            e->pool[idx].a = p0;
            e->pool[idx].b = p1;
            func_00101940(&d, e->pool[idx].x54);
        }
    }
    return 1;
}
#pragma optimization_level reset

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
typedef struct W_tbl_func_01E03A40_b097 {
    Uvs_b059_01E00E10 v[4];
} W_tbl_func_01E03A40_b097;

static s32 func_01E03A40_b097(Rib_b059_01E00E10 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E03A40_b097 D_01E071E0_b097;
    W_tbl_func_01E03A40_b097 tbl_w = D_01E071E0_b097;
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

/* shape b198:01E05C30, 260 insns, 4 copies: moves n trail emitters (0x7C bytes each) and drops trail particles into the
   emitter's pool: one at the head (flag 1) or four along a spline through the last three positions. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b097_01E04900;

typedef struct {
    u8 r, g, b, a;
} C4_b097_01E04900;

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
    C4_b097_01E04900 col;
    Vec4f pos;
    u8 pad38[0x10];
    u8 x48[0x10];
} Part_b097_01E04900;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b097_01E04900 *list;
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
    C4_b097_01E04900 col;
    Vec4f pos;
    Vec4f prev;
    Vec4f prev2;
    Vec4f vel;
    Vec4f off;
    Vec4f drift;
} Trail_b097_01E04900;

#pragma optimization_level 1

static s32 func_01E04900_b097(void *arg0, s32 arg1, s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00102550(void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101940(void *, void *);
    extern f32 func_0020D0E0(void *);
    extern void func_0020D070(void *);
    Spline_b097_01E04900 sp;
    Vec4f tmp;
    Trail_b097_01E04900 *e;
    s32 i;
    s32 k;
    s32 cnt;
    s32 idx;
    f32 f;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Trail_b097_01E04900 *)((u8 *)e + 0x8C);
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
                tmp.x = sp.out[k + 1].x - sp.out[k].x;
                tmp.y = sp.out[k + 1].y - sp.out[k].y;
                tmp.z = sp.out[k + 1].z - sp.out[k].z;
                f = func_0020D0E0(&tmp);
                if (f < 0.3f) {
                    tmp.x += e->drift.x;
                    tmp.y += e->drift.y;
                    tmp.z += e->drift.z;
                } else if (f > 1.0f) {
                    func_0020D070(&tmp);
                }
                e->list[idx].f14 = func_0020D0E0(&tmp);
                if (e->f18) {
                    e->list[idx].f14 *= e->f18;
                }
                e->list[idx].f18 = e->f1C;
                e->list[idx].flags = 0;
                if (e->flags & 2) {
                    e->list[idx].flags |= 4;
                    e->list[idx].bC = e->b16;
                }
                if (e->flags & 4) {
                    e->list[idx].flags |= 8;
                }
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

extern Tab_b059_01E00440 D_01E07240_b097;

#pragma optimization_level 1

static s32 func_01E04FE0_b097(void *arg0, s32 ot, s32 n) {
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
    tab = D_01E07240_b097;
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

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b097_01E059B0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b097_01E059B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b097_01E059B0;

typedef struct {
    u64 st;
    Xyz_b097_01E059B0 p;
} Vtx_b097_01E059B0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Col_b097_01E059B0 c;
    Vtx_b097_01E059B0 v[4];
    u8 tail[0x20];
} Pkt_b097_01E059B0;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b097_01E059B0;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 page;
    u8 texkind;
    u8 frame;
    u8 shift;
    u8 b, g, r, a;
    f32 width;
    f32 grow;
    f32 gravity;
    f32 floor;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Fx_b097_01E059B0;

#pragma optimization_level 1

static s32 func_01E059B0_b097(Fx_b097_01E059B0 *obj, s32 target, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 m[16];
    Vec_b097_01E059B0 a;
    Tex_b097_01E059B0 tex;
    Pkt_b097_01E059B0 pkt __attribute__((aligned(8)));
    Xyz_b097_01E059B0 xy;
    f32 d;
    Fx_b097_01E059B0 *e;
    s32 age;
    s32 i;
    s32 fr;
    f32 w;
    s32 texture;

    e = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Fx_b097_01E059B0 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            texture = func_00202BF0(5, e->texkind);
        } else {
            texture = func_00202BF0(4, 2);
        }
        e->vx += e->ax;
        e->vy += e->ay + e->gravity;
        e->vz += e->az;
        e->x += e->vx;
        e->y += e->vy;
        e->z += e->vz;
        e->width += e->grow;
        if (e->y < e->floor) {
            e->y = e->floor;
        }
        a.x = e->x;
        a.y = e->y;
        a.z = e->z;
        func_0020EB40(m);
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->tag = 9;
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b097_01E059B0 *)(s32)&pkt)->pad = 0;
        pkt.c.r = e->r;
        pkt.c.g = e->g;
        pkt.c.b = e->b;
        pkt.c.q = 1.0f;
        age = e->total - e->life;
        fr = e->frame;
        if (e->flags & 8) {
            fr = ((age >> e->shift) & 3) + 2;
            if (age < 3) {
                fr = age;
            }
            if (e->life < 7) {
                fr = 7 - (e->life >> e->shift);
            }
        }
        tex.page = e->page;
        func_001020B0(&tex, fr, 0);
        func_00101D20(&pkt, &tex, texture);
        if (e->life < 16) {
            pkt.c.a = (e->a >> 4) * e->life;
        } else {
            pkt.c.a = e->a;
        }
        if (func_00205440(&a, m, &xy, &d) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        w = func_001018E0(e->width, d);
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = xy.z;
        switch (e->flags & 0x30) {
        case 0x10:
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x20:
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x30:
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        default:
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        }
        func_002075F0(&pkt, target, (u32)d);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b097", func_01E06310_b097);
