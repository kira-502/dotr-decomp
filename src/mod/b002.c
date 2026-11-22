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

static void func_01E00080_b002(Obj_b002_01E00080 *arg0) {
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

/* shape b002:01E00440 (ShFx_Smk01), 647 insns, 1 copy (-O1,p): n particle emitters (0x38 bytes each), each with up to
   8 particles (0x28 bytes, indexes into a shared table): moves each live particle (gravity, floor), sizes it by age,
   and draws it as a textured screen-space quad of radius func_001018E0(scale, depth), flipped by the particle's flags
   & 0x30; b011:01E00440's C at -O1, b002 compiled cold (config/mod_warm.txt) */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b002_01E00440;

typedef struct {
    f32 s, t;
    Xyz_b002_01E00440 xyz;
} Vtx_b002_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Vtx_b002_01E00440 v[4];
    u8 tail[0x20];
} Pkt_b002_01E00440;

typedef struct {
    s32 id;
    u8 sub;
    u8 b5;
    u8 pad6[2];
    s32 u, w, v, h;
} Tex_b002_01E00440;

typedef struct {
    f32 x, y, z;
} V3_b002_01E00440;

typedef struct {
    u8 life;
    u8 pad1;
    u8 max;
    u8 flags;
    V3_b002_01E00440 pos;
    V3_b002_01E00440 vel;
    V3_b002_01E00440 acc;
} Part_b002_01E00440;

typedef struct {
    u8 drawn;
    u8 pad1[3];
    u8 flags;
    u8 pad5[3];
    Part_b002_01E00440 *parts;
    s16 idx[8];
    u8 pad1C;
    u8 count;
    u8 sub;
    u8 texid;
    u8 size;
    u8 shift;
    u8 b, g, r, a;
    f32 scale;
    f32 dscale;
    f32 grav;
    f32 floor;
} Emit_b002_01E00440;

#pragma optimization_level 1

static s32 func_01E00440_b002(void *arg0, s32 ot, s32 n) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, void *);
    extern f32 func_001018E0(f32, f32);
    f32 mat[16];
    Vec4f pos;
    Tex_b002_01E00440 td;
    Pkt_b002_01E00440 pkt __attribute__((aligned(8)));
    Xyz_b002_01E00440 xyz;
    f32 dep;
    Emit_b002_01E00440 *e;
    s32 i;
    Part_b002_01E00440 *parts;
    Part_b002_01E00440 *p;
    s32 j;
    s32 tex;
    s32 d;
    s32 sz;
    f32 r;

    e = arg0;
    parts = e->parts;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            tex = func_00202BF0(5, e->texid);
        } else {
            tex = func_00202BF0(4, 2);
        }
        e->scale += e->dscale;
        for (j = 0; j < e->count; j++) {
            if (e->idx[j] == -1) {
                continue;
            }
            p = &parts[e->idx[j]];
            if (p->life < 2) {
                e->idx[j] = -1;
            } else {
                e->drawn = 1;
            }
            if (func_00101B50(p) == 0) {
                continue;
            }
            p->vel.x += p->acc.x;
            p->vel.y += p->acc.y + e->grav;
            p->vel.z += p->acc.z;
            p->pos.x += p->vel.x;
            p->pos.y += p->vel.y;
            p->pos.z += p->vel.z;
            if (p->pos.y < e->floor) {
                p->pos.y = e->floor;
            }
            pos.x = p->pos.x;
            pos.y = p->pos.y;
            pos.z = p->pos.z;
            func_0020EB40(mat);
            ((Pkt_b002_01E00440 *)(s32)&pkt)->count = 0x24;
            ((Pkt_b002_01E00440 *)(s32)&pkt)->tag = 9;
            ((Pkt_b002_01E00440 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
            ((Pkt_b002_01E00440 *)(s32)&pkt)->pad = 0;
            pkt.r = e->r;
            pkt.g = e->g;
            pkt.b = e->b;
            pkt.q = 1.0f;
            d = p->max - p->life;
            sz = e->size;
            if (e->flags & 8) {
                sz = ((d >> e->shift) & 3) + 2;
                if (d < 3) {
                    sz = d;
                }
                if (p->life < 7) {
                    sz = 7 - (p->life >> e->shift);
                }
            }
            td.b5 = e->sub;
            func_001020B0(&td, sz, 0);
            func_00101D20(&pkt, &td, (void *)tex);
            if (p->life < 16) {
                pkt.a = (e->a >> 4) * p->life;
            } else {
                pkt.a = e->a;
            }
            if (func_00205440(&pos, mat, &xyz, &dep) == 0 || func_00101600(&xyz) == 0) {
                continue;
            }
            r = func_001018E0(e->scale, dep);
            pkt.v[0].xyz.z = pkt.v[1].xyz.z = pkt.v[2].xyz.z = pkt.v[3].xyz.z = xyz.z;
            switch (p->flags & 0x30) {
            case 0x10:
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = (u32)(xyz.x - r);
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x + r);
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y - r);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = (u32)(xyz.y + r);
                break;
            case 0x20:
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x - r);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xyz.x + r);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y - r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xyz.y + r);
                break;
            case 0x30:
                pkt.v[2].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x - r);
                pkt.v[0].xyz.x = pkt.v[1].xyz.x = (u32)(xyz.x + r);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = (u32)(xyz.y - r);
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y + r);
                break;
            default:
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(xyz.x - r);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(xyz.x + r);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(xyz.y - r);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(xyz.y + r);
                break;
            }
            func_002075F0((s32)&pkt, ot, (u32)dep);
        }
    }
    return 1;
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Node_b002_01E00E60;

typedef struct {
    u8 pad00[8];
    Node_b002_01E00E60 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
} Sys_b002_01E00E60;

typedef struct {
    Sys_b002_01E00E60 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    f32 cx, cy, cz;
} Burst_b002_01E00E60;

#pragma optimization_level 1

static void func_01E00E60_b002(Burst_b002_01E00E60 *arg) {
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern f32 func_001A6898(f32);
    extern f32 func_001A6A88(f32);
    Burst_b002_01E00E60 *pr;
    Sys_b002_01E00E60 *s;
    Node_b002_01E00E60 *node;
    s32 i;
    s32 idx;
    f32 angle;
    f32 step;
    f32 c;
    f32 sn;

    pr = arg;
    s = pr->sys;
    angle = 180.0f + (f32)((func_0019A5C8() >> 4) % 36000 - 18000) / 100.0f;
    step = 360.0f / s->count;
    for (i = 0; i < s->count; i++) {
        idx = func_00101C30(s->pool, 0x28, s->kind);
        if (idx >= 0) {
            s->ids[i] = idx;
            node = &s->pool[idx];
            func_00101B40(node, pr->life, pr->mask & (func_0019A5C8() >> 4));
            node->frame = ((func_0019A5C8() >> 4) & 3) << 4;
            angle += step;
            if (!(angle <= 360.0f)) {
                angle -= 360.0f;
            }
            c = func_001A6A88(3.1415927f * angle / 180.0f);
            sn = func_001A6898(3.1415927f * angle / 180.0f);
            node->x = pr->cx + pr->radius * sn;
            node->z = pr->cz + pr->radius * c;
            node->y = pr->cy;
            node->vx = pr->speed * sn;
            node->vz = pr->speed * c;
            node->vy = pr->rise;
            node->ax = -(node->vx / pr->life);
            node->az = -(node->vz / pr->life);
            node->ay = 0.0f;
        } else {
            s->ids[i] = -1;
        }
    }
}
#pragma optimization_level reset

/* OVL_CFLAGS: -O1,p -sdatathreshold 0 -relax_pointers */

/* shape b002:01E011B0, 312 insns, 6 copies: effect spawner (per-frame joint lists -> b002:01E00E60 bursts, then a
   timed particle cloud). Calls b002_01E00E60 of the same module as a plain extern. Its Burst type here uses a Vec
   for the centre where ovl-matched/b002_01E00E60.c has three floats: same layout, unify the types when integrating. */

typedef struct {
    f32 x, y, z, w;
} Vec_b002_01E011B0;

typedef struct {
    u8 pad00[3];
    u8 frame;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Part_b002_01E011B0;

typedef struct {
    u8 pad00[4];
    u8 b4;
    u8 pad05[3];
    Part_b002_01E011B0 *pool;
    s16 ids[8];
    u8 kind;
    u8 count;
    u8 b1E;
    u8 b1F;
    u8 b20;
    u8 pad21;
    u8 r, g, b, a;
    u8 pad26[2];
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
} Node_b002_01E011B0;

typedef struct {
    Node_b002_01E011B0 *sys;
    u8 life;
    u8 mask;
    u8 pad06[2];
    f32 speed;
    f32 rise;
    f32 radius;
    Vec_b002_01E011B0 c;
} Burst_b002_01E011B0;

typedef struct {
    Node_b002_01E011B0 *nodes;
    Part_b002_01E011B0 *parts;
    s16 *lists[8];
    u8 joint[8];
    u8 kind;
    u8 pkind;
    u8 b32;
    u8 joint2;
    s16 start;
    s16 end;
    f32 f38;
    f32 f3C;
    f32 f40;
} Spawner_b002_01E011B0;

extern void b002_01E00E60(Burst_b002_01E011B0 *);

#pragma optimization_level 1

static s32 func_01E011B0_b002(Spawner_b002_01E011B0 *obj, u16 t) {
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_00101B40(void *, s32, s32);
    Spawner_b002_01E011B0 *o;
    Node_b002_01E011B0 *node;
    s16 *p;
    s32 k;
    Part_b002_01E011B0 *part;
    s32 idx;
    Vec_b002_01E011B0 pos;
    Burst_b002_01E011B0 burst;

    o = obj;
    for (k = 0; k < 8; k++) {
        if (o->lists[k] == 0) {
            continue;
        }
        for (p = o->lists[k]; *p > 0; p++) {
            if (*p != t) {
                continue;
            }
            if (func_001F5620(func_001F53A0(), o->joint[k], &pos) == 0) {
                break;
            }
            idx = func_00101C30(o->nodes, 0x38, o->kind);
            if (idx < 0) {
                return 0;
            }
            node = &o->nodes[idx];
            func_00101AD0(node, 1, 0, 0xFF);
            node->b4 = 4;
            node->pool = o->parts;
            node->kind = o->pkind;
            node->count = 4;
            node->b1E = 1;
            node->b1F = o->b32;
            node->b20 = 4;
            node->b = node->g = node->r = 0x90;
            node->a = 0x30;
            node->f28 = o->f38;
            node->f2C = o->f40;
            node->f30 = -0.015f;
            node->f34 = pos.y;
            burst.sys = node;
            burst.life = 0x20;
            burst.mask = 3;
            burst.speed = 0.25f;
            burst.rise = 0.3f;
            burst.radius = 0.15f;
            burst.c = pos;
            b002_01E00E60(&burst);
        }
    }
    if (o->start != 0 && o->start <= t && o->end >= t) {
        if (func_001F5620(func_001F53A0(), o->joint2, &pos) == 0) {
            return 0;
        }
        idx = func_00101C30(o->nodes, 0x38, o->kind);
        if (idx < 0) {
            return 0;
        }
        node = &o->nodes[idx];
        func_00101AD0(node, 1, 0, 0xFF);
        node->b4 = 4;
        node->pool = o->parts;
        node->kind = o->pkind;
        node->count = 2;
        node->b1E = 1;
        node->b1F = o->b32;
        node->b20 = 4;
        node->b = node->g = node->r = 0x90;
        node->a = 0x30;
        node->f28 = o->f3C;
        node->f2C = o->f40;
        node->f30 = -0.007f;
        node->f34 = 0.0f;
        for (k = 0; k < node->count; k++) {
            idx = func_00101C30(o->parts, 0x28, o->pkind);
            if (idx >= 0) {
                node->ids[k] = idx;
                part = &o->parts[idx];
                func_00101B40(part, 0x20, 0);
                part->frame = ((func_0019A5C8() >> 4) & 3) << 4;
                part->x = pos.x + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->z = pos.z + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->y = pos.y + (f32)((func_0019A5C8() >> 4) % 500 - 250) / 100.0f;
                part->vx = part->vy = part->vz = part->ax = part->ay = part->az = 0.0f;
            } else {
                node->ids[k] = -1;
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b002:01E01690 (ShFx_Blade), 1294 insns, 1 copy (-O1,p): b097:01E00440's ShFx_Blade -O1 source, unchanged
   (b002 compiles cold) */

typedef struct Pool_b002_01E01690 {
    u8 kind;
    u8 pad1[3];
    f32 x, y, z;
} Pool_b002_01E01690;

typedef struct Spl_b002_01E01690 {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f out[28];
} Spl_b002_01E01690;

typedef struct Rib_b002_01E01690 {
    u8 kind;
    u8 pad1[3];
    u8 flags;
    u8 b5;
    u8 b6;
    u8 pad7;
    Pool_b002_01E01690 *pool;
    s16 idx[2][9];
    u8 slot;
    u8 count;
    u8 selA;
    u8 selB;
    u8 type;
    u8 pad35;
    s16 vset;
    f32 t1;
    f32 t2;
    f32 width;
    u8 b1, g1, r1, a1;
    u8 b2, g2, r2, a2;
    u8 b3, g3, r3, a3;
    f32 dx;
    f32 dy;
    u8 pad58[8];
} Rib_b002_01E01690;

typedef struct Uvs_b002_01E01690 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b002_01E01690;

typedef struct Tbl_b002_01E01690 {
    Uvs_b002_01E01690 v[3];
} Tbl_b002_01E01690;

typedef struct Xyz_b002_01E01690 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
} Xyz_b002_01E01690;

typedef struct Vtx_b002_01E01690 {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b002_01E01690 xyz;
} Vtx_b002_01E01690;

typedef struct Pk_b002_01E01690 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b002_01E01690 v[4];
    u64 pad70[3];
    u64 b0 : 2;
    u64 abe : 2;
    u64 b4 : 20;
    u64 fix : 10;
    u64 ref : 10;
    u64 b44 : 20;
} Pk_b002_01E01690;

#pragma optimization_level 1

static s32 func_01E01690_b002(Rib_b002_01E01690 *arg0, s32 id, s32 n) {
    extern s32 func_00101AF0();
    extern void func_0020EB40();
    extern void func_00101BA0();
    extern s32 func_00101C30();
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00102550();
    extern s32 func_00202BF0();
    extern s32 func_00205440();
    extern s32 func_00101600();
    extern void func_00101EE0();
    extern void func_002075F0();
    Rib_b002_01E01690 *rib = arg0;
    Pool_b002_01E01690 *pool = arg0->pool;
    Pool_b002_01E01690 *pt;
    s32 i __attribute__((aligned(16)));
    s32 j;
    s32 k;
    s32 idx;
    s32 segs;
    s32 tex0 __attribute__((aligned(16)));
    s32 tex1 __attribute__((aligned(16)));
    s32 tex2 __attribute__((aligned(16)));
    s32 cnt __attribute__((aligned(16)));
    f32 a;
    f32 h0;
    f32 h1;
    f32 m[4][4];
    Spl_b002_01E01690 spl[2];
    Vec4f pos[2];
    Vec4f v[5];
    Vec4f q[2];
    Xyz_b002_01E01690 s[2];
    f32 depth[4];
    extern Tbl_b002_01E01690 D_01E06C00_b002;
    Tbl_b002_01E01690 tbl = D_01E06C00_b002;
    extern Uvs_b002_01E01690 D_01E06C50_b002;
    Uvs_b002_01E01690 tbl1 = D_01E06C50_b002;
    extern Uvs_b002_01E01690 D_01E06C70_b002;
    Uvs_b002_01E01690 tbl2 = D_01E06C70_b002;
    Uvs_b002_01E01690 uvs;
    Pk_b002_01E01690 pk;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            rib++;
        }
        if (func_00101AF0(rib) == 0) {
            continue;
        }
        func_0020EB40(m);
        rib->b5 = 1;
        rib->b6 = rib->selA;
        func_00101BA0(rib, &pos[0]);
        rib->b6 = rib->selB;
        func_00101BA0(rib, &pos[1]);
        for (j = 0; j < 2; j++) {
            for (k = rib->count; k > 0; k--) {
                if (rib->idx[j][k - 1] >= 0) {
                    pt = &pool[rib->idx[j][k - 1]];
                    pt->kind = rib->kind;
                }
                rib->idx[j][k] = rib->idx[j][k - 1];
            }
            if (rib->idx[j][rib->count] >= 0) {
                pt = &pool[rib->idx[j][rib->count]];
                pt->kind = 0;
                rib->idx[j][rib->count] = -1;
            }
        }
        if (rib->kind == 0) {
            continue;
        }
        idx = func_00101C30(pool, 0x10, rib->slot);
        if (idx >= 0) {
            rib->idx[0][0] = idx;
            pt = &pool[rib->idx[0][0]];
            func_00101B40(pt, rib->kind, 0);
            pt->x = pos[0].x;
            pt->y = pos[0].y;
            pt->z = pos[0].z;
        } else {
            rib->idx[0][0] = -1;
        }
        idx = func_00101C30(pool, 0x10, rib->slot);
        if (idx >= 0) {
            rib->idx[1][0] = idx;
            pt = &pool[rib->idx[1][0]];
            func_00101B40(pt, rib->kind, 0);
            pt->x = pos[1].x;
            pt->y = pos[1].y;
            pt->z = pos[1].z;
        } else {
            rib->idx[1][0] = -1;
        }
        for (j = 0; j < 2; j++) {
            spl[j].n = 0;
            for (k = 0; k < rib->count; k++) {
                if (rib->idx[j][k] >= 0) {
                    pt = &pool[rib->idx[j][k]];
                    spl[j].x[spl[j].n] = pt->x;
                    spl[j].y[spl[j].n] = pt->y;
                    spl[j].z[spl[j].n] = pt->z;
                    spl[j].n++;
                }
            }
        }
        if (spl[0].n != spl[1].n || func_00102550(&spl[0]) == 0 || func_00102550(&spl[1]) == 0) {
            continue;
        }
        segs = (spl[0].n - 1) * 4;
        tex0 = func_00202BF0(tbl.v[rib->type].kind, tbl.v[rib->type].tex);
        tex1 = func_00202BF0(tbl1.kind, tbl1.tex);
        tex2 = func_00202BF0(tbl2.kind, tbl2.tex);
        ((Pk_b002_01E01690 *)(u32)&pk)->flags = 0x34;
        ((Pk_b002_01E01690 *)(u32)&pk)->size = 0xC;
        ((Pk_b002_01E01690 *)(u32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pk_b002_01E01690 *)(u32)&pk)->pad4 = 0;
        for (k = 0; k < segs - 1; k++) {
            v[0].x = spl[1].out[k].x + rib->t1 * (spl[0].out[k].x - spl[1].out[k].x);
            v[0].y = spl[1].out[k].y + rib->t1 * (spl[0].out[k].y - spl[1].out[k].y);
            v[0].z = spl[1].out[k].z + rib->t1 * (spl[0].out[k].z - spl[1].out[k].z);
            v[1].x = spl[1].out[k + 1].x + rib->t1 * (spl[0].out[k + 1].x - spl[1].out[k + 1].x);
            v[1].y = spl[1].out[k + 1].y + rib->t1 * (spl[0].out[k + 1].y - spl[1].out[k + 1].y);
            v[1].z = spl[1].out[k + 1].z + rib->t1 * (spl[0].out[k + 1].z - spl[1].out[k + 1].z);
            v[2] = spl[1].out[k];
            v[3] = spl[1].out[k + 1];
            v[4].x = v[0].x + rib->t2 * (v[1].x - v[0].x);
            v[4].y = v[0].y + rib->t2 * (v[1].y - v[0].y);
            v[4].z = v[0].z + rib->t2 * (v[1].z - v[0].z);
            while (rib->flags & 1) {
                if (func_00205440(&v[0], m, &pk.v[0].xyz, &depth[0]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[0].xyz) == 0) {
                    break;
                }
                if (func_00205440(&v[1], m, &pk.v[1].xyz, &depth[1]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[1].xyz) == 0) {
                    break;
                }
                if (func_00205440(&v[2], m, &pk.v[2].xyz, &depth[2]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[2].xyz) == 0) {
                    break;
                }
                if (func_00205440(&v[3], m, &pk.v[3].xyz, &depth[3]) == 0) {
                    break;
                }
                if (func_00101600(&pk.v[3].xyz) == 0) {
                    break;
                }
                pk.v[0].r = pk.v[1].r = rib->r1;
                pk.v[2].r = pk.v[3].r = rib->r2;
                pk.v[0].g = pk.v[1].g = rib->g1;
                pk.v[2].g = pk.v[3].g = rib->g2;
                pk.v[0].b = pk.v[1].b = rib->b1;
                pk.v[2].b = pk.v[3].b = rib->b2;
                pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
                pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
                uvs = tbl.v[rib->type];
                if (rib->type != 0 && rib->vset != 0) {
                    uvs.v1 = rib->vset;
                }
                func_00101EE0(&pk, &uvs, tex0);
                switch (rib->type) {
                case 1:
                    pk.abe = 3;
                    pk.fix = 7;
                    pk.ref = 0x80;
                    break;
                case 2:
                    pk.abe = 3;
                    pk.fix = 3;
                    pk.ref = 0x84;
                    break;
                }
                a = (rib->kind < 8 ? (f32)(u32)rib->kind * (f32)(u32)rib->a1 / 8.0f : (f32)(u32)rib->a1) / (f32)segs;
                pk.v[2].a = pk.v[3].a = 0;
                pk.v[0].a = (u32)(a * (f32)(segs - k));
                pk.v[1].a = (u32)(a * (f32)(segs - k - 1));
                func_002075F0((s32)&pk, id, 0);
                break;
            }
            cnt = 0;
            if (rib->flags & 2) {
                cnt = 1;
            }
            if (rib->flags & 4) {
                cnt = 3;
            }
            for (j = 0; j < cnt; j++) {
                q[0] = v[0];
                if (rib->flags & 8) {
                    q[1] = v[4];
                } else {
                    q[1] = v[1];
                }
                switch (j) {
                case 1:
                    q[0].x += rib->dx;
                    q[0].y += rib->dy;
                    q[1].x += rib->dx;
                    q[1].y += rib->dy;
                    break;
                case 2:
                    q[0].x -= rib->dx;
                    q[0].y -= rib->dy;
                    q[1].x -= rib->dx;
                    q[1].y -= rib->dy;
                    break;
                }
                if (func_00205440(&q[0], m, &s[0], &depth[0]) == 0) {
                    continue;
                }
                if (func_00101600(&s[0]) == 0) {
                    continue;
                }
                if (func_00205440(&q[1], m, &s[1], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&s[1]) == 0) {
                    continue;
                }
                h0 = rib->width / (depth[0] / 256.0f);
                if (rib->flags & 8) {
                    h1 = 0.0f;
                    func_00101EE0(&pk, &tbl2, tex2);
                } else {
                    h1 = rib->width / (depth[0] / 256.0f);
                    func_00101EE0(&pk, &tbl1, tex1);
                }
                pk.v[0].r = pk.v[2].r = pk.v[1].r = pk.v[3].r = rib->r3;
                pk.v[0].g = pk.v[2].g = pk.v[1].g = pk.v[3].g = rib->g3;
                pk.v[0].b = pk.v[2].b = pk.v[1].b = pk.v[3].b = rib->b3;
                pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
                pk.v[0].xyz.fog = pk.v[1].xyz.fog = pk.v[2].xyz.fog = pk.v[3].xyz.fog = 0;
                a = (rib->kind < 8 ? (f32)(u32)rib->kind * (f32)(u32)rib->a3 / 8.0f : (f32)(u32)rib->a3) / (f32)segs;
                pk.v[0].a = pk.v[1].a = (u32)(a * (f32)(segs - k));
                pk.v[2].a = pk.v[3].a = (u32)(a * (f32)(segs - k - 1));
                if (k == 0) {
                    pk.v[0].a = pk.v[1].a = 0;
                }
                pk.v[0].xyz.z = pk.v[1].xyz.z = s[0].z;
                pk.v[2].xyz.z = pk.v[3].xyz.z = s[1].z;
                pk.v[0].xyz.y = (u32)(s[0].y + h0);
                pk.v[1].xyz.y = (u32)(s[0].y - h0);
                pk.v[2].xyz.y = (u32)(s[1].y + h1);
                pk.v[3].xyz.y = (u32)(s[1].y - h1);
                pk.v[0].xyz.x = pk.v[1].xyz.x = s[0].x;
                pk.v[2].xyz.x = pk.v[3].xyz.x = s[1].x;
                func_002075F0((s32)&pk, id, 0);
                pk.v[0].xyz.x = (u32)(s[0].x - h0);
                pk.v[1].xyz.x = (u32)(s[0].x + h0);
                pk.v[2].xyz.x = (u32)(s[1].x - h1);
                pk.v[3].xyz.x = (u32)(s[1].x + h1);
                pk.v[0].xyz.y = pk.v[1].xyz.y = s[0].y;
                pk.v[2].xyz.y = pk.v[3].xyz.y = s[1].y;
                func_002075F0((s32)&pk, id, 0);
            }
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b241:01E00440 (ShFx_Flear01), 839 insns, 26 copies (-O1,p): draws each emitter of a list as a glowing ring: a
   fan of triangles and a quad pair per segment */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b241_01E00440;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
} Hdr_b241_01E00440;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    Xyz_b241_01E00440 xyz;
} Vtx1_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    Vtx1_b241_01E00440 v[3];
    u8 tail[8];
} Pkt1_b241_01E00440;

typedef struct {
    u64 st;
    Xyz_b241_01E00440 xyz;
} Vtx2_b241_01E00440;

typedef struct {
    Hdr_b241_01E00440 h;
    u8 r, g, b, a;
    f32 q;
    Vtx2_b241_01E00440 v[4];
    u8 tail[0x20];
} Pkt2_b241_01E00440;

typedef struct {
    f32 x, y, z, w;
} V4_b241_01E00440;

typedef struct {
    s32 id;
    u8 kind;
    u8 pad05[3];
    s32 w[4];
} Tex_b241_01E00440;

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
    V4_b241_01E00440 pos;
    V4_b241_01E00440 vel;
    V4_b241_01E00440 org;
} Obj_b241_01E00440;

#pragma optimization_level 1

static s32 func_01E02AD0_b002(Obj_b241_01E00440 *obj, s32 tex, s32 n) {
    extern Tex_b241_01E00440 D_01E06C90_b002;
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
    Obj_b241_01E00440 *o;
    s32 k;
    s32 i;
    s32 segs;
    s32 h;
    f32 m0[16];
    f32 m1[16];
    V4_b241_01E00440 org;
    Tex_b241_01E00440 t;
    Xyz_b241_01E00440 scr;
    Pkt1_b241_01E00440 p1 __attribute__((aligned(8)));
    Pkt2_b241_01E00440 p2 __attribute__((aligned(8)));
    f32 depth;
    f32 zf;
    f32 px;
    f32 py;
    f32 x;
    f32 y;
    f32 step;
    f32 r;
    f32 w;
    u8 d;

    o = obj;
    t = D_01E06C90_b002;
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
        segs = o->segs > 9 ? 9 : o->segs;
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
        ((Hdr_b241_01E00440 *)(s32)&p1)->count = 0x13;
        ((Hdr_b241_01E00440 *)(s32)&p1)->tag = 6;
        ((Hdr_b241_01E00440 *)(s32)&p1)->regs = 0x414141;
        ((Hdr_b241_01E00440 *)(s32)&p1)->pad = 0;
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
        ((Hdr_b241_01E00440 *)(s32)&p2)->count = 0x24;
        ((Hdr_b241_01E00440 *)(s32)&p2)->tag = 9;
        ((Hdr_b241_01E00440 *)(s32)&p2)->regs = ((u64)4 << 32) | 0x24242421;
        ((Hdr_b241_01E00440 *)(s32)&p2)->pad = 0;
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
            x = r * func_001A6898(3.1415927f * (step * i) / 180.0f);
            y = r * func_001A6A88(3.1415927f * (step * i) / 180.0f);
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
            p2.v[0].xyz.y = scr.y + py - w;
            p2.v[2].xyz.y = w + (scr.y + py);
            p2.v[1].xyz.y = scr.y + y - w;
            p2.v[3].xyz.y = w + (scr.y + y);
            func_002075F0(&p2, tex, (u32)zf);
            p2.v[0].xyz.y = p2.v[2].xyz.y = scr.y + py;
            p2.v[1].xyz.y = p2.v[3].xyz.y = scr.y + y;
            p2.v[0].xyz.x = w + (scr.x + px);
            p2.v[2].xyz.x = scr.x + px - w;
            p2.v[1].xyz.x = w + (scr.x + x);
            p2.v[3].xyz.x = scr.x + x - w;
            func_002075F0(&p2, tex, (u32)zf);
        }
    }
    return 1;
}

#pragma optimization_level reset

/* shape b002:01E037F0 (ShFx_Ndl), 843 insns, 1 copy (-O1,p): b011:01E04380's C (b002 compiles cold): n needle rays (0x68
   bytes each): move, spin and optionally aim at a joint, then a strip of quads jittered by the random table, faded in
   over the first frames */

#define ABS_b002_01E037F0(x) ((x) >= 0 ? (x) : -(x))

typedef struct {
    f32 x, y, z, w;
} Vec_b002_01E037F0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b002_01E037F0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b002_01E037F0 p;
} Vtx_b002_01E037F0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b002_01E037F0 v[4];
    u8 tail[0x20];
} Pkt_b002_01E037F0;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[6];
    s32 u;
    u8 pad10[4];
    s32 v;
} Tex_b002_01E037F0;

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
    Vec_b002_01E037F0 pos;
    Vec_b002_01E037F0 vel;
    s32 rot[4];
    s32 spin[4];
} Ray_b002_01E037F0;

extern Tex_b002_01E037F0 D_01E06CB0_b002;

#pragma optimization_level 1

static s32 func_01E037F0_b002(Ray_b002_01E037F0 *obj, s32 target, s32 count) {
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
    Ray_b002_01E037F0 *o;
    s32 i;
    s32 j;
    u8 idx;
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
    Xyz_b002_01E037F0 xy[2];
    Vec_b002_01E037F0 pt;
    Vec_b002_01E037F0 d;
    Vec_b002_01E037F0 tmp;
    Tex_b002_01E037F0 tex0;
    Tex_b002_01E037F0 tex;
    Pkt_b002_01E037F0 pkt __attribute__((aligned(8)));
    f32 dep[2];

    o = obj;
    tex0 = D_01E06CB0_b002;
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
        ((Pkt_b002_01E037F0 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b002_01E037F0 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b002_01E037F0 *)(s32)&pkt)->regs = 0x421421421421LL;
        ((Pkt_b002_01E037F0 *)(s32)&pkt)->pad = 0;
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
            if (ABS_b002_01E037F0(xy[1].x - xy[0].x) > ABS_b002_01E037F0(xy[1].y - xy[0].y)) {
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

/* shape b002:01E04520 (ShFx_Mptc), 941 insns, 1 copy (-O1,p): b024:01E02120 at -O1 (angle inline, step = 17.0f local,
   ABS macro): update and draw ribbon emitters (0x58 bytes each); every segment is projected straight into the
   packet's vertex slots and widened on screen; b059:01E00E10's C (b002 compiles cold) */

#define ABS(x) ((x) >= 0 ? (x) : -(x))

typedef struct Uvs_b002_01E04520 {
    s32 kind;
    u8 tex;
    u8 b5;
    u16 pad6;
    s32 u0, v0, u1, v1;
} Uvs_b002_01E04520;

typedef struct Rib_b002_01E04520 {
    u8 age;
    u8 b1;
    u8 life;
    u8 b3;
    u8 flags;
    u8 b5[3];
    u8 count;
    u8 k;
    u8 idx;
    u8 frame;
    u8 b5c;
    u8 div;
    u8 padE[2];
    u8 *pts;
    f32 scale;
    f32 f18;
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    f32 pos[3];
    u8 pad34[4];
    f32 vel[3];
    u8 pad44[4];
    f32 rot[4];
} Rib_b002_01E04520;

typedef struct Xyz_b002_01E04520 {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b002_01E04520;

typedef struct Pk_b002_01E04520 {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b002_01E04520 v[4];
    u64 pad60[3];
} Pk_b002_01E04520;

static inline void b059_01E00E10_tag(Pk_b002_01E04520 *p, s32 size, s32 flags, u64 regs) {
    p->flags = flags;
    p->size = size;
    p->regs = regs;
    p->pad4 = 0;
}

#pragma optimization_level 1
typedef struct W_tbl_func_01E00E10_b059 {
    Uvs_b002_01E04520 v[4];
} W_tbl_func_01E00E10_b059;

static s32 func_01E04520_b002(Rib_b002_01E04520 *arg0, s32 id __attribute__((aligned(8))), s32 n) {
    extern s32 func_00205440();
    extern void func_00101BA0();
    extern void func_001020B0();
    extern void func_00101D20();
    extern void func_0020C940();
    extern void func_0020BC00();
    s32 sel;
    f32 ang;
    s32 dx;
    f32 step;
    f32 b;
    Rib_b002_01E04520 *p = arg0;
    s32 i;
    f32 h1;
    s32 dy;
    s32 tex;
    u8 k;
    f32 w;
    f32 d;
    f32 a;
    f32 h0;
    s32 life;
    s32 j;

    f32 m2[4][4];
    f32 m[4][4];
    Vec4f t[2];
    Vec4f v;
    extern W_tbl_func_01E00E10_b059 D_01E06CD0_b002;
    W_tbl_func_01E00E10_b059 tbl_w = D_01E06CD0_b002;
    Uvs_b002_01E04520 uvs;
    Pk_b002_01E04520 pk;
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
        } else {
            tex = func_00202BF0(tbl_w.v[p->idx].kind, tbl_w.v[p->idx].tex);
        }
        p->pos[0] += p->vel[0];
        p->pos[1] += p->vel[1];
        p->pos[2] += p->vel[2];
        func_00101BA0(p, p->pos);
        func_0020EB40(m);
        func_0020C940(m2, 0, p->rot, p->pos);
        func_0020BC00(m, m2);
        k = p->k;
        step = 17.0f;
        ang = 0.0f;
        life = p->life - p->age;
        b059_01E00E10_tag((Pk_b002_01E04520 *)(u32)&pk, 9, 0x24, ((u64)4 << 32) | 0x24242421);
        pk.r = p->b;
        pk.g = p->g;
        pk.b = p->r;
        pk.q = 1.0f;
        if (p->flags & 4) {
            sel = p->frame;
            if (p->flags & 8) {
                sel = life & 7;
                if (life < 3) {
                    sel = life;
                }
                if (p->age < 4) {
                    sel = 7 - p->age;
                }
            }
            uvs.b5 = p->b5c;
            func_001020B0(&uvs, sel, 0);
            func_00101D20(&pk, &uvs, tex);
        } else {
            func_00101D20(&pk, &tbl_w.v[p->idx], tex);
        }
        if (p->age < 8) {
            pk.a = (p->a >> 3) * p->age;
        } else {
            pk.a = p->a;
        }
        for (j = 0; j < p->count; j++) {
            if (p->flags & 1) {
                v.x = p->scale * (f32)(p->pts[k] - p->pts[k + 1]) / 255.0f;
                v.y = p->scale * (f32)(p->pts[k + 2] - p->pts[k + 3]) / 255.0f;
                v.z = p->scale * (f32)(p->pts[k + 4] - p->pts[k + 5]) / 255.0f;
                k += 6;
            } else {
                ang += step;
                if (!(ang <= 360.0f)) {
                    ang -= 360.0f;
                }
                a = (f32)p->pts[k++] / 255.0f;
                b = p->f18 * (f32)p->pts[k++] / 255.0f;
                v.x = a * b * func_001A6898(3.1415927f * ang / 180.0f);
                v.z = a * b * func_001A6A88(3.1415927f * ang / 180.0f);
                v.y = a * p->scale;
            }
            w = p->width + p->grow * (f32)life;
            if (p->div > 1) {
                d = p->scale / (f32)p->div;
                w = w / (1.0f + func_0020D0E0(&v.x) / d);
            }
            t[0].x = v.x * (f32)life;
            t[0].y = v.y * (f32)life;
            t[0].z = v.z * (f32)life;
            if (func_00205440(&t[0], m, &pk.v[0], &depth[0]) == 0) {
                continue;
            }
            if (func_00101600(&pk.v[0]) == 0) {
                continue;
            }
            h0 = func_001018E0(w, depth[0]);
            if (p->flags & 2) {
                t[1].x = t[0].x + 4.0f * v.x;
                t[1].y = t[0].y + 4.0f * v.y;
                t[1].z = t[0].z + 4.0f * v.z;
                if (func_00205440(&t[1], m, &pk.v[2], &depth[1]) == 0) {
                    continue;
                }
                if (func_00101600(&pk.v[2]) == 0) {
                    continue;
                }
                h1 = func_001018E0(w, depth[1]);
                dy = ABS(pk.v[2].y - pk.v[0].y);
                dx = ABS(pk.v[2].x - pk.v[0].x);
                if (dy < dx) {
                    pk.v[1].x = pk.v[0].x;
                    pk.v[3].x = pk.v[2].x;
                    pk.v[1].y = (u32)(pk.v[0].y + h0);
                    pk.v[0].y = (u32)(pk.v[0].y - h0);
                    pk.v[3].y = (u32)(pk.v[2].y + h1);
                    pk.v[2].y = (u32)(pk.v[2].y - h1);
                } else {
                    pk.v[1].y = pk.v[0].y;
                    pk.v[3].y = pk.v[2].y;
                    pk.v[1].x = (u32)(pk.v[0].x + h0);
                    pk.v[0].x = (u32)(pk.v[0].x - h0);
                    pk.v[3].x = (u32)(pk.v[2].x + h1);
                    pk.v[2].x = (u32)(pk.v[2].x - h1);
                }
                pk.v[1].z = pk.v[0].z;
                pk.v[3].z = pk.v[2].z;
            } else {
                pk.v[1].x = (u32)(pk.v[0].x + h0);
                pk.v[1].y = (u32)(pk.v[0].y - h0);
                pk.v[2].x = (u32)(pk.v[0].x - h0);
                pk.v[2].y = (u32)(pk.v[0].y + h0);
                pk.v[3].x = (u32)(pk.v[0].x + h0);
                pk.v[3].y = (u32)(pk.v[0].y + h0);
                pk.v[0].x = (u32)(pk.v[0].x - h0);
                pk.v[0].y = (u32)(pk.v[0].y - h0);
                pk.v[1].z = pk.v[2].z = pk.v[3].z = pk.v[0].z;
            }
            pk.v[0].fog = pk.v[1].fog = pk.v[2].fog = pk.v[3].fog = 1;
            func_002075F0((s32)&pk, id, (u32)(depth[0]));
        }
    }
    return 1;
}
#pragma optimization_level reset

/* shape b200:01E05B40 (ShFx_Redeye), 766 insns, 3 copies (-O1,p): b099:01E02A90's red-eye streak at -O1: locals
   declared i, pool, ..., idx, r, tex, k, m; both alpha factors unsigned */

typedef struct {
    f32 x, y, z;
} Vec3_b200_01E05B40;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b200_01E05B40;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u64 st;
    Xyz_b200_01E05B40 xyz;
} Vtx_b200_01E05B40;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_b200_01E05B40 v[4];
    u8 tail[0x20];
} Pkt_b200_01E05B40;

typedef struct {
    s32 k0, k1;
    s32 u, w, v, h;
} Tex_b200_01E05B40;

typedef struct {
    Tex_b200_01E05B40 v[2];
} Tmpl_b200_01E05B40;

typedef struct {
    u8 life;
    u8 pad1[3];
    f32 x;
    f32 y;
    f32 z;
} Rec_b200_01E05B40;

typedef struct {
    s32 n;
    f32 x[8];
    f32 y[8];
    f32 z[8];
    Vec4f pts[28];
    u8 pad[0xC];
} Spl_b200_01E05B40;

typedef struct {
    u8 life;
    u8 pad1[4];
    u8 on;
    u8 sel;
    u8 pad7;
    Rec_b200_01E05B40 *pool;
    s16 ids[9];
    u8 kind;
    u8 n;
    u8 texid;
    u8 sel0;
    u8 sel1;
    u8 maxseg;
    u8 pad24[4];
    f32 th;
    f32 width;
    f32 depth;
    u8 b, g, r, a;
    Vec3_b200_01E05B40 off;
    u8 pad44[4];
} Emit_b200_01E05B40;

#pragma optimization_level 1

static s32 func_01E053E0_b002(void *arg0, s32 ot, s32 n) {
    extern void func_00101BA0(void *, void *);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00101B40(void *, u8, u8);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_00101EE0(void *, void *, void *);
    Emit_b200_01E05B40 *e = arg0;
    s32 i;
    Rec_b200_01E05B40 *pool = e->pool;
    f32 mat[16];
    Spl_b200_01E05B40 spl;
    Vec4f pos;
    extern Tmpl_b200_01E05B40 D_01E06D30_b002;
    Tmpl_b200_01E05B40 tmpl = D_01E06D30_b002;
    Vec4f pos2;
    Vec4f dir;
    Vec4f cam;
    Xyz_b200_01E05B40 scr;
    Pkt_b200_01E05B40 pkt __attribute__((aligned(8)));
    f32 depth;
    s32 idx;
    Rec_b200_01E05B40 *r;
    void *tex;
    s32 k;
    s32 m;
    f32 a;
    f32 hw;
    f32 as;
    f32 dx;
    f32 dy;

    for (i = 0; i < n; i++) {
        if (i != 0) {
            e++;
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        e->on = 1;
        e->sel = e->sel0;
        func_00101BA0(e, &pos);
        pos.x += e->off.x;
        pos.y += e->off.y;
        pos.z += e->off.z;
        cam = *(Vec4f *)func_001FAD10(0);
        e->sel = e->sel1;
        func_00101BA0(e, &pos2);
        dir.x = pos.x - pos2.x;
        dir.y = pos.y - pos2.y;
        dir.z = pos.z - pos2.z;
        func_0020D070(&dir.x);
        func_0020D070(&cam.x);
        if (func_0020D1A0(&dir.x, &cam.x) > e->th) {
            for (k = 0; k < e->n; k++) {
                if (e->ids[k] >= 0) {
                    (r = &pool[e->ids[k]])->life = 0;
                    e->ids[k] = -1;
                }
            }
            continue;
        }
        func_0020EB40(mat);
        for (k = e->n; k > 0; k--) {
            if (e->ids[k - 1] >= 0) {
                r = &pool[e->ids[k - 1]];
                r->life = e->life;
            }
            e->ids[k] = e->ids[k - 1];
        }
        if (e->ids[e->n] >= 0) {
            (r = &pool[e->ids[e->n]])->life = 0;
            e->ids[e->n] = -1;
        }
        if (e->life == 0) {
            continue;
        }
        idx = func_00101C30(pool, 0x10, e->kind);
        if (idx >= 0) {
            e->ids[0] = idx;
            r = &pool[e->ids[0]];
            if (func_00205440(&pos, mat, &scr, &depth)) {
                func_00101B40(r, e->life, 0);
                r->x = scr.x;
                r->y = scr.y;
                r->z = func_0017B340(scr.z);
                e->depth = depth;
            } else {
                e->ids[0] = -1;
            }
        } else {
            e->ids[0] = -1;
        }
        spl.n = 0;
        for (k = 0; k < e->n; k++) {
            if (e->ids[k] >= 0) {
                r = &pool[e->ids[k]];
                spl.x[spl.n] = r->x;
                spl.y[spl.n] = r->y;
                spl.z[spl.n] = 0.0f;
                if (spl.n != 0) {
                    dx = spl.x[spl.n - 1] - r->x;
                    dy = spl.y[spl.n - 1] - r->y;
                    if (func_001A6C60(dx * dx + dy * dy) > 32.0f) {
                        spl.n++;
                    }
                } else {
                    spl.n++;
                }
            }
        }
        if (spl.n < 3) {
            spl.pts[0].x = spl.x[0];
            spl.pts[0].y = spl.y[0];
            spl.pts[0].z = spl.z[0];
            m = 2;
        } else {
            func_00102550(&spl);
            m = (spl.n - 1) * 4;
        }
        tex = (void *)func_00202BF0(5, e->texid);
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->count = 0x34;
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->tag = 0xC;
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Pkt_b200_01E05B40 *)(s32)&pkt)->pad = 0;
        pkt.v[0].r = pkt.v[1].r = pkt.v[2].r = pkt.v[3].r = e->r;
        pkt.v[0].g = pkt.v[1].g = pkt.v[2].g = pkt.v[3].g = e->g;
        pkt.v[0].b = pkt.v[1].b = pkt.v[2].b = pkt.v[3].b = e->b;
        pkt.v[0].q = pkt.v[1].q = pkt.v[2].q = pkt.v[3].q = 1.0f;
        if (e->life < 8) {
            a = (f32)(u32)e->life * (f32)(u32)e->a / 8.0f;
        } else {
            a = (u32)e->a;
        }
        as = a / m;
        pkt.v[0].xyz.z = pkt.v[2].xyz.z = pkt.v[1].xyz.z = pkt.v[3].xyz.z = 0xFFFFFF;
        hw = e->width / (e->depth / 256.0f);
        for (k = 0; k < m - 1; k++) {
            if (k == 0) {
                func_00101EE0(&pkt, &tmpl.v[0], tex);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = (u32)(spl.pts[k].x - hw);
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)(spl.pts[k].x + hw);
                pkt.v[0].xyz.y = pkt.v[1].xyz.y = (u32)(spl.pts[k].y - hw);
                pkt.v[2].xyz.y = pkt.v[3].xyz.y = (u32)(spl.pts[k].y + hw);
                pkt.v[0].a = pkt.v[1].a = pkt.v[2].a = pkt.v[3].a = (u32)(as * (f32)(m - k));
                func_002075F0((s32)&pkt, ot, 0);
            } else {
                func_00101EE0(&pkt, &tmpl.v[1], tex);
                pkt.v[0].a = pkt.v[2].a = (u32)(as * (f32)(m - k));
                pkt.v[1].a = pkt.v[3].a = (u32)(as * (f32)(m - k - 1));
                pkt.v[0].xyz.y = (u32)(scr.y - hw);
                pkt.v[2].xyz.y = (u32)(scr.y + hw);
                pkt.v[1].xyz.y = (u32)(spl.pts[k].y - hw);
                pkt.v[3].xyz.y = (u32)(spl.pts[k].y + hw);
                pkt.v[0].xyz.x = pkt.v[2].xyz.x = scr.x;
                pkt.v[1].xyz.x = pkt.v[3].xyz.x = (u32)spl.pts[k].x;
                func_002075F0((s32)&pkt, ot, 0);
                pkt.v[0].xyz.x = (u32)(scr.x - hw);
                pkt.v[2].xyz.x = (u32)(scr.x + hw);
                pkt.v[1].xyz.x = (u32)(spl.pts[k].x - hw);
                pkt.v[3].xyz.x = (u32)(spl.pts[k].x + hw);
                pkt.v[0].xyz.y = pkt.v[2].xyz.y = scr.y;
                pkt.v[1].xyz.y = pkt.v[3].xyz.y = (u32)spl.pts[k].y;
                func_002075F0((s32)&pkt, ot, 0);
            }
            scr.x = (u32)spl.pts[k].x;
            scr.y = (u32)spl.pts[k].y;
        }
    }
    return 1;
}

#pragma optimization_level reset

/* shape b002:01E05FE0 (b002), 765 insns, 1 copy (-O1,p): b002 scene manager: setup takes both units, eight models and
   the walk spawner; at frame 20 arms the flare and the red-eye streak, at 118 two trails, at 122 the ray, flare, 8
   ribbons and the emitter; steps all effects and returns 8 / 1 / 2 at frames 230 / 112 / 125 */

typedef struct {
    f32 x, y, z, w;
} V4_b002_01E05FE0;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 b5;
    u8 pad6[0xE];
    f32 f14;
    f32 f18;
    f32 f1C;
    V4_b002_01E05FE0 pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    f32 f50;
    u8 pad54[0xC];
} Emit_b002_01E05FE0;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 sel;
    u8 segs;
    u8 b, g, r;
    u8 padB;
    u8 ib, ig, ir;
    u8 alpha;
    f32 radius;
    f32 grow;
    f32 width;
    V4_b002_01E05FE0 pos;
    u8 pad2C[0x20];
} Flare_b002_01E05FE0;

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 pad5[3];
    void *pool;
    s16 ids0[9];
    s16 ids1[9];
    u8 kind;
    u8 n;
    u8 sel0;
    u8 sel1;
    u8 b34;
    u8 pad35;
    s16 h36;
    f32 f38;
    u8 pad3C[8];
    u8 c0[4];
    u8 c1[4];
    u8 pad4C[0x14];
} Trail_b002_01E05FE0;

typedef struct {
    u8 pad0[4];
    u8 flags;
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
    f32 f18;
    f32 f1C;
    u8 c20[4];
    u8 c24[4];
    V4_b002_01E05FE0 pos;
    u8 pad38[0x20];
    s32 w58;
    s32 w5C;
    s32 w60;
    u8 pad64[4];
} Ray_b002_01E05FE0;

typedef struct {
    u8 pad0[5];
    u8 on;
    u8 pad6[2];
    void *pool;
    s16 ids[9];
    u8 kind;
    u8 n;
    u8 texid;
    u8 sel0;
    u8 sel1;
    u8 pad23[5];
    f32 th;
    f32 width;
    f32 depth;
    u8 b, g, r, a;
    u8 pad38[0x10];
} Eye_b002_01E05FE0;

typedef struct {
    u8 pad0[4];
    u8 flags;
    u8 b5;
    u8 pad6[2];
    u8 count;
    u8 k;
    u8 idx;
    u8 frame;
    u8 b5c;
    u8 padD[3];
    s8 *pts;
    f32 scale;
    u8 pad18[4];
    f32 width;
    f32 grow;
    u8 r, g, b, a;
    V4_b002_01E05FE0 pos;
    u8 pad38[0x20];
} Rib_b002_01E05FE0;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[8];
    u8 cam[0x14];
    Emit_b002_01E05FE0 emit;
    Spawner_b002_01E011B0 walk;
    Node_b002_01E011B0 smk[0x20];
    Part_b002_01E011B0 parts[0x32];
    Flare_b002_01E05FE0 flare;
    Trail_b002_01E05FE0 trail[2];
    Ray_b002_01E05FE0 ray;
    Eye_b002_01E05FE0 eye;
    u8 pool[0x28][0x10];
    Rib_b002_01E05FE0 rib[8];
    s8 tbl[0x100];
} Scene_b002_01E05FE0;

#pragma optimization_level 1

static s32 func_01E05FE0_b002(Scene_b002_01E05FE0 *g, s32 code) {
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
    extern s32 func_00101C30(void *, s32, s32);
    extern s32 func_0019A5C8(void);
    extern s32 func_01E053E0_b002();
    extern s32 func_01E01690_b002();
    extern s32 func_01E037F0_b002();
    extern s32 func_01E04520_b002();
    extern s16 D_01E06D60_b002[];
    extern s16 D_01E06D70_b002[];
    s32 ot;
    V4_b002_01E05FE0 v;
    s32 i;
    s32 k;
    s32 j;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x17B0);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 3; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 0xE, 1);
        g->m[1] = func_001F5560(g->unitA, 0xF, 0);
        g->m[2] = func_001F5560(g->unitA, 0x1A, 0);
        g->m[3] = func_001F5560(g->unitA, 0x1B, 0);
        g->m[4] = func_001F5560(g->unitA, 0x24, 0);
        g->m[5] = func_001F5560(g->unitA, 0x23, 0);
        g->m[6] = func_001F5560(g->unitA, 0x2C, 0);
        g->m[7] = func_001F5560(g->unitA, 0x36, 0);
        g->walk.joint[0] = g->m[6];
        g->walk.joint[1] = g->m[7];
        g->walk.lists[0] = D_01E06D60_b002;
        g->walk.lists[1] = D_01E06D70_b002;
        g->walk.nodes = g->smk;
        g->walk.kind = 0x20;
        g->walk.parts = g->parts;
        g->walk.pkind = 0x32;
        g->walk.b32 = 0;
        g->walk.joint2 = g->m[6];
        g->walk.start = 0x5C;
        g->walk.end = 0x6E;
        g->walk.f38 = 200.0f;
        g->walk.f3C = 150.0f;
        g->walk.f40 = 6.0f;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x14:
        func_00101AD0(&g->flare, 0xC, 0, 0xFF);
        g->flare.b5 = 1;
        g->flare.sel = g->m[0];
        g->flare.flags = 0x80;
        g->flare.segs = 9;
        g->flare.r = 0x80;
        g->flare.g = 0;
        g->flare.b = 0x20;
        g->flare.ir = g->flare.ig = g->flare.ib = g->flare.alpha = 0xC0;
        g->flare.radius = 80.0f;
        g->flare.grow = 40.0f;
        g->flare.width = 8.0f;
        func_00101AD0(&g->eye, 0xC8, 0, 0xFF);
        g->eye.on = 1;
        g->eye.sel0 = g->m[0];
        g->eye.sel1 = g->m[1];
        g->eye.pool = g->pool;
        g->eye.kind = 0x28;
        g->eye.n = 8;
        g->eye.texid = 1;
        g->eye.width = 150.0f;
        g->eye.th = 0.57f;
        g->eye.r = g->eye.g = g->eye.b = 0x80;
        g->eye.a = 0x40;
        for (i = 0; i < g->eye.n + 1; i++) {
            g->eye.ids[i] = -1;
        }
        g->eye.depth = -1.0f;
        break;
    case 0x76:
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->trail[i], 0x10, 0, 0xFF);
            g->trail[i].on = 1;
            g->trail[i].pool = g->pool;
            g->trail[i].kind = 0x28;
            g->trail[i].n = 6;
            g->trail[i].sel0 = g->m[i * 2 + 2];
            g->trail[i].sel1 = g->m[i * 2 + 3];
            g->trail[i].f38 = 1.0f;
            g->trail[i].b34 = 0;
            g->trail[i].h36 = 0;
            g->trail[i].c0[2] = g->trail[i].c0[1] = g->trail[i].c0[0] = g->trail[i].c0[3] = 0x80;
            g->trail[i].c1[2] = 0x80;
            g->trail[i].c1[1] = 0x80;
            g->trail[i].c1[0] = 0x10;
            for (j = 0; j < g->trail[i].n + 1; j++) {
                g->trail[i].ids0[j] = g->trail[i].ids1[j] = -1;
            }
        }
        break;
    case 0x7A:
        func_00101AD0(&g->ray, 0x1C, 0, 0xFF);
        g->ray.flags = 5;
        g->ray.f14 = 1.5f;
        g->ray.f1C = 60.0f;
        g->ray.b5 = 0;
        g->ray.bA = 2;
        g->ray.bB = 2;
        g->ray.bC = 3;
        g->ray.b8 = 0xA0;
        g->ray.b9 = func_0019A5C8() >> 4;
        g->ray.tbl = g->tbl;
        g->ray.f18 = 1.0f;
        g->ray.c20[2] = g->ray.c20[1] = g->ray.c20[0] = g->ray.c24[2] = g->ray.c24[1] = g->ray.c24[0] = 0x80;
        g->ray.c20[3] = 0x20;
        g->ray.c24[3] = 0x80;
        g->ray.pos = v;
        g->ray.w58 = 0x100;
        g->ray.w5C = 0x100;
        g->ray.w60 = 0x100;
        func_00101AD0(&g->flare, 0x20, 0, 0xFF);
        g->flare.b5 = 0;
        g->flare.flags = 0x81;
        g->flare.segs = 9;
        g->flare.ir = g->flare.ig = g->flare.ib = g->flare.alpha = 0xC0;
        g->flare.r = 0x60;
        g->flare.g = 0x10;
        g->flare.b = 0xC0;
        g->flare.grow = 0.0f;
        g->flare.radius = 900.0f;
        g->flare.pos = v;
        for (i = 0; i < 8; i++) {
            k = func_00101C30(g->rib, 0x58, 8);
            if (k >= 0) {
                func_00101AD0(&g->rib[k], (u8)(((func_0019A5C8() >> 4) & 3) + 0x16), (func_0019A5C8() >> 4) & 7, 0xFF);
                g->rib[k].flags = 7;
                g->rib[k].b5 = 0;
                g->rib[k].count = 0x28;
                g->rib[k].k = func_0019A5C8() >> 4;
                g->rib[k].idx = 2;
                g->rib[k].frame = 3;
                g->rib[k].b5c = 2;
                g->rib[k].width = 16.0f + 2.0f * i;
                g->rib[k].grow = 0.0f;
                g->rib[k].pts = g->tbl;
                g->rib[k].scale = 1.2f + (f32)((func_0019A5C8() >> 4) % 100 - 50) / 100.0f;
                g->rib[k].b = g->rib[k].g = g->rib[k].r = g->rib[k].a = 0x90;
                g->rib[k].pos = v;
            }
        }
        func_00101AD0(&g->emit, 0x20, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.8f;
        g->emit.f18 = 1.8f;
        g->emit.f1C = 1.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 40.0f;
        g->emit.f50 = 4.0f;
        g->emit.pos = v;
        break;
    case 0xE6:
        return 8;
    }
    func_01E00080_b002((Obj_b002_01E00080 *)&g->emit);
    func_01E011B0_b002(&g->walk, g->t);
    func_01E00440_b002(g->smk, ot, 0x20);
    func_01E053E0_b002(&g->eye, ot, 1);
    func_01E01690_b002(g->trail, ot, 2);
    func_01E037F0_b002(&g->ray, ot, 1);
    func_01E02AD0_b002((Obj_b241_01E00440 *)&g->flare, ot, 1);
    func_01E04520_b002(g->rib, ot, 8);
    switch (g->t) {
    case 0x70:
        return 1;
    case 0x7D:
        return 2;
    }
    return 0;
}

#pragma optimization_level reset
