#pragma once

namespace as
{
    // 相机接口型号
    enum CameraType
    {
        CAMERALINK = 0,
        GIGECAMERA,
        USB3CAMERA,
        CXPCAMERA
    };

    // 相机参数
    enum class CameraParameter
    {
        CAMERA_PARA_WIDTH = 0,
        CAMERA_PARA_HEIGHT = 1,
        CAMERA_PARA_SIZE = 2,
        CAMERA_CHANNEL
    };

    // 相机ID号
    enum class CameraID
    {
        CAMERA_ID_MAIN = 0x00, // 主相机
        CAMERA_ID_NONE
    };

    struct CameraConfig
    {
        size_t width;
        size_t height;
        size_t channels = 1;
        size_t ImageSize;
        // 待补充
    };

    // 保存图片格式
    enum class ImageType
    {
        Image_Bmp = 1, // bmp类型图像
        Image_Jpg = 2, // jpg类型图像
        Image_Png      // png类型图像
    };

    // 相机厂商
    enum CameraManufacturers
    {
        HIKcamear = 0,
        FLIRcamera,
        IKAPcamera
    };
}