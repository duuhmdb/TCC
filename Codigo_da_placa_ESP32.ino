#include "WiFi.h"
#include "HTTPClient.h"
#define RX 16
#define TX 17
const char* ssid = "AndroidAP62A9"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO
const char* pass = "bspf9177";//VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO
String server = "http://uniptccedrenew-001-site1.etempurl.com";
String host = "uniptccedrenew-001-site1.etempurl.com";
String completeData = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RX, TX);

  delay(2000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, pass); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop() {
   String dataToSent = Serial2.readString();
   Serial.print("Received data: \n");
   Serial.print(dataToSent);
   if(dataToSent.length() > 0){
        if(dataToSent == "<")
            Post(completeData);
        else if(dataToSent == ">")
            completeData = "";
        else
          completeData.concat(dataToSent);
   }
}

void Post(String data){
      if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
         HTTPClient http;   
         http.begin(server + "/trackings");  //Specify destination for HTTP request
         http.addHeader("Content-Type", "application/json");             //Specify content-type header
         http.addHeader("Host", host); 
         String postData = "{\"data\": \""+data+"\"}"; 
         int httpResponseCode = http.POST(postData); 
         if(httpResponseCode <= 0){
            Post(data);
         }
         else
          http.end();
      }
      else{
          Serial.println("Error in WiFi connection");   
      }
}
