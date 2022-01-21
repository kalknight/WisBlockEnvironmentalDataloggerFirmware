#include "PortSchema.h"

portSchema::portSchema(uint8_t _port_number, uint8_t _sendBatteryVoltage, uint8_t _sendTemperature,
                       uint8_t _sendRelativeHumidity, uint8_t _sendAirPressure, uint8_t _sendGasResistance,
                       uint8_t _sendLocation, bool (*initSensors)(portSchema *), sensorData (*readSensors)(portSchema *)) {
    port_number = _port_number;
    sendBatteryVoltage = _sendBatteryVoltage;
    sendTemperature = _sendTemperature;
    sendRelativeHumidity = _sendRelativeHumidity;
    sendAirPressure = _sendAirPressure;
    sendGasResistance = _sendGasResistance;
    sendLocation = _sendLocation;
    init_s = initSensors;
    read_s = readSensors;
}

uint8_t portSchema::encodeSensorDataToPayload(sensorData *sensor_data, uint8_t *payload_buffer, uint8_t start_pos) {
    /* If the data should be included in the payload according to the portSchema, then encode the value.
     * he order of these if statements is the order the sensor data will be encoded into the payload and should match
     * the schema.
     * The buffsize is increased by the amount of data encoded in each step.
     */
    uint8_t payload_length = start_pos;
    for (uint8_t i = 0; i < sendBatteryVoltage; i++) {
        payload_length = batteryVoltageSchema.encodeData(
            sensor_data->battery_mv[i].value, sensor_data->battery_mv[i].is_valid, payload_buffer, payload_length);
    }
    for (uint8_t i = 0; i < sendTemperature; i++) {
        payload_length = temperatureSchema.encodeData(
            sensor_data->temperature[i].value, sensor_data->temperature[i].is_valid, payload_buffer, payload_length);
    }
    for (uint8_t i = 0; i < sendRelativeHumidity; i++) {
        payload_length = relativeHumiditySchema.encodeData(
            sensor_data->humidity[i].value, sensor_data->humidity[i].is_valid, payload_buffer, payload_length);
    }
    for (uint8_t i = 0; i < sendAirPressure; i++) {
        payload_length = airPressureSchema.encodeData(sensor_data->pressure[i].value, sensor_data->pressure[i].is_valid,
                                                      payload_buffer, payload_length);
    }
    for (uint8_t i = 0; i < sendGasResistance; i++) {
        payload_length = gasResistanceSchema.encodeData(
            sensor_data->gas_resist[i].value, sensor_data->gas_resist[i].is_valid, payload_buffer, payload_length);
    }
    for (uint8_t i = 0; i < sendLocation; i++) {
        payload_length = locationSchema.encodeData(sensor_data->location[i].latitude, sensor_data->location[i].is_valid,
                                                   payload_buffer, payload_length);
        payload_length = locationSchema.encodeData(sensor_data->location[i].longitude,
                                                   sensor_data->location[i].is_valid, payload_buffer, payload_length);
    }
    return payload_length;
}

sensorData portSchema::decodePayloadToSensorData(uint8_t *buffer, uint8_t len, uint8_t start_pos) {
    sensorData sensor_data = {};
    uint8_t buff_pos = start_pos;

    for (uint8_t i = 0; (i < sendBatteryVoltage) && (buff_pos < len); i++) {
        buff_pos = batteryVoltageSchema.decodeData(&sensor_data.battery_mv[i].value,
                                                   &sensor_data.battery_mv[i].is_valid, buffer, buff_pos);
    }
    for (uint8_t i = 0; (i < sendTemperature) && (buff_pos < len); i++) {
        buff_pos = temperatureSchema.decodeData(&sensor_data.temperature[i].value, &sensor_data.temperature[i].is_valid,
                                                buffer, buff_pos);
    }
    for (uint8_t i = 0; (i < sendRelativeHumidity) && (buff_pos < len); i++) {
        buff_pos = relativeHumiditySchema.decodeData(&sensor_data.humidity[i].value, &sensor_data.humidity[i].is_valid,
                                                     buffer, buff_pos);
    }
    for (uint8_t i = 0; (i < sendAirPressure) && (buff_pos < len); i++) {
        buff_pos = airPressureSchema.decodeData(&sensor_data.pressure[i].value, &sensor_data.pressure[i].is_valid, buffer, buff_pos);
    }
    for (uint8_t i = 0; (i < sendGasResistance) && (buff_pos < len); i++) {
        buff_pos = gasResistanceSchema.decodeData(&sensor_data.gas_resist[i].value, &sensor_data.gas_resist[i].is_valid,
                                                  buffer, buff_pos);
    }
    for (uint8_t i = 0; (i < sendLocation) && (buff_pos < len); i++) {
        buff_pos = locationSchema.decodeData(&sensor_data.location[i].latitude, &sensor_data.location[i].is_valid, buffer, buff_pos);
        buff_pos = locationSchema.decodeData(&sensor_data.location[i].longitude, &sensor_data.location[i].is_valid, buffer, buff_pos);
    }

    return sensor_data;
}

bool portSchema::operator==(const portSchema &port2) {
    // clang-format off
    return ((port_number          == port2.port_number         ) &&
            (sendBatteryVoltage   == port2.sendBatteryVoltage  ) &&
            (sendTemperature      == port2.sendTemperature     ) &&
            (sendRelativeHumidity == port2.sendRelativeHumidity) &&
            (sendAirPressure      == port2.sendAirPressure     ) &&
            (sendGasResistance    == port2.sendGasResistance   ) &&
            (sendLocation         == port2.sendLocation        ));
    // clang-format on
}

portSchema portSchema::operator+(const portSchema &port2) const {
    portSchema combined_port = PORTERROR;
    // clang-format off
    combined_port.port_number = 0;
    combined_port.sendBatteryVoltage   = (this->sendBatteryVoltage   + port2.sendBatteryVoltage  );
    combined_port.sendTemperature      = (this->sendTemperature      + port2.sendTemperature     );
    combined_port.sendRelativeHumidity = (this->sendRelativeHumidity + port2.sendRelativeHumidity);
    combined_port.sendAirPressure      = (this->sendAirPressure      + port2.sendAirPressure     );
    combined_port.sendGasResistance    = (this->sendGasResistance    + port2.sendGasResistance   );
    combined_port.sendLocation         = (this->sendLocation         + port2.sendLocation        );
    // clang-format on
    return combined_port;
}

bool initPortErrorSensors(portSchema *port) {
    return false;
};

sensorData readPortErrorSensors(portSchema *port) {
    sensorData data = {};
    return data;
}