namespace aziza { //######## Requirement #25 ########
	void initializeMaze(node *x, bool north, bool south, bool east, bool west) {
		x->setNorthBool(north); //######## Requirement #24 ########
		x->setSouthBool(south);
		x->setEastBool(east);
		x->setWestBool(west);
	}

	void initializeNeighbors(node *x, node *north, node *south, node *east, node *west) {
		x->setNorth(north);
		x->setSouth(south);
		x->setEast(east);
		x->setWest(west);
	}

	void generateBoard(int x, int y, node& z) {
    	boardArray[x][y] = z.getRoomId();
	}

	void getName(char* x) {
		name = std::string(x);
	}
}