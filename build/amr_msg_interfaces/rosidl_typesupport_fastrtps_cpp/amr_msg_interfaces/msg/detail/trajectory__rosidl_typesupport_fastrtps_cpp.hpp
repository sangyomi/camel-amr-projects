// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from amr_msg_interfaces:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "amr_msg_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "amr_msg_interfaces/msg/detail/trajectory__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace amr_msg_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_amr_msg_interfaces
cdr_serialize(
  const amr_msg_interfaces::msg::Trajectory & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_amr_msg_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  amr_msg_interfaces::msg::Trajectory & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_amr_msg_interfaces
get_serialized_size(
  const amr_msg_interfaces::msg::Trajectory & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_amr_msg_interfaces
max_serialized_size_Trajectory(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace amr_msg_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_amr_msg_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, amr_msg_interfaces, msg, Trajectory)();

#ifdef __cplusplus
}
#endif

#endif  // AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
