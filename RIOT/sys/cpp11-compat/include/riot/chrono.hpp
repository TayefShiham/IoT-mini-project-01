/*
 * Copyright (C) 2015 Hamburg University of Applied Sciences (HAW)
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup cpp11-compat
 * @{
 *
 * @file
 * @brief  C++11 chrono drop in replacement that adds the function now based on
 *         ztimer/timex
 * @see    <a href="http://en.cppreference.com/w/cpp/thread/thread">
 *           std::thread, defined in header thread
 *         </a>
 *
 * @author Raphael Hiesgen <raphael.hiesgen (at) haw-hamburg.de>
 *
 * @}
 */

#ifndef RIOT_CHRONO_HPP
#define RIOT_CHRONO_HPP

#include <chrono>
#include <algorithm>

#include "time.h"
#include "timex.h"
#include "ztimer64.h"

namespace riot {

/**
 * @brief A time point for timed wait, as clocks from the standard are not
 *        available on RIOT.
 */
class time_point {
  using native_handle_type = timex_t;

 public:
  /**
   * @brief Creates a time point with seconds and microseconds set to 0.
   */
  inline time_point() : m_handle{0, 0} {}
  /**
   * @brief Create time point from timex_t struct.
   */
  explicit inline time_point(timex_t&& tp) : m_handle(tp) {}
  /**
   * @brief Use default copy constructor.
   */
  constexpr time_point(const time_point& tp) = default;
  /**
   * @brief Use default move constructor.
   */
  constexpr time_point(time_point&& tp) = default;

  /**
   * @brief Gives access to the native handle that stores the time information.
   */
  inline native_handle_type native_handle() const { return m_handle; }

  /**
   * @brief Add a standard chrono::duration to this time point.
   */
  template <class Rep, class Period>
  inline time_point& operator+=(const std::chrono::duration<Rep, Period>& d) {
    auto s = std::chrono::duration_cast<std::chrono::seconds>(d);
    auto m = (std::chrono::duration_cast<std::chrono::microseconds>(d) - s);
    m_handle.seconds += s.count();
    m_handle.microseconds += m.count();
    adjust_overhead();
    return *this;
  }

  /**
   * @brief Returns seconds member as uint32_t.
   */
  inline uint32_t seconds() const { return m_handle.seconds; }

  /**
   * @brief Returns microseconds member as uint32_t.
   */
  inline uint32_t microseconds() const { return m_handle.microseconds; }

 private:
  timex_t m_handle;
  void inline adjust_overhead() {
    auto secs = m_handle.microseconds / US_PER_SEC;
    m_handle.seconds += secs;
    m_handle.microseconds -= (secs * US_PER_SEC);
  }
};

/**
 * @brief Returns the current time saved in a time point.
 *
 * @return time_point containing the current time.
 */
inline time_point now() {
  timex_t tp;
  tp = timex_from_uint64(ztimer64_now(ZTIMER64_USEC));
  return time_point(std::move(tp));
}

/**
 * @brief Compares two timepoints.
 */
inline bool operator<(const time_point& lhs, const time_point& rhs) {
  return lhs.seconds() < rhs.seconds()
         || (lhs.seconds() == rhs.seconds() && lhs.microseconds()
                                               < rhs.microseconds());
}

/**
 * @brief Compares two timepoints.
 */
inline bool operator>(const time_point& lhs, const time_point& rhs) {
  return rhs < lhs;
}

/**
 * @brief Compares two timepoints.
 */
inline bool operator<=(const time_point& lhs, const time_point& rhs) {
  return !(rhs < lhs);
}

/**
 * @brief Compare two timepoints.
 */
inline bool operator>=(const time_point& lhs, const time_point& rhs) {
  return !(lhs < rhs);
}

} // namespace riot

#endif // RIOT_CHRONO_HPP
