#include "common.h"
#include "mod/b741.c"

typedef struct {
    void *tex;
    s32 flags;
    u8 b, g, r, a;
    f32 width;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    u8 pad18[8];
    s32 w20;
    s32 w24;
    s16 max;
    s16 jitter;
    s16 progress;
    u8 pad2E[0x12];
} Yarn_b741_01E02E50;

typedef struct {
    u8 pad0[0x10];
    Vec4f rot;
    Vec4f pos;
    u8 pad30[0x40];
} Crd_b741_01E02E50;

typedef struct {
    f32 x, y, z;
    u8 c;
    u8 d;
    s16 t;
} Part_b741_01E02E50;

typedef struct {
    s32 tex;
    s32 flags;
    u8 c[4];
    Part_b741_01E02E50 *parts;
    s16 uv[8];
    f32 f20;
    f32 f24;
    f32 radius;
    s16 count;
    u8 b2E;
    u8 b2F;
} Line_b741_01E02E50;

typedef struct {
    u8 crd[0x70];
    Yarn_b741_01E02E50 yarn[8];
    Vec4f scale;
    u8 pad280[0x10];
    Vec4f joint;
    u8 pad2A0[0x40];
    Emit_b000_01E01140 emit;
    Pt_b000_01E01140 pts[64];
    Crd_b741_01E02E50 cam;
    Line_b741_01E02E50 line;
    Part_b741_01E02E50 parts[128];
    s32 count;
    s32 frame;
    s32 id;
    s32 wFEC;
    s32 jA;
    s32 jB;
    u8 padFF8[8];
} Scene_b741_01E02E50;

static s32 func_01E02E50_b741(s32 arg0, s32 code) {
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern s32 func_00207500(void);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F53C0(s32, s32, void *);
    extern void func_00103290(void *, s32);
    extern void func_00103DB0(void *, void *, void *);
    extern s32 func_001043F0(void *, f32);
    extern s32 func_00103470(u8 *, u8, s32);
    extern s32 func_001032C0(u8 *, u8, s32);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern s32 func_0019A5C8();
    extern s32 b741_01E01BD0();
    Scene_b741_01E02E50 *g = (Scene_b741_01E02E50 *)arg0;
    s32 ot;
    Vec4f v;
    Vec4f t[2];
    s32 tex[4];
    s32 i;
    s32 n;
    s32 a;
    f32 r;
    Vec4f *c;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x1000);
        func_00103890(g);
        func_00103890(&g->scale);
        func_00103890(&g->cam);
        g->jA = func_001F5560(func_001F53A0(), 0xC, 1);
        g->jB = func_001F5560(func_001F53A0(), 0xB, 0);
        g->count = 0x114;
        g->frame = 1;
        g->id = code;
        g->wFEC = 0;
        func_00103290(c = (Vec4f *)&tex[0], 0);
        g->emit.texture = (void *)tex[0];
        g->emit.flags = 0x48000003;
        g->emit.color.r = 0x80;
        g->emit.color.g = 0x80;
        g->emit.color.b = 0x80;
        g->emit.color.a = 0;
        g->emit.size = 20.0f;
        g->emit.rot.x = 0.0f;
        g->emit.rot.y = 0.0f;
        g->emit.rot.z = 0.0f;
        g->emit.r.i.u = 0;
        g->emit.r.i.v = 0;
        g->emit.r.i.w = 0x20;
        g->emit.r.i.h = 0x20;
        g->emit.r.i.u0 = 0;
        g->emit.r.i.v0 = 0;
        g->emit.r.i.tw = 0x80;
        g->emit.r.i.th = 0x40;
        g->emit.pts = g->pts;
        g->emit.rots = NULL;
        *(s32 *)g->emit.pad48 = 0;
        g->emit.radius = 15.0f;
        g->emit.grow = 10.0f;
        g->emit.count = 0x40;
        g->emit.nframes = 8;
        g->emit.rate = 0x10;
        for (i = 0; i < g->emit.count; i++) {
            func_001043F0(&v, 14.0f);
            g->pts[i].x = v.x;
            g->pts[i].y = v.y;
            g->pts[i].z = v.z;
            g->pts[i].t = -(func_0019A5C8() % 12);
            g->pts[i].a = 0x80;
            g->pts[i].frame = func_0019A5C8() % 8;
        }
        g->line.tex = tex[0];
        g->line.flags = 0x20000003;
        g->line.c[2] = 0x80;
        g->line.c[1] = 0x80;
        g->line.c[0] = 0x80;
        g->line.c[3] = 0xFF;
        g->line.f20 = 0.5f;
        g->line.f24 = 5.0f;
        g->line.uv[0] = 0x20;
        g->line.uv[1] = 0x20;
        g->line.uv[2] = 0x20;
        g->line.uv[3] = 0x20;
        g->line.uv[4] = 0x20;
        g->line.uv[5] = 0x20;
        g->line.uv[6] = 0x80;
        g->line.uv[7] = 0x40;
        g->line.parts = g->parts;
        g->line.radius = 5.0f;
        g->line.count = 0x80;
        g->line.b2E = 1;
        g->line.b2F = 0;
        { f32 h = 4.0f; func_01E01A10_b741((Obj_b015_01E01620 *)&g->line, 0xC, h); }
        for (i = 0; i < 8; i++) {
            g->yarn[i].tex = (void *)tex[0];
            g->yarn[i].flags = 0;
            g->yarn[i].width = 5.0f;
            g->yarn[i].h10 = 0x5A;
            g->yarn[i].h12 = 0;
            g->yarn[i].h14 = 6;
            g->yarn[i].h16 = 0x20;
            g->yarn[i].r = 0x80;
            g->yarn[i].g = 0x80;
            g->yarn[i].b = 0x80;
            g->yarn[i].a = 0x80;
            g->yarn[i].max = 0x1C;
            g->yarn[i].progress = -i;
            g->yarn[i].jitter = 0x28;
            g->yarn[i].w20 = 0;
            g->yarn[i].w24 = 0;
        }
        return 0;
    }
    func_001F5620(func_001F53A0(), g->jA, &v);
    func_001F5620(func_001F53A0(), g->jB, &t[0]);
    func_001F53C0(1, func_001F5380(), c = (Vec4f *)tex);
    func_001F53C0(1, func_001F5380(), &g->joint);
    func_00103DB0(&v, &t[0], &g->cam.rot);
    g->cam.pos = t[0];
    func_001038D0(g);
    func_001038D0(&g->scale);
    func_001038D0(&g->cam);
    if (g->frame == 0x8C) {
        g->emit.flags |= 0x80000;
    }
    if (g->frame >= 0x4E) {
        func_01E00120_b741(ot, (Emit_b000_01E01140 *)&g->emit, (Cam_b000_01E01140 *)&g->scale);
        if (g->frame >= 0x104) {
            func_00103470(&g->emit.color.a, 0, 8);
        } else {
            func_001032C0(&g->emit.color.a, 0x80, 2);
        }
        for (i = 0; i < g->emit.count; i++) {
            if (g->pts[i].t >= 0) {
                g->pts[i].x *= 1.03f;
                g->pts[i].y *= 1.03f;
                g->pts[i].z *= 1.03f;
                func_00103470(&g->pts[i].a, 0, 8);
            }
            if (g->pts[i].t >= 0x10) {
                func_001043F0(&v, 14.0f);
                g->pts[i].x = v.x;
                g->pts[i].y = v.y;
                g->pts[i].z = v.z;
                g->pts[i].t = 0;
                g->pts[i].a = 0x80;
            }
        }
    }
    if (g->frame >= 0x2C && g->frame <= 0xA7) {
        for (i = 0; i < 8; i++) {
            t[1] = *c;
            t[1].x += 20.0f * func_0020B480(i * 0x2000);
            t[1].y += 20.0f * func_0020B550(i * 0x2000);
            func_01E02930_b741(ot, (Obj_b055_01E02930 *)&g->yarn[i], (Cam_b055_01E02930 *)g, (Vec_b055_01E02930 *)&t[0], (Vec_b055_01E02930 *)&t[1]);
        }
        b741_01E01BD0(ot, &g->line, &g->cam);
        if (g->frame > 0x104) {
            func_00103470(&g->line.c[3], 0, 0x10);
        }
        for (i = 0; i < g->line.count; i++) {
            if (g->parts[i].t >= 0) {
                g->parts[i].x *= 1.3f;
                g->parts[i].y *= 1.3f;
                g->parts[i].z *= 1.3f;
                if (g->parts[i].y > 50.0f) {
                    n = (s32)(10.0f * g->line.radius);
                    a = func_0019A5C8() % 0x10000;
                    r = 0.1f * (f32)(func_0019A5C8() % n);
                    g->parts[i].y = 4.0f;
                    g->parts[i].z = r * func_0020B480(a);
                    g->parts[i].x = r * func_0020B550(a);
                    g->parts[i].t = -(func_0019A5C8() % 12);
                }
            }
        }
    }
    g->frame++;
    g->count--;
    if (g->frame == 0x104) {
        return 2;
    }
    if (g->frame == 0x44) {
        return 1;
    }
    if (g->frame >= 0x4E && g->frame <= 0x103) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}
