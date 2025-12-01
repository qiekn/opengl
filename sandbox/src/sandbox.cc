#include "glcore/core/core.hh"
#include "sandbox_layer.hh"

using namespace core;

class Sandbox : public Application {
public:
  Sandbox() { PushLayer(CreateScope<SandboxLayer>()); }
};

int main() {
  Scope<Sandbox> app = CreateScope<Sandbox>();
  app->Run();
}
