#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec_b016_01E01190;

typedef struct {
    u8 pad00[0x80];
    s32 texture;
    u8 pad84[0x34];
    s16 count;
    u8 padBA[0x1E];
    u8 table[1];
} Obj_b016_01E01190;

typedef struct {
    u8 pad00[0x20];
    Vec_b016_01E01190 rotation;
    u8 pad30[4];
    f32 height;
    u8 pad38[0x10];
    f32 inner;
    f32 outer;
    u8 pad50[0xA];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 mode0[4];
    u8 mode1[4];
} Data_b016_01E01190;

static void func_01E00080_b388(Obj_b016_01E01190 *obj, Data_b016_01E01190 *data, s32 flags, Vec_b016_01E01190 *color) {
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    Vec_b016_01E01190 c;
    Vec_b016_01E01190 quad[4];
    Vec_b016_01E01190 pos;
    Vec_b016_01E01190 scale;
    f32 matrix[16];
    f32 depth[4];
    u8 packet[0x90];
    s16 alpha;
    s32 i;
    s16 width;
    s32 a;
    s16 j;
    f32 inner;
    u8 *pkt;
    s32 mode;
    f32 outer;

    pkt = packet;
    c = *color;
    width = data->width;
    j = 0;
    func_00107990(pkt, data->mode0, 2);
    func_00107990(pkt, data->mode1, 1);
    func_001092E0(pkt, 0);
    func_001094F0(pkt);
    alpha = flags >> 4;
    if (alpha == 0) {
        func_002086D0(pkt, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pkt, ((s64)alpha << 2) | (((u64)0x80 << 32) | 0x40));
    }
    scale.x = 0.1f;
    pos.x = c.x;
    scale.y = 0.1f;
    pos.y = c.y;
    scale.z = 0.1f;
    pos.z = c.z;
    func_00108EF0(matrix, &scale, &data->rotation, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = data->height;
    quad[3].y = data->height;
    inner = data->inner;
    outer = data->outer;
    for (i = 0; i < obj->count; i++) {
        a = data->step + j;
        quad[0].x = inner * func_00108030(obj->table, a, 1);
        quad[0].z = inner * func_00108030(obj->table, a, 0);
        quad[2].x = outer * func_00108030(obj->table, a, 1);
        quad[2].z = outer * func_00108030(obj->table, a, 0);
        a = j + (data->step + width);
        quad[1].x = inner * func_00108030(obj->table, a, 1);
        quad[1].z = inner * func_00108030(obj->table, a, 0);
        quad[3].x = outer * func_00108030(obj->table, a, 1);
        quad[3].z = outer * func_00108030(obj->table, a, 0);
        if ((flags & 0xF) == 0) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_002075F0(pkt, obj->texture, func_001A23B0(depth[0]));
            }
        } else if ((flags & 0xF) == 1) {
            if (func_00205630(quad, 0x70000000, matrix, pkt, depth) != 0) {
                func_00109380(pkt, 1);
                func_002075F0(pkt, obj->texture, 0);
            }
        }
        j += data->step;
    }
}

/* shape b388:01E003E0, 131 insns: the scene script of b388 (b236:01E01630's kind): each tick it counts g+0xB2BC; until 180
   it follows the model joint (g+0xB24C) into g+0xB1D0; from 221 to 272 it moves that point's depth by 3 (down when
   g+0xB2B8 is set); from 61 to 339 it spawns the module's two ring effects each tick, and from 311 a third; on tick 60 it
   copies the point to g+0x250 and spawns the burst effects */

typedef struct {
    f32 x, y, z, w;
} V4_b388_01E003E0;

typedef struct {
    u8 pad0[0x250];
    V4_b388_01E003E0 pos;
    u8 pad260[0xB1D0 - 0x260];
    V4_b388_01E003E0 v;
    u8 padB1E0[0x6C];
    s16 joint;
    u8 padB24E[0x6A];
    s16 down;
    u8 padB2BA[2];
    s16 tick;
} Ctx_b388_01E003E0;

static void func_01E003E0_b388(Ctx_b388_01E003E0 *g) {
    extern void b388_01E005F0();
    extern void b388_01E007F0();
    extern void b388_01E00AB0();
    extern void b388_01E00CD0();
    extern void b388_01E01570();
    extern void b388_01E01B60(Ctx_b388_01E003E0 *, void *, s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5620(s32, s32, void *);

    g->tick++;
    if (g->tick < 180) {
        func_001F5620(func_001F53A0(), g->joint, &g->v);
    }
    if (g->tick > 220 && g->tick < 273) {
        if (g->down != 0) {
            g->v.z -= 3.0f;
        } else {
            g->v.z += 3.0f;
        }
    }
    if (g->tick > 60 && g->tick < 340) {
        b388_01E01B60(g, b388_01E00CD0, 0);
        b388_01E01B60(g, b388_01E01570, 0);
        if (g->tick > 310) {
            b388_01E01B60(g, b388_01E00CD0, 0);
        }
    }
    if (g->tick == 60) {
        g->pos = g->v;
        b388_01E01B60(g, b388_01E005F0, 0);
        b388_01E01B60(g, b388_01E007F0, 0);
    }
    if (g->tick == 60) {
        b388_01E01B60(g, b388_01E00AB0, 0);
    }
}

/* shape b388:01E005F0, 127 insns: a growing blue glow placed at the scene's point (ctx+0xB1D0) and spinning 0x4000 per tick: f4C grows 0.5 to 100 before scene count 169, 3.5 to 230 before 220, 5.5 to 350 after 253; outer alpha up by 0x60 to 0xC0 until count 340, then down by 9 */

typedef struct {
    u8 pad0[0xB1D0];
    Vec4f at;
    u8 padB1E0[0xB2BC - 0xB1E0];
    s16 count;
} Ctx_b388_01E005F0;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    s32 rot[4];
    u8 pad30[0x1C];
    f32 f4C;
    u8 pad50[2];
    s16 f52;
    s16 tick;
    u8 pad56[2];
    s16 mode;
    s16 w;
    s16 h;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Fx_b388_01E005F0;

static s32 func_01E005F0_b388(Ctx_b388_01E005F0 *g, Fx_b388_01E005F0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00205C40(void *);

    if (o->mode == 1) {
        o->f4C = 4.0f;
        func_001076F0(o->col2, 0xFF, 0xFF, 0xFF);
        func_001076F0(o->col, 0x80, 0x40, 0xFF);
        o->f52 = 0;
        o->w = 10;
        o->h = 10;
        o->mode = 2;
        o->col2[3] = 0;
    }
    if (g->count < 340) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x60;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    if (g->count < 169) {
        if (o->f4C < 100.0f) {
            o->f4C += 0.5f;
        }
    } else if (g->count < 220) {
        if (o->f4C < 230.0f) {
            o->f4C += 3.5f;
        }
    } else if (g->count > 253) {
        if (o->f4C < 350.0f) {
            o->f4C += 5.5f;
        }
    }
    func_00205C40(o->rot);
    o->pos = g->at;
    o->rot[0] += 0x4000;
    o->tick++;
    return 0;
}

/* shape b388:01E007F0, 176 insns: b702:01E02790 family scene light (128, 4, 3, 5): before scene frame 341 it sits at the
   tracked point (0xB1D0), its radius grows by 5 to 100 and its level by 0.05 to 1, then it flickers between (4, 3, 5)
   and (5, 3, 6) every other tick; after that the level drops by 0.1 and the light ends; also ends when 0xB210 is 1 */

typedef struct {
    f32 c[4];
    Vec4f pos;
    f32 fC0;
    f32 fC4;
    f32 level;
} Light_b388_01E007F0;

typedef struct {
    u8 pad0[0xB1A0];
    Light_b388_01E007F0 light;
    u8 padB1CC[4];
    Vec4f src;
    u8 padB1E0[0x30];
    s32 flag;
    u8 padB214[0xA8];
    s16 frame;
} Scene_b388_01E007F0;

typedef struct {
    u8 pad0[0x50];
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
} Fx_b388_01E007F0;

static s32 func_01E007F0_b388(Scene_b388_01E007F0 *g, Fx_b388_01E007F0 *o) {
    extern void func_001F6C10(void *);

    if (o->mode == 1) {
        g->light.c[0] = 128.0f;
        g->light.c[1] = 4.0f;
        g->light.c[2] = 3.0f;
        g->light.c[3] = 5.0f;
        g->light.fC0 = 0.0f;
        g->light.fC4 = 10.0f;
        g->light.level = 0.0f;
        o->mode = 2;
        o->h50 = 0;
    }
    if (g->frame < 341) {
        g->light.pos.x = g->src.x;
        g->light.pos.y = g->src.y;
        g->light.pos.z = g->src.z;
        if (g->light.fC4 < 100.0f) {
            g->light.fC4 += 5.0f;
        }
    }
    if (g->frame < 341) {
        if (g->light.level < 1.0f) {
            g->light.level += 0.05f;
        } else if (o->t % 2 == 1) {
            g->light.c[1] = 4.0f;
            g->light.c[2] = 3.0f;
            g->light.c[3] = 5.0f;
        } else {
            g->light.c[1] = 5.0f;
            g->light.c[2] = 3.0f;
            g->light.c[3] = 6.0f;
        }
    } else if (g->light.level > 0.1f) {
        g->light.level -= 0.1f;
    } else {
        o->mode = 0;
    }
    if (g->flag == 1) {
        o->mode = 0;
    }
    if (o->mode == 0) {
        func_001F6C10(NULL);
    } else {
        func_001F6C10(&g->light);
    }
    o->t++;
    return 0;
}

/* shape b388:01E00AB0, 136 insns: b763:01E032F0 with offset 4, a grey 0x80 tint, alpha up by 20 to 0x50 while the
   scene timer at g+0xB210 is past 20, then down by 9 */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b388_01E00AB0;

typedef struct {
    f32 s, t;
    Xyz_b388_01E00AB0 p;
} Tv_b388_01E00AB0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    u8 r, g, b, a;
    f32 q;
    Tv_b388_01E00AB0 v[2];
    u8 tail[0x20];
} Tex_b388_01E00AB0;

typedef struct {
    u8 pad0[0xB210];
    s32 timer;
} Ctx_b388_01E00AB0;

typedef struct {
    u8 pad0[0x48];
    f32 f48;
    u8 pad4C[8];
    s16 tick;
    u8 pad56[2];
    s16 mode;
    u8 pad5A[6];
    u8 col[4];
} Fx_b388_01E00AB0;

static s32 func_01E00AB0_b388(Ctx_b388_01E00AB0 *g, Fx_b388_01E00AB0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_002087A0(void *, s32);
    Tex_b388_01E00AB0 pk __attribute__((aligned(8)));

    if (o->mode == 1) {
        o->f48 = 4.0f;
        func_001076F0(o->col, 0x80, 0x80, 0x80);
        o->mode = 2;
    }
    ((Tex_b388_01E00AB0 *)(s32)&pk)->flags = 0x26;
    ((Tex_b388_01E00AB0 *)(s32)&pk)->size = 5;
    ((Tex_b388_01E00AB0 *)(s32)&pk)->regs = 0x42421;
    ((Tex_b388_01E00AB0 *)(s32)&pk)->pad4 = 0;
    pk.r = o->col[0];
    pk.g = o->col[1];
    pk.b = o->col[2];
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
    pk.v[0].s = o->f48 / 1024.0f;
    pk.v[0].t = o->f48 / 512.0f;
    pk.v[1].s = (640.0f - o->f48) / 1024.0f;
    pk.v[1].t = (448.0f - o->f48) / 512.0f;
    func_002086D0(&pk, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pk, 1);
    func_002075F0((s32)&pk, (s32)func_00207500(), 0);
    if (g->timer > 20) {
        if (o->col[3] < 0x50) {
            o->col[3] += 0x14;
        }
    } else if (o->col[3] > 10) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->tick++;
    return 0;
}

/* shape b388:01E00CD0, 125 insns: b388:01E01570 with a purple ring placed on the model joint at g+0xB24C (height 33)
   and a random tilt -100..99; size grows by 4 from 10, f4C = 0.3 * size; alpha up by 21 to 0x80 for 6 ticks, then
   down by 9 until it ends; it follows the point at g+0xB1D0 */

typedef struct {
    u8 pad0[0x10];
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b388_01E00CD0;

typedef struct {
    u8 pad[0xB1D0];
    f32 x, y, z;
    u8 padB1DC[0x70];
    s16 joint;
} Game_b388_01E00CD0;

static s32 func_01E00CD0_b388(Game_b388_01E00CD0 *g, Obj_b388_01E00CD0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);

    if (o->mode == 1) {
        o->col[3] = 0;
        o->col2[3] = 0;
        func_001076F0(o->col, 0x38, 0x38, 0x38);
        func_001076F0(o->col2, 0x48, 0x28, 0x88);
        o->mode = 2;
        func_001F5620(func_001F53A0(), g->joint, &o->f10);
        o->f14 = 33.0f;
        o->f34 = (func_0019A5C8() >> 4) % 200 - 100;
        o->w20 = func_0019A5C8() % 16777215;
        o->w24 = func_0019A5C8() % 16777215;
        o->w28 = func_0019A5C8() % 16777215;
        o->f48 = 10.0f;
        o->h5A = 10;
        o->h5C = 10;
    }
    o->f48 += 4.0f;
    o->f4C = 0.3f * o->f48;
    if (o->t < 6) {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 0x15;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->t++;
    o->f10 = g->x;
    o->f14 = g->y;
    o->f18 = g->z;
    return 0;
}

/* shape b388:01E00ED0 (B388_OBJ_MOVE_203_1), 424 insns, 1 copy: b413:01E037E0 with two radii: a 36-quad wall between
   radius r1 (height y0) and r0 (height 0), each quad from angle a to a + width, a stepping by the object step; screen
   UVs from the corners, clamped to 640 x 448 */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_b388_01E00ED0;

typedef struct {
    Rgbaq_b388_01E00ED0 c;
    f32 s, t;
    u16 x, y;
    u32 z;
} Vtx_b388_01E00ED0;

typedef struct {
    u8 pad0[0x10];
    Vtx_b388_01E00ED0 v[4];
} Pkt_b388_01E00ED0;

typedef struct {
    u8 pad0[0xA];
    s16 sx;
    u8 padC[4];
    f32 x, y, z;
    u8 pad1C[4];
    s32 rot[3];
    u8 pad2C[0x34 - 0x2C];
    f32 y0;
    u8 pad38[0x48 - 0x38];
    f32 r0;
    f32 r1;
    u8 pad50[0x5A - 0x50];
    s16 step;
    s16 width;
    u8 pad5E[2];
    u8 col0[4];
    u8 col1[4];
} Obj_b388_01E00ED0;

typedef struct {
    u8 pad0[0xB22C];
    Pkt_b388_01E00ED0 *pk;
    u8 padB230[0xB4C0 - 0xB230];
    u8 sin[4];
} Scene_b388_01E00ED0;

static s32 func_01E00ED0_b388(Scene_b388_01E00ED0 *g, Obj_b388_01E00ED0 *o) {
    extern Rgbaq_b388_01E00ED0 func_00107740(void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec4f d;
    Vec4f q[4];
    Vec4f t;
    f32 m[16];
    f32 r0;
    f32 r1;
    f32 c;
    f32 s;
    f32 u;
    f32 v;
    s16 i;
    s16 a;
    s16 k;
    s16 w;

    a = 0;
    g->pk->v[0].c = func_00107740(o->col0);
    g->pk->v[1].c = func_00107740(o->col0);
    g->pk->v[2].c = func_00107740(o->col1);
    g->pk->v[3].c = func_00107740(o->col1);
    t.x = o->x;
    t.y = o->y;
    t.z = o->z;
    func_00108EF0(m, 0, o->rot, &t);
    r0 = o->r0;
    r1 = o->r1;
    q[0].y = o->y0;
    q[1].y = o->y0;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    w = o->width;
    for (i = 0; i < 36; i++) {
        c = func_00108030(g->sin, a, 1);
        s = func_00108030(g->sin, a, 0);
        q[2].x = c * r0;
        q[2].z = s * r0;
        q[0].x = c * r1;
        q[0].z = s * r1;
        k = w + a;
        c = func_00108030(g->sin, k, 1);
        s = func_00108030(g->sin, k, 0);
        q[3].x = c * r0;
        q[3].z = s * r0;
        q[1].x = c * r1;
        q[1].z = s * r1;
        a += o->step;
        if (func_00205630(q, 0x70000000, m, g->pk, &d.x) != 0) {
            u = (0x6BF8 - g->pk->v[0].x);
            v = (((o->sx + 0x720) * 16 - 8) - g->pk->v[0].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[0].s = u / 1024.0f;
            g->pk->v[0].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[1].x);
            v = (((o->sx + 0x720) * 16 - 8) - g->pk->v[1].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[1].s = u / 1024.0f;
            g->pk->v[1].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[2].x);
            v = (0x71F8 - g->pk->v[2].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[2].s = u / 1024.0f;
            g->pk->v[2].t = v / 512.0f;
            u = (0x6BF8 - g->pk->v[3].x);
            v = (0x71F8 - g->pk->v[3].y);
            u /= -16.0f;
            v /= -16.0f;
            if (u < 0.0f) u = 0.0f;
            if (u > 640.0f) u = 640.0f;
            if (v < 0.0f) v = 0.0f;
            if (v > 448.0f) v = 448.0f;
            g->pk->v[3].s = u / 1024.0f;
            g->pk->v[3].t = v / 512.0f;
            func_002075F0(g->pk, 0, 0);
        }
    }
    return 0;
}

/* shape b388:01E01570, 104 insns: a grey/white tumbling ring (three random turns, width 10 growing 4 a tick, height a tenth of it) on the scene point (ctx+0xB1D0): in by 32 up to 0xC0 for 6 ticks, then out by 9 and ends */

typedef struct {
    u8 pad0[0x10];
    f32 f10, f14, f18;
    u8 pad1C[4];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[8];
    f32 f34;
    u8 pad38[0x10];
    f32 f48;
    f32 f4C;
    s16 h50;
    u8 pad52[2];
    s16 t;
    u8 pad56[2];
    s16 mode;
    s16 h5A;
    s16 h5C;
    u8 pad5E[2];
    u8 col[4];
    u8 col2[4];
} Obj_b388_01E01570;

typedef struct {
    u8 pad[0xB1D0];
    f32 x, y, z;
} Game_b388_01E01570;

static s32 func_01E01570_b388(Game_b388_01E01570 *g, Obj_b388_01E01570 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->col[3] = 0;
        o->col2[3] = 0;
        func_001076F0(o->col, 0x38, 0x38, 0x38);
        func_001076F0(o->col2, 0xF0, 0xEF, 0xFF);
        o->mode = 2;
        o->w20 = func_0019A5C8() % 16777215;
        o->w24 = func_0019A5C8() % 16777215;
        o->w28 = func_0019A5C8() % 16777215;
        o->f48 = 10.0f;
        o->h5A = 10;
        o->h5C = 1;
    }
    o->f48 += 4.0f;
    o->f4C = 0.1f * o->f48;
    if (o->t < 6) {
        if (o->col2[3] < 0xC0) {
            o->col2[3] += 0x20;
        }
    } else if (o->col2[3] > 10) {
        o->col2[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->t++;
    o->f10 = g->x;
    o->f14 = g->y;
    o->f18 = g->z;
    return 0;
}

/* OVL_WARM */

/* shape b388:01E01710, 275 insns: b538:01E00EA0's module main for b388: keeps two order tables; with a code it clears
   the scene (0xB630 bytes), sets up its two coordinates, keeps the code and a 364-tick timer, the model's joints
   0x30/0x31/0x32/0x30/0x2F/0x2C and the camera's joint 1, textures (4,14) and (4,15), the camera's turned-back flag
   (turn / 180), scale 0.1, 256 random offsets -15..14 and thirty random 0..7 words; otherwise it runs the scene
   step (b388:01E003E0), every live slot's handler (400 of 0x70 bytes, all but b388:01E00CD0), draws the
   b388:01E005F0 slots with mode 36 (b388:01E00080) and runs b388:01E01CF0; counts the timer down and returns
   1 / 4 / 2 at steps 263 / 360 / 345, 6 between 274 and 339, 8 when the timer ends */

typedef struct {
    u8 pad0[0x10];
    u8 x10[0x34];
    s32 (*fn)(void *, void *);
    u8 pad48[0x10];
    s16 used;
    u8 pad5A[0x16];
} Slot_b388_01E01710;

typedef struct {
    u8 pad0[0x10];
    f32 sx, sy, sz;
    u8 pad1C[0x80 - 0x1C];
    s32 ot;
    u8 pad84[0xB8 - 0x84];
    s16 hB8;
    u8 padBA[0xD8 - 0xBA];
    u8 crdD8[0x260 - 0xD8];
    s32 tex[16];
    Slot_b388_01E01710 slot[400];
    u8 padB1A0[0xB210 - 0xB1A0];
    s32 timer;
    u8 padB214[8];
    s32 ot2;
    u8 padB220[0xB248 - 0xB220];
    s16 joint[6];
    u8 padB254[4];
    s16 cam;
    u8 padB25A[0xE];
    s16 hB268[30];
    u8 padB2A4[0xB2B8 - 0xB2A4];
    s16 turn;
    s16 code;
    s16 step;
    s8 noise[0x100];
    u8 padB3BE[0xB4C0 - 0xB3BE];
    u8 crdB4C0[1];
} Scene_b388_01E01710;

static s32 func_01E01710_b388(s32 arg0, s32 code) {
    extern void b388_01E00080(Scene_b388_01E01710 *, Slot_b388_01E01710 *, s32, void *);
    extern void b388_01E003E0(Scene_b388_01E01710 *, s32);
    extern s32 b388_01E005F0(void *, void *);
    extern s32 b388_01E00CD0(void *, void *);
    extern void b388_01E01CF0(Scene_b388_01E01710 *);
    s16 n;
    Scene_b388_01E01710 *g = (Scene_b388_01E01710 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F6160(s32, void *);
    extern s32 func_00202BF0(s32, s32);
    s32 ang[4];
    s32 k;
    s16 i;

    n = 0;
    g->ot2 = func_00207500();
    g->ot = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0xB630);
        func_00107C10(g->crdB4C0);
        func_00107C10(g->crdD8);
        g->code = code;
        g->timer = 364;
        g->joint[0] = func_001F5560(func_001F53A0(), 0x30, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 0x31, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 0x32, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0x30, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0x2F, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 0x2C, 0);
        g->cam = func_001F5560(func_001F5380(), 1, 1);
        for (k = 14; k < 16; k++) {
            g->tex[k] = func_00202BF0(4, k);
        }
        func_001F6160(func_001F53A0(), ang);
        g->turn = (s16)(ang[1] / 180.0f);
        g->sx = 0.1f;
        g->sy = 0.1f;
        g->sz = 0.1f;
        for (i = 0; i < 0x100; i++) {
            g->noise[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 30; i++) {
            g->hB268[i] = func_0019A5C8() % 8;
        }
        return 0;
    }
    b388_01E003E0(g, 0);
    for (i = 0; i < 400; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn != NULL && g->slot[i].fn != b388_01E00CD0) {
                g->slot[i].fn(g, &g->slot[i]);
            }
        }
    }
    for (i = 0; i < 400; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == b388_01E005F0) {
                g->hB8 = 36;
                b388_01E00080(g, &g->slot[i], 0x21, g->slot[i].x10);
                g->hB8 = 0;
            }
        }
    }
    b388_01E01CF0(g);
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 263) {
        return 1;
    }
    if (g->step == 360) {
        return 4;
    }
    if (g->step == 345) {
        return 2;
    }
    if (g->step > 273 && g->step < 340) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b388:01E01B60, 98 insns, 3 copies (b236:01E02330's code, generated by chatG/ovl/gen236.py): take a free effect slot (0x190 of 0x70 bytes), clear it, colour it from the
   owner's colour, place it at the owner's position; returns 1, or 0 if every slot is in use */

typedef struct Slot_b388_01E01B60 {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x24];
    s32 f40;
    s32 f44;
    u8 pad48[8];
    s16 f50;
    u8 pad52[6];
    s16 used;
    u8 pad5A[6];
    u8 c60[4];
    u8 c64[4];
    u8 pad68[8];
} Slot_b388_01E01B60;

typedef struct Obj_b388_01E01B60 {
    u8 pad0[0x250];
    f32 pos[3];
    u8 padA[0x2a0 - 0x250 - 12];
    Slot_b388_01E01B60 slots[0x190];
    u8 padB[0xb214 - 0x2a0 - 0x190 * 0x70];
    u8 rgba[4];
    u8 padC[0xb2b4 - 0xb214 - 4];
    s16 fB2B0;
} Obj_b388_01E01B60;

static s32 func_01E01B60_b388(Obj_b388_01E01B60 *obj, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106AB0();
    extern void func_00195108();
    Slot_b388_01E01B60 *s = NULL;
    s16 i;

    for (i = 0; i < 0x190; i++) {
        if (obj->slots[i].used == 0) {
            func_00195108(&obj->slots[i], 0x70);
            obj->slots[i].used = 1;
            s = &obj->slots[i];
            i = 0x190;
        }
    }
    if (s != NULL) {
        func_001076F0(s->c60, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c60[3] = obj->rgba[3];
        func_001076F0(s->c64, obj->rgba[0], obj->rgba[1], obj->rgba[2]);
        s->c64[3] = obj->rgba[3];
        func_00106AB0(s, obj->pos, 0);
        s->pos[0] = obj->pos[0];
        s->pos[1] = obj->pos[1];
        s->pos[2] = obj->pos[2];
        s->f50 = obj->fB2B0;
        s->f40 = arg2;
        s->f44 = arg1;
        return 1;
    }
    return 0;
}

/* shape b388:01E01CF0, 128 insns: b413:01E04E20 family module draw pass (two packets, list at ctx+0xB224): every live slot of 400 runs b388:01E00CD0 or b388:01E01570 by its callback, then b388:01E00ED0 */

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 body[0x48];
} PktA_b388_01E01CF0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    u8 body[0x68];
    u64 a;
    s32 b[4];
} PktB_b388_01E01CF0;

typedef struct {
    u8 pad00[0x44];
    void *cb;
    u8 pad48[0x10];
    s16 state;
    u8 pad5A[0x16];
} Ent_b388_01E01CF0;

typedef struct {
    u8 pad0000[0x2A0];
    Ent_b388_01E01CF0 ents[400];
    u8 pad[0xB224 - 0x2A0 - 400 * 0x70];
    s32 list;
    PktA_b388_01E01CF0 *pa;
    PktB_b388_01E01CF0 *pb;
} Mgr_b388_01E01CF0;

static void func_01E01CF0_b388(Mgr_b388_01E01CF0 *m) {
    extern void b388_01E00CD0(Mgr_b388_01E01CF0 *, Ent_b388_01E01CF0 *);
    extern void b388_01E00ED0(Mgr_b388_01E01CF0 *, Ent_b388_01E01CF0 *);
    extern void b388_01E01570(Mgr_b388_01E01CF0 *, Ent_b388_01E01CF0 *);
    extern s32 func_00207F60(void);
    extern void func_00208460(void);
    extern s32 func_00209E50(void);
    extern void func_00208800(s32, s32, void *, void *);
    extern s32 func_00207500(void);
    extern void func_00207FD0(s32, s32, s32);
    PktA_b388_01E01CF0 a __attribute__((aligned(8)));
    PktB_b388_01E01CF0 b __attribute__((aligned(8)));
    PktB_b388_01E01CF0 *p;
    s32 i;

    m->pa = &a;
    m->pb = &b;
    m->list = func_00207F60();
    m->pa->count = 0x26;
    m->pa->tag = 5;
    m->pa->regs = 0x42421;
    m->pa->pad = 0;
    m->pb->count = 0x34;
    m->pb->tag = 0xC;
    m->pb->regs = ((u64)0x4214 << 32) | 0x21421421;
    m->pb->pad = 0;
    func_00208460();
    func_002086D0(m->pb, ((u64)0x80 << 32) | 0x48);
    p = m->pb;
    func_00208800(func_00209E50(), 0, &p->a, p->b);
    func_00208460();
    for (i = 0; i < 400; i++) {
        if (m->ents[i].state == 0) {
            continue;
        }
        if (m->ents[i].cb == (void *)b388_01E00CD0) {
            b388_01E00CD0(m, &m->ents[i]);
            b388_01E00ED0(m, &m->ents[i]);
        }
        if (m->ents[i].cb == (void *)b388_01E01570) {
            b388_01E01570(m, &m->ents[i]);
            b388_01E00ED0(m, &m->ents[i]);
        }
    }
    func_00207FD0(m->list, func_00207500(), 0);
}
