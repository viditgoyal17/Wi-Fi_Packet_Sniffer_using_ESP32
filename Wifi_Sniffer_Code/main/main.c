#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_timer.h"

static int64_t last_print_time = 0; 

static void print_mac(const uint8_t *mac) {
    printf("%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

static const char* get_packet_type_name(uint8_t frame_type) {
    switch (frame_type) {
        case 0x80: return "Beacon";
        case 0x40: return "Probe Request";
        case 0x50: return "Probe Response";
        case 0x08: return "Data";
        default: return "Other";
    }
}

static void wifi_sniffer_packet_handler(void* buff, wifi_promiscuous_pkt_type_t type) {
    
    int64_t now = esp_timer_get_time(); // current time in microseconds

    if (now - last_print_time < 1000000) {       // 1 second rate limit
        return; 
    }
    last_print_time = now; 

    const wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buff;
    const uint8_t *payload = pkt->payload;

    uint8_t subtype = payload[0] & 0xF0;    // Subtype bits (high nibble)

    const uint8_t *dest_mac = payload + 4;
    const uint8_t *src_mac = payload + 10;

    printf("\n---------------------------------\n");
    printf("Channel: %d\n", pkt->rx_ctrl.channel);
    printf("RSSI: %d dBm\n", pkt->rx_ctrl.rssi);
    printf("Packet Type: %s\n", get_packet_type_name(subtype));
    printf("\nSource MAC: ");
    print_mac(src_mac);
    printf("\nDestination MAC: ");
    print_mac(dest_mac);
    printf("\n");

    if (subtype == 0x80 || subtype == 0x50) {
        uint8_t ssid_len = payload[37];
        if (ssid_len > 0 && ssid_len <= 32) {
            char ssid[33];
            memcpy(ssid, payload + 38, ssid_len);
            ssid[ssid_len] = '\0';
            printf("SSID: %s\n", ssid);
        } else {
            printf("SSID: (Hidden)\n");
        }
    }
}


void channel_hop_task(void *pvParameter) {
    uint8_t current_channel = 1;
    while (true) {
        esp_wifi_set_channel(current_channel, WIFI_SECOND_CHAN_NONE);
        printf("\n--- Switching to Channel %d ---\n", current_channel);
        current_channel++;
        if (current_channel > 13) {
            current_channel = 1;
        }
        vTaskDelay(pdMS_TO_TICKS(2000)); // 2 seconds delay
    }
}

void app_main(void) {
    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize Wi-Fi
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_start());

    // Enable Promiscuous mode
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous_rx_cb(&wifi_sniffer_packet_handler));

    printf("Wi-Fi Sniffer started (showing detailed packet info)...\n");

    // Start Channel Hopping
    xTaskCreate(&channel_hop_task, "channel_hop_task", 2048, NULL, 5, NULL);
}