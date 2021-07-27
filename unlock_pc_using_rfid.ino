/*
 * 
 * All the resources for this project: https://www.hackster.io/anshulpareek
 * Modified by Anshul pareek
 * 
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
#include<Keyboard.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
String readid;
String card1 = "22 CF 40 0D";
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    Serial.println("no card present");
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    Serial.println("reading..");
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  //byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  String readid = content.substring(1);
  if (content.substring(1) == "22 CF 40 0D") //change here the UID of the card/cards that you want to give access
  {
    if(readid==card1)
    { 
      Keyboard.press(KEY_LEFT_GUI);              //Press the left windows key.
      Keyboard.press('l');                       //Press the "l" key.
      Keyboard.releaseAll();                     //Release all keys.
      delay (100);
      Keyboard.press(\r);
      Keyboard.release(\r);
      //Keyboard.press(Enter);                     //Press the Enter key.
      //Keyboard.release(Enter);                   //Release the Enter key.
      delay(100);
      Keyboard.print("9799");                    // Change this value to your Windows PIN/Password.
      Keyboard.releaseAll();
      delay(100);
      Keyboard.press(\r);
      //Keyboard.press(Enter);
      Keyboard.releaseAll();
    }
    else
    {
      return;
    }
//    Serial.println("Authorized access");
//    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 
