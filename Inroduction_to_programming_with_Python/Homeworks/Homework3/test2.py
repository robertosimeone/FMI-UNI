import unittest
from unittest.mock import patch

from solution import Card, Deck, Player, Game, Belot, Poker


class TestCard(unittest.TestCase):
    """Test the Card class."""

    def test_simple_init(self):
        """Sanity test for the Card class."""
        card = Card('clubs', '2')
        self.assertTrue(hasattr(card, 'get_suit'))
        self.assertTrue(hasattr(card, 'get_face'))

    def test_suit_data(self):
        """Test for get_suit() method in Crad class."""
        card = Card("sineok_bql_drakon", "7")
        self.assertEqual(card.get_suit(), "sineok_bql_drakon")

    def test_face_data(self):
        """Test for get_face() method."""
        card = Card("sineok_bql_drakon", "7")
        self.assertEqual(card.get_face(), "7")


class TestDeck(unittest.TestCase):
    """Test the Deck class."""

    def test_simple_init(self):
        """Sanity test for the Deck class."""
        deck = Deck()
        self.assertTrue(hasattr(deck, 'cut'))
        self.assertTrue(hasattr(deck, 'shuffle'))
        self.assertTrue(hasattr(deck, 'get_cards'))

    def test_default_init(self):
        """Test for init method with no parameters."""
        deck = Deck()
        # self.assertEqual(len(deck._face_filter), 0)
        self.assertEqual(len(deck.get_cards()), 52)

    def test_parameters_init(self):
        """Test for init method with list parameter."""
        deck = Deck(["2", "7", "10", "J", "A"])
        # self.assertEqual(len(deck._face_filter), 5)
        self.assertEqual(len(deck.get_cards()), 20)

    @patch("random.randint", return_value=1)
    def test_deck_cutting_with_default_init(self, randint_mock):
        """Test default cut method."""
        deck = Deck()
        deck_cards = deck.get_cards()
        first_elem = deck_cards[0]
        second_elem = deck_cards[1]
        last_elem = deck_cards[51]

        deck.cut()
        deck_cards = deck.get_cards()
        self.assertEqual(deck_cards[0], second_elem)
        self.assertEqual(deck_cards[51], first_elem)
        self.assertEqual(deck_cards[50], last_elem)

    @patch("random.randint", return_value=15)
    def test_deck_cutting_with_custom_init(self, randint_mock):
        """Test corner case cut method."""
        deck = Deck(["5", "6", "7", "8"])
        deck_cards = deck.get_cards()
        first_elem = deck_cards[0]
        second_elem = deck_cards[1]
        last_elem = deck_cards[len(deck_cards) - 1]

        deck.cut()
        deck_cards = deck.get_cards()
        self.assertEqual(deck_cards[0], last_elem)
        self.assertEqual(deck_cards[1], first_elem)
        self.assertEqual(deck_cards[2], second_elem)

    @patch("random.randint", return_value=12)
    def test_not_valid_deck_cutting(self, randint_mock):
        """Test for not valid randint range in cut method."""
        deck = Deck(["2", "3", "4"])
        deck_cards = deck.get_cards()
        first_elem = deck_cards[0]
        last_elem = deck_cards[11]

        deck.cut()
        self.assertNotEqual(deck_cards[0], last_elem)
        self.assertNotEqual(deck_cards[1], first_elem)

    def test_simple_shuffle(self):
        """Test for existence of elements after shuffle."""
        deck = Deck()
        deck_cards1 = deck.get_cards()
        deck.shuffle()
        deck_cards2 = deck.get_cards()
        self.assertCountEqual(deck_cards1, deck_cards2)

    def test_get_cards(self):
        """Sanity test for get cards method."""
        deck = Deck(["A", "K", "4", "9"])
        self.assertEqual(len(deck.get_cards()), 16)


class TestPlayer(unittest.TestCase):
    """Test the Player class."""

    def test_simple_init(self):
        """Sanity test for the Player class."""
        player = Player()
        self.assertTrue(hasattr(player, 'get_cards'))


class TestGame(unittest.TestCase):
    """Test the Game class."""

    def test_simple_init(self):
        """Sanity test for the Game class."""
        game = Game(2, 'rtl', (1, 2))
        self.assertTrue(hasattr(game, 'get_players'))
        self.assertTrue(hasattr(game, 'prepare_deck'))
        self.assertTrue(hasattr(game, 'deal'))
        self.assertTrue(hasattr(game, 'get_deck'))

    def test_simple_get_players(self):
        """Test for get_players method."""
        game = Game(69, 'ltr', (4, 2, 0))
        self.assertEqual(len(game.get_players()), 69)

    def test_simple_get_deck(self):
        """Test for correct get_deck method (supposed to have 52 cards for default init?)."""
        game = Game(69, 'ltr', (4, 2, 0))
        deck = game.get_deck()
        self.assertEqual(len(deck.get_cards()), 52)

    # def test_simple_prepare_deck(self):
    #     """Test for preparing a new deal."""
    #     game = Game(69, 'ltr', (4, 2, 0))
    #     players = game.get_players()
    #     cards = []
    #     for manqk in players:
    #         player_cards = manqk.get_cards()
    #         for card in player_cards:
    #             cards.append(card)

    #     game.cut()
    #     self.assertCountEqual(cards, game.get_cards())


if __name__ == '__main__':
    unittest.main()