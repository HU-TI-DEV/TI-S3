idf_component_register(SRCS "main.cpp" "Ili9341Display.cpp" "MovingRect.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES esp_lcd_ili9341 drawables esp_timer)