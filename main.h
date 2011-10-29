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

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <QDebug>
#include <QDomDocument>
#include <QSettings>
#include <QxtCore/QxtCommandOptions>
#include "core.h"
#include "push.h"



class Payload : public QObject
{
    Q_OBJECT
public:
    Payload();
    ~Payload();

private:
    void refresh();
    Datas *datas;
    Push push;
    QByteArray *p_datas;   


public slots:
    void update();
private slots:
    void on_push_uuidChanged(QString uuid);
};

#endif // MAIN_H
