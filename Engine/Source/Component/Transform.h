#pragma once
#include "Eigen/core"
class Transform
{
  public:
    Transform() = default;
    Transform(Eigen::Vector3f position,
              Eigen::Vector3f rotation,
              Eigen::Vector3f scale)
      : mPosition(position)
      , mRotation(rotation)
      , mScale(scale)
    {
    }
    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void SetScale(float x, float y, float z);
    float GetPosX() const { return mPosition.x(); }
    float GetPosY() const { return mPosition.y(); }
    float GetPosZ() const { return mPosition.z(); }
    float GetScaleX() const { return mScale.x(); }
    float GetScaleY() const { return mScale.y(); }
    float GetScaleZ() const { return mScale.z(); }

private:
    Eigen::Vector3f mPosition{ 0.0f };
    Eigen::Vector3f mRotation{ 0.0f };
    Eigen::Vector3f mScale{ 0.0f };
};