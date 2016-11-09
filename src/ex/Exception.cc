/*
 * Copyright (c) 2012-2016, Nic McDonald
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * - Neither the name of prim nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "ex/Exception.h"

#include <cassert>
#include <cstdio>

namespace ex {

namespace {

std::string vstrprintf(const char* _format, va_list _args) {
  // make a copy of the args
  va_list args2;
  va_copy(args2, _args);

  // get the size of the output
  int size = vsnprintf(nullptr, 0, _format, _args);
  size++;  // null char

  // create a buffer large enough
  char* buffer = new char[size];

  // printf into the buffer
  int size2 = vsnprintf(buffer, (size_t)size,  _format, args2);
  assert((size2 + 1) >= size);

  // create a string
  std::string str(buffer);

  // clean up buffer
  delete[] buffer;

  // return the string
  return str;
}

}  // namespace

Exception::Exception(const char* _format, ...) {
  va_list args;
  va_start(args, _format);
  msg_ = vstrprintf(_format, args);
  va_end(args);
}

Exception::~Exception() {}

const char* Exception::what() const noexcept {
  return msg_.c_str();
}

}  // namespace ex
