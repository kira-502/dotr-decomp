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

static void func_01E00080_b617(Fx_b005_01E00080 *o) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b617", func_01E003A0_b617);

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b051_01E00DF0;

typedef struct {
    u8 r, g, b, a;
    s32 pad4;
    Xyz_b051_01E00DF0 xyz;
} Vtx_b051_01E00DF0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b051_01E00DF0 v[4];
    u8 tail[8];
} Pkt_b051_01E00DF0;

typedef struct {
    u8 b, g, r, a;
} Col_b051_01E00DF0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 seg;
    Col_b051_01E00DF0 c0;
    Col_b051_01E00DF0 c1;
    f32 r;
    f32 k;
    f32 dr;
    s32 ang;
    s32 dang;
    Vec4f pos;
    Vec4f vel;
    Vec4f rot;
} Emit_b051_01E00DF0;

#pragma optimization_level 3

static s32 func_01E02010_b617(void *arg0, s32 ot, s32 n) {
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
    Emit_b051_01E00DF0 *e;
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
    Pkt_b051_01E00DF0 pkt __attribute__((aligned(8)));

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
            rb = e->r * e->k;
        } else {
            rb = e->r;
            ra = e->r * e->k;
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
        ((Pkt_b051_01E00DF0 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b051_01E00DF0 *)(s32)&pkt)->tag = 8;
        ((Pkt_b051_01E00DF0 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b051_01E00DF0 *)(s32)&pkt)->pad = 0;
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

/* shape b285:01E003A0 (ShFx_Blade), 1096 insns, 11 copies (-O3,p): ShFx_Blade variant, -O3 build of b091:01E00410's
   source; the glow quad's alpha as an if/else, divided by segs at each use */

typedef struct Pool_b285_01E003A0 {
    u8 kind;
    u8 pad1[3];
    f32 x, y, z;
} Pool_b285_01E003A0;

typedef struct Spl_b285_01E003A0 {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spl_b285_01E003A0;

typedef struct Rib_b285_01E003A0 {
    u8 kind;
    u8 pad1[3];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    Pool_b285_01E003A0 *pool;
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
} Rib_b285_01E003A0;

typedef struct Uvs_b285_01E003A0 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b285_01E003A0;

typedef struct Tbl_b285_01E003A0 {
    Uvs_b285_01E003A0 v[3];
} Tbl_b285_01E003A0;

typedef struct Xyz_b285_01E003A0 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b285_01E003A0;

typedef struct Vtx_b285_01E003A0 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b285_01E003A0 xyz;
} Vtx_b285_01E003A0;

typedef struct Pk_b285_01E003A0 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b285_01E003A0 v[4];
    u64 pad70[3];
    u64 b0 : 2;
    u64 abe : 2;
    u64 b4 : 20;
    u64 fix : 10;
    u64 ref : 10;
    u64 b44 : 20;
} Pk_b285_01E003A0;

#pragma optimization_level 3

static s32 func_01E02870_b617(Rib_b285_01E003A0 *arg0, s32 id, s32 n) {
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
    Rib_b285_01E003A0 *rib = arg0;
    Pool_b285_01E003A0 *pool = arg0->pool;
    Pool_b285_01E003A0 *pt;
    s32 i __attribute__((aligned(16)));
    s32 j;
    s32 k;
    s32 idx;
    s32 tex0 __attribute__((aligned(16)));
    s32 tex1 __attribute__((aligned(16)));
    s32 tex2 __attribute__((aligned(16)));
    s32 segs __attribute__((aligned(16)));
    s32 cnt __attribute__((aligned(16)));
    f32 a;
    f32 h0;
    f32 h1;
    f32 m[4][4];
    Spl_b285_01E003A0 spl[2];
    Vec4f pos[2];
    Vec4f v[5];
    Vec4f q[2];
    Xyz_b285_01E003A0 s[2];
    f32 depth[4];
    extern Tbl_b285_01E003A0 D_01E06DB0_b617;
    Tbl_b285_01E003A0 tbl = D_01E06DB0_b617;
    extern Uvs_b285_01E003A0 D_01E06E00_b617;
    Uvs_b285_01E003A0 tbl1 = D_01E06E00_b617;
    extern Uvs_b285_01E003A0 D_01E06E20_b617;
    Uvs_b285_01E003A0 tbl2 = D_01E06E20_b617;
    Uvs_b285_01E003A0 uvs;
    Pk_b285_01E003A0 pk;

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
        ((Pk_b285_01E003A0 *)(u32)&pk)->flags = 0x34;
        ((Pk_b285_01E003A0 *)(u32)&pk)->size = 0xC;
        ((Pk_b285_01E003A0 *)(u32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pk_b285_01E003A0 *)(u32)&pk)->pad4 = 0;
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
                if (rib->kind < 8) {
                    a = (f32)rib->kind * (f32)(u32)rib->a3 / 8.0f;
                } else {
                    a = (f32)(u32)rib->a3;
                }
                pk.v[0].a = pk.v[1].a = (u32)(a / (f32)segs * (f32)(segs - k));
                pk.v[2].a = pk.v[3].a = (u32)(a / (f32)segs * (f32)(segs - k - 1));
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

/* shape b132:01E04B00 (ShFx_Afx01), 551 insns, 4 copies: draws n glow entities (0x30 bytes each): projects each one
   on its first frame, then a fan of up to 8 triangles (flag bits of mask) from its screen centre to the corners and
   edge midpoints of a square whose size grows with size and life & 3. The float -> int conversions are (s32)/(u32)
   casts (jal fptosi/fptoui, which block a0/a1 in the warm build). */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b132_01E04B00;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b132_01E04B00;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b132_01E04B00 uv;
    Xyz_b132_01E04B00 xyz;
} Vtx_b132_01E04B00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b132_01E04B00 v[4];
    u8 tail[8];
} Pkt_b132_01E04B00;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3[5];
    u8 size;
    u8 blend;
    u8 mask;
    u8 padB;
    Vec4f pos;
    u8 b2, g2, r2, a2;
    u8 b, g, r, a;
    u8 pad24[4];
    Xyz_b132_01E04B00 xy;
} Afx_b132_01E04B00;

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E03990_b617(Afx_b132_01E04B00 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Afx_b132_01E04B00 *e = arg0;
    f32 mat[16];
    u8 td[0x20];
    Pkt_b132_01E04B00 pk;
    f32 depth;
    u8 bl[4];
    s32 i;
    s32 u;
    s32 v;
    s32 j;
    f32 f;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->life == e->span - 1) {
            func_0020EB40(mat);
            if (func_00205440(&e->pos, mat, &e->xy, &depth) == 0) {
                e->life = 0;
                continue;
            }
            if (func_00101770(&e->xy) == 0) {
                e->life = 0;
                continue;
            }
        }
        u = (s32)(e->xy.x - 27648.0f);
        v = (s32)(e->xy.y - 29184.0f);
        ((Pkt_b132_01E04B00 *)(s32)&pk)->count = 0x33;
        ((Pkt_b132_01E04B00 *)(s32)&pk)->tag = 9;
        ((Pkt_b132_01E04B00 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x21421421;
        ((Pkt_b132_01E04B00 *)(s32)&pk)->pad = 0;
        func_002087A0(&pk, 1);
        pk.v[0].r = pk.v[1].r = e->r;
        pk.v[2].r = e->r2;
        pk.v[0].g = pk.v[1].g = e->g;
        pk.v[2].g = e->g2;
        pk.v[0].b = pk.v[1].b = e->b;
        pk.v[2].b = e->b2;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = 1.0f;
        pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[2].xyz.z = 0xFFFFFF;
        pk.v[0].xyz.f = pk.v[1].xyz.f = pk.v[2].xyz.f = 0;
        td[5] = e->blend;
        func_00101C80(td, bl);
        func_002086D0(&pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        ((Pkt_b132_01E04B00 *)(s32)&pk)->count |= 0x800;
        ((Uv_b132_01E04B00 *)(s32)&pk.v[2].uv)->u = u;
        ((Uv_b132_01E04B00 *)(s32)&pk.v[2].uv)->v = v;
        pk.v[2].xyz.x = e->xy.x;
        pk.v[2].xyz.y = e->xy.y;
        if (e->life < 8) {
            pk.v[0].a = pk.v[1].a = (e->a >> 3) * e->life;
            pk.v[2].a = (e->a2 >> 3) * e->life;
        } else {
            pk.v[0].a = pk.v[1].a = e->a;
            pk.v[2].a = e->a2;
        }
        f = (e->size + (e->life & 3) * 2) << 4;
        for (j = 0; j < 8; j++) {
            if (!(e->mask & (1 << j))) {
                continue;
            }
            switch (j) {
            case 0:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = v;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(27648.0f - f);
                pk.v[0].xyz.y = e->xy.y;
                pk.v[1].xyz.y = (u32)(29184.0f - f);
                break;
            case 1:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = u;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = (u32)(27648.0f - f);
                pk.v[1].xyz.x = e->xy.x;
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f - f);
                break;
            case 2:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = u;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = e->xy.x;
                pk.v[1].xyz.x = (u32)(37888.0f + f);
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f - f);
                break;
            case 3:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = v;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(37888.0f + f);
                pk.v[0].xyz.y = (u32)(29184.0f - f);
                pk.v[1].xyz.y = e->xy.y;
                break;
            case 4:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = v;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(37888.0f + f);
                pk.v[0].xyz.y = e->xy.y;
                pk.v[1].xyz.y = (u32)(36352.0f + f);
                break;
            case 5:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = u;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = (u32)(37888.0f + f);
                pk.v[1].xyz.x = e->xy.x;
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(36352.0f + f);
                break;
            case 6:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = u;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = e->xy.x;
                pk.v[1].xyz.x = (u32)(27648.0f - f);
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(36352.0f + f);
                break;
            case 7:
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b132_01E04B00 *)(s32)&pk.v[1].uv)->v = v;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(27648.0f - f);
                pk.v[0].xyz.y = (u32)(36352.0f + f);
                pk.v[1].xyz.y = e->xy.y;
                break;
            }
            func_002075F0(&pk, ot, 0);
        }
    }
    return 1;
}

/* shape b617:01E04230 (ShFx_Afx06), 569 insns, 1 copy: ShFx_Afx06: n beam entities (0x28 bytes each): projects a
   point offset from the object's joint toward the camera (unless flags & 2, flipped by flags & 1) for the depth and
   the entity for the base; one packet set up on the first live one (colour saved/restored around func_001F7060); then
   two textured quads above and below the base whose width grows with span - life (b172:01E012E0's form) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b617_01E04230;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b617_01E04230;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b617_01E04230 uv;
    Xyz_b617_01E04230 xyz;
} Vtx_b617_01E04230;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b617_01E04230 v[4];
    u8 tail[8];
} Pkt_b617_01E04230;

typedef struct {
    f32 x, y, z;
} V3_b617_01E04230;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    s32 obj;
    V3_b617_01E04230 pos;
    u8 pad18[0x10];
} Afx_b617_01E04230;

static s32 func_01E04230_b617(Afx_b617_01E04230 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern f32 func_001F5860(s32);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    Afx_b617_01E04230 *e = arg0;
    f32 mat[16];
    Vec4f cam;
    Vec4f pos;
    Vec4f d;
    Vec4f p;
    f32 m2[16];
    Xyz_b617_01E04230 xy[2];
    struct {
        Pkt_b617_01E04230 pk;
        s32 a[2];
        s32 b[2];
    } w;
    f32 depth[2];
    u8 c[4];
    s32 save;
    s32 i;
    s32 list;
    s32 v;
    s32 k;
    s32 any;
    f32 f;

    list = func_00207F60();
    any = 0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        cam = *func_001F9AD0(0);
        func_001F53C0(1, e->obj, &pos);
        if (!(e->flags & 2)) {
            d.x = cam.x - pos.x;
            d.y = cam.y - pos.y;
            d.z = cam.z - pos.z;
            func_00101A00(&d, m2);
            d.x = d.z = 0.0f;
            d.y = func_001F5860(e->obj);
            if (e->flags & 1) {
                d.y *= -1.0f;
            }
            func_0020CDD0(&p, m2, &d);
        } else {
            p.x = p.y = p.z = 0.0f;
        }
        p.x += pos.x;
        p.y += pos.y;
        p.z += pos.z;
        if (func_00205440(&p, mat, &xy[0], &depth[0]) == 0) {
            continue;
        }
        if (func_00101770(&xy[0]) == 0) {
            continue;
        }
        if (func_00205440(&e->pos, mat, &xy[1], &depth[1]) == 0) {
            continue;
        }
        if (func_00101770(&xy[1]) == 0) {
            continue;
        }
        v = (s32)(xy[1].y - 29184.0f);
        if (any == 0) {
            ((Pkt_b617_01E04230 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b617_01E04230 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b617_01E04230 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b617_01E04230 *)(s32)&w.pk)->pad = 0;
            w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g =
                w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = 0;
            w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = 0x80;
            w.pk.v[0].q = w.pk.v[1].q = w.pk.v[2].q = w.pk.v[3].q = 1.0f;
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = 0xFFFFFF;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            func_001F6490(e->obj, &save);
            c[0] = 0x80;
            c[1] = 0x80;
            c[2] = 0x80;
            c[3] = 0x80;
            func_001F63E0(e->obj, c);
            func_00208460();
            func_001F7060(e->obj, 0, w.a, w.b);
            func_00208460();
            any = 1;
            func_001F63E0(e->obj, &save);
        }
        w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g =
            w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = 0x80;
        w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = 0x80;
        w.pk.v[0].q = w.pk.v[1].q = w.pk.v[2].q = w.pk.v[3].q = 1.0f;
        w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = xy[0].z;
        func_002086D0(&w.pk, 0x44);
        ((Pkt_b617_01E04230 *)(s32)&w.pk)->count |= 0x800;
        w.pk.v[2].xyz.x = w.pk.v[3].xyz.x = xy[0].x;
        w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = xy[1].y;
        for (k = 0; k < 1; k++) {
            w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = 0x80;
            f = (e->span - e->life) << 5;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[0].uv)->u = 0;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[0].uv)->v = 0;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[1].uv)->v = 0;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[2].uv)->u = 0;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[2].uv)->v = v;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[3].uv)->u = 0x2800;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[3].uv)->v = v;
            w.pk.v[0].xyz.x = w.pk.v[2].xyz.x = (u32)(27648.0f - f);
            w.pk.v[1].xyz.x = w.pk.v[3].xyz.x = (u32)(37888.0f - f);
            w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = 0x7200;
            w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = xy[1].y;
            func_002075F0(&w.pk, 0, (u32)depth[0]);
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[0].uv)->u = 0;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[0].uv)->v = v;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[1].uv)->v = v;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[2].uv)->u = 0;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[2].uv)->v = 0x1C00;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[3].uv)->u = 0x2800;
            ((Uv_b617_01E04230 *)(s32)&w.pk.v[3].uv)->v = 0x1C00;
            w.pk.v[0].xyz.x = w.pk.v[2].xyz.x = (u32)(27648.0f + f);
            w.pk.v[1].xyz.x = w.pk.v[3].xyz.x = (u32)(37888.0f + f);
            w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = xy[1].y;
            w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = 0x8E00;
            func_002075F0(&w.pk, 0, (u32)depth[0]);
        }
    }
    if (any) {
        func_00207FD0(list, ot, (u32)depth[0]);
    }
    return 1;
}

/* shape b617:01E04B20 (ShFx_Core02), 520 insns, 1 copy: update and draw 2-D screen beams (0x40 bytes each): move,
   spin, fade by life, two crossed quads at the screen position */

#define ABS_b617_01E04B20(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b617_01E04B20;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b617_01E04B20;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b617_01E04B20 p;
} Vtx_b617_01E04B20;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b617_01E04B20 v[4];
    u8 tail[0x20];
} Pkt_b617_01E04B20;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b617_01E04B20;

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
    Vec_b617_01E04B20 pos;
    Vec_b617_01E04B20 vel;
} Beam_b617_01E04B20;

static s32 func_01E04B20_b617(Beam_b617_01E04B20 *o, s32 target, s32 count) {
    extern Tex_b617_01E04B20 D_01E06E40_b617;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101EE0(void *, void *, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    s32 i;
    s32 h __attribute__((aligned(16)));
    s32 j;
    u8 k;
    f32 dx;
    f32 dy;
    f32 len;
    f32 t;
    Tex_b617_01E04B20 tex;
    Xyz_b617_01E04B20 q;
    Pkt_b617_01E04B20 pkt __attribute__((aligned(8)));

    tex = D_01E06E40_b617;
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
        ((Pkt_b617_01E04B20 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b617_01E04B20 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b617_01E04B20 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b617_01E04B20 *)(s32)&pkt)->pad = 0;
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
        q.x = (u32)o->pos.x;
        q.y = (u32)o->pos.y;
        q.z = 0xFFFFFE;
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
        pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
        len = o->len;
        if (!(o->flags & 0x40)) {
            if (!(o->flags & 1)) {
                k = o->total - o->life;
                if (k < 8) {
                    len = o->len * (0.125f * k);
                }
            }
            if (o->life < 8) {
                len = o->len * (0.125f * o->life);
            }
        }
        for (j = 0; j < 2; j++) {
            t = 180.0f * j;
            dx = len * func_001A6898(3.1415927f * (o->angle + t) / 180.0f);
            dy = len * func_001A6A88(3.1415927f * (o->angle + t) / 180.0f);
            if (!(ABS_b617_01E04B20(dx) <= ABS_b617_01E04B20(dy))) {
                pkt.v[0].p.x = pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[1].p.x = pkt.v[3].p.x = q.x;
                pkt.v[0].p.y = (u32)(q.y + dy - o->width);
                pkt.v[1].p.y = (u32)(q.y - o->width);
                pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[3].p.y = q.y;
                func_002075F0(&pkt, target, 0);
                pkt.v[0].p.y = (u32)(o->width + (q.y + dy));
                pkt.v[1].p.y = (u32)(q.y + o->width);
                func_002075F0(&pkt, target, 0);
            } else {
                pkt.v[0].p.y = pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[1].p.y = pkt.v[3].p.y = q.y;
                pkt.v[0].p.x = (u32)(q.x + dx - o->width);
                pkt.v[1].p.x = (u32)(q.x - o->width);
                pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[3].p.x = q.x;
                func_002075F0(&pkt, target, 0);
                pkt.v[0].p.x = (u32)(o->width + (q.x + dx));
                pkt.v[1].p.x = (u32)(q.x + o->width);
                func_002075F0(&pkt, target, 0);
            }
        }
    }
    return 1;
}

/* shape b617:01E05340 (ShFx_Flear02), 634 insns, 1 copy: ShFx_Flear02, the screen-space ShFx_Flear01 (b040:01E03440's
   body without the projection): moves each live flare, its centre is the position cast straight to screen x/y at
   depth 0xFFFFFE; fan of segs*4 triangles centre to edge colour, and unless flag 1 one textured edge quad per slice,
   widened across the slice's steeper axis */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b617_01E05340;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b617_01E05340;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b617_01E05340 xyz;
} Vtx1_b617_01E05340;

typedef struct {
    Hdr_b617_01E05340 h;
    Vtx1_b617_01E05340 v[3];
    u8 tail[8];
} Pkt1_b617_01E05340;

typedef struct {
    u64 st;
    Xyz_b617_01E05340 xyz;
} Vtx2_b617_01E05340;

typedef struct {
    Hdr_b617_01E05340 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b617_01E05340 v[4];
    u8 tail[0x20];
} Pkt2_b617_01E05340;

typedef struct {
    f32 x, y, z, w;
} V4_b617_01E05340;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b617_01E05340;

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
    V4_b617_01E05340 pos;
    V4_b617_01E05340 vel;
} Obj_b617_01E05340;

#define ABS_b617_01E05340(v) ((v) >= 0.0f ? (v) : -(v))

static s32 func_01E05340_b617(Obj_b617_01E05340 *obj, s32 tex, s32 n) {
    extern Tex_b617_01E05340 D_01E06E60_b617;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_002086D0(void *, u64);
    extern void func_00101D20(void *, void *, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b617_01E05340 *o;
    s32 k;
    s32 h __attribute__((aligned(16)));
    Tex_b617_01E05340 t;
    Xyz_b617_01E05340 scr;
    Pkt1_b617_01E05340 p1 __attribute__((aligned(8)));
    Pkt2_b617_01E05340 p2 __attribute__((aligned(8)));
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
    t = D_01E06E60_b617;
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
        segs = o->segs;
        segs = segs > 9 ? 9 : segs;
        step = 90.0f / segs;
        scr.x = (u32)o->pos.x;
        scr.y = (u32)o->pos.y;
        scr.z = 0xFFFFFE;
        r = o->radius;
        w = o->width;
        zf = 0.0f;
        ((Hdr_b617_01E05340 *)(s32)&p1)->count = 0x13;
        ((Hdr_b617_01E05340 *)(s32)&p1)->tag = 6;
        ((Hdr_b617_01E05340 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b617_01E05340 *)(s32)&p1)->pad = 0;
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
        ((Hdr_b617_01E05340 *)(s32)&p2)->count = 0x24;
        ((Hdr_b617_01E05340 *)(s32)&p2)->tag = 9;
        ((Hdr_b617_01E05340 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b617_01E05340 *)(s32)&p2)->pad = 0;
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
            if (!(ABS_b617_01E05340(x - px) <= ABS_b617_01E05340(y - py))) {
                p2.v[0].xyz.x = p2.v[2].xyz.x = scr.x + px;
                p2.v[1].xyz.x = p2.v[3].xyz.x = scr.x + x;
                v = scr.y + py;
                p2.v[0].xyz.y = v - w;
                p2.v[2].xyz.y = w + v;
                v = scr.y + y;
                p2.v[1].xyz.y = v - w;
                p2.v[3].xyz.y = w + v;
                func_002075F0(&p2, tex, (u32)zf);
            } else {
                p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
                p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
                v = scr.x + px;
                p2.v[0].xyz.x = w + v;
                p2.v[2].xyz.x = v - w;
                v = scr.x + x;
                p2.v[1].xyz.x = w + v;
                p2.v[3].xyz.x = v - w;
                func_002075F0(&p2, tex, (u32)zf);
            }
        }
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

static s32 func_01E05D30_b617(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b617", func_01E06210_b617);
