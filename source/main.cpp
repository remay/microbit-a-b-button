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

void onButtonAClick(MicroBitEvent) {   
    uBit.display.print('A');  
}

void onButtonBClick(MicroBitEvent) {   
    uBit.display.print('B');  
}

void app_main() {
    uBit.MessageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonAClick);
    uBit.MessageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonBClick);
    uBit.display.print('X');

    while (1) {
       uBit.sleep(1000);
    }
}
