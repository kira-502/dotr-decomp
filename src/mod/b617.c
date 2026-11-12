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

INCLUDE_ASM("asm/nonmatchings/mod/b617", func_01E02010_b617);

INCLUDE_ASM("asm/nonmatchings/mod/b617", func_01E02870_b617);

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

INCLUDE_ASM("asm/nonmatchings/mod/b617", func_01E04230_b617);

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

INCLUDE_ASM("asm/nonmatchings/mod/b617", func_01E05340_b617);

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
