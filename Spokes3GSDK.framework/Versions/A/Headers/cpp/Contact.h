#pragma once
#if !defined INC_CM_CONTACT
#define      INC_CM_CONTACT


#include "Spokes3G.h"
#include <string>
#include <memory>
#include <cassert>


namespace Plantronics
{
    /*! The default implementation of an IContact - supporting class.
        User can implement another as long as it conforms to the IContact
        interface specification.
        */
    class Contact : public IContact
    {
    private:
        int32_t _Id;
        std::wstring _Name;
        std::wstring _FriendlyName;
        std::wstring _sipURI;
        std::wstring _eMail;
        std::wstring _Phone;
        std::wstring _WorkPhone;
        std::wstring _MobilePhone;
        std::wstring _HomePhone;

    public:
        Contact() : _Id(0) {}

        explicit Contact(pContact contact) : _Id(0) {
            assert(contact != nullptr);
            setName(contact->getName());
            _Id = contact->getID();
            setFriendlyName(contact->getFriendlyName());
            setSipUri(contact->getSipUri());
            setEmail(contact->getEmail());
            setPhone(contact->getPhone());
            setWorkPhone(contact->getWorkPhone());
            setMobilePhone(contact->getMobilePhone());
            setHomePhone(contact->getHomePhone());
        }

        Contact(Contact const &c) {
            setName(c.getName());
            _Id = c.getID();
            setFriendlyName(c.getFriendlyName());
            setSipUri(c.getSipUri());
            setEmail(c.getEmail());
            setPhone(c.getPhone());
            setWorkPhone(c.getWorkPhone());
            setMobilePhone(c.getMobilePhone());
            setHomePhone(c.getHomePhone());
        }

        Contact(ContactData const &cd) {
            setEmail(cd.email);
            setFriendlyName(cd.friendlyName);
            setHomePhone(cd.homePhone);
            setID(cd.id);
            setMobilePhone(cd.mobilePhone);
            setName(cd.name);
            setPhone(cd.phone);
            setSipUri(cd.sipUri);
            setWorkPhone(cd.workPhone);
        }

        virtual ~Contact() {}

        void operator delete(void *p) {
            ::operator delete(p);
        }

        const wchar_t* getName() const {
            return _Name.c_str();
        }
        void setName(const wchar_t* pName) {
            _Name.assign(pName ? pName : L"");
        }
        const wchar_t* getFriendlyName() const {
            return _FriendlyName.c_str();
        }
        void setFriendlyName(const wchar_t* pFName) {
            _FriendlyName.assign(pFName ? pFName : L"");
        }
        int32_t getID() const {
            return _Id;
        }
        void setID(int32_t id) {
            _Id = id;
        }
        const wchar_t* getSipUri() const {
            return _sipURI.c_str();
        }
        void setSipUri(const wchar_t* pSip) {
            _sipURI.assign(pSip ? pSip : L"");
        }
        const wchar_t* getPhone() const {
            return _Phone.c_str();
        }
        void setPhone(const wchar_t* pPhone) {
            _Phone.assign(pPhone ? pPhone : L"");
        }
        const wchar_t* getEmail() const {
            return _eMail.c_str();
        }
        void setEmail(const wchar_t* pEmail) {
            _eMail.assign(pEmail ? pEmail : L"");
        }
        const wchar_t* getWorkPhone() const {
            return _WorkPhone.c_str();
        }
        void setWorkPhone(const wchar_t* pWPhone) {
            _WorkPhone.assign(pWPhone ? pWPhone : L"");
        }
        const wchar_t* getMobilePhone() const {
            return _MobilePhone.c_str();
        }
        void setMobilePhone(const wchar_t* pMPhone) {
            _MobilePhone.assign(pMPhone ? pMPhone : L"");
        }
        const wchar_t* getHomePhone() const {
            return _HomePhone.c_str();
        }
        void setHomePhone(const wchar_t* pHPhone) {
            _HomePhone.assign(pHPhone ? pHPhone : L"");
        }
    };

    inline ::std::unique_ptr<Contact> makeContact(ContactData const &cd) {
        return ::std::unique_ptr<Contact>(new Contact(cd));
    }
}

#endif // !defined INC_CM_CONTACT
