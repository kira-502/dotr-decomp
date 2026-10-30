#include "common.h"

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

static void func_01E00080_b636(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

/* shape b045:01E00E30, 224 insns: b018:01E005A0 with n taken as is, rot[1] = -(rot[1] / 180) instead of the
   object's rotation (no rotation for the world matrix), and func_00109100(m, rot, 0, self + 0xD8) per sprite; draws n textured sprites along a curve read from a per-frame table (three s8
   angle tables 0x64 apart), each scaled by obj->size. Calls the module's sprite-UV helper (shape
   b008:01E00080), included above as a static function: the call keeps pk in $a0 across it. */

typedef struct {
    f32 s;
    f32 t;
} St_b045_01E00E30;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
    St_b045_01E00E30 st;
    u8 pad18[0xF];
    u8 q0;
    u8 pad28[0xF];
    u8 q1;
    u8 pad38[0xF];
    u8 q2;
    u8 pad48[0xF];
    u8 q3;
} Pk_b045_01E00E30;

typedef struct {
    s16 x, y, z;
    s16 pad6;
    s16 tab;
    s16 dy;
    s16 dz;
    s16 padE;
    s32 rx, ry, rz;
    u8 pad1C[0xC];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
} Obj_b045_01E00E30;

static void func_01E004D0_b636(u8 *self, Obj_b045_01E00E30 *obj, Pk_b045_01E00E30 *pk, s8 *base) {
    extern void func_00108EF0();
    extern void func_00109100();
    f32 m[16];
    Vec4f pos;
    Vec4f scale;
    f32 depth[4];
    f32 world[16];
    s32 rot[4];
    St_b045_01E00E30 uv;
    s16 i;
    s16 n;
    s32 h;
    s8 *p;
    f32 r;
    f32 f;
    f32 fx;
    f32 fy;
    f32 fz;

    func_00207500();
    n = *(s16 *)(self + 0xB8);
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
    func_01E00080_b636((Pk_b008_01E00080 *)pk, (Rect_b008_01E00080 *)(self + 0x94), 0);
    func_00208700(pk, *(void **)(self + 0x88), 1);
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    fx = obj->tab;
    fy = obj->dy;
    fz = obj->dz;
    fx /= 10.0f;
    fy /= 10.0f;
    fz /= 10.0f;
    pos.x = obj->x + fx;
    pos.y = obj->y + fy;
    pos.z = obj->z + fz;
    func_00108EF0(world, &scale, 0, &pos);
    for (i = 0; i < n; i++) {
        r = obj->size;
        func_00108CE0(m, r, r);
        func_00109100(m, rot, 0, self + 0xD8);
        p = base + i;
        h = i >> 1;
        f = p[obj->tab];
        f /= 20.0f;
        func_00107070(m, 0, f * (obj->scale + h));
        f = p[obj->tab + 100];
        f /= 20.0f;
        func_00107070(m, 1, f * (obj->scale + h));
        f = p[obj->tab + 180];
        f /= 20.0f;
        func_00107070(m, 2, f * (obj->scale + h));
        if (func_00205630((s32)m, 0x70000000, (s32)world, (s32)pk, depth) != 0) {
            func_002075F0((s32)pk, *(s32 *)(self + 0x80), func_001A23B0(depth[0]));
        }
    }
}

/* shape b636:01E00850, 136 insns: scene spawn step: red scene colour; t++; frame 51 stores joint B's point; frames
   52..64 copy it into the spawn point (six times); before frame 106 one 0x1E00A70 a tick at joint A raised 1; frames
   107..304 one 0x1E00C50 at joint A raised 4, plus one 0x1E00E60 every fourth frame */

typedef struct {
    u8 pad0[0x2D0];
    Vec4f pos;
    u8 pad2E0[0x33E0];
    Vec4f pt;
    u8 pad36D0[0xD4];
    u8 col[4];
    u8 pad37A8[0x40];
    s16 ja;
    s16 jb;
    u8 pad37EC[0x12];
    s16 t;
} Scene_b636_01E00850;

static void func_01E00850_b636(Scene_b636_01E00850 *g) {
    extern void b636_01E00A70(void);
    extern void b636_01E00C50(void);
    extern void b636_01E00E60(void);
    extern void b636_01E01650(void *, void *, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, void *);
    Vec4f v;
    s32 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    if (g->t == 0x33) {
        func_001F5620(func_001F53A0(), g->jb, &g->pt);
    }
    if (g->t > 0x33 && g->t < 0x41) {
        func_001F5620(func_001F53A0(), g->jb, &v);
        for (i = 0; i < 6; i++) {
            g->pos.x = g->pt.x;
            g->pos.y = g->pt.y;
            g->pos.z = g->pt.z;
        }
    }
    if (g->t < 0x6A) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 1.0f + v.y;
        g->pos.z = v.z;
        b636_01E01650(g, b636_01E00A70, 0);
    }
    if (g->t > 0x6A && g->t < 0x131) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 4.0f + v.y;
        g->pos.z = v.z;
        b636_01E01650(g, b636_01E00C50, 0);
    }
    if (g->t % 4 == 1 && g->t > 0x6A && g->t < 0x131) {
        func_001F5620(func_001F53A0(), g->ja, &v);
        g->pos.x = v.x;
        g->pos.y = 4.0f + v.y;
        g->pos.z = v.z;
        b636_01E01650(g, b636_01E00E60, 0);
    }
}

/* func_001076F0 takes plain ints here (functions.h says s8): hide that prototype */

/* OVL_WARM */

/* shape b636:01E00A70, 119 insns: spark pinned to a scene object with random spin and life; bigger early in the scene */

typedef struct Sp_b636_01E00A70 {
    s16 x, y, z;
    s16 life;
    s16 h8;
    u8 padA[4];
    s16 spin;
    u8 pad10[4];
    s32 f14;
    u8 pad18[0x10];
    u8 c28[4];
    u8 c2C[4];
    s16 rot;
    s16 age;
    s16 h34;
    s16 state;
    s16 h38;
    s16 h3A;
} Sp_b636_01E00A70;

typedef struct Scn_b636_01E00A70 {
    u8 pad0[0x37E8];
    s16 id;
    u8 pad37EA[0x14];
    s16 timer;
} Scn_b636_01E00A70;

static s32 func_01E00A70_b636(Scn_b636_01E00A70 *w, Sp_b636_01E00A70 *o) {
    extern s32 func_001076F0();
    extern s32 func_001F53A0();
    extern void func_001F5620();
    Vec4f v;

    if (o->state == 1) {
        if (w->timer < 0x54) {
            o->h38 = 0x19;
        } else {
            o->h38 = 5;
        }
        o->h34 = func_0019A5C8() % 8;
        o->f14 = func_0019A5C8() % 0xFFFF;
        func_001076F0(o->c28, 0x30, 8, 0x80);
        o->rot = 0;
        o->h3A = func_0019A5C8() % 360;
        o->spin = func_0019A5C8() % 25 + 10;
        o->h8 = func_0019A5C8() % 10;
        o->life = func_0019A5C8() % 7 + 2;
        o->state = 2;
    }
    if (o->age < o->life) {
        if (o->c28[3] < 0x61) {
            o->c28[3] += 0x30;
        }
    } else if (o->c28[3] > 0x10) {
        o->c28[3] -= 0xA;
    } else {
        o->state = 0;
    }
    if (o->age != 0) {
        o->rot += o->spin;
    }
    o->age++;
    func_001F5620(func_001F53A0(), w->id, &v);
    o->x = (s32)v.x;
    o->y = (s32)v.y;
    o->z = (s32)v.z;
    return 0;
}

/* shape b636:01E00C50, 130 insns: a blue spark (size 100 growing 5, frame 0..7, random turn, f30 growing 10..34, f8 0..9) held 11..18 ticks (alpha up by 48), then down by 10; h4 sways by 5 x the sine of the model angle - 180 */

typedef struct {
    u8 pad0[0x3A04];
    u8 trig[1];
} Game_b636_01E00C50;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    s32 rot;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b636_01E00C50;

static s32 func_01E00C50_b636(Game_b636_01E00C50 *g, Fx_b636_01E00C50 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    s32 ang[4];
    s32 d;

    if (o->mode == 1) {
        o->f38 = 100;
        o->f34 = func_0019A5C8() % 8;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0x30, 8, 0x80);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 25 + 10;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 8 + 11;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    func_001F6160(func_001F53A0(), ang);
    d = (s16)(5.0f * -func_00108030(g->trig, (s16)(ang[1] / 180.0f) - 180, 1));
    o->h4 += d;
    o->f38 += 5;
    return 0;
}

/* shape b636:01E00E60, 130 insns: b636:01E00C50 in red (size 110, held 12..19 ticks, sway 6) */

typedef struct {
    u8 pad0[0x3A04];
    u8 trig[1];
} Game_b636_01E00E60;

typedef struct {
    u8 pad0[4];
    s16 h4;
    s16 hold;
    s16 f8;
    u8 padA[4];
    s16 speed;
    u8 pad10[4];
    s32 rot;
    u8 pad18[0x10];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b636_01E00E60;

static s32 func_01E00E60_b636(Game_b636_01E00E60 *g, Fx_b636_01E00E60 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, void *);
    extern f32 func_00108030(void *, s32, s32);
    s32 ang[4];
    s32 d;

    if (o->mode == 1) {
        o->f38 = 110;
        o->f34 = func_0019A5C8() % 8;
        o->rot = func_0019A5C8() % 65535;
        func_001076F0(o->col, 0x80, 8, 0x30);
        o->f30 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->speed = func_0019A5C8() % 25 + 10;
        o->f8 = func_0019A5C8() % 10;
        o->hold = func_0019A5C8() % 8 + 12;
        o->mode = 2;
    }
    if (o->tick < o->hold) {
        if (o->col[3] <= 0x60) {
            o->col[3] += 0x30;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    if (o->tick != 0) {
        o->f30 += o->speed;
    }
    o->tick++;
    func_001F6160(func_001F53A0(), ang);
    d = (s16)(6.0f * -func_00108030(g->trig, (s16)(ang[1] / 180.0f) - 180, 1));
    o->h4 += d;
    o->f38 += 5;
    return 0;
}

/* shape b636:01E01070, 41 insns: look up the textures: group 4 cells 0-2, group 4 cells 13-15, group 5
   cells 0-2 (variant of b205:01E02370) */

typedef struct {
    u8 pad0[0x340];
    s32 tex[16];
    u8 pad380[0x3400];
    s32 tex5[3];
} Scene_b636_01E01070;

static void func_01E01070_b636(s32 arg0, Scene_b636_01E01070 *o) {
    s32 i;

    for (i = 0; i < 3; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 13; i < 16; i++) {
        o->tex[i] = func_00202BF0(4, i);
    }
    for (i = 0; i < 3; i++) {
        o->tex5[i] = func_00202BF0(5, i);
    }
}

/* shape b636:01E01120 (b636), 330 insns, 1 copy: b636 scene manager (b069:01E01210 / b538:01E00EA0 family): with a
   scene id (>= 0) it clears the scene, resets both camera blocks, keeps the id, sets the 355-frame countdown, zeroes
   three fades, takes eight model handles, loads textures and fills two 256-entry jitter tables (A: -15..14; B: 0..99
   -6..5, 100..179 -2..1, 180..255 -4..3); otherwise it runs the spawn step and every live node update, then draws
   each live node with its texture, rect and jitter table, counts down and returns 1 / 4 / 2 / 6 at frames 105 / 325 /
   315 / 116..309, 8 once the countdown runs out */

typedef struct {
    u8 pad0[0x24];
    void *fn;
    u8 pad28[0xC];
    s16 frame;
    s16 used;
    u8 pad38[8];
} Slot_b636_01E01120;

typedef struct {
    u8 pad0[0x80];
    s32 ot;
    u8 pad84[4];
    s32 tex88;
    u8 pad8C[8];
    Vec4f rect;
    u8 padA4[0x14];
    s16 hB8;
    u8 padBA[0x1E];
    u8 crdD8[0x238];
    s32 w310;
    s32 w314;
    s32 w318;
    u8 pad31C[0x478 - 0x31C];
    Slot_b636_01E01120 slot[200];
    u8 pad3678[0x108];
    s32 tex[3];
    u8 pad378C[0x37A0 - 0x378C];
    s32 timer;
    u8 pad37A4[8];
    s32 ot2;
    u8 pad37B0[0x37E8 - 0x37B0];
    s16 joint[8];
    u8 pad37F8[4];
    s16 code;
    s16 step;
    u8 pad3800[2];
    s8 noiseA[0x100];
    s8 noiseB[0x100];
    u8 pad3A02[2];
    u8 crd3A04[1];
} Scene_b636_01E01120;

static s32 func_01E01120_b636(s32 arg0, s32 code) {
    extern void b636_01E00850(Scene_b636_01E01120 *, s32);
    extern s32 b636_01E00A70(void *, void *);
    extern s32 b636_01E00C50(void *, void *);
    extern s32 b636_01E00E60(void *, void *);
    extern void b636_01E004D0(Scene_b636_01E01120 *, Slot_b636_01E01120 *, void *, s8 *);
    extern void b636_01E01070(s32, Scene_b636_01E01120 *);
    Scene_b636_01E01120 *g = (Scene_b636_01E01120 *)arg0;
    extern s32 func_00207500(void);
    extern void func_00195108(void *, s32);
    extern void func_00107C10(void *);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s16 func_001F5560(s32, s32, s32);
    extern void func_001F5F90(s32, void *);
    extern void func_00106080(void *, s32, s32, void *);
    f32 pos[4];
    f32 r1[4];
    f32 r2[4];
    f32 r3[4];
    u8 buf[0x90];
    s32 n;
    s32 i;

    n = 0;
    g->ot = func_00207500();
    g->ot2 = func_00207500();
    if (code >= 0) {
        func_00195108(g, 0x3B70);
        func_00107C10(g->crd3A04);
        func_00107C10(g->crdD8);
        g->code = code;
        g->timer = 355;
        g->w310 = 0;
        g->w314 = 0;
        g->w318 = 0;
        g->joint[0] = func_001F5560(func_001F53A0(), 0x11, 1);
        g->joint[1] = func_001F5560(func_001F53A0(), 5, 0);
        g->joint[2] = func_001F5560(func_001F53A0(), 6, 0);
        g->joint[3] = func_001F5560(func_001F53A0(), 0xD, 0);
        g->joint[4] = func_001F5560(func_001F53A0(), 0xE, 0);
        g->joint[5] = func_001F5560(func_001F53A0(), 0xF, 0);
        g->joint[6] = func_001F5560(func_001F53A0(), 0x17, 0);
        g->joint[7] = func_001F5560(func_001F53A0(), 0x1A, 0);
        b636_01E01070(0, g);
        for (i = 0; i < 0x100; i++) {
            g->noiseA[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 0; i < 0x100; i++) {
            g->noiseB[i] = func_0019A5C8() % 30 - 15;
        }
        for (i = 100; i < 180; i++) {
            g->noiseB[i] = func_0019A5C8() % 4 - 2;
        }
        for (i = 0; i < 100; i++) {
            g->noiseB[i] = func_0019A5C8() % 12 - 6;
        }
        for (i = 180; i < 0x100; i++) {
            g->noiseB[i] = func_0019A5C8() % 8 - 4;
        }
        return 0;
    }
    b636_01E00850(g, 0);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            if (g->slot[i].fn == b636_01E00A70) {
                b636_01E00A70(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b636_01E00C50) {
                b636_01E00C50(g, &g->slot[i]);
            }
            if (g->slot[i].fn == b636_01E00E60) {
                b636_01E00E60(g, &g->slot[i]);
            }
        }
    }
    func_001F5F90(func_001F5380(), pos);
    for (i = 0; i < 200; i++) {
        if (g->slot[i].used != 0) {
            n++;
            if (g->slot[i].fn == b636_01E00A70) {
                g->tex88 = g->tex[0];
                func_00106080(r1, 0x14, g->slot[i].frame, 0);
                g->rect = *(Vec4f *)r1;
                g->hB8 = 6;
                b636_01E004D0(g, &g->slot[i], buf, g->noiseB);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == b636_01E00C50) {
                g->tex88 = g->tex[1];
                func_00106080(r2, 0x14, g->slot[i].frame, 0);
                g->rect = *(Vec4f *)r2;
                g->hB8 = 0x12;
                b636_01E004D0(g, &g->slot[i], buf, g->noiseA);
                g->hB8 = 0;
            }
            if (g->slot[i].fn == b636_01E00E60) {
                g->tex88 = g->tex[2];
                func_00106080(r3, 0x14, g->slot[i].frame, 0);
                g->rect = *(Vec4f *)r3;
                g->hB8 = 0xC;
                b636_01E004D0(g, &g->slot[i], buf, g->noiseA);
                g->hB8 = 0;
            }
        }
    }
    if (g->timer != 0) {
        g->timer--;
    }
    if (g->step == 105) {
        return 1;
    }
    if (g->step == 325) {
        return 4;
    }
    if (g->step == 315) {
        return 2;
    }
    if (g->step > 115 && g->step < 310) {
        return 6;
    }
    if (g->timer <= 0) {
        return 8;
    }
    return 0;
}

/* shape b636:01E01650, 72 insns: twin of b046:01E03E20: take the first free slot of the 200-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x37FA and the two arguments; returns 1 if a
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
} Slot_b636_01E01650;

typedef struct {
    u8 pad[0x2D0];
    u8 m[0x1A8];
    Slot_b636_01E01650 s[200];
    u8 pad3678[0x12C];
    u8 r, g, b, a;
    u8 pad37A8[0x52];
    s16 v;
} Pool_b636_01E01650;

static s32 func_01E01650_b636(Pool_b636_01E01650 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b636_01E01650 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 200; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 200;
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
