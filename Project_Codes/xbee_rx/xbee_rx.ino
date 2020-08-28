#include "AESLib.h"
#include<string.h>

AESLib aesLib;

char ciphertext[512];
String cipher;

// AES Encryption Key
byte aes_key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

void setup() {
  Serial.begin(9600);

}

void loop() {
  char ciphertext1[512] = {"RECEIVED CIPHER TEXT"};
  aes_decryption(ciphertext1);
delay(500);
}

void aes_decryption(char * ciphertext) {
  byte dec_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  String decrypted = decrypt(ciphertext, dec_iv);
  Serial.print("Cleartext: ");
  Serial.println(decrypted);
  Serial.println();
}

String decrypt(char * msg, byte iv[]) {
  int msgLen = strlen(msg);
  char decrypted[msgLen]; // half may be enough
  aesLib.decrypt64(msg, msgLen, decrypted, aes_key, sizeof(aes_key), iv);
  return String(decrypted);
}
