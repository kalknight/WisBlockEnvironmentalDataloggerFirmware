#ifndef PORT_SCHEMA_H
#define PORT_SCHEMA_H

/**
 * @file PortSchema.h
 * @author Kalina Knight (kalina.knight77@gmail.com)
 * @brief Port schema definition as descibed the README.
 * Schema's include the functions for encoding and decoding the data to the payload as well.
 *
 * @version 0.2
 * @date 2022-01-13
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
    uint8_t sendNewSensor;
    */

    portSchema(uint8_t _port_number, uint8_t _sendBatteryVoltage, uint8_t _sendTemperature,
               uint8_t _sendRelativeHumidity, uint8_t _sendAirPressure, uint8_t _sendGasResistance,
               uint8_t _sendLocation, bool (*initSensors)(portSchema *), sensorData (*readSensors)(portSchema *));

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
     *
     * @param port2 Second port that this port is compared to.
     * @return True if they're equivalent, false if not.
     */
    bool operator==(const portSchema &port2);

    /**
     * @brief Combines two ports into separate port.
     * The port number is set to 0, and the send sensor flags are ||'ed.
     * Useful for sensor initiatlisation if using the port definition for this purpose.
     *
     * @param port2 Second port that this port is combined with.
     * @return Another port schema object that combines the given ports.
     */
    portSchema operator+(const portSchema &port2) const;

    bool initSensors() { return init_s(this); };
    sensorData readSensors() { return read_s(this); };
};

/**
 * @brief Get the Port object for the given port number.
 * @param port_number
 * @return Returns the portSchema.
 */
portSchema getPort(uint8_t port_number);

bool initPortErrorSensors(portSchema *port);
sensorData readPortErrorSensors(portSchema *port);

const portSchema PORTERROR( // Port returned when error has occurred
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