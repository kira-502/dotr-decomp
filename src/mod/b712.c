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


INCLUDE_ASM("asm/nonmatchings/mod/b712", func_01E01560_b712);

INCLUDE_ASM("asm/nonmatchings/mod/b712", func_01E02010_b712);
