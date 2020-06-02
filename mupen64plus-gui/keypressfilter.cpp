#include "keypressfilter.h"
#include "core_interface.h"
#include "common.h"
#include <QKeyEvent>

KeyPressFilter::KeyPressFilter(QObject *parent)
    : QObject(parent)
{
}

bool KeyPressFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        if (coreStarted) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            int modValue = QT2SDL2MOD(keyEvent->modifiers());
            int keyValue = QT2SDL2(keyEvent->key());
            if (keyValue != 0)
                (*CoreDoCommand)(M64CMD_SEND_SDL_KEYDOWN, (modValue << 16) + keyValue, NULL);
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease){
        if (coreStarted) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            int modValue = QT2SDL2MOD(keyEvent->modifiers());
            int keyValue = QT2SDL2(keyEvent->key());
            if (keyValue != 0)
                (*CoreDoCommand)(M64CMD_SEND_SDL_KEYUP, (modValue << 16) + keyValue, NULL);
        }
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}