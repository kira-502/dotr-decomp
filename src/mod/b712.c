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

static void func_01E00080_b712(Obj_b002_01E00080 *arg0) {
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

/* shape b011:01E02AD0 (ShFx_Afx01), 738 insns, 2 copies (-O1,p): the -O1 build of ShFx_Afx01 (b010:01E015A0's C):
   draws n glow entities (0x30 bytes each) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b011_01E02AD0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b011_01E02AD0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b011_01E02AD0 uv;
    Xyz_b011_01E02AD0 xyz;
} Vtx_b011_01E02AD0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b011_01E02AD0 v[4];
    u8 tail[8];
} Pkt_b011_01E02AD0;

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
    Xyz_b011_01E02AD0 xy;
} Afx_b011_01E02AD0;

#pragma optimization_level 1

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E00440_b712(Afx_b011_01E02AD0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00101770(void *);
    extern void func_00101C80(void *, u8 *);
    Afx_b011_01E02AD0 *e = arg0;
    f32 mat[16];
    u8 td[0x20];
    Pkt_b011_01E02AD0 pk;
    f32 depth;
    u8 bl[4];
    s32 i;
    s32 u;
    s32 v;
    s32 j;
    s32 sz;

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
        ((Pkt_b011_01E02AD0 *)(s32)&pk)->count = 0x33;
        ((Pkt_b011_01E02AD0 *)(s32)&pk)->tag = 9;
        ((Pkt_b011_01E02AD0 *)(s32)&pk)->regs = ((u64)4 << 32) | 0x21421421;
        ((Pkt_b011_01E02AD0 *)(s32)&pk)->pad = 0;
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
        ((Pkt_b011_01E02AD0 *)(s32)&pk)->count |= 0x800;
        ((Uv_b011_01E02AD0 *)(s32)&pk.v[2].uv)->u = u;
        ((Uv_b011_01E02AD0 *)(s32)&pk.v[2].uv)->v = v;
        pk.v[2].xyz.x = e->xy.x;
        pk.v[2].xyz.y = e->xy.y;
        if (e->life < 8) {
            pk.v[0].a = pk.v[1].a = (e->a >> 3) * e->life;
            pk.v[2].a = (e->a2 >> 3) * e->life;
        } else {
            pk.v[0].a = pk.v[1].a = e->a;
            pk.v[2].a = e->a2;
        }
        sz = e->size + (e->life & 3) * 2;
        for (j = 0; j < 8; j++) {
            if (!(e->mask & (1 << j))) {
                continue;
            }
            switch (j) {
            case 0:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = v;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[0].xyz.y = e->xy.y;
                pk.v[1].xyz.y = (u32)(29184.0f - (sz << 4));
                break;
            case 1:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = u;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[1].xyz.x = e->xy.x;
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f - (sz << 4));
                break;
            case 2:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = u;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = 0;
                pk.v[0].xyz.x = e->xy.x;
                pk.v[1].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(29184.0f - (sz << 4));
                break;
            case 3:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = v;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[0].xyz.y = (u32)(29184.0f - (sz << 4));
                pk.v[1].xyz.y = e->xy.y;
                break;
            case 4:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = v;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = 0x2800;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[0].xyz.y = e->xy.y;
                pk.v[1].xyz.y = (u32)(36352.0f + (sz << 4));
                break;
            case 5:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = 0x2800;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = u;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = (u32)(37888.0f + (sz << 4));
                pk.v[1].xyz.x = e->xy.x;
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(36352.0f + (sz << 4));
                break;
            case 6:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = u;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = 0x1C00;
                pk.v[0].xyz.x = e->xy.x;
                pk.v[1].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[0].xyz.y = pk.v[1].xyz.y = (u32)(36352.0f + (sz << 4));
                break;
            case 7:
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->u = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[0].uv)->v = 0x1C00;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->u = 0;
                ((Uv_b011_01E02AD0 *)(s32)&pk.v[1].uv)->v = v;
                pk.v[0].xyz.x = pk.v[1].xyz.x = (u32)(27648.0f - (sz << 4));
                pk.v[0].xyz.y = (u32)(36352.0f + (sz << 4));
                pk.v[1].xyz.y = e->xy.y;
                break;
            }
            func_002075F0(&pk, ot, 0);
        }
    }
    return 1;
}

/* shape b712:01E00FD0 (ShFx_Fdust), 356 insns, 1 copy (-O1,p): draws n dust billboards (0x20-byte emitters) rising
   along y: a screen-space sprite sized by depth, its colour and texture frame picked by flag 1 and age */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b712_01E00FD0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b712_01E00FD0;

typedef struct {
    u64 st;
    Xyz_b712_01E00FD0 xyz;
} Vtx_b712_01E00FD0;

typedef struct {
    Hdr_b712_01E00FD0 h;
    u8 r, g, b, a;
    f32 q;
    Vtx_b712_01E00FD0 v[4];
    u8 tail[0x20];
} Pkt_b712_01E00FD0;

typedef struct {
    f32 x, y, z, w;
} V4_b712_01E00FD0;

typedef struct {
    s32 id;
    u8 kind;
    u8 b5;
    u8 pad06[2];
    s32 w[4];
} Tex_b712_01E00FD0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 tex;
    u8 b9;
    u8 bA;
    u8 bB;
    f32 size;
    f32 vy;
    f32 x, y, z;
} Obj_b712_01E00FD0;

#pragma optimization_level 1

static s32 func_01E00FD0_b712(Obj_b712_01E00FD0 *obj, s32 ot, s32 n) {
    extern Tex_b712_01E00FD0 D_01E03200_b712[];
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_0020EB40(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern void func_001020B0();
    extern void func_00101D20(void *, void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Obj_b712_01E00FD0 *o;
    s32 i;
    s32 h;
    f32 m[16];
    Tex_b712_01E00FD0 t;
    V4_b712_01E00FD0 v;
    Xyz_b712_01E00FD0 scr;
    Pkt_b712_01E00FD0 p __attribute__((aligned(8)));
    f32 depth;
    s32 fr;
    f32 s;

    o = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        if (o->flags & 1) {
            h = func_00202BF0(5, o->tex);
        } else {
            h = func_00202BF0(D_01E03200_b712[o->tex].id, D_01E03200_b712[o->tex].kind);
        }
        o->y += o->vy;
        v.x = o->x;
        v.y = o->y;
        v.z = o->z;
        func_0020EB40(m);
        ((Hdr_b712_01E00FD0 *)(s32)&p)->count = 0x24;
        ((Hdr_b712_01E00FD0 *)(s32)&p)->tag = 9;
        ((Hdr_b712_01E00FD0 *)(s32)&p)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b712_01E00FD0 *)(s32)&p)->pad = 0;
        if (o->flags & 1) {
            if (o->max >> 1 < o->cur) {
                fr = o->b9;
                p.r = p.g = p.b = 0x80;
            } else {
                fr = o->bA;
                p.r = 0x60;
                p.g = 0x10;
                p.b = 0;
            }
            if (o->cur < 8) {
                p.a = o->cur << 4;
            } else {
                p.a = 0x80;
            }
            t.b5 = o->bB;
            func_001020B0(&t, fr, 0);
            func_00101D20(&p, &t, h);
        } else {
            p.b = 0;
            if (o->max >> 1 < o->cur) {
                p.r = 0xC0;
                p.g = 0x80;
            } else {
                p.r = 0x30;
                p.g = 8;
            }
            p.q = 1.0f;
            if (o->cur < 8) {
                p.a = o->cur * 31;
            } else {
                p.a = 0xF0;
            }
            func_00101D20(&p, &D_01E03200_b712[o->tex], h);
        }
        if (func_00205440(&v, m, &scr, &depth) == 0 || func_00101600(&scr) == 0) {
            continue;
        }
        s = o->size / (depth / 256.0f);
        p.v[0].xyz.z = p.v[1].xyz.z = p.v[2].xyz.z = p.v[3].xyz.z = scr.z;
        p.v[0].xyz.x = p.v[2].xyz.x = (u32)(scr.x - s);
        p.v[1].xyz.x = p.v[3].xyz.x = (u32)(scr.x + s);
        p.v[0].xyz.y = p.v[1].xyz.y = (u32)(scr.y - s);
        p.v[2].xyz.y = p.v[3].xyz.y = (u32)(scr.y + s);
        func_002075F0(&p, ot, (u32)depth);
    }
    return 1;
}

#pragma optimization_level reset


/* shape b712:01E01560 (ShFx_Obr), 684 insns, 2 copies (-O1,p): draws n ShFx_Obr arcs (0x4C-byte emitters): a ring of
   up to 9 points between two joints swept in up to 9 rotated rows, each visible cell a textured quad with UVs from
   the texture frame */

typedef struct {
    s32 id;
    u8 kind;
    u8 b5;
    u8 pad06[2];
    s32 w[4];
} Tex_b712_01E01560;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b712_01E01560;

typedef struct {
    u16 u : 14;
    u16 u_pad : 2;
    u16 v : 14;
    u16 v_pad : 2;
} Uv_b712_01E01560;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
} Hdr_b712_01E01560;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 uv;
    Xyz_b712_01E01560 xyz;
} Vtx_b712_01E01560;

typedef struct {
    Hdr_b712_01E01560 h;
    Vtx_b712_01E01560 v[4];
    u8 tail[0x20];
} Pkt_b712_01E01560;

typedef struct {
    u8 cur;
    u8 pad1[3];
    u8 flags;
    u8 b5;
    u8 joint;
    u8 pad7;
    u8 tex;
    u8 frame;
    u8 bA;
    u8 ncol;
    u8 nrow;
    u8 jA;
    u8 jB;
    u8 bF;
    f32 scale;
    f32 astep;
    f32 rstep;
    f32 rot;
    f32 drot;
    f32 ang;
    f32 dang;
    f32 len;
    f32 pos[3];
    s32 dir[4];
} Obj_b712_01E01560;

#pragma optimization_level 1

static s32 func_01E01560_b712(Obj_b712_01E01560 *obj, s32 ot, s32 n) {
    extern Tex_b712_01E01560 D_01E03230_b712[];
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_00101940(void *, void *);
    extern f32 func_0020D0E0(void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002086D0(void *, u64);
    extern void func_001020B0();
    extern void func_0020C630(void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208700(void *, s32, s32);
    extern void func_002075F0(void *, s32, s32);
    f32 mat2[16];
    f32 mat[16];
    Tex_b712_01E01560 t;
    Vec4f pts[9];
    Xyz_b712_01E01560 row[9];
    s32 vis[9];
    f32 dep[9];
    f32 rm[16];
    s32 rot[4];
    Vec4f v;
    Vec4f d;
    Vec4f a;
    Vec4f b;
    Pkt_b712_01E01560 pkt;
    Xyz_b712_01E01560 prev;
    f32 depth;
    Obj_b712_01E01560 *o;
    s32 i;
    s32 h;
    s32 pon;
    s32 on;
    s32 k;
    s32 j;
    s32 ncol;
    s32 nrow;
    f32 pdep;
    f32 ang;
    f32 an;
    f32 du;
    f32 dv;
    f32 v0;
    f32 u0;
    f32 u1;
    f32 u2;
    f32 v1;
    f32 v2;

    o = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            o++;
        }
        if (func_00101AF0(o) == 0) {
            continue;
        }
        if (o->flags & 2) {
            h = func_00202BF0(5, o->tex);
        } else {
            h = func_00202BF0(D_01E03230_b712[o->tex].id, D_01E03230_b712[o->tex].kind);
        }
        o->ang += o->dang;
        o->rot += o->drot;
        ang = 90.0f - o->ang;
        if (ang < 0.0f) {
            ang += 360.0f;
        }
        if (o->ncol >= 9 || o->nrow >= 9) {
            continue;
        }
        ncol = o->ncol;
        nrow = o->nrow;
        if (o->flags & 1) {
            o->b5 = 1;
            o->joint = o->jA;
            func_00101BA0(o, &a);
            o->joint = o->jB;
            func_00101BA0(o, &b);
            d.x = b.x - a.x;
            d.y = b.y - a.y;
            d.z = b.z - a.z;
            func_00101940(&d, o->dir);
            d.x *= o->scale;
            d.y *= o->scale;
            d.z *= o->scale;
            o->len = func_0020D0E0(&d);
            o->pos[0] = a.x;
            o->pos[1] = a.y;
            o->pos[2] = a.z;
        }
        d.x = o->pos[0];
        d.y = o->pos[1];
        d.z = o->pos[2];
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, o->dir, &d);
        func_0020BC00(mat, mat2);
        for (j = 0; j < ncol + 1; j++) {
            an = ang + o->astep * j;
            if (!(an <= 90.0f) && an < 180.0f) {
                an = 90.0f;
            }
            pts[j].x = o->len * func_001A6898(3.1415927f * an / 180.0f);
            pts[j].y = o->len * func_001A6A88(3.1415927f * an / 180.0f);
            pts[j].z = 0.0f;
            if (an == 90.0f) {
                ncol = j;
                break;
            }
        }
        ((Hdr_b712_01E01560 *)(s32)&pkt)->count = 0x34;
        ((Hdr_b712_01E01560 *)(s32)&pkt)->tag = 0xC;
        ((Hdr_b712_01E01560 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Hdr_b712_01E01560 *)(s32)&pkt)->pad = 0;
        func_002086D0(&pkt, 0x48);
        if (o->cur < 0x10) {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = o->cur * 8;
        } else {
            pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = 0x80;
        }
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g =
            pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = 0x80;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (o->flags & 4) {
            o->frame = (o->frame + 1) & 7;
        }
        t.b5 = o->bA;
        func_001020B0(&t, o->frame, o->bF);
        du = 16.0f * ((f32)(t.w[3] - t.w[2]) / (f32)o->ncol);
        dv = 16.0f * ((f32)(t.w[1] - t.w[0]) / (f32)o->nrow);
        v0 = 16.0f * (f32)t.w[0];
        u0 = 16.0f * (f32)t.w[2];
        rot[2] = 0;
        rot[0] = 0;
        for (k = 0; k < nrow + 1; k++) {
            rot[1] = (s32)(182.04f * (o->rot + k * o->rstep));
            func_0020C630(rm, rot);
            for (j = 0; j < ncol + 1; j++) {
                func_0020CDD0(&v, rm, &pts[j]);
                on = func_00205440(&v, mat, &pkt.v[0].xyz, &depth);
                while (k != 0 && j != 0) {
                    if (on == 0 || pon == 0 || vis[j] == 0 || vis[j - 1] == 0) {
                        break;
                    }
                    u1 = u0 + (j - 1) * du;
                    u2 = u0 + j * du;
                    v1 = v0 + (k - 1) * dv;
                    v2 = v0 + k * dv;
                    ((Hdr_b712_01E01560 *)(s32)&pkt)->count |= 0x800;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[0].uv)->u = (u32)v2;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[0].uv)->v = (u32)u2;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[1].uv)->u = (u32)v1;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[1].uv)->v = (u32)u2;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[2].uv)->u = (u32)v2;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[2].uv)->v = (u32)u1;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[3].uv)->u = (u32)v1;
                    ((Uv_b712_01E01560 *)(s32)&pkt.v[3].uv)->v = (u32)u1;
                    func_00208700(&pkt, h, 1);
                    pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                    pkt.v[1].xyz = row[j];
                    pkt.v[2].xyz = prev;
                    pkt.v[3].xyz = row[j - 1];
                    func_002075F0(&pkt, ot, (u32)((depth + pdep + dep[j] + dep[j - 1]) / 4.0f));
                    break;
                }
                if (j != 0) {
                    row[j - 1] = prev;
                    dep[j - 1] = pdep;
                    vis[j - 1] = pon;
                }
                prev = pkt.v[0].xyz;
                pdep = depth;
                pon = on;
            }
            row[j - 1] = pkt.v[0].xyz;
            dep[j - 1] = depth;
            vis[j - 1] = on;
        }
    }
    return 1;
}

#pragma optimization_level reset


/* shape b712:01E02010 (b712), 1140 insns, 1 copy (-O1,p): b712 scene manager: setup clears the scene, takes both
   units and two models, fills the 256-entry table; then a frame timer sets the glow at frames 66 and 292, spawns
   rising dust and a pulsing camera colour over 112..312, two waves of ShFx_Obr rings over 140..284 and 292..332, more
   dust at the target over 292..364, steps the emitter, wave, glow, dust and rings, and returns 8 / 6 / 1 / 3 at
   frames 400 / 292..340 / 282 / 341 */

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 b4;
    u8 pad5[3];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 bD;
    u8 bE;
    u8 bF;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 x, y, z;
    s32 w3C;
    s32 w40;
    s32 w44;
    u8 pad48[4];
} Obr_b712_01E02010;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    u8 pad14[0x18];
    u8 cam[0x14];
    Obj_b002_01E00080 emit;
    u8 pad94[0xC];
    s16 wv[2];
    u8 padA4[4];
    Afx_b011_01E02AD0 afx;
    Obj_b712_01E00FD0 dust[0xB4];
    Obr_b712_01E02010 obr[0x50];
    u8 tbl[0x100];
    u8 pad3018[8];
} Scene_b712_01E02010;

#pragma optimization_level 1

static s32 func_01E02010_b712(Scene_b712_01E02010 *g, s32 code) {
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
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern void func_001031C0(void *, u16);
    extern s32 func_01E01560_b712();
    s32 ot;
    Vec4f v;
    Vec4f w;
    u8 c0[4];
    u8 c1[4];
    s32 i;
    s32 k;
    s32 n;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x3020);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 1, 1);
        g->m1 = func_001F5560(g->unitA, 0x58, 0);
        g->wv[0] = 0x55;
        g->wv[1] = 0x18A;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x42:
        func_00101AD0(&g->afx, 0x16, 0, 0xFF);
        func_001F5620(g->unitA, g->m1, &g->afx.pos);
        g->afx.r2 = g->afx.g2 = g->afx.b2 = 0x80;
        g->afx.a2 = 0x40;
        g->afx.r = g->afx.g = g->afx.b = 0x80;
        g->afx.a = 0x70;
        g->afx.size = 0xC;
        g->afx.blend = 1;
        g->afx.mask = 0xFF;
        break;
    case 0x55:
        break;
    case 0x124:
        func_00101AD0(&g->afx, 0x34, 0, 0xFF);
        g->afx.pos = v;
        g->afx.r2 = g->afx.g2 = g->afx.b2 = 0x80;
        g->afx.a2 = 0x60;
        g->afx.r = g->afx.g = g->afx.b = 0x80;
        g->afx.a = 0x70;
        g->afx.size = 0xC;
        g->afx.blend = 2;
        g->afx.mask = 0xFF;
        break;
    case 0x190:
        return 8;
    }
    if (g->t >= 0x70 && g->t <= 0x138) {
        for (i = 0; i < 2; i++) {
            k = func_00101C30(g->dust, 0x20, 0xB4);
            if (k >= 0) {
                func_00101AD0(&g->dust[k], (u8)(((func_0019A5C8() >> 4) & 7) + 0x20), 0, 0xFF);
                g->dust[k].flags = 1;
                g->dust[k].tex = 0;
                g->dust[k].b9 = 4;
                g->dust[k].bA = 1;
                g->dust[k].bB = 2;
                g->dust[k].size = 35.0f;
                g->dust[k].vy = 1.2f + (f32)((func_0019A5C8() >> 4) % 40 - 20) / 100.0f;
                func_001F53C0(1, g->unitA, &w);
                g->dust[k].x = w.x + (f32)((func_0019A5C8() >> 4) % 5800 - 2900) / 100.0f;
                g->dust[k].y = w.y + (f32)((func_0019A5C8() >> 4) % 1200 - 600) / 100.0f;
                g->dust[k].z = w.z + (f32)((func_0019A5C8() >> 4) % 5800 - 2900) / 100.0f;
            }
        }
        c0[2] = c1[2] = 0x80;
        c0[1] = c1[1] = 0x40;
        c0[0] = c1[0] = 0x10;
        switch ((g->t - 0x70) & 0xF) {
        case 0:
            c0[3] = c1[3] = 0;
            break;
        case 1:
        case 15:
            c0[3] = c1[3] = 0x20;
            break;
        case 2:
        case 14:
            c0[3] = c1[3] = 0x40;
            break;
        case 3:
        case 13:
            c0[3] = c1[3] = 0x60;
            break;
        case 4:
        case 12:
            c0[3] = c1[3] = 0x80;
            break;
        case 5:
        case 11:
            c0[3] = c1[3] = 0xA0;
            break;
        case 6:
        case 10:
            c0[3] = c1[3] = 0xC0;
            break;
        case 7:
        case 9:
            c0[3] = c1[3] = 0xE0;
            break;
        case 8:
            c0[3] = c1[3] = 0xFF;
            break;
        }
        func_001F71A0(g->unitA, 1, 1, c0, c1, 1);
    }
    if (g->t >= 0x8C && g->t <= 0x11C) {
        for (i = 0; i < 3; i++) {
            k = func_00101C30(g->obr, 0x4C, 0x50);
            if (k >= 0) {
                func_00101AD0(&g->obr[k], (u8)(((func_0019A5C8() >> 4) & 3) + 0x14), 0, 0xFF);
                g->obr[k].b4 = 3;
                g->obr[k].b8 = 1;
                g->obr[k].b9 = (func_0019A5C8() >> 4) & 7;
                g->obr[k].bA = 2;
                g->obr[k].bD = g->m0;
                g->obr[k].bE = g->m1;
                g->obr[k].bF = 3;
                g->obr[k].f10 = 1.4f;
                g->obr[k].f1C = 180.0f + (f32)((func_0019A5C8() >> 4) % 180 * 200 - 18000) / 100.0f;
                g->obr[k].f20 = 0.0f;
                g->obr[k].f24 = 0.0f;
                if (i != 0) {
                    g->obr[k].bB = ((func_0019A5C8() >> 4) & 3) + 3;
                    g->obr[k].bC = ((func_0019A5C8() >> 4) & 3) + 3;
                    g->obr[k].f14 = 13.0f;
                    g->obr[k].f18 = 15.0f;
                    g->obr[k].f28 = 6.0f;
                } else {
                    g->obr[k].bB = ((func_0019A5C8() >> 4) & 3) + 4;
                    g->obr[k].bC = 1;
                    g->obr[k].f14 = 13.0f;
                    g->obr[k].f18 = 8.0f;
                    g->obr[k].f28 = 8.0f;
                }
            }
        }
    }
    if (g->t >= 0x124 && g->t <= 0x14C) {
        for (i = 0; i < 2; i++) {
            k = func_00101C30(g->obr, 0x4C, 0x50);
            if (k >= 0) {
                func_00101AD0(&g->obr[k], (u8)(((func_0019A5C8() >> 4) & 3) + 0x18), 0, 0xFF);
                g->obr[k].b4 = 6;
                g->obr[k].b8 = 1;
                g->obr[k].b9 = (func_0019A5C8() >> 4) & 7;
                g->obr[k].bA = 2;
                g->obr[k].bF = 3;
                g->obr[k].f1C = 180.0f + (f32)((func_0019A5C8() >> 4) % 180 * 200 - 18000) / 100.0f;
                g->obr[k].f20 = 0.0f;
                g->obr[k].f24 = 30.0f;
                g->obr[k].bB = ((func_0019A5C8() >> 4) & 3) + 5;
                g->obr[k].bC = ((func_0019A5C8() >> 4) & 3) + 3;
                g->obr[k].f14 = 16.0f;
                g->obr[k].f18 = 15.0f;
                g->obr[k].f28 = 5.0f;
                g->obr[k].x = v.x;
                g->obr[k].y = v.y;
                g->obr[k].z = v.z;
                g->obr[k].f2C = v.y;
                g->obr[k].w3C = 0x8000;
                g->obr[k].w44 = 0;
                g->obr[k].w40 = 0;
            }
        }
    }
    if (g->t >= 0x124 && g->t <= 0x16C) {
        for (i = 0; i < 7; i++) {
            k = func_00101C30(g->dust, 0x20, 0xB4);
            if (k >= 0) {
                func_00101AD0(&g->dust[k], (u8)(((func_0019A5C8() >> 4) & 7) + 0x16), 0, 0xFF);
                g->dust[k].flags = 1;
                g->dust[k].tex = 0;
                g->dust[k].b9 = 4;
                g->dust[k].bA = 1;
                g->dust[k].bB = 2;
                g->dust[k].size = 30.0f + (f32)((func_0019A5C8() >> 4) % 10 * 200 - 1000) / 100.0f;
                g->dust[k].vy = 3.4f + (f32)((func_0019A5C8() >> 4) % 2 * 200 - 200) / 100.0f;
                n = (s32)(v.y / 2.0f);
                g->dust[k].x = v.x + (f32)((func_0019A5C8() >> 4) % n * 200 - (n * 200 >> 1)) / 100.0f;
                g->dust[k].y = (f32)((func_0019A5C8() >> 4) % 1200 - 600) / 100.0f;
                g->dust[k].z = v.z + (f32)((func_0019A5C8() >> 4) % n * 200 - (n * 200 >> 1)) / 100.0f;
            }
        }
    }
    func_01E00080_b712(&g->emit);
    func_001031C0(g->wv, g->t);
    func_01E00440_b712(&g->afx, ot, 1);
    func_01E00FD0_b712(g->dust, ot, 0xB4);
    func_01E01560_b712(g->obr, ot, 0x50);
    if (g->t >= 0x124 && g->t <= 0x154) {
        return 6;
    }
    switch (g->t) {
    case 0x11A:
        return 1;
    case 0x155:
        return 3;
    }
    return 0;
}
#pragma optimization_level reset
