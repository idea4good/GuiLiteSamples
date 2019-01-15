/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#ifndef MBED_TICKER_H
#define MBED_TICKER_H

#include "drivers/TimerEvent.h"
#include "platform/Callback.h"
#include "platform/mbed_toolchain.h"
#include "platform/NonCopyable.h"
#include "platform/mbed_power_mgmt.h"
#include "hal/lp_ticker_api.h"
#include "platform/mbed_critical.h"

namespace mbed {
/** \addtogroup drivers */

/** A Ticker is used to call a function at a recurring interval
 *
 *  You can use as many separate Ticker objects as you require.
 *
 * @note Synchronization level: Interrupt safe
 *
 * Example:
 * @code
 * // Toggle the blinking LED after 5 seconds
 *
 * #include "mbed.h"
 *
 * Ticker timer;
 * DigitalOut led1(LED1);
 * DigitalOut led2(LED2);
 *
 * int flip = 0;
 *
 * void attime() {
 *     flip = !flip;
 * }
 *
 * int main() {
 *     timer.attach(&attime, 5);
 *     while(1) {
 *         if(flip == 0) {
 *             led1 = !led1;
 *         } else {
 *             led2 = !led2;
 *         }
 *         wait(0.2);
 *     }
 * }
 * @endcode
 * @ingroup drivers
 */
class Ticker : public TimerEvent, private NonCopyable<Ticker> {

public:
    Ticker() : TimerEvent(), _function(0), _lock_deepsleep(true)
    {
    }

    // When low power ticker is in use, then do not disable deep sleep.
    Ticker(const ticker_data_t *data) : TimerEvent(data), _function(0), _lock_deepsleep(true)
    {
#if DEVICE_LPTICKER
        _lock_deepsleep = (data != get_lp_ticker_data());
#endif
    }

    /** Attach a function to be called by the Ticker, specifying the interval in seconds
     *
     *  @param func pointer to the function to be called
     *  @param t the time between calls in seconds
     */
    void attach(Callback<void()> func, float t)
    {
        attach_us(func, t * 1000000.0f);
    }

    /** Attach a member function to be called by the Ticker, specifying the interval in seconds
     *
     *  @param obj pointer to the object to call the member function on
     *  @param method pointer to the member function to be called
     *  @param t the time between calls in seconds
     *  @deprecated
     *      The attach function does not support cv-qualifiers. Replaced by
     *      attach(callback(obj, method), t).
     */
    template<typename T, typename M>
    MBED_DEPRECATED_SINCE("mbed-os-5.1",
                          "The attach function does not support cv-qualifiers. Replaced by "
                          "attach(callback(obj, method), t).")
    void attach(T *obj, M method, float t)
    {
        attach(callback(obj, method), t);
    }

    /** Attach a function to be called by the Ticker, specifying the interval in microseconds
     *
     *  @param func pointer to the function to be called
     *  @param t the time between calls in micro-seconds
     *
     *  @note setting @a t to a value shorter than it takes to process the ticker callback
     *  causes the system to hang. Ticker callback is called constantly with no time
     *  for threads scheduling.
     *
     */
    void attach_us(Callback<void()> func, us_timestamp_t t)
    {
        core_util_critical_section_enter();
        // lock only for the initial callback setup and this is not low power ticker
        if (!_function && _lock_deepsleep) {
            sleep_manager_lock_deep_sleep();
        }
        _function = func;
        setup(t);
        core_util_critical_section_exit();
    }

    /** Attach a member function to be called by the Ticker, specifying the interval in microseconds
     *
     *  @param obj pointer to the object to call the member function on
     *  @param method pointer to the member function to be called
     *  @param t the time between calls in microseconds
     *  @deprecated
     *      The attach_us function does not support cv-qualifiers. Replaced by
     *      attach_us(callback(obj, method), t).
     */
    template<typename T, typename M>
    MBED_DEPRECATED_SINCE("mbed-os-5.1",
                          "The attach_us function does not support cv-qualifiers. Replaced by "
                          "attach_us(callback(obj, method), t).")
    void attach_us(T *obj, M method, us_timestamp_t t)
    {
        attach_us(Callback<void()>(obj, method), t);
    }

    virtual ~Ticker()
    {
        detach();
    }

    /** Detach the function
     */
    void detach();

#if !defined(DOXYGEN_ONLY)
protected:
    void setup(us_timestamp_t t);
    virtual void handler();

protected:
    us_timestamp_t         _delay;  /**< Time delay (in microseconds) for resetting the multishot callback. */
    Callback<void()>    _function;  /**< Callback. */
    bool          _lock_deepsleep;  /**< Flag which indicates if deep sleep should be disabled. */
#endif
};

} // namespace mbed

#endif
