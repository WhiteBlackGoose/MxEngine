#include "StaticRenderer.h"

void Additional::StaticEnvironment::Init()
{
	if (Width % ChunkWidth != 0 || Height % ChunkHeight != 0)
	{
		Logger::Instance().Error("MxEngine::Application", "chunks should be divisors of picture size");
		return;
	}
	auto chunkCountX = Width / ChunkWidth;
	auto chunkCountY = Height / ChunkHeight;
	viewports.resize(chunkCountX);
	for (size_t i = 0; i < chunkCountX; i++)
	{
		viewports[i].resize(chunkCountY);
		for (size_t j = 0; j < chunkCountY; j++)
		{
			auto cameraObject = MxObject::Create();
			cameraObject->Name = ToMxString(i * chunkCountX + j);
			auto controller = cameraObject->AddComponent<CameraController>();
			//viewports[i][j] = MxObject
		}
	}
}

void Additional::StaticEnvironment::OnUpdate()
{
	if (!isUpdateAlreadyCalled)
	{
		// We render the scene in the first frame
		isUpdateAlreadyCalled = true;
		Init();
	}
	else
	{
		// If one is already rendered, we allow the user to save the result
		//OnRender();
		this->CloseApplication();
	}	
}

void Additional::StaticEnvironment::SetChunkSize(size_t chunkWidth, size_t chunkHeight)
{
	ChunkWidth = chunkWidth;
	ChunkHeight = chunkHeight;
}

void Additional::StaticEnvironment::SetResolution(size_t desiredWidth, size_t desiredHeight)
{
	Width = desiredWidth;
	Height = desiredHeight;
}

void Additional::StaticEnvironment::SetDirection(const Vector3& direction)
{
	Direction = direction;
}

void Additional::StaticEnvironment::SetViewportAngle(const Vector2& newAngle)
{
	ViewportAngle = newAngle;
}