#include "common.h"

/* shape b032:01E05550 (b032), 614 insns, 1 copy (-O2,p): b032 scene manager (b085:01E04410 form at -O2): setup,
   then at t 0x72 two arcs, at 0x77 two rays with six rings, two flares, eight smokes and the emitter; updates and
   draws all, returns the phase code. 592/614 (22 words in the real build): ot takes s1 where the original has s4, so
   the &q[i] temp lands in s4 (orig s1) and the smoke loop's u8 temp / offset in s2/s4 (orig s1/s2). The parameter
   copies, opt_propagation off and the q[1] pointer turned out not to matter (same score without them). Tried: all
   120 orders of s/i/j/k/ot and a random search over all declarations (ot must be last; earlier gives ot s3/s4/s5 but
   moves g), copies as statements in each order, ot as an initializer, u32 ot, code or i/j as the smoke counter,
   q/s block-scoped in the case, s dropped, -O1/-O3 */

typedef struct {
    u8 pad0[4];
    u8 on;
    u8 b5;
    u8 pad6[0xE];
    f32 f14;
    f32 f18;
    f32 f1C;
    Vec4f pos;
    f32 f30;
    f32 f34;
    u8 pad38[0x18];
    f32 f50;
    u8 pad54[0xC];
} Emit_b032_01E05550;

typedef struct {
    s16 a;
    s16 b;
} Wv_b032_01E05550;

typedef struct {
    void *emits;
    void *parts;
    s16 *frames[4];
    u8 pad18[0x10];
    u8 bone[4];
    u8 pad2C[4];
    u8 emit_kind;
    u8 part_kind;
    u8 kind;
    u8 sel;
    s16 lo;
    s16 hi;
    f32 x0;
    f32 x1;
    f32 y;
} Walk_b032_01E05550;

typedef struct {
    s32 a;
    s32 b;
    u8 pad8[0xC];
} Cam_b032_01E05550;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 pad5[3];
    void *p8;
    s16 h0C[9];
    s16 h1E[9];
    u8 b30;
    u8 b31;
    u8 b32;
    u8 b33;
    u8 pad34[4];
    f32 f38;
    u8 pad3C[8];
    u8 c44[4];
    u8 c48[4];
    u8 pad4C[0x14];
} Arc_b032_01E05550;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    u8 c[4];
    f32 f10;
    f32 f14;
    u8 pad18[4];
    Vec4f pos;
    u8 pad2C[0x20];
} Flear_b032_01E05550;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6[2];
    u8 b8;
    u8 b9;
    u8 padA[6];
    s8 *tbl;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c20[4];
    u8 c24[4];
    Vec4f pos;
    u8 pad38[0x10];
    s32 w48;
    u8 pad4C[0x1C];
} Ray_b032_01E05550;

typedef struct {
    u8 pad0[4];
    u8 b4;
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
    u8 pad18[4];
    f32 f1C;
    f32 f20;
    u8 c[4];
    Vec4f pos;
    u8 pad38[0x20];
} Smk_b032_01E05550;

typedef struct {
    u8 pad0[4];
    u8 b4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    f32 f0C;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    u8 c20[4];
    u8 c24[4];
    Vec4f pos;
    s32 w38;
    u8 pad3C[0xC];
} Ring_b032_01E05550;

typedef struct {
    u16 t;
    u8 pad2[2];
    s32 unitA;
    s32 unitB;
    s32 m[6];
    u8 pad24[8];
    Cam_b032_01E05550 cam;
    Emit_b032_01E05550 emit;
    Wv_b032_01E05550 wv;
    Walk_b032_01E05550 walk;
    u8 emits[0x700];
    u8 parts[0x7D0];
    Arc_b032_01E05550 arc[2];
    u8 bolt[0x320];
    Flear_b032_01E05550 flear[2];
    u8 pad1430[0x18C];
    Ray_b032_01E05550 ray[2];
    Smk_b032_01E05550 smk[8];
    Ring_b032_01E05550 ring[6];
    s8 tbl[0x100];
    u8 pad1BFC[4];
} Scene_b032_01E05550;

#pragma optimization_level 2


static s32 func_01E05550_b032(Scene_b032_01E05550 *g, s32 code) {
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
    extern s32 func_0019A5C8(void);
    extern void func_001031C0(void *, u16);
    extern s16 D_01E06090_b032[];
    extern s16 D_01E060A0_b032[];
    Vec4f v;
    Vec4f q[2];
    Vec4f *s;
    s32 i;
    s32 j;
    s32 k;
    s32 ot;

    ot = func_00207500();
    if (code == -3 || code == -2) {
        return 8;
    }
    if (code >= 0) {
        func_00198948(g, 0, 0x1C00);
        g->unitA = func_001F53A0();
        g->unitB = func_001F5380();
        func_001F6160(g->unitA, &g->cam);
        func_00202BF0(4, 0xF);
        for (i = 0; i < 2; i++) {
            func_00202BF0(5, i);
        }
        g->m[0] = func_001F5560(g->unitA, 0x18, 1);
        g->m[1] = func_001F5560(g->unitA, 0x17, 0);
        g->m[2] = func_001F5560(g->unitA, 0x29, 0);
        g->m[3] = func_001F5560(g->unitA, 0x28, 0);
        g->m[4] = func_001F5560(g->unitA, 0x30, 0);
        g->m[5] = func_001F5560(g->unitA, 0x36, 0);
        g->walk.bone[0] = g->m[5];
        g->walk.bone[1] = g->m[4];
        g->walk.frames[0] = D_01E06090_b032;
        g->walk.frames[1] = D_01E060A0_b032;
        g->walk.emits = g->emits;
        g->walk.emit_kind = 0x20;
        g->walk.parts = g->parts;
        g->walk.part_kind = 0x32;
        g->walk.kind = 0;
        g->walk.sel = g->m[4];
        g->walk.lo = 0x6A;
        g->walk.hi = 0x71;
        g->walk.x0 = 170.0f;
        g->walk.x1 = 140.0f;
        g->walk.y = 6.0f;
        g->wv.a = 2;
        g->wv.b = 0xC0;
        func_00102330(g->tbl, 0x100);
        return 0;
    }
    g->t++;
    func_001F5F90(g->unitB, &v);
    switch (g->t) {
    case 0x72:
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->arc[i], 0x15, 0, 0xFF);
            g->arc[i].b4 = 1;
            g->arc[i].p8 = g->bolt;
            g->arc[i].b30 = 0x32;
            g->arc[i].b31 = 8;
            g->arc[i].b32 = g->m[i * 2];
            g->arc[i].b33 = g->m[i * 2 + 1];
            g->arc[i].f38 = 1.0f;
            g->arc[i].c44[0] = 0x80;
            g->arc[i].c44[1] = 0x80;
            g->arc[i].c44[2] = 0x80;
            g->arc[i].c44[3] = 0x80;
            g->arc[i].c48[1] = 0x20;
            g->arc[i].c48[2] = 0x20;
            g->arc[i].c48[0] = 0x80;
            for (j = 0; j < g->arc[i].b31 + 1; j++) {
                g->arc[i].h0C[j] = -1;
                g->arc[i].h1E[j] = -1;
            }
        }
        break;
    case 0x77:
        func_001F5620(g->unitA, g->m[0], &q[0]);
        func_001F5620(g->unitA, g->m[2], &q[1]);
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->ray[i], 0x14, 0, 0xFF);
            g->ray[i].b4 = 0;
            g->ray[i].b5 = 0;
            g->ray[i].b8 = 0x46;
            g->ray[i].b9 = func_0019A5C8() >> 4;
            g->ray[i].f1C = 70.0f;
            g->ray[i].tbl = g->tbl;
            g->ray[i].f14 = 3.8f;
            g->ray[i].f18 = 1.6f;
            g->ray[i].c20[2] = 0x20;
            g->ray[i].c20[1] = 0;
            g->ray[i].c20[0] = 0x80;
            g->ray[i].c20[3] = 0x18;
            g->ray[i].c24[3] = 0x60;
            g->ray[i].c24[0] = 0x60;
            g->ray[i].c24[1] = 0x60;
            g->ray[i].c24[2] = 0x60;
            s = &q[i];
            g->ray[i].pos = *s;
            if (g->cam.b == 0x8000) {
                g->ray[i].w48 = 0x3000;
            } else {
                g->ray[i].w48 = -0x3000;
            }
            for (j = 0; j < 3; j++) {
                k = j + i * 3;
                func_00101AD0(&g->ring[k], 0x14, (u8)(j * 4), 0xFF);
                g->ring[k].b4 = 0;
                g->ring[k].b5 = 0;
                g->ring[k].b7 = 9;
                g->ring[k].b8 = 2;
                g->ring[k].bA = 0x20;
                g->ring[k].b9 = 7;
                g->ring[k].f0C = 5.0f;
                g->ring[k].f10 = 0.8f;
                g->ring[k].f14 = 2.0f;
                g->ring[k].f18 = 0.0f;
                g->ring[k].f1C = 0.3f;
                g->ring[k].c20[3] = 0x60;
                g->ring[k].c20[0] = 0x60;
                g->ring[k].c20[1] = 0x60;
                g->ring[k].c20[2] = 0x60;
                g->ring[k].c24[1] = 0;
                g->ring[k].c24[2] = 0;
                g->ring[k].c24[0] = 0x80;
                g->ring[k].c24[3] = 0x60;
                g->ring[k].pos = *s;
                g->ring[k].w38 = g->ray[0].w48;
            }
        }
        for (i = 0; i < 2; i++) {
            func_00101AD0(&g->flear[i], 0x18, 0, 0xFF);
            g->flear[i].b5 = 0;
            g->flear[i].b4 = 0x81;
            g->flear[i].b7 = 9;
            if (i) {
                g->flear[i].f10 = 600.0f;
                g->flear[i].c[3] = 0xC0;
                g->flear[i].c[0] = 0xC0;
                g->flear[i].c[1] = 0xC0;
                g->flear[i].c[2] = 0xC0;
                g->flear[i].bA = 0x80;
                g->flear[i].b9 = 0;
                g->flear[i].b8 = 0x10;
            } else {
                g->flear[i].f10 = 1500.0f;
                g->flear[i].c[3] = 0xA0;
                g->flear[i].c[0] = 0xA0;
                g->flear[i].c[1] = 0xA0;
                g->flear[i].c[2] = 0xA0;
                g->flear[i].bA = 0x10;
                g->flear[i].b9 = 0;
                g->flear[i].b8 = 0x80;
            }
            g->flear[i].f14 = 0.0f;
            g->flear[i].pos.x = q[0].x + (q[1].x - q[0].x) / 2.0f;
            g->flear[i].pos.y = q[0].y + (q[1].y - q[0].y) / 2.0f;
            g->flear[i].pos.z = q[0].z + (q[1].z - q[0].z) / 2.0f;
        }
        for (k = 0; k < 8; k++) {
            func_00101AD0(&g->smk[k], (u8)(((func_0019A5C8() >> 4) & 3) + 0x1E), (func_0019A5C8() >> 4) & 7, 0xFF);
            g->smk[k].b4 = 7;
            g->smk[k].b5 = 0;
            g->smk[k].b8 = 0x32;
            g->smk[k].b9 = func_0019A5C8() >> 4;
            g->smk[k].bA = 1;
            g->smk[k].bC = 2;
            g->smk[k].bB = 3;
            g->smk[k].f1C = 25.0f + 2.0f * (f32)k;
            g->smk[k].f20 = 0.0f;
            g->smk[k].tbl = g->tbl;
            g->smk[k].f14 = 1.4f;
            g->smk[k].c[3] = 0x80;
            g->smk[k].c[0] = 0x80;
            g->smk[k].c[1] = 0x80;
            g->smk[k].c[2] = 0x80;
            g->smk[k].pos = v;
        }
        func_00101AD0(&g->emit, 0x16, 0, 0xFF);
        g->emit.b5 = 0;
        g->emit.on = 1;
        g->emit.f14 = 1.4f;
        g->emit.f18 = 1.0f;
        g->emit.f1C = 2.0f;
        g->emit.f30 = 0.0f;
        g->emit.f34 = 80.0f;
        g->emit.f50 = 6.0f;
        g->emit.pos = v;
        break;
    case 0xC6:
        return 8;
    }
    func_01E00080_b032((Obj_b010_01E00080 *)&g->emit);
    func_001031C0(&g->wv, g->t);
    func_01E010E0_b032((Obj_b010_01E010E0 *)&g->walk, g->t);
    func_01E00410_b032(g->emits, ot, 0x20);
    func_01E015A0_b032((Rib_b091_01E00410 *)g->arc, ot, 2);
    func_01E02820_b032(g->ring, ot, 6);
    func_01E03090_b032((Obj_b035_01E00410 *)g->flear, ot, 2);
    func_01E047A0_b032((Rib_b024_01E02120 *)g->smk, ot, 8);
    func_01E03C10_b032((Ray_b532_01E00080 *)g->ray, ot, 2);
    switch (g->t) {
    case 0x6D:
        return 1;
    case 0x74:
        return 2;
    }
    return 0;
}


#pragma optimization_level reset
