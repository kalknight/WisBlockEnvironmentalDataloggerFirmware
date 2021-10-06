#include "PortSchema.h"

void portSchema::encodeSensorDataToPayload(sensorData *sensor_data, lmh_app_data_t *lorawan_payload) {
    /* If the data should be included in the payload according to the portSchema, then encode the value.
     * he order of these if statements is the order the sensor data will be encoded into the payload and should match
     * the schema.
     * The buffsize is increased by the amount of data encoded in each step.
     */
    if (sendBatteryVoltage) {
        batteryVoltageSchema.encodeData(sensor_data->battery_mv.value, sensor_data->battery_mv.is_valid, lorawan_payload);
    }
    if (sendTemperature) {
        temperatureSchema.encodeData(sensor_data->temperature.value, sensor_data->temperature.is_valid, lorawan_payload);
    }
    if (sendRelativeHumidity) {
        relativeHumiditySchema.encodeData(sensor_data->humidity.value, sensor_data->humidity.is_valid, lorawan_payload);
    }
    if (sendAirPressure) {
        airPressureSchema.encodeData(sensor_data->pressure.value, sensor_data->pressure.is_valid, lorawan_payload);
    }
    if (sendGasResistance) {
        gasResistanceSchema.encodeData(sensor_data->gas_resist.value, sensor_data->gas_resist.is_valid, lorawan_payload);
    }
    if (sendLocation) {
        locationSchema.encodeData(sensor_data->location.latitude, sensor_data->location.is_valid, lorawan_payload);
        locationSchema.encodeData(sensor_data->location.longitude, sensor_data->location.is_valid, lorawan_payload);
    }
}
