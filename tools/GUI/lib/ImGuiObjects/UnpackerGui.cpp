#include "ImGuiObjects/UnpackerGui.h"

#include <Logger/Logger.h>
#include <Support/DiskSingleton.h>
#include <Unpacker/Unpacker.h>

// vendor
#include <imgui.h>

// stl
#include <iostream>

namespace UIObjects {

namespace {
void Unpack() {
  auto &disk = Support::DiskSingleton::GetSingleton();
  if (disk.ProjectDir.empty()) {
    Support::ChooseProjectDir();
  }
  LOG_INFO("Output dir: {}", disk.ProjectDir.string());

  Unpacking::UnpackerOptions options{disk.Iso, disk.Dump, disk.ProjectDir};

  Unpacking::Unpacker unpacker(options);
  unpacker.Dump();
  if (!unpacker.Unpack()) {
    LOG_ERROR("Failed to unpack '{}'", disk.Iso.string());
  }
  LOG_INFO("Unpacking done");
}

} // namespace

void UnpackerGui::OnInit() {}

void UnpackerGui::OnBeginDraw() {
  ImGui::Begin("Unpacker");

  if (ImGui::Button("Unpack")) {
    Unpack();
  }
  ImGui::Separator();
}

void UnpackerGui::OnEndDraw() { ImGui::End(); }

} // namespace UIObjects
