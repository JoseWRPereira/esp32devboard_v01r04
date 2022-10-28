idf_component_register(SRCS "testaPerifericos.c"
                    REQUIRES driver
                    REQUIRES piscaLed
                    REQUIRES serial_io
                    REQUIRES lcd
                    REQUIRES keyboard
                    INCLUDE_DIRS ".")
