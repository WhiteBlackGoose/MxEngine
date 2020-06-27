#pragma once

#include <MxEngine.h>
#include <Library/Primitives/Colors.h>

namespace ProjectTemplate
{
    using namespace MxEngine;

    class MxApplication : public Application
    {
    public:
        void MakeCube(float x, float y, float z)
        {
            auto object = MxObject::Create();
            object->Transform->Translate(MakeVector3(x, y, z));
            object->Transform->RotateY(45.0f);
            auto meshSource = object->AddComponent<MeshSource>(Primitives::CreateCube());
            auto meshRenderer = object->AddComponent<MeshRenderer>();
            auto yellowColor = MakeVector3(1.0f, 0.7f, 0.0f);
            meshRenderer->GetMaterial()->DiffuseColor = yellowColor;
            meshRenderer->GetMaterial()->AmbientColor = yellowColor;
            meshRenderer->GetMaterial()->SpecularColor = yellowColor;
        }

        virtual void OnCreate() override
        {
            auto cameraObject = MxObject::Create();
            auto controller = cameraObject->AddComponent<CameraController>();
            controller->SetDirection(Vector3(0.0f, -0.333f, 1.0f));
            // controller->Rotate(50, 50);
            
            cameraObject->Transform->SetRotation(Vector3{ -30, 80, 0 });
            
            // set viewport to 8K
            RenderManager::SetViewport(controller);
            
            RenderManager::ResizeViewport(1920, 1080);
            RenderManager::GetController().SetViewport(1920 * 2 / 3, 1080 * 2 / 3,
                1920 * 1 / 3 - 1, 1080 * 1 / 3 - 1);

            MakeCube(0.f, -1.f, 3.f);
            MakeCube(-0.f,  1.f, -3.f);
            MakeCube(-0.f,  1.f,  3.f);
            MakeCube(-0.f, -1.f, -3.f);
            MakeCube(-5.f,  1.f, -3.f);
            MakeCube(-5.f,  1.f, -3.f);

            auto lightObject = MxObject::Create();
            auto dirLight = lightObject->AddComponent<DirectionalLight>();
            dirLight->Direction = MakeVector3(0.5f, 1.0f, -0.1f);
            dirLight->FollowViewport();
        }

        virtual void OnUpdate() override
        {
            static bool firstFrame = true;
            if (firstFrame)
            {
                firstFrame = false;
            }
            else
            {
                ImageManager::TakeScreenShot("D:/tmp/cube.png", ImageType::PNG);
                this->CloseApplication();
            }
        }

        virtual void OnDestroy() override
        {
            
        }
    };
}

int main()
{
    ProjectTemplate::MxApplication app;
    app.Run();
    return 0;
}