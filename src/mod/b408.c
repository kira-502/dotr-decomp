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

static void func_01E00080_b408(Fx_b005_01E00080 *o) {
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

static s32 func_01E003A0_b408(Afx_b172_01E012E0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

static s32 func_01E011B0_b408(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E07480_b408;
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
    t = D_01E07480_b408;
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

static s32 func_01E01C00_b408(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern Uvs_b029_01E02B80 D_01E074A0_b408;
    Uvs_b029_01E02B80 tbl = D_01E074A0_b408;
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

typedef struct W_tmpl_func_01E026E0_b408 {
    Tex_b070_01E03C10 v[2];
} W_tmpl_func_01E026E0_b408;

static s32 func_01E026E0_b408(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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
    extern W_tmpl_func_01E026E0_b408 D_01E074C0_b408;
    W_tmpl_func_01E026E0_b408 tmpl_w = D_01E074C0_b408;
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

/* shape b238:01E02360, 205 insns, 8 copies: b044:01E03490 (-O2,p) built at -O4,p: run a list of emitters (0x3C bytes each): a held emitter just moves;
   otherwise it takes a particle (0x40 bytes) from its pool, copies its colours/sizes/velocity into it and
   gives it a random offset (rand() % range - range / 2, in hundredths), either as is or as a +/- segment */

typedef struct Col_b238_01E02360 {
    u8 r, g, b, a;
} Col_b238_01E02360;

typedef struct Vec3_b238_01E02360 {
    f32 x, y, z;
} Vec3_b238_01E02360;

typedef struct Em_b238_01E02360 {
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
    Col_b238_01E02360 col;
    f32 pos[3];
    Vec3_b238_01E02360 vel;
} Em_b238_01E02360;

typedef struct Part_b238_01E02360 {
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
    Col_b238_01E02360 col;
    f32 a[3];
    f32 b[3];
    Vec3_b238_01E02360 vel;
} Part_b238_01E02360;

static s32 func_01E03170_b408(Em_b238_01E02360 *arg0, s32 arg1, s32 n) {
    extern s32 func_00101C30();
    extern void func_00101AD0(void *, u8, s32, s32);
    extern void func_00101BA0();
    extern s32 func_0019A5C8();
    Em_b238_01E02360 *e = arg0;
    Part_b238_01E02360 *q;
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
        q = (Part_b238_01E02360 *)(e->pool + k * 0x40);
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
static s32 func_01E034B0_b408(Rib_b285_01E014C0 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern W_tbl_func_01E02BC0_b536 D_01E074F0_b408;
    W_tbl_func_01E02BC0_b536 tbl_w = D_01E074F0_b408;
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

static s32 func_01E04110_b408(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

/* shape b601:01E003A0 (ShFx_Gus2), 579 insns, 30 copies (-O3,p): moves and draws n spark emitters (0x44 bytes each):
   velocity, gravity, floor bounce, size growth, optional follow; each live one is one camera-facing square of its
   size around its projected point, with one of four texture corner orders picked by flags & 0x30.; the source of
   shape b061:01E01170, built here at -O3 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b601_01E003A0;

typedef struct {
    u64 uv;
    Xyz_b601_01E003A0 xyz;
} Vtx_b601_01E003A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b601_01E003A0 v[4];
    u8 tail[0x20];
} Pkt_b601_01E003A0;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b601_01E003A0;

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
} Spark_b601_01E003A0;

#pragma optimization_level 3

/* ot aligned: its spill slot, needed for the match */

static s32 func_01E045F0_b408(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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
    Tex_b601_01E003A0 td;
    Pkt_b601_01E003A0 pkt __attribute__((aligned(8)));
    Xyz_b601_01E003A0 scr;
    f32 depth;
    Spark_b601_01E003A0 *e;
    s32 i;
    s32 tex;
    s32 mode;
    s32 d;
    f32 s;
    f32 zf;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Spark_b601_01E003A0 *)((u8 *)e + 0x44);
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
        ((Pkt_b601_01E003A0 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b601_01E003A0 *)(s32)&pkt)->tag = 9;
        ((Pkt_b601_01E003A0 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b601_01E003A0 *)(s32)&pkt)->pad = 0;
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

/* shape b062:01E020A0 (ShFx_LCyl), 601 insns, 6 copies: draws n cylinder emitters (0x2C bytes each): a ring of up to
   36 points (radius r grown by dr, in the xy, zy or xz plane by mode) swept along each segment of e->pts as textured
   quads, with optional backface cull, scrolling s/t, blink and end fades */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b062_01E020A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b062_01E020A0 xyz;
} Vtx_b062_01E020A0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b062_01E020A0 v[4];
    u8 tail[0x20];
} Pkt_b062_01E020A0;

typedef struct {
    f32 x, y, z;
} V3_b062_01E020A0;

typedef struct {
    u8 b, g, r, a;
} Col_b062_01E020A0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 cnt;
    u8 tex;
    u8 padA;
    u8 mode;
    V3_b062_01E020A0 *pts;
    f32 usize;
    f32 pad14;
    f32 uscale;
    f32 vscale;
    f32 r;
    f32 dr;
    Col_b062_01E020A0 c;
} Cyl_b062_01E020A0;

/* the ?: clamp of nseg and cnt reused for the life span (before it is the count) give the original's spill slots */

static s32 func_01E04F00_b408(Cyl_b062_01E020A0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_00101940(void *, void *);
    extern f32 func_0020D0E0(void *);
    extern void func_0020EB40(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208CB0(void *, s32);
    extern void func_002086D0(void *, s32);
    extern void func_00208700(void *, void *, s32);
    extern void func_002075F0(s32, s32, s32);
    f32 mat[16];
    Vec4f ring[37];
    f32 pt[4];
    f32 dir[4];
    f32 dep[4];
    s32 rot[4];
    Pkt_b062_01E020A0 pkt;
    Cyl_b062_01E020A0 *e;
    s32 i;
    s32 tex __attribute__((aligned(16)));
    s32 k;
    s32 cnt;
    s32 nseg;
    s32 j;
    s32 on0;
    s32 on1;
    s32 on2;
    s32 on3;
    f32 a;
    f32 cross;
    f32 step;
    f32 ustep;
    f32 v0;
    f32 u0;
    f32 z;
    u8 al;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->tex);
        e->r += e->dr;
        nseg = e->seg;
        nseg = nseg > 36 ? 36 : nseg;
        step = 360.0f / nseg;
        for (j = 0; j < nseg; j++) {
            switch (e->mode & 0x18) {
            case 8:
                a = 3.1415927f * (step * j) / 180.0f;
                ring[j].x = e->r * func_001A6898(a);
                ring[j].y = e->r * func_001A6A88(a);
                ring[j].z = 0.0f;
                break;
            case 0x10:
                a = 3.1415927f * (step * j) / 180.0f;
                ring[j].z = e->r * func_001A6898(a);
                ring[j].y = e->r * func_001A6A88(a);
                ring[j].x = 0.0f;
                break;
            default:
                a = 3.1415927f * (step * j) / 180.0f;
                ring[j].x = e->r * func_001A6898(a);
                ring[j].z = e->r * func_001A6A88(a);
                ring[j].y = 0.0f;
                break;
            }
        }
        ring[nseg] = ring[0];
        ustep = e->usize / nseg;
        cnt = e->max - e->life;
        u0 = e->uscale * cnt;
        if (!(u0 <= 1.0f)) {
            u0 -= (s32)u0;
        }
        v0 = e->vscale * cnt;
        if (!(v0 <= 1.0f)) {
            v0 -= (s32)v0;
        }
        ((Pkt_b062_01E020A0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b062_01E020A0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b062_01E020A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b062_01E020A0 *)(s32)&pkt)->pad = 0;
        cnt = e->cnt;
        if ((e->mode & 0x20) && e->max - e->life < cnt) {
            cnt = e->max - e->life;
        }
        for (k = 0; k < cnt; k++) {
            dir[0] = e->pts[k + 1].x - e->pts[k].x;
            dir[1] = e->pts[k + 1].y - e->pts[k].y;
            dir[2] = e->pts[k + 1].z - e->pts[k].z;
            func_00101940(dir, rot);
            func_0020D0E0(dir);
            func_0020EB40(mat);
            for (j = 0; j < nseg; j++) {
                pt[0] = e->pts[k].x + ring[j].x;
                pt[1] = e->pts[k].y + ring[j].y;
                pt[2] = e->pts[k].z + ring[j].z;
                on0 = func_00205440(pt, mat, &pkt.v[0].xyz, &dep[0]);
                pt[0] = e->pts[k].x + ring[j + 1].x;
                pt[1] = e->pts[k].y + ring[j + 1].y;
                pt[2] = e->pts[k].z + ring[j + 1].z;
                on1 = func_00205440(pt, mat, &pkt.v[1].xyz, &dep[1]);
                pt[0] = e->pts[k + 1].x + ring[j].x;
                pt[1] = e->pts[k + 1].y + ring[j].y;
                pt[2] = e->pts[k + 1].z + ring[j].z;
                on2 = func_00205440(pt, mat, &pkt.v[2].xyz, &dep[2]);
                pt[0] = e->pts[k + 1].x + ring[j + 1].x;
                pt[1] = e->pts[k + 1].y + ring[j + 1].y;
                pt[2] = e->pts[k + 1].z + ring[j + 1].z;
                on3 = func_00205440(pt, mat, &pkt.v[3].xyz, &dep[3]);
                if (on0 == 0 || on1 == 0 || on2 == 0 || on3 == 0) {
                    continue;
                }
                if (e->mode & 1) {
                    cross = (pkt.v[0].xyz.x - pkt.v[2].xyz.x) * (pkt.v[3].xyz.y - pkt.v[2].xyz.y) -
                            (pkt.v[3].xyz.x - pkt.v[2].xyz.x) * (pkt.v[0].xyz.y - pkt.v[2].xyz.y);
                    if (!(cross <= 0.0f)) {
                        break;
                    }
                }
                pkt.v[0].q = 1.0f / dep[0];
                pkt.v[1].q = 1.0f / dep[1];
                pkt.v[2].q = 1.0f / dep[2];
                pkt.v[3].q = 1.0f / dep[3];
                pkt.v[0].s = (u0 + ustep * j) / dep[0];
                pkt.v[0].t = (1.0f + v0) / dep[0];
                pkt.v[1].s = (u0 + ustep * (j + 1)) / dep[1];
                pkt.v[1].t = (1.0f + v0) / dep[1];
                pkt.v[2].s = (u0 + ustep * j) / dep[2];
                pkt.v[2].t = v0 / dep[2];
                pkt.v[3].s = (u0 + ustep * (j + 1)) / dep[3];
                pkt.v[3].t = v0 / dep[3];
                func_00208CB0(&pkt, 0);
                func_002086D0(&pkt, 0x48);
                if (!(e->flags & 0x40) && e->life < 8) {
                    al = (e->c.a >> 3) * e->life;
                } else {
                    al = e->c.a;
                }
                if ((e->mode & 2) && (e->life & 1)) {
                    pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = 0;
                } else {
                    pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = al;
                }
                if (e->mode & 0x40) {
                    pkt.v[2].a = pkt.v[3].a = 0;
                }
                pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->c.r;
                pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->c.g;
                pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->c.b;
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                func_00208700(&pkt, (void *)tex, 1);
                if (e->flags & 0x80) {
                    z = 0.0f;
                } else {
                    z = (u32)((dep[0] + dep[1] + dep[2] + dep[3]) / 4.0f);
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}

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
static s32 func_01E05870_b408(Afx_b132_01E04B00 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

/* shape b408:01E06110 (b408), 1235 insns, 1 copy: b408 scene manager (b370:01E062B0's -O4 form, written from the
   asm): setup clears the scene, takes both units and three joints; frame 2 arms a flear, the emitter and two bolt
   emitters, 50 the flare, 60 the fade, two flears, eight ribbon trails, 24 bolts, two cylinders, a flear at the
   target and four bolt emitters, 200 eight ribbons at the target, 232 ends; frames 60..200 lay a 24-point path from
   the joint to the target and four arcs of six bolts along it (func_00102CB0); ribbons on odd frames, 10 sparks a
   frame on 2..37; steps every effect; returns 6 on 60..196, 1/2 on 50/197 */

typedef struct Cam_b408_01E06110 {
    s32 a;
    s32 dir;
    u8 pad8[0xC];
} Cam_b408_01E06110;

typedef struct Emit_b408_01E06110 {
    u8 pad0[4];
    u8 kind;
    u8 on;
    u8 sel;
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
} Emit_b408_01E06110;

typedef struct Wv_b408_01E06110 {
    s16 a;
    s16 b;
} Wv_b408_01E06110;

typedef struct Gus_b408_01E06110 {
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
} Gus_b408_01E06110;

typedef struct Afx_b408_01E06110 {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 on;
    u8 sel;
    u8 pad7;
    u8 scale;
    u8 blend;
    u8 mask;
    u8 len;
    s32 obj;
    u8 b2, g2, r2, a2;
    u8 b, g, r, a;
    u8 pad18[0x20];
} Afx_b408_01E06110;

typedef struct Rib_b408_01E06110 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 on;
    u8 sel;
    u8 pad7;
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
    Vec4f pos;
    f32 vel[3];
    u8 pad44[4];
    s32 rot[3];
    u8 pad54[4];
    s32 drot[3];
    u8 pad64[4];
} Rib_b408_01E06110;

typedef struct Flear_b408_01E06110 {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 on;
    u8 sel;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    Vec4f pos;
    Vec4f vel;
    f32 ox, oy, oz;
    u8 pad48[4];
} Flear_b408_01E06110;

typedef struct Vec3_b408_01E06110 {
    f32 x, y, z;
} Vec3_b408_01E06110;

typedef struct Bolt_b408_01E06110 {
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
    Vec3_b408_01E06110 p0;
    Vec3_b408_01E06110 p1;
    Vec3_b408_01E06110 vel;
} Bolt_b408_01E06110;

typedef struct Em_b408_01E06110 {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 on;
    u8 sel;
    u8 b7;
    void *pool;
    u8 count;
    u8 bD;
    u8 bE;
    u8 bF;
    u8 b10;
    u8 b11;
    u8 pad12[2];
    s32 range;
    f32 f18;
    f32 f1C;
    u8 b, g, r, a;
    f32 x, y, z;
    f32 vx, vy, vz;
} Em_b408_01E06110;

typedef struct Mptc_b408_01E06110 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 on;
    u8 pad6[2];
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
    Vec4f pos;
    u8 pad38[0x20];
} Mptc_b408_01E06110;

typedef struct Fade_b408_01E06110 {
    u8 pad0[4];
    u8 on;
    u8 pad5[3];
} Fade_b408_01E06110;

typedef struct Col_b408_01E06110 {
    u8 b, g, r, a;
} Col_b408_01E06110;

typedef struct Cyl_b408_01E06110 {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 cnt;
    u8 tex;
    u8 bA;
    u8 mode;
    Vec3_b408_01E06110 *pts;
    f32 usize;
    f32 f14;
    f32 uscale;
    f32 vscale;
    f32 r;
    f32 dr;
    Col_b408_01E06110 c;
} Cyl_b408_01E06110;

typedef struct Arc_b408_01E06110 {
    s32 n;
    f32 jitter;
    f32 angle;
    f32 bend;
    Vec3_b408_01E06110 a;
    Vec3_b408_01E06110 b;
    Vec3_b408_01E06110 *pts;
} Arc_b408_01E06110;

typedef struct Scene_b408_01E06110 {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[3];
    u8 pad18[0x14];
    Cam_b408_01E06110 cam;
    Emit_b408_01E06110 emit;
    Wv_b408_01E06110 wv;
    Gus_b408_01E06110 gus[250];
    Afx_b408_01E06110 afx;
    Afx_b132_01E04B00 glow;
    Rib_b408_01E06110 rib[0x3C];
    Flear_b408_01E06110 flear[0x10];
    Bolt_b408_01E06110 bolt[0x3C];
    Em_b408_01E06110 em[8];
    Mptc_b408_01E06110 mptc[0x14];
    Fade_b408_01E06110 fade;
    u8 tbl[0x100];
    Vec3_b408_01E06110 pts[48];
    Cyl_b408_01E06110 cyl[2];
    u8 pad7BF8[8];
} Scene_b408_01E06110;

static s32 func_01E06110_b408(Scene_b408_01E06110 *g, s32 code) {
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
    extern void func_00101AD0(void *, s32, u8, s32);
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_00102CB0(void *);
    extern s32 b408_01E04110();
    s32 ot;
    Vec4f v;
    Vec4f w[2];
    Arc_b408_01E06110 arc;
    Vec3_b408_01E06110 pts[17];
    s32 i;
    s32 j;
    s32 k;
    f32 s;
    f32 dx;
    f32 dy;
    f32 dz;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x7C00);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (j = 0; j < 3; j++) {
            func_00202BF0(5, j);
        }
        g->m[0] = func_001F5560(g->unitA, 9, 1);
        g->m[1] = func_001F5560(g->unitA, 0xE, 0);
        g->m[2] = func_001F5560(g->unitA, 0xF, 0);
        g->wv.a = 2;
        g->wv.b = 0xE2;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x2:
        k = func_00101C30(g->flear, 0x4C, 0x10);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x3A, 0, 0xFF);
            g->flear[k].on = 1;
            g->flear[k].sel = g->m[0];
            g->flear[k].flags = 0x85;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].alpha = 0x80;
            g->flear[k].ib = 0x80;
            g->flear[k].ig = 0x80;
            g->flear[k].ir = 0x80;
            g->flear[k].radius = 600.0f;
            g->flear[k].grow = 0.0f;
        }
        func_00101AD0(&g->emit, 0xFA, 0, 0xFF);
        g->emit.on = 1;
        g->emit.sel = g->m[0];
        g->emit.kind = 1;
        g->emit.f14 = 1.2f;
        g->emit.f18 = 1.2f;
        g->emit.f1C = 1.8f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 2.0f;
        for (i = 0; i < 2; i++) {
            k = func_00101C30(g->em, 0x3C, 8);
            func_00101AD0(&g->em[k], 0x30, i, 0);
            g->em[k].on = 1;
            g->em[k].sel = g->m[i];
            g->em[k].flags = 2;
            g->em[k].pool = g->bolt;
            g->em[k].count = 0x3C;
            g->em[k].bD = 9;
            g->em[k].bE = 1;
            g->em[k].bF = 0;
            g->em[k].b10 = 5;
            g->em[k].b11 = 0xC;
            g->em[k].range = 2000;
            g->em[k].f18 = 1.0f;
            g->em[k].f1C = 0.4f;
            g->em[k].b = 0x80;
            g->em[k].g = 0x80;
            g->em[k].r = 0x80;
            g->em[k].a = 0x20;
            g->em[k].vx = g->em[k].vy = g->em[k].vz = 0.0f;
        }
        break;
    case 0x32:
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
        g->afx.on = 1;
        g->afx.sel = g->m[2];
        break;
    case 0x3C:
        func_00101AD0(&g->fade, 0x10, 0, 0xFF);
        g->fade.on = 1;
        func_00101AD0(&g->emit, 0xA8, 0, 0xFF);
        g->emit.on = 0;
        g->emit.kind = 8;
        g->emit.f14 = 1.0f;
        g->emit.f18 = 1.4f;
        g->emit.f1C = 2.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 160.0f;
        g->emit.pos = v;
        g->emit.f50 = 8.0f;
        g->emit.pos.z = 0.0f;
        func_001F5620(g->unitA, g->m[0], &w[0]);
        k = func_00101C30(g->flear, 0x4C, 0x10);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x14, 0, 0xFF);
            g->flear[k].on = 0;
            g->flear[k].flags = 0x80;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].alpha = 0xF0;
            g->flear[k].ib = 0xF0;
            g->flear[k].ig = 0xF0;
            g->flear[k].ir = 0xF0;
            g->flear[k].radius = 100.0f;
            g->flear[k].grow = 60.0f;
            g->flear[k].width = 50.0f;
            g->flear[k].pos = w[0];
        }
        k = func_00101C30(g->flear, 0x4C, 0x10);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x80, 0xC, 0xFF);
            g->flear[k].on = 1;
            g->flear[k].sel = g->m[0];
            g->flear[k].flags = 0x82;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].alpha = 0xB0;
            g->flear[k].ib = 0xB0;
            g->flear[k].ig = 0xB0;
            g->flear[k].ir = 0xB0;
            g->flear[k].radius = 600.0f;
            g->flear[k].grow = 0.0f;
            g->flear[k].width = 0.0f;
        }
        for (i = 0; i < 8; i++) {
            func_00101AD0(&g->mptc[i], 0x20, i, 0xFF);
            g->mptc[i].age -= 4;
            g->mptc[i].flags = 5;
            g->mptc[i].on = 0;
            g->mptc[i].count = 0x32;
            g->mptc[i].k = i;
            g->mptc[i].idx = 0;
            g->mptc[i].b5c = 2;
            g->mptc[i].frame = (func_0019A5C8() >> 4) & 3;
            g->mptc[i].width = 60.0f;
            g->mptc[i].grow = -0.6f;
            g->mptc[i].pts = g->tbl;
            g->mptc[i].scale = 2.0f;
            g->mptc[i].a = 0x80;
            g->mptc[i].r = 0x80;
            g->mptc[i].g = 0x80;
            g->mptc[i].b = 0x80;
            func_001F5620(g->unitA, g->m[0], &g->mptc[i].pos);
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 6; j++) {
                func_00101AD0(&g->bolt[i * 6 + j], 0x91, i & 1, 0xFF);
                g->bolt[i * 6 + j].mode = 0;
                g->bolt[i * 6 + j].flags = 0;
                g->bolt[i * 6 + j].nseg = 9;
                g->bolt[i * 6 + j].jitter = 0.7f;
                g->bolt[i * 6 + j].grow = 0.2f;
                g->bolt[i * 6 + j].texid = 1;
                g->bolt[i * 6 + j].wdiv = 3;
                g->bolt[i * 6 + j].texsel = 0;
                g->bolt[i * 6 + j].b = 0x80;
                g->bolt[i * 6 + j].g = 0x80;
                g->bolt[i * 6 + j].r = 0x80;
                g->bolt[i * 6 + j].a = 0x20;
            }
        }
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->cyl[i], 0x8C, 0, 0xFF);
            g->cyl[i].seg = 0xC;
            g->cyl[i].cnt = 0x17;
            g->cyl[i].mode = 8;
            g->cyl[i].tex = 2;
            g->cyl[i].bA = 2;
            g->cyl[i].pts = g->pts;
            g->cyl[i].f14 = 1.0f;
            g->cyl[i].uscale = 0.02f;
            g->cyl[i].vscale = 0.3f;
            if (i) {
                g->cyl[i].usize = 2.0f;
                g->cyl[i].usize = 1.0f;
                g->cyl[i].r = 0.8f;
                g->cyl[i].c.r = g->cyl[i].c.g = g->cyl[i].c.b = g->cyl[i].c.a = 0xC0;
            } else {
                g->cyl[i].usize = 2.0f;
                g->cyl[i].r = 1.6f;
                g->cyl[i].c.r = g->cyl[i].c.g = g->cyl[i].c.b = 0x80;
                g->cyl[i].c.a = 0x50;
            }
            g->cyl[i].dr = 0.0f;
        }
        k = func_00101C30(g->flear, 0x4C, 0x10);
        if (k >= 0) {
            func_00101AD0(&g->flear[k], 0x96, 0, 0xFF);
            g->flear[k].on = 0;
            g->flear[k].sel = g->m[0];
            g->flear[k].flags = 0x85;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x40;
            g->flear[k].g = 0x20;
            g->flear[k].b = 0x80;
            g->flear[k].alpha = 0xC0;
            g->flear[k].ib = 0xC0;
            g->flear[k].ig = 0xC0;
            g->flear[k].ir = 0xC0;
            g->flear[k].radius = 1000.0f;
            g->flear[k].grow = 0.0f;
            g->flear[k].pos = v;
        }
        for (i = 0; i < 4; i++) {
            func_00101AD0(&g->em[i], 0x8C, i, 3);
            g->em[i].on = 0;
            g->em[i].flags = 0;
            g->em[i].pool = g->bolt;
            g->em[i].count = 0x3C;
            g->em[i].bD = 0xC;
            g->em[i].bE = 1;
            g->em[i].bF = 0;
            g->em[i].b10 = 6;
            g->em[i].b11 = 0x12;
            g->em[i].range = 6000;
            g->em[i].f18 = 0.8f;
            g->em[i].f1C = 0.4f;
            g->em[i].b = 0x80;
            g->em[i].g = 0x80;
            g->em[i].r = 0x80;
            g->em[i].a = 0x30;
            g->em[i].x = v.x;
            g->em[i].y = v.y;
            g->em[i].z = v.z;
            g->em[i].vx = g->em[i].vy = g->em[i].vz = 0.0f;
        }
        break;
    case 0xC8:
        for (i = 0; i < 8; i++) {
            func_00101AD0(&g->mptc[i], 0x20, i, 0xFF);
            g->mptc[i].age -= 4;
            g->mptc[i].flags = 5;
            g->mptc[i].on = 0;
            g->mptc[i].count = 0x28;
            g->mptc[i].k = i;
            g->mptc[i].idx = 0;
            g->mptc[i].b5c = 2;
            g->mptc[i].frame = (func_0019A5C8() >> 4) & 3;
            g->mptc[i].width = 120.0f;
            g->mptc[i].grow = -0.8f;
            g->mptc[i].pts = g->tbl;
            g->mptc[i].scale = 2.0f;
            g->mptc[i].a = 0x80;
            g->mptc[i].r = 0x80;
            g->mptc[i].g = 0x80;
            g->mptc[i].b = 0x80;
            g->mptc[i].pos = v;
        }
        break;
    case 0xE8:
        return 8;
    }
    if (g->t >= 2 && g->t <= 0xBD && (g->t & 1)) {
        k = func_00101C30(g->rib, 0x68, 0x3C);
        if (k >= 0) {
            func_00101AD0(&g->rib[k], 0x12, 0, 0xFF);
            g->rib[k].flags = 5;
            if (g->t < 0x3C) {
                g->rib[k].scale = 2.0f;
                g->rib[k].width = 20.0f;
                g->rib[k].count = 0x10;
            } else {
                g->rib[k].scale = 3.5f;
                g->rib[k].width = 35.0f;
                g->rib[k].count = 0x14;
            }
            g->rib[k].on = 1;
            g->rib[k].sel = g->m[0];
            g->rib[k].idx = 0;
            g->rib[k].b5c = 2;
            g->rib[k].frame = 3;
            g->rib[k].k = func_0019A5C8() >> 4;
            g->rib[k].pts = g->tbl;
            g->rib[k].f18 = 1.0f;
            g->rib[k].b1c = 0x80;
            g->rib[k].g1 = 0x80;
            g->rib[k].r1 = 0x80;
            g->rib[k].b0 = 0x80;
            g->rib[k].g0 = 0x80;
            g->rib[k].r0 = 0x80;
            g->rib[k].a0 = 0x10;
            g->rib[k].a1 = 0x40;
            g->rib[k].drot[0] = (func_0019A5C8() >> 4) & 0x7F;
            g->rib[k].drot[1] = (func_0019A5C8() >> 4) & 0x7F;
            g->rib[k].drot[2] = (func_0019A5C8() >> 4) & 0x7F;
        }
    }
    if (g->t >= 0x3C && g->t <= 0xC8) {
        func_001F5620(g->unitA, g->m[0], &w[0]);
        w[1] = w[0];
        dx = (v.x - w[0].x) / 24.0f;
        dy = (v.y - w[0].y) / 24.0f;
        dz = (v.z - w[0].z) / 24.0f;
        for (i = 0; i < 24; i++) {
            g->pts[i].x = w[0].x + dx * i;
            g->pts[i].y = w[0].y + dy * i;
            g->pts[i].z = w[0].z + dz * i;
        }
        for (j = 0; j < 4; j++) {
            arc.n = 6;
            arc.jitter = 5.0f + (f32)((func_0019A5C8() >> 4) % 2 * 200 - 200) / 100.0f;
            arc.angle = 90.0f * j;
            if (j & 1) {
                arc.bend = 47.0f;
            } else {
                arc.bend = -67.0f;
            }
            arc.pts = pts;
            arc.a.x = w[0].x;
            arc.a.y = w[0].y;
            arc.a.z = w[0].z;
            arc.b.x = v.x;
            arc.b.y = v.y;
            arc.b.z = v.z;
            func_00102CB0(&arc);
            for (i = 0; i < 6; i++) {
                g->bolt[j * 6 + i].p0 = pts[i];
                g->bolt[j * 6 + i].p1 = pts[i + 1];
            }
        }
    }
    if (g->t >= 0x3C && g->t <= 0xB3 && (g->t & 1)) {
        k = func_00101C30(g->rib, 0x68, 0x3C);
        if (k >= 0) {
            func_00101AD0(&g->rib[k], 0x18, 0, 0xFF);
            g->rib[k].flags = 5;
            g->rib[k].scale = 3.5f;
            g->rib[k].width = 50.0f;
            g->rib[k].count = 0x14;
            g->rib[k].on = 0;
            g->rib[k].idx = 0;
            g->rib[k].b5c = 2;
            g->rib[k].frame = 3;
            g->rib[k].k = func_0019A5C8() >> 4;
            g->rib[k].pts = g->tbl;
            g->rib[k].f18 = 1.0f;
            g->rib[k].b1c = 0x80;
            g->rib[k].g1 = 0x80;
            g->rib[k].r1 = 0x80;
            g->rib[k].b0 = 0x80;
            g->rib[k].g0 = 0x80;
            g->rib[k].r0 = 0x80;
            g->rib[k].a0 = 0x20;
            g->rib[k].a1 = 0x80;
            g->rib[k].drot[0] = (func_0019A5C8() >> 4) & 0x7F;
            g->rib[k].drot[1] = (func_0019A5C8() >> 4) & 0x7F;
            g->rib[k].drot[2] = (func_0019A5C8() >> 4) & 0x7F;
            g->rib[k].pos = v;
        }
    }
    if (g->t >= 2 && g->t <= 0x25) {
        for (i = 0; i < 10; i++) {
            k = func_00101C30(g->gus, 0x44, 0xC8);
            if (k >= 0) {
                func_001F5620(g->unitA, g->m[i & 1], &w[0]);
                s = 12.0f + (f32)((func_0019A5C8() >> 4) % 6 * 200 - 600) / 100.0f;
                func_00101AD0(&g->gus[k], (u8)(s32)s, 0, 0xFF);
                g->gus[k].flags = 0x41;
                g->gus[k].texkind = 0;
                g->gus[k].page = 2;
                g->gus[k].mode = func_0019A5C8() >> 4 & 7;
                g->gus[k].texmode = 0;
                g->gus[k].b = 0x80;
                g->gus[k].g = 0x80;
                g->gus[k].r = 0x80;
                g->gus[k].a = 0x60;
                g->gus[k].size = 80.0f;
                g->gus[k].grow = -5.0f;
                g->gus[k].gravity = g->gus[k].floor = 0.0f;
                w[1].x = (f32)((func_0019A5C8() >> 4) % 30 * 200 - 3000) / 100.0f;
                w[1].y = (f32)((func_0019A5C8() >> 4) % 30 * 200 - 3000) / 100.0f;
                w[1].z = (f32)((func_0019A5C8() >> 4) % 30 * 200 - 3000) / 100.0f;
                g->gus[k].px = w[0].x + w[1].x;
                g->gus[k].py = w[0].y + w[1].y;
                g->gus[k].pz = w[0].z + w[1].z;
                g->gus[k].vx = -(w[1].x / s);
                g->gus[k].vy = -(w[1].y / s);
                g->gus[k].vz = -(w[1].z / s);
                g->gus[k].ax = g->gus[k].ay = g->gus[k].az = 0.0f;
            }
        }
    }
    func_01E00080_b408((Fx_b005_01E00080 *)&g->emit);
    func_001031C0(&g->wv, g->t);
    b408_01E04110(&g->fade, ot);
    func_01E003A0_b408((Afx_b172_01E012E0 *)&g->afx, ot, 1);
    func_01E05870_b408(&g->glow, ot, 1);
    func_01E011B0_b408((Obj_b051_01E003A0 *)g->flear, ot, 0x10);
    func_01E01C00_b408((Rib_b029_01E02B80 *)g->rib, ot, 0x3C);
    func_01E03170_b408((Em_b238_01E02360 *)g->em, ot, 8);
    func_01E026E0_b408(g->bolt, ot, 0x3C);
    func_01E034B0_b408((Rib_b285_01E014C0 *)g->mptc, ot, 0x14);
    func_01E045F0_b408(g->gus, ot, 0xC8);
    func_01E04F00_b408((Cyl_b062_01E020A0 *)g->cyl, ot, 2);
    if (g->t >= 0x3C && g->t <= 0xC4) {
        return 6;
    }
    switch (g->t) {
    case 0x32:
        return 1;
    case 0xC5:
        return 2;
    }
    return 0;
}
