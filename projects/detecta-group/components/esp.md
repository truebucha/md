
# ESP

***

## Docs

[docs](https://arduino-esp8266.readthedocs.io/en/latest/)

[boot info](https://github.com/esp8266/esp8266-wiki/wiki/Boot-Process#esp-boot-modes)

***

### Circuit to boot up

GPIO0 - pulled high with a 10k resistor and a push button to ground

GPIO2 - pulled high with a 10k resistor

EN - pulled high with a 10k resistor

RST - using a push button to ground

GPIO15 - ground with a 10k resistor

USB/TTL ground - to breadboard negative

GND - to breadboard negative

VCC - to 3.35v provided by a LM371 based circuit (up to 1A)

TX - to USB/TTL RX

RX - to USB/TTL TX

### Pinout

### Esp12-e

![Esp12-e](r-esp/esp12e-pinout.png)

#### Node MCU

![Node MCU pinout](r-esp/nodemcu-pinout.png)

#### D1 mini

![D1 mini pinout](r-esp/wemos-d1-mini-pinout.png)

### Wiring up ESP12

#### First wiring
[wiring #1](http://neilkolban.com/tech/wiring-up-esp8266s/)

![circuit](r-esp/2015-07-04-1.png)

#### Second
![circuit](r-esp/nodeMcuEsp12.png)

#### Third
[link](https://forum.arduino.cc/index.php?topic=444454.0)

![circuit](r-esp/ESP_improved_stability.png)


#### Fourth
![circuit](r-esp/ESP12_Arduino.jpg)

#### Fifth
![circuit](r-esp/ESP12_circuit.jpg)

#### Sixth
![circuit](r-esp/adafruit_products_schem.png)

#### Seventh esp32
![circuit](r-esp/ai-thinker.png)

#### Eighth Node MCU 1.0
![circuit](r-esp/node_mcu_v1.0.png)
[pdf](r-esp/node_mcu_v1.0.pdf)

#### Schematic adafruit
[link](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/downloads)


***
### Power 

![power-table](r-esp/esp8266-PowerConsumption.jpg)

### Ota

[ota](http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html)

***

[Esp Http Updates]( http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html#http-server)

[Markdown](https://guides.github.com/features/mastering-markdown/)

