// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from amr_msg_interfaces:msg/GridMapInfo.idl
// generated code does not contain a copyright notice

#ifndef AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__TRAITS_HPP_
#define AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__TRAITS_HPP_

#include "amr_msg_interfaces/msg/detail/grid_map_info__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<amr_msg_interfaces::msg::GridMapInfo>()
{
  return "amr_msg_interfaces::msg::GridMapInfo";
}

template<>
inline const char * name<amr_msg_interfaces::msg::GridMapInfo>()
{
  return "amr_msg_interfaces/msg/GridMapInfo";
}

template<>
struct has_fixed_size<amr_msg_interfaces::msg::GridMapInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<amr_msg_interfaces::msg::GridMapInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<amr_msg_interfaces::msg::GridMapInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AMR_MSG_INTERFACES__MSG__DETAIL__GRID_MAP_INFO__TRAITS_HPP_
