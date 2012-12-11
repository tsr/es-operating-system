// Generated by esidl 0.2.1.
// This file is expected to be modified for the Web IDL interface
// implementation.  Permission to use, copy, modify and distribute
// this file in any software license is hereby granted.

#ifndef ORG_W3C_DOM_BOOTSTRAP_TREEWALKERIMP_H_INCLUDED
#define ORG_W3C_DOM_BOOTSTRAP_TREEWALKERIMP_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <org/w3c/dom/traversal/TreeWalker.h>

#include <org/w3c/dom/traversal/NodeFilter.h>
#include <org/w3c/dom/DOMException.h>
#include <org/w3c/dom/Node.h>

namespace org
{
namespace w3c
{
namespace dom
{
namespace bootstrap
{
class TreeWalkerImp : public ObjectMixin<TreeWalkerImp>
{
public:
    // TreeWalker
    Node getRoot();
    unsigned int getWhatToShow();
    traversal::NodeFilter getFilter();
    bool getExpandEntityReferences();
    Node getCurrentNode();
    void setCurrentNode(Node currentNode) throw(DOMException);
    Node parentNode();
    Node firstChild();
    Node lastChild();
    Node previousSibling();
    Node nextSibling();
    Node previousNode();
    Node nextNode();
    // Object
    virtual Any message_(uint32_t selector, const char* id, int argc, Any* argv)
    {
        return traversal::TreeWalker::dispatch(this, selector, id, argc, argv);
    }
    static const char* const getMetaData()
    {
        return traversal::TreeWalker::getMetaData();
    }
};

}
}
}
}

#endif  // ORG_W3C_DOM_BOOTSTRAP_TREEWALKERIMP_H_INCLUDED
