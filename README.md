# ml-gpio

## Required

* ml-pinmux

## API

``` js
/* Read api */

__gpioRead(
  pin, // nubmer
  method, // string, pullup or pulldown
)

/* Write api */

__gpioWrite(
  pin, // nubmer
  value, // number
)

```

## Example

``` js
  __pinmux(35, 8);
  __gpioWrite(35, 0);

```
