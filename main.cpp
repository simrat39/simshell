#include <gudev/gudev.h>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include "SimshellApp.hpp"

int main(int argc, char* argv[]) {
    auto app = SimshellApp::create();
    return app->run(argc, argv);
}
