#pragma once
#include <DirectXMath.h>
#include <cereal/cereal.hpp>
#include "ComponentIdentifier.hpp"


struct MaterialConstantBuffer
{
    DirectX::XMFLOAT4 ambient;
    DirectX::XMFLOAT4 diffuse;
    DirectX::XMFLOAT4 specular;
    float shininess;
    float padding[3] = { 0, 0, 0 };

    MaterialConstantBuffer();
    MaterialConstantBuffer(const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& diffuse, const DirectX::XMFLOAT4& specular, float shininess);
};

class MaterialComponent : public ComponentIdentifier
{
    MaterialConstantBuffer _materialConstantBuffer;
    bool _isDirty = true;
public:
    MaterialComponent();
	MaterialComponent(const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& diffuse, const DirectX::XMFLOAT4& specular, float shininess);
	MaterialComponent(int id, const DirectX::XMFLOAT4& ambient, const DirectX::XMFLOAT4& diffuse, const DirectX::XMFLOAT4& specular, float shininess);

    void SetAmbient(DirectX::XMFLOAT4 ambient);
    void SetDiffuse(DirectX::XMFLOAT4 diffuse);
    void SetSpecular(DirectX::XMFLOAT4 specular);
    void SetShininess(float shininess);

    DirectX::XMFLOAT4 GetAmbient() const;
    DirectX::XMFLOAT4 GetDiffuse() const;
    DirectX::XMFLOAT4 GetSpecular() const;
    float GetShininess() const;

    bool IsDirty() const;
    void SetIsDirty(bool isDirty);

    MaterialConstantBuffer GetMaterialConstantBuffer() const;

    static MaterialComponent GetDefaultMaterialComponent(int id);

    template<typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("_id", GetId()),
            CEREAL_NVP(_isDirty),
            cereal::make_nvp("ambient", _materialConstantBuffer.ambient),
            cereal::make_nvp("diffuse", _materialConstantBuffer.diffuse),
            cereal::make_nvp("specular", _materialConstantBuffer.specular),
            cereal::make_nvp("shininess", _materialConstantBuffer.shininess)
        );
    }
};

