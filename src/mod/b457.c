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

static void func_01E00080_b457(Fx_b005_01E00080 *o) {
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

static s32 func_01E003A0_b457(Afx_b172_01E012E0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

static s32 func_01E011B0_b457(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E07B00_b457;
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
    t = D_01E07B00_b457;
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

static s32 func_01E01C00_b457(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern Uvs_b029_01E02B80 D_01E07B20_b457;
    Uvs_b029_01E02B80 tbl = D_01E07B20_b457;
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

/* shape b457:01E026E0, 756 insns: draws n lightning strips (0x20-byte emitters) along each emitter's point list:
   texture either a fixed atlas cell with its own blend (flag 1) or the emitter's animated cell; every projected
   segment becomes 2 or (life & 3) + 1 quads widened across the shorter screen axis, ends faded when flag 0xF.1;
   the corner order rotates with the segment (flag 4) or with age. Sibling of b070:01E03C10. */

typedef struct {
    f32 x, y, z;
} Vec3_b457_01E026E0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b457_01E026E0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b457_01E026E0 xyz;
} Vtx_b457_01E026E0;

typedef struct {
    u64 u : 14;
    u64 pad0 : 2;
    u64 v : 14;
    u64 pad1 : 34;
} UV_b457_01E026E0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b457_01E026E0 v[4];
    u8 tail[0x20];
} Pkt_b457_01E026E0;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b457_01E026E0;

typedef struct {
    u8 b5[5];
    u8 b5x;
    u8 pad6[0x12];
} Uvs_b457_01E026E0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 n;
    u8 texid;
    u8 frame;
    u8 bB;
    u8 anim;
    u8 wdiv;
    u8 step;
    u8 flags2;
    u8 pad10[4];
    f32 grow;
    u8 b, g, r, a;
    Vec3_b457_01E026E0 *pts;
} Strip_b457_01E026E0;

extern Tex_b457_01E026E0 D_01E07B40_b457;

static s32 func_01E026E0_b457(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101EE0(void *, void *, void *);
    extern void func_001020B0();
    extern void func_00101C80(void *, void *);
    Strip_b457_01E026E0 *e = arg0;
    f32 mat[16];
    Xyz_b457_01E026E0 s[3];
    Vec4f v;
    Uvs_b457_01E026E0 uvs;
    Tex_b457_01E026E0 tmpl;
    Pkt_b457_01E026E0 pkt __attribute__((aligned(8)));
    f32 depth[2];
    u8 bl[4];
    Vec3_b457_01E026E0 *pts;
    s32 i;
    void *tex;
    s32 j;
    s32 start;
    s32 end;
    s32 cnt;
    s32 rot;
    s32 k;
    s32 dx;
    s32 dy;
    f32 fdx;
    f32 fdy;
    f32 w;
    u32 c0;
    u32 c1;
    f32 z;

    tmpl = D_01E07B40_b457;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        func_0020EB40(mat);
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b457_01E026E0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->flags & 1) {
            tex = (void *)func_00202BF0(4, 0xF);
            ((Pkt_b457_01E026E0 *)(s32)&pkt)->count |= 0x800;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[0].st)->u = tmpl.u * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[0].st)->v = tmpl.h * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[1].st)->u = tmpl.u * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[1].st)->v = tmpl.v * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[2].st)->u = tmpl.w * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[2].st)->v = tmpl.h * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[3].st)->u = tmpl.w * 16;
            ((UV_b457_01E026E0 *)(s32)&pkt.v[3].st)->v = tmpl.v * 16;
            func_00208CB0(&pkt, (u64)0xA | ((u64)tmpl.u << 4) | ((u64)tmpl.w << 14) | ((u64)tmpl.v << 24) |
                                    ((u64)(tmpl.h - 1) << 34));
            func_00208700(&pkt, tex, 1);
            func_00101C80(&tmpl, bl);
            func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        } else {
            tex = (void *)func_00202BF0(5, e->texid);
            uvs.b5x = e->bB;
            func_001020B0(&uvs, e->frame, e->anim);
            func_00101EE0(&pkt, &uvs, tex);
        }
        if (!(e->flags & 2) && e->life < e->n) {
            start = e->n - e->life;
        } else {
            start = 0;
        }
        if (e->step > 0 && e->max - e->life < e->n / e->step) {
            end = e->step * (e->max - e->life);
        } else {
            end = e->n;
        }
        pts = e->pts;
        for (j = start; j < end; j++) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
            if (e->flags2 & 1) {
                if (j == start) {
                    pkt.v[0].a = pkt.v[1].a = 0;
                }
                if (j == end - 1) {
                    pkt.v[2].a = pkt.v[3].a = 0;
                }
            }
            v.x = pts[j].x;
            v.y = pts[j].y;
            v.z = pts[j].z;
            if (func_00205440(&v, mat, &s[0], &depth[0]) == 0 || func_00101600(&s[0]) == 0) {
                continue;
            }
            v.x = pts[j + 1].x;
            v.y = pts[j + 1].y;
            v.z = pts[j + 1].z;
            if (func_00205440(&v, mat, &s[1], &depth[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            dx = s[0].x - s[1].x;
            fdx = (dx >= 0) ? dx : -dx;
            dy = s[0].y - s[1].y;
            fdy = (dy >= 0) ? dy : -dy;
            w = func_001A6C60(fdx * fdx + fdy * fdy) / e->wdiv;
            if (e->flags & 8) {
                cnt = 2;
            } else {
                cnt = (e->life & 3) + 1;
            }
            for (k = 0; k < cnt; k++) {
                rot = j & 3;
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
                switch ((e->flags & 4) ? rot : (e->life + j) & 3) {
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

static s32 func_01E032B0_b457(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

/* OVL_WARM */

/* shape b457:01E03790, 221 insns, 4 copies: draws a full-screen black fade quad: alpha by mode (1 fade out over the
   life, 2 fade in, else half-white 0x80), optional loop (restart life, flip mode), halved by flag 8; flags 0x20 /
   0x40 clear the alpha of the bottom / top edge. */

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b457_01E03790;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b457_01E03790 v[4];
    u8 tail[8];
} Pkt_b457_01E03790;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Fade_b457_01E03790;

static s32 func_01E03790_b457(Fade_b457_01E03790 *f, s32 ot) {
    extern s32 func_00101AF0(void *);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b457_01E03790 pkt __attribute__((aligned(8)));
    u8 flags;
    u8 a;

    if (func_00101AF0(f) == 0) {
        return 0;
    }
    ((Pkt_b457_01E03790 *)(s32)&pkt)->count = 0x14;
    ((Pkt_b457_01E03790 *)(s32)&pkt)->tag = 8;
    ((Pkt_b457_01E03790 *)(s32)&pkt)->regs = 0x41414141;
    ((Pkt_b457_01E03790 *)(s32)&pkt)->pad = 0;
    flags = f->flags;
    switch (flags & 7) {
    case 1:
        a = 128.0f / f->max * f->life;
        break;
    case 2:
        a = ((f->max - f->life) << 7) / f->max;
        break;
    case 4:
    default:
        a = 0x80;
        break;
    }
    if (f->life == 1 && (flags & 0x80)) {
        f->life = f->max;
        if (f->flags & 1) {
            f->flags = 2;
        } else {
            f->flags = 1;
        }
    }
    if (f->flags & 8) {
        a >>= 1;
    }
    pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = 0;
    pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = 0;
    pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = 0;
    pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
    pkt.v[0].z = pkt.v[1].z = pkt.v[2].z = pkt.v[3].z = 0xFFFFFF;
    func_002086D0(&pkt, 0x44);
    pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = a;
    if (f->flags & 0x20) {
        pkt.v[2].a = pkt.v[3].a = 0;
    }
    if (f->flags & 0x40) {
        pkt.v[0].a = pkt.v[1].a = 0;
    }
    pkt.v[0].x = pkt.v[2].x = 0x6C00;
    pkt.v[1].x = pkt.v[3].x = 0x9400;
    pkt.v[0].y = pkt.v[1].y = 0x7200;
    pkt.v[2].y = pkt.v[3].y = 0x8E00;
    func_002075F0(&pkt, ot, 0);
    return 1;
}

/* OVL_WARM */

/* shape b062:01E05220, 508 insns, 3 copies: moves n spark emitters (0x60 bytes each: position, velocity, turning angles,
   growing size and speed) and draws count square sprites per emitter, each pushed out from the emitter
   along a direction from its random table, scaled by the speed (optionally jittered); frame from age or
   fixed, alpha fading at the end. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b062_01E05220;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 tc;
        Xyz_b062_01E05220 p;
    } v[4];
    u8 tail[0x20];
} Pkt_b062_01E05220;

typedef struct {
    u8 pad0[5];
    u8 page;
    u8 pad6[2];
    s32 u, w, v, h;
    u8 pad18[8];
} Tex_b062_01E05220;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 count;
    u8 seed;
    u8 texid;
    u8 frame;
    u8 bC;
    u8 bD;
    u8 padE[2];
    u8 *tbl;
    f32 speed;
    f32 dspeed;
    f32 rise;
    f32 size;
    f32 dsize;
    u8 b, g, r, a;
    s32 rot[4];
    f32 pos[3];
    f32 vel[3];
    f32 rv[3];
} Spark_b062_01E05220;

static s32 func_01E03B10_b457(void *arg0, s32 ot, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern void func_00101A00(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat2[16];
    f32 mat[16];
    f32 rm[16];
    Vec4f out;
    Vec4f p;
    Vec4f d;
    Tex_b062_01E05220 td;
    Pkt_b062_01E05220 pkt __attribute__((aligned(8)));
    f32 dep;
    Spark_b062_01E05220 *e;
    s32 i;
    void *tex;
    u8 seed;
    s32 fr;
    s32 j;
    f32 sp;
    f32 h;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Spark_b062_01E05220 *)((u8 *)e + 0x60);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        e->pos[0] += e->vel[0];
        e->pos[1] += e->vel[1];
        e->pos[2] += e->vel[2];
        e->rot[0] += e->rv[0];
        e->rot[1] += e->rv[1];
        e->rot[2] += e->rv[2];
        e->size += e->dsize;
        e->speed += e->dspeed;
        p.x = e->pos[0];
        p.y = e->pos[1];
        p.z = e->pos[2];
        func_00101BA0(e, &p);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &p);
        func_0020BC00(mat, mat2);
        seed = e->seed;
        fr = e->max - e->life;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->tag = 9;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b062_01E05220 *)(s32)&pkt)->pad = 0;
        pkt.r = e->r;
        pkt.g = e->g;
        pkt.b = e->b;
        pkt.q = 1.0f;
        fr = (e->flags & 1) ? fr & 7 : e->frame;
        td.page = e->bD;
        func_001020B0(&td, fr, e->bC);
        func_00101D20(&pkt, &td, tex);
        pkt.a = e->a;
        if (!(e->flags & 0x40) && e->life < 8) {
            pkt.a = (e->a >> 3) * e->life;
        }
        p.x = p.y = p.z = 0.0f;
        for (j = 0; j < e->count; j++) {
            if (e->flags & 8) {
                sp = e->speed;
            } else {
                sp = e->speed * (e->tbl[seed++] / 255.0f);
                if (e->flags & 4) {
                    sp = 0.5f * (sp + e->speed);
                }
            }
            if (e->flags & 2) {
                d.x = e->tbl[seed] - e->tbl[seed + 1];
                d.z = e->tbl[seed + 2] - e->tbl[seed + 3];
                d.y = 0.0f;
                p.x = sp;
                seed += 4;
            } else {
                d.x = e->tbl[seed] - e->tbl[seed + 1];
                d.z = e->tbl[seed + 2] - e->tbl[seed + 3];
                d.y = e->tbl[seed + 4] - e->tbl[seed + 5];
                p.y = sp;
                seed += 6;
            }
            func_00101A00(&d, rm);
            func_0020CDD0(&out, rm, &p);
            if (e->flags & 2) {
                out.y += (e->rise * e->tbl[seed++]) / 255.0f;
            }
            if (func_00205440(&out, mat, &pkt.v[0].p, &dep) == 0) {
                continue;
            }
            if (func_00101600(&pkt.v[0].p) == 0) {
                continue;
            }
            h = func_001018E0(e->size, dep);
            pkt.v[1].p.x = pkt.v[0].p.x + h;
            pkt.v[1].p.y = pkt.v[0].p.y - h;
            pkt.v[2].p.x = pkt.v[0].p.x - h;
            pkt.v[2].p.y = pkt.v[0].p.y + h;
            pkt.v[3].p.x = pkt.v[0].p.x + h;
            pkt.v[3].p.y = pkt.v[0].p.y + h;
            pkt.v[0].p.x = pkt.v[0].p.x - h;
            pkt.v[0].p.y = pkt.v[0].p.y - h;
            pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = pkt.v[0].p.z;
            pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
            func_002075F0(&pkt, ot, (u32)dep);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mod/b457", func_01E04300_b457);

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

static s32 func_01E04B10_b457(Cyl_b062_01E020A0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

/* shape b715:01E003A0 (ShFx_RingTX), 461 insns, 18 copies (-O3,p): n ring emitters (0x5C bytes each): an inner and an
   outer circle of up to 36 points (radii growing each frame) joined into textured quads; texture rect from
   func_001020B0, mode 1 = no clamp and s scaled by e->scale, mode 2 = a 1-texel column in the middle; far z with
   flags & 0x80; the source of shape b603:01E039B0, built here at -O3 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b715_01E003A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b715_01E003A0 xyz;
} Vtx_b715_01E003A0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b715_01E003A0 v[4];
    u8 tail[0x20];
} Pkt_b715_01E003A0;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b715_01E003A0;

typedef struct {
    u8 b, g, r, a;
} Col_b715_01E003A0;

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 texid;
    u8 sub;
    u8 bA;
    u8 bB;
    u8 mode;
    u8 padD[3];
    f32 radius[2];
    f32 dradius[2];
    f32 scale;
    Col_b715_01E003A0 c0;
    Col_b715_01E003A0 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b715_01E003A0;

#pragma optimization_level 3

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E05480_b457(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    f32 depth[4];
    Tex_b715_01E003A0 td;
    Pkt_b715_01E003A0 pkt;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b715_01E003A0 *e;
    s32 i;
    s32 tex;
    s32 nseg;
    s32 k;
    s32 r;
    f32 step;
    f32 z;

    e = arg0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = func_00202BF0(5, e->texid);
        e->radius[0] += e->dradius[0];
        e->radius[1] += e->dradius[1];
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        if (e->seg > 36) {
            nseg = 36;
        } else {
            nseg = e->seg;
        }
        step = 360.0f / nseg;
        for (r = 0; r < 2; r++) {
            for (k = 0; k < nseg; k++) {
                ring[r][k].x = e->radius[r] * func_001A6898(3.1415927f * (step * k) / 180.0f);
                ring[r][k].z = e->radius[r] * func_001A6A88(3.1415927f * (step * k) / 180.0f);
                ring[r][k].y = 0.0f;
            }
        }
        ring[0][nseg] = ring[0][0];
        ring[1][nseg] = ring[1][0];
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b715_01E003A0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->c0.r;
        pkt.v[2].r = pkt.v[3].r = e->c1.r;
        pkt.v[0].g = pkt.v[1].g = e->c0.g;
        pkt.v[2].g = pkt.v[3].g = e->c1.g;
        pkt.v[0].b = pkt.v[1].b = e->c0.b;
        pkt.v[2].b = pkt.v[3].b = e->c1.b;
        td.b5 = e->sub;
        func_001020B0(&td, e->bB, e->bA);
        func_00102210(e->bA, &sw, &sh);
        switch (e->mode & 3) {
        case 1:
            func_00208CB0(&pkt, 0);
            sw *= e->scale;
            break;
        case 2:
            td.u = td.u + ((td.w - td.u) >> 1);
            td.w = td.u + 1;
        default:
            func_00208CB0(&pkt, 0xA | ((u64)td.u << 4) | ((u64)(td.w - 1) << 14) | ((u64)td.v << 24) |
                                    ((u64)(td.h - 1) << 34));
            break;
        }
        if (e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = e->life * (e->c0.a >> 3);
            pkt.v[2].a = pkt.v[3].a = e->life * (e->c1.a >> 3);
        } else {
            pkt.v[0].a = pkt.v[1].a = e->c0.a;
            pkt.v[2].a = pkt.v[3].a = e->c1.a;
        }
        for (k = 0; k < nseg; k++) {
            if (func_00205440(&ring[0][k], mat, &pkt.v[0].xyz, &depth[0]) != 0 &&
                func_00205440(&ring[0][k + 1], mat, &pkt.v[1].xyz, &depth[1]) != 0 &&
                func_00205440(&ring[1][k], mat, &pkt.v[2].xyz, &depth[2]) != 0 &&
                func_00205440(&ring[1][k + 1], mat, &pkt.v[3].xyz, &depth[3]) != 0) {
                pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                pkt.v[0].q = 1.0f / depth[0];
                pkt.v[1].q = 1.0f / depth[1];
                pkt.v[2].q = 1.0f / depth[2];
                pkt.v[3].q = 1.0f / depth[3];
                pkt.v[0].s = td.u / sw / depth[0];
                pkt.v[0].t = td.v / sh / depth[0];
                pkt.v[1].s = td.w / sw / depth[1];
                pkt.v[1].t = td.v / sh / depth[1];
                pkt.v[2].s = td.u / sw / depth[2];
                pkt.v[2].t = td.h / sh / depth[2];
                pkt.v[3].s = td.w / sw / depth[3];
                pkt.v[3].t = td.h / sh / depth[3];
                func_00101C80(&td, bl);
                func_002086D0(&pkt, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
                func_00208700(&pkt, (void *)tex, 1);
                if (e->flags & 0x80) {
                    pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                    z = 0.0f;
                } else {
                    z = (depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f;
                }
                func_002075F0((s32)&pkt, ot, (u32)z);
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b457:01E05BC0 (ShFx_Afx08), 514 insns, 4 copies (-O3,p): flickering screen-band effect, per
   emitter a random on/off timer and per-column random height jitter drawn as textured quads */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b457_01E05BC0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b457_01E05BC0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b457_01E05BC0 uv;
    Xyz_b457_01E05BC0 xyz;
} Vtx_b457_01E05BC0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b457_01E05BC0 v[4];
    u8 tail[8];
} Pkt_b457_01E05BC0;

typedef struct {
    u8 pad0[8];
    s32 on;
    u8 blend;
    u8 prob;
    u8 range;
    u8 timer;
    u8 maskOn;
    u8 maskOff;
    u8 step;
    u8 pad13;
    s32 obj;
    u8 b, g, r, a;
    u8 pad1C[0x10];
    s16 h[0x280];
} Afx_b457_01E05BC0;

#pragma optimization_level 3

static s32 func_01E05BC0_b457(Afx_b457_01E05BC0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_001F7060(s32, s32, void *, void *);
    extern Vec4f *func_001F9AD0(s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00101C80(void *, u8 *);
    s32 r;
    f32 mat[16];
    Vec4f pos;
    u8 td[0x20];
    struct {
        Pkt_b457_01E05BC0 pk;
        s32 a[2];
        s32 b[2];
    } w;
    Xyz_b457_01E05BC0 xy;
    u8 bl[4];
    f32 depth;
    s32 i;
    s32 list;
    s32 any;
    s16 *p;
    s32 u;
    Afx_b457_01E05BC0 *e;
    s32 j;

    e = arg0;
    list = func_00207F60();
    any = 0;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->timer == 0) {
            if (e->on) {
                e->on = 0;
                e->timer = ((func_0019A5C8() >> 4) & e->maskOff) + 1;
            } else {
                e->on = 1;
                e->timer = ((func_0019A5C8() >> 4) & e->maskOn) + 1;
            }
        }
        e->timer--;
        if (any == 0) {
            ((Pkt_b457_01E05BC0 *)(s32)&w.pk)->count = 0x34;
            ((Pkt_b457_01E05BC0 *)(s32)&w.pk)->tag = 0xC;
            ((Pkt_b457_01E05BC0 *)(s32)&w.pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
            ((Pkt_b457_01E05BC0 *)(s32)&w.pk)->pad = 0;
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
            ((Pkt_b457_01E05BC0 *)(s32)&w.pk)->count |= 0x800;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[0].uv)->u = 0;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[0].uv)->v = 0;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[1].uv)->u = 0x2800;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[1].uv)->v = 0;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[2].uv)->u = 0;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[2].uv)->v = 0x1C00;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[3].uv)->u = 0x2800;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[3].uv)->v = 0x1C00;
        }
        func_0020EB40(mat);
        func_001F9AD0(0);
        func_001F53C0(1, e->obj, &pos);
        if (func_00205440(&pos, mat, &xy, &depth) == 0) {
            continue;
        }
        w.pk.v[0].xyz.z = w.pk.v[1].xyz.z = w.pk.v[2].xyz.z = w.pk.v[3].xyz.z = xy.z;
        w.pk.v[0].xyz.f = w.pk.v[1].xyz.f = w.pk.v[2].xyz.f = w.pk.v[3].xyz.f = 0;
        td[5] = e->blend;
        func_00101C80(td, bl);
        func_002086D0(&w.pk, (u64)bl[0] | ((u64)bl[1] << 2) | ((u64)bl[2] << 4) | ((u64)bl[3] << 6));
        w.pk.v[0].a = w.pk.v[1].a = w.pk.v[2].a = w.pk.v[3].a = e->a;
        w.pk.v[0].r = w.pk.v[1].r = w.pk.v[2].r = w.pk.v[3].r = e->r;
        w.pk.v[0].g = w.pk.v[1].g = w.pk.v[2].g = w.pk.v[3].g = e->g;
        w.pk.v[0].b = w.pk.v[1].b = w.pk.v[2].b = w.pk.v[3].b = e->b;
        for (j = 0; j < 0x280; j += e->step) {
            p = &e->h[j];
            if (*p == 0) {
                if ((u8)(func_0019A5C8() >> 4) < e->prob) {
                    r = e->range;
                    *p = ((func_0019A5C8() >> 4) % r * 200 - (r * 200 >> 1)) / 100.0f;
                }
            } else {
                *p = 0;
            }
            u = j << 4;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[0].uv)->u = u;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[0].uv)->v = 0;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[1].uv)->u = (j + e->step) << 4;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[1].uv)->v = 0;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[2].uv)->u = u;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[2].uv)->v = 0x1C00;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[3].uv)->u = (j + e->step) << 4;
            ((Uv_b457_01E05BC0 *)(s32)&w.pk.v[3].uv)->v = 0x1C00;
            if (e->on == 0) {
                w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = 0x7200;
                w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = 0x8E00;
            } else {
                w.pk.v[0].xyz.y = w.pk.v[1].xyz.y = 29184.0f + (*p << 4);
                w.pk.v[2].xyz.y = w.pk.v[3].xyz.y = 29184.0f + ((*p + 0x1C0) << 4);
            }
            w.pk.v[0].xyz.x = w.pk.v[2].xyz.x = 27648.0f + u;
            w.pk.v[1].xyz.x = w.pk.v[3].xyz.x = 27648.0f + ((j + e->step) << 4);
            func_002075F0(&w.pk, 0, (u32)depth);
        }
    }
    if (any) {
        func_00207FD0(list, ot, 0);
    }
    return 1;
}
#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b457", func_01E063D0_b457);
