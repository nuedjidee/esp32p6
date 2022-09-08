#define MOTORLATCH 19 //12
#define MOTORCLK 17//4
#define MOTORENABLE 14//7
#define MOTORDATA 12 //8
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 5
#define MOTOR3_B 7
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR1_PWM 23// 11
#define MOTOR2_PWM 25//3
#define MOTOR3_PWM 27//6
#define MOTOR4_PWM 16//5
#define SERVO1_PWM 5//10
#define SERVO2_PWM 13//9
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4
void example(){
  motor(1, FORWARD, 255);
  motor(2, FORWARD, 255);
  motor(3, FORWARD, 0);
  motor(4, FORWARD, 100);
  delay(2000);
  // Be friendly to the motor: stop it before reverse.
  motor(1, RELEASE, 0);
  motor(2, RELEASE, 0);
  motor(3, RELEASE, 0);
  motor(4, RELEASE, 0);
  delay(100);
  motor(1, BACKWARD, 255);
  motor(2, BACKWARD, 100);
  motor(3, BACKWARD, 0);
  motor(4, BACKWARD, 100);
  delay(2000);
  motor(1, RELEASE, 0);
  motor(2, RELEASE, 0);
  motor(3, RELEASE, 0);
  motor(4, RELEASE, 0);
  delay(100);
  }
void analogWrite(int a,int b,int c){
  ledcSetup(c,490,8);
  ledcAttachPin(a, c);
  ledcWrite(c, b);
 // delay(9);
  }
void motor(int nMotor, int command, int speed)
{
  int motorA, motorB;
  if (nMotor >= 1 && nMotor <= 4)
  {
    switch (nMotor)
    {
      case 1:
        motorA = MOTOR1_A;
        motorB = MOTOR1_B;
        break;
      case 2:
        motorA = MOTOR2_A;
        motorB = MOTOR2_B;
        break;
      case 3:
        motorA = MOTOR3_A;
        motorB = MOTOR3_B;
        break;
      case 4:
        motorA = MOTOR4_A;
        motorB = MOTOR4_B;
        break;
      default:
        break;
    }
    switch (command)
    {
      case FORWARD:
        motor_output (motorA, HIGH, speed);
        motor_output (motorB, LOW, -1); // -1: no PWM set
        break;
      case BACKWARD:
        motor_output (motorA, LOW, speed);
        motor_output (motorB, HIGH, -1); // -1: no PWM set
        break;
      case BRAKE:
        motor_output (motorA, LOW, 255); // 255: fully on.
        motor_output (motorB, LOW, -1); // -1: no PWM set
        break;
      case RELEASE:
        motor_output (motorA, LOW, 0); // 0: output floating.
        motor_output (motorB, LOW, -1); // -1: no PWM set
        break;
      default:
        break;
    }
  }
}
void motor_output (int output, int high_low, int speed)
{
  int motorPWM;
  switch (output)
  {
    case MOTOR1_A:
    case MOTOR1_B:
      motorPWM = MOTOR1_PWM;
      break;
    case MOTOR2_A:
    case MOTOR2_B:
      motorPWM = MOTOR2_PWM;
      break;
    case MOTOR3_A:
    case MOTOR3_B:
      motorPWM = MOTOR3_PWM;
      break;
    case MOTOR4_A:
    case MOTOR4_B:
      motorPWM = MOTOR4_PWM;
      break;
    default:
      speed = -3333;
      break;
  }
  if (speed != -3333)
  {
    shiftWrite(output, high_low);
    // set PWM only if it is valid
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPWM, speed,output);
    }
  }
}
void shiftWrite(int output, int high_low)
{
  static int8_t latch_copy;
  static int shift_register_initialized = false;
  // Do the initialization on the fly,
  // at the first time it is used.
  if (!shift_register_initialized)
  {
    // Set pins for shift register to output
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);
    // Set pins for shift register to default value (low);
    digitalWrite(MOTORDATA, LOW);
    digitalWrite(MOTORLATCH, LOW);
    digitalWrite(MOTORCLK, LOW);
    // Enable the shift register, set Enable pin Low.
    digitalWrite(MOTORENABLE, LOW);
    // start with all outputs (of the shift register) low
    latch_copy = 0;
    shift_register_initialized = true;
  }
  // The defines HIGH and LOW are 1 and 0.
  // So this is valid.
  bitWrite(latch_copy, output, high_low);
  //Serial.println(latch_copy,BIN);
  shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_copy);
  delayMicroseconds(5); // For safety, not really needed.
  digitalWrite(MOTORLATCH, HIGH);
  delayMicroseconds(5); // For safety, not really needed.
  digitalWrite(MOTORLATCH, LOW);
}
