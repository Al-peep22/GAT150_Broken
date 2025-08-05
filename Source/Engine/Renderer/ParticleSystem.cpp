#include "ParticleSystem.h"
#include "Renderer.h"

namespace viper {
	bool ParticleSystem::Initialize(int poolSize)
	{
		particles.resize(poolSize); // Reserve space for 1000 particles
		return true;
	}

	void ParticleSystem::ShutDown()
	{
		particles.clear(); // Clear the particle vector
	}

	void ParticleSystem::Update(float dt)
	{
		for (auto& particle : particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				particle.active = (particle.lifespan > 0);
				particle.prevPosition = particle.position;
				particle.position += particle.velocity * dt;
			}
		}
	}
	void ParticleSystem::Draw(Renderer& renderer)
	{
		for (auto& particle : particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.x, particle.color.y, particle.color.z);
				//renderer.DrawPoint(particle.position.x, particle.position.y);
				renderer.DrawLine(particle.position.x, particle.position.y, particle.prevPosition.x, particle.prevPosition.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle)
	{
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle) {
			*freeParticle = particle; // Copy the particle data to the free slot

			freeParticle->active = true; // Activate the particle
			freeParticle->color = particle.color; // Set the color
		}
		else {
			std::cerr << "No free particle slots available!" << std::endl;
		}
		particles.push_back(particle); 
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : particles) {
			if (!particle.active) {
				return &particle;
			}
		}
		return nullptr;
	}
}