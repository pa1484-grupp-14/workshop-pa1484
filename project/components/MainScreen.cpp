#include "MainScreen.h"

MainScreen::MainScreen() {}
MainScreen::~MainScreen() {}

void MainScreen::process() {}
void MainScreen::constructUI(Tile* tile) {
  //Main Screen
  Tile& main_screen = *tile;

  //project text
  Widget& project_label = main_screen.addLabel("main label")
                              .setText("Software development project")
                              .setFont(&lv_font_montserrat_32)
                              .center();

  //group number label
  main_screen.addLabel()
      .setText("PA1484 Group 14")
      .setFont(&lv_font_montserrat_48)
      .alignTo(project_label, LV_ALIGN_CENTER, 0, -40)
      .focusOn()
      .getTile()
      .addLabel()
      .setText("Version 4")
      .setFont(&lv_font_montserrat_48)
      .alignTo(project_label, LV_ALIGN_CENTER, 0, 150);
}