%module client
%include "cpointer.i"
%include "carrays.i"

%{
#define SWIG_FILE_WITH_INIT
#include "client.h"
#include "game.h"
#include "protocol.h"
#include "protocol_helper.h"
#include "sysdep.h"
#include "client_helper.h"
#include <stdbool.h>
%}

%pointer_functions(Player, PlayerP);
%pointer_cast(PlayerP, Player *, playerp_to_playerp_nat);
%array_functions(PlayerP, PlayerPs);
%array_functions(Tile, Tiles);
%array_functions(int, ints);

Game *client_init(char *address);
Game *client_reinit(int fd);
int client_connect(Game *g, int id, char *name);
Game *client_close(Game *g);
char *fd_get_line(int fd);
int client_send_packet(Game *g, PMsgMsg *m);
int game_handle_cmsg(Game *g, CMsgMsg *m);
const char *tile_code(Tile t);
Tile tile_decode(const char *c);
typedef enum { east = 0, south = 1, west = 2, north = 3, noseat = -1 } seats;
seats game_id_to_seat(Game *g, int id);
typedef short Tile;
#define HiddenTile ((Tile) 0)

extern CMsgMsg *decode_cmsg(char *arg);
extern char *encode_pmsg(PMsgMsg *msg);

CMsgErrorMsg *CMsg_to_CMsgErrorMsg(CMsgMsg *msg);


PMsgMsg *PMsgSaveStateMsg_to_PMsg(PMsgSaveStateMsg *msg);


CMsgStateSavedMsg *CMsg_to_CMsgStateSavedMsg(CMsgMsg *msg);


PMsgMsg *PMsgLoadStateMsg_to_PMsg(PMsgLoadStateMsg *msg);


CMsgInfoTilesMsg  *CMsg_to_CMsgInfoTilesMsg (CMsgMsg *msg);


PMsgMsg *PMsgConnectMsg_to_PMsg(PMsgConnectMsg *msg);


CMsgConnectReplyMsg *CMsg_to_CMsgConnectReplyMsg(CMsgMsg *msg);


CMsgAuthReqdMsg *CMsg_to_CMsgAuthReqdMsg(CMsgMsg *msg);


PMsgMsg *PMsgAuthInfoMsg_to_PMsg(PMsgAuthInfoMsg *msg);


PMsgMsg *PMsgNewAuthInfoMsg_to_PMsg(PMsgNewAuthInfoMsg *msg);


CMsgRedirectMsg *CMsg_to_CMsgRedirectMsg(CMsgMsg *msg);


PMsgMsg *PMsgRequestReconnectMsg_to_PMsg(PMsgRequestReconnectMsg *msg);


CMsgReconnectMsg *CMsg_to_CMsgReconnectMsg(CMsgMsg *msg);


PMsgMsg *PMsgDisconnectMsg_to_PMsg(PMsgDisconnectMsg *msg);


CMsgPlayerMsg *CMsg_to_CMsgPlayerMsg(CMsgMsg *msg);


CMsgGameMsg *CMsg_to_CMsgGameMsg(CMsgMsg *msg);


CMsgNewRoundMsg *CMsg_to_CMsgNewRoundMsg(CMsgMsg *msg);


CMsgNewHandMsg *CMsg_to_CMsgNewHandMsg(CMsgMsg *msg);


CMsgPlayerDrawsMsg *CMsg_to_CMsgPlayerDrawsMsg(CMsgMsg *msg);


CMsgPlayerDrawsLooseMsg *CMsg_to_CMsgPlayerDrawsLooseMsg(CMsgMsg *msg);


PMsgMsg *PMsgDeclareSpecialMsg_to_PMsg(PMsgDeclareSpecialMsg *msg);


CMsgPlayerDeclaresSpecialMsg *CMsg_to_CMsgPlayerDeclaresSpecialMsg(CMsgMsg *msg);


CMsgStartPlayMsg *CMsg_to_CMsgStartPlayMsg(CMsgMsg *msg);


CMsgStopPlayMsg *CMsg_to_CMsgStopPlayMsg(CMsgMsg *msg);


PMsgMsg *PMsgRequestPauseMsg_to_PMsg(PMsgRequestPauseMsg *msg);


CMsgPauseMsg *CMsg_to_CMsgPauseMsg(CMsgMsg *msg);


PMsgMsg *PMsgReadyMsg_to_PMsg(PMsgReadyMsg *msg);


CMsgPlayerReadyMsg  *CMsg_to_CMsgPlayerReadyMsg(CMsgMsg *msg);


PMsgMsg *PMsgDiscardMsg_to_PMsg(PMsgDiscardMsg *msg);


CMsgPlayerDiscardsMsg  *CMsg_to_CMsgPlayerDiscardsMsg(CMsgMsg *msg);


PMsgMsg *PMsgNoClaimMsg_to_PMsg(PMsgNoClaimMsg *msg);


CMsgPlayerDoesntClaimMsg  *CMsg_to_CMsgPlayerDoesntClaimMsg(CMsgMsg *msg);


CMsgDangerousDiscardMsg  *CMsg_to_CMsgDangerousDiscardMsg(CMsgMsg *msg);


PMsgMsg *PMsgPungMsg_to_PMsg(PMsgPungMsg *msg);


CMsgPlayerClaimsPungMsg  *CMsg_to_CMsgPlayerClaimsPungMsg(CMsgMsg *msg);


CMsgClaimDeniedMsg  *CMsg_to_CMsgClaimDeniedMsg(CMsgMsg *msg);


CMsgPlayerPungsMsg  *CMsg_to_CMsgPlayerPungsMsg(CMsgMsg *msg);


PMsgMsg *PMsgFormClosedPungMsg_to_PMsg(PMsgFormClosedPungMsg *msg);


CMsgPlayerFormsClosedPungMsg *CMsg_to_CMsgPlayerFormsClosedPungMsg(CMsgMsg *msg);


PMsgMsg *PMsgKongMsg_to_PMsg(PMsgKongMsg *msg);


CMsgPlayerClaimsKongMsg *CMsg_to_CMsgPlayerClaimsKongMsg(CMsgMsg *msg);


CMsgPlayerKongsMsg *CMsg_to_CMsgPlayerKongsMsg(CMsgMsg *msg);


PMsgMsg *PMsgDeclareClosedKongMsg_to_PMsg(PMsgDeclareClosedKongMsg *msg);


CMsgPlayerDeclaresClosedKongMsg *CMsg_to_CMsgPlayerDeclaresClosedKongMsg(CMsgMsg *msg);


PMsgMsg *PMsgAddToPungMsg_to_PMsg(PMsgAddToPungMsg *msg);


CMsgPlayerAddsToPungMsg *CMsg_to_CMsgPlayerAddsToPungMsg(CMsgMsg *msg);


CMsgPlayerRobsKongMsg *CMsg_to_CMsgPlayerRobsKongMsg(CMsgMsg *msg);


PMsgMsg *PMsgQueryMahJongMsg_to_PMsg(PMsgQueryMahJongMsg *msg);


CMsgCanMahJongMsg *CMsg_to_CMsgCanMahJongMsg(CMsgMsg *msg);


PMsgMsg *PMsgChowMsg_to_PMsg(PMsgChowMsg *msg);


CMsgPlayerClaimsChowMsg *CMsg_to_CMsgPlayerClaimsChowMsg(CMsgMsg *msg);


CMsgPlayerChowsMsg *CMsg_to_CMsgPlayerChowsMsg(CMsgMsg *msg);


PMsgMsg *PMsgFormClosedChowMsg_to_PMsg(PMsgFormClosedChowMsg *msg);


CMsgPlayerFormsClosedChowMsg *CMsg_to_CMsgPlayerFormsClosedChowMsg(CMsgMsg *msg);


PMsgMsg *PMsgDeclareWashOutMsg_to_PMsg(PMsgDeclareWashOutMsg *msg);


CMsgWashOutMsg *CMsg_to_CMsgWashOutMsg(CMsgMsg *msg);


PMsgMsg *PMsgMahJongMsg_to_PMsg(PMsgMahJongMsg *msg);


CMsgPlayerClaimsMahJongMsg *CMsg_to_CMsgPlayerClaimsMahJongMsg(CMsgMsg *msg);


CMsgPlayerMahJongsMsg *CMsg_to_CMsgPlayerMahJongsMsg(CMsgMsg *msg);


PMsgMsg *PMsgPairMsg_to_PMsg(PMsgPairMsg *msg);


CMsgPlayerPairsMsg *CMsg_to_CMsgPlayerPairsMsg(CMsgMsg *msg);


PMsgMsg *PMsgFormClosedPairMsg_to_PMsg(PMsgFormClosedPairMsg *msg);


CMsgPlayerFormsClosedPairMsg *CMsg_to_CMsgPlayerFormsClosedPairMsg(CMsgMsg *msg);


PMsgMsg *PMsgSpecialSetMsg_to_PMsg(PMsgSpecialSetMsg *msg);


CMsgPlayerSpecialSetMsg *CMsg_to_CMsgPlayerSpecialSetMsg(CMsgMsg *msg);


PMsgMsg *PMsgFormClosedSpecialSetMsg_to_PMsg(PMsgFormClosedSpecialSetMsg *msg);


CMsgPlayerFormsClosedSpecialSetMsg *CMsg_to_CMsgPlayerFormsClosedSpecialSetMsg(CMsgMsg *msg);


PMsgMsg *PMsgShowTilesMsg_to_PMsg(PMsgShowTilesMsg *msg);


CMsgPlayerShowsTilesMsg *CMsg_to_CMsgPlayerShowsTilesMsg(CMsgMsg *msg);


CMsgHandScoreMsg *CMsg_to_CMsgHandScoreMsg(CMsgMsg *msg);


CMsgSettlementMsg *CMsg_to_CMsgSettlementMsg(CMsgMsg *msg);


PMsgMsg *PMsgSetPlayerOptionMsg_to_PMsg(PMsgSetPlayerOptionMsg *msg);


CMsgPlayerOptionSetMsg *CMsg_to_CMsgPlayerOptionSetMsg(CMsgMsg *msg);


CMsgGameOverMsg *CMsg_to_CMsgGameOverMsg(CMsgMsg *msg);


PMsgMsg *PMsgSetGameOptionMsg_to_PMsg(PMsgSetGameOptionMsg *msg);


CMsgGameOptionMsg *CMsg_to_CMsgGameOptionMsg(CMsgMsg *msg);


PMsgMsg *PMsgQueryGameOptionMsg_to_PMsg(PMsgQueryGameOptionMsg *msg);


PMsgMsg *PMsgListGameOptionsMsg_to_PMsg(PMsgListGameOptionsMsg *msg);


PMsgMsg *PMsgChangeManagerMsg_to_PMsg(PMsgChangeManagerMsg *msg);


CMsgChangeManagerMsg *CMsg_to_CMsgChangeManagerMsg(CMsgMsg *msg);


PMsgMsg *PMsgSendMessageMsg_to_PMsg(PMsgSendMessageMsg *msg);


CMsgMessageMsg *CMsg_to_CMsgMessageMsg(CMsgMsg *msg);


CMsgWallMsg *CMsg_to_CMsgWallMsg(CMsgMsg *msg);


CMsgCommentMsg *CMsg_to_CMsgCommentMsg(CMsgMsg *msg);


PMsgMsg *PMsgSwapTileMsg_to_PMsg(PMsgSwapTileMsg *msg);


CMsgSwapTileMsg *CMsg_to_CMsgSwapTileMsg(CMsgMsg *msg);

typedef enum {
  CMsgError = 0,
  CMsgInfoTiles = 1,
  CMsgStateSaved = 2,
  CMsgConnectReply = 10,
  CMsgReconnect = 11,
  CMsgAuthReqd = 12,
  CMsgRedirect = 13,
  CMsgPlayer = 20,
  CMsgNewRound = 29,
  CMsgGame = 30,
  CMsgNewHand = 31,
  CMsgPlayerDeclaresSpecial = 34,
  CMsgStartPlay = 35,
  CMsgStopPlay = 36,
  CMsgPause = 37,
  CMsgPlayerReady = 38,
  CMsgPlayerDraws = 40,
  CMsgPlayerDrawsLoose = 41,
  CMsgPlayerDiscards = 50,
  CMsgClaimDenied = 51,
  CMsgPlayerDoesntClaim = 52,
  CMsgDangerousDiscard = 55,
  CMsgPlayerClaimsPung = 60,
  CMsgPlayerPungs = 61,
  CMsgPlayerFormsClosedPung = 62,
  CMsgPlayerClaimsKong = 70,
  CMsgPlayerKongs = 71,
  CMsgPlayerDeclaresClosedKong = 80,
  CMsgPlayerAddsToPung = 81,
  CMsgPlayerRobsKong = 85,
  CMsgCanMahJong = 87,
  CMsgPlayerClaimsChow = 90,
  CMsgPlayerChows = 91,
  CMsgPlayerFormsClosedChow = 92,
  CMsgWashOut = 99,
  CMsgPlayerClaimsMahJong = 100,
  CMsgPlayerMahJongs = 101,
  CMsgPlayerPairs = 102,
  CMsgPlayerFormsClosedPair = 103,
  CMsgPlayerShowsTiles = 105,
  CMsgPlayerSpecialSet = 106,
  CMsgPlayerFormsClosedSpecialSet = 107,
  CMsgPlayerOptionSet = 110,
  CMsgHandScore = 115,
  CMsgSettlement = 120,
  CMsgGameOver = 200,
  CMsgGameOption = 300,
  CMsgChangeManager = 310,
  CMsgMessage = 400,
  CMsgWall = 900,
  CMsgComment = 999,
  CMsgSwapTile = 1000,
} ControllerMsgType;

/* Types of message sent by player. The numbers more or less
   match the corresponding controller messages.
*/
typedef enum {
  PMsgSaveState = 1,
  PMsgLoadState = 2,
  PMsgConnect = 10,
  PMsgRequestReconnect = 11,
  PMsgAuthInfo = 12,
  PMsgNewAuthInfo = 13,
  PMsgDisconnect = 14,
  PMsgDeclareSpecial = 33,
  PMsgRequestPause = 36,
  PMsgReady = 37,
  PMsgDiscard = 50,
  PMsgNoClaim = 51,
  PMsgPung = 60,
  PMsgFormClosedPung = 62,
  PMsgKong = 70,
  PMsgDeclareClosedKong = 80,
  PMsgAddToPung = 81,
  PMsgQueryMahJong = 87,
  PMsgChow = 90,
  PMsgFormClosedChow = 92,
  PMsgDeclareWashOut = 99,
  PMsgMahJong = 100,
  PMsgPair = 102,
  PMsgFormClosedPair = 103,
  PMsgShowTiles = 105,
  PMsgSpecialSet = 106,
  PMsgFormClosedSpecialSet = 107,
  PMsgSetPlayerOption = 110,
  PMsgSetGameOption = 300,
  PMsgQueryGameOption = 301,
  PMsgListGameOptions = 302,
  PMsgChangeManager = 310,
  PMsgSendMessage = 400,
  PMsgSwapTile = 1000,
} PlayerMsgType;

typedef struct _CMsgErrorMsg {
  ControllerMsgType type; /* CMsgError */
  int seqno; /* sequence number of player message provoking error, or 0 */
  char *error; /* human readable explanation */
} CMsgErrorMsg;

typedef struct _PMsgListGameOptionsMsg {
  PlayerMsgType type; /* PMsgListGameOptions */
  bool include_disabled; /* send even disabled options */
} PMsgListGameOptionsMsg;

typedef struct _CMsgMsg {
  ControllerMsgType type;
} CMsgMsg;

typedef struct _PMsgMsg {
  PlayerMsgType type;
} PMsgMsg;


typedef struct _Game {
  PlayerP players[NUM_SEATS]; /* the players */
  TileWind round; /* wind of the current round */
  int hands_as_east; /* number of hands completed with this dealer
		      (excluding current hand, except in state
		      HandComplete) */
  int firsteast; /* id of player who was east in first hand of game */
  GameState state; /* the state (see above) of the game */
  /* state dependent extra information */
  int active; /* players may not move unless the game is active */
  char *paused; /* This also stops moves; but it is a pause waiting
		   for players' permission to receive. The non-NULL
		   value is the reason for the pause.
		   If this is set, the ready array records
		   who we're still waiting for */
  /* The next fields are used for lots of auxiliary state information */
  seats player; /* the player doing something */
  Whence whence; /* where did the player's last tile come from? */
  seats supplier; /* and if from a discard, who supplied it? */
  Tile tile; /* and what was it? */
  Whence needs; /* where does the player need to get a tile from? */
  int serial; /* serial number of current discard/kong */
  Claims claims[NUM_SEATS]; /* who's claimed for the current discard */
  ChowPosition cpos; /* if a chow has been claimed, for which position? */
  int chowpending; /* is a chow in progress? */
  int mjpending; /* is a mah-jong from discard in progress? */
  Konging konging; /* is a kong in progress? */
  int ready[NUM_SEATS]; /* who is ready in a pause ? */
  unsigned int flags; /* misc flags. This will be zeroed at start of hand */
  /* This represents the wall.
     There is a hard-wired array, which needs to be big enough
     to accommodate all walls we might see.
     The  live_used  member gives the number of tiles used from the
     live wall; the live_end gives the end of the live wall;
     and the dead_end gives the end of the dead wall.
     Thus the live wall goes from live_used to (live_end-1)
     and the dead wall from live_end to (dead_end-1).
     Game options (will) determine how these are changed.
     The current setting is a fixed 16-tile kong box.
  */
  struct {
    Tile tiles[MAX_WALL_SIZE]; /* the tiles */
    int live_used; /* number of live tiles drawn */
    int live_end; /* start of dead wall */
    int dead_end; /* end of wall */
    int size; /* size of wall as dealt */
  } wall;
  /* This is a convenience to track the number of tiles of each value
     displayed on the table. It is (always) maintained by handle_cmsg. */
  Tile exposed_tile_count[MaxTile];
  /* This is the same, but tracks only discards */
  Tile discarded_tile_count[MaxTile];
  /* the following can be set to 1 to make the handle_cmsg
     function check the legality of all the messages.
     Otherwise, it will apply them blindly.
     (So client programs using this module will probably leave it zero.)
  */
  int cmsg_check;
  /* This is used by handle_cmsg to return error messages
     when it fails. */
  char *cmsg_err;
  int protversion; /* protocol version level for this game */
  int manager; /* id of the player who owns this game and
		  can set the game options. By default, 0,
		  in which case any player can set options.
		  In that case, any player can claim ownership, first
		  come first served.
		  Can be set to -1 to prohibit any use of
		  managerial functions.
	       */
  /* option table. */
  GameOptionTable option_table;
  int fd; /* for use by client programs */
  int cseqno; /* for use by the client_ routines */
  void *userdata; /* for client extensions */
} Game;

typedef struct _Player {
  int id; /* unique identifier assigned by the master controller,
	     and used in communication. Always non-zero for a real player. */
  char *name; /* the name of this player */
  TileWind wind; /* which wind this player currently is */
  int num_concealed; /* how many concealed tiles */
#define MAX_CONCEALED 14
  Tile concealed[MAX_CONCEALED]; /* the concealed tiles (if known) */
  int discard_hint; /* this is used by programs to tell player_discards_tile
		       which tile to discard, when the order of identical
		       tiles is important, as is the case when maintaining
		       a display of the hand according to the user's
		       preferences. */
#define MAX_TILESETS 7 /* may have up to seven pairs.
			  Note: this happens even without the seven
			  pairs hand, since the player_can_mah_jong
			  function blindly looks for pairs. Perhaps
			  it shouldn't. */
  TileSet tilesets[MAX_TILESETS]; /* exposed tiles */
  int num_specials; /* number of flowers and seasons held */
  Tile specials[8]; /* flowers and seasons */
  unsigned int flags; /* for bit definitions, see below */
  unsigned int dflags[NUM_SEATS]; /* see below */
  int cumulative_score; /* score so far in the game (excluding current hand)*/
  int hand_score; /* score in this hand. Set to -1 during hand. */
  char *err; /* used to return error messages by methods. Value is
		only meaningful after a method has failed (including
		test functions returning false). */
  void *userdata; /* for client programs */
} Player ;

typedef const Player *PlayerP;

typedef enum {
  HandComplete = 0, /* a hand has been finished, scored, and scores settled,
		   but the deal has not yet rotated. The player member
		   contains the seat of the player who went mah jong,
		   or -1 if the hand was drawn.
		   This is also the initial state (with seat -1) after
		   a Game message is handled.
		   The claims array is used to note which
		   players have requested to start the next hand.
		    */
  Dealing = 1, /* the deal is in progress */
  DeclaringSpecials = 2, /* the deal is complete, and we are declaring
			flowers and seasons. The player member
			contains the seat (NB) of the player due to declare */
  Discarding = 3, /* the current player is due to discard.
                 The player member contains the current
		 player as a seat.
		 The tile member notes the tile that was drawn.
		 The whence member tells where the extra tile
		 obtained by the player came from:
		 FromWall, FromDiscard, FromLoose, FromRobbedKong.
		 If it was FromDiscard, the supplier holds
		 the *seat* of the discarder. This is needed for
		 scoring systems that punish such people.
		 The needs records if the player needs to draw
		 another tile, because of, say, declaring specials
		 or kongs. It is FromNone, FromWall, or FromLoose.
		 The konging records if the player has just
		 melded to a pung (or declared a concealed kong)
		 which is potentially robbable. It is
		 NotKonging (unset), AddingToPung, DeclaringKong; if it is
		 set, then tile is the tile of the kong.
		 The claims record may contain MahJongClaims to indicate
		 a desire to rob the kong.
	      */
  Discarded = 4,  /* the current player has just discarded; other players are
		 making claims. The info record contains the following
		 members:
		 player the player that has discarded
		 tile   the tile that was discarded
		 serial  serial number of this discard
		 claims[seats]  contains
		   Discard/Chow/Pung/Kong/MahJong/NoClaim accordingly, or 0
		   if no claim has yet been received.
		 cpos  the ChowPosition, if the right hand player
                   has made a chow claim
		 chowpending  true if an unspecified chow claim has been
		          granted, but no specified claim has yet
                          been received.
	      */
  MahJonging = 5, /* the current player has  mah jong (which we've verified) and we
                 are declaring the hands
                 The info record contains the following members:
                 player  the player going mah jong
		 whence  where did the mahjong tile come from
		 supplier  if a discard/kong, who discarded (a seat)
		 tile    the tile that completed the hand
		 mjpending  if true, the mahjong was claimed
		          from a discard or robbed kong, but the discard
			  has not yet been declared in a set
		 chowpending mjpending, and the player has declared
		          a chow without specifying the position.
	      */
} GameState;

typedef struct _PMsgDeclareSpecialMsg { /* alias ds */
  PlayerMsgType type; /* PMsgDeclareSpecial */
  Tile tile; /* tile being declared, or blank */
} PMsgDeclareSpecialMsg;

typedef struct _PMsgDiscardMsg { /* alias d */
  PlayerMsgType type; /* PMsgDiscard */
  Tile tile; /* tile to be discarded */
  bool calling; /* player is making a Calling declaration */
} PMsgDiscardMsg;

typedef struct _PMsgNoClaimMsg { /* alias n */
  PlayerMsgType type; /* PMsgNoClaim */
  int discard; /* serial number of discard */
} PMsgNoClaimMsg;

typedef enum {
  Hidden, /* true if we can't see the player's hand */
  MahJongged, /* true if this hand has gone mah jongg */
  HandDeclared, /* true if the hand has been declared, and accordingly
		   the "concealed" tiles are no longer. Implies Hidden is
		   false */
  /* the next three flags are used to handle calling declarations */
  /* the next flag is set internally by the player module */
  NoDiscard, /* true before the first discard */
  /* the next two flags must be set by the user of this module,
     and are cleared by the player_newhand function */
  OriginalCall, /* true if the player has made an original call */
  Calling, /* true if the player has made a calling declaration
	      (when implemented) */
       } PlayerFlags;

int test_flag(Player p, PlayerFlags flag);

typedef enum {
  MJSevenPairs = 1
} MJSpecialHandFlags;

int player_can_mah_jong(PlayerP p, Tile d, MJSpecialHandFlags flags);
