#include <wiring_private.h>  //funções sbi() e cbi() do arduino

class ModuladorPWM
{};

class ConvSincrBuck : public ModuladorPWM
{
  public:
//    ConvSincrBuck(uint8_t pin_low, uint8_t pin_high);
    void config();
    void setDutyCicle(uint8_t duty);
};


class ConvSincrBoost : public ModuladorPWM
{
  public:
//    ConvSincrBuck(uint8_t pin_low, uint8_t pin_high);
    void config();
    void setDutyCicle(uint8_t duty);
    void turnOn();
    void turnOff();
};
