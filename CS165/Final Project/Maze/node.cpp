#include "node.h"

//Constructor
node::node(char x) { //######## Requirement #14 ########
	roomId = x;
}
node::node(){

}
//Setting the roomId
void node::setRoomId(char x) {
	roomId = x;
}
//Getting the roomId
char node::getRoomId(void) {
	return roomId;
}
//Setting the Bool Values
void node::setNorthBool(bool x) {
	northNeighbor = x;
}
void node::setSouthBool(bool x) {
	southNeighbor = x;
}
void node::setEastBool(bool x) {
	eastNeighbor = x;
}
void node::setWestBool(bool x) {
	westNeighbor = x;
}
//Getting the Bool Values
bool node::getNorthBool() {
	return northNeighbor;
}
bool node::getSouthBool() {
	return southNeighbor;
}
bool node::getEastBool() {
	return eastNeighbor;
}
bool node::getWestBool() {
	return westNeighbor;
}
//Setting the Neighbor Values
void node::setNorth(node *x) {
	north = x;
}
void node::setSouth(node *x) {
	south = x;
}
void node::setEast(node *x) {
	east = x;
}
void node::setWest(node *x) {
	west = x;
}
//Setting the Neighbor Values
node* node::getNorth() {
	return north;
}
node* node::getSouth() {
	return south;
}
node* node::getEast() {
	return east;
}
node* node::getWest() {
	return west;
}