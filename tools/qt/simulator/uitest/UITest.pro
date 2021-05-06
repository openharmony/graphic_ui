
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS \
    CJSON_HIDE_SYMBOLS \
    "ENABLE_SHAPING=0" \
    "ENABLE_BITMAP_FONT=0" \
    "ENABLE_ICU=1" \
    "ENABLE_VECTOR_FONT=1"

DEFINES += QT_COMPILER

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = ../libs

FORMS += \
    main_widget.ui

TRANSLATIONS += helloqt_zh_CN.ts

SOURCES += \
    ../../../../frameworks/animator/animator.cpp \
    ../../../../frameworks/animator/animator_manager.cpp \
    ../../../../frameworks/animator/easing_equation.cpp \
    ../../../../frameworks/animator/interpolation.cpp \
    ../../../../frameworks/common/graphic_startup.cpp \
    ../../../../frameworks/common/image.cpp \
    ../../../../frameworks/common/input_device_manager.cpp \
    ../../../../frameworks/common/screen.cpp \
    ../../../../frameworks/common/task.cpp \
    ../../../../frameworks/common/text.cpp \
    ../../../../frameworks/common/typed_text.cpp \
    ../../../../frameworks/common/ui_font_header.cpp \
    ../../../../frameworks/components/root_view.cpp \
    ../../../../frameworks/components/text_adapter.cpp \
    ../../../../frameworks/components/ui_abstract_clock.cpp \
    ../../../../frameworks/components/ui_abstract_progress.cpp \
    ../../../../frameworks/components/ui_abstract_scroll.cpp \
    ../../../../frameworks/components/ui_analog_clock.cpp \
    ../../../../frameworks/components/ui_arc_label.cpp \
    ../../../../frameworks/components/ui_axis.cpp \
    ../../../../frameworks/components/ui_box_progress.cpp \
    ../../../../frameworks/components/ui_button.cpp \
    ../../../../frameworks/components/ui_canvas.cpp \
    ../../../../frameworks/components/ui_chart.cpp \
    ../../../../frameworks/components/ui_checkbox.cpp \
    ../../../../frameworks/components/ui_circle_progress.cpp \
    ../../../../frameworks/components/ui_dialog.cpp \
    ../../../../frameworks/components/ui_digital_clock.cpp \
    ../../../../frameworks/components/ui_image_animator.cpp \
    ../../../../frameworks/components/ui_image_view.cpp \
    ../../../../frameworks/components/ui_label.cpp \
    ../../../../frameworks/components/ui_label_button.cpp \
    ../../../../frameworks/components/ui_list.cpp \
    ../../../../frameworks/components/ui_picker.cpp \
    ../../../../frameworks/components/ui_qrcode.cpp \
    ../../../../frameworks/components/ui_radio_button.cpp \
    ../../../../frameworks/components/ui_repeat_button.cpp \
    ../../../../frameworks/components/ui_scroll_view.cpp \
    ../../../../frameworks/components/ui_slider.cpp \
    ../../../../frameworks/components/ui_swipe_view.cpp \
    ../../../../frameworks/components/ui_texture_mapper.cpp \
    ../../../../frameworks/components/ui_time_picker.cpp \
    ../../../../frameworks/components/ui_toggle_button.cpp \
    ../../../../frameworks/components/ui_view.cpp \
    ../../../../frameworks/components/ui_view_group.cpp \
    ../../../../frameworks/dock/focus_manager.cpp \
    ../../../../frameworks/core/render_manager.cpp \
    ../../../../frameworks/core/task_manager.cpp \
    ../../../../frameworks/default_resource/check_box_res.cpp \
    ../../../../frameworks/dfx/event_injector.cpp \
    ../../../../frameworks/dfx/key_event_injector.cpp \
    ../../../../frameworks/dfx/point_event_injector.cpp \
    ../../../../frameworks/dfx/ui_dump_dom_tree.cpp \
    ../../../../frameworks/dock/input_device.cpp \
    ../../../../frameworks/dock/key_input_device.cpp \
    ../../../../frameworks/dock/pointer_input_device.cpp \
    ../../../../frameworks/dock/rotate_input_device.cpp \
    ../../../../frameworks/dock/screen_device_proxy.cpp \
    ../../../../frameworks/dock/virtual_input_device.cpp \
    ../../../../frameworks/draw/draw_arc.cpp \
    ../../../../frameworks/draw/draw_curve.cpp \
    ../../../../frameworks/draw/draw_image.cpp \
    ../../../../frameworks/draw/draw_label.cpp \
    ../../../../frameworks/draw/draw_line.cpp \
    ../../../../frameworks/draw/draw_rect.cpp \
    ../../../../frameworks/draw/draw_triangle.cpp \
    ../../../../frameworks/draw/draw_utils.cpp \
    ../../../../frameworks/events/event.cpp \
    ../../../../frameworks/font/base_font.cpp \
    ../../../../frameworks/font/glyphs_manager.cpp \
    ../../../../frameworks/font/ui_font.cpp \
    ../../../../frameworks/font/ui_font_adaptor.cpp \
    ../../../../frameworks/font/ui_font_allocator.cpp \
    ../../../../frameworks/font/ui_font_cache.cpp \
    ../../../../frameworks/font/ui_font_vector.cpp \
    ../../../../frameworks/font/ui_line_break.cpp \
    ../../../../frameworks/font/ui_multi_font_manager.cpp \
    ../../../../frameworks/font/ui_text_shaping.cpp \
    ../../../../frameworks/imgdecode/cache_manager.cpp \
    ../../../../frameworks/imgdecode/file_img_decoder.cpp \
    ../../../../frameworks/imgdecode/image_load.cpp \
    ../../../../frameworks/layout/flex_layout.cpp \
    ../../../../frameworks/layout/grid_layout.cpp \
    ../../../../frameworks/layout/list_layout.cpp \
    ../../../../frameworks/themes/theme.cpp \
    ../../../../frameworks/themes/theme_manager.cpp \
    ../../../../../utils/frameworks/color.cpp \
    ../../../../../utils/frameworks/geometry2d.cpp \
    ../../../../../utils/frameworks/graphic_math.cpp \
    ../../../../../utils/frameworks/hal_tick.cpp \
    ../../../../../utils/frameworks/mem_api.cpp \
    ../../../../../utils/frameworks/style.cpp \
    ../../../../../utils/frameworks/sys_info.cpp \
    ../../../../../utils/frameworks/transform.cpp \
    ../../../../../utils/frameworks/version.cpp \
    ../../../../../../../third_party/bounds_checking_function/src/memset_s.c \
    ../../../../../../../third_party/cJSON/cJSON.c

SOURCES += \
    ../../../../test/framework/src/test_case_list_adapter.cpp \
    ../../../../test/framework/src/ui_test_group.cpp \
    ../../../../test/framework/src/test_ability.cpp \
    ../../../../test/framework/src/ui_test_app.cpp \
    ../../../../test/uitest/test_animator/ui_test_animator.cpp \
    ../../../../test/uitest/test_anti_aliasing/ui_test_anti_aliasing.cpp \
    ../../../../test/uitest/test_arc_label/ui_test_arc_label.cpp \
    ../../../../test/uitest/test_border_margin_padding/ui_test_border_margin_padding.cpp \
    ../../../../test/uitest/test_button/ui_test_button.cpp \
    ../../../../test/uitest/test_canvas/ui_test_canvas.cpp \
    ../../../../test/uitest/test_chart/ui_test_chart_pillar.cpp \
    ../../../../test/uitest/test_chart/ui_test_chart_polyline.cpp \
    ../../../../test/uitest/test_dialog/ui_test_dialog.cpp \
    ../../../../test/uitest/test_digital_clock/ui_test_digital_clock.cpp \
    ../../../../test/uitest/test_draw_line/ui_test_draw_line.cpp \
    ../../../../test/uitest/test_draw_rect/ui_test_draw_rect.cpp \
    ../../../../test/uitest/test_event_injector/ui_test_event_injector.cpp \
    ../../../../test/uitest/test_focus_manager/ui_test_focus_manager.cpp \
    ../../../../test/uitest/test_font/ui_test_font.cpp \
    ../../../../test/uitest/test_image/ui_test_image.cpp \
    ../../../../test/uitest/test_image_animator/ui_test_image_animator.cpp \
    ../../../../test/uitest/test_input_event/ui_test_input_event.cpp \
    ../../../../test/uitest/test_label/ui_test_label.cpp \
    ../../../../test/uitest/test_layout/ui_test_advanced_layout.cpp \
    ../../../../test/uitest/test_layout/ui_test_basic_layout.cpp \
    ../../../../test/uitest/test_opacity/ui_test_opacity.cpp \
    ../../../../test/uitest/test_picker/ui_test_ui_picker.cpp \
    ../../../../test/uitest/test_progress_bar/ui_test_box_progress.cpp \
    ../../../../test/uitest/test_progress_bar/ui_test_circle_progress.cpp \
    ../../../../test/uitest/test_qrcode/ui_test_qrcode.cpp \
    ../../../../test/uitest/test_render/ui_test_render.cpp \
    ../../../../test/uitest/test_rotate_input/ui_test_rotate_input.cpp \
    ../../../../test/uitest/test_slider/ui_test_slider.cpp \
    ../../../../test/uitest/test_texture_mapper/ui_test_texture_mapper.cpp \
    ../../../../test/uitest/test_transform/ui_test_transform.cpp \
    ../../../../test/uitest/test_ui_analog_clock/ui_test_analog_clock.cpp \
    ../../../../test/uitest/test_ui_dump_dom_tree/ui_test_dump_dom.cpp \
    ../../../../test/uitest/test_ui_list/ui_test_ui_list.cpp \
    ../../../../test/uitest/test_ui_list_view/ui_test_list_layout.cpp \
    ../../../../test/uitest/test_ui_scroll_view/ui_test_ui_scroll_view.cpp \
    ../../../../test/uitest/test_ui_swipe_view/ui_test_ui_swipe_view.cpp \
    ../../../../test/uitest/test_vector_font/ui_test_vector_font.cpp \
    ../../../../test/uitest/test_view_bitmap/ui_test_view_bitmap.cpp \
    ../../../../test/uitest/test_view_group/ui_test_view_group.cpp \
    ../../../../test/uitest/test_view_percent/ui_test_view_percent.cpp \
    ../../../../test/uitest/test_view_scale_rotate/ui_test_view_scale_rotate.cpp

SOURCES += \
    ../../../../test/framework/src/ui_auto_test.cpp \
    ../../../../test/framework/src/ui_auto_test_group.cpp \
    ../../../../test/framework/src/compare_tools.cpp \
    ../../../../test/uitest/test_render/ui_auto_test_render.cpp \


SOURCES += \
    ../drivers/display/gui_thread.cpp \
    ../drivers/display/monitor.cpp \
    ../drivers/display/task_thread.cpp \
    ../drivers/indev/key_input.cpp \
    ../drivers/indev/mouse_input.cpp \
    ../drivers/indev/mousewheel_input.cpp \
    main.cpp \
    main_widget.cpp

HEADERS += \
    ../../../../frameworks/common/typed_text.h \
    ../../../../frameworks/core/render_manager.h \
    ../../../../frameworks/default_resource/check_box_res.h \
    ../../../../frameworks/dfx/key_event_injector.h \
    ../../../../frameworks/dfx/point_event_injector.h \
    ../../../../frameworks/dock/input_device.h \
    ../../../../frameworks/dock/pointer_input_device.h \
    ../../../../frameworks/dock/screen_device.h \
    ../../../../frameworks/dock/screen_device_proxy.h \
    ../../../../frameworks/dock/virtual_input_device.h \
    ../../../../frameworks/draw/draw_arc.h \
    ../../../../frameworks/draw/draw_curve.h \
    ../../../../frameworks/draw/draw_image.h \
    ../../../../frameworks/draw/draw_label.h \
    ../../../../frameworks/draw/draw_line.h \
    ../../../../frameworks/draw/draw_rect.h \
    ../../../../frameworks/draw/draw_triangle.h \
    ../../../../frameworks/draw/draw_utils.h \
    ../../../../frameworks/font/ui_font_adaptor.h \
    ../../../../frameworks/font/ui_multi_font_manager.h \
    ../../../../frameworks/imgdecode/cache_manager.h \
    ../../../../frameworks/imgdecode/file_img_decoder.h \
    ../../../../frameworks/imgdecode/image_load.h \
    ../../../../interfaces/innerkits/common/graphic_startup.h \
    ../../../../interfaces/innerkits/common/image_decode_ability.h \
    ../../../../interfaces/innerkits/common/input_device_manager.h \
    ../../../../interfaces/innerkits/common/task_manager.h \
    ../../../../interfaces/innerkits/dock/focus_manager.h \
    ../../../../interfaces/innerkits/dock/rotate_input_device.h \
    ../../../../interfaces/innerkits/dock/vibrator_manager.h \
    ../../../../interfaces/kits/animator/animator.h \
    ../../../../interfaces/kits/animator/easing_equation.h \
    ../../../../interfaces/kits/animator/interpolation.h \
    ../../../../interfaces/kits/common/image.h \
    ../../../../interfaces/kits/common/screen.h \
    ../../../../interfaces/kits/common/task.h \
    ../../../../interfaces/kits/common/text.h \
    ../../../../interfaces/kits/components/abstract_adapter.h \
    ../../../../interfaces/kits/components/root_view.h \
    ../../../../interfaces/kits/components/text_adapter.h \
    ../../../../interfaces/kits/components/ui_abstract_clock.h \
    ../../../../interfaces/kits/components/ui_abstract_progress.h \
    ../../../../interfaces/kits/components/ui_abstract_scroll.h \
    ../../../../interfaces/kits/components/ui_analog_clock.h \
    ../../../../interfaces/kits/components/ui_arc_label.h \
    ../../../../interfaces/kits/components/ui_axis.h \
    ../../../../interfaces/kits/components/ui_box_progress.h \
    ../../../../interfaces/kits/components/ui_button.h \
    ../../../../interfaces/kits/components/ui_canvas.h \
    ../../../../interfaces/kits/components/ui_chart.h \
    ../../../../interfaces/kits/components/ui_checkbox.h \
    ../../../../interfaces/kits/components/ui_circle_progress.h \
    ../../../../interfaces/kits/components/ui_dialog.h \
    ../../../../interfaces/kits/components/ui_digital_clock.h \
    ../../../../interfaces/kits/components/ui_image_animator.h \
    ../../../../interfaces/kits/components/ui_image_view.h \
    ../../../../interfaces/kits/components/ui_label.h \
    ../../../../interfaces/kits/components/ui_label_button.h \
    ../../../../interfaces/kits/components/ui_list.h \
    ../../../../interfaces/kits/components/ui_picker.h \
    ../../../../interfaces/kits/components/ui_qrcode.h \
    ../../../../interfaces/kits/components/ui_radio_button.h \
    ../../../../interfaces/kits/components/ui_repeat_button.h \
    ../../../../interfaces/kits/components/ui_scroll_view.h \
    ../../../../interfaces/kits/components/ui_slider.h \
    ../../../../interfaces/kits/components/ui_swipe_view.h \
    ../../../../interfaces/kits/components/ui_texture_mapper.h \
    ../../../../interfaces/kits/components/ui_time_picker.h \
    ../../../../interfaces/kits/components/ui_toggle_button.h \
    ../../../../interfaces/kits/components/ui_view.h \
    ../../../../interfaces/kits/components/ui_view_group.h \
    ../../../../interfaces/kits/dfx/event_injector.h \
    ../../../../interfaces/kits/dfx/ui_dump_dom_tree.h \
    ../../../../interfaces/kits/events/aod_callback.h \
    ../../../../interfaces/kits/events/cancel_event.h \
    ../../../../interfaces/kits/events/click_event.h \
    ../../../../interfaces/kits/events/drag_event.h \
    ../../../../interfaces/kits/events/event.h \
    ../../../../interfaces/kits/events/long_press_event.h \
    ../../../../interfaces/kits/events/press_event.h \
    ../../../../interfaces/kits/events/release_event.h \
    ../../../../interfaces/kits/events/virtual_device_event.h \
    ../../../../interfaces/kits/font/ui_font.h \
    ../../../../interfaces/kits/font/ui_font_header.h \
    ../../../../interfaces/kits/layout/flex_layout.h \
    ../../../../interfaces/kits/layout/grid_layout.h \
    ../../../../interfaces/kits/layout/layout.h \
    ../../../../interfaces/kits/layout/list_layout.h \
    ../../../../interfaces/kits/themes/theme.h \
    ../../../../interfaces/kits/themes/theme_manager.h \
    ../../../../interfaces/kits/window/window.h \
    ../../../../../utils/interfaces/innerkits/graphic_config.h \
    ../../../../../utils/interfaces/innerkits/graphic_locker.h \
    ../../../../../utils/interfaces/innerkits/graphic_semaphore.h \
    ../../../../../utils/interfaces/innerkits/hal_tick.h \
    ../../../../../utils/interfaces/kits/color.h \
    ../../../../../utils/interfaces/kits/file.h \
    ../../../../../utils/interfaces/kits/geometry2d.h \
    ../../../../../utils/interfaces/kits/graphic_assert.h \
    ../../../../../utils/interfaces/kits/graphic_log.h \
    ../../../../../utils/interfaces/kits/graphic_math.h \
    ../../../../../utils/interfaces/kits/graphic_types.h \
    ../../../../../utils/interfaces/kits/heap_base.h \
    ../../../../../utils/interfaces/kits/image_info.h \
    ../../../../../utils/interfaces/kits/input_event_info.h \
    ../../../../../utils/interfaces/kits/list.h \
    ../../../../../utils/interfaces/kits/mem_api.h \
    ../../../../../utils/interfaces/kits/rect.h \
    ../../../../../utils/interfaces/kits/style.h \
    ../../../../../utils/interfaces/kits/sys_info.h \
    ../../../../../utils/interfaces/kits/transform.h \
    ../../../../../utils/interfaces/kits/version.h \
    ../../../../../wms/interfaces/innerkits/lite_wm_type.h \
    ../../../../../../../third_party/bounds_checking_function/include/securec.h \
    ../../../../../../../third_party/bounds_checking_function/include/securectype.h \
    ../../../../../../../third_party/bounds_checking_function/src/input.inl \
    ../../../../../../../third_party/bounds_checking_function/src/output.inl \
    ../../../../../../../third_party/bounds_checking_function/src/secinput.h \
    ../../../../../../../third_party/bounds_checking_function/src/securecutil.h \
    ../../../../../../../third_party/bounds_checking_function/src/secureprintoutput.h \
    ../../../../../../../third_party/cJSON/cJSON.h \
    ../../../../../../../third_party/cJSON/cJSON_Utils.h \
    ../../../../../../../tools/developer_tools_lite/graphic_tool/iar_project/config/gpu_2d/graphic_config.h

HEADERS += \
    ../../../../test/framework/include/test_case_list_adapter.h \
    ../../../../test/framework/include/ui_test_app.h \
    ../../../../test/framework/include/test_resource_config.h \
    ../../../../test/framework/include/ui_test.h \
    ../../../../test/framework/include/ui_test_group.h \
    ../../../../test/uitest/test_animator/ui_test_animator.h \
    ../../../../test/uitest/test_anti_aliasing/ui_test_anti_aliasing.h \
    ../../../../test/uitest/test_arc_label/ui_test_arc_label.h \
    ../../../../test/uitest/test_button/ui_test_button.h \
    ../../../../test/uitest/test_canvas/ui_test_canvas.h \
    ../../../../test/uitest/test_chart/ui_test_chart_pillar.h \
    ../../../../test/uitest/test_chart/ui_test_chart_polyline.h \
    ../../../../test/uitest/test_dialog/ui_test_dialog.h \
    ../../../../test/uitest/test_digital_clock/ui_test_digital_clock.h \
    ../../../../test/uitest/test_draw_line/ui_test_draw_line.h \
    ../../../../test/uitest/test_draw_rect/ui_test_draw_rect.h \
    ../../../../test/uitest/test_event_injector/ui_test_event_injector.h \
    ../../../../test/uitest/test_focus_manager/ui_test_focus_manager.h \
    ../../../../test/uitest/test_font/ui_test_font.h \
    ../../../../test/uitest/test_image/ui_test_image.h \
    ../../../../test/uitest/test_image_animator/ui_test_image_animator.h \
    ../../../../test/uitest/test_input_event/ui_test_input_event.h \
    ../../../../test/uitest/test_label/ui_test_label.h \
    ../../../../test/uitest/test_layout/ui_test_advanced_layout.h \
    ../../../../test/uitest/test_layout/ui_test_basic_layout.h \
    ../../../../test/uitest/test_opacity/ui_test_opacity.h \
    ../../../../test/uitest/test_picker/ui_test_ui_picker.h \
    ../../../../test/uitest/test_progress_bar/ui_test_box_progress.h \
    ../../../../test/uitest/test_progress_bar/ui_test_circle_progress.h \
    ../../../../test/uitest/test_qrcode/ui_test_qrcode.cpp \
    ../../../../test/uitest/test_render/ui_test_render.h \
    ../../../../test/uitest/test_rotate_input/ui_test_rotate_input.h \
    ../../../../test/uitest/test_slider/ui_test_slider.h \
    ../../../../test/uitest/test_texture_mapper/ui_test_texture_mapper.h \
    ../../../../test/uitest/test_transform/ui_test_transform.h \
    ../../../../test/uitest/test_ui_analog_clock/ui_test_analog_clock.h \
    ../../../../test/uitest/test_ui_dump_dom_tree/ui_test_dump_dom.h \
    ../../../../test/uitest/test_ui_list/ui_test_ui_list.h \
    ../../../../test/uitest/test_ui_list_view/ui_test_list_layout.h \
    ../../../../test/uitest/test_ui_scroll_view/ui_test_ui_scroll_view.h \
    ../../../../test/uitest/test_ui_swipe_view/ui_test_ui_swipe_view.h \
    ../../../../test/uitest/test_vector_font/ui_test_vector_font.h \
    ../../../../test/uitest/test_view_bitmap/ui_test_view_bitmap.h \
    ../../../../test/uitest/test_view_group/ui_test_view_group.h \
    ../../../../test/uitest/test_view_percent/ui_test_view_percent.h \
    ../../../../test/uitest/test_view_scale_rotate/ui_test_view_scale_rotate.h


HEADERS += \
    ../../../../test/framework/include/ui_auto_test.h \
    ../../../../test/framework/include/ui_auto_test_group.h \
    ../../../../test/framework/include/compare_tools.h \
    ../../../../test/uitest/test_render/ui_auto_test_render.h


HEADERS += \
    ../drivers/config.h \
    ../drivers/display/gui_thread.h \
    ../drivers/display/task_thread.h \
    ../drivers/display/monitor.h \
    ../drivers/indev/key_input.h \
    ../drivers/indev/mouse_input.h \
    ../drivers/indev/mousewheel_input.h \
    main_widget.h

INCLUDEPATH += \
    ../drivers/display \
    ../drivers/indev \
    ../drivers \
    ../../../../frameworks \
    ../../../../test/framework/include \
    ../../../../test/uitest \
    ../../../../../utils/frameworks/windows \
    ../../../../../utils/interfaces/innerkits \
    ../../../../../utils/interfaces/kits \
    ../../../../../ui/interfaces/innerkits \
    ../../../../../ui/interfaces/kits \
    ../../../../../ui/interfaces/frameworks \
    ../../../../../../../third_party/bounds_checking_function/include \
    ../../../../../../../third_party/harfbuzz/src \
    ../../../../../../../third_party/icu/icu4c/source/common \
    ../../../../../../../third_party/freetype/include \
    ../../../../../../../third_party/cJSON \
    ../../../../../../../third_party/libjpeg \
    ../../../../../../../third_party/libpng \
    ../../../../../../../third_party/qrcodegen/cpp

LIBS += $$OUT_PWD/../libs/libpng.dll
LIBS += $$OUT_PWD/../libs/libjpeg.dll
LIBS += $$OUT_PWD/../libs/qrcodegen.dll
LIBS += $$OUT_PWD/../libs/freetype.dll
LIBS += $$OUT_PWD/../libs/libharfbuzz.a
LIBS += $$OUT_PWD/../libs/icu.dll
