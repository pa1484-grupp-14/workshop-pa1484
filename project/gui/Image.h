#ifndef GUI_IMAGE_H
#define GUI_IMAGE_H

#include "Widget.h"

class Image : public Widget {

public:
    Image(WidgetContainer& parent, uint32_t id);
    Image& setSource(const lv_image_dsc_t* src);
    Image& setScale(float scale);

};

#endif
