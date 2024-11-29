/***************************************************************************************
 * File: main.cpp
 * Author: Miguel Mendoza Jaidar
 * Email: miguel.mendoza.jaidar@example.com
 * 
 * Project: [Project Name or Description]
 * 
 * Ownership: 
 * This file is the intellectual property of Miguel Mendoza Jaidar.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 * 
 * License: 
 * Licensed under the MIT License. You may obtain a copy of the License at:
 * https://opensource.org/licenses/MIT
 * 
 * Usage:
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 * Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************************/

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
