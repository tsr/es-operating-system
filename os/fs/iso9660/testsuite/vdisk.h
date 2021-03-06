/*
 * Copyright 2008, 2009 Google Inc.
 * Copyright 2006 Nintendo Co., Ltd.
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

#include <es/object.h>

int esInit(Object** nameSpace);

#ifndef __es__

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <es.h>
#include <es/ref.h>
#include <es/endian.h>
#include <es/base/IStream.h>
#include <es/device/IDisk.h>

class VDisk : public es::Disk
{
    struct Geometry
    {
        unsigned int heads;
        unsigned int cylinders;
        unsigned int sectorsPerTrack;
        unsigned int bytesPerSector;
        long long diskSize;
    };

    Ref      ref;
    int      fd;
    Geometry geometry;

public:
    VDisk(char* vdisk)
    {
        geometry.cylinders = 0;
        geometry.heads = 0;
        geometry.sectorsPerTrack = 0;
        geometry.bytesPerSector = 0;
        geometry.diskSize = 0;

        fd = open(vdisk, O_RDWR);
        if (fd < 0)
        {
            fd = open(vdisk, O_RDWR | O_CREAT, 0777);
            if (fd < 0)
            {
                esThrow(ENOSPC);
            }
            setSize(512 * 2880);
        }
        long long size;
        size = getSize();
        if (size <= 512 * 2880 * 2)
        {
            switch (size / 512)
            {
            case 2880:  // 3-1/2 2HD
                geometry.cylinders = 80;
                geometry.heads = 2;
                geometry.sectorsPerTrack = 18;
                geometry.bytesPerSector = 512;
                geometry.diskSize = size;
                break;
            case 1440:  // 3-1/2 2DD
                geometry.cylinders = 80;
                geometry.heads = 2;
                geometry.sectorsPerTrack = 9;
                geometry.bytesPerSector = 512;
                geometry.diskSize = size;
                break;
            default:
                geometry.cylinders = 0;
                geometry.heads = 0;
                geometry.sectorsPerTrack = 0;
                geometry.bytesPerSector = 512;
                geometry.diskSize = size;
                break;
            }
        }
        else
        {
            // VPC 2004 vhd format
            u8 chs[4];
            read(chs, 4, size + 0x38);
            geometry.cylinders = BigEndian::word(chs + 0);
            geometry.heads = BigEndian::byte(chs + 2);
            geometry.sectorsPerTrack = BigEndian::byte(chs + 3);
            geometry.bytesPerSector = 512;
            geometry.diskSize = size;
            setPosition(0);
        }
        esReport("CHS: %u %u %u\n",
                 geometry.cylinders, geometry.heads, geometry.sectorsPerTrack);
    }

    ~VDisk()
    {
        close(fd);
    }

    //
    // es::Stream
    //

    long long getPosition()
    {
        int err;
        long long pos;
        pos = lseek(fd, 0, SEEK_CUR);
        if (pos < 0)
        {
            esThrow(errno);
        }
        return pos;
    }

    void setPosition(long long pos)
    {
        int err;

        if (geometry.diskSize && (pos % 512))
        {
            esThrow(EINVAL);
        }

        err = lseek(fd, pos, SEEK_SET);
        if (err < 0)
        {
            esThrow(errno);
        }
    }

    long long getSize()
    {
        long long tmp;
        tmp = getPosition();
        lseek(fd, 0, SEEK_END);
        long long size;
        size = getPosition();
        setPosition(tmp);
        if (512 * 2880 * 2 < size)
        {
            // .vhd
            size -= 512;
        }
        return size;
    }

    void setSize(long long size)
    {
        int err;

        err = ftruncate(fd, size);
        if (err)
        {
            esThrow(errno);
        }
    }

    int read(void* buffer, int size)
    {
        esThrow(EINVAL);

        size_t n = ::read(fd, buffer, size);
        return (int) n;
    }

    int read(void* buffer, int size, long long offset)
    {
#ifdef VERBOSE
        esReport("vdisk::read %ld byte at 0x%llx to %p.\n", size, offset, buffer);
#endif
        setPosition(offset);
        size_t n = ::read(fd, buffer, size);
        return (int) n;
    }

    int write(const void* buffer, int size)
    {
        esThrow(EINVAL);

        size_t n = ::write(fd, buffer, size);
        return (int) n;
    }

    int write(const void* buffer, int size, long long offset)
    {
#ifdef VERBOSE
        esReport("vdisk::write %ld byte at 0x%llx from %p.\n", size, offset, buffer);
#endif
        setPosition(offset);
        size_t n = ::write(fd, buffer, size);
        return (int) n;
    }

    void flush()
    {
    }

    //
    // es::Disk
    //

    unsigned int getHeads()
    {
        return geometry.heads;
    }
    unsigned int getCylinders()
    {
        return geometry.cylinders;
    }
    unsigned int getSectorsPerTrack()
    {
        return geometry.sectorsPerTrack;
    }
    unsigned int getBytesPerSector()
    {
        return geometry.bytesPerSector;
    }
    long long getDiskSize()
    {
        return geometry.diskSize;
    }

    //
    // Object
    //

    Object* queryInterface(const char* riid)
    {
        Object* objectPtr;
        if (strcmp(riid, es::Stream::iid()) == 0)
        {
            objectPtr = static_cast<es::Stream*>(this);
        }
        else if (strcmp(riid, es::Disk::iid()) == 0)
        {
            objectPtr = static_cast<es::Disk*>(this);
        }
        else if (strcmp(riid, Object::iid()) == 0)
        {
            objectPtr = static_cast<es::Stream*>(this);
        }
        else
        {
            return NULL;
        }
        objectPtr->addRef();
        return objectPtr;
    }

    unsigned int addRef()
    {
        return ref.addRef();
    }

    unsigned int release()
    {
        unsigned int count = ref.release();
        if (count == 0)
        {
            delete this;
            return 0;
        }
        return count;
    }
};

#endif  // __es__
