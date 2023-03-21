int pin = A1;
unsigned long PWM_period;

void setup()
{
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  PWM_period = pulseIn(pin, HIGH);
  //Serial.println("PWM duration =");
  Serial.print(PWM_period);
  Serial.println("");
}
