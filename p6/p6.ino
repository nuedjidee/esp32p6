
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4
int  sl, sr ;
void setup()
{ Serial.begin(9600);
  pinMode(34, INPUT);
  pinMode(35, INPUT);

}
void loop()
{
  sl = analogRead(34);
  sr = analogRead(35);

  if (sl > 60 && sr < 60) {
    l(250);delay(20);
  }
  if (sl < 60 && sr > 60) {
    r(250);delay(20);
  }
  if (sl < 60 && sr < 60) {
    f(250);
  }
  delay(5);
}
void f(int sp) {
  motor(1, FORWARD, sp);
  motor(2, FORWARD, sp);
}
void r(int sp) {
  motor(1, FORWARD, sp);
  motor(2, BACKWARD, sp);
}
void l(int sp) {
  motor(1, BACKWARD, sp);
  motor(2, FORWARD, sp);
}
void b(int sp) {
  motor(1, BACKWARD, sp);
  motor(2, BACKWARD, sp);
}
void s() {
  motor(1, RELEASE, 0);
  motor(2, RELEASE, 0);
}
