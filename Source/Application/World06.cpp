#include "World06.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>

namespace nc
{
    bool World06::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("Scenes/scene_framebuffer.json");
        m_scene->Initialize();

        auto texture = std::make_shared<Texture>();
        texture->CreateTexture(32, 32);
        ADD_RESOURCE("fb_texture", texture);

        auto framebuffer = std::make_shared<Framebuffer>();
        framebuffer->CreateFramebuffer(texture);
        ADD_RESOURCE("fb", framebuffer);

        auto material = GET_RESOURCE(Material, "materials/postprocess.mtrl");
        if(material)
        {
            material->albedoTexture = texture;
        }

        return true;
    }

    void World06::Shutdown()
    {
    }

    void World06::Update(float dt)
    {
        m_time += dt;

        ENGINE.GetSystem<Gui>()->BeginFrame();

        m_scene->Update(dt);
        m_scene->ProcessGui();

		//post process gui
		ImGui::Begin("Post Process");
        ImGui::SliderFloat("Blend", &m_blend, 0, 1);
        bool effect = m_params & INVERT_MASK;
      if(  ImGui::Checkbox("Invert", &effect))
      {
		  (effect) ? m_params |= INVERT_MASK : m_params ^= INVERT_MASK;
      }
      effect = m_params & GRAYSCALE_MASK;
      if (ImGui::Checkbox("GrayScale", &effect))
      {
          (effect) ? m_params |= GRAYSCALE_MASK : m_params ^= GRAYSCALE_MASK;
      }
        //set post process shader
		auto program = GET_RESOURCE(Program, "shaders/postprocess.prog");
        if (program)
        {
			program->Use();
            program->SetUniform("blend", m_blend); 
            program->SetUniform("params", m_params); 
        }
		ImGui::End();

        ENGINE.GetSystem<Gui>()->EndFrame();
    }

    void World06::Draw(Renderer& renderer)
    {
        // ** PASS 1
        m_scene->GetActorByName("postprocess")->active = false;

        auto framebuffer = GET_RESOURCE(Framebuffer, "fb");
        renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
        framebuffer->Bind();

        renderer.BeginFrame({ 0, 0, 0 }); //changes in the color for the frame
        m_scene->Draw(renderer);

        framebuffer->Unbind();

        // * PASS 2
        m_scene->GetActorByName("postprocess")->active = true;

        renderer.ResetViewport();
        renderer.BeginFrame();
        m_scene->GetActorByName("postprocess")->Draw(renderer);

        // post-render
        ENGINE.GetSystem<Gui>()->Draw();
        renderer.EndFrame();
    }
}