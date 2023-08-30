// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from amr_msg_interfaces:msg/GridMapInfo.idl
// generated code does not contain a copyright notice

#ifndef AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__STRUCT_HPP_
#define AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__amr_msg_interfaces__msg__GridMapInfo __attribute__((deprecated))
#else
# define DEPRECATED__amr_msg_interfaces__msg__GridMapInfo __declspec(deprecated)
#endif

namespace amr_msg_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GridMapInfo_
{
  using Type = GridMapInfo_<ContainerAllocator>;

  explicit GridMapInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rows = 0ul;
      this->cols = 0ul;
    }
  }

  explicit GridMapInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->rows = 0ul;
      this->cols = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _rows_type =
    uint32_t;
  _rows_type rows;
  using _cols_type =
    uint32_t;
  _cols_type cols;
  using _data_type =
    std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__rows(
    const uint32_t & _arg)
  {
    this->rows = _arg;
    return *this;
  }
  Type & set__cols(
    const uint32_t & _arg)
  {
    this->cols = _arg;
    return *this;
  }
  Type & set__data(
    const std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__amr_msg_interfaces__msg__GridMapInfo
    std::shared_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__amr_msg_interfaces__msg__GridMapInfo
    std::shared_ptr<amr_msg_interfaces::msg::GridMapInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GridMapInfo_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->rows != other.rows) {
      return false;
    }
    if (this->cols != other.cols) {
      return false;
    }
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const GridMapInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GridMapInfo_

// alias to use template instance with default allocator
using GridMapInfo =
  amr_msg_interfaces::msg::GridMapInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace amr_msg_interfaces

#endif  // AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__STRUCT_HPP_
