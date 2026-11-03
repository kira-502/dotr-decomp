#include "common.h"

/* shape b029:01E05AA0 (ShFx_ReqBlur), 286 insns, 10 copies: a flat textured screen quad shown between frames
   start..end, fading in over the first fade frames and out over the last 2 x fade; corners from the object (x16,
   offset to the screen centre). The original's far-depth chain writes corner 1 twice and never corner 2 */

typedef struct {
    u16 start;
    u16 end;
    u8 pad4;
    u8 fade;
    u8 tex;
    u8 pad7;
    f32 level;
    s32 x[4];
    s32 y[4];
    u8 b, g, r;
} Obj_b029_01E05AA0;

typedef struct {
    s16 n;
    u16 nreg;
    s32 pad4;
    u64 regs;
} Hdr_b029_01E05AA0;

typedef struct {
    u16 u : 14;
    u16 pu : 2;
    u16 v : 14;
    u16 pv : 2;
    u32 pad4;
} Uv_b029_01E05AA0;

typedef struct {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} Xyz_b029_01E05AA0;

typedef struct {
    Hdr_b029_01E05AA0 h;
    struct {
        u8 r, g, b, a;
        f32 q;
        Uv_b029_01E05AA0 uv;
        Xyz_b029_01E05AA0 xyz;
    } v[4];
    u8 tail[0x20];
} Pk_b029_01E05AA0;

typedef struct {
    u8 pad0[5];
    u8 tex;
    u8 pad6[0x12];
} Tex_b029_01E05AA0;

static s32 func_01E05AA0_b029(Obj_b029_01E05AA0 *obj, s32 dst, u16 frame) {
    Tex_b029_01E05AA0 tex;
    Pk_b029_01E05AA0 pk __attribute__((aligned(8)));
    u8 o[4];
    u8 a;
    s32 d;

    if (frame >= obj->start && frame <= obj->end) {
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->nreg = 0x34;
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->n = 0xC;
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->regs = ((u64)0x4214 << 32) | 0x21421421;
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->pad4 = 0;
        func_002087A0(&pk, 1);
        pk.v[0].r = pk.v[1].r = pk.v[2].r = pk.v[3].r = obj->r;
        pk.v[0].g = pk.v[1].g = pk.v[2].g = pk.v[3].g = obj->g;
        pk.v[0].b = pk.v[1].b = pk.v[2].b = pk.v[3].b = obj->b;
        pk.v[0].q = pk.v[1].q = pk.v[2].q = pk.v[3].q = 1.0f;
        pk.v[0].xyz.z = pk.v[1].xyz.z = pk.v[1].xyz.z = pk.v[3].xyz.z = 0xFFFFFF;
        pk.v[0].xyz.f = pk.v[1].xyz.f = pk.v[2].xyz.f = pk.v[3].xyz.f = 0;
        d = frame - obj->start;
        a = obj->fade * 16;
        if (d < obj->fade) {
            a = d * 16;
        }
        if (obj->end - frame < obj->fade * 2) {
            a = (obj->end - frame) * 8;
        }
        pk.v[0].a = pk.v[1].a = pk.v[2].a = pk.v[3].a = a;
        tex.tex = obj->tex;
        func_00101C80(&tex, o);
        func_002086D0(&pk, (s64)o[0] | ((s64)o[1] << 2) | ((s64)o[2] << 4) | ((s64)o[3] << 6));
        ((Hdr_b029_01E05AA0 *)(s32)&pk)->nreg |= 0x800;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[0].uv)->u = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[0].uv)->v = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[1].uv)->u = 0x2800;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[1].uv)->v = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[2].uv)->u = 0;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[2].uv)->v = 0x1C00;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[3].uv)->u = 0x2800;
        ((Uv_b029_01E05AA0 *)(s32)&pk.v[3].uv)->v = 0x1C00;
        pk.v[0].xyz.x = func_001A23B0(27648.0f + (f32)(obj->x[0] * 16));
        pk.v[1].xyz.x = func_001A23B0(37888.0f + (f32)(obj->x[1] * 16));
        pk.v[2].xyz.x = func_001A23B0(27648.0f + (f32)(obj->x[2] * 16));
        pk.v[3].xyz.x = func_001A23B0(37888.0f + (f32)(obj->x[3] * 16));
        pk.v[0].xyz.y = func_001A23B0(29184.0f + (f32)(obj->y[0] * 16));
        pk.v[1].xyz.y = func_001A23B0(29184.0f + (f32)(obj->y[1] * 16));
        pk.v[2].xyz.y = func_001A23B0(36352.0f + (f32)(obj->y[2] * 16));
        pk.v[3].xyz.y = func_001A23B0(36352.0f + (f32)(obj->y[3] * 16));
        func_002075F0((s32)&pk, dst, func_001A23B0(obj->level));
    }
    return 1;
}
