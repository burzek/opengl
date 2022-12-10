#include "includes/logging.hpp"

int main(int argc, char const *argv[]) {
    logging::log->init_log("arkanoid.log");
    logging::log->error("Starting game");

    GameEngine* engine = new GameEngine();
    engine->init();
    engine->run();
    delete engine;
    logging::log->info("Game finished");

}



//engine init=create gl window
//engine run =
//while (!end request) 
//  read inputs
//  update world
//  if fps is ok
//    render world()
//
//GameWindow =  window + gl setup


