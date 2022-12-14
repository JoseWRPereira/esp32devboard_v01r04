idf_component_register(SRCS "testaPerifericos.c"
                    REQUIRES driver
                    REQUIRES esp32-devboard_v01r04
                    REQUIRES wifi-ap-webserver
                    INCLUDE_DIRS ".")
