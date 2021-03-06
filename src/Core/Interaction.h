#pragma once

#include "Core/BSDF.h"
#include "Math/Ray.h"

#include <glm/glm.hpp>

#include <memory>

namespace Hikari
{
    class Primitive;

    class Interaction
    {
    public:
        Interaction() = default;

        Interaction(const glm::vec3& position) : m_Position(position) {}

        Interaction(
            const glm::vec3&    position,
            const glm::vec3&    normal,
            const glm::vec3&    wo,
            const glm::vec2&    uv,
            const Primitive*    primitive)
            : m_Position(position), m_Normal(normal), m_UV(uv), m_wo(wo), m_Primitive(primitive)
        {}

        Ray SpawnRayTo(const Interaction& i) const;

        Ray SpawnRay(const glm::vec3& direction) const;

        glm::vec3 Le() const;

        void ComputeScatteringFunctions();

        glm::vec3 m_Position, m_Normal, m_wo;
        glm::vec2 m_UV;

        // TODO(achal): Consider making it a shared_ptr.
        const Primitive* m_Primitive = nullptr;
        std::shared_ptr<BSDF> m_BSDF = nullptr;
    };

}   // namespace Hikari