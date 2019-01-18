#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

std::ifstream & operator>>(std::ifstream & input, sf::Vector2f & rhs);
std::ifstream & operator>>(std::ifstream & input, sf::IntRect & rhs);
std::ostream &operator<<(std::ostream & lhs, const sf::Vector2f & rhs);
std::ostream &operator<<(std::ostream & lhs, const sf::IntRect & rhs);

#endif /*OPERATOR_HPP*/