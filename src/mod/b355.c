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

static void func_01E00080_b355(s32 ot, Obj_b058_01E00080 *o, Spr_b058_01E00080 *s) {
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

static void func_01E00260_b355(Pk_b008_01E00080 *p, Rect_b008_01E00080 *r, s32 mode) {
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

typedef struct Rect_b003_01E00080 {
    s16 x, y, w, h;
} Rect_b003_01E00080;
typedef struct Uv_b003_01E00080 {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
    u64 xyz;
} Uv_b003_01E00080;
typedef struct Pk_b003_01E00080 {
    u8 pad0[0x18];
    Uv_b003_01E00080 c[4];
} Pk_b003_01E00080;

/* shape b003:01E00EA0, 342 insns, 15 copies: draws obj->count sprites along a curve read from three s8 tables
   (0x64 apart), each turned by the object's angles; mode (flags & 0xF) 0 = depth from the projection,
   1 = far z, 2 = -1. Calls the module's sprite-UV helper (shape b003:01E00080) as a static function. */

typedef struct {
    u8 pad0[0x20];
    Vec4f pos;
    u8 pad30[0x50];
    s32 f80;
    u8 pad84[4];
    void *f88;
    u8 pad8C[8];
    u8 f94[0x24];
    s16 count;
    u8 padBA[6];
    s16 fC0;
    u8 padC2[0x16];
    u8 fD8[4];
} Obj_b003_01E00EA0;

typedef struct {
    u8 pad0[8];
    s16 tab;
    u8 padA[0x1E];
    u8 tex[8];
    s16 scale;
    u8 pad32[6];
    s16 size;
    s16 angle;
} Def_b003_01E00EA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 fog : 8;
    u64 reg;
} Xyz_b003_01E00EA0;

typedef struct {
    f32 u, v;
} Uv_b003_01E00EA0;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Uv_b003_01E00EA0 uv;
    u64 pad18;
    Xyz_b003_01E00EA0 v[4];
    u64 pad60[6];
} Pk_b003_01E00EA0;

typedef struct {
    u64 tag;
    Pk_b003_01E00EA0 pk;
} Buf_b003_01E00EA0;

static void func_01E006B0_b355(Obj_b003_01E00EA0 *obj, Def_b003_01E00EA0 *def, s32 flags, s8 *base) {
    f32 m2[4][4];
    f32 d[4];
    Vec4f pos;
    Vec4f s;
    f32 out[4];
    f32 m[4][4];
    s32 rot[4];
    s32 rot2[4];
    Buf_b003_01E00EA0 buf;
    Uv_b003_01E00EA0 uv;
    s16 sel;
    s16 i;
    Pk_b003_01E00EA0 *p;
    s32 mode;
    s32 h;
    s8 *t;
    f32 f;
    f32 r;
    extern void func_00108EF0();
    extern void func_00108950();
    extern void func_00109100();

    func_00207500();
    p = &buf.pk;
    p->flags = 0x24;
    p->size = 9;
    p->regs = ((u64)4 << 32) | 0x24242421;
    p->pad4 = 0;
    p->flags |= 0x800;
    sel = flags >> 4;
    if (sel == 0) {
        func_002086D0(p, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(p, ((s64)sel << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107740(&uv, def->tex);
    p->uv = uv;
    func_00208700(p, obj->f88, 1);
    s.x = 0.1f;
    s.y = 0.1f;
    s.z = 0.1f;
    func_00205C40((s32)rot);
    rot[1] /= 180;
    rot[1] = -rot[1];
    rot[0] /= 180;
    rot[0] = -rot[0];
    rot2[2] = def->angle;
    pos.x = obj->pos.x;
    pos.y = obj->pos.y;
    pos.z = obj->pos.z;
    func_00108EF0(m, &s, NULL, &pos);
    mode = flags & 0xF;
    for (i = 0; i < obj->count; i++) {
        func_01E00260_b355((Pk_b003_01E00080 *)p, (Rect_b003_01E00080 *)obj->f94, obj->fC0);
        r = def->size;
        func_00108CE0(m2, r, r);
        func_00109100(m2, rot, 1, obj->fD8);
        func_00109100(m2, rot, 0, obj->fD8);
        t = base + i;
        h = i >> 1;
        f = t[def->tab];
        f /= 20.0f;
        d[0] = f * (def->scale + h);
        f = t[def->tab + 100];
        f /= 20.0f;
        d[1] = f * (def->scale + h);
        func_00108950(d, rot2, 2, obj->fD8);
        m2[0][0] += d[0];
        m2[1][0] += d[0];
        m2[2][0] += d[0];
        m2[3][0] += d[0];
        m2[0][1] += d[1];
        m2[1][1] += d[1];
        m2[2][1] += d[1];
        m2[3][1] += d[1];
        f = t[def->tab + 180];
        f /= 20.0f;
        d[2] = f * (def->scale + h);
        m2[0][2] += d[2];
        m2[1][2] += d[2];
        m2[2][2] += d[2];
        m2[3][2] += d[2];
        if (mode == 0) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, func_001A23B0(out[0]));
            }
        } else if (mode == 1) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                p->v[0].z = p->v[1].z = p->v[2].z = p->v[3].z = 0xFFFFFF;
                func_002075F0((s32)p, obj->f80, 0);
            }
        } else if (mode == 2) {
            if (func_00205630((s32)m2, 0x70000000, (s32)m, (s32)p, out) != 0) {
                func_002075F0((s32)p, obj->f80, -1);
            }
        }
    }
}

/* OVL_WARM */

/* shape b064:01E00C10, 200 insns: variant of b027:01E02590 (ring of quads around a point): two colour sets,
   ring width from the anim (s16 at 6) instead of 20, 18 segments 20 apart */

typedef struct {
    f32 x, y, z, w;
} Vec_b064_01E00C10;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[0x10];
    s16 radius;
    s16 start;
} Anim_b064_01E00C10;

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
} Obj_b064_01E00C10;

static void func_01E00C10_b355(Obj_b064_01E00C10 *o, Anim_b064_01E00C10 *an, void *p) {
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108500(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Vec_b064_01E00C10 quad[4];
    Vec_b064_01E00C10 pos;
    Vec_b064_01E00C10 scale;
    f32 m[16];
    f32 depth __attribute__((aligned(16)));
    s32 k;
    s32 n;
    s32 a;
    s16 j;

    j = 0;
    func_00109270(p, 0, 0);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col + 4, 2);
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
    for (k = 0; k < 18; k++) {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 20);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        if (func_00205630(quad, 0x70000000, m, p, &depth) != 0) {
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)depth);
            }
        }
        j += 20;
    }
}

/* shape b355:01E00F30, 550 insns: B355_W_S, the effect scene's step: colour 0x80,0,0,0, counts the frame (0x5210),
   follows joint 0x51FC; every 6th frame of 53..229 the point drops 30 under it (0x1E01E70 after 130), every 3rd of
   43..234 after 130 0x1E02200 + 0x1E02440; a trail of up to 15 points (0x4F10, angles 0x521A) grows by 3 every 14th
   frame and sinks by 2.7 x the camera-heading cosine, spawning 0x1E01D60 above -300; 0x1E01BF0 at level 31 on;
   frame 50 0x1E02F00; frames 110.. 0x1E02660 / 0x1E02C30 / 0x1E028E0 on the camera, 55..125 0x1E02A80 on the mark */

typedef struct {
    u8 pad0[0x250];
    Vec4f pos;
    u8 pad260[0x4F10 - 0x260];
    Vec4f pts[(0x5190 - 0x4F10) / 0x10];
    Vec4f mark;
    u8 pad51A0[0x51C0 - 0x51A0];
    s32 level;
    u8 col[4];
    u8 pad51C8[0x51FC - 0x51C8];
    s16 j;
    u8 pad51FE[0x5206 - 0x51FE];
    s16 spin;
    u8 pad5208[4];
    s16 f520C;
    u8 pad520E[2];
    s16 t;
    s16 ang;
    s16 flag;
    u8 pad5216[2];
    s16 n;
    s16 arr[20];
    u8 pad5242[0x5344 - 0x5242];
    u8 trig[1];
} Scene_b355_01E00F30;

static void func_01E00F30_b355(Scene_b355_01E00F30 *g) {
    extern void b355_01E01BF0(void);
    extern void b355_01E01D60(void);
    extern void b355_01E01E70(void);
    extern void b355_01E02200(void);
    extern void b355_01E02440(void);
    extern void b355_01E02660(void);
    extern void b355_01E028E0(void);
    extern void b355_01E02A80(void);
    extern void b355_01E02C30(void);
    extern void b355_01E02F00(void);
    extern void b355_01E03A20(Scene_b355_01E00F30 *, void (*)(void), s32);
    extern s32 func_001F53A0(void);
    extern s32 func_001F5380(void);
    extern void func_001F5620(s32, s32, void *);
    extern void func_001F5F90(s32, void *);
    extern void func_001F6160(s32, void *);
    extern s32 func_001A22C0(f32);
    Vec4f v;
    s32 w[4];
    s16 i;

    g->col[0] = 0x80;
    g->col[1] = 0;
    g->col[2] = 0;
    g->col[3] = 0;
    g->t++;
    func_001F5620(func_001F53A0(), g->j, &v);
    if (g->t > 52 && g->t < 230 && g->t % 6 == 1) {
        for (i = 0; i < 1; i++) {
            g->spin = func_0019A5C8() % 360;
            g->pos.x = v.x;
            g->pos.y = v.y;
            g->pos.z = v.z;
            g->pos.y = v.y - 30.0f;
            if (g->t > 130) {
                b355_01E03A20(g, b355_01E01E70, 0);
            }
        }
    }
    if (g->t > 42 && g->t < 235 && g->t % 3 == 1 && g->t > 130) {
        b355_01E03A20(g, b355_01E02200, 0);
        b355_01E03A20(g, b355_01E02440, 0);
    }
    if (g->t == 1) {
        g->n = 0;
        g->arr[0] = 0;
        g->arr[1] = 20;
        g->arr[2] = -20;
        g->arr[3] = 0;
        g->arr[4] = 20;
        g->arr[5] = -20;
        g->arr[6] = 0;
        g->arr[7] = 20;
        g->arr[8] = -20;
        g->arr[9] = 0;
        g->arr[10] = 20;
        g->arr[11] = -20;
        g->arr[12] = 0;
        g->arr[13] = 20;
        g->arr[14] = -20;
        g->arr[15] = 0;
        g->arr[16] = 20;
        g->arr[17] = -20;
        g->arr[18] = 0;
        g->arr[19] = 20;
    }
    if (g->t > 32 && g->t % 14 == 1 && g->n < 15) {
        g->n += 3;
    }
    if (g->t % 2 == 1) {
        for (i = 0; i < g->n; i++) {
            g->ang = g->arr[i];
            g->pos.x = v.x + g->pts[i].x;
            g->pos.y = 10.0f + g->pts[0].y;
            g->pos.z = v.z + g->pts[i].z;
            g->f520C = 0;
            if (g->pts[i].z > -300.0f) {
                b355_01E03A20(g, b355_01E01D60, 0);
            }
            func_001F6160(func_001F53A0(), w);
            g->pts[i].z -= 2.7 * func_00108030((s32)g->trig, (s16)func_001A22C0(w[1] / 180.0f) - 180, 1);
        }
    }
    if (g->t > 32 && g->t % 4 == 1 && g->level > 30) {
        for (i = 0; i < 1; i++) {
            g->pos.x = v.x + g->pts[0].x;
            g->pos.y = 10.0f + g->pts[0].y;
            g->pos.z = v.z + g->pts[0].z;
            b355_01E03A20(g, b355_01E01BF0, 0);
        }
        for (i = 0; i < 1; i++) {
            g->pos.x = v.x + g->pts[0].x + 5.0f * g->pts[0].z * func_00108030((s32)g->trig, 20, 0) / 10.0f;
            g->pos.y = 10.0f + g->pts[0].y;
            g->pos.z = v.z + g->pts[0].z;
            b355_01E03A20(g, b355_01E01BF0, 0);
        }
        for (i = 0; i < 1; i++) {
            g->pos.x = v.x + g->pts[0].x + 5.0f * g->pts[0].z * func_00108030((s32)g->trig, -20, 0) / 10.0f;
            g->pos.y = 10.0f + g->pts[0].y;
            g->pos.z = v.z + g->pts[0].z;
            b355_01E03A20(g, b355_01E01BF0, 0);
        }
    }
    if (g->t == 50) {
        b355_01E03A20(g, b355_01E02F00, 0);
    }
    if (g->t >= 110 && g->t < 226) {
        func_001F5F90(func_001F5380(), &v);
        g->pos.x = v.x;
        g->pos.y = 40.0f;
        g->pos.z = v.z;
        if (g->flag != 0) {
            g->pos.z += 5.0f;
        } else {
            g->pos.z -= 5.0f;
        }
        g->f520C = 0;
        b355_01E03A20(g, b355_01E02660, 0);
    }
    if (g->t >= 110 && g->t < 221) {
        func_001F5F90(func_001F5380(), &v);
        g->pos.x = v.x + func_0019A5C8() % 4 - 2.0f;
        g->pos.y = 42.0f;
        g->pos.z = v.z;
        if (g->flag != 0) {
            g->pos.z += 5.0f;
        } else {
            g->pos.z -= 5.0f;
        }
        g->f520C = 0;
        b355_01E03A20(g, b355_01E02C30, 0);
    }
    if (g->t >= 120 && g->t < 231) {
        func_001F5F90(func_001F5380(), &v);
        g->pos.x = v.x;
        g->pos.y = v.y;
        g->pos.z = v.z;
        g->f520C = 0;
        b355_01E03A20(g, b355_01E028E0, 0);
    }
    if (g->t >= 55 && g->t < 126) {
        if (g->t == 55) {
            func_001F5620(func_001F53A0(), g->j, &g->mark);
        }
        v.x = func_0019A5C8() % 6 - 3;
        v.y = func_0019A5C8() % 6 - 3;
        v.x /= 10.0f;
        v.y /= 10.0f;
        g->pos.x = g->mark.x + v.x;
        g->pos.y = g->mark.y + v.y;
        g->pos.z = g->mark.z;
        g->f520C = 0;
        b355_01E03A20(g, b355_01E02A80, 0);
    }
}

/* shape b064:01E017E0, 134 insns, 2 copies: a violet wisp: set up once (random heading, tilt -15..14); fades in to 0x60
   over 10 frames, then out; its size grows every other frame up to 18, its frame every third up to 7; x and z drift 10 along its heading, y 4 by
   its tilt, by a sine/cosine of its two angles (world trig table) */

typedef struct {
    u8 pad0[0x5344];
    u8 trig[1];
} World_b064_01E017E0;

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
} Wisp_b064_01E017E0;

static s32 func_01E017D0_b355(World_b064_01E017E0 *w, Wisp_b064_01E017E0 *o) {
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

/* shape b064:01E01A00, 125 insns: b064:01E01C00 family: a grey puff drifting 13 a frame along a random direction and a tilt of -90..89 (sine table at g+0x5344); fades in by 8 to 0xA0 for 8 ticks, out by 5; f38 grows to 13, kind steps every 5 ticks to 7 */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x1A];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b064_01E01A00;

static s32 func_01E019F0_b355(u8 * g, Spark_b064_01E01A00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x3F, 0x3F, 0x3F);
    if (o->mode == 1) {
        o->f38 = 0;
        o->dir = func_0019A5C8() % 360;
        o->kind = 0;
        o->angle = func_0019A5C8() % 180 - 90;
        o->mode = 2;
    }
    if (o->tick < 8) {
        if (o->col[3] < 0xA0) {
            o->col[3] += 8;
        }
    } else if (o->col[3] > 6) {
        o->col[3] -= 5;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 13) {
        o->f38++;
    }
    if (o->tick % 5 == 1) {
        if (o->kind < 7) {
            o->kind++;
        }
    }
    o->f8 = o->f8 + 13.0f * func_00108030(g + 0x5344, o->dir, 0);
    o->fA = o->fA + 13.0f * func_00108030(g + 0x5344, o->angle, 1);
    o->fC = o->fC + 13.0f * func_00108030(g + 0x5344, o->dir, 1);
    return 0;
}

/* shape b064:01E01C00, 89 insns: a drifting grey puff: colour (0x2F,0x2F,0x2F); on start f38 14, random
   direction, variant and f30 (-15..14); alpha grows by 0x18 (below 0x60) for 4 ticks, then fades out by 23 and
   stops; f38 grows to 20; f8 moves by 20 * func_00108030(game 0x5344, direction, 0) each tick */

typedef struct {
    u8 pad0[6];
    s16 life;
    s16 f8;
    u8 padA[4];
    s16 spin;
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Spark_b064_01E01C00;

static s32 func_01E01BF0_b355(u8 *g, Spark_b064_01E01C00 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    func_001076F0(o->col, 0x2F, 0x2F, 0x2F);
    if (o->mode == 1) {
        o->f38 = 14;
        o->dir = func_0019A5C8() % 360;
        o->kind = func_0019A5C8() % 7;
        o->angle = func_0019A5C8() % 30 - 15;
        o->mode = 2;
    }
    if (o->tick < 4) {
        if (o->col[3] < 0x60) {
            o->col[3] += 0x18;
        }
    } else if (o->col[3] > 0x18) {
        o->col[3] -= 23;
    } else {
        o->mode = 0;
    }
    o->tick++;
    if (o->f38 < 0x14) {
        o->f38++;
    }
    o->f8 = o->f8 + 20.0f * func_00108030(g + 0x5344, o->dir, 0);
    return 0;
}

/* shape b064:01E01D70, 66 insns, 2 copies: a swaying sprite over 18 steps: set up once (colour by stage), then its height
   follows a sine of the step and its x a sine of its own phase scaled by the world's table entry */

typedef struct {
    u8 pad0[0x4F18];
    Vec4f tbl[42];
    u8 pad51B8[8];
    s32 stage;
    u8 pad51C4[0x180];
    u8 trig[1];
} World_b064_01E01D70;

typedef struct {
    u8 pad0[8];
    s16 h8;
    u8 padA[0x1E];
    u8 c0[4];
    u8 pad2C[4];
    s16 idx;
    s16 phase;
    s16 h34;
    s16 state;
    s16 h38;
    s16 step;
} Obj_b064_01E01D70;

static s32 func_01E01D60_b355(World_b064_01E01D70 *w, Obj_b064_01E01D70 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->h38 = 5;
        o->h34 = 0;
        func_0019A5C8();
        func_001076F0(o->c0, 0x18, 0x18, 0x18);
        o->step = 0;
        o->state = 2;
        if (w->stage > 0x19) {
            o->c0[3] = 0x40;
        } else {
            o->c0[3] = 0;
        }
    }
    o->h34 = 300.0f * func_00108030(w->trig, o->step, 0);
    o->h8 = 5.0f * w->tbl[o->idx].x * func_00108030(w->trig, o->phase, 0);
    o->step += 10;
    if (o->step >= 0xB4) {
        o->state = 0;
    }
    return 0;
}

/* shape b064:01E01E80, 101 insns, 2 copies: a bobbing blue wisp, alternating its turn direction with each spawn: from
   stage 18 on it fades in and lingers 50 frames, earlier it fades straight out; bobs on a sine, turns 12 a frame */

typedef struct {
    u8 pad0[0x51C0];
    s32 stage;
    u8 pad51C4[0x46];
    s16 flip;
    u8 pad520C[0x138];
    u8 trig[1];
} World_b064_01E01E80;

typedef struct {
    s16 x, y;
    u8 pad4[0xC];
    s32 rot[3];
    u8 pad1C[0xC];
    u8 c0[4];
    u8 pad2C[4];
    s16 dir;
    s16 t;
    s16 h34;
    s16 state;
    s16 h38;
    s16 ang;
} Wisp_b064_01E01E80;

static s32 func_01E01E70_b355(World_b064_01E01E80 *w, Wisp_b064_01E01E80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern f32 func_00108030(void *, s16, s32);

    if (o->state == 1) {
        o->rot[2] = o->rot[1] = o->rot[0] = 0;
        o->h34 = 1;
        o->h38 = 1;
        o->state = 2;
        o->c0[3] = 0x80;
        o->dir = w->flip;
        if (w->flip == 0) {
            w->flip = 1;
        } else {
            w->flip = 0;
        }
    }
    o->t++;
    if (w->stage > 0x11) {
        if (o->t > 0x32) {
            if (o->c0[3] > 4) {
                o->c0[3] -= 3;
            } else {
                o->state = 0;
            }
        } else if (o->c0[3] < 0x60) {
            o->c0[3] += 0x13;
        }
    } else if (o->c0[3] > 0xA) {
        o->c0[3] -= 9;
    } else {
        o->state = 0;
    }
    o->h38 += 5;
    o->y += 3.0f * func_00108030(w->trig, o->t * 6, 0);
    if (o->dir == 0) {
        o->ang += 12;
    } else {
        o->ang -= 12;
    }
    func_001076F0(o->c0, 0x20, 0x20, 0x68);
    return 0;
}

/* shape b064:01E02020, 121 insns: a swaying wisp: on start x 0x4000, variant 0, f38 1, alpha 0x80, angle = game
   value 0x520A; f4 sways by 9 * -func_00108030(game 0x5344, a - 180, 1) where a = func_001F6160's value / 180;
   fades in or out by the game state 0x51C0 and age; f8 jitters -10..9, f38 grows by 2, the direction turns by 12
   (by -12 when angle is set); colour (0x18,0x18,0x30) */

typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad6[2];
    s16 f8;
    u8 padA[6];
    s32 x;
    s32 y;
    s32 z;
    u8 pad1C[0xC];
    u8 col[4];
    u8 pad2C[4];
    s16 angle;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 dir;
} Wisp_b064_01E02020;

typedef struct {
    u8 pad[0x51C0];
    s32 state;
    u8 pad51C4[0x46];
    s16 v;
} Game_b064_01E02020;

static s32 func_01E02010_b355(Game_b064_01E02020 *g, Wisp_b064_01E02020 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s32, s32);
    s32 buf[4];
    s16 a;

    if (o->mode == 1) {
        o->x = 0x4000;
        o->y = 0;
        o->z = 0;
        o->kind = 0;
        o->f38 = 1;
        o->mode = 2;
        o->col[3] = 0x80;
        o->angle = g->v;
    }
    func_001F6160(func_001F53A0(), buf);
    a = buf[1] / 180.0f;
    o->f4 = o->f4 + 9.0f * -func_00108030((u8 *)g + 0x5344, a - 180, 1);
    o->tick++;
    if (g->state > 0x11) {
        if (o->tick > 0xF) {
            if (o->col[3] > 4) {
                o->col[3] -= 3;
            } else {
                o->mode = 0;
            }
        } else if (o->col[3] < 0x60) {
            o->col[3] += 0x13;
        }
    } else if (o->col[3] > 0xA) {
        o->col[3] -= 9;
    } else {
        o->mode = 0;
    }
    o->f8 = func_0019A5C8() % 20 - 10;
    o->f38 += 2;
    if (o->angle == 0) {
        o->dir += 12;
    } else {
        o->dir -= 12;
    }
    func_001076F0(o->col, 0x18, 0x18, 0x30);
    return 0;
}

/* shape b064:01E02210, 142 insns: b064:01E02020 family: a white mote placed within 30 of point g->v
   (func_001F5620), fading in by 0x25 to 0x70 for 3 ticks, out by 12 after 16 ticks or once the scene state is
   under 17; sinks by 7 * the camera's sine each tick */

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 col[4];
    u8 pad2C[6];
    s16 tick;
    u8 pad34[2];
    s16 mode;
    s16 f38;
} Mote_b064_01E02210;

typedef struct {
    u8 pad[0x51C0];
    s32 state;
    u8 pad51C4[0x38];
    s16 v;
} Game_b064_01E02210;

static s32 func_01E02200_b355(Game_b064_01E02210 *g, Mote_b064_01E02210 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F53A0(void);
    extern void func_001F5620(s32, s32, f32 *);
    extern void func_001F6160(s32, s32 *);
    extern f32 func_00108030(void *, s32, s32);
    f32 p[4];
    s32 buf[4];
    s16 a;

    func_001076F0(o->col, 0x80, 0x80, 0x80);
    if (o->mode == 1) {
        func_001F5620(func_001F53A0(), g->v, p);
        o->x = p[0] + func_0019A5C8() % 60 - 30.0f;
        o->y = p[1] + func_0019A5C8() % 60 - 30.0f;
        o->z = p[2] + func_0019A5C8() % 60 - 30.0f;
        o->f38 = 1;
        o->mode = 2;
    }
    if (o->tick < 3) {
        if (o->col[3] < 0x70) {
            o->col[3] += 0x25;
        }
    }
    if (o->tick > 16) {
        if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
    }
    if (g->state < 17) {
        if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->mode = 0;
        }
    }
    func_001F6160(func_001F53A0(), buf);
    a = buf[1] / 180.0f;
    o->z = o->z - 7.0f * func_00108030((u8 *)g + 0x5344, a - 180, 1);
    o->tick++;
    return 0;
}

/* shape b064:01E02450, 135 insns, 2 copies: a grey wisp born near the model's joint (jittered 30/20/30), random heading,
   frame and tilt; fades in over 3 frames, then out (faster when the stage is below 17); its size grows to 20 */

typedef struct {
    u8 pad0[0x51C0];
    s32 stage;
} World_b064_01E02450;

typedef struct {
    s16 x, y, z;
    u8 pad6[0x22];
    u8 c0[4];
    u8 pad2C[4];
    s16 a30;
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
    s16 a3A;
} Wisp_b064_01E02450;

static s32 func_01E02440_b355(World_b064_01E02450 *w, Wisp_b064_01E02450 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern void func_001F5F90(s32, void *);
    Vec4f v;

    func_001076F0(o->c0, 0x10, 0x10, 0x10);
    if (o->state == 1) {
        func_001F5F90(func_001F5380(), &v);
        o->x = v.x + func_0019A5C8() % 30 - 15.0f;
        o->y = v.y + func_0019A5C8() % 20 - 10.0f;
        o->z = v.z + func_0019A5C8() % 30 - 15.0f;
        o->size = 0xE;
        o->a3A = func_0019A5C8() % 360;
        o->frame = func_0019A5C8() % 7;
        o->a30 = func_0019A5C8() % 30 - 15;
        o->state = 2;
    }
    if (o->t < 3) {
        if (o->c0[3] < 0x60) {
            o->c0[3] += 0x20;
        }
    } else if (o->c0[3] > 0x18) {
        o->c0[3] -= 0x17;
    } else {
        o->state = 0;
    }
    if (w->stage < 0x11) {
        if (o->c0[3] > 0xD) {
            o->c0[3] -= 0xC;
        } else {
            o->state = 0;
        }
    }
    o->t++;
    if (o->size < 0x14) {
        o->size++;
    }
    return 0;
}

/* shape b064:01E02670, 160 insns, 2 copies: a grey ember tied to the model: size from the model's scale (capped at 26) or
   random when it already had an angle; fades in for its life, then out (faster before stage 35); grows 1 a
   frame, its frame climbs every other frame to 5, turns by its speed and sinks or rises by the scene flag */

typedef struct {
    u8 pad0[0x51C0];
    s32 stage;
    u8 pad51C4[0x50];
    s16 sink;
} World_b064_01E02670;

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 speed;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
} Ember_b064_01E02670;

static s32 func_01E02660_b355(World_b064_01E02670 *w, Ember_b064_01E02670 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern f32 func_001F5860(s32);

    if (o->state == 1) {
        if (o->ang != 0) {
            o->size = func_0019A5C8() % 22 + 12;
        } else {
            o->size = 2.0f + func_001F5860(func_001F5380());
            if (o->size > 0x1A) {
                o->size = 0x1A;
            }
        }
        o->frame = 0;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->hA = o->ang;
        o->ang = func_0019A5C8() % 30 + 60;
        o->speed = func_0019A5C8() % 5 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 5 + 2;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (w->stage < 0x23) {
        if (o->c0[3] > 0xD) {
            o->c0[3] -= 0xC;
        } else {
            o->state = 0;
        }
    }
    if (o->t != 0) {
        o->size++;
    }
    if (o->t % 2 == 1) {
        if (o->frame < 5) {
            o->frame++;
        }
    }
    if (o->t != 0) {
        o->ang += o->speed;
    }
    if (o->t != 0) {
        if (w->sink != 0) {
            o->z--;
        } else {
            o->z++;
        }
    }
    o->t++;
    return 0;
}

/* shape b355:01E028E0, 104 insns: b064:01E028F0 twin: a blinking blue spark (size growing a random 4..6 a tick, frame 0..6, turn 0x4000): in by 32 up to 0x40 for 2 ticks; past size 40 out by 19, and out by 15 once the scene state is under 10; ends */

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 h8;
    u8 padA[6];
    s32 w10;
    s32 w14;
    u8 pad18[0x10];
    u8 col[4];
    u8 col2[4];
    s16 h30;
    s16 tick;
    s16 kind;
    s16 mode;
    s16 f38;
    s16 ang;
} Glow_b355_01E028E0;

typedef struct {
    u8 pad[0x51C0];
    s32 state;
} Game_b355_01E028E0;

static s32 func_01E028E0_b355(Game_b355_01E028E0 *g, Glow_b355_01E028E0 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->mode == 1) {
        o->f38 = 0;
        o->w10 = 0x4000;
        o->w14 = 0;
        o->kind = func_0019A5C8() % 7;
        o->mode = 2;
        o->h8 = func_0019A5C8() % 3 + 4;
        o->h6 = 6;
        func_001076F0(o->col2, 0x80, 0x80, 0x80);
    }
    if (o->tick < 2) {
        if (o->col[3] < 0x40) {
            o->col[3] += 0x20;
        }
    } else {
        if (o->f38 > 40) {
            if (o->col[3] > 0x14) {
                o->col[3] -= 0x13;
            } else {
                o->mode = 0;
            }
        }
        if (g->state < 10) {
            if (o->col[3] > 0x10) {
                o->col[3] -= 15;
            } else {
                o->mode = 0;
            }
        }
    }
    if (o->tick % 2 == 1) {
        func_001076F0(o->col, 0x30, 0x30, 0xF0);
    } else {
        func_001076F0(o->col, 0x20, 0x20, 0xC0);
    }
    o->tick++;
    o->f38 += o->h8;
    return 0;
}

/* shape b355:01E02A80, 108 insns: a blue flickering streak (b476:01E03090 shape): frame 5 growing by 1, a quarter tilt, random
   turn and sub-frame 0..6; alpha up by 40 to 0x50 for 2 frames, then down by 19 past 30 and by 15 when the timer drops under 10 */

typedef struct {
    u8 pad0[0x51C0];
    s32 timer;
} Scene_b355_01E02A80;

typedef struct {
    u8 pad0[6];
    s16 h6;
    s16 grow;
    u8 padA[6];
    s32 rot0;
    s32 rot1;
    u8 pad18[0x10];
    u8 c0[4];
    u8 c1[4];
    u8 pad30[2];
    s16 t;
    s16 sub;
    s16 state;
    s16 h38;
} Obj_b355_01E02A80;

static s32 func_01E02A80_b355(Scene_b355_01E02A80 *g, Obj_b355_01E02A80 *o) {
    extern void func_001076F0(void *, s32, s32, s32);

    if (o->state == 1) {
        o->h38 = 5;
        o->rot0 = 0x4000;
        o->rot1 = func_0019A5C8() % 65535;
        o->sub = func_0019A5C8() % 7;
        o->state = 2;
        o->grow = 1;
        o->h6 = -3;
        func_001076F0(o->c1, 8, 8, 0x80);
    }
    if (o->t < 2) {
        if (o->c0[3] < 0x50) {
            o->c0[3] += 0x28;
        }
    } else {
        if (o->h38 > 0x1E) {
            if (o->c0[3] > 0x14) {
                o->c0[3] -= 0x13;
            } else {
                o->state = 0;
            }
        }
        if (g->timer < 0xA) {
            if (o->c0[3] > 0x10) {
                o->c0[3] -= 0xF;
            } else {
                o->state = 0;
            }
        }
    }
    if (o->t % 2 == 1) {
        func_001076F0(o->c0, 0x10, 0x10, 0x80);
    } else {
        func_001076F0(o->c0, 0x20, 0x20, 0x50);
    }
    if (o->t != 0) {
        o->h38 += o->grow;
    }
    o->t++;
    return 0;
}

/* shape b064:01E02C40, 180 insns: b064:01E02670 family: a grey ember, size from the model (capped 26) or random; fades in for 1..2 ticks, out by 11 (by 12 once the scene counter reaches 221); grows to 30, turns 2 and steps its frame 0..5 every other tick, sinks or rises by the scene flag */

typedef struct {
    u8 pad0[0x5210];
    s16 count;
    u8 pad5212[2];
    s16 sink;
} World_b064_01E02C40;

typedef struct {
    s16 x, y, z;
    s16 life;
    s16 h8;
    s16 hA;
    u8 padC[2];
    s16 speed;
    u8 pad10[0x18];
    u8 c0[4];
    u8 pad2C[4];
    s16 ang;
    s16 t;
    s16 frame;
    s16 state;
    s16 size;
} Ember_b064_01E02C40;

static s32 func_01E02C30_b355(World_b064_01E02C40 *w, Ember_b064_01E02C40 *o) {
    extern void func_001076F0(void *, s32, s32, s32);
    extern s32 func_001F5380(void);
    extern f32 func_001F5860(s32);

    if (o->state == 1) {
        if (o->ang != 0) {
            o->size = func_0019A5C8() % 22 + 12;
        } else {
            o->size = 2.0f + func_001F5860(func_001F5380());
            if (o->size > 0x1A) {
                o->size = 0x1A;
            }
        }
        o->frame = 0;
        func_001076F0(o->c0, 0x40, 0x40, 0x40);
        o->hA = o->ang;
        o->ang = func_0019A5C8() % 60 + 10;
        o->speed = func_0019A5C8() % 5 + 10;
        o->h8 = func_0019A5C8() % 35;
        o->life = func_0019A5C8() % 2 + 1;
        o->state = 2;
    }
    if (o->t < o->life) {
        if (o->c0[3] <= 0x80) {
            o->c0[3] += 0x40;
        }
    } else if (o->c0[3] > 0xC) {
        o->c0[3] -= 0xB;
    } else {
        o->state = 0;
    }
    if (w->count > 220) {
        if (o->c0[3] > 0xD) {
            o->c0[3] -= 0xC;
        } else {
            o->state = 0;
        }
    }
    if (o->t != 0) {
        if (o->size < 30) {
            o->size++;
        }
    }
    if (o->t % 2 == 1) {
        o->ang += 2;
    }
    if (o->t % 2 == 1) {
        if (o->frame < 5) {
            o->frame++;
        } else {
            o->frame = 0;
        }
    }
    if (o->t != 0) {
        if ((s16)o->t % 2 == 1) {
            if (w->sink != 0) {
                o->z--;
            } else {
                o->z++;
            }
        }
    }
    o->t++;
    return 0;
}

typedef struct {
    u8 r, g, b, a;
    f32 q;
} Col_b355_01E02F00;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b355_01E02F00;

typedef struct {
    f32 s, t;
    Xyz_b355_01E02F00 p;
} Vtx_b355_01E02F00;

typedef struct {
    s16 tag;
    u16 count;
    s32 pad;
    u64 regs;
    Col_b355_01E02F00 c;
    Vtx_b355_01E02F00 v[2];
    u8 tail[0x20];
} Pkt_b355_01E02F00;

typedef struct {
    u8 pad0000[0x51C0];
    s32 w51C0;
} Mgr_b355_01E02F00;

typedef struct {
    u8 pad00[0x28];
    u8 col[4];
    u8 pad2C[6];
    s16 h32;
    u8 pad34[2];
    s16 h36;
} Obj_b355_01E02F00;

static inline void tag_b355_01E02F00(Pkt_b355_01E02F00 *p, s32 count, s32 tag, u64 regs) {
    p->count = count;
    p->tag = tag;
    p->regs = regs;
    p->pad = 0;
}

static s32 func_01E02F00_b355(Mgr_b355_01E02F00 *m, Obj_b355_01E02F00 *o) {
    extern void func_002087A0(void *, s32);
    extern s32 func_00207500(void);
    extern void func_002075F0(void *, s32, s32);
    Pkt_b355_01E02F00 pkt __attribute__((aligned(8)));

    tag_b355_01E02F00((Pkt_b355_01E02F00 *)(u32)&pkt, 0x26, 5, 0x42421);
    pkt.c.r = 0x80;
    pkt.c.g = 0x80;
    pkt.c.b = 0xA0;
    pkt.c.a = o->col[3];
    pkt.c.q = 1.0f;
    pkt.v[0].p.x = 0x6BF8;
    pkt.v[0].p.y = 0x71F8;
    pkt.v[0].p.z = 0xFFFFFF;
    pkt.v[0].p.f = 0;
    pkt.v[1].p.x = 0x93F8;
    pkt.v[1].p.y = 0x8DF8;
    pkt.v[1].p.z = 0xFFFFFF;
    pkt.v[1].p.f = 0;
    pkt.v[0].s = 0.001953125f;
    pkt.v[0].t = 0.00390625f;
    pkt.v[1].s = 0.623046875f;
    pkt.v[1].t = 0.87109375f;
    func_002086D0(&pkt, ((u64)0x80 << 32) | 0x44);
    func_002087A0(&pkt, 1);
    func_002075F0(&pkt, func_00207500(), 0);
    if (o->h32 < 8) {
        if (o->col[3] < 0x60) {
            o->col[3] += 12;
        }
    }
    if (m->w51C0 < 17) {
        if (o->col[3] > 13) {
            o->col[3] -= 12;
        } else {
            o->h36 = 0;
        }
    }
    o->h32++;
    if (m->w51C0 == 9) {
        o->h36 = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mod/b355", func_01E030D0_b355);

/* shape b064:01E03A20, 74 insns: twin of b046:01E03E20: take the first free slot of the 300-slot pool, clear it,
   give it the scene's colour twice, the scene matrix, the scene's values 0x520C and 0x5212 and the two arguments;
   returns 1 if a slot was found */

typedef struct {
    u8 pad[0x20];
    s32 b;
    s32 a;
    u8 c0[4];
    u8 c1[4];
    s16 v;
    s16 v2;
    u8 pad34[2];
    s16 used;
    u8 pad38[8];
} Slot_b064_01E03A20;

typedef struct {
    u8 pad[0x250];
    u8 m[0x50];
    Slot_b064_01E03A20 s[300];
    u8 pad4DA0[0x424];
    u8 r, g, b, a;
    u8 pad51C8[0x44];
    s16 v;
    u8 pad520E[4];
    s16 v2;
} Pool_b064_01E03A20;

static s32 func_01E03A20_b355(Pool_b064_01E03A20 *o, s32 a, s32 b) {
    extern void func_00195108(void *, s32);
    extern void func_001076F0(void *, u8, u8, u8);
    extern void func_00106AB0(void *, void *, s32);
    Slot_b064_01E03A20 *s = NULL;
    s16 i;
    s32 ret;

    for (i = 0; i < 300; i++) {
        if (o->s[i].used == 0) {
            func_00195108(&o->s[i], 0x40);
            o->s[i].used = 1;
            s = &o->s[i];
            i = 300;
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
        s->v2 = o->v2;
        s->b = b;
        s->a = a;
    } else {
        ret = 0;
    }
    return ret;
}

/* shape b064:01E03B50, 137 insns, 2 copies: one textured upright strip of an object (b053:01E022F0 family, texture 0x99 frame
   2); mode 0 only sets up the packet's texture, otherwise position = pos + vel / 10, yawed a quarter turn (a bit
   less when `!o->kind % 3`, which parses as (!o->kind) % 3), height a tenth of its value, drawn via
   func_00108F90. */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[0x1A];
    u8 col[8];
    s16 kind;
    u8 pad32[2];
    s16 page;
    u8 pad36[2];
    s16 size;
} Obj_b064_01E03B50;

static void func_01E03B50_b355(u8 *ctx, Obj_b064_01E03B50 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern void func_00105D00(void *, s32, s32);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    s32 rot[4];
    u8 *ot;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x99, 0, td);
        func_00105D00(td, 2, 0);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x29C), 1);
        return;
    }
    func_00205C40((s32)rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    if (!o->kind % 3) {
        rot[1] = 0x3A00;
    } else {
        rot[1] = 0x4000;
    }
    rot[0] = 0;
    rot[2] = 0;
    func_00108EF0(m, NULL, rot, &pos);
    func_00108CE0(quad, o->size, o->page / 10);
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    func_00108F90(quad, pkt, m, ot);
}

/* shape b064:01E03D80, 103 insns: b053:01E022F0 family (one textured camera-facing square; texture 0x14, page at ctx+0x268) */

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
} Obj_b064_01E03D80;

static void func_01E03D80_b355(u8 *ctx, Obj_b064_01E03D80 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    Vec4f rot;
    u8 *ot;
    f32 size;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x268), 1);
        return;
    }
    func_00205C40((s32)&rot);
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, &rot, &pos);
    size = o->size;
    func_00108CE0(quad, size, size);
    func_00108F90(quad, pkt, m, ot);
}

/* shape b064:01E03F20, 222 insns: mode 0 sets up the packet's texture (0x96, page o->page), otherwise an 18-sector
   ring of outer radius o->size around pos + vel / 10; the hole is 50 for the b064:01E01E80 object and 10 for the
   b064:01E02020 one, else none */

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[4];
    s32 func;
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b064_01E03F20;

static void func_01E03F20_b355(u8 *ctx, Obj_b064_01E03F20 *o, void *pkt, s32 mode) {
    extern s32 b355_01E01E70();
    extern s32 b355_01E02010();
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    u8 td[0x10];
    f32 inner;
    s32 i;
    s16 a;
    s16 k;

    inner = 0.0f;
    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x96, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x29C), 1);
        return;
    }
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    if (o->func == (s32)b355_01E01E70) {
        inner = 50.0f;
    }
    if (o->func == (s32)b355_01E02010) {
        inner = 10.0f;
    }
    for (i = 0; i < 18; i++) {
        k = o->ang + a;
        q[2].x = o->size * func_00108030(ctx + 0x5344, k, 1);
        q[2].z = o->size * func_00108030(ctx + 0x5344, k, 0);
        q[0].x = (o->size - inner) * func_00108030(ctx + 0x5344, k, 1);
        q[0].z = (o->size - inner) * func_00108030(ctx + 0x5344, k, 0);
        k = o->ang + 20 + a;
        q[3].x = o->size * func_00108030(ctx + 0x5344, k, 1);
        q[3].z = o->size * func_00108030(ctx + 0x5344, k, 0);
        q[1].x = (o->size - inner) * func_00108030(ctx + 0x5344, k, 1);
        q[1].z = (o->size - inner) * func_00108030(ctx + 0x5344, k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x51EC)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x51CC), (u32)*(f32 *)(ctx + 0x51EC));
        }
        a += 20;
    }
}

typedef struct {
    s16 x, y, z;
    u8 pad6[2];
    s16 vx, vy, vz;
    u8 padE[2];
    s32 rot[4];
    u8 pad20[8];
    u8 col[4];
    u8 pad2C[0xC];
    s16 size;
    s16 ang;
} Obj_b064_01E042A0;

typedef struct {
    u8 c[4];
} Col_b064_01E042A0;

static void func_01E042A0_b355(u8 *ctx, Obj_b064_01E042A0 *o, void *pkt, s32 mode) {
    extern Col_b064_01E042A0 D_01E04880_b355;
    extern void func_00106080(void *, s32, s32, void *);
    extern void func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205630(s32, s32, s32, s32, f32 *);
    extern void func_002075F0(s32, s32, s32);
    Vec4f q[4];
    Vec4f pos;
    f32 m[16];
    u8 td[0x10];
    Col_b064_01E042A0 col;
    s32 i;
    s16 a;
    s16 k;

    a = 0;
    col = D_01E04880_b355;
    if (mode == 0) {
        func_00106080(td, 0x9B, 3, td);
        func_00109270(pkt, 0, 0);
        col.c[3] = o->col[3];
        func_00107790(pkt, &col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x29C), 1);
        return;
    }
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, o->rot, &pos);
    q[0].y = 40.0f;
    q[1].y = 40.0f;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    for (i = 0; i < 9; i++) {
        k = o->ang + a;
        q[2].x = (o->size - 5) * func_00108030(ctx + 0x5344, k, 1);
        q[2].z = (o->size - 5) * func_00108030(ctx + 0x5344, k, 0);
        q[0].x = (o->size - 12.0f - 5.0f) * func_00108030(ctx + 0x5344, k, 1);
        q[0].z = (o->size - 12.0f - 5.0f) * func_00108030(ctx + 0x5344, k, 0);
        k = o->ang + 40 + a;
        q[3].x = (o->size - 5) * func_00108030(ctx + 0x5344, k, 1);
        q[3].z = (o->size - 5) * func_00108030(ctx + 0x5344, k, 0);
        q[1].x = (o->size - 12.0f - 5.0f) * func_00108030(ctx + 0x5344, k, 1);
        q[1].z = (o->size - 12.0f - 5.0f) * func_00108030(ctx + 0x5344, k, 0);
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x51EC)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x51CC), (u32)*(f32 *)(ctx + 0x51EC));
        }
        a += 40;
    }
}

/* shape b064:01E04650, 109 insns, 2 copies: one textured strip of an object (b053:01E022F0 family: turned a quarter, ten
   times wider than tall); mode 0 only sets up the packet's texture, otherwise position = pos + vel / 10, drawn
   via func_00108F90. */

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
} Obj_b064_01E04650;

static void func_01E04650_b355(u8 *ctx, Obj_b064_01E04650 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00108CE0(void *, f32, f32);
    extern void func_00108F90(void *, void *, void *, void *);
    Vec4f quad[4];
    Vec4f pos;
    u8 td[0x10];
    f32 m[16];
    s32 rot[4];
    u8 *ot;

    ot = func_00207500();
    if (mode == 0) {
        func_00106080(td, 0x14, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x268), 1);
        return;
    }
    func_00205C40((s32)rot);
    rot[1] = 0x4000;
    pos.x = o->x + o->vx / 10;
    pos.y = o->y + o->vy / 10;
    pos.z = o->z + o->vz / 10;
    func_00108EF0(m, NULL, rot, &pos);
    func_00108CE0(quad, o->size * 10, o->size);
    func_00108F90(quad, pkt, m, ot);
}
