# ml-gpio

## Required

* ml-pinmux

## API

``` js
/* Read api */

gpioRead(
  pin, // nubmer
  method, // string, pullup or pulldown
)

/* Write api */

gpioWrite(
  pin, // nubmer
  value, // number
)

```

## Example

``` js
  pinmux(35, 8);
  gpioWrite(35, 0);

```
