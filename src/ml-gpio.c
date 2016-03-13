#include <string.h>

#include "jerry.h"
#include "hal_gpio.h"
#include "microlattice.h"

DELCARE_HANDLER(gpio) {
  /* mode */
  int mode_req_sz = jerry_api_string_to_char_buffer(args_p[1].v_string, NULL, 0);
  mode_req_sz *= -1;
  char mode_buffer [mode_req_sz+1]; // 不能有*
  mode_req_sz = jerry_api_string_to_char_buffer (args_p[1].v_string, (jerry_api_char_t *) mode_buffer, mode_req_sz);
  mode_buffer[mode_req_sz] = '\0';

  int pin = (int)args_p[0].v_float32;
  int func = (int)args_p[2].v_float32;

  hal_gpio_status_t ret;
  hal_pinmux_status_t ret_pinmux_status;
  ret = hal_gpio_init(pin);
  ret_pinmux_status = hal_pinmux_set_function(pin, func);

  if (strncmp (mode_buffer, "OUTPUT", (size_t)mode_req_sz) == 0) {
    int status = (int)args_p[3].v_float32;

    ret = hal_gpio_set_direction(pin, HAL_GPIO_DIRECTION_OUTPUT);
    ret = hal_gpio_set_output(pin, status);

    ret_val_p->type = JERRY_API_DATA_TYPE_BOOLEAN;
    ret_val_p->v_bool = true;

    return true;
  } else {
    // hal_gpio_data_t gpio_data_befor;
    hal_gpio_data_t gpio_data;

    /* method_buffer */
    int method_req_sz = jerry_api_string_to_char_buffer(args_p[3].v_string, NULL, 0);
    method_req_sz *= -1;
    char method_buffer [method_req_sz+1]; // 不能有*
    method_req_sz = jerry_api_string_to_char_buffer (args_p[3].v_string, (jerry_api_char_t *) method_buffer, method_req_sz);
    method_buffer[method_req_sz] = '\0';

    ret = hal_gpio_set_direction(pin, HAL_GPIO_DIRECTION_INPUT);

    if (strncmp (method_buffer, "pullup", (size_t)mode_req_sz) == 0) {
      ret = hal_gpio_pull_up(pin);
    } else if (strncmp (method_buffer, "pulldown", (size_t)mode_req_sz) == 0) {
      ret = hal_gpio_pull_down(pin);
    }

    ret = hal_gpio_get_input(pin, &gpio_data);
    ret = hal_gpio_disable_pull(pin);
    ret_val_p->type = JERRY_API_DATA_TYPE_FLOAT64;
    ret_val_p->v_float64 = gpio_data;
  }
  ret = hal_gpio_deinit(pin);
  return true;
}


void ml_gpio_init(void)
{
  REGISTER_HANDLER(gpio);
}