#pragma once

class node {
	private:
		bool northNeighbor;
		bool southNeighbor;
		bool eastNeighbor;
		bool westNeighbor;
		node *north;
		node *south;
		node *east;
		node *west;
		char roomId;
	public:
		//Constructor
		node(char x);
		node();
		//Setting the roomId
		void setRoomId(char x);
		//Getting the roomId
		char getRoomId(void);
		//Setting the Bool Values
		void setNorthBool(bool x);
		void setSouthBool(bool x);
		void setEastBool(bool x);
		void setWestBool(bool x);
		//Getting the Bool Values
		bool getNorthBool();
		bool getSouthBool();
		bool getEastBool();
		bool getWestBool();
		//Setting the Neighbor Values
		void setNorth(node *x);
		void setSouth(node *x);
		void setEast(node *x);
		void setWest(node *x);
		//Setting the Neighbor Values
		node* getNorth();
		node* getSouth();
		node* getEast();
		node* getWest();
};