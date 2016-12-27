#ifndef __LOG_HPP__
#define __LOG_HPP__

enum E_LOG_SEVERITY_LEVEL
{
        E_LSL_NONE,
        E_LSL_NORMAL,
        E_LSL_NOTIFICATION,
        E_LSL_WARNING,
        E_LSL_ERROR,
        E_LSL_CRITICAL,
};

class Log
{
public :
        void Log();
        void Debug();
        void Error();
        void Warn();
private :
};

#endif // __LOG_HPP__
