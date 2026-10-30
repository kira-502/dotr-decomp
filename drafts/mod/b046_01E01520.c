#include "common.h"

/* shape b046:01E01520 (IWScatteredCircle4), 335 insns, 6 copies: a textured ring of 36 quads (10
   apart) around the anim point, inner radius 0x38, width 6; each quad projected corner by corner, STQ from a 64-wide
   strip of the texture rect, drawn count+1 times at the mean depth */

/* draft, 316/335: only the STQ block differs. The original computes t0 / 256 twice (v[0].t and v[1].t) and keeps t1 / 256
   in a copy (mov.s); this C shares t0 / 256 once. opt_propagation off is needed so 0/64/256 are not folded. */

typedef struct {
    u16 x, y;
    u8 z[3];
    u8 adc;
} Xyz_b046_01E01520;

typedef struct {
    u8 rgba[4];
    f32 q;
    f32 s, t;
    Xyz_b046_01E01520 xyz;
} Vtx_b046_01E01520;

typedef struct {
    u16 size;
    u16 flags;
    s32 pad4;
    u64 regs;
    Vtx_b046_01E01520 v[4];
} Pk_b046_01E01520;

typedef struct {
    s16 x, y, z;
    s16 w;
    u8 pad08[8];
    u8 rot[0x18];
    u8 col[4];
    u8 col2[0xC];
    s16 radius;
    s16 start;
} Anim_b046_01E01520;

typedef struct {
    u8 pad00[0x80];
    s32 target;
    u8 pad84[4];
    s32 texture;
    u8 pad8C[8];
    s16 u, v, w, h;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 bD8[1];
} Obj_b046_01E01520;

#pragma opt_propagation off
static void func_01E01520_b046(Obj_b046_01E01520 *o, Anim_b046_01E01520 *an, Pk_b046_01E01520 *p) {
    extern void func_00107790(void *, void *, s32);
    extern void func_00208700(void *, s32, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00208CB0(void *, u64);
    extern void func_002075F0(void *, s32, s32);
    Vec4f quad[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    f32 depth[4];
    s32 k;
    s32 n;
    s32 a;
    s16 j;
    f32 t0;
    f32 t1;
    f32 u0;
    f32 u1;
    f32 w;
    f32 sb;

    p->flags = 0x34;
    p->size = 0xC;
    p->regs = ((u64)0x4214 << 32) | 0x21421421;
    p->pad4 = 0;
    j = 0;
    func_002086D0(p, ((u64)0x80 << 32) | 0x48);
    func_00107790(p, an->col, 1);
    func_00107790(p, an->col2, 2);
    func_00208700(p, o->texture, 1);
    pos.x = an->x;
    pos.y = an->y;
    pos.z = an->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    t0 = o->v;
    t1 = o->v + o->h;
    func_00108EF0(m, &scale, an->rot, &pos);
    quad[0].y = 0.0f;
    quad[1].y = 0.0f;
    quad[2].y = 0.0f;
    quad[3].y = 0.0f;
    k = 0;
    do {
        a = an->start + j;
        quad[2].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[2].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[0].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[0].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        a = j + (an->start + 10);
        quad[3].x = an->radius * func_00108030(o->bD8, a, 1);
        quad[3].z = an->radius * func_00108030(o->bD8, a, 0);
        quad[1].x = (an->radius + an->w) * func_00108030(o->bD8, a, 1);
        quad[1].z = (an->radius + an->w) * func_00108030(o->bD8, a, 0);
        if (func_00205440(&quad[0], m, &p->v[0].xyz, &depth[0]) != 0 &&
            func_00205440(&quad[1], m, &p->v[1].xyz, &depth[1]) != 0 &&
            func_00205440(&quad[2], m, &p->v[2].xyz, &depth[2]) != 0 &&
            func_00205440(&quad[3], m, &p->v[3].xyz, &depth[3]) != 0) {
            p->v[3].xyz.adc = 0;
            p->v[2].xyz.adc = 0;
            p->v[1].xyz.adc = 0;
            p->v[0].xyz.adc = 0;
            p->v[0].q = 1.0f / depth[0];
            p->v[1].q = 1.0f / depth[1];
            p->v[2].q = 1.0f / depth[2];
            p->v[3].q = 1.0f / depth[3];
            func_00208CB0(p, (u64)0xFB | ((u64)o->u << 14) | ((u64)o->v << 24) | ((u64)(o->v + o->h - 1) << 34));
            w = 256.0f;
            u0 = 0.0f;
            u1 = 64.0f;
            p->v[0].s = u0 / depth[0];
            p->v[0].t = t0 / w / depth[0];
            p->v[1].s = u1 / w / depth[1];
            p->v[1].t = t0 / w / depth[1];
            p->v[2].s = u0 / w / depth[2];
            p->v[2].t = (sb = t1 / w) / depth[2];
            p->v[3].s = u1 / w / depth[3];
            p->v[3].t = sb / depth[3];
            for (n = 0; n < o->count + 1; n++) {
                func_002075F0(p, o->target, (u32)((depth[0] + depth[1] + depth[2] + depth[3]) / 4.0f));
            }
        }
        j += 10;
        k++;
    } while (k < 36);
}
#pragma opt_propagation reset
