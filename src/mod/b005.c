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

INCLUDE_ASM("asm/nonmatchings/mod/b005", func_01E003A0_b005);

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

INCLUDE_ASM("asm/nonmatchings/mod/b005", func_01E01D10_b005);

INCLUDE_ASM("asm/nonmatchings/mod/b005", func_01E027F0_b005);

INCLUDE_ASM("asm/nonmatchings/mod/b005", func_01E02F30_b005);

INCLUDE_ASM("asm/nonmatchings/mod/b005", func_01E03B90_b005);
