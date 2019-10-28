#include "player.h"

//constructor
Player::Player(int x,int y,int width,int height) : Sprite(x,y,width,height)
{
    std::int16_t initialHealth = 100;
    
    Player::setHealth(initialHealth);
    
    Player::setPlayerState(Player::PlayerState::NORMAL);
    Player::setupPlayerCollisionObject();
    
    Player::resetLoopCount();
    clipPlayer.w = 35; clipPlayer.h = 31;
    
    //set where head is facing
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_X] = 0.0f; //forward vector x value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Y] = 0.0f; //forward vector y value
	listener_orientation_vector[ORIENTATION_INDEX::FORWARD_Z] = 1.0f; //forward vector z value
	//set direction of top of head surface vector
	listener_orientation_vector[ORIENTATION_INDEX::UP_X] = 0.0f; //up vector x value
	listener_orientation_vector[ORIENTATION_INDEX::UP_Y] = 1.0f; //up vector y value
	listener_orientation_vector[ORIENTATION_INDEX::UP_Z] = 0.0f; //up vector z value
}

Player::~Player()
{
    //std::cout << "\n Player destructor called! \n";
}

void Player::setPlayerState(Player::PlayerState thisState){playerState = thisState;}
Player::PlayerState Player::getPlayerState(){return playerState;}

void Player::setupPlayerCollisionObject()
{
    CollisionBoxOwnerType type = CollisionBoxOwnerType::PLAYER;
    Player::setOwnerTypeOfCollisionObject(type);
}

void Player::setSpeed(float& speed){Sprite::setSpeed(speed);}

void Player::setPosX(float& x){Sprite::setPosX(x);}

void Player::setPosY(float& y){Sprite::setPosY(y);}

void Player::setVelX(float& dx){Sprite::setVelX(dx);}

void Player::setVelY(float& dy){Sprite::setVelY(dy);}

bool Player::loadMedia(LTexture* thisTex, std::string path,SDL_Renderer* gRenderer)
{
    return Sprite::loadMedia(&playerTexture,path,gRenderer);
}

void Player::setPointerToTexture(LTexture* thisTex){Sprite::setPointerToTexture(thisTex);}

LTexture* Player::getPointerToTexture(){return Sprite::getPointerToTexture();}

void Player::handleEvent(Event& thisEvent)
{
    Sprite::handleEvent(thisEvent);
    
    //if equipped weapon is not pointing to nullptr
    if(equippedPlayerWeapon != nullptr)
    {
        switch(thisEvent)
        {
            case Event::SPACE:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED); break;}
            case Event::SPACE_REPEAT:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
            case Event::SPACE_RELEASE:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
            default:{  break;}
        }
    }
    
}

void Player::setPlace(std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    Sprite::setPlace(screenWidth,screenHeight);
}

void Player::setSpriteClips(std::vector <SDL_Rect> *this_clips){Sprite::setSpriteClips(this_clips);}

std::vector <SDL_Rect> *Player::getSpriteClips(){return Sprite::getSpriteClips();}


void Player::setCamera( SDL_Rect& camera  ) //set camera relative to dot and intialize screen and level dimensions
{
	Sprite::setCamera(camera);
}

void Player::move(float& timeStep){Sprite::move(timeStep);}

bool Player::moveOnTiles(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    //if sprite is not moving on tiles and is colliding with wall
    if(!Sprite::moveOnTiles(timeStep, dungeonTiles))
    {
        Player::setPlayerState(Player::PlayerState::COLLIDING_CONTRA_WALL);
        return false;
    }
    else{return true;}
}

DungeonTile::TileType Player::moveOnTiles_TileType(float& timeStep, std::vector<DungeonTile*> &dungeonTiles)
{
    //return tile type dot touches
    DungeonTile::TileType tileType =  Sprite::moveOnTiles_TileType(timeStep,dungeonTiles);
    
    if(tileType == DungeonTile::TileType::TOP_LEFT || tileType == DungeonTile::TileType::LEFT 
        || tileType == DungeonTile::TileType::BOTTOM_LEFT || tileType == DungeonTile::TileType::TOP || 
        tileType == DungeonTile::TileType::BOTTOM ||
        tileType == DungeonTile::TileType::TOP_RIGHT || tileType == DungeonTile::TileType::RIGHT || 
        tileType == DungeonTile::TileType::BOTTOM_RIGHT 
        || tileType == DungeonTile::TileType::INVISIBLE_WALL)
    {
        Player::setPlayerState(Player::PlayerState::COLLIDING_CONTRA_WALL);
    }
    
    
    return tileType;
}

void Player::moveBack(float& timeStep)
{
    Sprite::moveBack(timeStep);
}

void Player::faceNorth(){Sprite::faceNorth();}

void Player::faceSouth(){Sprite::faceSouth();}

void Player::faceWest(){Sprite::faceWest();}

void Player::faceEast(){Sprite::faceEast();}

void Player::setSpriteState(Sprite::State state){Sprite::setSpriteState(state);}
Sprite::State Player::getSpriteState(){return Sprite::getSpriteState();}

void Player::incrementFrameCount(){Sprite::incrementFrameCount();}
std::int8_t Player::getFrameCount(){return Sprite::getFrameCount();}
void Player::resetFrameCount(){Sprite::resetFrameCount();}

void Player::setFrameOffset(std::int8_t& thisOffset){Sprite::setFrameOffset(thisOffset);}
std::int8_t Player::getFrameOffset(){return Sprite::getFrameOffset();}

void Player::setNumberOfAnimationFrames(std::int8_t& numFrames){Sprite::setNumberOfAnimationFrames(numFrames);}
std::int8_t Player::getNumberOfFramesOfAnimation(){return Sprite::getNumberOfFramesOfAnimation();}

void Player::setClipToShow(SDL_Rect* clip){ Sprite::setClipToShow(clip);}
SDL_Rect* Player::getClipToShow(){return Sprite::getClipToShow();}

void Player::render(SDL_Rect& camera, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    
    if(Player::getPlayerState() != PlayerState::FALLING_IN_HOLE){Sprite::render(camera,gRenderer,clip); }
    else{Sprite::render(camera,gRenderer,&clipPlayer);}
    
    
    //render collision box of player
    //Player::renderPlayerCollisionBox(camera,gRenderer);
    
    Player::renderEquippedWeapon(camera,gRenderer);
}


void Player::renderPlayerCollisionBox(SDL_Rect& camera,SDL_Renderer* gRenderer)
{
	SDL_SetRenderDrawColor(gRenderer,
                           200,
                           0,
                           0,
                           50);
    
    SDL_Rect pBox = {  Player::getCollisionBox().x - camera.x ,
                         Player::getCollisionBox().y - camera.y ,
                        Player::getCollisionBox().w,
                        Player::getCollisionBox().h };
    SDL_RenderDrawRect(gRenderer,&pBox);
}
    
float Player::getPosX(){return Sprite::getPosX();}

float Player::getPosY(){return Sprite::getPosY();}

int Player::getHeight(){return Sprite::getHeight();}

int Player::getWidth(){return Sprite::getWidth();}

float Player::getVelX(){return Sprite::getVelX();}

float Player::getVelY(){return Sprite::getVelY();}

float Player::getSpeed(){return Sprite::getSpeed();}

void Player::placeChar(int x, int y){Sprite::placeChar(x,y);}

void Player::setCollisionBox(SDL_Rect& box){Sprite::setCollisionBox(box);}

SDL_Rect& Player::getCollisionBox(){return Sprite::getCollisionBox();}

SDL_Rect& Player::getSpaceBox(){return Sprite::getSpaceBox();}

//Collision object Functions

void Player::setOwnerTypeOfCollisionObject(CollisionBoxOwnerType& oType)
{
    Sprite::setOwnerTypeOfCollisionObject(oType);
}
void Player::resetCollisionType(){Sprite::resetCollisionType();}
CollisionType Player::getCollisionType(){return Sprite::getCollisionType();}

CollisionObject* Player::getCollisionObjectPtr(){return Sprite::getCollisionObjectPtr();}

//Health

void Player::setHealth(std::int16_t& thisHP){health = thisHP;}
std::int16_t Player::getHealth(){return health;}
std::int16_t& Player::getHealthAddress(){return health;}
void Player::incrementHealth(std::int16_t& amount){health += amount;}
void Player::decrementHealth(std::int16_t& amount){health -= amount;}

//Weapon

void Player::renderEquippedWeapon(SDL_Rect& camera, SDL_Renderer* gRenderer)
{
    if(equippedPlayerWeapon != nullptr)
    {
        equippedPlayerWeapon->render(camera, gRenderer, nullptr);
    }
}

void Player::logic(float& timeStep)
{
	//listener change orientation logic
	
	
	//collsion logic
	Player::reactToCollision(timeStep);
	
    switch(Player::getPlayerState())
    {
        case Player::PlayerState::COLLIDING_CONTRA_WALL:{Player::runLogicState_CollideWithWall(timeStep); break;}
        case Player::PlayerState::NORMAL:{Player::runLogicState_Normal(timeStep); break;}
        case Player::PlayerState::PUSHED_BACKED_BY_ENEMY:{Player::runLogicState_PushedBack(timeStep); break;}
        case Player::PlayerState::FALLING_IN_HOLE:{Player::decrementHealth(cockroachDamage); break;}
    }
    
    //increment loop count
    Player::incrementLoopCount();
    if(Player::getLoopCount() > 20){Player::resetLoopCount();}
}

void Player::runLogicState_CollideWithWall(float& timeStep)
{
    float zeroVelocity = 0;
    
    Player::moveBack(timeStep);
    Player::setVelX(zeroVelocity); Player::setVelY(zeroVelocity);
    //set player state back to normal
    Player::setPlayerState(PlayerState::NORMAL);
}

void Player::runLogicState_Normal(float& timeStep)
{
    //if equipped weapon is not pointing to nullptr
    if(equippedPlayerWeapon != nullptr)
    {
        Player::runEquippedWeaponLogic(timeStep);
    }
}

void Player::runLogicState_PushedBack(float& timeStep)
{
    //if count of times player has been pushed back is less than number of times 
    //player has to be pushed back
    if( Player::getCountPushBack() < Player::getNumTimesPushBackPlayer())
    {
        Player::pushBackPlayer(timeStep,onePushBack); //get pushed back
        Player::incrementCountPushBack();
    }
    //else set player state back to normal and reset count
    else
    {
        Player::setPlayerState(PlayerState::NORMAL); 
        Player::resetCountPushBack();
    }
}

void Player::runEquippedWeaponLogic(float& timeStep)
{
    bool weaponActivated = false;
    
    //if weapon is not in state where weapon is activated
    if(equippedPlayerWeapon->getWeaponState() != Weapon::WeaponState::STAND_WITH_HANDLER_ACTIVATED)
    {
        //set weapon state based on sprite state
        switch(Player::getSpriteState())
        {
            case Sprite::State::STAND:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION); break;}
            case Sprite::State::WALK:{ equippedPlayerWeapon->setWeaponState(Weapon::WeaponState::MOVING_WITH_HANDLER_NO_ACTION); break;}
            default:{ break;}
        }
        
        weaponActivated = true;
    }
    
    
    //set direction weapon is facing to direction player is facing
    switch(Player::getFaceDirection())
    {
        case Player::FaceDirection::NORTH:
        {
            equippedPlayerWeapon->faceWeaponNorth(); break;
        }
        case Player::FaceDirection::NORTHEAST:
        {
            equippedPlayerWeapon->faceWeaponNorthEast(); break;
        }
        case Player::FaceDirection::EAST:
        {
            equippedPlayerWeapon->faceWeaponEast(); break;
        }
        case Player::FaceDirection::SOUTHEAST:
        {
            equippedPlayerWeapon->faceWeaponSouthEast(); break;
        }
        case Player::FaceDirection::SOUTH:
        {
            equippedPlayerWeapon->faceWeaponSouth(); break;
        }
        case Player::FaceDirection::SOUTHWEST:
        {
            equippedPlayerWeapon->faceWeaponSouthWest(); break;
        }
        case Player::FaceDirection::WEST:
        {
            equippedPlayerWeapon->faceWeaponWest(); break;
        }
        case Player::FaceDirection::NORTHWEST:
        {
            equippedPlayerWeapon->faceWeaponNorthWest(); break;
        }
    }
    
    equippedPlayerWeapon->logic(timeStep);
}

void Player::reactToCollision(float& timeStep)
{
    //reset count push back
    //count_PushBackPlayer = 0;
    switch(Player::getCollisionType())
    {
        
        case CollisionType::NONE:{ break;} // Do Nothing
        
        case CollisionType::HIT_BY_COCKROACH:
        {
			//std::cout << "Collision with cockroach! \n" << std::endl;
            Player::decrementHealth(cockroachDamage); //decrease health
            
            //put in state of push back
            Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
            std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
            Player::setNumTimesPushBackPlayer(numTimes);
            
            break;
        }
        case CollisionType::HIT_BY_ZOMBIE:
        {
			//std::cout << "Collision with cockroach! \n" << std::endl;
            Player::decrementHealth(greedZombieDamage); //decrease health
            
            //put in state of push back
            Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
            std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
            Player::setNumTimesPushBackPlayer(numTimes);
            
            break;
        }
        case CollisionType::COLLIDING_WITH_HOLE:
        {
            Player::decrementHealth(cockroachDamage);
            Player::setPlayerState( PlayerState::FALLING_IN_HOLE);
            break;
        }
        
        default:{break;}
    }
    
    if(equippedPlayerWeapon != nullptr)
    {
		if(equippedPlayerWeapon->getCollisionObjectPtr()->typeOfCollision == CollisionType::HIT_BY_COCKROACH)
		{
			if(equippedPlayerWeapon->getWeaponState() == Weapon::WeaponState::STAND_WITH_HANDLER_NO_ACTION
			 || equippedPlayerWeapon->getWeaponState() == Weapon::WeaponState::MOVING_WITH_HANDLER_NO_ACTION)
			 {
				Player::decrementHealth(cockroachDamage); //decrease health

				//put in state of push back
				Player::setPlayerState(Player::PlayerState::PUSHED_BACKED_BY_ENEMY);
				std::int8_t numTimes = cockroach_PushBackHero / onePushBack; 
				Player::setNumTimesPushBackPlayer(numTimes);
			 }
		}
	}
    
    Player::resetCollisionType();
}

void Player::pushBackPlayer(float& timeStep,std::int16_t& pushBackDist)
{
    float velX = Player::getVelX();
    float velY = Player::getVelY();
    
    float newPosX, newPosY;
    //if going right, push left
    if(velX > 0){newPosX = Player::getPosX() - pushBackDist - (velX * timeStep);}
    //else if going left, push right
    else if(velX < 0){newPosX = Player::getPosX() + pushBackDist - (velX * timeStep);}
    else if(velX == 0){newPosX = Player::getPosX() + pushBackDist;}
    
    Player::setPosX(newPosX);
    
    //if going down, push up
    if(velY > 0){newPosY = Player::getPosY() - pushBackDist - (velY * timeStep);}
    //else if going up, push down
    else if(velY < 0){newPosY = Player::getPosY() + pushBackDist - (velY * timeStep);}
    else if(velY == 0){newPosY = Player::getPosY() + pushBackDist; }

    Player::setPosY(newPosY);
}

void Player::setNumTimesPushBackPlayer(std::int8_t& thisNum){numTimes_pushBackPlayer = thisNum;}
std::int8_t Player::getNumTimesPushBackPlayer(){return numTimes_pushBackPlayer;}
void Player::resetNumTimesPushBackPlayer(){numTimes_pushBackPlayer = 0;}

void Player::incrementCountPushBack(){countPushBack += 1;}
std::int8_t Player::getCountPushBack(){return countPushBack;}
void Player::resetCountPushBack(){countPushBack = 0;}

void Player::incrementLoopCount(){loopCount++;}
std::int8_t Player::getLoopCount(){return loopCount;}
void Player::resetLoopCount(){loopCount = 0;}

void Player::MoveListener()
{
	
		
	//set current listener orientation
	alListenerfv(AL_ORIENTATION, listener_orientation_vector.data());
	
	//Initialize Listener speed
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);//is not moving in 3d space
	
	//initialize listener position
	alListener3f(AL_POSITION, 
					listener_position_vector[POSITION_INDEX::X], 
					listener_position_vector[POSITION_INDEX::Y], 
					listener_position_vector[POSITION_INDEX::Z]);
}

void Player::SetListenerDirection()
{
	switch(Player::getFaceDirection())
    {
        case Player::FaceDirection::NORTH:
        {
            equippedPlayerWeapon->faceWeaponNorth(); break;
        }
        case Player::FaceDirection::NORTHEAST:
        {
            equippedPlayerWeapon->faceWeaponNorthEast(); break;
        }
        case Player::FaceDirection::EAST:
        {
            equippedPlayerWeapon->faceWeaponEast(); break;
        }
        case Player::FaceDirection::SOUTHEAST:
        {
            equippedPlayerWeapon->faceWeaponSouthEast(); break;
        }
        case Player::FaceDirection::SOUTH:
        {
            equippedPlayerWeapon->faceWeaponSouth(); break;
        }
        case Player::FaceDirection::SOUTHWEST:
        {
            equippedPlayerWeapon->faceWeaponSouthWest(); break;
        }
        case Player::FaceDirection::WEST:
        {
            equippedPlayerWeapon->faceWeaponWest(); break;
        }
        case Player::FaceDirection::NORTHWEST:
        {
            equippedPlayerWeapon->faceWeaponNorthWest(); break;
        }
    }
}
