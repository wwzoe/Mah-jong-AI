from client import *


class GameManager:
    """
    Manages the communication to game server.
    """
    ADDR = ':5000'
    PORT = 5000

    def __init__(self):
        self.game = client.client_init(GameManager.ADDR)
        self._is_finish_declaring = False
        self._is_finish_scoring = False

    def connect(self):
        if client.client_connect(self.game, 21, 'BetaMahjong') != 1:
            print('Connect attempt to server at {} failed.\n')

    def receive_message(self):
        msg = client.fd_get_line(self.game.fd)
        return msg

    def send_message(self, msg):
        client.client_send_packet(self.game, msg)

    def handle_cmsg(self, cmsg):
        if client.game_handle_cmsg(self.game, cmsg) in (-1, -2):
            print('CMSG is in error.\n')

    def get_player_id(self, i):
        return client.PlayerP_value(
            client.PlayerPs_getitem(self.game.players, i)).id

    def get_tiles(self):
        tiles = []
        p_tiles = client.PlayerPs_getitem(
            self.game.players, self.our_index).concealed
        for i in range(13):
            tiles.append(client.tile_code(client.Tiles_getitem(p_tiles, i)))
        return tiles

    def get_our_seat(self):
        return self.our_seat

    def get_full_tiles(self):
        tiles = []
        p_tiles = client.PlayerPs_getitem(
            self.game.players, self.our_index).concealed
        for i in range(14):
            tiles.append(client.tile_code(client.Tiles_getitem(p_tiles, i)))
        return tiles

    def can_we_declare_mahjong(self, tile_code=None):
        our_player = client.PlayerPs_getitem(self.game.players, self.our_seat)
        if tile_code is not None:
            return client.player_can_mah_jong(
                our_player, client.tile_decode(tile_code), 1)
        else:
            return client.player_can_mah_jong(our_player, 0, 1)

    def declare_mahjong(self, is_from_wall):
        pmsg = client.PMsgMsg()
        pmsg.type = client.PMsgMahJong
        if is_from_wall:
            pmsg.discard = 0
        else:
            pmsg.discard = self.game.serial
        self.send_message(pmsg)

    def print_err(self):
        print('Game server sent an error as below:\n' + self.game.cmsg_err)

    def get_game_state(self):
        return self.game.state

    def init_our_info(self, our_id):
        self.our_id = our_id
        self.our_index = self._get_our_player_index(our_id)
        self.our_seat = client.game_id_to_seat(self.game, self.our_id)

    def init_seat(self):
        self.internal_player_number = {
            self.our_seat: 0,
            (self.our_seat + 1) % 4: 1,
            (self.our_seat + 2) % 4: 2,
            (self.our_seat + 3) % 4: 3
        }

    def init_game(self):
        self._is_finish_declaring = False
        self._is_finish_scoring = False

    def is_finish_declaring(self):
        return self._is_finish_declaring

    def is_finish_scoring(self):
        return self._is_finish_scoring

    def print_out_game_info(self):
        print('current game active: {}'.format(self.game.active))
        print('current game status: {}'.format(self.game.state))
        print('current game active player: {}'.format(self.game.player))
        if hasattr(self, 'our_id'):
            print('current our id: {}'.format(self.our_id))
        if hasattr(self, 'our_seat'):
            print('current player seat: {}'.format(self.our_seat))

    def is_our_turn(self):
        return self.game.player == self.our_seat

    def is_our_player(self):
        return self.game.player == client.game_id_to_seat(self.game,
                                                          self.our_id)

    def are_we_ready(self):
        return client.ints_getitem(self.game.ready, self.our_seat)

    def is_game_active(self):
        return self.game.active

    def is_game_paused(self):
        if self.game.paused is not None:
            print('Game is paused due to \n' + self.game.paused)
        return self.game.paused is not None

    def get_last_draw_tile(self):
        return client.tile_code(self.game.tile)

    def get_last_discarded_tile(self):
        return client.tile_code(self.game.tile)

    def get_active_player_number(self):
        return self.internal_player_number[self.game.player]

    def declare_specials(self, tile_code):
        declare_special_msg = client.PMsgDeclareSpecialMsg()
        declare_special_msg.type = client.PMsgDeclareSpecial
        declare_special_msg.tile = client.tile_decode(tile_code)
        self.send_message(
            client.PMsgDeclareSpecialMsg_to_PMsg(declare_special_msg))

    def finish_declaration(self):
        if not self._is_finish_declaring:
            declare_special_msg = client.PMsgDeclareSpecialMsg()
            declare_special_msg.type = client.PMsgDeclareSpecial
            declare_special_msg.tile = 0  # HIDDENTILE
            self.send_message(
                client.PMsgDeclareSpecialMsg_to_PMsg(declare_special_msg))
            self._is_finish_declaring = True

    def send_ready(self):
        ready_msg = client.PMsgMsg()
        ready_msg.type = client.PMsgReady
        self.send_message(ready_msg)

    def complete_scoring(self):
        if not self._is_finish_scoring:
            m = client.PMsgMsg()
            m.type = client.PMsgShowTiles
            self.send_message(m)
            self._is_finish_scoring = True

    def get_game_state(self):
        return self.game.state

    def test_winner_flag(self, flag):
        p = client.PlayerPs_getitem(self.game.players, self.game.player)
        return client.test_flag(p, flag)

    def test_self_flag(self, flag):
        p = client.PlayerPs_getitem(self.game.players, self.our_seat)
        return client.test_flag(p, flag)

    def discard_tile(self, tile_code):
        discard_tile_msg = client.PMsgDiscardMsg()
        discard_tile_msg.type = client.PMsgDiscard
        discard_tile_msg.tile = client.tile_decode(tile_code)
        discard_tile_msg.calling = False  # Never calling
        self.send_message(
            client.PMsgDiscardMsg_to_PMsg(discard_tile_msg)
        )

    def make_no_claim(self):
        nc_msg = client.PMsgNoClaimMsg()
        nc_msg.type = client.PMsgNoClaim
        nc_msg.discard = self.game.serial
        self.send_message(client.PMsgNoClaimMsg_to_PMsg(nc_msg))

    def _get_our_player_index(self, our_id):
        for i in range(4):
            if client.PlayerPs_getitem(self.game.players, i).id == our_id:
                return i
