"""
Implementation of Monte carlo tree
"""
from copy import deepcopy
from math import log, sqrt
from game_states import StateMap
import json


class MonteCarloTree:
    def __init__(self):
        self._map = {}

    def register_node(self, state, node):
        self._map[repr(state)] = node

    def __contains__(self, item):
        return repr(item) in self._map

    def make_expand_decision(self, present_state):
        node = self._map[repr(present_state)]

        max_ucb_value = 0

        c = sqrt(2)
        t = node.get_num_total_games()
        child_states = node.get_child_nodes()
        prefer_action = 'ERROR'
        for action in child_states:
            state = child_states[action]
            if state not in self:
                self.register_node(state, MonteCarloResultNode(state))
            state_info = self.get_state(state)
            w_i = state_info.get_num_win_games()
            n_i = state_info.get_num_total_games()
            if n_i != 0:
                ucb_value = w_i / n_i + c * sqrt(log(t) / n_i)
            else:
                ucb_value = 0
            if ucb_value >= max_ucb_value:
                prefer_action = action
        return prefer_action

    def get_state(self, state):
        return self._map[repr(state)]

    def backpropagate(self, states, is_win):
        for s in states:
            self._map[repr(s)].update_result(is_win)

    def serialize(self):
        d = {
            key: self._map[key].serialize() for key in self._map
        }
        return json.dumps(d)

    def deserialize(self, ss):
        j = json.loads(ss)
        for key in j:
            new_node = MonteCarloTreeNode()
            new_node.deserialize(j[key])
            self._map[key] = deepcopy(new_node)
        # check no Nonetype is generated
        for key in self._map:
            assert self._map[key] is not None

    def record_length(self):
        return len(self._map)

class MonteCarloTreeNode:
    def __init__(self, present_state=None):
        self._node_state = present_state
        self._child_nodes = {}
        self._num_total_games = 0
        self._num_win_games = 0

    def __hash__(self):
        return hash(self._node_state)

    def __eq__(self, other):
        return self._node_state == other._node_state

    def create_new_result_node(self, action, state):
        self._child_nodes[action] = state

    def update_result(self, is_win):
        self._num_total_games += 1
        if is_win:
            self._num_win_games += 1

    def get_num_total_games(self):
        return self._num_total_games

    def get_num_win_games(self):
        return self._num_win_games

    def get_child_nodes(self):
        return self._child_nodes

    def serialize(self):
        d = {
            'node_state': self._node_state.serialize(),
            'child_nodes': { key: self._child_nodes[key].serialize() for key in self._child_nodes },
            'number_total_games': self._num_total_games,
            'number_win_games': self._num_win_games
        }
        return json.dumps(d)

    def deserialize(self, ss):
        j = json.loads(ss)
        new_state = StateMap()
        new_state.deserialize(j['node_state'])
        self._node_state = deepcopy(new_state)
        self._num_total_games = j['number_total_games']
        self._num_win_games = j['number_win_games']
        for key in j['child_nodes']:
            s = StateMap()
            s.deserialize(j['child_nodes'][key])
            self._child_nodes[key] = deepcopy(s)


class MonteCarloResultNode(MonteCarloTreeNode):
    def __init__(self, present_state):
        super(self.__class__, self).__init__(present_state)


class MonteCarloDiscardNode(MonteCarloTreeNode):
    def __init__(self, present_state):
        super(self.__class__, self).__init__(present_state)
        state = deepcopy(present_state)
        for action in present_state.get_available_decisions():
            temp = deepcopy(state)
            temp.discard_tile(0, action)
            self.create_new_result_node(action, temp)
