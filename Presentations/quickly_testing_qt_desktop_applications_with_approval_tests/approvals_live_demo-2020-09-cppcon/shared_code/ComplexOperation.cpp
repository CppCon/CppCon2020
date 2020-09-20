#include "ComplexOperation.h"
#include "Logger.h"

#include <chrono>

void logTimeAndStep( Logger& logger, const std::string& step )
{
    auto end = std::chrono::system_clock::now();
    time_t end_time = std::chrono::system_clock::to_time_t( end );
    logger << step << " at " << ctime( &end_time );
}

void ComplexOperation::doStuff( std::ostream& stream )
{
    Logger logger( stream );

    logTimeAndStep( logger, "started computation" );

    logger << "Doing step 1" << '\n';
    logger << "Doing step 2 - part 1" << '\n';
    logger << "Doing step 2 - part 2" << '\n';
    logger << "Doing step 3 - testing if part 2 worked" << '\n';
    for ( int i = 1; i <= 7; ++i )
    {
        logger << "Step 4 - section " << i << '\n';
    }

    logTimeAndStep( logger, "finished computation" );

    logger << "Done!\n";
}
