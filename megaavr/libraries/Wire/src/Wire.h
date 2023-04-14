/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#ifndef TwoWire_h
#define TwoWire_h

#include <Arduino.h>

#ifndef TWI_BUFFER_SIZE
#if ((RAMEND - RAMSTART) < 1023)
#define TWI_BUFFER_SIZE 16
#elif ((RAMEND - RAMSTART) < 4095)
#define TWI_BUFFER_SIZE 32
#elif ((RAMEND - RAMSTART) < 8191)
#define TWI_BUFFER_SIZE 64
#else
#define TWI_BUFFER_SIZE 128
#endif
#endif

// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1
class TwoWire : public Stream
{
  private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t transmitting;
    static void (*user_onRequest)();
    static void (*user_onReceive)(int);
    static uint8_t onRequestService();
    static void onReceiveService(int);

  public:
    TwoWire();
    bool pins(uint8_t sda_pin, uint8_t scl_pin);
    bool swap(uint8_t state = 1);
    void begin();
    void begin(uint8_t address);
    void begin(int address);
    void begin(uint8_t address, bool receive_broadcast, uint8_t second_address);
    void begin(int address, bool receive_broadcast, uint8_t second_address);
    void begin(uint8_t address, bool receive_broadcast);
    void begin(int address, bool receive_broadcast);
    void end();
    void setClock(uint32_t frequency);
    void beginTransmission(uint8_t address);
    void beginTransmission(int address);
    uint8_t endTransmission();
    uint8_t endTransmission(bool sendStop);
    uint8_t requestFrom(uint8_t address, size_t quantity, bool sendStop);
    uint8_t requestFrom(int address, int quantity, int sendStop);
    uint8_t requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop);
    uint8_t requestFrom(uint8_t address, size_t quantity);
    uint8_t requestFrom(uint8_t address, uint8_t quantity);
    uint8_t requestFrom(int address, int quantity);
    virtual size_t write(uint8_t data);
    virtual size_t write(const uint8_t *data, size_t quantity);
    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));

    inline size_t write(unsigned long data) { return write((uint8_t)data); }
    inline size_t write(long data) { return write((uint8_t)data); }
    inline size_t write(unsigned int data) { return write((uint8_t)data); }
    inline size_t write(int data) { return write((uint8_t)data); }
    using Print::write;
};

extern TwoWire Wire;

#endif
