#include "logger.hpp"

int main()
{
    Logger simpleLog(logLevels::INFO);
    simpleLog.openFile("%Y %M %D.txt");
    simpleLog.log("Test log!", logLevels::INFO);
    return 0;
}
