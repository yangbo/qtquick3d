/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
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

import QtQuick 2.12
import QtQuick3D 1.0
import QtQuick3D.Materials 1.0

CustomMaterial {

    property bool uEnvironmentMappingEnabled: true
    property bool uShadowMappingEnabled: false
    property real roughness: 0.3
    property vector3d base_color: Qt.vector3d(0.7, 0.7, 0.7)
    property real intensity: 1.0
    property vector3d emission_color: Qt.vector3d(0, 0, 0)


    shaderInfo: ShaderInfo {
        version: "330"
        type: "GLSL"
        shaderKey: ShaderInfo.Glossy
    }

    property TextureInput emissive_texture: TextureInput {
            id: emissiveTexture
            type: TextureInput.Emissive
            enabled: true
            texture: Texture {
                id: emissiveImage
                tilingModeHorizontal: Texture.Repeat
                tilingModeVertical: Texture.Repeat
                source: "maps/emissive.png"
            }
    }

    property TextureInput emissive_mask_texture: TextureInput {
            id: emissiveMaskTexture
            type: TextureInput.Unknown
            enabled: true
            texture: Texture {
                id: emissiveMaskImage
                tilingModeHorizontal: Texture.Repeat
                tilingModeVertical: Texture.Repeat
                source: "maps/emissive_mask.png"
            }
    }

    property TextureInput uEnvironmentTexture: TextureInput {
            id: uEnvironmentTexture
            type: TextureInput.Environment
            enabled: uEnvironmentMappingEnabled
            texture: Texture {
                id: envImage
                tilingModeHorizontal: Texture.Repeat
                tilingModeVertical: Texture.Repeat
                source: "maps/spherical_checker.png"
            }
    }
    property TextureInput uBakedShadowTexture: TextureInput {
            type: TextureInput.LightmapShadow
            enabled: uShadowMappingEnabled
            texture: Texture {
                id: shadowImage
                tilingModeHorizontal: Texture.Repeat
                tilingModeVertical: Texture.Repeat
                source: "maps/shadow.png"
            }
    }

    Shader {
        id: aluminumAnodizedEmissiveShader
        stage: Shader.Fragment
        shader: "shaders/aluminumAnodizedEmissive.frag"
    }

    passes: [
        Pass {
            shaders: aluminumAnodizedEmissiveShader
        }
    ]

}
