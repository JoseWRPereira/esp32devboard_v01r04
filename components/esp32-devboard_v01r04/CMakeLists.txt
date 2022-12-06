file(GLOB hal_lib hal/*.c)

idf_component_register(SRCS "esp32-devboard_v01r04.c" ${hal_lib}
                    REQUIRES driver
                    INCLUDE_DIRS "include" "hal")
