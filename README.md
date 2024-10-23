Anleitung: Software in Visual Studio Code einbinden und auf den ESP laden
Voraussetzungen
Bevor wir anfangen, stellen wir sicher, dass du Visual Studio Code und die PlatformIO-Erweiterung installiert hast. Dies ist nötig, um den Code zu kompilieren und auf deinen ESP hochzuladen. Falls du dies noch nicht eingerichtet hast, folge diesen Schritten:

Visual Studio Code installieren
Lade Visual Studio Code von der offiziellen Webseite herunter und installiere es.

PlatformIO installieren
Öffne Visual Studio Code und gehe auf den Erweiterungsmarkt (Icon mit vier kleinen Quadraten links). Suche nach "PlatformIO" und installiere die Erweiterung.

Repository einbinden
Projekt herunterladen
Lade das Repository entweder als ZIP-Datei herunter oder klone es mit Git in einen Ordner deiner Wahl. Öffne danach den Ordner /firmware in Visual Studio Code.

PlatformIO-Projekt öffnen
Nach dem Öffnen des Ordners sollte Visual Studio Code das platformio.ini-Projekt automatisch erkennen. Wenn nicht, überprüfe, ob die platformio.ini-Datei im Root-Verzeichnis des Projekts vorhanden ist.

WiFi-Einstellungen anpassen
WiFi-Daten eingeben
Öffne die Datei platformio.ini und passe die Werte für -DWIFI_CREDS_SSID und -DWIFI_CREDS_PASSWD an. Trage deinen WLAN-Netzwerknamen und das Passwort ein:

ini
Code kopieren
-DWIFI_CREDS_SSID='"Dein_WLAN_Name"'
-DWIFI_CREDS_PASSWD='"Dein_WLAN_Passwort"'
Netzwerk überprüfen
Stelle sicher, dass dein Computer und der ESP im gleichen Netzwerk sind, damit der ESP mit dem Server kommunizieren kann.

Board und Pin-Layout anpassen
Passendes Board auswählen
In der platformio.ini-Datei findest du die Zeile board = esp12e. Falls du einen anderen ESP-Typ verwendest (z.B. ESP32), ändere die Board-Definition entsprechend. Eine Liste der unterstützten Boards findest du in der PlatformIO-Dokumentation.

Pin-Layout anpassen
Überprüfe die Datei main.cpp und stelle sicher, dass die GPIO-Pins deines Boards korrekt definiert sind. Wenn du spezielle Pins für Sensoren oder Aktoren verwendest, musst du diese entsprechend anpassen.

Optional: Batteriemessung oder PNP-Transistor aktivieren
Wenn du den Batteriestatus messen möchtest, öffne die platformio.ini und entferne das Semikolon (;) vor der Zeile -DUSE_BATTERY:

ini
Code kopieren
-DUSE_BATTERY
Wenn du einen PNP-Transistor (anstelle eines NPN-Transistors wie den BC547b) verwendest, aktiviere die Zeile -DUSE_PNP:

ini
Code kopieren
-DUSE_PNP
Firmware auf den ESP hochladen
ESP mit Computer verbinden
Schließe deinen ESP per USB-Kabel an deinen Computer an.

Upload starten
Klicke im PlatformIO-Fenster links auf das kleine "Flugzeug"-Symbol (Upload) oder führe den Upload über die Kommandozeile aus:

arduino
Code kopieren
pio run --target upload
Kompilieren und Hochladen
PlatformIO wird nun die Firmware kompilieren und auf den ESP hochladen. Stelle sicher, dass keine Fehlermeldungen auftreten und dass das richtige Board und der richtige Port ausgewählt sind.

Erfolg überprüfen
Sobald der Upload abgeschlossen ist, wird die Firmware auf deinem ESP laufen. Über die serielle Konsole von Visual Studio Code kannst du den Status des ESP überwachen. Öffne dazu das "Monitor"-Symbol und beobachte die Ausgabe.
