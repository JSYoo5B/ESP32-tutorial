/* FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/* ESP32 */
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

static const char* TAG = "CHIP_INFO";

void print_chip_info()
{
	esp_chip_info_t _chipInfo;
	char *pszChipNames[] = { "Unidentified", "ESP32", "ESP32s2" };
	uint32_t _sflashMb;
	uint32_t _intnHeapSz;
	uint32_t _heapSz;

	/* Get chip information */
	esp_chip_info(&_chipInfo);
	_sflashMb = spi_flash_get_chip_size();
	_sflashMb /= (1024 * 1024);
	_intnHeapSz = esp_get_free_internal_heap_size();
	_heapSz = esp_get_free_heap_size();

	/* Print chip information */
	ESP_LOGI(TAG, "ESP32 chip model: %s r%d", \
			pszChipNames[_chipInfo.model], _chipInfo.revision);
	ESP_LOGD(TAG, "  Core: %d", _chipInfo.cores);
	ESP_LOGD(TAG, "  S.Flash: %dMB (%s)", _sflashMb, \
			(_chipInfo.features & CHIP_FEATURE_EMB_FLASH) ? "Embedded" : "External");
	ESP_LOGV(TAG, "  Free heap size: %d / %d bytes\n", _intnHeapSz, _heapSz);
	if (_chipInfo.features & CHIP_FEATURE_WIFI_BGN)
	{
		ESP_LOGD(TAG, "  WiFi supported (802.11bgn 2.4GHz)");
	}
	if (_chipInfo.features & CHIP_FEATURE_BT)
	{
		ESP_LOGD(TAG, "  Bluetooth supported %s", \
				(_chipInfo.features & CHIP_FEATURE_BLE) ? "(+ BLE)" : "");
	}
}


void app_main(void)
{
	esp_log_level_set(TAG, ESP_LOG_ERROR);
	print_chip_info();
	
	esp_log_level_set(TAG, ESP_LOG_INFO);
	print_chip_info();
    
	while (1) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
