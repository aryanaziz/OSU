/**********
** Program: A15E1.cpp
** Author: Aryan Aziz
** Description: 
** Input: 
** Output: 
**********/

#include <iostream>

class node {
	public:
		//Getting the actual Neighbors
		node* getNorthNeighbor(void) {
			return northNeighbor;
		}
		node* getSouthNeighbor(void) {
			return southNeighbor;
		}
		node* getEastNeighbor(void) {
			return eastNeighbor;
		}
		node* getWestNeighbor(void) {
			return westNeighbor;
		}

		//Setting the actual Neighbors
		void setNorthNeighbor(node *x) {
			northNeighbor = x;
		}
		void setSouthNeighbor(node *x) {
			southNeighbor = x;
		}
		void setEastNeighbor(node *x) {
			eastNeighbor = x;
		}
		void setWestNeighbor(node *x) {
			westNeighbor = x;
		}

		//Getting the existence of the Neighbors
		bool doesNorthNeighborExist(void) {
			return northNeighborExist;
		}
		bool doesSouthNeighborExist(void) {
			return southNeighborExist;
		}
		bool doesEastNeighborExist(void) {
			return eastNeighborExist;
		}
		bool doesWestNeighborExist(void) {
			return westNeighborExist;
		}

		//Setting the existence of the Neighbors
		void setNorthNeighborBool(bool x) {
			northNeighborExist = x;
		}
		void setSouthNeighborBool(bool x) {
			southNeighborExist = x;
		}
		void setEastNeighborBool(bool x) {
			eastNeighborExist = x;
		}
		void setWestNeighborBool(bool x) {
			westNeighborExist = x;
		}
	private:
		bool northNeighborExist;
		bool southNeighborExist;
		bool eastNeighborExist;
		bool westNeighborExist;
		node *northNeighbor;
		node *southNeighbor;
		node *eastNeighbor;
		node *westNeighbor;		
};

void initializeMaze(node x, bool north, bool south, bool east, bool west) {
	x.setNorthNeighborBool(north);
	x.setSouthNeighborBool(south);
	x.setEastNeighborBool(east);
	x.setWestNeighborBool(west);
	//a.setSouthNeighbor(&e);
	//a.setEastNeighbor(&b);

	//std::cout << a.getSouthNeighbor()->doesSouthNeighborExist();

	std::cout << x.doesNorthNeighborExist();
}

void setNeighbors(node x, node *north, node *south, node *east, node *west){
	x.setNorthNeighbor(north);
	std::cout << x.getNorthNeighbor() << std::endl;

};

int main() {

	node a,b,c,d,e,f,g,h,i,j,k,l;

	initializeMaze(a, true, true, false, false);
	setNeighbors(a, &i, &e, &b, &d);
		std::cout << a.getNorthNeighbor();

	return 0;
}