// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from amr_msg_interfaces:msg/GridMapInfo.idl
// generated code does not contain a copyright notice

#ifndef AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__BUILDER_HPP_
#define AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__BUILDER_HPP_

#include "amr_msg_interfaces/msg/detail/grid_map_info__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace amr_msg_interfaces
{

namespace msg
{

namespace builder
{

class Init_GridMapInfo_data
{
public:
  explicit Init_GridMapInfo_data(::amr_msg_interfaces::msg::GridMapInfo & msg)
  : msg_(msg)
  {}
  ::amr_msg_interfaces::msg::GridMapInfo data(::amr_msg_interfaces::msg::GridMapInfo::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::amr_msg_interfaces::msg::GridMapInfo msg_;
};

class Init_GridMapInfo_cols
{
public:
  explicit Init_GridMapInfo_cols(::amr_msg_interfaces::msg::GridMapInfo & msg)
  : msg_(msg)
  {}
  Init_GridMapInfo_data cols(::amr_msg_interfaces::msg::GridMapInfo::_cols_type arg)
  {
    msg_.cols = std::move(arg);
    return Init_GridMapInfo_data(msg_);
  }

private:
  ::amr_msg_interfaces::msg::GridMapInfo msg_;
};

class Init_GridMapInfo_rows
{
public:
  explicit Init_GridMapInfo_rows(::amr_msg_interfaces::msg::GridMapInfo & msg)
  : msg_(msg)
  {}
  Init_GridMapInfo_cols rows(::amr_msg_interfaces::msg::GridMapInfo::_rows_type arg)
  {
    msg_.rows = std::move(arg);
    return Init_GridMapInfo_cols(msg_);
  }

private:
  ::amr_msg_interfaces::msg::GridMapInfo msg_;
};

class Init_GridMapInfo_header
{
public:
  Init_GridMapInfo_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GridMapInfo_rows header(::amr_msg_interfaces::msg::GridMapInfo::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GridMapInfo_rows(msg_);
  }

private:
  ::amr_msg_interfaces::msg::GridMapInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::amr_msg_interfaces::msg::GridMapInfo>()
{
  return amr_msg_interfaces::msg::builder::Init_GridMapInfo_header();
}

}  // namespace amr_msg_interfaces

#endif  // AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__BUILDER_HPP_
