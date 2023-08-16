#ifndef CONVERSION_H_
#define CONVERSION_H_

#include "libGalapagos/galapagos_packet.h"
#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"
#include "nnet_utils/nnet_helpers.h"

template <typename PRECISION_TYPE, class STREAM_TYPE, size_t STREAM_LENGTH, size_t GP_WIDTH>
void galapagos_to_hls_stream(
	galapagos_interface *gp,
	hls::stream<STREAM_TYPE> &hls)
{
	size_t STREAM_SIZE = STREAM_TYPE::size;
	size_t FIXED_POINT_WIDTH = PRECISION_TYPE::width;
	size_t GP_SIZE = GP_WIDTH / FIXED_POINT_WIDTH;
	size_t GP_LENGTH = ceil((STREAM_LENGTH * STREAM_SIZE) / GP_SIZE);

	galapagos_packet packet;

//	std::cout << "STREAM_LENGTH= " << STREAM_LENGTH << std::endl;
//	std::cout << "STREAM_SIZE= " << STREAM_SIZE << std::endl;
//	std::cout << "FIXED_POINT_WIDTH= " << FIXED_POINT_WIDTH << std::endl;
//	std::cout << "GP_LENGTH= " << GP_LENGTH << std::endl;
//	std::cout << "GP_SIZE= " << GP_SIZE << std::endl;
//    std::cout << "------------------------"  << std::endl;

	PRECISION_TYPE stream_buf[STREAM_LENGTH*STREAM_SIZE];
	#pragma HLS ARRAY_PARTITION variable=stream_buf complete

	for(int i=0; i<GP_LENGTH; i++)
	{
		packet = gp->read();
		for(int j=0; j<GP_SIZE; j++)
		{
			if( (i*GP_SIZE+j) < (STREAM_LENGTH*STREAM_SIZE) )
			stream_buf[i*GP_SIZE+j].range() = packet.data.range(FIXED_POINT_WIDTH*(j+1)-1, FIXED_POINT_WIDTH*j);
		}
	}

	for(int i=0; i<STREAM_LENGTH; i++)
	{
		STREAM_TYPE buf;
		for(int j=0; j<STREAM_SIZE; j++)
		{
			buf[j] = stream_buf[i*STREAM_SIZE + j];
		}
		hls.write(buf);
	}

}

template <class STREAM_TYPE, typename PRECISION_TYPE, size_t STREAM_LENGTH, size_t GP_WIDTH>
void hls_stream_to_galapagos(short id,
							 hls::stream<STREAM_TYPE> &hls,
							 galapagos_interface *gp)
{
	size_t STREAM_SIZE = STREAM_TYPE::size;
	size_t FIXED_POINT_WIDTH = PRECISION_TYPE::width;
	size_t GP_SIZE = GP_WIDTH / FIXED_POINT_WIDTH;
	size_t GP_LENGTH = ceil((STREAM_LENGTH * STREAM_SIZE) / GP_SIZE);

	galapagos_packet packet;
	packet.id = id;
	packet.dest = id - 1;
	packet.last = 0;

//	std::cout << "STREAM_LENGTH= " << STREAM_LENGTH << std::endl;
//	std::cout << "STREAM_SIZE= " << STREAM_SIZE << std::endl;
//	std::cout << "FIXED_POINT_WIDTH= " << FIXED_POINT_WIDTH << std::endl;
//	std::cout << "GP_LENGTH= " << GP_LENGTH << std::endl;
//	std::cout << "GP_SIZE= " << GP_SIZE << std::endl;
//    std::cout << "------------------------"  << std::endl;

	PRECISION_TYPE stream_buf[STREAM_LENGTH*STREAM_SIZE];
	#pragma HLS ARRAY_PARTITION variable=stream_buf complete

	for(int i=0; i<STREAM_LENGTH; i++)
	{
		STREAM_TYPE buf = hls.read();
		for(int j=0; j<STREAM_SIZE; j++)
		{
			stream_buf[i*STREAM_SIZE + j] = buf[j];
		}
	}

	for(int i=0; i<GP_LENGTH; i++)
	{
		packet.data = 0;
		for(int j=0; j<GP_SIZE; j++)
		{
            if( (i*GP_SIZE+j) < (STREAM_LENGTH*STREAM_SIZE) )
            {
                packet.data.range(FIXED_POINT_WIDTH*(j+1)-1, FIXED_POINT_WIDTH*j) = stream_buf[i*GP_SIZE+j].range();
            }
        }
		packet.last = (i >= (GP_LENGTH-1));
		gp->write(packet);
	}

}

#endif
