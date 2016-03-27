function gpio(pin) {
  this.pin = pin;
};

gpio.prototype.register = function() {
  return __pinmux(this.pin, 8);
}

gpio.prototype.write = function(status) {
  return __gpioWrite(this.pin, status);
}

gpio.prototype.read = function(method) {
  return __gpioWrite(this.pin, method);
}

module.exports = gpio;
