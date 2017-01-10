cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};

struct VertexInputType
{
	float4 lpos : POSITION;
	float4 lcol : COLOR;
	float3 normalIn : NORMAL;
};

struct PixelInputType
{
	float4 hpos : SV_POSITION;
	float4 hcol : COLOR;
	float3 normalOut : NORMAL;
	float3 worldpos : POSITION;

};

PixelInputType VShader(VertexInputType input)
{
	PixelInputType output;

	input.lpos.w = 1.0f;
	output.hpos = mul(input.lpos, world);
	float4 Worldpos = output.hpos;

	//output world matrix to W_POS
	output.hpos = mul(output.hpos, view);
	output.hpos = mul(output.hpos, proj);
	output.hcol = input.lcol;
	output.normalOut = mul((float3x3)world, input.normalIn);
	output.normalOut = normalize(output.normalOut);
	output.worldpos = Worldpos.xyz;
	return output;
}