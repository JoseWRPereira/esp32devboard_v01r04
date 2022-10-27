idf_component_register(SRCS "lcd.c"
                    REQUIRES driver
                    REQUIRES serial_io
                    INCLUDE_DIRS "include")
