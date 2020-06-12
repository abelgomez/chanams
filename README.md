# Chana Monitoring System

![Chan Monitoring System](doc/photos/chanams-front.jpg)

## Interior node

### PCB

#### Bill of materials

Qty | Description
---:|------------
  1 | Double-sided PCB (70mm x 90mm)
  1 | NodeMCU v3 (ESP8266)
  1 | 16x2 LCD display HD44780 1602A
  1 | FC-113 I2C interface for 1602A 
  1 | Push button (normally open)
  1 | Red LED
  1 | Yellow LED
  1 | Green LED
  2 | 1 kΩ resistor
  1 | 100 Ω resistor
  1 | Piezo buzzer
  1 | Logic level converter
  1 | 2 position switch (3 pin)
 -- | Pin headers
 -- | Dupont connectors
 -- | Wires

#### PCB Design

Front                                                                                         | Back
:--------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------:
[![Interior PCB Front](doc/design/interior-board-front.png)](doc/design/interior-board-front.pdf)                 | [![Interior PCB Back](doc/design/interior-board-back.png)](doc/design/interior-board-back.pdf)
[![Interior PCB Front](doc/photos/interior-pcb-front-small.jpg)](doc/photos/interior-pcb-front.jpg) | [![Interior PCB Front](doc/photos/interior-pcb-back-small.jpg)](doc/photos/interior-pcb-back.jpg)

### Stand 

#### Bill of materials

Qty | Description
---:|------------
  1 | Methacrylate sheet 3mm thick (270mm x 90mm)
  8 | M3 nylon hex nuts
  8 | M3 x 6mm nylon Phillips head screws
  4 | M3 x 6mm + 6mm nylon screws

#### Stand Design

Description                 | Blueprint / Representation
:--------------------------:|:-----------------------------------------------------------------------------------------:
**Interior body template**    | [![Interior body blueprint](doc/design/interior-body-blueprint.png)](doc/design/interior-body-blueprint.pdf)
**Interior body (side view)** | [![Interior body side](doc/design/interior-body-side.png)](doc/design/interior-body-side.pdf)
**Interior (design view)**    | [![Interior body design](doc/design/interior-body-design.png)](doc/design/interior-body-design.pdf)
**Result**                  | [![Interior](doc/photos/interior-small.jpg)](doc/photos/interior.jpg)

## Exterior node

### PCB

#### Bill of Materials

Qty | Description
---:|------------
  1 | Double-sided PCB (50mm x 70mm)
  1 | 1 NodeMCU v3 (ESP8266)
  1 | 1 DHT22 sensor board
  1 | AP7361C-33ER-13 low dropout regulator
  1 | Push button (normally open)
  1 | 4 AA Battery holder
  1 | Float switch (normally closed, but can be easily changed)
  1 | 100 Ω resistor
  1 | 220 Ω resistor
  1 | 2 position switch (3 pin)
 -- | Pin headers
 -- | Dupont connectors
 -- | Wires

#### PCB Design

Front                                                                                       | Back
:------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------:
[![Exterior PCB Front](doc/design/exterior-board-front.png)](doc/design/exterior-board-front.pdf)                  | [![Exterior PCB Back](doc/design/exterior-board-back.png)](doc/design/exterior-board-back-pdf)
[![Interior PCB Front](doc/photos/exterior-pcb-front-small.jpg)](doc/photos/exterior-pcb-front.jpg) | [![Interior PCB Front](doc/photos/exterior-pcb-back-small.jpg)](doc/photos/exterior-pcb-back.jpg)


### Case

#### Bill of Materials

Qty | Description
---:|------------
  1 | Methacrylate sheet 3mm thick (105mm x 70mm)
  1 | Methacrylate sheet 2mm thick (125mm x 115mm)
  1 | Methacrylate sheet 2mm thick (170mm x 160mm)
  4 | M3 nylon hex nuts
  2 | M3 x 6mm nylon Phillips head screws
  4 | M3 x 10mm + 6mm nylon screws

Additionally, a countersunk magnet can be attached to the top of the case to attach the device to the steel case of the external A/C unit:

Qty | Description
---:|------------
  1 | Countersunk magnet (⌀30mm)
  1 | M3 x 10mm countersunk screw
  2 | M3 steel hex nuts
 -- | Washer(s)


#### Case Design

Description                    | Blueprint / Representation
:-----------------------------:|:--------------------------:
**Exterior main case template**   | [![Exterior body blueprint](doc/design/exterior-body-blueprint.png)](doc/design/exterior-body-blueprint.pdf)
**Exterior lid template**         | [![Exterior cover blueprint](doc/design/exterior-cover-blueprint.png)](doc/design/exterior-cover-blueprint.pdf)
**Exterior skeleton template**    | [![Exterior skeleton blueprint](doc/design/exterior-skeleton-blueprint.png)](doc/design/exterior-skeleton-blueprint.pdf)
**Exterior skeleton (side view)** | [![Exterior skeleton side view](doc/design/exterior-skeleton-side.png)](doc/design/exterior-skeleton-side.pdf)
**Exterior (design view)**        | [![Exterior body desing](doc/design/exterior-body-design.png)](doc/design/exterior-body-design.pdf)
**Result**                     | [![Exterior](doc/photos/exterior-small.jpg)](doc/photos/exterior.jpg)


## Dependencies

Library name                | License      | Repository URL
----------------------------|:------------:|----------------
**ArduinoJson**             | MIT          | https://github.com/bblanchon/ArduinoJson
**Adafruit Unified Sensor** | Apache 2.0   | https://github.com/adafruit/Adafruit_Sensor
**DHT sensor library**      | MIT          | https://github.com/adafruit/DHT-sensor-library
**LiquidCrystal_I2C**       | Unknown      | https://github.com/marcoschwartz/LiquidCrystal_I2C
**PubSubClient**            | MIT          | https://github.com/knolleary/pubsubclient
**TaskScheduler**           | BSD 3-Clause | https://github.com/arkhipenko/TaskScheduler
**uMQTTBroker**             | MIT          | https://github.com/martin-ger/uMQTTBroker
**WiFiManager***            | MIT          | https://github.com/tzapu/WiFiManager

***NOTE:** WiFiManager has been heavily modified and is included in the `lib` folder. The modified code includes excerpts from [ESP8266HTTPUpdateServer](https://github.com/esp8266/Arduino/blob/interior/libraries/ESP8266HTTPUpdateServer/src/ESP8266HTTPUpdateServer-impl.h) library (LGPL).