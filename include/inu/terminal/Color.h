/** @file Color.hpp
 * @brief define color modifiers for text
*/



#ifndef INUCOLOR_H
#define INUCOLOR_H


#include <ostream>

namespace inu {
	/**
	 * Usage: 
	 *
	 * Red text for only one line:
	 * std::cout << FG_RED << "text" << FG_DEFAULT << std::endl;
	 *
	 * Green text with blue background for one line:
	 * std::cout << FG_GREEN << BG_BLUE << "TEXT" << FG_DEFAULT << BG_DEFAULT
	 * << std::endl;
	*/ 
	enum Color {
		FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
	};

}


std::ostream& operator<<(std::ostream& os, inu::Color color);





#endif
