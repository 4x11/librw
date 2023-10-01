#include <rw.h>
#include <skeleton.h>

rw::EngineOpenParams engineOpenParams;
rw::Camera *Camera;
rw::Texture *Texture;

rw::RGBA BackgroundColor = {64, 64, 64, 0};

void
Initialize(void)
{
    sk::globals.windowtitle = "Draw raster";
    sk::globals.width = 640;
    sk::globals.height = 480;
    sk::globals.quit = 0;
}

bool
Initialize3D(void)
{
    if(!sk::InitRW()) return false;

    Camera = sk::CameraCreate(sk::globals.width, sk::globals.height, 1);
    Texture = rw::Texture::read("files/whiteash", nil);

    return true;
}

void
Terminate3D(void)
{
    Texture->destroy();
    Camera->destroy();
    sk::TerminateRW();
}

void
Render(void)
{
    Camera->clear(&BackgroundColor, rw::Camera::CLEARIMAGE | rw::Camera::CLEARZ);

    Camera->beginUpdate();

    rw::RWDEVICE::Im2DVertex TriFan[4];
    float recipZ = 1.0f / Camera->nearPlane;
    for(int i = 0; i < 4; i++) {
        TriFan[i].setScreenZ(rw::im2d::GetNearZ());
        TriFan[i].setRecipCameraZ(recipZ);
        TriFan[i].setColor(255, 255, 255, 255);
    }
    TriFan[0].setScreenX(0);
    TriFan[0].setScreenY(0);
    TriFan[0].setU(0.0f, recipZ);
    TriFan[0].setV(0.0f, recipZ);
    TriFan[1].setScreenX(Camera->frameBuffer->width);
    TriFan[1].setScreenY(0);
    TriFan[1].setU(1.0f, recipZ);
    TriFan[1].setV(0.0f, recipZ);
    TriFan[2].setScreenX(Camera->frameBuffer->width);
    TriFan[2].setScreenY(Camera->frameBuffer->height);
    TriFan[2].setU(1.0f, recipZ);
    TriFan[2].setV(1.0f, recipZ);
    TriFan[3].setScreenX(0);
    TriFan[3].setScreenY(Camera->frameBuffer->height);
    TriFan[3].setU(0.0f, recipZ);
    TriFan[3].setV(1.0f, recipZ);

    rw::SetRenderStatePtr(rw::TEXTURERASTER, Texture->raster);
    rw::im2d::RenderPrimitive(rw::PRIMTYPETRIFAN, TriFan, 4);

    Camera->endUpdate();

    Camera->showRaster(0);
}

void
Idle(float timeDelta)
{
    Render();
}

void
KeyDown(int key)
{
    switch(key) {
    case sk::KEY_ESC: sk::globals.quit = 1; break;
    }
}

sk::EventStatus
AppEventHandler(sk::Event e, void *param)
{
    using namespace sk;
    Rect *r;
    MouseState *ms;

    ImGuiEventHandler(e, param);
    ImGuiIO &io = ImGui::GetIO();

    switch(e) {
    case INITIALIZE: Initialize(); return EVENTPROCESSED;
    case RWINITIALIZE: return Initialize3D() ? EVENTPROCESSED : EVENTERROR;
    case RWTERMINATE: Terminate3D(); return EVENTPROCESSED;
    case PLUGINATTACH: return EVENTPROCESSED;
    case KEYDOWN: KeyDown(*(int *)param); return EVENTPROCESSED;
    case KEYUP: return EVENTPROCESSED;
    case MOUSEBTN: return EVENTPROCESSED;
    case MOUSEMOVE: return EVENTPROCESSED;
    case RESIZE:
        r = (Rect *)param;
        // TODO: register when we're minimized
        if(r->w == 0) r->w = 1;
        if(r->h == 0) r->h = 1;

        sk::globals.width = r->w;
        sk::globals.height = r->h;
        if(::Camera) { sk::CameraSize(::Camera, r, 0.5f, 4.0f / 3.0f); }
        break;
    case IDLE: Idle(*(float *)param); return EVENTPROCESSED;
    default: break;
    }
    return sk::EVENTNOTPROCESSED;
}
