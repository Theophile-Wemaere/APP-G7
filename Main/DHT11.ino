#include <dht11.h>

dht11 DHT11;

float * readDHT11()
{
  int chk = DHT11.read(DHT11PIN);
  float humidity = (float)DHT11.humidity;
  float temperature = (float)DHT11.temperature;

  
  static float results[2];
  results[0] = humidity;
  results[1] = temperature;
  return results;
}
