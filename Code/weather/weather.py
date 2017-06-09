import json
import urllib.request as get
from config import *

cityId = 2794118  # kontich

url = "http://api.openweathermap.org/data/2.5/weather" \
      + "?id=" + str(cityId) \
      + "&APPID=" + str(apiKey) \
      + "&units=metric"

rawData = get.urlopen(url).read()
# print(rawData)

# Decode json
data = json.loads(rawData)

# weather vars
temp = data["main"]["temp"]
weather = data["weather"][0]["main"]

print("temp: %d°C, weer: %s" % (temp, weather))
