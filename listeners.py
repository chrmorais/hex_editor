import curses


class Listener:
    def update(self, app):
        pass


class ExitListiner(Listener):
    def update(self, app):
        last_event = app.event_history[-1]

        if last_event.type != 'key_press':
            return

        if last_event.data['key'] == ord('q'):
            app.exit()


class MoveByteGridCursorListiner(Listener):
    def update(self, app):
        last_event = app.event_history[-1]

        if last_event.type != 'key_press':
            return

        old_cursor = app.byte_grid.cursor_position

        delta_row, delta_col = 0, 0
        key = last_event.data['key']
        if key == curses.KEY_UP:
            delta_row = -1
        elif key == curses.KEY_RIGHT:
            delta_col = 1
        elif key == curses.KEY_DOWN:
            delta_row = 1
        elif key == curses.KEY_LEFT:
            delta_col = -1

        app.byte_grid.cursor_position = (old_cursor[0]+delta_row,
                                         old_cursor[1]+delta_col)

        app.address_block.highlight_inx = app.byte_grid.cursor_position[0]


def link_listeners(app):
    app.attach_listener(ExitListiner())
    app.attach_listener(MoveByteGridCursorListiner())
