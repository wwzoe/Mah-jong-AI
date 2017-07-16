/*  mcts.c
*
*   implements a computer program to play mahjong. monte-carlo tree search(MCTS)
*   is appied in this program to make decision.
**/

#include "client.h"
#include "tilemap.h"


typedef struct _MctNode{
  int total_games;
  int win_games;
  TileMap tile_map;
} MctNode, *pMctNode;

typedef struct _MctTreeNode{
  pMctNode first_child;
  pMctNode next_sibling;
} MctTreeNode, *pMctTreeNode;

pMctNode train(pMctNode);
bool play(pMctNode);
Action expand(pMctNode);


/*
  Play game with given monte-carlo tree
 */
bool play(pMctNode currentNode) {
  while(game.status != end) {
    if(myturn){
      pMctNode currentNode = getcurrentNode(State);
      Action maxWinRateAction = max(currentNode);
      do(maxWinRateAction);
    }
  }
}

pMctNode train(pMctNode root) {
  Nodelist tracer;
  // Down to leaf node
  pMctNode presentNode = root
  tracer.add(presentNode);
  while(presentNode != leafnode) {
    presentNode = choosenextnode(presentNode);
      tracer.add(presentNode);
  }

  // Expand leaf node
  pMctNode expandedNode = expand(presentNode);
  gameResult = randomplay(expandedNode);

  backproagate(trancer, gameResult);

}

int main(int argc, char const *argv[]) {
  // Connect to server

  char *address = ":5000";
  char *name = "BetaMj";
  int our_id = 0;
  char *cmessage;

  Player our_player;
  Game game;

  game = client_init(address);
  //  Game initialization failed, program exits.
  if (!game) {
    exit(1);
  }

  client_connect(game, our_id, name);

  // Main loop
  while(true) {
    cmessage = get_line(game->fd);
    //  If message is null
    if(! cmessage) {
      exit(2);
    }
    dispatch_message(cmessage);
  }
  return 0;
}

//  Dispatch message to respective handlers.
int dispatch_message(char *msg){
  CMsgMsg *cm;

  if(msg == NULL) {
    warn("Receive a empty message from controller\n");
    exit(3);
  }

  cm = decode_cmsg(msg);
  if(cm == NULL) {
    warn("Protocol error on controller connection");
    return 0;
  }

  switch ( cm->type ) {
  case CMsgError:
    break; /* damn all we can do */
  case CMsgGameOver:
    exit(0);
  case CMsgReconnect:
    /* we should never receive this */
    warn("Received Reconnect command\n");
    exit(1);
  case CMsgInfoTiles:
    /* We ignore these. */
    break;
  case CMsgCanMahJong:
    /* Currently we ignore these, as we don't issue queries */
    break;
  case CMsgConnectReply:
    game_handle_cmsg(the_game,cm);
    our_id = the_game->players[0]->id;
    our_player = the_game->players[0];
    break;
  case CMsgAuthReqd:
    {
      CMsgAuthReqdMsg *carm = (CMsgAuthReqdMsg *)cm;
      PMsgAuthInfoMsg paim;
      paim.type = PMsgAuthInfo;
      if ( strncmp(carm->authtype,"basic",16) != 0 ) {
	warn("Asked for unknown authorization type %.16s",carm->authtype);
	exit(1);
      }
      strcpy(paim.authtype,"basic");
      if ( password == NULL ) {
	warn("Asked for password, don't have it");
	exit(1);
      }
      paim.authdata = password;
      send_packet(&paim);
    }
    break;
    /* In these cases, our seat might have changed, so we need to calculate it */
  case CMsgGame:
    /* In this case, we need to ask for the game options */
    {
      PMsgListGameOptionsMsg plgom;
      plgom.type = PMsgListGameOptions;
      plgom.include_disabled = 0;
      send_packet(&plgom);
    }
    /* and then ... */
  case CMsgNewRound:
  case CMsgNewHand:
    game_handle_cmsg(the_game,cm);
    our_seat = game_id_to_seat(the_game,our_id);
    if ( debugeval ) fprintf(debugf,"New hand\n");
    /* reset strategy to default */
    curstrat.chowness = stratparams[chowness].values[0];
    curstrat.hiddenness = stratparams[hiddenness].values[0];
    curstrat.majorness = stratparams[majorness].values[0];
    curstrat.suitness = stratparams[suitness].values[0];
    curstrat.suit = 0;
    break;
    /* in all these cases, game_handle_cmsg does all the work we want */
  case CMsgPlayer:
  case CMsgStopPlay:
  case CMsgClaimDenied:
  case CMsgPlayerDoesntClaim:
  case CMsgPlayerClaimsPung:
  case CMsgPlayerClaimsKong:
  case CMsgPlayerClaimsChow:
  case CMsgPlayerClaimsMahJong:
  case CMsgPlayerShowsTiles:
  case CMsgDangerousDiscard:
  case CMsgGameOption:
  case CMsgChangeManager:
  case CMsgWall:
  case CMsgComment:
  case CMsgStateSaved:
  case CMsgMessage:
    game_handle_cmsg(the_game,cm);
    break;
  case CMsgHandScore:
    /* if that was the winner, we should start scoring our hand */
    if ( ( game_handle_cmsg(the_game,cm)
	   == the_game->players[the_game->player]->id)
	 && the_game->active )
      do_something();
    break;
    /* after a Settlement or Washout message, do something: start next hand */
  case CMsgWashOut:
  case CMsgSettlement:
    game_handle_cmsg(the_game,cm);
    if ( the_game->active ) do_something();
    break;
    /* likewise after a washout */
    /* after a MahJong message, we should do something: namely
       start making our scoring sets. */
  case CMsgPlayerRobsKong:
  case CMsgPlayerMahJongs:
    game_handle_cmsg(the_game,cm);
    if ( the_game->active ) do_something();
    break;
    /* in the case of a PlayerDeclaresSpecials message, we need to
       do something if it is now our turn; but this isn't given
       by the affected id.
       However, if the state is Discarding, and no tiles have
       so far been discarded, we shouldn't do something
       now, since we are about to be asked to pause.
    */
  case CMsgPlayerDeclaresSpecial:
    game_handle_cmsg(the_game,cm);
    if ( the_game->player == our_seat && the_game->active
	 && ! ( the_game->state == Discarding && the_game->serial == 0 ))
      do_something();
    break;
    /* in these cases, we need to do something if the message
       is addressed to us. */
  case CMsgPlayerDraws:
  case CMsgPlayerDrawsLoose:
  case CMsgPlayerPungs:
  case CMsgPlayerKongs:
  case CMsgPlayerChows:
  case CMsgPlayerFormsClosedPung:
  case CMsgPlayerFormsClosedChow:
  case CMsgPlayerPairs:
  case CMsgPlayerFormsClosedPair:
  case CMsgPlayerSpecialSet:
  case CMsgPlayerFormsClosedSpecialSet:
  case CMsgSwapTile:
    if ( game_handle_cmsg(the_game,cm) == our_id && the_game->active)
      do_something();
    break;
    /* in this case, we need to do something else if it's not our turn! */
  case CMsgPlayerDiscards:
    if ( game_handle_cmsg(the_game,cm) != our_id && the_game->active)
      check_discard(our_player,&curstrat,0);
    break;
    /* if this is us, we need to do something, and if it's
       somebody else, we might be able to rob the kong */
  case CMsgPlayerDeclaresClosedKong:
    if ( game_handle_cmsg(the_game,cm) == our_id && the_game->active)
      do_something();
    else if ( the_game->active )
      check_discard(our_player,&curstrat,1); /* actually this checks the kong */
    break;
  case CMsgPlayerAddsToPung:
    if ( game_handle_cmsg(the_game,cm) == our_id && the_game->active)
      do_something();
    else if ( the_game->active )
      check_discard(our_player,&curstrat,0); /* actually this checks the kong */
    break;
    /* In this case, it depends on the state of the game */
  case CMsgStartPlay:
    /* We need to do something if the id is us, or 0. */
    { int id;
    id = game_handle_cmsg(the_game,cm);
    if ( id == our_id || id == 0 )
      do_something();
    }
    break;
    /* similarly */
  case CMsgPlayerReady:
    game_handle_cmsg(the_game,cm);
    if ( ! the_game->paused ) do_something();
    break;
  case CMsgPause:
    game_handle_cmsg(the_game,cm);
    do_something();
    break;
  case CMsgPlayerOptionSet:
    /* we don't recognize any options, so ignore it */
    break;
  case CMsgRedirect:
    warn("Redirect command not currently supported");
    exit(1);
  }
  return 1;
}
