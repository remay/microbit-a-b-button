/* 
 * Copyright (c) 2015 Robert May
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MicroBit.h"

// Uncomment next line to get perhiperal to request a connection be secured as soon as the connection is opened
//#define SECRURE_ON_CONNECTION
#ifdef SECURE_ON_CONNECTION 
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "device_manager.h"
#pragma GCC diagnostic pop
#endif

void onButtonAClick(MicroBitEvent) {   
    uBit.display.print('A');  
}

void onButtonBClick(MicroBitEvent) {   
    uBit.display.print('B');  
}

#ifdef SECURE_ON_CONNECTION 
void connectionCallback(const Gap::ConnectionCallbackParams_t *params) {

    uBit.display.print('C');  
    dm_handle_t dmHandle = {
        .appl_id = 0,
    };
    if (dm_handle_get(params->handle, &dmHandle) != NRF_SUCCESS) {
        uBit.panic(1);
    }

    if (dm_security_setup_req(&dmHandle) != NRF_SUCCESS) {
        uBit.panic(2);
    }

}
#endif

void app_main() {
    uBit.MessageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonAClick);
    uBit.MessageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonBClick);
    uBit.display.print('X');

#ifdef SECURE_ON_CONNCTION
    uBit.ble->gap().onConnection(connectionCallback);
#endif

    while (1) {
       uBit.sleep(1000);
    }
}
