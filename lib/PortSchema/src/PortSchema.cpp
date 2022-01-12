#include "PortSchema.h"

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

portSchema getPort(uint8_t port_number) {
    switch (port_number) {
        case 1: {
            return PORT1;
        }
        case 2: {
            return PORT2;
        }
        case 3: {
            return PORT3;
        }
        case 4: {
            return PORT4;
        }
        case 5: {
            return PORT5;
        }
        case 6: {
            return PORT6;
        }
        case 7: {
            return PORT7;
        }
        case 8: {
            return PORT8;
        }
        case 9: {
            return PORT9;
        }
        case 50: {
            return PORT50;
        }
        case 51: {
            return PORT51;
        }
        case 52: {
            return PORT52;
        }
        case 53: {
            return PORT53;
        }
        case 54: {
            return PORT54;
        }
        case 55: {
            return PORT55;
        }
        case 56: {
            return PORT56;
        }
        case 57: {
            return PORT57;
        }
        case 58: {
            return PORT58;
        }
        case 59: {
            return PORT59;
        }
        default: {
            return PORTERROR;
        }
    }
}