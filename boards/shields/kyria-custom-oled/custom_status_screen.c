/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include "custom_status_screen.h"
#include "widgets/battery_status.h"
#include "widgets/bongo_cat.h"
#include "widgets/layer_status.h"
#include "widgets/modifiers.h"
#include "widgets/output_status.h"

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

LV_IMG_DECLARE(kyrialogo);

static struct zmk_widget_output_status output_status_widget;
static struct zmk_widget_layer_status layer_status_widget;
static struct zmk_widget_peripheral_battery_status
    peripheral_battery_status_widget;
static struct zmk_widget_modifiers modifiers_widget;
static struct zmk_widget_bongo_cat bongo_cat_widget;

lv_style_t global_style;

lv_obj_t *zmk_display_status_screen() {
  lv_obj_t *screen;

  screen = lv_obj_create(NULL);

#if IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  lv_style_init(&global_style);
  lv_style_set_text_font(&global_style, &lv_font_unscii_8);
  lv_style_set_text_letter_space(&global_style, 1);
  lv_style_set_text_line_space(&global_style, 1);
  lv_obj_add_style(screen, &global_style, LV_PART_MAIN);

  zmk_widget_output_status_init(&output_status_widget, screen);
  lv_obj_align(zmk_widget_output_status_obj(&output_status_widget),
               LV_ALIGN_TOP_LEFT, 0, 0);

  zmk_widget_bongo_cat_init(&bongo_cat_widget, screen);
  lv_obj_align(zmk_widget_bongo_cat_obj(&bongo_cat_widget),
               LV_ALIGN_BOTTOM_RIGHT, 0, -7);

  zmk_widget_modifiers_init(&modifiers_widget, screen);
  lv_obj_align(zmk_widget_modifiers_obj(&modifiers_widget),
               LV_ALIGN_BOTTOM_LEFT, 0, 0);

  zmk_widget_layer_status_init(&layer_status_widget, screen);
  // lv_obj_align(zmk_widget_layer_status_obj(&layer_status_widget),
  // LV_ALIGN_BOTTOM_LEFT, 2, -18);
  lv_obj_align_to(zmk_widget_layer_status_obj(&layer_status_widget),
                  zmk_widget_bongo_cat_obj(&bongo_cat_widget),
                  LV_ALIGN_BOTTOM_LEFT, 0, 5);

  zmk_widget_peripheral_battery_status_init(&peripheral_battery_status_widget,
                                            screen);
  lv_obj_align(zmk_widget_peripheral_battery_status_obj(
                   &peripheral_battery_status_widget),
               LV_ALIGN_TOP_RIGHT, 0, 0);
#endif

#if !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  lv_obj_t *kyrialogo_icon;
  kyrialogo_icon = lv_img_create(screen);
  lv_img_set_src(kyrialogo_icon, &kyrialogo);
  lv_obj_align(kyrialogo_icon, LV_ALIGN_BOTTOM_MID, 0, 0);
#endif

  return screen;
}