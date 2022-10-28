idf_component_register(SRCS "keyboard.c"
                    REQUIRES driver
                    REQUIRES serial_io
                    INCLUDE_DIRS "include")
