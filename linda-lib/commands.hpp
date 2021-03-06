#pragma once

#include <iostream>
#include <array>

#include <nlohmann/json.hpp>

#include "header.hpp"

using json = nlohmann::json;

template<std::size_t S>
class LongInt {
public:
    LongInt(const unsigned* in) {
        for(std::size_t i = 0; i < S; i++) a[i] = in[i];
    }
    
    template<typename T>
    LongInt(T& json) {
        a = json;
    }

    auto val() { return a; } 

    auto begin() { return a.begin(); }
    auto end() { return a.end(); }

    std::array<unsigned,S> a;
};

using uint156_t = LongInt<5>;
using uint15360_t = LongInt<480>;

struct Message {
    BaseHeaderType header{};
    json body{};
};

class Command {
public:
    Command(const std::string& name);

    Message& getMessage();

    friend std::ostream& operator<< (std::ostream& stream, const Command& c);

protected:
    Message m;
};

class Temperature : public Command {
public:
    Temperature(unsigned chips_bitmap);
    unsigned getAnswer();
};

class HVSet : public Command {
public:
    HVSet(unsigned counts);
};

class TPDACSet : public Command {
public:
    TPDACSet(unsigned counts);
};

class WriteChipRegister : public Command {
public:
    WriteChipRegister(uint156_t& val, unsigned chips_bitmap);
};

class ReadChipRegister : public Command {
public:
    ReadChipRegister(unsigned chips_bitmap);
    uint156_t getAnswer();
};

class WritePixelRegister : public Command {
public:
    WritePixelRegister(uint15360_t& val, unsigned chips_bitmap);
};

class ReadPixelRegister : public Command {
public:
    ReadPixelRegister(unsigned chips_bitmap);
    uint15360_t getAnswer();
};

class ChipIDRead : public Command {
public:
    ChipIDRead(unsigned chips_bitmap);
    unsigned getAnswer();
};