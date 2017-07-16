from unittest import TestCase

from game_states import StateMap
from monte_carlo_tree import *


class MonteCarloTreeNodeTestCase(TestCase):
    def test_update_result(self):
        s = StateMap()
        n = MonteCarloTreeNode(s)

        n.update_result(True)
        self.assertEqual(n.get_num_total_games(), 1)
        self.assertEqual(n.get_num_win_games(), 1)

        n.update_result(False)
        self.assertEqual(n.get_num_total_games(), 2)
        self.assertEqual(n.get_num_win_games(), 1)


class MonteCarloTreeDiscardNodeTestCase(TestCase):
    def test_create_a_new_discard_node(self):
        s = StateMap()
        draw_card = ['1C', '2C', '2C', '4D', 'RD', 'WD', 'WD', 'WW', 'NW', '1B', '9B', '8B', '4C']
        for i in draw_card:
            s.draw_a_new_tile(i)

        n = MonteCarloDiscardNode(s)
        self.assertEqual(len(n.get_child_nodes()), len(set(draw_card)))


class MonteCarloTreeTestCase(TestCase):
    def test_use_scenario_1(self):
        s = StateMap()
        m = MonteCarloTree()
        draw_card = ['1C', '2C', '2C', '4D', 'RD', 'WD', 'WD', 'WW', 'NW', '1B', '9B', '8B', '4C']
        for i in draw_card:
            s.draw_a_new_tile(i)

        # I'm the first to discard
        if s not in m:  # Of course, not
            m.register_node(s, MonteCarloDiscardNode(s))

        # expand tree node
        action = m.make_expand_decision(s)
        s.discard_tile(0, action)

        s.discard_tile(1, '2C')
        s.discard_tile(2, 'RD')
        s.discard_tile(3, 'RD')

        # it's our turn
        if s not in m:  # Of course, not
            m.register_node(s, MonteCarloDiscardNode(s))

        # expand tree node
        action = m.make_expand_decision(s)
        s.discard_tile(0, action)

    def test_back_propagate(self):
        s = StateMap()
        m = MonteCarloTree()
        states = list()

        draw_card = ['1C', '2C', '2C', '4D', 'RD', 'WD', 'WD', 'WW', 'NW', '1B', '9B', '8B', '4C']
        for i in draw_card:
            s.draw_a_new_tile(i)

        # I'm the first to discard
        if s not in m:  # Of course, not
            m.register_node(s, MonteCarloDiscardNode(s))

        states.append(deepcopy(s))
        self.assertIn(s, m)
        action = m.make_expand_decision(s)
        s.discard_tile(0, action)
        self.assertIn(s, m)
        states.append(deepcopy(s))

        self.assertIn(states[0], m)
        self.assertIn(states[1], m)

        # if we win
        m.backpropagate(states, True)

        for state in states:
            n = m.get_state(state)
            self.assertEqual(n.get_num_win_games(), 1)
            self.assertEqual(n.get_num_total_games(), 1)
