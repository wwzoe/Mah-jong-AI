"""
Mahjong AI program with Monte Carlo Tree Search
"""
from copy import deepcopy
from os.path import isfile
from time import sleep

from client import *
from game_manager import GameManager
from game_states import StateMap
from monte_carlo_tree import MonteCarloTree, MonteCarloDiscardNode

# Some data need to keep
our_id = 0
wind_round = None
player_1_id = 0
player_2_id = 0
player_3_id = 0
seat_dict = {}

mct = MonteCarloTree()
print('LOADING STATES HISTORY')
if isfile('param'):
    with open('param', 'r') as f:
        s = f.read()
        if s is not '':
            mct.deserialize(s)
    with open('mct_states', 'w') as mf:
        mf = mf.write(str(mct.record_length()))

game_state = StateMap()
states_in_game = []
is_discard_locked = False
game_count = 0
game_win = 0
game_lost = 0
prev_tiles = []
is_declare_updated = True

# Initializes game manager
game_mgr = GameManager()

# PLAY FUNCTION


def lets_play_it():
    global game_mgr, game_state, mct, is_discard_locked, prev_tiles, is_declare_updated
    if not game_mgr.is_game_active():
        return
    if game_mgr.is_game_paused():
        print('Game paused. Our state is {}'.format(game_mgr.are_we_ready()))
        if not game_mgr.are_we_ready():
            game_mgr.send_ready()
        return
    if game_mgr.get_game_state() == client.DeclaringSpecials and \
            game_mgr.is_our_turn() and not game_mgr.is_finish_declaring() \
            and is_declare_updated:
        # Dealing finished, we need to make clear our tiles
        if game_mgr.get_our_seat() != 0:
            tiles = game_mgr.get_tiles()
        else:
            tiles = game_mgr.get_full_tiles()
        print('Our tiles are {}'.format(tiles))
        for tile in tiles:
            if tile in ['1S', '2S', '3S', '4S', '1F', '2F', '3F', '4F']:
                # We have special tiles. Declaration is needed.
                if prev_tiles == tiles:         # AVOID Repeated Declaration
                    return
                prev_tiles = tiles
                print('Special tile {} found, declared'.format(tile))
                game_mgr.declare_specials(tile)
                is_declare_updated = False
                return

        print('Our tiles are {} after declaration'.format(tiles))
        for tile in tiles:
            game_state.draw_a_new_tile(tile)
        print('Declaring stage finished, game should start')
        game_mgr.finish_declaration()
        is_declare_finished = True
        return

    if game_mgr.get_game_state() == client.Discarding and \
            game_mgr.is_our_turn() and not is_discard_locked:
        # It's our turn to discard one card or announce mahjong?
        if game_mgr.can_we_declare_mahjong():
            # Yes, we win this game
            print('We are going to announce mahjong')
            game_mgr.declare_mahjong(True)
            return
        states_in_game.append(deepcopy(game_state))
        if game_state not in mct:
            mct.register_node(game_state, MonteCarloDiscardNode(game_state))
        act = mct.make_expand_decision(game_state)
        print('WE HAVE TILES FROM GAME: {}'.format(game_mgr.get_full_tiles()))
        print('WE HAVE TILES FROM STATE: {}'.format(game_state.get_our_tiles()))
        assert sorted(game_mgr.get_full_tiles()) == sorted(game_state.get_our_tiles())
        print('MCTS DECIDES TO DISCARD {}'.format(act))
        game_mgr.discard_tile(act)
        return
    if game_mgr.get_game_state() == client.Discarding and not game_mgr.is_our_turn():
        # DEALLING MSG 80/81
        game_mgr.make_no_claim()
        return
    if game_mgr.get_game_state() == client.Discarded and not game_mgr.is_our_turn():
        # MAKING CLAIM has not been implemented yet
        last_discarded_tile = game_mgr.get_last_discarded_tile()
        if game_mgr.can_we_declare_mahjong(last_discarded_tile):
            game_mgr.declare_mahjong(False)
            return
        game_mgr.make_no_claim()
        return
    if game_mgr.get_game_state() == client.MahJonging and not game_mgr.is_finish_scoring():
        if game_mgr.get_active_player_number() == 0:    # Winner are us
            # Scoring combination has not been implemented yet
            game_mgr.complete_scoring()
        elif game_mgr.test_winner_flag(client.HandDeclared) and \
                not game_mgr.test_self_flag(client.HandDeclared):
            print('We lost, completing score')
            game_mgr.complete_scoring()
        return

# END PLAY FUNCTION


def refresh_game():
    global states_in_game, game_state, is_declare_finished
    print('GAME IS REFRESHED')
    game_state = StateMap()
    states_in_game = []

# Connects to server
game_mgr.connect()

# Main loop
while True:
    msg = game_mgr.receive_message()
    if not msg:
        print('We just received a null msg.\n')
        break

    # Dispatch line. Might be a big switch but it's ugly
    cm = client.decode_cmsg(msg)
    msg_type = cm.type
    if msg_type == client.CMsgError:
        game_mgr.handle_cmsg(cm)
        print('We just received a error msg from server. Program down!\n')
        game_mgr.print_err()
        break
    elif msg_type == client.CMsgGameOver:
        game_mgr.handle_cmsg(cm)
        print('Game over!\n')
        print('MCTS RESULT: TOTAL: {} WINS: {} LOST: {}'.format(game_count, game_win, game_lost))
        with open('res', 'a') as r:
            r.writelines('\n')
        print('WRITING MCTS INTO DISK')
        with open('param', 'w') as f:
            f.write(mct.serialize())
    elif msg_type == client.CMsgReconnect:
        print('Server requires reconnection.\n')
    elif msg_type == client.CMsgInfoTiles:
        pass
    elif msg_type == client.CMsgCanMahJong:
        pass
    elif msg_type == client.CMsgConnectReply:
        game_mgr.handle_cmsg(cm)
        our_id = game_mgr.get_player_id(0)
        game_mgr.init_our_info(our_id)
    elif msg_type == client.CMsgAuthReqd:  # I do not think this will be sent
        pass
    elif msg_type == client.CMsgGame:
        pgmsg = client.PMsgListGameOptionsMsg()
        pgmsg.type = client.PMsgListGameOptions
        pgmsg.include_disable = 0
        game_mgr.send_message(client.PMsgListGameOptionsMsg_to_PMsg(pgmsg))
    elif msg_type in [client.CMsgNewRound, client.CMsgNewHand]:
        print('=' * 40 + '\nNEW HAND STARTS\n')
        game_mgr.handle_cmsg(cm)    # Able to know the wind of the round.
        # Processing is needed
        game_mgr.init_our_info(our_id)
        game_mgr.init_seat()
        game_mgr.init_game()
        if msg_type == client.CMsgNewHand:
            game_count += 1
            print('Game info: Game {}, won games {}, lost games {}'.format(game_count, game_win, game_lost))
    elif msg_type in [client.CMsgPlayer,
                      client.CMsgStopPlay,
                      client.CMsgClaimDenied,
                      client.CMsgPlayerDoesntClaim,
                      client.CMsgPlayerClaimsPung,
                      client.CMsgPlayerClaimsKong,
                      client.CMsgPlayerClaimsChow,
                      client.CMsgPlayerClaimsMahJong,
                      client.CMsgPlayerShowsTiles,
                      client.CMsgDangerousDiscard,
                      client.CMsgGameOption,
                      client.CMsgChangeManager,
                      client.CMsgWall,
                      client.CMsgComment,
                      client.CMsgStateSaved,
                      client.CMsgMessage]:
        game_mgr.handle_cmsg(cm)
    elif msg_type == client.CMsgHandScore:
        game_mgr.handle_cmsg(cm)
        lets_play_it()
    elif msg_type == client.CMsgWashOut:
        game_mgr.handle_cmsg(cm)
        print('DEAD HAND. GAME WILL RESTART')
        mct.backpropagate(states_in_game, False)
        game_lost += 1
        # Refresh game state
        refresh_game()
        with open('res', 'a') as r:
            r.writelines('D')

    elif msg_type == client.CMsgSettlement:
        game_mgr.handle_cmsg(cm)
        refresh_game()
    elif msg_type == client.CMsgPlayerRobsKong:
        game_mgr.handle_cmsg(cm)
    elif msg_type == client.CMsgPlayerMahJongs:
        game_mgr.handle_cmsg(cm)
        if game_mgr.is_our_turn():
            # we win game
            print('We just win the game.')
            game_win += 1
            mct.backpropagate(states_in_game, True)
            with open('res', 'a') as r:
                r.writelines('W')
        else:
            print('We just lost the game.')
            game_lost += 1
            mct.backpropagate(states_in_game, False)
            with open('res', 'a') as r:
                r.writelines('L')
        lets_play_it()

    elif msg_type == client.CMsgPlayerDeclaresSpecial:
        if game_mgr.get_game_state() == client.DeclaringSpecials:       # HACK: I'M SICK WITH IT.
            is_discard_locked = True
        else:
            is_discard_locked = False
        game_mgr.handle_cmsg(cm)
        if game_mgr.get_game_state() == client.DeclaringSpecials:
            lets_play_it()

    elif msg_type in [client.CMsgPlayerDraws, client.CMsgPlayerDrawsLoose]:
        is_discard_locked = False
        game_mgr.handle_cmsg(cm)
        print('Receive draw message')
        if game_mgr.get_game_state() == client.DeclaringSpecials:
            if game_mgr.is_our_turn():
                is_declare_updated = True
            lets_play_it()
            continue
        if game_mgr.get_game_state() not in [client.Dealing] \
                and game_mgr.is_our_turn():
            draw_tile = game_mgr.get_last_draw_tile()
            if draw_tile in ['1S', '2S', '3S', '4S', '1F', '2F', '3F', '4F']:
                print('Special tile {} found, declared'.format(draw_tile))
                game_mgr.declare_specials(draw_tile)
                is_declared = True
                continue
            print('We drew a {}.'.format(draw_tile))
            game_state.draw_a_new_tile(draw_tile)
            lets_play_it()

    elif msg_type in [
        client.CMsgPlayerDraws,
        client.CMsgPlayerDrawsLoose,
        client.CMsgPlayerPungs,
        client.CMsgPlayerKongs,
        client.CMsgPlayerChows,
        client.CMsgPlayerFormsClosedPung,
        client.CMsgPlayerFormsClosedChow,
        client.CMsgPlayerPairs,
        client.CMsgPlayerFormsClosedPair,
        client.CMsgPlayerSpecialSet,
        client.CMsgPlayerFormsClosedSpecialSet,
        client.CMsgSwapTile
    ]:
        action_id = game_mgr.handle_cmsg(cm)
        # DO SOMETHING

    elif msg_type == client.CMsgPlayerDiscards:
        game_mgr.handle_cmsg(cm)
        active_player = game_mgr.get_active_player_number()
        discarded_tile = game_mgr.get_last_discarded_tile()
        print('Player {} discarded tile {}'.format(
            active_player, discarded_tile))
        game_state.discard_tile(active_player, discarded_tile)
        if game_mgr.is_our_turn():
            # It's our decision, record it.
            states_in_game.append(deepcopy(game_state))
        lets_play_it()
    elif msg_type == client.CMsgPlayerDeclaresClosedKong:
        game_mgr.handle_cmsg(cm)
        lets_play_it()
    elif msg_type == client.CMsgPlayerAddsToPung:
        game_mgr.handle_cmsg(cm)
        lets_play_it()
    elif msg_type == client.CMsgStartPlay:
        game_mgr.handle_cmsg(cm)
    elif msg_type == client.CMsgPlayerReady:
        is_discard_locked = False
        game_mgr.handle_cmsg(cm)
        lets_play_it()
    elif msg_type == client.CMsgPause:
        game_mgr.handle_cmsg(cm)
        lets_play_it()
    elif msg_type == client.CMsgPlayerOptionSet:
        pass
    elif msg_type == client.CMsgRedirect:
        pass
