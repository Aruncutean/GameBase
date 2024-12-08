//
// Created by arunc on 14/11/2024.
//

#include "graphics/object/LoadObject3d.h"


#include "graphics/material/Material.h"


LoadObject3d::LoadObject3d() {
}

LoadObject3d::~LoadObject3d() {
}

Object3d  *LoadObject3d::load(std::string path) {
    Object3d *object3d = new Object3d();
    std::vector<MeshNEW *> *meshes = new std::vector<MeshNEW *>();
    std::vector<Material *> *materials = new std::vector<Material *>();

    FbxManager *manager = FbxManager::Create();
    if (!manager) {
        std::cerr << "Eșec la crearea managerului FBX!" << std::endl;
    }

    FbxIOSettings *ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxImporter *importer = FbxImporter::Create(manager, "");

    if (!importer->Initialize(path.c_str(), -1, manager->GetIOSettings())) {
        std::cerr << "Eșec la inițializarea importerului FBX: "
                << importer->GetStatus().GetErrorString() << std::endl;
        importer->Destroy();
        return nullptr;
    }

    FbxScene *scene = FbxScene::Create(manager, "My Scene");
    if (!importer->Import(scene)) {
        std::cerr << "Eșec la importul scenei FBX!" << std::endl;
        scene->Destroy();
        importer->Destroy();
        return nullptr;
    }
    importer->Destroy();

    FbxNode *rootNode = scene->GetRootNode();
    if (rootNode) {
        for (int i = 0; i < rootNode->GetChildCount(); i++) {
            FbxMesh *mesh = rootNode->GetChild(i)->GetMesh();
            Vertex *vertex = new Vertex();

            if (mesh) {
                FbxGeometryElementNormal *normalElement = mesh->GetElementNormal();

                FbxGeometryElementUV *uvElement = mesh->GetElementUV();
                FbxLayerElementMaterial *materialElement = mesh->GetElementMaterial();

                FbxLayerElement::EMappingMode mappingMode = materialElement->GetMappingMode();
                FbxLayerElement::EReferenceMode referenceMode = materialElement->GetReferenceMode();

                if (mappingMode != FbxLayerElement::eByPolygon) {
                    std::cout << "Materials are not mapped by polygon. Unsupported configuration.\n";
                }
                const FbxLayerElementArrayTemplate<int> &indexArray = materialElement->GetIndexArray();
                int index = 0;
                for (int j = 0; j < mesh->GetPolygonCount(); ++j) {
                    for (int k = 0; k < mesh->GetPolygonSize(j); ++k) {
                        int indexPosition = mesh->GetPolygonVertex(j, k);
                        FbxVector4 position = mesh->GetControlPointAt(indexPosition);
                        vertex->addVertex(glm::vec3(position[0], position[1], position[2]));

                        if (uvElement) {
                            FbxVector2 uv = uvElement->GetDirectArray().
                                    GetAt(uvElement->GetIndexArray().GetAt(j * 3 + k));
                            vertex->addUV(glm::vec2(uv[0], uv[1]));
                        }
                        if (normalElement) {
                            FbxVector4 normal = normalElement->GetDirectArray().GetAt(
                                normalElement->GetIndexArray().GetAt(j * 3 + k));
                            vertex->addNormal(glm::vec3(normal[0], normal[1], normal[2]));
                        }
                        vertex->addIndices(index);
                        index++;

                        int materialIndex = -1;
                        if (referenceMode == FbxLayerElement::eDirect) {
                            materialIndex = indexArray.GetAt(indexPosition);
                        } else if (referenceMode == FbxLayerElement::eIndexToDirect) {
                            int index = materialElement->GetIndexArray().GetAt(indexPosition);
                            materialIndex = indexArray.GetAt(indexPosition);
                        }
                        FbxSurfaceMaterial *material = rootNode->GetChild(i)->GetMaterial(materialIndex);
                        // if (material) {
                        //     std::cout << "Polygon " << indexPosition << " uses material: " << material->GetName() <<
                        //             "\n";
                        // } else {
                        //     std::cout << "Polygon " << indexPosition << " has no valid material.\n";
                        // }
                    }
                }
                int materialCount = rootNode->GetChild(i)->GetMaterialCount();
                // if (materialCount == 0) {
                //     std::cout << "No materials found on this mesh.\n";
                // }

                FbxNode *node = rootNode->GetChild(i);


                for (int mIndex = 0; mIndex < materialCount; ++mIndex) {
                    FbxSurfaceMaterial *material = node->GetMaterial(mIndex);

                    if (material) {
                        FbxProperty property = material->GetFirstProperty();
                        Material *materialCopy = new Material();
                        materialCopy->setName(material->GetName());

                        FbxProperty diffuseProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
                        if (diffuseProperty.IsValid()) {
                            FbxColor diffuseColor = diffuseProperty.Get<FbxColor>();
                            glm::vec4 baseColor(diffuseColor.mRed, diffuseColor.mGreen, diffuseColor.mBlue,
                                                diffuseColor.mAlpha);
                            materialCopy->setBaseColor(baseColor);
                        }

                        FbxProperty reflectionFactorProperty = material->FindProperty(
                            FbxSurfaceMaterial::sReflectionFactor);
                        if (reflectionFactorProperty.IsValid()) {
                            materialCopy->setMetallic(reflectionFactorProperty.Get<FbxDouble>());
                        } else {
                            materialCopy->setMetallic(0.0);
                        }

                        FbxProperty shininessProperty = material->FindProperty(FbxSurfaceMaterial::sShininess);
                        if (shininessProperty.IsValid()) {
                            double shininess = shininessProperty.Get<FbxDouble>();
                            materialCopy->setRoughness(1.0 - (shininess / 100.0));
                        } else {
                            materialCopy->setRoughness(1.0);
                        }

                        FbxProperty transparencyFactorProperty = material->FindProperty(
                            FbxSurfaceMaterial::sTransparencyFactor);
                        if (transparencyFactorProperty.IsValid()) {
                            materialCopy->setAlpha(1.0 - transparencyFactorProperty.Get<FbxDouble>());
                        } else {
                            materialCopy->setAlpha(1.0);
                        }

                        FbxProperty refractionIndexProperty = material->FindProperty("RefractionIndex");
                        if (refractionIndexProperty.IsValid()) {
                            materialCopy->setIor(refractionIndexProperty.Get<FbxDouble>());
                        } else {
                            materialCopy->setIor(1.5);
                        }
                        materials->push_back(materialCopy);
                    } else {
                        std::cout << "Material " << i << ": (null)\n";
                    }
                }
            }

            MeshNEW *meshNew = new MeshNEW(vertex);

            meshes->push_back(meshNew);
            object3d->setMaterial(materials);
        }
    }


    object3d->setMeshNew(meshes);
    scene->Destroy();
    manager->Destroy();
    return object3d;
}
