/*
 * Copyright (c) 2006
 * Nintendo Co., Ltd.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Nintendo makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#define VERBOSE

#include <es.h>
#include "cpu.h"
#include "io.h"
#include "mps.h"

bool Mps::ConfigurationTableHeader::
accept(Visitor& visitor)
{
    u8* ptr = reinterpret_cast<u8*>(this);
    ptr += sizeof(ConfigurationTableHeader);
    bool cont = true;
    for (int i = 0; cont && i < entryCount; ++i)
    {
        switch (*ptr)
        {
        case PROCESSOR:
            cont = visitor.at(reinterpret_cast<Processor*>(ptr));
            ptr += sizeof(Processor);
            break;
        case BUS:
            cont = visitor.at(reinterpret_cast<Bus*>(ptr));
            ptr += sizeof(Bus);
            break;
        case IO_APIC:
            cont = visitor.at(reinterpret_cast<IOApic*>(ptr));
            ptr += sizeof(IOApic);
            break;
        case IO_INTERRUPT_ASSIGNMENT:
            cont = visitor.at(reinterpret_cast<InterruptAssignment*>(ptr));
            ptr += sizeof(InterruptAssignment);
            break;
        case LOCAL_INTERRUPT_ASSIGNMENT:
            cont = visitor.at(reinterpret_cast<LocalInterruptAssignment*>(ptr));
            ptr += sizeof(LocalInterruptAssignment);
            break;
        default:
            cont = false;
            break;
        }
    }
    return true;
}

Mps::FloatingPointerStructure* Mps::
lookup(void* base, int len)
{
#ifdef VERBOSE
    esReport("Mps::lookup() at %p, %u\n", base, len);
#endif
    u8* ptr = static_cast<u8*>(base);
    while (sizeof(FloatingPointerStructure) <= len--)
    {
        if (ptr[0] == '_' && ptr[1] == 'M' && ptr[2] == 'P' && ptr[3] == '_')
        {
            u8 sum = 0;
            for (int i = 0; i < 16; i++)
            {
                sum += ptr[i];
            }
            if (sum == 0)
            {
                return reinterpret_cast<FloatingPointerStructure*>(ptr);
            }
        }
        ++ptr;
    }
    return 0;
}

Mps::FloatingPointerStructure* Mps::
lookup()
{
    FloatingPointerStructure* fps;
    u16* ebda = reinterpret_cast<u16*>(0x40e);  // for EBDA segment

    if (*ebda)
    {
        // Lookup the first kilobyte of Extended BIOS Data Area.
        fps = lookup(reinterpret_cast<void*>(*ebda * 16), 1024);
        if (fps)
        {
            return fps;
        }
    }
    else
    {
        // Lookup the last kilobyte of system base memory.
        fps = lookup(reinterpret_cast<void*>(*reinterpret_cast<u16*>(0x413) * 1024), 1024);
        if (fps)
        {
            return fps;
        }
    }

    // Lookup the BIOS ROM address space between 0F0000h and 0FFFFFh.
    fps = lookup((void*) 0xf0000, 0x10000);
    if (fps)
    {
        return fps;
    }

    return 0;
}

Mps::
Mps() :
    fps(lookup()),
    cth(0)
{
    ASSERT(sizeof(FloatingPointerStructure) == 16);
    ASSERT(sizeof(ConfigurationTableHeader) == 44);
    ASSERT(sizeof(Processor) == 20);
    ASSERT(sizeof(Bus) == 8);
    ASSERT(sizeof(IOApic) == 8);
    ASSERT(sizeof(InterruptAssignment) == 8);
    ASSERT(sizeof(LocalInterruptAssignment) == 8);

    if (fps == 0)
    {
        return;
    }
#ifdef VERBOSE
    fps->print();
#endif

    cth = reinterpret_cast<ConfigurationTableHeader*>(fps->address);
    if (!cth)
    {
        processorCount = 2;
    }
    else
    {
        cth->accept(processorCount);
#ifdef VERBOSE
        cth->print();
        Printer printer;
        cth->accept(printer);
#endif
    }
    ASSERT(0 < processorCount);
#ifdef VERBOSE
    esReport("MPS %d.%d (%d processor%s)\n",
             1 + fps->specRev / 10, fps->specRev % 10,
             static_cast<int>(processorCount),
             (1 < processorCount) ? "s" : "");
#endif

    fps = reinterpret_cast<FloatingPointerStructure*>(0x80000000 |reinterpret_cast<unsigned long>(fps));
    if (cth)
    {
        cth = reinterpret_cast<ConfigurationTableHeader*>(0x80000000 |reinterpret_cast<unsigned long>(cth));
    }
}

volatile u32* Mps::
getInterruptAssignment(unsigned int irq, unsigned int bus, InterruptAssignment& assignment)
{
    if (cth == 0)
    {
        if (16 <= irq || irq == 2 || bus != 0)
        {
            return 0;
        }
        assignment.entryType = IO_INTERRUPT_ASSIGNMENT;
        assignment.type = 0;    // INT
        assignment.flags = 0;
        assignment.busID = 0;
        assignment.busIRQ = irq;
        assignment.apicID = 0;
        assignment.apicINTINn = (irq == 0) ? 2 : irq;
        return reinterpret_cast<u32*>(0xfec00000);
    }

    LookupAssignment entry(irq, bus);
    cth->accept(entry);
    if (!entry)
    {
        return 0;
    }

    LookupIoApic apic(entry->apicID);
    cth->accept(apic);
    if (!apic || !apic->isUsable())
    {
        return 0;
    }

    assignment = *entry;
    return reinterpret_cast<u32*>(apic->address);
}
