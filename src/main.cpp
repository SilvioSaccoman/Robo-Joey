#include <Arduino.h>
#include <WiFi.h>
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// Pin per MAX98357A
#define I2S_BCLK 26
#define I2S_LRC  25
#define I2S_DOUT 22

AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2S *out;

void setup() {
    Serial.begin(115200);
    
    WiFi.begin("Vodafone-E08636455", "Spassocasa2025!");
    while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("\nWiFi Connesso!");

    // Configurazione Output I2S
    out = new AudioOutputI2S();
    out->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    out->setGain(0.1); // Volume iniziale basso (0.0 a 4.0)

    // Configurazione Sorgente Radio (MP3)
    file = new AudioFileSourceICYStream("http://stream.radioparadise.com/mp3_128");
    
    // Creiamo un buffer di 8KB (molto leggero per la RAM interna)
    buff = new AudioFileSourceBuffer(file, 8192);
    
    mp3 = new AudioGeneratorMP3();
    mp3->begin(buff, out);
}

void loop() {
    if (mp3->isRunning()) {
        if (!mp3->loop()) mp3->stop();
    } else {
        Serial.println("MP3 concluso o errore");
        delay(1000);
    }
}