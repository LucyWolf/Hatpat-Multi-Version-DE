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
Netzwerk sicherstellen
Stelle sicher, dass sich dein Computer und der ESP im gleichen WLAN befinden, damit die Kommunikation funktioniert.
Board und Pin-Layout anpassen
Board auswählen
In der Datei platformio.ini kannst du das Board definieren. Wenn du nicht den ESP8266 (esp12e) verwendest, musst du das Board wie folgt anpassen:

ini
Code kopieren
board = dein_board
Eine Liste der unterstützten Boards findest du in der PlatformIO-Dokumentation.

Pin-Layout anpassen
In der main.cpp kannst du die GPIO-Pins nach Bedarf anpassen, abhängig von deinem Schaltungsaufbau.

Optional: Batteriemessung oder PNP-Transistor aktivieren
Um die Batteriestandsmessung zu aktivieren, entferne das Semikolon (;) vor -DUSE_BATTERY in der platformio.ini:

ini
Code kopieren
-DUSE_BATTERY
Falls du einen PNP-Transistor verwendest (anstelle des NPN wie BC547b), entferne das Semikolon vor -DUSE_PNP:

ini
Code kopieren
-DUSE_PNP
Firmware auf den ESP hochladen
ESP mit Computer verbinden
Verbinde deinen ESP per USB-Kabel mit deinem Computer.

Upload starten
Um die Firmware hochzuladen, klicke auf das "Flugzeug"-Symbol (Upload) in PlatformIO oder benutze folgenden Befehl im Terminal:

bash
Code kopieren
pio run --target upload
Kompilieren und Hochladen
PlatformIO wird die Firmware kompilieren und auf den ESP hochladen. Achte darauf, dass keine Fehler auftreten und dass das richtige Board sowie der Port ausgewählt sind.

Seriellen Monitor öffnen
Nach dem Upload kannst du den Status des ESP über den seriellen Monitor überprüfen. Klicke dafür auf das "Monitor"-Symbol oder nutze den folgenden Befehl:

bash
Code kopieren
pio device monitor
Fehlerbehebung
Fehlermeldungen beim Hochladen:
Stelle sicher, dass das richtige Board in der platformio.ini definiert ist und dass der ESP korrekt verbunden ist.

Verbindungsprobleme:
Prüfe, ob dein WLAN korrekt eingerichtet ist und dass dein Computer und der ESP im gleichen Netzwerk sind.

Mit diesen Schritten solltest du in der Lage sein, die Software erfolgreich in Visual Studio Code einzubinden und auf deinen ESP hochzuladen. Bei weiteren Fragen sieh dir die PlatformIO-Dokumentation an.

markdown
Code kopieren

### So fügst du die Anleitung hinzu:

1. **Erstelle eine Datei namens `README.md` im Hauptverzeichnis deines Repositories.**
2. **Kopiere den obigen Text und füge ihn in die `README.md` ein.**
3. **Speichere die Datei und pushe sie in dein Repository auf GitHub.**

Der Text ist jetzt auf den Punkt gebracht und bietet eine klare Anleitung für das Einbinden der Sof
