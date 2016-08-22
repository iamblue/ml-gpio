#include <string.h>

#include "jerry-api.h"
#include "hal_gpio.h"
#include "microlattice.h"

DELCARE_HANDLER(__gpioWrite) {

  int pin = (int) jerry_get_number_value(args_p[0]);
  int status = (int) jerry_get_number_value(args_p[1]);

  hal_gpio_status_t ret;
  ret = hal_gpio_init(pin);
  ret = hal_gpio_set_direction(pin, HAL_GPIO_DIRECTION_OUTPUT);
  ret = hal_gpio_set_output(pin, status);
  ret = hal_gpio_deinit(pin);

  return jerry_create_boolean (true);
}

DELCARE_HANDLER(__gpioRead) {

  int pin = (int) jerry_get_number_value(args_p[0]);

  jerry_size_t method_req_sz = jerry_get_string_size (args_p[1]);
  jerry_char_t method_buffer[method_req_sz];
  jerry_string_to_char_buffer (args_p[1], method_buffer, method_req_sz);
  method_buffer[method_req_sz] = '\0';

  hal_gpio_status_t ret;
  ret = hal_gpio_init(pin);
  hal_gpio_data_t gpio_data;
  ret = hal_gpio_set_direction(pin, HAL_GPIO_DIRECTION_INPUT);

  if (strncmp (method_buffer, "pullup", (size_t)method_req_sz) == 0) {
    ret = hal_gpio_pull_up(pin);
  } else if (strncmp (method_buffer, "pulldown", (size_t)method_req_sz) == 0) {
    ret = hal_gpio_pull_down(pin);
  }

  ret = hal_gpio_get_input(pin, &gpio_data);
  ret = hal_gpio_disable_pull(pin);
  ret = hal_gpio_deinit(pin);

  return jerry_create_number ((double) gpio_data);;
}

void ml_gpio_init(void)
{
  REGISTER_HANDLER(__gpioWrite);
  REGISTER_HANDLER(__gpioRead);
}