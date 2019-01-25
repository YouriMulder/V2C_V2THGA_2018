#include "operator.hpp"

std::ifstream & operator>>(std::ifstream & input, sf::Vector2f & rhs) {
	std::string s;
	input >> s;
	bool x_fetched = false;
	bool negative = false;
	for (unsigned int index = 0; index < s.length(); index++) {
		if (s[index] == '(') {
			x_fetched = false;
		}
		else if (s[index] == ',') {
			x_fetched = true;
		}
		else if (s[index] == '-') {
			negative = true;
		}
		else if ((s[index] >= '0' && s[index] <= '9') && !x_fetched) {
			if (negative){
				rhs.x *= 10;
				rhs.x += ((int)s[index] - '0')*-1;
				negative = false;
			} else{
				rhs.x *= 10;
				rhs.x += (int)s[index] - '0';
			}
		}
		else if (s[index] >= '0' && s[index] <= '9' && x_fetched) {
			if (negative) {
				rhs.y *= 10;
				rhs.y += ((int)s[index] - '0')*-1;
				negative = false;
			} else {
				rhs.y *= 10;
				rhs.y += (int)s[index] - '0';
			}
		}
		else if (s[index] == ')') {
			return input;
		}
		/*else {
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw incorrect_coordinate(s);
		*/
	}
	return input;
}

std::ifstream & operator>>(std::ifstream & input, sf::IntRect & rhs) {
	char c;
	if (!(input >> c)) { /*throw endOfFile(_FILE, __LINE_);*/ }
	if (c != '(') { /*throw invalidPosition(c, _FILE, __LINE_);*/ }

	if (!(input >> rhs.left)) { /*throw invalidPosition(c, _FILE, __LINE_);*/ }
	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	if (!(input >> rhs.top)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	if (!(input >> rhs.width)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	if (!(input >> rhs.height)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }


	if (!(input >> c)) { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	if (c != ')') { /*throw invalidPosition(c, _FILE, __LINE_); */ }
	return input;
}

std::ostream &operator<<(std::ostream & lhs, const sf::Vector2f & rhs) {
	return lhs << "(" << rhs.x << "," << rhs.y << ") ";
}

std::ostream &operator<<(std::ostream & lhs, const sf::IntRect & rhs) {
	return lhs << "(" << rhs.left << "," << rhs.top << "," << rhs.width << "," << rhs.height << ") ";
}
