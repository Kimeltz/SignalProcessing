#ifndef SignalProcessing_h
#define SignalProcessing_h

class movingAverage
{
    public:
        movingAverage(int bufferSize);
        int init();
        float update(float newData);
        float* getBuffer();
        float getValue();
        int getSize();
        int getCount();

    private:
        int _size;
        float* _buffer;
        int _index;
        int _count;
        float _sum;

};

#endif