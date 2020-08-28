#include "AESLib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

AESLib aesLib;

String string0 = String("Name:*** ");
String string1 = String("Age:** ");
String string2 = String("Gender:* ");

String string3 = String("Temp:87'F ");
String string4 = String("Pulse:85bpm ");
String string5 = String("Oxirate:96% ");

String cleartextt0 = string0+string1+string2+string3+string4+string5;
char cleartext0[128];
char ciphertext0[128];
int str_len0 = cleartextt0.length() + 1; 

// AES Encryption Key
byte aes_key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
byte enc_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 
byte dec_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void setup() {
  Serial.begin(9600);
  
void loop() {
  cleartextt0.toCharArray(cleartext0, str_len0);
  String encrypted0;
  encrypted0 = encrypt(cleartext0, enc_iv);
  Serial.println(encrypted0);
  delay(15000);
}


String encrypt(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char encrypted[2 * msgLen];
  aesLib.encrypt64(msg, msgLen, encrypted, aes_key, sizeof(aes_key), iv);
  return String(encrypted);
}


void toCharacterArray(String stringValue,char *charArray)
{
  int i=0,k=0;
  while(stringValue[i]!=0)
  {
    charArray[k++] = stringValue[i];
    i += 1;
  }
}

String decrypt(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char decrypted[msgLen]; // half may be enough
  aesLib.decrypt64(msg, msgLen, decrypted, aes_key, sizeof(aes_key), iv);
  return String(decrypted);
}
