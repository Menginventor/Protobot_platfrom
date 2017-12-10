#include <mbed.h>
#include <param.h>
class motor {

  public:
    PwmOut  *M_A;
    PwmOut  *M_B;


    motor(PinName pin_A,PinName pin_B);
    void drive(float pwr);


};

class QE{
public:
  InterruptIn *enA;
  InterruptIn *enB;
  DigitalIn   *d_enA;
  DigitalIn   *d_enB;
  int q_state = 0;
  QE(PinName pin_A,PinName pin_B);
  void get_q_state();

  void a_rise();
  void a_fall();

  void b_rise();
  void b_fall();
};
class protobot {
  public:
    motor *left_motor;
    motor *right_motor;
    QE *left_encoder;
    QE *right_encoder;
    DigitalIn *mybutton;
    protobot();
    void press_button();
};
