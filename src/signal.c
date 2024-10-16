#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "signaling.h"


void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{


  // Wait for the request semaphore
    if (xSemaphoreTake(request, portMAX_DELAY) == pdTRUE) {
      
        data->output = data->input + 5;
    
        // Signal that the calculation is done by giving the response semaphore
        xSemaphoreGive(response);
    }


}

BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
     
 // Send the request by giving the request semaphore
    if (xSemaphoreGive(request) == pdTRUE) {
        // Wait for the response semaphore, signaling completion of the worker task
        if (xSemaphoreTake(response, portMAX_DELAY) == pdTRUE) {
            return pdTRUE;  // Success
        }
    }
    return pdFALSE;  // Failure
}