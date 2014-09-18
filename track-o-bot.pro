######################################################################
# Automatically generated by qmake (2.01a) Thu Sep 18 00:31:39 2014
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src test tmp src/Scenes
INCLUDEPATH += . src src/Scenes test

# Input
HEADERS += src/Autostart.h \
           src/CocoaInitializer.h \
           src/Core.h \
           src/GeneratedMarkers.h \
           src/Hearthstone.h \
           src/HearthstoneLogTracker.h \
           src/HearthstoneLogWatcher.h \
           src/Json.h \
           src/Local.h \
           src/Logger.h \
           src/OSXWindowCapture.h \
           src/Phash.h \
           src/SceneManager.h \
           src/SparkleUpdater.h \
           src/Tracker.h \
           src/Updater.h \
           src/Window.h \
           src/WindowCapture.h \
           src/WinSparkleUpdater.h \
           src/WinWindowCapture.h \
           test/MockWindowCapture.h \
           src/Scenes/ArenaScene.h \
           src/Scenes/ClassSelectionScene.h \
           src/Scenes/ConstructedScene.h \
           src/Scenes/IngameScene.h \
           src/Scenes/MainMenuScene.h \
           src/Scenes/Scene.h \
           src/Scenes/ShiftDetector.h \
           src/Scenes/SoloAdventuresScene.h
FORMS += src/AboutWidget.ui \
         src/LogWidget.ui \
         src/MainWindow.ui \
         src/SettingsWidget.ui \
         src/Window.ui
SOURCES += src/Autostart.cpp \
           src/Core.cpp \
           src/Hearthstone.cpp \
           src/HearthstoneLogTracker.cpp \
           src/HearthstoneLogWatcher.cpp \
           src/Json.cpp \
           src/Logger.cpp \
           src/Main.cpp \
           src/OSXWindowCapture.cpp \
           src/Phash.cpp \
           src/SceneManager.cpp \
           src/Tracker.cpp \
           src/Window.cpp \
           src/WinSparkleUpdater.cpp \
           src/WinWindowCapture.cpp \
           test/HearthstoneTest.cpp
RESOURCES += app.qrc markers.qrc
