#ifndef _C_POINT_CLOUD_HPP_
#define _C_POINT_CLOUD_HPP_

#include <limits>

#include "as/core/def.h"
#include "as/core/imgproc/ASPoint.hpp"
#include <Eigen/Dense>

namespace as
{
template <class PointT>
class AS_EXPORTS CPointCloud {
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    
public:
	CPointCloud() :
		scale_x_(1.0),
		scale_y_(1.0),
		timestamp_(0.0),
		width_(0),
		height_(0) {

    }

	// @brief construct from input point cloud and specified indices
	CPointCloud(const CPointCloud<PointT>& pc, const PointIndices& indices) {
		CopyPointCloud(pc, indices);
	}

	CPointCloud(const CPointCloud<PointT>& pc, const std::vector<int>& indices) {
		CopyPointCloud(pc, indices);
	}

	// @brief construct given width and height for organized point cloud
	CPointCloud(size_t width, size_t height, PointT point = PointT())
		: width_(width), height_(height) {
		points_.assign(width_ * height_, point);
	}

	virtual ~CPointCloud() = default;

	// @brief accessor of point via 2d indices for organized cloud
	inline const PointT* at(size_t col, size_t row) const {
		return IsOrganized() ? &(pc_[row * width_ + col]) : nullptr;
	}

	inline PointT* at(size_t col, size_t row) {
		return IsOrganized() ? &(points_[row * width_ + col]) : nullptr;
	}

	inline const PointT* operator()(size_t col, size_t row) const {
		return IsOrganized() ? &(points_[row * width_ + col]) : nullptr;
	}

	inline PointT* operator()(size_t col, size_t row) {
		return IsOrganized() ? &(points_[row * width_ + col]) : nullptr;
	}
	
	// @brief accessor of point via 1d index
	inline const PointT& operator[](size_t n) const { 
        return points_[n]; 
    }

	inline PointT& operator[](size_t n) { 
        return points_[n]; 
    }

	inline const PointT& at(size_t n) const { 
        return points_[n]; 
    }

	inline PointT& at(size_t n) { 
        return points_[n]; 
    }

	// @brief whether the cloud is organized
	inline bool IsOrganized() const { 
        return height_ > 1; 
    }

	// @brief accessor of point cloud height
	inline size_t height() const { 
        return height_; 
    }

	// @brief accessor of point cloud width
	inline size_t width() const { 
        return width_; 
    }

	// @brief accessor of point size, wrapper of vector
	inline size_t size() const { 
        return points_.size(); 
    }

	// @brief reserve function wrapper of vector
	inline virtual void reserve(size_t size) { 
        points_.reserve(size); 
    }

	// @brief empty function wrapper of vector
	inline bool empty() const { 
        return points_.empty(); 
    }

	// @brief resize function wrapper of vector
	inline virtual void resize(size_t size) {
		points_.resize(size);
		if (size != width_ * height_) {
			width_ = size;
			height_ = 1;
		}
	}

	// @brief clear function wrapper of vector
	inline virtual void clear() {
		points_.clear();
		width_ = height_ = 0;
	}

	// @brief copy point from another point cloud
	inline bool CopyPoint(size_t id, size_t rhs_id,
		const CPointCloud<PointT>& rhs) {
		if (id < points_.size() && rhs_id < rhs.points_.size()) {
			points_[id] = rhs.points_[rhs_id];
			return true;
		}
		return false;
	}

	// @brief copy point cloud
	inline void CopyPointCloud(const CPointCloud<PointT>& rhs,
		const PointIndices& indices) {
		CopyPointCloud(rhs, indices.indices);
	}

	template <typename IndexType>
	inline void CopyPointCloud(const CPointCloud<PointT>& rhs,
		const std::vector<IndexType>& indices) {
		width_ = indices.size();
		height_ = 1;
		points_.resize(indices.size());
		for (size_t i = 0; i < indices.size(); ++i) {
			points_[i] = rhs.points_[indices[i]];
		}
	}

	template <typename IndexType>
	inline void CopyPointCloudExclude(const CPointCloud<PointT>& rhs,
		const std::vector<IndexType>& indices) {
		width_ = indices.size();
		height_ = 1;
		points_.resize(rhs.size() - indices.size());
		std::vector<bool> mask(false, rhs.size());
		for (size_t i = 0; i < indices.size(); ++i) {
			mask[indices[i]] = true;
		}
		for (size_t i = 0; i < rhs.size(); ++i) {
			if (!mask[i]) {
				points_.push_back(rhs.points_[i]);
			}
		}
	}

	// @brief swap point cloud
	inline void SwapPointCloud(CPointCloud<PointT>* rhs) {
		points_.swap(rhs->points_);
		std::swap(width_, rhs->width_);
		std::swap(height_, rhs->height_);
		std::swap(sensor_to_world_pose_, rhs->sensor_to_world_pose_);
		std::swap(timestamp_, rhs->timestamp_);
	}

	bool CheckConsistency() const {
		return true;
	}

	// @brief cloud timestamp setter
	void set_timestamp(const double timestamp) { timestamp_ = timestamp; }

	// @brief cloud timestamp getter
	double get_timestamp() { return timestamp_; }

protected:
	double scale_x_;
	double scale_y_;
	double timestamp_;
	size_t width_;
	size_t height_;
	std::vector<PointT> points_;
};


// @brief Point cloud class split points and attributes storage
// for fast traversing
template <class PointT>
class AttributePointCloud : public CPointCloud<PointT> 
{
public:
	using CPointCloud<PointT>::points_;
	using CPointCloud<PointT>::width_;
	using CPointCloud<PointT>::height_;
	using CPointCloud<PointT>::IsOrganized;
	using CPointCloud<PointT>::timestamp_;

	// @brief default constructor
	AttributePointCloud() = default;

	// @brief construct from input point cloud and specified indices
	AttributePointCloud(const AttributePointCloud<PointT>& pc,
		const PointIndices& indices) {
		CopyPointCloud(pc, indices);
	}

	AttributePointCloud(const AttributePointCloud<PointT>& pc,
		const std::vector<int>& indices) {
		CopyPointCloud(pc, indices);
	}

	// @brief construct given width and height for organized point cloud
	AttributePointCloud(const size_t width, const size_t height,
		const PointT point = PointT()) {
		width_ = width;
		height_ = height;
		size_t size = width_ * height_;
		points_.assign(size, point);
		points_timestamp_.assign(size, 0.0);
		points_height_.assign(size, std::numeric_limits<float>::max());
		points_label_.assign(size, 0);
	}

	// @brief destructor
	virtual ~AttributePointCloud() = default;

	// @brief add points of input cloud, return the self cloud
	inline AttributePointCloud& operator+=(
		const AttributePointCloud<PointT>& rhs) {
		points_.insert(points_.end(), rhs.points_.begin(), rhs.points_.end());
		points_timestamp_.insert(points_timestamp_.end(),
			rhs.points_timestamp_.begin(),
			rhs.points_timestamp_.end());
		points_height_.insert(points_height_.end(), rhs.points_height_.begin(),
			rhs.points_height_.end());
		points_label_.insert(points_label_.end(), rhs.points_label_.begin(),
			rhs.points_label_.end());
		width_ = width_ * height_ + rhs.width_ * rhs.height_;
		height_ = 1;
		return *this;
	}

	// @brief overrided reserve function wrapper of vector
	inline void reserve(const size_t size) override {
		points_.reserve(size);
		points_timestamp_.reserve(size);
		points_height_.reserve(size);
		points_label_.reserve(size);
	}
    
	// @brief overrided resize function wrapper of vector
	inline void resize(const size_t size) override {
		points_.resize(size);
		points_timestamp_.resize(size, 0.0);
		points_height_.resize(size, std::numeric_limits<float>::max());
		points_label_.resize(size, 0);
		if (size != width_ * height_) {
			width_ = size;
			height_ = 1;
		}
	}

	// @brief overrided push_back function wrapper of vector
	inline void push_back(const PointT& point) {
		points_.push_back(point);
		points_timestamp_.push_back(0.0);
		points_height_.push_back(std::numeric_limits<float>::max());
		points_label_.push_back(0);
		width_ = points_.size();
		height_ = 1;
	}

	inline void push_back(const PointT& point, double timestamp,
		float height = std::numeric_limits<float>::max(),
		uint8_t label = 0) {
		points_.push_back(point);
		points_timestamp_.push_back(timestamp);
		points_height_.push_back(height);
		points_label_.push_back(label);
		width_ = points_.size();
		height_ = 1;
	}

	// @brief overrided clear function wrapper of vector
	inline void clear() override {
		points_.clear();
		points_timestamp_.clear();
		points_height_.clear();
		points_label_.clear();
		width_ = height_ = 0;
	}

	// @brief copy point from another point cloud
	inline bool CopyPoint(const size_t id, const size_t rhs_id,
		const AttributePointCloud<PointT>& rhs) {
		if (id < points_.size() && rhs_id < rhs.points_.size()) {
			points_[id] = rhs.points_[rhs_id];
			points_timestamp_[id] = rhs.points_timestamp_[rhs_id];
			points_height_[id] = rhs.points_height_[rhs_id];
			points_label_[id] = rhs.points_label_[rhs_id];
			return true;
		}
		return false;
	}

	// @brief copy point cloud
	inline void CopyPointCloud(const AttributePointCloud<PointT>& rhs,
		const PointIndices& indices) {
		CopyPointCloud(rhs, indices.indices);
	}

	template <typename IndexType>
	inline void CopyPointCloud(const AttributePointCloud<PointT>& rhs,
		const std::vector<IndexType>& indices) {
		width_ = indices.size();
		height_ = 1;
		points_.resize(indices.size());
		points_timestamp_.resize(indices.size());
		points_height_.resize(indices.size());
		points_label_.resize(indices.size());
		for (size_t i = 0; i < indices.size(); ++i) {
			points_[i] = rhs.points_[indices[i]];
			points_timestamp_[i] = rhs.points_timestamp_[indices[i]];
			points_height_[i] = rhs.points_height_[indices[i]];
			points_label_[i] = rhs.points_label_[indices[i]];
		}
	}

	// @brief swap point cloud
	inline void SwapPointCloud(AttributePointCloud<PointT>* rhs) {
		points_.swap(rhs->points_);
		std::swap(width_, rhs->width_);
		std::swap(height_, rhs->height_);
		std::swap(sensor_to_world_pose_, rhs->sensor_to_world_pose_);
		std::swap(timestamp_, rhs->timestamp_);
		points_timestamp_.swap(rhs->points_timestamp_);
		points_height_.swap(rhs->points_height_);
		points_label_.swap(rhs->points_label_);
	}

	// @brief overrided check data member consistency
	bool CheckConsistency() const {
		return ((points_.size() == points_timestamp_.size()) &&
			(points_.size() == points_height_.size()) &&
			(points_.size() == points_label_.size()));
	}

	size_t TransferToIndex(const size_t col, const size_t row) const {
		return row * width_ + col;
	}

	const std::vector<double>& points_timestamp() const {
		return points_timestamp_;
	}

	double points_timestamp(size_t i) const { 
        return points_timestamp_[i]; 
    }

	std::vector<double>* mutable_points_timestamp() { 
        return &points_timestamp_; 
    }

	const std::vector<float>& points_height() const { 
        return points_height_; 
    }

	float& points_height(size_t i) { 
        return points_height_[i]; 
    }

	const float& points_height(size_t i) const { 
        return points_height_[i]; 
    }

	void SetPointHeight(size_t i, size_t j, float height) {
		points_height_[i * width_ + j] = height;
	}

	void SetPointHeight(size_t i, float height) {
        points_height_[i] = height; 
    }

	std::vector<float>* mutable_points_height() { 
        return &points_height_; 
    }

	const std::vector<uint8_t>& points_label() const { 
        return points_label_; 
    }

	std::vector<uint8_t>* mutable_points_label() { 
        return &points_label_; 
    }

	uint8_t& points_label(size_t i) { 
        return points_label_[i]; 
    }

	const uint8_t& points_label(size_t i) const { 
        return points_label_[i]; 
    }

protected:
	std::vector<double> points_timestamp_;
	std::vector<float> points_height_;
	std::vector<uint8_t> points_label_;
};

// typedef of point cloud indices
typedef std::shared_ptr<PointIndices> PointIndicesPtr;
typedef std::shared_ptr<const PointIndices> PointIndicesConstPtr;

// typedef of point cloud
typedef AttributePointCloud<PointF> PointFCloud;
typedef AttributePointCloud<PointD> PointDCloud;
typedef AttributePointCloud<PointXYZMRGBHF> PointXYZMRGBHFCloud;
typedef AttributePointCloud<PointXYZMRGBHD> PointXYZMRGBHDCloud;


typedef std::shared_ptr<PointFCloud> PointFCloudPtr;
typedef std::shared_ptr<const PointFCloud> PointFCloudConstPtr;
typedef std::shared_ptr<PointXYZMRGBHFCloud> PointXYZMRGBHFCloudPtr;

typedef std::shared_ptr<PointDCloud> PointDCloudPtr;
typedef std::shared_ptr<const PointDCloud> PointDCloudConstPtr;
typedef std::shared_ptr<PointXYZMRGBHDCloud> PointXYZMRGBHDCloudPtr;
}

#endif