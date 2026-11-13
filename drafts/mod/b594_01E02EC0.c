#include "common.h"
#include "mod/b594.c"

/* shape b594:01E02EC0 (b594), 555 insns, 1 copy: b594 scene manager (b516:01E03030 form, s16 counters): setup (joint,
   textures, turn, five s8 jitter fills, eight random joints, eight random angles), step every slot but b594:01E02EB0,
   draw eight kinds; scene code from the timer */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    u8 pad48[8];
    s16 h50;
    u8 pad52[4];
    s16 h56;
    s16 used;
    u8 pad5A[0x16];
} Fx_b594_01E02EC0;

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
    Fx_b594_01E02EC0 fx[250];
    u8 pad7000[0x30];
    Vec4f pt[3];
    s32 tex[3];
    u8 pad706C[0x14];
    s32 count;
    u8 pad7084[8];
    s32 ot;
    u8 pad7090[0x28];
    s16 jA;
    u8 pad70BA[0xE];
    s16 jt[8];
    u8 pad70D8[8];
    s16 ang[8];
    u8 pad70F0[8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    s8 jit3[0x100];
    u8 pad73FE[2];
    u8 crd[0x170];
} Scene_b594_01E02EC0;

static s32 func_01E02EC0_b594(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern void b594_01E01840();
    Scene_b594_01E02EC0 *g = (Scene_b594_01E02EC0 *)arg0;
    s16 m;
    Vec4f v;
    s32 rm[4];
    s32 rm2[4];
    s32 rm3[4];
    s32 rm4[4];
    s32 rm5[4];
    s32 rm6[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s16 j;
    s32 n;

    m = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x7570);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 490;
        g->jA = func_001F5560(func_001F53A0(), 0x14, 1);
        for (i = 15; i < 16; i++) {
            g->tex260[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 100; k < 180; k++) {
            g->jit[k] = func_0019A5C8() % 20 + 4;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 20 - 10;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit3[k] = (func_0019A5C8() >> 4) % 40 - 20;
        }
        for (k = 100; k < 180; k++) {
            g->jit3[k] = (func_0019A5C8() >> 4) % 20 + 6;
        }
        for (k = 0; k < 8; k++) {
            n = func_001F54E0(func_001F53A0());
            m = func_0019A5C8() % n;
            if (m == 0) {
                m++;
            }
            if (!k) {
                g->jt[k] = func_001F5560(func_001F5380(), 0x14, 1);
            } else {
                g->jt[k] = func_001F5560(func_001F5380(), m, 0);
            }
        }
        for (k = 0; k < 8; k++) {
            g->ang[k] = (func_0019A5C8() >> 4) % 360;
        }
        return 0;
    }
    b594_01E01840(g, 0);
    for (j = 0; j < 250; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn != NULL && g->fx[j].fn != (s32 (*)())func_01E02EB0_b594) {
                g->fx[j].fn(g, &g->fx[j]);
            }
        }
    }
    for (k = 0; k < 250; k++) {
        if (g->fx[k].used != 0) {
            m++;
            if (g->fx[k].fn == (s32 (*)())func_01E01F30_b594) {
                g->hB8 = 0x24;
                func_01E011A0_b594((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                   (Vec_b016_01E01190 *)&g->pt[g->fx[k].h50]);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02090_b594) {
                g->tex88 = g->tex[0];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00EE0_b594((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02280_b594) {
                g->hB8 = 0x24;
                func_01E011A0_b594((Obj_b016_01E01190 *)g, (Data_b016_01E01190 *)&g->fx[k], 0x21,
                                   (Vec_b016_01E01190 *)&g->pt[g->fx[k].h50]);
                g->hB8 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E023F0_b594) {
                g->tex88 = g->tex[1];
                func_00106080(rm2, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm2;
                g->hBE = 0;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00EE0_b594((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E025E0_b594) {
                g->tex88 = g->tex[2];
                func_00106080(rm3, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm3;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b594((Obj_b594_01E00920 *)g, (Spr_b594_01E00920 *)&g->fx[k], 0x20, g->jit);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02790_b594) {
                g->tex88 = g->tex[2];
                func_00106080(rm4, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm4;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b594((Obj_b594_01E00920 *)g, (Spr_b594_01E00920 *)&g->fx[k], 0x21, g->jit2);
                g->hB8 = 0;
                g->hB0 = 0;
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02950_b594) {
                func_00106080(rm5, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm5;
                g->tex88 = g->tex[2];
                g->hBE = 5;
                v.x = g->fx[k].pos.x;
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E01500_b594((Obj_b094_01E01230 *)g, (Cam_b094_01E01230 *)&g->fx[k], 0x21, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E02B00_b594) {
                g->tex88 = g->tex[2];
                func_00106080(rm6, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)g->rm = *(Vec4f *)rm6;
                g->hB8 = 4;
                g->hB0 = 0;
                func_01E00920_b594((Obj_b594_01E00920 *)g, (Spr_b594_01E00920 *)&g->fx[k], 0x20, g->jit3);
                g->hB8 = 0;
                g->hB0 = 0;
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 0x8C) {
        return 1;
    }
    if (g->frame == 0x1DB) {
        return 4;
    }
    if (g->frame == 0x1D1) {
        return 2;
    }
    if (g->frame > 0x96 && g->frame < 0x1CC) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
