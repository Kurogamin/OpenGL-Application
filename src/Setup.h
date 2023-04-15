#pragma once
#include "Include.h"

class Setup
{
private:
	const char* window_title = "Z4";
	const char* glsl_version = "#version 460";
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	int r = 0.0f;
	int g = 0.0f;
	int b = 0.0f;
	bool failed = false;
	GLFWwindow* window;
	Camera camera;
	const float screenWidth = 1680.0f;
	const float screenHeight = 1050.0f;
	float lastX = screenWidth / 2.0f;
	float lastY = screenHeight / 2.0f;
	bool firstMouse = true;
	bool lookAround = true;
	bool advSettings = false;
	glm::vec3 dir = glm::vec3(0.0f, -1.0f, 0.0f);
	float randomFloat = 0.0f;
	int option = -1;
	float clippingDistance = 2000.0f;
	bool driving = false;
public:
	Transform rootTransform;
	Lights* lights = nullptr;
	DirectionalLightCube* dirLightCube = nullptr;
	Cube* cube = nullptr;
	Locomotive* locomotive = nullptr;
	ParticleEmitter* particleEmitter = nullptr;
	static Setup* instance;
	void startRendering()
	{
		glEnable(GL_DEPTH_TEST);
		
		processInput(this->window);
		setupImGuiWindow();
		//camera.UpdateCameraVectors();
		ImGui::Render();

		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void finishRendering()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	Setup()
	{
		instance = this;
		initialize();
	}

	~Setup()
	{
		glfwTerminate();
		delete this;
	}

	static void SetCube(Cube* cube)
	{
		Setup::instance->cube = cube;
	}

	static void SetLocomotive(Locomotive* loco)
	{
		Setup::instance->locomotive = loco;
	}

	void close()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void SetClippingDistance(float value)
	{
		this->clippingDistance = value;
	}

	Camera GetCamera()
	{
		return this->camera;
	}

	bool shouldClose()
	{
		glfwPollEvents();
		return glfwWindowShouldClose(this->window);
	}

	void SetMovementSpeed(float value)
	{
		this->camera.MovementSpeed = value;
	}

	void SetPitch(float value)
	{
		this->camera.Pitch = value;
	}

	float GetZoom()
	{
		return this->camera.Zoom;
	}

	float GetScreenWidth()
	{
		return this->screenWidth;
	}
	
	float GetScreenHeight()
	{
		return this->screenHeight;
	}

	void SetLights(Lights* lights)
	{
		this->lights = lights;
	}

	static Transform* GetRootTransform()
	{
		return &instance->rootTransform;
	}

	glm::mat4 GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(camera.Zoom), screenWidth / screenHeight, 0.1f, clippingDistance);
	}

	glm::mat4 GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}
	
	void SetDirectionalLightCube(DirectionalLightCube* dirLightCube)
	{
		this->dirLightCube = dirLightCube;
	}

private:
	void initialize()
	{
		init_glfw();
		init_window();
		init_opengl();
		setupCallbacks();
		init_imgui();
	}

	void init_glfw()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
			this->failed = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	}

	void init_opengl()
	{
		bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (err)
		{
			spdlog::error("Failed to initialize OpenGL loader!");
			this->failed = true;
		}
		spdlog::info("Successfully initialized OpenGL loader!");
	}

	void init_imgui()
	{
		// Setup Dear ImGui binding
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		// Setup style
		ImGui::StyleColorsDark();
	}

	void init_window()
	{
		// Create window with graphics context
		this->window = glfwCreateWindow(screenWidth, screenHeight, window_title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			this->failed = true;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync
	}

	void setupCallbacks()
	{
		glfwSetErrorCallback(glfw_error_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}

	void setupImGuiWindow()
	{
		// Start the Dear ImGui frame
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.


		if (this->locomotive != nullptr)
		{
			this->locomotive->Gui();
		}
		
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}

	void RootTransformGui()
	{
		if (ImGui::CollapsingHeader("RootTransform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::Button("Close")) option = -1;
			if (ImGui::Button("Position")) option = 0;
			if (ImGui::Button("Rotation")) option = 1;
			if (ImGui::Button("Scale")) option = 2;
			
			switch (option)
			{
			case 0:
				ImGui::DragFloat3("Position", (float*)&this->rootTransform.pos);
				break;
			case 1:
				ImGui::DragFloat3("Rotation", (float*)&this->rootTransform.eulerRot);
				break;
			case 2:
				ImGui::DragFloat3("Scale", (float*)&this->rootTransform.scale);
				break;
			}
		}
		this->rootTransform.EnableDirtyFlag();
	}

	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			this->lookAround = !this->lookAround;
			this->driving = !this->driving;
		}
		
		if (!driving)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				camera.ProcessKeyboard(FORWARD);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				camera.ProcessKeyboard(BACKWARD);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				camera.ProcessKeyboard(LEFT);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				camera.ProcessKeyboard(RIGHT);
		}
		else
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				locomotive->ProcessKeyboard(FORWARD);
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				locomotive->ProcessKeyboard(BACKWARD);
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				locomotive->ProcessKeyboard(LEFT);
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				locomotive->ProcessKeyboard(RIGHT);
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
				locomotive->ProcessKeyboard(SPACE);
		}
	}

	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		if (!instance->lookAround)
		{
			return;
		}
		
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (instance->firstMouse)
		{
			instance->lastX = xpos;
			instance->lastY = ypos;
			instance->firstMouse = false;
		}

		float xoffset = xpos - instance->lastX;
		float yoffset = instance->lastY - ypos; // reversed since y-coordinates go from bottom to top

		instance->lastX = xpos;
		instance->lastY = ypos;

		instance->camera.ProcessMouseMovement(xoffset, yoffset);
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		instance->camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}
};

Setup* Setup::instance = nullptr;
