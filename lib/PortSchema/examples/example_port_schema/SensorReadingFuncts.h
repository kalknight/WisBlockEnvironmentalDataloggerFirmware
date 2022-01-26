#ifndef EXAMPLE_SENSOR_READING_FUNCTS_H
#define EXAMPLE_SENSOR_READING_FUNCTS_H

/**
 * @file SensorReadingFuncts.h
 * @author Kalina Knight (kalina.knight77@gmail.com)
 * @brief  An example of custom sensor initialisation and reading functions for each port.
 * These functions are all just using initSensors() & getSensorData() from SensorHelper.h, but they can all be different
 * depending on the hardware and usage.
 *
 * @version 0.3
 * @date 2022-01-13
 *
 * @copyright (c) 2021 Kalina Knight - MIT License
 */

#include "PortSchema.h"
#include "SensorHelper.h"

bool initPort1Sensors(portSchema *port);
sensorData readPort1Sensors(portSchema *port);

bool initPort2Sensors(portSchema *port);
sensorData readPort2Sensors(portSchema *port);

bool initPort3Sensors(portSchema *port);
sensorData readPort3Sensors(portSchema *port);

bool initPort4Sensors(portSchema *port);
sensorData readPort4Sensors(portSchema *port);

bool initPort5Sensors(portSchema *port);
sensorData readPort5Sensors(portSchema *port);

bool initPort6Sensors(portSchema *port);
sensorData readPort6Sensors(portSchema *port);

bool initPort7Sensors(portSchema *port);
sensorData readPort7Sensors(portSchema *port);

bool initPort8Sensors(portSchema *port);
sensorData readPort8Sensors(portSchema *port);

bool initPort9Sensors(portSchema *port);
sensorData readPort9Sensors(portSchema *port);

bool initPort50Sensors(portSchema *port);
sensorData readPort50Sensors(portSchema *port);

bool initPort51Sensors(portSchema *port);
sensorData readPort51Sensors(portSchema *port);

bool initPort52Sensors(portSchema *port);
sensorData readPort52Sensors(portSchema *port);

bool initPort53Sensors(portSchema *port);
sensorData readPort53Sensors(portSchema *port);

bool initPort54Sensors(portSchema *port);
sensorData readPort54Sensors(portSchema *port);

bool initPort55Sensors(portSchema *port);
sensorData readPort55Sensors(portSchema *port);

bool initPort56Sensors(portSchema *port);
sensorData readPort56Sensors(portSchema *port);

bool initPort57Sensors(portSchema *port);
sensorData readPort57Sensors(portSchema *port);

bool initPort58Sensors(portSchema *port);
sensorData readPort58Sensors(portSchema *port);

bool initPort59Sensors(portSchema *port);
sensorData readPort59Sensors(portSchema *port);

#endif // EXAMPLE_SENSOR_READING_FUNCTS_H