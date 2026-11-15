#include "common.h"

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

static s32 func_01E00080_b096(Part_b010_01E04D20 *arg0, s32 id, s32 n) {
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

/* shape b096:01E00AA0 (b096), 963 insns, 1 copy (-O2,p): the b096 module main, written from the asm in
   b229:01E03C10's skeleton at -O2: code -3/-2 ends, code >= 0 clears the scene, takes both units and three joints;
   else counts the frame: 180/268/320 a 28-puff burst around the target, 420 ends; frames 88..264 three puffs drifting
   from the joint-0/1 midpoint, 2..27 six from joint 1, 40..71 three from joint 2 (the facing flips z); steps the
   puffs; returns 6 on frames 155..326, 2 on frame 327 (q[4] is never used: the frame keeps the slot) */

typedef struct Gus_b096_01E00AA0 {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 c[4];
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 x;
    f32 y;
    f32 z;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
} Gus_b096_01E00AA0;

typedef struct Scene_b096_01E00AA0 {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[3];
    u8 pad18[0x14];
    s32 cam[4];
    Gus_b096_01E00AA0 gus[0x1F4];
    s8 tbl[0x100];
} Scene_b096_01E00AA0;

#pragma optimization_level 2

static s32 func_01E00AA0_b096(Scene_b096_01E00AA0 *g, s32 code) {
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
    extern s32 func_01E00080_b096();
    s32 ot;
    Vec4f q[5];
    Vec4f v;
    s32 i;
    s32 k;
    f32 s;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x860C);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 0xD, 1);
        g->m[1] = func_001F5560(g->unitA, 0x10, 0);
        g->m[2] = func_001F5560(g->unitA, 0xC, 0);
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0xB4:
    case 0x10C:
    case 0x140:
        for (i = 0; i < 0x1C; i++) {
            k = func_00101C30(g->gus, 0x44, 0x1F4);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x30, (u8)(i * 2), 0xFF);
                g->gus[k].b5 = 0;
                g->gus[k].b4 = (func_0019A5C8() >> 4 & 3) << 4;
                g->gus[k].b8 = 0;
                g->gus[k].bB = 1;
                g->gus[k].bA = 5;
                g->gus[k].b9 = func_0019A5C8() >> 4 & 3;
                g->gus[k].c[2] = (func_0019A5C8() >> 4 & 0x3F) + 0x30;
                g->gus[k].c[1] = 0x10;
                g->gus[k].c[0] = (func_0019A5C8() >> 4 & 0x3F) + 0x30;
                g->gus[k].c[3] = (func_0019A5C8() >> 4 & 0x3F) + 0x50;
                g->gus[k].f10 = 250.0f;
                g->gus[k].f14 = 18.0f + (f32)((func_0019A5C8() >> 4) % 6 * 200 - 600) / 100.0f;
                g->gus[k].f18 = g->gus[k].f1C = 0.0f;
                g->gus[k].f30 = 1.0f;
                g->gus[k].f2C = g->gus[k].f34 = g->gus[k].f38 = g->gus[k].f3C = g->gus[k].f40 = 0.0f;
                g->gus[k].x = v.x + (f32)((func_0019A5C8() >> 4) % 2500 - 1250) / 100.0f;
                g->gus[k].y = v.y - 8.0f + (f32)((func_0019A5C8() >> 4) % 2500 - 1250) / 100.0f;
                g->gus[k].z = v.z + (f32)((func_0019A5C8() >> 4) % 2500 - 1250) / 100.0f;
            }
        }
        break;
    case 0x1A4:
        return 8;
    }
    if (g->t >= 0x58 && g->t < 0x109) {
        func_001F5620(g->unitA, g->m[2], &q[0]);
        func_001F5620(g->unitA, g->m[0], &q[1]);
        func_001F5620(g->unitA, g->m[1], &q[2]);
        for (i = 0; i < 3; i++) {
            k = func_00101C30(g->gus, 0x44, 0x1F4);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x80, 0, 0xFF);
                g->gus[k].b5 = 0;
                g->gus[k].b4 = (func_0019A5C8() >> 4 & 3) << 4;
                g->gus[k].b8 = 0;
                g->gus[k].bB = 1;
                g->gus[k].bA = 5;
                g->gus[k].b9 = func_0019A5C8() >> 4 & 3;
                g->gus[k].c[2] = (func_0019A5C8() >> 4 & 0x1F) + 0x30;
                g->gus[k].c[1] = 0x10;
                g->gus[k].c[0] = (func_0019A5C8() >> 4 & 0x1F) + 0x30;
                g->gus[k].c[3] = (func_0019A5C8() >> 4 & 0x3F) + 0x50;
                g->gus[k].f10 = 80.0f;
                g->gus[k].f14 = 10.0f + (f32)((func_0019A5C8() >> 4) % 4 * 200 - 400) / 100.0f;
                g->gus[k].f18 = g->gus[k].f1C = 0.0f;
                q[3].x = q[1].x + 0.5f * (q[2].x - q[1].x);
                q[3].y = q[1].y + 0.5f * (q[2].y - q[1].y);
                q[3].z = q[1].z + 0.5f * (q[2].z - q[1].z);
                g->gus[k].f2C = 0.3f * (q[3].x - q[0].x) + (f32)((func_0019A5C8() >> 4) % 40 - 20) / 100.0f;
                g->gus[k].f30 = (f32)((func_0019A5C8() >> 4) % 40 - 20) / 100.0f;
                g->gus[k].f34 = 0.3f * (q[3].z - q[0].z) + (f32)((func_0019A5C8() >> 4) % 40 - 20) / 100.0f;
                g->gus[k].x = q[0].x;
                g->gus[k].y = q[0].y;
                g->gus[k].z = q[0].z;
                g->gus[k].f38 = g->gus[k].f3C = g->gus[k].f40 = 0.0f;
            }
        }
    }
    if (g->t >= 2 && g->t < 0x1C) {
        func_001F5620(g->unitA, g->m[1], &q[0]);
        for (i = 0; i < 6; i++) {
            k = func_00101C30(g->gus, 0x44, 0x1F4);
            if (k >= 0) {
                func_00101AD0(&g->gus[k], 0x14, 0, 0xFF);
                g->gus[k].b5 = 0;
                g->gus[k].b4 = (func_0019A5C8() >> 4 & 3) << 4;
                g->gus[k].b8 = 0;
                g->gus[k].bB = 1;
                g->gus[k].bA = 5;
                g->gus[k].b9 = func_0019A5C8() >> 4 & 3;
                g->gus[k].c[2] = (func_0019A5C8() >> 4 & 0x3F) + 0x30;
                g->gus[k].c[1] = 0x10;
                g->gus[k].c[0] = (func_0019A5C8() >> 4 & 0x3F) + 0x30;
                g->gus[k].c[3] = 0x80;
                g->gus[k].f10 = 10.0f;
                g->gus[k].f14 = 4.0f;
                g->gus[k].f18 = g->gus[k].f1C = 0.0f;
                if (i & 1) {
                    g->gus[k].f2C = -0.2f + (f32)((func_0019A5C8() >> 4) % 10 - 5) / 100.0f;
                } else {
                    g->gus[k].f2C = 0.2f + (f32)((func_0019A5C8() >> 4) % 10 - 5) / 100.0f;
                }
                g->gus[k].f30 = (f32)((func_0019A5C8() >> 4) % 10 - 5) / 100.0f;
                g->gus[k].f3C = 0.01f;
                g->gus[k].f34 = -0.8f;
                g->gus[k].f40 = 0.05f;
                g->gus[k].x = q[0].x;
                g->gus[k].y = q[0].y;
                g->gus[k].z = 1.5f + q[0].z;
                if (g->cam[1] != 0x8000) {
                    g->gus[k].f34 *= -1.0f;
                    g->gus[k].f40 *= -1.0f;
                    g->gus[k].z = q[0].z - 1.5f;
                }
            }
        }
    }
    if (g->t >= 0x28 && g->t < 0x48) {
        func_001F5620(g->unitA, g->m[2], &q[0]);
        for (i = 0; i < 3; i++) {
            k = func_00101C30(g->gus, 0x44, 0x1F4);
            if (k >= 0) {
                s = 20.0f + (f32)((func_0019A5C8() >> 4) % 6 * 200 - 600) / 100.0f;
                func_00101AD0(&g->gus[k], (u8)(s32)s, 0, 0xFF);
                g->gus[k].b4 = 0;
                g->gus[k].b8 = 0;
                g->gus[k].bB = 1;
                g->gus[k].b9 = func_0019A5C8() >> 4 & 3;
                g->gus[k].bA = 5;
                g->gus[k].c[2] = (func_0019A5C8() >> 4 & 0x1F) + 0x30;
                g->gus[k].c[1] = 0x10;
                g->gus[k].c[0] = (func_0019A5C8() >> 4 & 0x1F) + 0x30;
                g->gus[k].c[3] = (func_0019A5C8() >> 4 & 0x3F) + 0x50;
                g->gus[k].f10 = 100.0f;
                g->gus[k].f14 = 8.0f;
                g->gus[k].f18 = g->gus[k].f1C = 0.0f;
                q[1].x = (f32)((func_0019A5C8() >> 4) % 5 * 200 - 500) / 100.0f;
                q[1].y = 2.0f + (f32)((func_0019A5C8() >> 4) % 2 * 200 - 200) / 100.0f;
                q[1].z = 3.0f + (f32)((func_0019A5C8() >> 4) % 3 * 200 - 300) / 100.0f;
                if (g->cam[1] == 0x8000) {
                    q[1].z *= -1.0f;
                }
                g->gus[k].x = q[0].x + q[1].x;
                g->gus[k].y = q[0].y + q[1].y;
                g->gus[k].z = q[0].z + q[1].z;
                g->gus[k].f2C = q[1].x / s;
                g->gus[k].f30 = q[1].y / s;
                g->gus[k].f34 = q[1].z / s;
                g->gus[k].f38 = g->gus[k].f3C = g->gus[k].f40 = 0.0f;
            }
        }
    }
    func_01E00080_b096(g->gus, ot, 0x1F4);
    if (g->t >= 0x9B && g->t < 0x147) {
        return 6;
    }
    switch (g->t) {
    case 0x147:
        return 2;
    }
    return 0;
}

#pragma optimization_level reset
