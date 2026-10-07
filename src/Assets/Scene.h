#pragma once

class Scene
{
public:

	void Run();

	virtual void OnCreate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestroy() = 0;

private:
};