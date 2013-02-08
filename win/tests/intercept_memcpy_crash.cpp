/* Copyright 2012 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This file is a part of AddressSanitizer, an address sanity checker.

#include "common.h"

int main(void) {
  volatile char buff1[6] = "Hello",
                buff2[5];
  memcpy(ident(buff2), ident(buff1), 6);

  UNREACHABLE();
// CHECK-NOT: This code should be unreachable

// CHECK: AddressSanitizer: stack-buffer-overflow on address [[ADDR:0x[0-9a-f]+]]
// CHECK: WRITE of size 6 at [[ADDR]] thread T0
// CHECK:   #0 {{.*}} __asan_report_error
// CHECK:   #1 {{.*}} wrap_memcpy
// CHECK:   #2 {{.*}} main
// CHECK: Address [[ADDR]] is located at offset {{.*}} in frame <main>
}
