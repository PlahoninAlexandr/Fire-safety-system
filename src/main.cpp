#include "Arduino.h"
#include "Observer.h"
#include "Context.h"
#include "ConcreteStateOn.h"
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkWifi Blynk(_blynkTransport);

char auth[] = "v6IioSNQCWB2lcHt3YZUpFA1YD-hJSgz";
char ssid[] = "SASHA";
char pass[] = "0663616537";

DHT dht(D6, DHT11);

const int timer = 5000;
const int num = 3;
const int arr[num] = {D1, D2, D3};

bool second_sensor = 1;
bool but_state = 0;

unsigned long curr_time = millis();
float t_new = 0, tmp = 1.0;

int Observer::static_number_ = 0;

Context *context = new Context(new ConcreteStateOn, "ConcreteStateOn");
Observer *observer1 = new Observer(*context);

void setup()
{
	Serial.begin(9600);
	Blynk.begin(auth, ssid, pass);
	for (auto i : arr) pinMode(i, OUTPUT);
	for (auto i : arr) digitalWrite(i, LOW);
	pinMode(D5, INPUT);
	digitalWrite(D5, LOW);
	dht.begin();
}

void loop()
{	
	but_state = 0;
	if (millis() - curr_time > timer)
	{
		context->NextState();
		delay(2000);
		context->Monitoring();
		delay(2000);
		context->Check();
		delay(2000);
		if (second_sensor == 1)
		{
			context->Fire();
			delay(2000);
			context->Announce();
		}
		else
			context->Announce();

		curr_time = millis();
	}
}