// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from amr_msg_interfaces:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__STRUCT_H_
#define AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'data'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/Trajectory in the package amr_msg_interfaces.
typedef struct amr_msg_interfaces__msg__Trajectory
{
  std_msgs__msg__Header header;
  int32_t stack_size;
  rosidl_runtime_c__int32__Sequence data;
} amr_msg_interfaces__msg__Trajectory;

// Struct for a sequence of amr_msg_interfaces__msg__Trajectory.
typedef struct amr_msg_interfaces__msg__Trajectory__Sequence
{
  amr_msg_interfaces__msg__Trajectory * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} amr_msg_interfaces__msg__Trajectory__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AMR_MSG_INTERFACES__MSG__DETAIL__TRAJECTORY__STRUCT_H_
