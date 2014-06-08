//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Andrew Duncan
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

//-------------------------------------------------------------------------

template<typename LiquidCrystal_T>
class LcdRowSlider 
{
public:

    LcdRowSlider(
        LiquidCrystal_T& lcd,
        int32_t min,
        int32_t max,
        uint8_t row,
        uint8_t firstColumn = 0,
        uint8_t lastColumn = 15)
    :
        _lcd(lcd),
        _min(min),
        _max(max),
        _row(row),
        _firstColumn(firstColumn),
        _columns(lastColumn - firstColumn + 1),
        _setup(false)
    {
    }

    //---------------------------------------------------------------------

    void value(int32_t value)
    {
        unscaled(map(value, _min, _max, 0, (_columns * 5) - 1));
    }

    void unscaled(uint8_t value)
    {
        if (not _setup)
        {
            setup();
        }

        uint8_t letters = value / 5;
        uint8_t bar = value % 5;
        uint8_t letter = 0;

        _lcd.setCursor(letter + _firstColumn, _row);

        for ( ; letter < letters ; ++letter)
        {
            _lcd.write((uint8_t)5);
        }

        ++letter;
        _lcd.write(bar);

        for ( ; letter < _columns ; ++letter)
        {
            _lcd.write((uint8_t)5);
        }
    }

    //---------------------------------------------------------------------

    uint8_t getRow() const { return _row; }

    //---------------------------------------------------------------------

    int32_t getMin() const { return _min; }
    int32_t getMax() const { return _max; }

    //---------------------------------------------------------------------

    void setColumns(uint8_t first, uint8_t last)
    {
        _firstColumn = first;
        _columns = last - first + 1;
    }

    void setMinMax(int32_t min, int32_t max) { _min = min; _max = max; }

private: 

    LiquidCrystal_T& _lcd;
    int32_t _min;
    int32_t _max;
    uint8_t _row;
    uint8_t _firstColumn;
    uint8_t _columns;
    boolean _setup;

    //---------------------------------------------------------------------

    void setup()
    {
        for (uint8_t letter = 0 ; letter <= 5 ; ++letter)
        {
            uint8_t pixel = (letter == 5) ? 0 : 1 << (4 - letter);
            uint8_t pixels[8] = { 0, pixel, pixel, 0x1F, pixel, pixel, 0, 0 };
            _lcd.createChar(letter, pixels);
        }

        _setup = true;
    }
};

//-------------------------------------------------------------------------

#endif

