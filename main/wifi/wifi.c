#include "wifi.h"

#define TAG "WiFi"
#define MAX_APS 10

//初始化标志位
int wifi_inited = 0;
int wifi_connected = 0;
//wifi存储数据
wifi_ap_record_t ap_records[MAX_APS];

void wifi_scan_task(void *pt);
void wifi_scan_show();
extern void show_wifiResult_screen(int aps_count);

extern char IPV4ADDR[20];
extern char GATEWAY[20];
extern char RSSI[10];//信号强度
extern void show_wifi_info(void);
extern void show_wifi_fail(void);

//扫描任务，wifi扫描需要时间，所以设置为任务
void wifi_scan_task(void *pt)
{
	ESP_LOGI(TAG, "2.WiFi初始化阶段");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_LOGI(TAG, "3.WiFi启动化阶段");
    ESP_ERROR_CHECK(esp_wifi_start());	
    ESP_LOGI("WIFI", "4. Wi-Fi 扫描");
    wifi_country_t wifi_country_config = {
        .cc = "CN",
        .schan = 1,
        .nchan = 13,
    };
    ESP_ERROR_CHECK(esp_wifi_set_country(&wifi_country_config));
    ESP_ERROR_CHECK(esp_wifi_scan_start(NULL, false));
    vTaskDelete(NULL);
}

//展示扫描结果
void wifi_scan_show(void)
{
    uint16_t ap_num = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_num));
    ESP_LOGI("WIFI", "AP Count : %d", ap_num);

    memset(ap_records, 0, sizeof(ap_records));

    uint16_t aps_count = MAX_APS;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&aps_count, ap_records));

    ESP_LOGI("WIFI", "AP Count: %d", aps_count);

    // printf("%30s %s %s %s\n", "SSID", "频道", "强度", "MAC地址");
    printf("%30s %s %s\n", "SSID", "频道", "强度");

	//调用ui函数展示
    for (int i = 0; i < aps_count; i++)
    {
        char text[60] = {0};
        sprintf(text,"%30s CH:%3d RRSI:%3d db\n",ap_records[i].ssid,ap_records[i].primary,ap_records[i].rssi);
        printf("%s",text);
        // printf("%30s  %3d  %3d  %02X-%02X-%02X-%02X-%02X-%02X\n", ap_records[i].ssid, ap_records[i].primary, ap_records[i].rssi, ap_records[i].bssid[0], ap_records[i].bssid[1], ap_records[i].bssid[2], ap_records[i].bssid[3], ap_records[i].bssid[4], ap_records[i].bssid[5]);
    }
	show_wifiResult_screen(aps_count);
}

static void run_on_event(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_SCAN_DONE) {
        wifi_scan_show();
    }else if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        wifi_event_sta_disconnected_t* event = (wifi_event_sta_disconnected_t*) event_data;
        ESP_LOGI(TAG, "WiFi disconnected, reason: %s", esp_err_to_name(event->reason));
        ESP_LOGI(TAG, "WiFi disconnected, reason: %d", event->reason);

        // 针对认证失败的重连策略
        if (event->reason == WIFI_REASON_AUTH_FAIL) {
            ESP_LOGI(TAG, "Authentication failed");
            //密码错误，跳转第三屏幕，显示信息
            show_wifi_fail();
        }else if (event->reason == WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT){
            ESP_LOGI(TAG, "HANDSHAKE_TIMEOUT");
            show_wifi_fail();
        }else if (event->reason == WIFI_REASON_NO_AP_FOUND){
            ESP_LOGI(TAG, "NO_AP_FOUND");
            show_wifi_fail();
        }else if (event->reason == WIFI_REASON_HANDSHAKE_TIMEOUT){
            ESP_LOGI(TAG, "HANDSHAKE_TIMEOUT");
            show_wifi_fail();
        }else {
            ESP_LOGI(TAG, "Other disconnect reason, restarting WiFi module");
            // ESP_ERROR_CHECK(esp_wifi_stop());
            // vTaskDelay(1000 / portTICK_PERIOD_MS); // 延迟1秒
            // ESP_ERROR_CHECK(esp_wifi_start());
            // ESP_ERROR_CHECK(esp_wifi_connect());
        }
    }else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        wifi_connected = 1;
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        strcpy(IPV4ADDR,ip4addr_ntoa(&event->ip_info.ip));
        ip4addr_ntoa_r(&event->ip_info.ip, IPV4ADDR, 20);
        strcpy(GATEWAY,ip4addr_ntoa(&event->ip_info.gw));
        ESP_LOGI("WiFi ip", "Got IP: %s", IPV4ADDR);
        ESP_LOGI("WiFi GTW", "Got GTW: %s", GATEWAY);
        // 获取 WiFi 信号强度（RSSI）
        wifi_ap_record_t ap_info;
        if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK) {
            int8_t rssi = ap_info.rssi;
            snprintf(RSSI, sizeof(char)*10,"%d dBm", rssi); // 将 RSSI 转换为字符串
            ESP_LOGI("WiFi", "Signal strength (RSSI): %s", RSSI);
        } else {
            ESP_LOGE("WiFi", "Failed to get WiFi signal strength");
        }
        show_wifi_info();
    }
}

void wifi_start(void){
	if (!wifi_inited)
	{
		//NVS
		ESP_LOGI(TAG, "0. 初始化NVS存储");
		esp_err_t ret = nvs_flash_init();
		if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
		{
			ESP_ERROR_CHECK(nvs_flash_erase());
			ret = nvs_flash_init();
		}
		ESP_ERROR_CHECK(ret);

        //wifi初始化
		ESP_LOGI(TAG, "1.WiFi初始化阶段");
		ESP_ERROR_CHECK(esp_netif_init());
		ESP_ERROR_CHECK(esp_event_loop_create_default());
		esp_netif_create_default_wifi_sta();
        //配置WiFi驱动程序
		wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
		ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
        //注册事件
		esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_SCAN_DONE, run_on_event, NULL);
        esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, run_on_event, NULL);
        esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, run_on_event, NULL);
		wifi_inited = 1;
	}
	xTaskCreate(wifi_scan_task, "wifi scan task", 1024 * 12, NULL, 1, NULL);
}

void wifi_stop(void) {
    ESP_LOGI(TAG, "开始关闭WiFi");

    // 停止WiFi
    ESP_ERROR_CHECK(esp_wifi_stop());
    ESP_LOGI(TAG, "WiFi已停止");

    // 取消事件处理程序的注册
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_SCAN_DONE, run_on_event));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, run_on_event));
    ESP_LOGI(TAG, "WiFi事件处理程序已取消注册");

    // 关闭WiFi驱动程序
    ESP_ERROR_CHECK(esp_wifi_deinit());
    ESP_LOGI(TAG, "WiFi驱动程序已关闭");

    // 销毁默认WiFi STA
    esp_netif_t* wifi_netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    if (wifi_netif) {
        esp_netif_destroy(wifi_netif);
        ESP_LOGI(TAG, "默认WiFi STA已销毁");
    } else {
        ESP_LOGE(TAG, "默认WiFi STA销毁失败");
    }

    // 清理网络接口//会导致重启
    // ESP_ERROR_CHECK(esp_netif_deinit());
    // ESP_LOGI(TAG, "网络接口已清理");

    // 清理默认事件循环
    ESP_ERROR_CHECK(esp_event_loop_delete_default());
    ESP_LOGI(TAG, "默认事件循环已清理");

    ESP_LOGI(TAG, "WiFi关闭完成");
    wifi_inited = 0;
}

