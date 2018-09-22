#ifndef GXNONCOPYABLE_H
#define GXNONCOPYABLE_H

namespace Gx
{

class NonCopyable
{
public:
    NonCopyable() = default;

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable &operator=(NonCopyable&) = delete;
};

}

#endif // GXNONCOPYABLE_H
