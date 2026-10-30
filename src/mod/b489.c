#include "common.h"

/* OVL_WARM: compile warm (DK_WARM=1, after a runtime-helper call as in the original many-files-per-run build).
   Its float -> int casts are MWCC runtime calls: fptosi = 0x001A22C0, fptoui = 0x001A23B0 (link names). */

/* shape b015:01E01620, 110 insns, 54 copies: scatter the particles on a random ring (flag 0x1D) or at a spawn point */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b015_01E01620;

typedef struct {
    u8 pad00[4];
    s32 flags;
    u8 pad08[3];
    u8 c;
    Part_b015_01E01620 *parts;
    u8 pad10[0x18];
    f32 radius;
    s16 count;
} Obj_b015_01E01620;

static s32 func_01E00080_b489(Obj_b015_01E01620 *obj, s32 life, f32 y) {
    f32 v[4];
    s32 a;
    s32 n;
    s32 i;
    f32 r;

    n = (s32)(10.0f * obj->radius);
    for (i = 0; i < obj->count; i++) {
        if (func_00104520(obj->flags, 0x1D) != 0) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % n);
            obj->parts[i].y = y;
            obj->parts[i].z = r * func_0020B480(a);
            obj->parts[i].x = r * func_0020B550(a);
        } else {
            func_001043F0(v, y);
            obj->parts[i].x = v[0];
            obj->parts[i].y = v[1];
            obj->parts[i].z = v[2];
        }
        obj->parts[i].t = -(func_0019A5C8() % life);
        obj->parts[i].c = obj->c;
        obj->parts[i].d = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b489", func_01E00240_b489);

/* shape b489:01E00FA0 (b489), 378 insns, 1 copy: b489 scene manager: setup (a 256-point line-particle fountain
   scattered on a ring), then the joints and colour flashes between frames 0x5C and 0xEB, the particles drawn, risen
   and respawned above 200 */

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Pt_b489_01E00FA0;

typedef struct {
    void *texture;
    s32 flags;
    u8 b, g, r, a;
    Pt_b489_01E00FA0 *parts;
    s16 u, v, w, h;
    s16 u0, v0, tw, th;
    f32 width;
    f32 len;
    f32 radius;
    s16 count;
    u8 nframes;
    u8 rate;
} Emit_b489_01E00FA0;

typedef struct {
    u8 crd[0x70];
    Vec4f scale;
    Vec4f dir;
    Vec4f joint;
    u8 padA0[0x40];
    Emit_b489_01E00FA0 emit;
    Pt_b489_01E00FA0 pts[256];
    u8 crd2[0x20];
    Vec4f v1130;
    u8 pad1140[0x40];
    u8 crd3[0x20];
    Vec4f v11A0;
    u8 pad11B0[0x40];
    Vec4f v11F0;
    s32 count;
    s32 frame;
    s32 id;
    u8 col[4];
    s32 jA;
    u8 b1214;
    u8 pad1215[0xB];
} Scene_b489_01E00FA0;

static s32 func_01E00FA0_b489(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001039A0(void *);
    extern u8 *func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6580(s32, void *);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, u8);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern s32 b489_01E00240();
    Scene_b489_01E00FA0 *g = (Scene_b489_01E00FA0 *)arg0;
    u8 *ot;
    Vec4f t[2];
    s32 tex[4];
    s32 i;
    s32 a;
    f32 r;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1220);
        func_00103890(g);
        func_00103890(g->crd2);
        func_00103890(&g->scale);
        func_00103890(g->crd3);
        g->jA = func_001F5560(func_001F53A0(), 1, 1);
        g->count = 0x100;
        g->frame = 1;
        g->id = code;
        g->b1214 = 0x80;
        g->col[3] = 0x80;
        g->col[0] = 0x80;
        g->col[1] = 0x80;
        g->col[2] = 0x80;
        func_00103290(tex, 0);
        g->emit.texture = (void *)tex[0];
        g->emit.flags = 0x60000003;
        g->emit.r = 0x80;
        g->emit.g = 0x80;
        g->emit.b = 0x80;
        g->emit.a = 0;
        g->emit.width = 0.2f;
        g->emit.len = 22.0f;
        g->emit.u = 0;
        g->emit.v = 0;
        g->emit.w = 0x20;
        g->emit.h = 0x20;
        g->emit.u0 = 0;
        g->emit.v0 = 0;
        g->emit.tw = 0x80;
        g->emit.th = 0x40;
        g->emit.parts = g->pts;
        g->emit.radius = 10.0f;
        g->emit.count = 0x100;
        g->emit.nframes = 8;
        g->emit.rate = 0;
        func_01E00080_b489((Obj_b015_01E01620 *)&g->emit, 0xC, 3.0f);
        for (i = 0; i < g->emit.count; i++) {
            a = func_0019A5C8() % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % 60);
            g->emit.parts[i].y = 0.1f * (f32)(func_0019A5C8() % 2000);
            g->emit.parts[i].z = r * func_0020B480(a);
            g->emit.parts[i].x = r * func_0020B550(a);
            g->emit.parts[i].c = 0;
        }
        return 0;
    }
    func_001F5F90(func_001F5380(), &g->v11F0);
    func_001F5620(func_001F53A0(), g->jA, &g->joint);
    func_001F5F90(func_001F5380(), &t[0]);
    func_001F5620(func_001F53A0(), g->jA, &t[1]);
    func_00103DB0(&t[0], &t[1], &g->dir);
    func_001F5620(func_001F53A0(), g->jA, &g->v11A0);
    func_001F5620(func_001F53A0(), g->jA, &g->v1130);
    func_001038D0(g);
    func_001039A0(g->crd2);
    func_001038D0(&g->scale);
    func_001038D0(g->crd3);
    if (g->frame > 0x5B && g->frame <= 0xEB) {
        func_001F6580(func_001F5380(), g->col);
        g->col[2] = func_0019A5C8() % 128;
        g->col[1] = func_0019A5C8() % 128;
        g->col[0] = func_0019A5C8() % 128;
    }
    if (g->frame == 0xEC) {
        func_001F6580(func_001F5380(), 0);
    }
    b489_01E00240(ot, &g->emit, &g->scale);
    if (g->frame > 0xEC) {
        func_00103470(&g->emit.a, 0, 8);
    } else if (g->frame > 0x14 && g->frame <= 0xEB) {
        func_001032C0(&g->emit.a, 0x80, 8);
    }
    for (i = 0; i < g->emit.count; i++) {
        if (g->pts[i].t >= 0) {
            g->pts[i].y += 4.0f;
            func_001032C0(&g->pts[i].c, 0x80, 0x10);
            if (g->pts[i].y > 200.0f) {
                a = func_0019A5C8() % 0x10000;
                r = 0.1f * (f32)(func_0019A5C8() % 60);
                g->emit.parts[i].y = 0.1f * (f32)(func_0019A5C8() % 30);
                g->emit.parts[i].z = r * func_0020B480(a);
                g->emit.parts[i].x = r * func_0020B550(a);
                g->pts[i].c = 0;
                g->pts[i].t = 0;
            }
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 0xEC) {
        return 2;
    }
    if (g->frame == 0x51) {
        return 1;
    }
    if (g->frame >= 0x5B && g->frame <= 0xEB) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

