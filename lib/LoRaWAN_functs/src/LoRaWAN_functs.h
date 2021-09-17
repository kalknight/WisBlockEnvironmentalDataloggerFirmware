/**
 * @file LoRaWAN_functs.h
 * @author Kalina Knight
 * @brief LoRaWAN functions and any associated variables.
 * Feel free to change the settings of the LoRaWAN connection.
 * The OTAA keys are defined locally (not remotely on GitHub) in a separate header file; see the README for further
 * explanantion.
 *
 * @version 0.1
 * @date 2021-08-24
 *
 * @copyright (c) 2021 Kalina Knight - MIT License
 */

#include <LoRaWan-RAK4630.h>

#include "Logging.h"

// LORAWAN CONFIG/PARAMETERS
static const DeviceClass_t loraClass = CLASS_A;                 /**< Class definition. */
static const LoRaMacRegion_t loraRegion = LORAMAC_REGION_AU915; /**< Region:AU915. */
static const lmh_confirm loraConfirm = LMH_UNCONFIRMED_MSG;     /**< Confirm/unconfirm packet definition. */

#define LORAWAN_DATERATE              DR_3        /**< LoRaMac datarates: DR_0 to DR_5*/
#define LORAWAN_TX_POWER              TX_POWER_10 /**< LoRaMac tx power: TX_POWER_0 to TX_POWER_10 (for AU915)*/
#define LORAWAN_JOIN_REQUEST_ATTEMPTS 3           /**< Join request reattempts. */
#define PAYLOAD_BUFFER_SIZE           64          /**< Data payload buffer size. */

/**
 * @brief Initialise LoRaWAN.
 * @param appEUI    OTAA key app EUI.
 * @param deviceEUI OTAA key device EUI.
 * @param appKey    OTAA key app key.
 * @return True if successful, false if not.
 */
bool initLoRaWAN(uint8_t *appEUI, uint8_t *deviceEUI, uint8_t *appKey);

/**
 * @brief Initialise LoRaWAN.
 * @param appEUI    OTAA key app EUI.
 * @param deviceEUI OTAA key device EUI.
 * @param appKey    OTAA key app key.
 * @param timer     Timer that will be started once network has been successfully joined.
 * @return True if successful, false if not.
 */
bool initLoRaWAN(uint8_t *appEUI, uint8_t *deviceEUI, uint8_t *appKey, SoftwareTimer *timer);

/**
 * @brief Attempt to join the LoRaWAN network.
 * Once connected the joined callback set in initLoRaWAN() will be called.
 */
inline void startLoRaWANJoinProcedure(void) {
    lmh_join();
};

/**
 * @brief Sends a frame with the data provided.
 * @param lora_app_data Data to be sent.
 */
void sendLoRaWANFrame(lmh_app_data_t *lora_app_data);

/**
 * @brief Gets the status of the current LoRaWAN connection.
 * @return True if connected, false if not.
 */
inline bool isLoRaWANConnected(void) {
    return (lmh_join_status_get() == LMH_SET);
};

/**
 * @brief Sets the class to loraClass.
 * @return True if successful, false if not.
 */
inline bool setLoRaWANClass(void) {
    return (lmh_class_request(loraClass) == LMH_SUCCESS);
};
