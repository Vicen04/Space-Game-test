#pragma once
#include "EngineSceneManager.h"

/// <summary>
/// Handles all engine related calls
/// </summary>
class EngineManager
{
public:
	std::shared_ptr<EngineSceneManager> GetSceneManager() { return engineSceneManager; }

	void Start();
	void Update(float deltaTime);
	void InitWindow(int argc, char* argv[]);

	EngineManager(int argc, char* argv[]);
	~EngineManager();

private:
    std::shared_ptr<EngineSceneManager> engineSceneManager;
};