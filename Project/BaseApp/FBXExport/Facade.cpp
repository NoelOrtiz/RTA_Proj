#include "FBXExport.h"
#include "Facade.h"
using namespace Exporter;

namespace EXP
{

	vector<VNUInfo> Facade::getVertices(vector<VNUInfo> fillOut, const char* filepath)
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
			VNUInfo obj;
			vector<PNTIWVertex> temp = exporter->getVertices();
			
			obj.vertInfo.x = temp[i].mPosition.x;
			obj.vertInfo.y = temp[i].mPosition.y;
			obj.vertInfo.z = temp[i].mPosition.z;
			obj.normInfo.x = temp[i].mNormal.x;
			obj.normInfo.y = temp[i].mNormal.y;
			obj.normInfo.z = temp[i].mNormal.z;
			obj.textureInfo.x = temp[i].mUV.x;
			obj.textureInfo.y = temp[i].mUV.y;
			fillOut.push_back(obj);
		}
		return fillOut;
	}
}