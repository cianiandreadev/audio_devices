
/* --------------------------------------------------------------------
 *
 *  GGGGGG  NN    N
 *  G       N N   N
 *  G  GGG  N  N  N - Netcom
 *  G    G  N   N N
 *  GGGGGG  N    NN
 *
 *  Copyright (c) 2016, GN-Netcom
 * -------------------------------------------------------------------- */

/**
 * @file Constants.h
 * @brief Various constants used in the application.
 */

#ifndef Constants_h
#define Constants_h

#define DEVICES_INFO_HELP_TXT @"To use this JabraNativeHid test application, you must first select a device from the device list. Then you can send commands to the device using the buttons below. Inputs are shown in the two listboxes under Input."
#define SCANNED_DEV_HELP_TXT  @"FirstScanDone\nDevices found:"
#define ALPHA_VALUE           1.0f
#define VIEW_CORNER_RADIUS    5.0
#define RGB_VALUE             0.94140625f
#define DEVICE_INITIAL_CNT    10
#define BTN_TXT_MUTE          @"Mute"
#define BTN_TXT_OFFHOOK       @"Off Hook"
#define BTN_TXT_RINGER        @"Ringer"
#define BTN_TXT_HOLD          @"On Hold"
#define BTN_TXT_ONLINE        @"Audio Link"
#define BTN_STATE_ON          @"(1)"
#define BTN_STATE_OFF         @"(0)"
#define SDK_INFO_TXT          @"SDK Version :"
#define SDK_DEFAULT_TXT       @"?"
#define FIRMWARE_VERSION_TXT  @"Firmware Version : %s"
#define SERIAL_NUMBER_TXT     @"Serial Number: %s"
#define TXT_BUFF_SIZE         80

//Translated data constants
#define UNDEFINED_TXT @"Undefined"
#define OFFHOOK_TXT @"Off Hook"
#define MUTE_TXT @"Mute"
#define FLASH_TXT @"Flash"
#define REDIAL_TXT @"Redial"
#define KEY0_TXT @"Key0"
#define KEY1_TXT @"Key1"
#define KEY2_TXT @"Key2"
#define KEY3_TXT @"Key3"
#define KEY4_TXT @"Key4"
#define KEY5_TXT @"Key5"
#define KEY6_TXT @"Key6"
#define KEY7_TXT @"Key7"
#define KEY8_TXT @"Key8"
#define KEY9_TXT @"Key9"
#define KEYSTAR_TXT @"Key*"
#define KEYPOUND_TXT @"Key#"
#define KEYCLEAR_TXT @"KeyClear"

//Pre defined states to test Jabra device
enum JabraDevice_States
{
    OFFHOOK = 1,
    RINGER,
    MUTE,
    HOLD,
    ONLINE,
    BATTERYINFO,
};

//Pre defined states to test Jabra callback states
enum JabraLib_CallbackStates
{
    DEVICE_ATTACH = 0,
    DEVICE_DETACH,
    DEVICE_SCAN_DONE,
    UPDATE_RAW_HID,
    UPDATE_TRANSLATED_HID
};

#endif /* Constants_h */
