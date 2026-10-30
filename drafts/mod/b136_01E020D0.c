#include "common.h"

/* shape b136:01E020D0 (B136PAINT_RAIN3), 204 insns, 1 copy: b159:01E01B30 cousin: the ring scaled (0.8, 1, 0.8) at
   the object's position, 9 sectors of 40 between radius o->size and o->size - 10 with the outer edge jittered -5..4
   in height each frame; mode 0 sets up the packet's texture (0x97, page o->page) */

typedef struct {
    s16 x, y, z;
    u8 pad6[0xA];
    s32 rot[4];
    u8 pad20[8];
    u8 col[8];
    u8 pad30[4];
    s16 page;
    u8 pad36[2];
    s16 size;
    s16 ang;
} Obj_b136_01E020D0;

static void func_01E020D0_b136(u8 *ctx, Obj_b136_01E020D0 *o, void *pkt, s32 mode) {
    extern void func_00106080(void *, s32, s16, void *);
    extern s32 func_00109270(void *, s32, s32);
    extern void func_00107790(void *, void *, s32);
    extern void func_00108EF0(void *, void *, void *, void *);
    extern void func_00106DD0(void *, f32, f32, f32);
    extern f32 func_00108030(void *, s16, s32);
    Vec4f q[4];
    Vec4f pos;
    Vec4f sc;
    f32 m[16];
    u8 td[0x10];
    s32 i;
    s16 a;
    s16 k;
    f32 c;
    f32 sn;
    f32 sx;
    f32 sz;

    a = 0;
    if (mode == 0) {
        func_00106080(td, 0x97, o->page, td);
        func_00109270(pkt, 0, 0);
        func_00107790(pkt, o->col, 0);
        func_00108500(pkt, td, 0);
        func_00208700(pkt, *(void **)(ctx + 0x10C), 1);
        return;
    }
    pos.x = o->x;
    pos.y = o->y;
    pos.z = o->z;
    { f32 r = 0.8f; func_00106DD0(&sc, r, 1.0f, r); }
    func_00108EF0(m, &sc, o->rot, &pos);
    q[0].y = 0.0f;
    q[1].y = 0.0f;
    *(f32 *)(u32)&q[2].y = 0.0f;
    *(f32 *)(u32)&q[3].y = 0.0f;
    for (i = 0; i < 9; i++) {
        k = o->ang + a;
        c = func_00108030(ctx + 0x3664, k, 1);
        sn = func_00108030(ctx + 0x3664, k, 0);
        q[2].x = c * o->size;
        q[2].z = sn * o->size;
        q[0].x = c * (o->size - 10);
        q[0].z = sn * (o->size - 10);
        k = o->ang + 40 + a;
        c = func_00108030(ctx + 0x3664, k, 1);
        sn = func_00108030(ctx + 0x3664, k, 0);
        q[3].x = c * o->size;
        q[3].z = sn * o->size;
        q[1].x = c * (o->size - 10);
        q[1].z = sn * (o->size - 10);
        *(f32 *)(u32)&q[2].y = func_0019A5C8() % 10 - 5;
        *(f32 *)(u32)&q[3].y = func_0019A5C8() % 10 - 5;
        if (func_00205630((s32)q, 0x70000000, (s32)m, (s32)pkt, (f32 *)(ctx + 0x3634)) != 0) {
            func_002075F0((s32)pkt, *(s32 *)(ctx + 0x360C), (u32)*(f32 *)(ctx + 0x3634));
        }
        a += 40;
    }
}
