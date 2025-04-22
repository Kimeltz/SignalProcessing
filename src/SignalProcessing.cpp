#include <Arduino.h>
#include "SignalProcessing.h"
#include <math.h>

movingAverage::movingAverage(int bufferSize)
    :_size(bufferSize), _index(0), _count(0), _sum(0.0f), _buffer(nullptr) {}

movingAverage::~movingAverage() {
    if (_buffer) free(_buffer);
}

bool movingAverage::init()
{
    if (_buffer) free(_buffer);
    _buffer = (float*) calloc(_size, sizeof(float));
    return (_buffer != nullptr);
}

float movingAverage::update(float newData)
{
    if (!_buffer) return 0.0f;
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
    if (_count == 0) return 0.0f;
    return _sum / _count;
}

int movingAverage::getSize()
{
    return _size;
}

int movingAverage::getCount()
{
    return _count;
}

movingStandardDeviation::movingStandardDeviation(int bufferSize)
    :_size(bufferSize), _index(0), _count(0), _sum(0.0f), _sumSquare(0.0f), _buffer(nullptr) {}

movingStandardDeviation::~movingStandardDeviation() {
    if (_buffer) free(_buffer);
}

bool movingStandardDeviation::init()
{
    if (_buffer) free(_buffer);
    _buffer = (float*) calloc(_size, sizeof(float));
    return (_buffer != nullptr);
}

float movingStandardDeviation::update(float newData)
{
    if (!_buffer) return 0.0f;
    if(_count == _size) {
        _sum -= _buffer[_index];
        _sumSquare -= _buffer[_index] * _buffer[_index];
    } else {
        _count++;
    }

    _buffer[_index] = newData;
    _sum += newData;
    _sumSquare += newData * newData;
    _index = (_index + 1) % _size; 

    float mean = _sum / _count;
    return sqrt((_sumSquare / _count) - (mean * mean));
}

float roundToNearest005(float val)
{
    return round(val * 20) / 20;
}
float* roundToNearest005(float* val, int size)
{
    for(int i = 0; i < size; i++)
    {
        val[i] = round(val[i] * 20) / 20;
    }
    return val;
}

float average(float* val, int size)
{
    float sum = 0.0f;
    for(int i = 0; i < size; i++) sum += val[i];
    return sum / size;
}

float standardDeviation(float* val, int size)
{
    float mean = average(val, size);
    float sum = 0.0f;
    for(int i = 0; i < size; i++) sum += pow(val[i] - mean, 2);
    return sqrt(sum / size);
}