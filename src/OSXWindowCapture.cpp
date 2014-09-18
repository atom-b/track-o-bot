#include "OSXWindowCapture.h"

using std::string;

// remove the window title bar which we are not interested in
#define OSX_WINDOW_TITLE_BAR_HEIGHT 22

OSXWindowCapture::OSXWindowCapture( const string& windowName )
  : mWindowName( windowName ), mWinId( 0 )
{
  mTimer = new QTimer( this );
  connect( mTimer, SIGNAL( timeout() ), this, SLOT( Update() ) );
  mTimer->start( OSX_UPDATE_WINDOW_DATA_INTERVAL );

  Update();
}

void OSXWindowCapture::Update() {
  if( mWinId == 0 ) {
    mWinId = FindWindow( mWindowName );
  }

  if( mWinId && !WindowRect( mWinId, &mRect ) ) {
    // Window became invalid
    mWinId = 0;
  }
}

bool OSXWindowCapture::WindowFound() {
  return mWinId != 0;
}

int OSXWindowCapture::Width() {
  return CGRectGetWidth( mRect );
}

int OSXWindowCapture::Height() {
  int height = CGRectGetHeight( mRect );
  return Fullscreen() ? height : std::max< int >( height - OSX_WINDOW_TITLE_BAR_HEIGHT, 0 );
}

QPixmap OSXWindowCapture::Capture( int x, int y, int w, int h ) {
  CGRect captureRect = CGRectMake(
      x + CGRectGetMinX( mRect ),
      y + CGRectGetMinY( mRect ) + ( Fullscreen() ? 0 : OSX_WINDOW_TITLE_BAR_HEIGHT ),
      w,
      h );

  CGImageRef image = CGWindowListCreateImage( captureRect,
      kCGWindowListOptionIncludingWindow,
      mWinId,
      kCGWindowImageNominalResolution | kCGWindowImageBoundsIgnoreFraming );

  QPixmap pixmap = QPixmap::fromMacCGImageRef( image );
  CGImageRelease( image );

  return pixmap;
}

bool OSXWindowCapture::Fullscreen() {
  // this is not the most elegant solution, but I couldn't find a better way
  return CGRectGetMinX( mRect ) == 0.0f && CGRectGetMinY( mRect ) == 0.0f &&
    ( int( CGRectGetHeight( mRect ) ) & OSX_WINDOW_TITLE_BAR_HEIGHT ) != OSX_WINDOW_TITLE_BAR_HEIGHT;
}

int OSXWindowCapture::FindWindow( const string& name ) {
  int winId = 0;

  CFArrayRef windowList = CGWindowListCopyWindowInfo(
      kCGWindowListExcludeDesktopElements,
      kCGNullWindowID );
  CFIndex numWindows = CFArrayGetCount( windowList );

  CFStringRef nameRef = CFStringCreateWithCString( kCFAllocatorDefault, name.c_str(), kCFStringEncodingMacRoman );

  for( int i = 0; i < (int)numWindows; i++ ) {
    CFDictionaryRef info = ( CFDictionaryRef )CFArrayGetValueAtIndex( windowList, i);
    CFStringRef thisWindowName = ( CFStringRef )CFDictionaryGetValue( info, kCGWindowName );
    CFStringRef thisWindowOwnerName = ( CFStringRef )CFDictionaryGetValue( info, kCGWindowOwnerName );
    CFNumberRef thisWindowNumber = ( CFNumberRef )CFDictionaryGetValue( info, kCGWindowNumber );

    if( thisWindowOwnerName && CFStringCompare( thisWindowOwnerName, nameRef, 0 ) == kCFCompareEqualTo ) {
      if( thisWindowName && CFStringCompare( thisWindowName, nameRef, 0 ) == kCFCompareEqualTo ) {
        CFNumberGetValue( thisWindowNumber, kCFNumberIntType, &winId );
        break;
      }
    }
  }

  CFRelease(nameRef);
  CFRelease(windowList);

  return winId;
}

bool OSXWindowCapture::WindowRect( int windowId, CGRect *rect ) {
  CFArrayRef windowList = CGWindowListCopyWindowInfo( kCGWindowListOptionIncludingWindow, windowId );
  CFIndex numWindows = CFArrayGetCount( windowList );

  if( numWindows > 0 ) {
    CFDictionaryRef info = ( CFDictionaryRef )CFArrayGetValueAtIndex( windowList, 0 );
    CGRectMakeWithDictionaryRepresentation( ( CFDictionaryRef )CFDictionaryGetValue( info, kCGWindowBounds ), rect);
  }

  CFRelease( windowList );
  return numWindows > 0;
}
