#include "common.h"
#include "mod/c500.c"

/* shape c500:01E027E0 (c500), 623 insns, 1 copy: c500 scene: code >= 0 sets up three rings, a 60-point spark cloud,
   six lightning bolts on six nodes, a billboard and the fire tail; each tick draws the billboard and tail until flag
   0x1E, then the bolts, sparks and rings growing and fading; 2 on tick 12, 8 when the 30-tick timer runs out */

typedef struct {
    u8 b, g, r, a;
} Col_c500_01E027E0;

typedef struct {
    f32 s[3];
    u8 padC[8];
    s32 rot;
    u8 pad18[8];
    Vec4f pos;
    u8 pad30[0x40];
} Node_c500_01E027E0;

typedef struct {
    Vec4f hist[8];
    s32 flags;
    f32 width;
    Col_c500_01E027E0 color;
    u8 padFC[0x14];
} Tail_c500_01E027E0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c500_01E027E0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c500_01E027E0;

typedef struct {
    f32 x, y, z;
} Pt_c500_01E027E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c500_01E027E0 color;
    f32 size;
    f32 u, v, w, h;
    Pt_c500_01E027E0 pts[60];
} Spark_c500_01E027E0;

typedef struct {
    s32 texture;
    s32 flags;
    Col_c500_01E027E0 color;
    u8 padC[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c500_01E027E0;

typedef struct {
    s32 texture;
    Col_c500_01E027E0 color;
    u8 pad8[4];
    s16 n;
    u8 padE[2];
    s16 u, v, w, h;
    s16 x18;
    s16 x1A;
    u8 pad1C[4];
    Vec4f p0;
    Vec4f pts[5];
} Elec_c500_01E027E0;

typedef struct {
    Node_c500_01E027E0 n0;
    Tail_c500_01E027E0 tail;
    Node_c500_01E027E0 n1;
    Mdl_c500_01E027E0 mdl;
    Bb_c500_01E003D0 bb;
    Node_c500_01E027E0 n2;
    Spark_c500_01E027E0 spark;
    Node_c500_01E027E0 n3;
    Ring_c500_01E027E0 ring[3];
    Node_c500_01E027E0 sub[6];
    Elec_c500_01E027E0 elec[6];
    f32 v[3];
    u8 pad17DC[4];
    Col_c500_01E027E0 color;
    s32 timer;
    s32 tick;
    s32 code;
    s32 flags;
    u8 pad17F4[0xC];
} Scene_c500_01E027E0;

static s32 func_01E027E0_c500(s32 arg0, s32 code) {
    Scene_c500_01E027E0 *g = (Scene_c500_01E027E0 *)arg0;
    extern void func_00103260(void *, s32);
    extern void func_001F53B0();
    s32 tex __attribute__((aligned(16)));
    s32 ot;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    ot = (s32)func_00207500();
    if (code >= 0) {
        func_00195108((s32)g, 0x1800);
        func_00103890(&g->n0);
        func_00103890(&g->n1);
        func_00103890(&g->n2);
        func_00103890(&g->n3);
        for (k = 0; k < 6; k++) {
            func_00103890(&g->sub[k]);
        }
        g->flags = 0;
        g->code = code;
        g->timer = 30;
        g->tick = 0;
        g->v[0] = 1.1f;
        g->v[1] = 1.1f;
        g->v[2] = 1.1f;
        g->color.r = g->color.g = g->color.b = g->color.a = 0x80;
        func_00103260(&tex, 0xF);
        g->ring[0].flags = 0x8000;
        g->ring[0].u = 0x8E;
        g->ring[0].v = 0;
        g->ring[0].w = 0x20;
        g->ring[0].h = 0x40;
        g->ring[0].color.r = 0x80;
        g->ring[0].color.g = 0x40;
        g->ring[0].color.b = 0x80;
        g->ring[0].color.a = 0x60;
        { f32 r = 0.1f; func_01E01360_c500((Ring_b001_01E035A0 *)&g->ring[0], tex, r, 34.0f, 0.0f, 28.0f); }
        g->ring[1].flags = 0x8000;
        g->ring[1].u = 0x8E;
        g->ring[1].v = 0;
        g->ring[1].w = 0x20;
        g->ring[1].h = 0x40;
        g->ring[1].color.r = 0x80;
        g->ring[1].color.g = 0x40;
        g->ring[1].color.b = 0x80;
        g->ring[1].color.a = 0x60;
        { f32 r = 0.0f; func_01E01360_c500((Ring_b001_01E035A0 *)&g->ring[1], tex, 0.1f, 37.0f, r, 21.0f); }
        g->ring[2].flags = 0x8000;
        g->ring[2].u = 0x8E;
        g->ring[2].v = 0;
        g->ring[2].w = 0x20;
        g->ring[2].h = 0x40;
        g->ring[2].color.r = 0x80;
        g->ring[2].color.g = 0x40;
        g->ring[2].color.b = 0x80;
        g->ring[2].color.a = 0x60;
        { f32 r = 14.0f; func_01E01360_c500((Ring_b001_01E035A0 *)&g->ring[2], tex, 0.1f, 40.0f, 0.0f, r); }
        g->spark.texture = tex;
        g->spark.size = 2.5f;
        for (i = 0; i < 60; i++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.pts[i].x = func_0019A5C8() % 100 - 50;
                g->spark.pts[i].z = func_0019A5C8() % 50;
                g->spark.pts[i].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.pts[i].x = func_0019A5C8() % 50 - 25;
                g->spark.pts[i].y = func_0019A5C8() % 25;
                g->spark.pts[i].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->spark.flags = 0;
        g->spark.u = 0.8125f;
        g->spark.v = 0.25f;
        g->spark.w = 0.125f;
        g->spark.h = 0.125f;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x40;
        g->spark.color.b = 0x80;
        g->spark.color.a = 0x80;
        for (i = 0; i < 6; i++) {
            g->elec[i].u = 10;
            g->elec[i].v = 0;
            g->elec[i].w = 0x2C;
            g->elec[i].h = 0x80;
            g->elec[i].x18 = 10;
            g->elec[i].x1A = 0;
            g->elec[i].p0.w = 13.75f;
            g->elec[i].color.r = 0xA0;
            g->elec[i].color.g = 0xA0;
            g->elec[i].color.b = 0x60;
            g->elec[i].color.a = 0x80;
            g->elec[i].texture = tex;
            g->elec[i].p0.x = g->elec[i].p0.y = g->elec[i].p0.z = 0.0f;
            for (j = 0; j < 5; j++) {
                if (j == 4) {
                    g->elec[i].pts[j].x = func_0019A5C8() % 10 - 5;
                    g->elec[i].pts[j].y = func_0019A5C8() % 10 - 5;
                } else {
                    g->elec[i].pts[j].x = func_0019A5C8() % 10 - 5;
                    g->elec[i].pts[j].y = func_0019A5C8() % 20;
                }
                g->elec[i].pts[j].z = 8.0f * (f32)(j + 1);
            }
            g->elec[i].n = func_0019A5C8() % 6 + 5;
        }
        func_00103260(&tex, 3);
        g->mdl.flags = 1;
        g->mdl.f30 = 1.0f;
        g->mdl.color.r = 0x80;
        g->mdl.color.g = 0x80;
        g->mdl.color.b = 0x80;
        g->mdl.color.a = 0x80;
        g->mdl.r[0] = 0x40;
        g->mdl.r[1] = 0;
        g->mdl.r[2] = 0x20;
        g->mdl.r[3] = 0x40;
        g->mdl.r[4] = 0x40;
        g->mdl.r[5] = 0;
        g->mdl.r[6] = 0x80;
        g->mdl.r[7] = 0x40;
        g->mdl.h48 = 0;
        g->mdl.h4A = 1;
        g->mdl.h4E = 2;
        g->mdl.h52 = 999;
        g->mdl.h50 = 0;
        g->mdl.h4C = g->mdl.h4E - 1;
        func_01E003D0_c500((Src_c500_01E003D0 *)&g->mdl, &g->bb, tex, 25.0f);
        func_001F53B0(2, &g->n0.pos);
        func_001F53B0(0, &g->n1.pos);
        func_001F53B0(0, &g->n2.pos);
        func_001F53B0(0, &g->n3.pos);
        for (k = 0; k < 6; k++) {
            func_001F53B0(0, &g->sub[k].pos);
            g->sub[k].rot = k * 0x2AAA + (func_0019A5C8() % 0x2000 - 0x1000);
        }
        g->n1.pos.y = 200.0f;
        g->n2.s[0] = g->n2.s[1] = g->n2.s[2] = 0.1f;
        g->n2.pos.y = 3.0f;
        g->tail.flags = 0;
        g->tail.color.r = 0xA0;
        g->tail.color.g = 0xA0;
        g->tail.color.b = 0x60;
        g->tail.color.a = 0x40;
        for (m = 0; m < 8; m++) {
            g->tail.hist[m].x = g->n1.pos.x;
            g->tail.hist[m].y = g->n1.pos.y;
            g->tail.hist[m].z = g->n1.pos.z;
        }
        g->tail.width = 5.0f;
        return 0;
    }
    func_001038D0(&g->n0);
    func_001039A0(&g->n1);
    func_001039A0(&g->n2);
    func_001038D0(&g->n3);
    for (k = 0; k < 6; k++) {
        func_001038D0(&g->sub[k]);
    }
    if (!func_00104520(g->flags, 0x1E)) {
        func_01E00630_c500(ot, (Obj_c500_01E00630 *)&g->mdl, (Strip_c500_01E00630 *)&g->bb, (Cam_c500_01E00630 *)&g->n1);
        func_01E01B10_c500(ot, (Tail_c500_01E01B10 *)&g->tail, (Cam_c500_01E01B10 *)g, (Vec_c500_01E01B10 *)&g->n1.pos);
    } else {
        for (i = 0; i < 6; i++) {
            if (g->elec[i].color.a < 0x60) {
                g->elec[i].u = g->elec[i].x18 + g->elec[i].w;
            } else if (g->elec[i].color.a < 0x40) {
                g->elec[i].u = g->elec[i].x18 + g->elec[i].w * 2;
            }
            func_01E02310_c500(ot, (Elec_c500_01E02310 *)&g->elec[i], (Cam_c500_01E02310 *)&g->sub[i]);
            if (g->elec[i].n) {
                g->elec[i].n--;
            }
            func_00103470(&g->elec[i].color.a, 0, 2);
        }
        if (g->n2.s[0] < 1.0f) {
            g->n2.s[0] = g->n2.s[1] = g->n2.s[2] += 0.2f;
        }
        func_01E00D80_c500(ot, (Spark_b013_01E010C0 *)&g->spark, (Cam_b013_01E010C0 *)&g->n2, (s32)g->v);
        func_00103470(&g->spark.color.a, 0, 8);
        if (g->n3.s[0] < 1.0f) {
            g->n3.s[0] = g->n3.s[1] = g->n3.s[2] += 0.2f;
        } else {
            g->n3.s[0] = g->n3.s[1] = g->n3.s[2] += 0.05f;
        }
        func_01E01620_c500(ot, (Ring_b001_01E03860 *)&g->ring[0], (Cam_b001_01E03860 *)&g->n3);
        func_01E01620_c500(ot, (Ring_b001_01E03860 *)&g->ring[1], (Cam_b001_01E03860 *)&g->n3);
        func_01E01620_c500(ot, (Ring_b001_01E03860 *)&g->ring[2], (Cam_b001_01E03860 *)&g->n3);
        func_00103470(&g->ring[0].color.a, 0, 8);
        func_00103470(&g->ring[1].color.a, 0, 8);
        func_00103470(&g->ring[2].color.a, 0, 8);
    }
    { f32 r = 0.0f; if (!func_00103540(&g->n1.pos.y, r, 20.0f)) {
        if (!func_00104520(g->flags, 0x1E)) {
            func_01E00270_c500(ot, (Src_b000_01E00400 *)&g->color);
        }
        g->flags |= 0x40000000;
    } }
    g->tick++;
    g->timer--;
    if (g->tick == 12) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
