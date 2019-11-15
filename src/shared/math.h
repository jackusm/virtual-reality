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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint64_t deterministic_uuid_seed;

int random(int min, int max);
uint64_t get_machine_hash();
void deterministic_uuid(uint64_t seed, char uuid[44]);
HANDLE mutex_lock(uint64_t seed);
BOOL mutex_is_locked(uint64_t seed);
int64_t combine_hash(int64_t result, int64_t hash);
uint32_t fnv32a(const void* data, int len);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <stl/string.h>
stl::string deterministic_uuid(uint64_t seed);
#endif
