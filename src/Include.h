#pragma once
#include "imgui.h"
#include "imgui_impl/imgui_impl_glfw.h"
#include "imgui_impl/imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h> 
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <imgui_impl/imgui_impl_opengl3_loader.h>
#include <stb_image.h>

#include "Shaders.h"
#include "Utilities.h"
#include "Transform.h"
#include "Vertices.h"
#include "Camera.h"
#include "Skybox.h"
#include "Mesh.h"
#include "Model.h"
#include "Cube.h"

#include "Material.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"


#include "Object.h"
#include "DirectionLine.h"
#include "LightCube.h"
#include "DirectionalLightCube.h"
#include "PointLightCube.h"
#include "SpotLightCube.h"
#include "Lights.h"
#include "ParticleEmitter.h"
#include "Locomotive.h"
#include "Setup.h"


#include "Floor.h"
#include "Roof.h"
#include "House.h"
#include "Houses.h"
