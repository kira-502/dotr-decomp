#include "common.h"

/* shape b215:01E02E50 (b215), 696 insns, 1 copy: b215 scene manager (130 slots): setup (six joints and a camera, one
   type-4 and two type-5 textures, s8 jitter tables, two 36-entry random s16 0..7 tables, a 40x40 grid of
   rand()%80/10, 2x40 random vectors /10, 2x36 random angles and 10s); step 01E01090 and every slot (counting the
   01E02540/01E02B70 ones, then 01E04520 if any), draw five kinds of slot; scene code from the timer (1 / 4 / 2 at
   0x8A / 0x104 / 0xFF, 6 in 0x95..0xF9, 8 once the 270-frame countdown runs out). Needs func_01E00BE0_b215 to take a
   third unused s32 (the asm passes a3 = 0, as in its b152 twin) */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[0xE];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b215_01E02E50;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[0x64];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        s32 rm[4];
        Rect_b152_01E014F0 rc;
    } u94;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b215_01E02E50 fx[130];
    u8 pad3B80[0x40];
    Vec4f vv[2][40];
    u8 pad40C0[0x9FD0 - 0x40C0];
    s32 tex[2];
    u8 pad9FD8[0x18];
    s32 count;
    u8 pad9FF4[8];
    s32 ot;
    u8 padA000[0x28];
    s16 j[6];
    u8 padA034[4];
    s16 cam;
    u8 padA03A[0xE];
    s16 grid[50][50];
    s16 h1[36];
    s16 h2[36];
    s16 ra[40][40];
    s16 rb[40][40];
    s16 rc[40][40];
    s16 rd[40][40];
    u8 padE660[0x12];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 crd[0x178];
} Scene_b215_01E02E50;

static s32 func_01E02E50_b215(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern void func_001F5620(s32, s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern s32 func_0019A5C8(void);
    extern s32 func_01E01A70_b215();
    extern void b215_01E01090();
    extern void b215_01E00D30();
    extern void b215_01E03AC0();
    extern void b215_01E04010();
    extern void b215_01E04520();
    Scene_b215_01E02E50 *g = (Scene_b215_01E02E50 *)arg0;
    s16 m;
    s16 n;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    Rect_b152_01E014F0 rc;
    Rect_b152_01E014F0 rc2;
    s32 ang[4];
    s32 i;
    s16 k;
    s16 a;

    m = 0;
    k = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0xE9F0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 270;
        g->j[0] = func_001F5560(func_001F53A0(), 1, 1);
        g->j[1] = func_001F5560(func_001F53A0(), 0x34, 0);
        g->j[2] = func_001F5560(func_001F53A0(), 0x35, 0);
        g->j[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->j[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->j[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 0; k < 36; k++) {
            g->h1[k] = func_0019A5C8() % 8;
        }
        for (k = 0; k < 36; k++) {
            g->h2[k] = func_0019A5C8() % 8;
        }
        for (a = 0; a < 40; a++) {
            for (k = 0; k < 40; k++) {
                g->grid[a][k] = func_0019A5C8() % 80;
                g->grid[a][k] = g->grid[a][k] / 10;
            }
        }
        for (a = 0; a < 2; a++) {
            for (k = 0; k < 40; k++) {
                g->vv[a][k].x = func_0019A5C8() % 30 - 15;
                g->vv[a][k].y = func_0019A5C8() % 30 - 15;
                g->vv[a][k].z = func_0019A5C8() % 30 - 15;
                g->vv[a][k].x /= 10.0f;
                g->vv[a][k].y /= 10.0f;
                g->vv[a][k].z /= 10.0f;
            }
        }
        for (a = 0; a < 2; a++) {
            for (k = 0; k < 36; k++) {
                g->ra[a][k] = func_0019A5C8() % 360;
                g->rb[a][k] = func_0019A5C8() % 360;
                g->rc[a][k] = func_0019A5C8() % 360;
                g->rd[a][k] = 10;
            }
        }
        return 0;
    }
    b215_01E01090(g, 0);
    for (n = 0; n < 130; n++) {
        if (g->fx[n].used != 0) {
            if (g->fx[n].fn != NULL) {
                if (g->fx[n].fn != (s32 (*)())func_01E02540_b215 && g->fx[n].fn != (s32 (*)())func_01E02B70_b215) {
                    g->fx[n].fn(g, &g->fx[n]);
                } else {
                    m++;
                }
            }
        }
    }
    for (a = 0; a < 130; a++) {
        if (g->fx[a].used != 0) {
            k++;
            if (g->fx[a].fn == (s32 (*)())func_01E01500_b215) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[a].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm;
                g->hB8 = 1;
                g->hBE = 0;
                func_001F5620(func_001F53A0(), g->j[0], &v);
                v.y -= 2.5f;
                b215_01E03AC0(g, &g->fx[a], 0x20, &v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E01A70_b215) {
                g->tex88 = g->tex[0];
                func_00106080(rm2, 0x14, g->fx[a].h56, NULL);
                *(Vec4f *)g->u94.rm = *(Vec4f *)rm2;
                g->hB8 = 1;
                g->hBE = 0;
                func_001F5620(func_001F5380(), g->cam, &v);
                v.y = 33.0f;
                b215_01E04010(g, &g->fx[a], 0x20, &v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E01EA0_b215) {
                g->tex88 = g->tex[1];
                rc = func_01E00BE0_b215(0, g->fx[a].h56, 0);
                g->u94.rc = rc;
                g->hBE = 0;
                v.x = g->fx[a].pos.x;
                v.y = g->fx[a].pos.y;
                v.z = g->fx[a].pos.z;
                func_01E00920_b215((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[a], 0x20, v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E01FF0_b215) {
                g->tex88 = g->tex[1];
                rc2 = func_01E00BE0_b215(0, g->fx[a].h56, 0);
                g->u94.rc = rc2;
                g->hBE = 0;
                v.x = g->fx[a].pos.x;
                v.y = g->fx[a].pos.y;
                v.z = g->fx[a].pos.z;
                func_01E00920_b215((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[a], 0x20, v);
            }
            if (g->fx[a].fn == (s32 (*)())func_01E02140_b215) {
                g->hB8 = 0x24;
                func_001F5620(func_001F5380(), g->cam, &v);
                v.y = 33.0f;
                b215_01E00D30(g, &g->fx[a], 0x20, &v);
                g->hB8 = 0;
            }
        }
    }
    if (m) {
        b215_01E04520(g);
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x8A) {
        return 1;
    }
    if (g->frame == 0x104) {
        return 4;
    }
    if (g->frame == 0xFF) {
        return 2;
    }
    if (g->frame > 0x94 && g->frame < 0xFA) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
