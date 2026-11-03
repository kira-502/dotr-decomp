#include "common.h"
#include "mod/b281.c"

/* shape b281:01E02440 (b281), 411 insns, 1 copy: b281 scene manager (b631:01E01EF0 form, best 400/411): setup (two
   joints, type-4 texture 15 and two type-5 textures, two 256 s8 jitter tables, eight random joints), step
   b281:01E015F0 and every slot except b281:01E02430, draw the b281:01E019D0 circles, b281:01E01C90 and b281:01E02030
   gas and b281:01E01E40 smoke; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x18];
    f32 f38;
    u8 pad3C[8];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b281_01E02440;

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
    s32 rm[4];
    u8 padA4[0xC];
    s16 hB0;
    u8 padB2[6];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex260[16];
    Fx_b281_01E02440 fx[150];
    u8 pad4440[0x50];
    s32 tex[2];
    u8 pad4498[0x18];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 jA;
    s16 jB;
    u8 pad44E8[0xC];
    s16 js[8];
    u8 pad4504[8];
    s16 h450C;
    s16 h450E;
    u8 pad4510[8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad471E[2];
    u8 crd[0x170];
} Scene_b281_01E02440;

static s32 func_01E02440_b281(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void func_01E015F0_b281();
    extern void func_01E00ED0_b281();
    extern void func_01E00920_b281();
    Scene_b281_01E02440 *g = (Scene_b281_01E02440 *)arg0;
    s16 n;
    Vec4f p;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s16 j;
    s32 (*fn)();
    s32 m;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x4890);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 374;
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->jB = func_001F5560(func_001F53A0(), 0x3F, 0);
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
        for (j = 0; j < 0x100; j++) {
            g->jit[j] = func_0019A5C8() % 30 - 15;
        }
        for (j = 0; j < 0x100; j++) {
            g->jit2[j] = func_0019A5C8() % 40 - 20;
        }
        for (j = 0; j < 8; j++) {
            m = func_001F54E0(func_001F5380());
            n = func_0019A5C8() % m;
            if (n == 0) {
                n++;
            }
            if (!j) {
                g->js[j] = func_001F5560(func_001F5380(), n, 1);
            } else {
                g->js[j] = func_001F5560(func_001F5380(), n, 0);
            }
        }
        g->h450C = 270;
        g->h450E = 90;
        return 0;
    }
    func_01E015F0_b281(g, 0);
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            fn = g->fx[k].fn;
            if (fn && fn != (s32 (*)())func_01E02430_b281) {
                fn(g, &g->fx[k]);
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E019D0_b281) {
                p = g->fx[k].pos;
                if (g->fx[k].h50 == 0) {
                    p.x += 10.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                if (g->fx[k].h50 == 1) {
                    p.x -= 10.0f * (g->fx[k].f38 * func_00108030(g->crdD8, g->fx[k].h5C, 1));
                }
                func_01E00ED0_b281((void *)g, (void *)&g->fx[k], 0x20, p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01C90_b281) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hB8 = 4;
                g->hBE = func_0019A5C8() % 4;
                g->hB0 = 0;
                func_01E00920_b281((void *)g, (void *)&g->fx[k], 0x21, g->jit);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01E40_b281) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = 0;
                p.x = g->fx[k].pos.x;
                p.y = g->fx[k].pos.y;
                p.z = g->fx[k].pos.z;
                func_01E01330_b281((void *)g, (void *)&g->fx[k], 0x20, p);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02030_b281) {
                g->tex88 = g->tex260[15];
                func_00106080(rm3, 0x97, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 10;
                g->hB0 = 1;
                func_01E00920_b281(g, &g->fx[k], 0x20, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 220) {
        return 1;
    }
    if (g->frame == 360) {
        return 4;
    }
    if (g->frame == 355) {
        return 2;
    }
    if (g->frame > 230 && g->frame < 350) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
