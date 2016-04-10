#include <SoftwareSerial.h>
SoftwareSerial SIM900(7,8);

void setup() {
Serial.begin(9600); 
SIM900power();  
}

void loop() {

 Serial.println("SubmitHttpRequest - started" );
  SubmitHttpRequest();
  Serial.println("SubmitHttpRequest - finished" );
  delay(10000);
}
//AT+HTTPINIT
//AT+HTTPPARA="CID",1
//AT+HTTPPARA="URL","http://url.com/endPoint"
//AT+HTTPPARA="CONTENT","application/json"
//AT+HTTPDATA=40,10000
//
//{"location_id": 238, "fill_percent": 90}
//
//AT+HTTPACTION=1
//AT+HTTPREAD
//AT+HTTPTERM

void SubmitHttpRequest()
{
 
  SIM900.println("AT+CSQ"); // Signal quality check

  delay(100);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);
 
  ShowSerialData();
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, Access point name string
  delay(4000);
 
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
  ShowSerialData();
 
  SIM900.println("AT+HTTPPARA=\"URL\",\"sim900test.net46.net/getstate.php?color=All\"");// setting the httppara, the second parameter is the website you want to access
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!SIM900.available());
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
  ShowSerialData();
 
  SIM900.println("");
  delay(100);
}


 void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(9, LOW);
  delay(5000);
}


 
void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(char (SIM900.read()));
}

