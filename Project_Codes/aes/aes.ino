#include "AESLib.h"
#include<string.h>

AESLib aesLib;

String string1 = String("Name:***** ");
String string2 = String("Age:** ");
String string7 = String("PH:8095979323 ");
String string3 = String("Temp: ");
String string4 = String("'C Pulse: ");
String string5 = String("Oxirate: ");
String string6 = String("%");
int value1 = 31; //temperature value
float value2 = 72.3; // pulse rate
int value3 = 93; // oxygen percentage

String cleartextt = "string1+string2+string7+string3+value1+string4+value2+string5+value3+string6
char cleartext[256];
char ciphertext[512]; 
int str_len = cleartextt.length() + 1; 


// AES Encryption Key
byte aes_key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

String encrypt(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char encrypted[2 * msgLen];
  aesLib.encrypt64(msg, msgLen, encrypted, aes_key, sizeof(aes_key), iv);
  return String(encrypted);
}

String decrypt(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char decrypted[msgLen]; // half may be enough
  aesLib.decrypt64(msg, msgLen, decrypted, aes_key, sizeof(aes_key), iv);
  return String(decrypted);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  cleartextt.toCharArray(cleartext, str_len);
  
  // Encrypt
  byte enc_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  String encrypted = encrypt(cleartext, enc_iv);
  sprintf(ciphertext, "%s", encrypted.c_str());
  Serial.print("Ciphertext: ");
  Serial.println(encrypted);

  // Decrypt
  byte dec_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  String decrypted = decrypt(ciphertext, dec_iv);
  Serial.print("Cleartext: ");
  Serial.println(decrypted);
  Serial.println();
 
  delay(500);
}
