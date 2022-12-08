#include "includes/logging.hpp"

namespace logging = boost::log;
namespace keywords = boost::log::keywords;

Log::Log() {

};

Log::~Log() {

};

void Log::init_log(std::string file_name) {
    logging::add_file_log(
         keywords::file_name = file_name.c_str(),
         keywords::rotation_size = 10 * 1024 * 1024,
         keywords::format = "[%TimeStamp%]: %Message%"
    );    
};


