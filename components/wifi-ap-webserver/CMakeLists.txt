file(GLOB web_pages webpages/*.c)

idf_component_register(SRCS "wifi-ap-webserver.c"  ${web_pages}
                    REQUIRES driver
                    REQUIRES esp_wifi
                    REQUIRES nvs_flash
                    REQUIRES esp_netif
                    REQUIRES esp_http_server
                    INCLUDE_DIRS "include" "webpages")
