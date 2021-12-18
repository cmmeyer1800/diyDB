#pragma once

#include <exception>

struct KeyNotFound : public std::exception{
	const char * what () const throw ();
};

struct DictOverflow : public std::exception{
	const char * what () const throw ();
};
