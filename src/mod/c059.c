#include "common.h"

/* shape c059:01E00080, 173 insns: c006:01E00710 family model setup: picks the first three models flagged in the scene mask (ctx+0x2CC0, bit 21 - i; ids 11..21 become i + 0xF5), switches all 22 on, then readies the three picked ones (random size, spin, speed, turn), registers them, places each 35 out from its scene point (ctx+0x29B0), tags them (ctx+0x2960) and gives them alpha 0x80 */

typedef struct {
    u8 pad0[4];
    s32 w4;
    u8 pad8[0x20];
    s32 w28;
    u8 pad2C[8];
    s32 w34;
    s32 w38;
    u8 pad3C[0x14];
    f32 v50[4];
    u8 col[4];
    s32 w64;
    u8 pad68[8];
} Obj_c059_01E00080;

typedef struct {
    u8 pad0[0x2650];
    Obj_c059_01E00080 obj[3];
    u8 pad27A0[0x2960 - 0x27A0];
    f32 tags[3][4];
    u8 pad2990[0x29B0 - 0x2990];
    f32 at[3][4];
    u8 pad29E0[0x2CAC - 0x29E0];
    s32 ids[3];
    u8 pad2CB8[8];
    u32 mask;
} Scene_c059_01E00080;

static void func_01E00080_c059(Scene_c059_01E00080 *g) {
    extern void func_001F5970(s32, s32);
    extern void func_001F5BD0(s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    extern void func_001099E0(void *, void *, void *, f32);
    Vec4f v;
    s16 i;
    s16 id;
    s32 n;
    s32 m;
    Obj_c059_01E00080 *p;

    n = 0;
    for (i = 0; i < 22; i++) {
        if (n < 3) {
            if ((g->mask >> (21 - i)) & 1) {
                id = i;
                if (i > 10) {
                    id = i + 0xF5;
                }
                g->ids[n] = id;
                n++;
            }
        }
    }
    for (i = 0; i < 22; i++) {
        m = i;
        if (m > 10) {
            m += 0xF6;
        }
        func_001F5970(m, 1);
    }
    for (i = 0; i < 3; i++) {
        n = g->ids[i];
        p = &g->obj[i];
        p->w64 = 0;
        p->v50[1] = (func_0019A5C8() % 26 + 9) / 6;
        p->w28 = func_0019A5C8() % 8 + 5;
        p->w34 = func_0019A5C8() % 0x1800 + 0x100;
        p->w38 = func_0019A5C8() % 0x800 - 0x400;
        func_001F5BD0(n, p);
        p->w4 = 0;
        func_001F5B70(n, p);
        if (i < 3) {
            func_001099E0(&v, g->at[i], p, 35.0f);
            *(Vec4f *)p->v50 = v;
        }
        func_001F5CA0(g->ids[i], g->tags[i]);
        func_001F5E40(n, p->col);
        p->col[3] = 0x80;
        func_001F5DE0(n, p->col);
    }
}

/* shape c059:01E00340 (C059_CARD_EAREY_2), 157 insns, 1 copy: the scene's sound setup: lists the voices whose bit
   (21 - k) is set in 0x2CC0 (k + 0xF5 above 10), switches all 22 voices on, then for each of three sparks picks a
   size 9..34 / 6, a step 5..12 (signed %8), a speed 0x100..0x18FF and a turn -0x400..0x3FF, places it 35 out along
   its path, aims the listed voice at it and sets that voice's volume byte to 0x80 */

typedef struct {
    f32 x, y, z, w;
} V4_c059_01E00340;

typedef struct {
    u8 pad0[0x28];
    s32 step;
    u8 pad2C[8];
    s32 speed;
    s32 turn;
    u8 pad3C[0x14];
    V4_c059_01E00340 pos;
    u8 col[4];
    s32 h64;
    u8 pad68[8];
} Spark_c059_01E00340;

typedef struct {
    u8 pad0[0x2650];
    Spark_c059_01E00340 sp[3];
    u8 pad27A0[0x1C0];
    u8 at[3][16];
    u8 pad2990[0x20];
    u8 path[3][16];
    u8 pad29E0[0x2CC];
    s32 ch[5];
    u32 mask;
} Scene_c059_01E00340;

static void func_01E00340_c059(Scene_c059_01E00340 *g) {
    extern void func_001F5970(s32, s32);
    extern void func_001099E0(void *, void *, void *, f32);
    extern void func_001F5CA0(s32, void *);
    extern void func_001F6490(s32, void *);
    extern void func_001F63E0(s32, void *);
    V4_c059_01E00340 v;
    Spark_c059_01E00340 *o;
    s16 k;
    s16 i;
    s32 n;
    s32 c;

    n = 0;
    for (k = 0; k < 22; k++) {
        if ((g->mask >> (21 - k)) & 1) {
            c = k;
            if (c > 10) {
                c += 0xF5;
            }
            g->ch[n++] = c;
        }
    }
    for (i = 0; i < 22; i++) {
        c = i;
        if (c > 10) {
            c += 0xF5;
        }
        func_001F5970(c, 1);
    }
    for (i = 0; i < 3; i++) {
        c = g->ch[i];
        o = &g->sp[i];
        o->h64 = 0;
        o->pos.y = (func_0019A5C8() % 26 + 9) / 6;
        o->step = func_0019A5C8() % 8 + 5;
        o->speed = func_0019A5C8() % 0x1800 + 0x100;
        o->turn = func_0019A5C8() % 0x800 - 0x400;
        if (i < 3) {
            func_001099E0(&v, g->path[i], o, 35.0f);
            o->pos = v;
        }
        func_001F5CA0(g->ch[i], g->at[i]);
        func_001F6490(c, o->col);
        o->col[3] = 0x80;
        func_001F63E0(c, o->col);
    }
}


/* shape c059:01E005C0, 68 insns: brings a sound channel up (channels past 10 are shifted by 0xF5): while the scene's
   state is below 10, fades a playing channel that is none of the three reserved ones and raises its volume byte by 16
   up to 0x80 */

typedef struct {
    u8 pad0[0x2A50];
    s32 state;
    u8 pad2A54[0x258];
    s32 res[3];
} Ctx_c059_01E005C0;

static s32 func_01E005C0_c059(Ctx_c059_01E005C0 *c, s32 arg1, s32 ch) {
    extern s32 func_001F5EC0(s32);
    extern s32 func_001F5AF0(s32);
    extern void func_00107370(s32, s32, f32);
    extern void func_001F5E40(s32, void *);
    extern void func_001F5DE0(s32, void *);
    u8 vol[4];
    s32 n;

    n = ch;
    if (ch > 0xA) {
        n = ch + 0xF5;
    }
    if (c->state < 0xA) {
        if (func_001F5EC0(n) != 0) {
            if (c->res[0] != n && c->res[1] != n && c->res[2] != n) {
                func_00107370(n, 0, 0.15f);
            }
        }
        if (func_001F5AF0(n) != 0) {
            func_001F5E40(n, vol);
            if (c->res[0] != n && c->res[1] != n && c->res[2] != n) {
                vol[3] += 0x10;
                if (vol[3] > 0x80) {
                    vol[3] = 0x80;
                }
                func_001F5DE0(n, vol);
            }
        }
    }
    return 0;
}

/* shape c059:01E006D0, 278 insns: steer one c059 card toward its slot: state 0 slides it in x/z until both are within 5
   (counting arrivals), lifts it to 30, then aims it at the centre; state 1 eases it in until 7 from the centre, then
   state 2 lifts it to 130 and fades it near the centre; the card's model follows its point and the camera's turn */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    f32 dx;
    u8 pad14[4];
    f32 dz;
    u8 pad1C[4];
    s32 rot[4];
    s32 ax;
    s32 ay;
    u8 pad38[4];
    s32 f3C;
    u8 pad40[0x10];
    f32 vx;
    f32 vy;
    f32 vz;
    u8 pad5C[4];
    u8 col[4];
    s32 state;
} Card_c059_01E006D0;

typedef struct {
    u8 pad0[0x29B0];
    Vec4f slot[0xF];
    u8 pad2AA0[2];
    s16 step;
    u8 pad2AA4[0x8C];
    u8 table[0x17C];
    s32 ch[4];
    s32 arrived;
} Scene_c059_01E006D0;

static s32 func_01E006D0_c059(Scene_c059_01E006D0 *g, Card_c059_01E006D0 *o, s32 idx) {
    extern s32 func_001F5AF0(s32);
    extern f32 func_001A6C60(f32);
    extern void func_00107130(void *, void *, s32);
    extern void func_00107B90(f32 *, f32 *, void *, void *);
    extern void func_001F5DE0(s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    extern void func_001F5B70(s32, void *);
    extern void func_00205C40();
    extern void func_001F5C40(s32, void *);
    s32 r[4];
    Vec4f v;
    Vec4f p;
    f32 dx;
    f32 dz;
    s32 ch;
    s16 n;
    f32 d;

    ch = g->ch[idx];
    n = 0;
    dx = 0.0f;
    dz = 0.0f;
    if (func_001F5AF0(ch) != 0) {
        d = func_001A6C60((o->x + o->dx) * (o->x + o->dx) + (o->z + o->dz) * (o->z + o->dz));
        func_00107130(o, &v, 1);
        if (o->state == 0) {
            func_00107B90(&dx, &dz, o, &g->slot[idx]);
            if (dx > 5.0f) {
                o->dx += o->vx;
            } else {
                n++;
                g->arrived++;
            }
            if (dz > 5.0f) {
                o->dz += o->vz;
            } else {
                n++;
                g->arrived++;
            }
            if (o->y < 30.0f) {
                o->y += o->vy / 5.0f;
            } else if (n == 2) {
                g->arrived++;
                o->vx = -(o->x + o->dx) / 35.0f;
                o->vz = -(o->z + o->dz) / 35.0f;
            }
        } else if (o->state == 2) {
            if (o->y < 130.0f) {
                o->y += o->vy;
            }
            if (d < 45.0f) {
                if (o->col[3] > 8) {
                    o->col[3] -= 7;
                } else {
                    o->col[3] = 0;
                }
                func_001F5DE0(ch, o->col);
            }
        }
        v.x += o->dx;
        v.z += o->dz;
        if (o->state == 1) {
            if (d > 7.0f) {
                o->dx += o->vx / 2.0f;
                o->dz += o->vz / 2.0f;
            } else {
                o->state = 2;
            }
            func_00108950(&v, o->rot, 0, g->table);
            o->rot[1] += 6;
        }
        func_00107130(&p, &v, 0);
        func_001F5B70(ch, &p);
        if (o->state > 0) {
            func_00205C40(r);
            func_001F5C40(ch, r);
        } else if (o->rot[3] == 0.0f) {
            func_00205C40(r);
            if (r[1] > o->ay) {
                o->ay += 0x800;
            } else {
                o->ay -= 0x800;
                o->f3C = 1;
            }
            if (r[0] > o->ax) {
                o->ax += 0x300;
            } else {
                o->ax -= 0x300;
            }
            func_001F5C40(ch, &o->ax);
        } else {
            func_00205C40(r);
            func_001F5C40(ch, r);
        }
        if (g->step > 0x67) {
            o->col[3] = 0;
            func_001F5DE0(ch, o->col);
        }
    }
    return 0;
}

/* shape c059:01E00B30, 278 insns: steer one c059 card toward its slot: state 0 slides it in x/z until both are within 5
   (counting arrivals), lifts it to 30, then aims it at the centre; state 1 eases it in until 7 from the centre, then
   state 2 lifts it to 130 and fades it near the centre; its height eases toward the model's own by a sixth a tick, and the model follows its point */

typedef struct {
    f32 x, y, z;
    u8 padC[4];
    f32 dx;
    f32 dy;
    f32 dz;
    u8 pad1C[4];
    s32 rot[4];
    s32 ax;
    s32 ay;
    u8 pad38[4];
    s32 f3C;
    u8 pad40[0x10];
    f32 vx;
    f32 vy;
    f32 vz;
    u8 pad5C[4];
    u8 col[4];
    s32 state;
} Card_c059_01E00B30;

typedef struct {
    u8 pad0[0x29B0];
    Vec4f slot[0xF];
    u8 pad2AA0[2];
    s16 step;
    u8 pad2AA4[0x8C];
    u8 table[0x16C];
    f32 h[4];
    s32 ch[4];
    s32 arrived;
} Scene_c059_01E00B30;

static s32 func_01E00B30_c059(Scene_c059_01E00B30 *g, Card_c059_01E00B30 *o, s32 idx) {
    extern s32 func_001F5EC0(s32);
    extern f32 func_001F5860(s32);
    extern void func_001F63E0(s32, void *);
    extern void func_001F5F00(s32, void *);
    extern f32 func_001A6C60(f32);
    extern void func_00107130(void *, void *, s32);
    extern void func_00107B90(f32 *, f32 *, void *, void *);
    extern void func_001F5DE0(s32, void *);
    extern void func_00108950(void *, void *, s32, void *);
    Vec4f v;
    Vec4f p;
    f32 dx;
    f32 dz;
    s32 ch;
    s16 n;
    f32 d;

    ch = g->ch[idx];
    n = 0;
    if (func_001F5EC0(ch) != 0) {
        d = func_001A6C60((o->x + o->dx) * (o->x + o->dx) + (o->z + o->dz) * (o->z + o->dz));
        func_00107130(o, &v, 1);
        if (o->state == 0) {
            func_00107B90(&dx, &dz, o, &g->slot[idx]);
            if (dx > 5.0f) {
                o->dx += o->vx;
            } else {
                n++;
                g->arrived++;
            }
            if (dz > 5.0f) {
                o->dz += o->vz;
            } else {
                n++;
                g->arrived++;
            }
            if (o->y + o->dy < 30.0f) {
                o->dy += o->vy / 5.0f;
            } else if (n == 2) {
                g->arrived++;
                o->vx = -(o->x + o->dx) / 35.0f;
                o->vz = -(o->z + o->dz) / 35.0f;
            }
        } else if (o->state == 2) {
            if (o->y + o->dy < 130.0f) {
                o->dy += o->vy;
            }
            if (d < 45.0f) {
                if (o->col[3] > 8) {
                    o->col[3] -= 7;
                } else {
                    o->col[3] = 0;
                }
                func_001F63E0(ch, o->col);
            }
        }
        v.x += o->dx;
        v.z += o->dz;
        v.y += o->dy;
        if (o->state == 1) {
            if (d > 7.0f) {
                if (d > 27.0f) {
                    o->dx += o->vx / 2.0f;
                    o->dz += o->vz / 2.0f;
                } else {
                    o->dx += o->vx / 3.0f;
                    o->dz += o->vz / 3.0f;
                }
            } else {
                o->state = 2;
            }
            func_00108950(&v, o->rot, 0, g->table);
            o->rot[1] += 6;
        }
        if (ch >> 8 != 0) {
            if (g->h[idx] > func_001F5860(ch)) {
                g->h[idx] -= func_001F5860(ch) / 6.0f;
            } else if (g->h[idx] < func_001F5860(ch)) {
                g->h[idx] += func_001F5860(ch) / 6.0f;
            }
        }
        v.z += g->h[idx];
        func_00107130(&p, &v, 0);
        func_001F5F00(ch, &p);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E00FB0_c059);

/* shape c059:01E01BB0, 75 insns: takes the first free of 48 effect slots (0x58 bytes, c021:01E028F0 shape), marks it with its
   index + 1, colours both from the context, copies the context's point and stores both arguments */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x18];
    s32 a2;
    s32 a1;
    u8 c40[4];
    u8 c44[4];
    s16 used;
    u8 pad4A[0xE];
} Slot_c059_01E01BB0;

typedef struct {
    u8 pad0[0x290];
    Slot_c059_01E01BB0 slots[0x30];
    u8 pad[0x2A20 - 0x290 - 0x30 * 0x58];
    Vec4f pos;
    u8 pad2A30[0x24];
    u8 rgba[4];
} Ctx_c059_01E01BB0;

static void func_01E01BB0_c059(Ctx_c059_01E01BB0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    s16 i;
    Slot_c059_01E01BB0 *s;

    for (i = 0; i < 0x30; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x58);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c44, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c44[3] = ctx->rgba[3];
        func_001076F0(s->c40, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c40[3] = ctx->rgba[3];
        s->pos = ctx->pos;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

/* OVL_WARM */

/* shape c059:01E01CE0, 127 insns: spawn a trail sprite: take the first free one of the 48 0x58-byte slots at g+0x290
   (cleared, marked with its index + 1), copy the scene's colour (g+0x2A54) into both colours, the position g+0x2A20, the
   rotation g+0x2A40..48 as integers, the scene's mode words, height = g+0x2A48 and height + 20, each at most 200, and link
   it at the head of the scene's list (g+0x2A5C) with the two arguments */

typedef struct {
    f32 x, y, z, w;
} V4_c059_01E01CE0;

typedef struct Ent_c059_01E01CE0 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[4];
    V4_c059_01E01CE0 pos;
    u8 pad20[0x10];
    struct Ent_c059_01E01CE0 *prev;
    struct Ent_c059_01E01CE0 *next;
    s32 w38;
    s32 w3C;
    u8 c40[4];
    u8 c44[4];
    s16 active;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
} Ent_c059_01E01CE0;

typedef struct {
    u8 pad0[0x290];
    Ent_c059_01E01CE0 ent[48];
    u8 pad1310[0x1710];
    V4_c059_01E01CE0 pos;
    u8 pad2A30[0x10];
    f32 rx;
    f32 ry;
    f32 rz;
    u8 pad2A4C[8];
    u8 col[4];
    u8 pad2A58[4];
    Ent_c059_01E01CE0 *head;
    u8 pad2A60[0x30];
    s16 h2A90;
    u8 pad2A92[4];
    s16 h2A96;
    u8 pad2A98[4];
    s16 h2A9C;
} Scene_c059_01E01CE0;

static void func_01E01CE0_c059(Scene_c059_01E01CE0 *g, s32 a, s32 b) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106CC0(void *, s32);
    s16 i;
    Ent_c059_01E01CE0 *e;

    for (i = 0; i < 48; i++) {
        if (g->ent[i].active == 0) {
            e = &g->ent[i];
            func_00106CC0(e, 0x58);
            g->ent[i].active = i + 1;
            goto found;
        }
    }
    e = 0;
found:
    if (e != 0) {
        func_001076F0(e->c44, g->col[0], g->col[1], g->col[2]);
        e->c44[3] = g->col[3];
        func_001076F0(e->c40, g->col[0], g->col[1], g->col[2]);
        e->c40[3] = g->col[3];
        e->pos = g->pos;
        e->h4E = g->rx;
        e->h50 = g->ry;
        e->h4C = g->rz;
        e->h4A = g->h2A90;
        e->prev = g->head;
        e->h56 = g->h2A9C;
        e->h52 = g->h2A96;
        if (e->prev == 0) {
            e->h2 = g->rz;
            e->hA = e->h2 + 20;
        } else {
            e->h2 = g->rz;
            e->hA = e->h2 + 20;
        }
        if (e->h2 > 200) {
            e->h2 = 200;
        }
        if (e->hA > 200) {
            e->hA = 200;
        }
        e->prev = g->head;
        if (e->prev != 0) {
            e->prev->next = e;
        }
        e->w38 = b;
        e->w3C = a;
        g->head = e;
    }
}

/* OVL_WARM */

/* shape c059:01E01EE0, 127 insns: spawn a trail sprite: take the first free one of the 48 0x58-byte slots at g+0x290
   (cleared, marked with its index + 1), copy the scene's colour (g+0x2A54) into both colours, the position g+0x2A20, the
   rotation g+0x2A40..48 as integers, the scene's mode words, height = g+0x2A48 and height + 20, each at most the scene's limit (g+0x2CD0), and link
   it at the head of the scene's list (g+0x2A5C) with the two arguments */

typedef struct {
    f32 x, y, z, w;
} V4_c059_01E01EE0;

typedef struct Ent_c059_01E01EE0 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[4];
    V4_c059_01E01EE0 pos;
    u8 pad20[0x10];
    struct Ent_c059_01E01EE0 *prev;
    struct Ent_c059_01E01EE0 *next;
    s32 w38;
    s32 w3C;
    u8 c40[4];
    u8 c44[4];
    s16 active;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
} Ent_c059_01E01EE0;

typedef struct {
    u8 pad0[0x290];
    Ent_c059_01E01EE0 ent[48];
    u8 pad1310[0x1710];
    V4_c059_01E01EE0 pos;
    u8 pad2A30[0x10];
    f32 rx;
    f32 ry;
    f32 rz;
    u8 pad2A4C[8];
    u8 col[4];
    u8 pad2A58[4];
    Ent_c059_01E01EE0 *head;
    u8 pad2A60[0x30];
    s16 h2A90;
    u8 pad2A92[4];
    s16 h2A96;
    u8 pad2A98[4];
    s16 h2A9C;
    u8 pad2A9E[0x232];
    s16 limit;
} Scene_c059_01E01EE0;

static void func_01E01EE0_c059(Scene_c059_01E01EE0 *g, s32 a, s32 b) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106CC0(void *, s32);
    s16 i;
    Ent_c059_01E01EE0 *e;

    for (i = 0; i < 48; i++) {
        if (g->ent[i].active == 0) {
            e = &g->ent[i];
            func_00106CC0(e, 0x58);
            g->ent[i].active = i + 1;
            goto found;
        }
    }
    e = 0;
found:
    i = g->limit;
    if (e != 0) {
        func_001076F0(e->c44, g->col[0], g->col[1], g->col[2]);
        e->c44[3] = g->col[3];
        func_001076F0(e->c40, g->col[0], g->col[1], g->col[2]);
        e->c40[3] = g->col[3];
        e->pos = g->pos;
        e->h4E = g->rx;
        e->h50 = g->ry;
        e->h4C = g->rz;
        e->h4A = g->h2A90;
        e->prev = g->head;
        e->h56 = g->h2A9C;
        e->h52 = g->h2A96;
        if (e->prev == 0) {
            e->h2 = g->rz;
            e->hA = e->h2 + 20;
        } else {
            e->h2 = g->rz;
            e->hA = e->h2 + 20;
        }
        if (e->h2 > i) {
            e->h2 = i;
        }
        if (e->hA > i) {
            e->hA = i;
        }
        e->prev = g->head;
        if (e->prev != 0) {
            e->prev->next = e;
        }
        e->w38 = b;
        e->w3C = a;
        g->head = e;
    }
}

/* OVL_WARM */

/* shape c059:01E020E0, 139 insns: c059:01E01CE0's ribbon node: kinds 0 and 1 get height rz and width rz + 28 (capped 180), the node copies the previous node's point, handler 0x1E031C0, flag 0x54 set */

typedef struct {
    f32 x, y, z, w;
} V4_c059_01E020E0;

typedef struct Ent_c059_01E020E0 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[4];
    V4_c059_01E020E0 pos;
    V4_c059_01E020E0 p20;
    struct Ent_c059_01E020E0 *prev;
    struct Ent_c059_01E020E0 *next;
    s32 w38;
    s32 w3C;
    u8 c40[4];
    u8 c44[4];
    s16 active;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    s16 h54;
    s16 h56;
} Ent_c059_01E020E0;

typedef struct {
    u8 pad0[0x290];
    Ent_c059_01E020E0 ent[48];
    u8 pad1310[0x1710];
    V4_c059_01E020E0 pos;
    u8 pad2A30[0x10];
    f32 rx;
    f32 ry;
    f32 rz;
    u8 pad2A4C[8];
    u8 col[4];
    u8 pad2A58[4];
    Ent_c059_01E020E0 *head;
    u8 pad2A60[0x30];
    s16 h2A90;
    u8 pad2A92[4];
    s16 h2A96;
    u8 pad2A98[4];
    s16 h2A9C;
} Scene_c059_01E020E0;

static void func_01E020E0_c059(Scene_c059_01E020E0 *g, s32 a) {
    extern void c059_01E031C0();
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106CC0(void *, s32);
    s16 i;
    Ent_c059_01E020E0 *e;
    Ent_c059_01E020E0 *p;

    for (i = 0; i < 48; i++) {
        if (g->ent[i].active == 0) {
            e = &g->ent[i];
            func_00106CC0(e, 0x58);
            g->ent[i].active = i + 1;
            goto found;
        }
    }
    e = 0;
found:
    if (e != 0) {
        func_001076F0(e->c44, g->col[0], g->col[1], g->col[2]);
        e->c44[3] = g->col[3];
        func_001076F0(e->c40, g->col[0], g->col[1], g->col[2]);
        e->c40[3] = g->col[3];
        e->pos = g->pos;
        e->h4E = g->rx;
        e->h50 = g->ry;
        e->h4C = g->rz;
        e->h4A = g->h2A90;
        e->prev = g->head;
        e->h56 = g->h2A9C;
        e->h52 = g->h2A96;
        if (e->h56 == 0) {
            e->h2 = g->rz;
            e->hA = e->h2 + 28;
            if (e->hA > 180) {
                e->hA = 180;
            }
        } else if (e->h56 == 1) {
            e->h2 = g->rz;
            e->hA = e->h2 + 28;
            if (e->hA > 180) {
                e->hA = 180;
            }
        }
        e->prev = g->head;
        p = e->prev;
        if (p != 0) {
            e->p20 = p->p20;
            p->next = e;
        }
        e->w38 = (s32)c059_01E031C0;
        e->w3C = a;
        e->h54 = 1;
        g->head = e;
    }
}

/* shape c059:01E02310, 84 insns: takes the first free of 40 effect slots (0x30 bytes, c059:01E01BB0 shape), marks it with its
   index + 1, colours both from the context at alpha 0, copies two frames, links it to the context's parent effect (taking
   its point twice and pointing it back), frame 5, and stores both arguments */

typedef struct Slot_c059_01E02310 {
    s16 x0, y0, z0;
    u8 pad6[2];
    s16 x, y, z;
    u8 padE[2];
    struct Slot_c059_01E02310 *parent;
    struct Slot_c059_01E02310 *child;
    s32 a2;
    s32 a1;
    u8 c20[4];
    u8 c24[4];
    s16 used;
    s16 f2A;
    s16 f2C;
    s16 f2E;
} Slot_c059_01E02310;

typedef struct {
    u8 pad0[0x1C30];
    Slot_c059_01E02310 slots[0x28];
    u8 pad[0x2A54 - 0x1C30 - 0x28 * 0x30];
    u8 rgba[4];
    u8 pad2A58[4];
    Slot_c059_01E02310 *parent;
    u8 pad2A60[0x36];
    s16 f2A96;
    u8 pad2A98[4];
    s16 f2A9C;
} Ctx_c059_01E02310;

static void func_01E02310_c059(Ctx_c059_01E02310 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    s16 i;
    Slot_c059_01E02310 *s;
    Slot_c059_01E02310 *p;

    for (i = 0; i < 0x28; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x30);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c24, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c24[3] = 0;
        func_001076F0(s->c20, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c20[3] = 0;
        s->f2A = ctx->f2A96;
        s->f2E = ctx->f2A9C;
        s->parent = ctx->parent;
        p = s->parent;
        if (p != NULL) {
            p->child = s;
            s->x0 = s->x = p->x;
            s->y0 = s->y = p->y;
            s->z0 = s->z = p->z;
        }
        s->f2C = 5;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

/* shape c059:01E02460, 93 insns: takes the first free of 48 effect slots (0x58 bytes), marks it with its index + 1, colours
   both from the context, copies its four floats, turns its three angles into shorts, copies four settings, frame 0, and
   stores both arguments */

typedef struct {
    f32 x, y, z, w;
} V3_c059_01E02460;

typedef struct {
    u8 pad0[0x10];
    V3_c059_01E02460 v;
    u8 pad20[0x10];
    s32 f30;
    u8 pad34[4];
    s32 a2;
    s32 a1;
    u8 c40[4];
    u8 c44[4];
    s16 used;
    s16 f4A;
    s16 f4C;
    s16 f4E;
    s16 f50;
    s16 f52;
    s16 t;
    s16 f56;
} Slot_c059_01E02460;

typedef struct {
    u8 pad0[0x290];
    Slot_c059_01E02460 slots[0x30];
    u8 pad[0x2A20 - 0x290 - 0x30 * 0x58];
    V3_c059_01E02460 v;
    u8 pad2A30[0x10];
    f32 r[3];
    u8 pad2A4C[8];
    u8 rgba[4];
    u8 pad2A58[4];
    s32 f2A5C;
    u8 pad2A60[0x30];
    s16 f2A90;
    u8 pad2A92[4];
    s16 f2A96;
    u8 pad2A98[4];
    s16 f2A9C;
} Ctx_c059_01E02460;

static void func_01E02460_c059(Ctx_c059_01E02460 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    extern s16 func_001A22C0(f32);
    s16 i;
    Slot_c059_01E02460 *s;

    for (i = 0; i < 0x30; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x58);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c44, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c44[3] = ctx->rgba[3];
        func_001076F0(s->c40, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c40[3] = ctx->rgba[3];
        s->v = ctx->v;
        s->f4E = func_001A22C0(ctx->r[0]);
        s->f50 = func_001A22C0(ctx->r[1]);
        s->f4C = func_001A22C0(ctx->r[2]);
        s->f4A = ctx->f2A90;
        s->f30 = ctx->f2A5C;
        s->f56 = ctx->f2A9C;
        s->f52 = ctx->f2A96;
        s->t = 0;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

/* shape c059:01E025E0, 92 insns: c059:01E01BB0 family: take the first free slot of 48 (0x58 bytes), clear it, mark it with its index + 1, give it the scene colour twice, position, three turns (fptosi of ctx+0x2A40..48), ids and both arguments */

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x10];
    s32 w30;
    u8 pad34[4];
    s32 a2;
    s32 a1;
    u8 c40[4];
    u8 c44[4];
    s16 used;
    s16 h4A;
    s16 h4C;
    s16 h4E;
    s16 h50;
    s16 h52;
    u8 pad54[2];
    s16 h56;
} Slot_c059_01E025E0;

typedef struct {
    u8 pad0[0x290];
    Slot_c059_01E025E0 slots[0x30];
    u8 pad[0x2A20 - 0x290 - 0x30 * 0x58];
    Vec4f pos;
    u8 pad2A30[0x10];
    f32 rx, ry, rz;
    u8 pad2A4C[8];
    u8 rgba[4];
    u8 pad2A58[4];
    s32 w2A5C;
    u8 pad2A60[0x30];
    s16 h2A90;
    u8 pad2A92[4];
    s16 h2A96;
    u8 pad2A98[4];
    s16 h2A9C;
} Ctx_c059_01E025E0;

static void func_01E025E0_c059(Ctx_c059_01E025E0 *ctx, s32 arg1, s32 arg2) {
    extern void func_001076F0();
    extern void func_00106CC0();
    extern s16 func_001A22C0(f32);
    s16 i;
    Slot_c059_01E025E0 *s;

    for (i = 0; i < 0x30; i++) {
        if (ctx->slots[i].used == 0) {
            s = &ctx->slots[i];
            func_00106CC0(s, 0x58);
            ctx->slots[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->c44, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c44[3] = ctx->rgba[3];
        func_001076F0(s->c40, ctx->rgba[0], ctx->rgba[1], ctx->rgba[2]);
        s->c40[3] = ctx->rgba[3];
        s->pos = ctx->pos;
        s->h4E = func_001A22C0(ctx->rx);
        s->h50 = func_001A22C0(ctx->ry);
        s->h4C = func_001A22C0(ctx->rz);
        s->h4A = ctx->h2A90;
        s->w30 = ctx->w2A5C;
        s->h56 = ctx->h2A9C;
        s->h52 = ctx->h2A96;
        s->a2 = arg2;
        s->a1 = arg1;
    }
}

/* shape c059:01E02750, 80 insns: take a free row (0x1B of 0x30 bytes at 0x1720), clear it, mark it with its index + 1;
   colour it from the scene colour 0x2A54, attach it to the scene points 0x2A20 / 0x2A10, one random roll thrown away,
   0x2A from the scene float 0x2A40, random 0x2C 0..1, scale 1, 0x2E from 0x2A9C, store arg */

typedef struct {
    u8 pad0[0x10];
    f32 sx, sy, sz;
    u8 pad1C[4];
    s32 arg;
    u8 col[4];
    s16 used;
    s16 f2A;
    s16 f2C;
    s16 f2E;
} Row_c059_01E02750;

typedef struct {
    u8 pad0[0x1720];
    Row_c059_01E02750 rows[0x1B];
    u8 pad1C30[0x2A10 - 0x1C30];
    u8 p2A10[0x10];
    u8 p2A20[0x20];
    f32 f2A40;
    u8 pad2A44[0x10];
    u8 rgba[4];
    u8 pad2A58[0x44];
    s16 f2A9C;
} Scene_c059_01E02750;

static void func_01E02750_c059(Scene_c059_01E02750 *g, s32 arg1, s32 arg) {
    extern void func_00106CC0(void *, s32);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106AB0(void *, void *, s32);
    s16 i;
    Row_c059_01E02750 *s;

    for (i = 0; i < 0x1B; i++) {
        if (g->rows[i].used == 0) {
            s = &g->rows[i];
            func_00106CC0(s, 0x30);
            g->rows[i].used = i + 1;
            goto found;
        }
    }
    s = NULL;
found:
    if (s != NULL) {
        func_001076F0(s->col, g->rgba[0], g->rgba[1], g->rgba[2]);
        s->col[3] = g->rgba[3];
        func_00106AB0(s, g->p2A20, 0);
        func_0019A5C8();
        s->f2A = g->f2A40;
        s->f2C = func_0019A5C8() % 2;
        func_00106AB0(s, g->p2A10, 1);
        s->sx = 1.0f;
        s->sy = 1.0f;
        s->sz = 1.0f;
        s->f2E = g->f2A9C;
        s->arg = arg;
    }
}

/* shape c059:01E02890, 67 insns: take a free slot (10 of 0x3C bytes at 0x23B0), clear it, mark it with its index + 1;
   attach it to the scene points 0x2A20 (mode 0) and 0x2A10 (mode 1), 0x30 from the scene float 0x2A40, 0x32/0x28 from
   0x2A90/0x2A9C, store the two arguments */

typedef struct {
    u8 pad0[0x20];
    s32 a2;
    s32 a1;
    s16 f28;
    u8 pad2A[4];
    s16 used;
    s16 f30;
    s16 f32;
    u8 pad34[8];
} Slot_c059_01E02890;

typedef struct {
    u8 pad0[0x23B0];
    Slot_c059_01E02890 slots[10];
    u8 pad2608[0x2A10 - 0x2608];
    u8 p2A10[0x10];
    u8 p2A20[0x20];
    f32 f2A40;
    u8 pad2A44[0x4C];
    s16 f2A90;
    u8 pad2A92[0xA];
    s16 f2A9C;
} Scene_c059_01E02890;

static void func_01E02890_c059(Scene_c059_01E02890 *g, s32 a1, s32 a2) {
    extern void func_00195108();
    extern void func_00106AB0(void *, void *, s32);
    Slot_c059_01E02890 *s = NULL;
    s16 i;

    for (i = 0; i < 10; i++) {
        if (g->slots[i].used == 0) {
            func_00195108(&g->slots[i], 0x3C);
            g->slots[i].used = i + 1;
            s = &g->slots[i];
            i = 10;
        }
    }
    if (s != NULL) {
        func_00106AB0(s, g->p2A20, 0);
        s->f30 = g->f2A40;
        s->f32 = g->f2A90;
        s->f28 = g->f2A9C;
        func_00106AB0(s, g->p2A10, 1);
        s->a2 = a2;
        s->a1 = a1;
    }
}

/* shape c059:01E029A0, 153 insns: c059:01E02C10 family band of 8 segments (45 degrees apart) between this object's ring and its linked parent's (or its own inner radius), heights swaying 10 by sines of the scene phase plus 4x the objects' angles; colours from the parent (or this object) and this object */

typedef struct Obj_c059_01E029A0 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[0x24];
    struct Obj_c059_01E029A0 *link;
    u8 pad34[0xC];
    u8 c40[4];
    u8 c44[4];
    u8 pad48[2];
    s16 h4A;
    u8 pad4C[2];
    s16 h4E;
    s16 h50;
} Obj_c059_01E029A0;

typedef struct {
    u8 pad0[0x250];
    Vec4f q[4];
    u8 pad290[0x2644 - 0x290];
    s32 tex;
    u8 pad2648[0x2A94 - 0x2648];
    s16 phase;
    u8 pad2A96[0x2ACC - 0x2A96];
    s32 ot;
    u8 pad2AD0[0x2B30 - 0x2AD0];
    u8 tab[1];
} Scn_c059_01E029A0;

static void func_01E029A0_c059(Scn_c059_01E029A0 *g, Obj_c059_01E029A0 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00106CF0(void *, s16, s32, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108FF0(void *, void *, s32, s32);
    f32 m[4];
    s32 i;
    Obj_c059_01E029A0 *prev;
    s32 a;

    prev = o->link;
    a = 0;
    if (lit == 0) {
        func_00106080(m, 0x9C, 0, m);
        func_00108500(p, m, 1);
        func_00208700(p, g->tex, 1);
    } else {
    g->q[1].y = g->q[0].y = 10.0f * func_00108030(g->tab, g->phase + o->h2 * 4, 0);
    g->q[3].y = g->q[2].y = 10.0f * func_00108030(g->tab, g->phase + o->hA * 4, 0);
    for (i = 0; i < 8; i++) {
        if (prev != NULL) {
            func_00106CF0(&g->q[0], a + prev->h4A, prev->h50, g->tab);
            func_00106CF0(&g->q[1], a + prev->h4A + 35, prev->h50, g->tab);
            o->h2 = prev->hA;
        } else {
            func_00106CF0(&g->q[0], a + o->h4A, o->h4E, g->tab);
            func_00106CF0(&g->q[1], a + o->h4A + 35, o->h4E, g->tab);
        }
        func_00106CF0(&g->q[2], a + o->h4A, o->h50, g->tab);
        func_00106CF0(&g->q[3], a + o->h4A + 35, o->h50, g->tab);
        if (prev == NULL) {
            func_00107790(p, o->c44, 1);
        } else {
            func_00107790(p, prev->c40, 1);
        }
        func_00107790(p, o->c40, 2);
        func_00108FF0(g->q, p, 0, g->ot);
        a = (s16)(a + 45);
    }
    }
}

/* several callees are called with other argument lists than functions.h gives: hide those prototypes */

/* OVL_WARM */

/* shape c059:01E02C10, 113 insns: draw a camera-facing quad (40x40 units) at the object, or its screen-space
   version in mode 0, then the two halves through the module's own drawer */

typedef struct Mat_c059_01E02C10 {
    f32 m[4][4];
} Mat_c059_01E02C10;

typedef struct Obj_c059_01E02C10 {
    u8 pad0[0x10];
    Vec4f pos;
    u8 pad20[0x23];
    u8 a43;
    u8 pad44[3];
    u8 a47;
} Obj_c059_01E02C10;

typedef struct Scn_c059_01E02C10 {
    u8 pad0[0x80];
    Mat_c059_01E02C10 mat;
    u8 padC0[0x190];
    Vec4f q[4];
    u8 pad290[0x23A4];
    void *tex;
    u8 pad2638[0x494];
    s32 ot;
    u8 pad2AD0[0x50];
    f32 z;
    u8 pad2B24[0x204];
    u8 col[4];
} Scn_c059_01E02C10;

static void func_01E02C10_c059(Scn_c059_01E02C10 *w, Obj_c059_01E02C10 *o, void *pk, s32 mode) {
    extern void func_00106080();
    extern void func_00108EF0();
    extern void func_00205C40();
    extern s32 func_00205630();
    extern void c059_01E02DE0(Scn_c059_01E02C10 *w, Obj_c059_01E02C10 *o, void *pk, s32 half);
    s16 i;
    f32 m[4];
    s32 rot[4];
    Mat_c059_01E02C10 m2;

    if (mode == 0) {
        func_00106080(m, 0x6E, 1, m);
        w->col[3] = o->a47;
        func_00107790(pk, w->col, 1);
        w->col[3] = o->a43;
        func_00107790(pk, w->col, 2);
        func_00108500(pk, m, 0);
        func_00208700(pk, w->tex, 0);
        return;
    }
    func_00205C40(rot);
    func_00108EF0(&m2, 0, rot, &o->pos);
    w->mat = m2;
    w->q[0].x = -20.0f;
    w->q[0].y = 40.0f;
    w->q[1].x = 20.0f;
    w->q[1].y = 40.0f;
    w->q[2].x = -20.0f;
    w->q[2].y = 0.0f;
    w->q[3].x = 20.0f;
    w->q[3].y = 0.0f;
    w->q[0].z = 0.0f;
    w->q[2].z = 0.0f;
    w->q[3].z = 0.0f;
    w->q[1].z = 0.0f;
    if (func_00205630(w->q, 0x70000000, &w->mat, pk, &w->z) != 0) {
        for (i = 0; i < 4; i++) {
            func_002075F0((s32)pk, w->ot, (u32)w->z);
        }
    }
    c059_01E02DE0(w, o, pk, 0);
    c059_01E02DE0(w, o, pk, 1);
}

/* shape c059:01E02DE0, 85 insns: draws an effect: mode 0 sets the packet's two colours from the scene colour with the effect's
   alphas and the scene texture; other modes lay the scene's quad (-20..20 by 30..120) and draw it three times with random
   frames 0..5 of texture page 0x82 */

typedef struct {
    u8 pad0[0x40];
    u8 c40[4];
    u8 c44[4];
} Fx_c059_01E02DE0;

typedef struct {
    u8 pad0[0x80];
    f32 m[16];
    u8 padC0[0x190];
    Vec4f quad[4];
    u8 pad290[0x263C - 0x290];
    void *tex;
    u8 pad2640[0x48C];
    s32 ot;
    u8 pad2AD0[0x25C];
    u8 col[4];
} Ctx_c059_01E02DE0;

static void func_01E02DE0_c059(Ctx_c059_01E02DE0 *c, Fx_c059_01E02DE0 *o, void *p, s32 mode) {
    extern void func_00107790(void *, void *, s32);
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00108FF0(void *, void *, void *, s32);
    s16 rect[8];
    s16 i;

    func_0019A5C8();
    if (mode == 0) {
        c->col[3] = o->c44[3];
        func_00107790(p, c->col, 1);
        c->col[3] = o->c40[3];
        func_00107790(p, c->col, 2);
        func_00208700(p, c->tex, 1);
    } else {
        c->quad[0].x = -20.0f;
        c->quad[0].y = 120.0f;
        c->quad[1].x = 20.0f;
        c->quad[1].y = 120.0f;
        c->quad[2].x = -20.0f;
        c->quad[2].y = 30.0f;
        c->quad[3].x = 20.0f;
        c->quad[3].y = 30.0f;
        c->quad[0].z = 0.0f;
        c->quad[2].z = 0.0f;
        c->quad[3].z = 0.0f;
        c->quad[1].z = 0.0f;
        for (i = 0; i < 3; i++) {
            func_00106080(rect, 0x82, func_0019A5C8() % 6, rect);
            func_00108500(p, rect, 0);
            func_00108FF0(c->quad, p, c->m, c->ot);
        }
    }
}

/* shape c059:01E02F40, 158 insns: draw one link of c059's trail: mode 0 sets the material (frame 0x97, scene texture
   0x2644); other modes build the link's quad from the previous link's ring (or its own inner ring when it is the first)
   and its own outer ring, colour it with the link's colour (alpha from the previous link at the near edge), and draw it
   three times turned by the scene's three angles (g+0x2D14, in 1/182 degree) */

typedef struct {
    u8 r, g, b, a;
} Col_c059_01E02F40;

typedef struct Ent_c059_01E02F40 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[0x14];
    Vec4f v20;
    struct Ent_c059_01E02F40 *prev;
    u8 pad34[0xC];
    u8 c40[4];
    Col_c059_01E02F40 col;
    u8 pad48[2];
    s16 ang;
    u8 pad4C[2];
    s16 r0;
    s16 r1;
} Ent_c059_01E02F40;

typedef struct {
    u8 pad0[0x80];
    u8 m[0x40];
    u8 padC0[0x180];
    Vec4f sc;
    Vec4f quad[4];
    u8 pad290[0x23B4];
    s32 tex;
    u8 pad2648[0x484];
    s32 ot;
    u8 pad2AD0[0x60];
    f32 scale;
    u8 pad2B34[0x1E0];
    s16 angs[3];
} Scene_c059_01E02F40;

static void func_01E02F40_c059(Scene_c059_01E02F40 *g, Ent_c059_01E02F40 *e, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern s32 func_00106CF0(void *, s32, s32, f32 *);
    extern void func_00107790(void *, void *, s32);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern void func_00108FF0(void *, void *, void *, s32);
    Ent_c059_01E02F40 *q = e->prev;
    f32 rm[4];
    s32 rot[4];
    f32 m[16];
    Col_c059_01E02F40 c;
    s32 i;

    if (mode == 0) {
        func_00106080(rm, 0x97, 0, rm);
        func_00108500(p, rm, 1);
        func_00208700(p, g->tex, 0);
        return;
    }
    if (q != 0) {
        func_00106CF0(&g->quad[0], q->ang, q->r1, &g->scale);
        func_00106CF0(&g->quad[1], (s16)(q->ang + 15), q->r1, &g->scale);
        g->quad[1].y = g->quad[0].y = q->hA;
        func_00107DD0(&g->quad[0], &q->v20, &e->v20, 0);
    } else {
        func_00106CF0(&g->quad[0], e->ang, e->r0, &g->scale);
        func_00106CF0(&g->quad[1], (s16)(e->ang + 15), e->r0, &g->scale);
        g->quad[1].y = g->quad[0].y = e->h2;
    }
    func_00106CF0(&g->quad[2], e->ang, e->r1, &g->scale);
    func_00106CF0(&g->quad[3], (s16)(e->ang + 15), e->r1, &g->scale);
    g->quad[2].y = g->quad[3].y = e->hA;
    func_00106FA0(&g->quad[0], &e->v20, 0);
    c = e->col;
    if (q == 0) {
        c.a = e->col.a;
    } else {
        c.a = q->c40[3];
    }
    func_00107790(p, &c, 1);
    c.a = e->c40[3];
    func_00107790(p, &c, 2);
    rot[2] = rot[0] = rot[1] = 0;
    for (i = 0; i < 3; i++) {
        func_0020EB40(g->m);
        func_0020C940(m, &g->sc, rot, 0);
        func_0020BC00(g->m, m);
        func_00108FF0(&g->quad[0], p, g->m, g->ot);
        rot[1] = g->angs[i] * 182;
    }
}

/* shape c059:01E031C0 (C059PAINT_RAIN6), 272 insns, 1 copy: draw one link of c059's rain column: mode 0 sets the
   material (frame 0x9C, colour 0x40, scene texture 0x2644); other modes build the link's quad from the previous
   link's ring (or its own inner ring) and its own outer ring off the scene's ring tables, lift both edges on a
   150-high sine of their heights (less 110), colour the near edge, and draw it 12 times turned 0x1554 apart (a second
   1.8-tall copy while the link is under 100, the 1.8f through a block local) */

typedef struct {
    f32 m[16];
} Mat_c059_01E031C0;

typedef struct Ent_c059_01E031C0 {
    u8 pad0[2];
    s16 h2;
    u8 pad4[6];
    s16 hA;
    u8 padC[0x14];
    Vec4f v20;
    struct Ent_c059_01E031C0 *prev;
    u8 pad34[0xC];
    u8 c40[4];
    u8 c44[4];
    u8 pad48[6];
    s16 r0;
    s16 r1;
} Ent_c059_01E031C0;

typedef struct {
    u8 pad0[0x80];
    Mat_c059_01E031C0 m;
    u8 padC0[0x180];
    Vec4f sc;
    Vec4f quad[4];
    u8 pad290[0x23B4];
    s32 tex;
    u8 pad2648[0x484];
    s32 ot;
    u8 pad2AD0[0x50];
    f32 dep;
    u8 pad2B24[0xC];
    u8 table[0x228];
    f32 t0[20];
    f32 t1[20];
    f32 t2[20];
    f32 t3[20];
} Scene_c059_01E031C0;

static void func_01E031C0_c059(Scene_c059_01E031C0 *g, Ent_c059_01E031C0 *e, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00107DD0(void *, void *, void *, s32);
    extern void func_00106FA0(void *, void *, s32);
    extern f32 func_00108030();
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108FF0(void *, void *, void *, s32);
    Ent_c059_01E031C0 *q = e->prev;
    f32 rm[4];
    s32 rot[4];
    Vec4f sv;
    Mat_c059_01E031C0 m;
    Mat_c059_01E031C0 m2;
    s16 a;
    s32 i;
    s32 r;

    a = 0;
    if (mode == 0) {
        func_00106080(rm, 0x9C, 0, rm);
        func_00107790(p, e->c40, 2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 0);
        return;
    }
    for (i = 0; i < 1; i++) {
        if (q != 0) {
            g->quad[0].x = g->t1[i] * q->r1;
            g->quad[0].z = g->t0[i] * q->r1;
            g->quad[1].x = g->t3[i] * q->r1;
            g->quad[1].z = g->t2[i] * q->r1;
            g->quad[0].y = g->quad[1].y = e->h2 = q->hA;
            func_00107DD0(&g->quad[0], &q->v20, &e->v20, 0);
        } else {
            g->quad[0].x = g->t1[i] * e->r0;
            g->quad[0].z = g->t0[i] * e->r0;
            g->quad[1].x = g->t3[i] * e->r0;
            g->quad[1].z = g->t2[i] * e->r0;
        }
        g->quad[2].x = g->t1[i] * e->r1;
        g->quad[2].z = g->t0[i] * e->r1;
        g->quad[3].x = g->t3[i] * e->r1;
        g->quad[3].z = g->t2[i] * e->r1;
        g->quad[2].y = g->quad[3].y = e->hA;
        func_00106FA0(&g->quad[0], &e->v20, 0);
        g->quad[1].y = g->quad[0].y = 30.0f + 150.0f * func_00108030(g->table, (s16)(e->h2 - 110), 1);
        g->quad[3].y = g->quad[2].y = 30.0f + 150.0f * func_00108030(g->table, e->hA - 110, 1);
        if (q == 0) {
            func_00107790(p, e->c44, 1);
        } else {
            func_00107790(p, q->c40, 1);
        }
    }
    rot[2] = rot[0] = rot[1] = 0;
    for (i = 0, r = 0; i < 12; i++) {
        func_0020EB40(&g->m);
        func_0020C940(&m, &g->sc, rot, 0);
        func_0020BC00(&g->m, &m);
        if (func_00205630(&g->quad[0], 0x70000000, &g->m, p, &g->dep) != 0) {
            func_002075F0(p, g->ot, (u32)g->dep);
        }
        if (e->h2 < 100) {
            {
                f32 k = 1.8f;
                func_00106DD0(&sv, 1.0f, k, 1.0f);
            }
            func_00108EF0(&m2, &sv, rot, 0);
            g->m = m2;
            func_00108FF0(&g->quad[0], p, &g->m, g->ot);
        }
        r += 0x1554;
        rot[1] = r;
        a += 30;
    }
}


/* shape b073:01E03BC0, 2 insns, 5 copies: an empty callback */

static void func_01E03600_c059(void) {
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03610_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03B00_c059);

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E03D70_c059);

/* OVL_WARM */

/* shape c059:01E040B0, 217 insns: two-pass ring of five quads: mode 0 sets the material (frame 0x96, colours 0x34 /
   0x38 on the inner / outer corners, scene texture 0x2644); otherwise the inner and outer radii are 65 x the table
   sine of the node's angle (0x2) and of that angle - 5, the inner corners sit at height angle - 90 and the outer ones
   12 below; each 72-degree segment is drawn under the first four of the scene's matrices for three of its joints
   (g+0x1310, 0x40 apart, 0x140 per joint) into the scene order table 0x2ACC */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c059_01E040B0;

typedef struct {
    Rgbaq_c059_01E040B0 c;
    u64 st;
    u64 xyz;
} Vtx_c059_01E040B0;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Vtx_c059_01E040B0 v[4];
} Pkt_c059_01E040B0;

typedef struct {
    u8 pad0[2];
    s16 ang;
    u8 pad4[0x30];
    u8 col[4];
    u8 col2[4];
} Node_c059_01E040B0;

typedef struct {
    u8 pad0[0x250];
    Vec4f quad[4];
    u8 pad290[0x1310 - 0x290];
    f32 mats[3][5][16];
    u8 pad16D0[0x2644 - 0x16D0];
    s32 tex;
    u8 pad2648[0x2ACC - 0x2648];
    s32 ot;
    u8 pad2AD0[0x60];
    u8 table[1];
} Scene_c059_01E040B0;

static void func_01E040B0_c059(Scene_c059_01E040B0 *g, Node_c059_01E040B0 *o, Pkt_c059_01E040B0 *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern Rgbaq_c059_01E040B0 func_00107740(void *);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_00108FF0(void *, void *, void *, s32);
    f32 rm[4];
    s16 r0;
    s16 r1;
    s16 k;
    s16 i;
    s16 j;
    f32 c1;
    f32 c0;
    f32 s0;
    f32 s1;

    if (mode == 0) {
        func_00106080(rm, 0x96, 0, rm);
        func_00109270(p, 0, 0);
        p->v[0].c = func_00107740(o->col);
        p->v[1].c = func_00107740(o->col);
        p->v[2].c = func_00107740(o->col2);
        p->v[3].c = func_00107740(o->col2);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
    } else {
        r0 = 65.0f * func_00108030(g->table, o->ang, 0);
        r1 = (s16)(65.0f * func_00108030(g->table, o->ang - 5, 0));
        g->quad[0].y = o->ang - 90;
        g->quad[1].y = o->ang - 90;
        g->quad[3].y = g->quad[2].y = g->quad[0].y - 12.0f;
        for (k = 0; k < 5; k++) {
            c0 = func_00108030(g->table, k * 72, 1);
            s0 = func_00108030(g->table, k * 72, 0);
            c1 = func_00108030(g->table, k * 72 + 72, 1);
            s1 = func_00108030(g->table, k * 72 + 72, 0);
            g->quad[0].x = c0 * r0;
            g->quad[0].z = s0 * r0;
            g->quad[1].x = c1 * r0;
            g->quad[1].z = s1 * r0;
            g->quad[2].x = c0 * r1;
            g->quad[2].z = s0 * r1;
            g->quad[3].x = c1 * r1;
            g->quad[3].z = s1 * r1;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 3; j++) {
                    func_00108FF0(g->quad, p, g->mats[j][i], g->ot);
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E04420_c059);

/* shape c059:01E053B0, 35 insns: raises two alphas by 16 up to 0x80 while the scene value is under 10, lowers them by 16 down to 16 while the other one is */

typedef struct {
    u8 pad0[0x2A50];
    s32 w2A50;
    u8 pad2A54[0x4E];
    s16 h2AA2;
} Ctx_c059_01E053B0;

typedef struct {
    u8 pad0[0x43];
    u8 a43;
    u8 pad44[3];
    u8 a47;
} Obj_c059_01E053B0;

static s32 func_01E053B0_c059(Ctx_c059_01E053B0 *ctx, Obj_c059_01E053B0 *o) {
    if (ctx->h2AA2 < 10) {
        if (o->a47 < 0x80) {
            o->a47 += 0x10;
        }
        if (o->a43 < 0x80) {
            o->a43 += 0x10;
        }
    }
    if (ctx->w2A50 < 10) {
        if (o->a47 > 0x10) {
            o->a47 -= 0x10;
        }
        if (o->a43 > 0x10) {
            o->a43 -= 0x10;
        }
    }
    return 0;
}

/* shape c059:01E05440, 178 insns: a falling column segment: its angle turns back by 4 (wrapped past -359), it remembers
   its old bottom/top, the bottom drops by 4 to the floor while the top follows within 20, then the top closes down
   and ends the segment (clearing the linked node's flag); once the top passes below the scene limit (0x2CC8) - 10 it
   hands the scene one more segment (0x1E05440 with the 0x1E029A0 draw) at its place, angle + 15; both colours stay
   dark red 0x40 with alphas rising by 13 to 0x30 for 8 frames, fading by 16 near the end or when low, else rising
   by 13 to 0x80 */

typedef struct {
    u8 pad0[0x30];
    s32 w30;
} Link_c059_01E05440;

typedef struct Seg_c059_01E05440 {
    u8 pad0[2];
    s16 y;
    u8 pad4[6];
    s16 top;
    u8 padC[0x28];
    Link_c059_01E05440 *link;
    u8 pad38[8];
    u8 col[4];
    u8 col2[4];
    s16 h48;
    s16 ang;
    u8 pad4C[2];
    s16 h4E;
    s16 h50;
    s16 h52;
} Seg_c059_01E05440;

typedef struct {
    u8 pad0[0x2A20];
    Vec4f pos;
    u8 pad2A30[0x10];
    f32 px, py, pz;
    u8 pad2A4C[4];
    s32 timer;
    u8 col[4];
    u8 pad2A58[4];
    Seg_c059_01E05440 *parent;
    u8 pad2A60[0x30];
    s16 ang;
    u8 pad2A92[4];
    s16 h2A96;
    u8 pad2A98[4];
    s16 h2A9C;
    u8 pad2A9E[4];
    s16 frame;
    u8 pad2AA4[0x224];
    s16 limit;
} Scene_c059_01E05440;

static s32 func_01E05440_c059(Scene_c059_01E05440 *g, Seg_c059_01E05440 *o) {
    extern void c059_01E01CE0(Scene_c059_01E05440 *, void *, void *, s32);
    extern void c059_01E029A0(void);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);

    o->ang -= 4;
    if (o->ang < -359) {
        o->ang %= 360;
    }
    o->h4E = o->y;
    o->h50 = o->top;
    if (o->y > 0) {
        o->y -= 4;
        if (o->top - o->y >= 20) {
            o->top -= 4;
        }
    } else {
        o->top -= 4;
        if (o->top < o->y) {
            o->top = o->y;
            if (o->link != NULL) {
                o->link->w30 = 0;
            }
            o->h48 = 0;
        }
    }
    if (o->top < g->limit - 10) {
        if (o->h52 > 0) {
            g->parent = o;
            g->px = o->h4E;
            g->py = o->h50;
            g->col[3] = 0;
            func_001076F0(g->col, 0x50, 0x50, 0x50);
            g->h2A96 = 1;
            g->pz = o->top;
            g->h2A9C = 1;
            func_00106DD0(&g->pos, 0.0f, 0.0f, 0.0f);
            g->ang = o->ang + 15;
            c059_01E01CE0(g, func_01E05440_c059, c059_01E029A0, 0);
            o->h52 = 0;
        }
    }
    func_001076F0(o->col2, 0x40, 0, 0);
    func_001076F0(o->col, 0x40, 0, 0);
    if (g->frame < 8) {
        if (o->col2[3] < 0x30) {
            o->col2[3] += 13;
        }
        if (o->col[3] < 0x30) {
            o->col[3] += 13;
        }
    } else if (g->timer < 10) {
        if (o->col2[3] > 16) {
            o->col2[3] -= 16;
        }
        if (o->col[3] > 16) {
            o->col[3] -= 16;
        }
    } else if (o->h4E < 15) {
        if (o->col2[3] > 16) {
            o->col2[3] -= 16;
        }
        if (o->col[3] > 16) {
            o->col[3] -= 16;
        }
    } else {
        if (o->col2[3] < 0x80) {
            o->col2[3] += 13;
        }
        if (o->col[3] < 0x80) {
            o->col[3] += 13;
        }
    }
    return 0;
}

/* OVL_WARM */

/* shape c059:01E05710, 213 insns: c026:01E00BF0's falling pair in whole units: turns -5 a tick; its spots (0x4E/0x50)
   are 1.3 times the top and bottom (0x2/0xA, at least 10, done in double); the top drops 5 a tick to 0, the bottom
   follows within 16 and then alone until it reaches the top (frees its link, stops). Once 0x52 is set and the
   bottom is above ctx+0x2CD0 it hands itself to the scene (ctx+0x2A5C.., grey 0x70) and, from scene stage 3 on,
   starts the module's c059:01E02F40 through c059:01E01EE0. Alpha by scene stage */

typedef struct Link_c059_01E05710 {
    u8 pad0[0x30];
    s32 f30;
} Link_c059_01E05710;

typedef struct Obj_c059_01E05710 {
    u8 pad0[2];
    s16 top;
    u8 pad4[6];
    s16 bot;
    u8 padC[0x28];
    Link_c059_01E05710 *link;
    u8 pad38[8];
    u8 col0[4];
    u8 col1[4];
    s16 h48;
    s16 ang;
    u8 pad4C[2];
    s16 h4E;
    s16 h50;
    s16 h52;
} Obj_c059_01E05710;

typedef struct Scn_c059_01E05710 {
    u8 pad0[0x2A20];
    s32 f2A20;
    s32 f2A24;
    s32 f2A28;
    u8 pad2A2C[0x14];
    f32 f2A40;
    f32 f2A44;
    f32 f2A48;
    u8 pad2A4C[4];
    s32 stage;
    u8 col[4];
    u8 pad2A58[4];
    Obj_c059_01E05710 *cur;
    u8 pad2A60[0x30];
    s16 f2A90;
    u8 pad2A92[4];
    s16 f2A96;
    u8 pad2A98[4];
    s16 f2A9C;
    u8 pad2A9E[4];
    s16 f2AA2;
    u8 pad2AA4[0x2CD0 - 0x2AA4];
    s16 f2CD0;
} Scn_c059_01E05710;

static s32 func_01E05710_c059(Scn_c059_01E05710 *g, Obj_c059_01E05710 *o) {
    extern void c059_01E01EE0(Scn_c059_01E05710 *g, void *fn, void *fn2, s32 arg);
    extern s32 c059_01E02F40();
    extern void func_001076F0(void *, s32, s32, s32);

    o->ang -= 5;
    if (o->ang <= -360) {
        o->ang = o->ang % 360;
    }
    o->h4E = 1.3 * o->top;
    o->h50 = 1.3 * o->bot;
    if (o->h4E < 10) {
        o->h4E = 10;
    }
    if (o->h50 < 10) {
        o->h50 = 10;
    }
    if (o->top > 0) {
        o->top -= 5;
        if (o->bot - o->top >= 16) {
            o->bot -= 5;
        }
    } else {
        o->bot -= 5;
        if (o->bot < o->top) {
            o->bot = o->top;
            if (o->link != NULL) {
                o->link->f30 = 0;
            }
            o->h48 = 0;
        }
    }
    if (o->bot < g->f2CD0 && o->h52 > 0) {
        g->cur = o;
        g->f2A40 = o->h4E;
        g->f2A44 = o->h50;
        g->col[3] = 0;
        func_001076F0(g->col, 0x70, 0x70, 0x70);
        g->f2A96 = 1;
        g->f2A48 = o->bot;
        g->f2A9C = 1;
        g->f2A24 = 0;
        g->f2A20 = 0;
        g->f2A28 = 0;
        g->f2A90 = o->ang + 10;
        if (g->stage > 2) {
            c059_01E01EE0(g, func_01E05710_c059, c059_01E02F40, 0);
        }
        o->h52 = 0;
    }
    if (g->f2AA2 < 8) {
        if (o->col1[3] < 0x40) {
            o->col1[3] += 12;
        }
        if (o->col0[3] < 0x40) {
            o->col0[3] += 12;
        }
    } else if (o->bot < 35) {
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 10;
        }
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 10;
        }
    } else if (g->stage < 10) {
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 10;
        }
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 10;
        }
    } else {
        if (o->col1[3] < 0x80) {
            o->col1[3] += 12;
        }
        if (o->link != NULL) {
            if (o->col0[3] < 0x80) {
                o->col0[3] += 12;
            }
        }
    }
    if (g->stage == 2) {
        o->h48 = 0;
    }
    return 0;
}

/* OVL_WARM */

/* shape c059:01E05A70, 244 insns: c059:01E05710 cousin: turns -4 a tick; while the scene stage (0x2AA2) is past 7 its
   spots (0x4E/0x50) shrink by 5 toward 10 i + 5 / 11 i + 5 for the first level i (ctx+0x2AD0) above its top; the top
   drops 5 a tick to 0, the bottom follows within 28 and then alone until it reaches the top (frees its link, stops);
   low spots fade; once 0x52 is set and the bottom is above ctx+0x2CD8 it hands itself to the scene (grey 0x50, alpha
   10, size 155) and from scene stage 17 on restarts itself through c059:01E020E0. Alpha by scene stage and height */

typedef struct Link_c059_01E05A70 {
    u8 pad0[0x30];
    s32 f30;
} Link_c059_01E05A70;

typedef struct Obj_c059_01E05A70 {
    u8 pad0[2];
    s16 top;
    u8 pad4[6];
    s16 bot;
    u8 padC[0x24];
    s32 f30;
    Link_c059_01E05A70 *link;
    u8 pad38[8];
    u8 col0[4];
    u8 col1[4];
    s16 h48;
    s16 ang;
    u8 pad4C[2];
    s16 h4E;
    s16 h50;
    s16 h52;
} Obj_c059_01E05A70;

typedef struct Scn_c059_01E05A70 {
    u8 pad0[0x2A20];
    s32 f2A20;
    s32 f2A24;
    s32 f2A28;
    u8 pad2A2C[0x14];
    f32 f2A40;
    f32 f2A44;
    f32 f2A48;
    u8 pad2A4C[4];
    s32 stage;
    u8 col[4];
    u8 pad2A58[4];
    Obj_c059_01E05A70 *cur;
    u8 pad2A60[0x30];
    s16 f2A90;
    u8 pad2A92[4];
    s16 f2A96;
    u8 pad2A98[4];
    s16 f2A9C;
    u8 pad2A9E[4];
    s16 f2AA2;
    u8 pad2AA4[0x2AD0 - 0x2AA4];
    f32 lv[8];
    u8 pad2AF0[0x2CD8 - 0x2AF0];
    s16 f2CD8;
} Scn_c059_01E05A70;

static s32 func_01E05A70_c059(Scn_c059_01E05A70 *g, Obj_c059_01E05A70 *o) {
    extern void c059_01E020E0(Scn_c059_01E05A70 *g, void *fn, void *fn2, s32 arg);
    extern void func_001076F0(void *, s32, s32, s32);
    s32 i;

    o->ang -= 4;
    if (o->ang <= 360) {
        o->ang = o->ang % 360;
    }
    for (i = 1; i < 8; i++) {
        if (g->lv[i] > o->top) {
            if (g->f2AA2 > 7) {
                if (o->h4E >= i * 10 + 5) {
                    o->h4E -= 5;
                }
                if (o->h50 >= i * 11 + 5) {
                    o->h50 -= 5;
                }
            }
            i = 8;
        }
    }
    if (o->top > 0) {
        o->top -= 5;
        if (o->bot - o->top >= 28) {
            o->bot -= 5;
        }
    } else {
        o->bot -= 5;
        if (o->bot < o->top) {
            o->bot = o->top;
            if (o->link != NULL) {
                o->link->f30 = 0;
            }
            o->h48 = 0;
        }
    }
    if (o->h50 < 20) {
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 0x10;
        }
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 0x10;
        }
    }
    if (o->bot < g->f2CD8 && o->h52 > 0) {
        g->cur = o;
        g->f2A40 = g->f2A44 = 155.0f;
        func_001076F0(g->col, 0x50, 0x50, 0x50);
        g->col[3] = 10;
        g->f2A96 = 1;
        g->f2A48 = o->bot;
        g->f2A9C = 1;
        g->f2A24 = 0;
        g->f2A20 = 0;
        g->f2A28 = 0;
        g->f2A90 = o->ang;
        if (g->stage > 16) {
            c059_01E020E0(g, func_01E05A70_c059, 0, 0);
        }
        o->h52 = 0;
    }
    if (g->f2AA2 < 8) {
        if (o->bot > 120) {
            if (o->f30 != 0) {
                if (o->col1[3] < 0x60) {
                    o->col1[3] += 6;
                }
            }
            if (o->col0[3] < 0x60) {
                o->col0[3] += 6;
            }
        } else {
            if (o->f30 != 0) {
                if (o->col1[3] < 0x60) {
                    o->col1[3] += 15;
                }
            }
            if (o->col0[3] < 0x60) {
                o->col0[3] += 15;
            }
        }
    } else if (g->stage < 10) {
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 0x10;
        }
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 0x10;
        }
    } else if (o->bot > 80) {
        if (o->f30 != 0) {
            if (o->col1[3] < 0x60) {
                o->col1[3] += 5;
            }
        }
        if (o->col0[3] < 0x60) {
            o->col0[3] += 5;
        }
    } else {
        if (o->col1[3] > 0x10) {
            o->col1[3] -= 5;
        }
        if (o->col0[3] > 0x10) {
            o->col0[3] -= 5;
        }
    }
    return 0;
}

/* shape c059:01E05E40, 83 insns: a blue glow following a scene point plus its offset (or the scene's own point once the timer
   passes 0x87 with the flag set); fades in by 16 to 0xB0 while the state is at least 11, else out by 15; grows by 4 to 60,
   turns 2048 */

typedef struct {
    Vec4f p;
    Vec4f off;
    u8 pad20[0x50];
} Pt_c059_01E05E40;

typedef struct {
    u8 pad0[0x2650];
    Pt_c059_01E05E40 pts[6];
    f32 x, y, z;
    u8 pad28FC[0x154];
    s32 state;
    u8 pad2A54[0x4E];
    s16 timer;
    u8 pad2AA4[0x24];
    s32 flag;
} Ctx_c059_01E05E40;

typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    u8 pad1C[8];
    f32 ang;
    u8 pad28[0x18];
    u8 c40[4];
    u8 c44[4];
    s16 live;
    u8 pad4A[2];
    s16 size;
    u8 pad4E[8];
    s16 idx;
} Fx_c059_01E05E40;

static s32 func_01E05E40_c059(Ctx_c059_01E05E40 *c, Fx_c059_01E05E40 *o) {
    o->x = c->pts[o->idx].p.x + c->pts[o->idx].off.x;
    o->y = c->pts[o->idx].p.y + c->pts[o->idx].off.y;
    o->z = c->pts[o->idx].p.z + c->pts[o->idx].off.z;
    if (c->timer > 0x87) {
        if (c->flag != 0) {
            o->x = c->x;
            o->y = c->y;
            o->z = c->z;
        }
    }
    o->c44[3] = 0;
    o->c44[0] = 0x50;
    o->c44[1] = 0x50;
    o->c44[2] = 0xFF;
    if (c->state > 0xA) {
        if (o->c40[3] < 0xB0) {
            o->c40[3] += 0x10;
        }
    } else if (o->c40[3] > 0x10) {
        o->c40[3] -= 0xF;
    } else {
        o->live = 0;
    }
    o->c40[0] = 0xB0;
    o->c40[1] = 0xB0;
    o->c40[2] = 0xBF;
    if (o->size < 0x3C) {
        o->size += 4;
    }
    o->ang += 2048.0f;
    return 0;
}

/* shape c059:01E05F90, 187 insns: a yellow (0x80, 0x80, 0) glow's step by its stage (0x2C): 0 fades both alphas by 16 and frees it (clearing its owner's 0x30); 1 hands it to the scene (colour 0x30/0x30/0 or 0x30/0x10/0 by callback c059:01E03610, owner 0x2A5C, centre cleared, slot 0x2A9C) and spawns c059:01E02310 with that callback (else c059:01E03D70) while 0xA is under its row limit, else clears the row; other stages grow 0xA by 8 to the limit and count down; jitters 0xE -20..19; fades out under scene time 10, else pins alphas to 0xB0 while staged */

typedef struct {
    s16 used;
    s16 lim;
    u8 pad4[0x30];
} Row_c059_01E05F90;

typedef struct {
    u8 pad0[0x2A20];
    u8 c2A20[0x30];
    s32 time;
    u8 col[4];
    u8 pad2A58[4];
    void *owner;
    u8 pad2A60[0x36];
    s16 h2A96;
    u8 pad2A98[4];
    s16 slot;
    u8 pad2A9E[0x2EBA - 0x2A9E];
    Row_c059_01E05F90 rows[1];
} Scene_c059_01E05F90;

typedef struct {
    u8 pad0[0x30];
    s32 w30;
} Own_c059_01E05F90;

typedef struct {
    u8 pad0[0xA];
    s16 hA;
    u8 padC[2];
    s16 hE;
    u8 pad10[4];
    Own_c059_01E05F90 *own;
    void *fn;
    u8 pad1C[4];
    u8 c20[4];
    u8 c24[4];
    s16 h28;
    s16 h2A;
    s16 stage;
    s16 row;
} Fx_c059_01E05F90;

static s32 func_01E05F90_c059(Scene_c059_01E05F90 *g, Fx_c059_01E05F90 *o) {
    extern void c059_01E02310(Scene_c059_01E05F90 *, void *, void *, s32);
    extern s32 c059_01E03610(void);
    extern s32 c059_01E03D70(void);
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106DD0(void *, f32, f32, f32);
    f32 x;
    f32 y;
    f32 z;

    if (o->stage > 1) {
        if (o->hA < g->rows[o->row].lim) {
            o->hA += 8;
        }
        o->stage--;
    } else if (o->stage == 1) {
        if (o->hA < g->rows[o->row].lim) {
            g->h2A96 = 0;
            g->col[3] = 0;
            if (o->fn == c059_01E03610) {
                func_001076F0(g->col, 0x30, 0x30, 0);
            } else {
                func_001076F0(g->col, 0x30, 0x10, 0);
            }
            g->owner = o;
            x = y = z = 0.0f;
            func_00106DD0(g->c2A20, x, y, z);
            g->slot = o->row;
            if (o->fn == c059_01E03610) {
                c059_01E02310(g, func_01E05F90_c059, c059_01E03610, 0);
            } else {
                c059_01E02310(g, func_01E05F90_c059, c059_01E03D70, 0);
            }
        } else {
            g->rows[o->row].used = 0;
        }
        o->stage = 0;
    } else if (o->stage == 0) {
        if (o->c24[3] > 16) {
            o->c24[3] -= 16;
        }
        if (o->c20[3] > 19) {
            o->c20[3] -= 16;
        } else {
            if (o->own != NULL) {
                o->own->w30 = 0;
            }
            o->h28 = 0;
        }
    }
    o->hE = func_0019A5C8() % 40 - 20;
    if (o->h2A == 0) {
        o->c24[0] = 0x80;
        o->c24[1] = 0x80;
        o->c24[2] = 0;
        o->c20[0] = 0x80;
        o->c20[1] = 0x80;
        o->c20[2] = 0;
        o->h2A = 1;
    } else {
        o->c24[0] = 0x80;
        o->c24[1] = 0x80;
        o->c24[2] = 0;
        o->c20[0] = 0x80;
        o->c20[1] = 0x80;
        o->c20[2] = 0;
        o->h2A = 0;
    }
    if (g->time < 10) {
        if (o->c24[3] > 16) {
            o->c24[3] -= 16;
        }
        if (o->c20[3] > 16) {
            o->c20[3] -= 16;
        } else {
            o->h28 = 0;
        }
    } else if (o->stage != 0) {
        if (o->c24[3] < 0xB0) {
            o->c24[3] = 0xB0;
        }
        if (o->c20[3] < 0xB0) {
            o->c20[3] = 0xB0;
        }
    }
    return 0;
}

/* shape c059:01E06280, 27 insns: second alpha 0; while the counter at 0x2A50 is below 10 fade by 0x15 and stop at
   the end, otherwise grow by 0x3C (below 0xF0); colour (0x20, 0, 0x40) */

typedef struct {
    u8 pad0[0x2A50];
    s32 count;
} Game_c059_01E06280;

typedef struct {
    u8 pad0[0x40];
    u8 col[4];
    u8 col2[4];
    s16 mode;
} Fx_c059_01E06280;

static s32 func_01E06280_c059(Game_c059_01E06280 *g, Fx_c059_01E06280 *o) {
    o->col2[3] = 0;
    if (g->count < 10) {
        if (o->col[3] > 0x20) {
            o->col[3] -= 0x15;
        } else {
            o->mode = 0;
        }
    } else {
        if (o->col[3] < 0xF0) {
            o->col[3] += 0x3C;
        }
    }
    o->col[0] = 0x20;
    o->col[1] = 0;
    o->col[2] = 0x40;
    return 0;
}

/* shape c059:01E062F0, 41 insns, 1 copy */

typedef struct Obj_c059_01E062F0 {
    u8 pad0[0x43];
    u8 c43;
    u8 pad44[3];
    u8 c47;
    s16 f48;
    u8 pad4A[0xC];
    s16 f56;
} Obj_c059_01E062F0;

static s32 func_01E062F0_c059(void *ctx, Obj_c059_01E062F0 *o) {
    if (o->f56 == 0) {
        if (o->c47 < 0xE0) {
            o->c47 += 0x30;
        }
        if (o->c43 < 0xE0) {
            o->c43 += 0x30;
        } else {
            o->f56 = 1;
        }
    } else if (o->f56 < 4) {
        o->f56++;
    } else {
        if (o->c47 > 0x13) {
            o->c47 -= 0x10;
        }
        if (o->c43 > 0x13) {
            o->c43 -= 0x10;
        } else {
            o->f48 = 0;
        }
    }
    return 0;
}

/* shape c059:01E063A0, 51 insns: a 10-tick counter (0x52); 0x4E swings by 2 between 0x14 and 0x3C (direction 0x56);
   while the game counter at 0x2A50 is below 10 the alpha fades by 0x10 and stops, otherwise grows by 9 below 0x80 */

typedef struct {
    u8 pad0[0x2A50];
    s32 count;
} Game_c059_01E063A0;

typedef struct {
    u8 pad0[0x40];
    u8 col[4];
    u8 pad44[4];
    s16 mode;
    u8 pad4A[4];
    s16 swing;
    u8 pad50[2];
    s16 f52;
    u8 pad54[2];
    s16 dir;
} Fx_c059_01E063A0;

static s32 func_01E063A0_c059(Game_c059_01E063A0 *g, Fx_c059_01E063A0 *o) {
    o->f52++;
    if (o->f52 >= 10) {
        o->f52 = 0;
    }
    if (o->dir == 0) {
        o->swing += 2;
        if (o->swing > 0x3C) {
            o->dir = 1;
        }
    } else {
        o->swing -= 2;
        if (o->swing < 0x14) {
            o->dir = 0;
        }
    }
    if (g->count < 10) {
        if (o->col[3] > 0x10) {
            o->col[3] -= 0x10;
        } else {
            o->mode = 0;
        }
    } else if (o->col[3] < 0x80) {
        o->col[3] += 9;
    }
    return 0;
}

/* shape c059:01E06470, 85 insns: a flying shard: moves by its s16 velocity and ends below ground; within 35 of the origin it
   shrinks by 0.35 on three axes and ends when the third runs out; flickers its colour every other frame */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[2];
    f32 sx, sy, sz;
    u8 pad1C[8];
    u8 c24[4];
    s16 live;
    u8 pad2A[2];
    s16 flip;
} Fx_c059_01E06470;

static s32 func_01E06470_c059(void *arg0, Fx_c059_01E06470 *o) {
    extern f32 func_001A6C60(f32);
    extern void func_00106BF0(void *, s32, s32, s32);
    extern void func_00106C50(void *, s32, s32, s32);
    s16 x;
    s16 y;
    s16 z;

    o->y += o->vy;
    if (o->y < 0) {
        o->live = 0;
    }
    o->x += o->vx;
    o->z += o->vz;
    x = o->x;
    z = o->z;
    y = o->y;
    if (!(35.0f <= func_001A6C60(x * x + z * z + y * y))) {
        o->sx -= 0.35f;
        o->sz -= 0.35f;
        o->sy -= 0.35f;
        if (o->sz < 0.0f) {
            o->live = 0;
        }
    }
    if (o->flip == 0) {
        func_00106BF0(o->c24, 0x30, 0, 1);
        o->flip = 1;
    } else {
        func_00106BF0(o->c24, 0x30, 0, 0);
        o->flip = 0;
    }
    func_00106C50(o->c24, 0x12, 0x80, 0);
    return 0;
}

/* shape c059:01E065D0, 84 insns: a purple rising glow: rises 9 a frame (its sub-frame stepped by the module timer); between
   heights 41 and 130 fades both alphas in by 19 to 0x80 while the scene state is at least 11 (else out by 15); above 130
   fades out and ends when the second runs out; ends at height 160 */

typedef struct {
    u8 pad0[0x2A50];
    s32 state;
} Ctx_c059_01E065D0;

typedef struct {
    u8 pad0[2];
    s16 y;
    u8 pad4[0x2A];
    s16 live;
    u8 pad30[2];
    s16 sub;
    u8 c34[4];
    u8 c38[4];
} Fx_c059_01E065D0;

static s32 func_01E065D0_c059(Ctx_c059_01E065D0 *c, Fx_c059_01E065D0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern void func_00106D80(s32, void *);

    o->y += 9;
    func_00106D80(5, &o->sub);
    if (o->y > 0x82) {
        if (o->c34[3] > 0x10) {
            o->c34[3] -= 0xF;
        }
        if (o->c38[3] > 0x10) {
            o->c38[3] -= 0xF;
        } else {
            o->live = 0;
        }
    } else if (o->y > 0x28) {
        if (c->state > 0xA) {
            if (o->c34[3] < 0x80) {
                o->c34[3] += 0x13;
            }
            if (o->c38[3] < 0x80) {
                o->c38[3] += 0x13;
            }
        } else {
            if (o->c34[3] > 0x10) {
                o->c34[3] -= 0xF;
            }
            if (o->c38[3] > 0x10) {
                o->c38[3] -= 0xF;
            }
        }
    }
    if (o->y >= 0xA0) {
        o->live = 0;
    }
    func_001076F0(o->c34, 0x80, 0x40, 0x80);
    func_001076F0(o->c38, 0x80, 0x40, 0x80);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/c059", func_01E06720_c059);

/* shape c059:01E06DC0, 88 insns: draws a scene effect (c017:01E02970 shape): mode 0 builds the gouraud packet (blend 0x48 for
   the c059:01E063A0 and c059:01E062F0 effects, else 0x42; colours swapped, q 0), other modes queue it */

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Rgbaq_c059_01E06DC0;

typedef struct {
    Rgbaq_c059_01E06DC0 c;
    u64 xyz;
} Vtx_c059_01E06DC0;

typedef struct {
    s16 tag;
    s16 count;
    s32 pad;
    u64 regs;
    Vtx_c059_01E06DC0 v[4];
} Pkt_c059_01E06DC0;

typedef struct {
    u8 pad0[0x3C];
    void *cb;
    u8 c40[4];
    u8 c44[4];
} Fx_c059_01E06DC0;

typedef struct {
    u8 pad0[0x2ACC];
    s32 target;
} Scene_c059_01E06DC0;

static void func_01E06DC0_c059(Scene_c059_01E06DC0 *g, Fx_c059_01E06DC0 *o, Pkt_c059_01E06DC0 *p, s32 mode) {
    extern void c059_01E062F0(void);
    extern void c059_01E063A0(void);
    extern Rgbaq_c059_01E06DC0 func_00107740(void *);
    extern void func_002075F0(void *, s32, s32);

    if (mode == 0) {
        p->count = 0x14;
        p->tag = 8;
        p->regs = 0x41414141;
        p->pad = 0;
        if (o->cb == (void *)c059_01E063A0 || o->cb == (void *)c059_01E062F0) {
            func_002086D0(p, ((u64)0x80 << 32) | 0x48);
        } else {
            func_002086D0(p, ((u64)0x80 << 32) | 0x42);
        }
        p->v[0].c = func_00107740(o->c44);
        p->v[1].c = func_00107740(o->c44);
        p->v[2].c = func_00107740(o->c40);
        p->v[3].c = func_00107740(o->c40);
        p->v[0].c.q = p->v[1].c.q = p->v[2].c.q = p->v[3].c.q = 0.0f;
        func_001094F0(p);
    } else {
        func_002075F0(p, g->target, 0);
    }
}
