#pragma once
#ifndef SPOKESENUMS
#define SPOKESENUMS

typedef enum 
{
    SESSIONMANAGER_OPT_UNKNOWN = 0,
    SESSIONMANAGER_SUPPRESS_DIALTONE = 1,
	SESSIONMANAGER_LOAD_PLUGINS = 2
} eSessionMgrOption;

typedef enum 
{
    SESSION_OPT_UNKNOWN = 0

} eSessionOption;

typedef enum 
{
    DEVICE_EVENT_KIND_DOCKED = 1,
    DEVICE_EVENT_KIND_UNDOCKED = 2,
    DEVICE_EVENT_KIND_TALKPRESS = 3,
    DEVICE_EVENT_KIND_UNKNOWN = 4,
    DEVICE_EVENT_KIND_NO_DEVICE = 5,
	DEVICE_EVENT_KIND_BASEPRESS = 6,
	DEVICE_EVENT_KIND_IDLE_TALKPRESS = 7
} eDeviceEventKind;


typedef enum RingTone
{
    RING_TONE_UNKNOWN = 0,
} eRingTone;

typedef enum 
{
    AUDIO_ROUTE_TO_HEADSET = 0,
    AUDIO_ROUTE_TO_SPEAKER = 1
} eAudioRoute;

typedef enum
{
    CALL_STATE_UNKNOWN = 0,
    CALL_STATE_ACCEPT_CALL = 1,
    CALL_STATE_TERMINATE_CALL = 2,
    CALL_STATE_HOLD_CALL = 3,
    CALL_STATE_RESUME_CALL = 4,
    CALL_STATE_FLASH = 5,
    CALL_STATE_CALL_IN_PROGRESS = 6,
    CALL_STATE_CALL_RINGING = 7,
    CALL_STATE_CALL_ENDED = 8,
    CALL_STATE_TRANSFER_TO_HEADSET = 9,
    CALL_STATE_TRANSFER_TO_SPEAKER = 10,
    CALL_STATE_MUTEON = 11,
    CALL_STATE_MUTEOFF = 12,
    CALL_STATE_MOBILE_CALL_RINGING= 13,
    CALL_STATE_MOBILE_CALL_IN_PROGRESS = 14,
    CALL_STATE_MOBILE_CALL_ENDED = 15,
    CALL_STATE_DON = 16,
    CALL_STATE_DOFF = 17,
    CALL_STATE_CALL_IDLE = 18,
    CALL_STATE_PLAY = 19,
    CALL_STATE_PAUSE = 20,
    CALL_STATE_STOP = 21,
    CALL_STATE_DTMF_KEY = 22,
    CALL_STATE_REJECT_CALL = 23,
	CALL_STATE_MAKE_CALL = 24, // Information only.  
	CALL_STATE_HOOK = 25,
	CALL_STATE_HOOK_IDLE = 26,
	CALL_STATE_HOOK_DOCKED = 27,
	CALL_STATE_HOOK_UNDOCKED = 28,
	CALL_STATE_BASE_EVENT = 29,
    CALL_STATE_CALL_ANSWERED_AND_ENDED = 30,
    CALL_STATE_CALL_UNANSWERED_AND_ENDED = 31,
    CALL_STATE_DEVICE_CHANGE = 32,
    CALL_STATE_DEVICE_ARRIVED = 33
} eCallState;

typedef enum PluginState
{
	PLUGIN_RUNNING = 1,
	PLUGIN_ACTIVE = 2,
	PLUGIN_USER_SIGNIN = 3,
	PLUGIN_USER_SIGNOUT = 4,
	PLUGIN_NOT_ACTIVE = 5
} ePluginState;


#endif