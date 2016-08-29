#ifndef __NON_COPYABLE_HPP__
#define __NON_COPYABLE_HPP__

class CNonCopyable
{
protected :
        CNonCopyable() {}
        ~CNonCopyable() {}

private :
        CNonCopyable(const CNonCopyable&) = delete;
        const CNonCopyable& operator=(const CNonCopyable&) = delete;
};

#endif // __NON_COPYABLE_HPP__
