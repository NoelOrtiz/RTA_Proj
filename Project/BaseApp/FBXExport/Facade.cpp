#include "FBXExport.h"
#include "Facade.h"
using namespace Exporter;

namespace EXP
{
	vector<Vertex> Facade::getVertices(vector<Vertex> fillOut, const char* filepath)
	{
		FBXExporter* exporter;
		exporter->Initialize();
		exporter->LoadScene(filepath);
		FbxScene* temp = exporter->getScene();
		exporter->ProcessControlPoints(temp->GetRootNode());
		exporter->ProcessMesh(temp->GetRootNode());

		for (int i = 0; i < exporter->getVertices().size(); i++)
		{
			vector<PNTIWVertex> temp = exporter->getVertices();
			fillOut[i].x = temp[i].mPosition.x;
			fillOut[i].y = temp[i].mPosition.y;
			fillOut[i].z = temp[i].mPosition.z;
		}
		return fillOut;
	}
}