#include "RingBuffer.h"
#include "string.h"

static rbElementsType rbElements;

//--------------------------------------------------------------------------------------


RingBuffer::RingBuffer(unsigned int bufferSize)
{
    ringBuffer = new unsigned char[bufferSize];
    memset(ringBuffer, 0, sizeof(bufferSize));
    rbElements.head = ringBuffer;
	rbElements.tail = ringBuffer;
    rbElements.totalBufferSize = (bufferSize - 1);
}

//--------------------------------------------------------------------------------------


void RingBuffer::WriteData(unsigned char data)
{
    static unsigned char *summ = ((ringBuffer + rbElements.totalBufferSize));

	*rbElements.head = data;
    rbElements.head = (rbElements.head == summ) ? ringBuffer : rbElements.head += 1;
}

//--------------------------------------------------------------------------------------


unsigned int RingBuffer::ReadData(unsigned char *data)
{
    unsigned int receivedDataSize = 0;
	static unsigned char *summ = ((ringBuffer + rbElements.totalBufferSize));

    while (rbElements.tail != rbElements.head)
    {
		*data = *rbElements.tail;
		++data;
        ++receivedDataSize;
		rbElements.tail = (rbElements.tail == summ) ? ringBuffer : rbElements.tail += 1;
    }

	return receivedDataSize;
}

//--------------------------------------------------------------------------------------


void RingBuffer::FlushRingBuffer(void)
{
    rbElements.tail = rbElements.head;
}

//--------------------------------------------------------------------------------------


unsigned int RingBuffer::GetReceivedBytesQty(void)
{
    unsigned int receivedDataSize = 0;
	static unsigned char *summ = ((ringBuffer + rbElements.totalBufferSize));
	rbElementsType rbElementsTemp;

    memcpy(&rbElementsTemp, &rbElements, sizeof(rbElementsType));
    while (rbElementsTemp.tail != rbElementsTemp.head)
    {
        ++receivedDataSize;
		rbElementsTemp.tail = (rbElementsTemp.tail == summ) ? ringBuffer : rbElementsTemp.tail += 1;
    }

	return receivedDataSize;
}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
