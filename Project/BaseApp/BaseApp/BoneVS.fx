cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix proj;
};

struct VertexInputType
{
	float4 lpos : POSITION0;
	float4 luv : TEXCOORD;
	float4 instPos : POSITION1;
};

struct PixelInputType
{
	float4 hpos : SV_POSITION;
	float4 huv : TEXCOORD;
};

PixelInputType BoneVShader(VertexInputType input)
{
	// ToPixelShader:
	PixelInputType output;

	// Manipulate vert information:
	input.lpos.x += input.instPos.x;
	input.lpos.y += input.instPos.y;
	input.lpos.z += input.instPos.z;

	output.hpos = mul(input.lpos, world);
	//output.wpos = output.hpos;			// when needful for lighting
	output.hpos = mul(output.hpos, view);
	output.hpos = mul(output.hpos, proj);

	// Manipulate UV information:
	output.huv = input.luv;

	return output;
}