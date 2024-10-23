# Patstrap

<p>
    <a href="#" alt="size"><img alt="Repository size" src="https://img.shields.io/github/repo-size/danielfvm/Patstrap?color=39d45f"></a>
    <a href="//github.com/danielfvm/Patstrap/commits/master" alt="commit"><img alt="Last Commit" src="https://img.shields.io/github/last-commit/danielfvm/Patstrap?color=39d45f"></a>
    <a href="//github.com/danielfvm/Patstrap/commits/master/" alt="Commits"><img alt="GitHub commit activity (branch)" src="https://img.shields.io/github/commit-activity/m/danielfvm/Patstrap/master"></a>
    <a href="//github.com/danielfvm/Patstrap?tab=GPL-3.0-1-ov-file#readme" alt="licence"><img alt="GitHub License" src="https://img.shields.io/github/license/danielfvm/Patstrap"></a>
    <a href="#" alt="stars"><img alt="GitHub Repo stars" src="https://img.shields.io/github/stars/danielfvm/Patstrap"></a>
</p>


Ein Open-Hardware- und Softwareprojekt, das versucht, haptisches Feedback durch Kopfstreicheln (Head Pat) an den Spieler in VR zu implementieren. Dieses Projekt konzentriert sich hauptsächlich auf die OSC-Unterstützung von VRChat. Das Projekt besteht aus einem Hardwareteil, dem 'Headpat-Strap' oder einfach 'Patstrap', einem Server, der auf dem PC läuft, und den erforderlichen Änderungen an einem VRChat-Avatar, um die Kommunikation über OSC zu unterstützen. Bitte beachte, dass dies nur ein Hobbyprojekt ist, aber fühle dich frei, zu experimentieren, den Code zu bearbeiten oder die Hardware nach deinen Wünschen anzupassen.

>   [!WARNING]
>   Dieses Projekt befindet sich in der Entwicklungsphase. Bitte beachte, dass die Komponenten des Projekts häufigen Änderungen unterliegen.

### Elektronik
Es wurde für einen ESP8266 (WEMOS D1 MINI) und für einen XIAO ESP32-C3 angepasst.
Für das haptische Feedback wurden zwei Vibrating Mini Motoren verwendet, um ein räumliches Feedback am Kopf zu erzeugen.
__________________________________________________
###    Das ist der Bauplan für den ESP D1 Mini.

## Hardware
### Teile
Um dieses Projekt zu realisieren, benötigst du:
- [ESP8266 WEMOS D1 Mini V4.0.0](https://de.aliexpress.com/item/1005006246661815.html) If you use a different ESP, you may need to change the pins in the code.
- 2x [150KΩ Resistors](https://de.aliexpress.com/item/1005001627995396.html)
- 2x [Transistors](https://de.aliexpress.com/item/1005003450640801.html)  (I used BC547)
- 2x [Vibrating motors](https://aliexpress.com/item/1005001446097852.html)

Und optional, wenn du einen Akku verwendest:
- 1x [180KΩ Resistors](https://de.aliexpress.com/item/1005001627995396.html)
- 2x [Diodes 1N5817](https://de.aliexpress.com/item/1005002620053985.html)
- [Battery](https://www.amazon.com/dp/B0B7N2T1TD?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [Battery charger](https://de.aliexpress.com/item/1005006274938832.html)
- [On/Off switch](https://aliexpress.com/item/1005003938856402.html)



### Hier ist der Schaltplan.
![378893354-243acea6-37cc-4932-948d-9416ec73516d](https://github.com/user-attachments/assets/62f9f993-bea8-4709-9126-896830231749)

### Battery
Für das Laden und die Stromversorgung des Geräts wird ein TP4056 verwendet. Um den Batteriestand zu messen, füge einen 180 kOhm Widerstand an Pin A0 hinzu und aktiviere Battery sense im Skript. Siehe das Schaltbild, um zu erfahren, wie es angeschlossen wird. Dafür werden auch zwei 1N5817-Dioden verwendet, um sicherzustellen, dass das Gerät auch während der Nutzung geladen werden kann.

>    [!WARNING]
>    Das kleine Lademodul wird von den neuen Ladegeräten unterstützt.


![image](https://github.com/user-attachments/assets/fe0c0cc5-658e-45f6-974f-cefb58357bf8)

____________________________________________________
###    Das ist der Bauplan für den Seeed Xiao ESP32C3.

## Hardware
### Teile
Um dieses Projekt zu realisieren, benötigst du:
- [ESP8266 WEMOS D1 Mini V4.0.0](https://de.aliexpress.com/item/1005006246661815.html) If you use a different ESP, you may need to change the pins in the code.
- 2x [150KΩ Resistors](https://de.aliexpress.com/item/1005001627995396.html)
- 2x [Transistors](https://de.aliexpress.com/item/1005003450640801.html)  (I used BC547)
- 2x [Vibrating motors](https://aliexpress.com/item/1005001446097852.html)

Und optional, wenn du einen Akku verwendest:
- 2x [180KΩ Resistors](https://de.aliexpress.com/item/1005001627995396.html)
- 1x [Diodes 1N5817](https://de.aliexpress.com/item/1005002620053985.html)
- [Battery](https://www.amazon.com/dp/B0B7N2T1TD?psc=1&ref=ppx_yo2ov_dt_b_product_details)
- [On/Off switch](https://aliexpress.com/item/1005003938856402.html)

![Seeed Xiao ESP32C3](https://github.com/user-attachments/assets/f2bc150c-dc54-4d7a-97c6-aec47bcf75b4)

Achte darauf, dass in der main.cpp auch das Board ausgewählt ist.
```main.cpp
// Select the board you are using
#define BOARD BOARD_WEMOSD1MINI // Change this to BOARD_XIAO_ESP32C3 or BOARD_WEMOSD1MINI
```
_________________________________________________________________



### Gehäuse
Das 3D-Modell und die STEP-Datei des Gehäuses, die Platz für die Motor Discs und den ESP8266 (WEMOS D1 MINI) sowie den XIAO ESP32-C3 bieten, sind im Verzeichnis /model verfügbar und können 3D-gedruckt werden. Alternativ kannst du ein normales Kopfband verwenden und die Motor Discs sowie den ESP einfach mit Heißkleber auf einem Kopfband befestigen.

### PCB
Optional kannst du eine Leiterplatte (PCB) für den Patstrap bestellen. Die benötigten Gerber-Dateien für die Bestellung findest du hier. Vielen Dank an The-Prophet für die Erstellung der PCB.

>   [!WARNING]
>   Die PCB wurde bisher noch nicht getestet und befindet sich noch in der Entwicklungsphase!

## Software
### Firmware
Um die Firmware auf den ESP hochzuladen, verwenden wir Visual Studio Code und PlatformIO. Bitte beziehe dich auf die SlimeVR-Dokumentation als Referenz zur Installation der IDE und der Erweiterung. Nach der Installation kannst du dieses Repository herunterladen und den Ordner /firmware in Visual Studio Code öffnen.


Öffne die platformio.ini und ändere die WLAN-Daten:

-DWIFI_CREDS_SSID='"WLAN Name"'
-DWIFI_CREDS_PASSWD='"WLAN Passwort"'
Entferne das ;, um das Board zu wechseln oder andere Module ein- oder auszuschalten. 
Die Akkuangabe ist bereits aktiv, wenn du das Skript das erste Mal öffnest, und der ESP D1 Mini ist ebenfalls aktiv.

Ihre Konfigurationsdatei sollte ungefähr so aussehen:
```ini
[env]
monitor_speed = 115200
monitor_echo = yes
monitor_filters = colorize
framework = arduino

build_unflags = -Os
build_flags = -O2
; Set your WiFi name and password here - Make sure it's within the same Network as the server software!
  -DWIFI_CREDS_SSID='"WLAN Name"'
  -DWIFI_CREDS_PASSWD='"WLAN Passwort"'

; Uncomment below ONLY if you used a PNP transistor, if you followed the guide you probably want to leave it commented. => inverts the output of the haptic motors
;  -DUSE_PNP

; Uncomment below if you want to measure battery
  -DUSE_BATTERY

; Define the board used
; Uncomment one of the following lines based on the board you're using

; For Seeed Xiao ESP32C3

;[env:seeed_xiao_esp32c3]
;platform = espressif32
;board = seeed_xiao_esp32c3
;framework = arduino
;build_flags =
;  ${env.build_flags}
;  -DBOARD_XIAO_ESP32C3
;  -DESP32C3

; For Wemos D1 Mini

[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino
upload_speed = 921600
monitor_speed = 115200
```
Nach Ihren Änderungen können Sie Ihren ESP anschließen, auf "Build" (✓) klicken und es flashen (→). 
Die Schaltflächen finden Sie in Visual Studio Code unten auf der linken Seite.

(bild hinzufügen)

In der main.cpp müsst ihr das Board auswählen, das ihr verwendet. Standardmäßig ist bereits das ESP D1 Mini ausgewählt.

(bild einfügen)

### Server
Unter "Releases" finden Sie die Binärdateien, um den Server auf Ihrem Computer auszuführen. Der Server fungiert als Mittelsmann, der die Kommunikation zwischen dem Gerät und VRChat ermöglicht. Der Server unterstützt sowohl Windows als auch Linux. Er öffnet ein Fenster, in dem der aktuelle Verbindungsstatus angezeigt wird. Wenn das Flashen der Hardware erfolgreich war und das Gerät läuft, sollten Sie den Text connected sehen. Sie können die Verbindung auch überprüfen, indem Sie die ESP-LED beobachten.

*   Schnelles Blinken (~10 Mal pro Sekunde): Nicht mit WLAN verbunden.
*   Langsame Blinkrate (~1 Mal pro Sekunde): Mit WLAN verbunden, aber nicht mit dem Server verbunden.
*   Dauerhaftes Licht: Verbunden.
*   Kein Licht: Vielleicht nicht eingeschaltet?

Wenn die Verbindung erfolgreich war, sollte Patstrap connection grün werden. Außerdem könnt ihr die Hardware testen, indem ihr auf Pat left und Pat right klickt.

(bild)

#### Port
Du kannst den OSC-Port sowie den Port zum ESP ändern, indem du ein Startargument hinzufügst.

Um den OSC-Port zu ändern, starte den Server über die Eingabeaufforderung und gib patstrap.exe --osc-port 1234 ein. 
Um den ESP-Port zu ändern, gib stattdessen patstrap.exe --esp-port 1234 ein, aber stelle sicher, dass du auch den Port in der platformio.ini-Datei änderst.

Wenn du den Port nicht jedes Mal manuell festlegen möchtest, wenn du den Server startest, kannst du eine .bat-Datei mit folgendem Inhalt erstellen:
```
@echo off
patstrap.exe --osc-port 1234
```
>   [!WICHTIG] 
>   Stelle sicher, dass sich die .bat-Datei im gleichen Ordner wie die .exe-Datei befindet. Alternativ kannst du den vollständigen Pfad zur .exe in der .bat-Datei hinzufügen.

Wenn du [VRCOSC](https://github.com/VolcanicArts/VRCOSC) verwendest, kannst du die .exe zum Autostart hinzufügen und (falls erforderlich) die Startargumente dort hinzufügen.

### VRChat
#### Avatar - Unity
Damit der Patstrap funktioniert, musst du [OSC-Unterstützung in VRChat aktivieren](https://docs.slimevr.dev/server/osc-information.html) und dein Avatar-Modell bearbeiten, um die erforderlichen Collider für die Erkennung von Kopfstreicheleinheiten einzufügen. Dafür benötigst du ein funktionierendes Avatar-Setup in Unity.
