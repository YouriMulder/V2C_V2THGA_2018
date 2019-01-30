#ifndef SIDE_HPP
#define SIDE_HPP

enum class Side {
	Left,
	Right,
	Top,
	Bottom,
	NoSideDetected
};

///\brief
/// A struct that contains booleans to determine collision for each side.
struct CollisionSides {
	/// \brief
	/// Determines if there is collision on the left.
	bool left = false;
	/// \brief
	/// Determines if there is collision on the right.
	bool right = false;
	/// \brief
	/// Determines if there is collision on the bottom.
	bool bottom = false;
	/// \brief
	/// Determines if there is collision on the top.
	bool top = false;
};

#endif /*SIDE_HPP*/