struct PixelInputType
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
};

float4 PShader(PixelInputType input) : SV_TARGET
{
	return input.col;
}