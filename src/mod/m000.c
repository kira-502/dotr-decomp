#include "common.h"

/* shape m000:01E00080 (m000), 127 insns, 1 copy: draws the two spinning triangles of the module's template
   (0x1E00300): with a non-negative argument it only clears the turn; otherwise, when func_001F5EB0 allows, it turns
   0x800 a frame, builds the matrix at the camera point and sends both triangles at the scene alpha */

typedef struct {
    Vec4f v[6];
} Tris_m000_01E00080;

typedef struct {
    s16 count;
    s16 tag;
    s32 pad;
    u64 regs;
} Hdr_m000_01E00080;

typedef struct {
    u8 r, g, b, a;
    f32 q;
    u8 pad8[7];
    u8 end;
} Vtx_m000_01E00080;

typedef struct {
    Hdr_m000_01E00080 h;
    Vtx_m000_01E00080 v[3];
} Pkt_m000_01E00080;

static s32 func_01E00080_m000(s32 arg0, s32 arg) {
    s32 *rot = (s32 *)arg0;
    extern Tris_m000_01E00080 D_01E00300_m000;
    extern s32 func_001F5EB0(void);
    extern void func_001F6480(void *);
    extern void func_001F53B0(s32, void *);
    extern void func_0020EB40(void *);
    extern void func_0020C940(void *, void *, void *, void *);
    extern void func_0020BC00(void *, void *);
    extern s32 func_00205630(void *, s32, void *, void *, f32 *);
    extern void func_002075F0(void *, s32, s32);
    Tris_m000_01E00080 t;
    Vec4f cam;
    f32 m2[16];
    f32 m[16];
    f32 depth[4];
    Pkt_m000_01E00080 pk;
    u8 pad180[0xC];
    u8 col[4];
    s32 ot;

    ot = (s32)func_00207500();
    t = D_01E00300_m000;
    if (arg >= 0) {
        rot[0] = 0;
        rot[1] = 0;
        rot[2] = 0;
        rot[3] = 0;
        return 0;
    }
    if (func_001F5EB0() == 0) {
        return 0;
    }
    func_001F6480(col);
    func_001F53B0(1, &cam);
    rot[1] += 0x800;
    func_0020EB40(m);
    func_0020C940(m2, NULL, rot, &cam);
    func_0020BC00(m, m2);
    ((Hdr_m000_01E00080 *)(u32)&pk)->tag = 0x13;
    ((Hdr_m000_01E00080 *)(u32)&pk)->count = 6;
    ((Hdr_m000_01E00080 *)(u32)&pk)->regs = 0x414141;
    ((Hdr_m000_01E00080 *)(u32)&pk)->pad = 0;
    func_002086D0(&pk, 0x48 | ((u64)0x80 << 32));
    pk.v[0].r = 0x80;
    pk.v[0].g = 0x20;
    pk.v[0].b = 0x20;
    pk.v[0].a = col[3];
    pk.v[0].q = 1.0f;
    pk.v[1].r = 0x20;
    pk.v[1].g = 0x80;
    pk.v[1].b = 0x20;
    pk.v[1].a = col[3];
    pk.v[1].q = 1.0f;
    pk.v[2].r = 0x20;
    pk.v[2].g = 0x20;
    pk.v[2].b = 0x80;
    pk.v[2].a = col[3];
    pk.v[2].q = 1.0f;
    pk.v[0].end = 0;
    pk.v[1].end = 0;
    pk.v[2].end = 0;
    if (func_00205630(&t.v[0], 0x70000000, m, &pk, depth) != 0) {
        func_002075F0(&pk, ot, (u32)depth[0]);
    }
    if (func_00205630(&t.v[3], 0x70000000, m, &pk, depth) != 0) {
        func_002075F0(&pk, ot, (u32)depth[0]);
    }
    return 0;
}
