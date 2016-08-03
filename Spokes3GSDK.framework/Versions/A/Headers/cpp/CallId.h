#pragma once

#include "Spokes3G.h"

namespace Plantronics
{
    // constants 
    class CallID : public ICall
    {
        private:
            int32_t ID;
            int32_t ConferenceID;
            bool  InConference;
        public:
            void operator delete(void *p) { ::operator delete(p); }

            virtual ~CallID() {}
            explicit CallID(int32_t id) : ID(id), ConferenceID(0), InConference(false) {}
            explicit CallID(pCall call)
            : ID(-1), ConferenceID(0), InConference(false)
            { 
                if(call != nullptr)
                {
                    ID = call->getID();
                    ConferenceID = call->getConferenceID();
                    InConference = call->getInConference();
                }
            }
            int32_t getID(){ return ID; }
            void setID(int32_t id) { ID = id; }
            int32_t getConferenceID() { return ConferenceID; }
            void setConferenceID(int32_t id) { ConferenceID = id; }
            bool getInConference(){ return InConference; }
            void setInConference(bool bConference){ InConference = bConference; }
    };

    typedef std::shared_ptr<CallID> ptCallID;

    class CallIDExt : public CallID
    {
        private:
            ICall * _call;
        public:
            virtual ~CallIDExt() {_call = nullptr;}
            CallIDExt(pCall call) : CallID(call)
            {
                _call = call;
            }
			CallIDExt(int32_t id) : CallID(id) {}
            ICall *getCall() { return _call; }
    };
}
