// #include <stdio.h>
// #include <string.h>
#include "esp_http_server.h"
#include "wifi-ap-webserver.h"
#include "string.h"



esp_err_t get_example(httpd_req_t *req)
{
    const char resp[] = "<h2>Example</h2>";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
httpd_uri_t uri_example = 
{
    .uri = "/example",
    .method = HTTP_GET,
    .handler = get_example,
    .user_ctx = NULL
};



esp_err_t get_test(httpd_req_t *req)
{
    const char resp[] = "<h2>Test</h2>";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
httpd_uri_t uri_test = 
{
    .uri = "/test",
    .method = HTTP_GET,
    .handler = get_test,
    .user_ctx = NULL
};

esp_err_t get_devboard(httpd_req_t *req)
{
    const char resp[] = "<h2>devboard</h2>";
    const char resp2[] = "<h2>devboard2</h2>";
    httpd_resp_set_status(req, "200 OK"); //      HTTP status string, 
    httpd_resp_set_type(req,"text/html");   //      Content Type
    httpd_resp_set_hdr(req,"charset","utf-8");    //  
    httpd_resp_sendstr_chunk(req,resp);
    httpd_resp_sendstr_chunk(req,resp2);
    httpd_resp_sendstr_chunk(req,NULL);
//    httpd_resp_send_chunk(req, resp2, HTTPD_RESP_USE_STRLEN );
    // httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
httpd_uri_t uri_devboard = 
{
    .uri = "/devboard",
    .method = HTTP_GET,
    .handler = get_devboard,
    .user_ctx = NULL
};


httpd_uri_t * uri_vector[] = { &uri_example, &uri_test, &uri_devboard };
size_t uri_vector_number_of_elements = sizeof(uri_vector)/sizeof(uri_vector[0]);


// esp_err_t get_handler(httpd_req_t *req)
// {
/*    const char resp[] = "<!DOCTYPE HTML><html><head>\
                            <title>ESP Input Form</title>\
                            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
                            </head><body>\
                            <form action=\"/get\">\
                                str: <input type=\"text\" name=\"str\">\
                                <input type=\"submit\" value=\"Submit\">\
                            </form><br>\
                            <form action=\"/get\">\
                                int: <input type=\"text\" name=\"int\">\
                                <input type=\"submit\" value=\"Submit\">\
                            </form><br>\
                            </body></html>";
*/
//     httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
//     return ESP_OK;
// }

// esp_err_t get_handler_str(httpd_req_t *req)
// {
//     // Read the URI line and get the host
//     char *buf;
//     size_t buf_len;
//     buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
//     if (buf_len > 1)
//     {
//         buf = malloc(buf_len);
//         if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK)
//         {
//             ESP_LOGI(TAG, "Host: %s", buf);
//         }
//         free(buf);
//     }

//     // Read the URI line and get the parameters
//     buf_len = httpd_req_get_url_query_len(req) + 1;
//     if (buf_len > 1) 
//     {
//         buf = malloc(buf_len);
//         if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) 
//         {
//             ESP_LOGI(TAG, "Found URL query: %s", buf);
//             char param[32];
//             if (httpd_query_key_value(buf, "str", param, sizeof(param)) == ESP_OK) 
//             {
//                 ESP_LOGI(TAG, "The string value = %s", param);
//             }
//             if (httpd_query_key_value(buf, "int", param, sizeof(param)) == ESP_OK) 
//             {
//                 ESP_LOGI(TAG, "The int value = %s", param);
//             }
//             if (httpd_query_key_value(buf, "K1", param, sizeof(param)) == ESP_OK) 
//             {
//                 ESP_LOGI(TAG, "The K1 value = %s", param);
//                 // if( param[0] == '1')
//                 //     digital_out.bits.rl0 = 1;
//                 // if( param[0] == '0')
//                 //     digital_out.bits.rl0 = 0;
//                 // digital_io_scan();
//             }
//             if (httpd_query_key_value(buf, "K2", param, sizeof(param)) == ESP_OK) 
//             {
//                 ESP_LOGI(TAG, "The K2 value = %s", param);
//                 // if( param[0] == '1')
//                     // digital_out.bits.rl1 = 1;
//                 // if( param[0] == '0')
//                 //     digital_out.bits.rl1 = 0;
//                 // digital_io_scan();
//             }
//         }
//         free(buf);
//     }

//     // The response
//     // const char resp[] = "The data was sent ...";
//     // httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
//     return ESP_OK;
// }









// esp_err_t get_handler_entradas(httpd_req_t *req)
// {
/*
    const char resp1[] = "<!DOCTYPE HTML><html><head>\
                            <title>ESP Input Form</title>\
                            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
                            </head>\
                            <body>\
                            E0 = 1;\
                            </body></html>";
    const char resp0[] = "<!DOCTYPE HTML><html><head>\
                            <title>ESP Input Form</title>\
                            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
                            </head>\
                            <body>\
                            E0 = 0;\
                            </body></html>";
*/
//     // const char resp0[] = "E0 = 0;";
//     // const char resp1[] = "E0 = 1;";
//     // char resp[] = "E:0b________";

/*    char resp[] = "<!DOCTYPE HTML>\
<html><head><title>ESP32 Dev. Board</title>\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
</head><body><center>\
<h1>SAEP 2023</h1><hr><br>\
Entradas:<br>\
<h2>0 b _ _ _ _ _ _ _ _</h2><br>\
Saidas\
<h2>\
<form action=\"/saidas\">\
<input type=\"checkbox\" name=\"K1\" value=\"1\" checke >\
<label for=\"K1\">K1</label>\
<input type=\"checkbox\" name=\"K2\" value=\"1\" checke >\
<label for=\"K2\">K2</label>\
</h2>\
<br>\
<input type=\"submit\" value=\"Atualizar\">\
</form>\
</center>\
</body>\
</html>";
*/


//     // digital_io_scan();

//     // resp[194] = digital_in.bits.e7 ? '1':'0';
//     // resp[196] = digital_in.bits.e6 ? '1':'0';
//     // resp[198] = digital_in.bits.e5 ? '1':'0';
//     // resp[200] = digital_in.bits.e4 ? '1':'0';
//     // resp[202] = digital_in.bits.e3 ? '1':'0';
//     // resp[204] = digital_in.bits.e2 ? '1':'0';
//     // resp[206] = digital_in.bits.e1 ? '1':'0';
//     // resp[208] = digital_in.bits.e0 ? '1':'0';

//     // resp[300] = digital_out.bits.rl0 ? 'd':' ';
//     // resp[377] = digital_out.bits.rl1 ? 'd':' ';

//     // ESP_LOGI(TAG, "The checkeD %c %c %c", resp[299], resp[300], resp[301]);
//     // ESP_LOGI(TAG, "The checkeD %c %c %c", resp[376], resp[377], resp[378]);


//     httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
//     return ESP_OK;
// }


// esp_err_t get_handler_saidas(httpd_req_t *req)
// {
//     // Read the URI line and get the host
//     char *buf;
//     size_t buf_len;
//     buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
//     if (buf_len > 1)
//     {
//         buf = malloc(buf_len);
//         if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK)
//         {
//             ESP_LOGI(TAG, "Host: %s", buf);
//         }
//         free(buf);
//     }

//     // Read the URI line and get the parameters
//     buf_len = httpd_req_get_url_query_len(req) + 1;
//     if (buf_len > 1) 
//     {
//         buf = malloc(buf_len);
//         if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) 
//         {
//             ESP_LOGI(TAG, "Found URL query: %s", buf);
//             char param[32];
//             if (httpd_query_key_value(buf, "K1", param, sizeof(param)) == ESP_OK) 
//             {
//                 ESP_LOGI(TAG, "The K1 value = %s", param);
//                     // digital_out.bits.rl0 = 1;
//             }
//             else
//             {
//                 // digital_out.bits.rl0 = 0;
//             }

//             if (httpd_query_key_value(buf, "K2", param, sizeof(param)) == ESP_OK) 
//             {
//                 ESP_LOGI(TAG, "The K2 value = %s", param);
//                     // digital_out.bits.rl1 = 1;
//             }
//             else
//             {
//                 // digital_out.bits.rl1 = 0;
//             }
//         }
//         free(buf);
//     }
//     else
//     {
//         // digital_out.bits.rl0 = 0;
//         // digital_out.bits.rl1 = 0;
//     }
//     // digital_io_scan();

//     get_handler_entradas(req);
//     return ESP_OK;
// }








/* URI handler structure for GET /uri */
// httpd_uri_t uri_get = 
// {
//     .uri = "/",
//     .method = HTTP_GET,
//     .handler = get_handler_entradas,
//     .user_ctx = NULL
// };

// httpd_uri_t uri_get_saidas= 
// {
//     .uri = "/saidas",
//     .method = HTTP_GET,
//     .handler = get_handler_saidas,
//     .user_ctx = NULL
// };

// httpd_uri_t uri_get_entradas = 
// {
//     .uri = "/entradas",
//     .method = HTTP_GET,
//     .handler = get_handler_entradas,
//     .user_ctx = NULL
// };





