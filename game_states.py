"""
Game state
"""

from enum import Enum


class TileState(Enum):
    InMyHand = 0
    InMyDiscardTiles = 1
    InPlayer1DiscardTiles = 2
    InPlayer2DiscardTiles = 3
    InPlayer3DiscardTiles = 4
    InMySuit = 5
    InPlayer1Suit = 6
    InPlayer2Suit = 7
    InPlayer3Suit = 8
    Unknown = 9

    def __int__(self):
        return self.value


class StateMap:
    """
    Represents the current state of tile.

    Note:
        State of tiles is stored in a list containing 136 slots.
        0   - 35     Characters
        36  - 71     Circles
        72  - 107    Bamboo
        108 - 111    Red Dragon
        112 - 115    Green Dragon
        116 - 119    White Dragon
        120 - 123    East Wind
        124 - 127    South Wind
        128 - 131    West Wind
        132 - 135    North Wind

        Lower and upper index are included.
    """
    TILE_NUMBER = 136
    EXTRA_FEATURES_NUMBER = 2
    TOTAL_NUMBER = TILE_NUMBER + EXTRA_FEATURES_NUMBER

    def __init__(self):
        """
        Initializes an empty state map.
        """
        # Create a initialized state map where all tiles are assumed unknown
        self._state = [TileState.Unknown] * StateMap.TILE_NUMBER
        self._state.append(False)  # isClaim bit
        self._state.append(False)  # Claim action bit

    def get_state(self, tile_code):
        start_index = StateMap._get_tile_start_index(tile_code)
        return self._state[start_index:start_index + 4]

    def draw_a_new_tile(self, tile_code):
        """
        Draws a new tile from the wall

        :param tile_code: tile code(reference to line 192 of tiles.c in original source code)
        """
        tile_states = self.get_state(tile_code)
        first_unknown_index = tile_states.index(TileState.Unknown)
        self.set_tile_status(tile_code, first_unknown_index, TileState.InMyHand)

    def discard_tile(self, player_id, tile_code):
        """
        Discards a tile from player's hand

        :param player_id: 0 for our
        :param tile_code:
        :return:
        """
        tile_states = self.get_state(tile_code)
        if player_id == 0:  # discard our tile
            first_in_hand_index = tile_states.index(TileState.InMyHand)
            self.set_tile_status(tile_code, first_in_hand_index, TileState.InMyDiscardTiles)
        else:  # other player discarded a tile
            first_unknown_index = tile_states.index(TileState.Unknown)
            self.set_tile_status(tile_code, first_unknown_index, TileState(1 + player_id))

    def make_chow(self, player_id, tile_code, position):
        """
        Makes a chow

        :param player_id: id of player
        :param tile_code:
        :param position:  reference to line 91 of protocol.c
        :return:
        """
        offset = {
            'Lower': 0,
            'Middle': 1,
            'Upper': 2
        }[position]
        base = int(tile_code[0])
        tiles_in_hand_to_change = [str(base - offset + i) + tile_code[1] for i in range(3)]
        tiles_in_hand_to_change.remove(tile_code)
        if player_id == 0:
            for tile in tiles_in_hand_to_change:
                tile_state = self.get_state(tile)
                first_in_hand_index = tile_state.index(TileState.InMyHand)
                self.set_tile_status(tile, first_in_hand_index, TileState.InMySuit)
            # handle the tile chowed
            tile_state = self.get_state(tile_code)
            tile_index = tile_state.index(TileState.InPlayer3DiscardTiles)
            self.set_tile_status(tile_code, tile_index, TileState.InMySuit)
        else:
            state_to_check = TileState(player_id)
            state_to_change = TileState(5 + player_id)
            for tile in tiles_in_hand_to_change:
                tile_state = self.get_state(tile)
                first_in_hand_index = tile_state.index(TileState.Unknown)
                self.set_tile_status(tile, first_in_hand_index, state_to_change)
            tile_state = self.get_state(tile_code)
            tile_index = tile_state.index(state_to_check)
            self.set_tile_status(tile_code, tile_index, state_to_change)

    def make_pung(self, player_id, discard_id, tile_code):
        discard_state = TileState(1 + discard_id)
        state_to_change = TileState(5 + player_id)
        states = self.get_state(tile_code)
        discard_index = states.index(discard_state)
        self.set_tile_status(tile_code, discard_index, state_to_change)
        if player_id == 0:
            detect_state = TileState.InMyHand
        else:
            detect_state = TileState.Unknown
        for _ in range(2):
            states = self.get_state(tile_code)  # Update to latest state
            i = states.index(detect_state)
            self.set_tile_status(tile_code, i, state_to_change)

    def make_kong(self, player_id, tile_code):
        state_to_change = TileState(5 + player_id)
        for i in range(4):
            self.set_tile_status(tile_code, i, state_to_change)

    def set_claim(self, claim):
        self._state[-1] = claim

    def is_claimed(self):
        return self._state[-1]

    def set_tile_status(self, tile_code, num, state):
        """
        Sets state of tile

        :param tile_code:
        :param num:
        :param state:
        :return:
        """
        self._state[StateMap._get_tile_start_index(tile_code) + num] = state

    def get_available_decisions(self):
        return set([StateMap._decode_index_to_tile(idx) for idx, mem in enumerate(self._state)
                    if mem == TileState.InMyHand])

    def get_our_tiles(self):
        return [StateMap._decode_index_to_tile(i) for i, m
                in enumerate(self._state) if m == TileState.InMyHand]

    @classmethod
    def _get_tile_start_index(cls, tile_code):
        """
        Gets the start index of designated tile.

        param tile_code:
        return: Start index in state map. e.g if tile_code is 1C, 0 will be returned.
        """
        if tile_code[1] is 'C':
            return 4 * (int(tile_code[0]) - 1)
        elif tile_code[1] is 'B':
            return 72 + 4 * (int(tile_code[0]) - 1)
        elif tile_code[1] is 'D':  # Circles and dragon is contained here
            if tile_code[0].isdigit():  # Case of circles
                return 36 + 4 * (int(tile_code[0]) - 1)
            else:
                if tile_code[0] not in ['R', 'G', 'W']:
                    raise ValueError('Tile code is not comply with protocol.\nCode received: {}'.format(tile_code))
                return {
                    'R': 108,
                    'G': 112,
                    'W': 116
                }[tile_code[0]]
        elif tile_code[1] is 'W':
            if tile_code[0] not in ['E', 'S', 'W', 'N']:
                raise ValueError('Tile code is not comply with protocol.\nCode received: {}'.format(tile_code))
            return {
                'E': 120,
                'S': 124,
                'W': 128,
                'N': 132
            }[tile_code[0]]
        raise ValueError('Tile code is not comply with protocol.\nCode received: {}'.format(tile_code))

    @classmethod
    def _decode_index_to_tile(cls, idx):
        kind_dict = {
            0: 'C',
            1: 'D',
            2: 'B',
        }
        tile_no = idx // 4
        tile_kind = tile_no // 9
        if tile_kind <= 2:
            return str(tile_no % 9 + 1) + kind_dict[tile_kind]
        else:
            return {
                27: 'RD',
                28: 'GD',
                29: 'WD',
                30: 'EW',
                31: 'SW',
                32: 'WW',
                33: 'NW'
            }[tile_no]

    def serialize(self):
        s = [int(i) for i in self._state]
        return ''.join([str(i) for i in s])

    def deserialize(self, serialized_obj):
        for i in range(StateMap.TILE_NUMBER):
            self._state[i] = TileState(int(serialized_obj[i]))
        self._state[StateMap.TILE_NUMBER] = bool(int(serialized_obj[StateMap.TILE_NUMBER]))
        self._state[StateMap.TILE_NUMBER+1] = bool(int(serialized_obj[StateMap.TILE_NUMBER+1]))

    def __eq__(self, other):
        return self._state == other._state

    def __hash__(self):
        _sum = 0
        for i in range(StateMap.TOTAL_NUMBER):
            _sum += int(self._state[i]) * 10 ** i
        return _sum

    def __repr__(self):
        return str(hash(self))
