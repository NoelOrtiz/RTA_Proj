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
		vector<Vertex> numVertices;
		vector<Normal> norms;
		vector<UV> uvs;
		bool success = false;
		vector<Vertex> getVertices(vector<Vertex> fillOut, const char* filepath);
	};
}