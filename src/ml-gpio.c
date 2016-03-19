#include <string.h>

#include "jerry.h"
#include "hal_gpio.h"
#include "microlattice.h"

DELCARE_HANDLER(gpioWrite) {

  int pin = (int)args_p[0].v_float32;
  int status = (int)args_p[1].v_float32;

  hal_gpio_status_t ret;
  ret = hal_gpio_init(pin);
  ret = hal_gpio_set_direction(pin, HAL_GPIO_DIRECTION_OUTPUT);
  ret = hal_gpio_set_output(pin, status);
  ret = hal_gpio_deinit(pin);

  ret_val_p->type = JERRY_API_DATA_TYPE_BOOLEAN;
  ret_val_p->v_bool = true;
  return true;

}

DELCARE_HANDLER(gpioRead) {

  int pin = (int)args_p[0].v_float32;
  /* method_buffer */
  int method_req_sz = jerry_api_string_to_char_buffer(args_p[1].v_string, NULL, 0);
  method_req_sz *= -1;
  char method_buffer [method_req_sz+1]; // 不能有*
  method_req_sz = jerry_api_string_to_char_buffer (args_p[1].v_string, (jerry_api_char_t *) method_buffer, method_req_sz);
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

  ret_val_p->type = JERRY_API_DATA_TYPE_FLOAT64;
  ret_val_p->v_float64 = gpio_data;
  return true;
}

void ml_gpio_init(void)
{
  REGISTER_HANDLER(gpioWrite);
  REGISTER_HANDLER(gpioRead);
}