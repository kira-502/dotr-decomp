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

static void func_01E00080_b379(Fx_b005_01E00080 *o) {
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

static s32 func_01E003A0_b379(Obj_b029_01E026A0 *o, s32 tex, s32 d, s32 h) {
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

static s32 func_01E00880_b379(Rib_b029_01E02B80 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
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
    extern Uvs_b029_01E02B80 D_01E07200_b379;
    Uvs_b029_01E02B80 tbl = D_01E07200_b379;
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

static s32 func_01E01360_b379(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

/* shape b029:01E05AA0 (ShFx_ReqBlur), 286 insns, 10 copies: a flat textured screen quad shown between frames
   start..end, fading in over the first fade frames and out over the last 2 x fade; corners from the object (x16,
   offset to the screen centre). The original's far-depth chain writes corner 1 twice and never corner 2 */

typedef struct {
    u16 start;
    u16 end;
    u8 pad4;
    u8 fade;
    u8 tex;
    u8 pad7;
    f32 level;
    s32 x[4];
    s32 y[4];
    u8 b, g, r;
} Obj_b029_01E05AA0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
} Hdr_b029_01E05AA0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
} Uv_b029_01E05AA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b029_01E05AA0;

typedef struct {
    Hdr_b029_01E05AA0 h;
    struct {
        u8 r, g, b, a;
        f32 q;
        Uv_b029_01E05AA0 uv;
        Xyz_b029_01E05AA0 xyz;
    } v[4];
    u8 tail[0x20];
} Pk_b029_01E05AA0;

typedef struct {
    u8 pad0[5];
    u8 tex;
    u8 pad6[0x12];
} Tex_b029_01E05AA0;

static s32 func_01E01C70_b379(Obj_b029_01E05AA0 *obj, s32 dst, u16 frame) {
    Tex_b029_01E05AA0 tex;
    Pk_b029_01E05AA0 pk __attribute__((aligned(8)));
    u8 o[4];
    u8 a;
    s32 d;

    if (frame >= obj->start && frame <= obj->end) {
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->nreg = 0x34;
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->n = 0xC;
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->pad4 = 0;
        func_002087A0(&pk, 1);
        pk.v[0].r = pk.v[1].r = pk.v[2].r = pk.v[3].r = obj->r;
        pk.v[0].g = pk.v[1].g = pk.v[2].g = pk.v[3].g = obj->g;
        pk.v[0].b = pk.v[1].b = pk.v[2].b = pk.v[3].b = obj->b;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[1].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
        pk.v[0].xyz.f = pk.v[1].xyz.f = pk.v[2].xyz.f = pk.v[3].xyz.f = 0;
        d = frame - obj->start;
        a = obj->fade * 16;
        if (d < obj->fade) {
            a = d * 16;
        }
        if (obj->end - frame < obj->fade * 2) {
            a = (obj->end - frame) * 8;
        }
        pk.v[0].a = pk.v[1].a = pk.v[2].a = pk.v[3].a = a;
        tex.tex = obj->tex;
        func_00101C80(&tex, o);
        func_002086D0(&pk, (s64)o[0] | ((s64)o[1] << 2) | ((s64)o[2] << 4) | ((s64)o[3] << 6));
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->nreg |= 0x800;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[0].uv)->u = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[0].uv)->v = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[1].uv)->u = 0x2800;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[1].uv)->v = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[2].uv)->u = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[2].uv)->v = 0x1C00;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[3].uv)->u = 0x2800;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[3].uv)->v = 0x1C00;
        pk.v[0].xyz.x = (u32)(27648.0f + (f32)(obj->x[0] * 16));
        pk.v[1].xyz.x = (u32)(37888.0f + (f32)(obj->x[1] * 16));
        pk.v[2].xyz.x = (u32)(27648.0f + (f32)(obj->x[2] * 16));
        pk.v[3].xyz.x = (u32)(37888.0f + (f32)(obj->x[3] * 16));
        pk.v[0].xyz.y = (u32)(29184.0f + (f32)(obj->y[0] * 16));
        pk.v[1].xyz.y = (u32)(29184.0f + (f32)(obj->y[1] * 16));
        pk.v[2].xyz.y = (u32)(36352.0f + (f32)(obj->y[2] * 16));
        pk.v[3].xyz.y = (u32)(36352.0f + (f32)(obj->y[3] * 16));
        func_002075F0((s32)&pk, dst, (u32)(obj->level));
    }
    return 1;
}

/* shape b379:01E020F0, 95 insns: if the value lies in [lo, hi] draw a full-screen flat quad (0x6BF8,0x71F8 -
   0x93F8,0x8DF8) in the source colour at the source depth, into a fresh draw buffer and close it */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b379_01E020F0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Xyz_b379_01E020F0 v[2];
    u64 tail;
} Flat_b379_01E020F0;

typedef struct {
    u16 lo;
    u16 hi;
    u8 pad4[4];
    f32 depth;
    u8 b, g, r, a;
} Src_b379_01E020F0;

static s32 func_01E020F0_b379(Src_b379_01E020F0 *src, s32 arg1, s32 v) {
    extern s32 func_00207F60(void);
    extern u64 func_00208D00(s32);
    extern void func_00207FD0(s32, s32, s32);
    Flat_b379_01E020F0 flat __attribute__((aligned(8)));
    s32 buf;

    buf = func_00207F60();
    if ((u16)v >= src->lo && (u16)v <= src->hi) {
        ((Flat_b379_01E020F0 *)(s32)&flat)->flags = 6;
        ((Flat_b379_01E020F0 *)(s32)&flat)->size = 3;
        ((Flat_b379_01E020F0 *)(s32)&flat)->regs = 0x441;
        ((Flat_b379_01E020F0 *)(s32)&flat)->pad4 = 0;
        flat.r = src->r;
        flat.g = src->g;
        flat.b = src->b;
        flat.a = src->a;
        flat.q = 1.0f;
        flat.v[0].x = 0x6BF8;
        flat.v[0].y = 0x71F8;
        flat.v[0].z = 0xFFFFFF;
        flat.v[0].f = 0;
        flat.v[1].x = 0x93F8;
        flat.v[1].y = 0x8DF8;
        flat.v[1].z = 0xFFFFFE;
        flat.v[1].f = 0;
        func_002086D0(&flat, func_00208D00(3));
        func_002075F0((s32)&flat, 0, (u32)src->depth);
        func_00207FD0(buf, arg1, 0);
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

static s32 func_01E02270_b379(Obj_b051_01E003A0 *obj, s32 tex, s32 n) {
    extern Tex_b051_01E003A0 D_01E07220_b379;
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
    t = D_01E07220_b379;
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

/* ot aligned: its spill slot, needed for the match */
static s32 func_01E02CC0_b379(Emit_b062_01E00DF0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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
static s32 func_01E03530_b379(Lbb_b005_01E012D0 *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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
static s32 func_01E03F70_b379(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
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

/* shape b379:01E046B0 (ShFx_GRing), 369 insns, 1 copy: for each live emitter (0x3C each) the two radii grow by their
   speeds, its point follows the source (func_00101BA0) and a quarter ring of up to 9 segments (90 / n degrees each)
   is drawn as Gouraud quads between the inner and outer radius, mirrored into all four quarters; inner colour
   0x0C..0x0F, outer 0x08..0x0B, alpha scaled by life / 8 for the first 8 frames unless flag 0x40; returns 1 */

typedef struct {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 pad5[2];
    u8 segs;
    u8 b1, g1, r1, a1;
    u8 b0, g0, r0, a0;
    f32 rin;
    f32 rout;
    f32 din;
    f32 dout;
    f32 x, y, z;
    s32 rot[4];
} Emit_b379_01E046B0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Vtx_b379_01E046B0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b379_01E046B0 v[4];
    u64 tail;
} Pkt_b379_01E046B0;

static s32 func_01E046B0_b379(void *arg0, s32 ot, s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_002075F0(void *, s32, s32);
    Emit_b379_01E046B0 *e = arg0;
    f32 m2[16];
    f32 mat[16];
    Vec4f ab[2][10];
    Vec4f q[4];
    f32 d[4];
    Vec4f v;
    Pkt_b379_01E046B0 pkt __attribute__((aligned(8)));
    s32 i;
    s32 segs;
    s32 k;
    s32 m;
    f32 step;
    f32 ang;
    f32 c;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->rin += e->din;
        e->rout += e->dout;
        segs = e->segs > 9 ? 9 : e->segs;
        step = 90.0f / segs;
        v.x = e->x;
        v.y = e->y;
        v.z = e->z;
        func_00101BA0(e, &v);
        e->x = v.x;
        e->y = v.y;
        e->z = v.z;
        func_0020EB40(mat);
        func_0020C940(m2, 0, e->rot, &v);
        func_0020BC00(mat, m2);
        for (k = 0; k < segs + 1; k++) {
            ang = 3.1415927f * (step * k) / 180.0f;
            c = func_001A6A88(ang);
            ang = func_001A6898(ang);
            ab[0][k].x = e->rin * ang;
            ab[0][k].z = e->rin * c;
            ab[1][k].x = e->rout * ang;
            ab[1][k].z = e->rout * c;
        }
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->count = 0x14;
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->tag = 8;
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->regs = 0x41414141;
        ((Pkt_b379_01E046B0 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = e->r0;
        pkt.v[2].r = pkt.v[3].r = e->r1;
        pkt.v[0].g = pkt.v[1].g = e->g0;
        pkt.v[2].g = pkt.v[3].g = e->g1;
        pkt.v[0].b = pkt.v[1].b = e->b0;
        pkt.v[2].b = pkt.v[3].b = e->b1;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].f = pkt.v[1].f = pkt.v[2].f = pkt.v[3].f = 0;
        pkt.v[0].a = pkt.v[1].a = e->a0;
        pkt.v[2].a = pkt.v[3].a = e->a1;
        if (!(e->flags & 0x40) && e->life < 8) {
            pkt.v[0].a = pkt.v[1].a = (e->a0 >> 3) * e->life;
            pkt.v[2].a = pkt.v[3].a = (e->a1 >> 3) * e->life;
        }
        func_002086D0(&pkt, 0x48);
        q[0].y = q[1].y = q[2].y = q[3].y = 0.0f;
        for (k = 0; k < segs; k++) {
            for (m = 0; m < 4; m++) {
                switch (m) {
                case 0:
                    q[0].x = ab[0][k].x;
                    q[1].x = ab[0][k + 1].x;
                    q[2].x = ab[1][k].x;
                    q[3].x = ab[1][k + 1].x;
                    q[0].z = ab[0][k].z;
                    q[1].z = ab[0][k + 1].z;
                    q[2].z = ab[1][k].z;
                    q[3].z = ab[1][k + 1].z;
                    break;
                case 1:
                    q[0].x = -ab[0][k].x;
                    q[1].x = -ab[0][k + 1].x;
                    q[2].x = -ab[1][k].x;
                    q[3].x = -ab[1][k + 1].x;
                    break;
                case 2:
                    q[0].z = -ab[0][k].z;
                    q[1].z = -ab[0][k + 1].z;
                    q[2].z = -ab[1][k].z;
                    q[3].z = -ab[1][k + 1].z;
                    break;
                case 3:
                    q[0].x = ab[0][k].x;
                    q[1].x = ab[0][k + 1].x;
                    q[2].x = ab[1][k].x;
                    q[3].x = ab[1][k + 1].x;
                    break;
                }
                if (func_00205440(&q[0], mat, &pkt.v[0].x, &d[0]) != 0 &&
                    func_00205440(&q[1], mat, &pkt.v[1].x, &d[1]) != 0 &&
                    func_00205440(&q[2], mat, &pkt.v[2].x, &d[2]) != 0 &&
                    func_00205440(&q[3], mat, &pkt.v[3].x, &d[3]) != 0) {
                    func_002075F0(&pkt, ot, (u32)((d[0] + d[1] + d[2] + d[3]) / 4.0f));
                }
            }
        }
    }
    return 1;
}

/* OVL_WARM */

/* shape b070:01E03C10, 676 insns, 13 copies: draws n lightning bolts (0x40-byte emitters): func_00102A50 builds the zigzag
   points between two ends (from func_00101BA0 or the emitter's moving ends); each projected segment becomes
   (life & 3) + 1 quads, widened across the shorter screen axis; the corner order rotates with age */

typedef struct {
    f32 x, y, z;
} Vec3_b070_01E03C10;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b070_01E03C10;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b070_01E03C10 xyz;
} Vtx_b070_01E03C10;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b070_01E03C10 v[4];
    u8 tail[0x20];
} Pkt_b070_01E03C10;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b070_01E03C10;

typedef struct {
    s32 n;
    f32 jitter;
    Vec3_b070_01E03C10 a;
    Vec3_b070_01E03C10 b;
    Vec3_b070_01E03C10 *pts;
} Bolt_b070_01E03C10;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 mode;
    u8 sel;
    u8 pad7;
    u8 nseg;
    u8 sel0;
    u8 sel1;
    u8 texid;
    u8 texsel;
    u8 wdiv;
    u8 padE[2];
    f32 jitter;
    f32 grow;
    u8 b, g, r, a;
    Vec3_b070_01E03C10 p0;
    Vec3_b070_01E03C10 p1;
    Vec3_b070_01E03C10 vel;
} Emit_b070_01E03C10;

typedef struct W_tmpl_func_01E04C80_b379 {
    Tex_b070_01E03C10 v[2];
} W_tmpl_func_01E04C80_b379;

static s32 func_01E04C80_b379(void *arg0, s32 ot __attribute__((aligned(8))), s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00102A50(void *);
    extern void func_00101EE0(void *, void *, void *);
    Emit_b070_01E03C10 *e = arg0;
    f32 mat[16];
    Bolt_b070_01E03C10 bolt;
    Vec3_b070_01E03C10 pts[17];
    Xyz_b070_01E03C10 s[3];
    Vec4f v;
    Vec3_b070_01E03C10 ab[2];
    extern W_tmpl_func_01E04C80_b379 D_01E07240_b379;
    W_tmpl_func_01E04C80_b379 tmpl_w = D_01E07240_b379;
    Pkt_b070_01E03C10 pkt __attribute__((aligned(8)));
    f32 depth[2];
    s32 i;
    void *tex;
    s32 j;
    s32 end;
    s32 k;
    s32 dx;
    s32 dy;
    f32 fdx;
    f32 fdy;
    f32 w;
    u32 c0;
    u32 c1;
    f32 z;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        if (e->mode != 0) {
            e->sel = e->sel0;
            func_00101BA0(e, &v);
            ab[0].x = v.x;
            ab[0].y = v.y;
            ab[0].z = v.z;
            if (e->flags & 2) {
                ab[1].x = ab[0].x + e->p0.x;
                ab[1].y = ab[0].y + e->p0.y;
                ab[1].z = ab[0].z + e->p0.z;
            } else {
                e->sel = e->sel1;
                func_00101BA0(e, &v);
                ab[1].x = v.x;
                ab[1].y = v.y;
                ab[1].z = v.z;
            }
        } else {
            e->p0.x += e->vel.x;
            e->p0.y += e->vel.y;
            e->p0.z += e->vel.z;
            e->p1.x += e->vel.x;
            e->p1.y += e->vel.y;
            e->p1.z += e->vel.z;
            ab[0] = e->p0;
            ab[1] = e->p1;
        }
        func_0020EB40(mat);
        bolt.n = e->nseg;
        bolt.jitter = e->jitter;
        bolt.pts = pts;
        bolt.a = ab[0];
        bolt.b = ab[1];
        func_00102A50(&bolt);
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b070_01E03C10 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = e->a;
        func_00101EE0(&pkt, &tmpl_w.v[e->texsel], tex);
        if (!(e->flags & 4) && e->life < bolt.n) {
            j = bolt.n - e->life;
        } else {
            j = 0;
        }
        if ((e->flags & 1) && e->max - e->life < bolt.n) {
            end = e->max - e->life;
        } else {
            end = bolt.n;
        }
        for (; j < end; j++) {
            if (func_00205440(&pts[j], mat, &s[0], &depth[0]) == 0 || func_00101600(&s[0]) == 0 ||
                func_00205440(&pts[j + 1], mat, &s[1], &depth[1]) == 0 || func_00101600(&s[1]) == 0) {
                continue;
            }
            dx = s[0].x - s[1].x;
            fdx = (dx >= 0) ? dx : -dx;
            dy = s[0].y - s[1].y;
            fdy = (dy >= 0) ? dy : -dy;
            w = func_001A6C60(fdx * fdx + fdy * fdy) / e->wdiv;
            for (k = 0; k < (e->life & 3) + 1; k++) {
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
                switch ((e->life + j) & 3) {
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

/* shape b379:01E05710 (b379), 1718 insns, 1 copy: b379 scene manager (written from the asm in b583:01E05670's -O4
   skeleton): setup clears the 0xD280 scene, takes both units, three joints and half the target's height (at least
   24); frame 2 five flears on the joints, 67 three more, 68 the blur quad and the fade, 260 fifteen rays at the
   target, 285 the blur quad again, 300 eight rings, the fade, the tint and two balls, 366/382 the fades (382
   recolours the target when func_001F6EF0 says so), 450 ends; rays and puffs at the joints on odd frames 3..47, rays
   on odd frames 67..239, an arc trail from a joint to the target on even frames 76..238; each trail sheds a ray and
   puffs at its head and on its 10th frame a ground ring, a ray and two bolts; steps every effect; returns 6 on
   95..376, 1/2 on 85/377 */

typedef struct Cam_b379_01E05710 {
    s32 a;
    s32 dir;
    u8 pad8[0xC];
} Cam_b379_01E05710;

typedef struct Fx_b379_01E05710 {
    u8 pad0[0x60];
} Fx_b379_01E05710;

typedef struct Fade_b379_01E05710 {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 pad5[3];
} Fade_b379_01E05710;

typedef struct Ray_b379_01E05710 {
    u8 step;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 on;
    u8 sel;
    u8 pad07;
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
    Vec4f pos;
    Vec4f vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b379_01E05710;

typedef struct Vec3_b379_01E05710 {
    f32 x, y, z;
} Vec3_b379_01E05710;

typedef struct Bolt_b379_01E05710 {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 mode;
    u8 pad6[2];
    u8 nseg;
    u8 sel0;
    u8 sel1;
    u8 texid;
    u8 texsel;
    u8 wdiv;
    u8 padE[2];
    f32 jitter;
    f32 grow;
    u8 b, g, r, a;
    Vec3_b379_01E05710 p0;
    Vec3_b379_01E05710 p1;
    Vec3_b379_01E05710 vel;
} Bolt_b379_01E05710;

typedef struct Quad_b379_01E05710 {
    u16 start;
    u16 end;
    u8 pad4;
    u8 fade;
    u8 tex;
    u8 pad7;
    f32 level;
    s32 x[4];
    s32 y[4];
    u8 b, g, r;
    u8 pad2F;
} Quad_b379_01E05710;

typedef struct Rev_b379_01E05710 {
    u16 lo;
    u16 hi;
    u8 pad4[4];
    f32 depth;
    u8 b, g, r, a;
} Rev_b379_01E05710;

typedef struct Flear_b379_01E05710 {
    u8 cur;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 on;
    u8 sel;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    Vec4f pos;
    Vec4f vel;
    f32 ox, oy, oz;
    u8 pad48[4];
} Flear_b379_01E05710;

typedef struct Col_b379_01E05710 {
    u8 b, g, r, a;
} Col_b379_01E05710;

typedef struct Rtx_b379_01E05710 {
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
    Col_b379_01E05710 c0;
    Col_b379_01E05710 c1;
    Vec4f pos;
    s32 rot[4];
    s32 drot[3];
    u8 pad58[4];
} Rtx_b379_01E05710;

typedef struct GRing_b379_01E05710 {
    u8 life;
    u8 pad1[3];
    u8 flags;
    u8 on;
    u8 pad6;
    u8 segs;
    u8 b1, g1, r1, a1;
    u8 b0, g0, r0, a0;
    f32 rin;
    f32 rout;
    f32 din;
    f32 dout;
    Vec3_b379_01E05710 pos;
    s32 rot[4];
} GRing_b379_01E05710;

typedef struct Lbb_b379_01E05710 {
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
    Col_b379_01E05710 c;
    Vec4f pos;
    s32 rot[4];
    s32 drot[4];
} Lbb_b379_01E05710;

typedef struct Gus_b379_01E05710 {
    u8 life;
    u8 pad01;
    u8 max;
    u8 pad03;
    u8 flags;
    u8 follow;
    u8 sel;
    u8 pad07;
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
} Gus_b379_01E05710;

typedef struct Trace_b379_01E05710 {
    u8 life;
    u8 pad1;
    u8 max;
    u8 pad3;
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 cnt;
    u8 texkind;
    u8 texpage;
    u8 texmode;
    u8 texidx;
    u8 padD[3];
    Vec3_b379_01E05710 *pts;
    f32 size;
    f32 blink;
    u8 b, g, r, a;
} Trace_b379_01E05710;

typedef struct Arc_b379_01E05710 {
    s32 n;
    f32 r;
    f32 ang;
    f32 fC;
    Vec3_b379_01E05710 a;
    Vec3_b379_01E05710 b;
    Vec3_b379_01E05710 *pts;
} Arc_b379_01E05710;

typedef struct Scene_b379_01E05710 {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[3];
    u8 pad18[0x14];
    Cam_b379_01E05710 cam;
    Fx_b379_01E05710 fx;
    s16 wv[2];
    Fade_b379_01E05710 fade;
    Ray_b379_01E05710 ray[0x64];
    Bolt_b379_01E05710 bolt[0x3C];
    Quad_b379_01E05710 quad;
    Rev_b379_01E05710 rev;
    Flear_b379_01E05710 flear[0x1E];
    Rtx_b379_01E05710 rtx[0x10];
    GRing_b379_01E05710 gring[0x1E];
    Lbb_b379_01E05710 lbb[8];
    Gus_b379_01E05710 gus[0x190];
    Trace_b379_01E05710 trace[0x12];
    Vec3_b379_01E05710 pts[0x12][24];
    f32 h;
    u8 tbl[0x100];
} Scene_b379_01E05710;

static s32 func_01E05710_b379(Scene_b379_01E05710 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern f32 func_001F5860(s32);
    extern void func_00102330(void *, s32);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F63E0(s32, void *);
    extern s32 func_001F6EF0(void);
    extern void func_00101AD0(void *, u8, u8, s32);
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020CDD0(void *, void *, void *);
    extern void func_00102F20(void *);
    extern void func_00101940(void *, void *);
    extern s32 b379_01E003A0();
    s32 ot __attribute__((aligned(8))); /* aligned: its spill slot */
    Vec4f v;
    Vec4f w[3];
    Vec4f dir;
    Arc_b379_01E05710 arc;
    f32 mat[16];
    Vec4f d;
    s32 rot[4];
    u8 col[4];
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 a;
    s32 b;
    u8 seg;
    f32 s;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0xD280);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 4; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 0x53, 1);
        g->m[1] = func_001F5560(g->unitA, 0x3E, 0);
        g->m[2] = func_001F5560(g->unitA, 0x48, 0);
        g->h = 0.5f * func_001F5860(g->unitB);
        if (g->h < 24.0f) {
            g->h = 24.0f;
        }
        g->wv[0] = 2;
        g->wv[1] = 0x1BC;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F53C0(1, g->unitB, &v);
    switch (g->t) {
    case 2:
        for (i = 0; i < 5; i++) {
            k = func_00101C30(g->flear, 0x4C, 0x1E);
            if (k < 0) {
                continue;
            }
            switch (i) {
            case 0:
            case 1:
                func_00101AD0(&g->flear[k], 0x10, i * 16, 0xFF);
                g->flear[k].on = 1;
                g->flear[k].sel = g->m[i];
                g->flear[k].flags = 0x81;
                g->flear[k].segs = 9;
                g->flear[k].r = 0;
                g->flear[k].g = 0;
                g->flear[k].b = 0x80;
                g->flear[k].alpha = 0xC0;
                g->flear[k].ib = 0xC0;
                g->flear[k].ig = 0xC0;
                g->flear[k].ir = 0xC0;
                g->flear[k].radius = 3200.0f;
                g->flear[k].grow = -200.0f;
                break;
            case 2:
            case 3:
            case 4:
                func_00101AD0(&g->flear[k], 0x18, 0x20, 0xFF);
                g->flear[k].on = 1;
                g->flear[k].sel = g->m[i - 2];
                g->flear[k].flags = 0x80;
                g->flear[k].segs = 9;
                g->flear[k].r = 0x20;
                g->flear[k].g = 0x20;
                g->flear[k].b = 0x80;
                g->flear[k].alpha = 0xC0;
                g->flear[k].ib = 0xC0;
                g->flear[k].ig = 0xC0;
                g->flear[k].ir = 0xC0;
                g->flear[k].radius = 2400.0f;
                g->flear[k].grow = -100.0f;
                g->flear[k].width = 35.0f;
                break;
            }
        }
        break;
    case 0x43:
        for (i = 0; i < 3; i++) {
            k = func_00101C30(g->flear, 0x4C, 0x1E);
            func_00101AD0(&g->flear[k], 0xAD, 0, 0xFF);
            g->flear[k].on = 1;
            g->flear[k].sel = g->m[i];
            g->flear[k].flags = 0x85;
            g->flear[k].segs = 9;
            g->flear[k].r = 0x10;
            g->flear[k].g = 0x10;
            g->flear[k].b = 0x80;
            g->flear[k].alpha = 0xC0;
            g->flear[k].ib = 0xC0;
            g->flear[k].ig = 0xC0;
            g->flear[k].ir = 0xC0;
            g->flear[k].radius = 600.0f;
            g->flear[k].grow = 0.0f;
            g->flear[k].width = 0.0f;
        }
        break;
    case 0x44:
        g->quad.start = g->t;
        g->quad.end = g->t + 0x28;
        g->quad.fade = 7;
        g->quad.tex = 2;
        g->quad.level = 0.0f;
        g->quad.x[0] = g->quad.x[2] = -8;
        g->quad.x[1] = g->quad.x[3] = 8;
        g->quad.y[0] = g->quad.y[1] = -8;
        g->quad.y[2] = g->quad.y[3] = 8;
        g->quad.r = 0x80;
        g->quad.g = 0x80;
        g->quad.b = 0x90;
        func_00101AD0(&g->fade, 8, 8, 0xFF);
        g->fade.flags = 0x82;
        break;
    case 0x104:
        for (i = 0, n = 0, seg = i * 2; i < 0xF; i++, n += 2, seg += 2) {
            k = func_00101C30(g->ray, 0x68, 0x64);
            if (k < 0) {
                continue;
            }
            func_00101AD0(&g->ray[k], 0x7E - n, n, 0xFF);
            g->ray[k].flags = 5;
            g->ray[k].size = g->h / 3.0f;
            g->ray[k].width = 80.0f;
            g->ray[k].delay = 0x76 - seg;
            g->ray[k].on = 0;
            g->ray[k].texkind = 0;
            g->ray[k].texpage = 2;
            g->ray[k].texmode = 3;
            g->ray[k].segments = seg;
            g->ray[k].index = func_0019A5C8() >> 4;
            g->ray[k].table = g->tbl;
            g->ray[k].radius = 1.0f;
            g->ray[k].r1 = 0x80;
            g->ray[k].b0 = 0x80;
            g->ray[k].g0 = 0x80;
            g->ray[k].r0 = 0x80;
            g->ray[k].g1 = 0x40;
            g->ray[k].b1 = 0x80;
            g->ray[k].a0 = 0x20;
            g->ray[k].a1 = 0xC0;
            g->ray[k].spin[0] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].spin[1] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].spin[2] = func_0019A5C8() >> 4 & 0x7F;
            g->ray[k].pos = v;
        }
        break;
    case 0x11D:
        g->quad.start = g->t;
        g->quad.end = 0x19C;
        g->quad.fade = 7;
        g->quad.tex = 2;
        g->quad.level = 0.0f;
        g->quad.x[0] = g->quad.x[2] = -8;
        g->quad.x[1] = g->quad.x[3] = 8;
        g->quad.y[0] = g->quad.y[1] = -8;
        g->quad.y[2] = g->quad.y[3] = 8;
        g->quad.r = 0x80;
        g->quad.g = 0x80;
        g->quad.b = 0x90;
        break;
    case 0x12C:
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 4; i++) {
                k = func_00101C30(g->rtx, 0x5C, 0x10);
                if (k < 0) {
                    continue;
                }
                func_00101AD0(&g->rtx[k], 0x30, j * 8 + i, 0xFF);
                g->rtx[k].flags = 0;
                g->rtx[k].seg = 0x24;
                g->rtx[k].mode = 1;
                g->rtx[k].texid = 2;
                g->rtx[k].sub = 2;
                g->rtx[k].bA = 6;
                g->rtx[k].bB = 0;
                g->rtx[k].radius[0] = 1.0f;
                g->rtx[k].radius[1] = 0.0f;
                g->rtx[k].dradius[0] = 3.0f;
                g->rtx[k].dradius[1] = 1.8f;
                g->rtx[k].scale = 0.25f;
                g->rtx[k].c0.r = 0xA0;
                g->rtx[k].c0.b = 0x60;
                g->rtx[k].c0.g = 0x60;
                g->rtx[k].c1.r = 0xA0;
                g->rtx[k].c1.b = 0x60;
                g->rtx[k].c1.g = 0x60;
                g->rtx[k].c0.a = 0x10;
                g->rtx[k].c1.a = 0x30;
                g->rtx[k].pos = v;
                if (j) {
                    g->rtx[k].rot[0] = 0x1000;
                    g->rtx[k].rot[1] = 0x4000;
                } else {
                    g->rtx[k].rot[0] = 0x2000;
                    g->rtx[k].rot[1] = -0x4000;
                }
                if (g->cam.dir != 0x8000) {
                    g->rtx[k].rot[1] = -g->rtx[k].rot[1];
                }
            }
        }
        func_00101AD0(&g->fade, 8, 0, 0xFF);
        g->fade.flags = 1;
        g->rev.lo = g->t;
        g->rev.hi = g->t + 0x50;
        g->rev.depth = 1.0f;
        g->rev.a = 0x80;
        g->rev.b = 0x80;
        g->rev.g = 0x80;
        g->rev.r = 0x80;
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->lbb[i], 0x34, i + 0x18, 0xFF);
            g->lbb[i].mode = 1;
            g->lbb[i].seg = 6;
            g->lbb[i].tex = 3;
            g->lbb[i].pad9 = 2;
            g->lbb[i].usize = 3.0f;
            g->lbb[i].vscale = -0.01f;
            g->lbb[i].r = 0.0f;
            switch (i) {
            case 0:
                g->lbb[i].rot[1] = 0x3000;
                break;
            case 1:
                break;
            }
            g->lbb[i].dr = 2.0f;
            g->lbb[i].pos = v;
            g->lbb[i].c.b = 0x80;
            g->lbb[i].c.g = 0x80;
            g->lbb[i].c.r = 0x80;
            g->lbb[i].c.a = 0x80;
        }
        break;
    case 0x16E:
        func_00101AD0(&g->fade, 0x10, 0, 0xFF);
        g->fade.flags = 2;
        break;
    case 0x17E:
        func_00101AD0(&g->fade, 8, 0, 0xFF);
        g->fade.flags = 4;
        if (func_001F6EF0()) {
            col[2] = 0x50;
            col[1] = 0x30;
            col[0] = 0x50;
            col[3] = 0x80;
            func_001F63E0(g->unitB, col);
        }
        break;
    case 0x1C2:
        return 8;
    }
    if ((g->t & 1) && g->t >= 2 && g->t < 0x30) {
        for (i = 0; i < 3; i++) {
            k = func_00101C30(g->ray, 0x68, 0x64);
            if (k >= 0) {
                func_00101AD0(&g->ray[k], 0xC, 0, 0xFF);
                g->ray[k].flags = 5;
                g->ray[k].size = 4.5f;
                g->ray[k].width = 40.0f;
                g->ray[k].segments = 0x14;
                g->ray[k].on = 1;
                g->ray[k].sel = g->m[i];
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 7;
                g->ray[k].delay = 0;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 1.0f;
                g->ray[k].b1 = 0x80;
                g->ray[k].g1 = 0x80;
                g->ray[k].r1 = 0x80;
                g->ray[k].b0 = 0x80;
                g->ray[k].g0 = 0x80;
                g->ray[k].r0 = 0x80;
                g->ray[k].a0 = 0;
                g->ray[k].a1 = 0x40;
                g->ray[k].spin[0] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].spin[1] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].spin[2] = func_0019A5C8() >> 4 & 0xFF;
            }
            for (j = 0; j < 0xE; j++) {
                k = func_00101C30(g->gus, 0x44, 0x190);
                if (k < 0) {
                    continue;
                }
                func_001F5620(g->unitA, g->m[i], &w[0]);
                s = 12.0f + (f32)((func_0019A5C8() >> 4) % 4 * 200 - 400) / 100.0f;
                func_00101AD0(&g->gus[k], (s32)s, 0, 0xFF);
                g->gus[k].flags = 0x40;
                g->gus[k].texkind = 0;
                g->gus[k].page = 2;
                g->gus[k].mode = (func_0019A5C8() >> 4) + 2 & 3;
                g->gus[k].texmode = 0;
                g->gus[k].a = 0x80;
                g->gus[k].b = 0x80;
                g->gus[k].g = 0x80;
                g->gus[k].r = 0x80;
                g->gus[k].size = 80.0f;
                g->gus[k].grow = -2.0f;
                g->gus[k].gravity = g->gus[k].floor = 0.0f;
                rot[0] = func_0019A5C8() >> 4 & 0xFFFF;
                rot[1] = func_0019A5C8() >> 4 & 0xFFFF;
                rot[2] = func_0019A5C8() >> 4 & 0xFFFF;
                func_0020C940(mat, 0, rot, 0);
                d.z = 0.0f;
                d.x = 0.0f;
                d.y = (f32)((func_0019A5C8() >> 4) % 80 * 200 - 8000) / 100.0f;
                func_0020CDD0(&w[1], mat, &d);
                g->gus[k].px = w[0].x + w[1].x;
                g->gus[k].py = w[0].y + w[1].y;
                g->gus[k].pz = w[0].z + w[1].z;
                g->gus[k].vx = -(w[1].x / s);
                g->gus[k].vy = -(w[1].y / s);
                g->gus[k].vz = -(w[1].z / s);
                g->gus[k].ax = g->gus[k].ay = g->gus[k].az = 0.0f;
            }
        }
    }
    if ((g->t & 1) && g->t >= 0x43 && g->t < 0xF0) {
        for (i = 0; i < 3; i++) {
            k = func_00101C30(g->ray, 0x68, 0x64);
            if (k >= 0) {
                func_00101AD0(&g->ray[k], 0xC, 0, 0xFF);
                g->ray[k].flags = 5;
                g->ray[k].size = 5.0f;
                g->ray[k].width = 40.0f;
                g->ray[k].segments = 0x14;
                g->ray[k].on = 1;
                g->ray[k].sel = g->m[i];
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 7;
                g->ray[k].delay = 0;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 1.0f;
                g->ray[k].b1 = 0x80;
                g->ray[k].g1 = 0x80;
                g->ray[k].r1 = 0x80;
                g->ray[k].b0 = 0x80;
                g->ray[k].g0 = 0x80;
                g->ray[k].r0 = 0x80;
                g->ray[k].a0 = 0;
                g->ray[k].a1 = 0x40;
                g->ray[k].spin[0] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].spin[1] = func_0019A5C8() >> 4 & 0x7F;
                g->ray[k].spin[2] = func_0019A5C8() >> 4 & 0xFF;
                g->ray[k].rot[0] = g->ray[k].rot[1] = g->ray[k].rot[2] = 0;
            }
        }
    }
    if (g->t >= 0x4B && g->t < 0xF0 && !(g->t & 1)) {
        k = func_00101C30(g->trace, 0x20, 0x12);
        if (k >= 0) {
            func_001F5620(g->unitA, g->m[k % 3], &w[0]);
            arc.n = 0x14;
            arc.r = 40.0f + (f32)((func_0019A5C8() >> 4) % 35 * 100 - 1750) / 100.0f;
            arc.ang = (f32)((func_0019A5C8() >> 4) % 180 * 200 - 18000) / 100.0f;
            arc.fC = (f32)((func_0019A5C8() >> 4) % 8 * 100 - 400) / 100.0f;
            arc.pts = g->pts[k];
            arc.a.x = w[0].x;
            arc.a.y = w[0].y;
            arc.a.z = w[0].z;
            arc.b.x = v.x;
            arc.b.y = v.y;
            arc.b.z = v.z;
            func_00102F20(&arc);
            func_00101AD0(&g->trace[k], arc.n + 6, 0, 0xFF);
            g->trace[k].b5 = 0;
            g->trace[k].flags = 0xB;
            g->trace[k].cnt = arc.n;
            g->trace[k].texkind = 0;
            g->trace[k].texpage = 2;
            g->trace[k].texmode = 0;
            g->trace[k].texidx = 3;
            g->trace[k].pts = g->pts[k];
            g->trace[k].size = 120.0f;
            g->trace[k].blink = 0.4f;
            g->trace[k].a = 0x80;
            g->trace[k].b = 0x80;
            g->trace[k].g = 0x80;
            g->trace[k].r = 0x80;
        }
    }
    for (i = 0; i < 0x12; i++) {
        a = g->trace[i].life - 1;
        b = g->trace[i].max - a;
        if (b > 1 && a > 6) {
            k = func_00101C30(g->ray, 0x68, 0x64);
            if (k >= 0) {
                func_00101AD0(&g->ray[k], 6, 0, 0xFF);
                g->ray[k].step = 1;
                g->ray[k].flags = 0x44;
                g->ray[k].size = 4.0f;
                g->ray[k].width = 60.0f;
                g->ray[k].segments = 0x10;
                g->ray[k].on = 0;
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 7;
                g->ray[k].delay = 0;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 1.0f;
                g->ray[k].b1 = 0x80;
                g->ray[k].g1 = 0x80;
                g->ray[k].r1 = 0x80;
                g->ray[k].b0 = 0x80;
                g->ray[k].g0 = 0x80;
                g->ray[k].r0 = 0x80;
                g->ray[k].a0 = 0x10;
                g->ray[k].a1 = 0x80;
                g->ray[k].spin[0] = g->ray[k].spin[1] = g->ray[k].spin[2] = 0;
                g->ray[k].pos.x = g->pts[i][b].x;
                g->ray[k].pos.y = g->pts[i][b].y;
                g->ray[k].pos.z = g->pts[i][b].z;
                dir.x = g->pts[i][b - 1].x - g->pts[i][b].x;
                dir.y = g->pts[i][b - 1].y - g->pts[i][b].y;
                dir.z = g->pts[i][b - 1].z - g->pts[i][b].z;
                func_00101940(&dir, g->ray[k].rot);
            }
            for (j = 0; j < 4; j++) {
                k = func_00101C30(g->gus, 0x44, 0x190);
                if (k < 0) {
                    continue;
                }
                func_00101AD0(&g->gus[k], 8, func_0019A5C8() >> 4 & 3, 0xFF);
                g->gus[k].flags = 0x40;
                g->gus[k].texkind = 0;
                g->gus[k].page = 2;
                g->gus[k].mode = (func_0019A5C8() >> 4) + 2 & 3;
                g->gus[k].texmode = 0;
                g->gus[k].b = 0x80;
                g->gus[k].g = 0x80;
                g->gus[k].r = 0x80;
                g->gus[k].a = 0x60;
                g->gus[k].size = 90.0f;
                g->gus[k].grow = 0.0f;
                g->gus[k].gravity = g->gus[k].floor = 0.0f;
                g->gus[k].vx = (f32)((func_0019A5C8() >> 4) % 150 - 75) / 100.0f;
                g->gus[k].vy = (f32)((func_0019A5C8() >> 4) % 150 - 75) / 100.0f;
                g->gus[k].vz = (f32)((func_0019A5C8() >> 4) % 150 - 75) / 100.0f;
                g->gus[k].px = g->pts[i][b].x;
                g->gus[k].py = g->pts[i][b].y;
                g->gus[k].pz = g->pts[i][b].z;
                g->gus[k].ax = g->gus[k].ay = g->gus[k].az = 0.0f;
            }
        }
        if (a == 9) {
            k = func_00101C30(g->gring, 0x3C, 0x1E);
            if (k >= 0) {
                func_00101AD0(&g->gring[k], 0x18, 0, 0xFF);
                g->gring[k].on = 0;
                g->gring[k].segs = 9;
                g->gring[k].rin = 0.3f;
                g->gring[k].rout = 0.0f;
                g->gring[k].b0 = 0x80;
                g->gring[k].g0 = 0x80;
                g->gring[k].r0 = 0x80;
                g->gring[k].a0 = 0xC0;
                g->gring[k].g1 = 0;
                g->gring[k].r1 = 0;
                g->gring[k].b1 = 0x80;
                g->gring[k].a1 = 0;
                g->gring[k].pos = g->pts[i][b];
                dir.x = g->pts[i][b - 1].x - g->pts[i][b].x;
                dir.y = g->pts[i][b - 1].y - g->pts[i][b].y;
                dir.z = g->pts[i][b - 1].z - g->pts[i][b].z;
                func_00101940(&dir, g->gring[k].rot);
                g->gring[k].din = 0.8f;
                g->gring[k].dout = 0.3f;
            }
            k = func_00101C30(g->ray, 0x68, 0x64);
            if (k >= 0) {
                func_00101AD0(&g->ray[k], 0x12, 0, 0xFF);
                g->ray[k].flags = 4;
                g->ray[k].size = 5.0f;
                g->ray[k].width = 45.0f;
                g->ray[k].segments = 0xA;
                g->ray[k].on = 0;
                g->ray[k].texkind = 0;
                g->ray[k].texpage = 2;
                g->ray[k].texmode = 6;
                g->ray[k].delay = 0;
                g->ray[k].index = func_0019A5C8() >> 4;
                g->ray[k].table = g->tbl;
                g->ray[k].radius = 0.5f;
                g->ray[k].b1 = 0x80;
                g->ray[k].g1 = 0x80;
                g->ray[k].r1 = 0x80;
                g->ray[k].b0 = 0x80;
                g->ray[k].g0 = 0x80;
                g->ray[k].r0 = 0x80;
                g->ray[k].a0 = 0;
                g->ray[k].a1 = 0x60;
                g->ray[k].spin[0] = g->ray[k].spin[1] = 0;
                g->ray[k].spin[2] = 0;
                g->ray[k].pos.x = v.x;
                g->ray[k].pos.y = v.y;
                g->ray[k].pos.z = v.z;
                dir.x = g->pts[i][b - 1].x - g->pts[i][b].x;
                dir.y = g->pts[i][b - 1].y - g->pts[i][b].y;
                dir.z = g->pts[i][b - 1].z - g->pts[i][b].z;
                func_00101940(&dir, g->ray[k].rot);
            }
            w[1].x = g->pts[i][b].x;
            w[1].y = g->pts[i][b].y;
            w[1].z = g->pts[i][b].z;
            for (j = 0; j < 2; j++) {
                k = func_00101C30(g->bolt, 0x40, 0x3C);
                if (k < 0) {
                    break;
                }
                func_00101AD0(&g->bolt[k], 0xA, j, 0xFF);
                g->bolt[k].mode = 0;
                g->bolt[k].flags = 0x84;
                g->bolt[k].p0.x = g->bolt[k].p1.x = w[1].x;
                g->bolt[k].p0.y = g->bolt[k].p1.y = w[1].y;
                g->bolt[k].p0.z = g->bolt[k].p1.z = w[1].z;
                g->bolt[k].p1.x += (f32)((func_0019A5C8() >> 4) % 30 * 200 - 3000) / 100.0f;
                g->bolt[k].p1.y += (f32)((func_0019A5C8() >> 4) % 30 * 200 - 3000) / 100.0f;
                g->bolt[k].p1.z += (f32)((func_0019A5C8() >> 4) % 30 * 200 - 3000) / 100.0f;
                g->bolt[k].nseg = 6;
                g->bolt[k].jitter = 1.0f;
                g->bolt[k].grow = 0.4f;
                g->bolt[k].texid = 1;
                g->bolt[k].wdiv = 4;
                g->bolt[k].texsel = 0;
                g->bolt[k].b = 0x80;
                g->bolt[k].g = 0x80;
                g->bolt[k].r = 0x80;
                g->bolt[k].a = 0x20;
            }
        }
    }
    func_01E00080_b379((Fx_b005_01E00080 *)&g->fx);
    func_001031C0(g->wv, g->t);
    b379_01E003A0(&g->fade, ot);
    func_01E02270_b379((Obj_b051_01E003A0 *)g->flear, ot, 0x10);
    func_01E01360_b379(g->gus, ot, 0x190);
    func_01E03530_b379((Lbb_b005_01E012D0 *)g->lbb, ot, 8);
    func_01E02CC0_b379((Emit_b062_01E00DF0 *)g->trace, ot, 0x12);
    func_01E00880_b379((Rib_b029_01E02B80 *)g->ray, ot, 0x64);
    func_01E03F70_b379(g->rtx, ot, 0x10);
    func_01E046B0_b379(g->gring, ot, 0x1E);
    func_01E04C80_b379(g->bolt, ot, 0x3C);
    func_01E01C70_b379((Obj_b029_01E05AA0 *)&g->quad, ot, g->t);
    func_01E020F0_b379((Src_b379_01E020F0 *)&g->rev, ot, g->t);
    if (g->t >= 0x5F && g->t < 0x179) {
        return 6;
    }
    switch (g->t) {
    case 0x55:
        return 1;
    case 0x179:
        return 2;
    }
    return 0;
}
