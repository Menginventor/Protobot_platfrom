#include <protobot_d1.h>
#include <mbed.h>


motor::motor(PinName pin_A,PinName pin_B){
        PwmOut PWM_A(pin_A);
        PwmOut PWM_B(pin_B);
        M_A = new PwmOut(pin_A);
        M_B = new PwmOut(pin_B);
        M_A->period(default_PWM_frequency);
        M_B->period(default_PWM_frequency);
}

void motor::drive(float pwr){

        if(pwr>=0) {
                M_B->write(0.0);
                M_A->write(pwr);
        }
        else{
                M_A->write(0.0);
                M_B->write(-pwr);
        }

}
protobot::protobot(){
        /*setup parameter */
        left_motor = new motor (left_motor_A_pin,left_motor_B_pin);
        right_motor = new motor (right_motor_A_pin,right_motor_B_pin);
        left_encoder = new QE(left_encoder_A_pin,left_encoder_B_pin);
        right_encoder =  new QE(right_encoder_A_pin,right_encoder_B_pin);
        mybutton = new DigitalIn(mybutton_pin);
}
void protobot::press_button(){
        while(mybutton->read() == 1) ; //wait for press button
}
void QE::get_q_state(){
        int p_state = q_state;

        if( d_enA->read() == 0) {
                if( d_enB->read() == 0) {
                        q_state = 0;
                }
                else{//B == 1
                        q_state = 3;
                }
        }
        else{//A == 1
                if( d_enB->read() == 0) {
                        q_state = 1;
                }
                else{//B == 1
                        q_state = 2;
                }
        }
        if (relative_angular_distant != NULL) {
                if (q_state - p_state ==1) {
                    *relative_angular_distant++;
                }
                else if (q_state - p_state == -1) {
                    *relative_angular_distant--;
                }
                else if (q_state - p_state ==-3) {
                    *relative_angular_distant++;
                }
                else if (q_state - p_state == 3) {
                    *relative_angular_distant--;
                }
        }

}
QE::QE(PinName pin_A,PinName pin_B){
        /*assign pin*/
        enA = new InterruptIn(pin_A);
        enB = new InterruptIn(pin_B);
        d_enA = new DigitalIn(pin_A);
        d_enB = new DigitalIn(pin_B);
        get_q_state();
        enA->rise(callback(this,&QE::a_rise));
        enB->rise(callback(this,&QE::b_rise));
        enA->fall(callback(this,&QE::a_fall));
        enB->fall(callback(this,&QE::b_fall));


}
void QE::a_rise(){
        get_q_state();
}
void QE::a_fall(){
        get_q_state();
}
void QE::b_rise(){
        get_q_state();
}
void QE::b_fall(){
        get_q_state();
}
