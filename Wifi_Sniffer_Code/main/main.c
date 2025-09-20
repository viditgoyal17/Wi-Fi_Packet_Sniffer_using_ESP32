#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

static const char *TAG = "WIFI_SNIFFER";

// Packet handler callback
static void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type) {
    const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
    const uint8_t *payload = ppkt->payload;

    // Example: Log source MAC of management frames
    if (type == WIFI_PKT_MGMT) {
        char mac[18];
        sprintf(mac, "%02x:%02x:%02x:%02x:%02x:%02x",
                payload[10], payload[11], payload[12],
                payload[13], payload[14], payload[15]);
        ESP_LOGI(TAG, "Mgmt frame from: %s | RSSI: %d", mac, ppkt->rx_ctrl.rssi);
    }
}

// Main application entry
void app_main(void) {
    // Initialize NVS
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize Wi-Fi driver
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_start());

    // Enable promiscuous mode and register callback
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_packet_handler);

    ESP_LOGI(TAG, "Wi-Fi sniffer started...");
}
