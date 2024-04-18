#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 15    

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::RandRange(-500.f, 500.f);
            location.Y = FMath::RandRange(-500.f, 500.f);
            location.Z = FMath::RandRange(1000.f, 2000.f);
            /*
            location.X = FMath::Sin(incr * i) * 400.f;
            location.Z = FMath::Cos(incr * i) * 400.f + 1000.f;
            */

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
    // Implement flocking by iterating over the Agents array
    for (int i = 0; i < Agents.Num(); i++) {
        AAgent* agent = Agents[i]; // Get the current agent
        FVector agentLocation = agent->GetActorLocation(); // Get the current agent's location
        FVector agentVelocity = agent->Velocity; // Get the current agent's velocity

        // Initialize vectors for alignment, cohesion, and separation
        FVector alignment = FVector(); // Boid wants to go in the same direction as other boids
        FVector cohesion = FVector(); // Boid wants to move towards the center of mass
        FVector separation = FVector(); // Boid wants to avoid other boids

        // Loop through all agents to calculate alignment, cohesion, and separation
        for (int j = 0; j < Agents.Num(); j++) {
            if (i != j) { // Exclude the current agent from calculations
                AAgent* otherAgent = Agents[j]; // Get the other agent
                FVector otherAgentLocation = otherAgent->GetActorLocation(); // Get the other agent's location
                FVector otherAgentVelocity = otherAgent->Velocity; // Get the other agent's velocity

                // Calculate alignment by summing up other agents' velocities
                alignment += otherAgentVelocity;

                // Calculate cohesion by summing up other agents' locations
                cohesion += otherAgentLocation;

                // Calculate separation by finding the vector pointing away from other agents
                separation += agentLocation - otherAgentLocation;
            }
        }

        // Divide alignment, cohesion, and separation by the number of agents (excluding the current agent)
        alignment /= Agents.Num() - 1;
        cohesion /= Agents.Num() - 1;
        separation /= Agents.Num() - 1;

        /*
        alignment = (alignment - agentVelocity);
        cohesion = (cohesion - agentLocation);
        separation = (separation - agentLocation);
        */


        // Update the agent's velocity by adding alignment, cohesion, and separation vectors
        agent->Velocity += alignment*0.125f + cohesion*0.03f + separation*0.6f;
        
        // TWEAK: Bounding Box
        /*
        float Xmin = -1000.f, Xmax = 1000.f;
        float Ymin = -1000.f, Ymax = 1000.f;
        float Zmin = 500.f, Zmax = 2500.f;

        // Check X bounds
        if (agentLocation.X < Xmin) {
            agent->Velocity.X = 100.f;
        }
        else if (agentLocation.X > Xmax) {
            agent->Velocity.X = -100.f;
        }

        // Check Y bounds
        if (agentLocation.Y < Ymin) {
            agent->Velocity.Y = 100.f;
        }
        else if (agentLocation.Y > Ymax) {
            agent->Velocity.Y = -100.f;
        }

        // Check Z bounds
        if (agentLocation.Z < Zmin) {
            agent->Velocity.Z = 100.f;
        }
        else if (agentLocation.Z > Zmax) {
            agent->Velocity.Z = -100.f;
        }
        */

        // TWEAK: Limiting the speed
        float maxSpeed = 20.f; // Maximum speed limit
        if (agent->Velocity.Size() > maxSpeed) {
            agent->Velocity = agent->Velocity.GetSafeNormal() * maxSpeed;
        }
    }
}

