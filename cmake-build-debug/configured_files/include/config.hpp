/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2008-2013 SonarSource
 * http://github.com/SonarOpenCommunity/sonar-cxx
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#pragma once

#include <cstdint>
#include <string_view>

/// @brief The name of the project.
/// This is a static, constant string representing the project's name.
static constexpr std::string_view project_name = "CppTemplate";

/// @brief The version of the project.
/// This is a semantic version string (e.g., "1.0.0").
static constexpr std::string_view project_version = "1.0.0";

/// @brief The major version number of the project.
/// Indicates the major release (breaking changes may occur).
static constexpr std::int32_t project_version_major{ 1 };

/// @brief The minor version number of the project.
/// Indicates the minor release (backward-compatible changes or features).
static constexpr std::int32_t project_version_minor{ 0 };

/// @brief The patch version number of the project.
/// Indicates patches or bug fixes for this version.
static constexpr std::int32_t project_version_patch{ 0 };

/// @brief The Git SHA of the current build.
/// Represents the commit hash used to track the exact state of the code at build time.
static constexpr std::string_view git_sha = "";
