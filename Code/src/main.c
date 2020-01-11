#include "stm32f10x.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
//#include "event_groups.h"


//void delay(uint32_t delay)	{	for(volatile uint32_t i = 0; i < delay;i++){}	}
//uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];

//********************************************************************************
//tasks handle
TaskHandle_t led1Task;

//********************************************************************************
//private function prototype
static void gpioInit(void);		//gpio init

//********************************************************************************
//task prototype
static void led1Blink(void);


//********************************************************************************
//main function
int main (void)
{
	gpioInit();
	
	xTaskCreate((TaskFunction_t)led1Blink, "ledBlink", 24, NULL, 1, &led1Task);	
	
	vTaskStartScheduler();	
	
	while(1) {	}	
}

//********************************************************************************
//gpio init
static void gpioInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;			//enable clock for GPIOA
	GPIOA->CRL &= ~GPIO_CRL_CNF5;						//cleare CNF PA5 
	GPIOA->CRL |= GPIO_CRL_MODE5_1;					//	
}

//********************************************************************************
//task led 1
static void led1Blink(void)
{
	for(;;)
	{		
		GPIOA->BSRR = GPIO_BSRR_BR5;
		vTaskDelay(pdMS_TO_TICKS(150));
		GPIOA->BSRR = GPIO_BSRR_BS5;
		vTaskDelay(pdMS_TO_TICKS(150));		
	}	
}
	

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
//static portBASE_TYPE xPrinted = pdFALSE;
volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    /* Parameters are not used. */
    ( void ) ulLine;
    ( void ) pcFileName;

    taskENTER_CRITICAL();
    {
        /* You can step out of this function to debug the assertion by using
        the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
        value. */
        while( ulSetToNonZeroInDebuggerToContinue == 0 )
        {
        }
    }
    taskEXIT_CRITICAL();
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task’s
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task’s stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*———————————————————–*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task’s state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task’s stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

