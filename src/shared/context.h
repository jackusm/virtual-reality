//
// MIT License
//
// Copyright (c) 2019 Rokas Kupstys
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
#pragma once

#include <winsock2.h>
#include <time.h>
#include <stl/unordered_map.h>
#include <stl/string.h>
#include <tiny-json.h>
#include "xorstr.hpp"
#include "vr-config.h"

struct context
{
    time_t payload_last_timestamp = time(nullptr);
    stl::string trusted_source;
    stl::string imgur_client_id;
    stl::string imgur_tag;
    stl::string vr_config;
    int imgur_tag_query_time;           // Minutes
    int imgur_tag_query_time_jitter;    // Minutes
    json_t pool[128];
    const json_t* root;

    context()
    {
        vr_config = xorstr_(VR_CONFIG);
        root = json_create(&vr_config.at(0), pool, 128);
    }

    stl::string get_prop_string(const char* prop_name) const
    {
        if (const json_t * prop = json_getProperty(root, prop_name))
        {
            if (prop->type == JSON_TEXT)
                return prop->u.value;
        }
        return "";
    }

    int64_t get_prop_number(const char* prop_name) const
    {
        if (const json_t * prop = json_getProperty(root, prop_name))
        {
            if (prop->type == JSON_INTEGER)
                return atoll(prop->u.value);
            if (prop->type == JSON_TEXT && strncmp(prop->u.value, "0x", 2) == 0)
            {
                char* end = nullptr;
                return strtoull(prop->u.value, &end, 16);
            }
        }
        return 0;
    }
};
