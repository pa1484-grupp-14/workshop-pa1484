#ifndef ARDUINO_ARCH_ESP32
#pragma once

#include <SDL2/SDL.h>
#include <lvgl.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_version.h>
#include "IDisplay.hpp"  // Assuming IDisplay is your interface

typedef struct {
    int16_t last_x;
    int16_t last_y;
    bool left_button_down;
#if LV_SDL_MOUSEWHEEL_MODE == LV_SDL_MOUSEWHEEL_MODE_CROWN
    int32_t diff;
#endif
} lv_sdl_mouse_t;

namespace hal {

class SDLDisplay : public IDisplay {
 public:
  SDLDisplay();
  ~SDLDisplay();

  bool init() override;
  void setBrightness(uint8_t brightness) override;
  void sleep() override;
  void wakeup() override;
  int handle_events() override;

  SDL_Renderer* getRenderer();

 private:
 void updateMouse();
  // Static callback function to bridge C-style LVGL callback and C++ member function
  static void flush_cb_static(lv_display_t* drv, const lv_area_t* area,
                              uint8_t* color_p);

  // Member function to handle the actual flushing
  void flush_display(lv_display_t* drv, const lv_area_t* area,
                     uint8_t* color_p);

  // Define screen dimensions as constants
  static constexpr int SCREEN_WIDTH = 600;
  static constexpr int SCREEN_HEIGHT = 450;
  static constexpr int PARTIAL_BUF_HEIGHT = 100;
  int screen_width;
  int screen_height;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;

  // Static buffers sized with the constants
  static lv_color_t buf1[SCREEN_WIDTH * SCREEN_HEIGHT];
  static lv_color_t buf2[SCREEN_WIDTH * SCREEN_HEIGHT];

  lv_sdl_mouse_t mouse_dsc;
  lv_display_t * disp_drv;
};

}  // namespace hal
#endif  // ARDUINO
