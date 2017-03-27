var http = require('http');
var Accessory, Service, Characteristic, UUIDGen;

module.exports = function(homebridge) {
    console.log("homebridge API version: " + homebridge.version);

    // Accessory must be created from PlatformAccessory Constructor
    Accessory = homebridge.platformAccessory;

    // Service and Characteristic are from hap-nodejs
    Service = homebridge.hap.Service;
    Characteristic = homebridge.hap.Characteristic;
    UUIDGen = homebridge.hap.uuid;
  
    // For platform plugin to be considered as dynamic platform plugin,
    // registerPlatform(pluginName, platformName, constructor, dynamic), dynamic must be true
    homebridge.registerPlatform("homebridge-samplePlatform", "OliKnx_Platform", OliKnx_Platform, true);
}

// Platform constructor
// config may be null
// api may be null if launched from old homebridge version
function OliKnx_Platform(log, config, api) {
    log("OliKnx_Platform Init");
    var platform = this;
    this.log = log;
    this.config = config;
    this.accessories = [];

    this.available = ["keuken", "living", "led"];

    if (api) {
        // Save the API object as plugin needs to register new accessory via this object.
        this.api = api;

        // Listen to event "didFinishLaunching", this means homebridge already finished loading cached accessories
        // Platform Plugin should only register new accessory that doesn't exist in homebridge after this event.
        // Or start discover new accessories
        this.api.on('didFinishLaunching', function() {
            platform.log("DidFinishLaunching");
        
            for(var i = 0; i < this.available.length; i++)
            {
                this.addAccessory(this.available[i]);
            }

        }.bind(this));
    }
}

// Function invoked when homebridge tries to restore cached accessory
// Developer can configure accessory at here (like setup event handler)
// Update current value
OliKnx_Platform.prototype.configureAccessory = function(accessory) {
    this.log(accessory.displayName, "Configure Accessory");
    var platform = this;

    // set the accessory to reachable if plugin can currently process the accessory
    // otherwise set to false and update the reachability later by invoking 
    // accessory.updateReachability()
    accessory.reachable = true;

    accessory.on('identify', function(paired, callback) {
        platform.log(accessory.displayName, "Identify!!!");
        callback();
    });

    if (accessory.getService(Service.Lightbulb)) {
        accessory.getService(Service.Lightbulb)
        .getCharacteristic(Characteristic.On)
        .on('set', function(value, callback) {
            platform.log(accessory.displayName, "Light -> " + value);
            callback();
        });
    }

    this.accessories.push(accessory);
}

//Handler will be invoked when user try to config your plugin
//Callback can be cached and invoke when nessary
OliKnx_Platform.prototype.configurationRequestHandler = function(context, request, callback) {
    this.log("Not implemented");
}

// Sample function to show how developer can add accessory dynamically from outside event
OliKnx_Platform.prototype.addAccessory = function(accessoryName) {
    this.log("Add Accessory");
    var platform = this;
    var uuid;

    uuid = UUIDGen.generate(accessoryName);

    var uuidExists = this.accessories.filter(function(item) {
        return item.UUID == uuid;
    }).length;

    if (uuidExists == 0) {

        var newAccessory = new Accessory(accessoryName, uuid);
        newAccessory.on('identify', function(paired, callback) {
            platform.log(accessory.displayName, "Identify!!!");
            callback();
        });
        // Plugin can save context on accessory
        // To help restore accessory in configureAccessory()
        // newAccessory.context.something = "Something"
        
        // Make sure you provided a name for service otherwise it may not visible in some HomeKit apps.
        newAccessory.addService(Service.Lightbulb, "Test Light")
        .getCharacteristic(Characteristic.On)
        .on('set', function(value, callback) {
            platform.log(newAccessory.displayName, "Light -> " + value);
            callback();
        });

        this.accessories.push(newAccessory);
        this.api.registerPlatformAccessories("homebridge-OliKnx_Platform", "OliKnx_Platform", [newAccessory]);
    }
}
