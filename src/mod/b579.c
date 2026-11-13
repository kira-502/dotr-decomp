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

static void func_01E00080_b579(Obj_b010_01E00080 *o) {
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

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */
/* OVL_WARM */

/* shape b387:01E00410, 1018 insns, 3 copies: comet emitters (0x44 bytes each): the head position (optionally following the
   owner) is pushed into a ring of pool entries; the history is either used as is (flag 4 of b24) or run through
   the spline; a head sprite is drawn at the first point, then a ribbon of quads between consecutive projected
   points (stopping at the first point that fails to project), widths from the depth, alpha fading along the tail. */

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spline_b387_01E00410;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b387_01E00410;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b387_01E00410 p;
} Vtx_b387_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b387_01E00410 v[4];
    u8 tail[0x20];
} Pkt_b387_01E00410;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    struct {
        u64 tc;
        Xyz_b387_01E00410 p;
    } v[4];
    u8 tail[0x20];
} Spr_b387_01E00410;

typedef struct {
    u8 pad0[5];
    u8 page;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b387_01E00410;

typedef struct {
    u8 life;
    u8 pad1[3];
    f32 x, y, z;
} Part_b387_01E00410;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 mask;
    u8 flags;
    u8 follow;
    u8 pad6[2];
    Part_b387_01E00410 *parts;
    s16 slot[9];
    u8 count;
    u8 texid;
    u8 b20;
    u8 page;
    u8 frame;
    u8 frame2;
    u8 b24;
    u8 pad25[3];
    s32 type;
    f32 size;
    f32 width;
    u8 b, g, r, a;
    f32 pos[3];
} Comet_b387_01E00410;

#pragma optimization_level 2

static s32 func_01E00410_b579(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00101BA0(void *, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101B40(void *, u8, s32);
    extern s32 func_00102550(void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern void func_00101EE0(void *, void *, void *);
    extern void func_002075F0(void *, s32, s32);
    f32 mat[16];
    Spline_b387_01E00410 sp;
    Vec4f t;
    Xyz_b387_01E00410 q[2];
    Tex_b387_01E00410 td;
    Pkt_b387_01E00410 pkt;
    Spr_b387_01E00410 spr;
    f32 dz[2];
    Comet_b387_01E00410 *e;
    Part_b387_01E00410 *pool;
    s32 i;
    s32 k;
    s32 m;
    Part_b387_01E00410 *p;
    void *tex;
    s32 ok;
    s32 pok;
    s32 fr;
    s32 idx;
    s32 dd;
    f32 h;
    f32 pw;
    f32 d;
    f32 al;

    e = arg0;
    pool = e->parts;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Comet_b387_01E00410 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        func_0020EB40(mat);
        if (e->follow != 0) {
            func_00101BA0(e, &t);
            e->pos[0] = t.x;
            e->pos[1] = t.y;
            e->pos[2] = t.z;
        }
        fr = e->mask & (e->max - e->life);
        if (e->life == 0) {
            for (k = 0; k < e->count; k++) {
                p = &pool[e->slot[k]];
                p->life = 0;
                e->slot[k] = -1;
            }
            continue;
        }
        for (k = e->count; k > 0; k--) {
            if (e->slot[k - 1] >= 0) {
                p = &pool[e->slot[k - 1]];
                p->life = e->life;
            }
            if (!(e->flags & 8)) {
                e->slot[k] = e->slot[k - 1];
            }
        }
        if (!(e->flags & 8)) {
            if (e->slot[e->count] >= 0) {
                p = &pool[e->slot[e->count]];
                p->life = 0;
                e->slot[e->count] = -1;
            }
            idx = func_00101C30(pool, 0x10, e->type);
            if (idx >= 0) {
                e->slot[0] = idx;
                p = &pool[e->slot[0]];
                func_00101B40(p, e->life, 0);
                p->x = e->pos[0];
                p->y = e->pos[1];
                p->z = e->pos[2];
            } else {
                e->slot[0] = -1;
            }
        }
        if (e->b24 & 4) {
            m = 0;
            for (k = 0; k < e->count; k++) {
                if (e->slot[k] >= 0) {
                    p = &pool[e->slot[k]];
                    sp.out[k].x = p->x;
                    sp.out[k].y = p->y;
                    sp.out[k].z = p->z;
                    m++;
                }
            }
        } else {
            sp.n = 0;
            for (k = 0; k < e->count; k++) {
                if (e->slot[k] >= 0) {
                    p = &pool[e->slot[k]];
                    sp.x[sp.n] = p->x;
                    sp.y[sp.n] = p->y;
                    sp.z[sp.n] = p->z;
                    sp.n++;
                }
            }
            if (func_00102550(&sp) == 0) {
                continue;
            }
            m = (sp.n - 1) * 4;
        }
        ok = func_00205440(&sp.out[0], mat, &q[1], &dz[1]);
        h = func_001018E0(e->size, dz[1]);
        if (ok != 0) {
            ok = func_00101600(&q[1]);
        }
        if (ok != 0 && !(e->flags & 1)) {
            ((Spr_b387_01E00410 *)(s32)&spr)->count = 0x24;
            ((Spr_b387_01E00410 *)(s32)&spr)->tag = 9;
            ((Spr_b387_01E00410 *)(s32)&spr)->regs = ((u64)4 << 32) | 0x24242421;
            ((Spr_b387_01E00410 *)(s32)&spr)->pad = 0;
            spr.r = e->r;
            spr.g = e->g;
            spr.b = e->b;
            spr.q = 1.0f;
            if (e->flags & 2) {
                dd = fr & 7;
                if (e->life < 7) {
                    dd = 7 - e->life;
                }
            } else {
                dd = e->frame;
            }
            td.page = e->page;
            func_001020B0(&td, dd, e->b20);
            func_00101D20(&spr, &td, tex);
            spr.a = e->a;
            if (!(e->flags & 0x40)) {
                if (e->life < 4) {
                    spr.a = (e->a >> 2) * e->life;
                }
            }
            if (e->flags & 0x80) {
                spr.v[0].p.z = spr.v[1].p.z = spr.v[2].p.z = spr.v[3].p.z = 0xFFFFFE;
                d = 0.0f;
            } else {
                spr.v[0].p.z = spr.v[1].p.z = spr.v[2].p.z = spr.v[3].p.z = q[1].z;
                d = dz[1];
            }
            spr.v[0].p.x = spr.v[2].p.x = q[1].x - h;
            spr.v[1].p.x = spr.v[3].p.x = q[1].x + h;
            spr.v[0].p.y = spr.v[1].p.y = q[1].y - h;
            spr.v[2].p.y = spr.v[3].p.y = q[1].y + h;
            func_002075F0(&spr, ot, (u32)d);
        }
        ((Pkt_b387_01E00410 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b387_01E00410 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b387_01E00410 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b387_01E00410 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        td.page = e->page;
        func_001020B0(&td, e->frame2, e->b20);
        if (e->flags & 4) {
            dd = (td.w - td.u) >> 1;
            td.u = td.u + dd - 1;
            td.w = td.w - dd + 1;
        }
        func_00101EE0(&pkt, &td, tex);
        h = func_001018E0(e->width, dz[1]);
        for (k = 1; k < m - 1; k++) {
            q[0] = q[1];
            dz[0] = dz[1];
            pw = h;
            pok = ok;
            ok = func_00205440(&sp.out[k], mat, &q[1], &dz[1]);
            if (ok != 0) {
                ok = func_00101600(&q[1]);
            }
            if (pok == 0 || ok == 0) {
                break;
            }
                h = func_001018E0(e->width, dz[1]);
                if (e->life < 4 && !(e->flags & 0x40)) {
                    al = (f32)e->life * e->a / 4.0f;
                } else {
                    al = e->a;
                }
                d = al / m;
                pkt.v[0].a = pkt.v[2].a = d * (m - k);
                pkt.v[1].a = pkt.v[3].a = d * (m - k - 1);
                if (k == 1 && (e->b24 & 2)) {
                    pkt.v[0].a = pkt.v[2].a = 0;
                }
                if (e->flags & 0x80) {
                    pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = 0xFFFFFE;
                    d = 0.0f;
                } else {
                    pkt.v[0].p.z = pkt.v[2].p.z = q[0].z;
                    pkt.v[1].p.z = pkt.v[3].p.z = q[1].z;
                    if (dz[0] < dz[1]) {
                        d = dz[0];
                    } else {
                        d = dz[1];
                    }
                }
                pkt.v[0].p.y = q[0].y - pw;
                pkt.v[1].p.y = q[1].y - h;
                pkt.v[2].p.y = q[0].y + pw;
                pkt.v[3].p.y = q[1].y + h;
                pkt.v[0].p.x = pkt.v[2].p.x = q[0].x;
                pkt.v[1].p.x = pkt.v[3].p.x = q[1].x;
                func_002075F0(&pkt, ot, (u32)d);
                pkt.v[0].p.x = q[0].x - pw;
                pkt.v[1].p.x = q[1].x - h;
                pkt.v[2].p.x = q[0].x + pw;
                pkt.v[3].p.x = q[1].x + h;
                pkt.v[0].p.y = pkt.v[2].p.y = q[0].y;
                pkt.v[1].p.y = pkt.v[3].p.y = q[1].y;
                func_002075F0(&pkt, ot, (u32)d);
        }
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

static s32 func_01E01400_b579(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E06080_b579;
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
    t = D_01E06080_b579;
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

extern Tex_b532_01E00080 D_01E060A0_b579;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E01F80_b579(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    tex0 = D_01E060A0_b579;
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

/* OVL_WARM */

/* OVL_CFLAGS: -O2,p -sdatathreshold 0 -relax_pointers */

/* shape b010:01E04D20, 646 insns, 49 copies: update and draw a pool of particles (0x44 bytes each): move,
   floor bounce, colour and frame, project, then one textured sprite whose corners follow the flip bits */

typedef struct Part_b010_01E04D20 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 follow;
    u8 b6[2];
    u8 tex;
    u8 frame;
    u8 anim;
    u8 bB;
    u8 r, g, b, a;
    f32 size;
    f32 grow;
    f32 grav;
    f32 floor;
    f32 pos[3];
    f32 vel[3];
    f32 acc[3];
} Part_b010_01E04D20;

typedef struct Xyz_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b010_01E04D20;

typedef struct Pk_b010_01E04D20 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b010_01E04D20 v[4];
    u64 pad60[3];
} Pk_b010_01E04D20;

typedef struct Buf_b010_01E04D20 {
    u64 tag;
    Pk_b010_01E04D20 pk;
} Buf_b010_01E04D20;

typedef struct Uvs_b010_01E04D20 {
    u8 b0[5];
    u8 b5;
    u8 pad6[0x12];
} Uvs_b010_01E04D20;

typedef struct Scr_b010_01E04D20 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Scr_b010_01E04D20;

static inline void b010_01E04D20_tag(Pk_b010_01E04D20 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 2

static s32 func_01E02B10_b579(Part_b010_01E04D20 *arg0, s32 id, s32 n) {
    extern void func_001020B0();
    extern void func_00101D20();
    extern s32 func_00205440();
    extern void func_00101BA0();
    Part_b010_01E04D20 *p = arg0;
    s32 i;
    s32 tex;
    s32 life;
    s32 frame;
    f32 half;
    f32 zf;
    u16 c;

    f32 m[4][4];
    Vec4f pos;
    Vec4f tmp;
    Uvs_b010_01E04D20 uvs;
    Pk_b010_01E04D20 pk __attribute__((aligned(8)));
    Scr_b010_01E04D20 scr;
    f32 depth;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            p++;
        }
        if (func_00101AF0(p) == 0) {
            continue;
        }
        tex = func_00202BF0(5, p->tex);
        p->vel[0] += p->acc[0];
        p->vel[1] += p->acc[1] + p->grav;
        p->vel[2] += p->acc[2];
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        p->size += p->grow;
        if (p->pos[1] < p->floor) {
            p->pos[1] = p->floor;
            if (p->flags & 2) {
                p->vel[1] = -(0.7f * p->vel[1]);
            }
        }
        if (p->follow != 0) {
            func_00101BA0(p, &tmp);
            p->pos[0] = tmp.x;
            p->pos[1] = tmp.y;
            p->pos[2] = tmp.z;
        }
        pos.x = p->pos[0];
        pos.y = p->pos[1];
        pos.z = p->pos[2];
        func_0020EB40(m);
        ((Pk_b010_01E04D20 *)(u32)&pk)->flags = 0x24;
        ((Pk_b010_01E04D20 *)(u32)&pk)->size = 9;
        ((Pk_b010_01E04D20 *)(u32)&pk)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pk_b010_01E04D20 *)(u32)&pk)->pad4 = 0;
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        life = p->life - p->age;
        frame = p->frame;
        if (p->flags & 1) {
            frame = (u8)func_001022D0(p->anim, life);
            if (p->flags & 4) {
                p->flags &= 0xCF;
                p->flags |= (u8)(((func_0019A5C8() >> 4) & 3) << 4);
            }
        }
        uvs.b5 = p->bB;
        func_001020B0(&uvs, frame, p->anim);
        func_00101D20(&pk, &uvs, tex);
        pk.a = p->a;
        if (!(p->flags & 0x40) && p->age < 0x10) {
            pk.a = (p->a >> 4) * p->age;
        }
        if (func_00205440(&pos, m, &scr, &depth) == 0) {
            continue;
        }
        if (func_00101600(&scr) == 0) {
            continue;
        }
        half = func_001018E0(p->size, depth);
        if (p->flags & 0x80) {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = 0xFFFFFE;
            zf = 0.0f;
        } else {
            pk.v[0].z = pk.v[1].z = pk.v[2].z = pk.v[3].z = scr.z;
            zf = depth;
        }
        switch (p->flags & 0x30) {
        case 0x10:
            c = scr.x;
            pk.v[0].x = pk.v[1].x = (u32)(c - half);
            pk.v[2].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[1].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[2].y = (u32)(c + half);
            break;
        case 0x20:
            c = scr.x;
            pk.v[1].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[2].x = (u32)(c + half);
            c = scr.y;
            pk.v[2].y = pk.v[3].y = (u32)(c - half);
            pk.v[0].y = pk.v[1].y = (u32)(c + half);
            break;
        case 0x30:
            c = scr.x;
            pk.v[2].x = pk.v[3].x = (u32)(c - half);
            pk.v[0].x = pk.v[1].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[2].y = (u32)(c - half);
            pk.v[1].y = pk.v[3].y = (u32)(c + half);
            break;
        default:
            c = scr.x;
            pk.v[0].x = pk.v[2].x = (u32)(c - half);
            pk.v[1].x = pk.v[3].x = (u32)(c + half);
            c = scr.y;
            pk.v[0].y = pk.v[1].y = (u32)(c - half);
            pk.v[2].y = pk.v[3].y = (u32)(c + half);
            break;
        }
        func_002075F0((s32)&pk, id, (u32)(zf));
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

static s32 func_01E03530_b579(Obj_b010_01E05740 *o, s32 tex, s32 h, s32 d) {
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

/* shape b561:01E02A90 (ShFx_RingTX), 505 insns, 16 copies (-O2,p): n ring emitters (0x5C bytes each): an inner and an
   outer circle of up to 36 points (radii growing each frame) joined into textured quads; texture rect from
   func_001020B0, mode 1 = no clamp and s scaled by e->scale, mode 2 = a 1-texel column in the middle; far z with
   flags & 0x80; the source of shape b603:01E039B0, built here at -O2 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b561_01E02A90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b561_01E02A90 xyz;
} Vtx_b561_01E02A90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b561_01E02A90 v[4];
    u8 tail[0x20];
} Pkt_b561_01E02A90;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b561_01E02A90;

typedef struct {
    u8 b, g, r, a;
} Col_b561_01E02A90;

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
    Col_b561_01E02A90 c0;
    Col_b561_01E02A90 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Emit_b561_01E02A90;

#pragma optimization_level 2

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E03A80_b579(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101BA0(void *, void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00102210(s32, f32 *, f32 *);
    f32 mat2[16];
    f32 mat[16];
    Vec4f ring[2][37];
    f32 depth[4];
    Tex_b561_01E02A90 td;
    Pkt_b561_01E02A90 pkt;
    f32 sw;
    f32 sh;
    u8 bl[4];
    Emit_b561_01E02A90 *e;
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
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b561_01E02A90 *)(s32)&pkt)->pad = 0;
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
            {
                s32 h = (td.w - td.u) >> 1; /* through a local: needed for the match */
                td.u += h;
            }
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

/* shape b213:01E00F90 (ShFx_Core01), 644 insns, 28 copies (-O2,p): update and draw spinning 2-D beams (0x50 bytes
   each): move, project, and draw each as two quads per half-turn, alpha and length fading in and out */

#define ABS_b213_01E00F90(x) ((x) >= 0.0f ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b213_01E00F90;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b213_01E00F90;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b213_01E00F90 p;
} Vtx_b213_01E00F90;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b213_01E00F90 v[4];
    u8 tail[0x20];
} Pkt_b213_01E00F90;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[0x13];
} Tex_b213_01E00F90;

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
    Vec_b213_01E00F90 pos;
    Vec_b213_01E00F90 vel;
    Vec_b213_01E00F90 point;
} Beam_b213_01E00F90;

#pragma optimization_level 2

static s32 func_01E04270_b579(void *p, s32 target, s32 count) {
    extern Tex_b213_01E00F90 D_01E060C0_b579;
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_00101AF0(void *);
    extern void func_00101BA0(void *, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, s32, s32, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00101EE0(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    extern void func_002075F0(void *, s32, s32);
    Beam_b213_01E00F90 *o = p;
    s32 i;
    s32 h __attribute__((aligned(16)));
    s32 j;
    u8 k;
    u8 a;
    s32 s;
    f32 zd;
    f32 dx;
    f32 ady;
    f32 dy;
    f32 len;
    f32 r1;
    f32 w;
    f32 t;
    f32 m2[16];
    f32 m1[16];
    Vec_b213_01E00F90 pt;
    Tex_b213_01E00F90 tex;
    Xyz_b213_01E00F90 q;
    Pkt_b213_01E00F90 pkt __attribute__((aligned(8)));
    f32 dep;

    tex = D_01E060C0_b579;
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
        pt = o->point;
        func_00101BA0(o, &o->pos);
        func_0020EB40(m1);
        func_0020C940(m2, 0, 0, &o->pos);
        func_0020BC00(m1, m2);
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b213_01E00F90 *)(s32)&pkt)->pad = 0;
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
        a = o->a;
        s = a >> 3;
        if (o->life >= 8 || (o->flags & 0x40)) {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = a;
        } else {
            pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = s * o->life;
        }
        pkt.v[0].a = 0;
        if (func_00205440(&pt, m1, &q, &dep) == 0 || func_00101600(&q) == 0) {
            continue;
        }
        r1 = func_001018E0(o->len, dep);
        w = func_001018E0(o->width, dep);
        if (o->flags & 0x80) {
            q.z = 0xFFFFFE;
            zd = 0.0f;
        } else {
            zd = dep;
        }
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = q.z;
        pkt.v[0].p.f = pkt.v[1].p.f = pkt.v[2].p.f = pkt.v[3].p.f = 1;
        len = r1;
        if (!(o->flags & 0x40)) {
            if (!(o->flags & 1)) {
                k = o->total - o->life;
                if (k < 8) {
                    len = r1 * (0.125f * k);
                }
            }
            if (o->life < 8) {
                len = r1 * (0.125f * o->life);
            }
        }
        for (j = 0; j < 2; j++) {
            t = 180.0f * j;
            dx = len * func_001A6898(3.1415927f * (o->angle + t) / 180.0f);
            dy = len * func_001A6A88(3.1415927f * (o->angle + t) / 180.0f);
            ady = ABS_b213_01E00F90(dy);
            if (!(ABS_b213_01E00F90(dx) <= ady)) {
                pkt.v[0].p.x = pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[1].p.x = pkt.v[3].p.x = q.x;
                pkt.v[0].p.y = (u32)(q.y + dy - w);
                pkt.v[1].p.y = (u32)(q.y - w);
                pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[3].p.y = q.y;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.y = (u32)(w + (q.y + dy));
                pkt.v[1].p.y = (u32)(q.y + w);
                func_002075F0(&pkt, target, (u32)zd);
            } else {
                pkt.v[0].p.y = pkt.v[2].p.y = (u32)(q.y + dy);
                pkt.v[1].p.y = pkt.v[3].p.y = q.y;
                pkt.v[0].p.x = (u32)(q.x + dx - w);
                pkt.v[1].p.x = (u32)(q.x - w);
                pkt.v[2].p.x = (u32)(q.x + dx);
                pkt.v[3].p.x = q.x;
                func_002075F0(&pkt, target, (u32)zd);
                pkt.v[0].p.x = (u32)(w + (q.x + dx));
                pkt.v[1].p.x = (u32)(q.x + w);
                func_002075F0(&pkt, target, (u32)zd);
            }
        }
    }
    return 1;
}

#pragma optimization_level reset

INCLUDE_ASM("asm/nonmatchings/mod/b579", func_01E04C80_b579);
