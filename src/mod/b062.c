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

static void func_01E00080_b062(Fx_b005_01E00080 *o) {
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

static s32 func_01E003A0_b062(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E07A80_b062;
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
    t = D_01E07A80_b062;
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

/* shape b062:01E00DF0 (ShFx_TraceLZ), 540 insns, 3 copies: draws n trail emitters (0x20 bytes each): for each of up
   to cnt segments (cnt clamped to max - life with flag 2) projects points j and j+1 of e->pts and draws two textured
   quads across them (vertical then horizontal offsets of half-width func_001018E0(size, depth)), alpha faded along
   the trail with flag 4, last segment's tail cleared with flag 8, far z with flag 0x80 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b062_01E00DF0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b062_01E00DF0 xyz;
} Vtx_b062_01E00DF0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b062_01E00DF0 v[4];
    u8 tail[0x20];
} Pkt_b062_01E00DF0;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[2];
    s32 w[4];
} Tex_b062_01E00DF0;

typedef struct {
    f32 x, y, z;
} V3_b062_01E00DF0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
    u8 cnt;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 texidx;
    u8 padD[3];
    V3_b062_01E00DF0 *pts;
    f32 size;
    f32 blink;
    u8 b, g, r, a;
} Emit_b062_01E00DF0;

static s32 func_01E00DF0_b062(Emit_b062_01E00DF0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern void func_0020EB40(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    Emit_b062_01E00DF0 *e;
    s32 i;
    s32 j;
    s32 cnt;
    s32 k;
    s32 texture;
    f32 mat[16];
    f32 pt[4];
    Xyz_b062_01E00DF0 xy[2];
    Tex_b062_01E00DF0 tex;
    Pkt_b062_01E00DF0 pkt __attribute__((aligned(8)));
    f32 dep[2];
    f32 r0;
    f32 r1;
    f32 alpha;
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
        func_0020EB40(mat);
        texture = func_00202BF0(5, e->texkind);
        ((Pkt_b062_01E00DF0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b062_01E00DF0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b062_01E00DF0 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b062_01E00DF0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        tex.page = e->texpage;
        func_001020B0(&tex, e->texidx, e->texmode);
        k = tex.w[1] - tex.w[0];
        tex.w[0] = tex.w[0] + (k >> 1) - 1;
        tex.w[1] = tex.w[1] - (k >> 1) + 1;
        func_00101EE0(&pkt, &tex, texture);
        cnt = e->cnt;
        if ((e->flags & 2) && e->max - e->life < e->cnt) {
            cnt = e->max - e->life;
        }
        for (j = 0; j < cnt; j++) {
            pt[0] = e->pts[j].x;
            pt[1] = e->pts[j].y;
            pt[2] = e->pts[j].z;
            if (func_00205440(pt, mat, &xy[0], &dep[0]) == 0 || func_00101600(&xy[0]) == 0) {
                continue;
            }
            r0 = func_001018E0(e->size, dep[0]);
            pt[0] = e->pts[j + 1].x;
            pt[1] = e->pts[j + 1].y;
            pt[2] = e->pts[j + 1].z;
            if (func_00205440(pt, mat, &xy[1], &dep[1]) == 0 || func_00101600(&xy[1]) == 0) {
                continue;
            }
            r1 = func_001018E0(e->size, dep[1]);
            if (e->life < 8 && !(e->flags & 0x40)) {
                alpha = e->life * (e->a >> 3);
            } else {
                alpha = e->a;
            }
            if ((e->flags & 1) && (e->life & 1)) {
                alpha *= e->blink;
            }
            if (e->flags & 4) {
                step = alpha / cnt;
                k = cnt - j;
                pkt.v[0].a = pkt.v[2].a = (u32)(step * k);
                pkt.v[1].a = pkt.v[3].a = (u32)(step * (k - 1));
            } else {
                pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (u32)alpha;
            }
            if (j == cnt - 1 && (e->flags & 8)) {
                pkt.v[1].a = pkt.v[3].a = 0;
            }
            if (e->flags & 0x80) {
                pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = 0xFFFFFE;
                z = 0.0f;
            } else {
                pkt.v[0].xyz.z = pkt.v[2].xyz.z = xy[0].z;
                pkt.v[1].xyz.z = pkt.v[3].xyz.z = xy[1].z;
                if (dep[0] < dep[1]) {
                    z = dep[0];
                } else {
                    z = dep[1];
                }
            }
            pkt.v[0].xyz.y = (u32)(xy[0].y - r0);
            pkt.v[1].xyz.y = (u32)(xy[1].y - r1);
            pkt.v[2].xyz.y = (u32)(xy[0].y + r0);
            pkt.v[3].xyz.y = (u32)(xy[1].y + r1);
            pkt.v[0].xyz.x = pkt.v[2].xyz.x = xy[0].x;
            pkt.v[1].xyz.x = pkt.v[3].xyz.x = xy[1].x;
            func_002075F0(&pkt, ot, (u32)z);
            pkt.v[0].xyz.x = (u32)(xy[0].x - r0);
            pkt.v[1].xyz.x = (u32)(xy[1].x - r1);
            pkt.v[2].xyz.x = (u32)(xy[0].x + r0);
            pkt.v[3].xyz.x = (u32)(xy[1].x + r1);
            pkt.v[0].xyz.y = pkt.v[2].xyz.y = xy[0].y;
            pkt.v[1].xyz.y = pkt.v[3].xyz.y = xy[1].y;
            func_002075F0(&pkt, ot, (u32)z);
        }
    }
    return 1;
}

/* shape b005:01E012D0 (ShFx_Lbb), 655 insns, 8 copies (-O3,p): draws n ball emitters (0x50 bytes each): a half
   circle of 2*seg+1 points (seg up to 9, radius r grown by dr) turned round y in 4*seg steps as textured quads, with
   optional backface cull, s/t flips by life, blink and end fades */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b005_01E012D0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b005_01E012D0 xyz;
} Vtx_b005_01E012D0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b005_01E012D0 v[4];
    u8 tail[0x20];
} Pkt_b005_01E012D0;

typedef struct {
    u8 b, g, r, a;
} Col_b005_01E012D0;

typedef struct {
    u8 life;
    u8 pad1;
    u8 end;
    u8 pad3;
    u8 flags;
    u8 pad5[2];
    u8 seg;
    u8 tex;
    u8 pad9;
    u8 mode;
    u8 padB;
    f32 usize;
    f32 vscale;
    f32 r;
    f32 dr;
    Col_b005_01E012D0 c;
    Vec4f pos;
    s32 rot[4];
    s32 drot[4];
} Lbb_b005_01E012D0;

#pragma optimization_level 3
/* ot aligned: its spill slot, needed for the match */
static s32 func_01E01660_b062(Lbb_b005_01E012D0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f v[4];
    Vec4f pts[20];
    Xyz_b005_01E012D0 row[20];
    s32 vis[20];
    f32 dep[20];
    f32 rm[16];
    s32 rot[4];
    Pkt_b005_01E012D0 pkt;
    Xyz_b005_01E012D0 prev;
    f32 depth;
    Lbb_b005_01E012D0 *e;
    s32 j;
    s32 m;
    s32 on;
    s32 nseg;
    s32 pon;
    s32 i;
    s32 tex __attribute__((aligned(16)));
    s32 k;
    s32 dang;
    s32 ang;
    f32 step;
    f32 a;
    f32 ustep;
    f32 vstep;
    f32 v0;
    f32 pdep;
    f32 cross;
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
        e->rot[0] += e->drot[0];
        e->rot[1] += e->drot[1];
        e->rot[2] += e->drot[2];
        nseg = e->seg;
        if (nseg > 9) {
            nseg = 9;
        }
        step = 90.0f / nseg;
        func_00101BA0(e, &e->pos);
        func_0020EB40(mat);
        func_0020C940(mat2, NULL, e->rot, &e->pos);
        func_0020BC00(mat, mat2);
        for (m = 1; m < nseg + 1; m++) {
            a = 3.1415927f * (step * m) / 180.0f;
            pts[nseg + m].x = pts[nseg - m].x = e->r * func_001A6898(a);
            pts[nseg + m].y = e->r * func_001A6A88(a);
            pts[nseg - m].y = -pts[nseg + m].y;
            pts[nseg - m].z = 0.0f;
            pts[nseg + m].z = 0.0f;
        }
        pts[nseg].x = e->r;
        pts[nseg].z = 0.0f;
        pts[nseg].y = 0.0f;
        rot[2] = 0;
        rot[0] = 0;
        dang = 0x10000 / (nseg * 4);
        ustep = e->usize / (nseg * 4);
        m = nseg * 2;
        vstep = e->usize / m;
        v0 = e->vscale * (e->end - e->life);
        if (e->mode & 4) {
            m = nseg;
        }
        for (k = 0, ang = 0; k < nseg * 4 + 1; k++) {
            if (k == (nseg * 4)) {
                rot[1] = 0;
            } else {
                rot[1] = ang;
            }
            func_0020C630(rm, rot);
            for (j = 0; j < m + 1; j++) {
                ((Pkt_b005_01E012D0 *)(s32)&pkt)->count = 0x34;
                ((Pkt_b005_01E012D0 *)(s32)&pkt)->tag = 0xC;
                ((Pkt_b005_01E012D0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
                ((Pkt_b005_01E012D0 *)(s32)&pkt)->pad = 0;
                func_0020CDD0(v, rm, &pts[j]);
                on = func_00205440(v, mat, &pkt.v[0].xyz, &depth);
                pkt.v[1].xyz = row[j];
                pkt.v[2].xyz = prev;
                pkt.v[3].xyz = row[j - 1];
                while (k != 0 && j != 0) {
                    if (on == 0 || pon == 0 || vis[j] == 0 || vis[j - 1] == 0) {
                        break;
                    }
                    if (e->mode & 1) {
                        if (j == 1) {
                            cross = (pkt.v[1].xyz.x - pkt.v[0].xyz.x) * (pkt.v[2].xyz.y - pkt.v[0].xyz.y) -
                                    (pkt.v[2].xyz.x - pkt.v[0].xyz.x) * (pkt.v[1].xyz.y - pkt.v[0].xyz.y);
                        } else {
                            cross = (pkt.v[0].xyz.x - pkt.v[2].xyz.x) * (pkt.v[3].xyz.y - pkt.v[2].xyz.y) -
                                    (pkt.v[3].xyz.x - pkt.v[2].xyz.x) * (pkt.v[0].xyz.y - pkt.v[2].xyz.y);
                        }
                        if (!(cross <= 0.0f)) {
                            goto next;
                        }
                    }
                    pkt.v[0].q = 1.0f / depth;
                    pkt.v[1].q = 1.0f / dep[j];
                    pkt.v[2].q = 1.0f / pdep;
                    pkt.v[3].q = 1.0f / dep[j - 1];
                    pkt.v[0].s = ustep * k / depth;
                    pkt.v[0].t = (v0 + vstep * j) / depth;
                    pkt.v[1].s = ustep * (k - 1) / dep[j];
                    pkt.v[1].t = (v0 + vstep * j) / dep[j];
                    pkt.v[2].s = ustep * k / pdep;
                    pkt.v[2].t = (v0 + vstep * (j - 1)) / pdep;
                    pkt.v[3].s = ustep * (k - 1) / dep[j - 1];
                    pkt.v[3].t = (v0 + vstep * (j - 1)) / dep[j - 1];
                    if (e->mode & 8) {
                        switch (e->life & 3) {
                        case 3:
                            pkt.v[0].s = (1.0f - pkt.v[0].s * depth) / depth;
                            pkt.v[1].s = (1.0f - pkt.v[1].s * dep[j]) / dep[j];
                            pkt.v[2].s = (1.0f - pkt.v[2].s * pdep) / pdep;
                            pkt.v[3].s = (1.0f - pkt.v[3].s * dep[j - 1]) / dep[j - 1];
                            break;
                        case 1:
                            pkt.v[0].t = (1.0f - pkt.v[0].t * depth) / depth;
                            pkt.v[1].t = (1.0f - pkt.v[1].t * dep[j]) / dep[j];
                            pkt.v[2].t = (1.0f - pkt.v[2].t * pdep) / pdep;
                            pkt.v[3].t = (1.0f - pkt.v[3].t * dep[j - 1]) / dep[j - 1];
                            break;
                        case 2:
                            pkt.v[0].s = (1.0f - pkt.v[0].s * depth) / depth;
                            pkt.v[1].s = (1.0f - pkt.v[1].s * dep[j]) / dep[j];
                            pkt.v[2].s = (1.0f - pkt.v[2].s * pdep) / pdep;
                            pkt.v[3].s = (1.0f - pkt.v[3].s * dep[j - 1]) / dep[j - 1];
                            pkt.v[0].t = (1.0f - pkt.v[0].t * depth) / depth;
                            pkt.v[1].t = (1.0f - pkt.v[1].t * dep[j]) / dep[j];
                            pkt.v[2].t = (1.0f - pkt.v[2].t * pdep) / pdep;
                            pkt.v[3].t = (1.0f - pkt.v[3].t * dep[j - 1]) / dep[j - 1];
                            break;
                        }
                    }
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
                    if (e->mode & 4) {
                        if (j == nseg - 1) {
                            pkt.v[0].a = pkt.v[1].a = al >> 1;
                        }
                        if (j == nseg) {
                            pkt.v[0].a = pkt.v[1].a = 0;
                            pkt.v[2].a = pkt.v[3].a = al >> 1;
                        }
                    }
                    pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->c.r;
                    pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->c.g;
                    pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->c.b;
                    pkt.v[0].xyz.f = pkt.v[1].xyz.f = pkt.v[2].xyz.f = pkt.v[3].xyz.f = 0;
                    func_00208700(&pkt, (void *)tex, 1);
                    if (e->flags & 0x80) {
                        z = 0.0f;
                    } else {
                        z = (u32)((depth + pdep + dep[j] + dep[j - 1]) / 4.0f);
                    }
                    func_002075F0((s32)&pkt, ot, (u32)z);
                    break;
                }
            next:
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
            vis[j - 1] = on;
            dep[j - 1] = depth;
            ang += dang;
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

static s32 func_01E020A0_b062(Cyl_b062_01E020A0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

static s32 func_01E02A10_b062(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

static s32 func_01E02EF0_b062(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern Uvs_b029_01E02B80 D_01E07AA0_b062;
    Uvs_b029_01E02B80 tbl = D_01E07AA0_b062;
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

static s32 func_01E039D0_b062(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E042E0_b062);

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

static s32 func_01E05220_b062(void *arg0, s32 ot, s32 n) {
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

/* shape b062:01E05A10, 104 insns: places the 30 ring pieces: for each live piece (flagged when under 4) takes its matrix, a
   radius of (level - 4) times its scale (not below 0) and an angle of 45 per index plus 16 per step, and sets its position to
   the centre plus the turned offset */

typedef struct {
    u8 n;
    u8 pad1;
    u8 step;
    u8 pad3;
    u8 flags;
    u8 pad5[0x33];
    f32 x, y, z;
} Piece_b062_01E05A10;

typedef struct {
    u8 m[0xC];
} Mtx_b062_01E05A10;

typedef struct {
    u8 pad0[0x60];
    f32 cx, cy, cz;
    u8 pad6C[0x6064 - 0x6C];
    Piece_b062_01E05A10 pieces[30];
    u8 pad[0x775C - 0x6064 - 30 * 0x44];
    Mtx_b062_01E05A10 mats[30];
    f32 scale[30];
} Scene_b062_01E05A10;

static void func_01E05A10_b062(Scene_b062_01E05A10 *s) {
    extern void func_00101A00(void *, void *);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_0020CDD0(void *, void *, void *);
    Vec4f v;
    Vec4f out;
    f32 mtx[16];
    f32 r;
    f32 a;
    s32 d;
    s32 i;

    for (i = 0; i < 0x1E; i++) {
        if (s->pieces[i].n != 0) {
            if (s->pieces[i].n < 4) {
                s->pieces[i].flags |= 8;
            }
            func_00101A00(&s->mats[i], mtx);
            d = s->pieces[i].step - s->pieces[i].n;
            r = (f32)(s->pieces[i].n - 4) * s->scale[i];
            if (r < 0.0f) {
                r = 0.0f;
            }
            a = (3.1415927f * (45.0f * i + 16.0f * d)) / 180.0f;
            v.x = r * func_001A6898(a);
            v.z = 0.0f;
            v.y = r * func_001A6A88(a);
            func_0020CDD0(&out, mtx, &v);
            s->pieces[i].x = s->cx + out.x;
            s->pieces[i].y = s->cy + out.y;
            s->pieces[i].z = s->cz + out.z;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b062", func_01E05BB0_b062);
