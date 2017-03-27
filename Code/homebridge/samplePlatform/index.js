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

    this.jsonObjects = require('/home/olivier/config.json');
    this.jsonObjects = this.jsonObjects.objects;

    if (api) {
        // Save the API object as plugin needs to register new accessory via this object.
        this.api = api;

        // Listen to event "didFinishLaunching", this means homebridge already finished loading cached accessories
        // Platform Plugin should only register new accessory that doesn't exist in homebridge after this event.
        // Or start discover new accessories
        this.api.on('didFinishLaunching', function() {
            platform.log("DidFinishLaunching");
        
            for(var i = 0; i < this.jsonObjects.length; i++)
            {
                if(this.jsonObjects[i].homekit)
                    this.addCommunicationObject(this.jsonObjects[i].Naam, i, this.jsonObjects[i].Type);
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

    this.log("Nummer: " + accessory.context.objectNumber);

    if (accessory.getService(Service.Lightbulb)) {
        accessory.getService(Service.Lightbulb)
        .getCharacteristic(Characteristic.On)
        .on('set', function(value, callback) {
            platform.log(accessory.displayName, "Light -> " + value);
            //platform.log(accessory.displayName, "Nummer: " + accessory.context.objectNumber);
            //platform.log(accessory.displayName, "Type: " + accessory.context.objectType);
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
OliKnx_Platform.prototype.addCommunicationObject = function(objectName, objectNumber, objectType) {
    
    var platform = this;
    var uuid;

    // Generate unique uuid for each object
    uuid = UUIDGen.generate(objectName);

    // Check if object is already registered before
    var uuidExists = this.accessories.filter(function(item) {
        return item.UUID == uuid;
    }).length;

    if (uuidExists == 0) {

        // Object wasn't registered, we add it now

        this.log("CommunicatieObject toevoegen: " + objectName);

        var newAccessory = new Accessory(objectName, uuid);
        newAccessory.on('identify', function(paired, callback) {
            platform.log(accessory.displayName, "Identify!!!");
            callback();
        });

        // We slagen het type op in het object
        newAccessory.context.objectType = objectType;
        newAccessory.context.objectNumber = objectNumber;
        
        // Make sure you provided a name for service otherwise it may not visible in some HomeKit apps.
        newAccessory.addService(Service.Lightbulb, objectName)
        .getCharacteristic(Characteristic.On)
        .on('set', function(value, callback) {
            platform.log(newAccessory.displayName, "Light -> " + value);
            platform.log(newAccessory.displayName, "Nummer: " + newAccessory.context.objectNumber);
            platform.log(newAccessory.displayName, "Type: " + newAccessory.context.objectType);
            callback();
        });

        // Het object is klaar, we slagen het op
        this.accessories.push(newAccessory);
        this.api.registerPlatformAccessories("homebridge-OliKnx_Platform", "OliKnx_Platform", [newAccessory]);
    }
}
