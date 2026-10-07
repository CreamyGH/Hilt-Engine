#include "Core/Window.h"

#include "Graphics/OpenGLContext.h"
#include "Graphics/Renderer.h"

#include "Systems/TransformSystem.h"

#include "Core/TimeStep.h"
#include "Core/Input.h"

std::vector<Vertex> vertices{
	{
		glm::vec3(0.5f,  0.5f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(1.0f, 1.0f)
	},
	{
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(1.0f, 0.0f)
	},
	{
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(0.0f, 0.0f)
	},
	{
		glm::vec3(-0.5f,  0.5f, 0.0f),
		glm::vec3(0.0f),
		glm::vec2(0.0f, 1.0f)
	}
};

std::vector<uint32_t> indices{
	0, 1, 3,
	1, 2, 3
};


int main()
{
	WindowConfig winConfig
	{
		.title = "OpenGL-Sandbox",
		.width = 1024,
		.height = 612,
		.vSyncEnabled = true,
	};

	Window window(winConfig);

	OpenGLContext GLContext;
	GLContext.Init();
	GLContext.PrintInfo();

	std::shared_ptr<Mesh> testMesh = std::make_shared<Mesh>();

	testMesh->SetVertices(vertices);
	testMesh->SetIndices(indices);
	testMesh->Create();

	std::shared_ptr<Shader> basicShader = std::make_shared<Shader>();

	basicShader->AddShader("assets/shaders/basic_shader.vert", GL_VERTEX_SHADER);
	basicShader->AddShader("assets/shaders/basic_shader.frag", GL_FRAGMENT_SHADER);

	std::shared_ptr<Texture2D> testTexture = std::make_shared<Texture2D>();

	testTexture->LoadFromImage("assets/container.jpg");
	testTexture->AssignSlot(0);
	testTexture->Create();

	std::shared_ptr<Material> testMaterial = std::make_shared<Material>();
	
	testMaterial->SetShader(basicShader);
	testMaterial->SetTexture(testTexture);

	entt::registry registry;

	entt::entity object = registry.create();
	registry.emplace<RenderComponent>(object, testMesh, testMaterial);
	registry.emplace<TransformComponent>(object);
	TransformComponent& objTransform = registry.get<TransformComponent>(object);

	objTransform.position = glm::vec3(0.0f, 0.0f, -3.0f);
	objTransform.quaternion = glm::angleAxis(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	entt::entity cameraEntity = registry.create();
	registry.emplace<CameraComponent>(cameraEntity);
	registry.emplace<TransformComponent>(cameraEntity);

	CameraComponent& camera = registry.get<CameraComponent>(cameraEntity);
	TransformComponent& cameraTransform = registry.get<TransformComponent>(cameraEntity);

	Renderer renderer(winConfig.width, winConfig.height);
	renderer.SetCameraEntity(cameraEntity);

	TransformSystem transformSys;

	Input::Init(window.GetHandle());

	float sens = 0.3f;
	bool enableMouse = false;

	double speed = 5.0;

	while (window.IsOpened())
	{
		TimeStep::GameLoopStart();
		Input::GameLoopStart();

		std::cout << "FPS: " << TimeStep::GetFPS() << '\n';

		if (enableMouse) {
			camera.yawAngle += Input::GetMouseDeltaX() * sens;
			camera.pitchAngle += Input::GetMouseDeltaY() * -sens;
		}

		if (Input::IsMouseKeyDown(MOUSE_LEFT)
			&& Input::GetMousePosX() > 0.0
			&& Input::GetMousePosX() < window.GetWidth())
		{
			Input::DisableCursor();
			enableMouse = true;
		}

		if (Input::IsKeyDown(KEY_ESCAPE)) {
			Input::EnableCursor();
			enableMouse = false;
		}
		
		if (Input::IsKeyDown(KEY_W)) {
			cameraTransform.position += (camera.front * float(TimeStep::GetDeltaTime() * speed));
		}

		if (Input::IsKeyDown(KEY_S)) {
			cameraTransform.position += (camera.front * float(TimeStep::GetDeltaTime() * -speed));
		}

		if (Input::IsKeyDown(KEY_A)) {
			cameraTransform.position += (camera.right * float(TimeStep::GetDeltaTime() * -speed));
		}

		if (Input::IsKeyDown(KEY_D)) {
			cameraTransform.position += (camera.right * float(TimeStep::GetDeltaTime() * speed));
		}

		transformSys.Update(registry);
		renderer.RenderFrame(registry);

		window.Update();

		Input::GameLoopEnd();
		TimeStep::GameLoopEnd();
	}
}