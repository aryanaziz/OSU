/**********
** Program: A14E2.cpp
** Author: Aryan Aziz
** Description: Convert game into classes. 
** Input: none
** Output: Game data. 
**********/

#include <iostream>
#include <string>
#include <cstdlib>

class Creature {
	protected:
		int type;
		int strength;
		int hitpoints;
		int damage;
	public:
		void setStrength(int x) {
			strength = x;
		};
		void setHitPoints(int x) {
			hitpoints = x;
		};
		int getStrength() {
			return strength;
		}
		int getHitPoints() {
			return hitpoints;
		}
		int getDamage() {
			damage = (rand( ) % strength) + 1; 
			return damage;
		};

};

class Demon : public Creature {
	public:
		int getDamage() {
			Creature::getDamage();
			if ((rand( ) % 100) < 5) { 
				damage = damage + 50; 
				std::cout << "Demonic attack inflicts 50 additional damage points!" << std::endl;
			}
			else {
				damage = damage;
			}
			return damage;
		};
		std::string getType() {
			return "Demon";
		};
};

class Cyberdemon : public Demon {
	public:
		Cyberdemon() {
			type = 1;
		};
		Cyberdemon(int x, int y) {
			type = 1;
			strength = x;
			hitpoints = y;
		};
		int getDamage() {
			Demon::getDamage();
			std::cout << "Cyberdemon Total Damage: " << damage << std::endl;
			return damage;
		};
		std::string getType() {
			return "Cyberdemon";
		};
};

class Balrog : public Demon {
	public:
		Balrog() {
			type = 1;
		};
		Balrog(int x, int y) {
			type = 2;
			strength = x;
			hitpoints = y;
		};
		int getDamage() {
			Demon::getDamage();
			int damage2 = (rand() % strength) + 1; 
			std::cout << "Balrog speed attack inflicts " << damage2 << " additional damage points!" << std::endl; 
			damage = damage + damage2; 

			std::cout << "Balrog Total Damage: " << damage << std::endl;
			return damage;
		};
		std::string getType() {
			return "Balrog";
		};
};

class Elf : public Creature {
	public:
		Elf() {
			type = 3;
		};
		Elf(int x, int y) {
			type = 3;
			strength = x;
			hitpoints = y;
		};
		int getDamage() {
			Creature::getDamage();
			if((rand() % 10) == 0) {
				std::cout << "Magical attack inflicts " << damage << " additional damage points!" << std::endl;
				damage = damage * 2;
			}
			else {
				damage = damage;
			}

			std::cout << "Elf Total Damage: " << damage << std::endl;
			return damage;
		}; 
		std::string getType() {
			return "Elf";
		};
};

class Human : public Creature {
	public:
		Human() {
			type = 0;
		};
		Human(int x, int y) {
			type = 0;
			strength = x;
			hitpoints = y;
		};
		int getDamage() {
			Creature::getDamage();
			std::cout << "Human Damage: " << damage << std::endl;
			return damage;
		}; 
		std::string getType() {
			return "Human";
		};
};


int main() {
	srand (time(NULL));

	std::cout << "##### Elf #####" << std::endl;
	Elf e(10, 10);
	Creature *creature1 = &e;
	creature1->setStrength(20);
	std::cout << "Strength: " << creature1->getStrength() << std::endl;
	for(int i = 0; i < 10; i++) {
		e.getDamage();
	};
	

	std::cout << std::endl;

	std::cout <<"##### Human #####" << std::endl;

	Human h(10,10);
	Creature *creature2 = &h;
	for(int i = 0; i < 10; i++) {
		h.getDamage();
	};

	std::cout << std::endl;

	std::cout << "##### Cyberdemon #####" << std::endl;

	Cyberdemon c(10,10);
	Creature *creature3 = &c;
	for(int i = 0; i < 10; i++) {
		c.getDamage();
	};

	std::cout << std::endl;

	std::cout << "##### Balrog #####" << std::endl;

	Balrog b(10,10);
	Creature *creature4 = &b;
	for(int i = 0; i < 10; i++) {
		b.getDamage();
	};


	return 0;
}