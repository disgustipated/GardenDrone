void checkSensors(){
  StaticJsonDocument<512> mqttDoc;
  JsonObject sMsg = mqttDoc.to<JsonObject>();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    SensorError();
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit and c
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  if (f != 2147483647 || h != 2147483647 || hif != 2147483647){
      sMsg["temp"] = f;
      sMsg["humidity"] = h;
      sMsg["indx"] = hif;
      //NEED TO RESPOND TO POST HERE
    } else {
      sMsg["temp"] = 0;
      sMsg["humidity"] = 0;
      sMsg["indx"] = 0;
      SensorError();
      //NEED TO RESPOND TO POST HERE
    }
}

void checkWaterLevels(){
  StaticJsonDocument<512> mqttDoc;
  JsonObject wlMsg = mqttDoc.to<JsonObject>();

  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(5);
 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distance = duration*0.034/2; //in cm
  distanceIn = distance*0.3937; //in inches

  wlMsg["waterLevel"] = distanceIn;
  //NEED TO RESPOND TO POST HERE
}
