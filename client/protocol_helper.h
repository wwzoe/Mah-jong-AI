/*
  This file handles the type conversion between XMsgMsg and its 'substruct'.
*/
#ifndef PROTOCOL_HELPER_H
#define PROTOCOL_HELPER_H

#include "protocol.h"

//  Controller message is below
CMsgErrorMsg *CMsg_to_CMsgErrorMsg(CMsgMsg *msg);

//  state of current game
PMsgMsg *PMsgSaveStateMsg_to_PMsg(PMsgSaveStateMsg *msg);

// requests server load the game state from a saved file
CMsgStateSavedMsg *CMsg_to_CMsgStateSavedMsg(CMsgMsg *msg);

// controller to save the state
PMsgMsg *PMsgLoadStateMsg_to_PMsg(PMsgLoadStateMsg *msg);

//sent to a player whenever its hand changes
CMsgInfoTilesMsg  *CMsg_to_CMsgInfoTilesMsg (CMsgMsg *msg);

//Message sent by player after connecting to controller.
PMsgMsg *PMsgConnectMsg_to_PMsg(PMsgConnectMsg *msg);

//Message sent by controller to player on receipt of ConnectMsg */
CMsgConnectReplyMsg *CMsg_to_CMsgConnectReplyMsg(CMsgMsg *msg);

//Message sent by controller to request authentication.
CMsgAuthReqdMsg *CMsg_to_CMsgAuthReqdMsg(CMsgMsg *msg);

//Message sent by player to provide authentication.
PMsgMsg *PMsgAuthInfoMsg_to_PMsg(PMsgAuthInfoMsg *msg);

//Message sent by player to provide new authentication info.
PMsgMsg *PMsgNewAuthInfoMsg_to_PMsg(PMsgNewAuthInfoMsg *msg);

//Message sent by controller to tell player to close connection and connect to another port.
CMsgRedirectMsg *CMsg_to_CMsgRedirectMsg(CMsgMsg *msg);

// message requests a "reconnection"
PMsgMsg *PMsgRequestReconnectMsg_to_PMsg(PMsgRequestReconnectMsg *msg);

//This message grants a reconnection request.
CMsgReconnectMsg *CMsg_to_CMsgReconnectMsg(CMsgMsg *msg);

//This message is an explicit disconnect to quit the game.
PMsgMsg *PMsgDisconnectMsg_to_PMsg(PMsgDisconnectMsg *msg);

//Message sent by controller to inform players of each other's existence.
CMsgPlayerMsg *CMsg_to_CMsgPlayerMsg(CMsgMsg *msg);

//Message sent by controller to initiate a game
CMsgGameMsg *CMsg_to_CMsgGameMsg(CMsgMsg *msg);

//Message to say that the wind of the round has changed
CMsgNewRoundMsg *CMsg_to_CMsgNewRoundMsg(CMsgMsg *msg);

//Message sent by controller to start new hand
CMsgNewHandMsg *CMsg_to_CMsgNewHandMsg(CMsgMsg *msg);

//Message sent by controller to draw one tile for player.
CMsgPlayerDrawsMsg *CMsg_to_CMsgPlayerDrawsMsg(CMsgMsg *msg);

//Message sent by controller to draw a loose tile for player.
CMsgPlayerDrawsLooseMsg *CMsg_to_CMsgPlayerDrawsLooseMsg(CMsgMsg *msg);

//Message sent by the player to declare a special tile.
PMsgMsg *PMsgDeclareSpecialMsg_to_PMsg(PMsgDeclareSpecialMsg *msg);

//Message sent by controller to implement special declaration. */
CMsgPlayerDeclaresSpecialMsg *CMsg_to_CMsgPlayerDeclaresSpecialMsg(CMsgMsg *msg);

//This message is sent to all players, to tell them they maystart normal play.
CMsgStartPlayMsg *CMsg_to_CMsgStartPlayMsg(CMsgMsg *msg);

//This message is sent to all players to stop play.
CMsgStopPlayMsg *CMsg_to_CMsgStopPlayMsg(CMsgMsg *msg);

//This message is sent by a player to request a pause in play.
PMsgMsg *PMsgRequestPauseMsg_to_PMsg(PMsgRequestPauseMsg *msg);

// This message is sent by the controller when it wishes to gain
CMsgPauseMsg *CMsg_to_CMsgPauseMsg(CMsgMsg *msg);

//this is the reply
PMsgMsg *PMsgReadyMsg_to_PMsg(PMsgReadyMsg *msg);

//tells other players who's ready
CMsgPlayerReadyMsg  *CMsg_to_CMsgPlayerReadyMsg(CMsgMsg *msg);

//Message sent by player to announce discard
PMsgMsg *PMsgDiscardMsg_to_PMsg(PMsgDiscardMsg *msg);

// Message sent by controller to implement discard
CMsgPlayerDiscardsMsg  *CMsg_to_CMsgPlayerDiscardsMsg(CMsgMsg *msg);

//sent by a player to say that it has no claim on the current discard.
PMsgMsg *PMsgNoClaimMsg_to_PMsg(PMsgNoClaimMsg *msg);

//Message sent by controller to say that a player is making no claim on the current discard
CMsgPlayerDoesntClaimMsg  *CMsg_to_CMsgPlayerDoesntClaimMsg(CMsgMsg *msg);

//sent by the controller after a claim has been implemented to announce that the discard was dangerous.
CMsgDangerousDiscardMsg  *CMsg_to_CMsgDangerousDiscardMsg(CMsgMsg *msg);

//Message sent by player to claim a pung.
PMsgMsg *PMsgPungMsg_to_PMsg(PMsgPungMsg *msg);

//Message sent by controller to other players to inform them of a pung claim (NOT of its success).
CMsgPlayerClaimsPungMsg  *CMsg_to_CMsgPlayerClaimsPungMsg(CMsgMsg *msg);

//generic refusal message sent by controller to deny a claim.
CMsgClaimDeniedMsg  *CMsg_to_CMsgClaimDeniedMsg(CMsgMsg *msg);

//Message sent by controller to implement a successful pung claim.
CMsgPlayerPungsMsg  *CMsg_to_CMsgPlayerPungsMsg(CMsgMsg *msg);

//Message to declare a closed pung during scoring
PMsgMsg *PMsgFormClosedPungMsg_to_PMsg(PMsgFormClosedPungMsg *msg);

//
CMsgPlayerFormsClosedPungMsg *CMsg_to_CMsgPlayerFormsClosedPungMsg(CMsgMsg *msg);

//
PMsgMsg *PMsgKongMsg_to_PMsg(PMsgKongMsg *msg);

//Message sent by controller to other players to inform them of a pung claim (NOT of its success).
CMsgPlayerClaimsKongMsg *CMsg_to_CMsgPlayerClaimsKongMsg(CMsgMsg *msg);

//Message sent by controller to implement a successful pung claim.
CMsgPlayerKongsMsg *CMsg_to_CMsgPlayerKongsMsg(CMsgMsg *msg);

//Message sent by player to announce a concealed kong. */
PMsgMsg *PMsgDeclareClosedKongMsg_to_PMsg(PMsgDeclareClosedKongMsg *msg);

//Message sent by controller to implement a concealed kong
CMsgPlayerDeclaresClosedKongMsg *CMsg_to_CMsgPlayerDeclaresClosedKongMsg(CMsgMsg *msg);

//Message sent by player to add drawn tile to exposed pung */
PMsgMsg *PMsgAddToPungMsg_to_PMsg(PMsgAddToPungMsg *msg);

//Message sent by controller to implement adding to a pung
CMsgPlayerAddsToPungMsg *CMsg_to_CMsgPlayerAddsToPungMsg(CMsgMsg *msg);

//Message sent by controller to say that the player has robbed the just declared kong
CMsgPlayerRobsKongMsg *CMsg_to_CMsgPlayerRobsKongMsg(CMsgMsg *msg);

//Message sent by player to ask whether it has a mah-jong hand.
PMsgMsg *PMsgQueryMahJongMsg_to_PMsg(PMsgQueryMahJongMsg *msg);

//the reply
CMsgCanMahJongMsg *CMsg_to_CMsgCanMahJongMsg(CMsgMsg *msg);

//Message sent by player to claim chow.
PMsgMsg *PMsgChowMsg_to_PMsg(PMsgChowMsg *msg);

//Message sent by controller to announce a chow claim
CMsgPlayerClaimsChowMsg *CMsg_to_CMsgPlayerClaimsChowMsg(CMsgMsg *msg);

//Message sent by controller to implement a chow claim.
CMsgPlayerChowsMsg *CMsg_to_CMsgPlayerChowsMsg(CMsgMsg *msg);

//To form a closed chow during scoring.
PMsgMsg *PMsgFormClosedChowMsg_to_PMsg(PMsgFormClosedChowMsg *msg);

//
CMsgPlayerFormsClosedChowMsg *CMsg_to_CMsgPlayerFormsClosedChowMsg(CMsgMsg *msg);

// some rules allow a player to declare a washout under certain circumstances.
PMsgMsg *PMsgDeclareWashOutMsg_to_PMsg(PMsgDeclareWashOutMsg *msg);

//Message sent by controller to declare a dead hand
CMsgWashOutMsg *CMsg_to_CMsgWashOutMsg(CMsgMsg *msg);

//Message sent by player to claim Mah-Jong.
PMsgMsg *PMsgMahJongMsg_to_PMsg(PMsgMahJongMsg *msg);

//Message sent by controller to announce mah-jong claim
CMsgPlayerClaimsMahJongMsg *CMsg_to_CMsgPlayerClaimsMahJongMsg(CMsgMsg *msg);

//essage sent by controller to announce successful mah-jong
CMsgPlayerMahJongsMsg *CMsg_to_CMsgPlayerMahJongsMsg(CMsgMsg *msg);

//Take the mah-jonged discard for a pair.
PMsgMsg *PMsgPairMsg_to_PMsg(PMsgPairMsg *msg);

//
CMsgPlayerPairsMsg *CMsg_to_CMsgPlayerPairsMsg(CMsgMsg *msg);

//Form a closed pair during scoring
PMsgMsg *PMsgFormClosedPairMsg_to_PMsg(PMsgFormClosedPairMsg *msg);

//
CMsgPlayerFormsClosedPairMsg *CMsg_to_CMsgPlayerFormsClosedPairMsg(CMsgMsg *msg);

//messages handle the case of special hands such as thirteen unique wonders
PMsgMsg *PMsgSpecialSetMsg_to_PMsg(PMsgSpecialSetMsg *msg);

//Player claims the discard to form a special set with all remaining tiles;this is a ShowTiles as well
CMsgPlayerSpecialSetMsg *CMsg_to_CMsgPlayerSpecialSetMsg(CMsgMsg *msg);

//
PMsgMsg *PMsgFormClosedSpecialSetMsg_to_PMsg(PMsgFormClosedSpecialSetMsg *msg);

//Form a special set in hand
CMsgPlayerFormsClosedSpecialSetMsg *CMsg_to_CMsgPlayerFormsClosedSpecialSetMsg(CMsgMsg *msg);

// sent by a losing player after it has finished making scoring combinations: it reveals the concealed tiles,
PMsgMsg *PMsgShowTilesMsg_to_PMsg(PMsgShowTilesMsg *msg);

//This message reveals a player's concealed tiles.
CMsgPlayerShowsTilesMsg *CMsg_to_CMsgPlayerShowsTilesMsg(CMsgMsg *msg);

// This message gives the calculated score for a hand.
CMsgHandScoreMsg *CMsg_to_CMsgHandScoreMsg(CMsgMsg *msg);

//This message announces the change in cumulative score for each player.
CMsgSettlementMsg *CMsg_to_CMsgSettlementMsg(CMsgMsg *msg);

//This message requests the controller to set a player option,
PMsgMsg *PMsgSetPlayerOptionMsg_to_PMsg(PMsgSetPlayerOptionMsg *msg);

//This informs the player that an option has been set.
CMsgPlayerOptionSetMsg *CMsg_to_CMsgPlayerOptionSetMsg(CMsgMsg *msg);

//Message to tell players game is over
CMsgGameOverMsg *CMsg_to_CMsgGameOverMsg(CMsgMsg *msg);

//Message to set a game option
PMsgMsg *PMsgSetGameOptionMsg_to_PMsg(PMsgSetGameOptionMsg *msg);

//Message to inform players of a game option value
CMsgGameOptionMsg *CMsg_to_CMsgGameOptionMsg(CMsgMsg *msg);

//Message to query a game option.
PMsgMsg *PMsgQueryGameOptionMsg_to_PMsg(PMsgQueryGameOptionMsg *msg);

//Message to query all game options
PMsgMsg *PMsgListGameOptionsMsg_to_PMsg(PMsgListGameOptionsMsg *msg);

//Request new manager for the game.
PMsgMsg *PMsgChangeManagerMsg_to_PMsg(PMsgChangeManagerMsg *msg);

//Give new manager for the game.
CMsgChangeManagerMsg *CMsg_to_CMsgChangeManagerMsg(CMsgMsg *msg);

//Send a message to other player(s).
PMsgMsg *PMsgSendMessageMsg_to_PMsg(PMsgSendMessageMsg *msg);

//Message from controller or other player.
CMsgMessageMsg *CMsg_to_CMsgMessageMsg(CMsgMsg *msg);

//This message is primarily used by the controller internally.
CMsgWallMsg *CMsg_to_CMsgWallMsg(CMsgMsg *msg);

//This message serves no purpose in the protocol
CMsgCommentMsg *CMsg_to_CMsgCommentMsg(CMsgMsg *msg);

//This message is for debugging and testing
PMsgMsg *PMsgSwapTileMsg_to_PMsg(PMsgSwapTileMsg *msg);

//
CMsgSwapTileMsg *CMsg_to_CMsgSwapTileMsg(CMsgMsg *msg);

#endif
