/* FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/* ESP32 */
#include "esp_system.h"
#include "esp_spi_flash.h"
/* C library (newlib) */
#include <stdio.h>

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
	printf("ESP32 chip model: %s r%d\n", \
			pszChipNames[_chipInfo.model], _chipInfo.revision);
	printf("  Core: %d\n", _chipInfo.cores);
	printf("  S.Flash: %dMB (%s)\n", _sflashMb, \
			(_chipInfo.features & CHIP_FEATURE_EMB_FLASH) ? "Embedded" : "External");
	printf("  Free heap size: %d / %d bytes\n", _intnHeapSz, _heapSz);
	if (_chipInfo.features & CHIP_FEATURE_WIFI_BGN)
	{
		printf("  WiFi supported (802.11bgn 2.4GHz)\n");
	}
	if (_chipInfo.features & CHIP_FEATURE_BT)
	{
		printf("  Bluetooth supported %s\n", \
				(_chipInfo.features & CHIP_FEATURE_BLE) ? "(+ BLE)" : "");
	}
}


void app_main(void)
{
	print_chip_info();

    while (1) {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
