#include "common.h"

/* shape b193:01E01D70, 325 insns: a 36-sector textured ring (inner radius fx->r, outer fx->r + fx->dr, the outer edge
   raised by fx->h) at the object, each sector a 64-texel-wide strip of the object's texture page, drawn count + 1
   times at its average depth */

/* draft, 306/325: b046:01E01520's form (opt_propagation off so 0/64/256 stay unfolded, do-while ring loop,
   `a = 0;` first so the pad store fills the bnez delay slot). Only the STQ block differs, exactly as in b046: the
   original divides v0 / 256 twice and keeps v1 / 256 in a mov.s copy; MWCC shares v0 / 256. */

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b193_01E01D70;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    f32 s, t;
    Xyz_b193_01E01D70 xyz;
} Vtx_b193_01E01D70;

typedef struct {
    s16 size;
    s16 flags;
    s32 pad;
    u64 regs;
    Vtx_b193_01E01D70 v[4];
} Pkt_b193_01E01D70;

typedef struct {
    u8 pad00[0x20];
    f32 x, y, z;
    u8 pad2C[0x54];
    s32 ot;
    u8 pad84[4];
    void *texture;
    u8 pad8C[8];
    s16 u;
    s16 v;
    u8 pad98[2];
    s16 h;
    u8 pad9C[0x1C];
    s16 count;
    u8 padBA[0x1E];
    u8 trig[1];
} Obj_b193_01E01D70;

typedef struct {
    u8 pad00[0x20];
    s32 rot[4];
    u8 pad30[0xC];
    f32 height;
    u8 pad40[8];
    f32 r;
    f32 dr;
    u8 pad50[0xA];
    s16 ang;
    u8 pad5C[4];
    u8 col[4];
    u8 col2[4];
} Fx_b193_01E01D70;

#pragma opt_propagation off
static void func_01E01D70_b193(Obj_b193_01E01D70 *o, Fx_b193_01E01D70 *fx, Pkt_b193_01E01D70 *pk, s32 mode) {
    extern s32 func_00205440(void *, void *, void *, f32 *);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern f32 func_00108030(void *, s16, s32);
    extern void func_002075F0(void *, s32, s32);
    s32 i __attribute__((aligned(16)));
    Vec4f q[4];
    Vec4f pos;
    Vec4f scale;
    f32 m[16];
    f32 dep[4];
    s16 blend;
    s16 a;
    s32 k;
    s32 j;
    f32 v0;
    f32 v1;
    f32 u0;
    f32 u1;
    f32 w;
    f32 sb;

    pk->flags = 0x34;
    pk->size = 0xC;
    a = 0;
    pk->regs = ((u64)0x4214 << 32) | 0x21421421;
    blend = mode >> 4;
    pk->pad = 0;
    if (blend == 0) {
        func_002086D0(pk, ((u64)0x80 << 32) | 0x42);
    } else {
        func_002086D0(pk, ((u64)blend << 2) | (((u64)0x80 << 32) | 0x40));
    }
    func_00107790(pk, fx->col, 1);
    func_00107790(pk, fx->col2, 2);
    func_00208700(pk, o->texture, 1);
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
    v0 = o->v;
    v1 = o->v + o->h;
    func_00108EF0(m, &scale, fx->rot, &pos);
    q[0].y = fx->height;
    q[1].y = fx->height;
    q[2].y = 0.0f;
    q[3].y = 0.0f;
    i = 0;
    do {
        k = fx->ang + a;
        q[2].x = fx->r * func_00108030(o->trig, k, 1);
        q[2].z = fx->r * func_00108030(o->trig, k, 0);
        q[0].x = (fx->r + fx->dr) * func_00108030(o->trig, k, 1);
        q[0].z = (fx->r + fx->dr) * func_00108030(o->trig, k, 0);
        k = a + (fx->ang + 10);
        q[3].x = fx->r * func_00108030(o->trig, k, 1);
        q[3].z = fx->r * func_00108030(o->trig, k, 0);
        q[1].x = (fx->r + fx->dr) * func_00108030(o->trig, k, 1);
        q[1].z = (fx->r + fx->dr) * func_00108030(o->trig, k, 0);
        if (func_00205440(&q[0], m, &pk->v[0].xyz, &dep[0]) != 0 && func_00205440(&q[1], m, &pk->v[1].xyz, &dep[1]) != 0 &&
            func_00205440(&q[2], m, &pk->v[2].xyz, &dep[2]) != 0 && func_00205440(&q[3], m, &pk->v[3].xyz, &dep[3]) != 0) {
            pk->v[0].xyz.f = pk->v[1].xyz.f = pk->v[2].xyz.f = pk->v[3].xyz.f = 0;
            pk->v[0].q = 1.0f / dep[0];
            pk->v[1].q = 1.0f / dep[1];
            pk->v[2].q = 1.0f / dep[2];
            pk->v[3].q = 1.0f / dep[3];
            func_00208CB0(pk, ((u64)o->u << 14) | 0xFB | ((u64)o->v << 24) | ((u64)(o->v + o->h - 1) << 34));
            w = 256.0f;
            u0 = 0.0f;
            u1 = 64.0f;
            pk->v[0].s = u0 / dep[0];
            pk->v[0].t = v0 / w / dep[0];
            pk->v[1].s = u1 / w / dep[1];
            pk->v[1].t = v0 / w / dep[1];
            pk->v[2].s = u0 / w / dep[2];
            pk->v[2].t = (sb = v1 / w) / dep[2];
            pk->v[3].s = u1 / w / dep[3];
            pk->v[3].t = sb / dep[3];
            for (j = 0; j < o->count + 1; j++) {
                func_002075F0(pk, o->ot, (u32)((dep[3] + (dep[2] + (dep[0] + dep[1]))) / 4.0f));
            }
        }
        a += 10;
        i++;
    } while (i < 36);
}
#pragma opt_propagation reset
