// --------------------------------------
// Advanced i2c_scanner
// Based on original i2c_scanner available on http://arduino.cc
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
// Version 7, May 27, 2017.
//    Added interactive menu
//    Improved interface
//    Added list of devices
//    Added I2C direct conection
//    Translated to PT-BR by Jhonatan Caldeira
//
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Wire.h>

int myAddress[127];
byte error, address;
int nDevices;
bool echo = false;
void showMenu() {
  Serial.println(F("\nI2C Scanner v.7"));
  Serial.println(F(" s - Escanear por dispositivos I2C"));
  Serial.println(F(" l - Listar todos dispositivos encotrados no último escaneamento"));
  Serial.println(F(" o - Puxar dados de um dispositivo (limitado a conexão entre Arduinos)"));
  Serial.println(F(" e - Habilitar ou desabilitar função echo"));
  Serial.println(F(" h - Mostra esse menu novamento\n"));
}
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  showMenu();
}
void loop()
{
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (echo){
      Serial.print("[I2CS] Recebido: ");Serial.println(c);
    }
    if(c == 'e'){
      echo = !echo;
      Serial.println(echo ? "[I2CS] Echo habilitado" : "[I2CS] Echo desabilitado");
    }
    else if (c == 'h') {
      showMenu();
    } else if (c == 'o') {
      if(nDevices <= 0){
        Serial.println(F("\n[IC2S] Primeiro você deve realizar um escaneamento."));
      }else{
      Serial.println(F("\n[IC2S] Digite com qual dispositivo deseja conectar: "));
      for (int i =  0; i < nDevices; i++ ) {
        Serial.print(F("[IC2S] ")); Serial.print(i + 1); Serial.print(F(") ")); Serial.print(F("0x")); if (myAddress[i] < 16)Serial.print(F("0")); Serial.println(myAddress[i], HEX);
      }
      while (Serial.available() < 1);
      int val = Serial.parseInt();
      Serial.print(F("[IC2S] Abrindo conexão no endereço")); Serial.print(F(" 0x")); if (myAddress[val - 1] < 16)Serial.print(F("0")); Serial.println(myAddress[val - 1], HEX);
      delay(100);
      if (myAddress[val - 1] != 0) {
        Wire.requestFrom(myAddress[val - 1], 6); // request 6 bytes from slave device #8
        Serial.print(F("[IC2S] Recebido de 0x")); if (myAddress[val - 1] < 16)Serial.print(F("0")); Serial.print(myAddress[val - 1], HEX); Serial.print(F(": "));
        while (Wire.available()) {
          char c = Wire.read();
          Serial.print(c);
        } Serial.println(F("\n"));
      } else {
        Serial.println(F("Invalido\n"));
      }
    }} else if (c == 'l') {
      if (nDevices <= 0) {
        Serial.println(F("\n[I2CS] Nenhum dispositivo para exibir\n"));
      } else {
        Serial.println(F("\n[IC2S] Dispositivos encontrados no último escaneamento"));
        for (int i =  0; i < nDevices; i++ ) {
          Serial.print(F("[IC2S] ")); Serial.print(i + 1); Serial.print(F(") ")); Serial.print(F("0x")); if (myAddress[i] < 16)Serial.print(F("0")); Serial.println(myAddress[i], HEX);
        } Serial.println(F("[I2CS] Fim\n"));
      }

    } else if (c == 's') {
      Serial.println(F("[I2CS] Escaneando..."));
      nDevices = 0;
      for (address = 1; address < 127; address++ )
      {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
          Serial.print(F("[I2CS] Dispositivo I2C encontrado no endereço 0x"));
          if (address < 16)Serial.print(F("0"));
          Serial.print(address, HEX);
          Serial.println(F("!"));
          myAddress[nDevices] = address;
          nDevices++;
        }
        else if (error == 4)
        {
          Serial.print(F("[I2CS] Erro desconhecido encontrado no endereço 0x"));
          if (address < 16)Serial.print(F("0"));
          Serial.println(address, HEX);
        }
      }
      if (nDevices == 0) {
        Serial.println(F("[I2CS] Nenhum dispositivo detectado\n"));
      } else {
        Serial.println(F("[I2CS] Escaneamento encerrado\n"));
      }
    }
  }
}
