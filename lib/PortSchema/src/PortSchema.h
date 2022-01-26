#ifndef PORT_SCHEMA_H
#define PORT_SCHEMA_H

/**
 * @file PortSchema.h
 * @author Kalina Knight (kalina.knight77@gmail.com)
 * @brief Port schema object as descibed the README.
 * Schema's include the functions for encoding and decoding the data to the payload.
 *
 * @version 0.3
 * @date 2022-01-26
 *
 * @copyright (c) 2021 Kalina Knight - MIT License
 */

#include "SensorPortSchema.h" /**< Go here for the individual sensor schema definitions. */

/** @brief portSchema describes which sensor data to include in each port and hence the payload. */
class portSchema {
  private:
    bool (*init_s)(portSchema *);
    sensorData (*read_s)(portSchema *);

  public:
    uint8_t port_number;

    /**< Number of sensor data readings of that type included in this port. If == 0 then data from that sensor is not
     * included at all. */
    uint8_t sendBatteryVoltage;
    uint8_t sendTemperature;
    uint8_t sendRelativeHumidity;
    uint8_t sendAirPressure;
    uint8_t sendGasResistance;
    uint8_t sendLocation;
    /* An example of a new sensor:
     * uint8_t sendNewSensor;
     */

    /**
     * @brief Define a new port schema without unique sensor operation functions.
     * All sensor readings are limited to send MAX_SENSOR_VALUES.
     * This does not check if the defined port will fit in a payload.
     * @param _port_number          Port number of this port.
     * @param _sendBatteryVoltage   Number of battery voltage readings in this port.
     * @param _sendTemperature      Number of temperature readings in this port.
     * @param _sendRelativeHumidity Number of relative humidity readings in this port.
     * @param _sendAirPressure      Number of air pressure readings in this port.
     * @param _sendGasResistance    Number of gas resistance readings in this port.
     * @param _sendLocation         Number of location readings in this port.
     */
    portSchema(uint8_t _port_number, uint8_t _sendBatteryVoltage, uint8_t _sendTemperature, uint8_t _sendRelativeHumidity,
               uint8_t _sendAirPressure, uint8_t _sendGasResistance, uint8_t _sendLocation);

    /**
     * @brief Define a new port schema without unique sensor operation functions.
     * All sensor readings are limited to send MAX_SENSOR_VALUES.
     * This does not check if the defined port will fit in a payload.
     * @param _port_number          Port number of this port.
     * @param _sendBatteryVoltage   Number of battery voltage readings in this port.
     * @param _sendTemperature      Number of temperature readings in this port.
     * @param _sendRelativeHumidity Number of relative humidity readings in this port.
     * @param _sendAirPressure      Number of air pressure readings in this port.
     * @param _sendGasResistance    Number of gas resistance readings in this port.
     * @param _sendLocation         Number of location readings in this port.
     * @param _initSensors          Function pointer to sensor initialisation for this port.
     * @param _readSensors          Function pointer to sensor reading for this port.
     */
    portSchema(uint8_t _port_number, uint8_t _sendBatteryVoltage, uint8_t _sendTemperature,
               uint8_t _sendRelativeHumidity, uint8_t _sendAirPressure, uint8_t _sendGasResistance,
               uint8_t _sendLocation, bool (*_initSensors)(portSchema *), sensorData (*_readSensors)(portSchema *));

    /**
     * @brief Encodes the given sensor data into the payload according to the port's schema.
     * Calls sensorPortSchema::encodeData for each sensor.
     * @param sensor_data Sensor data to be encoded.
     * @param payload_buffer Payload buffer for data to be written into.
     * @param start_pos Start encoding data at this byte. Defaults to 0.
     * @return Total length of data encoded to payload_buffer.
     */
    uint8_t encodeSensorDataToPayload(sensorData *sensor_data, uint8_t *payload_buffer, uint8_t start_pos = 0);

    /**
     * @brief Decodes the given payload into the sensor data according to the port's schema.
     * Calls sensorPortSchema::decodeData for each sensor.
     * @param buffer Payload buffer to be decoded.
     * @param len Length of payload buffer.
     * @param start_pos Start decoding data at this byte. Defaults to 0.
     * @return Decoded sensor data.
     */
    sensorData decodePayloadToSensorData(uint8_t *buffer, uint8_t len, uint8_t start_pos = 0);

    /**
     * @brief Compares for full equivalence between two port objects.
     * @param port2 Second port that this port is compared to.
     * @return True if they're equivalent, false if not.
     */
    bool operator==(const portSchema &port2);

    /**
     * @brief Combines two ports into separate port.
     * The port number is set to 0, and each send sensor is summed.
     * @param port2 Second port that this port is combined with.
     * @return Another port schema object that combines the given ports.
     */
    portSchema operator+(const portSchema &port2) const;

    /**
     * @brief Initialise the given sensors based on the port schema.
     * Defined in object construction - if not defined then this function will always return false.
     * @return True if successful. False if not.
     */
    bool initSensors() { return init_s(this); };

    /**
     * @brief Get the sensor data based on the port schema.
     * Defined in object construction - if not defined then this function will always empty sensorData.
     * @return The sensor data in sensorData struct format.
     */
    sensorData readSensors() { return read_s(this); };
};

/**
 * @brief Default init sensors for error port.
 * @return Always false.
 */
bool initPortErrorSensors(portSchema *port);

/**
 * @brief Default read sensors for error port.
 * @return Always empty sensorData.
 */
sensorData readPortErrorSensors(portSchema *port);

const portSchema PORTERROR( // Port returned when an error has occurred
    __UINT8_MAX__,          // port_number
    0,                      // sendBatteryVoltage
    0,                      // sendTemperature
    0,                      // sendRelativeHumidity
    0,                      // sendAirPressure
    0,                      // sendGasResistance
    0,                      // sendLocation
    &initPortErrorSensors,  // initSensors
    &readPortErrorSensors   // readSensors
);

#endif // PORT_SCHEMA_H