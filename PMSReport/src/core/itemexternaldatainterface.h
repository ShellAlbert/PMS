/***************************************************************************
 *   This file is part of the CuteReport project                           *
 *   Copyright (C) 2012-2017 by Alexander Mikhalov                         *
 *   alexander.mikhalov@gmail.com                                          *
 *                                                                         *
 **                   GNU General Public License Usage                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 **                  GNU Lesser General Public License                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library.                                      *
 *   If not, see <http://www.gnu.org/licenses/>.                           *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ****************************************************************************/
#ifndef ITEMEXTERNALDATAINTERFACE_H
#define ITEMEXTERNALDATAINTERFACE_H

#include <QObject>

#include "cutereport_globals.h"

namespace CuteReport
{

class CUTEREPORT_EXPORTS ItemExternalDataInterface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int _current_property READ _currentProperty WRITE _setCurrentProperty DESIGNABLE false STORED false)
    Q_PROPERTY(QString _current_property_description READ _current_property_description DESIGNABLE false STORED false)
    Q_PROPERTY(int _current_property_precision READ _current_property_precision DESIGNABLE false STORED false)

public:
    explicit ItemExternalDataInterface(QObject * parent);
    virtual ~ItemExternalDataInterface();

    virtual QString typeName() const = 0;

    virtual QByteArray serialize();
    virtual void deserialize(QByteArray &data);

    virtual void _setCurrentProperty(int num) {m_currentProperty = num;}
    virtual int _currentProperty() { return m_currentProperty;}
    virtual QString _current_property_description() const;
    virtual int _current_property_precision() const;

protected:
    int m_currentProperty;

private:
    void initMe();
};


} // namespace

Q_DECLARE_INTERFACE(CuteReport::ItemExternalDataInterface, "CuteReport.ItemExternalDataInterface/1.0")

#endif // ITEMEXTERNALDATAINTERFACE_H
