#pragma once
#if !defined INC_CONSTANT
#define      INC_CONSTANT


class ProductID
{
public:
    enum {
    Hendrix = 0x611,
    DA45 = 0xDA45,
    BlueMax2 = 0x4254,
    BlueMax5 = 0x0715,
    BlueMax5OC = 0x0716,
    Bellringer = 0x0410,
    Neo = 0x620,
    Hydra = 0x411,
    HydraOC = 0x412,
    Pac40C620 = 0xAA00,
    Pac40C620M = 0xAA01,
    Pac40C610 = 0xAA02,
    Pac40C610M = 0xAA03,
    Pac40DA45 = 0xAA05,
    Pac40DA45M = 0xAA06,
    Pac40DA45S = 0xAA07,
    Pac40DA45SM = 0xAA08,
    Pac40DA40 = 0xAA09,
    Pac40Sicily = 0xAA10,
    Pac40SicilyM = 0xAA11,
    CanaryUC = 0xAA12,
    CanaryOC = 0xAA13,
    Pac40SicilyV2 = 0xAA14,
    Pac40SicilyV2M = 0xAA15,
	Entera610UC = 0xAA18,
	Entera620UC = 0xAA19,
	Entera610OC = 0xAA1A,
	Entera620OC = 0xAA1B,
	Yeti = 0xAB01,
    YetiOC = 0xAB11,
    Yeti2 = 0xAB02,
    Yeti2OC = 0xAB12,
    Poseidon = 0xAC01,
    PoseidonOC = 0xAC11,
    DoubloonDA70 = 0xAF00,
    DoubloonDA80 = 0xAF01,
    DoubloonDA90 = 0xAF02,
	DoubloonHW515 = 0xAF03,
	DoubloonHW525 = 0xAF04,
	DoubloonHW545 = 0xAF05,
	DoubloonHW715 = 0xAF06,
	DoubloonHW725 = 0xAF07,
	DoubloonHW535 = 0xAF09,
    CapriAna = 0xCA01,
    RTXR3 = 0xCA03,
    RTXR3UC = 0x417,
    RTXR3OC = 0x418,
    CapriAnaOC = 0xCA00,
    Delphi1 = 0x717,
    Delphi1OC = 0x718,
    Delphi2 = 0x413,
    Delphi2OC = 0x414,
    Delphi2A = 0x415,
    Delphi2AOC = 0x416,
    CheetahHS = 0x6,
    Athena2HS = 0x7,
    VoyagerProV2HS = 0x8,
    Latte = 0xAE11,
    LatteOC = 0xAE01,
    BlackMagicC310 = 0xC00E,
    BlackMagicC320 = 0xC00F,
    BlackMagicC310M = 0xC01E,
    BlackMagicC320M = 0xC01F,
	BlackMagic2C310  = 0xC022,
    BlackMagic2C310M = 0xC023,
    BlackMagic2C320  = 0xC024,
    BlackMagic2C320M = 0xC025,
    BlackPacificC510   = 0xC015,
    BlackPacificC510M  = 0xC016,
    BlackPacificC520   = 0xC017,
    BlackPacificC520M  = 0xC018,
	BlackPacificC520_NEW = 0xC035,
	BlackPacificC520M_NEW = 0xC036,
    BlackPacific2C510  = 0xC019,
    BlackPacific2C510M = 0xC01A,
    BlackPacific2C520  = 0xC01B,
    BlackPacific2C520M = 0xC01C,
    BluePacificC720 = 0x10A,
    BluePacificC720M = 0x10B,
    BluePacificC710 = 0x10C,
    BluePacificC710M = 0x10D,
    BluePacificC720_1 = 0x124,
    BluePacificC720M_1 = 0x125,
	BluePacificC720_2 = 0x129,
	BluePacificC720M_2 = 0x12A,
	BlackWireC220 = 0xC003,
    BlackWireC310 = 0xc038,
    BlackWireC320 = 0xc039,
    BlackWireC310_2 = 0xc03e,
    BlackWireC320_2 = 0xc03f,
    BlackWireC315 = 0xc04a,
    BlackWireC325 = 0xc04b,
	BlackWireC435 = 0xC032,
	BlackWireC435M = 0xC033,
	VoyagerLegend_STD = 0x0113,
	VoyagerLegend_VZW = 0x0114,
	VoyagerLegend_ROW = 0x0115,
    VoyagerLegend_CHN = 0x0122,
    VoyagerLegend_SWE = 0x0123,
	VoyagerPro_UC = 0x0106,
	VoyagerPro_STD = 0x0107,
	VoyagerPro_VZW = 0x0108,
	VoyagerPro_ROW = 0x0109,
	M1100_ORIG = 0x0006,
	M1100_VZW = 0x0100,
	M1100_ROW = 0x0101,
	M1100_US = 0x0104,
	M1100_BMW = 0x010E,
	Nirvana_US = 0x011A,
	Nirvana_UK = 0x011C,
    Nirvana_Blur_US = 0x0137,
    Nirvana_Blur_UK = 0x0138,
	Sportster_Superlow = 0xC02F,
	Prius = 0xC034,
	Cinnamon = 0xAE02,
	Cinnamon_DFU = 0xAEFF,
	Cydoemus2SPK = 0x2FA,
	Cydoemus2HS = 0x2FB,
	Cydoemus2 = 0x2FC,
	Cydoemus21SPK = 0x2F6,
	Cydoemus21HS = 0x2F7,
	Madone = 0x0127,
	Crystal = 0x0130,
	Crystal_Verizon = 0x0132,
	Crystal_China = 0x0133,
	Crystal_World = 0x0134,
	Crystal_India = 0x0135,
	MetisAPU72 = 0xAF0A,
	MetisAPU75 = 0xAF08,
	Cruzeiro = 0xC03D,
	BlackWire325_1 = 0xC03A,
	BlackWire315_1 = 0xC037,
    Emerald_117 = 0x0117,
    Emerald_118 = 0x0118,
    Emerald_119 = 0x0119,
    Emerald_11e = 0x011e,
    Emerald_11f = 0x011f,
    Emerald_120 = 0x0120,
    Emerald_121 = 0x0121,
    Emerald_12e = 0x012e,
    Sublime_11b = 0x011b,
    Sublime_11d = 0x011d,
    Virtual = 0xFFFF
    };
};

class LegacyUsage
{
public:
    enum {
    TelephoneUsagePage = 0xB,
    ConsumerUsagePage = 0xC,
    DefaultUsagePage = 0xFFA0,
    HID2UsagePage = 0xFFA2,
    NeoUsagePage = 0xFF52,
    LEDUsagePage = 0x8,

    Ring = 0x9E,
    RFLink = 0xA1,
    Talk = 0xB7,
    VolumeUp = 0xB1,
    VolumeDown = 0xB2,
    VolumeUpHeld = 0xB3,
    VolumeDownHeld = 0xB4,
    Mute = 0xB5,
    MuteHeld = 0xB6,
    SignOn = 0x01,
    Exclusive = 0x8F,
    Version = 0x09,

    //A2DP Usage
    Stereo = 0xB8,

    //AVRCP Usages
    Play = 0xB9,
    Pause = 0xBA,
    FastForward = 0xBB,
    Rewind = 0xBC,
    Next = 0xBD,
    Previous = 0xBE,
    Stop = 0xBF
    };
};

class StandardUsage : public LegacyUsage
{
public:
    enum Usg {
    Ring = 0x9E,
    RFLink = 0xA1,
    SignOn = 0x8D,

    //Base Events
    PstnTalk = 0x60,
    VoipTalk = 0x61,
    Subscribe = 0x62,
    PstnTalkHeld = 0x63,
    VoipTalkHeld = 0x64,
    SubscribeHeld = 0x65,
    PstnTalkAndSubscribeHeld = 0x66,
    PstnTalkAndVoipTalkHeld = 0x67,
    PstnInComingCall = 0xD1,
    PstnLinkState = 0xD3,
    VoipLinkState = 0xD4,

    //DSP Usages
    DSPSetting = 0xAA,

    //Call Mutting usages
    CallMuteState = 0x90,

    //Ring type
    PstnRingType = 0xC6,
    VoipRingType = 0xC7,
    RingTone = 0xC8, // Covers all RingTone(VOIP/PSTN/Mobile,
    OcRingType = 0xC9,
    ToneVolume = 0xC2,

    OutgoingCallLine = 0xC3,
    AudioSource = 0xC5,
    AudioBandwidth = 0xA2,
    Intellistand = 0xA3,
    OTASubscription = 0xA4,
    RFPowerMode = 0xA6,
    PstnToneControl = 0xA7,
    VoipToneControl = 0xA8,
    RFLinkType = 0xD5,
    PasswordState = 0x66,
    BatteryLevel = 0x80,
    HeadsetDockState = 0xD0,
    HeadsetsInConference = 0x81,
    HeadsetRange = 0x82,
    DeviceStateRequest = 0x89,
    BaseVersion = 0x84,
    RemoteVersion = 0x85,
    PICVersion = 0x86,
	TuningVersion = 0x8D,
    BaseVersionFeature = 0x10,
    HeadsetVersionFeature = 0x11,
    DeviceReady = 0xCF,
    PasswordProtected = 0x66,
    VoipRFLinkDown = 0xAE,
    VoipRFLinkUp = 0xAF,
    MuteChanged = 0x9C,
    SecondCallRing = 0x9F,

    //MOC usages
    MOCStateChanged = 0x8A,
    MOCHookChanged = 0x8B,
    MOCHookSwitch = 0xD2,
    MOCMuteSwitch = 0xDA,
    MOCFlashSwitch = 0xD9,

    MOCMute = 0x09,
    MOCHook = 0x17,
    MOCRing = 0x18,
    MOCSpeaker = 0x1E,
    MOCOnline = 0x2A,
    WindowsSpeaker = 0xF8,
    WindowsMicrophone = 0xF9,

    //DFU
    DFUAck = 0x88,
    DFUData = 0x30,
    CommunicationTest = 0xF3,
    DisableI2C = 0xF5,
    DeviceVersionRequest = 0xF2,
    DECTMode = 0xD6,

    //Mobile presence
    MobilePresence = 0x32,
    MobileStatus = 0x33,
	MobileConnection = 0x34,

    //Dial Tone and Audio sensing
    AudioSensing = 0xD7,
    MOCDialTone = 0xD8,
    MOCDialToneActive = 0x3A,
    VoipCallActive = 0xDC,

    //Delphi Usages
    HeadsetWearingState = 0x71,
    Alert = 0x91,
    BTPowerLevel = 0xA9,
    BTHeadsetPairing = 0x92,
    DeviceInterface = 0x93,
    DevicesConnected = 0x94,
    VolumeLevel = 0x87,
    HIDPipeData = 0x30,
    HIDPipeCommand = 0x31,
    ATDMute = 0x99,
    ATDVolumeLevel = 0x9A,
    ATDRejectCall = 0x9B,
    CorruptDevice = 0x98,
    BTCorruptDevice = 0x08,
    Wearable = 0x9C,
    Corded = 0x9D,
    AnswerOnDon = 0x70,
    CallHandOff = 0x83,
    SensorControl = 0x25,

    //Conexant Device
    ConexantDevice = 0xAB,

    //Poseidon Device
    MobileLinkState = 0xD2,
    MobileTalk = 0x6A,
    InterfaceHoldState = 0x21,
    VOIPHoldState = 0x22,
    PSTNHoldState = 0x23,
    MobileHoldState = 0x24,
    PSTNInterface = 0xAC,
    MobileInterface = 0xAD,
    PstnTalkAndMobileTalkHeld = 0x70,
    VoipTalkAndMobileTalkHeld = 0x72,
    EnableBTInterface = 0xCB,
    EnableBTAutoConnect = 0xCC,
    EnableBTVoiceCommand = 0xCD,
    MobileTalkHeld = 0x73,
    AudioLinkState = 0xA5,
    DefaultSetting = 0xDF,
    ACLPooling = 0x97,
    BTFWVersion = 0x91,
    AudioLocation = 0xC6,
    MobileTalkAndSubscribeHeld = 0x6B,
    VoipTalkAndSubscribeHeld = 0x6C,

    //Capri Device
    InterfaceMode = 0x55,
    SoftphoneID = 0x56,
    DialPad = 0x9D,
    DialPadKey = 0x9B,
    MOCReflection = 0x8C,
    EnableHIDPipeAck = 0xC9,
    EnableAdvancedCC = 0xCE,

    //MOC Conferencing
    MOCDeviceHook = 0xDE,

    //Lync support
    MOCHold = 0x20,
    LyncRunning = 0x3F,
    ISOOutActive = 0xF7,
    ISORumble = 0xF5,
    ISONull = 0xF6,
    ISOData = 0xF2,

    SecondaryDevice = 0x13,
    DockStateValid = 0xDF,
    LocalOCMute = 0xDB,
    DeskphoneHeadset = 0x6F,

    //ROME extended version
    RomeVersion = 0xE7,

    //LATTE MOC make call dialed key
    DialPadKeyOut = 0x9C,

    //REJECT
    Reject = 0xDD,

    // Poseidon II
    A2DPEnabled = 0x41,

	// Nirvana
    NirvanaLanguage = 0x45,
    NirvanaSCOStartTone = 0x26,
    NirvanaMuteInterval = 0x27,
    NirvanaMuteOffVoicePrompt = 0xc1,
    NirvanaAutoPauseMedia = 0x25,
    NirvanaDonDoffSensor = 0x72,
    EnterCsrDfu = 0x57,               // Output

	VolumeControlOrientationLeft = 0x42,
	VolumeControlOrientationRight = 0x43,

	//Civic Lite 2
	Redial = 0x5B,
	VoiceMuteAlert = 0x59, //Input
	LyncRedial = 0xDB,
    MuteTone= 0xAF,
	VolumeTone=0xAE,
	MuteReminder = 0x5A,
	VoiceMuteReminder=0x58,
	TimedMuteReminder=0x27,
	ModelID = 0x7D
};
};

class HID2Usage
{
public:
    enum {
    //HID Version
		HIDVersion = 0xCE,  //Feature

		//Audio Link usages
		AudioLinkChanged = 0xA0, //Input
		AudioLinkState = 0xA5,   //Feature

		//Interface Link usages
		BTLink = 0x50,   //Output/Feature/Input
		PSTNLink = 0x52, //Output/Feature/Input
		VOIPLink = 0x54,   //Output/Feature/Input   

		//Interface Hold/Resume usages
		VOIPHold = 0x22,   //Output/Feature/Input
		PSTNHold = 0x24,  //Output/Feature/Input
		BTHold = 0x26,    //Output/Feature/Input      

		//Ring usage
		Ring = 0x9E,  //Output

		//PSTN, Mobile(BT) Ring indication usages
		PSTNRing = 0xD1, //Input
		BTRing = 0xD9,   //Input

		//Button press usages
		BasePSTNTalk = 0x60,          //Input
		BaseVOIPTalk = 0x61,          //Input
		BaseBTTalk = 0x6A,           //Input
		DeskphoneHSTalk = 0x6F,      //Input
		PSTNAndVOIPTalkHeld = 0x67,  //Input
		PSTNAndBTTalkHeld = 0x70,   //Input
		USBTalkAndBTTalkHeld = 0x72,//Input
		HeadsetVolumeUP = 0xB1,     //Input
		HeadsetVolumeDOWN = 0xB2,      //Input
		HeadsetFlash = 0xB3,          //Input
		HeadsetMuteHeld = 0xB6,      //Input
		HeadsetTalk = 0xB7,          //Input

		//AVRCP usages
		AVRCPStereo = 0xB8,          //Input
		AVRCPPlay = 0xB9,              //Input
		AVRCPPause = 0xBA,          //Input
		AVRCPFFWD = 0xBB,              //Input
		AVRCPRewind = 0xBC,          //Input
		AVRCPNext = 0xBD,              //Input
		AVRCPPrevious = 0xBE,          //Input
		AVRCPStop = 0xBF,              //Input

		//Audio Mixer usage
		AudioMixerChanged = 0x90,      //Input

		//VOIP call active usage
		SoftphoneCallActive = 0xDC, //Output

		//Exclusive usage
		Exclusive = 0x8F,              //Input/Feature/Output
		DeviceReady = 0xCF,          //Feature

		//Factory Defaults Usage
		FactoryDefault = 0x7F,      //Input/Feature/Output

		//Mute usage
		HeadsetMute = 0xB5,          //Input/Feature/Output
		HeadsetMuteChanged = 0x9C,  //Input

		//Blade Runner HID Pipe usage
		BladeRunnerData = 0xBE,      //Input/Output

		//Windows Audio detection usages
		ISOOUTChanged = 0xF2,                //Input/Feature
		WindowsSpeakerChanged = 0xF8,        //Input/Feature
		WindowsMicrophoneChanged = 0xF2,    //Input/Feature

		//USB Hub usage
		PeripheralDeviceConnected = 0x13,    //Feature

		//Corrupt FW usage
		InvalidateFirmware = 0x98,        //Output

		// Emerald CSR DFU usages
		EnterCsrDfu = 0x97,               // Output
		EnterCsrDfuOld = 0x0a,             // Output
		CsrReset = 0x9b,                   // Output
		CsrDfuCopyRequired = 0x97,         // Feature
		CsrCopyStart = 0x9a,               // Output
		CsrDfuError = 0x96,                // Feature
		CsrEnterDfuFailure = 0x95,         // Input

		//Display device Dial pad
		DialPadKey = 0x9B,	//Input Value
		DialPad = 0x9D,		//Input/Output Value

		//Headset Docked
		HeadsetDocked = 0xD0, //Input/Feature
		AutoAnswer = 0xA2, //Input/Feature/Output

		//MOC usages
		MOCStateChanged = 0x8A, //Input
		MOCReflection = 0x8C,   //Input
		MOCHookSwitch = 0xD2,   //Output Value
		MOCFlashSwitch = 0xD3,  //Output
		MOCMuteSwitch = 0xD9,   //Output

		MOCMute = 0x09,		//Feature
		MOCHook = 0x17,		//Feature
		MOCRing = 0x18,		//Feature
		MOCSpeaker = 0x1E,	//Feature
		MOCHold = 0x20,		//Feature
		MOCOnline = 0x2A,	//Feature
		Wave14 = 0x3F,		//Feature

		DialPadOC = 0x9E,	//Input
		DialPadKeyOC = 0x9C, //Output Value

		MOCDialTone = 0xE2,	   //Input/Feature/Output Value

		//Call Reject
		Reject = 0xDD,		 //Input/Output
		//Call Redial
		LyncRedial = 0xDB,   //Output

		//Model ID
		ModelID = 0x7D,

		AudioSensing= 0xE0,
		OTASubscription = 0xA4,
		BTInterface = 0xCB,
		BTAutoConnect = 0xCC,
		BTACLPolling = 0x97,
		RFPowerMode = 0xA6,
		OutgoingCallLine = 0xC3,
			
		PSTNAudioBandwidth = 0x58,
		VOIPAudioBandwidth = 0x59,
		BTAudioBandwidth = 0x5A,
		PSTNRingToneType = 0xE3,
		VOIPRingToneType = 0xE4,		
		BTRingToneType = 0xE5,
		MuteToneType = 0xE6,	
		EarconToneVolume = 0x91,
		PSTNToneVolume = 0x92,
		VOIPToneVolume = 0x93,
		MuteToneVolume = 0x94,
		BTToneVolume = 0x99,	
		BTVoiceCommand = 0xCD,
		BTA2DP=0x41,

		//Following are TBD HID usages
		VOIPToneControl = 0xA8,
		PSTNToneControl = 0xA7,
		SecondCallRing = 0x9F		
    };
};

class TelephonyUsage
{
public:
    enum {
    Hook = 0x20,
    Mute = 0x2F,
    Speaker = 0x2b,

    Key1 = 0xb1,
    Key2 = 0xb2,
    Key3 = 0xb3,
    Key4 = 0xb4,
    Key5 = 0xb5,
    Key6 = 0xb6,
    Key7 = 0xb7,
    Key8 = 0xb8,
    Key9 = 0xb9,
    Key0 = 0xb0,
    KeyStar = 0xba,
    KeyPound = 0xbb
    };
};


#endif // !defined INC_CONSTANT
