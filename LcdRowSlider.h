//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2013 Andrew Duncan
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

#ifndef LCD_ROW_SLIDER_H
#define LCD_ROW_SLIDER_H

//-------------------------------------------------------------------------

#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "LiquidCrystal.h"

//-------------------------------------------------------------------------

class LcdRowSlider 
{
public:

    LcdRowSlider(
        LiquidCrystal& lcd,
        int32_t min,
        int32_t max,
        uint8_t row,
        uint8_t firstColumn = 0,
        uint8_t lastColumn = 15);

    void value(int32_t value)
    {
        unscaled(map(value, _min, _max, 0, (_columns * 5) - 1));
    }

    void unscaled(uint8_t value);

    uint8_t getRow() const { return _row; }

    int32_t getMin() const { return _min; }
    int32_t getMax() const { return _max; }

    void setColumns(uint8_t first, uint8_t last);
    void setMinMax(int32_t min, int32_t max) { _min = min; _max = max; }

private: 

    LiquidCrystal& _lcd;
    int32_t _min;
    int32_t _max;
    uint8_t _row;
    uint8_t _firstColumn;
    uint8_t _columns;
    boolean _setup;

    void setup();
};

//-------------------------------------------------------------------------

#endif
