#include "Include.h"

int main(int, char**)
{
	Setup setup;
	
	Houses houses;
	houses.SetHouseCount(200 * 200);
	
	ParticleEmitter particles(1000);
	particles.transform.ChangePosition(glm::vec3(0.0f, 4.5f, 0.0f));
	setup.particleEmitter = &particles;

	Locomotive loco;
	loco.SetColor(255, 255, 255);
	loco.transform.ChangePosition(glm::vec3(30.0f, 3.0f, 30.0f));
	loco.transform.AddRotation(glm::vec3(0.0f, 90.0f, 0.0f));
	loco.SetParticleEmitter(&particles);
	Setup::SetLocomotive(&loco);
	setup.SetCube(loco.GetWindows());
	
	Skybox skybox;
	
	DirectionalLightCube dLightCube;
	SpotLightCube s1;
	SpotLightCube s2;
	loco.SetLights(&s1, &s2);

	DirectionalLightCube ddCube;
	ddCube.SetColor(255, 255, 255);
	ddCube.transform.ChangePosition(glm::vec3(0.0f, 20.0f, 0.0f));
	ddCube.SetRootTransform(Setup::GetRootTransform());
	setup.SetDirectionalLightCube(&ddCube);

	Floor floor;
	floor.SetColor(0, 0, 0);
	floor.SetScale(500);
	floor.transform.AddPosition(glm::vec3(300.0f, 0.0f, 300.0f));

	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 cameraPos;
	float dt = 1000.0f / ImGui::GetIO().Framerate;
	glEnable(GL_BLEND);
	
	while (!setup.shouldClose())
	{
		
		srand(time(NULL));
		dt = 1000.0f / ImGui::GetIO().Framerate;
		
		//Setup 
		setup.startRendering();
		projMatrix = setup.GetProjectionMatrix();
		viewMatrix = setup.GetCamera().GetViewMatrix();
		cameraPos = setup.GetCamera().Position;

		skybox.SetProjectionMatrix(projMatrix);
		skybox.SetViewMatrix(glm::mat4(glm::mat3(viewMatrix)));
		skybox.Draw();

		ddCube.SetViewMatrix(viewMatrix);
		ddCube.SetProjectionMatrix(projMatrix);
		ddCube.UpdateShaderLight(floor.GetShaders());
		ddCube.UpdateShaderLight(houses.GetShaders());
		ddCube.UpdateShaderLight(loco.GetShaders());
		//ddCube.Draw();

		loco.SetCameraPos(cameraPos);
		loco.SetProjectionMatrix(projMatrix);
		loco.SetViewMatrix(viewMatrix);
		loco.Draw();

		s1.UpdateShaderLight(floor.GetShaders());
		s1.UpdateShaderLight(houses.GetShaders());

		s2.UpdateShaderLight(floor.GetShaders(), "spotLights[1]");
		s2.UpdateShaderLight(houses.GetShaders(), "spotLights[1]");
		
		//Floor
		floor.SetProjectionMatrix(projMatrix);
		floor.SetViewMatrix(viewMatrix);
		floor.SetCameraPosition(cameraPos);
		floor.Draw();

		//Houses
		houses.SetProjectionMatrix(projMatrix);
		houses.SetViewMatrix(viewMatrix);
		houses.SetCameraPosition(cameraPos);
		houses.DrawHouses();
		
		particles.UpdateShader(projMatrix, viewMatrix, loco.GetModelMatrix());
		particles.DrawParticles(dt, cameraPos);

		setup.finishRendering();
	}

	setup.close();
	return 0;
}