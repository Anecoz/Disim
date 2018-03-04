#pragma once

#include "Application.h"

class DisimApplication : public Application
{
public:
  DisimApplication() = default;
  ~DisimApplication() = default;

  void render() override;
  void update(double delta) override;
};