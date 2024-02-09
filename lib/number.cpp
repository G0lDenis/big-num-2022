#include "number.h"
#include <cstring>
#include <iomanip>
#include <algorithm>

const uint32_t BASE = 1000000000U;
const size_t DIGIT_SIZE = 68;

uint2022_t from_uint(const uint32_t i) {
    std::vector<uint32_t> res = std::vector<uint32_t>(DIGIT_SIZE);
    for (int j = 0; j < res.size() - 1; j++) {
        res.at(j) = 0;
    }
    if (i >= BASE) {
        res.at(res.size() - 1) = i % BASE;
        res.at(res.size() - 2) = i / BASE;
    } else {
        res.at(res.size() - 1) = i;
    }

    return uint2022_t{res};
}

uint2022_t from_string(const char* buff) {
    std::vector<uint32_t> res(DIGIT_SIZE, (uint32_t) 0);
    const size_t len = strlen(buff);
    if (len == 0) {
        return uint2022_t{res};
    }
    size_t ind = len;
    int reg = DIGIT_SIZE - 1;
    char st[9] = "00000000";
    while ((ind-- > 0) && (reg >= 0)) {
        size_t reversed_ind = 8 - (len - ind - 1) % 9;
        st[reversed_ind] = *(buff + ind);
        if ((len - ind) % 9 == 0) {
            res[reg] = atoi(st);
            reg--;
            memset(st, '0', 9);
        }
    }
    if (strlen(st) != 0) {
        res[reg] = (uint32_t) _atoi64(st);
    }

    return uint2022_t{res};
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res = from_uint(0);
    for (size_t i = DIGIT_SIZE; i-- > 0;) {
        if (BASE > res._num[i] + lhs._num[i] + rhs._num[i]) {
            res._num[i] += lhs._num[i] + rhs._num[i];
        } else {
            res._num[i] += lhs._num[i] + rhs._num[i] - BASE;
            size_t j = i;
            while ((j-- > 0) && (res._num[j] == BASE - 1)) {
                res._num[j] = 0;
            }
            res._num[j] += 1;
        }
    }

    return res;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t res = from_uint(0);
    if (lhs < rhs) return res;
    for (size_t i = DIGIT_SIZE; i-- > 0;) {
        if (res._num[i] + lhs._num[i] >= rhs._num[i]) {
            res._num[i] += lhs._num[i] - rhs._num[i];
        } else {
            res._num[i] += lhs._num[i] + BASE - rhs._num[i];
            size_t j = i;
            while ((j-- > 0) && (res._num[j] == 0)) {
                res._num[j] = BASE - 1;
            }
            res._num[j] -= 1;
        }
    }

    return res;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    std::vector<uint64_t> aux_arr = std::vector<uint64_t>(DIGIT_SIZE);
    const size_t LAST_IND = DIGIT_SIZE - 1;
    for (size_t i = DIGIT_SIZE; i-- > 0;) {
        for (size_t j = DIGIT_SIZE; j-- > 0;) {
            // Skip leading nulls
            if (((2 * LAST_IND - i - j) >= DIGIT_SIZE) && (lhs._num[i] == 0) && (rhs._num[i] == 0)) continue;
            aux_arr[2 * LAST_IND - (i + j)] += (uint64_t) lhs._num[i] * (uint64_t) rhs._num[j];
        }
    }
    uint2022_t res = from_uint(0);
    for (size_t i = 0; i < DIGIT_SIZE; i++) {
        aux_arr[i + 1] += aux_arr[i] / BASE;
        res._num[LAST_IND - i] = aux_arr[i] % BASE;
    }

    return res;
}

uint2022_t operator/(const uint2022_t& lhs, const uint32_t rhs) {
    uint2022_t res = from_uint(0);
    for (size_t i = 0; i < DIGIT_SIZE - 1; i++) {
        uint32_t num = lhs._num[i] + res._num[i];
        res._num[i] = num / rhs;
        res._num[i + 1] += (num % rhs) * BASE;
    }
    res._num[DIGIT_SIZE - 1] = (lhs._num[DIGIT_SIZE - 1] + res._num[DIGIT_SIZE - 1]) / rhs;
    return res;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs == from_uint(0)) {
        throw std::invalid_argument("division by zero");
    }
    if (lhs < rhs) {
        return from_uint(0);
    }

    auto i = lhs._num.begin();
    while (i != lhs._num.end() && (*i == 0)) {
        i++;
    }
    size_t left_start = i - lhs._num.begin();
    i = rhs._num.begin();
    while (i != rhs._num.end() && (*i == 0)) {
        i++;
    }
    size_t right_start = i - rhs._num.begin();
    size_t power_diff = right_start - left_start;
    uint2022_t left = from_uint(0);
    uint2022_t right = from_uint(0);
    // When we divine a number by another, we have result between BASE^(n-1) and BASE^(n+1),
    // where n is a difference between maximum non-zero digit of numbers
    if (power_diff != 0) {
        // DIGIT_SIZE - 1 - power_diff + 1 = DIGIT_SIZE - power_diff
        left._num[DIGIT_SIZE - power_diff] = 1;
    }
    // DIGIT_SIZE - 1 - power_diff - 1 = DIGIT_SIZE - 2 - power_diff
    right._num[DIGIT_SIZE - 2 - power_diff] = 1;
    uint2022_t mid;
    while (left < right - from_uint(1)) {
        mid = (left + right) / 2;
        if (mid * rhs > lhs) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return left;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < DIGIT_SIZE; i++) {
        if (lhs._num[i] != rhs._num[i]) return false;
    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < DIGIT_SIZE; i++) {
        if (lhs._num[i] != rhs._num[i]) return lhs._num[i] < rhs._num[i];
    }

    return false;
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < DIGIT_SIZE; i++) {
        if (lhs._num[i] != rhs._num[i]) return lhs._num[i] > rhs._num[i];
    }

    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    auto i = value._num.begin();
    while (i != value._num.end() && (*i == 0)) {
        i++;
    }
    if (i == value._num.end()) stream << '0';
    bool first_num = true;
    while (i != value._num.end()) {
        if (first_num) {
            stream << *i;
            first_num = false;
        } else {
            stream << std::setfill('0') << std::setw(9) << *i;
        }
        i++;
    }

    return stream;
}
