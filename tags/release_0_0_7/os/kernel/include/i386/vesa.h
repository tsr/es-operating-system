/*
 * Copyright (c) 2006, 2007
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

#ifndef NINTENDO_ES_KERNEL_I386_VESA_H_INCLUDED
#define NINTENDO_ES_KERNEL_I386_VESA_H_INCLUDED

#include <es/interlocked.h>
#include <es/ref.h>
#include <es/types.h>
#include <es/base/IStream.h>
#include <es/base/IPageable.h>
#include <es/device/ICursor.h>

class Vesa : public IStream, public ICursor, public IPageable
{
    // VESA SuperVGA information block
    enum VbeInfoBlock
    {
        VESASignature = 0,      // 'VESA' 4 byte signature
        VESAVersion = 4,        // VBE version number
        OEMStringPtr = 6,       // Pointer to OEM string
        Capabilities = 10,      // Capabilities of video card
        VideoModePtr = 14,      // Pointer to supported modes
        TotalMemory = 18,       // Number of 64kb memory blocks

        // VBE 2.0
        OemSoftwareRev = 20,    // VBE implementation Software revision
        OemVendorNamePtr = 22,  // VbeFarPtr to Vendor Name String
        OemProductNamePtr = 26, // VbeFarPtr to Product Name String
        OemProductRevPtr = 30   // VbeFarPtr to Product Revision String
    };

    // VESA SuperVGA mode information block
    enum ModeInfoBlock
    {
        ModeAttributes = 0,     // Mode attributes
        WinAAttributes = 2,     // Window A attributes
        WinBAttributes = 3,     // Window B attributes
        WinGranularity = 4,     // Window granularity in k
        WinSize = 6,            // Window size in k
        WinASegment = 8,        // Window A segment
        WinBSegment = 10,       // Window B segment
        WinFuncPtr = 12,        // Pointer to window function
        BytesPerScanLine = 16,  // Bytes per scanline
        XResolution = 18,       // Horizontal resolution
        YResolution = 20,       // Vertical resolution
        XCharSize = 22,         // Character cell width
        YCharSize,              // Character cell height
        NumberOfPlanes,         // Number of memory planes
        BitsPerPixel,           // Bits per pixel
        NumberOfBanks,          // Number of CGA style banks
        MemoryModel,            // Memory model type
        BankSize,               // Size of CGA style banks
        NumberOfImagePages,     // Number of images pages

        RedMaskSize = 31,       // Size of direct color red mask
        RedFieldPosition,       // Bit posn of lsb of red mask
        GreenMaskSize,          // Size of direct color green mask
        GreenFieldPosition,     // Bit posn of lsb of green mask
        BlueMaskSize,           // Size of direct color blue mask
        BlueFieldPosition,      // Bit posn of lsb of blue mask
        RsvdMaskSize,           // Size of direct color res mask
        RsvdFieldPosition,      // Bit posn of lsb of res mask
        DirectColorModeInfo,    // Direct color mode attributes

        // VBE 2.0
        PhysBasePtr = 40        // Physical address for flat memory frame buffer
    };

    Ref     ref;
    u8*     vbeInfoBlock;
    u8*     modeInfoBlock;
    u8*     font;

    u16     xResolution;
    u16     yResolution;
    u8      bitsPerPixel;
    u8      redFieldPosition;
    u8      greenFieldPosition;
    u8      blueFieldPosition;
    u8*     physBasePtr;
    long    size;

    // mouse cursor
    Interlocked count;
    static u32  data[32];
    static u32  mask[32];
    static u16  xHotSpot;
    static u16  yHotSpot;
    u16         xPosition;
    u16         yPosition;
    u32         background[32][32];

    void saveBackground();
    void restoreBackground();
    void drawCursor();

public:
    Vesa(u8* vbeInfoBlock, u8* modeInfoBlock, u8* font,
         IContext* device);

    // IStream
    long long getPosition();
    void setPosition(long long pos);
    long long getSize();
    void setSize(long long size);
    int read(void* dst, int count);
    int read(void* dst, int count, long long offset);
    int write(const void* src, int count);
    int write(const void* src, int count, long long offset);
    void flush();

    // ICursor
    int show();
    int hide();
    void move(int dx, int dy);
    void getPosition(int& x, int& y);
    void setPosition(int x, int y);
    void setPattern(const u32 data[32], const u32 mask[32], u16 xHotSpot, u16 yHotSpot);

    // IPageable
    unsigned long long get(long long offset);
    void put(long long offset, unsigned long long pte);

    // IInterface
    bool queryInterface(const Guid& riid, void** objectPtr);
    unsigned int addRef(void);
    unsigned int release(void);
};

#endif // NINTENDO_ES_KERNEL_I386_VESA_H_INCLUDED