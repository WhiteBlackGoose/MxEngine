#pragma once
#include <MxEngine.h>
#include <vector>

namespace Additional
{
	using namespace MxEngine;
	using namespace std;

	/*!
	Inherit from this class if you need a static render-mechanism
	for rendering static scenes in high-resolution or 
	*/
	class StaticEnvironment : protected Application
	{
	private:
		void OnUpdate() override;
		void Init();
		bool isUpdateAlreadyCalled = false;
		size_t Width = 1920;
		size_t Height = 1080;
		size_t ChunkWidth = 960;
		size_t ChunkHeight = 540;
		Vector3 Direction = { 0, 0, 0 };
		Vector2 ViewportAngle = { 60, 60 };
		GResource<Texture> Render();
		vector<vector<CameraController::Handle>> viewports;
	public:
		/*!
		Sets the angle of the camera
		*/
		void SetViewportAngle(const Vector2& newAngle);

		/*!
		Sets direction of the central ray from the camera
		*/
		void SetDirection(const Vector3& direction);

		/*!
		Sets the desired resultion of the result
		1920, 1080 are default parameters
		*/
		void SetResolution(size_t desiredWidth, size_t desiredHeight);
		
		/*!
		Sets the chunk's size, it's the size of tiles
		that the resulting image would consist of

		E. g. that's how image with size of 300x200 and with size of chunks of 100x100 
		would be rendered
		___________________
		|     |     |     |
		|     |     |     |
		-------------------
		|     |     |     |
		|     |     |     |
		-------------------

		Useful if need to render a big image with the lack of video-memory
		*/
		void SetChunkSize(size_t chunkWidth, size_t chunkHeight);

		/*!
		Override this function to make sure you call your render
		functions just once
		*/
		virtual void OnRender(const GResource<Texture>& renderedResult);
	};
}