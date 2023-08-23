extern rw::EngineOpenParams engineOpenParams;

namespace sk {

using namespace rw;

// same as RW skeleton
enum Key
{
	// ascii...

	KEY_ESC   = 128,

	KEY_F1    = 129,
	KEY_F2    = 130,
	KEY_F3    = 131,
	KEY_F4    = 132,
	KEY_F5    = 133,
	KEY_F6    = 134,
	KEY_F7    = 135,
	KEY_F8    = 136,
	KEY_F9    = 137,
	KEY_F10   = 138,
	KEY_F11   = 139,
	KEY_F12   = 140,

	KEY_INS   = 141,
	KEY_DEL   = 142,
	KEY_HOME  = 143,
	KEY_END   = 144,
	KEY_PGUP  = 145,
	KEY_PGDN  = 146,

	KEY_UP    = 147,
	KEY_DOWN  = 148,
	KEY_LEFT  = 149,
	KEY_RIGHT = 150,

	// some stuff ommitted

	KEY_BACKSP = 168,
	KEY_TAB    = 169,
	KEY_CAPSLK = 170,
	KEY_ENTER  = 171,
	KEY_LSHIFT = 172,
	KEY_RSHIFT = 173,
	KEY_LCTRL  = 174,
	KEY_RCTRL  = 175,
	KEY_LALT   = 176,
	KEY_RALT   = 177,

	KEY_NULL,	// unused
	KEY_NUMKEYS,
};

enum EventStatus
{
	EVENTERROR,
	EVENTPROCESSED,
	EVENTNOTPROCESSED
};

enum Event
{
	INITIALIZE,
	RWINITIALIZE,
	RWTERMINATE,
	SELECTDEVICE,
	PLUGINATTACH,
	KEYDOWN,
	KEYUP,
	CHARINPUT,
	MOUSEMOVE,
	MOUSEBTN,
	MOUSEWHEEL,
	MOUSEHWHEEL,
	RESIZE,
	IDLE,
	QUIT
};

struct Globals
{
	const char *windowtitle;
	rw::int32 width;
	rw::int32 height;
	rw::bool32 quit;
	rw::bool32 minimized;
	rw::bool32 fpslimit;
	rw::float32 maxfps;
};
extern Globals globals;

// Argument to mouse events
struct MouseState
{
	int posx, posy;
	int buttons;	// bits 0-2 are left, middle, right button down
};

struct Args
{
	int argc;
	char **argv;
};
extern Args args;

bool InitRW(void);
void TerminateRW(void);
rw::Camera *CameraCreate(rw::int32 width, rw::int32 height, rw::bool32 z);
void CameraDestroy(rw::Camera *cam);
void CameraSize(rw::Camera *cam, rw::Rect *r, float viewWindow = 0.0f, float aspectRatio = 0.0f);
void CameraMove(rw::Camera *cam, rw::V3d *delta);
void CameraPan(rw::Camera *cam, rw::V3d *pos, float angle);
void CameraTilt(rw::Camera *cam, rw::V3d *pos, float angle);
void CameraRotate(rw::Camera *cam, rw::V3d *pos, float angle);
void SetMousePosition(int x, int y);
EventStatus EventHandler(Event e, void *param);

}

sk::EventStatus AppEventHandler(sk::Event e, void *param);

#include "imgui/imgui.h"
#include "imgui/imgui_impl_rw.h"
