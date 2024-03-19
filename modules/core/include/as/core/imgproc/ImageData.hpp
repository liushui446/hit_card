#ifndef _IMAGE_BUFFER_H_
#define _IMAGE_BUFFER_H_

#include <vector>
#include <string>
#include <memory>
#include <map>

#include "as/core/def.h"
#include "as/core/imgproc/ASRect.hpp"

namespace as
{
    enum class ImgType{
        NONE = 0x00,
        GRAY = 0x01,
        RGB = 0x02,
        BGR = 0x03,
        BayerRG8 = 0x04,
        DEPTH = 0x05,
    };

    const std::map<ImgType, int> kChannelsMap{
        {ImgType::GRAY, 1}, 
        {ImgType::RGB, 3}, 
        {ImgType::BGR, 3}, 
        {ImgType::BayerRG8, 1}, 
        {ImgType::DEPTH, 1} 
    };

    template<typename T>
    class AS_EXPORTS Blob {
    public:
        Blob() : data_(nullptr), count_(0), capacity_(0) {
            shape_.resize(3);
        }

        //shallow copy
        Blob(const int channels, const int height, const int width, T* data)
        : capacity_(0){
            shape_.resize(3);
            shape_[0] = height;
            shape_[1] = width;
            shape_[2] = channels;
            count_ = height * width * channels;
            data_ = data;
        }


        explicit Blob(const std::vector<int>& shape)
        // capacity_ must be initialized before calling Reshape
        : capacity_(0) {
            Reshape(shape);
        }

        ~Blob() {
            if (capacity_ != 0) 
            {
                delete[]data_;
            }
        }

        //@param[in] r: height  or rows
        //@param[in] c: width or cols
        //@param[in] n: channel
        inline const int offset(int r, int c, int n) const{
            return ((0 * shape_[0] + r) * shape_[1] + c) * shape_[2] + n;
        };

        void Reshape(const std::vector<int>& shape){
            count_ = 1;
            shape_.resize(shape.size());

            for (int i = 0; i < shape.size(); ++i)
            {
                count_ *= shape[i];
                shape_[i] = shape[i];
            }
            if (count_ > capacity_)
            {
                if (capacity_ != 0 && data_ != nullptr)
                {
                    delete[]data_;
                }

                capacity_ = count_;
                data_ = new T[capacity_];
            }
        }

        inline const std::vector<int>& shape() const{ 
            return shape_;
        }

        inline int shape(int index) const{ 
            // assert(index < shape_.size());
            return shape_[index];
        }

        void CopyFrom(const T* source) {
            size_t size = count_ * sizeof(T);
            if (data_ != NULL) {
                delete[]data_;
            }
            capacity_ = size;
            data_ = new T[size];
            memcpy(data_, source, size);
        }

        inline const T* blob_data() const{ 
            return data_;
        }

        inline const T* Blob::data() const{ 
            return data_;
        }

        inline T* mutable_data(){
            return data_; 
        }

    private:       
        Blob(const Blob&) = delete;

        Blob& operator=(const Blob&) = delete;

    protected:
        int count_;
        int capacity_;
        T* data_;
        std::vector<int> shape_;  // [row, col ,channel] or [height, width, channels]
    };

    /** 
    *	@class ImageData
    *   @brief ImageData suruct class, used for storaging the image captured by camera
    *
    */
    template<typename T>
    class AS_EXPORTS ImageData{
    public:
        ImageData()
            :frame_id_(-1),
            width_(0),
            height_(0),
            type_(ImgType::NONE),
            channels_(0),
            width_step_(0),
            blob_(nullptr),
            scale_x(0),
            scale_y(0),
            polarity(0),
            roi_x(0),
            roi_y(0),
            roi_width(0),
            roi_height(0),
            offset_(0),
            cropped(false){

        }

        /*
        * @brief shallow copy
        * @param[in] data Pointer to the user data, note no data is copied. 
        *  The external data is not automatically deallocated,
        *  so you should take care of it
        */
        ImageData(int width, int height, double scalex, double scaley, ImgType type, T* data)
            :frame_id_(-1),
            width_(width),
            height_(height),
            offset_(0),
            scale_x(scalex),
            scale_y(scaley),
            type_(type),
            polarity(0),
            roi_x(0),
            roi_y(0),
            roi_width(0),
            roi_height(0),
            cropped(false) {
            channels_ = kChannelsMap.at(type);
            width_step_ = width_ * channels_ * static_cast<int>(sizeof(T));
            blob_.reset(new (std::nothrow) Blob(channels_, height_, width_, data));
        }

        ImageData(int width, int height,double scalex, double scaley , ImgType type)
            :frame_id_(-1),
            width_(width),
            height_(height), 
            type_(type),
            offset_(0),
            scale_x(scalex),
            scale_y(scaley),
            polarity(0),
            roi_x(0),
            roi_y(0),
            roi_width(0),
            roi_height(0),
            cropped(false){
            channels_ = kChannelsMap.at(type);
            width_step_ = width_ * channels_ * static_cast<int>(sizeof(T));
            blob_.reset(new (std::nothrow) Blob<T>({ height_, width_, channels_ }));
        }

        ImageData(const ImageData &src)
            :frame_id_(src.frame_id_),
            width_(src.width_),
            height_(src.height_),
            type_(src.type_),
            channels_(src.channels_),
            width_step_(src.width_step_),
            blob_(src.blob_),
            offset_(src.offset_),
            scale_x(src.scale_x),
            scale_y(src.scale_y),
            polarity(src.polarity),
            roi_x(src.roi_x),
            roi_y(src.roi_y),
            roi_width(src.roi_width),
            roi_height(src.roi_height),
            cropped(false) {

        }

        ImageData& operator=(const ImageData& src) {
            this->frame_id_ = src.frame_id_;
            this->width_ = src.width_;
            this->height_ = src.height_;
            this->type_ = src.type_;
            this->channels_ = src.channels_;
            this->width_step_ = src.width_step_;
            this->blob_ = src.blob_;
            this->offset_ = src.offset_;
            this->scale_x = src.scale_x;
            this->scale_y = src.scale_y;
            this->polarity = src.polarity;
            this->roi_x = src.roi_x;
            this->roi_y = src.roi_y;
            this->roi_width = src.roi_width;
            this->roi_height = src.roi_height;
            this->cropped = src.cropped;
            return *this;
        }

        ~ImageData(){
            
        }

    protected:
        ImageData(int width, int height, double scalex, double scaley, ImgType type, std::shared_ptr<Blob<T>> blob, int offset = 0)
            :frame_id_(-1),
            width_(width),
            height_(height),
            type_(type),
            blob_(blob),
            offset_(offset),
            scale_x(scalex),
            scale_y(scaley),
            polarity(0),
            roi_x(0),
            roi_y(0),
            roi_width(0),
            roi_height(0),
            cropped(true){
            channels_ = kChannelsMap.at(type);
            width_step_ = width_ * channels_ * static_cast<int>(sizeof(T));
        }

    public:
        inline ImgType type() const{ 
            return type_; 
        }

        void set_type(ImgType type){
            type_ = type;
            channels_ = kChannelsMap.at(type_);
            blob_->Reshape({ height_, width_, channels_ });
        }

        inline int frame_id() const {
            return frame_id_;
        }

        void set_frame_id(int id) {
            frame_id_ = id;
            blob_->Reshape({ height_, width_, channels_ });
        }

        inline int width() const { 
            return width_; 
        }

        void set_width(int width) {
            width_ = width;
            blob_->Reshape({ height_, width_, channels_ });
        }

        inline int height() const { 
            return height_; 
        }

        void set_height(int height) {
            height_ = height;
            blob_->Reshape({ height_, width_, channels_ });
        }


        inline int channels() const { 
            return channels_; 
        }

        void set_channels(int channels) {
            channels_ = channels;
            blob_->Reshape({ height_, width_, channels_ });
        }

        void set_data(T* data, int image_size) {
            memcpy(mutable_data(), data, image_size);
        }

        inline int width_step() const {
            return width_step_;
        }

        inline double get_scaleX() const { 
            return scale_x; 
        }

        inline double get_scaleY() const { 
            return scale_y; 
        }

        // @brief: return the total number of pixels
        inline int total() const { 
            return width_ * height_ * channels_; 
        }
        
        T* mutable_data() { 
            return mutable_ptr(0); 
        }
        
        const T* data() const { 
            return ptr(0); 
        }

        T* mutable_ptr(int row = 0) {
            return  blob_->mutable_data() + blob_->offset(row, 0, 0) + offset_; //todo
        }

        const T* ptr(int row = 0) const {
            return blob_->data() + blob_->offset(row, 0, 0) + offset_; //todo
        }

        inline bool isEmpty(){
            if(blob_ == nullptr) 
                return true;
            else
                return false;
        }

        inline bool isCropped(){
            return cropped;
        }

        inline void setCropped(bool _cropped){
            this->cropped = _cropped;
        }
         
        /**	@brief should be used with caution
          */
        std::shared_ptr<ImageData> clone() const {
            std::shared_ptr<ImageData> im(new ImageData(width_, height_, scale_x, scale_y, type_));
            if (cropped) {
                for (int y = 0; y < height_; ++y) {
                    memcpy(im->mutable_ptr(y), this->ptr(y), im->width_step());
                }
            }
            else {
                memcpy(im->mutable_data(), this->data(), this->width_ * this->height_);
            }
            return (std::move(im));
        }
        
        ImageData operator()(const Rect<int>& roi) {
            int roi_offset = offset_ + blob_->offset(roi.y, roi.x, 0);
            return ImageData(roi.width, roi.height, this->scale_x, this->scale_y, type_, blob_, roi_offset);
        }

        

    protected:
        int frame_id_;        ///< frame id
        int width_;           ///< the width of the ROI image
        int height_;          ///< the height of the ROI image

        ImgType type_;
        int channels_;
        int width_step_;

        int polarity; ///< the polarity of the image background ,0:white, 1:black

        double roi_x; ///< ROI :the unit of mm
        double roi_y;
        double roi_width;
        double roi_height;

        double scale_x; ///< the scale of per pixel
        double scale_y;
        
        int offset_;

        std::shared_ptr<Blob<T>> blob_ = nullptr; ///< the origin data ptr
        bool cropped; ///< Image was cropped, memory space is no longer contiguous
    };

    typedef ImageData<unsigned char> ImageData8U;
    typedef ImageData<float> ImageData32F;
    typedef ImageData<double> ImageData64D;

    typedef std::shared_ptr<ImageData8U> ImageData8UPtr;
    typedef std::shared_ptr<ImageData8U> ThumbnailImageDataPtr;
    typedef std::shared_ptr< const ImageData8U> ImageData8UConstPtr;

    typedef std::shared_ptr<ImageData32F> ImageData32FPtr;
    typedef std::shared_ptr<const ImageData32FPtr> ImageData32FConstPtr;

    typedef std::shared_ptr<ImageData64D> ImageData64DPtr;
    typedef std::shared_ptr<const ImageData64DPtr> ImageData64DConstPtr;
}

#endif