//
// Created by olivier on 23/02/17.
// Deze defines zijn gegenereerd op basis van de commando's in de datasheet
// van SIM-KNX op pagina 26/27
//

#ifndef SIM_KNX_COMMANDS_H
#define SIM_KNX_COMMANDS_H

// General commands
#define GET_PHY_ADDR "dag"
#define SET_PHY_ADDR "das", 0, 1
#define GET_PROGRAM_MODE "dpg"
#define SET_PROGRAM_MODE "dps", 0, 1
#define RESTART "dr"
#define GET_DEVICE_STATE "dsg"
#define GET_VERSION "dvg"
#define DEVICE_TRANSPARANT_SET "dts", 0, 1
#define FACTORY_RESET "gci"
#define PARAMETER_DATA_GET "pdg", 2
#define SET_INTERFACE_OBJECT_DATA "ids", 2, 1
#define GET_INTERFACE_OBJECT_DATA "idg", 2

// Commands in normal mode
#define SET_OBJECT_DATA "ods", 1, 1
#define GET_OBJECT_DATA "odg", 1
#define SEND_GROUP_TELEGRAM "odt", 1
#define SEND_GROUP_READ_TELEGRAM "odr", 1
#define GET_RAM_FLAGS "ofg", 1
#define SET_OBJECT_VALUE "ovs", 1, 1
#define GET_OBJECT_VALUE "ovg", 1
#define SET_SENDING_GROUP_ADDR "ogs", 1, 1
#define ADD_GROUP_ADDR "oga", 1, 1
#define DELETE_GROUP_ADDR "ogd", 1, 1
#define GET_GROUP_ADDRS "ogg", 1
#define SET_OBJECT_CONFIG "ocs", 1, 6
#define GET_OBJECT_CONFIG "ocg", 1
#define SET_EVENT_GENERATION "dus"
#define GET_UPDATE_FLAGS "gug"
#define GET_VALUECHANGED_FLAGS "gcg"
#define GET_TIMEOUT_FLAGS "gtg"
//#define SEND_GLOBAL_UPDATE_FLAG "gui"
#define SEND_UPDATE_FLAG "oui"


// Commands in transparant mode
#define TRANSPARANT_DATA_SEND "tds", 1, 1
#define TRANSPARANT_RESPONSE_SEND "tes", 1, 1
#define TRANSPARANT_READ_REQUEST "trs", 1
//#define TRANSPARANT_READ_INDICATION "tri", 2
//#define TRANSPARANT_DATA_INDICATION "tdi", 3, 1
//#define TRANSPARANT_RESPONSE_INDICATION "tei", 3, 1
//#define TRANSPARANT_READ_CONFIRMATION "trc", 2
//#define TRANSPARANT_DATA_CONFIRMATION "tdc", 3, 1
//#define TRANSPARANT_RESPONSE_CONFIRMATION "tec", 3, 1
//#define TRANSPARANT_READ_NEGATIVE_CONFIRMATION "trn", 2
//#define TRANSPARANT_DATA_NEGATIVE_CONFIRMATION "tdn", 3, 1
//#define TRANSPARANT_RESPONSE_NEGATIVE_CONFIRMATION "ten", 3, 1










#endif //SIM_KNX_COMMANDS_H
