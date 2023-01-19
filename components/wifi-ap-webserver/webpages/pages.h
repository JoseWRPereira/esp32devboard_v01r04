#ifndef PAGES_H
#define PAGES_H

#include "wifi-ap-webserver.h"
#include "esp_http_server.h"
// #include "wifi-ap-webserver.h"

extern httpd_uri_t * uri_vector[];
extern size_t uri_vector_number_of_elements;

uint8_t web_digital_output( void );
int32_t web_stepmotor( void );
void web_stepmotor_reset( void );

#endif
