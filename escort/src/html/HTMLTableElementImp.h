/*
 * Copyright 2011, 2012 Esrille Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ORG_W3C_DOM_BOOTSTRAP_HTMLTABLEELEMENTIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_HTMLTABLEELEMENTIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/html/HTMLTableElement.h>

#include <boost/intrusive_ptr.hpp>

#include <org/w3c/dom/html/HTMLTableCaptionElement.h>
#include <org/w3c/dom/html/HTMLTableRowElement.h>
#include <org/w3c/dom/html/HTMLTableSectionElement.h>

#include "HTMLCollectionImp.h"
#include "HTMLElementImp.h"

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{

class HTMLTableElementImp : public ObjectMixin<HTMLTableElementImp, HTMLElementImp>
{
    // HTMLCollection for rows
    class Rows : public HTMLCollectionImp
    {
        boost::intrusive_ptr<HTMLTableElementImp> table;
    public:
        Rows(HTMLTableElementImp* table);

        // HTMLCollection
        virtual unsigned int getLength();
        virtual Element item(unsigned int index);
        virtual Object namedItem(const std::u16string& name) {
            return 0;
        }
    };

public:
    HTMLTableElementImp(DocumentImp* ownerDocument) :
        ObjectMixin(ownerDocument, u"table")
    {}
    HTMLTableElementImp(HTMLTableElementImp* org, bool deep) :
        ObjectMixin(org, deep)
    {}

    virtual void eval();

    // Utilities for Rows
    unsigned int getRowCount();
    html::HTMLTableRowElement getRow(unsigned int index);

    // HTMLTableElement
    html::HTMLTableCaptionElement getCaption();
    void setCaption(html::HTMLTableCaptionElement caption);
    html::HTMLElement createCaption();
    void deleteCaption();
    html::HTMLTableSectionElement getTHead();
    void setTHead(html::HTMLTableSectionElement tHead);
    html::HTMLElement createTHead();
    void deleteTHead();
    html::HTMLTableSectionElement getTFoot();
    void setTFoot(html::HTMLTableSectionElement tFoot);
    html::HTMLElement createTFoot();
    void deleteTFoot();
    html::HTMLCollection getTBodies();
    html::HTMLElement createTBody();
    html::HTMLCollection getRows();
    html::HTMLElement insertRow();
    html::HTMLElement insertRow(int index);
    void deleteRow(int index);
    std::u16string getSummary();
    void setSummary(const std::u16string& summary);
    // HTMLTableElement-30
    std::u16string getAlign();
    void setAlign(const std::u16string& align);
    std::u16string getBgColor();
    void setBgColor(const std::u16string& bgColor);
    std::u16string getBorder();
    void setBorder(const std::u16string& border);
    std::u16string getCellPadding();
    void setCellPadding(const std::u16string& cellPadding);
    std::u16string getCellSpacing();
    void setCellSpacing(const std::u16string& cellSpacing);
    std::u16string getFrame();
    void setFrame(const std::u16string& frame);
    std::u16string getRules();
    void setRules(const std::u16string& rules);
    std::u16string getWidth();
    void setWidth(const std::u16string& width);
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv) {
        return html::HTMLTableElement::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData() {
        return html::HTMLTableElement::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_HTMLTABLEELEMENTIMP_H_INCLUDED
