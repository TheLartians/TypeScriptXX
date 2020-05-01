#include <functional>
#include <string>

int watch(std::string path, const std::function<int()> callback);
