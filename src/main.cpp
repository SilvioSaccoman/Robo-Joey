#include "Arduino.h"
#include "Audio.h"
#include "WiFi.h"

// Definizione Pin I2S per MAX98357A
#define I2S_LRC       25
#define I2S_BCLK      26
#define I2S_DOUT      22

// Sostituisci con i tuoi dati
const char* ssid = "Vodafone-E08636455";
const char* password = "Spassocasa2025!";

Audio audio; // 'true' uses internal RAM for buffer

void setup() {
    // Inizializza la seriale a 115200 baud
    Serial.begin(115200);
    delay(1000); 
    Serial.println("\n--- Avvio ESP32 Audio Player ---");

    // Tentativo di connessione WiFi
    Serial.printf("Tentativo di connessione a: %s\n", ssid);
    WiFi.begin(ssid, password);

    // Loop di attesa con feedback visivo
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print("."); 
    }

    // Feedback di avvenuta connessione
    Serial.println("\n[OK] WiFi Connesso!");
    Serial.print("[INFO] Indirizzo IP assegnato: ");
    Serial.println(WiFi.localIP());
    Serial.print("[INFO] Potenza segnale (RSSI): ");
    Serial.println(WiFi.RSSI());
    Serial.println("---------------------------------");

    // Configurazione Audio
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(12); // Volume medio (0-21)

    // Avvio streaming
    Serial.println("[AUDIO] Avvio streaming radio...");
    audio.connecttohost("http://stream.radioparadise.com/mp3_128");
}

void loop() {
    // Importante: questo deve girare costantemente per alimentare il buffer audio
    audio.loop();

    // Feedback opzionale: se la connessione cade, avvisami
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 10000) { // Controlla ogni 10 secondi
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("[ERRORE] WiFi disconnesso!");
        }
        lastCheck = millis();
    }
}

// Funzione di callback opzionale (la libreria la chiama automaticamente se presente)
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}