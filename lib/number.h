#pragma once
#include <cinttypes>
#include <iostream>
#include <vector>


struct uint2022_t {
    std::vector<uint32_t> _num = std::vector<uint32_t> (68);
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char *buff);

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator/(const uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator/(const uint2022_t &lhs, const uint32_t rhs);

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs);

bool  operator<(const uint2022_t &lhs, const uint2022_t &rhs);

bool  operator>(const uint2022_t &lhs, const uint2022_t &rhs);

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value);
