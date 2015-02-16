#ifndef RINGBUFFER_H_INCLUDED
#define RINGBUFFER_H_INCLUDED

typedef struct
{
    unsigned char   *head;
    unsigned char   *tail;
    unsigned char   totalBufferSize;
}rbElementsType;



class RingBuffer
{
public:
    RingBuffer(unsigned int bufferSize);
    void WriteData(unsigned char data);
    unsigned int ReadData(unsigned char *data); //returns bytes QTY
    unsigned int GetReceivedBytesQty(void);
    void FlushRingBuffer(void);
private:
    unsigned char *ringBuffer;
    rbElementsType  rbElements;
};

#endif /* RINGBUFFER_H_INCLUDED */
