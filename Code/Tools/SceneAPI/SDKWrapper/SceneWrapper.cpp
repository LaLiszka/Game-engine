/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include <SceneAPI/SDKWrapper/SceneWrapper.h>

namespace AZ
{
   namespace SDKScene
   {
      const char* SceneWrapperBase::s_defaultSceneName = "myScene";

      SceneWrapperBase::SceneWrapperBase(fbxsdk::FbxScene* fbxScene)
          :m_fbxScene(fbxScene)
          , m_assImpScene(nullptr)
      {
      }

      SceneWrapperBase::SceneWrapperBase(aiScene* aiScene)
          :m_fbxScene(nullptr)
          , m_assImpScene(aiScene)
      {
      }


      bool SceneWrapperBase::LoadSceneFromFile([[maybe_unused]] const char* fileName)
      {
          return false;
      }
      bool SceneWrapperBase::LoadSceneFromFile([[maybe_unused]] const AZStd::string& fileName)
      {
          return LoadSceneFromFile(fileName.c_str());
      }

      const std::shared_ptr<SDKNode::NodeWrapper> SceneWrapperBase::GetRootNode() const
      {
          return {};
      }
      std::shared_ptr<SDKNode::NodeWrapper> SceneWrapperBase::GetRootNode()
      {
          return {};
      }

      void SceneWrapperBase::Clear()
      {
      }

      fbxsdk::FbxScene* SceneWrapperBase::GetFbxScene() const
      {
          return m_fbxScene;
      }

      const aiScene* SceneWrapperBase::GetAssImpScene() const
      {
          return m_assImpScene;
      }


   } //namespace Scene
}// namespace AZ
