#include "enemy_inventory.h"

EnemyInventory::EnemyInventory()
{
	
}

EnemyInventory::~EnemyInventory()
{
	
}

void EnemyInventory::setupEnemyVector()
{
    enemies_vector.resize(90);
    
    //for all enemies
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
		if(i < 50)
		{
			//make it a cockroach
			OtherCockroach* thisCockroach = new OtherCockroach(4,2,55,65);
			thisCockroach->setPointersToMedia(&cockroach_texture,cockroach_walk_clips);
			
			enemies_vector[i] = thisCockroach;
		}
		else if(i >= 50 && i <= 70)
		{
			//make it a greedy zombie
			GreedyZombie* thisZombie = new GreedyZombie(4,2,55,65);
			thisZombie->setPointersToMedia(&greed_zombie_texture,greed_zombie_walk_clips);
			
			enemies_vector[i] = thisZombie;
		}
		else
		{
			//make it a cockroach
			OtherCockroach* thisCockroach = new OtherCockroach(4,2,55,65);
			thisCockroach->setPointersToMedia(&cockroach_texture,cockroach_walk_clips);
			
			enemies_vector[i] = thisCockroach;
		}
        
    }
    
}

std::vector <Enemy*> *EnemyInventory::GetEnemyVector(){return &enemies_vector;}

void EnemyInventory::run_enemies_handle_events(RNGType& rngSeed,SDL_Rect& camera)
{
    //for every enemy 
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
        //if enemy pointer isn't pointing to nullptr
        //means it is not dead
        if( enemies_vector[i] != nullptr)
        {
            //if enemy within camera
            if(checkCollision(camera,enemies_vector[i]->getCollisionBox() ) )
            {
                enemies_vector[i]->handleEvent_EnemyAI(rngSeed);
            }
        }
    }
}

void EnemyInventory::run_enemies_logic(float& timeStep,SDL_Rect& camera, 
                        std::vector <DungeonTile*> &labyrinthTilesVector)
{
    //for every enemy 
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
        //if enemy pointer isn't pointing to nullptr
        //means it is not dead
        if( enemies_vector[i] != nullptr)
        {
            //if enemy within camera
            if(checkCollision(camera,enemies_vector[i]->getCollisionBox() ) )
            {
                enemies_vector[i]->logic(timeStep,labyrinthTilesVector);
            }
        }
    }

}

void EnemyInventory::run_enemies_render(SDL_Rect& camera,SDL_Renderer* gRenderer )
{
    //for every enemy 
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
        //if enemy pointer isn't pointing to nullptr
        //means it is not dead
        if( enemies_vector[i] != nullptr)
        {
            //if enemy within camera
            if(checkCollision(camera,enemies_vector[i]->getCollisionBox() ) )
            {
                enemies_vector[i]->render(camera,gRenderer,nullptr);
            }
        }
        
    }
}

void EnemyInventory::run_enemies_sound(SDL_Rect& camera, AudioRenderer* gAudioRenderer)
{
	//for every enemy 
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
        //if enemy pointer isn't pointing to nullptr
        //means it is not dead
        if( enemies_vector[i] != nullptr)
        {
            //if enemy within camera
            if(checkCollision(camera,enemies_vector[i]->getCollisionBox() ) )
            {
                enemies_vector[i]->sound(gAudioRenderer);
            }
        }
        
    }
}

void EnemyInventory::checkAndRemoveDeadEnemies(SDL_Rect& camera)
{
    //for all enemies
    for(size_t i = 0; i < enemies_vector.size(); ++i)
    {
        //if pointer to enemy element is not pointing to nullptr
        if(enemies_vector[i] != nullptr)
        {
            //if enemy is within camera
            if( checkCollision(enemies_vector[i]->getCollisionBox(),camera ) )
            {
                //if enemy is dead
                if(enemies_vector[i]->getHealth() <= 0 )
                {
                    //free enemy
                    delete enemies_vector[i];
                    enemies_vector[i] = nullptr;
                }
            }
        }
        
    }
}

void EnemyInventory::freeEnemyVector()
{
    for(size_t i=0; i < enemies_vector.size(); ++i)
    {
        if(enemies_vector[i] != nullptr)
        {
			delete enemies_vector[i];
			enemies_vector[i] = nullptr;
		}
    }
}
