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
	bool left = false;
	bool right = false;
	bool bottom = false;
	bool top = false;
};

#endif /*SIDE_HPP*/