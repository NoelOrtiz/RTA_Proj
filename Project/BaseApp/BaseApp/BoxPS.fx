struct PixelInputType
{
	float4 pos : SV_POSITION;
	float4 uv : TEXCOORD;
};

Texture2D tex : register(t0);
SamplerState ss : register(s0);

float4 BoxPShader(PixelInputType input) : SV_TARGET
{
	return tex.Sample(ss, input.uv.xy);
}