#pragma once
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include <d3d11_2.h>
#include <DirectXMath.h>

#include "Entity.hpp"

#include "TransformComponent.hpp"
#include "MaterialComponent.hpp"
#include "LightComponent.hpp"
#include "CameraComponent.hpp"
#include "MeshComponent.hpp"
#include "InstanceRendererSystem.hpp"

#include "Cube.hpp"
#include "VertexType.hpp"
#include "Constants.hpp"

// temp includes for demo
#include <random>

class World
{
	// Application State
	HWND _win32Window;

	int32_t _viewportWidth;
	int32_t _viewportHeight;

	// Entities
	std::vector<Entity> _entities;

	// Id Management
	int _nextEntityId = 1;
	int _nextComponentId = 1;
	int _nextPoolId = 1;

	// Storage -> Component Data
	std::vector<TransformComponent> _transformComponents;
	std::vector<MeshComponent> _meshComponents;
	std::vector<MaterialComponent> _materialComponents;
	std::vector<LightComponent> _lightComponents;
	std::vector<CameraComponent> _cameraComponents;

	// Storage -> Component Cache
	std::unordered_map<int, InstanceRendererSystem::InstancePool> _instancePools;

	// Storage -> Component Relations
	// entityId -> componentIndex
	std::unordered_map<int, int> _transformComponentIndices;
	std::unordered_map<int, int> _meshComponentIndices;
	std::unordered_map<int, int> _materialComponentIndices;
	std::unordered_map<int, int> _lightComponentIndices;
	std::unordered_map<int, int> _cameraComponentIndices;

	// Systems
	InstanceRendererSystem _instanceRenderer;

	// HLSL Constant Buffer Data
	LightConstantBuffer _lightConstantBufferData;
	PerFrameConstantBuffer _perFrameConstantBufferData{};
	CameraConstantBuffer _cameraConstantBufferData{};

public:
	// World loading and application management
	World();
	bool Initialize(HWND win32Window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void UpdateViewportDimensions(int32_t width, int32_t height);
	bool LoadWorld(std::string fileName = "");

	// Loops
	void Update(float deltaTime);
	void PeriodicUpdate(float deltaTime);
	void Render();
	
	// Entity-Component relations
	Entity CreateEntity();
	void AddComponent(int entityId, const TransformComponent& component);
	void AddComponent(int entityId, const MeshComponent& component);
	void AddComponent(int entityId, const MaterialComponent& component);
	void AddComponent(int entityId, const LightComponent& component);
	void AddComponent(int entityId, const CameraComponent& component);

	void RemoveComponent(int entityId, const TransformComponent& component);
	void RemoveComponent(int entityId, const MeshComponent& component);
	void RemoveComponent(int entityId, const MaterialComponent& component);
	void RemoveComponent(int entityId, const LightComponent& component);
	void RemoveComponent(int entityId, const CameraComponent& component);

	// Instance Rendering System

	void LinkRenderableInstancePool(const InstanceRendererSystem::InstancePool& instancePool);
	void AddRenderableInstance(int poolKey, int entityId, const InstanceConstantBuffer& instanceData);
	void UpdateRenderableInstanceData(int poolKey, int instanceIndex, const InstanceConstantBuffer& newData);
	void RemoveRenderableInstance(int poolKey, int instanceIndex);
	void RemoveAllRenderableInstances();

	void UpdateDirtyRenderableTransforms();

	std::vector<int> GetRenderableEntities(
		const std::unordered_map<int, int>& transformIndices,
		const std::unordered_map<int, int>& meshIndices,
		const std::unordered_map<int, int>& materialIndices
	) const;

};