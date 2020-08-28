#include<stdio.h>
#include<string.h>

void setup() {
  Serial.begin(9600);
  char msg[100] = {"ATTACK IS TODAY"};
  char key[100] = {"HELLO"};
  int msgLen = strlen(msg), keyLen = strlen(key), i, j;
  char temp[msgLen];
  char newKey[msgLen], encryptedMsg[msgLen], decryptedMsg[msgLen];

  for (i = 0; i < msgLen; i++) temp[i] = msg[i];
  Serial.print("");
  
  for (i = 0, j = 0; i < msgLen; ++i, ++j) {
    if (j == keyLen)
      j = 0;

    newKey[i] = key[j];
  }
  newKey[i] = '\0';
  Serial.print("");

  //encryption
  for (i = 0; i < msgLen; ++i)
    if(msg[i] == ' ') encryptedMsg[i] = '0';
    else encryptedMsg[i] = ((msg[i] + newKey[i]) % 26) + 'A';

  encryptedMsg[i] = '\0';
  Serial.println(encryptedMsg);

  //decryption
  for (i = 0, j = 0; i < msgLen; ++i, ++j) {
    if (j == keyLen)
      j = 0;

    newKey[i] = key[j];
  }
  newKey[i] = '\0';
  Serial.print("");
  
  for (i = 0; i < msgLen; ++i){
    if(encryptedMsg[i] == '0') decryptedMsg[i]=' ';
    else decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';
  }

  decryptedMsg[i] = '\0';
  Serial.print("");
  Serial.println(decryptedMsg);

}

void loop() {

}
