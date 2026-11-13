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

static void func_01E00080_b123(Obj_b002_01E00080 *arg0) {
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

static s32 func_01E00440_b123(Fx_b097_01E059B0 *obj, s32 target, s32 n) {
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

/* shape b123:01E00DA0 (ShFx_Afx03), 508 insns, 1 copy (-O1,p): b106:01E042B0 built at -O1, the flare
   sprites drawn as screen quads stepping out from the projected point */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b123_01E00DA0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b123_01E00DA0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b123_01E00DA0 uv;
    Xyz_b123_01E00DA0 xyz;
} Vtx_b123_01E00DA0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b123_01E00DA0 v[4];
    u8 tail[8];
} Pkt_b123_01E00DA0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 len;
    u8 blend;
    u8 dx;
    u8 dy;
    s32 obj;
    u8 pad10[3];
    u8 alpha;
    u8 pad14[0x10];
} Flare_b123_01E00DA0;

#pragma optimization_level 1

static s32 func_01E00DA0_b123(Flare_b123_01E00DA0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_001F53C0(s32, s32, void *);
    extern f32 func_001F5860(s32);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Flare_b123_01E00DA0 *e = arg0;
    f32 mat[16];
    Vec4f pos;
    Vec4f d;
    Vec4f p;
    Vec4f cam;
    f32 m2[16];
    u8 td[0x20];
    struct {
        Pkt_b123_01E00DA0 pk;
        s32 a[2];
        s32 b[2];
    } w;
    Xyz_b123_01E00DA0 xy;
    f32 depth;
    u8 bl[4];
    s32 i;
    s32 list;
    s32 any;
    s32 j;
    s32 k;
    s32 cnt;
    s32 x;
    s32 y;
    s32 m;

    list = func_00207F60();
    any = 0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (any == 0) {
            ((Pkt_b123_01E00DA0 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b123_01E00DA0 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b123_01E00DA0 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b123_01E00DA0 *)(s32)&w.pk)->pad = 0;
            w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g =
                w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a =
                    w.pk.v[3].a = 0x80;
            w.pk.v[0].q = w.pk.v[1].q = w.pk.v[2].q = w.pk.v[3].q = 1.0f;
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = 0xFFFFFF;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            func_00208460();
            func_001F7060(e->obj, 0, w.a, w.b);
            func_00208460();
            any = 1;
            ((Pkt_b123_01E00DA0 *)(s32)&w.pk)->count |= 0x800;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[0].uv)->u = 0;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[0].uv)->v = 0;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[1].uv)->v = 0;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[2].uv)->u = 0;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[2].uv)->v = 0x1C00;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[3].uv)->u = 0x2800;
            ((Uv_b123_01E00DA0 *)(s32)&w.pk.v[3].uv)->v = 0x1C00;
        }
        func_0020EB40(mat);
        cam = *func_001F9AD0(0);
        func_001F53C0(1, e->obj, &pos);
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
        p.x += pos.x;
        p.y += pos.y;
        p.z += pos.z;
        if (func_00205440(&p, mat, &xy, &depth) != 0 && func_00101770(&xy) != 0) {
            w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = xy.z;
            w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
            td[5] = e->blend;
            func_00101C80(td, bl);
            func_002086D0(&w.pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
            w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = e->alpha;
            cnt = e->len >> 1;
            m = e->span - e->life + 1;
            if (m < cnt) {
                cnt = m;
            }
            if (e->life < cnt) {
                cnt = e->life;
            }
            for (k = 0; k < 2; k++) {
                for (j = 0; j < cnt; j++) {
                    if (k) {
                        x = e->dx * (j + 1);
                        y = e->dy * (j + 1);
                    } else {
                        x = -e->dx * (j + 1);
                        y = -e->dy * (j + 1);
                    }
                    w.pk.v[0].xyz.x = w.pk.v[2].xyz.x = (u32)((x << 4) + 27648.0f);
                    w.pk.v[1].xyz.x = w.pk.v[3].xyz.x = (u32)(37888.0f + (x << 4));
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)((y << 4) + 29184.0f);
                    w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = (u32)(36352.0f + (y << 4));
                    func_002075F0(&w.pk, 0, (u32)depth);
                }
            }
        }
    }
    if (any) {
        func_00207FD0(list, ot, 0);
    }
    return 1;
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

static s32 func_01E01590_b123(Rib_b097_01E00440 *arg0, s32 id, s32 n) {
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
    extern Tbl_b097_01E00440 D_01E07000_b123;
    Tbl_b097_01E00440 tbl = D_01E07000_b123;
    extern Uvs_b097_01E00440 D_01E07050_b123;
    Uvs_b097_01E00440 tbl1 = D_01E07050_b123;
    extern Uvs_b097_01E00440 D_01E07070_b123;
    Uvs_b097_01E00440 tbl2 = D_01E07070_b123;
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

static s32 func_01E029D0_b123(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E07090_b123;
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
    t = D_01E07090_b123;
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

/* shape b603:01E01160 (ShFx_Core01), 691 insns, 9 copies (-O1,p): update and draw spinning 2-D beams (0x50 bytes
   each): move, project, and draw each as two quads per half-turn, alpha and length fading in and out; the source of
   shape b213:01E00F90, built here at -O1 */

#define ABS_b603_01E01160(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b603_01E01160;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b603_01E01160;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b603_01E01160 p;
} Vtx_b603_01E01160;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b603_01E01160 v[4];
    u8 tail[0x20];
} Pkt_b603_01E01160;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b603_01E01160;

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
    Vec_b603_01E01160 pos;
    Vec_b603_01E01160 vel;
    Vec_b603_01E01160 point;
} Beam_b603_01E01160;

#pragma optimization_level 1

static s32 func_01E036F0_b123(void *p, s32 target, s32 count) {
    extern Tex_b603_01E01160 D_01E070B0_b123;
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
    Beam_b603_01E01160 *o = p;
    s32 i;
    s32 j;
    s32 h __attribute__((aligned(16)));
    u8 k;
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
    Vec_b603_01E01160 pt;
    Tex_b603_01E01160 tex;
    Xyz_b603_01E01160 q;
    Pkt_b603_01E01160 pkt __attribute__((aligned(8)));
    f32 dep;

    tex = D_01E070B0_b123;
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
        ((Pkt_b603_01E01160 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b603_01E01160 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b603_01E01160 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b603_01E01160 *)(s32)&pkt)->pad = 0;
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
            ady = ABS_b603_01E01160(dy);
            if (!(ABS_b603_01E01160(dx) <= ady)) {
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

extern Tex_b011_01E04380 D_01E070D0_b123;

#pragma optimization_level 1

static s32 func_01E041C0_b123(Ray_b011_01E04380 *obj, s32 target, s32 count) {
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
    tex0 = D_01E070D0_b123;
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
typedef struct W_tbl_func_01E04EF0_b123 {
    Uvs_b097_01E025A0 v[2];
} W_tbl_func_01E04EF0_b123;

static s32 func_01E04EF0_b123(Rib_b097_01E025A0 *arg0, s32 ot, s32 n) {
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
    extern W_tbl_func_01E04EF0_b123 D_01E070F0_b123;
    W_tbl_func_01E04EF0_b123 tbl_w = D_01E070F0_b123;
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

static s32 func_01E05BB0_b123(Spawn_b097_01E03260 *arg0, s32 unused, s32 n) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b123", func_01E06390_b123);
