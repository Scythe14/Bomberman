#include "PlayerInput.hh"


PlayerInput::PlayerInput()
{
  keyValues[UP_KEY] = SDLK_UP;
  keyValues[DOWN_KEY] = SDLK_DOWN;
  keyValues[LEFT_KEY] = SDLK_LEFT;
  keyValues[RIGHT_KEY] = SDLK_RIGHT;
  keyValues[BOMB_KEY] = SDLK_SPACE;
  keyValues[SWITCHBOMB_KEY] = SDLK_c;
}

PlayerInput::PlayerInput(bool pl)
{
  if (pl == false) {
    keyValues[UP_KEY] = SDLK_UP;
    keyValues[DOWN_KEY] = SDLK_DOWN;
    keyValues[LEFT_KEY] = SDLK_LEFT;
    keyValues[RIGHT_KEY] = SDLK_RIGHT;
    keyValues[BOMB_KEY] = SDLK_SPACE;
    keyValues[SWITCHBOMB_KEY] = SDLK_c;
  }
  else {
    keyValues[UP_KEY] = SDLK_z;
    keyValues[DOWN_KEY] = SDLK_s;
    keyValues[LEFT_KEY] = SDLK_q;
    keyValues[RIGHT_KEY] = SDLK_d;
    keyValues[BOMB_KEY] = SDLK_LSHIFT;
    keyValues[SWITCHBOMB_KEY] = SDLK_LCTRL;
  }
}

PlayerInput::PlayerInput(const PlayerInput &ref)
{
  for (int i = static_cast<int>(UP_KEY); i < static_cast<int>(NO_KEY); ++i)
    keyValues[i] = ref.keyValues[i];
}

PlayerInput::~PlayerInput() {}

int	PlayerInput::getKey(InputKey key) const
{
  return keyValues[key];
}

void	PlayerInput::setKeyValue(InputKey key, int val)
{
  keyValues[key] = val;
}
