#include "inu/terminal/Color.h"

std::ostream& operator<<(std::ostream& os, inu::Color color) {
	return os << "\033[" << static_cast<int>(color) << "m";
}
