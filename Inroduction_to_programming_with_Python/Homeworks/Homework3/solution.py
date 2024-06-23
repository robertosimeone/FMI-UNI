import random


class Card:
    def __init__(self, suit, face):
        self._suit = suit
        self._face = face

    def get_suit(self):
        return self._suit

    def get_face(self):
        return self._face


class Deck:
    def __init__(self, face_filter=[]):
        faces = [str(x) for x in range(2, 11)]
        faces.extend(['J', 'Q', 'K', 'A'])
        if face_filter:
            self._cards = [Card(suit, face) for face in face_filter for suit in
                           ['clubs', 'diamonds', 'hearts', 'spades']]
        else:
            self._cards = [Card(suit, face) for face in faces for suit in ['clubs', 'spades', 'diamonds', 'hearts']]

    def cut(self):
        if len(self._cards) > 1:
            for current_cut in range(random.randint(1, len(self._cards) - 1)):
                self._cards.insert(0, self._cards.pop())

    def shuffle(self):
        random.shuffle(self._cards)

    def get_cards(self):
        return self._cards

    def add_cards(self, cards):
        self._cards.extend(cards)

    def add_card(self, card):
        self._cards.append(card)

    def draw_card(self):
        if self._cards:
            return self._cards.pop()


class Player:
    def __init__(self):
        self._hand = []

    def get_cards(self):
        return self._hand

    def clear_hand(self):
        self._hand.clear()

    def add_card_to_hand(self, card):
        self._hand.append(card)

    def add_cards_to_hand(self, cards):
        self._hand.extend(cards)


class Game:
    def __init__(self, number_of_players, dealing_direction, dealing_instructions, face_filter=[]):
        self._number_of_players = number_of_players
        self._dealing_direction = dealing_direction
        self._dealing_instructions = dealing_instructions
        self._players = [Player() for _ in range(self._number_of_players)]
        self._deck = Deck(face_filter)

    def get_players(self):
        return self._players

    def prepare_deck(self):
        for current_player in self._players:
            self._deck.add_cards(current_player.get_cards())
            current_player.clear_hand()
        self._deck.shuffle()
        self._deck.cut()

    def deal(self, player_search):
        given_player = -1
        for current_player in range(self._number_of_players):
            if self._players[current_player] is player_search:
                given_player = current_player
                break
        if given_player == -1:
            return
        order = []
        if self._dealing_direction == 'ltr':
            order = [x for x in range(given_player, self._number_of_players)]
            order.extend([x for x in range(0, given_player)])
        elif self._dealing_direction == 'rtl':
            order = [x for x in range(given_player, -1, -1)]
            order.extend([x for x in range(len(self._players) - 1, given_player, -1)])
        for instruction in self._dealing_instructions:
            for current_player in order:
                self._players[current_player].add_cards_to_hand([self._deck.draw_card() for card in range(instruction)])

    def get_deck(self):
        return self._deck


class Belot(Game):
    def __init__(self):
        super().__init__(4, 'ltr', (2, 3, 3), ['7', '8', '9', '10', 'J', 'Q', 'K', 'A'])


class Poker(Game):
    def __init__(self):
        super().__init__(9, 'rtl', (1, 1, 1, 1, 1))
