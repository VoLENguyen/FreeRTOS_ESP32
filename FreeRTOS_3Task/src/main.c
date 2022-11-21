#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BTN_CONTROL 32
#define BTN_0N 35
#define BTN_OFF 34
#define LED_BLINK 26
#define LED 27

void Task1(void *pvParameters);
void Task2(void *pvParameters);
void Task3(void *pvParameters);

TaskHandle_t xHandleTask1;
TaskHandle_t xHandleTask2;
TaskHandle_t xHandleTask3;

uint8_t pre_state = 0;

void configGPIO(){
    //  Create variable config
    gpio_config_t GPIO_config = {};

    // Config output
    GPIO_config.pin_bit_mask = ((1ULL << LED_BLINK) | (1ULL << LED));               /*!< GPIO pin: set with bit mask, each bit maps to a GPIO */                    
    GPIO_config.mode = GPIO_MODE_OUTPUT;  // cheess độ đầu ra                                          /*!< GPIO mode: set input/output mode                     */
    GPIO_config.pull_up_en = GPIO_PULLUP_DISABLE;                                   /*!< GPIO pull-up                                         */
    GPIO_config.pull_down_en = GPIO_PULLDOWN_DISABLE;                               /*!< GPIO pull-down                                       */
    GPIO_config.intr_type = GPIO_INTR_DISABLE;                                      /*!< GPIO interrupt type                                  */
    gpio_config(&GPIO_config);  

    // Config input
    GPIO_config.pin_bit_mask = ((1ULL << BTN_0N) | (1ULL << BTN_OFF) | (1ULL<< BTN_CONTROL));                                                           
    GPIO_config.mode = GPIO_MODE_INPUT;
    gpio_config(&GPIO_config);
}

void app_main(void)   
{
    configGPIO();

    xTaskCreate(Task1, "Task1", 1024, NULL, 6, &xHandleTask1);
    xTaskCreate(Task2, "Task2", 1024, NULL, 7, &xHandleTask2);
    xTaskCreate(Task3, "Task3", 1024, NULL, 5, &xHandleTask3);
}

void Task1( void * pvParameters )
{
    for(;;)
    {
        printf("Turning off the LED\n");
        gpio_set_level(LED_BLINK, 0);// low led tắt 
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("Turning on the LED\n");
        gpio_set_level(LED_BLINK, 1); // hig
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
// task2 //
void Task2( void * pvParameters )
{
    for(;;)
    {
        if(gpio_get_level(BTN_0N) == 1){
            while(gpio_get_level(BTN_0N) == 1);
            gpio_set_level(LED, 1);
            printf("Led on!\n");
        }
        if(gpio_get_level(BTN_OFF) == 1){
            while(gpio_get_level(BTN_OFF) == 1);
            gpio_set_level(LED, 0);
            printf("Led off!\n");
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);    
    }
}

void Task3( void * pvParameters )
{
    vTaskDelay(1000/portTICK_PERIOD_MS);
    for(;;)
    {
        if(gpio_get_level(BTN_CONTROL) == 1){
            while(gpio_get_level(BTN_CONTROL) == 1);
            printf("Control !!\n");
            if(pre_state == 0){
                pre_state = 1;
                printf("Pause Task1 !\n");
                vTaskSuspend(xHandleTask1); // vào trạng 
            } else if(pre_state == 1){
                pre_state = 0;
                printf("Run Task1 !\n");
                vTaskResume(xHandleTask1);
            } 
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
