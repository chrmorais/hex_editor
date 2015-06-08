class TextView:
    def __init__(self, view_zone):
        self.draw_zone = view_zone
        self.color = 1
        self.highlight_index = -1
        self.highlight_color = 1
        self.symbol_in_row = 0
        self.invisible_symbol = '.'
        self.data = []
