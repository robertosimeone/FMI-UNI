chess_names = {'r', 'n', 'b', 'q', 'k', 'p'}
checking_sequence = [(-1, -1), (-1, 0), (-1, 1), (1, -1), (1, 0), (1, +1), (0, -1), (0, 1)]
chess_points = {'r': 5, 'n': 3, 'b': 3, 'q': 9, 'k': 4, 'p': 1}
columns = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7}
from contextlib import suppress

class ChessException(Exception):
    # def __init__(self, message):
    #     self.message = message
    #     super().__init__(message)
    pass


class ChessPosition:
    def __init__(self, fen):
        self.fen = fen.split('/')
        self.chess_board = list()
        self.chess_board.extend([list() for _ in range(8)])
        for index, roll in enumerate(reversed(self.fen)):
            for figure in roll:
                if figure.isalpha():
                    self.chess_board[index].append(figure)
                else:
                    self.chess_board[index].extend(['-' for _ in range(int(figure))])
        if not self.is_valid_number_of_kings():
            raise ChessException("kings")
        if not self.check_kings_positions(*self.find_kings()):
            raise ChessException("kings")
        if not self.checkpawns():
            raise ChessException("pawns")

    def __str__(self):
        return '/'.join(self.fen)

    def __len__(self):
        number_of_figures = 0
        for roll in self.fen:
            for symbol in roll:
                if symbol.lower() in chess_names:
                    if symbol.islower() or symbol.isupper():
                        number_of_figures += 1
        return number_of_figures

    def __getitem__(self, coordinates):
        if self.chess_board[int(coordinates[1]) - 1][columns[coordinates[0]]] == '-':
            return None
        return self.chess_board[int(coordinates[1]) - 1][columns[coordinates[0]]]

    def get_white_score(self):
        white_score = []
        for roll in self.fen:
            for figure in roll:
                if figure.isupper():
                    white_score.append(figure)
        return ChessScore(white_score)

    def get_black_score(self):
        black_score = []
        for roll in self.fen:
            for figure in roll:
                if figure.islower():
                    black_score.append(figure)
        return  ChessScore(black_score)

    def white_is_winning(self):
        return self.get_white_score() > self.get_black_score()

    def black_is_winning(self):
        return self.get_white_score() < self.get_black_score()

    def is_equal(self):
        return self.get_white_score() == self.get_black_score()

    def checkpawns(self):
        for index, roll in enumerate(self.fen):
            if roll.count('p') or roll.count('P'):
                if index == 0 or index == 7:
                    return False
        return True

    def is_valid_number_of_kings(self):
        whitek = 0
        blackk = 0
        for roll in self.fen:
            whitek += roll.count('K')
            blackk += roll.count('k')
        return whitek == 1 and blackk == 1

    def check_kings_positions(self, first_king, second_king):
        if self.isValidPosition(first_king) and self.isValidPosition(second_king):
            for sequence in checking_sequence:
                coordinates = first_king[0] + sequence[0], first_king[1] + sequence[1]
                if self.isValidPosition(coordinates):
                    if self.chess_board[coordinates[0]][coordinates[1]] == 'K':
                        return False
        return True

    def find_kings(self):
        first_king = None
        second_king = None
        for index, roll in enumerate(self.chess_board):
            with suppress(ValueError):
                first_king = (index, roll.index('k'))
            with suppress(ValueError):
                second_king = (index, roll.index('K'))
        return first_king, second_king

    def isValidPosition(self, position):
        if 0 <= position[0] <= 7 and 0 <= position[1] <= 7:
            return True


class ChessScore:
    def __init__(self, figures):
        self.figures = list(figures)
        self.value = self.calculate_value()

    def calculate_value(self):
        value = 0
        for figure in self.figures:
            if figure.lower() in chess_names:
                value += chess_points[figure.lower()]
        return value

    def __lt__(self, other):
        return self.value < other.value

    def __gt__(self, other):
        return self.value > other.value

    def __le__(self, other):
        return self.value <= other.value

    def __ge__(self, other):
        return self.value >= other.value

    def __eq__(self, other):
        return self.value == other.value

    def __ne__(self, other):
        return self.value != other.value

    def __add__(self, other):
        return self.value + other.value

    def __sub__(self, other):
        return self.value - other.value

    def __int__(self):
        return self.value

# ck = ChessScore(['P','K'])
# print(int(ck))

# try:
#     ck = ChessPosition('k7/K7/8/8/8/8/8/8')
# except ChessException as e:
#     print(str(e))

