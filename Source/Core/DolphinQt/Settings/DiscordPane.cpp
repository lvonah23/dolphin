#include "DolphinQt/Settings/DiscordPane.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QSignalBlocker>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>

#include "Common/Config/Config.h"

#include "Core/Config/MainSettings.h"

#include "DolphinQt/Config/SettingsWindow.h"
#include "DolphinQt/Settings.h"
#include "DolphinQt/QtUtils/SignalBlocking.h"

DiscordPane::DiscordPane()
{
  CreateWidgets();
  LoadSettings();
  ConnectWidgets();
}

void DiscordPane::CreateWidgets()
{
  m_main_layout = new QVBoxLayout();

  auto* discord_box = new QGroupBox(tr("Discord Settings"));
  auto* discord_settings_layout = new QGridLayout(discord_box);
  discord_box->setLayout(discord_settings_layout);

  int row = 0;

  m_discord_username = new QLineEdit();
  discord_settings_layout->addWidget(new QLabel(tr("Username:")), row, 0);
  discord_settings_layout->addWidget(m_discord_username, row, 1);
  row++;

  m_main_layout->addWidget(discord_box);

  m_main_layout->addStretch(1);
  setLayout(m_main_layout);
}

void DiscordPane::ConnectWidgets()
{
  connect(m_discord_username, &QLineEdit::editingFinished, this, &DiscordPane::SaveSettings);
}

void DiscordPane::LoadSettings()
{
  SignalBlocking(m_discord_username)
    ->setText(QString::fromStdString(Config::Get(Config::DISCORD_USERNAME)));
}

void DiscordPane::SaveSettings()
{
  Config::ConfigChangeCallbackGuard config_guard;

  // Discord Settings
  Config::SetBaseOrCurrent(Config::DISCORD_USERNAME, m_discord_username->text().toStdString());

  LoadSettings();
}
