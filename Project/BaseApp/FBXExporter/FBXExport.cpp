#include "FBXExport.h"
#include <fstream>
#include <sstream>
#include <iomanip>





namespace Exporter
{
	
	
	FBXExporter::FBXExporter()
	{
		mFBXManager = nullptr;
		mFBXScene = nullptr;
		mTriangleCount = 0;
		mHasAnimation = true;
		QueryPerformanceFrequency(&mCPUFreq);
	}

	bool FBXExporter::Initialize()
	{
		mFBXManager = FbxManager::Create();
		if (!mFBXManager)
		{
			return false;
		}

		FbxIOSettings* fbxIOSettings = FbxIOSettings::Create(mFBXManager, IOSROOT);
		mFBXManager->SetIOSettings(fbxIOSettings);

		mFBXScene = FbxScene::Create(mFBXManager, "myScene");

		return true;
	}

	void FBXExporter::ProcessControlPoints(FbxNode* inNode)
	{
		FbxMesh* currMesh = inNode->GetMesh();
		unsigned int ctrlPointCount = currMesh->GetControlPointsCount();
		for (unsigned int i = 0; i < ctrlPointCount; ++i)
		{
			CtrlPoint* currCtrlPoint = new CtrlPoint();
			XMFLOAT3 currPosition;
			currPosition.x = static_cast<float>(currMesh->GetControlPointAt(i).mData[0]);
			currPosition.y = static_cast<float>(currMesh->GetControlPointAt(i).mData[1]);
			currPosition.z = static_cast<float>(currMesh->GetControlPointAt(i).mData[2]);
			currCtrlPoint->mPosition = currPosition;
			m_ControlVectors.push_back(currPosition);
			mControlPoints[i] = currCtrlPoint;
		}
	}

	void FBXExporter::ProcessSkeletonHierarchy(FbxNode* inRootNode)
	{

		for (int childIndex = 0; childIndex < inRootNode->GetChildCount(); ++childIndex)
		{
			FbxNode* currNode = inRootNode->GetChild(childIndex);
			ProcessSkeletonHierarchyRecursively(currNode, 0, 0, -1);
		}
	}

	void FBXExporter::ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex)
	{
		if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			Joint currJoint;
			currJoint.mParentIndex = inParentIndex;
			currJoint.mName = inNode->GetName();
			mSkeleton.mJoints.push_back(currJoint);
		}
		for (int i = 0; i < inNode->GetChildCount(); i++)
		{
			ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, mSkeleton.mJoints.size(), myIndex);
		}
	}

	bool FBXExporter::LoadScene(const char* inFileName)
	{
		LARGE_INTEGER start;
		LARGE_INTEGER end;
		mInputFilePath = inFileName;
		

		QueryPerformanceCounter(&start);
		FbxImporter* fbxImporter = FbxImporter::Create(mFBXManager, "myImporter");

		if (!fbxImporter)
		{
			return false;
		}

		if (!fbxImporter->Initialize(inFileName, -1, mFBXManager->GetIOSettings()))
		{
			return false;
		}

		if (!fbxImporter->Import(mFBXScene))
		{
			return false;
		}
		fbxImporter->Destroy();
		QueryPerformanceCounter(&end);


		return true;
	}

	//void FBXExporter::ExportFBX()
	//{
	//	LARGE_INTEGER start;
	//	LARGE_INTEGER end;
	//
	//	// Get the clean name of the model
	//	std::string genericFileName = Utilities::GetFileName(mInputFilePath);
	//	genericFileName = Utilities::RemoveSuffix(genericFileName);
	//
	//	QueryPerformanceCounter(&start);
	//	ProcessSkeletonHierarchy(mFBXScene->GetRootNode());
	//	if (mSkeleton.mJoints.empty())
	//	{
	//		mHasAnimation = false;
	//	}
	//
	//	std::cout << "\n\n\n\nExporting Model:" << genericFileName << "\n";
	//	QueryPerformanceCounter(&end);
	//	std::cout << "Processing Skeleton Hierarchy: " << ((end.QuadPart - start.QuadPart) / static_cast<float>(mCPUFreq.QuadPart)) << "s\n";
	//
	//	QueryPerformanceCounter(&start);
	//	ProcessGeometry(mFBXScene->GetRootNode());
	//	QueryPerformanceCounter(&end);
	//	std::cout << "Processing Geometry: " << ((end.QuadPart - start.QuadPart) / static_cast<float>(mCPUFreq.QuadPart)) << "s\n";
	//
	//	QueryPerformanceCounter(&start);
	//	Optimize();
	//	QueryPerformanceCounter(&end);
	//	std::cout << "Optimization: " << ((end.QuadPart - start.QuadPart) / static_cast<float>(mCPUFreq.QuadPart)) << "s\n";
	//	//PrintMaterial();
	//	std::cout << "\n\n";
	//
	//
	//
	//	std::string outputMeshName = mOutputFilePath + genericFileName + ".itpmesh";
	//	std::ofstream meshOutput(outputMeshName);
	//	WriteMeshToStream(meshOutput);
	//
	//	if (mHasAnimation)
	//	{
	//		std::string outputNnimName = mOutputFilePath + genericFileName + ".itpanim";
	//		std::ofstream animOutput(outputNnimName);
	//		WriteAnimationToStream(animOutput);
	//	}
	//	CleanupFbxManager();
	//	std::cout << "\n\nExport Done!\n";
	//}

	void FBXExporter::ProcessMesh(FbxNode* inNode)
	{
		FbxMesh* currMesh = inNode->GetMesh();

		mTriangleCount = currMesh->GetPolygonCount();
		int vertexCounter = 0;


		mTriangles.reserve(mTriangleCount);

		for (unsigned int i = 0; i < mTriangleCount; ++i)
		{
			XMFLOAT3 normal[3];
			XMFLOAT3 tangent[3];
			XMFLOAT3 binormal[3];
			XMFLOAT2 UV[3][2];
			Triangle currTriangle;
			mTriangles.push_back(currTriangle);

			for (unsigned int j = 0; j < 3; ++j)
			{
				int ctrlPointIndex = currMesh->GetPolygonVertex(i, j);
				CtrlPoint* currCtrlPoint = mControlPoints[ctrlPointIndex];


				ReadNormal(currMesh, ctrlPointIndex, vertexCounter, normal[j]);
				// We only have diffuse texture
				for (int k = 0; k < 1; ++k)
				{
					ReadUV(currMesh, ctrlPointIndex, currMesh->GetTextureUVIndex(i, j), k, UV[j][k]);
				}
				PNTIWVertex temp;
				temp.mPosition = currCtrlPoint->mPosition;
				temp.mNormal = normal[j];
				temp.mUV = UV[j][0];
				mVertices.push_back(temp);
				mTriangles.back().mIndices.push_back(vertexCounter);
				++vertexCounter;
			}
		}

		for (auto itr = mControlPoints.begin(); itr != mControlPoints.end(); ++itr)
		{
			delete itr->second;
		}
		mControlPoints.clear();
	}

	void FBXExporter::ReadUV(FbxMesh* inMesh, int inCtrlPointIndex, int inTextureUVIndex, int inUVLayer, XMFLOAT2& outUV)
	{
		if (inUVLayer >= 2 || inMesh->GetElementUVCount() <= inUVLayer)
		{
			throw exception("Invalid UV Layer Number");
		}
		FbxGeometryElementUV* vertexUV = inMesh->GetElementUV(inUVLayer);

		switch (vertexUV->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outUV.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
				outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexUV->GetIndexArray().GetAt(inCtrlPointIndex);
				outUV.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
				outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			case FbxGeometryElement::eIndexToDirect:
			{
				outUV.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(inTextureUVIndex).mData[0]);
				outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(inTextureUVIndex).mData[1]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;
		}
	}

	void FBXExporter::ReadNormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outNormal)
	{
		if (inMesh->GetElementNormalCount() < 1)
		{
			throw std::exception("Invalid Normal Number");
		}

		FbxGeometryElementNormal* vertexNormal = inMesh->GetElementNormal(0);
		switch (vertexNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
				outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
				outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(inCtrlPointIndex);
				outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[0]);
				outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[1]);
				outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexNormal->GetIndexArray().GetAt(inVertexCounter);
				outNormal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
				outNormal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
				outNormal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;
		}
	}

	void FBXExporter::ReadBinormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outBinormal)
	{
		if (inMesh->GetElementBinormalCount() < 1)
		{
			throw std::exception("Invalid Binormal Number");
		}

		FbxGeometryElementBinormal* vertexBinormal = inMesh->GetElementBinormal(0);
		switch (vertexBinormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexBinormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
				outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
				outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexBinormal->GetIndexArray().GetAt(inCtrlPointIndex);
				outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
				outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
				outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexBinormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inVertexCounter).mData[0]);
				outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inVertexCounter).mData[1]);
				outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inVertexCounter).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexBinormal->GetIndexArray().GetAt(inVertexCounter);
				outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
				outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
				outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;
		}
	}

	void FBXExporter::ReadTangent(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outTangent)
	{
		if (inMesh->GetElementTangentCount() < 1)
		{
			throw std::exception("Invalid Tangent Number");
		}

		FbxGeometryElementTangent* vertexTangent = inMesh->GetElementTangent(0);
		switch (vertexTangent->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
				outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
				outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexTangent->GetIndexArray().GetAt(inCtrlPointIndex);
				outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			switch (vertexTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[0]);
				outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[1]);
				outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[2]);
			}
			break;

			case FbxGeometryElement::eIndexToDirect:
			{
				int index = vertexTangent->GetIndexArray().GetAt(inVertexCounter);
				outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
				outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
				outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
			}
			break;

			default:
				throw std::exception("Invalid Reference");
			}
			break;
		}
	}
}