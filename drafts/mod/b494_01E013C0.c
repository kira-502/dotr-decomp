#include "common.h"
#include "mod/b494.c"

/* shape b494:01E013C0 (b494), 350 insns, 1 copy: the b494 scene manager: code >= 0 sets up (textures, scale 0.1, two
   jitter tables, eight random model joints, eight random angles), else runs B494_W_S, steps the 150 effect slots and
   draws the 01E00EE0 flames, 01E010D0 and 01E01230 beams; scene code from the frame */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x24];
    s32 (*fn)();
    f32 f48;
    u8 pad4C[0xA];
    s16 h56;
    s16 used;
    u8 pad5A[2];
    s16 h5C;
    u8 pad5E[0x12];
} Fx_b494_01E013C0;

typedef struct {
    u8 pad0[0x10];
    f32 sx;
    f32 sy;
    f32 sz;
    u8 pad1C[4];
    f32 px;
    f32 py;
    f32 pz;
    u8 pad2C[0x54];
    s32 ot80;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    s16 h94;
    s16 h96;
    s16 h98;
    s16 h9A;
    u8 pad9C[0x1C];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 crdD8[0x188];
    s32 tex[16];
    Fx_b494_01E013C0 fx[150];
    u8 pad4440[0x50];
    s32 tex2[2];
    u8 pad4498[0x18];
    s32 count;
    u8 pad44B4[8];
    s32 ot;
    u8 pad44C0[0x24];
    s16 joint[8];
    u8 pad44F4[0x18];
    s16 ang[8];
    u8 pad451C[8];
    s16 turn;
    s16 id;
    s16 frame;
    s8 jit[0x100];
    s8 jit2[0x100];
    u8 pad472A[2];
    u8 crd[0x174];
} Scene_b494_01E013C0;

static s32 func_01E013C0_b494(s32 arg0, s32 id) {
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F54E0(s32);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    extern void func_00106080(void *, s32, s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    extern void b494_01E01A90();
    extern void b494_01E02400();
    extern void func_01E00BE0_b494();
    Scene_b494_01E013C0 *g = (Scene_b494_01E013C0 *)arg0;
    Vec4f v;
    s32 rm[4];
    s32 ang[4];
    s32 i;
    s16 k;
    s16 n;
    s16 j;
    s32 m;

    n = 0;
    g->ot = func_00207500();
    g->ot80 = func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x48A0);
        func_00107C10(g->crd);
        func_00107C10(g->crdD8);
        g->id = id;
        g->count = 250;
        for (i = 15; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 0; i < 2; i++) {
            g->tex2[i] = func_00202BF0(5, i);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = ang[1] / 180.0f;
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (k = 0; k < 0x100; k++) {
            g->jit[k] = func_0019A5C8() % 30 - 15;
        }
        for (k = 0; k < 0x100; k++) {
            g->jit2[k] = func_0019A5C8() % 40 - 20;
        }
        for (k = 0; k < 8; k++) {
            m = func_001F54E0(func_001F53A0());
            n = func_0019A5C8() % m;
            if (n == 0) {
                n++;
            }
            if (!k) {
                g->joint[k] = func_001F5560(func_001F53A0(), n, 1);
            } else {
                g->joint[k] = func_001F5560(func_001F53A0(), n, 0);
            }
        }
        for (k = 0; k < 8; k++) {
            g->ang[k] = (func_0019A5C8() >> 4) % 360;
        }
        return 0;
    }
    func_01E00BE0_b494(g, 0);
    for (j = 0; j < 150; j++) {
        if (g->fx[j].used != 0) {
            if (g->fx[j].fn != NULL) {
                if (g->fx[j].fn != (s32 (*)())func_01E013B0_b494) {
                    g->fx[j].fn(g, &g->fx[j]);
                }
            }
        }
    }
    for (k = 0; k < 150; k++) {
        if (g->fx[k].used != 0) {
            n++;
            if (g->fx[k].fn == (s32 (*)())func_01E00EE0_b494) {
                g->tex88 = g->tex2[1];
                func_00106080(rm, 0x14, g->fx[k].h56, NULL);
                *(Vec4f *)&g->h94 = *(Vec4f *)rm;
                g->hBE = 0;
                v.x = g->fx[k].pos.x + g->fx[k].f48 * func_00108030(g->crdD8, g->fx[k].h5C, 0);
                v.y = g->fx[k].pos.y;
                v.z = g->fx[k].pos.z;
                func_01E00920_b494((Obj_b016_01E00ED0 *)g, (Cam_b016_01E00ED0 *)&g->fx[k], 0x20, v);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E010D0_b494) {
                g->tex88 = g->tex2[0];
                g->h94 = 0;
                g->h96 = 0;
                g->h98 = 31;
                g->h9A = 63;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 18;
                g->hBE = 0;
                b494_01E01A90(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
            if (g->fx[k].fn == (s32 (*)())func_01E01230_b494) {
                g->tex88 = g->tex2[0];
                g->h94 = 0;
                g->h96 = 0;
                g->h98 = 31;
                g->h9A = 31;
                g->hB8 = 0;
                g->px = g->fx[k].pos.x;
                g->py = g->fx[k].pos.y;
                g->pz = g->fx[k].pos.z;
                g->hB8 = 18;
                g->hBE = 0;
                b494_01E02400(g, &g->fx[k], 0x20, g->fx[k].pos);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->frame == 40) {
        return 1;
    }
    if (g->frame == 240) {
        return 3;
    }
    if (g->frame > 50 && g->frame < 235) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
