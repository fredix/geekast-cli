/****************************************************************************
** Copyright (C) 2010-2011 Frédéric Logier
** Contact: Frédéric Logier <frederic@logier.org>
**
** https://github.com/nodecast/geekast-cli
**
** This file is part of Nodecast.
**
** Nodecast is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nodecast is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Nodecast.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "core.h"

QString System::Linux()
{
    m_os_type = "linux";
    m_os_base = "unix";
    return "linux";
}


