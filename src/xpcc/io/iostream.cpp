// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#include "iostream.hpp"

#include <xpcc/architecture/driver/accessor/flash.hpp>

FLASH(uint16_t base[]) = { 10, 100, 1000, 10000 };

// ----------------------------------------------------------------------------
xpcc::IOStream::IOStream(IODevice& device) :
	device(&device),
	mode(ASCII)
{
}

// ----------------------------------------------------------------------------
void
xpcc::IOStream::writeInteger(int16_t value)
{
	accessor::Flash<uint16_t> basePtr = xpcc::accessor::asFlash(base);
	
	if (value < 0) {
		value = -value;
		this->device->write('-');
	}
	
	bool zero = true;
	uint8_t i = 4;
	do {
		i--;
		char d;
		for (d = '0'; value >= (int16_t) basePtr[i]; value -= basePtr[i])
		{
			d++;
			zero = false;
		}
		if (!zero) {
			this->device->write(d);
		}
	} while (i);
	
	this->device->write(static_cast<char>(value) + '0');
}

// ----------------------------------------------------------------------------
void
xpcc::IOStream::writeInteger(uint16_t value)
{
	bool zero = true;
	accessor::Flash<uint16_t> basePtr = xpcc::accessor::asFlash(base);

	uint8_t i = 4;
	do {
		i--;
		char d;
		for (d = '0'; value >= basePtr[i]; value -= basePtr[i])
		{
			d++;
			zero = false;
		}
		if (!zero) {
			this->device->write(d);
		}
	} while (i);
	
	this->device->write(static_cast<char>(value) + '0');
}

// ----------------------------------------------------------------------------
void
xpcc::IOStream::writeInteger(int32_t value)
{
	char buffer[ArithmeticTraits<int32_t>::decimalDigits + 1]; // +1 for '\0'

	#ifdef __AVR__
	// uses the optimized non standard function 'ltoa()' which is
	// not always available. For the general case snprintf() is
	// used.
	this->device->write(ltoa(value, buffer, 10));
#else
	snprintf(buffer, sizeof(buffer), "%d", value);
	this->device->write(buffer);
#endif
}
	
void
xpcc::IOStream::writeInteger(uint32_t value)
{
	char buffer[ArithmeticTraits<uint32_t>::decimalDigits + 1]; // +1 for '\0'
	
#ifdef __AVR__
	// uses the optimized non standard function 'ultoa()' which is
	// not always available.
	this->device->write(ultoa(value, buffer, 10));
#else
	snprintf(buffer, sizeof(buffer), "%u", value);
	this->device->write(buffer);
#endif
}

#ifndef __AVR__
void
xpcc::IOStream::writeInteger(int64_t value)
{
	char buffer[ArithmeticTraits<int64_t>::decimalDigits + 1]; // +1 for '\0'
	
#if __WORDSIZE == 64
	snprintf(buffer, sizeof(buffer), "%ld", value);
#else
	snprintf(buffer, sizeof(buffer), "%lld", value);
#endif
	this->device->write(buffer);
}

void
xpcc::IOStream::writeInteger(uint64_t value)
{
	char buffer[ArithmeticTraits<uint64_t>::decimalDigits + 1]; // +1 for '\0'
	
#if __WORDSIZE == 64
	snprintf(buffer, sizeof(buffer), "%lu", value);
#else
	snprintf(buffer, sizeof(buffer), "%llu", value);
#endif
	this->device->write(buffer);
}
#endif

// ----------------------------------------------------------------------------
void
xpcc::IOStream::writeHex( const char* s )
{
	while ( *s != '\0' ) {
		this->writeHex( *s );
		s++;
	}
}

// ----------------------------------------------------------------------------
void
xpcc::IOStream::writeHex( char value )
{
	char nibble = (value >> 4);
	char hex;

	if (nibble > 9) {
		hex = nibble + 'A' - 10;
	}
	else {
		hex = nibble + '0';
	}
	this->device->write(hex);

	nibble = (value & 0xF);
	if (nibble > 9) {
		hex = nibble + 'A' - 10;
	}
	else {
		hex = nibble + '0';
	}
	this->device->write(hex);
}
