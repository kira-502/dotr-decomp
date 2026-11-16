#include "common.h"

/* shape b617:01E003A0 (ShFx_Phantom), 1818 insns, 1 copy: ShFx_Phantom: n phantom emitters (0x28 bytes): projects
   each, glow alpha from four sines of the age; state 1 grows a strip quad, 3 (after a delay) splits it into two
   halves fading out, 2 draws four quarter quads around a swinging centre; then two ghost layers whose UV row cycles
   with the age; best draft, case 1's u0/u1 temps swapped (18 words) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b617_01E003A0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad;
} Uv_b617_01E003A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Uv_b617_01E003A0 uv;
    Xyz_b617_01E003A0 xyz;
} Vtx_b617_01E003A0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b617_01E003A0 v[4];
    u8 tail[0x20];
} Pkt_b617_01E003A0;

typedef struct {
    f32 x, y, z, w;
} V4_b617_01E003A0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 span;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 tex[3];
    u8 state;
    u8 timer;
    u8 delay;
    u8 padE;
    u8 k;
    f32 size;
    u8 b, g, r;
    u8 pad17;
    V4_b617_01E003A0 pos;
} Ent_b617_01E003A0;

typedef struct {
    u8 uv[10][4];
} Tbl_b617_01E003A0;

static s32 func_01E003A0_b617(Ent_b617_01E003A0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern Tbl_b617_01E003A0 D_01E06D80_b617;
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern s32 func_00101600(void *);
    Ent_b617_01E003A0 *e = arg0;
    f32 mat[16];
    Tbl_b617_01E003A0 tbl = D_01E06D80_b617;
    Pkt_b617_01E003A0 pkt;
    Xyz_b617_01E003A0 xy;
    f32 depth;
    u8 c[4];
    s32 i;
    s32 j;
    s32 off;
    s32 u0;
    s32 u1;
    s32 age;
    s32 tex0;
    s32 tex1;
    s32 tex2;
    s32 v1;
    s32 v0;
    s32 a;
    s32 b;
    s32 cc;
    s32 mv;
    s32 k;
    s32 d;
    s32 ku;
    f32 r;
    f32 t;
    f32 p;
    f32 q;
    f32 w;
    f32 h;
    f32 ang;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->state == 0 || e->state > 3) {
            e->life = 0;
            continue;
        }
        tex0 = func_00202BF0(5, e->tex[0]);
        tex1 = func_00202BF0(5, e->tex[1]);
        tex2 = func_00202BF0(5, e->tex[2]);
        func_0020EB40(mat);
        ((Pkt_b617_01E003A0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b617_01E003A0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b617_01E003A0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b617_01E003A0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        age = e->span - e->life;
        for (j = 0; j < 4; j++) {
            c[j] = (s32)(64.0f * func_001A6A88(3.1415927f * (90.0f * j + 10.0f * age) / 180.0f)) + 0x40;
        }
        off = 0;
        if (func_00205440(&e->pos, mat, &xy, &depth) == 0) {
            off = 1;
        }
        if (func_00101600(&xy) == 0) {
            off = 1;
        }
        r = e->size / (depth / 256.0f);
        pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
        if (e->flags & 0x80) {
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
            depth = 0.0f;
        } else {
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xy.z;
        }
        ((Pkt_b617_01E003A0 *)(s32)&pkt)->count |= 0x800;
        func_002086D0(&pkt, 0x48);
        switch (e->state) {
        case 1:
            if (e->timer == 0x1F) {
                e->state++;
            }
            e->timer++;
            if (off == 0) {
                pkt.v[3].a = pkt.v[1].a = pkt.v[2].a = pkt.v[0].a = e->timer * 4;
                u0 = tbl.uv[8][0];
                u1 = tbl.uv[8][1];
                v0 = tbl.uv[8][2];
                v1 = (v0 + e->timer) * 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->u = u0 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->v = v0 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->u = u1 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->v = v0 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->u = u0 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->v = v1 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->u = u1 << 4;
                ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->v = v1 << 4;
                func_00208700(&pkt, (void *)tex0, 1);
                if (e->flags & 1) {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x + r);
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x - r);
                } else {
                    pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x - r);
                    pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x + r);
                }
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xy.y + 2.0f * r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(pkt.v[3].xyz.y - r * (v1 - v0) / 32.0f);
                func_002075F0(&pkt, ot, (u32)depth);
            }
            break;
        case 3:
            if (e->delay == 0) {
                if (e->timer == 0x17) {
                    e->state = 0;
                }
                e->timer++;
                if (off == 0) {
                    a = tbl.uv[9][0];
                    b = tbl.uv[9][1];
                    cc = tbl.uv[9][3];
                    d = tbl.uv[9][2];
                    k = (cc - d) >> 1;
                    t = r / 32.0f * e->timer;
                    if (e->timer > 16) {
                        p = t;
                        q = t;
                        pkt.v[3].a = pkt.v[2].a = pkt.v[1].a = pkt.v[0].a = (0x18 - e->timer) * 16;
                    } else {
                        p = 0.0f;
                        q = 0.0f;
                        pkt.v[3].a = pkt.v[2].a = pkt.v[1].a = pkt.v[0].a = 0x80;
                    }
                    mv = d + k;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->u = a << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->v = d << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->u = b << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->v = d << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->u = a << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->v = mv << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->u = b << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->v = mv << 4;
                    func_00208700(&pkt, (void *)tex1, 1);
                    if (e->flags & 1) {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(t + (xy.x + r) - q);
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(q + (t + (xy.x - r)));
                    } else {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(q + (xy.x - r - t));
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x + r - t - q);
                    }
                    pkt.v[2].xyz.y = pkt.v[3].xyz.y = xy.y;
                    w = r * (b - a) / 32.0f;
                    pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(pkt.v[3].xyz.y - w - p);
                    func_002075F0(&pkt, ot, (u32)depth);
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->u = a << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->v = (d + k) << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->u = b << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->v = (d + k) << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->u = a << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->v = cc << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->u = b << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->v = cc << 4;
                    func_00208700(&pkt, (void *)tex1, 1);
                    if (e->flags & 1) {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x + r - t - q);
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(q + (xy.x - r - t));
                    } else {
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(q + (t + (xy.x - r)));
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(t + (xy.x + r) - q);
                    }
                    pkt.v[0].xyz.y = pkt.v[1].xyz.y = xy.y;
                    pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(p + (pkt.v[1].xyz.y + w));
                    func_002075F0(&pkt, ot, (u32)depth);
                }
                break;
            }
            e->delay--;
        case 2:
            if (off == 0) {
                a = tbl.uv[8][0];
                b = tbl.uv[8][1];
                cc = tbl.uv[8][2];
                d = tbl.uv[8][3];
                ku = (b - a) >> 1;
                k = (d - cc) >> 1;
                ang = 3.1415927f * (90.0f + age * e->k) / 180.0f;
                p = r / 4.0f * func_001A6A88(ang);
                q = r / 4.0f * func_001A6898(ang);
                h = 2.0f * r;
                for (j = 0; j < 4; j++) {
                    switch (j) {
                    case 0:
                        u0 = a;
                        u1 = a + ku;
                        v0 = cc;
                        v1 = cc + k;
                        if (e->flags & 1) {
                            pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x + r);
                        } else {
                            pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x - r);
                        }
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy.x;
                        pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xy.y - h);
                        pkt.v[2].xyz.y = pkt.v[3].xyz.y = xy.y;
                        pkt.v[3].xyz.x = (u32)(pkt.v[3].xyz.x + p);
                        pkt.v[3].xyz.y = (u32)(pkt.v[3].xyz.y + q);
                        pkt.v[0].a = c[0];
                        pkt.v[1].a = (c[0] + c[1]) >> 1;
                        pkt.v[2].a = (c[0] + c[2]) >> 1;
                        pkt.v[3].a = 0x80;
                        break;
                    case 1:
                        u0 = a + ku;
                        u1 = b;
                        v0 = cc;
                        v1 = cc + k;
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy.x;
                        if (e->flags & 1) {
                            pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x - r);
                        } else {
                            pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x + r);
                        }
                        pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xy.y - h);
                        pkt.v[2].xyz.y = pkt.v[3].xyz.y = xy.y;
                        pkt.v[2].xyz.x = (u32)(pkt.v[2].xyz.x + p);
                        pkt.v[2].xyz.y = (u32)(pkt.v[2].xyz.y + q);
                        pkt.v[1].a = c[1];
                        pkt.v[0].a = (c[0] + c[1]) >> 1;
                        pkt.v[3].a = (c[0] + c[3]) >> 1;
                        pkt.v[2].a = 0x80;
                        break;
                    case 2:
                        u0 = a;
                        u1 = a + ku;
                        v0 = cc + k;
                        v1 = d;
                        if (e->flags & 1) {
                            pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x + r);
                        } else {
                            pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x - r);
                        }
                        pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy.x;
                        pkt.v[0].xyz.y = pkt.v[1].xyz.y = xy.y;
                        pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xy.y + h);
                        pkt.v[1].xyz.x = (u32)(pkt.v[1].xyz.x + p);
                        pkt.v[1].xyz.y = (u32)(pkt.v[1].xyz.y + q);
                        pkt.v[2].a = c[2];
                        pkt.v[0].a = (c[0] + c[2]) >> 1;
                        pkt.v[3].a = (c[2] + c[3]) >> 1;
                        pkt.v[1].a = 0x80;
                        break;
                    case 3:
                        u0 = a + ku;
                        u1 = b;
                        v0 = cc + k;
                        v1 = d;
                        pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy.x;
                        if (e->flags & 1) {
                            pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x - r);
                        } else {
                            pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x + r);
                        }
                        pkt.v[0].xyz.y = pkt.v[1].xyz.y = xy.y;
                        pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xy.y + h);
                        pkt.v[0].xyz.x = (u32)(pkt.v[0].xyz.x + p);
                        pkt.v[0].xyz.y = (u32)(pkt.v[0].xyz.y + q);
                        pkt.v[3].a = c[3];
                        pkt.v[1].a = (c[1] + c[3]) >> 1;
                        pkt.v[2].a = (c[2] + c[3]) >> 1;
                        pkt.v[0].a = 0x80;
                        break;
                    }
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->u = u0 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->v = v0 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->u = u1 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->v = v0 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->u = u0 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->v = v1 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->u = u1 << 4;
                    ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->v = v1 << 4;
                    func_00208700(&pkt, (void *)tex0, 1);
                    func_002075F0(&pkt, ot, (u32)depth);
                }
            }
            break;
        }
        if (e->state != 3 && e->state != 0) {
            pkt.v[0].a = pkt.v[1].a = 0x10;
            pkt.v[2].a = pkt.v[3].a = 0x40;
        } else {
            pkt.v[0].a = pkt.v[1].a = 0x18 - e->timer;
            pkt.v[2].a = pkt.v[3].a = (0x18 - e->timer) * 2;
        }
        func_002086D0(&pkt, 0x48);
        for (j = 0; j < 2; j++) {
            u0 = tbl.uv[((e->span - e->life) + j * 4) >> 3 & 7][0];
            v0 = tbl.uv[((e->span - e->life) + j * 4) >> 3 & 7][2];
            v1 = tbl.uv[((e->span - e->life) + j * 4) >> 3 & 7][3];
            u1 = tbl.uv[((e->span - e->life) + j * 4) >> 3 & 7][1];
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->u = u0 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[0].uv)->v = v0 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->u = u1 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[1].uv)->v = v0 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->u = u0 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[2].uv)->v = v1 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->u = u1 << 4;
            ((Uv_b617_01E003A0 *)(s32)&pkt.v[3].uv)->v = v1 << 4;
            func_00208700(&pkt, (void *)tex2, 1);
            if (e->flags & 1) {
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x + 1.2f * r);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x - 1.2f * r);
            } else {
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xy.x - 1.2f * r);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xy.x + 1.2f * r);
            }
            pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xy.y + 2.4f * r);
            w = r * (v1 - v0) / 32.0f;
            ang = 270.0f + 3.5f * age;
            pkt.v[0].xyz.y = pkt.v[1].xyz.y =
                (u32)(pkt.v[3].xyz.y - 1.6f * w - w * func_001A6A88(3.1415927f * ang / 180.0f));
            func_002075F0(&pkt, ot, (u32)depth);
        }
    }
    return 1;
}
