#include "WiFiManager.h"

const char* ssid_global = SSID;
const char* pass_global = PASSWORD_WIFI;

// WiFiUDP instance for receiving UDP packets
WiFiUDP udp;
const unsigned int localPort = 4210;

// Static IP configuration 
IPAddress local_IP(192, 168, 1, 150); 
IPAddress gateway(192, 168, 1, 1);    
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);

void initWiFi() {
    ESP_LOGI("WIFI", "Static IP: 192.168.1.150");
    
    // Set WiFi to station mode 
    WiFi.mode(WIFI_STA);

    // Configure static IP
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
            ESP_LOGE("WIFI", "Error in configuring static IP!");
    }

    // Disconnect from any previous WiFi connection
    WiFi.disconnect(); 
    delay(100);

    ESP_LOGI("WIFI", "Trying to connect to: %s\n", ssid_global);
    WiFi.begin(ssid_global, pass_global);
}

bool isWiFiConnected() {
    return (WiFi.status() == WL_CONNECTED);
}

void udpReceiverTask(void *pvParameters) {
    udp.begin(localPort);
    ControlPacket incomingPacket;

    while (1) {
        int packetSize = udp.parsePacket();
        
        if (packetSize == sizeof(ControlPacket)) {
            // Read the incoming packet into our ControlPacket struct
            udp.read((char*)&incomingPacket, sizeof(ControlPacket));
            ESP_LOGI("UDP", "Packet received: Cmd=%d, Timestamp=%d", incomingPacket.command, incomingPacket.time_stamp);
            
            // Pass the received packet to the input processing function
            processInput(incomingPacket);
        }
        
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
