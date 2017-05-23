#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Enemy.h"
#include "AraragiKoyomiClass.h"
#include "Camera.hpp"
#include "Bullets.h"
#include "Skybox.h"
#include "Water.h"

class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getSpaceShip();
	std::shared_ptr<Enemy> getEnemy();
	std::shared_ptr<Skybox> getSkybox();

	void addEnemies();
	void weaponFire();
	void enemyFire(std::shared_ptr<Enemy> enemy_);
	bool findCollSpaceShipVsEnemy(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Enemy> enemy);
	bool findCollEnemyVsBullets(std::shared_ptr<Enemy> enemy, std::shared_ptr<Bullets> bullets);
	bool findCollSpaceShipVsBullets(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Bullets> bullets);
	//void handleCollEnemyVsBullets(std::shared_ptr<Bullets> bullets, std::vector <std::shared_ptr<Enemy>> enemyArr);
	//void handleCollEnemyVsBullets(std::vector <std::shared_ptr<Bullets>> bulletsArr,std::shared_ptr<Enemy> enemy);
	void handleCollEnemyVsBullets(std::vector <std::shared_ptr<Bullets>> bulletsArr, std::vector <std::shared_ptr<Enemy>> enemyArr);

	template <typename T1, typename T2>
	inline bool findCollisions(T1 obj1, T2 obj2) {	
	};

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::shared_ptr<BattleField> bf_;
	std::shared_ptr<BattleField> bf1_;
	std::shared_ptr<BattleField> bf2_;

    std::shared_ptr<SpaceShip> spaceship_;
	std::shared_ptr<Enemy> enemy_;
	std::shared_ptr<AraragiKoyomiClass> koyomi_;
    std::shared_ptr<Camera> cam_;
	std::shared_ptr<Bullets> bullets_;
	std::shared_ptr<Skybox> skybox_;
	std::shared_ptr<Water> water_;

	std::vector< std::shared_ptr<Bullets> > bulletsArr_;
	std::vector< std::shared_ptr<Bullets> > enemyBulletsArr_;

	std::vector <std::shared_ptr<Enemy>> enemyArr_;
	std::vector <std::shared_ptr<Enemy>> attackingEnemyArr_;

	const int battlefieldWidth_ = 32;
	const int battlefieldHeight_ = 0;
	const int battlefieldDepth_ = 512;

	int enemyCounter_ = 0;
	int bfCounter_ = 0;
	//std::shared_ptr<ParticlesEngineClass> particles_ptr;
};

