#if 0
//
// FX Version: fx_5_0
//
// 1 local buffer(s)
//
cbuffer MatrixBuffer
{
    float4x4 world;                     // Offset:    0, size:   64
    float4x4 view;                      // Offset:   64, size:   64
    float4x4 proj;                      // Offset:  128, size:   64
}

#endif

const BYTE BoxVS[] =
{
      1,  32, 255, 254,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  70,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  77,  97, 
    116, 114, 105, 120,  66, 117, 
    102, 102, 101, 114,   0, 102, 
    108, 111,  97, 116,  52, 120, 
     52,   0,  17,   0,   0,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  64,   0,   0,   0, 
     64,   0,   0,   0,  64,   0, 
      0,   0,  11, 100,   0,   0, 
    119, 111, 114, 108, 100,   0, 
    118, 105, 101, 119,   0, 112, 
    114, 111, 106,   0,   4,   0, 
      0,   0, 192,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0, 255, 255, 255, 255, 
      0,   0,   0,   0,  54,   0, 
      0,   0,  26,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  60,   0,   0,   0, 
     26,   0,   0,   0,   0,   0, 
      0,   0,  64,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     65,   0,   0,   0,  26,   0, 
      0,   0,   0,   0,   0,   0, 
    128,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};
