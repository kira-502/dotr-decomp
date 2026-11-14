#include "common.h"

typedef struct Cam_c536_01E00120 {
    f32 pos[3];
    u8 padC[4];
    s32 a[3];
    u8 pad1C[4];
    s32 b[3];
    u8 pad2C[4];
    f32 f30;
    f32 f34;
    u8 pad38[0x10];
    s32 steps;
} Cam_c536_01E00120;

static s32 func_01E00080_c538(Cam_c536_01E00120 *c, Cam_c536_01E00120 *t) {
    f32 k;
    f32 px;
    f32 py;
    f32 pz;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 b1;
    s32 b2;

    if (t->steps != 0) {
        k = 1.0f / t->steps;
        py = k * (t->f30 - c->f30);
        pz = k * (t->f34 - c->f34);
        c->f30 += py;
        c->f34 += pz;
        a0 = k * (t->a[0] - c->a[0]);
        a1 = k * (t->a[1] - c->a[1]);
        a2 = k * (t->a[2] - c->a[2]);
        c->a[0] += a0;
        c->a[1] += a1;
        c->a[2] += a2;
        a2 = k * (t->b[0] - c->b[0]);
        a0 = k * (t->b[1] - c->b[1]);
        a1 = k * (t->b[2] - c->b[2]);
        c->b[0] += a2;
        c->b[1] += a0;
        c->b[2] += a1;
        px = k * (t->pos[0] - c->pos[0]);
        py = k * (t->pos[1] - c->pos[1]);
        pz = k * (t->pos[2] - c->pos[2]);
        c->pos[0] += px;
        c->pos[1] += py;
        c->pos[2] += pz;
    }
    t->steps--;
    return t->steps;
}

/* shape c536:01E00330: module copy of main-program func_0027F180 (rules/ta_misc.c): reset every vertex colour to white with the given alpha, then refresh the model. */

typedef struct Vertex_c536_01E00330 {
    u8 pad0[0x10];
    u64 lower : 32;
    u64 color : 24;
    u64 upper : 8;
    u8 pad18[3];
    u8 alpha;
    u8 pad1C[0x14];
} Vertex_c536_01E00330;

typedef struct Count_c536_01E00330 {
    s16 count : 12;
    s16 reserved : 4;
} Count_c536_01E00330;

typedef struct Object_c536_01E00330 {
    u8 pad0[0x78];
    Vertex_c536_01E00330 *vertices;
    s32 field7C;
    s16 field80;
    Count_c536_01E00330 field82;
    u8 pad84[0xC];
    s32 field90;
} Object_c536_01E00330;

static s32 func_01E00290_c538(void *arg0, s32 arg1, f32 *arg2) {
    Object_c536_01E00330 *object = arg0;
    s32 result;
    s32 i;

    if (arg2 != NULL) {
        result = func_001DA2B0(object, 0, arg2[0], arg2[1]);
    } else {
        result = func_001D9F00(object, 1);
    }
    for (i = 0; i < object->field82.count; i++) {
        object->vertices[i].color = 0xFFFFFF;
        object->vertices[i].alpha = arg1;
    }
    if (result != 0) {
        func_001DA7A0(object->field90, (s32) object);
    } else {
        func_001DA7A0(0, (s32) object);
    }
    func_001DBCF0((s32) object);
    return 0;
}

/* shape c536:01E00440, 164 insns, 9 copies: draw a model's afterimages: for each older transform in the history
   (newest last), a copy of the model placed there with alpha / (k + 1) (far z), then the model itself */

typedef struct Prim_c536_01E00440 {
    u8 pad0[0x10];
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
    u8 pad18[3];
    u8 a;
    u8 pad1C[0x14];
} Prim_c536_01E00440;

typedef struct Mdl_c536_01E00440 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    Vec4f v30;
    u8 pad40[0x38];
    Prim_c536_01E00440 *prims;
    u8 pad7C[6];
    s16 count : 12;
    s16 pad82 : 4;
    u8 pad84[0xC];
} __attribute__((aligned(16))) Mdl_c536_01E00440;

typedef struct Obj_c536_01E00440 {
    Mdl_c536_01E00440 m;
    s32 f90;
} Obj_c536_01E00440;

typedef struct Hist_c536_01E00440 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    u8 pad30[0x40];
} Hist_c536_01E00440;

static s32 func_01E003A0_c538(Obj_c536_01E00440 *o, s32 alpha, s32 n, Hist_c536_01E00440 *hist) {
    extern s32 func_001D9F00();
    extern void func_001DA7A0();
    extern void func_001DBCF0();
    Mdl_c536_01E00440 copy;
    s32 k;
    s32 j;
    s32 r;

    for (k = n - 1; k > 0; k--) {
        copy = o->m;
        copy.v00 = hist[k].v20;
        copy.v10 = hist[k].v10;
        copy.v30 = hist[k].v00;
        r = func_001D9F00(&copy, 1);
        for (j = 0; j < copy.count; j++) {
            copy.prims[j].z = 0xFFFFFE;
            if (alpha) {
                copy.prims[j].a = alpha / (k + 1);
            } else {
                copy.prims[j].a = 0;
            }
        }
        if (k == n - 1) {
            if (r) {
                func_001DA7A0(o->f90, o);
            } else {
                func_001DA7A0(0, o);
            }
        }
        func_001DBCF0(&copy);
    }
    func_001D9F00(o, 1);
    for (j = 0; j < o->m.count; j++) {
        o->m.prims[j].z = 0xFFFFFF;
        o->m.prims[j].a = alpha;
    }
    func_001DBCF0(o);
    return 0;
}

/* shape c538:01E00630 (c538), 678 insns, 1 copy: the c538 module main (c615:01E00420's two-unit form): on start
   copies both unit models and places them at -125/125, -8 (code > 0 sends them in from the sides over 20 ticks); each
   tick steps the units in, then B rides toward A with afterimages, flag 6 spins A away; returns 2 on tick 34, 8 when
   done */

typedef struct Src_c538_01E00630 {
    Vec4f p0;
    Vec4f p1;
    u8 pad20[0x23];
    u8 f43;
    u8 pad44[0x5C];
} __attribute__((aligned(16))) Src_c538_01E00630;

typedef struct Unit_c538_01E00630 {
    Vec4f pos;
    s32 rot[4];
    s32 v20[4];
    Vec4f v30;
    u8 pad40[0x41];
    s8 lo : 5;
    s8 b5 : 1;
    s8 b6 : 1;
    s8 b7 : 1;
    u8 pad82[0x1E];
} __attribute__((aligned(16))) Unit_c538_01E00630;

typedef struct Ctl_c538_01E00630 {
    Vec4f a;
    s32 b[4];
    s32 z[3];
    u8 pad2C[4];
    f32 s[2];
    u8 pad38[8];
    f32 x;
    f32 y;
    s32 on;
    u8 pad4C[4];
} Ctl_c538_01E00630;

typedef struct Hist_c538_01E00630 {
    Vec4f v00;
    Vec4f v10;
    Vec4f v20;
    u8 pad30[0x40];
} Hist_c538_01E00630;

typedef struct Scene_c538_01E00630 {
    Hist_c538_01E00630 hist[4];
    Unit_c538_01E00630 a;
    Unit_c538_01E00630 b;
    Ctl_c538_01E00630 ctl[2];
    Vec4f p3A0;
    Vec4f p3B0;
    s32 timer;
    s32 timer2;
    s32 life;
    s32 code;
    s32 flags;
    s32 count;
    s32 alpha;
    u8 pad3DC[4];
} Scene_c538_01E00630;

static s32 func_01E00630_c538(s32 arg0, s32 code) {
    Scene_c538_01E00630 *g = (Scene_c538_01E00630 *)arg0;
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern s32 func_001F5B30(s32);
    extern s32 func_001F59D0(s32, s32);
    extern void func_00195108(void *, s32);
    extern void func_00205CB0(void *, f32, f32);
    extern void func_00205C40();
    extern void func_00104490(void *, void *, s32);
    extern s32 func_00207F60(void);
    extern void func_00207FD0(s32, s32, s32);
    extern s32 c538_01E00080();
    extern s32 c538_01E00290();
    extern s32 c538_01E003A0();
    s32 idA;
    s32 idB;
    Src_c538_01E00630 *a;
    Src_c538_01E00630 *b;
    s32 ot;
    s32 i;

    func_00207500();
    idA = func_001F53A0();
    idB = func_001F5380();
    a = (Src_c538_01E00630 *)func_001F5B30(idA);
    b = (Src_c538_01E00630 *)func_001F5B30(idB);
    if (a == NULL) {
        return 8;
    }
    if (a == NULL && b == NULL) {
        return 8;
    }
    if (code >= 0) {
        func_00195108(g, 0x3E0);
        if (a) {
            g->a = *(Unit_c538_01E00630 *)a;
        }
        if (b) {
            g->b = *(Unit_c538_01E00630 *)b;
        }
        if (a) {
            func_001F59D0(idA, 1);
            g->a.b6 = 1;
            g->a.b5 = 1;
        }
        if (b) {
            func_001F59D0(idB, 1);
            g->b.b6 = 1;
            g->b.b5 = 1;
        }
        g->flags = 0;
        g->life = 0x78;
        g->code = code;
        if (g->code == 0) {
            g->count = 20;
        } else {
            g->count = 0;
        }
        g->timer = 14;
        g->timer2 = 10;
        if (a) {
            a->f43 = 0;
        }
        if (b) {
            b->f43 = 0;
        }
        g->alpha = 0x80;
        {
            f32 r = -350.0f;
            func_00205CB0(&g->p3A0, r, r);
        }
        func_00205CB0(&g->p3B0, -125.0f, -8.0f);
        g->ctl[0].x = -125.0f;
        g->ctl[0].y = -8.0f;
        g->ctl[1].x = 125.0f;
        g->ctl[1].y = -8.0f;
        if (g->code > 0) {
            g->ctl[0].on = 20;
            func_00205CB0(&g->ctl[0], g->ctl[0].x, g->ctl[0].y);
            func_00205C40(g->ctl[0].z);
            g->ctl[0].z[0] -= g->a.v20[0];
            g->ctl[0].z[1] -= g->a.v20[1];
            g->ctl[0].z[2] -= g->a.v20[2];
            g->ctl[0].b[0] = 0;
            g->ctl[0].b[1] = 0x10000;
            g->ctl[0].b[2] = 0x10000;
            g->ctl[0].s[0] = 0.46875f;
            g->ctl[0].s[1] = 0.48913f;
            if (b) {
                g->ctl[1].on = 20;
                func_00205CB0(&g->ctl[1], g->ctl[1].x, g->ctl[1].y);
                func_00205C40(g->ctl[1].z);
                g->ctl[1].z[0] -= g->b.v20[0];
                g->ctl[1].z[1] -= g->b.v20[1];
                g->ctl[1].z[2] -= g->b.v20[2];
                g->ctl[1].b[0] = 0;
                g->ctl[1].b[1] = 0x10000;
                g->ctl[1].b[2] = 0x10000;
                g->ctl[1].s[0] = 0.46875f;
                g->ctl[1].s[1] = 0.48913f;
            }
        } else {
            g->flags |= 1;
            g->ctl[0].on = 1;
            func_00205CB0(&g->a, g->ctl[0].x, g->ctl[0].y);
            g->ctl[0].a = a->p0;
            func_00205C40(g->a.v20);
            g->ctl[0].z[0] = g->ctl[0].z[1] = g->ctl[0].z[2] = 0;
            g->a.rot[0] = 0;
            g->a.rot[1] = 0x10000;
            g->a.rot[2] = 0x10000;
            *(Vec4f *)g->ctl[0].b = a->p1;
            g->ctl[0].s[0] = g->ctl[0].s[1] = 0.1f;
            g->a.v30.x = 0.46875f;
            g->a.v30.y = 0.48913f;
            if (b) {
                g->flags |= 2;
                g->ctl[1].on = 1;
                func_00205CB0(&g->b, g->ctl[1].x, g->ctl[1].y);
                g->ctl[1].a = b->p0;
                func_00205C40(g->b.v20);
                g->ctl[1].z[0] = g->ctl[1].z[1] = g->ctl[1].z[2] = 0;
                g->b.rot[0] = 0;
                g->b.rot[1] = 0x10000;
                g->b.rot[2] = 0x10000;
                *(Vec4f *)g->ctl[1].b = b->p1;
                g->ctl[1].s[0] = g->ctl[1].s[1] = 0.1f;
                g->b.v30.x = 0.46875f;
                g->b.v30.y = 0.48913f;
                for (i = 0; i < 4; i++) {
                    g->hist[i].v20 = g->b.pos;
                    g->hist[i].v10 = *(Vec4f *)g->b.rot;
                    g->hist[i].v00 = g->b.v30;
                }
            }
        }
        return 0;
    }
    ot = func_00207F60();
    func_001D99F0();
    if (!func_00104520(g->flags, 4)) {
        if (func_00104520(g->flags, 0) && func_00104520(g->flags, 1)) {
            c538_01E00290(&g->a, g->alpha, NULL);
            c538_01E003A0(&g->b, g->alpha, 4, g->hist);
            if (g->timer < 7) {
                func_00104490(&g->b, &g->p3B0, g->timer);
            }
            if (g->timer < 3) {
                g->flags |= 0x40;
            }
            if (g->timer) {
                g->timer--;
            } else {
                g->flags |= 0x10;
                g->timer = 12;
            }
        } else {
            if (!func_00104520(g->flags, 0)) {
                if (!c538_01E00080(&g->a, &g->ctl[0])) {
                    g->flags |= 1;
                    g->a.rot[0] = 0;
                    g->a.rot[1] = 0;
                    g->a.rot[2] = 0;
                }
                c538_01E00290(&g->a, g->alpha, NULL);
            }
            if (b && !func_00104520(g->flags, 1)) {
                if (!c538_01E00080(&g->b, &g->ctl[1])) {
                    g->flags |= 2;
                    g->b.rot[0] = 0;
                    g->b.rot[1] = 0;
                    g->b.rot[2] = 0;
                    for (i = 0; i < 4; i++) {
                        g->hist[i].v20 = g->b.pos;
                        g->hist[i].v10 = *(Vec4f *)g->b.rot;
                        g->hist[i].v00 = g->b.v30;
                    }
                }
                c538_01E00290(&g->b, g->alpha, NULL);
            }
        }
    } else if (!func_00104520(g->flags, 5)) {
        g->ctl[1].on = 20;
        g->ctl[1].x = -125.0f;
        g->ctl[1].y = -8.0f;
        func_00205CB0(&g->b, g->ctl[1].x, g->ctl[1].y);
        g->ctl[1].a = b->p0;
        func_00205C40(g->b.v20);
        g->ctl[1].z[0] = g->ctl[1].z[1] = g->ctl[1].z[2] = 0;
        g->b.rot[0] = 0;
        g->b.rot[1] = 0x10000;
        g->b.rot[2] = 0x10000;
        *(Vec4f *)g->ctl[1].b = b->p1;
        g->ctl[1].s[0] = g->ctl[1].s[1] = 0.1f;
        g->b.v30.x = 0.46875f;
        g->b.v30.y = 0.48913f;
        c538_01E00290(&g->a, g->alpha, NULL);
        c538_01E003A0(&g->b, g->alpha, 4, g->hist);
        if (g->timer == 0) {
            if (g->code == 0) {
                g->flags |= 8;
            } else {
                g->flags |= 0x20;
            }
        } else {
            g->timer--;
        }
    } else if (!func_00104520(g->flags, 3)) {
        if (!c538_01E00080(&g->b, &g->ctl[1])) {
            g->flags |= 8;
            g->b.rot[0] = ((Unit_c538_01E00630 *)b)->rot[0];
            g->b.rot[1] = ((Unit_c538_01E00630 *)b)->rot[1];
            g->b.rot[2] = ((Unit_c538_01E00630 *)b)->rot[2];
        }
        c538_01E00290(&g->b, g->alpha, NULL);
    }
    func_001D9DD0();
    func_00207FD0(ot, (s32)func_00207500(), 0);
    if (func_00104520(g->flags, 6)) {
        g->a.rot[0] += 0x1000;
        g->a.rot[2] += 0x1000;
        func_00104490(&g->a, &g->p3A0, g->timer2);
        g->timer2--;
    }
    for (i = 3; i >= 0; i--) {
        if (i != 0) {
            g->hist[i].v20 = g->hist[i - 1].v20;
            g->hist[i].v10 = g->hist[i - 1].v10;
            g->hist[i].v00 = g->hist[i - 1].v00;
        } else {
            g->hist[i].v20 = g->b.pos;
            g->hist[i].v10 = *(Vec4f *)g->b.rot;
            g->hist[i].v00 = g->b.v30;
        }
    }
    g->count++;
    g->life--;
    if (func_00104520(g->flags, 2) || func_00104520(g->flags, 3)) {
        func_001F59D0(idA, 0);
        func_001F59D0(idB, 0);
        return 8;
    }
    if (g->count == 0x22) {
        return 2;
    }
    if (g->life <= 0) {
        func_001F59D0(idA, 0);
        func_001F59D0(idB, 0);
        return 8;
    }
    return 0;
}
