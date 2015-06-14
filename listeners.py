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

        new_cursor = app.byte_grid.cursor_position

        app.address_block.highlight_inx = new_cursor[0]
        app.text_view.highlight_index = (new_cursor[0] *
                                         app.text_view.symbol_in_row +
                                         new_cursor[1])

        app.status_line.offset = (app.offset_in_file +
                            new_cursor[0] * app.byte_grid.col_count +
                            new_cursor[1])

class GoToListener(Listener):
    def update(self,app):
        last_event = app.event_history[-1]

        if last_event.type != 'go_to':
            return

        app.go_to(last_event.data['offset'])

def link_listeners(app):
    app.attach_listener(ExitListiner())
    app.attach_listener(MoveByteGridCursorListiner())
    app.attach_listener(GoToListener())
