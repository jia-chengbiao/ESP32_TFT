#ifndef IMAGES_H
#define IMAGES_H

#include "lvgl.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

struct WEATHER
{
	char* weathername;
	char* filename;
};

struct LV_WEATHER
{
	char* weathername;
	char* Path;
};

extern const struct LV_WEATHER weather[30];

LV_IMG_DECLARE(ali);
#endif
