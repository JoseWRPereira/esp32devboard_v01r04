// #include <stdio.h>
// #include <string.h>
#include "esp_http_server.h"
#include "wifi-ap-webserver.h"
#include "string.h"
#include "esp_log.h"

static const char * MARK = "tag";

uint16_t str_to_uint16( char * ptr )
{
    uint16_t n = 0;
    while( *ptr )
    {
        if( (*ptr >= '0') && (*ptr <= '9') )
        {
            n *= 10;
            n += (*ptr) - '0';
        }
        ++ptr;
    }
    return( n );
}
int32_t str_to_int32( char * ptr )
{
    int32_t n = 0;
    uint8_t neg = 0;
    while( *ptr )
    {
        if( (*ptr >= '0') && (*ptr <= '9') )
        {
            n *= 10;
            n += (*ptr) - '0';
        }
        if( *ptr == '-')
        {
            neg = 1;
        }
        ++ptr;
    }
    if( neg )
    {
        n *= -1;
    }
    return( n );
}



uint8_t web_digital_output_var = 0;
uint8_t web_digital_output( void )
{
    return( web_digital_output_var );
}

esp_err_t get_digital_output(httpd_req_t *req)
{
    // Read the URI line and get the host
    char *buf;
    size_t buf_len;
    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(MARK, "Host: %s", buf);
        }
        free(buf);
    }

    // Read the URI line and get the parameters
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) 
    {
        buf = malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) 
        {
            ESP_LOGI(MARK, "Found URL query: %s", buf);
            char param[32];
            if (httpd_query_key_value(buf, "output", param, sizeof(param)) == ESP_OK)
            {
                ESP_LOGI(MARK, "The OUTPUT value = %s", param);
                web_digital_output_var = str_to_uint16( param );
            }
        }
        free(buf);
    }

    return ESP_OK;
}
httpd_uri_t uri_get_digital_output = 
{
    .uri = "/digital",
    .method = HTTP_GET,
    .handler = get_digital_output,
    .user_ctx = NULL
};






int32_t web_stepmotor_var = 0;
int32_t web_stepmotor( void )
{
    return( web_stepmotor_var );
}
void web_stepmotor_reset( void )
{
    web_stepmotor_var = 0;
}

esp_err_t get_stepmotor(httpd_req_t *req)
{
    // Read the URI line and get the host
    char *buf;
    size_t buf_len;
    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(MARK, "Host: %s", buf);
        }
        free(buf);
    }

    // Read the URI line and get the parameters
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) 
    {
        buf = malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) 
        {
            ESP_LOGI(MARK, "Found URL query: %s", buf);
            char param[32];
            if (httpd_query_key_value(buf, "steps", param, sizeof(param)) == ESP_OK)
            {
                ESP_LOGI(MARK, "The value = %s", param);
                web_stepmotor_var = str_to_int32( param );
            }
        }
        free(buf);
    }

    return ESP_OK;
}
httpd_uri_t uri_get_stepmotor = 
{
    .uri = "/stepmotor",
    .method = HTTP_GET,
    .handler = get_stepmotor,
    .user_ctx = NULL
};













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





void add_str( char * destino, char * str )
{
    char i = 0;
    while( *(str+i) )
    {
        *(destino+i) = *(str+i);
        i++;
    }
}
void add_radio( char * str, char * name, uint8_t check )
{
    str[30] = name[0];
    str[31] = name[1];
    if( check )
        str[49] = 'd';
    else
        str[49] = ' ';
}

void add_form_action( char * str, char * uri)
{
    char i = 0;
    char str_offset = 13;
    while( *(uri+i) )
    {
        *(str+str_offset+i) = *(uri+i);
        i++;
        if( i > 16 )
            break;
    }
}

void add_str_submit( char * str, char * value )
{
    char i = 0;
    char str_offset = 27;
    while( *(value+i) )
    {
        *(str+str_offset+i) = *(value+i);
        i++;
        if( i > 16 )
            break;
    }
}


char tag_div_class_box[] = "<div class=\"box\"><h4>                </h4>";
char tag_table_tr[] = "<table><tr>";
char tag_table_tr_tr[] = "</tr><tr>";
char tab_table_th[] = "<th>   </th>";
char tab_input_radio[] = "<td><input type=\"radio\" name=\"  \" disabled checke ></td>";
char tab_table_end[] = "</tr></table>";
char tab_form_action[] = "<form action=                >";
char tab_input_submit[] = "<input type=\"submit\" value=\"Ler entradas\">";
char tab_div_end[] = "</form></div><hr>";



esp_err_t get_devboard(httpd_req_t *req)
{

/*

const char html_box_entradas[] = "<div class=\"box\">\
    <h4>Entradas</h4>\
    <table>\
        <tr>\
          <th>E0</th>\
          <th>E1</th>\
          <th>E2</th>\
          <th>E3</th>\
          <th>E4</th>\
          <th>E5</th>\
          <th>E6</th>\
          <th>E7</th>\
        </tr>\
        <tr>\
          <td><input type=\"radio\" name=\"E0\" disabled checked></td>\
          <td><input type=\"radio\" name=\"E2\" disabled checked></td>\
          <td><input type=\"radio\" name=\"E1\" disabled checked></td>\
          <td><input type=\"radio\" name=\"E3\" disabled checked></td>\
          <td><input type=\"radio\" name=\"E4\" disabled checke ></td>\
          <td><input type=\"radio\" name=\"E5\" disabled checke ></td>\
          <td><input type=\"radio\" name=\"E6\" disabled checke ></td>\
          <td><input type=\"radio\" name=\"E7\" disabled checke ></td>\
        </tr>\
    </table>\
    <form action=\"/entradas\">\
        <input type=\"submit\" value=\"Ler entradas\">\
    </form>\
</div>\
<hr>";

const char html_box_saidas[] = "<div class=\"box\">\
    <h4>Saídas</h4>\
    <form action=\"/saidas\">\
        <table>\
            <tr>\
              <th>K1</th>\
              <th>K2</th>\
              <th>CA0</th>\
              <th>CA1</th>\
              <th>S1</th>\
              <th>S2</th>\
              <th>S3</th>\
              <th>S4</th>\
            </tr>\
            <tr>\
              <td><input type=\"checkbox\" name=\"K1\"  value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"K2\"  value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"CA0\" value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"CA1\" value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"S1\"  value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"S2\"  value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"S3\"  value=\"1\" checke ></td>\
              <td><input type=\"checkbox\" name=\"S4\"  value=\"1\" checke ></td>\
            </tr>\
        </table>\
        <input type=\"submit\" value=\"Atualizar Saidas\">\
    </form>\
</div>\
<hr>";

const char html_box_motorpasso[] = "<div class=\"box\">\
    <h4>Motor de passo</h4>\
    <form action=\"/motorpasso\">\
        <input type=\"submit\" value=\"Girar\">\
        <input type=\"text\" name=\"graus\" value=\"360\" maxlength=\"4\" size=\"4\">\
        <label>graus.</label>\
    </form>\
</div>\
<hr>";

const char html_box_ambiente[] = "<div class=\"box\">\
    <h4>Ambiente</h4>\
    <form action=\"/tempumid\">\
        <table>\
            <tr>\
              <th>Temperatura</th>\
              <th>Umidade</th>\
            </tr>\
            <tr>\
              <td>20 &deg;C</td>\
              <td>50 %%</td>\
            </tr>\
        </table>\
        <input type=\"submit\" value=\"Atualizar\">\
    </form>\
</div>\
<hr>";

const char html_box_display[] = "<div class=\"box\">\
    <h4>Display</h4>\
    <form action=\"/display\">\
        <input type=\"text\" name=\"graus\" value=\"Arri Egua!\" maxlength=\"16\" size=\"16\">\
        <input type=\"submit\" value=\"Enviar\">\
    </form>\
</div>\
<hr>\
<hr>";
*/
// const char html_head[] = "<!DOCTYPE HTML><html><head><title>ESP32 Devboard</title>
// <meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"></head><body>";
// const char html_head_end[] = "<header><h1>ESP32 Devboard</h1></header>";
// const char html_end[] = "</body></html>";

    const char html_head[] = "<!DOCTYPE HTML><html><head><title>ESP32 Devboard</title></head><body>";
    const char html_header[] = "<header><h1>ESP32 Devboard</h1></header>";
    const char html_end[] = "</body></html>";

    char html_style[] = "<style>h1{text-align:center;}h4{text-align:center;margin:auto;}hr{border:1px solid #ccc;width:80%%;}\
    .box{text-align:center;margin-left:25%%;margin-right:25%%;margin-bottom:2px;}\
    table{width:95%%;table-layout:fixed;text-align:center;margin-left:auto;margin-right:auto;}\
    td,th{margin:0;text-align:center;}td{padding-bottom:12px;}@media(max-width:600px)\
    {.box{margin-left:10%%;margin-right:10%%;}th{font-size:85%%;}}\
    </style>";

    httpd_resp_set_status(req, "200 OK");       //      HTTP status string, 
    httpd_resp_set_type(req,"text/html");       //      Content Type
    httpd_resp_set_hdr(req,"charset","utf-8");  //  
  
    httpd_resp_sendstr_chunk(req,html_head);
    httpd_resp_sendstr_chunk(req,html_style);
    httpd_resp_sendstr_chunk(req,html_header);

// char tag_div_class_box[] = "<div class=\"box\"><h4>                </h4>";
    add_str( &tag_div_class_box[21], "Entradas" );
    httpd_resp_sendstr_chunk(req,tag_div_class_box);
// char tag_table_tr[] = "<table><tr>";
    httpd_resp_sendstr_chunk(req,tag_table_tr);

// char tab_table_th[] = "<th>   </th>";
    add_str( &tab_table_th[4],"E0");
    httpd_resp_sendstr_chunk(req,tab_table_th);
    add_str( &tab_table_th[4],"E1");
    httpd_resp_sendstr_chunk(req,tab_table_th);

// char tag_table_tr_tr[] = "</tr><tr>";
    httpd_resp_sendstr_chunk(req,tag_table_tr_tr);

// char tab_input_radio[] = "<td><input type=\"radio\" name=\"  \" disabled checke ></td>";
    add_radio(tab_input_radio,"E0",0);
    httpd_resp_sendstr_chunk(req,tab_input_radio);
    add_radio(tab_input_radio,"E1",1);
    httpd_resp_sendstr_chunk(req,tab_input_radio);

// char tab_table_end[] = "</tr></table>";
    httpd_resp_sendstr_chunk(req,tab_table_end);

// char tab_form_action[] = "<form action=                >";
    add_form_action(tab_form_action,"\"/entradas\"");
    httpd_resp_sendstr_chunk(req,tab_form_action);

// char tab_input_submit[] = "<input type=\"submit\" value=\"Ler entradas\">";
    add_str_submit(tab_input_submit,"\"Ler Entradas\"");
    httpd_resp_sendstr_chunk(req,tab_input_submit);
// char tab_div_end[] = "</form></div><hr>";
    httpd_resp_sendstr_chunk(req,tab_div_end);


    httpd_resp_sendstr_chunk(req,html_end);
    httpd_resp_sendstr_chunk(req,NULL);
    return ESP_OK;
}
httpd_uri_t uri_devboard = 
{
    .uri = "/devboard",
    .method = HTTP_GET,
    .handler = get_devboard,
    .user_ctx = NULL
};


esp_err_t get_json(httpd_req_t *req)
{
    const char resp[] = "{\"Placa\": \"DevBoard\"}";
    const char resp2[] = ",{\"Versao\":\"v01r04\"}";
    httpd_resp_set_status(req, "200 OK"); //      HTTP status string, 
    httpd_resp_set_type(req,"json");   //      Content Type
    httpd_resp_set_hdr(req,"charset","utf-8");    //  
    httpd_resp_sendstr_chunk(req,resp);
    httpd_resp_sendstr_chunk(req,resp2);
    httpd_resp_sendstr_chunk(req,NULL);
    return ESP_OK;
}
httpd_uri_t uri_json = 
{
    .uri = "/json",
    .method = HTTP_GET,
    .handler = get_json,
    .user_ctx = NULL
};




httpd_uri_t * uri_vector[] = {  
                                &uri_get_digital_output,
                                &uri_get_stepmotor,
                                &uri_example, 
                                &uri_test, 
                                &uri_devboard, 
                                &uri_json 
                            };
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





