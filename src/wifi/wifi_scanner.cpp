#include "wifi_scanner.h"
#include <Arduino.h>
#include <WiFi.h>


// Turn security code into human-readable format
String getSecurityType(wifi_auth_mode_t securityCode) {
    switch (securityCode) {
        case WIFI_AUTH_OPEN:
            return "OPEN";
        case WIFI_AUTH_WEP:
            return "WEP";
        case WIFI_AUTH_WPA_PSK:
            return "WPA";
        case WIFI_AUTH_WPA2_PSK:
            return "WPA2";
        case WIFI_AUTH_WPA_WPA2_PSK:
            return "WPA/WPA2";
        case WIFI_AUTH_WPA3_PSK:
            return "WPA3";
        case WIFI_AUTH_WPA2_WPA3_PSK:
            return "WPA2/WPA3";
        default:
            return "UNKNOWN";
    }
}

// Read and print one network using index
void printOneNetwork(int networkIndex) {
    String networkName = WiFi.SSID(networkIndex);

    if (networkName == "") {
        networkName = "(hidden)";
    }

    int signalStrength = WiFi.RSSI(networkIndex);

    wifi_auth_mode_t securityCode = WiFi.encryptionType(networkIndex);
    
    String securityType = getSecurityType(securityCode);

    Serial.print("  Name: ");
    Serial.print(networkName);
    Serial.print("   Signal: ");
    Serial.print(signalStrength);
    Serial.print(" dBm");
    Serial.print("   Security: ");
    Serial.println(securityType);
}

// Start WiFi radio
void startWiFiScanner() {
    WiFi.mode(WIFI_STA);  // Station mode to scan
    WiFi.disconnect();  // This prevents connecting to networks
    delay(100);
}

// Do one scan and print each network found
void scanForNetworks() {
    Serial.println("Scanning for networks...");

    int networksFound = WiFi.scanNetworks();

    if (networksFound == 0) {
        Serial.println("No networks found.");
        Serial.println("");
        return;
    }

    Serial.print("Found ");
    Serial.print(networksFound);
    Serial.println(" networks:");

    for (int i = 0; i < networksFound; i = i + 1) {
        printOneNetwork(i);
    }

    Serial.println("");
    WiFi.scanDelete();   // Free the memory the scan used
}