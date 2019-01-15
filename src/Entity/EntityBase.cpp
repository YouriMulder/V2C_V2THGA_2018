#include "EntityBase.hpp"

EntityBase::EntityBase() {

}

EntityBase::~EntityBase() {

}

void EntityBase::move(float deltaX, float deltaY) {
	mPosition.x += deltaX;
	mPosition.y += deltaY;
}