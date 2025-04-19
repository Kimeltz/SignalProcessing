#include <Arduino.h>
#include "SignalProcessing.h"
#include <math.h>

movingAverage::movingAverage(int bufferSize)
    :_size(bufferSize), _index(0), _count(0), _sum(0.0f) {}

movingAverage::~movingAverage() {
    free(_buffer);
}

int movingAverage::init()
{
    _buffer = (float*) calloc(_size, sizeof(float));
    if(!_buffer)
    {
        Serial.println("Memory Allocation Failed");
        return -1;
    }
    else return 0;
}

float movingAverage::update(float newData)
{
    if(_count == _size) _sum -= _buffer[_index];
    else _count++;

    _buffer[_index] = newData;
    _sum += newData;
    _index = (_index + 1) % _size; 
    return _sum / _count;
}

float* movingAverage::getBuffer()
{
    return _buffer; 
}

float movingAverage::getValue()
{
    return _sum / _count;
}