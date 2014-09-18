#pragma once

#include "WindowCapture.h"

#include <ApplicationServices/ApplicationServices.h>
#include <QTimer>

using std::string;

// FindWindow is quite intensive in terms of performance
#define OSX_UPDATE_WINDOW_DATA_INTERVAL 3000 // ms

class OSXWindowCapture : public QObject, public WindowCapture
{
Q_OBJECT

private:
  QTimer*  mTimer;
  string   mWindowName;
  int      mWinId;
  CGRect   mRect;

  static int FindWindow( const string& name );
  static bool WindowRect( int windowId, CGRect *rect );

  bool Fullscreen();

private slots:
  void Update();

public:
  OSXWindowCapture( const string& windowName );

  bool WindowFound();
  int Width();
  int Height();

  QPixmap Capture( int x, int y, int w, int h );
};
