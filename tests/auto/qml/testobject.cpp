/****************************************************************************
**
** Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Milian Wolff <milian.wolff@kdab.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebChannel module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "testobject.h"


QT_BEGIN_NAMESPACE

TestObject::TestObject(QObject* parent)
    : QObject(parent)
    , embeddedObject(new QObject(this))
{
    embeddedObject->setObjectName("embedded");
}

TestObject::~TestObject()
{
}

QVariantMap TestObject::objectMap() const
{
    QVariantMap map;
    map.insert("subObject", QVariant::fromValue(embeddedObject));
    return map;
}

QString TestObject::stringProperty() const
{
    return m_stringProperty;
}

void TestObject::triggerSignals()
{
    emit testSignalBool(true);
    emit testSignalBool(false);

    emit testSignalInt(42);
    emit testSignalInt(1);
    emit testSignalInt(0);
}

int TestObject::testOverload(int i)
{
    emit testOverloadSignal(i);
    return i + 1;
}

QString TestObject::testOverload(const QString &str)
{
    emit testOverloadSignal(str);
    return str.toUpper();
}

QString TestObject::testOverload(const QString &str, int i)
{
    emit testOverloadSignal(str, i);
    return str.toUpper() + QString::number(i + 1);
}

int TestObject::testVariantType(const QVariant &val)
{
    return val.metaType().id();
}

bool TestObject::testEmbeddedObjects(const QVariantList &list)
{
    return list.size() == 2 &&
            list[0].metaType().id() == QMetaType::QObjectStar &&
            list[1].metaType().id() == QMetaType::QVariantMap &&
            list[1].toMap()["obj"].metaType().id() == QMetaType::QObjectStar;
}

void TestObject::setStringProperty(const QString &stringProperty)
{
    m_stringProperty = stringProperty;
}

QT_END_NAMESPACE
