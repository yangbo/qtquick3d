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


import QtQuick 2.15
import HelperWidgets 2.0
import QtQuick.Layouts 1.12
import StudioTheme 1.0 as StudioTheme

Section {
    caption: qsTr("Particle Target Direction")
    width: parent.width
    SectionLayout {

        Label {
            text: qsTr("Position")
            tooltip: qsTr("This property defines the position for particles target.")
        }
        ColumnLayout {
            RowLayout {
                spacing: 0

                Label {
                    text: qsTr("X")
                    width: 100
                    color: StudioTheme.Values.theme3DAxisXColor
                }
                SpinBox {
                    maximumValue: 9999999
                    minimumValue: -9999999
                    realDragRange: 5000
                    decimals: 2
                    backendValue: backendValues.position_x
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                }
            }
            RowLayout {
                spacing: 0

                Label {
                    text: qsTr("Y")
                    width: 100
                    color: StudioTheme.Values.theme3DAxisYColor
                }
                SpinBox {
                    maximumValue: 9999999
                    minimumValue: -9999999
                    realDragRange: 5000
                    decimals: 2
                    backendValue: backendValues.position_y
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                }
            }
            RowLayout {
                spacing: 0

                Label {
                    text: qsTr("Z")
                    width: 100
                    color: StudioTheme.Values.theme3DAxisZColor
                }
                SpinBox {
                    maximumValue: 9999999
                    minimumValue: -9999999
                    realDragRange: 5000
                    decimals: 2
                    backendValue: backendValues.position_z
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                }
            }
        }

        Label {
            text: qsTr("Position Variation")
            tooltip: qsTr("This property defines the position variation for particles target.")
        }
        ColumnLayout {
            RowLayout {
                spacing: 0

                Label {
                    text: qsTr("X")
                    width: 100
                    color: StudioTheme.Values.theme3DAxisXColor
                }
                SpinBox {
                    maximumValue: 9999999
                    minimumValue: -9999999
                    realDragRange: 5000
                    decimals: 2
                    backendValue: backendValues.positionVariation_x
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                }
            }
            RowLayout {
                spacing: 0

                Label {
                    text: qsTr("Y")
                    width: 100
                    color: StudioTheme.Values.theme3DAxisYColor
                }
                SpinBox {
                    maximumValue: 9999999
                    minimumValue: -9999999
                    realDragRange: 5000
                    decimals: 2
                    backendValue: backendValues.positionVariation_y
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                }
            }
            RowLayout {
                spacing: 0

                Label {
                    text: qsTr("Z")
                    width: 100
                    color: StudioTheme.Values.theme3DAxisZColor
                }
                SpinBox {
                    maximumValue: 9999999
                    minimumValue: -9999999
                    realDragRange: 5000
                    decimals: 2
                    backendValue: backendValues.positionVariation_z
                    Layout.fillWidth: true
                    Layout.minimumWidth: 0
                }
            }
        }

        Label {
            text: qsTr("Normalized")
            tooltip: qsTr("This property defines if the distance to position should be considered as normalized or not.")
        }
        SecondColumnLayout {
            CheckBox {
                id: normalizedCheckBox
                text: backendValues.normalized.valueToString
                backendValue: backendValues.normalized
                Layout.fillWidth: true
            }
        }

        Label {
            text: qsTr("Magnitude")
            tooltip: qsTr("This property defines the magnitude in position change per second.")
        }
        SecondColumnLayout {
            SpinBox {
                maximumValue: 999999
                minimumValue: -999999
                realDragRange: 5000
                decimals: 2
                backendValue: backendValues.magnitude
                Layout.fillWidth: true
            }
        }

        Label {
            text: qsTr("Magnitude Variation")
            tooltip: qsTr("This property defines the magnitude variation in position change per second.")
        }
        SecondColumnLayout {
            SpinBox {
                maximumValue: 999999
                minimumValue: -999999
                realDragRange: 5000
                decimals: 2
                backendValue: backendValues.magnitudeVariation
                Layout.fillWidth: true
            }
        }
    }

}
