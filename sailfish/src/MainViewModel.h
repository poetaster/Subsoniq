#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include <QModelIndex>

#include "Playlist.h"
#include "Player.h"
#include "PlaylistModel.h"
#include "MetadataController.h"

class MainViewModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QObject *playlistModel READ playlistModel CONSTANT)
	Q_PROPERTY(QObject *playlist READ playlist CONSTANT)
	Q_PROPERTY(QObject *player READ player CONSTANT)
	Q_PROPERTY(QObject *metadata READ metadata CONSTANT)

	public:
		MainViewModel();

		QObject *playlistModel();
		QObject *playlist();
		QObject *player();
		QObject *metadata();

	private:
		MetadataController m_metadata;
		Playlist m_playlist;
		PlaylistModel m_playlistModel;
		Player m_player;
};

#endif // MAINVIEWMODEL_H
