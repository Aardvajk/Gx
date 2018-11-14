#ifndef GX_DEBUG_H
#define GX_DEBUG_H

#include <sstream>

namespace Gx
{

class Debug
{
public:
    ~Debug();

    template<typename T> Debug &operator<<(const T &t){ o << t; return *this; }

private:
    std::ostringstream o;
};

}

#endif // GX_DEBUG_H
