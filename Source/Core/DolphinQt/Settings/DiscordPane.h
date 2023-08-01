#pragma once

#include <QWidget>

class QLineEdit;
class QVBoxLayout;

class DiscordPane : public QWidget
{
public:
  explicit DiscordPane();

private:
  void CreateWidgets();
  void ConnectWidgets();

  void LoadSettings();
  void SaveSettings();

  QVBoxLayout* m_main_layout;
  QLineEdit* m_discord_username;
};
