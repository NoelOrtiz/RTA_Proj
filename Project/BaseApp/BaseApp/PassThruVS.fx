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
};

struct PixelInputType
{
	float4 hpos : SV_POSITION;
	float4 hcol : COLOR;
};

PixelInputType VShader(VertexInputType input)
{
	PixelInputType output;

	input.lpos.w = 1.0f;
	output.hpos = mul(input.lpos, world);
	//output world matrix to W_POS
	output.hpos = mul(output.hpos, view);
	output.hpos = mul(output.hpos, proj);
	output.hcol = input.lcol;
	return output;
}