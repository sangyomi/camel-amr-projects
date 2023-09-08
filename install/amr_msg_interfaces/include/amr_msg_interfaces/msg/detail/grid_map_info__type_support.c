// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from amr_msg_interfaces:msg/GridMapInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "amr_msg_interfaces/msg/detail/grid_map_info__rosidl_typesupport_introspection_c.h"
#include "amr_msg_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "amr_msg_interfaces/msg/detail/grid_map_info__functions.h"
#include "amr_msg_interfaces/msg/detail/grid_map_info__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `data`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  amr_msg_interfaces__msg__GridMapInfo__init(message_memory);
}

void GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_fini_function(void * message_memory)
{
  amr_msg_interfaces__msg__GridMapInfo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(amr_msg_interfaces__msg__GridMapInfo, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "rows",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(amr_msg_interfaces__msg__GridMapInfo, rows),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "cols",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(amr_msg_interfaces__msg__GridMapInfo, cols),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "data",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(amr_msg_interfaces__msg__GridMapInfo, data),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_members = {
  "amr_msg_interfaces__msg",  // message namespace
  "GridMapInfo",  // message name
  4,  // number of fields
  sizeof(amr_msg_interfaces__msg__GridMapInfo),
  GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_member_array,  // message members
  GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_type_support_handle = {
  0,
  &GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_amr_msg_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, amr_msg_interfaces, msg, GridMapInfo)() {
  GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_type_support_handle.typesupport_identifier) {
    GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &GridMapInfo__rosidl_typesupport_introspection_c__GridMapInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
