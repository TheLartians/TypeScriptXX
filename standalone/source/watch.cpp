#include "watch.h"

#include <FileWatcher/FileWatcher.h>

#include <chrono>
#include <iostream>
#include <thread>

int watch(std::string path, const std::function<int()> callback) {
  std::cout << "Enter watch mode. watching: " << path << std::endl;
  struct ChangeListener : public FW::FileWatchListener {
    bool changed;
    void handleFileAction(FW::WatchID, const FW::String &, const FW::String &, FW::Action) {
      changed = true;
    }
  } listener;
  FW::FileWatcher fileWatcher;
  fileWatcher.addWatch(path, &listener, true);
  while (true) {
    listener.changed = false;
    fileWatcher.update();
    if (listener.changed) {
      try {
        callback();
      } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
