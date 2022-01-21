#include "PortSchema.h"
#include "SensorReadingFuncts.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SCHEMA DEFINITIONS: See readme for definitions in tabular format.

const portSchema PORT1( // Port 1
    1,                  // port_number
    1,                  // sendBatteryVoltage
    0,                  // sendTemperature
    0,                  // sendRelativeHumidity
    0,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort1Sensors,  // initSensors
    &readPort1Sensors   // readSensors
);

const portSchema PORT2( // Port 2
    2,                  // port_number
    0,                  // sendBatteryVoltage
    1,                  // sendTemperature
    0,                  // sendRelativeHumidity
    0,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort2Sensors,  // initSensors
    &readPort2Sensors   // readSensors
);

const portSchema PORT3( // Port 3
    3,                  // port_number
    1,                  // sendBatteryVoltage
    1,                  // sendTemperature
    0,                  // sendRelativeHumidity
    0,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort3Sensors,  // initSensors
    &readPort3Sensors   // readSensors
);

const portSchema PORT4( // Port 4
    4,                  // port_number
    0,                  // sendBatteryVoltage
    1,                  // sendTemperature
    1,                  // sendRelativeHumidity
    0,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort4Sensors,  // initSensors
    &readPort4Sensors   // readSensors
);

const portSchema PORT5( // Port 5
    5,                  // port_number
    1,                  // sendBatteryVoltage
    1,                  // sendTemperature
    1,                  // sendRelativeHumidity
    0,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort5Sensors,  // initSensors
    &readPort5Sensors   // readSensors
);

const portSchema PORT6( // Port 6
    6,                  // port_number
    0,                  // sendBatteryVoltage
    1,                  // sendTemperature
    1,                  // sendRelativeHumidity
    1,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort6Sensors,  // initSensors
    &readPort6Sensors   // readSensors
);

const portSchema PORT7( // Port 7
    7,                  // port_number
    1,                  // sendBatteryVoltage
    1,                  // sendTemperature
    1,                  // sendRelativeHumidity
    1,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPort7Sensors,  // initSensors
    &readPort7Sensors   // readSensors
);

const portSchema PORT8( // Port 8
    8,                  // port_number
    0,                  // sendBatteryVoltage
    1,                  // sendTemperature
    1,                  // sendRelativeHumidity
    1,                  // sendAirPressure
    1,                  // sendGasResistance
    0,                  // sendLocation
    &initPort8Sensors,  // initSensors
    &readPort8Sensors   // readSensors
);

const portSchema PORT9( // Port 9
    9,                  // port_number
    1,                  // sendBatteryVoltage
    1,                  // sendTemperature
    1,                  // sendRelativeHumidity
    1,                  // sendAirPressure
    1,                  // sendGasResistance
    0,                  // sendLocation
    &initPort9Sensors,  // initSensors
    &readPort9Sensors   // readSensors
);

const portSchema PORT50( // Port 50
    50,                  // port_number
    0,                   // sendBatteryVoltage
    0,                   // sendTemperature
    0,                   // sendRelativeHumidity
    0,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort50Sensors,  // initSensors
    &readPort50Sensors   // readSensors
);

const portSchema PORT51( // Port 51
    51,                  // port_number
    1,                   // sendBatteryVoltage
    0,                   // sendTemperature
    0,                   // sendRelativeHumidity
    0,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort51Sensors,  // initSensors
    &readPort51Sensors   // readSensors
);

const portSchema PORT52( // Port 52
    52,                  // port_number
    0,                   // sendBatteryVoltage
    1,                   // sendTemperature
    0,                   // sendRelativeHumidity
    0,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort52Sensors,  // initSensors
    &readPort52Sensors   // readSensors
);

const portSchema PORT53( // Port 53
    53,                  // port_number
    1,                   // sendBatteryVoltage
    1,                   // sendTemperature
    0,                   // sendRelativeHumidity
    0,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort53Sensors,  // initSensors
    &readPort53Sensors   // readSensors
);

const portSchema PORT54( // Port 54
    54,                  // port_number
    0,                   // sendBatteryVoltage
    1,                   // sendTemperature
    1,                   // sendRelativeHumidity
    0,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort54Sensors,  // initSensors
    &readPort54Sensors   // readSensors
);

const portSchema PORT55( // Port 55
    55,                  // port_number
    1,                   // sendBatteryVoltage
    1,                   // sendTemperature
    1,                   // sendRelativeHumidity
    0,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort55Sensors,  // initSensors
    &readPort55Sensors   // readSensors
);

const portSchema PORT56( // Port 56
    56,                  // port_number
    0,                   // sendBatteryVoltage
    1,                   // sendTemperature
    1,                   // sendRelativeHumidity
    1,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort56Sensors,  // initSensors
    &readPort56Sensors   // readSensors
);

const portSchema PORT57( // Port 57
    57,                  // port_number
    1,                   // sendBatteryVoltage
    1,                   // sendTemperature
    1,                   // sendRelativeHumidity
    1,                   // sendAirPressure
    0,                   // sendGasResistance
    1,                   // sendLocation
    &initPort57Sensors,  // initSensors
    &readPort57Sensors   // readSensors
);

const portSchema PORT58( // Port 58
    58,                  // port_number
    0,                   // sendBatteryVoltage
    1,                   // sendTemperature
    1,                   // sendRelativeHumidity
    1,                   // sendAirPressure
    1,                   // sendGasResistance
    1,                   // sendLocation
    &initPort58Sensors,  // initSensors
    &readPort58Sensors   // readSensors
);

const portSchema PORT59( // Port 59
    59,                  // port_number
    1,                   // sendBatteryVoltage
    1,                   // sendTemperature
    1,                   // sendRelativeHumidity
    1,                   // sendAirPressure
    1,                   // sendGasResistance
    1,                   // sendLocation
    &initPort59Sensors,  // initSensors
    &readPort59Sensors   // readSensors
);

/* An example of a new port:

// use the default initPortSensors() & readPortSensors() if they're the same
bool initPortSensorsX(portSchema *port);
sensorData readPortSensorsX(portSchema *port);

const portSchema PORTX( // Port X
    X,                  // port_number
    0,                  // sendBatteryVoltage
    0,                  // sendTemperature
    0,                  // sendRelativeHumidity
    0,                  // sendAirPressure
    0,                  // sendGasResistance
    0,                  // sendLocation
    &initPortSensorsX,  // initSensors
    &readPortSensorsX   // readSensors
);
*/
