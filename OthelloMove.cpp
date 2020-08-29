#include "OthelloMove.hpp"

using namespace std;

bool OthelloMove::operator==(const OthelloMove &rhs) {
    
    return mPosition.GetRow() == rhs.mPosition.GetRow() && mPosition.GetCol() == rhs.mPosition.GetCol();
}

OthelloMove::operator std::string() const {
    
    ostringstream os;
    
    os << "(" << (int) mPosition.GetRow() << ", " << (int) mPosition.GetCol() << ")";
    
    return os.str();
}
