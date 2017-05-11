# Configuratie van de webserver & de webapp's

Dit stappenplan moet een uitleg vormen van hoe de webserver geconfigureerd is en de websites die draaien juist geladen worden.
Volgende dingen worden er even besproken:

1. [Geinstalleerde pakketten](#geinstalleerde-pakketten)
2. [Configuratie van apache](#configuratie-van-apache)
3. [Folderstructuur](#folderstructuur)

## Geinstalleerde pakketten

Om alle webservices te laten werken zijn er een aantal pakketten nodig:

- Apache 2
- PHP 5.6.4 of hoger

Installeer deze pakketen op uw platform om door te kunnen gaan met deze uitleg.
Hier wordt er gewerkt op een Debian systeem.


## Configuratie van apache 

De apache config files bevinden zich op `/etc/apache2`

- Pas de `/etc/apache2/sites-available/000-default.conf` virtualhost file aan zodat deze eruitziet als volgt:
```
<VirtualHost *:80>
	ServerAdmin webmaster@localhost
	DocumentRoot /var/www/html/etsimport/public

	Alias /webconfig /var/www/webconfig
	Alias /webpage /var/www/webpage

	ErrorLog ${APACHE_LOG_DIR}/error.log
	CustomLog ${APACHE_LOG_DIR}/access.log combined
</VirtualHost>

```
Belangrijk hierbij is het aanpassen van de documentRoot en het toevoegen van de 2 Aliassen
	- Documentroot wijst naar het ETS config Laravel project met de landing page
	- De 2 Aliassen wijzen naar de 2 andere puur html pagina's met de configuratie en de besturing


- Pas in de `/etc/apache2/apache2.conf` file `AllowOverride None` aan naar `All` zodat je dit krijgt:
```
<Directory /var/www/>
        Options Indexes FollowSymLinks
        AllowOverride All
        Require all granted
</Directory>

```

## Folderstructuur

De folderstructuur in `/var/www` ziet eruit als volgt:

- html
	- etsimport (777)
- webconfig	(755)
- webpage (755)