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

static void func_01E00080_b005(Fx_b005_01E00080 *o) {
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

/* shape b005:01E003A0 (ShFx_Wfade), 310 insns, 1 copy: b029:01E026A0's full-screen fade quad (4 vertices, alpha
   following the emitter's counter), compiled after a one-argument helper (config/mod_warm.txt: b005 1) */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b005_01E003A0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b005_01E003A0;

typedef struct {
    Hdr_b005_01E003A0 h;
    Vtx_b005_01E003A0 v[4];
    u8 tail[8];
} Pkt_b005_01E003A0;

typedef struct {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
} Obj_b005_01E003A0;

static s32 func_01E003A0_b005(Obj_b005_01E003A0 *o, s32 tex, s32 h) {
    Pkt_b005_01E003A0 p __attribute__((aligned(8)));
    s32 d;
    u8 a;
    u8 mode;
    u8 k;
    f32 w;
    f32 mid;
    f32 s;

    if (func_00101AF0(o) == 0) {
        return 0;
    }
    ((Hdr_b005_01E003A0 *)(s32)&p)->count = 0x14;
    ((Hdr_b005_01E003A0 *)(s32)&p)->tag = 8;
    ((Hdr_b005_01E003A0 *)(s32)&p)->regs = 0x41414141;
    ((Hdr_b005_01E003A0 *)(s32)&p)->pad = 0;
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

static s32 func_01E00880_b005(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E04480_b005;
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
    t = D_01E04480_b005;
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

static s32 func_01E012D0_b005(Lbb_b005_01E012D0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

/* shape b005:01E01D10 (ShFx_Ndl), 696 insns, 1 copy (-O3,p): update and draw ribbon emitters (0x68 bytes each, may
   turn toward a target object); each segment is projected and drawn as a quad from the emitter's origin, widened on
   screen; b029:01E02B80 built at -O3 */

static inline f32 rad(f32 d) {
    return 3.1415927f * d / 180.0f;
}

typedef struct Uvs_b005_01E01D10 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b005_01E01D10;

typedef struct Rib_b005_01E01D10 {
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
} Rib_b005_01E01D10;

typedef struct Xyz_b005_01E01D10 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b005_01E01D10;

typedef struct Vtx_b005_01E01D10 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b005_01E01D10 xyz;
} Vtx_b005_01E01D10;

typedef struct Pk_b005_01E01D10 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b005_01E01D10 v[4];
    u8 pad70[0x20];
} Pk_b005_01E01D10;

static inline void b029_01E02B80_tag(Pk_b005_01E01D10 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 3

static s32 func_01E01D10_b005(Rib_b005_01E01D10 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101EE0();
    extern void func_0020C940();
    extern void func_0020BC00();
    extern void func_00101940();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Rib_b005_01E01D10 *p = arg0;
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
    Xyz_b005_01E01D10 s[2];
    f32 v[4];
    Vec4f d;
    Vec4f tgt;
    extern Uvs_b005_01E01D10 D_01E044A0_b005;
    Uvs_b005_01E01D10 tbl = D_01E044A0_b005;
    Uvs_b005_01E01D10 uvs;
    Pk_b005_01E01D10 pk __attribute__((aligned(8)));
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
        b029_01E02B80_tag((Pk_b005_01E01D10 *)(u32)&pk, 0xC, 0x34, ((u64)0x4214 << 32) | 0x21421421);
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

#pragma optimization_level reset

/* shape b005:01E027F0 (ShFx_RingTX), 461 insns, 1 copy (-O3,p): b715:01E003A0 (ShFx_RingTX) at -O3, compiled after
   a one-argument helper (config/mod_warm.txt: b005 1) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b005_01E027F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b005_01E027F0 xyz;
} Vtx_b005_01E027F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b005_01E027F0 v[4];
    u8 tail[0x20];
} Pkt_b005_01E027F0;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b005_01E027F0;

typedef struct {
    u8 b, g, r, a;
} Col_b005_01E027F0;

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
    Col_b005_01E027F0 c0;
    Col_b005_01E027F0 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b005_01E027F0;

#pragma optimization_level 3

static s32 func_01E027F0_b005(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    f32 depth[4];
    Tex_b005_01E027F0 td;
    Pkt_b005_01E027F0 pkt;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b005_01E027F0 *e;
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
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b005_01E027F0 *)(s32)&pkt)->pad = 0;
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

INCLUDE_ASM("asm/nonmatchings/mod/b005", func_01E02F30_b005);

/* shape b005:01E03B90 (b005), 556 insns, 1 copy: the b005 module main: code >= 0 clears the scene, takes both units,
   the camera and two joints; else counts the frame: 26 the flare and the glow emitter, 60 the two balls, 70 the fade,
   four rings, eight smoke puffs and the emitter at the target, 120 ends; on odd frames 28..61 a ribbon; the balls
   follow the joint line; steps every effect; returns 6 on frames 70..98, 1/2 on frames 60/99 */

typedef struct {
    s16 a;
    s16 b;
} Wv_b005_01E03B90;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 b5;
    u8 b6;
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
} Emit_b005_01E03B90;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 pad5[3];
} Fade_b005_01E03B90;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    s8 *tbl;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c20[4];
    u8 c24[4];
    u8 pad28[0x30];
    s32 w58;
    s32 w5C;
    s32 w60;
    u8 pad64[4];
} Rib_b005_01E03B90;

typedef union {
    Vec4f f;
    s32 i[4];
} Rot_b005_01E03B90;

typedef struct {
    u8 life;
    u8 pad1[6];
    u8 seg;
    u8 tex;
    u8 b9;
    u8 mode;
    u8 padB;
    f32 usize;
    f32 vscale;
    f32 r;
    f32 dr;
    u8 c[4];
    Vec4f pos;
    Rot_b005_01E03B90 rot;
    s32 drot[4];
} Lbb_b005_01E03B90;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[2];
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 c24[4];
    u8 c28[4];
    Vec4f pos;
    s32 w3C;
    u8 pad40[0x1C];
} Ring_b005_01E03B90;

typedef struct {
    u8 b0;
    u8 pad1[3];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD[3];
    s8 *tbl;
    f32 f14;
    u8 pad18[4];
    f32 f1C;
    f32 f20;
    u8 c[4];
    Vec4f pos;
    u8 pad38[0x20];
} Smk_b005_01E03B90;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m0;
    s32 m1;
    u8 pad14[0x18];
    u8 cam[0x44];
    Emit_b005_01E03B90 emit;
    Wv_b005_01E03B90 wv;
    Obj_b051_01E003A0 flear;
    Rib_b005_01E03B90 rib[0x3C];
    Fade_b005_01E03B90 fade;
    Lbb_b005_01E03B90 lbb[3];
    Ring_b005_01E03B90 ring[8];
    Smk_b005_01E03B90 smk[10];
    s8 tbl[0x100];
    u8 pad21C8[8];
} Scene_b005_01E03B90;

static s32 func_01E03B90_b005(Scene_b005_01E03B90 *g, s32 code) {
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
    extern void func_00101940(void *, void *);
    extern void func_001031C0(void *, s32);
    extern void func_01E003A0_b005();
    extern void func_01E01D10_b005();
    extern void func_01E027F0_b005();
    extern void func_01E02F30_b005();
    s32 ot;
    Vec4f a;
    Vec4f b;
    Vec4f v;
    Vec4f d;
    Vec4f *p;
    s32 i;
    s32 k;
    s32 j;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x21D0);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m0 = func_001F5560(g->unitA, 1, 1);
        g->m1 = func_001F5560(g->unitA, 0x28, 0);
        g->wv.a = 2;
        g->wv.b = 0x72;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x1A:
        func_00101AD0(&g->flear, 0x2C, 0, 0xFF);
        g->flear.pad5[0] = 1;
        g->flear.pad5[1] = g->m1;
        g->flear.flags = 0x81;
        g->flear.segs = 9;
        g->flear.radius = 180.0f;
        g->flear.grow = 0.0f;
        g->flear.ib = 0xC0;
        g->flear.ig = 0xC0;
        g->flear.ir = 0xC0;
        g->flear.r = 0x20;
        g->flear.g = 0x20;
        g->flear.b = 0x80;
        g->flear.alpha = 0xC0;
        g->flear.org.z = 0.0f;
        g->flear.org.y = 0.0f;
        g->flear.org.x = 0.0f;
        func_00101AD0(&g->emit, 0x2C, 0, 0xFF);
        g->emit.b5 = 1;
        g->emit.b6 = g->m1;
        g->emit.on = 4;
        g->emit.f14 = 1.0f;
        g->emit.f18 = 1.2f;
        g->emit.f1C = 1.4f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 4.0f;
        break;
    case 0x3C:
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->lbb[i], 0xE, 0, 0xFF);
            g->lbb[i].mode = 4;
            g->lbb[i].seg = 9;
            g->lbb[i].tex = 1;
            g->lbb[i].b9 = 2;
            g->lbb[i].usize = 3.0f;
            g->lbb[i].r = 13.0f;
            switch (i) {
            case 0:
                g->lbb[i].vscale = -0.08f;
                g->lbb[i].usize = 2.0f;
                g->lbb[i].drot[2] = 0x80;
                break;
            case 1:
                g->lbb[i].vscale = -0.04f;
                g->lbb[i].usize = 3.0f;
                g->lbb[i].rot.i[2] = 0x8000;
                g->lbb[i].drot[2] = 0x80;
                break;
            }
            g->lbb[i].dr = 0.0f;
            g->lbb[i].c[0] = 0x80;
            g->lbb[i].c[1] = 0x80;
            g->lbb[i].c[2] = 0x80;
            g->lbb[i].c[3] = 0;
        }
        break;
    case 0x46:
        func_00101AD0(&g->fade, 0xC, 0, 0xFF);
        g->fade.on = 1;
        for (j = 0; j < 4; j++) {
            func_00101AD0(&g->ring[j], 0x20, (u8)(j * 2), 0xFF);
            g->ring[j].b4 = 0;
            g->ring[j].b7 = 0x24;
            g->ring[j].bC = 1;
            g->ring[j].b8 = 1;
            g->ring[j].b9 = 2;
            g->ring[j].bA = 6;
            g->ring[j].bB = 0;
            g->ring[j].f10 = 1.0f;
            g->ring[j].f14 = 0.0f;
            g->ring[j].f18 = 2.0f;
            g->ring[j].f1C = 1.0f;
            g->ring[j].f20 = 0.5f;
            g->ring[j].c28[0] = 0x80;
            g->ring[j].c28[1] = 0x80;
            g->ring[j].c28[2] = 0x80;
            g->ring[j].c24[0] = 0x80;
            g->ring[j].c24[1] = 0x80;
            g->ring[j].c24[2] = 0x80;
            g->ring[j].c24[3] = 0;
            g->ring[j].c28[3] = 0x40;
            g->ring[j].pos = v;
            g->ring[j].w3C = 0x4000;
        }
        for (i = 0; i < 8; i++) {
            func_00101AD0(&g->smk[i], 0x20, (u8)i, 0xFF);
            g->smk[i].b0 -= 4;
            g->smk[i].b4 = 0xD;
            g->smk[i].b5 = 0;
            g->smk[i].b8 = 0x32;
            g->smk[i].b9 = i;
            g->smk[i].bA = 0;
            g->smk[i].bC = 2;
            g->smk[i].bB = 2;
            g->smk[i].f1C = 60.0f;
            g->smk[i].f20 = -0.6f;
            g->smk[i].tbl = g->tbl;
            g->smk[i].f14 = 2.0f;
            g->smk[i].c[0] = 0x80;
            g->smk[i].c[1] = 0x80;
            g->smk[i].c[2] = 0x80;
            g->smk[i].c[3] = 0x60;
            switch (i % 3) {
            case 0:
                g->smk[i].c[2] += 0x30;
                break;
            case 1:
                g->smk[i].c[1] += 0x30;
                break;
            case 2:
                g->smk[i].c[0] += 0x30;
                break;
            }
            g->smk[i].pos = v;
        }
        func_00101AD0(&g->emit, 0x20, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.8f;
        g->emit.f18 = 1.8f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 6.0f;
        g->emit.pos = v;
        break;
    case 0x78:
        return 8;
    }
    if (g->t >= 0x1C && g->t < 0x3E && (g->t & 1)) {
        k = func_00101C30(g->rib, 0x68, 0x3C);
        if (k >= 0) {
            func_00101AD0(&g->rib[k], 0x12, 0, 0xFF);
            g->rib[k].b4 = 0x85;
            g->rib[k].b5 = 1;
            g->rib[k].b6 = g->m1;
            g->rib[k].bA = 0;
            g->rib[k].bB = 2;
            g->rib[k].bC = 3;
            g->rib[k].b9 = func_0019A5C8() >> 4;
            g->rib[k].tbl = g->tbl;
            g->rib[k].f18 = 1.0f;
            g->rib[k].c24[0] = 0x80;
            g->rib[k].c24[1] = 0x80;
            g->rib[k].c24[2] = 0x80;
            g->rib[k].c20[0] = 0x80;
            g->rib[k].c20[1] = 0x80;
            g->rib[k].c20[2] = 0x80;
            g->rib[k].c20[3] = 0;
            g->rib[k].c24[3] = 0x30;
            g->rib[k].b8 = 0x12;
            g->rib[k].f14 = 2.5f;
            g->rib[k].f1C = 35.0f;
            g->rib[k].w58 = func_0019A5C8() >> 4 & 0x1FF;
            g->rib[k].w5C = func_0019A5C8() >> 4 & 0x1FF;
            g->rib[k].w60 = func_0019A5C8() >> 4 & 0x1FF;
        }
    }
    if (g->lbb[0].life > 0) {
        if (g->lbb[0].c[3] < 0x80) {
            g->lbb[0].c[3] += 8;
        }
        if (g->lbb[1].c[3] < 0x80) {
            g->lbb[1].c[3] += 8;
        }
        func_001F5620(g->unitA, g->m0, &a);
        func_001F5620(g->unitA, g->m1, p = &b);
        d.x = a.x - p->x;
        d.y = a.y - b.y;
        d.z = a.z - b.z;
        func_00101940(&d, &g->lbb[0].rot);
        g->lbb[1].rot = g->lbb[0].rot;
        g->lbb[1].pos = a;
        g->lbb[0].pos = g->lbb[1].pos;
    }
    func_01E00080_b005((Fx_b005_01E00080 *)&g->emit);
    func_001031C0(&g->wv, g->t);
    func_01E003A0_b005(&g->fade, ot);
    func_01E00880_b005(&g->flear, ot, 1);
    func_01E01D10_b005(g->rib, ot, 0x3C);
    func_01E012D0_b005((Lbb_b005_01E012D0 *)g->lbb, ot, 3);
    func_01E027F0_b005(g->ring, ot, 8);
    func_01E02F30_b005(g->smk, ot, 10);
    if (g->t >= 0x46 && g->t < 0x63) {
        return 6;
    }
    switch (g->t) {
    case 0x3C:
        return 1;
    case 0x63:
        return 2;
    }
    return 0;
}
