# Wachsinator

Der **Wachsinator** ist eine Arduino-basierte Steuerung für das Schmelzen und Auftauen von Wachs (z. B. Bienenwachs) mit automatischer Temperaturregelung, Zustandsverwaltung und Sicherheitsabschaltung.  
Das Projekt demonstriert sowohl Hardware-Ansteuerung als auch eine saubere, zustandsbasierte Softwarestruktur.

---

## 🧠 Konzept

Das System arbeitet mit vier klar definierten Zuständen:

| Zustand       | Beschreibung |
|----------------|--------------|
| **BEREIT**     | Grundzustand – wartet auf Benutzereingabe |
| **TAUEN**      | Aktiviert Heizlogik für moderates Erwärmen |
| **SCHMELZEN**  | Höhere Zieltemperatur, kontinuierliches Regelverhalten |
| **BETRIEB**    | Aktiv, solange Prozess läuft oder bis Schalter losgelassen wird |

Die Steuerung erfolgt über physische Schalter (Start, Tauen, Schmelzen, Zeitwahl) und eine Temperaturregelung mit **OneWire-Sensor** (Dallas DS18B20).

---

## ⚙️ Hardwareanforderungen

- Arduino-kompatibles Board (Uno, Nano, Mega)
- **OneWire-Temperatursensor** (z. B. DS18B20)
- Heizrelais (für Phase L und N)
- Signallampen (Betrieb / Bereitschaft)
- Potentiometer für Sollwert-Einstellung
- Taster bzw. Schalter für Betriebsarten

### Pinbelegung (laut Code)

| Komponente | Pin |
|-------------|-----|
| Heizung L | 7 |
| Heizung N | 8 |
| Lampe „Bereit“ | 9 |
| Lampe „Betrieb“ | 10 |
| Start-Schalter | 3 |
| Schalter „Tauen“ | 4 |
| Schalter „Schmelzen“ | 5 |
| Zeitschalter | 6 |
| Temperatur-Sensor | 2 |
| Potentiometer | A0 |

---

## 🧩 Softwarestruktur

Das Projekt ist modular aufgebaut. Jeder `.ino`-Sketch repräsentiert einen Betriebsmodus:

| Datei | Funktion |
|--------|-----------|
| `Wachsinator.ino` | Hauptprogramm, Zustandsverwaltung, Setup |
| `bereitschaft.ino` | Logik für den Bereitschaftsmodus |
| `schmelzen.ino` | Heizlogik für Schmelzprozess |
| `tauen.ino` | Heizlogik für Auftauprozess |

Hilfsfunktionen wie `temperatur()`, `DoControl()` und `heizen()` übernehmen Sensormessung, Regelung und Aktorsteuerung.

---

## 🔬 Technische Details

- Bibliotheken:  
  ```cpp
  #include <OneWire.h>
  #include <DallasTemperature.h>
  ```
- Zustandsmaschine (`enum operatingState`) sorgt für klare Logikübergänge.
- `DEBUG`-Schalter aktivierbar für serielle Ausgabe.
- Entkoppelter Regelkreis mit Soll-/Ist-Wert-Vergleich.

---

## 🚀 Installation & Nutzung

1. Projekt in der **Arduino IDE** öffnen.  
2. Board und Port auswählen.  
3. Ggf. Bibliotheken installieren:
   - **OneWire**
   - **DallasTemperature**
4. Sketch hochladen.
5. Sensor und Aktoren anschließen, Funktion testen.

---

## 💡 Erweiterungsideen

- OLED-Display oder LCD-Statusanzeige  
- EEPROM-Speicherung der letzten Solltemperatur  
- PID-Regler statt einfacher Zweipunktregelung  
- Logging von Temperaturverlauf über UART oder SD-Karte  

---

## 👨‍💻 Über das Projekt

Dieses Projekt zeigt:
- Verständnis für **Embedded-Systeme** und **Hardware-Programmierung**
- saubere **Zustandslogik (State Machine)**
- sichere **Sensor- und Aktoransteuerung**
- strukturierten Code mit klarer Trennung nach Betriebsarten

Ideal als Referenz für Embedded-/IoT-Interesse in Bewerbungen.

---

## 🧾 Lizenz

MIT License – frei verwendbar mit Namensnennung.
