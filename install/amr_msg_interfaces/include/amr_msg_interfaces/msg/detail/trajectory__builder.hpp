// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from amr_msg_interfaces:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
#define AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_

#include "amr_msg_interfaces/msg/detail/trajectory__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace amr_msg_interfaces
{

namespace msg
{

namespace builder
{

class Init_Trajectory_data
{
public:
  explicit Init_Trajectory_data(::amr_msg_interfaces::msg::Trajectory & msg)
  : msg_(msg)
  {}
  ::amr_msg_interfaces::msg::Trajectory data(::amr_msg_interfaces::msg::Trajectory::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::amr_msg_interfaces::msg::Trajectory msg_;
};

class Init_Trajectory_stack_size
{
public:
  explicit Init_Trajectory_stack_size(::amr_msg_interfaces::msg::Trajectory & msg)
  : msg_(msg)
  {}
  Init_Trajectory_data stack_size(::amr_msg_interfaces::msg::Trajectory::_stack_size_type arg)
  {
    msg_.stack_size = std::move(arg);
    return Init_Trajectory_data(msg_);
  }

private:
  ::amr_msg_interfaces::msg::Trajectory msg_;
};

class Init_Trajectory_header
{
public:
  Init_Trajectory_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Trajectory_stack_size header(::amr_msg_interfaces::msg::Trajectory::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Trajectory_stack_size(msg_);
  }

private:
  ::amr_msg_interfaces::msg::Trajectory msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::amr_msg_interfaces::msg::Trajectory>()
{
  return amr_msg_interfaces::msg::builder::Init_Trajectory_header();
}

}  // namespace amr_msg_interfaces

#endif  // AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
