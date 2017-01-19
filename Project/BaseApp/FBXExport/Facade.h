#pragma once

#include <vector>
#ifdef FBXEXPORT_EXPORTS
#define DLLEXPORT1 __declspec(dllexport)
#else
#define DLLEXPORT1 __declspec(dllimport)
#endif
struct Vertex
{
	float x;
	float y;
	float z;
};

struct Normal
{

};

struct UV
{

};

namespace  EXP
{
	class DLLEXPORT1 Facade
	{
	public:
		std::vector<Vertex> numVertices;
		std::vector<Normal> norms;
		std::vector<UV> uvs;
		bool success = false;
		std::vector<Vertex> getVertices(std::vector<Vertex> fillOut, const char* filepath);
	};
}