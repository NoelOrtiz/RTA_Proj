#include "FBXExport.h"
#include "Facade.h"
using namespace Exporter;

namespace EXP
{
	vector<Vertex> Facade::getVertices(vector<Vertex> fillOut, const char* filepath)
	{
		FBXExporter* exporter = new FBXExporter();
		exporter->Initialize();
		exporter->LoadScene(filepath);
		FbxScene* temp = exporter->getScene();
		FbxNode* tempNode = temp->GetRootNode();
		int tracker = temp->GetNodeCount();
		exporter->ProcessControlPoints(tempNode);
		exporter->ProcessMesh(temp->GetRootNode());

		for (int i = 0; i < exporter->getVertices().size(); i++)
		{
			Vertex obj;
			vector<PNTIWVertex> temp = exporter->getVertices();
			
			obj.x = temp[i].mPosition.x;
			obj.y = temp[i].mPosition.y;
			obj.z = temp[i].mPosition.z;
			fillOut.push_back(obj);
		}
		return fillOut;
	}
}