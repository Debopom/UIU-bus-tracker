//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "cn-project-a8c23-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "hwasi1e5X4OlC4SU5CMIzeqeivfMqdz2lW5v0Mtc"
#define WIFI_SSID "Joy Guru"
#define WIFI_PASSWORD "ohmygawd"


void setup() {
 
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

float longitude;
float latitude;
void loop() {
   int sensorValue = analogRead(A0);
   Serial.println(sensorValue);
   latitude=sensorValue;
   longitude= 90.4125;
   Serial.println(latitude);
   Serial.println(longitude);
  
 
  Firebase.setFloat("GPS/f_latitude", latitude);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // update value
  Firebase.setFloat("GPS/f_longitude", longitude);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // get value 
  Serial.print("lat ");
  Serial.println(Firebase.getFloat("GPS/f_latitude"));
  Serial.println(Firebase.getFloat("GPS/f_longitude"));
  delay(1000);

}
