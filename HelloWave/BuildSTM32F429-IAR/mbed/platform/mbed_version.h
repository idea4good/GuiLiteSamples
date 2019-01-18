
/** \addtogroup platform */
/** @{*/
/**
 * \defgroup platform_version Version macros
 * @{
 */
/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
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

#ifndef MBED_VERSION_H
#define MBED_VERSION_H

#define MBED_LIBRARY_VERSION 164

/** MBED_MAJOR_VERSION
  * Mbed 2 major version
  */
#define MBED_MAJOR_VERSION 2

/** MBED_MINOR_VERSION
  * Mbed 2 minor version
  */
#define MBED_MINOR_VERSION 0

/** MBED_PATCH_VERSION
  * Mbed 2 patch version
  */
#define MBED_PATCH_VERSION 164

#define MBED_ENCODE_VERSION(major, minor, patch) ((major)*10000 + (minor)*100 + (patch))

#define MBED_VERSION MBED_ENCODE_VERSION(MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION)

#define MBED_VERSION_CHECK(major, minor, patch) do { \
                                       MBED_STATIC_ASSERT((MBED_VERSION >= MBED_ENCODE_VERSION((major),(minor),(patch))), "Incompatible mbed-os version detected!!"); \
                                     } while(0)

#endif

/** @}*/
/** @}*/
