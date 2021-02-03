/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Quick 3D.
**
** $QT_BEGIN_LICENSE:GPL$
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
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICK3DPARTICLESHAPE_H
#define QQUICK3DPARTICLESHAPE_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QObject>
#include <QQmlEngine>
#include <QtQuick3D/private/qquick3dnode_p.h>
#include <QtQml/qqmlparserstatus.h>
#include <QtQuick3DParticles/qtquick3dparticlesglobal.h>

QT_BEGIN_NAMESPACE

class Q_QUICK3DPARTICLES_EXPORT QQuick3DParticleShape : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(bool fill READ fill WRITE setFill NOTIFY fillChanged)
    Q_PROPERTY(ShapeType type READ type WRITE setType NOTIFY typeChanged)

    QML_NAMED_ELEMENT(ParticleShape3D)
    Q_INTERFACES(QQmlParserStatus)

public:
    enum ShapeType
    {
        Cube = 0,
        Sphere,
        Cylinder
    };
    Q_ENUM(ShapeType)

    QQuick3DParticleShape(QObject *parent = nullptr);

    bool fill() const;
    ShapeType type() const;

    // Returns random point inside this shape
    QVector3D randomPosition(int particleIndex) const;

public Q_SLOTS:
    void setFill(bool fill);
    void setType(QQuick3DParticleShape::ShapeType type);

protected:
    // From QQmlParserStatus
    void componentComplete() override;
    void classBegin() override {}

Q_SIGNALS:
    void fillChanged();
    void typeChanged();

private:
    QVector3D randomPositionCube(int particleIndex) const;
    QVector3D randomPositionSphere(int particleIndex) const;
    QVector3D randomPositionCylinder(int particleIndex) const;

    QQuick3DNode *m_parentNode = nullptr;
    bool m_fill = false;
    ShapeType m_type = ShapeType::Cube;
};

QT_END_NAMESPACE

#endif // QQUICK3DPARTICLESHAPE_H
