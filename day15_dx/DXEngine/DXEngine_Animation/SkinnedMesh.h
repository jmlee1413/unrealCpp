#pragma once
#include "Mesh.h"
#include <string>
#include <utility>

namespace Utilities
{
	FbxAMatrix GetTransformMatrix(FbxNode* node);
	void ConvertFbxAMatrixToDXMatrix(XMFLOAT4X4* outMatrix, FbxAMatrix fbxAMatrix);
	FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex);
	FbxAMatrix GetGlobalPosition(
		FbxNode* pNode,
		const FbxTime& pTime,
		FbxPose* pPose,
		FbxAMatrix* pParentGlobalPosition = NULL);
};

struct Bone
{
public:
	XMFLOAT4X4 GetBoneMatrix(unsigned int frame, FbxPose* fbxPose);

	int boneIndex;
	int parentIndex;
	std::string name;
	FbxAMatrix globalBindposeInverseMatrix;
	FbxNode* fbxNode;
};

struct VertexWeight
{
public:
	void AddBoneData(unsigned int index, float weight);
	void Normalize();

	std::pair<unsigned int, float> boneWeight[4];
};


struct Skeleton
{
public:
	Bone* FindBoneByName(std::string boneName);

	std::vector<Bone> bones;
};

class SkinnedMesh :public Mesh
{
public:
	SkinnedMesh();
	~SkinnedMesh();

	void LoadSkeleton(FbxNode* root);
	void RLoadSkeletonHierarchy(FbxNode* child, int depth, int index, int parentIndex);
	void ReadAnimCurves(FbxNode* node);

private:
	Skeleton* skeleton;
};

