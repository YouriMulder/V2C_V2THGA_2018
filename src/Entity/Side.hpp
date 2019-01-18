#ifndef SIDE_HPP
#define SIDE_HPP

enum class Side {
		Left,
		Right,
		Top,
		Bottom,
		NoSideDetected
	};
struct CollisionSides {
	bool leftSide;
	bool rightSide;
	bool bottomSide;
	bool topSide;
};
#endif /*SIDE_HPP*/