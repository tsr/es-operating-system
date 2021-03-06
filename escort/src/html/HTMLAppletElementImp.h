// Generated by esidl 0.2.1.
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_HTMLAPPLETELEMENTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_HTMLAPPLETELEMENTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/HTMLAppletElement.h>
#include "HTMLElementImp.h"

#include <org/w3c/dom/html/HTMLElement.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class HTMLAppletElementImp : public ObjectMixin<HTMLAppletElementImp, HTMLElementImp>
{
public:
    // HTMLAppletElement
    std::u16string getAlign();
    void setAlign(const std::u16string& align);
    std::u16string getAlt();
    void setAlt(const std::u16string& alt);
    std::u16string getArchive();
    void setArchive(const std::u16string& archive);
    std::u16string getCode();
    void setCode(const std::u16string& code);
    std::u16string getCodeBase();
    void setCodeBase(const std::u16string& codeBase);
    std::u16string getHeight();
    void setHeight(const std::u16string& height);
    unsigned int getHspace();
    void setHspace(unsigned int hspace);
    std::u16string getName();
    void setName(const std::u16string& name);
    std::u16string getObject();
    void setObject(const std::u16string& object);
    unsigned int getVspace();
    void setVspace(unsigned int vspace);
    std::u16string getWidth();
    void setWidth(const std::u16string& width);
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return html::HTMLAppletElement::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return html::HTMLAppletElement::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_HTMLAPPLETELEMENTIMP_H_INCLUDED
