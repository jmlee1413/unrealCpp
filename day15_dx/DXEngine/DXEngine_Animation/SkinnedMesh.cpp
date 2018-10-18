#include "SkinnedMesh.h"


namespace Utilities
{
	FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime,
		FbxPose* pPose, FbxAMatrix* pParentGlobalPosition)
	{
		FbxAMatrix lGlobalPosition;
		bool lPositionFound = false;

		if (pPose)
		{
			int lNodeIndex = pPose->Find(pNode);

			if (lNodeIndex > -1)
			{
				if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
				{
					lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
				}
				else
				{
					FbxAMatrix lParentGlobalPosition;

					if (pParentGlobalPosition)
					{
						lParentGlobalPosition = *pParentGlobalPosition;
					}
					else
					{
						if (pNode->GetParent())
						{
							lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
						}
					}
					FbxAMatrix lLocalPosition = pNode->GetScene()->GetAnimationEvaluator()->GetNodeLocalTransform(pNode, pTime);
					lGlobalPosition = lParentGlobalPosition * lLocalPosition;
				}

				lPositionFound = true;
			}
		}

		if (!lPositionFound)
		{
			// There is no pose entry for that node, get the current global position instead.
			// Ideally this would use parent global position and local position to compute the global position.
			// Unfortunately the equation 
			//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
			// does not hold when inheritance type is other than "Parent" (RSrs).
			// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
			lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
		}

		return lGlobalPosition;
	}

	// Get the matrix of the given pose
	FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex)
	{
		FbxAMatrix lPoseMatrix;
		FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);
		memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

		return lPoseMatrix;
	}

	FbxAMatrix GetTransformMatrix(FbxNode* node)
	{
		if (!node)
		{
			throw std::exception("Null for mesh geometry!!");
		}

		const FbxVector4 t = node->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 r = node->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 s = node->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(t, r, s);
	}

	void ConvertFbxAMatrixToDXMatrix(XMFLOAT4X4* outMatrix, FbxAMatrix fbxAMatrix)
	{
		for (int r = 0; r < 4; r++)
		{
			for (int c = 0; c < 4; c++)
			{
				outMatrix->m[r][c] = (float)fbxAMatrix.Get(r, c);
			}
		}
	}
}

SkinnedMesh::SkinnedMesh()
{
}


SkinnedMesh::~SkinnedMesh()
{
}

void SkinnedMesh::LoadSkeleton(FbxNode* root)
{
	for (int i = 0; i < root->GetChildCount(); i++)
	{
		FbxNode* child = root->GetChild(i);
		RLoadSkeletonHierarchy(child, 0, 0, -1);
	}

}

void SkinnedMesh::RLoadSkeletonHierarchy(FbxNode* child, int depth, int index, int parentIndex)
{
	if (child->GetNodeAttribute() &&
		child->GetNodeAttribute()->GetAttributeType() &&
		child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		Bone bone;
		bone.parentIndex = parentIndex;
		bone.name = child->GetName();

		skeleton->bones.push_back(bone);
	}

	int childCount = child->GetChildCount();

	for (int i = 0; i < childCount; i++)
	{
		RLoadSkeletonHierarchy(child->GetChild(i), depth + 1, skeleton->bones.size(), index);
	}
}

void SkinnedMesh::ReadAnimCurves(FbxNode* node)
{
	FbxMesh* fbxMesh = node->GetMesh();
	unsigned int numDeformers = fbxMesh->GetDeformerCount();

	// !!Not sure what is the usage of a geometry transform matrix...
	FbxAMatrix geometryTransform = Utilities::GetTransformMatrix(node);

	for (unsigned int deformerIndex = 0; deformerIndex < numDeformers; deformerIndex++)
	{
		FbxSkin* fbxSkin = reinterpret_cast<FbxSkin*>(fbxMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));

		if (!fbxSkin)
		{
			continue;
		}

		unsigned int numBones = fbxSkin->GetClusterCount();

		for (unsigned int boneIndex = 0; boneIndex < numBones; boneIndex++)
		{
			FbxCluster* fbxCluster = fbxSkin->GetCluster(boneIndex);
			// A line is a joint
			std::string boneName = fbxCluster->GetLink()->GetName();
			Bone* bone = skeleton->FindBoneByName(boneName);

			FbxAMatrix transformMatrix;
			FbxAMatrix transformLinkMatrix;
			FbxAMatrix globalBindposeInverseMatrix;

			fbxCluster->GetTransformMatrix(transformMatrix);
			fbxCluster->GetTransformLinkMatrix(transformLinkMatrix);
			globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;

			bone->fbxNode = fbxCluster->GetLink();
		}
	}
}

XMFLOAT4X4 Bone::GetBoneMatrix(unsigned int frame, FbxPose * fbxPose)
{
	return XMFLOAT4X4();
}

void VertexWeight::AddBoneData(unsigned int index, float weight)
{
}

void VertexWeight::Normalize()
{
}

Bone * Skeleton::FindBoneByName(std::string boneName)
{
	return nullptr;
}
