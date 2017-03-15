"use strict";

var Service, Characteristic;
var exec = require('child_process').exec;
//var request = require("request");

module.exports = function (homebridge) {
    Service = homebridge.hap.Service;
    Characteristic = homebridge.hap.Characteristic;
    homebridge.registerAccessory("homebridge-led", "Led", LedAccessory);
}

function LedAccessory(log, config) {

    this.log = log;

    this.log("initialising led");
    this.log = log;
    this.name = config["name"];

    this.service = new Service.Lightbulb(this.name);

    this.service.getCharacteristic(Characteristic.On)
        .on("get", this.getState.bind(this))
        .on("set", this.setState.bind(this));

    // this.service = new Service.LockMechanism(this.name);

    // this.service.getCharacteristic(Characteristic.LockCurrentState).on("get", this.getState.bind(this));

    // this.service.getCharacteristic(Characteristic.LockTargetState)
    // .on('get', this.getState.bind(this))
    // .on('set', this.setState.bind(this));

    this.state = 0;
}

LedAccessory.prototype.getServices = function() {

    var informationService = new Service.AccessoryInformation();

    informationService.setCharacteristic(Characteristic.Manufacturer, "Ovde.be")
                      .setCharacteristic(Characteristic.Model, "Oli-Udoo")
                      .setCharacteristic(Characteristic.SerialNumber, "1");

    return [informationService, this.service];
}

LedAccessory.prototype.getState = function(callback) {

    this.log("Getting current state ...");

    callback(null, this.state);
}

LedAccessory.prototype.setState = function(state, callback) {
    this.log("Setting current state to " + state);

    this.state = !this.state

    // Set the led
    exec("/home/olivier/setgpio/setGpio " + state);

    callback(null);
}
