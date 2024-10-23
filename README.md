md
Code kopieren
# Anleitung: Software in Visual Studio Code einbinden und auf den ESP laden

## Voraussetzungen

Stelle sicher, dass du die **PlatformIO-Erweiterung** in Visual Studio Code installiert hast, um den Code zu kompilieren und auf deinen ESP hochzuladen. 

## Repository einbinden

1. **Projekt herunterladen**  
   Lade dieses Repository als ZIP-Datei herunter oder klone es mit Git. Öffne anschließend den Ordner `/firmware` in Visual Studio Code.

2. **PlatformIO-Projekt öffnen**  
   Nachdem du den Ordner geöffnet hast, sollte Visual Studio Code die Datei `platformio.ini` automatisch erkennen. Wenn nicht, prüfe, ob die Datei im Hauptverzeichnis vorhanden ist.

## WiFi-Einstellungen anpassen

1. **WiFi-Daten eingeben**  
   Öffne die Datei `platformio.ini` und füge deine WLAN-Daten ein:
   ```ini
   -DWIFI_CREDS_SSID='"Dein_WLAN_Name"'
   -DWIFI_CREDS_PASSWD='"Dein_WLAN_Passwort"'
