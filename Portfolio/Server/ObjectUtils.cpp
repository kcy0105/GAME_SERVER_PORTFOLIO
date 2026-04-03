#include "pch.h"
#include "ObjectUtils.h"
#include "Player.h"
#include "GameSession.h"

atomic<int64> ObjectUtils::s_idGenerator = 1;

PlayerRef ObjectUtils::CreatePlayer(GameSessionRef session)
{
	PlayerRef player = make_shared<Player>();

	player->session = session;
	session->player.store(player);

	player->posInfo->set_state(Protocol::MOVE_STATE_IDLE);
	player->posInfo->set_looking_right(true);

	return player;
}
