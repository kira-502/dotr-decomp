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

static void func_01E00080_b844(Obj_b010_01E00080 *o) {
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

static s32 func_01E00410_b844(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

static s32 func_01E01400_b844(Obj_b035_01E00410 *obj, s32 tex, s32 n) {
    extern Tex_b035_01E00410 D_01E03980_b844;
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
    t = D_01E03980_b844;
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

extern Tex_b532_01E00080 D_01E039A0_b844;

#pragma optimization_level 2

/* target aligned: its spill slot, needed for the match */
static s32 func_01E01F80_b844(Ray_b532_01E00080 *obj, s32 target __attribute__((aligned(8))), s32 count) {
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
    tex0 = D_01E039A0_b844;
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

/* shape b844:01E02B10 (b844), 898 insns, 1 copy (-O2,p): the b844 module main (b387:01E04490's -O2 skeleton): frame
   40 a flare on the joint, 81/89/110 a row of four rings between two joints, 198 a big flare at the target, frames
   198..225 a needle every other frame, 198..231 two falling comets per side; returns 6 on frames 198..226, 1/2 on
   188/227 */

typedef struct {
    f32 x, y, z;
} Vec3_b844_01E02B10;

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
    V4_b035_01E00410 pos;
    V4_b035_01E00410 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b844_01E02B10;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[7];
    u8 pad28[4];
    u8 cam[0x14];
    Obj_b010_01E00080 emit;
    u8 pad94[0xC];
    s16 wv[2];
    Obj_b035_01E00410 flear[5];
    Ray_b844_01E02B10 ray[0x3C];
    Obj_b035_01E00410 ring[3][4];
    Comet_b387_01E00410 lz1[0x1E];
    Comet_b387_01E00410 lz2[0x1E];
    Vec3_b844_01E02B10 vel1[0x1E];
    Vec3_b844_01E02B10 vel2[0x1E];
    Part_b387_01E00410 pool1[0xF0];
    Part_b387_01E00410 pool2[0xF0];
    u8 tbl[0x100];
} Scene_b844_01E02B10;

#pragma optimization_level 2

static s32 func_01E02B10_b844(Scene_b844_01E02B10 *g, s32 code) {
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
    extern void func_001031C0(void *, u16);
    extern void func_001F57B0(s32);
    s32 ot;
    V4_b035_01E00410 v;
    Vec4f q[2];
    s32 i;
    s32 k;
    s32 j;
    f32 dx, dy, dz;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x4FD0);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 0x76, 1);
        g->m[1] = func_001F5560(g->unitA, 0x7B, 0);
        g->m[2] = func_001F5560(g->unitA, 0x85, 0);
        g->m[3] = func_001F5560(g->unitA, 0x8C, 0);
        g->m[4] = func_001F5560(g->unitA, 0x7F, 0);
        g->m[5] = func_001F5560(g->unitA, 0x89, 0);
        g->m[6] = func_001F5560(g->unitA, 0x91, 0);
        g->wv[0] = 2;
        g->wv[1] = 0x1A8;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x28:
        func_00101AD0(&g->flear[0], 0x10, 0, 0xFF);
        g->flear[0].pad5[0] = 1;
        g->flear[0].pad5[1] = g->m[0];
        g->flear[0].flags = 0x81;
        g->flear[0].segs = 9;
        g->flear[0].r = 0x80;
        g->flear[0].g = 0;
        g->flear[0].b = 0x60;
        g->flear[0].ir = g->flear[0].ig = g->flear[0].ib = g->flear[0].alpha = 0xC0;
        g->flear[0].radius = 300.0f;
        g->flear[0].grow = 0.0f;
        g->flear[0].width = 0.0f;
        break;
    case 0x51:
    case 0x59:
    case 0x6E:
        switch (g->t) {
        case 0x51:
            k = 0;
            break;
        case 0x59:
            k = 1;
            break;
        case 0x6E:
            k = 2;
            break;
        }
        for (i = 0; i < 4; i++) {
            func_00101AD0(&g->ring[k][i], (u8)(0xF0 - g->t), 0, 0xFF);
            g->ring[k][i].pad5[0] = 0;
            g->ring[k][i].flags = 0x83;
            g->ring[k][i].segs = 9;
            g->ring[k][i].r = 0xA0;
            g->ring[k][i].g = 0x10;
            g->ring[k][i].b = 0x80;
            g->ring[k][i].ir = g->ring[k][i].ig = g->ring[k][i].ib = 0xC0;
            g->ring[k][i].alpha = 0x40;
            g->ring[k][i].radius = 160.0f - 15.0f * i;
            g->ring[k][i].grow = 0.0f;
            g->ring[k][i].width = 0.0f;
        }
        break;
    case 0xC6:
        func_00101AD0(&g->flear[1], 0x34, 0, 0xFF);
        g->flear[1].pad5[0] = 0;
        g->flear[1].flags = 0x83;
        g->flear[1].segs = 9;
        g->flear[1].r = 0x80;
        g->flear[1].g = 0;
        g->flear[1].b = 0x60;
        g->flear[1].ir = g->flear[1].ig = g->flear[1].ib = g->flear[1].alpha = 0xF0;
        g->flear[1].radius = 1500.0f;
        g->flear[1].grow = 0.0f;
        g->flear[1].width = 0.0f;
        g->flear[1].pos = v;
        break;
    case 0x1AE:
        return 8;
    }
    if (g->t > 0x28 && g->flear[0].cur == 0) {
        func_00101AD0(&g->flear[0], 0x10, 0, 0xFF);
        g->flear[0].radius = 380.0f;
        g->flear[0].grow = 0.0f;
    }
    for (j = 0; j < 3; j++) {
        if (g->ring[j][0].cur > 0) {
            func_001F5620(g->unitA, g->m[j + 1], &g->ring[j][0].pos);
            func_001F5620(g->unitA, g->m[j + 4], &g->ring[j][3].pos);
            dx = (g->ring[j][3].pos.x - g->ring[j][0].pos.x) / 4.0f;
            dy = (g->ring[j][3].pos.y - g->ring[j][0].pos.y) / 4.0f;
            dz = (g->ring[j][3].pos.z - g->ring[j][0].pos.z) / 4.0f;
            g->ring[j][1].pos.x = g->ring[j][0].pos.x + dx;
            g->ring[j][1].pos.y = g->ring[j][0].pos.y + dy;
            g->ring[j][1].pos.z = g->ring[j][0].pos.z + dz;
            g->ring[j][2].pos.x = g->ring[j][0].pos.x + 2.0f * dx;
            g->ring[j][2].pos.y = g->ring[j][0].pos.y + 2.0f * dy;
            g->ring[j][2].pos.z = g->ring[j][0].pos.z + 2.0f * dz;
        }
    }
    if (g->t >= 0xC6 && g->t < 0xE2 && (g->t & 1) == 0) {
        for (i = 0; i < 1; i++) {
            k = func_00101C30(g->ray, 0x68, 0x3C);
            if (k >= 0) {
                func_00101AD0(&g->ray[k], 0x18, 0, 0xFF);
                g->ray[k].flags = 0x85;
                g->ray[k].size = 4.0f;
                g->ray[k].width = 80.0f;
                g->ray[k].segments = 0x20;
                g->ray[k].pad05[0] = 0;
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 3;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 1.0f;
                g->ray[k].r0 = g->ray[k].g0 = g->ray[k].b0 = g->ray[k].r1 = g->ray[k].g1 = g->ray[k].b1 = 0x80;
                g->ray[k].a0 = 0x10;
                g->ray[k].a1 = 0x40;
                g->ray[k].spin[0] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].spin[1] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].spin[2] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].pos = v;
            }
        }
    }
    if (g->t >= 0xC6 && g->t < 0xE8) {
        for (i = 0; i < 2; i++) {
            k = func_00101C30(g->lz1, 0x44, 0x1E);
            if (k >= 0) {
                func_00101AD0(&g->lz1[k], 0x18, 0, 0xFF);
                g->lz1[k].follow = 0;
                g->lz1[k].flags = 4;
                g->lz1[k].parts = g->pool1;
                g->lz1[k].type = 0xF0;
                g->lz1[k].count = 7;
                g->lz1[k].texid = 1;
                g->lz1[k].page = 2;
                g->lz1[k].frame = 4;
                g->lz1[k].frame2 = 6;
                g->lz1[k].r = g->lz1[k].g = g->lz1[k].b = g->lz1[k].a = 0x80;
                g->lz1[k].size = 150.0f;
                g->lz1[k].width = 200.0f;
                for (j = 0; j < g->lz1[k].count + 1; j++) {
                    g->lz1[k].slot[j] = -1;
                }
                func_001F5620(g->unitA, g->m[3], &q[0]);
                g->lz1[k].pos[0] = v.x;
                g->lz1[k].pos[1] = v.y;
                g->lz1[k].pos[2] = v.z;
                g->vel1[k].x = (f32)((func_0019A5C8() >> 4) % 600 - 300) / 100.0f;
                g->vel1[k].y = 0.8f + (f32)((func_0019A5C8() >> 4) % 600 - 300) / 100.0f;
                g->vel1[k].z = (f32)((func_0019A5C8() >> 4) % 600 - 300) / 100.0f;
            }
            k = func_00101C30(g->lz2, 0x44, 0x1E);
            if (k >= 0) {
                func_00101AD0(&g->lz2[k], 0x18, 0, 0xFF);
                g->lz2[k].follow = 0;
                g->lz2[k].flags = 4;
                g->lz2[k].parts = g->pool2;
                g->lz2[k].type = 0xF0;
                g->lz2[k].count = 7;
                g->lz2[k].texid = 1;
                g->lz2[k].page = 2;
                g->lz2[k].frame = 4;
                g->lz2[k].frame2 = 6;
                g->lz2[k].r = g->lz2[k].g = g->lz2[k].b = g->lz2[k].a = 0x80;
                g->lz2[k].size = 150.0f;
                g->lz2[k].width = 200.0f;
                for (j = 0; j < g->lz2[k].count + 1; j++) {
                    g->lz2[k].slot[j] = -1;
                }
                func_001F5620(g->unitA, g->m[3], &q[0]);
                g->lz2[k].pos[0] = v.x;
                g->lz2[k].pos[1] = v.y;
                g->lz2[k].pos[2] = v.z;
                g->vel2[k].x = (f32)((func_0019A5C8() >> 4) % 600 - 300) / 100.0f;
                g->vel2[k].y = 0.8f + (f32)((func_0019A5C8() >> 4) % 600 - 300) / 100.0f;
                g->vel2[k].z = (f32)((func_0019A5C8() >> 4) % 600 - 300) / 100.0f;
            }
        }
    }
    for (i = 0; i < 0x1E; i++) {
        if (g->lz1[i].life > 0) {
            g->vel1[i].y -= 0.08f;
            g->lz1[i].pos[0] += g->vel1[i].x;
            g->lz1[i].pos[1] += g->vel1[i].y;
            g->lz1[i].pos[2] += g->vel1[i].z;
        }
        if (g->lz2[i].life > 0) {
            g->vel2[i].y -= 0.08f;
            g->lz2[i].pos[0] += g->vel2[i].x;
            g->lz2[i].pos[1] += g->vel2[i].y;
            g->lz2[i].pos[2] += g->vel2[i].z;
        }
    }
    if (g->t >= 0xC1 && g->t < 0xF6) {
        func_001F57B0(1);
    }
    func_01E00080_b844(&g->emit);
    func_001031C0(g->wv, g->t);
    func_01E00410_b844(g->lz1, ot, 0x1E);
    func_01E00410_b844(g->lz2, ot, 0x1E);
    func_01E01400_b844(g->flear, ot, 5);
    func_01E01400_b844(&g->ring[0][0], ot, 0xC);
    func_01E01F80_b844((Ray_b532_01E00080 *)g->ray, ot, 0x3C);
    if (g->t >= 0xC6 && g->t < 0xE3) {
        return 6;
    }
    switch (g->t) {
    case 0xBC:
        return 1;
    case 0xE3:
        return 2;
    }
    return 0;
}

#pragma optimization_level reset
