#include "common.h"

/* shape b058:01E00080, 118 insns, 13 copies: draws one textured square of an object (position = pos + vel / 10, size from
   the object, camera-facing via func_00205C40); mode 0 goes through func_00108F90, else projected + depth */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b058_01E00080;

typedef struct {
    void *texture;
    s16 tex;
    u8 pad6[6];
    s32 mode;
} Spr_b058_01E00080;

static void func_01E00080_b195(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
    extern void func_00106080(void *, s16, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 depth[4];
    f32 m[16];
    Vec4f rot;
    u8 packet[0x90];
    u8 *pkt;
    f32 size;

    pkt = packet;
    func_00106080(td, s->tex, o->page, td);
    func_00109270(pkt, 0, 0);
    func_00107790(pkt, o->col, 0);
    func_00108500(pkt, td, 0);
    func_00208700(pkt, s->texture, 1);
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    if (s->mode == 0) {
        func_00108F90(quad, pkt, m, ot);
        return;
    }
    if (func_00205630(quad, 0x70000000, m, pkt, depth) != 0) {
        func_00109380(pkt, 0);
        func_002075F0(pkt, ot, (u32)depth[0]);
    }
}

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00260_b195(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
    extern s32 func_001F53A0();
    s32 k;
    Vec_b004_01E00B40 *dst;
    Vec_b004_01E00B40 *src;
    Vec_b004_01E00B40 pos;
    s32 i;

    src = trail;
    k = n - 1;
    dst = trail;
    src--;
    func_001F5620(func_001F53A0(trail), arg2, (s32)&pos);
    for (i = 0; i < n; i++) {
        if (k != 0) {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        } else {
            dst->x = pos.x;
            dst->y = pos.y;
            dst->z = pos.z;
        }
        dst--;
        src--;
        k--;
    }
    return 0;
}

/* shape b008:01E00080, 273 insns, 45 copies: the 4-mode version of b003:01E00080 (texture coordinates of a
   sprite quad from a rectangle). Callers rely on it being static in their file. */

typedef struct Rect_b008_01E00080 {
    s16 x, y, w, h;
} Rect_b008_01E00080;

typedef struct Uv_b008_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b008_01E00080;

typedef struct Pk_b008_01E00080 {
    u8 pad0[0x18];
    Uv_b008_01E00080 c[4];
} Pk_b008_01E00080;

static void func_01E00330_b195(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
    if (mode == 0) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y + r->h) << 4;
    } else if (mode == 1) {
        p->c[0].u = (r->x) << 4;
        p->c[0].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
        p->c[3].u = (r->x + r->w) << 4;
        p->c[3].v = (r->y) << 4;
    } else if (mode == 2) {
        p->c[2].u = (r->x) << 4;
        p->c[2].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[1].u = (r->x + r->w) << 4;
        p->c[1].v = (r->y + r->h) << 4;
    } else {
        p->c[1].u = (r->x) << 4;
        p->c[1].v = (r->y) << 4;
        p->c[0].u = (r->x + r->w) << 4;
        p->c[0].v = (r->y) << 4;
        p->c[3].u = (r->x) << 4;
        p->c[3].v = (r->y + r->h) << 4;
        p->c[2].u = (r->x + r->w) << 4;
        p->c[2].v = (r->y + r->h) << 4;
    }
}

/* shape b195:01E00780, 155 insns: the effect scene's step: clears the tint to 0x80/0/0/0 and counts the frame (0x407E);
   from frame 30 to 49 it spawns 0x1E01060, before 50 three 0x1E00D90 a frame; on frame 29 the nine trail points take
   the joint's position; runs the shared step at +0x4000; on frame 50 it takes the joint's position and bursts 50
   0x1E014A0, 30 0x1E01730, 10 0x1E00C20, a 0x1E01920 and a 0x1E01840; frames 47 and 30 store the joint's position at
   0x320 and 0x330, and 0x338 sinks by 4 */

typedef struct {
    u8 pad0[0x2D0];
    f32 px, py, pz;
    u8 pad2DC[0x44];
    Vec4f p320;
    Vec4f p330;
    u8 pad340[0x3C30];
    Vec4f trail[9];
    u8 pad4000[0x24];
    u8 col[4];
    u8 pad4028[0x40];
    s16 joint;
    u8 pad406A[0x14];
    s16 t;
} Scene_b195_01E00780;

static void func_01E00780_b195(Scene_b195_01E00780 *g) {
    extern void b195_01E00260(void *, s32, s32);
    extern void b195_01E00C20(void);
    extern void b195_01E00D90(void);
    extern void b195_01E01060(void);
    extern void b195_01E014A0(void);
    extern void b195_01E01730(void);
    extern void b195_01E01840(void);
    extern void b195_01E01920(void);
    extern s32 b195_01E02650(Scene_b195_01E00780 *, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f a;
    Vec4f b;
    Vec4f *p;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F5620(func_001F53A0(), g->joint, &a);
    if (g->t >= 30 && g->t < 50) {
        b195_01E02650(g, (s32)b195_01E01060, 0);
    }
    if (g->t < 50) {
        for (i = 0; i < 3; i++) {
            b195_01E02650(g, (s32)b195_01E00D90, 0);
        }
    }
    if (g->t == 29) {
        p = g->trail;
        func_001F5620(func_001F53A0(), g->joint, &b);
        for (i = 0; i < 9; i++) {
            p->x = b.x;
            p->y = b.y;
            p->z = b.z;
            p++;
        }
    }
    b195_01E00260((u8 *)g + 0x4000, 10, g->joint);
    if (g->t == 50) {
        func_001F5620(func_001F53A0(), g->joint, &a);
        g->px = a.x;
        g->py = a.y;
        g->pz = a.z;
        for (i = 0; i < 50; i++) {
            b195_01E02650(g, (s32)b195_01E014A0, 0);
        }
        for (i = 0; i < 30; i++) {
            b195_01E02650(g, (s32)b195_01E01730, 0);
        }
        for (i = 0; i < 10; i++) {
            b195_01E02650(g, (s32)b195_01E00C20, 0);
        }
        b195_01E02650(g, (s32)b195_01E01920, 0);
        b195_01E02650(g, (s32)b195_01E01840, 0);
    }
    if (g->t == 47) {
        func_001F5620(func_001F53A0(), g->joint, &g->p320);
    }
    if (g->t == 30) {
        func_001F5620(func_001F53A0(), g->joint, &g->p330);
    }
    g->p330.z -= 4.0f;
}

/* shape b195:01E00A00, 134 insns: b194:01E00C60 with the sine table at g+0x4084 */

typedef struct {
    u8 pad0[0x4084];
    u8 trig[1];
} World_b195_01E00A00;

typedef struct {
    u8 pad0[8];
    s16 x, y, z;
    u8 padE[0x1A];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 h38;
    s16 a3A;
} Wisp_b195_01E00A00;

static s32 func_01E00A00_b195(World_b195_01E00A00 *w, Wisp_b195_01E00A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->c0, 0x3F, 0x30, 0x3F);
    if (o->state == 1) {
        o->h38 = 0;
        o->a3A = func_0019A5C8() % 360;
        o->frame = 0;
        o->a30 = func_0019A5C8() % 30 - 15;
        o->state = 2;
    }
    if (o->t < 10) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 9;
        }
    } else if (o->c0[3] > 0x10) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    if (o->t % 2 == 1) {
        if (o->h38 < 0x12) {
            o->h38++;
        }
    }
    if (o->t % 3 == 1) {
        if (o->frame < 7) {
            o->frame++;
        }
    }
    o->x += 10.0f * func_00108030(w->trig, o->a3A, 0);
    o->y += 4.0f * func_00108030(w->trig, o->a30, 1);
    o->z += 10.0f * func_00108030(w->trig, o->a3A, 1);
    return 0;
}

/* shape b195:01E00C20, 89 insns: on start 0x38 = 8, random rotation (0x18 0x2000..0x5FFF, 0x10 -0x2000..0x1FFF,
   0x14 0), variant 0..6; alpha grows by 0x40 (below 0x80) for 2 ticks, then fades by 13 once 0x38 passes 0x19 and by
   15 while the game counter at 0x4020 is below 10; colour (0x40, 0x20, 0); 0x38 grows by 2 */

typedef struct {
    u8 pad0[0x4020];
    s32 count;
} Game_b195_01E00C20;

typedef struct {
    u8 pad0[0x10];
    s32 rot10;
    s32 rot14;
    s32 rot18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b195_01E00C20;

static s32 func_01E00C20_b195(Game_b195_01E00C20 *g, Fx_b195_01E00C20 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 8;
        o->rot18 = func_0019A5C8() % 0x4000 + 0x2000;
        o->rot10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->rot14 = 0;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        if (o->f38 > 0x19) {
            if (o->col[3] > 0xE) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    func_001076F0(o->col, 0x40, 0x20, 0);
    o->tick++;
    o->f38 += 2;
    return 0;
}

/* OVL_WARM */

/* shape b195:01E00D90, 178 insns: b192:01E01710's spark in brown (0x30/0x10/0) on the line between joints 0x4068/0x406A,
   step 5..19; it follows the line until scene frame 71, flashes in over 2 ticks, fades by 5, ends from frame 51, and
   its flicker is 7 (20 from frame 50) */

typedef struct {
    s16 x, y, z;
    s16 size;
    u8 pad8[8];
    s32 rot[2];
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 k;
    s16 t;
    s16 h34;
    s16 state;
    s16 flick;
} Spark_b195_01E00D90;

typedef struct {
    u8 pad0[0x4068];
    s16 j0;
    s16 j1;
    u8 pad406C[0x12];
    s16 frame;
} Scene_b195_01E00D90;

static s32 func_01E00D90_b195(Scene_b195_01E00D90 *g, Spark_b195_01E00D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v[2];
    f32 dx;
    f32 dy;
    f32 dz;

    func_001076F0(o->col, 0x30, 0x10, 0);
    if (o->state == 1) {
        o->rot[0] = 0x4000;
        o->rot[1] = func_0019A5C8() % 65535;
        o->h34 = 0;
        if (g->frame < 50) {
            o->size = 2;
        } else {
            o->size = 4;
        }
        o->k = func_0019A5C8() % 15 + 5;
        o->state = 2;
        o->col[3] = 0;
    }
    func_001F5620(func_001F53A0(), g->j0, &v[0]);
    func_001F5620(func_001F53A0(), g->j1, &v[1]);
    if (g->frame < 71) {
        o->x = v[1].x;
        o->y = v[1].y;
        o->z = v[1].z;
        dx = v[0].x - v[1].x;
        dy = v[0].y - v[1].y;
        dz = v[0].z - v[1].z;
        dx /= 20.0f;
        dy /= 20.0f;
        dz /= 20.0f;
        o->x += dx * o->k;
        o->y += dy * o->k;
        o->z += dz * o->k;
    }
    if (o->t < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->state = 0;
    }
    if (g->frame >= 51) {
        o->state = 0;
    }
    if (g->frame < 50) {
        o->flick = 7;
    } else {
        o->flick = 20;
    }
    o->t++;
    return 0;
}

/* OVL_WARM */

/* shape b195:01E01060, 204 insns: b112:01E01510 cousin, an orange (0x80/0x40/0) streak on joint A (g+0x4068) aimed at
   joint B (g+0x406A): on start no spin, h38 0..14, frame 0..6, hold 5..19; until scene time 51 it sits on A and its
   spin is 180 x the pitch (from the flat and full distances, func_001082B0), negated by the camera's side
   (func_001F6160, turn / 180); alpha up by 64 for 2 ticks, then down by 13 once h38 passes 25 and by 15 while the
   scene state is under 10; from time 49 its hold falls by 2 to -15 */

typedef struct {
    u8 pad0[0x4020];
    s32 state;
    u8 pad4024[0x44];
    s16 ja;
    s16 jb;
    u8 pad406C[0x12];
    s16 time;
} Game_b195_01E01060;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 hold;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 t;
    s16 h34;
    s16 mode;
    s16 h38;
} Obj_b195_01E01060;

static s32 func_01E01060_b195(Game_b195_01E01060 *g, Obj_b195_01E01060 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F6160(s32, void *);
    extern f32 func_001A6C60(f32);
    extern s16 func_001082B0(s32, s32);
    f32 v[2][4];
    s32 cam[4];
    f32 dy;
    f32 dz;
    f32 dx;
    s16 side;
    s16 r;
    s16 a;

    func_001F6160(func_001F53A0(), cam);
    side = (f32)cam[1] / 180.0f;
    if (o->mode == 1) {
        o->h38 = func_0019A5C8() % 15;
        o->w18 = 0;
        o->w10 = 0;
        o->w14 = 0;
        o->h34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->hold = func_0019A5C8() % 15 + 5;
    }
    func_001F5620(func_001F53A0(), g->ja, v[0]);
    func_001F5620(func_001F53A0(), g->jb, v[1]);
    if (g->time < 51) {
        o->x = v[0][0];
        o->y = v[0][1];
        o->z = v[0][2];
    }
    if (o->t < 2) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x40;
        }
    } else {
        if (o->h38 > 25) {
            if (o->col[3] > 14) {
                o->col[3] -= 13;
            } else {
                o->mode = 0;
            }
        }
        if (g->state < 10) {
            if (o->col[3] > 16) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (g->time >= 49) {
        if (o->hold > -15) {
            o->hold -= 2;
        }
    }
    func_001076F0(o->col, 0x80, 0x40, 0);
    dx = v[0][0] - v[1][0];
    dy = v[0][1] - v[1][1];
    dz = v[0][2] - v[1][2];
    r = func_001A6C60(dx * dx + dz * dz);
    a = func_001082B0(r, (s16)func_001A6C60(dx * dx + (dy * dy + dz * dz)));
    if (g->time < 51) {
        if (side) {
            o->w10 = a * 180;
        } else {
            o->w10 = -a * 180;
        }
    }
    o->t++;
    o->h38++;
    return 0;
}

typedef struct {
    u8 pad00[6];
    s16 h6;
    u8 pad08[0x10];
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b112_01E017B0;

static s32 func_01E01390_b195(s32 unused, Obj_b112_01E017B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    func_001076F0(o->col, 0x8F, 0x8F, 0x8F);
    if (o->h36 == 1) {
        o->h38 = func_0019A5C8() % 8 + 3;
        if (o->h30 == 0) {
            o->w18 = -0x2000;
        } else {
            o->w18 = 0x2000;
        }
        o->h6 = o->h30;
        o->h34 = func_0019A5C8() % 7;
    }
    if (o->h32 < 4) {
        if (o->col[3] < 0x80) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->col[3] > 20) {
            o->col[3] -= 0x13;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    return 0;
}

/* shape b195:01E014A0, 161 insns: a rust (0x60, 0x20, 8) ember thrown from the tracked point (ctx+0x4068) away from the scene point (ctx+0x320) at a quarter of the distance plus a random -55..50 per axis, size from 17 growing 1; full alpha 3 ticks then down by 10 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x320];
    f32 at[3];
    u8 pad32C[0x4068 - 0x32C];
    s16 id;
} Ctx_b195_01E014A0;

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 hx, hy, hz;
    u8 padE[2];
    s32 v[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 size;
    s16 f3A;
} Fx_b195_01E014A0;

static s32 func_01E014A0_b195(Ctx_b195_01E014A0 *g, Fx_b195_01E014A0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    f32 p[4];

    if (o->mode == 1) {
        o->size = 17;
        o->f34 = 2;
        func_001F5620(func_001F53A0(), g->id, p);
        o->x = p[0];
        o->y = p[1];
        o->z = p[2];
        o->v[0] = (p[0] - g->at[0]) / 4.0f;
        o->v[1] = (p[0] - g->at[1]) / 4.0f;
        o->v[2] = (p[0] - g->at[2]) / 4.0f;
        o->v[0] += (func_0019A5C8() % 22 - 11) * 5;
        o->v[1] += (func_0019A5C8() % 22 - 11) * 5;
        o->v[2] += (func_0019A5C8() % 22 - 11) * 5;
        func_001076F0(o->col, 0x60, 0x20, 8);
        o->f30 = func_0019A5C8() % 360;
        o->f3A = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 3) {
        o->col[3] = 0x80;
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->hx += (s16)o->v[0];
        o->hy += (s16)o->v[1];
        o->hz += (s16)o->v[2];
    }
    o->tick += 2;
    o->size++;
    return 0;
}

/* shape b195:01E01730, 67 insns: a brown ember of random size 10..39 (frame 6, angle -45) tipped by random turns of +-0x2000: alpha 0x40 for 5 ticks, then out by 7 and ends */

typedef struct {
    u8 pad0[0x10];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b195_01E01730;

static s32 func_01E01730_b195(s32 arg0, Glow_b195_01E01730 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = func_0019A5C8() % 30 + 10;
        o->kind = 6;
        o->ang = -45;
        func_001076F0(o->col, 0x30, 0x18, 8);
        o->w18 = func_0019A5C8() % 0x4000 + 0x2000;
        o->w10 = func_0019A5C8() % 0x4000 - 0x2000;
        o->w14 = 0;
        o->mode = 2;
    }
    if (o->tick < 5) {
        o->col[3] = 0x40;
        o->col2[3] = 0;
    } else if (o->col[3] > 10) {
        o->col[3] -= 7;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b018:01E02480, 54 insns, 11 copies: step of a fading effect: on state 1 sets its two colours, a random angle and
   state 2; full alpha for the first 5 ticks, then fades by 10 until state 0 */

typedef struct {
    u8 pad0[0x28];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b018_01E02480;

static s32 func_01E01840_b195(void *arg0, Obj_b018_01E02480 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0x14A;
        func_001076F0(o->c0, 0xC0, 0x70, 0);
        func_001076F0(o->c1, 0x20, 0x10, 0);
        o->ang = func_0019A5C8() % 360;
        o->state = 2;
        o->c1[3] = 0x10;
    }
    if (o->t < 5) {
        o->c0[3] = 0x80;
    } else if (o->c0[3] > 16) {
        o->c0[3] -= 10;
    } else {
        o->state = 0;
    }
    o->t++;
    return 0;
}

/* shape b195:01E01920, 97 insns: b112:01E02420 with the light at game 0x3E80 (end flag 0x4020); a point light for the scene: on start sets the light (colour 128/4/2, range
   63) at the effect's position; its strength rises by 0.2 up to 1, then falls by 0.08 and the effect ends; the
   light is switched off (func_001F6C10(0)) once ended, and the effect ends when the game value 0x4020 is 1 */

typedef struct {
    f32 a, b, c, d;
    f32 x, y, z;
    u8 pad1C[4];
    f32 e, f, g;
} Light_b195_01E01920;

typedef struct {
    u8 pad[0x3E80];
    Light_b195_01E01920 light;
    u8 pad302C[0x174];
    s32 v;
} Game_b195_01E01920;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b195_01E01920;

static s32 func_01E01920_b195(Game_b195_01E01920 *g, Fx_b195_01E01920 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.a = 128.0f;
        g->light.b = 4.0f;
        g->light.c = 2.0f;
        g->light.d = 0.0f;
        g->light.e = 0.0f;
        g->light.f = 63.0f;
        g->light.g = 0.0f;
        g->light.x = o->x;
        g->light.y = o->y;
        g->light.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->light.g < 1.0f) {
            g->light.g += 0.2f;
        } else {
            o->phase = 1;
        }
    } else if (g->light.g > 0.1f) {
        g->light.g -= 0.08f;
    } else {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(0);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->v == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b195:01E01AB0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x4020 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x4020];
    s32 state;
} Game_b195_01E01AB0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b195_01E01AB0;

static s32 func_01E01AB0_b195(Game_b195_01E01AB0 *g, Fade_b195_01E01AB0 *o) {
    extern void func_001F6D00(s32);

    if (o->mode == 1) {
        o->vol = 0x80;
        o->mode = 2;
    }
    if (g->state > 0x1E) {
        if (o->vol > 0x30) {
            o->vol -= 10;
        } else {
            o->vol = 0x30;
        }
    } else {
        if (o->vol < 0x80) {
            o->vol += 10;
        } else {
            o->vol = 0x80;
        }
    }
    if (g->state == 1) {
        func_001F6D00((u8)o->vol);
    } else {
        func_001F6D00((u8)o->vol);
    }
    return 0;
}

static s32 func_01E01B70_b195(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E03780_b195;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E03788_b195;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b018:01E00C50: draws a flat ring of 18 quads around a point (radius obj->radius, angle step 0x14),
   scaled 0.1, turned a quarter, through the module's GS packet. */

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx, dy, dz;
    u8 padE[0x1A];
    s32 tex0;
    s32 tex1;
    u8 pad30[8];
    s16 radius;
    s16 angle;
} Obj_b018_01E00C50;

static void func_01E01BC0_b195(u8 *self, Obj_b018_01E00C50 *obj, void *pk) {
    extern f32 func_00108030(s32, s16, s32);
    extern void func_00108EF0();
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 mat[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 a;
    s32 k;
    f32 fx;
    f32 fy;
    f32 fz;

    a = 0;
    func_00107990(pk, (u8 *)&obj->tex0, 1);
    func_00107990(pk, (u8 *)&obj->tex1, 2);
    func_001092E0(pk, 0);
    func_001094F0(pk);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = obj->dx;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(mat, &scale, rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    q[0].x = 0.0f;
    q[0].z = 0.0f;
    q[1].x = 0.0f;
    q[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        k = obj->angle + a;
        q[2].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[2].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        k = a + (obj->angle + 0x14);
        q[3].x = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 1);
        q[3].z = (f32)obj->radius * func_00108030((s32)(self + 0xD8), k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)mat, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
        a += 0x14;
    }
}

/* shape b195:01E01E50 (b195), 509 insns, 1 copy: b195 scene manager (b266:01E01D50 form): with a scene id (>= 0) it
   clears the scene, resets both cameras, keeps the id, sets the 146-frame countdown, takes three model handles, loads
   textures 0..2 and 14..15 and lays out nine 5x50 quads along a sine arc; otherwise it runs the module step and every
   live node update (B195_OBJ_MOVE_201_ written out in place), draws every live node (twice by its drawer, one
   KEMU_PAINT_1 square, or the IWCircle_G4_2 ring with frame 0x9B), grows the scene scale by 0.01 up to 0.5 after
   frame 20, counts down and returns 1 / 4 / 2 at frames 40 / 60 / 50, 8 once the countdown runs out */

typedef struct Fx_b195_01E01E50 {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 idx;
    s16 used;
    u8 pad38[0x8];
} Fx_b195_01E01E50;

typedef struct Uv_b195_01E01E50 {
    f32 a, b, c, d;
} Uv_b195_01E01E50;

typedef struct Spr_b195_01E01E50 {
    s32 texture;
    s32 tex;
    s32 c;
    s32 mode;
} Spr_b195_01E01E50;

typedef struct Scene_b195_01E01E50 {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Uv_b195_01E01E50 uv;
    u8 padA4[0xD8 - 0xA4];
    u8 cam[0x310 - 0xD8];
    f32 sx, sy, sz;
    u8 pad31C[0x340 - 0x31C];
    s32 tex[16];
    f32 m[10][16];
    u8 pad600[0x774 - 0x600];
    Fx_b195_01E01E50 fx[220];
    u8 pad3E74[0x4020 - 0x3E74];
    s32 count;
    u8 pad4024[8];
    s32 ot2;
    u8 pad4030[0x4068 - 0x4030];
    s16 model[3];
    u8 pad406E[0x407C - 0x406E];
    s16 id;
    s16 timer;
    u8 pad4080[4];
    u8 sin[0x41F0 - 0x4084];
} Scene_b195_01E01E50;

static s32 func_01E01E50_b195(s32 arg0, s32 id) {
    Scene_b195_01E01E50 *g = (Scene_b195_01E01E50 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00106080(void *, s32, s32, s32);
    extern void func_01E00780_b195();
    extern void func_01E01BC0_b195();
    extern void b195_01E02770();
    extern void b195_01E02A40();
    extern void b195_01E02D00();
    extern void b195_01E02FE0();
    extern void b195_01E03200();
    extern void b195_01E03410();
    s32 a;
    Vec4f v;
    Spr_b195_01E01E50 s;
    s32 rot[4];
    Uv_b195_01E01E50 uv;
    u8 buf[0x90] __attribute__((aligned(8)));
    f32 fc;
    s32 i;
    s32 n;

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x41F0);
        func_00107C10(g->sin);
        func_00107C10(g->cam);
        g->id = id;
        g->count = 146;
        g->sx = 0.0f;
        g->sy = 0.0f;
        g->sz = 0.0f;
        g->model[0] = func_001F5560(func_001F53A0(), 0x3E, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 0x3D, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0xD, 0);
        for (i = 0; i < 3; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        for (a = 0; a < 10; a++) {
            func_00108CE0(g->m[a], 5.0f, 50.0f);
        }
        for (i = 0; i < 9; i++) {
            g->m[i][1] = 15.0f * func_00108030(g->sin, i * 20, 0);
            g->m[i][5] = 15.0f * func_00108030(g->sin, i * 20 + 20, 0);
            g->m[i][9] = 35.0f * func_00108030(g->sin, i * 20, 0);
            g->m[i][13] = 35.0f * func_00108030(g->sin, i * 20 + 20, 0);
            fc = i * 10 - 45;
            g->m[i][0] += fc;
            g->m[i][4] += fc;
            g->m[i][8] += fc;
            g->m[i][12] += fc;
            g->m[i][1] -= 10.0f;
            g->m[i][5] -= 10.0f;
            g->m[i][9] += 15.0f;
            g->m[i][13] += 15.0f;
            g->m[i][2] = 0.0f;
            g->m[i][6] = 0.0f;
            g->m[i][10] = 0.0f;
            g->m[i][14] = 0.0f;
        }
        return 0;
    }
    func_01E00780_b195(g, 0);
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            if (g->fx[i].fn == func_01E00A00_b195) {
                func_01E00A00_b195((World_b195_01E00A00 *)g, (Wisp_b195_01E00A00 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00C20_b195) {
                func_01E00C20_b195((Game_b195_01E00C20 *)g, (Fx_b195_01E00C20 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E00D90_b195) {
                func_01E00D90_b195((Scene_b195_01E00D90 *)g, (Spark_b195_01E00D90 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01060_b195) {
                func_01E01060_b195((Game_b195_01E01060 *)g, (Obj_b195_01E01060 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01390_b195) {
                func_01E01390_b195((s32)g, (Obj_b112_01E017B0 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E014A0_b195) {
                func_01E014A0_b195((Ctx_b195_01E014A0 *)g, (Fx_b195_01E014A0 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01730_b195) {
                func_01E01730_b195((s32)g, (Glow_b195_01E01730 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01840_b195) {
                func_01E01840_b195(g, (Obj_b018_01E02480 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01920_b195) {
                func_01E01920_b195((Game_b195_01E01920 *)g, (Fx_b195_01E01920 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01AB0_b195) {
                func_01E01AB0_b195((Game_b195_01E01AB0 *)g, (Fade_b195_01E01AB0 *)&g->fx[i]);
            }
            if (g->fx[i].fn == func_01E01B70_b195) {
                f32 bb;
                f32 aa;

                *(f32 *)(u32)&aa = *(f32 *)(u32)&D_01E03780_b195;
                *(f32 *)(u32)&bb = *(f32 *)(u32)&D_01E03788_b195;
                func_001F7170(2, 0, (s32)&aa, (s32)&bb, 0);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    func_00205C40((s32)rot);
    v.z -= 25.0f;
    for (i = 0; i < 220; i++) {
        if (g->fx[i].used != 0) {
            n++;
            if (g->fx[i].fn == func_01E00A00_b195) {
                s.texture = g->tex[2];
                s.c = 0;
                s.tex = 0x14;
                s.mode = 0;
                func_01E00080_b195(g->ot2, (Obj_b058_01E00080 *)&g->fx[i], (Spr_b058_01E00080 *)&s);
            }
            if (g->fx[i].fn == func_01E00C20_b195) {
                b195_01E02A40(g, &g->fx[i], buf, 0);
                b195_01E02A40(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E00D90_b195) {
                b195_01E02770(g, &g->fx[i], buf, 0);
                b195_01E02770(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01060_b195) {
                b195_01E02D00(g, &g->fx[i], buf, 0);
                b195_01E02D00(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01390_b195) {
                b195_01E02FE0(g, &g->fx[i], buf, 0);
                b195_01E02FE0(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E014A0_b195) {
                b195_01E03200(g, &g->fx[i], buf, 0);
                b195_01E03200(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01730_b195) {
                b195_01E03410(g, &g->fx[i], buf, 0);
                b195_01E03410(g, &g->fx[i], buf, 1);
            }
            if (g->fx[i].fn == func_01E01840_b195) {
                g->tex88 = g->tex[15];
                func_00106080(&uv, 0x9B, g->fx[i].idx, 0);
                g->uv = uv;
                func_01E01BC0_b195(g, &g->fx[i], buf, 0);
            }
        }
    }
    if (g->timer > 20) {
        if (g->sx < 0.5) {
            g->sx += 0.01f;
        }
        g->sy = 0.1f;
        if (g->sz < 0.5) {
            g->sz += 0.01f;
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 40) {
        return 1;
    }
    if (g->timer == 60) {
        return 4;
    }
    if (g->timer == 50) {
        return 2;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}


/* shape b195:01E02650, 72 insns: twin of b046:01E03E20: take the first free slot of the 220-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x407A and the two arguments; returns 1 if a
   slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    u8 pad32[0x4];
    s16 used;
    u8 pad38[0x8];
} Slot_b195_01E02650;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x4A4];
    Slot_b195_01E02650 s[220];
    u8 pad3E74[0x1B0];
    u8 r, g, b, a;
    u8 pad4028[0x52];
    s16 v;
} Pool_b195_01E02650;

static s32 func_01E02650_b195(Pool_b195_01E02650 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b195_01E02650 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 220; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 220;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c0, o->r, o->g, o->b);
        s->c0[3] = o->a;
        func_001076F0(s->c1, o->r, o->g, o->b);
        s->c1[3] = o->a;
        func_00106AB0(s, o->m, 0);
        ret = 1;
        s->v = o->v;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b195:01E02770, 179 insns: b112:01E03C50's fan of 9 thin triangles scaled 1 x 1.5 x 1 at the object's
   position (no drift); mode 0 sets up the packet with texture 0x97. Texture corners by the module helper (shape
   b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b195_01E02770;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b195_01E02770;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b195_01E02770 c;
    struct {
        u64 tc;
        Xyz_b195_01E02770 p;
    } v[4];
} Pkt_b195_01E02770;

typedef struct {
    u8 pad0[0x37C];
    void *texture;
    u8 pad380[0x3CAC];
    s32 ot;
    u8 pad4030[0x24];
    f32 dep;
    u8 pad4058[0x2C];
    u8 trig[1];
} Ctx_b195_01E02770;

typedef struct {
    s16 x, y, z;
    s16 span;
    s16 vx, vy, vz;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b195_01E02770;

static void func_01E02770_b195(Ctx_b195_01E02770 *c, Fan_b195_01E02770 *o, Pkt_b195_01E02770 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b195_01E02770 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s16 span;
    s32 k;
    s32 t;
    s16 a;

    span = o->span;
    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00330_b195((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, o->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        quad[0].x = 0.0f;
        quad[0].z = 0.0f;
        t = a + (o->ang + span);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        quad[1].x = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
            func_002075F0(p, c->ot, (u32)c->dep);
        }
        a += 0x28;
    }
}

/* shape b195:01E02A40, 174 insns: b112:01E03C50's fan of 9 thin triangles with a fixed span of 2, scaled 1 x 1.5 x 1 at
   the object's position (no drift); mode 0 sets up the packet with texture 0x9B. Texture corners by the module
   helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b195_01E02A40;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b195_01E02A40;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b195_01E02A40 c;
    struct {
        u64 tc;
        Xyz_b195_01E02A40 p;
    } v[4];
} Pkt_b195_01E02A40;

typedef struct {
    u8 pad0[0x37C];
    void *texture;
    u8 pad380[0x3CAC];
    s32 ot;
    u8 pad4030[0x24];
    f32 dep;
    u8 pad4058[0x2C];
    u8 trig[1];
} Ctx_b195_01E02A40;

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b195_01E02A40;

static void func_01E02A40_b195(Ctx_b195_01E02A40 *c, Fan_b195_01E02A40 *o, Pkt_b195_01E02A40 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b195_01E02A40 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 t;
    s16 a;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x9B, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00330_b195((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, o->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        quad[0].x = 0.0f;
        quad[0].z = 0.0f;
        t = a + (o->ang + 2);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        quad[1].x = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
            func_002075F0(p, c->ot, (u32)c->dep);
        }
        a += 0x28;
    }
}

/* shape b195:01E02D00, 182 insns: b195:01E02A40's fan of 9 thin triangles (span 2) with the rim raised to the object's
   h6, scaled 1 x 1.5 x 1 at the object's position; mode 0 sets up the packet with texture 0x9B. Texture corners by the module
   helper (shape b008:01E00080). */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b195_01E02D00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b195_01E02D00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b195_01E02D00 c;
    struct {
        u64 tc;
        Xyz_b195_01E02D00 p;
    } v[4];
} Pkt_b195_01E02D00;

typedef struct {
    u8 pad0[0x37C];
    void *texture;
    u8 pad380[0x3CAC];
    s32 ot;
    u8 pad4030[0x24];
    f32 dep;
    u8 pad4058[0x2C];
    u8 trig[1];
} Ctx_b195_01E02D00;

typedef struct {
    s16 x, y, z;
    s16 h6;
    u8 pad8[8];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[8];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Fan_b195_01E02D00;

static void func_01E02D00_b195(Ctx_b195_01E02D00 *c, Fan_b195_01E02D00 *o, Pkt_b195_01E02D00 *p, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b195_01E02D00 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 t;
    s16 a;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x9B, o->page, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(o->col);
        func_01E00330_b195((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, c->texture, 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, o->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = o->h6;
    quad[3].y = o->h6;
    for (k = 0; k < 9; k++) {
        t = o->ang + a;
        quad[2].x = o->size * func_00108030(c->trig, t, 1);
        quad[2].z = o->size * func_00108030(c->trig, t, 0);
        quad[0].x = 0.0f;
        quad[0].z = 0.0f;
        t = a + (o->ang + 2);
        quad[3].x = o->size * func_00108030(c->trig, t, 1);
        quad[3].z = o->size * func_00108030(c->trig, t, 0);
        quad[1].x = 0.0f;
        quad[1].z = 0.0f;
        if (func_00205630(quad, 0x70000000, m, p, &c->dep) != 0) {
            func_002075F0(p, c->ot, (u32)c->dep);
        }
        a += 0x28;
    }
}

/* shape b195:01E02FE0, 133 insns: b120:01E03DF0's two-pass quad with 9 quads: mode 0 sets the material (frame 0x97, two
   colours, scene texture 0x37C); other modes place it at the object with a 0.4 x-scale and a -0x4000 turn, then draw each of
   the 9 quads at scene 0x380 against the matrix at 0x290 (depth 0x4054, packet list 0x402C) */

typedef struct {
    f32 x, y, z, w;
} Vec_b195_01E02FE0;

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b195_01E02FE0;

typedef struct {
    Rgbaq_b195_01E02FE0 c;
    u64 st;
    u64 xyz;
} Vtx_b195_01E02FE0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_b195_01E02FE0 v[4];
} Pkt_b195_01E02FE0;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    s32 r0;
    s32 r1;
    s32 r2;
    u8 pad1C[0xC];
    u8 col[4];
    u8 col2[4];
} Anim_b195_01E02FE0;

typedef struct {
    u8 pad00[0x290];
    u8 m[0x40];
    u8 pad2D0[0xAC];
    s32 texture;
    Vec_b195_01E02FE0 quad[9][4];
    u8 pad5C0[0x3A6C];
    s32 target;
    u8 pad4030[0x24];
    f32 depth;
} Game_b195_01E02FE0;

static void func_01E02FE0_b195(Game_b195_01E02FE0 *g, Anim_b195_01E02FE0 *an, Pkt_b195_01E02FE0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_b195_01E02FE0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_0020EB40(void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern void func_002075F0(void *, s32, s32);
    Vec_b195_01E02FE0 pos;
    f32 rm[4];
    s32 rot[4];
    Vec_b195_01E02FE0 sc;
    f32 m[16];
    s16 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(an->col);
        p->v[1].c = func_00107740(an->col);
        p->v[2].c = func_00107740(an->col2);
        p->v[3].c = func_00107740(an->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->texture, 1);
    } else {
        func_0020EB40(g->m);
        func_00106DD0(&pos, an->x, an->y, an->z);
        sc.x = 0.4f;
        sc.y = 1.0f;
        sc.z = 1.0f;
        rot[0] = an->r0 - 0x4000;
        rot[1] = 0;
        rot[2] = an->r2;
        func_0020C940(m, &sc, rot, &pos);
        func_0020BC00(g->m, m);
        for (i = 0; i < 9; i++) {
            if (func_00205630(g->quad[i], 0x70000000, g->m, p, &g->depth) != 0) {
                func_00109380(p, 0);
                func_002075F0(p, g->target, (u32)g->depth);
            }
        }
    }
}

/* shape b195:01E03200, 131 insns: b294:01E02530's sprite in two passes: mode 0 sets the material (frame 0x9B, colour,
   scene texture 0x37C), other modes draw it (depth kept at scene 0x4054, packet list 0x402C) */

typedef struct {
    f32 s;
    f32 t;
} St_b195_01E03200;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b195_01E03200 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b195_01E03200;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 dx;
    s16 dy;
    s16 dz;
    u8 padE[0x1A];
    u8 tex[8];
    u8 pad30[4];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Obj_b195_01E03200;

typedef struct {
    u8 pad0[0x37C];
    void *tex;
    u8 pad380[0x3CAC];
    s32 ctx;
    u8 pad4030[0x24];
    f32 depth[1];
} Scene_b195_01E03200;

static void func_01E03200_b195(Scene_b195_01E03200 *g, Obj_b195_01E03200 *obj, Pk_b195_01E03200 *pk, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108EF0();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    Rect_b008_01E00080 rect[2];
    Vec4f world[4];
    s32 rot[4];
    St_b195_01E03200 uv;
    f32 r;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    if (mode == 0) {
        func_00106080(rect, 0x9B, obj->h34, rect);
        pk->nreg = 0x24;
        pk->n = 9;
        pk->regs = 0x24242421 | ((s64)4 << 32);
        pk->pad4 = 0;
        pk->nreg |= 0x800;
        func_002086D0(pk, 0x48 | ((s64)0x80 << 32));
        *(s32 *)&pk->st.t = 0;
        pk->q0 = 0;
        pk->q1 = 0;
        pk->q2 = 0;
        pk->q3 = 0;
        func_00107740(&uv, obj->tex);
        pk->st = uv;
        func_01E00330_b195((Pk_b008_01E00080 *)pk, rect, 0);
        func_00208700(pk, g->tex, 1);
    } else {
        scale.x = 0.1f;
        scale.y = 0.1f;
        scale.z = 0.1f;
        func_00205C40((s32)rot);
        fx = obj->dx;
        fy = obj->dy;
        fz = obj->dz;
        fx /= 10.0f;
        fy /= 10.0f;
        fz /= 10.0f;
        pos.x = obj->x + fx;
        pos.y = obj->y + fy;
        pos.z = obj->z + fz;
        func_00108EF0(world, &scale, rot, &pos);
        r = obj->size;
        func_00108CE0(m, r, r);
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, g->depth) != 0) {
            func_002075F0((s32)pk, g->ctx, func_001A23B0(g->depth[0]));
        }
    }
}

/* OVL_WARM */

/* shape b195:01E03410, 216 insns: b018:01E03B10's ring draw with texture page 0x97, quads 4 wide (40 apart) and
   b195's ctx (target 0x402C, depth 0x4054, trig 0x4084); the corner helper (shape b008:01E00080) is the module's
   0x1E00330 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b195_01E03410;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b195_01E03410;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Rgbaq_b195_01E03410 c;
    struct {
        u64 tc;
        Xyz_b195_01E03410 p;
    } v[4];
} Pkt_b195_01E03410;

typedef struct {
    f32 x, y, z, w;
} Vec_b195_01E03410;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x18];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 radius;
    s16 start;
} Anim_b195_01E03410;

typedef struct {
    u8 pad00[0x37C];
    void *texture;
    u8 pad380[0x402C - 0x380];
    s32 target;
    u8 pad4030[0x4054 - 0x4030];
    f32 depth;
    u8 pad4058[0x4084 - 0x4058];
    u8 trig[1];
} Obj_b195_01E03410;

static void func_01E03410_b195(Obj_b195_01E03410 *o, Anim_b195_01E03410 *an, Pkt_b195_01E03410 *p, s32 draw) {
    extern void func_00106080(void *, s32, s16, void *);
    extern Rgbaq_b195_01E03410 func_00107740(void *);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b195_01E03410 quad[4];
    Vec_b195_01E03410 pos;
    Vec_b195_01E03410 scale;
    f32 m[16];
    u8 td[0x18];
    s32 k;
    s32 a;
    s16 j;

    j = 0;
    if (draw == 0) {
        func_00106080(td, 0x97, an->h34, td);
        p->count = 0x24;
        p->tag = 9;
        p->regs = ((u64)4 << 32) | 0x24242421;
        p->pad = 0;
        p->count |= 0x800;
        func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        p->c.q = 0.0f;
        p->v[0].p.f = 0;
        p->v[1].p.f = 0;
        p->v[2].p.f = 0;
        p->v[3].p.f = 0;
        p->c = func_00107740(an->col);
        func_01E00330_b195((Pk_b008_01E00080 *)p, (Rect_b008_01E00080 *)td, 0);
        func_00208700(p, o->texture, 1);
        return;
    }
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.5f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->trig, a, 1);
        quad[2].z = an->radius * func_00108030(o->trig, a, 0);
        quad[0].x = (an->radius - 17) * func_00108030(o->trig, a, 1);
        quad[0].z = (an->radius - 17) * func_00108030(o->trig, a, 0);
        a = j + (an->start + 4);
        quad[3].x = an->radius * func_00108030(o->trig, a, 1);
        quad[3].z = an->radius * func_00108030(o->trig, a, 0);
        quad[1].x = (an->radius - 17) * func_00108030(o->trig, a, 1);
        quad[1].z = (an->radius - 17) * func_00108030(o->trig, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &o->depth) != 0) {
            func_002075F0(p, o->target, (u32)o->depth);
        }
        j += 40;
    }
}
