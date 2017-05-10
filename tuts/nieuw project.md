# Aanmaken van een configuratie file

Het aanmaken van een configuratiefile kan gebeuren op 2 verschillende manieren:

- [Via de ETS import tool](#via-de-ets-import-tool)
- [Manueel via de web configuratie tool]()

## Via de ETS import tool

De ETS import webtool is een webservice die op basis van een export van een werkend ETS project een config.json file aanmaakt dat gebruikt kan worden om uw KNX-IoT installatie te besturen via een webservice. 

Inhoud:

1. [Aanmaken van ETS project](#aanmaken-van-ets-project)
2. [Exporteren van de groep adressen](#exporteren-van-de-groep-adressen)
3. [Openen van de ETS import tool]()


### Aanmaken van ETS project

Voor het aanmaken van een KNX ETS project wordt er verwezen naar 1 van de KNX gecertificeerde cursusen. We gaan er hier vanuit dat u weet hoe een correct project aangemaakt en in gebruik genomen wordt. Er zijn wel een paar opmerkingen/tips om het importeren zo makkelijk mogelijk te laten verlopen:


- Gebruik een juist gestructureerde groep adressen structuur: 
![alt text](./fotos/gstructuur.png "Groep adressen structuur")

- Geef groep adressen niet exact dezelfde naam, doe het bijvoorbeeld zoals volgt:
![alt text](./fotos/gnaam.png "Namen van groep adressen")

- Geef elk groep adres het juiste type als dit niet automatisch gebeurd:
![alt text](./fotos/gtype.png "Type van groep adressen")
- Toegelaten types zijn:
	- 1.001
	- 3.007
	- 5.001


### Exporteren van de groep adressen

Als het hele ETS project klaar is en voldoet aan bovenstaande tips, kan het geëxporteerd worden.

- Open het "Group Addresses" paneel in ETS en selecteer de hoogste groep:
![alt text](./fotos/hoofdgroep.png "Selecteer de hoofdgroep")

- Selecteer in de menubalk Edit -> Export "Group Addresses":
![alt text](./fotos/export.png "Selecteer de export tool")

- Zorg dat het formaat op XML staat en kies een locatie om op te slaan:
![alt text](./fotos/export2.png "Kies XML als output")


### Openen van de ETS import tool

De ETS import tool kan geopend worden via de landing page op de locale webserver:

- Zoek het ip-address van uw KNX-IoT bord

- Surf naar:

```
<ip-addr>:80
```

- Klik op import:
![alt text](./fotos/landingPage.png "Open ETS import")
