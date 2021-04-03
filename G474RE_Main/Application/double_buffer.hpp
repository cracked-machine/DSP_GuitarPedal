/*
 * 		dsp_buffer.hpp
 *
 *  	Created on: Apr 2, 2021
 *      Author: Chris Sutton
 *
 *      MIT License
 *
 * 		Copyright (c) [2021] [Chris Sutton]
 *
 * 		Permission is hereby granted, free of charge, to any person obtaining a copy
 * 		of this software and associated documentation files (the "Software"), to deal
 * 		in the Software without restriction, including without limitation the rights
 * 		to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * 		copies of the Software, and to permit persons to whom the Software is
 * 		furnished to do so, subject to the following conditions:
 *
 * 		The above copyright notice and this permission notice shall be included in all
 * 		copies or substantial portions of the Software.
 *
 * 		THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * 		IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 		FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * 		AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * 		LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * 		OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 		SOFTWARE.
 */

#ifndef DOUBLE_BUFFER_HPP_
#define DOUBLE_BUFFER_HPP_

#include <assert.h>
#include <stdint.h>
#include <array>


enum class DBufAllign : uint8_t
{
	eight_bit_r 		= 4,		// 16-bit data right packed in 32-bit frame xxxxAABB
	sixteen_bit_l 		= 16,		// 16-bit data left packed in 32-bit frame AABBxxxx
	twentyfour_bit_l	= 16		// 24-bit data left packed in 32-bit frame AABBCCxx
};


enum class DBufFrame : uint8_t
{
	frame0 = 0,
	frame1 = 1
};

template <class T, size_t size>
class double_buffer
{

public:
	explicit double_buffer()
	{
		//assert(!size % 4);
		_rxBuf_frame0.fill(0);
		_txBuf_frame0.fill(0);
		_rxBuf_frame1.fill(0);
		_txBuf_frame1.fill(0);
	}

	T* getRxBuf();
	T* getTxBuf();

	uint8_t readRxFrame(int *left_sample, int *right_sample, DBufAllign allignment);
	uint8_t writeRxFrame(int *left_sample, int *right_sample, DBufAllign allignment);

	uint8_t readTxFrame(int *left_sample, int *right_sample, DBufAllign allignment);
	uint8_t writeTxFrame(int *left_sample, int *right_sample, DBufAllign allignment);

	DBufFrame swap_active_frame();
	DBufFrame get_active_frame();

private:

	DBufFrame _active_frame = DBufFrame::frame0;

	std::array<T, size*2> _rxBuf_bothFrames;
	std::array<T, size*2> _txBuf_bothFrames;

	std::array<T, size> _rxBuf_frame0;
	std::array<T, size> _txBuf_frame0;

	std::array<T, size> _rxBuf_frame1;
	std::array<T, size> _txBuf_frame1;

};

/*
 * @brief swap the current buffer frame
 *
 * @param	None
 *
 * @retval	1 current frame is 1
 * 			0 current frame is 0
 *
 */
template <class T, size_t size>
DBufFrame double_buffer<T, size>::swap_active_frame()
{
	DBufFrame res;
	switch(_active_frame)
	{
		case DBufFrame::frame0	:

			_active_frame = DBufFrame::frame1;
			res = get_active_frame();
			break;

		case DBufFrame::frame1	:

			_active_frame = DBufFrame::frame0;
			res = get_active_frame();
			break;
	}


	switch(_active_frame)
	{
		case DBufFrame::frame0	:


			break;

		case DBufFrame::frame1	:


			break;
	}

	return res;
}

/*
 * @brief Pull data from the specified Rx buffer
 *
 * @param	left_sample 	- the output left channel sample
 * 			right_smaple 	- the output right channel sample
 * 			allignment		- packet bit allignment
 * 							eight_bit_r 		= 4,	// 16-bit data right packed in 32-bit frame xxxxAABB
 * 							sixteen_bit_l 		= 16,	// 16-bit data left packed in 32-bit frame AABBxxxx
 * 							twentyfour_bit_l	= 16	// 24-bit data left packed in 32-bit frame AABBCCxx

 *
 * @retval	1 if pos param is pos+ 3 larger than buffer size
 * 			0 if pos param valid
 *
 */
template <class T, size_t size>
uint8_t double_buffer<T, size>::readRxFrame(	int *left_sample,
														int *right_sample,
														DBufAllign allignment)
{

	switch(_active_frame)
	{
		case DBufFrame::frame0	:

			*left_sample = (int) (( _rxBuf_frame0[0] << int(allignment) ) | _rxBuf_frame0[1]);
			*right_sample = (int) (( _rxBuf_frame0[2] << int(allignment) ) | _rxBuf_frame0[3]);
			break;

		case DBufFrame::frame1	:

			*left_sample = (int) (( _rxBuf_frame1[0] << int(allignment) ) | _rxBuf_frame1[1]);
			*right_sample = (int) (( _rxBuf_frame1[2] << int(allignment) ) | _rxBuf_frame1[3]);
			break;
	}

	return 0;


}

/*
 * @brief Pull data from the specified Tx buffer
 *
 * @param	left_sample 	- the output left channel sample
 * 			right_smaple 	- the output right channel sample
 * 			allignment		- packet bit allignment
 * 							eight_bit_r 		= 4,	// 16-bit data right packed in 32-bit frame xxxxAABB
 * 							sixteen_bit_l 		= 16,	// 16-bit data left packed in 32-bit frame AABBxxxx
 * 							twentyfour_bit_l	= 16	// 24-bit data left packed in 32-bit frame AABBCCxx
 *
 * @retval	1 if pos param is pos+ 3 larger than buffer size
 * 			0 if pos param valid
 *
 */
template <class T, size_t size>
uint8_t double_buffer<T, size>::readTxFrame(	int *left_sample,
														int *right_sample,
														DBufAllign allignment)
{

	switch(_active_frame)
	{
		case DBufFrame::frame0	:

			*left_sample = (int) (( _txBuf_frame0[0] << int(allignment) ) | _txBuf_frame0[1]);
			*right_sample = (int) (( _txBuf_frame0[2] << int(allignment) ) | _txBuf_frame0[3]);
			break;

		case DBufFrame::frame1	:

			*left_sample = (int) (( _txBuf_frame1[0] << int(allignment) ) | _txBuf_frame1[1]);
			*right_sample = (int) (( _txBuf_frame1[2] << int(allignment) ) | _txBuf_frame1[3]);
			break;
	}

	return 0;


}

/*
 * @brief 	Push data to the specified Tx buffer
 *
 * @param	left_sample 	- the input left channel sample
 * 			right_smaple 	- the input right channel sample
 * 			allignment		- packet bit allignment
 * 							eight_bit_r 		= 4,	// 16-bit data right packed in 32-bit frame xxxxAABB
 * 							sixteen_bit_l 		= 16,	// 16-bit data left packed in 32-bit frame AABBxxxx
 * 							twentyfour_bit_l	= 16	// 24-bit data left packed in 32-bit frame AABBCCxx
 *
 * @retval	1 if pos param is pos+ 3 larger than buffer size
 * 			0 if pos param valid
 */
template <class T, size_t size>
uint8_t double_buffer<T, size>::writeTxFrame(int *left_sample,
												int *right_sample,
												DBufAllign allignment)
{
	//restore to buffer
	switch(_active_frame)
	{
		case DBufFrame::frame0	:

			_txBuf_frame0[0] = ( (*left_sample) >> int(allignment) ) & 0xFFFF;
			_txBuf_frame0[1] = (*left_sample) & 0xFFFF;
			_txBuf_frame0[2] = ( (*right_sample) >> int(allignment) ) & 0xFFFF;
			_txBuf_frame0[3] = (*right_sample) & 0xFFFF;
			break;

		case DBufFrame::frame1	:

			_txBuf_frame1[0] = ( (*left_sample) >> int(allignment) ) & 0xFFFF;
			_txBuf_frame1[1] = (*left_sample) & 0xFFFF;
			_txBuf_frame1[2] = ( (*right_sample) >> int(allignment) ) & 0xFFFF;
			_txBuf_frame1[3] = (*right_sample) & 0xFFFF;
			break;
	}

	// update the conjoined buffer
	getTxBuf();

	return 0;
}


/*
 * @brief 	Push data to the specified Rx buffer
 *
 * @param	left_sample 	- the input left channel sample
 * 			right_smaple 	- the input right channel sample
 * 			allignment		- packet bit allignment
 * 							eight_bit_r 		= 4,	// 16-bit data right packed in 32-bit frame xxxxAABB
 * 							sixteen_bit_l 		= 16,	// 16-bit data left packed in 32-bit frame AABBxxxx
 * 							twentyfour_bit_l	= 16	// 24-bit data left packed in 32-bit frame AABBCCxx
 *
 * @retval	1 if pos param is pos+ 3 larger than buffer size
 * 			0 if pos param valid
 */
template <class T, size_t size>
uint8_t double_buffer<T, size>::writeRxFrame(int *left_sample,
												int *right_sample,
												DBufAllign allignment)
{

	//restore to buffer
	switch(_active_frame)
	{
		case DBufFrame::frame0	:

			_rxBuf_frame0[0] = ( (*left_sample) >> int(allignment) ) & 0xFFFF;
			_rxBuf_frame0[1] = (*left_sample) & 0xFFFF;
			_rxBuf_frame0[2] = ( (*right_sample) >> int(allignment) ) & 0xFFFF;
			_rxBuf_frame0[3] = (*right_sample) & 0xFFFF;
			break;

		case DBufFrame::frame1	:

			_rxBuf_frame1[0] = ( (*left_sample) >> int(allignment) ) & 0xFFFF;
			_rxBuf_frame1[1] = (*left_sample) & 0xFFFF;
			_rxBuf_frame1[2] = ( (*right_sample) >> int(allignment) ) & 0xFFFF;
			_rxBuf_frame1[3] = (*right_sample) & 0xFFFF;
			break;
	}

	// update the conjoined buffer
	getRxBuf();

	return 0;

}

/*
 * @brief 	Gets a pointer to the Rx buffer. Used for C API compatibility.
 * 			Pass this to a function expecting uint32_t pointer
 *
 * @param	None
 * @retval	the Rx buffer pointer
 *
 */
template <class T, size_t size> T* double_buffer<T, size>::getRxBuf()
{
	//return _rxBuf_frame0.data();	// return c array from std::array
	// return both rx frames conjoined into a c-style array
	std::copy(_rxBuf_frame0.data(), _rxBuf_frame0.data() + size,_rxBuf_bothFrames.data());
	std::copy(_rxBuf_frame1.data(), _rxBuf_frame1.data() + size,_rxBuf_bothFrames.data() + size);
	return _rxBuf_bothFrames.data();
}

/*
 * @brief 	Gets a pointer to the Tx buffer. Used for C API compatibility.
 * 			Pass this to a function expecting uint32_t pointer
 *
 * @param	None
 * @retval	the Tx buffer pointer
 *
 */
template <class T, size_t size> T* double_buffer<T, size>::getTxBuf()
{
	// return both tx frames conjoined into a c-style array
	std::copy(_txBuf_frame0.data(), _txBuf_frame0.data() + size,_txBuf_bothFrames.data());
	std::copy(_txBuf_frame1.data(), _txBuf_frame1.data() + size,_txBuf_bothFrames.data() + size);
	return _txBuf_bothFrames.data();
}


template <class T, size_t size> DBufFrame double_buffer<T, size>::get_active_frame()
{
	return _active_frame;
}

#endif /* DOUBLE_BUFFER_HPP_ */

