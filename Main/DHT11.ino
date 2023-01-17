#include <dht11.h>

dht11 DHT11;

float* readDHT11()
{
  int chk = DHT11.read(DHT11PIN);
  float humidity = (float)DHT11.humidity;
  float temperature = (float)DHT11.temperature;
  float results[2] = {humidity, temperature};
  return results;
}
