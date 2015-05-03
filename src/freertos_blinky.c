#include <registers.h>
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>

int main(int argc, char * argv[]) {

  vTaskStartScheduler();

  // We want to blink LEDs connected to GPIO pin G13 and G14
  // (this is documented in our board's PDF)
  //
  // GPIO are grouped by letter, and GPIO "G" live on the "AHB1" bus
  // (this is documented in the STM32F4 reference mnual, page 65)

  // Step 1 : Enable clock in RCC_AHBxENR
  RCC_AHB1ENR->GPIOGEN = 1;


  // Step 2 : Configure the GPIO pin to "general purpose output
  GPIO_MODER(GPIOG)->MODER13 = GPIO_MODE_OUTPUT;
  GPIO_MODER(GPIOG)->MODER14 = GPIO_MODE_OUTPUT;

  // Per doc, the output is push-pull by default (yay)
  // And we should also set the output speed, but really
  // we don't care (we're doing something super slow)

  long delay = 50000;

  while (1) {
    GPIO_ODR(GPIOG)->ODR13 = 0;
    GPIO_ODR(GPIOG)->ODR14 = 1;

//    sleep(delay);

    GPIO_ODR(GPIOG)->ODR13 = 1;
    GPIO_ODR(GPIOG)->ODR14 = 0;

//    sleep(delay);
  }
}
