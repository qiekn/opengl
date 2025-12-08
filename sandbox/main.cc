#include "glcore/core/core.hh"
#include "hello_triangle.hh"

using namespace core;

class Sandbox : public Application {
public:
  Sandbox() {
    // Test the first triangle
    PushLayer(CreateScope<HelloTriangle>());
  }
};

int main() {
  Scope<Sandbox> app = CreateScope<Sandbox>();
  app->Run();
}
