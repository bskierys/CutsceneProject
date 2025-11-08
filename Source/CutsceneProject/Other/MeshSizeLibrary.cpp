// Created by Bartłomiej Kierys

#include "MeshSizeLibrary.h"

float UMeshSizeLibrary::GetDungeonWallSizeFromMesh(const UStaticMesh* Mesh, const float DefaultSize)
{
	if (Mesh)
	{
		const FBoxSphereBounds Bounds = Mesh->GetBounds();
		return Bounds.BoxExtent.X * 2.0f;
	}
	return DefaultSize;
}
