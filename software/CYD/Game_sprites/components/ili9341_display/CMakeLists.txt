# components/ili9341_display/CMakeLists.txt
idf_component_register(
    SRCS "Ili9341Display.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver esp_timer drawables esp_lcd_ili9341
)