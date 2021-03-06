/*
 * Copyright 2008 Google Inc.
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

#ifndef __WIN32__

#include <ctype.h>
#include <string.h>
#include "core.h"

size_t strnlen(const char *s, const size_t n)
{
    int i;
    const char* t;

    for (i = 0, t = s; i < n && *t != '\0'; ++i, ++t)
    {

    }
    return (size_t) (t - s);
}

int stricmp(const char *s1, const char *s2)
{
    char c1;
    char c2;

    for (;;)
    {
        c1 = (char) (tolower)(*s1++);
        c2 = (char) (tolower)(*s2++);
        if (c1 < c2)
        {
            return -1;
        }
        if (c1 > c2)
        {
            return 1;
        }
        if (c1 == '\0')
        {
            return 0;
        }
    }
    return 0;
}

int strnicmp(const char *s1, const char *s2, size_t n)
{
    int i;
    char c1;
    char c2;

    for (i = 0; i < n; ++i)
    {
        c1 = (char) (tolower)(*s1++);
        c2 = (char) (tolower)(*s2++);
        if (c1 < c2)
        {
            return -1;
        }
        if (c1 > c2)
        {
            return 1;
        }
        if (c1 == '\0')
        {
            return 0;
        }
    }
    return 0;
}

#endif // __WIN32__
