#pragma once
#if !defined INC_PROCWATCHTYPES
#define      INC_PROCWATCHTYPES

#include <string>
typedef unsigned int ProcWatch_pid;

extern "C" {

    /// Notifications that Process Watcher provides
    enum ProcWatch_Ntf {
        /// Process started
        procwStarted,
        /// Process stopped
        procwStopped
    };

	struct ProcWatch_Args
	{
		ProcWatch_Ntf ntf;
		//name of the process
		const wchar_t* procName;
		//process id
		ProcWatch_pid pid;
		//process version
		const wchar_t* procVersion;
	};

    /** Callback by which the Process Watcher notifies users of process events. It's called on a Process Watcher's
    own thread.

    @param ntf The notification which is sent by Process Watcher
    @param procName The name of the process that notification is for. It is all lower-case (may be different
    than the name provided in #ProcWatch_Add).
    @param pid The Process IDentificator for the process that notification is for.
    */
    typedef void(*ProcWatch_CallBack)(ProcWatch_Args args);
	typedef void(*ProcWatch_Callback_All)(ProcWatch_Args args);
};


#endif // !defined INC_PROCWATCHTYPES
