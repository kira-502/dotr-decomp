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

static void func_01E00080_b136(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

/* shape b081:01E00080, 30 insns, 24 copies (s32 twin of b034:01E00080): shift a position history down by one, the newest from src */

static s32 func_01E00260_b136(Vec4f *dst, s32 n, s32 arg2, Vec4f *src) {
    s32 i;
    s32 k = n - 1;
    Vec4f *prev = dst;

    prev--;
    for (i = 0; i < n; i++, dst--, prev--, k--) {
        if (k != 0) {
            dst->x = prev->x;
            dst->y = prev->y;
            dst->z = prev->z;
        } else {
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
        }
    }
    return 0;
}

/* shape b136:01E002E0 (B136_W_S), 373 insns, 1 copy: the scene step: colour 0x80,0,0,0, counts the frame
   (0x365C), re-picks the joint on frames 94..184 step 10, then on frames 95..185 step 10 puts the point at the joint,
   spawns 0x1E00CA0 on side n, fills trail row n with the point, spawns three 0x1E01670 and bumps n; frame 1 spawns
   0x1E01950 */

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    u8 pad90[0x2FC0 - 0x90];
    Vec4f row[10][10];
    u8 pad3600[4];
    u8 col[4];
    u8 pad3608[0x3648 - 0x3608];
    s16 joint;
    u8 pad364A[0x3658 - 0x364A];
    s16 side;
    u8 pad365A[2];
    s16 t;
    u8 pad365E[2];
    s16 n;
} Scene_b136_01E002E0;

static void func_01E002E0_b136(Scene_b136_01E002E0 *g) {
    extern void b136_01E00CA0(void);
    extern void b136_01E01670(void);
    extern void b136_01E01950(void);
    extern void b136_01E01F00(Scene_b136_01E002E0 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5560(s32, s32, s32);
    extern void func_001F5620(s32, s32, void *);
    f32 v[4];

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F5620(func_001F53A0(), g->joint, v);
    if (g->t == 94) {
        g->joint = func_001F5560(func_001F53A0(), 35, 1);
    }
    if (g->t == 104) {
        g->joint = func_001F5560(func_001F53A0(), 11, 1);
    }
    if (g->t == 114) {
        g->joint = func_001F5560(func_001F53A0(), 16, 1);
    }
    if (g->t == 124) {
        g->joint = func_001F5560(func_001F53A0(), 21, 1);
    }
    if (g->t == 134) {
        g->joint = func_001F5560(func_001F53A0(), 26, 1);
    }
    if (g->t == 144) {
        g->joint = func_001F5560(func_001F53A0(), 35, 1);
    }
    if (g->t == 154) {
        g->joint = func_001F5560(func_001F53A0(), 11, 1);
    }
    if (g->t == 164) {
        g->joint = func_001F5560(func_001F53A0(), 16, 1);
    }
    if (g->t == 174) {
        g->joint = func_001F5560(func_001F53A0(), 21, 1);
    }
    if (g->t == 184) {
        g->joint = func_001F5560(func_001F53A0(), 26, 1);
    }
    func_001F5620(func_001F53A0(), g->joint, v);
    if (g->t == 95 || g->t == 105 || g->t == 115 || g->t == 125 || g->t == 135 || g->t == 145 ||
        g->t == 155 || g->t == 165 || g->t == 175 || g->t == 185) {
        g->side = g->n;
        g->pos.x = v[0];
        g->pos.y = v[1];
        g->pos.z = v[2];
        b136_01E01F00(g, b136_01E00CA0, 0);
        if (g->n == 0) {
            s32 i;
            Vec4f *p = g->row[0];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 1) {
            s32 i;
            Vec4f *p = g->row[1];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 2) {
            s32 i;
            Vec4f *p = g->row[2];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 3) {
            s32 i;
            Vec4f *p = g->row[3];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 4) {
            s32 i;
            Vec4f *p = g->row[4];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 5) {
            s32 i;
            Vec4f *p = g->row[5];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 6) {
            s32 i;
            Vec4f *p = g->row[6];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 7) {
            s32 i;
            Vec4f *p = g->row[7];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 8) {
            s32 i;
            Vec4f *p = g->row[8];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        if (g->n == 9) {
            s32 i;
            Vec4f *p = g->row[9];
            for (i = 0; i < 10; i++, p++) {
                p->x = v[0];
                p->y = v[1];
                p->z = v[2];
            }
        }
        b136_01E01F00(g, b136_01E01670, 0);
        b136_01E01F00(g, b136_01E01670, 0);
        b136_01E01F00(g, b136_01E01670, 0);
        g->n++;
    }
    if (g->t == 1) {
        b136_01E01F00(g, b136_01E01950, 0);
    }
}

/* shape b136:01E008C0, 134 insns: b019:01E01F60 with its sine table at ctx+0x3664 */

/* OVL_WARM */

typedef struct {
    u8 pad0[0x3664];
    u8 tab[1];
} Mgr_b136_01E008C0;

typedef struct {
    u8 pad0[8];
    s16 x;
    s16 y;
    s16 z;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 f30;
    s16 tick;
    s16 f34;
    s16 mode;
    s16 f38;
    s16 f3A;
} Fx_b136_01E008C0;

static s32 func_01E008C0_b136(Mgr_b136_01E008C0 *m, Fx_b136_01E008C0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x30, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->f3A = func_0019A5C8() % 360;
        o->f34 = 0;
        o->f30 = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 10) {
        if (o->col[3] < 0x60) {
            o->col[3] += 9;
        }
    } else if (o->col[3] > 16) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->tick % 2 == 1) {
        if (o->f38 < 18) {
            o->f38++;
        }
    }
    if (o->tick % 3 == 1) {
        if (o->f34 < 7) {
            o->f34++;
        }
    }
    o->x = o->x + 10.0f * func_00108030(m->tab, o->f3A, 0);
    o->y = o->y + 4.0f * func_00108030(m->tab, o->f30, 1);
    o->z = o->z + 10.0f * func_00108030(m->tab, o->f3A, 1);
    return 0;
}

typedef struct {
    u8 pad0000[0x3664];
    u8 tab[1];
} Mgr_b136_01E00AE0;

typedef struct {
    u8 pad00[8];
    s16 x, y, z;
    u8 pad0E[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    s16 h3A;
} Obj_b136_01E00AE0;

static s32 func_01E00AE0_b136(Mgr_b136_01E00AE0 *m, Obj_b136_01E00AE0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0xCF, 0x50, 0x50);
    if (o->h36 == 1) {
        o->h38 = 6;
        o->h3A = func_0019A5C8() % 360;
        o->h34 = func_0019A5C8() % 4;
        o->h30 = func_0019A5C8() % 360;
        o->h36 = 2;
    }
    if (o->h32 < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x14;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->h36 = 0;
    }
    o->h32++;
    o->x = o->x + 13.0f * func_00108030(m->tab, o->h3A, 0);
    o->y = o->y + 13.0f * func_00108030(m->tab, o->h30, 1);
    o->z = o->z + 13.0f * func_00108030(m->tab, o->h3A, 1);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E00CA0_b136);

/* shape b136:01E014B0, 110 insns: b266:01E01610 family: a red ember (size 7, random frame 0..3) at two random angles drifting 7 a tick on all three axes (sine table ctx+0x3664): in by 20 up to 0xA0 for 8 ticks, then out by 5 and ends */

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x1A];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b136_01E014B0;

typedef struct {
    u8 pad[0x3664];
    u8 sin[1];
} Game_b136_01E014B0;

static s32 func_01E014B0_b136(Game_b136_01E014B0 *g, Glow_b136_01E014B0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);
    extern s16 func_001A22C0(f32);

    func_001076F0(o->col, 0x4F, 0x1F, 0x1F);
    if (o->mode == 1) {
        o->f38 = 7;
        o->ang = func_0019A5C8() % 360;
        o->kind = func_0019A5C8() % 4;
        o->h30 = func_0019A5C8() % 360;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 0x14;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    o->h8 = func_001A22C0(o->h8 + 7.0f * func_00108030(g->sin, o->ang, 0));
    o->hA = func_001A22C0(o->hA + 7.0f * func_00108030(g->sin, o->h30, 1));
    o->hC = func_001A22C0(o->hC + 7.0f * func_00108030(g->sin, o->ang, 1));
    return 0;
}

/* shape b136:01E01670, 67 insns: a tumbling spark at three random turns, growing 1 and turning 0x400 a tick: in by 64 for 2 ticks, then orange, out by 10 and ends */

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
} Glow_b136_01E01670;

static s32 func_01E01670_b136(s32 arg0, Glow_b136_01E01670 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x8F, 0x1F, 0x10);
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->w14 += 0x400;
    o->f38++;
    o->tick++;
    return 0;
}

/* shape b136:01E01780, 48 insns: an orange flash placed at (0x4000, 0x400, 0): fades in by 0x26 for 5 ticks, out by 10 and ends; grows 1 a tick */

typedef struct {
    u8 pad0[6];
    s16 h6;
    u8 pad8[8];
    s32 w10;
    s32 w14;
    s32 w18;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Glow_b136_01E01780;

static s32 func_01E01780_b136(s32 arg0, Glow_b136_01E01780 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 5;
        func_001076F0(o->col, 0x8F, 0x1F, 0xF0);
        o->w10 = 0x4000;
        o->w14 = 0x400;
        o->w18 = 0;
        o->mode = 2;
    }
    if (o->tick < 5) {
        o->col[3] += 0x26;
    } else if (o->col[3] > 0x10) {
        o->col[3] -= 10;
    } else {
        o->mode = 0;
    }
    o->f38++;
    o->tick++;
    return 0;
}

/* shape b136:01E01840, 67 insns: a tumbling spark at three random turns, growing 1 and turning 0x400 a tick: in by 64 for 2 ticks, then dark, out by 14 and ends */

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
} Glow_b136_01E01840;

static s32 func_01E01840_b136(s32 arg0, Glow_b136_01E01840 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        func_001076F0(o->col, 0x2F, 0x1F, 0x20);
        o->w10 = func_0019A5C8() % 65535;
        o->w14 = func_0019A5C8() % 65535;
        o->w18 = func_0019A5C8() % 65535;
        o->mode = 2;
    }
    if (o->tick < 2) {
        o->col[3] += 0x40;
    } else if (o->col[3] > 0xF) {
        o->col[3] -= 14;
    } else {
        o->mode = 0;
    }
    o->w14 += 0x400;
    o->f38++;
    o->tick++;
    return 0;
}

/* shape b136:01E01950, 31 insns: func_001F7170(6, 2, &a, &b, 0) with copies of the module's floats at 0x01E02600 and
   0x01E02608; when the game value at 0x365C is 94 the effect's 0x36 is cleared; return 0 */

typedef struct {
    f32 v;
} F_b136_01E01950;

typedef struct {
    u8 pad0[0x365C];
    s16 v;
} Game_b136_01E01950;

typedef struct {
    u8 pad0[0x36];
    s16 f36;
} Fx_b136_01E01950;

extern F_b136_01E01950 D_01E02600_b136;
extern F_b136_01E01950 D_01E02608_b136;

static s32 func_01E01950_b136(Game_b136_01E01950 *g, Fx_b136_01E01950 *o) {
    extern void func_001F7170(s32, s32, void *, void *, s32);
    F_b136_01E01950 a;
    F_b136_01E01950 b;

    a = D_01E02600_b136;
    b = D_01E02608_b136;
    func_001F7170(6, 2, &a, &b, 0);
    if (g->v == 94) {
        o->f36 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E019D0_b136);

/* shape b136:01E01F00, 72 insns: twin of b046:01E03E20: take the first free slot of the 180-slot pool, clear it, give
   it the scene's colour twice, the scene matrix, the scene's value 0x3658 and the two arguments; returns 1 if a
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
} Slot_b136_01E01F00;

typedef struct {
    u8 pad[0x80];
    u8 m[0x204];
    Slot_b136_01E01F00 s[180];
    u8 pad2F84[0x680];
    u8 r, g, b, a;
    u8 pad3608[0x50];
    s16 v;
} Pool_b136_01E01F00;

static s32 func_01E01F00_b136(Pool_b136_01E01F00 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b136_01E01F00 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 180; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 180;
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

/* shape b136:01E02020, 41 insns: mode 0 sets up the drawing state: a 0x96 matrix from the anim's angle at 0x34,
   colour, texture group 4 cell 15 */

typedef struct {
    u8 pad0[0x28];
    u8 col[0xC];
    s16 h34;
} Anim_b136_01E02020;

static void func_01E02020_b136(s32 arg0, Anim_b136_01E02020 *an, void *p, s32 mode) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    f32 rm[4];

    func_00207500();
    if (mode == 0) {
        func_00106080(rm, 0x96, an->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, an->col, 0);
        func_00108500(p, rm, 1);
        func_00208700(p, func_00202BF0(4, 15), 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/mod/b136", func_01E020D0_b136);

/* shape b136:01E02400, 119 insns: draws a small depth-sorted sprite (b117:01E02A30 shape) with its own turn at a tenth scale: unlit,
   it sets up the colour and texture page; lit, it sends the square of its size at its depth if it lands on screen */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 dx, dy, dz;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[0xC];
    s16 h34;
    u8 pad36[2];
    s16 size;
} Fx_b136_01E02400;

typedef struct {
    u8 pad0[0x10C];
    s32 tex;
} Scene_b136_01E02400;

static void func_01E02400_b136(Scene_b136_01E02400 *g, Fx_b136_01E02400 *o, void *p, s32 lit) {
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_00109380(void *, s32);
    extern s32 func_001A23B0(f32);
    Vec4f quad[4];
    f32 z[4];
    Vec4f pos;
    Vec4f scale;
    f32 rm[4];
    f32 m[16];
    s32 rot[4];
    s32 v;

    v = (s32)func_00207500();
    if (lit == 0) {
        func_00106080(rm, 0x99, o->h34, rm);
        func_00109270(p, 0, 0);
        func_00107790(p, o->col, 0);
        func_00108500(p, rm, 0);
        func_00208700(p, g->tex, 1);
        return;
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->dx / 10;
    pos.y = o->y + o->dy / 10;
    pos.z = o->z + o->dz / 10;
    scale.x = 0.1f;
    scale.y = 0.1f;
    scale.z = 0.1f;
    func_00108EF0(m, &scale, o->rot, &pos);
    func_00108CE0(quad, o->size, o->size);
    if (func_00205630(quad, 0x70000000, m, p, z) != 0) {
        func_00109380(p, 0);
        func_002075F0((s32)p, v, func_001A23B0(z[0]));
    }
}
