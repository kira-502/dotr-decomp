#include "common.h"

/* shape c516:01E03130 (c516), 805 insns, 1 copy: c516 scene manager: code >= 0 sets up six after-image trails (random
   start ticks), a grey board and its point, the drifting-colour board with two points, and six lights, rings,
   outline boards and cameras (scale 0.1); else turns the six cameras on a 180 circle, fades the boards, runs each
   trail's tick script (frame tables at D_01E03F40/D_01E03F70, mask bits i and i + 20) and draws the shown
   lights/rings/outlines, drifts the board colour every 10 ticks; returns 8 when the timer runs out */

typedef struct Rot_c516_01E03130 {
    s32 x, y, z, w;
} Rot_c516_01E03130;

typedef struct Crd_c516_01E03130 {
    Vec4f scale;
    Rot_c516_01E03130 rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c516_01E03130;

typedef struct Light_c516_01E03130 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[8];
    Vec4f p[4];
    Rot_c516_01E03130 rot[64];
} Light_c516_01E03130;

typedef struct Ring_c516_01E03130 {
    s32 type;
    s32 flags;
    u8 b, g, r, a;
    u8 pad0C[4];
    s16 u, v, w, h;
    u8 pad18[0x3E8];
} Ring_c516_01E03130;

typedef struct Board_c516_01E03130 {
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    u8 pad10[0x20];
    f32 size;
    u8 b, g, r, a;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[0xC];
} Board_c516_01E03130;

typedef struct Part_c516_01E03130 {
    s32 texture;
    s32 flags;
    f32 scale;
    u8 b, g, r, a;
    f32 x, y, z;
    u8 pad1C[4];
} Part_c516_01E03130;

typedef struct Fx_c516_01E03130 {
    s32 kind;
    s32 pad4;
    s32 type;
    u8 padC[0x94];
} Fx_c516_01E03130;

typedef struct Trail_c516_01E03130 {
    f32 x, y, z;
    u8 a;
    u8 frame;
    s16 h;
} Trail_c516_01E03130;

typedef struct After_c516_01E03130 {
    s32 texture;
    s32 flags;
    u8 b, g, r, a;
    f32 scale;
    f32 x, y, z;
    s32 h1C;
    s16 u, v, w, h;
    s16 u0, v0, cols, h2E;
    Trail_c516_01E03130 t[4];
    f32 sx, sy, sz;
    u8 pad7C[4];
    s32 tick;
    s16 h84;
    s16 h86;
    s16 h88;
    s16 count;
    u8 pad8C[4];
} After_c516_01E03130;

typedef struct Scene_c516_01E03130 {
    Crd_c516_01E03130 cam;
    Crd_c516_01E03130 crd[6];
    Light_c516_01E03130 light[6];
    Ring_c516_01E03130 ring[6];
    Board_c516_01E03130 board;
    Part_c516_01E03130 part[2];
    Fx_c516_01E03130 fx[6];
    Board_c516_01E03130 model[6];
    Board_c516_01E03130 board2;
    Part_c516_01E03130 part2;
    After_c516_01E03130 after[6];
    s32 t;
    s32 timer;
    s32 code;
    s32 mask;
    s32 drift[3];
    u8 pad3FEC[4];
} Scene_c516_01E03130;

typedef struct Tbl_c516_01E03130 {
    s8 v[45];
} Tbl_c516_01E03130;

static s32 func_01E03130_c516(s32 arg0, s32 code) {
    Scene_c516_01E03130 *g = (Scene_c516_01E03130 *)arg0;
    extern Tbl_c516_01E03130 D_01E03F40_c516;
    extern Tbl_c516_01E03130 D_01E03F70_c516;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_00103260(s32 *, s32);
    Tbl_c516_01E03130 tbl;
    Tbl_c516_01E03130 tbl2;
    s32 tx[4];
    s32 ot;
    s32 i;
    s32 j;
    s32 t;

    ot = func_00207500();
    tbl = D_01E03F40_c516;
    tbl2 = D_01E03F70_c516;
    if (code >= 0) {
        func_00195108(g, 0x3FF0);
        func_00103890(&g->cam);
        for (i = 0; i < 6; i++) {
            func_00103890(&g->crd[i]);
        }
        g->timer = 0x50;
        g->t = 0;
        g->code = code;
        g->mask = 0;
        func_00103260(tx, 0xD);
        for (j = 0; j < 6; j++) {
            g->after[j].texture = tx[0];
            g->after[j].flags = 0x80083;
            g->after[j].x = 180.0f * func_0020B480(j * 0x2AAA);
            g->after[j].y = 180.0f * func_0020B550(j * 0x2AAA);
            g->after[j].y -= 150.0f;
            g->after[j].z = 0.0f;
            g->after[j].h1C = 0;
            g->after[j].sx = g->after[j].sy = g->after[j].sz = 1.0f;
            g->after[j].u = 0;
            g->after[j].v = 0;
            g->after[j].u0 = 0;
            g->after[j].v0 = 0;
            g->after[j].w = 0x14;
            g->after[j].h = 0x20;
            g->after[j].cols = 0x50;
            g->after[j].h2E = 0x40;
            g->after[j].scale = 50.0f;
            g->after[j].h84 = 0;
            g->after[j].h88 = 8;
            g->after[j].count = 1;
            g->after[j].r = 0x80;
            g->after[j].g = 0x80;
            g->after[j].b = 0x80;
            g->after[j].a = 0;
            g->after[j].tick = func_0019A5C8() % 15 - 30;
            for (i = 0; i < g->after[j].count + 1; i++) {
                if (g->after[j].a == 0) {
                    g->after[j].t[i].a = 0;
                } else {
                    g->after[j].t[i].a = g->after[j].a / (i + 1);
                }
                g->after[j].t[i].x = g->after[j].x;
                g->after[j].t[i].y = g->after[j].y;
                g->after[j].t[i].z = g->after[j].z;
                g->after[j].t[i].h = 0;
                g->after[j].t[i].frame = 0;
                g->after[j].h86 = g->after[j].h88 - 1;
            }
        }
        g->board2.size = 1.0f;
        g->board2.flags = 0x80003;
        g->board2.u = 0;
        g->board2.v = 0x40;
        g->board2.w = 0x14;
        g->board2.h = 0x20;
        g->board2.u0 = 0;
        g->board2.v0 = 0x40;
        g->board2.tw = 0x50;
        g->board2.th = 0x40;
        g->board2.h48 = 0;
        g->board2.h4A = 0;
        g->board2.h4E = 8;
        g->board2.h52 = 999;
        g->board2.h50 = 0;
        g->board2.h4C = g->board2.h4E - 1;
        g->board2.r = 0x80;
        g->board2.g = 0x80;
        g->board2.b = 0x80;
        g->board2.a = 0;
        t = tx[0];
        g->part2.z = 0.0f;
        g->part2.y = 0.0f;
        g->part2.x = 0.0f;
        g->part2.scale = 100.0f;
        g->part2.texture = t;
        g->part2.r = 0x80;
        g->part2.g = 0x80;
        g->part2.b = 0x80;
        g->part2.a = 0x80;
        func_00103260(tx, 0xF);
        g->board.size = 1.0f;
        g->board.flags = 0x80403;
        g->board.u = 0x80;
        g->board.v = 0x80;
        g->board.w = 0x80;
        g->board.h = 0x40;
        g->board.u0 = 0x80;
        g->board.v0 = 0x80;
        g->board.tw = 0x100;
        g->board.th = 0x100;
        g->board.h48 = 0;
        g->board.h4A = 0;
        g->board.h4E = 1;
        g->board.h52 = 999;
        g->board.h50 = 0;
        g->board.h4C = g->board.h4E - 1;
        g->board.r = 0x70;
        g->board.g = 0x40;
        g->board.b = 0x80;
        g->board.a = 0;
        t = tx[0];
        g->part[0].z = 0.0f;
        g->part[0].y = 0.0f;
        g->part[0].x = 0.0f;
        g->part[0].scale = 500.0f;
        g->part[0].texture = t;
        g->part[0].r = 0x80;
        g->part[0].g = 0x80;
        g->part[0].b = 0x80;
        g->part[0].a = 0x80;
        t = tx[0];
        g->part[1].z = 0.0f;
        g->part[1].y = 0.0f;
        g->part[1].x = 0.0f;
        g->part[1].scale = 500.0f;
        g->part[1].texture = t;
        g->part[1].r = 0x80;
        g->part[1].g = 0x80;
        g->part[1].b = 0x80;
        g->part[1].a = 0x80;
        g->part[0].z -= 1.0f;
        g->part[1].z -= 1.0f;
        for (i = 0; i < 6; i++) {
            g->light[i].flags = 0x80801;
            g->light[i].u = 0x8E;
            g->light[i].v = 0;
            g->light[i].w = 0x22;
            g->light[i].h = 0x40;
            g->light[i].r = 0x80;
            g->light[i].g = 0x40;
            g->light[i].b = 0x80;
            g->light[i].a = 0x20;
            func_01E029C0_c516((Obj_b000_01E032C0 *)&g->light[i], tx[0], 8.0f);
            g->ring[i].flags = 0x20080000;
            g->ring[i].u = 0x8E;
            g->ring[i].v = 0;
            g->ring[i].w = 0x20;
            g->ring[i].h = 0x40;
            g->ring[i].r = 0x80;
            g->ring[i].g = 0x40;
            g->ring[i].b = 0x80;
            g->ring[i].a = 0;
            {
                extern s32 c516_01E02210(void *, s32, f32, f32, f32, f32);
                f32 z = 0.0f;
                c516_01E02210(&g->ring[i], tx[0], 60.0f, 65.0f, z, z);
            }
            g->model[i].flags = 0x80401;
            g->model[i].u = 0x80;
            g->model[i].v = 0;
            g->model[i].w = 0x20;
            g->model[i].h = 0x20;
            g->model[i].u0 = 0xB0;
            g->model[i].v0 = 0x20;
            g->model[i].tw = 0x100;
            g->model[i].th = 0x100;
            g->model[i].size = 1.0f;
            g->model[i].r = 0x80;
            g->model[i].g = 0x40;
            g->model[i].b = 0x80;
            g->model[i].a = 0x20;
            g->model[i].h48 = 0;
            g->model[i].h4A = 0;
            g->model[i].h4C = 0;
            g->model[i].h4E = 1;
            g->model[i].h50 = 0;
            g->model[i].h52 = 999;
            g->fx[i].type = 1;
            {
                extern s32 c516_01E009B0(void *, void *, s32, f32);
                c516_01E009B0(&g->model[i], &g->fx[i], tx[0], 100.0f);
            }
            g->crd[i].scale.x = g->crd[i].scale.y = g->crd[i].scale.z = 0.1f;
        }
        return 0;
    }
    /* best so far (804/805): the original sets up this loop as counter, &crd[k] then the angle, all three
       strength-reduced; an explicit angle variable lands its zero one instruction early, i * 0x2AAA gets the
       angle and pointer registers swapped */
    func_00103920(&g->cam, 0.0f, 0.0f);
    j = 0;
    i = 0;
    do {
        func_00103920(&g->crd[j], 180.0f * func_0020B480(i), 180.0f * func_0020B550(i));
        j++;
        i += 0x2AAA;
    } while (j < 6);
    if (g->board2.h52 == 0 || g->board2.h52 == 999) {
        func_01E00120_c516(ot, (Spr_b000_01E02A30 *)&g->board2, (Part_b000_01E02A30 *)&g->part2,
                           (Cam_b000_01E02A30 *)g);
    }
    if (g->t < 10) {
        func_001032C0(&g->board2.a, 0x80, 0x10);
        func_001032C0(&g->board.a, 0x20, 4);
    }
    if (g->t > 0x3C) {
        func_00103470(&g->board2.a, 0, 0x10);
        func_00103470(&g->board.a, 0, 4);
    }
    for (i = 0; i < 6; i++) {
        if (g->after[i].tick >= 0) {
            g->after[i].count = 1;
            if (g->after[i].tick == 0) {
                g->mask |= 1 << i;
            }
            if (g->after[i].tick < 10) {
                g->after[i].count = 3;
                g->after[i].y += 15.0f;
                func_001032C0(&g->after[i].a, 0x60, 0x10);
            }
            if (g->after[i].tick == 10) {
                g->model[i].a = 0x80;
                g->light[i].a = 0x40;
                g->ring[i].a = 0x30;
                g->mask &= ~(1 << i);
                g->light[i].flags &= ~0x800;
                g->model[i].flags &= ~0x400;
                g->crd[i].scale.x = g->crd[i].scale.y = g->crd[i].scale.z = 0.1f;
            }
            if (g->after[i].tick == 15) {
                g->mask |= 1 << i;
            }
            if (g->after[i].tick > 0x22) {
                g->after[i].count = 3;
                func_00103540(&g->after[i].sx, 0.0f, 0.1f);
                func_00103390(&g->after[i].sy, 2.0f, 0.2f);
                g->after[i].y -= 10.0f;
                for (j = 0; j < g->after[i].count + 1; j++) {
                    g->after[i].t[j].y -= 10.0f;
                }
                func_00103470(&g->after[i].a, 0, 8);
            }
            if (func_00104520(g->mask, i + 20) == 0) {
                g->after[i].t[0].frame = tbl.v[g->after[i].tick];
                g->after[i].t[1].frame = tbl2.v[g->after[i].tick];
                if (tbl.v[g->after[i].tick] == 9) {
                    g->mask |= 1 << (i + 20);
                }
                func_01E018D0_c516(ot, (Spr_c516_01E018D0 *)&g->after[i], (Cam_c516_01E018D0 *)g);
            }
        }
        g->after[i].tick++;
        if (func_00104520(g->mask, i)) {
            func_01E00CF0_c516(ot, (Model_b013_01E004E0 *)&g->model[i], (Fx_b013_01E004E0 *)&g->fx[i],
                               (Cam_b013_01E004E0 *)&g->crd[i]);
            func_01E024D0_c516(ot, (Ring_b001_01E03860 *)&g->ring[i], (Cam_b001_01E03860 *)&g->crd[i]);
            func_01E02B20_c516(ot, (Spr_b000_01E03420 *)&g->light[i], (Cam_b000_01E03420 *)&g->crd[i]);
            if (g->crd[i].scale.x <= 1.0f) {
                g->crd[i].scale.x += 0.4f;
                g->crd[i].scale.y += 0.4f;
                g->crd[i].scale.z += 0.4f;
            } else {
                g->crd[i].scale.x += 0.005f;
                g->crd[i].scale.y += 0.005f;
                g->crd[i].scale.z += 0.005f;
                func_00103470(&g->model[i].a, 0, 6);
                func_00103470(&g->light[i].a, 0, 3);
                func_00103470(&g->ring[i].a, 0, 3);
            }
        }
        for (j = 0; j < 64; j++) {
            g->light[i].rot[j].x += 0x80;
            g->light[i].rot[j].y += 0x80;
            g->light[i].rot[j].z += 0x80;
        }
    }
    g->part[0].x = 150.0f * func_0020B550(g->t << 9);
    g->part[1].x = 150.0f * func_0020B550(-g->t << 9);
    if (g->t % 10 == 0) {
        g->drift[0] = func_0019A5C8() % 32 - 16;
        g->drift[1] = func_0019A5C8() % 32 - 16;
        g->drift[2] = func_0019A5C8() % 32 - 16;
    }
    if (g->drift[0] > 0) {
        func_001032C0(&g->board.r, 0xFF, g->drift[0]);
    } else if (g->drift[0] < 0) {
        func_00103470(&g->board.r, 0x80, (u8)-g->drift[0]);
    }
    if (g->drift[1] > 0) {
        func_001032C0(&g->board.g, 0xFF, g->drift[1]);
    } else if (g->drift[1] < 0) {
        func_00103470(&g->board.g, 0x80, (u8)-g->drift[1]);
    }
    if (g->drift[2] > 0) {
        func_001032C0(&g->board.b, 0xFF, g->drift[2]);
    } else if (g->drift[2] < 0) {
        func_00103470(&g->board.b, 0x80, (u8)-g->drift[2]);
    }
    if (g->board.h52 == 0 || g->board.h52 == 999) {
        func_01E00120_c516(ot, (Spr_b000_01E02A30 *)&g->board, (Part_b000_01E02A30 *)&g->part[0],
                           (Cam_b000_01E02A30 *)g);
        func_01E00120_c516(ot, (Spr_b000_01E02A30 *)&g->board, (Part_b000_01E02A30 *)&g->part[1],
                           (Cam_b000_01E02A30 *)g);
    }
    g->t++;
    if (--g->timer <= 0) {
        return 8;
    }
    return 0;
}
