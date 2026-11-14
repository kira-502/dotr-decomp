#include "common.h"

/* shape c512:01E015C0 (c512), 618 insns, 1 copy: c512 main: on start clears the 0xAA0 scene (timer 60), three dual
   boards (texture 8, size 30) flung from the centre on random headings with their coords, an 8-point outline (texture
   14, scale 30) and a 60-spark cloud (texture 15); each tick draws the boards, fades them from 41, slides them back
   by speed (grows 0.15) until landed, then draws the outline and sparks on them; 2 at tick 29, 8 when the timer ends
   */

typedef struct {
    u8 b, g, r, a;
} Col_c512_01E015C0;

typedef struct {
    f32 x, y, z, w;
} Scl_c512_01E015C0;

typedef struct {
    Scl_c512_01E015C0 s;
    s32 rot[4];
    Vec4f pos;
    u8 pad30[0x40];
} Crd_c512_01E015C0;

typedef struct {
    s16 r[8];
    s32 rot[4];
    f32 vx, vy, vz;
    u8 pad2C[4];
    f32 f30;
    Col_c512_01E015C0 color;
    s32 flags;
    u8 pad3C[4];
    s32 spin;
    u8 pad44[4];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Mdl_c512_01E015C0;

typedef struct {
    s16 r[8];
    u8 pad10[0x20];
    f32 f30;
    Col_c512_01E015C0 color;
    s32 flags;
    u8 pad3C[0xC];
    s16 h48, h4A, h4C, h4E, h50, h52;
    u8 pad54[0xC];
} Def_c512_01E015C0;

typedef struct {
    Vec4f v[8];
} Tbl_c512_01E015C0;

typedef struct {
    s32 tex;
    u8 pad4[8];
    f32 scale;
    s32 a, b, c;
    u8 pad1C[4];
    Vec4f p[8];
} Pts_c512_01E015C0;

typedef struct {
    f32 x, y, z;
} V3_c512_01E015C0;

typedef struct {
    s32 tex;
    s32 flags;
    Col_c512_01E015C0 color;
    f32 size;
    s16 u, v, w, h;
    u8 pad18[8];
    V3_c512_01E015C0 p[60];
} Spark_c512_01E015C0;

typedef struct {
    Crd_c512_01E015C0 a[3];
    Crd_c512_01E015C0 b[3];
    Crd_c512_01E015C0 c[3];
    Mdl_c512_01E015C0 obj[3];
    u8 bb[3][0x80];
    Def_c512_01E015C0 def;
    Pts_c512_01E015C0 pts;
    Spark_c512_01E015C0 spark;
    f32 speed;
    s32 timer;
    s32 code;
    s32 frame;
    s32 flags;
    u8 padA94[0xC];
} Scene_c512_01E015C0;

static s32 func_01E015C0_c512(s32 arg0, s32 code) {
    Scene_c512_01E015C0 *g = (Scene_c512_01E015C0 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00103890(void *);
    extern void func_001038D0(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_00103260(void *, s32);
    extern s32 func_0019A5C8(void);
    extern f32 func_0020B480(s32);
    extern f32 func_0020B550(s32);
    extern f32 func_001A6C18(f32, f32);
    extern s32 func_00104520(s32, s32);
    extern s32 func_001032C0(void *, s32, s32);
    extern void func_00103470(void *, s32, s32);
    extern void func_00103390(void *, f32, f32);
    extern s32 c512_01E00120(void *, void *, s32, f32);
    extern s32 c512_01E00380();
    extern s32 c512_01E00AD0();
    extern s32 c512_01E010B0();
    extern Tbl_c512_01E015C0 D_01E01FE0_c512;
    s32 tex __attribute__((aligned(16)));
    Tbl_c512_01E015C0 tbl;
    V3_c512_01E015C0 s;
    s32 ot;
    s32 t;
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 n;
    f32 r;
    f32 dz;
    f32 dx;
    f32 h;

    ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xAA0);
        g->flags = 0;
        g->speed = 0.0f;
        g->frame = 0;
        g->timer = 0x3C;
        g->code = code;
        for (i = 0; i < 3; i++) {
            func_00103890(&g->b[i]);
            func_00103890(&g->a[i]);
            func_001F53B0(0, &g->a[i].pos);
            func_00103890(&g->c[i]);
            func_001F53B0(0, &g->c[i].pos);
        }
        func_00103260(&tex, 8);
        for (i = 0; i < 3; i++) {
            g->obj[i].f30 = 1.0f;
            g->obj[i].flags = 0x40000001;
            g->obj[i].r[0] = 0;
            g->obj[i].r[1] = 0;
            g->obj[i].r[2] = 0x20;
            g->obj[i].r[3] = 0x80;
            g->obj[i].r[4] = 0x20;
            g->obj[i].r[5] = 0;
            g->obj[i].r[6] = 0x80;
            g->obj[i].r[7] = 0x80;
            g->obj[i].h48 = 0;
            g->obj[i].h4A = 1;
            g->obj[i].h4E = 3;
            g->obj[i].h52 = 999;
            g->obj[i].h50 = 0;
            g->obj[i].h4C = g->obj[i].h4E - 1;
            c512_01E00120(&g->obj[i], g->bb[i], tex, 30.0f);
            g->obj[i].color.r = 0x80;
            g->obj[i].color.g = 0x80;
            g->obj[i].color.b = 0x80;
            g->obj[i].color.a = 0;
            g->obj[i].spin = i * 0x2000;
            g->obj[i].rot[1] = (i * 0x5555 + (func_0019A5C8() % 0x3000 - 0x1800)) % 0x10000;
            r = 0.1f * (f32)(func_0019A5C8() % 100 + 30);
            dz = r * -func_0020B480(g->obj[i].rot[1]);
            dx = r * -func_0020B550(g->obj[i].rot[1]);
            g->obj[i].rot[2] = 0;
            g->obj[i].rot[0] = -(0x4000 - (s32)(65536.0f * (func_001A6C18(15.0f, r) / 6.2831855f)));
            g->obj[i].vx = dx / 4.0f;
            g->obj[i].vz = dz / 4.0f;
            g->obj[i].vy = 5.0f;
            func_001F53B0(0, &g->b[i].pos);
            h = 0.0f;
            g->b[i].pos.x += dx + 60.0 * g->obj[i].vx;
            g->b[i].pos.z += dz + 60.0 * g->obj[i].vz;
            g->b[i].pos.y += h + 60.0f * g->obj[i].vy;
        }
        func_00103260(&tex, 0xE);
        g->def.color.r = 0x80;
        g->def.color.g = 0x80;
        g->def.color.b = 0x80;
        g->def.color.a = 0x80;
        g->def.f30 = 1.0f;
        g->def.flags = 3;
        g->def.r[0] = 0x60;
        g->def.r[1] = 0;
        g->def.r[2] = 0x50;
        g->def.r[3] = 0x50;
        g->def.r[4] = 0x60;
        g->def.r[5] = 0;
        g->def.r[6] = 0x100;
        g->def.r[7] = 0x100;
        g->def.h48 = 0;
        g->def.h4A = 1;
        g->def.h4E = 2;
        g->def.h52 = 0;
        g->def.h50 = 0;
        g->def.h4C = g->def.h4E - 1;
        t = tex;
        tbl = D_01E01FE0_c512;
        g->pts.a = g->pts.b = g->pts.c = 0;
        g->pts.scale = 30.0f;
        g->pts.tex = t;
        for (k = 0; k < 8; k++) {
            g->pts.p[k].x = g->pts.scale * tbl.v[k].x;
            g->pts.p[k].y = g->pts.scale * tbl.v[k].y;
            g->pts.p[k].z = g->pts.scale * tbl.v[k].z;
        }
        for (i = 0; i < 3; i++) {
            g->a[i].s.x = g->a[i].s.y = g->a[i].s.y = 0.1f * (f32)i;
            g->a[i].rot[1] = g->c[i].rot[1] = (i * 0x5555 + (func_0019A5C8() % 0x3000 - 0x1800)) % 0x10000;
            g->c[i].s.x = g->c[i].s.y = g->c[i].s.y = 0.5f;
        }
        func_00103260(&tex, 0xF);
        g->spark.tex = tex;
        g->spark.size = 1.5f;
        for (n = 0; n < 60; n++) {
            if (func_00104520(g->spark.flags, 0x1D)) {
                g->spark.p[n].x = func_0019A5C8() % 100 - 50;
                g->spark.p[n].z = func_0019A5C8() % 50;
                g->spark.p[n].y = func_0019A5C8() % 100 - 50;
            } else {
                g->spark.p[n].x = func_0019A5C8() % 50 - 25;
                g->spark.p[n].y = func_0019A5C8() % 25;
                g->spark.p[n].z = func_0019A5C8() % 50 - 25;
            }
        }
        g->spark.flags = 1;
        g->spark.u = 0xB0;
        g->spark.v = 0x40;
        g->spark.w = 0x20;
        g->spark.h = 0x20;
        g->spark.color.r = 0x80;
        g->spark.color.g = 0x70;
        g->spark.color.b = 0x40;
        g->spark.color.a = 0x80;
        return 0;
    }
    for (i = 0; i < 3; i++) {
        func_001038D0(&g->c[i]);
        func_001038D0(&g->b[i]);
        func_001038D0(&g->a[i]);
        c512_01E00380(ot, &g->obj[i], g->bb[i], &g->b[i]);
        if (g->frame > 0x28) {
            func_00103470(&g->obj[i].color.a, 0, 8);
        }
        if (g->frame < 0x3C) {
            if (!func_00104520(g->flags, i + 10) && !func_001032C0(&g->obj[i].color.a, 0x80, 8)) {
                g->flags |= 1 << (i + 10);
            }
            if (g->b[i].pos.y > g->obj[i].vy * g->speed) {
                g->obj[i].spin += 0x1000;
                g->b[i].pos.x -= g->obj[i].vx * g->speed;
                g->b[i].pos.z -= g->obj[i].vz * g->speed;
                g->b[i].pos.y -= g->obj[i].vy * g->speed;
            } else {
                if (g->def.h52 == 0 || g->def.h52 == 999) {
                    c512_01E010B0(ot, &g->def, &g->pts, &g->a[i]);
                }
                g->def.h48++;
                func_00103390(&g->a[i].s.x, 1.5f, 0.3f);
                func_00103390(&g->a[i].s.y, 1.5f, 0.3f);
                func_00103390(&g->a[i].s.z, 1.5f, 0.3f);
                func_00103470(&g->def.color.a, 0, 4);
                s.y = s.x = s.z = 1.02f;
                if (g->c[i].s.x < 1.0f) {
                    g->c[i].s.x = g->c[i].s.y = g->c[i].s.z += 0.1f;
                }
                c512_01E00AD0(ot, &g->spark, &g->c[i], &s);
                func_00103470(&g->spark.color.a, 0, 4);
            }
            g->b[i].rot[0] = g->obj[i].rot[0];
            g->b[i].rot[1] = g->obj[i].rot[1];
            g->b[i].rot[2] = g->obj[i].rot[2];
        }
    }
    g->speed += 0.15f;
    g->frame++;
    g->timer--;
    if (g->frame == 0x1D) {
        return 2;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}
