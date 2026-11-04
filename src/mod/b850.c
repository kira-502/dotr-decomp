#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b004_01E00B40;

static s32 func_01E00080_b850(Vec_b004_01E00B40 *trail, s32 n, s32 arg2) {
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

/* shape b027:01E02300, 162 insns, 8 copies: a fan of 18 quads (centre at the origin, outer edge on a circle of
   radius data->radius, 20 angle units per step) sent through the caller's packet; same family as b016:01E01190 */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02300;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x54];
    u8 table[1];
} Obj_b027_01E02300;

typedef struct {
    s16 x, y, z;
    u8 pad06[2];
    s16 dx, dy, dz;
    u8 pad0E[0x1A];
    u8 mode0[4];
    u8 mode1[4];
    u8 pad30[8];
    s16 radius;
    s16 step;
} Data_b027_01E02300;

static void func_01E00150_b850(Obj_b027_01E02300 *obj, Data_b027_01E02300 *data, void *pkt) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b027_01E02300 quad[4];
    Vec_b027_01E02300 pos;
    Vec_b027_01E02300 scale;
    f32 matrix[16];
    f32 depth[4];
    s32 rot[4];
    s32 i;
    s16 j;
    s32 a;
    f32 fx;
    f32 fy;
    f32 fz;

    j = 0;
    func_00107990(pkt, data->mode0, 1);
    func_00107990(pkt, data->mode1, 2);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[0] += 0x4000;
    fx = data->dx;
    fy = data->dy;
    fz = data->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = data->x + fx;
    pos.y = data->y + fy;
    pos.z = data->z + fz;
    func_00108EF0(matrix, &scale, rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    quad[0].x = 0.0f;
    quad[0].z = 0.0f;
    quad[1].x = 0.0f;
    quad[1].z = 0.0f;
    for (i = 0; i < 18; i++) {
        a = data->step + j;
        quad[2].x = data->radius * func_00108030(obj->table, a, 1);
        quad[2].z = data->radius * func_00108030(obj->table, a, 0);
        a = j + (data->step + 20);
        quad[3].x = data->radius * func_00108030(obj->table, a, 1);
        quad[3].z = data->radius * func_00108030(obj->table, a, 0);
        if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
            func_00109380(pkt, 1);
            func_002075F0(pkt, obj->texture, 0);
        }
        j += 20;
    }
}

/* OVL_WARM */

typedef struct {
    f32 x, y, z, w;
} Vec_b027_01E02590;

typedef struct {
    s16 x, y, z;
    u8 pad06[0xA];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b027_01E02590;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    u8 b94[0x24];
    s16 count;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 bD8[1];
} Obj_b027_01E02590;

static void func_01E003E0_b850(Obj_b027_01E02590 *o, Anim_b027_01E02590 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b027_01E02590 quad[4];
    Vec_b027_01E02590 pos;
    Vec_b027_01E02590 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 0);
    func_00108500(p, o->b94, o->hBE);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    for (k = 0; k < 9; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + 20) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + 20) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 2);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + 20) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + 20) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 40;
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b850", func_01E006E0_b850);

/* shape b850:01E00C20, 92 insns: scene colour (0x80, 0, 0, 0); count 0x2E38 up; at 0x8B place the scene at model
   point 0x2E1C and run b850:01E015B0 once and b850:01E00FB0 / b850:01E01160 12 times each; between 0x88 and 0xA9 place
   it again and run b850:01E012F0; at 1 run b850:01E01A60; all through b850:01E02290 */

typedef struct {
    u8 pad0[0x250];
    f32 pos[3];
    u8 pad25C[0x2DF4 - 0x25C];
    u8 col[4];
    u8 pad2DF8[0x24];
    s16 point;
    u8 pad2E1E[0x1A];
    s16 count;
} Scene_b850_01E00C20;

static void func_01E00C20_b850(Scene_b850_01E00C20 *g) {
    extern void b850_01E00FB0(void);
    extern void b850_01E01160(void);
    extern void b850_01E012F0(void);
    extern void b850_01E015B0(void);
    extern void b850_01E01A60(void);
    extern void b850_01E02290(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    f32 pt[4];
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->count++;
    if (g->count == 0x8B) {
        func_001F5620(func_001F53A0(), g->point, pt);
        g->pos[0] = pt[0];
        g->pos[1] = pt[1];
        g->pos[2] = pt[2];
        b850_01E02290(g, b850_01E015B0, 0);
        for (i = 0; i < 12; i++) {
            b850_01E02290(g, b850_01E00FB0, 0);
        }
        for (i = 0; i < 12; i++) {
            b850_01E02290(g, b850_01E01160, 0);
        }
    }
    if (g->count > 0x87 && g->count < 0xAA) {
        func_001F5620(func_001F53A0(), g->point, pt);
        g->pos[0] = pt[0];
        g->pos[1] = pt[1];
        g->pos[2] = pt[2];
        b850_01E02290(g, b850_01E012F0, 0);
    }
    if (g->count == 1) {
        b850_01E02290(g, b850_01E01A60, 0);
    }
}

/* shape b850:01E00D90, 134 insns: b207:01E029A0 with the manager count at 0x2DF0 */

typedef struct {
    u8 pad0000[0x2DF0];
    s32 w3B00;
} Mgr_b850_01E00D90;

typedef struct {
    u8 pad00[6];
    s16 h6;
    s16 h8;
    u8 pad0A[4];
    s16 hE;
    s32 w10;
    s32 w14;
    u8 pad18[0x10];
    u8 c28[4];
    u8 c2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
} Obj_b850_01E00D90;

static s32 func_01E00D90_b850(Mgr_b850_01E00D90 *m, Obj_b850_01E00D90 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    s32 base;

    if (o->h36 == 1) {
        o->h38 = 70;
        base = 0;
        o->w10 = func_0019A5C8() % 0x4000 + base;
        o->w14 = func_0019A5C8() % 0xFFFF;
        o->h34 = func_0019A5C8() % 7;
        o->h36 = 2;
        o->hE = func_0019A5C8() % 3 + 4;
        o->h6 = 1;
        if (o->h30 == 0) {
            func_001076F0(o->c28, 0x80, 0x40, 0);
        } else {
            func_001076F0(o->c28, 0, 0x80, 0x80);
        }
    }
    if (o->h32 < 2) {
        if (o->c28[3] < 0xA0) {
            o->c28[3] += 0x50;
        }
    } else {
        if (o->h38 < 12) {
            if (o->c28[3] > 20) {
                o->c28[3] -= 19;
            } else {
                o->h36 = 0;
            }
        }
        if (o->h38 < -12) {
            o->h36 = 0;
        }
        if (m->w3B00 < 10) {
            if (o->c28[3] > 16) {
                o->c28[3] -= 15;
            } else {
                o->h36 = 0;
            }
        }
    }
    if (o->h32 % 2 == 1) {
        func_001076F0(o->c28, 0x80, 0x40, 0);
    } else {
        func_001076F0(o->c28, 0xB0, 0x80, 0);
    }
    o->h32++;
    o->h38 -= o->hE;
    return 0;
}

/* shape b850:01E00FB0, 106 insns: on start 0x38 = 0, random rotation, variant 0..6, speed 2..4 (0xE), 0x6 = 1, colour
   0x80 grey; alpha grows by 0x50 (below 0xA0) for 2 ticks; after that it fades by 19 once 0x38 passes 0x46, stops when
   0x38 drops below -12, and fades by 15 while the game counter 0x2DF0 is below 10; 0x38 grows by the speed */

typedef struct {
    u8 pad0[0x2DF0];
    s32 count;
} Game_b850_01E00FB0;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[6];
    s16 speed;
    s32 rot[3];
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
} Fx_b850_01E00FB0;

static s32 func_01E00FB0_b850(Game_b850_01E00FB0 *g, Fx_b850_01E00FB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->rot[0] = func_0019A5C8() % 0xFFFF;
        o->rot[1] = func_0019A5C8() % 0xFFFF;
        o->rot[2] = func_0019A5C8() % 0xFFFF;
        o->f34 = func_0019A5C8() % 7;
        o->mode = 2;
        o->speed = func_0019A5C8() % 3 + 2;
        o->f6 = 1;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
    }
    if (o->tick < 2) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x50;
        }
    } else {
        if (o->f38 > 0x46) {
            if (o->col[3] > 0x14) {
                o->col[3] -= 19;
            } else {
                o->mode = 0;
            }
        }
        if (o->f38 < -12) {
            o->mode = 0;
        }
        if (g->count < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    o->tick++;
    o->f38 += o->speed;
    return 0;
}

/* shape b850:01E01160, 100 insns: a blue tumbling burst: frame 10 growing by 2..3 once started, random turn on all three axes,
   width 15; both colours blue at full alpha on the first frame, then both down by 7, the first ending it */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 grow;
    u8 padA[6];
    s32 rot0;
    s32 rot1;
    s32 rot2;
    u8 pad1C[0xC];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b850_01E01160;

static s32 func_01E01160_b850(void *arg0, Obj_b850_01E01160 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 0xA;
        o->rot0 = func_0019A5C8() % 65535;
        o->rot2 = func_0019A5C8() % 65535;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = 0;
        o->state = 2;
        o->grow = func_0019A5C8() % 2 + 2;
        o->h6 = 0xF;
        func_001076F0(o->c0, 0x30, 0x30, 0xA0);
        func_001076F0(o->c1, 0x30, 0x30, 0xA0);
    }
    if (o->t < 1) {
        if (o->c0[3] < 0x80) {
            o->c0[3] = 0x80;
        }
        if (o->c1[3] < 0x80) {
            o->c1[3] = 0x80;
        }
    } else {
        if (o->c0[3] > 8) {
            o->c0[3] -= 7;
        } else {
            o->state = 0;
        }
        if (o->c1[3] > 8) {
            o->c1[3] -= 7;
        } else {
            o->c1[3] = 0;
        }
    }
    if (o->t != 0) {
        o->h38 += o->grow;
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 pad00[0x28];
    u8 col0[4];
    u8 col1[4];
    s16 h30;
    s16 h32;
    u8 pad34[2];
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b207_01E03000;

static s32 func_01E012F0_b850(s32 unused, Obj_b207_01E03000 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->h36 == 1) {
        o->h38 = 60;
        func_001076F0(o->col0, 0x80, 0x80, 0x80);
        func_001076F0(o->col1, 0xC0, 0xC0, 0);
        o->h3A = o->h30;
        o->h36 = 2;
        o->col1[3] = 0;
    }
    if (o->h32 <= 0) {
        o->col0[3] += 0x50;
    } else {
        if (o->col0[3] > 10) {
            o->col0[3] -= 9;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    if (o->h38 < 0) {
        o->h38 -= 2;
    }
    return 0;
}

/* shape b850:01E013C0, 123 insns: a yellow-white circling glow on a model joint: frame 40, angle from its start value; alpha up by 4 for
   18 frames, then flickering 0x40/0x50; sits on the joint, circling 3 around it as the angle turns 10 a frame; ends at frame 211 */

typedef struct {
    u8 pad0[0x2E1C];
    s16 joint;
    u8 pad2E1E[0x11E];
    u8 sin[1];
} Game_b850_01E013C0;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 c1[4];
    s16 ang0;
    s16 t;
    u8 pad34[2];
    s16 state;
    s16 h38;
    s16 ang;
} Obj_b850_01E013C0;

static s32 func_01E013C0_b850(Game_b850_01E013C0 *g, Obj_b850_01E013C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    extern s16 func_001A22C0(f32);
    struct {
        f32 x, y, z, w;
        f32 pad[4];
    } v;

    func_00108030(g->sin, o->ang, 0);
    if (o->state == 1) {
        o->h38 = 0x28;
        func_001076F0(o->c0, 0x80, 0x80, 0x80);
        func_001076F0(o->c1, 0xC0, 0xC0, 0);
        o->ang = o->ang0;
        o->state = 2;
        o->c1[3] = 0;
    }
    if (o->t < 0x12) {
        o->c0[3] += 4;
    } else if (o->t % 2 == 1) {
        o->c0[3] = 0x40;
    } else {
        o->c0[3] = 0x50;
    }
    func_001F5620(func_001F53A0(), g->joint, &v);
    o->x = func_001A22C0(v.x);
    o->y = func_001A22C0(v.y);
    o->z = func_001A22C0(v.z);
    o->x = func_001A22C0(o->x + 3.0f * func_00108030(g->sin, o->ang, 0));
    o->z = func_001A22C0(o->z + 3.0f * func_00108030(g->sin, o->ang, 1));
    o->t++;
    if (o->t > 0xD2) {
        o->state = 0;
    }
    o->ang += 0xA;
    if (o->ang >= 0x168) {
        o->ang %= 360;
    }
    return 0;
}

/* shape b850:01E015B0, 54 insns: variant of b257:01E031C0 (flash): start block as below; alpha grows by 0x60
   for the first 2 ticks, then fades out by 15 and stops */

typedef struct {
    u8 pad0[6];
    s16 life;
    u8 pad8[0x20];
    u8 col[4];
    u8 col2[4];
    u8 pad30[2];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
    s16 dir;
} Flash_b850_01E015B0;

static s32 func_01E015B0_b850(s32 arg0, Flash_b850_01E015B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0x12C;
        func_001076F0(o->col, 0xF0, 0xF0, 0xF0);
        func_001076F0(o->col2, 0x40, 0x40, 0xF0);
        o->dir = func_0019A5C8() % 360;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (o->tick < 2) {
        o->col[3] += 0x60;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 15;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b850:01E01690, 173 insns: b482:01E02E40 family scene flash light (ctx+0x2890, 0xC4 70) at the effect's point: warms by 42/21/10 toward orange while the level rises 0.2 to 1, then cools by 16/16/8 and dims 0.1 to 0.1; ends when ctx+0x2DF0 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b850_01E01690;

typedef struct {
    u8 pad0[0x2890];
    Light_b850_01E01690 light;
    u8 padL[0x2DF0 - 0x2890 - 0x2C];
    s32 flag;
} Scene_b850_01E01690;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x2A];
    s16 phase;
    u8 pad32[4];
    s16 mode;
} Fx_b850_01E01690;

static s32 func_01E01690_b850(Scene_b850_01E01690 *g, Fx_b850_01E01690 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.c[0] = 0.0f;
        g->light.c[1] = 0.0f;
        g->light.c[2] = 0.0f;
        g->light.c[3] = 0.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 70.0f;
        g->light.level = 0.0f;
        g->light.pos.x = o->x;
        g->light.pos.y = o->y;
        g->light.pos.z = o->z;
        o->mode = 2;
        o->phase = 0;
    }
    if (o->phase == 0) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.2f;
        } else {
            o->phase = 1;
        }
        if (g->light.c[0] < 128.0f) {
            g->light.c[0] += 42.0f;
        } else {
            g->light.c[0] = 128.0f;
        }
        if (g->light.c[1] < 64.0f) {
            g->light.c[1] += 21.0f;
        } else {
            g->light.c[1] = 128.0f;
        }
        if (g->light.c[2] < 32.0f) {
            g->light.c[2] += 10.0f;
        } else {
            g->light.c[2] = 64.0f;
        }
    } else {
        if (g->light.level > 0.1f) {
            g->light.level -= 0.1f;
        } else {
            o->mode = 0;
        }
        if (g->light.c[0] > 16.0f) {
            g->light.c[0] -= 16.0f;
        } else {
            g->light.c[0] = 0.0f;
        }
        if (g->light.c[1] > 16.0f) {
            g->light.c[1] -= 16.0f;
        } else {
            g->light.c[1] = 0.0f;
        }
        if (g->light.c[2] > 8.0f) {
            g->light.c[2] -= 8.0f;
        } else {
            g->light.c[2] = 0.0f;
        }
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    return 0;
}

/* shape b443:01E03FF0, 47 insns: constant variant of b205:01E01E50 (volume fade by game state): state at 0x2DF0 limit 0x1F,
   floor 0x30, down 10, up 10, cap 0x80 */

typedef struct {
    u8 pad[0x2DF0];
    s32 state;
} Game_b443_01E03FF0;

typedef struct {
    u8 pad[0x30];
    s16 vol;
    u8 pad32[4];
    s16 mode;
} Fade_b443_01E03FF0;

static s32 func_01E01950_b850(Game_b443_01E03FF0 *g, Fade_b443_01E03FF0 *o) {
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

static s32 func_01E01A10_b850(void) {
    f32 a;
    f32 b;

    *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02400_b850;
    *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02408_b850;
    func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
    return 0;
}

/* shape b850:01E01A60, 101 insns: a screen tint: builds a grey (0x80) full-screen textured sprite (0x6BF8,0x71F8 -
   0x93F8,0x8DF8, uv 0..0.625 x 0..0.875) in the effect's alpha on the stack and sends it; the alpha grows by 12
   (below 0x60) while the game step 0x2E38 is below 0x50, then fades by 9 and stops */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b850_01E01A60;

typedef struct {
    f32 s, t;
    Xyz_b850_01E01A60 p;
} Tv_b850_01E01A60;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b850_01E01A60 v[2];
    u8 tail[0x20];
} Tex_b850_01E01A60;

typedef struct {
    u8 pad0[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
} Fx_b850_01E01A60;

typedef struct {
    u8 pad0[0x2E38];
    s16 step;
} Game_b850_01E01A60;

static s32 func_01E01A60_b850(Game_b850_01E01A60 *g, Fx_b850_01E01A60 *o) {
    Tex_b850_01E01A60 pk __attribute__((aligned(8)));

    ((Tex_b850_01E01A60 *)(s32)&pk)->count = 0x26;
    ((Tex_b850_01E01A60 *)(s32)&pk)->tag = 5;
    ((Tex_b850_01E01A60 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b850_01E01A60 *)(s32)&pk)->pad = 0;
    pk.r = 0x80;
    pk.g = 0x80;
    pk.b = 0x80;
    pk.a = o->col[3];
    pk.q = 1.0f;
    pk.v[0].p.x = 0x6BF8;
    pk.v[0].p.y = 0x71F8;
    pk.v[0].p.z = 0xFFFFFF;
    pk.v[0].p.f = 0;
    pk.v[1].p.x = 0x93F8;
    pk.v[1].p.y = 0x8DF8;
    pk.v[1].p.z = 0xFFFFFF;
    pk.v[1].p.f = 0;
    pk.v[0].s = 0.0f;
    pk.v[0].t = 0.0f;
    pk.v[1].s = 0.625f;
    pk.v[1].t = 0.875f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->step < 0x50) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b850:01E01C00 (b850), 420 insns, 1 copy: b850 scene manager (b294:01E01DE0 form): with a scene id (>= 0) it
   clears the scene, resets both camera blocks, keeps the id, sets the 200-frame countdown, takes five model handles,
   loads textures 14..15, 2 and page-5 textures 0..1 and fills the jitter table with -15..14; otherwise it runs the
   module script, at frame 1 sets the nine trail points to the first model, steps the trail and every live node (the
   01E01A10 node inlined: a func_001F7170 call), draws the scattered-line, scattered-circle and circle nodes, counts
   down and returns 1 / 4 / 2 / 6 at frames 129 / 175 / 155 / 140..149, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 h34;
    s16 used;
    u8 pad38[8];
} Node_b850_01E01C00;

typedef struct {
    u8 pad0[0x80];
    s32 ot2;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    union {
        Vec4f rect;
        s16 h94;
    } u;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[4];
    s16 hBE;
    u8 padC0[0x18];
    u8 camD8[0x1D8];
    s32 tex[16];
    Node_b850_01E01C00 node[150];
    s32 tex5[2];
    u8 pad2878[0x28E0 - 0x2878];
    Vec4f pt[9];
    u8 trail[0x2DF0 - 0x2970];
    s32 count;
    u8 pad2DF4[8];
    s32 ot;
    u8 pad2E00[0x1C];
    s16 model[5];
    u8 pad2E26[0x10];
    s16 id;
    s16 timer;
    u8 pad2E3A[2];
    s8 rnd[256];
    u8 cam[0x174];
} Scene_b850_01E01C00;

static s32 func_01E01C00_b850(s32 arg0, s32 id) {
    Scene_b850_01E01C00 *g = (Scene_b850_01E01C00 *)arg0;
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern s32 func_00202BF0(s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_01E00C20_b850();
    extern void func_01E00080_b850();
    extern void func_01E00150_b850();
    extern void func_01E003E0_b850();
    extern void func_01E006E0_b850();
    extern s32 func_01E00D90_b850();
    extern s32 func_01E00FB0_b850();
    extern s32 func_01E01160_b850();
    extern s32 func_01E012F0_b850();
    extern s32 func_01E013C0_b850();
    extern s32 func_01E015B0_b850();
    extern s32 func_01E01690_b850();
    extern s32 func_01E01950_b850();
    extern s32 func_01E01A10_b850();
    extern s32 func_01E01A60_b850();
    s32 n;
    Vec4f v;
    Vec4f r1;
    Vec4f r2;
    Vec4f r3;
    Vec4f r4;
    Vec4f t;
    u8 buf[0x90] __attribute__((aligned(8)));
    f32 b;
    f32 a;
    s32 i;

    n = 0;
    g->ot2 = (s32)func_00207500();
    g->ot = (s32)func_00207500();
    if (id >= 0) {
        func_00195108(g, 0x30B0);
        func_00107C10(g->cam);
        func_00107C10(g->camD8);
        g->id = id;
        g->count = 200;
        g->model[0] = func_001F5560(func_001F53A0(), 3, 1);
        g->model[1] = func_001F5560(func_001F53A0(), 4, 0);
        g->model[2] = func_001F5560(func_001F53A0(), 0x1A, 0);
        g->model[3] = func_001F5560(func_001F53A0(), 0x6A, 0);
        g->model[4] = func_001F5560(func_001F53A0(), 0x40, 0);
        for (i = 14; i < 16; i++) {
            g->tex[i] = func_00202BF0(4, i);
        }
        g->tex[2] = func_00202BF0(4, 2);
        for (i = 0; i < 2; i++) {
            g->tex5[i] = func_00202BF0(5, i);
        }
        for (i = 0; i < 256; i++) {
            g->rnd[i] = func_0019A5C8() % 30 - 15;
        }
        return 0;
    }
    func_01E00C20_b850(g, 0);
    if (g->timer == 1) {
        Vec4f *p = g->pt;
        func_001F5620(func_001F53A0(), g->model[0], (s32)&t);
        for (i = 0; i < 9; i++, p++) {
            p->x = t.x;
            p->y = t.y;
            p->z = t.z;
        }
    }
    func_01E00080_b850(g->trail, 10, g->model[0]);
    for (i = 0; i < 150; i++) {
        if (g->node[i].used != 0) {
            if (g->node[i].fn == func_01E00D90_b850) {
                func_01E00D90_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E00FB0_b850) {
                func_01E00FB0_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01160_b850) {
                func_01E01160_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E012F0_b850) {
                func_01E012F0_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E013C0_b850) {
                func_01E013C0_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E015B0_b850) {
                func_01E015B0_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01690_b850) {
                func_01E01690_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01950_b850) {
                func_01E01950_b850(g, &g->node[i]);
            }
            if (g->node[i].fn == func_01E01A10_b850) {
                *(f32 *)(u32)&a = *(f32 *)(u32)&D_01E02400_b850;
                *(f32 *)(u32)&b = *(f32 *)(u32)&D_01E02408_b850;
                func_001F7170(2, 0, (s32)&a, (s32)&b, 0);
            }
            if (g->node[i].fn == func_01E01A60_b850) {
                func_01E01A60_b850(g, &g->node[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), &v);
    for (i = 0; i < 150; i++) {
        if (g->node[i].used != 0) {
            n++;
            if (g->node[i].fn == func_01E00D90_b850) {
                g->tex88 = g->tex[15];
                func_00106080(&r1, 0x9B, g->node[i].h34, 0);
                g->u.rect = r1;
                g->hB8 = 1;
                func_01E003E0_b850(g, &g->node[i], buf, 0);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E00FB0_b850) {
                g->tex88 = g->tex5[0];
                func_00106080(&r2, 0x14, g->node[i].h34, 0);
                g->u.rect = r2;
                g->hBE = 0;
                g->hB8 = 1;
                func_01E003E0_b850(g, &g->node[i], buf, 0);
                g->hB8 = 0;
            }
            if (g->node[i].fn == func_01E01160_b850) {
                g->tex88 = g->tex[15];
                func_00106080(&r3, 0x97, g->node[i].h34, 0);
                g->u.rect = r3;
                g->hB8 = 0;
                g->u.h94 = 160;
                func_01E006E0_b850(g, &g->node[i], buf, 0);
            }
            if (g->node[i].fn == func_01E012F0_b850) {
                g->tex88 = g->tex[15];
                func_00106080(&r4, 0x97, g->node[i].h34, 0);
                g->u.rect = r4;
                g->hB8 = 4;
                g->hB8 = 0;
                func_01E00150_b850(g, &g->node[i], buf, 0);
            }
            if (g->node[i].fn == func_01E013C0_b850) {
                func_01E00150_b850(g, &g->node[i], buf, 0);
            }
            if (g->node[i].fn == func_01E015B0_b850) {
                func_01E00150_b850(g, &g->node[i], buf, 0);
            }
        }
    }
    if (g->count != 0) {
        g->count--;
    }
    if (g->timer == 129) {
        return 1;
    }
    if (g->timer == 175) {
        return 4;
    }
    if (g->timer == 155) {
        return 2;
    }
    if (g->timer > 139 && g->timer < 150) {
        return 6;
    }
    if (g->count <= 0) {
        return 8;
    }
    return 0;
}

/* shape b850:01E02290, 72 insns: twin of b046:01E03E20: take the first free slot of the 150-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x2E34 and the two arguments; returns 1 if a
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
} Slot_b850_01E02290;

typedef struct {
    u8 pad[0x250];
    u8 m[0xA0];
    Slot_b850_01E02290 s[150];
    u8 pad2870[0x584];
    u8 r, g, b, a;
    u8 pad2DF8[0x3C];
    s16 v;
} Pool_b850_01E02290;

static s32 func_01E02290_b850(Pool_b850_01E02290 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b850_01E02290 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 150; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 150;
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
