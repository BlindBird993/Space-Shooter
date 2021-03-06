#pragma once

#include <windows.h>
#include <GL/glew.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Enemy.h"
#include "Camera.hpp"
#include "Bullets.h"
#include "Skybox.h"
#include "Water.h"
#include "AmmoGun.h"
#include "SOIL.h"

class GameManager : public SceneObject
{
public:
	GameManager();
	~GameManager();

	std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getSpaceShip();
	std::shared_ptr<Enemy> getEnemy();
	std::shared_ptr<Skybox> getSkybox();

	int count = 0;
	int score_ = 0;

	void addEnemies();
	void weaponFire();
	void enemyFire(std::shared_ptr<Enemy> enemy_);
	bool findCollSpaceShipVsEnemy(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Enemy> enemy);
	bool findCollEnemyVsBullets(std::shared_ptr<Enemy> enemy, std::shared_ptr<Bullets> bullets);
	bool findCollSpaceShipVsBullets(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Bullets> bullets);
	void handleCollEnemyVsBullets(std::vector <std::shared_ptr<Bullets>> bulletsArr, std::vector <std::shared_ptr<Enemy>> enemyArr);
	void handleCollSpaceshipVsBullets(std::shared_ptr<SpaceShip> spaceship, std::vector<std::shared_ptr<Bullets>> bulletsArr);

	void setCurrentTime(float time);
	void fire(std::string weapon);

	GLuint particleTexture_;
	std::shared_ptr<ParticlesEngineClass> particles_ptr;


protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:

	std::shared_ptr<BattleField> bf1_;
	std::shared_ptr<BattleField> bf2_;

	std::shared_ptr<SpaceShip> spaceship_;
	std::shared_ptr<Enemy> enemy_;
	std::shared_ptr<Camera> cam_;
	std::shared_ptr<Bullets> bullets_;
	std::shared_ptr<Skybox> skybox_;
	std::shared_ptr<Water> water_;

	std::vector< std::shared_ptr<Bullets> > bulletsArr_;
	std::vector< std::shared_ptr<Bullets> > enemyBulletsArr_;

	std::vector <std::shared_ptr<Enemy>> enemyArr_;
	std::vector <std::shared_ptr<Enemy>> attackingEnemyArr_;

	std::shared_ptr<AmmoGun> sun_;

	const int battlefieldWidth_ = 32;
	const int battlefieldHeight_ = 0;
	const int battlefieldDepth_ = 512;

	int enemyCounter_ = 0;


	float currentTime;
	float nextEnemy;
	const int secondsForEnemy = 5;

	float nextAmmoBox;
	const int secondsForAmmoBox = 10;

	float nextAmmoLaser;
	const int secondsForAmmoLaser = 10;

	float nextShooting;
	const float secondsForShooting = 0.5f;

	float nextShootingMachineGun;
	const float secondsForShootingMachineGun = 0.1f;
	float nextShootingLaser;
	const float secondsForShootingLaser = 0.0005f;
};

