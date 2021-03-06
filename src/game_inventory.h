#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include "collisionhandler.h"
#include "weapons_loader.h" //for sprite sheet textures and clips of weapons
#include "player_inventory.h" //for passing weapons and items to player inventory


class GameInventory
{
public:
	GameInventory();
	~GameInventory();
	
	void SetPointerToPlayerInventory(PlayerInventory* thisInventory);
	void SetPointerToCollisionHandler(CollisonHandler* thisInventory);
	//function to setup a default sword for player to use in beginning
	//set near player
	void setupDefaultGunForPlayer(std::int16_t& x, std::int16_t& y);

	//function to check if weapon on ground state collided with Hero
	void checkWeaponsOnGround_Collision(PlayerInventory* p_inventory);

	//function to render weapons if on ground
	void run_weapons_render(SDL_Renderer* gRenderer, SDL_Rect& camera);

	//function to pass weapon to hero inventory
	void passWeaponToPlayerInventory(Weapon* thisWeapon);

	//function to free weapons in weapons array
	void freeWeapons();
private:
	//array to contain weapon pointers
	std::array <Weapon*,1> weaponsArray;
	
	PlayerInventory* m_player_inventory_ptr;
	
	CollisonHandler* m_collision_handler_ptr;
};





#endif
