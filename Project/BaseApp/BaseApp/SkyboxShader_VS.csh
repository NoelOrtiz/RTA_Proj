#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 6.3.9600.16384
//
// Parameters:
//
//   row_major float4x4 ProjectionMatrix;
//   row_major float4x4 ViewMatrix;
//   row_major float4x4 WorldMatrix;
//
//
// Registers:
//
//   Name             Reg   Size
//   ---------------- ----- ----
//   WorldMatrix      c0       4
//   ViewMatrix       c4       4
//   ProjectionMatrix c8       4
//

    vs_2_0
    def c12, 1, 0, 0, 0
    dcl_position v0  // input<0,1,2>
    dcl_color v1  // input<4,5,6,7>

#line 30 "C:\Users\mrprr\Desktop\RTA_Proj_Graded\Project\BaseApp\BaseApp\SkyboxShader_VS.hlsl"
    mov r0.xyz, v0  // ::localH<0,1,2>
    mul r1, r0.x, c0
    mul r2, r0.y, c1
    add r1, r1, r2
    mul r0, r0.z, c2
    add r0, r0, r1
    mov r1.x, c12.x  // ::localH<3>
    mul r1, r1.x, c3
    add r0, r0, r1  // ::localH<0,1,2,3>

#line 36
    mul r1, r0.x, c4
    mul r2, r0.y, c5
    add r1, r1, r2
    mul r2, r0.z, c6
    add r1, r1, r2
    mul r0, r0.w, c7
    add r0, r0, r1  // ::localH<0,1,2,3>
    mul r1, r0.x, c8
    mul r2, r0.y, c9
    add r1, r1, r2
    mul r2, r0.z, c10
    add r1, r1, r2
    mul r0, r0.w, c11
    add r0, r0, r1  // ::localH<0,1,2,3>
    mov r0, r0  // ::output<0,1,2,3>
    mov r1, v1  // ::output<4,5,6,7>
    mov oPos, r0  // ::main<0,1,2,3>
    mov oD0, r1  // ::main<4,5,6,7>

// approximately 27 instruction slots used
#endif

const BYTE SkyboxShader_VS[] =
{
      0,   2, 254, 255, 254, 255, 
    198,   0,  68,  66,  85,  71, 
     40,   0,   0,   0, 224,   2, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0, 124,   0, 
      0,   0,  30,   0,   0,   0, 
    128,   0,   0,   0,   4,   0, 
      0,   0, 144,   2,   0,   0, 
    112,   1,   0,   0,  67,  58, 
     92,  85, 115, 101, 114, 115, 
     92, 109, 114, 112, 114, 114, 
     92,  68, 101, 115, 107, 116, 
    111, 112,  92,  82,  84,  65, 
     95,  80, 114, 111, 106,  95, 
     71, 114,  97, 100, 101, 100, 
     92,  80, 114, 111, 106, 101, 
     99, 116,  92,  66,  97, 115, 
    101,  65, 112, 112,  92,  66, 
     97, 115, 101,  65, 112, 112, 
     92,  83, 107, 121,  98, 111, 
    120,  83, 104,  97, 100, 101, 
    114,  95,  86,  83,  46, 104, 
    108, 115, 108,   0,  40,   0, 
      0,   0,   0,   0, 255, 255, 
    244,   3,   0,   0,   0,   0, 
    255, 255,  12,   4,   0,   0, 
      0,   0, 255, 255,  24,   4, 
      0,   0,  30,   0,   0,   0, 
     36,   4,   0,   0,  32,   0, 
      0,   0,  48,   4,   0,   0, 
     32,   0,   0,   0,  64,   4, 
      0,   0,  32,   0,   0,   0, 
     80,   4,   0,   0,  32,   0, 
      0,   0,  96,   4,   0,   0, 
     32,   0,   0,   0, 112,   4, 
      0,   0,  32,   0,   0,   0, 
    128,   4,   0,   0,  32,   0, 
      0,   0, 140,   4,   0,   0, 
     32,   0,   0,   0, 156,   4, 
      0,   0,  36,   0,   0,   0, 
    172,   4,   0,   0,  36,   0, 
      0,   0, 188,   4,   0,   0, 
     36,   0,   0,   0, 204,   4, 
      0,   0,  36,   0,   0,   0, 
    220,   4,   0,   0,  36,   0, 
      0,   0, 236,   4,   0,   0, 
     36,   0,   0,   0, 252,   4, 
      0,   0,  36,   0,   0,   0, 
     12,   5,   0,   0,  37,   0, 
      0,   0,  28,   5,   0,   0, 
     37,   0,   0,   0,  44,   5, 
      0,   0,  37,   0,   0,   0, 
     60,   5,   0,   0,  37,   0, 
      0,   0,  76,   5,   0,   0, 
     37,   0,   0,   0,  92,   5, 
      0,   0,  37,   0,   0,   0, 
    108,   5,   0,   0,  37,   0, 
      0,   0, 124,   5,   0,   0, 
     38,   0,   0,   0, 140,   5, 
      0,   0,  39,   0,   0,   0, 
    152,   5,   0,   0,  41,   0, 
      0,   0, 164,   5,   0,   0, 
     41,   0,   0,   0, 176,   5, 
      0,   0, 109,  97, 105, 110, 
      0, 105, 110, 112, 117, 116, 
      0, 112, 111, 115,  73, 110, 
      0, 171, 171, 171,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  99, 111, 108, 111, 
    114,  73, 110,   0, 123,   1, 
      0,   0, 132,   1,   0,   0, 
    148,   1,   0,   0, 132,   1, 
      0,   0,   5,   0,   0,   0, 
      1,   0,   8,   0,   1,   0, 
      2,   0, 156,   1,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      1,   0,   2,   0, 255, 255, 
      2,   0,   0,   0,   4,   0, 
      5,   0,   6,   0,   7,   0, 
    108, 111,  99,  97, 108,  72, 
      0, 171,   3,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
    255, 255,   9,   0,   0,   0, 
      3,   0, 255, 255, 255, 255, 
    255, 255,  11,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0,  18,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0,  25,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0, 112, 111, 115,  79, 
    117, 116,   0,  99, 111, 108, 
    111, 114,  79, 117, 116,   0, 
     24,   2,   0,   0, 132,   1, 
      0,   0,  31,   2,   0,   0, 
    132,   1,   0,   0,   5,   0, 
      0,   0,   1,   0,   8,   0, 
      1,   0,   2,   0,  40,   2, 
      0,   0,  28,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0,  29,   0,   0,   0, 
      4,   0,   5,   0,   6,   0, 
      7,   0, 111, 117, 116, 112, 
    117, 116,   0, 171,   5,   0, 
      0,   0,   1,   0,   8,   0, 
      1,   0,   2,   0,  40,   2, 
      0,   0,  26,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0,  27,   0,   0,   0, 
      4,   0,   5,   0,   6,   0, 
      7,   0, 112,   1,   0,   0, 
    117,   1,   0,   0, 172,   1, 
      0,   0,   2,   0,   0,   0, 
    188,   1,   0,   0,   0,   0, 
      0,   0, 212,   1,   0,   0, 
    132,   1,   0,   0,   5,   0, 
      0,   0, 220,   1,   0,   0, 
      0,   0,   0,   0, 112,   1, 
      0,   0,  56,   2,   0,   0, 
      2,   0,   0,   0,  72,   2, 
      0,   0,   0,   0,   0,   0, 
     96,   2,   0,   0, 104,   2, 
      0,   0,   2,   0,   0,   0, 
    120,   2,   0,   0,  77, 105, 
     99, 114, 111, 115, 111, 102, 
    116,  32,  40,  82,  41,  32, 
     72,  76,  83,  76,  32,  83, 
    104,  97, 100, 101, 114,  32, 
     67, 111, 109, 112, 105, 108, 
    101, 114,  32,  54,  46,  51, 
     46,  57,  54,  48,  48,  46, 
     49,  54,  51,  56,  52,   0, 
    171, 171, 254, 255,  52,   0, 
     67,  84,  65,  66,  28,   0, 
      0,   0, 154,   0,   0,   0, 
      0,   2, 254, 255,   3,   0, 
      0,   0,  28,   0,   0,   0, 
      5,   1,   0,   0, 147,   0, 
      0,   0,  88,   0,   0,   0, 
      2,   0,   8,   0,   4,   0, 
      0,   0, 108,   0,   0,   0, 
      0,   0,   0,   0, 124,   0, 
      0,   0,   2,   0,   4,   0, 
      4,   0,   0,   0, 108,   0, 
      0,   0,   0,   0,   0,   0, 
    135,   0,   0,   0,   2,   0, 
      0,   0,   4,   0,   0,   0, 
    108,   0,   0,   0,   0,   0, 
      0,   0,  80, 114, 111, 106, 
    101,  99, 116, 105, 111, 110, 
     77,  97, 116, 114, 105, 120, 
      0, 171, 171, 171,   2,   0, 
      3,   0,   4,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  86, 105, 101, 119, 
     77,  97, 116, 114, 105, 120, 
      0,  87, 111, 114, 108, 100, 
     77,  97, 116, 114, 105, 120, 
      0, 118, 115,  95,  50,  95, 
     48,   0,  77, 105,  99, 114, 
    111, 115, 111, 102, 116,  32, 
     40,  82,  41,  32,  72,  76, 
     83,  76,  32,  83, 104,  97, 
    100, 101, 114,  32,  67, 111, 
    109, 112, 105, 108, 101, 114, 
     32,  54,  46,  51,  46,  57, 
     54,  48,  48,  46,  49,  54, 
     51,  56,  52,   0,  81,   0, 
      0,   5,  12,   0,  15, 160, 
      0,   0, 128,  63,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,  10,   0,   0, 128, 
      1,   0,  15, 144,   1,   0, 
      0,   2,   0,   0,   7, 128, 
      0,   0, 228, 144,   5,   0, 
      0,   3,   1,   0,  15, 128, 
      0,   0,   0, 128,   0,   0, 
    228, 160,   5,   0,   0,   3, 
      2,   0,  15, 128,   0,   0, 
     85, 128,   1,   0, 228, 160, 
      2,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      2,   0, 228, 128,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 170, 128,   2,   0, 
    228, 160,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      1,   0,   0,   2,   1,   0, 
      1, 128,  12,   0,   0, 160, 
      5,   0,   0,   3,   1,   0, 
     15, 128,   1,   0,   0, 128, 
      3,   0, 228, 160,   2,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 228, 128,   1,   0, 
    228, 128,   5,   0,   0,   3, 
      1,   0,  15, 128,   0,   0, 
      0, 128,   4,   0, 228, 160, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   0,   0,  85, 128, 
      5,   0, 228, 160,   2,   0, 
      0,   3,   1,   0,  15, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 128,   5,   0,   0,   3, 
      2,   0,  15, 128,   0,   0, 
    170, 128,   6,   0, 228, 160, 
      2,   0,   0,   3,   1,   0, 
     15, 128,   1,   0, 228, 128, 
      2,   0, 228, 128,   5,   0, 
      0,   3,   0,   0,  15, 128, 
      0,   0, 255, 128,   7,   0, 
    228, 160,   2,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      5,   0,   0,   3,   1,   0, 
     15, 128,   0,   0,   0, 128, 
      8,   0, 228, 160,   5,   0, 
      0,   3,   2,   0,  15, 128, 
      0,   0,  85, 128,   9,   0, 
    228, 160,   2,   0,   0,   3, 
      1,   0,  15, 128,   1,   0, 
    228, 128,   2,   0, 228, 128, 
      5,   0,   0,   3,   2,   0, 
     15, 128,   0,   0, 170, 128, 
     10,   0, 228, 160,   2,   0, 
      0,   3,   1,   0,  15, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 128,   5,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    255, 128,  11,   0, 228, 160, 
      2,   0,   0,   3,   0,   0, 
     15, 128,   0,   0, 228, 128, 
      1,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  15, 128, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   1,   0,  15, 128, 
      1,   0, 228, 144,   1,   0, 
      0,   2,   0,   0,  15, 192, 
      0,   0, 228, 128,   1,   0, 
      0,   2,   0,   0,  15, 208, 
      1,   0, 228, 128, 255, 255, 
      0,   0
};