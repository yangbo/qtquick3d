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

#ifndef ASSIMPIMPORTER_H
#define ASSIMPIMPORTER_H

#include <QtQuick3DAssetImport/private/qssgassetimporter_p.h>
#include <QtQuick3DAssetUtils/private/qssgqmlutilities_p.h>

#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtCore/QHash>
#include <QtCore/QTemporaryDir>
#include <QtCore/QSet>
#include <QtCore/QVariant>
#include <QtCore/QCborStreamWriter>

#include "assimputils.h"

#include <assimp/matrix4x4.h>
#include <assimp/material.h>
#include <assimp/anim.h>
#include <assimp/postprocess.h>

namespace Assimp {
class Importer;
}

struct aiNode;
struct aiCamera;
struct aiLight;
struct aiScene;
struct aiMesh;
struct aiAnimMesh;
struct aiBone;
struct weightKey {
    weightKey(double time, double value) {
        mTime = time;
        mValue = value;
    }
    double mTime;
    double mValue;
};

enum class QSSGRenderComponentType;

QT_BEGIN_NAMESPACE

class AssimpImporter : public QSSGAssetImporter
{
public:
    AssimpImporter();
    ~AssimpImporter() override;

    const QString name() const override;
    const QStringList inputExtensions() const override;
    const QString outputExtension() const override;
    const QString type() const override;
    const QString typeDescription() const override;
    const QVariantMap importOptions() const override;
    const QString import(const QString &sourceFile, const QDir &savePath, const QVariantMap &options,
                         QStringList *generatedFiles) override;
    QString import(const QUrl &sourceFile, const QVariantMap &options, QSSGSceneDesc::Scene &scene) override;

private:
    void writeHeader(QTextStream &output);
    void processScene(QTextStream &output);
    void processNode(aiNode *node, QTextStream &output, int tabLevel = 1);
    void generateModelProperties(aiNode *modelNode, QTextStream &output, int tabLevel);
    QSSGQmlUtilities::PropertyMap::Type generateLightProperties(aiNode *lightNode, QTextStream &output, int tabLevel);
    QSSGQmlUtilities::PropertyMap::Type generateCameraProperties(aiNode *cameraNode, QTextStream &output, int tabLevel);
    void generateNodeProperties(aiNode *node, QTextStream &output, int tabLevel, aiMatrix4x4 *transformCorrection = nullptr, bool skipScaling = false);
    QString generateMeshFile(aiNode *node, QFile &file, const AssimpUtils::MeshList &meshes);
    void processMaterials(QTextStream &output);
    void generateMaterial(aiMaterial *material, QTextStream &output, int tabLevel = 1);
    QVector<QString> generateMorphing(aiNode *node, const AssimpUtils::MeshList &meshes, QTextStream &output, int tabLevel);
    QString generateImage(aiMaterial *material, aiTextureType textureType, unsigned index, int tabLevel);
    void processAnimations(QTextStream &output);
    template <typename T>
    void generateKeyframes(const QString &id, const QString &propertyName,
                           uint numKeys, const T *keys,
                           QTextStream &output, qreal animFreq, qreal &maxKeyframeTime);
    template <typename T>
    bool generateAnimationFile(QFile &file, const QList<T> &keyframes);
    void generateMorphKeyframes(const QString &id,
                                uint numKeys, const aiMeshMorphKey *keys,
                                QTextStream &output,
                                qreal animFreq, qreal &maxKeyframeTime);

    bool isModel(aiNode *node);
    bool isLight(aiNode *node);
    bool isCamera(aiNode *node);
    bool isBone(aiNode *node);
    QString generateUniqueId(const QString &id);
    void processOptions(const QVariantMap &options);
    bool checkBooleanOption(const QString &optionName, const QJsonObject &options);
    qreal getRealOption(const QString &optionName, const QJsonObject &options);

    Assimp::Importer *m_importer = nullptr;
    const aiScene *m_scene = nullptr;

    QHash<aiNode *, aiCamera *> m_cameras;
    QHash<aiNode *, aiLight *> m_lights;

    QVector<QHash<aiNode *, aiNodeAnim *> *> m_animations;
    QVector<QHash<aiNode *, aiMeshMorphAnim *> *> m_morphAnimations;
    // aiAnimation has mTicksPerSecond in order to correct the timing.
    // m_animFreqs[i] stores (1000 / mTicksPerSecond)
    //                   for m_animations[i] and m_morphAnimations[i]
    QVector<qreal> m_animFreqs;
    QHash<aiMaterial *, QString> m_materialIdMap;
    QSet<QString> m_uniqueIds;
    QHash<aiNode *, QString> m_nodeIdMap;
    QHash<aiNode *, QSSGQmlUtilities::PropertyMap::Type> m_nodeTypeMap;

    QDir m_savePath;
    QFileInfo m_sourceFile;
    QStringList m_generatedFiles;
    QMap<int, QString> m_embeddedTextureSources; // id -> destination path

    bool m_gltfMode = false;
    bool m_gltfUsed = false;
    bool m_binaryKeyframes = false;
    bool m_forceMipMapGeneration = false;
    bool m_useFloatJointIndices = false;
    bool m_generateLightmapUV = false;
    qreal m_globalScaleValue = 1.0;

    QVariantMap m_options;
    aiPostProcessSteps m_postProcessSteps;

};

QT_END_NAMESPACE

#endif // ASSIMPIMPORTER_H
