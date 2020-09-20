#ifndef DEMO_LOGGER_H
#define DEMO_LOGGER_H

#include <string>
#include <ostream>

// Based on https://stackoverflow.com/a/8446901/104370
struct Logger
{
    explicit Logger( std::ostream& os );

    std::streambuf* reset( std::ostream& os );

    template <typename T>
    friend Logger& operator<<( Logger& os, const T& t )
    {
        os.m_log << t;
        return os;
    }

    friend Logger& operator<<( Logger& os,
                               std::ostream& ( *pf )(std::ostream&));

private:
    std::ostream m_log;
};

#endif //DEMO_LOGGER_H
