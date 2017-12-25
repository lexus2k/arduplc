/*
    Copyright (C) 2017 - 2018 Alexey Dynda

    This file is part of Ardu PLC project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

enum
{
    /**
     * Top sensor error. Error means false-positive sensor reaction
     */
    ERROR_CODE_TOP_SENSOR     = 1,

    /**
     * Center sensor error. Check press position
     * case1. In the middle between bottom and top sensors: Error means false-positive sensor reaction
     * case2. Top or bottom position: Error means absence of sensor reaction
     */
    ERROR_CODE_CENTER_SENSOR  = 2,

    /**
     * Bottom sensor error. Error means false-positive sensor reaction
     */
    ERROR_CODE_BOTTOM_SENSOR  = 3,

    /**
     * Far sensor error. Error means false-positive sensor reaction
     */
    ERROR_CODE_FAR_SENSOR     = 4,

    /**
     * Near sensor error. Error means false-positive sensor reaction
     */
    ERROR_CODE_NEAR_SENSOR    = 5,

    ERROR_CODE_BOTTOM2_SENSOR = 6,
};

