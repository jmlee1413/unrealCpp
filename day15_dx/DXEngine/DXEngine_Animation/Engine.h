#pragma once
#include "DXApp.h"

class Engine : public DXApp
{
public:
	Engine(HINSTANCE hinstance);
	~Engine();

	bool Init() override;
	void ProcessInput(double deltaTime) override;
	void Update(double deltaTIme) override;
	void Render() override;
	void DrawMesh();

	void UpdateMesh(Mesh* mesh) override;

private:
	DIMOUSESTATE currentMouseState;
};

