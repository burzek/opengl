#ifndef DFABDB6B_1640_4DE4_BE2D_1721EA50AF88
#define DFABDB6B_1640_4DE4_BE2D_1721EA50AF88

#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

class Log {
    public:
        Log();
        virtual ~Log();
        void init_log(std::string log_file);
        
        void debug(std::string msg);
        void info(std::string msg);
        void error(std::string msg);
        
};

#endif /* DFABDB6B_1640_4DE4_BE2D_1721EA50AF88 */
