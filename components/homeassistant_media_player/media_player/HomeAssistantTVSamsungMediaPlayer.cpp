#include "HomeAssistantTVSamsungMediaPlayer.h"
#include "JSONTextHelpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace homeassistant_media_player {

static const char* const TAG = "homeassistant.media_player_samsung";

void HomeAssistantTVSamsungMediaPlayer::setup() {
  supported_features_.push_back(TV_BACK);
  supported_features_.push_back(TV_HOME);
  supported_features_.push_back(MENU_HOME);
  supported_features_.push_back(REMOTE_MODE);
  HomeAssistantTVMediaPlayer::setup();
}

void HomeAssistantTVSamsungMediaPlayer::subscribe_media_artist() {
  ESP_LOGI(TAG, "subscribe_media_artist: %s", this->entity_id_.c_str());
  subscribe_homeassistant_state(
      &HomeAssistantBaseMediaPlayer::media_artist_changed, this->entity_id_,
      "media_series_title");
}

std::string HomeAssistantTVSamsungMediaPlayer::stringForRemoteCommand(
    MediaPlayerTVRemoteCommand command) {
  switch (command) {
    case UP:
      return "KEY_UP";
    case DOWN:
      return "KEY_DOWN";
    case LEFT:
      return "KEY_LEFT";
    case RIGHT:
      return "KEY_RIGHT";
    case SELECT:
      return "KEY_ENTER";
    case BACK:
      return "KEY_RETURN";
    case HOME:
      return "KEY_HOME";
    case POWER:
      return "KEY_CHDOWN";
    case VOLUME_UP:
      return "KEY_VOLUP";
    case VOLUME_DOWN:
      return "KEY_VOLDOWN";
    case PAUSE_COMMAND:
      return "KEY_PAUSE";
  }
  return "";
}

void HomeAssistantTVSamsungMediaPlayer::tvRemoteCommand(
    MediaPlayerTVRemoteCommand command) {
  auto commandString = stringForRemoteCommand(command);
  ESP_LOGI(TAG, "tvRemoteCommand: %s, %s", commandString.c_str(),
           entity_id_.c_str());
  call_homeassistant_service("media_player.play_media",
                             {{"entity_id", entity_id_.c_str()},
                              {"media_content_type", "send_key"},
                              {"media_content_id", commandString.c_str()}});
}
}  // namespace homeassistant_media_player
}  // namespace esphome
