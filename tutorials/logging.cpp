#include "includes/logging.hpp"

namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;

Log::Log() 
{

};

Log::~Log() 
{

};


void Log::init_log(std::string file_name) 
{
    
    boost::log::add_common_attributes();
    boost::log::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] <%Severity%> %Message%");
    boost::log::add_file_log(
         keywords::file_name = file_name.c_str(),
         keywords::rotation_size = 10 * 1024 * 1024,
        keywords::format = (
            expr::stream
            << std::setw(8) << std::setfill('0') << expr::attr<unsigned int>("LineID") << " "
            << expr::format_date_time<boost::posix_time::ptime>("TimeStamp","[%H:%M:%S.%f] ")
            << "<" << boost::log::trivial::severity << "> " 
            << expr::smessage
    ));
        
};

void Log::debug(std::string msg) 
{
    BOOST_LOG_TRIVIAL(debug) << msg;
};

void Log::info(std::string msg)
{
    BOOST_LOG_TRIVIAL(info) << msg;
};

void Log::error(std::string msg)
{
    BOOST_LOG_TRIVIAL(error) << msg;
};
