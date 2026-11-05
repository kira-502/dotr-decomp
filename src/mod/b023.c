#include "common.h"

/* shape b023:01E00080 (ShFx_Gus), 580 insns, 1 copy (-O2,p): n gust puffs (0x44-byte emitters): each moves with its
   acceleration and gravity, stops at its floor and grows; its animation frame comes from its age with flag 8; it
   fades over its last 16 frames and draws as a textured screen-space square of its projected width, flipped by flags
   & 0x30; the source of b097:01E059B0, built here at -O2 */

typedef struct {
    f32 x, y, z, w;
} Vec_b023_01E00080;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b023_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b023_01E00080;

typedef struct {
    u64 st;
    Xyz_b023_01E00080 p;
} Vtx_b023_01E00080;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Col_b023_01E00080 c;
    Vtx_b023_01E00080 v[4];
    u8 tail[0x20];
} Pkt_b023_01E00080;

typedef struct {
    s32 id;
    u8 kind;
    u8 page;
    u8 pad06[0x12];
} Tex_b023_01E00080;

typedef struct {
    u8 life;
    u8 pad01;
    u8 total;
    u8 pad03;
    u8 flags;
    u8 pad05[3];
    u8 page;
    u8 texkind;
    u8 frame;
    u8 shift;
    u8 b, g, r, a;
    f32 width;
    f32 grow;
    f32 gravity;
    f32 floor;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
} Fx_b023_01E00080;

#pragma optimization_level 2

static s32 func_01E00080_b023(Fx_b023_01E00080 *obj, s32 target, s32 n) {
    extern s32 func_00101AF0(void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_0020EB40(void *);
    extern void func_001020B0(void *, s32, s32);
    extern void func_00101D20(void *, void *, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern s32 func_00101600(void *);
    extern f32 func_001018E0(f32, f32);
    extern void func_002075F0(void *, s32, s32);
    f32 m[16];
    Vec_b023_01E00080 a;
    Tex_b023_01E00080 tex;
    Pkt_b023_01E00080 pkt __attribute__((aligned(8)));
    Xyz_b023_01E00080 xy;
    f32 d;
    Fx_b023_01E00080 *e;
    s32 age;
    s32 i;
    s32 fr;
    f32 w;
    s32 texture;

    e = obj;
    for (i = 0; i < n; i++) {
        if (i != 0) {
            e = (Fx_b023_01E00080 *)((u8 *)e + 0x44);
        }
        if (func_00101AF0(e) == 0) {
            continue;
        }
        if (e->flags & 4) {
            texture = func_00202BF0(5, e->texkind);
        } else {
            texture = func_00202BF0(4, 2);
        }
        e->vx += e->ax;
        e->vy += e->ay + e->gravity;
        e->vz += e->az;
        e->x += e->vx;
        e->y += e->vy;
        e->z += e->vz;
        e->width += e->grow;
        if (e->y < e->floor) {
            e->y = e->floor;
        }
        a.x = e->x;
        a.y = e->y;
        a.z = e->z;
        func_0020EB40(m);
        ((Pkt_b023_01E00080 *)(s32)&pkt)->count = 0x24;
        ((Pkt_b023_01E00080 *)(s32)&pkt)->tag = 9;
        ((Pkt_b023_01E00080 *)(s32)&pkt)->regs = ((u64)4 << 32) | 0x24242421;
        ((Pkt_b023_01E00080 *)(s32)&pkt)->pad = 0;
        pkt.c.r = e->r;
        pkt.c.g = e->g;
        pkt.c.b = e->b;
        pkt.c.q = 1.0f;
        age = e->total - e->life;
        fr = e->frame;
        if (e->flags & 8) {
            fr = ((age >> e->shift) & 3) + 2;
            if (age < 3) {
                fr = age;
            }
            if (e->life < 7) {
                fr = 7 - (e->life >> e->shift);
            }
        }
        tex.page = e->page;
        func_001020B0(&tex, fr, 0);
        func_00101D20(&pkt, &tex, texture);
        if (e->life < 16) {
            pkt.c.a = (e->a >> 4) * e->life;
        } else {
            pkt.c.a = e->a;
        }
        if (func_00205440(&a, m, &xy, &d) == 0) {
            continue;
        }
        if (func_00101600(&xy) == 0) {
            continue;
        }
        w = func_001018E0(e->width, d);
        pkt.v[0].p.z = pkt.v[1].p.z = pkt.v[2].p.z = pkt.v[3].p.z = xy.z;
        switch (e->flags & 0x30) {
        case 0x10:
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x20:
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        case 0x30:
            pkt.v[2].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[0].p.x = pkt.v[1].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[2].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[1].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        default:
            pkt.v[0].p.x = pkt.v[2].p.x = (u32)((f32)(u32)xy.x - w);
            pkt.v[1].p.x = pkt.v[3].p.x = (u32)((f32)(u32)xy.x + w);
            pkt.v[0].p.y = pkt.v[1].p.y = (u32)((f32)(u32)xy.y - w);
            pkt.v[2].p.y = pkt.v[3].p.y = (u32)((f32)(u32)xy.y + w);
            break;
        }
        func_002075F0(&pkt, target, (u32)d);
    }
    return 1;
}
#pragma optimization_level reset

/* shape b023:01E00990 (b023), 458 insns, 1 copy (-O2,p): the scene manager in b181:01E03830's form: sets up two
   units; frames 0xB6..0x133 spawn a gust puff at the model, odd frames 0x12D..0x1A3 scattered puffs at unit B; then
   the cue table and the puff draw (ShFx_Gus) */

typedef struct {
    u16 start;
    u16 end;
    u8 motion;
    u8 flags;
    u8 rate;
    u8 pad7;
    s32 w8;
    u8 c0[4];
    u8 c1[4];
} Cue_b023_01E00990;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 model;
    s32 model2;
    u8 pad14[0x18];
    u8 cam[4];
    s32 side;
    u8 pad34[8];
    Fx_b023_01E00080 fx[150];
    s8 tbl[0x100];
} Scene_b023_01E00990;

#pragma optimization_level 2

static s32 func_01E00990_b023(Scene_b023_01E00990 *g, s32 code) {
    extern s32 func_00207500(void);
    extern void func_00198948(void *, s32, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_00102330(void *, s32);
    extern void func_001F63E0(s32, u8 *);
    extern s32 func_00101C30(void *, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00101AD0(void *, s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern void func_001F71A0(s32, s32, s32, void *, void *, s32);
    extern Cue_b023_01E00990 D_01E01100_b023[];
    s32 ot;
    Vec4f v;
    u8 col[4];
    s32 i;
    Cue_b023_01E00990 *e;
    u16 t;
    s32 unit;
    s32 n;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x2914);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 1; i++) {
            func_00202BF0(5, i);
        }
        g->model = func_001F5560(g->unitA, 0x1C, 1);
        g->model2 = func_001F5560(g->unitA, 0x2E, 0);
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    switch (g->t) {
    case 0x1D5:
        col[2] = col[1] = col[0] = col[3] = 0x80;
        func_001F63E0(g->unitA, col);
        break;
    case 0x1D6:
        return 8;
    }
    if (g->t >= 0xB6 && g->t < 0x134) {
        n = func_00101C30(g->fx, 0x44, 0x96);
        if (n >= 0) {
            func_00101AD0(&g->fx[n], 0x8C, 0, 0xFF);
            g->fx[n].flags = ((func_0019A5C8() >> 4) & 3) << 4 | 4;
            g->fx[n].texkind = 0;
            g->fx[n].page = 1;
            g->fx[n].frame = ((func_0019A5C8() >> 4) + 2) & 3;
            g->fx[n].shift = 0;
            g->fx[n].r = ((func_0019A5C8() >> 4) & 0x3F) + 0x18;
            g->fx[n].g = ((func_0019A5C8() >> 4) & 0x3F) + 0x18;
            g->fx[n].b = 0x60;
            g->fx[n].a = 0xF0;
            g->fx[n].width = 100.0f;
            g->fx[n].grow = 4.0f;
            g->fx[n].floor = 0.0f;
            g->fx[n].gravity = 0.0f;
            func_001F5620(g->unitA, g->model, &v);
            g->fx[n].x = v.x;
            g->fx[n].y = v.y;
            g->fx[n].z = v.z;
            g->fx[n].vx = ((func_0019A5C8() >> 4) % 20 - 10) / 100.0f;
            g->fx[n].vy = ((func_0019A5C8() >> 4) % 20 - 10) / 100.0f;
            if (g->side == 0x8000) {
                g->fx[n].vz = -1.4f;
            } else {
                g->fx[n].vz = 1.4f;
            }
        }
    }
    if (g->t > 0x12C && g->t < 0x1A4) {
        while (g->t & 1) {
            func_001F5F90(g->unitB, &v);
            n = func_00101C30(g->fx, 0x44, 0x96);
            if (n < 0) {
                break;
            }
            func_00101AD0(&g->fx[n], 0x30, 0, 0xFF);
            g->fx[n].flags = ((func_0019A5C8() >> 4) & 3) << 4 | 4;
            g->fx[n].texkind = 0;
            g->fx[n].page = 1;
            g->fx[n].frame = ((func_0019A5C8() >> 4) + 2) & 3;
            g->fx[n].shift = 0;
            g->fx[n].r = ((func_0019A5C8() >> 4) & 0x3F) + 0x18;
            g->fx[n].g = ((func_0019A5C8() >> 4) & 0x3F) + 0x18;
            g->fx[n].b = 0x60;
            g->fx[n].a = 0xF0;
            g->fx[n].width = 240.0f;
            g->fx[n].grow = 25.0f;
            g->fx[n].floor = 0.0f;
            g->fx[n].gravity = 0.0f;
            func_001F5F90(g->unitB, &v);
            g->fx[n].x = v.x + ((func_0019A5C8() >> 4) % 0xA28 - 0x514) / 100.0f;
            g->fx[n].y = v.y + ((func_0019A5C8() >> 4) % 0xA28 - 0x514) / 100.0f;
            g->fx[n].z = v.z + ((func_0019A5C8() >> 4) % 0xA28 - 0x514) / 100.0f;
            g->fx[n].vz = 0.0f;
            g->fx[n].vx = 0.0f;
            g->fx[n].vy = 0.25f;
            break;
        }
    }
    t = g->t;
    for (e = D_01E01100_b023; e->start != 0; e++) {
        if (t >= (u16)e->start && t <= e->end) {
            if (e->flags & 0x80) {
                unit = func_001F5380();
            } else {
                unit = func_001F53A0();
            }
            if (e->flags & 0x40) {
                e->c0[3] = e->c1[3] = (t - *(u8 *)&e->start) * e->rate;
            }
            func_001F71A0(unit, e->motion, e->flags & 3, e->c0, e->c1, e->w8);
            break;
        }
    }
    func_01E00080_b023(g->fx, ot, 0xA0);
    if (g->t >= 0x12C && g->t <= 0x1C8) {
        return 6;
    }
    switch (g->t) {
    case 0x122:
        return 1;
    case 0x1C9:
        return 2;
    }
    return 0;
}
#pragma optimization_level reset
