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
    homebridge.registerPlatform("homebridge-oliPlatform", "OliPlatform", OliPlatform, true);
}

  // Platform constructor
  // config may be null
  // api may be null if launched from old homebridge version
  function OliPlatform(log, config, api) {
    log("OliPlatform Init");
    var platform = this;
    this.log = log;
    this.config = config;
    this.accessories = [];

    // this.requestServer = http.createServer(function(request, response) {
    //   if (request.url === "/add") {
    //     this.addAccessory(new Date().toISOString());
    //     response.writeHead(204);
    //     response.end();
    //   }

    //   // if (request.url == "/reachability") {
    //   //   this.updateAccessoriesReachability();
    //   //   response.writeHead(204);
    //   //   response.end();
    //   // }

    //   // if (request.url == "/remove") {
    //   //   this.removeAccessory();
    //   //   response.writeHead(204);
    //   //   response.end();
    //   // }
    // }.bind(this));
    

    // this.requestServer.listen(18081, function() {
    //   platform.log("Server Listening...");
    // });

    if (api) {
      this.log("Api bestaat");
        // Save the API object as plugin needs to register new accessory via this object.
        this.api = api;

        // Listen to event "didFinishLaunching", this means homebridge already finished loading cached accessories
        // Platform Plugin should only register new accessory that doesn't exist in homebridge after this event.
        // Or start discover new accessories
        this.api.on('didFinishLaunching', function() {
          platform.log("DidFinishLaunching");

          this.addCommunicationObject("Rode led");
        }.bind(this));
    }


    // this.addAccessory(new Date().toISOString());
    //this.addAccessory("Living");
  }

  // Function invoked when homebridge tries to restore cached accessory
  // Developer can configure accessory at here (like setup event handler)
  // Update current value
  OliPlatform.prototype.configureAccessory = function(accessory) {
    /*this.log(accessory.displayName, "Configure Accessory");
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

    this.accessories.push(accessory);*/
  }


  //Handler will be invoked when user try to config your plugin
  //Callback can be cached and invoke when nessary
  OliPlatform.prototype.configurationRequestHandler = function(context, request, callback) {
      this.log("Not implemented");
  }


  // Sample function to show how developer can add accessory dynamically from outside event
  OliPlatform.prototype.addCommunicationObject = function(accessoryName, objectNummer, objectType) {
    
    this.log("Adding CommunicaionObject " + accessoryName);
    var platform = this;
    var uuid;

    uuid = UUIDGen.generate(accessoryName + new Date().toISOString());

    var newAccessory = new Accessory(accessoryName, uuid);
    newAccessory.on('identify', function(paired, callback) {
        platform.log(accessory.displayName, "Identify!!!");
        callback();
    });

    // Save the object nummer to the accessory
    newAccessory.context.objectNummer = objectNummer;
    
    // Make sure you provided a name for service otherwise it may not visible in some HomeKit apps.
    newAccessory.addService(Service.Lightbulb, accessoryName)
    .getCharacteristic(Characteristic.On)
    .on('set', function(value, callback) {
        platform.log("Setting value to " + value);
        platform.log("Objectnummer: " + newAccessory.context.objectNummer);
        callback();
    });

    this.accessories.push(newAccessory);
    this.api.registerPlatformAccessories("homebridge-oliPlatform", "OliPlatform", [newAccessory]);
  }
