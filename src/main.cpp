#include <protobot_d1.h>
Serial pc(USBTX, USBRX);



protobot robot;
int main() {
        pc.baud(115200);
        robot.press_button();

        robot.left_motor->drive(0.25);
        robot.right_motor->drive(0.25);
        while(1) {
            pc.printf("%d\t%d\n",robot.left_encoder->q_state,robot.right_encoder->q_state );

        }
}
