/**
 * @file main.cpp
 * @author Kalina Knight
 * @brief The main cpp file with setup() and loop().
 * Please see the README for further explanation.
 * @version 0.1
 * @date 2021-08-24
 *
 * @copyright (c) 2021 Kalina Knight - MIT License
 */

#include <Arduino.h>
#include <LoRaWan-RAK4630.h> // Click to get library: https://platformio.org/lib/show/6601/SX126x-Arduino

#include "LoRaWAN_functs.h" /**< Go here to change the LoRaWAN settings. */
#include "Logging.h"        /**< Go here to change the logging level for the entire application. */
#include "OTAA_keys.h"      /**< Go here to set the OTAA keys (See LoRaWAN_functs README). */
#include "Ports.h"          /**< Go here to see existing and define new sensor/port schemas. */
#include "SensorHelper.h"   /**< Go here to add code for init-ing and reading new additional sensors. */

// APP TIMER
const int lorawan_app_interval = 300000; /**< App payloadTimer interval value in [ms] = 5mins. */
SoftwareTimer payloadTimer;              /**< payloadTimer to wakeup task and send payload. */
// forward declarations
static void appTimerInit(void);
static void appTimerTimeoutHandler(TimerHandle_t unused);

// POWER SAVING - see README for further details on Semaphores & low power mode
// TODO: not sure about pdFalse
static SemaphoreHandle_t semaphore_handle = NULL; /**< Semaphore used by events to wake up loop task. */
enum class EVENT_TASK {
    SLEEP,        /**< Use semaphore take to "sleep" in a low power state. */
    SEND_PAYLOAD, /**< Send a sensor reading payload. */
};
static EVENT_TASK current_task = EVENT_TASK::SLEEP; /**< Current task of the device, similar to a finite
                                                       state machine
                                                       design. Used in loop() to switch between tasks. */

// PAYLOAD ENCODING
uint8_t payload_buffer[PAYLOAD_BUFFER_SIZE] = {};                /**< Buffer that payload data is placed in. */
lmh_app_data_t lorawan_payload = { payload_buffer, 0, 0, 0, 0 }; /**< Struct that passes the payload buffer and
                                                                    relevant params for a LoRaWAN frame. */
// forward declaration
void fillPayload(void);

// PORT/SENSOR SELECTION
// The chosen port determines the sensor data included in the payload - see
// PortSchema.h
static portSchema payload_port = PORT1; /**< Frame data port. E.g. port 3: battery voltage + temperature */

/**
 * @brief Setup code runs once on reset/startup.
 */
void setup() {
    // initialise the logging module - function does nothing if APP_LOG_LEVEL in
    // Logging.h = NONE
    initLogging();
    log(LOG_LEVEL::INFO,
        "\n============================================"
        "\nWelcome to Combined Library WisBlock Example"
        "\n============================================");

    // Create the semaphore that will enable low power 'sleep'
    semaphore_handle = xSemaphoreCreateBinary();

    // Init sensors according to payload_port selected
    if (!payload_port.initSensors()) {
        // OR USE initSensors() FROM SensorHelper.h
        // if (!initSensors(&payload_port, false, false)) {

        // error init-ing sensors
        delay(1000);
        return;
    }

    // Init payloadTimer
    appTimerInit();

    // Init LoRaWAN
    if (!initLoRaWAN(&payloadTimer, OTAA_KEY_APP_EUI, OTAA_KEY_DEV_EUI, OTAA_KEY_APP_KEY)) {
        delay(1000);
        return;
    }

    // Attempt to join the network
    startLoRaWANJoinProcedure();

    // Go to 'sleep' now that setup is complete until an event task is triggered
    current_task = EVENT_TASK::SLEEP;
}

/**
 * @brief Loop code runs repeated after setup().
 */
void loop() {
    switch (current_task) {
        case EVENT_TASK::SLEEP:
            // Sleep until we are woken up by an event
            log(LOG_LEVEL::DEBUG, "Semaphore sleep");
            // This function call puts the device to 'sleep' in low power mode.
            // The semaphore can only be taken once given in appTimerTimeoutHandler()
            // (or another function). It will wait (up to portMAX_DELAY ticks) for the
            // semaphore_handle semaphore to be given.
            xSemaphoreTake(semaphore_handle, portMAX_DELAY);
            // This point is only reached if the semaphore was able to be taken or the
            // function timed out. If the semaphore was able to be taken, then the
            // current_task should have been set before giving the semaphore. If
            // xSemaphoreTake() timed out then the current_task has not changed and the
            // switch-case will come back to EVENT_TASK::SLEEP and sleep again.
            break;

        case EVENT_TASK::SEND_PAYLOAD:
            // do nothing if not connected
            if (isLoRaWANConnected()) {
                log(LOG_LEVEL::DEBUG, "Send payload");
                // fill lora data buffer
                fillPayload();
                // send data
                sendLoRaWANFrame(&lorawan_payload);
            } else {
                log(LOG_LEVEL::DEBUG, "LoRaWAN not connected. Try again later.");
            }
            // go back to 'sleep'
            current_task = EVENT_TASK::SLEEP;
            break;

        default:
            // just in case there's an unknown current_task, go to 'sleep'
            current_task = EVENT_TASK::SLEEP;
            break;
    }
}

/**
 * @brief Function for the payloadTimer initialization.
 * Initializes the payloadTimer as repeating with lorawan_app_interval timeout.
 */
void appTimerInit(void) {
    log(LOG_LEVEL::DEBUG, "Initialising timer...");
    payloadTimer.begin(lorawan_app_interval, appTimerTimeoutHandler);
}

/**
 * @brief Function for handling payloadTimer timeout event.
 * Sets the current_task to SEND_PAYLOAD and then 'wakes' the device by giving
 * the semaphore so then it can be taken in loop(), and the switch case will
 * move to the new current_task.
 */
void appTimerTimeoutHandler(TimerHandle_t unused) {
    current_task = EVENT_TASK::SEND_PAYLOAD;
    // Give the semaphore, so the loop task can take it and wake up
    xSemaphoreGiveFromISR(semaphore_handle, pdFALSE);
}

/**
 * @brief Gets the sensor data, then fills payload_buffer with the encoded data
 * ready for sending via LoRaWAN. Follows the portSchema specified in
 * PortSchema.h.
 */
void fillPayload(void) {
    // get the sensor data
    sensorData sensor_data = {};
    sensor_data = payload_port.readSensors();
    // OR USE getSensorData() FROM SensorHelper.h
    // sensor_data = getSensorData(&payload_port);

    // log sensor data
    char log_sensor_data[MAX_LOG_LENGTH] = {};
    sensor_data.printable(log_sensor_data, MAX_LOG_LENGTH);

    log(LOG_LEVEL::INFO, "%s", log_sensor_data);

    // reset the payload
    memset(payload_buffer, 0, sizeof(payload_buffer));
    lorawan_payload.buffsize = 0;
    lorawan_payload.port = payload_port.port_number;

    // encode the sensor data to lorawan_payload
    lorawan_payload.buffsize = payload_port.encodeSensorDataToPayload(&sensor_data, payload_buffer);

    // log the encoded bytes
    char encoded_payload_bytes[3 * PAYLOAD_BUFFER_SIZE] = {};
    for (int b = 0; b < lorawan_payload.buffsize; b++) {
        snprintf(encoded_payload_bytes, sizeof(encoded_payload_bytes), "%s%02X ", encoded_payload_bytes, payload_buffer[b]);
    }
    log(LOG_LEVEL::INFO, "Port: %2.d | Payload: %s", lorawan_payload.port, encoded_payload_bytes);
}
