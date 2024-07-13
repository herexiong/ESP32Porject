#ifndef WIFI_H_
#define WIFI_H_

#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "lwip/ip4_addr.h"

void wifi_start(void);
void wifi_stop(void);

#endif