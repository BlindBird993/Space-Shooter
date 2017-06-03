#include "GameManager.hpp"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);

  // Adding the camera to the scene
  cam_.reset(new Camera());
  this->addSubObject(cam_);

  //  matrix_.translate(0.0f, 0.0f, -99.0f);
  skybox_.reset(new Skybox(cam_));
  this->addSubObject(skybox_);

  bf1_.reset(new BattleField(battlefieldWidth_, battlefieldDepth_, battlefieldHeight_));
  this->addSubObject(bf1_);

  bf2_.reset(new BattleField(battlefieldWidth_, battlefieldDepth_, battlefieldHeight_));
  bf2_->setZpos(battlefieldDepth_);
  this->addSubObject(bf2_);

  spaceship_.reset(new SpaceShip(skybox_));
  this->addSubObject(spaceship_);

  enemy_.reset(new Enemy("ordinary",1,battlefieldWidth_,battlefieldDepth_));
  //enemy_->setWeapon(new MachineGun(9999));
  enemyArr_.push_back(enemy_);
  this->addSubObject(enemy_);

  koyomi_.reset(new AraragiKoyomiClass());
  this->addSubObject(koyomi_);

/*  coin_.reset(new Coin());
  this->addSubObject(coin_)*/

  water_.reset(new Water(skybox_));
  this->addSubObject(water_);

  ammogun_.reset(new AmmoGun(-100));
  this->addSubObject(ammogun_);



}

void GameManager::privateRender()
{
  // Nothing to render
	GLfloat light[] = { 0.f,100.f,0.f,1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, light);

	glEnable(GL_FOG);

	GLfloat fogColor[3] = { 0.5f,0.5f,0.5f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);

	glFogf(GL_FOG_START, 200.f);
	glFogf(GL_FOG_END, 1000.f);

	glHint(GL_FOG_HINT, GL_NICEST);
}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();
  //arrayCounter_1 = 1;

  if (bf1_->getMatrix()[3].z >= 512)
  {
	  bf1_->setZpos(2 * battlefieldDepth_);
  }
  if (bf2_->getMatrix()[3].z >= 512)
  {
	  bf2_->setZpos(2 * battlefieldDepth_);
  }
  if (water_->getMatrix()[3].z >= 512)
  {
	  water_->setZpos(battlefieldDepth_);
  }

  //if (spaceship_ != nullptr){
	 // this->matrix_[3][0] = spaceship_->getMatrix()[3][0] - 5;
	 // this->matrix_[3][1] = spaceship_->getMatrix()[3][1] - 10;
	 // this->matrix_[3][2] = spaceship_->getMatrix()[3][2] - 10;
	 ////cam_->setMatrix(glm::mat4(spaceship_->getMatrix());
  //}
//bullets remove
  for (int i = 0; i < bulletsArr_.size(); i++)
  {
	  if (bulletsArr_.at(i)->life_ == 0)
	  {
		  this->removeSubObject(bulletsArr_.at(i));
		  bulletsArr_.erase(bulletsArr_.begin() + i--);
	  }

  }

  //addEnemies();
  //for (int i = 0; i < bulletsArr_.size(); i++)
  //{
  //	if (bulletsArr_.at(i)->collFlag == true) {
  //	 
  //	 this->removeSubObject(bulletsArr_.at(i));
  //	 bulletsArr_.erase(bulletsArr_.begin() + i--);
  //	}
  //}


  //Enemy fire
  for (int i = 0; i < attackingEnemyArr_.size(); i++)
  {
	  enemyFire(attackingEnemyArr_.at(i));
  }
  
  for (int i = 0; i < enemyBulletsArr_.size(); i++)
  {

	  if ((enemyBulletsArr_.at(i)->life_ == 0))
	  {
		  this->removeSubObject(enemyBulletsArr_.at(i));
		  enemyBulletsArr_.erase(enemyBulletsArr_.begin() + i--);
	  }
	  else if (enemyBulletsArr_.at(i)->getPosition().z > battlefieldDepth_)
	  {
		  this->removeSubObject(enemyBulletsArr_.at(i));
		  enemyBulletsArr_.erase(enemyBulletsArr_.begin() + i--);//removing from array
	  }
  }
  //Enemy remove
  if (!(enemyArr_.empty())) {
	  for (int i = 0; i < enemyArr_.size(); i++)
	  {
		  auto boundary = enemyArr_.at(i)->getMatrix()[3].z;

		  if (findCollSpaceShipVsEnemy(spaceship_, enemyArr_.at(i))) {
			  //std::cout << "Foo" << std::endl;
			  this->removeSubObject(enemyArr_.at(i));
			  enemyArr_.erase(enemyArr_.begin() + i--);
		  }

		  if (boundary > battlefieldDepth_)
		  {
			  this->removeSubObject(enemyArr_.at(i));
			  enemyArr_.erase(enemyArr_.begin() + i--);
		  }
	  }
  }
  if (!(attackingEnemyArr_.empty())) {
	  for (int i = 0; i < attackingEnemyArr_.size(); i++)
	  {
		  auto boundary = attackingEnemyArr_.at(i)->getMatrix()[3].z;

		  if (boundary > battlefieldDepth_)
		  {
			  this->removeSubObject(attackingEnemyArr_.at(i));
			  attackingEnemyArr_.erase(attackingEnemyArr_.begin() + i--);
		  }
	  }
  }

  for (int i = 0; i < enemyBulletsArr_.size(); i++)
  {
	  auto boundary = enemyBulletsArr_.at(i)->getMatrix()[3].z;

	  if (boundary > battlefieldDepth_)
	  {
		  this->removeSubObject(enemyBulletsArr_.at(i));
		  enemyBulletsArr_.erase(enemyBulletsArr_.begin() + i--);
	  }
  }

handleCollEnemyVsBullets(bulletsArr_, enemyArr_);
handleCollEnemyVsBullets(bulletsArr_, attackingEnemyArr_);
handleCollAmmoVsBullets(ammogun_, bulletsArr_);
//std::cout << enemyArr_.size() << std::endl;
}

std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getSpaceShip()
{
	return spaceship_;
}

std::shared_ptr<Enemy> GameManager::getEnemy()
{
	return enemy_;
}

std::shared_ptr<Skybox> GameManager::getSkybox()
{
	return skybox_;
}

void GameManager::addEnemies()
{ 

	float speed = static_cast <float> (rand()% 3 + 1);
	int xStartPos = rand() % 32 + 20;
	//random start position
		enemy_ = std::make_shared<Enemy>(*(new Enemy("ordinary", speed, xStartPos, battlefieldDepth_)));

		// Every 5'th enemy has a weapon
		if (enemyCounter_ == 5)
		{
			enemy_->setAmmo(300);
			attackingEnemyArr_.push_back(enemy_);
			this->addSubObject(enemy_);
			//enemyArr_.push_back(enemy_);

			enemyCounter_ = 0;
		}
		else
		{
			this->addSubObject(enemy_);
			enemyArr_.push_back(enemy_);

			enemyCounter_++;
		}
		
}

void GameManager::weaponFire()
{
	auto weapon = spaceship_->getWeapon();

	if (spaceship_->shoot())
	{
		auto position = spaceship_->getMatrix();

		//std::cout << position[3][0]<<" "<< position[3][1] << std::endl;

		//weapon->shoot();																			// Lower ammo count of weapon
		bullets_ = std::make_shared<Bullets>(*(new Bullets(weapon, position,true, battlefieldDepth_)));		// "Create" bullet

		this->addSubObject(bullets_);														// Add bullets to the scene
		bulletsArr_.push_back(bullets_);
		//std::cout << arrayCounter_ << ' ' << std::endl;
	}



}

void GameManager::enemyFire(std::shared_ptr<Enemy> enemy_)
{
	auto weapon = enemy_->getWeapon();

	if (enemy_->shoot())
	{
		auto position = enemy_->getMatrix();

		//weapon->shoot();																			// Lower ammo count of weapon
		bullets_ = std::make_shared<Bullets>(*(new Bullets(weapon, position, false, battlefieldDepth_)));		// "Create" bullet

		this->addSubObject(bullets_);														// Add bullets to the scene
		enemyBulletsArr_.push_back(bullets_);
	}

}

bool GameManager::findCollSpaceShipVsEnemy(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Enemy> enemy)
{

	glm::vec3 obj1Pos = spaceship->getPos();
	glm::vec3 obj2Pos = enemy->getPos();

	auto radius1 = spaceship->getRadius();
	auto radius2 = enemy->getRadius();

	//if (obj2Pos[2] >= (battlefieldDepth_ - std::abs(radius1+obj1Pos[2]))) {
	//
	//	if ((std::abs(obj1Pos[0]) - std::abs(obj2Pos[0]) < radius1) && (std::abs(obj2Pos[1]) - std::abs(obj2Pos[1]) < radius1)) {

	//		return true;
	//	}
	//
	//}
	//return false;
	if (obj2Pos[2] >= (battlefieldDepth_ - std::abs(radius1 + std::abs(obj1Pos[2])))) {


		bool collX = (obj1Pos[0] + radius1 >= obj2Pos[0] && obj2Pos[0] + radius2 >= obj1Pos[0]);
		bool collY = (obj1Pos[1] + radius1 >= obj2Pos[1] && obj2Pos[1] + radius2 >= obj1Pos[1]);


		return (collX&&collY);


	}
	return false;

}

bool GameManager::findCollEnemyVsBullets(std::shared_ptr<Enemy> enemy, std::shared_ptr<Bullets> bullets)
{
if (enemy != nullptr && bullets != nullptr){
	glm::vec3 obj1Pos = bullets->getPos();
	glm::vec3 obj2Pos = enemy->getPos();

	auto radius1 = bullets->getRadius();
	auto radius2 = enemy->getRadius();

	//std::cout << obj1Pos[0] << " " << obj1Pos[1] << std::endl;

	if (obj2Pos[2] >= (battlefieldDepth_ - std::abs(radius1 + std::abs(obj1Pos[2])))) {


		bool collX = (obj1Pos[0] + radius1 >= obj2Pos[0] && obj2Pos[0] + radius2 >= obj1Pos[0]);
		bool collY = (obj1Pos[1] + radius1 >= obj2Pos[1] && obj2Pos[1] + radius2 >= obj1Pos[1]);


		return (collX&&collY);

	
	}
	return false;
	}
}

bool GameManager::findCollSpaceShipVsBullets(std::shared_ptr<SpaceShip> spaceship, std::shared_ptr<Bullets> bullets)
{
	return false;
}

bool GameManager::findCollAmmoVsBullets(std::shared_ptr<AmmoGun> ammo, std::shared_ptr<Bullets> bullets)
{
	glm::vec3 obj1Pos = bullets->getPos();
	glm::vec3 obj2Pos = ammo->getPos();

	auto radius1 = bullets->getRadius();
	auto radius2 = ammo->getRadius();

	if (std::abs(obj2Pos[2]) <= std::abs(radius1 + std::abs(obj1Pos[2]))) {


		bool collX = (obj1Pos[0] + radius1 >= obj2Pos[0] && obj2Pos[0] + radius2 >= obj1Pos[0]);
		bool collY = (obj1Pos[1] + radius1 >= obj2Pos[1] && obj2Pos[1] + radius2 >= obj1Pos[1]);


		return (collX&&collY);

	}
	return false;
}

void GameManager::handleCollEnemyVsBullets(std::vector<std::shared_ptr<Bullets>> bulletsArr, std::vector<std::shared_ptr<Enemy>> enemyArr)
{

	if (enemyArr.empty() != true) {

		for (int i = 0; i < bulletsArr.size(); i++) {
		
			for (int j = 0; j < enemyArr.size(); j++) {
			
				if (findCollEnemyVsBullets(enemyArr.at(j), bulletsArr.at(i))) {

					if (enemyArr.at(j)->life_ <= 0) {

						this->removeSubObject(enemyArr.at(j));

						enemyArr.erase(enemyArr.begin() + j--);
					}
					else {
						enemyArr.at(j)->life_ -= bulletsArr.at(i)->damage_;
						//std::cout << enemyArr.at(j)->life_ << std::endl;
					}
				}
			}
		}
		glFlush();

	}

}

void GameManager::handleCollAmmoVsBullets(std::shared_ptr<AmmoGun> ammo, std::vector<std::shared_ptr<Bullets>> bulletsArr)
{
	for (int i = 0; i < bulletsArr.size(); i++) {
		
		if (findCollAmmoVsBullets(ammo, bulletsArr.at(i))) {
			
			this->removeSubObject(ammo);
			spaceship_->reload();

				}
		}
		glFlush();
}

//void GameManager::handleCollEnemyVsBullets(std::shared_ptr<Bullets> bullets, std::vector<std::shared_ptr<Enemy>> enemyArr)
//{
//	
//}

