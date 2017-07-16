/*
  This file handles the type conversion between XMsgMsg and its 'substruct'.
*/

#include "protocol_helper.h"

CMsgErrorMsg *CMsg_to_CMsgErrorMsg(CMsgMsg *msg) {
  //  先对CMsgMsg的类型进行判断，如果不是CMsgError(我们要转换到的类型)，那么返回0作为错误标记。
  if(msg -> type == CMsgError) {
    //  强制转换到CMsgErrorMsg类型的指针
    return (CMsgErrorMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgSaveStateMsg_to_PMsg(PMsgSaveStateMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgStateSavedMsg *CMsg_to_CMsgStateSavedMsg (CMsgMsg *msg) {
  //  先对CMsgMsg的类型进行判断，如果不是CMsgError(我们要转换到的类型)，那么返回0作为错误标记。
  if(msg -> type == CMsgStateSaved ) {
    //  强制转换到CMsgErrorMsg类型的指针
    return (CMsgStateSavedMsg  *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgLoadStateMsg_to_PMsg(PMsgLoadStateMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgInfoTilesMsg *CMsg_to_CMsgInfoTilesMsg (CMsgMsg *msg) {
  //  先对CMsgMsg的类型进行判断，如果不是CMsgError(我们要转换到的类型)，那么返回0作为错误标记。
  if(msg -> type == CMsgInfoTiles ) {
    //  强制转换到CMsgErrorMsg类型的指针
    return (CMsgInfoTilesMsg  *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgConnectMsg_to_PMsg(PMsgConnectMsg *msg) {

  return (PMsgMsg *) msg;
}



CMsgConnectReplyMsg  *CMsg_to_CMsgConnectReplyMsg (CMsgMsg *msg) {
  if(msg -> type == CMsgConnectReply) {
    return (CMsgConnectReplyMsg  *) msg;
  }
  else {
    return 0;
  }
}

CMsgAuthReqdMsg  *CMsg_to_CMsgAuthReqdMsg (CMsgMsg *msg) {
  if(msg -> type == CMsgAuthReqd) {
    return (CMsgAuthReqdMsg  *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgAuthInfoMsg_to_PMsg(PMsgAuthInfoMsg *msg) {

  return (PMsgMsg *) msg;
}

PMsgMsg *PMsgNewAuthInfoMsg_to_PMsg(PMsgNewAuthInfoMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgRedirectMsg  *CMsg_to_CMsgRedirectMsg (CMsgMsg *msg) {
  if(msg -> type == CMsgRedirect) {
    return (CMsgRedirectMsg  *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgRequestReconnectMsg_to_PMsg(PMsgRequestReconnectMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgReconnectMsg  *CMsg_to_CMsgReconnectMsg (CMsgMsg *msg) {
  if(msg -> type == CMsgReconnect) {
    return (CMsgReconnectMsg  *) msg;
  }
  else {
    return 0;
  }
}



PMsgMsg *PMsgDisconnectMsg_to_PMsg(PMsgDisconnectMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgPlayerMsg  *CMsg_to_CMsgPlayerMsg (CMsgMsg *msg) {
  if(msg -> type == CMsgPlayer) {
    return (CMsgPlayerMsg  *) msg;
  }
  else {
    return 0;
  }
}

CMsgGameMsg  *CMsg_to_CMsgGameMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgGame) {
    return (CMsgGameMsg  *) msg;
  }
  else {
    return 0;
  }
}

CMsgNewRoundMsg  *CMsg_to_CMsgNewRoundMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgNewRound) {
    return (CMsgNewRoundMsg  *) msg;
  }
  else {
    return 0;
  }
}

CMsgNewHandMsg  *CMsg_to_CMsgNewHandMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgNewHand) {
    return (CMsgNewHandMsg  *) msg;
  }
  else {
    return 0;
  }
}

CMsgPlayerDrawsMsg  *CMsg_to_CMsgPlayerDrawsMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerDraws) {
    return (CMsgPlayerDrawsMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgPlayerDrawsLooseMsg  *CMsg_to_CMsgPlayerDrawsLooseMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerDrawsLoose) {
    return (CMsgPlayerDrawsLooseMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgDeclareSpecialMsg_to_PMsg(PMsgDeclareSpecialMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerDeclaresSpecialMsg  *CMsg_to_CMsgPlayerDeclaresSpecialMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerDeclaresSpecial) {
    return (CMsgPlayerDeclaresSpecialMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgStartPlayMsg  *CMsg_to_CMsgStartPlayMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgStartPlay) {
    return (CMsgStartPlayMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgStopPlayMsg  *CMsg_to_CMsgStopPlayMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgStopPlay) {
    return (CMsgStopPlayMsg *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgRequestPauseMsg_to_PMsg(PMsgRequestPauseMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgPauseMsg  *CMsg_to_CMsgPauseMsg (CMsgMsg *msg) {
  if(msg -> type ==CMsgPause) {
    return (CMsgPauseMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgReadyMsg_to_PMsg(PMsgReadyMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerReadyMsg  *CMsg_to_CMsgPlayerReadyMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerReady) {
    return (CMsgPlayerReadyMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgDiscardMsg_to_PMsg(PMsgDiscardMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerDiscardsMsg  *CMsg_to_CMsgPlayerDiscardsMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerDiscards) {
    return (CMsgPlayerDiscardsMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgNoClaimMsg_to_PMsg(PMsgNoClaimMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerDoesntClaimMsg  *CMsg_to_CMsgPlayerDoesntClaimMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerDoesntClaim) {
    return (CMsgPlayerDoesntClaimMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgDangerousDiscardMsg  *CMsg_to_CMsgDangerousDiscardMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgDangerousDiscard) {
    return (CMsgDangerousDiscardMsg *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgPungMsg_to_PMsg(PMsgPungMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerClaimsPungMsg  *CMsg_to_CMsgPlayerClaimsPungMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerClaimsPung) {
    return (CMsgPlayerClaimsPungMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgClaimDeniedMsg *CMsg_to_CMsgClaimDeniedMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgClaimDenied) {
    return (CMsgClaimDeniedMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgPlayerPungsMsg  *CMsg_to_CMsgPlayerPungsMsg(CMsgMsg *msg) {
  if(msg -> type ==CMsgPlayerPungs) {
    return (CMsgPlayerPungsMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgFormClosedPungMsg_to_PMsg(PMsgFormClosedPungMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerFormsClosedPungMsg *CMsg_to_CMsgPlayerFormsClosedPungMsg (CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerFormsClosedPung) {
    return (CMsgPlayerFormsClosedPungMsg *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgKongMsg_to_PMsg(PMsgKongMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerClaimsKongMsg *CMsg_to_CMsgPlayerClaimsKongMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerClaimsKong) {
    return (CMsgPlayerClaimsKongMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgPlayerKongsMsg *CMsg_to_CMsgPlayerKongsMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerKongs) {
    return (CMsgPlayerKongsMsg *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgDeclareClosedKongMsg_to_PMsg(PMsgDeclareClosedKongMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerDeclaresClosedKongMsg *CMsg_to_CMsgPlayerDeclaresClosedKongMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerDeclaresClosedKong) {
    return (CMsgPlayerDeclaresClosedKongMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgAddToPungMsg_to_PMsg(PMsgAddToPungMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerAddsToPungMsg *CMsg_to_CMsgPlayerAddsToPungMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerAddsToPung) {
    return (CMsgPlayerAddsToPungMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgPlayerRobsKongMsg *CMsg_to_CMsgPlayerRobsKongMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerRobsKong) {
    return (CMsgPlayerRobsKongMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgQueryMahJongMsg_to_PMsg(PMsgQueryMahJongMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgCanMahJongMsg *CMsg_to_CMsgCanMahJongMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgCanMahJong) {
    return (CMsgCanMahJongMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgChowMsg_to_PMsg(PMsgChowMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgPlayerClaimsChowMsg *CMsg_to_CMsgPlayerClaimsChowMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerClaimsChow) {
    return (CMsgPlayerClaimsChowMsg *) msg;
  }
  else {
    return 0;
  }
}


CMsgPlayerChowsMsg *CMsg_to_CMsgPlayerChowsMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerChows) {
    return (CMsgPlayerChowsMsg *) msg;
  }
  else {
    return 0;
  }
}


PMsgMsg *PMsgFormClosedChowMsg_to_PMsg(PMsgFormClosedChowMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgPlayerFormsClosedChowMsg *CMsg_to_CMsgPlayerFormsClosedChowMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerFormsClosedChow) {
    return (CMsgPlayerFormsClosedChowMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgDeclareWashOutMsg_to_PMsg(PMsgDeclareWashOutMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgWashOutMsg *CMsg_to_CMsgWashOutMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgWashOut) {
    return (CMsgWashOutMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgMahJongMsg_to_PMsg(PMsgMahJongMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgPlayerClaimsMahJongMsg *CMsg_to_CMsgPlayerClaimsMahJongMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerClaimsMahJong) {
    return (CMsgPlayerClaimsMahJongMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgPlayerMahJongsMsg *CMsg_to_CMsgPlayerMahJongsMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerMahJongs) {
    return (CMsgPlayerMahJongsMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgPairMsg_to_PMsg(PMsgPairMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerPairsMsg *CMsg_to_CMsgPlayerPairsMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerPairs) {
    return (CMsgPlayerPairsMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgFormClosedPairMsg_to_PMsg(PMsgFormClosedPairMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerFormsClosedPairMsg *CMsg_to_CMsgPlayerFormsClosedPairMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerFormsClosedPair) {
    return (CMsgPlayerFormsClosedPairMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgSpecialSetMsg_to_PMsg(PMsgSpecialSetMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerSpecialSetMsg *CMsg_to_CMsgPlayerSpecialSetMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerSpecialSet) {
    return (CMsgPlayerSpecialSetMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgFormClosedSpecialSetMsg_to_PMsg(PMsgFormClosedSpecialSetMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerFormsClosedSpecialSetMsg *CMsg_to_CMsgPlayerFormsClosedSpecialSetMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerFormsClosedSpecialSet) {
    return (CMsgPlayerFormsClosedSpecialSetMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgShowTilesMsg_to_PMsg(PMsgShowTilesMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerShowsTilesMsg *CMsg_to_CMsgPlayerShowsTilesMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerShowsTiles) {
    return (CMsgPlayerShowsTilesMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgHandScoreMsg *CMsg_to_CMsgHandScoreMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgHandScore) {
    return (CMsgHandScoreMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgSettlementMsg *CMsg_to_CMsgSettlementMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgSettlement) {
    return (CMsgSettlementMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgSetPlayerOptionMsg_to_PMsg(PMsgSetPlayerOptionMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgPlayerOptionSetMsg *CMsg_to_CMsgPlayerOptionSetMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgPlayerOptionSet) {
    return (CMsgPlayerOptionSetMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgGameOverMsg *CMsg_to_CMsgGameOverMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgGameOver) {
    return (CMsgGameOverMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgSetGameOptionMsg_to_PMsg(PMsgSetGameOptionMsg *msg) {

  return (PMsgMsg *) msg;
}


CMsgGameOptionMsg *CMsg_to_CMsgGameOptionMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgGameOption) {
    return (CMsgGameOptionMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgQueryGameOptionMsg_to_PMsg(PMsgQueryGameOptionMsg *msg) {

  return (PMsgMsg *) msg;
}

PMsgMsg *PMsgListGameOptionsMsg_to_PMsg(PMsgListGameOptionsMsg *msg) {

  return (PMsgMsg *) msg;
}

PMsgMsg *PMsgChangeManagerMsg_to_PMsg(PMsgChangeManagerMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgChangeManagerMsg *CMsg_to_CMsgChangeManagerMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgChangeManager) {
    return (CMsgChangeManagerMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgSendMessageMsg_to_PMsg(PMsgSendMessageMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgMessageMsg *CMsg_to_CMsgMessageMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgMessage) {
    return (CMsgMessageMsg *) msg;
  }
  else {
    return 0;
  }
}

CMsgWallMsg  *CMsg_to_CMsgWallMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgWall) {
    return (CMsgWallMsg *) msg;
  }
  else {
    return 0;
  }
}


CMsgCommentMsg *CMsg_to_CMsgCommentMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgComment) {
    return (CMsgCommentMsg *) msg;
  }
  else {
    return 0;
  }
}

PMsgMsg *PMsgSwapTileMsg_to_PMsg(PMsgSwapTileMsg *msg) {

  return (PMsgMsg *) msg;
}

CMsgSwapTileMsg *CMsg_to_CMsgSwapTileMsg(CMsgMsg *msg) {
  if(msg -> type == CMsgSwapTile) {
    return (CMsgSwapTileMsg *) msg;
  }
  else {
    return 0;
  }
}
