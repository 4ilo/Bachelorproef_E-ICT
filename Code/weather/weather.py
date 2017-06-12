#!/usr/bin/env python3.6

import json
import urllib.request as get
import sys

from config import *
from SimKnx import SimKnx

def getWeather():
    url = "http://api.openweathermap.org/data/2.5/weather" \
          + "?id=" + str(cityId) \
          + "&APPID=" + str(apiKey) \
          + "&units=metric"

    rawData = get.urlopen(url).read()

    # Decode json
    return json.loads(rawData)


if(len(sys.argv) != 2):
    data = getWeather()

    # weather vars
    temp = data["main"]["temp"]
    weather = data["weather"][0]["main"]
    wind = data["wind"]["speed"]

else:
    wind = int(sys.argv[1])

print("wind: %d m/s" % wind)

SimKnx = SimKnx()

if (wind >= 10):
    SimKnx.setintegerObject(5, 100)     # We sturen rolluik naar beneden

