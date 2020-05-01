#include <string>
#include <functional>

int watch(std::string path, const std::function<int()> callback);
