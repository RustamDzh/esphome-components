#include "HomeAssistantTVKodiMediaPlayer.h"
#include "JSONTextHelpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace homeassistant_media_player {

static const char* const TAG = "homeassistant.media_player_kodi";

void HomeAssistantTVKodiMediaPlayer::setup() {
  supported_features_.push_back(TV_BACK);
  supported_features_.push_back(TV_HOME);
  supported_features_.push_back(MENU_HOME);
  supported_features_.push_back(REMOTE_MODE);
  HomeAssistantTVMediaPlayer::setup();
}

void HomeAssistantTVKodiMediaPlayer::subscribe_source() {
  ESP_LOGI(TAG, "subscribe_source: %s", this->entity_id_.c_str());
  subscribe_homeassistant_state(
      &HomeAssistantTVMediaPlayer::player_source_changed, this->entity_id_,
      "media_content_type");
}

void HomeAssistantTVKodiMediaPlayer::subscribe_media_artist() {
  ESP_LOGI(TAG, "subscribe_media_artist: %s", this->entity_id_.c_str());
  subscribe_homeassistant_state(
      &HomeAssistantTVMediaPlayer::media_artist_changed, this->entity_id_,
      "media_series_title");
}

std::string HomeAssistantTVKodiMediaPlayer::stringForRemoteCommand(
    MediaPlayerTVRemoteCommand command) {
  switch (command) {
    case UP:
      return "Input.Up";
    case DOWN:
      return "Input.Down";
    case LEFT:
      return "Input.Left";
    case RIGHT:
      return "Input.Right";
    case SELECT:
      return "Input.Select";
    case BACK:
      return "Input.Back";
    case HOME:
      return "Input.ContextMenu";
    case POWER:
      return "power";
    case VOLUME_UP:
      return "volume_up";
    case VOLUME_DOWN:
      return "volume_down";
    case PAUSE_COMMAND:
      return "pause";
  }
  return "";
}

void HomeAssistantTVKodiMediaPlayer::tvRemoteCommand(
    MediaPlayerTVRemoteCommand command) {
  auto commandString = stringForRemoteCommand(command);
  ESP_LOGI(TAG, "tvRemoteCommand: %s, %s", commandString.c_str(),
           entity_id_.c_str());
  call_homeassistant_service(
      "kodi.call_method",
      {{"entity_id", entity_id_.c_str()}, {"method", commandString.c_str()}});
}
}  // namespace homeassistant_media_player
}  // namespace esphome
