//#pragma pack_matrix(row_major)
struct PixelInputType
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
	float3 normal : NORMAL;
	float3 worldpos : POSITION;
};

cbuffer Lights : register(b0)
{
	float3 direction;
	float pointRadius;
	float4 color;
	float4 pointPosition;
	float4 pointColor;
	float4 spotColor;
	float4 spotPosition;
	float4 spotDirection;
	float spotRadius;
	float3 padding;
};

Texture2D groundTexture : register (t0);
SamplerState smpState : register (s1);

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 texturecolor = groundTexture.Sample(smpState, input.col.xy);
float3 norm = { 0,1,0 };

float directionRatio = saturate(dot(-direction, input.normal));
float4 directionResult = directionRatio * color;

float3 pointDirection = normalize(pointPosition.xyz - input.worldpos.xyz);
float pointRatio = saturate(dot(pointDirection, input.normal));
float4 pointAttenuation = 1 - saturate(length(pointPosition.xyz - input.worldpos.xyz) / pointRadius);
float4 pointResult = pointAttenuation * pointRatio * pointColor;

float3 spotDir = normalize(spotPosition.xyz - input.worldpos.xyz);
float spotRatio = saturate(dot(-spotDir.xyz, spotDirection.xyz));

float spotLightratio = saturate(dot(spotDir, input.normal));
float outerCone = cos(30.0f * (3.1415f / 180.0f));
float innerCone = cos(20.0f * (3.1415f / 180.0f));
float4 spotAttenuation = 1 - saturate((innerCone - spotRatio) / (innerCone - outerCone));

float4 spotResult = spotAttenuation * spotLightratio * spotColor;

return texturecolor * saturate(directionResult + spotResult + pointResult);
//return texturecolor;
}