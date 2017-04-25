var Accessory, Service, Characteristic, UUIDGen;

var dgram = require("dgram");

module.exports = function(homebridge) 
{
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

//
//  Platform constructor
// 
function OliKnx_Platform(log, config, api) 
{
    log("OliKnx_Platform Init");
    var platform = this;
    this.log = log;
    this.config = config;
    this.accessories = [];

    this.jsonObjects = require(config.configLocation);        // Get the contents of the json config file
    this.jsonObjects = this.jsonObjects.objects;


    if (api) 
    {
        // Save the API object as plugin needs to register new accessory via this object.
        this.api = api;

        // Listen to event "didFinishLaunching", this means homebridge already finished loading cached accessories
        // Platform Plugin should only register new accessory that doesn't exist in homebridge after this event.
        // Or start discover new accessories
        this.api.on('didFinishLaunching', function() 
        {
            platform.log("DidFinishLaunching");
        
            // Loop over all objects in the config file & only atach the ones with homekit checked
            for(var i = 0; i < this.jsonObjects.length; i++)
            {
                if(this.jsonObjects[i].homekit)
                    this.addCommunicationObject(this.jsonObjects[i], i+1);
            }

        }.bind(this));
    }
}

//
//  Function invoked when homebridge tries to restore cached accessory
//  Developer can configure accessory at here (like setup event handler)
//  Update current value
//
OliKnx_Platform.prototype.configureAccessory = function(accessory) 
{
    this.log(accessory.displayName, "Configure Accessory");
    var platform = this;

    var objectNumber;

    // Get the object number based on the Uname
    if((objectNumber = this.isAvailable(accessory.context.objectUname)))
    {

        // Accessery is just being initialised, or stil exists in cache after reboot

        // set the accessory to reachable if plugin can currently process the accessory
        accessory.reachable = true;

        accessory.context.objectNumber = objectNumber;      // Update the object number
        var info = accessory.getService(Service.AccessoryInformation)

        switch(accessory.context.objectType)
        {
            case 1:
                // Boolean licht object
                accessory.getService(Service.Lightbulb)
                .getCharacteristic(Characteristic.On)
                .on('set', function(value, callback) {
                    platform.log("Set licht -> " + value);
                    platform.sendValue(objectNumber, value);
                    callback();
                })
                .on('get', function(callback) {

                    platform.log("Get licht");
                    platform.askValue(objectNumber, callback);       // Get the value over udp from sim-knx
                });

                info.setCharacteristic(Characteristic.SerialNumber, "Lamp");

                break;

            case 3:
                // Absolute sturing dimmer of rolluik 
                
                if(accessory.context.objectSoort == "Dimmer")
                {
                    // We zoeken het bijhorende schakelobject voor de dimmer
                    var schakelObject = this.objectNumber(accessory.context.object.SchakelObject);
                    if(schakelObject == false) { schakelObject = objectNumber };
                    this.log("Dimmer schakel: " + schakelObject);

                    // Dimmer object --> maakt gebruik van percentages!!
                    accessory.getService(Service.Lightbulb)
                    .getCharacteristic(Characteristic.On)
                    .on('set', function(value, callback) {
                        platform.log("Set licht -> " + value);
                        platform.sendValue(schakelObject, value);
                        callback();
                    })
                    .on('get', function(callback) {
                        platform.log("Get licht");            
                        platform.askValue(schakelObject,callback);
                    });

                    accessory.getService(Service.Lightbulb)
                    .getCharacteristic(Characteristic.Brightness)
                    .on('set', function(value, callback) {
                        platform.log("Dimming to " + value);
                        platform.sendValue(objectNumber, value);
                        callback();
                    })
                    .on('get', function(callback) {
                        platform.log("Get dimming");
                        platform.askValue(objectNumber, callback);
                    });

                    info.setCharacteristic(Characteristic.SerialNumber, "Dimmer");
                }
                else if(accessory.context.objectSoort == "Rolluik")
                {
                    // Absoluute rolluik sturing
                    var service = accessory.getService(Service.WindowCovering);
                    
                    service.getCharacteristic(Characteristic.TargetPosition)
                    .on('set', function(value, callback) {
                        platform.log("Set target pos to " + value);
                        platform.sendValue(objectNumber, value);

                        service.setCharacteristic(Characteristic.PositionState, Characteristic.PositionState.STOPPED);
                        service.setCharacteristic(Characteristic.CurrentPosition, value);

                        callback();
                    });

                    service.getCharacteristic(Characteristic.CurrentPosition)
                    .on('get', function(callback) {
                        platform.log("Getting current pos");
                        platform.askValue(objectNumber, callback, service);
                    });
                }
                

                break;

            case 4:
                // Scene object
                accessory.getService(Service.Switch)
                .getCharacteristic(Characteristic.On)
                .on('set', function(value, callback) {
                    platform.log("Setting scene to 1");
                    callback(1);
                })
                .on('get', function(callback) {
                    platform.log("Getting scene state");
                    callback(null, 0);
                })


                info.setCharacteristic(Characteristic.SerialNumber, "Scene");

                break;
        }

        this.accessories.push(accessory);    
    }
    else
    {
        // The accessery is in cache, but isn't in the config file anymore, we remove it from cache
        this.log("Removing unused accessery");
        this.api.unregisterPlatformAccessories("homebridge-OliKnx_Platform", "OliKnx_Platform", [accessory]);
    }
}

/**
 * Check if the object in de config file matches with a specific uname
 *
 * @param      {String}            uname    The Uniqe name for an object
 * @return     {(boolean|nummer)}  objectnumber if available, False otherwise.
 */
OliKnx_Platform.prototype.isAvailable = function(uname) 
{
    for(var i = 0; i < this.jsonObjects.length; i++)
    {
        if(this.jsonObjects[i].uname == uname && this.jsonObjects[i].homekit == true)
        {
            return i+1;     // Return the current object number, it could be changed in de config file
        }
    }

    return false;
}

OliKnx_Platform.prototype.objectNumber = function(uname)
{
    for(var i = 0; i < this.jsonObjects.length; i++)
    {
        if(this.jsonObjects[i].uname == uname)
        {
            return i+1;     // Return the current object number, it could be changed in de config file
        }
    }

    return false;
}

/**
 * Send a value over udp to sim-knx (boolean or absolute value)
 *
 * @param      int  objectNummer  The object nummer
 * @param      int  value         The value
 */
OliKnx_Platform.prototype.sendValue = function(objectNummer, value)
{
    var udpPort = this.config.knxUdpPort;
    var udpHost = this.config.knxUdpHost;

    var message =  "set " + objectNummer + " " + value;
    var socket = dgram.createSocket("udp4");
    socket.send(message, 0, message.length, udpPort, udpHost);
}

/**
* Get the value for the object from sim-knx over udp
*
* @param      Int  objectNumber  The object number
* @return     Int  The value for the object.
*/
OliKnx_Platform.prototype.askValue = function(objectNumber, callback, service = 0)
{
    var udpPort = this.config.knxUdpPort;
    var udpHost = this.config.knxUdpHost;

    var message = "get " + objectNumber;

    var socket = dgram.createSocket("udp4");
    socket.bind(0, this.config.homebridgeHost);

    socket.on("message", makeResponseHandler(callback, service));

    socket.send(message, 0, message.length, udpPort, udpHost);
}

/**
 * Function creates responsehandler for socket.on that can use the homebridge callback function when finiched
 *
 * @param      {Function}  callback  A homebridge provided callback function
 * @return     {<type>}    The callback that will be passed to the socket.on method
 */
function makeResponseHandler(callback, service) 
{
    return function(msg, rinfo) 
    {
        // Deal with response here
        
        if(service != 0)        // For blinds we have to set the targetPos in order to work properly
        {
            service.setCharacteristic(Characteristic.PositionState, Characteristic.PositionState.STOPPED);
            service.setCharacteristic(Characteristic.CurrentPosition, parseInt(msg));
            service.setCharacteristic(Characteristic.TargetPosition, parseInt(msg));
        }

        var value = parseInt(msg);
        callback(null,  value);         // Return value to homebridge
    }
}

/**
 * We add a new homekit object based on the object from the config file
 *
 * @param       object        The object from de config.json file
 * @param       objectNumber  The object number
 */
OliKnx_Platform.prototype.addCommunicationObject = function(object, objectNumber) 
{
    
    var platform = this;
    var uuid;

    // Generate unique uuid for each object based on uname
    uuid = UUIDGen.generate(object.uname);

    // Check if object is already registered before
    var uuidExists = this.accessories.filter(function(item) {
        return item.UUID == uuid;
    }).length;

    if (uuidExists == 0) 
    {

        // Object wasn't registered, we add it now
        this.log("CommunicatieObject toevoegen: " + object.homekitNaam);

        var newAccessory = new Accessory(object.homekitNaam, uuid);

        // We save some information in the object for later use
        newAccessory.context.objectType = object.Type;
        newAccessory.context.objectNumber = objectNumber;
        newAccessory.context.objectUname = object.uname;
        newAccessory.context.objectSoort = object.Soort;
        newAccessory.context.object = object;

        // Add info to the objects
        newAccessory.getService(Service.AccessoryInformation)
            .setCharacteristic(Characteristic.Manufacturer, "Ovde.be")
            .setCharacteristic(Characteristic.Model, "Oli-Udoo");


        // Generate a new service based on the type
        if(object.Type == 1)
        {
            newAccessory.addService(Service.Lightbulb, object.homekitNaam);
        }
        else if(object.Type == 3)
        {
            // Absoluute sturing (roluik of dimmer)
            if(object.Soort == "Dimmer")
            {
                newAccessory.addService(Service.Lightbulb, object.homekitNaam);
            }
            else if(object.Soort == "Rolluik")
            {
                newAccessory.addService(Service.WindowCovering, object.homekitNaam);
            }
        }


        // The object is ready, we wil configure an save it to the cache
        this.configureAccessory(newAccessory);
        this.api.registerPlatformAccessories("homebridge-OliKnx_Platform", "OliKnx_Platform", [newAccessory]);
    }
}

//
//  Handler will be invoked when user try to config your plugin
//  Callback can be cached and invoke when nessary
//
OliKnx_Platform.prototype.configurationRequestHandler = function(context, request, callback) 
{
    this.log("Not implemented");
}