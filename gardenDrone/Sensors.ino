void checkSensors(){
  StaticJsonDocument<512> mqttDoc;
  JsonObject sMsg = mqttDoc.to<JsonObject>();

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
