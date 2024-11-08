#include "Settings.h"

QString Settings::serverUrl() const
{
	return value<QString>(ServerUrl);
}

void Settings::setServerUrl(const QString &serverUrl)
{
	m_subject.setValue(ServerUrl, serverUrl);
	m_subject.sync();
}

QString Settings::username() const
{
	return value<QString>(Username);
}

void Settings::setUsername(const QString &username)
{
	m_subject.setValue(Username, username);
	m_subject.sync();
}

QString Settings::password() const
{
	return value<QString>(Password);
}

void Settings::setPassword(const QString &password)
{
	m_subject.setValue(Password, password);
	m_subject.sync();
}

int Settings::bitRate() const
{
	return value<int>(BitRate, 320);
}

void Settings::setBitRate(int bitRate)
{
	m_subject.setValue(BitRate, bitRate);
	m_subject.sync();
}

bool Settings::scrobble() const
{
	return value<bool>(Scrobble);
}

void Settings::setScrobble(bool scrobble)
{
	m_subject.setValue(Scrobble, scrobble);
	m_subject.sync();
}
