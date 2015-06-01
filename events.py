
class Event:
    def __init__(self):
        self._listeners = []

    def attach(self, listener):
        if listener not in self._listeners:
            self._listeners.append(listener)

    def detach(self, listener):
        self._listeners.remove(listener)

    def notify(self):
        for listener in self._listeners:
            listener.update(self)

    def keyloop(context):
        pass

class ExitListener:
    def update(self, app):
        if app.event.get_last_ch() == ord('q'):
            app.exit()

