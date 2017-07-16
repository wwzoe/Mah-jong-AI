from unittest import TestCase

from game_states import TileState, StateMap


class TestStateMap(TestCase):
    def test_draw_a_new_tile(self):
        sm = StateMap()

        # Draw a 1 of Circle from the tile wall
        sm.draw_a_new_tile('1C')
        self.assertCountEqual(sm.get_state('1C'), [TileState.InMyHand] + [TileState.Unknown] * 3)

        # Draw two 3C from tile wall
        sm.draw_a_new_tile('3C')
        sm.draw_a_new_tile('3C')
        self.assertCountEqual(sm.get_state('3C'), [TileState.InMyHand] * 2 + [TileState.Unknown] * 2)

        # Draw a 5C when 5C is discarded by other player
        sm.set_tile_status('5C', 0, TileState.InPlayer2DiscardTiles)
        sm.draw_a_new_tile('5C')
        self.assertCountEqual(sm.get_state('5C'), [
            TileState.InPlayer2DiscardTiles] + [TileState.Unknown] * 2 + [TileState.InMyHand])

    def test__get_tile_start_index(self):
        self.assertEqual(StateMap._get_tile_start_index('1C'), 0)
        self.assertEqual(StateMap._get_tile_start_index('5C'), 16)
        self.assertEqual(StateMap._get_tile_start_index('2B'), 76)
        self.assertEqual(StateMap._get_tile_start_index('1D'), 36)
        self.assertEqual(StateMap._get_tile_start_index('RD'), 108)
        self.assertEqual(StateMap._get_tile_start_index('NW'), 132)

    def test_discard_tile(self):
        sm = StateMap()

        sm.draw_a_new_tile('2C')
        sm.draw_a_new_tile('2C')

        sm.discard_tile(1, '2C')
        self.assertCountEqual(sm.get_state('2C'),
                              [TileState.Unknown] + [TileState.InPlayer1DiscardTiles] + [TileState.InMyHand] * 2)
        sm.discard_tile(0, '2C')
        self.assertCountEqual(sm.get_state('2C'),
                              [TileState.Unknown, TileState.InPlayer1DiscardTiles, TileState.InMyDiscardTiles,
                               TileState.InMyHand])

    def test_make_chow(self):
        sm = StateMap()

        sm.draw_a_new_tile('2C')
        sm.draw_a_new_tile('4C')
        sm.discard_tile(3, '3C')
        sm.make_chow(0, '3C', 'Middle')

        self.assertIn(TileState.InMySuit, sm.get_state('2C'))
        self.assertIn(TileState.InMySuit, sm.get_state('3C'))
        self.assertIn(TileState.InMySuit, sm.get_state('4C'))

        sm.discard_tile(1, '6B')
        sm.make_chow(2, '6B', 'Upper')
        self.assertIn(TileState.InPlayer2Suit, sm.get_state('4B'))
        self.assertIn(TileState.InPlayer2Suit, sm.get_state('5B'))
        self.assertIn(TileState.InPlayer2Suit, sm.get_state('6B'))

    def test_make_pung(self):
        sm = StateMap()

        sm.draw_a_new_tile('RD')
        sm.draw_a_new_tile('RD')
        sm.discard_tile(1, 'RD')
        sm.make_pung(0, 1, 'RD')
        self.assertCountEqual(sm.get_state('RD'),
                              [TileState.InMySuit] * 3 + [TileState.Unknown])

        sm.discard_tile(2, 'WD')
        sm.make_pung(3, 2, 'WD')
        self.assertCountEqual((sm.get_state('WD')),
                              [TileState.InPlayer3Suit] * 3 + [TileState.Unknown])

    def test_make_kong(self):
        sm = StateMap()

        sm.draw_a_new_tile('3B')
        sm.draw_a_new_tile('3B')
        sm.draw_a_new_tile('3B')
        sm.discard_tile(1, '3B')
        sm.make_kong(0, '3B')
        self.assertCountEqual(sm.get_state('3B'),
                              [TileState.InMySuit] * 4)

        sm.discard_tile(3, '6B')
        sm.make_kong(2, '6B')
        self.assertCountEqual(sm.get_state('6B'),
                              [TileState.InPlayer2Suit] * 4)

    def test_dict_behavior_test(self):
        sm = StateMap()
        d = {sm : 'hello world'}
        lm = StateMap()

        self.assertEqual(d[lm], 'hello world')

    def test_get_available_decisions_in_discard_case(self):
        sm = StateMap()

        draw_card = ['1C', '2C', '2C', '4D', 'RD', 'WD', 'WD', 'WW', 'NW', '1B', '9B', '8B', '4C']
        for i in draw_card:
            sm.draw_a_new_tile(i)

        self.assertCountEqual(sm.get_available_decisions(), set(draw_card))

    def test_serialize(self):
        sm = StateMap()

        draw_card = ['1C', '2C', '2C', '4D', 'RD', 'WD', 'WD', 'WW', 'NW', '1B', '9B', '8B', '4C']
        for i in draw_card:
            sm.draw_a_new_tile(i)
        sm2 = StateMap()

        sm2.deserialize(sm.serialize())
        self.assertEqual(sm, sm2)
