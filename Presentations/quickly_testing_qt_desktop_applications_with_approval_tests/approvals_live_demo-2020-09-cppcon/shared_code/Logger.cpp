#include "Logger.h"

Logger::Logger( std::ostream& os ) : m_log( os.rdbuf() )
{
}
std::streambuf* Logger::reset( std::ostream& os )
{
    return m_log.rdbuf( os.rdbuf() );
}

Logger& operator<<( Logger& os, std::ostream& ( *pf )(std::ostream&))
{
    os.m_log << pf;
    return os;
}
