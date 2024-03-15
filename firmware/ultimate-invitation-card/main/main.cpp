#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "application.hpp"

extern "C" void app_main() {
  using namespace espena;
  application *app = application::get();
  app->run();
}