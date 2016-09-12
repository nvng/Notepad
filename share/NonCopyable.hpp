#ifndef __NON_COPYABLE_HPP__
#define __NON_COPYABLE_HPP__

class NonCopyable
{
protected :
        NonCopyable() {}
        ~NonCopyable() {}

private :
        NonCopyable(const NonCopyable&) = delete;
        const NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif // __NON_COPYABLE_HPP__
