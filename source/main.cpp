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

const MicroBitImage play_img ("0,1,0,0,0\n0,1,1,0,0\n0,1,1,1,0\n0,1,1,0,0\n0,1,0,0,0\n");
const MicroBitImage pause_img("0,0,0,0,0\n0,1,0,1,0\n0,1,0,1,0\n0,1,0,1,0\n0,0,0,0,0\n");

#define SCREEN_STATE_UNKNOWN 0
#define SCREEN_LOGO_UP       1
#define SCREEN_LOGO_DOWN     2
#define SCREEN_SCREEN_UP     3
int screen_state = SCREEN_STATE_UNKNOWN;

void onPlayPauseEvent(MicroBitEvent evt) {   
    if(evt.value == 0x0001 ) {
	uBit.display.print(play_img,0,0,0,0);
    }
    else if(evt.value == 0x0002 ) {
	uBit.display.print(pause_img,0,0,0,0);
    }
    else {
        uBit.display.print('?');
    }
}

void detect_screen() {
    // Detects if the logo up/down orientation has changed and raises events.
    int  accx        = uBit.accelerometer.getX();
    int  accy        = uBit.accelerometer.getY();
    int  accz        = uBit.accelerometer.getZ();
    bool is_vertical = (abs(accx) + abs(accz)) < 500;
    bool is_flat     = (abs(accx) + abs(accy)) < 500;

    if      ((accy >  500) && is_vertical && (screen_state != SCREEN_LOGO_UP)){
        screen_state = SCREEN_LOGO_UP;
        // send logo up event
        MicroBitEvent evt(MICROBIT_ID_ACCELEROMETER, 0x1001);
    }
    else if ((accy < -500) && is_vertical && (screen_state != SCREEN_LOGO_DOWN)){
        screen_state = SCREEN_LOGO_DOWN;
        // send logo down event
        MicroBitEvent evt(MICROBIT_ID_ACCELEROMETER, 0x1002);
    }
    else if ((accz < -500) && is_flat && (screen_state != SCREEN_SCREEN_UP)){
        screen_state = SCREEN_SCREEN_UP;
    }
    else {
        // other state, reset state engine
        //screen_state = SCREEN_STATE_UNKNOWN;
    }
}

void app_main() {
    uBit.MessageBus.listen(MES_REMOTE_CONTROL_ID, MICROBIT_EVT_ANY, onPlayPauseEvent);
    uBit.display.print('X');

    while (1) {
       detect_screen();
       uBit.sleep(50);
    }
}
