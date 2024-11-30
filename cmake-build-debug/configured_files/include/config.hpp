#pragma once

#include <cstdint>
#include <string_view>

/**
 * @brief Constants related to the project metadata.
 * 
 * These constants hold the project name, version information, and the 
 * associated Git commit hash, which are used for versioning and project 
 * metadata purposes.
 */

// The name of the project.
static constexpr std::string_view project_name = "CppTemplate";

/**
 * @brief The version of the project.
 * 
 * A string representing the full version of the project, including major, 
 * minor, and patch versions (e.g., "1.0.0").
 */
static constexpr std::string_view project_version = "1.0.0";

/**
 * @brief Major version number.
 * 
 * This number indicates significant changes, such as breaking changes or 
 * other large changes that could affect backward compatibility.
 */
static constexpr std::int32_t project_version_major{ 1 };

/**
 * @brief Minor version number.
 * 
 * This number represents smaller updates to the project, such as new features 
 * or enhancements that are backward compatible.
 */
static constexpr std::int32_t project_version_minor{ 0 };

/**
 * @brief Patch version number.
 * 
 * This number represents small bug fixes or patches that do not affect the 
 * public API and are backward compatible.
 */
static constexpr std::int32_t project_version_patch{ 0 };

/**
 * @brief Git commit SHA for the current project version.
 * 
 * This is the commit hash representing the current state of the project. If 
 * not set, it is represented as an empty string.
 */
static constexpr std::string_view git_sha = "";
