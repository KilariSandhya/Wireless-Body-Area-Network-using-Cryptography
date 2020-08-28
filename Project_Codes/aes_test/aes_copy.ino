#include "AESLib.h"
#include<string.h>
#include <Wire.h>
#include "Protocentral_MAX30205.h"
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000

AESLib aesLib;
MAX30205 tempSensor;

PulseOximeter pox;
uint32_t tsLastReport = 0;

int address_temp = 72;
int address_pulse = 87; 

char cleartext[256];
char ciphertext[512];
String temp_value;
String pulse_value;
String oxygen_value;
String text;

// AES Encryption Key
byte aes_key[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

void onBeatDetected()
{
  Serial.println("Beat!");
}

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
  Wire.begin();
  tempSensor.begin();

  Serial.print("Initializing pulse oximeter...");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  Wire.beginTransmission(address_temp);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(address_temp, 1);

  while (Wire.available() == 0);

  int temp = tempSensor.getTemperature(); // read temperature for every 100ms
  int fahrenheit = temp * 9 / 5 + 32;
  String temp1 = "Temp:";
  String temp2 = "'F ";
  temp_value = temp1 + fahrenheit + temp2;
  int count1=0;
  if (++count1 == 1275) {
  Serial.println(temp_value);
  count1 = 0;
  }

  Wire.beginTransmission(address_pulse);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(address_pulse, 1);

  while (Wire.available() == 0);

  pox.update();
    String pulse1 = "Pulse:";
    String pulse2 = "BPM ";
    int pulse_rate = pox.getHeartRate();
    String oxi1 = "SPO2:";
    String oxi2 = "%";
    int oxi_rate = pox.getSpO2();
    pulse_value = pulse1 + pulse_rate + pulse2;
    oxygen_value = oxi1 + oxi_rate + oxi2;
    Serial.println(pulse_value);

  text = temp_value + pulse_value + oxygen_value;
  int str_len = text.length() + 1;
  text.toCharArray(cleartext, str_len);

  // Encrypt
  byte enc_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  String encrypted = encrypt(cleartext, enc_iv);
  Serial.println(encrypted);

  // Decrypt
  byte dec_iv[N_BLOCK] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  String decrypted = decrypt(ciphertext, dec_iv);

  delay(500);
}
