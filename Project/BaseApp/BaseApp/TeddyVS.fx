cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};

struct VertexInputType
{
	float4 lpos : POSITION;
	float4 luv : TEXCOORD;
};

struct PixelInputType
{
	float4 hpos : SV_POSITION;
	float4 huv : TEXCOORD;
};

PixelInputType TeddyVShader(VertexInputType input)
{
	// ToPixelShader:
	PixelInputType output;

	// Manipulate vert information:
	input.lpos.w = 1.0f;
	input.lpos.z += 300.0f;
	input.lpos.y -= 100.0f;
	//input.lpos.x -= 5.0f;

	output.hpos = mul(input.lpos, world);
	//output.wpos = output.hpos;			// when needful for lighting
	output.hpos = mul(output.hpos, view);
	output.hpos = mul(output.hpos, proj);

	// Manipulate UV information:
	output.huv = input.luv;

	return output;
}