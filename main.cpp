/****************************************************************************
** Copyright (C) 2010 Frédéric Logier
** Contact: Frédéric Logier <frederic@logier.org>
**
** http://gitorious.org/nodecast/nodecast-cli
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

#include <QtCore/QCoreApplication>
#include "main.h"

QSettings settings("geekast", "geekast-cli");


Payload::Payload()
{
    datas = NULL;
    push.m_credentials  = settings.value("email").toString()+":"+settings.value("key").toString();
    push.m_server = settings.value("server").toString();
    push.m_uuid = settings.value("uuid").toString();


    //connect(&push, SIGNAL(httpResponse(int)), SLOT(on_push_httpResponse(int)));
    connect(&push, SIGNAL(uuidChanged(QString)), SLOT(on_push_uuidChanged(QString)));
}

Payload::~Payload()
{}



void Payload::on_push_uuidChanged(QString uuid)
{
    settings.setValue("uuid",uuid);
}

void Payload::refresh()
{
    std::cout << "refresh " << std::endl;


    datas->activated_hardware = settings.value("activated_hardware").toBool();
    datas->activated_uptime = settings.value("activated_uptime").toBool();
    datas->activated_memory = settings.value("activated_memory").toBool();
    datas->activated_load = settings.value("activated_load").toBool();
    datas->activated_process = settings.value("activated_process").toBool();
    datas->activated_network = settings.value("activated_network").toBool();
    datas->activated_cpu = settings.value("activated_cpu").toBool();
    datas->public_host = settings.value("public").toBool();
}

void Payload::update()
{
    std::cout << "update " << std::endl;

    p_datas = new QByteArray;

    if (!datas) datas = new Datas();
    refresh();

    std::cout << "before populate " << std::endl;
    datas->Populate(p_datas);
    std::cout << "after populate " << std::endl;

    push.Payload(p_datas);
    delete p_datas;
    delete datas;
    datas = NULL;
}


int main(int argc, char *argv[])
{
    QCoreApplication geekast_cli(argc, argv);

    std::cout << "key : " << settings.value("key").toString().toAscii().data() << std::endl;


    Payload payload;


    bool verbose, activated_hardware, activated_uptime, activated_memory, activated_load, activated_process, activated_network, activated_cpu, activated_fs;
    QString device, server, email, key, uuid, profil, l_public;
    int refresh;

    QxtCommandOptions options;
    options.add("debug", "show debug informations");
    options.alias("debug", "d");
    options.add("server", "set the server URL", QxtCommandOptions::Required);
    options.alias("server", "s");
    options.add("email", "set your email account", QxtCommandOptions::Required);
    options.alias("email", "m");
    options.add("key", "set your API key", QxtCommandOptions::Required);
    options.alias("key", "k");
    options.add("uuid", "set the private host UUID", QxtCommandOptions::Required);
    options.alias("uuid", "u");
    options.add("public", "set the public setting", QxtCommandOptions::Required);
    options.alias("public", "p");
    options.add("profil", "set the profil setting", QxtCommandOptions::Required);
    options.alias("profil", "pf");
    options.add("refresh", "set the refresh rate setting", QxtCommandOptions::Required);
    options.alias("refresh", "r");
    options.add("device", "set the device type (desktop|server)", QxtCommandOptions::Required);
    options.alias("device", "d");



    options.add("hardware", "set the push hardware option setting", QxtCommandOptions::Required);
    options.alias("hardware", "ph");
    options.add("uptime", "set the push uptime option setting", QxtCommandOptions::Required);
    options.alias("uptime", "pu");
    options.add("memory", "set the push memory option setting", QxtCommandOptions::Required);
    options.alias("memory", "pm");
    options.add("load", "set the push load option setting", QxtCommandOptions::Required);
    options.alias("load", "pl");
    options.add("process", "set the push process option setting", QxtCommandOptions::Required);
    options.alias("process", "pp");
    options.add("network", "set the push network option setting", QxtCommandOptions::Required);
    options.alias("network", "pn");
    options.add("cpu", "set the push cpu option setting", QxtCommandOptions::Required);
    options.alias("cpu", "pc");
    options.add("fs", "set the push file system option setting", QxtCommandOptions::Required);
    options.alias("fs", "pfs");



    options.add("verbose", "show more information about the process; specify twice for more detail", QxtCommandOptions::AllowMultiple);
    options.alias("verbose", "v");
    options.add("help", "show this help text");
    options.alias("help", "h");
    options.parse(QCoreApplication::arguments());
    if(options.count("help") || options.showUnrecognizedWarning()) {
        options.showUsage();
        return -1;
    }
    verbose = options.count("verbose");

    if(options.count("server")) {
        server = options.value("server").toString();
        settings.setValue("server", server);
    }
    else if(settings.contains("server"))
    {
        server = settings.value("server").toString();
    }
    else {
        std::cout << "geekast-cli: --server requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }

    if(options.count("email")) {
        email = options.value("email").toString();
        settings.setValue("email", email);
    }
    else if(settings.contains("email"))
    {
        email = settings.value("email").toString();
    }
    else {
        std::cout << "geekast-cli: --email requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("key")) {
        key = options.value("key").toString();
        settings.setValue("key", key);
    }
    else if(settings.contains("key"))
    {
        key = settings.value("key").toString();
    }
    else {
        std::cout << "geekast-cli: --key requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("uuid")) {
        uuid = options.value("uuid").toString();
        settings.setValue("uuid", uuid);
    }
    else if(settings.contains("uuid"))
    {
        uuid = settings.value("uuid").toString();
    }
    /*
    else {
        std::cout << "geekast-cli: --uuid requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }
    */

    if(options.count("public")) {
        l_public = options.value("public").toString();
        settings.setValue("public", l_public);
    }
    else if(settings.contains("public"))
    {
        l_public = settings.value("public").toString();
    }
    else {
        std::cout << "geekast-cli: --public requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("profil")) {
        profil = options.value("profil").toString();
        settings.setValue("profil", profil);
    }
    else if(settings.contains("profil"))
    {
        profil = settings.value("profil").toString();
    }
    else {
        std::cout << "geekast-cli: --profil requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("refresh")) {
        refresh = options.value("refresh").toInt();
        settings.setValue("refresh", refresh);
    }
    else if(settings.contains("refresh"))
    {
        refresh = settings.value("refresh").toInt();
    }
    else {
        std::cout << "geekast-cli: --refresh requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("device")) {
        device = options.value("device").toString();
        settings.setValue("device", device);
    }
    else if(settings.contains("device"))
    {
        device = settings.value("device").toString();
    }
    else {
        std::cout << "geekast-cli: --device requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }




    if(options.count("hardware")) {
        activated_hardware = options.value("hardware").toBool();
        settings.setValue("activated_hardware", activated_hardware);
    }
    else if(settings.contains("activated_hardware"))
    {
        activated_hardware = settings.value("activated_hardware").toBool();
    }
    else {
        std::cout << "geekast-cli: --hardware requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("uptime")) {
        activated_uptime = options.value("uptime").toBool();
        settings.setValue("activated_uptime", activated_uptime);
    }
    else if(settings.contains("activated_uptime"))
    {
        activated_uptime = settings.value("activated_uptime").toBool();
    }
    else {
        std::cout << "geekast-cli: --uptime requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("memory")) {
        activated_memory = options.value("memory").toBool();
        settings.setValue("activated_memory", activated_memory);
    }
    else if(settings.contains("activated_memory"))
    {
        activated_memory = settings.value("activated_memory").toBool();
    }
    else {
        std::cout << "geekast-cli: --memory requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }

    if(options.count("load")) {
        activated_load = options.value("load").toBool();
        settings.setValue("activated_load", activated_load);
    }
    else if(settings.contains("activated_load"))
    {
        activated_load = settings.value("activated_load").toBool();
    }
    else {
        std::cout << "geekast-cli: --load requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("process")) {
        activated_process = options.value("process").toBool();
        settings.setValue("activated_process", activated_process);
    }
    else if(settings.contains("activated_process"))
    {
        activated_process = settings.value("activated_process").toBool();
    }
    else {
        std::cout << "geekast-cli: --process requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }


    if(options.count("network")) {
        activated_network = options.value("network").toBool();
        settings.setValue("activated_network", activated_network);
    }
    else if(settings.contains("activated_network"))
    {
        activated_network = settings.value("activated_network").toBool();
    }
    else {
        std::cout << "geekast-cli: --network requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }

    if(options.count("cpu")) {
        activated_cpu = options.value("cpu").toBool();
        settings.setValue("activated_cpu", activated_cpu);
    }
    else if(settings.contains("activated_cpu"))
    {
        activated_cpu = settings.value("activated_cpu").toBool();
    }
    else {
        std::cout << "geekast-cli: --cpu requires a parameter" << std::endl;
        options.showUsage();
        return -1;
    }



    QTimer m_timer;
    m_timer.setInterval(settings.value("refresh").toInt()*60*1000);
    QObject::connect(&m_timer, SIGNAL(timeout()), &payload, SLOT(update()));
    m_timer.start();


    return geekast_cli.exec();
}
