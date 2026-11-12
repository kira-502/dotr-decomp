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

static void func_01E00080_b210(Obj_b010_01E00080 *o) {
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

/* shape b010:01E02000 (ShFx_Afx04), 903 insns, 15 copies (-O2,p): the -O2 build of b172:01E012E0 (ShFx_Afx04): draws
   n flare entities with a fan of up to 8 triangles per ring */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b010_01E02000;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b010_01E02000;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b010_01E02000 uv;
    Xyz_b010_01E02000 xyz;
} Vtx_b010_01E02000;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b010_01E02000 v[4];
    u8 tail[8];
} Pkt_b010_01E02000;

typedef struct {
    f32 x, y, z;
} V3_b010_01E02000;

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
    V3_b010_01E02000 pos;
    f32 pad24;
    V3_b010_01E02000 vel;
    f32 pad34;
} Afx_b010_01E02000;

#pragma optimization_level 2

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E00410_b210(Afx_b010_01E02000 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_00101BA0(void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Afx_b010_01E02000 *e = arg0;
    f32 mat[16];
    u8 td[0x20];
    Vec4f cam;
    Vec4f d;
    Vec4f p;
    f32 m2[16];
    Xyz_b010_01E02000 xy[2];
    struct {
        Pkt_b010_01E02000 pk;
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
            ((Pkt_b010_01E02000 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b010_01E02000 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b010_01E02000 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b010_01E02000 *)(s32)&w.pk)->pad = 0;
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
        ((Pkt_b010_01E02000 *)(s32)&w.pk)->count |= 0x800;
        ((Uv_b010_01E02000 *)(s32)&w.pk.v[2].uv)->u = u;
        ((Uv_b010_01E02000 *)(s32)&w.pk.v[2].uv)->v = v;
        ((Uv_b010_01E02000 *)(s32)&w.pk.v[3].uv)->u = u;
        ((Uv_b010_01E02000 *)(s32)&w.pk.v[3].uv)->v = v;
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
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = v;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = xy[1].y;
                    w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 1:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = u;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[1].xyz.x = xy[1].x;
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 2:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = u;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = 0;
                    w.pk.v[0].xyz.x = xy[1].x;
                    w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(29184.0f - fy);
                    break;
                case 3:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = v;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = (u32)(29184.0f - fy);
                    w.pk.v[1].xyz.y = xy[1].y;
                    break;
                case 4:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = v;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = w.pk.v[1].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[0].xyz.y = xy[1].y;
                    w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 5:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = 0x2800;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = u;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = (u32)(37888.0f + fx);
                    w.pk.v[1].xyz.x = xy[1].x;
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 6:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = u;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = 0x1C00;
                    w.pk.v[0].xyz.x = xy[1].x;
                    w.pk.v[1].xyz.x = (u32)(27648.0f - fx);
                    w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = (u32)(36352.0f + fy);
                    break;
                case 7:
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->u = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[0].uv)->v = 0x1C00;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->u = 0;
                    ((Uv_b010_01E02000 *)(s32)&w.pk.v[1].uv)->v = v;
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

static s32 func_01E01230_b210(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E06000_b210;
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
    t = D_01E06000_b210;
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

extern Tex_b532_01E00080 D_01E06020_b210;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E01DB0_b210(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    tex0 = D_01E06020_b210;
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

INCLUDE_ASM("asm/nonmatchings/mod/b210", func_01E02940_b210);

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b044:01E03490, 221 insns, 15 copies: run a list of emitters (0x3C bytes each): a held emitter just moves;
   otherwise it takes a particle (0x40 bytes) from its pool, copies its colours/sizes/velocity into it and
   gives it a random offset (rand() % range - range / 2, in hundredths), either as is or as a +/- segment */

typedef struct Col_b044_01E03490 {
    u8 r, g, b, a;
} Col_b044_01E03490;

typedef struct Vec3_b044_01E03490 {
    f32 x, y, z;
} Vec3_b044_01E03490;

typedef struct Em_b044_01E03490 {
    u8 b0;
    u8 b1[2];
    u8 b3;
    u8 flags;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 *pool;
    u8 count;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 b10;
    u8 b11;
    u8 b12[2];
    s32 range;
    f32 f18;
    f32 f1C;
    Col_b044_01E03490 col;
    f32 pos[3];
    Vec3_b044_01E03490 vel;
} Em_b044_01E03490;

typedef struct Part_b044_01E03490 {
    u8 b0[4];
    u8 b4;
    u8 b5;
    u8 b6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE[2];
    f32 f10;
    f32 f14;
    Col_b044_01E03490 col;
    f32 a[3];
    f32 b[3];
    Vec3_b044_01E03490 vel;
} Part_b044_01E03490;

#pragma optimization_level 2

static s32 func_01E03490_b210(Em_b044_01E03490 *arg0, s32 arg1, s32 n) {
    extern s32 func_00101C30();
    extern void func_00101AD0(void *, u8, s32, s32);
    extern void func_00101BA0();
    extern s32 func_0019A5C8();
    Em_b044_01E03490 *e = arg0;
    Part_b044_01E03490 *q;
    s32 i;
    s32 k;
    f32 rx;
    f32 ry;
    f32 rz;
    Vec4f tmp;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->b0 & e->b3) {
            e->pos[0] += e->vel.x;
            e->pos[1] += e->vel.y;
            e->pos[2] += e->vel.z;
            continue;
        }
        k = func_00101C30(e->pool, 0x40, e->count);
        if (k < 0) {
            continue;
        }
        q = (Part_b044_01E03490 *)(e->pool + k * 0x40);
        func_00101AD0(q, e->b11, 0, 0xFF);
        q->b5 = e->b5;
        q->b4 = e->flags;
        q->b9 = e->b6;
        q->b8 = e->bD;
        q->bB = e->bE;
        q->bC = e->bF;
        q->bD = e->b10;
        q->f10 = e->f18;
        q->f14 = e->f1C;
        q->col = e->col;
        q->vel = e->vel;
        if (e->b5) {
            func_00101BA0(e, &tmp);
            e->pos[0] = tmp.x;
            e->pos[1] = tmp.y;
            e->pos[2] = tmp.z;
        }
        rx = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        ry = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        rz = ((func_0019A5C8() >> 4) % e->range - (e->range >> 1)) / 100.0f;
        if (e->flags & 2) {
            q->a[0] = rx;
            q->a[1] = ry;
            q->a[2] = rz;
        } else {
            q->a[0] = e->pos[0] + rx;
            q->a[1] = e->pos[1] + ry;
            q->a[2] = e->pos[2] + rz;
            q->b[0] = e->pos[0] - rx;
            q->b[1] = e->pos[1] - ry;
            q->b[2] = e->pos[2] - rz;
        }
        if (e->b5 == 0) {
            e->pos[0] += e->vel.x;
            e->pos[1] += e->vel.y;
            e->pos[2] += e->vel.z;
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
typedef struct W_tbl_func_01E03810_b210 {
    Uvs_b024_01E02120 v[4];
} W_tbl_func_01E03810_b210;

static s32 func_01E03810_b210(Rib_b024_01E02120 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E03810_b210 D_01E06070_b210;
    W_tbl_func_01E03810_b210 tbl_w = D_01E06070_b210;
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

static s32 func_01E045C0_b210(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
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

/* shape b210:01E04B10 (b210), 1313 insns, 1 copy (-O2,p): the b210 module main: code >= 0 clears the scene, takes
   both units and three joints; else counts the frame: 2 two flares and the light, 16 two flares and six bolt
   emitters, 56 the afterimage, 68 the fade, the glow, eight ribbons, a flare and five bolt lines from the joint, 180
   a big flare, 190 the fade and six bolt lines through the target, 350 ends; rays every other frame 2..329, frames
   190..326 flares and rays near the target; steps every effect; returns 6 on frames 190..326, 1/2 on frames 180/327
   */

typedef struct {
    u8 count;
    u8 pad1;
    u8 len;
    u8 mask;
    u8 mode;
    u8 b5;
    u8 b6;
    u8 pad7[0xD];
    f32 sx, sy, sz;
    Vec4f pos;
    f32 f70;
    f32 f74;
    u8 pad78[0x18];
    f32 f90;
    u8 pad94[0xC];
} Fx_b210_01E04B10;

typedef struct {
    f32 x, y, z;
} Vec3_b210_01E04B10;

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
    Vec3_b210_01E04B10 p0;
    Vec3_b210_01E04B10 p1;
    Vec3_b210_01E04B10 vel;
} Bolt_b210_01E04B10;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b210_01E04B10 a;
    Vec3_b210_01E04B10 b;
    Vec3_b210_01E04B10 *pts;
} Line_b210_01E04B10;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[3];
    u8 pad18[0x14];
    u8 cam[0x14];
    Fx_b210_01E04B10 fx;
    s16 wv[2];
    Afx_b010_01E02000 afx;
    Ray_b532_01E00080 ray[0x3C];
    Obj_b035_01E00410 flear[0x18];
    Bolt_b210_01E04B10 bolt[0x64];
    Em_b044_01E03490 em[8];
    Rib_b024_01E02120 rib[0x14];
    Obj_b010_01E05740 fade;
    u8 pad4221[3];
    u8 tbl[0x100];
    u8 pad4324[0xC];
} Scene_b210_01E04B10;

#pragma optimization_level 2

static s32 func_01E04B10_b210(Scene_b210_01E04B10 *g, s32 code) {
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
    extern void func_001031C0(void *, u16);
    extern void func_00102A50(void *);
    extern s32 func_01E045C0_b210();
    extern s32 func_01E02940_b210();
    s32 ot;
    Vec4f v;
    Vec4f p;
    Vec4f q[2];
    Line_b210_01E04B10 line;
    Vec3_b210_01E04B10 pts[17];
    s32 i;
    s32 k;
    s32 j;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x4330);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 0x23, 1);
        g->m[1] = func_001F5560(g->unitA, 0x2A, 0);
        g->m[2] = func_001F5560(g->unitA, 1, 0);
        g->wv[0] = 2;
        g->wv[1] = 0x158;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 2:
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->flear[i], 0x12, 0, 0xFF);
            g->flear[i].pad5[0] = 1;
            g->flear[i].pad5[1] = g->m[i];
            g->flear[i].flags = 0x80;
            g->flear[i].segs = 9;
            g->flear[i].radius = 50.0f;
            g->flear[i].grow = 10.0f;
            g->flear[i].ir = g->flear[i].ig = g->flear[i].ib = 0xC0;
            g->flear[i].r = 0x10;
            g->flear[i].g = 0x20;
            g->flear[i].b = 0x80;
            g->flear[i].alpha = 0xD0;
            g->flear[i].org.x = g->flear[i].org.y = g->flear[i].org.z = 0.0f;
            g->flear[i].width = 8.0f;
        }
        func_00101AD0(&g->fx, 0xFA, 0, 0xFF);
        g->fx.b5 = 1;
        g->fx.b6 = g->m[0];
        g->fx.mode = 1;
        g->fx.sx = 1.2f;
        g->fx.sy = 1.2f;
        g->fx.sz = 1.8f;
        g->fx.f70 = 0.0f;
        g->fx.f74 = 40.0f;
        g->fx.f90 = 2.0f;
        break;
    case 0x10:
        for (i = 0; i < 2; i++) {
            k = func_00101C30(g->flear, 0x4C, 0x18);
            if (k < 0) {
                continue;
            }
            func_00101AD0(&g->flear[k], 0xFF, 0, 0xFF);
            g->flear[k].pad5[0] = 1;
            g->flear[k].pad5[1] = g->m[i];
            g->flear[k].flags = 5;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xC0;
            g->flear[k].radius = 150.0f;
            g->flear[k].grow = 0.0f;
        }
        for (k = 0; k < 6; k++) {
            func_00101AD0(&g->em[k], 0x26, 8, 0);
            g->em[k].b5 = 1;
            g->em[k].flags = 2;
            g->em[k].pool = (u8 *)g->bolt;
            g->em[k].count = 100;
            g->em[k].bD = 8;
            g->em[k].bE = 1;
            g->em[k].bF = 0;
            g->em[k].b10 = 5;
            g->em[k].b11 = 0xC;
            g->em[k].f18 = 1.0f;
            g->em[k].f1C = 0.4f;
            g->em[k].col.r = 0x80;
            g->em[k].col.g = 0x80;
            g->em[k].col.b = 0x80;
            g->em[k].col.a = 0x20;
            g->em[k].vel.x = g->em[k].vel.y = g->em[k].vel.z = 0.0f;
            switch (k) {
            case 0:
            case 1:
                g->em[k].b6 = g->m[k];
                g->em[k].range = 700;
                break;
            default:
                g->em[k].b6 = g->m[2];
                g->em[k].range = 1300;
                break;
            }
        }
        break;
    case 0x38:
        func_00101AD0(&g->afx, 0x1C, 0, 0xFF);
        g->afx.flags = 0;
        g->afx.blend = 2;
        g->afx.mask = 0xFF;
        g->afx.scale = 8;
        g->afx.len = 0x18;
        g->afx.obj = g->unitA;
        g->afx.b = 0x80;
        g->afx.g = 0x80;
        g->afx.r = 0x80;
        g->afx.a = 0;
        g->afx.b2 = 0x90;
        g->afx.g2 = 0x90;
        g->afx.r2 = 0x90;
        g->afx.a2 = 0x40;
        g->afx.pad5[0] = 1;
        g->afx.pad5[1] = g->m[2];
        break;
    case 0x44:
        func_00101AD0(&g->fade, 0x10, 0, 0xFF);
        g->fade.flags = 1;
        func_00101AD0(&g->fx, 0xD0, 0, 0xFF);
        g->fx.b5 = 0;
        g->fx.mode = 8;
        g->fx.sx = 1.0f;
        g->fx.sy = 1.4f;
        g->fx.sz = 2.0f;
        g->fx.f70 = 0.0f;
        g->fx.f74 = 160.0f;
        g->fx.pos = v;
        g->fx.f90 = 8.0f;
        g->fx.pos.z = 0.0f;
        for (k = 0; k < 8; k++) {
            func_00101AD0(&g->rib[k], 0x20, (u8)k, 0xFF);
            g->rib[k].age -= 4;
            g->rib[k].flags = 5;
            g->rib[k].b5[0] = 0;
            g->rib[k].count = 0x1E;
            g->rib[k].k = k;
            g->rib[k].idx = 0;
            g->rib[k].b5c = 2;
            g->rib[k].frame = func_0019A5C8() >> 4 & 3;
            g->rib[k].width = 50.0f;
            g->rib[k].grow = -0.6f;
            g->rib[k].pts = g->tbl;
            g->rib[k].scale = 1.0f;
            g->rib[k].b = g->rib[k].g = g->rib[k].r = g->rib[k].a = 0x80;
            func_001F5620(g->unitA, g->m[2], g->rib[k].pos);
        }
        func_001F5620(g->unitA, g->m[2], &q[0]);
        k = func_00101C30(g->flear, 0x4C, 0x18);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x18, 0, 0xFF);
            g->flear[k].pad5[0] = 0;
            g->flear[k].flags = 0x80;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xC0;
            g->flear[k].radius = 100.0f;
            g->flear[k].grow = 150.0f;
            g->flear[k].width = 60.0f;
            g->flear[k].pos = *(V4_b035_01E00410 *)&q[0];
        }
        for (j = 0; j < 5; j++) {
            q[1] = q[0];
            q[1].y += 80.0f;
            switch (j) {
            case 0:
                q[1].x -= 50.0f;
                break;
            case 1:
                q[1].x += 50.0f;
                break;
            case 2:
                q[1].z -= 50.0f;
                break;
            case 3:
                q[1].z += 50.0f;
                break;
            }
            line.n = 5;
            line.jitter = 0.2f;
            line.pts = pts;
            line.a.x = q[0].x;
            line.a.y = q[0].y;
            line.a.z = q[0].z;
            line.b.x = q[1].x;
            line.b.y = q[1].y;
            line.b.z = q[1].z;
            func_00102A50(&line);
            for (i = 0; i < 5; i++) {
                k = func_00101C30(g->bolt, 0x40, 0x64);
                if (k < 0) {
                    break;
                }
                func_00101AD0(&g->bolt[k], 0x80, j & 1, 0xFF);
                g->bolt[k].mode = 0;
                g->bolt[k].flags = 0;
                g->bolt[k].p0 = pts[i];
                g->bolt[k].p1 = pts[i + 1];
                g->bolt[k].nseg = 8;
                g->bolt[k].jitter = 0.8f;
                g->bolt[k].grow = 0.3f;
                g->bolt[k].texid = 1;
                g->bolt[k].wdiv = 3;
                g->bolt[k].texsel = 0;
                g->bolt[k].b = 0x80;
                g->bolt[k].g = 0x80;
                g->bolt[k].r = 0x80;
                g->bolt[k].a = 0x20;
            }
        }
        break;
    case 0xB4:
        q[0] = v;
        q[0].y += 45.0f;
        k = func_00101C30(g->flear, 0x4C, 0x18);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x18, 0, 0xFF);
            g->flear[k].pad5[0] = 0;
            g->flear[k].flags = 0x81;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xC0;
            g->flear[k].radius = 1600.0f;
            g->flear[k].grow = 100.0f;
            g->flear[k].width = 60.0f;
            g->flear[k].pos = *(V4_b035_01E00410 *)&q[0];
        }
        break;
    case 0xBE:
        func_00101AD0(&g->fade, 0xC, 0, 0xFF);
        g->fade.flags = 1;
        for (j = 0; j < 6; j++) {
            q[1] = v;
            q[0] = q[1];
            q[0].y += 60.0f;
            q[1].y -= 60.0f;
            switch (j) {
            case 0:
                q[0].x -= 18.0f;
                q[1].x -= 18.0f;
                break;
            case 1:
                q[0].x += 18.0f;
                q[1].x += 18.0f;
                break;
            case 2:
                q[0].z -= 18.0f;
                q[1].z -= 18.0f;
                break;
            case 3:
                q[0].z += 18.0f;
                q[1].z += 18.0f;
                break;
            case 4:
                q[0].x += 10.0f;
                q[1].x += 10.0f;
                q[0].z += 10.0f;
                q[1].z += 10.0f;
                break;
            case 5:
                q[0].x -= 10.0f;
                q[1].x -= 10.0f;
                q[0].z -= 10.0f;
                q[1].z -= 10.0f;
                break;
            }
            line.n = 5;
            line.jitter = 0.4f;
            line.pts = pts;
            line.a.x = q[0].x;
            line.a.y = q[0].y;
            line.a.z = q[0].z;
            line.b.x = q[1].x;
            line.b.y = q[1].y;
            line.b.z = q[1].z;
            func_00102A50(&line);
            for (i = 0; i < 5; i++) {
                k = func_00101C30(g->bolt, 0x40, 0x64);
                if (k < 0) {
                    break;
                }
                func_00101AD0(&g->bolt[k], 0x8C, j & 1, 0xFF);
                g->bolt[k].mode = 0;
                g->bolt[k].flags = 0;
                g->bolt[k].p0 = pts[i];
                g->bolt[k].p1 = pts[i + 1];
                g->bolt[k].nseg = 6;
                g->bolt[k].jitter = 1.0f;
                g->bolt[k].grow = 0.3f;
                g->bolt[k].texid = 1;
                g->bolt[k].wdiv = 4;
                g->bolt[k].texsel = 0;
                g->bolt[k].b = 0x80;
                g->bolt[k].g = 0x80;
                g->bolt[k].r = 0x80;
                g->bolt[k].a = 0x20;
            }
        }
        break;
    case 0x15E:
        return 8;
    }
    if (g->t >= 2 && g->t < 0x14A && !(g->t & 1)) {
        for (j = 0; j < 2; j++) {
            k = func_00101C30(g->ray, 0x68, 0x3C);
            if (k < 0) {
                continue;
            }
            func_00101AD0(&g->ray[k], 0x10, 0, 0xFF);
            g->ray[k].flags = 5;
            if (g->t < 0x44) {
                g->ray[k].size = 0.5f;
                g->ray[k].width = 10.0f;
                g->ray[k].segments = 8;
                g->ray[k].pad05[1] = g->m[j];
            } else {
                g->ray[k].size = 3.5f;
                g->ray[k].width = 30.0f;
                g->ray[k].segments = 0x12;
                g->ray[k].pad05[1] = g->m[2];
            }
            g->ray[k].pad05[0] = 1;
            g->ray[k].texkind = 0;
            g->ray[k].texpage = 2;
            g->ray[k].texmode = 3;
            g->ray[k].index = func_0019A5C8() >> 4;
            g->ray[k].table = g->tbl;
            g->ray[k].radius = 1.0f;
            g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
            g->ray[k].a0 = 0x10;
            g->ray[k].a1 = 0x40;
            g->ray[k].spin[0] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].spin[1] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].spin[2] = func_0019A5C8() >> 4 & 0x7F;
        }
    }
    if (g->t >= 0xBE && g->t < 0x147) {
        for (i = 0; i < 4; i++) {
            p.x = v.x + (f32)((func_0019A5C8() >> 4) % 2800 - 1400) / 100.0f;
            p.y = v.y + (f32)((func_0019A5C8() >> 4) % 2800 - 1400) / 100.0f;
            p.z = v.z + (f32)((func_0019A5C8() >> 4) % 2800 - 1400) / 100.0f;
            k = func_00101C30(g->flear, 0x4C, 0x18);
            if (k >= 0) {
                func_00101AD0(&g->flear[k], 0xC, 0, 0xFF);
                g->flear[k].pad5[0] = 0;
                g->flear[k].flags = 1;
                g->flear[k].segs = 9;
                g->flear[k].ir = g->flear[k].ig = g->flear[k].ib = g->flear[k].alpha = 0xC0;
                g->flear[k].r = 0x60;
                g->flear[k].g = 0x10;
                g->flear[k].b = 0x40;
                g->flear[k].grow = 0.0f;
                g->flear[k].radius = 300.0f;
                g->flear[k].grow = 0.0f;
                g->flear[k].pos = *(V4_b035_01E00410 *)&p;
            }
            k = func_00101C30(g->ray, 0x68, 0x3C);
            if (k >= 0) {
                g->ray[k].flags = 5;
                func_00101AD0(&g->ray[k], 8, 0, 0xFF);
                g->ray[k].size = 5.0f;
                g->ray[k].width = 40.0f;
                g->ray[k].a1 = 0xA0;
                g->ray[k].a0 = 0;
                g->ray[k].pad05[0] = 0;
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 3;
                g->ray[k].segments = 0x28;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 1.0f;
                g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
                g->ray[k].pos = *(Vec_b532_01E00080 *)&p;
            }
        }
    }
    func_01E00080_b210((Obj_b010_01E00080 *)&g->fx);
    func_001031C0(g->wv, g->t);
    func_01E045C0_b210(&g->fade, ot);
    func_01E00410_b210(&g->afx, ot, 1);
    func_01E01230_b210(g->flear, ot, 0x18);
    func_01E01DB0_b210(g->ray, ot, 0x3C);
    func_01E03490_b210(g->em, ot, 8);
    func_01E02940_b210(g->bolt, ot, 0x64);
    func_01E03810_b210(g->rib, ot, 0x14);
    if (g->t >= 0xBE && g->t < 0x147) {
        return 6;
    }
    switch (g->t) {
    case 0xB4:
        return 1;
    case 0x147:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
