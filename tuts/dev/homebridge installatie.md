# Installeren van Homebridge

Homebridge is een Node.js server appicatie dat binnen je eigen netwerk een IOS HomeKit app kan emuleren. Het heeft ondersteuning voor custom plugins.

Het open source project is te vinden op github: [https://github.com/nfarina/homebridge](https://github.com/nfarina/homebridge)

Het volgende zal besproken worden:

1. [Installatie van Node.js](#installatie-van-nodejs)
2. [Installatie van HomeBridge](#installatie-van-homebridge)
3. [Configuratie van HomeBridge](#configuratie-van-homebridge)


## Installatie van Node.js

Om alles vlot en juist te laten werken willen we minstens:

- node 6.10.0
- npm 3.10.10

Voor de installatie van node.js wordt er verwezen naar de officele instructies van node.js. Dit kan gebeuren via een package manager of compilatie vanaf de broncode.


## Installatie van HomeBridge

- Homebridge kan geinstaleerd worden via de npm package manager:

```
sudo npm install -g --unsafe-perm homebridge
```

Dit installeerd homebridge globaal.

- Na het installeren zou het commando `homebridge` volgende output moeten geven:

```
No plugins found. See the README for information on installing plugins.
```


## Configuratie van HomeBridge

Na het installeren van HomeBridge wordt er automatisch een folder aangemaakt: `~/.homebridge`. 
- In deze folder maken we een config.json file aan met volgende inhoud:
`nano ~/.homebridge/config.json`

```
{
    "bridge": {
        "name": "KNX-IoT",
        "username": "CC:22:3D:E3:CE:31",
        "port": 51826,
        "pin": "031-45-154"
    },
    
    "description": "Your own KNX-IoT installation",

    "accessories": [
    ],

    "platforms": [
		{
			"platform": "OliKnx_Platform",
			"name": "Oli-knx",
			"configLocation": "/etc/KNX-iot/config.json",
			"knxUdpPort": 1234,
			"knxUdpHost": "localhost",
			"homebridgeHost": "0.0.0.0"
		}
    ]
}
```

Hier worden een paar instellingen voor homebridge aangemaakt waarin we specifieren dat we de KNX_Platform plugin gaan gebruiken.

- Vervolgens moeten we de plugin nog toevoegen aan Homebridge. Kopier de "OliKnxPlatform" folder vanuit de code naar `/usr/share/nodejs/lib/node_modules`.

- Als we nu `homebridge` starten zou alles moeten werken op voorwaarde dat er al een config.json file aangemaakt is in `/ets/KNX-iot`. Kijk hiervoor in de uitleg over een nieuw project op starten.