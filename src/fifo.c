#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include <stdio.h>

#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
   struct request_msg data; 
   xQueueReceive(requests, &data, portMAX_DELAY);
   data.output = data.input +5;
   data.handled_by = id;
   xQueueSendToBack(results, &data, portMAX_DELAY);
}