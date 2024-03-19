#ifndef _IMAGE_BUFFER_HPP_
#define _IMAGE_BUFFER_HPP_

#include <mutex>
#include "as/core/def.h"
#include "as/core/imgproc/ImageData.hpp"

namespace as
{
    class AS_EXPORTS ImageBuffer
    {
    public:
        ImageBuffer(int width, int height, ImgType type, int capacity);

        void Clear();

        void Reset();

        void SetCapacity(const unsigned int capacity);

        uint64_t Size() const;

        bool Empty() const { 
            return tail_ == -1 && head_ == 0; 
        }

        bool Full() const { 
            return (head_ == 0 && tail_ == capacity_ - 1); 
        }

        uint64_t BufferSize() const { 
            return capacity_; 
        }

        void push(uint8_t* data, int size, int frame_id = -1);

        ImageData8UPtr pop(int index);

        ImageData8UPtr latest();

        int latest_index() { 
            return tail_; 
        }

        std::string imageInfo(int index);

    public:
        // The scale used to resize images sent to frontend
        static constexpr double kImageScale = 0.2;

    private:
        ImageBuffer& operator=(const ImageBuffer& other) = delete;

        uint64_t capacity_;
        int head_; //
        int tail_; //current frame
        // 编码图像,压缩传递
        std::vector<uint8_t> send_buffer_;

        // 原始图像数据流
        std::vector<ImageData8UPtr> image_buffer_;

        // mutex lock and condition variable to protect the received image
        std::mutex mutex_;
        // std::condition_variable cvar_;
    };

    typedef  std::shared_ptr<ImageBuffer> ImageBufferPtr;
}

#endif