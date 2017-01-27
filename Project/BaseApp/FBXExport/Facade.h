#pragma once

#include <vector>
#ifdef FBXEXPORT_EXPORTS
#define DLLEXPORT1 __declspec(dllexport)
#else
#define DLLEXPORT1 __declspec(dllimport)
#endif
struct VNUInfo
{
	XMFLOAT3 vertInfo;
	XMFLOAT3 normInfo;
	XMFLOAT2 textureInfo;

};
struct Vertex
{
	float x;
	float y;
	float z;
};


struct Normal
{
	float x;
	float y;
	float z;
};

struct UV
{
	float x;
	float y;
};

namespace  EXP
{
	class DLLEXPORT1 Facade
	{
	public:
		bool success = false;
		std::vector<VNUInfo> getVertices(std::vector<VNUInfo> fillOut, const char* filepath);
		void getJoints( const char* filepath);
	};
}