# Anleitung: Software in Visual Studio Code einbinden und auf den ESP laden

## Voraussetzungen

Bevor wir anfangen, stelle sicher, dass du **Visual Studio Code** und die **PlatformIO-Erweiterung** installiert hast. Dies ist notwendig, um den Code zu kompilieren und auf deinen ESP hochzuladen.

Falls du dies noch nicht eingerichtet hast, folge diesen Schritten:

1. **Visual Studio Code installieren**  
   Lade Visual Studio Code von der [offiziellen Webseite](https://code.visualstudio.com/) herunter und installiere es.

2. **PlatformIO installieren**  
   Öffne Visual Studio Code, gehe zu den Erweiterungen (Icon mit vier Quadraten links), suche nach `PlatformIO` und installiere die Erweiterung.

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

Netzwerk sicherstellen
Stelle sicher, dass sich dein Computer und der ESP im gleichen WLAN befinden, damit die Kommunikation funktioniert.
Board und Pin-Layout anpassen
Board auswählen
In der Datei platformio.ini kannst du das Board definieren. Wenn du nicht den ESP8266 (esp12e) verwendest, musst du das Board wie folgt anpassen:
