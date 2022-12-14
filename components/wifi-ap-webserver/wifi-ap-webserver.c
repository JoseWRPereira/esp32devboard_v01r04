#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_http_server.h"
#include "wifi-ap-webserver.h"
#include "pages.h"


#define CONFIG_ESP_WIFI_SSID            "DevBoard"
#define CONFIG_ESP_WIFI_PASSWORD        "12345678"
#define CONFIG_ESP_WIFI_CHANNEL         1
#define CONFIG_ESP_MAX_STA_CONN         5





static const char *TAG = "wifi softAP";

static void wifi_event_handler( void* arg, 
                                esp_event_base_t event_base,
                                int32_t event_id, 
                                void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) 
    {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } 
    else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) 
    {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}

void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            &wifi_event_handler,
            NULL,
            NULL
        )
    );

    wifi_config_t wifi_config = 
    {
        .ap = 
        {
            .ssid = CONFIG_ESP_WIFI_SSID,
            .ssid_len = strlen(CONFIG_ESP_WIFI_SSID),
            .channel = CONFIG_ESP_WIFI_CHANNEL,
            .password = CONFIG_ESP_WIFI_PASSWORD,
            .max_connection = CONFIG_ESP_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .pmf_cfg = 
            {
                .required = false,
            },
        },
    };
    if (strlen(CONFIG_ESP_WIFI_PASSWORD) == 0) 
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

	esp_wifi_connect();
    ESP_LOGI(   TAG, 
        "wifi_init_softap finished. SSID:%s password:%s channel:%d",
        CONFIG_ESP_WIFI_SSID, 
        CONFIG_ESP_WIFI_PASSWORD, 
        CONFIG_ESP_WIFI_CHANNEL    
    );
}

void nvs_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");
}




esp_err_t get_help(httpd_req_t *req)
{
    const char resp[] = "<h2>help</h2><hr><br>project-name : esp32devboard <br> version : v01r04 <br> hw-dev : DuffVonAxel/JoseWRPereira <br> sw-dev : JoseWRPereira <br> for-more : github.com/JoseWRPereira/esp32devboard_v01r04";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t uri_help = 
{
    .uri = "/help",
    .method = HTTP_GET,
    .handler = get_help,
    .user_ctx = NULL
};

httpd_handle_t start_webserver(void)
{
    size_t i;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &uri_help);
        for( i=0; i<uri_vector_number_of_elements; i++ )
            httpd_register_uri_handler(server, uri_vector[i]);
    }
    return server;
}

void stop_webserver(httpd_handle_t server)
{
    if (server)
    {
        httpd_stop(server);
    }
}




/// @brief Initialization of wifi module as soft acces point, 
///         and web server starting.
/// @param  void
void wifi_init( void )
{
    nvs_init();
    wifi_init_softap();
    start_webserver();
}