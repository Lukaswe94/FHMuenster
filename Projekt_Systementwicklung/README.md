![enter image description here](https://upload.wikimedia.org/wikipedia/commons/thumb/1/1f/Logo_FH_Muenster_cmyk.svg/1024px-Logo_FH_Muenster_cmyk.svg.png)
# Projekt Systementwicklung 2020 Parallelgruppe  01-04

## About
Bei diesem Projekt handelt es sich um einem http-Server der ausschließlich http /1.1   konforme Requests entgegen nimmt und entsprechende Responses zurück gibt. 
Der Server wurde entwickelt für Linux Ubuntu 64bit.

## Unterstützte Formate
- html
- jpg
- png
- gif
- css
- js
- ogg 

## Installation

Voraussetzung für die Installation sind  CMAKE v.3.10.

Kopieren Sie das Repository  mit gültiger Benutzerkennung  
`git clone https://git.fh-muenster.de/pse2020/pse2020-1pg-03/pse1pg03 `

Wechseln Sie in das Verzeichnis pse1pg03  
`cd pse1pg03/`

Kompilieren Sie das Projekt  
`cmake CMakeLists.txt` 

Erstellen Sie eine ausführbare Datei  
`make`

Führen Sie die Datei aus  
`./PSE`

## Bedienung
Haben Sie den Server gestartet, können Sie im Browser unter  
`http://localhost:31337`  
anfragen

oder im Terminal mit dem Befehl  
`nc localhost`

### Verzeichnisse

#### default/
Das Verzeichnis ist unter dem lokalen Host zu erreichen.  
#### extern/ 
Das Verzeichnis ist unter dem externen Host zu erreichen.
#### intern/
Das Verzeichnis ist unter dem internen Host zu erreichen. Intern ist mit einer Basis-Authentifizierung gesichert und nur erreichbar durch: 
  
Benutzername: test  
Passwort: testtest  

Hier lässt sich auch die Dokumentation unseres Servers finden, unter der Adresse `/html/index.html`

#### Sie können den Nutzer ändern indem sie:
ins Verzeichnis intern wechsel  
`cd docroot/intern`

die Datei ändern  
``htpasswd -s -c htpasswd Benutzername``

## Dokumentation
Zu Erstellung der Dokumentation wurde Doxygen genutzt. Diese lässt sich im Ordner des Projektes unter` /html/index.html` finden
Falls sie Kommentare ändern sollten und eine Neue Doku erstellen wollen, können sie dies mit dem Befehl `doxygen` im Terminal machen.
(Dies änder nicht die auf der Website aufrufbare Version. Diese muss seperat im entsprechenden Ordner mit der neuen Version ersetzt werden.)

## Autoren
**Kai Eric Wulfert**  
**Jannick Weelink**  
**Tim Lause**  
## Lizenz

Dieses Produkt unterliegt den Lizenzbestimmungen der FH Münster.

## Danksagung
Danke an Leon V. ,Leon L. und Leon K. für die Unterstützung! 

